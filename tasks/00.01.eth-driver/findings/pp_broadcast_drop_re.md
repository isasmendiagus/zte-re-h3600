# Why broadcast dies at `drop_PP` (0x921da040) — PP/OPC stage RE

Status: pure RE, 2026-06-04. Read-only (no source edited, device untouched).
Sources: `decomp_all_tm.c` (the UP statistics dumper @0x52xxx, `tm_pon_*_initial`
bodies, `qmg_set_qmg_trap_cfg`, OPC/SOPC setters), `DATASHEET.md` (OPC/drop-counter
map), live stock dump `regs/stock_eth_2mib.txt`, mainline `zx-eth-main.c`, and the
prior live findings `hw_broadcast_flood_re.md`, `port1_drops_at_PP_re.md`,
`pktdeal_override_re.md`, `redwedge_debug_state.md`.

---

## TL;DR — the headline correction

**`drop_PP` (0x921da040) is NOT a "bridge forwarding/policy" stage and it is NOT
the lever for broadcast flood-replication.** It is the **OPC top "PP DROP"
drop-reason counter** at the very *end* of the upstream pipeline (the egress
issue stage). It is the symptom, not the gate.

A broadcast increments `drop_PP` for one reason: **it reached the OPC issue stage
with NO valid egress destination** — because nothing upstream gave it one. On
this chip a broadcast/unknown-DA frame is given a destination in exactly two ways,
and stock uses only the second:

1. **Autonomous L2 flood-replication** — NOT configured by stock at all. Stock's
   bridge init `tm_pon_pp_brg_initial` deliberately leaves every broadcast-flood
   register at 0 (`brdcst_fld_en`/`brdcst_fwd_en`/bcast-flood-portmask = 0). There
   is **no broadcast replication/MGID/flood-domain table that stock programs**.
2. **Trap to CPU** — stock's `def_ptl_pkt_action` (pro_action) marks the
   broadcast/control protocol slots as deal=1 (TRAP). The SPA classifier traps the
   broadcast to the CPU queue; the Linux bridge then floods it in software.

So **stock NEVER autonomously HW-floods broadcast LAN→LAN.** It traps it to the
CPU and software-floods. The "drop_PP +N exact-match under all-pktdeal=0" you
measured is precisely what happens when you remove the trap (set every pktdeal
slot to forward) **without** there being any autonomous-flood path to take over:
the broadcast has no destination, falls through to OPC, and OPC counts it as a PP
drop. This reconciles every live observation (RED/DSCH flat, QMG hw_fwd/hw_trap
flat, drop_PP == MAC RX exactly).

The lever to make broadcast "work" is therefore **NOT** a PP/OPC register — it is
either (a) keep the SPA pktdeal trap on the broadcast/ARP/ND slots (= what stock
does; SW-flood), or (b) build the autonomous flood-replication path the chip does
not ship with — which is the open `zte-hw-forwarding-deadend` problem and needs
more than any single 0x921da0xx / SBRG register (already proven: poking all those
had no effect).

---

## 1. What `drop_PP` / the 0x921da000 block actually is

The block at phys **0x921da000** is the **OPC top** (output-processor /
issue-stage) status+drop region, NOT the SBRG bridge and NOT "PP_PM". Decompile
proof — the upstream statistics dumper (`tm_up_statistics_get`, decomp
`decomp_all_tm.c:46345-46450`) reads the three OPC drop counters and labels them:

```c
local_20c = fpga_read_reg(0x76810);   /* phys 0x92000000 + 0x76810*4 = 0x921DA040 */
local_208 = fpga_read_reg(0x76811);   /*                              = 0x921DA044 */
local_204 = fpga_read_reg(0x76812);   /*                              = 0x921DA048 */
...
printk("opc_top pp drop cnts: %u\n",  local_20c);   /* 0x921da040  ← "drop_PP"  */
printk("opc_top red drop cnts: %u\n", local_208);   /* 0x921da044  ← "drop_RED" */
printk("opc_top usch drop cnts: %u\n",local_204);   /* 0x921da048             */
```

(The DN dumper @46587-46653 reads the mirrored set `0x76810/11/13` and prints
`PP DROP / RED DROP / DSCH DROP`.) So:

