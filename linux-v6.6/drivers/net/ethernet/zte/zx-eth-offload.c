// SPDX-License-Identifier: GPL-2.0-only
/* Included from zx-eth-main.c — single translation unit. */

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

/* [Iter 20] Carved 64 MiB region at phys 0x4C000000. Stock kernel uses
 * mem=192M to hide this from the kernel allocator; we replicate via
 * reserved-memory DT + direct memremap_wc (bypassing dma_alloc_coherent
 * because the kernel doesn't manage this region — it's outside `mem=192M`).
 * Carved layout matches stock per agent 3 vmlinux RE:
 *   +0x00000000  BPPE table (16 KiB) + jumbo BPPE at +0x10000  <-- stock-exact
 *   +0x00020000  ACL RAM    (4 MiB, zeroed before BMU enable)
 *   +0x00420000  Flow RAM   (1 MiB, zeroed)
 *   +0x02C20000  BP buffer pool
 *   +0x03F1F000  TM RX desc ring
 *   +0x03FDF000  TM TX UP desc ring
 *   +0x03FEF000  TM TX DN desc ring
 *
 * [wedge #2 lead 2026-07-31] BPPE moved +0x02700000 -> +0x00000000 (stock's
 * exact address 0x4C000000; stock: bppe@carve+0, jumbo@+0x10000,
 * ACL@+0x20000, flow@+0x420000 — see static_analysis_vmlinux_platform_init.md
 * §5). It had been parked at +0x02700000 to coincide with the HW-dictated
 * PM/ACL carve base (0x4E700000 = fpga[0x3a0024]-0x20000), i.e. inside the
 * 128 KiB head that carve reserves ahead of the ACL table — which is exactly
 * what made zx_ft_pm_ext_init's full-span memset silently wipe the BP pool
 * every boot (fix #1b). carve+0..+0x20000 is otherwise unused (ACL starts at
 * +0x20000) and is precisely the size stock's BPPE region occupies, so this
 * both restores stock parity and permanently removes that overlap hazard.
 * It also tests whether the BMU DDR-prefetch engine has an address/window
 * constraint, which is the last untested explanation for bppe_cnt==0
 * (every value-parity write, re-prime edge, kick and cache-flush theory is
 * already refuted — findings/wifi_stage3_wedge_topcrm_axiqos_2026-07-31.md).
 */
#define CARVED_BASE_PHYS	0x4C000000UL
#define CARVED_SIZE		(64UL * 1024 * 1024)
#define CARVED_ACL_OFF		0x00020000UL
#define CARVED_ACL_SIZE		(4UL * 1024 * 1024)
#define CARVED_FLOW_OFF		0x00420000UL
#define CARVED_FLOW_SIZE	(1UL * 1024 * 1024)
#define CARVED_BPPE_OFF		0x00000000UL	/* stock-exact; see layout note */
#define CARVED_BP_OFF		0x02C20000UL
#define CARVED_RXDESC_OFF	0x03F1F000UL
#define CARVED_TXUP_OFF		0x03FDF000UL
#define CARVED_TXDN_OFF		0x03FEF000UL

static int zx_tm_alloc_pools(struct zx_eth *e)
{
	void __iomem *base;
	u16 *bppe;
	int i;

	/* memremap_wc the entire 64 MiB carved region. WC = write-combine,
	 * uncached. CPU writes go directly to DDR via the write buffer; HW
	 * DMA reads see fresh data without cache flush. Same model stock uses.
	 */
	base = memremap(CARVED_BASE_PHYS, CARVED_SIZE, MEMREMAP_WC);
	if (!base) {
		dev_err(e->dev, "memremap_wc(0x%lx, %lu MiB) failed\n",
			CARVED_BASE_PHYS, CARVED_SIZE / (1024 * 1024));
		return -ENOMEM;
	}
	e->carved_va = base;
	dev_dbg(e->dev, "carved region: phys 0x%lx + %lu MiB → va %p\n",
		 CARVED_BASE_PHYS, CARVED_SIZE / (1024 * 1024), base);

	/* Zero ACL RAM (4 MiB) — stock tm.ko aclRamInit equivalent. Without
	 * this the classifier rules match random data → frames misrouted.
	 * Also zero Flow RAM (1 MiB).
	 */
	memset_io(base + CARVED_ACL_OFF, 0, CARVED_ACL_SIZE);
	memset_io(base + CARVED_FLOW_OFF, 0, CARVED_FLOW_SIZE);
	/* [egress fix 2026-05-29] Zero the TX UP+DN descriptor rings (64 KiB each).
	 * Without this, stale DDR content with leftover VALID bits sits in the rings;
	 * HW auto-fetches those phantom descriptors and its DN produce pointer desyncs
	 * (observed tm[0x10068] high16 stuck at 0x13, never draining our real desc at
	 * slot 0). Stock's ring starts clean. */
	memset_io(base + CARVED_TXUP_OFF, 0, 0x10000);
	memset_io(base + CARVED_TXDN_OFF, 0, 0x10000);
	dev_dbg(e->dev, "carved: zeroed ACL RAM (4 MiB @+0x%lx) + Flow RAM (1 MiB @+0x%lx) + TX UP/DN rings\n",
		 CARVED_ACL_OFF, CARVED_FLOW_OFF);

	/* Pool entity layout: cpu (virt) = base + off; dma (phys) = CARVED + off. */
	e->bppe_cpu   = (void *)(base + CARVED_BPPE_OFF);
	e->bppe_dma   = CARVED_BASE_PHYS + CARVED_BPPE_OFF;
	e->bp_cpu     = (void *)(base + CARVED_BP_OFF);
	e->bp_dma     = CARVED_BASE_PHYS + CARVED_BP_OFF;
	e->rxdesc_cpu = (void *)(base + CARVED_RXDESC_OFF);
	e->rxdesc_dma = CARVED_BASE_PHYS + CARVED_RXDESC_OFF;
	/* RX ring 1 (DN/WAN): the HW derives it as the ring-0 region + 0x20000 (no
	 * separate base register — only TM[+0xF0] is programmed; stock queue_init
	 * RE). The DN/uplink (MAC4/WAN) ingress→CPU frames land here. Zero both rings
	 * (0x40000) so stale VALID/len bits don't make the scan deliver phantoms. */
	e->rxdesc_dn_cpu = (void *)(base + CARVED_RXDESC_OFF + 0x20000);
	e->rxdesc_dn_dma = CARVED_BASE_PHYS + CARVED_RXDESC_OFF + 0x20000;
	memset_io(base + CARVED_RXDESC_OFF, 0, 0x40000);
	e->txdesc_cpu = (void *)(base + CARVED_TXUP_OFF);
	e->txdesc_dma = CARVED_BASE_PHYS + CARVED_TXUP_OFF;
	e->dndesc_cpu = (void *)(base + CARVED_TXDN_OFF);
	e->dndesc_dma = CARVED_BASE_PHYS + CARVED_TXDN_OFF;
	e->tx_head = 0;
	spin_lock_init(&e->tm_tx_lock);
	spin_lock_init(&e->bmu_free_lock);
	e->bmu_free_credit = 0;

	/* Populate BPPE: stock writes byteswapped u16 indices 0..N-1.
	 * Each entry says "BP slot index". HW pulls these one at a time when
	 * RX needs a buffer. Verified vs stock pon_tm_bmu_init decomp:5694 —
	 * loop trace: bppe[0]=0, bppe[i]=bswap16(i) for all i.
	 */
	bppe = (u16 *)e->bppe_cpu;
	for (i = 0; i < TM_BPPE_POOL_SIZE; i++)
		bppe[i] = cpu_to_be16(i);
	/* [wedge fix #2] jumbo BPPE table at +0x10000 (stock layout), be16
	 * indices 0..TM_JUMBO_BPPE_POOL_SIZE-1 — stock primes a real jumbo
	 * pool (0x66 entries); mainline used to advertise an empty one. */
	bppe = (u16 *)((u8 *)e->bppe_cpu + 0x10000);
	for (i = 0; i < TM_JUMBO_BPPE_POOL_SIZE; i++)
		bppe[i] = cpu_to_be16(i);

	dev_dbg(e->dev, "TM pools (carved): bppe@%pad, bp@%pad, rxdesc@%pad, txup@%pad, txdn@%pad\n",
		 &e->bppe_dma, &e->bp_dma, &e->rxdesc_dma,
		 &e->txdesc_dma, &e->dndesc_dma);
	return 0;
}

static void zx_tm_free_pools(struct zx_eth *e)
{
	/* Carved region — single memremap; no per-block dma_free. */
	if (e->carved_va) {
		memunmap(e->carved_va);
		e->carved_va = NULL;
	}
	e->bppe_cpu = e->bp_cpu = e->rxdesc_cpu = e->txdesc_cpu = e->dndesc_cpu = NULL;
}

/* Five BMU instances at TM[0x8000 + N * 0x400] for N in 0..4. Stock
 * register snapshot + stock_table.h replay shows all five enabled with
 * identical config. The HW alloc engine routes per-port to whichever
 * instance services that port — if any instance is unconfigured, its
 * BPPE table is empty → "pool empty" alloc failure even when other
 * instances have buffers. Per bmu_protocol_deep_re.md candidate #1.
 *
 * All instances share the SAME bppe_dma / bp_dma (one CMA region
 * services them all). The BPPE_BASE/BP_BUFFER/BP_SIZE regs are at
 * GLOBAL TM offsets (0x00E8-0x00FC) — stock writes them once at
 * tm_base+0xE8..0xFC (plat decomp :5740-5742), NOT at per-instance
 * BMU sub-block offsets like 0x8000+. Verified live: per-instance
 * TM[0x80E8] does NOT accept writes (readback 0). Per-instance regs:
 *   base + 0x8000 BMU_INIT (enable)
 *   base + 0x8004 CTRL1
 *   base + 0x8008 CTRL2
 *   base + 0x8048 POOL_SIZE producer cursor
 *   base + 0x804C JUMBO_POOL_SIZE
 *   base + 0x8058 BUCKETS_M1
 *   base + 0x805C JUMBO_BUCK
 */
