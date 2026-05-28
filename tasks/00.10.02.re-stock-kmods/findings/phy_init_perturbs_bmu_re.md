# PHY init perturbs BMU/TM — root cause RE

**Empirical bug** (A/B test 2026-05-28):

| `ZX_SKIP_PHY_INIT` | BMU alloc | `tm_tx_dropped` | `TM[0x100]` |
|---|---|---|---|
| `1` (skip mainline `phy_init_hw + phy_attach_direct`) | works | 0 | `0x7700` (bit 1 = clear) |
| `0` (run mainline PHY init) | broken | ≥1 | `0x7702` (bit 1 = TX_DONE set) |

i.e. **running mainline's PHY init asserts the TM TX_DONE roll-up bit
on TM[0x100], which the IRQ handler then sees as work pending while the
HW TX path is wedged**. Sources used for the RE below:

- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_plat_zxylzb_9128S.c`
  — `pon_npp_smac_init`, `gephy_ldo_init`, `gephy_tx_dac_drv_force_enable`,
  `gephy_ldo_timer_func`, `extphy_timer_func`, `register_phy_int`,
  `phy_process`, `smac_init`.
- `tasks/00.10.02.re-stock-kmods/findings/eth_init_flow_2026_05_26.md`
  — full live-captured stock module init order.
- `tasks/00.10.02.re-stock-kmods/findings/tm_100_status_bit_decode.md`
  — bit-level decode of TM[0x100] including bit 1 = TX_DONE.
- `tasks/00.10.01.re-vmlinux/vmlinux.dis` — disassembly of stock's
  `zx_mdio_read` / `zx_mdio_write` (vmlinux-resident).
- `tasks/00.10.03.re-uboot/findings/static_analysis_uboot_eth.md`
  + `uboot_eth_decomp/FUN_40e50c40.c` — U-Boot PHY init (none of LDO /
  TX-DAC; only reads `0x1e` / `0x1a` + pulses per-port reset).
- `linux-v6.6/drivers/net/phy/phy-zte-gephy.c` — mainline PHY driver.
- `linux-v6.6/drivers/net/phy/phy_device.c` — `phy_init_hw`,
  `phy_attach_direct`.
- `linux-v6.6/drivers/net/mdio/mdio-zte.c` — mainline MDIO controller.
- `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c::zx_eth_init_phys`
  — mainline driver's PHY bring-up.

---

## 1. Stock PHY init — order, registers, timing

### 1.1 Call order inside `plat-zxylzb_9128S::zx_pon_init`

```
zx_pon_init                                              (plat:8900)
├─ pon_reset(0xffffffff) + msleep(10)
├─ TOPCRM block clock-gate + register_pon_int()
├─ TM[0x40044]=0xffffff7f; TM[0x4001c]=0xf; msleep(1)
├─ tm_pon_tm_init()                                      (plat:7062)
│   ├─ pon_tm_red_init                  ← BMU RED config
│   ├─ pon_tm_dma_init                  ← TM DMA channels
│   ├─ pon_tm_bmu_init                  ← BPPE pool + TM[0x8004/0x8058/...]
│   ├─ pon_tm_bmu_enable                ← TM[0x8000]=1
│   ├─ TM[0xc008]=0                     ← post-bmu fence write
│   ├─ pon_tm_net_init                  ← netdev "sw"+"pon", napi, queue init, tm_timer
│   └─ pon_tm_int_init                  ← TM[0x104]=0xffffffff (all masked); request_irq
├─ netdebug_module_init()
├─ tm_pon_pp_init()                     ← PP block
└─ tm_pon_npp_init()                                     (plat:2238)
    ├─ tm_pon_idm_init
    ├─ pon_npp_spa_init
    ├─ pon_npp_sipc_init
    ├─ pon_npp_smct_init
    ├─ pon_npp_smac_init                                 (plat:3273) ←★ PHY HERE
    ├─ pon_npp_sip_init
    └─ pon_npp_uopc_init
