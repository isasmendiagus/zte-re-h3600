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
#include <linux/crc-itu-t.h>
#include <linux/delay.h>
#include <linux/etherdevice.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <net/dsa.h>
#include <uapi/linux/if_bridge.h>

/* 4 user LAN ports (0..3) + CPU port (5). Port 4 is the unused RGMII WAN MAC on
 * the H3600; sized to cover the CPU port index. Refined when the DT/port map is
 * wired (P0 cont.).
 */
#define ZX_DSA_NUM_PORTS	6
#define ZX_DSA_USER_PORTS	4	/* lan0..3 */
#define ZX_DSA_CPU_PORT		5

/* Port isolation (SBRAG reg 0x39 @ PP 0x83c0 + regport*4, 1 byte/port).
 * Stored byte = allow-bitmap in REGPORT bit-space (set bit = may forward there).
 * Both the slot index and the bit positions are remapped logical->regport via
 * this table (RE'd from tm_port_isolate_set, decomp_all_tm.c:36297-36328).
 */
#define ZX_ISOLATE_BASE		0x3c0	/* PP window offset (phys 0x923883c0) */
static const u8 zx_regport[8] = { 1, 2, 3, 4, 5, 0, 6, 7 };

/* NPP register window base (greg per-port control lives here). TODO: obtain
 * from DT reg / share with the conduit (zx-eth) instead of hardcoding.
 */
#define ZX_NPP_PHYS		0x921c0000UL
#define ZX_NPP_SIZE		0x1000

/* PP/SBRAG register window (FDB MAC table + port isolation). */
#define ZX_PP_PHYS		0x92388000UL
#define ZX_PP_SIZE		0x1000

/* SBRAG indirect FDB protocol (offsets from PP base; memory zte-dsa-foundation).
 * NOTE: the CORRECT offsets are 0x14/18/1c/20/24 — the legacy zx-eth-main.c
 * constants were +0x800 too high (0x388814...). We use the right ones here.
 */
#define ZX_SBRAG_CMD		0x14	/* ram_addr | mem_id<<22 | rw<<27 | mode<<31 */
#define ZX_SBRAG_BUSY		0x18	/* bit0 == 1 -> access complete */
#define ZX_SBRAG_D0		0x1c	/* commit register (write last) */
#define ZX_SBRAG_D1		0x20
#define ZX_SBRAG_D2		0x24
#define ZX_SBRAG_MEMID_UC	0	/* unicast MAC table */
#define ZX_SBRAG_MEMID_VLAN	4	/* VLAN table */

/* greg per-port control (memory zte-dsa-foundation):
 *   STP state  @+0x44, 3 bits/port (shift = phys_port*3): HW 0=Dis 1=Blk 2=Lis 3=Lrn 4=Fwd
 *   STP enable @+0x40 (must be set for the STP state field to take effect)
 *   port_closed@+0x4c, 1 bit/port (1 = disabled)
 */
#define ZX_GREG_STP_EN		0x40
#define ZX_GREG_STP_STATE	0x44
#define ZX_GREG_PORT_CLOSED	0x4c

struct zx_dsa_priv {
	struct dsa_switch	*ds;
	struct device		*dev;
	void __iomem		*regs;	/* NPP window (greg) — see TODO above */
	void __iomem		*pp_regs; /* PP/SBRAG window (FDB, isolation) */
	u8			bridged;  /* bitmap of user ports in a bridge */
	int			br_num[ZX_DSA_NUM_PORTS]; /* dsa_bridge.num per port */
	/* TODO P0/P1: conduit (sw netdev) ref for the datapath/tag */
};

static void zx_greg_rmw(struct zx_dsa_priv *priv, u32 off, u32 mask, u32 val)
{
	u32 v = readl(priv->regs + off);

	v = (v & ~mask) | (val & mask);
	writel(v, priv->regs + off);
}

/* DSA port -> chip phys port. For the 4 LAN user ports (0..3) this is identity;
 * the CPU/other ports use the stock getPort remap (0..4->0..4, 6->5, 7->6).
 * TODO: full remap when CPU-port ops are wired.
 */
