/* FOCUSED HFF (HW fast-forward) install-trace target table — Phase 6 Stage 2-0b.
 * Captures, on a real forwarded flow through stock, the exact CLA hardfast entry
 * + slot + the flow-descriptor -> entry mapping, so we can replicate it in the
 * mainline driver. See tasks/00.10.02.re-stock-kmods/findings/phase6_stage2_readiness.md.
 * The KEY probe is 'C' cla_set_hash_table(slot, entry) — slot in r0, the 17-word
 * entry in r1 (deref'd). Each marker unique; func_addr (entry+20) is authoritative.
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

/* === switch (1 function) === */
static const struct trace_target_v2 kt_switch_targets[] = {
	{ "hf_set_l3_entry",            0x01, {64,0,0,0},  1, 'H' },  /* HFF install entry (ptSession) */
};
#define KT_SWITCH_COUNT  (sizeof(kt_switch_targets)/sizeof(kt_switch_targets[0]))

/* === tm (5 functions) === */
static const struct trace_target_v2 kt_tm_targets[] = {
	{ "zte_api_fast_l3_session_add", 0x03, {64,64,0,0}, 2, 'A' }, /* ptFastL3Session, result */
	{ "tm_acl_fast_add_v4v6",        0x06, {0,64,64,0}, 4, 'V' }, /* dir, entry, handle, .., out */
	{ "tm_acl_get_fastHashRule",     0x0a, {0,64,0,64}, 4, 'R' }, /* .., flow-desc(r1), .., entry-out(r3) */
	{ "cla_set_hash_table",          0x02, {0,64,0,0},  2, 'C' }, /* slot(r0), 17-word ENTRY(r1) — KEY */
	{ "cla_set_indirect_rw_cmd",     0x04, {0,0,64,0},  3, 'I' }, /* rw(r0), idx(r1), data(r2) */
};
#define KT_TM_COUNT  (sizeof(kt_tm_targets)/sizeof(kt_tm_targets[0]))

/* Master table — kotrace iterates this on module-load to splice probes. */
static const struct trace_module_v2 kt_modules[] = {
	{ "switch.ko", kt_switch_targets, KT_SWITCH_COUNT },
	{ "tm.ko",     kt_tm_targets,     KT_TM_COUNT },
};
#define KT_NUM_MODULES  (sizeof(kt_modules)/sizeof(kt_modules[0]))

/* Total tracable functions: 6 */
#endif /* KOTRACE_TARGETS_H */
