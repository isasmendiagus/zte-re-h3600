# Mainline gap matrix — stock RE → driver implementation plan

Built from the 5 static analysis docs in
`tasks/00.10.02.re-stock-kmods/findings/static_analysis_*.md` + the
runtime visibility + init deep RE findings. This is the **actionable
roadmap**: each row is a discrete gap with target file, test, and
implementation order.

**Scope of this doc**:
- **TIER A** — ~20 critical gaps that block ping bidi (🔴) or unlock
  observability (🟢 tooling). These are well-RE'd and ready to
  implement. Built first iteration.
- **TIER B** — remaining ~150 functions on the data path that need
  systematic mainline cross-reference. Subsequent iterations will
  expand this section.
- **OUT OF SCOPE** — ~1900 functions that are debug/PerfMon/sysfs
  handlers / cleanup / WiFi LED / DSL / OAM — not on LAN data path.

Architecture target (refactor):
```
linux-v6.6/drivers/net/ethernet/zte/
├── zx279128-eth.c    KEEP   netdev/NAPI/TX/RX hot path only
├── zx-pon-plat.c     NEW    chip init (ioremap, reset, SERDES, IRQ)
├── zx-tm-sdk.c       NEW    per-block SDK (tmOnuReg pattern, debugfs stats)
├── zx-switch.c       OPT    switch fabric (VLAN/FDB/multicast)  - only if size warrants
└── *.h tables        KEEP   data
```

DT (linux-v6.6/arch/arm/boot/dts/zte/zx279128s.dtsi): add 3 reg ranges
+ 4 IRQ entries to `pon@92000000`.

---

## TIER A — critical gaps (Layers 0..5)

