from __future__ import annotations

import socket
import threading
import time
import uuid
from pathlib import Path

import psutil

from .adapters import build_adapters
from .adapters.base import AdapterError, ToolAdapter, ToolNotInstalledError
from .config import Config
from .models import AdapterResult, BinaryInfo, SessionResult, ToolRun, ToolStatus, utcnow
from .store import save_session


class ResourceMonitor:
    def __init__(self, interval_s: float = 0.05):
        self.interval_s = interval_s
        self._peak_bytes = 0
        self._stop = threading.Event()
        self._thread: threading.Thread | None = None
        self._proc = psutil.Process()

    def _sample(self) -> None:
        procs = [self._proc, *self._proc.children(recursive=True)]
        total = 0
        for p in procs:
            try:
                total += p.memory_info().rss
            except psutil.Error:
                pass
        self._peak_bytes = max(self._peak_bytes, total)

    def _loop(self) -> None:
        while not self._stop.is_set():
            self._sample()
            self._stop.wait(self.interval_s)

    def __enter__(self) -> "ResourceMonitor":
        self._thread = threading.Thread(target=self._loop, daemon=True)
        self._thread.start()
        return self

    def __exit__(self, *exc) -> bool:
        self._stop.set()
        if self._thread is not None:
            self._thread.join()
        return False

    @property
    def peak_mb(self) -> float:
        return self._peak_bytes / (1024 * 1024)


def collect_binaries(config: Config, explicit: list[Path] | None = None) -> list[Path]:
    if explicit:
        paths = []
        for p in explicit:
            p = Path(p)
            if p.is_dir():
                paths.extend(sorted(f for f in p.iterdir() if f.is_file()))
            else:
                paths.append(p)
        missing = [str(p) for p in paths if not p.exists()]
        if missing:
            raise FileNotFoundError(f"binaries not found: {missing}")
        return paths
    corpus_dir = config.corpus.dir
    if corpus_dir.exists():
        found = sorted(f for f in corpus_dir.iterdir() if f.is_file())
        if found:
            return found
    raise FileNotFoundError(
        f"no binaries: pass --binary or build the corpus ({corpus_dir} is empty)"
    )


def run_single(
    session_id: str,
    adapter: ToolAdapter,
    tool_version: str | None,
    binary: BinaryInfo,
    timeout_s: float,
    repeat: int = 0,
) -> ToolRun:
    started = utcnow()
    t0 = time.perf_counter()
    with ResourceMonitor() as mon:
        try:
            result = adapter.analyze(binary.path, timeout_s=timeout_s)
            wall = time.perf_counter() - t0
            return ToolRun(
                session=session_id,
                tool=adapter.name,
                tool_version=tool_version,
                binary_name=binary.path.name,
                binary_sha256=binary.sha256,
                started=started.isoformat(),
                wall_time_s=round(wall, 4),
                peak_mem_mb=round(mon.peak_mb, 2),
                ok=True,
                skipped=False,
                error="",
                stats=result.stats,
                artifacts=[str(a) for a in result.artifacts],
                notes=result.notes,
                repeat=repeat,
            )
        except NotImplementedError as e:
            wall = time.perf_counter() - t0
            return _skipped_run(session_id, adapter, tool_version, binary, started, wall,
                                f"adapter not implemented: {e}", repeat)
        except ToolNotInstalledError as e:
            wall = time.perf_counter() - t0
            return _skipped_run(session_id, adapter, tool_version, binary, started, wall,
                                str(e), repeat)
        except AdapterError as e:
            wall = time.perf_counter() - t0
            return ToolRun(
                session=session_id,
                tool=adapter.name,
                tool_version=tool_version,
                binary_name=binary.path.name,
                binary_sha256=binary.sha256,
                started=started.isoformat(),
                wall_time_s=round(wall, 4),
                peak_mem_mb=round(mon.peak_mb, 2),
                ok=False,
                skipped=False,
                error=str(e),
                repeat=repeat,
            )


