# RX trap-ring one-wrap halt: stock-vs-mainline RE

Date: 2026-06-04
Scope: read-only RE of stock `pon_tm_net_poll` / `soft_release_rx_desc` vs mainline
`zx_tm_napi_poll` / `zx_tm_release_rx_desc_raw`. Goal: find the exact reason the
CPU-RX trap path halts after exactly one ~1024 ring wrap.

Source refs:
- Stock decomp: `tasks/00.10.02.re-stock-kmods/findings/decomp_all_plat_zxylzb_9128S.c`
- Mainline: `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`

---

## TL;DR — the single exact discrepancy

The per-queue RX count register `tm[(q+0x4040)*4]` (= `tm[0x10100 + q*4]`) is a
**packed pair of 16-bit counters, one per descriptor ring**:

- **HIGH 16 bits** = pending count for **RX ring 1** (the "up"/first ring).
- **LOW 16 bits**  = pending count for **RX ring 0** (the "down"/second ring).

The release register `tm[0x4068]` word is
`reason/ring(bit14) | count(bits 4..) | sop(bit3) | qid(bits 0..2)`. **Bit 14 is the
RING SELECTOR**: it tells HW *which ring's pending counter to decrement*.

- Stock releases ring-1 consumption with `soft_release_rx_desc(1, q, …)` ⇒ **bit14 = 1**
  (decrement HIGH-16). Lines 8726/8729.
- Stock releases ring-0 consumption with `soft_release_rx_desc(0, q, …)` ⇒ **bit14 = 0**
  (decrement LOW-16). Lines 8835/8838.

**Mainline reads pending from the LOW-16 (`status & 0xffff`, line 2898 — ring 0) but
hard-codes the release word with `(1u << 14)` (line 2862 — ring 1).** So it consumes
ring-0 descriptors while telling HW it consumed from ring 1. Result:

- The **LOW-16 (ring-0) counter mainline actually drained is NEVER decremented**, and
- the **HIGH-16 (ring-1) counter is decremented for descriptors that never arrived
  there**, underflowing it.

This desynchronises HW's producer/consumer accounting. After HW has produced one full
ring (≈`TM_RX_DESC_PER_Q`=1024) of descriptors into the ring whose consumer index never
advances, HW believes the ring is still full / un-consumed, stops producing, and stops
asserting the RX IRQ → `tm_irq_count`/`tm_napi_count` freeze, `tm_rx_count` latches at
~1024. Exactly the observed symptom.

This is the **ring-consumer-cursor** candidate. The IRQ-rearm and BMU-producer-cursor
candidates are ruled out below.

---

## Stock `pon_tm_net_poll` @ 0x1c9f0 (decomp lines 8562–8866)

Context pointer `iVar13 = DAT_0001d324` is a **software** ring-bookkeeping struct (not a
register block). Field offsets:

| off  | meaning                                   |
|------|-------------------------------------------|
| +0x38| ring-0 desc-array base (VA, `ZX_VA_DESC_BASE`) |
| +0x3c| ring-0 head cursor (0..0x3ff, wraps at 0x400) |
| +0x78| ring-1 desc-array base (VA)               |
| +0x7c| ring-1 head cursor (0..0x3ff, wraps at 0x400) |

Per-poll, per-queue (`local_58` = 7→0, gated by `local_44` active-queue mask):

1. `uVar6 = tm[(local_58 + 0x4040) * 4]` — the packed count register (line 8612).
2. **Ring 1 first**: consume `iVar9 = min(budget/2, uVar6 >> 0x10)` descriptors
   (lines 8619–8621 → HIGH-16). Desc address = `*(iVar13+0x78) + head*0x10`
   (line 8623); head incremented and wrapped `if (0x3ff < head) head = 0`
   (lines 8639–8643). For each desc: bp index = `(desc[7]>>1) | (desc[8]<<7)`
   (line 8644); SOP/own flag = `desc[6] & 1` (line 8645); deliver via
   `netif_receive_skb` / `switch_skb_recv`; `pp_bmu_free_bp` once per desc
   (lines 8703/8711). `local_4c` counts descs with `desc[6]&1` set (the SOP run).
3. **Ring-1 release** (lines 8724–8730):
   - `if (iVar9 - local_4c) soft_release_rx_desc(1, q, 0, iVar9 - local_4c)` (sop=0)
   - `if (local_4c)        soft_release_rx_desc(1, q, 1, local_4c)`           (sop=1)
   Both with **first-arg = 1 ⇒ bit14 = 1**.
