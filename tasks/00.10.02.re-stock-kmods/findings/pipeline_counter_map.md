# Pipeline counter register map — CPU→LAN egress (downstream) path

Goal: give `zx_pipeline_stats_show` (zx-eth-main.c) a `readl()` for every
per-stage counter stock prints, so one `cat pipeline_stats` shows where a
CPU-sourced frame dies in the egress pipeline.

## Addressing model (READ THIS FIRST)

Stock reads every counter via `fpga_read_reg(id)` where (per
`stock_runtime_visibility_2026-05-27.md` + `smac_real_counters_re.md`):

```
phys = 0x92000000 + id * 4          # id is a DWORD index from pon_base
```

The mainline driver maps `e->base = 0x921c0000` (the NPP unified window).
So to call `readl(e->base + OFF)`:

```
OFF (e->base relative) = phys - 0x921c0000 = id*4 - 0x1c0000
```

All offsets below are the **e->base-relative byte offset** ready to drop
into `readl(e->base + OFF)`. The driver's named windows confirm the bands:
`TM_OFF=0x180000` (TM), `PP_OFF=0x1c0000` (PP), MAC[i] at `(i+1)*0x40000`.

Source function for the whole downstream block:
`decomp_all_tm.c:46455 tm_dn_statistics_get @ 0x52e50` (printk strings at
46596-46658). Upstream counterpart: `tm_up_statistics_get @ 0x523e4`
(46130). All reads are plain free-running 32-bit counters unless a
shift/mask is noted (decomp does `(raw >> sh) & mask`).

---

## EGRESS PATH IN PIPELINE ORDER (CPU → wire)

A frame travels: CPU/IDM → QMG (queue mgr) → RED → DSCH (downstream
scheduler) → SOPC (hands to physical MAC) → SMAC[N] (MAC TX → wire).
Counters listed in that flow order. "alive at N, zero at N+1" = the gate.

| # | Stage | Counter | e->base OFF | fpga id | extract | Meaning | decomp cite |
|---|-------|---------|-------------|---------|---------|---------|-------------|
| 0 | QMG (TM[0xc000]) | **QMG sw fwd pkts** | `0x18c044` | 0xd3011 | raw | SW-forwarded pkts entering QMG (CPU-injected). Stock=1527. **First egress counter.** | tm.c:46575,46641 |
| 0 | QMG (TM[0xc000]) | **QMG hw fwd pkts** | `0x18c048` | 0xd3012 | raw | HW-forwarded pkts | tm.c:46576,46642 |
| 0 | QMG (TM[0xc000]) | **QMG hw trap pkts** | `0x18c04c` | 0xd3013 | raw | Pkts trapped to CPU by QMG (the hairpin path!) | tm.c:46577,46643 |
| 1 | RED (TM[0x4000]) | RED fwd in / out | `0x184204`/`0x184210` | 0xd1081/0xd1084 | raw | RED queue fwd accepted in / dequeued out | tm.c:46569-70,46638 |
| 1 | RED (TM[0x4000]) | RED trap in / out | `0x184208`/`0x184214` | 0xd1082/0xd1085 | raw | RED trap-path in / out | tm.c:46571-72,46639 |
| 1 | RED (TM[0x4000]) | RED drop in / out | `0x18420c`/`0x184218` | 0xd1083/0xd1086 | raw | RED early-drop in / out | tm.c:46573-74,46640 |
| 2 | DSCH (TM[0x14000]) | **DSCH in que pkts** | `0x194200` | 0xd5080 | `>>24` | Pkts queued into downstream scheduler | tm.c:46578-79,46644 |
| 2 | DSCH (TM[0x14000]) | **DSCH out que pkts** | `0x1941fc` | 0xd507f | `(<<16)>>24` i.e. `(raw>>8)&0xff` | Pkts dequeued from DSCH toward egress. Stock=247. | tm.c:46580-81,46645 |
| 3 | SOPC (NPP+0x19xxx) | **sopc_send2smac0** | `0x01915c` | 0x76457 | raw | Frames SOPC handed to physical MAC0 (LAN1). **Final crossbar→MAC counter.** | tm.c:46582,46646 |
| 3 | SOPC | **sopc_send2smac1** | `0x019160` | 0x76458 | raw | → MAC1 (LAN2) | tm.c:46583,46647 |
| 3 | SOPC | **sopc_send2smac2** | `0x019164` | 0x76459 | raw | → MAC2 (LAN3 = host port). Stock=462, == tcpdump. **THE counter to watch for our hairpin.** | tm.c:46584,46648 |
| 3 | SOPC | **sopc_send2smac3** | `0x019168` | 0x7645a | raw | → MAC3 (LAN4) | tm.c:46585,46649 |
| 3 | SOPC | **sopc_send2smac4** | `0x01916c` | 0x7645b | raw | → MAC4 (WAN) | tm.c:46586,46650 |
| 4 | SMAC[N] (MAC[N]) | **smacN tx_bytes** | `(N+1)*0x40000 + 0x714` | tbl 0x0f | raw | Wire-side TX bytes from MAC N | smac_real_counters_re.md tbl 0x0f; tm.c:46654 (via smac_get_statistics 0x10) |
| 4 | SMAC[N] | **smacN tx_pkts** (send total frames) | `(N+1)*0x40000 + 0x718` | tbl 0x10 | raw | Wire-side TX frames. Stock smac2=462. **dead end of egress.** | smac tbl 0x10; tm.c:46654 |

