// SPDX-License-Identifier: GPL-2.0
/*
 * ZTE ZX279128S — integrated Ethernet driver (NPP / IDM / 4× MAC).
 *
 * Reverse-engineered from stock plat-zxylzb_9128S.ko (vendor kernel 4.1).
 *
 * Memory map (single ioremap from npp_base = 0x921c0000, 2 MiB):
 *   +0x000000  NPP control regs + sub-block init
 *   +0x008000  IDM (descriptor rings, IRQ status, RX/TX kick)
 *   +0x040000  MAC0 — GMII → GePHY → RJ45 #1
 *   +0x080000  MAC1 — MII  → GePHY → RJ45 #2
 *   +0x0C0000  MAC2 — MII  → GePHY → RJ45 #3
 *   +0x100000  MAC3 — MII  → GePHY → RJ45 #4
 *   +0x140000  MAC4 — RGMII → external Realtek WAN PHY (not used by minimal driver)
 *   +0x180000  TM  — Traffic Manager (skipped for now)
 *   +0x1C0000  PP  — Packet Processor (only one bit poked for CPU↔LAN forwarding)
 *
 * Strategy: U-Boot already runs smac_init + GePHY autoneg before booting
 * Linux (we see "mac 0 phy status changed: 1000M full-duplex" in the log).
 * The driver re-runs MAC config to take ownership of the regs, but does NOT
 * touch MDIO (we have no decompiled symbol for the MDIO controller yet —
 * relying on U-Boot's left-over PHY state).
 *
 * idm0 / idm1 are the two CPU-facing "aggregate" netdevs. The on-chip switch
 * forwards between LAN ports in hardware; the driver only deals with packets
 * destined for / originating from the CPU.
 */

#include <linux/dma-mapping.h>
#include <linux/etherdevice.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/skbuff.h>
#include <linux/spinlock.h>

#include <linux/firmware.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>

#include "zx-fpga-reg-tables.h"
#include "zx-pp-pro-actions.h"

/* Runtime-loaded replay snapshots (was: #include "zx279128-eth-{stock,cla,pm}-regs.h").
 * Bin files live in initramfs at /lib/firmware/zx-replay/{stock,cla,pm}.bin.
 * Each file: [u32 magic 'ZXGR'][u32 count][records...]
 */
#define ZX_REPLAY_MAGIC 0x5A584752u

struct zx_replay_stock { s32 off; u32 val; } __packed;
struct zx_replay_cla   { u32 ram_id; u32 ram_addr; u32 data[17]; } __packed;
struct zx_replay_pm    { u32 ram_id; u32 ram_addr; u32 data[8];  } __packed;

/* These bounds match what's actually in the snapshots; used by zx_cla_apply_replay
 * to generate the ram=7 CPU-queue entries (constant payload, address range only). */
#define ZX_CLA_RAM7_FIRST  0
#define ZX_CLA_RAM7_LAST   1023

#define DRV_NAME "zx279128-eth"

/* ---------- NPP / IDM register map (npp_base) ---------- */
#define NPP_REG_MASK_GLOBAL	0x0004
#define NPP_REG_IRQ_ENABLE	0x0008
#define NPP_REG_IRQ_MASK	0x000C
#define NPP_REG_CONTROL		0x0040
#define NPP_REG_RESET		0x0048
#define NPP_REG_SIPC_INIT	0xC000
#define NPP_REG_SMCT_INIT_0	0x10000
#define NPP_REG_SMCT_INIT_1	0x10010
#define NPP_REG_INIT_VAL	0x10008
#define NPP_REG_SPA_INIT	0x141C0
#define NPP_REG_UOPC_INIT	0x18000

/* IDM regs (still within npp_base, offset +0x8000) */
#define IDM_REG_CONTROL		0x8000
/* Stock writes idm_desc_addr (offset 0 = RX descs) to npp+0x8008 and
 * idm_desc_addr+0x4000 (TX descs) to npp+0x8004. Our defines were SWAPPED:
 * fixed 2026-05-20 after RE pon_npp_idm_init. */
#define IDM_REG_TX_DESC_BASE	0x8004
#define IDM_REG_RX_DESC_BASE	0x8008
#define IDM_REG_RX_ENABLE	0x800C
#define IDM_REG_REG_10		0x8010
#define IDM_REG_REG_18		0x8018
#define IDM_REG_TIMEOUT		0x801C
#define IDM_REG_IRQ_STATUS	0x8020
#define IDM_REG_IRQ_MASK	0x8024
#define IDM_REG_TX_KICK		0x8040
#define IDM_REG_TX_STATUS	0x8044
#define IDM_REG_RX_KICK		0x8048
#define IDM_REG_RX_QLEN		0x804C
#define IDM_REG_REG_C0		0x80C0

/* PP (Packet Processor — routes SW frames to CPU via NPP/IDM rings) */
#define PP_OFF			0x1C0000
#define PP_REG_CTRL_0		0x0000
#define PP_REG_CTRL_28		0x0028
#define PP_REG_CPU_FWD		0x002C
/* Bridge / classifier sub-block at PP_OFF + 0x8000 / +0xC000 */
#define PP_BRG_BASE		0x8000
#define PP_CLA_BASE		0xC000

/* TOP_CRM clock control (separate ioremap from main NPP block) */
#define ZX_TOPCRM_BASE		0x94000000
#define TOPCRM_REG_PON_CLK	0x0C	/* zx_pon_clk_reset_init final write: |= 0x1E0 */
#define TOPCRM_PON_CLK_BITS	0x1E0	/* bits 5-8 — PON subsystem clocks */

/* CPU forwarding bit: stock does pp[0x2c] |= 1 << (lan_up_port + 0x19).
 * lan_up_port = 0 for LAN-only mode (g_pon_work_mode==0x10) → bit 25. */
#define PP_CPU_FWD_BIT		BIT(25)

/* ===== TM (Traffic Manager) — CPU↔switch path (the REAL one for ethernet) ===== */
#define TM_OFF			0x180000	/* npp_base + 0x180000 = 0x92340000 */
#define TM_REG_BPPE_BASE	0x00E8	/* BPPE physical addr in DDR */
#define TM_REG_JUMBO_BPPE_BASE	0x00EC
#define TM_REG_BP_BUFFER_BASE	0x00F4
#define TM_REG_BP_JUMBO_BASE	0x00F8
#define TM_REG_BP_SIZE		0x00FC	/* low 16 = BP_SIZE, high 16 = JUMBO_BP_SIZE */
#define TM_REG_IRQ_MASK		0x0104
#define TM_REG_BMU_INIT		0x8000
#define TM_REG_BMU_CTRL		0x8004
#define TM_REG_BMU_CTRL2	0x8008
#define TM_REG_BMU_ALLOC_RESULT	0x800C
#define TM_REG_BMU_ALLOC_CTRL	0x8014
#define TM_REG_BMU_POOL_SIZE	0x8048	/* high 16 = BPPE_POOL_SIZE */
#define TM_REG_BMU_JUMBO_POOL	0x804C
#define TM_REG_BMU_BUCKETS_M1	0x8058	/* (POOL_SIZE>>5)-1 */
#define TM_REG_BMU_JUMBO_BUCK	0x805C
#define TM_REG_DMA_CTRL		0x10000
#define TM_REG_DMA_REG20	0x10020
#define TM_REG_DMA_REG24	0x10024
#define TM_REG_DMA_REG28	0x10028
#define TM_REG_DMA_REG2C	0x1002C
#define TM_REG_DMA_TIMEOUT	0x10030
#define TM_REG_DMA_REG34	0x10034
#define TM_REG_DMA_REG3C	0x1003C
#define TM_REG_DMA_TX_UP_BASE	0x10050
#define TM_REG_DMA_DESC_CNT_UP	0x10058
#define TM_REG_DMA_TX_DN_BASE	0x10060
#define TM_REG_DMA_DESC_CNT_DN	0x10068
#define TM_REG_DMA_REG388	0x10388

#define TM_RX_QCNT_BASE		(0x4040 * 4)	/* tm[0x10100+q*4] per-queue RX count */
/* TM IRQ_MASK: 1 = MASKED. Stock 0xFFFFFFFC = bits 0,1 (PON RX/TX) unmasked.
 * Reverted to stock bits — TM IRQ flood at 61k/s when we unmasked other bits
 * meant they're spurious/keep-asserted state bits, not edge-triggered events. */
#define TM_IRQ_ARM_BITS		0x03		/* bits 0,1 only */

/* Stock prints `BPPE_POOL_SIZE=2000` in `pon init` = 0x2000 = 8192. Match
 * stock to avoid buffer exhaustion under sustained traffic (2026-05-22 boot
 * UART capture, tasks/mainline_eth/captures/boot_init_2026-05-22.log line 451). */
#define TM_BPPE_POOL_SIZE	1024	/* was 8192 — 18MB bp_pool failed dma_alloc_coherent
					 * on default CMA. 1024 entries → ~2.3 MB,
					 * fits comfortably. Reduce buffer head-room
					 * but plenty for initial RX validation. */
#define TM_BP_SIZE		2304	/* stock has 0x900=2304 (NOT 2048!) in TM[0xFC] low16 */
#define TM_TX_RING_SIZE		1024
#define TM_TX_DESC_SIZE		16
#define TM_JUMBO_BP_SIZE	10240	/* stock high16 of TM[0xFC] = 0x2800=10240 */
#define TM_NUM_RX_QUEUES	8
#define TM_RX_DESC_PER_Q	1024	/* Stock uses idx % 0x400 (1024); was 256 — explains why we saw zeros */
#define TM_DESC_SIZE		16

/* BRG (Bridge) sub-block of PP — indirect RAM access registers + FDB hash. */
#define PP_BRG_RAM_CMD		0x8014	/* bucket | (slot<<22) | (0x08000000=read) */
#define PP_BRG_RAM_READY	0x8018	/* poll bit 0 == 1 before issuing */
#define PP_BRG_RAM_D0		0x801C	/* data word 0 */
#define PP_BRG_RAM_D1		0x8020	/* data word 1 */
#define PP_BRG_RAM_D2		0x8024	/* data word 2 */
#define PP_BRG_RAM_TABLE_SIZE	0x8184	/* low 2 bits index a mac_table_size[] of u16 */
#define PP_BRG_ISOLATE(p)	(0x83C0 + (p) * 4)	/* per-port isolation mask */
#define PP_BRG_VLAN_BASE	0x8000	/* TODO: VLAN tables indirect addressed too */
#define BRG_RAM_READ		0x08000000

/* Port number assignments (inferred from stock pon_pp_brg_init):
 *  ports 0..3 = LAN MACs 0..3
 *  port  4    = MAC4 (RGMII WAN)
 *  port  5    = ?  (PON?)
 *  ports 6,7  = CPU/internal — stock isolates both with mask 0xdf
 * Use port 6 as our CPU port for idm0/idm1 FDB entries. */
#define ZX_CPU_PORT		5	/* Stock active CLA rule has inport=5 → CPU port is 5 (mined from stock /sys debug). */

/* MAC[i] window — base = npp_base + (i+1) * 0x40000 */
#define MAC_STRIDE		0x40000
#define MAC_REG_CONTROL		0x0000
#define MAC_REG_IRQ_MASK	0x0004
#define MAC_REG_ENABLE		0x0008
#define MAC_REG_PHY_CB		0x00E0
#define MAC_REG_D00		0x0D00
#define MAC_REG_D30		0x0D30

#define ZX_NUM_MACS		4	/* skip MAC4 (RGMII WAN) — not on H3600 LAN-only */

/* IRQ bits in IDM_REG_IRQ_STATUS / IRQ_MASK.
 * Per stock idm_net_int / idm_net_poll, masking semantics is unclear:
 *   - idm_net_init writes mask = idm_int_mask (zero-init global → 0)
 *   - idm_net_int does `mask |= 0x14` (set bits 2,4)
 *   - idm_net_poll does `mask &= ~0x14` (clear bits 2,4) on NAPI complete
 * The pattern "set in handler, clear in poll-complete" is consistent with
 * "1 = MASKED" semantics on bits 2 (RX) and 4 (TX). Bit 0 is unknown. */
#define IDM_IRQ_RX		0x04	/* bit 2 — RX pending */
#define IDM_IRQ_TX		0x10	/* bit 4 — TX done */
#define IDM_IRQ_NAPI_MASK	(IDM_IRQ_RX | IDM_IRQ_TX)
#define IDM_IRQ_ALL_MASKED	0x1F	/* mask everything */

/* Descriptor ring geometry (from RE) */
#define IDM_RX_RING_SIZE	2048
#define IDM_TX_RING_SIZE	1024
#define IDM_DESC_SIZE		8
#define IDM_RX_RING_BYTES	(IDM_RX_RING_SIZE * IDM_DESC_SIZE)	/* 16 KB */
#define IDM_TX_RING_BYTES	(IDM_TX_RING_SIZE * IDM_DESC_SIZE)	/* 8 KB */
#define IDM_DESC_BUF_BYTES	(IDM_RX_RING_BYTES + IDM_TX_RING_BYTES)	/* 24 KB */
#define IDM_TX_DESC_OFFSET	IDM_RX_RING_BYTES			/* TX after RX */

#define IDM_RX_SKB_SIZE		0x6C4		/* 1732 — matches stock alloc */
#define IDM_RX_SKB_HEADROOM	0x20		/* 32 B reserve */
#define IDM_TX_POOL_LIMIT	0x200
#define IDM_TX_PORT_LIMIT	0x400

/* Descriptor word [4:8] bit fields (TX) */
#define IDM_DESC_LEN_MASK	0x1FFFFF
#define IDM_DESC_CSUM_SHIFT	28
#define IDM_DESC_PORT_BIT	BIT(31)

#define ZX_NPORTS		2	/* idm0 + idm1 */

struct zx_eth;

struct zx_eth_port {
	struct net_device *netdev;
	struct zx_eth *eth;
	int idx;
	u32 stats_rx_drops;
};

struct zx_eth {
	struct device *dev;
	void __iomem *base;	/* NPP + IDM + MACs + PP + TM (all in 2MB block) */
	void __iomem *pon_early;	/* 0x92000000-0x921bffff (PON_TOP early regs — CLA tables, etc) */
	void __iomem *topcrm;	/* clock control (small ioremap of 0x94000000) */
	void __iomem *fpga_base;	/* unified FPGA window 0x92000000 + 4 MiB
					 * — addresses every register described in
					 * zx-fpga-reg-tables.h. Overlaps with `base`
					 * and `pon_early`; we use it for the
					 * descriptor-table-driven `zx_fpga_write()`
					 * helper only (separate from existing direct
					 * tm_write/pp_write paths). */
	int irq_idm;
	int irq_npp;
	int irq_tm;

	/* TM subsystem (CPU↔switch via "sw" netdev) */
	struct napi_struct tm_napi;
	struct net_device *sw_dev;
	void *bppe_cpu;		dma_addr_t bppe_dma;	/* u16 index array */
	void *bp_cpu;		dma_addr_t bp_dma;	/* BP backing store */
	void *rxdesc_cpu;	dma_addr_t rxdesc_dma;	/* 8 queues * N * 16B */
	void *txdesc_cpu;	dma_addr_t txdesc_dma;	/* 1024 * 16B TM TX desc ring */
	u32 tx_head;		/* current TX desc write index (0..1023) */
	spinlock_t tm_tx_lock;
	u32 rx_head[TM_NUM_RX_QUEUES];
	u32 tm_irq_count;
	u32 tm_napi_count;
	u32 tm_rx_count;
	u32 tm_rx_loopback_drops;
	u32 tm_tx_count;
	u32 tm_tx_dropped;
	/* Phase 5: dedup set for FDB learning — 128 buckets, 1 bit each.
	 * Indexed by (src_mac[11] & 0x7f). Crude but avoids re-adding the
	 * same MAC repeatedly. Reset on reload. */
	u8  fdb_learned[16];

	struct napi_struct napi;
	struct zx_eth_port ports[ZX_NPORTS];

	/* DMA descriptor ring (RX 16KB + TX 8KB, contiguous) */
	void *desc_cpu;
	dma_addr_t desc_dma;

	/* Shadow rings of SKB pointers */
	struct sk_buff *rx_skb[IDM_RX_RING_SIZE];
	struct sk_buff *tx_skb[IDM_TX_RING_SIZE];

	u32 rx_idx;	/* next slot to consume from HW */
	u32 tx_idx;	/* next slot to fill (producer) */
	u32 tx_done;	/* next slot to reclaim (consumer) */
	atomic_t tx_pending;

	spinlock_t tx_lock;

	bool started;

	/* Replay snapshots loaded via request_firmware */
	const struct firmware *fw_stock;
	const struct firmware *fw_cla;
	const struct firmware *fw_pm;
	const struct zx_replay_stock *r_stock; u32 r_n_stock;
	const struct zx_replay_cla   *r_cla;   u32 r_n_cla;
	const struct zx_replay_pm    *r_pm;    u32 r_n_pm;
};

/* ============================================================
 *   Low-level helpers
 * ============================================================ */

static inline u32 npp_read(struct zx_eth *e, u32 off)
{
	return readl(e->base + off);
}

static inline void npp_write(struct zx_eth *e, u32 off, u32 val)
{
	writel(val, e->base + off);
}

static inline void npp_or(struct zx_eth *e, u32 off, u32 bits)
{
	npp_write(e, off, npp_read(e, off) | bits);
}

static inline void npp_and(struct zx_eth *e, u32 off, u32 mask)
{
	npp_write(e, off, npp_read(e, off) & mask);
}

static inline u32 mac_off(int port, u32 off)
{
	return (port + 1) * MAC_STRIDE + off;
}

/* Use streaming DMA for SKB data; descriptor uses skb_data_phys */
static dma_addr_t zx_map_rx_skb(struct zx_eth *e, struct sk_buff *skb)
{
	return dma_map_single(e->dev, skb->data, IDM_RX_SKB_SIZE - IDM_RX_SKB_HEADROOM,
			      DMA_FROM_DEVICE);
}

/* ============================================================
 *   BRG RAM indirect access — for FDB / VLAN tables
 *   (decoded from brg_ram_get/set RE)
 * ============================================================ */

static int zx_brg_wait_ready(struct zx_eth *e)
{
	void __iomem *pp = e->base + PP_OFF;
	int n = 50;
	while (n--) {
		if (readl(pp + PP_BRG_RAM_READY) & 1)
			return 0;
		udelay(2);
	}
	return -EBUSY;
}

static int zx_brg_ram_set(struct zx_eth *e, u32 bucket, u32 slot,
			  u32 d0, u32 d1, u32 d2)
{
	void __iomem *pp = e->base + PP_OFF;

	if (zx_brg_wait_ready(e))
		return -EBUSY;
	writel(bucket | (slot << 22), pp + PP_BRG_RAM_CMD);
	writel(d0, pp + PP_BRG_RAM_D0);
	writel(d1, pp + PP_BRG_RAM_D1);
	writel(d2, pp + PP_BRG_RAM_D2);
	return 0;
}

