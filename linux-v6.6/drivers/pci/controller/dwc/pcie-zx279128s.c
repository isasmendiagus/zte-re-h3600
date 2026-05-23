// SPDX-License-Identifier: GPL-2.0
/*
 * PCIe RC driver for ZTE ZXIC ZX279128S SoC (DesignWare based).
 *
 * Reverse-engineered from stock H3600 firmware vmlinux (kernel 4.1).
 * See PCIE_DRIVER_DESIGN.md for the full RE notes.
 *
 * Memory map (per-port):
 *   DBI region:        0x0F000000 (port 0) / 0x0F100000 (port 1), 16K
 *   SoC ctrl regs:     0x09500000 (port 0) / 0x09600000 (port 1), 16K
 *                      → LTSSM mirror at +0xDC, bits [22:17] (0x11 = L0)
 *   Outbound MEM win:  0x10000000-0x18000000 (port 0)
 *                      0x20000000-0x28000000 (port 1)
 *
 * Reset / clock control via syscon regmaps:
 *   TOPCRM:     0x94000000 (clocks gating + main resets)
 *   PCIe-CRM:   0x94100000 (sub-resets / PHY)
 *   PCIe-CRM2:  0x94200000 (extra reset bits @ +0x0C)
 */

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/mfd/syscon.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/pci.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>
#include <linux/reset.h>

#include "pcie-designware.h"

#define ZX_PCIE_LTSSM_DBG		0xDC
#define ZX_PCIE_LTSSM_STATE_SHIFT	17
#define ZX_PCIE_LTSSM_STATE_MASK	GENMASK(22, 17)
#define ZX_PCIE_LTSSM_STATE_L0		0x11

/*
 * The TOPCRM/PCIe-CRM bit positions below come from the disassembly of
 * synopsys_pcie_setup() (see PCIE_DRIVER_DESIGN.md). Names are inferred
 * from context — the stock driver uses raw magic constants.
 */
#define ZX_TOPCRM_PCIE0_CLKEN		0x70    /* set 0xb5  → enable clocks */
#define ZX_TOPCRM_PCIE0_RST_DEASSERT	0x70    /* clear bit 8  → release reset */
#define ZX_TOPCRM_SUBRST_REG		0x08    /* OR 0x8000/0x2000/0x4000 */
#define ZX_TOPCRM_PCIE0_PHY_REL		0x74    /* clear bit 0, set bit 0 */
#define ZX_TOPCRM_PCIE0_AUX		0x24    /* clear bit 26 */
#define ZX_PCIECRM_PHY_REG		0x00    /* set bit 5 */
#define ZX_PCIECRM2_LANE_REG		0x0C    /* clear bit 14 */

/* Per-port stride in the stock register-block array is 0x38 bytes; we use
 * a port_id field instead since each instance probes independently. */

struct zx279128s_pcie {
	struct dw_pcie		*pci;
	void __iomem		*soc_ctrl;	/* 0x09500000 / 0x09600000 */
	struct regmap		*topcrm;	/* syscon @ 0x94000000 */
	struct regmap		*pcie_crm;	/* syscon @ 0x94100000 */
	struct regmap		*pcie_crm2;	/* syscon @ 0x94200000 */
	struct clk_bulk_data	*clks;
	int			num_clks;
	struct reset_control	*rst_core;
	struct reset_control	*rst_phy;
	int			port_id;	/* 0 or 1 */
};

#define to_zx_pcie(x)	dev_get_drvdata((x)->dev)

static void zx279128s_pcie_dump_regs(struct zx279128s_pcie *zp, const char *tag,
				     bool include_soc_ctrl)
{
	u32 v;
	struct device *dev = zp->pci->dev;
#define DUMP_RM(rm, off) do { \
	regmap_read(zp->rm, off, &v); \
	dev_info(dev, "  %-12s[0x%02x] = 0x%08x\n", #rm, off, v); \
} while (0)
	dev_info(dev, "REGS @ %s:\n", tag);
	DUMP_RM(topcrm,    0x08);
	DUMP_RM(topcrm,    0x24);
	DUMP_RM(topcrm,    0x4C);
	DUMP_RM(topcrm,    0x70);
	DUMP_RM(topcrm,    0x74);
	DUMP_RM(pcie_crm,  0x70);
	DUMP_RM(pcie_crm,  0x74);
	DUMP_RM(pcie_crm2, 0x0C);
	/* soc_ctrl @ 0x09500000 is only safe to read AFTER controller enable
	 * (soc_ctrl[0x00] |= 0x28). Reading it before causes data abort hang
	 * on cold boot when the block is power-gated. */
	if (include_soc_ctrl) {
		dev_info(dev, "  soc_ctrl[0x00] = 0x%08x\n", readl(zp->soc_ctrl));
		dev_info(dev, "  soc_ctrl[0xDC] = 0x%08x (LTSSM)\n",
			 readl(zp->soc_ctrl + 0xDC));
	}
#undef DUMP_RM
}

