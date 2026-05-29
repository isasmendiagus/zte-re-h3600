# Stock TM DN-ring RE-MEASURE (corrected method) — 2026-05-28

**VERDICT (one line): the DN ring is GENUINELY UNUSED — `0x921d0068` TM DN
consume (and cursor `0x1006c`, kick `0x1c0064`) stay flat 0 across egress even
with the corrected warmup+throwaway+double-read method, while QMG sw_fwd /
MAC2 TX-OK climb in lock-step. The earlier "no ring" was NOT a measurement
artifact — the decomp↔hardware contradiction is REAL and deeper.**

## Method (the corrected one — reads only)
Booted factory stock (cold DTR pulse via uart-bridge ctl port 9998 →
`UART_TCP=1 python3 lib/uart.py auto_stock`; cspstart autoboots NAND →
`Linux H3600 V9 4.1.25`, `/bin/fpga` present). Root SSH `admin`/`UkuGPeyRDU`
(paramiko invoke_shell). Egress generated from host
`ping -c N -i 0.05 192.168.1.1`; N/N replies each run.
Reg read = `/bin/fpga -r <wordidx> 1`, wordidx=(phys-0x92000000)/4.
Per snapshot: ONE persistent `cat /proc/kmsg`, ~1.2s warmup, **one throwaway
fpga read (0xd3011) which the kernel ring drops**, then real reads; KEY regs
read **TWICE** in the same snapshot and the LAST value kept (so a dropped first
read is seen and discarded). No `&`-subshells around fpga, no per-reg cats.
Script: `tasks/00.10.02.re-stock-kmods/scripts/dn_ring_remeasure.py`.

## Run 1 — host `ping -c 100`
| reg (phys) | word | BEFORE | AFTER | delta | note |
|---|---|---|---|---|---|
| 0x921d0068 TM DN **consume** ← KEY | 0x7401a | 0x00000000 | 0x00000000 | **+0** | dbl-read [0,0] both phases |
| 0x921d006c TM DN cursor | 0x7401b | 0x00000000 | 0x00000000 | +0 | dbl-read [0,0] |
| 0x921d0064 TM DN kick   | 0x74019 | 0x00000000 | 0x00000000 | +0 | dbl-read [0,0] |
| 0x921d0058 TM UP consume| 0x74016 | 0x00000000 | 0x00000000 | +0 | control |
| 0x921d005c TM UP cursor | 0x74017 | 0x00000000 | 0x00000000 | +0 | control |
| 0x9234c044 QMG sw_fwd   | 0xd3011 | 0x00000051 | 0x000000d1 | **+128** | egress confirm |
| 0x92280718 MAC2 TX-OK   | 0xa01c6 | 0x00000053 | 0x000000d3 | **+128** | egress confirm |

## Run 2 — host `ping -c 200`
| reg (phys) | word | BEFORE | AFTER | delta | note |
|---|---|---|---|---|---|
| 0x921d0068 TM DN **consume** ← KEY | 0x7401a | 0x00000000 | 0x00000000 | **+0** | dbl-read [0,0] both phases |
| 0x921d006c TM DN cursor | 0x7401b | 0x00000000 | 0x00000000 | +0 | dbl-read [0,0] |
| 0x921d0064 TM DN kick   | 0x74019 | 0x00000000 | 0x00000000 | +0 | dbl-read [0,0] |
| 0x921d0058 TM UP consume| 0x74016 | 0x00000000 | 0x00000000 | +0 | control |
| 0x921d005c TM UP cursor | 0x74017 | 0x00000000 | 0x00000000 | +0 | control |
| 0x9234c044 QMG sw_fwd   | 0xd3011 | 0x000000ed | 0x00000196 | **+169** | egress confirm |
| 0x92280718 MAC2 TX-OK   | 0xa01c6 | 0x000000ef | 0x0000019f | **+176** | egress confirm |

## Run 3 (confirmation) — host `ping -c 300`, EVERY reg double-read
| reg | BEFORE(last) | DURING raw [1st,2nd] | delta |
|---|---|---|---|
| 0x921d0068 DN consume | 0x00000000 | [0x0,0x0] | **+0** |
| 0x921d006c DN cursor  | 0x00000000 | [0x0,0x0] | +0 |
| 0x921d0064 DN kick    | 0x00000000 | [0x0,0x0] | +0 |
| 0x9234c044 QMG sw_fwd | 0x00000200 | **[0x2b2,0x2bd]** | +189 |
| 0x92280718 MAC2 TX-OK | 0x00000204 | **[0x2c8,0x2d3]** | +207 |

## Why this is conclusive (the first-read-drop is accounted for, not the cause)
- The corrected method's whole point is the first-read-drop. In Run 3 the
  DURING double-reads of sw_fwd `[0x2b2→0x2bd]` and MAC2 `[0x2c8→0x2d3]` **DIFFER**
  — i.e. these live counters incremented BETWEEN the two reads inside one
  snapshot, proving the device was actively egressing during the read window
  AND that the throwaway/double-read discipline is working.
- In that SAME window, the DN consume/cursor/kick double-reads are `[0x0,0x0]` —
  a stable, genuine zero, not a dropped printk. There is no dropped read to
  rescue: the register really holds 0 on both reads.
- Raw kmsg (run2 DURING): `reg=0x0007401a value=0x00000000` (twice),
  `reg=0x0007401b 0` (twice), `reg=0x00074019 0` (twice), UP regs 0,
  `reg=0x000d3011 value=0x00000196`, `reg=0x000a01c6 value=0x0000019f`.

## Verdict
QMG sw_fwd (0x9234c044) and MAC2 TX-OK (0x92280718) climb in lock-step every
run (+128/+128, +169/+176, +189/+207 — surplus over ping count = stray LAN
frames), so egress is real and software-forwarded. But TM DN consume
(0x921d0068), DN cursor (0x921d006c) and DN kick (0x921d0064) are flat 0 — and
this is confirmed by reading them twice per snapshot under the corrected
warmup+throwaway method, so it is NOT a false zero from a dropped read.

**The DN ring is genuinely NOT used by stock CPU→LAN egress. The earlier
0x10068=0 was correct, not an artifact.** The decomp (`pon_tm_net_tx` dir-1 →
`pon_tm_data_raw_send(...,1)` → `soft_insert_tx_1desc` → kick TM[0x10064]) does
NOT match live stock behaviour for this path — the contradiction is real and
deeper. Do NOT replicate the DN-ring dir-1 kick in mainline as the fix; the
stock inject is a ring-less software-forward straight into the QMG sw_fwd queue
(consistent with all prior IDM/UP/DN oracles). Next RE must find the actual
sw_fwd enqueue write, not a ring doorbell.

## Device left
On STOCK (NAND boot). Reads only — no registers written, no NAND flashed, no
reboot issued. SSH closed cleanly.