static int zx_brg_ram_get(struct zx_eth *e, u32 bucket, u32 slot,
			  u32 *d0, u32 *d1, u32 *d2)
{
	void __iomem *pp = e->base + PP_OFF;

	if (zx_brg_wait_ready(e))
		return -EBUSY;
	writel(bucket | (slot << 22) | BRG_RAM_READ, pp + PP_BRG_RAM_CMD);
	if (zx_brg_wait_ready(e))
		return -EBUSY;
	*d0 = readl(pp + PP_BRG_RAM_D0);
	*d1 = readl(pp + PP_BRG_RAM_D1);
	*d2 = readl(pp + PP_BRG_RAM_D2);
	return 0;
}

/* CRC-16 used by stock to hash MAC into bucket (per crc_16 RE — standard
 * CRC-16/IBM with 0xA001 polynomial, init 0). */
static u16 zx_crc16(const u8 *data, int len)
{
	u16 crc = 0;
	int i, j;
	for (i = 0; i < len; i++) {
		crc ^= data[i];
		for (j = 0; j < 8; j++)
			crc = (crc & 1) ? (crc >> 1) ^ 0xA001 : crc >> 1;
	}
	return crc;
}

/* Add a static MAC entry to the FDB → switch routes frames with this dst MAC
 * to the given port. For CPU-bound traffic, port = ZX_CPU_PORT.
 *
 * Entry layout (12 bytes / 3 words, from pon_pp_add_mac RE):
 *   byte 0  : port mask = (1 << port)
 *   byte 1  : flags — bit 0 = static, bits 4-7 = "valid" nibble (0xf=in-use)
 *   byte 2  : low 8 bits of VLAN ID
 *   byte 3  : ((vid >> 8) & 0xf) | ((port & 0xf) << 4)
 *   bytes 4-9 : 6 MAC bytes (mac[0..5])
 *   bytes 10-11: pad/aging
 */
static int zx_fdb_add(struct zx_eth *e, const u8 *mac, u16 vlan, u8 port)
{
	u32 table_size_idx, table_size;
	u16 bucket;
	u32 d0, d1, d2, existing;
	int slot;
	u8 entry[12] = {0};

	/* Hash table size selected by pp[0x8184] & 3 → mac_table_size[] u16.
	 * Stock values are { 0x400, 0x800, 0x1000, 0x2000 } typically. We try
	 * the current table size from a small lookup; fallback to 0x400. */
	table_size_idx = readl(e->base + PP_OFF + PP_BRG_RAM_TABLE_SIZE) & 3;
	table_size = (table_size_idx == 0) ? 0x400 :
		     (table_size_idx == 1) ? 0x800 :
		     (table_size_idx == 2) ? 0x1000 : 0x2000;

	bucket = (zx_crc16(mac, 6) & (table_size - 1)) & 0x3FF;

	entry[0] = 1 << port;
	entry[1] = 0xF0;	/* valid */
	entry[2] = vlan & 0xFF;
	entry[3] = ((vlan >> 8) & 0xF) | ((port & 0xF) << 4);
	memcpy(&entry[4], mac, 6);
	d0 = entry[0] | (entry[1] << 8) | (entry[2] << 16) | (entry[3] << 24);
	d1 = entry[4] | (entry[5] << 8) | (entry[6] << 16) | (entry[7] << 24);
	d2 = entry[8] | (entry[9] << 8) | (entry[10] << 16) | (entry[11] << 24);

	/* Linear probe through 4 slots in bucket; find empty (valid nibble 0). */
	for (slot = 0; slot < 4; slot++) {
		if (zx_brg_ram_get(e, bucket, slot, &existing, &d1, &d2))
			return -EBUSY;
		if ((existing & 0x0000F000) == 0) {
			zx_brg_ram_set(e, bucket, slot, d0, d1, d2);
			dev_info(e->dev,
				 "FDB add: port=%u vlan=%u %pM → bucket=%u slot=%d\n",
				 port, vlan, mac, bucket, slot);
			return 0;
		}
	}
	return -ENOSPC;
}

/* Per-port isolation: bit pattern of ports this port may forward to.
 * Stock: port_isolate(6, 0xdf), port_isolate(7, 0xdf) for CPU/internal ports. */
static void zx_port_isolate(struct zx_eth *e, u8 port, u8 mask)
{
	void __iomem *pp = e->base + PP_OFF;
	u32 v = readl(pp + PP_BRG_ISOLATE(port));
	writel(v | mask, pp + PP_BRG_ISOLATE(port));
}

/* Add port to a VLAN — exactly like stock pon_pp_add_port_to_vlan.
 * Layout (per asm of @0x7504): VLAN entry sits in BRG_RAM at
 *   bucket = vid & 0xFFF,  slot = 4
 * entry[0] (first u32) encodes:
 *   bit 0     = VLAN valid (always set)
 *   bits[1+2*port..2+2*port] = 2-bit mode for port (mode 3 = tagged member)
 * mode field is positioned at (port*2 + 1) bits offset. */
static int zx_vlan_add_port(struct zx_eth *e, u16 vid, u8 port, u8 mode)
{
	u32 d0, d1, d2;
	u32 shift;
	int err;

	if (port >= 8)
		return -EINVAL;

	err = zx_brg_ram_get(e, vid & 0xFFF, 4, &d0, &d1, &d2);
	if (err)
		return err;

	shift = port * 2 + 1;
	d0 = ((d0 | 1) & ~(3 << shift)) | ((mode & 3) << shift);

	return zx_brg_ram_set(e, vid & 0xFFF, 4, d0, d1, d2);
}

/* ============================================================
 *   PP (Packet Processor) init — from pon_pp_*_init RE
 *
 * Without this the on-chip switch (SW) hands frames to PP but PP
 * doesn't elevate anything to NPP/IDM → CPU never sees RX.
 * Topology (from ZX279128S block diagram):
 *   RJ45 → GePHY → MAC[i] → SW → PP → DDR (via PP_AXI / IDM ring)
 * ============================================================ */

static void zx_pp_init(struct zx_eth *e)
{
	void __iomem *pp = e->base + PP_OFF;

	/* PP global config bank 0 (offsets 0x00–0x118) — verbatim replay of
	 * stock_eth.bin dump. These are what chip_tm_init / zte_api_pp_global_init
	 * leave the chip in. Without them PP silently drops CPU→switch packets. */
	writel(0x00000001, pp + 0x0000);
	writel(0x02abfc8d, pp + 0x0004);	/* ⭐ PP enable / config word */
	writel(0x00000001, pp + 0x0008);
	writel(0x00640064, pp + 0x000c);
	writel(0x00000001, pp + 0x0010);
	writel(0x00000fff, pp + 0x0020);	/* port mask */
	writel(0x00000106, pp + 0x0024);
	writel(0x01070104, pp + 0x0028);
	writel(0x00000106, pp + 0x002c);	/* CPU FWD base; OR'd below */
	writel(0x00000101, pp + 0x0030);
	writel(0x00010001, pp + 0x0034);
	writel(0x00000106, pp + 0x003c);
	writel(0x01030101, pp + 0x0040);
	writel(0x00000106, pp + 0x0044);
	writel(0x00111111, pp + 0x0048);
	writel(0x00000490, pp + 0x0054);
	writel(0x000003aa, pp + 0x0090);
	writel(0x0000007f, pp + 0x0094);
	writel(0x00002e00, pp + 0x009c);
	writel(0x000000f4, pp + 0x00a0);
	writel(0x00f42e00, pp + 0x00a4);
	writel(0x0000f42e, pp + 0x00ac);
	writel(0x00220022, pp + 0x00b0);
	writel(0x002e002e, pp + 0x00b4);
	writel(0x00f400f4, pp + 0x00b8);
	writel(0x04f4052e, pp + 0x00c0);
	writel(0x04f40000, pp + 0x00c4);
	writel(0x04f4052e, pp + 0x00c8);
	writel(0x04f4052e, pp + 0x00cc);
	writel(0x04f40000, pp + 0x00d0);
	writel(0x0000052e, pp + 0x00d4);
	writel(0x0000052e, pp + 0x00d8);
	writel(0x04f4052e, pp + 0x00dc);
	writel(0x0a220a22, pp + 0x00e0);
	/* PP per-instance config replicated 4 times — stock dump 2026-05-21 showed
	 * the marker 0x242F0 at offsets 0x104, 0x504, 0x904, 0xD04 (Δ 0x400).
	 * Each instance has the same 7-word config block. Our prior code only wrote
	 * instance 0 → other 3 unprogrammed → possibly the missing TX wire-emit fix.
	 * See H3600/stock_state/FINDINGS_2026-05-21.md */
	{
		int inst;
		for (inst = 0; inst < 4; inst++) {
			u32 ibase = 0x0100 + inst * 0x400;
			writel(0x0000000f, pp + ibase + 0x00);
			writel(0x000242f0, pp + ibase + 0x04);	/* marker */
			writel(0x00000064, pp + ibase + 0x08);
			writel(0x00000411, pp + ibase + 0x0c);
			writel(0x22008e3f, pp + ibase + 0x10);
			writel(0xc7000007, pp + ibase + 0x14);
			writel(0xf000107c, pp + ibase + 0x18);
		}
	}
	/* Stock CPU forwarding bit (lan_up_port=0 → bit 25). */
	writel(readl(pp + 0x002c) | PP_CPU_FWD_BIT, pp + 0x002c);

	/* pon_pp_brg_init — ALL values verified via live stock dump (not Ghidra
	 * decompile, which had printk strings cast as constants). */
	writel(0x040200FF, pp + PP_BRG_BASE + 0x0004);
	writel(0x0000DFDF, pp + PP_BRG_BASE + 0x0008);
	writel(0x0000000A, pp + PP_BRG_BASE + 0x0050);
	writel(0x00211B00, pp + PP_BRG_BASE + 0x0188);
	writel(0x000000FF, pp + PP_BRG_BASE + 0x01C0);
	writel(0x00005555, pp + PP_BRG_BASE + 0x01C4);
	writel(0x000000FF, pp + PP_BRG_BASE + 0x02C0);
	/* stock leaves BRG[0x0300], 0x0304, 0x0344, 0x0380, 0x063C as 0 — skip */
	writel(0x015555FF, pp + PP_BRG_BASE + 0x0340);
	writel(0x00000001, pp + PP_BRG_BASE + 0x0380);

	/* pon_pp_cla_init — verified */
	writel(0x00000600, pp + PP_CLA_BASE + 0x0080);
	/* stock leaves CLA[0x0084] as 0 — skip */

	/* PP_BRG port isolation table (pp+0x83C0..0x83DC) — exact stock values.
	 * Each port's mask = which OTHER ports it can FORWARD to (~self mask).
	 * Critical: port 5 (CPU) needs 0xDF to send to LAN ports 0..3.
	 * Without this, CPU→LAN packets get dropped by BRG isolation. */
	writel(0x000000FE, pp + PP_BRG_BASE + 0x03C0);	/* port 0 -> all except self */
	writel(0x000000FD, pp + PP_BRG_BASE + 0x03C4);	/* port 1 */
	writel(0x000000FB, pp + PP_BRG_BASE + 0x03C8);	/* port 2 */
	writel(0x000000F7, pp + PP_BRG_BASE + 0x03CC);	/* port 3 */
	writel(0x000000EF, pp + PP_BRG_BASE + 0x03D0);	/* port 4 */
	writel(0x000000DF, pp + PP_BRG_BASE + 0x03D4);	/* port 5 CPU -> CRITICAL */
	writel(0x000000FF, pp + PP_BRG_BASE + 0x03D8);	/* port 6 */
	writel(0x000000FF, pp + PP_BRG_BASE + 0x03DC);	/* port 7 */

	/* SBRG (Switch Bridge) flood/forward enables — controls per-port
	 * broadcast/unicast/multicast forwarding decisions. RE'd from sbragRegTable:
	 *   pp_brg[0x300] = broadcast flood enable mask (8 ports, 1 bit each)
	 *   pp_brg[0x304] = pon broadcast flood inctrl mask
	 *   pp_brg[0x340] = unknown unicast pktdeal (2-bit per port, 16-bit mask)
	 *   pp_brg[0x2D4] = unknown multicast pktdeal
	 * Enable broadcast for all ports + CPU. Without this, CPU broadcasts
	 * (ARP, IPv6-ND) get dropped at the SBRG flood stage. */
	writel(0x000000FF, pp + PP_BRG_BASE + 0x0300);	/* brdcst flood en: all 8 ports */
	writel(0x000000FF, pp + PP_BRG_BASE + 0x0304);	/* brdcst fwd en: all 8 ports */
}

/* ============================================================
 *   MAC init (per-port) — from smac_init() RE
 * ============================================================ */

/* MAC_REG_CONTROL semantics (verified from stock live dump):
 *   bit 0+1 (0x3) = MAC enable/running
 *   bit 13  (0x2000) = "no PHY / power-saved" (set when no link)
 * Stock writes 0xBAE003 initially (smac_init default), then phy_int handler
 * adjusts per port:
 *   - link UP:   clear bit 13, keep bits 0+1  → 0xBA6003
 *   - link DOWN: clear bits 0+1, set bit 13   → 0xBAE000
 * We don't run MDIO so hardcode: port 0 (LAN1, confirmed link UP from U-Boot)
 * gets 0xBA6003; other ports get 0xBAE000.
 *
 * MAC_REG_IRQ_MASK stock = 0x3FFF (not 0xFFFF as default init suggested). */
static void zx_smac_init_port(struct zx_eth *e, int port)
{
	u32 ctrl = (port == 0) ? 0xBA6003 : 0xBAE000;

	writel(ctrl,       e->base + mac_off(port, MAC_REG_CONTROL));
	writel(0x3FFF,     e->base + mac_off(port, MAC_REG_IRQ_MASK));
	writel(0x80000001, e->base + mac_off(port, MAC_REG_ENABLE));
	{
		u32 v = readl(e->base + mac_off(port, MAC_REG_D00));
		writel(v & ~0x2, e->base + mac_off(port, MAC_REG_D00));
	}
	{
		u32 v = readl(e->base + mac_off(port, MAC_REG_D30));
		writel(v & ~0x20, e->base + mac_off(port, MAC_REG_D30));
	}
	/* Enable the MAC at NPP level (npp[(port+1)*0x40000] |= 2) */
	npp_or(e, (port + 1) * MAC_STRIDE, 0x2);
}

/* ============================================================
 *   NPP global init — from tm_pon_npp_init + sub-init oneliners
 * ============================================================ */

static void zx_npp_init(struct zx_eth *e)
{
	/* All values verified from live stock dump. */
	npp_write(e, NPP_REG_IRQ_ENABLE, 0x000000);	/* stock = 0, not 0xFFFFFF */
	npp_write(e, NPP_REG_IRQ_MASK,   0x03FFFF);	/* stock = 0x3FFFF */
	msleep(1);

	/* IDM IRQs masked at probe — open() unmasks bit 2 selectively. */
	npp_write(e, IDM_REG_IRQ_MASK,   IDM_IRQ_ALL_MASKED);
	npp_write(e, IDM_REG_REG_18,     0x40);
	npp_write(e, IDM_REG_TIMEOUT,    5000);
	npp_write(e, IDM_REG_REG_10,     0x40);

	/* IDM control: stock has 0x020F6766 with everything running. Write the
	 * exact stock value (was OR-patched with wrong bits before). */
	npp_write(e, IDM_REG_CONTROL,    0x020F6766);

	/* PP setting from pon_npp_idm_init (left as-is for now). */
	writel(0x640, e->base + PP_OFF + 0x38);

	/* Sub-init oneliners — verified */
	npp_write(e, NPP_REG_SPA_INIT,    0);
	npp_write(e, NPP_REG_SIPC_INIT,   0x11);
	npp_write(e, NPP_REG_SMCT_INIT_0, 0xB);
	npp_write(e, NPP_REG_SMCT_INIT_1, 0x3810);

	/* Final global mask + reset */
	npp_write(e, NPP_REG_MASK_GLOBAL, 0xFFFFFFFF);
	npp_write(e, NPP_REG_RESET,       0);

	/* Per-MAC bring-up */
	for (int i = 0; i < ZX_NUM_MACS; i++)
		zx_smac_init_port(e, i);

	/* tm_pon_npp_init tail — verified */
	/* stock NPP[0x40] = 0 → don't OR 0x300 */
	npp_write(e, NPP_REG_INIT_VAL,   0x80);
	npp_write(e, NPP_REG_UOPC_INIT,  0x124);	/* exact stock value */

	/* PP CPU_FWD: stock reads 0x106 (bits 1, 2, 8). Our hypothesis that
	 * lan_up_port + 0x19 set bit 25 was wrong — stock doesn't set bit 25
	 * in this register. Leave it alone (PP brg_init sets it indirectly). */
}

/* ============================================================
 *   IDM descriptor ring + SKB pool init
 * ============================================================ */

static int zx_idm_init_rx(struct zx_eth *e)
{
	u32 *rx_desc = e->desc_cpu;	/* RX desc at offset 0 */

	for (int i = 0; i < IDM_RX_RING_SIZE; i++) {
		struct sk_buff *skb;
		dma_addr_t dma;

		skb = __netdev_alloc_skb(e->ports[0].netdev, IDM_RX_SKB_SIZE,
					 GFP_KERNEL);
		if (!skb)
			return -ENOMEM;
		skb_reserve(skb, IDM_RX_SKB_HEADROOM);

		dma = zx_map_rx_skb(e, skb);
		if (dma_mapping_error(e->dev, dma)) {
			dev_kfree_skb(skb);
			return -ENOMEM;
		}

		rx_desc[i * 2]     = cpu_to_le32(dma);
		rx_desc[i * 2 + 1] = 0;
		e->rx_skb[i] = skb;
	}
	return 0;
}

static void zx_idm_free_rx(struct zx_eth *e)
{
	u32 *rx_desc = e->desc_cpu;
	for (int i = 0; i < IDM_RX_RING_SIZE; i++) {
		if (!e->rx_skb[i])
			continue;
		dma_unmap_single(e->dev, le32_to_cpu(rx_desc[i * 2]),
				 IDM_RX_SKB_SIZE - IDM_RX_SKB_HEADROOM,
				 DMA_FROM_DEVICE);
		dev_kfree_skb(e->rx_skb[i]);
		e->rx_skb[i] = NULL;
	}
}

