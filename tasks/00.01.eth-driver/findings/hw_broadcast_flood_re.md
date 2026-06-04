# Autonomous HW broadcast/multicast flood on the ZX279128S — register RE

Status: pure RE, 2026-06-04. Source: `decomp_all_tm.c` (sbrg_* bodies +
`tm_pon_pp_brg_initial`), `DATASHEET.md` SBRG/PP map, live stock dump
`regs/stock_eth_2mib.txt`, mainline `zx-eth-main.c` (`zx_pp_brg_init`),
empirical Iter AF/AG in `hw_forwarding_offload.md`.

THE HEADLINE (answers the whole brief):

> **Autonomous HW broadcast flood is NOT governed by `brdcst_fld_en`
> (PP[0x8300]) and NOT by the per-protocol SPA pktdeal RAM (0x921d4300).
> In stock, a broadcast/unknown-DA frame floods to the LAN ports purely by
> the SBRG VLAN-membership RAM (the per-VLAN port action table) minus the
> per-port isolation mask.** `brdcst_fld_en` is a *forced-flood override*
> that ADDS the listed ports (incl. the CPU port) on top of VLAN flooding —
> stock leaves it 0 precisely because turning it on hairpins the device's own
> broadcasts back to the CPU. So broadcast flood and unicast forwarding are
> in two independent register blocks and compose freely. See §2/§3.

---

## 1. The complete SBRG broadcast/multicast/unknown-flood register map

All registers live in the SBRG / PP_BRG block, **base phys `0x92388000`**
(ioremap base `0x921c0000` + `PP_OFF 0x1c0000` ⇒ pp window offset = phys −
`0x92380000`). Stock reaches them via `tmOnuRegWrite(reg_id, val, sub, &sbragRegTable)`;
each `sbragRegTable[reg_id]` entry is `{…, +8 phys_addr, +0xc mask, +0x10 shift,
+0x14 stride}` (read-modify-write with mask/shift — see `tmOnuRegWrite` @ tm.ko
0x45c14). reg_id (hex used in decomp) == DATASHEET reg_id (decimal). Verified
mapping for every flood register:

| setter fn (tm.ko) | reg_id | phys | pp off | bits | field | per-port? | LIVE stock |
|---|---|---|---|---|---|---|---|
| `sbrg_set_multicst_transmit_ctrl` | 0x2d (45) | 0x923882d4 | 0x82d4 | [15:0] | multicst_transmit_ctrl | 2b/port | **0x5555** (=1 each) |
| `sbrg_set_unknown_multicst_pktdeal` | 0x2e (46) | 0x923882d4 | 0x82d4 | [23:16] | unknown_multicst_pktdeal | 1b/port | 0x00 |
| `sbrg_set_unknown_multicst_fwd` | 0x2f (47) | 0x923882d4 | 0x82d4 | [31:24] | unknown_multicst_fwd | 1b/port | 0x00* |
| `sbrg_set_unkmul_flood_portmask` | 0x30 (48) | 0x923882d8 | 0x82d8 | [7:0]×9 | unkmul flood portmask | bitmap×idx | 0 |
| **`sbrg_set_brdcst_fld_en`** | 0x31 (49) | 0x92388300 | **0x8300** | [7:0] | **brdcst_fld_en** (forced bcast flood portmask) | bitmap | **0x00** |
| **`sbrg_set_brdcst_fwd_en`** | 0x32 (50) | 0x92388300 | **0x8300** | [15:8] | **brdcst_fwd_en** | bitmap | **0x00** |
| `sbrg_set_pon_brdcst_fld_inctrl` | 0x33 (51) | 0x92388304 | 0x8304 | [7:0] | bcast flood portmask | bitmap | 0x00 |
| `sbrg_set_unknown_unicst_*` | 0x35 (53) | 0x92388340 | 0x8340 | [23:8] | unknown_unicst_pktdeal | 2b/port | 0x5555 |
| `sbrg_set_unknown_unicst_fwd` | 0x36 (54) | 0x92388340 | 0x8340 | [31:24] | unknown_unicst_fwd | bitmap | 0x01 (CPU only) |
| `sbrg_set_pon_unkuni_fld_inctrl` | 0x37 (55) | 0x92388344 | 0x8344 | [7:0] | unkuni flood portmask | bitmap | 0x00 |
| `sbrg_set_pt_tls` | 0x38 (56) | 0x92388380 | 0x8380 | [7:0] | pt_tls | bitmap | 0x01 (CPU only) |
| `sbrg_set_dft_multi_vl_trans_pktdeal` | 0x43 (67) | 0x92388638 | 0x8638 | [7:0] | dft_multi_vl_trans_pktdeal | 1b/port | **0xc0** |
| **`sbrg_set_dft_brd_vl_trans_pktdeal`** | 0x44 (68) | 0x9238863c | **0x863c** | [15:0] | **dft_brd_vl_trans_pktdeal** | 2b/port | **0x0000** |
| `sbrg_set_dft_unkuni_vl_trans_pktdeal` | 0x45 (69) | 0x9238863c | 0x863c | [31:16] | dft_unkuni_vl_trans_pktdeal | 2b/port | 0x0000 |
| `sbrg_set_multicst_vltrans_table` | 0x48 (72) | 0x92388670 | 0x8670 | [31:0]×49 | per-VLAN multicast translate/flood | per-VLAN | 0 |
| `sbrg_set_brdmulticst_vltrans_table` | 0x49 (73) | 0x92388730 | 0x8730 | [31:0]×49 | per-VLAN **broadcast** translate/flood | per-VLAN | 0 |

