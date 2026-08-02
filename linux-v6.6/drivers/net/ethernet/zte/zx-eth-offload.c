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
		 * drops killing concurrent handshakes). Same cookie + same raw
		 * = same tuple (NAT recipe immutable for a conntrack flow) ->
		 * nothing to update: report "already installed" (rc 1) so the
		 * caller skips the HW rewrite entirely.
		 */
		if (e->ft_flows[self].raw == raw) {
			*pm_slot = e->ft_flows[self].pm_slot;
			return 1;
		}
		/* [H3 fix 2026-07-04] Self-REPLACE with a CHANGED 5-tuple: the
		 * caller (zx_ft_flower_replace) is about to install a brand-new
		 * raw/raw0 recipe at this cookie's pm_slot, but the OLD raw's 5
		 * ways (and OLD raw0's poly-0 bucket, if it had one) are a
		 * SEPARATE CLA address from the new ones and are never touched by
		 * the upcoming install -- so if we didn't clear them here they'd
		 * be orphaned: still valid_en, still HW-forwarding the dead
		 * tuple, forever (a plain DESTROY later only clears the CURRENT
		 * raw/raw0, never a replaced-away one). This is finding H3(a) /
		 * H3a (findings/qa_static_bughunt_2026-07-04.md); the C2 fix
		 * deliberately left it out of scope. Uses the same
		 * zx_ft_uninstall() helper untrack()/partial-install-rollback
		 * use, so "clear a flow's old footprint" has exactly one
		 * implementation. */
		dev_info(e->dev,
			 "[phase6/ft] self-replace old-footprint clear: cookie=%lx old_raw=0x%04x old_raw0=%s0x%04x -> new_raw=0x%04x pm_slot=%u\n",
			 cookie, e->ft_flows[self].raw,
			 e->ft_flows[self].has_raw0 ? "" : "n/a-",
			 e->ft_flows[self].raw0, raw, e->ft_flows[self].pm_slot);
		zx_ft_uninstall(e, e->ft_flows[self].raw,
				e->ft_flows[self].has_raw0,
				e->ft_flows[self].raw0,
				e->ft_flows[self].pm_slot);
		e->ft_flows[self].raw = raw;
		e->ft_flows[self].raw0 = raw0;
		e->ft_flows[self].has_raw0 = has_raw0;
		*pm_slot = e->ft_flows[self].pm_slot;
		return 0;
	}
	if (free < 0)
		return -ENOSPC;			/* tracking table full */
	e->ft_flows[free].cookie = cookie;
	e->ft_flows[free].raw = raw;
	e->ft_flows[free].raw0 = raw0;
	e->ft_flows[free].has_raw0 = has_raw0;
	e->ft_flows[free].pm_slot = ZX_FT_PM_BASE + free;
	e->ft_flows[free].used = true;
	*pm_slot = e->ft_flows[free].pm_slot;
	return 0;
}

/* Undo a reservation (no CLA write / HW write failed): free the slot. */
static void zx_ft_flow_release(struct zx_eth *e, unsigned long cookie)
{
	int i;

	for (i = 0; i < ZX_FT_MAX_FLOWS; i++)
		if (e->ft_flows[i].used && e->ft_flows[i].cookie == cookie) {
			e->ft_flows[i].used = false;
			return;
		}
}

