# Stock vs mainline register diff — ground-truth comparison

Captured 2026-05-27 ~07:30 UTC. Device rebooted to factory pristine
stock firmware (uImage from `ext/extracted/` flashed to slot A via
`tasks/00.04.flash-tool/flash.py both`). SSH access enabled via admin
web UI config. Register reads done via `/bin/devmem2` over SSH.

**Test setup**:
- Cable plugged in LAN 3 (= PHY[2] = MAC[2])
- `ping -c 3 192.168.1.1` from host → 0% loss, 11.6 ms ← stock works
- Read same physical addresses as the mainline cable-swap experiment

## Mapping confirmed

| Physical port | MDIO addr | PHY[i] | MAC[i] | Base addr |
|---|---|---|---|---|
| LAN 1 | 0xa (10) | PHY[0] | MAC[0] | 0x92200000 |
| LAN 2 | 0xb (11) | PHY[1] | MAC[1] | 0x92240000 |
| LAN 3 | 0xc (12) | PHY[2] | MAC[2] | 0x92280000 |
| LAN 4 | 0xd (13) | PHY[3] | MAC[3] | 0x922c0000 |
| (wifi RGMII) | — | — | MAC[4] | 0x92300000 |

LAN N = MAC[N-1] (natural 0-indexed). Confirmed by:
- Cable in LAN 3, stock has MAC[2].ctrl = 0xBA6003 (the "linked"
  pattern, bit 19 clear)
- All other MACs = 0xBAE000 (the "init default", bits 0+1 clear)

## Stock register snapshot (ping bidi WORKING)

```
=== MACs (cable on LAN 3 = MAC[2]) ===
MAC[0] @0x92200000 ctrl=0xBAE000  mask=0x3FFF  en=0x80000001  (default init)
MAC[1] @0x92240000 ctrl=0xBAE000  mask=0x3FFF  en=0x80000001  (default init)
MAC[2] @0x92280000 ctrl=0xBA6003  mask=0x3FFF  en=0x80000001  ← LINKED + ACTIVE
MAC[3] @0x922c0000 ctrl=0xBAE000  mask=0x3FFF  en=0x80000001  (default init)
MAC[4] @0x92300000 ctrl=0x0       en=0x0                       (RGMII / wifi off)

MAC[0].D00 = 0x0
MAC[0].D30 = 0x0

=== TM IRQ ===
TM[0x100] IRQ_STATUS = 0x00000010   ← only bit 4 set
TM[0x104] IRQ_MASK   = 0xFFFFFFFC   ← bits 0+1 BOTH unmasked
TM[0x108]            = 0x0
TM[0x10C]            = 0x0

=== TM queue counters (low16=consumed cursor, high16=ingressed total) ===
q[0..7] all = 0x0  ← drained by NAPI (consumed catches up with ingressed)

=== Port isolation table @ 0x923883c0..0x923883dc ===
port 0: 0xFE   port 1: 0xFD   port 2: 0xFB   port 3: 0xF7
port 4: 0xEF   port 5: 0xDF   port 6: 0xFF   port 7: 0xFF
```

## Mainline snapshot (ping bidi BROKEN, same cable on LAN 3 = MAC[2])

```
=== MACs ===
MAC[0] ctrl=0xBAE003  mask=0x3FFF  en=0x80000001
MAC[1] ctrl=0xBAE003  mask=0x3FFF  en=0x80000001
MAC[2] ctrl=0xBAE000  mask=0x3FFF  en=0x80000001   ← BITS 0+1 CLEAR (disabled!)
MAC[3] ctrl=0xBAE003  mask=0x3FFF  en=0x80000001

=== TM IRQ ===
TM[0x100] = 0x0000000A   ← bits 1+3 set
TM[0x104] = 0xFFFFFFFE   ← only bit 0 unmasked

=== queue counters ===
q[0] = 0x00060000   ← 6 ingressed, 0 consumed = pending forever (NAPI never runs)
q[1..7] = 0x0

=== Port isolation table ===
port 0: 0xFD   port 1: 0xFB   port 2: 0xF7   port 3: 0xEF
port 4: 0xDF   port 5: 0xFE   port 6: 0xBF   port 7: 0x7F
```

## Key diffs

### Diff 1 — MAC ctrl pattern is INVERTED

Stock: default = `0xBAE000` (bits 0+1 clear), linked MAC = `0xBA6003`
       (bits 0+1 set, bit 19 clear).
Main:  default = `0xBAE003` (bits 0+1 set), and **MAC[2] specifically
       ends up `0xBAE000`** (bits 0+1 cleared, no idea who clears them).

