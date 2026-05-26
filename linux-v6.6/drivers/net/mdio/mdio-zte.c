// SPDX-License-Identifier: GPL-2.0
/*
 * MDIO bus driver for the ZTE ZXIC ZX279128S SoC
 *
 * The controller is a small (24-byte) MMIO block that handles standard
 * IEEE 802.3 Clause-22 MDIO transactions. Protocol reverse-engineered
 * from the stock vendor kernel — see
 *   tasks/00.01.eth-driver/findings/mdio_protocol.md
 *
 * Copyright (C) 2026 Agustin Isasmendi <infra@quecomere.com>
 */

#include <linux/bitfield.h>
#include <linux/iopoll.h>
#include <linux/mdio.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/of.h>
#include <linux/of_mdio.h>
#include <linux/phy.h>
#include <linux/platform_device.h>

#define DRV_NAME		"mdio-zte"

#define ZTE_MDIO_WDATA		0x04  /* u16 write data */
#define ZTE_MDIO_RDATA		0x08  /* u16 read data */
#define ZTE_MDIO_DONE		0x10  /* w0 to clear; HW sets nonzero on done */
#define ZTE_MDIO_CTRL		0x14
#define   ZTE_MDIO_CTRL_REGAD	GENMASK(4, 0)
#define   ZTE_MDIO_CTRL_PHYAD	GENMASK(9, 5)
#define   ZTE_MDIO_CTRL_OP_WR	BIT(10)
#define   ZTE_MDIO_CTRL_OP_RD	BIT(11)
#define   ZTE_MDIO_CTRL_GO	BIT(14)

#define ZTE_MDIO_POLL_US	1
#define ZTE_MDIO_TIMEOUT_US	1000

struct zte_mdio {
	void __iomem *base;
	struct mutex lock;	/* serialises the controller */
};

static int zte_mdio_wait_done(struct zte_mdio *ctx)
{
	u32 done;

	return readl_poll_timeout(ctx->base + ZTE_MDIO_DONE, done, done != 0,
				  ZTE_MDIO_POLL_US, ZTE_MDIO_TIMEOUT_US);
}

static int zte_mdio_xfer(struct zte_mdio *ctx, u32 op, int phy, int reg,
			 u16 wdata)
{
	u32 ctrl;
	int ret;

	mutex_lock(&ctx->lock);

	/* Park the controller: drop GO, clear done. */
	writel(0, ctx->base + ZTE_MDIO_CTRL);
	writel(0, ctx->base + ZTE_MDIO_DONE);

	if (op == ZTE_MDIO_CTRL_OP_WR)
		writel(wdata, ctx->base + ZTE_MDIO_WDATA);

	ctrl = op
	     | FIELD_PREP(ZTE_MDIO_CTRL_PHYAD, phy)
	     | FIELD_PREP(ZTE_MDIO_CTRL_REGAD, reg);
	writel(ctrl, ctx->base + ZTE_MDIO_CTRL);
	writel(ctrl | ZTE_MDIO_CTRL_GO, ctx->base + ZTE_MDIO_CTRL);

	ret = zte_mdio_wait_done(ctx);

	/* Drop GO and clear done regardless of outcome. */
	writel(0, ctx->base + ZTE_MDIO_CTRL);
	writel(0, ctx->base + ZTE_MDIO_DONE);

	mutex_unlock(&ctx->lock);
	return ret;
}

static int zte_mdio_read(struct mii_bus *bus, int phy, int reg)
{
	struct zte_mdio *ctx = bus->priv;
	int ret;

	ret = zte_mdio_xfer(ctx, ZTE_MDIO_CTRL_OP_RD, phy, reg, 0);
	if (ret)
		return ret;

	return readl(ctx->base + ZTE_MDIO_RDATA) & 0xffff;
}

static int zte_mdio_write(struct mii_bus *bus, int phy, int reg, u16 val)
{
	struct zte_mdio *ctx = bus->priv;

	return zte_mdio_xfer(ctx, ZTE_MDIO_CTRL_OP_WR, phy, reg, val);
}

static int zte_mdio_probe(struct platform_device *pdev)
{
	struct zte_mdio *ctx;
	struct mii_bus *bus;
	int ret;

	bus = devm_mdiobus_alloc_size(&pdev->dev, sizeof(*ctx));
	if (!bus)
		return -ENOMEM;

	ctx = bus->priv;
	mutex_init(&ctx->lock);

	ctx->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(ctx->base))
		return PTR_ERR(ctx->base);

	bus->name = DRV_NAME;
	snprintf(bus->id, MII_BUS_ID_SIZE, "%s-%pa",
		 DRV_NAME, &pdev->resource[0].start);
	bus->parent = &pdev->dev;
	bus->read = zte_mdio_read;
	bus->write = zte_mdio_write;

	ret = of_mdiobus_register(bus, pdev->dev.of_node);
	if (ret) {
		dev_err(&pdev->dev, "failed to register MDIO bus: %d\n", ret);
		return ret;
	}

	dev_info(&pdev->dev, "ZTE MDIO bus registered\n");

	/* DEBUG (Phase 12): one-shot PHY ID probe across all 32 addresses.
	 * Bypasses phylib so we see the raw bus response without needing a
	 * netdev or phy_attach to be wired up yet. */
	{
		int addr;

		for (addr = 0; addr < 32; addr++) {
			int id1 = zte_mdio_read(bus, addr, 2);  /* MII_PHYSID1 */
			int id2 = zte_mdio_read(bus, addr, 3);  /* MII_PHYSID2 */

			if (id1 == 0xffff && id2 == 0xffff)
				continue;  /* no PHY here */
			if (id1 < 0 || id2 < 0)
				continue;  /* read error */
			dev_info(&pdev->dev,
				 "scan addr %2d: PHY_ID1=%#06x PHY_ID2=%#06x (full=%#010x)\n",
				 addr, id1, id2, (id1 << 16) | id2);
		}
	}

	platform_set_drvdata(pdev, bus);
	return 0;
}

static int zte_mdio_remove(struct platform_device *pdev)
{
	struct mii_bus *bus = platform_get_drvdata(pdev);

	mdiobus_unregister(bus);
	return 0;
}

static const struct of_device_id zte_mdio_of_match[] = {
	{ .compatible = "zte,zx279128s-mdio" },
	{ }
};
MODULE_DEVICE_TABLE(of, zte_mdio_of_match);

static struct platform_driver zte_mdio_driver = {
	.driver = {
		.name = DRV_NAME,
		.of_match_table = zte_mdio_of_match,
	},
	.probe = zte_mdio_probe,
	.remove = zte_mdio_remove,
};
module_platform_driver(zte_mdio_driver);

MODULE_AUTHOR("Agustin Isasmendi <infra@quecomere.com>");
MODULE_DESCRIPTION("ZTE ZX279128S MDIO bus driver");
MODULE_LICENSE("GPL");