/* Invalidate the buckets a tracked FT flow occupies (zero the entry in all 5 way
 * banks -> valid_en off -> key-compare misses -> flow traps). Returns 0 if
 * found+cleared, -ENOENT else.
 *
 * [C2 fix] Also zero the DN-only poly-0 ram2 bucket (raw0 & 0xff) when the
 * flow has one. That bucket is a SEPARATE ram2 address from way0
 * (raw & 0xff, cleared by the 5-way loop below) -- it is the entry
 * zx_ft_install_recipe additionally writes for DN flows because it's the
 * slot the WAN-ingress lookup actually consults. Before this fix it was
 * never cleared here, so a destroyed flow's dead tuple kept HW-forwarding
 * (stale poly-0 hit) until its pm_slot got reused by an unrelated new flow,
 * at which point the stale entry started applying the NEW flow's NAT to the
 * OLD (supposedly dead) tuple's traffic (findings/qa_static_bughunt_2026-07-04.md
 * C2 fail#1).
 *
 * [H2 fix] The unconditional 5-way zero below is safe against wiping a LIVE
 * other flow's higher-way bucket (ram3/4/5/6) only because zx_ft_flow_reserve
 * now declines (never admits) any two tracked flows that would ever share a
 * way address in any of the 5 banks (findings/qa_static_bughunt_2026-07-04.md
 * H2) -- i.e. the collision is prevented at install time, not papered over
 * here at destroy time. Do not relax reserve()'s higher-way check without
 * revisiting this loop.
 *
 * [H3 fix 2026-07-04] The actual clearing is now zx_ft_uninstall() (shared
 * with the self-REPLACE and partial-install-failure rollback call sites) --
 * this function used to duplicate the same 5-way+poly-0+ext-block zeroing
 * ad hoc. On a nonzero rc (a CLA/PM indirect-engine write reporting -EBUSY --
 * the only failure mode observed on this silicon, a wait_done timeout) retry
 * ONCE, then dev_warn loudly naming the still-possibly-live entry rather
 * than the old behavior of silently discarding the rc entirely (findings/
 * qa_static_bughunt_2026-07-04.md H3(c)). Deliberately NOT an unbounded
 * retry loop: this runs under zx_hwlock (held for the whole zx_ft_setup_cb
 * body), so retrying forever here would stall every other FT/DSA/debugfs
 * user of the same hardware indefinitely. The tracking slot is freed either
 * way -- the cookie is already gone from conntrack by the time DESTROY
 * fires, so there is no live SW-side owner left to keep the slot reserved
 * for. */
static int zx_ft_flow_untrack(struct zx_eth *e, unsigned long cookie)
{
	int i, rc;

	for (i = 0; i < ZX_FT_MAX_FLOWS; i++) {
		if (e->ft_flows[i].used && e->ft_flows[i].cookie == cookie) {
			rc = zx_ft_uninstall(e, e->ft_flows[i].raw,
					     e->ft_flows[i].has_raw0,
					     e->ft_flows[i].raw0,
					     e->ft_flows[i].pm_slot);
			if (rc) {
				rc = zx_ft_uninstall(e, e->ft_flows[i].raw,
						     e->ft_flows[i].has_raw0,
						     e->ft_flows[i].raw0,
						     e->ft_flows[i].pm_slot);
				if (rc)
					dev_warn(e->dev,
						 "[phase6/ft] flow del cookie=%lx: HW clear FAILED rc=%d (after 1 retry) -- raw=0x%04x pm_slot=%u may still be live/forwarding the dead tuple; freeing tracking slot anyway (cookie already gone from conntrack, can't retry forever under zx_hwlock)\n",
						 cookie, rc, e->ft_flows[i].raw,
						 e->ft_flows[i].pm_slot & 0xff);
			}
			dev_info(e->dev,
				 "[phase6/ft] flow del cookie=%lx -> cleared raw=0x%04x (5 ways) poly0=%s(ram2[0x%02x]) ext blk %u rc=%d\n",
				 cookie, e->ft_flows[i].raw,
				 e->ft_flows[i].has_raw0 ? "cleared" : "n/a",
				 e->ft_flows[i].raw0 & 0xff,
				 e->ft_flows[i].pm_slot & 0xff, rc);
			e->ft_flows[i].used = false;
			e->ft_flows[i].has_raw0 = false;
			return rc;
		}
	}
	return -ENOENT;
}

/* Resolve the next-hop MAC via route + neigh on the egress dev (mirrors stock FFE). */
static bool zx_ft_resolve_nh(struct net_device *odev, __be32 daddr, u8 nh_mac[ETH_ALEN])
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

