import json
import shutil
import subprocess
from pathlib import Path

import pytest

from rebench.adapters.ghidra import GhidraAdapter
from rebench.adapters.r2 import R2Adapter
from rebench.config import ToolConfig
from rebench.models import BinaryInfo

PING = Path(r"C:\Windows\System32\ping.exe")
HAS_R2 = R2Adapter(ToolConfig(name="r2"), Path.cwd()).probe().installed

pytestmark_pe = pytest.mark.skipif(not PING.exists(), reason="requires Windows PE")


@pytest.mark.skipif(not HAS_R2, reason="radare2 not installed")
@pytest.mark.skipif(not PING.exists(), reason="requires Windows PE")
def test_r2_real_analysis():
    adapter = R2Adapter(ToolConfig(name="r2"), Path.cwd())
    result = adapter.analyze(PING, timeout_s=120)
    assert result.stats["functions"] > 10
    assert result.stats["imports"] > 5
    assert result.stats["sections"] > 0


def test_r2_not_installed_raises():
    adapter = R2Adapter(
        ToolConfig(name="r2", path=r"C:\nonexistent\r2.exe"), Path.cwd()
    )
    with pytest.raises(Exception, match="not found"):
        adapter.analyze(PING, timeout_s=10)


def _make_mock_ghidra(tmp_path: Path) -> Path:
    mock_dir = tmp_path / "mock_ghidra"
    mock_dir.mkdir()
    bat = mock_dir / "analyzeHeadless.bat"
    bat.write_text(
        "@echo off\r\n"
        "set \"last=\"\r\n"
        ":parse\r\n"
        "if \"%~1\"==\"\" goto done\r\n"
        "set \"last=%~1\"\r\n"
        "shift\r\n"
        "goto parse\r\n"
        ":done\r\n"
        'echo {"functions": 12, "named_functions": 4, "imports": 30, "exports": 2, "symbols": 20, "strings": 55} > "%last%"\r\n'
        "exit /b 0\r\n",
        encoding="ascii",
    )
    return mock_dir


def test_ghidra_mock_analysis(tmp_path):
    mock_dir = _make_mock_ghidra(tmp_path)
    adapter = GhidraAdapter(
        ToolConfig(name="ghidra", install_dir=str(mock_dir)), Path.cwd()
    )
    status = adapter.probe()
    assert status.installed
    result = adapter.analyze(PING, timeout_s=60)
    assert result.stats["functions"] == 12
    assert result.stats["named_functions"] == 4
    assert result.stats["imports"] == 30


def test_ghidra_probe_missing():
    adapter = GhidraAdapter(
        ToolConfig(name="ghidra", install_dir=r"C:\nonexistent-ghidra"), Path.cwd()
    )
    assert not adapter.probe().installed


def test_util_json_len_and_names():
    from rebench.adapters.util import is_auto_name, json_len

    assert json_len("[1,2,3]") == 3
    assert json_len("") is None
    assert json_len("garbage") is None
    assert json_len('[{"a":1}] trailing noise') == 1
    assert is_auto_name("fcn.00401000")
    assert is_auto_name("FUN_140001000")
    assert not is_auto_name("check_password")
