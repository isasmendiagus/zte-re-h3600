# Init-order egress RE — why CPU-TX hairpins/storms instead of egressing MAC[2]

**Date** 2026-05-28. Device booted, mainline driver, probed live over the
register tool (`localhost:9999`) + decomp triangulation.

**One-line verdict:** The bug is an INIT-ORDER bug exactly as suspected,
but the load-bearing wipe is not just MAC `en` — it is the **whole stock
`smac_init` block** (mask `+0x04`, enable `+0x08`, and the MAC↔PHY
interface word `+0xE0`). Mainline programs the MAC at probe step 3
(`zx_npp_init`→`zx_smac_init_port`) and then runs `pon_reset(0xffffffff)`
at step 5 (`zx_eth_init_pon_chip`→`zx_pon_reset`), which clears every MAC
block. Nothing reprograms them afterward — `stock_table.h` has zero MAC
ctrl/en writes, and `adjust_link` only writes `ctrl=0xBA6003`. So MAC[2]
is left half-initialized. Forcing `en` alone (prior live test) re-runs the
MAC core WITHOUT the `+0xE0` PHY-interface word, so the MAC↔PHY datapath
is mis-bonded and the MAC reflects egress internally → the packet STORM.

---

## Live ground truth (MAC[2] = host port LAN3, phys 0x92280000)

```
+0x00 ctrl = 0x00BA6003   (adjust_link wrote it — correct for 1000/FD)
+0x04 mask = 0x00000000   <- stock smac_init sets 0xFFFF   ✗ WIPED
+0x08 en   = 0x00000000   <- stock smac_init sets 0x80000001 ✗ WIPED
+0xE0      = 0x00000000   <- stock smac_init sets 0x00011200 ✗ WIPED  (MAC↔PHY iface)
+0xD00     = 0x00000000   (smac_init clears bit1 — OK by luck)
+0xD30     = 0x00000000   (smac_init clears bit5 — OK by luck)
NPP[0x19068] SOPC bridge = 0  (bit2 not set; ready bit7 never asserted)
NPP[0x19038] duplex      = 0  (FD — correct)
NPP[0x1902c]             = 0x70 (bits4,5,6 active MACs — matches stock ✓)
SPA loopback_en (0x92394088 bit1) = 0  (ruled out as storm source)
TM[0xc000] = 0x03f40050 (link-UP value set ✓); PP[0x1c01c]=0xfc000000 (BIT29 set ✓)
```

`ctrl=0xBA6003` is the *correct* final value (start 0xBAE003 → speed/duplex
clears bit15 sets bit13 → 0xBA6003 → enable ORs 3). The header's "bit19/bit15"
guesses don't matter — the wipe of **mask/en/+0xE0** is the gap.

## Stock vs mainline bring-up ORDER

| Phase | STOCK (`init_module` plat:8891 + per-link `extphy_timer_func`:3137) | MAINLINE (`zx_eth_probe` L4522-4545 + `adjust_link`) |
|---|---|---|
| chip reset | `pon_reset(0xffffffff)` FIRST (plat:8923) | step 5 `zx_eth_init_pon_chip` — AFTER smac_init |
| MAC bring-up | `tm_pon_npp_init`→`pon_npp_smac_init`→`smac_init` AFTER reset (plat:8935) | step 3 `zx_npp_init`→`zx_smac_init_port` BEFORE reset (wiped) |
| per-link UP | `pon_reset(1<<(p+6)); smac_init(p); config_speed_duplex(p); smac_sopc_mode_switch(p); smac_enable_part_3(p)` (plat:3194-3198) | `pon_reset bit; writel(0xBA6003,ctrl); TM[0xc000]; SOPC poll+set; duplex` — **no smac_init, no mask/en/+0xE0** |

Stock ALWAYS re-runs the full `smac_init` (ctrl+mask+en+0xE0) after any reset
pulse, then ORs `|3`. Mainline's `adjust_link` skips `smac_init` entirely, so
mask/en/+0xE0 stay at the post-`pon_reset` zero.

## Mechanism: half-init MAC → internal loop, not egress