static int zx_idm_init(struct zx_eth *e)
{
	int err;

	e->desc_cpu = dma_alloc_coherent(e->dev, IDM_DESC_BUF_BYTES + 0x20,
					 &e->desc_dma, GFP_KERNEL);
	if (!e->desc_cpu)
		return -ENOMEM;
	if (e->desc_dma & 0x1F) {
		dev_err(e->dev, "DMA buffer not 32B aligned: %pad\n", &e->desc_dma);
		dma_free_coherent(e->dev, IDM_DESC_BUF_BYTES + 0x20,
				  e->desc_cpu, e->desc_dma);
		return -EINVAL;
	}
	memset(e->desc_cpu, 0, IDM_DESC_BUF_BYTES);

	/* Program ring bases (NPP[+0x8004]=RX, NPP[+0x8008]=TX) — order
	 * per stock idm_init: REG_C0=0, then RX, then TX. */
	npp_write(e, IDM_REG_REG_C0,       0);
	npp_write(e, IDM_REG_TX_DESC_BASE, e->desc_dma + IDM_TX_DESC_OFFSET);
	npp_write(e, IDM_REG_RX_DESC_BASE, e->desc_dma);

	err = zx_idm_init_rx(e);
	if (err) {
		dma_free_coherent(e->dev, IDM_DESC_BUF_BYTES + 0x20,
				  e->desc_cpu, e->desc_dma);
		return err;
	}

	/* Stock kicks RX once per slot during init (2048 single-buffer writes).
	 * Match exactly — bits[31:16]=1 means "1 new refill available". */
	for (int i = 0; i < IDM_RX_RING_SIZE; i++)
		npp_write(e, IDM_REG_RX_KICK, 0x10000);

	/* Final RX enable from stock */
	npp_write(e, IDM_REG_RX_ENABLE, 0x4000800);

	e->rx_idx = 0;
	e->tx_idx = 0;
	e->tx_done = 0;
	atomic_set(&e->tx_pending, 0);

	return 0;
}

/* ============================================================
 *   TX completion reclaim — from idm_check_tx_done_nolock RE
 * ============================================================ */

static void zx_idm_tx_reclaim(struct zx_eth *e)
{
	u32 *tx_desc = e->desc_cpu + IDM_TX_DESC_OFFSET;
	unsigned long flags;
	u32 done_cnt, i;

	spin_lock_irqsave(&e->tx_lock, flags);
	done_cnt = npp_read(e, IDM_REG_TX_STATUS) & 0xFFFF;
	done_cnt = min_t(u32, done_cnt, 0x100);	/* stock caps at 256/call */
	if (done_cnt == 0)
		goto out;

	for (i = 0; i < done_cnt; i++) {
		u32 slot = e->tx_done;
		struct sk_buff *skb = e->tx_skb[slot];

		e->tx_skb[slot] = NULL;
		e->tx_done = (slot + 1) & (IDM_TX_RING_SIZE - 1);
		if (!skb)
			continue;
		dma_unmap_single(e->dev, le32_to_cpu(tx_desc[slot * 2]),
				 skb->len, DMA_TO_DEVICE);
		dev_consume_skb_any(skb);
		atomic_dec(&e->tx_pending);
	}
	/* ACK to HW — low 16 bits of TX_KICK are "consumed count" */
	npp_write(e, IDM_REG_TX_KICK, done_cnt);

	/* Wake the queue if it was throttled */
	for (i = 0; i < ZX_NPORTS; i++) {
		if (netif_queue_stopped(e->ports[i].netdev))
			netif_wake_queue(e->ports[i].netdev);
	}
out:
	spin_unlock_irqrestore(&e->tx_lock, flags);
}

/* ============================================================
 *   RX path — NAPI poll (from idm_net_poll RE)
 * ============================================================ */

static int zx_idm_poll(struct napi_struct *napi, int budget)
{
	struct zx_eth *e = container_of(napi, struct zx_eth, napi);
	u32 *rx_desc = e->desc_cpu;
	int done = 0;

	/* Always check TX done first (stock does same in idm_net_poll) */
	zx_idm_tx_reclaim(e);

	while (done < budget) {
		u32 qlen = npp_read(e, IDM_REG_RX_QLEN) & 0xFFFF;
		u32 to_take, n;

		if (qlen == 0)
			break;

		to_take = min_t(u32, qlen, (u32)(budget - done));

		for (n = 0; n < to_take; n++) {
			u32 idx = e->rx_idx;
			u32 *d = &rx_desc[idx * 2];
			struct sk_buff *skb = e->rx_skb[idx];
			struct sk_buff *new_skb;
			dma_addr_t new_dma;
			u32 word1 = le32_to_cpu(d[1]);
			u16 len = word1 & 0x3FFF;
			u8 port = (word1 >> 31) & 1;
			struct net_device *ndev = e->ports[port].netdev;

			new_skb = __netdev_alloc_skb(ndev, IDM_RX_SKB_SIZE, GFP_ATOMIC);
			if (!new_skb) {
				e->ports[port].stats_rx_drops++;
				ndev->stats.rx_dropped++;
				goto next;
			}
			skb_reserve(new_skb, IDM_RX_SKB_HEADROOM);
			new_dma = zx_map_rx_skb(e, new_skb);
			if (dma_mapping_error(e->dev, new_dma)) {
				dev_kfree_skb(new_skb);
				ndev->stats.rx_dropped++;
				goto next;
			}

			dma_unmap_single(e->dev, le32_to_cpu(d[0]),
					 IDM_RX_SKB_SIZE - IDM_RX_SKB_HEADROOM,
					 DMA_FROM_DEVICE);
			skb_put(skb, len);
			skb->dev = ndev;
			skb->protocol = eth_type_trans(skb, ndev);
			ndev->stats.rx_bytes += len;
			ndev->stats.rx_packets++;
			napi_gro_receive(napi, skb);

			d[0] = cpu_to_le32(new_dma);
			d[1] = 0;
			e->rx_skb[idx] = new_skb;
next:
			e->rx_idx = (idx + 1) & (IDM_RX_RING_SIZE - 1);
			done++;
		}
		/* ACK consumed slots + announce refills (both = n) */
		npp_write(e, IDM_REG_RX_KICK, (n << 16) | n);
	}

	if (done < budget) {
		napi_complete_done(napi, done);
		/* Unmask RX+TX IRQs (clear bits 2+4) — per stock idm_net_poll end */
		npp_and(e, IDM_REG_IRQ_MASK, ~IDM_IRQ_NAPI_MASK);
	}

	return done;
}

/* ============================================================
 *   IRQ handler — match stock idm_net_int semantics
 * ============================================================ */

static irqreturn_t zx_idm_irq(int irq, void *dev_id)
{
	struct zx_eth *e = dev_id;
	u32 status = npp_read(e, IDM_REG_IRQ_STATUS);

	if (!status)
		return IRQ_NONE;

	/* Mask bits 2+4 (RX+TX) — silences the IRQ; NAPI will unmask. */
	npp_or(e, IDM_REG_IRQ_MASK, IDM_IRQ_NAPI_MASK);
	napi_schedule(&e->napi);
	return IRQ_HANDLED;
}

/* ============================================================
 *   TX path — from idm_net_tx RE
 * ============================================================ */

static netdev_tx_t zx_idm_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct zx_eth_port *port = *(struct zx_eth_port **)netdev_priv(ndev);
	struct zx_eth *e = port->eth;
	u32 *tx_desc = e->desc_cpu + IDM_TX_DESC_OFFSET;
	dma_addr_t dma;
	unsigned long flags;
	u32 idx, len;

	/* Min frame length per stock (0x21) */
	if (skb->len < 0x21) {
		if (skb_padto(skb, 0x21)) {
			ndev->stats.tx_dropped++;
			return NETDEV_TX_OK;
		}
		skb->len = 0x21;
	}
	len = skb->len;

	if (atomic_read(&e->tx_pending) >= IDM_TX_POOL_LIMIT) {
		netif_stop_queue(ndev);
		return NETDEV_TX_BUSY;
	}

	dma = dma_map_single(e->dev, skb->data, len, DMA_TO_DEVICE);
	if (dma_mapping_error(e->dev, dma)) {
		ndev->stats.tx_dropped++;
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	spin_lock_irqsave(&e->tx_lock, flags);
	idx = e->tx_idx;
	e->tx_idx = (idx + 1) & (IDM_TX_RING_SIZE - 1);

	tx_desc[idx * 2]     = cpu_to_le32(dma);
	tx_desc[idx * 2 + 1] = cpu_to_le32((len & IDM_DESC_LEN_MASK) |
					   (port->idx ? IDM_DESC_PORT_BIT : 0));
	e->tx_skb[idx] = skb;
	atomic_inc(&e->tx_pending);

	/* DSB to flush write before kick (stock does DataSynchronizationBarrier(0xf)) */
	dma_wmb();
	npp_write(e, IDM_REG_TX_KICK, 1 << 16);

	ndev->stats.tx_bytes   += len;
	ndev->stats.tx_packets += 1;
	spin_unlock_irqrestore(&e->tx_lock, flags);
	return NETDEV_TX_OK;
}

/* ============================================================
 *   Netdev ops
 * ============================================================ */

static int zx_eth_open(struct net_device *ndev)
{
	struct zx_eth_port *port = *(struct zx_eth_port **)netdev_priv(ndev);
	struct zx_eth *e = port->eth;

	netdev_info(ndev, "open\n");

	/* First port to open: enable NAPI + unmask RX IRQ only.
	 * (Stock idm_net_open only clears bit 2 (RX) — TX completion is
	 * polled from NAPI alongside RX, no separate IRQ enable needed.) */
	if (!e->started) {
		napi_enable(&e->napi);
		/* Unmask BOTH RX (bit 2) and TX done (bit 4) — see if any IDM IRQ fires */
		npp_and(e, IDM_REG_IRQ_MASK, ~IDM_IRQ_NAPI_MASK);
		e->started = true;
	}

	netif_carrier_on(ndev);
	netif_start_queue(ndev);
	return 0;
}

static int zx_eth_stop(struct net_device *ndev)
{
	struct zx_eth_port *port = *(struct zx_eth_port **)netdev_priv(ndev);
	struct zx_eth *e = port->eth;
	int i, others_up = 0;

	netif_stop_queue(ndev);
	netif_carrier_off(ndev);

	for (i = 0; i < ZX_NPORTS; i++)
		if (e->ports[i].netdev != ndev &&
		    (e->ports[i].netdev->flags & IFF_UP))
			others_up++;

	if (!others_up && e->started) {
		/* Mask all IRQs (stock idm_net_stop sets bits 2+4) */
		npp_or(e, IDM_REG_IRQ_MASK, IDM_IRQ_NAPI_MASK);
		napi_disable(&e->napi);
		e->started = false;
	}
	netdev_info(ndev, "stop\n");
	return 0;
}

static const struct net_device_ops zx_eth_netdev_ops = {
	.ndo_open	= zx_eth_open,
	.ndo_stop	= zx_eth_stop,
	.ndo_start_xmit	= zx_idm_xmit,
	.ndo_set_mac_address = eth_mac_addr,
	.ndo_validate_addr   = eth_validate_addr,
};

/* ============================================================
 *   TM (Traffic Manager) — CPU↔switch path
 *   Architecture mirrors stock pon_tm_* + airoha_eth.c patterns.
 * ============================================================ */

static inline u32 tm_read(struct zx_eth *e, u32 off)
{
	return readl(e->base + TM_OFF + off);
}

static inline void tm_write(struct zx_eth *e, u32 off, u32 val)
{
	writel(val, e->base + TM_OFF + off);
}

static inline void tm_or(struct zx_eth *e, u32 off, u32 bits)
{
	tm_write(e, off, tm_read(e, off) | bits);
}

static inline void tm_and(struct zx_eth *e, u32 off, u32 mask)
{
	tm_write(e, off, tm_read(e, off) & mask);
}

/* Allocate DMA-coherent regions for BPPE pool, BP backing store, RX desc rings.
 * Stock uses reserved DDR (0x4E700000), we use CMA-backed coherent for now —
 * total <2MB which fits within default CMA. */
static int zx_tm_alloc_pools(struct zx_eth *e)
{
	size_t bppe_sz = TM_BPPE_POOL_SIZE * sizeof(u16);
	size_t bp_sz   = TM_BPPE_POOL_SIZE * TM_BP_SIZE;
	/* RX desc area: HW expects UP ring at base+0, DN ring at base+0x10000.
	 * With 1024 descs/queue × 8 queues × 16B = 128KB per ring; need 256KB total
	 * but stock used 64KB offset between rings... use 0x40000 to be safe. */
	size_t desc_sz = 0x40000;
	u16 *bppe;
	int i;

	e->bppe_cpu = dma_alloc_coherent(e->dev, bppe_sz, &e->bppe_dma, GFP_KERNEL);
	e->bp_cpu   = dma_alloc_coherent(e->dev, bp_sz,   &e->bp_dma,   GFP_KERNEL);
	e->rxdesc_cpu = dma_alloc_coherent(e->dev, desc_sz, &e->rxdesc_dma, GFP_KERNEL);
	/* TM TX desc ring: 1024 × 16 B */
	e->txdesc_cpu = dma_alloc_coherent(e->dev, TM_TX_RING_SIZE * TM_TX_DESC_SIZE,
					   &e->txdesc_dma, GFP_KERNEL);
	if (!e->bppe_cpu || !e->bp_cpu || !e->rxdesc_cpu || !e->txdesc_cpu)
		return -ENOMEM;
	e->tx_head = 0;
	spin_lock_init(&e->tm_tx_lock);

	/* Populate BPPE: stock writes byteswapped u16 indices 0..N-1.
	 * Each entry says "BP slot index". HW pulls these one at a time when
	 * RX needs a buffer. */
	bppe = (u16 *)e->bppe_cpu;
	for (i = 0; i < TM_BPPE_POOL_SIZE; i++)
		bppe[i] = cpu_to_be16(i);

	dev_info(e->dev, "TM pools: bppe=%pad (%zu B), bp=%pad (%zu B), rxdesc=%pad (%zu B)\n",
		 &e->bppe_dma, bppe_sz, &e->bp_dma, bp_sz,
		 &e->rxdesc_dma, desc_sz);
	return 0;
}

static void zx_tm_free_pools(struct zx_eth *e)
{
	if (e->bppe_cpu)
		dma_free_coherent(e->dev, TM_BPPE_POOL_SIZE * sizeof(u16),
				  e->bppe_cpu, e->bppe_dma);
	if (e->bp_cpu)
		dma_free_coherent(e->dev, TM_BPPE_POOL_SIZE * TM_BP_SIZE,
				  e->bp_cpu, e->bp_dma);
	if (e->rxdesc_cpu)
		dma_free_coherent(e->dev, 0x40000,
				  e->rxdesc_cpu, e->rxdesc_dma);
	if (e->txdesc_cpu)
		dma_free_coherent(e->dev, TM_TX_RING_SIZE * TM_TX_DESC_SIZE,
				  e->txdesc_cpu, e->txdesc_dma);
	e->bppe_cpu = e->bp_cpu = e->rxdesc_cpu = e->txdesc_cpu = NULL;
}

/* pon_tm_bmu_init equivalent — register pool addrs + sizes with BMU */
static void zx_tm_bmu_init(struct zx_eth *e)
{
	/* BP/BPPE base physical addresses */
	tm_write(e, TM_REG_BPPE_BASE,       e->bppe_dma);
	tm_write(e, TM_REG_JUMBO_BPPE_BASE, e->bppe_dma);  /* no jumbo for now */
	tm_write(e, TM_REG_BP_BUFFER_BASE,  e->bp_dma);
	tm_write(e, TM_REG_BP_JUMBO_BASE,   e->bp_dma);
	/* Stock: low16=BP_SIZE=0x900, high16=JUMBO_BP_SIZE=0x2800 */
	tm_write(e, TM_REG_BP_SIZE,
		 (TM_BP_SIZE & 0xFFFF) | ((TM_JUMBO_BP_SIZE & 0xFFFF) << 16));

	/* BMU control regs (from pon_tm_bmu_init RE) */
	tm_write(e, TM_REG_BMU_INIT,        0);
	tm_write(e, TM_REG_BMU_CTRL,        0x104C040);
	tm_write(e, TM_REG_BMU_CTRL2,       0x104C040);

	/* Pool sizes: high 16 = total, low 16 = (runtime) consumed */
	tm_write(e, TM_REG_BMU_POOL_SIZE,   TM_BPPE_POOL_SIZE << 16);
	tm_write(e, TM_REG_BMU_JUMBO_POOL,  0);  /* no jumbo */

	/* tm[0x8058] = number of BPPE slots. Stock runtime = 0x100 = 256
	 * (captured via regtracer on running stock).  Our previous formula
	 * "(POOL_SIZE>>5)-1" wrote 7 which kept the BMU rejecting allocs. */
	tm_write(e, TM_REG_BMU_BUCKETS_M1,  TM_BPPE_POOL_SIZE);
	tm_write(e, TM_REG_BMU_JUMBO_BUCK,  0);

	/* tm[0x8040] = BPPI ptr. Stock value 0x00c50076 looks like a runtime
	 * cursor (low 16 = head, high 16 = tail). Init the head to 0 so HW
	 * starts pulling BPPE entries from slot 0. */
	tm_write(e, 0x8040, 0);

	dev_info(e->dev, "TM BMU init: pool_size=%d, bp_size=%d, bppe@%pad\n",
		 TM_BPPE_POOL_SIZE, TM_BP_SIZE, &e->bppe_dma);
}

/* pon_tm_bmu_enable — turns the BMU on. Without this it stays idle. */
static void zx_tm_bmu_enable(struct zx_eth *e)
{
	tm_write(e, TM_REG_BMU_INIT, 1);
	dev_info(e->dev, "TM BMU enabled: tm[0x8000]=%#x 0x8058=%#x 0x8048=%#x 0x8090=%#x\n",
		 tm_read(e, TM_REG_BMU_INIT),
		 tm_read(e, 0x8058), tm_read(e, 0x8048), tm_read(e, 0x8090));
}

/* Register a MAC as a CPU port destination in the ONU MAC table.
 * From stock spa_set_onu_mac_addr (in tm.ko, calls tmOnuRegWrite via spaRegTable).
 * Hardware: spaRegTable entries [0x16] + [0x17] target NPP+0x14120 + slot*8.
 * Layout per slot (8 bytes):
 *   +0: mac[2]<<24 | mac[3]<<16 | mac[4]<<8 | mac[5]
 *   +4: mac[0]<<8  | mac[1]                                    (low 16 bits)
 * When switch sees frame with dst_mac matching a slot → routes to CPU port. */
#define ZX_SPA_ONU_MAC_BASE	0x14120
/* pp_pm indirect access regs (relative to npp_base). From ppPmRegTable decode:
 *   [0] cmd        0x1dc014 (mask fcfffff)
 *   [1] done_bit   0x1dc018 (mask 1)
 *   [2] data slot 0..3 starting 0x1dc01c (stride 4)
 *   [3] data slot 4..7 starting 0x1dc100 (stride 4)
 */
#define PP_PM_REG_CMD		0x1DC014
#define PP_PM_REG_DONE		0x1DC018
#define PP_PM_REG_DATA0		0x1DC01C	/* data slot 0..3 stride 4 */
#define PP_PM_REG_DATA4		0x1DC100	/* data slot 4..7 stride 4 */

static int zx_pp_pm_wait_done(struct zx_eth *e)
{
	int t = 100;
	while (t-- && !(readl(e->base + PP_PM_REG_DONE) & 1))
		udelay(50);
	return t < 0 ? -EBUSY : 0;
}

/* Mirrors stock pp_pm_set_indirect_cmd(rw=0, ram_id=0xc, idx).
 * cmd = idx | (ram_id << 22) | (rw << 27) */
