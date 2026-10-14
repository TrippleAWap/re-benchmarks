import asyncio
from pathlib import Path

import pytest

from textual.widgets import Static

from rebench.config import Config
from rebench.tui.dashboard import BenchApp

PING = Path(r"C:\Windows\System32\ping.exe")

pytestmark = pytest.mark.skipif(
    not PING.exists(), reason="requires a Windows PE to parse"
)


def test_tui_dashboard_smoke():
    config = Config.load()

    async def main() -> None:
        app = BenchApp(
            config, tool_names=["baseline"], binary_paths=[PING], repeats=1
        )
        async with app.run_test(size=(110, 40)) as pilot:
            for _ in range(150):
                await pilot.pause(0.1)
                info = str(app.query_one("#info", Static).render())
                if "done" in info or "failed" in info:
                    break
            info = str(app.query_one("#info", Static).render())
            assert "done" in info, f"dashboard did not finish: {info}"
            assert app._completed >= 1
            table = app.query_one("#runs")
            assert table.row_count >= 1

    asyncio.run(main())
