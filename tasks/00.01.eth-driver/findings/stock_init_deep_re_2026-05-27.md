# Stock kmod init flow — deep RE pass

Captured 2026-05-27 by walking raw Ghidra decomp of all five kmods
(`zx_ponreg`, `tm`, `switch`, `idmfdb`, `plat_zxylzb_9128S`) in
`tasks/00.10.02.re-stock-kmods/findings/decomp_all_*.c`. Every function
body cited has been read in full; absolute file:line refs given for each
claim so the doc is grep-verifiable.

This supersedes earlier `stock_init_sequence_analysis_2026-05-27.md`
where it disagrees — that doc had a stale assumption about `lan_up_port`
that the raw decomp here refutes.

## Why this doc exists

Mainline ping bidi is broken despite 10+ RE-validated fixes. Pattern
suggests a structural piece is missing, not a single bit twiddle. To
find it we need the *complete* authoritative stock init flow, not
sampled fragments.

## Module load order (lsmod evidence)

```
zx_ponreg          ← loaded 1st (low-level register accessor, only 4KB decomp)
tm                 ← uses zx_ponreg
switch             ← uses zx_ponreg + tm
idmfdb             ← uses switch
plat_zxylzb_9128S  ← uses mt7915 + idmfdb + switch + tm  ← entrypoint of chip bring-up
mt7915             ← WiFi (separate path, not relevant to LAN)
```

The actual chip bring-up runs in `plat_zxylzb_9128S` `init_module` —
which the other kmods are dependencies for. The flow chains through
helpers in plat (`pon_reset`, `zx_pon_clk_reset_init`, `tm_pon_*_init`)
plus crosses into switch+tm modules for shared APIs.

## Globals (memory-mapped regions)

| Symbol | Phys addr | Size | Set in | Mainline mapped? |
|---|---|---|---|---|
| `pon_base` | `0x92000000` | 4 MiB | DT `pon@92000000` reg[0] | ✅ |
| `top_crm_base` | `0x94000000` | 1 MiB | DT reg[1] | ✅ as `e->topcrm` |
| `sys_ctrl_base` | `0x94100000` | 1 MiB | DT reg[2] | ❌ **MISSING** |
| `pin_mux_base` | `0x94200000` | 1 MiB | DT reg[3] | ❌ **MISSING** |
| `pon_serdes_base` | `0x9fe00000` | 1 MiB | DT reg[4] | ❌ **MISSING — not even in our DT** |
| `tm_base` | (alias) `pon_base + 0x180000` | | indirect via `pon_base` offset | ✅ via `e->base + 0x180000` |
| `pp_base` | (alias) `pon_base + 0x380000` | | indirect | ✅ |
| `npp_base` | (alias) `pon_base + 0x3c0000` | | indirect | ✅ |

Three of five mappings missing in mainline. This alone is enough to
explain anything that depends on SERDES bring-up or sys_ctrl writes.

## Globals (state variables)

| Symbol | Type | Set by | Default | Stock live value |
|---|---|---|---|---|
| `lan_up` | int | `init_module` if `g_pon_work_mode == 0x10` | 0 | **1** |
| `lan_up_port` | u8 | `tm_set_p2pmode(p)` from switch.ko | 0 | **4** (= WAN port) |
| `g_pon_irq` | int | `irq_of_parse_and_map(pon_node, 0)` | — | GIC 66 = "pon" |
| `g_tm_irq` | int | `irq_of_parse_and_map(...)` | — | GIC 68 = "pon_tm" |
| `g_pp_irq` | int | — | — | GIC 69 = "pon_pp" |
| `g_npp_irq` | int | — | — | GIC 67 = "pon_npp" |
| `g_phy_irq[0..3]` | int[4] | from gephy DT children | — | GIC 71..74 |

Stock /proc/interrupts captured today during ping confirms `pon_tm` fires
~100/ping. The other "pon", "pon_npp", "pon_pp" IRQs register but fire
0 times — purely defensive registration.

## `init_module` (plat-zxylzb_9128S @ +0x1d378, decomp line 8891)

Chronological actions:

