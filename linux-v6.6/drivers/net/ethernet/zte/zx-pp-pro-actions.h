/* SPDX-License-Identifier: GPL-2.0
 *
 * Stock-derived `def_ptl_pkt_action` table for the PPE block.
 *
 * Reverse-engineered 2026-05-23 via a kotrace runtime capture of
 * stock chip_tm_init -> zte_api_pp_set_pro_action calls on a working
 * H3600 device. See:
 *   tasks/00.01.eth-driver/findings/chip_tm_init_args.md
 *   tasks/00.01.eth-driver/findings/captures/kotrace_full_args.txt
 *
 * The 142 stock calls split as 71 unique protocol IDs × 2 PP instances.
 * action = 1 means "trap to CPU"; action = 0 means "forward normally".
 * Only one entry (proto 0x14) differs between the two PP instances —
 * PP0 traps it, PP1 forwards.
 *
 * Driver Phase 4: implement zx_pp_apply_pro_action_table() that iterates
 * this list and writes each entry to the equivalent PP register on each
 * PP instance. Requires RE-ing zte_api_pp_set_pro_action in tm.ko first
 * to know which register/offset takes the action value.
 */
#ifndef ZX_PP_PRO_ACTIONS_H
#define ZX_PP_PRO_ACTIONS_H

#include <linux/types.h>

struct zx_pp_pro_action_entry {
	u8 proto;
	u8 action_pp0;
	u8 action_pp1;
};

static const struct zx_pp_pro_action_entry zx_pp_pro_actions[] = {
	{ 0x00, 1, 1 },  { 0x01, 1, 1 },  { 0x02, 1, 1 },  { 0x03, 1, 1 },
	{ 0x04, 1, 1 },  { 0x05, 1, 1 },  { 0x06, 1, 1 },  { 0x07, 1, 1 },
	{ 0x08, 1, 1 },  { 0x09, 1, 1 },  { 0x0a, 1, 1 },  { 0x0b, 1, 1 },
	{ 0x0c, 1, 1 },  { 0x0d, 1, 1 },  { 0x0e, 1, 1 },  { 0x0f, 1, 1 },
	{ 0x10, 1, 1 },  { 0x11, 1, 1 },  { 0x12, 0, 0 },  { 0x13, 1, 1 },
	{ 0x14, 1, 0 },  /* sole PP0/PP1 divergence — verify with double trace */
	{ 0x15, 1, 1 },  { 0x16, 1, 1 },  { 0x17, 1, 1 },  { 0x18, 1, 1 },
	{ 0x19, 1, 1 },  { 0x1a, 1, 1 },  { 0x1b, 1, 1 },  { 0x1c, 1, 1 },
	{ 0x1d, 1, 1 },  { 0x1e, 0, 0 },  { 0x1f, 0, 0 },  { 0x20, 0, 0 },
	{ 0x21, 1, 1 },  { 0x22, 1, 1 },  { 0x23, 0, 0 },  { 0x24, 0, 0 },
	{ 0x25, 1, 1 },  { 0x26, 0, 0 },  { 0x27, 1, 1 },  { 0x28, 0, 0 },
	{ 0x29, 1, 1 },  { 0x2a, 1, 1 },  { 0x2b, 1, 1 },  { 0x2c, 1, 1 },
	{ 0x2d, 1, 1 },  { 0x2e, 1, 1 },  { 0x2f, 1, 1 },  { 0x30, 1, 1 },
	{ 0x31, 1, 1 },  { 0x32, 1, 1 },  { 0x33, 1, 1 },  { 0x34, 1, 1 },
	{ 0x35, 1, 1 },  { 0x36, 1, 1 },  { 0x37, 1, 1 },  { 0x38, 1, 1 },
	{ 0x39, 1, 1 },  { 0x3a, 1, 1 },  { 0x3b, 1, 1 },  { 0x3c, 1, 1 },
	{ 0x3d, 1, 1 },  { 0x3e, 1, 1 },  { 0x3f, 1, 1 },  { 0x40, 1, 1 },
	{ 0x41, 1, 1 },  { 0x42, 1, 1 },  { 0x43, 0, 0 },  { 0x44, 0, 0 },
	{ 0x45, 1, 1 },  { 0x46, 1, 1 },
};

#define ZX_PP_PRO_ACTION_COUNT  ARRAY_SIZE(zx_pp_pro_actions)

#endif /* ZX_PP_PRO_ACTIONS_H */
