/*
 * kotrace.ko — kernel-side loader-notifier + RAM patcher for the ZTE
 * H3600 RE work.
 *
 * Phase A2: register_module_notifier() + UART direct-write per event.
 * Phase A3 (this version): when MODULE_STATE_COMING fires for "switch",
 *   walk its kallsyms, find target init functions, allocate executable
 *   thunks via module_alloc(), patch each function's first instruction
 *   in RAM with `b thunk`. Each thunk writes a unique marker char to
 *   the PL011 UART so we see the live call order.
 *
 * Why a separate module instead of patching switch.ko on disk: see
 * tasks/00.01.eth-driver/findings/ko_splice_bugs.md — on-disk patching
 * via LIEF/ELF tripped multiple loader bugs that bricked the device
 * without panic messages. Doing the splice in RAM AFTER the kernel's
 * own loader runs avoids every one of those failure modes — we work
 * with FULLY RESOLVED runtime addresses, no relocations needed.
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/notifier.h>
#include <linux/io.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/elf.h>
#include <linux/kallsyms.h>
#include <linux/types.h>     /* u8, u16, u32 — needed by kotrace_targets.h */
#include "kotrace_targets.h" /* auto-generated v2 target table (~2157 fns) */
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <asm/cacheflush.h>

/* This kernel doesn't EXPORT_SYMBOL module_alloc / set_memory_rw /
 * set_memory_ro — they live in the kernel image but aren't visible to
 * modules at link time. We resolve them at module init via
 * kallsyms_lookup_name (which IS exported) and store function pointers. */
static void *(*p_module_alloc)(unsigned long);
static int   (*p_set_memory_rw)(unsigned long, int);
static int   (*p_set_memory_ro)(unsigned long, int);
static struct module *(*p_find_module)(const char *);

/* ZTE-shifted PL011 UART data register. Already initialized by U-Boot.
 * On this device the data register is at +0x04 (ZTE-shifted layout).
 * FR (flag register) is at +0x18 in stock PL011; we use the same offset
 * (verified by behaviour — kmsg2uart uses the same shift).
 *   FR bit 5 = TXFF (TX FIFO full); we busy-wait until it clears.
 */
#define PL011_BASE_PHYS  0x94404000UL
#define PL011_DR_OFFSET  0x04
#define PL011_FR_OFFSET  0x14    /* ZTE-shifted (stock PL011 has FR at 0x18) */
#define PL011_FR_TXFF    (1u << 5)
static void __iomem *pl011_base;

/* ---------- UART direct write (PL011) ---------- */

static void uart_putc(char c)
{
	int timeout;
	if (!pl011_base) return;
	/* Wait until TX FIFO has space. Cap to ~1M iters to avoid wedging
	 * if the FR offset is wrong on this chip variant. */
	timeout = 1000000;
	while ((readl(pl011_base + PL011_FR_OFFSET) & PL011_FR_TXFF)
	       && --timeout)
		cpu_relax();
	writel((unsigned char)c, pl011_base + PL011_DR_OFFSET);
}

static void uart_puts(const char *s)
{
	while (*s)
		uart_putc(*s++);
}

static void uart_puthex(unsigned long v)
{
	int i;
	uart_putc('0'); uart_putc('x');
	for (i = 28; i >= 0; i -= 4) {
		int n = (v >> i) & 0xf;
		uart_putc(n < 10 ? '0' + n : 'a' + n - 10);
	}
}

/* ---------- Phase 3b: trace ring buffer for r0-r3 args ---------- */

#define RING_ENTRIES      65536    /* 2 MiB — sized for full boot capture (cspd init storm = tens of thousands of fn calls). Mask needs 16 bits; thunk uses lsl#16/lsr#11 instead of lsl#18/lsr#13. */
#define RING_ENTRY_SIZE   32        /* must be power of 2; thunk uses lsl #5 */
#define RING_BYTES        (RING_ENTRIES * RING_ENTRY_SIZE)
#define RING_IDX_MASK     (RING_ENTRIES - 1)
/* Per-entry layout (32 bytes):
 *   off 0:  marker char (1B) + 3B pad
 *   off 4:  r0 (32-bit)
 *   off 8:  r1
 *   off 12: r2
 *   off 16: r3
 *   off 20..31: reserved (12B — could hold seq counter, lr, or timestamp)
 */
static u8  *ring_buf;
static u32  ring_idx;     /* monotonically incremented by thunks; we mask on read */

/* ---------- rmmod-safety: track every patch so exit() can reverse ---------- */
/* Without this, removing kotrace leaves dangling branches into freed thunk
 * memory — the next call into a previously-patched function jumps to garbage
 * and the device crashes. We record every successful patch and restore the
 * original first instruction at module-exit.
 *
 * Sized for the v2 set (~2200 fns); kmalloc'd in init. Per entry: 8B. */
#define MAX_PATCHES 2400
struct patch_record {
	unsigned long func_addr;   /* address whose first insn we replaced */
	u32           original;    /* the displaced insn (to restore on exit) */
};
static struct patch_record *patches;
static unsigned int          n_patches;

/* ---------- Phase A3 / Phase B-runtime: target functions + thunk codegen
 *
 * Phase B (2026-05-25): the hardcoded switch_targets[] + tm_targets[]
 * arrays below are LEGACY (~60 entries). The real target table now lives
 * in kotrace_targets.h — auto-generated from ARG_SIGNATURES.json by
 * tasks/00.10.02.re-stock-kmods/scripts/generate_kotrace_targets.py.
 *
 * kotrace_targets.h provides:
 *   - struct trace_target_v2 { name, arg_kind, deref[4], n_args, marker }
 *   - struct trace_module_v2 { mod_name, targets, n_targets }
 *   - kt_modules[KT_NUM_MODULES] master list (5 eth-related .ko, 2157 fns)
 *
 * The new v2 path is enabled by KOTRACE_USE_V2 (default ON). Smart-deref
 * via copy_from_kernel_nofault on pointer args is NOT yet wired into the
 * thunk (would require ARM-asm extension to call a C helper post-capture).
 * For now arg_kind/deref are recorded in the table but unused at trace
 * time. Future: extend thunk to call a C helper that derefs pointer args.
 *
 * To revert to legacy hardcoded mode, set #define KOTRACE_USE_V2 0.
 */
#define KOTRACE_USE_V2 1
/* Diagnostic mode: when set, kotrace_init does NOTHING beyond ioremap +
 * kallsyms_lookup + register_notifier — no walks, no patches. The notifier
 * callback also does nothing past the [ko:C/L name] print. Used to isolate
 * whether the boot-time hang is in kotrace's heavy init work (alloc /
 * walks / patches) or in module load itself.
 *
 * Set to 1 only when actively diagnosing the bake-in crash; default 0. */
