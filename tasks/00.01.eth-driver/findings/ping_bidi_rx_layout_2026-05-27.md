# Ping bidi RX investigation — descriptors at +0x1000, NAPI delivers len=0

Continuation of [ping_bidi_irq_storm_2026-05-27.md]. Two big fixes
landed (Phase 50 enables MDIO/PHY drivers in defconfig; Phase 51
flips the `pending = status & 0xFFFF` → `status >> 16` field read).
After both, PHY[0] is link up and TX-to-host works (host sees
device's IPv6 link-local NDP). RX still blocked.

## Polling-mode experiment (workaround, NOT committed)

To bypass the TM-bit-0 IRQ never firing, I added a 10 ms
`schedule_delayed_work` that calls `napi_schedule(&e->tm_napi)` from
`sw_open`. Built and booted. Results:

  * `tm_napi_count = 64,349` over ~20 s (NAPI poll ran 3.2 k/sec)
  * `tm_rx_count = 5` (NAPI thought 5 frames delivered)
  * `rx_head[0..7] = 6 0 0 0 0 0 0 0` (queue 0 head advanced 6 slots)
  * BUT: per-iteration descriptor reads returned `len=0 bppe=0`
    raw[0..7]=00 00 00 00 00 00 00 00
  * sw netdev rx_packets stayed at 0 (the 5 "delivered" frames either
    had len=0 so the alloc_skb branch was skipped, or were filtered
    elsewhere with no counter)
  * Ping host→device still 100 % loss

## The actual clue — descriptor layout mismatch

`zx_stats_show` dumps:

  rxdesc DIFF from canaries: 64512 words changed, first at offset 0x1000

That means: between probe (where we filled rxdesc with a canary
pattern) and the stats read, HW changed 64512 words — first
modification at byte offset **0x1000** from `rxdesc_cpu`.

But our `zx_tm_napi_poll` computes the descriptor address as

```c
u8 *desc = (u8 *)e->rxdesc_cpu +
           (q * TM_RX_DESC_PER_Q + idx) * TM_DESC_SIZE;
```

i.e., for `q = 0, idx = 0` we read at offset 0. HW has NOT touched
offset 0 — the bytes there are still the canary pattern (the diag
reports 0 there only because that's the canary 0xZZ which prints as
0x00 sometimes, or because the canary we wrote was zero — same
visual either way). HW is actually writing descriptors starting at
**offset 0x1000**.

So one of:

  (a) `TM_RX_DESC_PER_Q` is too small / wrong — the per-queue stride
      should be larger so q=0 base is at 0x1000.
  (b) The queue order is reversed (q=7 first, q=0 last), so q=0 base
      is at the END of the rxdesc area not the start.
  (c) HW expects a 4 KB header / control block at +0x0..0xfff and
      descs start at +0x1000.

Stock's `pon_tm_net_poll` (decomp_all_plat_zxylzb_9128S.c:8558) uses

```c
*(uint *)(iVar13 + 0x78) + *(int *)(iVar13 + 0x7c) * 0x10
```

— where iVar13 references a per-queue control struct, +0x78 is the
queue's desc-ring base pointer, +0x7c is the next-desc index. Each
desc is 0x10 bytes. The base pointer is per-queue, NOT a single
global rxdesc_cpu + q * stride calculation. So our layout assumption
is probably wrong.

Stock likely sets up 8 separate desc rings, with HW providing 8
base pointers — and the global TM[0xF0] = rxdesc_dma we set may just
be queue 0's base, with the other queues at independent addresses
that HW infers from queue config registers.

## Next step (recommended)

Read stock's `pon_tm_queue_init` (decomp line 6914) more carefully —
specifically the per-queue init it does. We currently allocate a
single 256 KB rxdesc area and assume all 8 queues live inside via
stride. Stock probably wants 8 × 4 KB rings (or similar) with each
ring's base programmed to a different TM register.

The 64512 words changed gives us a hint: 64512 words × 4 bytes =
258 048 bytes ≈ 256 KB ≈ our whole rxdesc area. So HW IS writing
across the full area; it just doesn't agree with us on where each
queue starts.

## Other findings (recorded for the record)

  * **The whole RX path runs**: NAPI poll body executes, reads
    descriptors, releases descs to HW (queue counters go 3 → 0).
    The frame data parsing fails because the descs at our computed
    offsets are zeros.

  * **The TM IRQ never fires**: separate problem; even with our
    Phase 48 fix giving the IRQ a clean bit-0 path, status bit 0 at
    TM[0x100] doesn't set. Stock probably arms it via a register we
    don't write yet.

  * **Phase 50 + Phase 51** (defconfig + >>16) are necessary but
    not sufficient. Both should stay in main.

  * Polling-mode workaround is REVERTED in main (per user
    instruction). The code lives only in the experiment branch.
