# SOPC / SPA / QMG hw-fwd decision for the CPU-source TX frame (2026-05-28)

DECOMP/STATIC ONLY. Goal: find the register(s) that make the QMG/SOPC
HARDWARE-FORWARD a CPU-injected (GEM 0x2c / lan_up port 4) frame, FDB-resolved
to internal port 3 = MAC2/LAN3, so `sopc_send2smac2` (0x921d9164) and
`SMAC2 TX` (0x92280718) increment. Companion to `arch_survey_cpu_egress.md`,
`eth_pipeline_architecture_2026-05-28.md`, `cpu_egress_routing_re.md`.

---

## TL;DR — the #1 poke-testable hypothesis

**The send2smacN gate is NOT in the SPA/SBRG/QMG/SOPC config layer — every
per-source forwarding attribute is already stock-faithful in mainline. The
gate is that MAC2 is link-DISABLED: SOPC will not emit `send2smac2` to a MAC
whose CONTROL[0]=bits0,1 (TX+RX enable) are clear.**

Decisive decomp evidence (`pon_npp_smac_enable.part.3 @ plat:2769`):
```c
void pon_npp_smac_enable_part_3(int port){
    *(npp_base + port*0x40000 + 0x40000) |= 3;   // MAC[port] CONTROL[0] |= bits 0,1
}
// disable (link-down) clears them: pon_npp_smac_disable_part_4 @ plat:2782 : &= ~3
```
This `|= 3` is the per-MAC TX/RX egress-enable, run on EVERY PHY link-up.

Live-stock proof (`regs/stock_eth_2mib.txt`):
* MAC0 (active, **egressing** — `sopc_send2smac0`=0x54d): `0x92200000 = 0x00ba6003` → bits 0,1 SET.
* MAC2 (host/LAN3, idle this capture): `0x92280000 = 0x00bae000` → bits 0,1 **CLEAR**.
The only egress-relevant delta between the working MAC and the dead MAC is
CONTROL[0] bits 0,1 (+ bit15 link-state). SOPC routes to MAC0 but not MAC2.

### POKE TEST (phys in reachable window)
MAC2 CONTROL reg = `npp_base + 2*0x40000 + 0x40000` = `0x921c0000 + 0xc0000` =
**`0x92280000`**.

1. (prereq, stock smac_init — NOT the U-Boot variant; see "storm" note below)
   ```
   poke 0x92280000 0x00bae003     # CONTROL: bits0,1 (tx+rx en) + stock 0xbae000
   poke 0x92280004 0x0000ffff     # IRQ_MASK (stock smac_init = 0xffff)
   poke 0x92280008 0x80000001     # ENABLE  (stock-live = 0x80000001)
   ```
2. the actual egress-enable (replays `pon_npp_smac_enable_part_3`):
   ```
   poke 0x92280000 0x00bae003     # ensure CONTROL[0] bits 0,1 set (also covers
                                  # the smac_init "npp+(2+1)*0x40000 |= 2" — that
                                  # IS MAC2 CONTROL[0] bit1, same reg, plat:3293)
   ```
   Then run `txtest 4` and watch `sopc_send2smac2` (0x921d9164) and
   `SMAC2 TX` (0x92280718). Expect both to increment.
   NOTE: `npp+(port+1)*0x40000` for port2 = 0x921c0000+0xc0000 = 0x92280000 =
   the MAC2 CONTROL reg itself; the stock `|=2` is bit1 of CONTROL[0], NOT a
   separate NPP register. (0x922c0000 would be MAC3 — do not poke it.)

**Do NOT** also write `0x922800e0`, `0x92280c20`, `0x92280c50`, `0x92280070`,
`0x922800b4`, `0x92280b00`. Those are U-Boot DIRECT-MUX MAC↔PHY words that
stock leaves 0 (stock-live `0x922000e0 = 0` on the *egressing* MAC0). They are
what mainline `zx_smac_init_port` (zx-eth-main.c:1230-1235) adds, and they are
the source of the packet STORM the session hit when enabling the MAC. Stock's
fabric egress needs only CONTROL/IRQ_MASK/ENABLE + the NPP `|=2`.

---

## Q1 — What makes SOPC assert send2smac[port]?

The SOPC `send2smacN` is the DOWNSTREAM output stage. It dequeues from DSCH and
hands the frame to physical MAC N. There is **no per-source "send2smac select"
register** — the egress port N is the DA/FDB-resolved port, and SOPC simply
gates on the destination MAC being **enabled/link-ready**.

* `tm_pon_npp_sopc_initial @ tm:43242` does ONLY: `sopc_set_crc_pad_cfg(0..4,0)`
  + `opc_top_set_sp_rr_cfg(0)`. No per-port egress-enable mask.
  - crc_pad: `sopcRegTable` reg 0..4 → base_off 0x76401 → phys `0x921d9004`,
    2 bits/port. Stock-live `0x921d9004 = 0` (= what stock writes). ✓ default.
  - sp_rr: `sopcRegTable` reg 8 → base_off 0x76800 → phys `0x921da000`, bit0.
    Stock writes 0 = already 0. ✓.
