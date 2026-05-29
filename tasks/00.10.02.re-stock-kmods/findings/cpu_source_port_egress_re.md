# CPU/host source-port ALLOWED-EGRESS config — the G.988 port-mapper (PM) gate (2026-05-28)

DECOMP + LIVE cross-check. DECOMP/ANALYSIS ONLY — did not touch device/build/git.

**New experiment that drives this doc:** a CPU-sourced frame NEVER reaches any
physical MAC wire (host tcpdump = 0 device-originated frames, INCLUDING
broadcast); the device's own ARP reply comes back to the CPU as
"TM RX ingress=2 delivered" — i.e. the fabric forwards a CPU-sourced frame
**back to the CPU**, never out a physical egress port (MAC2). Host is confirmed
on MAC2 (MAC2 RX-ok counts host frames, MAC2 TX-ok stays 0). So the gate is the
**source-port forwarding / allowed-egress for the CPU/host source port**.

Companion to: `sopc_spa_cpu_egress_re.md`, `sopc_egress_port_gate_re.md`,
`arch_survey_cpu_egress.md`, `idm_cpuport_fabric_forward_re.md`,
`cpu_egress_routing_re.md`.

Addr rule: `fpga_read_reg(id)=*(0x92000000+id*4)`; e->base=phys 0x921c0000;
tm_base=0x92340000. `tmOnuRegWrite(regId,val,idx,table)` → reg-id =
`table[regId].base_off + idx*stride`; phys = `0x92000000 + reg_id*4`; RMW with
table mask/shift. Reg-table base_offs read from
`linux-v6.6/.../zx-fpga-reg-tables.h` (`zx_pmregtable` @365, `zx_sparegtable`
@629). Every claim tied to a decomp line + a live line in
`regs/stock_eth_2mib.txt`. Confidence per claim.

---

## TL;DR — the missing config and the #1 poke-test

**Prior RE chased the WRONG layer.** The SBRG per-source attributes
(transfer_en, smac_look, da_lookup, port-isolate `PP[0x83c0]`) ARE stock-faithful
in mainline (confirmed in `sopc_*_re.md`). But there is a SECOND, ENTIRELY
SEPARATE source→allowed-egress mechanism that **mainline never programs at all**:
the **G.988 Port-Mapper (PM) subsystem** + the **SPA source-port match
classifier**, both run by stock in `tm_pon_npp_initial` and BOTH skipped by
mainline.

Stock `tm_initial → tm_pon_npp_initial` (tm:43444-43467) calls, in order:
`...spa_initial()` (tm:43271) **and** `...pm_initial()` (tm:43376). Mainline's
`zx_npp_init` (zx-eth-main.c:1256) replicates only the bare one-liner
`NPP[0x141c0]=0` (`pon_npp_spa_init`, plat:3347) and **omits the entire SPA-match
classifier and the entire PM/G.988 forwarding-rule table**. Grep of the whole
mainline `zte/` tree: ZERO refs to `pm_set`, `g988`, `in_port_rule`,
`out_port_rule`, `inport_equal`, `match_mode`, `matchram`, `hashram`,
`set_port_rule` (confirmed empty). The only SPA call mainline keeps is
`spa_set_enty_pktdeal_cfg` / `spa_set_onu_mac_addr` (zx-eth-main.c:1109,1857) —
NOT the source-port forwarding decision.

**The PM/G.988 table is the chip's per-source "allowed in-port/out-port pair +
inport==outport handling + cpu-not-drop" matrix** — the exact SPA / source→egress
gate the task is asking for. On stock it is configured; on mainline it is in
power-on-default state, and the default behavior is "loop CPU-sourced frames back
to CPU", matching the experiment exactly.

### POKE TEST #1 (in window; decomp+live grounded) — set inport_equal_outport & cpu_not_drop on the PM ctrl reg
```
mem  0x921e0054                 # PM g988 ctrl. mainline expected NOT 0xc0 (default 0)
poke 0x921e0054 0x000000c0      # stock-live value: bit4 cpu_not_drop=0,
                                # bits7-8 inport_equal_outport_staen=1 (=0xc0)
```
Then re-run the ARP/broadcast test and watch MAC2 TX-ok (0x92280718) +
`sopc_send2smac2` (0x921d9164). Stock-live for this reg is **`0x921e0054 =
0x000000c0`** (grep confirmed). Decode (zx_pmregtable):
- reg4 cpu_drop_staen  : base 0x78015 shift5 → bit5 = 0
- reg5 cpu_not_drop_staen: base 0x78015 shift4 → bit4 = 0  (stock set 0; "do not drop")
- reg0x10 inport_equal_outport_staen: base 0x78015 mask0x3 shift7 → bits7-8 = `0xc0>>7 = 1`
matches stock `tm_pon_npp_pm_initial` (tm:43407-43408):
`zte_api_set_g988_cpu_not_drop_staen(0); zte_api_set_g988_inport_equal_outport_staen(1);`

