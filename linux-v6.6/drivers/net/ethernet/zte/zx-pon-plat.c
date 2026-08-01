// SPDX-License-Identifier: GPL-2.0
/*
 * ZTE ZXIC ZX279128S — PON sub-block chip-level init.
 *
 * Stock kmod equivalents (plat-zxylzb_9128S.ko init_module pre-TM steps):
 *   pon_reset(0xffffffff) + msleep(10)
 *   pon_base[0x4001c] = 0xf
 *   zx_pon_clk_reset_init(mode=1) — incl. ref_clk_set, reg_def_set,
 *     serdes_mode_set, TOPCRM clock cycles, rxpll lock spin, PLL band
 *     ready spin, temperature-compensated coarse band cal, sys_ctrl bit
 *
 * Findings refs:
 *   tasks/00.10.02.re-stock-kmods/findings/static_analysis_plat_zxylzb_init.md
 *   tasks/00.01.eth-driver/findings/mainline_gap_matrix.md [A03][A05][A06]
 *   tasks/00.01.eth-driver/findings/iter5_pon_reset_breaks_serdes_2026-05-27.md
 *   tasks/00.01.eth-driver/findings/stock_runtime_visibility_2026-05-27.md
 */

#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/types.h>

#include "zx-pon-plat.h"

/*
 * [A09] SoC AXI bus-matrix / QoS block @ phys 0x00a20000 — mirror of the
 * STOCK KERNEL's `zx279128_init_machine` (vmlinux 4.1.25 @0xc06390f4), NOT
 * of any stock kmod. This is why every driver-level stock-parity audit
 * missed it: stock programs this block from arch_initcall(3), long before
 * plat-zxylzb_9128S.ko loads, so it never appears in the kmod replay table.
 * Mainline 6.6 has no equivalent machine-init hook, so on mainline the
 * block is left at power-on defaults (verified live 2026-07-31: +0x00
 * reads 0x01000000 and +0x78/+0x80/+0x84/+0x88 read 0 — i.e. every field
 * stock programs is unset).
 *
 * Stock writes, in this exact order, each separated by outer_cache.sync():
 *   [+0x80] = 0x40000001   (set:   bit30 + bit0)
 *   [+0x84] = 0xBFFFFFFF   (clear: everything except bit30 — set/clear pair)
 *   [+0x88] = 0x1F0F1F0F   (four 8-bit priority/threshold fields)
 *   [+0x78] = 0x1F0F1F0F   (same shape — second master's fields)
 *   [+0x00] = 0x0D000000   (mode/commit)
 *
 * The 0x1F0F1F0F priority fields + the bit30 set/clear pair are the shape of
 * an interconnect QoS / arbitration configuration. Relevance to this driver:
 * the fabric-ingress endurance wedge (findings/wifi_stage3_wedge_bmu_pool_
 * 2026-07-28.md) halts a fabric-core arbiter under sustained load from the
 * IDM/fabric masters while every datapath accounting bank still reads
 * healthy — the signature of an unarbitrated/starved AXI master rather than
 * an over-charged datapath counter. Restoring stock's arbitration weights is
 * cheap, is exact stock parity, and removes this whole block as a variable.
 *
 * Ref: tasks/00.10.02.re-stock-kmods/findings/static_analysis_vmlinux_platform_init.md [vm-05]
 */
#define ZX_SOC_AXI_QOS_PHYS	0x00a20000UL
#define ZX_SOC_AXI_QOS_SIZE	0x100