What stock does dynamically (and we don't):
- On PHY link UP for port N: `MAC[N].ctrl |= 3` (enable bits 0+1)
- On PHY link UP for port N: `MAC[N].ctrl &= ~0x80000` (clear bit 19)
- On PHY link DOWN: `MAC[N].ctrl &= ~3` (disable bits 0+1)

Our mainline init sets every MAC to "enabled but bit 19 high" and
**never re-configures based on PHY state**. This is the missing
PHY-interrupt handler.

Bit 19 semantics (now clearer): **0 = MAC is RX-ready and linked**;
**1 = MAC is in initial/idle state**. Stock cleared it on the linked
MAC, set on all others. We have it set on all 4.

### Diff 2 — TM IRQ mask

Stock: `0xFFFFFFFC` — bits 0+1 unmasked (RX-done + TX-done IRQs both
       firing and getting handled by stock's NAPI poll).
Main:  `0xFFFFFFFE` — only bit 0 unmasked. We had to mask bit 1
       (Phase 48) because our NAPI poll doesn't process TX
       completions, so HW kept asserting bit 1, causing IRQ storm.

Implication: we need to **implement TX completion reclaim** in
`zx_tm_napi_poll` so bit 1 can stay unmasked without storming. Then
we match stock's IRQ mask.

### Diff 3 — TM IRQ status field meanings

Stock IRQ status = 0x10 (only bit 4) during active ping.
Mainline IRQ status = 0x0A (bits 1+3) — bit 1 = TX-done pending
(never acked), bit 3 = ??? (toggles inconsistently in our experiment).

Stock's "bit 4 only" status suggests bit 4 is "in steady state, RX
queue idle, BMU armed" — i.e., reflecting healthy operation. Bit 0
isn't sticky; it sets, fires the IRQ, and clears as the queue gets
drained.

### Diff 4 — Queue counters drained vs frozen

Stock: all queues at 0 because NAPI keeps up. Each ingressed frame
fires the IRQ, NAPI poll runs, releases the desc, counter goes back
to 0.

Main: q[0] = 0x60000 frozen. 6 frames ingressed (high16 = 6),
0 consumed (low16 = 0). NAPI never runs because the **RX IRQ
gating to TM[0x100] bit 0 isn't firing** for our driver.

### Diff 5 — Port isolation table is COMPLETELY DIFFERENT

Stock pattern:
```
port 0: 0xFE   port 1: 0xFD   port 2: 0xFB   port 3: 0xF7
port 4: 0xEF   port 5: 0xDF   port 6: 0xFF   port 7: 0xFF
```

Mainline pattern:
```
port 0: 0xFD   port 1: 0xFB   port 2: 0xF7   port 3: 0xEF
port 4: 0xDF   port 5: 0xFE   port 6: 0xBF   port 7: 0x7F
```

Stock's values look like one-bit-shift pattern (rotating). Ours look
like the formula `bit-fiddle(don't fwd to self)` which we coded.
We're writing the WRONG formula. Stock's pattern decoded with our
formula gives nonsensical masks (e.g., port 0 = 0x20 = "port 0
can't fwd to CPU port" which would break LAN→CPU traffic — yet
stock ping works).

Conclusion: **either our bit-fiddle formula is wrong**, OR stock
uses a different semantic where the value isn't a strict
"can't-fwd-to" bitmask. Need to re-read stock's
`tm_port_isolate_set` more carefully than the earlier RE attempt.

## What this means for ping bidi

Top three things to fix, ordered by likely impact:

1. **Add PHY-link-aware MAC config**: hook into the phylib link-state
   callback (or run a periodic poller) that does:
   ```
   on link UP on port N:
     MAC[N].ctrl = 0xBA6003  (or equivalent: |3, & ~0x80000)
   on link DOWN on port N:
     MAC[N].ctrl = 0xBAE000  (or equivalent: & ~3, | 0x80000)
   ```

2. **Fix port isolation values**: rewrite `zx_tm_port_isolate_set`
   to produce stock's pattern. Best approach: capture the masks
   stock passes to `tm_port_isolate_set(port, mask)` via kotrace
   instead of trying to derive them from disassembly.

3. **Implement TX completion reclaim**: walk TX descriptor ring on
   each NAPI poll, free completed entries, then unmask TX-done bit
   1 in `TM_IRQ_ARM_BITS`. Once unmasked and acked properly, we
   match stock's `0xFFFFFFFC` mask without storming.

After all 3, the expectation is that RX path comes alive:
- MAC[2] (where cable is) is enabled → frames reach switch
- Port isolation lets MAC[2] forward to CPU port → frames reach queue
- TM IRQ fires → NAPI drains → netdev sees packets

## Raw register dump location

Full stock SSH+devmem2 capture in `/tmp/stock_regs_snapshot.txt`.
Will copy to `tasks/00.01.eth-driver/findings/captures/` in a
follow-up commit.
