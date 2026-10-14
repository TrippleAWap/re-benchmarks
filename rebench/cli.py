from __future__ import annotations

import platform

import typer
from rich.console import Console
from rich.table import Table

from . import __version__
from .adapters import build_adapters
from .config import Config

app = typer.Typer(no_args_is_help=True, help="Benchmark harness for RE tools.")
console = Console()


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


def main() -> None:
    app()


if __name__ == "__main__":
    main()
