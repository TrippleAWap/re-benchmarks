from __future__ import annotations

from pathlib import Path

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
        agg[key] = {
            "tool": rs[0].tool,
            "binary": rs[0].binary_name,
            "time": sum(r.wall_time_s for r in rs) / len(rs),
            "mem": sum(r.peak_mem_mb for r in rs) / len(rs),
            "functions": rs[-1].stats.get("functions", 0),
        }
    return agg


def _grouped_bars(ax, agg, value_key, ylabel, title, log=False):
    import numpy as np

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
        import numpy as np

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

        sym_scores = [s for s in scores if ".sym." in s.binary_name or s.binary_name.endswith("-sym.exe")]
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