```c
printk("pon init\n");
bp_max_number = (u32_BPPE_POOL_SIZE, u32_JUMBO_BPPE_POOL_SIZE);
reserve_mem_info();                   // print pdt_mem layout (informational)
g_pon_work_mode = zte_get_pon_mode(); // RE'd: returns 0x10 = LAN-only
if (g_pon_work_mode == 0x10) lan_up = 1;
printk("lan_up=%d, lan_up_port=%d\n", lan_up, lan_up_port);  // lan_up=1 lan_up_port=4

iVar2 = of_find_matching_node_and_match(0, &zx_pon_match, 0);
while (iVar2) {
    if (of_device_is_compatible(iVar2, "zte,zx279128s-pon")) {
        pon_base       = of_iomap(node, 0);                 // 0x92000000
        top_crm_base   = of_iomap(node, 1);                 // 0x94000000
        sys_ctrl_base  = of_iomap(node, 2);                 // 0x94100000  ← MISSING
        pin_mux_base   = of_iomap(node, 3);                 // 0x94200000  ← MISSING
        pon_serdes_base= of_iomap(node, 4);                 // 0x9fe00000  ← MISSING
        g_pon_irq      = irq_of_parse_and_map(node, 0);
    }
    if (of_device_is_compatible(iVar2, "zte,zx279128s-gephy")) {
        for (i=0; i<4; i++) g_phy_irq[i] = irq_of_parse_and_map(gephy, i);
    }
    iVar2 = of_find_matching_node_and_match(iVar2, ...);
}

pon_reset(0xffffffff);                ← ❌ MISSING in mainline
msleep(10);
*(pon_base + 0x40018) = 2;            ← MAYBE missing (residue from stock)
zx_pon_clk_reset_init(1);             ← ❌❌❌ ENTIRE FUNCTION MISSING (SERDES + temp band cal + sys_ctrl writes)
register_pon_int();                   ← ❌ no PON IRQ in mainline (we have only TM IRQ)
*(pon_base + 0x40044) = 0xffffff7f;   ← maybe missing
*(pon_base + 0x4001c) = 0xf;          ← MISSING (live mainline reads 0 here)
msleep(1);

tm_pon_tm_init();                     ← ✅ have (with gaps inside, see below)
netdebug_module_init();               ← ❌ noop in mainline
tm_pon_pp_init();                     ← ✅ have via PP block init
tm_pon_npp_init();                    ← ✅ have NPP partial

if (lan_up != 0) {
    *(pp_base + 0x2c) |= 1 << (lan_up_port + 0x19);  ← bit 29 — HW-write-locked anyway
    zx_pon_clk_reset();                              ← ❌ MISSING (`top_crm_base + 0xc) |= 0x1e0`)
}
return 0;
```

## `pon_reset(uint mask)` (line 7744)

```c
*(pon_base + 8) &= ~mask;        // clear bits
udelay loop 100x;                 // ~100us delay
*(pon_base + 8) |= mask;         // re-set bits
```

Called as `pon_reset(0xffffffff)` from init_module → clears+restores all
bits of `pon_base[8]`. Establishes a known reset state for the entire
PON block (TM + PP + NPP + BMU all live under pon_base).

**Live read on stock during ping**: `pon_base + 8 = 0xffffffff`
(post-reset state, all bits set). So mainline observes a "post-reset"
state if we skip pon_reset, but only because stock booted earlier and
left it set. After a power-cycle without stock, `pon_base + 8` could be
in any state.

## `zx_pon_clk_reset_init(int param_1)` (line 8266)

The big one. Brings up the SERDES with temperature-compensated band
calibration. **Entire function missing in mainline.**

