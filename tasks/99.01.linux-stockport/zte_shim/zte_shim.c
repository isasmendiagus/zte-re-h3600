/*
 * zte_shim.ko - ZTE H3600 kernel symbol shim (TRIMMED edition)
 *
 * Provides ONLY symbols that are not in any stock .ko AND not in vanilla 4.1.25.
 * These ~40 symbols were originally built into ZTE's patched kernel proper.
 *
 * Verified via objdump -t on every stock .ko (plat, tm, switch, idmfdb):
 * any global/function that stock owns is REMOVED from shim to avoid the
 * duplicate-symbol crash (e.g. g_tm_init_flag is plat.ko's, shim'd 4-byte
 * stub previously shadowed plat's real ~32B struct and crashed idmfdb).
 *
 * Load order: zte_shim.ko FIRST, then zx_ponreg → plat → tm → switch → idmfdb.
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/skbuff.h>
#include <linux/spinlock.h>
#include <linux/netdevice.h>
#include <linux/notifier.h>

#define SHIM_LOG(fmt, ...) \
	printk(KERN_NOTICE "[zte_shim] " fmt, ##__VA_ARGS__)

/* Trace each stub call: function name + caller (resolved via kallsyms %pS).
 * Rate-limited to avoid flooding kmsg when called from a hot path. The
 * primary value is the FIRST call (proves wiring) and the caller name. */
