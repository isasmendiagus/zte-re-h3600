# Stock init flow — static analysis depth-first walk

**Working doc, in progress.** Walking from `plat-zxylzb_9128S init_module`
entry point through every function call, depth-first, documenting each.

For each function: file:line where defined, brief comment of what it does,
HW writes (addr + value), and list of sub-calls.

Source: `tasks/00.10.02.re-stock-kmods/findings/decomp_all_*.c` (raw Ghidra
decomp of 5 kmods).

Cross-reference convention: `[fn-NN]` link tags so we can grep.

---

## Legend

- **HW writes**: register address + value the function pokes
- **Sub-calls**: nested function invocations (descended in same doc)
- **In mainline?**: ✓ replicated / ⚠ partial / ✗ missing / N/A
- **Severity if missing**: 🔴 likely path-breaking · 🟡 unclear · 🟢 informational

---

## [fn-00] `init_module` @ plat:8891 — chip bring-up entry point

What it does: top-level orchestrator. Resolves DT nodes, maps the 5 IO
regions, kicks off the SERDES bring-up, registers PON IRQ, then calls
the TM / PP / NPP per-block init helpers in order.

HW writes (direct):
- `pon_base + 0x40018 = 2` — purpose unknown
- `pon_base + 0x40044 = 0xffffff7f` — likely IRQ mask (post-`register_pon_int`)
- `pon_base + 0x4001c = 0xf` — purpose unknown
- `pp_base + 0x2c |= 1 << (lan_up_port + 0x19)` — CPU forward enable (HW-locked anyway)

Sub-calls in order:
1. `printk("pon init")`
2. `reserve_mem_info()` — [fn-01]
3. `zte_get_pon_mode()` → 0x10 (LAN-only)
4. `printk("lan_up=1, lan_up_port=4")`
5. `of_find_matching_node_and_match("zte,zx279128s-pon")`
6. `of_iomap(node, 0..4)` → 5 mappings (pon_base, top_crm, sys_ctrl, pin_mux, pon_serdes)
7. `irq_of_parse_and_map(node, 0)` → `g_pon_irq`
8. `irq_of_parse_and_map(gephy_node, 0..3)` → `g_phy_irq[0..3]`
9. `pon_reset(0xffffffff)` — [fn-02]
10. `msleep(10)`
11. `zx_pon_clk_reset_init(1)` — [fn-03]
12. `register_pon_int()` — [fn-04]
13. `msleep(1)`
14. `tm_pon_tm_init()` — [fn-05]
15. `netdebug_module_init()` — [fn-06]
16. `tm_pon_pp_init()` — [fn-07]
17. `tm_pon_npp_init()` — [fn-08]
18. `if (lan_up): pp_base+0x2c |= BIT(lan_up_port+0x19); zx_pon_clk_reset()` — [fn-09]

In mainline? **⚠ partial** — mainline lacks pon_reset, zx_pon_clk_reset_init,
register_pon_int, netdebug, the lan_up final clock-enable, and the 5 ioremap
mappings collapses to 2.

---

## [fn-01] `reserve_mem_info` @ plat:7772 — purely informational

What it does: just `printk`s the memory layout (BP pool base, descriptor
bases, ACL base, etc.) — no register writes. Helps the operator see where
TM allocs its buffers in physical RAM.

HW writes: **none**.

Sub-calls: only `printk` (47 of them).

In mainline? **N/A** (informational).

---

## [fn-02] `pon_reset(uint mask)` @ plat:7744 — pulse pon[8] bits

What it does: clear specified bits in `pon_base[8]`, delay ~100us, set them
back. Net result is a transient HW reset pulse for the bits in `mask`.
Called as `pon_reset(0xffffffff)` from init_module → resets every bit
briefly.

HW writes:
- `pon_base + 8 &= ~mask` (clear)
- delay 100x via `__delay` (Ghidra mis-resolves as `_request_threaded_irq`)
- `pon_base + 8 |= mask` (re-set)

Sub-calls:
- `__delay` (100x)

In mainline? **✗ missing**. Severity 🟡 — final state inherits via warm boot
from stock, but cold-boot mainline observes HW default until first execution.
Pulse transition may also trigger HW state-machine resets.

---

## [fn-03] `zx_pon_clk_reset_init(int mode)` @ plat:8266 — SERDES bring-up

What it does: full SERDES bring-up sequence — cycles TOPCRM clock, waits
for rxpll lock + PLL band-ready, reads CPU temperature, computes
temperature-compensated band value, writes it to `pon_serdes_base[0x44]`,
clears `sys_ctrl[0x10]` bit 11, enables `TOPCRM[0xc]` clock bits.

HW writes:
- `TOPCRM[0x08] &= ~0x20`
- `TOPCRM[0x08] &= ~0x10`
- delay 10x
- `TOPCRM[0x08] |= 0x20`
- delay 10x
- `TOPCRM[0x08] |= 0x10`
- spin until `pon_serdes_base[0x68] & 0x10` (rxpll ready)
- retry-loop until `pon_serdes_base[0x70] & 0x1000000` (PLL band)
- `pon_serdes_base[0x44] = (val & 0xffc0ffff) | (coarse << 16)` — band write
- `pon_serdes_base[0x40] |= 0x04000000` — band enable
- `sys_ctrl_base[0x10] &= ~0x800` — clear bit 11
- `TOPCRM[0x0c] |= 0x1e0` — enable bits 5..8

Sub-calls:
- `ref_clk_set()` — [fn-10]
- `reg_def_set()` — [fn-11]
- `serdes_mode_set(mode, 0, 0)` — [fn-12]
- `temp_ctrl_read()` — [fn-13]
- printks ("rxpll_ready", "serdes band cpu_temper:X coarse:0xY", "band calc fin")
- spin loops + retry counter

In mainline? **✗ MISSING entire function**. Severity 🔴 — depends on whether
warm-boot inherits the band value. Cold-boot to mainline → SERDES never gets
band cal → may operate at HW default band → marginal link.

---

## [fn-04] `register_pon_int` @ plat:7724 — register PON top-level IRQ

What it does: registers `zx_pon_int` as handler for the `pon` IRQ
(g_pon_irq = GIC 66). Returns 0 on success.

HW writes: **none** (kernel-side IRQ registration only).

Sub-calls:
- `request_threaded_irq(g_pon_irq, zx_pon_int, 0, 0x80, "pon", DAT_...)`

In mainline? **✗ missing**. Severity 🟢 — stock /proc/interrupts shows
gphy_pon (GIC 66) fires **0 times** during ping → defensive registration,
not on hot path.

---

## [fn-05] `tm_pon_tm_init` @ plat:7062 — TM block bring-up

What it does: TM-block bring-up. Sets the wide-IRQ masks, then chains:
RED-init → DMA-init → BMU-init → set RX desc base → BMU-enable → clear
0xc008 → net (netdev) init → IRQ init.

HW writes:
- `tm_base + 0x128 = 0x1fff`
- `tm_base + 0x130 = 0x1fffff`
- delay 10x
- `tm_base + 0xf0 = ZX_DESC_BASE` (carved RAM phys addr)
- `tm_base + 0xc008 = 0`

Sub-calls:
- `pon_tm_red_init()` — [fn-14]
- `pon_tm_dma_init()` — [fn-15]
- `pon_tm_bmu_init()` — [fn-16]
- `pon_tm_bmu_enable()` — [fn-17]
- `pon_tm_net_init()` — [fn-18]
- `pon_tm_int_init()` — [fn-19]

In mainline? **⚠ partial** — most pieces replicated via `zx_eth_init_chip_tm`,
but `TM[0xc008]=0` missing. The 0x128/0x130 writes are replicated. Severity 🟡.

---

## [fn-06] `netdebug_module_init` @ plat:8871 — register /dev/netdebug_dev

What it does: registers char device (major 99) `netdebug_dev` for some
diagnostic ioctl interface. Pure user-space-facing diag, no HW touch.

HW writes: **none**.

Sub-calls:
- `__register_chrdev(99, 0, 0x100, "netdebug_dev", &netdebug_module_fops)`

In mainline? **N/A** (diag). Severity 🟢.

---

## [fn-07] `tm_pon_pp_init` @ plat:5527 — PP block bring-up

What it does: orchestrates PP (Packet Processor) bring-up: control init →
bridge init → classifier init → register PP IRQ.

HW writes (direct): **none** (delegates).

Sub-calls in order:
- `printk("pon_pp init")`
- `pon_pp_ctrl_init()` — [fn-20]
- `pon_pp_brg_init()` — [fn-21]
- `pon_pp_cla_init()` — [fn-22]
- `request_threaded_irq(g_pp_irq, zx_pon_pp_int, 0, 0, "pon_pp", 0)`

In mainline? **⚠ partial** — PP_BRG + CLA writes replayed via stock_table.h,
but ctrl_init may be missing. PP IRQ NOT registered. Severity 🟡 — PP IRQ
fires 0 on stock (defensive), PP_BRG state is critical for switch fwd.

---

## [fn-08] `tm_pon_npp_init` @ plat:2238 — NPP block bring-up

What it does: orchestrates NPP (Network Packet Processor) bring-up. Direct
writes for NPP global config, then dispatches to per-subsystem inits, then
registers NPP IRQ.

HW writes (direct):
- `npp_base + 0x08 = 0xffffff`
- `npp_base + 0x0c = 0xfffff`
- `msleep(1)`
- `npp_base + 0x04 = 0xffffffff`
- `npp_base + 0x48 = 0`
- `npp_base + 0x40 |= 0x300`
- `npp_base + 0x10008 = 0x80`

Sub-calls (in order):
- `printk("pon_npp init")`
- `pon_npp_idm_init()` — [fn-23]
- `pon_npp_spa_init()` — [fn-24]
- `pon_npp_sipc_init()` — [fn-25]
- `pon_npp_smct_init()` — [fn-26]
- `pon_npp_smac_init()` — [fn-27]
- `request_threaded_irq(g_npp_irq, pon_npp_int, 0, 0, "pon_npp", 0)`
- `pon_npp_uopc_init()` — [fn-28]

In mainline? **⚠ partial** — SMAC inits via stock_table, IDM netdev missing
entirely, NPP IRQ not registered. The 7 direct writes may not all be
present.

---

## [fn-09] `zx_pon_clk_reset` @ plat:8339 — final clock enable

What it does: single-write helper that sets bits 5..8 of `TOPCRM[0x0c]`.
Called at end of `init_module` if `lan_up != 0`.

HW writes:
- `TOPCRM[0x0c] |= 0x1e0`

Sub-calls: **none**.

In mainline? **✗ missing**. Severity 🟢 — stock readout shows the bits ARE
set (`0x005179e0`), but that's from stock's prior boot. Cold-boot mainline
inherits whatever U-Boot left. May or may not matter.

---

---

## [fn-10] `ref_clk_set(uint mode)` @ plat:8206 — reference clock + PLL setup

What it does: configures the reference-clock PLL @ `top_crm_base + 0x50`.
Two paths depending on mode: integer-divider PLL (mode=1) vs fractional PLL
(otherwise — used by U-Boot mode=0).

HW writes:
- `TOPCRM[0x50] &= 0x7fffffff` (clear MSB before reconfig)
- `pll_cfg_integer(TOPCRM+0x50, 1, 0x32, 4, 2)` if mode==1 — [fn-30]
- `pll_cfg_fractional(TOPCRM+0x50, 1, 0x5d, 0x4fdf3b, 5, 3)` otherwise — [fn-31]
- delay 50x

Sub-calls:
- `pll_cfg_integer` — [fn-30] (integer divider config for kernel mode)
- `pll_cfg_fractional` — [fn-31] (fractional divider for U-Boot mode)
- `__delay`

In mainline? **✗ missing**. Severity 🔴 — without proper ref-clk PLL setup
the SERDES PLL won't lock cleanly. **U-Boot already calls this with mode=0**
before mainline runs, so PLL is at U-Boot's settings; stock kernel
overrides with mode=1 integer settings. Mainline never overrides → SERDES
PLL is at fractional U-Boot config, not kernel's.

---

## [fn-11] `reg_def_set` @ plat:8231 — SERDES register defaults

What it does: pokes 24 default values into `pon_serdes_base[0..0x17]`. This
is the "factory" SERDES register set baseline.

HW writes (all to `pon_serdes_base[N]`):
```
[0]    = 0x800180a7     [c]    = 0xa02e2400
[1]    = 0x8f           [d]    = 0xc0593d44
[2]    = 0x540          [e]    = 0xf0f
[3]    = 4              [f]    = 0
[4]    = 0              [10]   = 0x3c0000
[5]    = 0x18a6400      [11]   = 0xea00a013   ← THIS is what gets band-cal'd to 0xea2ca013 later
[6]    = 0xb50140       [12]   = 0x101038ca
[7]    = 0x1216000      [13]   = 0x5a008
[8]    = 0x40000000     [14]   = 0x33333333
[9]    = 0xb510007      [15]   = 0x33333333
[a]    = 0              [16]   = 0x3e23333
[b]    = 0              [17]   = 0x40244
```

⚡ **Big insight**: `pon_serdes_base[0x11] = 0xea00a013` here is the
*pre-band-cal* value. The kernel's `zx_pon_clk_reset_init` then OR-in
the coarse band: `(0xea00a013 & 0xffc0ffff) | (0x2c << 16) = 0xea2ca013`.
Our live stock readout matches **exactly** (`0xea2ca013`). Confirms this
function ran on stock at boot.

