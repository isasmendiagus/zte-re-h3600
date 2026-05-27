# [A03] pon_reset(-1) breaks warm-boot SERDES inheritance

Bench-tested 2026-05-27 during Iter 5 of the gap-matrix-driven roadmap.
Discovered that adding stock's `pon_reset(0xffffffff)` call to mainline
WITHOUT the matching `zx_pon_clk_reset_init` SERDES bring-up regresses
the device state.

## The test

Iter 5 attempted to add three small writes from stock's init_module flow:
- [A03] `pon_reset(0xffffffff)` + `msleep(10)`
- [A04] `TM[0xc008] = 0`
- [A05] `pon_base + 0x4001c = 0xf`

All three commits cited in `mainline_gap_matrix.md` as "🟡 unclear" or
"🟢 informational" severity — defensive parity with stock, not expected
to be path-critical.

## Bench evidence

`pon_serdes_base` reads via debugfs `pipeline_stats` after probe:

| Reg | Before Iter 5 (warm-boot inherit) | After Iter 5 (with pon_reset) | Stock running |
|---|---|---|---|
| `pon_serdes[0x40]` band ena | `0x043c0000` ✓ bit 26 set | **`0x003c0040`** ❌ bit 26 CLEARED | `0x043c0000` |
| `pon_serdes[0x44]` band coarse | `0xea2ca013` ✓ band=0x2c | **`0xeac0a013`** ❌ band=0xc0 (HW default) | `0xea2ca013` |
| `pon_serdes[0x68]` rxpll lock | `0x00001558` ✓ bit 4 set | **`0x00000400`** ❌ lost | `0x00001558` |
| `pon_serdes[0x70]` PLL band ready | `0x01b15555` ✓ bit 24 set | **`0x00000000`** ❌ lost | `0x01b15555` |

The `pon_reset(0xffffffff)` cycles `pon_base[8]` — clearing then restoring
every bit. This pulse propagates through the pon_serdes subsystem and
**resets the SERDES PLL + band-calibration state**.

Without the immediately-following `zx_pon_clk_reset_init` (which stock
does and we deferred), the SERDES stays in this uncalibrated state.
Mainline still boots (the link goes up, MAC layer works) but the SERDES
is operating at default band settings instead of the temperature-
compensated value stock computed.

## Why this matters

Mainline's standard test cycle is **warm-boot from stock via TFTP**:
1. Cold boot → stock runs `zx_pon_clk_reset_init` (band cal at boot temp)
2. SERDES is in cal'd state (`0xea2ca013` for the device's current temp)
3. DTR pulse → power cycle → U-Boot
4. TFTP load mainline → bootm → mainline takes over
5. Mainline inherits stock's SERDES cal — works "for free"

When mainline `pon_reset(-1)` runs, step 5's inheritance is invalidated:
the SERDES state stock left is destroyed, and mainline has no
`zx_pon_clk_reset_init` to re-cal.

## Implication for the gap matrix

**A03 (pon_reset) has a hidden dependency on A06 (zx_pon_clk_reset_init).**
The two must be bundled. Stock does them in sequence; mainline must too.

Updated gap matrix: A03 moves from Layer 1 (small writes) to Layer 2
(SERDES bring-up bundle), to be committed together with A06 as a single
iter (with sub-commits if the bundle exceeds the 200-line guardrail).

## Decision for Iter 5

- **REVERTED**: A03 (pon_reset). Don't commit alone.
- **KEPT**: A05 (`pon[0x4001c] = 0xf`). Harmless, matches stock value
  that mainline currently reads as 0. No side effect on SERDES.
- **KEPT**: A04 (`TM[0xc008] = 0`). Same — write that doesn't break
  anything, brings us closer to stock parity.

Net Iter 5 result: 2 of 3 planned writes added. Bench-test PASS after
revert.

## Lesson learned

Future iters: any gap that says "stock does X" should be checked
against the warm-boot inheritance baseline. If we already inherit a
better state than X would produce, we either need to skip X or bundle
it with the follow-up that re-establishes the state.

Cross-ref:
- `tasks/00.01.eth-driver/findings/mainline_gap_matrix.md` [A03]
- `tasks/00.10.02.re-stock-kmods/findings/static_analysis_plat_zxylzb_init.md` [fn-02] `pon_reset`
- `tasks/00.01.eth-driver/findings/stock_runtime_visibility_2026-05-27.md` (live stock pon_serdes values)
