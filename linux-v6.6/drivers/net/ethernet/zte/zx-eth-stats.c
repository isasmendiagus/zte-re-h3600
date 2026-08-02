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
	zx_pon_tail_explicit_init(eth);       /* 2 C loops replace 272 PON_TAIL bursts */
	zx_npp_twin_init(eth);                /* 3 twin-pair sub-blocks */
	zx_stock_apply_block(eth, "NPP",
			     ZX_STOCK_OPS_NPP_START,      ZX_STOCK_OPS_NPP_END);
	zx_npp_aux_init(eth);                 /* 13 × 12 identical writes */
	zx_tm_per_instance_init(eth);         /* 16 instance tables */
	zx_tm_explicit_init(eth);             /* 2 C loops replace 31 TM bursts */
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
 * Empirically the first 4 of each group of 16 are populated (slots
 * 0..3, 16..19, 32..35, ... 240..243). We mirror exactly that pattern
 * so the HW lookup hits a registered MAC regardless of which group
 * index it computes.
 */
static void zx_eth_register_cpu_mac_slots(struct zx_eth *eth)
{
	u8 mac[6];
	int sl;

	for (sl = 0; sl < 256; sl++) {
		if ((sl & 0xF) >= 4)
			continue;  /* only first 4 of each group of 16 */
		memcpy(mac, eth->sw_dev->dev_addr, 6);
		mac[5] += (sl & 0x03);
		zx_register_cpu_mac(eth, (u8)sl, mac);
	}
}

/* Clear the SPA destination-MAC filter table to match stock (empty).
 * The boot ROM pre-loads trap_dmac[0..3] with the device MACs (from fuses),
 * which makes the SPA parser send routed to-me-MAC transit to the CPU before
 * the CLA forward hash, blocking HW L3 forwarding. Stock keeps it empty; we do
 * too. ONU-MAC (registered above) stays populated so l3_en still arms.
 */
static void zx_eth_clear_spa_trap_dmac(struct zx_eth *eth)
{
	int sl;

	for (sl = 0; sl < 4; sl++) {
		writel(0, eth->base + ZX_SPA_TRAP_DMAC_BASE + sl * 8);
		writel(0, eth->base + ZX_SPA_TRAP_DMAC_BASE + sl * 8 + 4);
	}
	dev_dbg(eth->dev, "SPA trap_dmac filter cleared (match stock; enables HW L3 forward)\n");
}

/*
 * VLAN port-membership + per-port isolation masks. Mirrors the tail of
 * stock's pon_pp_brg_init.
 *
 * VLAN: vid 0 and 1, every one of the 8 ports gets membership type 3
 * (= tagged + untagged egress). 16 entries total, all should succeed.
 *
 * Isolation: per-port "block egress to these ports" bitmap.
 *   port 0..5: no self-loop (mask = ~(1<<port) & 0xff)
 *   port 6, 7 (CPU): 0xff = block ALL egress (CPU traffic exits via the
 *                    direct CPU FWD register, not the switch fabric)
 * Stock pon_pp_brg_init only OR'd 0xdf into ports 6/7 because the chip
 * already has HW defaults; mainline boots leave the masks zero, so we
 * write all eight explicitly.
 */
static void zx_eth_init_vlan_and_isolation(struct zx_eth *eth)
{
	struct device *dev = eth->dev;
	int vid, port, n_ok = 0;
	int i;

	for (vid = 0; vid < 2; vid++)
		for (port = 0; port < 8; port++)
			if (zx_vlan_add_port(eth, vid, port, 3) == 0)
				n_ok++;
	dev_dbg(dev, "VLAN setup: %d/%d port-vlan entries OK\n", n_ok, 16);

	for (i = 0; i < 6; i++)
		zx_port_isolate(eth, i, (u8)(~(1u << i) & 0xff));
	zx_port_isolate(eth, 6, 0xFF);
	zx_port_isolate(eth, 7, 0xFF);
	dev_dbg(dev, "isolate ports 0..7 = %#x %#x %#x %#x %#x %#x %#x %#x\n",
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(0)),
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(1)),
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(2)),
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(3)),
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(4)),
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(5)),
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(6)),
		 readl(eth->base + PP_OFF + PP_BRG_ISOLATE(7)));
}

