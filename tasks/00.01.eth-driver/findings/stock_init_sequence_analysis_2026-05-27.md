# Stock init sequence — full RE analysis vs mainline gaps

Captured 2026-05-27 EOD after 6 RE-validated fixes failed to restore
ping bidi. Goal: identify the MISSING init step(s) that prevent
TM[0x100] bit 0 from ever firing in mainline.

## Source-of-truth: stock `zx_pon_init` (plat-zxylzb_9128S.ko @ 0x1d9a8)

Captured via shim+kotrace 2026-05-26 (16,340 events). Documented in
`tasks/00.10.02.re-stock-kmods/findings/eth_init_flow_2026_05_26.md`.

```
zx_pon_init:
  [a]  reserve_mem_info()
  [b]  zte_get_pon_mode()  → returns 0x10 (LAN-only)
  [c]  bp_max_number setup  → JUMBO_BP=2800, BPPE_POOL=256, BP_BUFFER=0xe0000
  [d]  printk "lan_up=1, lan_up_port=4"               ← lan_up_port = 4 !!
  [e]  of_find_matching_node_and_match("zte,zx279128s-pon"):
         pon_base       = of_iomap(node, 0)   = 0x92000000, 4 MiB
         top_crm_base   = of_iomap(node, 1)   = 0x94000000
         sys_ctrl_base  = of_iomap(node, 2)
         pin_mux_base   = of_iomap(node, 3)
         pon_serdes_base= of_iomap(node, 4)
         g_pon_irq      = irq_of_parse_and_map(node, 0)
       for "zte,zx279128s-gephy":
         for i in 0..3: g_phy_irq[i] = irq_of_parse_and_map(gephy, i)
  [f]  pon_reset(0xffffffff)
  [g]  msleep(10)
  [h]  pon_base + 0x40018 = 2                          ← scope of bit unknown
  [i]  zx_pon_clk_reset_init(1)                        ← SERDES bring-up, REG read-modify-writes
  [j]  register_pon_int()                              ← request_threaded_irq(g_pon_irq, ...)
  [k]  pon_base + 0x40044 = 0xffffff7f                 ← interrupt MASK (pon_int_enable target)
  [l]  pon_base + 0x4001c = 0xf                        ← scope unknown
  [m]  msleep(1)
  [n]  tm_pon_tm_init()                                ← see below
  [o]  netdebug_module_init()
  [p]  tm_pon_pp_init()                                ← see below
  [q]  tm_pon_npp_init()                               ← see below
  [r]  if (lan_up != 0):
         pp_base + 0x2c |= 1 << (lan_up_port + 0x19)  ← bit 29 for lan_up_port=4 !!
         zx_pon_clk_reset()
```

## Stock `tm_pon_tm_init` body (decomp 7058)

```c
printk("pon tm init\n");
*(tm_base + 0x128) = 0x1fff;          // we DO write this
*(tm_base + 0x130) = 0x1fffff;        // we DO write this
pon_tm_red_init();                    // see Phase 9d (we have it)
pon_tm_dma_init();                    // see Phase 26 zx_eth_init_chip_tm
iVar1 = pon_tm_bmu_init();            // we have zx_tm_bmu_init
if (iVar1 >= 0) {
    *(tm_base + 0xf0) = PHYS_ADDR;    // RX desc base — carved RAM @ 0x40520000 + (BMU pool offset)
    pon_tm_bmu_enable();              // we have zx_tm_bmu_enable
    *(tm_base + 0xc008) = 0;          // ⚠️ MISSING in mainline (verified by grep)
    pon_tm_net_init();                // creates netdevs + queues, enables PHY IRQs
    pon_tm_int_init();                // request_threaded_irq(g_tm_irq, zx_pon_tm_int, "pon_tm", ...)
}
```

## Stock `tm_pon_pp_init` body (decomp 5525)

```c
printk("pon_pp init\n");
pon_pp_ctrl_init();
pon_pp_brg_init();
pon_pp_cla_init();
request_threaded_irq(g_pp_irq, zx_pon_pp_int, ...);
```

### `pon_pp_ctrl_init` (decomp 5562)

