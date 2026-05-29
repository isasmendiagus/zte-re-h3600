# Stock vmlinux platform init — static analysis

**Binary**: `tasks/00.10.01.re-vmlinux/vmlinux.elf` (Linux 4.1.25,
ARM EABI5, not stripped, 43,214 symbols).

**Goal**: identify pre-driver HW touches done by the kernel itself (machine
descriptor, builtin platform code, early initcalls) that mainline 6.6 does
not reproduce — specifically anything that could affect `pon_tm_bmu_init`
returning `TM[0x800c]==0` (BMU alloc "pool empty").

**Bottom line**: the stock vmlinux does **not** touch the TM register
region (`0x92340000..0x9234FFFF`) at boot. Every TM register write
originates from loadable modules (`plat-zxylzb_9128S.ko` / `tm.ko`). The
real candidate for "missing pre-init" is **the 64 MiB carved DDR region
at the top of physical RAM**, which stock reserves via
`memblock_reserve`, statically iomaps at virt `0xf1000000`, and where
the BMU's `bppe` pool data + ACL/Flow RAM tables physically live. Mainline
uses `dma_alloc_coherent()` returning arbitrary phys addresses instead.

---

## Legend

- **HW writes**: register address + value
- **In mainline?**: ✓ replicated / ⚠ partial / ✗ missing / N/A
- **Severity if missing**: 🔴 likely path-breaking · 🟡 unclear · 🟢 informational

---

## 1. Machine descriptor summary

Symbol `__mach_desc_ZX` @ `0xc065d334` (struct `machine_desc`, 0x68 bytes,
section `.arch.info.init`). Field layout (from raw dump + comparison with
stock 4.1.25 source `tasks/99.01.linux-stockport/linux-4.1.25/arch/arm/mach-zx/zx279128s.c`):

| Offset | Field | Value | Pointed at |
|---|---|---|---|
| `+0x00` | `.nr` | `0xffffffff` | (~0, so it's DT-style) |
| `+0x04` | `.name` | `0xc0585af4` | `"ZTE ZX279128S (Device Tree)"` |
| `+0x08` | `.dt_compat` | `0xc0661a18` | → `0xc0585b10` `"zte,zx279128-smp"`, then NULL |
| `+0x18` | `.l2c_aux_val` | `0x00004030` | L2C-310 aux ctrl value |
| `+0x1c` | `.l2c_aux_mask` | `0xfffffffe` | L2C-310 aux ctrl mask (only bit 0 cleared) |
| `+0x44` | `.reserve` | `0xc0015924` | `zx279128_reserve_mem` |
| `+0x48` | `.map_io` | `0xc0639098` | `zx_map_io` |
| `+0x50` | `.init_irq` | `0xc06391d4` | `zx279128_init_irq` |
| `+0x58` | `.init_machine` | `0xc06390f4` | `zx279128_init_machine` |
| `+0x60` | `.restart` | `0xc0015800` | `zx279128_restart` |

The mainline stockport descriptor at `mach-zx/zx279128s.c` already
mirrors `.name`, `.dt_compat`, `.map_io`. It does **not** mirror
`.l2c_aux_val/mask`, `.reserve`, `.init_irq`, `.init_machine`, or
`.restart`. The kernel core falls back to generic equivalents for these
on mainline.

CPU bringup: `.smp = __cpu_method_of_table_zx_smp` @ `0xc0662d20` →
`zx_smp_ops` @ `0xc065e818` →
- `zx_smp_prepare_cpus` @ `0xc06392f0` — ioremaps the SCU at phys
  `MPCORE_BASE` (loaded from `mrc p15,4,r0,c15,c0` cluster register),
  calls `scu_enable`, then ioremaps a `compat="zte,zx279128-smp-boot"`
  DT node, patches the secondary-CPU trampoline into it (memcpy of
  `c001725c..c00172b8` then `v7_coherent_kern_range`), `iounmap`,
  `sev`. Standard A9 SMP bringup; not relevant to TM.

---

## 2. Pre-driver HW init sequence (chronological)

### [vm-01] `zx279128_reserve_mem` @ `0xc0015924` — top-of-RAM 64 MiB carveout

Runs from `arm_memblock_init` (during `setup_arch`), before `paging_init`.

What it does:
1. `printk("ZX_RESERVE_MEM_SIZE is %x, %x\n", ZX_RESERVE_MEM_SIZE, pdt_mem_size)`
2. Calls `cal_reserve_mem()` (→ [vm-02]) which sets `ZX_RESERVE_MEM_SIZE`
   based on `pdt_mem_size`.
3. Computes the carveout range:
   - `start = pdt_mem_size + 0x40000000 - (ZX_RESERVE_MEM_SIZE << 20)`
   - For 256 MiB device → `start = 256·MB + 0x40000000 - 64·MB = 0x4C000000`
   - `size  = ZX_RESERVE_MEM_SIZE << 20` (e.g. 64 MiB = 0x04000000)
4. `memblock_reserve(start, size)` — pulls this range out of kernel
   allocatable memory. `panic("memblock_reserve for pp bp buffer failed!, system will panic.")` on fail.

This is the carved DDR region that subsequently:
- gets statically iomapped at virt `0xf1000000` (see [vm-03])
- hosts the BMU's `bppe` table at `0x4C000000` (= "BUF_BASE0" in
  decomp logs), `jumbo_bppe` at `0x4C010000`, ACL RAM at `0x4C020000`,
  Flow RAM at `0x4C420000`, BP pool at `0x4C520000`