static void zx_pp_pm_set_cmd(struct zx_eth *e, u8 rw, u8 ram_id, u32 addr)
{
	writel(addr | ((u32)ram_id << 22) | ((u32)rw << 27),
	       e->base + PP_PM_REG_CMD);
}

/* Write an 8-word pp_pm RAM entry. Data slots 0..3 at +0x01C, slots 4..7 at +0x100. */
static int zx_pp_pm_write_entry(struct zx_eth *e, u8 ram_id, u32 ram_addr,
				const u32 data[8])
{
	int i;
	if (zx_pp_pm_wait_done(e))
		return -EBUSY;
	for (i = 0; i < 4; i++)
		writel(data[i], e->base + PP_PM_REG_DATA0 + i * 4);
	for (i = 4; i < 8; i++)
		writel(data[i], e->base + PP_PM_REG_DATA4 + (i - 4) * 4);
	zx_pp_pm_set_cmd(e, 0, ram_id, ram_addr);
	return zx_pp_pm_wait_done(e);
}

/* Replay all pp_pm entries dumped from stock (ram=3 default flow_info + ram=6 global). */
static void zx_pp_pm_apply_replay(struct zx_eth *e)
{
	u32 i, ok = 0, fail = 0;
	if (!e->r_pm) {
		dev_warn(e->dev, "pp_pm replay: no firmware loaded\n");
		return;
	}
	for (i = 0; i < e->r_n_pm; i++) {
		if (zx_pp_pm_write_entry(e, e->r_pm[i].ram_id,
					 e->r_pm[i].ram_addr,
					 e->r_pm[i].data) == 0)
			ok++;
		else
			fail++;
	}
	dev_info(e->dev, "pp_pm replay: %u ok, %u fail (%u total)\n",
		 ok, fail, e->r_n_pm);
}

static int zx_pp_pm_set_cpu_mac(struct zx_eth *e, u8 slot, const u8 *mac)
{
	u32 hi = ((u32)mac[0] << 8) | mac[1];
	u32 lo = ((u32)mac[2] << 24) | ((u32)mac[3] << 16) |
		 ((u32)mac[4] << 8)  | mac[5];

	if (zx_pp_pm_wait_done(e))
		return -EBUSY;
	zx_pp_pm_set_cmd(e, 0, 0xc, slot);
	writel(hi, e->base + PP_PM_REG_DATA0 + 1 * 4);	/* data slot 1 */
	writel(lo, e->base + PP_PM_REG_DATA0 + 0 * 4);	/* data slot 0 */
	dev_info(e->dev, "pp_pm CPU MAC ram[%u] = %pM (data1=%#x data0=%#x)\n",
		 slot, mac, hi, lo);
	return 0;
}

/* ============================================================
 *   CLA (Classifier) indirect RAM access — for ACL hash table writes
 *   From RE of cla_set_indirect_rw_cmd/data/status in tm.ko.
 *   claRegTable entries:
 *     [0] cmd  = pp[0xC014]   bits: addr[21:0] | ram_id[26:22] | rw_en[27]
 *     [1] done = pp[0xC018]   bit 0
 *     [2] data = pp[0xC01C..0xC05C] stride 4, 17 slots (data[0..16])
 * ============================================================ */
#define CLA_REG_CMD		0x1CC014	/* pp+0xC014 — npp_base+0x1CC014 */
#define CLA_REG_DONE		0x1CC018
#define CLA_REG_DATA0		0x1CC01C	/* stride 4, slots 0..16 */
#define CLA_RAM_READ		(1u << 27)

static int zx_cla_wait_done(struct zx_eth *e)
{
	int t = 100;
	while (t-- && !(readl(e->base + CLA_REG_DONE) & 1))
		udelay(5);
	return t < 0 ? -EBUSY : 0;
}

/* Write one CLA RAM entry: 17 data words to data slots, then cmd reg.
 * Per RE: write data first, then cmd with rw=0 triggers commit. */
static int zx_cla_write_entry(struct zx_eth *e, u8 ram_id, u32 ram_addr,
			      const u32 data[17])
{
	int i;
	if (zx_cla_wait_done(e))
		return -EBUSY;
	for (i = 0; i < 17; i++)
		writel(data[i], e->base + CLA_REG_DATA0 + i * 4);
	writel(ram_addr | ((u32)ram_id << 22), e->base + CLA_REG_CMD);
	return zx_cla_wait_done(e);
}

/* Replay all CLA entries we dumped from stock */
static void zx_cla_apply_replay(struct zx_eth *e)
{
	u32 i, ok = 0, fail = 0;
	u32 ram7_data[17] = {7, 0,};

	if (!e->r_cla) {
		dev_warn(e->dev, "CLA replay: no firmware loaded\n");
		return;
	}
	for (i = 0; i < e->r_n_cla; i++) {
		if (zx_cla_write_entry(e, e->r_cla[i].ram_id,
				       e->r_cla[i].ram_addr,
				       e->r_cla[i].data) == 0)
			ok++;
		else
			fail++;
	}
	/* ram=7 (CPU queue): all entries have data[0]=7, rest 0 — generate runtime */
	for (i = ZX_CLA_RAM7_FIRST; i <= ZX_CLA_RAM7_LAST; i++) {
		if (zx_cla_write_entry(e, 7, i, ram7_data) == 0)
			ok++;
		else
			fail++;
	}
	dev_info(e->dev, "CLA replay: %u ok, %u fail (%u snapshot + ram=7 0..%d)\n",
		 ok, fail, e->r_n_cla, ZX_CLA_RAM7_LAST);
}

/* chip_tm_init's trap_queue setup — replays def_ptl_pkt_map via cla_set_cpu_queue_id.
 * RE'd from switch.ko:chip_tm_init @ 0x36ac calling tm.ko functions.
 * Per stock, maps each (ptype, port) → CPU queue id. Port 5 is CPU (skipped). */
#include "zx_pkt_map.h"

static int zx_cla_set_cpu_queue_id(struct zx_eth *e, u32 addr, u8 qid)
{
	u32 ram7_data[17] = {0,};
	ram7_data[0] = qid;
	/* Reuses zx_cla_write_entry: writes data[0..16] then CMD with ram_id<<22.
	 * For trap_queue setup we only set data[0]=qid, rest 0. */
	return zx_cla_write_entry(e, 7, addr, ram7_data);
}

/* ===================================================================
 * Phase 4 (in progress, 2026-05-24): per-function ports of stock
 * chip_tm_init's call chain.
 *
 * Each function here is the C equivalent of a stock tm.ko leaf
 * helper. The data sources used to write them:
 *   - kotrace runtime trace (call sequence + r0..r3 args), in
 *     tasks/00.01.eth-driver/findings/captures/kotrace_p3c_full_args.txt
 *   - register descriptor tables in zx-fpga-reg-tables.h
 *   - stock disassembly via `arm-linux-gnueabi-objdump --disassemble=<fn>`
 *
 * fpga_base is the unified 4 MiB ioremap of 0x92000000..0x923fffff
 * — the same physical window stock's zx_ponreg.ko maps at virt
 * 0xf4000000 and accesses via writel(val, fpga_base + off * 4).
 * =================================================================== */

/* Write one FPGA register, descriptor-table style.
 * Mirrors stock `tmOnuRegWrite(reg_id, val, sub_idx, table)`:
 *   addr_off  = table[reg_id].base_off + table[reg_id].stride * sub_idx
 *   writel(val, fpga_base + addr_off * 4)
 * No mask/shift handling — stock tmOnuRegWrite does a read-mask-or-write
 * cycle using table[].mask which we haven't extracted. For now we assume
 * the descriptor entries we touch want whole-register writes.
 */
/* Wrapper around the inline helper in zx-fpga-reg-tables.h that adds
 * the struct zx_eth's fpga_base lookup + ratelimited dev_warn diagnostics. */
static int zx_table_write(struct zx_eth *e,
			  const struct zx_fpga_reg *table, size_t n,
			  u16 reg_id, u32 val, u32 sub_idx)
{
	int rc = zx_fpga_table_write(e->fpga_base, table, n, reg_id, val, sub_idx);
	if (rc < 0)
		dev_warn_ratelimited(e->dev, "fpga_table_write(%u, val=%#x, sub=%u): %d\n",
				     reg_id, val, sub_idx, rc);
	return rc;
}

/* Stock tm_port_isolate_set(port, mask).
 *   8 calls during chip_tm_init, one per port.
 *   `mask` = bitmap of ports this port may NOT forward to (8-port wide).
 *   Stock writes sbragRegTable[57] (base 0xe20f0, stride 1, per port).
 *
 * Bit-fiddling reproduced from tm_port_isolate_set's disassembly:
 *   inv = ~mask
 *   out = ((inv >> 5) & 1)        bit 5 of inv → out bit 0
 *       | ((inv << 1) & 0x3e)     inv bits 0..4 → out bits 1..5
 *       |  (inv & 0xc0)           inv bits 6..7 → out bits 6..7
 * The reshape is to map an 8-port bitmask onto the HW register's bit layout.
 */
static int zx_tm_port_isolate_set(struct zx_eth *e, u32 port, u32 mask)
{
	u32 inv = ~mask;
	u32 hw  = ((inv >> 5) & 1u)
		| ((inv << 1) & 0x3eu)
		| ( inv       & 0xc0u);
	return zx_table_write(e, zx_sbragregtable,
			      ZX_SBRAGREGTABLE_COUNT, 57, hw, port);
}

/* Stock spa_set_enty_pktdeal_cfg(port, proto, action) →
 *   tmOnuRegWrite(reg_id = 67 + proto, val = action, sub_idx = port, spaRegTable)
 * Per disasm of spa_set_enty_pktdeal_cfg @ 0x2b1f4 in tm.ko.
 * spaRegTable entries 67..137 are packed 2-bit fields (mask 0x3) at
 * shift = (proto & 7) * 2 within the same register, stride 5 per port. */
static int zx_spa_set_enty_pktdeal_cfg(struct zx_eth *e, u8 port, u8 proto, u8 action)
{
	if (proto > 0x46) return -EINVAL;  /* table has 71 protos */
	return zx_table_write(e, zx_sparegtable, ZX_SPAREGTABLE_COUNT,
			      67 + proto, action, port);
}

/* Replay the def_ptl_pkt_action table for every port × every protocol.
 * This is stock chip_tm_init's pp_set_pro_action loop, decomposed:
 * stock calls pp_set_pro_action(pp_inst, proto, action) which internally
 * loops over ports → spa_set_enty_pktdeal_cfg(port, proto, action). We
 * write the same configuration directly, port-major. The table
 * zx_pp_pro_actions[] was extracted from kotrace trace; see
 * tasks/00.01.eth-driver/findings/chip_tm_init_args.md. */
static void zx_chip_tm_init_pro_action(struct zx_eth *e)
{
	int port, i, ok = 0, fail = 0;
	for (port = 0; port < 8; port++) {
		for (i = 0; i < ZX_PP_PRO_ACTION_COUNT; i++) {
			/* Most entries are symmetric PP0 == PP1; we use PP0 action.
			 * proto 0x14 differs (PP0=1, PP1=0) — pick the trap variant. */
			u8 action = zx_pp_pro_actions[i].action_pp0;
			if (zx_spa_set_enty_pktdeal_cfg(e, port, zx_pp_pro_actions[i].proto, action) == 0)
				ok++;
			else
				fail++;
		}
	}
	dev_info(e->dev, "pro_action replay: %d ok, %d fail (%d entries × 8 ports)\n",
		 ok, fail, ZX_PP_PRO_ACTION_COUNT);
}

/* Replay chip_tm_init's per-port isolation loop.
 * Masks observed in kotrace trace, one per port (sw_init_switch boot path):
 *   port 0 → 0xff01    port 4 → 0xff10
 *   port 1 → 0xff02    port 5 → 0xff20 (extrapolated)
 *   port 2 → 0xff04    port 6 → 0xff40 (extrapolated)
 *   port 3 → 0xff08    port 7 → 0xff80 (extrapolated)
 * Each port masks ITSELF off the destination set — standard ONT.
 */
static void zx_chip_tm_init_isolate(struct zx_eth *e)
{
	int p;
	for (p = 0; p < 8; p++) {
		int rc = zx_tm_port_isolate_set(e, p, 0xffffff00u | (1u << p));
		if (rc)
			dev_warn(e->dev, "isolate port %d: %d\n", p, rc);
	}
	dev_info(e->dev, "port isolation programmed (sbragRegTable[57] x 8)\n");
}

static void zx_chip_tm_init_trap_queues(struct zx_eth *e)
{
	u32 ok = 0, fail = 0;
	int port, i;

	for (i = 0; i < ZX_DEF_PTL_PKT_MAP_COUNT; i++) {
		u8 ptype = zx_def_ptl_pkt_map[i].ptype;
		u8 qid   = zx_def_ptl_pkt_map[i].qid0;	/* bank 0 only for now */
		for (port = 0; port < 8; port++) {
			u32 addr;
			if (port == 5)
				continue;	/* CPU port — skip */
			addr = ptype | zx_pkt_port_addr_offset[port];
			if (zx_cla_set_cpu_queue_id(e, addr, qid) == 0)
				ok++;
			else
				fail++;
		}
	}
	dev_info(e->dev, "trap_queue replay: %u ok, %u fail (%u entries × 7 ports)\n",
		 ok, fail, ZX_DEF_PTL_PKT_MAP_COUNT);
}

/* Both writes: spa table + pp_pm RAM (mirrors stock tm_onu_mac_addr_set) */
static void zx_register_cpu_mac(struct zx_eth *e, u8 slot, const u8 *mac)
{
	u32 low = ((u32)mac[2] << 24) | ((u32)mac[3] << 16) |
		  ((u32)mac[4] << 8)  | mac[5];
	u32 high = ((u32)mac[0] << 8) | mac[1];
	void __iomem *spa = e->base + ZX_SPA_ONU_MAC_BASE + slot * 8;
	writel(low,  spa + 0);
	writel(high, spa + 4);
	zx_pp_pm_set_cpu_mac(e, slot, mac);
	dev_info(e->dev, "CPU MAC slot[%u] = %pM (spa+pp_pm registered)\n",
		 slot, mac);
}

/* Pre-DMA setup (tm_pon_tm_init opening lines).
 *
 * IMPORTANT FINDING (2026-05-21, stock /dev/mem dump via dumpregs.sh):
 * TM register block has **4 identical instances** replicated at offsets
 * 0x000, 0x400, 0x800, 0xC00. Each instance is 0x400 bytes. Stock programs
 * all 4 instances with IDENTICAL values. Likely one TM instance per
 * port/channel (4 GE PHY ports). Our previous code only wrote to instance
 * 0 (plus partial 0x400) — the TX wire-emit may use any of instance 0..3
 * depending on which port the packet egresses on. Now writes all 4.
 *
 * See H3600/stock_state/FINDINGS_2026-05-21.md for the dump. */
#define TM_INSTANCE_STRIDE 0x400
/* Stock dump shows master config 0x140 in 16 instances but stock plat
 * module's pon_tm_int_init writes ONLY to instance 0's tm_base+0x104.
 * Reverted to 4 — bumping to 16 caused silent hang after FPGA IRQ enable
 * during 2026-05-24 test. The per-instance state in dump may come from
 * HW mirroring, not explicit writes. */
#define TM_NUM_INSTANCES   4
static void zx_tm_pre_init(struct zx_eth *e)
{
	int inst;
	for (inst = 0; inst < TM_NUM_INSTANCES; inst++) {
		u32 base = inst * TM_INSTANCE_STRIDE;
		tm_write(e, base + 0x000, 0x00000140);	/* master config */
		tm_write(e, base + 0x004, 0x00000010);
		tm_write(e, base + 0x104, 0xfffffffc);	/* IRQ mask, bits 0,1 unmasked */
		tm_write(e, base + 0x124, 0x03ffffff);
		tm_write(e, base + 0x12c, 0x00001fff);	/* IRQ enable mask */
		tm_write(e, base + 0x134, 0x001fffff);
	}

	/* Legacy/extra (not in stock per-instance pattern but in our prior code) */
	tm_write(e, 0x128, 0x1FFF);
	tm_write(e, 0x130, 0x1FFFFF);
}

/* RED queue config — equivalent of stock plat-zxylzb red_set_queue_cfg.
 * Decoded from disassembly: poll TM[+0x4018] bit 0 for idle (up to 20 retries),
 * then commit q_idx|(type<<22) at TM[+0x4014] and write 4 cfg words at +0x401c/
 * +0x4020/+0x4024/+0x4028. */
static int zx_red_set_queue_cfg(struct zx_eth *e, u16 q_idx, u32 type,
				u32 w0, u32 w1, u32 w2, u32 w3)
{
	int retries;
	for (retries = 0; retries < 20; retries++)
		if (tm_read(e, 0x4018) & 1)
			break;
	if (retries == 20)
		return -EBUSY;
	tm_write(e, 0x4014, (u32)q_idx | (type << 22));
	tm_write(e, 0x4028, w3);
	tm_write(e, 0x4024, w2);
	tm_write(e, 0x4020, w1);
	tm_write(e, 0x401c, w0);
	return 0;
}

/* pon_tm_red_init equivalent — 4 loops configuring 1168 RED-queue slots.
 * Stock calls this from tm_pon_tm_init BEFORE pon_tm_dma_init/bmu_init.
 * Hypothesis: without these queue configs HW receives packets via BMU but
 * never fires the RX/TX-done bits on TM[+0x100] bits 0/1 → no GIC line 68
 * IRQ → kernel never sees RX. */
static void zx_tm_red_init(struct zx_eth *e)
{
	int q, fail = 0;

	/* Loop 1: q=0..15, type=0, cfg={0x400, 0, 0, 0} */
	for (q = 0; q < 16; q++)
		if (zx_red_set_queue_cfg(e, q, 0, 0x400, 0, 0, 0))
			fail++;
	/* Loop 2: q=16..399, type=0, cfg={0x00800400, 0, 0, 0} */
	for (q = 16; q < 400; q++)
		if (zx_red_set_queue_cfg(e, q, 0, 0x00800400, 0, 0, 0))
			fail++;
	/* Loop 3: q=0..383, type=2, cfg={0x00200020, 0, 0, 0} */
	for (q = 0; q < 384; q++)
		if (zx_red_set_queue_cfg(e, q, 2, 0x00200020, 0, 0, 0))
			fail++;
	/* Loop 4: q=0..383, type=4, cfg={0xff803fff, 0x0100ff80, 0x00100200, 0x20} */
	for (q = 0; q < 384; q++)
		if (zx_red_set_queue_cfg(e, q, 4, 0xff803fff, 0x0100ff80, 0x00100200, 0x20))
			fail++;
	dev_info(e->dev, "TM RED init: %d failed of 1168 queue configs (busy timeout)\n", fail);
}

/* pon_pp_ctrl_init equivalent — 2 writes + 52ms delay.
 * Stock calls this BEFORE pon_pp_brg_init. The write to pp[0] = 2 may
 * be a trigger that starts PP processing (not just state). */
