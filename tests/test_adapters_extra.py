import re
from pathlib import Path

import pytest

from rebench.adapters.util import is_auto_name


def test_util_basics():
    assert is_auto_name("fcn.00401000")
    assert is_auto_name("FUN_140001000")
    assert is_auto_name("sub_401000")
    assert is_auto_name("")
    assert not is_auto_name("check_password")


def test_json_len_edge_cases():
    from rebench.adapters.util import json_len

    assert json_len("[1,2,3]") == 3
    assert json_len('??[{"a":1}]') == 1
    assert json_len("") is None
    assert json_len("total garbage") is None


def test_parse_marked_sections():
    from rebench.adapters.util import parse_marked_sections

    text = '__R2B_FUNCTIONS__\n[{"name":"a"}]\n__R2B_IMPORTS__\n[{"o":1},{"o":2}]\n'
    sections = parse_marked_sections(text)
    assert sections["functions"] == '[{"name":"a"}]'
    assert sections["imports"] == '[{"o":1},{"o":2}]'


def test_first_json_list():
    from rebench.adapters.util import first_json_list

    assert first_json_list('??[{"name":"x"}]') == [{"name": "x"}]
    assert first_json_list("no json here") is None


def test_binaryninja_not_installed():
    from pathlib import Path

    from rebench.adapters.binaryninja import BinaryNinjaAdapter
    from rebench.adapters.base import ToolNotInstalledError
    from rebench.config import ToolConfig

    try:
        import binaryninja  # noqa: F401

        pytest.skip("binaryninja installed")
    except ImportError:
        pass
    adapter = BinaryNinjaAdapter(ToolConfig(name="binaryninja"), Path.cwd())
    assert not adapter.probe().installed
    with pytest.raises(ToolNotInstalledError):
        adapter.analyze(Path("x.exe"), timeout_s=5)


def test_ghidra_script_is_jython_safe():
    script = Path(__file__).resolve().parent.parent / "rebench" / "ghidra_scripts" / "rebench_dump.py"
    assert script.exists()
    content = script.read_text(encoding="utf-8")
    assert "f\"" not in content
    assert not re.search(r"\blist\(.*iterator", content)


def test_ida_script_present():
    script = Path(__file__).resolve().parent.parent / "rebench" / "ida_scripts" / "rebench_dump.py"
    assert script.exists()
    content = script.read_text(encoding="utf-8")
    assert "auto_wait" in content
    assert "qexit" in content