- is what `pon_tm_bmu_init` (plat:5694) writes into `TM[0xe8..0xfc]` as
  physical addresses.

**In mainline?** ✗ — Mainline uses `dma_alloc_coherent()` and points the
BMU at the DMA-returned physical pages instead. **Severity 🔴 likely
path-breaking** if BMU HW has any implicit dependency on the carved
region (address bounds, AXI master attributes, alignment beyond what
DMA-coherent guarantees).

### [vm-02] `cal_reserve_mem` @ `0xc0015834` — pick reserve size by RAM size

Dispatch on `pdt_mem_size`:
- `pdt_mem_size == 0x08000000` (128 MiB) → `ZX_RESERVE = 0xf000` (var.A,
  computes via formula at +0x18a..0x147)
- `pdt_mem_size == 0x10000000` (256 MiB) → `ZX_RESERVE = 0xf000` (var.B)
- Other → default: 0x900 / 0x2800 / 0x800 / 0x200 globals (printk
  `"%s,%d"`). Most likely 64 MiB carved (`ZX_RESERVE_MEM_SIZE`
  symbol is exported at `0xc069ea10`; its initial value is `0x40` = 64
  MiB, set by this function at runtime).

Numeric tracing (256 MiB case):
- write `0xea00+0x00 = 0x900`
- write `0xea00+0x04 = 0x2000`
- write `0xea00+0x08 = 0x2800`
- write `0xea00+0x0c = 0x66`
- write `0xea00+0x10 = ZX_RESERVE_MEM_SIZE_IN_MIB`
- `printk` and return.

Globals at `0xc069ea00..0xc069ea14` (`u32_BP_SIZE`, `u32_BPPE_POOL_SIZE`,
`u32_JUMBO_BP_SIZE`, `u32_JUMBO_BPPE_POOL_SIZE`, `ZX_RESERVE_MEM_SIZE`)
are populated here. These are the **u32_BP_SIZE = 0x900**,
**u32_BPPE_POOL_SIZE = 0x2000 (= 8192)**, **u32_JUMBO_BP_SIZE = 0x2800**,
**u32_JUMBO_BPPE_POOL_SIZE = 0x66 (= 102)**, **ZX_RESERVE_MEM_SIZE =
0x40 (= 64 MiB)** constants the kmod decompiles reference.

**In mainline?** ✗ — Mainline driver uses its own constants
`TM_BPPE_POOL_SIZE = 1024`, `TM_BP_SIZE = 2304` (= 0x900). These match
stock's `BP_SIZE` but **pool size is 8x smaller** (1024 vs 8192) due to
`dma_alloc_coherent` of 18 MiB failing. Severity 🟡 — works for low
packet rate but starves at scale.

### [vm-03] `zx_map_io` @ `0xc0639098` — static iotable

Creates 19 static virt→phys mappings via `iotable_init`. Last entry is
runtime-computed: `pfn = ((pdt_mem_size + 0x40000000) - ZX_RESERVE_MEM_SIZE*MB) >> 12`,
i.e. **the carved DDR region** is mapped at virt `0xf1000000` (size
0x520000 ≈ 5.1 MiB).