static void zx_soc_axi_qos_init(const struct zx_pon_plat_ctx *ctx)
{
	static const struct {
		u32 off;
		u32 val;
	} seq[] = {
		{ 0x80, 0x40000001 },
		{ 0x84, 0xBFFFFFFF },
		{ 0x88, 0x1F0F1F0F },
		{ 0x78, 0x1F0F1F0F },
		{ 0x00, 0x0D000000 },
	};
	void __iomem *qos;
	int i;

	qos = ioremap(ZX_SOC_AXI_QOS_PHYS, ZX_SOC_AXI_QOS_SIZE);
	if (!qos) {
		dev_warn(ctx->dev, "[A09] ioremap(0x%lx) failed — AXI QoS left at POR\n",
			 ZX_SOC_AXI_QOS_PHYS);
		return;
	}

	for (i = 0; i < ARRAY_SIZE(seq); i++) {
		writel(seq[i].val, qos + seq[i].off);
		/* stock interleaves outer_cache.sync() between every write;
		 * mb() is the mainline equivalent (dsb + outer sync on ARM). */
		mb();
	}

	dev_dbg(ctx->dev, "[A09] SoC AXI QoS programmed (stock machine-init parity): [0x00]=0x%08x [0x78]=0x%08x [0x80]=0x%08x [0x88]=0x%08x\n",
		 readl(qos + 0x00), readl(qos + 0x78),
		 readl(qos + 0x80), readl(qos + 0x88));

	iounmap(qos);
}

/*
 * [A03] pon_reset — mirror of stock plat:7744 `pon_reset(mask)`.
 *
 * Stock decomp:
 *   pon_base[8] &= ~mask;
 *   udelay (100x __delay);
 *   pon_base[8] |= mask;
 *
 * Stock calls pon_reset(0xffffffff) at the start of init_module — cycles
 * every bit of pon_base[8], triggering a transient HW reset pulse for
 * all sub-blocks under pon_base.
 *
 * Safe only when followed immediately by zx_pon_clk_reset_init — the
 * reset pulse wipes SERDES PLL+band state, A06 re-establishes it.
 */
static void zx_pon_reset(const struct zx_pon_plat_ctx *ctx, u32 mask)
{
	u32 cur = readl(ctx->pon_early + 8);

	writel(cur & ~mask, ctx->pon_early + 8);
	udelay(200);                          /* stock: 100x __delay ≈ 200us */
	writel(cur | mask,  ctx->pon_early + 8);
}

/*
 * [A06a] SERDES register defaults — mirror of stock plat:8231
 * `reg_def_set`. Pokes 24 default values into pon_serdes_base[0..0x17].
 * "Factory" SERDES baseline written inside zx_pon_clk_reset_init BEFORE
 * the band calibration.
 *
 * The band coarse value at pon_serdes_base[0x44] is INTENTIONALLY left
 * at 0xea00a013 (pre-band-cal) — A06d (band cal) ORs in the
 * temperature-compensated coarse bits to produce final 0xea2ca013.
 */
static const struct {
	u32 off;	/* byte offset from pon_serdes_base */
	u32 val;
} zx_serdes_defaults[] = {
	{ 0x00, 0x800180a7 },	{ 0x04, 0x0000008f },
	{ 0x08, 0x00000540 },	{ 0x0c, 0x00000004 },
	{ 0x10, 0x00000000 },	{ 0x14, 0x018a6400 },
	{ 0x18, 0x00b50140 },	{ 0x1c, 0x01216000 },
	{ 0x20, 0x40000000 },	{ 0x24, 0x0b510007 },
	{ 0x28, 0x00000000 },	{ 0x2c, 0x00000000 },
	{ 0x30, 0xa02e2400 },	{ 0x34, 0xc0593d44 },
	{ 0x38, 0x00000f0f },	{ 0x3c, 0x00000000 },
	{ 0x40, 0x003c0000 },	{ 0x44, 0xea00a013 },
	{ 0x48, 0x101038ca },	{ 0x4c, 0x0005a008 },
	{ 0x50, 0x33333333 },	{ 0x54, 0x33333333 },
	{ 0x58, 0x03e23333 },	{ 0x5c, 0x00040244 },
};

