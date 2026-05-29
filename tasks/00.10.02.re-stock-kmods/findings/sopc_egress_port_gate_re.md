# SOPC egress-port gate for a CPU-source frame: QMG sw_fwd → send2smacN (2026-05-28)

DECOMP + LIVE cross-check. Goal (task): find the register(s) that make the
fabric assign an egress port so `sopc_send2smacN` fires for a CPU/host-sourced
frame, the stock-vs-mainline delta, whether mainline's sw_fwd is forward-vs-trap,
and a poke-test. Companion to `sopc_spa_cpu_egress_re.md`,
`stock_live_egress_oracle_re.md`, `dsch_drop_cpu_egress_re.md`,
`pipeline_counter_map.md`, `cpu_egress_routing_re.md`.

Every register claim is tied to a decomp line and/or a live-dump line
(`regs/stock_eth_2mib.txt`). Confidence stated per claim. Addr rule:
`fpga_read_reg(id)=*(0x92000000+id*4)`; e->base=phys 0x921c0000; phys=0x921c0000+off.

---

## TL;DR

1. **SOPC has NO source-gated egress-port matrix.** CROSS-CHECKED (live + decomp,
   HIGH). `sopcRegTable` (zx-fpga-reg-tables.h:616) covers only crc_pad
   (0x921d9004), smac delay/half/ready (0x921d9038) and sp_rr (0x921da000) — none
   is a per-(source,dest) egress pick. `tm_pon_npp_sopc_initial` (tm:43242) sets
   only crc_pad=0 ×5 + sp_rr=0. SOPC emits `send2smac[N]` for whatever egress
   port the *upstream forwarding decision* placed the frame's queue on; there is
   no spa/dpa knob to "turn on send2smacN" per source. (`0x921d91c8=0x1f`,
   `0x191cc..dc=0x10` are SOPC **status** reads via fpga-id 0x76471/0x76473 at
   tm:46781 — read-only HW state, NOT a config gate. Red herring.)

2. **mainline's QMG decision is sw_fwd, identical to stock — NOT a trap.**
   CROSS-CHECKED (live, HIGH). `stock_live_egress_oracle_re.md`: while stock
   egresses 0x257 frames out MAC2, **QMG sw_fwd (0x9234c044) climbs in lockstep**;
   **hw_fwd (0x9234c048)=0 and hw_trap (0x9234c04c)=0** — on BOTH stock and
   mainline. So Q3 is settled: a CPU frame is *software-forwarded*, not trapped;
   "sw_fwd vs hw_fwd" is a dead end. `qmg_set_qmg_trap_cfg` (tm:32924) is a single
   GLOBAL 2-bit value, not per-port — QMG does not make a per-source fwd/trap pick.

3. **The real divergence is the egress SUBMISSION PATH, not a config register.**
   CROSS-CHECKED (live, HIGH). Stock egresses CPU→LAN with the **UP/DN/IDM DMA
   rings all untouched**: `TM[0x10054]` kick / `0x10058` consume / `0x1005c`
   cursor all read **0** the entire time it pushes 0x257 frames
   (`stock_live_egress_oracle_re.md:37-39`). Stock injects the frame as a pure
   *software-forwarded fabric packet* (BMU-buffer + fabric inject → QMG sw_fwd →
   SOPC → MAC), per `pon_tm_data_raw_send`/`pon_tm_bmu_alloc_bp`. Mainline builds a
   16-B desc and **kicks the UP ring (`TM[0x10054]=1`)**; that frame *does* reach
   QMG sw_fwd (`txtest`: +5) but is consumed by the ring path and never feeds the
   SOPC egress crossbar. **This is why send2smacN stays 0 with sw_fwd nonzero.**

---

## (a) The register(s) that gate send2smacN for a source-CPU frame

There is **no single egress-port-select register**. The egress port N for
`send2smac[N]` is the destination resolved by the PP_BRG DA-lookup (FDB `pbm`
byte; `dump_mac_data` plat:4631 shows entry byte0 = pbm) for a learned unicast,
or the flood mask for unknown-unicast/broadcast. The per-source "allowed egress"
is the **port-isolate** matrix `PP[0x83c0+phys_port*4]` (plat:4606
`pon_pp_port_isolate_part_1`). Live stock = {fe,fd,fb,f7,ef,df,ff,ff}
(0x923883c0..dc) = `~BIT(self)` → every source may egress to MAC2. **Mainline
already matches this** (`live_vs_live_diff_data.md`, oracle line 118). So the
allowed-egress matrix is NOT the gate.

Port numbering (load-bearing): `getPort` (tm:43494) remaps logical→physical
{0→1,1→2,2→3,3→4,4→5,5→0,6→6,7→7}. All per-port bitmaps (isolate, vl_chk,
transfer_en, smac_look) are indexed by **physical** port. CPU = logical 5 =
physical 0; LAN ports = physical 1..5.

**Conclusion:** the egress-port assignment machinery is config-correct in
mainline. send2smacN is 0 because the frame is on the DMA ring, not the fabric
software-forward path that feeds SOPC.

## (b) Stock vs mainline — exact deltas (config layer)

The config layer is ~stock-faithful. Remaining non-dynamic SBRG/PP_BRG diffs
(oracle §"SBRG", `live_vs_live_diff_data.md`), all LOW-odds for the gate but real:

