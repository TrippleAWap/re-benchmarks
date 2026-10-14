from __future__ import annotations

from pathlib import Path

from rich.text import Text
from textual.app import App, ComposeResult
from textual.widgets import DataTable, Footer, Header, ProgressBar, RichLog, Static

from ..config import Config
from ..models import SessionResult, ToolRun


class BenchApp(App):
    TITLE = "rebench"
    SUB_TITLE = "RE tool benchmark harness"
    BINDINGS = [("q", "quit", "Quit"), ("c", "clear_log", "Clear log")]

    def __init__(
        self,
        config: Config,
        tool_names: list[str] | None = None,
        binary_paths: list[Path] | None = None,
        timeout_s: float | None = None,
        repeats: int | None = None,
        tag: str | None = None,
    ):
        super().__init__()
        self.config = config
        self.tool_names = tool_names
        self.binary_paths = binary_paths
        self.timeout_s = timeout_s
        self.repeats = repeats
        self.tag = tag
        self._completed = 0
        self._total = 0

    def compose(self) -> ComposeResult:
        yield Header(show_clock=True)
        yield Static("preparing...", id="info")
        yield ProgressBar(total=1, show_eta=False, id="progress")
        yield DataTable(id="runs")
        yield RichLog(id="log", wrap=True, markup=True, highlight=True)
        yield Footer()

    def on_mount(self) -> None:
        table = self.query_one("#runs", DataTable)
        table.cursor_type = "row"
        table.add_columns("tool", "binary", "time (s)", "mem (MB)", "functions", "status")
        log = self.query_one("#log", RichLog)
        log.write("[bold cyan]rebench[/] starting - press [bold]q[/] to quit")
        self.run_worker(self._work, thread=True, exclusive=True)

    def _work(self) -> None:
        from ..runner import estimate_runs, run_and_save

        try:
            total, n_binaries, n_tools = estimate_runs(
                self.config,
                tool_names=self.tool_names,
                binary_paths=self.binary_paths,
                repeats=self.repeats,
            )
        except Exception as e:
            self.call_from_thread(self._fatal, str(e))
            return
        self._total = total
        self.call_from_thread(self._setup, n_binaries, n_tools, total)

        def on_start(adapter, binary, rep) -> None:
            label = binary.path.name
            self.call_from_thread(
                self._set_info,
                f"[cyan]{adapter.display_name}[/] analyzing [bold]{label}[/]"
                + (f" (repeat {rep + 1})" if rep else ""),
            )

        def on_end(run: ToolRun) -> None:
            self.call_from_thread(self._add_row, run)

        try:
            session, out = run_and_save(
                self.config,
                tool_names=self.tool_names,
                binary_paths=self.binary_paths,
                timeout_s=self.timeout_s,
                repeats=self.repeats,
                on_run_start=on_start,
                on_run_end=on_end,
                tag=self.tag,
            )
        except Exception as e:
            self.call_from_thread(self._fatal, str(e))
            return
        self.call_from_thread(self._finish, session, out)

    def _setup(self, n_binaries: int, n_tools: int, total: int) -> None:
        bar = self.query_one("#progress", ProgressBar)
        bar.total = max(1, total)
        self._set_info(
            f"{n_tools} tools x {n_binaries} binaries"
            f" x repeats = [bold]{total}[/] runs"
        )

    def _set_info(self, text: str) -> None:
        self.query_one("#info", Static).update(text)

    def _add_row(self, run: ToolRun) -> None:
        self._completed += 1
        bar = self.query_one("#progress", ProgressBar)
        bar.progress = self._completed

        table = self.query_one("#runs", DataTable)
        if run.ok:
            status = Text("ok", style="green")
        elif run.skipped:
            status = Text("skipped", style="yellow")
        else:
            status = Text("failed", style="red")
        funcs = str(run.stats.get("functions", "-")) if run.ok else "-"
        table.add_row(
            run.tool,
            run.binary_name,
            f"{run.wall_time_s:.2f}",
            f"{run.peak_mem_mb:.1f}",
            funcs,
            status,
        )
        table.scroll_end(animate=False)

        log = self.query_one("#log", RichLog)
        if run.skipped:
            log.write(f"[yellow]skipped[/] {run.tool}: {run.error}")
        elif not run.ok:
            log.write(f"[red]failed[/] {run.tool} on {run.binary_name}: {run.error}")
        else:
            log.write(
                f"[green]ok[/] {run.tool} {run.binary_name} "
                f"{run.wall_time_s:.2f}s {run.peak_mem_mb:.1f}MB"
            )

    def _finish(self, session: SessionResult, out: Path) -> None:
        ok = len([r for r in session.runs if r.ok])
        self._set_info(
            f"[bold green]done[/] - {ok}/{len(session.runs)} runs ok - saved {out}"
        )
        log = self.query_one("#log", RichLog)
        log.write(f"[bold green]session saved:[/] {out}")
        log.write("generate charts with: [bold]rebench report[/]")

    def _fatal(self, message: str) -> None:
        self._set_info("[bold red]failed[/]")
        self.query_one("#log", RichLog).write(f"[red]error:[/] {message}")

    def action_clear_log(self) -> None:
        self.query_one("#log", RichLog).clear()