/* Map a redirect/egress netdev to its chip regport. DSA per-port (lanN) slaves
 * carry their port index via dsa_port_from_netdev().
 *
 * [H4 fix 2026-07-04, findings/qa_static_bughunt_2026-07-04.md] This USED to
 * fall back to regport 2 (lan1) whenever odev was NULL or not one of our DSA
 * user ports -- which the nf_flowtable legitimately hands us for a bridge
 * master, a VLAN upper, a ppp device, or a wifi netdev sitting on top of a
 * DSA port. Guessing lan1 armed a real HW direct-forward CLA entry that
 * steered that flow's actual traffic to whatever host physically sits on
 * lan1 -- silent misdelivery to the wrong port, not merely a missed
 * optimization. There is no valid regport for a non-DSA-user-port egress
 * device, so this now returns a sentinel and the caller declines the
 * offload (stays on the SW path) instead of installing a guessed route. */
#define ZX_FT_EGRESS_INVALID	0xff
static const u8 zx_ft_regport[8] = { 1, 2, 3, 4, 5, 0, 6, 7 };
static u8 zx_ft_egress_regport(struct net_device *odev)
{
	struct dsa_port *dp;

	if (!odev || !dsa_slave_dev_check(odev))
		return ZX_FT_EGRESS_INVALID;
	dp = dsa_port_from_netdev(odev);
	if (IS_ERR_OR_NULL(dp))
		return ZX_FT_EGRESS_INVALID;
	return zx_ft_regport[dp->index & 7];
}

/* [Stage-3 WiFi Phase C 2026-07-27] Resolve a flow's egress netdev to the WLAN
 * logical port (`essid = 0x10 | (idm_ring<<3) | ssid`, 0x10-0x1f) when it is a
 * vif currently bound in the Phase-B (idm,ssid)<->vif dispatch table — the
 * mainline equivalent of stock's get_sw_port_from_devname()
 * (decomp_all_switch.c:4515: WLAN devname -> 0x10+ssid / 0x18+ssid), which is
 * where stock's hardfast installer gets the gemport_uni_id for a WiFi DN flow
 * (switch.c:1697). Returns ZX_FT_EGRESS_INVALID when disabled, unbound, or not
 * a wifi vif — the caller then declines exactly as the pre-Phase-C H4 guard.
 *
 * Locking: called under zx_hwlock (zx_ft_setup_cb). wifi_bind's
 * register/unregister do NOT take zx_hwlock, so a concurrent unbind can race
 * this scan — same convention as the zx_idm_poll RX dispatch, and benign for
 * the same reason: only pointer EQUALITY with odev (held live by the caller's
 * flow rule) plus two u8s are read, nothing is dereferenced through
 * wlan_ndev; the worst case installs a flow whose frames then land on a
 * now-unbound node and are counted as idm_wifi_rx_nobind (delivered to the
 * idmN stack fallback), not misdelivered. */
static u8 zx_ft_wifi_essid(struct zx_eth *e, const struct net_device *odev)
{
	int i;

	if (!odev || !READ_ONCE(e->ft_wifi_en))
		return ZX_FT_EGRESS_INVALID;
	for (i = 0; i < 16; i++) {
		struct zx_wifi_dispatch_node *wn = &e->zx_wifi_dispatch[i];

		if (READ_ONCE(wn->enabled) && wn->wlan_ndev == odev)
			return 0x10 | ((wn->idm & 1) << 3) | (wn->ssid & 7);
	}
	return ZX_FT_EGRESS_INVALID;
}

/* [Stage-3 WiFi UP 2026-07-28] Resolve a flow's INGRESS ifindex (from the
 * nf_flow_table rule's FLOW_DISSECTOR_KEY_META) to the flow-key header byte:
 * a currently-bound WiFi vif returns the fabric rule header for its ring
 * (0x38 = idm1, 0x30 = idm0); anything else returns the eth header 0x48.
 * Gated by ftwifi like zx_ft_wifi_essid, so ftwifi=0 keeps every install
 * byte-identical to the pre-fix driver. Same locking convention as
 * zx_ft_wifi_essid (integer compare against the bind-time cached ifindex; a
 * racing unbind at worst mis-keys one install, which then just LOOK_UP_MISSes
 * and stays on the SW path). */
static u8 zx_ft_wifi_ing_hdr(struct zx_eth *e, int ifindex)
{
	int i;

	if (!ifindex || !READ_ONCE(e->ft_wifi_en))
		return ZX_FT_KEY_HDR_ETH;
	for (i = 0; i < 16; i++) {
		struct zx_wifi_dispatch_node *wn = &e->zx_wifi_dispatch[i];

		if (READ_ONCE(wn->enabled) && wn->wlan_ifindex == ifindex)
			return ZX_FT_KEY_HDR_IDM(wn->idm);
	}
	return ZX_FT_KEY_HDR_ETH;
}