| phys | fpga widx | OPC counter | meaning |
|---|---|---|---|
| 0x921da040 | 0x76810 | **opc_top PP DROP** | frame reached OPC issue with no valid disposition |
| 0x921da044 | 0x76811 | opc_top RED DROP | dropped by RED at the OPC (the unicast→CPU wedge counter) |
| 0x921da048/4c | 0x76812/13 | opc_top USCH/DSCH DROP | egress-scheduler drop |

These are **drop-REASON aggregates at the OPC**, the last stage. They are
clear-on-nothing read counters, live stock = 0 in a healthy capture
(`stock_eth_2mib.txt:26641` `921da040 00000000`). Writable OPC config in this
block is tiny: `0x921da004` sp_rr (=0x55 live), `0x921da054`=0xb00,
`0x921da060`=0x280001c0 — scheduler/round-robin knobs, **no forwarding/flood
decision lives here.** `greg_set_opc_ram_init`/`opc_top_set_sp_rr_cfg` are the
only OPC setters and they configure RAM-init + scheduling, not destinations.

The full UP pipeline order, read straight off the dumper's print sequence:
```
SMAC → SPA(fwd/drp/cpy/trp) → pp_ctrl_drop → SADM(pass/drop) → BRG(tx/rx) →
CLA(fwd/trap/drop/copy) → PM(recv/send/fwd/trap) → DPA → RED(fwd/trap/drop) →
QMG(sw_fwd/hw_fwd/hw_trap) → USCH → UOPC → OPC-top(PP/RED/USCH drop)
```
`drop_PP` is the terminal bucket. A frame only lands there if it traversed
everything upstream **without being assigned an egress (forwarded, trapped, or
explicitly dropped earlier).** That is exactly the state of a broadcast when the
trap is removed and no flood-replication exists.

---

## 2. THE KEY question — what replicates broadcast vs drops it

**Decompiled answer: stock has NO autonomous broadcast replication path. There is
no MGID / flood-domain / member-replication table that stock programs for
broadcast.** Proof from the authoritative bridge init `tm_pon_pp_brg_initial`
(`decomp_all_tm.c:43579-43644`):

- It enables the bridge: `sbrg_set_pt_transfer_en(p,1)`×8,
  `sbrg_set_pt_da_lookup_en(p,1)`×8, SMAC-learn, age, etc.
- For **multicast** it floods: `sbrg_set_unknown_multicst_fwd(p,1)`×8 (line 43632).
- For **unknown unicast** it sends to CPU only: `sbrg_set_unknown_unicst_fwd`
  loop→0 then `(0,1)` (CPU port).
- For **BROADCAST** it calls **NOTHING**. `sbrg_set_brdcst_fld_en`,
  `sbrg_set_brdcst_fwd_en`, `sbrg_set_pon_brdcst_flood_portmask`,
  `sbrg_set_dft_brd_vl_trans_pktdeal` are **never called** → they stay at cold
  reset 0 (live dump confirms 0x8300=0, 0x8304=0, 0x863c=0).

So in stock the broadcast bridge-flood mask is **empty**. The bridge does NOT
hand a broadcast frame a member-port destination. That is by design — broadcast
reaches the host purely by being **trapped to the CPU** (SPA pktdeal / pro_action
deal=1), after which the Linux/ONT bridge floods it in software. This is why
poking the SBRG flood registers (`0x8300`/`0x8304`/`0x82d4`/`0x863c`) had no
effect on your drop_PP: those registers were already irrelevant to the path stock
actually uses, and turning them on does not synthesize the missing
replication-engine wiring.

**The replicate-vs-drop decision is made upstream at SPA/CLA, not at PP/OPC:**
- deal=1 (TRAP) on the broadcast ptype slot → SPA marks the frame for the CPU
  queue → it gets a destination (CPU) → QMG hw_trap/sw_fwd → reaches CPU. NOT
  dropped at OPC.
- deal=0 (FORWARD) on that slot, with NO bridge flood mask and NO FDB hit (DA=
  ff:ff:ff never matches an FDB entry) → the frame has no trap destination AND no
  flood destination → it falls through every stage and OPC drops it as PP DROP.
  **This is exactly your `drop_PP +N` measurement.**

There is no "per-port broadcast receive-enable" or member/forward-mask that stock
programs to make autonomous flood happen. The chip *has* the substrate (VLAN
membership RAM + isolation rows — both programmed by mainline), but the
membership-flood path is not actually exercised in the current
trap-all-DSA-conduit configuration; just setting the SBRG registers does not
activate it (live-confirmed negative, `hw_broadcast_flood_re.md` Iter AM).

