// SPDX-License-Identifier: GPL-2.0-only
/* Included from zx-eth-main.c — single translation unit. */

	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = 0;
	if (!e->pm_ext)
		return -ENODEV;
	if (sscanf(buf, "%7s", cmd) != 1)
		return -EINVAL;

	/* [ft_lock] this node pokes the SAME PM-external DDR carve that
	 * zx_ft_ext_flow_write/_clear (the FT install/untrack path, held
	 * under zx_hwlock via zx_ft_setup_cb) read/write per-flow — serialize
	 * every branch below against that path + sibling debugfs tools. */
	mutex_lock(&zx_hwlock);
	if (!strcmp(cmd, "z")) {
		memset_io(e->pm_ext + ZX_PM_EXT_FLOW_DIR0, 0, 0x8000 * 16);
		memset_io(e->pm_ext + ZX_PM_EXT_FLOW_DIR1, 0, 0x8000 * 16);
		mutex_unlock(&zx_hwlock);
		pr_info("[ZXETH] extwrite: BOTH dir tables zeroed\n");
		return count;
	}
	if (!strcmp(cmd, "r")) {
		u8 ent[16];
		void __iomem *p;

		if (sscanf(buf, "%*s %x %x", &dir, &idx) != 2 || idx >= 0x8000) {
			mutex_unlock(&zx_hwlock);
			return -EINVAL;
		}
		p = e->pm_ext +
		    (dir ? ZX_PM_EXT_FLOW_DIR1 : ZX_PM_EXT_FLOW_DIR0) + idx * 16;
		memcpy_fromio(ent, p, 16);
		mutex_unlock(&zx_hwlock);
		pr_info("[ZXETH] ext dir%u[%#x] = %16ph\n", dir & 1, idx, ent);
		return count;
	}
	if (!strcmp(cmd, "w")) {
		if (sscanf(buf, "%*s %x %x %x %x %x",
			   &dir, &idx, &w[0], &w[1], &w[2]) != 5 || idx >= 0x8000) {
			mutex_unlock(&zx_hwlock);
			return -EINVAL;
		}
		zx_extwrite_one(e, dir & 1, idx, w);
		mutex_unlock(&zx_hwlock);
		pr_info("[ZXETH] extwrite dir%u[%#x] = %08x %08x %08x\n",
			dir & 1, idx, w[0], w[1], w[2]);
		return count;
	}
	if (!strcmp(cmd, "f") || !strcmp(cmd, "enc")) {
		bool enc = cmd[0] == 'e';

		if (sscanf(buf, "%*s %x %x %x %x %x %x",
			   &dir, &idx, &cnt, &w[0], &w[1], &w[2]) != 6 ||
		    idx >= 0x8000 || cnt > 0x8000 || idx + cnt > 0x8000) {
			mutex_unlock(&zx_hwlock);
			return -EINVAL;
		}
		for (i = idx; i < idx + cnt; i++) {
			u32 fi[3] = { w[0], w[1], w[2] };

			if (enc) {
				u16 sp = ((dir & 1) << 15) | (i & 0x7fff);

				fi[0] = (fi[0] & ~(0x3fffu << 18)) |
					((u32)(sp & 0x3fff) << 18);
				fi[1] = (fi[1] & ~3u) | (sp >> 14);
			}
			zx_extwrite_one(e, dir & 1, i, fi);
		}
		mutex_unlock(&zx_hwlock);
		pr_info("[ZXETH] extwrite %s dir%u[%#x..%#x] base %08x %08x %08x\n",
			cmd, dir & 1, idx, idx + cnt - 1, w[0], w[1], w[2]);
		return count;
	}
	mutex_unlock(&zx_hwlock);
	return -EINVAL;
}

static const struct file_operations zx_extwrite_fops = {
	.owner = THIS_MODULE,
	.open  = simple_open,
	.write = zx_extwrite_write,
	.llseek = default_llseek,
};

/* fttest: DEBUG/TEST-ONLY entry point into the real zx_ft_flow_reserve() /
 * zx_ft_install_recipe() / zx_ft_flow_untrack() functions with a
 * synthetic, test-controlled cookie and 5-tuple, so a regression test
 * (scratchpad/regress.py's replace_orphan) can drive the exact production
 * self-REPLACE / partial-install / DESTROY code paths — including the
 * [H3 fix 2026-07-04] zx_ft_uninstall() rollback call — deterministically,
 * without depending on nf_flowtable ever choosing to redeliver a real
 * connection's cookie with a changed tuple (it structurally can't:
 * nf_flow_table_offload.c assigns cls->cookie = (unsigned long)&tuple, a
 * fixed sub-struct address inside the flow_offload object for that
 * direction, so a genuinely different 5-tuple on the SAME cookie never
 * occurs via real traffic on this conduit path — see
 * findings/fix_h3_rollback_2026-07-04.md for the full reachability
 * analysis). This node reuses the exact static functions the real
 * FLOW_CLS_REPLACE/DESTROY dispatch (zx_ft_setup_cb) calls; it does not
 * duplicate any install/rollback logic of its own.
 *   install <cookie> <saddr> <daddr> <sport> <dport> <eg_regport>  (all hex
 *     except eg_regport, which is decimal; TCP always assumed)
 *   destroy <cookie>                                                (hex)
 * A fixed test next-hop MAC (02:00:00:00:00:01, locally-administered) is
 * used for install — the recipe's CLA/PM writes don't require a resolvable
 * real neighbor, only zx_ft_flower_replace's caller-side zx_ft_resolve_nh()
 * does, and this node bypasses that caller entirely. */
