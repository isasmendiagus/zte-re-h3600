#!/usr/bin/env python3
"""Resolve kotrace_dump entries: func_addr -> symbol name.

Reads:
  - /tmp/uart_bridge.log  for the most-recent "[ko: target NAME @ 0xADDR]"
    lines (built when kotrace patches modules at insmod time).
  - A kotrace_dump.txt produced by `cat /proc/kotrace_dump`.

Emits one line per entry:
    <seq> <marker> <symbol|addr> r0=... r1=... r2=... r3=...
"""
import re
import sys
from pathlib import Path


def build_addr_map(uart_log: Path) -> dict:
    data = uart_log.read_bytes().decode("utf-8", "replace")
    # Use the LAST "kotrace loaded" line as anchor — handles multi-insmod log
    anchor = data.rfind("[ko: kotrace loaded]")
    if anchor < 0:
        anchor = 0
    sub = data[anchor:]
    m = {}
    for hit in re.finditer(r"\[ko: target (\S+) @ 0x([0-9a-f]+)\]", sub):
        m[int(hit.group(2), 16)] = hit.group(1)
    return m


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <kotrace_dump.txt> [uart_log]", file=sys.stderr)
        sys.exit(2)
    dump_path = Path(sys.argv[1])
    uart_path = Path(sys.argv[2]) if len(sys.argv) > 2 else Path("/tmp/uart_bridge.log")

    addr_map = build_addr_map(uart_path)
    print(f"# {len(addr_map)} symbols resolved from {uart_path}", file=sys.stderr)

    for line in dump_path.read_text().splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            print(line)
            continue
        # New format: "<seq> <marker> <func_addr> <r0> <r1> <r2> <r3>"
        parts = line.split()
        if len(parts) < 7:
            # Old format: "<seq> <marker> <r0> <r1> <r2> <r3>"
            print(line)
            continue
        seq, marker, fn_hex, r0, r1, r2, r3 = parts[:7]
        fn_addr = int(fn_hex, 16)
        sym = addr_map.get(fn_addr, f"0x{fn_addr:08x}")
        print(f"{seq:>6} {marker} {sym:<40s} r0={r0} r1={r1} r2={r2} r3={r3}")


if __name__ == "__main__":
    main()
