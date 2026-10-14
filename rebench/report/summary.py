from __future__ import annotations

from pathlib import Path

from .charts import aggregate_runs


def _fmt(v: float, digits: int = 2) -> str:
    return f"{v:.{digits}f}"


def markdown_report(session, scores, chart_paths: list[Path],
                    scaling_chart: Path | None = None,
                    scale_entries: list[dict] | None = None) -> str:
    lines: list[str] = []
    lines.append(f"# rebench report - session `{session.id}`")
    lines.append("")
    lines.append(f"- host: **{session.host}**")
    if session.tag:
        lines.append(f"- tag: **{session.tag}**")
    lines.append(f"- started: {session.started_at}")
    lines.append(f"- finished: {session.finished_at}")
    ok_runs = [r for r in session.runs if r.ok and not r.skipped]
    lines.append(f"- runs: {len(ok_runs)} ok, "
                 f"{len([r for r in session.runs if r.skipped])} skipped, "
                 f"{len([r for r in session.runs if not r.ok and not r.skipped])} failed")
    lines.append("")

    skipped = [r for r in session.runs if r.skipped]
    if skipped:
        lines.append("## Skipped tools")
        lines.append("")
        seen = {}
        for r in skipped:
            seen.setdefault(r.tool, r.error)
        for tool, err in sorted(seen.items()):
            lines.append(f"- **{tool}**: {err}")
        lines.append("")

    agg = aggregate_runs(session.runs)
    if agg:
        lines.append("## Speed & memory")
        lines.append("")
        lines.append("| tool | binary | avg time (s) | avg peak mem (MB) |")
        lines.append("|---|---|---:|---:|")
        for key in sorted(agg):
            a = agg[key]
            lines.append(
                f"| {a['tool']} | {a['binary']} | {_fmt(a['time'])} | {_fmt(a['mem'], 1)} |"
            )
        lines.append("")

        for chart in chart_paths:
            if chart.name in ("speed.png", "memory.png"):
                lines.append(f"![{chart.stem}]({chart.name})")
                lines.append("")

    if scaling_chart is not None and scale_entries:
        lines.append("## Scaling (analysis time vs binary complexity)")
        lines.append("")
        entries = sorted(scale_entries, key=lambda e: e["tier"])
        tools = sorted({r.tool for r in session.runs if r.ok and not r.skipped})
        lines.append("| tier | gt functions | size | " + " | ".join(tools) + " |")
        lines.append("|---|---:|---:|" + "---:|" * len(tools))
        agg = aggregate_runs(session.runs)
        for e in entries:
            times = []
            for tool in tools:
                a = agg.get((tool, e["name"]))
                times.append(_fmt(a["time"]) if a else "-")
            lines.append(
                f"| {e['tier']} | {e['ground_truth']['function_count']} | "
                f"{e['size_bytes'] / 1024:.0f}K | " + " | ".join(times) + " |"
            )
        lines.append("")
        lines.append(f"![scaling]({scaling_chart.name})")
        lines.append("")

    if scores:
        lines.append("## Function recovery (vs ground truth)")
        lines.append("")
        lines.append("| tool | binary | found | ground truth | recovery | name match |")
        lines.append("|---|---|---:|---:|---:|---:|")
        for s in sorted(scores, key=lambda s: (s.binary_name, s.tool)):
            nm = "-" if s.name_match_ratio is None else f"{s.name_match_ratio:.0%}"
            lines.append(
                f"| {s.tool} | {s.binary_name} | {s.functions} | {s.gt_functions} | "
                f"{s.recovery_ratio:.2f} | {nm} |"
            )
        lines.append("")
        for chart in chart_paths:
            if chart.name in ("recovery.png", "namematch.png"):
                lines.append(f"![{chart.stem}]({chart.name})")
                lines.append("")

    failed = [r for r in session.runs if not r.ok and not r.skipped]
    if failed:
        lines.append("## Failures")
        lines.append("")
        for r in failed:
            lines.append(f"- **{r.tool}** on `{r.binary_name}`: {r.error}")
        lines.append("")

    return "\n".join(lines) + "\n"
