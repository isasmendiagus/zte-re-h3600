# port1 MAC→SPA admit gate — SPA up/dn pps_en + PM out-rule, mainline vs stock (RE)

**Status: NEW LEAD (static RE + stock-live diff, untested on HW). Date: 2026-05-31. Branch: eth-dsa.**

Follow-up to `port1_sdet_ingress_gate_re.md` (its LIVE TEST section localized the silent
port1 drop to the **SMAC→SPA admit stage**, UPSTREAM of SDET: MAC1 RX-ok=88, SDET uni1
transport=2 vs uni2/3=229/230, SDET drop=0 → frames never reach SDET). This pass compares,
value-by-value, exactly what mainline `zx_pm_spa_init` writes vs what stock writes and what the
stock unit reads live, for the entire SPA up/dn receive-admit path.

---

## 1. Address model (confirmed)
- `tmOnuRegWrite(reg_id, val, idx, table)` (decomp_all_tm.c:35358) is a **RMW**:
  `phys = 0x92000000 + (base_off + stride*idx)*4`, masked/shifted per the table entry
  (`+8`=base_off words, `+0xc`=mask, `+0x10`=shift, `+0x14`=stride). 28-byte entries.
- `zx_sparegtable` base_offs (zx-fpga-reg-tables.h:629). SPA block = phys 0x921D4xxx
  (= e->base 0x921C0000 + 0x14xxx; word 0x75000 → 0x921D4000).
- mainline `npp_write(e, off, val) = writel(val, e->base + off)`; NPP-rel off = phys − 0x921C0000.

## 2. `spa_set_up_reg_pkt_en(entry, 1)` fully decoded (decomp_all_tm.c:26271)
Writes **reg_id 0** (base_off 0x75000), one of 3 sub-words selected by the entry range, setting
bit `entry`. With enable=1 the Ghidra `bVar1` collapses to the literal sub-index:
- entry 0x00–0x1f → idx0 → **0x921D4000** bit(entry)        → mainline 0x14000=0xffffffff ✓
- entry 0x20–0x3f → idx1 → **0x921D4004** bit(entry−0x20)   → mainline 0x14004=0xffffffff ✓
- entry 0x40–0x4d → idx2 → **0x921D4008** bit(entry−0x40)   → mainline 0x14008=0x00003fff ✓ (14 bits)

**Mainline's 3 bulk writes bit-exactly replicate stock's 78-entry `spa_set_up_reg_pkt_en(0..0x4d,1)`
loop.** Cross-checked against stock-live `stock_eth_2mib.txt`:
`921d4000 ffffffff / 921d4004 ffffffff / 921d4008 00003fff` — identical. **SPA up pkt_en is NOT
the bug; the leading "wrong/short mask" hypothesis is DISPROVEN.** Same for dn pkt_en
(0x14040/44/48 = ffffffff/ffffffff/0007ffff, matches `spa_set_dn_reg_pkt_en(0..0x52,1)`).
`spa_set_match_mode(1)` → 0x1407c=1 also matches (stock 921d407c 00000001).

## 3. THE DIFF — registers stock has set that mainline NEVER writes
Direct grep of stock-live `regs/stock_eth_2mib.txt` for the SPA block vs the 8 writes in
`zx_pm_spa_init` (zx-eth-main.c:4711-4718):