```c
ref_clk_set();                                  // helper, undocumented
*(top_crm_base + 8) &= ~0x20;
*(top_crm_base + 8) &= ~0x10;
udelay 10x;
*(top_crm_base + 8) |= 0x20;
udelay 10x;
reg_def_set();                                  // default register setup
serdes_mode_set(param_1, 0, 0);                 // SERDES mode select
*(top_crm_base + 8) |= 0x10;

while ((*(pon_serdes_base + 0x68) & 0x10) == 0) {}   // wait rxpll lock
printk("rxpll_ready\n");

retries = 20;
while ((*(pon_serdes_base + 0x70) & 0x1000000) == 0) {
    udelay;
    if (--retries == 0) {
        printk("err:pll is not ready for banding\n");
        return -1;
    }
}

iVar1 = *(pon_serdes_base + 0x70);
temp  = temp_ctrl_read();                       // CPU temperature sensor
coarse = (iVar1 << 8) >> 0x1a;                  // extract band bits 18..23
printk("serdes band cpu_temper:%d coarse:0x%x\n", temp, coarse);

// Temperature compensation:
if (temp < -6)                       coarse += 1;
else if (temp + 6 > 0xf) {                       // temp > 9
    if (temp - 10 < 0x31)            coarse -= 1; // 10..58
    else if (temp - 0x3b < 0x21)     coarse -= 2; // 59..91
    else                             coarse -= 3; // 92+
}
if (coarse > 0x3f) coarse = 0x3f;

*(pon_serdes_base + 0x44) = (val & 0xffc0ffff) | (coarse << 16);  // write band
*(pon_serdes_base + 0x40) |= 0x4000000;                            // enable band
printk("band calc fin\n");

*(sys_ctrl_base + 0x10) &= ~0x800;              // clear bit 11 of sys_ctrl[0x10]
*(top_crm_base + 0xc) |= 0x1e0;                 // set bits 5-8 of TOPCRM[0xc]
return 0;
```

**This function needs `pon_serdes_base` (0x9fe00000) and `sys_ctrl_base`
(0x94100000) — neither mapped in mainline.** It also calls
`temp_ctrl_read()` (CPU thermal sensor, also not implemented in
mainline). Without it, the SERDES is at whatever band stock left it
in. As temperature drifts, our link can become marginal silently.

## `tm_pon_tm_init` (line 7062) — TM module bring-up

```c
printk("pon tm init\n");
*(tm_base + 0x128) = 0x1fff;          // ✅ have
*(tm_base + 0x130) = 0x1fffff;        // ✅ have
udelay 10x;
pon_tm_red_init();                    // ✅ Phase 9d
pon_tm_dma_init();                    // ✅ with UP/DN dndesc_dma fix
iVar1 = pon_tm_bmu_init();
if (iVar1 >= 0) {
    *(tm_base + 0xf0) = ZX_DESC_BASE; // ✅ rxdesc_dma
    pon_tm_bmu_enable();              // ✅
    *(tm_base + 0xc008) = 0;          // ❌ MISSING — single missing write
    pon_tm_net_init();                // ⚠️ partial (we create only "sw", stock creates "sw"+"pon")
    pon_tm_int_init();                // ✅ devm_request_irq for TM IRQ
}
```

## `pon_tm_dma_init` (line 6279)

```c
*(tm_base + 0x10000) |= 0x2f0000;     // DMA ctrl OR-in bits — verify mainline does this
*(tm_base + 0x10028) = 1;
*(tm_base + 0x1002c) = 1;
*(tm_base + 0x10030) = 50000;         // timeout?
*(tm_base + 0x10034) = 0x40;
*(tm_base + 0x10004) = 0x7f;          // weight?
*(tm_base + 0x10020) = 0x20;
*(tm_base + 0x10024) = 0x20;
*(tm_base + 0x10050) = ZX_TX_UP_DESC_BASE;    // ✅
*(tm_base + 0x10060) = ZX_TX_DN_DESC_BASE;    // ✅ (we have via dndesc_dma fix)
*(tm_base + 0x10388) = 0x131217;      // odd value — check mainline replays this
*(tm_base + 0x1003c) = 0x400040;
```

**11 register writes**. Need to verify each is replicated in
`zx_eth_init_chip_tm` or stock_table.h. Most likely candidates for
"missing in mainline":
- `tm_base + 0x10000 |= 0x2f0000` — OR-in is conditional; if we only write the value we lose existing bits
- `tm_base + 0x10388 = 0x131217`
- `tm_base + 0x10004 = 0x7f`

## `pon_tm_int_init` (line 6333)

