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
#include <linux/of_mdio.h>
#include <linux/phy.h>
#include <linux/platform_device.h>
#include <linux/skbuff.h>
#include <linux/spinlock.h>

#include <linux/firmware.h>

#include "zx_reg_tables.h"
#include <linux/debugfs.h>
#include <linux/seq_file.h>

#include "zx-fpga-reg-tables.h"
#include "zx-pp-pro-actions.h"

/* Runtime-loaded replay snapshots (was: #include "zx279128-eth-{stock,cla,pm}-regs.h").
 * Bin files live in initramfs at /lib/firmware/zx-replay/{stock,cla,pm}.bin.
 * Each file: [u32 magic 'ZXGR'][u32 count][records...]
 */
#define ZX_REPLAY_MAGIC 0x5A584752u

/* zx_replay_stock removed — stock.bin replaced by embedded
 * zx_stock_init_table[] in zx_stock_table.h (refactor #38 Phase 3).
 * Phase 5 added per-HW-block section comments to the table.
 * Phase 6 added ZX_STOCK_<name>_{START,END,LEN} slice constants so we
 * can replay each block independently, and added zx_replay_stock_block()
 * below as the per-block helper. Future phases will replace each call
 * with a true zx_<block>_init() function that derives the values. */
#include "zx_stock_table.h"
/* Phase 8: zx_stock_init_table[] re-expressed as a stream of ops in
 * zx_stock_bursts.h — bursts of contiguous +4 writes collapse to
 * __iowrite32_copy(), short runs stay as singletons. ~2× fewer ops,
 * but more importantly: each burst can be named in the source. */
#include "zx_stock_bursts.h"
#include "zx_npp_twin_data.h"  /* Phase 9f: NPP twin-pair arrays */
/* zx_replay_cla removed — cla.bin replaced by embedded zx_cla_init_table[]
 * in zx_cla_table.h (refactor #38 Phase 1.a, commit 8a57adac2). The
 * embedded version uses struct zx_cla_entry from that header. */
/* zx_replay_pm removed — pm.bin replaced by embedded zx_pm_init_table[]
 * in zx_pm_table.h (refactor #38 Phase 2). Uses struct zx_pm_entry from
 * that header. */

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
	/* Per-ingress-port RX counter (decoded from desc[6]: (desc[6]>>3 & 0x1F)-1).
	 * Used to identify the CPU-hairpin loopback ingress port empirically.
	 * The port that spikes 1:1 with tm_tx_count IS the hairpin source — we
	 * can then drop those frames to break the DUPs amplification loop.
	 * 32 slots: ingress is a 5-bit field minus 1, so values run -1..30; we
	 * shift by +1 to index. */
	u32 tm_rx_per_ingress[32];
	/* BMU buffer-free credit (stock: allow_free_cnt) — preserved across calls.
	 * Refilled from tm[0x80dc] bits 8..13 when it hits 0. */
	u32 bmu_free_credit;
	spinlock_t bmu_free_lock;
	u32 tm_bmu_free_ok;
	u32 tm_bmu_free_fail;
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

	/* All 3 replay snapshots that used to be runtime firmware blobs are
	 * now embedded as zx_{cla,pm,stock}_init_table[] in their respective
	 * headers (refactor #38 Phase 1+2+3). No more firmware_request at
	 * driver probe. */
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
	/* 2026-05-25: write in REVERSE order (D2 first, D0 last) — D0 commits.
	 * Per stock sbrg_set_indreg_wr (decomp_all_tm.c L8422): writes 0x4e
	 * (D2) → 0x4d (D1) → 0x4c (D0). Writing D0 first commits with stale
	 * D1/D2 → entry partially written → switch silently uses bad data. */
	writel(d2, pp + PP_BRG_RAM_D2);
	writel(d1, pp + PP_BRG_RAM_D1);
	writel(d0, pp + PP_BRG_RAM_D0);
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

/* CRC-16/IBM (poly 0xA001, init 0, LSB-first) — legacy, used in other paths.
 * NOT the hash sbrg_add_mactable uses. */
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

/* sbrg_hash — match stock decomp_all_tm.c L8204 for the mode==0x3c path
 * (the path sbrg_add_mactable uses). Stock builds an 8-byte buffer from
 * {mac_low_4, mac_high_2|vlan<<16}, REVERSES it, then runs CRC-16/XMODEM
 * (poly 0x1021 MSB-first, init 0, no xorout) over the reversed 8 bytes.
 * Returns the result masked to 10 bits (0..0x3FF, the bucket index).
 *
 * This is critical: switch egress lookup uses this exact hash to find the
 * destination MAC. If we write entries with a DIFFERENT hash, lookups
 * miss → switch flood → DUPs. The original CRC-16/IBM hash put entries
 * in wrong buckets across the whole table. */
static u16 zx_sbrg_hash(const u8 *mac, u16 vlan)
{
	u8 raw[8] = {
		mac[0], mac[1], mac[2], mac[3],
		mac[4], mac[5],
		(u8)(vlan & 0xff), (u8)((vlan >> 8) & 0xff),
	};
	u8 rev[8] = {
		raw[7], raw[6], raw[5], raw[4],
		raw[3], raw[2], raw[1], raw[0],
	};
	u16 crc = 0;
	int i, j;
	for (i = 0; i < 8; i++) {
		crc ^= ((u16)rev[i]) << 8;
		for (j = 0; j < 8; j++)
			crc = (crc & 0x8000) ? (crc << 1) ^ 0x1021 : (crc << 1);
	}
	return crc & 0x3ff;
}

/* Add a static MAC entry to the FDB → switch routes frames with this dst MAC
 * to the given port.
 *
 * 2026-05-25: rewrote entry encoding to match stock sbrg_add_mactable
 * (decomp_all_tm.c L10836-L10840) instead of old (wrong) format.
 *
 * Stock 3-word format:
 *   word2 (D2) = port_id | (mac_low_4 << 8)
 *   word1 (D1) = (status<<4 & 0xf0) | (vlan>>8 & 0xf)
 *                | (smac_ctrl<<8) | (dmac_ctrl<<9)
 *   word0 (D0) = (mac_low_4 >> 24) | ((vlan & 0xfff) << 24)
 *                | ((mac_high_2 & 0xffff) << 8)
 *
 * status=0xF marks the slot as valid+static. zx_brg_ram_set now writes
 * D2→D1→D0 (D0 last commits). */
static int zx_fdb_add(struct zx_eth *e, const u8 *mac, u16 vlan, u8 port)
{
	u16 bucket;
	u32 d0, d1, d2, existing;
	int slot;
	u32 mac_low_4, mac_high_2;
	const u32 status = 0xF, dmac_ctrl = 0, smac_ctrl = 0;

	if (port >= 8 || (vlan & ~0xfffu))
		return -EINVAL;

	mac_low_4  = (u32)mac[0]       | ((u32)mac[1] << 8)
		   | ((u32)mac[2] << 16) | ((u32)mac[3] << 24);
	mac_high_2 = (u32)mac[4]       | ((u32)mac[5] << 8);

	/* Hash bucket — TEMP revert to IBM hash while we verify the new
	 * sbrg_hash (CCITT/XMODEM) didn't itself wedge RX. */
	bucket = zx_crc16(mac, 6) & 0x3FF;

	/* Stock entry encoding */
	d2 = (u32)port | (mac_low_4 << 8);
	d1 = ((status & 0xf) << 4)
	   | ((vlan >> 8) & 0xf)
	   | ((smac_ctrl & 1u) << 8)
	   | ((dmac_ctrl & 1u) << 9);
	d0 = (mac_low_4 >> 24)
	   | ((u32)(vlan & 0xfff) << 24)
	   | ((mac_high_2 & 0xffff) << 8);

	/* Linear probe through 4 slots in bucket; find empty.
	 * Stock uses status nibble bits 31..28 of d2 (the new format). For now
	 * preserve existing logic (check d0 bits) but fix the d1/d2 clobber
	 * bug — zx_brg_ram_get overwrites our intended d1/d2 with stale HW
	 * data, so save/restore them. */
	{
		u32 save_d1 = d1, save_d2 = d2;
		u32 ex_d1, ex_d2;
		for (slot = 0; slot < 4; slot++) {
			if (zx_brg_ram_get(e, bucket, slot, &existing, &ex_d1, &ex_d2))
				return -EBUSY;
			/* Stock status nibble at d2 bits 31..28 = 0 → empty */
			if (((ex_d2 >> 28) & 0xf) == 0) {
				zx_brg_ram_set(e, bucket, slot, d0, save_d1, save_d2);
				dev_info(e->dev,
					 "FDB add: port=%u vlan=%u %pM → bucket=%u slot=%d\n",
					 port, vlan, mac, bucket, slot);
				return 0;
			}
		}
	}
	return -ENOSPC;
}

