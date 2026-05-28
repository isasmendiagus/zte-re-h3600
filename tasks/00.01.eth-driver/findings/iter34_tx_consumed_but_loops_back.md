# [Iter 34] TX descs consumed by HW, frames loop back to CPU (no egress)

Post-iter34 bench (revert Iter 32 + Iter 33 drop post-kick clear):

## Counters

```
TM[0x10054] UP kick    = 1 (stuck — HW never clears)
TM[0x10050] UP base    = 0x4FFDF000 ✓ (carved match)
TM[0x1005c] UP cursor  = 0x001A001A (HIGH=write_ptr=26, LOW=read_ptr=26)
TM[0x10058] UP done    = 0
tm_tx_count            = 17
tm_rx_loopback_drops   = 32 (each TX loops back at least once)
host tcpdump          = 0 frames from device MAC
```

## Decoded TX desc bytes (verified vs stock)

```
desc[0]    = 0xc9    CPU/source marker ✓
desc[1]    = 0x00
desc[2..3] = 0x02c0  egress port hint = (lan_up_port=4 + 0x28) << 4 ✓
desc[4..7] = 0x4a010000   byte 6=1, byte 7=0x4a (bp=0x25=37 = bp_idx<<1)
desc[8..11]= 0x21 00 b4 00   byte 11=0x21 (VALID|0x20) ✓
desc[12..13]= 0x0168   len = 0x168/4 = 90 bytes ✓
```

All byte-for-byte correct vs stock decomp.

## Behavior

HW DOES consume descs:
- TM[0x1005c] cursor: HIGH=LOW=26 → HW finished 26 TXs since boot
- bp_idx recycles (always returns 37) → BMU is freeing post-consume
- 32 loopback drops in 10-ping test → switch routes back to CPU

But host wire shows 0 frames. So:
1. Driver writes desc + kicks
2. HW reads desc, "transmits" to switch fabric
3. Switch fabric receives the frame
4. Instead of routing to MAC[N] for wire egress, switch sends BACK to CPU
5. CPU NAPI receives it, detects own-MAC → drops as loopback

The wedge is in **PP/switch fabric CPU-egress routing**:
- Frame from CPU should go to a specific MAC[N] based on desc[2..3]
  egress hint (0x2c0 = lan_up_port=4 = LAN4)
- BUT switch fabric ignores the hint and reflects frame back to CPU

## Hypothesis

The encoding `(lan_up_port + 0x28) << 4 = 0x2c0` is the "encoded port"
stock uses. But the switch fabric may need:
- An FDB entry saying "this MAC lives at MAC[N]"
- A specific table (PP_BRG, sbrag etc) mapping egress hint → physical port
- The PP_CPU_FWD_BIT(29) at PP[0x2c] or PP[0x1a01c] — both HW-locked

Per prior agents, PP[0x2c] and PP[0x1a01c] are HW-locked phantom regs
(stock can't write them either). So the routing config must be
elsewhere.

## Things to try next

1. Boot stock + SSH + dump CPU-egress related regs to find what stock
   has set differently
2. Look at sbrag_table replay — maybe missing FDB or routing entry
3. Verify egress encoding `(port + 0x28) << 4` against stock decomp —
   maybe should be `(lan_up_port + bit) << shift` with different math

## State summary post-overnight

- **RX path**: WORKING end-to-end
  (tm_rx_count=200+ during pings, NAPI drains, BMU frees, kernel
  receives ARP, populates ARP cache)
- **TX path**: HW consumes descs but switch hairpin to CPU (not wire)
- **Ping bidi**: 100% loss (no ARP reply egress)

13+ commits this overnight. Major progress but TX wedge persists.