/* Parse a flow_cls_offload 5-tuple + actions and install/remove the HW recipe. */
static int zx_ft_flower_replace(struct zx_eth *e, struct flow_cls_offload *cls)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(cls);
	struct flow_action_entry *act;
	struct net_device *odev = NULL;
	__be32 saddr = 0, daddr = 0;
	__be16 sport = 0, dport = 0;
	u8 nh_mac[ETH_ALEN] = {0};
	bool have_mac = false;
	u8 ip_proto = 0;
	u8 eg_regport;
	u8 key_hdr = ZX_FT_KEY_HDR_ETH;
	int ing_ifindex = 0;
	u16 raw, raw0 = 0, pm_slot = 0;
	bool is_dn, has_raw0;
	struct zx_ft_nat nat = {0};
	int i, rc;

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) {
		struct flow_match_basic m;

		flow_rule_match_basic(rule, &m);
		ip_proto = m.key->ip_proto;
	}
	/* [Stage-3 WiFi UP 2026-07-28] nf_flow_table_offload.c always emits the
	 * META key with ingress_ifindex = the direction's iifidx — the ONLY
	 * ingress identity in the rule, needed to key fabric-ingress (WiFi vif)
	 * flows for their per-inport CLA extract rule (see key_hdr below). */
	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_META)) {
		struct flow_match_meta m;

		flow_rule_match_meta(rule, &m);
		ing_ifindex = m.key->ingress_ifindex;
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

	/* Only L3 5-tuple flows (TCP/UDP) are offloadable; ICMP/no-port -> SW. */
	if ((ip_proto != IPPROTO_TCP && ip_proto != IPPROTO_UDP) || !daddr)
		return -EOPNOTSUPP;

	flow_action_for_each(i, act, &rule->action) {
		switch (act->id) {
		case FLOW_ACTION_REDIRECT:
		case FLOW_ACTION_REDIRECT_INGRESS:
			odev = act->dev;
			break;
		case FLOW_ACTION_MANGLE:
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
				have_mac = true;
			} else if (act->mangle.htype ==
				   FLOW_ACT_MANGLE_HDR_TYPE_IP4) {
				/* nf_flow_table: offset 12=saddr(SNAT), 16=daddr(DNAT);
				 * val = the new __be32 address (mask covers all 32b). */
				if (act->mangle.offset ==
				    offsetof(struct iphdr, saddr)) {
					nat.new_ip = (__force __be32)act->mangle.val;
					nat.snat = true;
				} else if (act->mangle.offset ==
					   offsetof(struct iphdr, daddr)) {
					nat.new_ip = (__force __be32)act->mangle.val;
					nat.dnat = true;
				}
			} else if (act->mangle.htype ==
					FLOW_ACT_MANGLE_HDR_TYPE_TCP ||
				   act->mangle.htype ==
					FLOW_ACT_MANGLE_HDR_TYPE_UDP) {
				/* nf_flow_table: L4 ports at word offset 0. mask
				 * ~0xffff0000 => rewrite SOURCE port (high 16b),
				 * val=htonl(port<<16); mask ~0xffff => DEST port
				 * (low 16b), val=htonl(port). */
				u32 v = ntohl((__force __be32)act->mangle.val);

				if (act->mangle.mask == (__force u32)~htonl(0xffff0000)) {
					nat.new_sport = (v >> 16) & 0xffff;
					nat.sport_set = true;
				} else if (act->mangle.mask ==
					   (__force u32)~htonl(0xffff)) {
					nat.new_dport = v & 0xffff;
					nat.dport_set = true;
				}
			}
			break;
		default:
			break;
		}
	}

	if (!have_mac && !zx_ft_resolve_nh(odev, daddr, nh_mac)) {
		dev_info(e->dev,
			 "[phase6/ft] cookie=%lx %pI4:%u->%pI4:%u no resolved nh-MAC, skip\n",
			 cls->cookie, &saddr, ntohs(sport), &daddr, ntohs(dport));
		return -EOPNOTSUPP;
	}

	eg_regport = zx_ft_egress_regport(odev);
	if (eg_regport == ZX_FT_EGRESS_INVALID) {
		/* [Stage-3 WiFi Phase C 2026-07-27] Before declining, try the
		 * WiFi resolution: a bound vif egress resolves to the WLAN
		 * logical port essid (0x10-0x1f), which the recipe installs as
		 * gemport_uni_id (the HW-validated egress-steering field, now
		 * carrying stock's WiFi encoding). Gated by debugfs "ftwifi"
		 * (default off -> this block is a no-op and the H4 decline
		 * below is byte-identical to the pre-Phase-C behavior). */
		eg_regport = zx_ft_wifi_essid(e, odev);
		if (eg_regport != ZX_FT_EGRESS_INVALID)
			dev_info(e->dev,
				 "[phaseC/ft] cookie=%lx egress %s -> wifi essid 0x%02x (idm%u ssid%u), installing DN hardfast\n",
				 cls->cookie, netdev_name(odev), eg_regport,
				 (eg_regport >> 3) & 1, eg_regport & 7);
	}
	if (eg_regport == ZX_FT_EGRESS_INVALID) {
		/* [H4 fix 2026-07-04] odev is not a DSA user port of this switch
		 * (bridge master / VLAN upper / ppp / wifi / NULL) -- there is no
		 * regport to hand the HW, and guessing one (the old lan1
		 * fallback) misdelivers real traffic. Decline; the flow stays on
		 * the SW flowtable fast-path, which handles any egress device. */
		dev_info(e->dev,
			 "[phase6/ft] offload declined: egress dev %s is not a DSA user port of this switch (H4 guard) -> stays in SW\n",
			 odev ? netdev_name(odev) : "(null)");
		return -EOPNOTSUPP;
	}

	/* [up-hwoffload 2026-07-04] UPSTREAM (LAN->WAN, egress = WAN regport) used to
	 * stay on the SW flowtable fast-path: the UP direction's HW-forwarded frames
	 * reached the MAC4 wire but with src IP 0.0.0.0 (the PM engine's flow_info
	 * FETCH for the UP direction lands on a different address than the external
	 * dir-0 table the old recipe wrote — measured 2026-07-04 via the sport-encoded
	 * fill: the server never saw the encoded ports). Root cause (RE'd, see
	 * findings/stock_red_drain_up_RE_2026-07-04.md CANDIDATE 2 and the up_idx_fix
	 * comment on zx_ft_pack_cla): mainline packed cmd_flow_id as pm_slot*128+1 for
	 * BOTH directions; DN's fetch happens to land >=0x400 (external DDR, which the
	 * recipe also populates -> works by coincidence), UP's identical fetch lands on
	 * the SAME resolved index but nothing was ever written there for UP's values.
	 * FIXED by repacking the UP entry's cmd_flow_id = pm_slot directly (<0x400,
	 * dir=UP=0 -> internal ram0[pm_slot], which the recipe already writes).
	 * Verified on-device 2026-07-04: UP HW-forwarded frames now carry the correct
	 * SNAT src IP (was 0.0.0.0), cla_up_fwd increments, ACKs no longer trap to the
	 * CPU -> removes the RED-drop flood that fed the residual sustained-download
	 * admission latch (findings/wedge_txflowctrl_fix_2026-07-04.md). e->ft_up_en
	 * now DEFAULTS to 1 (see zx_eth_probe); the debugfs "ftup" knob still allows
	 * forcing UP back to SW-only for regression testing. */
	if (eg_regport == ZX_WAN_REGPORT && !READ_ONCE(e->ft_up_en)) {
		/* Ratelimited: the nf_flow_table re-REPLACE storm (see
		 * zx_ft_flow_reserve) re-delivers this several times per second
		 * for every live download; unlimited it floods/wraps the dmesg
		 * ring (QA 2026-07-04) and each line costs a slow UART printk. */
		dev_info_ratelimited(e->dev,
			 "[phase6/ft] cookie=%lx %pI4:%u->%pI4:%u UP dir -> SW fast-path (no HW install)\n",
			 cls->cookie, &saddr, ntohs(sport), &daddr, ntohs(dport));
		return 0;
	}

	/* Reserve a tracking slot BEFORE writing the CLA: decline (stay SW) on a
	 * bucket collision or a full table instead of clobbering/leaking. The
	 * reserve-time hash MUST match the install-time hash, so derive the same
	 * ingress-awareness (WAN-ingress = egress toward a LAN port) here.
	 *
	 * [C2 fix] zx_ft_install_recipe ALSO writes a poly-0 ram2 entry
	 * (raw0 & 0xff) for DN flows (eg_regport != ZX_WAN_REGPORT) -- the slot
	 * the WAN-ingress lookup actually consults. Compute that same raw0 here
	 * (pure SW CRC, no HW engine access, same pattern already used for
	 * `raw` which install_recipe independently recomputes too) so reserve()
	 * can collision-check it and untrack() can later clear it. */
	is_dn = eg_regport != ZX_WAN_REGPORT;
	/* [Stage-3 WiFi UP 2026-07-28] The UP direction of a WiFi client's flow
	 * ingresses the FABRIC (bound vif -> rx_handler -> idm ring), which
	 * classifies under its per-inport CLA group (rule 0x70/0x60), NOT the
	 * eth group-9 rule 0x90 — so the key header, the entry's extr_index,
	 * and consequently raw/raw0 all change. Resolve the ingress ifindex
	 * against the wifi_bind table (ftwifi-gated; eth flows and ftwifi=0 stay
	 * byte-identical). Only the UP direction (egress == WAN) can be
	 * fabric-ingress on this topology; DN's ingress is the WAN port. */
	if (!is_dn)
		key_hdr = zx_ft_wifi_ing_hdr(e, ing_ifindex);
	raw = zx_ft_flow_hash(e, ip_proto, saddr, daddr, sport, dport, is_dn,
			      key_hdr);
	/* WiFi-ingress UP flows get NO poly-0 slot (fabric probes the poly-1
	 * way set, proven live — see zx_ft_install_recipe), so has_raw0 stays
	 * DN-only. */
	has_raw0 = is_dn;
	if (has_raw0)
		raw0 = zx_ft_flow_hash_poly0(ip_proto, saddr, daddr, sport,
					     dport, is_dn, key_hdr);
	if (key_hdr != ZX_FT_KEY_HDR_ETH)
		dev_info(e->dev,
			 "[phaseC/ft] cookie=%lx ingress ifindex %d is a bound wifi vif -> fabric key_hdr=0x%02x (rule 0x%02x), installing UP hardfast\n",
			 cls->cookie, ing_ifindex, key_hdr, key_hdr << 1);
	rc = zx_ft_flow_reserve(e, cls->cookie, raw, has_raw0, raw0, &pm_slot);
	if (rc == 1)		/* identical flow already live: idempotent no-op */
		return 0;
	if (rc == -EOPNOTSUPP) {
		dev_info(e->dev,
			 "[phase6/ft] offload declined: CLA bucket collision cookie=%lx raw 0x%04x (way0 0x%02x owned) -> stays in SW\n",
			 cls->cookie, raw, raw & 0xff);
		return rc;
	}
	if (rc < 0) {
		dev_info(e->dev,
			 "[phase6/ft] offload declined: flow table full (max %d) cookie=%lx -> stays in SW\n",
			 ZX_FT_MAX_FLOWS, cls->cookie);
		return -EOPNOTSUPP;
	}

	rc = zx_ft_install_recipe(e, ip_proto, saddr, daddr, sport, dport,
				  nh_mac, eg_regport, pm_slot, &nat, key_hdr);
	if (rc < 0) {
		/* [H3 fix 2026-07-04] Partial-install failure (findings/
		 * qa_static_bughunt_2026-07-04.md H3(b)): zx_ft_install_recipe
		 * accumulates rc across ALL 5 way writes + the poly-0 write (it
		 * does not bail out after the first failure), so by the time we
		 * get here anywhere from 0 to all of those writes may have
		 * landed. zx_ft_flow_release() alone (the old behavior) only
		 * freed the TRACKING slot -- any ways/poly-0/PM entries that DID
		 * land stayed live and untracked, and once the freed pm_slot got
		 * reused by a future flow, THAT flow's install fed the orphan
		 * entry its rewrite state (same corruption class as C2). Unwind
		 * with the exact (raw, raw0, pm_slot) this attempt just used --
		 * re-zeroing a location that was never actually written is a
		 * harmless no-op, so it's safe to call unconditionally rather
		 * than trying to track which subset of writes succeeded. */
		zx_ft_uninstall(e, raw, has_raw0, raw0, pm_slot);
		zx_ft_flow_release(e, cls->cookie);
		return rc;
	}
	return 0;
}