#define SHIM_TRACE(fmt, ...) \
	printk_ratelimited(KERN_INFO "[shim] %s(" fmt ") <- %pS\n", \
		__func__, ##__VA_ARGS__, __builtin_return_address(0))

/* ============================================================
 * SECTION 1 — GLOBALS (built into ZTE kernel, not in any .ko)
 * ============================================================ */

unsigned long pdt_mem_size = 256UL * 1024 * 1024;	/* 256 MiB */
EXPORT_SYMBOL(pdt_mem_size);

unsigned int product_vid = 0x32;	/* H3600 VID */
EXPORT_SYMBOL(product_vid);

unsigned int u32_BP_SIZE = 2304;	/* matches stock TM[0xFC]=0x900 */
EXPORT_SYMBOL(u32_BP_SIZE);

unsigned int u32_BPPE_POOL_SIZE = 256;
EXPORT_SYMBOL(u32_BPPE_POOL_SIZE);

unsigned int u32_JUMBO_BP_SIZE = 10240;
EXPORT_SYMBOL(u32_JUMBO_BP_SIZE);

unsigned int u32_JUMBO_BPPE_POOL_SIZE = 32;
EXPORT_SYMBOL(u32_JUMBO_BPPE_POOL_SIZE);

unsigned int ZX_RESERVE_MEM_SIZE = 64;	/* MB */
EXPORT_SYMBOL(ZX_RESERVE_MEM_SIZE);

/* g_sw_cap: stock declares this as a 92-byte BSS variable
 * (c06adebc..c06adf18 in stock vmlinux) that's populated at runtime —
 * most likely a struct/table of function pointers. switch.ko emits
 * relocs at g_sw_cap+0x6c that, when our shim has only a 4-byte u32,
 * land in adjacent BSS and the CPU executes garbage → bad-syscall oops.
 * Defensive workaround: declare g_sw_cap as a 256-byte naked function
 * where every 4-byte slot is `bx lr`. Any direct branch to any offset
 * inside returns cleanly. Indirect callers that load a function pointer
 * from this region will still fault — when that happens we'll have to
 * populate real callbacks. Discovered 2026-05-26 stockport revival. */
asm(
    "    .global g_sw_cap\n"
    "    .type   g_sw_cap, %function\n"
    "    .align  2\n"
    "g_sw_cap:\n"
    "    .rept 64\n"
    "        bx lr\n"
    "    .endr\n"
    "    .size   g_sw_cap, . - g_sw_cap\n"
);
extern void g_sw_cap(void);
EXPORT_SYMBOL(g_sw_cap);

/* g_switch_debug_level: stock has this as T (text) at c06915dc — just a
 * u32 (=1) but located in the .text section, immediately followed by
 * SW_ops table at +4. switch.ko likely emits `bl g_switch_debug_level+0x1c`
 * style relocations to invoke functions in the following table. Same
 * defensive naked-function fix as g_sw_cap. */
asm(
    "    .global g_switch_debug_level\n"
    "    .type   g_switch_debug_level, %function\n"
    "    .align  2\n"
    "g_switch_debug_level:\n"
    "    .rept 64\n"
    "        bx lr\n"
    "    .endr\n"
    "    .size   g_switch_debug_level, . - g_switch_debug_level\n"
);
extern void g_switch_debug_level(void);
EXPORT_SYMBOL(g_switch_debug_level);

/* WlanIndex2WlanIdmMap: stock exports this as a FUNCTION at
 * c02ca5a0 (T). Disasm shows real prologue `str lr, [sp, #-4]!` then
 * MDIO/idm-lookup logic. We had it as a 16-byte array → callers branch
 * into BSS → bad syscall oops. Use a naked stub that returns -1 (no
 * mapping) so callers proceed via the "no wlan attached" path. */
int WlanIndex2WlanIdmMap(int wlan_idx)
{
    SHIM_TRACE("wlan_idx=%d", wlan_idx);
    return -1;
}
EXPORT_SYMBOL(WlanIndex2WlanIdmMap);

/* IfName2WlanIdmMap: stock exports as T (function) at c02ca720.
 * Same pattern as WlanIndex2WlanIdmMap — must be a function, not array. */
int IfName2WlanIdmMap(const char *ifname)
{
    SHIM_TRACE("ifname=%s", ifname ? ifname : "(null)");
    return -1;
}
EXPORT_SYMBOL(IfName2WlanIdmMap);

/* ============================================================
 * SECTION 2 — Functions (built into ZTE kernel)
 * ============================================================ */

/* __alloc_skbuff: stock's ffe_sk_buff.c FFE-pool allocator. We can't
 * easily emulate (would need BMU pool setup). For now return NULL so
 * plat takes its error path (plat checks `subs r4, r0, #0; beq error`). */
struct sk_buff *__alloc_skbuff(unsigned int size, gfp_t priority, int fclone, int node)
{
	SHIM_TRACE("size=%u prio=%x fclone=%d node=%d",
		size, priority, fclone, node);
	return NULL;
}
EXPORT_SYMBOL(__alloc_skbuff);

/* skb_recycle: removed from kernel post-3.9; stub returns NULL. */
struct sk_buff *skb_recycle(struct sk_buff *skb)
{
	SHIM_TRACE("skb=%p", skb);
	return NULL;
}
EXPORT_SYMBOL(skb_recycle);

/* dma_cache_maint: old DMA API. 1=TO_DEVICE 2=FROM_DEVICE. wmb is safe. */
void dma_cache_maint(const void *start, size_t size, int direction)
{
	/* called per-packet potentially — trace is ratelimited */
	SHIM_TRACE("addr=%p size=%zu dir=%d", start, size, direction);
	wmb();
}
EXPORT_SYMBOL(dma_cache_maint);

/* FFE — ZTE Fast Forwarding Engine, disabled */
int ffe_learn_skb(struct sk_buff *skb)   { SHIM_TRACE("skb=%p", skb); return 0; }
EXPORT_SYMBOL(ffe_learn_skb);
int ffe_receive_skb(struct sk_buff *skb) { SHIM_TRACE("skb=%p", skb); return 0; }
EXPORT_SYMBOL(ffe_receive_skb);
int ffe_get_npu_enable(void)             { SHIM_TRACE(""); return 0; }
EXPORT_SYMBOL(ffe_get_npu_enable);

int temp_ctrl_read(void) { SHIM_TRACE(""); return 45; }	/* fake 45°C */
EXPORT_SYMBOL(temp_ctrl_read);

int zte_get_pon_mode(void) { SHIM_TRACE(""); return 0x10; }	/* LAN-only */
EXPORT_SYMBOL(zte_get_pon_mode);

int zx_mdio_read(int port, int reg)
{
	SHIM_TRACE("port=%d reg=%d", port, reg);
	return 0xffff;
}
EXPORT_SYMBOL(zx_mdio_read);

int zx_mdio_write(int port, int reg, int val)
{
	SHIM_TRACE("port=%d reg=%d val=%#x", port, reg, val);
	return 0;
}
EXPORT_SYMBOL(zx_mdio_write);

/* CSP — board-info accessors. Stock kernel exports these from vmlinux
 * (CspGetBoardDesInfo @0xc0421c9c, CspGetPortInfo @0xc0421c74,
 * CspGetSwInfo @0xc0421cc4, CspGetSlicInfo @0xc0421cec). All take a
 * single (void **out) argument and write a sub-pointer into a global
 * board_info struct at fixed offsets. Recovered 2026-05-26 via
 * vmlinux-to-elf + objdump.
 *
 * We allocate a 1 KiB zeroed fake_board_info; switch.ko reads fields
 * like sw_info[+8] (num_ports) and port_info[+2] (port count). Both
 * being 0 takes the "no-op, no ports" code path which is harmless for
 * bring-up — we can populate sensible defaults once we reach that
 * stage. */
static u8 fake_board_info[1024] __aligned(8);

int CspGetBoardDesInfo(void **out)
{
	SHIM_TRACE("out=%p", out);
	if (out) *out = &fake_board_info[0x20];
	return 0;
}
EXPORT_SYMBOL(CspGetBoardDesInfo);

int CspGetPortInfo(void **out)
{
	SHIM_TRACE("out=%p", out);
	if (out) *out = &fake_board_info[0x68];
	return 0;
}
EXPORT_SYMBOL(CspGetPortInfo);

int CspGetSwInfo(void **out)
{
	SHIM_TRACE("out=%p", out);
	if (out) *out = &fake_board_info[0x80];
	return 0;
}
EXPORT_SYMBOL(CspGetSwInfo);

int CspGetSlicInfo(void **out)
{
	SHIM_TRACE("out=%p", out);
	if (out) *out = &fake_board_info[0xec];
	return 0;
}
EXPORT_SYMBOL(CspGetSlicInfo);

int CSPKernel_skb_SelectQueue(struct net_device *dev, struct sk_buff *skb)
{
	SHIM_TRACE("dev=%s skb=%p",
		dev ? dev->name : "(null)", skb);
	return 0;
}
EXPORT_SYMBOL(CSPKernel_skb_SelectQueue);

int Kernel_ASEND(int a, int b, int c, int d)
{
	SHIM_TRACE("%#x %#x %#x %#x", a, b, c, d);
	return 0;
}
EXPORT_SYMBOL(Kernel_ASEND);

int LedActionSet(int led, int action)
{
	SHIM_TRACE("led=%d action=%d", led, action);
	return 0;
}
EXPORT_SYMBOL(LedActionSet);

int npu_register_driver(void *drv)
{
	SHIM_TRACE("drv=%p", drv);
	return 0;
}
EXPORT_SYMBOL(npu_register_driver);

int wlan_to_idm_map(int x)
{
	SHIM_TRACE("x=%d", x);
	return -1;
}
EXPORT_SYMBOL(wlan_to_idm_map);

/* sw_public_*_func_reg — callback registration tables, accept any */
int sw_public_port_cfg_func_reg(void *p)        { SHIM_TRACE("p=%p", p); return 0; }
EXPORT_SYMBOL(sw_public_port_cfg_func_reg);
int sw_public_port_vlan_func_reg(void *p)       { SHIM_TRACE("p=%p", p); return 0; }
EXPORT_SYMBOL(sw_public_port_vlan_func_reg);
int sw_public_port_ratelimit_func_reg(void *p)  { SHIM_TRACE("p=%p", p); return 0; }
EXPORT_SYMBOL(sw_public_port_ratelimit_func_reg);
int sw_public_onu_other_func_reg(void *p)       { SHIM_TRACE("p=%p", p); return 0; }
EXPORT_SYMBOL(sw_public_onu_other_func_reg);
int sw_public_onu_qos_func_reg(void *p)         { SHIM_TRACE("p=%p", p); return 0; }
EXPORT_SYMBOL(sw_public_onu_qos_func_reg);
int sw_public_onu_mactable_func_reg(void *p)    { SHIM_TRACE("p=%p", p); return 0; }
EXPORT_SYMBOL(sw_public_onu_mactable_func_reg);
int sw_public_onu_statistics_func_reg(void *p)  { SHIM_TRACE("p=%p", p); return 0; }
EXPORT_SYMBOL(sw_public_onu_statistics_func_reg);

int fuc_table_node_clear(int x)  { SHIM_TRACE("x=%d", x); return 0; }
EXPORT_SYMBOL(fuc_table_node_clear);
int fuc_table_node_create(int x) { SHIM_TRACE("x=%d", x); return 0; }
EXPORT_SYMBOL(fuc_table_node_create);

void hw_watchdog_reset(void) { /* silent — too noisy, may be called per-tick */ }
EXPORT_SYMBOL(hw_watchdog_reset);

void *br_lookup_mfd(void *p1, void *p2)
{
	SHIM_TRACE("p1=%p p2=%p", p1, p2);
	return NULL;
}
EXPORT_SYMBOL(br_lookup_mfd);

int register_bridge_notifier(struct notifier_block *nb)
{
	SHIM_TRACE("nb=%p", nb);
	return 0;
}
EXPORT_SYMBOL(register_bridge_notifier);

static int __init zte_shim_init(void)
{
	/* Populate fake_board_info so switch.ko enters its netdev-creation
	 * loop. From sw_reg_set_onu_swcap disasm (switch.ko@0x3d3c-0x3d58):
	 *   r3 = CspGetSwInfo() = &fake_board_info[0x80]
	 *   r2 = *(u32 *)(r3 + 8)              ; offset 0x88 = num_ports
	 *   cmp r2, #8 ; bgt error             ; must be ≤8
	 *   r1 = CspGetPortInfo() = &fake_board_info[0x68]
	 *   r1 = *(u16 *)(r1 + 2)              ; offset 0x6a = port_count
	 *   cmp r1, #8 ; bls ok                ; must be ≤8
	 * Start with 1 of each (1 port total). switch.ko's loop will then
	 * dereference more fields per-port — those will surface via
	 * SHIM_TRACE as crashes or zeros we'll fill in next iteration. */
	*(u32 *)(fake_board_info + 0x88) = 1;	/* sw_info.num_ports */
	*(u16 *)(fake_board_info + 0x6a) = 1;	/* port_info.port_count */

	SHIM_LOG("loaded — 40 truly-missing symbols (stripped from 50+, no duplicates)\n");
	SHIM_LOG("board: num_ports=%u port_count=%u\n",
		 *(u32 *)(fake_board_info + 0x88),
		 *(u16 *)(fake_board_info + 0x6a));
	SHIM_LOG("globals: u32_BP_SIZE=%u pdt_mem_size=%lu ZX_RESERVE_MEM_SIZE=%u\n",
		 u32_BP_SIZE, pdt_mem_size, ZX_RESERVE_MEM_SIZE);
	return 0;
}

static void __exit zte_shim_exit(void) { SHIM_LOG("unloaded\n"); }

module_init(zte_shim_init);
module_exit(zte_shim_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ZTE H3600 kernel symbol shim (trimmed v0.2)");
MODULE_VERSION("0.2");
