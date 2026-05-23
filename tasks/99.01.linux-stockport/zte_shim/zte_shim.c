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

unsigned int g_sw_cap = 0;
EXPORT_SYMBOL(g_sw_cap);

int g_switch_debug_level = 0;
EXPORT_SYMBOL(g_switch_debug_level);

unsigned char WlanIndex2WlanIdmMap[16] = {0};
EXPORT_SYMBOL(WlanIndex2WlanIdmMap);

unsigned char IfName2WlanIdmMap[16] = {0};
EXPORT_SYMBOL(IfName2WlanIdmMap);

/* ============================================================
 * SECTION 2 — Functions (built into ZTE kernel)
 * ============================================================ */

/* __alloc_skbuff: stock's ffe_sk_buff.c FFE-pool allocator. We can't
 * easily emulate (would need BMU pool setup). For now return NULL so
 * plat takes its error path (plat checks `subs r4, r0, #0; beq error`). */
struct sk_buff *__alloc_skbuff(unsigned int size, gfp_t priority, int fclone, int node)
{
	(void)size; (void)priority; (void)fclone; (void)node;
	return NULL;
}
EXPORT_SYMBOL(__alloc_skbuff);

/* skb_recycle: removed from kernel post-3.9; stub returns NULL. */
struct sk_buff *skb_recycle(struct sk_buff *skb)
{
	return NULL;
}
EXPORT_SYMBOL(skb_recycle);

/* dma_cache_maint: old DMA API. 1=TO_DEVICE 2=FROM_DEVICE. wmb is safe. */
void dma_cache_maint(const void *start, size_t size, int direction)
{
	(void)start; (void)size; (void)direction;
	wmb();
}
EXPORT_SYMBOL(dma_cache_maint);

/* FFE — ZTE Fast Forwarding Engine, disabled */
int ffe_learn_skb(struct sk_buff *skb) { return 0; }
EXPORT_SYMBOL(ffe_learn_skb);
int ffe_receive_skb(struct sk_buff *skb) { return 0; }
EXPORT_SYMBOL(ffe_receive_skb);
int ffe_get_npu_enable(void) { return 0; }
EXPORT_SYMBOL(ffe_get_npu_enable);

int temp_ctrl_read(void) { return 45; }	/* fake 45°C */
EXPORT_SYMBOL(temp_ctrl_read);

int zte_get_pon_mode(void) { return 0x10; }	/* LAN-only */
EXPORT_SYMBOL(zte_get_pon_mode);

int zx_mdio_read(int port, int reg)
{
	return 0xffff;
}
EXPORT_SYMBOL(zx_mdio_read);

int zx_mdio_write(int port, int reg, int val)
{
	return 0;
}
EXPORT_SYMBOL(zx_mdio_write);

/* CSP — Customer Service Platform stubs */
int CspGetSwInfo(void *info) { if (info) memset(info, 0, 64); return 0; }
EXPORT_SYMBOL(CspGetSwInfo);

int CspGetPortInfo(int port, void *info) { if (info) memset(info, 0, 64); return 0; }
EXPORT_SYMBOL(CspGetPortInfo);

int CSPKernel_skb_SelectQueue(struct net_device *dev, struct sk_buff *skb) { return 0; }
EXPORT_SYMBOL(CSPKernel_skb_SelectQueue);

int Kernel_ASEND(int a, int b, int c, int d) { return 0; }
EXPORT_SYMBOL(Kernel_ASEND);

int LedActionSet(int led, int action) { return 0; }
EXPORT_SYMBOL(LedActionSet);

int npu_register_driver(void *drv) { return 0; }
EXPORT_SYMBOL(npu_register_driver);

int wlan_to_idm_map(int x) { return -1; }
EXPORT_SYMBOL(wlan_to_idm_map);

/* sw_public_*_func_reg — callback registration tables, accept any */
int sw_public_port_cfg_func_reg(void *p) { return 0; }
EXPORT_SYMBOL(sw_public_port_cfg_func_reg);
int sw_public_port_vlan_func_reg(void *p) { return 0; }
EXPORT_SYMBOL(sw_public_port_vlan_func_reg);
int sw_public_port_ratelimit_func_reg(void *p) { return 0; }
EXPORT_SYMBOL(sw_public_port_ratelimit_func_reg);
int sw_public_onu_other_func_reg(void *p) { return 0; }
EXPORT_SYMBOL(sw_public_onu_other_func_reg);
int sw_public_onu_qos_func_reg(void *p) { return 0; }
EXPORT_SYMBOL(sw_public_onu_qos_func_reg);
int sw_public_onu_mactable_func_reg(void *p) { return 0; }
EXPORT_SYMBOL(sw_public_onu_mactable_func_reg);
int sw_public_onu_statistics_func_reg(void *p) { return 0; }
EXPORT_SYMBOL(sw_public_onu_statistics_func_reg);

int fuc_table_node_clear(int x) { return 0; }
EXPORT_SYMBOL(fuc_table_node_clear);
int fuc_table_node_create(int x) { return 0; }
EXPORT_SYMBOL(fuc_table_node_create);

void hw_watchdog_reset(void) { /* silent */ }
EXPORT_SYMBOL(hw_watchdog_reset);

void *br_lookup_mfd(void *p1, void *p2) { return NULL; }
EXPORT_SYMBOL(br_lookup_mfd);

int register_bridge_notifier(struct notifier_block *nb) { return 0; }
EXPORT_SYMBOL(register_bridge_notifier);

static int __init zte_shim_init(void)
{
	SHIM_LOG("loaded — 40 truly-missing symbols (stripped from 50+, no duplicates)\n");
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