```

**Critical**: BMU init **+ enable + tm_net_init** all complete BEFORE any
MDIO/PHY transaction happens. By the time the first
`zx_mdio_write(...)` fires for a PHY, the BMU pool is armed, the
TM IRQ handler is registered, and `TM[0x104]` has all bits masked.

### 1.2 `pon_npp_smac_init` (plat:3273) — exact MDIO sequence

```c
pon_npp_smac_init() {
    gephy_ldo_init();                       // (1) LDO arm — 4× PHYs
    for (i = 0; i < 4; i++) {
        zx_mdio_write(uni_phy[i], 0x10, 0x8001);   // (2) ext page select
        zx_mdio_write(uni_phy[i], 0x11, 0x0000);   // (2) ext data write
        smac_init(i);                              // (3) MAC[i] regs
        npp_base[0x40000*(i+1)] |= 2;              // (3) NPP smac-enable bit
        uni_phy_stat[i] = 0xffffffff;
        has_phy_int[i] = 1;
    }
    phy_process(0);                         // (4) flush PHY event queue
    add_timer(gephy_ldo_timer, +200);       // (5) start LDO temp watchdog
    register_phy_int();                     // (6) per-PHY IRQ arm
    zx5201_config();                        // (7) external PHY (ZX5201)
    add_timer(extphy_timer, +10);           // (8) external PHY poll timer
    uni_phy_stat[4] = 0xffffffff;
    // (9) restart autoneg on lan_up_port ONLY:
    int p = lan_up_port;                    // = 4 on H3600 (cspstart)
    uint v = zx_mdio_read(uni_phy[p], 0x00);
    zx_mdio_write(uni_phy[p], 0x00, v | 0x800);
}
```

`gephy_ldo_init` (plat:2972), per PHY:

| MDIO write | Meaning |
|---|---|
| `(phy, 0x17, 0x2448)` | LDO control magic |
| `(phy, 0x10, 0xb640)` | ext-page select for LDO arm reg |
| `(phy, 0x11, 0x001f)` | enable all 5 LDO domains |

`register_phy_int` (plat:3074), per PHY:

| MDIO write | Meaning |
|---|---|
| `(phy, 0x18, 0x0005)` | enable link-change IRQ |

then `request_threaded_irq(g_phy_irq[i], zx_phy_int, ...)`.

**Stock writes ONLY these registers at init time**:
- `0x17 = 0x2448` (LDO ctrl)
- ext `0xb640 = 0x001f` (LDO arm)
- ext `0x8001 = 0x0000` (purpose unclear — possibly "no override" pin
  mux, written once per PHY)
- `0x18 = 0x0005` (link IRQ enable, via `register_phy_int`)
- `0x00 |= 0x800` (autoneg restart) — **only the `lan_up_port` PHY**

**Stock does NOT write the `tx_dac_drv_force_enable` extended registers
(`0xb676/77/67/68/c2/c1/78/69`) at init.** Those writes happen ONLY
inside `gephy_ldo_timer_func` (200-jiffy = 2 s timer) when:
- die temp > 0x32 °C / < 0x3b °C (LDO 0x1f / 0x1c mux), or
- a port's no-cable counter reaches 0x1e (re-arm autoneg path), or
- the autoneg loop has been stuck > 0x14 attempts (force redrive).

I.e. **stock treats tx_dac writes as a corrective / runtime
compensation, not init**.

### 1.3 Stock `zx_mdio_write` accessor (vmlinux T section, `c00174c4`)

```
spin_lock_bh                          // _bh: disables BHs/softirqs
                                       // but NOT hardirqs (e.g. TM IRQ)