```c
*(tm_base + 0x104) = 0xffffffff;          // mask ALL initially
request_threaded_irq(g_tm_irq, zx_pon_tm_int, 0, 0, "pon_tm", &pon_tm_int_info);
```

Mainline mostly matches via `devm_request_irq`.

## `zx_pon_tm_int` (line 6306) — THE TM IRQ TOP HALF

```c
uVar1 = *(tm_base + 0x100) & 3 & ~*(tm_base + 0x104);   // unmasked active bits
if (uVar1 != 0) {
    pon_tm_net_int(*param_2, uVar1);                     // mid-half
    param_2[1]++;                                         // IRQ count
}
return 1;                                                 // IRQ_HANDLED always
```

Two-line decision: any of bit 0/1 active and unmasked → call
`pon_tm_net_int` which schedules NAPI. **Stock returns IRQ_HANDLED even
when status is 0** — defensive against spurious.

## `pon_tm_net_init` (line 6950) — netdev creation + IRQ arming

```c
pon_tm_netdev.sw  = pon_tm_net_register(1, "sw", ...);      // ⚠️ stock "sw" netdev
pon_tm_netdev.pon = pon_tm_net_register(0, "pon");          // ❌ mainline lacks "pon" netdev
set_pon_tm_int_info(pon_netdev + 0x4c0);                    // bind IRQ info to "pon"
netif_napi_add(pon_netdev, ..., pon_tm_net_poll, 0x200);    // NAPI on "pon" only
pon_tm_queue_init();
*(tm_base + 0x104) |= 7;                                    // mask bits 0,1,2 (initially masked)
init_timer(pon_tm_timer, pon_tm_timer_func);                // periodic timer
pon_tm_timer.expires = jiffies + 1;
add_timer(pon_tm_timer);
printk("pon_tm net init ok,%d/%d\n", 0xd8, 0xb0);
```

**Stock has TWO netdevs**: "sw" and "pon". NAPI bound to "pon" only.

## `pon_tm_net_open` (line 6502) — IRQ unmask gate

```c
clear_bit(0, ...);
netif_carrier_on(param_1);
if (strcmp(name, "pon") == 0) {
    DMB;
    *(tm_base + 0x104) &= 0xfffffffc;       // UNMASK bits 0+1 (RX+TX) only when "pon" opens
}
```

⇒ Stock's TM IRQ stays masked at `0x7` (bits 0/1/2) UNTIL userspace
`ifconfig pon up`. Mainline bypasses by writing mask directly in init.

## `pon_tm_timer_func` (line 6438) — periodic TX-done reclaim

```c
for (dir in {0, 1}) {                                       // sw + pon
    if (netdev[dir] != 0) {
        spin_lock;
        pon_tm_check_tx_done_nolock(dir);                   // reads TM[0x10058] / [0x10068]
        spin_unlock;
    }
}
pon_tm_timer.expires = jiffies + 1;                          // 1 jiffy
pon_tm_poll_cnt++;
add_timer(pon_tm_timer);
```

`pon_tm_check_tx_done_nolock(dir)` does (line 6362):
```c
if (dir != 1) net_txq.tx_done    -= (*(tm_base + 0x10058) & 0xffff);
else          net_txq.pon_tx_done -= (*(tm_base + 0x10068) & 0xffff);
```

**This is the periodic read of `TM[0x10058] low16` that we've confirmed
empirically is clear-on-read.** Mainline now has this in commit
`80f610eda` (after the EOD finding). The fact that current mainline
still has tcpdump=0 frames means this timer is necessary but not
sufficient.

## `pon_tm_net_close` (line 6478, indirect from net_stop)

```c
if (strcmp(name, "pon") == 0) {
    napi_disable(...);
    *(tm_base + 0x104) |= 7;             // re-mask
}
```

Mirror of `_open`.

## `register_pon_int` (line 7724) — PON top-level IRQ

```c
request_threaded_irq(g_pon_irq, zx_pon_int, 0, 0x80, "pon", DAT_0001b280);
```

Just registers `zx_pon_int` for GIC 66. We don't know yet what
`zx_pon_int` does — search `decomp_all_plat_zxylzb_9128S.c` for the
function body. **Stock /proc/interrupts shows pon=0 fires during ping**
so this IRQ is defensive — handler probably never runs but kernel still
needs the registration for some path.