4. **Ring 0 second** (lines 8732–8839): consume `uVar7 = min((budget-iVar9)/2,
   uVar6 & 0xffff)` (lines 8734–8736 → LOW-16) from base `*(iVar13+0x38)`, head
   `+0x3c`, same wrap-at-0x400.
5. **Ring-0 release** (lines 8832–8839):
   - `soft_release_rx_desc(0, q, 0, uVar7 - local_4c)` (sop=0)
   - `soft_release_rx_desc(0, q, 1, local_4c)`         (sop=1)
   Both with **first-arg = 0 ⇒ bit14 = 0**.
6. Loop re-runs (`local_30 = 4` passes) while any queue made progress; then
   NAPI-complete path (lines 8590–8595): `napi_complete_done`, `disableIRQinterrupts()`,
   `tm[0x104] &= 0xfffffffc` (re-enable RX/TXdone IRQ bits).

### `soft_release_rx_desc` @ 0x1a8e8 (lines 7204–7232)

```
soft_release_rx_desc(param_1=ring, param_2=q, param_3=sop, param_4=count):
  poll up to 30x: if ((tm[0x4064] & 1) == 0) {        // 0 == HW ready for a release
     tm[0x4068] = param_1<<0xe | param_4<<4 | param_2 | param_3<<3;  // ring|count|q|sop
     tm[0x4064] = 1;                                    // commit
     return 0; }
  ... "failed to rls rx desc"
```

Word layout of `tm[0x4068]`: **bit14 = ring select**, bits 4+ = count, bit3 = sop,
bits 0..2 = qid.

### Ring base/size setup — `pon_tm_dma_init` @ 0x1927c (lines 6279–6301)

`tm[0x1003c] = 0x400040` (ring size: 0x400 = 1024 entries each). TX ring bases at
`tm[0x10050]`/`tm[0x10060]`. The RX desc-array VAs (`ZX_VA_DESC_BASE`) feed the SW
struct `+0x38`/`+0x78`. The two RX rings are **shared across all 8 queues** — the queue
id only selects the count-register field and the release-word `qid`; the desc array is
indexed by `head*0x10` with **no queue stride**.

---

## Mainline `zx_tm_napi_poll` (lines 2885–3114) and release (2852–2872)

- Single ring `e->rxdesc_cpu`, indexed `(q*TM_RX_DESC_PER_Q + idx)*TM_DESC_SIZE`
  (line 2932) — i.e. **per-queue stride**, unlike stock's per-ring shared array.
- `pending = tm_read(0x10100 + q*4) & 0xffff` (line 2898) — reads the **LOW-16 / ring-0**
  field only. The HIGH-16 (ring 1) is never consulted.
- Release `zx_tm_release_rx_desc_raw`: `tm[0x4068] = (1u<<14) | (count<<4) | q | (sop<<3)`
  (line 2862) — **bit14 hard-coded to 1 ⇒ always decrements the HIGH-16 / ring-1
  counter**, which is *not* the field it read.
- `sop` is forced to 1 for every release (line 2871, `zx_tm_release_rx_desc` wrapper and
  Iter-U raw calls at 3096/3098) — stock derives sop from `desc[6]&1` per desc and splits
  the release into sop=0 + sop=1 sub-counts.

Net: mainline drains ring 0 but acknowledges to ring 1. The two HW counters diverge; one
ring wrap later the producer stalls.

---

## Why the other two candidates are NOT the cause

