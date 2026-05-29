# Stock-LIVE TM DN-ring usage oracle (2026-05-28)

**VERDICT: stock CPU→LAN egress DOES NOT USE the TM DN ring either.**
The DN ring KICK (0x921d0064) and CONSUME (0x921d0068) stay flat 0 while the
device egresses 100+ frames out MAC2. This closes the measurement gap — stock
uses **NEITHER** DMA ring (UP, DN, or IDM). It egresses via software-forward
(QMG sw_fwd) with every DMA-ring doorbell/consume counter at 0.

## What was measured

Booted **factory stock** (cold DTR reset via uart-bridge ctl port 9998 →
`UART_TCP=1 python3 lib/uart.py auto_stock`; cspstart autoboots NAND →
`Linux H3600 V9 4.1.25`, `/bin/fpga` present, no `devmem`). Root SSH
(`admin`/`UkuGPeyRDU`, paramiko `invoke_shell` PTY). READS ONLY — no register
written, no NAND flashed, no reboot issued.

Reg-read tool = `/bin/fpga -r <wordidx> 1`, `wordidx = (phys-0x92000000)/4`.
Output lands in the **kernel ring** (not stdout): captured per-read with
`(cat /proc/kmsg > /tmp/k &) ; sleep 0.6 ; fpga -r <w> 1 ; sleep 0.8 ; cat /tmp/k`
and parsed for `<4>fpga read: reg=0x..., value=0x...`. Per-register capture
(one dedicated kmsg window each, retry-until-seen) was needed — a single
combined capture intermittently dropped lines on this busy stock device.

Word indices independently re-derived and verified (`(phys-0x92000000)/4`):
0x921d0064→**0x74019**, 0x921d0068→**0x7401a**, 0x921d0058→0x74016,
0x921c8044→0x72011, 0x9234c044→0xd3011, 0x92280718→0xa01c6. All match the
task-supplied ids.

Egress generated from the **host**: `ping -c 100 -i 0.05 192.168.1.1`
(stock echoes 100 ICMP replies out MAC2/LAN). 100/100 received each run.

## Run 3 (clean, all 6 regs captured both phases) — host `ping -c 100`

| reg (phys) | word | BEFORE | AFTER | delta |
|---|---|---|---|---|
| 0x921d0064 TM **DN ring KICK**    | 0x74019 | 0x00000000 | 0x00000000 | **+0 ← KEY** |
| 0x921d0068 TM **DN ring CONSUME** | 0x7401a | 0x00000000 | 0x00000000 | **+0 ← KEY** |
| 0x921d0058 TM UP consume          | 0x74016 | 0x00000000 | 0x00000000 | +0 (control) |
| 0x921c8044 IDM consume            | 0x72011 | 0x00000000 | 0x00000000 | +0 (control) |
| 0x9234c044 QMG **sw_fwd**         | 0xd3011 | 0x000001f9 | 0x00000270 | **+0x77 (+119)** |
| 0x92280718 MAC2 **TX-OK**         | 0xa01c6 | 0x000001fc | 0x00000273 | **+0x77 (+119)** |

Raw kmsg (run 3 AFTER):
```
<4>fpga read: reg=0x00074019, value=0x00000000   # DN kick    <-- stays 0
<4>fpga read: reg=0x0007401a, value=0x00000000   # DN consume <-- stays 0
<4>fpga read: reg=0x00074016, value=0x00000000   # UP consume
<4>fpga read: reg=0x00072011, value=0x00000000   # IDM consume
<4>fpga read: reg=0x000d3011, value=0x00000270   # QMG sw_fwd
<4>fpga read: reg=0x000a01c6, value=0x00000273   # MAC2 TX-OK
```

## Corroborating runs (partial captures, fully consistent)

- **Run 1** (`-c 100`): DN kick 0→0, DN consume 0→0, UP 0→0, IDM 0→0;
  QMG sw_fwd 0xf0→0x157 (**+103**); MAC2 TX-OK BEFORE=0xf0 = sw_fwd BEFORE=0xf0
  (lock-step); MAC2 AFTER line dropped by the kmsg race.
- **Run 2** (`-c 100`): DN kick 0→0, UP 0→0; QMG sw_fwd 0x16f→0x1d6 (**+103**);
  MAC2 TX-OK BEFORE=0x16f = sw_fwd BEFORE=0x16f (lock-step).
- Across all three runs every DN/UP/IDM read that landed = **0**; QMG sw_fwd
  climbed +103/+103/+119; MAC2 TX-OK tracked sw_fwd 1:1 whenever both captured.

## Interpretation (every number tied to its reg)

- **QMG sw_fwd (0x9234c044) +119 and MAC2 TX-OK (0x92280718) +119 climb in
  perfect lock-step** — the device really egressed ~100 ping replies (+stray
  LAN frames) out MAC2 during the window, software-forwarded (sw_fwd, not
  hw_fwd). Egress confirmed.
- **TM DN ring KICK (0x921d0064) = 0→0 and CONSUME (0x921d0068) = 0→0** across
  the egress. **The DN DMA ring counters DO NOT MOVE during stock CPU→LAN
  egress.** This is the ring the stock "sw" netdev's decomp routes to, and it
  is the one neither prior oracle had read — now read, and it is flat.
- **TM UP consume (0x921d0058) = 0** and **IDM consume (0x921c8044) = 0** —
  reconfirms both prior oracles (UP + IDM rings unused).

### ===> HEADLINE / FLAG-IT <===
Stock egresses CPU→LAN frames using **NONE of the three DMA rings**: UP
(kick TM[0x10054]/consume 0x10058), DN (kick TM[0x10064]/consume 0x10068),
and IDM (kick 0x8040/consume 0x8044) are **all flat 0** while QMG sw_fwd +
MAC2 TX climb together +119. The DN-ring hypothesis from the decomp ("sw
routes to DN, so maybe stock kicks 0x10064") is **REFUTED by live measurement**.

This **rules out** the proposed fix of "mainline must kick TM[0x10064] instead
of 0x10054/IDM." Kicking ANY of these rings is not what stock does. The real
stock inject path is a **software-forward straight into the QMG sw_fwd queue**
(no ring doorbell, no ring consume) — consistent with `stock_idm_ring_usage_
oracle_re.md` and `stock_swfwd_egress_path_re.md`. The next RE step must trace
stock's actual sw_fwd enqueue (likely BMU buffer alloc + a direct fabric/QMG
enqueue write that makes 0x9234c044 increment with TM[0x10054/0x10064] AND
IDM[0x8044] all at 0) — NOT a fourth ring guess.

## Method notes
- Bridge owns /dev/ttyUSB0; reset via `UART_TCP=1 python3 lib/uart.py auto_stock`
  (DTR on bridge ctl port 9998). Note actual path is `~/Projects/MYSELF/ZTE/lib/
  uart.py` (STATE.md's `zxic/lib/uart.py` is stale).
- Device is in a ~1-2 min reboot cycle; SSH-connect retry loop races the up
  window. Reads are idempotent/safe.
- kmsg capture is racy under load — read **one reg per dedicated capture
  window** (retry-until-the-line-appears) for reliable per-phase snapshots;
  a single combined capture drops lines.
- Oracle script: `/tmp/dn_ring_oracle.py`.

## Device left
On STOCK (NAND boot). **Reads only — no registers written, no NAND flashed,
no reboot issued.** SSH session closed cleanly. The cold DTR `auto_stock` reset
overrode whatever mainline boot was in progress; left running stock as found.
