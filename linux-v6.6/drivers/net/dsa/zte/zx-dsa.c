// SPDX-License-Identifier: GPL-2.0
/*
 * DSA driver for the ZTE ZX279128S SoC on-chip 4-port ethernet switch.
 *
 * P0 SKELETON (2026-05-30): registers the switch with DSA (4 user ports
 * lan0..3 + CPU port), returns the ZTE tag protocol, and stubs the HW ops.
 * The packet datapath + HW programming are filled in across P1..P3 — see
 * tasks/00.01.eth-driver/findings/dsa_driver_plan.md and memory
 * zte-dsa-foundation for the RE'd register map.
 *
 * Architecture: the existing zx-eth-main.c `sw` netdev is the DSA *conduit*
 * (the CPU<->fabric DMA path). This driver programs the switch fabric and
 * presents per-port netdevs; the tag_zte tagger conveys the port via a small
 * internal tag the conduit stamps into / parses from the DMA descriptor.
 *
 * STATUS: compiles; NOT yet wired to probe (needs the DT node + the conduit
 * relationship — P0 cont./P1). HW ops are stubs (return 0) pending P3.
 *
 * Copyright (C) 2026 Agustin Isasmendi <infra@quecomere.com>
 */

#include <linux/dsa/zte.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <net/dsa.h>

/* 4 user LAN ports (0..3) + CPU port (5). Port 4 is the unused RGMII WAN MAC on
 * the H3600; sized to cover the CPU port index. Refined when the DT/port map is
 * wired (P0 cont.). */
#define ZX_DSA_NUM_PORTS	6
#define ZX_DSA_CPU_PORT		5

struct zx_dsa_priv {
	struct dsa_switch	*ds;
	struct device		*dev;
	/* TODO P0/P1: conduit (sw netdev) ref + switch register access handle */
};

static enum dsa_tag_protocol zx_dsa_get_tag_protocol(struct dsa_switch *ds,
						     int port,
						     enum dsa_tag_protocol mp)
{
	return DSA_TAG_PROTO_ZTE;
}

static int zx_dsa_setup(struct dsa_switch *ds)
{
	struct zx_dsa_priv *priv = ds->priv;

	/* TODO P1: drive the switch-fabric init (reuse zx-eth init helpers),
	 * mark the CPU port, set up the conduit relationship. Stub for now. */
	dev_info(priv->dev, "zx-dsa: setup (skeleton) — %d ports, CPU port %d\n",
		 ds->num_ports, ZX_DSA_CPU_PORT);
	return 0;
}

static void zx_dsa_phylink_get_caps(struct dsa_switch *ds, int port,
				    struct phylink_config *config)
{
	/* TODO P2: per-port phylink caps (internal GePHY, 10/100/1000). */
	__set_bit(PHY_INTERFACE_MODE_INTERNAL, config->supported_interfaces);
	config->mac_capabilities = MAC_10 | MAC_100 | MAC_1000FD;
}

static int zx_dsa_port_enable(struct dsa_switch *ds, int port,
			      struct phy_device *phy)
{
	/* TODO P3: greg port_closed @0x921c004c bit(port) = 0 (open). */
	return 0;
}

static void zx_dsa_port_disable(struct dsa_switch *ds, int port)
{
	/* TODO P3: greg port_closed bit(port) = 1 (closed). */
}

static const struct dsa_switch_ops zx_dsa_switch_ops = {
	.get_tag_protocol	= zx_dsa_get_tag_protocol,
	.setup			= zx_dsa_setup,
	.phylink_get_caps	= zx_dsa_phylink_get_caps,
	.port_enable		= zx_dsa_port_enable,
	.port_disable		= zx_dsa_port_disable,
	/* TODO P3: port_stp_state_set, port_bridge_join/leave, port_fdb_add/del,
	 * port_vlan_add/del, port_fast_age — see dsa_driver_plan.md. */
};

static int zx_dsa_probe(struct platform_device *pdev)
{
	struct zx_dsa_priv *priv;
	struct dsa_switch *ds;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	ds = devm_kzalloc(&pdev->dev, sizeof(*ds), GFP_KERNEL);
	if (!ds)
		return -ENOMEM;

	priv->dev = &pdev->dev;
	priv->ds = ds;

	ds->dev = &pdev->dev;
	ds->num_ports = ZX_DSA_NUM_PORTS;
	ds->ops = &zx_dsa_switch_ops;
	ds->priv = priv;

	platform_set_drvdata(pdev, priv);

	return dsa_register_switch(ds);
}

static int zx_dsa_remove(struct platform_device *pdev)
{
	struct zx_dsa_priv *priv = platform_get_drvdata(pdev);

	if (priv && priv->ds)
		dsa_unregister_switch(priv->ds);

	return 0;
}

static const struct of_device_id zx_dsa_of_match[] = {
	{ .compatible = "zte,zx279128-switch" },
	{ }
};
MODULE_DEVICE_TABLE(of, zx_dsa_of_match);

static struct platform_driver zx_dsa_driver = {
	.probe	= zx_dsa_probe,
	.remove	= zx_dsa_remove,
	.driver	= {
		.name		= "zx279128-dsa",
		.of_match_table	= zx_dsa_of_match,
	},
};
module_platform_driver(zx_dsa_driver);

MODULE_AUTHOR("Agustin Isasmendi <infra@quecomere.com>");
MODULE_DESCRIPTION("ZTE ZX279128S on-chip switch DSA driver");
MODULE_LICENSE("GPL");
