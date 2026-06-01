# MAC → SPA ingress admit / handoff — RE of the one un-understood ingress stage

**Status:** static RE of stock decomp (`decomp_all_plat_zxylzb_9128S.c`,
`decomp_all_tm.c`) cross-checked against mainline `zx-eth-main.c` and prior findings.
**Date:** 2026-06-01.
**Question:** what physically carries an RX'd frame from `SMAC[port]` into the SPA/fabric,
and what per-port enable/state could silently drop **port1** there (MAC1 RX-ok climbs clean,
SPA `rcv_uni1` ≈ 0, SDET uni1 transport ≈ 2 vs uni2/3 ≈ 229/230, no drop counter).

---

## 0. TL;DR

- The block physically between **SMAC RX** and the **SPA** is the **SOPC↔SMAC bridge**, gated by a
  single per-port register **`NPP[0x19068]` = phys `0x921D9068`** (inside the SOPC block 0x921d9000).
  - **bit (port+5)** = RO "PHY-MAC link-ready" handshake (HW sets it when the serializer bonds).
  - **bit (port)**   = "this SMAC's RX is admitted into the switch crossbar" (SW sets it).
  Without bit(port) set, the MAC clocks frames in off the wire (RX-ok counter ticks) but the SOPC
  bridge does NOT hand them to the SPA → frames vanish silently, no drop counter. This is the
  **only per-port gate between SMAC RX and the SPA per-uni receive.** (plat:2290 `smac_sopc_mode_switch`)
- A second per-port datapath enable: **`MAC[port]+0x0` bits[1:0]** — stock `pon_npp_smac_enable_part_3`
  sets `|= 3` (bit0+bit1) AFTER the bridge handshake; `disable_part_4` clears `&= ~3` on link-down
  (plat:2769/2782). bit1 = "MAC in fabric"; bit0 = RX/TX datapath enable.
- **SADM is NOT this gate.** SADM (`0x92384000`) sits *downstream of CLA* (RX path: …→SPA→SDET→CLA→**SADM**→RED→QMG),
  it is a per-flow/per-subscriber policer, and it is enabled only globally (`adm_en=1`, no per-port bucket).
  It cannot drop port1 before the SPA per-uni receive counts. Ruled out as the MAC→SPA gate.
- **Mainline already implements the 0x19068 handshake** (zx-eth-main.c:4449-4500, "Iter 25") AND the
  `MAC.ctrl |= 3` enable — *but guarded by `if (ready)`*. ⇒ The live port1 silent drop is most likely
  **the port1 PHY-MAC ready bit `0x19068`[6] never asserting**, so mainline never sets `0x19068`[1] and
  the bridge for port1 stays closed. RX-ok climbs because that counter is wire-side, *before* the bridge.

---

## 1. The MAC → SPA datapath, with real phys addresses

```
SMAC[port] RX (wire)                         phys 0x92200000 + port*0x40000
   │  RX-ok counter +0x780 / RX-bytes +0x784  (wire-side, BEFORE the bridge — ticks regardless)
   ▼
[per-port MAC datapath enable]  MAC[port]+0x0 bits[1:0]   (stock |=3 ; mainline |=3)
   ▼
[SOPC↔SMAC bridge]  NPP[0x19068] = 0x921D9068
        bit(port+5) = PHY-MAC link-ready (RO gate)
        bit(port)   = admit this SMAC's RX into the crossbar (SW set)
        NPP[0x19038] = 0x921D9038  bit(port+16) = duplex (0=FD,1=HD)
   ▼
SPA per-uni receive  rcv_uniN sop/eop @ 0x921D45CC + uni*4   ← FIRST fabric-side witness
   ▼
SDET per-uni  transport/drop @ 0x921C4160 + uni*4
   ▼  CLA (regport) → SADM (per-flow policer, 0x92384000) → RED → QMG → SIPC → CPU
```

Bases: `npp_base = 0x921C0000`; `pp_base = 0x92380000`; `tm_base = 0x92340000`.
`fpga_read_reg(idx) = *(0x92000000 + idx*4)`.