| ID  | Source (doc + fn) | What it does | Mainline status | Sev | Layer | Target file | Test |
|---|---|---|---|---|---|---|---|
| A01 | runtime_visibility | debugfs `/sys/kernel/debug/zx_eth/pipeline_stats` mirroring stock `tmTest/tmup`+`tmdn` output (per-stage counters) | ❌ missing | 🟢 tool | 0 | zx-tm-sdk.c (new) | cat returns format matching stock; counters increment under traffic |
| A02 | plat fn-23 + agent finding | `zx-pon-plat.c` skeleton: probe entry, of_iomap for the 3 missing regions (sys_ctrl @ 0x94100000, pin_mux @ 0x94200000, pon_serdes @ 0x9fe00000) + DT changes | ❌ missing (only top_crm + pon_base mapped) | 🔴 | 1 | zx-pon-plat.c (new) + dtsi | After init, `cat /sys/kernel/debug/zx_eth/iomem` shows 5 mappings |
| A03 | plat fn-02 | `pon_reset(0xffffffff)`: pon_base[8] &= ~0xff..; udelay 100x; pon_base[8] \|= 0xff.. | ❌ missing | 🟡 | 1 | zx-pon-plat.c | Probe boots cleanly cold-from-DTR; reg pon[8] readable post-reset |
| A04 | plat fn-05 (`tm_pon_tm_init` direct write) | `TM[0xc008] = 0` (single write missing) | ❌ missing | 🟡 | 1 | zx-tm-sdk.c | read TM[0xc008] = 0 after init |
| A05 | plat fn-00 (init_module direct writes) | `pon_base + 0x4001c = 0xf` | ❌ missing | 🟡 | 1 | zx-pon-plat.c | read pon[0x4001c] = 0xf after init (via fpga -r equiv) |
| A06 | plat fn-03 `zx_pon_clk_reset_init` | SERDES bring-up: TOPCRM cycle + reg_def_set + serdes_mode_set + wait rxpll + wait PLL band + temp-compensated band write + sys_ctrl bit clear + final TOPCRM bits. **Big function — break into sub-commits** | ❌ entire fn missing | 🔴🔴 | 2 | zx-pon-plat.c | Read `pon_serdes_base[0x44]` post-init: bits 16-21 should encode coarse band (stock had 0x2c on cold boot at room temp) |
| A06a | plat fn-11 `reg_def_set` | 24 writes to pon_serdes_base[0..0x17] default values | ❌ missing | 🔴 | 2 | zx-pon-plat.c | Read `pon_serdes_base[0x11]` = 0xea00a013 pre-band-cal |
| A06b | plat fn-12 `serdes_mode_set(1)` | 7 writes setting SERDES mode (mode=1 for kernel) | ❌ missing | 🔴 | 2 | zx-pon-plat.c | Read `pon_serdes_base[0]` low byte = 0xa5 |
| A06c | plat fn-10 `ref_clk_set(1)` + fn-30 `pll_cfg_integer` | Reference clock PLL setup with integer divider (mode=1) | ❌ missing | 🔴 | 2 | zx-pon-plat.c | Read `top_crm_base[0x50]` after init |
| A07 | plat fn-04 `register_pon_int` | request_threaded_irq for `g_pon_irq` (defensive — stock /proc/interrupts: 0 fires) | ❌ missing | 🟢 | 3 | zx-pon-plat.c | /proc/interrupts shows pon entry registered |
| A08 | plat fn-07 → request PP IRQ + agent finding (PP IRQ exposes 4 events: port migrate, static violation, **hash collision**, mac aged) | request_threaded_irq for `g_pp_irq` with handler reading PP[0x8060, 0x80a8, 0x80f0, 0x8138] | ❌ missing | 🟡 | 3 | zx-pon-plat.c | /proc/interrupts shows pp entry; debugfs shows event counts |
| A09 | plat fn-08 → request NPP IRQ | request_threaded_irq for `g_npp_irq` | ❌ missing | 🟢 | 3 | zx-pon-plat.c | /proc/interrupts shows pon_npp entry |
| A10 | plat fn-46 `pon_tm_net_int` + fn-47 `pon_tm_net_poll` | TM IRQ mid-half **MASK→NAPI→UNMASK pattern**: handler re-masks TM[0x104] \|= 7 before scheduling NAPI; poll worker unmasks `TM[0x104] &= ~3` at napi_complete | ⚠️ partial (we unmask but don't re-mask) | 🟡 | 3 | zx279128-eth.c | NAPI poll handles >100 frames without IRQ storm; `tm_irq_count` matches stock pattern |
| A11 | switch fn-555 (agent finding) | Link-state-dependent: `fpga_write_reg(0xd3000, 0x03f40050)` on link-UP, `0x1f40fa0` on link-DOWN. Stock_table.h is STATIC and captures only one of these. | ❌ missing | 🔴 | 4 | zx279128-eth.c (in adjust_link callback) | After cable plug, fpga -r 0xd3000 returns 0x03f40050; on unplug, 0x1f40fa0 |
| A12 | tm.ko agent finding | ACL-extra-index init for entries **10..15** (not just 0..9). `zte_zx_api_pp_global_init` re-inits via `cla_set_extra_index_table(i)` for i=0..15 | ❌ partial (we cover 0..9) | 🟡 | 4 | zx-tm-sdk.c | Read CLA extra-index table entries 10..15 → non-zero |
| A13 | tm.ko agent finding | `zte_zx_api_pp_set_trap_queue`: protocol → CPU-queue mapping for 8 priority classes. Critical for ARP-reply / ICMP-reply routing to CPU. | ❌ missing | 🔴 | 4 | zx-tm-sdk.c | Send ping host→device. Stock-equivalent debugfs counter `cla trap pkts` increments |
| A14 | plat fn-21 `pon_pp_brg_init` | 13 PP_BRG writes + VLAN port adds (0/1 for 8 ports) + port isolate (6, 0xdf), (7, 0xdf) | ⚠️ partial (stock_table.h covers writes; VLAN adds + isolate may be missing) | 🟡 | 4 | zx-tm-sdk.c (or zx-switch.c if split) | After init: PP[0x8050]=0xfffffffa, PP[0x83c0+6*4] has 0xdf set |
| A15 | plat fn-09 `zx_pon_clk_reset` | Final clock enable: `TOPCRM[0xc] \|= 0x1e0` | ❌ missing | 🟢 | 5 | zx-pon-plat.c | Read TOPCRM[0xc] post-init has bits 5-8 set |
| A16 | plat fn-23 `pon_npp_idm_init` (partial — IDM mgmt path, low LAN priority) | IDM netdev + DMA rings | ❌ not relevant for LAN | — | skip | — | — |
| A17 | plat fn-18 `pon_tm_net_init` | Two netdevs ("sw" + "pon"). NAPI bound to "pon" only. **Mainline only has "sw"** but bypasses gate by writing mask direct. | ⚠️ workable as-is | 🟢 | 5 | zx279128-eth.c | Optional: add "pon" netdev for stock parity |
| A18 | plat fn-55 `gephy_ldo_timer_func` | Periodic (200 jiffies) temp-driven GePHY LDO mode switch | ❌ missing | 🟢 | 5 | (defer) | Not blocking ping bidi at room temp |
| A19 | plat fn-54 `extphy_timer_func` | Periodic (10 jiffies) external WAN PHY poll | ❌ missing | 🟢 | skip | — | Not relevant for LAN-only testing |
| A20 | plat fn-37 `zx5201_config` | External WAN PHY (zx5201) init via MDIO addrs 8-9 | ❌ missing | 🟢 | skip | — | LAN tests don't need WAN PHY |

## Implementation order (commit-by-commit plan)

| Iter | Layer | Target gap(s) | Notes |
|---|---|---|---|
| 1 | — | THIS DOC (matrix) | Commit + schedule next |
| 2 | 0 | A01 | debugfs `pipeline_stats` infra. Creates `zx-tm-sdk.c` + Makefile/Kconfig entries |
| 3 | 1 | A02 | DT 3 new reg ranges + `zx-pon-plat.c` skeleton + ioremap of 5 regions |
| 4 | 1 | A03, A04, A05 | Three small writes batched: pon_reset + TM[0xc008]=0 + pon[0x4001c]=0xf |
| 5 | 2 | A06a | `reg_def_set` — 24 SERDES default writes |
| 6 | 2 | A06b | `serdes_mode_set(1)` — 7 SERDES mode writes |
| 7 | 2 | A06c | `ref_clk_set(1)` + `pll_cfg_integer` |
| 8 | 2 | A06 final | `zx_pon_clk_reset_init` glue + waits + band cal |
| 9 | 3 | A10 | TM IRQ mid-half MASK→NAPI→UNMASK pattern |
| 10 | 3 | A07, A09 | Register PON + NPP IRQs (defensive empty handlers) |
| 11 | 3 | A08 | Register PP IRQ with the 4-event handler |
| 12 | 4 | A11 | Carrier-up `fpga[0xd3000]` link-state writer |
| 13 | 4 | A14 | PP_BRG VLAN adds + port isolate (if not in stock_table) |
| 14 | 4 | A12 | ACL-extra-index 10..15 init |
| 15 | 4 | A13 | Trap-queue protocol mapping |
| 16 | 5 | A15 | Final TOPCRM clock enable |
| 17 | 5 | end-to-end | Ping bidi test, capture diff vs stock |

## TIER B — to be expanded in subsequent iters

The full per-function walk of the 2087 documented functions (mostly
sysfs handlers, PerfMon counters, ACL helpers, OMCI/GPON legacy)
against mainline state. Most are out-of-scope for LAN ping bidi but
will be needed for feature parity later.

Tier B candidates to cross-reference:
- PHY runtime: stock `extphy_timer_func` vs our phylib state machine
- BMU runtime: stock alloc/free vs `zx_bmu_alloc_bp` / `zx_bmu_free_bp`
- TX path desc format: byte-by-byte comparison stock `pon_tm_data_raw_send` vs `zx_sw_xmit`
- Switch fabric register replay completeness vs stock chip_tm_init API call sequence
- IRQ handler ack patterns: stock `zx_pon_pp_int` / `pon_npp_int` bodies

These will be added as TIER B as we hit dependencies on them during TIER A iterations.

## OUT OF SCOPE

- DSL stack (`/etc/dsl/{boot,fw}.bin` + nfbi binary): Realtek external chip, separate from eth fabric
- mt7915 WiFi (separate PCIe chip with own driver in mainline)
- OMCI/GPON legacy in switch.ko (PON-derived but not used for LAN)
- /proc/tm/shell debugger (27 functions in plat) — stock dev tool, N/A
- WLAN LED handlers in idmfdb (depends on mt7915 kallsyms)
- cspd userspace daemon (not a kernel concern)
- `patch.ko` runtime binary patching
- `kudp.ko` (kernel UDP hooks — unclear purpose, probably mgmt)
- `shellproc.ko` (in-kernel shell)

## Cross-refs

- Source docs:
  - `tasks/00.10.02.re-stock-kmods/findings/static_analysis_plat_zxylzb_init.md` (1821 lines)
  - `tasks/00.10.02.re-stock-kmods/findings/static_analysis_tm_ko_init.md` (2359 lines)
  - `tasks/00.10.02.re-stock-kmods/findings/static_analysis_switch_ko_init.md` (1177 lines)
  - `tasks/00.10.02.re-stock-kmods/findings/static_analysis_idmfdb_init.md` (121 lines)
  - `tasks/00.10.02.re-stock-kmods/findings/static_analysis_zx_ponreg_init.md` (90 lines)
- Runtime:
  - `tasks/00.01.eth-driver/findings/stock_runtime_visibility_2026-05-27.md`
  - `tasks/00.01.eth-driver/findings/stock_sysfs_debug_tree_2026-05-27.md`
- Deep RE:
  - `tasks/00.01.eth-driver/findings/stock_init_deep_re_2026-05-27.md`
  - `tasks/00.01.eth-driver/findings/stock_init_sequence_analysis_2026-05-27.md`