```c
pp_base[10]   = 0x1070104;            // = pp_base + 0x28 = 0x1070104 ✅ we write
*pp_base      = 2;                    // pp_base + 0 = 2 ✅ but only after Phase 4
(*_request_threaded_irq)(0x66665b0);  // delay loop (~52ms)
```

### `pon_pp_brg_init` (decomp 5359 — all 14 writes)

We have all 14 PP_BRG writes in mainline post Phase 50 (verified above).

### `pon_pp_cla_init` (decomp 5500)

```c
*(pp_base + 0xc000) = ...;            // CLA RAM init via cla_ram_set
```

We have CLA init via `zx_cla_apply_replay` / stock_table.

## Stock `tm_pon_npp_init` body (decomp 2236)

```c
printk("pon_npp init\n");
*(npp_base + 8)    = 0xffffff;        // ⚠️ check mainline
*(npp_base + 0xc)  = 0xfffff;         // ⚠️ check mainline
msleep(1);
pon_npp_idm_init();                   // ⚠️ idm_net_register, NAPI add, idm IRQ regs
pon_npp_spa_init();                   // NPP[0x141c0] = 0
pon_npp_sipc_init();                  // NPP[0xc000] = 0x11
pon_npp_smct_init();                  // NPP[0x10000] = 0xb, NPP[0x10010] = 0x3810
*(npp_base + 4)    = 0xffffffff;      // ⚠️ check mainline
*(npp_base + 0x48) = 0;               // ⚠️ check mainline
pon_npp_smac_init();                  // 4x smac_init() — we have via stock_table
request_threaded_irq(g_npp_irq, pon_npp_int, ...);   // ⚠️ MISSING: we don't register pon_npp IRQ
*(npp_base + 0x40) |= 0x300;          // ⚠️ check mainline
*(npp_base + 0x10008) = 0x80;         // ⚠️ check mainline
pon_npp_uopc_init();                  // NPP[0x18000] |= 8
```

### `pon_npp_idm_init` (decomp 4340)

```c
idm_net_register(1, "idm1");
idm_net_register(0, "idm0");
netif_napi_add(idm_netdev, idm_net_poll, weight=255);
*(npp_base + 0x8024) = 0x1f;          // IDM IRQ_MASK
idm_int_mask = 0x1f;
*(npp_base + 0x8018) = 0x40;          // IDM something
*(npp_base + 0x801c) = 5000;          // IDM TIMEOUT?
// ... more
```

We DO ioremap idm_base but **do not implement idm_net_register/idm netdev**.
We DO write `IDM_REG_IRQ_MASK = 0x1f` to npp+0x8024 per stock match.

## Critical observation: lan_up_port = 4 (not 0)

```c
// Stock init flow doc line 27:
printk "lan_up=1, lan_up_port=4"
```

And:
```c
// Stock decomp line 8940:
*(pp_base + 0x2c) |= 1 << (lan_up_port + 0x19U);  // 4+25 = 29 → BIT(29)
```

Mainline definition (line 129):
```c
#define PP_CPU_FWD_BIT  BIT(25)         // ← WRONG: should be BIT(29)
```

But: even live `devmem 0x9238002c 32 0x20000106` (BIT(29) set) does NOT
stick — readback stays 0x00000106. The register is **HW-locked** by
some prior init state that mainline doesn't establish.

## Comparison: Phase 50 init order vs HEAD vs stock

