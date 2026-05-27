# [Iter 14] Bit-1 ack: stock uses identical mask cycle, no special write

Static analysis grep over `pon_tm_net_poll` (fn-47 @ plat:8562),
`pon_tm_net_int` (fn-46 @ plat:6893), `zx_pon_tm_int` (fn-45 @ plat:6306),
and `pon_tm_check_tx_done_nolock` (fn-43 context @ plat:6360) for the
TM[0x100] bit-1 ack mechanism stock uses.

## Stock's pattern (per static_analysis_plat_zxylzb_init.md)

1. `zx_pon_tm_int` (top-half): reads `TM[0x100] & 3 & ~TM[0x104]`, calls
   `pon_tm_net_int` if any bit pending. Returns IRQ_HANDLED.
2. `pon_tm_net_int`: writes `TM[0x104] |= 7` (mask bits 0,1,2 during NAPI),
   `__napi_schedule`.
3. `pon_tm_net_poll`: drains RX descriptors. At end if budget remaining:
   `napi_complete_done()` + `TM[0x104] &= 0xfffffffc` (unmask bits 0+1).
4. `pon_tm_check_tx_done_nolock` (timer @ jiffy): reads `TM[0x10058]` or
   `TM[0x10068]` low16, subtracts from SW pending counter. Read clears
   the low16 counter.

**Nowhere does stock write TM[0x100] to clear bit 1.** The mask cycle
(mask-OR in IRQ → mask-AND in poll) is identical to mainline's
existing code. So bit 1 is HW-managed; it stays set as long as the
underlying condition holds.

## What is the underlying condition?

Bit 1 = TX done. Per fn-43 context: stock's `soft_insert_tx_1desc`
write to `TM[0x10054] = 1` (UP kick) or `TM[0x10064] = 1` (DN kick)
fires the HW DMA. HW asserts bit 1 in TM[0x100] when *the SW
write-cursor advances ahead of HW read-cursor* on either ring (i.e.
TX descriptors pending HW-side consumption).

For bit 1 to CLEAR:
- HW must consume all pending TX descriptors (high16 of TM[0x10068]
  must reach the SW write cursor)
- SW must read TM[0x10058]/[0x10068] low16 to ack-back the consume count

Mainline does step 2 via the periodic timer (Iter 9 commit `80f610eda`).
Step 1 is HW responsibility — and the HW is wedged: bench shows
TM[0x10068] high16 = 7 (7 pending), low16 = 0 (HW hasn't consumed
anything to ack).

## Therefore bit 1 is a SYMPTOM, not the cause

The real wedge is HW TX consume engine not running. Bit 1 persistence
is just the visible artifact.

## New hypothesis: A07 (PON IRQ not registered) is the cause

Stock registers `zx_pon_int` as handler for hwirq 66 (GIC SPI 0x42)
via `request_threaded_irq(g_pon_irq, ...)` in `register_pon_int`
(plat:7724). Mainline does **NOT** request irq_pon (it's fetched from
DT but never `devm_request_irq`'d).

Bench memdump from Iter 14:
```
pon[0x40040] (status) = 0x00000008    ← bit 3 SET
pon[0x40044] (mask)   = 0xffffff7f    ← bit 7 unmasked (= enabled)
```

Bit 7 in PON aggregate IRQ — stock unmasks it in `register_pon_int`
finalization (`pon[0x40044] = 0xffffff7f`). The semantics of bit 7 in
that aggregate are not yet RE'd to a specific sub-block, but it's the
only enabled bit and stock services events on it.

If bit 7 corresponds to a TX-related event in the PON aggregate (e.g.
"TX engine wants service"), mainline's missing PON IRQ handler means
those events queue up forever. The TX consume engine may be waiting
for a PON IRQ-level handshake that never happens.

## Next iter plan

1. **Register `irq_pon` with a minimal handler** (just reads
   `pon[0x40040]`, logs which bits set, returns IRQ_HANDLED).
2. Boot bench, check ping bidi.
3. If bit 1 of TM[0x100] clears → confirmed. Promote handler to do
   the dispatch logic stock has (bit 6 → lp_isr, bit 4 → rog_onu_flag).
4. If no change → orthogonal issue, document, pivot.

This is a low-risk single-handler add. Stock's handler is very simple
(per fn-258): read status & ~mask, dispatch to lp_isr if bit 6 set,
set rog_onu_flag if bit 4 set, return IRQ_HANDLED. We can implement
exactly that and see what happens.

Cross-ref:
- `static_analysis_plat_zxylzb_init.md` fn-04, fn-45, fn-46, fn-47, fn-258
- `mainline_gap_matrix.md` [A07]
- `iter13_tm_bit1_storm_2026-05-27.md` (why bit 1 itself can't be
  cleared from driver)
