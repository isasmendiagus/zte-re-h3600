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
#include <linux/inetdevice.h>
#include <net/dsa.h>
#include <net/flow_offload.h>
#include <net/neighbour.h>
#include <net/pkt_cls.h>
#include <net/route.h>
#include <uapi/linux/if_bridge.h>

/* 4 user LAN ports (0..3) + CPU port (5). Port 4 is the unused RGMII WAN MAC on
 * the H3600; sized to cover the CPU port index. Refined when the DT/port map is
 * wired (P0 cont.).
 */
#define ZX_DSA_NUM_PORTS	6
#define ZX_DSA_USER_PORTS	5	/* lan0..3 (MAC0-3 GePHY) + lan4 = WAN (MAC4, RGMII/ZX5201). lan4 left standalone (un-bridged) = the L3 WAN interface. */
#define ZX_DSA_CPU_PORT		5

/* Port isolation (SBRAG reg 0x39 @ PP 0x83c0 + regport*4, 1 byte/port).
 * Stored byte = allow-bitmap in REGPORT bit-space (set bit = may forward there).
 * Both the slot index and the bit positions are remapped logical->regport via
 * this table (RE'd from tm_port_isolate_set, decomp_all_tm.c:36297-36328).
 */
#define ZX_ISOLATE_BASE		0x3c0	/* PP window offset (phys 0x923883c0) */
static const u8 zx_regport[8] = { 1, 2, 3, 4, 5, 0, 6, 7 };

/* The WAN/RGMII regport (lan4 = MAC4 = modem uplink; zx_regport[4]=5). WAN-ingress
 * packets extract the CLA hash key with an extra bit at key position 32 (kb[4] bit0)
 * that GePHY LAN-ingress packets lack; the key builder must set it for entries whose
 * matching packets ingress the WAN or they land at the wrong hash bucket and MISS
 * (findings/wan_ingress_data_hitrate_2026-07-03). */
#define ZX_WAN_REGPORT		5

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

/* [Phase 6 / Stage 2] CLA classifier + PM packet-modify indirect windows, for
 * HW flow offload. The NPP/PP windows above DON'T reach these blocks, so we map
 * them separately. CLA @ 0x9238c000 (cmd/data + the HW hash engine), PM @
 * 0x921dc000 (next-hop MAC rewrite + flow_info). Offsets are relative to each
 * window base; encoding mirrors zx-eth-main.c (CMD = addr|ram_id<<22|rw<<27,
 * CMD-first then data descending — the verified commit order). The recipe words
 * come from the stock-FFE kotrace decode (findings/phase6_*GROUNDTRUTH*).
 */
#define ZX_CLA_PHYS		0x9238c000UL
#define ZX_CLA_SIZE		0x1000
#define ZX_PM_PHYS		0x921dc000UL
#define ZX_PM_SIZE		0x1000
#define ZX_CLA_CMD		0x014	/* phys 0x9238c014 */
#define ZX_CLA_DONE		0x018
#define ZX_CLA_DATA0		0x01c	/* slots 0..16 stride 4 */
#define ZX_CLA_HASH_TRIG	0x2c0	/* write 1 to latch+compute */
#define ZX_CLA_HASH_KEY0	0x2c4	/* 12 key words stride 4 */
#define ZX_CLA_HASH_OUT		0x2fc	/* 16-bit raw hash */
#define ZX_PM_CMD		0x014	/* phys 0x921dc014 */
#define ZX_PM_DONE		0x018
#define ZX_PM_DATA0		0x01c	/* data slots 0..3 stride 4 */
#define ZX_PM_DATA4		0x100	/* data slots 4..7 stride 4 */

/* Per-flow offload tracking: the tc cookie -> the ram2 hash bucket the flow's
 * entry was placed in. Needed so FLOW_CLS_DESTROY can invalidate exactly the
 * bucket that flow occupies (multi-flow per-slot placement, not fill520). */
#define ZX_MAX_OFFLOAD_FLOWS	32
struct zx_flow_ent {
	unsigned long	cookie;
	u16		raw;	/* raw HW hash (derives all 5 way buckets) */
	bool		used;
};

struct zx_dsa_priv {
	struct dsa_switch	*ds;
	struct device		*dev;
	void __iomem		*regs;	/* NPP window (greg) — see TODO above */
	void __iomem		*pp_regs; /* PP/SBRAG window (FDB, isolation) */
	void __iomem		*cla_regs; /* CLA classifier window (flow offload) */
	void __iomem		*pm_regs;  /* PM packet-modify window (next-hop) */
	bool			ffe_armed; /* extract infra written once (Stage 2) */
	u8			bridged;  /* bitmap of user ports in a bridge */
	int			br_num[ZX_DSA_NUM_PORTS]; /* dsa_bridge.num per port */
	struct zx_flow_ent	flows[ZX_MAX_OFFLOAD_FLOWS]; /* offload slot map */
	/* TODO P0/P1: conduit (sw netdev) ref for the datapath/tag */
};

/* PM indirect-RAM bridge to the conduit module's working path (see
 * include/linux/dsa/zte.h). The conduit registers these at its probe; the
 * binder routes its PM next-hop/flow_info writes through them because the
 * binder's own pm_regs ioremap does NOT commit to the live PM RAM. */
struct zx_pm_ops *zx_pm_ops;
EXPORT_SYMBOL_GPL(zx_pm_ops);