Note address arithmetic: in C-decomp `pon_serdes_base[N]` is `[N*4]` bytes,
so `pon_serdes_base[0x11]` is at byte offset 0x44 — exactly the band reg.

Sub-calls: **none**.

In mainline? **✗ missing**. Severity 🔴🔴 — these are the SERDES
"factory defaults". Without them, the SERDES is at HW power-on defaults
(may be different). **This + band cal are the two halves of what's
missing**.

---

## [fn-12] `serdes_mode_set(int mode)` @ plat:7924 — SERDES mode select

What it does: configures SERDES for mode=1 (standard GE) or mode=3 (other).
For mode=1: pokes 7 fields across `pon_serdes_base[0,2,5,8,9]`. Called with
arg=1 from `zx_pon_clk_reset_init`.

HW writes (for mode=1):
- `pon_serdes_base[0]  = (val & 0xffffff00) | 0xa5`        (byte 0 lowest byte = 0xa5)
- `pon_serdes_base[2]  = (val & 0xffffff00) | 0x20`
- `pon_serdes_base[5]  = (val & 0xffff00ff) | 0x5800`
- `pon_serdes_base[8]  = val & 0xffffff`                   (clear bits 24-31)
- `pon_serdes_base[9]  = (val & 0xffffff00) | 0x03`
- `pon_serdes_base[9]  = (val & 0xff00ffff) | 0x570000`
- `pon_serdes_base[9]  = (val & 0xffffff)   | 0x07000000`

For mode=3 (not used by kernel init): different pattern with `[3]=5`,
`[9]=0x83`, etc.

Sub-calls: **none**.

In mainline? **✗ missing**. Severity 🔴 — these are the actual SERDES
mode bits. Without them, SERDES might be in a different mode than GE.

Note: live stock readout matches the mode=1 pattern partially. E.g.:
- `[0]=0x800180a5` — bits 0-7 = 0xa5 ✓
- `[5]=0x18a6400` after reg_def_set, then OR in 0x5800 → 0x18a6400 stays
  because mask 0xffff00ff keeps middle byte = 0x64, and 0x5800 is bits
  15:11 — wait that overlaps. Let me re-check: 0x18a6400 in binary —
  middle byte index 0xff00 = bits 15:8. Live shows `[5]=0x018a6400`
  but the modify is `& 0xffff00ff | 0x5800` → keeps bits 31:16 and 7:0,
  sets bits 15:8 = 0x58. Result expected: `(0x018a6400 & 0xffff00ff) |
  0x5800 = 0x01805800` — but we saw `0x01a05800` actually no, the live
  earlier dump showed `9fe00014 018a5800`. So bits 15:8 = 0x58 ✓ confirms
  serdes_mode_set ran on stock.

---

## [fn-13] `temp_ctrl_read` @ plat:9879 — Ghidra-undecompilable

Decompiles as `halt_baddata()` — Ghidra hit bad instruction. Likely an
imported kernel symbol resolved via `kallsyms_lookup_name` at module load
time, similar to other entries near it (zx_mdio_read,
irq_of_parse_and_map). The real function is probably a thermal-zone read
from `/soc/temp@94100034`.

HW reads: thermal sensor at `0x94100034` (we saw it in `/proc/iomem`).

Sub-calls: external (kernel thermal API).

In mainline? **✗ missing**. Severity 🟡 — we can hardcode temp to a
nominal value (e.g., 30°C) for first impl. Real port would use
`thermal_zone_get_temp()` API.

---

## [fn-14] `pon_tm_red_init` @ plat:7237 — RED queue policy init

What it does: configures the RED (Random Early Drop) policy for ~640 TM
queues across 3 RAM banks. Sets thresholds + decision params per-queue
via `red_set_queue_cfg(queue_id, params, ram_id)` helper.

HW writes (indirectly via red_set_queue_cfg, which writes TM[0x4014..0x4028]):
- Ram 0: queues 0..0xf, params = `[0x400, 0, 0, 0]`
- Ram 0: queues 0x10..0x190, params = `[0x800400, 0, 0, 0]`
- Ram 2: queues 0..0x180, params = `[0x200020, 0, 0, 0]`
- Ram 4: queues 0..0x180, params = `[0xff803fff, 0x100ff80, 0x100200, 0x20]`

Sub-calls:
- `red_set_queue_cfg(qid, params, ram_id)` × ~640 — see [fn-32]

In mainline? **✓** — we have it via Phase 9d. Should verify the param
arrays match exactly.

---

## [fn-15] `pon_tm_dma_init` @ plat:6279 — TM DMA setup

What it does: configures TM DMA ring control regs + sets the UP/DN ring
base physical addresses (in carved RAM region).

HW writes (11 total):
- `TM[0x10000] |= 0x2f0000`     (DMA ctrl OR-in bits)
- `TM[0x10028] = 1`
- `TM[0x1002c] = 1`
- `TM[0x10030] = 50000`         (timeout?)
- `TM[0x10034] = 0x40`
- `TM[0x10004] = 0x7f`          (`tm_set_onu_mac + tm_base + 4` decomp expression)
- `TM[0x10020] = 0x20`
- `TM[0x10024] = 0x20`
- `TM[0x10050] = ZX_TX_UP_DESC_BASE`   (carved phys: pdt_mem + 0x405e0000 + ...)
- `TM[0x10060] = ZX_TX_DN_DESC_BASE`   (carved phys: pdt_mem + 0x405f0000 + ...)
- `TM[0x10388] = 0x131217`
- `TM[0x1003c] = 0x400040`

Sub-calls: **none**.

In mainline? **⚠ partial** — `zx_eth_init_chip_tm` writes UP+DN bases,
DMA ctrl. Need audit of which of the 11 are present. Suspect missing:
- `0x10000 |= 0x2f0000` (OR-in, may be overwritten by direct =)
- `0x10004 = 0x7f`
- `0x10030 = 50000`
- `0x10388 = 0x131217`
- `0x1003c = 0x400040`

Severity 🟡 — single missing writes individually small but cumulative may
affect DMA behavior.

---

## [fn-16] `pon_tm_bmu_init` @ plat:5694 — BMU buffer pool setup

What it does: initializes the BMU buffer-pool linked-list in carved RAM,
then programs TM[0x8000..0x8058] BMU control regs. BMU is the source of
all buffer pointers (BPs) used for RX/TX descriptors.

HW writes:
- Memory: writes `BPPE_POOL_SIZE` entries of (idx,next_idx) linked-list to
  `bppe_va_addr` (in carved RAM at `pdt_mem + ZX_RESERVE_MEM_SIZE*-0x100000`)
- Memory: same for jumbo at `jumbo_bppe_va_addr`
- `dma_cache_maint(bppe_va_addr, 0x20000, 1)` — flush cache
- `TM[0x8000] = 0`                              (disable BMU during config)
- `TM[0x8004] = 0x104c040`                      (BMU ctrl 1)
- `TM[0x8008] = 0x104c040`                      (BMU ctrl 2)
- `TM[0x8058] = (BPPE_POOL_SIZE >> 5) - 1`     (pool size)
- `TM[0x805c] = (JUMBO_BPPE_POOL_SIZE >> 5) - 1` (jumbo pool size)
- `TM[0xf4] = BP_BUFFER_BASE_PHYS`              (BP data base)
- `TM[0xf8] = JUMBO_BP_BUFFER_BASE_PHYS`        (jumbo BP base)
- `TM[0xe8] = BPPE_BASE_PHYS`                   (BPPE table base)
- `TM[0xec] = JUMBO_BPPE_BASE_PHYS`             (jumbo BPPE base)
- `TM[0xfc] = BP_SIZE | (JUMBO_BP_SIZE << 16)`  (size descriptors)
- `TM[0x8048] = BPPE_POOL_SIZE << 16`           (pool config)
- `TM[0x804c] = JUMBO_BPPE_POOL_SIZE << 16`     (jumbo pool config)

Sub-calls:
- `dma_cache_maint` (cache flush for BPPE region)

In mainline? **⚠ partial** — `zx_tm_bmu_init` in our driver replicates
most BMU regs, but uses `dma_alloc_coherent` instead of carved RAM. Need
verify: are the per-pool size masks correctly programmed? Are
`TM[0xe8], [0xec], [0xf4], [0xf8]` set?

Severity 🟡 — BMU is on the hot path for RX. Misconfig could cause
silent BP exhaustion.

---

## [fn-17] `pon_tm_bmu_enable` @ plat:5762 — enable BMU

What it does: single-write enable. After BMU is configured, this flips
the enable bit to start accepting alloc/free requests.

HW writes:
- `TM[0x8000] = 1`

Sub-calls: **none**.

In mainline? **✓** — mainline writes `BMU_INIT = 1` post-config.

---

## [fn-18] `pon_tm_net_init` @ plat:6950 — netdev creation + IRQ arming

What it does: creates the two CPU netdevs ("sw" and "pon"), binds NAPI
to "pon", initializes the TM queue tracking RAM, applies the initial
mask `|= 7`, and starts the periodic `pon_tm_timer` (1-jiffy reclaim
timer).

HW writes:
- `TM[0x104] |= 7` (mask bits 0,1,2 — initially masked, unmask via net_open)

Sub-calls:
- `pon_tm_net_register(1, "sw")` — register "sw" netdev
- `pon_tm_net_register(0, "pon")` — register "pon" netdev
- `set_pon_tm_int_info(pon_netdev + 0x4c0)` — bind IRQ info to pon
- `netif_napi_add(pon_netdev, ..., pon_tm_net_poll, weight=0x200)`
- `pon_tm_queue_init()` — [fn-29]
- `init_timer_key(pon_tm_timer, ...)` — timer init
- `add_timer(pon_tm_timer)` — start periodic timer (expires jiffies+1)

In mainline? **⚠ partial** — we create only "sw", missing "pon".
NAPI bound to "sw". `pon_tm_timer` equivalent added in commit `80f610eda`.
Severity 🟡 — IRQ unmask in mainline bypasses the "pon"-strcmp gate so
function still works for our purposes, but the "missing pon netdev"
could affect IRQ-info routing.

---

## [fn-19] `pon_tm_int_init` @ plat:6333 — TM IRQ registration

What it does: masks all TM IRQs initially (`TM[0x104] = 0xffffffff`), then
requests the GIC IRQ via `request_threaded_irq`.

HW writes:
- `TM[0x104] = 0xffffffff` (mask EVERYTHING initially)

Sub-calls:
- `request_threaded_irq(g_tm_irq, zx_pon_tm_int, flags=0, name="pon_tm", &pon_tm_int_info)`

In mainline? **⚠ partial** — mainline writes `TM[0x104] = 0xfffffffe`
directly (bit 0 unmasked from boot). Uses `devm_request_irq`. End state
similar.

Severity 🟢.

---

## [fn-29] `pon_tm_queue_init` @ plat:6916 — TM queue tracking RAM setup

What it does: allocates per-queue (8 queues) descriptor ring tracking
slots in carved RAM. Sets net_txq global state with the DN/UP ring phys
addresses. Prints the current TM[0x10058]/TM[0x10068] count regs at end
(diagnostic).

HW writes (memory, not registers):
- Initializes 8 queue-state entries at carved RAM, each with:
  - phys addr of 0x20000 region per queue (DN side)
  - phys addr 0x4000 step (UP side)
- Sets globals: `net_txq.dn_phys = ...+0x20000`, `net_txq.up_phys = ...+0x10000`

HW reads (diag printk):
- `TM[0x10068]` DMA DN CNT
- `TM[0x10058]` DMA UP CNT

Sub-calls: **none**.

In mainline? **✗ unclear** — we don't have an equivalent "queue ring
tracking" struct. We use a simpler tx_head/tx_done counter pair. The
stock multi-queue tracking with carved RAM regions doesn't map cleanly.
May or may not matter.

Severity 🟡.

---

## [fn-30] `pll_cfg_integer(uint *base, p2, p3, p4, p5)` @ plat:8094 — PLL integer-divider config

What it does: configures the PLL at `base` (passed as `top_crm_base + 0x50`)
for integer-divider mode. Sets feedback divide, post-divide, ref-divide,
disables fractional, then delays 100x and clears MSB.

HW writes (to `*base` and `base[1]`):
- `*base |= 0x80000000` (PLL reset bit set)
- `*base |= 0x08000000`
- `*base &= 0xfeffffff` (clear bit 24)
- `*base = (val & 0xff03ffff) | (p2 << 0x12)` — post-divide?
- `*base = (val & 0xfffc003f) | (p3 << 6)` — feedback divide (here p3=0x32)
- `*base = (val & 0xffffffc7) | (p4 << 3)` if p4 (here p4=4)
- `*base = (val & 0xfffffff8) | p5` if p5 (here p5=2)
- `base[1] &= 0xf7ffffff`
- `base[1] |= 0x04000000`
- `base[1] &= 0xfdffffff`
- `base[1] &= 0xfeffffff`
- `base[1] &= 0xff000000`
- delay 100x
- `*base &= 0x7fffffff` (clear MSB = release PLL reset)

Sub-calls:
- `__delay` (100x)

In mainline? **✗ missing**. Severity 🔴 — kernel's mode=1 PLL settings
won't be applied without this. Severity depends on whether U-Boot's
mode=0 fractional PLL is "close enough" for SERDES to lock at GE rate.

---

## [fn-31] `pll_cfg_fractional` @ plat:8132 — fractional PLL config

What it does: same idea as pll_cfg_integer but for fractional divider.
Used by U-Boot stage (`ref_clk_set(mode=0)`). Sets feedback divide,
post-divide + the fractional `param_4 = 0x4fdf3b`.

