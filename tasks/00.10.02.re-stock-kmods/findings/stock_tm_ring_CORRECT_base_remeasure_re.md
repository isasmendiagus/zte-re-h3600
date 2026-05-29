# Stock TM ring RE-MEASURE at the CORRECT base (0x92350000) — 2026-05-28

**VERDICT (one line): at the CORRECTED base the DN ring regs are NOT the pure-0
the wrong base (0x921d00xx) gave — they read a stable `0x00000001` — BUT they do
NOT tick per-packet. DN consume 0x92350068 stays pinned at 0x1 (init value) while
QMG sw_fwd climbs +126/+167 in lock-step with egress. So the DN consume is NOT a
free-running egress counter and does NOT climb with QMG sw_fwd. UP regs flat 0.**

## Method (reads only, corrected /proc/kmsg)
Factory stock (`Linux H3600 V9 4.1.25`, `/bin/fpga` present). Root SSH
`admin`/`UkuGPeyRDU` (paramiko). Egress = host `ping -c N -i 0.05 192.168.1.1`;
N/N replies each run. Reg read `/bin/fpga -r <wordidx> 1`, wordidx=(phys-0x92000000)/4.
Per snapshot: ONE persistent `cat /proc/kmsg`, ~1.2s warmup, one throwaway read
(0xd3011), then real reads; KEY regs read TWICE, keep LAST value (discard dropped
1st). Script: `tasks/00.10.02.re-stock-kmods/scripts/tm_ring_correct_base_remeasure.py`.
Reproduced identically across two full script runs.

## Result table (CORRECTED base 0x92350xxx)
| reg (phys) | word | BEFORE | DURING | delta | note |
|---|---|---|---|---|---|
| 0x92350068 DN consume ← KEY | 0xd401a | 0x00000001 | 0x00000001 | **+0** | pinned at 0x1, dbl-read last=0x1 |
| 0x92350064 DN kick    | 0xd4019 | 0x00000001 | 0x00000001 | **+0** | pinned at 0x1 |
| 0x92350058 UP consume | 0xd4016 | 0x00000000 | 0x00000000 | +0 | control, flat |
| 0x92350054 UP kick    | 0xd4015 | 0x00000000 | 0x00000000 | +0 | control, flat |
| 0x9234c044 QMG sw_fwd | 0xd3011 | climbs | climbs | **+126 / +167** | egress confirm, lock-step w/ ping count |

Raw kmsg (run2 DURING): `reg=0x000d4019 0x1` (x2), `reg=0x000d401a [0x0,0x1]`
(throwaway-drop then 0x1), UP regs 0x0, `reg=0x000d3011 0x00002c0a`.

## Why this matters (vs the wrong-base measurement)
- The wrong base 0x921d00xx (= npp+0x10000 = SMCT/SIPC block) read **pure 0**. The
  corrected base 0x92350xxx reads **0x1** — confirming 0x92350000 is a DIFFERENT,
  real register block (the address-map error in ADDRESS_MAP_ERROR_tm_ring is real:
  the TM ring was never being read before).
- BUT 0x1 is a **static init value, not a packet tick**: it is identical BEFORE
  (idle) and DURING flood, and identical for both -c100 and -c200 runs, while QMG
  sw_fwd in the SAME snapshots climbs +126/+167 (≈ ping count + stray LAN frames).
  The DN consume double-read `[0x0,0x1]` is the expected throwaway-drop then the
  real 0x1 — there is no missed increment.

## Verdict
**NO** — 0x92350068 (DN consume) does NOT climb in lock-step with QMG sw_fwd. It
holds a constant 0x1 across idle and egress. UP 0x92350058 stays flat 0 as
expected. So even at the proven-correct tm_base, the DN ring consume is not a
per-packet egress counter under live stock CPU→LAN egress.

This neither matches the decomp prediction (DN consume should advance per frame)
nor the earlier ring-less conclusion (it's not 0 — the block is real and was
mis-addressed). The 0x1 likely reflects a one-time ring-init / head pointer set at
bringup, not active descriptor consumption. Next RE should: (a) read the DN ring
HEAD/TAIL/level fields (0x10060 base + cursor 0x1006c) and the descriptor memory
itself during egress to see if a head index advances even when this consume latch
does not; (b) re-confirm `soft_insert_tx_1desc(_,1)` actually writes 0x10064 at
runtime (kotrace claims it does) vs. the sw_fwd enqueue being the real path.

## Device left
On STOCK (NAND boot). Reads only — no registers written, no NAND flashed, no
reboot issued. SSH closed cleanly. Two measurement runs, identical results.