\* `unknown_multicst_fwd` is set to **1 for all 8 ports** in `tm_pon_pp_brg_initial`
(tm.c:43632 `sbrg_set_unknown_multicst_fwd(port,1)`); the live dump byte read 0
because the capture window differs — the authoritative init value is 0xff. (For
broadcast the equivalent `brdcst_fwd_en` is deliberately left 0.)

Master enables that gate whether the bridge runs at all (all set by
`tm_pon_pp_brg_initial`, live-confirmed):

| phys | pp off | field | LIVE | meaning |
|---|---|---|---|---|
| 0x92388004 | 0x8004 | pt_transfer_en[7:0] / age / exchange_md | 0x040200ff | all 8 ports transfer-enabled; macaddr_age_en(b17); exchange_md(b26) |
| 0x923882c0 | 0x82c0 | pt_da_lookup_en[7:0] | 0x000000ff | DA-lookup (FDB) on for all ports — drives known-vs-unknown decision |
| 0x923881c0 | 0x81c0 | pt_smac_look_en[7:0] / lookfail_pktdeal | 0x000000ff | SMAC-lookup (learning) on for all ports |
| 0x923881c4 | 0x81c4 | pt_learn_mode[port] | 0x00005555 | learn_mode=1 (auto-learn) all ports |
| 0x923883c0+p*4 | 0x83c0 | isolate_pt_cfg[port] (x9) | 0xfe/fd/fb/f7/ef/df/ff/ff | per-port egress mask: each port may egress to all-but-itself |

### What each "pktdeal" / "transmit_ctrl" value means (decomp range checks)
- broadcast/unkuni/multicst `vl_trans_pktdeal` and `multicst_transmit_ctrl` are
  2-bit fields; the setters accept **0, 1, 2** (value 3 rejected — see
  `tm_port_dft_broadcst_vltrans_set` @ tm.c:44779, `sbrg_set_dft_brd_vl_trans_pktdeal`
  @ tm.c:11496 `param_2<3`). These are *VLAN-translate* actions (0 = no
  translate / use VLAN-membership flood; 1, 2 = translate variants), NOT a
  flood/trap toggle.