static int zx279128s_pcie_setup_port0(struct zx279128s_pcie *zp)
{
	zx279128s_pcie_dump_regs(zp, "before-setup", false);

	/* Full clock+PHY+reset bring-up. U-Boot leaves things half-configured;
	 * stock kernel completes them. Order matters: lane mux first, then
	 * gateable clocks, then subresets, then PHY reset cycle, then enable.
	 */
	/* 0. SerDes lane mux for PCIe (U-Boot only sets PON portion 0x381FF;
	 *    we OR 0x3CE00 to get full 0x3CFFF). */
	regmap_update_bits(zp->topcrm,   0x4C, 0x3CE00,    0x3CE00);
	udelay(100);

	/* 1. PCIe-CRM gateable clocks */
	regmap_update_bits(zp->pcie_crm, 0x70, 0x1AAB5,    0x1AAB5);
	udelay(50);

	/* 2. TOPCRM subresets — bits 13-15, 16, 20-27 */
	regmap_update_bits(zp->topcrm,   0x08, 0x0FF1E000, 0x0FF1E000);
	udelay(200);

	/* 3. Assert PHY reset */
	regmap_update_bits(zp->pcie_crm, 0x74, 0x1B,       0);
	udelay(50);

	/* 4. Lane isolation/iso bits — write EXACT stock value 0x25B005.
	 * Stock w/ WiFi running shows pcie_crm2[0x0C] = 0x25B005:
	 *   bits set: 0,2,12,13,15,18,20,21
	 * U-Boot leaves diff bits 8,10,11,14 set which need to be cleared. */
	regmap_write(zp->pcie_crm2, 0x0C, 0x25B005);
	udelay(500);

	/* 5. Aux clear */
	regmap_update_bits(zp->topcrm,   0x24, BIT(26),    0);
	udelay(50);

	/* 6. Release PHY reset */
	regmap_update_bits(zp->pcie_crm, 0x74, 0x1B,       0x1B);
	udelay(50);

	/* 7. Controller enable: bits 3 + 5 */
	writel(readl(zp->soc_ctrl) | 0x28, zp->soc_ctrl);
	udelay(100);

	/* 8. DBI link-control writes (last steps of stock init).
	 * Configure x1 link width via PORT_LINK_CONTROL approximation
	 * (stock writes to dbi+0xa0 and +0x80). DWC core handles LTSSM_ENABLE
	 * later in its setup_rc, so we don't touch DBI 0x710 here. */
	dw_pcie_dbi_ro_wr_en(zp->pci);
	dw_pcie_writel_dbi(zp->pci, 0xa0,
			   (dw_pcie_readl_dbi(zp->pci, 0xa0) & ~0xf) | 1);
	dw_pcie_writel_dbi(zp->pci, 0x80,
			   dw_pcie_readl_dbi(zp->pci, 0x80) | 0x20);
	dw_pcie_dbi_ro_wr_dis(zp->pci);

	zx279128s_pcie_dump_regs(zp, "after-setup", true);
	return 0;
}

static int zx279128s_pcie_setup_port1(struct zx279128s_pcie *zp)
{
	/*
	 * Translation of synopsys_pcie_setup(port=1) from RE.
	 * Different bits than port 0; some hardcoded magic writes
	 * (lane training params at DBI offsets 0x1B0 / 0x1B4).
	 */
	regmap_update_bits(zp->topcrm, ZX_TOPCRM_PCIE0_CLKEN, 0x1aa00, 0x1aa00);
	udelay(50);

	regmap_update_bits(zp->topcrm, ZX_TOPCRM_SUBRST_REG,
			   0x8000000, 0x8000000);
	udelay(50);

	/* Stock writes 0x202D5A and 0x46C24A to DBI+0x1B4 / DBI+0x1B0.
	 * These are lane training parameters. We poke them via the DWC
	 * core helpers so DBI writes go through the proper ELBI path. */
	dw_pcie_dbi_ro_wr_en(zp->pci);
	dw_pcie_writel_dbi(zp->pci, 0x1B4, 0x202D5A);
	dw_pcie_writel_dbi(zp->pci, 0x1B0, 0x46C24A);
	dw_pcie_dbi_ro_wr_dis(zp->pci);

	regmap_update_bits(zp->topcrm, ZX_TOPCRM_SUBRST_REG,
			   0x2000000, 0x2000000);
	udelay(50);
	regmap_update_bits(zp->topcrm, ZX_TOPCRM_SUBRST_REG,
			   0x4000000, 0x4000000);
	udelay(50);

	regmap_update_bits(zp->topcrm, ZX_TOPCRM_PCIE0_PHY_REL, BIT(3), 0);
	udelay(50);
	regmap_update_bits(zp->pcie_crm2, ZX_PCIECRM2_LANE_REG, BIT(1), 0);
	udelay(50);
	regmap_update_bits(zp->topcrm, ZX_TOPCRM_PCIE0_AUX, BIT(26), 0);
	udelay(50);
	regmap_update_bits(zp->topcrm, ZX_TOPCRM_PCIE0_PHY_REL, BIT(3), BIT(3));
	regmap_update_bits(zp->topcrm, ZX_TOPCRM_PCIE0_RST_DEASSERT,
			   BIT(17), 0);

	regmap_update_bits(zp->pcie_crm, ZX_PCIECRM_PHY_REG, BIT(5), BIT(5));

	regmap_write(zp->topcrm, ZX_TOPCRM_PCIE0_PHY_REL, 0x3F);

	return 0;
}

