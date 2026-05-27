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

---

## Round 2 (post-Phase-52 deeper RE) — MAJOR finding

### Bit-4 hypothesis REFUTED

`zx_pon_tm_int` (the IRQ top-half) at decomp line 6311:

```c
uVar1 = *(tm_base + 0x100) & 3 & ~*(tm_base + 0x104);
if (uVar1 != 0) {
    pon_tm_net_int(*param_2, uVar1);
    // ...
}
```

Status is masked with `& 3` — only bits 0 and 1 are inspected. Bit 4
shown in stock's healthy live state (0x10) is NOT what triggers the
IRQ. Confirmed by reading the only TM[0x100] read in all of stock
plat-zxylzb_9128S.ko (single reference).

So stock fires on bit 0 (RX) and bit 1 (TX done). Our mainline only
unmasks bit 0 (Phase 48 silenced TX storm) — fine.

### Stock IRQ lifecycle (full picture)

1. `pon_tm_int_init` (decomp 6338): mask = 0xFFFFFFFF (everything
   masked), then `request_threaded_irq(zx_pon_tm_int, ...)`.
2. `pon_tm_net_init` (6966): mask |= 7 (mask bits 0,1,2); creates
   `pon_tm_timer` running `pon_tm_timer_func` every jiffy — TX-done
   polling, not RX.
3. `pon_tm_net_open` (6519): IF `strcmp(name,"pon")==0` → mask &= ~3
   (UNMASK bits 0,1). **Gated on the "pon" netdev (not "sw")**.
4. IRQ fires → `pon_tm_net_int` (6900): mask |= 7 (re-mask) then
   `__napi_schedule`.
5. `pon_tm_net_poll` (8594): on `napi_complete_done`, mask &= ~3
   (re-unmask).
6. `pon_tm_net_close` (6494): IF `strcmp(name,"pon")==0` → mask |= 7.

Our mainline unmasks directly in init (line 2114) — fine in principle,
matches stock's eventual state.

### Stock has TWO netdevs: "sw" and "pon"

`pon_tm_net_init` (decomp 6938):
```c
pon_tm_netdev._4_4_ = pon_tm_net_register(1, &_LC21, ...);   // "sw"
pon_tm_netdev._0_4_ = pon_tm_net_register(0, &_LC3);         // "pon"
```

Mainline only has one netdev (`sw`). Stock's IRQ-unmask is gated on
the "pon" netdev's open() — so user-space must `ifconfig pon up` for
stock IRQ to actually be unmasked. (We bypass this by writing the
mask directly in init.) Not the root cause, but worth knowing —
the stock kernel itself is dormant on the RX path until userspace
arms the PON link.

### 🚨 REAL BUG CANDIDATE — DMA UP/DN ring sharing same address

`pon_tm_dma_init` (decomp 6280):
```c
*(tm_base + 0x10050) = ... + 0x405e0000 + ...;   // UP ring base
*(tm_base + 0x10060) = ... + 0x405f0000 + ...;   // DN ring base (DIFFERENT by 0x10000)
```

Mainline `zx_eth_init_chip_tm` (line 2353-2354):
```c
tm_write(e, TM_REG_DMA_TX_UP_BASE, e->txdesc_dma);   // 0x10050
tm_write(e, TM_REG_DMA_TX_DN_BASE, e->txdesc_dma);   // 0x10060 ← SAME PTR
```

We write the same DMA address to both UP (switch→CPU, RX) and DN
(CPU→switch, TX) descriptor base regs. Stock has them at PHYS
addresses 0x10000 apart.

**Why this might cause `tm_irq_count=0`**: TM[0x100] bit 0 ("RX
pending") might be asserted only when the UP ring's tail pointer
advances. If our UP ring shares memory with the DN ring, TX activity
on the DN side may keep zeroing out RX completions before they
register, or the HW's UP/DN advance logic gets confused and bit 0
never asserts.

**Why ping worked at Phase 50 originally**: same code existed at the
Phase 5j PING BIDI milestone (2026-05-24). Either it worked despite
the shared address (ping is low-bandwidth, rings rarely fill), or
there's a config change between then and now (the PHY/MAC.ctrl
plumbing now correctly enables RX on multiple ports, *increasing*
DMA traffic enough that the bug manifests). Or the descriptor format
is such that UP and DN can share if specific offsets are used.

### Action items for next session (still no driver code)

1. **Read `zx_eth_init_chip_tm` and the alloc site for `e->txdesc_dma`**
   — check whether there's a separate `e->rxdesc_dma` that the line
   2354 write should be using. If so, this is a clean one-line fix.
2. **Re-flash stock and devmem2 read `tm_base + 0x10050` and `+0x10060`**
   — confirm stock's *runtime* addresses differ.
3. **Search for `0x405e0000` and `0x405f0000` in stock replay table
   `zx_stock_table.h`** — does it have these writes?
4. **Look at stock decomp for the "ring entry advance" path** — what
   asserts bit 0 of TM[0x100]? Is it tied to the UP ring's TX
   completion or to some queue threshold?

The DMA UP/DN ring bug is the strongest single hypothesis seen so far
for the `tm_irq_count=0` symptom. Verification needs runtime
experiment on next iteration — *not* a driver patch per the AFK
instruction. Memo this for the user's return: "found the candidate,
needs a single-byte/line driver change to validate."

(Recorded 2026-05-27 round 2 of the autonomous loop, ~30 min after
phase52 test result.)

### Round 2 follow-up — descriptor allocation confirmed separate

`struct zx_eth` fields (lines 290-291):
```c
void *rxdesc_cpu;       dma_addr_t rxdesc_dma;   /* 8 queues * N * 16B */
void *txdesc_cpu;       dma_addr_t txdesc_dma;   /* 1024 * 16B TM TX desc ring */
```

Allocated separately at lines 1646 and 1648. So we DO have two
distinct DMA regions; we just point TM[0x10050] at the wrong one.

Current writes:
- TM[0xF0]       = `e->rxdesc_dma`   (line 2318, per-instance — RX ring base, working)
- TM[0x10050]    = `e->txdesc_dma`   (line 2353, UP/RX direction — **mismatch?**)
- TM[0x10060]    = `e->txdesc_dma`   (line 2354, DN/TX direction — correct)

Two scenarios:
1. **TM[0x10050] should be rxdesc_dma** (matching the UP=RX semantic).
   Then line 2353 is a one-line bug.
2. **TM[0x10050] is a totally separate DMA control region** that needs
   its own dma_alloc_coherent (matching stock's `+0x405e0000` offset
   being distinct from rxdesc_dma).

The stock arithmetic for both UP and DN bases involves
`u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE + u32_BP_SIZE *
u32_BPPE_POOL_SIZE + pdt_mem_size + 0x405X0000 + ZX_RESERVE_MEM_SIZE *
-0x100000` — i.e., they're in the BMU/BPPE pool memory region, NOT
the per-instance RX descriptor area (which is in 0xF0-controlled
RAM). So **scenario 2 is more likely**: these are separate DMA
control rings tied to the BPPE pool, distinct from the per-instance
RX descriptor ring at TM[0xF0].

Not a one-line fix; would need a new DMA allocation of correct size
pointing into the BMU pool. Save for next driver-code session.

**Net of round 2:** Bit-4 hypothesis dead. Real candidate found
(DMA UP base wrong) but it's a non-trivial fix, not a quick patch.
Stockport doesn't suffer from this because stock allocates pdt_mem
in physical RAM regions directly; we use dma_alloc_coherent which
gives us different physical pages.