void zx_dsa_register_pm_ops(struct zx_pm_ops *ops)
{
	zx_pm_ops = ops;
	pr_info("[zx-dsa] PM ops %s by conduit\n", ops ? "registered" : "cleared");
}
EXPORT_SYMBOL_GPL(zx_dsa_register_pm_ops);

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
	/* [Iter AE 2026-06-04 prune] assisted_learning_on_cpu_port was tried (Iter AB)
	 * to push bridge-learned MACs into the HW FDB, but it was INERT here (the device
	 * bridge FDB stayed empty in the static-neigh test) and did NOT contribute to the
	 * fix — the wedge was the RX-ring bit14 bug (Iter AD). Reverted to keep the merge
	 * minimal; re-add later as a deliberate HW-FDB-offload feature if/when needed. */
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

#if IS_ENABLED(CONFIG_NET_CLS_FLOWER)
/* [Phase 6 / Stage 1] HW flow-offload plumbing — LOG ONLY (no chip write yet).
 * DSA routes a user-port netdev's tc-flower offload to these ops. We parse the
 * flow's 5-tuple + action and log it; Stage 2 translates it into a CLA
 * classifier entry (first a ram1 rule-TCAM rule, then the ram2-6 hash) via the
 * already-present zx_cla_write_entry()/clapeek. Design + the stock-FFE RE this
 * mirrors: tasks/00.10.02.re-stock-kmods/findings/phase6_offload_design.md.
 * Returning -EOPNOTSUPP here keeps every flow in the (working) SW datapath while
 * we validate that the callback fires with the right tuple.
 */

/* ---- Stage 2: CLA/PM indirect access (ported from zx-eth-main.c, base-relative) ---- */
static int zx_cla_wait(struct zx_dsa_priv *p)
{
	int t = 100;

	while (t-- && !(readl(p->cla_regs + ZX_CLA_DONE) & 1))
		udelay(5);
	return t < 0 ? -EBUSY : 0;
}

/* Write an n-word CLA RAM entry (CMD-first, data descending — verified commit order). */
static int zx_cla_wr(struct zx_dsa_priv *p, u8 ram_id, u32 addr, const u32 *d, int n)
{
	int i;

	if (zx_cla_wait(p))
		return -EBUSY;
	writel(addr | ((u32)ram_id << 22), p->cla_regs + ZX_CLA_CMD);
	for (i = n - 1; i >= 0; i--)
		writel(d[i], p->cla_regs + ZX_CLA_DATA0 + i * 4);
	return zx_cla_wait(p);
}

static int zx_pm_wait(struct zx_dsa_priv *p)
{
	int t = 100;

	/* udelay(50) — must match the proven conduit helper zx_pp_pm_wait_done.
	 * A 10x-shorter poll (the old udelay(5)) does not give the indirect-RAM
	 * commit enough settle time in the binder's back-to-back write loop, so
	 * consecutive PM writes raced and dropped (3/4 banks landed nothing, 1
	 * corrupted) — diagnosed 2026-06-28. */
	while (t-- && !(readl(p->pm_regs + ZX_PM_DONE) & 1))
		udelay(50);
	return t < 0 ? -EBUSY : 0;
}

/* Read back an 8-word PM RAM entry via the indirect iface (rw=1). */
static int zx_pm_rd(struct zx_dsa_priv *p, u8 ram_id, u32 addr, u32 d[8])
{
	int i;

	if (zx_pm_wait(p))
		return -EBUSY;
	writel(addr | ((u32)ram_id << 22) | (1u << 27), p->pm_regs + ZX_PM_CMD);
	if (zx_pm_wait(p))
		return -EBUSY;
	for (i = 0; i < 4; i++)
		d[i] = readl(p->pm_regs + ZX_PM_DATA0 + i * 4);
	for (i = 4; i < 8; i++)
		d[i] = readl(p->pm_regs + ZX_PM_DATA4 + (i - 4) * 4);
	return 0;
}

/* Write an 8-word PM RAM entry (CMD-first then data descending), then
 * read-back-verify and retry. The bare write was observed not to commit from
 * the DSA mapping (PM read back zero) while the conduit's identical sequence
 * persisted — so verify the indirect-RAM actually took and retry a few times.
 */
static int zx_pm_wr(struct zx_dsa_priv *p, u8 ram_id, u32 addr, const u32 d[8])
{
	u32 rb[8];
	int i, try;

	for (try = 0; try < 8; try++) {
		if (zx_pm_wait(p))
			return -EBUSY;
		writel(addr | ((u32)ram_id << 22), p->pm_regs + ZX_PM_CMD);
		for (i = 7; i >= 4; i--)
			writel(d[i], p->pm_regs + ZX_PM_DATA4 + (i - 4) * 4);
		for (i = 3; i >= 0; i--)
			writel(d[i], p->pm_regs + ZX_PM_DATA0 + i * 4);
		if (zx_pm_wait(p))
			return -EBUSY;
		/* Verify the entry committed (word0+word1 are enough to tell). */
		if (zx_pm_rd(p, ram_id, addr, rb))
			return -EBUSY;
		if (rb[0] == d[0] && rb[1] == d[1]) {
			if (try)
				pr_info("[zx-dsa] pm_wr ram%u[%#x] took after %d retries\n",
					ram_id, addr, try);
			return 0;
		}
		pr_warn("[zx-dsa] pm_wr ram%u[%#x] try%d: wrote %08x %08x readback %08x %08x\n",
			ram_id, addr, try, d[0], d[1], rb[0], rb[1]);
	}
	return -EIO;
}

