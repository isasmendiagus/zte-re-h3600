# MAC.ctrl + TM IRQ_STATUS bit-deduction experiment

Captured live on bench unit while user manually changed link state.
Goal: figure out which bits in MAC[].ctrl and TM[0x100] are
link-state-dependent, since stock has runtime code that flips these
bits via PHY interrupt handlers (which our mainline driver doesn't
run).

## Setup
- Mainline kernel (commit 17e816751 + uncommitted MAC.ctrl 0xBA6003→0xBAE003 fix)
- Cable on Port 0 (LAN1), initially link UP at 1000 full-duplex
- Snapshots taken via `/bin/memdump <addr> <len>` over the C-init REPL
- Reg base notes:
    - MAC[i] = 0x92200000 + i * 0x40000  (MAC[0]=0x92200000, MAC[1]=0x92240000…)
    - TM IRQ status = 0x92340100, mask = 0x92340104
    - PHY[i] BMSR via debugfs (uses mdiobus)

---

## Snapshot 1 — cable on Port 0, link UP @ 1000 FD

```
=== MACs ===
MAC[0] @0x40000 ctrl=0xBAE003 mask=0x3FFF en=0x80000001
MAC[1] @0x80000 ctrl=...     (truncated in capture)
MAC[2] @0xc0000 ctrl=0xBAE000 mask=0x3FFF en=0x80000001
MAC[3] @0x100000 ctrl=...    (truncated in capture)
MAC[4] @0x140000 ctrl=0x0     (disabled — RGMII to wifi)

=== MAC[0] sub-regs ===
MAC[0].D00 = 0x00000000
MAC[0].D30 = 0x00000000

=== TM ===
TM[0x100] IRQ_STATUS = 0x0000000A    ← bits 1, 3 set
TM[0x104] IRQ_MASK   = 0xFFFFFFFE
TM[0x108..0x120]     = 0
TM[0x10100] (q0)     = 0x00060000    ← high16 = 6 frames

=== PHY link state ===
PHY[0] BMSR=0x796D link=1 an_done=1 LPA=0xCDE1 STAT1000=0x7800
PHY[1] BMSR=0x7949 link=0 an_done=0
PHY[2] BMSR=0x7949 link=0 an_done=0
PHY[3] BMSR=0x7949 link=0 an_done=0
```

## Snapshot 2 — cable DISCONNECTED from Port 0, all PHYs link DOWN

```
=== MACs ===
MAC[0] @0x40000 ctrl=...      (truncated in capture)
MAC[3] @0x100000 ctrl=0xBAE003 mask=0x3FFF en=0x80000001

=== MAC[0] sub-regs ===
MAC[0].D00 = 0x00000000  (unchanged)
MAC[0].D30 = 0x00000000  (unchanged)

=== TM ===
TM[0x100] IRQ_STATUS = 0x00000002    ← bit 3 CLEARED, bit 1 still set
TM[0x104] IRQ_MASK   = 0xFFFFFFFE
TM[0x108..0x120]     = 0
TM[0x10100] (q0)     = 0x00060000    ← unchanged (no new traffic)

=== PHY link state ===
PHY[0] BMSR=0x7949 link=0 an_done=0  ← was 0x796D when link UP
PHY[1] BMSR=0x7949 link=0 an_done=0
PHY[2] BMSR=0x7949 link=0 an_done=0
PHY[3] BMSR=0x7949 link=0 an_done=0
```

## Diff snapshot 1 vs snapshot 2

| Reg                | Link UP   | Link DOWN | XOR / change             |
|--------------------|-----------|-----------|--------------------------|
| MAC[0].ctrl        | 0xBAE003  | (TBD)     | _need clean capture_     |
| MAC[0].mask        | 0x3FFF    | (TBD)     |                          |
| MAC[0].en          | 0x80000001| (TBD)     |                          |
| MAC[0].D00         | 0x00000000| 0x00000000| no change                |
| MAC[0].D30         | 0x00000000| 0x00000000| no change                |
| MAC[3].ctrl        | (TBD)     | 0xBAE003  | _no change vs init_      |
| **TM[0x100]**      | **0x0A**  | **0x02**  | **bit 3 (0x08) cleared** |
| TM[0x104]          | 0xFFFFFFFE| 0xFFFFFFFE| no change                |
| q0 counter         | 0x60000   | 0x60000   | frozen (no traffic)      |
| PHY[0] BMSR        | 0x796D    | 0x7949    | bit 2 (link) + bit 5 (an_done) cleared |

## Findings so far

1. **TM[0x100] bit 3 = "some port has link"** (or "RX FIFO ready"). 
   Set when at least one PHY is linked, clear when all PHYs are down.
   This is a STATUS bit, not a pending-IRQ bit (clearing with mask
   would have no effect — it reflects HW state).

2. **TM[0x100] bit 1 = TX-done pending** (stays set, never cleared by
   our driver — known from Phase 47).

3. **TM[0x100] bit 0 = RX pending** — confirmed NEVER set in any
   snapshot, even when q[0] has 6 frames queued (high16 = 6). This
   confirms our prior finding: HW does not assert bit 0 even when
   there ARE pending frames. There must be another condition that
   gates bit 0.

4. **MAC[0..3].ctrl does NOT change with link state** — because our
   driver doesn't run stock's `switch_phy_int_check` which would
   call `pon_npp_smac_config_speed_duplex` based on PHY status.
   So our MAC.ctrl stays at smac_init's 0xBAE003 forever.

5. **MAC.D00 / D30 = 0** in both snaps. Stock's smac_init clears bit 1
   of D00 and bit 5 of D30 starting from "whatever was there". The
   fact that both reads return 0 suggests they're write-only,
   reserved-zero, or our init already AND'd them to clean state.

## Open data points to capture

- Snapshot 3 (port 1 cable): does MAC[1].ctrl update? Does it stay 0xBAE003?
- Snapshot 4 (port 2 cable): same for MAC[2]
- Snapshot 5 (port 3 cable): same for MAC[3]
- Whether TM[0x100] bit 3 needs to clear/set to gate bit 0 ("RX pending")
- Whether MAC[i].en bit toggles with link