#define KOTRACE_MINIMAL_BOOT 0

/* Module-load-time filters (all settable via insmod params, no recompile).
 *   patch_limit   = cap on total successful patches (0 = no limit)
 *   patch_modules = comma-separated whitelist of module names to patch
 *                   (empty = patch all in kt_modules[])
 *   patch_skip    = comma-separated function names to skip (across modules)
 * Examples:
 *   insmod kotrace.ko patch_modules=switch,tm
 *   insmod kotrace.ko patch_skip=pon_tm_timer_func,extphy_timer_func
 */
static unsigned int patch_limit = 0;
static char patch_modules[256] = "";
static char patch_skip[512]    = "";
/* patch_pct: per-module percentage cap (0-100). 100 = patch all targets
 * in each module that gets to patch_module(). 50 = first 50% only.
 * Combine with patch_limit (global cap) and patch_modules (whitelist)
 * for fine bisect. */
static unsigned int patch_pct  = 100;

/* patch_pct_per: per-module percentage overrides. CSV of name:pct pairs.
 * Modules listed override patch_pct; modules NOT listed use patch_pct.
 * Example: patch_pct_per=tm:0,switch:50,plat_zxylzb_9128S:100
 * (sets tm to 0, switch to 50%, plat to 100; idmfdb/mt7915/zx_ponreg get patch_pct). */
static char patch_pct_per[256] = "";

/* Look up the percentage for a given module name in patch_pct_per. Returns
 * -1 if not found (caller should fall back to global patch_pct). */
static int lookup_pct_for_module(const char *name)
{
	const char *p = patch_pct_per;
	size_t nlen = strlen(name);
	while (*p) {
		const char *colon = p;
		while (*colon && *colon != ':' && *colon != ',') colon++;
		if (*colon == ':' && (size_t)(colon - p) == nlen &&
		    memcmp(p, name, nlen) == 0) {
			/* parse decimal pct after the colon */
			int v = 0;
			const char *q = colon + 1;
			while (*q >= '0' && *q <= '9') v = v * 10 + (*q++ - '0');
			return v;
		}
		while (*p && *p != ',') p++;
		if (*p == ',') p++;
	}
	return -1;
}

/* EXPERIMENT 2026-05-26: HW watchdog timing probe. Before doing ANY
 * patching work, sleep N seconds (500 ms ticks with a heartbeat to
 * UART) so we can observe whether the SoC resets just from "boot ran
 * long" (HW WDT from cspstart, fed only by cspd post-pc&) or whether
 * the reset only happens AFTER we touch instructions in modules.
 *
 * insmod kotrace.ko wait_secs=20  → 20 s of [ko:wait i=NN] before patch
 * If we see N print "wait i=" lines then a Boot SPI NAND, HW WDT is
 * the culprit (timeout ≈ N*0.5 s).
 * If we get through wait_secs OK then patches still crash, it's
 * patches.  */
static unsigned int wait_secs = 0;
/* module_param(wait_secs,...) declared in the bottom param block */

/* EXPERIMENT (2026-05-26): kernel-timer watchdog feeder. Heavy thunk
 * activity during plat/tm/switch init wedges cpu1 long enough to
 * trip the soft-lockup detector (or possibly the HW watchdog, but
 * see findings/kotrace_init_capture.md — we observed silent SoC
 * resets between [ko:L switch] and U-Boot). This timer runs every
 * 50 ms and touches the per-cpu softlockup watchdog (resolved via
 * kallsyms because it's not EXPORT_SYMBOL'd here). Only helps with
 * the SOFTWARE detector; HW WDT (/dev/FeedDog) is fed by cspd from
 * userspace and isn't reachable cleanly from a kernel module. */
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/delay.h>
static void (*p_touch_all_softlockup_watchdogs)(void);
static void (*p_touch_softlockup_watchdog)(void);
static struct timer_list kotrace_wdt_timer;
static int  kotrace_wdt_enabled = 1;

static void kotrace_wdt_pet(unsigned long _)
{
	if (p_touch_all_softlockup_watchdogs)
		p_touch_all_softlockup_watchdogs();
	else if (p_touch_softlockup_watchdog)
		p_touch_softlockup_watchdog();
	mod_timer(&kotrace_wdt_timer, jiffies + msecs_to_jiffies(50));
}

/* Returns 1 if `name` is mentioned in `list` (comma-separated) OR if
 * list is empty (when default_yes=1) / never (default_yes=0). */
static int name_in_list(const char *name, const char *list, int default_when_empty)
{
	const char *p = list;
	size_t nlen = strlen(name);
	if (!*p) return default_when_empty;
	while (*p) {
		const char *q = p;
		while (*q && *q != ',') q++;
		if ((size_t)(q - p) == nlen && memcmp(p, name, nlen) == 0)
			return 1;
		p = (*q == ',') ? q + 1 : q;
	}
	return 0;
}

/* Legacy v1 struct kept for the hardcoded arrays below — only .name and
 * .marker are actually used by patch_module(). v2 struct (from header) is
 * field-compatible for those two fields, so patch_module() now accepts the
 * v2 type directly. */
struct trace_target {
	const char *name;
	char        marker;
};

struct trace_module {
	const char              *mod_name;
	const struct trace_target *targets;
	unsigned int             n_targets;
};

/* switch.ko top-level init functions (Phase 2 — already captured) */
static const struct trace_target switch_targets[] = {
	{ "chip_tm_init",         'C' },
	{ "sw_init_switch",       'S' },
	{ "sw_alarm_init",        'A' },
	{ "sw_init_wlan_ssid",    'W' },
	{ "ethdrv_port_dev_init", 'E' },
	/* Phase 4 RX-path debug — what stock does on each received packet */
	{ "pdt_ethdrv_recv",      '*' },
	{ "ethdrv_recv_fin",      '.' },
	{ "sw_set_trap_cpu_ip",   '~' },
	/* Phase 5: CPU queue ratelimit — silent-killer candidate.
	 * If stock sets a non-zero rate and we never call this, our CPU TX
	 * may be gated to 0 PPS at boot. Captures: (port, rate). */
	{ "sw_port_set_cpu_queue_ratelimit", '<' },
};

/* tm.ko functions to trace.
 * Phase 3: top-level zte_api_* called by chip_tm_init (markers uppercase
 *          + a few lowercase).
 * Phase 3c (drill-down): one layer deeper — the sub-callees from each
 *          zte_api_*, extracted via `objdump -d --disassemble=<name>`.
 *          The sub-callees are MORE LIKELY to be leaf functions that
 *          directly do `writel(reg, val)` — exactly what mainline needs. */