Egress drop counters (any >0 = that stage dropped the frame):

| Stage | Counter | e->base OFF | fpga id | Meaning | cite |
|-------|---------|-------------|---------|---------|------|
| PP | PP DROP cnts | `0x01a040` | 0x76810 | PP-block drops | tm.c:46587,46651 |
| RED | RED DROP cnts | `0x01a044` | 0x76811 | RED aggregate drops | tm.c:46588,46652 |
| DSCH | DSCH DROP cnts | `0x01a04c` | 0x76813 | DSCH drops | tm.c:46589,46653 |

---

## UPSTREAM-shared classifier/forwarder counters (also printed in dn block)

These sit between sipc→spa→cla→pm→dpa→brg on the way to QMG; useful to see
the CPU frame's classification before QMG. All in `tm_dn_statistics_get`.

| Stage | Counter | e->base OFF | fpga id | extract | Meaning | cite |
|-------|---------|-------------|---------|---------|---------|------|
| SIPC | cpu_short_drop / cpu_pkt_drop / sipc2cpu aful/ful dn | `0x00c004` | 0x73001 | nibble fields `(raw<<X)>>0x1c` (see code) | SIPC→CPU drop/almost-full (downstream). | tm.c:46525,46597-46600 |
| SIPC | sipc_2spa sop / eop / drop | `0x00c044` | 0x73011 | `&0xf`, `(<<24)>>28`, `(<<20)>>28` | SIPC→SPA handoff sop/eop/drop | tm.c:46532,46607-09 |
| SPA | spa_fwd/drp/cpy/trp (before vlan) | `0x0145c4` | 0x75171 | bytes: `>>24`,`(<<8)>>24`,`(<<16)>>24`,`&0xff` | SPA decision pre-VLAN-filter | tm.c:46536,46610-13 |
| SPA | spa_fwd/drp/cpy/trp (after vlan) | `0x0145c8` | 0x75172 | same byte split | SPA decision post-VLAN-filter | tm.c:46537,46614-17 |
| PP_CTRL | pp_ctrl_drop | `0x1c0098` | 0xe0026 | `&0xffff` | PP control-plane drop | tm.c:46542,46618 |
| SADM | sadm pon pass (pkt/uni/brd/multi) | `0x1c4200` | 0xe1080 | byte fields | SADM pass classification | tm.c:46544,46619 |
| SADM | sadm pon drop (pkt/uni/brd/multi) | `0x1c4228` | 0xe108a | byte fields | SADM drop classification | tm.c:46545,46621 |
| CLA | **cla fwd pkts** | `0x1cc3cc` | 0xe30f3 | `&0xffff` | Classifier forward count | tm.c:46546,46623 |
| CLA | **cla trap pkts** | `0x1cc3d0` | 0xe30f4 | `&0xffff` | Classifier trap-to-CPU count | tm.c:46548,46625 |
| CLA | **cla drop pkts** | `0x1cc3d4` | 0xe30f5 | `&0xffff` | Classifier drop count | tm.c:46550,46624 |
| CLA | cla copy pkts | `0x1cc3dc` | 0xe30f7 | raw | Classifier copy count | tm.c:46552,46626 |
| ADM | adm drop pkts | `0x1d422c` | 0xe508b | raw | ADM drop | tm.c:46553,46627 |
| PM | pm recv / send / fwd / trap | `0x1dc088`/`0x1dc080`/`0x1dc0a0` | 0xe7022/0xe7020/0xe7028 | recv `&0xffff`; send `>>16`; fwd `>>16`, trap `&0xffff` | Perf-mon recv/send/fwd/trap | tm.c:46554-60,46628-31 |
| DPA | dpa_fwd/drp/cpy/trp | `0x1d810c` | 0xe6043 | byte fields `>>24`,`(<<8)>>24`,`(<<16)>>24`,`&0xff` | Egress port-aggregation decision | tm.c:46561,46632-35 |
| BRG | brg_rx / brg_tx | `0x1c8c00` | 0xe2300 | `&0xff`, `(<<16)>>24` | Bridge rx/tx (PP_BRG @ PP+0x8c00) | tm.c:46566,46636-37 |

