import json
import sys
from pathlib import Path

import pytest

from rebench.config import Config
from rebench.models import BinaryInfo, SessionResult, ToolRun
from rebench.runner import run_session
from rebench.store import load_session, save_session

PING = Path(r"C:\Windows\System32\ping.exe")

pytestmark = pytest.mark.skipif(
    not PING.exists(), reason="requires a Windows PE to parse"
)


def test_baseline_stats():
    config = Config.load()
    session = run_session(config, tool_names=["baseline"], binary_paths=[PING])
    assert len(session.runs) == 1
    run = session.runs[0]
    assert run.ok, run.error
    assert run.stats["imports"] > 0
    assert run.stats["sections"] > 0
    assert run.wall_time_s > 0


def test_run_skips_uninstalled_adapters():
    config = Config.load()
    session = run_session(config, tool_names=["ghidra", "baseline"], binary_paths=[PING])
    by_tool = {r.tool: r for r in session.runs}
    assert by_tool["baseline"].ok
    assert by_tool["ghidra"].skipped


def test_store_roundtrip(tmp_path):
    config = Config.load()
    session = run_session(config, tool_names=["baseline"], binary_paths=[PING])
    out = save_session(tmp_path, session)
    assert out.exists()
    loaded = load_session(out)
    assert loaded.id == session.id
    assert loaded.host == session.host
    assert len(loaded.runs) == len(session.runs)
    original = session.runs[0]
    restored = loaded.runs[0]
    assert restored.tool == original.tool
    assert restored.ok == original.ok
    assert restored.stats == original.stats
    assert restored.wall_time_s == original.wall_time_s
