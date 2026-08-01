/* SPDX-License-Identifier: GPL-2.0 */
/*
 * ZTE ZXIC ZX279128S — chip-level init for the PON sub-block.
 *
 * Mirrors stock plat-zxylzb_9128S.ko's init_module pre-TM steps:
 *   A03  pon_reset(0xffffffff) + msleep(10)
 *   A05  pon_base + 0x4001c = 0xf
 *   A06  zx_pon_clk_reset_init(mode=1) — SERDES bring-up
 *
 * This layer is deliberately decoupled from struct zx_eth (the main
 * driver's private struct) — callers pass a small ctx with only the
 * IO bases the helpers need. Keeps zx-pon-plat.c compilable as a
 * standalone unit and avoids dragging the entire eth driver's private
 * state across compilation units.
 *
 * Stock references:
 *   tasks/00.10.02.re-stock-kmods/findings/static_analysis_plat_zxylzb_init.md
 *   tasks/00.01.eth-driver/findings/mainline_gap_matrix.md [A03][A05][A06]
 *   tasks/00.01.eth-driver/findings/stock_init_deep_re_2026-05-27.md
 */

#ifndef _ZX_PON_PLAT_H
#define _ZX_PON_PLAT_H

#include <linux/device.h>
#include <linux/io.h>

/*
 * Context passed by the eth driver to chip-init helpers.
 *   dev         — for dev_info/err logging
 *   pon_early   — ioremap of "pon"  DT reg (0x92000000-0x921bffff)
 *   topcrm      — ioremap of "topcrm" syscon (0x94000000)
 *   sys_ctrl    — ioremap of "sys_ctrl" DT reg (0x94100000) — A02
 *   pin_mux     — ioremap of "pin_mux"  DT reg (0x94200000) — A02
 *   pon_serdes  — ioremap of "pon_serdes" DT reg (0x9fe00000) — A02
 *
 * sys_ctrl / pin_mux / pon_serdes may be NULL on older DTBs — helpers
 * skip cleanly in that case. pon_early + topcrm are required.
 */
struct zx_pon_plat_ctx {
	struct device	*dev;
	void __iomem	*pon_early;
	void __iomem	*topcrm;
	void __iomem	*sys_ctrl;
	void __iomem	*pin_mux;
	void __iomem	*pon_serdes;
};

/*
 * Run the full PON chip-init sequence:
 *   1. pon_reset(0xffffffff)
 *   2. msleep(10)
 *   3. pon_early[0x4001c] = 0xf
 *   4. zx_pon_clk_reset_init(mode=1) — SERDES bring-up incl. band cal
 *
 * Returns 0 on success. Negative errno on SERDES bring-up failure
 * (rxpll lock timeout, missing ioremaps, etc.) — driver may proceed
 * with degraded SERDES state.
 */
int zx_pon_plat_init(const struct zx_pon_plat_ctx *ctx);

#endif /* _ZX_PON_PLAT_H */