static const struct trace_target tm_targets[] = {
	/* Phase 3 — API surface */
	{ "tm_cla_outspace_cfg_get",            'g' },
	{ "tm_cla_outspace_cfg_set",            's' },
	{ "tm_protocol_pkt_limit_pps_set",      'l' },
	{ "zte_api_pp_global_init",             'P' },
	{ "zte_api_pp_set_cpu_queue_rate",      'q' },
	{ "zte_api_pp_set_pro_action",          'r' },
	{ "zte_api_pp_set_trap_queue",          't' },
	{ "zte_api_sw_global_init",             'G' },
	{ "zte_api_sw_port_init",               'p' },
	{ "zte_api_sw_port_set_port_isolatemask", 'i' },
	{ "zte_api_sw_set_port_brdcast",        'b' },
	{ "zte_api_sw_set_port_muticast",       'm' },
	{ "zte_api_sw_set_port_unicast",        'u' },
	{ "zte_api_sw_vlan_set_port_pvid",      'v' },
	{ "zte_api_sw_vlan_set_port_vlancfg",   'V' },

	/* Phase 3c — first drill-down layer (sub-callees) */
	/* sw_global_init internals */
	{ "sbrg_set_table_sel",                 'a' },
	{ "sbrg_set_hash_mode",                 'h' },
	{ "sbrg_set_hash_collision_pktdeal",    'k' },
	{ "sbrg_set_macaddr_exchange_md",       'x' },
	{ "sbrg_set_multicst_md",               'M' },
	{ "sbrg_set_multi_mac_hash_mode",       'H' },
	{ "sbrg_set_multi_mac_vlan_mode",       'N' },
	{ "tm_multivlan_mode_set",              'n' },
	{ "tm_tpid_vlu_select_get",             'T' },
	{ "tm_in_port_tpid_select_set",         'I' },
	{ "tm_mac_learn_mode_set",              'L' },
	{ "tm_mac_da_look_ena_set",             'D' },
	/* BISECT iter3 — octant1 of quarter2 RE-ENABLED */
	{ "zte_api_sw_other_set_onu_mtu",       'O' },
	{ "tm_port_pvid_set",                   'd' },
	{ "tm_port_isolate_set",                'Y' },
	{ "tm_port_brdcast_flood_ena_set",      'F' },
	/* BISECT iter4 — first 2 of octant2 RE-ENABLED */
	{ "tm_port_brdcast_fwd_ena_set",        'B' },
	{ "tm_port_protocol_pktdeal_set",       'K' },
	/* BISECT iter5 — enable pkt_limit_map only */
	{ "tm_protocol_pkt_limit_map_set",      'J' },
	/* PERMANENTLY DISABLED — patching this crashes chip_tm_init */
#if 0
	{ "tm_vlantable_add_set",               'X' },
#endif
	/* BISECT iter6 — re-enable original second half (21 funcs) */
	{ "tm_vlan_check_ena_set",              'Q' },
	{ "tm_port_unicast_act_set",            'U' },
	{ "tm_port_multicast_act_set",          'R' },
	/* cla + adm + flood/forward */
	{ "cla_set_outspace_cfg",               'o' },
	{ "cla_get_outspace_cfg",               'c' },
	{ "adm_set_policing_enable",            'e' },
	{ "adm_set_pass_pktcnt_persec",         'f' },
	{ "tm_port_dft_broadcst_vltrans_set",   'w' },
	{ "tm_port_dft_multicst_vltrans_set",   'y' },
	{ "tm_port_dft_unkunicst_vltrans_set",  'z' },
	{ "tm_port_pon_broadcast_floodport_set",'0' },
	{ "tm_port_pon_unicast_floodport_set",  '1' },
	{ "tm_port_unknwn_unicast_flood_set",   '2' },
	{ "tm_port_unknwn_unicast_fwd_set",     '3' },
	{ "tm_port_unknwn_multicast_flood_set", '4' },
	{ "tm_port_unknwn_multicast_fwd_set",   '5' },
	{ "tm_port_unknwn_multicast_floodport_set", '6' },
	{ "cla_set_dn_unknown_da_action_cfg",   '7' },
	{ "cla_set_extra_index_table",          '8' },
	{ "cla_get_extra_index_table",          '9' },
	{ "cla_set_mac_req_ctrl_config",        '!' },
	/* IRQ enable path — why does our mainline's tm-irq count stay at 0? */
	{ "sbrg_set_irq_en_mask",               '$' },

	/* Phase 5 — HW classifier + responder + FDB config (the "missing" cspd calls).
	 * These tell HW: "this is our IP, route ARP/ICMP to me / autorespond, populate
	 * the HW MAC table, set the CPU queue id, gate per-protocol CPU punt". Each
	 * marker captures (r0, r1, r2, r3) so we can see what cspd loads at boot. */
	{ "cla_set_local_ipv4_addr",            '+' },  /* (ipv4_addr) */
	{ "cla_set_local_ipv6_addr",            '-' },  /* (ipv6_addr*) */
	{ "cla_set_oth_l3_pkt_action_cfg",      '=' },  /* (act ∈ 0..3) */
	{ "cla_set_cpu_queue_id",               ':' },  /* (ram_addr, cpu_qid) */
	{ "dpa_set_protocol_cpu_pps_en",        ';' },  /* (en ∈ 0..1) */
	{ "dpa_set_protocol_pkt_aly_en",        '?' },  /* (en ∈ 0..1) */
	{ "spa_set_cpu_untag_pri",              '%' },  /* (port, pri) */
	{ "spa_set_cpu_untag_svid",             '&' },  /* (port, svid) */
	{ "sbrg_add_mactable",                  '>' },  /* (mac*, port) — HW FDB add */
	{ "sbrg_change_portmask",               '|' },  /* (mac_idx, portmask) — HW FDB update */

	/* Phase 3d ATTEMPTED but FAILED — patching tmOnuRegWrite et al.
	 * (374-call-sites leaf helpers) caused chip_tm_init to hang
	 * before reaching [ko:L switch]. Likely cause: per-call thunk
	 * overhead disrupted timing-sensitive register-write sequences,
	 * or stack pressure from deep nested patched-call chain. Phase 3c
	 * coverage (60 targets, no leaf) is the working state.
#if 0
	{ "tmOnuRegWrite",                      '@' },
	{ "tmOnuRegWriteNoCheck",               '#' },
	{ "tmOnuRegRead",                       '$' },
	{ "tmOnuRegReadNoCheck",                '%' },
#endif
	 */

	/* Phase 5 (2026-05-24): HW classifier / sbrg / spa / dpa config —
	 * the "missing init" that explains why ping bidi fails. These all
	 * live in tm.ko and are called from cspd at boot via exported APIs.
	 * Capturing args here tells us exactly what cspd loads, so we can
	 * replay it in our mainline driver's probe(). */
	{ "cla_set_local_ipv4_addr",            '+' },	/* HW IP — auto-ARP/ICMP responder */
	{ "cla_set_local_ipv6_addr",            '-' },
	{ "cla_set_oth_l3_pkt_action_cfg",      '=' },	/* unknown-L3 action (drop/fwd/cpu) */
	{ "cla_set_cpu_queue_id",               'Z' },	/* which qid is "the CPU queue" */
	{ "dpa_set_protocol_cpu_pps_en",        '&' },	/* gate: protocol→CPU enable */
	{ "dpa_set_protocol_pkt_aly_en",        '^' },	/* gate: HW protocol analysis */
	{ "spa_set_cpu_untag_pri",              '(' },	/* CPU port VLAN untag prio */
	{ "spa_set_cpu_untag_svid",             ')' },	/* CPU port VLAN untag SVID */
	{ "spa_set_enty_pktdeal_cfg",           '[' },	/* entry pkt-deal config */
	{ "sbrg_add_mactable",                  'S' },	/* HW FDB populate — CRÍTICO */
	{ "sbrg_change_portmask",               'C' },	/* per-MAC egress port mask */
};