static inline int zx_phys_port(int port)
{
	return port;
}

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
	 * mark the CPU port, set up the conduit relationship. Stub for now.
	 */
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
	struct zx_dsa_priv *priv = ds->priv;
	int p = zx_phys_port(port);

	/* greg has no slot for the CPU port (logical 5); skip it. */
	if (port >= ZX_DSA_USER_PORTS)
		return 0;

	/* greg port_closed bit(p) = 0 -> open. NOT yet HW-verified. */
	zx_greg_rmw(priv, ZX_GREG_PORT_CLOSED, BIT(p), 0);
	return 0;
}

static void zx_dsa_port_disable(struct dsa_switch *ds, int port)
{
	struct zx_dsa_priv *priv = ds->priv;
	int p = zx_phys_port(port);

	/* greg has no slot for the CPU port (logical 5); skip it. */
	if (port >= ZX_DSA_USER_PORTS)
		return;

	/* greg port_closed bit(p) = 1 -> closed. */
	zx_greg_rmw(priv, ZX_GREG_PORT_CLOSED, BIT(p), BIT(p));
}

static void zx_dsa_port_stp_state_set(struct dsa_switch *ds, int port, u8 state)
{
	struct zx_dsa_priv *priv = ds->priv;
	int p = zx_phys_port(port);
	u32 hw, shift;

	/* greg STP has no slot for the CPU port (logical 5); it's SW-handled. */
	if (port >= ZX_DSA_USER_PORTS)
		return;

	/* Map Linux BR_STATE_* -> chip STP encoding (zte-dsa-foundation):
	 * 0=Disabled 1=Blocking 2=Listening 3=Learning 4=Forwarding.
	 */
	switch (state) {
	case BR_STATE_DISABLED:
		hw = 0;
		break;
	case BR_STATE_BLOCKING:
		hw = 1;
		break;
	case BR_STATE_LISTENING:
		hw = 2;
		break;
	case BR_STATE_LEARNING:
		hw = 3;
		break;
	case BR_STATE_FORWARDING:
		hw = 4;
		break;
	default:
		dev_warn(priv->dev, "unsupported STP state %u on port %d\n",
			 state, port);
		return;
	}

	/* enable STP for this port, then write the 3-bit state field. NOT yet
	 * HW-verified (writes are spec-backed; confirm via memdump-readback).
	 */
	zx_greg_rmw(priv, ZX_GREG_STP_EN, BIT(p), BIT(p));
	shift = p * 3;
	zx_greg_rmw(priv, ZX_GREG_STP_STATE, 0x7u << shift, hw << shift);
}

/* --- SBRAG FDB (unicast MAC table) -------------------------------------- */

static int zx_sbrag_wait(struct zx_dsa_priv *priv)
{
	int i;

	for (i = 0; i < 100; i++) {
		if (readl(priv->pp_regs + ZX_SBRAG_BUSY) & 1)
			return 0;
		udelay(2);
	}
	return -ETIMEDOUT;
}

/* Commit one entry at table slot `addr` in memory `mem_id` (rw=0 write).
 * Write order D2 -> D1 -> D0 (D0 commits), matching stock sbrg_set_indreg_wr.
 */
static int zx_sbrag_write_entry(struct zx_dsa_priv *priv, u32 mem_id, u16 addr,
				u32 d0, u32 d1, u32 d2)
{
	int ret = zx_sbrag_wait(priv);

	if (ret)
		return ret;

	writel((addr & 0xfff) | (mem_id << 22), priv->pp_regs + ZX_SBRAG_CMD);
	writel(d2, priv->pp_regs + ZX_SBRAG_D2);
	writel(d1, priv->pp_regs + ZX_SBRAG_D1);
	writel(d0, priv->pp_regs + ZX_SBRAG_D0);
	return 0;
}