CTRL &= ~0x4000                       // GO=0 (park)
DONE  = 0                              // clear done
CTRL &= ~0xc00                         // OP=0
CTRL |=  0x400                         // OP_WR
WDATA = wdata
CTRL  = ... (PHYAD<<5 | REGAD)
CTRL |= 0x4000                         // GO=1
poll DONE != 0 (max 10000 iterations)
CTRL &= ~0x4000
DONE = 0
spin_unlock_bh
```

Identical opcode pattern to mainline `mdio-zte.c::zte_mdio_xfer` BUT:

- Stock uses `spin_lock_bh` → reschedules disabled, softirqs disabled,
  hardirqs ENABLED. So a TM hardirq can fire mid-MDIO, and stock's
  `zx_pon_tm_int` runs to completion (mostly `__napi_schedule`).
- Mainline uses `mutex_lock` → can sleep. Hardirqs ENABLED (same), but
  also schedule may run, meaning the MDIO operation can be delayed by
  preemption / scheduling latency.

Practical poll budget: 10000 iterations × ~100 ns each = up to ~1 ms
per MDIO xfer. Each xfer worst-case takes ~30 µs in practice (HW MDIO
clock).

---

## 2. Mainline PHY init — order, registers, timing

### 2.1 Call order inside `zx-eth-main.c::zx_eth_probe`

```
zx_eth_probe
├─ zx_eth_init_chip_pon_setup            (pon_reset + small writes)
├─ zx_eth_init_vlan_and_isolation
├─ zx_idm_init                           ← IDM ring + IRQ
├─ for i in 0..ZX_NPORTS: zx_eth_probe_port (netdev per LAN port)
├─ netif_napi_add_weight(ports[0], idm_poll, 512)
├─ devm_request_irq(irq_idm, zx_idm_irq)
├─ zx_eth_init_tm_subsystem                                   ←★ BMU HERE
│   ├─ zx_tm_alloc_pools                ← dma_alloc_coherent
│   ├─ zx_tm_pre_init / zx_tm_red_init / zx_pp_ctrl_init /
│   │  zx_pp_brg_init / zx_tm_dma_init
│   ├─ zx_tm_bmu_init                   ← TM[0x8004/0x8058/...]
│   ├─ zx_tm_post_bmu                   ← TM[0xc008]=0
│   ├─ zx_tm_bmu_enable                 ← TM[0x8000]=1
│   ├─ zx_sw_netdev_create
│   ├─ devm_request_irq(irq_tm, zx_tm_irq)        ← TM IRQ live from here
│   ├─ zx_eth_register_cpu_mac_slots
│   ├─ zx_eth_init_chip_tm
│   ├─ zx_pp_pm_apply_replay
│   └─ zx_eth_repoint_tm_descriptors
├─ devm_request_irq(irq_pon, zx_pon_irq)
└─ zx_eth_init_phys                                          ←★ PHY HERE
```

The order **matches stock** (BMU+TM up *before* PHY).

### 2.2 `zx_eth_init_phys` (`zx-eth-main.c:3768`) — call sequence per PHY

```c
for each gephy:
    phy_init_hw(phydev);                     // (A) runs config_init + config_intr
    phy_attach_direct(sw_dev, phydev, 0, MODE_INTERNAL);  // (B) — also runs phy_init_hw internally
    phydev->adjust_link = zx_eth_adjust_link;
    phy_request_interrupt(phydev);
    phy_start(phydev);
```

`phy_init_hw` (`phy_device.c:1226`):

```c
phy_device_reset(phydev, 0);                 // GPIO PHY-reset deassert (no-op here)
if (drv->soft_reset)    drv->soft_reset();   // not provided → skipped
phy_scan_fixups();                            // none registered for our PHY ID
if (drv->config_init)   drv->config_init();  // <-- LDO + 8× TX-DAC writes
if (drv->config_intr)   drv->config_intr();  // <-- writes 0x18 = 0x0005
```

`phy_attach_direct` (`phy_device.c:1429`):

```c
... module-refcount + sysfs bookkeeping ...
phydev->state = PHY_READY;
phydev->interrupts = PHY_INTERRUPT_DISABLED;  // <-- DISABLES IRQ flag
...
err = phy_init_hw(phydev);                    // <-- RUNS phy_init_hw AGAIN
                                              //     config_intr now writes 0x18 = 0
                                              //     because interrupts==DISABLED
