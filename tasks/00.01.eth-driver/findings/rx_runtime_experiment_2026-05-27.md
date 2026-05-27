# RX runtime experiment — handoff state (2026-05-27)

Captured live on bench unit during user-driven debugging session. This
doc consolidates the four mainline snapshots taken via cable-swap,
extracts the surviving hypotheses, and sets up the next step (stock
kernel comparison via UART shell).

## What's running

- **Mainline driver** (commit `eb57a2bac` + uncommitted MAC.ctrl
  `0xBA6003 → 0xBAE003` change in `zx_smac_init_port`).
- **Defconfig** has `CONFIG_MDIO_ZTE=y` + `CONFIG_ZTE_GEPHY=y` (Phase
  50 fix). MDIO bus + PHY driver are loaded — confirmed by debugfs
  PHY readout returning BMSR values.
- **TM IRQ bit 1 masked** (Phase 48). Mask register = `0xFFFFFFFE`,
  only RX bit (bit 0) unmasked.

## Symptom

`ping host → device` returns 100% loss. `tm_rx_count = 0` and
`tm_irq_count = 0` in every mainline snapshot. The chip's per-queue
RX counter at `TM[0x10100]` shows pending frames (`high16 = 6`
after some host traffic on LAN 1) but the TM IRQ never fires
(`TM[0x100] bit 0` stays clear), so NAPI never runs, frames never
reach the netdev.

Meanwhile **TX works** — host sees device's IPv6 link-local NDP via
the linked LAN port, so the wire is alive and our driver completes
transmissions.

## Snapshots (mainline boot, post-init)

All addresses are physical (memdump-readable via the C-init REPL
`/bin/memdump <addr> <len>`).

### Address legend

| Block | Phys addr | What |
|---|---|---|
| MAC[i].ctrl | `0x9220_0000 + i*0x40000` | 0xBAE003 = enable + ??? |
| MAC[i].mask | + 4 | IRQ mask (we set 0xFFFF, gets clobbered to 0x3FFF by replay) |
| MAC[i].en   | + 8 | 0x80000001 |
| TM IRQ status | `0x9234_0100` | bit 0=RX pending, bit 1=TX pending, bit 3=??? |
| TM IRQ mask | `0x9234_0104` | 1=masked |
| TM RX queue counters | `0x9235_0100..0x9235_011c` | low16 = ???, high16 = pending |
| Port isolation table | `0x9238_83c0..0x9238_83dc` | sbragRegTable[57] |
| PHY BMSR | via MDIO bus driver | reg 1 standard IEEE 802.3 |

### Snapshot 1 — LAN 1 (PHY[0]) link UP, host pinging

```
MAC[0] ctrl=0xBAE003  mask=0x3FFF  en=0x80000001
MAC[0].D00 = 0x00000000
MAC[0].D30 = 0x00000000
MAC[2] ctrl=0xBAE000  mask=0x3FFF  en=0x80000001  ← bits 0,1 CLEAR (disabled)
TM[0x100] = 0x0000000A  ← bits 1, 3 set
TM[0x104] = 0xFFFFFFFE
q[0]      = 0x00060000  ← 6 frames pending in HW
PHY[0]    BMSR=0x796D link=1 an_done=1 LPA=0xCDE1 STAT1000=0x7800
PHY[1..3] BMSR=0x7949 link=0
```

### Snapshot 2 — cable disconnected, all PHYs link DOWN

```
MAC[3] ctrl=0xBAE003  (no change from init for the unplugged ports)
TM[0x100] = 0x00000002  ← bit 3 CLEARED (was set)
q[0]      = 0x00060000  (frozen; no new frames since no link)
PHY[0..3] BMSR=0x7949 link=0
```

### Snapshot 3 — cable in LAN 2 (PHY[1]) link UP, no host traffic yet

