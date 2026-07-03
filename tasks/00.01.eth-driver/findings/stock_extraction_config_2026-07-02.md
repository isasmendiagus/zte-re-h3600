# STOCK CLA hash-key EXTRACTION config — LIVE capture while HW-forwarding (2026-07-02)

## Headline (overturns the task hypothesis)

Captured the STOCK firmware's CLA hash-key extraction **while it was HW-forwarding a
real NAT'd internet download**. Stock's extracted key (`gparsehashkey`) carries the
**full real 5-tuple** — but **the extraction RULE config, ram0 index table, ex_rule_id
header, and every CLA config register are BYTE-IDENTICAL to mainline's**. The task
premise ("stock programs a different extract rule; mainline's rule is null") is
**refuted**: the config is the same on both. The mainline empty-key is therefore NOT a
missing/wrong extraction-rule field — it is a **dynamic packet-parse difference** (see
Synthesis). There is **no ram1 winoffset/winmask/inport_mask value for mainline to add**;
it already has them.

## Environment / method

- **Confirmed STOCK**: `Linux H3600 V9 4.1.25 #2 SMP Thu Feb 17 18:29:32 CST 2022 armv7l`
  (mainline was `6.6.0 #456`). Booted by DTR power-cycle + passive wait → U-Boot 2013.04
  autobooted NAND (`root=/dev/mtdblock8 ro jffs2`). `/bin/fpga` + stock userland present.
- **HW-forward flow established (allowed "use the WAN by routing a download"):** attached
  a macvlan on the ZTE-LAN host NIC (`enxc8a362e95900`) into the local incus container
  `dev` (IP 192.168.1.200), added a /32 route `80.249.99.148 via 192.168.1.1`, and ran a
  looping `curl` of `http://ipv4.download.thinkbroadband.com/1GB.zip` → LAN→WAN transit
  through the ZTE, NAT'd out the owner's real WAN. **WAN never reconfigured**; left exactly
  as-found (`default via 10.44.66.250 dev nbif1 src 10.44.66.222`, internet still up).
  Cleanup: download killed, macvlan removed, device `/tmp` helpers removed.
- **HW-forwarding CONFIRMED**: `cla_tx_fwd` (fpga widx `0xe30f0` / phys `0x9238c3c0`)
  climbed `0x0 → 0x5e32 → 0xf24a → …` (wrapped the 16-bit counter — tens of thousands of
  packets HW-forwarded) during the download. Baseline before flow = `0x0`.
- Read recipe: stock `fpga -r`/`fpga -w` via `/dev/logger_main` capture (per
  stock_ffe_live_install_capture). CLA indirect: CMD widx `0xe3005` (phys 0x9238c014) =
  `addr|(ram_id<<22)|(rw<<27)`, DATA widx `0xe3007` (phys 0x9238c01c). Ring re-streams
  history → LAST occurrence per session used.

## A. gparsehashkey latch (STOCK, forwarding) — the NON-EMPTY key

Phys `0x9238c260` (widx `0xe3098`), 12 words, stable across 4 reads:

```
4c000000 8150000c a1f20391 10f8c728 000000a1 00000000 00000000 00000000 00000000 00000000 00000000 00000000
```

Decode (bit layout cross-validated against the 06-28 known-good key→tuple:
**LE bytes, LSB-first bit order, extra_data stream starts at bit offset 1, 16-bit LE fields**):

- word0 `0x4c000000`: header byte 0x4c → `ex_rule_id = 0x98`; inport(baked)=0, outport=0.
- extra_data (words1-4): **proto=0x06 (TCP), src=192.168.1.200, dst=80.249.99.148,
  sport=34940, dport=80** = the LAN→WAN (pre-NAT, upstream) packet of the download. ✔ real
  5-tuple, byte-for-byte.
