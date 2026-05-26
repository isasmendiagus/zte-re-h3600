// SPDX-License-Identifier: GPL-2.0
/*
 * Driver for the gigabit Ethernet PHY integrated in the ZTE ZXIC
 * ZX279128S SoC.
 *
 * Identifies via PHY ID 0x84b9_5031 (top 28 bits; bottom 4 are silicon
 * revision and are masked).  Four PHY instances live on the SoC's
 * private MDIO bus (drivers/net/mdio/mdio-zte.c) at addresses 10..13;
 * they are wired to the four user-facing MAC ports through the on-chip
 * switch.
 *
 * The PHY exposes a vendor-specific extended-register page through the
 * standard IEEE-802.3 Clause-22 "page select" pattern:
 *
 *   mdio_write(0x10, <ext_addr>);
 *   mdio_write(0x11, <ext_data>);
 *
 * Reverse-engineered (in 2026) from the stock vendor kernel — see
 *   refs/zte-zx279128R/findings.md and
 *   tasks/00.10.02.re-stock-kmods/findings/decomp_all_plat_zxylzb_9128S.c
 * The vendor's config_init for these PHYs performs two analog block
 * power-ups:
 *
 *   1. LDO enable: arm via reg 0x17 then poke extended reg 0xb640.
 *   2. TX-DAC drive enable: write a fixed pattern across extended regs
 *      0xb676/77/67/68/c2/c1/78/69.
 *
 * Without (1) the PHY core stays in low-power and the gigabit link
 * does not come up.
 *
 * Copyright (C) 2026 Agustin Isasmendi <infra@quecomere.com>
 */

#include <linux/module.h>
#include <linux/phy.h>

#define ZTE_GEPHY_PHY_ID		0x84b95031
#define ZTE_GEPHY_PHY_ID_MASK		0xfffffff0

/* Indirect / extended page access */
#define ZTE_GEPHY_EXT_ADDR_REG		0x10  /* page-select / ext addr */
#define ZTE_GEPHY_EXT_DATA_REG		0x11  /* ext data */
#define ZTE_GEPHY_LDO_CTRL_REG		0x17  /* mandatory write before LDO arm */
#define   ZTE_GEPHY_LDO_CTRL_VAL	0x2448

/* Extended-page register addresses */
#define ZTE_GEPHY_EXT_LDO_ARM		0xb640
#define   ZTE_GEPHY_EXT_LDO_ENABLE	0x001f

/* TX-DAC drive sub-block — programmed in pairs (ext_addr, ext_data) */
struct zte_gephy_ext_init {
	u16 addr;
	u16 val;
};

static const struct zte_gephy_ext_init zte_gephy_tx_dac_init[] = {
	{ 0xb676, 0x0000 },
	{ 0xb677, 0x0000 },
	{ 0xb667, 0x0003 },
	{ 0xb668, 0x0003 },
	{ 0xb6c2, 0x0002 },
	{ 0xb6c1, 0x0001 },
	{ 0xb678, 0x0000 },
	{ 0xb669, 0x0000 },
};

static int zte_gephy_ext_write(struct phy_device *phydev, u16 addr, u16 val)
{
	int ret;

	ret = phy_write(phydev, ZTE_GEPHY_EXT_ADDR_REG, addr);
	if (ret < 0)
		return ret;
	return phy_write(phydev, ZTE_GEPHY_EXT_DATA_REG, val);
}

static int zte_gephy_probe(struct phy_device *phydev)
{
	phydev_info(phydev, "ZTE GePHY bound (PHY ID %#010x)\n", phydev->phy_id);
	return 0;
}

static int zte_gephy_config_init(struct phy_device *phydev)
{
	int ret, i;

	phydev_info(phydev, "config_init (LDO arm + TX DAC drive enable)\n");

	/* (1) LDO enable. The vendor kernel arms via 0x17=0x2448 then pokes
	 * extended reg 0xb640. Without this the PHY core stays unpowered. */
	ret = phy_write(phydev, ZTE_GEPHY_LDO_CTRL_REG, ZTE_GEPHY_LDO_CTRL_VAL);
	if (ret < 0)
		return ret;
	ret = zte_gephy_ext_write(phydev, ZTE_GEPHY_EXT_LDO_ARM,
				  ZTE_GEPHY_EXT_LDO_ENABLE);
	if (ret < 0)
		return ret;

	/* (2) TX-DAC drive enable — eight extended-register writes. */
	for (i = 0; i < ARRAY_SIZE(zte_gephy_tx_dac_init); i++) {
		ret = zte_gephy_ext_write(phydev,
					  zte_gephy_tx_dac_init[i].addr,
					  zte_gephy_tx_dac_init[i].val);
		if (ret < 0)
			return ret;
	}

	return 0;
}

static struct phy_driver zte_gephy_drivers[] = {
	{
		PHY_ID_MATCH_MODEL(ZTE_GEPHY_PHY_ID),
		.name		= "ZTE ZXIC ZX279128S GePHY",
		/* PHY_GBIT_FEATURES from genphy_* */
		.flags		= PHY_IS_INTERNAL,
		.probe		= zte_gephy_probe,
		.config_init	= zte_gephy_config_init,
	},
};

module_phy_driver(zte_gephy_drivers);

static const struct mdio_device_id __maybe_unused zte_gephy_tbl[] = {
	{ PHY_ID_MATCH_MODEL(ZTE_GEPHY_PHY_ID) },
	{ }
};
MODULE_DEVICE_TABLE(mdio, zte_gephy_tbl);

MODULE_AUTHOR("Agustin Isasmendi <infra@quecomere.com>");
MODULE_DESCRIPTION("ZTE ZXIC ZX279128S internal GePHY driver");
MODULE_LICENSE("GPL");
