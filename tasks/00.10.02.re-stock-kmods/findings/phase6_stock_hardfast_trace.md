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
