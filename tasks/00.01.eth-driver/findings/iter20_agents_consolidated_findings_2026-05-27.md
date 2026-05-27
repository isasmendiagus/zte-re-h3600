# [Iter 20] Three agents — consolidated TX-wedge findings

Three RE agents launched in parallel 2026-05-27 to attack different
angles of the TX wedge. Summary of what each found + the synthesized
plan.

## Agent 1 — BMU Protocol Deep RE

Output: `tasks/00.10.02.re-stock-kmods/findings/bmu_protocol_deep_re.md`

### Key findings

1. **Five BMU instances**, not one. Stock has TM[0x8000], +0x400,
   +0x800, +0xC00, +0x1000 — all configured identically with stock_table
   replay (rows 16347–16458). Mainline only configured instance 0.
   → Fixed in commit `05166bb2a` (5-instance loop), didn't unblock.

2. **Stock pool geometry**: BPPE_POOL=8192, BP_SIZE=0x900, total
   BPPE region 128 KiB (`dma_cache_maint(bppe_va, 0x20000, 1)` — HW
   may prefetch ahead). Mainline POOL=1024, 2 KiB region.

3. **TM[0x8058] BUCKETS_M1**: stock LIVE = 0x100 (256). Stock formula
   per decomp `(POOL>>5)-1` gives 255 for POOL=8192, off by +1 from
   live. Either decomp imprecise or HW post-increments. Mainline now
   writes `(POOL>>5)-1` = 31 for POOL=1024 (commit `2123aa0da`).

4. **Register map decoded** for TM[0x8000..0x80DC] + TM[0xE8..0xFC]:
   - 0x8000 = enable (bit 0)
   - 0x8004/0x8008 = CTRL1/2 (0x0104C040)
   - 0x800C = alloc result (bit 31 = valid)
   - 0x8014 = alloc ctrl (bit 0 = kick, bit 1 = jumbo)
   - 0x8048 = POOL_SIZE producer cursor (high16 = write_ptr, low16 = read_ptr)
   - 0x8058 = BUCKETS_M1
   - 0xE8 = BPPE_BASE (phys)
   - 0xF4 = BP_BUFFER_BASE (phys)
   - 0xF0 = RX desc base (per-instance)
   - 0xFC = `BP_SIZE | JUMBO_BP_SIZE<<16`

### Top candidates (ranked)

1. 🔴 5 BMU instances not configured — **tested + disproved as sole cause**
2. 🟡 TM[0x8048] writes don't latch — alignment or sequencing issue
3. 🟡 BPPE region size 2 KiB vs stock's 128 KiB — HW prefetch overrun

---

## Agent 2 — TM[0x100] Bit Decode

Output: `tasks/00.10.02.re-stock-kmods/findings/tm_100_status_bit_decode.md`

### Key findings

`TM[0x100]` is the **TM IRQ aggregate status register**. Stock NEVER
writes it — confirmed via full grep across `decomp_all_*.c`. Only one
read site: the IRQ handler at plat:6311 (`status & 3 & ~mask`). Not
W1C, not W0C — bits self-clear when the underlying HW condition ends.

### Bit map (decoded)

| Bit | Meaning |
|---|---|
| 0 | RX_PENDING |
| 1 | TX_DONE (TX pending unconsumed) |
| 2 | generic ERR (masked by stock during stop) |
| 3 | BMU_READY / block-ok steady-state (stock idle = 0x08) |
| 8-10 | FIFO interrupt rollup (3 of 8 FIFOs) — sub-block reg 0xd |
| 12-13 | DMA_DES_INT for UP/DN directions — sub-block reg 0xc |
| 14 | Queue interrupt rollup — sub-block reg 0xb |

### Why mainline has TM[0x100] = 0x7702 vs stock 0x08

Stock's `tm_pon_tm_reg_initial` (tm.ko:42448) calls:
- `pon_tm_set_queue_int_mask`
- `pon_tm_set_dma_des_int_mask`
- `pon_tm_set_fifo_int_mask`

These mask sub-block interrupts at the indirect `claRegTable` path.
**Mainline never executes this chain** — sub-block masks default to
"everything unmasked" → minor exceptions in any FIFO/DMA-direction/queue
light up the rollups in TM[0x100].

Combined with the still-pending TX path issues, bit 1 + bits 12/13
are explained jointly: the DMA UP ring fetch is failing, asserting
DMA_DES_INT bits, and TX won't drain, holding bit 1. Bit 3 (block-ok)
doesn't set because the init chain didn't complete.

---

## Agent 3 — Stock vmlinux Platform Init Binary RE

Output: `tasks/00.10.02.re-stock-kmods/findings/static_analysis_vmlinux_platform_init.md`

### Key findings

1. **Machine descriptor**: `__mach_desc_ZX` @ 0xc065d334, compatible
   `"zte,zx279128-smp"`. Callbacks:
   - `.reserve` = `zx279128_reserve_mem` (0xc0015924)
   - `.map_io` = `zx_map_io` (0xc0639098, 19-entry iotable)
   - `.init_irq` = `zx279128_init_irq` (0xc06391d4)
   - `.init_machine` = `zx279128_init_machine` (0xc06390f4)
   - `.restart` = `zx279128_restart` (0xc0015800)
   - `.l2c_aux_val` = 0x4030, `.l2c_aux_mask` = 0xfffffffe

2. **TM[0x8xxx] never touched** by vmlinux. All BMU touches originate
   from `plat-zxylzb_9128S.ko` and `tm.ko` at module init. So no
   "pre-driver HW init by vmlinux" is missing.