static void zx_serdes_apply_defaults(const struct zx_pon_plat_ctx *ctx)
{
	int i;

	if (!ctx->pon_serdes) {
		dev_dbg(ctx->dev, "[A06a] pon_serdes not mapped — skipping defaults\n");
		return;
	}

	for (i = 0; i < ARRAY_SIZE(zx_serdes_defaults); i++)
		writel(zx_serdes_defaults[i].val,
		       ctx->pon_serdes + zx_serdes_defaults[i].off);

	dev_dbg(ctx->dev, "[A06a] SERDES defaults applied (%d regs). pon_serdes[0x44]=0x%08x (stock pre-band-cal=0xea00a013)\n",
		 (int)ARRAY_SIZE(zx_serdes_defaults),
		 readl(ctx->pon_serdes + 0x44));
}

/*
 * [A06c] PLL integer-divider config — mirror of stock plat:8094
 * `pll_cfg_integer(base, p2, p3, p4, p5)`. `base` points at the
 * ref-clock PLL pair (topcrm + 0x50 / +0x54).
 */
static void zx_pll_cfg_integer(void __iomem *base, u32 p2, u32 p3,
			       u32 p4, u32 p5)
{
	u32 v;

	v = readl(base + 0); writel(v | 0x80000000,        base + 0);
	v = readl(base + 0); writel(v | 0x08000000,        base + 0);
	v = readl(base + 0); writel(v & 0xfeffffff,        base + 0);
	v = readl(base + 0); writel((v & 0xff03ffff) | (p2 << 18), base + 0);
	v = readl(base + 0); writel((v & 0xfffc003f) | (p3 << 6),  base + 0);
	if (p4) {
		v = readl(base + 0);
		writel((v & 0xffffffc7) | (p4 << 3), base + 0);
	}
	if (p5) {
		v = readl(base + 0);
		writel((v & 0xfffffff8) | p5, base + 0);
	}
	v = readl(base + 4); writel(v & 0xf7ffffff,        base + 4);
	v = readl(base + 4); writel(v | 0x04000000,        base + 4);
	v = readl(base + 4); writel(v & 0xfdffffff,        base + 4);
	v = readl(base + 4); writel(v & 0xfeffffff,        base + 4);
	v = readl(base + 4); writel(v & 0xff000000,        base + 4);

	udelay(200);                          /* stock: 100x __delay ≈ 200us */

	v = readl(base + 0); writel(v & 0x7fffffff,        base + 0);
}

/*
 * [A06c] Reference clock PLL setup — mirror of stock plat:8206
 * `ref_clk_set(mode)`. We only port the mode=1 (kernel) path — U-Boot
 * already did its mode=0 fractional setup before mainline runs.
 */
static void zx_ref_clk_set(const struct zx_pon_plat_ctx *ctx, int mode)
{
	void __iomem *base;

	if (!ctx->topcrm) {
		dev_dbg(ctx->dev, "[A06c] topcrm not mapped — skipping ref_clk_set\n");
		return;
	}
	base = ctx->topcrm + 0x50;

	/* clear MSB before reconfigure */
	writel(readl(base) & 0x7fffffff, base);

	if (mode == 1) {
		zx_pll_cfg_integer(base, 1, 0x32, 4, 2);
	} else {
		dev_warn(ctx->dev, "[A06c] ref_clk_set mode=%d not implemented (only mode=1)\n",
			 mode);
		return;
	}

	udelay(100);                          /* stock: 50x __delay ≈ 100us */
	dev_dbg(ctx->dev, "[A06c] ref_clk_set(mode=%d) done. topcrm[0x50]=0x%08x\n",
		 mode, readl(base));
}

/*
 * [A06b] SERDES mode = 1 (standard GE) — mirror of stock plat:7924
 * `serdes_mode_set(1)`. 7 read-modify-writes on
 * pon_serdes_base[0, 2, 5, 8, 9].
 */