static void zx_pp_ctrl_init(struct zx_eth *e)
{
	void __iomem *pp = e->fpga_base + 0x380000;
	writel(0x01070104, pp + 0x28);
	writel(0x00000002, pp + 0x00);
	msleep(52);
	dev_info(e->dev, "PP ctrl init: pp[0x28]=0x01070104 pp[0]=2 + 52ms delay\n");
}

/* pon_pp_brg_init equivalent — initializes the PP bridge so CPU TX egresses
 * to UNI ports. Without this, mainline TX never reaches the wire (driver
 * counter increments but no packets seen on host tcpdump).
 * 13 fixed register writes to pp_base = fpga_base + 0x380000. */
static void zx_pp_brg_init(struct zx_eth *e)
{
	void __iomem *pp = e->fpga_base + 0x380000;
	writel(0x020000ff, pp + 0x8004);
	writel(0xff5555ff, pp + 0x8340);
	writel(0x0000001e, pp + 0x8344);
	writel(0x0000001f, pp + 0x8380);
	writel(0xaaaaaaaa, pp + 0x863c);
	writel(0x000000ff, pp + 0x81c0);
	writel(0x00005555, pp + 0x81c4);
	writel(0x0013f434, pp + 0x8188);
	writel(0x000000ff, pp + 0x82c0);
	writel(0x0000ffff, pp + 0x8300);
	writel(0x020000ff, pp + 0x8304);
	writel(0xfffffffa, pp + 0x8050);
	writel(0x0000ff00, pp + 0x8008);

	/* pon_pp_add_port_to_vlan loop: vlan 0 + 1, port 0..7, action=3.
	 * brg_ram_set with ram_id=4: poll pp[+0x8018] for idle, then write
	 * (vlan | 4<<22) to pp[+0x8014], write 4 words at +0x801c/+0x8020/
	 * +0x8024/+0x8028. We then modify word[0] (=offset +0x801c) to:
	 *   val |= 1  (enable bit)
	 *   val &= ~(3 << (port*2 + 1))
	 *   val |= (3 << (port*2 + 1))    [since action_type=3]
	 * For vlan=0,port=0: set bits 1-2 → val |= 0x6
	 * For vlan=0,port=1: set bits 3-4 → val |= 0x18
	 * ... pattern: bits (port*2+1) and (port*2+2) = action=3
	 * For 8 ports total: val ends up = 1 | 0x6|0x18|0x60|0x180|0x600|0x1800|0x6000|0x18000 = 0x1FFFF
	 * (= bit 0 + bits 1..16)
	 * Same for vlan=1.
	 *
	 * Since we don't have brg_ram_get to read prior values, do an
	 * approximate "set vlan 0 and 1 entries to 0x1FFFF" via brg_ram_set. */
	{
		int vlan;
		for (vlan = 0; vlan <= 1; vlan++) {
			int retries;
			for (retries = 0; retries < 50; retries++)
				if (readl(pp + 0x8018) & 1)
					break;
			if (retries == 50) {
				dev_warn(e->dev, "PP brg_ram_set vlan=%d: not ready\n", vlan);
				break;
			}
			writel(((u32)vlan) | (4u << 22), pp + 0x8014);
			writel(0x1FFFF, pp + 0x801c);	/* word 0 = enable + all 8 ports action=3 */
			writel(0x00000000, pp + 0x8020);	/* word 1 */
			writel(0x00000000, pp + 0x8024);	/* word 2 */
			writel(0x00000000, pp + 0x8028);	/* word 3 */
		}
	}

	/* pon_pp_port_isolate(6, 0xdf) and (7, 0xdf): pp[0x83c0 + port*4] |= 0xdf */
	writel(readl(pp + 0x83d8) | 0xdf, pp + 0x83d8);	/* port 6 */
	writel(readl(pp + 0x83dc) | 0xdf, pp + 0x83dc);	/* port 7 */

	dev_info(e->dev, "PP bridge init: 13 regs + VLAN0/1 + port6/7 isolate done\n");
}

/* Post-BMU setup (tm_pon_tm_init between bmu_init and pon_tm_net_init).
 *
 * Stock dump 2026-05-21 showed per-instance desc base registers at
 * offsets +0xE8/+0xEC/+0xF0/+0xF4/+0xF8 (5 of them) in ALL 4 TM instances.
 * Stock values per instance (identical across all 4):
 *   +0xE8 0x4E700000   +0xEC 0x4E710000   +0xF0 0x4FF1F000  (TX desc)
 *   +0xF4 0x4EC20000   +0xF8 0x4FE20000
 * These are 5 distinct buffer pool base addresses. We only have one rxdesc
 * buffer, so program +0xF0 with our address in all 4 instances. The other
 * 4 (+0xE8/+0xEC/+0xF4/+0xF8) we don't have buffers for; the values stock
 * uses suggest jumbo BP / additional descriptor regions. Leave NULL for now
 * unless TX needs them.
 *
 * BP_SIZE +0xFC = 0x28000900 (= BP_SIZE 0x900 in low 16, mode 0x2800 in
 * high 16) — set per-instance in all 4. */
static void zx_tm_post_bmu(struct zx_eth *e)
{
	int inst;
	for (inst = 0; inst < TM_NUM_INSTANCES; inst++) {
		u32 base = inst * TM_INSTANCE_STRIDE;
		/* Descriptor base address — only one buffer pool, use same for all instances. */
		tm_write(e, base + 0xF0, e->rxdesc_dma);
		/* BP_SIZE config matches stock per-instance */
		tm_write(e, base + 0xFC, 0x28000900);
	}
	/* CANARY: write distinct pattern at rxdesc_cpu to detect HW writes.
	 * After traffic, if any word changes from 0xDEAD0000+n → HW wrote there. */
	{
		u32 *d = (u32 *)e->rxdesc_cpu;
		int i;
		for (i = 0; i < 1024; i++)
			d[i] = 0xDEAD0000u | (u32)i;
		dma_wmb();
		dev_info(e->dev, "rxdesc canaries planted at %pad (TM[0xF0]=%#x, first w[0]=%#x)\n",
			 &e->rxdesc_dma, tm_read(e, 0xF0), d[0]);
	}
	tm_write(e, 0xC008, 0);
}

/* pon_tm_dma_init equivalent — values from stock_eth.bin live dump. */
static void zx_tm_dma_init(struct zx_eth *e)
{
	tm_write(e, TM_REG_DMA_CTRL,       0x003f6564);	/* stock: 0x3f6564, was OR 0x2f0000 */
	tm_write(e, 0x10004,               0x0000007f);	/* stock */
	tm_write(e, 0x10008,               0x00002001);	/* stock */
	tm_write(e, 0x10018,               0x00000001);	/* stock */
	tm_write(e, TM_REG_DMA_REG28,      1);
	tm_write(e, TM_REG_DMA_REG2C,      1);
	tm_write(e, TM_REG_DMA_TIMEOUT,    50000);
	tm_write(e, TM_REG_DMA_REG34,      0x40);
	tm_write(e, 0x10038,               0x00010001);	/* stock */
	tm_write(e, TM_REG_DMA_REG20,      0x20);
	tm_write(e, TM_REG_DMA_REG24,      0x20);
	/* TX desc regions — UP ring is our real txdesc, DN unused (no PON) */
	tm_write(e, TM_REG_DMA_TX_UP_BASE, e->txdesc_dma);
	tm_write(e, TM_REG_DMA_TX_DN_BASE, e->txdesc_dma);
	tm_write(e, TM_REG_DMA_REG388,     0x131217);
	tm_write(e, TM_REG_DMA_REG3C,      0x400040);

	/* TM SCH/RED + per-queue templates (0x10140-0x101cc) from stock dump.
	 * Without these the TM kick is accepted but packets aren't processed
	 * onward to PP. The 0x0ac90ac9 at 0x10140 mirrors the TX cmd byte 0xc9. */
	tm_write(e, 0x10140, 0x0ac90ac9);
	tm_write(e, 0x10148, 0x00000a0a);
	tm_write(e, 0x1014c, 0xf4f40000);
	tm_write(e, 0x10150, 0x0000c8c8);
	tm_write(e, 0x10158, 0x00001c84);
	tm_write(e, 0x10160, 0x2e002e00);
	tm_write(e, 0x10170, 0x0000002e);
	tm_write(e, 0x10180, 0x00008400);
	tm_write(e, 0x10184, 0x000a0000);
	tm_write(e, 0x10188, 0x00f40000);
	tm_write(e, 0x1018c, 0x000000cb);
	tm_write(e, 0x10194, 0x00100c00);
	tm_write(e, 0x10198, 0x32222222);
	tm_write(e, 0x1019c, 0x00020002);
	tm_write(e, 0x101a4, 0x04000000);
	tm_write(e, 0x101a8, 0x40000000);
	tm_write(e, 0x101b0, 0x40000000);
	tm_write(e, 0x101c0, 0x006001a8);
	tm_write(e, 0x101c4, 0x504e8000);
	tm_write(e, 0x101c8, 0x10042002);
	tm_write(e, 0x101cc, 0x5f0d2190);

	/* Per-queue cmd templates (0x10280-0x102bc) — 8 queues × 2 entries. */
	tm_write(e, 0x10280, 0x00008010);
	tm_write(e, 0x10284, 0x00020080);
	tm_write(e, 0x10288, 0x00020036);
	tm_write(e, 0x1028c, 0x00008010);
	tm_write(e, 0x10290, 0x00020080);
	tm_write(e, 0x10294, 0x00020016);
	tm_write(e, 0x10298, 0x00008010);
	tm_write(e, 0x1029c, 0x00020080);
	tm_write(e, 0x102a0, 0x00020046);
	tm_write(e, 0x102a4, 0x0002002e);
	tm_write(e, 0x102a8, 0x00008010);
	tm_write(e, 0x102ac, 0x0002002e);
	tm_write(e, 0x102b0, 0x00008010);
	tm_write(e, 0x102b4, 0x0002002e);
	tm_write(e, 0x102b8, 0x00008010);
	tm_write(e, 0x102bc, 0x0002002e);

	/* TM[0x4xxx] queue/RX-ACK config from stock dump — never written by us.
	 * 0x4014/0x4018 look like RX queue enable+config. 0x4080+ are stats but
	 * 0x4040=port mask and 0x4068=ACK control are gating. */
	tm_write(e, 0x4004, 0x000000de);
	tm_write(e, 0x4014, 0x0100017f);
	tm_write(e, 0x4018, 0x00000001);
	tm_write(e, 0x401c, 0xff803fff);
	tm_write(e, 0x4020, 0x0100ff80);
	tm_write(e, 0x4024, 0x00100200);
	tm_write(e, 0x4028, 0x00000020);
	tm_write(e, 0x4040, 0x000003ff);
	tm_write(e, 0x4068, 0x0000001b);
	tm_write(e, 0x4074, 0x00003fff);

	/* SCH (scheduler) globals at TM[0x14000+] — RE'd via SchRegTable + stock dump.
	 * tm[0x14000] = 0x3d7 is the per-port scheduler ENABLE mask (9-bit, ports
	 * 0,1,2,4,6,7,8,9 enabled). Without this, TM dispatches but PP never
	 * receives because the scheduler doesn't run. CRITICAL for TX→PP handoff. */
	tm_write(e, 0x14000, 0x000003d7);	/* per-port SCH enable mask */
	tm_write(e, 0x14004, 0x0d1cef00);
	tm_write(e, 0x14014, 0x03c00006);
	tm_write(e, 0x14018, 0x00000001);	/* SCH global enable? */
	tm_write(e, 0x1401c, 0x0003e800);
	tm_write(e, 0x14024, 0x00000014);
	tm_write(e, 0x14028, 0x00001869);
	tm_write(e, 0x14040, 0x00000249);

	/* QMG (queue manager) at TM[0xC000+] — per QmgRegTable + stock dump */
	tm_write(e, 0xC000, 0x01f40fa0);
	tm_write(e, 0xC004, 0x00000002);
	tm_write(e, 0xC00C, 0x000003ff);
	tm_write(e, 0xC010, 0x00000faa);
	tm_write(e, 0xC02C, 0x00001112);
	tm_write(e, 0xC044, 0x000004f4);
	tm_write(e, 0xC060, 0x0000052e);

	dev_info(e->dev, "TM DMA init: ctrl=%#x, timeout=%u, sch[0]=%#x\n",
		 tm_read(e, TM_REG_DMA_CTRL), tm_read(e, TM_REG_DMA_TIMEOUT),
		 tm_read(e, 0x14000));
}

/* soft_release_rx_desc — ACK consumed RX descriptors to HW (mirrors stock).
 * Stock: tm[0x4068] = (rsn<<14) | (count<<4) | qid | (sop<<3); tm[0x4064] = 1
 * sop=1 for "start of packet" descs (single-frag packets), sop=0 for cont. */
static void zx_tm_release_rx_desc_raw(struct zx_eth *e, u8 q, u16 count, u8 sop)
{
	int t = 100;
	while (t-- && (tm_read(e, 0x4064) & 1))
		udelay(2);
	if (t < 0) {
		dev_warn_ratelimited(e->dev, "TM release_rx_desc not ready\n");
		return;
	}
	tm_write(e, 0x4068, (1u << 14) | ((u32)count << 4) | (u32)q | ((u32)sop << 3));
	tm_write(e, 0x4064, 1);
}

static void zx_tm_release_rx_desc(struct zx_eth *e, u8 q, u16 count)
{
	/* For single-buffer packets, all descs are SOPs (sop=1).
	 * Stock would also do soft_release_rx_desc(1, q, 0, 0) but that's a no-op. */
	zx_tm_release_rx_desc_raw(e, q, count, 1);
}

/* NAPI poll — based on pon_tm_net_poll RE, simplified for first iteration */
/* RX checkpoint logging — only first N polls and only when pending found */
#define RXCP(e, stage, fmt, ...) do { \
	if ((e)->tm_napi_count < 20) \
		pr_emerg("[ZXETH/RX poll#%u CP%d] " fmt "\n", \
			 (e)->tm_napi_count, stage, ##__VA_ARGS__); \
} while (0)

static int zx_tm_napi_poll(struct napi_struct *napi, int budget)
{
	struct zx_eth *e = container_of(napi, struct zx_eth, tm_napi);
	int done = 0;
	int q;

	e->tm_napi_count++;
	RXCP(e, 1, "enter budget=%d tm_irq_count=%u tm_rx_count=%u",
	     budget, e->tm_irq_count, e->tm_rx_count);

	/* Check each of 8 RX queues for pending descriptors */
	for (q = 0; q < TM_NUM_RX_QUEUES && done < budget; q++) {
		u32 status = tm_read(e, TM_RX_QCNT_BASE + q * 4);
		u32 pending = status & 0xFFFF;	/* low 16 = pending */
		u32 take, n, ack = 0;

		if (!pending) {
			if (e->tm_napi_count < 5 && q == 0)
				RXCP(e, 2, "q=%d no pending (raw=%#x)", q, status);
			continue;
		}
		RXCP(e, 3, "q=%d pending=%u (raw status=%#x)", q, pending, status);

		take = min_t(u32, pending, (u32)(budget - done));
		take = min_t(u32, take, TM_RX_DESC_PER_Q);

		/* RX desc area at rxdesc_cpu+0 (was +0x10000), per TM[0xF0]=rxdesc_dma fix. */
		for (n = 0; n < take; n++) {
			u32 idx = e->rx_head[q];
			u8 *desc = (u8 *)e->rxdesc_cpu +
				   (q * TM_RX_DESC_PER_Q + idx) * TM_DESC_SIZE;
			u16 len = le16_to_cpu(*(__le16 *)(desc + 12)) >> 2;
			u8 bppe_idx = desc[7] >> 1;
			RXCP(e, 4, "q=%d desc[%u] @%p: len=%u bppe=%u "
			          "raw[0..7]=%02x %02x %02x %02x %02x %02x %02x %02x",
			     q, idx, desc, len, bppe_idx,
			     desc[0], desc[1], desc[2], desc[3],
			     desc[4], desc[5], desc[6], desc[7]);

			if (len > 0 && len < 1600 && e->bp_cpu) {
				/* Compute BP buffer addr from BPPE: BP_SIZE * bppe_idx.
				 * HW prepends a 16-byte metadata header before the actual
				 * ethernet frame (diag dump 2026-05-24 showed bytes 0-15
				 * are zeros, eth frame starts at +0x10). */
				const u8 *bp_buf = (const u8 *)e->bp_cpu + (u32)bppe_idx * TM_BP_SIZE;
				const u8 *src = bp_buf + 16;	/* skip HW metadata header */
				/* Phase 5: ingress port from desc[6] bits 3..7, minus 1.
				 * Per stock RE: `r2 = (desc[6] >> 3) & 0x1F; r2 -= 1; pkt[180] = r2`.
				 * This is the UNI/PON port the packet arrived on. */
				int ingress_port = ((desc[6] >> 3) & 0x1F) - 1;
				if (e->sw_dev && !memcmp(src + 6, e->sw_dev->dev_addr, 6)) {
					e->tm_rx_loopback_drops++;
					if (e->tm_rx_loopback_drops <= 5)
						dev_info(e->dev, "LOOPBACK drop #%u src=%pM dst=%pM ethertype=%04x len=%u ingress=%d\n",
							 e->tm_rx_loopback_drops, src + 6, src,
							 ntohs(*(__be16*)(src + 12)), len, ingress_port);
				} else {
					struct sk_buff *skb = netdev_alloc_skb(e->sw_dev, len + 64);
					if (skb) {
						skb_reserve(skb, 32);
						memcpy(skb_put(skb, len), src, len);
						skb->protocol = eth_type_trans(skb, e->sw_dev);
						e->sw_dev->stats.rx_packets++;
						e->sw_dev->stats.rx_bytes += len;
						netif_receive_skb(skb);
						e->tm_rx_count++;
						if (e->tm_rx_count <= 10) {
							dev_info(e->dev, "TM RX q=%d idx=%u len=%u bppe=%u "
								 "src=%pM dst=%pM ethertype=%04x ingress=%d delivered\n",
								 q, idx, len, bppe_idx,
								 src + 6, src, ntohs(*(__be16*)(src + 12)),
								 ingress_port);
						}
						/* Phase 5: dynamic FDB learning. If src MAC is unicast
						 * (not multicast bit) AND we extracted a valid ingress
						 * port (0..7), register it in the switch FDB so
						 * subsequent unicast TX to this MAC routes correctly.
						 * Only do this once per MAC — track via simple table. */
						if (ingress_port >= 0 && ingress_port < 8 &&
						    (src[6] & 1) == 0 /* unicast src */) {
							/* Hash this MAC into a small "already learned"
							 * set to avoid re-adding. Use last byte as crude
							 * dedup key. */
							u8 key = src[11] & 0x7f;
							if (!(e->fdb_learned[key >> 3] & (1u << (key & 7)))) {
								e->fdb_learned[key >> 3] |= (1u << (key & 7));
								int rc = zx_fdb_add(e, src + 6, 0, ingress_port);
								if (e->tm_rx_count <= 30)
									dev_info(e->dev, "FDB learn %pM → port=%d rc=%d\n",
										 src + 6, ingress_port, rc);
							}
						}
					}
				}
			}
			e->rx_head[q] = (idx + 1) & (TM_RX_DESC_PER_Q - 1);
			done++;
			ack++;
		}

		/* ACK to HW so pending count decrements (stock: soft_release_rx_desc) */
		if (ack)
			zx_tm_release_rx_desc(e, (u8)q, (u16)ack);
	}

	if (done < budget) {
		napi_complete_done(napi, done);
		/* Re-arm: CLEAR mask bits to re-enable IRQs (1=masked semantics) */
		tm_and(e, TM_REG_IRQ_MASK, ~(u32)TM_IRQ_ARM_BITS);
	}
	return done;
}

