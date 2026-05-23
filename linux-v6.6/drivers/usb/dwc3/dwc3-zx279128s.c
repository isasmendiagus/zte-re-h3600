// SPDX-License-Identifier: GPL-2.0
/*
 * dwc3-zx279128s.c - SoC glue layer for ZTE ZXIC ZX279128S DWC3 USB3 host.
 *
 * Reverse-engineered from the stock ZTE H3600 firmware (kernel 4.1).
 * The stock wrapper does:
 *   1. ioremap(0x09100000, 1MiB)   - DWC3 core regs
 *   2. ioremap(0x09300000, 1MiB)   - SoC USB ctrl extra region
 *   3. set 4 clock-gate bits in TOPCRM @ phys 0x9400004C:
 *        bit 11 (0x800), bit 14 (0x4000), bit 9 (0x200), bit 10 (0x400)
 *   4. tweak DWC3 internal regs:
 *        DWC3+0xC110 = (val & 0x7FFFF)  | 0x100400
 *        DWC3+0xC12C = (val & 0x3FFFFF) | 0xC800000
 *   5. set bit 20 (0x100000) in SoC USB ctrl @ +0x20
 *   6. allocate child dwc3 platform device and register it
 *
 * In mainline we let DT describe the child snps,dwc3 node and use
 * of_platform_populate() after running steps 3-5.
 */

#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/mfd/syscon.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>

#define ZX_TOPCRM_USB_CLK_REG	0x4C
#define ZX_TOPCRM_USB_CLK_BITS	(BIT(11) | BIT(14) | BIT(9) | BIT(10))

/* DWC3 SoC-specific tweaks (offsets from DWC3 core base) */
#define ZX_DWC3_TWEAK1_OFF	0xC110
#define ZX_DWC3_TWEAK1_MASK	0xFFF80000
#define ZX_DWC3_TWEAK1_VAL	0x100400
#define ZX_DWC3_TWEAK2_OFF	0xC12C
#define ZX_DWC3_TWEAK2_MASK	0xFFC00000
#define ZX_DWC3_TWEAK2_VAL	0xC800000

/* SoC USB control register (extra region) */
#define ZX_USB_CTRL_REG		0x20
#define ZX_USB_CTRL_ENABLE	BIT(20)

struct dwc3_zx279128s {
	struct device		*dev;
	struct regmap		*topcrm;
	void __iomem		*dwc3_base;	/* 0x09100000, used only at probe */
	void __iomem		*usb_ctrl;	/* 0x09300000 */
};

static int dwc3_zx279128s_setup(struct dwc3_zx279128s *zd)
{
	u32 val;

	/* 1. Enable USB clock-gate bits in TOPCRM. Stock writes these one by
	 *    one with udelay(50us) in between. */
	regmap_update_bits(zd->topcrm, ZX_TOPCRM_USB_CLK_REG,
			   BIT(11), BIT(11));
	udelay(50);
	regmap_update_bits(zd->topcrm, ZX_TOPCRM_USB_CLK_REG,
			   BIT(14), BIT(14));
	udelay(50);
	regmap_update_bits(zd->topcrm, ZX_TOPCRM_USB_CLK_REG,
			   BIT(9), BIT(9));
	udelay(150);
	regmap_update_bits(zd->topcrm, ZX_TOPCRM_USB_CLK_REG,
			   BIT(10), BIT(10));
	udelay(50);

	regmap_read(zd->topcrm, ZX_TOPCRM_USB_CLK_REG, &val);
	dev_info(zd->dev, "TOPCRM+0x4C after USB clock-gate enable = 0x%08x\n",
		 val);

	/* 2. DWC3 internal tweaks. Stock pokes these via the DWC3 core base. */
	val = readl(zd->dwc3_base + ZX_DWC3_TWEAK1_OFF);
	val = (val & ~ZX_DWC3_TWEAK1_MASK) | ZX_DWC3_TWEAK1_VAL;
	writel(val, zd->dwc3_base + ZX_DWC3_TWEAK1_OFF);

	val = readl(zd->dwc3_base + ZX_DWC3_TWEAK2_OFF);
	val = (val & ~ZX_DWC3_TWEAK2_MASK) | ZX_DWC3_TWEAK2_VAL;
	writel(val, zd->dwc3_base + ZX_DWC3_TWEAK2_OFF);

	/* 3. Enable SoC USB ctrl bit. */
	val = readl(zd->usb_ctrl + ZX_USB_CTRL_REG);
	writel(val | ZX_USB_CTRL_ENABLE, zd->usb_ctrl + ZX_USB_CTRL_REG);

	usleep_range(50, 100);
	return 0;
}

static int dwc3_zx279128s_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct dwc3_zx279128s *zd;
	struct resource *res;
	int ret;

	zd = devm_kzalloc(dev, sizeof(*zd), GFP_KERNEL);
	if (!zd)
		return -ENOMEM;
	zd->dev = dev;

	zd->topcrm = syscon_regmap_lookup_by_phandle(np, "zte,topcrm");
	if (IS_ERR(zd->topcrm))
		return dev_err_probe(dev, PTR_ERR(zd->topcrm),
				     "missing zte,topcrm phandle\n");

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dwc3");
	if (!res)
		return -ENODEV;
	/* devm_ioremap (not _resource) so we don't reserve the region — the
	 * child snps,dwc3 node owns it. We only need transient access for
	 * the SoC-specific tweaks during probe. */
	zd->dwc3_base = devm_ioremap(dev, res->start, resource_size(res));
	if (!zd->dwc3_base)
		return -ENOMEM;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "ctrl");
	zd->usb_ctrl = devm_ioremap_resource(dev, res);
	if (IS_ERR(zd->usb_ctrl))
		return PTR_ERR(zd->usb_ctrl);

	platform_set_drvdata(pdev, zd);

	ret = dwc3_zx279128s_setup(zd);
	if (ret)
		return ret;

	/* Populate the child snps,dwc3 node — DWC3 core driver takes over. */
	ret = of_platform_populate(np, NULL, NULL, dev);
	if (ret) {
		dev_err(dev, "failed to populate child dwc3 node: %d\n", ret);
		return ret;
	}

	dev_info(dev, "ZX279128S DWC3 glue ready\n");
	return 0;
}

static void dwc3_zx279128s_remove(struct platform_device *pdev)
{
	of_platform_depopulate(&pdev->dev);
}

static const struct of_device_id dwc3_zx279128s_of_match[] = {
	{ .compatible = "zte,zx279128s-dwc3" },
	{},
};
MODULE_DEVICE_TABLE(of, dwc3_zx279128s_of_match);

static struct platform_driver dwc3_zx279128s_driver = {
	.probe = dwc3_zx279128s_probe,
	.remove_new = dwc3_zx279128s_remove,
	.driver = {
		.name = "zx279128s-dwc3",
		.of_match_table = dwc3_zx279128s_of_match,
	},
};
module_platform_driver(dwc3_zx279128s_driver);

MODULE_ALIAS("platform:zx279128s-dwc3");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ZTE ZX279128S DWC3 USB3 glue layer");
