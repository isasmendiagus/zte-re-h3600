}

/* ============================================================
 *   BRG RAM indirect access — for FDB / VLAN tables
 *   (decoded from brg_ram_get/set RE)
 * ============================================================
 */

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
	/* Write in REVERSE order (D2 first, D0 last) — D0 commits.
	 * Per stock sbrg_set_indreg_wr (decomp_all_tm.c L8422): writes 0x4e
	 * (D2) → 0x4d (D1) → 0x4c (D0). Writing D0 first commits with stale
	 * D1/D2 → entry partially written → switch silently uses bad data.
	 */
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
 * NOT the hash sbrg_add_mactable uses.
 */
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
 * in wrong buckets across the whole table.
 */
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
 * Entry encoding matches stock sbrg_add_mactable
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
 * D2→D1→D0 (D0 last commits).
 */
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
	 * sbrg_hash (CCITT/XMODEM) didn't itself wedge RX.
	 */
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
	 * data, so save/restore them.
	 */
	{
		u32 save_d1 = d1, save_d2 = d2;
		u32 ex_d1, ex_d2;

		for (slot = 0; slot < 4; slot++) {
			if (zx_brg_ram_get(e, bucket, slot, &existing, &ex_d1, &ex_d2))
				return -EBUSY;
			/* Stock status nibble at d2 bits 31..28 = 0 → empty */
			if (((ex_d2 >> 28) & 0xf) == 0) {
				zx_brg_ram_set(e, bucket, slot, d0, save_d1, save_d2);
				dev_dbg(e->dev,
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
 *   Verified by independent review: zx_brg_ram_set above writes
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
 * ============================================================
 */

#define ZX_SBRAG_CMD	0x388814
#define ZX_SBRAG_BUSY	0x388818
#define ZX_SBRAG_D0	0x38881C
#define ZX_SBRAG_D1	0x388820
#define ZX_SBRAG_D2	0x388824

static int zx_sbrag_wait(struct zx_eth *e)
{
	int n = 100;

	/* BUSY bit0: 1 = operation in progress, 0 = idle/ready. Live-confirmed
	 * 2026-05-31: the register reads 0 at idle, so the old "wait for bit0==1"
	 * timed out immediately (returned -EBUSY before any write was issued) and
	 * every FDB write silently failed. Wait for IDLE instead. */
	while (n-- > 0) {
		if (!(readl(e->fpga_base + ZX_SBRAG_BUSY) & 1))
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
 * flood that produces RUN2+ DUP storms.
 */
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
	 * Approximate for now — collision just means linear-probe in sbrag (TODO).
	 */
	ram_addr = zx_crc16(mac, 6) & 0xfff;

	/* D2[7:0] is a PORT BITMAP in REGPORT space, NOT a raw port number
	 * (RE 2026-05-31 of stock sbrg_add_mactable + a live-learned entry whose
	 * D2 low byte read back 0x08 = BIT(3) = regport 3 = logical port 2). The
	 * logical DSA port must be remapped {0:1,1:2,2:3,3:4,4:5,5:0,6:6,7:7} and
	 * then encoded as BIT(regport). Writing the raw port number left unicast
	 * undirected → the switch kept flooding. */
	{
		static const u8 port_remap[8] = { 1, 2, 3, 4, 5, 0, 6, 7 };
		u32 regport = port_remap[port & 7];

		d2 = BIT(regport) | (mac_low_4 << 8);
	}
	d1 = ((status & 0xf) << 4)
	   | ((vlan >> 8) & 0xf)
	   | ((smac_ctrl & 1u) << 8)
	   | ((dmac_ctrl & 1u) << 9);
	d0 = (mac_low_4 >> 24)
	   | ((u32)(vlan & 0xfff) << 24)
	   | ((mac_high_2 & 0xffff) << 8);

	/* Write order RE-corrected 2026-05-31 via live poke + readback round-trip:
	 * the DATA words go FIRST (D2→D1→D0), THEN the CMD register commits the
	 * indirect write. The old order (CMD first, then data) did NOT store the
	 * entry — a readback returned garbage; data-then-CMD round-trips exactly
	 * (D2 read back the regport bitmap 0x08, etc.). */
	rc = zx_sbrag_wait(e);		/* wait for idle (BUSY bit0 == 0) */
	if (rc)
		return rc;
	writel(d2, e->fpga_base + ZX_SBRAG_D2);
	writel(d1, e->fpga_base + ZX_SBRAG_D1);
	writel(d0, e->fpga_base + ZX_SBRAG_D0);
	rc = zx_sbrag_set_cmd(e, 0, 0, mem_id, ram_addr);	/* commit */
	if (rc)
		return rc;
	rc = zx_sbrag_wait(e);		/* wait for completion */
	if (rc)
		return rc;
	dev_dbg(e->dev, "SBRAG add: %pM vlan=%u port=%u → mem_id=%u ram_addr=%u\n",
		 mac, vlan, port, mem_id, ram_addr);
	return 0;
}

/* Disable unknown-unicast flood for all ports except CPU.
 *
 * The big DUPs fix: when the switch can't find the
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
 * mask=0x000000ff shift=24 confirms the 8-bit field at top of the dword.
 */
static void zx_sbrg_set_unknown_unicast_flood_policy(struct zx_eth *e, u8 cpu_port_bitmap)
{
	void __iomem *pp = e->base + PP_OFF;
	u32 v_old = readl(pp + PP_BRG_PKTDEAL_FLOOD);
	/* PP[0x8340] holds TWO fields:
	 *   bits  8..23: sbragRegTable[0x35] PKTDEAL — 2 bits per port (8 ports).
	 *                Stock kotrace shows pktdeal=1 for every port → 0b01 in
	 *                each 2-bit slot → 0x5555 in bits 8..23.
	 *   bits 24..31: sbragRegTable[0x36] FWD — 1 bit per port (8 ports).
	 *                Stock kotrace: only port 5 (CPU) → 0x20.
	 * Earlier fix only touched FWD bits; PKTDEAL stayed at HW default
	 * (likely 0 = drop), which may have been worse than the missing FWD
	 * config. Stock writes BOTH; replay both in one read-modify-write.
	 */
	u32 pktdeal_all = 0x5555u;	/* every port: pktdeal=1 */
	u32 v = (v_old & 0x000000ffu) |
		(pktdeal_all << 8) |
		((u32)cpu_port_bitmap << 24);
	writel(v, pp + PP_BRG_PKTDEAL_FLOOD);
	dev_dbg(e->dev,
		 "SBRG flood policy: PP[0x8340] %08x -> %08x (pktdeal=0x%04x fwd_bitmap=0x%02x)\n",
		 v_old, v, pktdeal_all, cpu_port_bitmap);
}

/* Per-port isolation: bit pattern of ports this port may forward to.
 * Stock: port_isolate(6, 0xdf), port_isolate(7, 0xdf) for CPU/internal ports.
 */
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
 * mode field is positioned at (port*2 + 1) bits offset.
 */
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
 *   PON low-bank init
 *
 * Stock hits four identical PON sub-blocks at pon_early offsets
 * 0x00000, 0x10000, 0x20000, 0x30000 with the same 4-word pattern.
 *
 * The fourth word per block (0x44bef) is the only non-trivial value —
 * its semantics are not yet RE'd on the .ko side.
 * ============================================================
 */
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
 *   NPP twin-pair init
 *
 * NPP has three pairs of sub-blocks at stride 0x2000 that receive
 * bit-identical writes in stock — instances (0,1), (2,3), (6,7).
 * One payload per pair is kept in zx_npp_twin_data.h and applied to
 * both instance bases.
 *
 * The pair 6/7 payload at +0x280..+0x2bc holds an embedded Ethernet
 * frame template (dst MAC + IPv4/TCP) used by the HW classifier
 * autoreply path. It is environment-specific in the stock capture
 * (encodes the unit's connected-host MAC); preserved bit-for-bit
 * pending dynamic-construction RE.
 *
 * Instance 10 (96 writes at +0x14000) is not a twin pair and stays
 * in the generic zx_stock_apply_block("NPP") path.
 * ============================================================
 */
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
 *   PON_TAIL lookup RAM init
 *
 * The single biggest run in stock-init: 4082 contiguous writes at
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
 * ============================================================
 */
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
 *   TM per-instance table init
 *
 * Each of the 16 TM instances (0x180000 + i * 0x400) carries a
 * 64-word config table at +0x10240. The stock blob writes the
 * SAME 256-byte image into all 16 instances — verified bit-identical.
 *
 * High half of the first 16 words is DDR-backed (0x4ec____, 0x4ff____):
 * very likely default queue/buffer descriptor base pointers. The
 * later words look like small queue control / threshold bytes.
 * Exact semantics still un-RE'd; the bit pattern is preserved.
 *
 * Each instance also gets a fixed 7-word control-register write
 * (handled in the same loop body to keep the per-instance code in
 * one place).
 * ============================================================
 */
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

		/* 7 control regs identical across all 16 TM instances. */
		writel(0x00000140, tm_i + 0x000);  /* instance enable / mode? */
		writel(0x00000010, tm_i + 0x004);
		writel(0x4ff1f000, tm_i + 0x0f0);  /* DDR base pointer */
		writel(~(u32)TM_IRQ_ARM_BITS, tm_i + 0x104);  /* mask all but our IRQ bits */
		writel(0x03ffffff, tm_i + 0x124);
		writel(0x00001fff, tm_i + 0x12c);
		writel(0x001fffff, tm_i + 0x134);

		/* 64-word per-instance config table. */
		__iowrite32_copy(tm_i + 0x10240,
				 zx_tm_per_instance_init_data, 64);
	}
}

/*
 * PON_TAIL explicit register init — replaces 343 generic burst ops.
 */
static void zx_pon_tail_init_256x6(struct zx_eth *e)
{
	static const u32 p[6] = {
		0x000061a8, 0x000000c8, 0x0d820200,
		0x00000096, 0x000009c4, 0x00989680,
	};
	void __iomem *win = e->pon_early;
	int i, j;

	for (i = 0; i < 256; i++) {
		u32 off = 0xbffc0 - i * 0x400;
		for (j = 0; j < ARRAY_SIZE(p); j++)
			writel(p[j], win - off + j * 4);
	}
}

static void zx_pon_tail_init_16x4(struct zx_eth *e)
{
	static const u32 p[4] = { 0x00010001, 0x00020001, 0x00020001, 0x00010001, };
	void __iomem *win = e->pon_early;
	u32 base = 0xf7da8; int i, j;
	for (i = 0; i < 16; i++) {
		u32 off = base - i * 0x400;
		for (j = 0; j < ARRAY_SIZE(p); j++)
			writel(p[j], win - off + j * 4);
	}
}

static void zx_pon_tail_explicit_init(struct zx_eth *e)
{
	zx_pon_tail_init_256x6(e);
	zx_pon_tail_init_16x4(e);
}

static void zx_tm_explicit_bmu_bases(struct zx_eth *e)
{
	static const u32 p[6] = {
		0x4e700000, 0x4e710000, 0x4ff1f000,
		0x4ec20000, 0x4fe20000, 0x28000900,
	};
	int i, j;
	for (i = 0; i < TM_NUM_INSTANCES; i++) {
		void __iomem *tm = e->base + TM_OFF + i * TM_INSTANCE_STRIDE;
		for (j = 0; j < ARRAY_SIZE(p); j++)
			writel(p[j], tm + 0x4e8 + j * 4);
	}
}

static void zx_tm_explicit_red_queues(struct zx_eth *e)
{
	static const u32 p[40] = { [0 ... 39] = 0x000000ff, };
	int i, j;
	for (i = 0; i < TM_NUM_INSTANCES; i++) {
		void __iomem *tm = e->base + TM_OFF + i * TM_INSTANCE_STRIDE;
		for (j = 0; j < ARRAY_SIZE(p); j++)
			writel(p[j], tm + 0x4340 + j * 4);
	}
}

static void zx_tm_explicit_init(struct zx_eth *e)
{
	zx_tm_explicit_bmu_bases(e);
	zx_tm_explicit_red_queues(e);
}

/* ============================================================
 *   NPP_AUX init
 *
 * 13 NPP_AUX sub-blocks at base offsets 0xcc000, 0xd0000, 0xd4000, …,
 * 0xfc000 (stride 0x4000). Each gets the same 12-word init — verified
 * bit-identical across all 13 instances.
 *
 * What these registers are exactly is still un-RE'd; the values are
 * preserved bit-for-bit. The pattern alone tells us NPP has at least
 * 13 sub-units that need identical configuration.
 * ============================================================
 */
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
 *   Stock-init replay walker
 *
 * zx_stock_ops[] (zx_stock_bursts.h) holds the captured writes
 * pre-classified into two op kinds: contiguous +4 stride runs of
 * ≥4 entries become RUN ops backed by static const u32 arrays and
 * flushed via __iowrite32_copy(); everything else is a SINGLE op
 * (one writel()). Original order is preserved so the chip sees an
 * identical sequence of MMIO writes.
 *
 * The walker takes [start, end) over the ops array so explicit
 * named init helpers can be interleaved at the right point in the
 * init sequence by splitting the table into named ranges.
 * ============================================================
 */
static void zx_stock_apply_block(struct zx_eth *e, const char *name,
				 u32 start, u32 end)
{
	u32 i, runs = 0, singles = 0, regs_in_runs = 0, skipped_bmu = 0;

	for (i = start; i < end; i++) {
		const struct zx_stock_op *op = &zx_stock_ops[i];
		void __iomem *win = (op->window == ZX_BURST_WIN_PON_EARLY)
				    ? e->pon_early : e->base;

		/* [wedge fix #2 2026-07-31] SKIP the TM BMU sub-block
		 * (TM[0x8000..0x11ff] x5 instances = base window offsets
		 * 0x188000..0x1891ff). The captured stock table contains this
		 * block's RUNTIME state (HW-owned cursors 0x8040/44/48, status
		 * counters, AND the INIT=1 enables). Replaying INIT=1 here —
		 * BEFORE zx_tm_bmu_init has configured/primed anything — makes
		 * the virgin BMU engine latch an EMPTY producer state; the
		 * engine never re-samples the producer cursor on later INIT
		 * toggles (live-proven: every re-prime variant read back
		 * bppe_cnt=0), so the fabric ran forever on a ~15-buffer
		 * recycle margin instead of the 8192-BP pool. Skipping the
		 * range leaves zx_tm_bmu_init/zx_tm_bmu_enable as the FIRST
		 * toucher: a proper virgin-block 0->1 enable with a valid
		 * producer -> the pool actually produces (stock-parity
		 * bppe_cnt ~8112). */
		if (op->window == ZX_BURST_WIN_BASE &&
		    op->off_or_addr >= 0x188000 && op->off_or_addr < 0x189200) {
			skipped_bmu++;
			continue;
		}

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
	dev_dbg(e->dev,
		 "stock-init %s: %u ops (%u runs/%u regs + %u singles, %u BMU-block skipped)\n",
		 name, end - start, runs, regs_in_runs, singles, skipped_bmu);
}

/* ============================================================
 *   PP (Packet Processor) init — from pon_pp_*_init RE
 *
 * Without this the on-chip switch (SW) hands frames to PP but PP
 * doesn't elevate anything to NPP/IDM → CPU never sees RX.
 * Topology (from ZX279128S block diagram):
 *   RJ45 → GePHY → MAC[i] → SW → PP → DDR (via PP_AXI / IDM ring)
 * ============================================================
 */

/* [HW-FWD EXPERIMENT 2026-06-03, branch hw-bridge-offload] SPA per-entity pktdeal:
 * 0 = let the L2/SBRG engine decide (DA-lookup forwards LAN<->LAN in HW; ONU-MAC
 * match should still trap DA=our-MAC to CPU); 1 = old trap-all-to-CPU. Default 0
 * to test HW forwarding. Revert to 1 if it breaks CPU connectivity. */
static uint zx_spa_pktdeal;
module_param(zx_spa_pktdeal, uint, 0644);
MODULE_PARM_DESC(zx_spa_pktdeal, "SPA per-entity pktdeal (0=SBRG-forward/HW, 1=trap-to-CPU)");

/* [HW-FWD EXPERIMENT 2026-06-04, branch hw-ack-forward] per-protocol pktdeal.
 * The stock def_ptl_pkt_action table (zx_pp_pro_actions[]) sets deal=1 (TRAP) for
 * most protocol-type slots, which is why TCP control segments (ACKs) trap to the
 * CPU while bulk data HW-forwards. For a pure L2 bridge (our OpenWrt goal) we want
 * the SPA classifier to FORWARD every protocol slot (deal=0) so TCP HW-forwards
 * both directions like UDP — no per-protocol CPU trap. Frames addressed to the
 * device itself still reach the CPU via normal L2 (FDB / unknown-unicast flood,
 * cpu_port is in PP[0x8340] fwd bitmap). Set =0 to restore the stock trap table.
 * RE: tasks/00.10.02.re-stock-kmods/findings/decomp_halt_baddata_band.c
 *     (tm_port_protocol_pktdeal_set @ tm.ko 0x37340 -> SPA 0x921d4300[1:0]).
 * NEGATIVE RESULT (Iter AF, 2026-06-04): forward-all=1 BREAKS broadcast/ARP —
 * with every slot deal=0 the ARP/ND broadcasts arrive at the MAC (smac RX climbs)
 * but are neither flooded nor trapped to the CPU (tm_rx=0, hw_fwd=0), so the bridge
 * never learns/replies and ping is 100% loss. The stock trap table deliberately
 * traps broadcast/control to the CPU. The fix must be SURGICAL: flip only the
 * TCP-pure-ACK ptype slot to forward, leaving broadcast/control trapping. Default
 * therefore back to 0 (stock table = known-good 354 Mbit/s baseline). */
static uint zx_proto_fwd_all;
module_param(zx_proto_fwd_all, uint, 0644);
MODULE_PARM_DESC(zx_proto_fwd_all, "force all per-protocol pktdeal slots to FORWARD (1=HW-forward all incl TCP; 0=stock trap table)");

static void zx_pp_init(struct zx_eth *e)
{
	void __iomem *pp = e->base + PP_OFF;

	/* PP global config bank 0 (offsets 0x00–0x118) — verbatim replay of
	 * stock_eth.bin dump. These are what chip_tm_init / zte_api_pp_global_init
	 * leave the chip in. Without them PP silently drops CPU→switch packets.
	 */
	writel(0x00000001, pp + 0x0000);
	writel(0x02abfc8d, pp + 0x0004);	/* ⭐ PP enable / config word */
	writel(0x00000001, pp + 0x0008);
	writel(0x00640064, pp + 0x000c);
	writel(0x00000001, pp + 0x0010);
	writel(0x00000fff, pp + 0x0020);	/* port mask */
	writel(0x00000106, pp + 0x0024);
	writel(0x01070104, pp + 0x0028);
	writel(0x00000106 | PP_CPU_FWD_BIT, pp + 0x002c);	/* CPU FWD enabled (bit 25) */
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
	/* PP per-instance config replicated 4 times — stock dump showed
	 * the marker 0x242F0 at offsets 0x104, 0x504, 0x904, 0xD04 (Δ 0x400).
	 * Each instance has the same 7-word config block. Our prior code only wrote
	 * instance 0 → other 3 unprogrammed → possibly the missing TX wire-emit fix.
	 * See tasks/00.10.02.re-stock-kmods/findings/
	 */
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
	/* Note: stock leaves PP[+0x2c] = 0x00000106 on all 8 per-port blocks.
	 * Bit 25 (the `pp[0x2c] |= 1 << (lan_up_port + 0x19)` write in stock
	 * decomp) is conditional on lan_up != 0, which is not the boot path
	 * we exercise — so we deliberately do not set it here.
	 */

	/* pon_pp_brg_init — ALL values verified via live stock dump (not Ghidra
	 * decompile, which had printk strings cast as constants).
	 */
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

	/* === HW classifier + SPA CPU pktdeal config from stock kotrace ===
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
		dev_dbg(e->dev, "cla_oth_l3_act_cfg: PP+0x%x %#x -> %#x\n",
			 byte_off + ZX_FPGA_BASE_TO_NPP_OFF, cur, new_v);

		/* spa_set_enty_pktdeal_cfg(entity 0..7, slot 0x43..0x7d, val=1) — 8 × 59 = 472 writes.
		 * Stock kotrace shows 465 — slight diff likely from validation bounds.
		 * stride is in dwords; spaRegTable already encodes per-entity stride.
		 */
		/* [HW-FWD EXPERIMENT 2026-06-03, branch hw-bridge-offload] pktdeal value
		 * is module-param'd so we can test trap-all(=1) vs let-SBRG-forward(=0)
		 * without a re-edit. Default 0 = let the L2/SBRG engine decide (DA-lookup
		 * forwards LAN<->LAN in HW; ONU-MAC match should still trap DA=our-MAC to
		 * CPU). =1 restores the old trap-all-to-CPU. Goal: get QMG hw_fwd to climb
		 * (HW forwarding) while ping-to-device still works. */
		for (slot = 0x43; slot <= 0x7d; slot++) {
			ent = &zx_spa_table[slot];
			if (ent->mask == 0)
				continue;
			for (port = 0; port < 8; port++) {
				byte_off = (ent->base_dword + port * ent->stride) * 4
					   - ZX_FPGA_BASE_TO_NPP_OFF;
				cur = readl(e->base + byte_off);
				new_v = (cur & ~(ent->mask << ent->shift)) |
					((zx_spa_pktdeal & ent->mask) << ent->shift);
				writel(new_v, e->base + byte_off);
			}
		}
		dev_dbg(e->dev, "spa_enty_pktdeal_cfg: applied val=%u for entities 0..7 × slots 0x43..0x7d\n",
			 zx_spa_pktdeal);
	}

	/* PP_BRG port isolation table (pp+0x83C0..0x83DC) — exact stock values.
	 * Each port's mask = which OTHER ports it can FORWARD to (~self mask).
	 * Critical: port 5 (CPU) needs 0xDF to send to LAN ports 0..3.
	 * Without this, CPU→LAN packets get dropped by BRG isolation.
	 */
	writel(0x000000FE, pp + PP_BRG_BASE + 0x03C0);	/* port 0 -> all except self */
	writel(0x000000FD, pp + PP_BRG_BASE + 0x03C4);	/* port 1 */
	writel(0x000000FB, pp + PP_BRG_BASE + 0x03C8);	/* port 2 */
	writel(0x000000F7, pp + PP_BRG_BASE + 0x03CC);	/* port 3 */
	writel(0x000000EF, pp + PP_BRG_BASE + 0x03D0);	/* port 4 */
	writel(0x000000DF, pp + PP_BRG_BASE + 0x03D4);	/* port 5 CPU -> CRITICAL */
	writel(0x000000FF, pp + PP_BRG_BASE + 0x03D8);	/* port 6 */
	writel(0x000000FF, pp + PP_BRG_BASE + 0x03DC);	/* port 7 */

	/* [Stage-3 WiFi Phase B e2e, 2026-07-25] PP_BRG[0x008] VLAN-check
	 * enables — power-on default is 0x0000ff00 = outport_vl_chk_en[15:8]
	 * = 0xff, i.e. every bridge-FORWARD egress is VLAN-checked. Mainline
	 * populates NO VLAN tables, so the check fails for every bridged
	 * frame → drop_PP (0x921da040) +1/frame. Invisible on wire ports
	 * (their traffic rides the CLA per-inport catch-all traps, which
	 * bypass the bridge), but it silently killed ALL FORWARD-class
	 * unicast ingressing from the WiFi/ring fabric ports 6/7 — a real
	 * WLAN client associated + 4-way-handshaked fine (trap-class) and
	 * then had every IP packet eaten. Stock writes 0x0000dfdf here AND
	 * populates the VLAN tables; with no VLAN feature, all-checks-off
	 * is the faithful config. Root-caused live by regdump-vs-stock diff
	 * + poke; see findings/wifi_stage3_phaseB_e2e_realclient_2026-07-07.md.
	 * VALIDATED ON HW (live poke on #524): FORWARD-class ring-ingress
	 * frames then deliver fabric→TM-trap→dispatch→vif stack, pp_drop
	 * frozen. NOTE for the OPEN port1/jack2 drop_PP anomaly: this reg
	 * was never in the June port1 diff shortlists — retest jack2.
	 */
	writel(0x00000000, pp + PP_BRG_BASE + 0x0008);	/* vl_chk all OFF */

	/* SBRG (Switch Bridge) flood/forward enables — controls per-port
	 * broadcast/unicast/multicast forwarding decisions. RE'd from sbragRegTable:
	 *   pp_brg[0x300] = broadcast flood enable mask (8 ports, 1 bit each)
	 *   pp_brg[0x304] = pon broadcast flood inctrl mask
	 *   pp_brg[0x340] = unknown unicast pktdeal (2-bit per port, 16-bit mask)
	 *   pp_brg[0x2D4] = unknown multicast pktdeal
	 * Enable broadcast for all ports + CPU. Without this, CPU broadcasts
	 * (ARP, IPv6-ND) get dropped at the SBRG flood stage.
	 */
	writel(0x000000FF, pp + PP_BRG_BASE + 0x0300);	/* brdcst flood en: all 8 ports */
	writel(0x000000FF, pp + PP_BRG_BASE + 0x0304);	/* brdcst fwd en: all 8 ports */
}

/* ============================================================
 *   MAC init (per-port) — from smac_init() RE
 * ============================================================
 */

/* MAC_REG_CONTROL semantics (decomp of stock smac_init @ +0x13278):
 *   bits 0+1 (0x3) = MAC enable/running. Stock toggles via
 *                    pon_npp_smac_{enable,disable}_part_* on link state.
 *   bit 13 (0x2000) = gigabit mode (set by config_speed_duplex when 1Gbps).
 *   bit 14 (0x4000) = 100 Mbps mode.
 *   bit 15 (0x8000) = half-duplex / 10 Mbps mode.
 *   bit 19 (0x80000) = ??? — set unconditionally by stock smac_init,
 *                       never cleared anywhere in the decomp. Earlier
 *                       guess that "phy_int handler clears it on link up"
 *                       was a misread (it actually clears bit 13 via the
 *                       speed-duplex path; bit 19 stays set).
 *
 * Use stock's value 0xBAE003 verbatim — even for unused ports — and let
 * speed_duplex / enable_part_* adjust the lower bits as needed.
 *
 * MAC_REG_IRQ_MASK stock = 0xFFFF (smac_init). We used to write 0x3FFF
 * which leaves bits 14,15 masked; harmless but doesn't match stock.
 */
static void zx_smac_init_port(struct zx_eth *e, int port)
{
	void __iomem *mac = e->base + mac_off(port, 0);

	/* [egress fix 2026-05-29] Faithful port of U-Boot FUN_40e50c40 — the
	 * authoritative per-link MAC↔PHY serializer bring-up whose tail makes the
	 * SOPC↔MAC READY bit (0x19068 bit port+5) assert. The earlier [Iter21] port
	 * had two bugs that left the serializer unconfigured (so READY never bonded):
	 *   (1) it wrote 0x32/0xa8 to mac+0xC20/0xC50 — WRONG offsets. The decomp's
	 *       pointer base is 0x922000e0 (MAC+0xe0), so its "+0xc20/+0xc50" are
	 *       actually mac+0xD00 (tsf_mode/store-fwd) and mac+0xD30 (rsf_mode/flow);
	 *       AND it separately CLEARED bits in 0xD00/0xD30 instead of writing them.
	 *   (2) ctrl/mask used 0xBAE003/0xFFFF vs U-Boot's 0xBBE003/0xFFFE.
	 * (The +0xb00 write IS correct: decomp 0x92200070+0xa90 = mac+0xb00.) */
	writel(0x00bbe003, mac + MAC_REG_CONTROL);	/* npp[(port+1)*0x40000] */
	writel(0x80000001, mac + MAC_REG_ENABLE);	/* +0x8 */
	writel(0x00011200, mac + 0x0E0);		/* +0xe0 serializer/PHY iface */
	writel(0x00000032, mac + MAC_REG_D00);		/* +0xd00 tsf/store-fwd (was mis-offset 0xC20) */
	writel(0x000000A8, mac + MAC_REG_D30);		/* +0xd30 rsf/flow-ctrl (was mis-offset 0xC50) */
	writel(0x0000fffe, mac + MAC_REG_IRQ_MASK);	/* +0x4 = 0xfffe */
	writel(0x00300002, mac + 0x070);		/* +0x70 IFG / rate */
	writel(0x00004000, mac + 0x0B4);		/* +0xb4 */
	writel(0x0010ff11, mac + 0xB00);		/* +0xb00 (= decomp 0x92200070+0xa90) */

	/* Final TX+RX enable — U-Boot ends per-port init with `MAC[N][0] |= 3`.
	 * Our initial 0xBAE003 write above already has bits 0+1 set, but be
	 * explicit to match U-Boot's pattern exactly (no functional change).
	 */
	{
		u32 v = readl(mac + MAC_REG_CONTROL);

		writel(v | 0x3, mac + MAC_REG_CONTROL);
	}

	/* Enable the MAC at NPP level (npp[(port+1)*0x40000] |= 2) */
	npp_or(e, (port + 1) * MAC_STRIDE, 0x2);
}

/* ============================================================
 *   NPP global init — from tm_pon_npp_init + sub-init oneliners
 * ============================================================
 */

static void zx_npp_init(struct zx_eth *e)
{
	/* All values verified from live stock dump. */
	npp_write(e, NPP_REG_IRQ_ENABLE, 0xFFFFFF);	/* NPP reset gate: stock writes 0xFFFFFF (write-1-to-toggle, self-clears to 0 readback) */
	npp_write(e, NPP_REG_IRQ_MASK,   0xFFFFFFFF);	/* NPP clock gate: U-Boot writes 0xFFFFFFFF (all 32 bits toggled), stock writes 0xFFFFF (20 bits). Higher bits may gate BMU/DDR paths */
	usleep_range(1000, 2000);

	/* IDM IRQs masked at probe — open() unmasks bit 2 selectively. */
	npp_write(e, IDM_REG_IRQ_MASK,   IDM_IRQ_ALL_MASKED);
	npp_write(e, IDM_REG_REG_18,     0x40);
	npp_write(e, IDM_REG_TIMEOUT,    5000);
	npp_write(e, IDM_REG_REG_10,     0x40);

	/* IDM control: stock has 0x020F6766 with everything running. Write the
	 * exact stock value (was OR-patched with wrong bits before).
	 */
	npp_write(e, IDM_REG_CONTROL,    0x020F6766);

	/* PP setting from pon_npp_idm_init (left as-is for now). */
	writel(0x640, e->base + PP_OFF + 0x38);

	/* Sub-init oneliners — verified */
	npp_write(e, NPP_REG_SPA_INIT,    0);
	npp_write(e, NPP_REG_SIPC_INIT,   0x11);
	npp_write(e, NPP_REG_SMCT_INIT_0, 0xB);
	/* [SIPC RE 2026-07-31] stock pon_npp_smct_init also writes npp+0x10004
	 * (SMCT pp_pmau, phys 0x921d0004) = 0xB — hidden in the decomp behind a
	 * Ghidra symbol collision (*(tm_set_onu_mac + npp_base + 4)). Mainline
	 * never wrote it → POR value 0xA. PMAU = SMCT packet-memory credit
	 * pools; the only init divergence in the whole SIPC/SMCT complex. */
	npp_write(e, NPP_REG_SMCT_PP_PMAU, 0xB);
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
	 * in this register. Leave it alone (PP brg_init sets it indirectly).
	 */
}

/* ============================================================
 *   IDM descriptor ring + SKB pool init
 * ============================================================
 */

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
	 * per stock idm_init: REG_C0=0, then RX, then TX.
	 */
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
	 * Match exactly — bits[31:16]=1 means "1 new refill available".
	 */
	for (int i = 0; i < IDM_RX_RING_SIZE; i++)
		npp_write(e, IDM_REG_RX_KICK, 0x10000);

	/* Final RX enable from stock.
	 * [Stage-3 WiFi Phase B, 2026-07-23] This is ALSO the "enable IDM RX"
	 * step the Phase-B spec (§4) calls for — it is the exact stock enable
	 * value and no additional register write is needed for the ring to
	 * receive WiFi-stamped frames; idm0/idm1 are already registered, up-able
	 * netdevs (zx_eth_probe_port). The ring reads 0 today only because
	 * nothing feeds it, which is precisely the gap the Phase-B dispatch
	 * (zx_idm_poll RX dispatch + zx_idm_xmit TX stamp) closes. */
	npp_write(e, IDM_REG_RX_ENABLE, 0x4000800);

	e->rx_idx = 0;
	e->tx_idx = 0;
	e->tx_done = 0;
	atomic_set(&e->tx_pending, 0);

	return 0;
}

/* ============================================================
 *   TX completion reclaim — from idm_check_tx_done_nolock RE
 * ============================================================
 */

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
 * ============================================================
 */

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
			/* [Stage-3 WiFi observation, 2026-07-07] ADDITIVE ssid decode.
			 * Per stock RE (findings/wifi_offload_feasibility_2026-07-04.md
			 * dump_idm_desc_rx): IDM RX desc byte6 bit0..2 = ssid, byte6
			 * bit3 = ssid_valid → word1 bits 16..18 / bit 19. This is pure
			 * observation to establish the RX-ssid ground truth once fabric
			 * ports 6/7 carry MT7915 AP traffic; delivery below is unchanged
			 * (still napi_gro_receive). No dispatch, no behavior change. */
			u8 ssid = (word1 >> 16) & 0x7;
			bool ssid_valid = (word1 >> 19) & 1;

			e->idm_rx_count++;
			if (ssid_valid)
				e->idm_rx_per_ssid[ssid]++;
			else
				e->idm_rx_ssid_invalid++;

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

			/* [Stage-3 WiFi Phase B, 2026-07-23] RX dispatch.
			 * BUILD-VERIFIED, UNTESTED ON HARDWARE (spec §1/§3,
			 * findings/wifi_stage3_phaseB_dispatcher_spec_2026-07-07.md).
			 * If this ring frame carries a valid ssid that maps to a
			 * bound, UP mac80211 vif, hand the *intact* L2 frame to
			 * that vif's ndo_start_xmit — mirroring stock
			 * idm_fdb_forward's direct ndo_start_xmit call
			 * (idm_fdb_forward.c:54). ⚠ Deliberately does NOT call
			 * eth_type_trans() here: eth_type_trans() pulls the 14-B
			 * Ethernet header (skb_pull(ETH_HLEN)), which the vif's
			 * transmit path needs left intact. When nothing is bound
			 * (the default), this whole block is skipped and delivery
			 * falls through unchanged to the local stack below — the
			 * exact SW baseline. `port` here is the idm ring index
			 * (word1 bit31), so node_index = ssid + port*8. */
			if (ssid_valid && ssid < 8) {
				struct zx_wifi_dispatch_node *wn =
					&e->zx_wifi_dispatch[ssid + port * 8];

				if (wn->enabled && wn->wlan_ndev &&
				    (wn->wlan_ndev->flags & IFF_UP)) {
					/* [Phase C R1 validation 2026-07-28] one-shot
					 * payload ground truth: first 4 dispatched
					 * frames per arm (debugfs idm_rx_dump=0 to
					 * re-arm). Answers the never-verified offset
					 * question (TM ring had a +2 quirk; this ring
					 * was unverified). Tiny console load. */
					if (e->idm_wifi_rx_dumped < 4) {
						e->idm_wifi_rx_dumped++;
						pr_info("[phaseC/idm-rx] dispatch len=%u ssid=%u first bytes:\n",
							len, ssid);
						print_hex_dump(KERN_INFO, "  idmrx: ",
							DUMP_PREFIX_OFFSET, 16, 1,
							skb->data,
							min_t(u32, len, 48), false);
					}
					/* [Phase C 2026-07-28, HW-proven root cause]
					 * The PM edit decrements the IPv4 TTL but
					 * does NOT update the IP header checksum
					 * (dispatched frames carried the checksum
					 * of TTL+1 — off by exactly 0x100). On the
					 * eth DN path the egress pipeline repairs
					 * it in HW; on this fabric->IDM shuttle
					 * nothing does, so the client's IP stack
					 * silently drops every frame. Repair it
					 * here — the CPU touches each frame anyway.
					 * (TCP/UDP checksums are unaffected: TTL is
					 * not in the pseudo-header; IPv6 has no
					 * header checksum.) */
					if (len >= ETH_HLEN + sizeof(struct iphdr) &&
					    ((struct ethhdr *)skb->data)->h_proto ==
							htons(ETH_P_IP)) {
						struct iphdr *iph = (struct iphdr *)
							(skb->data + ETH_HLEN);

						iph->check = 0;
						iph->check = ip_fast_csum(
							(const void *)iph, iph->ihl);
					}
					skb->dev = wn->wlan_ndev;
					e->idm_wifi_rx_dispatched++;
					if (READ_ONCE(e->ft_wifi_dispatch_qx)) {
						/* Alternate mode: standard L2
						 * injection (full xmit path:
						 * queue pick + validate +
						 * HARD_TX_LOCK). Works, but
						 * measured ~4x slower than the
						 * direct call — kept as a
						 * debug/comparison knob. */
						skb->protocol =
							((struct ethhdr *)skb->data)->h_proto;
						skb_reset_mac_header(skb);
						dev_queue_xmit(skb);
					} else {
						wn->wlan_ndev->netdev_ops->ndo_start_xmit(
							skb, wn->wlan_ndev);
					}
					goto refill;	/* skip eth_type_trans + gro */
				}
				e->idm_wifi_rx_nobind++;
			}

			skb->protocol = eth_type_trans(skb, ndev);
			ndev->stats.rx_bytes += len;
			ndev->stats.rx_packets++;
			napi_gro_receive(napi, skb);

refill:
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
 * ============================================================
 */

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
 * ============================================================
 */

static netdev_tx_t zx_idm_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct zx_eth_port *port = *(struct zx_eth_port **)netdev_priv(ndev);
	struct zx_eth *e = port->eth;
	u32 *tx_desc = e->desc_cpu + IDM_TX_DESC_OFFSET;
	dma_addr_t dma;
	unsigned long flags;
	u32 idx, len, word1;
	/* [Stage-3 WiFi Phase B, 2026-07-23] read the ssid stamped by
	 * zx_wifi_rx_handler (if any) — see the ZX_SKB_CB_TAG_* definition. */
	const struct zx_skb_wifi_tag *tag =
		(const struct zx_skb_wifi_tag *)&skb->cb[ZX_SKB_CB_TAG_OFF];

	/* Fail the build if the mainline sk_buff::cb ever shrinks below our tag. */
	BUILD_BUG_ON(ZX_SKB_CB_TAG_OFF + sizeof(struct zx_skb_wifi_tag) >
		     sizeof_field(struct sk_buff, cb));

	/* Min frame length 0x40 per stock pon_tm_data_raw_send (per stock decomp):
	 * if (len < 0x40 && param_3==0 && (desc[14]&1)==0) zeropad to 0x40 and
	 * encode len=0x40 in desc[12..13]=0x100 and desc[8..11] |= 0x40<<9.
	 */
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

	/* [Stage-3 WiFi Phase B, 2026-07-23] base word1 = today's behavior: len
	 * plus the ring-select bit derived from which idm netdev we're on
	 * (port->idx). The ring bit is chosen by the netdev, NOT by the ssid tag
	 * — so we deliberately do NOT reproduce stock's bug where an unmasked
	 * cb[0xb7]<<28 (e.g. an echoed 0xff RX sentinel) also corrupts bit31.
	 * Only when a valid ssid tag was stamped by zx_wifi_rx_handler do we OR
	 * in the (clamped) 3-bit ssid at bits 28..30; otherwise the descriptor
	 * is byte-identical to the pre-Phase-B baseline. UNTESTED ON HARDWARE. */
	word1 = (len & IDM_DESC_LEN_MASK) | (port->idx ? IDM_DESC_PORT_BIT : 0);
	if (tag->magic == ZX_SKB_CB_TAG_MAGIC) {
		word1 |= (u32)(tag->ssid & IDM_DESC_SSID_MASK) << IDM_DESC_SSID_SHIFT;
		e->idm_wifi_tx_injected++;
	}

	tx_desc[idx * 2]     = cpu_to_le32(dma);
	tx_desc[idx * 2 + 1] = cpu_to_le32(word1);
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
 *   [Stage-3 WiFi Phase B, 2026-07-23] IDM <-> WiFi-vif dispatch glue
 *
 *   BUILD-VERIFIED, UNTESTED ON HARDWARE. Staged per
 *   findings/wifi_stage3_phaseB_dispatcher_spec_2026-07-07.md. Mainline
 *   equivalent of stock idmfdb.ko's register_idm_fdb_node /
 *   idm_fdb_recv_handle, minus the WlanIndex2WlanIdmMap indirection (mainline
 *   owns both ends of the (idm,ssid)<->vif mapping, so we bind directly).
 *
 *   TX direction (vif -> ring): a netdev rx_handler on each bound vif
 *   intercepts every frame the vif RECEIVES over the air, stamps the ssid
 *   into skb->cb, and re-injects it onto the vif's bound idmN netdev via
 *   zx_idm_xmit. This mirrors stock's idm_fdb_recv_handle (spec §2.3). It
 *   defaults OFF: with no vif bound, no rx_handler is installed, so the SW
 *   baseline is untouched. NOTE (spec §2.3 coexistence caveat): a vif can
 *   hold only one rx_handler, and the bridge owns it while the vif is a br0
 *   member — binding therefore returns -EBUSY unless the vif is first removed
 *   from br0. Reversible: unregister + re-bridge restores the baseline.
 * ============================================================
 */

static rx_handler_result_t zx_wifi_rx_handler(struct sk_buff **pskb)
{
	struct sk_buff *skb = *pskb;
	struct zx_wifi_dispatch_node *node =
		rcu_dereference(skb->dev->rx_handler_data);
	struct zx_skb_wifi_tag *tag;

	/* Fall through to the normal stack (SW baseline) when the binding is
	 * inactive or the target ring isn't up — stock gates on a non-NULL
	 * idm_dev (idm_fdb_recv_handle.c:28); we add the stricter IFF_UP test. */
	if (!node || !node->enabled || !node->idm_ndev ||
	    !(node->idm_ndev->flags & IFF_UP))
		return RX_HANDLER_PASS;

	/* [Stage-3 WiFi Phase B.2, 2026-07-24] EAPOL passthrough — the Phase-B
	 * live discovery: diverting EAPOL into the fabric starves hostapd's
	 * ETH_P_PAE packet socket and the WPA2 4-way handshake times out (no STA
	 * can join a bound AP vif). Control-plane frames must reach the stack.
	 * findings/wifi_stage3_phaseB_ondevice_validation_2026-07-07.md. */
	if (skb->protocol == cpu_to_be16(ETH_P_PAE))
		return RX_HANDLER_PASS;

	/* [Phase B.2] Loop guard: frames the TM trap-RX path delivered INTO this
	 * vif (zx_wifi_tm_rx_dispatch) carry the shuttled marker — hand them to
	 * the local stack; re-injecting would loop vif->ring->trap->vif forever. */
	tag = (struct zx_skb_wifi_tag *)&skb->cb[ZX_SKB_CB_TAG_OFF];
	if (tag->magic == ZX_SKB_CB_TAG_MAGIC_SHUTTLED)
		return RX_HANDLER_PASS;

	/* [Stage-3 UP offload 2026-07-28] Inject ONLY IPv4 TCP DATA frames;
	 * PASS everything else (ARP, DHCP, ICMP, IPv6, TCP SYN/FIN/RST) to the
	 * normal stack. Two HW-proven reasons:
	 *  1. The hardfast deliberately CPU-traps TCP control packets (SYN-only
	 *     hping bursts never ride HW — Phase-C validation), so injecting
	 *     them buys nothing;
	 *  2. a CLA-missing injected frame round-trips fabric->trap->TM-ring and
	 *     must survive the +2-offset trap parser (Phase-B.2's noparse quirk)
	 *     to get back to the stack — live 2026-07-28: 12 injected handshake
	 *     SYNs trapped back, 0 re-dispatched, connection dead. Keeping the
	 *     control plane on the SW path makes connect/teardown robust while
	 *     established data rides the fabric fast path. (rx_handler runs
	 *     post-eth_type_trans: skb->data = L3, mac header pulled.) */
	if (skb->protocol == cpu_to_be16(ETH_P_IP)) {
		const struct iphdr *iph;
		const struct tcphdr *th;

		if (!pskb_may_pull(skb, sizeof(*iph)))
			return RX_HANDLER_PASS;
		iph = (const struct iphdr *)skb->data;
		if (iph->protocol != IPPROTO_TCP)
			return RX_HANDLER_PASS;
		if (!pskb_may_pull(skb, iph->ihl * 4 + sizeof(*th)))
			return RX_HANDLER_PASS;
		th = (const struct tcphdr *)(skb->data + iph->ihl * 4);
		if (th->syn || th->fin || th->rst)
			return RX_HANDLER_PASS;
	} else {
		return RX_HANDLER_PASS;
	}

	/* [Stage-3 UP offload 2026-07-28] Restore the L2 header before the ring:
	 * rx_handlers run post-eth_type_trans (skb->data = L3, mac header
	 * pulled), but zx_idm_xmit DMA-maps skb->data verbatim — without this
	 * push the fabric receives a HEADERLESS frame the CLA can never parse
	 * (and the trap-side parser only sometimes rescues, cf. the Phase-B.2
	 * offset-hunt/noparse quirks). Same pattern as the bridge's
	 * br_dev_queue_push_xmit. If the mac header isn't where we expect,
	 * stay on the SW path rather than inject garbage. */
	if (!skb_mac_header_was_set(skb) ||
	    skb_mac_header(skb) != skb->data - ETH_HLEN)
		return RX_HANDLER_PASS;
	skb_push(skb, ETH_HLEN);

	/* Stamp ssid for zx_idm_xmit's TX-descriptor packer (spec §2.1/§2.2). */
	tag->magic = ZX_SKB_CB_TAG_MAGIC;
	tag->ssid  = node->ssid;

	skb->dev = node->idm_ndev;
	/* Direct ndo_start_xmit-equivalent call, mirroring stock's raw dispatch
	 * (spec §2.3 recommends this over dev_queue_xmit to start). On TX_BUSY
	 * zx_idm_xmit did NOT take ownership, so drop here (can't re-queue from
	 * an rx_handler). Revisit with dev_queue_xmit if backpressure drops hurt. */
	if (zx_idm_xmit(skb, node->idm_ndev) == NETDEV_TX_BUSY)
		kfree_skb(skb);

	return RX_HANDLER_CONSUMED;
}

/* Bind a WiFi vif to (idm_ring, ssid). node_index = ssid + idm_ring*8.
 * UNTESTED ON HARDWARE. Takes/holds a reference on the vif for the lifetime of
 * the binding; installs the rx_handler under rtnl. Returns -EBUSY if the vif
 * already has an rx_handler (e.g. it is still a br0 member — see the caveat
 * above). */
static int zx_wifi_register_vif(struct zx_eth *e, struct net_device *vif,
				u8 idm_ring, u8 ssid)
{
	struct zx_wifi_dispatch_node *node;
	int rc;

	if (!vif || idm_ring > 1 || ssid > 7)
		return -EINVAL;
	if (idm_ring >= ZX_NPORTS || !e->ports[idm_ring].netdev)
		return -ENODEV;

	node = &e->zx_wifi_dispatch[ssid + idm_ring * 8];
	if (node->enabled)
		return -EBUSY;

	node->idm	= idm_ring;
	node->ssid	= ssid;
	node->idm_ndev	= e->ports[idm_ring].netdev;
	node->wlan_ndev	= vif;
	node->wlan_ifindex = vif->ifindex;

	rc = netdev_rx_handler_register(vif, zx_wifi_rx_handler, node);
	if (rc) {
		node->wlan_ndev = NULL;
		node->idm_ndev  = NULL;
		return rc;
	}

	dev_hold(vif);
	/* Publish last: the rx_handler above already returns RX_HANDLER_PASS
	 * until enabled flips true, and the RX-dispatch path in zx_idm_poll
	 * likewise checks enabled — so no frame is dispatched half-bound. */
	smp_wmb();
	node->enabled = true;
	netdev_info(vif, "[ZXETH] wifi_bind: %s -> idm%u ssid%u (node %u) [UNTESTED]\n",
		    vif->name, idm_ring, ssid, ssid + idm_ring * 8);
	return 0;
}

/* Unbind. UNTESTED ON HARDWARE. */
static int zx_wifi_unregister_vif(struct zx_eth *e, u8 idm_ring, u8 ssid)
{
	struct zx_wifi_dispatch_node *node;
	struct net_device *vif;

	if (idm_ring > 1 || ssid > 7)
		return -EINVAL;

	node = &e->zx_wifi_dispatch[ssid + idm_ring * 8];
	if (!node->enabled)
		return -ENOENT;

	node->enabled = false;
	smp_wmb();
	vif = node->wlan_ndev;
	if (vif) {
		rtnl_lock();
		if (node->wlan_ndev == vif)
			netdev_rx_handler_unregister(vif);
		rtnl_unlock();
		dev_put(vif);
	}
	node->wlan_ndev = NULL;
	node->idm_ndev  = NULL;
	node->wlan_ifindex = 0;
	return 0;
}

/* ============================================================
 *   Netdev ops
 * ============================================================
 */

static int zx_eth_open(struct net_device *ndev)
{
	/* [Phase C R1 fix, 2026-07-27] NAPI + IDM RX IRQ are now started ONCE at
	 * probe (stock parity), NOT here. The IDM RX ring consumer must run even
	 * with no idm0/idm1 netdev administratively UP, because WiFi HW-offload
	 * egress lands hw-forwarded frames on the IDM RX ring with no netdev ever
	 * upped (the R1 black hole). NAPI ownership lives in probe + remove.
	 * findings/wifi_stage3_phaseC_R1_fix_2026-07-25.md
	 */
	netdev_dbg(ndev, "open\n");
	netif_carrier_on(ndev);
	netif_start_queue(ndev);
	return 0;
}

static int zx_eth_stop(struct net_device *ndev)
{
	/* [Phase C R1 fix, 2026-07-27] Do NOT stop the IDM engine here: the NAPI /
	 * IDM IRQ lifecycle now lives at probe/remove, so downing idm0/idm1 (or the
	 * last eth port) cannot kill WiFi-offload RX-ring delivery. See zx_eth_open
	 * + findings/wifi_stage3_phaseC_R1_fix_2026-07-25.md.
	 */
	netif_stop_queue(ndev);
	netif_carrier_off(ndev);
	netdev_dbg(ndev, "stop\n");
	return 0;
}

/* HW flow-offload entry (Workstream B). Defined after the CLA/PM helpers below;
 * forward-declared here so it can be wired into the conduit's netdev ops. This is
 * the ndo_setup_tc that DSA delegates TC_SETUP_FT (nf_flow_table/conntrack offload)
 * to — see net/dsa/slave.c dsa_slave_setup_tc -> conduit master ndo_setup_tc. */
static int zx_eth_setup_tc(struct net_device *ndev, enum tc_setup_type type,
			   void *type_data);

static const struct net_device_ops zx_eth_netdev_ops = {
	.ndo_open	= zx_eth_open,
	.ndo_stop	= zx_eth_stop,
	.ndo_start_xmit	= zx_idm_xmit,
	.ndo_set_mac_address = eth_mac_addr,
	.ndo_validate_addr   = eth_validate_addr,
	.ndo_setup_tc	= zx_eth_setup_tc,
};

/* ============================================================
 *   TM (Traffic Manager) — CPU↔switch path
 *   Architecture mirrors stock pon_tm_* + airoha_eth.c patterns.
 * ============================================================
 */

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

