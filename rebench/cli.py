from __future__ import annotations

import platform
from pathlib import Path
from typing import Optional, List

import typer
from rich.console import Console
from rich.table import Table

from . import __version__
from .adapters import build_adapters
from .config import Config
from .models import SessionResult, ToolRun

app = typer.Typer(no_args_is_help=True, help="Benchmark harness for RE tools.")
console = Console()
corpus_app = typer.Typer(no_args_is_help=True, help="Build and inspect the binary corpus.")
app.add_typer(corpus_app, name="corpus")


@app.callback()
def _callback() -> None:
    pass


@app.command("list-tools")
def list_tools() -> None:
    """Detect installed RE tools and show their status."""
    config = Config.load()
    table = Table(title=f"rebench {__version__} - tool detection", expand=True)
    table.add_column("tool", style="cyan", no_wrap=True)
    table.add_column("status")
    table.add_column("version", style="magenta")
    table.add_column("path / detail", overflow="fold")
    table.add_column("kind", style="dim")

    for adapter in build_adapters(config):
        if not adapter.config.enabled:
            table.add_row(adapter.display_name, "[yellow]disabled[/yellow]", "-", "-", adapter.kind)
            continue
        status = adapter.probe()
        if status.installed:
            mark = "[green]installed[/green]"
        else:
            mark = "[red]missing[/red]"
        table.add_row(
            adapter.display_name,
            mark,
            status.version or "-",
            status.path or status.detail or "-",
            adapter.kind,
        )
    console.print(table)
    console.print(f"host: {platform.node()} ({platform.system()} {platform.release()})")


@app.command()
def run(
    tools: Optional[str] = typer.Option(None, "--tools", "-t", help="Comma-separated tool names (default: all enabled)"),
    binary: Optional[List[Path]] = typer.Option(None, "--binary", "-b", help="Binary file or directory (repeatable)"),
    timeout_s: Optional[float] = typer.Option(None, "--timeout", help="Per-run timeout in seconds"),
    repeats: Optional[int] = typer.Option(None, "--repeats", min=1, help="Repeats per tool/binary pair"),
    threads: Optional[int] = typer.Option(None, "--threads", min=1, help="Cap every tool to N cpu cores (0 = unlimited)"),
    tag: Optional[str] = typer.Option(None, "--tag", help="Label stored with the session"),
) -> None:
    """Run every available tool against the given binaries."""
    from .runner import run_and_save

    config = Config.load()
    tool_names = [t.strip() for t in tools.split(",")] if tools else None
    binary_paths = [Path(b) for b in binary] if binary else None

    def on_run_end(run: ToolRun) -> None:
        label = _run_mark(run)
        console.print(
            f"  [cyan]{run.tool:<12}[/cyan] {run.binary_name:<32} "
            f"{run.wall_time_s:>8.2f}s {run.cpu_time_s:>8.2f}cpu "
            f"{run.peak_mem_mb:>8.1f}MB {run.peak_threads:>4}thr {label}"
        )

    try:
        session, out = run_and_save(
            config,
            tool_names=tool_names,
            binary_paths=binary_paths,
            timeout_s=timeout_s,
            repeats=repeats,
            tag=tag,
            threads=threads,
            on_run_end=on_run_end,
        )
    except FileNotFoundError as e:
        console.print(f"[red]error:[/red] {e}")
        raise typer.Exit(1)

    _print_summary(session)
    console.print(f"[green]saved[/green] {out}")


@corpus_app.command("build")
def corpus_build() -> None:
    """Compile corpus sources and record ground-truth manifest."""
    from .corpus.builder import build_corpus

    config = Config.load()
    try:
        manifest = build_corpus(config)
    except Exception as e:
        console.print(f"[red]error:[/red] {e}")
        raise typer.Exit(1)
    table = Table(title="corpus built", expand=True)
    table.add_column("binary", style="cyan")
    table.add_column("format")
    table.add_column("variant")
    table.add_column("gt functions", justify="right")
    table.add_column("size", justify="right")
    table.add_column("sha256", style="dim")
    for entry in manifest["entries"]:
        table.add_row(
            entry["name"],
            entry.get("format", "pe"),
            entry["variant"],
            str(entry["ground_truth"]["function_count"]),
            f"{entry['size_bytes'] / 1024:.0f}K",
            entry["sha256"][:12],
        )
    console.print(table)
    if manifest.get("elf_skipped"):
        console.print("[yellow]ELF variants skipped - no cross toolchain (install zig, or x86_64-linux-gnu-gcc)[/yellow]")
    console.print(f"[green]manifest saved[/green] {config.corpus.manifest}")