/* ============================================================
 *   SBRAG indirect-protocol MAC FDB (THE table the switch consults)
 *
 *   Round-2 reviewer (2026-05-24) confirmed zx_brg_ram_set above writes
 *   to PP_BRG_RAM = VLAN/per-port table, NOT the MAC FDB. The real MAC
 *   table is reached via stock's sbrg_set_indreg_wr protocol against
 *   sbragRegTable.  Physical offsets (byte) from fpga_base:
 *
 *     CMD   (reg 0x13)  at 0x388814  mask 0x8fc00fff
 *     BUSY  (reg 0x14)  at 0x388818  bit 0
 *     DATA0 (reg 0x4c)  at 0x38881C  full 32-bit
 *     DATA1 (reg 0x4d)  at 0x388820  full 32-bit
 *     DATA2 (reg 0x4e)  at 0x388824  full 32-bit
 *
 *   CMD encoding (stock sbrg_set_indreg_cmd, decomp_all_tm.c L8316):
 *     val = ram_addr | (mem_id << 22) | (rw << 27) | (mode << 31)
 *   BUSY semantics: stock polls regId 0x14 reading 1 means "complete".
 *   Write order: D2 → D1 → D0 (D0 commits, same as PP_BRG_RAM).
 * ============================================================ */

#define ZX_SBRAG_CMD	0x388814
#define ZX_SBRAG_BUSY	0x388818
#define ZX_SBRAG_D0	0x38881C
#define ZX_SBRAG_D1	0x388820
#define ZX_SBRAG_D2	0x388824

static int zx_sbrag_wait(struct zx_eth *e)
{
	int n = 10;
	while (n-- > 0) {
		if (readl(e->fpga_base + ZX_SBRAG_BUSY) & 1)
			return 0;
		udelay(2);
	}
	return -EBUSY;
}

static int zx_sbrag_set_cmd(struct zx_eth *e, u32 mode, u32 rw, u32 mem_id, u32 ram_addr)
{
	u32 val, cur;
	const u32 cmd_mask = 0x8fc00fffu;

	if (mode > 1 || rw > 1 || mem_id > 0x1f || ram_addr > 0xfff)
		return -EINVAL;
	val = (ram_addr & 0xfff) | ((mem_id & 0x1f) << 22) | ((rw & 1) << 27) | ((mode & 1u) << 31);
	cur = readl(e->fpga_base + ZX_SBRAG_CMD);
	writel((cur & ~cmd_mask) | (val & cmd_mask), e->fpga_base + ZX_SBRAG_CMD);
	return 0;
}

/* zx_sbrag_add_mac — register one MAC in the real switch FDB via the indirect
 * sbrag protocol.  Mirrors stock sbrg_add_mactable for the simple-unicast path
 * (mem_id=0, no multicast specials) with the entry encoding it computes at
 * decomp_all_tm.c L10836-10840 (D0..D2 as in zx_fdb_add).
 *
 * This is ADDITIVE to zx_fdb_add (which writes to PP_BRG_RAM, a separate
 * table). Round-2 review identified sbrag as the table the switch egress
 * logic actually consults, so populating it should stop the auto-learn-aging
 * flood that produces RUN2+ DUP storms. */
static int zx_sbrag_add_mac(struct zx_eth *e, const u8 *mac, u16 vlan, u8 port)
{
	u32 mac_low_4, mac_high_2;
	u32 d0, d1, d2;
	const u32 status = 0xF, dmac_ctrl = 0, smac_ctrl = 0;
	u32 mem_id = 0;
	u32 ram_addr;
	int rc;

	if (port >= 8 || (vlan & ~0xfffu))
		return -EINVAL;

	mac_low_4  = (u32)mac[0]       | ((u32)mac[1] << 8)
		   | ((u32)mac[2] << 16) | ((u32)mac[3] << 24);
	mac_high_2 = (u32)mac[4]       | ((u32)mac[5] << 8);

	/* Same hash we use for PP_BRG_RAM; sbrg_hash actually uses CRC-16/CCITT.
	 * Approximate for now — collision just means linear-probe in sbrag (TODO). */
	ram_addr = zx_crc16(mac, 6) & 0xfff;

	d2 = (u32)port | (mac_low_4 << 8);
	d1 = ((status & 0xf) << 4)
	   | ((vlan >> 8) & 0xf)
	   | ((smac_ctrl & 1u) << 8)
	   | ((dmac_ctrl & 1u) << 9);
	d0 = (mac_low_4 >> 24)
	   | ((u32)(vlan & 0xfff) << 24)
	   | ((mac_high_2 & 0xffff) << 8);

	rc = zx_sbrag_wait(e);
	if (rc)
		return rc;
	rc = zx_sbrag_set_cmd(e, 0, 0, mem_id, ram_addr);
	if (rc)
		return rc;
	rc = zx_sbrag_wait(e);
	if (rc)
		return rc;
	/* D2 → D1 → D0 (D0 commits) */
	writel(d2, e->fpga_base + ZX_SBRAG_D2);
	writel(d1, e->fpga_base + ZX_SBRAG_D1);
	writel(d0, e->fpga_base + ZX_SBRAG_D0);
	dev_info(e->dev, "SBRAG add: %pM vlan=%u port=%u → mem_id=%u ram_addr=%u\n",
		 mac, vlan, port, mem_id, ram_addr);
	return 0;
}

/* Disable unknown-unicast flood for all ports except CPU.
 *
 * THE big DUPs fix (Plan agent 2026-05-25): when the switch can't find the
 * destination MAC in its FDB, it floods the frame to every port that has
 * "unknown unicast forward" enabled. Stock kotrace
 * (kotrace_p3c_analysis.txt) shows it calls `tm_port_unknwn_unicast_fwd_set`
 * 8 times — ports 0,1,2,3,4,6,7 with enable=0 and ONLY port 5 (CPU) with
 * enable=1. We never set this, so every unknown-DA reply gets broadcast to
 * all 4 LAN ports + MAC4-RGMII + CPU loopback → host sees 1-3 copies per
 * ping → DUPs (158 by RUN3 in our test).
 *
 * Stock impl (decomp_all_tm.c L6987 sbrg_set_unknown_unicst_fwd) is a
 * read-modify-write of sbragRegTable[0x36], which is PP[0x8340] bits
 * 24..31 — one bit per port. Bit 24 = port 0 etc. Setting only bit 29
 * (port 5 = CPU) is the result of running all 8 stock calls.
 *
 * RE: regId 0x36 in zx_sbragregtable: base_off=0x0e20d0 → byte 0x388340
 * → phys 0x92388340 → relative to our pp_base (PP_OFF=0x1c0000): 0x8340.
 * mask=0x000000ff shift=24 confirms the 8-bit field at top of the dword. */