HW writes: same shape as fn-30, plus `base[1] = (val & 0xff000000) | param_4`
to set fractional component.

Sub-calls: `__delay`.

In mainline? **N/A** — U-Boot already calls this once before we run.

---

## [fn-20] `pon_pp_ctrl_init` @ plat:5543 — PP control init (TINY)

What it does: 2 writes + delay. Sets PP[0x28] and PP[0x00].

HW writes:
- `pp_base + 0x28 = 0x1070104`
- `pp_base + 0x00 = 2`
- delay 10x

Sub-calls: **none**.

In mainline? **⚠ partial** via stock_table.h. Order may differ. Severity 🟡.

---

## [fn-21] `pon_pp_brg_init` @ plat:5361 — PP bridge init

What it does: configures PP bridge — VLAN bitmaps, flood policy, MAC learn.
Per-port adds to VLANs 0/1. Isolates ports 6+7 (CPU + internal).

HW writes (13 direct):
- `pp_base + 0x8004 = 0x20206425` (decomp anomaly — string literal addr used as value)
- `pp_base + 0x8340 = 0xff5555ff`
- `pp_base + 0x8344 = 0x1e`
- `pp_base + 0x8380 = 0x1f`
- `pp_base + 0x863c = 0xaaaaaaaa`
- `pp_base + 0x81c0 = 0xff`
- `pp_base + 0x81c4 = 0x5555`
- `pp_base + 0x8188 = 0x13f434`
- `pp_base + 0x82c0 = 0xff`
- `pp_base + 0x8300 = 0xffff`
- `pp_base + 0x8304 = 0x1e`
- `pp_base + 0x8050 = 0xfffffffa`     ← FLOOD POLICY (flood to all except 0+2)
- `pp_base + 0x8008 = 0xff00`

Sub-calls:
- `pon_pp_add_port_to_vlan(0, port, 3)` × 8 ports
- `pon_pp_add_port_to_vlan(1, port, 3)` × 8 ports
- `pon_pp_port_isolate_part_1(6, 0xdf)` (port 6 isolated except bit 5)
- `pon_pp_port_isolate_part_1(7, 0xdf)` (port 7 isolated except bit 5)

In mainline? **⚠ partial** — stock_table.h should have the 13 writes. VLAN
adds + port isolate may be missing. Severity 🟡 — defines what switch forwards.

---

## [fn-22] `pon_pp_cla_init` @ plat:5502 — CLA classifier init (TINY)

What it does: 2 writes. CLA control regs.

HW writes:
- `pp_base + 0xc080 = 0x1000`
- `pp_base + 0xc084 = 2`

Sub-calls: **none**.

In mainline? **⚠ partial** — verify in `zx_cla_apply_replay` or stock_table.
Severity 🟡.

---

## [fn-23] `pon_npp_idm_init` @ plat:4342 — IDM netdev + DMA rings

What it does: registers 2 IDM netdevs (`idm0`, `idm1`), allocates DMA desc
rings, pre-allocates 0x200 sk_buffs for RX, programs IDM IRQ mask + thresh,
starts IDM timer.

HW writes:
- `npp_base + 0x8024 = 0x1f`              (IDM IRQ mask)
- `npp_base + 0x8018 = 0x40`              (threshold)
- `npp_base + 0x801c = 5000`              (timeout)
- `npp_base + 0x8010 = 0x40`              (control)
- `npp_base + 0x8000 |= 0xf0000`          (enable bits)
- `npp_base + 0x8000 = (val & 0xf00fffff) | 0x2000000`
- `pp_base + 0x38 = 0x0640` (byte writes)
- `npp_base + 0x80c0 = 0`
- `npp_base + 0x8008 = idm_desc_addr`     (DMA TX base)
- `npp_base + 0x8004 = idm_desc_addr + 0x4000`  (DMA RX base)
- `npp_base + 0x8048 = 0x10000`           (per-desc kick)
- `npp_base + 0x800c = 0x4000800`         (DMA threshold)

Sub-calls:
- `idm_net_register(1, "idm1")`
- `idm_net_register(0, "idm0")`
- `netif_napi_add(idm_netdev, ..., idm_net_poll, weight=0xff)`
- `idm_creat_status_proc()`
- `arm_dma_ops(...)` — alloc 0x2e6bc bytes DMA-coherent
- `__alloc_skbuff(0x6c4, ...)` × 0x200
- `hwnat_set_hook_ptr()`
- `init_timer_key(idm_timer)` + `add_timer(...)`

In mainline? **✗ missing** — no IDM netdev. Severity 🟡 — IDM is for
in-band mgmt, not LAN forwarding hot path.

---

## [fn-24] `pon_npp_spa_init` @ plat:3347 — Service Port Agg init (TINY)

What it does: single write.

HW writes:
- `npp_base + 0x141c0 = 0`

Sub-calls: **none**.

In mainline? **⚠** — verify in stock_table. Severity 🟢.

---

## [fn-25] `pon_npp_sipc_init` @ plat:2262 — SIPC init (TINY)

What it does: single write.

HW writes:
- `npp_base + 0xc000 = 0x11`

Sub-calls: **none**.

In mainline? **⚠** — verify in stock_table. Severity 🟢.

---

## [fn-26] `pon_npp_smct_init` @ plat:3335 — SMCT init (TINY)

What it does: 3 writes.

HW writes:
- `npp_base + 0x10000 = 0xb`
- `npp_base + 0x10004 = 0xb`
- `npp_base + 0x10010 = 0x3810`

Sub-calls: **none**.

In mainline? **⚠** — verify. Severity 🟢.

---

## [fn-27] `pon_npp_smac_init` @ plat:3273 — 4 GePHY init

What it does: loops 4 GePHYs, programs each MDIO (LDO+page select), calls
`smac_init(port)`, sets NPP per-port enable. Then `phy_process(0)`,
schedules `gephy_ldo_timer`, registers 4 PHY IRQs via `register_phy_int`,
configures external WAN PHY via `zx5201_config`, sets up `extphy_timer`.

HW writes per PHY i=0..3:
- `mdio_write(uni_phy[i], 0x10, 0x8001)` → `mdio_write(0x11, 0)`
- `npp_base + i*0x40000 + 0x40000 |= 2`   (per-port NPP enable)

Sub-calls:
- `gephy_ldo_init()` — [fn-34]
- `smac_init(i)` × 4 — [fn-33]
- `phy_process(0)` — [fn-35]
- `init_timer_key(gephy_ldo_timer)` + `add_timer(...)`
- `register_phy_int()` — [fn-36]
- `zx5201_config()` — [fn-37]
- `init_timer_key(extphy_timer)` + `add_timer(...)`
- `mdio_read/write(uni_phy[lan_up_port], 0)` — external PHY power-up

In mainline? **⚠ partial** — phy-zte-gephy does LDO+TX-DAC via phylib
config_init. NPP per-port enable bit may be missing. PHY IRQs via phylib
(different mechanism, has storm bug). Severity 🟡.

---

## [fn-28] `pon_npp_uopc_init` @ plat:3357 — UOPC init (TINY)

What it does: OR-in bit 3 of NPP[0x18000].

HW writes:
- `npp_base + 0x18000 |= 8`

Sub-calls: **none**.

In mainline? **⚠** — verify. Severity 🟢.

---

## Level-3 helpers (called from [fn-27] pon_npp_smac_init)

### [fn-33] `smac_init(int port)` @ plat:2272 — per-port SMAC bring-up

What it does: initializes per-port SMAC registers. Sets MAC.ctrl to
`0xBAE003` (the post-link-down state, bit 19 sticky set for init).

HW writes (per port, base = npp_base + port*0x40000 + 0x40000):
- `base + 0x000 = 0xbae003`     (MAC.ctrl init — bit 19 set, RX/TX off)
- `base + 0x004 = 0xffff`       (MAC.mask)
- `base + 0x008 = 0x80000001`   (MAC.en)
- `base + 0x0e0 = PTR_caseD_47_...` (decomp anomaly — likely a fnptr/data ptr)
- `base + 0xd00 &= ~0x2`        (clear bit 1)
- `base + 0xd30 &= ~0x20`       (clear bit 5)

In mainline? **⚠** — our Phase 52 adjust_link callback writes
`MAC.ctrl = 0xBA6003` (link UP) but doesn't write the other regs.
Severity 🟡.

### [fn-34] `gephy_ldo_init` @ plat:2972 — LDO arm for 4 GePHYs

What it does: loops 4 GePHYs, writes LDO arm pattern (0x17=0x2448, ext
0xb640 → 0x1f or 0x1c based on board config flags).

HW writes per phy:
- `mdio_write(phy, 0x17, 0x2448)`
- `mdio_write(phy, 0x10, 0xb640)`
- `mdio_write(phy, 0x11, 0x1f)` (or `0x1c`)
- `g_geLdoFlag[phy] = 0/1`

In mainline? **✓** — phy-zte-gephy `config_init` does LDO arm. Hardcoded
0x1f (skip the 0x1c fallback). Severity 🟢.

### [fn-35] `phy_process(int)` @ plat:2916 — PHY status sweep from IRQ tasklet

What it does: walks 5 phys, checks `has_phy_int` flag, on set: reads
mdio 0x19, marks TX-DAC flag, calls `switch_phy_int_check_part_5(idx)`.

HW reads: `mdio_read(phy, 0x19)` per phy.
HW writes: GIC pending-clear per phy.

Sub-calls:
- `switch_phy_int_check_part_5(idx)` (documented in stock_init_deep_re)

In mainline? **N/A** — phylib state machine equivalent.

### [fn-36] `register_phy_int` @ plat:3074 — register 4 GePHY IRQs

What it does: loops 4 PHYs. For each: writes `0x18=5` (link-state IRQ
enable), gets irq_desc, registers `zx_phy_int` handler.

HW writes:
- `mdio_write(phy, 0x18, 0x0005)` × 4

Sub-calls:
- `request_threaded_irq(g_phy_irq[i], zx_phy_int, 0, 0, name, i)` × 4

In mainline? **⚠** — phylib `phy_request_interrupt()` equivalent. Has
storm bug on PHY[3] in mainline.

### [fn-37] `zx5201_config` @ plat:3224 — external WAN PHY (zx5201) init

What it does: configures the 5th external PHY (WAN-side, MDIO addrs 8-9
distinct from GePHY 10-13). Pokes ~12 mdio regs.

HW writes (selected):
- `mdio_write(8, 0x12, 0x8402)`
- `mdio_write(9, 0x16, 0xa0f)`
- `mdio_write(9, 0x1b, 0x800)`
- `mdio_write(8, 0x1d, 0x355)`
- `mdio_write(8, 0x10, 0xb62d)` + `mdio_write(8, 0x11, 6)`
- `mdio_write(9, 0x12, 4)`
- `mdio_write(9, 0x11, (val & 0xc1ff) | 0x2800)`
- ...more conditional on `product_vid == ' '`

In mainline? **✗ missing** — external WAN PHY not initialized. Severity 🟢
for LAN testing, 🔴 if WAN needed.

### [fn-32] `red_set_queue_cfg(queue, params, ram)` @ plat:7092 — RED helper

What it does: poll-wait until `TM[0x4018] & 1`, then write 4-word RED
config to TM[0x401c..0x4028] with selector in TM[0x4014].

HW writes:
- spin until `TM[0x4018] & 1`
- `TM[0x4014] = queue | (ram << 0x16)`
- `TM[0x4028] = params[3]`
- `TM[0x4024] = params[2]`
- `TM[0x4020] = params[1]`
- `TM[0x401c] = params[0]`

In mainline? **⚠** — RED via Phase 9d. Verify params per RAM.

---

## Walk status

- Top-level `init_module` mapped: **✓**
- Level-1 functions documented: **✓ all 10** ([fn-00..09])
- Level-2 functions: **✓ ~20** documented ([fn-10..29])
- Level-3 helpers: **✓ key ones** ([fn-30..37])
- Not yet documented (low priority leaves):
  - `serdes_set_*` / `pll_ssc_cfg` (PHY-related helpers, not on init path)
  - `cla_ram_set/get/dump` (called from CLA setup, but indirect via stock_table.h)
  - `sadm_ram_set/get` (PP_SADM is empty in init; helpers exist but unused)
  - `pon_pp_add_port_to_vlan` (helper called by pp_brg_init — 16 invocations)
  - `pon_pp_port_isolate_part_1` (called 2x by pp_brg_init)
  - `idm_net_register` + `idm_net_poll` (IDM netdev internals)
  - `pon_npp_idm_init` skb-prealloc internals

### [fn-38] `tm_proc_init` @ plat:341 — /proc/tm dir + shell entry

What it does: creates `/proc/tm` directory + `create_shell_proc()` for the
runtime debug shell. Used to be how stock developers poked the device.

HW writes: **none**.

Sub-calls:
- `proc_mkdir("tm", 0)` → stores `tm_proc_root`
- `create_shell_proc()` — creates `/proc/tm/shell` entry (read = usage, write = command)

In mainline? **N/A** — userspace debug interface only. Our equivalent is
the debugfs at `/sys/kernel/debug/zx_eth/`.

**Note**: NOT called from `init_module`. Likely called from `module_init`
helpers that run at module load time. The `init_module` we walked covers
the chip bring-up; `tm_proc_init` is a parallel registration step.

### [fn-39] `pon_tm_usch_init` @ plat:7504 — EMPTY STUB

```c
undefined4 pon_tm_usch_init(void) { return 0; }
```