/*
 * Map the two extra MMIO windows the driver needs alongside the DT-listed
 * "npp" resource:
 *
 *   pon_early : the "pon" reg-name resource (1.75 MiB at PON base),
 *               used by negative-offset stock writes.
 *   fpga_base : a unified 4 MiB window starting at the same PON base,
 *               used by descriptor-driven zx_fpga_table_write access.
 *               It overlaps the "pon" + "npp" resources plus a small
 *               tail; that's why it's not its own DT reg entry (DT
 *               bindings forbid overlapping resources).
 *
 * Both use plain devm_ioremap (no request_mem_region) so they can coexist
 * with the byname mapping of "pon" without resource-collision errors.
 */
static int zx_eth_init_extra_mmio(struct zx_eth *eth,
				  struct platform_device *pdev)
{
	struct device *dev = eth->dev;
	struct resource *pon_res;

	pon_res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pon");
	if (!pon_res)
		return dev_err_probe(dev, -ENODEV, "missing 'pon' reg\n");

	eth->pon_early = devm_ioremap(dev, pon_res->start,
				      resource_size(pon_res));
	if (!eth->pon_early)
		return dev_err_probe(dev, -ENOMEM, "ioremap PON early\n");

	eth->fpga_base = devm_ioremap(dev, pon_res->start, 0x400000);
	if (!eth->fpga_base)
		return dev_err_probe(dev, -ENOMEM, "ioremap fpga_base failed\n");

	return 0;
}

/* [phase6/ft] Map + ZERO the PM external table carve (see the pm_ext field
 * comment). The bases (acl @0x923a0024, pm @0x923a0020 = acl + 0x400000) are
 * pre-programmed (boot ROM / U-Boot) but read as GARBAGE until the PON/PP
 * block clocks are up — so this MUST run late in probe (after
 * zx_eth_init_pon_chip + the TM subsystem replay), NOT at iomap time.
 * Erased DDR there is 0xff, which the PM engine decodes as an all-enables
 * flow_info with garbage NAT values -> every HW-forwarded frame is mangled
 * (MACs/IPs zeroed, ports 0xffff). Stock zeroes this at aclRamInit.
 * pfn_valid() guard: NEVER touch pages the kernel owns (if a boot pointed
 * the bases into kernel RAM, skip instead of corrupt). */
static void zx_ft_pm_ext_init(struct zx_eth *eth)
{
	struct device *dev = eth->dev;
	u32 aclb = readl(eth->fpga_base + 0x3a0024);
	u32 pmb  = readl(eth->fpga_base + 0x3a0020);
	u32 carve = aclb - 0x20000u;

	if (aclb >= 0x40000000u && pmb == aclb + 0x400000u &&
	    region_intersects(carve, ZX_PM_EXT_SPAN, IORESOURCE_SYSTEM_RAM,
			      IORES_DESC_NONE) == REGION_DISJOINT) {
		eth->pm_ext_phys = carve;
		eth->pm_ext = devm_ioremap(dev, carve, ZX_PM_EXT_SPAN);
		if (eth->pm_ext) {
			/* Zero the FULL span again (safe as of 2026-07-31).
			 * History worth keeping straight: this memset used to
			 * clobber the BMU BPPE free-list, because BPPE was
			 * parked at CARVED_BPPE_OFF == this same carve base
			 * (0x4E700000), inside the 0x20000 head that the carve
			 * reserves ahead of the ACL table. Fix #1b worked around
			 * it by skipping the head. BPPE now lives at
			 * CARVED_BASE_PHYS+0 (stock-exact 0x4C000000), so the
			 * head is nobody's and the original full-span zero is
			 * both correct and desirable — erased DDR reads 0xff,
			 * which the PM engine decodes as an all-enables
			 * flow_info with garbage NAT values. Removing the
			 * special case removes the landmine: any future carve
			 * reshuffle can no longer silently re-create the
			 * overlap. */
			memset_io(eth->pm_ext, 0, ZX_PM_EXT_SPAN);
		dev_dbg(dev,
			 "[phase6/ft] PM external tables: carve 0x%08x +0x%x mapped, fully zeroed (BPPE now at carve+0, no overlap; acl 0x%08x pm 0x%08x)\n",
				 carve, ZX_PM_EXT_SPAN, aclb, pmb);
		}
	}
	if (!eth->pm_ext)
		dev_warn(dev,
			 "[phase6/ft] PM external tables UNAVAILABLE (acl 0x%08x pm 0x%08x) — HW-forward NAT rewrite would read erased DDR; offload rewrite disabled\n",
			 aclb, pmb);
}

