# Stock-LIVE IDM-ring usage oracle (2026-05-28)

**VERDICT: stock CPU→LAN egress DOES NOT USE the IDM ring.**
(And it does not use the TM UP ring either — it uses *neither* DMA ring.)

## What was measured

Booted **factory stock** (DTR pulse via the uart-bridge control port 9998 →
`uart.py auto_stock` lets cspstart autoboot NAND; fell through to the pristine
factory rootfs — `Linux H3600 V9 4.1.25`, `/bin/fpga` present, no `devmem`,
no netshell). Root SSH (`admin`/`UkuGPeyRDU`, paramiko `invoke_shell`).

Reg-read tool = `/bin/fpga -r <wordidx> 1` where `wordidx = (phys-0x92000000)/4`.
Output lands in the **kernel ring**, captured with `cat /proc/kmsg >/tmp/k &`
then `grep 'fpga read'` (matches the prior oracle's method exactly; `dmesg`
ring had already wrapped so the live `/proc/kmsg` capture is required).

Egress generated from the **host**: `ping -c N 192.168.1.1` (stock echoes N
ICMP replies out MAC2/LAN). Read all 5 regs before and after.

| phys | wordidx | reg |
|---|---|---|
| 0x921c8040 | 0x72010 | IDM TX **kick** |
| 0x921c8044 | 0x72011 | IDM TX **consume/done** ← KEY |
| 0x921d0058 | 0x74016 | TM UP-ring consume (control, expect 0) |
| 0x9234c044 | 0xd3011 | QMG **sw_fwd** (egress confirm) |
| 0x92280718 | 0xa01c6 | MAC2 **TX-OK** (egress confirm) |

## Run 1 — host `ping -c 50`

| reg (phys) | BEFORE | AFTER | delta |
|---|---|---|---|
| 0x921c8040 IDM kick    | 0x00000000 | 0x00000000 | **0** |
| 0x921c8044 IDM consume | 0x00000000 | 0x00000000 | **0 ← KEY** |
| 0x921d0058 TM UP consume | 0x00000000 | 0x00000000 | 0 (control) |
| 0x9234c044 QMG sw_fwd  | 0x000000a3 | 0x000000f0 | **+0x4d (+77)** |
| 0x92280718 MAC2 TX-OK  | 0x000000a3 | 0x000000f0 | **+0x4d (+77)** |

## Run 2 (confirmation) — host `ping -c 100`

| reg (phys) | BEFORE | AFTER | delta |
|---|---|---|---|
| 0x921c8040 IDM kick    | 0x00000000 | 0x00000000 | **0** |
| 0x921c8044 IDM consume | 0x00000000 | 0x00000000 | **0 ← KEY** |
| 0x921d0058 TM UP consume | 0x00000000 | 0x00000000 | 0 (control) |
| 0x9234c044 QMG sw_fwd  | 0x0000010a | 0x00000188 | **+0x7e (+126)** |
| 0x92280718 MAC2 TX-OK  | 0x0000010a | 0x00000188 | **+0x7e (+126)** |

Raw kmsg lines (run 2 AFTER):
```
<4>fpga read: reg=0x00072010, value=0x00000000   # IDM kick
<4>fpga read: reg=0x00072011, value=0x00000000   # IDM consume  <-- stays 0
<4>fpga read: reg=0x00074016, value=0x00000000   # TM UP consume
<4>fpga read: reg=0x000d3011, value=0x00000188   # QMG sw_fwd
<4>fpga read: reg=0x000a01c6, value=0x00000188   # MAC2 TX-OK
```

## Interpretation (tie every number to its reg)

- **QMG sw_fwd (0x9234c044) and MAC2 TX-OK (0x92280718) climb in perfect
  lock-step** — run1 both +0x4d, run2 both +0x7e. So the device really did
  egress (≈ping count + a few stray LAN frames) out MAC2 during each window.
  Egress is confirmed and sw-forwarded (sw_fwd, not hw_fwd — consistent with
  the prior oracle).
- **IDM consume (0x921c8044) stayed 0x00000000 across both runs** while
  126 frames egressed. The IDM kick (0x921c8040) also stayed 0. **The IDM
  CPU-port DMA ring counters DO NOT MOVE during stock CPU→LAN egress.**
- **TM UP consume (0x921d0058) stayed 0** — reconfirms the prior oracle:
  the UP DMA ring is also unused.

### ===> HEADLINE / FLAG-IT <===
Stock egresses CPU→LAN frames using **NEITHER the IDM ring NOR the UP ring.**
Both ring kicks (IDM 0x8040, UP TM[0x10054]) and both consume counters
(IDM 0x8044, UP 0x10058) are flat 0 while QMG sw_fwd + MAC2 TX climb together.

This **refutes** the IDM-ring hypothesis recorded in STATE.md Journey #10 /
`idm_ring_xmit_test_result_2026-05-28.md`. The mainline IDM-ring rewrite
(`zx_sw_xmit` → IDM ring, npp+0x8044 increments on txtest) was making the
**hardware** consume descriptors on a ring that **stock itself never uses for
this path**. That is why mainline's IDM-ring frames die before the QMG: the IDM
ring is not the stock CPU→LAN inject mechanism.

The real stock inject path is **something else** — it pushes CPU frames into
the switch fabric such that QMG sw_fwd counts them with *both* DMA-ring consume
counters untouched. Candidates to investigate next (not measured here):
a memory-mapped/PIO CPU-port inject FIFO, a doorbell other than 0x8040/0x10054,
or a BMU/buffer-pointer hand-off that enqueues straight into the QMG sw_fwd
queue. The next RE step should trace stock's actual TX submit for a
CPU-sourced LAN frame and find the write that makes QMG sw_fwd (0x9234c044)
increment with IDM 0x8044 and TM 0x10058 both at 0.

## Method notes (for next time)
- Bridge owns /dev/ttyUSB0; go through it: `UART_TCP=1 python3 lib/uart.py …`
  and DTR control is the bridge's port 9998. Don't open the tty directly.
- `auto_stock` = DTR reset + no boot interception → cspstart → NAND factory.
- factory busybox: no `tail`/`head`; `sed -n '$p'` works. `dmesg` ring wraps —
  use the live `/proc/kmsg` capture for fpga reads.

## Device left
On STOCK (NAND boot), **reads only — no registers written, no NAND flashed,
no reboot**. Left running stock as found (per instructions: user will reboot
to mainline). SSH session closed cleanly.