| Step | Stock | Phase 50 (PING BIDI WORKS) | HEAD |
|---|---|---|---|
| pon_reset(-1) | ✅ explicit | ❌ no | ❌ no |
| msleep(10) | ✅ | ❌ | ❌ |
| pon_base + 0x40018 = 2 | ✅ | ⚠️ residue from stock pre-reboot | ⚠️ residue |
| zx_pon_clk_reset_init | ✅ SERDES | ⚠️ partial via TOPCRM | ⚠️ partial |
| register_pon_int | ✅ | ❌ no PON IRQ | ❌ no PON IRQ |
| pon + 0x40044 = 0xffffff7f | ✅ | ⚠️ residue | ⚠️ residue |
| pon + 0x4001c = 0xf | ✅ | ❌ missing (live = 0) | ❌ missing (live = 0) |
| msleep(1) | ✅ | ❌ | ❌ |
| TM[0x128] = 0x1fff | ✅ | ✅ | ✅ |
| TM[0x130] = 0x1fffff | ✅ | ✅ | ✅ |
| pon_tm_red_init | ✅ | ✅ via phase 9d | ✅ |
| pon_tm_dma_init | ✅ | ✅ via Phase 26 | ✅ (with UP/DN fix) |
| pon_tm_bmu_init | ✅ | ✅ | ✅ |
| TM[0xF0] = phys carved | ✅ carved | ✅ rxdesc_dma | ✅ rxdesc_dma |
| pon_tm_bmu_enable | ✅ | ✅ | ✅ |
| **TM[0xc008] = 0** | ✅ | ❓ unverified | ❌ likely missing |
| pon_tm_net_init | ✅ | partial — netif_napi_add | partial |
| pon_tm_int_init | ✅ request_threaded_irq | ✅ devm_request_irq | ✅ devm_request_irq |
| netdebug_module_init | ✅ | ❌ noop | ❌ noop |
| pon_pp_ctrl_init | ✅ | ✅ via stock_table | ✅ |
| pon_pp_brg_init (14 regs) | ✅ | ✅ via PP block | ✅ |
| pon_pp_cla_init | ✅ | ✅ | ✅ |
| request_threaded_irq pp_irq | ✅ | ❌ no PP IRQ | ❌ no PP IRQ |
| pon_npp_idm_init | ✅ register idm netdev | ❌ no idm netdev | ❌ |
| pon_npp_spa/sipc/smct/uopc | ✅ | ✅ via stock_table | ✅ |
| NPP[+4] = 0xffffffff | ✅ | ❓ check | ❓ |
| NPP[+0x48] = 0 | ✅ | ❓ check | ❓ |
| NPP[+0x40] \|= 0x300 | ✅ | ❓ check | ❓ |
| NPP[+0x10008] = 0x80 | ✅ | ❓ check | ❓ |
| request_threaded_irq npp_irq | ✅ | ❌ | ❌ |
| **if lan_up: PP[0x2c] \|= BIT(29)** | ✅ | ⚠️ bit 25 (wrong) | ⚠️ bit 25 (wrong) |
| zx_pon_clk_reset() | ✅ | ❌ | ❌ |

## Conclusions

### The ping-blocking pieces (in priority order)

1. **HW-lock state**: PP[0x2c] bit 29 cannot be set without prior
   `pon_reset` + `zx_pon_clk_reset_init` + the proper sequence. The
   register is locked until those run. Mainline lacks the full ceremony.

2. **Missing `pon_reset(0xffffffff)`** at module init. Stock's reset
   clears `pon_base + 8` bits, waits, restores. This puts HW in a
   known state. Without it the HW retains old state from any prior
   stock boot, which may have set "locks" we can't undo.

3. **Missing `zx_pon_clk_reset_init(1)`** SERDES bring-up. We replay
   some TOPCRM bits via stock_table but not the band-calibration loop.