### The handoff function (stock) — `smac_sopc_mode_switch(port, duplex)` (plat:2290)
```c
// dma_cfg_byteorder is a Ghidra label = the constant 0x19064 (plat:6165),
// so (dma_cfg_byteorder + npp_base + 4) == npp_base + 0x19068 == 0x921D9068.
for (i = 5; i; i--) {
    barrier();
    if (NPP[0x19068] & (1 << (port + 5))) {       // wait PHY-MAC link-ready
        NPP[0x19068] |= (1 << port);              // ADMIT this MAC's RX into the fabric  <-- THE GATE
        break;
    }
}
NPP[0x19038] = (NPP[0x19038] & ~(1<<(port+16))) | ((duplex!=1) << (port+16));   // duplex flag
```
Called on every PHY-IRQ link transition from `switch_phy_int_check_part_5` (plat:2904), and at
cold bring-up via `switch_phy_int_check` → `smac_sopc_mode_switch(port, dup)` (plat:3197).

### The per-port MAC datapath enable (stock)
```c
pon_npp_smac_enable_part_3(port):  NPP[(port+1)*0x40000] |= 3;          // plat:2769  (= MAC[port]+0 |= 3)
pon_npp_smac_disable_part_4(port): NPP[(port+1)*0x40000] &= ~3;         // plat:2782  link-down
```
Order at link-up (plat:2899-2906): `pon_reset(port)` → `smac_init(port)` →
`config_speed_duplex` → **`smac_sopc_mode_switch(port,dup)`** → **`smac_enable_part_3(port)`** (ctrl|=3).
So the bridge is opened FIRST, MAC RX/TX enabled SECOND.

---

## 2. What feeds the SPA `rcv_uni` witness — trace backward

`rcv_uniN` (`0x921D45CC + uni*4`, byte-packed sop/eop per uni; uni = logical port) is the SPA's
"frames received into the parser for uni N" counter. The ONLY thing upstream of it that is
per-port is the SOPC bridge bit `0x19068`[port]. Everything else upstream is either:
- wire-side (SMAC RX, before the bridge — does not gate),
- not per-port (SOPC `crc_pad`/`sp_rr`, the SPA match/hash RAM is portless, the SPA `pkt_en`/`pps_en`
  bitmaps are per-ENTRY not per-port — all `spa_match_hash_ram_re.md` confirmed identical/all-on).

⇒ **If `rcv_uni1` does not climb while MAC1 RX-ok does, the frame was dropped at the
SOPC bridge `0x19068`** (bit1 not admitting), because that is the sole per-port element between
the two counters. There is no per-uni "receive enable" register in the SPA itself.

---

## 3. SADM specifically (the datasheet's barely-understood block)

- **Base `0x92384000`** (= `pp_base + 0x4000`). Indirect RAM port at `pp_base+0x4014`(cmd) /
  `+0x4018`(done bit0) / `+0x401c`(data) — `sadm_ram_set/get` (plat:5555/5576).
- **Position in the RX pipeline: downstream of CLA** — `…SPA→SDET→CLA→SADM→RED→QMG…`
  (`mac_to_cpu_path_re.md` S6; DATASHEET RX diagram). So SADM is far below the MAC→SPA gate;
  it cannot be the cause of `rcv_uni1` staying low. **Ruled out as the MAC→SPA admit gate.**
- **Per-port surface:** `sadm_port_limit(port<8, …)` (plat:5606) writes the per-port token-bucket RAM
  (mem_id 2 then 0; RAM[0] bit0 = bucket enable). **This function is NEVER CALLED** anywhere in the
  stock decomp — per-port SADM buckets are left at HW reset. PPS gates `brgunsapt_pps_en` etc.
  (tm:13307…) are `x9` arrays but indexed by *traffic class / bridge-cast-type*, not ingress port.
- **Stock SADM init = global only:** `tm_pon_pp_sadm_initial` (tm:42704) → `sadm_set_adm_en(1)`
  (`0x92384000`[0]=1), `sadm_set_adm_trap_en(1)` (`0x92384000`[5]=1), `sadm_set_one_second(200000000)`
  (`0x9238400c`). The other plat-side `pon_pp_sadm_init` (plat:5685) is a literal **no-op (`return;`)**.
- **Mainline does NOT initialize SADM at all** (no write to `0x92384000`/`pp_base+0x4xxx`; the
  `0x4014/0x4018/0x401c` writes in zx-eth-main.c are TM-ring at `tm_base+0x4014`, a different block).
  Harmless for port1 (SADM admits per-flow at reset default and is downstream anyway), but noted.

Verdict: **SADM does NOT admit/drop per *ingress port*** in any code path that runs. It is a
per-flow/per-subscriber policer enabled globally; not the silent port1 gate.

