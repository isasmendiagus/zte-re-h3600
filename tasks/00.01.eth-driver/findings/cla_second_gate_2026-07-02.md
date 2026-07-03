# CLA "second gate" — RESOLVED: the miss is CONTENT-INDEPENDENT (engine-level), NOT windata/slot/regime (2026-07-02)

Device: mainline #456 (`Linux (none) 6.6.0 #456 Thu Jul 2 19:04:20 UTC 2026`), live, no reboot.
Rig: host enxc8a362e95900 = 172.31.9.50/24 on device **lan1** (ingress; static gw ARP
172.31.9.1→f4:f6:47:0f:42:64); device lan1=172.31.9.1, lan4=192.168.9.1, ip_forward=1.
Flow: UDP **172.31.9.50:50010 → 192.168.9.50:53** (host route via 172.31.9.1, routed to lan4).

## Headline

With rule 0x90 forced (clean stable key), a byte-exact 5-tuple entry in all 520 internal
buckets MISSES — **and so does an all-zero-windata catch-all**, identically. Both give
`cla_tx_fwd`=0 FLAT, `cla_tx_trp` += exactly the packet count, `desOut` action=TRAP
rsn=**0x54 LOOK_UP_MISS**. The two content extremes (correct 5-tuple vs all-zero) behave
identically, so **the second gate is CONTENT-INDEPENDENT**: not windata packing, not the
slot, not the internal/external regime. It is the previously documented **#452 CLA
hash-lookup-ENGINE regression** (the lookup runs — acl_required climbs, desIn=FORWARD —
but the bucket compare returns MISS for ANY valid entry). The prior-session "zero-key
catch-all FORWARDED" does **NOT reproduce on clean #456** → it was a polluted-state / #444
artifact, consistent with the mainline_extract_paradox note.

---

## STEP 1 — forced rule 0x90; captured the LIVE extracted key (STABLE)

- Saved default `ram0[9]` = `93929190 97969594 9b9a9998 9f9e9d9c 00150051` (words0-3 are the
  extra-index data bytes; word4 = index_valid).
- Forced rule 0x90: wrote `ram0[9]` word4 = **0x00150001** (clawrite ram0 addr 9, preserving
  words0-3), readback-confirmed.
- gparsehashkey (0x9238c260, 12 words), read twice mid-flow — **IDENTICAL / STABLE**:

  **`48000000  583e0022  81501265  86b41265  0000006b  00000000×7`**

  word0 = 0x48000000 → ex_rule_id **0x90**; words5-11 zero; **no volatile field** (words4-5
  stable, unlike rule 0x96). This is the clean L3-relative 5-tuple key, matching the paradox
  note byte-for-byte. Decodes to the flow 5-tuple {proto UDP, 172.31.9.50, 192.168.9.50,
  sport 50010, dport 53} in the CLA's 1-bit-left-shifted key-stream packing.

## STEP 2 — hash / bucket / internal-vs-external

- **hashcalc(key) → raw hash = 0xf6d5** (12-word feed gives same as 5-word: 0xf6d5).
- outspace_cfg 0x9238c094 = **0x4** → space_sel=0, hash_num=1. cla_config 0x9238c080=0x600,
  poly 0x9238c090=0x00e400e4.
- Slot = raw low byte = **0xd5** → ram2[0xd5] (< 0x100, well inside the 520 internal buckets;
  fill520 covers ram2[0..0xff]).
- mem_ctrl regime bit: ram1[0x90] word14 = 0x00700000 → byte0x3b = (word14>>24)&0xff = 0x00 →
  **bit1 = 0 = INTERNAL** (matches stock=0). ram1[0x90] full:
  `22038608 000058a1 0 0 f00ff000 ffffffff ffffffff 0fffffff 0 0 0 0 0 0 00700000 00092492 0`.
- hashcalc(all-zero key) → raw **0x0000** → slot 0 → also INTERNAL.
- **Verdict: the real key is INTERNAL; the bucket (0xd5) was filled by fill520. External-SRAM
  (0xF1020000) is NOT involved — the external-regime hypothesis is ruled out.**

## STEP 3 — the decisive "match-by-construction" test