/* TM IRQ handler — mirrors zx_pon_tm_int: only schedule NAPI if real bits pending */
static irqreturn_t zx_tm_irq(int irq, void *dev_id)
{
	struct zx_eth *e = dev_id;
	u32 status = tm_read(e, 0x100);                 /* IRQ_STATUS */
	u32 mask   = tm_read(e, TM_REG_IRQ_MASK);
	u32 pending = status & ~mask & TM_IRQ_ARM_BITS;  /* only our bits */

	if (!pending)
		return IRQ_NONE;                          /* spurious — let kernel see */

	e->tm_irq_count++;
	if (e->tm_irq_count < 5)
		pr_emerg("[ZXETH/TM_IRQ#%u] status=%#x mask=%#x pending=%#x — scheduling NAPI\n",
		         e->tm_irq_count, status, mask, pending);
	/* Mask our bits during NAPI (stock: mask |= 7) */
	tm_or(e, TM_REG_IRQ_MASK, TM_IRQ_ARM_BITS);
	napi_schedule(&e->tm_napi);
	return IRQ_HANDLED;
}

/* ============================================================
 *   "sw" netdev — what stock calls pon_tm_netdev[0]
 * ============================================================ */

static struct delayed_work zx_bmu_dump_work;
static struct zx_eth *zx_bmu_dump_eth;

static void zx_bmu_dump_fn(struct work_struct *w)
{
	struct zx_eth *e = zx_bmu_dump_eth;
	if (!e) return;
	dev_info(e->dev, "=== BMU STATE DUMP (delayed 30s after sw open) ===\n");
	dev_info(e->dev, "  tm[0x8000]=0x%08x BMU_CFG\n",  tm_read(e, 0x8000));
	dev_info(e->dev, "  tm[0x8004]=0x%08x BPP_CFG\n",  tm_read(e, 0x8004));
	dev_info(e->dev, "  tm[0x8008]=0x%08x BPP_CFG2\n", tm_read(e, 0x8008));
	dev_info(e->dev, "  tm[0x800c]=0x%08x SW_ALLOC_BP (result)\n", tm_read(e, 0x800c));
	dev_info(e->dev, "  tm[0x8014]=0x%08x SW_ALLOC_CFG\n", tm_read(e, 0x8014));
	dev_info(e->dev, "  tm[0x8040]=0x%08x BPPI_PTR\n",  tm_read(e, 0x8040));
	dev_info(e->dev, "  tm[0x8048]=0x%08x BPPE_PTR (pool_size<<16)\n", tm_read(e, 0x8048));
	dev_info(e->dev, "  tm[0x8058]=0x%08x POOL_SIZE_M1\n", tm_read(e, 0x8058));
	dev_info(e->dev, "  tm[0x8080]=0x%08x BPPE_BPCNT (bufs available)\n", tm_read(e, 0x8080));
	dev_info(e->dev, "  tm[0x8088]=0x%08x BPPI_BPCNT\n", tm_read(e, 0x8088));
	dev_info(e->dev, "  tm[0x8090]=0x%08x ALLOC_BPCNT (allocs done)\n", tm_read(e, 0x8090));
	dev_info(e->dev, "  tm[0x8098]=0x%08x RLS_BPCNT\n",  tm_read(e, 0x8098));
	dev_info(e->dev, "  tm[0x80dc]=0x%08x BP_STAT\n",    tm_read(e, 0x80dc));
	dev_info(e->dev, "  tm_tx_count=%u  tm_tx_dropped=%u\n",
		 e->tm_tx_count, e->tm_tx_dropped);
}

static int zx_sw_open(struct net_device *ndev)
{
	struct zx_eth *e = *(struct zx_eth **)netdev_priv(ndev);

	netdev_info(ndev, "sw open\n");
	napi_enable(&e->tm_napi);
	/* Unmask TM IRQs: CLEAR bits 0,1 (1=masked semantics) */
	tm_and(e, TM_REG_IRQ_MASK, ~(u32)TM_IRQ_ARM_BITS);
	netdev_info(ndev, "sw open: TM IRQ_MASK now 0x%08x (was 0xFFFFFFFF)\n",
		    tm_read(e, TM_REG_IRQ_MASK));
	netif_carrier_on(ndev);
	netif_start_queue(ndev);

	/* Schedule a BMU state dump 30s from now — by then kernel printk
	 * is calm and our dev_info messages will reliably reach UART. */
	zx_bmu_dump_eth = e;
	INIT_DELAYED_WORK(&zx_bmu_dump_work, zx_bmu_dump_fn);
	schedule_delayed_work(&zx_bmu_dump_work, msecs_to_jiffies(30000));

	return 0;
}

static int zx_sw_stop(struct net_device *ndev)
{
	struct zx_eth *e = *(struct zx_eth **)netdev_priv(ndev);

	netif_stop_queue(ndev);
	netif_carrier_off(ndev);
	/* Mask all TM IRQs (1=masked) before disabling NAPI */
	tm_write(e, TM_REG_IRQ_MASK, 0xFFFFFFFF);
	napi_disable(&e->tm_napi);
	netdev_info(ndev, "sw stop\n");
	return 0;
}

/* Raw UART debug — bypass kernel console (which hangs after ~30s of init noise).
 * Direct PL011 DR write at 0x94404004 (ZTE shifted +4 offset). One byte at a time.
 * Use sparingly — only key markers, NOT for every packet. */
static void __iomem *zx_dbg_uart;
static inline void zx_dbg_uart_init(void)
{
	if (!zx_dbg_uart)
		zx_dbg_uart = ioremap(0x94404000, 0x40);
}
static inline void zx_dbg_putc(char c)
{
	/* Wait for PL011 TX FIFO not full (ZTE FR @ +0x1C, TXFF bit 5).
	 * Blocking write — reliable even when kernel printk is hammering UART. */
	if (!zx_dbg_uart) return;
	while (__raw_readl(zx_dbg_uart + 0x1C) & (1 << 5))
		cpu_relax();
	__raw_writeb(c, zx_dbg_uart + 4);
}
static inline void zx_dbg_putn(u32 n)
{
	char buf[16];
	int i = 0;
	if (n == 0) { zx_dbg_putc('0'); return; }
	while (n > 0) { buf[i++] = '0' + (n % 10); n /= 10; }
	while (i--) zx_dbg_putc(buf[i]);
}
static inline void zx_dbg_puts(const char *s)
{
	while (*s) zx_dbg_putc(*s++);
}
static inline void zx_dbg_puthex(u32 n)
{
	int i;
	const char *hx = "0123456789abcdef";
	for (i = 28; i >= 0; i -= 4) zx_dbg_putc(hx[(n >> i) & 0xf]);
}

/* (legacy stubs — no longer used but keep API for now) */
static inline void zx_dbg_write(u32 off, u32 val) {}
static inline void zx_dbg_inc(u32 off) {}

/* BMU alloc — mirror of pon_tm_bmu_alloc_bp.
 *  Returns bp index (0..N-1) on success, 0xFFFF on failure.
 *  Protocol (per Ghidra RE):
 *    1. set tm[0x8014] |= 1   (alloc kick)
 *    2. poll tm[0x8014] & 3 == 0 (busy/done bits)
 *    3. read tm[0x800c]; bit31 = error, bits[15:0] = bp idx
 */
/* HACK: HW BMU pool depletes (auto-consumed for RX that never feeds back).
 * Bypass BMU, cycle through our 256-entry pool manually. HW will still
 * compute packet addr = bp_dma + bp_idx*BP_SIZE which lies in our DMA region. */
static u32 zx_bmu_alloc_bp(struct zx_eth *e)
{
	static u32 cycle;
	return (cycle++) & (TM_BPPE_POOL_SIZE - 1);
}

/* zx_sw_xmit — TM TX path.
 *  Replicates stock pon_tm_data_raw_send + soft_insert_tx_1desc:
 *    1. alloc BP via BMU
 *    2. memcpy(bp_pool + BP_SIZE*bp, skb->data, len)
 *    3. fill 16-byte TX desc at txdesc_cpu[tx_head*16]
 *       - byte 0 = 0x80, byte 1 = 0xc9 (cmd/flags)
 *       - desc[2..3] = 0x10000 / 0x1000000 (lower-half pkt info)
 *       - byte 7 = (bp & 0x7f) << 1
 *       - byte 8 = (bp >> 7) & 0x7f
 *       - byte 11 = 0x20 (valid bit)
 *       - bytes 12..13 = (len & 0x3fff) | 0x100 for <64B, else len in [2:15]
 *    4. advance tx_head (wrap at 1024)
 *    5. kick HW: tm[0x10054] = 1  (upstream queue 0)
 */
/* TX checkpoint logging — gated to first N packets so we don't flood the log.
 * Use pr_emerg so it always reaches console regardless of loglevel. */
#define TXCP(e, stage, fmt, ...) do { \
	if ((e)->tm_tx_count < 5) \
		pr_emerg("[ZXETH/TX#%u CP%d:%s] " fmt "\n", \
			 (e)->tm_tx_count, stage, __func__, ##__VA_ARGS__); \
} while (0)

static netdev_tx_t zx_sw_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct zx_eth *e = *(struct zx_eth **)netdev_priv(ndev);
	unsigned long flags;
	u32 bp, len;
	u8 *bp_buf;
	u8 *desc;

	TXCP(e, 1, "enter skb=%p len=%u dev=%s tx_head=%u",
	     skb, skb->len, ndev->name, e->tx_head);

	if (!e->bp_cpu || !e->txdesc_cpu) {
		TXCP(e, -1, "DROP: bp_cpu=%p txdesc_cpu=%p", e->bp_cpu, e->txdesc_cpu);
		goto drop;
	}

	len = skb->len;
	if (len < 64) {
		if (skb_padto(skb, 64)) {
			TXCP(e, -1, "DROP: padto failed (orig_len=%u)", skb->len);
			goto drop_noskb;
		}
		len = 64;
	}
	if (len > TM_BP_SIZE) {
		TXCP(e, -1, "DROP: len %u > BP_SIZE %u", len, TM_BP_SIZE);
		goto drop;
	}
	TXCP(e, 2, "size_ok len=%u (skb->len was %u)", len, skb->len);

	spin_lock_irqsave(&e->tm_tx_lock, flags);

	bp = zx_bmu_alloc_bp(e);
	if (bp == 0xFFFF) {
		spin_unlock_irqrestore(&e->tm_tx_lock, flags);
		/* First failure: emit ONE clean diagnostic via kernel printk */
		if (e->tm_tx_dropped == 0) {
			pr_emerg("[ZXETH] BMU alloc FAIL #1: 8000=%#x 8014=%#x "
				 "800c=%#x 8048=%#x 8058=%#x 8080=%#x 8090=%#x\n",
				 tm_read(e, 0x8000), tm_read(e, 0x8014),
				 tm_read(e, 0x800c), tm_read(e, 0x8048),
				 tm_read(e, 0x8058), tm_read(e, 0x8080),
				 tm_read(e, 0x8090));
		}
		e->tm_tx_dropped++;
		goto drop;
	}
	/* First success: also emit clean line */
	if (e->tm_tx_count == 0)
		pr_emerg("[ZXETH] BMU alloc OK #1: bp=%u len=%u (8090=%#x)\n",
			 bp, len, tm_read(e, 0x8090));

	bp_buf = (u8 *)e->bp_cpu + (u32)bp * TM_BP_SIZE;
	/* TX: copy skb data to bp_buf + 0 (HW reads from start of BP).
	 * RX uses bp_buf + 16 (HW prepends 16-byte metadata) — TX is different. */
	memcpy(bp_buf, skb->data, len);
	TXCP(e, 3, "BMU alloc OK: bp=%u bp_buf=%p, copied %u bytes from skb", bp, bp_buf, len);

	desc = (u8 *)e->txdesc_cpu + e->tx_head * TM_TX_DESC_SIZE;
	memset(desc, 0, TM_TX_DESC_SIZE);
	TXCP(e, 4, "desc[%u]=%p prepared (memset done, BP_SIZE=%u)", e->tx_head, desc, TM_BP_SIZE);
	/* 2026-05-24: corrected TX desc format from RE of stock pon_tm_net_tx +
	 * pon_tm_data_raw_send. Stock writes:
	 *   desc[0]  = 0x80 (byte 0 of u32 = 0x00000080)
	 *   desc[1..3] = 0 (rest of first u32)
	 *   desc[4..7] = 0x00010000  (so desc[6]=1)
	 *   desc[8..11] = 0x01000000 INITIALLY (so desc[11]=1 = TX VALID bit),
	 *     then pon_tm_data_raw_send does bfi(len, #9, #14) preserving bit 24
	 *     and adds bp_hi at low byte.
	 *   desc[12..13] = 2 or 3 (set by caller; pon_tm_data_raw_send adds len<<2)
	 * Our old code wrote desc[11]=0x20 (bit 29) instead of 0x01 (bit 24).
	 * Bit 24 is what HW likely treats as "VALID — process this desc". */
	desc[0]  = 0x80;
	desc[1]  = 0x00;
	/* desc[2..3] encodes egress port hint: ((port+0x28) & 0x3f) << 4.
	 * Hardcoded port=0 (LAN port 0) works as proven baseline.
	 * Experiment with desc[2..3]=0 dropped tm_rx_count from 700k to 6k —
	 * port hint IS needed. Future: replace with FDB lookup of dst MAC. */
	{
		u32 port = 0;
		*(__le16 *)(desc + 2) = cpu_to_le16(((port + 0x28) & 0x3f) << 4);
	}
	*(u32 *)(desc + 4) = cpu_to_le32(0x00010000);
	*(u32 *)(desc + 8) = cpu_to_le32(((bp >> 7) & 0x7f) |
					 ((len & 0x3fff) << 9) |
					 (0x01U << 24));	/* was 0x20 — fixed to 0x01 */
	desc[7]  = (bp & 0x7f) << 1;
	/* bytes 12-13 = len encoding (parallel to bits[22:9] above) */
	if (len < 64)
		*(__le16 *)(desc + 12) = cpu_to_le16((len & 0x3fff) | 0x100);
	else
		*(__le16 *)(desc + 12) = cpu_to_le16((len & 0x3fff) << 2);

	dma_wmb();
	TXCP(e, 5, "desc[0..15]=%02x %02x %02x %02x  %02x %02x %02x %02x  "
	          "%02x %02x %02x %02x  %02x %02x %02x %02x",
	     desc[0], desc[1], desc[2], desc[3], desc[4], desc[5], desc[6], desc[7],
	     desc[8], desc[9], desc[10], desc[11], desc[12], desc[13], desc[14], desc[15]);
	e->tx_head = (e->tx_head + 1) & (TM_TX_RING_SIZE - 1);
	TXCP(e, 6, "tx_head=%u (post-incr); about to kick TM[0x10054]=1, TM[0x10064]=1", e->tx_head);

	/* Kick HW: both UP and DN queues. Empirically UP-only INCREASED
	 * duplicates to 203/5pings vs 70 with both. Dual kick keeps the
	 * 70-DUPs baseline. DUP origin is likely switch flooding the same
	 * packet to multiple ports or bouncing through CPU port. */
	tm_write(e, 0x10054, 1);	/* upstream kick */
	tm_write(e, 0x10064, 1);	/* downstream kick */
	TXCP(e, 7, "kick done; TM[0x10058]=%#x (UP cnt) TM[0x10068]=%#x (DN cnt)",
	     tm_read(e, 0x10058), tm_read(e, 0x10068));

	e->tm_tx_count++;
	ndev->stats.tx_packets++;
	ndev->stats.tx_bytes += len;
	spin_unlock_irqrestore(&e->tm_tx_lock, flags);

	if (e->tm_tx_count <= 3) {
		u32 cnt_up = tm_read(e, 0x10058);
		u32 cnt_dn = tm_read(e, 0x10068);
		void __iomem *mac0 = e->base + mac_off(0, 0);
		u32 mac0_ctrl  = readl(mac0 + 0x000);
		u32 mac0_ena   = readl(mac0 + 0x008);
		u32 mac0_cnt714 = readl(mac0 + 0x714);
		u32 mac0_cnt718 = readl(mac0 + 0x718);
		void __iomem *pp = e->base + PP_OFF;
		u32 pp_cnt714 = readl(pp + 0x714);
		u32 pp_cnt780 = readl(pp + 0x780);
		/* Tiny delay then re-read MAC counter to see if HW processed */
		udelay(200);
		pr_emerg("[ZXETH] TX#%u bp=%u len=%u  TM_UP=%#x DN=%#x  MAC0[ctrl=%#x ena=%#x 714=%#x 718=%#x]  PP[714=%#x 780=%#x]\n",
			 e->tm_tx_count, bp, len, cnt_up, cnt_dn,
			 mac0_ctrl, mac0_ena, mac0_cnt714, mac0_cnt718,
			 pp_cnt714, pp_cnt780);
		pr_emerg("[ZXETH] TX#%u +200us: MAC0[714=%#x 718=%#x]  PP[714=%#x 780=%#x]\n",
			 e->tm_tx_count,
			 readl(mac0 + 0x714), readl(mac0 + 0x718),
			 readl(pp + 0x714), readl(pp + 0x780));
	}

	dev_kfree_skb_any(skb);
	return NETDEV_TX_OK;

drop:
	dev_kfree_skb_any(skb);
drop_noskb:
	ndev->stats.tx_dropped++;
	return NETDEV_TX_OK;
}

static const struct net_device_ops zx_sw_netdev_ops = {
	.ndo_open	= zx_sw_open,
	.ndo_stop	= zx_sw_stop,
	.ndo_start_xmit	= zx_sw_xmit,
	.ndo_set_mac_address = eth_mac_addr,
	.ndo_validate_addr   = eth_validate_addr,
};

