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

#define ZTE_TAG_LEN	4	/* {mark, port, 0, 0}; stripped before DMA */
#define ZTE_TAG_MARK	0x5a	/* sanity marker for the internal tag */

#endif /* _LINUX_DSA_ZTE_H */
