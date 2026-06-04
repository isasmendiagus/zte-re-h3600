# Phase 6 / Stage 0b — LIVE stock HFF hardfast capture (GROUND TRUTH)

2026-06-04, branch phase6-hw-offload. Captured the EXACT CLA hardfast entries stock installs for a
real offloaded flow — the ground truth for Stage 2 (no more guessing the entry bit-layout).

## Setup (how we got stock to forward)
Stock is in HW-datapath mode: a manual `ifconfig eth0` does NOT forward (the WAN MAC TX path isn't
wired). Had to PROVISION the WAN via stock's web UI (192.168.1.1). Creds recovered from our own
`ext/config.bin` (decoded with tools/cfg_tool.py → tools/dtr-mod/ztetool.py; H3600 uses hardcoded AES
keys): **web admin = `admin` / `a3.141592A`** (DevAuthInfo AppID=1, Level=1). The WAN connection
**`capWAN`** = Enrutamiento (Route), static 10.9.9.2/24, gw 10.9.9.1 (our host enx6c70). After Apply,
stock created WAN iface **nbif2**, `default via 10.9.9.1 dev nbif2`, ARP of 10.9.9.1 REACHABLE.
(The other connection `WanConnection` = the real DIGI PPPoE, VLAN20 digiuser@digi — left intact.)
Test rig: LAN client = host enxc8a362e95900 192.168.1.50 (stock LAN), route 10.9.9.0/24 via
192.168.1.1; WAN ISP = host enx6c70cbb68169 in netns 'wan' = 10.9.9.1 (iperf3 -s). LAN→WAN verified
(ping ttl=63, routed) and an iperf TCP flow ran at ~331 Mbit/s → stock installed a hardfast.

## Install trace (kotrace_hff.ko on stock, /proc/kotrace_dump)
Per direction, the FFE install fires:
```
H hf_set_l3_entry(ptSession)
A zte_api_fast_l3_session_add(ptFastL3Session, result, dir)   dir: r2=1 fwd / r2=0xffffffff rev
C cla_set_hash_table(slot, entry)        slot r0 = 0x5a (fwd) / 0xfc (rev); entry ptr r1
I cla_set_indirect_rw_cmd(rw, word_idx, data)  per-word writes of the entry into the CLA
```
⇒ a flow installs **TWO** CLA hash entries (one per direction), both in **ram2** (slot < 0x100).

