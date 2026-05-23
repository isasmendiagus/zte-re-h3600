# research/ — live investigations

One file per open question. Created when an investigation starts,
**updated as you go** (don't accumulate notes elsewhere), promoted to
`../findings/` when the question is answered.

## Template

```markdown
# <topic>

**Status**: open | wip | answered | stalled
**Owner**: <agent name / human / last toucher>
**Started**: <YYYY-MM-DD>
**Task IDs**: #87, #91 (in main TaskList — keep in sync)
**Updated**: <YYYY-MM-DD> on each non-trivial finding

## Question

What we're trying to find out, in one sentence.
"Why is RX desc ring empty after `ifconfig eth0 up` in mainline?"

## Why we care

The bigger goal this unblocks. One paragraph max.
"RX dead → no ping → no OpenWrt port. Believed gated by chip_tm_init
which isn't ported."

## Hypotheses (most likely first)

1. **<short name>**: <one-line description>. Evidence for: X. Against: Y.
2. ...

## What I've tried

| Date       | Experiment                              | Result | Note |
|------------|-----------------------------------------|--------|------|
| 2026-05-19 | Replay TM[0xF0] with stock value 0x...  | rx=0   | desc base set, no IRQ |
| 2026-05-20 | Force-set CPU_FWD bit 25 in pp[0x2c]    | bit auto-clears in 200ms | new question |

Be terse. One row per experiment. Link to commit / driver function if useful.

## Open sub-questions (children to spawn)

- [ ] Why does `pp[0x2c]` bit 25 auto-clear?
- [ ] Does stock set bit 25 explicitly, or relies on default?

## Next concrete step

What the NEXT person picking this up should do.
"Splice a printk into stock switch.ko at +0x12a4 (chip_tm_init entry) +
+0x1320 (TM[0xF0] write) and capture stock-side values during normal boot."

## References

- Ghidra: switch.ko @ 0x00012a40 (chip_tm_init)
- Stock dump: ext/stock_regs_dump.csv line 14387
- Related: [[research/cpu_fwd_bit25]], [[research/tm_rx_ack]]
```

## File naming

`<short-slug>.md` — e.g. `rx_path_dead.md`, `cpu_fwd_bit25.md`,
`def_ptl_pkt_action_table.md`. Match what you'd grep for.

## Lifecycle

1. **open**: question framed, no experiments yet. Lives here.
2. **wip**: actively iterating. Lives here, updated frequently.
3. **answered**: question conclusively answered. **Move to `../findings/`**
   and add a one-line entry in `LEARNED.md` (if generally useful) or
   `tasks/00.01.eth-driver/ETHERNET_DRIVER_DESIGN.md` (if driver-specific).
4. **stalled**: hit a wall, parking. Stays here with reason at top.

## How this fits with TaskList

Each research thread typically has a matching TaskList entry (e.g. #91
"Decode SchRegTable / QmgRegTable"). The research file is **the detail**;
the TaskList is **the index**. Keep both in sync:
- New thread → new TaskCreate.
- Thread answered → TaskUpdate to completed + move research → findings.