3. **Carved memory**: `cal_reserve_mem` does `memblock_reserve(0x4C000000, 0x04000000)`
   = 64 MiB at phys 0x4C000000. Stock sets `ZX_RESERVE_MEM_SIZE = 0x40`
   (64) from ATAG `gs_ztebootinfo`. Statically iomapped at virt
   0xf1000000 via `zx_map_io`. Layout:
   - 0x4C000000 carved base
   - 0x4C020000 ACL RAM (4 MiB, zeroed by tm.ko `aclRamInit`)
   - 0x4C420000 Flow RAM (1 MiB, ditto)
   - 0x4C520000 BP pool start
   - 0x4E700000 BPPE base
   - 0x4EC20000 BP buffer pool
   - 0x4FF1F000 TM RX desc
   - 0x4FFDF000 TX UP desc
   - 0x4FFEF000 TX DN desc

4. **Most likely missing pieces** (ranked by agent):
   1. 🔴 `aclRamInit` not run on mainline — 4 MiB ACL + 1 MiB Flow
      RAM not zeroed → classifier matches random rules.
   2. 🔴 **BMU pool placement outside carved region** — mainline's CMA
      addresses may be unreachable by BMU's AXI master.

5. **Unexpected — 5 mystery SoC sys-ctrl writes** at phys 0x00a20000
   by `zx279128_init_machine`:
   ```
   [+0x80] = 0x40000001
   [+0x84] = 0xBFFFFFFF (= ~0x40000000)
   [+0x78] = 0x1F0F1F0F
   [+0x88] = 0x1F0F1F0F
   [+0x00] = 0x0D000000
   ```
   Pattern looks like AXI interconnect QoS / DMA priority config. Each
   write gated by `outer_cache.sync()`. Mainline 6.6 doesn't touch this.
   → **Tested via runtime devmem**: writes stuck but BMU still empty.
   Not the sole cause but architecturally correct.

6. **Stockport (parked task 99.01)** confirmed already hit the
   carved-region wall: tm.ko page-faults on `__memzero(0xf1020000, 4MB)`
   because mainline DT lacks the iotable mapping.

---

## Synthesized plan → Iter 20

Combine all three agents' findings:

1. **Reserve full 64 MiB at 0x4C000000** via `reserved-memory` DT node
   with `no-map` + `mem=192M` boot arg.
2. **memremap_wc** the carved region in driver (bypass dma_alloc_coherent,
   write-combine = uncached but write-buffered for HW DMA).
3. **Place all TM DMA structures** (BPPE, BP pool, RX desc, TX UP, TX DN)
   at stock-exact offsets within carved region.
4. **Zero ACL RAM** (4 MiB @ 0x4C020000) + Flow RAM (1 MiB @ 0x4C420000)
   before BMU enable.
5. Keep 5 BMU instance config from commit `05166bb2a`.
6. (Future) Add `pon_tm_set_{queue,dma_des,fifo}_int_mask` chain to
   clear TM[0x100] rollup bits 8-14.
7. (Future) Replicate 5 SoC sys-ctrl AXI writes at 0x00a20000 from
   `zx279128_init_machine` — currently runtime-poked, not driver-coded.

DT + driver changes in this iter:
- `linux-v6.6/arch/arm/boot/dts/zte/zx279128s-h3600.dts`:
  - bootargs: add `mem=192M`, move cma=16M to 0x48000000
  - memory@40000000: reg shrunk to 0x0c000000 (192 MiB)
  - new reserved-memory node `eth_carved@4c000000` (64 MiB, no-map)
  - &eth: `memory-region = <&eth_carved>`
- `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`:
  - struct zx_eth: new `void __iomem *carved_va` field
  - `zx_tm_alloc_pools`: replaced with memremap_wc + offset assignments
  - `zx_tm_free_pools`: replaced with memunmap

## Current state

### What's still pending (agent 4)

- **Agent 4 (U-Boot eth path RE)** still running. Goal: confirm whether
  U-Boot's own eth init leaves HW state that stock module relies on.

### Expected from carved-region change

If HW BMU master only sees `0x4C000000-0x4FFFFFFF` as readable DDR:
- BPPE at 0x4E700000 → HW can READ it → alloc returns valid bp_idx
- BP pool at 0x4EC20000 → HW DMA can read/write packet bodies
- TX UP/DN at 0x4FFDF000/0x4FFEF000 → HW consume engine reads descs
- ACL RAM zeroed → classifier matches predictable (zero) rules

Test: boot, read TM[0x800c] post-alloc-kick. If bit 31 sets, BMU works.
Then ping, watch `tm_irq_count` + `tm_rx_count` in pipeline_stats.

## debugfs counters to watch (already exist)

`/sys/kernel/debug/zx_eth/pipeline_stats` shows:
- `tm_irq_count` — TM IRQ fires (should be > 0 if HW works)
- `tm_napi_count` — NAPI scheduled
- `tm_rx_count` — frames delivered to netdev
- `tm_tx_count` — frames pushed
- `tm_tx_dropped` — failed BMU allocs (currently >0)
- `tm_bmu_free_ok` — BPs released (currently 0)
- extras section shows TM[0x100], TM[0x10068], BPPE/BP/RX bases

Plus `/proc/interrupts` to see GIC-level IRQ counts.

## Files changed

- `linux-v6.6/arch/arm/boot/dts/zte/zx279128s-h3600.dts`
- `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c` (zx_tm_alloc_pools + struct field)

Plus the 3 agent doc files in `tasks/00.10.02.re-stock-kmods/findings/`.