| phys | stock-live | mainline | reg_id / setter | meaning |
|---|---|---|---|---|
| 0x921D4000 | ffffffff | 0xffffffff ✓ | 0 idx0 / up pkt_en[0x00-0x1f] | per-entry RX pkt enable |
| 0x921D4004 | ffffffff | 0xffffffff ✓ | 0 idx1 / up pkt_en[0x20-0x3f] | |
| 0x921D4008 | 00003fff | 0x00003fff ✓ | 0 idx2 / up pkt_en[0x40-0x4d] | |
| **0x921D400C** | **ffffffff** | **— (unset)** ✗ | **2 idx0 / `spa_set_up_reg_pps_en`[0x00-0x1f]** | **per-entry up PPS/policer enable** |
| **0x921D4010** | **3fffffff** | **— (unset)** ✗ | **2 idx1 / `spa_set_up_reg_pps_en`[0x20-0x3d]** | (30 bits = 0x20..0x3d) |
| 0x921D4040 | ffffffff | 0xffffffff ✓ | 1 idx0 / dn pkt_en | |
| 0x921D4044 | ffffffff | 0xffffffff ✓ | 1 idx1 / dn pkt_en | |
| 0x921D4048 | 0007ffff | 0x0007ffff ✓ | 1 idx2 / dn pkt_en | |
| **0x921D404C** | **ffffffff** | **— (unset)** ✗ | **3 idx0 / `spa_set_dn_reg_pps_en`** | per-entry dn PPS enable |
| **0x921D4050** | **ffffffff** | **— (unset)** ✗ | **3 idx1 / `spa_set_dn_reg_pps_en`** | |
| 0x921D4054 | 03ff05dc | RMW \|=0x03000000 (partial) | direct 0x75015 | b24/25 set; low bits (05dc) left at HW default |
| 0x921D407C | 00000001 | 0x1 ✓ | 0x12 / match_mode | |

`spa_set_up_reg_pps_en` (decomp_all_tm.c:26373) writes **reg_id 2** (base 0x75003 → 0x921D400C
idx0, 0x921D4010 idx1), setting bit `entry` for entries 0..0x3d. `spa_set_dn_reg_pps_en` →
reg_id 3 (0x75013 → 0x921D404C/4050). **No caller exists in the tm decomp** — stock sets these
in U-Boot / another module, so they are EXACTLY the kind of register mainline can silently miss.
The names ("up/dn reg PPS enable") and their position next to the pkt_en words strongly indicate
a second per-entry receive-admit/policer-enable that must be ON in parallel with pkt_en. If the
HW reset default is 0 (disabled) and these gate the same per-entry RX as pkt_en, then a frame
whose SPA entry has pkt_en=1 but pps_en=0 (mainline) is admitted by one stage and dropped/policed
by the other — silently, with no SIPC/SDET drop counter (SDET never sees it), which is the exact
observed signature.

## 4. Why this could be port1-specific (the entry-mapping mechanism)
The SPA pkt_en/pps_en bitmaps are **per-ENTRY (per matched rule), not per-physical-port** — 78
pkt_en bits, 62 pps_en bits, not 8. A frame's entry is chosen by the SPA match/hash RAM
(`spa_set_matchram`/`spa_set_hashram`, ram_id 0/5, content-match on MAC/VLAN). So "all-ones
pkt_en + zero pps_en" does NOT uniformly drop all ports — it drops only frames that resolve to an
entry where the two bitmaps disagree. Ports 0/2/3 and port1 (regport2) resolve to **different
entries** via the match/hash RAM (different source MAC / per-port rule), so a stage that is
enabled for ports 0/2/3's entries but not port1's entry produces a config-invisible, single-port
silent drop. This is the only mechanism found that is consistent with byte-identical per-port
config yet port1-only failure at MAC→SPA.

**Caveat (MEDIUM):** I could not prove from the decomp that pps_en is a hard RX gate (vs. a
policer that only drops over-rate) nor that its reset default is 0. The stock-live value
(ffffffff/3fffffff = "all entries enabled") shows stock deliberately turns it fully ON; mainline
leaving it at an unknown HW default is the risk. This must be confirmed by the live read in §6.

## 5. Other mainline-vs-stock SPA/PM gaps found (ranked lower)
- **PM out-port rules only idx0 primed.** Stock `tm_pon_npp_pm_initial` (decomp:43376) runs
  BOTH `pm_set_in_port_rule_valid(i,i,0)` AND `pm_set_out_port_rule_valid(i,i,0)` for **all i=0..7**
  (reg_id 6 / reg_id 7), then `zte_api_set_port_rule` sets out idx0=0x08. Mainline
  (zx-eth-main.c:4720-4731) writes only the in-port loop `0x20180+i*4=i` and a single
  `0x201a0=0x08`; it never primes out-port idx1..7 (`0x201a4..01bc`). Stock-live HAS them:
  `921e01a4=1, 01a8=2, 01ac=3, ...`. This is OUT-port (egress) state, so it is **downstream** of
  the MAC→SPA ingress drop and unlikely to be THIS gate, but it is a real omission. (in-port
  `921e0180..018c = 0,1,2,3` match mainline.)
