#@runtime Jython
# rebench stats dump: writes analysis stats to a JSON file given as script arg.
# @category rebench
import json

from ghidra.program.model.data import StringDataType

args = getScriptArgs()
out_path = args[0]

program = currentProgram
fm = program.getFunctionManager()

functions = 0
named = 0
func_iter = fm.getFunctions(True)
while func_iter.hasNext():
    f = func_iter.next()
    functions += 1
    name = f.getName()
    if not (name.startswith("FUN_") or name.startswith("thunk_FUN_")):
        named += 1

symbols = 0
sym_iter = program.getSymbolTable().getAllSymbols(True)
while sym_iter.hasNext():
    sym_iter.next()
    symbols += 1

imports = 0
loc_iter = program.getExternalManager().getExternalLocations()
while loc_iter.hasNext():
    loc_iter.next()
    imports += 1

exports = 0
ep_iter = program.getSymbolTable().getExternalEntryPointIterator()
while ep_iter.hasNext():
    ep_iter.next()
    exports += 1

strings = 0
data_iter = program.getListing().getDefinedData(True)
while data_iter.hasNext():
    d = data_iter.next()
    try:
        if StringDataType.isInstanceOfString(d.getBaseDataType()):
            strings += 1
    except:
        pass

result = {
    "functions": functions,
    "named_functions": named,
    "symbols": symbols,
    "imports": imports,
    "exports": exports,
    "strings": strings,
}

fh = open(out_path, "w")
try:
    json.dump(result, fh)
finally:
    fh.close()
print("REBENCH_RESULT " + json.dumps(result))