DROP_HPMAU / DROP_AFUL CNT (overflow back-pressure drops, all should be 0):
`dn_cpu_DROP_HPMAU` id 0x73060 (`0x00c180`), PON0 0x73067 (`0x00c19c`),
PON1 0x73068 (`0x00c1a0`); `dn_cpu_DROP_AFUL` 0x73070 (`0x00c1c0`), PON0
0x73077 (`0x00c1dc`), PON1 0x73078 (`0x00c1e0`). cite tm.c:46526-31,46601-06.

---

## SMAC[N] wire-side TX/RX/err counters (table-addressed → direct readl)

Stock reads these via `smac_get_statistics(port, statNum, &out)` →
`tmOnuRegRead(statNum, out, port, &smacRegTable)` (tm.c:21385, 35339).
The indirect math resolves to a **plain readl** because every stat entry
has `stride=0x10000 dwords (=0x40000 B)`, `mask=0xffffffff`, `shift=0`:

```
phys = 0x92000000 + (entry.off + port*0x10000)*4
     = 0x92200000 + port*0x40000 + (entry.off-0x80000)*4
e->base OFF = (port+1)*0x40000 + byte_off    # i.e. mac_off(port, byte_off)
```

Full table decoded in `smac_real_counters_re.md`. Headline + error subset:

| statNum | mac_off(port, X) | Meaning | confirmed |
|---------|------------------|---------|-----------|
| 0x0f | `+0x714` | TX total bytes | stock dump 0x21931 |
| 0x10 | `+0x718` | **TX total frames** (== sopc_send2smacN on healthy path) | stock dump 0x54d |
| 0x11 | `+0x71c` | TX good broadcast | — |
| 0x28 | `+0x780` | **RX total frames** (wire ingress) | stock dump 0x5b4 |
| 0x29 | `+0x784` | **RX total bytes** | stock dump 0xa58bb |
| 0x2d | `+0x794` | RX CRC error frames | err |
| 0x32 | `+0x7a8` | RX oversize frames | err |
| 0x3d | `+0x7d4` | RX overflow error | err |
| 0x3f | `+0x7dc` | RX watchdog err | err |

**Driver discrepancy to fix**: current `zx_pipeline_stats_show` labels
`+0x710`=tx_bytes, `+0x714`=tx_pkts, `+0x718`=tx_bc. The decoded table
(verified vs stock dump) says they are shifted by one slot:
`+0x714`=tx_bytes, `+0x718`=tx_pkts, `+0x71c`=tx_bc; `+0x710` is the
empty table-entry 0x0e (reads 0 on stock). RX `+0x780`/`+0x784` are
already correct in the driver. Re-label TX to +0x714/+0x718/+0x71c.

---

## Notes for the driver patch

- Read order to print = pipeline order above (QMG → RED → DSCH → SOPC →
  SMAC TX), then the classifier block, then drop counters. That makes the
  "alive at stage N, 0 at N+1" gate visually obvious in one `cat`.
- For the hairpin specifically: if **QMG sw fwd** increments per TX but
  **DSCH out que** / **sopc_send2smac2** / **smac2 tx_pkts** stay 0 while
  **QMG hw trap** climbs → the frame is being trapped back to CPU at QMG
  (confirms the loopback). If sopc_send2smac2 climbs but smac2 tx_pkts
  stays 0 → MAC TX is the gate. This pinpoints the exact gate stage.
- All reads are kernel-context `readl(e->base + OFF)` — same accessor the
  driver already uses; TM-gating (the fpga-from-userspace=0 problem) does
  not apply to in-driver reads (per stock_runtime_visibility findings).
- These are free-running, NOT read-to-clear (smac_real_counters_re.md §;
  only TM[0x10058] is clear-on-read).
