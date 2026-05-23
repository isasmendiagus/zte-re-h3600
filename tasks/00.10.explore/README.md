# explore — discovery / RE / archaeology tasks (umbrella)

**ID**: 00.10
**Parent**: [00 openwrt-port](../00.openwrt-port/)
**Children**: [00.10.01 re-vmlinux](../00.10.01.re-vmlinux/), [00.10.02 re-stock-kmods](../00.10.02.re-stock-kmods/), [00.10.03 re-uboot](../00.10.03.re-uboot/), [00.10.04 mainline-archaeology](../00.10.04.mainline-archaeology/)
**TaskList items**: none directly (per-child tasks own theirs)
**Status**: 🔬 ACTIVE — knowledge accumulators; grow over time.

## What goes here

Tasks whose deliverable is **learning**, not implementation. They produce
findings, annotated binaries, archaeology reports — never a working
daemon or a driver.

Two flavors:

### Knowledge bases (`re-*`)
Long-lived RE projects centered on a specific binary. Own the Ghidra
project for that binary + a `findings/` folder of stable discoveries.
Multiple consumer tasks reference them.

### Archaeology / surveys (no prefix)
One-shot research efforts that produce a written report. Once published
they're append-only references.

## Rules of engagement (apply to every child)

These rules are LIFTED OUT here so children don't repeat them.

### For knowledge-base RE tasks (`re-*`)

The Ghidra projects under these tasks are **shared infrastructure**.
Annotations you make affect every future consumer.

| OK ✅ | Avoid ❌ |
|---|---|
| Add comments / labels / bookmarks | Mass-renaming existing functions ("better name" is subjective) |
| Define new structs | Restructuring existing struct definitions |
| Add function signatures from RE | Deleting existing types |
| Add data types from disassembly | Speculative renames you haven't verified |

**If you need destructive experiments** (try renaming an entire
subsystem to see if it clarifies the call graph) → **copy the `.rep/`
into your consumer task's local `ghidra/` and experiment there**. Don't
pollute the shared project.

### Findings flow

Stable discoveries get promoted to text in the RE task's `findings/`:

```
1. You're in your consumer task (e.g. 00.01.eth-driver), iterating
2. You discover something in stock vmlinux (e.g. chip_tm_init signature)
3. Write a quick note in 00.01.eth-driver/research/<topic>.md (working hypothesis)
4. Once verified and stable: PROMOTE to 00.10.01.re-vmlinux/findings/<topic>.md
5. Cross-link from your consumer task's README
```

The Ghidra annotations are the live state; the `findings/` markdown is
the durable record.

### Findings doc template

```markdown
# <topic>

**Where**: <function name> @ <address> in <binary>
**Verified by**: <which iter / which experiment confirmed this>
**Discovered during**: <which task's work led here>
**Consumed by**: <which tasks benefit from knowing this>

## TL;DR

<one-paragraph statement of the finding>

## Details

<the actual content — disassembly snippet, struct layout, control flow,
whatever the finding is>

## How to verify

<exact reproduction steps so the next person can confirm>

## Open questions

<things this finding raises but doesn't answer>
```

## When does an exploration spawn a new task here?

- ≥2 consumers need the same RE → promote to `00.10.NN.re-<binary>/`
- A piece of one-shot research produces a substantial document → file it as `00.10.NN.<topic>/`
- A consumer task's `research/` folder accumulates 3+ files about the same external binary → that's a signal a knowledge-base task wants to exist

When NOT to spawn a new explore task:

- One-off RE of a binary nobody else will look at — keep task-local (like `00.05.01.rop-no-uart/`)
- "I might want to RE this someday" — wait until you actually do
- A finding belongs to a single consumer task — keep it in that task's `research/`

## See also

- `CLAUDE.md` "Ghidra project ownership" — the promotion rule in detail
- `docs/KERNELS.md` — which binaries each RE task analyzes
- `ghidra/README.md` (top-level) — the shared dump_*.py scripts that operate on these projects