static const struct trace_module trace_modules[] = {
	{ "switch", switch_targets, sizeof(switch_targets)/sizeof(switch_targets[0]) },
	{ "tm",     tm_targets,     sizeof(tm_targets)/sizeof(tm_targets[0])         },
};
#define NUM_TRACE_MODULES  (sizeof(trace_modules) / sizeof(trace_modules[0]))

/* Bookkeeping per patched function — kept just for diagnostic prints. */
struct thunk_info {
	unsigned long  func_addr;
	void          *thunk;
	u32            displaced;
	bool           patched;
};

/* ---------- ARM A32 codegen helpers ---------- */

/* Build an A32 "b <to>" instruction bytes, to be placed at `from`.
 *
 * Cortex-A9: B's runtime target = (PC at exec) + 8 + sign_extend(imm24<<2).
 * So encoded imm24 = ((to - (from + 8)) >> 2) & 0xffffff.
 * Range: ±32 MiB. Returns 0xffffffff on out-of-range (caller bails).
 */
static u32 arm_encode_b(unsigned long from, unsigned long to)
{
	s32 diff = (s32)((long)to - (long)(from + 8));
	if (diff & 3) return 0xffffffff;          /* not 4-aligned */
	diff >>= 2;
	if (diff < -0x800000 || diff >= 0x800000)
		return 0xffffffff;                    /* out of ±32MiB */
	return 0xea000000u | ((u32)diff & 0x00ffffff);
}

/* movw rD, #imm16        ARM encoding:  cond[31:28]=AL, 0011_0000,
 *   imm4[19:16] in bits 19:16, rD[15:12], imm12[11:0] in bits 11:0
 * Encoded: 0xE300_0000 | (imm16hi4 << 16) | (rD << 12) | imm16lo12
 */
static u32 arm_encode_movw(int rD, u16 imm16)
{
	return 0xe3000000u
		| (((u32)(imm16 >> 12) & 0xf) << 16)
		| (((u32)rD & 0xf) << 12)
		| ((u32)imm16 & 0xfff);
}

/* movt rD, #imm16 — same layout, opcode 0xE340_0000 */
static u32 arm_encode_movt(int rD, u16 imm16)
{
	return 0xe3400000u
		| (((u32)(imm16 >> 12) & 0xf) << 16)
		| (((u32)rD & 0xf) << 12)
		| ((u32)imm16 & 0xfff);
}

/* mov rD, #imm8 (rotated). For small imm we just use the 8-bit immediate
 * field, no rotation: opcode 0xE3A0_0000 | (rD << 12) | imm8.
 */
static u32 arm_encode_mov_imm8(int rD, u8 imm8)
{
	return 0xe3a00000u | (((u32)rD & 0xf) << 12) | (u32)imm8;
}

/* strb rS, [rN]           opcode 0xE5C?_?000  with rN in bits 19:16, rS in 15:12 */
static u32 arm_encode_strb_at(int rS, int rN)
{
	return 0xe5c00000u | (((u32)rN & 0xf) << 16) | (((u32)rS & 0xf) << 12);
}

#define INSN_PUSH_R0R1     0xe92d0003u  /* push {r0, r1} */
#define INSN_POP_R0R1      0xe8bd0003u  /* pop  {r0, r1} */
#define INSN_PUSH_R4_R7    0xe92d00f0u  /* push {r4, r5, r6, r7} */
#define INSN_POP_R4_R7     0xe8bd00f0u  /* pop  {r4, r5, r6, r7} */

#define THUNK_BYTES  96   /* 23 insns × 4 = 92, rounded up for alignment.
                           * Bumped from 72: we added (a) idx-masking insns
                           * to prevent OOB when ring wraps past 16k events,
                           * and (b) 3 insns to record func_addr at +20. */

/* ---------- Build thunk in newly-allocated executable memory ---------- */

/* Thunk layout (23 insns × 4 bytes = 92 bytes, alloc rounds to 96):
 *  +0   push {r4, r5, r6, r7}      save scratch (keeps SP 8-aligned)
 *  +4   movw r4, #LO(&ring_idx)
 *  +8   movt r4, #HI(&ring_idx)
 * +12   ldr  r5, [r4]               r5 = current idx
 * +16   add  r6, r5, #1
 * +20   str  r6, [r4]               idx++ (non-atomic; init is single-thread)
 * +24   mov  r5, r5, lsl #16        @ low 16 bits → bits 31..16
 * +28   mov  r5, r5, lsr #11        @ → bits 20..5 (= (idx & 0xFFFF) << 5)
 *                                   This masks idx to RING_IDX_MASK (RING_ENTRIES=65536)
 *                                   and pre-shifts by 5 (RING_ENTRY_SIZE=32).
 *                                   Two-insn alternative to `and r5,r5,#imm`
 *                                   because the mask 0xFFFF doesn't encode
 *                                   as an 8-bit-rotated ARM immediate.
 * +32   movw r4, #LO(ring_buf)
 * +36   movt r4, #HI(ring_buf)
 * +40   add  r4, r4, r5              r4 = ring_buf + entry_offset (no shift)
 * +44   mov  r5, #<marker>
 * +48   strb r5, [r4]                entry[0]    = marker
 * +52   str  r0, [r4, #4]            entry[4..7] = r0
 * +56   str  r1, [r4, #8]            entry[8..11]= r1
 * +60   str  r2, [r4, #12]           entry[12..15]= r2
 * +64   str  r3, [r4, #16]           entry[16..19]= r3
 * +68   movw r5, #LO(func_addr)
 * +72   movt r5, #HI(func_addr)
 * +76   str  r5, [r4, #20]           entry[20..23]= func_addr (NEW)
 * +80   pop  {r4, r5, r6, r7}        restore
 * +84   <displaced original insn>
 * +88   b    func+4
 *
 * Why masking matters: with v2 patching ~2k functions, post-boot the ring
 * cycles through 16k entries in seconds. The original thunk did
 * `add r4, r4, r5, lsl #5` with raw idx — for idx > 16383 it writes past
 * ring_buf, corrupting whatever sits after it (the 512KB allocation's
 * next neighbour in the page-allocator's slab/buddy). That's the most
 * plausible cause of the boot-hang we saw when v2 was baked into the
 * rootfs.
 *
 * Recording func_addr (NEW): solves the marker-ambiguity problem —
 * markers are derived from the function name's first char and thus
 * collide (e.g. 166 different 'p' functions in our v2 set). On dump,
 * userspace can resolve func_addr → symbol via the patching log.
 */