- **0x921D4054 low bits.** Stock 0x03ff05dc; mainline only OR-sets bits24-25, leaving 0x05dc
  (looks like a 0x5dc=1500 length/threshold field) at HW default. Same value for all ports →
  not port1-specific, low priority, but worth writing the literal stock value for faithfulness.
- **`spa_set_port_pkt_filter`/`spa_set_port_dft_pri` per-port loops** (reg_id 57-65 @ 0x921D42A8,
  reg_id 0x... dft_pri): stock writes 0 (=stock-live 0x921D4288.. all 0); mainline leaves at
  reset (also likely 0). Symmetric across ports → not the gate.
- **`zx_pp_pm_apply_replay`** (zx-eth-main.c:1936) replays a 1025-entry captured PP_PM RAM
  (zx_pm_table.h, ram_id 3). This is the PP/CLA-side port-mapper (downstream classifier, CLA is
  ruled out) — entry0 differs (0x00010000 vs 0x00810000 for the rest) but it is not the SPA
  ingress admit. Low priority for this gate.

## 6. Concrete tests (read-only first, then poke)
All pokes write literal phys; SPA regs are 0x921D4xxx. With port1+port2+port3 cabled, ping port1.

### Step A — read the suspect regs live on MAINLINE (definitive)
```
devmem 0x921D400C    # up pps_en[0x00-0x1f]   stock=0xffffffff
devmem 0x921D4010    # up pps_en[0x20-0x3d]   stock=0x3fffffff
devmem 0x921D404C    # dn pps_en              stock=0xffffffff
devmem 0x921D4050    # dn pps_en              stock=0xffffffff
devmem 0x921D4054    # stock=0x03ff05dc
```
If any read **0** (or != stock) on mainline → confirmed missing write. (If they already read
ffffffff/3fffffff = HW default is all-on, this hypothesis is dead — go to the PM out-rule / re-examine
the match/hash RAM as the port1-entry selector.)

### Step B — poke to stock values, re-ping port1
```
devmem 0x921D400C 32 0xffffffff
devmem 0x921D4010 32 0x3fffffff
devmem 0x921D404C 32 0xffffffff
devmem 0x921D4050 32 0xffffffff
devmem 0x921D4054 32 0x03ff05dc
```
**Expected if this is the gate:** SDET uni1 transport counter `0x921C4164[7:0]` (currently 2)
climbs to track uni2/3 (`0x921C4168`/`0x921C416C`), the SPA rcv_uni1 region in `0x921D45CC+N*4`
fills, and `rx_per_ingress[port1]` starts incrementing.

### Step C (if A/B negative) — dump SPA match/hash RAM to see port1's entry
The per-entry pps/pkt gate matters only via which entry port1 resolves to. Read the match-RAM
(indirect, ram_id 0; cmd 0x921D4014, done 0x921D4018, data 0x921D401C..30 — protocol in
`pm_spa_init_recipe_re.md` §B) for the entries hit by port1 vs port2/3, and check each entry's
pkt_en vs pps_en bit. The bit that is 1 for port2/3's entry and 0 for port1's entry IS the gate.

## 7. Driver fix (after Step A/B confirm)
In `zx_pm_spa_init` (zx-eth-main.c:4711), add the four missing SPA pps_en words + the literal
0x14054 right after the pkt_en block:
```c
npp_write(e, 0x1400c, 0xffffffff);  /* SPA up pps_en[0x00-0x1f]  */
npp_write(e, 0x14010, 0x3fffffff);  /* SPA up pps_en[0x20-0x3d]  */
npp_write(e, 0x1404c, 0xffffffff);  /* SPA dn pps_en             */
npp_write(e, 0x14050, 0xffffffff);  /* SPA dn pps_en             */
npp_write(e, 0x14054, 0x03ff05dc);  /* literal stock (was partial RMW) */
```
And (separately, for egress faithfulness, lower priority) prime PM out-port rules 1..7:
`for i in 1..7: npp_write(e, 0x201a0 + i*4, i);` BEFORE the `0x201a0=0x08` line.

