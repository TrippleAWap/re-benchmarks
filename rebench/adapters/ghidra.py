from __future__ import annotations

import json
import shutil
import subprocess
import tempfile
import uuid
from pathlib import Path

from .base import (
    AdapterResult,
    AnalysisFailedError,
    ToolAdapter,
    ToolNotInstalledError,
)
from .registry import register
from .util import kill_tree, tail
from ..models import ToolStatus

_SCRIPT_NAME = "rebench_dump.py"


def _find_headless(install_dir: str | None) -> Path | None:
    import os

    candidates: list[Path] = []
    if install_dir:
        candidates.append(Path(install_dir))
    env = os.environ.get("GHIDRA_INSTALL_DIR")
    if env:
        candidates.append(Path(env))
    for root in (Path(r"C:\Program Files"), Path(r"C:\Program Files (x86)"),
                 Path("C:\\"), Path.home()):
        if not root.exists():
            continue
        try:
            for entry in sorted(root.glob("ghidra*"), reverse=True):
                if entry.is_dir():
                    candidates.append(entry)
        except OSError:
            continue
    for c in candidates:
        for script in ("analyzeHeadless.bat", "analyzeHeadless"):
            p = c / "support" / script
            if p.exists():
                return p
            p = c / script
            if p.exists():
                return p
    return None


@register
class GhidraAdapter(ToolAdapter):
    name = "ghidra"
    display_name = "Ghidra"
    description = "Ghidra headless analysis via analyzeHeadless + post-script."
    kind = "cli"

    def _script_dir(self) -> Path:
        return Path(__file__).resolve().parent.parent / "ghidra_scripts"

    def probe(self) -> ToolStatus:
        headless = _find_headless(self.config.install_dir)
        if headless is None:
            return ToolStatus(detail="analyzeHeadless not found (set [tools.ghidra] install_dir)")
        v = None
        parent = headless.parent.parent
        if parent.name.lower().startswith("ghidra"):
            v = parent.name.replace("ghidra_", "").replace("ghidra", "").strip("_ ")
        return ToolStatus(installed=True, path=str(headless), version=v, detail=str(parent))

    def analyze(self, binary: Path, timeout_s: float) -> AdapterResult:
        headless = _find_headless(self.config.install_dir)
        if headless is None:
            raise ToolNotInstalledError("ghidra headless not found")
        script = self._script_dir() / _SCRIPT_NAME
        if not script.exists():
            raise AnalysisFailedError(f"post-script missing: {script}")

        workdir = Path(tempfile.mkdtemp(prefix="rebench_ghidra_"))
        out_json = workdir / "stats.json"
        project = f"rebench_{uuid.uuid4().hex[:8]}"
        cmd = [
            str(headless),
            str(workdir),
            project,
            "-import",
            str(binary),
            "-deleteProject",
            "-scriptPath",
            str(self._script_dir()),
            "-postScript",
            _SCRIPT_NAME,
            str(out_json),
        ]
        try:
            proc = subprocess.Popen(
                cmd,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True,
                encoding="utf-8",
                errors="replace",
            )
            try:
                out, _ = proc.communicate(timeout=timeout_s)
            except subprocess.TimeoutExpired:
                kill_tree(proc.pid)
                raise AnalysisFailedError(
                    f"ghidra timed out after {timeout_s:.0f}s"
                ) from None
        except OSError as e:
            shutil.rmtree(workdir, ignore_errors=True)
            raise AnalysisFailedError(f"failed to launch ghidra: {e}") from e

        try:
            if proc.returncode != 0:
                raise AnalysisFailedError(
                    f"ghidra exited with {proc.returncode}: {tail(out)}"
                )
            if not out_json.exists():
                raise AnalysisFailedError(
                    f"ghidra produced no stats file: {tail(out)}"
                )
            stats = json.loads(out_json.read_text(encoding="utf-8"))
        finally:
            shutil.rmtree(workdir, ignore_errors=True)

        return AdapterResult(
            stats={
                "functions": int(stats.get("functions", 0)),
                "named_functions": int(stats.get("named_functions", 0)),
                "function_names": list(stats.get("function_names", []))[:10000],
                "imports": int(stats.get("imports", 0)),
                "exports": int(stats.get("exports", 0)),
                "symbols": int(stats.get("symbols", 0)),
                "strings": int(stats.get("strings", 0)),
                "sections": 0,
            },
            notes="headless analysis",
        )
