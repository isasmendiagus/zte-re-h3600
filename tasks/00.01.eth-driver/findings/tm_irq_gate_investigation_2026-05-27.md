# TM IRQ gate investigation — register diff post-Phase-52

Following Phase 52 (PHY IRQ + MAC.ctrl link callback) succeeding at the
PHY/MAC layer but ping bidi still failing, this doc traces what's
different between our mainline TM init and stock's.

## TM[0x100..0x140] live register diff

### Mainline (post Phase 52)
```
0x100 = 0000000a   IRQ status (bits 1, 3 set)
0x104 = fffffffe   IRQ mask (bit 0 only unmasked)
0x108 = 0
0x10c = 0
0x110..0x120 = 0
0x124 = 03ffffff   per-instance "queue enable?"
0x128 = 0          ← we write 0x1FFF in zx_tm_pre_init line 2121, but lost
0x12c = 00001fff   per-instance "IRQ enable mask"
0x130 = 0          ← we write 0x1FFFFF in line 2122, but lost
0x134 = 001fffff   per-instance
0x138..0x13c = 0
```

### Stock (saved capture)
```
0x100 = 00000010   ← only bit 4 set (steady state, healthy)
0x104 = fffffffc   ← bits 0+1 BOTH unmasked
0x108..0x10c = 0
```

(Didn't capture 0x110..0x140 on stock — would require another reboot
to stock since we lose SSH on TFTP mainline boot.)

### Stock-init replay table (zx_stock_table.h) for TM @ 0x180...

```
0x180000 = 0x140
0x180004 = 0x10
0x1800f0 = 0x4ff1f000
0x180104 = 0xfffffffc
0x180124 = 0x03ffffff
0x18012c = 0x00001fff
0x180134 = 0x001fffff
0x180400 = 0x140    (next instance, +0x400)
...
```

**Stock_table.h does NOT have writes to 0x180128 or 0x180130** — only
0x18012c and 0x180134. This is at odds with `tm_pon_tm_init` decomp:

```c
*(uint*)(tm_base + 0x128) = 0x1fff;
*(uint*)(tm_base + 0x130) = 0x1fffff;
```

## Why are 0x128 / 0x130 zero in mainline?

We write them in `zx_tm_pre_init` line 2121-2122 ("Legacy/extra").
Then live state shows 0. Possibilities:

1. **Decomp shows phantom writes** — Ghidra got the tm_base relative
   pointer wrong. Stock actually writes to 0x12c/0x134 (confirmed by
   replay table) and the decomp's "0x128/0x130" was a misread of the
   binary. The writes our code does are duplicate of pre-instance
   writes but at WRONG offsets, no real effect.

2. **Decomp is right, our writes happen but get clobbered later**.
   Some function between `zx_tm_pre_init` and the live read writes 0
   to these offsets. Could be `zx_tm_red_init`, `zx_pp_*`, the
   chip_tm_init tail, or `zx_eth_repoint_tm_descriptors`.

3. **Writes silently fail** — the HW returns 0 on read regardless of
   what we write. Read-only offsets or unmapped region.

The replay-table evidence (option 1) is more authoritative — it's a
LIVE capture of what stock actually writes during boot, not Ghidra's
guess. So most likely, 0x128/0x130 in the decomp was a misread.

In that case, **our 0x12c/0x134 writes match stock exactly** for
those regs. The TM IRQ gate issue is elsewhere.

## Phase 50 historical context

Phase 50 (PING BIDI WORKS, 2026-05-24) had the same writes — comment
"Legacy/extra (not in stock per-instance pattern but in our prior
code)" in line 2121 suggests pre-existing. Ping worked then with
40% loss + DUPs. So:

- If 0x128/0x130 writes were ineffective: ping worked WITHOUT them.
- The TM IRQ DID fire then (1.6M tm_rx_count per Phase 50 doc).
- Something else changed between Phase 50 and now that broke the
  IRQ gating.

This points away from 0x128/0x130 as the root cause.

## What changed Phase 50 → now

Per `git log --oneline a3e6a8017..HEAD -- linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c`,
63 commits. Big themes:

- Phase 11-14: MDIO + GePHY drivers added. Required Phase 50
  (defconfig) and Phase 52 (link callback) to be functional.
- Phase 1-9: Stock-init replay table extractions, per-block
  walker.
- Phase 21-30: extraction of zx_eth_* init helpers.
- Phase 48: TM IRQ bit 1 (TX done) permanently masked to silence
  storm. We unmask only bit 0 now (vs stock's bits 0+1).

Of these, only Phase 48 directly touches IRQ behavior. It limits
us to bit-0-only IRQ delivery. If the actual RX-pending bit isn't
bit 0 but is, say, bit 4 (which stock IRQ_STATUS shows set on a
healthy boot), we'd never see IRQ even when frames are queued.

## Hypothesis to verify next session

**Stock IRQ STATUS bit 4 might be the RX bit, not bit 0.**

Evidence:
- Stock TM[0x100] = 0x10 (bit 4 only) when ping is working.
- Mainline TM[0x100] = 0x0A (bits 1, 3 — neither = bit 4).
- Stock decomp `zx_pon_tm_int`: `status & 3` (bits 0+1) — but that
  might be the "ARM" bits separate from the actual RX/TX bits.
- Stock's mask `0xfffffffc` unmasks bits 0+1, but the visible status
  bit (bit 4) is OUTSIDE that unmask.

Interpretation: maybe stock unmasks bits 0+1 as "request lines"
that get auto-cleared after some HW ack, while the steady-state
"queue has data" is signaled via bit 4. The interrupt fires when
bit 4 transitions (level-triggered to GIC), gets cleared by HW
when queue is drained.

If that's the case, we need to unmask bit 4 too (mask = 0xFFFFFFEC)
or whatever the real "fire IRQ on this" bit is.

**Action for next session:**
1. Re-flash factory stock (we have factory image, takes ~3 min)
2. Read TM[0x100] over time while pinging — see which bits flicker
3. Cross-reference with mask = 0xFFFFFFFC (bits 0+1 unmasked)
4. Confirm whether bit 4 is the actual IRQ trigger
5. Try a runtime experiment with devmem2: change mainline TM[0x104]
   to fffffffc and see if IRQs start firing

## Queue counter trend (post-Phase-52, with traffic)

```
q[0] = 0x00030000   (3 pending)
q[2] = 0x0000014f   (335 cursor — high low16 means activity)
q[4] = 0x00000170   (368 cursor)
q[5] = 0x00000057   (87 cursor)
```

Compare with pre-Phase-52 (only q[0] had any activity) and stock
(all queues idle at 0). The switch is now correctly forwarding
frames to multiple TM queues — MAC.ctrl fix unlocked that. But NAPI
never runs to drain them.

## Files to look at next session (read-only)

- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_plat_zxylzb_9128S.c`
  search for `tm_base + 0x100` and `tm_base + 0x104` to find all
  reads/writes of these registers.
- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_tm.c` for any
  reg-write sequences that touch TM IRQ status.

No driver code changes per user instruction. This doc captures the
state for the next investigation pass.