static int build_thunk(void *thunk_mem, u32 displaced, unsigned long func_addr,
		       char marker)
{
	u32 *p = thunk_mem;
	unsigned long thunk_addr = (unsigned long)thunk_mem;
	unsigned long idx_ptr    = (unsigned long)&ring_idx;
	unsigned long buf_ptr    = (unsigned long)ring_buf;
	u32 back_b;

	p[0]  = INSN_PUSH_R4_R7;
	p[1]  = arm_encode_movw(4, (u16)(idx_ptr & 0xffff));
	p[2]  = arm_encode_movt(4, (u16)(idx_ptr >> 16));
	p[3]  = 0xe5945000;   /* ldr r5, [r4] */
	p[4]  = 0xe2856001;   /* add r6, r5, #1 */
	p[5]  = 0xe5846000;   /* str r6, [r4] */
	p[6]  = 0xe1a05805;   /* mov r5, r5, lsl #16 */
	p[7]  = 0xe1a055a5;   /* mov r5, r5, lsr #11 */
	p[8]  = arm_encode_movw(4, (u16)(buf_ptr & 0xffff));
	p[9]  = arm_encode_movt(4, (u16)(buf_ptr >> 16));
	p[10] = 0xe0844005;   /* add r4, r4, r5 */
	p[11] = arm_encode_mov_imm8(5, (u8)marker);
	p[12] = arm_encode_strb_at(5, 4);   /* strb r5, [r4] */
	p[13] = 0xe5840004;   /* str r0, [r4, #4]  */
	p[14] = 0xe5841008;   /* str r1, [r4, #8]  */
	p[15] = 0xe584200c;   /* str r2, [r4, #12] */
	p[16] = 0xe5843010;   /* str r3, [r4, #16] */
	p[17] = arm_encode_movw(5, (u16)(func_addr & 0xffff));
	p[18] = arm_encode_movt(5, (u16)(func_addr >> 16));
	p[19] = 0xe5845014;   /* str r5, [r4, #20] */
	p[20] = INSN_POP_R4_R7;
	p[21] = displaced;
	back_b = arm_encode_b(thunk_addr + 88, func_addr + 4);
	if (back_b == 0xffffffff) {
		uart_puts("[ko: back-jump out of range]\n");
		return -ERANGE;
	}
	p[22] = back_b;

	flush_icache_range(thunk_addr, thunk_addr + THUNK_BYTES);
	return 0;
}

/* ---------- Find a function by name within a loaded module ---------- */

/* In 4.1.25 mod->kallsyms->{symtab,strtab,num_symtab} is the per-module
 * kallsyms (populated during load before MODULE_STATE_COMING fires).
 */
static unsigned long find_sym_in_mod(struct module *mod, const char *name)
{
	unsigned int i;
	struct mod_kallsyms *ks = mod->kallsyms;
	if (!ks) return 0;
	for (i = 0; i < ks->num_symtab; i++) {
		const char *n = ks->strtab + ks->symtab[i].st_name;
		if (n && strcmp(n, name) == 0)
			return (unsigned long)ks->symtab[i].st_value;
	}
	return 0;
}

/* ---------- Apply patches to switch.ko ---------- */

/* set_memory_rw / set_memory_ro: take a *page-aligned* virtual address
 * and a *page count*. On ARM 4.1.25 with vmalloc'd module memory.
 */
static int make_text_writable(unsigned long addr)
{
	return p_set_memory_rw(addr & PAGE_MASK, 1);
}
static int make_text_readonly(unsigned long addr)
{
	return p_set_memory_ro(addr & PAGE_MASK, 1);
}

/* THUNK_BYTES is now declared above (before build_thunk) */

/* Decide whether the function's first instruction can be safely
 * displaced (= moved into a thunk and replaced with a `b` to it).
 * Reject anything that:
 *   - is itself a branch (b/bl/bx/blx) — displacing breaks control flow
 *   - is PC-relative (uses PC as source register) — copying it changes
 *     its effective load address, computing the wrong runtime value
 *
 * For functions we reject here, the entry never gets patched; that
 * marker just won't fire. Better to silently miss it than to brick the
 * device with a corrupted call.
 */
static bool insn_is_displaceable(u32 insn)
{
	/* b <imm> */
	if ((insn & 0x0f000000) == 0x0a000000) return false;
	/* bl <imm> */
	if ((insn & 0x0f000000) == 0x0b000000) return false;
	/* bx Rm */
	if ((insn & 0x0ffffff0) == 0x012fff10) return false;
	/* blx Rm */
	if ((insn & 0x0ffffff0) == 0x012fff30) return false;
	/* Any insn with Rn = R15 = PC (catches ldr Rd,[pc,...], add Rd,pc,...,
	 * etc — all of which produce a runtime value that depends on the
	 * instruction's own location, so we can't move it.). The Rn field
	 * lives at bits [19:16] for most ARM encodings we care about here. */
	if ((insn & 0x000f0000) == 0x000f0000) return false;
	return true;
}

/* Phase B-runtime: now takes trace_target_v2 (compat with v1 via field
 * overlap — v2 has all the fields v1 used). The v2 struct also carries
 * arg_kind + deref sizes which a future thunk extension will consume. */
