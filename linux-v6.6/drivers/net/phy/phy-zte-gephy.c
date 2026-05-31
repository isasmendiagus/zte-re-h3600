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

/* Vendor link-change interrupt registers (RE'd from stock register_phy_int
 * @ +0x144d4 in plat-zxylzb_9128S.ko + live cable-swap experiment, see
 * tasks/00.01.eth-driver/findings/phy_irq_state_machine_2026-05-27.md):
 *   reg 0x18 = interrupt enable. Stock writes 0x0005 to arm link-state IRQ.
 *   reg 0x1a = status latch. Bit 6 (0x40) reflects link UP, bits 7..9 the
 *              speed code. Read clears the latch.
 */
#define ZTE_GEPHY_INT_ENABLE_REG	0x18
#define   ZTE_GEPHY_INT_LINK_EVT	0x0005
#define ZTE_GEPHY_STATUS_REG		0x1a
#define   ZTE_GEPHY_STATUS_LINK_UP	BIT(6)

/* Extended-page register addresses */
#define ZTE_GEPHY_EXT_LDO_ARM		0xb640
#define   ZTE_GEPHY_EXT_LDO_ENABLE	0x001f

/* TX-DAC drive sub-block — programmed in pairs (ext_addr, ext_data) */
struct zte_gephy_ext_init {
	u16 addr;
	u16 val;
};

/* [2026-05-30] FORCE-DRIVE pattern (stock gephy_tx_dac_drv_force_enable
 * param_2==0, decomp plat-zxylzb_9128S.c:2378-2393). The previous table here
 * was the param_2==1 *reduced* pattern (b676/b677=0, b6c2/b6c1=2/1, b678=0) —
 * which links + RXes but leaves the copper TX driver weak/off, matching the
 * observed "MAC2 counts TX, host sees nothing, zero CRC errors" (un-driven
 * line, not garbled). The force pattern fully enables the copper TX DAC:
 * b676/b677=3, b6c2/b6c1=3, and crucially b678=0xf (was 0).
 */
static const struct zte_gephy_ext_init zte_gephy_tx_dac_init[] = {
	{ 0xb676, 0x0003 },
	{ 0xb677, 0x0003 },
	{ 0xb667, 0x0003 },
	{ 0xb668, 0x0003 },
	{ 0xb6c2, 0x0003 },
	{ 0xb6c1, 0x0003 },
	{ 0xb678, 0x000f },
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

static int zte_gephy_ext_read(struct phy_device *phydev, u16 addr)
{
	int ret;

	ret = phy_write(phydev, ZTE_GEPHY_EXT_ADDR_REG, addr);
	if (ret < 0)
		return ret;
	return phy_read(phydev, ZTE_GEPHY_EXT_DATA_REG);
}

static int zte_gephy_probe(struct phy_device *phydev)
{
	phydev_info(phydev, "ZTE GePHY bound (PHY ID %#010x)\n", phydev->phy_id);
	return 0;
}

static int zte_gephy_config_init(struct phy_device *phydev)
{
	int ret, i, ldo_state;

	/* [Iter 23] Skip LDO arm + TX-DAC writes if PHY analog is already
	 * up. Per agent 7 (phy_init_perturbs_bmu_re.md): re-arming the LDO
	 * power-cycles the PHY analog domain → RGMII glitch → switch fabric
	 * sees link bounce → MAC TX FIFO wedges (mainline doesn't issue the
	 * per-port pon_reset(1<<(N+6)) stock does in extphy_timer_func).
	 * U-Boot already armed the LDO; checking ext 0xb640 == 0x001f lets
	 * us skip the disruptive writes when already armed. The PHY ID is
	 * read in probe so we know the PHY is reachable via MDIO.
	 */
	ldo_state = zte_gephy_ext_read(phydev, ZTE_GEPHY_EXT_LDO_ARM);
	if (ldo_state == ZTE_GEPHY_EXT_LDO_ENABLE) {
		/* [2026-05-29] LDO already armed by U-Boot. SKIP the disruptive LDO
		 * re-arm (avoids the PHY-analog power-cycle / RGMII glitch that wedges
		 * the MAC TX FIFO — Iter 23), but STILL apply the TX-DAC drive enable.
		 * The TX-DAC drives the COPPER TX pair: if U-Boot armed the LDO but did
		 * NOT enable the TX-DAC, the PHY links + RX works but cannot DRIVE TX onto
		 * copper → exactly the observed "RX works, 0 TX egress" symptom. The
		 * TX-DAC writes are non-disruptive (no power-cycle), so applying them when
		 * already-armed is safe.
		 */
		phydev_info(phydev, "config_init: LDO armed (ext 0xb640=0x%04x) — keeping LDO, applying TX-DAC drive\n",
			    ldo_state);
		goto tx_dac;
	}

	phydev_info(phydev, "config_init: arming LDO + TX DAC drive (prior state 0x%04x)\n",
		    ldo_state);

	/* (1) LDO enable. The vendor kernel arms via 0x17=0x2448 then pokes
	 * extended reg 0xb640. Without this the PHY core stays unpowered.
	 */
	ret = phy_write(phydev, ZTE_GEPHY_LDO_CTRL_REG, ZTE_GEPHY_LDO_CTRL_VAL);
	if (ret < 0)
		return ret;
	ret = zte_gephy_ext_write(phydev, ZTE_GEPHY_EXT_LDO_ARM,
				  ZTE_GEPHY_EXT_LDO_ENABLE);
	if (ret < 0)
		return ret;

tx_dac:
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

static int zte_gephy_config_intr(struct phy_device *phydev)
{
	u16 val = (phydev->interrupts == PHY_INTERRUPT_ENABLED)
		  ? ZTE_GEPHY_INT_LINK_EVT : 0;

	return phy_write(phydev, ZTE_GEPHY_INT_ENABLE_REG, val);
}

static irqreturn_t zte_gephy_handle_interrupt(struct phy_device *phydev)
{
	int status;

	/* Stock pattern: read 0x1a TWICE. First read returns the latched
	 * pending state and ARMS the clear; second read returns the
	 * settled state and actually clears the latch. A single read
	 * leaves the latch asserted, the GIC line stays high
	 * (level-triggered), the handler re-enters immediately → infinite
	 * IRQ storm on any PHY whose internal status bit is asserted
	 * (e.g. unconnected PHY[3] on LAN4 firing 14.6M times in 70s).
	 *
	 * Cross-ref: phy_irq_state_machine_2026-05-27.md confirms stock
	 * runs ~3 IRQs per cable transition; we were running ~80k/sec.
	 */
	status = phy_read(phydev, ZTE_GEPHY_STATUS_REG);
	if (status < 0)
		return IRQ_NONE;
	(void)phy_read(phydev, ZTE_GEPHY_STATUS_REG);  /* settle + clear */

	phy_trigger_machine(phydev);
	return IRQ_HANDLED;
}

static struct phy_driver zte_gephy_drivers[] = {
	{
		PHY_ID_MATCH_MODEL(ZTE_GEPHY_PHY_ID),
		.name			= "ZTE ZXIC ZX279128S GePHY",
		/* PHY_GBIT_FEATURES from genphy_* */
		.flags			= PHY_IS_INTERNAL,
		.probe			= zte_gephy_probe,
		.config_init		= zte_gephy_config_init,
		.config_intr		= zte_gephy_config_intr,
		.handle_interrupt	= zte_gephy_handle_interrupt,
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