static int zx_sw_netdev_create(struct zx_eth *e)
{
	struct net_device *ndev;
	/* Match stock CPU MAC slot[0] (programmed by replay from stock_eth.bin).
	 * Switch HW routes frames with this dst MAC → CPU port. */
	u8 mac[ETH_ALEN] = { 0xf4, 0xf6, 0x47, 0x0f, 0x42, 0x64 };
	int err;

	ndev = alloc_etherdev(sizeof(struct zx_eth *));
	if (!ndev)
		return -ENOMEM;
	SET_NETDEV_DEV(ndev, e->dev);
	*(struct zx_eth **)netdev_priv(ndev) = e;
	ndev->netdev_ops = &zx_sw_netdev_ops;
	ndev->watchdog_timeo = msecs_to_jiffies(5000);
	snprintf(ndev->name, IFNAMSIZ, "sw");
	eth_hw_addr_set(ndev, mac);

	/* Stock prints `netif_napi_add() called with weight 512 on device pon`
	 * in `pon tm init` (2026-05-22 UART capture line 464). Default mainline
	 * NAPI_POLL_WEIGHT=64 is 8x lower than stock and bottlenecks bursty RX. */
	netif_napi_add_weight(ndev, &e->tm_napi, zx_tm_napi_poll, 512);

	err = register_netdev(ndev);
	if (err) {
		netif_napi_del(&e->tm_napi);
		free_netdev(ndev);
		return err;
	}
	e->sw_dev = ndev;
	netdev_info(ndev, "sw registered (MAC %pM)\n", ndev->dev_addr);
	return 0;
}

/* ============================================================
 *   Probe / remove
 * ============================================================ */

/* ============================================================
 *   Debugfs: /sys/kernel/debug/zx_eth/{stats,mem}
 *   stats = pretty-printed driver counters + key reg snapshot
 *   mem   = binary dump of the 2MB NPP region (for diff vs stock)
 * ============================================================ */
static struct dentry *zx_debugfs_root;

static int zx_stats_show(struct seq_file *s, void *_unused)
{
	struct zx_eth *e = s->private;
	u32 i;

	seq_printf(s, "=== Driver counters ===\n");
	seq_printf(s, "tm_irq_count      = %u\n", e->tm_irq_count);
	seq_printf(s, "tm_napi_count     = %u\n", e->tm_napi_count);
	seq_printf(s, "tm_rx_count       = %u\n", e->tm_rx_count);
	seq_printf(s, "tm_rx_loopback_drops = %u\n", e->tm_rx_loopback_drops);
	seq_printf(s, "tm_tx_count       = %u\n", e->tm_tx_count);
	seq_printf(s, "tm_tx_dropped     = %u\n", e->tm_tx_dropped);
	seq_printf(s, "tx_head           = %u\n", e->tx_head);
	seq_printf(s, "BMU_ALLOC_RESULT  = 0x%08x\n", tm_read(e, TM_REG_BMU_ALLOC_RESULT));
	seq_printf(s, "BMU_ALLOC_CTRL    = 0x%08x\n", tm_read(e, TM_REG_BMU_ALLOC_CTRL));
	seq_printf(s, "TM[0x10054] TX kick  = 0x%08x\n", tm_read(e, 0x10054));
	seq_printf(s, "TM[0x10058] TX count = 0x%08x\n", tm_read(e, 0x10058));
	seq_printf(s, "rx_idx            = %u\n", e->rx_idx);
	seq_printf(s, "tx_idx / tx_done  = %u / %u  pending=%d\n",
		   e->tx_idx, e->tx_done, atomic_read(&e->tx_pending));
	seq_printf(s, "rx_head[0..7]     = ");
	for (i = 0; i < 8; i++) seq_printf(s, "%u ", e->rx_head[i]);
	seq_printf(s, "\n");

	if (e->rxdesc_cpu) {
		const u32 *d = (const u32 *)e->rxdesc_cpu;
		u32 first_nz_off = 0xFFFFFFFF, nz_count = 0;
		for (i = 0; i < (0x40000/4); i++) {
			if (d[i] != (0xDEAD0000u | (u32)i)) {
				if (first_nz_off == 0xFFFFFFFF) first_nz_off = i*4;
				nz_count++;
			}
		}
		seq_printf(s, "rxdesc DIFF from canaries: %u words changed, first at offset 0x%x\n",
			   nz_count, first_nz_off);
		if (first_nz_off != 0xFFFFFFFF) {
			u32 base = first_nz_off / 4;
			seq_printf(s, "  bytes near first diff: ");
			for (i = 0; i < 8 && (base+i)*4 < 0x40000; i++)
				seq_printf(s, "[+0x%x]=0x%08x ", (base+i)*4, d[base+i]);
			seq_printf(s, "\n");
		}
	}
	if (e->bp_cpu) {
		const u32 *bp = (const u32 *)e->bp_cpu;
		u32 nz = 0;
		for (i = 0; i < (524288/4); i++) if (bp[i]) nz++;
		seq_printf(s, "bp area: %u non-zero words (size 524288B)\n", nz);
	}
	if (e->bp_cpu) {
		const u32 *bp = (const u32 *)e->bp_cpu;
		seq_printf(s, "bp[bppe=0] (first 64B of BP buffer 0): ");
		for (i = 0; i < 16; i++) seq_printf(s, "%08x ", bp[i]);
		seq_printf(s, "\n");
	}
	seq_printf(s, "Verify TM[0xF0] now = 0x%08x (expected rxdesc_dma=%pad)\n",
		   tm_read(e, 0xF0), &e->rxdesc_dma);

	seq_printf(s, "\n=== TOPCRM (clock control) — stock should match ===\n");
	if (e->topcrm) {
		seq_printf(s, "TOPCRM[0x004] = 0x%08x  (stock=0x000001fb)\n", readl(e->topcrm + 0x004));
		seq_printf(s, "TOPCRM[0x008] = 0x%08x  (stock=0x1ff7ffff)\n", readl(e->topcrm + 0x008));
		seq_printf(s, "TOPCRM[0x00c] = 0x%08x  (stock=0x005179e0)\n", readl(e->topcrm + 0x00c));
		seq_printf(s, "TOPCRM[0x010] = 0x%08x  (stock=0x0000b114)\n", readl(e->topcrm + 0x010));
		seq_printf(s, "TOPCRM[0x014] = 0x%08x  (stock=0xcffffbf7)\n", readl(e->topcrm + 0x014));
		seq_printf(s, "TOPCRM[0x048] = 0x%08x  (stock=0x0ffedfff)\n", readl(e->topcrm + 0x048));
		seq_printf(s, "TOPCRM[0x04c] = 0x%08x  (stock=0x0003cfff)\n", readl(e->topcrm + 0x04c));
	}

	seq_printf(s, "\n=== TM regs ===\n");
	seq_printf(s, "TM[0x0100] IRQ_STATUS       = 0x%08x  (bits 0,1 are RX/TX pending)\n", tm_read(e, 0x100));
	seq_printf(s, "TM[0x0104] IRQ_MASK         = 0x%08x\n", tm_read(e, TM_REG_IRQ_MASK));
	seq_printf(s, "TM[0x0124] (queue enable?)  = 0x%08x\n", tm_read(e, 0x124));
	seq_printf(s, "TM[0x012C]                  = 0x%08x\n", tm_read(e, 0x12C));
	seq_printf(s, "TM[0x0134]                  = 0x%08x\n", tm_read(e, 0x134));
	seq_printf(s, "TM[0x8000] BMU_INIT         = 0x%08x\n", tm_read(e, TM_REG_BMU_INIT));
	seq_printf(s, "TM[0x8004] BMU_CTRL         = 0x%08x\n", tm_read(e, TM_REG_BMU_CTRL));
	seq_printf(s, "TM[0x8008] BMU_CTRL2        = 0x%08x\n", tm_read(e, TM_REG_BMU_CTRL2));
	seq_printf(s, "TM[0x800C] BMU_ALLOC_RESULT = 0x%08x\n", tm_read(e, TM_REG_BMU_ALLOC_RESULT));
	seq_printf(s, "TM[0x10000] DMA_CTRL        = 0x%08x\n", tm_read(e, TM_REG_DMA_CTRL));
	seq_printf(s, "TM[0x10058] DMA_DESC_CNT_UP = 0x%08x\n", tm_read(e, TM_REG_DMA_DESC_CNT_UP));
	seq_printf(s, "TM[0x10068] DMA_DESC_CNT_DN = 0x%08x\n", tm_read(e, TM_REG_DMA_DESC_CNT_DN));
	seq_printf(s, "TM[0x10030] DMA_TIMEOUT     = 0x%08x\n", tm_read(e, TM_REG_DMA_TIMEOUT));
	seq_printf(s, "\n=== Per-queue RX desc counts (TM[0x10100+q*4]) ===\n");
	for (i = 0; i < 8; i++) {
		u32 v = tm_read(e, 0x10100 + i * 4);
		seq_printf(s, "  q[%d] TM[0x%05x] = 0x%08x  (low16=avail, high16=??)\n",
			   i, 0x10100 + i * 4, v);
	}

	seq_printf(s, "\n=== PP regs ===\n");
	seq_printf(s, "PP[0x2c] CPU_FWD            = 0x%08x  (stock=0x00000106)\n",
		   readl(e->base + PP_OFF + PP_REG_CPU_FWD));
	seq_printf(s, "PP[0x04]                    = 0x%08x  (stock=0x02abfc8d)\n", readl(e->base + PP_OFF + 0x04));
	seq_printf(s, "PP[0x24]                    = 0x%08x  (stock=0x00000106)\n", readl(e->base + PP_OFF + 0x24));
	seq_printf(s, "PP[0x28]                    = 0x%08x  (stock=0x01070104)\n", readl(e->base + PP_OFF + 0x28));
	seq_printf(s, "PP[0x30]                    = 0x%08x  (stock=0x00000101)\n", readl(e->base + PP_OFF + 0x30));
	seq_printf(s, "PP[0x34]                    = 0x%08x  (stock=0x00010001)\n", readl(e->base + PP_OFF + 0x34));
	seq_printf(s, "PP[0x3c]                    = 0x%08x  (stock=0x00000106)\n", readl(e->base + PP_OFF + 0x3c));
	seq_printf(s, "PP[0x40]                    = 0x%08x  (stock=0x01030101)\n", readl(e->base + PP_OFF + 0x40));

	seq_printf(s, "\n=== IDM regs ===\n");
	seq_printf(s, "IDM[0x8000] CTRL            = 0x%08x\n", readl(e->base + IDM_REG_CONTROL));
	seq_printf(s, "IDM[0x8020] IRQ_STATUS      = 0x%08x\n", readl(e->base + IDM_REG_IRQ_STATUS));
	seq_printf(s, "IDM[0x8024] IRQ_MASK        = 0x%08x\n", readl(e->base + IDM_REG_IRQ_MASK));
	seq_printf(s, "IDM[0x8044] TX_STATUS       = 0x%08x\n", readl(e->base + IDM_REG_TX_STATUS));
	seq_printf(s, "IDM[0x804C] RX_PENDING      = 0x%08x  (low16=count, stock reads here)\n",
		   readl(e->base + 0x804C));
	seq_printf(s, "IDM[0x8004] TX_DESC_BASE    = 0x%08x\n", readl(e->base + 0x8004));
	seq_printf(s, "IDM[0x8008] RX_DESC_BASE    = 0x%08x\n", readl(e->base + 0x8008));

	seq_printf(s, "\n=== Per-port MAC[i] @ (i+1)*0x40000, first 64 bytes ===\n");
	for (i = 0; i < 5; i++) {
		u32 base = (i + 1) * MAC_STRIDE;
		u32 ctrl = readl(e->base + base + MAC_REG_CONTROL);
		u32 mask = readl(e->base + base + MAC_REG_IRQ_MASK);
		u32 en   = readl(e->base + base + MAC_REG_ENABLE);
		seq_printf(s, "MAC[%u] @0x%05x ctrl=%08x mask=%08x en=%08x\n",
			   i, base, ctrl, mask, en);
	}

	return 0;
}

static int zx_stats_open(struct inode *inode, struct file *file)
{
	return single_open(file, zx_stats_show, inode->i_private);
}

static const struct file_operations zx_stats_fops = {
	.owner   = THIS_MODULE,
	.open    = zx_stats_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = single_release,
};

/* mem: binary 2MB dump of the NPP/MAC/PP region for diff vs stock_eth.bin */
static ssize_t zx_mem_read(struct file *file, char __user *ubuf,
			   size_t count, loff_t *ppos)
{
	struct zx_eth *e = file->private_data;
	const size_t REGION = 0x200000;
	if (*ppos >= REGION) return 0;
	if (*ppos + count > REGION) count = REGION - *ppos;
	{
		void *tmp = kmalloc(count, GFP_KERNEL);
		if (!tmp) return -ENOMEM;
		memcpy_fromio(tmp, e->base + *ppos, count);
		if (copy_to_user(ubuf, tmp, count)) { kfree(tmp); return -EFAULT; }
		kfree(tmp);
	}
	*ppos += count;
	return count;
}

static const struct file_operations zx_mem_fops = {
	.owner = THIS_MODULE,
	.open  = simple_open,
	.read  = zx_mem_read,
	.llseek = default_llseek,
};

static void zx_debugfs_init(struct zx_eth *e)
{
	zx_debugfs_root = debugfs_create_dir("zx_eth", NULL);
	debugfs_create_file("stats", 0444, zx_debugfs_root, e, &zx_stats_fops);
	debugfs_create_file("mem",   0444, zx_debugfs_root, e, &zx_mem_fops);
	dev_info(e->dev, "debugfs ready: /sys/kernel/debug/zx_eth/{stats,mem}\n");
}

static void zx_debugfs_exit(void)
{
	debugfs_remove_recursive(zx_debugfs_root);
	zx_debugfs_root = NULL;
}

static int zx_eth_probe_port(struct zx_eth *eth, int idx)
{
	struct net_device *ndev;
	struct zx_eth_port *port;
	u8 mac[ETH_ALEN];
	int err;

	ndev = alloc_etherdev_mqs(sizeof(struct zx_eth_port *), 1, 1);
	if (!ndev)
		return -ENOMEM;

	SET_NETDEV_DEV(ndev, eth->dev);
	ndev->netdev_ops = &zx_eth_netdev_ops;
	ndev->watchdog_timeo = msecs_to_jiffies(5000);
	ndev->hw_features = NETIF_F_SG;
	snprintf(ndev->name, IFNAMSIZ, "idm%d", idx);

	port = &eth->ports[idx];
	port->netdev = ndev;
	port->eth = eth;
	port->idx = idx;
	*(struct zx_eth_port **)netdev_priv(ndev) = port;

	eth_random_addr(mac);
	mac[0] = 0x02;
	mac[5] = idx;
	eth_hw_addr_set(ndev, mac);

	err = register_netdev(ndev);
	if (err) {
		free_netdev(ndev);
		port->netdev = NULL;
		return err;
	}
	netdev_info(ndev, "registered (MAC %pM)\n", ndev->dev_addr);
	return 0;
}