static void zx_serdes_mode_set_1(const struct zx_pon_plat_ctx *ctx)
{
	void __iomem *s;
	u32 v;

	if (!ctx->pon_serdes) {
		dev_dbg(ctx->dev, "[A06b] pon_serdes not mapped — skipping mode set\n");
		return;
	}
	s = ctx->pon_serdes;

	v = readl(s + 0x00); writel((v & 0xffffff00) | 0xa5,     s + 0x00);
	v = readl(s + 0x08); writel((v & 0xffffff00) | 0x20,     s + 0x08);
	v = readl(s + 0x14); writel((v & 0xffff00ff) | 0x5800,   s + 0x14);
	v = readl(s + 0x20); writel(v & 0x00ffffff,              s + 0x20);
	v = readl(s + 0x24); writel((v & 0xffffff00) | 0x03,     s + 0x24);
	v = readl(s + 0x24); writel((v & 0xff00ffff) | 0x570000, s + 0x24);
	v = readl(s + 0x24); writel((v & 0x00ffffff) | 0x07000000, s + 0x24);

	dev_dbg(ctx->dev, "[A06b] SERDES mode=1 set. pon_serdes[0x00]=0x%08x [0x24]=0x%08x\n",
		 readl(s + 0x00), readl(s + 0x24));
}

/*
 * [A06d] Full SERDES bring-up — mirror of stock plat:8266
 * `zx_pon_clk_reset_init(mode)`. Ties together A06a/b/c, TOPCRM[0x08]
 * clock cycles, rxpll lock + PLL band ready waits, temperature-
 * compensated coarse band cal, sys_ctrl + final TOPCRM enable.
 *
 * Hardcoded CPU temp = 30°C (matches bench's "warm/normal" band on
 * stock; final coarse → 0x2c via temp 10..58 → coarse-1 path).
 * TODO: hook thermal_zone_get_temp() for real read.
 */
static int zx_pon_clk_reset_init(const struct zx_pon_plat_ctx *ctx, int mode)
{
	void __iomem *crm = ctx->topcrm;
	void __iomem *sr = ctx->pon_serdes;
	int retries;
	u32 v, raw_coarse, coarse, temp_c;

	if (!crm || !sr) {
		dev_warn(ctx->dev, "[A06d] topcrm/pon_serdes not mapped — SERDES bring-up SKIPPED\n");
		return -ENODEV;
	}

	zx_ref_clk_set(ctx, mode);

	/* TOPCRM[0x08] clock cycle: disable bits 4+5, delay, re-enable
	 * bit 5 first (the SERDES sub-clock that gates apb access). */
	v = readl(crm + 0x08); writel(v & ~0x20u, crm + 0x08);
	v = readl(crm + 0x08); writel(v & ~0x10u, crm + 0x08);
	udelay(20);                              /* stock: 10x __delay */
	v = readl(crm + 0x08); writel(v | 0x20u, crm + 0x08);
	udelay(20);

	zx_serdes_apply_defaults(ctx);
	zx_serdes_mode_set_1(ctx);

	v = readl(crm + 0x08); writel(v | 0x10u, crm + 0x08);

	/* rxpll lock — stock spins forever; we cap at 100ms. Cold boot or
	 * a heavy TOPCRM cycle can take a few hundred us; 5ms was too tight. */
	retries = 2000;                              /* 2000 × 50us = 100ms */
	while ((readl(sr + 0x68) & 0x10u) == 0 && --retries > 0)
		udelay(50);
	if (retries <= 0) {
		dev_err(ctx->dev, "[A06d] rxpll lock timeout (100ms) — pon_serdes[0x68]=0x%08x\n",
			readl(sr + 0x68));
		return -ETIMEDOUT;
	}
	dev_dbg(ctx->dev, "[A06d] rxpll_ready (waited %d × 50us)\n", 2000 - retries);

	/* PLL band ready (stock: 20 retries) */
	retries = 20;
	while ((readl(sr + 0x70) & 0x01000000u) == 0 && --retries > 0)
		udelay(50);
	if (retries <= 0) {
		dev_err(ctx->dev, "[A06d] PLL band-ready timeout — pon_serdes[0x70]=0x%08x\n",
			readl(sr + 0x70));
		return -ETIMEDOUT;
	}

	raw_coarse = ((readl(sr + 0x70) << 8) >> 26) & 0x3f;

	temp_c = 30;
	coarse = raw_coarse;
	if ((int)temp_c < -6)
		coarse = (coarse + 1) & 0x3f;
	else if (temp_c > 9) {
		if (temp_c >= 10 && temp_c < 59)
			coarse = (coarse - 1) & 0x3f;
		else if (temp_c >= 59 && temp_c < 92)
			coarse = (coarse - 2) & 0x3f;
		else
			coarse = (coarse - 3) & 0x3f;
	}
	dev_dbg(ctx->dev, "[A06d] serdes band cpu_temper:%u coarse:0x%x (raw 0x%x)\n",
		 temp_c, coarse, raw_coarse);

	v = readl(sr + 0x44);
	writel((v & 0xffc0ffffu) | (coarse << 16), sr + 0x44);

	v = readl(sr + 0x40); writel(v | 0x04000000u, sr + 0x40);

	dev_dbg(ctx->dev, "[A06d] band calc fin — pon_serdes[0x44]=0x%08x [0x40]=0x%08x\n",
		 readl(sr + 0x44), readl(sr + 0x40));

	/* sys_ctrl bit clear — purpose unknown; likely gates a downstream
	 * SERDES output. Optional if sys_ctrl wasn't mapped. */
	if (ctx->sys_ctrl) {
		v = readl(ctx->sys_ctrl + 0x10);
		writel(v & ~0x800u, ctx->sys_ctrl + 0x10);
	}

	v = readl(crm + 0x0c); writel(v | 0x1e0u, crm + 0x0c);

	return 0;
}