Full table (decoded from `zx_io_desc` @ `0xc065e6b0`):

| virt | phys | size | meaning |
|---|---|---|---|
| `0xf0000000` | `0x00400000` | 1 MiB | Cortex-A9 PERIPHBASE/SCU |
| `0xf0100000` | `0x00800000` | 1 MiB | GIC dist/CPU |
| `0xf0200000` | `0x00a20000` | 1 MiB | **SoC sys-ctrl block** (init_machine writes here, see [vm-05]) |
| `0xf9602000` | `0x00c00000` | 1 MiB | PL310 L2C-310 |
| `0xf0400000` | `0x94000000` | 1 MiB | top_crm |
| `0xf0500000` | `0x94100000` | 1 MiB | pcie crm |
| `0xf0600000` | `0x94200000` | 1 MiB | pcie crm2 |
| `0xf0700000` | `0x94400000` | 1 MiB | UART (DEBUG_LL) |
| `0xf0800000` | `0x9a100000` | 1 MiB | gephy |
| `0xf0900000` | `0x00d00000` | 1 MiB | ? |
| `0xf4000000` | `0x92000000` | 4 MiB | **pon/npp/tm/pp/idm** (covers our `0x92340000` TM) |
| `0xf0a00000` | `0x00200000` | 1 MiB | ? |
| `0xf0f00000` | `0x9fe00000` | 0x20000 | ? |
| `0xf0b00000` | `0x09100000` | 1 MiB | USB DWC3 |
| `0xf0c00000` | `0x09400000` | 1 MiB | ? |
| `0xf3000000` | `0x10000000` | 4 MiB | PCIe (MT_DEVICE_WC) |
| `0xf3400000` | `0x20000000` | 4 MiB | PCIe (MT_DEVICE_WC) |
| `0xf0d00000` | `0x09300000` | 1 MiB | ? |
| `0xf0e00000` | `0x09200000` | 1 MiB | ? |
| `0xf1000000` | `RUNTIME` (`= 0x4C000000` for 256 MiB) | 0x520000 | **carved DDR** — bppe + ACL + Flow + BP pool live here |

**In mainline?** ⚠ partial — mainline stockport now mirrors 13 of these
(see `tasks/99.01.linux-stockport/.../mach-zx/zx279128s.c`). The 19-entry
build above is more complete. Mainline 6.6 driver doesn't use static
iotable at all; it `of_iomap`s per-driver.

### [vm-04] `zx279128_init_irq` @ `0xc06391d4` — `arm,cortex-a9-mg-crm` quirks

Runs from `init_IRQ` (after `paging_init`, before any initcalls).

What it does:
1. `of_find_compatible_node(NULL, NULL, "arm,cortex-a9-mg-crm")`
2. If found, `of_iomap` and write 6 magic values to offsets 0x50..0x64:
   - `[+0x50] = 0x002a0000`
   - `[+0x54] = 0x00000800`
   - `[+0x58] = 0x28001550`
   - `[+0x5C] = 0x0000540a`
   - `[+0x60] = 0x80022a02`
   - `[+0x64] = 0x00020a80`
3. `iounmap` and `b irqchip_init`.

If the DT node is missing it `printk("failed to find a9-mg-crm node")`
and skips to `irqchip_init`. Stock + our DTB do **not** declare this
compatible (`grep "cortex-a9-mg-crm" zx279128s.dtsi` → nothing), so this
quirk path is never hit on either stock or mainline. Likely dead/legacy
code for an earlier ZX SoC variant.

**In mainline?** N/A — never executes.

### [vm-05] `zx279128_init_machine` @ `0xc06390f4` — SoC sysctrl + GPIO

Runs from `customize_machine` (arch_initcall level 3), before any module
loads.

What it does:
1. `of_platform_populate(NULL, NULL, NULL, NULL)` — bind built-in
   platform drivers to DT nodes (i2c, spi, wdt, uart, etc.).
