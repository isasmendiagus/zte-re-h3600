#!/usr/bin/env python3
"""Extract function signatures + inferred struct sizes from Ghidra decomp.

Reads every `decomp_all_*.c` in tasks/00.10.02.re-stock-kmods/findings/
and produces a single ARG_SIGNATURES.json:

{
  "<module_name>": {
    "<function_name>": {
      "addr":   "0x00020480",       # entry address (hex string)
      "ret":    "undefined4",       # return type
      "args":   [                   # list of arg specs (max 4 = r0..r3 useful)
        {"kind": "pointer", "type": "int *", "name": "param_1", "deref": 32},
        {"kind": "scalar",  "type": "uint",  "name": "param_2"}
      ]
    }, ...
  }, ...
}

Used by kotrace's trace-stub: given a function entry address, look up the
arg specs to know which r0-r3 are scalars (record value) vs pointers
(record value + safely deref N bytes).

Struct size inference: scans the function body for `*(type *)(param_N + 0xOFFSET)`
patterns; max(offset) + 4 = inferred size (capped at 256). Falls back to 32
when no body offsets found.
"""
import json
import re
import sys
from pathlib import Path

FINDINGS = Path(__file__).resolve().parents[1] / "findings"
OUT = FINDINGS / "ARG_SIGNATURES.json"

# Match the header comment Ghidra inserts.
FUNC_HEADER_RE = re.compile(
    r'/\*\s*=+\s*FUNCTION:\s+(?P<name>\S+)\s*@\s*(?P<addr>[0-9a-fA-F]+)\s*=+\s*\*/'
)

# Match a typical C signature line. Tolerates `static`, multi-space, etc.
# Captures: return type (possibly with *), name, raw args string.
# This is intentionally permissive; Ghidra writes them on a single line.
SIG_RE = re.compile(
    r'^\s*(?P<ret>(?:static\s+)?[\w\*\s]+?)\s+'
    r'(?P<name>\w+)\s*'
    r'\((?P<args>[^)]*)\)\s*$'
)

# A single-arg pattern inside the parens: `<type> <name>` or `<type>* <name>`.
# Ghidra spaces: `int param_1`, `byte *param_3`, `undefined4 *param_2`.
ARG_RE = re.compile(
    r'^\s*(?P<type>(?:const\s+)?[\w]+(?:\s*\*+)?)\s*(?P<name>\w+)\s*$'
)

# Struct-offset access in body: `*(uint *)(param_N + 0xOFFSET)` or
# `*(byte *)(param_N + 0xOFFSET)`. We scan for these to bound struct size.
BODY_OFFSET_RE = re.compile(
    r'\*\s*\(\s*(?P<dtype>\w+)\s*\*\s*\)\s*\(\s*(?P<arg>param_\d+)\s*\+\s*0x(?P<off>[0-9a-fA-F]+)\s*\)'
)
# Also catch `param_N[idx]` array-style (less common in Ghidra decomp).
ARRAY_RE = re.compile(r'(?P<arg>param_\d+)\s*\[\s*(?P<idx>\d+)\s*\]')

SCALAR_TYPES = {
    "int", "uint", "long", "ulong", "short", "ushort", "char", "uchar",
    "byte", "undefined1", "undefined2", "undefined4", "undefined8",
    "bool", "code", "size_t", "ssize_t",
    "u8", "u16", "u32", "u64", "s8", "s16", "s32", "s64",
}

DEFAULT_DEREF = 32       # if pointer with no struct evidence
MAX_DEREF = 256          # cap; bigger structs we'll override manually
TYPE_SIZE = {            # bytes per access type, for body-scan
    "byte": 1, "char": 1, "uchar": 1, "undefined1": 1, "u8": 1, "s8": 1,
    "ushort": 2, "short": 2, "undefined2": 2, "u16": 2, "s16": 2,
    "int": 4, "uint": 4, "long": 4, "ulong": 4, "undefined4": 4,
    "u32": 4, "s32": 4, "code": 4,
}


def is_pointer_type(t: str) -> bool:
    return "*" in t


def classify_arg(type_str: str, body: str, arg_name: str) -> dict:
    """Return spec dict for one arg. type_str is the Ghidra type.

    Ghidra often types a struct-pointer arg as plain `int` (when it
    can't confidently infer the type). Compensate: if a scalar-typed
    arg is dereferenced in the body via `*(type*)(arg + 0xN)`, promote
    it to a pointer. This catches cases like
        undefined4 sbrg_add_mactable(int param_1)
        ... *(uint*)(param_1 + 0x18) ...
    where param_1 is really a struct pointer."""
    t = type_str.strip()
    base = t.replace("*", "").strip()
    if is_pointer_type(t):
        size = infer_struct_size(body, arg_name)
        return {"kind": "pointer", "type": t, "deref": size}
    # Body-evidence promotion: scalar-typed but dereferenced as struct.
    body_size = infer_struct_size_strict(body, arg_name)
    if body_size > 0:
        return {"kind": "pointer", "type": t + "*", "deref": body_size,
                "promoted": True}
    if base in SCALAR_TYPES:
        return {"kind": "scalar", "type": t}
    # Unknown type — treat as pointer (safer).
    return {"kind": "pointer", "type": t, "deref": DEFAULT_DEREF}


