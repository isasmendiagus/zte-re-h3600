# re-vmlinux — knowledge base for the stock H3600 vmlinux

**ID**: 00.10.01
**Parent**: [00.10 explore](../00.10.explore/)
**Children**: none
**TaskList items**: none directly (consumers own their tasks)
**Consumed by**: [00.01 eth-driver](../00.01.eth-driver/), [00.02 stock-shell](../00.02.stock-shell/), and any future task that touches stock-kernel internals
**Status**: 🧠 KNOWLEDGE BASE — append-only; grows as findings get promoted from consumer tasks.

## What's here

This task **owns the Ghidra analysis** of the stock 4.1.25 vmlinux that
ships in the H3600's slot A. It is a shared knowledge base that multiple
consumer tasks reference.

```
./ghidra/h3600_vmlinux.gpr      ← open this in Ghidra
./ghidra/h3600_vmlinux.rep/     ← project data (~30 MB ELF + ~100 MB analyzed state)
./findings/                     ← markdown notes promoted from consumer tasks
```

## What the binary is

- File: `ext/extracted/vmlinux.bin` — extracted from NAND once (golden source)
- Version: Linux 4.1.25 (per `strings vmlinux.bin | grep '^Linux version'`)
- Arch: ARM 32-bit, soft-float, little-endian
- Loaded base in Ghidra: `0xc0008000` (standard ARM kernel base)
- See `docs/KERNELS.md` "kernel #2" for full context

## Rules of engagement (read before editing the Ghidra project)

This project is **shared infrastructure**. Annotations you make affect
every future consumer.

| OK ✅ | Avoid ❌ |
|---|---|
| Add comments / labels | Mass-renaming existing functions ("better name" subjective) |
| Add bookmarks ("looked at this") | Restructuring existing struct definitions |
| Define new structs | Deleting existing types |
| Add function signatures from RE | Speculative renames you haven't verified |
| Add data types from disassembly | Anything you'd later undo |

**If you need destructive experiments** (try renaming an entire subsystem
to see if it clarifies the call graph) → copy the `.rep/` into your
consumer task's `ghidra/` and experiment there. Don't pollute this one.

## How to add findings

When you discover something stable enough to last beyond one session:

1. Write a markdown doc at `findings/<short-slug>.md`
2. Lead with: what you found, where (which function + address), how you
   verified, what consumer tasks would benefit
3. Link to the function in Ghidra by address (the gold-standard reference)
4. Update your consumer task's README to cross-link the new finding

See `findings/README.md` for the template.

## Currently known findings

(populated as discoveries land here; today this is empty — pre-existing
findings still live in consumer tasks' `research/` notes)

## See also

- `docs/KERNELS.md` "kernel #2 — Stock kernel" — full binary context
- `ghidra/README.md` (top-level) — the shared dump_*.py tooling that operates on this project
- Sibling RE tasks: [00.11 re-stock-kmods](../00.11.re-stock-kmods/), [00.12 re-uboot](../00.12.re-uboot/)