/* Commit a PM entry through the conduit's PROVEN path if it has registered its
 * ops; otherwise fall back to the local (non-committing-on-this-HW) zx_pm_wr so
 * the binder still runs. The conduit's path writes the same indirect iface
 * (ram_id, addr, data[8]) but via its working e->base mapping. */
static int zx_pm_commit(struct zx_dsa_priv *p, u8 ram_id, u32 addr, const u32 d[8])
{
	if (zx_pm_ops && zx_pm_ops->write) {
		int rc = zx_pm_ops->write(ram_id, addr, d);
		u32 rb[8] = {0};

		/* Keep the readback-verify diagnostic on the conduit path too, so a
		 * regression is visible in dmesg (was: "readback 00000000"). */
		if (zx_pm_ops->read && zx_pm_ops->read(ram_id, addr, rb) == 0)
			pr_info("[zx-dsa] pm_commit(conduit) ram%u[%#x]: wrote %08x %08x readback %08x %08x\n",
				ram_id, addr, d[0], d[1], rb[0], rb[1]);
		else
			pr_info("[zx-dsa] pm_commit(conduit) ram%u[%#x]: wrote %08x %08x (read n/a) rc=%d\n",
				ram_id, addr, d[0], d[1], rc);
		return rc;
	}
	pr_warn("[zx-dsa] pm_commit: no conduit ops registered, falling back to local pm_regs (may not commit)\n");
	return zx_pm_wr(p, ram_id, addr, d);
}

/* Arm the FFE extract infra once: the v4 5-tuple extract rule + the ram0[9]
 * extract-index. ram0[9] word4 MUST be 0x00150001 (enable ONLY slot 0 -> rule
 * 0x90), matching zx_ffe_table.h zx_ffe_index[9] and the packer's extr_index low
 * byte 0x90 (cla[3]=0). Using 0x00150151 (the old value) would enable slot 8 ->
 * the HW selects the highest-enabled rule 0x98, whose ex_rule_id 0x98 != the
 * stored extr_index 0x90 -> LOOK_UP_MISS (code review C1 / c1_reconciliation
 * 2026-07-03: this write did not commit on the DSA mapping so it was masked, but
 * align it so it is correct-by-construction). The rule content lives at ram1[0x90]
 * (armed by the conduit's zx_cla_ffe_extract_init); the ram1[0x98] write below is
 * inert (slot 8 disabled) but harmless. Idempotent (guarded by ffe_armed). */
static void zx_ffe_arm(struct zx_dsa_priv *p)
{
	static const u32 rule90[17] = {
		0x22038608, 0x000058a1, 0, 0, 0xf00ff000, 0xffffffff, 0xffffffff,
		0x0fffffff, 0, 0, 0, 0, 0, 0, 0x00700000, 0x00092492, 0
	};
	static const u32 idx9[5] = {
		0x93929190, 0x97969594, 0x9b9a9998, 0x9f9e9d9c, 0x00150001
	};

	if (p->ffe_armed)
		return;
	zx_cla_wr(p, 1, 0x98, rule90, 17);
	zx_cla_wr(p, 0, 9, idx9, 5);
	p->ffe_armed = true;
	dev_info(p->dev, "[phase6] FFE extract armed (ram1[0x98] + ram0[9] fast-enable)\n");
}

/* Drive the CLA HW hash engine: load the 12-word (45-byte) flow key, pulse the
 * trigger, read the 16-bit raw hash. The chip computes the same 4-poly CRC it uses
 * on ingress, so we get the exact bucket the HW will probe. Load the key FIRST,
 * trigger LAST (the trigger is a control reg; triggering before the key -> 0).
 * Mirrors the conduit's zx_cla_hash_raw / the hashcalc debugfs. */
static u16 zx_cla_hash_raw(struct zx_dsa_priv *p, const u32 key[12])
{
	int i;

	for (i = 0; i < 12; i++)
		writel(key[i], p->cla_regs + ZX_CLA_HASH_KEY0 + i * 4);
	writel(1, p->cla_regs + ZX_CLA_HASH_TRIG);	/* trigger AFTER loading */
	return readl(p->cla_regs + ZX_CLA_HASH_OUT) & 0xffff;
}

/* Build the flow's 12-word HW hash key and return its raw 16-bit hash.
 *
 * The key is the flow's EXTRACTED-key form (NOT the raw stored windata):
 *   word0 = 0x48000000 = ex_rule_id 0x90 (v4-5tuple), inport/outport 0 — the HW
 *           zeroes inport in the extracted key for this rule (verified: the live
 *           gparsehashkey word0 = 0x48000000 regardless of ingress port).
 *   then the 7 fields {proto, srcHi, srcLo, dstHi, dstLo, sport, dport} are
 *   bit-packed at bit anchor 33 + 16*n in a little-endian byte stream (the "1-bit
 *   left shift" — each 16-bit field value is the RAW field, only the bit anchor is
 *   shifted; cla_gate2/cla_windata_packer findings).
 *
 * SELF-CHECK (offline-verified): for UDP 172.31.9.50:50010 -> 192.168.9.50:53 this
 * reproduces the live key 48000000 583e0022 81501265 86b41265 0000006b, which the
 * HW hashes to raw 0xf6d5 -> ram2 slot 0xd5 (matches on-device gparsehashkey). */
