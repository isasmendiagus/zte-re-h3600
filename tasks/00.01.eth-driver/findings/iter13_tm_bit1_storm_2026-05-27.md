# [Iter 13] TM[0x100] bit 1 is HW-asserted, no driver-side ack found

Validation experiment 2026-05-27. Tested whether enabling TM IRQ bit 1
(stock's `pon_tm_net_int` mask = `0xfffffffc`, mainline previously
`0xfffffffe`) restores RX delivery. Did NOT — instead produced an IRQ
storm because bit 1 in TM[0x100] is HW-set and not clearable by:

- Write 1-to-clear (devmem write 0x02 to TM[0x100] → bit 1 stays set)
- Write 0-to-clear (devmem write 0x00 → bit 1 stays set)
- Draining TM[0x10058] / TM[0x10068] (UP/DN TX-done counters — these
  ARE clear-on-read per Iter 12 timer, but bit 1 of TM[0x100] persists)

## Bench test

After temporarily setting `TM_IRQ_ARM_BITS = 0x03` and reflashing:

```
/proc/interrupts:
  26: 3544934 GIC-0 68 Level zx279128-eth-tm     ← storm
debugfs/pipeline_stats:
  tm_irq_count   = 4803015
  tm_napi_count  = 4803013
  tm_rx_count    = 0
  tm_tx_count    = 10  (no real TX traffic)
TM[0x100] = 0x00000002 (bit 1 set persistently)
TM[0x104] = 0xffffffff (mask pinned all-set by storm race)
TM[0x10058] = 0x00000000   ← UP TX-done counter drained ok
TM[0x10068] = 0x00070000   ← DN TX-done HIGH16=7 (7 pending stuck)
```

NAPI was scheduled 4.8M times in ~5 seconds. All 8 RX queues empty (no
work). Then a race between handler's mask-OR and NAPI's mask-AND
pinned TM[0x104] at 0xffffffff, IRQ stopped firing afterwards.

Ping bidi remained 100% loss (HW TX consume is still wedged — see
`stock_init_sequence_analysis_2026-05-27.md` "HW won't consume our TX"
section; 7 DN-direction frames stuck).

## Interpretation

Bit 1 of TM[0x100] is asserted by HW and reflects an *internal* state
that mainline cannot directly clear. Possibilities:

1. **Tied to DN TX-pending count > 0**: TM[0x10068] high16 = 7 → some
   internal "TX queue not empty" state machine asserts bit 1. The
   mechanism that drains DN TX (HW consume engine) is what would
   clear it, not SW. We're already blocked on that wedge.

2. **Tied to a sub-register read sequence** stock follows in
   `pon_tm_net_poll` (decomp:8594) that mainline's NAPI poll skips.
   Mainline NAPI checks per-queue counters at `TM_RX_QCNT_BASE + q*4`
   and `zx_tm_release_rx_desc` on ack — none of those read the
   sub-regs that might clear bit 1.

3. **Stock writes bit 1 to a clear register elsewhere** in the
   `pon_tm_net_int` → NAPI path that mainline replicates incorrectly.

## Decision

Revert `TM_IRQ_ARM_BITS` to `0x01` to stop the storm. Mainline IRQ pipe
is again silent on bit 1 (which was the case before this experiment),
but at least the system stays responsive.

## Next iter targets

- **Stock decomp**: read `pon_tm_net_poll` and `pon_tm_check_tx_done_nolock`
  in full, find every TM[0x...] write done in the NAPI/timer paths.
  One of those is the bit-1 ack.
- **TX consume wedge**: orthogonal issue. Bit 1 may simply be the
  *symptom* of the wedge, not the cause. If we fix the wedge (HW drains
  pending TX), bit 1 might self-clear.

## Lesson

"Unmasking matches stock" is necessary but not sufficient — the full
ack pattern matters too, otherwise level-triggered IRQs storm. Bias
toward not committing changes that introduce storms even if they look
architecturally right; first find the matching ack.

Cross-ref:
- `tm_irq_gate_investigation_2026-05-27.md` (prior round on this)
- `stock_init_sequence_analysis_2026-05-27.md` "HW won't consume our TX"
