# CLA "second gate" — RESOLVED: it IS a WINDATA-PACKING gate, NOT an engine-state regression (2026-07-02)

Device: mainline #456 (`Linux (none) 6.6.0 #456 Thu Jul 2 19:04:20 UTC 2026`), live, no reboot.
Rig: host enxc8a362e95900 = 172.31.9.50/24 on device **lan1**; static gw ARP
172.31.9.1→f4:f6:47:0f:42:64; device lan1=172.31.9.1, lan4=192.168.9.1, ip_forward=1.
Flow: UDP **172.31.9.50:50010 → 192.168.9.50:53**.

## HEADLINE — the prior "content-independent engine regression" conclusion is REFUTED

The CLA hash-lookup **engine WORKS** on this boot. It performs a genuine **content-exact
match** and returns FORWARD when the stored windata equals the extracted key, and MISS
otherwise. Reproducible, flow-verified:

| test | ram0[9] rule | windata | ACL(submit) | cla_tx_fwd | cla_tx_trp | verdict |
|---|---|---|---|---|---|---|
| **TEST 0** | 0x98 (empty→ZERO key) | all-zero | +250 | **+250** | 0 | **FORWARD** |
| TEST 0 repeat | 0x98 | all-zero | +250 | **+250** | +1 | **FORWARD** |
| CONTROL a | 0x98 (zero key) | NONZERO 5-tuple | +250 | 0 | +250 | MISS |
| CONTROL b | 0x98 (zero key) | zero, **valid-bit OFF** | +250 | 0 | +250 | MISS |

⇒ zero windata matches ONLY the zero key; a nonzero windata (or a cleared valid bit) MISSES
the zero key. This is an **exact content compare**, so the engine is not broken.

**Why the prior session wrongly concluded "content-independent":** its "zero-windata control"
(cla_second_gate_2026-07-02.md, Test B) was run with **rule 0x90 forced (a NON-zero key)**
against a zero windata → a guaranteed content mismatch, not a control. Zero is shift/format-
invariant, so the *only* case it can ever match is the zero key — which is exactly TEST 0 here.
On this clean boot the zero-key/zero-windata catch-all **does** forward (+250, reproduced twice).

## VERDICT

**Gate 2 is a WINDATA-CONTENT / PACKING gate, not an engine-state gate.** The lookup engine
demonstrably hits (forwards) on a genuine content match. The residual problem is purely:
*produce the byte-exact windata that equals the rule-0x90 extracted key.*

## The decomp windata layout + compare transform

- `cla_set_hash_table` @ 0x15a14 (ghidra/output_ko/tm.ko/cla_set_hash_table.c): the ram2 entry
  is **15 words / 60 bytes**, written via `cla_set_indirect_rw_data` for words 0xe..0. Debug
  printk (lines 23–72) fixes the layout: **windata0 = *(u16*)(entry+0x13)**, windataN at
  **0x13+2N** (20 LE-16 shorts, bytes 0x13..0x3a). Bytes 0x00..0x12 are action/valid/extr_index
  (word3 bit31 = valid; byte0x10 = action, 0x49 = forward).
- `tm_acl_get_fastHashRule` @ 0x57218 (…/tm_acl_get_fastHashRule.c) builds the v4 entry
  (`param_4`) windata (lines 213–234): it is a **SCATTERED copy** of the flow-key descriptor
  (`memcpy(auStack_78, param_2+0x60, 0x50)`) into shorts at param_4[0x13,0x15,…,0x37]. Notably
  **windata0@0x13 = local_75<<8** (low byte forced 0) — the tuple is NOT a plain contiguous
  {proto,src,dst,sport,dport} short-block.
- `aclBuildHashAndAclRule` @ 0x5cc20 lines 513–553 and `tm_acl_fast_add_v4v6` @ 0x5c2a8 lines
  114–156: the **hash KEY** used for the slot (a SEPARATE `&local_91` buffer, *not* the stored
  entry) = the windata region packed with a **1-bit left shift** (equivalently putbits at bit
  **33+16·n**). The stored **entry windata is RAW**; only the transient slot-key is shifted.

