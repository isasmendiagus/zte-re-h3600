# PHY[N] ↔ MAC[N] interconnect on ZX279128S — RE of the "MAC-RX-counter-stays-zero" wedge

Sources walked:
- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_plat_zxylzb_9128S.c`
- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_tm.c`
- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_zx_ponreg.c`
- `tasks/00.10.02.re-stock-kmods/findings/static_analysis_plat_zxylzb_init.md`
- `tasks/00.10.02.re-stock-kmods/findings/static_analysis_tm_ko_init.md`
- `tasks/00.10.02.re-stock-kmods/findings/regs/stock_eth_2mib.txt` (live stock dump)
- `tasks/00.10.03.re-uboot/findings/uboot_eth_decomp/FUN_40e50c40.c`
- `tasks/00.10.03.re-uboot/findings/static_analysis_uboot_eth.md`
- `tasks/00.01.eth-driver/findings/stock_vs_mainline_regs_2026-05-27.md`
- `tasks/00.01.eth-driver/findings/stock_runtime_visibility_2026-05-27.md`
- `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c` (mainline)

---

## 1. Interconnect identification

**The MAC[0..3]→PHY[0..3] path is NOT classic RGMII/SGMII** in any
software-visible sense. Stock never writes an "interface_mode" register
and U-Boot never sets RX/TX skew. There is no PHY_INTERFACE_MODE_RGMII
init anywhere; mainline uses `PHY_INTERFACE_MODE_INTERNAL`, which is
correct.

What stock + U-Boot actually do is gate a **per-port handshake bus**
between the PHY block (MDIO 10..13), the SMAC blocks (`MAC[N] @
0x92200000 + N*0x40000`), and the switch fabric (`NPP`/`SOPC` @
`0x921c0000`/`0x921d9000`). The gate is in **NPP_misc at +0x19068**:

```
   poll  NPP[0x19068] bit (port + 5) == 1     ← "PHY-MAC link-ready"
   then  NPP[0x19068] |=  (1 << port)         ← "SMAC port enabled"
```

Plus a duplex/speed select in NPP[0x19038] bit (port + 0x10).

This is identical in U-Boot (`FUN_40e50c40` step n) and stock runtime
(`smac_sopc_mode_switch` @ plat:2290). Without this handshake, the
SMAC block stays internally disconnected from the switch crossbar even
though its PHY link comes up and its `MAC.ctrl` bits 0+1 are set.

`top_crm` only gates the **PON subsystem clock** (TOPCRM[0x0C] |=
0x1E0); it does not gate per-PHY-MAC traffic.

---

## 2. Stock per-port "link-up" sequence (every register touched)

When `switch_phy_int_check_part_5(N)` (plat:2797) observes PHY[N] link
UP via MDIO reg 0x1a bit 6:

```
1. pon_reset(1 << (N+6))                      // pulse per-port reset
2. smac_init(N):                              // re-init MAC regs
     MAC[N].ctrl   = 0xBAE003                 // bit 19 set, RX/TX OFF
     MAC[N].mask   = 0xFFFF
     MAC[N].en     = 0x80000001
     MAC[N].0xe0   = PTR_caseD_47_...         // (fn ptr; mainline writes 0x00011200)
     MAC[N].d00   &= ~0x2
     MAC[N].d30   &= ~0x20
3. pon_npp_smac_config_speed_duplex_part_0(N, speed, duplex):
     MAC[N].ctrl bits 13/14/15 set per detected speed/duplex
       (1G FD → 0x2000 |  ;  100 FD → 0xa000 ;  100 HD → 0xe000 ; 10 → 0x6000 etc)
4. smac_sopc_mode_switch(N, duplex):
     for i in 0..4:  __delay(0x66665b0)
       if (NPP[0x19068] & (1 << (N+5))) {
         NPP[0x19068] |= (1 << N)             // ← THE GATE
         break
       }
     NPP[0x19038] &= ~(1 << (N+0x10))         // duplex bit clear
       | ((dup!=1) << (N+0x10))               //   (set if FULL duplex)
     __delay(0x66665b0)