If that alone doesn't open egress, also enable the out-port forwarding rule that
stock installs for the bridge port (POKE TEST #2 below).

---

## The SPA / PM source-port machinery (decomp)

### A. PM (Port-Mapper / ITU-T G.988 MAC-bridge) — the in/out-port forwarding matrix
`tm_pon_npp_pm_initial` (tm:43376) is the stock initializer. It:
1. Loops i=0..7: `pm_set_in_port_rule_valid(i,i,0)` + `pm_set_out_port_rule_valid(i,i,0)`
   — sets ALL 16 per-port forwarding rules INVALID (tm:43391-43395).
2. `pm_set_g988_mode(0,0)/(1,1)/(2,3)` (tm:43397-43399) — 3 rule-match modes.
3. `zte_api_set_port_rule(&{1,1,5})` (tm:43404-43406). Trace:
   `tm_pm_port_rule_set` (tm:47679) zeroes a 3-word struct, sets
   `{*=1, [1]=1, [2]=0}`, → `pm_set_port_cfg({1,1,0})` (tm:23422). Since `*=1`
   (out-port branch): `pm_set_out_port_rule_valid(0,0,1)` — **enables the
   OUT-port forwarding rule for physical port 0, valid_en=1.**
4. `zte_api_set_g988_cpu_not_drop_staen(0)` (tm:43407).
5. `zte_api_set_g988_inport_equal_outport_staen(1)` (tm:43408).

**Register map (phys), zx_pmregtable + tmOnuRegWrite:**
| stock setter | reg-id | base_off | phys | encoding | stock-LIVE |
|---|---|---|---|---|---|
| pm_set_g988_mode (tm:22927) | 3 | 0x78015 | 0x921e0054 b2-3 | mask3 sh2 | `0xc0` → mode bits 0 |
| pm_set_g988_cpu_drop_staen (22966) | 4 | 0x78015 | 0x921e0054 b5 | 1b sh5 | 0 |
| pm_set_g988_cpu_not_drop_staen (23001) | 5 | 0x78015 | 0x921e0054 b4 | 1b sh4 | 0 (stock=0) |
| pm_set_g988_inport_equal_outport_staen (23036) | 0x10 | 0x78015 | 0x921e0054 b7-8 | mask3 sh7 | **1** |
| pm_set_in_port_rule_valid (23077) | 6 | 0x78060 | 0x921e0180+idx*4 | val=`port|en<<3`, idx=cfg | all idx = port, en=0 |
| pm_set_out_port_rule_valid (23163) | 7 | 0x78068 | 0x921e01a0+idx*4 | val=`port|en<<3`, idx=cfg | **idx0=0x08 (port0,en=1)**; idx1-7 en=0 |
| g988 rule RAM (pm_add_g988_rule, 23636) | 0xd | 0x78092 | 0x921e0248+idx*4 | bit20=valid,b18-19 in,b15-17 out | all 0 (no explicit rule installed at boot) |

Live confirmation (grep `regs/stock_eth_2mib.txt`):
- `921e0054 000000c0` ✓ (inport_equal_outport=1, cpu_not_drop=0)
- `921e01a0 00000008` ✓ (out-port rule idx0 = port0, valid_en bit3 SET) — the
  ONE enabled forwarding rule; idx1..7 = `0x1..0x7` (valid_en=0).
- `921e0180..019c = 0x0..0x7` (all in-port rules valid_en=0).
- g988 rule RAM `921e0248+` all 0.

Semantics (from `pm_check_g988_rule` tm:23579 + `pm_add_g988_rule` tm:23616):
the PM block is the chip's **(in_port, out_port) forwarding-pair authorizer**
plus an **inport==outport (hairpin) handler** and a **cpu-drop/cpu-not-drop**
policy. This is the GPON-SoC equivalent of the DSA "CPU source-port → allowed
egress matrix" (`arch_survey_cpu_egress.md` Mechanism A). With the PM block in
power-on default (mainline), the source→egress authorization for the CPU port is
absent → the fabric's fallback is to keep the frame on the CPU/ingress side =
**loop to CPU** = the exact symptom.

### B. SPA source-port match classifier
`tm_pon_npp_spa_initial` (tm:43271): per-port `spa_set_up_reg_pkt_en(i,1)` /
`spa_set_dn_reg_pkt_en(i,1)` (i to 0x53), `spa_set_pt_802x_trap_en`,
`spa_set_port_dft_pri`, `spa_set_port_pkt_filter`, then **`spa_set_match_mode(1)`**
(tm:43328) + loads the SPA **matchram** (`spa_set_matchram`, 11 entries from
`_LANCHOR1`) and **hashram** (`spa_set_hashram`, 8 entries). This is the
source-port→behavior CAM that classifies an ingress frame by its source port
before the PM forwarding decision.

`spa_set_match_mode(1)`: `tmOnuRegWrite(0x12, 1, 0, spaRegTable)` (tm:26725).
reg18 base_off 0x7501f mask0x3 → phys **0x921d407c**. Stock-LIVE `921d407c
00000001` ✓ (match enabled). Mainline leaves this at default 0 (match disabled).
Stock-LIVE also shows the device's own MAC in the SPA match-RAM:
`921d4120 470f4264 / 921d4124 0000f4f6` = `f4:f6:47:0f:42:64`.

`pon_npp_spa_init` bare reset = `NPP[0x141c0]=0` → phys **0x921d41c0**; mainline
DOES replicate just this (zx-eth-main.c:1278, `NPP_REG_SPA_INIT 0x141C0`),
stock-LIVE `921d41c0 00000000` ✓ — but the bare reset is NOT the classifier
config; the matchram/match_mode load (above) is, and mainline omits it.

---

## What mainline OMITS (the divergence)

Mainline `zx_npp_init` (zx-eth-main.c:1256-1300) replicates the NPP/IDM/SMAC
one-liners and `NPP[0x141c0]=0`, but **never calls the equivalents of
`tm_pon_npp_spa_initial` (SPA matchram + `spa_set_match_mode(1)`) or
`tm_pon_npp_pm_initial` (the entire G.988 PM forwarding-rule + inport_equal +
cpu_not_drop config).** Tree-wide grep: zero refs to any PM/g988/match-mode
symbol. So the per-source allowed-egress authorization that lets a CPU-sourced
frame egress a physical port is in power-on-default state → frames loop to CPU.

This is independent of (and additional to) the earlier-flagged
`PON_PP_TM_CFG 0x923a001c` bit29 omission (`idm_cpuport_fabric_forward_re.md`):
that gate governs "CPU/WAN port → TM fabric accept" (frame reaching QMG at all);
the PM/SPA gate here governs "once in the fabric, which egress port is
authorized for a CPU-sourced frame". The new experiment (frame DOES reach CPU /
loops, broadcast also blocked) points at THIS (egress-authorization) layer, not
the TM-accept layer — broadcast floods independent of FDB but is still blocked,
which is the signature of a source-port egress-authorization gate, not FDB.