- A second read caught a different in-flight packet: `4c000000 a1f2000d 1458c728 00a085bc
  000191e0` → **proto TCP, src=80.249.99.148:80, dst=10.44.66.222:51440** = the WAN→LAN
  (post-NAT, downstream) direction. Also a full real 5-tuple.

**Contrast with mainline** (findings/desout_and_inport_sweep_2026-07-02.md): mainline's
gparsehashkey = `4c000000 00000000 …` — **identical word0 header (0x4c000000 → same
ex_rule_id 0x98), but words1-11 ALL ZERO**. Same header/rule selected, opposite extraction
result.

## B. Active CLA ram1 extract rule(s)

The selected rule is `ex_rule_id = 0x98`. Read ram1 at 0x90 and 0x98 (17 words each):

**ram1[0x90] == ram1[0x98]  (BYTE-IDENTICAL to each other):**
```
22038608 000058a1 00000000 00000000 f00ff000 ffffffff ffffffff 0fffffff
00000000 00000000 00000000 00000000 00000000 00000000 00700000 00092492 00000000
```
This matches mainline's boot rule ram1[0x90] `22038608 000058a1 …` on record — **identical**.

Decoded (`cla_set_extra_rule_table` fields):
- **winoffset[0..6] = {8, 12, 14, 16, 18, 20, 22}** (7 bits each @ bit 7·N). IP-header-relative
  byte offsets → {proto@8/9, srcIP@12-15, dstIP@16-19, sport@20-21, dport@22-23}.
- **winmask[0] = 0x00ff** (masks TTL byte off, keeps proto byte); **winmask[1..6] = 0xffff**
  (full 16-bit). (@ bit 140 + 16·N; region words4-7 `f00ff000 ffffffff ffffffff 0fffffff`.)
- **offset_type[0..6] = 2 (all)** — every window is **L3-header-relative** (word15
  `0x00092492` = 3-bit fields all == 2). ← key mechanistic detail (see Synthesis).
- byte 0x39 (word14 `0x00700000` → byte0x39=0x70): **inport_mask=1 (bit5), outport_mask=1
  (bit4)**, bit6=1.
- So the rule extracts exactly {proto, srcIP×2, dstIP×2, sport, dport} = the 5-tuple,
  anchored at the parsed L3 header.

## C. CLA ram0[9] (extra_index_table entry + index_valid)

Read ram0 addr 9 (5 words):
```
93929190 97969594 9b9a9998 9f9e9d9c 00150151
```
- words0-3 = extract_index bytes **0x90,0x91,…,0x9f** (sequential; the 16 candidate ram1
  rule addresses).
- word4 `0x00150151`: **index_valid = low16 = 0x0151** → bits {0,4,6,8} set →
  enabled rules = extract_index[{0,4,6,8}] = ram1 addrs **{0x90, 0x94, 0x96, 0x98}**.
  HW picked **0x98** for this TCP flow.
- **Identical to mainline** (mainline ram0[9] word4 = 0x00150151 on record).

## D. CLA config block (0x9238c000..0x9238c0ff) — all non-zero regs

```
0x9238c080 (idx5/mac_req_ctrl) = 0x00000600
0x9238c088                      = 0x00007fff
0x9238c090 (hash poly)          = 0x00e400e4
0x9238c094 (outspace_cfg)       = 0x00000004   (space_sel=0, hash_num=1)
0x9238c098                      = 0x7fff7fff
0x9238c09c (local_ipv4)         = 0x00000000   (unused, as in 06-24)
0x9238c0c8                      = 0x00000001
0x9238c0d0                      = 0x00000001
0x9238c0d4                      = 0x00000007
```
All other words in 0x9238c000..0x0ff read 0 (excluding the indirect CMD/DATA ports at
0x9238c014/01c which show read residue). **Every value matches the mainline #452 fullblock
dump byte-for-byte** — including outspace=0x4 (not 0x8). No config-register difference.

## E. Live FFE-installed ram2 forward entry (bonus)