def infer_struct_size_strict(body: str, arg_name: str) -> int:
    """Like infer_struct_size but returns 0 (not default) when no
    deref evidence found — used for the body-evidence promotion."""
    reach = 0
    for m in BODY_OFFSET_RE.finditer(body):
        if m.group("arg") != arg_name:
            continue
        off = int(m.group("off"), 16)
        sz = TYPE_SIZE.get(m.group("dtype").lower(), 4)
        reach = max(reach, off + sz)
    for m in ARRAY_RE.finditer(body):
        if m.group("arg") != arg_name:
            continue
        idx = int(m.group("idx"))
        reach = max(reach, idx * 4 + 4)
    return min(reach, MAX_DEREF) if reach else 0


def infer_struct_size(body: str, arg_name: str) -> int:
    """Scan function body for `*(type*)(arg_name + 0xN)` and return
    max(N + sizeof(type)). Capped at MAX_DEREF, fallback DEFAULT_DEREF."""
    reach = 0
    for m in BODY_OFFSET_RE.finditer(body):
        if m.group("arg") != arg_name:
            continue
        off = int(m.group("off"), 16)
        sz = TYPE_SIZE.get(m.group("dtype").lower(), 4)
        reach = max(reach, off + sz)
    for m in ARRAY_RE.finditer(body):
        if m.group("arg") != arg_name:
            continue
        idx = int(m.group("idx"))
        # assume 4-byte stride (most common)
        reach = max(reach, idx * 4 + 4)
    if reach == 0:
        return DEFAULT_DEREF
    return min(reach, MAX_DEREF)


def parse_module(path: Path) -> dict:
    """Parse one decomp_all_<module>.c, return {func_name: spec_dict}."""
    text = path.read_text(encoding="utf-8", errors="replace")
    # Split by function header.
    blocks = []
    last_end = 0
    last_header = None
    for m in FUNC_HEADER_RE.finditer(text):
        if last_header is not None:
            blocks.append((last_header, text[last_end:m.start()]))
        last_header = m
        last_end = m.end()
    if last_header is not None:
        blocks.append((last_header, text[last_end:]))

    out = {}
    for header_match, body in blocks:
        name = header_match.group("name")
        addr = "0x" + header_match.group("addr").lstrip("0").rjust(8, "0")

        # Find signature — may span multiple lines (Ghidra often puts
        # return type on its own line, then `name(args)` on the next).
        # Strategy: collect non-comment lines into a buffer until we hit `{`
        # or a balanced `)`, then try to match the joined buffer.
        sig_match = None
        buf = []
        for line in body.splitlines()[:30]:
            line_s = line.strip()
            if not line_s or line_s.startswith(("/*", "//", "*")):
                continue
            if line_s.startswith("{"):
                break
            buf.append(line_s)
            joined = " ".join(buf)
            if "(" in joined and joined.count("(") == joined.count(")") and name in joined:
                m = SIG_RE.match(joined)
                if m and m.group("name") == name:
                    sig_match = m
                    break
        if sig_match is None:
            continue

        args_raw = sig_match.group("args").strip()
        arg_specs = []
        if args_raw and args_raw != "void":
            for arg_raw in args_raw.split(","):
                arg_raw = arg_raw.strip()
                if not arg_raw:
                    continue
                m = ARG_RE.match(arg_raw)
                if not m:
                    # Pointer-to-array or other weird; skip with placeholder.
                    arg_specs.append({"kind": "unknown", "raw": arg_raw})
                    continue
                spec = classify_arg(m.group("type"), body, m.group("name"))
                spec["name"] = m.group("name")
                arg_specs.append(spec)
        out[name] = {
            "addr": addr,
            "ret":  sig_match.group("ret").strip(),
            "args": arg_specs[:4],   # only first 4 = r0..r3
        }
    return out


def main():
    decomp_files = sorted(FINDINGS.glob("decomp_all_*.c"))
    if not decomp_files:
        sys.exit(f"no decomp files in {FINDINGS}")

    result = {}
    total = 0
    for path in decomp_files:
        mod_name = path.stem[len("decomp_all_"):]
        funcs = parse_module(path)
        result[mod_name] = funcs
        total += len(funcs)
        print(f"  {mod_name}: {len(funcs)} signatures")
    print(f"\nTotal: {total} signatures across {len(decomp_files)} modules")

    OUT.write_text(json.dumps(result, indent=2))
    sz = OUT.stat().st_size
    print(f"Wrote {OUT}  ({sz:,} bytes)")


if __name__ == "__main__":
    main()
