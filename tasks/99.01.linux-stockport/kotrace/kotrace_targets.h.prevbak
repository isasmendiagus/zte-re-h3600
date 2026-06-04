/* FOCUSED ingress-trace target table (hand-written, NOT auto-generated).
 *
 * Built for tasks/99.01.linux-stockport — stock LAN->CPU ingress fn trace.
 * Goal: capture, at RUNTIME on the stock kernel, the per-port RX->CPU ingress
 * datapath + the per-port bring-up, to see what stock does for port1/jack2
 * that makes its ingress reach the CPU — the difference our mainline driver
 * misses (mainline: ports 0/2/3 deliver to CPU, port1 delivers 0; the drop is
 * in MAC->SPA, upstream of SPA rcv_uni, NOT the 0x19068 SOPC bridge which was
 * DISPROVEN on HW). Sibling of kotrace_targets_egress.h — same struct/format.
 *
 * Two halves:
 *   (A) per-port BRING-UP (plat) — the link-up serializer/bond + admit chain
 *       that makes a MAC's RX reach the SPA/fabric. Port number is arg0 scalar
 *       on every one of these (logged as a value, NOT deref'd).
 *   (B) per-port RX->CPU INGRESS path — the NAPI poll that drains the TM RX
 *       ring, stamps the ingress port into skb->cb (skb+0xb4), and the
 *       switch.ko demux that branches PER-PORT on that stamp to a CPU netdev.
 *
 * Each marker is UNIQUE so the dump can be read by eye; the recorded
 * func_addr (entry+20) is the authoritative identifier.
 *
 * To use: build kotrace with this header instead of the full one
 * (the build wrapper copies it over kotrace_targets.h).
 */
#ifndef KOTRACE_TARGETS_H
#define KOTRACE_TARGETS_H

#define KOTRACE_DEREF_CAP   64

struct trace_target_v2 {
	const char *name;
	u8 arg_kind;          /* bit i = arg i is pointer */
	u8 deref[4];          /* per-arg deref size (capped to KOTRACE_DEREF_CAP) */
	u8 n_args;            /* 0..4 useful args */
	char marker;          /* 1-char log marker (unique here) */
};

struct trace_module_v2 {
	const char                      *mod_name;
	const struct trace_target_v2    *targets;
	unsigned int                     n_targets;
};

/* === plat_zxylzb_9128S — (A) per-port bring-up + (B) RX poll (9 functions) === */
static const struct trace_target_v2 kt_plat_zxylzb_9128S_targets[] = {
	/* (A) BRING-UP — port = arg0 scalar (logical/raw-MAC index). */
	{ "switch_phy_int_check_part_5",      0x00, {0,0,0,0}, 1, 'L' },  /* runtime link-up driver: pon_reset->smac_init->cfg_sd->sopc_switch->enable (plat:2797) */
	{ "pon_reset",                        0x00, {0,0,0,0}, 1, 'P' },  /* arg0 = reset-bit MASK 1<<(port+6), NOT a port# (plat:7744) */
	{ "smac_init",                        0x00, {0,0,0,0}, 1, 'I' },  /* per-port MAC reg program: ctrl 0xbae003 etc (plat:2272) */
	{ "pon_npp_smac_config_speed_duplex", 0x00, {0,0,0,0}, 1, 'D' },  /* port<5 guard then _part_0 worker (plat:2957) */
	{ "smac_sopc_mode_switch",            0x00, {0,0,0,0}, 2, 'B' },  /* THE SOPC bridge: poll ready bit(port+5), set admit bit(port) @0x19068; arg1=duplex (plat:2290) */
	{ "pon_npp_smac_enable",              0x00, {0,0,0,0}, 1, 'E' },  /* port<5 guard then _part_3 -> MAC[port]+0 |= 3 (plat:3111) */
	{ "extphy_timer_func",                0x00, {0,0,0,0}, 0, 'X' },  /* periodic per-lan_up_port PHY poll, no args (plat:3137) */
	/* (B) INGRESS RX->CPU — NAPI poll handlers: (napi*, budget). */
	{ "pon_tm_net_poll",                  0x01, {64,0,0,0}, 2, 'N' },  /* drains TM RX ring; stamps ingress port skb+0xb4=(desc[6]>>3)-1; calls switch_skb_recv (plat:8562) */
	{ "idm_net_poll",                     0x01, {64,0,0,0}, 2, 'M' },  /* IDM/CPU-port RX ring poll twin (plat:4024) */
};
#define KT_PLAT_ZXYLZB_9128S_COUNT  (sizeof(kt_plat_zxylzb_9128S_targets)/sizeof(kt_plat_zxylzb_9128S_targets[0]))

/* === switch — (B) the per-port ingress demux + delivery leaf (3 functions) === */
static const struct trace_target_v2 kt_switch_targets[] = {
	{ "pdt_ethdrv_recv", 0x01, {64,0,0,0}, 1, 'r' },  /* THE per-port demux: reads skb+0xb4 ingress port, branches per-port (isolatemask/learnlimit) -> CPU netdev (switch:536) */
	{ "ethdrv_recv_fin", 0x03, {64,64,0,0}, 2, 'f' },  /* per-port delivery leaf: (skb, dev); eth_type_trans + netif_receive_skb (switch:504) */
	{ "ffe_receive_skb", 0x01, {64,0,0,0}, 2, 'F' },  /* SUSPECT: fast-fwd hook, called (skb,3) on every branch; body stripped in decomp (switch:13329) */
};
#define KT_SWITCH_COUNT  (sizeof(kt_switch_targets)/sizeof(kt_switch_targets[0]))

/* Master table — kotrace iterates this on module-load to splice probes. */
static const struct trace_module_v2 kt_modules[] = {
	{ "plat_zxylzb_9128S.ko", kt_plat_zxylzb_9128S_targets, KT_PLAT_ZXYLZB_9128S_COUNT },
	{ "switch.ko",            kt_switch_targets,            KT_SWITCH_COUNT },
};
#define KT_NUM_MODULES  (sizeof(kt_modules)/sizeof(kt_modules[0]))

/* Total tracable functions: 12 */
#endif /* KOTRACE_TARGETS_H */
