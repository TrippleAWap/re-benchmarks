from pathlib import Path

from rebench.adapters.util import cpu_affinity_list
from rebench.config import Config, ToolConfig
from rebench.runner import resolve_threads, run_session

PING = Path(r"C:\Windows\System32\ping.exe")


class _FakeAdapter:
    def __init__(self, tool_config):
        self.config = tool_config
        self.name = tool_config.name


def test_cpu_affinity_list():
    import psutil

    n = psutil.cpu_count(logical=True) or 1
    assert cpu_affinity_list(0) is None
    assert cpu_affinity_list(-1) is None
    assert cpu_affinity_list(1) == [0]
    assert cpu_affinity_list(4) == [0, 1, 2, 3]
    assert cpu_affinity_list(n + 10) == list(range(n))


def test_resolve_threads_precedence():
    config = Config.load()
    config.run.threads = 4

    capped = _FakeAdapter(ToolConfig(name="baseline", threads=2))
    assert resolve_threads(capped, config) == 2

    uncapped = _FakeAdapter(ToolConfig(name="baseline"))
    assert resolve_threads(uncapped, config) == 4

    assert resolve_threads(uncapped, config, override=1) == 1
    assert resolve_threads(uncapped, config, override=0) == 4

    config.run.threads = 0
    assert resolve_threads(uncapped, config) == 0


def test_run_records_thread_limit(tmp_path):
    if not PING.exists():
        import pytest

        pytest.skip("requires Windows PE")
    config = Config.load()
    config.run.results_dir = tmp_path
    session = run_session(
        config,
        tool_names=["baseline"],
        binary_paths=[PING],
        threads=2,
    )
    run = session.runs[0]
    assert run.ok
    assert run.threads_limit == 2
    assert run.peak_threads >= 1


def test_run_thread_limit_from_tool_config(tmp_path):
    if not PING.exists():
        import pytest

        pytest.skip("requires Windows PE")
    config = Config.load()
    config.run.results_dir = tmp_path
    config.tools["baseline"] = ToolConfig(name="baseline", threads=1)
    session = run_session(
        config,
        tool_names=["baseline"],
        binary_paths=[PING],
    )
    run = session.runs[0]
    assert run.ok
    assert run.threads_limit == 1
