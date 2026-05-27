# Phase 52 bench test — partial win, ping still broken

Tested 2026-05-27 ~08:00 UTC. TFTP-booted mainline kernel containing
Phase 52 (PHY IRQ + MAC.ctrl link callback). Cable on LAN 3 (PHY[2] =
MAC[2]) plus a second cable on LAN 4 (PHY[3] = MAC[3]).

## What's working ✅

Boot dmesg shows the PHY IRQ → adjust_link path firing:
```
[57.464] mdio-zte-0x9a101000:0a: config_init (LDO arm + TX DAC drive enable)
[57.901] mdio-zte-0x9a101000:0b: config_init (LDO arm + TX DAC drive enable)
[58.498] mdio-zte-0x9a101000:0c: config_init (LDO arm + TX DAC drive enable)
[59.096] mdio-zte-0x9a101000:0d: config_init (LDO arm + TX DAC drive enable)
[59.305] sw: PHY[2] link UP @ 1000/FD → MAC[2].ctrl=0xba6003
[62.900] PHY init complete (4 GePHYs attached)
[66.907] sw: PHY[3] link UP @ 1000/FD → MAC[3].ctrl=0xba6003
```

Live readout post-init:
```
MAC[0].ctrl = 0xBAE003  (no cable, init default — stock has 0xBAE000;
                         we don't transition idle→default via callback)
MAC[1].ctrl = 0xBAE003  (same)
MAC[2].ctrl = 0xBA6003  ← matches stock linked pattern
MAC[3].ctrl = 0xBA6003  ← matches stock linked pattern
```

`net sw: could not add device link to mdio-zte-0x9a101000:0X err -17`
warnings appear for PHYs 1..3 — expected, only PHY 0 gets the "primary"
attach; subsequent attaches succeed at phy_attach_direct level but the
sysfs symlink-attach (single attached_dev slot per netdev) refuses.
This is cosmetic; our `e->gephy[]` array tracks them all fine and the
link callbacks fire correctly.

## What's still broken ❌

```
tm_irq_count = 0       ← TM IRQ never fires (same as pre-Phase-52)
tm_napi_count = 0      ← NAPI poll never runs
tm_rx_count = 0        ← no frames delivered to sw netdev
```

Ping host → device: **100 % loss** on both LAN 3 and LAN 4 cables.

## What's NEW (interesting!) 🆕

Queue counters now show traffic distributed across multiple queues
(was just q[0] before):
```
q[0] = 0x00030000   ← 3 frames pending, 0 consumed
q[2] = 0x0000002d   ← 45 cursor advanced
q[4] = 0x0000002f   ← 47 cursor advanced
q[5] = 0x0000000f   ← 15 cursor advanced
```

The switch IS forwarding frames to multiple queues now that MAC[2]
and MAC[3] are properly enabled. So the **switch RX path works** —
the missing piece is the **TM IRQ gate** that should fire on
TM[0x100] bit 0 when frames arrive.

## What this means

MAC.ctrl was a real bug but NOT the (only) blocker for ping bidi.
Fixing it unblocks frames reaching multiple TM queues (good sign),
but NAPI never runs because the TM RX IRQ bit 0 doesn't assert.

The TM IRQ gate is its OWN bug — separate from MAC.ctrl. Hypothesis
from Phase 47 investigation: stock has some extra TM register write
that gates bit 0 from "queue has data" → "IRQ fires" that we haven't
ported yet.

## Next investigation (no driver code per user instruction)

Things to look at while user is AFK:

1. **Compare TM[0x100..0x140] register block stock vs mainline** —
   read full TM IRQ control area on stock (already have partial snap
   in `stock_regs_lan3_2026-05-27.txt`). Diff for missing writes.

2. **Inspect stock pon_tm_int_init carefully** — already RE'd but
   may have missed a register write that gates bit 0.

3. **Look for queue-counter → IRQ-bit translation** — there's likely
   a per-queue config register that says "when queue N has more than
   T entries, raise bit 0 of TM[0x100]". Threshold/credit register.

4. **Boot log shows IRQ numbers shifted** (TM = IRQ 24 now, was 20).
   That's because phy_request_interrupt allocated 4 new linux IRQ #s.
   The GIC SPI mapping for TM is still 68; linux IRQ # is virtual.
   Not a bug, just a note.

## Test mechanics

Cable currently on LAN 3 + LAN 4 from earlier swap experiments.
Slot A has factory stock; mainline is RAM-only via TFTP. To return
to mainline state for further testing, run
`python3 tasks/00.01.eth-driver/scripts/tftp_boot_mainline.py`.