@corpus_app.command("list")
def corpus_list() -> None:
    """Show binaries and ground truth from the manifest."""
    from .corpus.builder import load_manifest

    config = Config.load()
    try:
        manifest = load_manifest(config.corpus.manifest)
    except Exception as e:
        console.print(f"[red]error:[/red] {e}")
        raise typer.Exit(1)
    table = Table(title=f"corpus (generated {manifest.get('generated', '?')})", expand=True)
    table.add_column("binary", style="cyan")
    table.add_column("format")
    table.add_column("source")
    table.add_column("variant")
    table.add_column("gt functions", justify="right")
    table.add_column("path", overflow="fold")
    for entry in manifest["entries"]:
        table.add_row(
            entry["name"],
            entry.get("format", "pe"),
            entry.get("source", "-"),
            entry.get("variant", "-"),
            str(entry["ground_truth"]["function_count"]),
            entry.get("path", "-"),
        )
    console.print(table)


@corpus_app.command("scale")
def corpus_scale(
    tiers: str = typer.Option("100,1000,5000,20000,50000", "--tiers", help="Comma-separated function counts, e.g. 100,1000,10000,50000"),
    no_strip: bool = typer.Option(False, "--no-strip", help="Keep symbols in scale binaries"),
) -> None:
    """Generate and build scaling binaries (N functions per tier)."""
    from .corpus.builder import build_scale_corpus

    config = Config.load()
    tier_list = []
    for t in tiers.split(","):
        t = t.strip()
        if not t:
            continue
        n = int(t)
        if n < 2:
            console.print(f"[red]error:[/red] tier must be >= 2: {n}")
            raise typer.Exit(1)
        tier_list.append(n)
    try:
        manifest = build_scale_corpus(config, tier_list, strip_binaries=not no_strip)
    except Exception as e:
        console.print(f"[red]error:[/red] {e}")
        raise typer.Exit(1)
    table = Table(title="scale corpus built", expand=True)
    table.add_column("binary", style="cyan")
    table.add_column("tier functions", justify="right")
    table.add_column("gt functions", justify="right")
    table.add_column("size", justify="right")
    for entry in manifest["entries"]:
        if not entry.get("scale"):
            continue
        table.add_row(
            entry["name"],
            str(entry["tier"]),
            str(entry["ground_truth"]["function_count"]),
            f"{entry['size_bytes'] / 1024:.0f}K",
        )
    console.print(table)
    console.print(f"[green]manifest saved[/green] {config.corpus.manifest}")
    console.print("run with: [bold]rebench run --binary corpus/binaries/scale --timeout 3600[/bold]")


def _run_mark(run: ToolRun) -> str:
    if run.skipped:
        return f"[yellow]skipped[/yellow] {run.error}"
    if not run.ok:
        return f"[red]failed[/red] {run.error}"
    return "[green]ok[/green]"


def _print_summary(session: SessionResult) -> None:
    if not session.runs:
        return
    table = Table(title=f"session {session.id}", expand=True)
    table.add_column("tool", style="cyan")
    table.add_column("binary")
    table.add_column("time (s)", justify="right")
    table.add_column("cpu (s)", justify="right")
    table.add_column("threads", justify="right")
    table.add_column("mem (MB)", justify="right")
    table.add_column("status")
    for r in session.runs:
        status = "[green]ok[/green]" if r.ok else ("[yellow]skipped[/yellow]" if r.skipped else "[red]failed[/red]")
        detail = "" if r.ok or not r.error else f" - {r.error}"
        table.add_row(
            r.tool,
            r.binary_name,
            f"{r.wall_time_s:.2f}",
            f"{r.cpu_time_s:.2f}",
            str(r.peak_threads),
            f"{r.peak_mem_mb:.1f}",
            f"{status}{detail}",
        )
    console.print(table)


