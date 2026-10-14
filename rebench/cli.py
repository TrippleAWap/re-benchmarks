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
            f"{run.wall_time_s:>8.2f}s {run.peak_mem_mb:>8.1f}MB {label}"
        )

    try:
        session, out = run_and_save(
            config,
            tool_names=tool_names,
            binary_paths=binary_paths,
            timeout_s=timeout_s,
            repeats=repeats,
            on_run_end=on_run_end,
        )
    except FileNotFoundError as e:
        console.print(f"[red]error:[/red] {e}")
        raise typer.Exit(1)

    if tag:
        session.tag = tag
        from .store import save_session

        out = save_session(config.run.results_dir, session)

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
    table.add_column("variant")
    table.add_column("gt functions", justify="right")
    table.add_column("size", justify="right")
    table.add_column("sha256", style="dim")
    for entry in manifest["entries"]:
        table.add_row(
            entry["name"],
            entry["variant"],
            str(entry["ground_truth"]["function_count"]),
            f"{entry['size_bytes'] / 1024:.0f}K",
            entry["sha256"][:12],
        )
    console.print(table)
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
    table.add_column("source")
    table.add_column("variant")
    table.add_column("gt functions", justify="right")
    table.add_column("path", overflow="fold")
    for entry in manifest["entries"]:
        table.add_row(
            entry["name"],
            entry.get("source", "-"),
            entry.get("variant", "-"),
            str(entry["ground_truth"]["function_count"]),
            entry.get("path", "-"),
        )
    console.print(table)


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
    table.add_column("mem (MB)", justify="right")
    table.add_column("status")
    for r in session.runs:
        status = "[green]ok[/green]" if r.ok else ("[yellow]skipped[/yellow]" if r.skipped else "[red]failed[/red]")
        detail = "" if r.ok or not r.error else f" - {r.error}"
        table.add_row(
            r.tool,
            r.binary_name,
            f"{r.wall_time_s:.2f}",
            f"{r.peak_mem_mb:.1f}",
            f"{status}{detail}",
        )
    console.print(table)


def main() -> None:
    app()


if __name__ == "__main__":
    main()