/* FLOW_CLS_STATS: the nf_flow_table GC polls every HW-offloaded flow for activity
 * and refreshes flow->timeout from the reported lastused
 * (nf_flow_table_core.c:nf_flow_offload_gc_step -> nf_flow_offload_stats ->
 * flow_offload_work_stats: flow->timeout = max(timeout, lastused + get_timeout)).
 * HW-forwarded packets BYPASS the CPU, so with no stats report the core sees the
 * flow as idle, ages it out (FLOW_CLS_DESTROY) and re-installs on the next trapped
 * packet (FLOW_CLS_REPLACE) -> the heavy install/destroy churn that leaves the HW
 * entry absent most of the time (the ~17 % hit-rate). For a resident tracked flow
 * report lastused = now (keepalive) so the core keeps it offloaded and does NOT GC
 * it while our HW entry is installed.
 *
 * The CLA exposes no per-flow/per-bucket HW hit counter indexable by pm_slot (only
 * the global cla_tx_fwd 0x9238c3c0 and a per-entry age bit in ram2 byte0x10 bit6),
 * so pkts/bytes are reported 0; the keepalive relies on conntrack teardown /
 * FLOW_CLS_DESTROY and the 32-entry cap to release a flow. FLOW_ACTION_HW_STATS_
 * DELAYED matches the GC-poll cadence (mtk_ppe/mlx5 pattern). Returns -EOPNOTSUPP
 * for a cookie we do not track so the core never refreshes a flow we don't own. */