**IRQ re-arm (candidate 2): RULED OUT.** Stock IRQ flow (`pon_tm_net_int` @ 0x1a0e8,
lines 6893–6911): mask `tm[0x104] |= 7`, `__napi_schedule`. NAPI-complete (lines
8590–8595): `napi_complete_done`, then unmask `tm[0x104] &= 0xfffffffc`. Mainline
`zx_tm_irq` (3117–3135) and the poll tail (3101–3104) do exactly the same: mask in IRQ
(`tm_or(0x104, ARM_BITS)`), unmask at complete (`tm_and(0x104, ~ARM_BITS)`). Ordering and
register semantics are identical. Stock does **not** re-read pending + reschedule after
unmask (that was Iter V's invention; it busy-looped). So the IRQ path is faithful and is
not the wedge.

**BMU producer cursor (candidate 4): RULED OUT.** Stock `pp_bmu_free_bp` and mainline
`zx_bmu_free_bp` (3422–3447) both free exactly one BP per consumed desc via `tm[0x8010]`
with the `tm[0x80dc]` credit refill. Mainline already calls it once per desc (delivered
or dropped). BP recycling is independent of the desc-ring consumer index; it would cause
pool exhaustion (a different, already-fixed symptom), not a clean one-wrap IRQ freeze.

The decomp supports **only** the ring-consumer-cursor (release-field) mechanism.

---

## Concrete fix

The minimal, decomp-faithful fix is to make the release decrement the **same ring field
the poll read**. Mainline reads LOW-16 ⇒ it must release with **bit14 = 0**, not 1.

### Fix A (minimal, recommended): release ring 0

In `zx_tm_release_rx_desc_raw` (line 2862), change the hard-coded ring selector from 1
to 0 so it acknowledges the LOW-16 (ring-0) counter that `zx_tm_napi_poll` actually
drains:

```c
/* bit14 = ring selector; mainline consumes the LOW-16 (ring 0) count field
 * (status & 0xffff in zx_tm_napi_poll), so it MUST ack ring 0 (bit14=0).
 * Stock soft_release_rx_desc(0, …) decompiles to bit14=0 (plat decomp 8835/8838);
 * the prior (1u<<14) acked ring 1 and left ring 0's pending counter un-decremented,
 * stalling the producer after one TM_RX_DESC_PER_Q wrap. */
tm_write(e, 0x4068, ((u32)count << 4) | (u32)q | ((u32)sop << 3));   /* bit14 = 0 */
tm_write(e, 0x4064, 1);
```

Keep the `while (t-- && (tm_read(0x4064) & 1))` busy-wait — stock waits for
`(tm[0x4064] & 1) == 0` before writing (line 7220), which mainline already does.

This single bit flip aligns read-field and ack-field and should stop the one-wrap halt.

### Fix B (more faithful, if A is insufficient): drain BOTH ring fields

If after Fix A the HW still feeds the HIGH-16 ring under flood (i.e. some traps land on
ring 1), replicate stock's two-ring drain. Per poll, per queue:

```c
u32 raw   = tm_read(e, 0x10100 + q*4);
u32 pend0 = raw & 0xffff;          /* ring 0 */
u32 pend1 = raw >> 16;             /* ring 1 */
```

Consume `pend1` descriptors first, releasing with bit14=1; then `pend0`, releasing with
bit14=0. With a single shared `rxdesc_cpu` array this needs a second head cursor
(`rx_head1[q]`) and a second ring region, matching stock's `+0x38`/`+0x78` split. This is
the literal stock structure but a larger change — only take it if telemetry shows
`raw >> 16` going nonzero.

### Also align `sop` (low risk, do alongside A)

Stock sets sop from `desc[6] & 1` and releases in two sub-counts (sop=0 run + sop=1 run).
Mainline forces sop=1 for the delivered count and sop=0 only for the skipped-slot
remainder (Iter U). If HW gates re-fill on the sop bit per descriptor, mismatched sop
could also stall a ring; derive sop per desc from `desc[6] & 1` and accumulate the two
sub-counts exactly as stock does (lines 8645–8654, 8725–8730).

---

## Confidence and ambiguity

**Confidence: HIGH** that bit14 is a ring/field selector and that mainline mis-targets it
(reads LOW-16, acks HIGH-16). This is directly readable in the decomp:
`soft_release_rx_desc(1,…)` for the HIGH-16 ring (8620/8726) vs
`soft_release_rx_desc(0,…)` for the LOW-16 ring (8735/8835), with the bit-14 placement
explicit at line 7221. It is the only mechanism in the decomp that (a) is per-ring,
(b) is a write mainline gets wrong every poll, and (c) produces a *clean* stall after one
ring's worth of production rather than a busy-loop or gradual pool drain.

**Ambiguities / things to verify on-device:**
1. Bit 14 could nominally be a "reason code" rather than a strict ring index; but the
   1↔HIGH16 / 0↔LOW16 pairing in the decomp is unambiguous regardless of the field's
   name, so Fix A holds either way.
2. Whether real CPU traps ever populate the HIGH-16 (ring 1) field. If `raw >> 16` is
   always 0 in practice, Fix A alone fully resolves it; if not, Fix B is required. Add a
   one-line telemetry print of `raw>>16` vs `raw&0xffff` per queue to settle this before
   committing to A vs B.
3. The stock two-ring-shared-array layout (no queue stride) differs from mainline's
   per-queue stride. Fix A does not touch the array layout and is unaffected; Fix B would
   need to adopt the stock layout for the second ring.
4. Prior failed Iter U already releases the *skipped-slot* remainder with sop=0 — but
   still with bit14=1 (it calls the same `_raw` helper). So Iter U released the right
   *count* to the *wrong ring*; that is exactly why it had "no effect." Fix A is the piece
   Iter U missed.