static int zx279128s_pcie_link_up(struct dw_pcie *pci)
{
	struct zx279128s_pcie *zp = to_zx_pcie(pci);
	u32 dbg;

	/*
	 * SoC mirror of PORT_DEBUG_2 at offset 0xDC of the SoC ctrl block,
	 * NOT in DBI. Bits [22:17] hold the LTSSM state (0x11 = L0).
	 */
	dbg = readl(zp->soc_ctrl + ZX_PCIE_LTSSM_DBG);
	return (FIELD_GET(ZX_PCIE_LTSSM_STATE_MASK, dbg)
			== ZX_PCIE_LTSSM_STATE_L0);
}

static int zx279128s_pcie_start_link(struct dw_pcie *pci)
{
	/* clocks/PHY already up from host_init; nothing extra needed.
	 * DWC core has set LTSSM enable bit during setup_rc. */
	return 0;
}

static int zx279128s_pcie_host_init(struct dw_pcie_rp *pp)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct zx279128s_pcie *zp = to_zx_pcie(pci);
	int ret;

	/*
	 * Pulse PERST# GPIOs to reset PCIe endpoint before bringing up clocks.
	 * Stock pin_set(): base 0x94407000 (verified via zx_map_io iotable):
	 *   bank   = pin >> 4              (16 pins per bank)
	 *   bit    = 1 << (pin & 0xf)
	 *   SET reg= base + bank*0x40 + 0x18  (write 1<<bit -> drive HIGH)
	 *   CLR reg= base + bank*0x40 + 0x1C  (write 1<<bit -> drive LOW)
	 * Pins 53 and 55 -> bank 3 -> base 0x944070C0.
	 *   pin 53 = bit 5 (0x20)
	 *   pin 55 = bit 7 (0x80)
	 */
	{
		void __iomem *gpio = ioremap(0x944070C0, 0x40);
		if (gpio) {
			/* Stock has bank3 lvl reg = 0x20A7 with WiFi running
			 * (bits 0,1,2,5,7,13 set). Pins 48,49,50,53,55,61 high.
			 * Pin 50 (bit 2) is set by U-Boot ("output gpio:50,value:1")
			 * and stays high in stock — likely an MT7915 power enable.
			 * Ensure it's HIGH before PERST# pulse. */
			writel(BIT(0) | BIT(1) | BIT(2) | BIT(13), gpio + 0x18);
			usleep_range(1000, 2000);

			/* PERST# pulse: pin 53 (bit 5), pin 55 (bit 7).
			 * Stock sequence: 10ms low → 200ms high. */
			writel(BIT(5), gpio + 0x1C); usleep_range(10000, 11000);
			writel(BIT(5), gpio + 0x18); msleep(200);
			writel(BIT(7), gpio + 0x1C); usleep_range(10000, 11000);
			writel(BIT(7), gpio + 0x18); msleep(200);

			iounmap(gpio);
			dev_info(pci->dev, "PERST# pulsed + pins 48/49/50/61 driven HIGH\n");
		}
	}

	/*
	 * IMPORTANT: DWC core reads DBI registers (version_detect, iatu_detect)
	 * IMMEDIATELY after host_init returns. So clocks/resets/PHY must be UP
	 * before we return from here — can't defer to start_link.
	 */
	if (zp->port_id == 0)
		ret = zx279128s_pcie_setup_port0(zp);
	else
		ret = zx279128s_pcie_setup_port1(zp);
	if (ret)
		return ret;

	/* Wait briefly for the controller to settle after clock enable */
	usleep_range(1000, 2000);

	dev_info(pci->dev, "ZX279128S PCIe port %d clocks/PHY ready\n",
		 zp->port_id);

	/* Wait up to 200ms for LTSSM to reach L0. If endpoint is connected
	 * (e.g. MT7915), link should come up. If not, return error to avoid
	 * hanging in DWC core's iatu_detect (which reads DBI regs that
	 * require an active controller).
	 */
	{
		int i;
		u32 dbg = 0;
		for (i = 0; i < 200; i++) {
			dbg = readl(zp->soc_ctrl + ZX_PCIE_LTSSM_DBG);
			if (FIELD_GET(ZX_PCIE_LTSSM_STATE_MASK, dbg)
					== ZX_PCIE_LTSSM_STATE_L0) {
				dev_info(pci->dev, "PCIe link up after %dms\n", i);
				/* Give the endpoint MCU 500ms to fully boot
				 * before DWC core enumerates. MT7915 needs this
				 * — without it, MCU command times out at probe. */
				msleep(500);
				return 0;
			}
			usleep_range(1000, 2000);
		}
		dev_err(pci->dev, "PCIe link FAILED to reach L0 (LTSSM=0x%08x) — aborting probe\n",
			dbg);
		return -ENODEV;
	}
}

