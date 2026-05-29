# Working commit 2ad931ed8 vs current — FLOOD / forwarding diff (CPU→LAN egress gate)

**Date:** 2026-05-28 · **Type:** git/code archaeology, no code change
**Goal:** Find the flood/forwarding/FDB/isolation config that let a CPU-sourced
frame get an egress port at `2ad931ed8` (on-wire-verified, flooded, ~60% loss +
DUPs) but does NOT in the current `zx-eth-main.c` (frame reaches QMG sw_fwd
0x9234c044 but SOPC send2smac2 0x921d9164 and MAC2 TX 0x92280718 stay 0).

Sources:
- OLD: `git show 2ad931ed8:linux-v6.6/.../zx279128-eth.c` (dumped /tmp/old_zx279128-eth.c)
- CUR: `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`
- stock-live: `tasks/00.10.02.re-stock-kmods/findings/regs/stock_eth_2mib.txt`

## Conclusion (one line)

The egress at `2ad931ed8` was **forced switch flooding** driven by
`zx_pp_brg_init()` writing NON-stock flood values to the PP_BRG block (phys
`0x92388xxx`). Refactor #38's "DUP fix" rewrote that same function to the
**stock-live** (CPU-only) values, which removes every flood destination for a
CPU frame with an unknown DA → switch drops it → SOPC send2smac2 never fires.
The bulk stock replay (`zx_stock_bursts.h`) is **NOT** involved — it makes
**zero** writes to `0x92388xxx` (verified: `grep -c 0x92388` = 0).

## Probe ordering — who writes the flood gates last (identical in OLD & CUR)

1. `zx_pp_init()` writes PP_BRG 0x8300=0xFF, 0x8304=0xFF, isolate 0x83c0..dc (stock).
2. `zx_eth_apply_stock_init()` bulk replay — touches NO 0x92388xxx reg.
3. `zx_eth_init_vlan_and_isolation()` → `zx_port_isolate()`.
4. `zx_eth_init_tm_subsystem()` → **`zx_pp_brg_init()`** = LAST writer of the
   flood gates. This is the divergence point.

So the live-on-HW flood config is entirely whatever `zx_pp_brg_init()` writes.

## The diff (`zx_pp_brg_init`, pp = fpga_base + 0x380000, phys 0x92388000)

| Reg phys | field | OLD 2ad931ed8 (egress WORKED) | CUR (no egress) | stock-live |
|---|---|---|---|---|
| 0x92388300 | brdcst_fld_en | **0x0000ffff** (ON) | 0x00000000 (OFF) | 0 |
| 0x92388304 | brdcst_fwd portmask | **0x020000ff** (ON) | 0x00000000 (OFF) | 0 |
| 0x92388340 | unk-unicast pktdeal[23:8]+FWD bitmap[31:24] | **0xff5555ff** (FWD=0xff, all 8 ports) | 0x015555ff (FWD=0x01, CPU only) | 015555ff |
| 0x92388344 | unk-unicast flood portmask | **0x0000001e** (ports 1-4) | 0x00000000 (OFF) | 0 |
| 0x92388380 | pt_tls | **0x0000001f** | 0x00000001 (CPU only) | 1 |
| 0x92388004 | bridge ctrl (MAC aging FSM) | 0x020000ff (aging OFF) | 0x040200ff (aging+exchange ON) | 040200ff |
| 0x92388188 | aging-cycle blob | 0x0013f434 | 0x00211b00 | 00211b00 |

OLD code: /tmp/old_zx279128-eth.c lines 1621-1637 + zx_pp_init L652-653 (0x300/0x304=0xff).
CUR code: zx-eth-main.c L2369-2406 (zx_pp_brg_init) + L1178-1179 (zx_pp_init 0x300/0x304=0xff, later clobbered to 0).

## Why this gates SOPC send2smac2

A CPU TX frame whose DA is not FDB-resolved to a LAN port is an **unknown
unicast** (or broadcast for ARP). Its only egress route is the SBRG flood
fabric:
- `0x8340[31:24]` = unknown-unicast **FWD bitmap**, one bit per port.
- `0x8300/0x8304` = broadcast flood enable/portmask.

At `2ad931ed8` the FWD bitmap = **0xff** (flood to ALL ports incl. LAN MACs) and
broadcast flood = 0xffff/0xff. The switch therefore replicated the CPU frame to
the LAN port → SOPC send2smac2 fired → MAC2 TX → wire (the DUPs/60% loss were
the flood amplification). The current driver narrowed the FWD bitmap to **0x01**
(internal/CPU port only) and zeroed broadcast flood, matching stock — so the
unknown-DA CPU frame has **no LAN egress bit set**: it advances to QMG sw_fwd but
the sw_fwd decision yields an empty/CPU-only egress port-set, so send2smac2 to
the LAN MAC is never issued.

Stock genuinely runs with 0x8340=0x015555ff (verified). Stock does NOT egress
CPU frames by flooding — it resolves the DA via the FDB to a real LAN port. The
mainline driver has not reproduced that FDB-resolved CPU-TX path, so the only
thing that ever produced on-wire egress was the working commit's brute-force
flood-to-all.

Q1 answer: yes — the current driver's flood "fixes" (0x8340 FWD→CPU-only,
0x8300/0x8304→0, pt_tls→CPU-only) directly removed the flooding 2ad931ed8 relied on.
Q2 answer: no — the bulk replay does not write any 0x92388xxx flood reg (0 writes);
the regression is 100% in `zx_pp_brg_init`'s hand-coded values, not the replay.
Q3: see poke test below.

## First poke-test (make SOPC send2smac2 fire) — single register

Reg: **PP_BRG `0x8340`, phys `0x92388340`** (in poke range [0x921c0000,0x923c0000)).
Set the unknown-unicast FWD bitmap (bits 31:24) from 0x01 to 0xff, keeping the
pktdeal field:

```
poke 0x92388340 = 0xff5555ff      # was 0x015555ff
```

Then TX one frame via `txtest`/zx_sw_xmit and watch SOPC send2smac2 (0x921d9164)
and MAC2 TX (0x92280718) increment. This is the single highest-probability gate.

If 0x8340 alone is insufficient (broadcast/ARP still dropped), add the two
broadcast-flood gates to restore the full 2ad931ed8 flood state:

```
poke 0x92388300 = 0x0000ffff      # brdcst_fld_en  (was 0)
poke 0x92388304 = 0x020000ff      # brdcst_fwd portmask (was 0)
poke 0x92388344 = 0x0000001e      # unk-unicast flood portmask (was 0)
```

Order of confidence: 0x8340 first (unicast egress / ICMP-reply path), then
0x8300+0x8304 (ARP/broadcast). These four writes are exactly the OLD
`zx_pp_brg_init` values minus the aging-FSM change at 0x8004 — leave 0x8004 at
the current 0x040200ff initially (aging ON is harmless to the flood test and
keeping it isolates the variable to the flood bitmaps).

To make permanent: in `zx_pp_brg_init()` (zx-eth-main.c ~L2376/L2385/L2403/L2404)
revert 0x8340→0xff5555ff, 0x8344→0x0000001e, 0x8300→0x0000ffff,
0x8304→0x020000ff. This re-creates the on-wire-verified flood egress (accepting
the DUPs) and decouples egress from the (still-unreproduced) FDB-resolved path.
