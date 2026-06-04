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

## UPDATE 2026-06-04 — the two paths to a correct entry are both walled; DECISION NEEDED
Investigated both ways to get a CORRECT CLA forward entry for Stage 2:
1. **koprobe ground-truth on stock — BLOCKED.** Stock installs an L3 hardfast only for a ROUTED/NAT'd
   ESTABLISHED flow, which needs a WAN uplink. The device's WAN jack is EMPTY (enx6c70 absent) and
   there's no GPON fiber → stock has no WAN → no hardfast to trace. Can't be fixed in software (the
   WAN port is the physical MAC4 jack; the host's LAN-jack NICs can't present a WAN to stock).
2. **full static decode — slow/error-prone.** tm_acl_get_fastHashRule (tm.c:49213-49469) packs the
   entry as an opaque, unlabeled HW bit-shuffle (param_2 flow-desc → param_4 entry); identifying which
   bits are the 5-tuple key vs the egress/action by hand is high-risk guessing.
Confirmed via clapeek on live mainline: the CLA boot rules ARE loaded (ram1 addr0x16 reads byte-exact
to zx_cla_table.h) and readable; the review's clapeek word0 OFF-BY-ONE is real (peek "addr0x18"
returned the 0x19 entry). So a mainline copy-a-working-rule-and-tweak-the-outport experiment is
possible, but (a) still needs the action-bit decode and (b) risks perturbing the live classifier on
the WORKING SW router.

### Recommendation
The clean, low-risk unblock is **physical: plug a host NIC (or a real uplink) into the WAN jack** so
stock gets a WAN, a real flow goes ESTABLISHED, and koprobe captures the EXACT hardfast entry + regs
to copy. Without that, Stage 2 is a slow blind-decode/experiment grind. The entire SW router (Phases
0-4) + all Phase 6 RE + the verified cls_flower plumbing (Stage 1) are already delivered; Stage 2 (the
actual chip offload) is the remaining frontier and is gated on this.

## UPDATE 2026-06-04 (Stage 2 — clawrite primitive added; ram2 write doesn't persist yet)
Added a `clawrite` debugfs to the mainline driver (zx-eth-main.c): `echo "<ram_id> <addr> <w0..w16>"`
→ zx_cla_write_entry + readback. Builds clean, debugfs present after boot. Findings on HW:
- **ram2 READ works + is populated** at boot: clapeek ram2 0x21/0x79/0xcb/0x121 read the live boot
  classification entries (e.g. 0x79 = 01005055 00154000 80000408 80000c17 80000043 00c20001 ...).
  Note: word3 = 8000_xx17 / 9000_xx17 (valid bit31 + inport), word4 = 42/43 (outport) — matches
  cla_ram_layout_re.md ram2 field map.