phy_resume(phydev);
```

**Net effect, per PHY**:

| Step | MDIO writes |
|------|---|
| `phy_init_hw` #1 (our call) | `0x17=0x2448`, ext `0xb640=0x001f`, 8× tx_dac ext writes, `0x18=0x0005` |
| `phy_attach_direct → phy_init_hw` #2 | same `0x17`/`0xb640`/8× tx_dac, then `0x18=0x0000` (because PHY_INTERRUPT_DISABLED set inside attach) |
| `phy_request_interrupt` | sets `phydev->interrupts=PHY_INTERRUPT_ENABLED`, internally calls `config_intr` → `0x18=0x0005` again |
| `phy_start` | kicks state machine, will call `phy_init_hw` a 3rd time after suspend/resume in some paths |

So per PHY, **~24 MDIO writes** of mostly-redundant LDO/TX-DAC poking,
plus 3 toggles of the IRQ enable bit 0x18, ALL while `TM[0x104]` has
bits 1+ unmasked (mainline writes `TM[0x104] = 0xfffffffe` — only bit 0
masked; **stock writes `0xffffffff` — ALL masked at init and only opens
bits 0+1 in `pon_tm_net_open` after the netdev is up**).

For 4 PHYs that's **~96 MDIO transactions** at init, each ~30 µs, total
~3 ms of MDIO bus activity.

### 2.3 The `config_intr` interaction

`zte_gephy_config_intr` writes `0x18 = 0x0005` (link IRQ enable) when
`phydev->interrupts == PHY_INTERRUPT_ENABLED`, else `0x18 = 0`.

After mainline's sequence:
1. `phy_init_hw` #1: `interrupts` field still has whatever was set at
   probe (default `PHY_INTERRUPT_ENABLED`), so we write `0x0005`. PHY
   immediately becomes capable of asserting the GIC line.
2. `phy_attach_direct` line 1519 sets `interrupts = PHY_INTERRUPT_DISABLED`.
3. `phy_attach_direct → phy_init_hw` #2 → `config_intr` writes `0x18 = 0`.
4. `phy_request_interrupt` flips back to `PHY_INTERRUPT_ENABLED`,
   re-arms.

During the window between (1) and (2), the PHY's IRQ line is armed but
the GIC IRQ is NOT yet `request_irq`'d at the Linux side. Stock never
hits this window — `register_phy_int` does the GIC request **AT THE
SAME TIME** as the `0x18=5` MDIO write (in a loop where each iteration
is `mdio_write(phy[i], 0x18, 5); request_threaded_irq(g_phy_irq[i],
zx_phy_int, ...)`).

---

## 3. MDIO controller activity & shared resources

### 3.1 The controller @ `0x9a101000`

Standalone MMIO block, 0x18 bytes:

```
+0x04  WDATA   (u16)
+0x08  RDATA   (u16)
+0x10  DONE    (HW sets nonzero on completion)
+0x14  CTRL    (PHYAD/REGAD/OP/GO bits)
```

Power/clock: **No DT property in either stock or mainline maps a clock
or reset to this controller** (`linux-v6.6/arch/arm/boot/dts/zte/
zx279128s.dtsi:232-269` — bare `reg = <0x9a101000 0x18>`). The
controller is part of the always-on PERI sub-block that U-Boot's
Phase-A (FUN_40e40454) configures and never gates off.

The TM block and the MDIO controller are at completely separate phys
windows (`0x92340000` vs `0x9a101000`) and there is no documented
clock/reset sharing.

### 3.2 No direct PHY → BMU hardware path

There is no MMIO bit that goes "MDIO write → BMU action". MDIO is a
serial protocol controller; its writes affect the PHY chip only, not
the SoC switch fabric. The connection between PHY and SMAC happens via
the RGMII / internal MAC interface — physical link state, not MMIO.

### 3.3 The real propagation path: PHY → link UP → switch fabric → BMU back-pressure

Looking at stock's behavior on link UP (`extphy_timer_func` plat:3137):

```c
when link state changes to UP for phy[N]:
    pon_reset(1 << (N + 6));           // <-- per-port HW reset pulse!
    smac_init(N);                      // re-init MAC[N] regs
    pon_npp_smac_config_speed_duplex(N, speed, duplex);
    smac_sopc_mode_switch(N, duplex);
    pon_npp_smac_enable(N);            // (re-)enable port for traffic
