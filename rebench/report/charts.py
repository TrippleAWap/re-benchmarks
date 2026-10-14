from __future__ import annotations

import re
from pathlib import Path

import numpy as np

TOOL_COLORS = {
    "baseline": "#8a8a8a",
    "r2": "#e05d44",
    "ghidra": "#4caf7d",
    "ida": "#4d8fd6",
    "binaryninja": "#e8913d",
    "angr": "#9b59d0",
}

BACKGROUND = "#12141a"
FOREGROUND = "#e8e8ee"
GRID = "#2a2e3a"

_MPL_SETUP = False


def _setup_mpl():
    global _MPL_SETUP
    if _MPL_SETUP:
        return
    import matplotlib

    matplotlib.use("Agg")
    import matplotlib.pyplot as plt

    plt.rcParams.update(
        {
            "figure.facecolor": BACKGROUND,
            "axes.facecolor": BACKGROUND,
            "savefig.facecolor": BACKGROUND,
            "text.color": FOREGROUND,
            "axes.edgecolor": GRID,
            "axes.labelcolor": FOREGROUND,
            "xtick.color": FOREGROUND,
            "ytick.color": FOREGROUND,
            "grid.color": GRID,
            "font.size": 10,
        }
    )
    _MPL_SETUP = True


def _color(tool: str) -> str:
    return TOOL_COLORS.get(tool, "#aaaaaa")


def aggregate_runs(runs) -> dict[tuple[str, str], dict]:
    grouped: dict[tuple[str, str], list] = {}
    for run in runs:
        if run.skipped or not run.ok:
            continue
        grouped.setdefault((run.tool, run.binary_name), []).append(run)
    agg = {}
    for key, rs in grouped.items():
        n = len(rs)
        wall = sum(r.wall_time_s for r in rs) / n
        cpu = sum(r.cpu_time_s for r in rs) / n
        agg[key] = {
            "tool": rs[0].tool,
            "binary": rs[0].binary_name,
            "time": wall,
            "cpu": cpu,
            "parallelism": (cpu / wall) if wall > 0 else 0.0,
            "threads": max(r.peak_threads for r in rs),
            "mem": sum(r.peak_mem_mb for r in rs) / n,
            "functions": rs[-1].stats.get("functions", 0),
        }
    return agg


def _grouped_bars(ax, agg, value_key, ylabel, title, log=False):
    binaries = sorted({b for (_, b) in agg})
    tools = sorted({t for (t, _) in agg})
    width = 0.8 / max(1, len(tools))
    x = np.arange(len(binaries))
    for i, tool in enumerate(tools):
        values = [agg.get((tool, b), {}).get(value_key, 0) for b in binaries]
        ax.bar(x + i * width, values, width, label=tool, color=_color(tool))
    ax.set_xticks(x + width * (len(tools) - 1) / 2)
    ax.set_xticklabels(binaries, rotation=20, ha="right")
    ax.set_ylabel(ylabel)
    ax.set_title(title)
    if log:
        ax.set_yscale("log")
    ax.grid(True, axis="y", alpha=0.5)
    ax.legend(frameon=False)


def make_scaling_chart(session, manifest: dict, out_dir: Path,
                       kind: str = "wall") -> Path | None:
    scale_entries = {e["name"]: e for e in manifest.get("entries", []) if e.get("scale")}
    if not scale_entries:
        return None

    value_key = "cpu_time_s" if kind == "cpu" else "wall_time_s"
    data: dict[tuple[str, int], list[float]] = {}
    for run in session.runs:
        if run.skipped or not run.ok:
            continue
        entry = scale_entries.get(run.binary_name)
        if entry is None:
            continue
        data.setdefault((run.tool, int(entry["tier"])), []).append(getattr(run, value_key))
    if not data:
        return None

    _setup_mpl()
    import matplotlib.pyplot as plt

    tiers = sorted({t for (_, t) in data})
    tools = sorted({t for (t, _) in data})
    fig, ax = plt.subplots(figsize=(9, 5))
    for tool in tools:
        xs = [tier for tier in tiers if (tool, tier) in data]
        ys = [sum(data[(tool, tier)]) / len(data[(tool, tier)]) for tier in xs]
        if not xs:
            continue
        ax.plot(xs, ys, marker="o", label=tool, color=_color(tool))
    ax.set_xscale("log")
    ax.set_yscale("log")
    ax.set_xticks(tiers)
    ax.get_xaxis().set_major_formatter(plt.ScalarFormatter())
    ax.set_xlabel("functions in binary (scale tier)")
    if kind == "cpu":
        ax.set_ylabel("avg cpu time (s)")
        title = f"cpu time scaling - session {session.id}"
        fname = "scaling-cpu.png"
    else:
        ax.set_ylabel("avg wall time (s)")
        title = f"analysis time scaling - session {session.id}"
        fname = "scaling.png"
    ax.set_title(title)
    ax.grid(True, which="both", alpha=0.3)
    ax.legend(frameon=False)
    fig.tight_layout()
    p = out_dir / fname
    fig.savefig(p, dpi=150)
    plt.close(fig)
    return p