/* Prefetch + read one entry (rw=1). */
static int zx_sbrag_read_entry(struct zx_dsa_priv *priv, u32 mem_id, u16 addr,
			       u32 *d0, u32 *d1, u32 *d2)
{
	int ret = zx_sbrag_wait(priv);

	if (ret)
		return ret;

	writel((addr & 0xfff) | (mem_id << 22) | (1u << 27),
	       priv->pp_regs + ZX_SBRAG_CMD);	/* rw=1 prefetch */
	ret = zx_sbrag_wait(priv);
	if (ret)
		return ret;

	*d0 = readl(priv->pp_regs + ZX_SBRAG_D0);
	*d1 = readl(priv->pp_regs + ZX_SBRAG_D1);
	*d2 = readl(priv->pp_regs + ZX_SBRAG_D2);
	return 0;
}

/* SBRAG hash mode/width registers (PP window offsets). */
#define ZX_SBRAG_HASH_MODE	0x180	/* bit3: fold VLAN into the hash */
#define ZX_SBRAG_TABLE_SEL	0x184	/* [1:0]: 0=10bit 1=8bit 2=9bit */

/* Real stock sbrg_hash (RE'd from tm.ko sbrg_hash @decomp_all_tm.c:8204):
 * CRC-16/CCITT (poly 0x1021, init 0, MSB-first, no final xor) over the 8 bytes
 * {vlan_hi, vlan_lo, MAC0..MAC5} (VLAN folded only if hash_mode set), then
 * masked to the table-sel width. crc_itu_t() is exactly this CRC. The width +
 * hash_mode are read live from the PP regs so we match whatever the HW uses.
 */
static u16 zx_sbrag_hash(struct zx_dsa_priv *priv, const unsigned char *mac,
			 u16 vid)
{
	u8 buf[8];
	u16 h;

	if (readl(priv->pp_regs + ZX_SBRAG_HASH_MODE) & BIT(3)) {
		buf[0] = (vid >> 8) & 0xff;	/* vlan_hi */
		buf[1] = vid & 0xff;		/* vlan_lo */
	} else {
		buf[0] = 0;
		buf[1] = 0;
	}
	memcpy(&buf[2], mac, ETH_ALEN);		/* MAC0..MAC5, OUI first */

	h = crc_itu_t(0, buf, sizeof(buf)) & 0x3ff;	/* 10-bit raw */
	switch (readl(priv->pp_regs + ZX_SBRAG_TABLE_SEL) & 0x3) {
	case 1:		return h & 0x0ff;	/* 256 buckets (live default) */
	case 2:		return h & 0x1ff;	/* 512 */
	default:	return h & 0x3ff;	/* 1024 */
	}
}

static int zx_dsa_port_fdb_add(struct dsa_switch *ds, int port,
			       const unsigned char *addr, u16 vid,
			       struct dsa_db db)
{
	struct zx_dsa_priv *priv = ds->priv;
	int p = zx_phys_port(port);
	/* HW splits the MAC OUI-first: high2 = MAC[0..1], low4 = MAC[2..5],
	 * big-endian-packed (stock sbrg_add_mactable, decomp_all_tm.c:10706+).
	 */
	u16 mac_high2 = addr[0] << 8 | addr[1];
	u32 mac_low4 = addr[2] << 24 | addr[3] << 16 | addr[4] << 8 | addr[5];
	u32 d0, d1, d2;

	/* Entry layout (stock sbrg_add_mactable, memory zte-dsa-foundation):
	 *  D0 = mac_low4>>24 | mac_high2<<8 | vlan<<24
	 *  D1 = (status&0xf)<<4 | (vlan>>8)&0xf | smac_ctrl<<8 | dmac_ctrl<<9
	 *  D2 = port_id | mac_low4<<8 ;  status=0xF = static present.
	 */
	d0 = (mac_low4 >> 24) | ((u32)vid << 24) | ((u32)mac_high2 << 8);
	d1 = (0xFu << 4) | ((vid >> 8) & 0xf);
	d2 = (p & 0xff) | (mac_low4 << 8);

	return zx_sbrag_write_entry(priv, ZX_SBRAG_MEMID_UC,
				    zx_sbrag_hash(priv, addr, vid),
				    d0, d1, d2);
}

static int zx_dsa_port_fdb_del(struct dsa_switch *ds, int port,
			       const unsigned char *addr, u16 vid,
			       struct dsa_db db)
{
	struct zx_dsa_priv *priv = ds->priv;