#define TM_NUM_BMU_INSTANCES   5

/* pon_tm_bmu_init equivalent — register pool addrs + sizes with BMU */
static void zx_tm_bmu_init(struct zx_eth *e)
{
	int inst;

	/* Disable BMU instance 0 — stock parity: pon_tm_bmu_init disables
	 * only instance 0 (tm_base+0x8000=0). All 5 instances share one
	 * engine; disabling instance 0 gates the entire BMU while config
	 * is written. Writing BPPE_BASE while the engine is running may
	 * latch a stale value internally.
	 */
	tm_write(e, TM_REG_BMU_INIT, 0);

	/* BPPE/BP base physical addresses — GLOBAL TM registers (one copy
	 * shared by all 5 instances). Stock writes them at tm_base+0xE8..0xFC
	 * (plat decomp :5740). The per-BMU sub-block TM[0x80E8] is NOT writable
	 * (verified live: writel→readback 0).
	 */
	tm_write(e, TM_REG_BPPE_BASE,       e->bppe_dma);
	tm_write(e, TM_REG_JUMBO_BPPE_BASE, e->bppe_dma + 0x10000);
	tm_write(e, TM_REG_BP_BUFFER_BASE,  e->bp_dma);
	tm_write(e, TM_REG_BP_JUMBO_BASE,   e->bp_dma);
	tm_write(e, TM_REG_BP_SIZE,
		 (TM_BP_SIZE & 0xFFFF) |
		 ((TM_JUMBO_BP_SIZE & 0xFFFF) << 16));

	for (inst = 0; inst < TM_NUM_BMU_INSTANCES; inst++) {
		u32 base = inst * TM_INSTANCE_STRIDE;

		/* BMU sub-block control regs (per-instance) */
		tm_write(e, base + TM_REG_BMU_CTRL,        0x104C040);
		tm_write(e, base + TM_REG_BMU_CTRL2,       0x104C040);

		/* BUCKETS_M1: stock formula (POOL_SIZE>>5)-1 */
		tm_write(e, base + TM_REG_BMU_BUCKETS_M1,  (TM_BPPE_POOL_SIZE >> 5) - 1);
		tm_write(e, base + TM_REG_BMU_JUMBO_BUCK,
			 (TM_JUMBO_BPPE_POOL_SIZE >> 5) - 1);
	}

	/* Stock parity: dma_cache_maint(bppe, 0x20000, 1) — full L1+L2 cache
	 * clean so the BMU DMA engine can read the BPPE table from DDR. Stock
	 * calls this unconditionally right before 0x8048/0x804c writes.
	 */
	__cpuc_flush_dcache_area(e->bppe_cpu, 0x20000);
	outer_clean_range(e->bppe_dma, e->bppe_dma + 0x20000);
	dma_wmb();

	/* Prime the producer cursors ONCE, instance 0 only — exact stock
	 * parity. Stock's pon_tm_bmu_init writes 0x8048/0x804c a single time
	 * (plat decomp :5694); all 5 instances share one engine.
	 */
	tm_write(e, TM_REG_BMU_POOL_SIZE,  TM_BPPE_POOL_SIZE << 16);
	tm_write(e, TM_REG_BMU_JUMBO_POOL, TM_JUMBO_BPPE_POOL_SIZE << 16);

	dev_dbg(e->dev, "TM BMU init: %d instances configured, pool_size=%d, bp_size=%d, bppe@%pad\n",
		 TM_NUM_BMU_INSTANCES, TM_BPPE_POOL_SIZE, TM_BP_SIZE,
		 &e->bppe_dma);
}

/* pon_tm_bmu_enable — turn on all 5 BMU instances. Without this they
 * stay idle.
 */
static void zx_tm_bmu_enable(struct zx_eth *e)
{
	int inst;

	for (inst = 0; inst < TM_NUM_BMU_INSTANCES; inst++) {
		u32 base = inst * TM_INSTANCE_STRIDE;

		tm_write(e, base + TM_REG_BMU_INIT, 1);
	}
	dev_dbg(e->dev, "TM BMU enabled (%d instances): tm[0x8000]=%#x tm[0x8400]=%#x tm[0x9000]=%#x\n",
		 TM_NUM_BMU_INSTANCES,
		 tm_read(e, TM_REG_BMU_INIT),
		 tm_read(e, 0x400 + TM_REG_BMU_INIT),
		 tm_read(e, 0x1000 + TM_REG_BMU_INIT));

	/* [wedge fix #2 2026-08-01] Populate the BMU pool by freeing every
	 * BPPE index. Stock has ~8112 entries; mainline's BMU DDR prefetch
	 * engine never auto-primes the pool (bppe_cnt stays 0 at
	 * TM[0x8080]), so the fabric survives on only the ~10-entry on-chip
	 * BPPI recycle margin. By freeing each BP index (0..POOL-1) into
	 * the BMU after enable, we manually build both the on-chip BPPI FIFO
	 * and the DDR BPPE free-list pool. The BPPI fills to its ~191-entry
	 * max first, then excess spills to BPPE, achieving stock parity
	 * (~8000 DDR entries). This eliminates the ~1k-frame endurance
	 * limit that gates ftwifi=1.
	 */
	{
		int i;

		for (i = 0; i < TM_BPPE_POOL_SIZE; i++)
			tm_write(e, TM_REG_BMU_FREE, (u32)i);
		dev_info(e->dev,
			 "[wedge fix #2] BMU pool primed: freed %d BPs, "
			 "bppe_cnt=%u bppi_cnt=%u\n",
			 TM_BPPE_POOL_SIZE,
			 tm_read(e, 0x8080), tm_read(e, 0x8088));
	}
}

/* Register a MAC as a CPU port destination in the ONU MAC table.
 * From stock spa_set_onu_mac_addr (in tm.ko, calls tmOnuRegWrite via spaRegTable).
 * Hardware: spaRegTable entries [0x16] + [0x17] target NPP+0x14120 + slot*8.
 * Layout per slot (8 bytes):
 *   +0: mac[2]<<24 | mac[3]<<16 | mac[4]<<8 | mac[5]
 *   +4: mac[0]<<8  | mac[1]                                    (low 16 bits)
 * When switch sees frame with dst_mac matching a slot → routes to CPU port.
 */
#define ZX_SPA_ONU_MAC_BASE	0x14120
/* SPA destination-MAC filter table ("trap_dmac"): 4 slots x 8 bytes at
 * NPP+0x141A0. Same byte layout as ONU-MAC. When a slot holds a device MAC,
 * the SPA parser sends frames with that dst_mac to the CPU (action_rsn
 * UDF_DMAC0) *before* the CLA forward hash, which prevents HW L3 forwarding of
 * routed to-me-MAC transit. Stock leaves this table EMPTY (it is populated only
 * on demand at runtime by tm_soft_protocol_dmac_set, never by init); the SoC
 * boot ROM, however, pre-loads it with the device MACs from fuses. We clear it
 * to match stock so routed transit reaches the CLA (first packet -> LOOK_UP_MISS
 * -> CPU routes, subsequent packets -> CLA HW forward). To-me management traffic
 * is unaffected: it reaches the CPU via the L3-local (dst-IP) path, not this
 * dst-MAC trap. See findings/trap_dmac_clear_HW_FORWARD_2026-06-28.md.
 */
#define ZX_SPA_TRAP_DMAC_BASE	0x141A0
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
 * cmd = idx | (ram_id << 22) | (rw << 27)
 */
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
	/* CMD-FIRST then data (descending) — matches stock pp_pm_set_*_ram_info
	 * (kotrace: X cmd then Y data_id 2,1,0) and the verified zx_pp_pm_set_cpu_mac.
	 * The old data-first order did NOT commit PM entries. */
	zx_pp_pm_set_cmd(e, 0, ram_id, ram_addr);
	for (i = 7; i >= 4; i--)
		writel(data[i], e->base + PP_PM_REG_DATA4 + (i - 4) * 4);
	for (i = 3; i >= 0; i--)
		writel(data[i], e->base + PP_PM_REG_DATA0 + i * 4);
	return 0;
}

/* Read an 8-word pp_pm RAM entry via the indirect iface (rw=1). */
static int zx_pp_pm_read_entry(struct zx_eth *e, u8 ram_id, u32 ram_addr,
			       u32 data[8])
{
	int i;

	if (zx_pp_pm_wait_done(e))
		return -EBUSY;
	zx_pp_pm_set_cmd(e, 1, ram_id, ram_addr);	/* rw=1 read */
	if (zx_pp_pm_wait_done(e))
		return -EBUSY;
	for (i = 0; i < 4; i++)
		data[i] = readl(e->base + PP_PM_REG_DATA0 + i * 4);
	for (i = 4; i < 8; i++)
		data[i] = readl(e->base + PP_PM_REG_DATA4 + (i - 4) * 4);
	return 0;
}

/* [H5 fix 2026-07-04] Write a PM indirect-RAM entry AND read-back-verify the
 * write actually committed, retrying up to ZX_PM_WR_RETRIES times.
 *
 * zx_pp_pm_write_entry() only waits for the engine DONE bit BEFORE issuing its
 * command; it never confirms the write's data landed. This indirect engine has
 * been observed to silently drop a write under contention -- the DSA side
 * needed the identical 8-iteration readback-retry loop against the same HW
 * (zx-dsa.c zx_pm_wr(), "the bare write was observed not to commit"). On the FT
 * install path a silently-dropped PM write arms a live CLA verdict pointing at
 * a stale/zero pm_slot, so the flow HW-forwards with the previous occupant's
 * next-hop MAC / NAT state (findings/qa_static_bughunt_2026-07-04.md H5).
 * Verify word0+word1 (enough to tell our payload from stale/zero -- every FT
 * PM entry has a nonzero, unique-per-slot word0: next_hop IP, flow_info descr,
 * ram6 sub=pm_slot>=8, ram3 cmd=0x00800000) and retry; return -EIO on
 * persistent mismatch so the caller fails the install cleanly (rollback via
 * zx_ft_uninstall). MUST be called with zx_hwlock held -- same as the bare
 * write it wraps; it issues both a write and a read on the shared PM engine. */
