from __future__ import annotations

import json
import os
import shutil
import tempfile
import uuid
from pathlib import Path

from .base import AdapterResult, AnalysisFailedError, ToolAdapter, ToolNotInstalledError
from .headless import run_headless_json
from .registry import register
from .util import cpu_affinity_list
from ..models import ToolStatus

_SCRIPT_NAME = "rebench_dump.py"
_SEARCH_ROOTS = (Path(r"C:\Program Files"), Path(r"C:\Program Files (x86)"))
_HEADLESS_NAMES = ("idat.exe", "idat64.exe")


def _find_idat(install_dir: str | None) -> Path | None:
    candidates: list[Path] = []
    if install_dir:
        candidates.append(Path(install_dir))
    for root in _SEARCH_ROOTS:
        if not root.exists():
            continue
        for entry in sorted(root.glob("IDA*"), reverse=True):
            if entry.is_dir():
                candidates.append(entry)
    for c in candidates:
        for name in _HEADLESS_NAMES:
            p = c / name
            if p.exists():
                return p
    return None


@register
class IdaAdapter(ToolAdapter):
    name = "ida"
    display_name = "IDA"
    description = "IDA headless analysis via idat + IDAPython script."
    kind = "cli"

    def probe(self) -> ToolStatus:
        idat = _find_idat(self.config.install_dir)
        if idat is None:
            return ToolStatus(detail="idat/idat64 not found (set [tools.ida] install_dir)")
        v = None
        parent = idat.parent.name
        if "IDA" in parent:
            v = parent.replace("IDA", "").replace("Professional", "").strip()
        return ToolStatus(installed=True, path=str(idat), version=v or None,
                          detail=str(idat.parent))

    def analyze(self, binary: Path, timeout_s: float, threads: int = 0) -> AdapterResult:
        idat = _find_idat(self.config.install_dir)
        if idat is None:
            raise ToolNotInstalledError("ida headless (idat) not found")
        src_script = Path(__file__).resolve().parent.parent / "ida_scripts" / _SCRIPT_NAME
        if not src_script.exists():
            raise AnalysisFailedError(f"IDA script missing: {src_script}")

        workdir = Path(tempfile.mkdtemp(prefix="rebench_ida_"))
        try:
            out_json = workdir / "stats.json"
            script = workdir / _SCRIPT_NAME
            shutil.copyfile(src_script, script)
            db_path = workdir / "rebench.i64"

            env = dict(os.environ)
            env.setdefault("TVHEADLESS", "1")

            s_arg = f"-S{_SCRIPT_NAME} {out_json.name}"
            cmd = [str(idat), "-A", s_arg, f"-o{db_path}", str(binary)]

            run_headless_json(cmd, out_json, timeout_s, "ida", cwd=workdir, env=env,
                              affinity_cpus=cpu_affinity_list(threads))
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
            notes="headless analysis (auto_wait)",
        )