---

## Key references
- `linux-v6.6/.../zx-eth-main.c:4706` zx_pm_spa_init (the 8 SPA writes), :4720 PM rules,
  :1936 zx_pp_pm_apply_replay, :1226 zx_smac_init_port, :689 port_remap{1,2,3,4,5,0,6,7}.
- `linux-v6.6/.../zx-fpga-reg-tables.h:629` zx_sparegtable (reg_id 0/1=pkt_en, 2/3=pps_en).
- `decomp_all_tm.c:26271` spa_set_up_reg_pkt_en, :26373 spa_set_up_reg_pps_en (reg_id 2),
  :26416 spa_set_dn_reg_pps_en (reg_id 3), :43271 tm_pon_npp_spa_initial (no pps_en caller),
  :43376 tm_pon_npp_pm_initial (in+out rule loops 0..7), :47640 tm_pm_port_get (=port_remap),
  :35358 tmOnuRegWrite addr formula.
- `regs/stock_eth_2mib.txt`: 921d4000-4054 block (the diff in §3), 921e0180/01a0 (PM rules).
- `port1_sdet_ingress_gate_re.md` (LIVE TEST: drop is MAC→SPA, upstream of SDET; uni1=2).
- `pm_spa_init_recipe_re.md` (SPA/PM recipe + indirect-RAM protocol for Step C).

## Bottom line
Mainline's SPA pkt_en (0x14000/04/08) **bit-exactly replicates** stock — the "short mask drops
port1's bit" hypothesis is **disproven** (stock-live confirms identical). The real mainline-vs-stock
gap on the SPA up-receive path is the **per-entry up/dn PPS-enable bitmaps at 0x921D400C/4010
(up) and 0x404C/4050 (dn)** which stock sets to ffffffff/3fffffff and **mainline never writes**.
Because these are per-ENTRY (resolved via the SPA match/hash RAM), they can drop only the entries
that port1 (regport2) resolves to while leaving ports 0/2/3 untouched — the exact mechanism for a
byte-identical-config, port1-only, counter-silent MAC→SPA drop. Confirm with the read in §6-A
(currently never read by mainline); if 0, poke §6-B and watch SDET uni1 (0x921C4164) climb.
Secondary omission: PM out-port rules 1..7 unprimed (downstream/egress, lower rank).
```

## LIVE TEST 2026-05-31 — Agent C pps_en hypothesis DEAD + MAC-ctrl bit identical
- SPA pps_en regs read ALREADY at stock values: 0x921D400C=0xffffffff, 0x4010=0x3fffffff,
  0x404C=0xffffffff, 0x4050=0xffffffff, 0x4054=0x03ff05dc. HW default is all-on, so mainline not
  writing them is harmless. Agent C's hypothesis is DEAD (its own caveat anticipated this).
- MAC ctrl bit16 hypothesis (the user's "wrong bit"): MAC1/MAC2/MAC3 ctrl ALL = 0x00bb6003 (bit16
  SET on all three). port2/3 WORK with bit16 set, so bit16 is NOT the discriminator.
CUMULATIVE: every readable per-port register is now BYTE-IDENTICAL between port1 (fails) and the
working ports 2/3 (and stock): MAC ctrl/en, SPA pkt_en+pps_en+match, SDET maxframe (drop=0), CLA
ram2 (clapeek-verified valid), SIPC (drop=0), isolation, STP, PM in/out rules, broadcast flood.
The drop is precisely localized (MAC1-RX=88 → SDET uni1 transport=2, 86 lost MAC→SDET, silent, no
drop counter) but is NOT a wrong value in ANY readable register — it is a dynamic state or an
init-sequence/silicon-channel issue specific to port1's MAC→SPA path, invisible to register reads.
Beyond register-level debugging. Only remaining path: a stock kotrace of port1 ingress to find an
init-SEQUENCE difference (heavy). Multi-port DSA functional on 3/4 ports + hotplug.