Dead code — vestigial from PON era. Not called from `init_module`. Likely
named for "upstream scheduler init" but contains no logic.

In mainline? **N/A**.

## Findings summary

### Init phases in order (from init_module)

1. **Discovery**: zte_get_pon_mode, DT parse, of_iomap × 5, irq_of_parse_and_map × 5
2. **Reset**: pon_reset(0xffffffff) + msleep(10)
3. **Clock + SERDES**: pon_base+0x40018=2 → zx_pon_clk_reset_init(1)
4. **PON IRQ register**: register_pon_int
5. **More clock**: pon_base+0x40044=0xffffff7f + pon_base+0x4001c=0xf + msleep(1)
6. **TM bring-up**: tm_pon_tm_init (RED, DMA, BMU, net+queue, IRQ)
7. **diag char dev**: netdebug_module_init
8. **PP bring-up**: tm_pon_pp_init (ctrl, brg with 13 writes + VLAN, CLA, IRQ)
9. **NPP bring-up**: tm_pon_npp_init (7 direct + IDM, SPA, SIPC, SMCT, SMAC×4 with phys, IRQ, UOPC)
10. **Final clock**: if lan_up: pp[0x2c] |= BIT(lan_up_port+0x19) + zx_pon_clk_reset

### Total HW writes in stock init (rough count)

- Direct stack of init_module: ~6
- zx_pon_clk_reset_init: ~10 (TOPCRM, SERDES, sys_ctrl)
- reg_def_set: 24 (SERDES defaults)
- serdes_mode_set: 7 (SERDES mode bits)
- pll_cfg_integer/fractional: ~12 (PLL setup)
- pon_tm_tm_init writes: ~5
- pon_tm_dma_init: 11
- pon_tm_bmu_init: 13 (+ linked-list init in RAM)
- pon_tm_red_init: ~640 (via red_set_queue_cfg)
- pon_tm_net_init: 1 mask write
- pon_tm_int_init: 1
- pon_tm_queue_init: 0 reg writes (RAM only)
- pon_pp_ctrl_init: 2
- pon_pp_brg_init: 13 (+ VLAN adds + port isolate)
- pon_pp_cla_init: 2
- pon_npp_idm_init: 12 reg + heavy DMA setup
- pon_npp_spa/sipc/smct/uopc_init: 5 total tiny
- pon_npp_smac_init: 4 PHYs × ~2 reg + 4× smac_init (each 6 writes) = 32
- gephy_ldo_init: 4 PHYs × 4 mdio writes = 16
- register_phy_int: 4 mdio_write(0x18, 5)
- zx5201_config: ~12 external mdio
- zx_pon_clk_reset (final): 1 OR

**Estimate**: ~800+ register/mdio writes in full stock init.

Mainline replays a large portion via `stock_table.h` / `zx_cla_table.h` /
`zx_fpga_reg_tables.h` (these dump-tables were generated by kotrace-replay).
But the **dynamic/helper-based parts** (SERDES band cal, PHY IRQ ack
pattern, IDM netdev creation, multi-port netdev model) are not replayable
via tables — they need to be coded explicitly in mainline.

---

# PART 2 — Runtime functions + helpers

Documents the **non-init** functions that run during normal operation:
TX path, RX path, IRQ handlers, BMU alloc/free, switch-fabric runtime
helpers, and periodic timers. These are the functions that move data
once init is complete.

---

## TX path

### [fn-40] `pon_tm_net_tx(skb, netdev)` @ plat:6721 — netdev xmit entry