static int zx_ft_flower_stats(struct zx_eth *e, struct flow_cls_offload *cls)
{
	int i;

	for (i = 0; i < ZX_FT_MAX_FLOWS; i++)
		if (e->ft_flows[i].used && e->ft_flows[i].cookie == cls->cookie) {
			flow_stats_update(&cls->stats, 0, 0, 0, jiffies,
					  FLOW_ACTION_HW_STATS_DELAYED);
			return 0;
		}
	return -EOPNOTSUPP;
}

static int zx_ft_setup_cb(enum tc_setup_type type, void *type_data, void *cb_priv)
{
	struct zx_eth *e = cb_priv;
	struct flow_cls_offload *cls = type_data;
	int rc;

	if (type != TC_SETUP_CLSFLOWER)
		return -EOPNOTSUPP;

	/* [ft_lock 2026-07-04] nf_flow_table dispatches REPLACE/DESTROY/STATS
	 * on three separate WQ_UNBOUND workqueues — mutually concurrent, and
	 * concurrent with the DSA tc-flower path (rtnl) + debugfs pokes that
	 * drive the identical CLA/PM/hash-engine hardware and the ft_flows[]
	 * table. Serialize the whole callback body (reserve/install/untrack)
	 * with the shared cross-module lock. See
	 * findings/qa_static_bughunt_2026-07-04.md finding C1. */
	mutex_lock(&zx_hwlock);
	switch (cls->command) {
	case FLOW_CLS_REPLACE:
		rc = zx_ft_flower_replace(e, cls);
		break;
	case FLOW_CLS_DESTROY:
		dev_info(e->dev, "[phase6/ft] flower destroy cookie=%lx\n", cls->cookie);
		/* [H3 fix 2026-07-04] Look at the untrack rc instead of discarding
		 * it (findings/qa_static_bughunt_2026-07-04.md H3(c)) -- the
		 * dev_warn on a real failure now happens inside
		 * zx_ft_flow_untrack() itself (it has the raw/pm_slot details to
		 * make the warning actionable); nf_flow_table has no use for a
		 * nonzero FLOW_CLS_DESTROY return (there's no "undo a destroy"),
		 * so this callback still always reports success upstream. */
		rc = zx_ft_flow_untrack(e, cls->cookie);
		if (rc && rc != -ENOENT)
			dev_warn_ratelimited(e->dev,
				"[phase6/ft] destroy cookie=%lx: untrack reported rc=%d -- see the HW clear FAILED warning above if the retry also failed\n",
				cls->cookie, rc);
		rc = 0;
		break;
	case FLOW_CLS_STATS:
		rc = zx_ft_flower_stats(e, cls);
		break;
	default:
		rc = -EOPNOTSUPP;
		break;
	}
	mutex_unlock(&zx_hwlock);
	return rc;
}