#define ZX_PM_WR_RETRIES 8
static int zx_pp_pm_write_verify(struct zx_eth *e, u8 ram_id, u32 ram_addr,
				 const u32 data[8])
{
	u32 rb[8];
	int try, rc;

	for (try = 0; try < ZX_PM_WR_RETRIES; try++) {
		rc = zx_pp_pm_write_entry(e, ram_id, ram_addr, data);
		if (rc)
			continue;	/* engine busy pre-write -- retry */
		rc = zx_pp_pm_read_entry(e, ram_id, ram_addr, rb);
		if (rc)
			continue;	/* engine busy pre-read -- retry */
		if (rb[0] == data[0] && rb[1] == data[1]) {
			e->ft_pm_verify_ok++;
			if (try) {
				e->ft_pm_verify_retry++;
				dev_info(e->dev,
					 "[phase6/ft] pm_write ram%u[%#x] committed after %d retr%s\n",
					 ram_id, ram_addr, try, try == 1 ? "y" : "ies");
			}
			return 0;
		}
		dev_warn(e->dev,
			 "[phase6/ft] pm_write ram%u[%#x] try%d NOT committed: wrote %08x %08x readback %08x %08x\n",
			 ram_id, ram_addr, try, data[0], data[1], rb[0], rb[1]);
	}
	e->ft_pm_verify_fail++;
	dev_warn(e->dev,
		 "[phase6/ft] pm_write ram%u[%#x] FAILED to commit after %d tries -- failing install\n",
		 ram_id, ram_addr, ZX_PM_WR_RETRIES);
	return rc ? rc : -EIO;
}

/* ---- PM-ops bridge to the built-in DSA flow-offload binder ----
 *
 * The binder (zx-dsa.c, built-in) cannot commit PM RAM through its own ioremap;
 * the conduit's zx_pp_pm_write_entry/read_entry (via e->base) provably do. We
 * register a {write,read} pair the binder calls. Capture `e` in a module-global
 * set at probe (single instance — like zx_bmu_dump_eth above). */
static struct zx_eth *zx_pm_ops_eth;

static int zx_pm_ops_write(u8 ram_id, u32 addr, const u32 d[8])
{
	if (!zx_pm_ops_eth)
		return -ENODEV;
	return zx_pp_pm_write_entry(zx_pm_ops_eth, ram_id, addr, d);
}

static int zx_pm_ops_read(u8 ram_id, u32 addr, u32 d[8])
{
	if (!zx_pm_ops_eth)
		return -ENODEV;
	return zx_pp_pm_read_entry(zx_pm_ops_eth, ram_id, addr, d);
}

static struct zx_pm_ops zx_eth_pm_ops = {
	.write = zx_pm_ops_write,
	.read  = zx_pm_ops_read,
};

