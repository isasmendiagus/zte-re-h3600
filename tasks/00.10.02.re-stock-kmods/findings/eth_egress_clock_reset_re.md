# Eth egress SoC clock/reset tree — RE (TOPCRM @ 0x94000000)

**Date** 2026-05-28. **Scope (this agent):** SoC-level CLOCK/RESET tree only
(TOPCRM `zte,zx279128s-topcrm` @ 0x94000000, sys_ctrl 0x94100000, pin_mux
0x94200000, pon_serdes, pon_base reset reg). A sibling agent owns the FPGA-write
mechanism + the block-local 0x9238c000 enable — NOT covered here.

**Sources:** stock plat decomp `decomp_all_plat_zxylzb_9128S.c`
(`zx_pon_clk_reset_init` @8266, `ref_clk_set` @8202, `zx_pon_clk_reset` @8337,
`pon_reset` @7740, `pon_init` @8891, `smac_sopc_mode_switch` @2290); U-Boot
`uboot_eth_decomp/FUN_40e4fc7c.c` (= clk_reset_init), `FUN_40e4fa08.c`
(= ref_clk_set), `FUN_40e21050.c` (eth top init), `FUN_40e40844.c`,
`FUN_40e21b00.c`; mainline `zx-eth-main.c` (`zx_eth_init_topcrm` @4584) +
`zx-pon-plat.c` (`zx_pon_clk_reset_init` @200, `zx_pon_plat_init` @290).

---

## 1. The SoC clock/reset tree for ethernet

### TOPCRM (0x94000000) — the syscon the driver references via `zte,topcrm`
of_iomap index 1 of the `zte,zx279128s-pon` node in stock (`pon_init` @8950).

| TOPCRM reg | bits | role (from stock/U-Boot) | who sets it |
|---|---|---|---|
| 0x08 | bit5 (0x20), bit4 (0x10) | **SERDES/PON sub-clock + reset-deassert pulse.** Stock/U-Boot: clear b4+b5 → delay → set b5 → serdes cfg → set b4 (b4 gates apb, b5 the lane). | stock `clk_reset_init`; mainline `zx_pon_clk_reset_init` ✓ |
| 0x0c | bits5-8 (0x1e0) | **PON-subsystem clock enable (the datapath clocks incl. egress/SOPC side).** | stock asserts it **TWICE** (see §2) |
| 0x18 | PLL cfg | per-PHY ref-clock PLL divider (speed-dependent) | U-Boot `FUN_40e21b00` only (PHY path) |
| 0x50/0x54 | PLL | ref_clk PLL (integer/fractional) | stock `ref_clk_set`; mainline `zx_ref_clk_set` ✓ |
| 0x4c | bits0-8 forced hi | misc gate; U-Boot `FUN_40e40844` re-sets low9=1 | mainline writes 0x0003cfff ✓ (equivalent) |

### Other controllers
- **pon_base+8 = phys 0x92000008** (pon reg, of_iomap idx 0 → in the FPGA
  window): the **per-block reset register**. `pon_reset(mask)` = clear mask →
  delay → set mask. `pon_reset(0xffffffff)` resets all; per-port SMAC uses
  `pon_reset(1<<(port+6))` (MAC2 = bit 8) — this is the TX/egress-side per-port
  reset pulse. **Note: 0x92000008 is BELOW the 0x921c0000 poke floor → not
  poke-able**, but mainline already pulses it in `adjust_link` (@4063) and
  `zx_pon_reset` (@303).
- sys_ctrl 0x94100000+0x10 bit11 clear — SERDES output gate; mainline ✓.
- The SOPC per-port egress enable (`smac_sopc_mode_switch`) is NPP-side
  (`npp+0x19068`/`+0x19038`) — in poke range, already handled by mainline
  `adjust_link` (cross-checked w/ `cpu_lan_egress_gate_re.md`). NOT a SoC clock.

---

## 2. Stock/U-Boot vs mainline diff — the egress-relevant gap

Mainline replicates essentially the entire SoC clock tree: TOPCRM[0x08] b4/b5
pulse (`zx-pon-plat.c:214-225`), ref_clk PLL, serdes band cal, sys_ctrl bit,
pon_reset(0xffffffff), and `TOPCRM[0x0c]|=0x1e0`. So the bulk tree is NOT the
hole. The one asymmetric difference is **ORDERING of `TOPCRM[0x0c]|=0x1e0`**:

