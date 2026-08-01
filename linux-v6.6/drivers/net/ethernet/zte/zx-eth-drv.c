// SPDX-License-Identifier: GPL-2.0-only
/* Included from zx-eth-main.c — single translation unit. */

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

/* ===================================================================
 * Per-function C ports of stock chip_tm_init's call chain.
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
 * ===================================================================
 */

/* Write one FPGA register, descriptor-table style.
 * Mirrors stock `tmOnuRegWrite(reg_id, val, sub_idx, table)`:
 *   addr_off  = table[reg_id].base_off + table[reg_id].stride * sub_idx
 *   writel(val, fpga_base + addr_off * 4)
 * No mask/shift handling — stock tmOnuRegWrite does a read-mask-or-write
 * cycle using table[].mask which we haven't extracted. For now we assume
 * the descriptor entries we touch want whole-register writes.
 */
/* Wrapper around the inline helper in zx-fpga-reg-tables.h that adds
 * the struct zx_eth's fpga_base lookup + diagnostics.
 *
 * Error-code triage (zx_fpga_table_write returns negatives):
 *   -1  reg_id is past the end of our captured descriptor table. Happens
 *       when callers (notably the pro_action proto loop) try ids stock
 *       knows about but we never extracted. Expected — log at dev_dbg.
 *   -2  table[reg_id].reg_id mismatch — sparse-table corruption. Real
 *       bug; keep the dev_warn_ratelimited.
 *   -3  sub_idx > max_sub_idx. Happens when callers iterate ports over
 *       a SoC-wide register (max_sub_idx == 0). Expected — log at
 *       dev_dbg.
 *   -4  descriptor marked not-writable. Real bug; keep the warn.
 */
static int zx_table_write(struct zx_eth *e,
			  const struct zx_fpga_reg *table, size_t n,
			  u16 reg_id, u32 val, u32 sub_idx)
{
	int rc = zx_fpga_table_write(e->fpga_base, table, n, reg_id, val, sub_idx);

	if (rc == -1 || rc == -3)
		dev_dbg(e->dev, "fpga_table_write(%u, val=%#x, sub=%u): %d (expected)\n",
			reg_id, val, sub_idx, rc);
	else if (rc < 0)
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
	/* Stock tm_port_isolate_set remaps the logical port to its physical
	 * sbragRegTable index before writing (decomp_all_tm.c:36297 switch):
	 * 0->1 1->2 2->3 3->4 4->5 5->0 6->6 7->7. Omitting this remap was the
	 * iter34 TX-hairpin root cause: the CPU port (logical 5) wrote index 5,
	 * leaving PP[0x83d4]=0xfe (blocks port 0) instead of 0xdf (blocks self),
	 * so the CPU port never blocked its own egress and CPU-TX looped back.
	 * See tx_hairpin_persists_after_8340_fix_re.md.
	 */
	static const u8 port_remap[8] = { 1, 2, 3, 4, 5, 0, 6, 7 };
	u32 inv = ~mask;
	u32 hw  = ((inv >> 5) & 1u)
		| ((inv << 1) & 0x3eu)
		| (inv       & 0xc0u);
	return zx_table_write(e, zx_sbragregtable,
			      ZX_SBRAGREGTABLE_COUNT, 57, hw, port_remap[port & 7]);
}

/* Stock spa_set_enty_pktdeal_cfg(port, proto, action) →
 *   tmOnuRegWrite(reg_id = 67 + proto, val = action, sub_idx = port, spaRegTable)
 * Per disasm of spa_set_enty_pktdeal_cfg @ 0x2b1f4 in tm.ko.
 * spaRegTable entries 67..137 are packed 2-bit fields (mask 0x3) at
 * shift = (proto & 7) * 2 within the same register, stride 5 per port.
 */
static int zx_spa_set_enty_pktdeal_cfg(struct zx_eth *e, u8 port, u8 proto, u8 action)
{
	if (proto > 0x46)               /* table has 71 protos */
		return -EINVAL;
	return zx_table_write(e, zx_sparegtable, ZX_SPAREGTABLE_COUNT,
			      67 + proto, action, port);
}

/* Replay the def_ptl_pkt_action table for every port × every protocol.
 * This is stock chip_tm_init's pp_set_pro_action loop, decomposed:
 * stock calls pp_set_pro_action(pp_inst, proto, action) which internally
 * loops over ports → spa_set_enty_pktdeal_cfg(port, proto, action). We
 * write the same configuration directly, port-major. The table
 * zx_pp_pro_actions[] was extracted from kotrace trace; see
 * tasks/00.01.eth-driver/findings/chip_tm_init_args.md.
 */
/* [Iter AQ, 2026-06-04 — THE TCP-ACK-HW-FORWARD FIX] The SPA per-protocol pktdeal
 * decides which protocol-type SLOTS forward (deal=0) vs trap (deal=1). The
 * zx_pp_pro_actions[] replay above writes the kotrace proto value DIRECTLY as the
 * slot index — but stock's zte_api_pp_set_pro_action first REMAPS proto->ptype-slot
 * (a 71-case switch), so our un-remapped writes land on the WRONG slots and TCP
 * control frames (pure-ACK/SYN/FIN) end up trapping to the CPU (~62k/flow).
 * Stock's actual forward-slot set (read live from stock's pktdeal RAM 0x921d4300)
 * is the list below. VERIFIED ON HW: forcing exactly these slots to forward makes
 * TCP ACKs HW-forward (tm_rx delta 2 over a 20s/354 Mbit-s flow, 0 retransmits)
 * while broadcast/ARP still traps to the CPU (ping 4/4) — i.e. CPU offloaded for
 * TCP without breaking the bridge. MUST go through spa_set_enty_pktdeal_cfg (the
 * indirect write); a direct poke of 0x921d4300 does NOT update the live classifier.
 * See tasks/00.01.eth-driver/findings/stock_ack_forward_lever_re.md.
 */
static const u8 zx_pktdeal_ack_fwd_slots[] = {
	0x0c, 0x0d, 0x17, 0x1f, 0x22, 0x24, 0x25, 0x26,
	0x2c, 0x2d, 0x2f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45,
};

static void zx_chip_tm_init_pro_action(struct zx_eth *e)
{
	int port, i, ok = 0, fail = 0;

	for (port = 0; port < 8; port++) {
		for (i = 0; i < ZX_PP_PRO_ACTION_COUNT; i++) {
			/* Most entries are symmetric PP0 == PP1; we use PP0 action.
			 * proto 0x14 differs (PP0=1, PP1=0) — pick the trap variant.
			 * forward-all override: deal=0 so TCP HW-forwards like UDP.
			 */
			u8 action = zx_proto_fwd_all ? 0 : zx_pp_pro_actions[i].action_pp0;

			if (zx_spa_set_enty_pktdeal_cfg(e, port, zx_pp_pro_actions[i].proto, action) == 0)
				ok++;
			else
				fail++;
		}
		/* THE FIX: force stock's remapped forward-slot set to deal=0 so TCP
		 * control frames HW-forward (CPU offloaded) while broadcast keeps
		 * trapping. Skipped under the (debug) forward-all override. */
		if (!zx_proto_fwd_all) {
			for (i = 0; i < (int)ARRAY_SIZE(zx_pktdeal_ack_fwd_slots); i++)
				zx_spa_set_enty_pktdeal_cfg(e, port,
					zx_pktdeal_ack_fwd_slots[i], 0);
		}
	}
	dev_dbg(e->dev, "pro_action: %d ok, %d fail [%s]\n",
		 ok, fail,
		 zx_proto_fwd_all ? "FORWARD-ALL (debug)" :
		 "stock trap table + ACK-fwd slots (TCP ACKs HW-fwd, bcast traps)");
}

/* chip_tm_init's per-port isolation loop. mask = ports each port may NOT
 * forward to. Ports 0..5 isolate themselves (mask 1<<p); the two internal
 * ports 6,7 isolate nothing (mask 0). Combined with the logical->physical
 * remap in zx_tm_port_isolate_set this lands the stock-live table
 * {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xff,0xff} at PP[0x83c0..0x83dc] — idx5
 * (CPU port) = 0xdf = blocks self, which stops the CPU-TX hairpin.
 * Ports 6,7 masks were 0xff40/0xff80 (extrapolated) before; stock-live has
 * 0xff there (mask 0). See tx_hairpin_persists_after_8340_fix_re.md.
 */
static void zx_chip_tm_init_isolate(struct zx_eth *e)
{
	static const u8 self_mask[8] = { 1u << 0, 1u << 1, 1u << 2, 1u << 3,
					 1u << 4, 1u << 5, 0, 0 };
	void __iomem *pp = e->base + PP_OFF;
	int p;

	for (p = 0; p < 8; p++) {
		int rc = zx_tm_port_isolate_set(e, p, 0xffffff00u | self_mask[p]);

		if (rc)
			dev_warn(e->dev, "isolate port %d: %d\n", p, rc);
	}
	dev_dbg(e->dev, "isolate PP[0x83c0..dc] = %#x %#x %#x %#x %#x %#x %#x %#x\n",
		 readl(pp + PP_BRG_ISOLATE(0)) & 0xff, readl(pp + PP_BRG_ISOLATE(1)) & 0xff,
		 readl(pp + PP_BRG_ISOLATE(2)) & 0xff, readl(pp + PP_BRG_ISOLATE(3)) & 0xff,
		 readl(pp + PP_BRG_ISOLATE(4)) & 0xff, readl(pp + PP_BRG_ISOLATE(5)) & 0xff,
		 readl(pp + PP_BRG_ISOLATE(6)) & 0xff, readl(pp + PP_BRG_ISOLATE(7)) & 0xff);
}

/* WiFi (fabric inport 6/7) trap re-steer, fix "A.2".
 *
 * Stock steers ARP (ptype 0x11) plus the 0x1d/0x1f/0x20 protocol classes to
 * CPU DN queue 5 ({ptype,qid0,qid1} = {..,5,5} in zx_def_ptl_pkt_map). On
 * mainline, DN queue 5 has never been exercised by wire traffic and
 * pops-to-nowhere the first time it is hit by a fabric-port-6/7 (WiFi) trap —
 * the "dead q5" pathology documented in
 * findings/wifi_stage3_qmg_queue5_consumer_re_2026-07-07.md §4. Queue 4 is
 * live-proven delivered since boot (that doc's §4 delta table). We therefore
 * re-steer the affected q5 rows to q4 across ALL ram7 banks so that whichever
 * bank a port-6/7 ingress frame actually consults — base/dir-1 (row 0x011),
 * or per-port bank 6 (0x311) / 7 (0x391); unresolved device-free, see that
 * doc §2.4 + §7 open-Q — lands in a delivered queue. This subsumes the
 * bank-index-space ambiguity that made the earlier single-bank `0x391`
 * re-steer miss (doc §2.4). Wire-port banks (0..4) are overridden at runtime
 * by the ram2 catch-all cpu_qid (→q7, doc §2.3), so this is a no-op for the
 * existing LAN/WAN trap delivery and only changes the port-6/7 outcome.
 * ON-DEVICE-UNTESTED. Set ZX_WIFI_TRAP_LIVE_QID to 0xff to disable the
 * re-steer (leaving the stock-parity dual-bank replay of A.1 intact).
 */
#define ZX_WIFI_TRAP_DEAD_QID	5	/* pop-to-nowhere DN queue on mainline */
#define ZX_WIFI_TRAP_LIVE_QID	4	/* live-delivered replacement (doc §4) */

/* chip_tm_init's trap-queue setup — replays def_ptl_pkt_map into CLA ram7.
 *
 * Stock chip_tm_init (decomp_all_switch.c:2505-2518) walks the
 * {ptype,qid0,qid1} table calling zte_api_pp_set_trap_queue for BOTH
 * directions (decomp_all_tm.c:57882-57916):
 *   dir 0 → loops port 0..7 SKIPPING 5, writes qid0 into the 7 per-inport
 *           banks (offsets 0x080/0x100/0x180/0x200/0x280/0x300/0x380);
 *   dir 1 → writes port 5 ONLY, i.e. qid1 into the base bank 0x000-0x7f
 *           (row = ptype & 0x7f; tm_protocol_pkt_limit_map_set port-5 case,
 *           decomp_all_tm.c:40362-40400 / :3957 cla_set_cpu_queue_id;
 *           bank offsets cross-confirmed by DATASHEET.md:890,894).
 * Mainline previously replayed dir 0 ONLY (qid0 into the 7 per-inport banks)
 * and left the base bank at the blanket qid=7 from zx_cla_apply_replay — but
 * the base bank is a live-proven trap-steering bank
 * (fix_churn_red_dnbank_2026-07-04.md). This adds the missing dir-1 base-bank
 * replay (fix "A.1", stock parity) and the WiFi q5->q4 re-steer (fix "A.2").
 * Source: findings/wifi_stage3_qmg_queue5_consumer_re_2026-07-07.md §2, §5.
 * Since every ptype in zx_def_ptl_pkt_map is <= 0x7f, "ptype & 0x7f",
 * "ptype & 0xff" and "ptype | 0" all reduce to ptype, so the single
 * "ptype | zx_pkt_port_addr_offset[port]" row computation is exact for every
 * bank (base bank offset = 0).
 * BUILD-VERIFIED, ON-DEVICE-UNTESTED.
 */
static void zx_chip_tm_init_trap_queues(struct zx_eth *e)
{
	u32 ok = 0, fail = 0, resteer = 0;
	int port, i;

	for (i = 0; i < ZX_DEF_PTL_PKT_MAP_COUNT; i++) {
		u8 ptype = zx_def_ptl_pkt_map[i].ptype;
		u8 qid0  = zx_def_ptl_pkt_map[i].qid0;
		u8 qid1  = zx_def_ptl_pkt_map[i].qid1;

		for (port = 0; port < 8; port++) {
			u32 addr = ptype | zx_pkt_port_addr_offset[port];
			/* dir-1 base bank (port-5 slot, offset 0) takes qid1;
			 * the 7 per-inport banks (dir-0) take qid0. */
			u8 qid = (port == 5) ? qid1 : qid0;

			/* Fix A.2: re-steer the dead-q5 WiFi trap classes to
			 * the live q4 in EVERY bank (base + per-inport 6/7). */
			if (ZX_WIFI_TRAP_LIVE_QID != 0xff &&
			    qid == ZX_WIFI_TRAP_DEAD_QID) {
				qid = ZX_WIFI_TRAP_LIVE_QID;
				resteer++;
			}

			if (zx_cla_set_cpu_queue_id(e, addr, qid) == 0)
				ok++;
			else
				fail++;
		}
	}
	dev_dbg(e->dev,
		 "trap_queue replay: %u ok, %u fail (%u entries x 8 banks incl. base/dir-1; %u q%u->q%u WiFi re-steers)\n",
		 ok, fail, ZX_DEF_PTL_PKT_MAP_COUNT, resteer,
		 ZX_WIFI_TRAP_DEAD_QID, ZX_WIFI_TRAP_LIVE_QID);
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
	dev_dbg(e->dev, "CPU MAC slot[%u] = %pM (spa+pp_pm registered)\n",
		 slot, mac);
}

/* Pre-DMA setup (tm_pon_tm_init opening lines).
 *
 * The TM register block has 4 identical instances at offsets 0x000,
 * 0x400, 0x800, 0xC00 (each 0x400 bytes wide), one per GePHY port.
 * Stock programs all 4 instances with identical values; TX wire-emit
 * may use any of instance 0..3 depending on egress port.
 *
 * The full per-mem dump shows 16-instance state but stock's
 * pon_tm_int_init only writes instance 0..3 explicitly; the rest is HW
 * mirroring and writing to instances 4..15 hangs the FPGA IRQ path.
 */