/* Replay all pp_pm entries dumped from stock (ram=3 default flow_info
 * + ram=6 global). Embedded static C array — see zx_pm_table.h for the
 * regeneration command.
 */
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
	dev_dbg(e->dev, "pp_pm init: %u ok, %u fail (%u embedded)\n",
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
	dev_dbg(e->dev, "pp_pm CPU MAC ram[%u] = %pM (data1=%#x data0=%#x)\n",
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
 * ============================================================
 */
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
 * Per RE: write data first, then cmd with rw=0 triggers commit.
 */
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

/* CLA HASH write (ram2-6 + ram1 per the FFE hardfast install). Per the live stock
 * kotrace of cla_set_hash_table → cla_set_indirect_rw_cmd + cla_set_indirect_rw_data
 * (Phase 6, findings/phase6_stock_hardfast_trace.md): the WRITE protocol is
 *   (1) CMD(rw=0, ram_id, addr)  FIRST  — arms the slot,
 *   (2) then write the data words in DESCENDING data_id order (word[n-1]..word[0]).
 * This differs from zx_cla_write_entry (data-first, ascending) which only commits
 * word0 for the hash rams. nwords = 15 for ram2-6 hash, 17 for ram1. */
static int zx_cla_write_hash(struct zx_eth *e, u8 ram_id, u32 ram_addr,
			     const u32 *data, int nwords)
{
	int i;

	if (zx_cla_wait_done(e))
		return -EBUSY;
	writel(ram_addr | ((u32)ram_id << 22), e->base + CLA_REG_CMD); /* CMD first, rw=0 */
	for (i = nwords - 1; i >= 0; i--)
		writel(data[i], e->base + CLA_REG_DATA0 + i * 4);
	return zx_cla_wait_done(e);
}

/* CLA HW hash engine (Phase 6, VERIFIED on mainline 2026-06-04). Write the 12-word
 * (45-byte) flow key to HASH_KEY0.., pulse the trigger, read the 16-bit raw hash. The
 * HW computes the same 4-poly CRC as the SW cla_acl_hash_addr_gen — so we get the slot
 * the chip itself will use on ingress, with NO SW CRC reimpl and NO engine init (the
 * block is live out of reset). The caller masks the raw hash to a ram2-6 slot
 * (mask = (0x400<<(6-ACL_OUT_SPACE_SEL))-1, + way bits + free-slot probe).
 * GOTCHA: load the key FIRST, trigger LAST (HASH_TRIG is a control reg, not key data;
 * triggering before the key is loaded yields 0). See
 * findings/phase6_cla_hw_hash_CRACKED.md + memory zte-cla-hw-hash-engine. */
#define CLA_HASH_TRIG		0x1CC2C0	/* fpga 0xe30b0 — write 1 to latch+compute */
#define CLA_HASH_KEY0		0x1CC2C4	/* fpga 0xe30b1 — 12 key words, stride 4 */
#define CLA_HASH_OUT		0x1CC2FC	/* fpga 0xe30bf — 16-bit raw hash result */

static u16 zx_cla_hash_raw(struct zx_eth *e, const u32 key[12])
{
	int i;

	for (i = 0; i < 12; i++)
		writel(key[i], e->base + CLA_HASH_KEY0 + i * 4);
	writel(1, e->base + CLA_HASH_TRIG);	/* trigger AFTER loading the key */
	return readl(e->base + CLA_HASH_OUT) & 0xffff;
}

/* Indirect READ of one CLA RAM entry (17 words). Mirror of zx_cla_write_entry
 * with the CLA_RAM_READ bit set: write the cmd (rw=1), wait done, read DATA0..16.
 * Debug-only — used by the cladump/clapeek debugfs to compare per-port classify
 * state (e.g. why port1 ingress isn't trapped to CPU while port0/2/3 are).
 */
static int zx_cla_read_entry(struct zx_eth *e, u8 ram_id, u32 ram_addr, u32 data[17])
{
	int i;

	if (zx_cla_wait_done(e))
		return -EBUSY;
	writel(ram_addr | ((u32)ram_id << 22) | CLA_RAM_READ, e->base + CLA_REG_CMD);
	if (zx_cla_wait_done(e))
		return -EBUSY;
	/* NOTE (2026-06-01): this back-to-back indirect read returns data[1..16]
	 * correctly but data[0] (word0) is OFFSET BY ONE ENTRY — readback word0 of
	 * the entry at addr A actually yields the NEXT entry's word0 (verified 7/7
	 * vs zx_cla_table.h: read[A].word0 == table[A+1].word0). Stock's fpga path
	 * does not show this (its CMD and data reads are ms apart). The STORED data
	 * is correct; only this tool's word0 read is shifted. Don't trust word0 from
	 * a single read — cross-check via the previous entry, or use stock fpga. */
	for (i = 0; i < 17; i++)
		data[i] = readl(e->base + CLA_REG_DATA0 + i * 4);
	return 0;
}

/* CLA RAM init: walk a captured (ram_id, addr, 17-word payload) array
 * and write each one through the CLA command register sequence. Static
 * embedded data — no firmware_request — see zx_cla_table.h header for
 * the regeneration command.
 */
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
	dev_dbg(e->dev, "CLA init: %u ok, %u fail (%u embedded + ram=7 0..%d)\n",
		 ok, fail, ZX_CLA_INIT_TABLE_LEN, ZX_CLA_RAM7_LAST);
}

/* ===================================================================
 * Phase 6 — FFE extract-infrastructure init (zx_cla_ffe_extract_init).
 *
 * Ports the stock tm_acl_fast_init / tm_acl_l2_fast_init /
 * tm_acl_3tuple_fast_init one-time setup: write the CLA ram1 extract
 * RULES (5-tuple/3-tuple window descriptors) + the ram0 extract-INDEX
 * tables (with the index_valid "fast-enable" bits). Without this the CLA
 * has no extract rules, cannot compute the 5-tuple hash, and traps every
 * routed flow to the CPU. See zx_ffe_table.h header for full provenance.
 *
 * The table is verified byte-exact against the live stock CLA dump. Each
 * ram1 rule is 17 words (zx_cla_write_hash ram_id=1), each ram0 index is 5
 * words (zx_cla_write_hash ram_id=0) — both CMD-first + descending.
 * ===================================================================
 */
#include "zx_ffe_table.h"

static void zx_cla_ffe_extract_init(struct zx_eth *e)
{
	u32 ok = 0, fail = 0, i;

	/* ram1 extract rules first (the window descriptors the index points at) */
	for (i = 0; i < ARRAY_SIZE(zx_ffe_rules); i++) {
		if (zx_cla_write_hash(e, 1, zx_ffe_rules[i].id,
				      zx_ffe_rules[i].w, 17) == 0)
			ok++;
		else
			fail++;
	}
	/* ram0 extract-index tables (carry the index_valid fast-enable bits) */
	for (i = 0; i < ARRAY_SIZE(zx_ffe_index); i++) {
		if (zx_cla_write_hash(e, 0, zx_ffe_index[i].id,
				      zx_ffe_index[i].w, 5) == 0)
			ok++;
		else
			fail++;
	}
	dev_dbg(e->dev,
		 "CLA FFE extract init: %u ok, %u fail (%zu ram1 rules + %zu ram0 index)\n",
		 ok, fail, ARRAY_SIZE(zx_ffe_rules), ARRAY_SIZE(zx_ffe_index));
}

/* ===================================================================
 * Phase 6 / Workstream B — HW flow-offload binder (conduit side).
 *
 * The conduit netdev (idm0/idm1) is the DSA conduit master. DSA delegates the
 * nf_flow_table / conntrack HW-offload path (TC_SETUP_FT) to the conduit master's
 * ndo_setup_tc (net/dsa/slave.c dsa_slave_setup_tc), which previously dead-ended at
 * -EOPNOTSUPP. We now bind a flow_block_cb that handles TC_SETUP_CLSFLOWER and
 * writes the PROVEN HW L3-forward recipe (CLA ram2 5-tuple entry brute-filled to all
 * 520 hash buckets + PM ram1 next-hop + ram0 flow_info + ram6 sub_ram + ram3 cmd_ram),
 * mirroring the DSA-side zx-dsa.c binder but using the conduit's own CLA/PM helpers.
 * findings: trap_dmac_clear_HW_FORWARD_2026-06-28 + ffe_install_port_spec_2026-06-24.
 * ===================================================================
 */
/* Per-(flow,direction) PM slot allocation. The old design wrote flow_info /
 * next-hop / sub_ram / cmd_ram all at the single hardcoded slot 5 for EVERY flow
 * and BOTH directions, so a bidirectional NAT flow's UP entry (next-hop = modem
 * MAC, egress WAN) and DN entry (next-hop = client MAC, egress lan2) clobbered each
 * other -> one direction always carried the wrong next-hop -> trapped to SW -> the
 * download crawled. Each direction is a distinct tc cookie, so a distinct PM slot
 * per tracked ft_flows[] entry gives a distinct slot per direction automatically.
 * pm_slot = ZX_FT_PM_BASE + tracking-index (base>0 avoids slot 0; 32 flows ->
 * slots 8..39, well within PM ram0/1/6/3's ~0x400 addresses). */
#define ZX_FT_PM_BASE		8

/* The WAN/RGMII regport (lan4 = MAC4 = the modem uplink). WAN-ingress packets
 * (the DN/reply direction of a routed flow) extract the CLA hash key with an extra
 * bit set at key position 32 (kb[4] bit0, one bit below the proto field at base
 * bit 33); GePHY LAN-ingress packets do not. The key builder must set that bit for
 * the entry whose matching packets ingress the WAN, or the entry lands at the wrong
 * hash bucket and WAN-ingress data MISSES (findings/wan_ingress_data_hitrate). */
#define ZX_WAN_REGPORT		5

/* [Stage-3 WiFi UP 2026-07-28] Flow-key header byte (key word0 byte3 =
 * ex_rule_id >> 1). The CLA extract rule is selected per INGRESS group and is
 * baked into the hashed key, so the installer must build the key (and the
 * entry's extr_index) for the rule the flow's ingress port actually
 * classifies under: eth ingress (GePHY LAN + WAN/RGMII) = group 9 = rule
 * 0x90; fabric ingress = per-inport group 6/7 = rule 0x60 (idm0) / 0x70
 * (idm1). findings/wifi_stage3_up_cla_keymiss_forensics_2026-07-28.md. */
#define ZX_FT_KEY_HDR_ETH	0x48	/* rule 0x90 >> 1 */
#define ZX_FT_KEY_HDR_IDM(idm)	(0x30 | (((idm) & 1) << 3))	/* 0x60/0x70 >> 1 */

/* Build the 15-word CLA ram2 forward entry for the 5-tuple (byte-exact reproduction
 * of the HW-validated forwarding entries; see zx-dsa.c zx_cla_pack_entry).
 * flow_id = the PM flow_info slot this entry's cmd_flow_id must point at.
 *
 * [up-hwoffload 2026-07-04] cmd_flow_id is a 15-bit HW field split across TWO
 * entry bytes (findings/stock_red_drain_up_RE_2026-07-04.md CANDIDATE 2, RE'd
 * from decomp_all_tm.c tm_acl_get_fastHashRule):
 *   entry_byte[3] (this word's bits[31:24]) = ((idx & 0x7f) << 1) | 1   (LOW 7 bits)
 *   entry_byte[4] (next word's bits[7:0])   = (idx >> 7) & 0xff        (HIGH bits)
 *   => decoded cmd_flow_id = (byte3 >> 1) | (byte4 << 7)
 * The PM engine fetches flow_info from ram0[cmd_flow_id | dir<<10] (dir: UP=0,
 * DN=1) when cmd_flow_id < 0x400, else from an EXTERNAL DDR table.
 *
 * The OLD packing (still used for DN below) hardcoded byte3=0x03 (decodes to a
 * constant low-bits=1) and put flow_id in byte4 (the HIGH bits) — so EVERY
 * entry decoded to cmd_flow_id = flow_id*128+1. For DN (flow_id/pm_slot >= 8)
 * that is always >=0x400 -> EXTERNAL DDR fetch, which zx_ft_ext_flow_write also
 * populates at that exact block -> DN works, by coincidence of two matched
 * "bugs" (see the finding). For UP the same formula resolves the SAME
 * cmd_flow_id, but nothing was ever written to that DDR block for the UP
 * direction's values -> the HW fetches erased/zeroed flow_info -> UP
 * HW-forwarded frames egress with src IP 0.0.0.0 (verified on-device
 * 2026-07-04, up_observe.py baseline1: 17/34 UP frames src=0.0.0.0).
 *
 * FIX (up_idx_fix, UP direction only): pack cmd_flow_id = pm_slot directly
 * (byte3 = ((pm_slot&0x7f)<<1)|1, byte4 = pm_slot>>7 = 0 for pm_slot<128 —
 * true for all real slots, ZX_FT_PM_BASE=8..8+ZX_FT_MAX_FLOWS-1=39). Since
 * pm_slot < 0x400, the HW fetch resolves to INTERNAL ram0[pm_slot | 0<<10] =
 * ram0[pm_slot] for dir=UP(0) with NO shift — exactly the address
 * zx_ft_install_recipe already writes via zx_pp_pm_write_entry(e, 0, pm_slot,
 * fi) (that call previously landed on an address nothing ever fetched from).
 * DN keeps the OLD (proven, ~760 Mbps) packing untouched — lower risk than
 * also flipping its fetch to internal ram0. */
static void zx_ft_pack_cla(u32 cla[15], u8 ip_proto, __be32 saddr, __be32 daddr,
			   __be16 sport, __be16 dport, u8 flow_id, bool is_wan,
			   u8 eg_regport, bool up_idx_fix, u8 key_hdr)
{
	u32 s = ntohl(saddr), d = ntohl(daddr);
	u8 s0 = (s >> 24) & 0xff, s1 = (s >> 16) & 0xff, s2 = (s >> 8) & 0xff, s3 = s & 0xff;
	u8 d0 = (d >> 24) & 0xff, d1 = (d >> 16) & 0xff, d2 = (d >> 8) & 0xff, d3 = d & 0xff;
	u16 sp = ntohs(sport), dp = ntohs(dport);
	u8 idx_lo = up_idx_fix ? (u8)(((flow_id & 0x7f) << 1) | 1) : 0x03;
	u8 idx_hi = up_idx_fix ? (u8)((flow_id >> 7) & 0xff) : flow_id;

	/* word0 byte0x01 hi-nibble / byte0x02 = gemport_uni_id (the CLA action's egress
	 * port, in REGPORT space). With da_known=1 the classifier egresses the forwarded
	 * frame DIRECTLY to gemport_uni_id. Stock's DN entry carries the egress client's
	 * regport (e.g. 3 for a lan2 client); mainline HARDCODED 5 = the WAN regport, so
	 * every downstream (WAN-ingress) frame was misrouted to the WAN port instead of
	 * the LAN client. Verified on-device 2026-07-03: gemport_uni_id=5 -> desOut
	 * Outport=5 (WAN); gemport_uni_id=3 -> desOut Outport=3 (lan2), mac2_tx climbs.
	 * eg_regport is the egress port's regport (WAN=5 for the upload direction, the
	 * LAN client's regport for the download direction), so this is correct for BOTH
	 * directions and preserves the old 0x03005044 for WAN-egress (upload) flows.
	 * byte3 (bits31:24) is now the LOW 7 bits of cmd_flow_id (idx_lo), see above.
	 *
	 * [Stage-3 WiFi Phase C 2026-07-27] gemport_uni_id is a 12-BIT stored field
	 * spanning entry bytes 1-2 (stock decoder cla_set_hash_table,
	 * decomp_all_tm.c:3366-3550: gemport_uni_id = byte2<<4 | byte1>>4), i.e.
	 * cla[0] bits [15:12] (low nibble) + bits [23:16] (high byte). The old
	 * packing wrote only the low nibble — fine for eth regports 1-5, but a
	 * WiFi egress carries the WLAN logical port `essid = 0x10|(idm<<3)|ssid`
	 * (0x10-0x1f, Phase-A live stock correlation: gemport_uni_id=28=0x1c for
	 * an idm1/ssid4 client, outport left 0) whose bit4 was truncated. Packing
	 * the high bits is a no-op for every eth value (1-5 have no high bits). */
	cla[0] = ((u32)idx_lo << 24) | 0x000044 |
		 (((u32)eg_regport & 0xf) << 12) |	   /* gemport_uni_id[3:0]  */
		 ((((u32)eg_regport >> 4) & 0xff) << 16);  /* gemport_uni_id[11:4] */
	/* word1 bytes: [0x04]=idx_hi (HIGH bits of cmd_flow_id) [0x05]=0xc0(e8_en)
	 * [0x06]=0x11 [0x07]=0xfa. cmd_flow_id MUST equal the slot the recipe writes
	 * flow_info/next-hop to (mirror zx-dsa.c zx_cla_pack_entry); hardcoding 0 while
	 * PM was written at slot 5 pointed the CLA entry at the wrong next-hop. */
	cla[1] = (0xfau << 24) | (0x11u << 16) | (0xc0u << 8) | idx_hi;
	cla[2] = 0x00000608;
	/* word3 is NOT a valid bit — it is the high part of extr_index
	 * (extr_index = byte0x10<<4 | byte0xf>>4, cla_set_hash_table tm.c:3444).
	 * byte0x10=0x49 (word4) + byte0xf=0x00 (this word) => extr_index low byte 0x90,
	 * which MUST equal the ex_rule_id the HW classifies the flow under (rule 0x90).
	 * The stock-captured 0x80000000 made byte0xf=0x80 => extr_index 0x98 != 0x90 =>
	 * LOOK_UP_MISS on every packet (verified on-device 2026-07-02). Must be 0. */
	cla[3] = 0;
	/* byte0x10 = 0x49 = valid_en(bit6) + extr_index nibble(→rule 0x90). For the
	 * WAN/download-ingress entry ALSO set bit5 = `direct` (0x49→0x69) AND bit4 of
	 * byte0x12 = `da_known` (→ +0x00100000, giving cla[4]=0x00100069). The reference
	 * firmware sets BOTH on the download-direction (WAN-ingress) entry. da_known is
	 * part of the WAN-ingress key-COMPARE: a WAN/RGMII-ingress DN packet only matches
	 * a stored entry that has da_known=1 (verified on-device 2026-07-03: da_known=0
	 * content — even filled into all 520 buckets — MISSES; da_known=1 at the correct
	 * poly-0 slot HITS). `direct` alone (da_known=0) is necessary but NOT sufficient.
	 * LAN-ingress (upload) forwards without either, so gate both on is_wan. */
	/* [up-hwoffload 2026-07-04] `direct`+`da_known` are ALSO required on the UP
	 * (LAN-ingress, egress=WAN) entry, not just the WAN-ingress/DN one. The
	 * cmd_flow_id repack (up_idx_fix, idx=pm_slot -> internal ram0[pm_slot])
	 * alone was NOT sufficient: with it but WITHOUT these bits, UP frames still
	 * HW-forwarded (cla_up_fwd incremented) but egressed with src IP 0.0.0.0 —
	 * i.e. the CLA verdict fires and PICKS an egress port either way, but the
	 * PM/NAT-rewrite stage that reads flow_info/next_hop only actually RUNS
	 * when `direct`+`da_known` are set, regardless of which side ingressed.
	 * (The is_wan-only gating in the comment above documents da_known's
	 * WAN-ingress KEY-COMPARE role, which is a separate, additional need —
	 * it does not mean da_known is WAN-ingress-only for the rewrite stage.)
	 * Verified on-device 2026-07-04 (findings/up_hwoffload_2026-07-04.md):
	 * with both up_idx_fix AND this bit set, UP frames egress with the correct
	 * SNAT src IP and a sustained 6 GB + 4x1 GB (10 GB total, one boot)
	 * download completed at ~830-920 Mbps with qmg_up_trap staying 0 the
	 * entire time — no residual admission latch. */
	/* [Stage-3 WiFi UP 2026-07-28] byte0x10's low nibble is the extr_index
	 * rule-select nibble (extr_index low byte = key_hdr << 1): 0x9 for eth
	 * ingress (rule 0x90), 0x7/0x6 for fabric ingress (rule 0x70/0x60). The
	 * entry's extr_index must equal the packet's ex_rule_id or the compare
	 * fails even at the right bucket (2026-06-28 finding). key_hdr >> 3
	 * yields exactly that nibble (0x48>>3=9, 0x38>>3=7, 0x30>>3=6), so the
	 * eth cases below are byte-identical to the proven 0x69/0x49 values.
	 *
	 * FABRIC-ingress entries must NOT set `direct` (byte0x10 bit5): the
	 * fabric lookup's key-compare REJECTS direct=1 entries — proven live
	 * 2026-07-28 by fill520 sweeps with a byte-stable, model-exact key
	 * (rule select + key + all 520 buckets covered -> still 100%
	 * LOOK_UP_MISS; flipping ONLY direct 1->0 made the same entry match,
	 * and da_known=1+direct=0 fired the CLA forward verdict, cla_up_fwd
	 * == injections). da_known stays 1 (drives the PM rewrite stage). The
	 * eth UP/DN cases keep direct=1 (0x69) — required there (2026-07-04:
	 * WAN-ingress compare needs direct=1; eth-UP rewrite validated with
	 * it). */
	cla[4] = ((u32)ip_proto << 24) |
		 ((key_hdr != ZX_FT_KEY_HDR_ETH) ? (0x00100040u | (key_hdr >> 3)) :
		  (up_idx_fix || is_wan) ? (0x00100060u | (key_hdr >> 3))
					 : (0x00000040u | (key_hdr >> 3)));
	cla[5] = ((u32)s3 << 24) | ((u32)s0 << 16) | ((u32)s1 << 8);
	cla[6] = ((u32)d3 << 24) | ((u32)d0 << 16) | ((u32)d1 << 8) | s2;
	cla[7] = ((u32)(dp & 0xff) << 24) | ((u32)(sp >> 8) << 16) |
		 ((u32)(sp & 0xff) << 8) | d2;
	/* byte0x20 = dport HIGH byte. windata6 (CLA hash compare, tm.c:3433) = LE16 at
	 * 0x1f/0x20 = the live dport; the old constant 0x14 only matched dport 0x14xx and
	 * corrupted the key-compare for any other dport (verified on-device). */
	cla[8] = (u32)(dp >> 8) & 0xff;
	cla[9] = cla[10] = cla[11] = cla[12] = cla[13] = cla[14] = 0;
}

/* Build the flow's 12-word HW hash key (ex_rule_id 0x90 v4-5tuple extracted-key
 * form: word0=0x48000000, then {proto,srcHi,srcLo,dstHi,dstLo,sport,dport} bit-
 * packed at bit anchor 33+16*n, LE byte stream) and return its raw 16-bit hash.
 * Mirrors zx-dsa.c zx_cla_flow_hash.
 *
 * is_wan makes the key INGRESS-AWARE: WAN/RGMII-ingress packets (the DN/reply
 * direction of a routed flow, ingress lan4/MAC4) extract the key with kb[4] bit0
 * (key position 32, one bit below the proto field at base 33) SET; GePHY LAN
 * ingress leaves it 0. Setting it moves the entry to the bucket the WAN-ingress
 * extraction probes, so WAN-ingress DN data HITS instead of LOOK_UP_MISSing
 * (proven: driver key pos32=0 -> raw 0x7b38 = installed slot, but the live
 * WAN-ingress DN key pos32=1 -> raw 0x3e4e; findings/wan_ingress_data_hitrate). */
static void zx_ft_build_key(u32 key[12], u8 ip_proto, __be32 saddr,
			    __be32 daddr, __be16 sport, __be16 dport, bool is_wan,
			    u8 key_hdr)
{
	u32 s = ntohl(saddr), d = ntohl(daddr);
	u16 fields[7] = {
		ip_proto, (s >> 16) & 0xffff, s & 0xffff,
		(d >> 16) & 0xffff, d & 0xffff, ntohs(sport), ntohs(dport),
	};
	u8 kb[48] = {0};
	int n, i;

	/* [Stage-3 WiFi UP 2026-07-28] key word0 byte3 = ex_rule_id >> 1 (the
	 * latch decodes ex_rule_id = word0 >> 23). The HW bakes the SELECTED
	 * extract rule into the hashed header, and the rule is per-INGRESS-group:
	 * eth ingress classifies under group 9 -> rule 0x90 -> 0x48; fabric
	 * ingress under its per-inport group -> rule 0x70 (idm1) / 0x60 (idm0)
	 * -> 0x38 / 0x30 (live-verified byte-exact,
	 * findings/wifi_stage3_up_cla_keymiss_forensics_2026-07-28.md). */
	kb[3] = key_hdr;
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
}

static u16 zx_ft_flow_hash(struct zx_eth *e, u8 ip_proto, __be32 saddr,
			   __be32 daddr, __be16 sport, __be16 dport, bool is_wan,
			   u8 key_hdr)
{
	u32 key[12];

	zx_ft_build_key(key, ip_proto, saddr, daddr, sport, dport, is_wan,
			key_hdr);
	return zx_cla_hash_raw(e, key);
}

/* SW CRC-32 (poly 0x04C11DB7 = hash0_poly, init 0, MSB-first, no xorout) over the
 * reversed 45-byte flow key, masked to 16 bits — this reproduces stock's
 * cla_acl_hash_addr_gen(hash_mode=0). The CLA's PRIMARY ram2 way probes with
 * hash0_poly (=0x04C11DB7) for WAN/RGMII ingress, but the HW hash engine used by
 * zx_cla_hash_raw computes with poly1 (0x1EDC6F41) — so the driver's HW-hash slot
 * (poly1) is the WRONG ram2 slot for a WAN-ingress DN entry and the lookup MISSES.
 * The WAN-ingress DN entry must be installed at THIS poly-0 slot to be probed.
 * Verified on-device 2026-07-03: entry at the poly-0 slot HITS (acl_failed flat),
 * entry at the poly-1 slot MISSES 100% (1618/1618). */
static u16 zx_cla_hash_sw_poly0(const u32 key[12])
{
	u32 crc = 0;
	int b, i;

	for (b = 44; b >= 0; b--) {
		crc ^= (u32)((key[b >> 2] >> (8 * (b & 3))) & 0xff) << 24;
		for (i = 0; i < 8; i++)
			crc = (crc & 0x80000000) ? (crc << 1) ^ 0x04C11DB7
						 : (crc << 1);
	}
	return crc & 0xffff;
}

static u16 zx_ft_flow_hash_poly0(u8 ip_proto, __be32 saddr, __be32 daddr,
				 __be16 sport, __be16 dport, bool is_wan,
				 u8 key_hdr)
{
	u32 key[12];

	zx_ft_build_key(key, ip_proto, saddr, daddr, sport, dport, is_wan,
			key_hdr);
	return zx_cla_hash_sw_poly0(key);
}

/* The 5 per-flow way buckets (one per bank) for a raw hash. Mirrors
 * zx-dsa.c zx_cla_way_slots (the CLA hash lookup is multi-way; an entry must be in
 * every bank at the flow's hash — ram2 alone MISSES, verified on-device). */
static void zx_ft_way_slots(u16 raw, u8 ram[5], u16 addr[5])
{
	ram[0] = 2; addr[0] = raw & 0xff;
	ram[1] = 3; addr[1] = 0x100 + (raw & 0x7f);
	ram[2] = 4; addr[2] = 0x180 + (raw & 0x3f);
	ram[3] = 5; addr[3] = 0x1c0 + (raw & 0x3f);
	ram[4] = 6; addr[4] = 0x200 + (raw & 0x7);
}

/* Parsed NAT rewrite for one offloaded direction (from the flow's MANGLE actions).
 * A HW fast-flow is unidirectional: it rewrites exactly ONE L3 address (src for the
 * SNAT/upload half, dst for the DNAT/download half) plus optionally its L4 port. */
struct zx_ft_nat {
	bool   snat;		/* rewrite source IP (upload/SNAT half) */
	bool   dnat;		/* rewrite dest IP   (download/DNAT half) */
	bool   sport_set;	/* rewrite source L4 port */
	bool   dport_set;	/* rewrite dest L4 port */
	__be32 new_ip;		/* the ONE rewritten address (src if snat, dst if dnat) */
	u16    new_sport;	/* host-order replacement source port */
	u16    new_dport;	/* host-order replacement dest port */
};

/* Build the 3-word PM flow_info entry (ram_id 0). Field layout decoded from stock
 * pp_pm_set_flow_info (tm.c:18340) / findings/nat_offload_re: word0 = dmac_en(b0) |
 * nat_dport[17:2] | nat_sport[31:18]; word1 = nat_sport[15:14] | hl_ttl_en(b2) |
 * tcp_udp_chk_en(b3) | ip_chk_en(b4) | dport_en(b5) | sport_en(b6) | dip_en(b7) |
 * sip_en(b8) | subnet_id[12:9] | next_hop_idx[26:18].  NAT/DMAC/TTL/checksum are done
 * by these enable bits + the next_hop RAM (NOT by cmd_ram, which is VLAN/tunnel only).
 *
 * The old opaque constants (fi[0]=(0x0de8<<16)|slot; fi[1]=0x0014035c) were a byte-
 * copied stock capture that (a) hardcoded next_hop_idx=5 — an empty slot, so every
 * flow's DMAC was rewritten to 00:00:00:00:00:00 and the frame black-holed — and
 * (b) always set sip_en/sport_en (source rewrite) for BOTH directions, so the DNAT
 * (download) half never de-NAT'd the dest back to the LAN client. */
static void zx_ft_build_flow_info(u32 fi[8], const struct zx_ft_nat *n,
				  u16 next_hop_idx)
{
	bool rw = n->snat || n->dnat || n->sport_set || n->dport_set;
	u32 w0 = 0, w1 = 0;

	w0 |= 1u << 0;					/* dmac_en (next-hop MAC) */
	w0 |= ((u32)n->new_dport & 0xffff) << 2;	/* nat_dport[17:2]  */
	w0 |= ((u32)n->new_sport & 0x3fff) << 18;	/* nat_sport[31:18] */

	w1 |= ((u32)n->new_sport >> 14) & 0x3;		/* nat_sport[15:14] */
	w1 |= 1u << 2;					/* hl_ttl_en (routed transit) */
	if (rw)
		w1 |= 1u << 3;				/* tcp_udp_chk_en */
	/* ip_chk_en must accompany hl_ttl_en, not just NAT: the PM TTL edit
	 * leaves the IP checksum STALE unless bit4 folds it (same defect class
	 * as Phase-C R1, findings/wifi_stage3_phaseC_R1_validation; stock sets
	 * flow_info bit4). Proven live 2026-07-28 on a nat=fwd WiFi-UP flow:
	 * HW-forwarded frames reached the host wire with ttl 63 and
	 * `bad cksum (off by 0x100)` -> silently dropped by the receiver; DN
	 * only survived this because its frames pass the CPU dispatch, which
	 * repairs the csum in SW. Unconditional: any TTL-edited frame needs it. */
	w1 |= 1u << 4;					/* ip_chk_en */
	if (n->dport_set)
		w1 |= 1u << 5;				/* dport_en */
	if (n->sport_set)
		w1 |= 1u << 6;				/* sport_en */
	if (n->dnat)
		w1 |= 1u << 7;				/* dip_en */
	if (n->snat)
		w1 |= 1u << 8;				/* sip_en */
	w1 |= 1u << 9;					/* subnet_id = 1 (per stock capture) */
	w1 |= ((u32)next_hop_idx & 0x1ff) << 18;	/* next_hop_idx[26:18] */

	fi[0] = w0;
	fi[1] = w1;
	fi[2] = fi[3] = fi[4] = fi[5] = fi[6] = fi[7] = 0;
}

/* ---- PM EXTERNAL flow_info (the DDR tables the PM engine actually fetches) ----
 *
 * Geometry (from stock tm.ko pp_pm_set_external_flow_info + the static iotable:
 * carve mapped at virt 0xf1000000, acl @+0x20000 for 4 MiB, pm @+0x420000 for
 * 1 MiB; flow tables at (0xf140000 | dir?0x9c00:0x1c00 + idx)*0x10):
 *   carve + 0x41C000  dir-0 (upstream)  flow_info table, 0x8000 x 16 B
 *   carve + 0x49C000  dir-1 (downstream) flow_info table, 0x8000 x 16 B
 * Entry bytes = the canonical 9-byte flow_info REVERSED (entry[i] = fi_byte[8-i]).
 *
 * The fetch index measured on silicon (port-encoded fill, 2026-07-04):
 *   idx = cmd_flow_id * 128 + 1   for our TCP flows (cmd_flow_id = entry
 * byte 0x04 = pm_slot). The low 7 bits' origin is unproven (may be a per-packet
 * sub-field), so we ROBUSTLY fill the flow's whole 128-entry block (2 KiB) —
 * blocks are keyed by cmd_flow_id, which is unique per offloaded direction, so
 * blocks never collide. With the block resident the DN download HW-forwards
 * end-to-end at ~64-73 MB/s (~520-580 Mbps), DN CLA hit-rate ~99.997%.
 */
#define ZX_PM_EXT_SPAN		0x520000	/* acl 4M + pm 1M + 0x20000 head */
#define ZX_PM_EXT_FLOW_DIR0	0x41C000
#define ZX_PM_EXT_FLOW_DIR1	0x49C000
#define ZX_PONPP_PM_BASE_OFF	0x1e0020	/* 0x923a0020 - 0x921c0000 */
#define ZX_PONPP_ACL_BASE_OFF	0x1e0024	/* 0x923a0024 - 0x921c0000 */

static void zx_ft_ext_flow_write(struct zx_eth *e, bool wan_ing, u8 flow_id,
				 const u32 fi[8])
{
	u8 fb[12], ent[16] = {0};
	void __iomem *blk;
	int i;

	if (!e->pm_ext)
		return;
	for (i = 0; i < 12; i++)
		fb[i] = (fi[i >> 2] >> (8 * (i & 3))) & 0xff;	/* LE bytes */
	for (i = 0; i < 9; i++)
		ent[i] = fb[8 - i];
	blk = e->pm_ext + (wan_ing ? ZX_PM_EXT_FLOW_DIR1 : ZX_PM_EXT_FLOW_DIR0) +
	      (u32)flow_id * 128 * 16;
	for (i = 0; i < 128; i++)
		memcpy_toio(blk + i * 16, ent, 16);
}

/* Zero a flow's external block in BOTH direction tables (used on destroy;
 * also written on install for the direction we haven't proven, see caller). */
static void zx_ft_ext_flow_clear(struct zx_eth *e, u8 flow_id)
{
	u32 zero[8] = {0};

	zx_ft_ext_flow_write(e, false, flow_id, zero);
	zx_ft_ext_flow_write(e, true, flow_id, zero);
}

/* Write the proven recipe (PM tables + the CLA hash entry at the flow's own bucket
 * in all 5 way banks) for per-slot multi-flow coexistence. Returns raw hash or errno. */
static int zx_ft_install_recipe(struct zx_eth *e, u8 ip_proto, __be32 saddr,
				__be32 daddr, __be16 sport, __be16 dport,
				const u8 nh_mac[ETH_ALEN], u8 eg_regport,
				u16 pm_slot, const struct zx_ft_nat *nat,
				u8 key_hdr)
{
	u32 cla[15];
	u32 nh[8] = {0}, fi[8] = {0}, sub[8] = {0}, cmd[8] = {0};
	u8 ram[5];
	u16 addr[5];
	u16 raw;
	/* [Stage-3 WiFi UP 2026-07-28] key_hdr != ETH marks a flow whose
	 * matching packets ingress the FABRIC (a bound WiFi vif injecting via
	 * idm0/idm1): the key/extr_index are built for the fabric rule (key_hdr
	 * 0x30/0x38) and the key's pos32 WAN-ingress bit stays 0 (live-verified:
	 * fabric = 0, LAN-like). Callers only pass a fabric key_hdr for
	 * eg_regport == ZX_WAN_REGPORT (the UP direction), so the WAN-ingress
	 * branch below and fabric-keying are mutually exclusive. */
	int w, rc = 0;

	/* Without the external flow_info tables the PM rewrite reads erased
	 * DDR and mangles every HW-forwarded frame — refuse the offload so
	 * the flow stays on the (correct) SW path. */
	if (!e->pm_ext)
		return -EOPNOTSUPP;

	/* next_hop RAM (ram1): the ONE rewritten L3 address + the next-hop DMAC.
	 * For a NAT half that is the SNAT src / DNAT dst address (nat->new_ip);
	 * for a plain forward it is daddr (informational). */
	nh[0] = ntohl((nat->snat || nat->dnat) ? nat->new_ip : daddr);
	nh[1] = ((u32)nh_mac[2] << 24) | ((u32)nh_mac[3] << 16) |
		((u32)nh_mac[4] << 8) | nh_mac[5];
	nh[2] = ((u32)nh_mac[0] << 8) | nh_mac[1];
	/* [H5 fix] rc-check + readback-verify every PM write; on persistent
	 * failure abort so the caller (zx_ft_flower_replace / fttest) rolls the
	 * partial install back via zx_ft_uninstall and declines (stays SW)
	 * rather than arming a CLA verdict at a half-written pm_slot. */
	rc = zx_pp_pm_write_verify(e, 1, pm_slot, nh);
	if (rc)
		return rc;

	/* flow_info (ram0): per-direction rewrite-enable descriptor. next_hop_idx MUST
	 * be pm_slot (the slot we just wrote next_hop to) — the old code hardcoded 5.
	 * [up-hwoffload 2026-07-04] For the UP direction (eg_regport==WAN) this internal
	 * ram0[pm_slot] write is now the entry the HW ACTUALLY fetches from — see the
	 * up_idx_fix cmd_flow_id repack in zx_ft_pack_cla below (dir=UP=0, so the fetch
	 * address ram0[cmd_flow_id | 0<<10] == ram0[pm_slot], no shift needed). For DN
	 * this write is still unused (DN's cmd_flow_id resolves to the external DDR
	 * table instead) but harmless. */
	zx_ft_build_flow_info(fi, nat, pm_slot);
	rc = zx_pp_pm_write_verify(e, 0, pm_slot, fi);
	if (rc)
		return rc;

	/* The PM engine actually FETCHES flow_info from the EXTERNAL DDR table
	 * (see zx_ft_ext_flow_write) — without this every HW-forwarded frame is
	 * rewritten from erased DDR and black-holes. Write BOTH direction tables
	 * (dir-1 proven for WAN-ingress/DN; dir-0 unproven but harmless — the
	 * block is keyed by pm_slot, unique per offloaded direction). */
	zx_ft_ext_flow_write(e, true, pm_slot & 0xff, fi);
	zx_ft_ext_flow_write(e, false, pm_slot & 0xff, fi);

	sub[0] = pm_slot;				/* ram6 sub_ram -> ram3 cmd idx */
	rc = zx_pp_pm_write_verify(e, 6, pm_slot, sub);
	if (rc)
		return rc;

	cmd[0] = 0x00800000;				/* ram3 cmd: last_cmd=1 (no-op fwd) */
	rc = zx_pp_pm_write_verify(e, 3, pm_slot, cmd);
	if (rc)
		return rc;

	/* WAN-ingress (is_wan) = this entry's matching packets ingress the WAN/RGMII
	 * port, which for a routed flow is the direction that egresses toward a LAN
	 * port (eg_regport != WAN). Those packets extract the key with pos32=1 (hash)
	 * AND need the `direct` verdict bit set in the entry (see zx_ft_pack_cla).
	 * [up-hwoffload 2026-07-04] up_idx_fix = this entry's matching packets are the
	 * UP/ACK direction (egress toward WAN) — only THIS direction's cmd_flow_id is
	 * repacked to point at the internal ram0[pm_slot] flow_info; DN keeps the old
	 * (proven, external-DDR) packing untouched. */
	zx_ft_pack_cla(cla, ip_proto, saddr, daddr, sport, dport, pm_slot & 0xff,
		       eg_regport != ZX_WAN_REGPORT, eg_regport,
		       eg_regport == ZX_WAN_REGPORT, key_hdr);
	raw = zx_ft_flow_hash(e, ip_proto, saddr, daddr, sport, dport,
			      eg_regport != ZX_WAN_REGPORT, key_hdr);
	zx_ft_way_slots(raw, ram, addr);
	for (w = 0; w < 5; w++) {
		int r = zx_cla_write_hash(e, ram[w], addr[w], cla, 15);

		if (r)
			rc = r;
	}

	/* WAN-ingress (DN) entries: the CLA's primary ram2 way probes with hash0_poly
	 * (0x04C11DB7), NOT the poly1 (0x1EDC6F41) that the HW hash engine (raw above)
	 * computes — so ALSO install at the poly-0 ram2 slot, which is the slot the
	 * WAN/RGMII-ingress lookup actually consults. Without this the DN entry sits at
	 * the poly-1 slot and every WAN-ingress DN packet LOOK_UP_MISSes (acl_failed
	 * climbs 1:1, download traps→drops). Verified on-device 2026-07-03. */
	if (eg_regport != ZX_WAN_REGPORT) {
		u16 raw0 = zx_ft_flow_hash_poly0(ip_proto, saddr, daddr,
						 sport, dport, true, key_hdr);
		int r = zx_cla_write_hash(e, 2, raw0 & 0xff, cla, 15);

		if (r)
			rc = r;
		dev_info(e->dev,
			 "[phase6/ft] WAN-DN poly-0 install: raw0=0x%04x ram2[0x%02x] rc=%d\n",
			 raw0, raw0 & 0xff, r);
	}
	/* [Stage-3 WiFi UP 2026-07-28] FABRIC-ingress (wifi_ing) UP entries need
	 * NO poly-0 slot: the fabric lookup probes the poly-1 way set exactly
	 * like GePHY LAN ingress — proven live by zeroing the poly-0 slot under
	 * an active HW-forwarding upload (rate/hit-rate unchanged, acl_fail
	 * stayed flat). Only WAN/RGMII ingress (the DN branch above) consults
	 * the poly-0 ram2 slot. */

	dev_info(e->dev,
		 "[phase6/ft] recipe: proto=%u %pI4:%u->%pI4:%u eg_rp=%u wan_ing=%d nh=%pM pm_slot=%u nat=%s%s%s ip=%pI4 sp=%u dp=%u fi=%08x:%08x -> raw=0x%04x buckets ram2[0x%02x]/3[0x%03x]/4[0x%03x]/5[0x%03x]/6[0x%03x] rc=%d\n",
		 ip_proto, &saddr, ntohs(sport), &daddr, ntohs(dport),
		 eg_regport, eg_regport != ZX_WAN_REGPORT, nh_mac, pm_slot,
		 nat->snat ? "S" : "", nat->dnat ? "D" : "",
		 (nat->snat || nat->dnat) ? "" : "fwd", &nat->new_ip,
		 nat->new_sport, nat->new_dport, fi[0], fi[1], raw,
		 addr[0], addr[1], addr[2], addr[3], addr[4], rc);
	return rc ? rc : raw;
}

/* [H3 fix 2026-07-04] Shared rollback/unwind helper: clears the COMPLETE HW
 * footprint a single install of zx_ft_install_recipe() can have written for
 * one (raw, raw0, pm_slot) triple —
 *   - the 5 poly-1 way buckets derived from `raw` (zx_ft_way_slots: ram2-6),
 *   - the DN-only poly-0 ram2 bucket at `raw0 & 0xff` (when @has_raw0),
 *   - the PM EXTERNAL DDR flow_info block for pm_slot (both direction
 *     tables — zx_ft_ext_flow_clear already zeroes both),
 *   - the in-PM next_hop (ram1) and flow_info (ram0) entries for pm_slot.
 * (ram3/ram6 cmd/sub entries are deliberately NOT touched here — restoring
 * their pre-flow stock-replay defaults is a separate, pre-existing defect,
 * finding M3, out of scope for this fix.)
 *
 * This is THE single place that knows how to fully undo an install, used by:
 *   1. zx_ft_flow_reserve(), to clear the OLD raw/raw0's footprint before a
 *      self-REPLACE (same cookie, changed 5-tuple) adopts the new one —
 *      findings/qa_static_bughunt_2026-07-04.md H3(a) / H3a. Before this fix
 *      the old entry was left live and kept HW-forwarding the dead tuple
 *      forever (DESTROY only ever clears the CURRENT raw/raw0, never an
 *      in-place-replaced-away one).
 *   2. zx_ft_flower_replace(), to unwind a PARTIAL install (some but not all
 *      of the 5 way writes / the poly-0 write / the PM writes succeeded)
 *      when zx_ft_install_recipe() returns an error — H3(b). Safe to call
 *      unconditionally on every attempted (raw, raw0, pm_slot): every write
 *      it undoes is idempotent (re-zeroing an already-zero/never-written
 *      location is a no-op), so it doesn't matter which subset actually
 *      landed before the failure.
 *   3. zx_ft_flow_untrack(), as the single source of truth for what a clean
 *      DESTROY must clear (replaces the untrack-local zeroing that used to
 *      duplicate this logic ad hoc).
 * Returns 0, or the first nonzero CLA/PM write rc — ALL writes are still
 * attempted regardless (best-effort clear), matching the existing untrack
 * behavior of accumulating rc rather than aborting partway. */
static int zx_ft_uninstall(struct zx_eth *e, u16 raw, bool has_raw0, u16 raw0,
			   u16 pm_slot)
{
	u32 zero15[15] = {0};
	u32 zero8[8] = {0};
	u8 ram[5];
	u16 addr[5];
	int w, rc = 0, r;

	zx_ft_way_slots(raw, ram, addr);
	for (w = 0; w < 5; w++) {
		r = zx_cla_write_hash(e, ram[w], addr[w], zero15, 15);
		if (r)
			rc = r;
	}
	if (has_raw0) {
		r = zx_cla_write_hash(e, 2, raw0 & 0xff, zero15, 15);
		if (r)
			rc = r;
	}
	zx_ft_ext_flow_clear(e, pm_slot & 0xff);
	r = zx_pp_pm_write_entry(e, 0, pm_slot, zero8);	/* flow_info */
	if (r)
		rc = r;
	r = zx_pp_pm_write_entry(e, 1, pm_slot, zero8);	/* next_hop */
	if (r)
		rc = r;
	return rc;
}

/* Reserve a FT tracking slot at HW hash raw, recording {cookie, raw[, raw0]}
 * BEFORE the CLA entry is written so a declined offload leaves ft_flows[]/CLA
 * untouched:
 *   -EOPNOTSUPP  another tracked flow (different cookie) already owns raw's CLA
 *                way0 bucket (raw & 0xff = ram2 primary) -> reject (stay SW),
 *                never clobber; delete-either-kills-both is thus impossible.
 *                [C2 fix] Extended to the poly-0 ram2 bucket too: way0
 *                (raw & 0xff) and the DN-only poly-0 slot (raw0 & 0xff) are
 *                BOTH addresses in the same ram_id=2 space
 *                (zx_ft_install_recipe writes both), so a new flow's slot(s)
 *                must be checked against every tracked flow's raw&0xff AND
 *                raw0&0xff (when the tracked flow has one) -- not just
 *                raw&0xff vs raw&0xff. Without this, two DN flows whose
 *                raw&0xff differ but whose raw0&0xff coincide (~53%
 *                probability by 20 concurrent flows, birthday bound over 256
 *                buckets) both got admitted and the second install's poly-0
 *                write silently clobbered the first's WAN-ingress-facing
 *                entry (findings/qa_static_bughunt_2026-07-04.md C2 fail#2).
 *                [H2 fix] Also extended to the HIGHER way buckets (ram3/4/5/6
 *                -- zx_ft_way_slots' way index 1..4). Those banks fold `raw`
 *                into much smaller spaces than ram2's 256 (ram3=128, ram4/5=
 *                64, ram6=only 8) for up to ZX_FT_MAX_FLOWS=32 concurrent
 *                flows, so a distinct-raw&0xff pair can still share a ram6/
 *                ram3/4/5 bucket. zx_ft_flow_untrack unconditionally zeroes
 *                a destroyed flow's own 5 way buckets; if a live OTHER flow
 *                still maps to one of those higher-way buckets (raw&0xff
 *                differs, but e.g. raw&0x7 coincides), destroying flow A
 *                wipes flow B's higher-way entry out from under it (the
 *                driver's own model requires the entry "in every bank" --
 *                comment above zx_ft_way_slots) -- a cross-flow write with no
 *                install-time collision check to prevent it
 *                (findings/qa_static_bughunt_2026-07-04.md H2). Fixed the
 *                same way as C2: decline the new flow at reserve() time
 *                instead of sharing-then-clobbering, so untrack's unconditional
 *                5-way zero is provably safe -- no two tracked flows are ever
 *                admitted with any way address (index 0..4, any ram bank) in
 *                common, so no destroy can ever zero a bucket another live
 *                flow depends on.
 *   -ENOSPC      the tracking table is full and this cookie is not already known.
 * @has_raw0/@raw0: the caller's DN-only poly-0 hash (zx_ft_flow_hash_poly0),
 * mirroring exactly what zx_ft_install_recipe will write when eg_regport !=
 * ZX_WAN_REGPORT; pass has_raw0=false for UP-direction installs, eth and
 * WiFi-ingress alike (no poly-0 write happens for those — the fabric lookup
 * probes the poly-1 way set, proven live 2026-07-28).
 * Re-uses the slot on REPLACE (same cookie). On success records
 * {cookie,raw,raw0,has_raw0}, assigns a per-entry PM slot (ZX_FT_PM_BASE +
 * tracking-index -> distinct per direction, since each direction is a
 * distinct cookie/entry), returns it via *pm_slot, and returns 0. */
static int zx_ft_flow_reserve(struct zx_eth *e, unsigned long cookie, u16 raw,
			      bool has_raw0, u16 raw0, u16 *pm_slot)
{
	int i, self = -1, free = -1;
	/* [H2 fix] this flow's 5 way (ram,addr) pairs, computed once so every
	 * tracked flow below can be checked against all of them, not just
	 * way0 (ram2). */
	u8 ram[5], ram_t[5];
	u16 addr[5], addr_t[5];
	int w;

	zx_ft_way_slots(raw, ram, addr);

	for (i = 0; i < ZX_FT_MAX_FLOWS; i++) {
		if (!e->ft_flows[i].used) {
			if (free < 0)
				free = i;
			continue;
		}
		if (e->ft_flows[i].cookie == cookie) {
			self = i;
			continue;
		}
		/* [C2 fix] Each branch below logs a DISTINCT tag purely for
		 * testability (findings/fix_c2_poly0_2026-07-04.md /
		 * scratchpad/regress.py's poly0_stale test greps for
		 * "poly0" to confirm the NEW raw0-based checks -- not just
		 * the pre-existing way0-vs-way0 check -- actually fire and
		 * decline instead of clobbering). No behavior difference
		 * between branches; all four return -EOPNOTSUPP identically. */
		if ((e->ft_flows[i].raw & 0xff) == (raw & 0xff)) {
			dev_info(e->dev,
				 "[phase6/ft] reserve decline: way0 collision cookie=%lx raw=0x%04x vs tracked raw=0x%04x\n",
				 cookie, raw, e->ft_flows[i].raw);
			return -EOPNOTSUPP;	/* CLA way0 bucket collision */
		}
		if (has_raw0 && (raw0 & 0xff) == (e->ft_flows[i].raw & 0xff)) {
			dev_info(e->dev,
				 "[phase6/ft] reserve decline: poly0-vs-way0 collision cookie=%lx raw0=0x%04x vs tracked raw=0x%04x\n",
				 cookie, raw0, e->ft_flows[i].raw);
			return -EOPNOTSUPP;	/* new poly-0 vs tracked way0 */
		}
		if (e->ft_flows[i].has_raw0) {
			if ((raw & 0xff) == (e->ft_flows[i].raw0 & 0xff)) {
				dev_info(e->dev,
					 "[phase6/ft] reserve decline: way0-vs-poly0 collision cookie=%lx raw=0x%04x vs tracked raw0=0x%04x\n",
					 cookie, raw, e->ft_flows[i].raw0);
				return -EOPNOTSUPP;	/* new way0 vs tracked poly-0 */
			}
			if (has_raw0 &&
			    (raw0 & 0xff) == (e->ft_flows[i].raw0 & 0xff)) {
				dev_info(e->dev,
					 "[phase6/ft] reserve decline: poly0 collision cookie=%lx raw0=0x%04x vs tracked raw0=0x%04x\n",
					 cookie, raw0, e->ft_flows[i].raw0);
				return -EOPNOTSUPP;	/* poly-0 vs poly-0 */
			}
		}
		/* [H2 fix] Higher-way collision check (ram3/4/5/6, way index
		 * 1..4 -- way0/ram2 is already fully covered by the four checks
		 * above, so start at w=1 to avoid a redundant duplicate decline
		 * reason for the same bucket). ram[w]/ram_t[w] are always equal
		 * for a given w (zx_ft_way_slots maps way index -> ram bank
		 * unconditionally), so only the addr needs comparing. Distinct
		 * "higher-way" log tag purely for testability (regress.py's
		 * high_way_collision test greps for it to confirm this new
		 * check -- not just the pre-existing way0/poly0 checks --
		 * actually fires). */
		zx_ft_way_slots(e->ft_flows[i].raw, ram_t, addr_t);
		for (w = 1; w < 5; w++) {
			if (addr[w] != addr_t[w])
				continue;
			dev_info(e->dev,
				 "[phase6/ft] reserve decline: higher-way collision (ram%u addr=0x%03x) cookie=%lx raw=0x%04x vs tracked raw=0x%04x\n",
				 ram[w], addr[w], cookie, raw,
				 e->ft_flows[i].raw);
			return -EOPNOTSUPP;
		}
	}
	if (self >= 0) {			/* REPLACE existing cookie */
		/* Re-REPLACE of an identical live flow: nf_flow_table re-delivers
		 * FLOW_CLS_REPLACE continuously while the flow's OTHER direction
		 * rides the SW fast-path (every SW-forwarded packet sets
		 * NF_FLOW_HW_REFRESH -> nf_flow_offload_add re-queues). Our UP
		 * direction deliberately stays SW, so a live download suffers a
		 * re-REPLACE storm. Rewriting the live CLA buckets + PM slot +
		 * external flow_info block on every re-delivery is non-atomic
		 * under active HW lookup -> transient LOOK_UP_MISS trap bursts
		 * (measured 2026-07-04: ~12% of DN packets punted to SW, RED
