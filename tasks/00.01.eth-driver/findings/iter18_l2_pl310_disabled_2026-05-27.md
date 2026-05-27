# [Iter 18] L2 PL310 cache — kept DISABLED in mainline

Runtime probe 2026-05-27 of PL310 cache controller registers via
memdump on mainline:

```
0xc00000  Cache ID  = 0x410000c9   (ARM Ltd, PL310)
0xc00100  Control   = 0x00000000   ← bit 0 (Enable) = 0
```

L2 is **OFF** on mainline. The L2C-310 driver in Linux 6.6 has the
node compatible (`arm,pl310-cache`) recognized but no init message
appears in dmesg — the driver isn't being auto-probed.

## Comparison with stock

Stock kernel 4.1.25 ships `patch.ko` which runtime-patches
`__l2c210_op_pa_range` (the L2 cache phys-range op function) via a
custom `patch_function` mechanism. Symbols visible in patch.ko:

- `__l2c210_op_pa_range` (target)
- `l2x0_patch` (driver setup)
- `clean_l1_dcache`, `invalid_icache_all` (cache maint helpers)
- `patch_pci_read_u32` (also patches PCI access)

This is a vendor-specific PL310 erratum workaround that does not exist
upstream. Full RE pending (separate agent run).

## Why we keep L2 OFF for now

1. **Driver works without L2** — ARM Cortex-A9 has separate L1 I+D
   caches that operate independently. ~30-50% perf hit, no correctness.
2. **DMA path uses uncached pages** — `dma_alloc_coherent` returns
   non-cacheable pages (no `dma-coherent` DT property). L1/L2 not
   involved in I/O.
3. **TX wedge is unrelated** — the symptom is HW TM DMA engine not
   consuming descriptors. CPU cache state doesn't gate HW DMA on
   uncached pages.
4. **Enabling L2 without the patch.ko erratum fix could introduce new
   bugs** — better to debug TX wedge first with cache state matching
   current known-OK (boot-OK) state.

User answer 2026-05-27: "no necesitamos ese cache L2 para ahora,
seguimos sin nada → dejarlo OFF". Made explicit via `status =
"disabled"` on the l2cc node.

## When to revisit

After ping bidi works:
1. RE patch.ko fully (background agent in progress)
2. Identify the specific PL310 erratum number(s) it works around
3. Either:
   a. Map to a kernel `CONFIG_PL310_ERRATA_*` already supported in 6.6
   b. Mirror the runtime-patch logic in a small init hook
   c. Add an `arm,errata-*` DT property if kernel auto-detects
4. Remove `status = "disabled"` and verify L2 enables cleanly
5. Bench-test perf delta (ping latency, throughput)

## DT change

`linux-v6.6/arch/arm/boot/dts/zte/zx279128s.dtsi`:

```dts
l2cc: cache-controller@c00000 {
    ...
    status = "disabled";    /* NEW */
};
```

Note: the `next-level-cache = <&l2cc>` reference on the CPU node
(line 26) remains — it just points to a disabled node. The cpu's L1
cache info is still meaningful; the L2 link is descriptive metadata.

## Cross-ref

- `tasks/00.10.02.re-stock-kmods/findings/static_analysis_patch_ko.md`
  (pending — agent running)
- ARM PL310 TRM (DDI 0246F): `__l2c210_op_pa_range` semantics
- Linux upstream: `arch/arm/mm/cache-l2x0.c` — has CONFIG_PL310_ERRATA_*
  for 588369 / 727915 / 752271 / 753970 / 769419 already