static void zx_tm_pre_init(struct zx_eth *e)
{
	int inst;

	for (inst = 0; inst < TM_NUM_INSTANCES; inst++) {
		u32 base = inst * TM_INSTANCE_STRIDE;

		tm_write(e, base + 0x000, 0x00000140);	/* master config */
		tm_write(e, base + 0x004, 0x00000010);
		tm_write(e, base + 0x104, ~(u32)TM_IRQ_ARM_BITS);  /* mask all but our IRQ bits */
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
 * +0x4020/+0x4024/+0x4028.
 */
static int zx_red_set_queue_cfg(struct zx_eth *e, u16 q_idx, u32 type,
				u32 w0, u32 w1, u32 w2, u32 w3)
{
	int retries;

	for (retries = 0; retries < 20; retries++)
		if (tm_read(e, TM_RED_QCFG_READY) & 1)
			break;
	if (retries == 20)
		return -EBUSY;
	tm_write(e, TM_RED_QCFG_CMD, (u32)q_idx | (type << 22));
	tm_write(e, TM_RED_QCFG_DATA3, w3);
	tm_write(e, TM_RED_QCFG_DATA2, w2);
	tm_write(e, TM_RED_QCFG_DATA1, w1);
	tm_write(e, TM_RED_QCFG_DATA0, w0);
	return 0;
}

/* pon_tm_red_init equivalent — 4 loops configuring 1168 RED-queue slots.
 * Stock calls this from tm_pon_tm_init BEFORE pon_tm_dma_init/bmu_init.
 * Hypothesis: without these queue configs HW receives packets via BMU but
 * never fires the RX/TX-done bits on TM[+0x100] bits 0/1 → no GIC line 68
 * IRQ → kernel never sees RX.
 */
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

	/* [red-arm 2026-07-04] Clear RED_CFG bit6 (phys 0x92344004, tm off
	 * 0x4004): DISABLE the RED cpuDn out-buffer occupancy accounting.
	 *
	 * ROOT CAUSE OF THE CHURN/WAN-RX WEDGE (validated live on the H3600,
	 * findings/fix_churn_red_dnbank_2026-07-04.md): with bit6=1 (the 0xDE
	 * reset value, == stock live) every WAN-ingress hw_trap charges the RED
	 * out-buffer used_space of its CPU-DN queue (RED out-queue indices
	 * 8-15, stock's red_info_store "cpuDn" bank; readable via RED indirect
	 * ram1, CMD 0x4014 = q|0x8400000) 1:1 -- and on mainline NOTHING ever
	 * returns it: DN traps deliver to the CPU via ring0, whose dequeue/
	 * release credits only the cpuUp bank. used_space leaks monotonically
	 * to the 0x400=1024 depth, RED then demotes all further DN traps to
	 * sw_fwd (which never reaches the CPU on mainline) = the reboot-only
	 * "qmg_dn_trap pinned at 1024" wedge (churn storms and even idle WAN
	 * chatter get there). No SW op refunds a charged queue -- release port
	 * 0x4064/0x4068 (both bank polarities x both sop values, stale AND
	 * actively-charging queues), ram0/ram1 indirect writes (both write
	 * protocols), RED cfg_enable toggle, OPC ram-init pulse: ALL refuted
	 * live with the ram1 occupancy oracle watching.
	 *
	 * bit6 is a LIVE level control, proven by runtime bisection: 0xDE
	 * leaks 1:1, 0x9E (bit6 cleared) stops the charge instantly, restoring
	 * 0xDE resumes the leak, re-clearing freezes it again. bit7 alone
	 * (0x5E) does NOT stop it. With bit6=0 a 60-flow churn storm drove
	 * qmg_dn_trap to 2098 -- past the old 1024 wall -- with zero occupancy
	 * accumulation, lan4 datapath healthy, downloads at line rate.
	 *
	 * Stock DIVERGENCE, deliberate: stock runs bit6=1 but never exercises
	 * the DN hw_trap path at scale (its to-CPU traffic rides the sw_fwd
	 * verdict; live stock reads qmg_dn_trap == 0), so the charge-only
	 * accounting never hurts it. Mainline's trap-all DSA-conduit
	 * architecture charges it on EVERY WAN-ingress frame, so the
	 * accounting must be off until (if ever) delivery is rearchitected
	 * onto the sw_fwd path. CPU overload protection still exists upstream/
	 * downstream of it: ADM per-queue PPS policing, the RX ring pending
	 * counters + NAPI budget, and the BMU pool. */
	{
		u32 cfg = tm_read(e, TM_RED_CFG);

		tm_write(e, TM_RED_CFG, cfg & ~TM_RED_CFG_CPUDN_CHARGE);
		dev_dbg(e->dev, "TM RED init: %d failed of 1168 queue configs; RED_CFG 0x%02x -> 0x%02x (bit6 cpuDn charge-accounting OFF)\n",
			 fail, cfg, cfg & ~TM_RED_CFG_CPUDN_CHARGE);
	}
}

/* [Iter Y 2026-06-04] zx_red_block_init — init the REAL RED congestion block at phys 0x92344000
 * (e->base + 0x184000).
 *
 * ⚠ [red-arm 2026-07-04] LATENT BASE BUG, now understood: every access below goes through
 * tm_write()/tm_read() (= e->base + TM_OFF 0x180000 + off) with NPP-relative offsets
 * (RED_OFF 0x184000), so it all lands at 0x924Cxxxx DEAD SPACE — none of these writes have
 * ever reached the RED block. Benign in the end: the RED globals reset-default to stock's
 * live values (RED_CFG=0xDE, share maxes 0x3ff/0x3fff), and the premise below ("mainline
 * never writes 0x92344xxx") was wrong anyway — zx_tm_red_init()'s TM[0x4014] IS the RED
 * indirect port at phys 0x92344014 (tm-relative), and its ram0 q0-15=0x400 matches stock
 * live. The churn/WAN-RX 1024 wedge root cause was NOT this bug (stock also runs
 * RED_CFG=0xDE) but the bit6 cpuDn charge-accounting — see the [red-arm] block in
 * zx_tm_red_init. Left otherwise untouched: making these writes land would apply
 * UNVALIDATED config values (e.g. q0-15 guart 0x3ff vs the live-verified 0x400) — clean up
 * in a dedicated pass.
 *
 * Original rationale (kept for history): UNTESTED-PENDING-HW (committed during a host-USB
 * block so it's ready to build+test the moment 2 stable NICs return). RATIONALE: grep proved
 * mainline NEVER writes the
 * 0x92344xxx RED block — zx_tm_red_init() above touches TM[0x4014]=0x921c4014 (a DIFFERENT block).
 * So the RED block's per-queue OUT-BUFFER thresholds + global share pools run at reset/bootloader
 * defaults → suspected cause of the CPU/trap-queue RED drops + the ~1024 latch under load.
 * Replicates stock pon_tm_red_init (decomp_all_tm.c:42509+): global enables + per-queue out-buffer.
 * RED indirect (same pattern as the CLA hash): CMD 0x184014 = addr|ram<<22|rw<<27; DONE 0x184018
 * bit0; DATA0 0x18401c. Per-queue out-buffer entry = guart | (max_space << 11).
 */
#define RED_OFF		0x184000	/* phys 0x92344000 - e->base 0x921c0000 */
#define RED_CFG		(RED_OFF + 0x04)	/* [1:0]cfg_en [2]share_mode [3]trap_color [4]open_out */
#define RED_IND_CMD	(RED_OFF + 0x14)
#define RED_IND_DONE	(RED_OFF + 0x18)
#define RED_IND_DATA0	(RED_OFF + 0x1c)
#define RED_IN_SHARE_MAX	(RED_OFF + 0x40)
#define RED_UP_OUT_SHARE_MAX	(RED_OFF + 0x74)

static void zx_red_set_outbuf(struct zx_eth *e, u32 queid, u32 guart, u32 max_sp)
{
	int t = 20;

	while (t-- && !(tm_read(e, RED_IND_DONE) & 1))
		udelay(2);
	if (t < 0)
		return;
	/* stock red_set_out_buffer_queue_cfg: cmd(rw=0,ram=0,addr=queid) then data0 */
	tm_write(e, RED_IND_CMD, queid);
	tm_write(e, RED_IND_DATA0, (guart & 0x7ff) | ((max_sp & 0xffff) << 11));
}

static void zx_red_block_init(struct zx_eth *e)
{
	u32 q, cfg;

	/* Global enables (stock pon_tm_red_init head): cfg_enable[1:0]=2, share_mode[2],
	 * trap_color_en[3], open_out_en[4]; preserve any reset high bits via RMW. */
	cfg = tm_read(e, RED_CFG);
	cfg = (cfg & ~0x3u) | 0x2u;	/* cfg_enable = 2 (mode select) */
	cfg |= (1u << 2) | (1u << 3) | (1u << 4);	/* share_mode | trap_color_en | open_out_en */
	tm_write(e, RED_CFG, cfg);
	tm_write(e, RED_IN_SHARE_MAX, 0x3ff);		/* stock red_set_in_share_max(0x3ff) */
	tm_write(e, RED_UP_OUT_SHARE_MAX, 0x3fff);	/* stock red_set_up_out_share_max(0x3fff) */

	/* Per-queue OUT buffer (stock ranges, decomp 42523-42556): the CPU/trap queues (q16-335)
	 * get max_space 0x7ff — vs an uninitialized/small reset default that caps CPU delivery. */
	for (q = 0; q < 400; q++) {
		u32 guart = 0x40, max_sp;

		if (q < 0x10) {
			guart = 0x3ff;
			max_sp = 0;
		} else if (q < 0x150) {
			max_sp = 0x7ff;
		} else if (q < 0x178) {
			max_sp = (q & 7) ? 0x80 : 0x200;
		} else if (q < 0x188) {
			max_sp = 0xc00;
		} else {
			max_sp = 0x3ff;
		}
		zx_red_set_outbuf(e, q, guart, max_sp);
	}

	/* IN-buffer per-queue (stock red_set_in_buffer_queue_cfg, q<0x180, guart=0x20 max_sp=0x200).
	 * THE INGRESS RED buffer — mainline omitted it, so each queue's in-buffer max_space stayed at
	 * the reset default (≈0) and RED REJECTED frames at QMG-ingress. This is why the WAN DN→CPU
	 * path drops (lan4 rx=0, RED[0x1a044] climbs) and is the same ingress reject as the LAN
	 * redwedge. type=2 in the RED indirect cmd (q | 2<<22); data = guart | (max_sp << 13). */
	for (q = 0; q < 0x180; q++) {
		int t = 20;

		while (t-- && !(tm_read(e, RED_IND_DONE) & 1))
			udelay(2);
		if (t < 0)
			break;
		tm_write(e, RED_IND_CMD, q | (2u << 22));
		tm_write(e, RED_IND_DATA0, (0x20u & 0x1fff) | ((0x200u & 0x7ffff) << 13));
	}
	dev_dbg(e->dev, "RED block init (0x92344000): globals + 400 out-buffer + 0x180 in-buffer queues\n");
}

/* pon_pp_ctrl_init equivalent — 2 writes + 52ms delay.
 * Stock calls this BEFORE pon_pp_brg_init. The write to pp[0] = 2 may
 * be a trigger that starts PP processing (not just state).
 */
static void zx_pp_ctrl_init(struct zx_eth *e)
{
	void __iomem *pp = e->fpga_base + 0x380000;

	writel(0x01070104, pp + 0x28);
	writel(0x00000002, pp + 0x00);
	msleep(52);
	dev_dbg(e->dev, "PP ctrl init: pp[0x28]=0x01070104 pp[0]=2 + 52ms delay\n");
}

/* pon_pp_brg_init equivalent — initializes the PP bridge so CPU TX egresses
 * to UNI ports. Without this, mainline TX never reaches the wire (driver
 * counter increments but no packets seen on host tcpdump).
 * 13 fixed register writes to pp_base = fpga_base + 0x380000.
 */
/* CPU port = 5 per stock kotrace (sbrg_set_unknown_unicst_fwd called
 * 8 times with port 5 = enable=1, others = enable=0).
 */
#define ZX_CPU_PORT_BIT		BIT(5)
#define ZX_ALL_PORTS_BITMAP	0xffu

static void zx_pp_brg_init(struct zx_eth *e)
{
	void __iomem *pp = e->fpga_base + 0x380000;

	/* Log INHERITED state from U-Boot before we overwrite.
	 * Lets us see what U-Boot left behind so we can spot regs where we
	 * may be clobbering a known-good config. Diff against the writes
	 * below tells us which writes are no-ops vs. destructive.
	 */
	dev_dbg(e->dev, "PP_BRG inherited from U-Boot (pre-init):\n");
	dev_dbg(e->dev, "  PP[0x8004]=%08x  [0x8008]=%08x  [0x8050]=%08x\n",
		 readl(pp + 0x8004), readl(pp + 0x8008), readl(pp + 0x8050));
	dev_dbg(e->dev, "  PP[0x8188]=%08x (aging_cycle)\n", readl(pp + 0x8188));
	dev_dbg(e->dev, "  PP[0x81c0]=%08x (SMAC_LOOK_EN bitmap)\n", readl(pp + 0x81c0));
	dev_dbg(e->dev, "  PP[0x81c4]=%08x (LEARN_MODE per port)\n", readl(pp + 0x81c4));
	dev_dbg(e->dev, "  PP[0x82c0]=%08x (DA_LOOKUP_EN bitmap)\n", readl(pp + 0x82c0));
	dev_dbg(e->dev, "  PP[0x8300]=%08x  [0x8304]=%08x\n",
		 readl(pp + 0x8300), readl(pp + 0x8304));
	dev_dbg(e->dev, "  PP[0x8340]=%08x (PKTDEAL+FWD)\n", readl(pp + PP_BRG_PKTDEAL_FLOOD));
	dev_dbg(e->dev, "  PP[0x8344]=%08x  [0x8380]=%08x  [0x863c]=%08x\n",
		 readl(pp + 0x8344), readl(pp + 0x8380), readl(pp + 0x863c));

	/* PP[0x8004] = bridge control. Stock-live 0x040200ff: bit 17
	 * macaddr_age_en + bit 26 macaddr_exchange_md (sbrg_set_macaddr_age_en(1)
	 * + sbrg_set_macaddr_exchange_md(1) in tm_pon_pp_brg_initial,
	 * decomp_all_tm.c:43606). Without the aging FSM the HW IGNORES learned
	 * FDB entries on the egress DA-lookup, so a learned host MAC reads as
	 * unknown-unicast → floods CPU-only (PP[0x8340]) → CPU-TX hairpins back
	 * to CPU. Was 0x020000ff (bit 25 set, wrong). See fdb_learn_commit_re.md.
	 */
	writel(0x040200ff, pp + 0x8004);
	/* PP[0x8340] = PKTDEAL(0x5555) + unknown-unicast FWD bitmap[31:24].
	 * Stock LIVE = 0x015555ff (FWD only to internal port 0 = CPU). 0xff
	 * floods all 8 ports → every CPU TX with unknown DA hairpins back to
	 * the CPU as loopback (the iter34 wedge). See fdb_learning_enable_re.md
	 * Q6. NB: CPU is internal port 0 = bit 0x01 (port-5→0 remap), not 0x20.
	 */
	writel(0x015555ff, pp + PP_BRG_PKTDEAL_FLOOD);
	/* Broadcast / unknown-flood gates. Stock DISABLES forced flooding here:
	 * broadcast egress is governed only by VLAN-0 membership minus port
	 * isolation (which excludes the CPU source port → no hairpin). Stock-live
	 * (regs/stock_eth_2mib.txt): PP[0x8300/0x8304/0x8344]=0, PP[0x8380]=0x01
	 * (pt_tls = CPU port only, sbrg_set_pt_tls(0,1) in tm_pon_pp_brg_initial).
	 * Forcing these (0x1e/0x1f/0xffff) flooded the device's OWN broadcasts
	 * back to the CPU = the residual hairpin. See cpu_lan_egress_gate_re.md.
	 */
	writel(0x00000000, pp + 0x8344);	/* unknown-unicast flood portmask: off */
	writel(0x00000001, pp + 0x8380);	/* pt_tls: CPU port only (was 0x1f) */
	writel(0xaaaaaaaa, pp + 0x863c);

	/* SMAC_LOOK_EN — 1 bit per port. Phase 50 (PING BIDI WORKS) had all
	 * 8 ports enabled (0xff). A later commit (cf65924ff4) cleared bit 5
	 * to prevent CPU-port-hairpin FDB flap; that revealed itself as the
	 * regressor that breaks the host→CPU RX path: clearing bit 5 stops
	 * the switch from doing source-MAC lookup on frames arriving at the
	 * CPU port (the path the IRQ-driven NAPI feeds from). Restore to
	 * 0xff to match stock + Phase 50 baseline.
	 */
	writel(ZX_ALL_PORTS_BITMAP, pp + 0x81c0);

	writel(0x00005555, pp + 0x81c4);
	writel(0x00000001, pp + 0x8184);	/* tm_mac_ramaddr_sel_set(1): FDB RAM addr/size select (stock) */
	writel(0x00211b00, pp + 0x8188);	/* aging-cycle blob, stock-live (was 0x0013f434 — clobbered zx_pp_init) */
	writel(0x000000ff, pp + 0x82c0);
	writel(0x00000000, pp + 0x8300);	/* sbrg_set_brdcst_fld_en: OFF (stock=0; was 0xffff = the broadcast hairpin gate) */
	writel(0x00000000, pp + 0x8304);	/* broadcast flood portmask: off (stock=0) */
	writel(0xfffffffa, pp + 0x8050);
	/* [Phase B close-out, 2026-07-25] VLAN-check enables: MUST be 0, not
	 * the 0x0000ff00 this stock-replay line used to write. This function
	 * runs AFTER zx_pp_init (probe order: zx_pp_init → zx_eth_apply_
	 * stock_init → zx_pp_brg_init), so the old value here silently
	 * CLOBBERED commit b5a4e5d8b's vl_chk-off write in zx_pp_init — the
	 * same last-writer-wins replay trap as the RED_CFG bit6 story.
	 * Found on the first #527 boot: 0x92388008 read back 0x0000ff00
	 * despite the fix being compiled in. outport_vl_chk_en[15:8] with
	 * mainline's effectively-empty VLAN tables = every bridge-FORWARD
	 * verdict drop_PP'd (killed all WiFi/ring FORWARD-class unicast).
	 * See findings/wifi_stage3_phaseB_e2e_realclient_2026-07-07.md.
	 */
	writel(0x00010000, pp + 0x8008);	/* vl_chk all OFF + cpu_chk_en (bit16) */
	dev_dbg(e->dev, "PP_BRG post-init: SMAC_LOOK_EN=%02x (CPU port 5 disabled)\n",
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
	 * approximate "set vlan 0 and 1 entries to 0x1FFFF" via brg_ram_set.
	 */
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

	dev_dbg(e->dev, "PP bridge init: 13 regs + VLAN0/1 + port6/7 isolate done\n");
}

/* Post-BMU setup (tm_pon_tm_init between bmu_init and pon_tm_net_init).
 *
 * Stock dump showed per-instance desc base registers at
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
 * high 16) — set per-instance in all 4.
 */
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
	 * After traffic, if any word changes from 0xDEAD0000+n → HW wrote there.
	 */
	{
		u32 *d = (u32 *)e->rxdesc_cpu;
		int i;

		for (i = 0; i < 1024; i++)
			d[i] = 0xDEAD0000u | (u32)i;
		dma_wmb();
		dev_dbg(e->dev, "rxdesc canaries planted at %pad (TM[0xF0]=%#x, first w[0]=%#x)\n",
			 &e->rxdesc_dma, tm_read(e, 0xF0), d[0]);
	}
	tm_write(e, 0xC008, 0);
}

/* SCH (downstream scheduler) indirect-RAM access port — TM[0x14014/18/1c].
 *
 * The SCH block's per-queue token-bucket shaper tables (fill-rate, bucket-cap)
 * live in indirect RAM, written through a command/data/done port — NOT by
 * direct register writes. The stock tm.ko populates them in tm_pon_tm_sch_initial
 * (decomp_all_tm.c:47025). Mainline previously wrote garbage straight to the
 * indirect port, leaving every per-queue bucket-cap at 0 → no queue ever has
 * credit → DSCH drops every CPU→LAN egress frame (drop_DSCH++). See
 * findings/dsch_drop_cpu_egress_re.md and pipeline_trace_dies_at_dsch.md.
 *
 * Register map (zx_schregtable[], zx-fpga-reg-tables.h:152-154; base word
 * 0x000d5000 == TM[0x14000]):
 *   reg_id 13 -> TM[0x14014] = indirect RW command  (mask 0x8fcfffff)
 *   reg_id 14 -> TM[0x14018] = ind-acc done  (RO, bit0 = idle/ready)
 *   reg_id 15 -> TM[0x1401c] = ind-acc data
 *
 * Command encoding (sch_set_indirect_rw_cmd, decomp_all_tm.c:29690):
 *   cmd = RAMAddr | (RAMID<<22) | (indRwEn<<27) | (incrEn<<31)
 *   indRwEn: 0=write, 1=read.  RAMID<0x10, RAMAddr<0x200.
 */
#define ZX_SCH_REG_CMD		0x14014
#define ZX_SCH_REG_DONE		0x14018
#define ZX_SCH_REG_DATA		0x1401c

/* Poll the ind-acc DONE bit (mirrors sch_get_ind_acc_done @29725 + the ~0x14-try
 * poll loops in the shaper setters, e.g. sch_set_up_pq_sharp_fill_rate @30465). */
static void zx_sch_wait_done(struct zx_eth *e)
{
	int t = 0x14;		/* stock loops up to 0x14 (=20) tries */

	while (t-- && !(tm_read(e, ZX_SCH_REG_DONE) & 1))
		udelay(2);
	if (t < 0)
		dev_warn_ratelimited(e->dev, "SCH indirect access timeout\n");
}

/* One indirect WRITE: poll-done -> CMD(incrEn=0, indRwEn=0=write, ramid, addr)
 * -> DATA. CMD-before-DATA, no trailing poll — exactly as the stock single-value
 * setters do (sch_set_up_pq_sharp_fill_rate @30481-30483, ..._bucket_cap
 * @30647-30649, ..._tcont_sharp_fill_rate @30807-30809). */
static void zx_sch_indirect_write(struct zx_eth *e, u32 ramid, u32 addr, u32 val)
{
	zx_sch_wait_done(e);
	tm_write(e, ZX_SCH_REG_CMD, (addr & 0x1ff) | ((ramid & 0xf) << 22));
	tm_write(e, ZX_SCH_REG_DATA, val);
}

/* zx_sch_init — replay stock tm_pon_tm_sch_initial's per-queue shaper RAM init
 * (decomp_all_tm.c:47025). The stock loop runs 0x20 units (tcont) x 8 queues,
 * each unit calling:
 *   tm_tcont_sharp_set(unit, 1600000)        (@45564)
 *   tm_tcont_que_sharp_set(unit, que, 1600000) for que 0..7  (@45535)
 *
 * tm_tcont_que_sharp_set -> sch_set_up_pq_sharp_fill_rate(unit,que,1600000)
 *                             = RAMID 2, addr = que + unit*8, val = 1600000
 *                        -> sch_set_up_pq_sharp_bucket_cap(unit,que,getFillcap)
 *                             = RAMID 3, addr = que + unit*8, val = getFillcap()
 * tm_tcont_sharp_set     -> sch_set_up_tcont_sharp_fill_rate(unit,1600000)
 *                             = RAMID 5, addr = unit, val = 1600000   (@30808)
 *                        -> sch_set_up_tcont_sharp_bucket_cap(unit,getFillcap)
 *                             = RAMID 6, addr = unit, val = getFillcap() (@30955)
 *
 * fill-rate value: 1600000 = 0x186A00 (< 0x200000 limit, fits cmd data).
 * bucket-cap value: tm_getFillcap(1600000). The getFillcap table (tm.ko .rodata,
 *   verified via objdump) tops out at threshold 20480; 1600000 exceeds all 10
 *   thresholds so it falls to tm_getFillcap_part_44 (@42422): (1600000>>8)=6250,
 *   which is < 199999 so it clamps to 200000 = 0x30D40 (< 0x400000 limit). */
#define ZX_SCH_FILL_RATE	1600000		/* 0x186A00 */
#define ZX_SCH_BUCKET_CAP	200000		/* tm_getFillcap(1600000) = 0x30D40 */
#define ZX_SCH_UNITS		0x20		/* tcont count, stock loop @47057 */
#define ZX_SCH_QUEUES		8		/* queues/tcont, stock loop @47055 */
#define ZX_SCH_RAMID_PQ_FILL	2		/* per-queue fill-rate  @30482 */
#define ZX_SCH_RAMID_PQ_CAP	3		/* per-queue bucket-cap @30648 */
#define ZX_SCH_RAMID_TCONT_FILL	5		/* tcont fill-rate      @30808 */
#define ZX_SCH_RAMID_TCONT_CAP	6		/* tcont bucket-cap     @30955 */

static void zx_sch_init(struct zx_eth *e)
{
	u32 unit, que;

	for (unit = 0; unit < ZX_SCH_UNITS; unit++) {
		/* tcont-level shaper (RAMID 5/6, addr = unit) */
		zx_sch_indirect_write(e, ZX_SCH_RAMID_TCONT_FILL, unit,
				      ZX_SCH_FILL_RATE);
		zx_sch_indirect_write(e, ZX_SCH_RAMID_TCONT_CAP, unit,
				      ZX_SCH_BUCKET_CAP);

		/* per-queue shaper (RAMID 2/3, addr = que + unit*8) */
		for (que = 0; que < ZX_SCH_QUEUES; que++) {
			u32 addr = que + unit * 8;

			zx_sch_indirect_write(e, ZX_SCH_RAMID_PQ_FILL, addr,
					      ZX_SCH_FILL_RATE);
			zx_sch_indirect_write(e, ZX_SCH_RAMID_PQ_CAP, addr,
					      ZX_SCH_BUCKET_CAP);
		}
	}
	dev_dbg(e->dev, "SCH shaper RAM init: %u units x %u queues, rate=%u cap=%u\n",
		 ZX_SCH_UNITS, ZX_SCH_QUEUES, ZX_SCH_FILL_RATE, ZX_SCH_BUCKET_CAP);
}

/* [txflowctrl 2026-07-04] Legacy shared-ring/dual-kick fallback switch.
 * 0 (default) = stock topology: distinct UP/DN TX rings, SINGLE UP kick per
 * enqueue (stock soft_insert_tx_1desc dir0 — the config stock uses for ALL
 * lan-mode CPU TX incl. CPU→WAN).
 * 1 = the historical mainline config (DN base = UP base, kick both engines).
 * Boot-time only (rings are programmed at init): pass
 * zx279128_eth.zx_tx_dualkick=1 on the kernel cmdline to fall back without a
 * rebuild. The shared config is the documented HW-deadlock topology (see the
 * comment in zx_tm_dma_init) — fallback exists purely for bring-up A/B. */
static unsigned int zx_tx_dualkick;
module_param(zx_tx_dualkick, uint, 0444);
MODULE_PARM_DESC(zx_tx_dualkick, "legacy TM TX shared-ring dual-kick (0=stock single-kick)");

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
	/* TX desc regions: stock writes two DISTINCT addresses (UP ring at
	 * 0x4FFDF000, DN ring at 0x4FFEF000 — 64 KiB apart in carved RAM).
	 * Sharing the same DMA address between UP and DN deadlocks the HW
	 * after ~24 UP entries because the consumer ptr never advances.
	 * Validated via stock devmem2 reads + pon_tm_dma_init RE — see
	 * findings/tm_rx_path_bench_validation_2026-05-27.md.
	 */
	tm_write(e, TM_REG_DMA_TX_UP_BASE, e->txdesc_dma);
	/* [txflowctrl 2026-07-04] DISTINCT DN ring (stock topology, see comment
	 * above). The old shared DN=UP config (the "[egress-port test]" era) is
	 * the documented deadlock topology and is kept only behind the
	 * zx_tx_dualkick=1 boot fallback. */
	tm_write(e, TM_REG_DMA_TX_DN_BASE,
		 zx_tx_dualkick ? e->txdesc_dma : e->dndesc_dma);
	tm_write(e, TM_REG_DMA_REG388,     0x131217);
	tm_write(e, TM_REG_DMA_REG3C,      0x400040);

	/* TM SCH/RED + per-queue templates (0x10140-0x101cc) from stock dump.
	 * Without these the TM kick is accepted but packets aren't processed
	 * onward to PP. The 0x0ac90ac9 at 0x10140 mirrors the TX cmd byte 0xc9.
	 */
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
	 * 0x4040=port mask and 0x4068=ACK control are gating.
	 *
	 * [red-arm 2026-07-04] 0x4004 (RED_CFG, phys 0x92344004): the stock-dump
	 * value is 0xDE, but bit6 = the cpuDn out-buffer charge-accounting MUST
	 * stay CLEARED on mainline (0x9E) or the DN trap-credit leak/wedge comes
	 * back — this very line (a later-init replay of the stock constant) is
	 * what silently reverted the zx_tm_red_init clear on the first fixed
	 * build. See the [red-arm] comment in zx_tm_red_init for the full story
	 * + findings/fix_churn_red_dnbank_2026-07-04.md. */
	tm_write(e, TM_RED_CFG, 0x0000009e);
	tm_write(e, TM_RED_QCFG_CMD, 0x0100017f);
	tm_write(e, TM_RED_QCFG_READY, 0x00000001);
	tm_write(e, TM_RED_QCFG_DATA0, 0xff803fff);
	tm_write(e, TM_RED_QCFG_DATA1, 0x0100ff80);
	tm_write(e, TM_RED_QCFG_DATA2, 0x00100200);
	tm_write(e, TM_RED_QCFG_DATA3, 0x00000020);
	tm_write(e, TM_RED_PORT_MASK, 0x000003ff);
	tm_write(e, TM_RED_RELEASE, 0x0000001b);
	tm_write(e, TM_RED_OUT_SHARE_MAX, 0x00003fff);

	/* SCH (scheduler) globals at TM[0x14000+] — RE'd via SchRegTable + stock dump.
	 * tm[0x14000] = 0x3d7 is the per-port scheduler ENABLE mask (9-bit, ports
	 * 0,1,2,4,6,7,8,9 enabled). Without this, TM dispatches but PP never
	 * receives because the scheduler doesn't run. CRITICAL for TX→PP handoff.
	 */
	tm_write(e, 0x14000, 0x000003d7);	/* per-port SCH enable mask (KEEP).
						 * bit0 = que_sharp_enable (sch_set_que_sharp_enable,
						 * SchRegTable reg_id 0 @ zx-fpga-reg-tables.h:139)
						 * — required for the per-queue shaper to take effect. */
	tm_write(e, 0x14004, 0x0d1cef00);	/* KEEP (stock dump) */
	/* 0x14014/0x14018/0x1401c are the SCH indirect-access CMD/DONE/DATA port,
	 * NOT config words. Previously this code wrote three garbage values
	 * straight to them (CMD=0x03c00006 => RAMID 0xF invalid; DONE is RO; DATA
	 * with no valid command behind it), so the per-queue shaper RAM stayed 0
	 * and the DSCH dropped every CPU egress frame. Replace with a proper
	 * indirect-RAM init that replays stock tm_pon_tm_sch_initial. */
	zx_sch_init(e);
	tm_write(e, 0x14024, 0x00000014);	/* spend_byte (KEEP; sch_set_spend_byte 0x14) */
	tm_write(e, 0x14028, 0x00001869);	/* shp_fill_time (KEEP; sch_set_shp_fill_time 0x1869) */
	tm_write(e, 0x14040, 0x00000249);	/* KEEP (stock dump) */

	/* QMG (queue manager) at TM[0xC000+] — per QmgRegTable + stock dump */
	tm_write(e, TM_QMG_THD, 0x01f40fa0);
	tm_write(e, 0xC004, 0x00000002);
	tm_write(e, 0xC00C, 0x000003ff);
	tm_write(e, 0xC010, 0x00000faa);
	tm_write(e, 0xC02C, 0x00001112);
	tm_write(e, 0xC044, 0x000004f4);
	tm_write(e, 0xC060, 0x0000052e);

	dev_dbg(e->dev, "TM DMA init: ctrl=%#x, timeout=%u, sch[0]=%#x\n",
		 tm_read(e, TM_REG_DMA_CTRL), tm_read(e, TM_REG_DMA_TIMEOUT),
		 tm_read(e, 0x14000));
}