static u16 zx_cla_flow_hash(struct zx_dsa_priv *p, u8 ip_proto, __be32 saddr,
			    __be32 daddr, __be16 sport, __be16 dport, bool is_wan)
{
	u32 s = ntohl(saddr), d = ntohl(daddr);
	u16 fields[7] = {
		ip_proto, (s >> 16) & 0xffff, s & 0xffff,
		(d >> 16) & 0xffff, d & 0xffff, ntohs(sport), ntohs(dport),
	};
	u8 kb[48] = {0};
	u32 key[12];
	int n, i;

	kb[3] = 0x48;		/* word0 = 0x48000000 (ex_rule_id 0x90) */
	if (is_wan)
		kb[4] |= 1;	/* key pos32: WAN/RGMII-ingress extraction bit */
	for (n = 0; n < 7; n++) {
		u32 base = 33 + 16 * n;

		for (i = 0; i < 16; i++)
			if (fields[n] & (1u << i)) {
				u32 pos = base + i;

				kb[pos >> 3] |= 1u << (pos & 7);
			}
	}
	for (i = 0; i < 12; i++)
		key[i] = kb[4 * i] | (kb[4 * i + 1] << 8) |
			 (kb[4 * i + 2] << 16) | (kb[4 * i + 3] << 24);
	return zx_cla_hash_raw(p, key);
}

/* The CLA hash lookup is multi-way: a raw hash maps to one bucket in EACH bank
 * (ram2..ram6), and the HW probes across ways. So a per-flow entry must be placed
 * at the flow's bucket in ALL banks, not just ram2 (verified on-device: ram2[slot]
 * alone MISSES; adding the ram3/4/5/6 ways -> HW forwards). The per-bank slot masks
 * come from aclGetAvailableHashAddr (cla ram-layout): way0=ram2 raw&0xff,
 * way1=ram3 0x100+raw&0x7f, way2=ram4 0x180+raw&0x3f, way3=ram5 0x1c0+raw&0x3f,
 * ext=ram6 0x200+raw&7. These 5 buckets are distinct per distinct raw hash, so
 * different flows still occupy disjoint buckets and coexist. */
static void zx_cla_way_slots(u16 raw, u8 ram[5], u16 addr[5])
{
	ram[0] = 2; addr[0] = raw & 0xff;
	ram[1] = 3; addr[1] = 0x100 + (raw & 0x7f);
	ram[2] = 4; addr[2] = 0x180 + (raw & 0x3f);
	ram[3] = 5; addr[3] = 0x1c0 + (raw & 0x3f);
	ram[4] = 6; addr[4] = 0x200 + (raw & 0x7);
}

/* Per-flow CLA forward-entry field-packer. Builds the 15-word ram2 hash entry for
 * the {proto, src, dst, sport, dport} 5-tuple, reproducing the kotrace-decoded and
 * HW-validated byte layout EXACTLY (findings/trap_dmac_clear_HW_FORWARD_2026-06-28 +
 * phase6_cla_keybuilder_SPEC). Derived & verified against the two ground-truth
 * forwarding entries (STEP2 192.168.9.50 + 4b 10.44.66.250): words 0-4 constant
 * header, words 5-7 carry the IPs/ports interleaved as the 0x90-window extractor
 * stores them, word8 = 0x14 trailer.
 *
 *   word5 = s3<<24 | s0<<16 | s1<<8 | 0          (src octets [.,o2,o1,o4])
 *   word6 = d3<<24 | d0<<16 | d1<<8 | s2          (src o3 + dst [o2,o1,o4])
 *   word7 = dport_lo<<24 | sport_hi<<16 | sport_lo<<8 | d2
 *
 * Critical proven constants: byte0x05 = 0xc0 (e8_en/modify arm — REQUIRED), word3 =
 * 0x80000000 (valid), byte0x13 = real IP proto (UDP 0x11 / TCP 0x06), byte0x04 =
 * cmd_flow_id linking to the PM flow_info index. saddr/daddr are __be32 (network). */