static const struct dw_pcie_host_ops zx279128s_pcie_host_ops = {
	.host_init = zx279128s_pcie_host_init,
};

static const struct dw_pcie_ops zx279128s_dw_pcie_ops = {
	.link_up    = zx279128s_pcie_link_up,
	.start_link = zx279128s_pcie_start_link,
};

static int zx279128s_pcie_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct zx279128s_pcie *zp;
	struct dw_pcie *pci;
	struct resource *res;
	int ret;

	zp = devm_kzalloc(dev, sizeof(*zp), GFP_KERNEL);
	if (!zp)
		return -ENOMEM;

	pci = devm_kzalloc(dev, sizeof(*pci), GFP_KERNEL);
	if (!pci)
		return -ENOMEM;

	pci->dev = dev;
	pci->ops = &zx279128s_dw_pcie_ops;
	pci->pp.ops = &zx279128s_pcie_host_ops;
	zp->pci = pci;

	if (of_property_read_u32(np, "zte,port-id", &zp->port_id))
		zp->port_id = 0;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "soc_ctrl");
	zp->soc_ctrl = devm_ioremap_resource(dev, res);
	if (IS_ERR(zp->soc_ctrl))
		return PTR_ERR(zp->soc_ctrl);

	zp->topcrm = syscon_regmap_lookup_by_phandle(np, "zte,topcrm");
	if (IS_ERR(zp->topcrm))
		return dev_err_probe(dev, PTR_ERR(zp->topcrm),
				     "missing zte,topcrm\n");

	zp->pcie_crm = syscon_regmap_lookup_by_phandle(np, "zte,pcie-crm");
	if (IS_ERR(zp->pcie_crm))
		return dev_err_probe(dev, PTR_ERR(zp->pcie_crm),
				     "missing zte,pcie-crm\n");

	zp->pcie_crm2 = syscon_regmap_lookup_by_phandle(np, "zte,pcie-crm2");
	if (IS_ERR(zp->pcie_crm2))
		return dev_err_probe(dev, PTR_ERR(zp->pcie_crm2),
				     "missing zte,pcie-crm2\n");

	zp->num_clks = devm_clk_bulk_get_all(dev, &zp->clks);
	if (zp->num_clks < 0)
		return zp->num_clks;

	zp->rst_core = devm_reset_control_get_optional_exclusive(dev, "core");
	if (IS_ERR(zp->rst_core))
		return PTR_ERR(zp->rst_core);

	zp->rst_phy = devm_reset_control_get_optional_exclusive(dev, "phy");
	if (IS_ERR(zp->rst_phy))
		return PTR_ERR(zp->rst_phy);

	platform_set_drvdata(pdev, zp);

	ret = clk_bulk_prepare_enable(zp->num_clks, zp->clks);
	if (ret)
		return ret;

	reset_control_deassert(zp->rst_core);
	reset_control_deassert(zp->rst_phy);

	ret = dw_pcie_host_init(&pci->pp);
	if (ret) {
		dev_err(dev, "failed to initialize host: %d\n", ret);
		goto err_clk;
	}

	dev_info(dev, "ZX279128S PCIe port %d up\n", zp->port_id);
	return 0;

err_clk:
	clk_bulk_disable_unprepare(zp->num_clks, zp->clks);
	return ret;
}

static const struct of_device_id zx279128s_pcie_of_match[] = {
	{ .compatible = "zte,zx279128s-pcie" },
	{},
};

static struct platform_driver zx279128s_pcie_driver = {
	.probe = zx279128s_pcie_probe,
	.driver = {
		.name = "zx279128s-pcie",
		.of_match_table = zx279128s_pcie_of_match,
		.suppress_bind_attrs = true,
	},
};
module_platform_driver(zx279128s_pcie_driver);

MODULE_DESCRIPTION("ZTE ZXIC ZX279128S PCIe controller driver");
MODULE_LICENSE("GPL v2");