What it does: kernel calls this for each outgoing skb on a TM netdev
("sw" or "pon"). Acquires spinlock, calls `ffe_learn_skb` for first-pass
FFE flow learning. Calls `pon_tm_get_next_txdesc(dir)` to grab the next
TX desc slot in the ring. Fills the 16-byte desc:
- `*puVar3 = 0x80` (first dword)
- byte 0 → `0xc9` (CPU/source marker, OVERRIDES dword's byte 0)
- `puVar3[3] = 0` (last dword)
- `puVar3[1] = 0x10000` (desc[4..7] — second dword)
- `puVar3[2] = 0x1000000` (desc[8..11] — third dword)
Then calls `dev_qos_get_queue` to pick a TM queue (writes desc[3] bits),
ethertype-checks (0x884c=OAM / 0x8899=ZTE vendor go a special path),
fetches dst netdev info, applies QoS via `dev_qos_select_queue`, then
calls `pon_tm_data_raw_send(skb, desc, dir)`.

HW writes: none direct (delegated to pon_tm_data_raw_send + soft_insert).

Sub-calls:
- `ffe_learn_skb(skb, 3)` — [fn-49]
- `pon_tm_get_next_txdesc(dir)` — [fn-41]
- `dev_qos_get_queue(...)`, `dev_qos_select_queue(...)` — QoS hooks
- `pon_tm_data_raw_send(skb, desc, dir)` — [fn-42]

In mainline? **⚠ partial** — our `zx_sw_xmit` does desc fill + BP alloc
+ kick directly (no ffe_learn, no QoS hook, no ethertype filter). Stock
desc format documented in `tx_path_stock_decomp.md`.

### [fn-41] `pon_tm_get_next_txdesc(uint dir)` @ plat:6689 — ring slot allocation

What it does: returns pointer to next free TX desc in the UP (dir=0) or
DN (dir=1) ring, advancing the write index. If ring is over half-full
(>0x200 pending), calls `pon_tm_check_tx_done_nolock` to consume completions.
Returns 0 if ring full (>0x400 pending).

HW reads:
- `tm_base + 0x10058` (UP CNT) or `tm_base + 0x10068` (DN CNT) via [fn-43]

In mainline? **⚠** — we use simpler `tx_head` counter, no "check full"
gate. Severity 🟡 — could drop frames silently if ring fills.

### [fn-42] `pon_tm_data_raw_send(skb, desc, dir)` @ plat:6600 — fill BP + desc

What it does: allocates a BP via `pon_tm_bmu_alloc_bp`, computes BP buffer
addr (`pdt_mem + 0x40520010 + bp*BP_SIZE`), memcpy(s skb data to BP buf,
then fills desc bytes:
- `desc[11] = (desc[11] & 1) | 0x20` (VALID|0x20 — bit 5 = format/CPU marker)
- For small (<64B) packets: zeropad to 64, set desc[12..13] = 0x100,
  desc[8..11] |= 0x40 << 9
- For normal: set len in desc[12..13] (`(desc[12..13] & 3) | (len << 2)`)
  and desc[8..11] (`(desc[8..11] & 0xff8001ff) | (len << 9)`)
- `desc[7] = (desc[7] & 1) | ((bp & 0x7f) << 1)` (low 7 bits of bp_idx)
- `desc[8] = bp >> 7` (high bit of bp_idx)
- `dma_cache_maint(BP_buf, len)`
- Call `soft_insert_tx_1desc(desc, dir)` — actually kick the HW

HW writes: indirect via soft_insert.

Sub-calls:
- `pon_tm_bmu_alloc_bp()` — [fn-44]
- `memcpy(BP_buf, skb->data, len)`
- `__memzero(BP_buf + len, pad)` if undersize
- `dma_cache_maint(BP_buf, len)` — DMA flush
- `soft_insert_tx_1desc(desc, dir)` — [fn-43]

In mainline? **⚠ partial** — we have the desc format (matches stock) but
NOT exactly: missing the small-packet special case for desc[12..13]=0x100
when len was originally <64. Severity 🟡 — mostly OK because we pad to 64
before doing the encoding.

### [fn-43] `soft_insert_tx_1desc(desc, dir)` @ plat:6234 — DMA flush + HW kick

What it does: TINY. Flushes the desc cache (16 bytes) and kicks the
appropriate ring.

HW writes:
- `dma_cache_maint(desc, 0x10, 1)` (DMA flush)
- If dir==0: `tm_base + 0x10054 = 1` (UP kick)
- Else:      `tm_base + 0x10064 = 1` (DN kick)

In mainline? **✓** — we call `tm_write(e, 0x10054, 1)`. Stock kicks ONE
ring per skb, not both. Severity ✓.

---

## RX path

### [fn-45] `zx_pon_tm_int(irq, dev_id)` @ plat:6306 — TM IRQ top-half

What it does: reads `TM[0x100] & 3 & ~TM[0x104]` — the active unmasked
IRQ bits among bit 0 (RX pending) and bit 1 (TX done). If any set,
calls `pon_tm_net_int(netdev, status)` and increments IRQ counter.
Returns IRQ_HANDLED unconditionally.

HW reads:
- `TM[0x100]` (status)
- `TM[0x104]` (mask)

Sub-calls:
- `pon_tm_net_int(pon_netdev, status)` — [fn-46]

In mainline? **⚠** — we have equivalent top-half but it may not be
defensive about always returning IRQ_HANDLED. Severity 🟡.

### [fn-46] `pon_tm_net_int(netdev, status)` @ plat:6893 — TM IRQ mid-half

What it does: increments per-netdev IRQ count, **re-masks** TM IRQ
bits 0,1,2 (`TM[0x104] |= 7`) to prevent re-entry during NAPI poll,
stores the status in netdev struct, then `__napi_schedule` the NAPI
worker if it wasn't already scheduled.

HW writes:
- `TM[0x104] |= 7` (re-mask during NAPI run)

Sub-calls:
- `__napi_schedule(pon_netdev + 0x70)`

In mainline? **⚠** — we use generic `napi_schedule_irqoff()` without the
TM[0x104] re-mask. The stock pattern of MASK→NAPI_RUN→UNMASK in poll is
not replicated. Severity 🟡 — could cause IRQ storm during NAPI delay.

### [fn-47] `pon_tm_net_poll(napi, budget)` @ plat:8562 — NAPI worker

What it does: NAPI poll worker, drains RX descriptors until budget
exhausted or ring empty. For each desc:
- Read bp_idx from desc[7..8] (bp_idx = `(desc[7]>>1) | (desc[8] << 7)`)
- Compute BP buf addr (carved RAM region)
- `net_invalid_cache(BP_buf, len)` — invalidate cache for HW write-back
- If small packet: allocate skb via `__netdev_alloc_skb`, memcpy from BP
- If `switch_skb_recv` registered (fast-path hook): set vlan bits, call
  it directly (bypasses netif_receive_skb)
- Otherwise: `eth_type_trans` + `netif_receive_skb_sk` (slow path)
- Release BP back to BMU via `soft_release_rx_desc` or `pp_bmu_free_bp`
- Advance ring tail (`iVar13 + 0x7c`)

At end if budget remaining: `napi_complete_done()` + UN-MASK
`TM[0x104] &= 0xfffffffc` (bits 0+1 cleared = enabled).

HW writes:
- `TM[0x104] &= 0xfffffffc` (re-unmask at end if work complete)
- Indirect via `soft_release_rx_desc` and `pp_bmu_free_bp`

Sub-calls:
- `net_invalid_cache(addr, len)` — DMA cache invalidate (every desc)
- `__netdev_alloc_skb(netdev, len+0x12, 0x20)` — skb alloc
- `memcpy(skb->data, BP_buf, len)`
- `eth_type_trans(skb, netdev)` — fall-through path
- `netif_receive_skb_sk(...)` — fall-through
- `switch_skb_recv(skb)` — fast-path hook (if registered)
- `pp_bmu_free_bp(bp_idx, 0, jumbo_flag)` — [fn-48]
- `disableIRQinterrupts()` — guard the unmask write
- `napi_complete_done(napi, work_done)`

In mainline? **⚠ partial** — our NAPI poll drains rxdesc but doesn't
distinguish small packets vs jumbo, no fast-path hook. Severity 🟡.

### [fn-50] `soft_release_rx_desc(bp, qid, jumbo, port)` @ plat:7204 — release RX BP

What it does: writes to TM[0x4064/0x4068] to release the BP back to BMU.
Polls TM[0x4064] for ack first (max 30 retries).

HW writes:
- Spin until `TM[0x4064] & 1 == 0` (ready)
- `TM[0x4068] = (bp << 14) | (port << 4) | qid | (jumbo << 3)`
- `TM[0x4064] = 1` (trigger)

In mainline? **⚠** — we have BMU free helper but the desc-release path
is via TM[0x4068]/[0x4064], not just BMU free. Severity 🟡.

---

## BMU runtime

### [fn-44] `pon_tm_bmu_alloc_bp()` @ plat:5772 — alloc BP from pool

What it does: spinlocks, checks alloc_timeout flag, requests a BP via
`TM[0x8014] |= 1`, polls until `TM[0x8014] & 3 == 0` (max 200 retries),
reads result `TM[0x800c]`. If bit 31 of result is set → success, return
low 16 bits as bp_idx; else → fail.

HW writes:
- `TM[0x8014] |= 1` (request)

HW reads:
- `TM[0x8014]` (polling)
- `TM[0x800c]` (result)

In mainline? **⚠** — our `zx_bmu_alloc_bp` similar pattern. Severity ✓.

### [fn-48] `pp_bmu_free_bp(bp, ?, jumbo)` @ plat:5823 — free BP back

What it does: spinlocks, checks `allow_free_cnt > 0`, decrements it,
writes `TM[0x8010] = bp | (jumbo << 15)` to perform free. Polls
`TM[0x80dc]` (read of remaining credit) when needed.

HW writes:
- `TM[0x8010] = bp_idx | (jumbo << 15)` (free)

HW reads:
- `TM[0x80dc]` (BP credit counter)

In mainline? **⚠** — `zx_bmu_free_bp` similar pattern. Severity ✓.

### [fn-44b] `pon_tm_bmu_alloc_jumbo_bp()` @ plat:5861 — jumbo BP alloc

Same as fn-44 but writes `TM[0x8014] = 3` for jumbo request.

---

## Switch fabric helpers (called by init AND runtime)

### [fn-51] `pon_pp_add_port_to_vlan(vlan, port, mode)` @ plat:5102

What it does: VLAN-port membership entry. Reads existing entry via
`brg_ram_get(vlan, ...)`, OR-in port membership at `bits[port*2+1, port*2+2]` =
mode (3 = full, 0 = remove). Writes back via `brg_ram_set`.

HW writes (indirect via brg_ram_set):
- `pp_base + 0x8014..0x8028` (BRG RAM access regs)

In mainline? **⚠** — stock_table.h replay may have static VLAN entries
captured. Dynamic adds NOT replicated. Severity 🟡.

### [fn-52] `pon_pp_port_isolate_part_1(port, mask)` @ plat:4606 — port isolate (TINY)

What it does: OR-in mask into per-port isolation reg.

HW writes:
- `pp_base + 0x83c0 + port*4 |= mask`

Called as `pon_pp_port_isolate_part_1(6, 0xdf)` and `(7, 0xdf)` from
`pon_pp_brg_init` to isolate ports 6+7 (CPU + internal) except for bit 5
(presumably the CPU-to-CPU loopback or similar).

In mainline? **⚠** — verify in stock_table. Severity 🟡.

### [fn-53] `pon_pp_del_port_from_vlan(vlan, port)` — wrapper

What it does: calls `pon_pp_add_port_to_vlan(vlan, port, 0)` — mode 0 = remove.

In mainline? Same as [fn-51]. **N/A** standalone.

---

## PHY runtime

### [fn-54] `extphy_timer_func` @ plat:3137 — periodic external PHY poller

What it does: every 10 jiffies, reads external PHY (uni_phy[lan_up_port])
status via MDIO 0x1a (with page-select 0x1e dance), decides link
state/speed/duplex, calls `pon_npp_smac_disable` (if down) or
`smac_init` + `pon_npp_smac_config_speed_duplex` + `smac_sopc_mode_switch`
+ `pon_npp_smac_enable` (if up). Stores last state in `uni_phy_stat[port]`.

HW reads:
- MDIO reg 0x1e save
- MDIO 0x1e = 0 (page select)
- MDIO 0x1a read × 2 (latch clear + settled)
- MDIO 0x1e restore

Sub-calls:
- `zx_mdio_read/write(uni_phy[lan_up_port], reg)`
- `smac_init` + speed/duplex config helpers
- `pon_reset(1 << (port+6))` (per-port HW reset)
- `add_timer` (reschedule every 10 jiffies)

In mainline? **✗ missing** — only relevant for external WAN PHY. Severity 🟢
for LAN testing.

### [fn-55] `gephy_ldo_timer_func` @ plat:2442 — temp-driven LDO mode switch

What it does: every 200 jiffies, reads temperature via `temp_ctrl_read`,
based on hot/cold thresholds (0x32 + 0x3b = 50°C + 59°C) decides whether
to switch GePHY LDO modes via MDIO. Plus PHY status monitor +
auto-renegotiate trigger if speed drops or link-partner indicates speed
change.

HW reads:
- `temp_ctrl_read()` (CPU temp)
- mdio_read various GePHY regs (5, 10, 0x14, 0x15)

HW writes:
- mdio_write(phy, 0x10, 0xb640) + mdio_write(phy, 0x11, 0x1c) or 0x1f
  (LDO mode switch)

In mainline? **✗ missing** — no temp-driven LDO management. Severity 🟢
unless device runs at extreme temps.

### [fn-56] `phy_process(int)` @ plat:2916 — PHY IRQ tasklet body

Already documented under init walk [fn-35]. Called from IRQ tasklet
scheduled by `zx_phy_int`. Iterates 5 phys, processes link state changes.

### [fn-57] `switch_phy_int_check_part_5(port)` — per-port handler

Already documented in `stock_init_deep_re_2026-05-27.md`. The internal
GePHY IRQ-tasklet body — does `mdio_read 0x1a` twice with delay, decides
link UP/DOWN/speed change, calls smac_enable/disable.

In mainline? **✗ missing** — phylib state machine equivalent (different
mechanism).

---

## FFE (Fast Forwarding Engine) + IDM runtime

### [fn-49] `ffe_learn_skb` @ plat:9767 — Ghidra-undecompilable

`halt_baddata()` — imported kernel symbol from another module
(probably idmfdb or external). Called from TX path to learn flow rules
for HW fast-path forwarding.

In mainline? **✗ missing** — no FFE. Severity 🟢 (we don't have HW fast
forward anyway).

### [fn-58] `idm_net_register(dir, name)` @ plat:3685 — register IDM netdev

What it does: allocates etherdev with 0xf0 priv bytes, sets watchdog to
5s, copies name ("idm0" or "idm1"), copies idm_mac into hw_addr,
registers via `register_netdev`. Returns netdev pointer.

HW writes: **none**.

Sub-calls:
- `alloc_etherdev_mqs(0xf0, 1, 1)`
- `msecs_to_jiffies(5000)`
- `register_netdev(...)`

In mainline? **✗ missing** — no IDM netdev. Severity 🟡 (mgmt only).

### [fn-59] `idm_net_open(netdev)` @ plat:3759 — bring up IDM netdev

What it does: similar to `pon_tm_net_open` but for "idm0" instead of
"pon". Unmasks IDM IRQs at `NPP[0x8024] &= ~0x14`.

HW writes:
- `NPP[0x8024] = idm_int_mask & ~0x14` (unmask IDM IRQ bits)

In mainline? **✗ missing**. Severity 🟡.

### [fn-60] `idm_net_stop(netdev)` @ plat:3734 — bring down IDM netdev

Mirror of `idm_net_open` — re-masks IDM IRQs via OR-in 0x14.

HW writes:
- `NPP[0x8024] |= 0x14`

---

## Periodic timers

Summary of all `add_timer` calls done during init:

| Timer | Period | Function | Started in |
|---|---|---|---|
| `pon_tm_timer` | 1 jiffy | `pon_tm_timer_func` (TX-done reclaim, reads TM[0x10058]/[0x10068]) | [fn-18] pon_tm_net_init |
| `gephy_ldo_timer` | 200 jiffies | `gephy_ldo_timer_func` (temp-driven LDO + autoneg watch) | [fn-27] pon_npp_smac_init |
| `extphy_timer` | 10 jiffies | `extphy_timer_func` (external PHY status poll) | [fn-27] pon_npp_smac_init |
| `idm_timer` | (TBD) | (TBD) | [fn-23] pon_npp_idm_init |

In mainline:
- `pon_tm_timer` equivalent: ✓ added in commit `80f610eda`
- `gephy_ldo_timer`: ✗ missing
- `extphy_timer`: ✗ missing (external PHY not used)
- `idm_timer`: ✗ missing (no IDM)

---

## Summary of runtime functions documented

Documented in Part 2: 21 runtime/helper functions ([fn-40..60]).

## Cross-refs for runtime functions

- Stock TX desc format: `tx_path_stock_decomp.md` (older, focused on desc bytes)
- Stock TM IRQ lifecycle: `stock_init_deep_re_2026-05-27.md` (TM[0x100/0x104] mask dance)
- Stock PHY IRQ-storm-vs-no-storm: `phy_irq_state_machine_2026-05-27.md`

## Big-picture insight from full walk

The stock data path is:

```
TX:  net_xmit(skb) → pon_tm_net_tx → ffe_learn_skb → pon_tm_get_next_txdesc
                  → pon_tm_data_raw_send (BMU alloc + memcpy + desc fill)
                  → soft_insert_tx_1desc (cache flush + kick TM[0x10054]/[0x10064])
                  → HW dispatches via switch fabric → MAC[N] → wire

RX:  wire → MAC[N] → switch fabric → TM RX ring → IRQ bit 0 in TM[0x100]
                  → zx_pon_tm_int (top-half, GIC ack)
                  → pon_tm_net_int (mid-half, re-mask + napi_schedule)
                  → pon_tm_net_poll (NAPI worker)
                  → for each desc: cache invalidate, alloc skb, memcpy BP→skb
                  → switch_skb_recv (fast hook) OR netif_receive_skb (slow)
                  → pp_bmu_free_bp / soft_release_rx_desc (return BP to pool)
                  → at end: napi_complete + TM[0x104] &= ~3 (unmask)
```

Mainline is largely OK on the desc format / kick sequence (matches stock's
data_raw_send + soft_insert pattern). Where mainline diverges:
- No `ffe_learn_skb` / no fast-path FFE
- No `switch_skb_recv` hook — always slow path
- TM IRQ mid-half doesn't re-mask bits 0,1,2 during NAPI (could storm
  during long poll)
- Single netdev "sw" vs stock's "sw"+"pon" — IRQ gate at pon-open is
  bypassed by writing mask directly in init
- Periodic timers: only pon_tm_timer is replicated, the other 3 are
  missing (less critical for LAN testing)

---

# APPENDIX: Complete function inventory

Sweep of the remaining 275 functions in `decomp_all_plat_zxylzb_9128S.c`
(334 total — entries [fn-00..60] above cover the 59 functions on the init
path + key TX/RX/BMU/PHY runtime helpers; this appendix adds the rest).

Use `- [fn-NNN]` (sequential from fn-100) to differentiate appendix entries
from the detailed `## [fn-NN]` write-ups earlier. file:line uses the
plat-zxylzb decomp at `decomp_all_plat_zxylzb_9128S.c`. Anything written to
hardware is called out — boring leaves get a one-liner.

## CRC / checksum / parse helpers

- [fn-100] `tm_set_onu_mac(port, mac)` @ plat:3 — write 6-byte MAC to NPP[port*8 + 0x120/0x124]. **HW write**: `npp_base + port*8 + 0x120/0x124`. Valid ports 0..4. Used by OAM/OMCI for ONU identity.
- [fn-101] `tm_get_onu_mac(port, *mac)` @ plat:19 — readback of the above. Ports 0..4.
- [fn-102] `tm_get_tpid(port)` @ plat:41 — return `npp_base[port*4 + 0x9c]` (per-port VLAN TPID).
- [fn-103] `zx_tm_init` @ plat:50 — empty placeholder (just printks "zx_tm_init start/end"). Unused stub.
- [fn-104] `crc_16(buf, len, init)` @ plat:61 — CRC-16 over buf using `crc16_tab[]`. No HW.
- [fn-105] `crc_16_de(buf, len, init)` @ plat:82 — CRC-16 walking backwards (decoder/reverse variant).
- [fn-106] `ether_crc_32(buf, len, init)` @ plat:103 — standard Ethernet CRC-32 via lookup table.
- [fn-107] `proc_parse_mac(str, *out)` @ plat:123 — parse "aa:bb:cc:dd:ee:ff" → 6-byte array for /proc shell.
- [fn-108] `proc_parse_ip(str, *out)` @ plat:158 — parse "a.b.c.d" → 4-byte array.

## /proc shell debugger (runtime memory poker)

This is a powerful runtime debug aid: writes to `/proc/tm/shell` parse a
mini-DSL (`-f sym p1,p2,p3` etc.) and let stock devs invoke arbitrary
symbol functions, dump memory, walk task lists, resolve userspace
addresses via ELF symbol parsing, etc.

- [fn-109] `proc_get_cmd(buf, *argv, ...)` @ plat:190 — split a /proc write into argv[] array (skips quotes/whitespace).
- [fn-110] `getopt(argc, argv, optstring)` @ plat:255 — re-implementation of POSIX getopt for the in-kernel shell.
- [fn-111] `isint(str, base)` @ plat:356 — recognize numeric prefix (`0x`, `0b`, `0`) and verify all chars are digits.
- [fn-112] `module_proc_open(inode, file)` @ plat:409 — `single_open(file, shellReadProc, 0)`.
- [fn-113] `shellReadProc(seq)` @ plat:419 — prints the shell-command usage banner ("Usage: echo [OPTIONS] > /proc/tm/shell"). Documents -b/-w/-l/-f/-F/-c/-a/-s/-d/-p/-P/-t/-h flags.
- [fn-114] `shell_dump_sym_data(addr, sz)` @ plat:431 — hex+ASCII dump (xxd-style) of byte/word/dword data. Uses DataSynchronizationBarrier(0xf) before each load (suggests the targets may be MMIO).
- [fn-115] `shell_sym(...)` @ plat:529 — top-level shell command dispatch. Calls `getopt`, resolves symbol via `kallsyms_lookup_name` or `usyms_lookup_name`, then either invokes as function pointer (-f/-F) or reads memory (`shell_dump_sym_data`).
- [fn-116] `user_va2pa(task, vaddr)` @ plat:744 — userspace virtual→physical translation via page table walk (`find_vma` + manual MMU descent).
- [fn-117] `check_user_addr(addr)` @ plat:762 — bounds-check user-space pointer (against 0xC0000000).
- [fn-118] `shellWriteProc(file, buf, n, ppos)` @ plat:782 — entry called on write to `/proc/tm/shell`. Parses argv, dispatches to shell_sym.
- [fn-119] `create_shell_proc(parent)` @ plat:1070 — creates `/proc/tm/shell` entry with the module_proc_fops. Called by `tm_proc_init`.
- [fn-120] `myfile_read(fd, buf, n)` @ plat:1082 — kernel-mode file read using `vfs_read` for ELF parsing.
- [fn-121] `get_task_full_path.constprop.9(task)` @ plat:1105 — derive a task's exe full path via d_path on its mm.
- [fn-122] `myfile_open.constprop.10(path)` @ plat:1138 — kernel-mode `filp_open` wrapper for `usyms_lookup_*`.
- [fn-123] `myfile_lseek.constprop.14(fd, off)` @ plat:1154 — kernel-mode lseek wrapper.

## ELF symbol resolver (used by /proc/tm/shell for user-space symbols)

A mini ELF32 parser embedded in the driver so the in-kernel shell can
resolve `userland:libc:malloc`-style symbols. Notable for being a
self-contained user-symbol lookup, not relying on userspace tooling.

- [fn-124] `get_elf_header.constprop.5(fd, *ehdr)` @ plat:1177 — read+validate Elf32_Ehdr magic+class+endian.
- [fn-125] `get_data(fd, *buf, off, sz)` @ plat:1223 — pread-like helper.
- [fn-126] `get_32bit_elf_symbols(fd, ehdr, symtab, strtab)` @ plat:1260 — load all Elf32_Sym entries into in-kernel array.
- [fn-127] `get_32bit_section_headers.constprop.7(fd, *shdrs)` @ plat:1307 — load Elf32_Shdr table.
- [fn-128] `get_string_table.part.0.constprop.13(fd, *shdr)` @ plat:1380 — load `.strtab`/`.dynstr` from ELF.
- [fn-129] `func_insert(rbroot, sym)` @ plat:1409 — insert into rbtree of resolved symbols.
- [fn-130] `func_search(rbroot, addr)` @ plat:1441 — find symbol by address.
- [fn-131] `func_print(node)` @ plat:1468 — printk an rbtree node (debug).
- [fn-132] `build_func_usyms(task, path)` @ plat:1488 — full pipeline: open ELF, parse, build rbtree, attach to task struct.
- [fn-133] `usyms_lookup_name(name)` @ plat:1740 — find symbol by name in the cached rbtree.
- [fn-134] `usyms_lookup_addr(path, addr)` @ plat:1886 — find symbol by address, on-demand build cache if missing.
- [fn-135] `dump_task_info(task)` @ plat:2008 — printk pid, comm, state, exe path, etc. for debug command `-P <pid>`.

## NPP IRQ / global helpers (above smac_init level)

- [fn-136] `register_ptp_int(handler)` @ plat:2186 — stash `ptp_isr`, unmask NPP[0x04] bit 17. **HW**: `npp_base+0x04 &= ~0x20000`.
- [fn-137] `register_oam_int(handler)` @ plat:2197 — stash `oam_isr`, unmask NPP[0x04] bit 18. **HW**: `npp_base+0x04 &= ~0x40000`.
- [fn-138] `pon_npp_int(irq, dev)` @ plat:2208 — NPP top-level IRQ handler. Reads NPP[0]/NPP[4], routes bits 17/18 to ptp/oam ISRs.
- [fn-139] `pon_npp_int_enable(mask)` @ plat:2228 — clear `mask` bits in NPP[0x04] (unmask).

## SMAC per-port helpers (link-state machine guts)

- [fn-140] `smac_sopc_mode_switch(port, dup)` @ plat:2290 — poll NPP[port*0x40000+0x40004] bit `port+5` (up to 5×), then set/clear NPP[0x19038] bit `port+0x10` based on duplex (half=1, full=0). Followed by `__delay(10)`. **HW**: `npp_base + port*0x40000 + 0x19038`.
- [fn-141] `gephy_ldo_test(*params)` @ plat:2320 — manual LDO test: walks `uni_phy[]`, writes MDIO 0x10=0xb640 + 0x11=arg for each PHY (gated by boot-param `_DAT_f0807004|0x7000` flags).
- [fn-142] `gephy_tx_dac_drv_force_enable(port, on)` @ plat:2370 — force TX-DAC drive on/off via 8 MDIO writes (regs 0xb676/0xb677/0xb667/0xb668/0xb6c2/0xb6c1/0xb678/0xb669). Different values for on/off. **Critical**: this is the same TX-DAC sequence we replay in mainline `phy-zte-gephy` (Phase 1).
- [fn-143] `zx_phy_int(irq, hwirq)` @ plat:2420 — top-half of GePHY IRQ. Sets `has_phy_int[idx]=1`, writes the GIC pending bit (`g_phy_hwirq[idx]>>5 * 4 + base`), schedules `phy_process` tasklet.
- [fn-144] `pon_npp_smac_config_speed_duplex.part.0(port, speed, dup)` @ plat:2737 — guts: sets `NPP[port*0x40000+0x40000]` bits 13..15 for speed (0/1/2 = 10/100/1000) + bit 14 for duplex. **HW**: `npp_base + port*0x40000 + 0x40000`.
- [fn-145] `pon_npp_smac_enable.part.3(port)` @ plat:2769 — set bits 0+1 in `NPP[port*0x40000+0x40000]`. **HW**: `npp_base + port*0x40000 + 0x40000 |= 3`.
- [fn-146] `pon_npp_smac_disable.part.4(port)` @ plat:2782 — clear bits 0+1. **HW**: `npp_base + port*0x40000 + 0x40000 &= ~3`.
- [fn-147] `switch_phy_int_check.part.5(port)` @ plat:2797 — per-port PHY-IRQ tasklet body. Reads MDIO 0x1a twice with delay, decides UP/DOWN, re-resets MAC via pon_reset + smac_init + sopc_mode_switch + enable. Same logic also runs from extphy_timer. (Already documented in `stock_init_deep_re_*` and as [fn-57] above; this is the actual implementation behind that wrapper.)
- [fn-148] `pon_npp_smac_config_speed_duplex(port,sp,du)` @ plat:2957 — port<5 wrapper around .part.0.
- [fn-149] `smac_del_extphy_scan` @ plat:3026 — `del_timer(extphy_timer)`. Used at module unload.
- [fn-150] `switch_smac_get_rx_flow_crtl(port)` @ plat:3036 — read `NPP[port*0x40000+0x40090]`.
- [fn-151] `switch_smac_set_rx_flow_crtl(port, val)` @ plat:3048 — write `NPP[port*0x40000+0x40090]`. **HW**: `npp_base + port*0x40000 + 0x40090`.
- [fn-152] `switch_phy_int_check(port)` @ plat:3061 — port<4 wrapper around .part.5.
- [fn-153] `pon_npp_smac_enable(port)` @ plat:3111 — port<5 wrapper around .part.3.
- [fn-154] `pon_npp_smac_disable(port)` @ plat:3124 — port<5 wrapper around .part.4.
- [fn-155] `pon_npp_smac_mode(port, mode)` @ plat:3209 — set bits 22:23 of `NPP[(port+0x18)*4]`. **HW**: `npp_base + (port+0x18)*4 |= mode`.

## NPP sub-block init tinies + dump

- [fn-156] `smct_dump_pmau` @ plat:3325 — printk `NPP[0x100d8]` ("PMAU left counter").
- [fn-157] `phy_process` @ plat:2916 — (already documented as [fn-35] / [fn-56]) — PHY IRQ tasklet body.

## HWNAT stub (placeholder)

- [fn-158] `hwnat_is_from_cpu` @ plat:3367 — returns 1 (always). Stub.
- [fn-159] `multicast_flood_is_bind` @ plat:3376 — returns 1 (always). Stub.
- [fn-160] `hwnat_skb_to_foe` @ plat:3385 — returns 0 (no-op). Stub.
- [fn-161] `hwnat_set_hook_ptr` @ plat:3953 — installs above 3 as hooks. Called once from `pon_npp_idm_init`.
- [fn-162] `hwnat_unset_hook_ptr` @ plat:3965 — clears the 3 hooks. Module unload path.

## IDM (in-band management) netdev runtime

- [fn-163] `idm_eth_get_stats(netdev)` @ plat:3394 — return `netdev + 0x4cc` (rtnl stats area).
- [fn-164] `_idm_skb_stack_pop(stack_idx)` @ plat:3403 — pop a pre-allocated skb from one of 3 idm skb-stack pools (1024 entries each). Used to avoid skb alloc on hot RX path. Uses `idm_lock_stack[]` spinlock.
- [fn-165] `idm_skb_stack_pop(idx, need_len)` @ plat:3438 — wrapper that drops the skb if its tailroom is insufficient.
- [fn-166] `dump_idm_data(buf, len)` @ plat:3461 — hex dump of up to 128 bytes via printk.
- [fn-167] `idm_net_int(irq, dev)` @ plat:3486 — IDM IRQ top-half. Reads NPP[0x8020], re-masks NPP[0x8024] |= 0x14, schedules NAPI. **HW**: `npp_base+0x8024`.
- [fn-168] `idm_mode_proc_open(inode, file)` @ plat:3513 — `single_open(idm_proc_read, 0)`.
- [fn-169] `idm_proc_read(seq)` @ plat:3523 — 28 `seq_printf`s dumping IDM stats counters (`idm_pop_size_err[0..2]`, `idm_push_failed`, `idm_push_cnt`, `idm_skb_stack_full/empty`, `idm_rx_arp_count`, etc.).
- [fn-170] `idm_proc_write(file, buf, n)` @ plat:3606 — accepts commands like `tx_scan=1`, `tx_done=1`, sets `idm_net_debug` toggle, `idm_tx_scan`, `idm_net_check_speed`, etc.
- [fn-171] `idm_net_timeout(netdev)` @ plat:3721 — TX watchdog (5s) — wakes queue, refreshes jiffies stamp.
- [fn-172] `_idm_skb_stack_push(skb, idx)` @ plat:3785 — push freed skb back onto pool (or kfree if pool full).
- [fn-173] `idm_skb_stack_push(skb)` @ plat:3832 — if skb has `recycled` flag (bit 0x10 at +0xbc), push to pool 0; else kfree.
- [fn-174] `idm_check_tx_done_nolock` @ plat:3846 — drain NPP[0x8044] TX-done count, free completed skbs (up to 256/call). Updates `idm_tx_done_total`, `idm_skb_tx`. **HW**: `npp_base+0x8040` (kick), reads `npp_base+0x8044` (count).
- [fn-175] `idm_check_tx_done_lock` @ plat:3902 — IRQ-saved wrapper around the nolock variant.
- [fn-176] `idm_timer_func` @ plat:3920 — 1-jiffy periodic. If `idm_tx_scan` enabled, drains tx-done; if `idm_net_check_speed`, watches RX byte counter for > 1MiB/100-jiffies and disables further speed-check; re-arms timer.
- [fn-177] `idm_invalid_cache(addr, len)` @ plat:3977 — 32-byte aligned `dma_cache_maint(addr, len, 2)` invalidate.
- [fn-178] `idm_int_disable(mask)` @ plat:3988 — OR-in `mask` into NPP[0x8024]. **HW**: `npp_base+0x8024`.
- [fn-179] `idm_int_enable(mask)` @ plat:3999 — clear `mask` bits in NPP[0x8024]. **HW**: `npp_base+0x8024`.
- [fn-180] `dump_idm_desc_rx(desc)` @ plat:4010 — printk one RX desc (idm/len/ssid/ssid_vld).
- [fn-181] `idm_net_poll(napi, budget)` @ plat:4024 — IDM NAPI poll. Drains NPP[0x8020] descriptors, calls `_idm_skb_stack_push` to recycle, calls `netif_receive_skb` for forwarded ones. Returns work done.
- [fn-182] `dump_idm_desc_tx(desc)` @ plat:4196 — printk one TX desc.
- [fn-183] `idm_net_tx(skb, netdev)` @ plat:4208 — IDM TX entry. Allocates from `tx_desc` ring (1024 entries), writes desc[0..1] with skb data ptr + length, kicks via `NPP[0x8040] = count << 16`. **HW**: `npp_base+0x8040`.
- [fn-184] `idm_creat_status_proc` @ plat:4304 — `proc_mkdir("idm") + proc_create("status")`.
- [fn-185] `idm_cfg_byteorder(swap)` @ plat:4326 — set NPP[0x8000] bits 16..19 for endian swap. **HW**: `npp_base+0x8000`.
- [fn-186] `dump_idm_net_info(port)` @ plat:4460 — printk per-IDM-port stats (irq/irq_err/poll/rx_int/tx_int).

## L2/VLAN management + dump

- [fn-187] `_dump_vlan_info(vlan, mask)` @ plat:4482 — print VLAN id + bitmap of member ports (using `port_name[]`).
- [fn-188] `get_mac_status(idx)` @ plat:4503 — return "invalid"/"valid N"/"static" string for FDB-entry status nibble.
- [fn-189] `L2ReadProc(seq)` @ plat:4520 — `/proc/tm/l2` read: print mac aging time + dump_mac_data sweep.
- [fn-190] `VlanReadProc(seq)` @ plat:4535 — `/proc/tm/vlan` read: dump_all_vlan_info.
- [fn-191] `pon_pp_port_isolate(port)` @ plat:5288 — port<8 wrapper around .part.1. (.part.1 = [fn-52].)
- [fn-192] `brg_cal_mac_hash(mac)` @ plat:4619 — return crc_16(mac, 6, 0) & 0x3ff. **Switch FDB hash function.**
- [fn-193] `dump_mac_data(depth, id, *entry)` @ plat:4631 — printk one FDB entry (pbm/vlan/mac).
- [fn-194] `pon_pp_del_mac(mac, vlan)` @ plat:4649 — FDB delete: hash mac, brg_ram_get/set with status nibble cleared.
- [fn-195] `pon_pp_cls_port_mac(port)` @ plat:4710 — set PP[0x8004] bit 16 + port<<8 to trigger HW "clear all MAC for port". **HW**: `pp_base+0x8004`.
- [fn-196] `pon_pp_add_mac(mac, vlan, port)` @ plat:4723 — FDB add: hash mac, find empty depth slot, brg_ram_set with new entry + status=0xf (static valid).
- [fn-197] `pon_pp_dump_mac` @ plat:4797 — iterate hash table 0..1023 × depth 0..3, printk each filled entry.
- [fn-198] `pon_pp_dump_hash_mac(mac)` @ plat:4844 — printk all 4 depths of one hash bucket.
- [fn-199] `pon_pp_learned_mac(seq)` @ plat:4886 — same as dump_mac but only entries with non-zero learned bit.
- [fn-200] `L2WriteProc(file, buf, n)` @ plat:4924 — `/proc/tm/l2` write: parse add/del/clr/dump/aging commands, dispatch.
- [fn-201] `dump_vlan_info(vlan)` @ plat:5138 — brg_ram_get(vlan, ram=0) + _dump_vlan_info.
- [fn-202] `VlanWriteProc(file, buf, n)` @ plat:5163 — `/proc/tm/vlan` write: parse add/del/iso/dump commands.
- [fn-203] `dump_all_vlan_info` @ plat:5255 — for vlan in 0..4095, dump_vlan_info(vlan).
- [fn-204] `pon_pp_set_aging_time(secs)` @ plat:5301 — set PP[0x8188] = secs * 0x1107. **HW**: `pp_base+0x8188`. (0x1107 ≈ 4359, units are some clock divider — 100ms granularity.)
- [fn-205] `pon_pp_brg_int` @ plat:5311 — PP-bridge IRQ body. Reads `PP[0x8054] & ~PP[0x8050]` (4 status bits), printks "port migrate" / "static violation" / "hash collision" / "mac aged" event with the offending MAC + vlan + port. Then clears the latch register.
- [fn-206] `create_l2_proc` @ plat:5395 — proc_create_data("l2") with L2Read/Write.
- [fn-207] `create_vlan_proc` @ plat:5407 — proc_create_data("vlan") with VlanRead/Write.

## PP CLA classifier helpers (poke-style RAM access)

- [fn-208] `cla_ram_set(idx, params[4], ram_id)` @ plat:5419 — poll PP[0xc018] bit 0, write PP[0xc014] selector + PP[0xc01c..0xc028] 4-word data. **HW**: `pp_base+0xc014..0xc028`. Used by stock_table.h replays.
- [fn-209] `cla_ram_get(idx, *out, ram_id)` @ plat:5443 — readback variant. Polls twice (request → wait → read).
- [fn-210] `cla_ram_dump(idx, ram_id)` @ plat:5478 — cla_ram_get + printk 4 words.

## PP SADM (storm/admission) helpers

- [fn-211] `sadm_ram_set(idx, *data, ram_id)` @ plat:5555 — poll PP[0x4018], write PP[0x4014] selector + PP[0x401c] data. **HW**: `pp_base+0x4014/4018/401c`.
- [fn-212] `sadm_ram_get(idx, *out, ram_id)` @ plat:5576 — readback variant.
- [fn-213] `sadm_port_limit(port, kbps)` @ plat:5606 — set per-port rate limit. Computes bucket fill = (PP[0x4024]+1)*kbps*0x20 / 250000, writes via sadm_ram_set to ram_id=2 + ram_id=0 (enable).
- [fn-214] `sadm_dump_port(port)` @ plat:5628 — printk bucket configs for both cast + bcast directions.
- [fn-215] `pon_pp_sadm_init` @ plat:5685 — empty stub (returns 0). The 5750-decomp text confirms — vestigial.

## BMU helpers (additional)

- [fn-216] `pon_tm_bmu_disable` @ plat:5752 — `TM[0x8000] = 0`. **HW**: `tm_base+0x8000`.
- [fn-217] `zte_pp_free_skb_data` @ plat:5852 — empty stub. Returns void.
- [fn-218] `_check_bppe(jumbo)` @ plat:5896 — diagnostic: walks the BPPE pool (linked-list ring at `bppe_va_addr`), uses `_test_and_set_bit` to detect duplicate BP indices ("bppe bp %d repeat" / "bppe bp %d invalid"). Used to verify BMU pool isn't corrupt. Reads `TM[0x8048]`/`TM[0x804c]`/`TM[0x8080]`/`TM[0x8084]`. **DMA flush** `dma_cache_maint(local_244, 0x20000, 2)`.
- [fn-219] `dump_bmu_reg` @ plat:6103 — printk all 16 BMU MMIO regs (TM[0x8000..0x80dc] + TM[0xe8]/[0xf4]).
- [fn-220] `dump_bmu_status` @ plat:6128 — printk software counters (alloc/free/repeat/timeout) tracked by `bmu_status[]`.
- [fn-221] `check_bppe` @ plat:6147 — `_check_bppe(0)` for normal pool.
- [fn-222] `check_jumbo_bppe` @ plat:6157 — `_check_bppe(1)` for jumbo pool.

## DMA helpers

- [fn-223] `dma_cfg_byteorder(swap)` @ plat:6167 — set TM[0x10000] bits 16..19 to 0x2/0xf based on swap. **HW**: `tm_base+0x10000`.
- [fn-224] `dma_ram_get(idx, *out, ram_id)` @ plat:6186 — TM DMA-RAM RW (polls TM[0x10018] bit 0). **HW**: `tm_base+0x10014/18/1c`.
- [fn-225] `dma_tx_free(p1,p2,p3)` @ plat:6214 — write TM[0x1004c] = combined p1<<20 | p2<<12 | p3 | 0x200000 (TX desc-ring release). **HW**: `tm_base+0x1004c`. Polls bit 21 before write.
- [fn-226] `soft_insert_tx_multidesc(*ring)` @ plat:6249 — multi-desc TX kick. Computes wrap, two cache flushes (head+wrap-around), single HW kick of count to TM[0x10054] (UP) or TM[0x10064] (DN). **HW**: `tm_base+0x10054/10064`. Stock fast-path multi-skb batching (mainline uses 1-desc kick).

## TM IRQ + netdev runtime additions

- [fn-227] `set_pon_tm_int_info(addr)` @ plat:6323 — stash a struct pointer used by IRQ dispatch.
- [fn-228] `register_omci_oam_handle(handler)` @ plat:6352 — store `omci_oam_rx` fn pointer (called from `pon_tm_net_tx` ethertype 0x884c path).
- [fn-229] `pon_tm_check_tx_done_nolock(dir)` @ plat:6362 — read TM[0x10058] (UP CNT) or TM[0x10068] (DN CNT) and subtract from net_txq tracking counter. **Critical**: this is the "TX done reclaim" we replicated in mainline commit `80f610eda`. CONFIRMED clear-on-read by us 2026-05-25.
- [fn-230] `pon_tm_eth_get_stats(netdev)` @ plat:6376 — return `netdev + 0x4d0`.
- [fn-231] `pon_tm_net_register(dir, name)` @ plat:6385 — alloc_etherdev_mqs(0xf8, 1, 1), set ops to `pon_tm_net_netdev_ops`, copy default MAC, register. Returns netdev*.
- [fn-232] `pon_tm_net_timeout(netdev)` @ plat:6427 — TX watchdog: `netif_tx_wake_queue` + refresh jiffies.
- [fn-233] `pon_tm_timer_func` @ plat:6438 — periodic (jiffies+1): for each direction (UP=0, DN=1), spin-lock + `pon_tm_check_tx_done_nolock` + unlock. Increments `pon_tm_poll_cnt`. **Mainline-relevant**: this is the exact loop we cloned in commit `80f610eda`.
- [fn-234] `pon_tm_net_stop(netdev)` @ plat:6478 — `netif_carrier_off`, if name=="pon" then napi_disable + `TM[0x104] |= 7` (re-mask).
- [fn-235] `pon_tm_net_open(netdev)` @ plat:6502 — `netif_carrier_on`, if name=="pon" then `TM[0x104] &= 0xfffffffc` (unmask bits 0+1). **HW**: `tm_base+0x104`.

## TX/RX dump + diagnostic helpers

- [fn-236] `net_invalid_cache(addr, len)` @ plat:6527 — wrap `dma_cache_maint(aligned_addr, aligned_len, 2)` for RX cache invalidate.
- [fn-237] `dump_net_data(buf, len)` @ plat:6538 — hex dump up to 128 bytes via printk.
- [fn-238] `dump_desc(desc)` @ plat:6563 — printk 5 dwords of a desc + decode bp/gem/len.
- [fn-239] `dump_desc_tx(desc)` @ plat:6580 — same plus oam_omci_flag.
- [fn-240] `check_pon_tm_queue` @ plat:6980 — read TM[0x10058] / TM[0x10068] and compare to software counters, printk mismatch.
- [fn-241] `dump_pon_tm_net_info(port)` @ plat:7036 — printk per-netdev stats (`tx_packets`, `tx_bytes`, `rx_packets`, `irq`, `poll`).

## RED queue helpers (Random Early Drop policy)

- [fn-242] `red_get_queue_cfg(qid, *params, ram)` @ plat:7117 — readback of red_set_queue_cfg ([fn-32]).
- [fn-243] `red_get_queue_status(qid, *out, ram)` @ plat:7155 — read live queue status (occupancy, drop count) via TM[0x4030..0x4044].
- [fn-244] `is_red_alloc_bp_empty(jumbo)` @ plat:7186 — read TM[0x80dc] bits 9..0, return true if 0 (BMU pool empty).

## USCH (upstream scheduler) helpers — all empty/unused on LAN path

USCH is the upstream-PON queue scheduler. On this LAN-only device the
init is a no-op ([fn-39]) and these helpers are vestigial. They're
called by the /proc shell for debug only.

- [fn-245] `usch_ram_set(idx, val, ram)` @ plat:7293 — poll TM[0x14018], write TM[0x14014]+TM[0x1401c]. **HW**: `tm_base+0x14014/14018/1401c`.
- [fn-246] `usch_ram_get(idx, *out, ram)` @ plat:7313 — readback.
- [fn-247] `usch_set_que_wrr_pos(qid, pos)` @ plat:7340 — usch_ram_set(qid, pos&7, ram=0).
- [fn-248] `usch_get_que_wrr_pos(qid, *out)` @ plat:7359 — usch_ram_get(qid, ram=0).
- [fn-249] `usch_set_que_weight(qid, w)` @ plat:7381 — usch_ram_set(qid, w&0x3ffff, ram=1).
- [fn-250] `usch_get_que_weight(qid, *out)` @ plat:7400 — usch_ram_get(qid, ram=1).
- [fn-251] `usch_set_pq_shp_fill(qid, fill)` @ plat:7422 — usch_ram_set(qid, fill&0x1fffff, ram=2).
- [fn-252] `usch_get_pq_shp_fill(qid, *out)` @ plat:7441 — usch_ram_get(qid, ram=2).
- [fn-253] `usch_set_pq_shp_max(qid, max)` @ plat:7463 — usch_ram_set(qid, max&0x3fffff, ram=3).
- [fn-254] `usch_get_pq_shp_max(qid, *out)` @ plat:7482 — usch_ram_get(qid, ram=3).

## /dev/netdebug_dev char-device interface

- [fn-255] `netdebug_dev_open` @ plat:7513 — return 0 (no-op).
- [fn-256] `netdebug_dev_release` @ plat:7522 — return 0 (no-op).
- [fn-257] `netdebug_dev_ioctl(file, cmd, arg)` @ plat:7531 — main netdebug ioctl handler. Switches on cmd (0x100/0x101/...) to enable/disable trace, dump tables, etc. Operates on `g_netdebug_mod_tabel[]` bitmap.

## PON top-level IRQ + ISR registration helpers

- [fn-258] `zx_pon_int(irq, dev)` @ plat:7657 — PON top-level IRQ handler. Reads `pon_base+0x40040` & ~`pon_base+0x40044`. Bit 6 → lp_isr, bit 4 → set rog_onu_flag (rogue ONU detected). Returns IRQ_HANDLED.
- [fn-259] `register_gmac_int(handler, arg)` @ plat:7676 — store `gpon_isr` + arg, `pon_int_enable(1)`.
- [fn-260] `register_emac_int(handler, arg)` @ plat:7688 — store `epon_isr`, `pon_int_enable(0x100)`.
- [fn-261] `register_lp_int(handler, arg)` @ plat:7700 — store `lp_isr`, `pon_int_enable(0x40)`.
- [fn-262] `pon_is_registered` @ plat:7712 — if `lan_up==0 && pon_registered==0`, set `pon_registered=1`. Returns 1.
- [fn-263] `pon_int_enable(mask)` @ plat:7762 — clear `mask` bits in `pon_base + 0x40044`. **HW**: `pon_base+0x40044`. Inverse of mask register.

## SERDES helpers (PRBS / EQ / band-cal probe)

These are runtime-tunable SERDES diagnostics — none called from init.
All operate on `pon_serdes_base[0x40]` (control reg) and friends.

- [fn-264] `serdes_set_gen_en_open` @ plat:7825 — clear+set bit 29 of pon_serdes_base[0x40] (PRBS gen enable toggle). **HW**: `pon_serdes_base+0x40`.
- [fn-265] `serdes_set_gen_en_disable` @ plat:7837 — clear bit 29.
- [fn-266] `serdes_set_check_en_open` @ plat:7849 — toggle bit 30 (PRBS check). **HW**: `pon_serdes_base+0x40`.
- [fn-267] `serdes_set_check_en_disable` @ plat:7861 — clear bit 30.
- [fn-268] `serdes_set_err_cnt_en_open` @ plat:7873 — toggle bit 31 (PRBS error counter).
- [fn-269] `serdes_set_err_cnt_en_disable` @ plat:7885 — clear bit 31.
- [fn-270] `serdes_get_err_cnt` @ plat:7895 — read 32-bit error count split across `pon_serdes_base[0x60]>>16` and `pon_serdes_base[0x64]<<16`.
- [fn-271] `serdes_prbs_err_ok` @ plat:7904 — return bit 14 of `pon_serdes_base[0x68]` (PRBS sync ok).
- [fn-272] `serdes_err_cnt_reset` @ plat:7913 — clear+set bit 31 of pon_serdes_base[0x40].
- [fn-273] `serdes_set_tx_prbs_mode(mode)` @ plat:7952 — switch TX PRBS pattern: 0=PRBS7, 1=PRBS23, 2=PRBS31. **HW**: `pon_serdes_base[0]`, `pon_serdes_base[0x11]`.
- [fn-274] `serdes_set_rx_prbs_mode(mode)` @ plat:7978 — same for RX. **HW**: `pon_serdes_base+0x14`, `pon_serdes_base+0x44`.
- [fn-275] `serdes_rx_ready` @ plat:8003 — check `pon_serdes_base+0x68 & 0x10` for RX-PLL ready.
- [fn-276] `serdes_set_tx_eq(mode)` @ plat:8017 — set TX equalizer pre+post: mode=1 → 3dB, mode=2 → 6dB. **HW**: `pon_serdes_base[0]`, `pon_serdes_base[1]`.
- [fn-277] `serdes_set_rx_eq(mode)` @ plat:8041 — set RX equalizer. **HW**: `pon_serdes_base+8`.

## APB / PLL low-level helpers

- [fn-278] `apb_write(off, val)` @ plat:8061 — write `pon_serdes_base[off] = val`. **HW**: `pon_serdes_base+off`. Generic poke.
- [fn-279] `apb_read(off)` @ plat:8071 — read `pon_serdes_base[off]`.
- [fn-280] `apb_bit_write(off, val, width, lsb)` @ plat:8080 — bitfield poke at pon_serdes_base[off].
- [fn-281] `pll_ssc_cfg(*base, p2, p3, p4, p5, p6)` @ plat:8172 — PLL Spread-Spectrum Clock config (variant of pll_cfg_*). Sets ramp register `base[2] |= 0x800`, configures feedback/post-div, then loops on `base[1] & 0x10000000` for "PLL lock". Not called from init.

## Userspace VMA / task dumpers (debug aids)

- [fn-282] `dump_task_fd(task)` @ plat:8349 — iterate task's open files (struct fdtable), printk "fd N : path".
- [fn-283] `my_dump_vma(task)` @ plat:8384 — iterate rb_tree of VMAs (vm_area_structs), printk each region with rwx flags + heap/stack/file path. Re-impl of `/proc/N/maps`.
- [fn-284] `get_usyms_lib(task, vaddr)` @ plat:8513 — given task+vaddr, find the VMA + offset in ELF, call `usyms_lookup_addr`.

## Stubs

- [fn-285] `pp_skb_recycle` @ plat:8551 — returns 0xffffffff. Stub.
- [fn-286] `cleanup_module` @ plat:9045 — empty body. **No cleanup performed on module unload** — the device is meant to be hot-swapped via warm reboot only.

## Imported kernel symbols — `halt_baddata` PLT stubs (87 entries)

These are PLT-style relocations Ghidra can't decompile (the actual entry
is a single instruction PLT branch resolved at module-load time via
`kallsyms_lookup_name`). All decompile as a one-line `halt_baddata()`
call. They're listed for completeness — none are stock-specific code, all
are standard Linux kernel symbols.

