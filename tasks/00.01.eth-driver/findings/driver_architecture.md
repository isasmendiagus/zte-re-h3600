# zx279128-eth driver — current architecture overview

State as of refactor #38 Phase 18 (commit 8ea52743f, 2026-05-26).

This doc describes what the driver currently looks like so a reviewer
(or returning developer) can navigate the 3.6 kLOC file without having
to re-read every line.

## High-level shape

```
┌─────────────── mainline 6.6 ─────────────────┐
│                                              │
│  drivers/net/mdio/mdio-zte.c   (Phase 11)    │  ←  hardware MDIO
│  drivers/net/phy/phy-zte-gephy.c (Phase 13)  │  ←  4 GePHY drivers
│  drivers/net/ethernet/zte/zx279128-eth.c     │  ←  this file
│                                              │
└──────────────────────────────────────────────┘
```

`zx279128-eth.c` is currently **monolithic** — it owns the on-chip
switch, PP (Packet Processor), NPP, TM (Traffic Manager), IDM (CPU
DMA ring), and BMU. Phase 15-onward of refactor #38 is moving the
clearly-separable HW blocks out into their own drivers; today only
the MDIO and PHY are split. The DSA-style split into per-block
drivers is planned but not started.

## File layout — top-to-bottom (approximate line ranges)

| Range | Section | Purpose |
| --- | --- | --- |
| 1–80 | License / includes / file banner | — |
| 80–250 | Macros, register-offset #defines | TM/PP/IDM/BMU register map constants |
| 250–700 | SBRAG (CPU SBRAG bus) helpers | indirect-access wrappers for the SBRAG block — used for FDB programming |
| 700–950 | Static const stock-init data | pulled in from generated headers (zx_stock_bursts.h, zx_npp_twin_data.h, zx_pm_table.h, zx_cla_table.h, etc.) |
| 950–1100 | Block init helpers | zx_pon_low_init / zx_pon_tail_lookup_init / zx_npp_aux_init / zx_npp_twin_init / zx_tm_per_instance_init / zx_stock_apply_block |
| 1100–1700 | PP (Packet Processor) init | bridge-side init, PP_BRG ram, CPU forwarding, port isolation |
| 1700–2050 | pp_pm RAM / CLA / trap_queue | classifier ACL, per-protocol CPU queue routing, MAC->slot tables |
| 2050–2400 | TM (Traffic Manager) | DMA setup, BMU buffer pool init, queue / RED config |
| 2400–2700 | NAPI / RX path | zx_tm_napi_poll, per-queue descriptor walk, BMU recycle |
| 2700–3050 | TX path | zx_sw_xmit, BMU alloc, queue kick |
| 3050–3180 | IDM netdev (idm0/idm1) | wifi-conduit interfaces, registration |
| 3180–3260 | per-port helpers | zx_eth_probe_port |
| 3264–3577 | zx_eth_probe + supporting | the big probe — DMA mask, resource map, stock replays, FDB seed, netdev register, IRQ wire-up |
| 3577– end | zx_eth_remove, of_device_id, module init | — |

## Boot-time call graph

`zx_eth_probe()` runs in this order:

1. **Resource setup** — read `reg-names = "pon", "npp"` MMIO windows, alloc DMA pools (bppe, bp, rxdesc).
2. **TOPCRM clock enable** — flip a handful of bits in the SoC clock-mux syscon so PON-side clocks are gated on. Hardcoded ioremap of 0x94000000; the DT phandle `zte,topcrm = <&topcrm>` is published for Phase 10b but not yet consumed.
3. **Stock-init replay (per-block)** —
   - `zx_pon_low_init`     — 4 PON-LOW sub-blocks × 4 writes each
   - `zx_stock_apply_block("PON_B", …)`  — 1792 still-anonymous singletons
   - `zx_pon_tail_lookup_init` — 16 KB lookup-RAM init: 4080×0x4bef + 2 footer
   - `zx_stock_apply_block("PON_TAIL", …)` — remaining ~6 k writes
   - `zx_stock_apply_block("NPP", …)`     — the 96-write tail not in twin pairs
   - `zx_npp_twin_init`     — 752 unique writes replayed to 2 sub-blocks each
   - `zx_npp_aux_init`      — 13 × 12 identical writes (clean loop)
   - `zx_tm_per_instance_init` — 16 instances × (7 common control regs + 64-word per-instance table)
   - `zx_stock_apply_block("TM", …)`  — the rest of TM
   - `zx_stock_apply_block("PP_FUC", …)` — packet-processor function table