## The actual entries (read back from the chip via fpga, ram2)
flow fwd = 192.168.1.50:52811 → 10.9.9.1:5201 TCP ; rev = the return path (NAT'd via 10.9.9.2).
```
ram2[0x5a] fwd: 03005044 fa11c000 00000608 80000000 06000009 32c0a800 010a0901 51ce4b09 00000014  (+0…)
ram2[0xfc] rev: 03002044 fa11c000 00000608 80000000 06100029 010a0900 020a0909 4b145109 000000ce  (+0…)
```
(17 words each; words 9–16 = 0.)

## Field decode (initial — matched against the known 5-tuple)
- **word3 = 0x80000000** — bit31 = VALID/enable (both entries).
- **word4** = `06_00_0009` / `06_10_0029` — byte0 `06` = IP proto TCP; the rest = inport/outport +
  flags (fwd 0x09 vs rev 0x29 differ → direction/port).
- **words5–7** carry the 5-tuple, bit-packed (per tm_acl_get_fastHashRule shifts): src 192.168.1.50
  (c0 a8 .. 32), dst 10.9.9.1 (0a 09 .. 01), sport 0xCE4B=52811, dport 0x1451=5201 — all present,
  rotated. Reverse entry has the tuple swapped (0a 09 / and the NAT mapping).
- **word0** = 0x0300_5044 / 0x0300_2044 — action/result (egress + a field that differs by dir).
- **word1 = 0xfa11c000** (both) — action/policer/queue field (constant here).
- **word2 = 0x00000608** (both) — likely an ethertype/proto-class tag (0x0800 IP related).
- **word8** = 0x14 / 0xce — trailing tuple/hash byte.

## ⇒ Stage 2 plan (now grounded)
Replicate in mainline zx-dsa cls_flower_add: build a ram2 hash entry with word3=0x80000000 (valid),
word4 byte0=proto, words5–7 = the 5-tuple packed exactly as above, word0/word1 = the egress action,
and write it via the zx-dsa CLA primitive (priv->pp_regs, ram_id=2, slot) — using cla_set_hash_table's
addr→bank mapping. Verify: clapeek the slot back == our bytes, and hw_trap flat under iperf.
The exact bit-packing of words5–7 (and word0 action) = next: align tm_acl_get_fastHashRule (tm.c:49213)
against these concrete entries to pin each field. We now have 2 reference entries to validate against.

## Entry FORMAT decoded (tm_acl_get_fastHashRule tm.c:49213-49465 + matched vs the 2 captured entries)
The entry `param_4` is a LITTLE-ENDIAN byte array (~0x39 bytes = the 15-word ram2 slot). fpga reads it
as 32-bit words (BE display) → to map: LE byte offset = stream index of [w&0xff, w>>8, w>>16, w>>24].
Two regions:
- **Header/action/match-meta (bytes 0x00–0x12)**, built lines 49312-49421:
  - byte0: flags (bit6=0x40 set, bit2, + session+0x18 low 2 bits). 
  - **bytes 1–2: EGRESS target uni/port** — `uVar10` from the switch on session+0xb2 (uni 0..7 → 1..7);
    `param_4[2]=uVar10>>4`, `param_4[1]=(param_4[1]&0xf)|((uVar10&0xf)<<4)` (dir==1 route case, 49410-411).
  - byte3 = `(param_3&0x7f)<<1 | 1` (priority/rule id).
  - bytes4–9: proto/len/flags (param_4[4]=param_3 hi; byte6 inport/outport bits from session+0xb0/0xb1;
    byte8 |8). **proto** (06=TCP) lands in this region (seen as word4 byte0 in the entries).
  - bytes 0xb–0xc: inport (session+0xb0 << shifts). byte0xe/0xf: a field (session+0x10 << 6 / >> 2).
  - **valid**: the captured word3=0x80000000 ⇒ the enable/valid bit is the top bit of that word region.
- **5-tuple (bytes 0x13–0x37)**, built lines 49445-49464 (fwd, param_1!=0):
  - bytes **0x15–0x18 = `*(session+0x64)`** (IP A, byte-swapped into two ushorts @0x15,0x17).
  - bytes **0x19–0x1c = `*(session+0x6c)`** (IP B).
  - bytes **0x1d–0x20 = `*(session+0x74)`** (ports, src+dst packed).
  - byte 0x13 = `*(session+0x60)>>16` (a tuple/hash byte). (param_1==0 bridge path 49422-442 writes the
    full MAC/v6 set instead.)
Cross-check vs ram2[0x5a]: sport 0xCE4B is byte-aligned at LE-stream offset 29 (=0x1d ✓ ports region);
src 192.168.1.50 / dst 10.9.9.1 bytes appear in the 0x15–0x1c region (bit-rotated as the ushort packing
predicts). Reverse entry 0xfc has the tuple swapped + the NAT mapping (10.9.9.2).

## ⇒ Stage 2 implementation options (both now concrete)
A) **Verbatim replay (fastest proof):** write the EXACT captured 17 words to mainline CLA ram2 slot 0x5a
   via the zx-dsa primitive, reproduce the EXACT flow (src 192.168.1.50:52811 → dst 10.9.9.1:5201 TCP,
   same in/out port mapping), and check hw_trap goes flat. Proves "writing this CLA entry ⇒ HW forwards"
   with ZERO bit-packing risk. Then parameterize.
B) **Parameterized build:** implement the byte layout above in cls_flower_add (egress uni in [1][2],
   proto in the byte4-9 region, valid bit, IPs at 0x15/0x19, ports at 0x1d from the flow_rule match),
   write via zx_cla_write_entry(ram2, slot). Validate the produced bytes == a captured entry for the
   same tuple before trusting it.