/* soft_release_rx_desc — ACK consumed RX descriptors to HW (mirrors stock).
 * Stock: tm[0x4068] = (rsn<<14) | (count<<4) | qid | (sop<<3); tm[0x4064] = 1
 * sop=1 for "start of packet" descs (single-frag packets), sop=0 for cont.
 */
static int zx_bmu_free_bp(struct zx_eth *e, u16 bp_idx, u8 is_pon);

static void zx_tm_release_rx_desc_raw(struct zx_eth *e, u8 q, u16 count, u8 sop,
				      u8 ring)
{
	int t = 100;

	while (t-- && (tm_read(e, TM_RED_RELEASE_GO) & 1))
		udelay(2);
	if (t < 0) {
		dev_warn_ratelimited(e->dev, "TM release_rx_desc not ready\n");
		return;
	}
	/* [Iter AD 2026-06-04] WEDGE FIX — tm[0x4068] bit14 = RX-ring SELECTOR (HIGH-16 vs
	 * LOW-16 of the packed per-q count tm[0x10100+q*4]). The poll reads pending from the
	 * LOW-16 (ring 0): `status & 0xffff` — but this release HARDCODED bit14=1 (ring 1),
	 * so it drained ring 0 yet ACKed ring 1. Ring 0's consumer count never advanced → after
	 * HW fills one ~1024 ring with no consumer progress it STOPS producing + stops the RX IRQ
	 * → tm_rx_count/tm_irq freeze at ~1024 = the unicast→CPU wedge. Stock soft_release_rx_desc
	 * (plat decomp @0x1a8e8) sets bit14 to MATCH the ring it consumed. Fix: bit14=0 to ack the
	 * ring 0 the poll actually drains. (Explains why Iter U failed: right count, wrong ring.) */
	tm_write(e, TM_RED_RELEASE, ((u32)ring << 14) | ((u32)count << 4) | (u32)q |
			    ((u32)sop << 3));
	tm_write(e, TM_RED_RELEASE_GO, 1);
}