Stock `pon_init` (@8891) sequence:
```
pon_reset(0xffffffff); msleep(10)
pon_base+0x40018 = 2
zx_pon_clk_reset_init(1)        # TOPCRM[0xc] |= 0x1e0   (FIRST, pre-datapath)
register_pon_int(); pon+0x40044=0xffffff7f; pon+0x4001c=0xf
tm_pon_tm_init(); netdebug_init(); tm_pon_pp_init(); tm_pon_npp_init()   # <-- datapath bring-up
if (lan_up) { pp[0x2c] |= 1<<(lan_up_port+0x19);  zx_pon_clk_reset(); }  # TOPCRM[0xc] |= 0x1e0  (SECOND)
```
`zx_pon_clk_reset()` (@8337) is literally just `TOPCRM[0xc] |= 0x1e0` — a
**re-assertion of the PON-subsystem clocks AFTER all of TM/PP/NPP datapath init
and after the CPU-FWD enable**, and it fires only in lan_up mode (our mode 0x10).

Mainline asserts `TOPCRM[0xc]|=0x1e0` only BEFORE the datapath replay
(`zx_eth_init_topcrm`@4606 and `zx_pon_plat_init`→`zx_pon_clk_reset_init`@281,
both run in probe before `zx_eth_init_tm_subsystem`@4732). **Mainline never does
the SECOND, post-datapath-init `zx_pon_clk_reset()`.**

Why this is the "RX works / TX-egress dead" candidate: bits 5-8 (0x1e0) are the
PON-subsystem datapath clocks. If any step in the large TM/PP/NPP replay (or the
PP master-enable / 0x40018 writes) momentarily gates or fails to fully un-gate
the egress-side clock, stock's terminal re-assert restores it; mainline leaves
it in whatever state the replay produced. RX uses the ingress half (already
clocked from the first assert + per-port pon_reset); the egress/SOPC datapath is
the half re-blessed by the SECOND assert. This precisely matches the symptom
(QMG+DSCH pass, SMAC TX=0, SOPC send2smacN never fires).

(The other U-Boot-only TOPCRM writes — 0x18 PLL divider in `FUN_40e21b00`, 0x4c
low9 in `FUN_40e40844` — are PHY-clock/MDIO and are already covered or
equivalent in mainline; not egress gates.)

---

## 3. The exact missing write + how to test

### #1 missing clock/reset write
```
TOPCRM[0x0c] |= 0x1e0        # phys 0x9400000c, syscon = zte,topcrm (0x94000000)
```
re-asserted **AFTER** the full TM/PP/NPP datapath bring-up (i.e. at the END of
`zx_eth_init_tm_subsystem`, mirroring stock `zx_pon_clk_reset()` which runs after
`tm_pon_*_init` + the CPU-FWD write), in lan mode.

### Testability
- **Out of poke range.** Poke covers only `[0x921c0000, 0x923c0000)`
  (`zx_poke_write`@3771). TOPCRM is 0x94000000 — a different syscon, NOT mapped
  in the FPGA/npp windows. **Cannot poke-test; requires a source change +
  rebuild.**
- **Source change to test:** in `zx-eth-main.c`, at the tail of
  `zx_eth_init_tm_subsystem` (after `zx_tm_bmu_enable`/`zx_eth_init_chip_tm`,
  i.e. after all TM/PP/NPP datapath init and after the CPU-FWD bit is set), add:
  ```c
  /* stock zx_pon_clk_reset(): re-assert PON-subsystem clocks AFTER datapath
   * init. Stock pon_init does this as its terminal step in lan_up mode. */
  if (eth->topcrm)
      writel(readl(eth->topcrm + 0x0c) | 0x1e0, eth->topcrm + 0x0c);
  ```
  Then rebuild, reboot, bring the link up and `txtest`; watch SMAC2 TX
  (0x92280714/0x92280718) and the SOPC send2smac counters (0x19915c..0x19916c).
  PASS = SMAC[N] TX increments / send2smacN fires.

### Caveat / confidence
- TOPCRM clock tree fully mapped & diffed: **HIGH**.
- The single missing op being the post-datapath `TOPCRM[0xc]|=0x1e0`
  re-assert: **MEDIUM**. It is the only SoC-clock/reset action stock performs
  that mainline omits, and its position (terminal, post-datapath, lan-only)
  fits the egress-only symptom. But it is a re-assert of bits mainline already
  set once; if the replay never clears those bits the re-assert is a no-op and
  the true gate is the block-local 0x9238c000 enable / ETH_TM2 (sibling agent's
  scope) or the per-port SMAC re-init (`init_order_egress_re.md`:
  `adjust_link` must re-run full `zx_smac_init_port` after the `pon[8]` per-port
  reset, restoring mask/en/+0xE0). Recommend landing this TOPCRM re-assert
  together with that per-port SMAC re-init, since both are cheap source changes
  and the egress path needs both the clock present AND the MAC re-bonded.
