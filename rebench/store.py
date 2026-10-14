from __future__ import annotations

import json
from dataclasses import asdict
from pathlib import Path
from typing import Any

from .models import SessionResult, ToolRun


def save_session(results_dir: Path, session: SessionResult) -> Path:
    results_dir.mkdir(parents=True, exist_ok=True)
    path = results_dir / f"{session.id}.jsonl"
    header = {k: v for k, v in asdict(session).items() if k != "runs"}
    lines = [json.dumps({"type": "session", **header}, default=str)]
    for run in session.runs:
        lines.append(json.dumps({"type": "run", **asdict(run)}, default=str))
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return path


def load_session(path: Path) -> SessionResult:
    session: SessionResult | None = None
    runs: list[ToolRun] = []
    with Path(path).open("r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            obj = json.loads(line)
            if obj.get("type") == "session":
                session = SessionResult(
                    id=obj["id"],
                    started_at=obj["started_at"],
                    finished_at=obj.get("finished_at", ""),
                    host=obj.get("host", ""),
                    tag=obj.get("tag", ""),
                )
            elif obj.get("type") == "run":
                runs.append(_run_from_obj(obj))
    if session is None:
        raise ValueError(f"no session header in {path}")
    session.runs = runs
    return session


def list_sessions(results_dir: Path) -> list[Path]:
    if not results_dir.exists():
        return []
    return sorted(results_dir.glob("*.jsonl"))


def _run_from_obj(obj: dict[str, Any]) -> ToolRun:
    return ToolRun(
        session=obj["session"],
        tool=obj["tool"],
        tool_version=obj.get("tool_version"),
        binary_name=obj["binary_name"],
        binary_sha256=obj.get("binary_sha256", ""),
        started=obj.get("started", ""),
        wall_time_s=float(obj.get("wall_time_s", 0.0)),
        peak_mem_mb=float(obj.get("peak_mem_mb", 0.0)),
        cpu_time_s=float(obj.get("cpu_time_s", 0.0)),
        peak_threads=int(obj.get("peak_threads", 0)),
        threads_limit=int(obj.get("threads_limit", 0)),
        ok=bool(obj.get("ok", False)),
        skipped=bool(obj.get("skipped", False)),
        error=obj.get("error", ""),
        stats=obj.get("stats", {}),
        artifacts=obj.get("artifacts", []),
        notes=obj.get("notes", ""),
        repeat=int(obj.get("repeat", 0)),
    )