2. `zte_gpio_init()` — registers the SoC GPIO driver.
3. `dsb st` (memory barrier).
4. Five writes to **virt `0xf0200000` = phys `0x00a20000`** (a SoC
   sys-ctrl peripheral), each separated by an `outer_cache.sync()`
   indirect call (via `outer_cache.sync` at `outer_cache + 0x14`):

   | offset | value | purpose (guessed) |
   |---|---|---|
   | `+0x80` | `0x40000001` | bit 30 + bit 0 set |
   | `+0x84` | `0xBFFFFFFF` | (= ~0x40000000) clear bit 30 |
   | `+0x88` | `0x1F0F1F0F` | four 8-bit priority/threshold fields |
   | `+0x78` | `0x1F0F1F0F` | same |
   | `+0x00` | `0x0D000000` | unlock / magic |

   The 0x40000000-shaped pattern + 0x1F0F-style fields suggest this is
   an AXI bus-matrix / QoS / NIC configuration block, not L2C/PL310 (we
   verified: PL310 sits at phys 0x00c00000, virt 0xf9602000, separately
   ioremapped — see [vm-03]).

5. `outer_cache.sync()` between each write enforces ordering.

**In mainline?** ✗ — mainline 6.6 doesn't touch this block. **Severity
🟡 unclear** — without knowing what 0x00a20000 is, can't rule out
relevance. Pattern doesn't smell BMU-related (no bits look like
"buffer-pool enable"); more likely interconnect QoS / DMA priority.

### [vm-06] `customize_machine` @ `0xc06346b8` — initcall3 entrypoint

Initcall level 3 wrapper. Calls `machine_desc->init_machine` ([vm-05])
if defined, else falls back to plain `of_platform_populate`. Standard
ARM `arch/arm/kernel/setup.c` boilerplate.

---

## 3. Memory reservation — exact carve

Single `memblock_reserve` call from [vm-01]:
- Address range (256 MiB device): `0x4C000000 .. 0x50000000` (64 MiB).
- Mechanism: ATAG-parsed RAM size (`pdt_mem_size`, populated from
  `gs_ztebootinfo` ATAG block — `parse_tag_ztebootinfo` @ `0xc06355c8`
  copies the tag into a 0x554-byte global; the offset inside that
  struct containing the RAM size is read by [vm-02] via `[0xea00+0x10]`
  in MiB).
- Subsequent static iomap at virt `0xf1000000` (in [vm-03]) maps the
  first 5.1 MiB of this region for direct CPU access. The remainder
  (≈ 59 MiB) is reserved but not pre-mapped — `plat`/`tm` ko code uses
  the physical addresses directly when writing them into TM registers
  (DMA, no CPU access path needed).

**ATAG dependency**: This reservation requires that the bootloader
passes the `ATAG_ZTE_BOOTINFO` (tag 0x54410011 per
`__tagtable_parse_tag_ztebootinfo` @ `0xc065d39c`). Our cspstart
bootloader does (we know from `r1 = 0x44258` matching `.nr = 0x44258`
in the ATAG-style mach descriptor at
`tasks/99.01.linux-stockport/linux-4.1.25/arch/arm/mach-zx/zx279128s.c:88`).
Mainline 6.6 doesn't have this tag parser.

---

## 4. Platform-specific quirks vs mainline 6.6 freebies

| Quirk | Where in stock | Mainline 6.6 equivalent | Gap |
|---|---|---|---|
| 64 MiB top-of-RAM reservation | `zx279128_reserve_mem` ([vm-01]) | — | ✗ would need `reserved-memory` DT node + matching driver consumer |
| 19-entry static iotable | `zx_map_io` ([vm-03]) | `of_iomap` per-driver | ⚠ functionally OK (mainline driver `of_iomap`s the regions it needs) BUT the virtual addresses **0xf1020000 / 0xf1420000** that tm.ko hardcodes will never resolve without [vm-03] |
| ATAG bootinfo parse | `parse_tag_ztebootinfo` | DT only | ⚠ mainline can't use ATAGs; need to embed `memory@40000000` size in DTB |
| `zx_pll` clock-tree driver | `clk_register_zx_pll` @ `0xc02c6df0` | mainline has zx-clk drivers | ⚠ DT bindings differ |
| `cortex-a9-mg-crm` 6-reg poke | [vm-04] | — | N/A (dead code on this DTS) |
| `outer_cache.sync`-gated writes at phys 0x00a20000 | [vm-05] | — | 🟡 unclear, mainline never writes |
| L2C-310 aux ctrl mask | `.l2c_aux_val/mask` in `__mach_desc_ZX` | mainline initializes via DT `cache-level = <2>` etc. | ⚠ value must match |
| `__l2c210_op_pa_range` per-cache-line lock loop | @ `0xc0014cc0` | mainline 6.6 same (still uses spinlock-per-line) | ✓ confirmed identical loop structure (see §7) |
| `gs_ztebootinfo` exported (1364 bytes) | `0xc069e23c` | — | N/A — only `csp_get_raheader` and similar userland-facing code consumes it |
| GIC writes via virt `0xf0100000+0x100/0x1100` (cleared in phy_process) | static iomap | DT-driven | ⚠ stock plat.ko hardcodes virt; mainline doesn't need this since it `of_iomap`s |

