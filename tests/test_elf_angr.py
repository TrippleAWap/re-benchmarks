import shutil
import subprocess
from importlib.util import find_spec
from pathlib import Path

import pytest

from rebench.adapters.angr import AngrAdapter
from rebench.adapters.baseline import BaselineAdapter
from rebench.config import Config, CorpusConfig, ToolConfig
from rebench.corpus.builder import build_corpus, find_elf_toolchain

REPO = Path(__file__).resolve().parent.parent
CORPUS_BIN = REPO / "corpus" / "binaries" / "stringutils-d.exe"
ZIG = shutil.which("zig") is not None
R2 = BaselineAdapter(ToolConfig(name="baseline"), REPO).probe().installed
HAS_R2 = shutil.which("r2") is not None or shutil.which("r2.exe") is not None


def test_angr_real_analysis():
    if find_spec("angr") is None:
        pytest.skip("angr not installed")
    if not CORPUS_BIN.exists():
        pytest.skip("corpus not built")
    adapter = AngrAdapter(ToolConfig(name="angr"), REPO)
    result = adapter.analyze(CORPUS_BIN, timeout_s=300)
    assert result.stats["functions"] > 5
    assert result.stats["imports"] > 0
    assert result.stats["sections"] > 0
    assert len(result.stats["function_names"]) == result.stats["functions"]


def test_angr_timeout():
    if find_spec("angr") is None:
        pytest.skip("angr not installed")
    adapter = AngrAdapter(ToolConfig(name="angr"), REPO)
    if not CORPUS_BIN.exists():
        pytest.skip("corpus not built")
    from rebench.adapters.base import AnalysisFailedError

    with pytest.raises(AnalysisFailedError, match="timed out"):
        adapter.analyze(CORPUS_BIN, timeout_s=0.001)


def test_baseline_elf(tmp_path):
    if not ZIG:
        pytest.skip("zig not installed")
    elf = tmp_path / "hello"
    proc = subprocess.run(
        ["zig", "cc", "-target", "x86_64-linux-musl", "-static", "-O0",
         "-o", str(elf), str(REPO / "rebench" / "corpus" / "sources" / "stringutils.c")],
        capture_output=True, text=True, timeout=120,
    )
    assert proc.returncode == 0, proc.stderr[-500:]
    adapter = BaselineAdapter(ToolConfig(name="baseline"), REPO)
    result = adapter.analyze(elf, timeout_s=60)
    assert result.stats["functions"] >= 11
    assert result.stats["sections"] > 10
    assert "main" in result.stats["function_names"]
    assert result.stats["imports"] >= 0


def test_builder_elf_variants(tmp_path):
    if not ZIG:
        pytest.skip("zig not installed")
    config = Config(root=tmp_path)
    config.corpus = CorpusConfig(
        dir=tmp_path / "bin",
        manifest=tmp_path / "manifest.json",
        sources=REPO / "rebench" / "corpus" / "sources",
    )
    manifest = build_corpus(config, formats=["elf"])
    names = [e["name"] for e in manifest["entries"]]
    assert "stringutils-linux-d" in names
    assert "stringutils-linux-o2" in names
    assert "stringutils-linux-sym" in names
    for entry in manifest["entries"]:
        assert entry["format"] == "elf"
        assert entry["ground_truth"]["function_count"] >= 10
        assert entry["size_bytes"] > 3000


def test_r2_on_elf(tmp_path):
    if not (ZIG and HAS_R2):
        pytest.skip("needs zig + radare2")
    from rebench.adapters.r2 import R2Adapter

    elf = tmp_path / "hello"
    subprocess.run(
        ["zig", "cc", "-target", "x86_64-linux-musl", "-static", "-O0",
         "-o", str(elf), str(REPO / "rebench" / "corpus" / "sources" / "stringutils.c")],
        capture_output=True, text=True, timeout=120, check=True,
    )
    adapter = R2Adapter(ToolConfig(name="r2"), REPO)
    result = adapter.analyze(elf, timeout_s=300)
    assert result.stats["functions"] > 100
    assert result.stats["sections"] > 10


def test_find_elf_toolchain_shape():
    tc = find_elf_toolchain()
    if ZIG:
        assert tc is not None and tc[0].endswith("zig")