static void zx_eth_iounmap_action(void *iomem)
{
	iounmap((void __iomem *)iomem);
}

/*
 * [A03][A05][A06] Chip-level PON init — pon_reset + 0x4001c poke +
 * full SERDES bring-up. Body lives in zx-pon-plat.c so the main eth
 * driver stays focused on netdev / NAPI / TX-RX hot path. We thread
 * just the IO bases through a small ctx struct so zx-pon-plat doesn't
 * have to know about struct zx_eth.
 */
static void zx_eth_init_pon_chip(struct zx_eth *eth)
{
	struct zx_pon_plat_ctx ctx = {
		.dev        = eth->dev,
		.pon_early  = eth->pon_early,
		.topcrm     = eth->topcrm,
		.sys_ctrl   = eth->sys_ctrl,
		.pin_mux    = eth->pin_mux,
		.pon_serdes = eth->pon_serdes,
	};

	zx_pon_plat_init(&ctx);
}

static int zx_eth_init_topcrm(struct zx_eth *eth)
{
	struct device *dev = eth->dev;
	struct device_node *np;
	int rc;

	np = of_parse_phandle(dev->of_node, "zte,topcrm", 0);
	if (!np)
		return dev_err_probe(dev, -ENODEV,
				     "missing zte,topcrm phandle\n");

	eth->topcrm = of_iomap(np, 0);
	of_node_put(np);
	if (!eth->topcrm)
		return dev_err_probe(dev, -ENOMEM,
				     "of_iomap TOPCRM failed\n");

	rc = devm_add_action_or_reset(dev, zx_eth_iounmap_action,
				      (void *)eth->topcrm);
	if (rc)
		return rc;

	writel(readl(eth->topcrm + TOPCRM_REG_PON_CLK) | TOPCRM_PON_CLK_BITS,
	       eth->topcrm + TOPCRM_REG_PON_CLK);
	dev_dbg(dev, "TOPCRM[0x0C] = %#x (PON clocks enabled)\n",
		readl(eth->topcrm + TOPCRM_REG_PON_CLK));

	writel(0x0003cfff, eth->topcrm + 0x4c);
	/* TOPCRM[0x08] = PON-domain reset/clock control. Stock + U-Boot do a
	 * reset-deassert EDGE on bits 4,5 (clear 0x30 → set 0x20 → set 0x10), NOT
	 * a single slam — the falling edge is what actually un-resets the egress
	 * sub-block (ETH_TM2 mux @0x923a0000, the SOPC egress). Slamming the final
	 * value left the block in its power-up reset state, silently dropping
	 * writes (0x923a00e0 read back 0; SMAC TX never incremented). See
	 * fpga_access_and_egress_clock_re.md + U-Boot FUN_40e4fc7c.
	 */
	writel(0x1ff7ffff & ~0x30u, eth->topcrm + 0x08);        /* deassert: clear reset bits 4,5 */
	udelay(100);
	writel((0x1ff7ffff & ~0x30u) | 0x20u, eth->topcrm + 0x08); /* set bit 5 */
	udelay(100);
	writel(0x1ff7ffff, eth->topcrm + 0x08);                 /* set bit 4 → final stock value, edge complete */
	dev_dbg(dev, "TOPCRM[0x4c]=%#x [0x08]=%#x (stock-match)\n",
		readl(eth->topcrm + 0x4c), readl(eth->topcrm + 0x08));

	return 0;
}

/* [WiFi productionization 2026-08-01] Netdevice notifier: auto-bind wlan
 * interfaces to the next free idm/ssid slot when hostapd creates them.
 * Uses the proven config as baseline (wlan1 → idm1/ssid4 corresponds to
 * slot index = ssid + idm*8 = 4 + 1*8 = 12). Generic policy: assign
 * sequentially starting from the first wlan slot.
 */