static LIST_HEAD(zx_ft_block_cb_list);

static int zx_eth_setup_block(struct zx_eth *e, struct flow_block_offload *f)
{
	struct flow_block_cb *block_cb;

	/* NB: on Linux 6.6 the nf_flow_table offload core binds its block with
	 * binder_type = FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS (see
	 * nf_flow_table_block_offload_init(), nf_flow_table_offload.c) and
	 * dispatches it via ndo_setup_tc(dev, TC_SETUP_FT, bo). There is NO
	 * distinct FLOW_BLOCK_BINDER_TYPE_FT in this kernel, so the FT flowtable
	 * block is accepted by the CLSACT_INGRESS arm below — no extra case
	 * needed. (Newer kernels add FLOW_BLOCK_BINDER_TYPE_FT; add it here if
	 * this driver is forward-ported.) */
	if (f->binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS &&
	    f->binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS)
		return -EOPNOTSUPP;

	f->driver_block_list = &zx_ft_block_cb_list;

	switch (f->command) {
	case FLOW_BLOCK_BIND:
		block_cb = flow_block_cb_alloc(zx_ft_setup_cb, e, e, NULL);
		if (IS_ERR(block_cb))
			return PTR_ERR(block_cb);
		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, &zx_ft_block_cb_list);
		return 0;
	case FLOW_BLOCK_UNBIND:
		block_cb = flow_block_cb_lookup(f->block, zx_ft_setup_cb, e);
		if (!block_cb)
			return -ENOENT;
		flow_block_cb_remove(block_cb, f);
		list_del(&block_cb->driver_list);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}