---

## 4. Numbering — does a per-port admit register mis-target port1?

| element | index space | port1 lands at |
|---|---|---|
| SMAC RX-ok / `MAC[port]+0` enable | phys-MAC-index (= raw logical) | MAC1 = `0x92240000` |
| **SOPC bridge `0x19068` bit(port) / bit(port+5)** | **phys-MAC-index (= raw logical port)** | **bit1 (enable) / bit6 (ready)** |
| `0x19038` duplex bit(port+16) | raw logical | bit17 |
| SPA `rcv_uni` / SDET uni | uni (= logical) | uni1 |
| SADM `adm_en` | global, not per-port | n/a |
| SADM `sadm_port_limit` (uncalled) | `port < 8` raw | port1 (if ever called) |

The bridge is indexed by **raw logical port** (same as MAC[port]), and SPA/SDET by **uni = logical**.
For LAN0..3, MAC-index == uni == logical, so MAC1 → bridge bit1 → rcv_uni1 is internally consistent —
**no block mis-maps port1.** The drop is a *state* problem (bridge bit not admitting), not a
wrong-index write. ⚠️ Foot-gun for any fix: poke the bridge with **raw/logical port 1** (bit1, ready
bit6), NOT regport. (Regport blocks — isolation/CLA — would use regport2; those are downstream and
already exonerated.)

---

## 5. Ranked, testable hypotheses for the silent port1 MAC→SPA drop

### H1 (LEADING) — port1's PHY-MAC ready bit `0x19068`[6] never asserts → bridge bit1 never set
- **Mechanism:** mainline `zx_eth_adjust_link` (zx-eth-main.c:4449-4500) polls `0x19068` bit(i+5),
  and sets bit(i) **only inside `if (ready)`** (faithfully matching stock plat:2298). If port1's
  ready bit (bit 6) never goes high — exactly the kind of serializer/RGMII anomaly that
  `phy_mac_rgmii_wedge_re.md` documents and the multiport memory calls "a genuine anomaly" — then
  `0x19068`[1] is never set, the SOPC bridge for port1 stays closed, RX-ok still climbs (wire-side),
  and `rcv_uni1` stays ~0. **This matches every observable.**
- **Read (port-space = raw/logical):** `devmem 0x921D9068`. Expect working ports to show bits
  {0,2,3} set (enable) and {5,7,8} set (ready); **port1 = bit1 clear and/or bit6 clear**.
- **Poke / expected observable:** force the enable bit:
  `v=$(devmem 0x921D9068); devmem 0x921D9068 32 $((v | (1<<1)))` then ping jack2. If the ready
  gate was the only thing missing, **SPA `rcv_uni1` (0x921D45CC byte1) and SDET uni1 transport
  (0x921C4164) begin to climb** and frames reach the CPU. (mainline's own warning
  "SOPC ready bit N NEVER set — bridge NOT enabled" in dmesg is the direct confirmation if it fires
  for PHY[1].)
- If forcing bit1 alone is insufficient, also re-assert `MAC[1]+0 |= 3` (`0x92240000`) and clear
  the duplex bit `0x921D9038`[17].

### H2 — port1 stuck in half-duplex flag `0x19038`[17] (admit-but-mangle)
- If `0x921D9038` bit17 is set for port1 (HD) while the link is FD, the SOPC bridge may gate/garble
  RX. **Read `0x921D9038`**; bit17 should be **0** for FD. Poke clear; re-check `rcv_uni1`.

### H3 — port1's `MAC[1]+0` datapath bits[1:0] cleared (mainline mis-ordered enable)
- Mainline sets `MAC.ctrl |= 3` both in `zx_smac_init_port` and at adjust_link, but if a `pon_reset`
  or smac_init re-run between them lands the MAC at `0xBAE000` (bits 0/1 clear) and the final
  `|= 3` is skipped for port1, RX into fabric is off. **Read `0x92240000`**; expect bits 0+1 set.
  Lower probability (mainline re-asserts |=3) but cheap to check.

### H4 (LOW) — SADM/SDET per-uni init left at a bad reset value for uni1
- Mainline skips `tm_pon_npp_sdet_initial` and the full SPA per-uni init. But SDET uni1 drop=0 and
  the maxframe word reads the correct stock value (`port1_sdet`/numbering map), and SADM is downstream
  and per-flow. Unlikely, but if H1-H3 fail, replay the SDET/SPA per-uni init (`pm_spa_init_recipe_re.md`).