---

## 3. The complete stock PP-stage config under which broadcast "works"

"Works" = trapped to CPU + SW-flooded (the only thing stock does). The decisive,
decompiled stock config:

```c
/* SPA per-protocol pktdeal RAM (0x921d4300, reg67[1:0], +0x14/idx, per port):   */
/*   broadcast / ARP(0806) / ND / control protocol slots  = deal 1 (TRAP)        */
/*   (this is zx_pp_pro_actions[] / def_ptl_pkt_action; deal: 0=fwd 1=trap        */
/*    2=drop 3=copy). Leaving these at 1 is what makes broadcast reach the CPU.   */

/* SBRG/PP_BRG bridge (base phys 0x92388000) — broadcast flood DELIBERATELY OFF:  */
writel(0x00000000, pp + 0x8300); /* brdcst_fld_en / brdcst_fwd_en  = 0  (stock)  */
writel(0x00000000, pp + 0x8304); /* pon bcast flood portmask       = 0  (stock)  */
writel(0x00000000, pp + 0x863c); /* dft_brd / dft_unkuni vl_trans  = 0  (stock)  */
writel(0x015555ff, pp + 0x8340); /* unknown-unicast -> CPU only    (stock)       */
writel(0x00000001, pp + 0x8380); /* pt_tls = CPU port only         (stock)       */
/*  multicast IS flooded: sbrg_set_unknown_multicst_fwd(p,1) -> 0x82d4[31:24]=0xff */

/* OPC top (0x921da000) — scheduling only, NOT a forwarding knob:                 */
/*   0x921da004 = 0x00000055 (sp_rr), 0x921da054 = 0xb00, 0x921da060 = 0x280001c0 */
/*   (drop counters 0x921da040/44/48 are read-only, live 0).                      */
```

**There is NO register value that makes the stock PP/OPC stage autonomously
replicate broadcast to the LAN member ports — because stock never does that.** The
"complete config for broadcast" is: trap it (pktdeal=1) and let SW flood. Any
register address in the 0x921da0xx OPC block is the wrong target.

If autonomous HW flood is genuinely wanted (beyond what stock does), the substrate
to drive would be the per-VLAN membership RAM (PP_BRG ram_id 4: all LAN ports
action=3) + isolation rows "all-but-self" + the flood path being actually
activated — but this is the unsolved `zte-hw-forwarding-deadend` work and the
SBRG-register pokes alone are proven insufficient (Iter AM, AN).

---

## 4. The port1 connection — SAME counter, DIFFERENT root cause

port1 ingress frames "dying at drop_PP" and broadcast "dying at drop_PP" hit the
**same OPC PP-DROP bucket for the same structural reason (no valid destination
assigned upstream), but the upstream cause is different**:

- **port1 (SOLVED):** port1's frames passed SPA/SDET but were **not trapped to
  CPU** (the trap verdict was suppressed) because of **SPA `port_vlan_filter`
  (0x921d42ac + port*4, [5:0])** being left at a non-zero HW reset default
  (p1=0x26) instead of stock's 0. With the filter non-zero, port1's frames got no
  trap destination → fell through to OPC → PP DROP. **Fix (merged):**
  `zx_pm_spa_init` clears the whole port_vlan_filter ×10 table to 0
  (`port1_drops_at_PP_re.md` ★★★ SOLVED). So port1's drop_PP was a
  per-port *trap-verdict-suppressed* miss.

- **broadcast (this doc):** ALL ports' broadcast hits drop_PP under all-pktdeal=0
  because the *protocol* trap was globally removed and no flood-replication exists.
  It is a *config-removed-the-only-destination* miss, not a per-port verdict.

**Common mechanism, confirmed:** `drop_PP` = "OPC received a frame with no
disposition." Whether the missing disposition is caused by a suppressed per-port
trap verdict (port1) or a globally-removed protocol trap with no flood fallback
(broadcast), the terminal counter is the same 0x921da040. The lesson from port1
applies directly: **the lever is upstream (the trap-verdict / pktdeal assignment),
never the OPC drop counter itself.**

---

## 5. Stock vs mainline for the PP/broadcast path — what mainline must do

