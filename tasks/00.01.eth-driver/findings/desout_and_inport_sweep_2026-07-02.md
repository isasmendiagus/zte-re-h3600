# desOut latch + inport sweep → FIRST REPRODUCIBLE HW FORWARD (2026-07-02)

**Headline: cla_tx_fwd MOVED — 700 packets HW-forwarded 1:1 across four bursts,
verified all the way to the MAC4 (lan4/WAN) wire.** The gate was NOT the verdict
binding and NOT an inport *byte packing* problem: **the HW-extracted hash key is
ALL ZEROS** (no inport, no 5-tuple, nothing) under the driver's boot ram1 rule,
so any stored ram2 entry carrying real key content can never compare-match. A
ram2 entry whose key fields are all zero (windata=0, inport=0) HITS and the full
forward action chain (ram2 action → PM next-hop rewrite → lan4 egress) executes
flawlessly.

Same live boot as the two prior 2026-07-02 findings (banner `#456 Thu Jul 2
19:04:20 UTC 2026`, uptime continuous 22260→46180 s). All writes RAM-only via
driver debugfs. Rig unchanged (host 172.31.9.50 on lan2; flow UDP
172.31.9.50:50010 → 192.168.9.50:53, ~200 pkts/burst).

## TASK 1 — desOut: the classify OUTCOME latch (base 0x9238c39c)

5 independent read groups during a 450-pkt burst (paired with desIn):

| word | phys | flow value | behavior | decode |
|---|---|---|---|---|
| desOut[0] | 0x9238c39c | **0xaa200000** (miss regime) / **0xa4800000** (hit regime) / 0xa5b00000 idle | static per regime | **rsn = bits[29:23]**: 0xaa200000→**0x54 LOOK_UP_MISS**, 0xa4800000→**0x49 OTHERS/forward**, idle 0xa5b00000→0x4b |
| desOut[1] | 0x9238c3a0 | 0x82610841 | static during flow (idle 0x80010805) | mirrors desIn[3]; bit6 l3_en=1 |
| desOut[2] | 0x9238c3a4 | 0x00000e0c | static | ? |
| desOut[3] | 0x9238c3a8 | 0x00002a22 | static | ? |
| desOut[4] | 0x9238c3ac | 0xc1→0xcf→0xd8→0xdf→0xec | **changes EVERY read** (live) | rolling event counter/timestamp — proves latch liveness |
| desOut[5] | 0x9238c3b0 | 0x00d40000 | static | ? |

**THE MISSING MEASUREMENT, FOUND:** while desIn[2] stays 0xa4800000 (rsn 0x49,
"submitted, forward-grade"), desOut[0] during the miss regime = 0xaa200000 →
**rsn 0x54 LOOK_UP_MISS**. The earlier conclusion "the lookup does not even
miss" (from desIn alone) was wrong — desIn shows the INGRESS reason, desOut
shows the OUTCOME, and the outcome was a hash-compare miss all along.
When the matching entry is installed, desOut[0] flips to 0xa4800000 (rsn 0x49)
and stays there while cla_tx_fwd climbs.

**Bonus decode — `acl_required` 0x9238c3b8 halves:** hi16 = packets submitted to
classify; **lo16 = packets submitted AND trapped**. They tracked identically for
5000+ packets (every submit trapped) and diverged the instant forwarding began
(hi16 climbs, lo16 freezes). Live proof: 0x18d218d2 → 0x199a18d2 after the first
forwarded burst.

## TASK 2 — the HW-extracted key is EMPTY

gparsehashkey latch 0x9238c260..0x9238c28c (12 words), read twice mid-burst
(acl_required verified climbing 1:1 in the same window):

```
0x4c000000 00000000 00000000 00000000 00000000 00000000
0x00000000 00000000 00000000 00000000 00000000 00000000   (identical both reads)
```

Words 1..11 all zero; word0's 0x4c high byte is static across flow/idle (was
0x4b in the 06-28 session) — a status/sequence byte, not key content.
Decoded inport (bits[16:5] any packing) = **0**. Extra_data = **all zero**.

Cross-check via the STORED side (authoritative ram2 byte layout from stock
`cla_set_hash_table` decomp printks, decomp_all_tm.c:3399-3462, bytes LE per
word):

- **inport = (byte[0x0e]&0x3f)<<6 | byte[0x0d]>>2** → lives in WORD3, not
  word4. Installed entry word3=0x80000000 → stored inport = **0**.
- **byte 0x10 (word4 low byte) is NOT an inport byte.** 0x49 = 0b01001001 =
  bit6 `valid_en`=1 + low nibble `extr_index`=9 (the ram0[9] link). The
  briefing's "byte0x10=0x49 is the WAN inport" lineage was a misdecode.
  (Stock boot-table confirmation: regport3 L2 entries carry word3=0x…0c17
  → byte0x0d=0x0c → inport=3 ✓, word4 low byte 0x43 = valid_en+extr_index 3.)
- windata0..6 (u16 @ byte 0x13,0x15,…) of the installed entry = 0x0011 (UDP),
  0xac1f/0x0932 (172.31.9.50), 0xc0a8/0x0932 (192.168.9.50), 0xc35a (50010),
  0x0035 (53) — the 5-tuple was stored correctly all along.

**Actual vs stored inport: HW key inport = 0; historical entry stored inport = 0
too (word3). The tuple windata was the mismatch — stored 5-tuple vs extracted
zeros.**