## `chip_tm_init` (switch.ko line 2272) — switch fabric init

Large function (~500 lines). Sets `g_switch_debug_level`, calls
`zte_api_sw_global_init`, then per-port loop calling
`zte_api_sw_port_init` + `zte_api_sw_vlan_set_port_pvid` +
`zte_api_sw_vlan_set_port_vlancfg` for all 5 ports (LAN1-4 + WAN).
Plus VLAN tag setup (0x88a8, 0x8100, 0x9100, 0x9200).

Mainline replays the switch-fabric register state via `stock_table.h`
(huge data file with replayed init writes). Whether that's a complete
substitute for `chip_tm_init` is unverified — `stock_table.h` was
captured by kotrace-replay-grabbing what the kmod actually wrote at
boot, so it should be functionally equivalent IF the same boot path
was traced.

## Mainline gap matrix — definitive

| Step | Stock | Mainline | Severity |
|---|---|---|---|
| Map `pon_base` | ✅ | ✅ | — |
| Map `top_crm_base` | ✅ | ✅ | — |
| Map `sys_ctrl_base` (0x94100000) | ✅ | ❌ | 🔴 needed by SERDES bring-up |
| Map `pin_mux_base` (0x94200000) | ✅ | ❌ | 🟡 unknown if needed at runtime |
| Map `pon_serdes_base` (0x9fe00000) | ✅ | ❌ | 🔴 SERDES bring-up impossible without |
| `pon_reset(0xffffffff)` | ✅ | ❌ | 🟡 cold-boot safety (warm boot inherits from stock) |
| `msleep(10)` after reset | ✅ | ❌ | 🟢 cosmetic |
| `pon_base + 0x40018 = 2` | ✅ | residue | 🟢 happens to be set on warm boot |
| **`zx_pon_clk_reset_init(1)`** | ✅ ENTIRE FN | ❌ | 🔴🔴 SERDES + temp band cal + sys_ctrl writes — **the prime suspect for "TX doesn't reach wire"** on warm-boot-from-stock |
| `register_pon_int()` | ✅ | ❌ no PON IRQ | 🟡 defensive on stock (0 fires during ping) |
| `pon_base + 0x40044 = 0xffffff7f` | ✅ | residue | 🟢 |
| `pon_base + 0x4001c = 0xf` | ✅ | ❌ (live = 0) | 🟡 |
| `msleep(1)` | ✅ | ❌ | 🟢 |
| `TM[0x128] = 0x1fff` | ✅ | ✅ | — |
| `TM[0x130] = 0x1fffff` | ✅ | ✅ | — |
| `pon_tm_red_init` | ✅ | ✅ Phase 9d | — |
| `pon_tm_dma_init` 11 writes | ✅ | ⚠️ verify each | 🟡 audit needed |
| `pon_tm_bmu_init` | ✅ | ✅ `zx_tm_bmu_init` | — |
| `TM[0xf0] = ZX_DESC_BASE` | ✅ phys carved | ✅ `rxdesc_dma` (kernel DMA pool) | — |
| `pon_tm_bmu_enable` | ✅ | ✅ | — |
| **`TM[0xc008] = 0`** | ✅ | ❌ | 🟡 single missing write — easy to add |
| `pon_tm_net_init` w/ "pon" netdev | ✅ "sw"+"pon" | ⚠️ "sw" only | 🟡 IRQ gate bypassed in mainline init — works for that path but missing the "pon" IRQ-info binding |
| `pon_tm_int_init` | ✅ | ✅ | — |
| `netdebug_module_init` | ✅ | ❌ noop | 🟢 mostly diag |
| `pon_pp_brg_init` 14 writes | ✅ | ✅ stock_table | — |
| `pon_pp_cla_init` | ✅ | ✅ replay | — |
| `request_threaded_irq pp_irq` | ✅ | ❌ | 🟡 stock fires 0 IRQs, defensive |
| `pon_npp_idm_init` (idm netdev) | ✅ | ❌ no idm netdev | 🟡 separate mgmt path |
| `pon_npp_spa/sipc/smct/uopc_init` | ✅ | ✅ replay | — |
| `request_threaded_irq npp_irq` | ✅ | ❌ | 🟡 stock fires 0 |
| `if lan_up: PP[0x2c] |= BIT(29)` | ✅ | ⚠️ BIT(25) wrong + HW-locked anyway | 🟢 stock readback also shows BIT(29)=0 — HW-locked on both |
| `zx_pon_clk_reset()` (`TOPCRM[0xc] |= 0x1e0`) | ✅ | ❌ | 🟡 last clock enable — may be needed |
| `pon_tm_timer` (periodic TX reclaim) | ✅ | ✅ commit `80f610eda` | — |