- the SPA per-protocol `enty_pktdeal_cfg` (0x921d4300) is a **different** 2-bit
  field with **0=FORWARD, 1=TRAP-to-CPU, 2=DROP, 3=copy**
  (`decomp_halt_baddata_band.c`, confirmed live Iter AF/AG).

---

## 2. Forwarding decision for a broadcast frame (DA = ff:ff:ff:ff:ff:ff)

Authoritative bridge init is **`tm_pon_pp_brg_initial`** (tm.c:43579), NOT the
plat `pon_pp_brg_init` (proven by live: 0x8340=0x015555ff matches tm.c's path,
not plat's 0xff5555ff). Its broadcast-relevant actions:

- `sbrg_set_pt_transfer_en(port,1)` ×8, `sbrg_set_pt_da_lookup_en(port,1)` ×8,
  `sbrg_set_pt_smac_look_en/learn_mode` ×8 — bridge fully enabled + learning.
- `sbrg_set_unknown_unicst_fwd(port,0)` ×8 then `(0,1)` → unknown-UNICAST floods
  to CPU port only.
- `sbrg_set_pt_tls(port,0)` ×8 then `(0,1)` → PP[0x8380]=0x01.
- **It NEVER calls `sbrg_set_brdcst_fld_en` / `sbrg_set_brdcst_fwd_en` /
  the bcast flood-portmask / `sbrg_set_dft_brd_vl_trans_pktdeal`.** They stay at
  cold-reset 0 (live dump: 0x8300=0, 0x8304=0, 0x863c=0). Confirmed by grep of
  every caller in the kmods.

⇒ **Stock's broadcast forwarding decision: a broadcast (or any DA that the FDB
treats as flood) is replicated by the SBRG to every port that is a member of the
frame's VLAN, minus that port's isolation-mask bit, minus the ingress port
itself.** The VLAN-membership RAM is the per-VLAN port-action table (ram_id 4 in
the PP_BRG indirect RAM at 0x8014/0x801c…; in mainline programmed to "all 8 ports
action=3" = word 0x1FFFF for VLAN 0 and 1). Isolation rows (0x83c0+p*4) carry
"all-but-self" so a LAN-ingress broadcast egresses the *other* LAN ports.
**This flood happens in HW, autonomously, with no CPU involvement.**

`brdcst_fld_en` (PP[0x8300]) is an ADDITIVE forced-flood portmask layered on top
— turning it on forces the listed ports (including the CPU port, bit 0) to always
receive broadcast even when VLAN/isolation would not. Stock keeps it 0 because
including the CPU port re-injects the device's own egress broadcasts back to the
CPU (the documented +15 hairpin, `cpu_lan_egress_gate_re.md`). It is therefore
**not needed** for LAN-to-LAN HW flood and is actively harmful if it lists the CPU
port.

---

## 3. Is broadcast flood SEPARATE from 0x921d4300? — YES (confirmed)

Two different blocks, two different pipeline stages:

| | block base | reg | stage | role |
|---|---|---|---|---|
| per-protocol pktdeal | **SPA** 0x921d4000 | 0x921d4300 (reg67[1:0], +0x14/idx) | SPA classify (early) | 0=fwd / 1=trap / 2=drop per (port × proto-slot) |
| broadcast flood | **SBRG/PP_BRG** 0x92388000 | VLAN-membership RAM + 0x83c0 isolation (+ optional 0x8300) | L2 bridge (later) | replicate flood frame to member ports |

They are independent and **compose**: setting every SPA pktdeal slot = 0
(forward) only changes the SPA classify verdict; the SBRG VLAN-flood for
broadcast is governed entirely by the membership/isolation RAM and is untouched
by 0x921d4300. So **"all per-protocol slots = forward" + "VLAN-membership flood
configured" gives HW broadcast flooding alongside HW unicast forwarding** — they
do not conflict.

### Why Iter AF saw broadcast die under all-pktdeal=0 (reconciliation)
Iter AF (`hw_forwarding_offload.md`) set all SPA slots = forward and saw ARP/ND
neither flooded nor trapped (`hw_fwd=0, tm_rx=0`). That is NOT because broadcast
flood lives in 0x921d4300 — it is because in the *current mainline trap-all DSA
conduit* the chip's L2 forwarding/flood path was never actually exercised: the
CLA traps everything to the CPU and the bridge relied on that trap + SW flood.
Removing the trap (all-forward) removed the only path that was moving broadcast,
while the autonomous SBRG VLAN-flood was not yet doing the replication because the
bridge forwarding/FDB offload is not wired up (the `zte-hw-forwarding-deadend`
problem). The fix is to ENABLE the SBRG VLAN-flood path (this doc's §4 recipe),
not to touch 0x921d4300. The two are orthogonal.

---

## 4. Recipe: autonomous HW broadcast flood to the LAN ports

Apply in the SBRG/PP_BRG window (`pp = base + 0x1c0000`). Values are the
**stock-authoritative** ones (from `tm_pon_pp_brg_initial` + the VLAN init), which
is the configuration under which the stock chip floods broadcast LAN→LAN in HW.

```c
/* --- bridge master enables (already in mainline, keep) --- */
writel(0x040200ff, pp + 0x8004);  /* transfer_en all + age_en + exchange_md   */
writel(0x000000ff, pp + 0x82c0);  /* pt_da_lookup_en all ports                 */
writel(0x000000ff, pp + 0x81c0);  /* pt_smac_look_en all ports                 */
writel(0x00005555, pp + 0x81c4);  /* learn_mode=1 all ports                    */

/* --- the autonomous flood path: VLAN membership + isolation --- */
/* per-VLAN port-action RAM (ram_id 4), VLAN 0 and 1, all 8 ports action=3:   */
/*   for each vlan: poll pp[0x8018]&1; write (vlan|4<<22)->pp[0x8014];         */
/*   write 0x1FFFF->pp[0x801c]; 0->0x8020/0x8024/0x8028.  (mainline already    */
/*   does this — it is THE broadcast replication table)                        */
/* per-port egress/isolation mask "all-but-self" (stock-live):                 */
writel(0x000000fe, pp + 0x83c0);  /* port0 -> all but 0 */
writel(0x000000fd, pp + 0x83c4);  /* port1 -> all but 1 */
writel(0x000000fb, pp + 0x83c8);  /* port2 */
writel(0x000000f7, pp + 0x83cc);  /* port3 */
/* ...stock leaves the LAN rows at all-but-self; CPU/uplink rows per topology  */

/* --- DO NOT force-flood through the CPU port --- */
writel(0x00000000, pp + 0x8300);  /* brdcst_fld_en / brdcst_fwd_en = 0 (stock) */
writel(0x00000000, pp + 0x8304);  /* bcast flood portmask = 0  (stock)         */
writel(0x015555ff, pp + 0x8340);  /* unknown_unicst: pktdeal 0x5555 + fwd=CPU   */
writel(0x00000000, pp + 0x8344);  /* unkuni flood portmask = 0 (stock)          */
writel(0x00000001, pp + 0x8380);  /* pt_tls: CPU port only (stock)              */
writel(0x00000000, pp + 0x863c);  /* dft_brd / dft_unkuni vl_trans_pktdeal = 0  */
                                  /* (stock — NOT 0xaaaaaaaa)                    */
writel(0x000000c0, pp + 0x8638);  /* dft_multi_vl_trans_pktdeal = 0xc0 (stock)  */
/* multicast: stock sets unknown_multicst_fwd=0xff (flood mcast to all ports): */
/*   read-modify 0x82d4[31:24]=0xff (sbrg_set_unknown_multicst_fwd per port)   */
```

**The load-bearing trio for broadcast = (a) per-VLAN membership RAM lists all LAN
ports, (b) isolation rows are "all-but-self", (c) `brdcst_fld_en`=0 so the CPU
port is NOT force-added.** That is the entire autonomous-flood config. No
0x921d4300 change is required or wanted.

To also make HW *unicast* forward (the parallel goal) the missing piece is the
SBRAG unicast FDB being populated (assisted learning → `.port_fdb_add` →
`zx_sbrag_write_entry`) so known-DA unicast egresses to one port instead of
flooding — that is the separate `zte-hw-forwarding-deadend` work and is
orthogonal to broadcast flood.

---

## 5. Stock vs mainline diff — what mainline gets WRONG for HW broadcast flood

Mainline `zx_pp_brg_init` (zx-eth-main.c ~L2509-2600) DOES program the VLAN-0/1
membership RAM (all 8 ports, 0x1FFFF) and the isolation rows, so the autonomous
flood *substrate* is present. The remaining drifts (current mainline values vs
stock-authoritative):

| pp off | field | mainline now | stock | impact |
|---|---|---|---|---|
| 0x863c | dft_brd / dft_unkuni vl_trans_pktdeal | **0xaaaaaaaa** (=2 all ports) | **0x00000000** | DRIFT. Mainline forces vl-translate action 2 on all broadcast; stock uses 0 (plain VLAN-membership flood). 0xaaaaaaaa can mis-route/translate broadcast away from a plain flood. **Set to 0.** |
| 0x8300 | brdcst_fld_en/fwd_en | 0x00000000 (already fixed) | 0x00000000 | OK now (earlier 0xffff caused the CPU-port hairpin). |
| 0x8304 | bcast flood portmask | 0x00000000 (fixed) | 0x00000000 | OK now. |
| 0x8344 | unkuni flood portmask | 0x00000000 (fixed) | 0x00000000 | OK now. |
| 0x8380 | pt_tls | 0x00000001 (fixed) | 0x00000001 | OK now. |
| 0x8008 | transfer/vlan-chk | 0x0000ff00 | **0x0000dfdf** | 2nd-order drift (vlan-check bitmap); fix to dfdf. |
| 0x82d4 | unknown_multicst_fwd[31:24] | not explicitly set | **0xff** | Mainline never calls the multicast-flood enable; stock floods unknown-multicast to all ports. **Add `unknown_multicst_fwd=0xff`** if multicast group flood is wanted. |

What mainline is MISSING for full autonomous HW broadcast flood:
1. **`PP[0x863c] = 0` (not 0xaaaaaaaa).** Highest-leverage. Stock floods broadcast
   with vl_trans_pktdeal=0; mainline's 0xaaaaaaaa applies translate-action-2 which
   is not the plain-flood path.
2. **`unknown_multicst_fwd = 0xff`** at 0x82d4[31:24] (stock floods unknown
   multicast to all ports; mainline omits it). Only needed if multicast flood is
   required in addition to broadcast.
3. Cosmetic: 0x8008 → 0x0000dfdf.

The broadcast *substrate* (VLAN membership RAM + isolation) is otherwise correct
in mainline; the autonomous flood mainly needs the 0x863c value corrected and the
multicast-fwd bit added — and crucially it must NOT be coupled to any 0x921d4300
change (which is what broke Iter AF).

---

## Confidence
- Reg→addr→field mapping (every flood reg): HIGH. Decomp `tmOnuRegWrite` index +
  DATASHEET table + live dump cross-check all agree (e.g. 0x36→0x8340 verified
  three ways).
- "Broadcast flood = VLAN membership minus isolation, brdcst_fld_en is an additive
  CPU-hairpin override stock leaves 0": HIGH (decomp `tm_pon_pp_brg_initial` never
  calls the flood setters; live dump 0x8300/0x8304/0x863c=0; egress-gate RE).
- "Separate from 0x921d4300, composes with all-forward": HIGH (different block,
  different stage; SPA pktdeal value semantics differ from vl_trans pktdeal).
- "Mainline 0x863c=0xaaaaaaaa is the broadcast-flood drift": MEDIUM-HIGH (clear
  source-vs-stock value diff; exact behavioural effect of vl_trans=2 not bench-
  confirmed). Bench step: set 0x863c=0, keep all SPA pktdeal at stock, br0 over ≥2
  LAN ports, ARP between two hosts → expect HW flood with tm_rx flat.

---

## LIVE TEST (2026-06-04, Iter AM) — the recipe did NOT enable HW broadcast flood

Tested on the live mainline device (good jack4 NIC, br0=lan0..3, jack2/lan↔jack4/lan):
1. all SPA pktdeal slots → forward (`all 0`).
2. poked `0x9238863c=0` (dft_brd vl_trans_pktdeal), then the FULL §4 recipe via the poke
   debugfs: `0x8004=0x040200ff, 0x82c0=0xff, 0x81c0=0xff, 0x81c4=0x5555, 0x8300=0,
   0x8304=0, 0x8340=0x015555ff, 0x8344=0, 0x8380=0x01, 0x863c=0, 0x8638=0xc0,
   0x82d4=0xff005555` (readbacks confirmed the writes landed).
3. Dynamic ARP (neigh flushed) ping nsB→nsA.

RESULT: **100% loss both times** — broadcast still does NOT HW-flood LAN→LAN. So the §4
register recipe is necessary-but-NOT-sufficient. This CONFIRMS the doc's own §3 caveat:
in the mainline trap-all conduit the chip's autonomous L2 forward/flood path is not
actually active, and just setting the SBRG flood/VLAN/isolation registers does not turn
it on. The missing piece is the same `zte-hw-forwarding-deadend` wiring (the DA-lookup /
FDB-offload / forwarding-enable path) that makes the chip do L2 forwarding+flooding on
its own instead of trapping to the CPU.

NOTE the asymmetry that proves the path is partly-active: known-DA UNICAST does HW-forward
(UDP both dirs, TCP data — tm_rx flat) — so DA-lookup→egress works. But BROADCAST (DA-miss
→ flood) does NOT replicate in HW. So the unicast-egress path is wired but the
flood-replication path is not, and the §4 registers alone don't enable it. Enabling HW
broadcast flood needs more than these registers (likely a VLAN-membership-RAM /
flood-replication-enable that mainline isn't programming correctly, or a master
flood-enable not captured here). Until that's cracked, all-0 (forward all protocols)
cannot be used because broadcast/ARP dies.

NET: the "all-0 + HW-broadcast-flood" clean-solution path is BLOCKED at the broadcast
flood-replication wiring — same root as the open HW-forwarding-offload problem.

---

## LIVE DIAGNOSTIC (Iter AN) — broadcast dies at drop_PP (0x921da040), NOT flooded

Under all-0, generated a sustained broadcast flood (`ping -b -f 10.0.0.255` from nsB) and
diffed the FULL pipeline chain. Clean result:
- smac3 RX_pkts +341 (the broadcast frames arrived at the MAC).
- **`drops: PP[0x1a040]` +341** (EXACTLY matches) — every broadcast frame is DROPPED at the
  PP forwarding/policy stage (drop_PP, phys 0x921da040).
- RED[0x1a044], DSCH[0x1a04c] unchanged; QMG hw_fwd/hw_trap unchanged (no flood, no trap).

⟹ The broadcast-flood failure is NOT a missing SBRG flood register (those were poked with
no effect) — it is the **PP forwarding decision DROPPING broadcast** instead of replicating
it. This is the SAME drop_PP stage where port1 ingress died (DATASHEET errata). With the
stock pktdeal table broadcast WORKS only because it TRAPS to the CPU (deal=1 → bridge SW-
floods); the autonomous HW flood-replication path is what drop_PP is refusing.

NEXT RE TARGET (precise): the PP / drop_PP (0x921da040) forwarding-and-flood-replication
decision — what makes PP DROP a broadcast (DA=ff:ff:ff) vs REPLICATE it to the VLAN member
ports. This is the real lever for autonomous HW broadcast flood (and, once it floods,
all-0 forwards TCP too with no broadcast cost).

---

## CORRECTION (Iter AO) — "stock parity" was OVER-CLAIMED; stock DOES forward TCP ACKs

Journey #34 concluded "we are at stock parity (stock also traps control to CPU for L2)". That
CONFLICTS with the earlier DIRECT live stock measurement (Iter O, zte-hw-forwarding-deadend):
stock ran TCP at 353 Mbit/s with QMG **hw_trap FLAT** (CPU bypassed) — so stock HW-forwards the
TCP flow including ACKs; only ICMP trapped. A direct live measurement outweighs the decomp
inference, so: **stock forwards the TCP ACKs; our merged solution traps them. We are NOT at parity.**

Likely mechanism (to be RE-confirmed): stock's "hw_trap flat" is the STEADY STATE after the FFE
conntrack engine, on ESTABLISHED, installed a HW forward bind for the flow (stock's FFE explicitly
TRAPS TCP until conntrack==ESTABLISHED, then offloads). So stock's ACK-forward is the FFE-installed
bind, NOT a static matchram classify-to-forward (if the matchram forwarded TCP, stock would never
trap it / need the FFE). The SPA matchram is therefore probably NOT the lever — but RE of stock's
matchram init settles it: if stock's matchram traps TCP-control → confirms it's the FFE bind; if it
forwards TCP → the matchram IS the lever and mainline (which leaves matchram at HW-default) just
needs to replicate it. Open question; pursuing via matchram RE.

---

## ★★★ DECISIVE LIVE STOCK MEASUREMENT (Iter AP) — stock HW-forwards TCP ACKs (NOT at parity)

Booted stock NAND (DTR power-cycle, no autoboot interrupt; SSH admin@.1). Two hosts on stock LAN
ports (jack2=192.168.1.50, jack4/nsB=192.168.1.51), iperf3 TCP .51→.50 through stock's bridge.
Read stock QMG counters via /bin/fpga→/dev/logger_main (hw_trap widx 0xd3018, hw_fwd 0xd3017,
sw_fwd 0xd3011):
- BEFORE (idle): hw_trap=188, hw_fwd=0, sw_fwd=310.
- DURING (mid 353 Mbit/s TCP flow): hw_trap=241, hw_fwd=0, sw_fwd=367.
- ⟹ **hw_trap delta = +53** over ~6s of a 353 Mbit/s flow (hundreds of thousands of frames).
  Negligible = background ARP/control. **Stock does NOT trap the TCP ACK stream — it HW-forwards it.**

CONTRAST: on MAINLINE the identical flow traps **+62000** (the whole ACK stream) to the CPU.
Both hit 353-354 Mbit/s (same throughput, single flow) but stock's CPU is ~idle, mainline's drains
62k ACKs/flow. hw_fwd=0 on BOTH → the bulk L2 forward bypasses QMG (ring-less fabric path).

CONCLUSIONS (decisive, ends the contradictions):
1. **We are NOT at stock parity** — stock HW-forwards TCP ACKs; mainline traps them.
2. **The goal IS achievable** (stock proves it on this exact silicon).
3. Stock forwards ACKs **statically from t=0** (hw_trap delta is flat/background, no learning burst) ⟹
   **NOT the FFE** (no trap-then-install). It is a **static chip-config difference** mainline doesn't
   replicate. (This also overrides the matchram agent's "stock traps generic TCP" inference — the
   live chip forwards it.)
NEXT: diff stock's LIVE forward/trap config vs mainline's programmed config to find the lever that
routes TCP-ACK to the ring-less L2 fabric (forward) instead of the SPA-pktdeal-trap path. Stock 2MiB
dump exists (regs/stock_eth_2mib.txt); read stock's pktdeal RAM (0x921d4300) + SADM/transfer/da_lookup
+ ring-less-path enables live and compare to zx_pp_pro_actions / the mainline init.