static int zx_eth_setup_tc(struct net_device *ndev, enum tc_setup_type type,
			   void *type_data)
{
	struct zx_eth *e;

	/* Two netdev flavours share this hook with DIFFERENT netdev_priv
	 * layouts: the idm%d user netdevs store a (struct zx_eth_port *),
	 * while the `sw` conduit stores a (struct zx_eth *) directly. DSA's
	 * TC_SETUP_FT delegation targets the conduit (sw), so detect it and
	 * decode priv accordingly — misreading it here would deref garbage. */
	if (ndev->netdev_ops == &zx_eth_netdev_ops) {
		struct zx_eth_port *port = *(struct zx_eth_port **)netdev_priv(ndev);

		e = port->eth;
	} else {
		e = *(struct zx_eth **)netdev_priv(ndev);
	}

	switch (type) {
	case TC_SETUP_BLOCK:
	case TC_SETUP_FT:
		return zx_eth_setup_block(e, type_data);
	default:
		return -EOPNOTSUPP;
	}
}

/* chip_tm_init's trap_queue setup — replays def_ptl_pkt_map via cla_set_cpu_queue_id.
 * RE'd from switch.ko:chip_tm_init @ 0x36ac calling tm.ko functions.
 * Per stock, maps each (ptype, port) → CPU queue id. Port 5 is CPU (skipped).
 */
#include "zx_pkt_map.h"

static int zx_cla_set_cpu_queue_id(struct zx_eth *e, u32 addr, u8 qid)
{
	u32 ram7_data[17] = {0,};

	ram7_data[0] = qid;
	/* Reuses zx_cla_write_entry: writes data[0..16] then CMD with ram_id<<22.
	 * For trap_queue setup we only set data[0]=qid, rest 0.
	 */
	return zx_cla_write_entry(e, 7, addr, ram7_data);
}