**No TM block touches**: a movw/movt scan of the full vmlinux disassembly
(`vmlinux.dis`, 778k lines) finds **zero** instructions that load the
physical address `0x92340000..0x9234FFFF` or virtual `0xf4340000..0xf434FFFF`
(the TM block). The kernel proper never reads or writes any TM register.
All TM access happens after `plat-zxylzb_9128S.ko` `of_iomap`s the region
at module init.

---

## 5. The "single most likely missing piece" for BMU alloc

Per `pon_tm_bmu_init` decomp (plat:5694), the BMU pool linkage is set up
as follows:
```
bppe_va_addr        = pdt_mem - ZX_RESERVE*MiB                  (virt access via 0xf1000000 iotable)
jumbo_bppe_va_addr  = bppe_va_addr + 0x10000

// Populate bppe[i] = bswap16(i) for i=0..u32_BPPE_POOL_SIZE-1
// Populate jumbo_bppe similarly
// Flush dcache for bppe region

TM[0x8000] = 0                                       (disable)
TM[0x8004] = 0x104c040
TM[0x8008] = 0x104c040
TM[0x8058] = (u32_BPPE_POOL_SIZE >> 5) - 1
TM[0x805c] = (u32_JUMBO_BPPE_POOL_SIZE >> 5) - 1
TM[0xf4]   = phys + 0x40520000 - ZX_RESERVE*MiB      ← BP buffer base (DDR, in carved region)
TM[0xf8]   = TM[0xf4] + u32_BP_SIZE * u32_BPPE_POOL_SIZE
TM[0xe8]   = phys + 0x40000000 - ZX_RESERVE*MiB      ← bppe base (DDR, in carved region)
TM[0xec]   = phys + 0x40010000 - ZX_RESERVE*MiB      ← jumbo_bppe base
TM[0xfc]   = u32_BP_SIZE | (u32_JUMBO_BP_SIZE << 16)
TM[0x8048] = u32_BPPE_POOL_SIZE << 16
TM[0x804c] = u32_JUMBO_BPPE_POOL_SIZE << 16
```

For a 256 MiB device with 64 MiB reserved:
- `bppe @ phys 0x4C000000`  (virt 0xf1000000 — directly CPU-writable via static iotable)
- `jumbo_bppe @ 0x4C010000`
- `bp pool @ 0x4C520000`
- `bp pool end @ 0x4C520000 + 8192 * 0x900 = 0x4D000000`  (fits in 64 MiB)

**Mainline gap**: `zx_eth_main.c:1721-1736` writes the same TM registers
but with `dma_alloc_coherent()` return values, which for ARM CMA or
`coherent_pool` typically come back in **kernel-allocated DDR pages**
inside the 0x40000000..0x4BFFFFFF range, NOT in the carved 0x4C000000+
region. There is no documented hardware reason the BMU MUST use carved
RAM, BUT:

1. **`aclRamInit` is never run** — tm.ko's `aclRamInit_part_6` (tm:54670)
   does `__memzero(0xf1020000, 0x400000)` + `__memzero(0xf1420000, 0x100000)`
   to zero the ACL + Flow lookup tables BEFORE BMU starts allocating. If
   these tables contain garbage at boot, the classifier could be matching
   random rules that drop / mis-classify every BMU alloc request.
   Mainline doesn't do this zero. **Severity 🔴.**