---

## Prioritized poke-tests (all phys in [0x921c0000, 0x923c0000))

**P1 (highest) — PM ctrl: inport_equal_outport + cpu_not_drop.**
```
poke 0x921e0054 0x000000c0      # stock-live; inport_eq_outport=1, cpu_not_drop=0
```
Re-test broadcast + ARP reply; watch MAC2 TX-ok 0x92280718 and send2smac2
0x921d9164. Cheapest single write; matches the exact stock value.

**P2 (high) — enable the out-port forwarding rule stock installs.**
out_port_rule_valid is RAM behind reg7 (base 0x78068, idx-strided). The plain
MMIO at `0x921e01a0` (idx0) reads the readback; the indirect write semantics use
the same window. Replay `pm_set_out_port_rule_valid(0,0,1)`:
```
poke 0x921e01a0 0x00000008      # idx0: port0 | valid_en(bit3)  — matches stock-live
```
If the bridge/host egress port is NOT physical 0, also enable the rule for the
host's physical port. Port remap `getPort`/`tm_pm_port_get` (tm:43494, 47640):
logical→physical {0→1,1→2,2→3,3→4,4→5,5→0,6→6,7→7}. CPU = logical 5 → physical 0
(the one stock enables). The LAN/MAC ports are physical 1..5. **Caveat (stated
honestly): which physical-port index corresponds to MAC2/host on THIS unit is not
fully nailed from the decomp alone — verify by reading `0x921e01a0..01bc` live on
mainline, find which idx differs from stock, and set valid_en (bit3) on the
host's egress-port idx.** Confidence MEDIUM on the exact index, HIGH that the
mechanism (out-port-rule-valid + inport_equal_outport) is the gate.

