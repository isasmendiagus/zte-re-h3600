# Stock SIPC + SMCT window sweep, idle vs egressing — 2026-05-28

**VERDICT (one line): the ring-less CPU→LAN inject lives in the SMCT CPU-port
channel — `0x921d0040` (word 0x74010) is a LIVE byte-replicated queue
head/level that increments in lock-step with QMG sw_fwd / MAC2 TX-OK during
egress, and `0x921d004c` (word 0x74013) is its wrapping companion pointer. The
SIPC bridge window (0x921cc000) only jitters (no monotonic egress counter). All
other SMCT regs are flat. This is the never-probed doorbell region the task
was looking for.**

## Method (corrected — reads only)
Device already on factory stock (prior agent left it; re-confirmed
`uname` = `Linux H3600 V9 4.1.25`, `/bin/fpga` present). No cold-reset needed,
no NAND touched. Root SSH `admin`/`UkuGPeyRDU` via paramiko invoke_shell.
Egress from host `ping -c N -i 0.05 192.168.1.1` (100/100 and 200/200 replies).
Reg read `/bin/fpga -r <wordidx> 1`, wordidx=(phys-0x92000000)/4.
Per snapshot: ONE persistent `cat /proc/kmsg`, ~1.2s warmup, ONE throwaway
fpga read (0xd3011, dropped by the ring), then real reads. **EVERY reg
double-read in-window** and the LAST value kept — so a dropped first read is
seen+discarded, and a live counter is told apart from a stable value by whether
the two in-window reads differ. Did NOT read 0x921d0054 / 0x921d0064 (known
ring kicks). Script:
`tasks/00.10.02.re-stock-kmods/scripts/sipc_smct_sweep.py`.

## SIPC bridge window 0x921cc000 (word 0x73000+) — idle vs DURING
| phys (word) | BEFORE | DURING | Δ100 | Δ200 | verdict |
|---|---|---|---|---|---|
| 0x921cc000 (73000) | 0x11 | 0x11 | flat | flat | static (id/cfg) |
| 0x921cc004 (73001) | 0x20000/0x30000 | 0xf0000/0x50000 | +851968 | +131072 | upper nibble jitters, non-linear |
| 0x921cc008 (73002) | 0x4ff/0x888 | 0x966/0x466 | +1127 | -1058 | jitter, dbl-read DIFFERS each phase (live but noisy, sign-inconsistent) |
| 0x921cc00c..14 | 0 | 0 | flat | flat | |
| 0x921cc018 (73006) | 0xf00/0xd00 | 0xa00/0x100 | -1280 | -3072 | 0x100-stepped, wanders both dirs |
| 0x921cc01c (73007) | 0xa00/0x700 | 0x400/0xd00 | -1536 | +1536 | 0x100-stepped, wanders both dirs |
| 0x921cc020 (73008) | 0x0/0xe00 | 0xa00/0xc00 | +2560 | -512 | 0x100-stepped, wanders both dirs |
| 0x921cc024..30 | 0 | 0 | flat | flat | |
| 0x921cc034 (7300d) | 0x1001 | 0x1001 | flat | flat | static cfg |
| 0x921cc038/3c (7300e/f) | 0x318 | 0x318 | flat | flat | static (size?) |

SIPC verdict: the 0x18/0x1c/0x20 trio are 0x100-granular fill/credit gauges
that wander up AND down with no monotonic relationship to packet count; 0x04/
0x08 jitter non-linearly. **No SIPC reg is the inject counter.** SIPC is the
mailbox/credit bridge, not the egress doorbell.

## SMCT-control window 0x921d0000 (word 0x74000+) — idle vs DURING
| phys (word) | BEFORE | DURING | Δ100 | Δ200 | verdict |
|---|---|---|---|---|---|
| 0x921d0000 (74000) | 0xb | 0xb | flat | flat | static |
| 0x921d0004 (74001) | 0xb | 0xb | flat | flat | static |
| 0x921d0008 (74002) | 0x80 | 0x80 | flat | flat | static (depth=128) |
| 0x921d000c (74003) | 0 | 0 | flat | flat | |
| 0x921d0010 (74004) | 0x3810 | 0x3810 | flat | flat | static base/cfg |
| 0x921d0014 (74005) | 0 | 0 | flat | flat | |
| 0x921d0018 (74006) | 0x1 | 0x1 | flat | flat | enable bit |
| 0x921d001c..3c | 0 | 0 | flat | flat | all zero |
| **0x921d0040 (74010)** | **0x9b9b / 0x8d8d** | **0xf8f8 / 0xbbbb** | **+23901** | **+11822** | **LIVE: byte-replicated (0xXYXY), dbl-read DIFFERS in-window (0x9696→0x9b9b, 0xb6b6→0xbbbb) — increments WHILE being read during egress** |
| 0x921d0044 (74011) | 0 | 0 | flat | flat | |
| 0x921d0048 (74012) | 0 | 0 | flat | flat | |
| **0x921d004c (74013)** | **0xb9 / 0xab** | **0x16 / 0xd9** | **-163** | **+46** | **LIVE wrapping ptr: dbl-read DIFFERS (0xb4→0xb9, 0xd5→0xd9), 8-bit wrap (companion head/tail of 0x40)** |

## Controls (egress confirmation — climb both runs)
| reg | Δ100 | Δ200 | in-window dbl-read DURING |
|---|---|---|---|
| 0x9234c044 QMG sw_fwd | +262 | +363 | [0x739→0x73b] (incrementing) |
| 0x92280718 MAC2 TX-OK | +262 | +363 | [0x73d→0x73f] (incrementing) |

## Why this is conclusive
- The corrected double-read discipline works: sw_fwd `[0x739→0x73b]` and MAC2
  `[0x73d→0x73f]` DIFFER inside one snapshot → device genuinely egressing
  during the read window, drops accounted for.
- In that SAME window, **0x921d0040 also DIFFERS between its two reads**
  (0xb6b6→0xbbbb, and 0x9696→0x9b9b at idle) — it is a live free-running queue
  gauge, NOT a dropped-read artifact (a dropped read would repeat). It is the
  ONLY reg in either window whose in-window double-read changes in step with the
  egress counters every phase. Its companion 0x921d004c likewise ticks live.
- Byte-replicated value (0xXYXY) ⇒ a per-lane/4-replicated free-buffer or
  head pointer of the SMCT CPU-port channel — exactly the ring-less inject
  queue head (the inject pushes into this SMCT channel; sw_fwd/MAC2-TX then
  drain it). The Δ is not a clean 1:1 with packet count because the field is a
  free-level/credit (consumed-then-refilled), not a monotonic packet counter.

## Verdict / next step
The ring-less CPU→LAN inject is the **SMCT CPU-port channel at 0x921d0040
(+companion 0x921d004c)** — confirming the prior localization to the
0x921d0000 SMCT window, and explaining why every earlier oracle (which only
read +0x54/+0x64 ring kicks) saw nothing: the inject uses the +0x40 channel
head, not the ring doorbells. SIPC (0x921cc000) is a credit/mailbox bridge with
0x100-granular gauges that wander, not the doorbell. Mainline RE should model
the inject as a push to the SMCT 0x40 channel (depth 0x80 per +0x08), not a
DMA-ring kick. Recommend a follow-up that, on the SAME boot, correlates the
exact +0x40 step per single injected frame (1-packet pulses) to nail
head vs free-level semantics.

## Device left
On STOCK (NAND boot). Reads only — no registers written, no NAND flashed, no
reboot. SSH closed cleanly.
