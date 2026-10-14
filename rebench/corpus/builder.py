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


def find_elf_toolchain() -> list[str] | None:
    if shutil.which("zig"):
        return ["zig", "cc", "-target", "x86_64-linux-musl", "-static"]
    gnu = shutil.which("x86_64-linux-gnu-gcc")
    if gnu:
        return [gnu, "-static"]
    return None


def dump_function_names(nm: str, image: Path) -> list[str]:
    proc = subprocess.run(
        [nm, "--defined-only", str(image)],
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
    )
    if proc.returncode != 0:
        raise CorpusBuildError(f"nm failed on {image}: {proc.stderr[-400:]}")
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


def _build_variant(
    compile_cmd: list[str],
    flags: list[str],
    src: Path,
    obj: Path,
    image: Path,
) -> None:
    proc = subprocess.run(
        [*compile_cmd, *flags, "-c", "-o", str(obj), str(src)],
        capture_output=True, text=True,
    )
    if proc.returncode != 0:
        raise CorpusBuildError(
            f"compile failed for {src.name} -> {image.name}: {proc.stderr[-800:]}"
        )

    proc = subprocess.run(
        [*compile_cmd, *flags, "-o", str(image), str(obj)],
        capture_output=True, text=True,
    )
    if proc.returncode != 0:
        raise CorpusBuildError(
            f"link failed for {src.name} -> {image.name}: {proc.stderr[-800:]}"
        )


def build_corpus(config, sources: list[Path] | None = None,
                 formats: list[str] | None = None) -> dict:
    gcc = _require_tool("gcc")
    nm = _require_tool("nm")
    strip = _require_tool("strip")

    src_dir = sources_dir(config)
    if sources is None:
        sources = sorted(src_dir.glob("*.c"))
    if not sources:
        raise CorpusBuildError(f"no .c sources in {src_dir}")

    formats = formats or ["pe", "elf"]
    elf_cmd = find_elf_toolchain() if "elf" in formats else None

    out_dir = config.corpus.dir
    build_dir = config.root / "corpus" / "build"
    out_dir.mkdir(parents=True, exist_ok=True)
    build_dir.mkdir(parents=True, exist_ok=True)

    entries = []
    elf_skipped = "elf" in formats and elf_cmd is None

    for src in sources:
        if "pe" in formats:
            for vtag, (flags, do_strip) in VARIANTS.items():
                obj = build_dir / f"{src.stem}-{vtag}.o"
                exe = out_dir / f"{src.stem}-{vtag}.exe"
                _build_variant([gcc], flags, src, obj, exe)
                entries.append(_manifest_entry(nm, strip, do_strip, [obj], exe,
                                               src.name, vtag, "pe", config.root))

        if "elf" in formats and elf_cmd is not None:
            for vtag, (flags, do_strip) in VARIANTS.items():
                obj = build_dir / f"{src.stem}-linux-{vtag}.o"
                exe = out_dir / f"{src.stem}-linux-{vtag}"
                _build_variant(elf_cmd, flags, src, obj, exe)
                entries.append(_manifest_entry(nm, strip, do_strip, [obj], exe,
                                               src.name, vtag, "elf", config.root))

    manifest = {
        "generated": utcnow().isoformat(),
        "gcc": gcc,
        "elf_toolchain": " ".join(elf_cmd) if elf_cmd else None,
        "elf_skipped": elf_skipped,
        "entries": entries,
    }
    config.corpus.manifest.parent.mkdir(parents=True, exist_ok=True)
    config.corpus.manifest.write_text(
        json.dumps(manifest, indent=2), encoding="utf-8"
    )
    return manifest


