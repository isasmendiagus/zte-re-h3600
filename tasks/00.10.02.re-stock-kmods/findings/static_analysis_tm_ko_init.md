# tm.ko init flow — static analysis depth-first walk

**Working doc.** Walking from `tm.ko`'s module init entry point
(`tm_initModule`) through every function call, depth-first, documenting
each. tm.ko is the largest of the stock kmods (~1.9MB decomp, ~70k
lines) and implements the Traffic Manager / Packet Processor /
Network Packet Processor (TM/PP/NPP) bring-up that sits on top of the
chip-level setup done by `plat-zxylzb_9128S`.

For each function: file:line where defined, brief comment of what it
does, HW writes (addr + value via fpga_write_reg or tmOnuRegWrite —
both go through a sub-block register table), and list of sub-calls.

Source: `tasks/00.10.02.re-stock-kmods/findings/decomp_all_tm.c` (raw
Ghidra decomp of stock tm.ko).

Cross-reference convention: `[fn-NN]` link tags so we can grep.

---

## Legend

- **HW writes**: register address + value the function pokes. Most TM
  writes go through `fpga_write_reg(addr, val)` (plat-level helper, an
  imported kernel symbol). The 5-digit addresses (e.g. `0x10009`,
  `0x75015`, `0xe8131`) are sub-block IDs that the plat layer maps to a
  physical offset on the TM/PP/NPP base.
- **Sub-calls**: nested function invocations (descended in same doc)
- **In mainline?**: ✓ replicated / ⚠ partial / ✗ missing / N/A — we
  haven't done the cross-check yet, so all are marked "unknown — to
  verify".
- **Severity if missing**: 🔴 likely path-breaking · 🟡 unclear ·
  🟢 informational

---

## Entry point — `tm_initModule`

The module's `init_module` symbol is actually named **`tm_initModule`**
(at `0x78198`, decomp line 69411). It is the function ELF-tagged as the
module init. Mirror cleanup is `tm_cleanupModule @ 0x781cc` (line
69426) which unregisters the chardev and tears down sysfs.

---

## [fn-00] `tm_initModule` @ decomp_all_tm.c:69411 — module init top-level

What it does: registers the `tm_sample_dev` char device, creates the
sysfs interface tree, runs the ACL test setup (which actually inits
the SDK DB + ACL RAM tables), then runs the big `tm_initial`
bring-up. Five-call wrapper.

HW writes (direct): **none** — all writes are pushed down into
sub-calls.

Sub-calls in order:
1. `tm_devReg()` — [fn-01] — register `tm_sample_dev` chardev (major 0xc6)
2. `tmUsrInterfaceCreate()` — [fn-02] — create sysfs groups
3. `printk("tm_initModule begin...")`
4. `aclTestInit()` — [fn-03] — trampoline into SDK init
5. `tm_initial()` — [fn-04] — main TM/PP/NPP bring-up
6. `printk("tm_initModule end...")`
7. `return 0`

In mainline? **unknown — to verify**. Severity 🔴 if missing — this is
the whole TM block. Mainline needs to replicate the `tm_initial` core
even if it skips the sysfs/chardev surfaces.

---

## [fn-01] `tm_devReg` @ decomp_all_tm.c:120 — register tm_sample_dev chardev

What it does: registers char device major 0xc6 named
`"tm_sample_dev"` with `tm_devFops`. Used by the user-space `tmCli`
helper (orca-style debug shell) to peek/poke TM regs from userspace.

HW writes: **none** (kernel chardev registration only).

Sub-calls:
- `__register_chrdev(0xc6, 0, 0x100, "tm_sample_dev", &tm_devFops)`

In mainline? **unknown — to verify**. Severity 🟢 — userspace debug
surface, not on hot path.

---

## [fn-02] `tmUsrInterfaceCreate` @ decomp_all_tm.c:69389 — sysfs surface wrapper

What it does: one-line wrapper around `tm_sysfs_init`. Returns 0 on
success, -1 on failure.

HW writes: **none**.

Sub-calls:
- `tm_sysfs_init()` — [fn-02a]

In mainline? **unknown — to verify**. Severity 🟢 — diag surface.

---

### [fn-02a] `tm_sysfs_init` @ decomp_all_tm.c:69304 — create the /sys/devices/platform/tm/* tree

What it does: looks up the `"tm"` platform_device (registering a fresh
one via `platform_device_register_full` if missing), then creates 10
sysfs groups on it. These are the `tmTest`, `ppCla`, `nppGreg`,
`ppPm`, `nppPm`, `nppSdet`, `nppSpa`, `nppAdm`, `ppBrg`, `red`
directories we observed under `/sys/devices/platform/tm/`.

HW writes: **none**.

Sub-calls:
- `bus_find_device_by_name(&platform_bus_type, 0, "tm")`
- `platform_device_register_full(...)` (if device missing)
- `sysfs_create_group(dev, &pp_pm_info_group)` — "ppPm"
- `sysfs_create_group(dev, cla_info_group)` — "ppCla"
- `sysfs_create_group(dev, &greg_info_group)` — "nppGreg"
- `sysfs_create_group(dev, &npp_pm_info_group)` — "nppPm"
- `sysfs_create_group(dev, &sdet_info_group)` — "nppSdet"
- `sysfs_create_group(dev, &spa_info_group)` — "nppSpa"
- `sysfs_create_group(dev, &adm_info_group)` — "nppAdm"
- `sysfs_create_group(dev, &brg_info_group)` — "ppBrg"
- `sysfs_create_group(dev, &red_info_group)` — "red"
- `sysfs_create_group(dev, &tm_test_group)` — "tmTest"

In mainline? **unknown — to verify**. Severity 🟢 — pure diag.

---

## [fn-03] `aclTestInit` @ decomp_all_tm.c:149 — SDK init trampoline

What it does: misleadingly named — just calls `tm_sdk_init` and
returns 1. Real work is in [fn-03a].

HW writes: **none**.

Sub-calls:
- `tm_sdk_init()` — [fn-03a]

In mainline? **unknown — to verify**. Severity 🔴 — propagates into
SDK DB init.

---

### [fn-03a] `tm_sdk_init` @ decomp_all_tm.c:54799 — initialize SDK databases

What it does: initializes the in-memory TM SDK databases (flow-list,
ACL aging tables) and the ACL RAM if not already done. Clears
`acl_api_busy_lock`. If `lan_up == 1` (which it is, set by plat init),
clears `g_fast_opti` to disable the L2-fastpath optimization.

HW writes: **none directly** (zeroes carved RAM ranges via memzero in
sub-calls).

Sub-calls:
- `tm_db_init()` — [fn-03a-1]
- `aclRamInit.part.6()` — [fn-03a-2] (if `g_aclRamInited == 0`)
- Sets globals: `acl_api_busy_lock = 0`, `g_fast_opti = 0` (when
  `lan_up == 1`).

In mainline? **unknown — to verify**. Severity 🟡 — these are
software-only DB structures, but downstream code (ACL rules, flow
fast-path) depends on them.

---

#### [fn-03a-1] `tm_db_init` @ decomp_all_tm.c:54023 — flow-list DB init

What it does: zeroes a 100-byte stack flow-template, calls
`operListInit` to allocate the per-list head/tail kmem_cache slots,
then twice inserts a default flow entry (up + down direction) via
`addFlowOperInfo`. Sets the `gs_upDefFlowInit`/`gs_downDefFlowInit`
flags.

HW writes: **none** (pure-software list setup).

Sub-calls:
- `__memzero(...)` ×2
- `operListInit()` — allocs `s_tmFlowInfoListHead_u`,
  `s_tmSubRamInfoListHead`, `s_tmNatInfoListHead`,
  `s_tmAclInfoListHead`, etc. via `kmem_cache_alloc` (defined at
  decomp_all_tm.c:50290)
- `addFlowOperInfo(...)` ×2 (defined at decomp_all_tm.c:51948)

In mainline? **unknown — to verify**. Severity 🟢 — only matters if
mainline replicates the ACL/flow fast-path; we don't.

---

#### [fn-03a-2] `aclRamInit.part.6` @ decomp_all_tm.c:54670 — wipe ACL RAM + program index tables

What it does: zeroes two huge physical RAM regions
(`0xf1020000` for 4 MiB, `0xf1420000` for 1 MiB — both inside the
carved TM-reserved memory), then in a loop programs 10 ACL
extra-index tables via `cla_set_extra_index_table`. On loop end,
zeroes more state (DAT_000606d0 region, 0x10208-byte table at
DAT_000606d4), optionally calls `tm_acl_3tuple_fast_init` +
`tm_acl_fast_init` if `g_fast_opti != 0` (which is 0 in LAN-mode), then
reads back the outspace cfg and sets `g_aclRamInited = 1`.

HW writes:
- `__memzero(0xf1020000, 0x400000)` — wipes ACL RAM region (4 MiB)
- `__memzero(0xf1420000, 0x100000)` — wipes ACL aux RAM (1 MiB)
- 10× `cla_set_extra_index_table(idx, &local_2c)` — programs extra-
  index lookup config for indices 1..10 via CLA indirect access
  (registers around `0x37xxx` based on neighboring cla helpers; goes
  through `tmOnuRegWrite`)
- `cla_get_outspace_cfg(...)` — reads back outspace policy
- Sets globals: `g_aclRamInited = 1`

Sub-calls:
- `__memzero` ×N
- `cla_set_extra_index_table` (decomp:2650) — ACL extra-index table
  programmer
- `tm_acl_3tuple_fast_init` (decomp:54576) — skipped (g_fast_opti=0)
- `tm_acl_fast_init` (decomp:54140) — skipped
- `cla_get_outspace_cfg`

In mainline? **unknown — to verify**. Severity 🟡 — the 5 MiB RAM wipe
is critical if ACL is exercised (uninit RAM = stale rules firing). Our
driver does not use ACL so probably safe to skip, but the
`cla_get_outspace_cfg` readback informs `ACL_OUT_SPACE_SEL` which other
init paths reference.

---

## [fn-04] `tm_initial` @ decomp_all_tm.c:47123 — main TM/PP/NPP bring-up

What it does: top orchestrator. Five-port loop reads-back & writes
SMAC config (round-trip per port to ensure registers latched), sets
`g_tm_init_flag = 0` initially, then chains: TM-init → PP-init →
NPP-init. Sets `g_tm_init_flag = 1` only when all three return 0.

HW writes (via sub-calls):
- 5 × (smac_get_cfg + smac_set_cfg) — round-trip read/write of SMAC
  config for ports 0..4 (these go through `tmOnuRegRead/Write` ⇒
  `fpga_read_reg/write_reg`, NPP SMAC reg ID `1`)

Sub-calls:
- `smac_get_cfg(port, buf)` × 5 — [fn-04a]
- `smac_set_cfg(port, buf)` × 5 — [fn-04b]
- `tm_pon_tm_initial()` — [fn-05]
- `tm_pon_pp_initial()` — [fn-06]
- `tm_pon_npp_initial()` — [fn-07]
- Sets global: `g_tm_init_flag = 1` on success

In mainline? **unknown — to verify**. Severity 🔴 — this is the meat
of TM bring-up.

---

### [fn-04a] `smac_get_cfg` @ decomp_all_tm.c:20707 — read SMAC config word, unpack to per-bit fields

What it does: reads NPP SMAC register ID `1` via `tmOnuRegRead`, then
bit-decomposes the 32-bit word into ~23 sub-fields (param_2[0..0x16]
each pulled from a 1..3-bit field).