`smac_init` (`decomp_all_plat_zxylzb_9128S.c:2272`) writes ctrl/mask/en AND
`+0xE0 = 0x00011200` (the MAC↔PHY interface/callback word; U-Boot
`FUN_40e50c40` sets the same and notes "without it: PHY link UP but frames
don't decode through the MAC"). With `en=0x80000001` set but `+0xE0=0` and
mask=0, the MAC core runs but its serializer is not bonded to the PHY RGMII/
internal lane → it loops the egress frame back into the switch RX, which
re-injects, which egresses again = the hundreds-of-loops STORM the prior test
saw. With `en=0`, the MAC accepts nothing, so the frame only hairpins at the
switch fabric (the residual ~15). Either way: zero wire egress.

## LIVE-TESTABLE poke sequence (full stock smac_init for MAC[2], stock order)

Apply IN THIS ORDER, then ping from host; then DISABLE MAC[2] after capture.
All addresses are in poke range and poke-able (none are dynamic QMG regs).

```
# 1. smac_init(2): mask, the MAC<->PHY iface word, then U-Boot iface regs
sh -c "echo '92280004 0000ffff' > /sys/kernel/debug/zx_eth/poke"   # MAC2 mask=0xffff
sh -c "echo '922800e0 00011200' > /sys/kernel/debug/zx_eth/poke"   # MAC2 +0xE0 iface  <-- THE missing word
sh -c "echo '92280c20 00000032' > /sys/kernel/debug/zx_eth/poke"
sh -c "echo '92280c50 000000a8' > /sys/kernel/debug/zx_eth/poke"
sh -c "echo '92280070 00300002' > /sys/kernel/debug/zx_eth/poke"
sh -c "echo '922800b4 00004000' > /sys/kernel/debug/zx_eth/poke"
sh -c "echo '92280b00 0010ff11' > /sys/kernel/debug/zx_eth/poke"
# 2. smac_sopc_mode_switch(2, full): SOPC bridge enable bit2, duplex bit18 clear(FD)
sh -c "echo '921d9068 00000004' > /sys/kernel/debug/zx_eth/poke"   # NPP[0x19068] |= bit2
# 3. ctrl (already 0xBA6003) then enable_part_3: en LAST
sh -c "echo '92280000 00ba6003' > /sys/kernel/debug/zx_eth/poke"
sh -c "echo '92280008 80000001' > /sys/kernel/debug/zx_eth/poke"   # MAC2 master enable LAST
# --- ping host now; watch: cat .../stats  (loopback should stay flat, TM[0x10058] should move) ---
# 4. ALWAYS disable after test (storm guard):
sh -c "echo '92280008 00000000' > /sys/kernel/debug/zx_eth/poke"
```

PASS = `tm_rx_loopback_drops` stays flat AND host tcpdump sees frames from
`f4:f6:47:0f:42:64` (and/or `TM[0x10058]` UP count increments).
If it STILL storms with `+0xE0=0x00011200` present, the iface word is not the
seal and the loop is in the SOPC/SMAC bond order — fall back to also pulsing
the per-port reset in source (can't poke pon[8]=0x92000008, it's out of range).

## Source fix (the real change)

`zx_eth_adjust_link` must call the full `zx_smac_init_port(e, i)` on link-UP
(restoring mask/en/+0xE0) BEFORE the SOPC bridge + `|3` enable — i.e. mirror
stock `smac_init; config_speed_duplex; smac_sopc_mode_switch; enable_part_3`.
Secondarily, reorder probe so the `zx_smac_init_port` loop runs AFTER
`zx_eth_init_pon_chip` (after `pon_reset`), per stock `pon_reset → smac_init`.

## Confidence
- Init-order wipe is real: HIGH (probe order L4527 vs L4537 + `zx_pon_reset`
  mask 0xffffffff + stock_table has no MAC writes + live mask/en/+0xE0 = 0).
- `+0xE0` is the storm seal: MEDIUM-HIGH (U-Boot + stock both set it; prior
  test enabled `en` WITHOUT it and got the storm). Direct confirmation needs
  the poke test above (I was blocked from enabling the MAC myself per the
  storm guard).