def _manifest_entry(nm: str, strip: str, do_strip: bool, obj_paths: list[Path],
                    exe: Path, source_name: str, vtag: str, fmt: str, root: Path,
                    extra: dict | None = None) -> dict:
    obj_names: set[str] = set()
    for obj in obj_paths:
        obj_names.update(dump_function_names(nm, obj))
    linked_names = set(dump_function_names(nm, exe))
    gt_names = sorted(obj_names & linked_names)

    if do_strip:
        strip_proc = subprocess.run([strip, str(exe)], capture_output=True, text=True)
        if strip_proc.returncode != 0:
            raise CorpusBuildError(f"strip failed for {exe}: {strip_proc.stderr[-400:]}")

    entry = {
        "name": exe.name,
        "source": source_name,
        "variant": vtag,
        "format": fmt,
        "path": str(exe.relative_to(root)),
        "sha256": sha256_file(exe),
        "size_bytes": exe.stat().st_size,
        "ground_truth": {
            "function_names": gt_names,
            "function_count": len(gt_names),
        },
    }
    if extra:
        entry.update(extra)
    return entry


def build_scale_corpus(config, tiers: list[int], strip_binaries: bool = True) -> dict:
    gcc = _require_tool("gcc")
    nm = _require_tool("nm")
    strip = _require_tool("strip")

    gen_dir = config.root / "corpus" / "generated"
    out_dir = config.corpus.dir / "scale"
    build_dir = config.root / "corpus" / "build"
    gen_dir.mkdir(parents=True, exist_ok=True)
    out_dir.mkdir(parents=True, exist_ok=True)
    build_dir.mkdir(parents=True, exist_ok=True)

    from .generator import CHUNK_SIZE, generate_scale_sources, scale_binary_name

    new_entries = []
    built_names = set()
    for n in tiers:
        tier_dir = gen_dir / f"scale_s{n}"
        tier_dir.mkdir(parents=True, exist_ok=True)
        files = generate_scale_sources(n)
        for fname, content in files.items():
            (tier_dir / fname).write_text(content, encoding="utf-8")

        objs: list[Path] = []
        part_sources = sorted(
            f for f in files if f.endswith(".c") and "_part" in f
        )
        flags = ["-O0"]
        for fname in part_sources:
            obj = build_dir / f"scale_s{n}" / (Path(fname).stem + ".o")
            obj.parent.mkdir(parents=True, exist_ok=True)
            proc = subprocess.run(
                [gcc, *flags, "-c", "-o", str(obj), str(tier_dir / fname)],
                capture_output=True, text=True,
            )
            if proc.returncode != 0:
                raise CorpusBuildError(
                    f"compile failed for {fname}: {proc.stderr[-800:]}"
                )
            objs.append(obj)

        main_obj = build_dir / f"scale_s{n}" / "main.o"
        proc = subprocess.run(
            [gcc, *flags, "-c", "-o", str(main_obj),
             str(tier_dir / f"scale_s{n}_main.c")],
            capture_output=True, text=True,
        )
        if proc.returncode != 0:
            raise CorpusBuildError(
                f"compile failed for scale_s{n}_main.c: {proc.stderr[-800:]}"
            )
        objs.append(main_obj)

        exe = out_dir / f"{scale_binary_name(n)}-d.exe"
        proc = subprocess.run(
            [gcc, *flags, "-o", str(exe), *[str(o) for o in objs]],
            capture_output=True, text=True,
        )
        if proc.returncode != 0:
            raise CorpusBuildError(
                f"link failed for scale_s{n}: {proc.stderr[-800:]}"
            )

        built_names.add(exe.name)
        new_entries.append(
            _manifest_entry(nm, strip, strip_binaries, objs, exe,
                            f"scale_s{n} ({len(part_sources) + 1} TUs, "
                            f"chunks of {CHUNK_SIZE})",
                            "d", "pe", config.root,
                            extra={"scale": True, "tier": n})
        )

    for stale in out_dir.iterdir():
        if stale.is_file() and stale.name not in built_names:
            stale.unlink()

    manifest = {}
    if config.corpus.manifest.exists():
        manifest = json.loads(config.corpus.manifest.read_text(encoding="utf-8"))
    kept = [e for e in manifest.get("entries", []) if not e["name"].startswith("scale_")]
    manifest["entries"] = kept + new_entries
    manifest["scale_tiers"] = tiers
    manifest["generated"] = utcnow().isoformat()
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
