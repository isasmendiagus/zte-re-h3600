# Phase 4 COMPLETE — Ping bidi working (2026-05-24)

## TL;DR
After ~14 commits over a single session, mainline `zx279128-eth.c` driver
on ZTE H3600 (ZXIC ZX279128S) achieves bidirectional ping with the host.
Total session change: from "boot silently hangs after FPGA IRQ enable" to
"`64 bytes from 192.168.1.99: icmp_seq=3 time=16.2 ms`".

## Final test result
```
$ ping -c5 192.168.1.99
PING 192.168.1.99 (192.168.1.99) 56(84) bytes of data.
From 192.168.1.50 icmp_seq=1 Destination Host Unreachable
From 192.168.1.50 icmp_seq=2 Destination Host Unreachable
From 192.168.1.50 icmp_seq=3 Destination Host Unreachable
64 bytes from 192.168.1.99: icmp_seq=3 ttl=64 time=16.2 ms
64 bytes from 192.168.1.99: icmp_seq=3 ttl=64 time=17.9 ms (DUP!)
64 bytes from 192.168.1.99: icmp_seq=3 ttl=64 time=19.5 ms (DUP!)
64 bytes from 192.168.1.99: icmp_seq=3 ttl=64 time=21.3 ms (DUP!)

5 packets transmitted, 3 received, +70 duplicates, 40% packet loss

$ ip neigh | grep 192.168.1.99
192.168.1.99 dev enxc8a362e95900 lladdr f4:f6:47:0f:42:64 REACHABLE
```

## The journey (14 commits)

1. **99b75df91 — RED queue init (zx_tm_red_init)** unlocked TM IRQs
   (count 0 → 19M). RED queue config in plat-zxylzb's
   pon_tm_red_init gates the RX/TX-done events on TM[0x100] bits 0/1.

2. **cac2d93ba — RX delivery (TM[+0xF0] re-write)** — bulk fpga.bin
   replay was overwriting our rxdesc_dma with stock DDR pointer
   0x4ff1f000. Re-write after replay. tm_rx_count 0 → 1.6M.

3. **b1c9ea4d0 — loopback filter** — switch reflects CPU TX back; drop
   packets where src MAC == sw_dev MAC.

4. **81a0ed50a — RX frame at BP+0x10** — diagnostic dump revealed HW
   prepends 16-byte metadata header to BP buffer. Frame actually starts
   at bp_buf + 16. Without this fix kernel saw zero bytes.

5. **c33b7557d** — loopback filter validated, TX stays at +0.

6. **57fbfbd04 — PP bridge init (13 regs)** — ported pon_pp_brg_init.

7. **8e2554fb1 — VLAN0/1 + port6/7 isolate** — additional bridge init.

8. **f23696571 — PP ctrl init** — pp[0x28] + pp[0] + 52ms delay.

9. **11a5317e3** — TX_UP/DN_BASE re-write after replay (later refined).

10. **f1f3c6402** — skip desc bases in bulk replay (cleaner approach).

11. **a5e56c8d4 — TX desc[11] = 0x01** (not 0x20) — RE'd from stock
    pon_tm_net_tx. The VALID bit is at bit 24, we had it at bit 29.

12. **a3e6a8017 — TX desc[2..3] egress port — PING BIDI** — THE final
    fix. Without this field set to `((port+0x28) & 0x3f) << 4`, switch
    had no idea where to send the packet → loopback. With port=0 hard-
    coded, switch routes to LAN port 0 → reaches host.

## Process highlights

- **Used kotrace runtime trace + Ghidra static disasm**: combined approach
  to RE plat-zxylzb's TX path (pon_tm_net_tx + pon_tm_data_raw_send).
- **Bisected hang via CKPT prints**: dense logging in bulk replay loop
  pinpointed exact offset (0x80000) that hangs the AHB bus → led to
  whitelist approach for replay.
- **Diagnostic BP buffer dump**: 40-byte hex dump in napi_poll revealed
  the +0x10 offset for RX frames.
- **Independent stock vs mainline comparison via UART REPL + sshd**: had
  shell on both stock (sshd) and mainline (C-init REPL via TCP bridge),
  enabling live comparison of /proc/interrupts, register reads, etc.

## What's NOT done

See `tx_rx_paths.md` "Known artifacts / open work" for the full list.
Quick: DUPs/loss from hardcoded port 0, looser TM init (only 4/16 instances),
hardcoded qid=0, etc. Driver is *functional* not *production-grade*.