- **clawrite to a FREE ram2 slot (0xaa) did NOT persist** (rc=0 but readback + neighbors all zero).
  Boot-load uses the SAME zx_cla_write_entry and those entries DO persist → so a fresh-slot direct
  write needs something more. LEADS: (a) the kotrace showed stock writes the entry via PER-WORD
  cla_set_indirect_rw_cmd calls (r0=rw, r1=word_idx, r2=data), NOT "17 data regs then one CMD" — the
  ram2 hash write protocol may be per-word/commit-per-word; (b) a hash-valid addr / tag bit may be
  required (the slot must be the hash of the key); (c) a possible read off-by-one (review) — but
  neighbors a8..ac all zero rules out a simple ±1. NEXT: diff zx_cla_write_entry vs the boot-load path
  vs the stock cla_set_indirect_rw_cmd per-word sequence; fix the write; then re-test (write a boot
  entry's bytes to its own slot and confirm round-trip, then a fresh slot).

## UPDATE 2026-06-04 (Stage 2 loop iter — a hardfast is a ram0+ram1+ram2 TRIO, not just ram2)
Two findings this iteration:
1. **cla_set_indirect_rw_cmd (tm.c:0x44c)** = just the CMD-reg write: `tmOnuRegWrite(claRegTable[0],
   addr + ram_id*0x400000 + rw*0x8000000)` = `addr|ram_id<<22|rw<<27` — EXACTLY the driver's encoding
   (zx-eth-main.c:2044). Validates ram_id<10, addr≤0x3fffff. The DATA (17 words) is written by the
   caller before the CMD. So the driver's protocol matches the CMD; the data path is the suspect.
2. **A hardfast install touches THREE rams** (re-read the kotrace 'I' lines for the fwd flow):
   `cla_set_indirect_rw_cmd(rw=0, ram_id=2, addr=0x5a)` + `(rw=0, ram=1, addr=0x98)` +
   `(rw=0, ram=0, addr=0x09)`. ⇒ a flow = **ram0 (extract-index, addr 0x09) + ram1 (rule TCAM, addr
   0x98) + ram2 (hash result, addr 0x5a)** TRIO. Writing ram2 alone (what clawrite did) is NOT enough
   to forward — the CLA needs ram0 (which bytes to extract as the key), ram1 (the rule that matches +
   points into the hash), and ram2 (the forward action). This is the real reason mainline traps: it
   has the boot ram0/1 but never installs per-flow ram1+ram2 hardfast entries.
- Also: clawrite to ram2 0x5a persisted ONLY word0 (0x03005044 seen at 0x5a via the off-by-one) —
  words1-16 didn't stick. Either the runtime CLA hash engine partial-commits, or the data-reg write
  needs a different sequence than boot-load. TBD.

### NEXT (loop)
Reboot STOCK, kotrace/fpga-read the FULL trio for one flow: ram0[0x09], ram1[0x98], ram2[0x5a] (and
the reverse trio). Then in mainline write all three via clawrite and re-test hw_trap. Also resolve the
ram2 words1-16 persist issue (compare boot-load timing vs runtime; try writing each word + CMD).

## UPDATE 2026-06-04 (Stage 2 loop — CLA-hash WRITE protocol still resists; data-port semantics)
- Stock cla_set_hash_table (tm.c:3521-3530) write order = **CMD(addr) FIRST, then 15 words (idx 14→0)**
  via cla_set_indirect_rw_data. The driver does data-first + 17 words (wrong order/count for hash).
- BUT a dynamic fpga test on stock (CMD-first write of a pattern to a FREE ram2 slot 0xee, then read
  back) STILL persisted only word0 (deadbeef); words1-14 read back as STALE (the prior flow's
  ram2[0x0c]) — so CMD-first alone is NOT the fix; the per-word DATA write isn't landing words1-14.
- ROOT: tmOnuRegWrite(regtype, val, idx) (tm.c:35356) = `reg = claRegTable[regtype].base +
  idx*claRegTable[regtype].stride(+0x14)`; then `fpga_write_reg(reg, (cur & ~(mask<<sh)) |
  (val&mask)<<sh)` — a MASKED read-modify-write (mask=+0xc, shift=+0x10). So the DATA-port write for
  ram2 depends on claRegTable[2]'s {base, stride, mask, shift}. The driver assumes base=0xC01C,
  stride=4, full-word — one of those is wrong for the data port (likely stride≠4, OR a single
  auto-incrementing port, OR mask<32b). 
- NEXT (dynamic probe, per user's web-UI/experiment suggestion): on stock, write DISTINCT values to
  0xe3007, 0xe3008, 0xe3009 and read each DIRECTLY (fpga -r, not via the CLA read-CMD) to check if
  the data regs are independent (stride 4) or aliased/single-port. Also recover claRegTable[2] from
  the decomp data section (or fpga-read the descriptor). Then fix zx_cla_write_entry's hash path.
- Tool note (user): can perturb firewall/rules in the stock web UI + read CLA registers to observe
  table effects — use only if needed.