static void zx_tm_release_rx_desc(struct zx_eth *e, u8 q, u16 count)
{
	/* For single-buffer packets, all descs are SOPs (sop=1).
	 * Stock would also do soft_release_rx_desc(1, q, 0, 0) but that's a no-op.
	 */
	zx_tm_release_rx_desc_raw(e, q, count, 1, 0);
}

/* [Stage-3 WiFi Phase B.2, 2026-07-24] TM trap-RX -> bound-vif dispatch.
 *
 * Fix-A on-device validation (findings/wifi_stage3_fixA_ondevice_validation_
 * 2026-07-07.md) proved that fabric-port-6/7 (IDM ring) ingress traps deliver
 * to the CPU on the TM rings (q4 ring0, UP-side) with a fabric-internal
 * ingress identity in desc[6]: raw port >= 0x10 (observed 24 for idm1/ssid0;
 * hypothesis raw = 0x10 | idm<<3 | ssid — the first-8 diag below verifies,
 * incl. the idm0 raw value and the ssid bit placement, ON-DEVICE-UNTESTED).
 * These frames previously died in DSA demux (tag port 23 has no netdev).
 *
 * Semantics: a port-6/7-ingress trap is an UP frame the bound vif already
 * received over the air and injected into the fabric (zx_wifi_rx_handler);
 * the fabric couldn't hw-forward it, so the CPU must now process it as if
 * received on that vif — mirroring stock's wlan->idm->fabric->trap->CPU slow
 * path. Delivery = netif_rx() into the vif with the SHUTTLED cb marker so
 * the vif's rx_handler passes it to the stack (no re-inject loop). The vif's
 * own netdev stats are NOT touched (mac80211/DSA netdevs own their stats).
 *
 * Returns true when the frame was dispatched (caller skips the baseline sw
 * delivery); false = keep baseline behavior (unbound, alloc failure).
 */
#define ZX_ET_KNOWN(et) ((et) == ETH_P_IP || (et) == ETH_P_ARP || \
			 (et) == ETH_P_IPV6 || (et) == ETH_P_8021Q || \
			 (et) == ETH_P_PPP_DISC || (et) == ETH_P_PPP_SES || \
			 (et) == ETH_P_PAE)

/* [Phase B close-out, 2026-07-25] Fabric trap frames reach the CPU in more
 * than one layout, and the desc len field's meaning varies with the path:
 *   - UP-ring traps (B.2's ARPs):        eth frame at bp+16 (16B HW prefix)
 *   - DN traps via the trap path:        eth frame at bp+18 (extra 2B stub —
 *     the July live-proven UNHANDLED_PROTO 0x9f2a shift, commit 5e2d25a5e)
 *   - DN bridge-FORWARD-to-CPU (seen on the first #529 boot with the VLAN
 *     check cleared at init): NO ethernet header — the IP packet sits
 *     directly at bp+16 (TM-RX debug showed dst=45:00:.. et=c0a8 = raw IPv4
 *     bytes, and desc len == the IP total-length exactly).
 * A blind stub-size heuristic can't cover all of these, so detect by
 * CONTENT: probe the 4 plausible eth-frame offsets for a known ethertype
 * (0x9f2a-style SA tails are not in the known set), and if none matches,
 * accept a bare IPv4/IPv6 header at bp+16 and deliver it tun-style (L3,
 * skb->protocol set by hand). Frame length is derived from the L3 header
 * (IP total-length / IPv6 payload-length) rather than the ambiguous desc
 * len whenever possible. */
static bool zx_wifi_tm_rx_dispatch(struct zx_eth *e, const u8 *bp, u16 len,
				   u8 raw)
{
	u8 idm = (raw >> 3) & 1, ssid = raw & 7;
	struct zx_wifi_dispatch_node *wn = &e->zx_wifi_dispatch[ssid + idm * 8];
	bool bound = wn->enabled && wn->wlan_ndev &&
		     (wn->wlan_ndev->flags & IFF_UP);
	struct zx_skb_wifi_tag *tag;
	struct sk_buff *skb;
	static const u8 cands[4] = { 16, 18, 2, 0 };
	const u8 *frm = NULL;
	u16 flen = 0, l3proto = 0;
	int i;

	e->tm_rx_fabric++;
	if (e->tm_rx_fabric <= 8) {
		dev_info(e->dev,
			 "TM-RX fabric #%u raw=0x%02x (idm%u ssid%u) len=%u bound=%d\n",
			 e->tm_rx_fabric, raw, idm, ssid, len, bound);
		print_hex_dump(KERN_INFO, "  bp: ", DUMP_PREFIX_OFFSET, 16, 1,
			       bp, 48, false);
	}
	if (!bound) {
		e->tm_wifi_rx_nobind++;
		return false;
	}

	/* 1) Ethernet frame at one of the known stub offsets? */
	for (i = 0; i < 4; i++) {
		u16 et = ntohs(*(const __be16 *)(bp + cands[i] + 12));

		if (!ZX_ET_KNOWN(et))
			continue;
		frm = bp + cands[i];
		if (et == ETH_P_IP)
			flen = 14 + ntohs(*(const __be16 *)(frm + 16));
		else if (et == ETH_P_IPV6)
			flen = 14 + 40 + ntohs(*(const __be16 *)(frm + 18));
		else if (et == ETH_P_ARP)
			flen = 60;	/* 42 real + min-frame pad */
		else
			flen = len;	/* PAE/PPPoE/8021Q: trust desc len */
		break;
	}
	/* 2) Bare L3 at bp+16 (DN bridge-FORWARD delivery, no eth header). */
	if (!frm && (bp[16] >> 4) == 4 && (bp[16] & 0xf) >= 5) {
		u16 totlen = ntohs(*(const __be16 *)(bp + 18));

		if (totlen >= 20) {
			frm = bp + 16;
			flen = totlen;
			l3proto = ETH_P_IP;
		}
	}
	if (!frm && (bp[16] >> 4) == 6) {
		frm = bp + 16;
		flen = 40 + ntohs(*(const __be16 *)(bp + 20));
		l3proto = ETH_P_IPV6;
	}
	if (!frm || flen < 20 ||
	    flen > TM_BP_SIZE - (u16)(frm - bp)) {
		e->tm_wifi_rx_noparse++;
		if (e->tm_wifi_rx_noparse <= 4) {
			dev_dbg(e->dev, "TM-RX fabric NOPARSE #%u len=%u\n",
				 e->tm_wifi_rx_noparse, len);
			print_hex_dump(KERN_INFO, "  bp: ", DUMP_PREFIX_OFFSET,
				       16, 1, bp, 48, false);
		}
		return false;
	}

	skb = netdev_alloc_skb(wn->wlan_ndev, flen + 32);
	if (!skb)
		return false;
	skb_reserve(skb, 16);
	memcpy(skb_put(skb, flen), frm, flen);
	tag = (struct zx_skb_wifi_tag *)&skb->cb[ZX_SKB_CB_TAG_OFF];
	tag->magic = ZX_SKB_CB_TAG_MAGIC_SHUTTLED;
	tag->ssid  = ssid;
	if (l3proto) {
		/* tun-style L3 delivery: no mac header to parse */
		skb->dev = wn->wlan_ndev;
		skb->protocol = htons(l3proto);
		skb->pkt_type = PACKET_HOST;
		skb_reset_mac_header(skb);
	} else {
		skb->protocol = eth_type_trans(skb, wn->wlan_ndev);
	}
	netif_rx(skb);
	e->tm_wifi_rx_dispatched++;
	return true;
}
#undef ZX_ET_KNOWN