**P3 (do alongside) — SPA match enable.** If P1+P2 move send2smac2 but the
classifier still mis-sorts the CPU source:
```
poke 0x921d407c 0x00000001      # spa_set_match_mode(1), stock-live = 1
```

**P4 (already-flagged, complementary, NOT the new symptom's cause) —**
`PON_PP_TM_CFG`: `poke 0x923a001c 0x23200000` (stock-live 0x21200000→0x23200000).
This is the "reach-QMG" gate; per the new experiment the frame already reaches
CPU, so P1/P2 (egress authorization) rank above it for THIS symptom.

---

## Confidence + honesty
- **HIGH**: mainline omits the entire SPA-match + PM/G.988 forwarding-rule init
  (tree grep empty; stock runs both in `tm_pon_npp_initial`).
- **HIGH**: the PM block IS a source→(in/out)-port forwarding authorizer with an
  inport==outport hairpin handler and cpu-drop policy (decomp of
  pm_set_*/pm_add_g988_rule/pm_check_g988_rule).
- **HIGH**: live stock values for 0x921e0054 (0xc0), 0x921e01a0 (0x08),
  0x921d407c (1), 0x921d41c0 (0) all match the decomp'd stock writes.
- **MEDIUM/UNRESOLVED**: which physical-port index = MAC2/host (P2). The decomp
  gives the remap but not a hardware-pinout-to-MAC binding; resolve by a live
  mainline-vs-stock diff of `0x921e0180..01bc`.
- **NOT proven on the wire**: the *effect* of the PM authorization on a CPU frame
  is decomp-inferred. The new experiment (loop-to-CPU, broadcast also blocked) is
  the behavioral evidence that fits this gate better than the previously-blamed
  MAC-enable / DMA-ring / FDB layers (all of which prior live work showed
  stock-faithful or already-correct).

---

## Sources
- `decomp_all_tm.c`: tm_pon_npp_initial @43444, tm_pon_npp_spa_initial @43271,
  tm_pon_npp_pm_initial @43376, pm_set_g988_mode @22911,
  pm_set_g988_cpu_not_drop_staen @22992, pm_set_g988_inport_equal_outport_staen
  @23027, pm_set_in_port_rule_valid @23061, pm_set_out_port_rule_valid @23147,
  pm_set_port_cfg @23422, pm_check_g988_rule @23579, pm_add_g988_rule @23616,
  pm_set_g988_cfg @23722, spa_set_match_mode @26715, tm_pm_port_rule_set @47679,
  tm_pm_g988_rule_set @47749, getPort @43494, tm_pm_port_get @47640,
  tmOnuRegWrite @35358 (entry layout +8 base / +0xc mask / +0x10 shift / +0x14
  stride), tm_initial @47125, zte_api_set_port_rule @58693.
- `decomp_all_plat_zxylzb_9128S.c`: pon_npp_spa_init @3347 (NPP[0x141c0]=0),
  pon_pp_port_isolate.part.1 @4606.
- `linux-v6.6/.../zx-fpga-reg-tables.h`: zx_pmregtable @365 (reg-ids 3/4/5/6/7/
  0xd/0x10), zx_sparegtable @629 (reg18=match_mode @0x7501f).
- `linux-v6.6/.../zx-eth-main.c`: zx_npp_init @1256 (NPP_REG_SPA_INIT 0x141C0
  @1278; no PM/SPA-match init), zx_pp_brg_init @2339; tree grep for
  pm/g988/match_mode/port_rule = empty.
- `regs/stock_eth_2mib.txt`: 921e0054=0xc0, 921e01a0=0x08 (idx0 out-port-rule
  valid), 921e0180..019c, 921e01a4..01bc, 921e0248+ (g988 RAM, all 0),
  921d407c=1 (match_mode), 921d4120/4124 (own MAC f4:f6:47:0f:42:64 in SPA RAM),
  921d41c0=0; 923a001c=0x21200000.
