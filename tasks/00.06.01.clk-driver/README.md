# clk-driver — resurrect clk-zx296702 + adapt for ZX279128S

**ID**: 00.06.01
**Parent**: [00.06 platform-drivers](../00.06.platform-drivers/)
**Children**: none (open work in `research/`)
**TaskList items**: #105
**Status**: 🎯 PLANNED — not active yet; spec laid out below for when it starts.

## Goal

Bring back the standard Linux clock framework support for the ZX279128S SoC
by:

1. **Cherry-picking** `drivers/clk/zte/clk-zx296702.c` from pre-Jan-2021 mainline
2. **Adapting it** with our `clk-zx279128s.c` overlay (already drafted at
   [`tasks/00.openwrt-port/kernel-patches/clk/clk-zx279128s.c`](../00.openwrt-port/kernel-patches/clk/))
3. **Wiring Kconfig + Makefile** so `CONFIG_SOC_ZX279128S` selects it
4. **Verifying** standard `clk_get()` works for one consumer — pick a simple
   one like UART or a kernel timer

## Why this is the urgent platform-driver to do first

Without the clock framework, every standard Linux driver fails its
clock_get / clk_prepare_enable calls. Today we work around this in
`zx279128-eth.c` by **brute-replaying 22,363 stock register writes** to
the topology controller. That hack:

- Doesn't generalize — every new driver would need its own hack
- Bypasses Linux's clock-tree introspection (`/sys/kernel/debug/clk/`)
- Makes power-gating impossible (no idea which clocks are in use)
- Is fragile — any reorder of register writes can break it

A proper clock driver fixes all of this for every future driver at once.

## What's already done

- ✅ Archaeology — `tasks/00.10.04.mainline-archaeology/` confirms
  `drivers/clk/zte/clk-zx296702.c` is reusable; register model + PLL layout
  match ZX279128S per winnt5's chinadsl analysis
- ✅ ZX279128S overlay drafted — `tasks/00.openwrt-port/kernel-patches/clk/clk-zx279128s.c`
  exists with our SoC-specific bindings (PLL frequencies, mux topology
  for the parts that differ)
- ✅ Defconfig entry — `tasks/00.openwrt-port/kernel-patches/configs/zx279128s_defconfig`
  already has `CONFIG_SOC_ZX279128S=y` planned

## What's NOT done (this task's deliverables)

- [ ] Cherry-pick `clk-zx296702.c` into `zxic/linux-v6.6/drivers/clk/zte/`
- [ ] Apply the `clk-zx279128s.c` overlay
- [ ] Update `drivers/clk/zte/Makefile` and `Kconfig`
- [ ] Update `arch/arm/mach-zx/Kconfig` to make `SOC_ZX279128S` select the new clock driver
- [ ] Compile-clean
- [ ] Boot-test — verify kernel doesn't panic on init
- [ ] Functional test — pick one device (e.g. a kernel-managed timer), confirm `clk_get` succeeds and the clock actually runs
- [ ] Update `zx279128-eth.c` to **prefer** standard `clk_get` over brute-replay (keep replay as fallback initially)
- [ ] Document any deltas vs ZX296702 in `findings/zx279128s_vs_zx296702_clock.md`

## Source commits (where to cherry-pick FROM)

Per `tasks/00.10.04.mainline-archaeology/KERNEL_ARCHAEOLOGY_ES.md` section 2:

- **`5a4658081226`** (2015-06-04, Jun Nie) — "clk: zx: clock support for zx296702" — the primary
- **`4599dd2c9269`** (2015-07-23, Jun Nie) — "clk: zx: audio div clocks" — follow-up (may or may not be needed for our SoC)
- Plus any later fixes between 2015 and 2021-01 — `git log drivers/clk/zte/clk-zx296702.c` on a pre-5.11 checkout

Easiest path: clone `linux v5.10` (last LTS before the removal), grab the file + its history.

## Test plan

```sh
# After resurrection + build:
cat /sys/kernel/debug/clk/clk_summary
# Should list ZX296702 clocks (osc, plls, dividers, gates)

# Then in our eth driver:
struct clk *c = clk_get(dev, "pclk");
# Should return a valid clk, not -ENOENT
```

Verifying success: any clock-using driver that previously had to be
hacked now Just Works.

## Research

Open questions / hypotheses go in `research/<topic>.md` per the
convention in `tasks/00.10.explore/README.md` "Findings flow".

Likely first research files:
- `research/pll_freq_delta.md` — what PLL frequencies differ between ZX296702 and ZX279128S
- `research/missing_clocks.md` — clocks the ZX279128S has that ZX296702 doesn't (need to be added to the resurrected driver)
- `research/clock_consumer_audit.md` — list of drivers that would benefit immediately

## Findings

Stable discoveries get promoted from `research/` to here (currently empty).

## See also

- [Parent: 00.06 platform-drivers](../00.06.platform-drivers/) — the umbrella + cherry-pick catalog
- [00.10.04 mainline-archaeology](../00.10.04.mainline-archaeology/) — the analysis justifying this work
- `tasks/00.openwrt-port/kernel-patches/clk/clk-zx279128s.c` — our ZX279128S overlay (drafted)
- `tasks/00.01.eth-driver/` — primary beneficiary (will remove the brute-replay hack)
- `zxic/linux-v6.6/drivers/clk/zte/` — the destination for the resurrected file
- Memory `gpl_legitimacy_context` — why resurrecting GPL'd Linux code is legitimate