def make_charts(session, scores, out_dir: Path) -> list[Path]:
    _setup_mpl()
    import matplotlib.pyplot as plt

    out_dir.mkdir(parents=True, exist_ok=True)
    agg = aggregate_runs(session.runs)
    written: list[Path] = []

    if agg:
        fig, ax = plt.subplots(figsize=(9, 5))
        _grouped_bars(ax, agg, "time", "avg wall time (s)",
                      f"analysis speed - session {session.id}", log=True)
        fig.tight_layout()
        p = out_dir / "speed.png"
        fig.savefig(p, dpi=150)
        plt.close(fig)
        written.append(p)

        fig, ax = plt.subplots(figsize=(9, 5))
        _grouped_bars(ax, agg, "mem", "avg peak memory (MB)",
                      f"memory usage - session {session.id}")
        fig.tight_layout()
        p = out_dir / "memory.png"
        fig.savefig(p, dpi=150)
        plt.close(fig)
        written.append(p)

    if scores:
        score_agg = {}
        for s in scores:
            score_agg.setdefault((s.tool, s.binary_name), s)
        fig, ax = plt.subplots(figsize=(9, 5))
        binaries = sorted({b for (_, b) in score_agg})
        tools = sorted({t for (t, _) in score_agg})
        width = 0.8 / max(1, len(tools))

        x = np.arange(len(binaries))
        for i, tool in enumerate(tools):
            values = [
                min(score_agg.get((tool, b)).recovery_ratio, 10.0)
                if score_agg.get((tool, b)) else 0
                for b in binaries
            ]
            ax.bar(x + i * width, values, width, label=tool, color=_color(tool))
        ax.axhline(1.0, color=FOREGROUND, linestyle="--", linewidth=0.8, alpha=0.6)
        ax.set_xticks(x + width * (len(tools) - 1) / 2)
        ax.set_xticklabels(binaries, rotation=20, ha="right")
        ax.set_ylabel("functions found / ground truth (capped at 10)")
        ax.set_title(f"function recovery - session {session.id}")
        ax.grid(True, axis="y", alpha=0.5)
        ax.legend(frameon=False)
        fig.tight_layout()
        p = out_dir / "recovery.png"
        fig.savefig(p, dpi=150)
        plt.close(fig)
        written.append(p)

        sym_scores = [s for s in scores if re.search(r"-sym(\.exe)?$", s.binary_name)]
        if sym_scores and any(s.name_match_ratio is not None for s in sym_scores):
            fig, ax = plt.subplots(figsize=(9, 5))
            sym_agg = {(s.tool, s.binary_name): s for s in sym_scores}
            binaries = sorted({b for (_, b) in sym_agg})
            tools = sorted({t for (t, _) in sym_agg})
            width = 0.8 / max(1, len(tools))
            x = np.arange(len(binaries))
            for i, tool in enumerate(tools):
                values = []
                for b in binaries:
                    s = sym_agg.get((tool, b))
                    values.append(s.name_match_ratio if s and s.name_match_ratio is not None else 0)
                ax.bar(x + i * width, values, width, label=tool, color=_color(tool))
            ax.set_xticks(x + width * (len(tools) - 1) / 2)
            ax.set_xticklabels(binaries, rotation=20, ha="right")
            ax.set_ylim(0, 1.15)
            ax.set_ylabel("name match ratio")
            ax.set_title("symbol name recovery (unstripped builds)")
            ax.grid(True, axis="y", alpha=0.5)
            ax.legend(frameon=False)
            fig.tight_layout()
            p = out_dir / "namematch.png"
            fig.savefig(p, dpi=150)
            plt.close(fig)
            written.append(p)

    return written