- [fn-287] `alloc_etherdev_mqs` @ plat:9056 — std.
- [fn-288] `filp_open` @ plat:9068 — std (used by shell ELF reader).
- [fn-289] `strcpy` @ plat:9081 — std.
- [fn-290] `skb_put` @ plat:9093 — std.
- [fn-291] `_clear_bit` @ plat:9105 — std.
- [fn-292] `rb_last` @ plat:9117 — std.
- [fn-293] `kallsyms_lookup` @ plat:9129 — std (resolves addr → name).
- [fn-294] `_test_and_set_bit` @ plat:9141 — std.
- [fn-295] `_set_bit` @ plat:9153 — std.
- [fn-296] `__arm_ioremap` @ plat:9165 — std (used by reg_def_set indirectly).
- [fn-297] `rb_next` @ plat:9177 — std.
- [fn-298] `memcpy` @ plat:9189 — std.
- [fn-299] `kfree` @ plat:9202 — std.
- [fn-300] `proc_create_data` @ plat:9214 — std.
- [fn-301] `free_pages` @ plat:9226 — std.
- [fn-302] `rb_insert_color` @ plat:9238 — std.
- [fn-303] `_raw_spin_lock_irqsave` @ plat:9250 — std.
- [fn-304] `_raw_spin_lock` @ plat:9262 — std.
- [fn-305] `full_name_hash` @ plat:9274 — std.
- [fn-306] `eth_type_trans` @ plat:9286 — std.
- [fn-307] `napi_complete_done` @ plat:9298 — std.
- [fn-308] `msecs_to_jiffies` @ plat:9310 — std.
- [fn-309] `_raw_spin_unlock_bh` @ plat:9322 — std.
- [fn-310] `__get_free_pages` @ plat:9334 — std.
- [fn-311] `zx_mdio_write` @ plat:9346 — **Custom**, exported by mdio kmod. Per-PHY MDIO write.
- [fn-312] `__alloc_skbuff` @ plat:9358 — std (likely __alloc_skb).
- [fn-313] `__napi_schedule` @ plat:9370 — std.
- [fn-314] `netif_receive_skb_sk` @ plat:9382 — std.
- [fn-315] `find_vma` @ plat:9394 — std (used by shell user_va2pa).
- [fn-316] `__aeabi_idiv` @ plat:9406 — std ARM divmod.
- [fn-317] `kallsyms_lookup_name` @ plat:9418 — std (the unexported one we need module_alloc trick for — see MEMORY entry).
- [fn-318] `request_threaded_irq` @ plat:9430 — std.
- [fn-319] `add_timer` @ plat:9442 — std.
- [fn-320] `netif_napi_add` @ plat:9454 — std.
- [fn-321] `warn_slowpath_null` @ plat:9466 — std.
- [fn-322] `strncmp` @ plat:9478 — std.
- [fn-323] `zte_get_pon_mode` @ plat:9489 — **Custom** ZTE platform helper. Returns 0x10 (LAN-only) for our hw rev.
- [fn-324] `register_netdev` @ plat:9501 — std.
- [fn-325] `strncpy` @ plat:9513 — std.
- [fn-326] `free_netdev` @ plat:9526 — std.
- [fn-327] `of_iomap` @ plat:9538 — std (DT iomap).
- [fn-328] `sscanf` @ plat:9550 — std.
- [fn-329] `printk` @ plat:9563 — std.
- [fn-330] `kmalloc_order` @ plat:9575 — std.
- [fn-331] `_raw_spin_unlock_irqrestore` @ plat:9587 — std.
- [fn-332] `__print_symbol` @ plat:9599 — std.
- [fn-333] `netif_tx_wake_queue` @ plat:9611 — std.
- [fn-334] `proc_mkdir` @ plat:9623 — std.
- [fn-335] `__memzero` @ plat:9635 — std ARM bzero.
- [fn-336] `__aeabi_uidiv` @ plat:9647 — std ARM unsigned divmod.
- [fn-337] `rb_first` @ plat:9659 — std.
- [fn-338] `__netdev_alloc_skb` @ plat:9671 — std.
- [fn-339] `strcmp` @ plat:9683 — std.
- [fn-340] `sprintf` @ plat:9696 — std.
- [fn-341] `dma_cache_maint` @ plat:9709 — std (ARM-specific cache op).
- [fn-342] `of_device_is_compatible` @ plat:9721 — std.
- [fn-343] `init_timer_key` @ plat:9733 — std.
- [fn-344] `__dev_kfree_skb_any` @ plat:9745 — std.
- [fn-345] `filp_close` @ plat:9757 — std.
- [fn-346] `__register_chrdev` @ plat:9781 — std.
- [fn-347] `netif_carrier_off` @ plat:9793 — std.
- [fn-348] `seq_printf` @ plat:9805 — std.
- [fn-349] `simple_strtoul` @ plat:9817 — std.
- [fn-350] `dev_get_by_name` @ plat:9829 — std.
- [fn-351] `_raw_spin_lock_bh` @ plat:9841 — std.
- [fn-352] `netif_carrier_on` @ plat:9853 — std.
- [fn-353] `__tasklet_hi_schedule` @ plat:9865 — std.
- [fn-354] `irq_to_desc` @ plat:9889 — std (used by register_phy_int).
- [fn-355] `zx_mdio_read` @ plat:9901 — **Custom** (zte mdio kmod).
- [fn-356] `irq_of_parse_and_map` @ plat:9913 — std.
- [fn-357] `strlen` @ plat:9925 — std.
- [fn-358] `napi_disable` @ plat:9938 — std.
- [fn-359] `del_timer` @ plat:9950 — std.
- [fn-360] `__copy_to_user` @ plat:9962 — std.
- [fn-361] `single_open` @ plat:9974 — std.
- [fn-362] `strchr` @ plat:9986 — std.
- [fn-363] `skb_recycle` @ plat:9999 — std (kernel skb pool recycle).
- [fn-364] `_raw_spin_unlock` @ plat:10011 — std.
- [fn-365] `of_find_matching_node_and_match` @ plat:10023 — std (DT lookup).
- [fn-366] `__copy_from_user` @ plat:10035 — std.
- [fn-367] `show_stack` @ plat:10047 — std (used by shell -e).
- [fn-368] `msleep` @ plat:10059 — std.
- [fn-369] `__kmalloc` @ plat:10071 — std.
- [fn-370] `d_path` @ plat:10083 — std (dentry → path).
- [fn-371] `find_task_by_vpid` @ plat:10095 — std (used by shell -p / -P).