	/* First approximation: zero the hash slot. Proper delete is
	 * lookup-then-zero (match {mac,vlan,status!=0}); TODO with the real hash.
	 */
	return zx_sbrag_write_entry(priv, ZX_SBRAG_MEMID_UC,
				    zx_sbrag_hash(priv, addr, vid),
				    0, 0, 0);
}

/* --- VLAN table (SBRAG mem_id=4; 2 bits/port membership in D0) ----------- */

static int zx_dsa_port_vlan_add(struct dsa_switch *ds, int port,
				const struct switchdev_obj_port_vlan *vlan,
				struct netlink_ext_ack *extack)
{
	struct zx_dsa_priv *priv = ds->priv;
	int p = zx_phys_port(port);
	u32 d0, d1, d2, shift = p * 2 + 1;
	u32 attr;
	int ret;

	/* attr: 2-bit per-port membership/tag mode (stock tm_vlantable_add_set
	 * 0..3). Best-effort mapping pending RE of the exact encoding (TODO):
	 * untagged member vs tagged member.
	 */
	attr = (vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED) ? 2 : 3;

	ret = zx_sbrag_read_entry(priv, ZX_SBRAG_MEMID_VLAN, vlan->vid,
				  &d0, &d1, &d2);
	if (ret)
		return ret;

	d0 = (d0 & ~(0x3u << shift)) | (attr << shift);
	d0 |= 1;	/* bit0: row has at least one member */

	return zx_sbrag_write_entry(priv, ZX_SBRAG_MEMID_VLAN, vlan->vid,
				    d0, d1, d2);
}

static int zx_dsa_port_vlan_del(struct dsa_switch *ds, int port,
				const struct switchdev_obj_port_vlan *vlan)
{
	struct zx_dsa_priv *priv = ds->priv;
	int p = zx_phys_port(port);
	u32 d0, d1, d2, shift = p * 2 + 1;
	int ret;

	ret = zx_sbrag_read_entry(priv, ZX_SBRAG_MEMID_VLAN, vlan->vid,
				  &d0, &d1, &d2);
	if (ret)
		return ret;

	d0 &= ~(0x3u << shift);		/* clear this port's membership */
	if (!(d0 & ~1u))		/* no members left -> clear valid bit */
		d0 = 0;

	return zx_sbrag_write_entry(priv, ZX_SBRAG_MEMID_VLAN, vlan->vid,
				    d0, d1, d2);
}

/* --- Port isolation / bridge membership --------------------------------- */

/* Write port P's allow-set (LOGICAL bit-space, set bit = may forward to that
 * logical port) into the isolation register, permuting logical->regport for
 * both the slot and the bits (RE'd transform, see zx_regport). RMW the low byte.
 */
static void zx_isolate_set(struct zx_dsa_priv *priv, int logical_port,
			   u32 allow_logical)
{
	u32 stored = 0, off, v;
	int b;

	for (b = 0; b < 8; b++)
		if (allow_logical & BIT(b))
			stored |= BIT(zx_regport[b]);

	off = ZX_ISOLATE_BASE + zx_regport[logical_port] * 4;
	v = readl(priv->pp_regs + off);
	writel((v & ~0xffu) | (stored & 0xff), priv->pp_regs + off);
}

/* Recompute every user port's isolation. DSA semantics: standalone ports talk
 * only to the CPU (isolated from each other); bridged ports may forward to
 * co-members of the same bridge + CPU. (Stock's default is allow-all; DSA wants
 * isolated-until-bridged.) NOT yet HW-verified.
 */
static void zx_recompute_isolation(struct zx_dsa_priv *priv)
{
	int p, q;

	for (p = 0; p < ZX_DSA_USER_PORTS; p++) {
		u32 allow = BIT(ZX_DSA_CPU_PORT);	/* always reach the CPU */

		if (priv->bridged & BIT(p)) {
			for (q = 0; q < ZX_DSA_USER_PORTS; q++)
				if ((priv->bridged & BIT(q)) &&
				    priv->br_num[q] == priv->br_num[p])
					allow |= BIT(q);
		}
		allow &= ~BIT(p);			/* never self */
		zx_isolate_set(priv, p, allow);
	}
}

