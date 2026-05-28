# [Iter 27] TX wedge localized: between PP CLA trap and TM QMG enqueue

Bench-tested 2026-05-28 ~01:50 UTC. After all carved-region +
SOPC bridge + PHY fixes (commits bf6cd356f..06f263151), confirmed
frames flow through the HW pipeline UP TO PP CLA classifier, then
die before reaching TM QMG (the queue that feeds CPU).

## Counter telemetry under 30 host→device pings

| Stage | Reg | Before | After (30 pings) | Delta |
|---|---|---|---|---|
| Wire arrives at MAC[2] RX | MAC[2]+0x780 | 11 | 70 | +59 ✓ |
| CLA flags for CPU trap | PP[0xc3c4] | 0x56 (86) | 0x8a (138) | +52 ✓ |
| QMG enqueues for CPU | TM[0xc060] | 0xd (13) | 0xd (13) | **+0 ✗** |
| Driver sees IRQ | tm_irq_count | 0 | 0 | +0 |
| Driver NAPI rx | tm_rx_count | 0 | 0 | +0 |

PP CLA is doing its job (138 packets trapped for CPU). But QMG never
sees them. The wedge lives in the **PP → TM CPU queue handoff**.

## What's already correct vs stock

Verified non-issues (read mainline reg, matches stock LIVE):
- `TM[0xc000] = 0x01f40fa0` ✓ (sw_alarm_init equivalent done)
- `PP[0xc080] = 0x00000600` ✓ (CLA classifier ctrl matches stock)
- `MAC[N]+0x780` real RX counter increments per ping ✓
- `PP[0xc3c4]` CLA trap counter increments per ping ✓
- 574 trap_queue entries replayed via zx_chip_tm_init_trap_queues ✓

PP[0xc080] = 0x600 runtime poke was a no-op (already at 0x600).

## Hypothesis for next iter

PP CLA classifier flags packets for CPU but writes them to a queue
that TM QMG doesn't recognize. Likely culprits:

1. **trap_queue table queue_id mismatch** — `zx_chip_tm_init_trap_queues`
   writes (protocol, port) → queue_id mappings. The queue_id may
   reference TM CPU queues that mainline doesn't actually enable.

2. **TM CPU queue config** — mainline writes TM regs for 4 instances
   (TM_NUM_INSTANCES) and 5 BMU instances (TM_NUM_BMU_INSTANCES). The
   actual CPU queue setup may need different reg writes.

3. **A PP→TM bridge register** we haven't found yet — a "release
   to TM" or "trap commit" enable that gates the path.

## Other diagnostics gathered

- TM[0x100] returns to 0x02 (just bit 1) when idle. Bit 0 (RX_PENDING)
  never asserts → confirms HW thinks "no RX pending for CPU" even
  though CLA trapped 138 frames. The trap_queue → CPU queue selector
  is the gate.

- Frames die "silently" (no error count increments observed). Whatever
  drops them does so without flagging an error.

## Next-iter test plan (per stages)

1. Boot stock, dump PP+TM regs at offsets 0xc000..0xcfff to compare.
   Specifically: PP[0xc080..0xc0ff] (CLA config), TM[0xc008..0xc0ff]
   (QMG config + queue selector). Diff vs mainline.

2. Check trap_queue table contents byte-by-byte against stock_table.h
   replay output.

3. Find the TM CPU queue "enable" / "ready" register. May need to
   audit mainline's TM per-instance pre_init.

## Commit referenced

Documentation only — no driver change. Companion to commit 06f263151
(real RX counter fix that enabled this diagnosis).