static int zx_wlan_notifier(struct notifier_block *nb,
			    unsigned long event, void *ptr)
{
	struct net_device *ndev = netdev_notifier_info_to_dev(ptr);
	struct zx_eth *e = container_of(nb, struct zx_eth, wlan_nb);
	int i;

	if (!ndev || !ndev->name)
		goto out;

	if (event == NETDEV_REGISTER &&
	    !strncmp(ndev->name, "wlan", 4)) {
		for (i = 0; i < 16; i++) {
			if (!READ_ONCE(e->zx_wifi_dispatch[i].enabled)) {
				u8 idm = i >> 3, ssid = i & 7;

				if (zx_wifi_register_vif(e, ndev, idm, ssid) == 0) {
					dev_info(e->dev,
						 "[wifi] auto-bind: %s -> idm%u/ssid%u (slot %d)\n",
						 ndev->name, idm, ssid, i);
				}
				break;
			}
		}
	} else if (event == NETDEV_UNREGISTER &&
		   !strncmp(ndev->name, "wlan", 4)) {
		for (i = 0; i < 16; i++) {
			struct zx_wifi_dispatch_node *wn = &e->zx_wifi_dispatch[i];

			if (READ_ONCE(wn->enabled) &&
			    wn->wlan_ndev == ndev) {
				/* Cache idm/ssid before clearing, unlock RTNL
				 * for the rx_handler unregister (the handler
				 * takes rtnl_lock internally). */
				u8 idm = wn->idm, ssid = wn->ssid;

				rtnl_unlock();
				zx_wifi_unregister_vif(e, idm, ssid);
				rtnl_lock();
				dev_info(e->dev,
					 "[wifi] auto-unbind: %s (was idm%u/ssid%u, slot %d)\n",
					 ndev->name, idm, ssid, i);
				break;
			}
		}
	}
out:
	return NOTIFY_DONE;
}