static ssize_t zx_fttest_write(struct file *f, const char __user *ubuf,
			       size_t count, loff_t *ppos)
{
	struct zx_eth *e = f->private_data;
	static const u8 test_mac[ETH_ALEN] = { 0x02, 0x00, 0x00, 0x00, 0x00, 0x01 };
	struct zx_ft_nat nat = {0};
	char buf[128];
	unsigned long cookie;
	unsigned int saddr, daddr, sport, dport, eg_regport;
	unsigned int key_hdr = ZX_FT_KEY_HDR_ETH;
	u16 raw, raw0 = 0, pm_slot = 0;
	bool is_dn, has_raw0;
	int n, rc;

	if (count == 0 || count >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = 0;

	if (sscanf(buf, "destroy %lx", &cookie) == 1) {
		mutex_lock(&zx_hwlock);
		rc = zx_ft_flow_untrack(e, cookie);
		mutex_unlock(&zx_hwlock);
		pr_info("[fttest] destroy cookie=%lx rc=%d\n", cookie, rc);
		return count;
	}
	/* [H4 fix 2026-07-04, findings/qa_static_bughunt_2026-07-04.md] "resolve
	 * <devname>": drive the REAL, unmodified zx_ft_egress_regport() (the
	 * exact function zx_ft_flower_replace() calls on every REPLACE) against
	 * a live net_device looked up by name, and apply the same
	 * ZX_FT_EGRESS_INVALID guard zx_ft_flower_replace() applies, so a
	 * regression test can deterministically prove the H4 fix without
	 * needing to stage a genuine non-DSA nf_flowtable egress on real
	 * traffic. (Staging that live was attempted and found infeasible on
	 * this rig's topology -- see the regress.py h4_nondsa_decline
	 * docstring/findings/fix_h4_nondsa_2026-07-04.md for why -- so this
	 * exercises the identical production resolver + sentinel check via a
	 * deterministic, HW-write-free debugfs query instead. No installs, no
	 * HW state touched -- purely a resolve-and-report.) */
	{
		char devname[IFNAMSIZ];

		if (sscanf(buf, "resolve %15s", devname) == 1) {
			struct net_device *d = dev_get_by_name(&init_net, devname);
			u8 rp = zx_ft_egress_regport(d);
			/* [Phase C 2026-07-27] also report the wifi resolution
			 * (real helper, gated by ftwifi like production). */
			u8 we = zx_ft_wifi_essid(e, d);

			if (rp != ZX_FT_EGRESS_INVALID)
				pr_info("[fttest] resolve dev=%s -> VALID regport=%u\n",
					devname, rp);
			else if (we != ZX_FT_EGRESS_INVALID)
				pr_info("[fttest] resolve dev=%s -> WIFI essid=0x%02x (idm%u ssid%u)\n",
					devname, we, (we >> 3) & 1, we & 7);
			else
				pr_info("[fttest] resolve dev=%s -> INVALID (H4 guard would decline; ftwifi=%u)\n",
					devname, READ_ONCE(e->ft_wifi_en));
			if (d)
				dev_put(d);
			return count;
		}
	}
	/* [Stage-3 WiFi UP 2026-07-28] optional 7th arg = key_hdr (hex): the
	 * flow-key header byte (0x48 eth default; 0x38/0x30 = fabric idm1/idm0)
	 * so the WiFi-UP fabric-keyed install path is white-box testable
	 * without staging a live WiFi client (mirrors the production
	 * zx_ft_wifi_ing_hdr resolution, which real traffic exercises). */
	n = sscanf(buf, "install %lx %x %x %x %x %u %x",
		   &cookie, &saddr, &daddr, &sport, &dport, &eg_regport,
		   &key_hdr);
	if (n == 6 || n == 7) {
		if (n == 6)
			key_hdr = ZX_FT_KEY_HDR_ETH;
		is_dn = eg_regport != ZX_WAN_REGPORT;
		has_raw0 = is_dn;	/* fabric UP: poly-1 ways only */
		mutex_lock(&zx_hwlock);
		raw = zx_ft_flow_hash(e, IPPROTO_TCP, htonl(saddr), htonl(daddr),
				      htons((u16)sport), htons((u16)dport), is_dn,
				      (u8)key_hdr);
		if (has_raw0)
			raw0 = zx_ft_flow_hash_poly0(IPPROTO_TCP, htonl(saddr),
						     htonl(daddr), htons((u16)sport),
						     htons((u16)dport), is_dn,
						     (u8)key_hdr);
		rc = zx_ft_flow_reserve(e, cookie, raw, has_raw0, raw0, &pm_slot);
		if (rc == 0)
			rc = zx_ft_install_recipe(e, IPPROTO_TCP, htonl(saddr),
						  htonl(daddr), htons((u16)sport),
						  htons((u16)dport), test_mac,
						  eg_regport & 0xff, pm_slot, &nat,
						  (u8)key_hdr);
		mutex_unlock(&zx_hwlock);
		pr_info("[fttest] install cookie=%lx key_hdr=0x%02x raw=0x%04x raw0=0x%04x pm_slot=%u rc=%d\n",
			cookie, key_hdr, raw, raw0, pm_slot, rc);
		return count;
	}
	return -EINVAL;
}

static const struct file_operations zx_fttest_fops = {
	.owner = THIS_MODULE,
	.open  = simple_open,
	.write = zx_fttest_write,
	.llseek = default_llseek,
};

/* pmpeek: read back a PM RAM entry. "<ram_id> <addr>" (hex) → logs 8 words. */
static ssize_t zx_pmpeek_write(struct file *f, const char __user *ubuf,
			       size_t count, loff_t *ppos)
{
	struct zx_eth *e = f->private_data;
	char buf[64];
	u32 ram_id = 0, addr = 0, data[8] = {0};
	int rc;

	if (count == 0 || count >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = 0;
	if (sscanf(buf, "%x %x", &ram_id, &addr) != 2)
		return -EINVAL;
	/* [ft_lock] serialize against the FT/DSA offload paths + sibling
	 * debugfs pokes on the PM engine. */
	mutex_lock(&zx_hwlock);
	rc = zx_pp_pm_read_entry(e, ram_id & 0xff, addr, data);
	mutex_unlock(&zx_hwlock);
	pr_info("[ZXETH] pmpeek pm-ram%u addr%#x rc=%d: %08x %08x %08x %08x %08x %08x %08x %08x\n",
		ram_id, addr, rc, data[0], data[1], data[2], data[3],
		data[4], data[5], data[6], data[7]);
	return rc ? rc : count;
}

static const struct file_operations zx_pmpeek_fops = {
	.owner = THIS_MODULE,
	.open  = simple_open,
	.write = zx_pmpeek_write,
	.llseek = default_llseek,
};

/* pmfill: write ONE PM flow_info entry (8 words) to ALL in-PM ram0 slots [0..0x3ff],
 * to brute-force the CLA→flow_info linkage index (analogue of fill520 for the CLA hash).
 * "<w0> ... <w7>" hex. Used to test whether a routed flow HW-forwards once the flow_info
 * (→next-hop) is present at whatever index the CLA match links to. */
static ssize_t zx_pmfill_write(struct file *f, const char __user *ubuf,
			       size_t count, loff_t *ppos)
{
	struct zx_eth *e = f->private_data;
	char buf[160];
	u32 data[8] = {0};
	int n = 0, consumed, ok = 0;
	unsigned int a;
	char *p;

	if (count == 0 || count >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = 0;
	p = buf;
	while (n < 8 && sscanf(p, "%x%n", &data[n], &consumed) == 1) {
		n++;
		p += consumed;
	}
	/* [ft_lock] serialize this bulk 0x400-slot write against the FT/DSA
	 * offload paths + sibling debugfs pokes on the PM engine. */
	mutex_lock(&zx_hwlock);
	for (a = 0; a < 0x400; a++)
		if (zx_pp_pm_write_entry(e, 0, a, data) == 0)
			ok++;
	mutex_unlock(&zx_hwlock);
	pr_info("[ZXETH] pmfill: flow_info (%d words) -> %d ram0 slots\n", n, ok);
	return count;
}

static const struct file_operations zx_pmfill_fops = {
	.owner = THIS_MODULE,
	.open  = simple_open,
	.write = zx_pmfill_write,
	.llseek = default_llseek,
};

/* mdio: live read/write of a PHY register via the mii_bus (WAN ZX5201 = phy 8).
 * "<phy> <reg>" reads (logs value); "<phy> <reg> <val>" writes. For diagnosing +
 * bringing up the WAN copper link without a rebuild per attempt. */
static ssize_t zx_mdio_write(struct file *f, const char __user *ubuf,
			     size_t count, loff_t *ppos)
{
	struct zx_eth *e = f->private_data;
	struct mii_bus *bus = NULL;
	char buf[64];
	u32 phy = 0, reg = 0, val = 0;
	int n, k, v;

	if (count == 0 || count >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = 0;
	n = sscanf(buf, "%x %x %x", &phy, &reg, &val);
	if (n < 2)
		return -EINVAL;
	for (k = 0; k < 5; k++)
		if (e->gephy[k]) {
			bus = e->gephy[k]->mdio.bus;
			break;
		}
	if (!bus) {
		pr_err("[ZXETH] mdio: no mii_bus\n");
		return -ENODEV;
	}
	if (n == 3) {
		mdiobus_write(bus, phy, reg, val);
		pr_info("[ZXETH] mdio W phy%u reg%#x = %#06x\n", phy, reg, val);
	} else {
		v = mdiobus_read(bus, phy, reg);
		pr_info("[ZXETH] mdio R phy%u reg%#x = %#06x\n", phy, reg, v);
	}
	return count;
}

static const struct file_operations zx_mdio_fops = {
	.owner = THIS_MODULE,
	.open  = simple_open,
	.write = zx_mdio_write,
	.llseek = default_llseek,
};

/* hashcalc: drive the CLA HW hash engine (Phase 6 Stage 2b). Write up to 12 hex key
 * words "<k0> <k1> ... <k11>"; zx_cla_hash_raw loads them, triggers, and reads the
 * 16-bit raw hash, logged here. This is the slot oracle the chip uses on ingress —
 * cls_flower_add builds the key from a flow's 5-tuple+ports and uses the same path.
 * Verified vs manual poke: key 0x11/0x22../0xcc → 0x4a15. Fewer than 12 words →
 * the rest are zero. (Slot = raw & mask + way bits; mask from the outspace cfg.) */
static ssize_t zx_hashcalc_write(struct file *f, const char __user *ubuf,
				 size_t count, loff_t *ppos)
{
	struct zx_eth *e = f->private_data;
	char buf[160], *p;
	u32 key[12] = {0};
	int n = 0, consumed;
	u16 raw;

	if (count == 0 || count >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = 0;
	p = buf;
	while (n < 12 && sscanf(p, "%x%n", &key[n], &consumed) == 1) {
		n++;
		p += consumed;
	}
	/* [ft_lock] the hash engine's key/trigger/result regs are shared with
	 * the FT/DSA offload install paths — a concurrent install's key load
	 * could otherwise interleave with this one's trigger. */
	mutex_lock(&zx_hwlock);
	raw = zx_cla_hash_raw(e, key);
	mutex_unlock(&zx_hwlock);
	pr_info("[ZXETH] hashcalc %d words -> raw hash 0x%04x\n", n, raw);
	return count;
}

static const struct file_operations zx_hashcalc_fops = {
	.owner = THIS_MODULE,
	.open  = simple_open,
	.write = zx_hashcalc_write,
	.llseek = default_llseek,
};

/* poke: live register write for reflash-free experiments. Write "<phys> <val>"
 * (hex), e.g.  sh -c "echo '92280008 80000001' > /sys/kernel/debug/zx_eth/poke"
 * phys must be in [0x921c0000, 0x923c0000) (the e->base MMIO window) and 4-aligned.
 * Pairs with memdump/regdump for peeks. DEBUG ONLY.
 */
static ssize_t zx_poke_write(struct file *f, const char __user *ubuf,
			     size_t count, loff_t *ppos)
{
	struct zx_eth *e = f->private_data;
	char buf[64];
	u32 phys, val, off;

	if (count == 0 || count >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = 0;
	{
		int n = sscanf(buf, "%x %x", &phys, &val);

		if (n < 1)
			return -EINVAL;
		if (phys < 0x921c0000u || phys >= 0x921c0000u + 0x200000u || (phys & 3))
			return -EINVAL;
		off = phys - 0x921c0000u;
		if (n == 1) {	/* one arg = read-only PEEK (unlocks arbitrary mainline reg reads) */
			pr_info("[ZXETH] peek 0x%08x = 0x%08x\n", phys, readl(e->base + off));
			return count;
		}
		writel(val, e->base + off);
		pr_info("[ZXETH] poke 0x%08x = 0x%08x (readback 0x%08x)\n",
			phys, val, readl(e->base + off));
		return count;
	}
}

static const struct file_operations zx_poke_fops = {
	.owner  = THIS_MODULE,
	.open   = simple_open,
	.write  = zx_poke_write,
	.llseek = default_llseek,
};

/* fdbadd: seed one static HW (sbrag) FDB entry so the switch DIRECTS a unicast
 * to <port> instead of flooding it. Write "<port> <aa:bb:cc:dd:ee:ff>", e.g.
 *   echo '2 c8:a3:62:e9:59:00' > /sys/kernel/debug/zx_eth/fdbadd
 * Proves the HW-FDB-learning hypothesis for the lan2 dup storm. DEBUG ONLY.
 */
static ssize_t zx_fdbadd_write(struct file *f, const char __user *ubuf,
			       size_t count, loff_t *ppos)
{
	struct zx_eth *e = f->private_data;
	unsigned int port, m[6];
	char buf[64];
	u8 mac[6];
	int i, rc;

	if (count == 0 || count >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = 0;
	if (sscanf(buf, "%u %x:%x:%x:%x:%x:%x", &port,
		   &m[0], &m[1], &m[2], &m[3], &m[4], &m[5]) != 7)
		return -EINVAL;
	for (i = 0; i < 6; i++)
		mac[i] = m[i] & 0xff;
	rc = zx_sbrag_add_mac(e, mac, 0, port & 0xff);
	pr_info("[ZXETH] fdbadd %pM -> port %u = %d\n", mac, port, rc);
	return rc ? rc : count;
}

static const struct file_operations zx_fdbadd_fops = {
	.owner  = THIS_MODULE,
	.open   = simple_open,
	.write  = zx_fdbadd_write,
	.llseek = default_llseek,
};

/* [Iter AI] pktdeal: live-bisect the per-protocol SPA pktdeal RAM (0x921d4300).
 * Write "<proto> <deal>" to set that protocol-slot's action (0=forward 1=trap
 * 2=drop 3=copy) on ALL 8 ports at runtime, no reboot. Used to find which ptype
 * slot the chip assigns to TCP pure-ACKs: flip slots to 0 while a TCP flow runs
 * and watch tm_rx_count stop climbing. proto range 0..0x46 (slot 0x43+proto).
 *   echo '6 0' > /sys/kernel/debug/zx_eth/pktdeal   # forward proto-slot 6
 * Special: "all 0" forwards every slot 0..0x46 (= forward-all, breaks broadcast);
 * "stock" restores the zx_pp_pro_actions trap table. DEBUG ONLY. */
static ssize_t zx_pktdeal_write(struct file *f, const char __user *ubuf,
				size_t count, loff_t *ppos)
{
	struct zx_eth *e = f->private_data;
	unsigned int proto, deal;
	char buf[64];
	int port, i, ok = 0;

	if (count == 0 || count >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = 0;

	if (!strncmp(buf, "stock", 5)) {
		for (i = 0; i < ZX_PP_PRO_ACTION_COUNT; i++)
			for (port = 0; port < 8; port++)
				zx_spa_set_enty_pktdeal_cfg(e, port,
					zx_pp_pro_actions[i].proto,
					zx_pp_pro_actions[i].action_pp0);
		pr_info("[ZXETH] pktdeal: restored stock trap table\n");
		return count;
	}
	if (!strncmp(buf, "all ", 4) && sscanf(buf + 4, "%u", &deal) == 1) {
		for (proto = 0; proto <= 0x46; proto++)
			for (port = 0; port < 8; port++)
				if (zx_spa_set_enty_pktdeal_cfg(e, port, proto, deal & 3) == 0)
					ok++;
		pr_info("[ZXETH] pktdeal: ALL slots 0..0x46 -> deal=%u (%d writes)\n", deal & 3, ok);
		return count;
	}
	if (sscanf(buf, "%u %u", &proto, &deal) != 2 || proto > 0x46)
		return -EINVAL;
	for (port = 0; port < 8; port++)
		if (zx_spa_set_enty_pktdeal_cfg(e, port, proto & 0xff, deal & 3) == 0)
			ok++;
	pr_info("[ZXETH] pktdeal: proto-slot %u -> deal=%u on %d ports\n", proto, deal & 3, ok);
	return count;
}

static const struct file_operations zx_pktdeal_fops = {
	.owner  = THIS_MODULE,
	.open   = simple_open,
	.write  = zx_pktdeal_write,
	.llseek = default_llseek,
};

/* txtest: inject N known TX frames straight through zx_sw_xmit — isolates the
 * TX/egress path (no ARP/RX/ping involved). Frame: dst = host MAC (FDB-resolved
 * to internal port 3 / MAC[2]), src = device MAC, ethertype 0x88b5 (local
 * experimental, so it isn't mistaken for ARP/IP if it loops back), payload
 * "ZXTX"+seq. Read the pipeline counters before/after to see where it dies.
 *   sh -c "echo 5 > /sys/kernel/debug/zx_eth/txtest"
 */
static ssize_t zx_txtest_write(struct file *f, const char __user *ubuf,
			       size_t count, loff_t *ppos)
{
	struct zx_eth *e = f->private_data;
	static const u8 host_mac[6] = { 0xc8, 0xa3, 0x62, 0xe9, 0x59, 0x00 };
	char buf[16];
	unsigned int n = 1, i;

	if (!e->sw_dev)
		return -ENODEV;
	if (count >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = 0;
	if (kstrtouint(buf, 0, &n) || n == 0)
		n = 1;
	if (n > 64)
		n = 64;

	for (i = 0; i < n; i++) {
		struct sk_buff *skb = netdev_alloc_skb(e->sw_dev, 64);
		u8 *p;

		if (!skb)
			break;
		p = skb_put(skb, 64);
		memset(p, 0, 64);
		memcpy(p, host_mac, 6);
		memcpy(p + 6, e->sw_dev->dev_addr, 6);
		p[12] = 0x88; p[13] = 0xb5;
		p[14] = 'Z'; p[15] = 'X'; p[16] = 'T'; p[17] = 'X'; p[18] = (u8)i;
		skb->dev = e->sw_dev;
		zx_sw_xmit(skb, e->sw_dev);
	}
	pr_info("[ZXETH] txtest: injected %u known frames (dst=host, ethertype 0x88b5)\n", i);
	return count;
}

static const struct file_operations zx_txtest_fops = {
	.owner  = THIS_MODULE,
	.open   = simple_open,
	.write  = zx_txtest_write,
	.llseek = default_llseek,
};

/* [Stage-3 WiFi Phase B, 2026-07-23] wifi_bind: manually bind/unbind a WiFi
 * vif to an IDM ring + ssid (spec §5 step 2 — decouples "does the dispatch
 * mechanism work" from "how is the (idm,ssid) mapping discovered", the latter
 * being an open policy question, spec §6.3). BUILD-VERIFIED, UNTESTED ON
 * HARDWARE.
 *   Bind:    echo '<ifname> <idm> <ssid>' > wifi_bind   # e.g. 'wlan1 0 0'
 *   Unbind:  echo 'del <idm> <ssid>'      > wifi_bind   # e.g. 'del 0 0'
 * Reading the file dumps the current 16-node table.
 * NOTE: netdev_rx_handler_register returns -EBUSY if the vif already has an
 * rx_handler (it does while a br0 member) — `brctl delif br0 <vif>` first
 * (spec §2.3 coexistence caveat). */
static ssize_t zx_wifi_bind_write(struct file *f, const char __user *ubuf,
				  size_t count, loff_t *ppos)
{
	/* .open is single_open() (for the seq-file read side), so
	 * f->private_data is the struct seq_file — the zx_eth pointer is in
	 * seq->private (== inode->i_private). Every OTHER write knob in this
	 * driver uses simple_open (private_data = i_private directly); this one
	 * combines a seq-file reader with a writer, hence the extra hop.
	 * [Fixed 2026-07-24 during on-device validation: the original
	 * build-verified code read f->private_data directly and would have
	 * dereferenced the seq_file as a zx_eth on the very first write.] */
	struct zx_eth *e = ((struct seq_file *)f->private_data)->private;
	char buf[64], ifname[IFNAMSIZ];
	unsigned int idm, ssid;
	struct net_device *vif;
	int rc;

	if (count == 0 || count >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = 0;

	if (sscanf(buf, "del %u %u", &idm, &ssid) == 2) {
		rc = zx_wifi_unregister_vif(e, idm & 0xff, ssid & 0xff);
		pr_info("[ZXETH] wifi_bind: del idm%u ssid%u = %d [UNTESTED]\n",
			idm, ssid, rc);
		return rc ? rc : count;
	}

	if (sscanf(buf, "%15s %u %u", ifname, &idm, &ssid) != 3)
		return -EINVAL;

	vif = dev_get_by_name(&init_net, ifname);
	if (!vif)
		return -ENODEV;
	rc = zx_wifi_register_vif(e, vif, idm & 0xff, ssid & 0xff);
	dev_put(vif);	/* register took its own ref on success */
	pr_info("[ZXETH] wifi_bind: %s idm%u ssid%u = %d [UNTESTED]\n",
		ifname, idm, ssid, rc);
	return rc ? rc : count;
}

static int zx_wifi_bind_show(struct seq_file *s, void *unused)
{
	struct zx_eth *e = s->private;
	int i;

	seq_puts(s, "# IDM<->WiFi dispatch table (Stage-3 Phase B)\n");
	seq_printf(s, "# rx_dispatched=%u rx_nobind=%u tx_injected=%u\n",
		   e->idm_wifi_rx_dispatched, e->idm_wifi_rx_nobind,
		   e->idm_wifi_tx_injected);
	seq_printf(s, "# tm_rx_fabric=%u tm_rx_dispatched=%u tm_rx_nobind=%u noparse=%u (Phase B.2)\n",
		   e->tm_rx_fabric, e->tm_wifi_rx_dispatched,
		   e->tm_wifi_rx_nobind, e->tm_wifi_rx_noparse);
	seq_puts(s, "# node idm ssid  vif        idm_ndev\n");
	for (i = 0; i < 16; i++) {
		struct zx_wifi_dispatch_node *n = &e->zx_wifi_dispatch[i];

		if (!n->enabled)
			continue;
		seq_printf(s, "  %2d   %u    %u    %-10s %s\n",
			   i, n->idm, n->ssid,
			   n->wlan_ndev ? n->wlan_ndev->name : "(null)",
			   n->idm_ndev ? n->idm_ndev->name : "(null)");
	}
	return 0;
}

static int zx_wifi_bind_open(struct inode *inode, struct file *file)
{
	return single_open(file, zx_wifi_bind_show, inode->i_private);
}

static const struct file_operations zx_wifi_bind_fops = {
	.owner   = THIS_MODULE,
	.open    = zx_wifi_bind_open,
	.read    = seq_read,
	.write   = zx_wifi_bind_write,
	.llseek  = seq_lseek,
	.release = single_release,
};

/* ============================================================
 *   pipeline_stats — mirror stock /sys/devices/platform/tm/tmTest/{tmup,tmdn}
 *
 *   This is the OBSERVABILITY layer (gap matrix [A01], Layer 0).
 *   Each line maps to a counter stock prints; lines marked (TODO) are
 *   for register offsets we haven't pinned down yet — they'll fill in
 *   as future iters implement each block's accessors.
 *
 *   Diff against stock: capture stock tmup/tmdn via the kmsg trick
 *   (tasks/00.01.eth-driver/scripts/stock_fpga_dump.sh pattern) and
 *   compare line-by-line.
 *
 *   Stock reference live capture:
 *     tasks/00.01.eth-driver/findings/stock_runtime_visibility_2026-05-27.md
 * ============================================================
 */

/* MAC[N] cumulative byte/packet counters at +0x710..+0x71c.
 * Per-port base = e->base + (port+1) * MAC_STRIDE (existing mac_off helper).
 * Verified on stock 2026-05-27 via memdump @ 0x9220071[0-c], 0x9228071[0-c], etc.
 */
static int zx_pipeline_stats_show(struct seq_file *s, void *_unused)
{
	struct zx_eth *e = s->private;
	int p;

	seq_puts(s, "=== mainline pipeline_stats — mirror of stock tmTest/{tmup,tmdn} ===\n");
	seq_puts(s, "Stock reference: tasks/00.01.eth-driver/findings/stock_runtime_visibility_2026-05-27.md\n");
	seq_puts(s, "Lines marked (TODO) wait for the corresponding block's reg accessor (subsequent gap-matrix iters).\n\n");

	/* ---------- UPSTREAM (UNI → CPU) ---------- */
	seq_puts(s, "upstream statistics:\n");
	for (p = 0; p < 5; p++) {
		void __iomem *mac = e->base + mac_off(p, 0);
		/* CORRECTED: MAC[N]+0x710..0x71c are TX-side counters, NOT RX
		 * (per agent 9 smac_real_counters_re.md). Real wire-side RX
		 * counters: MAC[N]+0x780 (rx pkts), +0x784 (rx bytes).
		 */
		u32 rx_pkts  = readl(mac + 0x780);	/* receive total frames */
		u32 rx_crc   = readl(mac + 0x794);	/* receive CRC error frames */
		u32 rx_ovf   = readl(mac + 0x7d4);	/* receive overflow error */
		u32 rx_wdog  = readl(mac + 0x7dc);	/* receive watchdog err */
		u32 rx_uc    = readl(mac + 0x7c4);	/* receive good unicast */

		seq_printf(s, "  smac%d RX_pkts=%u good_uc=%u | ERR crc=%u ovf=%u wdog=%u\n",
			   p, rx_pkts, rx_uc, rx_crc, rx_ovf, rx_wdog);
	}

	/* [port1 hunt 2026-06-01] Per-uni ingress chain — localizes where a
	 * port's frames are lost between MAC-RX and the CPU. uni == logical port. */
	seq_puts(s, "  ingress chain (uni=logical port):\n");
	for (p = 0; p < 5; p++) {
		u32 spa_rcv = readl(e->base + 0x145cc + p * 4);	/* SPA per-uni receive */
		u32 sdet_tr = readl(e->base + 0x4160 + p * 4);	/* SDET egress_transport_cnt [7:0] */

		seq_printf(s, "    uni%d: SPA_rcv=0x%08x  SDET_transport=%u (raw 0x%08x)\n",
			   p, spa_rcv, sdet_tr & 0xff, sdet_tr);
	}
	/* [2026-06-01] LAN→CPU ingress is UPSTREAM → the relevant QMG counters are
	 * the UP set (0xc054/5c/60); 0xc044/48/4c are DN (egress). Print both. */
	seq_printf(s, "  QMG DN sw_fwd=%u hw_fwd=%u hw_trap=%u | UP sw_fwd=%u hw_fwd=%u hw_trap=%u | SIPC drop=0x%08x\n",
		   readl(e->base + TM_OFF + 0xc044),
		   readl(e->base + TM_OFF + 0xc048),
		   readl(e->base + TM_OFF + 0xc04c),
		   readl(e->base + TM_OFF + 0xc054),
		   readl(e->base + TM_OFF + 0xc05c),
		   readl(e->base + TM_OFF + 0xc060),
		   readl(e->base + 0xc004));
	seq_printf(s, "  drops: PP[0x1a040]=%u RED[0x1a044]=%u DSCH[0x1a04c]=%u\n",
		   readl(e->base + 0x1a040),
		   readl(e->base + 0x1a044),
		   readl(e->base + 0x1a04c));
	seq_printf(s, "  CLA fwd[0x1cc3c0]=%u drop[0x1cc3c8]=%u copy[0x1cc3d8]=%u | SADM pass[0x1c4200]=%u drop[0x1c4208]=%u\n",
		   readl(e->base + 0x1cc3c0),
		   readl(e->base + 0x1cc3c8),
		   readl(e->base + 0x1cc3d8),
		   readl(e->base + 0x1c4200),
		   readl(e->base + 0x1c4208));

	/* ---------- [A02] new MMIO regions (sys_ctrl / pin_mux / pon_serdes) ---------- */
	seq_puts(s, "\nextras mapped via DT (gap [A02]):\n");
	if (e->sys_ctrl) {
		seq_printf(s, "  sys_ctrl[0x10]   = 0x%08x  (stock=0x00000100 — bit 11 clear)\n",
			   readl(e->sys_ctrl + 0x10));
	} else {
		seq_puts(s, "  sys_ctrl         = (not mapped)\n");
	}
	if (e->pon_serdes) {
		seq_printf(s, "  pon_serdes[0x40] = 0x%08x  (stock=0x043c0000 — bit 26 = band ena)\n",
			   readl(e->pon_serdes + 0x40));
		seq_printf(s, "  pon_serdes[0x44] = 0x%08x  (stock=0xea2ca013 — bits 16-21 = coarse band 0x2c)\n",
			   readl(e->pon_serdes + 0x44));
		seq_printf(s, "  pon_serdes[0x68] = 0x%08x  (stock=0x00001558 — bit 4 = rxpll lock)\n",
			   readl(e->pon_serdes + 0x68));
		seq_printf(s, "  pon_serdes[0x70] = 0x%08x  (stock=0x01b15555 — bit 24 = PLL band ready)\n",
			   readl(e->pon_serdes + 0x70));
	} else {
		seq_puts(s, "  pon_serdes       = (not mapped)\n");
	}
	if (e->pin_mux) {
		seq_printf(s, "  pin_mux[0x00]    = 0x%08x  (stock=0x0f0ffffa)\n",
			   readl(e->pin_mux + 0x00));
	} else {
		seq_puts(s, "  pin_mux          = (not mapped)\n");
	}

	/* ---------- DOWNSTREAM (CPU → UNI) ---------- */
	seq_puts(s, "\ndownstream statistics:\n");
	seq_puts(s, "  (TODO) QMG sw fwd / hw fwd / hw trap pkts         [need TM_QMG offsets]\n");
	seq_puts(s, "  (TODO) DSCH in / out que pkts                     [need TM_DSCH offsets]\n");
	for (p = 0; p < 5; p++)
		seq_printf(s, "  (TODO) sopc_send2smac%d                            [need NPP_Sopc per-port offset]\n", p);

	/* ---------- ERROR COUNTERS ---------- */
	seq_puts(s, "\nerror counters (all should be 0 on healthy path):\n");
	seq_puts(s, "  (TODO) smct(0x14..0x54) — sipc_err / mult_err / drop_err / res_more / des_err\n");
	seq_puts(s, "  (TODO) bmu(0x30..0x39)  — sw_alcecnt / *_erlscnt / normal+jumbo_bperr\n");
	seq_puts(s, "  (TODO) qmg(0x0c, 0x37..0x42) — fifo_err / cache_active_N\n");
	seq_puts(s, "  (TODO) red(0x2b) reg_up_dbg, pp_ctrl(0x25) ram_left_cnt\n");
	seq_puts(s, "  (TODO) uopc(0xa2..0xb1) — no_sop_err / no_eop_err / wr_no_*_err_high\n");

	/* ---------- DRIVER-INTERNAL COUNTERS ---------- */
	seq_puts(s, "\n=== driver-internal counters (mainline ground truth) ===\n");
	seq_printf(s, "tm_irq_count         = %u\n", e->tm_irq_count);
	seq_printf(s, "tm_napi_count        = %u\n", e->tm_napi_count);
	seq_printf(s, "tm_rx_count          = %u\n", e->tm_rx_count);
	seq_printf(s, "tm_rx_loopback_drops = %u\n", e->tm_rx_loopback_drops);
	seq_printf(s, "tm_tx_count          = %u\n", e->tm_tx_count);
	seq_printf(s, "tm_tx_dropped        = %u\n", e->tm_tx_dropped);
	seq_printf(s, "sw_tx_pending        = %u (max %u)\n",
		   e->sw_tx_pending, e->sw_tx_pending_max);
	seq_printf(s, "sw_tx_reclaimed      = %u\n", e->sw_tx_reclaimed);
	seq_printf(s, "sw_tx_full_drops     = %u (queue_stops %u)\n",
		   e->sw_tx_full_drops, e->sw_tx_queue_stops);
	seq_printf(s, "tm_bmu_free_ok       = %u\n", e->tm_bmu_free_ok);
	seq_printf(s, "tm_bmu_free_fail     = %u\n", e->tm_bmu_free_fail);

	return 0;
}

static int zx_pipeline_stats_open(struct inode *inode, struct file *f)
{
	return single_open(f, zx_pipeline_stats_show, inode->i_private);
}

static const struct file_operations zx_pipeline_stats_fops = {
	.owner   = THIS_MODULE,
	.open    = zx_pipeline_stats_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = single_release,
};

static void zx_debugfs_init(struct zx_eth *e)
{
	zx_debugfs_root = debugfs_create_dir("zx_eth", NULL);
	debugfs_create_file("stats", 0444, zx_debugfs_root, e, &zx_stats_fops);
	debugfs_create_file("mem",   0444, zx_debugfs_root, e, &zx_mem_fops);
	debugfs_create_file("pipeline_stats", 0444, zx_debugfs_root, e,
			    &zx_pipeline_stats_fops);
	debugfs_create_file("regdump", 0444, zx_debugfs_root, e, &zx_regdump_fops);
	debugfs_create_file("cladump", 0444, zx_debugfs_root, e, &zx_cladump_fops);
	debugfs_create_file("clapeek", 0644, zx_debugfs_root, e, &zx_clapeek_fops);
	debugfs_create_file("clawrite", 0644, zx_debugfs_root, e, &zx_clawrite_fops);
	debugfs_create_file("hashcalc", 0644, zx_debugfs_root, e, &zx_hashcalc_fops);
	debugfs_create_file("fill520", 0644, zx_debugfs_root, e, &zx_fill520_fops);
	debugfs_create_file("pmwrite", 0644, zx_debugfs_root, e, &zx_pmwrite_fops);
	debugfs_create_file("mdio", 0644, zx_debugfs_root, e, &zx_mdio_fops);
	debugfs_create_file("pmpeek", 0644, zx_debugfs_root, e, &zx_pmpeek_fops);
	debugfs_create_file("pmfill", 0644, zx_debugfs_root, e, &zx_pmfill_fops);
	debugfs_create_file("poke", 0644, zx_debugfs_root, e, &zx_poke_fops);
	debugfs_create_file("fdbadd", 0644, zx_debugfs_root, e, &zx_fdbadd_fops);
	debugfs_create_file("fttest", 0644, zx_debugfs_root, e, &zx_fttest_fops);
	debugfs_create_file("extwrite", 0644, zx_debugfs_root, e,
			    &zx_extwrite_fops);
	debugfs_create_u32("ftup", 0644, zx_debugfs_root, &e->ft_up_en);
	/* [Stage-3 WiFi Phase C 2026-07-27] WiFi-egress offload gate, default 0
	 * (= pre-Phase-C baseline). STILL default-OFF: the sustained
	 * fabric-ingress wedge is NOT fixed. A 2026-07-31 candidate ([A09] SoC
	 * AXI-QoS init) survived 205k HW-forwarded frames in one run but the
	 * wedge reproduced at inj=1755 on the very next fresh boot of the SAME
	 * build — so that run was environmental luck, not a fix. Read the
	 * variance warning in
	 * findings/wifi_stage3_wedge_topcrm_axiqos_2026-07-31.md before ever
	 * flipping this on the strength of a single endurance run. */
	debugfs_create_u32("ftwifi", 0644, zx_debugfs_root, &e->ft_wifi_en);
	/* [Phase C R1 validation 2026-07-28] dispatch xmit mode (0 = direct
	 * ndo_start_xmit, stock parity, DEFAULT — HW-validated 7.65 MB/s;
	 * 1 = dev_queue_xmit, works but ~4x slower) + hexdump re-arm knob. */
	e->ft_wifi_dispatch_qx = 0;
	debugfs_create_u32("wifi_dispatch_qx", 0644, zx_debugfs_root,
			   &e->ft_wifi_dispatch_qx);
	debugfs_create_u32("idm_rx_dump", 0644, zx_debugfs_root,
			   &e->idm_wifi_rx_dumped);
	debugfs_create_file("pktdeal", 0644, zx_debugfs_root, e, &zx_pktdeal_fops);
	debugfs_create_file("txtest", 0644, zx_debugfs_root, e, &zx_txtest_fops);
	/* [Stage-3 WiFi Phase B, 2026-07-23] manual (idm,ssid)<->vif binding
	 * knob — BUILD-VERIFIED, UNTESTED ON HARDWARE (spec §5 step 2). */
	debugfs_create_file("wifi_bind", 0644, zx_debugfs_root, e,
			    &zx_wifi_bind_fops);
	dev_dbg(e->dev, "debugfs ready: /sys/kernel/debug/zx_eth/{stats,mem,pipeline_stats,regdump,poke,txtest}\n");
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
	/* NETIF_F_HW_TC gates tc_can_offload() so the flow_block binds (MTK pattern).
	 * Enables HW flow-offload (nf_flow_table) delegation into ndo_setup_tc. */
	ndev->hw_features |= NETIF_F_HW_TC;
	ndev->features |= NETIF_F_HW_TC;
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
	netdev_dbg(ndev, "registered (MAC %pM)\n", ndev->dev_addr);
	return 0;
}

/* MAC.ctrl values (RE'd from stock pon_npp_smac_enable/disable_part_*
 * + verified live by toggling MAC[3].ctrl via devmem2 on stock —
 * see tasks/00.01.eth-driver/findings/phy_irq_state_machine_2026-05-27.md).
 *
 * Bits 0+1 are the RX/TX enable pair; stock always moves them together.
 * Bit 19 starts set (smac_init writes 0xBAE003) and clears on the first
 * link UP for the lifetime of the device. We don't model the sticky
 * bit explicitly — just write the full value, which already has bit 19
 * cleared in both runtime values.
 */
#define MAC_CTRL_LINK_UP	0xBA6003u	/* enabled + bit 19 clear */
#define MAC_CTRL_LINK_DOWN	0xBA6000u	/* disabled + bit 19 clear */

/* adjust_link callback fired by the phylib state machine whenever any
 * attached PHY's link state changes. We have all 4 GePHYs attached to
 * the same sw netdev (the CPU-side aggregate), so this callback fires
 * for every PHY transition. Walk our cached pointers, detect which one
 * flipped, and update the corresponding MAC[port].ctrl.
 */
static void zx_eth_adjust_link(struct net_device *ndev)
{
	struct zx_eth *e = *(struct zx_eth **)netdev_priv(ndev);
	int i;

	for (i = 0; i < 5; i++) {	/* [WAN] incl. MAC4/WAN link-up bring-up */
		struct phy_device *phy = e->gephy[i];
		bool now, is_wan, full;
		int spd;

		/* [WAN] MAC4's PHY (external ZX5201 @ MDIO 0x08) is NOT phylib-
		 * probed — it doesn't present a standard PHY ID, so gephy[4]==NULL.
		 * Treat the WAN port as a FIXED 1G/full link that's always up: the
		 * external PHY auto-negotiates with the peer on its own (host gets
		 * carrier). This brings up MAC4 (smac_init + speed/duplex + SOPC
		 * admit) whenever a LAN PHY link event fires zx_eth_adjust_link. */
		is_wan = (i == 4 && !phy);
		if (!phy && !is_wan)
			continue;
		now  = is_wan ? true : phy->link;
		spd  = is_wan ? SPEED_1000 : phy->speed;
		full = is_wan ? true : (phy->duplex == DUPLEX_FULL);
		if (now == e->phy_was_link[i])
			continue;

		/* [Iter 24] Per agent 7 finding (phy_init_perturbs_bmu_re.md):
		 * stock's extphy_timer_func issues pon_reset(1<<(N+6)) on every
		 * link-state transition to clear any wedged TX FIFO state from
		 * the RGMII glitch caused by PHY analog config. Mirror that
		 * before re-enabling the MAC: bit (N+6) of pon[8] toggled
		 * low→high pulses the per-port reset. Skip for unconnected ports
		 * (only if we have pon_early mapped — sanity check).
		 */
		if (e->pon_early) {
			u32 mask = 1u << (i + 6);
			u32 v = readl(e->pon_early + 8);

			writel(v & ~mask, e->pon_early + 8);
			msleep(10);                           /* stock pattern */
			writel(v | mask, e->pon_early + 8);
		}

		/* [lead #1 fix 2026-05-29] The probe-time global pon_reset(0xffffffff)
		 * AND the per-port pon_reset pulse just above WIPE the MAC block —
		 * MASK, ENABLE and the +0xe0 serializer bond all go to 0, so MAC[N]
		 * is not truly live and SOPC never issues send2smacN (CPU->LAN egress
		 * dies before the wire; live-confirmed MAC2 MASK/EN/iface=0). The old
		 * code only re-wrote CTRL here. Stock ALWAYS re-runs the full smac_init
		 * after a reset pulse — mirror that so the MAC comes back fully live
		 * (CTRL+MASK+ENABLE+iface+NPP enable). */
		if (now) {
			void __iomem *mc = e->base + mac_off(i, MAC_REG_CONTROL);
			u32 c;

			/* (2) smac_init reset values: ctrl=0xBAE003, mask, en, +0xe0 (stock plat:3195) */
			zx_smac_init_port(e, i);

			/* (3) config_speed_duplex — the EXPLICIT ctrl rewrite that sets the
			 * RUNNING value (stock plat:2737 / config_speed_duplex_part_0). For
			 * gigabit/FD: clear bit15 (0x8000), set bit13 (0x2000) => 0xBA6003 (the
			 * proven working value). bit15 is cleared HERE — before the SOPC bridge
			 * handshake and before MAC enable — NOT later in the TX path. This is the
			 * piece the old code skipped (it left ctrl at 0xBAE003). */
			c = readl(mc);
			if (spd == SPEED_1000) {
				c = (c & ~0x8000u) | 0x2000u;
			} else {
				c = full ? (c | 0xa000u)
					 : ((c & ~0x2000u) | 0x8000u);
				c = (spd == SPEED_100) ? (c | 0x4000u)
						       : (c & ~0x4000u);
			}
			writel(c, mc);
		} else {
			writel(MAC_CTRL_LINK_DOWN,
			       e->base + mac_off(i, MAC_REG_CONTROL));
		}

		/* [Iter 28] Stock sw_port_alarm_kthread writes fpga[0xd3000]
		 * on link state change. The reg is TM[0xc000] (= phys
		 * 0x9234c000). Values:
		 *   0x01f40fa0  link DOWN (sw_alarm_init initial)
		 *   0x03f40050  link UP
		 *
		 * Empirical 2026-05-28: writing 0x03f40050 made QMG up
		 * hw_trap counter (TM[0xc060]) increment from 2 → 13 under
		 * ping load — frames now flow from CLA to QMG! Without this,
		 * QMG silently drops CPU-bound frames. Mainline never
		 * updated this reg (Iter 11 disproved A11 at the time,
		 * but A11 IS load-bearing now that carved DMA + SOPC bridge
		 * + 5 BMU instances are all in place).
		 */
		/* [Iter AA 2026-06-04] QMG queue threshold 0x9234c000:
		 *   [12:0]=up_ram_thd, [25:13]=dn_ram_thd (per DATASHEET).
		 * Stock link-UP value 0x03f40050 = up_thd=0x050(80), dn_thd=0x1fa0(8096):
		 * the UP (CPU/trap) queue is starved (80) while DN is ample (8096). Stock
		 * gets away with up=80 because it HW-forwards TCP in BOTH directions, so
		 * the UP/CPU queue carries almost nothing. MAINLINE traps the reverse
		 * (ACK) direction to the CPU → that starved UP queue floods → the wedge.
		 * MITIGATION (diverge from stock): raise up_ram_thd 80→0xfa0(4000) on
		 * link-UP so the trapped UP traffic can buffer. New link-UP = 0x03f40fa0
		 * (up=4000, dn=8096 unchanged). UNTESTED-pending-HW (2-NIC TCP, USB-blocked).
		 * The deeper stock-faithful fix is to make the UP dir HW-forward (no trap).
		 */
		writel(now ? 0x03f40fa0 : 0x01f40fa0,
		       e->base + TM_OFF + TM_QMG_THD);

		/* [Iter 25] SOPC↔SMAC bridge handshake at NPP[0x19068].
		 * Per agent 8 (phy_mac_rgmii_wedge_re.md) — THIS is the
		 * gate that lets the switch fabric route frames in/out of
		 * MAC[N]. Stock smac_sopc_mode_switch (plat:2290) +
		 * U-Boot FUN_40e50c40: on link UP, poll bit (port+5) for
		 * "PHY-MAC link-ready", then set bit port for SOPC→SMAC
		 * bridge enable. On link DOWN, clear bit port to disable
		 * the bridge.
		 */
		if (now) {
			void __iomem *mc = e->base + mac_off(i, MAC_REG_CONTROL);
			int retries = 20;
			u32 ready_bit = 1u << (i + 5);
			u32 enable_bit = 1u << i;
			u32 duplex_bit = 1u << (i + 16);	/* NPP[0x19038] half-duplex flag */
			u32 reg;
			bool ready = false;

			/* (4) smac_sopc_mode_switch (stock plat:2290): poll the PHY-MAC READY
			 * bit (port+5), then set the bridge ENABLE bit (port) ONLY when ready
			 * was observed — stock sets it inside the if. Writing the enable while
			 * not-ready does NOT latch the bridge (why the old unconditional write
			 * read back 0). */
			while (retries-- > 0) {
				reg = readl(e->base + NPP_REG_SOPC_BRIDGE);
				if (reg & ready_bit) {
					ready = true;
					break;
				}
				udelay(100);
			}
			if (ready) {
				writel(reg | enable_bit, e->base + NPP_REG_SOPC_BRIDGE);
				netdev_info(ndev, "[egress] PHY[%d] SOPC bridge ENABLED (ready): NPP[0x19068] %#x → %#x\n",
					    i, reg, readl(e->base + NPP_REG_SOPC_BRIDGE));
			} else {
				netdev_warn(ndev, "[egress] PHY[%d] SOPC ready bit %d NEVER set (NPP[0x19068]=%#x) — bridge NOT enabled\n",
					    i, i + 5, reg);
			}

			/* [Iter 25b] NPP[0x19038] bit (port+16) = half-duplex flag.
			 * Stock smac_sopc_mode_switch (plat:2305): sets bit if
			 * duplex != 1 (= half), clears if duplex == 1 (= full).
			 * For our 1000/FD this should be cleared.
			 */
			reg = readl(e->base + NPP_REG_SOPC_DUPLEX);
			if (full)
				writel(reg & ~duplex_bit, e->base + NPP_REG_SOPC_DUPLEX);
			else
				writel(reg | duplex_bit, e->base + NPP_REG_SOPC_DUPLEX);

			/* (5) enable — ctrl |= 3 (rx/tx en) as the FINAL step, AFTER the
			 * bridge handshake (stock pon_npp_smac_enable / enable_part_3,
			 * plat:3198). smac_init set these bits already, but stock enables
			 * after the bridge is up, so re-assert here to match the order. */
			writel(readl(mc) | 0x3u, mc);
		} else {
			u32 reg = readl(e->base + NPP_REG_SOPC_BRIDGE);

			writel(reg & ~(1u << i), e->base + NPP_REG_SOPC_BRIDGE);
		}

		netdev_info(ndev, "PHY[%d]%s link %s @ %d/%s → MAC[%d].ctrl=%#x (port-reset bit %d pulsed)\n",
			    i, is_wan ? "(WAN)" : "", now ? "UP" : "DOWN",
			    now ? spd : 0,
			    now ? (full ? "FD" : "HD") : "-",
			    i,
			    now ? MAC_CTRL_LINK_UP : MAC_CTRL_LINK_DOWN,
			    i + 6);
		e->phy_was_link[i] = now;
	}
}

/* [WAN] Port of stock zx5201_config (plat:3224): the external WAN PHY ("ZX5201"
 * at MDIO 0x08, config page 0x09) needs this vendor magic to bring up its copper
 * TX driver. Without it CPU→MAC4 egress reaches QMG sw_fwd but the frame never
 * reaches the wire (the OPC won't issue send2smac4 to a port whose TX endpoint
 * isn't driving) — the ZX5201 equivalent of the GePHY TX-DAC force. The ZX5201 is
 * NOT phylib-probed (no standard PHY ID), so we drive it directly on the mii_bus.
 * See tasks/00.01.eth-driver/findings/{wan_port_bringup_re,mac4_egress_dispatch_re}.md */
static void zx_wan_zx5201_config(struct zx_eth *e, struct mii_bus *bus)
{
	int v, u;

	if (!bus)
		return;

	/* [WAN-RGMII] RGMII pad/clock setup that stock's zx5201_config does
	 * BEFORE the MDIO sequence — we skipped this and CPU->MAC4 TX never
	 * reached the wire (fabric dispatched to send2smac4 but MAC4 TX-ok=0).
	 *
	 * RE (Iter loop-4, agent): stock virt 0xf060000c == phys 0x9420000c ==
	 * pin_mux register #3 (the SoC pad / IO-mux / pad-drive bank). stock
	 * does  *0xf060000c &= 0xffe7f7ff  (clears pad bits 11,19,20) — these
	 * are the WAN-RGMII pad-mode/drive/delay bits for MAC4's interface.
	 * MAC0-3 are internal MII/GMII so they don't need it; MAC4 is RGMII to
	 * the external ZX5201, which does. pin_mux is already ioremapped.
	 * Cites: ghidra/output_ko/plat-zxylzb_9128S.ko/zx5201_config.c:16,
	 *        ghidra/output_pcie_extra/FUN_c0016c68_c0016c68.c:45-55.
	 */
	if (e && e->pin_mux) {
		u32 pm = readl(e->pin_mux + 0x0c);

		writel(pm & 0xffe7f7ff, e->pin_mux + 0x0c);
		dev_dbg(e->dev, "[WAN-RGMII] pin_mux[0x0c] %08x -> %08x (clear pad bits 11/19/20)\n",
			 pm, readl(e->pin_mux + 0x0c));
	}
	/* [WAN-RGMII] sys_ctrl[0x10] bit 11 = the RGMII select bit; stock boot
	 * clears it (&= ~0x800) and stock-live reads 0x100 (bit 11 clear).
	 * Enforce it (harmless if already clear). phys 0x94100010. */
	if (e && e->sys_ctrl) {
		u32 sc = readl(e->sys_ctrl + 0x10);

		if (sc & 0x800) {
			writel(sc & ~0x800u, e->sys_ctrl + 0x10);
			dev_dbg(e->dev, "[WAN-RGMII] sys_ctrl[0x10] %08x -> %08x (clear RGMII bit 11)\n",
				 sc, readl(e->sys_ctrl + 0x10));
		}
	}

	mdiobus_write(bus, 8, 0x12, 0x8402);
	mdiobus_write(bus, 9, 0x16, 0x0a0f);
	mdiobus_write(bus, 9, 0x1b, 0x0800);
	mdiobus_write(bus, 8, 0x1d, 0x0355);
	mdiobus_write(bus, 8, 0x10, 0xb62d);
	mdiobus_write(bus, 8, 0x11, 0x0006);
	mdiobus_write(bus, 9, 0x12, 0x0004);
	v = mdiobus_read(bus, 9, 0x15);
	u = mdiobus_read(bus, 9, 0x14);
	mdiobus_write(bus, 9, 0x11, (((v < 0) ? 0 : v) & 0xc1ff) | 0x2800);
	mdiobus_write(bus, 9, 0x10, (u < 0) ? 0 : u);
	mdiobus_write(bus, 9, 0x12, 0x0204);
	v = mdiobus_read(bus, 9, 0x16);
	mdiobus_write(bus, 9, 0x16, (((v < 0) ? 0 : v) & 0xfff3) | 4);
	/* Bring the copper link UP. The old `BMCR |= 0x800` (mis-annotated "power-up"
	 * from stock plat:3317) actually SET bit11 = POWER-DOWN, leaving the ZX5201
	 * powered down so the host PHY never linked (carrier=0). CLEAR bit11 + enable
	 * & restart autoneg. VERIFIED LIVE 2026-06-06 (debugfs mdio): clearing bit11
	 * brings the host link up at 1000/FD. */
	v = mdiobus_read(bus, 8, 0);
	if (v < 0)
		v = 0;
	mdiobus_write(bus, 8, 0, (v & ~0x800u) | 0x1200u);	/* ~power-down | AN-en | AN-restart */
}

/*
 * Attach each GePHY to the sw netdev so phylib's state machine drives
 * our adjust_link callback on link changes. After phy_init_hw fires
 * the vendor config (LDO + TX DAC), phy_attach_direct wires the PHY
 * to the netdev, phy_request_interrupt arms the GIC IRQ line that the
 * DT declared, and phy_start kicks the state machine.
 *
 * All 4 PHYs share the sw netdev because we don't yet have per-port
 * netdevs (that's the DSA refactor). adjust_link detects which PHY
 * flipped by walking e->gephy[] and comparing against phy_was_link[].
 *
 * EXPERIMENTAL — implemented from RE evidence and stock register
 * snapshot diff, not yet bench-tested on mainline. See
 * findings/phy_irq_state_machine_2026-05-27.md for the empirical
 * validation that drove this design.
 */
/* Set ZX_SKIP_PHY_INIT=1 to skip mainline's phy_init_hw + phy_attach.
 * Per user 2026-05-28 suggestion: U-Boot leaves PHYs initialized; let
 * mainline inherit that state instead of overwriting it. Caveat:
 * pon_reset(0xffffffff) in A03 may already wipe U-Boot state — this
 * test will tell us if PHY config_init is needed or if U-Boot's state
 * suffices.
 */
#define ZX_SKIP_PHY_INIT  0

static void zx_eth_init_phys(struct zx_eth *e)
{
	struct device *dev = e->dev;
	struct device_node *np = dev->of_node;
	int n = of_count_phandle_with_args(np, "zte,gephys", NULL);
	int i;

	if (n <= 0) {
		dev_info(dev, "no zte,gephys phandles in DT (n=%d)\n", n);
		return;
	}
	if (n > 5)		/* [WAN] up to 5: 4 LAN GePHYs + the WAN ZX5201 @ MDIO 0x08 */
		n = 5;

	if (ZX_SKIP_PHY_INIT) {
		dev_dbg(dev, "ZX_SKIP_PHY_INIT=1 — leaving PHYs in U-Boot state, no phy_init_hw/attach\n");
		return;
	}

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
		if (ret)
			dev_warn(dev, "  [%d] phy_init_hw(%s) = %d\n",
				 i, phydev_name(phydev), ret);

		/* Hook the PHY to sw netdev so phylib's state machine
		 * routes link-change events to zx_eth_adjust_link.
		 * Multiple attach to the same netdev: the netdev's
		 * phydev pointer will end up as the last-attached one;
		 * we don't care, we use our own e->gephy[] array.
		 */
		if (e->sw_dev) {
			ret = phy_attach_direct(e->sw_dev, phydev, 0,
						PHY_INTERFACE_MODE_INTERNAL);
			if (ret) {
				dev_warn(dev, "  [%d] phy_attach_direct = %d\n",
					 i, ret);
				put_device(&phydev->mdio.dev);
				continue;
			}
			phydev->adjust_link = zx_eth_adjust_link;
			/* Use phylib POLLING, not the per-PHY link IRQ. Live HW test
			 * (2026-05-31): the GePHY link-change IRQs (GIC SPI 0x47..0x4a)
			 * do NOT fire for the cabled ports — moving the cable jack1->jack2
			 * left irq 18/19/20 at 0 and adjust_link never ran, so the new
			 * port's MAC was never re-inited (dead port until reboot). Only the
			 * unconnected PHY[3] spuriously storms its line (~650/s, ~30M total).
			 * Stock doesn't rely on these IRQs either — it polls via
			 * extphy_timer_func (decomp_all_plat_zxylzb_9128S.c:3137). PHY_POLL
			 * makes phylib's state machine poll link (~1s) and call
			 * zx_eth_adjust_link -> zx_smac_init_port on every change (hotplug
			 * works without reboot), and disabling the PHY IRQ also stops the
			 * PHY[3] storm. See findings/multiport_root_cause_macinit.md.
			 */
			phydev->irq = PHY_POLL;
			phy_start(phydev);
			e->gephy[i] = phydev;
			e->phy_was_link[i] = false;
			/* phy_attach_direct already takes its own reference;
			 * drop the of_phy_find_device one to balance.
			 */
			put_device(&phydev->mdio.dev);
		} else {
			/* No netdev yet — just init_hw and release. */
			put_device(&phydev->mdio.dev);
		}
	}
	dev_dbg(dev, "PHY init complete (%d GePHYs attached)\n", n);

	/* [WAN] bring up the external ZX5201 WAN PHY (MDIO 0x08) — not phylib-probed,
	 * so config it directly on the mii_bus (borrow a GePHY's bus). */
	{
		struct mii_bus *bus = NULL;
		int k;

		for (k = 0; k < 5; k++)
			if (e->gephy[k]) {
				bus = e->gephy[k]->mdio.bus;
				break;
			}
		if (bus) {
			zx_wan_zx5201_config(e, bus);
			dev_dbg(dev, "[WAN] ZX5201 PHY @ MDIO 0x08 configured (copper TX up)\n");
		} else {
			dev_warn(dev, "[WAN] no mii_bus to config ZX5201 PHY\n");
		}
	}
}

/*
 * Enable the PON-subsystem clocks via the SoC's TOPCRM block.
 *
 * Stock does this in zx_pon_clk_reset_init: read-modify-write bit 5-8
 * of TOPCRM[0x0C], then poke TOPCRM[0x4c] and [0x08] to the stock-match
 * values that turn on the FPGA → GIC IRQ routing we depend on. Linux
 * defaults leave many of those bits cleared.
 *
 * The TOPCRM base address is resolved from the `zte,topcrm` phandle on
 * our DT node (points at a syscon@94000000 sibling).
 */
/* Forward declarations — defined further below. */
static void zx_eth_init_chip_tm(struct zx_eth *eth);
static void zx_eth_repoint_tm_descriptors(struct zx_eth *eth);
static void zx_eth_register_cpu_mac_slots(struct zx_eth *eth);
static void zx_eth_clear_spa_trap_dmac(struct zx_eth *eth);

/*
 * Replay the captured stock init sequence per HW block, in the same
 * order stock's boot does it.
 *
 * For each block we call either:
 *   - an explicit zx_<block>_init() helper (blocks where we have
 *     decoded the writes into readable C), or
 *   - zx_stock_apply_block() which streams the still-generic
 *     (off,val) ops from zx_stock_bursts.h.
 *
 * Decoded blocks let us drop the corresponding entries from the
 * generated ops table (via SKIP_BLOCKS in
 * tasks/00.01.eth-driver/scripts/gen_stock_bursts.py) so the data we
 * ship stays minimal.
 */
static void zx_eth_apply_stock_init(struct zx_eth *eth)
{
	zx_pon_low_init(eth);                 /* 4 sub-blocks × 4 writes */
	zx_stock_apply_block(eth, "PON_B",
			     ZX_STOCK_OPS_PON_B_START,    ZX_STOCK_OPS_PON_B_END);
	zx_pon_tail_lookup_init(eth);         /* 16 KB lookup RAM */
	zx_stock_apply_block(eth, "PON_TAIL",
			     ZX_STOCK_OPS_PON_TAIL_START, ZX_STOCK_OPS_PON_TAIL_END);
	zx_npp_twin_init(eth);                /* 3 twin-pair sub-blocks */
	zx_stock_apply_block(eth, "NPP",
			     ZX_STOCK_OPS_NPP_START,      ZX_STOCK_OPS_NPP_END);
	zx_npp_aux_init(eth);                 /* 13 × 12 identical writes */
	zx_tm_per_instance_init(eth);         /* 16 instance tables */
	zx_stock_apply_block(eth, "TM",
			     ZX_STOCK_OPS_TM_START,       ZX_STOCK_OPS_TM_END);
	zx_stock_apply_block(eth, "PP_FUC",
			     ZX_STOCK_OPS_PP_FUC_START,   ZX_STOCK_OPS_PP_FUC_END);
}

/*
 * TM subsystem bring-up — the path that carries CPU↔switch traffic.
 *
 * Returns 0 if either (a) we initialised the TM/sw netdev successfully
 * or (b) the DT didn't declare a "tm" IRQ (in which case the sw netdev
 * is intentionally disabled and the rest of the driver can still run
 * for idm0/idm1 wifi conduits). Returns non-zero only on real errors
 * — the caller should propagate that to its err_napi unwind path.
 *
 * Bring-up order matches stock tm_pon_tm_init:
 *
 *   1. alloc bppe/bp/rxdesc/txdesc coherent pools
 *   2. pre-init / RED / PP_CTRL / PP_BRG / DMA / BMU init / BMU enable
 *   3. create the "sw" netdev (the CPU port)
 *   4. wire up the TM IRQ
 *   5. seed CPU MAC slots (pp_pm RAM[12])
 *   6. chip_tm_init tail (CLA + trap_queue + isolate + pro_action +
 *      sbrg IRQ enable)
 *   7. replay the pp_pm flow_info / sub_ram tables
 *   8. RE-write the TM RX/TX desc base regs so HW points at OUR DMA
 *      pool, not the stock-DDR addresses left by the replay.
 *      Mandatory — without this RX delivers from un-mapped memory.
 */
/* PM (G.988 Port-Mapper) + SPA source-port classifier init. Stock runs this via
 * tm_pon_npp_pm_initial / tm_pon_npp_spa_initial (decomp_all_tm.c:43376/43271); mainline
 * omitted it entirely (only the bare NPP_REG_SPA_INIT=0 in zx_npp_init). This is the
 * source→allowed-egress AUTHORIZER: without it the switch fabric loops CPU-sourced frames
 * back to the CPU (ingress=2) instead of egressing to a physical MAC — the live-confirmed
 * "QMG sw_fwd ticks but SOPC send2smac never fires, 0 on wire (even broadcast)" symptom.
 * Direct-register recipe (values cross-checked vs stock dump regs/stock_eth_2mib.txt). The
 * SPA match-RAM (indirect, ram_id 0) is NOT populated here yet — if egress still fails,
 * that table is the next piece. See pm_spa_init_recipe_re.md + cpu_source_port_egress_re.md.
 * Must run LAST in init so the bulk stock replay doesn't clobber 0x921e00xx.
 */
static void zx_pm_spa_init(struct zx_eth *e)
{
	int i;

	/* SPA up/dn packet-enable + match mode */
	npp_write(e, 0x14000, 0xffffffff);
	npp_write(e, 0x14004, 0xffffffff);
	npp_write(e, 0x14008, 0x00003fff);
	npp_write(e, 0x14040, 0xffffffff);
	npp_write(e, 0x14044, 0xffffffff);
	npp_write(e, 0x14048, 0x0007ffff);
	npp_write(e, 0x14054, readl(e->base + 0x14054) | 0x03000000);
	npp_write(e, 0x1407c, 0x00000001);		/* SPA match_mode = 1 */

	/* [port1 ingress fix 2026-06-02] SPA port_vlan_filter (0x142ac + port*4, [5:0]).
	 * Mainline left it at a non-zero reset default (p0=0x36 p1=0x26 p2=0x36 p3=0x27
	 * p4=0x36); stock clears all of them to 0. That non-zero per-port VLAN filter
	 * GATES port1's ingress→CPU trap (port1 frames pass MAC→SPA→SDET but are dropped
	 * at the OPC, never hw-trapped). LIVE-CONFIRMED: zeroing these (matching stock)
	 * makes port1's rx_per_ingress climb (0 → 18) — the long-standing port1 gate.
	 * x10 table; clear all to fully match stock. Runs in zx_pm_spa_init (last in init)
	 * so the bulk stock replay can't re-default it. */
	for (i = 0; i < 10; i++)
		npp_write(e, 0x142ac + i * 4, 0);

	/* PM in-port rule table (logical port i → entry i), 0..7 */
	for (i = 0; i < 8; i++)
		npp_write(e, 0x20180 + i * 4, i);

	/* PM G.988 modes (pm_set_g988_mode 1→1, 2→3) */
	npp_write(e, 0x20058, 0x00000001);
	npp_write(e, 0x2005c, 0x00000003);

	/* PM out-port rule idx0 valid (phys port0) + ctrl: inport_equal_outport_staen=1,
	 * cpu_not_drop_staen=0 (stock-live 0x921e0054=0xc0). Ctrl last. */
	npp_write(e, 0x201a0, 0x00000008);
	npp_write(e, 0x20054, 0x000000c0);
}

static int zx_eth_init_tm_subsystem(struct zx_eth *eth,
				    struct platform_device *pdev)
{
	struct device *dev = eth->dev;
	int err;

	eth->irq_tm = platform_get_irq_byname_optional(pdev, "tm");
	if (eth->irq_tm < 0) {
		dev_warn(dev, "no TM IRQ in DT — sw netdev disabled\n");
		return 0;
	}

	err = zx_tm_alloc_pools(eth);
	if (err)
		return dev_err_probe(dev, err, "TM pools alloc failed\n");

	zx_tm_pre_init(eth);
	zx_tm_red_init(eth);
	zx_red_block_init(eth);	/* [Iter Y] init the real RED block 0x92344000 (stock does, mainline didn't) */
	zx_pp_ctrl_init(eth);
	zx_pp_brg_init(eth);
	zx_tm_dma_init(eth);
	zx_tm_bmu_init(eth);
	zx_tm_post_bmu(eth);
	zx_tm_bmu_enable(eth);

	/* [A04] TM[0xc008] = 0. Stock plat:7080 — single write inside
	 * tm_pon_tm_init right after pon_tm_bmu_enable, purpose unknown
	 * but consistently present. Live mainline read before this was 0
	 * already (uninitialized HW default), so this is defensive parity
	 * with stock.
	 */
	/* Stock asserts TOPCRM[0x0c] |= 0x1e0 a SECOND time after all TM init
	 * (zx_pon_clk_reset in init_module). The re-write may trigger clock
	 * gating hw to re-evaluate after BMU is configured. */
	{
		void __iomem *crm = eth->topcrm;
		if (crm) {
			u32 v = readl(crm + 0x0c);
			writel(v | 0x1e0u, crm + 0x0c);
			dev_info(eth->dev, "[wedge fix #2] TOPCRM[0x0c] re-asserted post-BMU: 0x%08x\n",
				 readl(crm + 0x0c));
		}
	}

	tm_write(eth, 0xc008, 0);

	err = zx_sw_netdev_create(eth);
	if (err) {
		dev_err(dev, "sw netdev create failed: %d\n", err);
		goto err_pools;
	}

	err = devm_request_irq(dev, eth->irq_tm, zx_tm_irq, 0,
			       DRV_NAME "-tm", eth);
	if (err) {
		dev_err(dev, "TM IRQ request failed: %d\n", err);
		goto err_swdev;
	}

	zx_eth_register_cpu_mac_slots(eth);
	zx_eth_clear_spa_trap_dmac(eth);
	zx_eth_init_chip_tm(eth);
	zx_pp_pm_apply_replay(eth);   /* replay pp_pm flow_info / sub_ram */
	zx_eth_repoint_tm_descriptors(eth);

	/* Hand the binder (built-in zx-dsa) our working PM indirect-RAM path so its
	 * per-flow next-hop/flow_info writes commit to the live datapath PM RAM. */
	zx_pm_ops_eth = eth;
	zx_dsa_register_pm_ops(&zx_eth_pm_ops);

	dev_info(dev, "TM ready: IRQ=%d, sw netdev up, CPU MAC + CLA + pp_pm replay done\n",
		 eth->irq_tm);
	return 0;

err_swdev:
	unregister_netdev(eth->sw_dev);
	free_netdev(eth->sw_dev);
	netif_napi_del(&eth->tm_napi);
err_pools:
	zx_tm_free_pools(eth);
	return err;
}

/*
 * "chip_tm_init" tail — the four trap/classifier table replays and the
 * one-shot FPGA IRQ enable. Mirrors what stock's chip_tm_init() does
 * after the TM DMA/BMU are up:
 *
 *  1. CLA ACL hash replay  — programs the "trap-to-CPU" rules that
 *                            stock has at boot.
 *  2. trap_queue setup     — per-protocol CPU queue routing. Overrides
 *                            the blanket "qid=7" from cla_apply_replay
 *                            with the stock def_ptl_pkt_map (82 entries
 *                            × 8 banks: dir-0 qid0 into the 7 per-inport
 *                            banks + dir-1 qid1 into the base bank), and
 *                            re-steers the dead-q5 WiFi trap classes to q4
 *                            (wifi_stage3_qmg_queue5_consumer_re, A.1+A.2).
 *  3. per-port isolate     — chip_tm_init calls tm_port_isolate_set 8×.
 *                            This is the TM-side per-port mask, separate
 *                            from the PP_BRG_ISOLATE writes done earlier
 *                            in zx_eth_init_vlan_and_isolation().
 *  4. pro_action replay    — def_ptl_pkt_action: which protocols get
 *                            trapped to CPU. Without this, broadcasts
 *                            (ARP) never reach the netdev.
 *  5. FPGA IRQ enable      — stock's sbrg_set_irq_en_mask(0xa). Maps
 *                            to a single writel at fpga_base + 0 (the
 *                            raw IRQ enable mask via sbragRegTable[0]).
 *                            Without this the TM IRQ count stays 0.
 */
static void zx_eth_init_chip_tm(struct zx_eth *eth)
{
	zx_cla_apply_replay(eth);
	zx_cla_ffe_extract_init(eth);	/* Phase 6: FFE 5-tuple extract rules + index (HW fast-classify) */
	zx_chip_tm_init_trap_queues(eth);
	zx_chip_tm_init_isolate(eth);
	zx_chip_tm_init_pro_action(eth);

	writel(0xa, eth->fpga_base + 0);
	dev_dbg(eth->dev, "FPGA IRQ enable: wrote 0xa to fpga+0 (sbrg_set_irq_en_mask equiv)\n");
}

/*
 * The bulk stock_init replay we run during probe legitimately programs
 * the four stock DDR pointers it captured at boot time (TM rxdesc base
 * = 0x4ff1f000, TX_UP_BASE = 0x4ffdf000, TX_DN_BASE = 0x4ffef000).
 * Those addresses are valid for the stock kernel — they point to the
 * stock kernel's coherent DMA pool — but they're meaningless to us:
 * mainline allocates its own DMA buffers via dma_alloc_coherent(),
 * with phys addresses that depend on CMA placement at boot.
 *
 * Without re-pointing the registers, the TM ASIC writes RX descriptors
 * to whatever happens to live at 0x4ff1f000 (some random kernel page)
 * and reads TX descriptors from 0x4ffdf000 (garbage), so RX silently
 * corrupts memory and TX never leaves the chip.
 *
 * This must run AFTER zx_pp_pm_apply_replay() (which is where the
 * stock pointers get re-programmed) and BEFORE the netdev opens.
 */
static void zx_eth_repoint_tm_descriptors(struct zx_eth *eth)
{
	struct device *dev = eth->dev;
	int inst;

	for (inst = 0; inst < TM_NUM_INSTANCES; inst++) {
		u32 base = inst * TM_INSTANCE_STRIDE;

		tm_write(eth, base + 0xF0, eth->rxdesc_dma);
	}
	dev_dbg(dev, "Re-wrote TM[+0xF0] x%d to rxdesc_dma=%pad\n",
		TM_NUM_INSTANCES, &eth->rxdesc_dma);

	tm_write(eth, TM_REG_DMA_TX_UP_BASE, eth->txdesc_dma);
	/* [txflowctrl] distinct DN ring (stock topology); shared only under the
	 * zx_tx_dualkick=1 legacy fallback. */
	tm_write(eth, TM_REG_DMA_TX_DN_BASE,
		 zx_tx_dualkick ? eth->txdesc_dma : eth->dndesc_dma);
	dev_dbg(dev, "Re-wrote TM TX_UP=%pad DN=%pad\n",
		&eth->txdesc_dma, zx_tx_dualkick ? &eth->txdesc_dma : &eth->dndesc_dma);
}

/*
 * Register the sw netdev MAC across the CPU-port destination tables.
 *
 * Stock's pp_pm RAM[12] holds 4 distinct "CPU MAC" addresses (last byte
 * = M0..M3) replicated across 64 slots: positions where (slot & 0xF)
 * is less than 4. That spreads the four MACs across 16 groups of 16,
 * presumably indexed by GEMPORT / T-CONT for the GPON side.
 *
