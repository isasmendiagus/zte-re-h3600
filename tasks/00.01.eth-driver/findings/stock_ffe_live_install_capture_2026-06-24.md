# Stock FFE HW-forward install — LIVE capture (2026-06-24)

Captured from a STOCK ZTE H3600 actively HW-forwarding a routed/NAT'd internet flow (user's real
modem on the WAN jack = 10.44.66.250; LAN client 192.168.1.50 → internet through the ZTE). This is
the dynamic per-flow install we've been hunting — the thing mainline never does.

## FFE engagement rule (IMPORTANT)
The FFE installs a HW hardfast (ram2 + PM) **only for a sustained, kernel-conntrack-ESTABLISHED bulk
TCP connection**. DNS/UDP, ICMP ping, short curls, and raw hping3 SYN streams are all CPU-TRAPPED
(climb cla_tx_trp 0xe30f1, NOT cla_tx_fwd 0xe30f0). What engaged it: a long-lived bulk HTTP download
(curl of a 200MB+ file) to a CDN host routed through the ZTE. cla_tx_fwd climbed
0xa424→0xa655→…→0xf3ae→wrapped (tens of thousands of HW-forwarded pkts); cla_rx_fwd (0xe30f3) in
lockstep.

## Read recipe (reproducible; stock has `fpga -w`)
```
(cat /dev/logger_main > /tmp/r.bin &) ; fpga -r 0x73000 1            # warmup
# CLA ram2 read: CMD widx 0xe3005 = addr|(ram_id<<22)|(rw<<27), rw=1=read ; DATA widx 0xe3007 (read 17)
fpga -w 0xe3005 <cmdval> ; fpga -r 0xe3007 17
# PM read NEEDS the DONE poll: CMD 0x77005 (=0x921dc014), DONE 0x77006 (poll==1), DATA 0x77007
fpga -w 0x77005 <cmdval> ; fpga -r 0x77006 1 ; fpga -r 0x77007 4
killall cat ; grep -aE "fpga read:" /tmp/r.bin
```
cmd packing: CLA `addr|ram_id<<22|rw<<27`; PM `addr + ram_id*0x400000 + rw*0x8000000`.

## THE LIVE FORWARD ENTRY — CLA ram2[0x2f] (15 words)
```
3d005044 fa11c066 00000608 80000000 06000049 32c0a800 9450f901 50a97263 0 0 0 0 0 0 0
```
Decode (matches device conntrack exactly):
- word3 = 0x80000000 = VALID (bit31).
- **proto = entry byte 0x13 = 0x06 (TCP)** — NOT byte 0x09. (byte0x09=0x06 is a constant IPv4/ethertype-class tag `0x0608`.)
- src_ip bytes 0x15..0x18 = `a8 c0 32 01` = **192.168.1.50** (the corrected per-16-bit-short IP packing, confirmed live).
- dst_ip bytes 0x19.. = `94 50 f9` → **80.249.99.148** (NAT'd internet dst).
- sport 0x1d = 0xa972 = 43378 ; dport 0x1f = 0x0050 = 80.
- egress gemport_uni_id (bytes1/2) = 5.
- cmd_flow_id = (byte4<<7)|(byte3>>1) = 0x66<<7|0x3d>>1 = 13086 (rule/flow id; does NOT directly index PM ram0).
- word4 dir/inport byte = 0x09 ↔ 0x49 (the documented +0x40 inport bit; toggled between re-reads).
word0/1/2/3 (`3d005044 fa11c066 00000608 80000000`) match the prior stock template (`phase6_stock_hardfast_trace.md`) and `phase6_cla_keybuilder_SPEC.md` BYTE-FOR-BYTE → the key-builder/entry layout GENERALIZES (validated on a new proto/dst/NAT class).

Per-flow-varying bytes only: 0x03/0x04 (rule/cmd_flow_id), 0x10 (dir/inport), **0x13 (proto)**, 0x19-0x1c (dst_ip), 0x1d-0x1f (ports). src_ip (0x15-0x18) constant across LAN-side flows. ⇒ slot = hash & 0xff (internal way-0); every distinct 5-tuple gets its own ram2 slot. Also captured ~60 valid UDP/DNS entries (word4=`11000009`, byte0x13=0x11) + 4 portless infra entries (boot-time per-inport classifier, incl. a0x21=inport regport2).

## PM flow_info (ram0) — paired with the ram2 entry
PM reads work WITH the DONE poll. flow_info (ram0) populated:
- ram0[0x003] = `00000005 0 0` (fwd flow_info; word0 = next_hop_idx-ish, small int)
- ram0[0x403] = `00000007/00000001 0 0` (rev flow_info; 0x3/0x403 = the fwd/rev pair pattern from prior groundtruth)
- ram0[0x00..0x07] word0 = 3,6,2,5,2,5,1… (per-flow next_hop_idx pointers)

## OPEN ITEM — PM next-hop ram1 not surfaced
PM ram1[0x00..0x40] read ALL ZERO (word0..2); PM DATA4-7 (0x1DC100) returned stale identical content
across entries (`00000020 0 1 1`). So this fpga recipe only reliably returns PM DATA0-3 / flow_info
word0. The next-hop MAC (dst-host MAC for the L3 rewrite) was NOT captured — either it's at a ram1
index > 0x40 or needs a DATA-latch step the recipe lacks. Prior single-hop groundtruth had
ram1[4]/[5] = host MACs (`…62e95900 …0000c8a3`), so the FORMAT is known; just not re-captured here.

## Other state
- CLA local_ipv4 (0xe3027) = 0 (stock doesn't use it here).
- ONU-MAC table (0x75048+) populated: 470f4264/0000f4f6, ...4265, ...4266, ...4267 (per-port MACs).
- **Headline diff vs mainline:** stock's ram2 is full of valid FFE-installed forward entries (1 HTTP
  TCP + ~60 DNS UDP + 4 infra); MAINLINE never installs ANY ram2 forward entry → that is exactly why
  mainline reads cla_fwd=0. The gate isn't a static register — it's the per-flow FFE install (ram2 +
  PM flow_info + next-hop), which only fires for matured/established flows.

## Implications for the mainline port
1. The mainline offload install must write: CLA ram2 entry (corrected layout, proto at byte 0x13) +
   PM ram0 flow_info + PM ram1 next-hop, linked. The driver's current cls_flower hook writes ram2 but
   the PM flow_info/next-hop linkage + proto-byte position need to match this capture.
2. The trigger must be a MATURED/ESTABLISHED flow (Linux conntrack / nf_flow_table TC_SETUP_FT), not a
   manual one-shot — stock only HW-offloads established bulk TCP.
3. OPEN (must verify on mainline): does writing the FULL install (ram2+PM ram0+ram1) make mainline's
   acl_required + cla_tx_fwd climb? The earlier slot-sweep (ram2 ALONE) did not. This is the next test.