static int zx_dsa_port_bridge_join(struct dsa_switch *ds, int port,
				   struct dsa_bridge bridge,
				   bool *tx_fwd_offload,
				   struct netlink_ext_ack *extack)
{
	struct zx_dsa_priv *priv = ds->priv;

	if (port >= ZX_DSA_USER_PORTS)
		return -EINVAL;

	priv->bridged |= BIT(port);
	priv->br_num[port] = bridge.num;
	zx_recompute_isolation(priv);
	return 0;
}

static void zx_dsa_port_bridge_leave(struct dsa_switch *ds, int port,
				     struct dsa_bridge bridge)
{
	struct zx_dsa_priv *priv = ds->priv;

	if (port >= ZX_DSA_USER_PORTS)
		return;

	priv->bridged &= ~BIT(port);
	zx_recompute_isolation(priv);
}

/* port_fast_age: flush DYNAMIC (learned) FDB entries on a port (STP topology
 * change). Best-effort SW sweep: iterate the unicast hash slots, zero entries
 * whose port matches and whose status nibble is present-but-not-static (0xF =
 * static, kept). The HW may also expose an age/flush command — TODO RE. NOT
 * HW-verified. Slot count follows the live table-sel width.
 */
static void zx_dsa_port_fast_age(struct dsa_switch *ds, int port)
{
	struct zx_dsa_priv *priv = ds->priv;
	int p = zx_phys_port(port);
	u32 nslots, slot;

	switch (readl(priv->pp_regs + ZX_SBRAG_TABLE_SEL) & 0x3) {
	case 1:
		nslots = 0x100;
		break;
	case 2:
		nslots = 0x200;
		break;
	default:
		nslots = 0x400;
		break;
	}

	for (slot = 0; slot < nslots; slot++) {
		u32 d0, d1, d2, status;

		if (zx_sbrag_read_entry(priv, ZX_SBRAG_MEMID_UC, slot,
					&d0, &d1, &d2))
			continue;
		status = (d1 >> 4) & 0xf;
		if (status && status != 0xf && (d2 & 0xff) == (u32)p)
			zx_sbrag_write_entry(priv, ZX_SBRAG_MEMID_UC, slot,
					     0, 0, 0);
	}
}

static const struct dsa_switch_ops zx_dsa_switch_ops = {
	.get_tag_protocol	= zx_dsa_get_tag_protocol,
	.setup			= zx_dsa_setup,
	.phylink_get_caps	= zx_dsa_phylink_get_caps,
	.port_enable		= zx_dsa_port_enable,
	.port_disable		= zx_dsa_port_disable,
	.port_stp_state_set	= zx_dsa_port_stp_state_set,
	.port_bridge_join	= zx_dsa_port_bridge_join,
	.port_bridge_leave	= zx_dsa_port_bridge_leave,
	.port_fdb_add		= zx_dsa_port_fdb_add,
	.port_fdb_del		= zx_dsa_port_fdb_del,
	.port_vlan_add		= zx_dsa_port_vlan_add,
	.port_vlan_del		= zx_dsa_port_vlan_del,
	.port_fast_age		= zx_dsa_port_fast_age,
	/* All per-port switch ops implemented. VLAN attr 2-bit encoding + the HW
	 * age/flush command are best-effort/TODO. ALL ops compile but are NOT
	 * HW-verified (driver doesn't probe yet) — see dsa_driver_plan.md.
	 */
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

	/* NPP greg window for per-port control. Non-exclusive ioremap because the
	 * conduit (zx-eth) also maps this space — sharing is intentional until the
	 * register access is unified (TODO: get the base from DT reg / conduit).
	 */
	priv->regs = devm_ioremap(&pdev->dev, ZX_NPP_PHYS, ZX_NPP_SIZE);
	if (!priv->regs)
		return -ENOMEM;

	priv->pp_regs = devm_ioremap(&pdev->dev, ZX_PP_PHYS, ZX_PP_SIZE);
	if (!priv->pp_regs)
		return -ENOMEM;

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
