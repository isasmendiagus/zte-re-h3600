# [Iter 16] HW DMA addr window — stock 0x4FFx, mainline 0x4Cxx

Direct stock-vs-mainline runtime comparison of TM DMA base registers,
captured 2026-05-27 via SSH to running stock + UART memdump on
running mainline.

## Side-by-side

| Reg | Stock LIVE | Mainline LIVE | Delta |
|---|---|---|---|
| `TM[0x0f0]` RX desc base    | `0x4FF1F000` | `0x4C080000` | +63.5 MiB |
| `TM[0x10050]` UP TX base    | `0x4FFDF000` | `0x4C048000` | +64.4 MiB |
| `TM[0x10060]` DN TX base    | `0x4FFEF000` | `0x4C04C000` | +64.4 MiB |
| `TM[0x10000]` DMA_CTRL      | `0x003f6564` | `0x003f6564` | same ✓ |
| `TM[0x100]` IRQ status      | `0x00000008` | `0x00007702` | 1+8-10+12-14 extra on mainline |
| `TM[0x104]` IRQ mask        | `0xfffffffc` | `0xfffffffe` | mainline bit 1 masked |
| `TM[0x10068]` DN TX done    | `0x00000000` | `0x00070000` | 7 stuck on mainline |
| `TM[0x8040]` BMU state      | `0x00e60097` | `0x001a000f` | very different |

## Interpretation

Stock's three DMA bases all sit in the `0x4FFxxxxx` range — a 1 MiB
slab in the top of 256 MiB physical RAM (256 MiB @ 0x40000000 →
0x40000000-0x50000000). Stock reserves this via boot-arg `mem=...` +
internal `pdt_mem` carve.

Mainline uses `dma_alloc_coherent` which returns whatever CMA hands
out — `0x4Cxxxxxx`. The pages are valid physical RAM but **65 MiB
outside the stock-reserved window**.

## Hypothesis: HW DMA address window restriction

The TM block's DMA engine may have a hardcoded address window
(e.g. only accepts bases in `0x4FF00000 - 0x4FFFFFFF`) tied to:

1. **BMU pool layout** — BMU's pool descriptors and packet buffers are
   in the same `0x4F` region; the TM engine may expect to compute
   offsets like `pdt_mem + 0x40520010 + bp*BP_SIZE` and arrive at
   valid BP storage. Mainline's CMA-scattered allocations break that
   pointer arithmetic.

2. **Hardware reset state** — TM may have an internal register that
   defines the valid DMA window, set by stock during a phase we
   haven't RE'd. If mainline doesn't set it, HW operates with a
   default that rejects writes outside some range.

3. **Cache/aliasing constraint** — DDR controller may treat the top
   1 MiB differently (e.g. uncached, write-through) for DMA descriptor
   integrity. Mainline's CMA pages go through normal cache.

## Symptoms tied to this

- `tm_irq_count = 0` after PHYs link UP and frames arrive at switch
  (HW classifies them per stock pp_pm pattern but never asserts TM
  IRQ status bit 0 because RX desc writeback is going to memory HW
  doesn't actually read for completion)
- `TM[0x10068]` high16 = 7 pending TX never decremented because HW
  TX consume engine can't read the DN ring at mainline's CMA-allocated
  address
- `TM[0x100]` bit 1 stays set because the underlying "TX done event"
  comes from HW completing DMA, which never completes
- `TM[0x100]` extra bits (8-10, 12-14) set in mainline only —
  likely error indicators for "DMA out of bounds" / "BMU desc fetch
  failed" / similar conditions, never asserted on stock (where DMA
  works fine)
- `TM[0x8040]` BMU state diverges drastically (mainline = 0x1a000f vs
  stock = 0xe60097)

## Fix proposal (Iter 17)

1. Add `reserved-memory` node to `zx279128s-h3600.dts` reserving
   `0x4FF00000 - 0x4FFFFFFF` (1 MiB) for the eth driver:
   ```dts
   reserved-memory {
       #address-cells = <1>;
       #size-cells = <1>;
       ranges;

       eth_dma_pool: eth-dma-pool@4ff00000 {
           reg = <0x4ff00000 0x100000>;
           no-map;
       };
   };
   ```
2. Reference it from the `pon@92000000` node:
   ```dts
   memory-region = <&eth_dma_pool>;
   ```
3. In driver `zx_tm_alloc_pools`: call
   `of_reserved_mem_device_init(e->dev)` then keep
   `dma_alloc_coherent` — it will now allocate from the reserved
   region.
4. Verify post-boot via memdump that `TM[0xf0]`, `TM[0x10050]`,
   `TM[0x10060]` all read in the `0x4FFxxxxx` range.

If this matches stock, see if `TM[0x100]` clears bit 1 and `TM[0x10068]`
drains. If yes → the TX wedge is resolved.

If it doesn't help → there's an additional HW window programming we're
missing (e.g. a "DMA allowed range" register stock sets that we miss),
but at least we've matched stock memory layout.

## Risk: address conflict

Need to confirm `0x4FF00000 - 0x4FFFFFFF` isn't:
- Used by U-Boot post-handoff
- In the mainline kernel zImage load area (we load at 0x42000000, well
  below 0x4F)
- Owned by another platform driver

CLAUDE.md says boot args: `mem=256M` → kernel sees full 256 MiB, no
carve. Need to change to `mem=255M` (carve top 1 MiB) or use DT
reserved-memory with `no-map` to exclude from kernel allocator.

## Stock-side reads for reference (lib/ssh_shell.py output)

```
TM[0x000]    = 0x140         (master)
TM[0x108]    = 0x0
TM[0x110]    = 0x0
TM[0x124]    = 0x3FFFFFF     (queue enable)
TM[0x12c]    = 0x1FFF        same as mainline
TM[0x134]    = 0x1FFFFF      same as mainline
TM[0x10000]  = 0x3F6564      same as mainline ✓
TM[0x10058]  = 0x2           (UP TX done counter, drained)
TM[0xc008]   = 0x0           same as mainline ✓
TM[0x8000]   = 0x1           BMU enabled (same)
TM[0x8048]   = 0x50          BMU
```

## Cross-ref

- `stock_init_sequence_analysis_2026-05-27.md` "HW won't consume our
  TX" (this is finally the answer)
- `tm_irq_gate_investigation_2026-05-27.md` round 2 DMA mention
- `CLAUDE.md` hardware section (256 MiB RAM @ 0x40000000)