Recommended: A first (de-risks the "does a CLA hash entry actually override the trap?" question with a
known-good entry), then B.

## UPDATE 2026-06-04 — FULL hardfast trio captured (ram0+ram1+ram2)
flow #2 = 192.168.1.50:46063 → 10.9.9.1:5201 TCP. Install (kotrace) wrote ram2[0x35] fwd / ram2[0x0c]
rev + ram1[0x98] + ram0[0x09]. ram1/ram0 addrs are the SAME across both captured flows ⇒ FIXED shared
infra; only the ram2 slot changes (= hash of the 5-tuple). Full entries (fpga read, 17 words):
```
ram0[0x09] (extract-index, FIXED): 93929190 97969594 9b9a9998 9f9e9d9c 00150051 0...   (which packet
   bytes form the hash key: extract_index0..15 = 0x90..0x9f ascending; 0x00150051 = ext_mode/len)
ram1[0x98] (rule TCAM IP, FIXED):  22038608 000058a1 00000000 00000000 f00ff000 ffffffff ffffffff
   0fffffff 0 0 0 0 0 0 00700000 00092492 0   (matches IP, points into the hash; ~= boot ram1 entries)
ram2[0x35] (fwd hash result):      03005044 fa11c000 00000608 80000000 06000009 32c0a800 010a0901
   51b3ef09 00000014 0...   (sport 0xB3EF=46063 at word7 ✓; same shape as the 0x5a capture)
ram2[0x0c] (rev hash result):      03002044 fa11c000 00000608 80000000 06100029 010a0900 020a0909
   ef145109 000000b3 0...
```
⇒ **To offload a flow on mainline: ensure ram0[0x09]+ram1[0x98] exist (infra — check the boot table),
then write ONE ram2 entry at the flow's hash slot.** The slot = hash(5-tuple) via the ram0 extract +
the CLA hash poly (cla_get_hash_poly_config) — still need that to compute a slot for an arbitrary flow,
OR craft a flow with a known sport so it hashes to a captured slot (verbatim replay).
NOTE: stock forwards LAN→WAN with ip_forward=0 (HW/FFE forwards, TTL decremented) — the chip routes,
not the CPU. This is precisely the offload we want.
OPEN (carry): clawrite ram2 persisted only word0 — likely mainline's zx_cla_write_entry ram2 path
(U-Boot loaded the live ram2 we read, mainline never wrote ram2 successfully). Fix the data-write.

## ✅ RESOLVED 2026-06-04 — CLA hash WRITE protocol cracked + verified on mainline
kotrace of cla_set_indirect_rw_data during a live install gave the EXACT sequence:
`cla_set_indirect_rw_cmd(rw=0, ram_id, addr)` FIRST, then `cla_set_indirect_rw_data(data_id, value)`
for data_id **DESCENDING** (word[n-1]..word[0]); nwords=15 for ram2-6, 17 for ram1. word0 is written
LAST. The old driver did data-FIRST + ascending → only word0 stuck.
Fix: added `zx_cla_write_hash(e, ram_id, addr, data, nwords)` (zx-eth-main.c) = CMD-first + descending
write; clawrite routes ram1-6 through it (nwords 17 for ram1, 15 for ram2-6). VERIFIED on mainline:
`clawrite 2 5a <captured fwd entry>` → clapeek ram2[0x5a] reads back the FULL entry
`03005044 fa11c000 00000608 80000000 06000009 32c0a800 010a0901 51ce4b09 00000014` (all words persist,
not just word0). The write primitive now works — Stage 2's blocker is cleared.
NEXT: write the full trio ram0[0x09]+ram1[0x98]+ram2[slot] in mainline + reproduce the flow (netns rig,
bound sport→captured slot) → pipeline_stats/hw_trap FLAT = HW forwards. Then parameterize in cls_flower_add.
