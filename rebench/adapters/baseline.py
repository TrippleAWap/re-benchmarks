from __future__ import annotations

from importlib.metadata import version
from importlib.util import find_spec
from pathlib import Path

from .base import AdapterResult, AnalysisFailedError, ToolAdapter
from .registry import register
from .util import count_printable_runs, detect_format, is_auto_name
from ..models import ToolStatus


@register
class BaselineAdapter(ToolAdapter):
    name = "baseline"
    display_name = "Baseline (pefile)"
    description = "Static parsing: imports, exports, sections, symbols. No analysis."
    kind = "library"

    def probe(self) -> ToolStatus:
        try:
            v = version("pefile")
        except Exception:
            return ToolStatus(detail="pefile python package not installed")
        elf = "ELF supported" if find_spec("elftools") else "ELF needs pyelftools"
        return ToolStatus(installed=True, version=v, detail=f"python pefile, {elf}")

    def analyze(self, binary: Path, timeout_s: float) -> AdapterResult:
        try:
            fmt = detect_format(binary)
        except ValueError as e:
            raise AnalysisFailedError(str(e)) from e
        if fmt == "pe":
            return self._analyze_pe(binary)
        return self._analyze_elf(binary)

    def _analyze_pe(self, binary: Path) -> AdapterResult:
        import pefile

        try:
            pe = pefile.PE(str(binary), fast_load=True)
        except pefile.PEFormatError as e:
            raise AnalysisFailedError(f"not a valid PE file: {e}") from e
        except OSError as e:
            raise AnalysisFailedError(f"cannot read binary: {e}") from e

        try:
            pe.parse_data_directories(
                directories=[
                    pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"],
                    pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_EXPORT"],
                ]
            )
            imports = 0
            if hasattr(pe, "DIRECTORY_ENTRY_IMPORT"):
                imports = sum(len(entry.imports) for entry in pe.DIRECTORY_ENTRY_IMPORT)
            exports = 0
            if hasattr(pe, "DIRECTORY_ENTRY_EXPORT") and pe.DIRECTORY_ENTRY_EXPORT.symbols:
                exports = len(pe.DIRECTORY_ENTRY_EXPORT.symbols)
            sections = len(pe.sections)
        finally:
            pe.close()

        return AdapterResult(
            stats={
                "functions": 0,
                "named_functions": 0,
                "imports": imports,
                "exports": exports,
                "sections": sections,
                "strings": count_printable_runs(binary),
                "symbols": 0,
            },
            notes="static PE metadata only, no analysis",
        )

    def _analyze_elf(self, binary: Path) -> AdapterResult:
        if find_spec("elftools") is None:
            raise AnalysisFailedError(
                "pyelftools not installed - install with: pip install pyelftools"
            )
        from elftools.elf.elffile import ELFFile

        try:
            stream = open(binary, "rb")
        except OSError as e:
            raise AnalysisFailedError(f"cannot read binary: {e}") from e

        try:
            elf = ELFFile(stream)
            sections = elf.num_sections()
            symtab = elf.get_section_by_name(".symtab")
            dynsym = elf.get_section_by_name(".dynsym")

            defined_funcs: list[str] = []
            symbol_count = 0
            for sec in (symtab, dynsym):
                if sec is None:
                    continue
                for sym in sec.iter_symbols():
                    symbol_count += 1
                    if (
                        sym["st_info"]["type"] == "STT_FUNC"
                        and sym["st_shndx"] != "SHN_UNDEF"
                        and sym["st_value"] != 0
                    ):
                        defined_funcs.append(sym.name)

            imports = 0
            exports = 0
            if dynsym is not None:
                for sym in dynsym.iter_symbols():
                    if sym["st_info"]["type"] != "STT_FUNC":
                        continue
                    if sym["st_shndx"] == "SHN_UNDEF":
                        imports += 1
                    elif sym["st_value"] != 0:
                        exports += 1
        finally:
            stream.close()

        unique = sorted(set(defined_funcs))
        named = sum(1 for n in unique if not is_auto_name(n))
        return AdapterResult(
            stats={
                "functions": len(unique),
                "named_functions": named,
                "function_names": unique[:10000],
                "imports": imports,
                "exports": exports,
                "sections": sections,
                "strings": count_printable_runs(binary),
                "symbols": symbol_count,
            },
            notes="static ELF metadata only, no analysis",
        )