static void patch_module(struct module *mod,
			 const struct trace_target_v2 *targets,
			 unsigned int n_targets)
{
	void *thunks_mem;
	size_t total = n_targets * THUNK_BYTES;
	unsigned int i;
	unsigned int patched_this_call = 0;
	unsigned int max_for_this_module;

	/* Effective pct = per-module override from patch_pct_per if present,
	 * else global patch_pct (default 100). */
	{
		int per = lookup_pct_for_module(mod->name);
		unsigned int eff_pct = (per >= 0) ? (unsigned int)per : patch_pct;
		if (eff_pct > 100) eff_pct = 100;
		max_for_this_module = (eff_pct >= 100) ? n_targets
		                                       : (n_targets * eff_pct) / 100;
	}

	/* patch_modules whitelist: if non-empty, only patch listed modules. */
	if (!name_in_list(mod->name, patch_modules, 1)) {
		uart_puts("[ko: skip (patch_modules whitelist): ");
		uart_puts(mod->name);
		uart_puts("]\n");
		return;
	}

	uart_puts("[ko: '");
	uart_puts(mod->name);
	uart_puts("' found, allocating thunks: ");
	uart_puthex(total);
	uart_puts("]\n");

	thunks_mem = p_module_alloc(total);
	if (!thunks_mem) {
		uart_puts("[ko: module_alloc failed]\n");
		return;
	}

	for (i = 0; i < n_targets; i++) {
		unsigned long func = find_sym_in_mod(mod, targets[i].name);
		void *thunk = (char *)thunks_mem + i * THUNK_BYTES;
		u32 *func_p = (u32 *)func;
		u32 displaced, branch;

		if (patch_limit > 0 && n_patches >= patch_limit) {
			uart_puts("[ko: patch_limit (global) reached, skipping rest]\n");
			break;
		}
		if (patched_this_call >= max_for_this_module) {
			uart_puts("[ko: patch_pct cap reached for this module]\n");
			break;
		}
		if (name_in_list(targets[i].name, patch_skip, 0)) {
			uart_puts("[ko: skip (patch_skip): ");
			uart_puts(targets[i].name);
			uart_puts("]\n");
			continue;
		}
		uart_puts("[ko: target ");
		uart_puts(targets[i].name);
		uart_puts(" @ ");
		uart_puthex(func);
		uart_puts("]\n");

		if (!func) {
			uart_puts("  (skip: symbol not found)\n");
			continue;
		}

		displaced = *func_p;

		if (!insn_is_displaceable(displaced)) {
			uart_puts("  (skip: first insn not displaceable, opcode=");
			uart_puthex(displaced);
			uart_puts(")\n");
			continue;
		}

		if (build_thunk(thunk, displaced, func, targets[i].marker) < 0) {
			uart_puts("  (skip: thunk build failed)\n");
			continue;
		}

		branch = arm_encode_b(func, (unsigned long)thunk);
		if (branch == 0xffffffff) {
			uart_puts("  (skip: forward branch out of range)\n");
			continue;
		}

		if (make_text_writable(func) < 0) {
			uart_puts("  (skip: set_memory_rw failed)\n");
			continue;
		}
		*func_p = branch;
		flush_icache_range(func, func + 4);
		make_text_readonly(func);

		/* Record for rmmod-time restoration. Drop silently if full. */
		if (patches && n_patches < MAX_PATCHES) {
			patches[n_patches].func_addr = func;
			patches[n_patches].original  = displaced;
			n_patches++;
		}
		uart_puts("  patched OK\n");
		patched_this_call++;
	}
	uart_puts("[ko: SUMMARY '");
	uart_puts(mod->name);
	uart_puts("' patched=");
	uart_puthex(patched_this_call);
	uart_puts(" of=");
	uart_puthex(n_targets);
	uart_puts(" (total now=");
	uart_puthex(n_patches);
	uart_puts(")]\n");
}

static const struct trace_module *find_trace_module(const char *name)
{
	unsigned int i;
	for (i = 0; i < NUM_TRACE_MODULES; i++)
		if (strcmp(trace_modules[i].mod_name, name) == 0)
			return &trace_modules[i];
	return NULL;
}

/* v2 lookup — matches kt_modules[].mod_name against kernel's mod->name.
 * kt_modules entries end in ".ko" (e.g. "tm.ko") but mod->name is
 * stripped ("tm"). We strip the suffix at compare time. Returns NULL if
 * no match (caller can fallback to v1 or skip). */
static const struct trace_module_v2 *find_trace_module_v2(const char *name)
{
#if KOTRACE_USE_V2
	unsigned int i;
	size_t nlen = strlen(name);
	for (i = 0; i < KT_NUM_MODULES; i++) {
		const char *m = kt_modules[i].mod_name;
		size_t mlen = strlen(m);
		/* m ends in ".ko" → must be longer than nlen by exactly 3 and
		 * the prefix must match. */
		if (mlen == nlen + 3 &&
		    m[nlen] == '.' && m[nlen+1] == 'k' && m[nlen+2] == 'o' &&
		    memcmp(m, name, nlen) == 0)
			return &kt_modules[i];
	}
#endif
	return NULL;
}

/* ---------- Module-state notifier ---------- */

static const char marker_for_state[] = {
	[MODULE_STATE_LIVE]      = 'L',
	[MODULE_STATE_COMING]    = 'C',
	[MODULE_STATE_GOING]     = 'G',
	[MODULE_STATE_UNFORMED]  = 'U',
};

static int kotrace_notify(struct notifier_block *nb,
			  unsigned long action, void *data)
{
	struct module *mod = data;
	char marker = '?';

	if (action < ARRAY_SIZE(marker_for_state))
		marker = marker_for_state[action];

	uart_putc('[');
	uart_putc('k'); uart_putc('o'); uart_putc(':');
	uart_putc(marker);
	uart_putc(' ');
	if (mod && mod->name[0])
		uart_puts(mod->name);
	else
		uart_puts("(null)");
	uart_putc(']');
	uart_putc('\n');

#if KOTRACE_MINIMAL_BOOT
	/* Skip patching entirely in MINIMAL_BOOT mode — just observe loads. */
	return NOTIFY_DONE;
#endif

	if (mod && action == MODULE_STATE_COMING) {
		/* Try v2 (auto-generated, 2157 fns) first; fallback to v1
		 * (hardcoded ~60 fns) if v2 has no entry for this module. */
		const struct trace_module_v2 *tm2 = find_trace_module_v2(mod->name);
		if (tm2) {
			uart_puts("[ko: v2 lookup hit for '");
			uart_puts(mod->name);
			uart_puts("' (");
			uart_puthex(tm2->n_targets);
			uart_puts(" targets)]\n");
			patch_module(mod, tm2->targets, tm2->n_targets);
		} else {
			const struct trace_module *tm = find_trace_module(mod->name);
			if (tm) {
				/* v1 still hardcodes legacy 60-fn lists; we need
				 * a small inline adapter (v1->v2 has only .name +
				 * .marker overlap). Since v2 covers everything we
				 * care about now, this fallback is rarely hit. */
				uart_puts("[ko: v1 fallback for '");
				uart_puts(mod->name);
				uart_puts("' — consider regenerating kotrace_targets.h]\n");
			}
		}
	}

	return NOTIFY_DONE;
}

static struct notifier_block kotrace_nb = {
	.notifier_call = kotrace_notify,
	.priority      = 0,
};

/* ---------- Module init / exit ---------- */

/* ---------- procfs dump (text) ---------- */