static int zx_eth_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct zx_eth *eth;
	int err, i;

	eth = devm_kzalloc(dev, sizeof(*eth), GFP_KERNEL);
	if (!eth)
		return -ENOMEM;
	eth->dev = dev;
	spin_lock_init(&eth->tx_lock);

	eth->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(eth->base))
		return dev_err_probe(dev, PTR_ERR(eth->base), "ioremap NPP\n");

	eth->irq_idm = platform_get_irq_byname(pdev, "idm");
	if (eth->irq_idm < 0)
		eth->irq_idm = platform_get_irq(pdev, 0);
	eth->irq_npp = platform_get_irq_byname_optional(pdev, "npp");

	platform_set_drvdata(pdev, eth);

	/* Load replay snapshots from /lib/firmware/zx-replay/*.bin (initramfs).
	 * Soft-fail: warn but continue — useful for bring-up without all snapshots. */
	{
		const struct {
			const char *name;
			const struct firmware **fwp;
			const void **datap;
			u32 *countp;
			size_t rsize;
		} fws[] = {
			{ "zx-replay/stock.bin", &eth->fw_stock,
			  (const void **)&eth->r_stock, &eth->r_n_stock,
			  sizeof(struct zx_replay_stock) },
			{ "zx-replay/cla.bin", &eth->fw_cla,
			  (const void **)&eth->r_cla, &eth->r_n_cla,
			  sizeof(struct zx_replay_cla) },
			{ "zx-replay/pm.bin", &eth->fw_pm,
			  (const void **)&eth->r_pm, &eth->r_n_pm,
			  sizeof(struct zx_replay_pm) },
		};
		int fi;
		for (fi = 0; fi < ARRAY_SIZE(fws); fi++) {
			int rc = request_firmware(fws[fi].fwp, fws[fi].name, dev);
			if (rc) {
				dev_warn(dev, "replay %s: request_firmware=%d\n",
					 fws[fi].name, rc);
				continue;
			}
			if ((*fws[fi].fwp)->size < 8) {
				dev_warn(dev, "replay %s: too small\n", fws[fi].name);
				release_firmware(*fws[fi].fwp); *fws[fi].fwp = NULL;
				continue;
			}
			{
				const u32 *hdr = (const u32 *)(*fws[fi].fwp)->data;
				u32 magic = hdr[0], cnt = hdr[1];
				size_t expect = 8 + (size_t)cnt * fws[fi].rsize;
				if (magic != ZX_REPLAY_MAGIC ||
				    (*fws[fi].fwp)->size != expect) {
					dev_warn(dev, "replay %s: bad header (magic=%#x cnt=%u size=%zu vs %zu)\n",
						 fws[fi].name, magic, cnt,
						 (*fws[fi].fwp)->size, expect);
					release_firmware(*fws[fi].fwp); *fws[fi].fwp = NULL;
					continue;
				}
				*fws[fi].datap = (const void *)((*fws[fi].fwp)->data + 8);
				*fws[fi].countp = cnt;
				dev_info(dev, "replay %s: %u entries (%zu bytes)\n",
					 fws[fi].name, cnt, (*fws[fi].fwp)->size);
			}
		}
	}

	/* Set the DMA mask before allocating coherent buffers */
	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	if (err)
		return dev_err_probe(dev, err, "failed to set DMA mask\n");

	/* TOP_CRM clock enable for PON subsystem bits 5-8 (stock does this
	 * in zx_pon_clk_reset_init). Small dedicated ioremap. */
	eth->topcrm = devm_ioremap(dev, ZX_TOPCRM_BASE, 0x100);
	if (!eth->topcrm)
		return dev_err_probe(dev, -ENOMEM, "ioremap TOPCRM\n");
	writel(readl(eth->topcrm + TOPCRM_REG_PON_CLK) | TOPCRM_PON_CLK_BITS,
	       eth->topcrm + TOPCRM_REG_PON_CLK);
	dev_info(dev, "TOPCRM[0x0C] = %#x (PON clocks enabled)\n",
		 readl(eth->topcrm + TOPCRM_REG_PON_CLK));
	/* 2026-05-24: TOPCRM stock-match writes — Linux defaults leave many
	 * bits cleared that stock sets. Writing the exact stock values for
	 * the differing registers should enable FPGA → GIC IRQ routing. */
	writel(0x0003cfff, eth->topcrm + 0x4c);   /* was 0x000381ff */
	writel(0x1ff7ffff, eth->topcrm + 0x08);   /* was 0x10061fff — many clock-enable bits */
	dev_info(dev, "TOPCRM[0x4c]=%#x [0x08]=%#x (stock-match)\n",
		 readl(eth->topcrm + 0x4c), readl(eth->topcrm + 0x08));

	zx_pp_init(eth);
	zx_npp_init(eth);

	/* Map PON early region (0x92000000-0x921bffff = 1.5MB) — contains CLA
	 * tables, FWD configuration, etc. that switch.ko populates. */
	/* fpga_base: unified 4 MiB window covering pon + npp + idm + tm + pp,
	 * matching stock zx_ponreg.ko's `fpga_base` (virt 0xf4000000 →
	 * phys 0x92000000). Used by descriptor-table writes
	 * (zx-fpga-reg-tables.h). Overlaps with `pon_early` (first 1.75 MiB)
	 * and `base` (next 2 MiB); fine, the regions read consistently. */
	eth->fpga_base = devm_ioremap(dev, 0x92000000, 0x400000);
	if (!eth->fpga_base)
		return dev_err_probe(dev, -ENOMEM, "ioremap fpga_base failed\n");

	eth->pon_early = devm_ioremap(dev, 0x92000000, 0x1C0000);
	if (!eth->pon_early)
		return dev_err_probe(dev, -ENOMEM, "ioremap PON early\n");

	/* Init raw UART debug (bypass console — survives console hang) */
	zx_dbg_uart_init();
	if (zx_dbg_uart) {
		zx_dbg_puts("\n[zxdbg] probe OK\n");
	}

	/* Replay stock NPP/TM register state (TM/QoS/queue config + CLA tables
	 * we don't generate via init code). Empirical snapshot from running stock. */
	if (eth->r_stock) {
		u32 i, neg = 0, pos = 0;
		for (i = 0; i < eth->r_n_stock; i++) {
			s32 off = eth->r_stock[i].off;
			u32 val = eth->r_stock[i].val;
			if (off < 0) {
				writel(val, eth->pon_early + (off + 0x1C0000));
				neg++;
			} else {
				writel(val, eth->base + off);
				pos++;
			}
		}
		dev_info(dev, "replayed %u stock regs (%u PON-early + %u NPP+)\n",
			 eth->r_n_stock, neg, pos);
	} else {
		dev_warn(dev, "stock replay skipped: firmware not loaded\n");
	}

	dev_info(dev, "PP[0x2c] (CPU_FWD) = %#x, IDM[0x8000] CTRL = %#x\n",
		 readl(eth->base + PP_OFF + PP_REG_CPU_FWD),
		 readl(eth->base + IDM_REG_CONTROL));

	/* Match stock pon_pp_brg_init tail: VLAN port membership setup +
	 * isolate CPU/internal ports 6 & 7. */
	{
		int vid, port, n_ok = 0;
		for (vid = 0; vid < 2; vid++)
			for (port = 0; port < 8; port++)
				if (zx_vlan_add_port(eth, vid, port, 3) == 0)
					n_ok++;
		dev_info(dev, "VLAN setup: %d/%d port-vlan entries OK\n", n_ok, 16);
	}
	zx_port_isolate(eth, 6, 0xDF);
	zx_port_isolate(eth, 7, 0xDF);
	dev_info(dev, "isolate ports 6,7 = %#x, %#x\n",
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(6)),
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(7)));

	err = zx_idm_init(eth);
	if (err)
		return dev_err_probe(dev, err, "IDM init failed\n");

	/* netdevs — register first so napi has a real device */
	for (i = 0; i < ZX_NPORTS; i++) {
		err = zx_eth_probe_port(eth, i);
		if (err)
			goto err_unregister;
	}
	/* NAPI attached to port 0 (arbitrary). Weight 512 to match stock pon NAPI
	 * (2026-05-22 UART capture). */
	netif_napi_add_weight(eth->ports[0].netdev, &eth->napi, zx_idm_poll, 512);

	err = devm_request_irq(dev, eth->irq_idm, zx_idm_irq, 0,
			       DRV_NAME "-idm", eth);
	if (err) {
		dev_err(dev, "failed to request IDM IRQ %d: %d\n",
			eth->irq_idm, err);
		goto err_napi;
	}

	/* ===== TM subsystem (the REAL CPU↔switch path) ===== */
	eth->irq_tm = platform_get_irq_byname_optional(pdev, "tm");
	if (eth->irq_tm < 0) {
		dev_warn(dev, "no TM IRQ in DT — sw netdev disabled\n");
	} else {
		err = zx_tm_alloc_pools(eth);
		if (err) {
			dev_err(dev, "TM pools alloc failed: %d\n", err);
			goto err_napi;
		}
		/* Order: pre-init regs → DMA → BMU init → BMU enable → post BMU.
		 * Matches stock tm_pon_tm_init sequence. */
		zx_tm_pre_init(eth);
		zx_tm_red_init(eth);   /* 2026-05-24: queue config — stock does this BEFORE dma/bmu */
		zx_pp_ctrl_init(eth);  /* 2026-05-24: PP ctrl init — stock calls before brg_init */
		zx_pp_brg_init(eth);   /* 2026-05-24: PP bridge init — enables CPU TX to UNI egress */
		zx_tm_dma_init(eth);
		zx_tm_bmu_init(eth);
		zx_tm_post_bmu(eth);
		zx_tm_bmu_enable(eth);

		err = zx_sw_netdev_create(eth);
		if (err) {
			dev_err(dev, "sw netdev create failed: %d\n", err);
			zx_tm_free_pools(eth);
			goto err_napi;
		}

		err = devm_request_irq(dev, eth->irq_tm, zx_tm_irq, 0,
				       DRV_NAME "-tm", eth);
		if (err) {
			dev_err(dev, "TM IRQ request failed: %d\n", err);
			unregister_netdev(eth->sw_dev);
			free_netdev(eth->sw_dev);
			netif_napi_del(&eth->tm_napi);
			zx_tm_free_pools(eth);
			goto err_napi;
		}

		/* Register sw netdev MAC as CPU port destination — BOTH tables */
		/* Stock pp_pm RAM[12]: 4 CPU MACs (last byte M0..M3) at slots where
		 * (slot & 0xF) < 4 — i.e. 16 groups of 4 → 64 slots total.
		 * Pattern: 0..3=M0..M3, 16..19, 32..35, 48..51, ... 240..243.
		 * The 16-stride likely indexes GEMPORT/T-CONT. HW lookup hashes
		 * packet attrs → group_idx * 16, then matches M0..M3.
		 * Discovered via stock pp_pm dump (256 non-zero in 256 slots). */
		{
			u8 mac[6];
			int sl;
			for (sl = 0; sl < 256; sl++) {
				if ((sl & 0xF) >= 4) continue;  /* only first 4 of each group of 16 */
				memcpy(mac, eth->sw_dev->dev_addr, 6);
				mac[5] += (sl & 0x03);
				zx_register_cpu_mac(eth, (u8)sl, mac);
			}
		}

		/* Replay CLA ACL hash table from stock snapshot — this programs
		 * the actual "trap-to-CPU" rules that stock has at boot. */
		zx_cla_apply_replay(eth);

		/* chip_tm_init's trap_queue setup: per-protocol CPU queue routing.
		 * Overrides the blanket "qid=7" from cla_apply_replay with the
		 * stock def_ptl_pkt_map (82 entries × 7 ports). */
		zx_chip_tm_init_trap_queues(eth);

		/* Phase 4 port (2026-05-24): per-port isolate masks. Stock
		 * chip_tm_init calls tm_port_isolate_set 8 times. */
		zx_chip_tm_init_isolate(eth);

		/* Phase 4 cont: pro_action replay — the def_ptl_pkt_action
		 * table that decides which protocols get trapped to CPU.
		 * Without this, broadcasts (ARP) don't reach the netdev. */
		zx_chip_tm_init_pro_action(eth);

		/* Phase 4 IRQ enable — stock chip_tm_init calls
		 * sbrg_set_irq_en_mask(0xa) once. Per kotrace runtime capture:
		 * marker '$' fires with r0=0x0000000a during boot init (after
		 * tm_vlan_check_ena, before sbrg_set_table_sel et al).
		 * sbrg_set_irq_en_mask writes via sbragRegTable[0] which is a
		 * raw FPGA offset 0 register (the IRQ enable mask).
		 * Mainline's tm IRQ stayed at count=0 until we add this. */
		writel(0xa, eth->fpga_base + 0);
		dev_info(dev, "FPGA IRQ enable: wrote 0xa to fpga+0 (sbrg_set_irq_en_mask equiv)\n");

		/* Phase 4 BULK replay (state-replay strategy): dump of the full
		 * FPGA register window (0x92000000 + 4 MiB) captured from a
		 * STOCK boot where ping works. Replays only non-zero/non-0xff
		 * entries (25515 records). Skips known DDR-pointing registers
		 * (BMU/desc base) since stock's addresses don't match ours.
		 * Format: [magic 'ZXFP'][u32 count][u32 offset, u32 value]... */
		{
			const struct firmware *fw = NULL;
			int rfw_ret;
			dev_info(dev, "CKPT1: before request_firmware(fpga.bin)\n");
			rfw_ret = request_firmware(&fw, "zx-replay/fpga.bin", dev);
			dev_info(dev, "CKPT2: request_firmware ret=%d fw=%p size=%zu\n",
				 rfw_ret, fw, fw ? fw->size : 0);
			if (rfw_ret == 0 && fw && fw->size >= 8) {
				const u8 *p = fw->data;
				const u32 *hdr = (const u32 *)p;
				u32 cnt = hdr[1];
				size_t i, applied = 0, skipped = 0;
				if (hdr[0] != 0x5046585au /* 'ZXFP' little-endian */) {
					dev_warn(dev, "zx-replay/fpga.bin: bad magic %#x\n", hdr[0]);
				} else {
					dev_info(dev, "CKPT3: starting replay loop cnt=%u\n", cnt);
					for (i = 0; i < cnt; i++) {
						u32 off = *(const u32 *)(p + 8 + i*8);
						u32 val = *(const u32 *)(p + 12 + i*8);
						bool allow = false;
						if ((val & 0xff000000u) == 0x4e000000u) {
							skipped++;
							continue;
						}
						/* Skip TM[0x10050]=TX_UP_BASE and TM[0x10060]=TX_DN_BASE
						 * — stock values are 0x4ffdf000/0x4ffef000 (DDR), our
						 * dma_init has set them to txdesc_dma which the bulk
						 * replay would otherwise overwrite. Also skip 0x10064
						 * (TX DN KICK = 1) — spurious kick on stale stock base. */
						if (off == 0x350050 || off == 0x350060 || off == 0x350064) {
							skipped++;
							continue;
						}
						/* Skip TM[+0xF0] across 4 instances — RX desc base.
						 * Stock val 0x4ff1f000 is DDR; we set to rxdesc_dma. */
						if (off == 0x3400f0 || off == 0x3404f0 ||
						    off == 0x3408f0 || off == 0x340cf0) {
							skipped++;
							continue;
						}
						/* WHITELIST of FPGA sub-blocks known to be safe to write.
						 * Other ranges (PON, IDM, etc.) hang the AHB bus when
						 * written without prior topcrm clock-enable.  We don't
						 * need them — mainline H3600 is a router not an ONT. */
						/* 0x000000-0x040000: pon_low control regs (4 entries) */
						/* 0x040000-0x080000: secondary pon block (worked in prior tests) */
						if (off < 0x80000) allow = true;
						/* 0x1c0000-0x200000: NPP block */
						else if (off >= 0x1c0000 && off < 0x200000) allow = true;
						/* 0x340000-0x360000: TM block */
						else if (off >= 0x340000 && off < 0x360000) allow = true;
						/* 0x380000-0x3b0000: PP block */
						else if (off >= 0x380000 && off < 0x3b0000) allow = true;

						if (!allow) {
							skipped++;
							continue;
						}
						if ((i & 0xff) == 0)
							dev_info(dev, "CKPT_PRE: i=%zu off=%#x val=%#x\n", i, off, val);
						writel(val, eth->fpga_base + off);
						applied++;
					}
					dev_info(dev, "fpga.bin replay: %zu applied, %zu skipped (DDR ptrs), %u total\n",
						 applied, skipped, cnt);
				}
				release_firmware(fw);
			} else {
				dev_warn(dev, "zx-replay/fpga.bin missing/bad; bulk replay skipped (ret=%d)\n", rfw_ret);
			}
			dev_info(dev, "CKPT4: after bulk replay block\n");
		}

		/* Replay pp_pm flow_info/sub_ram from stock snapshot */
		zx_pp_pm_apply_replay(eth);

		/* CRITICAL fix 2026-05-24: bulk replay above overwrote TM[+0xF0]
		 * (the RX descriptor base address) with stock's value 0x4ff1f000
		 * which points at stock's DDR. Mainline's rxdesc_dma is in CMA at
		 * a totally different address. Re-write our value so HW writes RX
		 * to our buffer (not random kernel memory). */
		{
			int inst;
			for (inst = 0; inst < TM_NUM_INSTANCES; inst++) {
				u32 base = inst * TM_INSTANCE_STRIDE;
				tm_write(eth, base + 0xF0, eth->rxdesc_dma);
			}
			dev_info(dev, "Re-wrote TM[+0xF0] x%d instances to rxdesc_dma=%pad (was overwritten by bulk replay)\n",
				 TM_NUM_INSTANCES, &eth->rxdesc_dma);
		}
		/* CRITICAL fix 2026-05-24: bulk replay also overwrites
		 * TM[0x10050] (TX_UP_BASE) = 0x4ffdf000 and TM[0x10060] (TX_DN_BASE)
		 * = 0x4ffef000 — both stock DDR addresses. HW was reading TX desc
		 * from random kernel memory, seeing invalid descs, dropping all TX.
		 * Re-write to our txdesc_dma so HW reads our actual ring. */
		tm_write(eth, TM_REG_DMA_TX_UP_BASE, eth->txdesc_dma);
		tm_write(eth, TM_REG_DMA_TX_DN_BASE, eth->txdesc_dma);
		dev_info(dev, "Re-wrote TM[0x10050/0x10060] TX_UP/DN_BASE = txdesc_dma=%pad (was overwritten by bulk replay)\n",
			 &eth->txdesc_dma);

		dev_info(dev, "TM ready: IRQ=%d, sw netdev up, CPU MAC + CLA + pp_pm replay done\n",
			 eth->irq_tm);
	}

	/* Program FDB so switch knows which port the CPU netdevs live on.
	 * Without this, frames addressed to our MAC would be dropped/flooded
	 * by the switch. Also add broadcast to CPU so ARP works. */
	/* NO FDB adds: stock helpSpa shows port mapping 0-4=UNI, 5=PON, 6-7=WiFi.
	 * CPU is NOT a numbered port — it's a side channel via cpu_qid + da_known_cpu.
	 * Previous code added FDB → port=5 (PON), which routed CPU MAC traffic OUT
	 * THE FIBER. Stock relies on: flooding for broadcasts, da_known_cpu (via
	 * pp_pm RAM[12]) for unicasts to CPU MAC. */

	dev_info(dev, "ZX279128S ethernet ready (IRQ=%d, base=%pR, CPU_PORT=%d)\n",
		 eth->irq_idm, platform_get_resource(pdev, IORESOURCE_MEM, 0),
		 ZX_CPU_PORT);

	zx_debugfs_init(eth);
	return 0;

err_napi:
	netif_napi_del(&eth->napi);
err_unregister:
	while (--i >= 0) {
		unregister_netdev(eth->ports[i].netdev);
		free_netdev(eth->ports[i].netdev);
	}
	zx_idm_free_rx(eth);
	if (eth->desc_cpu)
		dma_free_coherent(dev, IDM_DESC_BUF_BYTES + 0x20,
				  eth->desc_cpu, eth->desc_dma);
	return err;
}

static int zx_eth_remove(struct platform_device *pdev)
{
	struct zx_eth *eth = platform_get_drvdata(pdev);
	int i;

	/* 1. Mask ALL IDM IRQs at HW (don't rely on devm_free_irq alone) */
	npp_write(eth, IDM_REG_IRQ_MASK, IDM_IRQ_ALL_MASKED);
	/* 2. Disable RX path in IDM control */
	npp_write(eth, IDM_REG_RX_ENABLE, 0);

	/* 3. Free IRQ before touching NAPI (handler won't schedule new work) */
	devm_free_irq(eth->dev, eth->irq_idm, eth);

	/* 4. If NAPI was ever enabled, disable it cleanly. Safe even if
	 * never enabled — napi_disable handles NAPI_STATE_DISABLE check. */
	if (eth->started) {
		napi_disable(&eth->napi);
		eth->started = false;
	}
	netif_napi_del(&eth->napi);

	/* 5. Unregister netdevs (this calls ndo_stop on each UP iface — our
	 *    zx_eth_stop already handles IRQ mask, but masked again above). */
	for (i = ZX_NPORTS - 1; i >= 0; i--) {
		if (eth->ports[i].netdev) {
			unregister_netdev(eth->ports[i].netdev);
			free_netdev(eth->ports[i].netdev);
		}
	}

	/* 6. Free DMA last (nothing should reference it now) */
	zx_idm_free_rx(eth);
	if (eth->desc_cpu)
		dma_free_coherent(eth->dev, IDM_DESC_BUF_BYTES + 0x20,
				  eth->desc_cpu, eth->desc_dma);

	/* 7. TM teardown — order matters! HW DMA must be quiescent before
	 *    we free its memory or the bus will hang. */
	if (eth->sw_dev) {
		/* a) Mask all TM IRQs (1=masked semantics) so handler can't re-schedule */
		tm_write(eth, TM_REG_IRQ_MASK, 0xFFFFFFFF);
		/* b) Disable BMU — stops HW from allocating new BPs */
		tm_write(eth, TM_REG_BMU_INIT, 0);
		/* c) Clear DMA control bits (stop TX/RX engines) */
		tm_write(eth, TM_REG_DMA_CTRL, 0);
		/* d) Tiny delay to let in-flight transactions complete */
		msleep(10);
		/* e) Now safe to free IRQ + NAPI + netdev */
		devm_free_irq(eth->dev, eth->irq_tm, eth);
		unregister_netdev(eth->sw_dev);
		netif_napi_del(&eth->tm_napi);
		free_netdev(eth->sw_dev);
		eth->sw_dev = NULL;
	}
	zx_tm_free_pools(eth);

	zx_debugfs_exit();

	/* 8. Release replay firmware images */
	if (eth->fw_stock) release_firmware(eth->fw_stock);
	if (eth->fw_cla)   release_firmware(eth->fw_cla);
	if (eth->fw_pm)    release_firmware(eth->fw_pm);
	return 0;
}

static const struct of_device_id zx_eth_of_match[] = {
	{ .compatible = "zte,zx279128s-eth" },
	{ }
};
MODULE_DEVICE_TABLE(of, zx_eth_of_match);

static struct platform_driver zx_eth_driver = {
	.probe		= zx_eth_probe,
	.remove		= zx_eth_remove,
	.driver = {
		.name		= DRV_NAME,
		.of_match_table	= zx_eth_of_match,
	},
};
module_platform_driver(zx_eth_driver);

MODULE_AUTHOR("H3600 mainline port");
MODULE_DESCRIPTION("ZTE ZX279128S integrated Ethernet driver (NPP+IDM+MACs)");
MODULE_LICENSE("GPL");
