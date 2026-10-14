import json

import ida_auto
import ida_entry
import idaapi
import idautils
import idc

out_path = idc.ARGV[1] if len(idc.ARGV) > 1 else "rebench_stats.json"
ida_auto.auto_wait()

AUTO_PREFIXES = (
    "sub_",
    "nullsub_",
    "j_",
    "unknown_libname_",
    "unknown_function_",
    "SEH_",
    "TlsCallback_",
    "loc_",
    "locret_",
)

functions = 0
named = 0
for ea in idautils.Functions():
    functions += 1
    name = idc.get_func_name(ea) or ""
    if name and not name.startswith(AUTO_PREFIXES):
        named += 1

imports = 0


def _import_cb(ea, name, ordinal):
    global imports
    imports += 1
    return True


for i in range(idaapi.get_import_module_qty()):
    idaapi.enum_import_names(i, _import_cb)

exports = ida_entry.get_entry_qty()

symbols = sum(1 for _ in idautils.Names())

strings = sum(1 for _ in idautils.Strings())

result = {
    "functions": functions,
    "named_functions": named,
    "imports": imports,
    "exports": exports,
    "symbols": symbols,
    "strings": strings,
}

with open(out_path, "w") as fh:
    json.dump(result, fh)

idc.qexit(0)