2. **DMA cache coherency**: stock's `dma_cache_maint(bppe_va_addr,
   0x20000, 1)` explicitly flushes the bppe region after populating it.
   Mainline uses `dma_alloc_coherent` which returns
   already-coherent-mapped memory — this should be equivalent, but only
   if the BMU's AXI master uses the same domain.

3. **AXI bus master attributes**: the carved region may have different
   AXI security / cacheability attributes than normal DDR (configured by
   either uboot, by [vm-05]'s mystery writes at phys 0x00a20000, or by
   one of the SoC clock-gates the eth driver doesn't enable). If BMU
   reads come back as zeros (e.g. because the master can't reach normal
   DDR), the alloc would return 0 ("pool empty") and `TM[0x800c]` would
   read back 0 — **matching observed mainline symptom exactly**.

**Most likely single fix to try**:

> **Zero the ACL RAM (`0x4C020000`, 4 MiB) and Flow RAM (`0x4C420000`,
> 1 MiB) at probe time, and point BMU's BP/BPPE pools at fixed physical
> addresses inside the carved reserve region (not `dma_alloc_coherent`
> output).** This requires a `reserved-memory` DT node and either
> matching `memory-region` consumer or a direct `memremap`/`ioremap` of
> the reservation. If after this `TM[0x800c]` still reads 0, the
> remaining suspect is the [vm-05] sys-ctrl block at phys 0x00a20000
> (`outer_cache.sync`-gated writes) gating BMU's AXI master.

---

## 6. Other findings (Q6, Q7 from prompt)

### Q6: `fixed_pci_read_u32` @ `0xc0014dec`

Trivial spinlock-protected `*r0 = *r1` load. The implementation reads
one `u32` from `*r1` under `_raw_spin_lock_irqsave(&fixed_pci_lock)`
(lock @ `0xc069e9c8`). `_u16`, `_u8` variants @ `0xc0014e1c` / `_u8` @
`0xc0014e50`; write variants `_u32` @ `0xc0014e84`, `_u16` @
`0xc0014eb4`, `_u8` @ `0xc0014ee8`. All are exported (`__kstrtab_*`).

`patch.ko` hooks these (see `static_analysis_patch_ko.md`) to provide
PL310 L2C atomic-range ops. Since our PCIe is only used for WiFi (and
mainline 6.6 has its own L2C-310 driver with proper locking), patching
these is not relevant for the TX/RX BMU bug.

### Q7: `__l2c210_op_pa_range` @ `0xc0014cc0`

Disassembly (annotated):
```asm
c0014cc0: cmp   r1, r2                 ; if (end <= start) return
c0014cc4: push  {r4-r6, lr}
c0014cc8: mov   r4, r1                 ; r4 = addr (start)
c0014ccc: mov   r6, r2                 ; r6 = end
c0014cd0: mov   r5, r0                 ; r5 = reg ptr
c0014cd4: popcs {r4-r6, pc}            ; (return if start>=end)
.loop:
c0014cd8: ldr   r0, [pc, #32]          ; r0 = &l2cc_spinlock
c0014cdc: bl    _raw_spin_lock_irqsave
c0014ce0: mov   r1, r0                 ; r1 = saved flags
c0014ce4: str   r4, [r5]               ; *reg = addr (the cache-line op)
c0014ce8: ldr   r0, [pc, #16]          ; r0 = &l2cc_spinlock
c0014cec: add   r4, r4, #32            ; addr += L1_CACHE_BYTES (32)
c0014cf0: bl    _raw_spin_unlock_irqrestore
c0014cf4: cmp   r6, r4
c0014cf8: bhi   .loop                  ; while (end > addr)
c0014cfc: pop   {r4-r6, pc}
```

Confirmed: this is the **per-cache-line lock-and-write** version (loop
takes/releases the spinlock once per 32-byte cache line), matching what
`static_analysis_patch_ko.md` describes. `patch.ko` exists because this
fine-grained locking is required for correctness when L2C MMIO can race
with another bus master — `patch.ko` replaces the L2C op pointers with
versions that use atomic register-pair writes. Mainline 6.6's L2C-310
driver does the same per-line approach; no patch needed.

---

## 7. Function index

| Address | Symbol | Role | When it runs |
|---|---|---|---|
| `0xc065d334` | `__mach_desc_ZX` | machine descriptor (struct, not fn) | static |
| `0xc06390f4` | `zx279128_init_machine` | SoC sys-ctrl writes + GPIO init + of_platform_populate | arch_initcall 3 |
| `0xc06391d4` | `zx279128_init_irq` | optional a9-mg-crm quirk + irqchip_init | early, from `init_IRQ` |
| `0xc0639098` | `zx_map_io` | static iotable_init (19 entries) | very early, from `paging_init`→`devicemaps_init` |
| `0xc0015924` | `zx279128_reserve_mem` | top-of-RAM memblock_reserve | `arm_memblock_init` (post-FDT, pre-paging) |
| `0xc0015834` | `cal_reserve_mem` | dispatch on RAM size; populate ZX_RESERVE_MEM_SIZE + BP_SIZE / BPPE_POOL_SIZE globals | called from [vm-01] |
| `0xc0015800` | `zx279128_restart` | writes `1` to virt `0xf040`+0x44 → SoC reset | machine_desc.restart |
| `0xc06346b8` | `customize_machine` | wrapper that invokes init_machine | initcall3 |
| `0xc06392f0` | `zx_smp_prepare_cpus` | SCU enable + secondary trampoline patch | smp_init |
| `0xc06355c8` | `parse_tag_ztebootinfo` | copy ATAG into `gs_ztebootinfo` (1364 bytes) | ATAG parse during setup_arch |
| `0xc0014cc0` | `__l2c210_op_pa_range` | per-line spinlock+write for L2C-310 range ops | called by L2 cache driver |
| `0xc0014dec` | `fixed_pci_read_u32` | spinlock-protected MMIO read helper | (patched by patch.ko at runtime) |
| `0xc02c6df0` | `clk_register_zx_pll` | ZX PLL clock driver | clk init |
| `0xc0017040` | `zte_board_init` | reads `zte_get_vid()`, picks board params, → `CspSetBoardInfo` | ? |
| `0xc065e6b0` | `zx_io_desc` (array, 19 × `struct map_desc`) | static iotable data | static |
| `0xc065d33c..c065d398` | `__arch_info_begin..__arch_info_end` | mach_desc table | linker-section |
| `0xc069e23c` | `gs_ztebootinfo` (1364 bytes) | ATAG bootinfo blob | populated at boot |
| `0xc069dba0` | `pdt_mem_size` (u32) | RAM size in bytes, from ATAG | populated at boot |
| `0xc069ea00..ea14` | `u32_BP_SIZE`, `u32_BPPE_POOL_SIZE`, `u32_JUMBO_BP_SIZE`, `u32_JUMBO_BPPE_POOL_SIZE`, `ZX_RESERVE_MEM_SIZE` | BMU sizing constants | populated by [vm-02] |
| `0xc066d2a4` | `outer_cache` (struct outer_cache_fns) | populated by PL310 init; `.sync` @ +0x14 called from [vm-05] | static (filled at L2C init) |

---

## 8. Cross-references to other docs

- `static_analysis_plat_zxylzb_init.md` — full RE of plat-zxylzb_9128S.ko
  `init_module` chain (fn-00..fn-29). [fn-16] is `pon_tm_bmu_init`, the
  function this doc connects to.
- `static_analysis_tm_ko_init.md` — RE of tm.ko including `aclRamInit`,
  `tm_pon_tm_init` orchestrator.
- `static_analysis_patch_ko.md` — RE of patch.ko (L2C-310 op locking).
- `tasks/99.01.linux-stockport/findings/stockport_revival_2026_05_26.md`
  — empirical confirmation that without the carved-region iotable, tm.ko
  page-faults on first `__memzero(0xf1020000, 0x400000)` call.
- `tasks/99.01.linux-stockport/linux-4.1.25/arch/arm/mach-zx/zx279128s.c`
  — reconstructed machine-desc + iotable (mirrors §1 + §2 [vm-03]).
- `HW_BLOCKS_INVENTORY.md` — physical memory map: stock uses 9 separate
  ioremap regions, mainline 1.

---

## 9. Disassembly artifacts

- `tasks/00.10.01.re-vmlinux/vmlinux.dis` — full objdump -d (31 MiB,
  778k lines). Generated for this analysis; can be reused or deleted.
- `tasks/00.10.01.re-vmlinux/nm.txt` — full nm dump (43,214 symbols).
- `tasks/00.10.01.re-vmlinux/symbols.txt` — objdump -t dump.

Both can be regenerated from `vmlinux.elf` with the standard
`arm-linux-gnueabi-{nm,objdump}` commands.
