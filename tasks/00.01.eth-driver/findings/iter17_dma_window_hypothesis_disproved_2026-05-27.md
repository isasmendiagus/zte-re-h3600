# [Iter 17] DMA window hypothesis disproved — reverting reserved-memory

Iter 16's hypothesis (HW requires DMA bases in 0x4FF region) was tested
by adding a `reserved-memory` node + `of_reserved_mem_device_init`.
Two variants tested:

| Config | Driver probe | DMA bases | Wedge state |
|---|---|---|---|
| `no-map` 1 MiB | ❌ -ENOMEM on `dma_alloc_coherent` | n/a | n/a |
| `no-map` 4 MiB | ❌ -ENOMEM (bp_sz=2.25 MiB fits but allocator fails) | n/a | n/a |
| `reusable` 4 MiB | ✓ probes | 0x4c048000 (back to CMA — region didn't pin) | identical to pre-iter17 |

**Conclusion: `shared-dma-pool` doesn't deliver what we needed.**

With `no-map`, `of_reserved_mem_device_init` succeeds but
`dma_alloc_coherent` returns -ENOMEM — likely missing
`CONFIG_DMA_DECLARE_COHERENT` or the `rmem_dma_setup` path isn't
hooked. With `reusable`, the pool is added to CMA but CMA distributes
across the WHOLE CMA area (including the existing 0x4ec00000-0x4FBFFFFF
range), so allocations don't pin to 0x4FCxxxxx.

## More importantly: the hypothesis itself was probably wrong

User pushback 2026-05-27: "no entiendo qué diferencia hay que mainline
exponga toda la ram vs a darle los 256-64?". Valid point — from a HW
DMA perspective, ANY valid physical RAM address with cache coherency
should work. The 0x4FFx vs 0x4Cxx address difference between stock and
mainline is an **allocator artifact** (stock hardcoded carved RAM,
mainline CMA), not a HW-required window.

If HW genuinely required addresses in a specific window, that'd be a
very unusual SoC restriction. Not impossible, but extraordinary claim
requires extraordinary evidence — and we don't have any.

## What the real wedge is (returning to)

Stock-vs-mainline register diffs that are NOT address-related:

```
                       stock LIVE     mainline LIVE
TM[0x100] status       0x00000008    0x00007702
                       (bit 3)        (bits 1, 8, 9, 10, 12, 13, 14)
TM[0x8040] BMU         0x00e60097    0x001a000f
TM[0x10068] DN done    0x00000000    0x00071ee3 (high16=7 pending stuck)
```

The extra bits in TM[0x100] (8-10, 12-14) are likely **error
indicators** set by sub-blocks. TM[0x8040] being so different (BMU
state register) suggests BMU is mis-configured in mainline. Combined
with `tm_bmu_free_ok = 0` in driver counters (BMU never freed a BP),
the bug is in the BMU pool setup, not in the DMA address.

## Next iter targets

1. **TM[0x8040] decode**: figure out what each bit means. Search stock
   decomp for reads/writes to this reg. Compare init sequence.
2. **TM[0x100] bit semantics**: especially bits 8-10, 12-14. These
   only assert on mainline — what condition triggers them?
3. **BMU init order**: `pon_tm_bmu_init` + `pon_tm_bmu_enable` — verify
   mainline replicates stock byte-for-byte. We have it per the gap
   matrix but worth double-checking.

## Reverted artifacts

- DTS reverted: no `reserved-memory` node, no `memory-region` on eth
- Driver reverted: removed `of_reserved_mem.h` include, removed
  `of_reserved_mem_device_init` call from `zx_tm_alloc_pools`

## Lesson

"Stock has X at address Y, mainline has X at address Z" is not a
hypothesis — it's just an observation. Before assuming "the address
matters", consider whether the symptom you're chasing could be caused
by something else entirely. In this case the obvious-in-retrospect
TM[0x8040] BMU divergence was a much stronger signal than the address
diff but I latched onto the address first because it was the most
visually distinctive.

Cross-ref:
- `iter16_dma_addr_window_2026-05-27.md` (retracted hypothesis)
- User feedback on the equivalence of 256-vis vs 192+64-carved