@app.command("ui")
def ui(
    tools: Optional[str] = typer.Option(None, "--tools", "-t", help="Comma-separated tool names (default: all enabled)"),
    binary: Optional[List[Path]] = typer.Option(None, "--binary", "-b", help="Binary file or directory (repeatable)"),
    timeout_s: Optional[float] = typer.Option(None, "--timeout", help="Per-run timeout in seconds"),
    repeats: Optional[int] = typer.Option(None, "--repeats", min=1, help="Repeats per tool/binary pair"),
    threads: Optional[int] = typer.Option(None, "--threads", min=1, help="Cap every tool to N cpu cores (0 = unlimited)"),
    tag: Optional[str] = typer.Option(None, "--tag", help="Label stored with the session"),
) -> None:
    """Run benchmarks in a live TUI dashboard."""
    try:
        from .tui.dashboard import BenchApp
    except ImportError:
        console.print("[red]error:[/red] textual missing - install with: pip install rebench[tui]")
        raise typer.Exit(1)

    config = Config.load()
    tool_names = [t.strip() for t in tools.split(",")] if tools else None
    app = BenchApp(
        config,
        tool_names=tool_names,
        binary_paths=[Path(b) for b in binary] if binary else None,
        timeout_s=timeout_s,
        repeats=repeats,
        threads=threads,
        tag=tag,
    )
    app.run()


@app.command("report")
def report(
    session_id: Optional[str] = typer.Option(None, "--session", help="Session id, or comma-separated ids to merge (default: latest)"),
    out: Optional[Path] = typer.Option(None, "--out", help="Output directory"),
) -> None:
    """Render charts and a markdown report for a benchmark session."""
    from .corpus.builder import load_manifest
    from .metrics.compare import score_session
    from .report.charts import make_charts, make_scaling_chart
    from .report.summary import markdown_report
    from .store import list_sessions, load_session

    config = Config.load()
    if session_id:
        ids = [s.strip() for s in session_id.split(",") if s.strip()]
        sessions = []
        for sid in ids:
            p = config.run.results_dir / f"{sid}.jsonl"
            if not p.exists():
                console.print(f"[red]error:[/red] session not found: {p}")
                raise typer.Exit(1)
            sessions.append(load_session(p))
    else:
        found = list_sessions(config.run.results_dir)
        if not found:
            console.print("[red]error:[/red] no sessions recorded yet - run 'rebench run' first")
            raise typer.Exit(1)
        sessions = [load_session(found[-1])]

    session = sessions[0]
    if len(sessions) > 1:
        session.started_at = min(s.started_at for s in sessions)
        session.finished_at = max(s.finished_at for s in sessions)
        session.runs = [r for s in sessions for r in s.runs]
        session.id = "+".join(s.id for s in sessions)
        session.tag = ",".join(sorted({s.tag for s in sessions if s.tag}))
    scores = []
    scale_entries: list[dict] = []
    scaling_chart = None
    out_dir = out or (config.run.results_dir / f"report-{session.id}")
    out_dir.mkdir(parents=True, exist_ok=True)
    try:
        manifest = load_manifest(config.corpus.manifest)
        scores = score_session(session, manifest)
        scaling_chart = make_scaling_chart(session, manifest, out_dir)
        scale_entries = [e for e in manifest.get("entries", []) if e.get("scale")]
    except Exception as e:
        console.print(f"[yellow]accuracy scoring unavailable:[/yellow] {e}")

    try:
        charts = make_charts(session, scores, out_dir)
    except ImportError:
        console.print("[red]error:[/red] matplotlib missing - install with: pip install rebench[charts]")
        raise typer.Exit(1)

    if scaling_chart is not None:
        charts = [c for c in charts if c.name != "scaling.png"] + [scaling_chart]

    md = out_dir / "report.md"
    md.write_text(
        markdown_report(session, scores, charts, scaling_chart, scale_entries),
        encoding="utf-8",
    )

    for c in charts:
        console.print(f"  [blue]chart[/blue] {c}")
    console.print(f"[green]report written[/green] {md}")


def main() -> None:
    app()


if __name__ == "__main__":
    main()
