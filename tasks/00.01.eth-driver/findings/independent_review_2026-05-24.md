# Independent review of Phase 5 approach (2026-05-24)

Reviewer: separate opus 4.7 agent, given full context of session and access to
all repo files. Asked: "is this approach sound, or am I in denial about
something?" Returned a brutal — and useful — critique.

## The 3 critical findings

### 🔴 #1 — BMU "alloc" is a fiction (the smoking gun)

`linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c:2121-2125`:

```c
static u32 zx_bmu_alloc_bp(struct zx_eth *e)
{
    static u32 cycle;
    return (cycle++) & (TM_BPPE_POOL_SIZE - 1);
}
```

This is **not** a HW BMU allocation — it's a software cycle counter. We then
`memcpy(bp_cpu + bp*BP_SIZE, skb->data, len)` and tell HW "use this bp_idx".

**Why this is a smoking-gun for 100% TX loss**:
- HW BMU may think `BP[137]` is RX-owned with stale RX data
- We overwrite it for TX; HW reads back its own RX data as if it were our TX frame
- The BPPE FIFO (the queue that tells HW "this BP is now valid TX content from
  CPU") is never updated. We're writing a TX desc that references a `bp_idx`
  the BPPE ring doesn't currently hold
- HW may DMA from `bp_dma + bp_idx*BP_SIZE`, but metadata about ownership lives
  in the BMU and we've bypassed it entirely
- Kicks return success counters but no payload reaches wire

**Stock decomp** explicitly does an alloc-kick + poll (see comment at L2113-2117):
```
tm[0x8014] |= 1; poll tm[0x8014]&3==0; read tm[0x800c]; bit31=error, [15:0]=bp_idx
```

We documented this protocol in a comment, then **chose not to use it** and added
a stub with a "HACK" warning. That tech-debt is now load-bearing failure.

### 🔴 #2 — Replay system is doing harm, not just being incomplete

`zx-replay/{stock.bin (22363 entries), cla.bin (780), pm.bin (1025)}` are
captured from another unit's running state with **a different MAC and a
different DDR map**. We re-patch 4 DDR pointers after replay (L2931-2953)
because the bulk replay overwrites them with stock's reserved-DDR addresses
(0x4FF1F000, 0x4FFDF000, 0x4FFEF000).

But TM has **5 buffer-base pointers per instance × 4 instances = 16 pointers**.
We only re-patch 4. The other 12 still hold stock's DDR addresses — HW BMU
may allocate from those for RX queue 1..7 and silently corrupt random kernel
memory there. RX "works" mostly because queue 0 is fine.

Beyond that: stock's runtime state has stock's CPU MAC slots, stock's FDB hash
entries (using stock's MAC), stock's runtime queue cursors. Replay is paying
the cost of "replicate the whole HW state" **without the benefit**.

Phase 7 has "replace bulk replay with explicit init" already pending. Reviewer
recommends bringing it forward.

### 🔴 #3 — `lan_up_port` hardcoded to 0, real value unknown

From `lan_up_port_lifecycle.md`: `lan_up_port` is set by
`tm_set_p2pmode(macfiltermode)` from `sw_other_set_wan_lan_switch`. Stock
prints `"lan_up_port=0x%x\n"` at boot. We've never captured that print in
any kotrace run.

Our TX desc port encoding `((0 + 0x28) & 0x3f) << 4 = 0x280` is almost
certainly wrong. Combined with empty HW FDB, the switch falls back to
flooding (= the LOOPBACK drops we see).

## Other things the reviewer flagged

### Reverts indicate too many variables changing at once

Three reverts in Phase 5:
- `1f22809a6` — revert smart bp offset detect (made it worse)
- `91ab13e04` — revert FDB hardcode (didn't help)
- `ce98884b0` — revert UP-only TX kick (INCREASED dupes)

Pattern: change-then-test loop has too many independent variables under change
at once. Should be: baseline + 1-change + measure + commit/revert. Current
cumulative state may have unreverted noise (e.g., `fdb_learned[]` dynamic
learning at L1950-1962 is still active and adding entries we can't easily
reason about).

### We've never kotraced a *working* TX

All stock RE so far is on boot-init paths. We've never captured stock's
`pon_tm_net_tx` actually running with `tcpdump on host` confirming a packet
on wire. One kotrace probe on `pon_tm_net_tx` + `pon_tm_data_raw_send` with
skb-data dump on a stock unit pinging the host gives us the **exact desc
bytes + bp_idx** for a known-good TX. Diff with ours = answer.

### PP IRQ matters less than thought

PP IRQ signals exceptional events (table full, security violations, link state).
Servicing it would be correct upstream behavior but **is not what's blocking
bidi ping**. FDB learning happens in HW silently. Phase 5e was a misdirection.

## Recommended re-ordering of Phase 5

Reviewer says:
1. ❌ **NOT** implementing `sbrg_add_mactable` next — incremental progress on
   right problem-class but won't fix it alone; another wasted build cycle
2. ✅ **Canary experiment first** — `memset(bp_buf, 0xAB, BP_SIZE)` before
   memcpy, tcpdump host. If wire shows `AB AB AB...` → HW DMAs from expected
   BP. If not → BMU desync confirmed.
3. ✅ **Disable bulk replay** for one test — see if RX still works without
   `fpga.bin`. Removes 25k unknowns from debug surface in one stroke.
4. ✅ **Kotrace stock `pon_tm_net_tx` during ping** — capture a real successful
   TX (desc bytes + bp_idx + skb data) on stock. Diff with mainline.
5. ✅ **THEN** implement real BMU allocator (`zx_bmu_alloc_bp` correctly) +
   `sbrg_add_mactable` + correct `lan_up_port`.

## Cited files & line numbers

- `linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c`
  - L2118-2125 BMU bypass (the HACK)
  - L1685-1689 known 5-pointer comment (we knew)
  - L2880-2894 partial DDR-pointer patch (only 4 of 16)
  - L2849-2926 bulk replay (the 22k+ writes)
  - L2207-2245 TX desc fill
  - L1705-1715 RX canary pattern (template for TX canary)
  - L1950-1962 fdb_learned[] dynamic learning (still active)
- `tasks/00.10.02.re-stock-kmods/findings/lan_up_port_lifecycle.md` — L8-15 setter
- `tasks/00.10.02.re-stock-kmods/findings/tx_path_stock_decomp.md` — L100-105 consumer
- `tasks/00.01.eth-driver/findings/stock_register_state_2026-05-24.md` — PP per-port values

## TL;DR

> Fix the BMU bypass first (or prove it's irrelevant via the canary experiment),
> kill the bulk `fpga.bin` replay, then capture stock's actual `lan_up_port`
> value via kotrace. **Then** implement `sbrg_add_mactable`. In that order.
> The current "add more replay + more init calls" loop is a local minimum.

## Self-assessment honesty check

The reviewer caught what I had been postponing/avoiding:
- I added the BMU bypass with a "HACK" comment and never came back to it
- I knew the replay was approximate but used it as a crutch
- I never asked "what if our most basic assumption (BMU alloc works) is wrong"

The kotrace approach was correct, but **we kotraced the wrong paths** —
init-time, not runtime-TX. Easy to fix in the next iteration.