/**
 * zx_eth_probe() - Initialize the ZX279128S integrated Ethernet driver
 * @pdev: platform device matching "zte,zx279128s-eth"
 *
 * Maps 5 MMIO regions (pon, npp, sys_ctrl, pin_mux, pon_serdes),
 * performs the full SoC clock/reset sequence, replays ~22k stock
 * register writes, initializes the TM/BMU/RED/CLA/PP/IDM datapath,
 * creates the DSA conduit (sw) and WiFi offload (idm0/idm1) netdevs,
 * and registers debugfs and the PM ops bridge to the built-in DSA driver.
 *
 * Return: 0 on success, negative errno on failure.
 */
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
	/* [up-hwoffload 2026-07-04] UP HW-offload defaults ON now that the
	 * cmd_flow_id fetch-index packing is fixed (zx_ft_pack_cla up_idx_fix) —
	 * see the comment in the tc-flower ADD handler above the ft_up_en gate.
	 * debugfs "ftup" (0644) still allows forcing it back to 0 for A/B tests. */
	eth->ft_up_en = 1;

	/* [wedge #2 fix 2026-08-01] WiFi HW-offload defaults ON. The BMU pool
	 * priming fix (zx_tm_bmu_enable) eliminated the fabric-ingress endurance
	 * wedge — sustained WiFi UP HW-forwarding no longer starves the front-end.
	 * debugfs "ftwifi" (0644) still allows forcing it back to 0 for A/B tests. */
	eth->ft_wifi_en = 1;

	/* DTS exposes two reg entries — "pon" and "npp". Map the npp one
	 * by name so the driver is robust to reg-entry reordering. The pon
	 * mapping (and the topcrm syscon mapping) is done in dedicated
	 * helpers further below.
	 */
	eth->base = devm_platform_ioremap_resource_byname(pdev, "npp");
	if (IS_ERR(eth->base))
		return dev_err_probe(dev, PTR_ERR(eth->base), "ioremap NPP\n");

	/* [A02] Optional extras — older DTBs without these names won't error.
	 * We use the *_optional() byname helper so a missing resource returns
	 * NULL instead of failing probe. Subsequent iters (zx_pon_clk_reset_init
	 * et al.) will check for NULL and skip the feature if absent.
	 */
	{
		struct resource *r;

		r = platform_get_resource_byname(pdev, IORESOURCE_MEM, "sys_ctrl");
		eth->sys_ctrl = r ? devm_ioremap_resource(dev, r) : NULL;
		if (IS_ERR(eth->sys_ctrl))
			eth->sys_ctrl = NULL;

		r = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pin_mux");
		eth->pin_mux = r ? devm_ioremap_resource(dev, r) : NULL;
		if (IS_ERR(eth->pin_mux))
			eth->pin_mux = NULL;

		r = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pon_serdes");
		eth->pon_serdes = r ? devm_ioremap_resource(dev, r) : NULL;
		if (IS_ERR(eth->pon_serdes))
			eth->pon_serdes = NULL;

		dev_dbg(dev, "MMIO extras: sys_ctrl=%s pin_mux=%s pon_serdes=%s\n",
			 eth->sys_ctrl  ? "mapped" : "absent",
			 eth->pin_mux   ? "mapped" : "absent",
			 eth->pon_serdes ? "mapped" : "absent");
	}

	eth->irq_idm = platform_get_irq_byname(pdev, "idm");
	if (eth->irq_idm < 0)
		eth->irq_idm = platform_get_irq(pdev, 0);
	eth->irq_npp = platform_get_irq_byname_optional(pdev, "npp");
	/* [A07][A08] Optional PON / PP IRQs — present if DT has them. */
	eth->irq_pon = platform_get_irq_byname_optional(pdev, "pon");
	eth->irq_pp  = platform_get_irq_byname_optional(pdev, "pp");

	platform_set_drvdata(pdev, eth);

	/* Set the DMA mask before allocating coherent buffers */
	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	if (err)
		return dev_err_probe(dev, err, "failed to set DMA mask\n");

	err = zx_eth_init_topcrm(eth);
	if (err)
		return err;

	zx_pp_init(eth);
	zx_npp_init(eth);

	err = zx_eth_init_extra_mmio(eth, pdev);
	if (err)
		return err;

	/* [A03][A05] Chip-level pon_reset + small writes, before the bulk
	 * stock_table.h replay touches NPP/PP/TM regs. Stock init_module
	 * does these between of_iomap and tm_pon_tm_init.
	 */
	zx_eth_init_pon_chip(eth);

	zx_eth_apply_stock_init(eth);

	/* [txflowctrl] distinct UP/DN rings (stock topology); shared only under
	 * the zx_tx_dualkick=1 legacy fallback. */
	tm_write(eth, TM_REG_DMA_TX_UP_BASE, eth->txdesc_dma);
	tm_write(eth, TM_REG_DMA_TX_DN_BASE,
		 zx_tx_dualkick ? eth->txdesc_dma : eth->dndesc_dma);

	dev_dbg(dev, "PP[0x2c] (CPU_FWD) = %#x, IDM[0x8000] CTRL = %#x\n",
		 readl(eth->base + PP_OFF + PP_REG_CPU_FWD),
		 readl(eth->base + IDM_REG_CONTROL));

	zx_eth_init_vlan_and_isolation(eth);

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
	 * (boot UART capture).
	 */
	netif_napi_add_weight(eth->ports[0].netdev, &eth->napi, zx_idm_poll, 512);

	err = devm_request_irq(dev, eth->irq_idm, zx_idm_irq, 0,
			       DRV_NAME "-idm", eth);
	if (err) {
		dev_err(dev, "failed to request IDM IRQ %d: %d\n",
			eth->irq_idm, err);
		goto err_napi;
	}

	err = zx_eth_init_tm_subsystem(eth, pdev);
	if (err)
		goto err_napi;

	/* Source→egress authorizer (PM/SPA) — stock runs it, mainline omitted it. Runs
	 * after the bulk replay + TM subsystem so 0x921e00xx isn't clobbered. Without this
	 * CPU-sourced frames loop back to the CPU instead of egressing a physical MAC. */
	zx_pm_spa_init(eth);

	/* Re-assert the PON-subsystem clocks AFTER the datapath replay. Stock's
	 * pon_init (lan_up mode) calls zx_pon_clk_reset() (TOPCRM[0x0c] |= 0x1e0)
	 * as its TERMINAL step — after tm/pp/npp init — to re-bless the egress
	 * half, which the bulk replay can leave gated. Mainline only asserted it
	 * once in probe (zx_eth_init_topcrm), before the datapath. See
	 * eth_egress_clock_reset_re.md.
	 */
	if (eth->topcrm)
		writel(readl(eth->topcrm + TOPCRM_REG_PON_CLK) | TOPCRM_PON_CLK_BITS,
		       eth->topcrm + TOPCRM_REG_PON_CLK);

	/* [A07] Register PON aggregate IRQ — stock's register_pon_int
	 * equivalent. Mainline previously fetched irq_pon from DT but
	 * never requested it; the level-triggered GIC line would assert
	 * for any pending bit in pon[0x40040] AND ~pon[0x40044] and stay
	 * asserted with no service. Optional in DT (skip cleanly if absent).
	 */
	if (eth->irq_pon > 0) {
		err = devm_request_irq(dev, eth->irq_pon, zx_pon_irq, 0,
				       DRV_NAME "-pon", eth);
		if (err)
			dev_warn(dev, "[A07] PON IRQ %d request failed: %d (continuing)\n",
				 eth->irq_pon, err);
		else
			dev_dbg(dev, "[A07] PON IRQ %d registered\n",
				 eth->irq_pon);
	}

	/* PHY power-up (LDO + TX DAC) + attach to sw netdev for link-state
	 * tracking. Must run AFTER zx_eth_init_tm_subsystem so e->sw_dev is
	 * valid for phy_attach_direct.
	 */
	zx_eth_init_phys(eth);

	/* Intentionally no FDB seeding here.
	 *
	 * Stock helpSpa shows the switch port mapping as 0-4=UNI / 5=PON /
	 * 6-7=WiFi — i.e. there is NO "CPU" port number. CPU-bound traffic
	 * reaches the host via a side channel: cpu_qid + da_known_cpu,
	 * which we already programmed through the pp_pm RAM[12] CPU MAC
	 * slots in zx_eth_register_cpu_mac_slots().
	 *
	 * An earlier revision added an FDB entry pointing at port 5 (PON)
	 * for the host MAC, which silently routed CPU egress out the
	 * fiber. For broadcasts we rely on the switch's flood; for unicast
	 * we rely on the da_known_cpu lookup.
	 */

	/* [phase6/ft] PM external tables — must be after PON/TM init (the base
	 * registers read garbage while the PON-PP block clocks are gated). */
	zx_ft_pm_ext_init(eth);

	/* [wedge fix #2 2026-07-31] Post-pm_ext BMU pool sanity print. The pool
	 * must have been produced at zx_tm_bmu_enable time (virgin-block 0->1
	 * enable — see the BMU-range skip in zx_stock_apply_block) and must
	 * still be intact here (zx_ft_pm_ext_init no longer wipes the BPPE
	 * head). Stock-healthy idle: bppe_cnt ~8112, bppi_cnt ~79. A 0 here
	 * means the fabric is running pool-less and WILL wedge under sustained
	 * HW-forwarding. */
	dev_info(eth->dev,
		 "[wedge fix #2] BMU pool state post-pm_ext: bppe_cnt=%u bppi_cnt=%u (stock-healthy ~8112/~79)\n",
		 tm_read(eth, 0x8080), tm_read(eth, 0x8088));

	/* [Phase C R1 fix, 2026-07-27] Start the IDM RX ring consumer NOW (stock
	 * idm_net_init unmasks at init) — at the END of probe, after all IDM/TM
	 * init that could re-mask (the init-time IDM_IRQ_ALL_MASKED). The consumer
	 * (zx_idm_poll NAPI + IDM IRQ) must run even when no idm0/idm1 netdev is
	 * administratively UP: WiFi HW-offload egress lands hw-forwarded frames on
	 * the IDM RX ring with no netdev ever upped. Without this, ftwifi=1 traffic
	 * accumulates in the ring (RX_PENDING climbs) while idm_rx_count stays 0
	 * (the R1 black hole); proven live — bringing idm links up drained the ring
	 * 0->93, all ssid=4 (essid 0x1c). NAPI ownership is HERE (+ zx_eth_remove),
	 * not in open/stop. findings/wifi_stage3_phaseC_R1_fix_2026-07-25.md
	 */
	napi_enable(&eth->napi);
	npp_and(eth, IDM_REG_IRQ_MASK, ~IDM_IRQ_NAPI_MASK);
	eth->started = true;

	dev_info(dev, "ZX279128S ethernet ready (IRQ=%d, base=%pR, CPU_PORT=%d)\n",
		 eth->irq_idm, platform_get_resource(pdev, IORESOURCE_MEM, 0),
		 ZX_CPU_PORT);

	zx_debugfs_init(eth);

	/* [WiFi productionization 2026-08-01] Auto-bind wlan interfaces:
	 * register a netdevice notifier so wlanX is automatically bound to
	 * the next available idm/ssid slot when hostapd creates the vif.
	 * The debugfs wifi_bind knob still works for manual overrides.
	 */
	eth->wlan_nb.notifier_call = zx_wlan_notifier;
	register_netdevice_notifier(&eth->wlan_nb);

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

