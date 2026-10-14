import pytest
from typer.testing import CliRunner

from rebench.cli import app
from rebench import __version__

runner = CliRunner()


def test_version():
    assert __version__ == "0.1.0"


def test_list_tools_runs():
    result = runner.invoke(app, ["list-tools"])
    assert result.exit_code == 0
    assert "tool detection" in result.output
    for tool in ("Baseline", "radare2", "Ghidra", "IDA", "Binary Ninja", "angr"):
        assert tool in result.output