/* /proc/kotrace_dump: read returns a TEXT representation of the ring buffer,
 * one line per captured call:
 *   <seq> <marker> <r0> <r1> <r2> <r3>
 * Why text and not binary: the stock device's userspace is very thin
 * (busybox sans od/xxd/dd-with-stdout-piping); `cat /proc/kotrace_dump`
 * gives a stream that SSH can carry without binary mangling.
 *
 * seq_file would be cleaner but its single_open buffer is small and we
 * may emit 200+ KB. Roll our own with a position cursor on entry index.
 */

static ssize_t kotrace_dump_read(struct file *f, char __user *buf,
				 size_t count, loff_t *ppos)
{
	/* *ppos encodes entry index. We emit one line per entry up to
	 * min(ring_idx, RING_ENTRIES). When ring_idx > RING_ENTRIES the
	 * ring has wrapped — we still emit RING_ENTRIES lines in slot
	 * order, prefixed with a comment line about wrap. */
	char line[96];
	int line_len;
	u32 idx_snap = ring_idx;     /* snapshot to avoid torn reads */
	u32 emitted = idx_snap;
	bool wrapped = false;
	loff_t entry;
	size_t written = 0;

	if (emitted > RING_ENTRIES) {
		emitted = RING_ENTRIES;
		wrapped = true;
	}

	/* If pos is past the last entry's last byte, we're done. The cursor
	 * just walks entries; we don't try to enforce byte-perfect resume
	 * across read() calls — userspace `cat` does big reads, so we emit
	 * as many full lines as fit and bump *ppos by line index. We use
	 * *ppos = entry_index + 1; pos==0 means "haven't emitted anything yet". */

	if (*ppos == 0 && wrapped) {
		line_len = snprintf(line, sizeof(line),
				    "# WRAPPED: ring_idx=%u > capacity=%u; %u oldest entries lost\n",
				    idx_snap, RING_ENTRIES, idx_snap - RING_ENTRIES);
		if (line_len > 0 && (size_t)line_len <= count) {
			if (copy_to_user(buf, line, line_len))
				return -EFAULT;
			written += line_len;
		}
	}

	entry = *ppos;
	while (entry < emitted) {
		const u8 *e = ring_buf + entry * RING_ENTRY_SIZE;
		u32 r0 = *(const u32 *)(e + 4);
		u32 r1 = *(const u32 *)(e + 8);
		u32 r2 = *(const u32 *)(e + 12);
		u32 r3 = *(const u32 *)(e + 16);
		u32 fn = *(const u32 *)(e + 20);   /* func_addr recorded by thunk */
		char marker = e[0] ? e[0] : '?';
		line_len = snprintf(line, sizeof(line),
				    "%5lld %c %08x  %08x %08x %08x %08x\n",
				    entry, marker, fn, r0, r1, r2, r3);
		if (line_len <= 0) break;
		if (written + line_len > count) break;
		if (copy_to_user(buf + written, line, line_len))
			return -EFAULT;
		written += line_len;
		entry++;
	}
	*ppos = entry;
	return written;
}

/* write() to /proc/kotrace_dump zeroes the ring and resets ring_idx.
 * Lets us snapshot a clean window:
 *     echo > /proc/kotrace_dump     # reset
 *     <do something>
 *     cat /proc/kotrace_dump        # delta
 * The reset path doesn't lock — we just zero ring_idx then memset.
 * On a busy device a thunk may fire mid-reset and write to slot N
 * where N was already memset; that's harmless (we'd read a half-filled
 * entry but the (entry, marker, regs) tuple still parses).
 */
static ssize_t kotrace_dump_write(struct file *f, const char __user *buf,
				  size_t count, loff_t *ppos)
{
	ring_idx = 0;
	memset(ring_buf, 0, RING_BYTES);
	return count;
}

static const struct file_operations kotrace_dump_fops = {
	.owner  = THIS_MODULE,
	.read   = kotrace_dump_read,
	.write  = kotrace_dump_write,
	.llseek = default_llseek,
};

static struct proc_dir_entry *proc_entry;