## The extracted key + the "1-bit shift" clarified

Forced rule 0x90 (ram0[9] word4 = 0x00150001). Live `gparsehashkey` (STABLE, 3 reads):
`48000000 583e0022 81501265 86b41265 0000006b` → hashcalc **0xf6d5 → slot 0xd5** (== prior).
Bit-extracting extra_data at **bit 33+16·n** yields the RAW 5-tuple
`{0011 ac1f 0932 c0a8 0932 c35a 0035}` = {UDP, 172.31.9.50, 192.168.9.50, sport 50010, dport 53}.
**The "1-bit-left-shift" is only the bit-33 anchor** (33 = 1 past a word boundary); the field
*values* are the plain raw 5-tuple, not a shifted 5-tuple.

## RIG BUG found & fixed (invalidated several intermediate reads)

`hping3 --udp` **defaults the source IP to 127.0.0.1** (confirmed on the wire by tcpdump: the
extracted key showed src = 0x7f000001). Adding **`-a 172.31.9.50`** restores the correct src
and the canonical key. Also mid-session the host rig config (172.31.9.50/24 + 192.168.9.0/24
route + static gw ARP) was silently torn down (flow leaked out wlo1) — RESTORED. All final
results above/below were re-run with the flow confirmed (ACL/TRP += packet count).

## TEST 1 — packings tried (all flow-verified MISS)

With rule 0x90 forced (clean stable key, slot 0xd5, fill520 → all 520 buckets):

| packing (windata) | result |
|---|---|
| raw 5-tuple LE @0x13 (prior Test A) | MISS (TRP+250) |
| raw shifted-left-1 == gparse bytes verbatim @0x13 (1a/1b) | MISS |
| raw LE @0x11 (proto@0x11) / shift1 @0x11 | MISS |
| big-endian tuple @0x13 / @0x11 | MISS |
| **sweep: offsets 0x13..0x29 × {LE,BE} × {raw,shift1}** (24 placements) | **ALL MISS** |

No hand-constructed **contiguous** 5-tuple block forwards. Combined with the decomp, the correct
windata is the **scattered / field-specific layout** that `tm_acl_get_fastHashRule` emits from
the flow-key descriptor (windata0@0x13 = high-byte-only, etc.) — not reproducible byte-exactly
from RAM alone without the flow-descriptor struct.

## TEST 2 — not reached

No 5-tuple packing forwarded, so the selectivity/wire-egress confirmation was not applicable.
(Selectivity of the *engine* is already shown: CONTROL a proves a nonzero windata MISSES the
zero key, i.e. the match is per-content, not catch-all.)

## Bottom line for driver productization

The engine is proven correct; the only missing piece is the **exact stock windata bytes**.
Do NOT hand-roll a 5-tuple→windata packer (the layout is scattered/non-contiguous). Instead:
1. Port stock's entry-builder chain verbatim — `tm_acl_fast_add_v4v6` → `tm_acl_get_fastHashRule`
   → `cla_set_hash_table` (60-byte entry, windata scatter from the flow-key descriptor), OR
2. MMIO-capture stock's actual ram2 entry (all 15 words) for one known 5-tuple flow and replay
   the byte-exact entry via fill520/clawrite on mainline to confirm the forward, then codify
   that transform.

## State left behind (device healthy, NO reboot)
- Device on **mainline #456**, alive; console REPL + UART bridge up; console loglevel set to 8.
- **ram0[9] RESTORED to 0x00150051** (readback-confirmed).
- ram2 hash banks hold the last test entry (RAM-only, INERT; clears on next DTR boot). No ram1
  edits. All other access read-only.
- **Host rig RESTORED**: enxc8a362e95900 has 192.168.1.50/24 (tftp) **and** 172.31.9.50/24;
  route 192.168.9.0/24 via 172.31.9.1; static ARP 172.31.9.1→f4:f6:47:0f:42:64. Did NOT reboot.