/**
 * zx_eth_remove() — Tear down the ZX279128S Ethernet driver
 * @pdev: platform device
 *
 * Reverse of probe: stops DMA engines, frees IRQs, disables NAPI,
 * unregisters netdevs, unmaps MMIO, and frees the carved DDR region.
 *
 * Return: 0.
 */
static int zx_eth_remove(struct platform_device *pdev)
{
	struct zx_eth *eth = platform_get_drvdata(pdev);
	int i;

	unregister_netdevice_notifier(&eth->wlan_nb);

	/* 0. Stop the binder from calling into us once we tear down. */
	zx_dsa_register_pm_ops(NULL);
	zx_pm_ops_eth = NULL;

	/* 1. Mask ALL IDM IRQs at HW (don't rely on devm_free_irq alone) */
	npp_write(eth, IDM_REG_IRQ_MASK, IDM_IRQ_ALL_MASKED);
	/* 2. Disable RX path in IDM control */
	npp_write(eth, IDM_REG_RX_ENABLE, 0);

	/* 3. Free IRQ before touching NAPI (handler won't schedule new work) */
	devm_free_irq(eth->dev, eth->irq_idm, eth);

	/* 4. If NAPI was ever enabled, disable it cleanly. Safe even if
	 * never enabled — napi_disable handles NAPI_STATE_DISABLE check.
	 */
	if (eth->started) {
		napi_disable(&eth->napi);
		eth->started = false;
	}
	netif_napi_del(&eth->napi);

	/* 5. Unregister netdevs (this calls ndo_stop on each UP iface — our
	 *    zx_eth_stop already handles IRQ mask, but masked again above).
	 */
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
	 *    we free its memory or the bus will hang.
	 */
	if (eth->sw_dev) {
		/* a) Mask all TM IRQs (1=masked semantics) so handler can't re-schedule */
		tm_write(eth, TM_REG_IRQ_MASK, 0xFFFFFFFF);
		/* b) Disable BMU — stops HW from allocating new BPs */
		tm_write(eth, TM_REG_BMU_INIT, 0);
		/* c) Clear DMA control bits (stop TX/RX engines) */
		tm_write(eth, TM_REG_DMA_CTRL, 0);
		/* d) Tiny delay to let in-flight transactions complete */
		usleep_range(10000, 11000);
		/* e) Now safe to free IRQ + NAPI + netdev */
		devm_free_irq(eth->dev, eth->irq_tm, eth);
		/* [txflowctrl] stop the 1-jiffy TX reclaim timer before the
		 * netdev goes away (the reclaim wakes its queue). */
		if (zx_sw_tx_reclaim_timer_ready) {
			zx_tm_tx_reclaim_eth = NULL;
			del_timer_sync(&zx_sw_tx_reclaim_timer);
		}
		unregister_netdev(eth->sw_dev);
		netif_napi_del(&eth->tm_napi);
		free_netdev(eth->sw_dev);
		eth->sw_dev = NULL;
	}
	zx_tm_free_pools(eth);

	zx_debugfs_exit();

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