/* NAPI poll — based on pon_tm_net_poll RE, simplified for first iteration */
/* RX checkpoint logging — kept under pr_debug so it compiles out unless
 * the file/dyn-debug is enabled. The first-N-polls gate is preserved so
 * even with debug on the log stays bounded during bring-up.
 */
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

	/* Drain BOTH RX rings per queue. ring 0 (LOW16) = UP/LAN trap path (works);
	 * ring 1 (HIGH16) = DN path for the WAN/MAC4 uplink ingress→CPU. The HW writes
	 * ring 1 at rxdesc + 0x20000 (stock queue_init: single TM[+0xF0] base, ring1 =
	 * region + 0x20000). Mainline read only LOW16 → WAN/DN frames piled in ring 1
	 * (q7 HIGH16) undrained → WAN RX→CPU never worked. Release tm[0x4068] bit14=ring.
	 * (2026-06-06, stock pon_tm_net_poll dual-ring; root cause via user "check main".) */
	for (int ring = 0; ring < 2 && done < budget; ring++) {
	 u8  *desc_base = ring ? (u8 *)e->rxdesc_dn_cpu : (u8 *)e->rxdesc_cpu;
	 u32 *heads     = ring ? e->rx_head_dn : e->rx_head;

	 for (q = 0; q < TM_NUM_RX_QUEUES && done < budget; q++) {
		u32 status = tm_read(e, TM_RX_QCNT_BASE + q * 4);
		u32 pending = ring ? (status >> 16) : (status & 0xffff);
		u8  rxring = (u8)ring;
		u32 take, n, ack = 0, start_head, slots;

		if (!pending) {
			if (e->tm_napi_count < 5 && q == 0)
				RXCP(e, 2, "q=%d no pending (raw=%#x)", q, status);
			continue;
		}
		RXCP(e, 3, "q=%d pending=%u (raw status=%#x)", q, pending, status);

		take = min_t(u32, pending, (u32)(budget - done));
		take = min_t(u32, take, TM_RX_DESC_PER_Q);
		start_head = heads[q];	/* [Iter U] remember ring pos to release the FULL advance */

		/* [Iter 31] HW writes RX descs out-of-order: in queue 5, first
		 * frame at idx 0, subsequent at idx 12+. SW rx_head[q] advance
		 * by 1 each frame misses non-contiguous descs. Scan forward
		 * looking for valid desc (len > 0) — skip empty/stale entries.
		 */
		for (n = 0; n < take; n++) {
			u32 idx = heads[q];
			u8 *desc;
			u16 len;
			int scan;

			/* Skip empty descs (len=0) up to a full ring scan */
			for (scan = 0; scan < TM_RX_DESC_PER_Q; scan++) {
				desc = desc_base +
					(q * TM_RX_DESC_PER_Q + idx) * TM_DESC_SIZE;
				len = le16_to_cpu(*(__le16 *)(desc + 12)) >> 2;
				if (len > 0 && len < 1600)
					break;
				idx = (idx + 1) & (TM_RX_DESC_PER_Q - 1);
			}
			if (scan >= TM_RX_DESC_PER_Q) {
				/* Scanned whole ring, no valid desc → stop */
				break;
			}
			heads[q] = idx;
			/* bp_idx is 10 bits split: low 7 in desc[7]>>1, high 7 in desc[8].
			 * Stock pon_tm_net_poll @ +0x8754:
			 *   uVar11 = (desc[7]>>1) | (desc[8]<<7);
			 */
			u16 bppe_idx = ((u16)(desc[7] >> 1)) |
				       ((u16)desc[8] << 7);
			RXCP(e, 4, "q=%d desc[%u] @%p: len=%u bppe=%u raw[0..7]=%02x %02x %02x %02x %02x %02x %02x %02x",
			     q, idx, desc, len, bppe_idx,
			     desc[0], desc[1], desc[2], desc[3],
			     desc[4], desc[5], desc[6], desc[7]);

			if (len > 0 && len < 1600 &&
			    bppe_idx < TM_BPPE_POOL_SIZE && e->bp_cpu) {
				u8 *bp_buf = (u8 *)e->bp_cpu + (u32)bppe_idx * TM_BP_SIZE;
				u16 et_at_0 = ntohs(*(const __be16 *)(bp_buf + 12));
			const u8 *src = (et_at_0 >= 0x0600 && et_at_0 != 0xffff) ?
					bp_buf : (bp_buf + 16);
			/* Ingress port comes from desc[6] bits 3..7 minus 1.
				 * Per stock RE: `r2 = (desc[6] >> 3) & 0x1F; r2 -= 1;
				 * pkt[180] = r2`. This is the UNI/PON port the packet
				 * arrived on.
				 */
				int ingress_port = ((desc[6] >> 3) & 0x1F) - 1;
				bool dsa = netdev_uses_dsa(e->sw_dev);
				/* Per-ingress counter for empirical CPU-loopback port id */
				{
					int slot = (ingress_port + 1) & 0x1F;

					e->tm_rx_per_ingress[slot]++;
				}
				if (dsa && ingress_port < 0) {
					/* DSA: no user port to demux an invalid ingress to;
					 * drop it (no delivery). The BP is freed by the
					 * common release below — do NOT free it here too.
					 * [wedge fix 2026-07-31] an extra zx_bmu_free_bp
					 * in this branch double-freed the BP: the duplicate
					 * index in the BPPE free ring made the HW allocator
					 * hand ONE buffer to TWO in-flight frames, which is
					 * the fabric-ingress endurance wedge (corrupted
					 * parse keys, then chip-wide MAC-admit halt).
					 * Live-proven: tm_rx_loopback_drops == the BMU
					 * alloc/release ledger drift (149) at wedge onset. */
					;
				} else if (e->sw_dev &&
					   !memcmp(src + 6, e->sw_dev->dev_addr, 6)) {
					/* Loopback suppression: the switch fabric hairpins the
					 * CPU's own egress back to the CPU RX path in BOTH
					 * standalone and DSA modes (HW behaviour, not a forwarding
					 * decision — confirmed 2026-05-31: isolating the fabric to
					 * CPU<->lan2 only did NOT stop it). Without this drop the
					 * hairpin amplifies into a DUP storm (host saw ~200 copies
					 * per ICMP reply). A frame whose SRC MAC is our own conduit
					 * MAC can only be our reflected TX — drop it. Bridge transit
					 * frames keep the original end-host SRC MAC, so this never
					 * drops legitimately forwarded traffic. */
					e->tm_rx_loopback_drops++;
					if (e->tm_rx_loopback_drops <= 5)
						dev_info(e->dev, "LOOPBACK drop #%u src=%pM dst=%pM ethertype=%04x len=%u ingress=%d\n",
							 e->tm_rx_loopback_drops, src + 6, src,
							 ntohs(*(__be16 *)(src + 12)), len, ingress_port);
					/* [wedge fix 2026-07-31] BP freed ONLY by the common
					 * release below. The extra zx_bmu_free_bp that used
					 * to sit here was the primary double-free feeder:
					 * every hairpinned CPU-egress frame poisoned the
					 * BPPE free ring with a duplicate BP index (one per
					 * loopback drop — ledger-verified live). */
				} else if (ingress_port >= 15 &&
					   zx_wifi_tm_rx_dispatch(e, bp_buf, len,
						(u8)(ingress_port + 1))) {
					/* [Stage-3 WiFi Phase B.2] fabric/IDM-ingress
					 * trap (desc raw port >= 0x10) handed to the
					 * bound vif's stack. When unbound the helper
					 * returns false and the frame falls through
					 * to the baseline sw delivery below (where
					 * DSA demux drops it — pre-B.2 behavior).
					 * BP is freed by the common release below. */
					e->tm_rx_count++;
				} else {
					struct sk_buff *skb =
						netdev_alloc_skb(e->sw_dev,
								 len + (dsa ? ZTE_TAG_LEN : 0) + 64);

					if (skb) {
						skb_reserve(skb, 32);
						/* [P1 conduit/DSA] prepend the 4-byte internal tag
						 * {0x5a, ingress_port,...} so tag_zte's rcv (reached via
						 * the ETH_P_XDSA ptype after eth_type_trans) demuxes the
						 * frame to the lan<ingress> netdev. Dormant until a DSA
						 * switch binds (netdev_uses_dsa false otherwise). */
						if (dsa) {
							u8 *t = skb_put(skb, ZTE_TAG_LEN);

							t[0] = ZTE_TAG_MARK;
							t[1] = ingress_port & 0xff;
							t[2] = 0;
							t[3] = 0;
						}
						memcpy(skb_put(skb, len), src, len);
						skb->protocol = eth_type_trans(skb, e->sw_dev);
						e->sw_dev->stats.rx_packets++;
						e->sw_dev->stats.rx_bytes += len;
						netif_receive_skb(skb);
						e->tm_rx_count++;
						if (e->tm_rx_count <= 10) {	/* first-N trap classifier (kept low; was bumped to 130 for the Iter AC TCP-trap RE) */
							dev_info(e->dev, "TM RX q=%d idx=%u len=%u bppe=%u src=%pM dst=%pM ethertype=%04x ingress=%d delivered\n",
								 q, idx, len, bppe_idx,
								 src + 6, src, ntohs(*(__be16 *)(src + 12)),
								 ingress_port);
						}
						/* [Iter AH] TCP-trap slot identifier: for the first
						 * ~50 IPv4-TCP frames that trap, log the trap QUEUE
						 * (q maps to the chip ptype slot via zx_def_ptl_pkt_map)
						 * + L4 detail, so we can see which ptype the chip
						 * assigns to TCP pure-ACKs (which trap) vs TCP data
						 * (which HW-forwards). Dump desc bytes too in case the
						 * ptype rides in the RX descriptor directly. */
						{
							static u32 tcptrap_log;
							u16 et = ntohs(*(const __be16 *)(src + 12));

							if (et == 0x0800 && tcptrap_log < 50) {
								const u8 *ip = src + 14;
								u8 ihl = (ip[0] & 0x0f) * 4;
								u8 proto = ip[9];

								if (proto == 6) {
									const u8 *tcp = ip + ihl;
									u8 thl = (tcp[12] >> 4) * 4;
									u8 flags = tcp[13];
									int payload = (int)len - 14 - ihl - thl;

									tcptrap_log++;
									dev_info(e->dev,
										"TCPTRAP #%u q=%d len=%u ihl=%u thl=%u payload=%d flags=%02x %s ingress=%d desc[4..b]=%02x %02x %02x %02x %02x %02x %02x %02x\n",
										tcptrap_log, q, len, ihl, thl, payload, flags,
										(payload <= 0 && (flags & 0x10)) ? "PURE-ACK" : "data",
										ingress_port,
										desc[4], desc[5], desc[6], desc[7],
										desc[8], desc[9], desc[10], desc[11]);
								}
							}
						}
						/* Dynamic FDB learning DISABLED (degradation test).
						 * Per round-2 review: zx_fdb_add writes to PP_BRG_RAM
						 * (VLAN table), not the sbrag MAC FDB the switch reads
						 * on egress. After many writes the wrong-table state
						 * may flip switch behavior to flood — explains the
						 * RUN1→RUN2 DUP storm (0 → 60+ DUPs over 10s).
						 * Keep only the at-probe HW FDB seed for own MAC.
						 */
					}
				}
				/* Release BP back to BMU pool — stock NAPI calls
				 * pp_bmu_free_bp once per descriptor (delivered OR
				 * dropped). Without this the pool exhausts: validated
				 * 2026-05-27 via stock-vs-mainline BMU register diff
				 * (mainline alloc 17912 / rls 15946, pool bppe_cnt=0)
				 * + stock BMU-disable repro of mainline syndrome.
				 * Per Phase 53 finding doc.
				 */
				zx_bmu_free_bp(e, bppe_idx, 0);
			}
			/* [dup-fix 2026-05-31] INVALIDATE the consumed RX descriptor
			 * (clear the len field desc[12..13] the scan keys on). The
			 * scan re-finds any desc with len>0 as "valid"; without
			 * clearing, a delivered desc stays valid and gets re-read on
			 * ring-wrap / re-scan -> the same BP (bppe) is delivered again
			 * (the lan2 dup storm: identical copies, same bppe, growing
			 * over time). Stock invalidates each desc after consuming it.
			 * dma_wmb so the HW sees it before re-filling the slot. */
			*(__le16 *)(desc + 12) = 0;
			dma_wmb();
			heads[q] = (idx + 1) & (TM_RX_DESC_PER_Q - 1);
			done++;
			ack++;
		}

		/* ACK to HW so pending count decrements (stock: soft_release_rx_desc).
		 * [Iter U 2026-06-04] WEDGE FIX: release EVERY ring slot the poll
		 * advanced past, not just the `ack` delivered frames. The scan-forward
		 * (skip len=0/stale descs) moves rx_head past skipped slots; if those
		 * are never released, HW's free-slot count never recovers and after one
		 * TM_RX_DESC_PER_Q wrap the RX engine stops producing (tm_irq_count
		 * freezes) — the unicast→CPU wedge. Stock pon_tm_net_poll releases the
		 * full scanned range in two calls (sop=0 non-delivered + sop=1 delivered).
		 */
		slots = (heads[q] - start_head) & (TM_RX_DESC_PER_Q - 1);
		if (slots > ack)
			zx_tm_release_rx_desc_raw(e, (u8)q, (u16)(slots - ack), 0, rxring);
		if (ack)
			zx_tm_release_rx_desc_raw(e, (u8)q, (u16)ack, 1, rxring);
	 }
	}

	if (done < budget) {
		napi_complete_done(napi, done);
		/* Re-arm: CLEAR mask bits to re-enable IRQs (1=masked semantics) */
		tm_and(e, TM_REG_IRQ_MASK, ~(u32)TM_IRQ_ARM_BITS);
		/* [Iter W 2026-06-04] A pending-recheck+napi_schedule re-arm was tried
		 * here to close a suspected missed-IRQ race — REVERTED: it busy-looped
		 * (TM_RX_QCNT low16 reads nonzero when empty → 235k polls) AND did NOT
		 * raise throughput (tm_rx still capped ~922 under flood, RED dropping
		 * 4005). ⇒ NAPI scheduling is NOT the bottleneck; RED drops trap-bound
		 * frames BEFORE the CPU RX ring. See findings Iter W.
		 */
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

/* [A07] PON aggregate IRQ handler — mirrors stock zx_pon_int (plat:7657).
 *
 * Reads pon[0x40040] & ~pon[0x40044] (status AND-NOT mask = pending+enabled
 * bits). Stock dispatches bit 6 → lp_isr, bit 4 → rog_onu_flag. We don't
 * have those sub-handlers wired yet, so this is a minimal stub: read +
 * log + return IRQ_HANDLED. The READ itself is the ack — leaving status
 * unread keeps the level-triggered GIC line asserted.
 *
 * Hypothesis (iter14_bit1_ack_not_in_napi_path_2026-05-27.md): the
 * PON aggregate IRQ has a TX-related event (bit 7 in mask = unmasked)
 * that mainline never services. Without service, the HW TX consume
 * engine may stall waiting for a SW handshake.
 */
static irqreturn_t zx_pon_irq(int irq, void *dev_id)
{
	struct zx_eth *e = dev_id;
	u32 status, mask, pending;
	static u32 pon_irq_count;

	if (!e->pon_early)
		return IRQ_NONE;

	status = readl(e->pon_early + 0x40040);
	mask   = readl(e->pon_early + 0x40044);
	pending = status & ~mask;

	pon_irq_count++;
	if (pon_irq_count < 8)
		dev_info(e->dev, "[A07/PON_IRQ#%u] status=%#x mask=%#x pending=%#x\n",
			 pon_irq_count, status, mask, pending);

	return IRQ_HANDLED;
}

/* ============================================================
 *   "sw" netdev — what stock calls pon_tm_netdev[0]
 * ============================================================
 */

static struct delayed_work zx_bmu_dump_work;
static struct zx_eth *zx_bmu_dump_eth;

/* [txflowctrl 2026-07-04] TM TX-ring flow control — port of stock's CPU-TX
 * occupancy accounting (pon_tm_get_next_txdesc plat:6689 +
 * pon_tm_check_tx_done_nolock plat:6362 + pon_tm_timer_func plat:6438).
 *
 * The low16 of TM[0x10058] (UP) / TM[0x10068] (DN) is CLEAR-ON-READ
 * "descriptors consumed since last read" (empirically confirmed 2026-05-27,
 * commit 546ae0b3a). Stock keeps a per-direction in-flight counter:
 * +1 per enqueue, -= consumed-count on reclaim; reclaims on-demand in the
 * hot path once pending > 0x1ff and REFUSES the enqueue (drops the skb) at
 * pending > 0x3ff, so it can never overwrite a descriptor the HW still owns.
 * A 1-jiffy kernel timer (add_timer, NOT a workqueue — must keep running
 * when kworkers starve under load) reclaims in the background.
 *
 * Mainline previously had NONE of this: tx_head wrapped at 1024 and
 * memset-overwrote live descriptors, which under sustained ACK load overran
 * the ring → torn descs (the exactly-64B TX latch), engine cursor corruption
 * (mac4_tx halt), BMU buffer-pointer leaks → global RX descriptor-engine
 * halt, reboot-only. See findings/stock_red_drain_up_RE_2026-07-04.md.
 */
#define TM_SW_TX_RECLAIM_THRESH	0x1ff	/* half-full: reclaim in the hot path */
#define TM_SW_TX_FULL_THRESH	0x3ff	/* stock: refuse enqueue at ring-full */
#define TM_SW_TX_FULL_SHARED	0x300	/* conservative full mark for the
					 * dual-kick fallback (two engines
					 * walking one shared ring) */
#define TM_SW_TX_WAKE_THRESH	0x200	/* wake the stopped queue below this */

static struct timer_list zx_sw_tx_reclaim_timer;
static struct zx_eth *zx_tm_tx_reclaim_eth;
static bool zx_sw_tx_reclaim_timer_ready;

static inline u32 zx_sw_tx_full_thresh(void)
{
	return zx_tx_dualkick ? TM_SW_TX_FULL_SHARED : TM_SW_TX_FULL_THRESH;
}

/* Reclaim completed TX descriptors against the HW clear-on-read
 * consumed-count register(s). THE ONLY PLACE those registers may be read.
 * Caller must hold tm_tx_lock. */
static void zx_sw_tx_reclaim_locked(struct zx_eth *e)
{
	u32 done = tm_read(e, TM_REG_DMA_DESC_CNT_UP) & 0xffff;

	if (zx_tx_dualkick)
		done += tm_read(e, TM_REG_DMA_DESC_CNT_DN) & 0xffff;
	if (done > e->sw_tx_pending)	/* defensive: never underflow */
		done = e->sw_tx_pending;
	e->sw_tx_pending -= done;
	e->sw_tx_reclaimed += done;
	if (e->sw_dev && netif_queue_stopped(e->sw_dev) &&
	    e->sw_tx_pending <= TM_SW_TX_WAKE_THRESH)
		netif_wake_queue(e->sw_dev);
}

/* 1-jiffy background reclaim — kernel timer, NOT a workqueue: the wedge
 * builds exactly when ksoftirqd/kworkers spin, and a delayed_work would
 * starve then (stock uses add_timer for the same reason). */
static void zx_sw_tx_reclaim_timer_fn(struct timer_list *t)
{
	struct zx_eth *e = zx_tm_tx_reclaim_eth;
	unsigned long flags;

	if (!e)
		return;	/* remove path cleared us; do not re-arm */
	spin_lock_irqsave(&e->tm_tx_lock, flags);
	if (e->sw_tx_pending)
		zx_sw_tx_reclaim_locked(e);
	spin_unlock_irqrestore(&e->tm_tx_lock, flags);
	mod_timer(&zx_sw_tx_reclaim_timer, jiffies + 1);
}

/* [egress keepalive 2026-05-29] Mirror stock extphy_timer_func (plat:3137), which
 * re-runs the per-link MAC bring-up every ~10 jiffies. That re-trigger is what
 * catches/holds the TRANSIENT SOPC<->MAC bridge READY bit (0x19068 bit port+5):
 * mainline sets the bridge once at link-up, then READY drops and send2smac2 stops
 * (egress dies). This worker periodically re-asserts the LIGHT part of the chain
 * (config_speed_duplex ctrl + ready-gated 0x19068 enable + MAC enable) for each
 * link-up host port — NO pon_reset/smac_init, so it doesn't disturb live traffic. */
static struct delayed_work zx_mac_keepalive_work;
static struct zx_eth *zx_mac_keepalive_eth;

static void zx_mac_keepalive_fn(struct work_struct *w)
{
	struct zx_eth *e = zx_mac_keepalive_eth;
	int i;

	if (!e)
		goto resched;
	for (i = 0; i < 5; i++) {	/* [WAN] incl. MAC4/WAN; NULL gephy[i] skipped below */
		struct phy_device *phy = e->gephy[i];
		void __iomem *mc = e->base + mac_off(i, MAC_REG_CONTROL);
		void __iomem *br = e->base + NPP_REG_SOPC_BRIDGE;
		u32 c, reg;
		int t;
		/* [WAN] MAC4 = the WAN port (external ZX5201 PHY @ MDIO 0x08, NOT
		 * phylib-probed → gephy[4]==NULL). Without holding its SOPC bridge
		 * (0x19068 bit4) + MAC enable open here, the one-shot is_wan bring-up
		 * in zx_eth_adjust_link decays and send2smac4 stops → CPU→MAC4 egress
		 * dies after QMG sw_fwd. Re-assert it as a fixed 1G/FD always-up port
		 * (only after the one-shot set phy_was_link[4]). See mac4_wan_tx_egress_re.md */
		bool is_wan = (i == 4 && !phy);

		if (is_wan) {
			if (!e->phy_was_link[i])
				continue;
		} else if (!phy || !phy->link || !e->phy_was_link[i]) {
			continue;
		}

		/* re-write running ctrl (config_speed_duplex): gigabit/FD => clear
		 * bit15, set bit13 (0xBA6003); re-triggers the MAC->PHY handshake. */
		c = readl(mc);
		if (is_wan || phy->speed == SPEED_1000)
			c = (c & ~0x8000u) | 0x2000u;
		writel(c, mc);

		/* ready-gated SOPC bridge enable: catch the READY pulse (i+5), set
		 * the enable bit (i) ONLY when ready is observed (stock semantics). */
		for (t = 0; t < 5; t++) {
			reg = readl(br);
			if (reg & (1u << (i + 5))) {
				writel(reg | (1u << i), br);
				break;
			}
			udelay(50);
		}

		/* re-assert MAC enable (stock steady-state pon_npp_smac_enable) */
		writel(readl(mc) | 0x3u, mc);
	}
resched:
	schedule_delayed_work(&zx_mac_keepalive_work, msecs_to_jiffies(100));
}

/* Periodic STATS dump — DISABLED by default (was flooding the bridge log
 * every 5s with no actionable change). Re-enable temporarily for debug by
 * defining ZX_PERIODIC_STATS=1. The one-shot at sw_open+30s is enough for
 * normal observation; if you need correlation across ping runs, bump the
 * macro and rebuild.
 */
#define ZX_PERIODIC_STATS	0

static void zx_bmu_dump_fn(struct work_struct *w)
{
	struct zx_eth *e = zx_bmu_dump_eth;
	u32 alloc, rls, bppe_avail, bppi, bp_stat, tx_kick, tx_pend;

	if (!e)
		return;
	/* Compact one-line dump: most-changing counters for ping-loop correlation */
	alloc      = tm_read(e, 0x8090);
	rls        = tm_read(e, 0x8098);
	bppe_avail = tm_read(e, 0x8080);
	bppi       = tm_read(e, 0x8088);
	bp_stat    = tm_read(e, TM_REG_BMU_BP_STAT);
	tx_kick    = tm_read(e, TM_REG_DMA_TX_UP_KICK);
	/* [txflowctrl] TM[0x10058] is CLEAR-ON-READ and owned by the reclaim —
	 * report the driver's occupancy counter instead of a raw read. */
	tx_pend    = e->sw_tx_pending;
	dev_dbg(e->dev,
		 "STATS uptime_jiff=%lu drv:rx=%u rxlb=%u tx=%u txdrop=%u napi=%u irq=%u hw:alloc=%u rls=%u(diff=%d) bppe_avail=%u bppi=%u bp_stat=%08x tx_kick=%u tx_pend=%u\n",
		 jiffies,
		 e->tm_rx_count, e->tm_rx_loopback_drops, e->tm_tx_count, e->tm_tx_dropped,
		 e->tm_napi_count, e->tm_irq_count,
		 alloc, rls, (int)rls - (int)alloc,
		 bppe_avail, bppi, bp_stat,
		 tx_kick, tx_pend);

	/* Per-ingress-port RX histogram — for DUPs hairpin diagnosis.
	 * The port whose count grows ~1:1 with tm_tx_count is the CPU hairpin
	 * loopback source. Drop frames from it to break the amplification
	 * loop. Slots [0..31] = ingress_port+1 (so slot 0 = ingress -1 "invalid",
	 * slot 1 = port 0, slot 8 = port 7, etc.).
	 */
	dev_dbg(e->dev, "STATS rx_per_ingress[]: [ing-1]=%u [0]=%u [1]=%u [2]=%u [3]=%u [4]=%u [5]=%u [6]=%u [7]=%u [8]=%u [9]=%u [10]=%u [11]=%u [12]=%u [13]=%u\n",
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

	netdev_dbg(ndev, "sw open\n");
	napi_enable(&e->tm_napi);
	/* Unmask TM IRQs: CLEAR bits 0,1 (1=masked semantics) */
	tm_and(e, TM_REG_IRQ_MASK, ~(u32)TM_IRQ_ARM_BITS);
	netdev_dbg(ndev, "sw open: TM IRQ_MASK now 0x%08x (was 0xFFFFFFFF)\n",
		    tm_read(e, TM_REG_IRQ_MASK));
	netif_carrier_on(ndev);
	netif_start_queue(ndev);

	/* Schedule a BMU state dump 30s from now — by then kernel printk
	 * is calm and our dev_info messages will reliably reach UART.
	 */
	zx_bmu_dump_eth = e;
	INIT_DELAYED_WORK(&zx_bmu_dump_work, zx_bmu_dump_fn);
	schedule_delayed_work(&zx_bmu_dump_work, msecs_to_jiffies(10000));

	/* [txflowctrl] TM TX reclaim — 1-jiffy kernel timer (stock
	 * pon_tm_timer_func): reclaims the clear-on-read consumed-counts
	 * into sw_tx_pending and wakes the queue after a ring-full stop. */
	zx_tm_tx_reclaim_eth = e;
	if (!zx_sw_tx_reclaim_timer_ready) {
		timer_setup(&zx_sw_tx_reclaim_timer,
			    zx_sw_tx_reclaim_timer_fn, 0);
		zx_sw_tx_reclaim_timer_ready = true;
	}
	mod_timer(&zx_sw_tx_reclaim_timer, jiffies + 1);

	/* [egress keepalive] periodic SOPC<->MAC bridge re-assert (stock extphy_timer
	 * equivalent) — holds the transient 0x19068 READY so CPU->LAN egress stays up. */
	zx_mac_keepalive_eth = e;
	INIT_DELAYED_WORK(&zx_mac_keepalive_work, zx_mac_keepalive_fn);
	schedule_delayed_work(&zx_mac_keepalive_work, msecs_to_jiffies(200));

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
	netdev_dbg(ndev, "sw stop\n");
	return 0;
}


/* BMU alloc — mirror of pon_tm_bmu_alloc_bp.
 *  Returns bp index (0..N-1) on success, 0xFFFF on failure.
 *  Protocol (per Ghidra RE):
 *    1. set tm[0x8014] |= 1   (alloc kick)
 *    2. poll tm[0x8014] & 3 == 0 (busy/done bits)
 *    3. read tm[0x800c]; bit31 = error, bits[15:0] = bp idx
 */
/* HW BMU buffer-pool allocator.
 *
 * Protocol per pon_tm_bmu_alloc_bp in plat-zxylzb_9128S.ko @ 0x18668:
 *   1. set tm[0x8014] |= 1            (alloc kick)
 *   2. poll tm[0x8014] & 3 == 0       (busy/done bits clear when done)
 *   3. read tm[0x800c]: bit31 SET = valid, bits[15:0] = bp_idx;
 *                       bit31 CLEAR = pool empty / error
 *
 * Returns the allocated bp_idx (0..1023), or U32_MAX on failure. Caller
 * must check and drop TX on failure.
 *
 * Spin-locked because alloc must be serialized — HW has one alloc engine.
 * Reuses e->tx_lock since alloc only happens in the TX path.
 */
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
 * Returns 0 on success, -EBUSY on credit-refill timeout.
 */
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
		 * wrong — it gave 1 credit per refill, starving the pool.
		 */
		e->bmu_free_credit = (tm_read(e, TM_REG_BMU_BP_STAT) >> 3) & 0x3f;
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
 * pr_debug so it compiles out unless the file/dyn-debug is enabled.
 */
#define TXCP(e, stage, fmt, ...) do { \
	if ((e)->tm_tx_count < 5) \
		pr_debug("[ZXETH/TX#%u CP%d:%s] " fmt "\n", \
			 (e)->tm_tx_count, stage, __func__, ##__VA_ARGS__); \
} while (0)

/* [egress fix 2026-05-30] DN egress-port hint. Stock DN desc encodes the
 * FDB-resolved egress port as ((port+0x28)&0x3f)<<4 in desc bytes[2:3]
 * (decomp pon_tm_net_tx plat:6848). LIVE-PROVEN on the H3600: port=2 routes a
 * CPU->LAN frame to MAC2 (the cabled host port) with ZERO DSCH drops —
 * send2smac2 + MAC2 TX climb. The old default 4 directed frames to a no-link
 * port, so DSCH dropped every frame (the long-hunted "dies at DSCH" wall).
 * Still a module param (0644) so other cablings can be swept at runtime. */
static unsigned int zx_eg_port = 2;
module_param(zx_eg_port, uint, 0644);
MODULE_PARM_DESC(zx_eg_port, "DN egress port index for the host MAC (desc hint (port+0x28)<<4)");

static netdev_tx_t zx_sw_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct zx_eth *e = *(struct zx_eth **)netdev_priv(ndev);
	unsigned long flags;
	u32 bp, len;
	u8 *bp_buf;
	u8 *desc;
	u8 eg = zx_eg_port;	/* egress switch port for the desc hint */

	/* CPU→LAN egress: submit on the TM UP DMA ring (kick TM[0x10054]). Live
	 * oracles proved stock uses NO DMA ring (UP/DN/IDM consume counters all 0)
	 * — it software-forwards straight to QMG sw_fwd. We can't yet replicate that
	 * exact no-ring inject, but the UP ring is the path that DOES reach QMG
	 * sw_fwd on mainline (the furthest we get); the remaining gate is QMG
	 * sw_fwd → SOPC send2smac2 (SOPC never fires for the CPU-sourced frame).
	 * Keeping the UP ring as the QMG-reaching baseline while we crack SOPC.
	 * (IDM-ring attempt reverted: HW consumed descs but frame never reached
	 * QMG — see idm_ring_xmit_test_result + stock_{idm,dn}_ring_usage_oracle.)
	 */
	TXCP(e, 1, "enter skb=%p len=%u dev=%s tx_head=%u",
	     skb, skb->len, ndev->name, e->tx_head);

	if (!e->bp_cpu || !e->dndesc_cpu) {
		TXCP(e, -1, "DROP: bp_cpu=%p dndesc_cpu=%p", e->bp_cpu, e->dndesc_cpu);
		goto drop;
	}

	/* [P1 conduit/DSA] When this netdev is a DSA conduit, frames arrive from
	 * tag_zte with a 4-byte internal tag prepended ({0x5a, egress_port, 0, 0}).
	 * Consume the egress port and skb_pull the tag so the rest of the path sees
	 * the bare frame (the tag never reaches the wire). Dormant until a DSA
	 * switch binds to this conduit (netdev_uses_dsa == false otherwise), so the
	 * standalone egress path is unaffected. See dsa_conduit_refactor_guide.md. */
	if (netdev_uses_dsa(ndev) && skb->len >= ZTE_TAG_LEN + ETH_HLEN &&
	    skb->data[0] == ZTE_TAG_MARK) {
		eg = skb->data[1];
		skb_pull(skb, ZTE_TAG_LEN);
	}

	/* skb_put_padto() pads to 64 AND advances skb->len (unlike skb_padto), and
	 * COWs/expands the head if needed — so it is safe on the cloned/shared skbs
	 * a DSA conduit can receive, and the memcpy below reads a consistent len.
	 * Frees the skb on failure (-> drop_noskb). No-op when len >= 64. */
	if (skb_put_padto(skb, 64)) {
		TXCP(e, -1, "DROP: put_padto failed");
		goto drop_noskb;
	}
	len = skb->len;
	if (len > TM_BP_SIZE) {
		TXCP(e, -1, "DROP: len %u > BP_SIZE %u", len, TM_BP_SIZE);
		goto drop;
	}
	TXCP(e, 2, "size_ok len=%u (skb->len was %u)", len, skb->len);

	spin_lock_irqsave(&e->tm_tx_lock, flags);

	/* [txflowctrl 2026-07-04] Ring-occupancy gate (stock
	 * pon_tm_get_next_txdesc): reclaim on demand once half-full; if the
	 * ring is still full, REFUSE the enqueue — stop the conduit queue
	 * (backpressures the DSA user ports through the qdisc) and drop the
	 * skb exactly like stock (TCP regenerates; the HW engine keeps
	 * draining sanely). NEVER overwrite a descriptor the HW still owns —
	 * that overrun was the sustained-download wedge (torn descs → 64B
	 * latch → engine halt → BMU leak → global RX halt, reboot-only). */
	if (e->sw_tx_pending > TM_SW_TX_RECLAIM_THRESH)
		zx_sw_tx_reclaim_locked(e);
	if (e->sw_tx_pending > zx_sw_tx_full_thresh()) {
		e->sw_tx_full_drops++;
		if (!netif_queue_stopped(ndev)) {
			netif_stop_queue(ndev);
			e->sw_tx_queue_stops++;
		}
		spin_unlock_irqrestore(&e->tm_tx_lock, flags);
		TXCP(e, -1, "DROP: TX ring full (pending=%u)", e->sw_tx_pending);
		goto drop;
	}

	bp = zx_bmu_alloc_bp(e);
	if (bp == U32_MAX || bp >= TM_BPPE_POOL_SIZE) {
		spin_unlock_irqrestore(&e->tm_tx_lock, flags);
		/* First failure: emit ONE clean diagnostic via kernel printk */
		if (e->tm_tx_dropped == 0) {
			pr_debug("[ZXETH] BMU alloc FAIL #1: 8000=%#x 8014=%#x 800c=%#x 8048=%#x 8058=%#x 8080=%#x 8090=%#x\n",
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
	 * RX path confirms this (BPDUMP shows zeros at +0..15, frame at +16).
	 * TX must mirror it: place frame at bp_buf+16 so the wire format
	 * matches.
	 */
	memset(bp_buf, 0, 16);                  /* zero the HW prefix area */
	memcpy(bp_buf + 16, skb->data, len);    /* frame goes at +16 */
	TXCP(e, 3, "BMU alloc OK: bp=%u bp_buf=%p, copied %u bytes from skb (frame at +16)",
	     bp, bp_buf, len);

	/* [txflowctrl 2026-07-04] Stock TX desc format (Ghidra decomp of
	 * pon_tm_net_tx + pon_tm_data_raw_send, see tasks/00.10.02.re-stock-kmods/
	 * findings/tx_path_stock_decomp.md), written the stock way:
	 *   word0: byte0 = 0xc9 (CPU/source marker), bytes2-3 = egress-port hint
	 *          ((port+0x28)&0x3f)<<4 — THE verified egress fix (a 0 hint gave
	 *          SOPC no destination → DSCH dropped every frame).
	 *   word1: 0x00010000 (desc[6]=1) | bp low7 <<1 in byte 7.
	 *   word2: bp high bits | len<<9 | 0x21<<24 (byte11 = VALID 0x01 | fmt
	 *          0x20 — stock does desc[11] = (desc[11]&1) | 0x20).
	 *   word3: len encoding in bytes 12-13, bytes 14-15 = 0.
	 * NO memset (the old memset-then-rebuild destroyed live descriptors when
	 * the ring overran and tore frames to 64 B if HW fetched mid-rebuild);
	 * every byte is written explicitly, and word2 — carrying the VALID
	 * byte — is written LAST, after a barrier, so the HW can never fetch a
	 * half-built descriptor. The occupancy gate above guarantees this slot
	 * was already consumed by the HW. Nothing touches the desc post-kick.
	 */
	desc = (u8 *)e->txdesc_cpu + e->tx_head * TM_TX_DESC_SIZE;
	{
		u32 w3 = (len < 64) ? ((len & 0x3fff) | 0x100)
				    : ((len & 0x3fff) << 2);

		*(__le32 *)(desc + 0)  = cpu_to_le32(0xc9 |
					 ((u32)(((eg + 0x28) & 0x3f) << 4) << 16));
		*(__le32 *)(desc + 4)  = cpu_to_le32(0x00010000 |
					 ((u32)((bp & 0x7f) << 1) << 24));
		*(__le32 *)(desc + 12) = cpu_to_le32(w3);
		dma_wmb();	/* all fields visible before VALID */
		*(__le32 *)(desc + 8)  = cpu_to_le32(((bp >> 7) & 0x7f) |
						     ((len & 0x3fff) << 9) |
						     (0x21U << 24));
	}

	dma_wmb();
	TXCP(e, 5, "desc[0..15]=%02x %02x %02x %02x  %02x %02x %02x %02x  %02x %02x %02x %02x  %02x %02x %02x %02x",
	     desc[0], desc[1], desc[2], desc[3], desc[4], desc[5], desc[6], desc[7],
	     desc[8], desc[9], desc[10], desc[11], desc[12], desc[13], desc[14], desc[15]);
	e->tx_head = (e->tx_head + 1) & (TM_TX_RING_SIZE - 1);
	TXCP(e, 6, "tx_head=%u (post-incr); about to kick TM[0x10054]=1", e->tx_head);

	/* [txflowctrl] SINGLE kick, stock soft_insert_tx_1desc dir0: the UP
	 * engine alone consumes this ring. The legacy dual-kick (two engines
	 * fetching ONE shared ring) double-emitted frames and is the
	 * documented HW-deadlock topology — kept only behind zx_tx_dualkick=1
	 * (which also re-shares the DN base, see zx_tm_dma_init). */
	tm_write(e, TM_REG_DMA_TX_UP_KICK, 1);	/* upstream kick */
	if (zx_tx_dualkick)
		tm_write(e, 0x10064, 1);	/* legacy downstream kick */

	e->sw_tx_pending++;
	if (e->sw_tx_pending > e->sw_tx_pending_max)
		e->sw_tx_pending_max = e->sw_tx_pending;
	TXCP(e, 7, "kick done; sw_tx_pending=%u", e->sw_tx_pending);

	e->tm_tx_count++;
	ndev->stats.tx_packets++;
	ndev->stats.tx_bytes += len;
	spin_unlock_irqrestore(&e->tm_tx_lock, flags);

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
	/* [phase6/ft] DSA delegates TC_SETUP_FT (nf_flow_table/conntrack
	 * offload) to the conduit master's ndo_setup_tc. sw IS the conduit
	 * (lan1..lanN -> lower_sw), so the FT flow_block binds here. */
	.ndo_setup_tc	= zx_eth_setup_tc,
};

static int zx_sw_netdev_create(struct zx_eth *e)
{
	struct net_device *ndev;
	/* Match stock CPU MAC slot[0] (programmed by replay from stock_eth.bin).
	 * Switch HW routes frames with this dst MAC → CPU port.
	 */
	u8 mac[ETH_ALEN] = { 0xf4, 0xf6, 0x47, 0x0f, 0x42, 0x64 };
	int err;

	ndev = alloc_etherdev(sizeof(struct zx_eth *));
	if (!ndev)
		return -ENOMEM;
	SET_NETDEV_DEV(ndev, e->dev);
	/* [P1 conduit/DSA] Bind the `sw` netdev to a UNIQUE DT node so a DSA
	 * switch can select it as conduit unambiguously via
	 * `ethernet = <&cpu_conduit>`. of_find_net_device_by_node() ->
	 * of_dev_node_match() walks dev->parent, so binding sw to the shared eth
	 * controller node would also match idm0/idm1 (same parent) and FIFO
	 * registration order would pick idm0 (registered first) as the conduit
	 * instead of sw — breaking the tagger datapath, whose hooks live in the
	 * sw netdev path. Anchoring sw to the eth node's `conduit` child (which
	 * idm0/idm1's parent-walk never reaches) makes sw the only match. Fall
	 * back to the eth node itself when the child is absent (older DTBs). */
	{
		struct device_node *cnp =
			of_get_child_by_name(e->dev->of_node, "conduit");

		device_set_node(&ndev->dev,
				cnp ? of_fwnode_handle(cnp)
				    : dev_fwnode(e->dev));
	}
	*(struct zx_eth **)netdev_priv(ndev) = e;
	ndev->netdev_ops = &zx_sw_netdev_ops;
	/* [phase6/ft] NETIF_F_HW_TC gates tc_can_offload()/flow_block binding
	 * on the conduit so nf_flow_table (TC_SETUP_FT) delegation offloads
	 * here. Mirror the idm%d user netdevs (MTK pattern). */
	ndev->hw_features |= NETIF_F_HW_TC;
	ndev->features |= NETIF_F_HW_TC;
	ndev->watchdog_timeo = msecs_to_jiffies(5000);
	snprintf(ndev->name, IFNAMSIZ, "sw");
	eth_hw_addr_set(ndev, mac);

	/* Stock prints `netif_napi_add() called with weight 512 on device pon`
	 * in `pon tm init` (boot UART capture). Default mainline
	 * NAPI_POLL_WEIGHT=64 is 8x lower than stock and bottlenecks bursty RX.
	 */
	netif_napi_add_weight(ndev, &e->tm_napi, zx_tm_napi_poll, 512);

	err = register_netdev(ndev);
	if (err) {
		netif_napi_del(&e->tm_napi);
		free_netdev(ndev);
		return err;
	}
	e->sw_dev = ndev;
	netdev_dbg(ndev, "sw registered (MAC %pM)\n", ndev->dev_addr);

	/* Stock kotrace captures exactly one sbrg_add_mactable call with
	 * port=1; we mirror it. Don't seed port=6 here — it caused flood /
	 * DUPs in trial runs.
	 */
	{
		int rc = zx_fdb_add(e, ndev->dev_addr, 0, 1);

		netdev_dbg(ndev, "HW FDB seed (PP_BRG_RAM): self MAC port=1 rc=%d\n", rc);
		/* Unknown-unicast FWD bitmap is configured in zx_pp_brg_init
		 * (PP[0x8340] = 0x015555ff, CPU-only) to match stock LIVE. An
		 * earlier attempt with bitmap 0x20 gave tx_done=0 / 100% loss,
		 * but 0x20 was the WRONG bit: stock's port-5→internal-0 remap
		 * makes the CPU bit 0x01, not 0x20. See fdb_learning_enable_re.md Q6.
		 */
	}
	return 0;
}

/* ============================================================
 *   Probe / remove
 * ============================================================
 */

/* ============================================================
 *   Debugfs: /sys/kernel/debug/zx_eth/{stats,mem}
 *   stats = pretty-printed driver counters + key reg snapshot
 *   mem   = binary dump of the 2MB NPP region (for diff vs stock)
 * ============================================================
 */
static struct dentry *zx_debugfs_root;

static int zx_stats_show(struct seq_file *s, void *_unused)
{
	struct zx_eth *e = s->private;
	u32 i;

	seq_puts(s, "=== Driver counters ===\n");
	seq_printf(s, "tm_irq_count      = %u\n", e->tm_irq_count);
	seq_printf(s, "tm_napi_count     = %u\n", e->tm_napi_count);
	seq_printf(s, "tm_rx_count       = %u\n", e->tm_rx_count);
	/* Per-ingress-port RX-to-CPU histogram. slot[i] = ingress_port+1, so
	 * port0=slot1 .. port7=slot8 (slot0 = invalid/-1). Shows WHICH ingress
	 * port's frames actually reached the CPU — the live per-port discriminator
	 * for the multi-port (port1) gap. */
	seq_printf(s, "rx_per_ingress port0..7 = %u %u %u %u %u %u %u %u  (invalid=%u)\n",
		   e->tm_rx_per_ingress[1], e->tm_rx_per_ingress[2],
		   e->tm_rx_per_ingress[3], e->tm_rx_per_ingress[4],
		   e->tm_rx_per_ingress[5], e->tm_rx_per_ingress[6],
		   e->tm_rx_per_ingress[7], e->tm_rx_per_ingress[8],
		   e->tm_rx_per_ingress[0]);
	seq_printf(s, "tm_rx_loopback_drops = %u\n", e->tm_rx_loopback_drops);
	/* [Stage-3 WiFi observation] IDM RX ssid histogram — additive, decoded
	 * from IDM RX desc word1 bits16..19 in zx_idm_poll. All-zero today (ports
	 * 6/7 carry no MT7915 traffic yet); becomes the empirical RX-ssid ground
	 * truth once an AP client sends through the fabric. */
	seq_printf(s, "idm_rx_count      = %u\n", e->idm_rx_count);
	seq_printf(s, "tm_rx_fabric      = %u (wifi_dispatched=%u nobind=%u noparse=%u)\n",
		   e->tm_rx_fabric, e->tm_wifi_rx_dispatched,
		   e->tm_wifi_rx_nobind, e->tm_wifi_rx_noparse);
	seq_printf(s, "idm_rx_per_ssid 0..7 = %u %u %u %u %u %u %u %u  (ssid_invalid=%u)\n",
		   e->idm_rx_per_ssid[0], e->idm_rx_per_ssid[1],
		   e->idm_rx_per_ssid[2], e->idm_rx_per_ssid[3],
		   e->idm_rx_per_ssid[4], e->idm_rx_per_ssid[5],
		   e->idm_rx_per_ssid[6], e->idm_rx_per_ssid[7],
		   e->idm_rx_ssid_invalid);
	seq_printf(s, "tm_tx_count       = %u\n", e->tm_tx_count);
	seq_printf(s, "tm_tx_dropped     = %u\n", e->tm_tx_dropped);
	seq_printf(s, "tm_bmu_free_ok    = %u\n", e->tm_bmu_free_ok);
	seq_printf(s, "tm_bmu_free_fail  = %u\n", e->tm_bmu_free_fail);
	seq_printf(s, "bmu_free_credit   = %u\n", e->bmu_free_credit);
	seq_printf(s, "tx_head           = %u\n", e->tx_head);
	seq_printf(s, "sw_tx_pending     = %u (max %u, reclaimed %u)\n",
		   e->sw_tx_pending, e->sw_tx_pending_max, e->sw_tx_reclaimed);
	seq_printf(s, "sw_tx_full_drops  = %u (queue_stops %u)\n",
		   e->sw_tx_full_drops, e->sw_tx_queue_stops);
	/* [H5 fix] FT PM-write readback-verify accounting (finding H5). ok
	 * counts every readback-confirmed install-path PM commit; regress.py
	 * pm_write_verify asserts this advances by 4 per install (proving the
	 * verify path ran), and fail should always be 0 on healthy silicon. */
	seq_printf(s, "ft_pm_verify      = ok=%llu retry=%llu fail=%llu\n",
		   e->ft_pm_verify_ok, e->ft_pm_verify_retry, e->ft_pm_verify_fail);
	seq_printf(s, "BMU_ALLOC_RESULT  = 0x%08x\n", tm_read(e, TM_REG_BMU_ALLOC_RESULT));
	seq_printf(s, "BMU_ALLOC_CTRL    = 0x%08x\n", tm_read(e, TM_REG_BMU_ALLOC_CTRL));
	seq_printf(s, "TM[0x10054] TX kick  = 0x%08x\n", tm_read(e, TM_REG_DMA_TX_UP_KICK));
	/* [txflowctrl] TM[0x10058]/[0x10068] are CLEAR-ON-READ and owned by
	 * zx_sw_tx_reclaim_locked — no raw reads here. */
	seq_printf(s, "rx_idx            = %u\n", e->rx_idx);
	seq_printf(s, "tx_idx / tx_done  = %u / %u  pending=%d\n",
		   e->tx_idx, e->tx_done, atomic_read(&e->tx_pending));
	seq_puts(s, "rx_head[0..7]     = ");
	for (i = 0; i < 8; i++)
		seq_printf(s, "%u ", e->rx_head[i]);
	seq_puts(s, "\n");

	if (e->rxdesc_cpu) {
		const u32 *d = (const u32 *)e->rxdesc_cpu;
		u32 first_nz_off = 0xFFFFFFFF, nz_count = 0;

		for (i = 0; i < (0x40000/4); i++) {
			if (d[i] != (0xDEAD0000u | (u32)i)) {
				if (first_nz_off == 0xFFFFFFFF)
					first_nz_off = i*4;
				nz_count++;
			}
		}
		seq_printf(s, "rxdesc DIFF from canaries: %u words changed, first at offset 0x%x\n",
			   nz_count, first_nz_off);
		if (first_nz_off != 0xFFFFFFFF) {
			u32 base = first_nz_off / 4;

			seq_puts(s, "  bytes near first diff: ");
			for (i = 0; i < 8 && (base+i)*4 < 0x40000; i++)
				seq_printf(s, "[+0x%x]=0x%08x ", (base+i)*4, d[base+i]);
			seq_puts(s, "\n");
		}
	}
	if (e->bp_cpu) {
		const u32 *bp = (const u32 *)e->bp_cpu;
		u32 nz = 0;

		for (i = 0; i < (524288 / 4); i++)
			if (bp[i])
				nz++;
		seq_printf(s, "bp area: %u non-zero words (size 524288B)\n", nz);
	}
	if (e->bp_cpu) {
		const u32 *bp = (const u32 *)e->bp_cpu;

		seq_puts(s, "bp[bppe=0] (first 64B of BP buffer 0): ");
		for (i = 0; i < 16; i++)
			seq_printf(s, "%08x ", bp[i]);
		seq_puts(s, "\n");
	}
	seq_printf(s, "Verify TM[0xF0] now = 0x%08x (expected rxdesc_dma=%pad)\n",
		   tm_read(e, 0xF0), &e->rxdesc_dma);

	seq_puts(s, "\n=== TOPCRM (clock control) — stock should match ===\n");
	if (e->topcrm) {
		seq_printf(s, "TOPCRM[0x004] = 0x%08x  (stock=0x000001fb)\n", readl(e->topcrm + 0x004));
		seq_printf(s, "TOPCRM[0x008] = 0x%08x  (stock=0x1ff7ffff)\n", readl(e->topcrm + 0x008));
		seq_printf(s, "TOPCRM[0x00c] = 0x%08x  (stock=0x005179e0)\n", readl(e->topcrm + 0x00c));
		seq_printf(s, "TOPCRM[0x010] = 0x%08x  (stock=0x0000b114)\n", readl(e->topcrm + 0x010));
		seq_printf(s, "TOPCRM[0x014] = 0x%08x  (stock=0xcffffbf7)\n", readl(e->topcrm + 0x014));
		seq_printf(s, "TOPCRM[0x048] = 0x%08x  (stock=0x0ffedfff)\n", readl(e->topcrm + 0x048));
		seq_printf(s, "TOPCRM[0x04c] = 0x%08x  (stock=0x0003cfff)\n", readl(e->topcrm + 0x04c));
	}

	seq_puts(s, "\n=== TM regs ===\n");
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
	/* [txflowctrl] DESC_CNT_UP/DN low16 are CLEAR-ON-READ and owned by
	 * zx_sw_tx_reclaim_locked — report the driver occupancy instead. */
	seq_printf(s, "sw_tx_pending (in-flight TX descs) = %u (max %u)\n",
		   e->sw_tx_pending, e->sw_tx_pending_max);
	seq_printf(s, "TM[0x10030] DMA_TIMEOUT     = 0x%08x\n", tm_read(e, TM_REG_DMA_TIMEOUT));
	seq_puts(s, "\n=== Per-queue RX desc counts (TM[0x10100+q*4]) ===\n");
	for (i = 0; i < 8; i++) {
		u32 v = tm_read(e, 0x10100 + i * 4);

		seq_printf(s, "  q[%d] TM[0x%05x] = 0x%08x  (low16=avail, high16=??)\n",
			   i, 0x10100 + i * 4, v);
	}

	seq_puts(s, "\n=== PP regs ===\n");
	seq_printf(s, "PP[0x2c] CPU_FWD            = 0x%08x  (stock=0x00000106)\n",
		   readl(e->base + PP_OFF + PP_REG_CPU_FWD));
	seq_printf(s, "PP[0x04]                    = 0x%08x  (stock=0x02abfc8d)\n", readl(e->base + PP_OFF + 0x04));
	seq_printf(s, "PP[0x24]                    = 0x%08x  (stock=0x00000106)\n", readl(e->base + PP_OFF + 0x24));
	seq_printf(s, "PP[0x28]                    = 0x%08x  (stock=0x01070104)\n", readl(e->base + PP_OFF + 0x28));
	seq_printf(s, "PP[0x30]                    = 0x%08x  (stock=0x00000101)\n", readl(e->base + PP_OFF + 0x30));
	seq_printf(s, "PP[0x34]                    = 0x%08x  (stock=0x00010001)\n", readl(e->base + PP_OFF + 0x34));
	seq_printf(s, "PP[0x3c]                    = 0x%08x  (stock=0x00000106)\n", readl(e->base + PP_OFF + 0x3c));
	seq_printf(s, "PP[0x40]                    = 0x%08x  (stock=0x01030101)\n", readl(e->base + PP_OFF + 0x40));

	seq_puts(s, "\n=== IDM regs ===\n");
	seq_printf(s, "IDM[0x8000] CTRL            = 0x%08x\n", readl(e->base + IDM_REG_CONTROL));
	seq_printf(s, "IDM[0x8020] IRQ_STATUS      = 0x%08x\n", readl(e->base + IDM_REG_IRQ_STATUS));
	seq_printf(s, "IDM[0x8024] IRQ_MASK        = 0x%08x\n", readl(e->base + IDM_REG_IRQ_MASK));
	seq_printf(s, "IDM[0x8044] TX_STATUS       = 0x%08x\n", readl(e->base + IDM_REG_TX_STATUS));
	seq_printf(s, "IDM[0x804C] RX_PENDING      = 0x%08x  (low16=count, stock reads here)\n",
		   readl(e->base + 0x804C));
	seq_printf(s, "IDM[0x8004] TX_DESC_BASE    = 0x%08x\n", readl(e->base + 0x8004));
	seq_printf(s, "IDM[0x8008] RX_DESC_BASE    = 0x%08x\n", readl(e->base + 0x8008));

	seq_puts(s, "\n=== Per-port MAC[i] @ (i+1)*0x40000, first 64 bytes ===\n");
	for (i = 0; i < 5; i++) {
		u32 base = (i + 1) * MAC_STRIDE;
		u32 ctrl = readl(e->base + base + MAC_REG_CONTROL);
		u32 mask = readl(e->base + base + MAC_REG_IRQ_MASK);
		u32 en   = readl(e->base + base + MAC_REG_ENABLE);

		seq_printf(s, "MAC[%u] @0x%05x ctrl=%08x mask=%08x en=%08x\n",
			   i, base, ctrl, mask, en);
	}

	/* PHY link state — read BMSR (reg 1) + LPA (reg 5) + 1000T STATUS
	 * (reg 0xA) for each GePHY on the DT phandle list. BMSR bit 2 =
	 * Link Status (1 = up); bit 5 = Auto-Neg complete (1 = done).
	 */
	{
		struct device_node *np = e->dev->of_node;
		int n = of_count_phandle_with_args(np, "zte,gephys", NULL);
		int p;

		seq_puts(s, "\n=== PHY link state ===\n");
		for (p = 0; p < n; p++) {
			struct device_node *phy_np;
			struct phy_device *phydev;
			int bmsr, lpa, t1000;

			phy_np = of_parse_phandle(np, "zte,gephys", p);
			if (!phy_np)
				continue;
			phydev = of_phy_find_device(phy_np);
			of_node_put(phy_np);
			if (!phydev) {
				seq_printf(s, "  PHY[%d] not found\n", p);
				continue;
			}
			bmsr = phy_read(phydev, MII_BMSR);
			lpa  = phy_read(phydev, MII_LPA);
			t1000 = phy_read(phydev, MII_STAT1000);
			seq_printf(s, "  PHY[%d] %s BMSR=0x%04x link=%d an_done=%d  LPA=0x%04x  STAT1000=0x%04x\n",
				   p, phydev_name(phydev), bmsr & 0xffff,
				   !!(bmsr & BMSR_LSTATUS),
				   !!(bmsr & BMSR_ANEGCOMPLETE),
				   lpa & 0xffff, t1000 & 0xffff);
			put_device(&phydev->mdio.dev);
		}
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

	if (*ppos >= REGION)
		return 0;
	if (*ppos + count > REGION)
		count = REGION - *ppos;
	{
		void *tmp = kmalloc(count, GFP_KERNEL);

		if (!tmp)
			return -ENOMEM;
		memcpy_fromio(tmp, e->base + *ppos, count);
		if (copy_to_user(ubuf, tmp, count)) {
			kfree(tmp);
			return -EFAULT;
		}
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

/* regdump: hex-TEXT dump of forwarding-relevant register windows, one
 * "<phys> <value>" line per u32 (phys = 0x921c0000 + e->base offset).
 * Robust over the glitchy UART (a corrupt line is detectable/discardable,
 * unlike the raw binary `mem` file). Diff vs regs/stock_eth_2mib.txt.
 */
static const struct { u32 off, len; } zx_regdump_wins[] = {
	{ 0x000100, 0x040 },	/* TM IRQ / queue-enable */
	{ 0x008000, 0x0e0 },	/* TM BMU */
	{ 0x00c000, 0x120 },	/* TM QMG / CLA handoff */
	{ 0x010000, 0x120 },	/* TM DMA / per-queue */
	{ 0x040000, 0x040 },	/* MAC0 ctrl */
	{ 0x080000, 0x040 },	/* MAC1 ctrl */
	{ 0x0c0000, 0x040 },	/* MAC2 ctrl (host port) */
	{ 0x100000, 0x040 },	/* MAC3 ctrl */
	{ 0x140000, 0x040 },	/* MAC4 ctrl */
	{ 0x1c0000, 0x060 },	/* PP ctrl */
	{ 0x1c8000, 0x700 },	/* PP_BRG: flood/lookup/isolate/FDB/VLAN */
};

static int zx_regdump_show(struct seq_file *s, void *_unused)
{
	struct zx_eth *e = s->private;
	size_t i;
	u32 o;

	for (i = 0; i < ARRAY_SIZE(zx_regdump_wins); i++) {
		u32 base = zx_regdump_wins[i].off;
		u32 len  = zx_regdump_wins[i].len;

		for (o = 0; o < len; o += 4)
			seq_printf(s, "%08x %08x\n",
				   0x921c0000u + base + o,
				   readl(e->base + base + o));
	}
	return 0;
}

static int zx_regdump_open(struct inode *inode, struct file *f)
{
	return single_open(f, zx_regdump_show, inode->i_private);
}

static const struct file_operations zx_regdump_fops = {
	.owner   = THIS_MODULE,
	.open    = zx_regdump_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = single_release,
};

/* cladump: dump the CLA ram7 (trap-queue) CPU-queue id for every (ptype, port)
 * via the indirect read. Lets us diff the per-port trap config of a FAILING port
 * (e.g. port1/jack2: MAC RX climbs but tm_rx_count=0) against a WORKING port
 * (port0/2/3) on the same boot — the per-port plain registers are identical, so
 * if the trap RAM differs that's the bit. Port 5 = CPU (skipped). */
static int zx_cladump_show(struct seq_file *s, void *_unused)
{
	struct zx_eth *e = s->private;
	u32 data[17];
	int i, port;
	static const u8 cols[7] = { 0, 1, 2, 3, 4, 6, 7 };

	seq_puts(s, "CLA ram7 trap-queue qid per (ptype,bank):\n");
	seq_puts(s, "ptype  p0 p1 p2 p3 p4 p6 p7 base\n");
	/* [ft_lock] the CLA indirect engine's CMD/DONE/DATA registers are
	 * shared across ALL ram_ids — a concurrent FT/DSA install writing
	 * ram2-6 could otherwise interleave with this read-only ram7 walk and
	 * make it print a wrong (other-ram_id) value. Named explicitly in
	 * qa_static_bughunt_2026-07-04.md C1's calling-context list. */
	mutex_lock(&zx_hwlock);
	for (i = 0; i < ZX_DEF_PTL_PKT_MAP_COUNT; i++) {
		u8 ptype = zx_def_ptl_pkt_map[i].ptype;

		seq_printf(s, "0x%02x  ", ptype);
		for (port = 0; port < 7; port++) {
			u32 addr = ptype | zx_pkt_port_addr_offset[cols[port]];

			if (zx_cla_read_entry(e, 7, addr, data) == 0)
				seq_printf(s, " %02x", data[0] & 0xff);
			else
				seq_puts(s, " ??");
		}
		/* base bank (dir-1 / port-5 slot, offset 0) — now written by the
		 * dual-bank replay; surfaced here for the on-device re-steer
		 * oracle (wifi_stage3_qmg_queue5_consumer_re §6 check #2). */
		if (zx_cla_read_entry(e, 7, ptype | zx_pkt_port_addr_offset[5],
				      data) == 0)
			seq_printf(s, " %02x", data[0] & 0xff);
		else
			seq_puts(s, " ??");
		seq_puts(s, "\n");
	}
	mutex_unlock(&zx_hwlock);
	return 0;
}

static int zx_cladump_open(struct inode *inode, struct file *f)
{
	return single_open(f, zx_cladump_show, inode->i_private);
}

static const struct file_operations zx_cladump_fops = {
	.owner   = THIS_MODULE,
	.open    = zx_cladump_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = single_release,
};

/* clapeek: ad-hoc indirect read of any CLA entry. Write "<ram_id> <addr>" (hex),
 * the 17 data words are printed to the kernel log (like poke's readback). */
static ssize_t zx_clapeek_write(struct file *f, const char __user *ubuf,
				size_t count, loff_t *ppos)
{
	struct zx_eth *e = f->private_data;
	char buf[64];
	u32 ram_id, addr, data[17];
	int rc;

	if (count == 0 || count >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = 0;
	if (sscanf(buf, "%x %x", &ram_id, &addr) != 2)
		return -EINVAL;
	/* [ft_lock] serialize against the FT/DSA offload paths + sibling
	 * debugfs pokes touching the same CLA indirect engine. */
	mutex_lock(&zx_hwlock);
	rc = zx_cla_read_entry(e, ram_id & 0xff, addr, data);
	mutex_unlock(&zx_hwlock);
	if (rc) {
		pr_info("[ZXETH] clapeek ram%u addr%#x: err %d\n", ram_id, addr, rc);
		return rc;
	}
	pr_info("[ZXETH] clapeek ram%u addr%#x: %08x %08x %08x %08x %08x %08x %08x %08x %08x\n",
		ram_id, addr, data[0], data[1], data[2], data[3], data[4],
		data[5], data[6], data[7], data[8]);
	pr_info("[ZXETH]   clapeek+:           %08x %08x %08x %08x %08x %08x %08x %08x\n",
		data[9], data[10], data[11], data[12], data[13], data[14],
		data[15], data[16]);
	return count;
}

static const struct file_operations zx_clapeek_fops = {
	.owner = THIS_MODULE,
	.open  = simple_open,
	.write = zx_clapeek_write,
	.llseek = default_llseek,
};

/* clawrite: ad-hoc indirect WRITE of any CLA entry (Phase 6 HW flow-offload).
 * Write "<ram_id> <addr> <w0> <w1> ... <w16>" (all hex) — installs the 17-word
 * entry via zx_cla_write_entry, then reads it back to the log to confirm. Used
 * to replay stock-captured hardfast hash entries (findings/phase6_stock_hardfast_
 * trace.md) into ram2 and measure whether the chip then HW-forwards (hw_trap flat).
 * Fewer than 17 words → the rest are zero-filled. */
static ssize_t zx_clawrite_write(struct file *f, const char __user *ubuf,
				 size_t count, loff_t *ppos)
{
	struct zx_eth *e = f->private_data;
	char buf[320];
	u32 ram_id = 0, addr = 0, data[17] = {0};
	int n = 0, pos = 0, consumed, rc;
	char *p;

	if (count == 0 || count >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = 0;
	if (sscanf(buf, "%x %x%n", &ram_id, &addr, &pos) != 2)
		return -EINVAL;
	p = buf + pos;
	while (n < 17 && sscanf(p, "%x%n", &data[n], &consumed) == 1) {
		n++;
		p += consumed;
	}
	/* ALL CLA indirect rams use the CMD-first/descending protocol (verified from
	 * decomp): ram0 = cla_set_extra_index_table (CMD-first, 5 words desc, tm.c:2650);
	 * ram1 = rule TCAM (17 words); ram2-6 = hash (15 words). The old plain data-first
	 * path (zx_cla_write_entry) did NOT persist ram0 — that's why the ram0 extract
	 * write silently failed. ram7 (cpu_queue) still uses the plain path. */
	/* [ft_lock] serialize the whole write+readback sequence against the
	 * FT/DSA offload paths + sibling debugfs pokes on the CLA engine. */
	mutex_lock(&zx_hwlock);
	if (ram_id == 0)
		rc = zx_cla_write_hash(e, 0, addr, data, 5);
	else if (ram_id >= 1 && ram_id <= 6)
		rc = zx_cla_write_hash(e, ram_id & 0xff, addr, data,
				       (ram_id == 1) ? 17 : 15);
	else
		rc = zx_cla_write_entry(e, ram_id & 0xff, addr, data);
	pr_info("[ZXETH] clawrite ram%u addr%#x: %d words, rc=%d\n",
		ram_id, addr, n, rc);
	if (rc == 0 && zx_cla_read_entry(e, ram_id & 0xff, addr, data) == 0)
		pr_info("[ZXETH]   clawrite readback: %08x %08x %08x %08x %08x %08x %08x %08x %08x\n",
			data[0], data[1], data[2], data[3], data[4],
			data[5], data[6], data[7], data[8]);
	mutex_unlock(&zx_hwlock);
	return rc ? rc : count;
}

static const struct file_operations zx_clawrite_fops = {
	.owner = THIS_MODULE,
	.open  = simple_open,
	.write = zx_clawrite_write,
	.llseek = default_llseek,
};

/* fill520: write ONE ram2-hash entry (15 words) into ALL 520 hash buckets
 * (ram2[0..0xff] ram3[0..0x7f] ram4[0..0x3f] ram5[0..0x3f] ram6[0..7]) IN-KERNEL,
 * instantly — instead of 520 slow UART pokes. Phase 6 slot-sweep test accelerator.
 * Write "<w0> <w1> ... <w14>" (hex). Removes the slot-prediction dimension so a
 * routed flow that the FFE extract now classifies will match SOMEWHERE and HW-forward. */
static ssize_t zx_fill520_write(struct file *f, const char __user *ubuf,
				size_t count, loff_t *ppos)
{
	struct zx_eth *e = f->private_data;
	static const struct { u8 ram; u16 n; } banks[] = {
		{ 2, 0x100 }, { 3, 0x80 }, { 4, 0x40 }, { 5, 0x40 }, { 6, 8 },
	};
	char buf[320];
	u32 data[15] = {0};
	int n = 0, consumed, b, ok = 0;
	unsigned int a;
	char *p;

	if (count == 0 || count >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = 0;
	p = buf;
	while (n < 15 && sscanf(p, "%x%n", &data[n], &consumed) == 1) {
		n++;
		p += consumed;
	}
	/* [ft_lock] serialize this bulk 520-bucket write against the FT/DSA
	 * offload paths + sibling debugfs pokes on the CLA engine. */
	mutex_lock(&zx_hwlock);
	for (b = 0; b < ARRAY_SIZE(banks); b++)
		for (a = 0; a < banks[b].n; a++)
			if (zx_cla_write_hash(e, banks[b].ram, a, data, 15) == 0)
				ok++;
	mutex_unlock(&zx_hwlock);
	pr_info("[ZXETH] fill520: wrote entry (%d words) to %d/520 hash buckets\n",
		n, ok);
	return count;
}

static const struct file_operations zx_fill520_fops = {
	.owner = THIS_MODULE,
	.open  = simple_open,
	.write = zx_fill520_write,
	.llseek = default_llseek,
};

/* pmwrite: write a PM (packet-modify) RAM entry via the pp_pm indirect iface
 * (Phase 6 HW L3 forward). "<ram_id> <addr> <w0> ... <w7>" (hex). ram_id 1 = next-hop
 * (MAC rewrite), 0 = flow_info. Mirrors stock pp_pm_set_next_hop_ram_info / set_flow_info,
 * the per-flow L3 action mainline's replay never writes. <8 words → zero-filled. */
static ssize_t zx_pmwrite_write(struct file *f, const char __user *ubuf,
				size_t count, loff_t *ppos)
{
	struct zx_eth *e = f->private_data;
	char buf[160];
	u32 ram_id = 0, addr = 0, data[8] = {0};
	int n = 0, pos = 0, consumed, rc;
	char *p;

	if (count == 0 || count >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	buf[count] = 0;
	if (sscanf(buf, "%x %x%n", &ram_id, &addr, &pos) != 2)
		return -EINVAL;
	p = buf + pos;
	while (n < 8 && sscanf(p, "%x%n", &data[n], &consumed) == 1) {
		n++;
		p += consumed;
	}
	/* [ft_lock] serialize against the FT/DSA offload paths + sibling
	 * debugfs pokes on the PM engine. */
	mutex_lock(&zx_hwlock);
	rc = zx_pp_pm_write_entry(e, ram_id & 0xff, addr, data);
	mutex_unlock(&zx_hwlock);
	pr_info("[ZXETH] pmwrite pm-ram%u addr%#x: %d words, rc=%d\n",
		ram_id, addr, n, rc);
	return rc ? rc : count;
}

static const struct file_operations zx_pmwrite_fops = {
	.owner = THIS_MODULE,
	.open  = simple_open,
	.write = zx_pmwrite_write,
	.llseek = default_llseek,
};

/* extwrite: PM EXTERNAL flow_info table probe tool (debug/RE only).
 * The PM engine DMA-fetches per-flow flow_info from the DDR carve (see
 * zx_ft_ext_flow_write). This node writes/encodes/reads raw entries so the
 * engine's fetch INDEX + direction-table selection can be measured on silicon
 * (fill entries whose nat_sport ENCODES their own index -> the sport seen on
 * the wire IS the fetched index).
 *   w   <dir> <idx> <w0> <w1> <w2>          write one entry
 *   f   <dir> <start> <cnt> <w0> <w1> <w2>  fill range with the same entry
 *   enc <dir> <start> <cnt> <w0> <w1> <w2>  fill range, nat_sport := (dir<<15)|idx
 *   r   <dir> <idx>                          dump entry bytes to dmesg
 *   z                                        zero BOTH dir tables completely
 * All values hex except the cmd word. nat_sport packing (flow_info layout):
 * w0[31:18] = sport[13:0], w1[1:0] = sport[15:14]. */
static void zx_extwrite_one(struct zx_eth *e, u32 dir, u32 idx, const u32 fi[3])
{
	u8 fb[12], ent[16] = {0};
	int i;

	for (i = 0; i < 12; i++)
		fb[i] = (fi[i >> 2] >> (8 * (i & 3))) & 0xff;
	for (i = 0; i < 9; i++)
		ent[i] = fb[8 - i];
	memcpy_toio(e->pm_ext +
		    (dir ? ZX_PM_EXT_FLOW_DIR1 : ZX_PM_EXT_FLOW_DIR0) +
		    idx * 16, ent, 16);
}

static ssize_t zx_extwrite_write(struct file *f, const char __user *ubuf,
				 size_t count, loff_t *ppos)
{
	struct zx_eth *e = f->private_data;
	char buf[160], cmd[8] = "";
	u32 dir = 0, idx = 0, cnt = 0, w[3] = {0, 0, 0};
	u32 i;

	if (count == 0 || count >= sizeof(buf))
		return -EINVAL;
