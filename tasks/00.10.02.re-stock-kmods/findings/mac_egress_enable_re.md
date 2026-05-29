# MAC egress-enable RE — why CPU-TX never egresses MAC[2] (host port)

Date 2026-05-28. Driver `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`.
Decomp `decomp_all_plat_zxylzb_9128S.c` (smac/pon), `decomp_all_tm.c` (smac_set_*).

## TL;DR
YES — the MAC port-block being un-programmed (en=0, mask=0, ctrl missing
bit15) is the gate. It is NOT the QMG scheduler. ROOT CAUSE is an **init
ordering bug**: mainline runs `smac_init` (which programs ctrl/mask/en)
and THEN runs the global `pon_reset(0xffffffff)`, which wipes every MAC
block back to 0. Stock does the opposite order. After that, only
`adjust_link` re-touches MAC[2].ctrl (and writes the wrong value
0xBA6003, missing bit15); it never restores mask(+0x04) or en(+0x08).

## 1. What the three MAC registers mean (decomp-cited)

Stock `smac_init(port)` — `decomp_all_plat_zxylzb_9128S.c:2272-2283`:
```c
void smac_init(int param_1){
  param_1 = param_1 * 0x40000;
  *(npp_base + param_1 + 0x40000) = 0xbae003;     // +0x00 CTRL
  *(npp_base + param_1 + 0x40004) = 0xffff;        // +0x04 IRQ/feature MASK
  *(npp_base + param_1 + 0x40008) = 0x80000001;    // +0x08 ENABLE
  *(npp_base + param_1 + 0x400e0) = &PTR_caseD..;  // +0xE0 PHY cb (0x11200)
  *(npp_base + param_1 + 0x40d00) &= 0xfffffffd;   // +0xD00 clr bit1
  *(npp_base + param_1 + 0x40d30) &= 0xffffffdf;   // +0xD30 clr bit5
}
```
- **+0x00 CTRL = 0xBAE003**. Bits0+1 (0x3) = RX/TX enable pair (stock moves
  them together via `pon_npp_smac_enable_part_3`: `ctrl |= 3`, decomp:2775;
  `disable_part_4`: `ctrl &= ~3`, decomp:2788). **bit15 (0x8000)** is part
  of the static config word and is present in the *runtime* host-port value
  too (live stock MAC2 ctrl=0x00BAE000 + the 0x3 enable = 0xBAE003-class).
  bit13 (0x2000) toggled by speed/duplex. The mainline header comment at
  L1187-1197 mislabels bit15 as "half-duplex/10M"; on the live stock dump
  bit15 is SET on the 1G/FD host port, so it is a static MAC-config bit
  that must stay set, not a speed bit.
- **+0x04 MASK = 0xFFFF** (mainline live = 0). Per-MAC feature/IRQ mask;
  un-RE'd individually but stock holds 0x3FFF/0xFFFF on every live MAC and
  0 disables MAC operation. The NPP_AUX twin blocks use exactly the same
  triple (ctrl=0xbae000 / mask=0x3fff / en=0x80000001 — see mainline
  `zx_npp_aux_init` L954-956), corroborating the meaning.
- **+0x08 ENABLE = 0x80000001**. **bit31 = master MAC enable** (the SMAC
  hardware block clock/run gate); bit0 = a secondary run bit. With +0x08
  = 0 the MAC core is held disabled → it accepts nothing from the switch
  fabric for egress. This is the egress gate.

Stock programs ALL four MACs identically (live: ctrl=0xba6003/0xbae000,
mask=0x3fff, en=0x80000001 on 0..3).

## 2. What mainline actually does

`zx_smac_init_port` (L1205-1248) DOES write the correct triple:
`0xBAE003` ctrl, `0xFFFF` mask, `0x80000001` en. Good.

But the probe sequence (`zx_eth_probe`, L4490-4503) is:
```
4491  zx_npp_init(eth);          // -> zx_smac_init_port() x4  (programs MACs)
4501  zx_eth_init_pon_chip(eth); // -> zx_pon_reset(0xffffffff) (WIPES MACs)
4503  zx_eth_apply_stock_init(eth);
```
`zx_pon_reset` (`zx-pon-plat.c:42-49`) does `pon[8] &= ~mask; udelay;
pon[8] |= mask` with mask=0xffffffff — a transient reset pulse to EVERY
sub-block, including all MAC port blocks. The stock burst replay
(`zx_stock_bursts.h`) contains **no** MAC ctrl/en writes (grep for
`0xbae003`/the en value at MAC windows = 0 hits), so nothing re-programs
the MACs after the wipe.