```

So when a PHY transitions to "link up", stock issues a **per-port
peripheral reset** of the switch fabric for that port BEFORE
re-enabling MAC. The reset pulse writes `pon_base[0x8] = 1 << (N+6)`
which clears all latched state of switch ports 6/7/8/9 (= LAN1..LAN4)
including any wedged TX FIFOs.

Now the empirical bug story:
- With `ZX_SKIP_PHY_INIT=1`: mainline never touches the PHYs. PHYs are
  in U-Boot state — already auto-negotiated, link is reported UP from
  before, no transition occurs, no MAC re-init. BMU+TM stay in the
  clean state mainline put them in. `TM[0x100] bit 1 = 0`.
- With `ZX_SKIP_PHY_INIT=0`: mainline runs `phy_init_hw`. The first
  thing `zte_gephy_config_init` does is `phy_write(phydev, 0x17,
  0x2448)` + ext `0xb640=0x001f` — **re-arming the LDO**. This causes
  the PHY's internal MAC↔analog interface to briefly drop and
  re-establish. RGMII de-asserts then re-asserts. The MAC sees this as
  a link-down → link-up transition.
- Mainline does NOT have an `extphy_timer_func` equivalent that issues
  the `pon_reset(1 << (N+6))` per-port reset on UP. So mainline's
  internal switch port for whichever PHY just hiccupped enters its
  "after link UP" state with stale TX FIFO contents (the TX descriptors
  mainline pre-populated in BMU init). Those stale descriptors trigger
  the `TX_DONE` rollup bit (bit 1) on TM[0x100] because their `done`
  bit is being asserted by HW but the read-cursor never advances —
  same wedge documented in `915120431` "TM won't consume TX
  descriptors".

In short: **mainline's `config_init` LDO re-arm causes an RGMII glitch
on every PHY at probe time, which puts the switch fabric's TX FIFOs in
the same wedged state we already know about — but earlier, before any
traffic, so we see it as "BMU broken on first packet"**.

### 3.4 MDIO interrupts / clock gating

- No interrupt from the MDIO controller (no `interrupts` property in DT).
- No "MDIO done" IRQ races with TM IRQ; done is polled.
- No shared clock gate between MDIO and BMU/TM (different power
  domains per U-Boot Phase-A code).

So Q3's literal "shared resource" answer is **none directly**. The
coupling is **PHY analog re-arm → RGMII glitch → switch fabric TX FIFO
state**.

---

## 4. Diff table — stock vs mainline PHY init

| Aspect | Stock | Mainline | Severity |
|---|---|---|---|
| Init order relative to BMU | PHY init AFTER BMU+TM up (matches) | PHY init AFTER BMU+TM up (matches) | n/a — both correct |
| `config_init` runs how many times | Once per PHY (inside `pon_npp_smac_init`) | TWO times per PHY (once from our `phy_init_hw` call, once from `phy_attach_direct`'s internal `phy_init_hw`) | 🟡 redundant MDIO traffic |
| LDO arm writes (`0x17=0x2448`, ext `0xb640=0x001f`) | Yes, at init, once per PHY | Yes, at init, twice per PHY (× 4 PHYs = 8) | 🔴 **prime suspect — triggers analog re-arm** |
| TX-DAC writes (ext `0xb676/77/...`) | **NO** — only the runtime LDO timer writes these, conditionally | YES, 8× ext writes per `config_init` call → 16× per PHY → 64× total at probe | 🟡 unnecessary MDIO churn; values may not match stock's mode-1 set |
| Ext page-select write `0x10=0x8001 / 0x11=0x0000` | Yes, once per PHY in `pon_npp_smac_init` | **NO** — mainline does not write this | 🟡 unknown purpose; might be a pinmux/strap unlatch |
| Per-port `pon_reset(1<<(N+6))` on link UP | Yes (in `extphy_timer_func`) | **NO** — `zx_eth_adjust_link` only writes `MAC[N].ctrl` | 🔴 **second prime suspect — leaves switch fabric in wedged state on every PHY link transition** |
| `smac_init(N)` (full MAC reg re-init) on link UP | Yes | **NO** — adjust_link only twiddles enable/disable bits in `MAC[N].ctrl` | 🔴 related to above |
| Per-PHY IRQ arm (`0x18=0x0005`) toggles before GIC request | One write, then immediate `request_threaded_irq` (tight loop, same iteration) | Three toggles: `0x0005 → 0x0000 → 0x0005`. GIC `request_irq` happens AFTER the toggles (`phy_request_interrupt` does both) | 🟡 small risk of spurious IRQ during the open window |
| `TM[0x104]` mask state during PHY init | `0xffffffff` (all bits masked) — TM IRQ can't fire | `0xfffffffe` (bit 0 unmasked) — TM IRQ live during PHY init | 🟡 not the cause of the bug, but reduces safety margin |
| Autoneg restart (`reg 0 \|= 0x800`) | ONLY on `lan_up_port` (= LAN4) | NOT issued (phylib runs its own autoneg via `genphy_*` resume) | 🟡 differing autoneg timeline |
| MDIO accessor primitive | `spin_lock_bh` | `mutex_lock` | 🟢 functionally equivalent for our purposes |
| ZX5201 external PHY config | Yes (`zx5201_config`) | Not applicable on our DUT (no `0x5201` PHY ID) | 🟢 n/a |
| Periodic LDO temp watchdog (200 jiffies) | Yes (`gephy_ldo_timer`) | **NO** | 🟢 not relevant for first-boot bug, but eventually needed for temperature compensation |
| External PHY status poll (10 jiffies) | Yes (`extphy_timer`) | **NO** — we use PHY IRQs | 🟢 mainline uses IRQ which is functionally equivalent |

---

## 5. Why mainline's PHY init breaks BMU (synthesis)

1. **`zte_gephy_config_init` re-arms LDO** by writing `0x17 = 0x2448`
   and ext `0xb640 = 0x001f`. This power-cycles the PHY's internal
   analog domain on every probe.
2. The power-cycle causes a transient drop of the **RGMII clock /
   valid signals between PHY[N] and MAC[N]**.
3. The on-chip switch fabric sees this as a link-down → link-up
   sequence on internal port `(N+1)` (LAN1..4 = ports 6..9).
4. Stock handles this transition via `extphy_timer_func` which
   **issues `pon_reset(1 << (N+6))` to clear the per-port HW state**
   then re-runs `smac_init(N)` + `smac_config_speed_duplex` +
   `smac_enable`. The per-port reset clears the TX FIFO state and
   re-points the descriptor pointer.
5. **Mainline does not issue the per-port reset.** Its `adjust_link`
   only writes `MAC[N].ctrl = 0xBA6003` / `0xBA6000` to set/clear the
   RX+TX enable bits and the "post-first-link" sticky bit nibble. The
   switch fabric's TX FIFO is left in whatever state the RGMII glitch
   produced.
6. With the TX FIFO state stale, the first BMU buffer pointer fetched
   by HW for a CPU-egress (TX) operation either points to a wedged
   slot or its associated `done` bit fails to advance the read-cursor.
7. `TM[0x100]` bit 1 (TX_DONE roll-up) asserts immediately because the
   TM block's internal "TX work pending" condition is true and never
   self-clears. The IRQ handler sees pending work but `tm_tx_dropped`
   increments because BMU appears empty (HW is holding the BPs that
   never got freed).

This is consistent with all the observed symptoms:
- `TM[0x100] = 0x7702` with bit 1 set
- `tm_tx_dropped ≥ 1` even at idle
- `ZX_SKIP_PHY_INIT=1` works (no PHY perturbation → no RGMII glitch
  → no TX FIFO wedge)

It is also consistent with the prior bug "HW won't consume TX
descriptors" (`915120431`) — that bug is now identifiable as the
*persistent symptom* of the same root cause whenever any PHY has had
its config re-armed without the matching per-port reset.

---

## 6. Proposed minimal fix for mainline

Three independent options, ranked best-fit first:

### Option A — Skip `config_init` if PHY is already configured (RECOMMENDED, lowest risk)

Add an "already initialized by U-Boot" detection at the top of
`zte_gephy_config_init`: read back ext `0xb640`. If it already reads
`0x001f`, the LDO is armed — skip the rest of `config_init`. The
probe-time write was the bug; if we don't repeat it, no glitch.

```c
static int zte_gephy_config_init(struct phy_device *phydev)
{
    int armed;

    /* Detect prior init (U-Boot or warm reboot). The LDO arm bit
     * is sticky across kernel boundaries since the PHY core is
     * never power-cycled. Re-arming the LDO causes an RGMII
     * glitch that wedges the on-chip switch fabric's TX FIFOs;
     * see findings/phy_init_perturbs_bmu_re.md.
     */
    phy_write(phydev, ZTE_GEPHY_EXT_ADDR_REG, ZTE_GEPHY_EXT_LDO_ARM);
    armed = phy_read(phydev, ZTE_GEPHY_EXT_DATA_REG);
    if (armed == ZTE_GEPHY_EXT_LDO_ENABLE) {
        phydev_info(phydev, "LDO already armed — skipping config_init\n");
        return 0;
    }

    /* ... original LDO + TX-DAC writes ... */
}
```

**Pros**: minimum change, keeps the cold-boot path correct (if U-Boot
ever didn't init PHYs we still cover it).
**Cons**: relies on the LDO bit being read-back exact match. Verify
once on bench.

### Option B — Drop TX-DAC writes from `config_init`, keep only LDO arm

Move the 8× TX-DAC writes to a separate function (mirror stock's
`gephy_tx_dac_drv_force_enable`) that is NOT called from `config_init`.
Stock only calls it from the periodic timer in response to specific
runtime conditions. Mainline's `config_init` keeps just the LDO arm
(if needed) and the page-select write.

**Pros**: matches stock exactly. Removes 64 MDIO transactions from
probe.
**Cons**: doesn't fix the RGMII glitch if the LDO arm itself is what's
causing it. Useful as a *second* step combined with Option A.

### Option C — Add per-port `pon_reset(1<<(N+6))` to `zx_eth_adjust_link`

Whenever a PHY's link state flips, do what stock's `extphy_timer_func`
does:

```c
static void zx_eth_adjust_link(struct net_device *ndev)
{
    ...
    for (i = 0; i < 4; i++) {
        if (phy->link != e->phy_was_link[i]) {
            if (phy->link) {
                /* Mirror stock extphy_timer_func: per-port reset
                 * + re-init MAC before re-enabling. Clears stale
                 * TX FIFO state from the link transition.
                 */
                zx_pon_reset_port(e, i);          /* writes pon_base+8 */
                zx_smac_init(e, i);               /* MAC[N] reg block */
                zx_smac_config_speed_duplex(e, i, phy->speed, phy->duplex);
            }
            writel(phy->link ? 0xBA6003 : 0xBA6000,
                   e->base + mac_off(i, MAC_REG_CONTROL));
            ...
        }
    }
}
```

**Pros**: addresses the root cause directly. Also fixes any future
cable-swap / link-flap scenarios that hit the same bug.
**Cons**: bigger change, needs `zx_pon_reset_port` + `zx_smac_init`
helpers to exist (parts already exist in driver, just need wiring).
Risk: per-port reset could disturb other operations if mis-timed.

### Recommendation

Ship **Option A as the immediate fix** (one read-modify-skip in
`zte_gephy_config_init` — minimal blast radius, validates the
hypothesis), then layer **Option C** in a follow-up commit for
correctness on runtime link-flap. Defer Option B until after both ship
since it's cosmetic / parity work.

---

## 7. Cross-references

- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_plat_zxylzb_9128S.c`
  lines 2270-2415 (smac_init, tx_dac), 2438-2731 (gephy_ldo_timer_func),
  2914-2952 (phy_process), 2968-3021 (gephy_ldo_init), 3072-3105
  (register_phy_int), 3137-3204 (extphy_timer_func — the link-UP
  reset-+-re-init handler), 3273-3320 (pon_npp_smac_init).
- `tasks/00.10.02.re-stock-kmods/findings/tm_100_status_bit_decode.md`
  — TM[0x100] bit 1 = TX_DONE.
- `tasks/00.01.eth-driver/findings/phy_irq_state_machine_2026-05-27.md`
  — MAC[N].ctrl semantics and stock's three-state machine.
- `tasks/00.10.03.re-uboot/findings/uboot_eth_decomp/FUN_40e50c40.c`
  — U-Boot's per-port init confirms PHY reg 0x1e/0x1a reads only,
  per-port reset pulse, no LDO/tx_dac. So when mainline inherits
  U-Boot's PHY state and skips its own `phy_init_hw`, the LDO is
  already armed (set by either the on-chip strap or by an earlier
  boot stage), which is why `ZX_SKIP_PHY_INIT=1` works.
- `linux-v6.6/drivers/net/phy/phy_device.c:1226` (`phy_init_hw`),
  `:1429` (`phy_attach_direct` — second `phy_init_hw` at L1546).
- `linux-v6.6/drivers/net/phy/phy-zte-gephy.c:95-122`
  (`zte_gephy_config_init` — the function to patch).