Test A (byte-exact 5-tuple, windata = the packet's L3 windows = match-by-construction):
- fill520 `03005044 fa11c000 00000608 80000000 11000049 32ac1f00 32c0a809 35c35a09` → 520/520;
  ram2[0xd5] readback byte-exact. windata N0..N6 = {0x0011,0xac1f,0x0932,0xc0a8,0x0932,0xc35a,
  0x0035} = the exact 5-tuple the packet presents at the winoffsets.
- 385-pkt + 500-pkt UDP flows: **cla_tx_fwd = 0 FLAT**; cla_tx_trp +385 / +500 exactly;
  acl_required (hi16 of 0x9238c3b8) += exactly the pkt count (submitted to lookup).
- Descriptor latches decoded (action=w2[22:21], rsn=w2[29:23]=(w2>>23)&0x7f, l3_en=w3 bit6):
  - desIn  w2=0xa4800000 → action=**FORWARD** rsn=**0x49** (OTHERS), l3_en=1 (w3=0x82610841).
  - desOut w2=0xaa200000 → action=**TRAP** rsn=**0x54 = LOOK_UP_MISS**.

Test B (zero-windata catch-all — the "zero key" the prior session claimed forwarded):
- fill520 `03005044 fa11c000 00000608 80000000 00000049 0×10` → 520/520; ram2[0] byte-exact
  (windata region all zero, valid bit word3=0x80000000, action byte0x10=0x49 kept).
- 500-pkt flow: **cla_tx_fwd = 0 FLAT**; cla_tx_trp += 500 exactly; desOut w2=0xaa200000 →
  rsn **0x54 LOOK_UP_MISS**. IDENTICAL to Test A.

⇒ Correct-content and zero-content entries MISS identically at the computed slot with all 520
buckets filled and a clean stable key. **The compare is content-independent → STRUCTURAL.**

## STEP 4 — synthesis (definitive)

- **Why did the zero-key "match" before but the real key misses now?** It didn't — on a clean
  #456 boot the zero-windata catch-all ALSO misses (Test B). The earlier "zero-key forwarded"
  was a polluted-CLA-state / #444-build artifact (same conclusion as the extract-paradox note).
  On #456 there is NO content — correct, zero, or otherwise — that the lookup will match.
- **The second gate is the #452 hash-lookup-ENGINE regression at the bucket COMPARE/verdict.**
  The lookup demonstrably RUNS (acl_required climbs, desIn=FORWARD 0x49) but returns
  LOOK_UP_MISS (0x54) for any valid entry, even one present in all 520 internal buckets at the
  exact hashcalc slot. Ruled out this session: windata packing/content, slot, INTERNAL/EXTERNAL
  regime (confirmed INTERNAL), key volatility (rule 0x90 stable), valid bit (word3=0x80000000
  present). Consistent with the prior full-block CLA direct-register diff being byte-identical
  stock-vs-#452.
- **Exact next action:** the gate is NOT a settable CLA direct register and NOT entry content.
  It is an **init-OPERATION or a #444→#452 driver-code change**, most plausibly a per-bucket
  occupancy/valid structure the 15-word `zx_cla_write_hash` does not populate, OR a
  hash-lookup/search build/reset op the PM-ops/FFE-arm refactor dropped between #444 and #452.
  Two concrete moves (neither doable RAM-only from the live device):
  1. **Driver bisect #444→#452**: the PM-ops-bridge + FFE-arm refactor is the only delta; look
     for a reordered/dropped CLA hash-table build/reset/lookup-enable or an indirect-RAM init
     op (the boot `tm_pon_pp_cla_initial` does only get/set_config + outspace + oth_l3_action +
     mtu + api_lock — no hash-lookup enable/table-build; verify #444 did no more).
  2. **MMIO-trace stock's FFE trap→forward install** for the same 5-tuple and diff its
     write-set (esp. any per-bucket occupancy word / indirect-RAM op) against fill520 +
     ram0[9] — the compare verdict almost certainly depends on an occupancy/lookup-enable field
     that the raw 15-word entry write does not set.

---

## State left behind (device healthy, NO reboot)

- Device on **mainline #456**, alive, console REPL + UART bridge (:9998/:9999) up, rig intact.
- **ram0[9] RESTORED to 0x00150051** (readback-confirmed).
- ram2 hash banks hold the last test entry (zero-windata catch-all) — RAM-only, INERT (all
  LOOK_UP_MISS), clears on next DTR boot. No ram1 edits. All other access read-only (peek).
- Host NIC has both 192.168.1.50 (U-Boot TFTP) and 172.31.9.50 (rig). Restore/keep 192.168.1.50
  before any future DTR TFTP boot (tftpd binds 192.168.1.50:69). Did NOT reboot.
