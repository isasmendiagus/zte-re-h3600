/*
 * netdev_probe.ko — print sizeof(struct net_device) + offsetof of every
 * pointer field, to find what field is at offset 0x1DC in our kernel.
 *
 * Why: stock plat-zxylzb_9128S.ko was compiled against ZTE's kernel
 * headers; its pon_tm_net_register() does `ldr r1, [r4, #0x1DC]` to read
 * some pointer field of struct net_device. In stock that's a valid
 * pointer; in our kernel offset 0x1DC lands on a different field → NULL
 * → BUG. Knowing OUR layout lets us decide between binary-patching
 * plat.ko or realigning our struct.
 *
 * Output goes via printk → captured on UART (DEBUG_LL).
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netdevice.h>

#define P(field) \
	printk(KERN_NOTICE "[netdev_probe] offsetof(net_device, " #field ") = %u (0x%X)\n", \
	       (unsigned)offsetof(struct net_device, field), \
	       (unsigned)offsetof(struct net_device, field))

#define P_AT(off) do { \
	if (offsetof(struct net_device, ml_priv) == (off)) \
		printk(KERN_NOTICE "[netdev_probe] AT_0x%X = ml_priv\n", (unsigned)(off)); \
} while (0)

static int __init np_init(void)
{
	printk(KERN_NOTICE "[netdev_probe] === sizeof(struct net_device) = %u (0x%X) ===\n",
	       (unsigned)sizeof(struct net_device),
	       (unsigned)sizeof(struct net_device));

	/* Candidate pointer fields plat might be reading at +0x1DC.
	 * Mostly the protocol-private pointer fields (one of them lands
	 * around the middle of net_device).  Skip conditional ones if
	 * they're not compiled in. */
	P(name);
#ifdef CONFIG_NET_NS
	P(nd_net);
#endif
	P(dev_addr);
	P(broadcast);
#ifdef CONFIG_RPS
	P(_rx);
#endif
	P(_tx);
	P(num_tx_queues);
	P(qdisc);
	P(tx_queue_len);
	P(watchdog_timeo);

	/* The protocol-specific pointer cluster — these are the most
	 * common candidates for plat's hardcoded offset. */
	P(ip_ptr);
#if IS_ENABLED(CONFIG_DECNET)
	P(dn_ptr);
#endif
	P(ip6_ptr);
#if IS_ENABLED(CONFIG_AX25)
	P(ax25_ptr);
#endif
	P(ieee80211_ptr);
#if IS_ENABLED(CONFIG_NET_DSA)
	P(dsa_ptr);
#endif
#if IS_ENABLED(CONFIG_TIPC)
	P(tipc_ptr);
#endif
	P(atalk_ptr);
#if IS_ENABLED(CONFIG_PHONET)
	P(phonet_ptr);
#endif
	P(ml_priv);

	printk(KERN_NOTICE "[netdev_probe] === target offset is 0x1DC (476) ===\n");
	printk(KERN_NOTICE "[netdev_probe] === look up which field above matches 0x1DC ===\n");

	return -EINVAL;  /* don't stay loaded */
}

static void __exit np_exit(void) {}

module_init(np_init);
module_exit(np_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Diagnostic: print net_device field offsets to find ABI mismatch");
