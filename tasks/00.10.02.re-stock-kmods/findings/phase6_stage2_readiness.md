# Phase 6 / Stage 2 — readiness assessment + the de-risked next step (0b koprobe)

2026-06-04, branch phase6-hw-offload. Honest status before writing the CLA-rule code.

## What's READY (verified)
- **Write primitive in zx-dsa**: pp_regs+0x14/0x18/0x1c IS the same indirect block as zx-eth's CLA
  (0x1CC014/018/01C) — SBRAG (3 words) and CLA (17 words) share it, selected by ram_id/mem_id. So
  zx-dsa can write CLA ram1/ram2-6 with a 17-word variant of the existing zx_sbrag_write_entry
  (priv->pp_regs). No cross-module call to zx-eth needed.
- **Read-back**: clapeek (zx-eth debugfs) + zx_sbrag_read_entry pattern in zx-dsa.
- **ram1 entry structure**: 17 words/entry. Boot snapshot zx_cla_table.h has ~724 live ram1 rules to
  copy from. cla_ram_layout_re.md: ram1 = rule-TCAM, winoffset0..19 + winmask0..19 + flags, byte0x39
  bit5=inport_mask, bit4=outport_mask.

## The RISK (why not just code it blind)
A ram1 entry is a generic packet-window TCAM (20 offset/mask pairs + action). Hand-constructing one
that (a) matches a specific 5-tuple via the right window offsets/masks AND (b) sets the outport action
AND (c) actually OVERRIDES the per-inport CPU trap — all guessed from the boot snapshot — is
error-prone. The adversarial review (phase6_research_review.md) explicitly flagged the trap-override
as UNPROVEN, and noted the merged #36 TCP-ACK HW-forward used the SPA pktdeal field (0x921d4300), NOT
a CLA action. Guessing TCAM bits + the trap interaction could burn several build/boot cycles.

## DE-RISKED NEXT STEP = 0b koprobe ground-truth (do this BEFORE the Stage-2 write)
Boot STOCK, establish ONE real forwarded flow (iperf LAN→WAN through the stock router), and capture
EXACTLY what stock writes:
1. kotrace {tm_acl_fast_add_v4v6, cla_set_hash_table, cla_set_indirect_rw_cmd, tm_acl_get_fastHashRule,
   hf_set_l3_entry} → /proc/kotrace_dump = the live call order + r0-r3 (entry ptr, slot, ram_id).
2. With the entry pointer/slot from the trace, read the actual CLA entry bytes on stock via
   `fpga -r` of the CLA indirect (or dump the memory the entry was built from).
3. Note whether stock ALSO writes SPA pktdeal (0x921d4300) / any trap-suppression reg for that flow.
This gives the EXACT working entry (ram_id + 17 words + slot + hash) + the full set of regs to
replicate — then Stage 2 becomes "copy these bytes via zx-dsa CLA write" with high confidence, and we
know up front whether the trap-override needs the pktdeal lever.

## Alternative quick experiment (if koprobe is too heavy this iter)
Copy a WORKING boot-snapshot ram1 rule to a free slot, change only the outport nibble, install via
zx-dsa CLA write on a flower match, and watch hw_trap under iperf — a cheap "does changing outport on
a real rule redirect?" probe. Lower confidence but no stock boot needed.

## Decision
Next iteration: 0b koprobe ground-truth (the review's recommended de-risk). It needs a stock boot +
kotrace build (stock_instrumentation_extraction_howto.md) but yields the exact entry+regs, avoiding
blind TCAM guessing. Then Stage 2 write + iperf hw_trap verification.
