/* FOCUSED egress-trace target table (hand-written, NOT auto-generated).
 *
 * Built for tasks/00.10.02.re-stock-kmods stock CPU->LAN egress fn trace.
 * Only the 8 candidate submit-path functions are patched, so the ring is
 * tiny, unambiguous, and we disturb the live switch/plat modules minimally.
 *
 * Each marker is UNIQUE so the dump can be read by eye; the recorded
 * func_addr (entry+20) is the authoritative identifier.
 *
 * To use: build kotrace with this header instead of the full 2157-fn one
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

/* === plat_zxylzb_9128S (6 functions) === */
static const struct trace_target_v2 kt_plat_zxylzb_9128S_targets[] = {
	{ "pon_tm_net_tx",            0x03, {64,64,0,0}, 2, 'T' },  /* dir-1 sw netdev xmit */
	{ "pon_tm_data_raw_send",     0x03, {64,15,0,0}, 3, 'R' },  /* BMU alloc + DN desc build */
	{ "soft_insert_tx_1desc",     0x00, {0,0,0,0},   2, '1' },  /* ring kick TM[0x10054/64] */
	{ "soft_insert_tx_multidesc", 0x01, {28,0,0,0},  1, 'M' },
	{ "dma_tx_free",              0x00, {0,0,0,0},   4, 'F' },  /* gauge 0x4c? */
	{ "dma_ram_get",              0x02, {0,32,0,0},  3, 'G' },  /* gauge 0x10014/18/1c? */
};
#define KT_PLAT_ZXYLZB_9128S_COUNT  (sizeof(kt_plat_zxylzb_9128S_targets)/sizeof(kt_plat_zxylzb_9128S_targets[0]))

/* === switch (2 functions) === */
static const struct trace_target_v2 kt_switch_targets[] = {
	{ "swport_dev_xmit_fin", 0x03, {64,64,0,0}, 4, 'X' },  /* eth3 copper-port xmit */
	{ "pdt_ethdrv_send",     0x03, {64,64,0,0}, 2, 'S' },  /* switch send leaf */
};
#define KT_SWITCH_COUNT  (sizeof(kt_switch_targets)/sizeof(kt_switch_targets[0]))

/* Master table — kotrace iterates this on module-load to splice probes. */
static const struct trace_module_v2 kt_modules[] = {
	{ "plat_zxylzb_9128S.ko", kt_plat_zxylzb_9128S_targets, KT_PLAT_ZXYLZB_9128S_COUNT },
	{ "switch.ko",            kt_switch_targets,            KT_SWITCH_COUNT },
};
#define KT_NUM_MODULES  (sizeof(kt_modules)/sizeof(kt_modules[0]))

/* Total tracable functions: 8 */
#endif /* KOTRACE_TARGETS_H */