While reading, the CLA indirect port held a **live FFE write to ram2[0x99]** (CMD residue
`0x00800099` = ram2 addr 0x99, rw=0=write). Clean re-read of ram2[0x99] (17 words):
```
2b003044 fa11c000 00000608 80000000 06100069 9450f900 de0a2c63 2c005042 000000eb 0 0 …
```
Decode (06-24 ram2 layout; windataN = LE16 @ byte 0x13+2N): word3=0x80000000 VALID;
**proto=TCP(byte0x13=0x06); src=80.249.99.148; dst=10.44.66.222; sport=80; dport(NAT)=
0xeb2c=60204** = the downstream (WAN→LAN, post-NAT) direction of the download. word4 byte0x10
toggles 0x69↔0x29 (dir/HW-hit-age bit) between reads. (The upstream-direction entry lives at
the hash of the upstream key; not separately located this session — matches the 06-24
capture of the fwd/rev entry pair.)

## Synthesis — what actually differs, and what mainline must do

**Stock's extraction rule is IDENTICAL to mainline's** at every level captured:
- ram1[0x90]/[0x98] rule bytes: identical.
- ram0[9] index_valid (0x0151 → rules {0x90,0x94,0x96,0x98}): identical.
- gparsehashkey word0 header (0x4c000000 → ex_rule_id 0x98): identical.
- all CLA config regs (poly, outspace=0x4, mac_req_ctrl=0x600, …): identical.

Yet stock's key = full 5-tuple, mainline's = all zero. **Therefore the gap is NOT the
extraction-rule config** — the minimal ram1 winoffset/winmask/inport_mask "mainline must add"
is **none; it already has the correct rule** (winoffset {8,12,14,16,18,20,22}, winmask
{0x00ff,0xffff×6}, offset_type=L3-relative, inport_mask=outport_mask=1).

The decisive mechanistic clue is **offset_type = 2 (L3-header-relative) for all 7 windows**:
the extract engine reads the packet bytes at offsets measured **from the parsed L3-header
pointer**. Stock's packets are genuine NAT'd routed transit that the DPA/parser fully
classifies as IPv4 → the L3 anchor is valid → the identical windows land on the real IP/L4
header and pull the 5-tuple. Mainline extracted zeros with the SAME rule ⇒ its packets
reached the extract engine **without a valid parsed L3-header anchor** (the windows read a
null/OOB base → zero), even though a coarse `l3_en` descriptor flag was set.

**Direction for the mainline port (config-negative, dynamic-positive):**
1. Stop hunting the ram1 extraction rule — it is already correct/identical. Do not add or
   change winoffset/winmask/inport_mask.
2. The mainline empty-key is a **parse-anchor / flow-genuineness** problem. Either
   (a) mainline's test packets weren't genuine L3-parsed routed transit (the recurring
   "test a truly routable flow via the real WAN nexthop" caveat — this capture used exactly
   such a flow on stock and it worked with the stock-==-mainline config), or
   (b) the DPA/parser on mainline isn't publishing the L3-header offset the extract engine
   anchors on. Verify on mainline: with a genuinely-routed established flow, does
   gparsehashkey populate? If still zero, chase the DPA L3-offset/parse-result feeding the
   extract engine (offset_type=2 anchor), NOT the CLA ram1/ram0/config.
3. Once the extracted key is non-zero, per-flow ram2 entries (correct 5-tuple windata) will
   compare-match and HW-forward — the whole downstream chain is already proven working with
   the zero-key catch-all.

## State left behind
- Device on **STOCK** (normal NAND firmware) — healthy, WAN untouched (as-found), internet up.
- No NAND/flash writes; no WAN reconfig. Host: macvlan removed, container `dev` restored to
  eth0-only, download stopped. Device `/tmp/rd.sh /tmp/clard.sh /tmp/r.bin` removed.
- All device register access was read-only except the standard CLA indirect read-command
  writes (rw=1 read of RAM) and the `0x73000` warmup — no data/config modified.
```
