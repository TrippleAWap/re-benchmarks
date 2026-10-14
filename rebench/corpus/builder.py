from __future__ import annotations

import json
import shutil
import subprocess
from pathlib import Path

from ..models import sha256_file, utcnow

VARIANTS: dict[str, tuple[list[str], bool]] = {
    "d": (["-O0"], True),
    "o2": (["-O2"], True),
    "sym": (["-O0", "-g"], False),
}


class CorpusBuildError(RuntimeError):
    pass


def _require_tool(name: str) -> str:
    found = shutil.which(name)
    if not found:
        raise CorpusBuildError(
            f"'{name}' not found on PATH - install mingw64 binutils (gcc, nm, strip)"
        )
    return found


def dump_function_names(nm: str, exe: Path) -> list[str]:
    proc = subprocess.run(
        [nm, "--defined-only", str(exe)],
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
    )
    if proc.returncode != 0:
        raise CorpusBuildError(f"nm failed on {exe}: {proc.stderr[-400:]}")
    names = []
    for line in proc.stdout.splitlines():
        parts = line.split()
        if len(parts) == 3 and parts[1] in ("T", "t"):
            name = parts[2]
            if name.startswith("_"):
                continue
            names.append(name)
    return names


def sources_dir(config) -> Path:
    if config.corpus.sources.exists():
        return config.corpus.sources
    packaged = Path(__file__).resolve().parent / "sources"
    if packaged.exists():
        return packaged
    raise CorpusBuildError(f"sources dir not found: {config.corpus.sources}")


def build_corpus(config) -> dict:
    gcc = _require_tool("gcc")
    nm = _require_tool("nm")
    strip = _require_tool("strip")

    src_dir = sources_dir(config)
    sources = sorted(src_dir.glob("*.c"))
    if not sources:
        raise CorpusBuildError(f"no .c sources in {src_dir}")

    out_dir = config.corpus.dir
    build_dir = config.root / "corpus" / "build"
    out_dir.mkdir(parents=True, exist_ok=True)
    build_dir.mkdir(parents=True, exist_ok=True)

    entries = []
    for src in sources:
        for vtag, (flags, do_strip) in VARIANTS.items():
            obj = build_dir / f"{src.stem}-{vtag}.o"
            exe = out_dir / f"{src.stem}-{vtag}.exe"

            proc = subprocess.run(
                [gcc, *flags, "-c", "-o", str(obj), str(src)],
                capture_output=True, text=True,
            )
            if proc.returncode != 0:
                raise CorpusBuildError(
                    f"compile failed for {src.name} [{vtag}]: {proc.stderr[-800:]}"
                )

            proc = subprocess.run(
                [gcc, *flags, "-o", str(exe), str(obj)],
                capture_output=True, text=True,
            )
            if proc.returncode != 0:
                raise CorpusBuildError(
                    f"link failed for {src.name} [{vtag}]: {proc.stderr[-800:]}"
                )

            obj_names = set(dump_function_names(nm, obj))
            linked_names = set(dump_function_names(nm, exe))
            gt_names = sorted(obj_names & linked_names)

            if do_strip:
                strip_proc = subprocess.run([strip, str(exe)], capture_output=True, text=True)
                if strip_proc.returncode != 0:
                    raise CorpusBuildError(f"strip failed for {exe}: {strip_proc.stderr[-400:]}")

            entries.append(
                {
                    "name": exe.name,
                    "source": src.name,
                    "variant": vtag,
                    "path": str(exe.relative_to(config.root)),
                    "sha256": sha256_file(exe),
                    "size_bytes": exe.stat().st_size,
                    "ground_truth": {
                        "function_names": gt_names,
                        "function_count": len(gt_names),
                    },
                }
            )

    manifest = {
        "generated": utcnow().isoformat(),
        "gcc": gcc,
        "entries": entries,
    }
    config.corpus.manifest.parent.mkdir(parents=True, exist_ok=True)
    config.corpus.manifest.write_text(
        json.dumps(manifest, indent=2), encoding="utf-8"
    )
    return manifest


def load_manifest(path: Path) -> dict:
    if not Path(path).exists():
        raise CorpusBuildError(
            f"manifest not found: {path} - run 'rebench corpus build' first"
        )
    return json.loads(Path(path).read_text(encoding="utf-8"))