```
MAC[0] ctrl=0xBAE003  (still set from init)
MAC[1] ctrl=0xBAE003
MAC[2] ctrl=0xBAE000  ← still disabled
MAC[3] ctrl=0xBAE003
TM[0x100] = 0x00000002  ← bit 3 NOT set even though PHY[1] linked
q[0..7]   = 0x60000 / 0  (q[0] unchanged frozen)
PHY[1]    BMSR=0x796D link=1
```

After issuing host pings:
```
tm_tx_count grew 14 → 17 (driver TX'd 3 frames — gratuitous ARPs)
q[0..7] = unchanged
tm_rx_count = 0  ← nothing arrived
```

### Snapshot 4 — cable in LAN 3 (PHY[2]) link UP, no host traffic yet

```
MAC[2] ctrl=0xBAE000  ← STILL disabled even though PHY[2] linked
TM[0x100] = 0x0000000A  ← bit 3 SET AGAIN (mystery — same as snap 1)
q[0..7]   = 0x60000 / 0  (q[0] still frozen, others 0)
PHY[2]    BMSR=0x796D link=1
```

## Port isolation table (decoded)

```
Phys addr   HW value  Reverse-mapped mask  Meaning
9238_83c0   0xFD      0x01                 port 0 doesn't fwd to port 0
9238_83c4   0xFB      0x02                 port 1 doesn't fwd to port 1
9238_83c8   0xF7      0x04                 port 2 doesn't fwd to port 2
9238_83cc   0xEF      0x08                 port 3 doesn't fwd to port 3
9238_83d0   0xDF      0x10                 port 4 doesn't fwd to port 4
9238_83d4   0xFE      0x20                 port 5 (CPU) doesn't fwd to itself
9238_83d8   0xBF      0x40                 port 6 doesn't fwd to port 6
9238_83dc   0x7F      0x80                 port 7 doesn't fwd to port 7
```