/*
 * Public entry — full chip-init sequence (A03 + A05 + A06). Caller is
 * the main eth driver from its probe path after ioremaps complete.
 */
int zx_pon_plat_init(const struct zx_pon_plat_ctx *ctx)
{
	int rc;

	if (!ctx || !ctx->pon_early || !ctx->topcrm) {
		pr_err("zx_pon_plat_init: missing pon_early/topcrm\n");
		return -EINVAL;
	}

	/* [A09] SoC AXI bus-matrix/QoS — stock does this from machine init
	 * (arch_initcall 3), i.e. BEFORE any datapath block is touched, so it
	 * runs first here too. */
	zx_soc_axi_qos_init(ctx);

	/* [A03] pon_reset(0xffffffff) + 10ms settle. Cycles every bit of
	 * pon_base[8], triggering a HW reset pulse for the pon sub-blocks.
	 * Safe because A06 (zx_pon_clk_reset_init) runs immediately after
	 * to re-establish the SERDES state that pon_reset wipes. */
	zx_pon_reset(ctx, 0xffffffffU);
	msleep(10);
	dev_dbg(ctx->dev, "[A03] pon_reset(0xffffffff) done. pon[8]=0x%08x\n",
		 readl(ctx->pon_early + 8));

	/* [Iter 22] Stock init_module (plat-zxylzb_9128S line 8925-8930)
	 * does 3 pon[+0x400XX] writes here, in this order, before TM init.
	 * Per agent 5 hw_write_lock_pattern_re.md Q1.2.6 — the 0x40018 write
	 * is the "single most plausible state divergence" between stock and
	 * mainline; possibly an eth subsystem block-enable.
	 */
	writel(2,          ctx->pon_early + 0x40018);	/* purpose unknown */
	writel(0xf,        ctx->pon_early + 0x4001c);	/* [A05] */
	writel(0xffffff7f, ctx->pon_early + 0x40044);	/* PON IRQ mask: bit 7 unmasked */

	dev_dbg(ctx->dev, "PON chip pre-init: pon[0x40018]=0x%08x pon[0x4001c]=0x%08x pon[0x40044]=0x%08x\n",
		 readl(ctx->pon_early + 0x40018),
		 readl(ctx->pon_early + 0x4001c),
		 readl(ctx->pon_early + 0x40044));

	/* [A06d] Full SERDES bring-up — must run immediately after A03 to
	 * re-establish the band calibration that pon_reset just wiped. */
	rc = zx_pon_clk_reset_init(ctx, 1);
	if (rc)
		dev_warn(ctx->dev, "[A06] zx_pon_clk_reset_init returned %d — SERDES may be uncalibrated\n",
			 rc);

	return rc;
}