5. pon_npp_smac_enable_part_3(N):
     MAC[N].ctrl |= 0x3                       // FINAL RX+TX enable
6. MAC[N].0x90 = saved value (some checkpoint)
```

On link DOWN: `pon_npp_smac_disable_part_4(N)` → `MAC[N].ctrl &= ~3`.

The **NPP[0x19068]** write is the load-bearing handshake. Without it the
switch fabric's SOPC sub-block doesn't accept frames out of this MAC.
U-Boot's `FUN_40e50c40` does the same exact poll+set pattern before
final `MAC[N].ctrl |= 3`.

---

## 3. Mainline vs stock diff

`zx_smac_init_port` (zx-eth-main.c:1205) and `zx_eth_adjust_link`
(:3716) cover the **per-port MAC writes** correctly — the 0xe0 /
0xc20 / 0xc50 / 0x70 / 0xb4 / 0xb00 set from U-Boot are all present.

What mainline is **missing** entirely:

| Stock write | Mainline | Severity |
|---|---|---|
| `NPP[0x19068] |= (1 << port)` on link-UP (the "SOPC enable" gate) | **absent** | 🔴 likely root cause |
| `NPP[0x19038]` duplex bit (port+0x10) | absent | 🟡 may matter only at FD/HD switch |
| `pon_npp_smac_config_speed_duplex_part_0(N, speed, dup)` — speed-aware MAC.ctrl bits 13/14/15 | hard-coded 0xBA6003 (only bit 13 = "gigabit") | 🟡 OK at 1G FD, wrong at any other speed |
| `pp[0x2c] |= 1 << (port+0x19)` per active port | only port 0 / lan_up_port=0 | 🟡 wrong port if cable not on LAN1 |
| Init-time `MAC[N].ctrl = 0xBAE000` (bits 0+1 clear) then `|=3` on link-up | inits to `0xBAE003` (bits 0+1 already set) | 🟢 cosmetic — but it does explain the inverted ctrl pattern seen in stock_vs_mainline_regs |

Note: there is no `NPP[0x19068]` write or `NPP[0x19038]` write anywhere
in the mainline source. `grep -n "0x19068\|0x19038" zx-eth-main.c`
returns nothing.

---

## 4. The MAC RX counter (+0x710..+0x71c) — what it actually measures

**Key empirical finding**: in the live stock register dump
(`regs/stock_eth_2mib.txt`) captured with the cable on LAN3
(= PHY[2] = MAC[2]) and `ping -c 30` successfully running:

```
MAC[0] @0x92200714 = 0x21931   ← LAN1, no cable, but counter is HIGH
MAC[2] @0x92280714 = 0x00000   ← LAN3 (the active cable!), counter ZERO
MAC[2] @0x92280718 = 0x00000
MAC[2] @0x9228071c = 0x00000
```

So on stock, **the MAC where the cable is sees zero at +0x710..+0x71c**,
yet ping works. Meanwhile MAC[0] (no cable!) shows 0x21931 bytes.
Conclusion: **+0x710..+0x71c are NOT "this port's wire-side RX
counters"**. They are some other kind of counter — most plausibly a
CPU/internal-loopback path counter (MAC[0] is where SOPC sends
CPU-bound traffic via the egress path, so its 0x714 increments when
the CPU emits frames).

The actual "smac N recv" counter that stock reports as `72` for LAN3 is
read via `smac_get_statistics(2, 0x29, &val)` → `tmOnuRegRead(1, val,
2, &smacRegTable)` → `fpga_read_reg(table[0x29].offset + 2 *
table[0x29].stride)`. `fpga_read_reg(idx) = *(pon_base + idx*4)`, so
the recv counter lives somewhere in **NPP space (0x921c0000-)**, not
in MAC[N] MMIO. The exact entry of `smacRegTable[0x29]` would need a
Ghidra data export to confirm the offset.

**Implication**: the test "MAC[2] +0x710 stays 0 under ping" is
inconclusive — it stays 0 on stock too. To actually observe whether
mainline frames reach the MAC RX, we need to read the same counters
stock's sysfs uses (`smac_get_statistics(port, 0x29, ...)`), which
means reading from the NPP block via the smacRegTable indirection.

What mainline currently does (`zx_pipeline_stats_show` :3546 reads
`mac + 0x710..0x71c`) is **looking at the wrong location**.

---

## 5. Proposed minimal fix (1–3 register writes)

Order of likelihood:

### Fix A (highest confidence) — Add the SOPC-enable handshake on link-up

In `zx_eth_adjust_link` (zx-eth-main.c:3716), **after** the `pon_reset`
pulse and **before** writing `MAC_CTRL_LINK_UP`, add:

```c
/* Stock smac_sopc_mode_switch: poll NPP[0x19068] bit (port+5)
 * for up to ~5 iterations, then set NPP[0x19068] bit (port).
 * This signals the switch-fabric SOPC sub-block that smacN is ready
 * to carry traffic.  Without it, MAC.ctrl |= 3 enables the MAC at the
 * wire but frames don't get routed into the switch crossbar.
 */
