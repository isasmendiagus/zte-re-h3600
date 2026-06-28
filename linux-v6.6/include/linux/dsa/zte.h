/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Shared definitions for the ZTE ZX279128S DSA tagger (net/dsa/tag_zte.c) and
 * the conduit driver (drivers/net/ethernet/zte/zx-eth-main.c).
 *
 * The switch port is carried OUT-OF-BAND in the CPU<->fabric DMA descriptor.
 * To convey it between the DSA tagger and the conduit across the qdisc layer,
 * an INTERNAL tag is prepended by the tagger and consumed+stripped by the
 * conduit before DMA (so it never reaches the wire). See tag_zte.c.
 */
#ifndef _LINUX_DSA_ZTE_H
#define _LINUX_DSA_ZTE_H

#include <linux/types.h>

#define ZTE_TAG_LEN	4	/* {mark, port, 0, 0}; stripped before DMA */
#define ZTE_TAG_MARK	0x5a	/* sanity marker for the internal tag */

/*
 * PM (packet-modify / next-hop) indirect-RAM bridge.
 *
 * The flow-offload binder lives in the BUILT-IN DSA driver (zx-dsa.c,
 * CONFIG_NET_DSA_ZTE_ZX279128=y) while the conduit lives in a MODULE
 * (zx-eth-main.c, CONFIG_ZX279128_ETH=m). The binder's own ioremap of the PM
 * window (devm_ioremap(0x921dc000)) does NOT commit to the live datapath PM RAM
 * — proven by readback-verify (word1 never lands) — whereas the conduit's PM
 * path (via e->base = ioremap(0x921c0000,...) + 0x1DC0xx) provably commits.
 *
 * A built-in cannot call a module symbol directly, but a module can call a
 * built-in exported setter and register function pointers. So the conduit
 * registers a {write,read} pair (wrapping its working zx_pp_pm_write_entry /
 * zx_pp_pm_read_entry) at probe; the binder calls zx_pm_ops->write()/read()
 * instead of its own non-committing path. write/read take the same indirect
 * iface the conduit uses: (ram_id, ram_addr, data[8]).
 */
struct zx_pm_ops {
	int (*write)(u8 ram_id, u32 addr, const u32 d[8]);
	int (*read)(u8 ram_id, u32 addr, u32 d[8]);
};

/* Defined + exported by the built-in DSA side (zx-dsa.c). NULL until the
 * conduit module registers. */
extern struct zx_pm_ops *zx_pm_ops;
void zx_dsa_register_pm_ops(struct zx_pm_ops *ops);

#endif /* _LINUX_DSA_ZTE_H */