Then `zx_eth_adjust_link` (L3842-3948) fires on link-up and writes only:
```
3874  writel(MAC_CTRL_LINK_UP, mac_off(i,MAC_REG_CONTROL));  // 0xBA6003
```
`MAC_CTRL_LINK_UP = 0xBA6003` (L3833) — **missing bit15 (0x8000)** vs
stock's 0xBAE003. It never re-writes +0x04 or +0x08.

LIVE confirmation (debugfs regdump / stats, 2026-05-28):
```
MAC[0] ctrl=00000000 mask=00000000 en=00000000
MAC[1] ctrl=00000000 mask=00000000 en=00000000
MAC[2] ctrl=00ba6003 mask=00000000 en=00000000   <- host port, en=0!
MAC[3] ctrl=00000000 mask=00000000 en=00000000
tm_tx_count=17   TM[0x10058] TX count=0           <- 17 pushed, 0 consumed
```
MAC[2].ctrl is the lone non-zero because adjust_link rewrote it; the
0xBAE000 vs 0xBA6000 difference is exactly the bit15 the mainline LINK_UP
constant drops. mask/en stayed 0 = MAC core disabled = no egress.

## 3. The gate — ranking
1. **MAC[2] +0x08 ENABLE = 0 (bit31 master enable)** — PRIMARY. MAC core
   held disabled → switch routes the ARP reply to MAC2 but the MAC won't
   egress it. Confirmed: 17 frames pushed, 0 consumed by TM.
2. **MAC[2] +0x04 MASK = 0** — same root cause (wiped), also required.
3. **ctrl bit15 (0x8000) missing** — wrong adjust_link constant; restore.
4. QMG/TM-DMA diffs — secondary; the TX count never even reaches the MAC,
   so the QMG diffs are downstream symptoms, not the gate.

Stock's per-port link path PROVES the fix model: on every link event it
does `pon_reset(1<<(port+6)); smac_init(port); smac_enable_part_3(port)`
(decomp:2887-2905, 3194-3198) — i.e. it ALWAYS re-runs the full smac_init
(ctrl+mask+en) after any reset pulse. Mainline's adjust_link skips the
smac_init step.

## 4. CONCRETE FIX

### Fix A (primary, minimal) — reorder probe so smac_init runs AFTER pon_reset
`zx-eth-main.c` `zx_eth_probe` ~L4490. Move `zx_npp_init` (or at least the
per-MAC `zx_smac_init_port` loop) to run AFTER `zx_eth_init_pon_chip`:
```c
zx_pp_init(eth);
/* npp global init WITHOUT the smac loop */
zx_eth_init_pon_chip(eth);   /* pon_reset(0xffffffff) FIRST, like stock */
zx_npp_init(eth);            /* now smac_init survives — matches init_module:8923 then 8935 */
zx_eth_apply_stock_init(eth);
```
This mirrors stock `init_module` (decomp:8923 `pon_reset` → 8935
`tm_pon_npp_init`→smac_init).

### Fix B (also required) — make adjust_link restore the full MAC triple
`zx-eth-main.c` `zx_eth_adjust_link`, replace the lone ctrl write at
L3874-3875 (and the LINK_UP constant) so link-up re-runs smac_init then
sets bits0+1, like stock's `pon_reset;smac_init;enable_part_3`:
```c
/* L3833: fix the constant — restore bit15 (0x8000) to match stock 0xBAE003 */
#define MAC_CTRL_LINK_UP   0xBAE003u   /* was 0xBA6003 (dropped bit15) */
#define MAC_CTRL_LINK_DOWN 0xBAE000u

/* L3874 area — on link UP, restore the WHOLE MAC block (stock pattern):*/
if (now) {
    void __iomem *mac = e->base + mac_off(i, 0);
    writel(0x00BAE003, mac + MAC_REG_CONTROL);   /* +0x00 ctrl (bit15 set) */
    writel(0x0000FFFF, mac + MAC_REG_IRQ_MASK);  /* +0x04 mask  */
    writel(0x80000001, mac + MAC_REG_ENABLE);    /* +0x08 enable (bit31)   */
} else {
    writel(MAC_CTRL_LINK_DOWN, e->base + mac_off(i, MAC_REG_CONTROL));
}
```
(Equivalently: just call `zx_smac_init_port(e, i)` then OR-in `0x3` on
link-up — that is byte-for-byte the stock `smac_init;enable_part_3` path.)

Apply to **all** MACs at init (Fix A already loops 0..3); Fix B only needs
the active port on each link event, but doing the full triple is harmless
and exactly matches stock.

### Quick live validation (no reflash)
The single load-bearing register is MAC[2] +0x08. A devmem poke of
`0x92280008 = 0x80000001` (and `0x92280004 = 0x3fff`, `0x92280000 |=
0x8000`) on the running device should immediately let the ping reply
egress, proving the gate before committing the source fix.