for (int t = 0; t < 5; t++) {
    udelay(1);
    if (readl(e->base + 0x19068) & (1u << (port + 5))) {
        writel(readl(e->base + 0x19068) | (1u << port),
               e->base + 0x19068);
        break;
    }
}
/* Duplex select — bit clear = FD, set = HD. */
{
    u32 v = readl(e->base + 0x19038);
    v &= ~(1u << (port + 16));
    if (phy->duplex != DUPLEX_FULL)
        v |=  (1u << (port + 16));
    writel(v, e->base + 0x19038);
}
```

`e->base` is `npp_base = 0x921c0000`, so `+0x19068` = `0x921D9068`
which matches both U-Boot's `iVar8 = 0x921d9000` and the stock decomp
of `dma_cfg_byteorder + npp_base + 4`.

### Fix B (secondary, complements A)

When `phy->speed != 1000` or `phy->duplex != FULL`, the constant
`MAC_CTRL_LINK_UP = 0xBA6003` is wrong. Mirror
`pon_npp_smac_config_speed_duplex_part_0`:

```c
u32 ctrl = 0xBA6000;            /* base: bit 19 clear, bits 0/1 will be OR'd later */
if (phy->speed == 1000)         ctrl |= 0x2000;       /* bit 13 — gigabit */
else if (phy->speed == 100)     ctrl |= 0xa000;       /* bits 13 + 15 — 100M */
else                            ctrl |= 0xe000;       /* bits 13+14+15 — 10M */
if (phy->duplex != DUPLEX_FULL) ctrl |= 0x4000;       /* bit 14 — half */
ctrl |= 0x3;                                          /* enable RX/TX */
writel(ctrl, e->base + mac_off(port, MAC_REG_CONTROL));
```

### Fix C (verification only — read the correct counter)

Stop reading `mac + 0x710..0x71c` as "wire-side RX bytes/packets". To
prove frames reach MAC RX, the cleanest probe is to mirror stock's
`smac_get_statistics(port, 0x29, ...)`. Until the smacRegTable layout
is recovered, the next-best signal is:

- read `NPP[0x19068]` — does bit `(port+5)` ever come up?
- read `NPP[0x1902c]` — stock = 0x70 (bits 4,5,6 set for active
  MACs 0/1/2). If mainline shows 0x00, the SMAC blocks aren't being
  brought online by the fabric.

---

## Confidence

- **High** (Fix A): the NPP[0x19068] handshake is independently
  attested by U-Boot (FUN_40e50c40 line 79-81) and stock runtime
  (smac_sopc_mode_switch). Mainline does not implement it.
- **Medium** (Fix B): only matters when the negotiated speed/duplex
  differs from 1G/FD. If the bench cable always trains at 1G/FD,
  0xBA6003 may already be right.
- **High** (the 0x710 misinterpretation): empirically proven by stock
  dump showing 0 for the active port and non-zero for an idle port.
