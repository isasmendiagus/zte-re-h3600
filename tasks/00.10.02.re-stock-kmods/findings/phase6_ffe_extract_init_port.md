# Phase 6 — FFE extract-infrastructure init ported to mainline

2026-06-05, branch `phase6-hw-offload`. Closes the actionable next step from
`phase6_cla_hw_hash_CRACKED.md` (UPDATE 2026-06-05d): port the stock FFE extract
init so the CLA has the 5-tuple/3-tuple extract rules + index tables (and their
fast-enable bits) it needs to compute the hash on ingress instead of trapping all.

## What was ported

Stock functions (decomp_all_tm.c), all using cla_set_extra_rule_table (ram1, 17
words) / cla_set_extra_index_table (ram0, 5 words), both CMD-first + descending
(== the driver's existing `zx_cla_write_hash`):

- `tm_acl_l2_fast_init` (tm.c:49785) — loop idx 1..8, per port writes ram1 rules
  `(idx<<4)+0..+3`: +0/+1 = v4 5-tuple (local_b0, word0 0x22038608), +2/+3 = v6
  5-tuple (local_6c, word0 0xe1828406). +1/+3 are the dir-set variant (word14 high
  nibble 0->2). Rule_ids 0x10..0x83.
- `tm_acl_3tuple_fast_init` (tm.c:54578) — loop idx 1..9, per port writes ram1
  rules base `0x14+0x10*(idx-1)`, +0..+3: v4 3-tuple (local_a8, word1 0x00000001)
  + v6 3-tuple (local_64). Rule_ids 0x14..0x17, 0x24..0x27, ..., 0x94..0x97.
- `tm_acl_fast_init` (tm.c:54140) — the L3 5-tuple init: ram1 rules 0x90/0x91 (v4
  5-tuple) + 0x02/0x03 (v6 5-tuple); reads ram0 index 9, sets index_valid |=1 (v4)
  + reads index 10, sets |=4 (v6).
- ram0 extract-index tables idx 1..10 — base extract-byte layout from
  `aclRamInit_part_6` (tm.c:54704, extract_index0..15 = sequential bytes per index);
  word4 = index_valid + flags after the fast-enable OR's.

Caller in stock: `aclRamInit_part_6` (tm.c:54772-54774) calls
`tm_acl_3tuple_fast_init()` then `tm_acl_fast_init()` when `g_fast_opti != 0`.
(`tm_acl_l2_fast_init` is called from a separate path; its rules are in the same
0x10.. range and are included here for completeness/parity.)

## The fast-ENABLE register — there isn't a separate one

There is NO standalone fpga_write_reg "fast enable" bit. The HW gate is the
**index_valid mask** in each ram0 index entry word4 (bits set by
`EN_V4FAST_EXTIDXTBL`/`EN_V6FAST_EXTIDXTBL`, tm.c:49717/49751):

  bit0 = v4 5-tuple, bit2 = v6 5-tuple, bit4 = v4 3-tuple, bit6 = v6 3-tuple
  (the 0x10/0x30, 0x40/0xc0 etc. are the +dir variants).

So ram0[0x09] word4 `0x00150051` = (0x40|0x10|0x01) valid + 0x15 flag byte (byte
0x12 = valid_en bit4 | nomatch_cfg). Writing the ram0 index tables WITH these word4
values IS the enable. `g_ipv4FastEn`/`g_ipv6FastEn` are SW-only flags that steer
`aclGetExtIdxRuleRamAddrByPort` (tm.c:50137) to return extract-index 9 (v4) / 10
(v6) for any port < 0x20; they have no direct HW write.

CLA indirect-write CMD encoding (cla_set_indirect_rw_cmd, tm.c:324):
`cmd = ram_addr | ram_id<<22 | rw_en<<27`; rw_en=0 for write. e->base phys
0x921c0000; CLA cmd reg = base+0x1CC014 (already mapped). No new ioremap.

## Cross-check vs captured ground truth (0 mismatches)

`scripts/ffe_gen_table.py` regenerates the whole table from the loop structure and
asserts every entry byte-exact against the live stock dump
`findings/captures/cla_stock/cla_stock_ram0-6_2026-06-01.txt`. Verified:

- ram1[0x90] (v4 5-tuple) = `22038608 000058a1 0 0 f00ff000 ffffffff ffffffff
  0fffffff 0 0 0 0 0 0 00700000 00092492 0` == the CRACKED.md captured ram1[0x98].
- ram0[0x09] = `93929190 97969594 9b9a9998 9f9e9d9c 00150051` == CRACKED.md.
- All captured rule_ids 0x02,0x03,0x10..0x27 and index 0x01..0x0a match exactly.

NOTE: the capture also has ram1[0x18/0x19/0x28/0x29] (`00010100`/`00000910`
templates) — these are written by a DIFFERENT (non-5tuple/3tuple) init and are
intentionally NOT in this port (out of the 3 targeted functions). They do not
affect the 5-tuple/3-tuple extract path.

## Code changes (driver)

- `linux-v6.6/drivers/net/ethernet/zte/zx_ffe_table.h` — NEW. Generated +
  verified table: 72 ram1 rules + 10 ram0 index entries, with full provenance
  header + regen command.
- `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`:
  - `#include "zx_ffe_table.h"` + new `zx_cla_ffe_extract_init(struct zx_eth *e)`
    (writes the 72 ram1 rules via `zx_cla_write_hash(e,1,id,w,17)` then the 10 ram0
    index tables via `zx_cla_write_hash(e,0,id,w,5)`; logs ok/fail).
  - Called once in `zx_eth_init_chip_tm()` immediately AFTER `zx_cla_apply_replay(eth)`
    (so the baseline trap rules exist first, then the extract infra is layered on).

## Entries written (ram, addr)

- ram1 rules: 0x02,0x03; 0x10-0x17,0x20-0x27,0x30-0x37,0x40-0x47,0x50-0x57,
  0x60-0x67,0x70-0x77,0x80-0x87 (L2 0x?0-0x?3 + 3tuple 0x?4-0x?7 per port 1..8);
  0x90,0x91,0x94-0x97. (72 total.)
- ram0 index: 1,2,3,4,5,6,7,8,9,10. (word4 fast-enable: idx1-5=0x00150355,
  idx6-7=0x00150055, idx8=0x00150755, idx9=0x00150051 [v4], idx10=0x00150004 [v6].)

## Build

`python3 tasks/00.01.eth-driver/scripts/build_slotA.py` — COMPILES CLEANLY, no
warnings/errors; zx279128-eth.ko rebuilt + embedded; zImage 14,380,999 bytes.
("exceeds NAND write size" is the expected TFTP-boot warning.) NOT booted.

## Uncertainties for the interactive session to verify on-device

1. **Call-site ordering**: I placed `zx_cla_ffe_extract_init` after
   `zx_cla_apply_replay` inside `zx_eth_init_chip_tm`. Stock runs the FFE init from
   `aclRamInit_part_6` (earlier, during tm_sdk_init) — confirm doing it post-replay
   doesn't get clobbered by a later table write, and that the extract rules read
   back intact via `clapeek 1 0x90` / `clapeek 0 9` after boot.
2. **L2 init inclusion**: `tm_acl_l2_fast_init` is not on the same caller as the
   other two in the decomp; I included its rules for parity. If the L2 rules cause
   unexpected matches, they can be dropped (the v4/v6 5-tuple 0x90/0x91/0x02/0x03 +
   their index-9/10 valids are the core for routed-TCP offload).
3. **index word4 flags**: I replicated the captured word4 verbatim (post-enable
   state), which sets valid bits for ALL classes per port (incl. ones from inits I
   didn't fully port). All referenced rule_ids ARE installed, but confirm no index
   points at an empty rule and traps.
4. After this init, re-run the Stage-2b slot-sweep: the ram2 per-flow entry at the
   HW-hashed slot should now actually forward (the missing ram0/ram1 chain is the
   gap this port fills). Verify hw_trap delta drops on the matched flow.

Tooling added: `tasks/00.01.eth-driver/scripts/ffe_gen_table.py` (generator +
verifier), `tasks/00.01.eth-driver/scripts/ffe_build_words.py` (field-by-field
reconstruction cross-check).

## ON-DEVICE REVIEW (2026-06-05, interactive session) — port is CORRECT but NOT SUFFICIENT
Reviewed + tested the subagent's port on hardware:
- Code review: clean, uses the validated zx_cla_write_hash primitive, call-site after zx_cla_apply_replay
  is sane. Table data VERIFIED byte-exact vs ground truth: ram1[0x90]=22038608 000058a1 0 0 f00ff000
  ffffffff ffffffff 0fffffff 0 0 0 0 0 0 00700000 00092492 0; ram0[9]=93929190 97969594 9b9a9998
  9f9e9d9c 00150051. Committed 31e98ecc5.
- BOOT VERIFIED: the FFE init runs automatically — clapeek ram0[0x9] reads back the config at boot
  (was all-zeros before). The extract infrastructure is now present on mainline. ✓ (real milestone)
- FORWARD TEST: NEGATIVE. Wrote the per-flow ram2 fwd entry at all 6 candidate buckets → still traps
  60/60. Then wrote it at ALL 256 ram2 buckets (covers any bucket) → STILL traps 80/80. So bucket
  prediction is NOT the gap.
- ROOT (pipeline_stats during the flow): **CLA fwd[0x1cc3c0]=0, drop=0, copy=0** — the CLA never makes
  a forward decision; everything goes to UP hw_trap. ⇒ even with ram0/ram1 extract tables present and a
  matching ram2 entry, the CLA is not CONSULTING the hash to forward. The missing piece is a CLA
  fast-path FORWARD-ENABLE (the mode/register that switches the CLA from trap-all to hash-forward),
  which is NOT among the 3 ported init functions.
### NEXT RE TARGET
Find what enables the CLA forward/hash-consult path (vs trap-all). Candidates: a per-port or global
CLA "fast/acl forward enable" register set at FFE-enable time or capWAN/routing provisioning; the
oth_l3_pkt_action / default-flow action (0x9238c0cc/fc); trap_acl_en; or the SADM/QMG forward routing.
This is the same "trap-all pipeline" enable the deadend history (Iter K-AD) circled — now narrowed to:
extract tables ARE present, hash engine + entry write WORK, but CLA fwd=0 → the forward ACTION/enable
is the last switch. Look at what tm_acl_fast_init's CALLER (tm.c:54773) does around the init calls, and
any cla_set_config / acl-enable writes in that path.