static int __init kotrace_init(void)
{
	pl011_base = ioremap(PL011_BASE_PHYS, 0x100);
	if (!pl011_base) {
		pr_err("kotrace: ioremap PL011 failed\n");
		return -ENOMEM;
	}
	uart_puts("[koINIT:A ioremap_ok]\n");

	ring_buf = kzalloc(RING_BYTES, GFP_KERNEL);
	if (!ring_buf) {
		uart_puts("[koINIT:RING_BUF_KZALLOC_FAIL]\n");
		iounmap(pl011_base);
		return -ENOMEM;
	}
	ring_idx = 0;
	uart_puts("[koINIT:B ring_buf_ok]\n");

	patches = kzalloc(sizeof(*patches) * MAX_PATCHES, GFP_KERNEL);
	if (!patches) {
		uart_puts("[koINIT:PATCHES_KZALLOC_FAIL]\n");
		kfree(ring_buf);
		iounmap(pl011_base);
		return -ENOMEM;
	}
	n_patches = 0;
	uart_puts("[koINIT:C patches_ok]\n");

	proc_entry = proc_create("kotrace_dump", 0666, NULL, &kotrace_dump_fops);
	if (!proc_entry) {
		uart_puts("[koINIT:PROC_CREATE_FAIL]\n");
		kfree(ring_buf);
		iounmap(pl011_base);
		return -ENOMEM;
	}
	uart_puts("[koINIT:D proc_ok]\n");

	/* Resolve the un-exported helpers via kallsyms. */
	p_module_alloc  = (void *)kallsyms_lookup_name("module_alloc");
	p_set_memory_rw = (void *)kallsyms_lookup_name("set_memory_rw");
	p_set_memory_ro = (void *)kallsyms_lookup_name("set_memory_ro");
	p_find_module   = (void *)kallsyms_lookup_name("find_module");
	if (!p_module_alloc || !p_set_memory_rw || !p_set_memory_ro ||
	    !p_find_module) {
		uart_puts("[ko: kallsyms_lookup_name failed for one of "
			  "module_alloc / set_memory_rw / set_memory_ro / "
			  "find_module]\n");
		iounmap(pl011_base);
		pl011_base = NULL;
		return -ENOENT;
	}
	uart_puts("[koINIT:E kallsyms_ok]\n");

	/* WDT timing probe (see wait_secs at top of file). */
	if (wait_secs > 0) {
		unsigned int ticks = wait_secs * 2;   /* 500ms each */
		unsigned int i;
		uart_puts("[ko: wait probe starting ");
		uart_puthex(ticks);
		uart_puts(" ticks @ 500ms]\n");
		for (i = 0; i < ticks; i++) {
			uart_puts("[ko:wait i=");
			uart_puthex(i);
			uart_puts("]\n");
			msleep(500);
		}
		uart_puts("[ko: wait probe DONE — survived ");
		uart_puthex(wait_secs);
		uart_puts("s]\n");
	}

	/* EXPERIMENT 2026-05-26: try to keep softlockup detector happy during
	 * heavy thunk activity. These two are best-effort (NULL is OK; we
	 * fall back from "all" to single-cpu, and if both are missing the
	 * timer just no-ops). */
	p_touch_all_softlockup_watchdogs =
		(void *)kallsyms_lookup_name("touch_all_softlockup_watchdogs");
	p_touch_softlockup_watchdog =
		(void *)kallsyms_lookup_name("touch_softlockup_watchdog");
	if (kotrace_wdt_enabled &&
	    (p_touch_all_softlockup_watchdogs || p_touch_softlockup_watchdog)) {
		setup_timer(&kotrace_wdt_timer, kotrace_wdt_pet, 0);
		mod_timer(&kotrace_wdt_timer, jiffies + msecs_to_jiffies(50));
		uart_puts("[ko: wdt-pet timer armed]\n");
	} else {
		uart_puts("[ko: wdt-pet skipped (disabled or symbols missing)]\n");
	}

	uart_puts("[ko: kotrace loaded]\n");
	register_module_notifier(&kotrace_nb);
	uart_puts("[koINIT:F notifier_registered]\n");

#if KOTRACE_MINIMAL_BOOT
	uart_puts("[koINIT:Z minimal-mode — skipping walks]\n");
	return 0;
#endif

	/* For each module we want to trace: if it's already loaded
	 * (e.g. cspd brought it up before us), patch it now — the
	 * COMING-notifier path won't fire for already-live modules.
	 * This lets us iterate without re-flashing the rootfs.
	 *
	 * Phase B-runtime: v2 first (full kt_modules[] table, ~2157 fns),
	 * fallback to v1 (trace_modules[]) only if v2 has no entry for the
	 * module — so we don't double-patch. */
	{
		unsigned int i;
#if KOTRACE_USE_V2
		for (i = 0; i < KT_NUM_MODULES; i++) {
			const struct trace_module_v2 *t = &kt_modules[i];
			/* kt_modules names end in ".ko"; mod->name is the stripped form. */
			char nm[64];
			size_t L = strlen(t->mod_name);
			uart_puts("[koINIT:G i="); uart_puthex(i); uart_puts("]\n");
			if (L >= 3 && L < sizeof(nm)) {
				memcpy(nm, t->mod_name, L - 3);
				nm[L - 3] = '\0';
			} else {
				continue;
			}
			{
				struct module *m = p_find_module(nm);
				if (m) {
					uart_puts("[ko: v2 '");
					uart_puts(nm);
					uart_puts("' already loaded — patching now (");
					uart_puthex(t->n_targets);
					uart_puts(" targets)]\n");
					patch_module(m, t->targets, t->n_targets);
				} else {
					uart_puts("[ko: v2 '");
					uart_puts(nm);
					uart_puts("' not yet loaded — will wait for COMING]\n");
				}
			}
		}
#else
		for (i = 0; i < NUM_TRACE_MODULES; i++) {
			const struct trace_module *t = &trace_modules[i];
			struct module *m = p_find_module(t->mod_name);
			if (m) {
				uart_puts("[ko: '");
				uart_puts(t->mod_name);
				uart_puts("' already loaded — patching now]\n");
				patch_module(m, t->targets, t->n_targets);
			} else {
				uart_puts("[ko: '");
				uart_puts(t->mod_name);
				uart_puts("' not yet loaded — will wait for COMING]\n");
			}
		}
#endif
	}
	uart_puts("[koINIT:Z init_done]\n");
	return 0;
}

static void __exit kotrace_exit(void)
{
	unsigned int i;

	/* Stop wdt-pet timer first so it can't fire while we're tearing down. */
	if (kotrace_wdt_enabled &&
	    (p_touch_all_softlockup_watchdogs || p_touch_softlockup_watchdog))
		del_timer_sync(&kotrace_wdt_timer);

	/* Stop receiving new module-load events FIRST so no new patches can
	 * sneak in mid-unpatch. */
	unregister_module_notifier(&kotrace_nb);

	/* Reverse every patch we made — restore the original first instruction.
	 * Until this runs, ALL patched functions branch into our thunk memory;
	 * after kotrace.ko is freed those thunks vanish and any call would
	 * jump to garbage → kernel oops / silent hang. */
	if (patches) {
		uart_puts("[ko: restoring ");
		uart_puthex(n_patches);
		uart_puts(" patched fns]\n");
		for (i = 0; i < n_patches; i++) {
			unsigned long addr = patches[i].func_addr;
			u32 *p = (u32 *)addr;
			if (make_text_writable(addr) < 0)
				continue;
			*p = patches[i].original;
			flush_icache_range(addr, addr + 4);
			make_text_readonly(addr);
		}
		uart_puts("[ko: unpatch done]\n");
		kfree(patches);
		patches = NULL;
		n_patches = 0;
	}

	if (proc_entry) {
		proc_remove(proc_entry);
		proc_entry = NULL;
	}
	uart_puts("[ko: kotrace unloaded]\n");
	if (pl011_base)
		iounmap(pl011_base);
	kfree(ring_buf);
	ring_buf = NULL;
}

module_init(kotrace_init);
module_exit(kotrace_exit);

module_param(patch_limit, uint, 0644);
MODULE_PARM_DESC(patch_limit, "Max patches applied (bisect aid); 0 = no limit");
module_param_string(patch_modules, patch_modules, sizeof(patch_modules), 0644);
MODULE_PARM_DESC(patch_modules, "CSV whitelist of modules to patch; empty = all");
module_param_string(patch_skip, patch_skip, sizeof(patch_skip), 0644);
MODULE_PARM_DESC(patch_skip, "CSV blacklist of function names to skip");
module_param(patch_pct, uint, 0644);
MODULE_PARM_DESC(patch_pct, "Per-module percentage cap (0-100). Default 100.");
module_param_string(patch_pct_per, patch_pct_per, sizeof(patch_pct_per), 0644);
MODULE_PARM_DESC(patch_pct_per, "CSV overrides per module: name:pct,name:pct,...");
module_param(wait_secs, uint, 0644);
MODULE_PARM_DESC(wait_secs, "EXPERIMENT: sleep N s with 500ms UART heartbeat BEFORE patching (0=off)");
module_param_named(wdt_pet, kotrace_wdt_enabled, int, 0644);
MODULE_PARM_DESC(wdt_pet, "EXPERIMENT: periodic softlockup-watchdog touch from kernel timer (1=on)");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZTE H3600 RE — agus@quecomere");
MODULE_DESCRIPTION("Module-notifier + RAM-patcher trace for switch.ko");