static void zx_cla_pack_entry(u32 cla[15], u8 ip_proto, __be32 saddr, __be32 daddr,
			      __be16 sport, __be16 dport, u8 flow_id, bool is_wan)
{
	u8 s0 = (ntohl(saddr) >> 24) & 0xff, s1 = (ntohl(saddr) >> 16) & 0xff;
	u8 s2 = (ntohl(saddr) >>  8) & 0xff, s3 =  ntohl(saddr)        & 0xff;
	u8 d0 = (ntohl(daddr) >> 24) & 0xff, d1 = (ntohl(daddr) >> 16) & 0xff;
	u8 d2 = (ntohl(daddr) >>  8) & 0xff, d3 =  ntohl(daddr)        & 0xff;
	u16 sp = ntohs(sport), dp = ntohs(dport);

	/* Word 0-4 header: const template with byte0x04=flow_id, byte0x05=0xc0
	 * (e8_en arm), byte0x13=ip_proto. word3=0x80000000 (valid). */
	cla[0] = 0x03005044;
	/* word1 bytes: [0x04]=cmd_flow_id [0x05]=0xc0(e8_en) [0x06]=0x11 [0x07]=0xfa */
	cla[1] = (0xfau << 24) | (0x11u << 16) | (0xc0u << 8) | (flow_id & 0xff);
	cla[2] = 0x00000608;
	/* word3 is NOT a valid bit — it is the high part of extr_index
	 * (extr_index = byte0x10<<4 | byte0xf>>4, cla_set_hash_table tm.c:3444).
	 * byte0x10=0x49 (word4) + byte0xf=0x00 (this word) => extr_index low byte 0x90,
	 * which MUST equal the ex_rule_id the HW classifies the flow under (rule 0x90).
	 * The stock-captured 0x80000000 made byte0xf=0x80 => extr_index 0x98 != 0x90 =>
	 * LOOK_UP_MISS on every packet (verified on-device 2026-07-02). Must be 0. */
	cla[3] = 0;
	/* byte0x10 bit5 = `direct` (0x49->0x69) for the WAN/download-ingress entry — see
	 * zx-eth-main.c zx_ft_pack_cla: necessary+sufficient to flip WAN-ingress
	 * trap->forward (bisected on-device 2026-07-03). LAN-ingress forwards without it,
	 * so gate on is_wan. extr_index stays 0x90 (word3=0). */
	cla[4] = ((u32)ip_proto << 24) | (is_wan ? 0x00000069 : 0x00000049);
	/* Word 5-7: the verified IP/port interleave. */
	cla[5] = ((u32)s3 << 24) | ((u32)s0 << 16) | ((u32)s1 << 8);
	cla[6] = ((u32)d3 << 24) | ((u32)d0 << 16) | ((u32)d1 << 8) | s2;
	cla[7] = ((u32)(dp & 0xff) << 24) | ((u32)(sp >> 8) << 16) |
		 ((u32)(sp & 0xff) << 8) | d2;
	/* byte0x20 = dport HIGH byte (NOT a constant 0x14). The CLA hash COMPARE reads
	 * windata6 = the plain LE16 at entry bytes 0x1f/0x20 (cla_set_hash_table tm.c:3433)
	 * and matches it against the live packet's L4-window @IP-offset 22 = dport (BE,
	 * winmask 0xffff). dport_lo lands at 0x1f (above); dport_hi MUST be at 0x20.
	 * The old hardcoded 0x14 only coincidentally matched the capture flow whose
	 * dport=5201=0x1451 (hi byte 0x14); for any other dport it corrupts windata6 and
	 * the bucket key-compare MISSES (verified on-device: dport 53 → stored windata6
	 * 0x1435 vs HW-extracted 0x0035). */
	cla[8] = (u32)(dp >> 8) & 0xff;
	cla[9] = cla[10] = cla[11] = cla[12] = cla[13] = cla[14] = 0;
}

/* Build + write the per-flow HW L3-forward recipe (the full PROVEN recipe):
 *   - CLA ram2 forward entry for the 5-tuple (zx_cla_pack_entry), brute-filled to
 *     all 520 hash buckets to sidestep slot prediction (the validated fill520 path).
 *   - PM ram1[N] next-hop: dst IP + the resolved next-hop MAC (DMAC rewrite source).
 *   - PM ram0[N] flow_info: fi[0]=(0x0de8<<16)|next_hop_idx (rewrite-enable bits),
 *     fi[1]=0x0014035c with sub_ram_index encoded.
 *   - PM ram6[sub] sub_ram: cmd_addr -> the ram3 microcode index.
 *   - PM ram3[cmd] cmd_ram: minimal valid last_cmd=1 rewrite (DMAC-set/TTL--).
 * idx is the shared flow_info / next-hop slot (matches cmd_flow_id in the CLA entry). */