(Two `halt_baddata` entries were already covered earlier: `ffe_learn_skb`
[fn-49] at plat:9767 and `temp_ctrl_read` [fn-13] at plat:9879. They both
also decompile as PLT stubs but are documented above for context.)

---

## Total inventory

- **Detailed entries (Part 1 + Part 2)**: 61 functions ([fn-00..60])
- **Appendix entries**: 275 functions ([fn-100..371], with some doubling: counts include [fn-13] and [fn-49] visited above)
- **Grand total functions in the decomp**: 334 ✓

Coverage breakdown by category (appendix):
- /proc shell + ELF symbol resolver: 27 functions
- IDM netdev runtime: 23 functions
- SMAC per-port helpers: 16 functions
- BMU helpers + checkers: 7 functions
- L2/VLAN management: 18 functions
- PP CLA/SADM helpers: 8 functions
- USCH helpers (vestigial): 10 functions
- SERDES PRBS/EQ helpers: 14 functions
- TM IRQ + netdev runtime: 9 functions
- Dump/debug helpers (printk-only): ~15 functions
- PON top-level IRQ helpers: 6 functions
- HWNAT stubs: 5 functions
- Imported kernel-symbol PLT stubs: 85 functions
- Other helpers (crc, parse, hash): ~10 functions

## Top findings from the appendix sweep