| phys | what (decomp) | stock-LIVE | mainline | cite |
|---|---|---|---|---|
| 0x92388008 b0-7 | `sbrg_set_inport_vl_chk_en` (sbrag reg10) | **0xdf** | 0x00 | tm:5390 / table reg10 |
| 0x92388008 b8-15 | `sbrg_set_outport_vl_chk_en` (sbrag reg11) | **0xdf** | 0xff | tm:5487 |
| 0x9238863c | (mcast vl-trans blob) | **0** | 0xaaaaaaaa | oracle line 120 |

NB three writers touch PP[0x8008]: `pon_pp_brg_init` (plat:5379) writes 0xff00;
`tm_pon_pp_brg_initial` (tm:43596-97) zeroes BOTH bytes via the per-port
`tm_vlan_check_ena_set(p,0,0)`+`(p,1,0)` loop; then runtime (cspd
`sw_vlan_set_port_transparent`, switch:7916) sets them to 0xdf (all ports except
physical 5). Mainline replays only the first (0xff00). **out-port VLAN-check is
ON for the egress LAN port in BOTH** (bit for MAC2's phys port is set in 0xff and
0xdf alike), so this is unlikely to be the egress gate — but it is a genuine
config drift worth aligning. (Decomp-inferred semantics; the in/out-port
VLAN-check *effect* on a CPU frame is not live-proven.)

The big substantive delta is the **path** (§3 above), not these registers.

## (c) sw_fwd = forward, not trap — how to tell

Read the three QMG counters during TX (already mapped, free-running readl):
`QMG sw_fwd 0x9234c044`, `hw_fwd 0x9234c048`, **`hw_trap 0x9234c04c`**. On stock
*and* mainline, hw_trap stays 0 while sw_fwd counts — so mainline is NOT trapping
to CPU; it forwards exactly like stock. The CPU-loopback "storm" seen under ping
is a *broadcast/ARP* hairpin (RX-side), separate from this egress gate
(`txtest_clean_trace_dsch_fixed.md`: clean unicast `txtest` frame does NOT loop —
it just vanishes after DSCH). DSCH drop is FIXED (shaper-RAM init now in
`zx_sch_init`, drop_DSCH=0 confirmed live).

## (d) Prioritized poke-test

**P1 (highest) — stop using the UP ring; replicate the fabric software-forward.**
This is a code change, not a single poke (the inject is a BMU-alloc + fabric
write, not a ring kick). The poke-confirmable *negative* first: during `txtest`,
read `0x921d0054`/`0x921d0058`/`0x921d005c` — mainline kicks 0x10054 and advances
0x1005c; **stock leaves all three 0** while egressing. That mismatch is the proof.
Then port `pon_tm_data_raw_send` (plat:6596) faithfully: BMU-alloc BP
(`0x921c8014|=1`; read BP from `0x921c800c`), copy frame to `BP[bp]+16`, build the
16-B desc with the GEM nibble `((lan_up_port+0x28)&0x3f)<<4`=0x2c0, and submit via
the **fabric software-forward** (NOT `TM[0x10054]`). Watch `0x9234c044` (sw_fwd),
`0x921d9164` (send2smac2), `0x92280718` (MAC2 TX) move in lockstep as on stock.

**P2 (cheap, do alongside) — align the two config drifts and re-`txtest`:**
```
poke 0x92388008 0x0000dfdf      # in/out-port vl-chk = stock 0xdfdf (was 0xff00)
poke 0x9238863c 0x00000000      # stock leaves 0 (mainline wrote 0xaaaaaaaa)
```
Then `txtest 4`; watch 0x921d9164 / 0x92280718. LOW odds of being the gate but
both are genuine stock-vs-mainline deltas and free to test.

**P3 (secondary) — per-port "closed" gate.** `tm_port_status_set(p,0)` →
`greg_set_port_closed(physport,1)` closes all ports at init (tm:43166-70,
`tm_pon_npp_greg_initial`), reopened on link-up. Live stock = OPEN (greg closed
regs 0x9238c14c..0x9238c164 all read 0). If mainline leaves the egress port
CLOSED (nonzero) SOPC won't emit. Verify those phys read 0; if not, clear them.
Decomp-inferred mapping (port→regId port+0x39 in gregRegTable, tm:22421); the
exact per-port reg is gregRegTable reg 57+ (base_off 0xe3053+ → phys 0x9238c14c+),
widths vary, so confirm by reading before poking.

---

## What I could NOT pin / honesty
- No single "egress-port-select" register exists; the gate is architectural (the
  DMA-ring vs fabric-software-forward path). The exact fabric-inject write stock
  uses (the thing that bumps QMG sw_fwd with TM[0x10054]=0) is not isolated to one
  MMIO in the decomp — `pon_tm_data_raw_send` ends at `soft_insert_tx_1desc` which
  *does* kick a ring (tm:6239 0x10054 / 6242 0x10064) in the decomp, yet the live
  oracle shows the ring counters at 0. That contradiction (decomp says ring kick,
  live says no ring) is UNRESOLVED — likely a second slot-B-stock TX path or a
  fabric-inject the decomp pretties into the ring kick. Resolving it needs a live
  before/after diff across the BMU + fabric-inject window during a real egress
  (the oracle method extended), per `stock_egress_trace_empirical_re.md`.
- PP[0x8008] vl-chk *effect* on a CPU frame is decomp-inferred, not live-proven.