* SOPC top `0x921d9000 = 0x04444444` (boot default; sp_rr_mode=0 leaves it).
  Mainline doesn't write it — harmless, default is correct.
* `smac_sopc_mode_switch @ plat:2290` (run per link-up) writes:
  - `npp+0x19068` bit(port+5) POLLED (MAC-PHY-ready), then bit(port) SET.
  - `npp+0x19038` bit(port+16) = half-duplex flag.
  **These are TRANSIENT handshake bits, NOT a persistent egress gate**: live
  stock `0x921d9068 = 0` and `0x921d9038 = 0` even though MAC0 is actively
  egressing 0x54d frames. So 0x19068/0x19038 are RED HERRINGS for the gate.
  (Mainline already replicates this handshake at zx-eth-main.c:4092-4135.)

Decoder note: `dma_cfg_byteorder` in `smac_sopc_mode_switch` is a FUNCTION
symbol (addr 0x19064) reused as an integer constant, so
`dma_cfg_byteorder + npp_base + 4` = `npp_base + 0x19068`.

**Conclusion:** SOPC has no source-gated egress matrix. It egresses to MAC N
iff MAC N is enabled. The CPU-source-specific config is in the SBRG (Q2/Q3),
and that is already correct — leaving the MAC-enable as the gate.

## Q2 — QMG hw_fwd vs sw_fwd / trap decision

`tm_pon_tm_qmg_initial @ tm:42626` sets only ext_ddr/ddr_cache/ram_thd — no
per-source forwarding mode. `qmg_set_qmg_trap_cfg @ tm:32924` is a single
GLOBAL 2-bit value (`sbragRegTable`-style reg 4), not per-port. The QMG does
NOT make the fwd-vs-trap decision; it inherits it from the SBRG/CLA classifier
upstream.

**`sw_fwd` is EXPECTED for a CPU-injected frame** (it was placed on the UP ring
by software, so it counts as software-forwarded entering the QMG). It is NOT a
bug signal. `hw_fwd` is for frames the line-side classifier forwarded. So the
"sw_fwd not hw_fwd" observation is a normal property of CPU TX, not the wedge.
The real localization (per `txtest_clean_trace_dsch_fixed.md`) is DSCH→SOPC:
frame consumed by DSCH, never reaches an enabled MAC.

## Q3 — SPA / spa_* / sbrg per-source attributes (the DSA "source→egress" matrix)

The DSA-pattern "CPU/source-port → allowed-egress-port" config lives in the
SBRG (`sbragRegTable`, decoded in `zx-fpga-reg-tables.h`; phys = 0x92000000 +
base_off*4). Stock programs ALL 8 ports in `tm_pon_pp_brg_initial @ tm:43579`.
Every one is already replicated in mainline and matches stock-live:

| stock setter (tm:43595/43628) | sbrag regId | base_off | phys | stock-live | mainline |
|---|---|---|---|---|---|
| `sbrg_set_pt_transfer_en(p,1)` ×8 | 1 | 0xe2001 | 0x92388004 b0..7 | `040200ff` (=0xff) | `PP[0x8004]=0x040200ff` ✓ |
| `sbrg_set_pt_smac_look_en(p,1)` ×8 | 0x20 | 0xe2070 | 0x923881c0 b0..7 | `000000ff` | `PP[0x81c0]=0xff` ✓ |
| `sbrg_set_pt_da_lookup_en(p,1)` ×8 | 0x2c | 0xe20b0 | 0x923882c0 b0..7 | `000000ff` | `PP[0x82c0]=0xff` ✓ |
| `sbrg_set_pt_learn_mode(1,p)` ×8 | 0x22..0x29 | 0xe2007.. | 0x923881c4 | `00005555` | ✓ |
| `sbrg_set_unknown_unicst_fwd(0,1)` | 0x36 | 0xe20d0 | 0x92388340 b24..31 | `015555ff` (fwd byte=0x01, port0) | `PP[0x8340]=0x015555ff` ✓ |
| `sbrg_set_pt_tls(0,1)` | 0x38 | 0xe20e0 | 0x92388380 b0..7 | `00000001` (port0) | `PP[0x8380]=0x01` ✓ |
| `..unicst_fwd from-pon flood` | 0x37 | 0xe20d1 | 0x92388344 | `00000000` | `PP[0x8344]=0` ✓ |
| broadcast ctrl / from-pon | 0x49/0x4b | 0xe20c0/c1 | 0x92388300/304 | `0`/`0` | `0`/`0` ✓ |

So there is **NO missing source→egress-allowed config**. The lan_up/CPU source
(handled as one of the 8 ports; logical lan_up_port 4 → physical 5 via the
`tm_port_pkt_filter_set` remap {1,2,3,4,5,0,6,7} @ tm:36001) is fully enabled
for transfer + DA-lookup. The U-Boot direct-PP dump corroborates the same
window (`0x92388004 = 0x000200ff`, FUN_40e50a9c).