| item | mainline now | stock | verdict |
|---|---|---|---|
| **broadcast/ARP/ND pktdeal slots** | deal=1 (trap) by default; `zx_proto_fwd_all=1` forces ALL to 0 | deal=1 (trap) on bcast/control | **KEEP trapping broadcast.** The whole drop_PP problem appears only when these are forced to 0. Do NOT set forward-all. |
| `0x8300` brdcst_fld_en/fwd_en | written **0xFF/0xFF** in the older `zx_pp_brg_init` (`zx-eth-main.c:1240-1241`); set 0 in the newer path (line 2551) | **0** | **BUG: dueling init.** The 0xFF write (line 1240/1241) is wrong (stock=0; it caused the CPU-port broadcast hairpin). Ensure the 0 write wins / remove the 0xFF write. |
| `0x8304` bcast flood portmask | 0xFF (line 1241) vs 0 (line 2552) | **0** | same dueling-init bug; must end at 0. |
| `0x863c` dft_brd vl_trans | 0xaaaaaaaa (historical) / 0 | **0** | set 0 (stock); 0xaaaaaaaa is a translate action, not plain flood. |
| `unknown_multicst_fwd` 0x82d4[31:24] | not set | **0xff** | add if multicast flood wanted (stock floods unknown-mcast to all ports). |
| **autonomous broadcast replication** | none (relies on CPU trap + SW flood) | none (relies on CPU trap + SW flood) | **MATCHES stock.** Mainline is doing the right thing by trapping; the "all-0 + HW-flood" path is NOT something stock does and is blocked by the open HW-forwarding-deadend. |
| OPC block 0x921da0xx | scheduler defaults | 0x55/0xb00/0x280001c0 | not forwarding-related; no action needed for broadcast. |

**What mainline must NOT do:** chase a PP/OPC register to "enable broadcast flood."
There isn't one. The OPC PP-DROP is downstream of the decision.

**What mainline SHOULD do (matches stock, already mostly correct):**
1. **Keep broadcast/ARP/ND trapping to the CPU** (pktdeal deal=1 on those slots) —
   the broadcast then reaches the bridge and SW-floods. This is stock's actual
   behaviour and avoids drop_PP entirely. Do not run `zx_proto_fwd_all=1`.
2. **Fix the dueling broadcast-flood init**: remove/override the `0xFF` writes to
   `pp+0x8300` / `pp+0x8304` (`zx-eth-main.c:1240-1241`) so they stay 0 like stock
   (prevents the CPU broadcast hairpin).
3. If TCP-data HW-forward is wanted alongside, flip ONLY the TCP-data ptype slots
   to deal=0 (surgical), **leaving broadcast/control trapping** — never forward-all
   (per `pktdeal_override_re.md` §E use-case 1).
4. Autonomous HW broadcast flood (no CPU) is a separate, unsolved effort
   (`zte-hw-forwarding-deadend`): it requires activating the membership-flood
   replication path, which the SBRG/OPC registers alone do not turn on
   (live-proven). It is NOT achievable by any 0x921da0xx write.

---

## Confidence

- **drop_PP (0x921da040) = OPC-top "PP DROP" reason counter, terminal stage:**
  HIGH. Bit-exact from the tm.ko dumper (`fpga_read_reg(0x76810)` → printk
  "opc_top pp drop cnts"), widx→phys arithmetic, and the DN dumper's "PP DROP"
  label; live stock value 0.
- **Stock does NOT program any autonomous broadcast replication; broadcast reaches
  host via CPU trap + SW flood:** HIGH. `tm_pon_pp_brg_initial` never calls any
  broadcast-flood setter (decomp 43579-43644); live dump 0x8300/04/863c=0; SBRG
  pokes had no effect (Iter AM/AN).
- **Broadcast under all-pktdeal=0 hits drop_PP because the trap (its only
  destination) was removed and no flood path exists:** HIGH. Matches the exact
  counter behaviour (drop_PP == MAC RX, RED/DSCH/QMG flat) and the pipeline order.
- **port1 and broadcast share the OPC PP-DROP counter for the same structural
  reason (no disposition), different upstream cause; port1 fixed via SPA
  port_vlan_filter:** HIGH (port1) — merged + verified; the linkage is structural.
- **No PP/OPC register enables broadcast flood; the lever is the upstream
  SPA/pro_action trap (or the unsolved flood-replication wiring):** HIGH for "not
  in OPC"; the flood-replication activation itself remains the open
  HW-forwarding-deadend item.