#define ZX_FLOW_IDX	5	/* PM flow_info / next-hop slot (proven test used 5) */
#define ZX_SUBRAM_IDX	5	/* PM ram6 sub_ram slot */
#define ZX_CMD_IDX	5	/* PM ram3 cmd_ram (rewrite microcode) slot */
static int zx_install_l3_recipe(struct zx_dsa_priv *p, u8 ip_proto, __be32 saddr,
				__be32 daddr, __be16 sport, __be16 dport,
				const u8 nh_mac[ETH_ALEN], u8 in_regport, u8 eg_regport)
{
	u32 cla[15];
	u32 nh[8] = {0}, fi[8] = {0}, sub[8] = {0}, cmd[8] = {0};
	u8 ram[5];
	u16 addr[5];
	u16 raw;
	int w, rc = 0;

	/* PM next-hop ram1[idx]: dst IP + the 6-byte rewrite MAC (stock split layout). */
	nh[0] = ntohl(daddr);
	nh[1] = ((u32)nh_mac[2] << 24) | ((u32)nh_mac[3] << 16) |
		((u32)nh_mac[4] << 8) | nh_mac[5];
	nh[2] = ((u32)nh_mac[0] << 8) | nh_mac[1];
	zx_pm_commit(p, 1, ZX_FLOW_IDX, nh);

	/* PM flow_info ram0[idx]: rewrite-enable bits (0x0de8) | next_hop_idx in word0;
	 * word1 carries the egress queue + sub_ram_index (proven 0x0014035c). */
	fi[0] = (0x0de8u << 16) | ZX_FLOW_IDX;
	fi[1] = 0x0014035c;
	zx_pm_commit(p, 0, ZX_FLOW_IDX, fi);

	/* PM ram6 sub_ram: cmd_addr -> the ram3 microcode index (links flow_info to the
	 * DMAC-set/TTL-- rewrite). Minimal: word0 low = cmd_addr (the ram3 slot). */
	sub[0] = ZX_CMD_IDX;
	zx_pm_commit(p, 6, ZX_SUBRAM_IDX, sub);

	/* PM ram3 cmd_ram: the rewrite microcode. Minimal valid last_cmd=1 entry
	 * (0x00800000) = a no-op terminate that lets the forward proceed (the proven
	 * minimal forward; a full DMAC-set/TTL-- microcode is the productization). */
	cmd[0] = 0x00800000;
	zx_pm_commit(p, 3, ZX_CMD_IDX, cmd);

	/* CLA forward entry — packed per-flow, written at the flow's own hash bucket
	 * in ALL 5 banks (per-slot placement, replacing the fill520 all-buckets hack
	 * that let a 2nd flow clobber the 1st). The HW hash engine gives the exact
	 * bucket the chip probes on ingress; the multi-way lookup requires the entry in
	 * every bank at the flow's hash (ram2 alone MISSES — verified on-device). The
	 * 5 buckets are distinct per distinct 5-tuple, so flows coexist.
	 * cmd_flow_id (byte0x04) = 0: the HW-validated forwarding entries used 0 here. */
	zx_cla_pack_entry(cla, ip_proto, saddr, daddr, sport, dport, 0,
			  in_regport == ZX_WAN_REGPORT);
	/* Ingress-aware hash: packets matching this entry ingress in_regport; a
	 * WAN/RGMII ingress sets key pos32. (Local tc-flower tests inject on a GePHY
	 * LAN port -> in_regport != WAN -> pos32=0, unchanged.) */
	raw = zx_cla_flow_hash(p, ip_proto, saddr, daddr, sport, dport,
			       in_regport == ZX_WAN_REGPORT);
	zx_cla_way_slots(raw, ram, addr);
	for (w = 0; w < 5; w++) {
		int r = zx_cla_wr(p, ram[w], addr[w], cla, 15);

		if (r)
			rc = r;
	}

	dev_info(p->dev,
		 "[phase6] recipe: proto=%u %pI4:%u->%pI4:%u in_rp=%u eg_rp=%u nh=%pM -> raw=0x%04x buckets ram2[0x%02x]/3[0x%03x]/4[0x%03x]/5[0x%03x]/6[0x%03x] rc=%d\n",
		 ip_proto, &saddr, ntohs(sport), &daddr, ntohs(dport),
		 in_regport, eg_regport, nh_mac, raw,
		 addr[0], addr[1], addr[2], addr[3], addr[4], rc);
	return rc ? rc : raw;
}

/* Resolve the next-hop MAC for an L3-routed flow: route lookup on the dst IP, then
 * a neighbour lookup on the resolved gateway (or the dst itself when on-link). Falls
 * back to the caller's pre-seeded MAC if resolution fails (e.g. neigh not yet
 * populated). Mirrors how stock's FFE install pulls the resolved neighbour. */
static bool zx_resolve_nh_mac(struct net_device *odev, __be32 daddr,
			      u8 nh_mac[ETH_ALEN])
{
	struct neighbour *n;
	struct rtable *rt;
	__be32 nh_ip = daddr;
	bool ok = false;

	if (!odev)
		return false;
	rt = ip_route_output(dev_net(odev), daddr, 0, 0, odev->ifindex);
	if (!IS_ERR(rt)) {
		if (rt->rt_gw_family == AF_INET && rt->rt_gw4)
			nh_ip = rt->rt_gw4;
		ip_rt_put(rt);
	}
	n = neigh_lookup(&arp_tbl, &nh_ip, odev);
	if (n) {
		if (n->nud_state & NUD_VALID) {
			read_lock_bh(&n->lock);
			ether_addr_copy(nh_mac, n->ha);
			read_unlock_bh(&n->lock);
			ok = !is_zero_ether_addr(nh_mac);
		}
		neigh_release(n);
	}
	return ok;
}

/* Reserve a tracking slot for a flow (identified by its tc cookie) at HW hash
 * raw, recording {cookie, raw} so FLOW_CLS_DESTROY can invalidate exactly this
 * flow's 5 way buckets. Called BEFORE the CLA entry is written, so a DECLINED
 * offload leaves both flows[] and the CLA banks untouched (flow stays in SW):
 *   -EOPNOTSUPP  another tracked flow (different cookie) already owns raw's CLA
 *                bucket. All 5 ways derive from the low byte, and way0 = ram2
 *                (raw & 0xff) is the 256-slot primary that the HW resolves on;
 *                two flows sharing it clobber each other and delete-either kills
 *                both, so a same-way0 collision is rejected (kept in SW). (Higher
 *                ways can alias between distinct raw&0xff without harm — the HW
 *                hits the distinct way0 entry; verified on-device with 11 flows.)
 *   -ENOSPC      the tracking table is full and this cookie is not already known.
 * Re-uses the slot on REPLACE (same cookie), still checking collisions vs others.
 * Returns 0 and records the slot on success. */
