# rx_path_dead

**Status**: wip
**Owner**: -
**Started**: 2026-04 (approximate)
**Task IDs**: #91, #92, #93
**Updated**: 2026-05-22

## Question

Mainline `zx279128-eth` driver: why is RX path completely dead?
`tm_irq_count = 0`, `rx_packets = 0`, per-queue RX desc rings never populated.
TM hardware never fires an RX interrupt despite link up + traffic on wire.

## Why we care

RX dead → driver can't carry traffic → no ping → blocks stage 3 (sustained
LAN↔device ping) → blocks stage 4 (NAND-persist mainline) → blocks
stage 5 (OpenWrt port — the actual goal).

This is **the single biggest blocker** on the eth-driver.

## Hypotheses (most likely first)

1. **`chip_tm_init` not ported.** Stock `switch.ko` calls a function
   `chip_tm_init` during init that touches multiple TM registers we
   never write. Believed to set up the TM→PP forwarding gate that lets
   RX packets reach the CPU descriptor ring. **Strongest hypothesis.**
   Evidence: task #87 confirmed missing in mainline; stock register
   dump shows TM writes mainline driver doesn't replay.
2. **`pp[0x2c]` `CPU_FWD` bit 25 auto-clears.** We've seen this bit
   self-clear ~200 ms after we set it. Suggests another gate or a
   counter elsewhere is unsatisfied. May be a symptom of #1.
3. **`def_ptl_pkt_action` table not replayed.** We replay several tables
   (pp_pm, CLA) but not this one. Stock has 256-entry default action map.
4. **`SchRegTable` / `QmgRegTable` decoding wrong.** We brute-replay raw
   register dumps but may be writing in wrong order or missing barriers.

## What I've tried

| Date       | Experiment | Result | Note |
|------------|-----------|--------|------|
| ~2026-04   | Replay 22,363 stock regs verbatim | TX partial works, RX still 0 | suggests RX init needs ordered runtime calls, not just static replay |
| ~2026-04   | Mine stock sysfs (`/proc/zte/sys/...`) for HW state diff | Found ~30 register diffs vs ours | task #66, #75 |
| ~2026-04   | Fix TM IRQ_MASK semantics (1=masked, inverted) | IRQ now unmasked but still no fire | task #62 |
| ~2026-04   | Set TM[0xF0] = RX desc base per PonTmRegTable[4] | desc base set, still no IRQ | task #68 |
| ~2026-04   | Apply TM 4-instance replication fix | TM regs now match stock | task #96 |
| ~2026-04   | Force-set `pp[0x2c]` bit 25 (CPU_FWD) | bit auto-clears ~200 ms later | open: why? |
| 2026-05    | Implement `zx_sw_xmit` (TX baseline) | Some TX works, RX still 0 | task #88 |

## Open sub-questions

- [ ] (#87) Port `chip_tm_init` — RE the function in stock switch.ko, then port
- [ ] (#89) RE + port `zte_api_pp_global_init` + `cpu_queue_rate`
- [ ] (#90) Dump `def_ptl_pkt_map` + `def_ptl_pkt_action` tables + replay
- [ ] (#91) Decode SchRegTable / QmgRegTable → find TM→PP gate
- [ ] (#92) Investigate `pp[0x2c]` CPU_FWD bit 25 auto-clear
- [ ] (#93) Extract `def_ptl_pkt_action` table + implement `pro_action` replay

## Next concrete step

The methodology to use now (blocked on tooling step 2 of `ROADMAP.md`):

1. Splice `printk("[STOCK] chip_tm_init entry r0=%lx r1=%lx\n", r0, r1);`
   into stock `switch.ko` at `chip_tm_init` entry.
2. Add more `printk`s at every register-write call site inside the function.
3. Push patched .ko to device, rmmod/insmod, watch `kmsg2uart` UART output
   during normal stock boot.
4. Compare register writes vs what our mainline driver does. Port the missing.

Iter cost: ~30 s per .ko patch (see `docs/ITERATE.md` Loop B).

## References

- `tasks/00.01.eth-driver/ETHERNET_DRIVER_DESIGN.md` — exhaustive driver design notes
- `tasks/00.01.eth-driver/captures/` — stock-side register dumps + sysfs snapshots
- `ext/rootfs/kmodule/switch.ko` — stock binary to RE
- Ghidra project: see `ghidra/` (specifics in `tasks/00.01.eth-driver/README.md`)
- Related: [[research/cpu_fwd_bit25]] (sibling — bit 25 auto-clear),
  [[research/def_ptl_pkt_action]] (sibling — missing replay)
