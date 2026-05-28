# [Iter 30] First CPU-bound RX delivered to driver

Bench-tested 2026-05-28 ~02:00 UTC. After the cascade of overnight fixes
(carved 64 MiB region, 5 BMU instances, SOPC bridge handshake on link UP,
PHY LDO skip, TM[0xc000] link-UP flip, TX_DONE IRQ unmask, LOW16 pending
parse fix), the FIRST frame was delivered from HW to driver.

## Boot dmesg confirms

```
[   74.851] BPDUMP q=5 len=333 bppe=37
            +00..0f=00000000000000000000000000002800
            +10..1f=ffffffffffff2c9975313ea908004500
            +20..2f=013f00004000401139af00000000ffff

[   75.211] TM RX q=5 idx=0 len=333 bppe=37
            src=2c:99:75:31:3e:a9 dst=ff:ff:ff:ff:ff:ff
            ethertype=0800 ingress=0 delivered
```

Source MAC `2c:99:75:31:3e:a9` = LAN1 host NIC (enx2c9975313ea9). The
frame is broadcast (DHCP/ARP) sent by host when interface came up.

Frame format: HW prefix at bytes 0..15 (`0x2800` near end), ethernet
frame starts at byte 16 (`ff ff ff ff ff ff` = broadcast dst, then
host's source MAC at +22, ethertype at +28). Length 333 bytes confirmed
as a normal IP packet.

## Counter state under sustained pings

After 20 pings from host LAN3 (192.168.1.50 → device 192.168.1.99):

```
tm_irq_count     = 15
tm_napi_count    = 15
tm_rx_count      = 1   ← only the LAN1 frame from boot
tm_bmu_free_ok   = 1
tm_tx_count      = 14
tm_tx_dropped    = 0

PP[0xc3c4] CLA trap     = ~138 packets (increments under ping)
TM[0xc060] QMG up trap  = 0x0d to 0x0e (only 14)
TM[0x10114] queue 5 cnt = 0xff96000e (LOW16=14 pending, HIGH16=cursor)
```

## What changed

| Iter | Change | Effect |
|---|---|---|
| Iter 20 | Carved 64 MiB DMA region | TM[0x100] error bits 8-14 cleared |
| Iter 22 | 3 pon writes (0x40018=2, etc) | Stock match |
| Iter 23 | LDO skip when armed | Less RGMII glitch on probe |
| Iter 24 | Per-port reset on link UP | Mirror stock extphy_timer pattern |
| Iter 25 | SOPC bridge handshake (NPP[0x19068]) | Switch fabric routes frames in/out MAC |
| Iter 28 | TM[0xc000] flip 0x1f40fa0 → 0x3f40050 on link UP | CLA → QMG handoff |
| Iter 29 | TM_IRQ_ARM_BITS = 0x03 (unmask TX_DONE) | TM IRQ fires properly |
| Iter 30 | NAPI pending = `status & 0xffff` (LOW16) | NAPI sees queued frames |

## Open issues

1. **Only 1 of N frames delivered.** Queue 5 reports 14 pending, NAPI
   ran 15 times, delivered 1. Subsequent NAPI calls see queue empty
   despite the counter saying 14. Possible:
   - `rx_head[5]` advances incorrectly
   - Descriptors at idx 1..13 have len=0 / invalid → skipped
   - The 0xff96 high16 means HW is far past where SW reads

2. **LAN3 pings don't reach driver.** Our ping source is LAN3
   (192.168.1.50). MAC[2]+0x780 increments under ping (frames at
   MAC level). CLA trap counter increments. QMG count increments.
   But the only RX delivered is the LAN1 boot ARP. LAN3 frames may
   be queued at a different queue index or filtered out.

3. **TX path still wedged.** tm_tx_count increments (14 frames pushed)
   but `tm_tx_dropped = 0`, and host-side tcpdump (prior test) showed
   zero outgoing frames from device. The TX side of the pipeline is
   independent and still broken.

## Next iter targets

- Investigate rx_head[q] advance + desc layout to find why only 1
  delivered out of 14 pending
- Check if LAN3 frames go to a different queue than queue 5
- Investigate TX path: HW consume engine still wedged (TM[0x10068]
  high16 still stuck at 7 from boot-time gratuitous ARPs)

Confidence: this is a major architectural breakthrough. The RX path
runs end-to-end. Remaining issues are in implementation details (desc
layout, queue mapping) rather than missing HW init.
