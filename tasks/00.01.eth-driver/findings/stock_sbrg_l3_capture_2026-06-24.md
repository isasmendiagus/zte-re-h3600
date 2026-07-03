# Stock SBRG bridge-config capture (for the l3_en gate diff) — 2026-06-24

Captured live on STOCK (booted from NAND, 192.168.1.1) via SSH + `fpga -r <widx>` (widx =
(phys-0x92000000)/4; SBRG base_off region 0xe2xxx → phys 0x92388xxx). Goal: find the per-port
L3/bridge config stock has that the mainline driver never writes — the suspected armer of the
per-packet `l3_en` descriptor bit (see offload_gate_investigation_2026-06-24.md).

## ★ Prime suspect: da_lookup_en (sbragRegTable reg_id 0x2c/44)
`sbrg_set_pt_da_lookup_en(port,en)` (decomp tm.c:6228) = reg_id 44, base_off 0xe20b0 →
**phys 0x923882c0**, bits[7:0] = per-port enable (bit N = port N). **STOCK = 0x000000ff (all 8
ports DA-lookup ENABLED).** The mainline driver NEVER writes reg_id 44 (grep: only reg_id 57
port-isolate + the indirect FDB add use zx_sbragregtable) ⇒ mainline leaves it at HW default.
DA-lookup is the only PROVEN destined-to-me/DA machinery (verifier's mandated fallback); if it's
the armer of l3_en, mainline-default (likely 0) = the gate. TEST: read mainline 0x923882c0; if
!=0xff, set 0xff and watch acl_required.

## Full SBRG config snapshot (stock)
| widx (base_off) | phys | value | notes |
|---|---|---|---|
| 0xe2001 | 0x92388004 | 0x040200ff | reg1 transfer_en bits[7:0]=0xff (all ports) + reg5/6/7/8/9 fields |
| 0xe2002 | 0x92388008 | 0x0000dfdf | reg10/11 (0xdf,0xdf) + reg12-14 |
| 0xe2005 | 0x92388014 | 0x01000fff | reg15(0xfff)/16/17/18 |
| 0xe2006 | 0x92388018 | 0x00000001 | reg20/21 |
| 0xe2007 | 0x9238801c | 0x0001ffff | reg22 (sub0) |
| 0xe2060 | 0x92388180 | 0x00000004 | reg23-28 |
| 0xe2061 | 0x92388184 | 0x00000001 | reg29 |
| 0xe2062 | 0x92388188 | 0x00211b00 | reg30 |
| 0xe2064 | 0x92388190 | 0x00000000 | reg31 |
| 0xe2070 | 0x923881c0 | 0x000000ff | reg32/33 bits[7:0]=0xff (all ports) |
| 0xe2071 | 0x923881c4 | 0x00005555 | reg34-41 (2-bit fields, 0b01 per port) |
| 0xe2075 | 0x923881d4 | 0x00000000 | reg42 (sub0) |
| 0xe2080 | 0x92388200 | 0x00000000 | reg43 (sub0) |
| **0xe20b0** | **0x923882c0** | **0x000000ff** | **reg44 da_lookup_en — ALL PORTS ON (prime suspect)** |
| 0xe20b5 | 0x923882d4 | 0x00005555 | reg45/46/47 |
| 0xe20b6 | 0x923882d8 | 0x00000000 | reg48 (sub0) |
| 0xe20c0 | 0x92388300 | 0x00000000 | reg49/50 |
| 0xe20c1 | 0x92388304 | 0x00000000 | reg51 |
| 0xe20d0 | 0x92388340 | 0x015555ff | reg52/53/54 (bits[7:0]=0xff + 0x5555) |
| 0xe20d1 | 0x92388344 | 0x00000000 | reg55 |
| 0xe20e0 | 0x92388380 | 0x00000001 | reg56 |
| 0xe20f0 | 0x923883c0 | 0x000000fe | reg57 port-isolate sub0 = 0xfe (driver DOES write this) |
| 0xe218c | 0x92388630 | 0x00000080 | reg58 |

## Other L3 regs (stock, for the diff)
- CLA config 0x9238c080 = 0x600 (== mainline; not the gate).
- CLA local_ipv4 0x9238c09c = **0x00000000 on stock TOO** ⇒ local_ipv4 is NOT the differentiator
  (was my/the workflow's STEP-3 hypothesis — REFUTED: both 0).
- SPA ONU-MAC slot0 0x921d4120 = 0x470f4264 (device MAC; == mainline slots 0-3).

## Candidates to diff vs mainline (set on stock, possibly unset on mainline)
Ranked by "driver never writes it": **reg44 da_lookup_en (0xff)** [TOP — driver never writes];
reg32/33 (0xe2070=0xff); reg34-41 (0xe2071=0x5555); reg45-47 (0xe20b5=0x5555); reg52-54
(0xe20d0=0x015555ff); reg30 (0xe2062=0x00211b00); reg56 (0xe20e0=1). Many are per-port enables the
mainline init likely skips. NEXT: reboot mainline, read the same widx set, diff, then enable the
stock-set-but-mainline-unset ones (da_lookup_en first) and watch acl_required (0x9238c3b8 hi16).

## ★ RESULT (mainline diff + test) — STATIC APPROACH DEFINITIVELY EXHAUSTED
Rebooted mainline, read the same SBRG widx set, diffed vs stock:
- **da_lookup_en (0x923882c0) = 0xff on mainline TOO** (HW reset default) → NOT the gate. Refuted.
- Only **3** registers differ: e2002 (stock 0x0000dfdf / mainline 0x0000ff00), e2005 (0x01000fff /
  0x000001c8), e2007 sub0 (0x0001ffff / 0x0064420f). All OTHER SBRG L3/bridge config is IDENTICAL.
- TEST: poked mainline's e2002/e2005/e2007 to the stock values (readback-confirmed stuck) + flooded
  the transit flow → **acl_required STILL 0, cla_tx_fwd 0** (hw_trap climbed). The 3 SBRG diffs are
  NOT the gate (likely incidental L2/VLAN/port-membership config, not the l3_en armer).
⇒ Combined with all prior refutations: **there is NO static-config gate.** The L3-relevant static
state (da_lookup, local_ipv4=0 both, ONU-MAC, CLA config 0x600, classify-loadable) is identical
stock↔mainline, yet stock forwards and mainline traps. **The difference is DYNAMIC**: stock's CPU
actively routes the flow AND the FFE conntrack engine (switch.ko: ffe_learn_skb → hf_set_l3_entry →
zte_api_fast_l3_session_add) installs the HW session at runtime; acl_required climbing on stock is a
CONSEQUENCE of an FFE-installed, actively-routed flow — not a static gate. Manually writing ram2
(slot-sweep) didn't move acl_required because the FFE install does more than ram2 AND/OR the packet
isn't recognized as an actively-routed session.
## ONLY remaining path: active-forwarding capture
Capture stock WHILE ACTIVELY FORWARDING (acl_required climbing): provision routing via the web UI
(Chrome MCP → Enrutamiento) so stock routes a real LAN→WAN flow, then (a) confirm acl_required climbs
for that flow, (b) read the descriptor l3_en + the FFE-installed CLA ram2 + PM next-hop/flow_info for
the live 5-tuple, (c) compare to mainline. This shows EXACTLY what an armed/forwarded flow looks like
— the dynamic install to replicate. Needs stock routing active (UI provisioning; WAN uplink or an
internal route).