4. **PHY power-up** — `zx_eth_init_phys()` walks `zte,gephys = <&gephy0…>` phandles and calls `phy_init_hw()` on each, which runs the phy-zte-gephy `config_init` (LDO + TX DAC enable).
5. **PP / VLAN / port-isolation** — explicit C, mostly verbatim from the stock dump.
6. **TM setup** — BMU pool, DMA ring, IRQ wire-up, NAPI register.
7. **CLA / trap_queue / pro_action / pp_pm replays** — final round of replays for the classifier and trap routing.
8. **Netdev register** — eth0 (the "sw" CPU port) + idm0/idm1 (wifi conduit).
9. **TM IRQ enable** — wakes the rest of the stack.

## Generated headers and their owners

| Header | Generator script | What it holds |
| --- | --- | --- |
| zx_stock_table.h     | gen_stock_table.py     | 22363-entry (off,val) replay table from stock.bin |
| zx_stock_bursts.h    | gen_stock_bursts.py    | same, but factored into burst/single ops with per-block skip ranges |
| zx_npp_twin_data.h   | gen_npp_twin_data.py   | 3 pairs of bit-identical NPP sub-block init |
| zx_cla_table.h       | gen_cla_table.py       | 780-entry CLA replay |
| zx_pm_table.h        | gen_pm_table.py        | 1025-entry pp_pm replay |
| zx-fpga-reg-tables.h | (manually curated)     | 651 descriptors mapping (fpga_word → table/reg_id/mask/shift) |
| zx_reg_tables.h      | (legacy, kept for now) | a smaller older descriptor set |

## What's still anonymous

Out of the 22363 stock writes, **15469 entries (69 %) are still
inside `zx_stock_apply_block`** — they're applied via the generic
burst/single walker without per-write naming. Breakdown:

| Block | Remaining ops | Why hard to name |
| --- | --- | --- |
| PON_B | 1792 singletons | every write hits a different control reg; the descriptor table doesn't cover the smac/sbrg/dpa side. Needs decomp + kotrace of stock PON kmods. |
| PON_TAIL | ~7 k mixed | most after 9e are RAM-table fills for FDB/ACL TCAM that don't map to single descriptor regs. |
| NPP | 96 (instance 10) | last NPP sub-block, no twin to pair against. |
| TM | ~3 k mixed | between the 16-instance tables (9d) and the 16 per-instance common regs (9g) — the scattered remainder. |
| PP_FUC | 2450 mixed | per-port varied config — no clean pattern collapse. |

## Hand-written init helpers (extracted blocks)

All in zx279128-eth.c, called from `zx_eth_probe`:

  zx_pon_low_init             — 4 sub-blocks × 4 writes, stride 0x10000
  zx_pon_tail_lookup_init     — 4080 same-value writes + 2 footer words
  zx_npp_aux_init             — 13 instances × 12 writes, stride 0x4000
  zx_npp_twin_init            — 3 bit-identical sub-block pairs at stride 0x2000
  zx_tm_per_instance_init     — 16 instances × (7 control regs + 64-word table)
  zx_stock_apply_block(name, start, end) — the generic walker

## Pending refactor work (post Phase 18)

| Task # | Phase | Target |
| --- | --- | --- |
| #71 | 10b | Driver reads pon + topcrm from DT instead of hardcoded devm_ioremap. |
| —   | —   | DSA conversion: split switch + per-port netdevs (multi-week). |
| —   | —   | More descriptor-driven naming of PON-side regs (needs PON-side .ko decomp). |
| —   | —   | Cover letter + RFC submission to netdev. |

## Verification gate

Every refactor commit must boot the device and produce:
  - `mdio-zte 9a101000.mdio: ZTE MDIO bus registered`
  - 4× `ZTE ZXIC ZX279128S GePHY mdio-…: ZTE GePHY bound`
  - 4× `… config_init (LDO arm + TX DAC drive enable)` (from phy_init_hw)
  - `ZX279128S ethernet ready (IRQ=…, base=…)`
  - No `Unable to handle kernel paging request`, no `Oops`.

Skip ping bidi as part of the refactor gate — it's a pre-existing
issue separate from this refactor track.