DEAD-ENDS confirmed write-locked (don't bother): `tm_set_pp_wan_cfg` BIT(29)
@ fpga 0xe8007 = phys `0x9239001c` reads **0** on stock-live (write does not
latch); `pp_base+0x2c` BIT(29) reads 0x106 (bit29 never latches). Both noted
in `cpu_egress_routing_re.md` Q3 — neither is the gate.

---

## Stock-vs-mainline gap (the one real divergence)

Mainline's `zx_smac_init_port` (zx-eth-main.c:1205) brings the MAC up using the
**U-Boot direct-mux** recipe (writes +0x0E0=0x00011200, +0xC20, +0xC50, +0x070,
+0x0B4, +0xB00). Stock's fabric path (`smac_init @ plat:2270`) does NOT write
those — stock-live MAC0 (egressing) has `+0xe0 = 0`. Mixing U-Boot-MAC config
with fabric egress is the storm cause (`session_2026-05-28_tx_egress_state.md`
"ruled out"). The stock-faithful fabric MAC bring-up is just:
```
CONTROL[0x00]=0xbae003 ; IRQ_MASK[0x04]=0xffff ; ENABLE[0x08]=0x80000001 ;
CONTROL[0xd00]&=~2 ; CONTROL[0xd30]&=~0x20 ; npp+(port+1)*0x40000 |= 2 ;
then per-link: CONTROL[0x00] |= 3   (pon_npp_smac_enable_part_3)
```

---

## Ranked hypotheses (poke-testable)

* **H1 (highest) — MAC2 not egress-enabled.** Replay stock smac_init (NO
  U-Boot +0xe0/0xC20/0xC50/0x070/0xB4/0xB00) then `MAC2 CONTROL[0]|=3`:
  - `poke 0x92280000 0x00bae003`   (CONTROL: tx+rx en; bit1 also = the stock
    `npp+(2+1)*0x40000 |= 2`, which IS MAC2 CONTROL[0], plat:3293)
  - `poke 0x92280004 0x0000ffff`
  - `poke 0x92280008 0x80000001`
  Then `txtest 4`; watch `0x921d9164` (send2smac2) and `0x92280718` (SMAC2 TX).
  Confidence HIGH: the only live-stock delta between an egressing MAC and a
  dead MAC is CONTROL[0] bits 0,1, set by the link handler `|= 3`.

* **H2 (medium) — full link-up sequence needed, not just CONTROL|=3.** If H1's
  CONTROL|=3 alone doesn't fire send2smac2, also run speed/duplex
  (`pon_npp_smac_config_speed_duplex_part_0 @ plat:2737`: CONTROL bits 13-15)
  for 1000/full → CONTROL ends ~`0x00ba6003` (== the working MAC0 value
  `0x92200000=0x00ba6003`). Poke `0x92280000 0x00ba6003`.

* **H3 (low) — SOPC handshake.** If still 0, set the transient mode bits the
  link handler uses: `poke 0x921d9068 (read|0x4)` (bit port=2 egress-enable)
  after the MAC-ready bit (port+5=7). Stock-live=0 so likely unnecessary, but
  cheap to try. (Mainline already does this in adjust_link.)

---

## Sources
- `decomp_all_plat_zxylzb_9128S.c`: smac_init @2270, smac_sopc_mode_switch
  @2290, config_speed_duplex.part0 @2737, smac_enable.part3 @2769,
  smac_disable.part4 @2782, dma_cfg_byteorder @6165, init_module @8889.
- `decomp_all_tm.c`: tm_pon_npp_sopc_initial @43242, opc_top_set_sp_rr_cfg
  @25871, sopc_set_crc_pad_cfg @25563, tm_pon_tm_qmg_initial @42626,
  qmg_set_qmg_trap_cfg @32924, tm_pon_pp_brg_initial @43579 (all sbrg per-port
  setters), tm_set_pp_wan_cfg @35962, tm_set_p2pmode @35979, tmOnuRegWrite
  @35356 (table-entry layout: +8 id, +0xc mask, +0x10 shift, +0x14 stride).
- `linux-v6.6/.../zx-fpga-reg-tables.h`: zx_sbragregtable (line 421),
  zx_sopcregtable (line 616) — base_off → phys = 0x92000000 + base_off*4.
- `linux-v6.6/.../zx-eth-main.c`: zx_smac_init_port @1205, NPP init @1256,
  SOPC handshake @4092-4135, MAC_CTRL_LINK_UP=0xBA6003 @4031.
- `regs/stock_eth_2mib.txt`: MAC0=0x00ba6003 (egressing), MAC2=0x00bae000
  (idle); SBRG 0x92388004/81c0/82c0/8340/8380; SOPC 0x921d9000/9068/9038;
  send2smac0=0x54d.
- `tasks/00.10.03.re-uboot/findings/uboot_eth_decomp/FUN_40e50a9c.c` (direct PP
  window 0x92388000, transfer_en byte 0xff), FUN_40e4fda4/FUN_40e4fd24 (direct
  ETH_TM2 mux @0x923a0000 — U-Boot bypasses SOPC entirely).