## TASK 3 — sweep table (each: fill520 + clapeek-verify + 200-pkt burst)

| entry variant | word3 | word4 | w5..w7 | acl hi16 Δ | cla_tx_fwd Δ | cla_tx_trp Δ | desOut[0] |
|---|---|---|---|---|---|---|---|
| A1 inport=3 (real field) | 80000c00 | 11000049 | tuple | +200 | 0 | +214 | 0xaa200000 (0x54) |
| A2 inport=3 stock-style | 80000c17 | 11000049 | tuple | +200 | 0 | +217 | 0xaa200000 |
| briefed V=0x03 | 80000000 | 11000003 | tuple | +200 | 0 | +205 | — |
| briefed V=0x43 | 80000000 | 11000043 | tuple | +200 | 0 | +210 | — |
| briefed V=0x09 | 80000000 | 11000009 | tuple | +200 | 0 | +210 | — |
| briefed V=0x0b | 80000000 | 1100000b | tuple | +200 | 0 | +206 | — |
| briefed V=0x4b | 80000000 | 1100004b | tuple | +200 | 0 | +204 | — |
| **C zero-key** | **80000000** | **00000049** | **0** | **+200** | **+200** | **+6** | **0xa4800000 (0x49)** |
| C re-confirm | 〃 | 〃 | 〃 | +200 | **+200** | +8 | 0xa4800000 |
| T1 zero-key + inport=3 | 80000c00 | 00000049 | 0 | +200 | 0 | +213 | — |
| T2 zero-key + windata0=0x0011 | 80000000 | 11000049 | 0 | +200 | 0 | +~205 | — |
| C restored (final) | 80000000 | 00000049 | 0 | +200 | **+200** | +2 | 0xa4800000 |
| C + MAC4-wire check | 〃 | 〃 | 〃 | +100 | **+100** | — | — |

All entries share w0..w2 = `03005044 fa11c000 00000608` (action/PM binding) and
were installed in all 520 buckets. cla_tx_fwd total: 0 → **0x2bc (700)**.

**Wire proof:** MAC4 TX-ok counter 0x92300718 went 0x0dea → 0x0e4e = **+100 for
a 100-pkt burst** — the forwarded packets physically egress lan4/WAN with zero
CPU involvement. Host↔device lan2 ping unaffected throughout (to-me traffic is
never submitted to classify — acl_required climbed exactly 1:1 with the flow
only).

## VERDICT

1. **The verdict/action binding is NOT the gate and never was.** Given a
   compare-match, the CLA executes the ram2 action + PM chain perfectly
   (700/700 forwarded, correct egress port).
2. **No inport *byte* fixes it because the compare key is empty.** T1 proves the
   compare IS inport-sensitive (stored 3 vs key 0 → miss), and C proves the
   key's inport is 0. Same for the 5-tuple (T2: even one nonzero windata short
   → miss).
3. **The real remaining gap = KEY EXTRACTION.** The driver's boot ram1 rule
   (ram1[0x90] `22038608 000058a1 …`) submits packets with a null key: the
   winoffset/winmask windows extract nothing and the inport/outport mask flags
   (ram1 byte 0x39 bits5/4) don't join inport to the key. Stock forwarding
   presumably programs a real extraction rule per flow-type. Until that rule is
   replicated, per-flow discrimination is impossible — but a WORKING trap-all →
   forward-all toggle now exists.
4. Caveat for the current state: the installed zero-key entry is a **catch-all
   forward** — every classify-submitted (routed/l3_en) packet is HW-forwarded
   via PM next-hop idx 5 (lan4, MAC cc:29:bd:22:b4:2b). Fine on this diagnostic
   rig; must become per-flow before real use.

## Next steps (Stage 2b continuation)
- RE the ram1 rule fields that arm extraction: winoffset0..19/winmask0..19 +
  inport_mask/outport_mask (cla_set_extra_rule_table, decomp_all_tm.c:2870),
  and how ex_rule_id/ex_rule_mode feed the key {outport,inport,flags,extra_data}.
  Target: a rule that extracts proto/src/dst/ports so the key matches the
  stored windata layout above.
- Then per-flow entries become real: HW hash engine (0x9238c2c0/c2c4/c2fc)
  computes the slot from the now-nonzero key; clawrite ram2[slot].
- Driver work: bind zx_install_l3_recipe() to write the zero-key catch-all only
  as an explicit "offload everything" mode; per-flow needs the extraction rule.
- Re-examine the 06-28 aa9cfb17 one-off forward: almost certainly the same
  zero-key match (an entry with empty windata was present mid-session).

## State left behind (device healthy, NO reboot)
- Device on #456, console REPL + UART bridge alive, rig intact, host↔lan2 ping OK.
- Installed (RAM-only): **zero-key forward entry** `03005044 fa11c000 00000608
  80000000 00000049 00000000 00000000 00000000` in all 520 buckets (clapeek
  ram2[5] verified); ram0[9] word4 = 0x00150151 (bit8 set, from prior session —
  extraction is null regardless); PM ram1[5]/ram0[5]/ram6[5]/ram3[5] unchanged.
- HW forwarding is ACTIVE for routed transit flows (see caveat above).
- Final counters: cla_tx_fwd=0x2bc (700), cla_tx_trp=0x1bf4, acl_required
  hi16=0x1d84-ish/lo16 frozen at 0x1a64, MAC4 TX-ok 0x0e4e.