static int zx_flow_reserve(struct zx_dsa_priv *p, unsigned long cookie, u16 raw)
{
	int i, self = -1, free = -1;

	for (i = 0; i < ZX_MAX_OFFLOAD_FLOWS; i++) {
		if (!p->flows[i].used) {
			if (free < 0)
				free = i;
			continue;
		}
		if (p->flows[i].cookie == cookie) {
			self = i;
			continue;
		}
		if ((p->flows[i].raw & 0xff) == (raw & 0xff))
			return -EOPNOTSUPP;	/* CLA way0 bucket collision */
	}
	if (self >= 0) {			/* REPLACE existing cookie */
		p->flows[self].raw = raw;
		return 0;
	}
	if (free < 0)
		return -ENOSPC;			/* tracking table full */
	p->flows[free].cookie = cookie;
	p->flows[free].raw = raw;
	p->flows[free].used = true;
	return 0;
}

/* Undo a reservation (no CLA write occurred / a later HW write failed): free the
 * slot so flows[] does not leak a phantom entry. */
static void zx_flow_release(struct zx_dsa_priv *p, unsigned long cookie)
{
	int i;

	for (i = 0; i < ZX_MAX_OFFLOAD_FLOWS; i++)
		if (p->flows[i].used && p->flows[i].cookie == cookie) {
			p->flows[i].used = false;
			return;
		}
}

/* Invalidate the buckets a tracked flow occupies: zero the 15-word entry in all 5
 * way banks so valid_en (byte0x10 bit6) clears and the bucket key-compare misses
 * -> the flow TRAPS again. Returns 0 if a tracked flow was found+cleared, -ENOENT. */
static int zx_flow_untrack(struct zx_dsa_priv *p, unsigned long cookie)
{
	u32 zero[15] = {0};
	u8 ram[5];
	u16 addr[5];
	int i, w, rc = 0;

	for (i = 0; i < ZX_MAX_OFFLOAD_FLOWS; i++) {
		if (p->flows[i].used && p->flows[i].cookie == cookie) {
			zx_cla_way_slots(p->flows[i].raw, ram, addr);
			for (w = 0; w < 5; w++) {
				int r = zx_cla_wr(p, ram[w], addr[w], zero, 15);

				if (r)
					rc = r;
			}
			dev_info(p->dev,
				 "[phase6] flow del cookie=%lx -> cleared raw=0x%04x (5 ways) rc=%d\n",
				 cookie, p->flows[i].raw, rc);
			p->flows[i].used = false;
			return rc;
		}
	}
	return -ENOENT;
}

static int zx_dsa_cls_flower_add(struct dsa_switch *ds, int port,
				 struct flow_cls_offload *cls, bool ingress)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(cls);
	struct zx_dsa_priv *priv = ds->priv;
	struct flow_action_entry *act;
	struct net_device *odev = NULL;
	__be32 saddr = 0, daddr = 0;
	__be16 sport = 0, dport = 0;
	u8 ip_proto = 0;
	u16 raw;
	int i, rc, in_ifidx = 0;
	/* Resolved next-hop MAC. Default = the validated test-flow DST until the
	 * MANGLE/neigh resolution below fills it (Stage 3 generalizes). */
	u8 nh_mac[ETH_ALEN] = { 0x6c, 0x70, 0xcb, 0xb6, 0x81, 0x69 };
	u8 eg_regport = 2;	/* fallback = lan1 regport */
	bool mangle_dmac = false;

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_META)) {
		struct flow_match_meta m;

		flow_rule_match_meta(rule, &m);
		in_ifidx = m.key->ingress_ifindex;
	}
	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) {
		struct flow_match_basic m;

		flow_rule_match_basic(rule, &m);
		ip_proto = m.key->ip_proto;
	}
	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV4_ADDRS)) {
		struct flow_match_ipv4_addrs m;

		flow_rule_match_ipv4_addrs(rule, &m);
		saddr = m.key->src;
		daddr = m.key->dst;
	}
	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) {
		struct flow_match_ports m;

		flow_rule_match_ports(rule, &m);
		sport = m.key->src;
		dport = m.key->dst;
	}

	dev_info(ds->dev,
		 "[phase6] cls_flower_add port%d ing=%d cookie=%lx proto=%u %pI4:%u -> %pI4:%u in_ifidx=%d\n",
		 port, ingress, cls->cookie, ip_proto,
		 &saddr, ntohs(sport), &daddr, ntohs(dport), in_ifidx);

	flow_action_for_each(i, act, &rule->action) {
		switch (act->id) {
		case FLOW_ACTION_REDIRECT:
		case FLOW_ACTION_REDIRECT_INGRESS:
			odev = act->dev;
			dev_info(ds->dev, "[phase6]   act[%d]=REDIRECT dev=%s\n",
				 i, odev ? netdev_name(odev) : "?");
			break;
		case FLOW_ACTION_MANGLE:
			/* NAT/eth-dst rewrite: capture the new dst-MAC if present.
			 * Ethernet header mangle at offset 0 = dst MAC bytes [0..3],
			 * offset 4 = dst[4..5] | src[0..1]. */
			if (act->mangle.htype == FLOW_ACT_MANGLE_HDR_TYPE_ETH) {
				u32 v = act->mangle.val;

				if (act->mangle.offset == 0) {
					nh_mac[0] = v & 0xff;
					nh_mac[1] = (v >> 8) & 0xff;
					nh_mac[2] = (v >> 16) & 0xff;
					nh_mac[3] = (v >> 24) & 0xff;
				} else if (act->mangle.offset == 4) {
					nh_mac[4] = v & 0xff;
					nh_mac[5] = (v >> 8) & 0xff;
				}
				mangle_dmac = true;
			}
			dev_info(ds->dev,
				 "[phase6]   act[%d]=MANGLE(NAT) htype=%u off=%u val=%08x\n",
				 i, act->mangle.htype, act->mangle.offset,
				 act->mangle.val);
			break;
		default:
			dev_info(ds->dev, "[phase6]   act[%d]=id %u\n", i, act->id);
			break;
		}
	}

	/* [Phase 6 / Stage 2] Install the HW L3-forward recipe + accept the offload.
	 * Only flows with an egress redirect target are modelled; everything else
	 * stays in the (working) SW datapath. */
	if (!odev)
		return -EOPNOTSUPP;
	for (i = 0; i < ZX_DSA_USER_PORTS; i++) {
		struct dsa_port *dp = dsa_to_port(ds, i);

		if (dp && dp->slave == odev) {
			eg_regport = zx_regport[i & 7];
			break;
		}
	}

	/* Resolve the real next-hop MAC: a MANGLE eth-dst action (NAT path) wins;
	 * otherwise do a route+neigh lookup on the egress dev. Keep the seeded
	 * fallback if neither resolves (neigh may not be populated yet). */
	if (!mangle_dmac)
		zx_resolve_nh_mac(odev, daddr, nh_mac);

	/* Compute the flow's HW hash up-front and RESERVE a tracking slot BEFORE
	 * touching the CLA. A declined offload (bucket collision or full table)
	 * must leave both flows[] and the CLA banks untouched and stay in the
	 * (working) SW datapath — never clobber an existing entry, never leak. */
	raw = zx_cla_flow_hash(priv, ip_proto, saddr, daddr, sport, dport,
			       zx_regport[port & 7] == ZX_WAN_REGPORT);
	rc = zx_flow_reserve(priv, cls->cookie, raw);
	if (rc == -EOPNOTSUPP) {
		dev_info(ds->dev,
			 "[phase6] offload declined: CLA bucket collision cookie=%lx raw 0x%04x (way0 0x%02x already owned) -> stays in SW\n",
			 cls->cookie, raw, raw & 0xff);
		return rc;
	}
	if (rc < 0) {
		dev_info(ds->dev,
			 "[phase6] offload declined: flow table full (max %d) cookie=%lx raw 0x%04x -> stays in SW\n",
			 ZX_MAX_OFFLOAD_FLOWS, cls->cookie, raw);
		return -EOPNOTSUPP;
	}

	zx_ffe_arm(priv);
	rc = zx_install_l3_recipe(priv, ip_proto, saddr, daddr, sport, dport,
				  nh_mac, zx_regport[port & 7], eg_regport);
	if (rc < 0) {
		zx_flow_release(priv, cls->cookie);	/* undo reservation on HW error */
		return rc;
	}

	return 0;
}