**Interpretation**: standard "don't loop frames back to source port"
config. Not a bug. Initial hypothesis ("port isolation blocks all
LAN ports from reaching CPU") was wrong.

## Surviving hypotheses

After snap 1..4 + port-isolation decode, the remaining unknowns:

1. **MAC[2].ctrl gets disabled (bits 0,1 cleared)** somewhere between
   our `zx_smac_init_port` and the post-boot snapshot. Persists across
   linking PHY[2]. Whatever clears it doesn't fire for MAC[0/1/3].
   **Possible cause**: a write in the stock-init replay specifically
   targeting MAC[2]'s ctrl reg.

2. **TM[0x100] bit 3** toggles between snap 1 (set) and snap 2 (clear)
   AND between snap 3 (clear) and snap 4 (set). Doesn't correlate
   cleanly with link state — set in snap 1 (PHY[0] linked) and snap 4
   (PHY[2] linked) but NOT in snap 3 (PHY[1] linked). Unknown semantic.

3. **TM[0x100] bit 0 (RX pending)** never asserts even with `q[0]
   high16 = 6` (6 pending frames). The gate from queue-pending to
   IRQ-pending is broken. This is *the* root cause of RX failing.

4. **`tm_tx_count` grew from 14 → 17** during LAN 2 ping attempt.
   Three TX frames emitted — likely gratuitous ARPs from
   `ip addr add` retries when host pings. So /init's TX path keeps
   trying. But no RX arrives, so ARP never resolves.

## What changed between this and Phase 50 (PING BIDI WORKS, 2026-05-24)

Possible regressions worth knowing:
- Phase 11–14 (Mainline #38) added MDIO + PHY drivers. Phase 50
  fix (defconfig CONFIG_MDIO_ZTE=y) closed this gap.
- Earlier MAC.ctrl was hardcoded to `0xBA6003` (bit 19 clear). Now
  back to stock value `0xBAE003`. Didn't restore ping bidi alone.
- Phase 51 (>>16 fix on queue counter pending field) reverted — not
  the right interpretation.

The PING BIDI WORKS doc (`phase4_PING_BIDI_2026-05-24.md`) says
"99b75df91 — RED queue init unlocked TM IRQs (count 0 → 19M)". So at
some point RED init was working. We still call `zx_tm_red_init()` in
our probe, but the IRQ doesn't gate. Something else is missing.

## The runtime experiment — what we want to learn

We have a **working oracle**: the stock kernel boots from NAND and
ping bidi works perfectly. By reading the *exact same physical
registers* on stock vs mainline (while ping is actively working on
stock, broken on mainline), we will find the diff.

**Specifically the questions to answer:**

1. On stock with ping bidi running:
   - What is `TM[0x100]` (IRQ status)? Bits 0,1 set/clear with what cadence?
   - What is `TM[0x104]` (IRQ mask)? Same as ours (0xFFFFFFFE) or different?
   - What is `MAC[0].ctrl`? Same `0xBAE003` or different?
   - What are the per-queue counters at `TM[0x10100..]`?
   - Are there registers we *don't* touch that have non-zero values?

2. The diff between "stock running ping bidi" and "mainline ping
   broken" pinpoints the exact register(s) we're missing. The set is
   small — these registers are at fixed offsets, both kernels access
   them via the same MMIO window.

## Tactical plan

### Limitation
SSH access dies the moment we unplug the cable. **For the cable-swap
diff we'd lose connectivity.** Solution: spawn a parallel agent to
prep an interactive UART shell on stock (so we can do everything via
serial regardless of cable state). Independent of network.

### Agent task (delegated)
Prepare an interactive shell on stock UART (`/dev/ttyAMA0`) that
survives SSH disconnect. Push `tools/memdump` to `/tmp/memdump`.
Verify by ssh-ing in, kicking off the UART shell, disconnecting
ssh, and reading regs via UART.

### What I'll do in parallel
Read the stock decomp for:
- `pon_tm_red_init` (the RED queue config we ported; verify our port
  matches stock byte-for-byte at the register-write level)
- `pon_tm_int_init` (the IRQ-handler-registration that sets up the
  gate we're missing)
- `pon_tm_queue_init` (where stock allocates the per-queue desc
  rings — relevant for the +0x1000 offset mystery from earlier
  layout finding)

These three are the most likely places where stock does something we
don't, that ends up gating `TM[0x100]` bit 0.

### Register checklist to capture (when stock UART is ready)

```
# Block headers
memdump 92340100 80       # TM IRQ + queue control
memdump 92340500 40       # TM instance 1 control
memdump 92340900 40       # TM instance 2 control
memdump 92340c00 40       # TM instance 3 control

# MACs
memdump 92200000 40       # MAC[0] full first 64B
memdump 92240000 40
memdump 92280000 40
memdump 922c0000 40
memdump 92340000 40       # MAC[4] (wifi RGMII)

# Queue counter window
memdump 92350100 80

# Port isolation + sbrag area
memdump 923883c0 40

# BMU / DMA
memdump 92348000 20       # TM BMU
memdump 92350000 20       # TM DMA

# Also CPU forwarding bits etc.
memdump 92300028 20       # PP

# PHY regs via debugfs (only the linked one matters)
cat /sys/kernel/debug/zx_eth/stats | grep -A4 'PHY link'  # mainline
# Stock equivalent: read PHY directly via /sys/class/mdio_bus
```

## State the user needs to know before walking away

- 6 commits this session: Phase 47/48/49/50/51-reverted plus
  documentation. All on `main`, all boot-verified except Phase 51
  which was reverted.
- Uncommitted: `MAC[0].ctrl = 0xBAE003` (stock-match) change in
  `zx_smac_init_port`. Doesn't fix ping but is correct per decomp.
- TFTP boot mainline kernel still in slot A. Reboot via NAND brings
  back stock automatically. To return to mainline experiment, run
  `tasks/00.01.eth-driver/scripts/tftp_boot_mainline.py` again.
- The "MAC[2] disabled mystery" + "TM[0x100] bit 0 never sets" are
  the two open threads. Stock comparison will likely answer both.