static void zx_sbrg_set_unknown_unicast_flood_policy(struct zx_eth *e, u8 cpu_port_bitmap)
{
	void __iomem *pp = e->base + PP_OFF;
	u32 v_old = readl(pp + 0x8340);
	/* PP[0x8340] holds TWO fields:
	 *   bits  8..23: sbragRegTable[0x35] PKTDEAL — 2 bits per port (8 ports).
	 *                Stock kotrace shows pktdeal=1 for every port → 0b01 in
	 *                each 2-bit slot → 0x5555 in bits 8..23.
	 *   bits 24..31: sbragRegTable[0x36] FWD — 1 bit per port (8 ports).
	 *                Stock kotrace: only port 5 (CPU) → 0x20.
	 * Earlier fix only touched FWD bits; PKTDEAL stayed at HW default
	 * (likely 0 = drop), which may have been worse than the missing FWD
	 * config. Stock writes BOTH; replay both in one read-modify-write. */
	u32 pktdeal_all = 0x5555u;	/* every port: pktdeal=1 */
	u32 v = (v_old & 0x000000ffu) |
		(pktdeal_all << 8) |
		((u32)cpu_port_bitmap << 24);
	writel(v, pp + 0x8340);
	dev_info(e->dev,
		 "SBRG flood policy: PP[0x8340] %08x -> %08x (pktdeal=0x%04x fwd_bitmap=0x%02x)\n",
		 v_old, v, pktdeal_all, cpu_port_bitmap);
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
 *   PON low-bank init (refactor #38 Phase 9a)
 *
 * Replaces the first 16 entries of the old zx_stock_init_table[] (the
 * PON_LOW block). Stock hits four identical PON sub-blocks at pon_early
 * offsets 0x00000, 0x10000, 0x20000, 0x30000 with the same 4-word
 * pattern. Capturing it as a loop here makes the intent obvious to a
 * netdev reviewer; the wires are bit-for-bit identical to stock.
 *
 * The fourth word per block (0x44bef) is the only non-trivial value —
 * we leave it unnamed until the matching .ko-side RE catches up.
 * ============================================================ */
static void zx_pon_low_init(struct zx_eth *e)
{
	int i;

	for (i = 0; i < 4; i++) {
		void __iomem *blk = e->pon_early + i * 0x10000;

		writel(0xffffffff, blk + 0x0);  /* clear/enable bank A */
		writel(0xffffffff, blk + 0x4);  /* clear/enable bank B */
		writel(0xffffffff, blk + 0x8);  /* clear/enable bank C */
		writel(0x00044bef, blk + 0xc);  /* PON sub-block cfg */
	}
}

/* ============================================================
 *   NPP twin-pair init (refactor #38 Phase 9f)
 *
 * NPP has three pairs of sub-blocks at stride 0x2000 that receive
 * BIT-IDENTICAL writes in stock — instances (0,1), (2,3), (6,7).
 * Rather than store the data twice, we keep one copy per pair (in
 * zx_npp_twin_data.h) and apply each set to both instance bases.
 *
 * The pair 6/7 payload at +0x280..+0x2bc holds an embedded Ethernet
 * frame template (dst MAC + IPv4/TCP) used by the HW classifier
 * autoreply path. It is environment-specific in the stock capture
 * (encodes the unit's connected-host MAC); preserved bit-for-bit
 * pending dynamic-construction RE.
 *
 * Instance 10 (96 writes at +0x14000) is NOT a twin pair and stays
 * in the generic zx_stock_apply_block("NPP") path.
 * ============================================================ */
static void zx_npp_apply_pair(struct zx_eth *e, u32 base_off,
			      const struct zx_off_val *ops, size_t n)
{
	void __iomem *p = e->base + base_off;
	size_t i;

	for (i = 0; i < n; i++)
		writel(ops[i].val, p + ops[i].off);
}

static void zx_npp_twin_init(struct zx_eth *e)
{
	zx_npp_apply_pair(e, 0x0000, zx_npp_pair_01, ARRAY_SIZE(zx_npp_pair_01));
	zx_npp_apply_pair(e, 0x2000, zx_npp_pair_01, ARRAY_SIZE(zx_npp_pair_01));
	zx_npp_apply_pair(e, 0x4000, zx_npp_pair_23, ARRAY_SIZE(zx_npp_pair_23));
	zx_npp_apply_pair(e, 0x6000, zx_npp_pair_23, ARRAY_SIZE(zx_npp_pair_23));
	zx_npp_apply_pair(e, 0xc000, zx_npp_pair_67, ARRAY_SIZE(zx_npp_pair_67));
	zx_npp_apply_pair(e, 0xe000, zx_npp_pair_67, ARRAY_SIZE(zx_npp_pair_67));
}

/* ============================================================
 *   PON_TAIL lookup RAM init (refactor #38 Phase 9e)
 *
 * The single biggest run in stock.bin: 4082 contiguous writes at
 * pon_early fpga byte 0xc0040..0xc4004 (16 KB), filling a HW lookup
 * RAM with the default value 0x00004bef, then setting 2 control
 * words immediately after.
 *
 *   slots 0..4079  →  0x00004bef    (default: drop/no-match action)
 *   slot  4080     →  0x07d0000c    (threshold/credit — 0x7d0 = 2000)
 *   slot  4081     →  0x0000002a    (count/flags     — 42)
 *
 * The 4080-of-same-value pattern is the classic signature of a HW
 * lookup table (FDB / ACL TCAM / VLAN map) being initialized to a
 * default "miss" action, followed by a 2-word footer holding the
 * table's runtime parameters.
 *
 * Replaces a 16 KB rodata burst array + 1 __iowrite32_copy with a
 * tiny loop. Reader can see at a glance what's happening.
 * ============================================================ */
static void zx_pon_tail_lookup_init(struct zx_eth *e)
{
	void __iomem *rom = e->pon_early + 0xc0040;
	int i;

	for (i = 0; i < 4080; i++)
		writel(0x00004bef, rom + i * 4);

	writel(0x07d0000c, rom + 4080 * 4);
	writel(0x0000002a, rom + 4081 * 4);
}

/* ============================================================
 *   TM per-instance table init (refactor #38 Phase 9d)
 *
 * Each of the 16 TM instances (0x180000 + i * 0x400) carries a
 * 64-word config table at +0x10240. The stock blob writes the
 * SAME 256-byte image into all 16 instances — verified
 * bit-identical (see findings/stock_table_structural_patterns.md
 * pattern B).
 *
 * High half of the first 16 words is DDR-backed (0x4ec____, 0x4ff____):
 * very likely default queue/buffer descriptor base pointers. The
 * later words look like small queue control / threshold bytes.
 * Exact semantics still un-RE'd; the bit pattern is preserved.
 *
 * Replaces 1024 individual writel() calls with 16 __iowrite32_copy
 * calls of a shared source array.
 * ============================================================ */
static const u32 zx_tm_per_instance_init_data[64] = {
	/*  0..*/ 0x4ffeff10, 0x4ec33b10, 0x4ec33b90, 0x4ffeff20,
	          0x4ec30e10, 0x4ec30e90, 0x4ffeff30, 0x4ec31710,
	/*  8..*/ 0x4ec31790, 0x4ec2bd10, 0x4ffefee0, 0x4ec2d810,
	          0x4ffefef0, 0x4ec2fc10, 0x4ffeff00, 0x4ec2f310,
	/* 16..*/ 0x00008010, 0x00020080, 0x00020036, 0x00008010,
	          0x00020080, 0x00020016, 0x00008010, 0x00020080,
	/* 24..*/ 0x00020046, 0x0002002e, 0x00008010, 0x0002002e,
	          0x00008010, 0x0002002e, 0x00008010, 0x0002002e,
	/* 32..*/ 0x4ec2c610, 0x4ec2c690, 0x4ff2bd40, 0x4ec34d10,
	          0x4ec29a10, 0x4ec29a90, 0x4ec29b10, 0x4ff2bd00,
	/* 40..*/ 0x4ec2e110, 0x4ec2e190, 0x4ec2e210, 0x4ff2bd10,
	          0x4ec2ea10, 0x4ff2bd20, 0x4ec30510, 0x4ff2bd30,
	/* 48..*/ 0x0000002f, 0x0000002a, 0x00000021, 0x00000028,
	          0x0000002f, 0x0000002f, 0x00000025, 0x00000021,
	/* 56..*/ 0x0000002f, 0x0000002f, 0x00000023, 0x00000021,
	          0x00000028, 0x00000021, 0x00000028, 0x00000021,
};

static void zx_tm_per_instance_init(struct zx_eth *e)
{
	int i;

	for (i = 0; i < 16; i++) {
		void __iomem *tm_i = e->base + 0x180000 + i * 0x400;

		/* Phase 9g: 7 control regs identical across all 16 TM instances. */
		writel(0x00000140, tm_i + 0x000);  /* instance enable / mode? */
		writel(0x00000010, tm_i + 0x004);
		writel(0x4ff1f000, tm_i + 0x0f0);  /* DDR base pointer */
		writel(0xfffffffc, tm_i + 0x104);
		writel(0x03ffffff, tm_i + 0x124);
		writel(0x00001fff, tm_i + 0x12c);
		writel(0x001fffff, tm_i + 0x134);

		/* Phase 9d: 64-word per-instance config table. */
		__iowrite32_copy(tm_i + 0x10240,
				 zx_tm_per_instance_init_data, 64);
	}
}

/* ============================================================
 *   NPP_AUX init (refactor #38 Phase 9c)
 *
 * 13 NPP_AUX sub-blocks at base offsets 0xcc000, 0xd0000, 0xd4000, …,
 * 0xfc000 (stride 0x4000). Each gets the SAME 12-word init —
 * verified bit-identical across all 13 instances. Replaces 156 entries
 * of the stock table with a single 13-iteration loop.
 *
 * What these registers are exactly is still un-RE'd; the values are
 * preserved bit-for-bit. The pattern alone tells us NPP has at least
 * 13 sub-units that need identical configuration.
 * ============================================================ */
static void zx_npp_aux_init(struct zx_eth *e)
{
	int i;

	for (i = 0; i < 13; i++) {
		void __iomem *aux = e->base + 0xcc000 + i * 0x4000;

		writel(0x00bae000, aux + 0x000);
		writel(0x00003fff, aux + 0x004);
		writel(0x80000001, aux + 0x008);
		writel(0xffff0000, aux + 0x070);
		writel(0x03e80000, aux + 0x0d4);
		writel(0x00000063, aux + 0x0dc);
		writel(0x00001142, aux + 0x110);
		writel(0x0401710f, aux + 0x11c);
		writel(0x00800800, aux + 0x120);
		writel(0x8000ffff, aux + 0x300);
		writel(0xffffffff, aux + 0x304);
		writel(0x00002000, aux + 0xb00);
	}
}

/* ============================================================
 *   Stock-init replay (refactor #38 Phase 8 + 9b per-block)
 *
 * zx_stock_ops[] (zx_stock_bursts.h) is the same set of writes as
 * zx_stock_init_table[] but pre-classified: contiguous +4 stride runs
 * of ≥4 entries become RUN ops backed by static const u32 arrays and
 * flushed via __iowrite32_copy(); everything else is a SINGLE op
 * (one writel()). Original order is preserved, so the chip sees an
 * identical sequence of MMIO writes.
 *
 * Walked per-block (Phase 9b) so explicit zx_<block>_init() calls can
 * be interleaved at the right point in the init sequence.
 *
 * Most of the savings live in PON_TAIL where ~16 KB of contiguous
 * RAM-table init was 4082 individual writel() calls before.
 * ============================================================ */
static void zx_stock_apply_block(struct zx_eth *e, const char *name,
				 u32 start, u32 end)
{
	u32 i, runs = 0, singles = 0, regs_in_runs = 0;

	for (i = start; i < end; i++) {
		const struct zx_stock_op *op = &zx_stock_ops[i];
		void __iomem *win = (op->window == ZX_BURST_WIN_PON_EARLY)
				    ? e->pon_early : e->base;

		if (op->kind == ZX_BURST_KIND_RUN) {
			__iowrite32_copy(win + op->off_or_addr, op->data,
					 op->val_or_len);
			runs++;
			regs_in_runs += op->val_or_len;
		} else {
			writel(op->val_or_len, win + op->off_or_addr);
			singles++;
		}
	}
	dev_info(e->dev,
		 "stock-init %s: %u ops (%u runs/%u regs + %u singles)\n",
		 name, end - start, runs, regs_in_runs, singles);
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
	/* REMOVED 2026-05-24: live-stock dump shows PP[+0x2c] = 0x00000106 across
	 * ALL 8 per-port blocks. Our previous |= BIT(25) wrote 0x02000106, which
	 * is wrong. The per-port block's +0x2c init value (0x106 from line 512)
	 * is the correct stock value. Bit 25 was a misinterpretation of the
	 * stock decomp (`pp[0x2c] |= 1 << (lan_up_port + 0x19)` was conditional
	 * on `lan_up != 0` which is not set in our boot path).
	 * See tasks/00.01.eth-driver/findings/stock_register_state_2026-05-24.md */

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

	/* === HW classifier + SPA CPU pktdeal config from stock kotrace 2026-05-24 ===
	 * RE: cspd calls during init (kotrace_phase5b_dump.txt):
	 *   - cla_set_oth_l3_pkt_action_cfg(0) — 1 call (action 0 for unknown L3)
	 *   - spa_set_enty_pktdeal_cfg(port 0..7, slot 0..58, val=1) — 465 calls
	 *     This is the CPU port full pktdeal setup; without it, the switch
	 *     doesn't know how to handle pkts from the CPU port.
	 *
	 * Register table addresses extracted from tm.ko .data (see zx_reg_tables.h):
	 *   claRegTable[0x15] -> PP @ 0x9238c0cc (mask 0x3 shift 0)
	 *   spaRegTable[0x43..0x7d] -> NPP @ 0x921d4300..0x921d430c (mask 0x3, various shifts, stride 5)
	 *
	 * Our ioremap base is 0x921c0000 so offsets are:
	 *   PP[+0xc0cc]  = byte 0x1cc0cc from our base
	 *   NPP[+0x4300] = byte 0x14300 from our base
	 */
	{
#define ZX_FPGA_BASE_TO_NPP_OFF 0x1c0000	/* our base is +0x1c0000 from physical FPGA 0x92000000 */
		u32 port, slot, byte_off, cur, new_v;
		const struct zx_reg_entry *ent;

		/* cla_set_oth_l3_pkt_action_cfg(0) */
		ent = &zx_cla_table[0x15];
		byte_off = ent->base_dword * 4 - ZX_FPGA_BASE_TO_NPP_OFF;
		cur = readl(e->base + byte_off);
		new_v = (cur & ~(ent->mask << ent->shift)) | ((0 & ent->mask) << ent->shift);
		writel(new_v, e->base + byte_off);
		dev_info(e->dev, "cla_oth_l3_act_cfg: PP+0x%x %#x -> %#x\n",
			 byte_off + ZX_FPGA_BASE_TO_NPP_OFF, cur, new_v);

		/* spa_set_enty_pktdeal_cfg(entity 0..7, slot 0x43..0x7d, val=1) — 8 × 59 = 472 writes.
		 * Stock kotrace shows 465 — slight diff likely from validation bounds.
		 * stride is in dwords; spaRegTable already encodes per-entity stride. */
		for (slot = 0x43; slot <= 0x7d; slot++) {
			ent = &zx_spa_table[slot];
			if (ent->mask == 0)
				continue;
			for (port = 0; port < 8; port++) {
				byte_off = (ent->base_dword + port * ent->stride) * 4
					   - ZX_FPGA_BASE_TO_NPP_OFF;
				cur = readl(e->base + byte_off);
				new_v = (cur & ~(ent->mask << ent->shift)) |
					((1 & ent->mask) << ent->shift);
				writel(new_v, e->base + byte_off);
			}
		}
		dev_info(e->dev, "spa_enty_pktdeal_cfg: applied for entities 0..7 × slots 0x43..0x7d\n");
	}

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

	/* Min frame length 0x40 per stock pon_tm_data_raw_send (decomp 2026-05-24):
	 * if (len < 0x40 && param_3==0 && (desc[14]&1)==0) zeropad to 0x40 and
	 * encode len=0x40 in desc[12..13]=0x100 and desc[8..11] |= 0x40<<9. */
	if (skb->len < 0x40) {
		if (skb_padto(skb, 0x40)) {
			ndev->stats.tx_dropped++;
			return NETDEV_TX_OK;
		}
		skb->len = 0x40;
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
	spin_lock_init(&e->bmu_free_lock);
	e->bmu_free_credit = 0;

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
/* Refactor #38 Phase 2 (2026-05-26): pm.bin → embedded zx_pm_init_table.
 * Bit-identical writes, no semantic change. See gen_pm_table.py. */
#include "zx_pm_table.h"

static void zx_pp_pm_apply_replay(struct zx_eth *e)
{
	u32 i, ok = 0, fail = 0;

	for (i = 0; i < ZX_PM_INIT_TABLE_LEN; i++) {
		if (zx_pp_pm_write_entry(e, zx_pm_init_table[i].ram_id,
					 zx_pm_init_table[i].ram_addr,
					 zx_pm_init_table[i].data) == 0)
			ok++;
		else
			fail++;
	}
	dev_info(e->dev, "pp_pm init: %u ok, %u fail (%u embedded)\n",
		 ok, fail, ZX_PM_INIT_TABLE_LEN);
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

/* Refactor #38 Phase 1 (2026-05-26): use embedded static table instead of
 * firmware_request("zx-replay/cla.bin"). Bit-identical writes — verified
 * by comparing the generated zx_cla_table.h against the in-tree partial
 * zx279128-eth-cla-regs.h. The firmware_request for cla.bin can be made
 * optional in a follow-up commit once this is proven not to regress. */
#include "zx_cla_table.h"

static void zx_cla_apply_replay(struct zx_eth *e)
{
	u32 i, ok = 0, fail = 0;
	u32 ram7_data[17] = {7, 0,};

	for (i = 0; i < ZX_CLA_INIT_TABLE_LEN; i++) {
		if (zx_cla_write_entry(e, zx_cla_init_table[i].ram_id,
				       zx_cla_init_table[i].ram_addr,
				       zx_cla_init_table[i].data) == 0)
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
	dev_info(e->dev, "CLA init: %u ok, %u fail (%u embedded + ram=7 0..%d)\n",
		 ok, fail, ZX_CLA_INIT_TABLE_LEN, ZX_CLA_RAM7_LAST);
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
/* CPU port = 5 per stock kotrace (sbrg_set_unknown_unicst_fwd called
 * 8 times with port 5 = enable=1, others = enable=0). */
#define ZX_CPU_PORT_BIT		BIT(5)
#define ZX_ALL_PORTS_BITMAP	0xffu

static void zx_pp_brg_init(struct zx_eth *e)
{
	void __iomem *pp = e->fpga_base + 0x380000;

	/* 2026-05-25 — log INHERITED state from U-Boot before we overwrite.
	 * Lets us see what U-Boot left behind so we can spot regs where we
	 * may be clobbering a known-good config. Diff against the writes
	 * below tells us which writes are no-ops vs. destructive. */
	dev_info(e->dev, "PP_BRG inherited from U-Boot (pre-init):\n");
	dev_info(e->dev, "  PP[0x8004]=%08x  [0x8008]=%08x  [0x8050]=%08x\n",
		 readl(pp + 0x8004), readl(pp + 0x8008), readl(pp + 0x8050));
	dev_info(e->dev, "  PP[0x8188]=%08x (aging_cycle)\n", readl(pp + 0x8188));
	dev_info(e->dev, "  PP[0x81c0]=%08x (SMAC_LOOK_EN bitmap)\n", readl(pp + 0x81c0));
	dev_info(e->dev, "  PP[0x81c4]=%08x (LEARN_MODE per port)\n", readl(pp + 0x81c4));
	dev_info(e->dev, "  PP[0x82c0]=%08x (DA_LOOKUP_EN bitmap)\n", readl(pp + 0x82c0));
	dev_info(e->dev, "  PP[0x8300]=%08x  [0x8304]=%08x\n",
		 readl(pp + 0x8300), readl(pp + 0x8304));
	dev_info(e->dev, "  PP[0x8340]=%08x (PKTDEAL+FWD)\n", readl(pp + 0x8340));
	dev_info(e->dev, "  PP[0x8344]=%08x  [0x8380]=%08x  [0x863c]=%08x\n",
		 readl(pp + 0x8344), readl(pp + 0x8380), readl(pp + 0x863c));

	writel(0x020000ff, pp + 0x8004);
	writel(0xff5555ff, pp + 0x8340);
	writel(0x0000001e, pp + 0x8344);
	writel(0x0000001f, pp + 0x8380);
	writel(0xaaaaaaaa, pp + 0x863c);

	/* SMAC_LOOK_EN — 1 bit per port; was 0xff (all 8 enabled).
	 * 2026-05-25 EXPERIMENT: disable SMAC learn on CPU port (bit 5).
	 * Hypothesis: switch hairpins our own egress back to CPU port; with
	 * SMAC learn enabled there, switch updates FDB from the looped-back
	 * frame (sometimes with src_mac rewritten by switch egress stamping)
	 * → FDB flap → flood. Disabling CPU-port learn keeps FDB stable.
	 * LAN ports 0-4,6,7 still learn so external hosts get FDB entries. */
	writel(ZX_ALL_PORTS_BITMAP & ~ZX_CPU_PORT_BIT, pp + 0x81c0);

	writel(0x00005555, pp + 0x81c4);
	writel(0x0013f434, pp + 0x8188);
	writel(0x000000ff, pp + 0x82c0);
	writel(0x0000ffff, pp + 0x8300);
	writel(0x020000ff, pp + 0x8304);
	writel(0xfffffffa, pp + 0x8050);
	writel(0x0000ff00, pp + 0x8008);
	dev_info(e->dev, "PP_BRG post-init: SMAC_LOOK_EN=%02x (CPU port 5 disabled)\n",
		 readl(pp + 0x81c0));

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
static int zx_bmu_free_bp(struct zx_eth *e, u16 bp_idx, u8 is_pon);

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
/* RX checkpoint logging — kept under pr_debug so it compiles out unless
 * the file/dyn-debug is enabled. The first-N-polls gate is preserved so
 * even with debug on the log stays bounded during bring-up. */
#define RXCP(e, stage, fmt, ...) do { \
	if ((e)->tm_napi_count < 20) \
		pr_debug("[ZXETH/RX poll#%u CP%d] " fmt "\n", \
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
			/* bp_idx is 10 bits split: low 7 in desc[7]>>1, high 7 in desc[8].
			 * Stock pon_tm_net_poll line 8754:
			 *   uVar11 = (desc[7]>>1) | (desc[8]<<7);
			 * We previously used only desc[7]>>1 → wrong buffer for bp>=128
			 * (delivered all-zero garbage to Linux). */
			u16 bppe_idx = ((u16)(desc[7] >> 1)) |
				       ((u16)desc[8] << 7);
			RXCP(e, 4, "q=%d desc[%u] @%p: len=%u bppe=%u "
			          "raw[0..7]=%02x %02x %02x %02x %02x %02x %02x %02x",
			     q, idx, desc, len, bppe_idx,
			     desc[0], desc[1], desc[2], desc[3],
			     desc[4], desc[5], desc[6], desc[7]);

			if (len > 0 && len < 1600 && e->bp_cpu) {
				const u8 *bp_buf = (const u8 *)e->bp_cpu + (u32)bppe_idx * TM_BP_SIZE;
				/* Detect frame offset by examining the ETHERTYPE field
				 * (16-bit, bytes 12..13 of ethernet frame). Real ethertypes
				 * are >= 0x0600 (per IEEE 802.3). If we see a valid value
				 * at bp_buf+12, the frame is at +0 (looped-back TX).
				 * Else at bp_buf+16 (fresh RX with HW prefix). */
				u16 et_at_0 = ntohs(*(const __be16 *)(bp_buf + 12));
				const u8 *src = (et_at_0 >= 0x0600 && et_at_0 != 0xffff) ?
						bp_buf : (bp_buf + 16);
				/* Phase 5 deep probe: dump bytes 0..47 of bp_buf for first
				 * 12 packets to see exactly what HW writes. We want to
				 * distinguish fresh-RX (HW prefix at 0..15, frame at 16+)
				 * from looped-TX (frame at 0+, no prefix). */
				if (e->tm_rx_count + e->tm_rx_loopback_drops < 20) {
					dev_info(e->dev,
						"BPDUMP q=%d len=%u bppe=%u +00..0f=%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x +10..1f=%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x +20..2f=%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
						q, len, bppe_idx,
						bp_buf[0],  bp_buf[1],  bp_buf[2],  bp_buf[3],  bp_buf[4],  bp_buf[5],  bp_buf[6],  bp_buf[7],
						bp_buf[8],  bp_buf[9],  bp_buf[10], bp_buf[11], bp_buf[12], bp_buf[13], bp_buf[14], bp_buf[15],
						bp_buf[16], bp_buf[17], bp_buf[18], bp_buf[19], bp_buf[20], bp_buf[21], bp_buf[22], bp_buf[23],
						bp_buf[24], bp_buf[25], bp_buf[26], bp_buf[27], bp_buf[28], bp_buf[29], bp_buf[30], bp_buf[31],
						bp_buf[32], bp_buf[33], bp_buf[34], bp_buf[35], bp_buf[36], bp_buf[37], bp_buf[38], bp_buf[39],
						bp_buf[40], bp_buf[41], bp_buf[42], bp_buf[43], bp_buf[44], bp_buf[45], bp_buf[46], bp_buf[47]);
				}
				/* Phase 5: ingress port from desc[6] bits 3..7, minus 1.
				 * Per stock RE: `r2 = (desc[6] >> 3) & 0x1F; r2 -= 1; pkt[180] = r2`.
				 * This is the UNI/PON port the packet arrived on. */
				int ingress_port = ((desc[6] >> 3) & 0x1F) - 1;
				/* Per-ingress counter for empirical CPU-loopback port id */
				{
					int slot = (ingress_port + 1) & 0x1F;
					e->tm_rx_per_ingress[slot]++;
				}
				if (e->sw_dev && !memcmp(src + 6, e->sw_dev->dev_addr, 6)) {
					e->tm_rx_loopback_drops++;
					if (e->tm_rx_loopback_drops <= 5)
						dev_info(e->dev, "LOOPBACK drop #%u src=%pM dst=%pM ethertype=%04x len=%u ingress=%d\n",
							 e->tm_rx_loopback_drops, src + 6, src,
							 ntohs(*(__be16*)(src + 12)), len, ingress_port);
					/* BMU free on drops DISABLED — RX wedged in test
					 * 2026-05-25; suspect still double-frees the same
					 * way as the unconditional call. Pool leak is slow
					 * (~30 BPs/min) so acceptable for now. */
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
						/* Dynamic FDB learning DISABLED 2026-05-25 (degradation test).
						 * Per round-2 review: zx_fdb_add writes to PP_BRG_RAM
						 * (VLAN table), not the sbrag MAC FDB the switch reads
						 * on egress. After many writes the wrong-table state
						 * may flip switch behavior to flood — explains the
						 * RUN1→RUN2 DUP storm (0 → 60+ DUPs over 10s).
						 * Keep only the at-probe HW FDB seed for own MAC. */
					}
				}
				/* DO NOT call zx_bmu_free_bp here. Empirical test
				 * 2026-05-25: ALLOC_BPCNT=15864, RLS_BPCNT=15893 →
				 * HW was already releasing more than allocating, so
				 * our explicit free was DOUBLE-freeing, corrupting the
				 * pool and killing RX entirely (100% loss). HW must
				 * auto-recycle BPs when zx_tm_release_rx_desc is acked.
				 * Stock pon_tm_net_poll's pp_bmu_free_bp may apply only
				 * to a different RX path (jumbo/PON-side?). TBD. */
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
		pr_debug("[ZXETH/TM_IRQ#%u] status=%#x mask=%#x pending=%#x — scheduling NAPI\n",
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

/* Periodic STATS dump — DISABLED by default (was flooding the bridge log
 * every 5s with no actionable change). Re-enable temporarily for debug by
 * defining ZX_PERIODIC_STATS=1. The one-shot at sw_open+30s is enough for
 * normal observation; if you need correlation across ping runs, bump the
 * macro and rebuild. */
#define ZX_PERIODIC_STATS	0

static void zx_bmu_dump_fn(struct work_struct *w)
{
	struct zx_eth *e = zx_bmu_dump_eth;
	u32 alloc, rls, bppe_avail, bppi, bp_stat, tx_kick, tx_done;
	if (!e) return;
	/* Compact one-line dump: most-changing counters for ping-loop correlation */
	alloc      = tm_read(e, 0x8090);
	rls        = tm_read(e, 0x8098);
	bppe_avail = tm_read(e, 0x8080);
	bppi       = tm_read(e, 0x8088);
	bp_stat    = tm_read(e, 0x80dc);
	tx_kick    = tm_read(e, 0x10054);
	tx_done    = tm_read(e, 0x10058);
	dev_info(e->dev,
		 "STATS uptime_jiff=%lu drv:rx=%u rxlb=%u tx=%u txdrop=%u napi=%u irq=%u "
		 "hw:alloc=%u rls=%u(diff=%d) bppe_avail=%u bppi=%u bp_stat=%08x "
		 "tx_kick=%u tx_done=%u\n",
		 jiffies,
		 e->tm_rx_count, e->tm_rx_loopback_drops, e->tm_tx_count, e->tm_tx_dropped,
		 e->tm_napi_count, e->tm_irq_count,
		 alloc, rls, (int)rls - (int)alloc,
		 bppe_avail, bppi, bp_stat,
		 tx_kick, tx_done);

	/* Per-ingress-port RX histogram — for DUPs hairpin diagnosis.
	 * The port whose count grows ~1:1 with tm_tx_count is the CPU hairpin
	 * loopback source. Drop frames from it to break the amplification
	 * loop. Slots [0..31] = ingress_port+1 (so slot 0 = ingress -1 "invalid",
	 * slot 1 = port 0, slot 8 = port 7, etc.). */
	dev_info(e->dev, "STATS rx_per_ingress[]: "
		 "[ing-1]=%u [0]=%u [1]=%u [2]=%u [3]=%u [4]=%u [5]=%u [6]=%u "
		 "[7]=%u [8]=%u [9]=%u [10]=%u [11]=%u [12]=%u [13]=%u\n",
		 e->tm_rx_per_ingress[0],
		 e->tm_rx_per_ingress[1],  e->tm_rx_per_ingress[2],
		 e->tm_rx_per_ingress[3],  e->tm_rx_per_ingress[4],
		 e->tm_rx_per_ingress[5],  e->tm_rx_per_ingress[6],
		 e->tm_rx_per_ingress[7],
		 e->tm_rx_per_ingress[8],  e->tm_rx_per_ingress[9],
		 e->tm_rx_per_ingress[10], e->tm_rx_per_ingress[11],
		 e->tm_rx_per_ingress[12], e->tm_rx_per_ingress[13],
		 e->tm_rx_per_ingress[14]);
#if ZX_PERIODIC_STATS
	schedule_delayed_work(&zx_bmu_dump_work, msecs_to_jiffies(5000));
#endif
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
	schedule_delayed_work(&zx_bmu_dump_work, msecs_to_jiffies(10000));

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
/* REAL HW BMU allocator — replaces the cycle-counter HACK (2026-05-24).
 * Stock protocol per pon_tm_bmu_alloc_bp (plat-zxylzb_9128S.ko @ 0x18668):
 *   1. set tm[0x8014] |= 1  (alloc kick)
 *   2. poll tm[0x8014] & 3 == 0  (busy/done bits clear when alloc done)
 *   3. read tm[0x800c]: bit31 SET = valid, bits[15:0] = bp_idx
 *      (bit31 CLEAR = pool empty / error → return invalid)
 *
 * Returns the allocated bp_idx (0..1023), or U32_MAX on failure (pool empty
 * or HW hung). Caller must check and drop TX on failure.
 *
 * Spin-locked because alloc must be serialized — HW has 1 alloc engine.
 * Stock used spin_lock_bh; we use the existing e->tx_lock since alloc only
 * happens in the TX path here. */
static u32 zx_bmu_alloc_bp(struct zx_eth *e)
{
	u32 status, result;
	int poll = 200;

	/* Trigger alloc */
	writel(readl(e->base + TM_OFF + 0x8014) | 1, e->base + TM_OFF + 0x8014);

	/* Poll for completion: bits[1:0] = 0 means done */
	while (poll-- > 0) {
		status = readl(e->base + TM_OFF + 0x8014) & 3;
		if (status == 0) {
			result = readl(e->base + TM_OFF + 0x800c);
			if ((int)result < 0)	/* bit 31 = valid */
				return result & 0xffff;
			/* bit 31 clear = no free buffers, fail */
			break;
		}
	}

	/* Timeout or pool empty */
	return U32_MAX;
}

/* zx_bmu_free_bp — release a BMU buffer back to HW (stock: pp_bmu_free_bp).
 *
 * Stock protocol (plat-zxylzb_9128S.ko @ 0x18794):
 *   spin_lock(&free_lock)
 *   retry up to 200x:
 *     if allow_free_cnt > 0:
 *        allow_free_cnt--
 *        tm[0x8010] = bp_idx | (is_pon << 15)
 *        return 0
 *     allow_free_cnt = (tm[0x80dc] >> 8) & 0x3f  // refill from HW status
 *   return -1
 *
 * Must be called once per RX descriptor consumed (delivered OR dropped), or
 * the BMU pool drains and HW eventually runs out of RX buffers.
 * Returns 0 on success, -EBUSY on credit-refill timeout. */
static int zx_bmu_free_bp(struct zx_eth *e, u16 bp_idx, u8 is_pon)
{
	unsigned long flags;
	int retry;

	spin_lock_irqsave(&e->bmu_free_lock, flags);
	for (retry = 0; retry < 200; retry++) {
		if (e->bmu_free_credit != 0) {
			e->bmu_free_credit--;
			tm_write(e, 0x8010, (u32)bp_idx | ((u32)(is_pon & 1) << 15));
			e->tm_bmu_free_ok++;
			spin_unlock_irqrestore(&e->bmu_free_lock, flags);
			return 0;
		}
		/* Refill credit from HW. Stock formula (decomp):
		 *   allow_free_cnt = (uint)(tm[0x80dc] << 23) >> 26
		 * which extracts bits 3..8 (6-bit count). With typical
		 * tm[0x80dc]=0x50000111, this is 34. The earlier ">> 8" was
		 * wrong — it gave 1 credit per refill, starving the pool. */
		e->bmu_free_credit = (tm_read(e, 0x80dc) >> 3) & 0x3f;
	}
	e->tm_bmu_free_fail++;
	spin_unlock_irqrestore(&e->bmu_free_lock, flags);
	return -EBUSY;
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
 * pr_debug so it compiles out unless the file/dyn-debug is enabled. */
#define TXCP(e, stage, fmt, ...) do { \
	if ((e)->tm_tx_count < 5) \
		pr_debug("[ZXETH/TX#%u CP%d:%s] " fmt "\n", \
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
	if (bp == U32_MAX || bp >= TM_BPPE_POOL_SIZE) {
		spin_unlock_irqrestore(&e->tm_tx_lock, flags);
		/* First failure: emit ONE clean diagnostic via kernel printk */
		if (e->tm_tx_dropped == 0) {
			pr_debug("[ZXETH] BMU alloc FAIL #1: 8000=%#x 8014=%#x "
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
		pr_debug("[ZXETH] BMU alloc OK #1: bp=%u len=%u (8090=%#x)\n",
			 bp, len, tm_read(e, 0x8090));

	bp_buf = (u8 *)e->bp_cpu + (u32)bp * TM_BP_SIZE;
	/* HW BP layout: [16-byte HW prefix][ethernet frame].
	 * RX path confirmed this (BPDUMP shows zeros at +0..15, frame at +16).
	 * TX must mirror it: place frame at bp_buf+16. Confirmed via Phase 5g
	 * no-replay experiment which showed device TX reaches wire BUT shifted
	 * by 16 bytes (frame appears starting at ARP-payload offset 2 instead
	 * of L2 dst MAC) — exactly what putting frame at bp_buf+0 would cause. */
	memset(bp_buf, 0, 16);                  /* zero the HW prefix area */
	memcpy(bp_buf + 16, skb->data, len);    /* frame goes at +16 */
	TXCP(e, 3, "BMU alloc OK: bp=%u bp_buf=%p, copied %u bytes from skb (frame at +16)",
	     bp, bp_buf, len);

	desc = (u8 *)e->txdesc_cpu + e->tx_head * TM_TX_DESC_SIZE;
	memset(desc, 0, TM_TX_DESC_SIZE);
	TXCP(e, 4, "desc[%u]=%p prepared (memset done, BP_SIZE=%u)", e->tx_head, desc, TM_BP_SIZE);
	/* Stock TX desc format (Ghidra decomp of pon_tm_net_tx + pon_tm_data_raw_send,
	 * 2026-05-24, see tasks/00.10.02.re-stock-kmods/findings/tx_path_stock_decomp.md):
	 *   desc[0]   = 0xc9 (CPU/source marker; was 0x80 in our baseline)
	 *   desc[1..3]= 0 except desc[2..3] port hint
	 *   desc[4..7]= 0x00010000  (so desc[6]=1)
	 *   desc[8..11]= 0x21 at byte 11 (VALID|0x20), bp_idx + len<<9 in low bits
	 *   desc[12..13] = (desc[12..13] & 3) | (len << 2). */
	desc[0]  = 0xc9;
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
	/* desc[11] = 0x21 (bit 0 VALID + bit 5 format), not 0x01 — stock decomp
	 * pon_tm_data_raw_send does desc[11] = (desc[11]&1) | 0x20. */
	*(u32 *)(desc + 8) = cpu_to_le32(((bp >> 7) & 0x7f) |
					 ((len & 0x3fff) << 9) |
					 (0x21U << 24));
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

	/* Stock soft_insert_tx_1desc (decomp 2026-05-24) kicks ONE reg (UP=0x10054 or
	 * DN=0x10064) by direction. Tested single-kick (UP only) on top of fixed
	 * desc[11]=0x21: 100% loss vs dual-kick's 60% loss + DUPs. So switch needs
	 * BOTH rings populated to actually move packets to the wire in our setup
	 * (likely because we don't have GPON DN traffic but switch routing expects
	 * activity on DN side too). Keep dual-kick. */
	tm_write(e, 0x10054, 1);	/* upstream kick */
	/* tm_write(e, 0x10064, 1); */	/* downstream kick — disabled */

	/* Post-kick desc invalidation 2026-05-25:
	 * pcap data showed HW emitting the SAME TX desc multiple times — host
	 * received 300 replies for 30 sent (10x amplification), with replies
	 * for old (cross-run) ICMP seqs continuing to fire. Hypothesis: HW
	 * keeps polling the desc ring and re-emitting any slot whose valid
	 * bit (desc[11] bit 5 = 0x20) is still set. Clear it now so HW only
	 * emits once per kick. Use the prior slot we just wrote (tx_head
	 * already advanced — subtract 1 with wrap). dma_wmb to push it out
	 * before HW's next poll cycle. This is the post-kick clear; if HW
	 * reads desc asynchronously (after kick returns), we'd break TX —
	 * in which case revert and implement a NAPI-driven reclaim instead. */
	{
		u32 prev = (e->tx_head - 1) & (TM_TX_RING_SIZE - 1);
		u8 *pdesc = (u8 *)e->txdesc_cpu + prev * TM_TX_DESC_SIZE;
		pdesc[11] &= ~0x20;
		dma_wmb();
	}

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
		pr_debug("[ZXETH] TX#%u bp=%u len=%u  TM_UP=%#x DN=%#x  MAC0[ctrl=%#x ena=%#x 714=%#x 718=%#x]  PP[714=%#x 780=%#x]\n",
			 e->tm_tx_count, bp, len, cnt_up, cnt_dn,
			 mac0_ctrl, mac0_ena, mac0_cnt714, mac0_cnt718,
			 pp_cnt714, pp_cnt780);
		pr_debug("[ZXETH] TX#%u +200us: MAC0[714=%#x 718=%#x]  PP[714=%#x 780=%#x]\n",
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

	/* Phase 6 2026-05-24: single port=1 entry only (was port=1 + port=6).
	 * Stock kotrace captured exactly one sbrg_add_mactable call with port=1.
	 * Adding port=6 entry may have caused flood / DUPs. */
	{
		int rc = zx_fdb_add(e, ndev->dev_addr, 0, 1);
		netdev_info(ndev, "HW FDB seed (PP_BRG_RAM): self MAC port=1 rc=%d\n", rc);
		/* DO NOT call zx_sbrg_set_unknown_unicast_flood_policy(e, 0x20).
		 * Evidence (Agent 1 RE + git blame): an earlier init at L1831
		 * already writes PP[0x8340] = 0xff5555ff which is the CORRECT
		 * stock-matching state: PKTDEAL=1 (normal lookup) for ALL ports
		 * + FWD enabled on ALL ports + reserved low byte. Disabling FWD
		 * on LAN ports (the 0x20 = CPU-only bitmap) breaks lookup on
		 * those ports → every unicast falls through to fallback action
		 * (drop/flood depending on cla_set_dn_unknown_da_action_cfg).
		 * Observed: tx_done counter stays at 0, ping 100% loss. */
	}
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
	seq_printf(s, "tm_bmu_free_ok    = %u\n", e->tm_bmu_free_ok);
	seq_printf(s, "tm_bmu_free_fail  = %u\n", e->tm_bmu_free_fail);
	seq_printf(s, "bmu_free_credit   = %u\n", e->bmu_free_credit);
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

/*
 * Phase 14: run drv->config_init on each PHY referenced from the DT.
 *
 * The monolithic eth driver doesn't have per-port netdevs to attach
 * via phylink_connect_phy() yet (that's the DSA refactor), but the
 * PHY analog blocks still need their LDO + TX DAC powered up via the
 * phy-zte-gephy config_init callback. phy_init_hw() is the documented
 * way to fire config_init without a netdev attach.
 *
 * Looks up "zte,gephys = <&gephy0>, ..." in DT, resolves each handle
 * to a struct phy_device, and inits it.
 */
static void zx_eth_init_phys(struct device *dev)
{
	struct device_node *np = dev->of_node;
	int n = of_count_phandle_with_args(np, "zte,gephys", NULL);
	int i;

	if (n <= 0) {
		dev_info(dev, "no zte,gephys phandles in DT (n=%d)\n", n);
		return;
	}
	dev_info(dev, "PHY init: %d phandles in zte,gephys\n", n);

	for (i = 0; i < n; i++) {
		struct device_node *phy_np;
		struct phy_device *phydev;
		int ret;

		phy_np = of_parse_phandle(np, "zte,gephys", i);
		if (!phy_np)
			continue;
		phydev = of_phy_find_device(phy_np);
		of_node_put(phy_np);
		if (!phydev) {
			dev_warn(dev, "  [%d] phy_device not found\n", i);
			continue;
		}
		ret = phy_init_hw(phydev);
		dev_info(dev, "  [%d] phy_init_hw(%s) = %d\n",
			 i, phydev_name(phydev), ret);
		put_device(&phydev->mdio.dev);
	}
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

	/* DTS exposes two reg entries — "pon" and "npp". Map the npp one
	 * by name so the driver is robust to reg-entry reordering (the
	 * pon hardcoded ioremap a few lines below is the Phase 10b TODO). */
	eth->base = devm_platform_ioremap_resource_byname(pdev, "npp");
	if (IS_ERR(eth->base))
		return dev_err_probe(dev, PTR_ERR(eth->base), "ioremap NPP\n");

	eth->irq_idm = platform_get_irq_byname(pdev, "idm");
	if (eth->irq_idm < 0)
		eth->irq_idm = platform_get_irq(pdev, 0);
	eth->irq_npp = platform_get_irq_byname_optional(pdev, "npp");

	platform_set_drvdata(pdev, eth);

	/* All 3 register-replay snapshots (stock, cla, pm) are now embedded
	 * as static C tables in zx_{cla,pm,stock}_table.h (refactor #38
	 * Phase 1+2+3). No more firmware_request() at probe — the driver
	 * is self-contained. All 4 runtime
	 * firmware loads (cla, pm, stock, fpga) are now gone. */

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

	/* Refactor #38 Phase 9b: per-block init in original stock order.
	 * Each block is either an explicit zx_<block>_init() (extracted)
	 * or a zx_stock_apply_block() call into the still-generic ops
	 * table. As blocks get extracted in later phases, the corresponding
	 * SKIP_BLOCKS entry in gen_stock_bursts.py drops them from the
	 * generated ops; the per-block call here is replaced by the new
	 * zx_<block>_init(). */
	zx_pon_low_init(eth);  /* PON_LOW — Phase 9a (extracted) */
	zx_stock_apply_block(eth, "PON_B",
		ZX_STOCK_OPS_PON_B_START,    ZX_STOCK_OPS_PON_B_END);
	zx_pon_tail_lookup_init(eth);  /* PON_TAIL 16 KB lookup RAM — Phase 9e (extracted) */
	zx_stock_apply_block(eth, "PON_TAIL",
		ZX_STOCK_OPS_PON_TAIL_START, ZX_STOCK_OPS_PON_TAIL_END);
	zx_npp_twin_init(eth);  /* NPP twin pairs 0/1, 2/3, 6/7 — Phase 9f (extracted) */
	zx_stock_apply_block(eth, "NPP",
		ZX_STOCK_OPS_NPP_START,      ZX_STOCK_OPS_NPP_END);
	zx_npp_aux_init(eth);  /* NPP_AUX — Phase 9c (extracted) */
	zx_tm_per_instance_init(eth);  /* TM 16x64-word tables — Phase 9d (extracted) */
	zx_stock_apply_block(eth, "TM",
		ZX_STOCK_OPS_TM_START,       ZX_STOCK_OPS_TM_END);
	zx_stock_apply_block(eth, "PP_FUC",
		ZX_STOCK_OPS_PP_FUC_START,   ZX_STOCK_OPS_PP_FUC_END);

	/* Phase 14: kick PHY power-up (LDO + TX DAC) on all GePHYs. */
	zx_eth_init_phys(dev);

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
	/* Stock live dump 2026-05-24 shows all 8 ports have isolation masks:
	 *   port 0..5: mask = ~(1<<port) & 0xff  (no-self-loop, e.g. port0=0xfe)
	 *   port 6,7 (CPU): mask = 0xff (block ALL egress via this register)
	 * Stock pon_pp_brg_init only OR's 0xdf into ports 6,7 — the rest is HW
	 * default. Our mainline likely has HW default = 0 (no isolation), so
	 * we must explicitly set the no-self-loop masks for 0..5 too. */
	for (i = 0; i < 6; i++)
		zx_port_isolate(eth, i, (u8)(~(1u << i) & 0xff));
	zx_port_isolate(eth, 6, 0xFF);  /* CPU port: was 0xDF, but stock state shows bit 5 also set → 0xff */
	zx_port_isolate(eth, 7, 0xFF);
	dev_info(dev, "isolate ports 0..7 = %#x %#x %#x %#x %#x %#x %#x %#x\n",
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(0)),
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(1)),
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(2)),
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(3)),
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(4)),
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(5)),
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

		/* fpga.bin bulk replay was disabled in Phase 5g (2026-05-24) and
		 * removed entirely in refactor #38 Phase 4 (2026-05-26). The dead
		 * #if ZX_BULK_REPLAY 0 path was ~80 lines of code behind a
		 * compile-time gate — never compiled in. Driver works fine
		 * without it (PING BIDI achieved without bulk replay). The
		 * fpga.bin blob is also deleted from the initramfs. See:
		 *   tasks/00.10.02.re-stock-kmods/findings/eth_init_flow_2026_05_26.md
		 * for the explicit init sequence we use instead. */

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

	/* 8. All replay images (cla/pm/stock) are now embedded — Phase 1+2+3.
	 *    No firmware images to release. */
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