static int zx_dsa_cls_flower_del(struct dsa_switch *ds, int port,
				 struct flow_cls_offload *cls, bool ingress)
{
	struct zx_dsa_priv *priv = ds->priv;
	int rc;

	dev_info(ds->dev, "[phase6] cls_flower_del port%d cookie=%lx\n",
		 port, cls->cookie);
	rc = zx_flow_untrack(priv, cls->cookie);
	/* Not a tracked offload flow (e.g. one we declined) -> nothing to undo. */
	return rc == -ENOENT ? 0 : rc;
}

/* Report keepalive stats for a resident tracked flow so the flowtable/tc core
 * refreshes lastused and does not age out a HW entry whose packets bypass the CPU
 * (see zx_ft_flower_stats in zx-eth-main.c for the full rationale). This DSA
 * tc-flower path is the manual test path (filters persist until userspace deletes
 * them, so it is not GC-churned like the FT path) -- the keepalive is kept for
 * consistency and to make `tc -s filter` show the flow as used. */
static int zx_dsa_cls_flower_stats(struct dsa_switch *ds, int port,
				   struct flow_cls_offload *cls, bool ingress)
{
	struct zx_dsa_priv *priv = ds->priv;
	int i;

	for (i = 0; i < ZX_MAX_OFFLOAD_FLOWS; i++)
		if (priv->flows[i].used && priv->flows[i].cookie == cls->cookie) {
			flow_stats_update(&cls->stats, 0, 0, 0, jiffies,
					  FLOW_ACTION_HW_STATS_DELAYED);
			return 0;
		}
	return -EOPNOTSUPP;
}
#endif /* CONFIG_NET_CLS_FLOWER */

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
#if IS_ENABLED(CONFIG_NET_CLS_FLOWER)
	.cls_flower_add		= zx_dsa_cls_flower_add,
	.cls_flower_del		= zx_dsa_cls_flower_del,
	.cls_flower_stats	= zx_dsa_cls_flower_stats,
#endif
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

	/* [Phase 6 / Stage 2] CLA + PM windows for HW flow offload. Shared with the
	 * conduit (zx-eth) — non-exclusive ioremap, same as regs/pp_regs above. */
	priv->cla_regs = devm_ioremap(&pdev->dev, ZX_CLA_PHYS, ZX_CLA_SIZE);
	if (!priv->cla_regs)
		return -ENOMEM;

	priv->pm_regs = devm_ioremap(&pdev->dev, ZX_PM_PHYS, ZX_PM_SIZE);
	if (!priv->pm_regs)
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