1. **Massive in-kernel debug shell** (`shell_sym` + ELF parser + symbol
   rbtree): the stock driver embeds a complete /proc shell that can
   resolve userspace symbols by parsing ELF files at runtime — a major
   debugging tool that explains how stock devs poked the device. Notable
   for understanding stock-side workflow but **N/A for mainline port**.

2. **`pon_tm_timer_func`** ([fn-233]) is the exact pattern we cloned in
   mainline commit `80f610eda`. The stock side runs it both UP+DN
   directions in a single timer callback — confirms our 1-jiffy reclaim
   timer matches stock behavior. Note: stock spin-locks around
   `pon_tm_check_tx_done_nolock` while we use `napi_disable`-guarded
   reclaim — equivalent but worth verifying.

3. **HW writes in untraced helpers** worth checking in mainline:
   - `pon_pp_set_aging_time` ([fn-204]) writes `PP[0x8188] = secs * 0x1107` — FDB aging.
     Stock default not visible from init, but `pon_pp_brg_init`'s `PP[0x8188]=0x13f434` (see [fn-21])
     evaluates to ~73 seconds aging time at the 0x1107 scale. Mainline may have a different default.
   - `pon_pp_brg_int` ([fn-205]) handles 4 HW-detected events (port migrate / static violation /
     hash collision / mac aged) by reading PP[0x8060..0x80b0..0x80f0..0x8138] event-info regs.
     Mainline doesn't register PP IRQ at all, so these events are silently lost.
   - `idm_check_tx_done_nolock` ([fn-174]) reads NPP[0x8044] as a TX-done count and writes
     `NPP[0x8040]` as kick — same clear-on-read pattern as TM[0x10058]. Suggests **all the
     "DMA CNT" registers in this hardware are clear-on-read** (we only confirmed it for
     TM[0x10058]). Worth probing for the other rings if we ever activate IDM.