4. **Missing `register_pon_int()`** — we don't request the PON IRQ
   (linux IRQ #26 in stock). The PON IRQ handler may be required for
   some path even if it doesn't fire RX directly.

5. **Missing `request_threaded_irq` for pon_pp and pon_npp**. Same
   pattern as PON: we don't register them.

6. **PP_CPU_FWD_BIT = BIT(25)** is hard-coded WRONG. Should be
   BIT(29) for `lan_up_port=4`. (Won't fix it alone — bit is locked.)

7. **TM[0xc008] = 0** write missing (small, may not be load-bearing
   but stock does it).

### Theory of cause

The HW is in a "partially initialized" state when our mainline code
runs. We benefit from residual register values from the prior stock
boot (e.g. 0x40018 = 2). But some registers got cleared / reset to
defaults by `pon_reset(-1)` that stock DOES run at module init —
and our mainline never executes pon_reset. Without it:

- The HW reset cycle never happens.
- Internal HW state machines that gate "frame → TM RX → bit 0 IRQ"
  remain in a clamped state.
- PP[0x2c] write to bit 29 is rejected because the HW is in a
  pre-reset mode where that register is read-only.

### Next-session implementation roadmap

1. **Add a `zx_pon_init` function in mainline** that mirrors stock's
   `zx_pon_init` exactly:
   ```c
   static int zx_pon_init(struct zx_eth *e)
   {
       /* a-c: reserve mem, pon mode — we don't need these on mainline */
       /* d: print lan_up_port — informational */
       /* e: already done by DT parse */

       /* f-g: pon_reset() — ⚠️ NEED TO RE-IMPLEMENT */
       u32 v = readl(e->pon_early + 8);
       writel(v & ~0xffffffffu, e->pon_early + 8);
       msleep(10);
       writel(v | 0xffffffffu, e->pon_early + 8);

       /* h: pon_base + 0x40018 = 2 */
       writel(2, e->pon_early + 0x40018);

       /* i: zx_pon_clk_reset_init — need to port this carefully */
       /* This requires top_crm_base, pon_serdes_base, sys_ctrl_base.
        * The serdes calibration is involved (read pon_serdes_base + 0x68
        * waiting for bit 4, then band calc from temp_ctrl_read). */
       zx_pon_clk_reset_init(e, 1);  /* NEW helper */

       /* j: register_pon_int — request_threaded_irq for irq_pon */
       err = devm_request_irq(dev, e->irq_pon, zx_pon_irq, 0, "pon", e);
       if (err) return err;

       /* k-l: writes ordered */
       writel(0xffffff7f, e->pon_early + 0x40044);
       writel(0xf,        e->pon_early + 0x4001c);

       msleep(1);

       /* n: tm_pon_tm_init equivalent — we have zx_eth_init_chip_tm */
       zx_eth_init_chip_tm(e);
       /* + missing: writel(0, e->base + 0xc008) */

       /* p: tm_pon_pp_init — we have via apply_stock + pp_brg + etc */

       /* q: tm_pon_npp_init — we have most but missing IDM netdev */

       /* r: if lan_up: PP[0x2c] |= BIT(lan_up_port + 0x19) */
       if (lan_up) {
           u32 v = readl(e->base + PP_OFF + 0x2c);
           writel(v | BIT(lan_up_port + 0x19), e->base + PP_OFF + 0x2c);
           zx_pon_clk_reset(e);  /* NEW helper */
       }
       return 0;
   }
   ```

2. **Fix PP_CPU_FWD_BIT to derive from lan_up_port**:
   ```c
   #define PP_CPU_FWD_BIT(lan_up_port)  BIT((lan_up_port) + 25)
   /* For lan_up_port=4: BIT(29) */
   ```
   And read `lan_up_port` value from a DT property or hard-code to 4
   for the H3600.

3. **Verify pon_irq is wired**: check our DT has `interrupts` for
   "pon" (GIC SPI 0x42 = 66), "pp" (0x45 = 69), "npp" (0x43 = 67).
   Currently only "tm", "npp", "idm" are in DT.

4. **TM[0xc008] write**: add `writel(0, e->base + 0xc008)` after
   `pon_tm_bmu_enable` in `zx_eth_init_chip_tm`.

## Status of fixes already applied this session

| Commit | Description | Confidence | Helped? |
|---|---|---|---|
| `9a278d294` | UP/DN DMA rings separated | High (RE-validated) | HW state changed but ping unchanged |
| `f20382821` | BMU release in NAPI | High (matches stock soft_release_rx_desc) | Stops leak; ping unchanged |
| `f7c6fc9d7` | SMAC_LOOK_EN to 0xff | High (matches stock 0xff) | Live state correct; ping unchanged |
| `a9691534a` | PP_CPU_FWD_BIT OR | Architecturally right but wrong bit (BIT(25) vs BIT(29)) AND register HW-locked | No live effect |
| `b3411b71a` | Queue counter high16 | High (stock pon_tm_net_poll RE-confirmed) | No effect (NAPI doesn't run anyway) |

## Final recommendation

The 6 fixes are correct in isolation but **the HW is operating in a
state that doesn't permit the RX IRQ to fire**, because of the missing
`pon_reset` → SERDES bring-up → ordered helper calls ceremony. The
fix is to implement a proper `zx_pon_init()` equivalent in mainline.
Estimated effort: 4-8 hours including testing.

## EOD update — PP[0x002c] is HW-write-protected on most bits

Bench test 2026-05-27 EOD: writing 0xffffffff to PP[0x002c] via
`busybox devmem` and reading back yields **0x00000f0f**.

Writable bits: only bits 0-3 and 8-11 (`mask = 0x00000f0f`).
Bits 25 (PP_CPU_FWD_BIT) and 29 (`lan_up_port + 0x19`) are NOT
writable via direct register access. They stay 0 regardless of what
we write.

Stock decomp shows stock writes via:
```c
*(pp_base + 0x2c) |= 1 << (lan_up_port + 0x19);  // bit 29
```
which is a normal read-modify-write. **Yet stock somehow succeeds.**

Possible explanations:
1. Stock's `pp_base` is at a DIFFERENT physical address than ours
   (different of_iomap mapping). Our pp_base = 0x92380000.
2. There's an indirect-write mechanism not yet RE'd (a config
   register that gates write access to the upper bits).
3. The HW enters a different state after stock's full init ceremony
   where the upper bits become writable.

Status of pon+8 (reset register):
- Live mainline reads `pon_base + 8 = 0xffffffff` → already in
  post-reset state. So `pon_reset(0xffffffff)` would be a no-op.
- That rules out "HW stuck in reset" hypothesis.

Status of `register_pon_int` etc:
- Mainline has no PON, PP, or NPP IRQ registered. Only TM and IDM.
- This may keep upstream queues backpressured if they need draining
  via dedicated IRQ servicing.

## ⭐ ENORME UPDATE — Missing SERDES/sys_ctrl/pin_mux mappings

Per sibling-chip DT (`refs/zte-zx279128R/zx279128R.dts`), stock's
`pon@92000000` node has SEVEN reg ranges:

```
0x92000000 0x2000000   # pon_base (range 1)
0x92000000 0x140000    # pon (range 2, partial)
0x92000000 0x2000000   # pon (range 3, duplicate)
0x94000000 0x100000    # top_crm_base
0x94100000 0x100000    # sys_ctrl_base
0x94200000 0x100000    # pin_mux_base
0x9fe00000 0x100000    # pon_serdes_base
```

**Mainline only maps 4 of 5 unique blocks**:

| Block | Stock | Mainline | Live read |
|---|---|---|---|
| pon_base | ✅ 0x92000000 | ✅ `e->pon_early`/`fpga_base` | active |
| top_crm | ✅ 0x94000000 | ✅ `e->topcrm` | active |
| sys_ctrl | ✅ 0x94100000 | ❌ MISSING | live: mostly 0, 0x100 @ +0x10 |
| pin_mux | ✅ 0x94200000 | ❌ MISSING | live: `0x0f0ffffa` etc — active config |
| pon_serdes | ✅ 0x9fe00000 | ❌ NOT EVEN IN DT | live: `0x800010a7` etc — HW alive |

(Live readings via devmem 2026-05-27 EOD)

**Stock's `zx_pon_clk_reset_init` writes to pon_serdes_base** (decomp
line 8284) including a temperature-compensated band calibration. We
**don't replicate this** at all in mainline.

## Why Phase 50 ping worked but now doesn't (revised theory)

Phase 50 worked because the test flow was:
1. Reboot to stock (NAND boot)
2. Stock runs full init: pon_reset, SERDES band calibration, pin_mux setup
3. Power stays on
4. TFTP-boot mainline kernel **into RAM** (no HW reset)
5. Mainline kernel inherits stock's HW state — including the proper
   SERDES calibration and pin_mux config
6. Ping bidi works because the HW is properly configured

Today the test flow is the same, **but SERDES calibration drifts with
temperature**. The H3600 has been on for hours, possibly warmed up
beyond the band stock calibrated for. When the temperature shifts
more than ~6°C from the calibration point, the SERDES becomes
marginal — frames still get to MAC level but data integrity at the
internal switch fabric degrades. Symptoms: TM IRQ stops firing
because frames don't make it through the switch with valid CRC.

This would also explain why **early in the morning** ping might work
(cooler chip) and **after sustained activity** it breaks.

## Confirmation experiment

To confirm the theory:
1. Cold-reboot device fully (DTR pulse) to stock
2. Run ping bidi for ~5 minutes — should work
3. Wait 30 minutes (chip warms up)
4. Re-test ping — should still work (stock recalibrates if it drifts)
5. Now TFTP-boot mainline
6. Run ping — predict will fail (mainline can't recalibrate SERDES)

If ping works in step 2-4 but fails in step 6 reproducibly, theory
confirmed.

## Probably-right concrete next steps (in priority order)

1. **Verify pp_base address**: dump stock /proc/iomem to see where
   "pp" maps in its address space. Compare with our PP_OFF=0x1c0000
   from npp base. They may differ.

2. **Register the missing IRQs**: add devm_request_irq for PON,
   NPP, and PP in addition to TM and IDM. Even empty handlers might
   help if the HW needs them serviced to avoid backpressure.

3. **Look for indirect "write enable" register** by:
   - Searching stock for register reads in `0x80..0x100` range of
     pp_base around the time it sets PP[0x2c]. There may be a
     "config commit" register.
   - Verifying via memdump on stock LIVE what PP[0x002c] reads as
     and what bit pattern it has bits 25/29 set to.

4. **Read PP[0x002c] on running stock** to confirm bit 29 IS set
   there. If it is → stock can set it; we just don't know how. If
   it ISN'T → maybe the bit's role is different from what the RE
   suggested.

## 🚨 CRITICAL UPDATE — TX is also broken at wire level

Bench test 2026-05-27 EOD via host-side tcpdump filter on sw MAC:

```bash
sudo tcpdump -i enxc8a362e95900 -n -e ether src f4:f6:47:0f:42:64
```

Triggered TX from mainline device by:
- `busybox ifconfig sw down` + `up` (gratuitous ARP on bring-up)
- `busybox ifconfig sw 192.168.1.99 netmask 255.255.255.0` (re-add IP)
- Multiple cycles

Driver counter `tm_tx_count`: 16 → 63 (+47 TX operations)
Host tcpdump capture: **0 frames received**

The driver believes it transmitted 47 frames, but **zero reached the
host's NIC at wire level**. TX is broken just like RX — not just the
TM→CPU NAPI delivery path, but **the entire frame path from driver
through HW to physical cable**.

This rules out all RX-specific theories. The bug is in a path SHARED
by TX and RX:
- Pin mux (not mapped in mainline; live shows `0x0f0ffffa` etc — may
  be wrong config)
- MAC[2] clock/enable to PHY (link reports up but doesn't drive PHY)
- Switch fabric egress dropping at MAC handoff
- PHY TX-path disable (link UP on RX side but TX side off)

Next session: compare MAC[2] (0x92280000) + pin_mux (0x94200000)
live values stock-vs-mainline. Differences there are the real bug.

## 🔥 ULTRA-CRITICAL FINDING — HW won't consume our TX

Bench test 2026-05-27 even-later EOD via debugfs dump:

```
tm_tx_count               = 63   ← driver pushed 63 TX descriptors + kicks
TM[0x10058] DMA_DESC_CNT_UP = 0x00290000   ← 41 pending (high16) NOT consumed
TM[0x10054] TX kick          = 0x00000001  ← kick is set
```

We kicked 63 TX through the UP path (sw netdev TX path, per stock
soft_insert_tx_1desc). HW consumed only **22 of 63** (63 - 41 pending
= 22). The other 41 are queued in the UP TX ring but the HW **never
consumes them**.

Combined with:
```
q[0] RX queue counter = 0x00060000  ← 6 frames pending (host pings)
```

The **RX path works** up to the TM CPU queue (HW classifies host pings
correctly, puts them in queue 0).

The **TX path is broken** at the HW switch-fabric egress consume
engine — we kick, descriptors queue, but HW doesn't drain.

This rules out everything we've been investigating (TM IRQ, BMU pool,
PP_CPU_FWD_BIT, queue counter interpretation) as the primary cause.
The bug is **upstream**: the HW that should pull TX descriptors from
the UP ring and forward to MAC[N] for serialization is **not running**.

### What could gate HW TX consumption?

1. A specific "TX engine enable" bit in some control register
2. A clock to the switch-fabric egress path that's not enabled
3. The TX desc format may be wrong (HW skips invalid descriptors,
   counting them as "pending" forever)
4. A "credit" mechanism (similar to BMU) for TX-side that's exhausted
5. The dndesc_dma DMA region (for DN path) needs to also be set for
   UP path because HW expects coupled state

The fact that **stock works with the same DMA address scheme** (UP and
DN at distinct phys addresses) suggests stock has the right "TX enable"
sequence. We're missing it.

### Why bit 0 of TM[0x100] never fires (linked to TX bug)

If the switch-fabric is partially wedged (TX engine off, RX engine on),
the HW might also gate IRQ assertion to prevent SW from servicing the
RX queue while TX is stuck. This would prevent NAPI from running and
draining RX, creating the observed "RX frames queue without
notification" symptom.

So the TX bug and RX-IRQ bug may have a **single common root cause** in
the switch-fabric enable / clock / control state.


## Final RE finding — Stock has periodic TX reclaim timer

Stock decomp `pon_tm_check_tx_done_nolock` (decomp 6360):
```c
void pon_tm_check_tx_done_nolock(int dir) {
    if (dir != 1)
        net_txq.tx_done -= (TM[0x10058] & 0xffff);   // sw netdev
    else
        net_txq.tx_done_pon -= (TM[0x10068] & 0xffff); // pon netdev
}
```

Called every jiffy by `pon_tm_timer` (decomp 6436, runs from `add_timer`
in `pon_tm_net_init`). For each direction, reads the **low 16 bits of
the DMA_DESC_CNT register** and subtracts it from a SW pending counter.

This is the SW-side "reclaim" that completes the TX cycle.

**Mainline doesn't have this timer.** Without it:
- HW may be using TM[0x10058] low16 as "consumed since last read" — a
  clear-on-read counter. Without periodic reads, HW thinks SW never
  acknowledges → never advances internal cursor → ring fills → no more
  consumption.
- OR mainline's TX desc format may be subtly wrong (bad checksum,
  invalid valid-bit), HW skips them, counts them as queued forever.

Three hypothesis for next session, in order of likelihood:

### Hypothesis 1: TM[0x10058] low16 is clear-on-read

Add a periodic timer in mainline that reads TM[0x10058] every jiffy.
If the read itself drives the HW state, this fix is one line:

```c
mod_timer(&e->tx_reclaim, jiffies + 1);
static void tx_reclaim_fn(timer) {
    (void)tm_read(e, 0x10058);  // discard — read advances HW
    (void)tm_read(e, 0x10068);
    mod_timer(&e->tx_reclaim, jiffies + 1);
}
```

Easy to test. If ping bidi comes back after adding this, hypothesis
confirmed.

### Hypothesis 2: TX desc format bug

We already wire desc[0]=0xc9, desc[2..3]=port hint, desc[8..11]=
bp_idx+len, desc[12..13]=len<<2. But there could be other bits/bytes
HW expects (e.g., a VALID bit at desc[15]) that we omit. Stock's
`pon_tm_data_raw_send` (decomp 6596) should be the authoritative
TX desc format. Compare line-by-line with our `zx_sw_xmit`.

### Hypothesis 3: Missing TX engine enable register

There may be a register that gates the HW "TX consume engine" from
running. Search stock init for any "tx_en" / "egress_en" type writes
near tm_pon_tm_init that we might have missed.

## Total commits this session

```
915120431 findings: HW won't consume TX descriptors — switch fabric egress wedged
bd3bc21a3 findings: TX also broken at wire level — bug is shared TX+RX path
a20e1f83c RE: full stock init sequence analysis + mainline gap matrix
b3411b71a NAPI: read queue pending count from high 16 bits (un-revert Phase 51)
a9691534a PP: OR PP_CPU_FWD_BIT into PP[0x002c] (Phase 50 + stock-validated)
f7c6fc9d7 PP: restore SMAC_LOOK_EN to 0xff (Phase 50 baseline + stock)
f20382821 TM NAPI: re-introduce zx_bmu_free_bp per descriptor (delivered + dropped)
5b3407ca4 TM: also use distinct dndesc_dma in repoint helper
9a278d294 TM RX: allocate distinct DN ring; document stock fixed-RAM strategy
```

