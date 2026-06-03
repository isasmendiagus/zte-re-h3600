// SPDX-License-Identifier: GPL-2.0
/*
 * Tag handling for the ZTE ZX279128S on-chip switch.
 *
 * The ZX279128S conveys the switch port OUT-OF-BAND, in the CPU<->fabric DMA
 * descriptor (TX egress port in desc word3 bits[9:4]; RX ingress port in
 * desc[6] bits[7:3]), NOT in the ethernet frame. The standard DSA tagger model
 * assumes an in-band tag the conduit carries transparently, which does not fit.
 *
 * To bridge the two without losing the port across the qdisc layer (skb->cb is
 * not preserved between the tagger and the conduit's ndo_start_xmit), this
 * tagger prepends a small INTERNAL tag that the conduit driver
 * (drivers/net/ethernet/zte/zx-eth-main.c) consumes and STRIPS before DMA — so
 * it never reaches the wire:
 *
 *   TX: tagger prepends {mark, port}. The conduit reads the port, writes it into
 *       the descriptor egress field, and copies frame[ZTE_TAG_LEN:] into the BP
 *       buffer (dropping the internal tag).
 *   RX: the conduit reads the descriptor ingress port, prepends {mark, port}
 *       before netif_receive_skb(); this tagger reads the port, selects the
 *       per-port netdev, and pulls the tag.
 *
 * Reverse-engineered from the stock vendor kernel (pon_tm_net_tx / pon_tm_net_poll
 * descriptor handling) — see tasks/00.01.eth-driver/findings/dsa_driver_plan.md
 * and memory zte-dsa-foundation.
 *
 * Copyright (C) 2026 Agustin Isasmendi <infra@quecomere.com>
 */

#include <linux/dsa/zte.h>
#include <linux/etherdevice.h>

#include "tag.h"

#define ZTE_NAME	"zte"

static struct sk_buff *zte_tag_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	u8 *tag;

	tag = skb_push(skb, ZTE_TAG_LEN);
	tag[0] = ZTE_TAG_MARK;
	tag[1] = dp->index & 0xff;	/* egress switch port; conduit maps to desc */
	tag[2] = 0;
	tag[3] = 0;

	return skb;
}

static struct sk_buff *zte_tag_rcv(struct sk_buff *skb, struct net_device *dev)
{
	/* The conduit calls eth_type_trans() before delivery, which pulls ETH_HLEN
	 * and resets the MAC header to the frame start — i.e. to our prepended tag.
	 * So read the tag at skb_mac_header(), NOT skb->data (which now sits
	 * ETH_HLEN into the frame). Then skb_pull_rcsum(ZTE_TAG_LEN): combined with
	 * dsa_switch_rcv's skb_push(ETH_HLEN), skb->data ends at the real eth header.
	 * (Same pattern as tag_ar9331.)
	 */
	u8 *tag = skb_mac_header(skb);
	int port = tag[1];

	if (unlikely(tag[0] != ZTE_TAG_MARK))
		return NULL;

	skb->dev = dsa_master_find_slave(dev, 0, port);
	if (!skb->dev)
		return NULL;

	skb_pull_rcsum(skb, ZTE_TAG_LEN);

	/* [bridge-fwd fix 2026-06-03] Do NOT set skb->offload_fwd_mark. This is a
	 * TRAP-ALL driver with NO hardware bridge offload (no .port_bridge_join / HW
	 * forwarding — every frame is trapped to the CPU). dsa_default_offload_fwd_
	 * mark() sets offload_fwd_mark = !!(dp->bridge), i.e. 1 whenever the user
	 * port is in a bridge — telling the bridge "hardware already forwarded this
	 * to the other bridge ports, don't software-forward it". That is a LIE here:
	 * the HW did NOT forward it, so the frame reaches the CPU but the bridge
	 * drops it instead of flooding to the peer lan port -> lan<->lan comms break
	 * (verified: ARP RX on lan1 never egresses lan2). Leaving offload_fwd_mark=0
	 * lets the software bridge forward lan1<->lan2 through the CPU. (When real HW
	 * bridge offload is added, restore this gated on actual HW-fwd capability.) */

	return skb;
}

static const struct dsa_device_ops zte_netdev_ops = {
	.name			= ZTE_NAME,
	.proto			= DSA_TAG_PROTO_ZTE,
	.xmit			= zte_tag_xmit,
	.rcv			= zte_tag_rcv,
	.needed_headroom	= ZTE_TAG_LEN,
};

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DSA tag driver for the ZTE ZX279128S switch (out-of-band descriptor port, internal tag)");
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_ZTE, ZTE_NAME);

module_dsa_tag_driver(zte_netdev_ops);