**Single most actionable test:** read `0x921D9068` live and compare port1's bit6 (ready) and bit1
(enable) against a working port's bits; then force bit1 and watch `0x921D45CC`. This isolates H1
in one read + one poke.

---

## 6. Citations
- stock: `smac_sopc_mode_switch` plat:2290; `dma_cfg_byteorder`(=0x19064) plat:6165;
  `switch_phy_int_check_part_5` plat:2797 (link-up/down sequence, calls bridge then enable);
  `pon_npp_smac_enable_part_3` plat:2769 / `disable_part_4` plat:2782 (MAC+0 |= 3 / &= ~3);
  `tm_pon_npp_initial` tm:43446 (no SADM); `tm_pon_pp_sadm_initial` tm:42704 (global adm_en only);
  `pon_pp_sadm_init` plat:5685 (no-op); `sadm_ram_set/get` plat:5555/5576; `sadm_port_limit`
  plat:5606 (UNCALLED); `sadm_set_adm_en` tm:12470 (reg0 = 0x92384000[0]).
- mainline: `zx_smac_init_port` zx-eth-main.c:1226 (ctrl|=3 + npp_or(MAC,0x2));
  `zx_eth_adjust_link` 0x19068 handshake :4449-4500; `mac_off` :408 (raw port).
- findings: `phy_mac_rgmii_wedge_re.md` (0x19068 gate, port1 RGMII/serializer anomaly),
  `mac_to_cpu_path_re.md` (S2 bridge, S6 SADM placement, pipeline counters),
  `port_numbering_map_re.md` (bridge = raw logical; uni = logical), `spa_match_hash_ram_re.md`
  (SPA portless, pkt_en all-on), `ingress_datapath_architecture_re.md`, `pm_spa_init_recipe_re.md`.

---

## DATASHEET updates
Add to DATASHEET.md (these are new / corrected register semantics):

1. **New register — SOPC↔SMAC bridge / per-port RX-into-fabric admit** (the MAC→SPA gate):
   - `0x921D9068` (NPP[0x19068], inside SOPC block 0x921d9000), R/W, indexed by **raw/logical port** (= phys-MAC-index for LAN0..3):
     - bit(port+5) `phy_mac_ready[port]` — RO, HW sets when serializer/PHY-MAC bonds (port0→b5,1→b6,2→b7,3→b8,4→b9).
     - bit(port)   `mac_rx_to_fabric_en[port]` — RW, SW admits this SMAC's RX into the switch crossbar (port0→b0…4→b4). **THE per-port MAC→SPA admit gate.** Confidence ✅ (stock `smac_sopc_mode_switch` plat:2290 + mainline Iter25).
   - `0x921D9038` (NPP[0x19038]) bit(port+16) `smac_duplex_half[port]` — RW, 0=full-duplex, 1=half (port0→b16…). Confidence ✅.
2. **Correction/addition — per-port MAC datapath enable:** `MAC[port]+0x0` (`0x92200000 + port*0x40000`) **bits[1:0]** = RX/TX datapath enable + "MAC-in-fabric"; stock `pon_npp_smac_enable_part_3` sets `|= 3` AFTER the 0x19068 handshake, `disable_part_4` clears `&= ~3` on link-down. (Datasheet currently only notes mac ctrl 0xbae003; document bits[1:0] as the enable pair and bit1 as the NPP-level "MAC in fabric" bit.) Confidence ✅.
3. **SADM (§3.15) clarification:** SADM is **downstream of CLA** in the RX path (SPA→SDET→CLA→**SADM**→RED→QMG) and is a **per-flow / per-subscriber** policer, **not** a per-ingress-port admit gate — it cannot gate the SMAC→SPA handoff. Stock init is **global only**: `adm_en 0x92384000[0]=1`, `adm_trap_en 0x92384000[5]=1`, `one_second 0x9238400c=200000000` (`tm_pon_pp_sadm_initial`). Per-port token-bucket helper `sadm_port_limit` exists but is **never called** (per-port buckets left at reset). `pon_pp_sadm_init` (plat) is a no-op. **Mainline initializes SADM not at all.** SADM RAM access: `pp_base+0x4014` cmd / `+0x4018`[0] done / `+0x401c` data (= phys `0x92384014/18/1c`). Confidence 🟡→✅ for placement/init.
