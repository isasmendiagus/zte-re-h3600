# Ping bidi root-cause: TM IRQ storm pinned at TX-done

## Snapshot

Captured 2026-05-27 ~03:35 UTC on a Phase 46 boot. The device booted
cleanly (driver init OK, `ZX279128S ethernet ready`, sw netdev up) but
ping host→device fails 100 % loss and the host's ARP table shows
192.168.1.99 in FAILED state.

Querying device state via the C-init REPL:

```
=== Driver counters ===
tm_irq_count      = 318,140,910
tm_napi_count     = 318,140,908
tm_rx_count       = 0
tm_tx_count       = 21
...
TM[0x0100] IRQ_STATUS       = 0x00000002  (bit 1 = TX pending)
TM[0x0104] IRQ_MASK         = 0xffffffff
TM[0x10054] TX kick         = 0x00000001
TM[0x10058] TX count        = 0x00000000
...

cat /proc/interrupts:
20:  318644795 GIC-0  68 Level     zx279128-eth-tm
```

318 million IRQs. NAPI ran 318 million times. tm_rx_count stayed at 0
the entire boot. Storm rate ~166 k IRQs/sec when sampled twice ~3 s
apart.

## What's happening

1. /init brings up sw netdev, ip addr add. That kicks off a handful of
   outgoing frames (gratuitous ARP, IPv6 ND, etc.) — driver counter
   shows `tm_tx_count = 21`.
2. HW transmits, sets TM[0x100] bit 1 (TX done pending).
3. Our IRQ handler `zx_tm_irq` (zx279128-eth.c:2610) runs:
   - reads status, computes `pending = status & ~mask & 0x03`
   - if non-zero: `mask |= 0x03` (mask our bits during NAPI), schedule NAPI
4. NAPI poll `zx_tm_napi_poll` (zx279128-eth.c:2462):
   - walks 8 RX queues
   - none have pending descriptors → done = 0
   - falls through to `napi_complete_done` + `mask &= ~0x03` (re-arm)
5. IRQ refires IMMEDIATELY because TM[0x100] bit 1 was never ACKed.

Net: ~166k IRQs/sec eating one CPU core forever. Any actual RX that
arrives may or may not get processed — the storm probably starves
real packet processing or at least makes it intermittent.

## Why bit 1 stays asserted

We never write to TM[0x100]. Stock `zx_pon_tm_int`
(decomp_all_plat_zxylzb_9128S.c:6304) doesn't either — it just reads
`status & 3 & ~mask` and calls `pon_tm_net_int`. Stock's path then
schedules NAPI which is `pon_tm_net_poll`
(decomp_all_plat_zxylzb_9128S.c:8558) — and we DON'T see stock writing
to TM[0x100] there either.

So stock must be acking bit 1 implicitly, probably by processing TX
completion descriptors at TM[0x10058] (DMA_DESC_CNT_UP) or some other
TX-completion FIFO. Our NAPI poll **does not touch the TX side at
all** — it only walks the 8 RX queue counters (TM[0x10100..0x1011c]
range) and releases RX descs.

## Probable fix path (NOT executed in autonomous loop)

Three candidates ordered by risk:

1. **Mask bit 1 permanently** until TX completion processing is
   implemented. Change `#define TM_IRQ_ARM_BITS 0x03` →
   `0x01` (zx279128-eth.c:166). Stops storm immediately. Loses TX
   completion notifications — but we don't process them anyway so
   no functional regression. Simplest test.

2. **Read TM[0x10058] in NAPI poll** to see if reading the TX desc
   count register clears bit 1 (read-to-clear semantics on some HW).
   Cheap, easy to revert.

3. **Implement proper TX completion reclaim** in the NAPI poll body:
   walk TX completion descriptors, free skbs, advance tx_done index,
   then check IRQ status again. Stock-correct but biggest change;
   needs more RE to know exactly which queue counters / register
   region holds the TX completion FIFO.

Recommendation: try (1) first to confirm hypothesis, then (3) for
the real fix.

## Open questions

- Why was this not seen at Phase 50 (PING BIDI WORKS milestone,
  2026-05-24)? Some commit since then must have either started
  triggering TX (e.g. /init's ip addr add) or stopped a previously
  silent TX-ack mechanism. `git log --oneline 4ca166fea..HEAD --
  drivers/net/ethernet/zte/zx279128-eth.c` shows 40+ commits over
  3 days — bisecting from the Phase 50 commit would localize.

- Is TM[0x100] write-1-to-clear? Most ARM SoCs use W1C for IRQ
  status. Worth one experimental write in zx_tm_irq before
  scheduling NAPI: `tm_write(e, 0x100, pending)`.

- Does the RED queue config that "requires RED queue config!" for
  bit 0 RX cover this? Phase boot log shows "TM RED init: 0 failed
  of 1168 queue configs". So RED IS configured.