def _skipped_run(session_id, adapter, tool_version, binary, started: str, wall, reason, repeat) -> ToolRun:
    return ToolRun(
        session=session_id,
        tool=adapter.name,
        tool_version=tool_version,
        binary_name=binary.path.name,
        binary_sha256=binary.sha256,
        started=started,
        wall_time_s=round(wall, 4),
        peak_mem_mb=0.0,
        ok=False,
        skipped=True,
        error=reason,
        repeat=repeat,
    )


def run_session(
    config: Config,
    tool_names: list[str] | None = None,
    binary_paths: list[Path] | None = None,
    timeout_s: float | None = None,
    repeats: int | None = None,
    tag: str | None = None,
    on_run_start=None,
    on_run_end=None,
) -> SessionResult:
    timeout_s = timeout_s if timeout_s is not None else config.run.timeout_s
    repeats = repeats if repeats is not None else max(1, config.run.repeats)
    session_id = f"{utcnow().strftime('%Y%m%d-%H%M%S')}-{uuid.uuid4().hex[:6]}"

    binaries = collect_binaries(config, binary_paths)
    adapters = build_adapters(config)
    if tool_names:
        wanted = set(tool_names)
        adapters = [a for a in adapters if a.name in wanted]

    session = SessionResult(
        id=session_id,
        started_at=utcnow().isoformat(),
        finished_at="",
        host=socket.gethostname(),
        tag=tag or "",
    )

    probes: dict[str, ToolStatus] = {}
    for adapter in adapters:
        try:
            probes[adapter.name] = adapter.probe()
        except Exception as e:
            probes[adapter.name] = ToolStatus(detail=f"probe failed: {e}")

    for path in binaries:
        info = BinaryInfo.from_path(path)
        for adapter in adapters:
            status = probes[adapter.name]
            for rep in range(repeats):
                if on_run_start is not None:
                    on_run_start(adapter, info, rep)
                if not adapter.config.enabled:
                    run = _skipped_run(session_id, adapter, status.version, info,
                                       utcnow().isoformat(), 0.0, "disabled in config", rep)
                elif not status.installed:
                    run = _skipped_run(session_id, adapter, status.version, info,
                                       utcnow().isoformat(), 0.0,
                                       status.detail or "not installed", rep)
                else:
                    run = run_single(session_id, adapter, status.version, info,
                                     timeout_s, repeat=rep)
                session.runs.append(run)
                if on_run_end is not None:
                    on_run_end(run)

    session.finished_at = utcnow().isoformat()
    return session


def estimate_runs(
    config: Config,
    tool_names: list[str] | None = None,
    binary_paths: list[Path] | None = None,
    repeats: int | None = None,
) -> tuple[int, int, int]:
    repeats = repeats if repeats is not None else max(1, config.run.repeats)
    binaries = collect_binaries(config, binary_paths)
    adapters = build_adapters(config)
    if tool_names:
        wanted = set(tool_names)
        adapters = [a for a in adapters if a.name in wanted]
    runnable = 0
    for adapter in adapters:
        if not adapter.config.enabled:
            continue
        try:
            if adapter.probe().installed:
                runnable += 1
        except Exception:
            continue
    total = len(binaries) * runnable * repeats
    return total, len(binaries), runnable


def run_and_save(
    config: Config,
    tool_names: list[str] | None = None,
    binary_paths: list[Path] | None = None,
    timeout_s: float | None = None,
    repeats: int | None = None,
    tag: str | None = None,
    on_run_start=None,
    on_run_end=None,
) -> tuple[SessionResult, Path]:
    session = run_session(
        config,
        tool_names=tool_names,
        binary_paths=binary_paths,
        timeout_s=timeout_s,
        repeats=repeats,
        tag=tag,
        on_run_start=on_run_start,
        on_run_end=on_run_end,
    )
    out = save_session(config.run.results_dir, session)
    return session, out