HW writes: **none** (it's a read).

HW reads:
- `tmOnuRegRead(1, &local_14, port_id, &smacRegTable)` ⇒ ultimately
  `fpga_read_reg(table_entry.base + port * stride)`

Sub-calls:
- `tmOnuRegRead` (decomp:35337)

In mainline? **unknown — to verify**. Severity 🟢 — feeds into [fn-04b].

---

### [fn-04b] `smac_set_cfg` @ decomp_all_tm.c:20668 — pack and write SMAC config word

What it does: bounds-checks each of the ~23 sub-fields read by
[fn-04a], then bit-composes them into a single 32-bit word and writes
back via `tmOnuRegWrite(1, packed_value, port, &smacRegTable)`. So the
get/set pair is effectively a "touch" / identity write — useful for
forcing register-state coherency.

HW writes:
- 1× `tmOnuRegWrite(1, composed_word, port, &smacRegTable)` — writes
  the packed SMAC reg for the given port (5 ports total).

Sub-calls:
- `tmOnuRegWrite` (decomp:35356)

In mainline? **unknown — to verify**. Severity 🟡 — the round-trip
may be a defensive register-coherency dance from cold boot.

---

## [fn-05] `tm_pon_tm_initial` @ decomp_all_tm.c:47097 — TM block init

What it does: chains the 4 TM sub-block inits (reg, RED, QMG, SCH) and
ORs their return codes. On failure logs ratelimit'd error.

HW writes: **none directly**.

Sub-calls:
- `tm_pon_tm_reg_initial()` — [fn-05a]
- `tm_pon_tm_red_initial()` — [fn-05b]
- `tm_pon_tm_qmg_initial()` — [fn-05c]
- `tm_pon_tm_sch_initial()` — [fn-05d]

In mainline? **unknown — to verify**. Severity 🔴 — TM is critical
path for RX/TX descriptor handling.

---

### [fn-05a] `tm_pon_tm_reg_initial` @ decomp_all_tm.c:42448 — TM IRQ masks + gap

What it does: sets queue-int masks (3 queues × 1 bit-flag), DMA
descriptor-int masks (2 dirs), 8 FIFO masks, then writes the
"gap_add" inter-packet-gap value (4 octets).

HW writes (via `tmOnuRegWrite` with TM sub-block IDs):
- TM reg `0xb` (queue_int_mask): clear-and-set bit for queues 0,1,2
- TM reg `0xc` (dma_des_int_mask): clear-and-set bits 0 + 1
- TM reg `0xd` (fifo_int_mask): clear-and-set bits 0..7
- TM reg `0x1` (gap_add via `pon_tm_set_gap_add`) = `4`

Sub-calls:
- `pon_tm_set_queue_int_mask(0,0)` — [fn-05a-1]
- `pon_tm_set_queue_int_mask(0,1)` — same fn, queue 1
- `pon_tm_set_queue_int_mask(1,2)` — same fn, queue 2 (note flag=1)
- `pon_tm_set_dma_des_int_mask(1,1)` — [fn-05a-2]
- `pon_tm_set_dma_des_int_mask(1,0)`
- `pon_tm_set_fifo_int_mask(i, 1)` ×8 — [fn-05a-3]
- `pon_tm_set_gap_add(4)` — [fn-05a-4]

In mainline? **unknown — to verify**. Severity 🟡 — IRQ masks
overlap with what plat-zxylzb does; gap_add is TM-specific.

---

#### [fn-05a-1] `pon_tm_set_queue_int_mask` @ decomp_all_tm.c:35019 — RMW queue int mask

What it does: RMW on TM register `0xb` (queue_int_mask sub-block):
read current value via `tmOnuRegRead`, clear bit at `param_2`, set
bit to `param_1`, write back via `tmOnuRegWrite`.

HW writes:
- `tmOnuRegRead(0xb, &local_14, 0, ...)` (read)
- `tmOnuRegWrite(0xb, (local_14 & ~(1<<param_2)) | (param_1<<param_2), 0, ...)` (RMW write)

Sub-calls:
- `tmOnuRegRead` / `tmOnuRegWrite` — both indirect through
  `fpga_read_reg`/`fpga_write_reg` (Ghidra `halt_baddata` — these are
  imported kernel symbols from plat-zxylzb; see decomp:69885 +
  decomp:70019).

In mainline? **unknown — to verify**. Severity 🟡.

---

#### [fn-05a-2] `pon_tm_set_dma_des_int_mask` @ decomp_all_tm.c:35117 — RMW DMA desc int mask

What it does: identical pattern to [fn-05a-1] but on TM reg `0xc`.
RMW one bit per call.

HW writes: same shape as [fn-05a-1], reg id `0xc`.

Sub-calls: `tmOnuRegRead`/`tmOnuRegWrite`.

In mainline? **unknown — to verify**. Severity 🟡.

---

#### [fn-05a-3] `pon_tm_set_fifo_int_mask` @ decomp_all_tm.c:35212 — RMW FIFO int mask

What it does: same RMW pattern on TM reg `0xd`. One bit per call,
called 8× for FIFO indices 0..7.

HW writes: `tmOnuRegWrite(0xd, ...)`.

Sub-calls: `tmOnuRegRead`/`tmOnuRegWrite`.

In mainline? **unknown — to verify**. Severity 🟡.

---

#### [fn-05a-4] `pon_tm_set_gap_add` @ decomp_all_tm.c:34523 — set TM inter-packet gap

What it does: writes the gap-add value (4) to TM reg `0x1` via
`tmOnuRegWrite`. Range-checks `param_1 < 0xf`.

HW writes:
- `tmOnuRegWrite(1, 4, 0, ...)` — gap-add = 4 octets

Sub-calls: `tmOnuRegWrite`.

In mainline? **unknown — to verify**. Severity 🟡 — affects min
IPG on egress.

---

### [fn-05b] `tm_pon_tm_red_initial` @ decomp_all_tm.c:42487 — RED policy bring-up

What it does: full RED (Random Early Drop) configuration. Enables
RED globally, opens the "out" path, enables trap-color, sets share
mode + per-share max thresholds, then loops through ~640 queues across
3 ranges programming per-queue out-buffer / in-buffer / buffer config.

This corresponds 1:1 with `pon_tm_red_init` from the plat-zxylzb walk
([plat-fn-14]) but with **different per-queue parameters** — the TM
kmod's RED config is more granular than the plat-level pre-init.

HW writes:
- TM reg `0` (`red_cfg_enable`) = `(1) + (0)*2 = 1` — red_en=1, color_en=0
- TM reg `1` (`red_open_out_en`) = `1`
- TM reg `2` (`red_trap_color_en`) = `1`
- TM reg `3` (`red_share_mode`) = `1`
- TM reg `4` (`red_in_share_max`) = `0x3ff`
- TM reg `5` (`red_up_out_share_max`) = `0x3fff`
- Loop 0..0x190 (=400) — `red_set_out_buffer_queue_cfg(qid, thd, drop_p)`:
  - qid 0..0xf:    thd=0x3ff, drop_p=0
  - qid 0x10..0x14f: thd=0x40,  drop_p=0x7ff
  - qid 0x150..0x177 (24): thd=0x40, drop_p = (qid&7==0 ? 0x200 : 0x80)
  - qid 0x178..0x187: thd=0x40, drop_p=0xc00
  - qid 0x188..0x18f: thd=0x40, drop_p=0x3ff
- Loop 0..0x180 — `red_set_in_buffer_queue_cfg(qid, 0x20, 0x200)`
- Loop 0..0x180 — `red_set_buffer_queue_cfg(qid, &params)` with
  params = {0x3fff, 0x80, 0xff, 0x100, 0x80, 0x80, 0x20, 0x10, 0x200, 0xff}

Sub-calls (each writes via `tmOnuRegWrite`):
- `red_set_cfg_enable(0,1)` — [fn-05b-1] (decomp:33086)
- `red_set_open_out_en(1)` (decomp:33149)
- `red_set_trap_color_en(1)` (decomp:33206)
- `red_set_share_mode(1)` (decomp:33263)
- `red_set_in_share_max(0x3ff)` (decomp:33493)
- `red_set_up_out_share_max(0x3fff)` (decomp:33596)
- `red_set_out_buffer_queue_cfg(...)` × 400 (decomp:33649)
- `red_set_in_buffer_queue_cfg(...)` × 0x180 (decomp:33896)
- `red_set_buffer_queue_cfg(...)` × 0x180 (decomp:34147)

In mainline? **unknown — to verify**. Severity 🟡 — RED config sets
QoS drop behaviour; our mainline already replicates some of these via
the plat-side [plat-fn-14] call.

---

### [fn-05c] `tm_pon_tm_qmg_initial` @ decomp_all_tm.c:42624 — Queue Manager init

What it does: disables external-DDR-only mode, enables DDR-cache
mode, and if `lan_up == 1` sets the up/down RAM thresholds.

HW writes (via `fpga_write_reg` through qmg_set_* helpers):
- `qmg_set_ext_ddr_only_enable(0)` — disable ext-DDR-only path
- `qmg_set_ddr_cache_enable(1)` — enable DDR cache
- If `lan_up == 1`:
  - `qmg_set_up_ram_thd(0x50)` — UP RAM threshold = 80
  - `qmg_set_dn_ram_thd(0x1fa0)` — DN RAM threshold = 8096

Sub-calls:
- `qmg_set_ext_ddr_only_enable` (decomp:32811)
- `qmg_set_ddr_cache_enable` (decomp:32865)
- `qmg_set_up_ram_thd` (decomp:32704)
- `qmg_set_dn_ram_thd` (decomp:32758)

In mainline? **unknown — to verify**. Severity 🔴 — QMG selects the
RAM backing for queue state; mis-config could cause queue-state
corruption.

---

### [fn-05d] `tm_pon_tm_sch_initial` @ decomp_all_tm.c:47023 — Scheduler init

What it does: reads FPGA reg `0x10006` (selects HW-rev/board mode),
enables DWRR (both primary and secondary), enables queue+tcont
shapers, enables HW up+dn ageing, then for each of 32 tconts × 8
queues sets shaper rates to 1,600,000 (1.6 Mbps base) via
`tm_tcont_sharp_set` / `tm_tcont_que_sharp_set`. Finally programs
age-mode and HW-age-time based on the board-mode register read.

HW writes (via fpga_write_reg through sch_set_* helpers):
- `sch_set_dwrr_enable(1)`
- `sch_set_secsch_dwrr_enable(1)`
- `sch_set_que_sharp_enable(1)`
- `sch_set_tcont_sharp_enable(1)`
- `sch_set_hw_up_age_enable(1)`
- `sch_set_hw_dn_age_enable(1)`
- Loop 0..0x1f (32 tconts):
  - `tm_tcont_sharp_set(tcont, 1600000)` (per-tcont rate)
  - Loop 0..7 (8 queues):
    - `tm_tcont_que_sharp_set(tcont, queue, 1600000)`
- If `fpga_read_reg(0x10006) == 0` (board-mode A):
  - `tm_tcont_que_age_mode_set(0, 1)` + `(1, 1)` — age-mode = 1
  - `tm_tcont_que_hw_age_time_set(100000000)` — 100 ms
- Else (board-mode B):
  - `tm_tcont_que_age_mode_set(0, 0)` + `(1, 1)`
  - `tm_tcont_que_hw_age_time_set(220000000)` — 220 ms
  - `sch_set_oam_age_enable(1)`

Sub-calls:
- `fpga_read_reg(0x10006)` — board-mode probe
- `sch_set_dwrr_enable` (decomp:28953)
- `sch_set_secsch_dwrr_enable` (decomp:29258)
- `sch_set_que_sharp_enable` (decomp:28892)
- `sch_set_tcont_sharp_enable` (decomp:29136)
- `sch_set_hw_up_age_enable` (decomp:29014)
- `sch_set_hw_dn_age_enable` (decomp:29380)
- `tm_tcont_sharp_set` × 32
- `tm_tcont_que_sharp_set` × 32×8 = 256
- `tm_tcont_que_age_mode_set` × 2
- `tm_tcont_que_hw_age_time_set` × 1
- `sch_set_oam_age_enable(1)` (decomp:29319, board-mode B only)

In mainline? **unknown — to verify**. Severity 🟡 — scheduler config
relevant only if we exercise multiple queues; mainline uses 1 queue.

---

## [fn-06] `tm_pon_pp_initial` @ decomp_all_tm.c:43647 — PP block init

What it does: chains 7 PP sub-block inits (reg, sadm, brg, cla, adm,
dpa, pm) and ORs their return codes.

HW writes: **none directly**.

Sub-calls:
- `tm_pon_pp_reg_initial()` — [fn-06a]
- `tm_pon_pp_sadm_initial()` — [fn-06b]
- `tm_pon_pp_brg_initial()` — [fn-06c]
- `tm_pon_pp_cla_initial()` — [fn-06d]
- `tm_pon_pp_adm_initial()` — [fn-06e]
- `tm_pon_pp_dpa_initial()` — [fn-06f]
- `tm_pon_pp_pm_initial()` — [fn-06g]

In mainline? **unknown — to verify**. Severity 🔴 — PP is the
packet-processing core (classifier, bridge, ADM accounting).

---

### [fn-06a] `tm_pon_pp_reg_initial` @ decomp_all_tm.c:42650 — PP general regs + TPIDs

What it does: sets mult-mode flags, jumbo length, PM and ACL base
physical addresses (in carved RAM), then programs 8 TPID slots (0x8100
default + 0x88a8/0x9100/0x9200 at the canonical indices).

HW writes:
- `pon_pp_set_mult_mode(0, 0)` and `(0, 1)` — 2 mode bits
- `pon_pp_set_jumb_len(0x800)` — jumbo length = 2048
- `pon_pp_set_pm_base_addr(pdt_mem + 0x40420000 + ZX_RESERVE_MEM_SIZE * -0x100000)`
  — PM table base (carved RAM phys addr)
- `pon_pp_set_acl_base_addr(pdt_mem + 0x40020000 + ZX_RESERVE_MEM_SIZE * -0x100000)`
  — ACL table base
- TPID slot 0,4,5,6,7 = `0x8100` (standard 802.1Q)
- TPID slot 1 = `0x9100`
- TPID slot 2 = `0x88a8` (802.1ad S-tag)
- TPID slot 3 = `0x9200`

Sub-calls:
- `pon_pp_set_mult_mode`
- `pon_pp_set_jumb_len`
- `pon_pp_set_pm_base_addr` — sets a TM/PP register to the carved
  RAM phys addr for PM (PerfMon) tables
- `pon_pp_set_acl_base_addr` — same for ACL tables
- `pon_pp_set_tpid` × 8

In mainline? **unknown — to verify**. Severity 🔴 — PM/ACL base
addrs MUST point at the right carved RAM region, else the PP block
writes scribble RAM. TPIDs are essential for VLAN parsing.

---

### [fn-06b] `tm_pon_pp_sadm_initial` @ decomp_all_tm.c:42702 — SADM (stream ADM) init

What it does: enables stream-ADM and stream-ADM-trap, sets the
"one-second" tick count to 200,000,000 (=200 MHz clock).

HW writes:
- `sadm_set_adm_en(1)`
- `sadm_set_adm_trap_en(1)`
- `sadm_set_one_second(200000000)` — informs ADM of HW clock for
  per-second rate accounting

Sub-calls: 3× sadm_set_* (fpga_write_reg under the hood)

In mainline? **unknown — to verify**. Severity 🟡 — accounting only,
not packet-path-critical.

---

### [fn-06c] `tm_pon_pp_brg_initial` @ decomp_all_tm.c:43579 — Bridge init

What it does: configures the L2 bridge (Switch-style brg block):
per-port-transfer enable, disables vlan-check on inport+outport for
all 8 ports, enables SMAC lookup + sets fail-action, enables global
mirror + MAC-age, sets MAC ram-addr-sel and aging-cycle, then **busy-
spins 100 × `__delay`** to let the stat-clean toggle settle, finally
re-enables per-port learn mode + DA-lookup + multicast forwarding +
TLS bits.

⚠ **Ghidra mis-decode** at decomp:43621:
`(*_serdes_set_check_en_open)(0x66665b0)` — this is actually a
`__delay(0x66665b0)` call (the `0x66665b0` is the
loops_per_jiffy-equivalent magic). 100 iterations of a busy delay.

HW writes (via `sbrg_set_*` and `tm_*` helpers ⇒ fpga_write_reg):
- 8× `sbrg_set_pt_transfer_en(port, 1)`
- 8× `tm_vlan_check_ena_set(port, 0, 0)` — inport vlan-check off
- 8× `tm_vlan_check_ena_set(port, 1, 0)` — outport vlan-check off
- 8× `sbrg_set_pt_smac_look_en(port, 1)` — enable SMAC lookup
- 8× `sbrg_set_pt_smac_lookfail_pktdeal(port, 0)` — fail action = forward
- `sbrg_set_irq_en_mask(10)` — mask = 0xa
- `sbrg_set_globle_mirror_en(1)`
- `sbrg_set_macaddr_age_en(1)`
- `tm_mac_ramaddr_sel_set(1)`
- `sbrg_set_hash_collision_pktdeal(1)`
- `sbrg_set_multicst_md(1)`
- `sbrg_set_macaddr_exchange_md(1)`
- 8× `sbrg_set_pt_learn_mode(0, port)` — learn-mode reset
- `tm_mac_aging_cycle_set(0)` — clear aging cycle
- `sbrg_set_stat_clean_en(1)`
- 100× `__delay(0x66665b0)` (decomp ⇒ `(*_serdes_set_check_en_open)`)
- `sbrg_set_stat_clean_en(0)`
- `tm_mac_aging_cycle_set(300)` — final aging cycle = 300
- 8× per-port loop:
  - `sbrg_set_pt_learn_mode(1, port)` — learn-mode on
  - `sbrg_set_pt_da_lookup_en(port, 1)`
  - `sbrg_set_unknown_unicst_fwd(port, 0)`
  - `sbrg_set_unknown_multicst_fwd(port, 1)`
  - `sbrg_set_pt_tls(port, 0)`
- `sbrg_set_unknown_unicst_fwd(0, 1)` — port 0 (PON/CPU?) overrides
- `sbrg_set_pt_tls(0, 1)`

Sub-calls: many `sbrg_set_*` + `tm_vlan_check_ena_set` + `__delay`.

In mainline? **unknown — to verify**. Severity 🔴 — this is the
switch L2 fabric. Without it the bridge doesn't forward / learn /
flood properly. **This is likely the most impactful PP sub-init.**

---

### [fn-06d] `tm_pon_pp_cla_initial` @ decomp_all_tm.c:42725 — Classifier init

What it does: reads current CLA config, sets 3 fields to 1 (local_2c,
28, 24 — probably 3 enable bits), zeroes the rest of the struct, then
writes back. Then sets outspace-cfg=2, oth_l3_pkt_action=0,
up/dn/l3 MTU lengths to 0x3fff. Finally calls `api_lock_init` to
zero `fast_api_busy_lock` and `acl_api_lock`.

HW writes:
- `cla_set_config(auStack_48)` — writes a CLA struct (~12-word)
- `cla_set_outspace_cfg(2, 0)`
- `cla_set_oth_l3_pkt_action_cfg(0)`
- `cla_set_up_mtu_length_cfg(0x3fff)` — 16383
- `cla_set_dn_mtu_length_cfg(0x3fff)`
- `cla_set_l3_mtu_length_cfg(0x3fff)`

Sub-calls:
- `cla_get_config` / `cla_set_config`
- `cla_set_outspace_cfg`
- `cla_set_oth_l3_pkt_action_cfg`
- 3× `cla_set_*_mtu_length_cfg`
- `api_lock_init()` (decomp:58861) — sets `fast_api_busy_lock=0`,
  `acl_api_lock=0`

In mainline? **unknown — to verify**. Severity 🔴 — MTU regs and
CLA enable bits gate ingress classification.

---

### [fn-06e] `tm_pon_pp_adm_initial` @ decomp_all_tm.c:42771 — ADM (admission) init + protocol limiter

What it does: this is **huge** (~7000 lines of decomp). Sets the ADM
turn-on enable and one-second tick = 200 MHz, then **for each of 2
modes × ~125 protocol types** sets per-protocol packet-limit pps and
priority-map. Goal: program per-protocol-type rate limits and CPU
priority for ~125 packet protocols (ICMP, ARP, IGMP, LLC, BPDU, etc.).

HW writes:
- `adm_set_turnon_enable(1)`
- `adm_set_one_second(200000000)`
- ~10× `tm_protocol_pkt_limit_pps_set(mode, prio, ena, pps)`:
  - mode 0,1 × prio (0,3,4,5,6) — sets pps to 800, 400, 400, 400, 1000
- ~125 × 2 (modes) × 2 (something) iterations of
  `tm_protocol_pkt_limit_map_set(mode, protocol_id, prio_class, sub_mode)`
  — programs which queue/priority each protocol goes to.

(See decomp:42909..43089 for the full mind-numbing list. The
protocol IDs span 0x00..0x7f, the prio_class is 0..7.)

Sub-calls:
- `adm_set_turnon_enable`
- `adm_set_one_second`
- `tm_protocol_pkt_limit_pps_set` × ~10
- `tm_protocol_pkt_limit_map_set` × ~500

In mainline? **unknown — to verify**. Severity 🟡 — protocol pps
limiting and CPU-priority mapping. Without it, CPU could be DoS'd by
high-rate protocol traffic; bridge functions still work though.

---

### [fn-06f] `tm_pon_pp_dpa_initial` @ decomp_all_tm.c:43092 — DPA (deep-packet aly) init

What it does: nested triple loop programs `dpa_set_tpid_i_sel_i(i,
j, k, k, ...)` for i=0..8, j=0..3, k=0..3 (=144 calls). Then enables
protocol-aly for 7 packet types and enables protocol-cpu-pps.

HW writes (via fpga_write_reg through dpa_set_*):
- 144× `dpa_set_tpid_i_sel_i(i, j, k, k)` — sets TPID-select-index
  for each (i,j,k) combo
- 7× `dpa_set_protocol_pkt_aly_en(i, 1)` — enable protocol analysis
  for protocol IDs 0..6
- `dpa_set_protocol_cpu_pps_en(1)`

Sub-calls: `dpa_set_tpid_i_sel_i`, `dpa_set_protocol_pkt_aly_en`,
`dpa_set_protocol_cpu_pps_en`.

In mainline? **unknown — to verify**. Severity 🟡 — DPA is for
deep-packet inspection / per-protocol analysis. Not critical for
bridging.

---

### [fn-06g] `tm_pon_pp_pm_initial` @ decomp_all_tm.c:43133 — PP PerfMon init

What it does: enables padding for PerfMon entries and sets padding
length to 0x1e (30 bytes).

HW writes:
- `pp_pm_cfg_padding_en_set(1)`
- `pp_pm_cfg_padding_len_set(0x1e)`

Sub-calls: 2× pp_pm_cfg_*.

In mainline? **unknown — to verify**. Severity 🟢 — performance
monitoring; not on hot path.

---

## [fn-07] `tm_pon_npp_initial` @ decomp_all_tm.c:43444 — NPP block init

What it does: chains 8 NPP sub-block inits (greg, sdet, sipc, uopc,
sopc, spa, pm, smac) and ORs their return codes.

HW writes: **none directly**.

Sub-calls:
- `tm_pon_npp_greg_initial()` — [fn-07a]
- `tm_pon_npp_sdet_initial()` — [fn-07b]
- `tm_pon_npp_sipc_initial()` — [fn-07c]
- `tm_pon_npp_uopc_initial()` — [fn-07d]
- `tm_pon_npp_sopc_initial()` — [fn-07e]
- `tm_pon_npp_spa_initial()` — [fn-07f]
- `tm_pon_npp_pm_initial()` — [fn-07g]
- `tm_pon_npp_smac_initial()` — [fn-07h]

In mainline? **unknown — to verify**. Severity 🔴 — NPP touches per-
port 802.x auth and port-status (i.e. port admin-up/down). Likely on
hot path.

---

### [fn-07a] `tm_pon_npp_greg_initial` @ decomp_all_tm.c:43150 — port 802.x + status init

What it does: for ports 0..7 (with a special-case to skip from port
5 to port 7), disables 802.x authentication and disables port-status
(port admin-down). Then enables WiFi queue-1 protocol mode.

⚠ The loop has a quirk at `uVar3 == 5`: it does port 6 first (with
authen=0, status=0) and then bumps `uVar3` to 7, so port 5 is
effectively **skipped** for the second pass.

HW writes:
- 8× `tm_port_802x_authen_set(port, 0)` — disable 802.x authen
- 8× `tm_port_status_set(port, 0)` — port admin-down (will be brought
  up by net_open later)
- `greg_set_wifi_queue1_protocol(1)` — WiFi q1 protocol mode = 1

Sub-calls: `tm_port_802x_authen_set`, `tm_port_status_set`,
`greg_set_wifi_queue1_protocol`.

In mainline? **unknown — to verify**. Severity 🟡 — port-status here
sets admin-down; the link is brought up later by net_open. Mainline
needs equivalent.

---

### [fn-07b] `tm_pon_npp_sdet_initial` @ decomp_all_tm.c:43182 — frame-length detector init

What it does: sets max-frame length to 0x3000 (12288 bytes — jumbo
limit) for 5 ports (0..4), min-frame to 0xc (12), down-max-frame to
0x3000.

HW writes:
- 5× `sdet_set_maxframe_length(port, 0x3000)` — 12288
- `sdet_set_minframe_length(0xc)` — 12
- `sdet_set_down_maxframe_length(0x3000)`

Sub-calls: `sdet_set_*`.

In mainline? **unknown — to verify**. Severity 🟡 — frame-size
filter; mis-config could drop legit frames.

---

### [fn-07c] `tm_pon_npp_sipc_initial` @ decomp_all_tm.c:43209 — SIPC init

What it does: enables SIPC RX, disables SIPC CPU-up path.

HW writes:
- `sipc_set_rx_en(1)`
- `sipc_set_cpu_up_en(0)`

Sub-calls: 2× sipc_set_*.

In mainline? **unknown — to verify**. Severity 🟡 — SIPC = stream
IPC; gate for some control path traffic.

---

### [fn-07d] `tm_pon_npp_uopc_initial` @ decomp_all_tm.c:43225 — UOPC tcont count

What it does: sets UOPC tcont count to 4.

HW writes:
- `uopc_set_tcont_num(4)`

Sub-calls: 1.

In mainline? **unknown — to verify**. Severity 🟡 — informs UOPC
about how many TCONTs exist.

---

### [fn-07e] `tm_pon_npp_sopc_initial` @ decomp_all_tm.c:43240 — SOPC init

What it does: disables CRC padding for 5 ports, sets SP-RR cfg to 0.

HW writes:
- 5× `sopc_set_crc_pad_cfg(port, 0)`
- `opc_top_set_sp_rr_cfg(0)` — strict-priority vs RR mode = 0

Sub-calls: 6.

In mainline? **unknown — to verify**. Severity 🟢.

---

### [fn-07f] `tm_pon_npp_spa_initial` @ decomp_all_tm.c:43269 — SPA (stream parser) init

What it does: enables up+dn-direction reg-packet-enable for protocols
0..0x52, enables 802.x trap for ports 1..7, **directly pokes FPGA reg
`0x75015`** to OR-in bits 24-25 (`0x3000000`), sets default-priority to
0 for 8 ports, packet-filter to 0 for 9 ports, sets match-mode=1,
then memcpys a 0x160-byte canonical match-pattern table from
`_LANCHOR1` and pushes it row-by-row to SPA via `spa_set_matchram`.
Also pushes 8 hash-ram rows.

HW writes:
- 0x4e× `spa_set_up_reg_pkt_en(i, 1)` (i=0..0x4d)
- 0x53× `spa_set_dn_reg_pkt_en(i, 1)` (i=0..0x52)
- 7× `spa_set_pt_802x_trap_en(port, 1)` (port=1..7)
- `fpga_read_reg(0x75015)` + `fpga_write_reg(0x75015, val | 0x3000000)`
  — DIRECT poke of FPGA reg `0x75015` to OR-in bits 24-25
- 8× `spa_set_port_dft_pri(port, 0)`
- 9× `spa_set_port_pkt_filter(port, 0)`
- `spa_set_match_mode(1)`
- ~88 rows of `spa_set_matchram(...)` from `_LANCHOR1` table
- 8× `spa_set_hashram(idx, ...)`

Sub-calls: many spa_set_*, `fpga_read_reg`/`fpga_write_reg` direct.

In mainline? **unknown — to verify**. Severity 🔴 — the matchram +
hashram together drive packet classification. Without them, traffic
classifies as "unknown" → may not route correctly.

---

### [fn-07g] `tm_pon_npp_pm_initial` @ decomp_all_tm.c:43374 — NPP PerfMon init

What it does: for 8 ports, disables in-port + out-port rule-valid.
Sets g988 mode for the 3 modes (0→0, 1→1, 2→3). Then calls
`zte_api_set_port_rule` with a default rule, disables g988
"cpu-not-drop-staen", and enables "inport-equal-outport-staen".

HW writes:
- 8× `pm_set_in_port_rule_valid(p, p, 0)`
- 8× `pm_set_out_port_rule_valid(p, p, 0)`
- 3× `pm_set_g988_mode(idx, mode)` — (0,0), (1,1), (2,3)
- `zte_api_set_port_rule(...)` — pushes default rule
- `zte_api_set_g988_cpu_not_drop_staen(0)`
- `zte_api_set_g988_inport_equal_outport_staen(1)`

Sub-calls: pm_set_*, zte_api_set_*.

In mainline? **unknown — to verify**. Severity 🟡 — g988 = TR-156
PON management plane; not used in LAN-up mode.

---

### [fn-07h] `tm_pon_npp_smac_initial` @ decomp_all_tm.c:43422 — SMAC TSF mode

What it does: loops port 0..4 calling `smac_set_tsf_mode(port)` (with
no second arg — looks like a unary helper that sets a default TSF
mode).

HW writes: 5× `smac_set_tsf_mode(port)`.

Sub-calls: 5× smac_set_tsf_mode.

In mainline? **unknown — to verify**. Severity 🟡.

---

## Cross-cut leaf utilities

### [util-A] `tmOnuRegRead` @ decomp_all_tm.c:35337 — table-driven register read

What it does: looks up sub-block `param_1` in the supplied register-
table (e.g., `&smacRegTable`, the various DAT_xxxx ones), validates
the access (mode 1 = read), computes the physical address as
`table[ID].base + port * stride`, then calls
`fpga_read_reg(addr)`, finally masks the value via `(table[ID].mask)
>> (table[ID].shift)`.

Sub-calls: `tmOnuGlbRegValidation` (decomp:35310), `fpga_read_reg`
(imported, decomp:70019 / halt_baddata).

### [util-B] `tmOnuRegWrite` @ decomp_all_tm.c:35356 — table-driven register write

What it does: counterpart to [util-A] with mode 2 = write. Validates,
computes addr, calls `fpga_write_reg(addr, val)`.

Sub-calls: `tmOnuGlbRegValidation`, `fpga_write_reg` (imported,
decomp:69885 / halt_baddata).

### [util-C] `fpga_read_reg` / `fpga_write_reg` — imported from plat-zxylzb_9128S

Both decomp as `halt_baddata()` (see decomp:69885 and decomp:70019)
— these are kernel symbols resolved by plat-zxylzb's
`kallsyms_lookup_name` indirection. They map a sub-block ID + offset
to a register address on TM/PP/NPP/PON_TM bases (which the plat
layer ioremap'd in plat-fn-00).

### [util-D] `__delay(0x66665b0)` — Ghidra-misnamed as `_serdes_set_check_en_open`

As noted in the task brief, calls like `(*_serdes_set_check_en_open)
(0x66665b0)` appearing inside busy loops (e.g., in
`tm_pon_pp_brg_initial` at decomp:43621) are actually `__delay()`
invocations with the `0x66665b0` loops_per_jiffy-equivalent magic.

### [util-E] `__memzero`, `memcpy`, `printk`, `__register_chrdev`,
`bus_find_device_by_name`, `platform_device_register_full`,
`sysfs_create_group`, `kmem_cache_alloc`, `_raw_spin_lock_bh`,
`___ratelimit` — all imported kernel symbols, most decomp as
`halt_baddata` near decomp:69897..70090.

---

## What tm.ko `init_module` does at init time — one-paragraph summary

`tm_initModule` registers the `tm_sample_dev` chardev (major 0xc6) and
the `/sys/devices/platform/tm/*` sysfs tree (10 groups: ppPm, ppCla,
nppGreg, nppPm, nppSdet, nppSpa, nppAdm, ppBrg, red, tmTest), then
initializes the TM SDK in-memory databases (flow-list, NAT-list,
ACL-list, sub-RAM-list via `kmem_cache_alloc`) and wipes 5 MiB of
carved RAM at `0xf1020000` + `0xf1420000` for ACL tables, programming
10 ACL extra-index lookup tables. The bulk of init is `tm_initial`,
which round-trips SMAC per-port config for ports 0..4 (cold-boot
register-coherency dance), then runs three big block bring-ups:
**TM** (queue/DMA/FIFO IRQ masks, gap=4, full RED policy for ~640
queues, QMG cache-mode enable + RAM thresholds, scheduler DWRR/shaper
config for 32 tconts × 8 queues at 1.6 Mbps base, age-mode by board
revision); **PP** (mult-mode, jumbo=2048, PM+ACL base addrs in carved
RAM, 8 TPID slots incl. 802.1ad 0x88a8, SADM accounting with 200 MHz
tick, full L2 bridge init including SMAC-lookup enable + 100x __delay
stat-clean settle + per-port learn/DA/multicast forwarding,
classifier with 0x3fff MTU and api_lock_init, ADM with ~500
per-protocol PPS-limit + priority-map programmings, DPA tpid-select
matrix and 7 protocol analyzers, PerfMon padding); **NPP** (per-port
802.x off + admin-down, frame-detector 12-12288 bytes, SIPC RX
enable, UOPC tcont=4, SOPC, SPA stream-parser including direct FPGA
reg `0x75015` poke and 88-row matchram + 8-row hashram table, NPP
PerfMon with g988-mode and default port rule, SMAC TSF-mode per
port). Net effect: brings the TM/PP/NPP packet-processing pipeline
from cold-reset to "ready to forward L2/L3 with VLAN tagging, MAC
learning, and per-protocol rate limiting", on top of whatever plat-
zxylzb did at chip level.

---

## Walk status

- Top-level `tm_initModule` mapped: **✓** ([fn-00])
- Level-1 (5 callees): documented ([fn-01]..[fn-04] + [fn-02a])
- Level-2 (sub-block inits): documented:
  - SDK: [fn-03a-1] tm_db_init, [fn-03a-2] aclRamInit.part.6
  - TM (4): [fn-05a]..[fn-05d]
  - PP (7): [fn-06a]..[fn-06g]
  - NPP (8): [fn-07a]..[fn-07h]
- Level-3 (concrete RMW helpers): documented for TM-reg init
  ([fn-05a-1..-4]). The other ~30 `sbrg_set_*`, `cla_set_*`,
  `pm_set_*`, `sch_set_*`, `red_set_*`, `spa_set_*` helpers all
  follow the same template — `tmOnuRegWrite` / `fpga_write_reg` with
  the appropriate sub-block ID — and are cited as file:line within
  their parent function's "Sub-calls" list.

**Functions documented**: 35 (8 top-level/wrappers + 27 sub-block
init functions + 5 cross-cut utilities). Plus dozens of leaf helpers
cited by file:line.

**Things I couldn't figure out / open items**:

- The exact bit-field layout that `smac_get_cfg` ⇆ `smac_set_cfg`
  marshal/unmarshal (23 sub-fields packed into one 32-bit word) —
  would need a sister doc to interpret each field by name. Not
  necessary for porting since stock does an identity round-trip.
- `tm_pon_pp_adm_initial`'s ~500-call protocol-PPS table — would be
  better expressed as a data table than enumerated; we recorded the
  shape (mode × protocol-id × prio_class) and a few representative
  values but did not transcribe every entry.
- `tm_pon_npp_spa_initial`'s matchram table at `_LANCHOR1` (0x160
  bytes = 88 rows × 4 bytes? or 22 rows × 16 bytes?) — would need
  Ghidra struct definition to read the constants.
- The actual physical address the sub-block IDs map to. We know
  e.g. TM-reg `0x1` is `pon_tm_set_gap_add`, but we don't know what
  byte offset on the `tm_base` (0x92xxxxxx?) it ends up at — that
  mapping lives inside `fpga_write_reg` in plat-zxylzb_9128S, which
  Ghidra decompiles as halt_baddata.

---

# APPENDIX: Complete function inventory

This appendix catalogs the remaining **1235** functions in `tm.ko` not
covered by the [fn-00..fn-07h] detailed walks above. They are grouped by
functional role. Entry format:

```
- [fn-NNN] `function_name` @ tm.c:LINE — one-line summary
```

Summary heuristics: `setter` / `getter` are inferred from name pattern;
`fpga_write_reg(0xN)` / `tmOnuRegWrite(N)` calls are the first literal-
address sub-block I/O found in the body (most TM SDK helpers wrap one or
more such calls).

## Imported kernel symbols (PLT stubs) (27)

All decomp as `halt_baddata()` — they are kernel symbols resolved at module load time (via `kallsyms_lookup_name` indirection done in plat-zxylzb_9128S). Listed by line only; bodies carry no information.

- [fn-100] `try_module_get` @ tm.c:69617 — imported kernel symbol (PLT stub)
- [fn-101] `serdes_set_rx_prbs_mode` @ tm.c:69629 — imported kernel symbol (PLT stub)
- [fn-102] `gephy_ldo_test` @ tm.c:69641 — imported kernel symbol (PLT stub)
- [fn-103] `__printk_ratelimit` @ tm.c:69653 — imported kernel symbol (PLT stub)
- [fn-104] `kfree` @ tm.c:69678 — imported kernel symbol (PLT stub)
- [fn-105] `_raw_spin_unlock_bh` @ tm.c:69702 — imported kernel symbol (PLT stub)
- [fn-106] `zx_mdio_write` @ tm.c:69714 — imported kernel symbol (PLT stub)
- [fn-107] `hw_watchdog_reset` @ tm.c:69726 — imported kernel symbol (PLT stub)
- [fn-108] `serdes_set_err_cnt_en_open` @ tm.c:69738 — imported kernel symbol (PLT stub)
- [fn-109] `capable` @ tm.c:69762 — imported kernel symbol (PLT stub)
- [fn-110] `module_put` @ tm.c:69774 — imported kernel symbol (PLT stub)
- [fn-111] `serdes_get_err_cnt` @ tm.c:69786 — imported kernel symbol (PLT stub)
- [fn-112] `serdes_set_check_en_open` @ tm.c:69798 — imported kernel symbol (PLT stub)
- [fn-113] `strncpy` @ tm.c:69810 — imported kernel symbol (PLT stub)
- [fn-114] `memcmp` @ tm.c:69823 — imported kernel symbol (PLT stub)
- [fn-115] `sscanf` @ tm.c:69848 — imported kernel symbol (PLT stub)
- [fn-116] `serdes_set_gen_en_open` @ tm.c:69873 — imported kernel symbol (PLT stub)
- [fn-117] `memset` @ tm.c:69897 — imported kernel symbol (PLT stub)
- [fn-118] `serdes_set_check_en_disable` @ tm.c:69910 — imported kernel symbol (PLT stub)
- [fn-119] `serdes_set_err_cnt_en_disable` @ tm.c:69922 — imported kernel symbol (PLT stub)
- [fn-120] `strcmp` @ tm.c:69946 — imported kernel symbol (PLT stub)
- [fn-121] `sysfs_remove_group` @ tm.c:69959 — imported kernel symbol (PLT stub)
- [fn-122] `serdes_set_tx_prbs_mode` @ tm.c:69983 — imported kernel symbol (PLT stub)
- [fn-123] `zx_mdio_read` @ tm.c:70031 — imported kernel symbol (PLT stub)
- [fn-124] `serdes_set_gen_en_disable` @ tm.c:70043 — imported kernel symbol (PLT stub)
- [fn-125] `__copy_from_user` @ tm.c:70067 — imported kernel symbol (PLT stub)
- [fn-126] `__unregister_chrdev` @ tm.c:70079 — imported kernel symbol (PLT stub)

## Sysfs entry handlers (read/write/help/show) (22)

Handlers for `/sys/devices/platform/tm/*` entries. Most use `__copy_from_user` + `sscanf` to parse input and call into the corresponding TM/PP/NPP block helper, then `printk` the result.

- [fn-127] `tm_show_fast_rule_list` @ tm.c:55071 — show
- [fn-128] `tm_show_common_rule_list` @ tm.c:55131 — show
- [fn-129] `pm_info_store` @ tm.c:63538 — ~409 lines body
- [fn-130] `pm_info_show` @ tm.c:63992 — show
- [fn-131] `pm_info_store` @ tm.c:64197 — ~231 lines body
- [fn-132] `pm_info_show` @ tm.c:64745 — show
- [fn-133] `greg_info_store` @ tm.c:64863 — ~107 lines body
- [fn-134] `greg_info_show` @ tm.c:64970 — show
- [fn-135] `sdet_info_store` @ tm.c:65014 — ~39 lines body
- [fn-136] `sdet_info_show` @ tm.c:65053 — show
- [fn-137] `spa_info_store` @ tm.c:65088 — ~274 lines body
- [fn-138] `spa_info_show` @ tm.c:65571 — show, fpga_read_reg(0x750aa)
- [fn-139] `adm_info_show` @ tm.c:65804 — show, printk:" echo [index]                            > sadmpps", fpga_read_reg(0xe5090)
- [fn-140] `adm_info_store` @ tm.c:66071 — ~189 lines body
- [fn-141] `brg_info_store` @ tm.c:66534 — ~326 lines body
- [fn-142] `brg_info_show` @ tm.c:66876 — show, fpga_read_reg(0xe2002)
- [fn-143] `cla_info_store` @ tm.c:67325 — fpga_write_reg(0xe30b0)
- [fn-144] `cla_info_show` @ tm.c:67825 — show, fpga_read_reg(0xe30ee)
- [fn-145] `red_info_store` @ tm.c:68398 — ~311 lines body
- [fn-146] `red_info_show` @ tm.c:68709 — show, fpga_read_reg(0xd1033)
- [fn-147] `tm_test_store` @ tm.c:68848 — ~398 lines body
- [fn-148] `tm_test_show` @ tm.c:69246 — show

## Diagnostic / dump / show / help functions (11)

Read-only debug surfaces; mostly emit register state via `printk`. Not on packet path.

- [fn-149] `showFlowInfoTest` @ tm.c:159 — show
- [fn-150] `tm_show_list` @ tm.c:54047 — show
- [fn-151] `tm_show_acl_list` @ tm.c:54110 — show
- [fn-152] `tm_show_acl_rule_entry` @ tm.c:54296 — show, printk:"ActionInfo:"
- [fn-153] `tm_acl_showhashCount` @ tm.c:54557 — ~19 lines body
- [fn-154] `tm_show_common_rule_list_detail` @ tm.c:60009 — show
- [fn-155] `tm_show_common_rule_config_list` @ tm.c:60724 — show
- [fn-156] `tm_show_one_common_rule_config` @ tm.c:60743 — show
- [fn-157] `tm_show_fast_rule_list_detail` @ tm.c:63455 — show
- [fn-158] `pmDebugShowCmdInfo` @ tm.c:63509 — ~29 lines body
- [fn-159] `pmDebugShowPmResult` @ tm.c:63947 — printk:"%02x "

## zte_api_* — exported TM SDK API (called from switch.ko) (95)

These are the function-pointer-table entries used by switch.ko, ppd / cspd, and the WiFi binding stubs to drive the TM block from other kernel modules.

- [fn-160] `zte_api_sw_get_wlan_port` @ tm.c:54864 — getter
- [fn-161] `zte_api_sw_port_set_port_multiprorate` @ tm.c:54875 — setter
- [fn-162] `zte_api_sw_qos_get_port_streamselect` @ tm.c:54884 — getter
- [fn-163] `zte_api_sw_fast_entry_policy` @ tm.c:54895 — ~14 lines body
- [fn-164] `zte_api_sw_get_fast_max_entry` @ tm.c:54909 — getter
- [fn-165] `zte_api_set_debuglevel` @ tm.c:54927 — setter
- [fn-166] `zte_api_sw_get_pon_port` @ tm.c:54937 — getter
- [fn-167] `zte_api_sw_set_l2fast_opti` @ tm.c:54958 — setter
- [fn-168] `zte_api_sw_port_get_port_mirror` @ tm.c:54968 — getter, fpga_read_reg(0xe8131)
- [fn-169] `zte_api_sw_set_fast_max_entry` @ tm.c:55224 — setter
- [fn-170] `zte_api_sw_port_set_port_mirror` @ tm.c:55240 — setter, fpga_write_reg(0xe8131)
- [fn-171] `zte_api_pp_set_pro_action` @ tm.c:55387 — setter
- [fn-172] `zte_api_sw_set_port_muticast` @ tm.c:55866 — setter
- [fn-173] `zte_api_sw_port_init` @ tm.c:55891 — ~45 lines body
- [fn-174] `zte_api_sw_vlan_set_port_inframemode` @ tm.c:55936 — setter
- [fn-175] `zte_api_sw_port_get_port_loopback` @ tm.c:55984 — getter
- [fn-176] `zte_api_sw_phy_read` @ tm.c:56006 — ~13 lines body
- [fn-177] `zte_api_sw_port_set_port_loopback` @ tm.c:56019 — setter
- [fn-178] `zte_api_sw_phy_write` @ tm.c:56042 — ~12 lines body
- [fn-179] `zte_api_sw_port_set_port_floodcontrolmask` @ tm.c:56054 — setter
- [fn-180] `zte_api_sw_port_clear_port_count` @ tm.c:56081 — ~35 lines body
- [fn-181] `zte_api_sw_port_clear_count_by_portid` @ tm.c:56116 — ~27 lines body
- [fn-182] `zte_api_sw_mac_add_port_macaddress` @ tm.c:56143 — ~72 lines body
- [fn-183] `zte_api_sw_mac_del_port_macaddress` @ tm.c:56215 — ~91 lines body
- [fn-184] `zte_api_sw_mac_add_port_macfilterentry` @ tm.c:56306 — ~91 lines body
- [fn-185] `zte_api_sw_mac_set_onu_proaction` @ tm.c:56397 — setter
- [fn-186] `zte_api_sw_other_set_onu_mtu` @ tm.c:56472 — setter, fpga_write_reg(0x34001)
- [fn-187] `zte_api_sw_port_rx_pause_count_open` @ tm.c:56504 — ~23 lines body
- [fn-188] `zte_api_sw_port_get_port_statistics1` @ tm.c:56527 — getter
- [fn-189] `zte_api_sw_port_get_port_statistics2` @ tm.c:56624 — getter
- [fn-190] `zte_api_sw_port_get_port_statistics3` @ tm.c:56698 — getter
- [fn-191] `zte_api_sw_port_get_port_statistics4` @ tm.c:56785 — getter
- [fn-192] `zte_api_sw_port_set_port_ratelimit` @ tm.c:56862 — setter
- [fn-193] `zte_api_sw_port_get_port_ratelimit` @ tm.c:56941 — getter
- [fn-194] `zte_api_sw_port_set_port_multicastrate` @ tm.c:57014 — setter
- [fn-195] `zte_api_sw_port_set_port_broadcastrate` @ tm.c:57060 — setter
- [fn-196] `zte_api_sw_port_get_port_multicastrate` @ tm.c:57106 — getter
- [fn-197] `zte_api_sw_port_get_port_broadcastrate` @ tm.c:57143 — getter
- [fn-198] `zte_api_sw_qos_set_port_schedule` @ tm.c:57179 — setter
- [fn-199] `zte_api_sw_qos_get_port_schedule` @ tm.c:57199 — getter
- [fn-200] `zte_api_sw_set_mac_ratelimit` @ tm.c:57215 — setter, fpga_write_reg(0xe1005)
- [fn-201] `zte_api_fast_l3_session_clr` @ tm.c:57322 — ~36 lines body
- [fn-202] `zte_api_fast_l3_session_use` @ tm.c:57358 — ~38 lines body
- [fn-203] `zte_api_fast_l3_session_stat` @ tm.c:57396 — ~48 lines body
- [fn-204] `zte_api_set_6rd_sip` @ tm.c:57444 — setter, tmOnuRegWrite(0x14)
- [fn-205] `zte_api_get_6rd_sip` @ tm.c:57475 — getter, tmOnuRegRead(0x14)
- [fn-206] `zte_api_pp_set_cpu_queue_rate` @ tm.c:57522 — setter
- [fn-207] `zte_api_sw_set_cla_other_l3pkt_action` @ tm.c:57563 — setter
- [fn-208] `zte_api_sw_set_qnum_map_mode` @ tm.c:57578 — setter, printk:"ERROR:(%s:%d)"
- [fn-209] `zte_api_sw_get_qnum_map_mode` @ tm.c:57605 — getter, printk:"ERROR:(%s:%d)"
- [fn-210] `zte_api_sw_set_sbrg_pri_qtab_pon` @ tm.c:57632 — setter, printk:"ERROR:(%s:%d)"
- [fn-211] `zte_api_sw_get_sbrg_pri_qtab_pon` @ tm.c:57660 — getter, printk:"ERROR:(%s:%d)"
- [fn-212] `zte_api_set_g988_cpu_not_drop_staen` @ tm.c:57688 — setter
- [fn-213] `zte_api_set_g988_inport_equal_outport_staen` @ tm.c:57700 — setter
- [fn-214] `zte_api_sw_qos_get_availbktid` @ tm.c:57712 — getter
- [fn-215] `zte_api_sw_set_dmac_ratelimit_en` @ tm.c:57760 — setter, fpga_write_reg(0xe10a1)
- [fn-216] `zte_api_pp_set_pro_en` @ tm.c:57852 — setter
- [fn-217] `zte_api_pp_set_trap_queue` @ tm.c:57882 — setter
- [fn-218] `zte_api_pp_global_init` @ tm.c:57956 — printk:"ERROR:(%s:%d)"
- [fn-219] `zte_api_sw_set_port_brdcast` @ tm.c:57999 — setter
- [fn-220] `zte_api_sw_set_port_unicast` @ tm.c:58023 — setter
- [fn-221] `zte_api_sw_set_muti2uni` @ tm.c:58049 — setter
- [fn-222] `zte_api_sw_vlan_get_port_inframemode` @ tm.c:58076 — getter
- [fn-223] `zte_api_sw_vlan_set_port_pvid` @ tm.c:58115 — setter
- [fn-224] `zte_api_sw_vlan_get_port_pvid` @ tm.c:58140 — getter
- [fn-225] `zte_api_sw_vlan_set_port_vlancfg` @ tm.c:58164 — setter
- [fn-226] `zte_api_sw_vlan_get_port_vlancfg` @ tm.c:58196 — getter
- [fn-227] `zte_api_sw_port_get_port_enable` @ tm.c:58249 — getter
- [fn-228] `zte_api_sw_port_get_port_linkmode` @ tm.c:58280 — getter
- [fn-229] `zte_api_sw_port_get_port_linkstate` @ tm.c:58330 — getter
- [fn-230] `zte_api_sw_port_set_port_enable` @ tm.c:58375 — setter
- [fn-231] `zte_api_sw_port_set_port_linkmode` @ tm.c:58415 — setter
- [fn-232] `zte_api_sw_port_set_port_flowcontrol` @ tm.c:58443 — setter
- [fn-233] `zte_api_sw_port_get_port_flowcontrol` @ tm.c:58464 — getter
- [fn-234] `zte_api_sw_port_set_port_isolatemask` @ tm.c:58480 — setter
- [fn-235] `zte_api_sw_mac_set_onu_agingtime` @ tm.c:58496 — setter
- [fn-236] `zte_api_sw_mac_get_onu_agingtime` @ tm.c:58512 — getter
- [fn-237] `zte_api_sw_mac_set_port_learnlimit` @ tm.c:58528 — setter
- [fn-238] `zte_api_sw_mac_get_port_learnlimit` @ tm.c:58544 — getter
- [fn-239] `zte_api_sw_mac_clear_macaddress` @ tm.c:58560 — ~16 lines body
- [fn-240] `zte_api_sw_mac_clear_port_mactable` @ tm.c:58576 — ~19 lines body
- [fn-241] `zte_api_sw_mac_set_port_macfiltermode` @ tm.c:58595 — setter
- [fn-242] `zte_api_sw_mac_del_port_macfilterentry` @ tm.c:58636 — ~30 lines body
- [fn-243] `zte_api_sw_mac_set_onu_stpaction` @ tm.c:58666 — setter
- [fn-244] `zte_api_set_g988_rule` @ tm.c:58710 — setter
- [fn-245] `zte_api_get_g988_statistics` @ tm.c:58759 — getter
- [fn-246] `zte_api_set_zte_rule` @ tm.c:58809 — setter
- [fn-247] `zte_api_get_zte_statistics` @ tm.c:58828 — getter
- [fn-248] `zte_api_sw_global_init` @ tm.c:58900 — ~85 lines body
- [fn-249] `zte_api_fast_l3_session_add` @ tm.c:59030 — ~936 lines body
- [fn-250] `zte_api_fast_l3_session_del` @ tm.c:59966 — ~43 lines body
- [fn-251] `zte_api_cla_show_aclrule` @ tm.c:62986 — show
- [fn-252] `zte_api_sw_qos_add_port_streamselect` @ tm.c:63181 — ~158 lines body
- [fn-253] `zte_api_sw_qos_del_port_streamselect` @ tm.c:63339 — ~116 lines body
- [fn-254] `zte_api_sw_port_set_port_ratelimit_clr` @ tm.c:63479 — setter

## ACL / CLA / classifier / flow helpers (125)

Classifier (CLA) configuration, ACL rule manipulation, hash-table fast-path helpers, flow-tuple operations, aging tables.

- [fn-255] `addAclRuleTest` @ tm.c:169 — ~14 lines body
- [fn-256] `addAclRuleTestExtern` @ tm.c:183 — ~9 lines body
- [fn-257] `delAclRuleTest` @ tm.c:192 — ~10 lines body
- [fn-258] `tmAclTestMain` @ tm.c:202 — ~96 lines body
- [fn-259] `cla_set_indirect_rw_cmd` @ tm.c:298 — setter, tmOnuRegWrite(0)
- [fn-260] `cla_get_indirect_rw_status` @ tm.c:336 — getter, tmOnuRegRead(1)
- [fn-261] `cla_set_indirect_rw_data` @ tm.c:365 — setter, tmOnuRegWrite(2)
- [fn-262] `cla_get_indirect_rw_data` @ tm.c:394 — getter, tmOnuRegRead(2)
- [fn-263] `cla_set_trap_acl_en_config` @ tm.c:533 — setter, tmOnuRegWrite(4)
- [fn-264] `cla_set_mac_req_ctrl_config` @ tm.c:564 — setter, tmOnuRegWrite(5)
- [fn-265] `cla_set_l3_mtu_length_cfg` @ tm.c:595 — setter, tmOnuRegWrite(6)
- [fn-266] `cla_get_l3_mtu_length_cfg` @ tm.c:626 — getter, tmOnuRegRead(6)
- [fn-267] `cla_set_l3_mtu_act_cfg` @ tm.c:654 — setter, tmOnuRegWrite(7)
- [fn-268] `cla_set_port_mirror_flow_ctrl_config` @ tm.c:683 — setter
- [fn-269] `cla_get_port_mirror_flow_ctrl_config` @ tm.c:721 — getter
- [fn-270] `cla_set_hash_poly_config` @ tm.c:762 — setter, tmOnuRegWrite(0xc)
- [fn-271] `cla_get_hash_poly_config` @ tm.c:805 — getter, tmOnuRegRead(0xc)
- [fn-272] `cla_set_up_mtu_length_cfg` @ tm.c:916 — setter, tmOnuRegWrite(0xe)
- [fn-273] `cla_get_up_mtu_length_cfg` @ tm.c:945 — getter, tmOnuRegRead(0xe)
- [fn-274] `cla_set_up_mtu_act_cfg` @ tm.c:973 — setter, tmOnuRegWrite(0xf)
- [fn-275] `cla_set_dn_mtu_length_cfg` @ tm.c:1002 — setter, tmOnuRegWrite(0x10)
- [fn-276] `cla_get_dn_mtu_length_cfg` @ tm.c:1031 — getter, tmOnuRegRead(0x10)
- [fn-277] `cla_set_dn_mtu_act_cfg` @ tm.c:1059 — setter, tmOnuRegWrite(0x11)
- [fn-278] `cla_set_local_ipv4_addr` @ tm.c:1088 — setter, tmOnuRegWrite(0x12)
- [fn-279] `cla_get_local_ipv4_addr` @ tm.c:1112 — getter, tmOnuRegRead(0x12)
- [fn-280] `cla_set_local_ipv6_addr` @ tm.c:1141 — setter, tmOnuRegWrite(0x13)
- [fn-281] `cla_get_local_ipv6_addr` @ tm.c:1171 — getter, tmOnuRegRead(0x13)
- [fn-282] `cla_set_ttl_over_action_cfg` @ tm.c:1212 — setter, tmOnuRegWrite(0x14)
- [fn-283] `cla_get_ttl_over_action_cfg` @ tm.c:1243 — getter, tmOnuRegRead(0x14)
- [fn-284] `cla_get_oth_l3_pkt_action_cfg` @ tm.c:1303 — getter, tmOnuRegRead(0x15)
- [fn-285] `cla_set_dn_unknown_da_action_cfg` @ tm.c:1332 — setter, tmOnuRegWrite(0x16)
- [fn-286] `cla_get_dn_unknown_da_action_cfg` @ tm.c:1364 — getter, tmOnuRegRead(0x16)
- [fn-287] `cla_set_up_l2_uni_default_flow_cfg` @ tm.c:1393 — setter, tmOnuRegWrite(0x17)
- [fn-288] `cla_get_up_l2_uni_default_flow_cfg` @ tm.c:1445 — getter, tmOnuRegRead(0x17)
- [fn-289] `cla_set_dn_l2_default_flow_cfg` @ tm.c:1505 — setter, tmOnuRegWrite(0x1a)
- [fn-290] `cla_get_dn_l2_default_flow_cfg` @ tm.c:1552 — getter, tmOnuRegRead(0x1a)
- [fn-291] `cla_set_up_l3_default_flow_cfg` @ tm.c:1608 — setter, tmOnuRegWrite(0x1e)
- [fn-292] `cla_get_up_l3_default_flow_cfg` @ tm.c:1653 — getter, tmOnuRegRead(0x1e)
- [fn-293] `cla_set_dn_l3_default_flow_cfg` @ tm.c:1701 — setter, tmOnuRegWrite(0x21)
- [fn-294] `cla_get_dn_l3_default_flow_cfg` @ tm.c:1748 — getter, tmOnuRegRead(0x21)
- [fn-295] `cla_set_up_mirror_cfg` @ tm.c:1804 — setter, tmOnuRegWrite(0x25)
- [fn-296] `cla_get_up_mirror_cfg` @ tm.c:1842 — getter, tmOnuRegRead(0x25)
- [fn-297] `cla_set_dn_multi_flow_cfg` @ tm.c:1890 — setter, tmOnuRegWrite(0x26)
- [fn-298] `cla_get_dn_multi_flow_cfg` @ tm.c:1936 — getter, tmOnuRegRead(0x26)
- [fn-299] `cla_set_dn_broad_flow_cfg` @ tm.c:1992 — setter, tmOnuRegWrite(0x2a)
- [fn-300] `cla_get_dn_broad_flow_cfg` @ tm.c:2038 — getter, tmOnuRegRead(0x2a)
- [fn-301] `cla_set_up_unicast_flow_cfg` @ tm.c:2094 — setter, tmOnuRegWrite(0x2e)
- [fn-302] `cla_get_up_unicast_flow_cfg` @ tm.c:2139 — getter, tmOnuRegRead(0x2e)
- [fn-303] `cla_set_dn_unicast_flow_cfg` @ tm.c:2187 — setter, tmOnuRegWrite(0x31)
- [fn-304] `cla_get_dn_unicast_flow_cfg` @ tm.c:2234 — getter, tmOnuRegRead(0x31)
- [fn-305] `cla_set_dn_unknown_flow_cfg` @ tm.c:2290 — setter, tmOnuRegWrite(0x35)
- [fn-306] `cla_get_dn_unknown_flow_cfg` @ tm.c:2335 — getter, tmOnuRegRead(0x35)
- [fn-307] `cla_set_dn_mirror_cfg` @ tm.c:2391 — setter, tmOnuRegWrite(0x39)
- [fn-308] `cla_get_dn_mirror_cfg` @ tm.c:2428 — getter, tmOnuRegRead(0x39)
- [fn-309] `cla_set_def_qos_info_cfg` @ tm.c:2464 — setter, tmOnuRegWrite(0x3a)
- [fn-310] `cla_get_def_qos_info_cfg` @ tm.c:2498 — getter, tmOnuRegRead(0x3a)
- [fn-311] `cla_set_up_default_bucket_id_cfg` @ tm.c:2528 — setter, tmOnuRegWrite(0x3c)
- [fn-312] `cla_get_up_default_bucket_id_cfg` @ tm.c:2560 — getter, tmOnuRegRead(0x3c)
- [fn-313] `cla_set_dn_default_bucket_id_cfg` @ tm.c:2589 — setter, tmOnuRegWrite(0x3b)
- [fn-314] `cla_get_dn_default_bucket_id_cfg` @ tm.c:2621 — getter, tmOnuRegRead(0x3b)
- [fn-315] `cla_get_extra_index_table` @ tm.c:2742 — getter
- [fn-316] `cla_set_extra_rule_table` @ tm.c:2870 — setter
- [fn-317] `cla_get_extra_rule_table` @ tm.c:3094 — getter
- [fn-318] `cla_set_hash_table` @ tm.c:3366 — setter
- [fn-319] `cla_get_hash_table` @ tm.c:3553 — getter
- [fn-320] `cla_set_external_hash_table` @ tm.c:3792 — setter
- [fn-321] `cla_get_external_hash_table` @ tm.c:3839 — getter
- [fn-322] `cla_set_cpu_queue_id` @ tm.c:3957 — setter
- [fn-323] `cla_get_cpu_queue_id` @ tm.c:4025 — getter
- [fn-324] `cla_acl_hash_addr_gen` @ tm.c:4154 — ~117 lines body
- [fn-325] `cla_list_hash_addr_gen` @ tm.c:4271 — ~23 lines body
- [fn-326] `cla_set_acl_aging_table` @ tm.c:4294 — setter
- [fn-327] `cla_get_acl_aging_table` @ tm.c:4367 — getter
- [fn-328] `cla_set_acl_dscp_tc_qid_table` @ tm.c:4447 — setter
- [fn-329] `cla_get_acl_dscp_tc_qid_table` @ tm.c:4520 — getter
- [fn-330] `tm_flow_rate_limit_ena_set` @ tm.c:35752 — setter
- [fn-331] `tm_soft_protocol_dmac_set` @ tm.c:36717 — setter
- [fn-332] `tm_soft_protocol_dmac_get` @ tm.c:36764 — getter
- [fn-333] `tm_soft_protocol_ethtype_set` @ tm.c:36813 — setter
- [fn-334] `tm_soft_protocol_ethtype_get` @ tm.c:36856 — getter
- [fn-335] `tm_flow_rate_limit_ena_get` @ tm.c:40854 — getter
- [fn-336] `tm_flow_rate_limit_get` @ tm.c:40877 — getter
- [fn-337] `tm_flow_rate_limit_set` @ tm.c:45496 — setter
- [fn-338] `tm_soft_protocol_iptype_set` @ tm.c:46044 — setter
- [fn-339] `tm_soft_protocol_iptype_get` @ tm.c:46087 — getter
- [fn-340] `tm_cla_acl_aging_table_set` @ tm.c:46865 — setter, printk:"ERROR:(%s:%d)"
- [fn-341] `tm_cla_acl_aging_table_get` @ tm.c:46884 — getter, printk:"ERROR:(%s:%d)"
- [fn-342] `opcDbSetCrtList` @ tm.c:48093 — ~20 lines body
- [fn-343] `opcDbCmdEntryValidSet` @ tm.c:48113 — printk:"ERROR:the index %d of cmd entry isnot exist"
- [fn-344] `aclWlanToIdmReset` @ tm.c:48165 — ~22 lines body
- [fn-345] `opcDbQosEntryValidSet` @ tm.c:48187 — printk:"ERROR:the index %d of qos entry isnot exist"
- [fn-346] `opcDbNatEntryValidSet` @ tm.c:48246 — printk:"ERROR:the index %d of nat entry isnot exist"
- [fn-347] `opcDbVlanEntryValidSet` @ tm.c:48306 — printk:"ERROR:the index %d of vlan entry isnot exist"
- [fn-348] `opcDbSubRamEntryValidSet` @ tm.c:48366 — printk:"ERROR:the index %d of modify entry isnot exist"
- [fn-349] `aclBuildExtRuleAndHashEntriesByParseCondition` @ tm.c:48424 — printk:"ERROR:(%s:%d)"
- [fn-350] `tm_acl_get_fastHashRule` @ tm.c:49213 — getter, printk:"ERROR:(%s:%d)"
- [fn-351] `opcDbFlowEntryValidSet` @ tm.c:49491 — printk:"ERROR:the index %d of flow entry isnot exist"
- [fn-352] `operInfoDel` @ tm.c:49579 — printk:"ERROR:del flowId %d exceed 512"
- [fn-353] `EN_V4FAST_EXTIDXTBL` @ tm.c:49717 — ~34 lines body
- [fn-354] `EN_V6FAST_EXTIDXTBL` @ tm.c:49751 — ~34 lines body
- [fn-355] `tm_acl_l2_fast_init` @ tm.c:49785 — ~99 lines body
- [fn-356] `delAclRule` @ tm.c:49884 — ~174 lines body
- [fn-357] `aclWLANToIDMEssidCfg` @ tm.c:50058 — ~25 lines body
- [fn-358] `aclWLANToIDMEssidMap` @ tm.c:50083 — ~20 lines body
- [fn-359] `aclEssidToWlanIDMMap` @ tm.c:50103 — ~34 lines body
- [fn-360] `aclGetExtIdxRuleRamAddrByPort` @ tm.c:50137 — printk:"ERROR:(%s:%d)"
- [fn-361] `aclWLANToIDMEssidCfg2` @ tm.c:50175 — ~19 lines body
- [fn-362] `aclEssidToWlanIDMMap2` @ tm.c:50194 — ~36 lines body
- [fn-363] `operInfoAdd` @ tm.c:50419 — printk:"ERROR:(%s:%d)"
- [fn-364] `aclGetAvailableHashAddr.constprop.13` @ tm.c:52341 — printk:"ERROR:(%s:%d)"
- [fn-365] `tm_acl_fast_add_v4v6` @ tm.c:52521 — printk:"ERROR:(%s:%d)"
- [fn-366] `aclBuildHashAndAclRule` @ tm.c:52917 — printk:"ERROR:(%s:%d)"
- [fn-367] `addAclRule` @ tm.c:53798 — printk:"ERROR:(%s:%d)"
- [fn-368] `tm_acl_fast_add` @ tm.c:54225 — ~36 lines body
- [fn-369] `aclRamInit` @ tm.c:54784 — ~15 lines body
- [fn-370] `tm_acl_setMtchInfo` @ tm.c:55152 — ~72 lines body
- [fn-371] `tm_delete_fast_rule_node` @ tm.c:57290 — ~32 lines body
- [fn-372] `tm_findFastIdxByTuple` @ tm.c:58985 — ~45 lines body
- [fn-373] `tm_acl_check_matchfiled` @ tm.c:62835 — ~78 lines body
- [fn-374] `tm_acl_find_filter` @ tm.c:62913 — ~73 lines body
- [fn-375] `tm_acl_add_rule_node` @ tm.c:63011 — ~83 lines body
- [fn-376] `tm_acl_delete_rule_node` @ tm.c:63094 — ~61 lines body
- [fn-377] `tm_acl_free_match_filter` @ tm.c:63155 — ~26 lines body
- [fn-378] `claDebugAddFastRule` @ tm.c:69450 — ~128 lines body
- [fn-379] `claDebugDelFastRule` @ tm.c:69578 — ~39 lines body

## PerfMon counters (pp_pm / npp_pm / pm_*) (94)

PerfMon block accessors — programs counter rules, reads back stats for `/sys/devices/platform/tm/ppPm` and `/nppPm`. Not on packet path.

- [fn-380] `pon_pp_get_pm_base_addr` @ tm.c:16205 — getter, tmOnuRegRead(0xe)
- [fn-381] `pp_pm_set_indirect_cmd` @ tm.c:18079 — setter, tmOnuRegWrite(0)
- [fn-382] `pp_pm_get_indirect_cmd` @ tm.c:18117 — getter, tmOnuRegRead(0)
- [fn-383] `pp_pm_ind_acc_done_get` @ tm.c:18149 — getter, tmOnuRegRead(1)
- [fn-384] `pp_pm_ind_acc_data_set` @ tm.c:18172 — setter, tmOnuRegWrite(2)
- [fn-385] `pp_pm_ind_acc_data_get` @ tm.c:18203 — getter, tmOnuRegRead(2)
- [fn-386] `pp_pm_cfg_padding_en_set` @ tm.c:18242 — setter, tmOnuRegWrite(5)
- [fn-387] `pp_pm_cfg_padding_en_get` @ tm.c:18269 — getter, tmOnuRegRead(5)
- [fn-388] `pp_pm_cfg_padding_len_set` @ tm.c:18290 — setter, tmOnuRegWrite(4)
- [fn-389] `pp_pm_cfg_padding_len_get` @ tm.c:18317 — getter, tmOnuRegRead(4)
- [fn-390] `pp_pm_set_flow_info` @ tm.c:18338 — setter
- [fn-391] `pp_pm_get_flow_info` @ tm.c:18426 — getter
- [fn-392] `pp_pm_set_external_flow_info` @ tm.c:18533 — setter
- [fn-393] `pp_pm_get_external_flow_info` @ tm.c:18575 — getter
- [fn-394] `pp_pm_set_next_hop_ram_info` @ tm.c:18621 — setter
- [fn-395] `pp_pm_get_next_hop_ram_info` @ tm.c:18721 — getter
- [fn-396] `pp_pm_set_vlan_modify_ram_info` @ tm.c:18820 — setter
- [fn-397] `pp_pm_get_vlan_modify_ram_info` @ tm.c:18892 — getter
- [fn-398] `pp_pm_get_cmd_ram_info` @ tm.c:18974 — getter
- [fn-399] `pp_pm_set_cmd_ram_info` @ tm.c:19044 — setter
- [fn-400] `pp_pm_set_e8_qos_info` @ tm.c:19125 — setter
- [fn-401] `pp_pm_get_e8_qos_info` @ tm.c:19188 — getter
- [fn-402] `pp_pm_set_modify_ram_info` @ tm.c:19270 — setter
- [fn-403] `pp_pm_get_modify_ram_info` @ tm.c:19331 — getter
- [fn-404] `pp_pm_set_sub_ram_info` @ tm.c:19411 — setter
- [fn-405] `pp_pm_get_sub_ram_info` @ tm.c:19490 — getter
- [fn-406] `pp_pm_set_pri_ram_info` @ tm.c:19583 — setter
- [fn-407] `pp_pm_get_pri_ram_info` @ tm.c:19655 — getter
- [fn-408] `pp_pm_set_v6rd_cmd_info` @ tm.c:19748 — setter
- [fn-409] `pp_pm_get_v6rd_cmd_info` @ tm.c:19810 — getter
- [fn-410] `pp_pm_set_pppoe_session_id_ram_info` @ tm.c:19887 — setter
- [fn-411] `pp_pm_get_pppoe_session_id_ram_info` @ tm.c:19946 — getter
- [fn-412] `pp_pm_set_b4_ipv6_ram_info` @ tm.c:20026 — setter
- [fn-413] `pp_pm_get_b4_ipv6_ram_info` @ tm.c:20094 — getter
- [fn-414] `pp_pm_set_aftr_ipv6_ram_info` @ tm.c:20171 — setter
- [fn-415] `pp_pm_get_aftr_ipv6_ram_info` @ tm.c:20239 — getter
- [fn-416] `pp_pm_set_onu_mac_ram_info` @ tm.c:20316 — setter
- [fn-417] `pp_pm_get_onu_mac_ram_info` @ tm.c:20390 — getter
- [fn-418] `pp_pm_get_diag_ram_info` @ tm.c:20475 — getter
- [fn-419] `greg_set_nppu_pm_ram_init` @ tm.c:22140 — setter, tmOnuRegWrite(0x1c)
- [fn-420] `pm_set_indirect_rw_cmd` @ tm.c:22695 — setter, tmOnuRegWrite(0)
- [fn-421] `pm_get_indirect_rw_status` @ tm.c:22733 — getter, tmOnuRegRead(1)
- [fn-422] `pm_get_indirect_rw_data` @ tm.c:22761 — getter, tmOnuRegRead(2)
- [fn-423] `pm_get_indirect_data` @ tm.c:22799 — getter
- [fn-424] `pm_set_g988_mode` @ tm.c:22909 — setter, tmOnuRegWrite(3)
- [fn-425] `pm_set_g988_cpu_drop_staen` @ tm.c:22955 — setter, tmOnuRegWrite(4)
- [fn-426] `pm_set_g988_cpu_not_drop_staen` @ tm.c:22989 — setter, tmOnuRegWrite(5)
- [fn-427] `pm_set_g988_inport_equal_outport_staen` @ tm.c:23024 — setter, tmOnuRegWrite(0x10)
- [fn-428] `pm_set_in_port_rule_valid` @ tm.c:23059 — setter, tmOnuRegWrite(6)
- [fn-429] `pm_get_in_port_rule_valid` @ tm.c:23106 — getter, tmOnuRegRead(6)
- [fn-430] `pm_set_out_port_rule_valid` @ tm.c:23145 — setter, tmOnuRegWrite(7)
- [fn-431] `pm_get_out_port_rule_valid` @ tm.c:23192 — getter, tmOnuRegRead(7)
- [fn-432] `pm_set_flow_sta_en` @ tm.c:23231 — setter, tmOnuRegWrite(8)
- [fn-433] `pm_get_flow_sta_en` @ tm.c:23263 — getter, tmOnuRegRead(8)
- [fn-434] `pm_set_flow_sta_pkt_len_sel` @ tm.c:23284 — setter, tmOnuRegWrite(9)
- [fn-435] `pm_set_flow_sta_read_clear_en` @ tm.c:23318 — setter, tmOnuRegWrite(10)
- [fn-436] `pm_set_flow_sta_cnt_mode` @ tm.c:23352 — setter, tmOnuRegWrite(0xb)
- [fn-437] `pm_set_flow_sta_fwd_only_en` @ tm.c:23386 — setter, tmOnuRegWrite(0xc)
- [fn-438] `pm_set_port_cfg` @ tm.c:23420 — setter
- [fn-439] `pm_get_port_cfg` @ tm.c:23452 — getter
- [fn-440] `pm_get_port_statistics_cfg` @ tm.c:23493 — getter
- [fn-441] `pm_check_g988_rule` @ tm.c:23579 — ~37 lines body
- [fn-442] `pm_add_g988_rule` @ tm.c:23616 — tmOnuRegWrite(0xd)
- [fn-443] `pm_select_g988_reg` @ tm.c:23641 — tmOnuRegWrite(0xd), tmOnuRegRead(0xd)
- [fn-444] `pm_set_g988_cfg` @ tm.c:23720 — setter
- [fn-445] `pm_get_g988_cfg` @ tm.c:23767 — getter
- [fn-446] `pm_get_g988_statistics_cfg` @ tm.c:23819 — getter
- [fn-447] `pm_select_zte_reg` @ tm.c:23893 — tmOnuRegWrite(0xe), tmOnuRegRead(0xe)
- [fn-448] `pm_set_zte_cfg` @ tm.c:23982 — setter
- [fn-449] `pm_get_zte_cfg` @ tm.c:24014 — getter
- [fn-450] `pm_get_zte_statistics_cfg` @ tm.c:24046 — getter
- [fn-451] `pm_set_flow_cfg` @ tm.c:24137 — setter
- [fn-452] `pm_get_flow_statistics_cfg` @ tm.c:24168 — getter
- [fn-453] `pm_get_port_statistics` @ tm.c:24199 — getter
- [fn-454] `pm_get_g988_index_cfg` @ tm.c:24273 — getter, tmOnuRegRead(0xd)
- [fn-455] `pm_get_g988_statistics` @ tm.c:24297 — getter
- [fn-456] `pm_get_zte_index_cfg` @ tm.c:24363 — getter, tmOnuRegRead(0xe)
- [fn-457] `pm_get_zte_statistics` @ tm.c:24392 — getter
- [fn-458] `tm_pm_flow_rule_set` @ tm.c:42257 — setter
- [fn-459] `tm_pm_flow_sta_en_set` @ tm.c:42289 — setter
- [fn-460] `tm_pm_flow_statistics_get` @ tm.c:42308 — getter
- [fn-461] `tm_pm_port_statistics_get.part.46` @ tm.c:42436 — ~12 lines body
- [fn-462] `tm_pm_port_get` @ tm.c:47640 — getter
- [fn-463] `tm_pm_port_rule_set` @ tm.c:47677 — setter
- [fn-464] `tm_pm_port_statistics_get` @ tm.c:47707 — getter
- [fn-465] `tm_pm_g988_rule_set` @ tm.c:47747 — setter
- [fn-466] `tm_pm_g988_statistics_get` @ tm.c:47803 — getter
- [fn-467] `tm_pm_zte_rule_set` @ tm.c:47893 — setter
- [fn-468] `tm_pm_zte_statistics_get` @ tm.c:47927 — getter
- [fn-469] `sw_get_pm_overflow` @ tm.c:54820 — getter
- [fn-470] `pm_port_name_get` @ tm.c:64160 — getter
- [fn-471] `pm_port_stat_print` @ tm.c:64428 — ~88 lines body
- [fn-472] `pm_g988_stat_print` @ tm.c:64516 — ~113 lines body
- [fn-473] `pm_zte_stat_print` @ tm.c:64629 — ~116 lines body

## Bridge / MAC / VLAN table helpers (sbrg, tm_mac, tm_vlan, tm_multicst) (212)

L2 bridge fabric: per-port enable bits, MAC table aging/learning, VLAN tables, multicast/broadcast tables. These collectively drive the switch forwarding decisions; mainline-criticality is high if we rely on hardware L2 learning.

- [fn-474] `sbrg_change_portmask` @ tm.c:4613 — ~9 lines body
- [fn-475] `sbrg_set_irq_en_mask` @ tm.c:4622 — setter, tmOnuRegWrite(0)
- [fn-476] `sbrg_set_pt_transfer_en` @ tm.c:4649 — setter, tmOnuRegWrite(1), tmOnuRegRead(1)
- [fn-477] `sbrg_get_pt_transfer_en` @ tm.c:4703 — getter, tmOnuRegRead(1)
- [fn-478] `sbrg_set_pt_macaddr_clr` @ tm.c:4744 — setter, tmOnuRegWrite(2)
- [fn-479] `sbrg_get_pt_macaddr_clr` @ tm.c:4780 — getter, tmOnuRegRead(2)
- [fn-480] `sbrg_set_macaddr_age_en` @ tm.c:4813 — setter, tmOnuRegWrite(4)
- [fn-481] `sbrg_get_macaddr_age_en` @ tm.c:4844 — getter, tmOnuRegRead(4)
- [fn-482] `sbrg_set_pt_learn_limit_en` @ tm.c:4873 — setter, tmOnuRegWrite(5), tmOnuRegRead(5)
- [fn-483] `sbrg_get_pt_learn_limit_en` @ tm.c:4927 — getter, tmOnuRegRead(5)
- [fn-484] `sbrg_set_hash_collision_pktdeal` @ tm.c:4968 — setter, tmOnuRegWrite(6)
- [fn-485] `sbrg_get_hash_collision_pktdeal` @ tm.c:5000 — getter, tmOnuRegRead(6)
- [fn-486] `sbrg_set_one_func_open` @ tm.c:5029 — setter, tmOnuRegWrite(7)
- [fn-487] `sbrg_get_one_func_open` @ tm.c:5059 — getter, tmOnuRegRead(7)
- [fn-488] `sbrg_set_mac_bind` @ tm.c:5088 — setter, tmOnuRegWrite(8)
- [fn-489] `sbrg_get_mac_bind` @ tm.c:5117 — getter, tmOnuRegRead(8)
- [fn-490] `sbrg_set_desc_monitor_sel` @ tm.c:5146 — setter, tmOnuRegWrite(9)
- [fn-491] `sbrg_get_desc_monitor_sel` @ tm.c:5177 — getter, tmOnuRegRead(9)
- [fn-492] `sbrg_set_cpu_chk_en` @ tm.c:5206 — setter, tmOnuRegWrite(0xc)
- [fn-493] `sbrg_get_cpu_chk_en` @ tm.c:5236 — getter, tmOnuRegRead(0xc)
- [fn-494] `sbrg_set_outport_vlan_sle` @ tm.c:5265 — setter, tmOnuRegWrite(0xd)
- [fn-495] `sbrg_get_outport_vlan_sle` @ tm.c:5296 — getter, tmOnuRegRead(0xd)
- [fn-496] `sbrg_set_stat_clean_en` @ tm.c:5325 — setter, tmOnuRegWrite(0xe)
- [fn-497] `sbrg_get_stat_clean_en` @ tm.c:5356 — getter, tmOnuRegRead(0xe)
- [fn-498] `sbrg_set_inport_vl_chk_en` @ tm.c:5390 — setter, tmOnuRegWrite(10), tmOnuRegRead(10)
- [fn-499] `sbrg_get_inport_vl_chk_en` @ tm.c:5444 — getter, tmOnuRegRead(10)
- [fn-500] `sbrg_set_outport_vl_chk_en` @ tm.c:5485 — setter, tmOnuRegWrite(0xb), tmOnuRegRead(0xb)
- [fn-501] `sbrg_get_outport_vl_chk_en` @ tm.c:5539 — getter, tmOnuRegRead(0xb)
- [fn-502] `sbrg_set_pt_smac_look_en` @ tm.c:5580 — setter, tmOnuRegWrite(0x20), tmOnuRegRead(0x20)
- [fn-503] `sbrg_get_pt_smac_look_en` @ tm.c:5634 — getter, tmOnuRegRead(0x20)
- [fn-504] `sbrg_set_pt_smac_lookfail_pktdeal` @ tm.c:5675 — setter, tmOnuRegWrite(0x21), tmOnuRegRead(0x21)
- [fn-505] `sbrg_get_pt_smac_lookfail_pktdeal` @ tm.c:5729 — getter, tmOnuRegRead(0x21)
- [fn-506] `sbrg_set_pt_learn_mode` @ tm.c:5770 — setter
- [fn-507] `sbrg_get_pt_learn_mode` @ tm.c:5807 — getter
- [fn-508] `sbrg_get_ind_access_initial_done` @ tm.c:5848 — getter, tmOnuRegRead(0x14)
- [fn-509] `sbrg_get_ind_access_lk_lnok` @ tm.c:5877 — getter, tmOnuRegRead(0x15)
- [fn-510] `sbrg_set_ind_access_data` @ tm.c:5906 — setter, tmOnuRegWrite(0x16)
- [fn-511] `sbrg_get_ind_access_data` @ tm.c:5935 — getter, tmOnuRegRead(0x16)
- [fn-512] `sbrg_set_isolate_pt_cfg` @ tm.c:5976 — setter, tmOnuRegWrite(0x39)
- [fn-513] `sbrg_get_isolate_pt_cfg` @ tm.c:6013 — getter, tmOnuRegRead(0x39)
- [fn-514] `sbrg_set_macaddr_ln_num_limit` @ tm.c:6053 — setter, tmOnuRegWrite(0x2a)
- [fn-515] `sbrg_get_macaddr_ln_num_limit` @ tm.c:6088 — getter, tmOnuRegRead(0x2a)
- [fn-516] `sbrg_get_macaddr_ln_statistics` @ tm.c:6129 — getter, tmOnuRegRead(0x2b)
- [fn-517] `sbrg_set_srcaddr_aging_cycle` @ tm.c:6170 — setter, tmOnuRegWrite(0x1e)
- [fn-518] `sbrg_get_srcaddr_aging_cycle` @ tm.c:6197 — getter, tmOnuRegRead(0x1e)
- [fn-519] `sbrg_set_pt_da_lookup_en` @ tm.c:6226 — setter, tmOnuRegWrite(0x2c), tmOnuRegRead(0x2c)
- [fn-520] `sbrg_get_pt_da_lookup_en` @ tm.c:6280 — getter, tmOnuRegRead(0x2c)
- [fn-521] `sbrg_set_brdcst_fld_en` @ tm.c:6321 — setter, tmOnuRegWrite(0x31), tmOnuRegRead(0x31)
- [fn-522] `sbrg_get_brdcst_fld_en` @ tm.c:6375 — getter, tmOnuRegRead(0x31)
- [fn-523] `sbrg_set_brdcst_fwd_en` @ tm.c:6416 — setter, tmOnuRegWrite(0x32), tmOnuRegRead(0x32)
- [fn-524] `sbrg_get_brdcst_fwd_en` @ tm.c:6470 — getter, tmOnuRegRead(0x32)
- [fn-525] `sbrg_set_multicst_transmit_ctrl` @ tm.c:6511 — setter, tmOnuRegWrite(0x2d), tmOnuRegRead(0x2d)
- [fn-526] `sbrg_get_multicst_transmit_ctrl` @ tm.c:6565 — getter, tmOnuRegRead(0x2d)
- [fn-527] `sbrg_set_unknown_multicst_pktdeal` @ tm.c:6606 — setter, tmOnuRegWrite(0x2e), tmOnuRegRead(0x2e)
- [fn-528] `sbrg_get_unknown_multicst_pktdeal` @ tm.c:6660 — getter, tmOnuRegRead(0x2e)
- [fn-529] `sbrg_set_unknown_multicst_fwd` @ tm.c:6701 — setter, tmOnuRegWrite(0x2f), tmOnuRegRead(0x2f)
- [fn-530] `sbrg_get_unknown_multicst_fwd` @ tm.c:6755 — getter, tmOnuRegRead(0x2f)
- [fn-531] `sbrg_set_unknown_unicst_transmit_ctrl` @ tm.c:6796 — setter, tmOnuRegWrite(0x34), tmOnuRegRead(0x34)
- [fn-532] `sbrg_get_unknown_unicst_transmit_ctrl` @ tm.c:6851 — getter, tmOnuRegRead(0x34)
- [fn-533] `sbrg_set_unknown_unicst_pktdeal` @ tm.c:6892 — setter, tmOnuRegWrite(0x35), tmOnuRegRead(0x35)
- [fn-534] `sbrg_get_unknown_unicst_pktdeal` @ tm.c:6946 — getter, tmOnuRegRead(0x35)
- [fn-535] `sbrg_set_unknown_unicst_fwd` @ tm.c:6987 — setter, tmOnuRegWrite(0x36), tmOnuRegRead(0x36)
- [fn-536] `sbrg_get_unknown_unicst_fwd` @ tm.c:7041 — getter, tmOnuRegRead(0x36)
- [fn-537] `sbrg_set_table_sel` @ tm.c:7082 — setter, tmOnuRegWrite(0x1d)
- [fn-538] `sbrg_get_table_sel` @ tm.c:7112 — getter, tmOnuRegRead(0x1d)
- [fn-539] `sbrg_set_capture_pt` @ tm.c:7141 — setter, tmOnuRegWrite(0x3a)
- [fn-540] `sbrg_get_capture_pt` @ tm.c:7172 — getter, tmOnuRegRead(0x3a)
- [fn-541] `sbrg_set_vl_mirror_en` @ tm.c:7201 — setter, tmOnuRegWrite(0x3b)
- [fn-542] `sbrg_get_vl_mirror_en` @ tm.c:7232 — getter, tmOnuRegRead(0x3b)
- [fn-543] `sbrg_set_pt_mirror_en` @ tm.c:7261 — setter, tmOnuRegWrite(0x3c)
- [fn-544] `sbrg_get_pt_mirror_en` @ tm.c:7292 — getter, tmOnuRegRead(0x3c)
- [fn-545] `sbrg_set_gempt_mirror_en` @ tm.c:7321 — setter, tmOnuRegWrite(0x3d)
- [fn-546] `sbrg_get_gempt_mirror_en` @ tm.c:7352 — getter, tmOnuRegRead(0x3d)
- [fn-547] `sbrg_set_igsdrp_mirror_en` @ tm.c:7381 — setter, tmOnuRegWrite(0x3e)
- [fn-548] `sbrg_get_igsdrp_mirror_en` @ tm.c:7412 — getter, tmOnuRegRead(0x3e)
- [fn-549] `sbrg_set_globle_mirror_en` @ tm.c:7441 — setter, tmOnuRegWrite(0x3f)
- [fn-550] `sbrg_get_globle_mirror_en` @ tm.c:7472 — getter, tmOnuRegRead(0x3f)
- [fn-551] `sbrg_set_igs_mirror_en` @ tm.c:7501 — setter, tmOnuRegWrite(0x40)
- [fn-552] `sbrg_get_igs_mirror_en` @ tm.c:7532 — getter, tmOnuRegRead(0x40)
- [fn-553] `sbrg_set_egs_mirror_en` @ tm.c:7561 — setter, tmOnuRegWrite(0x41)
- [fn-554] `sbrg_get_egs_mirror_en` @ tm.c:7592 — getter, tmOnuRegRead(0x41)
- [fn-555] `sbrg_set_mirror_vlid` @ tm.c:7621 — setter, tmOnuRegWrite(0x42)
- [fn-556] `sbrg_get_mirror_vlid` @ tm.c:7652 — getter, tmOnuRegRead(0x42)
- [fn-557] `sbrg_set_dft_multi_vl_trans_pktdeal` @ tm.c:7681 — setter, tmOnuRegWrite(0x43), tmOnuRegRead(0x43)
- [fn-558] `sbrg_get_dft_multi_vl_trans_pktdeal` @ tm.c:7736 — getter, tmOnuRegRead(0x43)
- [fn-559] `sbrg_set_multicst_vltrans_table` @ tm.c:7777 — setter, tmOnuRegWrite(0x48)
- [fn-560] `sbrg_get_multicst_vltrans_table` @ tm.c:7848 — getter, tmOnuRegRead(0x48)
- [fn-561] `sbrg_set_broadcst_vltrans_table` @ tm.c:7888 — setter, tmOnuRegWrite(0x49)
- [fn-562] `sbrg_get_broadcst_vltrans_table` @ tm.c:7959 — getter, tmOnuRegRead(0x49)
- [fn-563] `sbrg_set_multicst_pritrans_table` @ tm.c:7999 — setter, tmOnuRegWrite(0x4a)
- [fn-564] `sbrg_get_multicst_pritrans_table` @ tm.c:8064 — getter, tmOnuRegRead(0x4a)
- [fn-565] `sbrg_set_broadcst_pritrans_table` @ tm.c:8102 — setter, tmOnuRegWrite(0x4b)
- [fn-566] `sbrg_get_broadcst_pritrans_table` @ tm.c:8166 — getter, tmOnuRegRead(0x4b)
- [fn-567] `sbrg_hash` @ tm.c:8204 — ~76 lines body
- [fn-568] `sbrg_access_timeout` @ tm.c:8280 — tmOnuRegRead(0x14)
- [fn-569] `sbrg_set_indreg_cmd` @ tm.c:8316 — setter, tmOnuRegWrite(0x13)
- [fn-570] `sbrg_get_indreg_cmd` @ tm.c:8358 — getter, tmOnuRegRead(0x13)
- [fn-571] `sbrg_set_indreg_wr_cfg` @ tm.c:8391 — setter
- [fn-572] `sbrg_get_indreg_wr_cfg` @ tm.c:8405 — getter
- [fn-573] `sbrg_set_indreg_wr` @ tm.c:8422 — setter, tmOnuRegWrite(0x4e)
- [fn-574] `sbrg_print_mactable` @ tm.c:8443 — tmOnuRegWrite(0x13), tmOnuRegRead(0x1d)
- [fn-575] `sbrg_print_ipv4table` @ tm.c:8549 — tmOnuRegWrite(0x13), tmOnuRegRead(0x14)
- [fn-576] `sbrg_print_ipv6table` @ tm.c:8648 — tmOnuRegWrite(0x13), tmOnuRegRead(0x14)
- [fn-577] `sbrg_print_vltbl` @ tm.c:8774 — tmOnuRegWrite(0x13), tmOnuRegRead(0x14)
- [fn-578] `sbrg_lookup_vltbl` @ tm.c:8844 — tmOnuRegRead(0x4c)
- [fn-579] `sbrg_add_vltbl` @ tm.c:8913 — tmOnuRegWrite(0x4c), tmOnuRegRead(0x4c)
- [fn-580] `sbrg_set_macaddr_exchange_md` @ tm.c:8985 — setter, tmOnuRegWrite(0x17)
- [fn-581] `sbrg_get_macaddr_exchange_md` @ tm.c:9016 — getter, tmOnuRegRead(0x17)
- [fn-582] `sbrg_set_multicst_md` @ tm.c:9045 — setter, tmOnuRegWrite(0x18)
- [fn-583] `sbrg_get_multicst_md` @ tm.c:9075 — getter, tmOnuRegRead(0x18)
- [fn-584] `sbrg_set_hash_mode` @ tm.c:9104 — setter, tmOnuRegWrite(0x1a)
- [fn-585] `sbrg_get_hash_mode` @ tm.c:9133 — getter, tmOnuRegRead(0x1a)
- [fn-586] `sbrg_set_multi_vlan_mode` @ tm.c:9162 — setter, tmOnuRegWrite(0x19)
- [fn-587] `sbrg_get_multi_vlan_mode` @ tm.c:9193 — getter, tmOnuRegRead(0x19)
- [fn-588] `sbrg_lookup_ipv4table` @ tm.c:9222 — tmOnuRegRead(0x4c)
- [fn-589] `sbrg_add_ipv4table` @ tm.c:9368 — tmOnuRegRead(0x4c)
- [fn-590] `sbrg_delete_ipv4table` @ tm.c:9588 — tmOnuRegRead(0x4c)
- [fn-591] `sbrg_lookup_ipv6table` @ tm.c:9715 — tmOnuRegRead(0x4c)
- [fn-592] `sbrg_add_ipv6table` @ tm.c:9903 — tmOnuRegWrite(0x4e), tmOnuRegRead(0x4c)
- [fn-593] `sbrg_delete_ipv6table` @ tm.c:10231 — tmOnuRegWrite(0x4e), tmOnuRegRead(0x4c)
- [fn-594] `sbrg_set_multi_mac_vlan_mode` @ tm.c:10429 — setter, tmOnuRegWrite(0x1b)
- [fn-595] `sbrg_get_multi_mac_vlan_mode` @ tm.c:10460 — getter, tmOnuRegRead(0x1b)
- [fn-596] `sbrg_set_multi_mac_hash_mode` @ tm.c:10489 — setter, tmOnuRegWrite(0x1c)
- [fn-597] `sbrg_get_multi_mac_hash_mode` @ tm.c:10520 — getter, tmOnuRegRead(0x1c)
- [fn-598] `sbrg_lookup_mactable` @ tm.c:10549 — tmOnuRegRead(0x4c)
- [fn-599] `sbrg_add_mactable` @ tm.c:10706 — tmOnuRegRead(0x4c)
- [fn-600] `sbrg_delete_mactable` @ tm.c:10911 — tmOnuRegRead(0x4c)
- [fn-601] `sbrg_get_ptclr_bit` @ tm.c:11055 — getter, tmOnuRegRead(0x1f)
- [fn-602] `sbrg_set_uni_unkmul_fld_inctrl` @ tm.c:11084 — setter, tmOnuRegWrite(0x30), tmOnuRegRead(0x30)
- [fn-603] `sbrg_get_uni_unkmul_fld_inctrl` @ tm.c:11138 — getter, tmOnuRegRead(0x30)
- [fn-604] `sbrg_set_pon_brdcst_fld_inctrl` @ tm.c:11184 — setter, tmOnuRegWrite(0x33), tmOnuRegRead(0x33)
- [fn-605] `sbrg_get_pon_brdcst_fld_inctrl` @ tm.c:11237 — getter, tmOnuRegRead(0x33)
- [fn-606] `sbrg_set_pon_unkuni_fld_inctrl` @ tm.c:11278 — setter, tmOnuRegWrite(0x37), tmOnuRegRead(0x37)
- [fn-607] `sbrg_get_pon_unkuni_fld_inctrl` @ tm.c:11331 — getter, tmOnuRegRead(0x37)
- [fn-608] `sbrg_set_unkmul_flood_portmask` @ tm.c:11372 — setter, tmOnuRegWrite(0x30)
- [fn-609] `sbrg_set_pon_brdcst_flood_portmask` @ tm.c:11421 — setter, tmOnuRegWrite(0x33)
- [fn-610] `sbrg_pon_unkuni_flood_portmask` @ tm.c:11453 — tmOnuRegWrite(0x37)
- [fn-611] `sbrg_set_dft_brd_vl_trans_pktdeal` @ tm.c:11485 — setter, tmOnuRegWrite(0x44), tmOnuRegRead(0x44)
- [fn-612] `sbrg_get_dft_brd_vl_trans_pktdeal` @ tm.c:11539 — getter, tmOnuRegRead(0x44)
- [fn-613] `sbrg_set_dft_unkuni_vl_trans_pktdeal` @ tm.c:11580 — setter, tmOnuRegWrite(0x45), tmOnuRegRead(0x45)
- [fn-614] `sbrg_get_dft_unkuni_vl_trans_pktdeal` @ tm.c:11634 — getter, tmOnuRegRead(0x45)
- [fn-615] `sbrg_set_pt_tls` @ tm.c:11675 — setter, tmOnuRegWrite(0x38), tmOnuRegRead(0x38)
- [fn-616] `sbrg_get_pt_tls` @ tm.c:11728 — getter, tmOnuRegRead(0x38)
- [fn-617] `sbrg_set_uni_vtrans_outvlan_check` @ tm.c:11769 — setter, tmOnuRegWrite(0x46), tmOnuRegRead(0x46)
- [fn-618] `sbrg_get_uni_vtrans_outvlan_check` @ tm.c:11822 — getter, tmOnuRegRead(0x46)
- [fn-619] `sbrg_set_broad_vtrans_outvlan_check` @ tm.c:11863 — setter, tmOnuRegWrite(0x47), tmOnuRegRead(0x47)
- [fn-620] `sbrg_get_broad_vtrans_outvlan_check` @ tm.c:11917 — getter, tmOnuRegRead(0x47)
- [fn-621] `sbrg_get_statistics` @ tm.c:11958 — getter, fpga_read_reg(0xe2300)
- [fn-622] `sbrg_get_command` @ tm.c:12092 — getter
- [fn-623] `sbrg_set_qnum_map_mode` @ tm.c:12182 — setter, tmOnuRegWrite(0x4f), tmOnuRegRead(0x4f)
- [fn-624] `sbrg_get_qnum_map_mode` @ tm.c:12235 — getter, tmOnuRegRead(0x4f)
- [fn-625] `sbrg_set_sbrg_pri_qtab_pon` @ tm.c:12276 — setter
- [fn-626] `sbrg_get_sbrg_pri_qtab_pon` @ tm.c:12328 — getter
- [fn-627] `sbrg_set_up_l2_unlook_fwd` @ tm.c:12374 — setter, tmOnuRegWrite(0x58), tmOnuRegRead(0x58)
- [fn-628] `sbrg_get_up_l2_unlook_fwd` @ tm.c:12427 — getter, tmOnuRegRead(0x58)
- [fn-629] `tm_vlan_statistics` @ tm.c:35484 — ~9 lines body
- [fn-630] `tm_vlan_stat_config` @ tm.c:35493 — ~9 lines body
- [fn-631] `tm_mac_old_ena_set` @ tm.c:35624 — setter
- [fn-632] `tm_multicast_mode_set` @ tm.c:35640 — setter
- [fn-633] `tm_mac_exchange_mode_set` @ tm.c:35656 — setter
- [fn-634] `tm_mac_learn_mode_set` @ tm.c:35672 — setter
- [fn-635] `tm_multicst_vltrans_table_lookup_get` @ tm.c:38522 — getter
- [fn-636] `tm_multicst_vltrans_table_print_get` @ tm.c:38646 — getter
- [fn-637] `tm_multicst_vltrans_table_delete_set` @ tm.c:38713 — setter
- [fn-638] `tm_multicst_vltrans_table_upd_set` @ tm.c:38836 — setter
- [fn-639] `tm_multicst_vltrans_table_add_set` @ tm.c:38945 — setter
- [fn-640] `tm_broadcst_vltrans_table_delete_set` @ tm.c:39078 — setter
- [fn-641] `tm_broadcst_vltrans_table_add_set` @ tm.c:39178 — setter
- [fn-642] `tm_broadcst_vltrans_table_lookup_get` @ tm.c:39295 — getter
- [fn-643] `tm_broadcst_vltrans_table_print_get` @ tm.c:39415 — getter
- [fn-644] `tm_mac_learn_mode_get` @ tm.c:39482 — getter, printk:"ERROR:(%s:%d)"
- [fn-645] `tm_mac_aging_cycle_set` @ tm.c:39556 — setter
- [fn-646] `tm_mac_learning_limit_set` @ tm.c:39589 — setter
- [fn-647] `tm_mac_learning_limit_get` @ tm.c:39641 — getter, printk:"ERROR:(%s:%d)"
- [fn-648] `tm_mac_exchange_mode_get` @ tm.c:39702 — getter
- [fn-649] `tm_multicast_mode_get` @ tm.c:39740 — getter
- [fn-650] `tm_hash_mode_set` @ tm.c:39762 — setter
- [fn-651] `tm_hash_mode_get` @ tm.c:39778 — getter
- [fn-652] `tm_multivlan_mode_set` @ tm.c:39800 — setter
- [fn-653] `tm_multivlan_mode_get` @ tm.c:39816 — getter
- [fn-654] `tm_mactable_print_get` @ tm.c:40459 — getter
- [fn-655] `tm_mactable_lookup_get` @ tm.c:40475 — getter, printk:"ERROR:(%s:%d)"
- [fn-656] `tm_mactable_add_set` @ tm.c:40522 — setter, printk:"ERROR:(%s:%d)"
- [fn-657] `tm_vlantable_print_get` @ tm.c:40566 — getter
- [fn-658] `tm_vlantable_lookup_get` @ tm.c:40582 — getter, printk:"ERROR:(%s:%d)"
- [fn-659] `tm_ipv4table_print_get` @ tm.c:40714 — getter
- [fn-660] `tm_ipv6table_print_get` @ tm.c:40730 — getter
- [fn-661] `tm_ipv6table_lookup_get` @ tm.c:40746 — getter, printk:"ERROR:(%s:%d)"
- [fn-662] `tm_ipv6table_add_set` @ tm.c:40801 — setter, printk:"ERROR:(%s:%d)"
- [fn-663] `tm_mac_ramaddr_sel_get` @ tm.c:41569 — getter, printk:"ERROR:(%s:%d)"
- [fn-664] `tm_mac_aging_cycle_get` @ tm.c:41614 — getter, printk:"ERROR:(%s:%d)"
- [fn-665] `tm_mac_ramaddr_sel_set` @ tm.c:41652 — setter
- [fn-666] `tm_mac_learning_number_get` @ tm.c:41706 — getter, printk:"ERROR:(%s:%d)"
- [fn-667] `tm_mac_old_ena_get` @ tm.c:41758 — getter, printk:"ERROR:(%s:%d)"
- [fn-668] `tm_mactable_delete_set` @ tm.c:42020 — setter, printk:"ERROR:(%s:%d)"
- [fn-669] `tm_ipv4table_lookup_get` @ tm.c:42053 — getter, printk:"ERROR:(%s:%d)"
- [fn-670] `tm_ipv4table_add_set` @ tm.c:42096 — setter, printk:"ERROR:(%s:%d)"
- [fn-671] `tm_ipv4table_delete_set` @ tm.c:42137 — setter, printk:"ERROR:(%s:%d)"
- [fn-672] `tm_ipv6table_delete_set` @ tm.c:42171 — setter
- [fn-673] `tm_vlan_check_ena_get` @ tm.c:43679 — getter, printk:"ERROR:(%s:%d)"
- [fn-674] `tm_mac_tranfer_ena_set` @ tm.c:44923 — setter
- [fn-675] `tm_mac_tranfer_ena_get` @ tm.c:44949 — getter, printk:"ERROR:(%s:%d)"
- [fn-676] `tm_mac_da_look_ena_set` @ tm.c:44987 — setter
- [fn-677] `tm_mac_da_look_ena_get` @ tm.c:45013 — getter, printk:"ERROR:(%s:%d)"
- [fn-678] `tm_mac_sa_look_ena_set` @ tm.c:45051 — setter
- [fn-679] `tm_mac_sa_look_ena_get` @ tm.c:45077 — getter, printk:"ERROR:(%s:%d)"
- [fn-680] `tm_mac_sa_lookfail_ctrl_set` @ tm.c:45115 — setter
- [fn-681] `tm_mac_sa_lookfail_ctrl_get` @ tm.c:45141 — getter, printk:"ERROR:(%s:%d)"
- [fn-682] `tm_vlantable_add_set` @ tm.c:45179 — setter, printk:"ERROR:(%s:%d)"
- [fn-683] `tm_vlan_bkt_rate_limit_set` @ tm.c:45686 — setter
- [fn-684] `tm_vlan_bkt_rate_limit_get` @ tm.c:45730 — getter
- [fn-685] `tm_ipv6table_delete_set.part.18` @ tm.c:69437 — printk:"ERROR:(%s:%d)"

## Scheduler / TCONT / port-level helpers (sch, tm_tcont, tm_port, tm_pon) (176)

Scheduler shaper config, TCONT per-queue shaping, per-port status/auth/down-stream, PON-side shaping. Most are RMW setters around `fpga_write_reg`.

- [fn-686] `sch_get_que_sharp_enable` @ tm.c:28924 — getter, tmOnuRegRead(0)
- [fn-687] `sch_get_dwrr_enable` @ tm.c:28985 — getter, tmOnuRegRead(1)
- [fn-688] `sch_get_hw_up_age_enable` @ tm.c:29046 — getter, tmOnuRegRead(2)
- [fn-689] `sch_set_hw_up_age_mode` @ tm.c:29075 — setter, tmOnuRegWrite(3)
- [fn-690] `sch_get_hw_up_age_mode` @ tm.c:29107 — getter, tmOnuRegRead(3)
- [fn-691] `sch_get_tcont_sharp_enable` @ tm.c:29168 — getter, tmOnuRegRead(4)
- [fn-692] `sch_set_quesch_sharp_enable` @ tm.c:29197 — setter, tmOnuRegWrite(5)
- [fn-693] `sch_get_quesch_sharp_enable` @ tm.c:29229 — getter, tmOnuRegRead(5)
- [fn-694] `sch_get_secsch_dwrr_enable` @ tm.c:29290 — getter, tmOnuRegRead(6)
- [fn-695] `sch_set_oam_age_enable` @ tm.c:29319 — setter, tmOnuRegWrite(7)
- [fn-696] `sch_get_oam_age_enable` @ tm.c:29351 — getter, tmOnuRegRead(7)
- [fn-697] `sch_get_hw_dn_age_enable` @ tm.c:29412 — getter, tmOnuRegRead(8)
- [fn-698] `sch_set_hw_dn_age_mode` @ tm.c:29441 — setter, tmOnuRegWrite(9)
- [fn-699] `sch_get_hw_dn_age_mode` @ tm.c:29473 — getter, tmOnuRegRead(9)
- [fn-700] `sch_set_hw_age_time` @ tm.c:29502 — setter, tmOnuRegWrite(10)
- [fn-701] `sch_get_hw_age_time` @ tm.c:29526 — getter, tmOnuRegRead(10)
- [fn-702] `sch_set_sw_age_enable` @ tm.c:29555 — setter, tmOnuRegWrite(0xc)
- [fn-703] `sch_get_sw_age_enable` @ tm.c:29587 — getter, tmOnuRegRead(0xc)
- [fn-704] `sch_set_sw_age_pqid` @ tm.c:29616 — setter, tmOnuRegWrite(0xb)
- [fn-705] `sch_get_sw_age_pqid` @ tm.c:29640 — getter, tmOnuRegRead(0xb)
- [fn-706] `sch_set_indirect_rw_cmd` @ tm.c:29669 — setter, tmOnuRegWrite(0xd)
- [fn-707] `sch_get_ind_acc_done` @ tm.c:29725 — getter, tmOnuRegRead(0xe)
- [fn-708] `sch_set_ind_acc_data` @ tm.c:29759 — setter, tmOnuRegWrite(0xf)
- [fn-709] `sch_get_ind_acc_data` @ tm.c:29777 — getter, tmOnuRegRead(0xf)
- [fn-710] `sch_set_spend_byte` @ tm.c:29800 — setter, tmOnuRegWrite(0x10)
- [fn-711] `sch_get_spend_byte` @ tm.c:29819 — getter, tmOnuRegRead(0x10)
- [fn-712] `sch_set_shp_fill_time` @ tm.c:29842 — setter, tmOnuRegWrite(0x11)
- [fn-713] `sch_get_shp_fill_time` @ tm.c:29871 — getter, tmOnuRegRead(0x11)
- [fn-714] `sch_set_quesch_mount_tcont_que` @ tm.c:29896 — setter, tmOnuRegWrite(0x12)
- [fn-715] `sch_get_quesch_mount_tcont_que` @ tm.c:29953 — getter, tmOnuRegRead(0x12)
- [fn-716] `sch_set_up_que_sp_dwrr_cfg` @ tm.c:30003 — setter
- [fn-717] `sch_get_up_que_sp_dwrr_cfg` @ tm.c:30139 — getter
- [fn-718] `sch_set_up_queue_wrr_weight` @ tm.c:30236 — setter
- [fn-719] `sch_get_up_queue_wrr_weight` @ tm.c:30328 — getter
- [fn-720] `sch_set_up_pq_sharp_fill_rate` @ tm.c:30420 — setter
- [fn-721] `sch_get_up_pq_sharp_fill_rate` @ tm.c:30494 — getter
- [fn-722] `sch_set_up_pq_sharp_bucket_cap` @ tm.c:30586 — setter
- [fn-723] `sch_get_up_pq_sharp_bucket_cap` @ tm.c:30660 — getter
- [fn-724] `sch_set_up_tcont_sharp_fill_rate` @ tm.c:30752 — setter
- [fn-725] `sch_get_up_tcont_sharp_fill_rate` @ tm.c:30820 — getter
- [fn-726] `sch_set_up_tcont_sharp_bucket_cap` @ tm.c:30899 — setter
- [fn-727] `sch_get_up_tcont_sharp_bucket_cap` @ tm.c:30967 — getter
- [fn-728] `sch_get_up_queue_last_pkt_cnt` @ tm.c:31046 — getter
- [fn-729] `sch_set_secsch_sp_dwrr_cfg` @ tm.c:31138 — setter
- [fn-730] `sch_get_secsch_sp_dwrr_cfg` @ tm.c:31269 — getter
- [fn-731] `sch_set_quesch_sharp_fill_rate` @ tm.c:31364 — setter
- [fn-732] `sch_get_quesch_sharp_fill_rate` @ tm.c:31437 — getter
- [fn-733] `sch_set_quesch_sharp_bucket_cap` @ tm.c:31529 — setter
- [fn-734] `sch_get_quesch_sharp_bucket_cap` @ tm.c:31602 — getter
- [fn-735] `sch_set_secsch_wrr_weight` @ tm.c:31694 — setter
- [fn-736] `sch_get_secsch_wrr_weight` @ tm.c:31781 — getter
- [fn-737] `sch_set_dn_que_sp_dwrr_cfg` @ tm.c:31873 — setter
- [fn-738] `sch_get_dn_que_sp_dwrr_cfg` @ tm.c:32004 — getter
- [fn-739] `sch_set_dn_queue_wrr_weight` @ tm.c:32091 — setter
- [fn-740] `sch_get_dn_queue_wrr_weight` @ tm.c:32182 — getter
- [fn-741] `sch_set_dn_pq_sharp_fill_rate` @ tm.c:32269 — setter
- [fn-742] `sch_get_dn_pq_sharp_fill_rate` @ tm.c:32278 — getter
- [fn-743] `sch_set_dn_pq_sharp_bucket_cap` @ tm.c:32287 — setter
- [fn-744] `sch_get_dn_pq_sharp_bucket_cap` @ tm.c:32296 — getter
- [fn-745] `sch_set_dn_tcont_sharp_fill_rate` @ tm.c:32305 — setter
- [fn-746] `sch_get_dn_tcont_sharp_fill_rate` @ tm.c:32389 — getter
- [fn-747] `sch_set_dn_tcont_sharp_bucket_cap` @ tm.c:32469 — setter
- [fn-748] `sch_get_dn_tcont_sharp_bucket_cap` @ tm.c:32538 — getter
- [fn-749] `sch_get_dn_queue_last_pkt_cnt` @ tm.c:32617 — getter
- [fn-750] `tm_port_flow_ctrl_mac_set` @ tm.c:35457 — setter
- [fn-751] `tm_port_flow_ctrl_mac_get` @ tm.c:35466 — getter
- [fn-752] `tm_port_statistics` @ tm.c:35475 — ~9 lines body
- [fn-753] `tm_tcont_que_dwrr_ena_set` @ tm.c:35546 — setter
- [fn-754] `tm_port_egress_sharp_ena_set` @ tm.c:35562 — setter
- [fn-755] `tm_port_ingress_rate_limit_ena_set` @ tm.c:35592 — setter
- [fn-756] `tm_port_802x_trap_set` @ tm.c:35919 — setter
- [fn-757] `tm_port_pkt_filter_set` @ tm.c:35991 — setter
- [fn-758] `tm_port_pvid_set` @ tm.c:36059 — setter
- [fn-759] `tm_port_pvid_get` @ tm.c:36111 — getter, printk:"ERROR:(%s:%d)"
- [fn-760] `tm_port_pkt_filter_get` @ tm.c:36168 — getter
- [fn-761] `tm_port_vlan_filter_set` @ tm.c:36238 — setter
- [fn-762] `tm_port_isolate_set` @ tm.c:36288 — setter
- [fn-763] `tm_port_isolate_get` @ tm.c:36337 — getter, printk:"ERROR:(%s:%d)"
- [fn-764] `tm_port_ingress_rate_limit_ena_get` @ tm.c:36397 — getter
- [fn-765] `tm_port_rate_limit_get` @ tm.c:36420 — getter
- [fn-766] `tm_port_egress_sharp_ena_get` @ tm.c:36448 — getter
- [fn-767] `tm_port_egress_dwrr_ena_set` @ tm.c:36471 — setter
- [fn-768] `tm_tcont_que_sharp_ena_set` @ tm.c:36481 — setter
- [fn-769] `tm_port_egress_dwrr_ena_get` @ tm.c:36497 — getter
- [fn-770] `tm_tcont_que_sharp_ena_get` @ tm.c:36520 — getter
- [fn-771] `tm_port_egress_spdwrr_schedule_set` @ tm.c:36543 — setter
- [fn-772] `tm_port_egress_spdwrr_schedule_get` @ tm.c:36567 — getter
- [fn-773] `tm_port_egress_traffic_sharp_get` @ tm.c:36601 — getter
- [fn-774] `tm_port_protocol_pktdeal_set` @ tm.c:36899 — setter
- [fn-775] `tm_port_protocol_pktdeal_get` @ tm.c:37154 — getter
- [fn-776] `tm_port_flow_send_ctrl_set` @ tm.c:37409 — setter
- [fn-777] `tm_port_flow_send_ctrl_get` @ tm.c:37451 — getter
- [fn-778] `tm_port_status_get` @ tm.c:37538 — getter
- [fn-779] `tm_port_802x_authen_get` @ tm.c:37628 — getter
- [fn-780] `tm_port_bpdu_pass802x_set` @ tm.c:37675 — setter
- [fn-781] `tm_port_bpdu_pass802x_get` @ tm.c:37718 — getter
- [fn-782] `tm_port_802x_trap_get` @ tm.c:37765 — getter
- [fn-783] `tm_port_stp_set` @ tm.c:37812 — setter
- [fn-784] `tm_port_stp_get` @ tm.c:37856 — getter
- [fn-785] `tm_port_stp_status_set` @ tm.c:37908 — setter
- [fn-786] `tm_port_stp_status_get` @ tm.c:37951 — getter
- [fn-787] `tm_port_clear_macaddr_set` @ tm.c:38489 — setter
- [fn-788] `tm_tcont_sch_mode_set` @ tm.c:40964 — setter
- [fn-789] `tm_tcont_sch_mode_get` @ tm.c:40980 — getter
- [fn-790] `tm_tcont_que_dwrr_ena_get` @ tm.c:41003 — getter
- [fn-791] `tm_tcont_que_sharp_get` @ tm.c:41026 — getter
- [fn-792] `tm_tcont_sharp_get` @ tm.c:41049 — getter
- [fn-793] `tm_tcont_que_sch_sp_dwwr_mod_get` @ tm.c:41072 — getter
- [fn-794] `tm_tcont_que_sch_weight_set` @ tm.c:41096 — setter
- [fn-795] `tm_tcont_que_sch_weight_get` @ tm.c:41141 — getter
- [fn-796] `tm_tcont_que_sch_sp_dwwr_mod_set` @ tm.c:41164 — setter
- [fn-797] `tm_tcont_secsch_hang_que_set` @ tm.c:41219 — setter
- [fn-798] `tm_port_vlan_filter_get` @ tm.c:41514 — getter, printk:"ERROR:(%s:%d)"
- [fn-799] `tm_tcont_oamqueue_enable` @ tm.c:42215 — ~42 lines body
- [fn-800] `tm_port_cast_rate_limit_get` @ tm.c:43729 — getter
- [fn-801] `tm_port_ingress_unkown_sa_pps_set` @ tm.c:43773 — setter
- [fn-802] `tm_port_ingress_unkown_sa_pps_get` @ tm.c:43797 — getter
- [fn-803] `tm_port_brdcast_flood_ena_set` @ tm.c:43829 — setter
- [fn-804] `tm_port_brdcast_flood_ena_get` @ tm.c:43855 — getter, printk:"ERROR:(%s:%d)"
- [fn-805] `tm_port_brdcast_fwd_ena_set` @ tm.c:43893 — setter
- [fn-806] `tm_port_brdcast_fwd_ena_get` @ tm.c:43919 — getter, printk:"ERROR:(%s:%d)"
- [fn-807] `tm_port_unknwn_multicast_flood_set` @ tm.c:43957 — setter
- [fn-808] `tm_port_unknwn_multicast_flood_get` @ tm.c:43983 — getter, printk:"ERROR:(%s:%d)"
- [fn-809] `tm_port_unknwn_multicast_fwd_set` @ tm.c:44021 — setter
- [fn-810] `tm_port_unknwn_multicast_fwd_get` @ tm.c:44047 — getter, printk:"ERROR:(%s:%d)"
- [fn-811] `tm_port_multicast_act_set` @ tm.c:44085 — setter
- [fn-812] `tm_port_multicast_act_get` @ tm.c:44116 — getter, printk:"ERROR:(%s:%d)"
- [fn-813] `tm_port_unknwn_multicast_floodport_set` @ tm.c:44165 — setter
- [fn-814] `tm_port_unknwn_multicast_floodport_get` @ tm.c:44220 — getter, printk:"ERROR:(%s:%d)"
- [fn-815] `tm_port_unknwn_unicast_flood_set` @ tm.c:44287 — setter
- [fn-816] `tm_port_unknwn_unicast_flood_get` @ tm.c:44330 — getter, printk:"ERROR:(%s:%d)"
- [fn-817] `tm_port_unknwn_unicast_fwd_set` @ tm.c:44383 — setter
- [fn-818] `tm_port_unknwn_unicast_fwd_get` @ tm.c:44409 — getter, printk:"ERROR:(%s:%d)"
- [fn-819] `tm_port_unicast_act_set` @ tm.c:44447 — setter
- [fn-820] `tm_port_unicast_act_get` @ tm.c:44473 — getter, printk:"ERROR:(%s:%d)"
- [fn-821] `tm_port_pon_broadcast_floodport_set` @ tm.c:44511 — setter
- [fn-822] `tm_port_pon_broadcast_floodport_get` @ tm.c:44537 — getter, printk:"ERROR:(%s:%d)"
- [fn-823] `tm_port_pon_unicast_floodport_set` @ tm.c:44575 — setter
- [fn-824] `tm_port_pon_unicast_floodport_get` @ tm.c:44601 — getter, printk:"ERROR:(%s:%d)"
- [fn-825] `tm_port_tls_set` @ tm.c:44639 — setter
- [fn-826] `tm_port_tls_get` @ tm.c:44665 — getter, printk:"ERROR:(%s:%d)"
- [fn-827] `tm_port_dft_multicst_vltrans_set` @ tm.c:44703 — setter
- [fn-828] `tm_port_dft_multicst_vltrans_get` @ tm.c:44729 — getter, printk:"ERROR:(%s:%d)"
- [fn-829] `tm_port_dft_broadcst_vltrans_set` @ tm.c:44767 — setter
- [fn-830] `tm_port_dft_broadcst_vltrans_get` @ tm.c:44798 — getter, printk:"ERROR:(%s:%d)"
- [fn-831] `tm_port_dft_unkunicst_vltrans_set` @ tm.c:44845 — setter
- [fn-832] `tm_port_dft_unkunicst_vltrans_get` @ tm.c:44876 — getter, printk:"ERROR:(%s:%d)"
- [fn-833] `tm_port_overspeed_bucket_ena_set` @ tm.c:45223 — setter
- [fn-834] `tm_port_overspeed_bucket_ena_get` @ tm.c:45247 — getter
- [fn-835] `tm_port_name_get` @ tm.c:45278 — getter
- [fn-836] `tm_port_more_name_get` @ tm.c:45315 — getter
- [fn-837] `tm_port_rate_limit_set` @ tm.c:45375 — setter
- [fn-838] `tm_port_cast_rate_limit_set` @ tm.c:45404 — setter
- [fn-839] `tm_port_egress_traffic_sharp_set` @ tm.c:45451 — setter
- [fn-840] `tm_tcont_secsch_sharp_set` @ tm.c:45598 — setter
- [fn-841] `tm_port_ingress_unkown_unida_pps_set` @ tm.c:45832 — setter
- [fn-842] `tm_port_ingress_unkown_unida_pps_get` @ tm.c:45856 — getter
- [fn-843] `tm_port_ingress_unkown_mulda_pps_set` @ tm.c:45888 — setter
- [fn-844] `tm_port_ingress_unkown_mulda_pps_get` @ tm.c:45912 — getter
- [fn-845] `tm_port_unknwn_multicast_floodcontrolmask` @ tm.c:45944 — ~28 lines body
- [fn-846] `tm_port_pon_broadcast_floodcontrolmask` @ tm.c:45972 — ~36 lines body
- [fn-847] `tm_port_pon_unkuni_floodcontrolmask` @ tm.c:46008 — ~36 lines body
- [fn-848] `tm_tcont_que_age_ena_set` @ tm.c:46903 — setter
- [fn-849] `tm_tcont_que_age_ena_get` @ tm.c:46927 — getter
- [fn-850] `tm_tcont_que_age_mode_get` @ tm.c:46979 — getter
- [fn-851] `tm_tcont_que_hw_age_time_get` @ tm.c:47172 — getter
- [fn-852] `tm_tcont_que_sw_age_ena_set` @ tm.c:47188 — setter
- [fn-853] `tm_tcont_que_sw_age_ena_get` @ tm.c:47204 — getter
- [fn-854] `tm_tcont_que_sw_age_pqid_set` @ tm.c:47227 — setter
- [fn-855] `tm_tcont_que_sw_age_pqid_get` @ tm.c:47262 — getter
- [fn-856] `tm_tcont_secsch_sharp_get` @ tm.c:47291 — getter
- [fn-857] `tm_tcont_que_secsch_weight_set` @ tm.c:47314 — setter
- [fn-858] `tm_tcont_que_secsch_weight_get` @ tm.c:47348 — getter
- [fn-859] `tm_tcont_sec_sch_sp_dwwr_mod_set` @ tm.c:47371 — setter
- [fn-860] `tm_tcont_sec_sch_sp_dwwr_mod_get` @ tm.c:47389 — getter
- [fn-861] `tm_tcont_secsch_hang_que_get` @ tm.c:47413 — getter

## RED (Random Early Drop) policy (26)

Per-queue thresholds + drop-probability programming. Loops in [fn-05b] dispatch through these.

- [fn-862] `red_set_open_out_en` @ tm.c:33149 — setter, tmOnuRegWrite(1)
- [fn-863] `red_get_open_out_en` @ tm.c:33178 — getter, tmOnuRegRead(1)
- [fn-864] `red_set_trap_color_en` @ tm.c:33206 — setter, tmOnuRegWrite(2)
- [fn-865] `red_get_trap_color_en` @ tm.c:33235 — getter, tmOnuRegRead(2)
- [fn-866] `red_set_share_mode` @ tm.c:33263 — setter, tmOnuRegWrite(3)
- [fn-867] `red_get_share_mode` @ tm.c:33290 — getter, tmOnuRegRead(3)
- [fn-868] `red_set_indirect_rw_cmd` @ tm.c:33318 — setter, tmOnuRegWrite(4)
- [fn-869] `red_get_indirect_rw_cmd` @ tm.c:33366 — getter, tmOnuRegRead(4)
- [fn-870] `red_get_ind_acc_done` @ tm.c:33398 — getter, tmOnuRegRead(5)
- [fn-871] `red_set_ind_acc_data` @ tm.c:33426 — setter, tmOnuRegWrite(6)
- [fn-872] `red_get_ind_acc_data` @ tm.c:33453 — getter, tmOnuRegRead(6)
- [fn-873] `red_set_in_share_max` @ tm.c:33493 — setter, tmOnuRegWrite(7)
- [fn-874] `red_get_in_share_max` @ tm.c:33520 — getter, tmOnuRegRead(7)
- [fn-875] `red_set_fec_enable` @ tm.c:33545 — setter, tmOnuRegWrite(0xb)
- [fn-876] `red_get_fec_enable` @ tm.c:33571 — getter, tmOnuRegRead(0xb)
- [fn-877] `red_set_up_out_share_max` @ tm.c:33596 — setter, tmOnuRegWrite(0xc)
- [fn-878] `red_get_up_out_share_max` @ tm.c:33623 — getter, tmOnuRegRead(0xc)
- [fn-879] `red_set_out_buffer_queue_cfg` @ tm.c:33649 — setter
- [fn-880] `red_get_out_buffer_queue_cfg` @ tm.c:33715 — getter
- [fn-881] `red_get_out_que_ram_used_space` @ tm.c:33801 — getter
- [fn-882] `red_set_in_buffer_queue_cfg` @ tm.c:33896 — setter
- [fn-883] `red_get_in_buffer_queue_cfg` @ tm.c:33966 — getter
- [fn-884] `red_get_in_que_ram_used_space` @ tm.c:34052 — getter
- [fn-885] `red_set_buffer_queue_cfg` @ tm.c:34147 — setter
- [fn-886] `red_get_buffer_queue_cfg` @ tm.c:34257 — getter
- [fn-887] `red_get_buffer_queue_used_space` @ tm.c:34369 — getter

## NPP block helpers (spa, sdet, smac, smct, sopc, uopc, sipc, sadm, greg, opc) (233)

Stream parser, frame-length detector, MAC, scrambler, OPC, IPC, stream-ADM, NPP-global-register helpers. Many are simple `tmOnuRegWrite(reg_id, val, port, &reg_table)` wrappers.

- [fn-888] `sadm_set_adm_en` @ tm.c:12468 — setter, tmOnuRegWrite(0)
- [fn-889] `sadm_get_adm_en` @ tm.c:12497 — getter, tmOnuRegRead(0)
- [fn-890] `sadm_set_adm_mode` @ tm.c:12530 — setter, tmOnuRegWrite(1)
- [fn-891] `sadm_get_adm_mode` @ tm.c:12557 — getter, tmOnuRegRead(1)
- [fn-892] `sadm_set_pps_type` @ tm.c:12590 — setter, tmOnuRegWrite(2)
- [fn-893] `sadm_get_pps_type` @ tm.c:12617 — getter, tmOnuRegRead(2)
- [fn-894] `sadm_set_adm_trap_en` @ tm.c:12645 — setter, tmOnuRegWrite(3)
- [fn-895] `sadm_set_bps_th` @ tm.c:12673 — setter, tmOnuRegWrite(4)
- [fn-896] `sadm_get_bps_th` @ tm.c:12700 — getter, tmOnuRegRead(4)
- [fn-897] `sadm_set_one_second` @ tm.c:12728 — setter, tmOnuRegWrite(5)
- [fn-898] `sadm_get_one_second` @ tm.c:12756 — getter, tmOnuRegRead(5)
- [fn-899] `sadm_set_indacs_cmd` @ tm.c:12784 — setter, tmOnuRegWrite(6)
- [fn-900] `sadm_get_indacs_cmd` @ tm.c:12829 — getter, tmOnuRegRead(6)
- [fn-901] `sadm_get_indacs_done` @ tm.c:12865 — getter, tmOnuRegRead(7)
- [fn-902] `sadm_set_indacs_dat` @ tm.c:12893 — setter, tmOnuRegWrite(8)
- [fn-903] `sadm_get_indacs_dat` @ tm.c:12920 — getter, tmOnuRegRead(8)
- [fn-904] `sadm_set_bucket_overspeed_threshold` @ tm.c:12960 — setter, tmOnuRegWrite(9)
- [fn-905] `sadm_get_bucket_overspeed_threshold` @ tm.c:12990 — getter, tmOnuRegRead(9)
- [fn-906] `sadm_set_bucket_overspeed_en` @ tm.c:13018 — setter, tmOnuRegWrite(10), tmOnuRegRead(10)
- [fn-907] `sadm_get_bucket_overspeed_en` @ tm.c:13077 — getter, tmOnuRegRead(10)
- [fn-908] `sadm_set_spend_byte` @ tm.c:13115 — setter, tmOnuRegWrite(0xb)
- [fn-909] `sadm_get_spend_byte` @ tm.c:13144 — getter, tmOnuRegRead(0xb)
- [fn-910] `sadm_set_bucket_fill_time` @ tm.c:13172 — setter, tmOnuRegWrite(0xc)
- [fn-911] `sadm_get_bucket_fill_time` @ tm.c:13206 — getter, tmOnuRegRead(0xc)
- [fn-912] `sadm_set_brgunsapt_pps_pktnum` @ tm.c:13234 — setter, tmOnuRegWrite(0xd)
- [fn-913] `sadm_get_brgunsapt_pps_pktnum` @ tm.c:13266 — getter, tmOnuRegRead(0xd)
- [fn-914] `sadm_set_brgunsapt_pps_en` @ tm.c:13305 — setter, tmOnuRegWrite(0xe)
- [fn-915] `sadm_get_brgunsapt_pps_en` @ tm.c:13340 — getter, tmOnuRegRead(0xe)
- [fn-916] `sadm_set_brgun_unidapt_pps_pktnum` @ tm.c:13379 — setter, tmOnuRegWrite(0xf)
- [fn-917] `sadm_get_brgun_unidapt_pps_pktnum` @ tm.c:13412 — getter, tmOnuRegRead(0xf)
- [fn-918] `sadm_set_brgun_unidapt_pps_en` @ tm.c:13451 — setter, tmOnuRegWrite(0x10)
- [fn-919] `sadm_get_brgun_unidapt_pps_en` @ tm.c:13486 — getter, tmOnuRegRead(0x10)
- [fn-920] `sadm_set_brgun_muldapt_pps_pktnum` @ tm.c:13530 — setter, tmOnuRegWrite(0x11)
- [fn-921] `sadm_get_brgun_muldapt_pps_pktnum` @ tm.c:13563 — getter, tmOnuRegRead(0x11)
- [fn-922] `sadm_set_brgun_muldapt_pps_en` @ tm.c:13602 — setter, tmOnuRegWrite(0x12)
- [fn-923] `sadm_get_brgun_muldapt_pps_en` @ tm.c:13637 — getter, tmOnuRegRead(0x12)
- [fn-924] `sadm_set_up_tf_mode` @ tm.c:13681 — setter, tmOnuRegWrite(0x13)
- [fn-925] `sadm_get_up_tf_mode` @ tm.c:13708 — getter, tmOnuRegRead(0x13)
- [fn-926] `sadm_set_dn_tf_mode` @ tm.c:13742 — setter, tmOnuRegWrite(0x14)
- [fn-927] `sadm_get_dn_tf_mode` @ tm.c:13769 — getter, tmOnuRegRead(0x14)
- [fn-928] `sadm_get_statistics` @ tm.c:13803 — getter, fpga_read_reg(0xe1080)
- [fn-929] `sadm_access_timeout` @ tm.c:13889 — ~34 lines body
- [fn-930] `sadm_set_indreg_wr_cfg` @ tm.c:13923 — setter
- [fn-931] `sadm_set_indreg_rd_cfg` @ tm.c:13939 — setter
- [fn-932] `sadm_set_indtbl_flow_tfcfg_table` @ tm.c:13955 — setter
- [fn-933] `sadm_get_indtbl_flow_tfcfg_table` @ tm.c:14034 — getter
- [fn-934] `sadm_set_indtbl_ip_vlan_tfcfg_table` @ tm.c:14119 — setter
- [fn-935] `sadm_get_indtbl_ip_vlan_tfcfg_table` @ tm.c:14170 — getter
- [fn-936] `sadm_set_indtbl_token_bucket_fill_spd` @ tm.c:14217 — setter
- [fn-937] `sadm_get_indtbl_token_bucket_fill_spd` @ tm.c:14292 — getter
- [fn-938] `sadm_set_ip_vlan_token_bucket_fill_spd` @ tm.c:14381 — setter
- [fn-939] `sadm_get_ip_vlan_token_bucket_fill_spd` @ tm.c:14429 — getter
- [fn-940] `sadm_set_indtbl_token_bucket_capacity` @ tm.c:14476 — setter
- [fn-941] `sadm_get_indtbl_token_bucket_capacity` @ tm.c:14561 — getter
- [fn-942] `sadm_set_ip_vlan_token_bucket_capacity` @ tm.c:14645 — setter
- [fn-943] `sadm_get_ip_vlan_token_bucket_capacity` @ tm.c:14690 — getter
- [fn-944] `sadm_sadmtable_print` @ tm.c:14738 — printk:"%-5d%-18d%-16d", tmOnuRegWrite(6), tmOnuRegRead(7)
- [fn-945] `sipc_set_rx_en` @ tm.c:20552 — setter, tmOnuRegWrite(0)
- [fn-946] `sipc_get_rx_en` @ tm.c:20581 — getter, tmOnuRegRead(0)
- [fn-947] `sipc_set_cpu_up_en` @ tm.c:20610 — setter, tmOnuRegWrite(1)
- [fn-948] `sipc_get_cpu_up_en` @ tm.c:20639 — getter, tmOnuRegRead(1)
- [fn-949] `smac_set_tfe` @ tm.c:20750 — setter, tmOnuRegWrite(3)
- [fn-950] `smac_get_tfe` @ tm.c:20793 — getter, tmOnuRegRead(3)
- [fn-951] `smac_set_efc` @ tm.c:20832 — setter, tmOnuRegWrite(7)
- [fn-952] `smac_get_efc` @ tm.c:20875 — getter, tmOnuRegRead(7)
- [fn-953] `smac_set_pt` @ tm.c:20914 — setter, tmOnuRegWrite(4)
- [fn-954] `smac_get_pt` @ tm.c:20952 — getter, tmOnuRegRead(4)
- [fn-955] `smac_set_dzpq` @ tm.c:20991 — setter, tmOnuRegWrite(5)
- [fn-956] `smac_set_pr` @ tm.c:21034 — setter, tmOnuRegWrite(2)
- [fn-957] `smac_set_ipg` @ tm.c:21077 — setter, tmOnuRegWrite(0)
- [fn-958] `smac_set_rfa` @ tm.c:21120 — setter, tmOnuRegWrite(8)
- [fn-959] `smac_set_rfd` @ tm.c:21163 — setter, tmOnuRegWrite(9)
- [fn-960] `smac_set_timestamp_control` @ tm.c:21206 — setter, tmOnuRegWrite(10)
- [fn-961] `smac_set_tsf_mode` @ tm.c:21254 — setter, tmOnuRegWrite(0xb)
- [fn-962] `smac_set_rsf_mode` @ tm.c:21297 — setter, tmOnuRegWrite(0xc)
- [fn-963] `smac_set_cnt_rst` @ tm.c:21340 — setter, tmOnuRegWrite(0xd)
- [fn-964] `smac_get_statistics` @ tm.c:21383 — getter
- [fn-965] `smac_get_stat` @ tm.c:21419 — getter
- [fn-966] `smac_set_rfe` @ tm.c:21563 — setter, tmOnuRegWrite(6)
- [fn-967] `greg_set_soam_int_req` @ tm.c:21606 — setter, tmOnuRegWrite(0)
- [fn-968] `greg_get_soam_int_req` @ tm.c:21633 — getter, tmOnuRegRead(0)
- [fn-969] `greg_set_ptp_int_req` @ tm.c:21657 — setter, tmOnuRegWrite(1)
- [fn-970] `greg_get_ptp_int_req` @ tm.c:21684 — getter, tmOnuRegRead(1)
- [fn-971] `greg_set_mci_inir` @ tm.c:21708 — setter
- [fn-972] `greg_get_mci_inir` @ tm.c:21742 — getter
- [fn-973] `greg_set_lpi_inir` @ tm.c:21768 — setter
- [fn-974] `greg_get_lpi_inir` @ tm.c:21802 — getter
- [fn-975] `greg_set_soam_int_mask` @ tm.c:21828 — setter, tmOnuRegWrite(0xc)
- [fn-976] `greg_get_soam_int_mask` @ tm.c:21848 — getter, tmOnuRegRead(0xc)
- [fn-977] `greg_set_ptp_int_mask` @ tm.c:21872 — setter, tmOnuRegWrite(0xd)
- [fn-978] `greg_get_ptp_int_mask` @ tm.c:21892 — getter, tmOnuRegRead(0xd)
- [fn-979] `greg_set_mci_int_mask` @ tm.c:21916 — setter
- [fn-980] `greg_get_mci_int_mask` @ tm.c:21943 — getter
- [fn-981] `greg_set_lpi_int_mask` @ tm.c:21974 — setter
- [fn-982] `greg_get_lpi_int_mask` @ tm.c:22001 — getter
- [fn-983] `greg_set_soam_ram_init` @ tm.c:22032 — setter, tmOnuRegWrite(0x18)
- [fn-984] `greg_set_opc_ram_init` @ tm.c:22059 — setter, tmOnuRegWrite(0x19)
- [fn-985] `greg_set_smct_ram_init` @ tm.c:22086 — setter, tmOnuRegWrite(0x1a)
- [fn-986] `greg_set_spa_ram_init` @ tm.c:22113 — setter, tmOnuRegWrite(0x1b)
- [fn-987] `greg_set_port_stp_en` @ tm.c:22167 — setter
- [fn-988] `greg_get_port_stp_en` @ tm.c:22202 — getter
- [fn-989] `greg_set_port_sel_stp_rstp` @ tm.c:22229 — setter
- [fn-990] `greg_get_port_sel_stp_rstp` @ tm.c:22264 — getter
- [fn-991] `greg_set_port_stp_rstp_status` @ tm.c:22291 — setter
- [fn-992] `greg_get_port_stp_rstp_status` @ tm.c:22331 — getter
- [fn-993] `greg_set_port_need_authen` @ tm.c:22358 — setter
- [fn-994] `greg_get_port_need_authen` @ tm.c:22394 — getter
- [fn-995] `greg_set_port_closed` @ tm.c:22421 — setter
- [fn-996] `greg_get_port_closed` @ tm.c:22456 — getter
- [fn-997] `greg_set_one_step_mode` @ tm.c:22483 — setter, tmOnuRegWrite(0x40), tmOnuRegRead(0x40)
- [fn-998] `greg_set_oam_mode` @ tm.c:22526 — setter, tmOnuRegWrite(0x41)
- [fn-999] `greg_get_oam_mode` @ tm.c:22552 — getter, tmOnuRegRead(0x41)
- [fn-1000] `greg_set_oam_action` @ tm.c:22572 — setter, tmOnuRegWrite(0x42)
- [fn-1001] `greg_get_oam_action` @ tm.c:22599 — getter, tmOnuRegRead(0x42)
- [fn-1002] `greg_set_tm_oam_en` @ tm.c:22619 — setter, tmOnuRegWrite(0x43)
- [fn-1003] `greg_set_gap_add` @ tm.c:22645 — setter, tmOnuRegWrite(0x44)
- [fn-1004] `sdet_set_maxframe_length` @ tm.c:24470 — setter
- [fn-1005] `sdet_get_maxframe_length` @ tm.c:24504 — getter
- [fn-1006] `sdet_set_minframe_length` @ tm.c:24545 — setter, tmOnuRegWrite(5)
- [fn-1007] `sdet_get_minframe_length` @ tm.c:24576 — getter, tmOnuRegRead(5)
- [fn-1008] `sdet_set_uni_pmp_vid_vld` @ tm.c:24605 — setter, tmOnuRegWrite(6)
- [fn-1009] `sdet_get_uni_pmp_vid_vld` @ tm.c:24642 — getter, tmOnuRegRead(6)
- [fn-1010] `sdet_set_uni_pmp_vid` @ tm.c:24683 — setter, tmOnuRegWrite(7)
- [fn-1011] `sdet_get_uni_pmp_vid` @ tm.c:24717 — getter, tmOnuRegRead(7)
- [fn-1012] `sdet_set_uni_omp_vid_vld` @ tm.c:24758 — setter, tmOnuRegWrite(8)
- [fn-1013] `sdet_get_uni_omp_vid_vld` @ tm.c:24795 — getter, tmOnuRegRead(8)
- [fn-1014] `sdet_set_uni_omp_vid` @ tm.c:24836 — setter, tmOnuRegWrite(9)
- [fn-1015] `sdet_get_uni_omp_vid` @ tm.c:24870 — getter, tmOnuRegRead(9)
- [fn-1016] `sdet_set_soft_vid` @ tm.c:24911 — setter, tmOnuRegWrite(0xd)
- [fn-1017] `sdet_get_soft_vld` @ tm.c:24957 — getter, tmOnuRegRead(0xd)
- [fn-1018] `sdet_set_soft_vid_vld` @ tm.c:25003 — setter, tmOnuRegWrite(0xc)
- [fn-1019] `sdet_get_soft_vid_vld` @ tm.c:25046 — getter, tmOnuRegRead(0xd)
- [fn-1020] `sdet_set_c_tpid` @ tm.c:25092 — setter, tmOnuRegWrite(0xe)
- [fn-1021] `sdet_get_c_tpid` @ tm.c:25121 — getter, tmOnuRegRead(0xe)
- [fn-1022] `sdet_set_smac_md_level` @ tm.c:25161 — setter, tmOnuRegWrite(0xf)
- [fn-1023] `sdet_get_smac_md_level` @ tm.c:25198 — getter, tmOnuRegRead(0xf)
- [fn-1024] `sdet_set_down_maxframe_length` @ tm.c:25239 — setter, tmOnuRegWrite(0x10)
- [fn-1025] `sdet_get_down_maxframe_length` @ tm.c:25270 — getter, tmOnuRegRead(0x10)
- [fn-1026] `sdet_set_soam_drop_en` @ tm.c:25299 — setter, tmOnuRegWrite(0x11), tmOnuRegRead(0x11)
- [fn-1027] `sdet_get_soam_drop_en` @ tm.c:25347 — getter, tmOnuRegRead(0x11)
- [fn-1028] `smct_get_uni_pmau` @ tm.c:25388 — getter, tmOnuRegRead(0)
- [fn-1029] `smct_set_uni_pmau` @ tm.c:25417 — setter, tmOnuRegWrite(0)
- [fn-1030] `smct_get_pp_pmau` @ tm.c:25446 — getter, tmOnuRegRead(1)
- [fn-1031] `smct_set_pp_pmau` @ tm.c:25475 — setter, tmOnuRegWrite(1)
- [fn-1032] `smct_get_ppmove_pmau` @ tm.c:25504 — getter, tmOnuRegRead(2)
- [fn-1033] `smct_set_ppmove_pmau` @ tm.c:25533 — setter, tmOnuRegWrite(2)
- [fn-1034] `sopc_set_crc_pad_cfg` @ tm.c:25563 — setter
- [fn-1035] `sopc_get_crc_pad_cfg` @ tm.c:25592 — getter
- [fn-1036] `sopc_set_smac_delay_cnt_cfg` @ tm.c:25633 — setter, tmOnuRegWrite(5)
- [fn-1037] `sopc_get_smac_delay_cnt_cfg` @ tm.c:25664 — getter, tmOnuRegRead(5)
- [fn-1038] `sopc_set_smac_half_mode` @ tm.c:25693 — setter, tmOnuRegWrite(6), tmOnuRegRead(6)
- [fn-1039] `sopc_get_smac_half_mode` @ tm.c:25741 — getter, tmOnuRegRead(6)
- [fn-1040] `sopc_set_smac_ready_mode` @ tm.c:25782 — setter, tmOnuRegWrite(7), tmOnuRegRead(7)
- [fn-1041] `sopc_get_smac_ready_mode` @ tm.c:25830 — getter, tmOnuRegRead(7)
- [fn-1042] `opc_top_set_sp_rr_cfg` @ tm.c:25871 — setter, tmOnuRegWrite(8)
- [fn-1043] `opc_top_get_sp_rr_cfg` @ tm.c:25902 — getter, tmOnuRegRead(7)
- [fn-1044] `spa_set_indirect_rw_cmd` @ tm.c:25931 — setter, tmOnuRegWrite(4)
- [fn-1045] `spa_get_indirect_rw_status` @ tm.c:25969 — getter, tmOnuRegRead(5)
- [fn-1046] `spa_set_indirect_rw_data` @ tm.c:25998 — setter, tmOnuRegWrite(6)
- [fn-1047] `spa_set_hashram` @ tm.c:26027 — setter
- [fn-1048] `spa_get_indirect_rw_data` @ tm.c:26088 — getter, tmOnuRegRead(6)
- [fn-1049] `spa_set_up_reg_pkt_en` @ tm.c:26269 — setter
- [fn-1050] `spa_set_dn_reg_pkt_en` @ tm.c:26320 — setter, tmOnuRegWrite(1), tmOnuRegRead(1)
- [fn-1051] `spa_set_up_reg_pps_en` @ tm.c:26371 — setter, tmOnuRegWrite(2), tmOnuRegRead(2)
- [fn-1052] `spa_set_dn_reg_pps_en` @ tm.c:26414 — setter, tmOnuRegWrite(3), tmOnuRegRead(3)
- [fn-1053] `spa_set_stp_action` @ tm.c:26457 — setter, tmOnuRegWrite(7)
- [fn-1054] `spa_set_pt_bpdu_trap_en` @ tm.c:26483 — setter, tmOnuRegWrite(8), tmOnuRegRead(8)
- [fn-1055] `spa_get_pt_bpdu_trap_en` @ tm.c:26525 — getter, tmOnuRegRead(8)
- [fn-1056] `spa_set_pt_802x_trap_en` @ tm.c:26566 — setter, tmOnuRegWrite(9), tmOnuRegRead(9)
- [fn-1057] `spa_get_pt_802x_trap_en` @ tm.c:26608 — getter, tmOnuRegRead(9)
- [fn-1058] `spa_set_port_dft_pri` @ tm.c:26649 — setter
- [fn-1059] `spa_get_port_dft_pri` @ tm.c:26679 — getter
- [fn-1060] `spa_set_match_mode` @ tm.c:26713 — setter, tmOnuRegWrite(0x12)
- [fn-1061] `spa_set_match_rep_en` @ tm.c:26739 — setter, tmOnuRegWrite(0x13)
- [fn-1062] `spa_set_color_mode` @ tm.c:26765 — setter, tmOnuRegWrite(0x14), tmOnuRegRead(0x14)
- [fn-1063] `spa_get_color_mode` @ tm.c:26801 — getter, tmOnuRegRead(0x14)
- [fn-1064] `spa_set_loopback_en` @ tm.c:26842 — setter, tmOnuRegWrite(0x15)
- [fn-1065] `spa_set_onu_mac_addr` @ tm.c:26868 — setter, tmOnuRegWrite(0x16)
- [fn-1066] `spa_get_onu_mac_addr` @ tm.c:26906 — getter, tmOnuRegRead(0x16)
- [fn-1067] `spa_set_trap_dmac` @ tm.c:26958 — setter, tmOnuRegWrite(0x18)
- [fn-1068] `spa_get_trap_dmac` @ tm.c:26996 — getter, tmOnuRegRead(0x18)
- [fn-1069] `spa_set_trap_protocol_type0` @ tm.c:27048 — setter, tmOnuRegWrite(0x1a)
- [fn-1070] `spa_get_trap_protocol_type0` @ tm.c:27076 — getter, tmOnuRegRead(0x1a)
- [fn-1071] `spa_set_trap_protocol_type1` @ tm.c:27099 — setter, tmOnuRegWrite(0x1b)
- [fn-1072] `spa_get_trap_protocol_type1` @ tm.c:27127 — getter, tmOnuRegRead(0x1b)
- [fn-1073] `spa_set_trap_protocol_type2` @ tm.c:27150 — setter, tmOnuRegWrite(0x1c)
- [fn-1074] `spa_get_trap_protocol_type2` @ tm.c:27178 — getter, tmOnuRegRead(0x1c)
- [fn-1075] `spa_set_trap_protocol_type3` @ tm.c:27201 — setter, tmOnuRegWrite(0x1d)
- [fn-1076] `spa_get_trap_protocol_type3` @ tm.c:27229 — getter, tmOnuRegRead(0x1d)
- [fn-1077] `spa_set_trap_eth_type0` @ tm.c:27252 — setter, tmOnuRegWrite(0x1e)
- [fn-1078] `spa_get_trap_eth_type0` @ tm.c:27279 — getter, tmOnuRegRead(0x1e)
- [fn-1079] `spa_set_trap_eth_type1` @ tm.c:27302 — setter, tmOnuRegWrite(0x1f)
- [fn-1080] `spa_get_trap_eth_type1` @ tm.c:27329 — getter, tmOnuRegRead(0x1f)
- [fn-1081] `spa_set_trap_eth_type2` @ tm.c:27352 — setter, tmOnuRegWrite(0x20)
- [fn-1082] `spa_get_trap_eth_type2` @ tm.c:27379 — getter, tmOnuRegRead(0x20)
- [fn-1083] `spa_set_trap_eth_type3` @ tm.c:27402 — setter, tmOnuRegWrite(0x21)
- [fn-1084] `spa_get_trap_eth_type3` @ tm.c:27429 — getter, tmOnuRegRead(0x21)
- [fn-1085] `spa_set_tpid_i_sel_i` @ tm.c:27452 — setter
- [fn-1086] `spa_get_tpid_i_sel_i` @ tm.c:27494 — getter
- [fn-1087] `spa_set_pon_untag_svid` @ tm.c:27538 — setter, tmOnuRegWrite(0x32)
- [fn-1088] `spa_get_pon_untag_svid` @ tm.c:27564 — getter, tmOnuRegRead(0x32)
- [fn-1089] `spa_set_pon_untag_pri` @ tm.c:27593 — setter, tmOnuRegWrite(0x33)
- [fn-1090] `spa_get_pon_untag_pri` @ tm.c:27619 — getter, tmOnuRegRead(0x33)
- [fn-1091] `spa_set_cpu_untag_svid` @ tm.c:27648 — setter, tmOnuRegWrite(0x34)
- [fn-1092] `spa_get_cpu_untag_svid` @ tm.c:27674 — getter, tmOnuRegRead(0x34)
- [fn-1093] `spa_set_cpu_untag_pri` @ tm.c:27703 — setter, tmOnuRegWrite(0x35)
- [fn-1094] `spa_get_cpu_untag_pri` @ tm.c:27729 — getter, tmOnuRegRead(0x35)
- [fn-1095] `spa_set_port_up_untag_pvid` @ tm.c:27758 — setter, tmOnuRegWrite(0x36)
- [fn-1096] `spa_get_port_up_untag_pvid` @ tm.c:27790 — getter, tmOnuRegRead(0x36)
- [fn-1097] `spa_set_port_up_untag_svid` @ tm.c:27831 — setter, tmOnuRegWrite(0x37)
- [fn-1098] `spa_get_port_up_untag_svid` @ tm.c:27863 — getter, tmOnuRegRead(0x37)
- [fn-1099] `spa_set_port_up_untag_pri` @ tm.c:27904 — setter, tmOnuRegWrite(0x38)
- [fn-1100] `spa_get_port_up_untag_pri` @ tm.c:27939 — getter, tmOnuRegRead(0x38)
- [fn-1101] `spa_set_port_pkt_filter` @ tm.c:27980 — setter
- [fn-1102] `spa_get_port_pkt_filter` @ tm.c:28013 — getter
- [fn-1103] `spa_set_port_vlan_filter` @ tm.c:28059 — setter, tmOnuRegWrite(0x42)
- [fn-1104] `spa_get_port_vlan_filter` @ tm.c:28092 — getter, tmOnuRegRead(0x42)
- [fn-1105] `spa_set_enty_pktdeal_cfg` @ tm.c:28133 — setter
- [fn-1106] `spa_get_enty_pktdeal_cfg` @ tm.c:28167 — getter
- [fn-1107] `spa_set_enty_pon_other_pktdeal_cfg` @ tm.c:28222 — setter
- [fn-1108] `spa_get_enty_pon_other_pktdeal_cfg` @ tm.c:28256 — getter
- [fn-1109] `spa_get_statistics` @ tm.c:28302 — getter, fpga_read_reg(0x75178)
- [fn-1110] `spa_get_matchram` @ tm.c:28400 — getter
- [fn-1111] `spa_print_match_ram` @ tm.c:28564 — ~19 lines body
- [fn-1112] `spa_get_hashram` @ tm.c:28583 — getter
- [fn-1113] `uopc_set_tcont_num` @ tm.c:28663 — setter, tmOnuRegWrite(1), tmOnuRegRead(0)
- [fn-1114] `uopc_get_tcont_num` @ tm.c:28714 — getter, tmOnuRegRead(1)
- [fn-1115] `uopc_set_tcont_sch_active_ena` @ tm.c:28737 — setter, tmOnuRegWrite(2)
- [fn-1116] `uopc_get_tcont_sch_active_ena` @ tm.c:28766 — getter, tmOnuRegRead(2)
- [fn-1117] `uopc_set_mac_ept_resume_ena` @ tm.c:28789 — setter, tmOnuRegWrite(3)
- [fn-1118] `uopc_get_mac_ept_resume_ena` @ tm.c:28818 — getter, tmOnuRegRead(3)
- [fn-1119] `uopc_set_tcont_syn_ena` @ tm.c:28841 — setter, tmOnuRegWrite(4)
- [fn-1120] `uopc_get_tcont_syn_ena` @ tm.c:28869 — getter, tmOnuRegRead(4)

## PP block helpers (adm, dpa, pp_*, tm_protocol) (42)

Admission control, deep-packet analyzer, packet-processor general regs, per-protocol PPS limiter.

- [fn-1121] `dpa_get_protocol_pkt_aly_en` @ tm.c:14961 — getter
- [fn-1122] `dpa_get_protocol_cpu_pps_en` @ tm.c:15029 — getter, tmOnuRegRead(7)
- [fn-1123] `dpa_set_pon_detault_pri` @ tm.c:15053 — setter, tmOnuRegWrite(8)
- [fn-1124] `dpa_get_pon_detault_pri` @ tm.c:15081 — getter, tmOnuRegRead(8)
- [fn-1125] `dpa_get_tpid_i_sel_i` @ tm.c:15147 — getter
- [fn-1126] `adm_get_turnon_enable` @ tm.c:16591 — getter, tmOnuRegRead(0)
- [fn-1127] `adm_set_color_enable` @ tm.c:16622 — setter, tmOnuRegWrite(2)
- [fn-1128] `adm_get_color_enable` @ tm.c:16649 — getter, tmOnuRegRead(2)
- [fn-1129] `adm_set_credit_cmp_mode` @ tm.c:16672 — setter, tmOnuRegWrite(1)
- [fn-1130] `adm_get_credit_cmp_mode` @ tm.c:16700 — getter, tmOnuRegRead(1)
- [fn-1131] `adm_set_flow_stc_mode` @ tm.c:16731 — setter, tmOnuRegWrite(3)
- [fn-1132] `adm_get_flow_stc_mode` @ tm.c:16759 — getter, tmOnuRegRead(3)
- [fn-1133] `adm_set_bucket_fill_time` @ tm.c:16784 — setter, tmOnuRegWrite(4)
- [fn-1134] `adm_get_bucket_fill_time` @ tm.c:16812 — getter, tmOnuRegRead(4)
- [fn-1135] `adm_set_indirect_rw_cmd` @ tm.c:16837 — setter, tmOnuRegWrite(5)
- [fn-1136] `adm_get_indirect_rw_cmd` @ tm.c:16884 — getter, tmOnuRegRead(5)
- [fn-1137] `adm_get_ind_acc_done` @ tm.c:16915 — getter, tmOnuRegRead(6)
- [fn-1138] `adm_set_ind_acc_data` @ tm.c:16948 — setter, tmOnuRegWrite(7)
- [fn-1139] `adm_get_ind_acc_data` @ tm.c:16975 — getter, tmOnuRegRead(7)
- [fn-1140] `adm_set_spend_byte_cfg` @ tm.c:17015 — setter, tmOnuRegWrite(8)
- [fn-1141] `adm_get_spend_byte_cfg` @ tm.c:17043 — getter, tmOnuRegRead(8)
- [fn-1142] `adm_set_protocol_pkt_map` @ tm.c:17068 — setter, tmOnuRegWrite(10), tmOnuRegRead(10)
- [fn-1143] `adm_get_protocol_pkt_map` @ tm.c:17122 — getter
- [fn-1144] `adm_set_policing_enable` @ tm.c:17197 — setter
- [fn-1145] `adm_get_policing_enable` @ tm.c:17236 — getter
- [fn-1146] `adm_set_pass_pktcnt_persec` @ tm.c:17296 — setter
- [fn-1147] `adm_get_pass_pktcnt_persec` @ tm.c:17338 — getter
- [fn-1148] `adm_get_up_pass_protocal_packtcnt` @ tm.c:17396 — getter, tmOnuRegRead(0x11)
- [fn-1149] `adm_get_dn_pass_protocal_packtcnt` @ tm.c:17436 — getter, tmOnuRegRead(0x10)
- [fn-1150] `adm_get_up_drop_protocal_packtcnt` @ tm.c:17476 — getter, tmOnuRegRead(0x13)
- [fn-1151] `adm_get_dn_drop_protocal_packtcnt` @ tm.c:17516 — getter, tmOnuRegRead(0x12)
- [fn-1152] `adm_get_down_drop_protocol_pktcnt` @ tm.c:17556 — getter, tmOnuRegRead(0x14)
- [fn-1153] `adm_get_up_drop_protocol_pktcnt` @ tm.c:17581 — getter, tmOnuRegRead(0x15)
- [fn-1154] `adm_set_bucket_c` @ tm.c:17606 — setter
- [fn-1155] `adm_get_bucket_c` @ tm.c:17665 — getter
- [fn-1156] `adm_set_bucket_e` @ tm.c:17760 — setter
- [fn-1157] `adm_get_bucket_e` @ tm.c:17830 — getter
- [fn-1158] `adm_get_pkt_stastc` @ tm.c:17922 — getter
- [fn-1159] `adm_indirect_ram_print` @ tm.c:18021 — ~58 lines body
- [fn-1160] `tm_protocol_pkt_limit_map_get` @ tm.c:40408 — getter
- [fn-1161] `tm_protocol_pkt_limit_pps_get` @ tm.c:40930 — getter
- [fn-1162] `pp_adm_onesecond` @ tm.c:57743 — fpga_write_reg(0xe5012)

## PON block helpers (pon_*) (54)

PON-direction TM helpers (gap, ageing, IRQ masks). Many are mirror-functions of TM counterparts but for the PON port.

- [fn-1163] `pon_pp_get_6rd_sip` @ tm.c:15191 — getter, tmOnuRegRead(0x14)
- [fn-1164] `pon_pp_set_6rd_sip` @ tm.c:15238 — setter, tmOnuRegWrite(0x14)
- [fn-1165] `pon_pp_get_brg_int_state` @ tm.c:15269 — getter, tmOnuRegRead(0)
- [fn-1166] `pon_pp_set_brg_int_mask` @ tm.c:15298 — setter, tmOnuRegWrite(1)
- [fn-1167] `pon_pp_get_brg_int_mask` @ tm.c:15323 — getter, tmOnuRegRead(1)
- [fn-1168] `pon_pp_set_step_en` @ tm.c:15348 — setter, tmOnuRegWrite(2), tmOnuRegRead(2)
- [fn-1169] `pon_pp_get_step_en` @ tm.c:15406 — getter, tmOnuRegRead(2)
- [fn-1170] `pon_pp_set_step_pro_sel` @ tm.c:15446 — setter, tmOnuRegWrite(3), tmOnuRegRead(3)
- [fn-1171] `pon_pp_get_step_pro_sel` @ tm.c:15504 — getter, tmOnuRegRead(3)
- [fn-1172] `pon_pp_get_step_status` @ tm.c:15544 — getter, tmOnuRegRead(4)
- [fn-1173] `pon_pp_set_port_auth_en` @ tm.c:15573 — setter, tmOnuRegWrite(5), tmOnuRegRead(5)
- [fn-1174] `pon_pp_get_port_auth_en` @ tm.c:15631 — getter, tmOnuRegRead(5)
- [fn-1175] `pon_pp_set_port_close_en` @ tm.c:15671 — setter, tmOnuRegWrite(6), tmOnuRegRead(6)
- [fn-1176] `pon_pp_get_port_close_en` @ tm.c:15729 — getter, tmOnuRegRead(6)
- [fn-1177] `pon_pp_set_mult_mac_tran_en` @ tm.c:15769 — setter, tmOnuRegWrite(7)
- [fn-1178] `pon_pp_get_mult_mac_tran_en` @ tm.c:15798 — getter, tmOnuRegRead(7)
- [fn-1179] `pon_pp_get_mult_mode` @ tm.c:15866 — getter
- [fn-1180] `pon_pp_set_read_clean_en` @ tm.c:15911 — setter, tmOnuRegWrite(10)
- [fn-1181] `pon_pp_get_read_clean_en` @ tm.c:15940 — getter, tmOnuRegRead(10)
- [fn-1182] `pon_pp_set_no_crc_en` @ tm.c:15969 — setter, tmOnuRegWrite(0xb)
- [fn-1183] `pon_pp_get_no_crc_en` @ tm.c:15997 — getter, tmOnuRegRead(0xb)
- [fn-1184] `pon_pp_get_jumb_len` @ tm.c:16055 — getter, tmOnuRegRead(0xc)
- [fn-1185] `pon_pp_set_port_up_en` @ tm.c:16084 — setter, tmOnuRegWrite(0xd), tmOnuRegRead(0xd)
- [fn-1186] `pon_pp_get_port_up_en` @ tm.c:16142 — getter, tmOnuRegRead(0xd)
- [fn-1187] `pon_pp_get_acl_base_addr` @ tm.c:16258 — getter, tmOnuRegRead(0xf)
- [fn-1188] `pon_pp_set_wifi_mac_len` @ tm.c:16287 — setter, tmOnuRegWrite(0x10)
- [fn-1189] `pon_pp_get_wifi_mac_len` @ tm.c:16316 — getter, tmOnuRegRead(0x10)
- [fn-1190] `pon_pp_get_tpid` @ tm.c:16377 — getter, tmOnuRegRead(0x11)
- [fn-1191] `pon_pp_set_dslite_flow_lable` @ tm.c:16417 — setter, tmOnuRegWrite(0x12)
- [fn-1192] `pon_pp_get_dslite_flow_lable` @ tm.c:16448 — getter, tmOnuRegRead(0x12)
- [fn-1193] `pon_pp_set_dslite_traffclass_hoplimit` @ tm.c:16487 — setter, tmOnuRegWrite(0x13)
- [fn-1194] `pon_pp_get_dslite_traffclass_hoplimit` @ tm.c:16519 — getter, tmOnuRegRead(0x13)
- [fn-1195] `pon_tm_set_read_clean_en` @ tm.c:34463 — setter, tmOnuRegWrite(0)
- [fn-1196] `pon_tm_get_read_clean_en` @ tm.c:34494 — getter, tmOnuRegRead(0)
- [fn-1197] `pon_tm_get_gap_add` @ tm.c:34550 — getter, tmOnuRegRead(0)
- [fn-1198] `pon_tm_set_bp_base_addr` @ tm.c:34579 — setter, tmOnuRegWrite(2)
- [fn-1199] `pon_tm_get_bp_base_addr` @ tm.c:34602 — getter, tmOnuRegRead(2)
- [fn-1200] `pon_tm_set_jum_bp_base_addr` @ tm.c:34630 — setter, tmOnuRegWrite(3)
- [fn-1201] `pon_tm_get_jum_bp_base_addr` @ tm.c:34654 — getter, tmOnuRegRead(3)
- [fn-1202] `pon_tm_set_desc_base_addr` @ tm.c:34682 — setter, tmOnuRegWrite(4)
- [fn-1203] `pon_tm_get_desc_base_addr` @ tm.c:34706 — getter, tmOnuRegRead(4)
- [fn-1204] `pon_tm_set_norm_data_base_addr` @ tm.c:34734 — setter, tmOnuRegWrite(5)
- [fn-1205] `pon_tm_get_norm_data_base_addr` @ tm.c:34758 — getter, tmOnuRegRead(5)
- [fn-1206] `pon_tm_set_jumbo_data_base_addr` @ tm.c:34786 — setter, tmOnuRegWrite(6)
- [fn-1207] `pon_tm_get_jumbo_data_base_addr` @ tm.c:34810 — getter, tmOnuRegRead(6)
- [fn-1208] `pon_tm_set_bp_slice_size` @ tm.c:34838 — setter, tmOnuRegWrite(7)
- [fn-1209] `pon_tm_get_bp_slice_size` @ tm.c:34871 — getter, tmOnuRegRead(7)
- [fn-1210] `pon_tm_get_queue_int_state` @ tm.c:34902 — getter, tmOnuRegRead(8)
- [fn-1211] `pon_tm_get_dma_des_int_state` @ tm.c:34939 — getter, tmOnuRegRead(9)
- [fn-1212] `pon_tm_get_fifo_int_state` @ tm.c:34976 — getter, tmOnuRegRead(10)
- [fn-1213] `pon_tm_get_queue_int_mask` @ tm.c:35077 — getter, tmOnuRegRead(0xb)
- [fn-1214] `pon_tm_get_dma_des_int_mask` @ tm.c:35172 — getter, tmOnuRegRead(0xc)
- [fn-1215] `pon_tm_get_fifo_int_mask` @ tm.c:35270 — getter, tmOnuRegRead(0xd)
- [fn-1216] `pon_dg_config_set` @ tm.c:43478 — setter, fpga_write_reg(0x10009)

## Mirror helpers (tm_mirror) (18)

Port-mirror configuration. ~18 functions; minor diagnostic feature, not on hot path.

- [fn-1217] `tm_mirror_globle_ena_set` @ tm.c:35608 — setter
- [fn-1218] `tm_mirror_ingress_ena_set` @ tm.c:39838 — setter
- [fn-1219] `tm_mirror_egress_ena_set` @ tm.c:39855 — setter
- [fn-1220] `tm_mirror_vlan_ena_set` @ tm.c:39872 — setter
- [fn-1221] `tm_mirror_pt_ena_set` @ tm.c:39888 — setter
- [fn-1222] `tm_mirror_gempt_ena_set` @ tm.c:39904 — setter
- [fn-1223] `tm_mirror_igsdrp_ena_set` @ tm.c:39920 — setter
- [fn-1224] `tm_mirror_vlan_id_set` @ tm.c:39936 — setter
- [fn-1225] `tm_mirror_capture_port_set` @ tm.c:39952 — setter
- [fn-1226] `tm_mirror_capture_port_get` @ tm.c:40000 — getter, printk:"ERROR:(%s:%d)"
- [fn-1227] `tm_mirror_globle_ena_get` @ tm.c:41788 — getter, printk:"ERROR:(%s:%d)"
- [fn-1228] `tm_mirror_ingress_ena_get` @ tm.c:41818 — getter, printk:"ERROR:(%s:%d)"
- [fn-1229] `tm_mirror_egress_ena_get` @ tm.c:41848 — getter, printk:"ERROR:(%s:%d)"
- [fn-1230] `tm_mirror_vlan_ena_get` @ tm.c:41878 — getter, printk:"ERROR:(%s:%d)"
- [fn-1231] `tm_mirror_pt_ena_get` @ tm.c:41908 — getter, printk:"ERROR:(%s:%d)"
- [fn-1232] `tm_mirror_gempt_ena_get` @ tm.c:41938 — getter, printk:"ERROR:(%s:%d)"
- [fn-1233] `tm_mirror_igsdrp_ena_get` @ tm.c:41968 — getter, printk:"ERROR:(%s:%d)"
- [fn-1234] `tm_mirror_vlan_id_get` @ tm.c:41998 — getter, printk:"ERROR:(%s:%d)"

## Configuration helpers (get_cfg / set_cfg pairs) (6)

Bit-packed config accessor pairs — analogous to [fn-04a/b] smac_{get,set}_cfg.

- [fn-1235] `sbrg_get_config` @ tm.c:12135 — getter, fpga_read_reg(0xe2070)
- [fn-1236] `red_set_cfg_enable` @ tm.c:33086 — setter, tmOnuRegWrite(0)
- [fn-1237] `red_get_cfg_enable` @ tm.c:33120 — getter, tmOnuRegRead(0)
- [fn-1238] `tm_sch_secsch_sp_dwrr_cfg_set` @ tm.c:41188 — setter
- [fn-1239] `tm_cla_outspace_cfg_set` @ tm.c:41482 — setter
- [fn-1240] `tm_cla_outspace_cfg_get` @ tm.c:42346 — getter, printk:"ERROR:(%s:%d)"

## Other tm_* helpers (51)

TM-namespaced helpers that didn't fit elsewhere — register dumps, wrappers around `tmOnuRegRead/Write`, soft-state DB ops.

- [fn-1241] `tmOnuRegReadNoCheck` @ tm.c:35380 — ~15 lines body
- [fn-1242] `tmOnuRegWriteNoCheck` @ tm.c:35395 — ~19 lines body
- [fn-1243] `tmOnuMiscRegWrite` @ tm.c:35414 — ~24 lines body
- [fn-1244] `tmOnuMiscRegRead` @ tm.c:35438 — ~19 lines body
- [fn-1245] `tm_pp_red_allcfgram_init` @ tm.c:35502 — ~44 lines body
- [fn-1246] `tm_tpid_set` @ tm.c:35572 — setter
- [fn-1247] `tm_stream_l3_mtu_set` @ tm.c:35736 — setter
- [fn-1248] `tm_out_port_tpid_select_set` @ tm.c:35768 — setter
- [fn-1249] `tm_set_pp_wan_cfg` @ tm.c:35962 — setter, fpga_write_reg(0xe8007)
- [fn-1250] `tm_set_p2pmode` @ tm.c:35979 — setter
- [fn-1251] `tm_oam_unmatch_mode_set` @ tm.c:36645 — setter
- [fn-1252] `tm_oam_unmatch_mode_get` @ tm.c:36680 — getter
- [fn-1253] `tm_tpid_get` @ tm.c:37994 — getter
- [fn-1254] `tm_in_port_tpid_select_set` @ tm.c:38022 — setter
- [fn-1255] `tm_in_port_tpid_select_get` @ tm.c:38173 — getter
- [fn-1256] `tm_out_port_tpid_select_get` @ tm.c:38333 — getter
- [fn-1257] `tm_stream_l3_mtu_get` @ tm.c:39724 — getter
- [fn-1258] `tm_smac_statistics1` @ tm.c:40058 — ~109 lines body
- [fn-1259] `tm_smac_statistics2` @ tm.c:40167 — ~74 lines body
- [fn-1260] `tm_smac_statistics3` @ tm.c:40241 — ~60 lines body
- [fn-1261] `tm_smac_statistics4` @ tm.c:40301 — ~61 lines body
- [fn-1262] `tm_onu_mac_addr_set` @ tm.c:41273 — setter, printk:"ERROR:(%s:%d)"
- [fn-1263] `tm_onu_mac_addr_get` @ tm.c:41365 — getter
- [fn-1264] `tm_get_up_drop_protocal_packtcnt` @ tm.c:41450 — getter
- [fn-1265] `tm_get_dn_drop_protocal_packtcnt` @ tm.c:41466 — getter
- [fn-1266] `tm_yellow_drop_cfg` @ tm.c:42370 — ~50 lines body
- [fn-1267] `tm_getFillcap.part.44` @ tm.c:42420 — ~16 lines body
- [fn-1268] `tm_getFillcap` @ tm.c:45353 — ~22 lines body
- [fn-1269] `tm_wifi_ssid_rate_limit_set` @ tm.c:45629 — setter
- [fn-1270] `tm_wifi_ssid_rate_limit_get` @ tm.c:45652 — getter
- [fn-1271] `tm_ip_bkt_rate_limit_set` @ tm.c:45759 — setter
- [fn-1272] `tm_ip_bkt_rate_limit_get` @ tm.c:45803 — getter
- [fn-1273] `tm_up_statistics_get` @ tm.c:46130 — getter, fpga_read_reg(0x7105e)
- [fn-1274] `tm_dn_statistics_get` @ tm.c:46455 — getter, fpga_read_reg(0x73001)
- [fn-1275] `tm_error_monitor` @ tm.c:46669 — fpga_read_reg(0x74014)
- [fn-1276] `tm_cla_cpu_queueid_set` @ tm.c:46817 — setter, printk:"ERROR:(%s:%d)"
- [fn-1277] `tm_cla_cpu_queueid_get` @ tm.c:46843 — getter, printk:"ERROR:(%s:%d)"
- [fn-1278] `tm_up_sch_sharp_total_cfg_print` @ tm.c:47449 — ~191 lines body
- [fn-1279] `tm_set_qnum_map_mode` @ tm.c:47985 — setter, printk:"ERROR:(%s:%d)"
- [fn-1280] `tm_get_qnum_map_mode` @ tm.c:48012 — getter, printk:"ERROR:(%s:%d)"
- [fn-1281] `tm_set_sbrg_pri_qtab_pon` @ tm.c:48039 — setter, printk:"ERROR:(%s:%d)"
- [fn-1282] `tm_get_sbrg_pri_qtab_pon` @ tm.c:48066 — getter, printk:"ERROR:(%s:%d)"
- [fn-1283] `tm_get_acl_flow_status` @ tm.c:54056 — getter
- [fn-1284] `tm_del_acl_flow_rule` @ tm.c:54092 — ~18 lines body
- [fn-1285] `tm_add_acl_flow_rule` @ tm.c:54261 — printk:"ERROR:(%s:%d)"
- [fn-1286] `tm_tpid_vlu_select_get` @ tm.c:58872 — getter
- [fn-1287] `tm_convert_value_to_name` @ tm.c:60031 — ~611 lines body
- [fn-1288] `tm_print_common_rule_config` @ tm.c:60642 — printk:" 0x%02x "
- [fn-1289] `tm_cla_get_parse_info` @ tm.c:60764 — getter, printk:"mask :"
- [fn-1290] `tm_cla_get_oper_info` @ tm.c:61985 — getter, printk:"SW_ACL_ACT_SET_IPV6_DIPV6value="
- [fn-1291] `tm_sysfs_delete` @ tm.c:69360 — ~29 lines body

## Cleanup / device-file ops (7)

`tm_cleanupModule` mirror of init; tm_dev* char-device file ops (read/write/open/release stub or trivial wrappers).

- [fn-1292] `tm_devRead` @ tm.c:1 — ~9 lines body
- [fn-1293] `tm_devWrite` @ tm.c:10 — ~9 lines body
- [fn-1294] `tm_devIoctl` @ tm.c:19 — ~71 lines body
- [fn-1295] `tm_devRelease` @ tm.c:90 — ~11 lines body
- [fn-1296] `tm_devOpen` @ tm.c:101 — ~19 lines body
- [fn-1297] `tm_devCleanup` @ tm.c:138 — ~11 lines body
- [fn-1298] `tm_cleanupModule` @ tm.c:69426 — ~11 lines body

## Miscellaneous / utility (36)

Glue, type-conversion helpers, CRC, and assorted leaves.

- [fn-1299] `CRC_32` @ tm.c:4105 — ~25 lines body
- [fn-1300] `CRC_16` @ tm.c:4130 — ~24 lines body
- [fn-1301] `qmg_get_up_ram_thd` @ tm.c:32733 — getter, tmOnuRegRead(0)
- [fn-1302] `qmg_get_dn_ram_thd` @ tm.c:32786 — getter, tmOnuRegRead(1)
- [fn-1303] `qmg_get_ext_ddr_only_enable` @ tm.c:32840 — getter, tmOnuRegRead(2)
- [fn-1304] `qmg_get_ddr_cache_enable` @ tm.c:32893 — getter, tmOnuRegRead(3)
- [fn-1305] `qmg_set_qmg_trap_cfg` @ tm.c:32924 — setter, tmOnuRegWrite(4)
- [fn-1306] `qmg_get_qmg_trap_cfg` @ tm.c:32952 — getter, tmOnuRegRead(4)
- [fn-1307] `qmg_set_qmg_up_ram_depth` @ tm.c:32983 — setter, tmOnuRegWrite(5)
- [fn-1308] `qmg_get_qmg_up_ram_depth` @ tm.c:33011 — getter, tmOnuRegRead(5)
- [fn-1309] `qmg_get_statistics` @ tm.c:33036 — getter, tmOnuRegRead(6)
- [fn-1310] `getPort` @ tm.c:43492 — ~46 lines body
- [fn-1311] `getTpidAddr` @ tm.c:49469 — ~22 lines body
- [fn-1312] `writeQosInfoToRam.constprop.7` @ tm.c:50230 — ~23 lines body
- [fn-1313] `writeCmdInfoToRam.constprop.8` @ tm.c:50253 — ~37 lines body
- [fn-1314] `printaddr` @ tm.c:53978 — ~10 lines body
- [fn-1315] `calculateIpDelta` @ tm.c:53988 — ~14 lines body
- [fn-1316] `calculatePortDelta` @ tm.c:54002 — ~12 lines body
- [fn-1317] `calculateDelta` @ tm.c:54014 — ~9 lines body
- [fn-1318] `ztePonGetPrbsCounters` @ tm.c:54855 — ~9 lines body
- [fn-1319] `zte_zx_api_sw_get_wlan_port` @ tm.c:54947 — getter
- [fn-1320] `epondrvCfgContinuesTransPrbs` @ tm.c:55361 — fpga_write_reg(0x2000d)
- [fn-1321] `zte_zx_api_pp_global_init` @ tm.c:55812 — printk:"ERROR:(%s:%d)"
- [fn-1322] `sw_get_arp_icmp_stat` @ tm.c:57535 — getter
- [fn-1323] `gpondrvCfgCntnusprbs` @ tm.c:57780 — fpga_write_reg(0x36000)
- [fn-1324] `ztePonCfgCntnusprbs` @ tm.c:57805 — fpga_read_reg(0x10006)
- [fn-1325] `ztePonCfgPrbsRxBist` @ tm.c:57831 — ~21 lines body
- [fn-1326] `zte_zx_api_pp_set_trap_queue` @ tm.c:57919 — setter
- [fn-1327] `prbsCounterGetHandler` @ tm.c:58847 — ~14 lines body
- [fn-1328] `spaDebugStatics` @ tm.c:65362 — ~16 lines body
- [fn-1329] `spaDebugGetMatchRam` @ tm.c:65378 — ~62 lines body
- [fn-1330] `spaDebugGetHashRam` @ tm.c:65440 — ~24 lines body
- [fn-1331] `spaDebugSetMatchRuleAndHashRam` @ tm.c:65464 — ~107 lines body
- [fn-1332] `PrintBrgDesc` @ tm.c:66260 — ~274 lines body
- [fn-1333] `brgDebugStatics` @ tm.c:66860 — ~16 lines body
- [fn-1334] `tmUsrInterfaceRelease` @ tm.c:69401 — ~10 lines body

