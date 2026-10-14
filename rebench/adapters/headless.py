from __future__ import annotations

import subprocess
from pathlib import Path

from .util import kill_tree, tail


def run_headless_json(
    cmd: list[str],
    out_json: Path,
    timeout_s: float,
    tool: str,
    cwd: Path | None = None,
    env: dict | None = None,
) -> str:
    """Run a headless tool that must write stats JSON to out_json.

    Returns the captured stdout. Raises AnalysisFailedError on timeout,
    nonzero exit, or missing output file.
    """
    from .base import AnalysisFailedError

    try:
        proc = subprocess.Popen(
            cmd,
            cwd=str(cwd) if cwd else None,
            env=env,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            encoding="utf-8",
            errors="replace",
        )
    except OSError as e:
        raise AnalysisFailedError(f"failed to launch {tool}: {e}") from e

    try:
        out, _ = proc.communicate(timeout=timeout_s)
    except subprocess.TimeoutExpired:
        kill_tree(proc.pid)
        raise AnalysisFailedError(f"{tool} timed out after {timeout_s:.0f}s") from None

    if proc.returncode != 0:
        raise AnalysisFailedError(f"{tool} exited with {proc.returncode}: {tail(out)}")
    if not out_json.exists():
        raise AnalysisFailedError(f"{tool} produced no stats file: {tail(out)}")
    return out or ""