## Priority recommendations

### 🔴 Critical — implement first (must succeed before next test)

1. **Map `sys_ctrl_base` + `pon_serdes_base` in DT + driver.** Add to
   our DT's `pon@92000000` node reg array (positions 2 and 4 — pin_mux
   at 3 may also be needed). Then `devm_platform_ioremap_resource` or
   `of_iomap` for each in driver probe.

2. **Implement `zx_pon_clk_reset_init` equivalent.** This is the
   SERDES bring-up the findings doc identified months ago. Concrete
   action items:
   - Add the TOPCRM[8] bit-cycle: `&=~0x30; udelay; |=0x20; udelay; |=0x10`
   - Wait for `pon_serdes_base[0x68] & 0x10` (rxpll lock)
   - Wait for `pon_serdes_base[0x70] & 0x1000000` (PLL band ready)
   - Read temperature via a kernel thermal API (or hardcode for bench)
   - Apply band calc + write `pon_serdes_base[0x44]` (band) + `[0x40] |= 0x4000000` (enable)
   - Clear `sys_ctrl_base[0x10] & ~0x800`
   - Final `TOPCRM[0xc] |= 0x1e0`

### 🟡 Likely needed — implement after critical works

3. **Add `pon_reset(0xffffffff)` + msleep(10)** at probe start.
4. **Add missing single writes**:
   - `pon_base + 0x4001c = 0xf`
   - `TM[0xc008] = 0`
   - Final `TOPCRM[0xc] |= 0x1e0` (== `zx_pon_clk_reset()`)
5. **Audit `pon_tm_dma_init` 11 writes** vs `zx_eth_init_chip_tm` for
   missing values (especially `TM[0x10388] = 0x131217`).

### 🟢 Defensive — last

6. Register `pon`, `pp`, `npp` IRQs (even with empty handlers).
7. Implement "pon" netdev (separate from "sw").

## Estimate

- 🔴 critical (1+2): **4-6h of focused work** (DT edits, ioremap, helper port, SERDES bring-up, bench iterate)
- 🟡 likely (3-5): **1-2h**
- 🟢 defensive (6-7): **2-3h**

Total to address structurally: **~10h of focused work**. Higher confidence
that this resolves the bug than any further bit-twiddling at the TM
descriptor level, because the missing SERDES + sys_ctrl + pin_mux maps
are HW-fundamental — they affect every byte at the wire.

## What this doc rules out

After this RE pass:
- `desc[2..3]` port hint **isn't** the bug (already empirically refuted)
- `PP[0x2c] BIT(29)` **isn't** the bug (stock readback shows it 0 too)
- `lan_up_port` value interpretation **isn't** ambiguous (raw decomp confirms port index, value 4 = WAN)
- Latch clearing in PHY IRQ handler **isn't** the bug (stock identical handler, 0 storm)
- `pon_tm_timer` periodic TX reclaim **isn't** sufficient alone (we have it, ping still broken)

## What still has uncertainty

- Whether **all three missing ioremaps** are accessed at runtime or
  only at init (only init = one-time cost, simpler port)
- The body of `serdes_mode_set`, `reg_def_set`, `ref_clk_set` (called
  from `zx_pon_clk_reset_init`) — they may have additional writes we
  haven't dumped yet
- The body of `pon_tm_dma_init` writes — we cited offsets but didn't
  confirm mainline replays each (audit pending)
- Whether kotrace shim can wake/read the TM block when /dev/mem returns
  0 (the open question from this session)
