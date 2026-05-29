# Stock CPU→LAN egress: EMPIRICAL netdev identification + BMU/QMG footprint (2026-05-28)

**VERDICT (Task 1):** The CPU→LAN egress netdev is **`sw`** (its `ndo_start_xmit` =
`pon_tm_net_tx`). `sw` is the egress terminus; `br0` (the L3 iface that holds
192.168.1.1) and `eth3` (the physical copper LAN port) move in identical lock-step
above it, confirming the path **br0 → sw → eth3/MAC2**.

**VERDICT (Task 2):** Egress **does NOT consume BMU buffers** via the alloc/free
pointer path — all 8 BMU registers (0x921c8000–0x921c801c) are byte-for-byte FLAT
across a 600-frame flood. Only **QMG sw_fwd (0x9234c044)** and **MAC2 TX-OK
(0x92280718)** climb. The inject is a pure software-forward into the sw_fwd queue
with zero BMU pool churn and no DMA ring (consistent with all three ring oracles).

## Method (reads only)

Live factory stock `Linux H3600 V9 4.1.25` (cold DTR reset via uart-bridge ctl
port 9998 → `UART_TCP=1 python3 lib/uart.py auto_stock` → NAND slot-0 autoboot).
Root SSH `admin`/`UkuGPeyRDU`, paramiko `invoke_shell`. Egress generated from the
**host** (`enxc8a362e95900` @ 192.168.1.50/24) with `ping -c N 192.168.1.1`;
device echoed N/N replies out MAC2/LAN each run. No registers written, no NAND
flashed, no reboot. Scripts: `tasks/00.10.02.re-stock-kmods/scripts/egress_netdev_id.py`
(netdev) and `…/scripts/reg_diff.py` (regs). fpga reg-read =
`/bin/fpga -r <wordidx> 1`, `wordidx=(phys-0x92000000)/4`, captured from
`/proc/kmsg` (no `devmem` on stock — reconfirmed).

## Task 1 — per-netdev tx_packets delta (from /sys/class/net/*/statistics)

Only THREE of 29 netdevs moved; every other netdev (pon, idm0, idm1, eth0/1/2/4,
all wlan*, nbif*, ifb*) delta = **0**.

| netdev | RUN A (host ping -c 50) | RUN B (host ping -c 100) | role |
|---|---|---|---|
| **sw**  | tx **+80** (554→634) | tx **+130** (662→792) | **CPU→LAN egress (`pon_tm_net_tx`)** |
| **eth3**| tx +80 (542→622)    | tx +130 (650→780)    | physical copper LAN port (carrier UP, in br0) |
| **br0** | tx +80 (528→608)    | tx +130 (636→766)    | L3 bridge master, holds 192.168.1.1 |

Deltas track 1:1 across all three and exceed the bare ping count (+80 for 50,
+130 for 100) by a constant ~+30 = ARP + LAN background frames in the window.
The three move together because the frame traverses **br0 (L3 reply) → sw
(`pon_tm_net_tx` xmit) → eth3/MAC2 (HW egress)**; counters increment at each layer.
`sw` is the netdev whose `ndo_start_xmit` is the actual SW egress entry — RE THAT.

## Topology (`ip -o addr`, `brctl show`)

- **br0** = 192.168.1.1/24, fe80::1; master bridge `8000.f4f6470f4264`, members:
  eth1, eth2, eth3, eth4, nbif0, wlan0, wlan5g0. **eth3** is the only member with
  carrier (`UP,LOWER_UP`); wlan0/wlan5g0 also UP. State UP.
- **sw** = MAC `00:d0:d0:81:82:83`, `UP,LOWER_UP`, qdisc pfifo_fast — NOT a bridge
  member, NOT carrying an IP. It is the standalone switch/mgmt egress netdev.
- **pon** = same MAC as sw (00:d0:d0:81:82:83), UP — the WAN/uplink twin (flag-0,
  UP-ring per decomp); its tx delta = 0 (not the LAN egress).
- idm0/idm1 = 00:d0:d0:61:62:00/01, UP, tx delta 0.

## Task 2 — BMU / QMG reg diff: IDLE vs DURING (host ping -c 600 flood, 600/600 rx)

Two independent runs, identical pattern:

| reg (phys / word) | IDLE | DURING | delta | run-2 delta |
|---|---|---|---|---|
| BMU 0x921c8000 (0x72000) | 0x020f6766 | 0x020f6766 | **0** | 0 |
| BMU 0x921c8004 (0x72001) | 0x4dac4000 | 0x4dac4000 | **0** | 0 |
| BMU 0x921c8008 (0x72002) | 0x4dac0000 | 0x4dac0000 | **0** | 0 |
| BMU 0x921c800c (0x72003) bp_idx | 0x04000800 | 0x04000800 | **0** | 0 |
| BMU 0x921c8010 (0x72004) free   | 0x00000040 | 0x00000040 | **0** | 0 |
| BMU 0x921c8014 (0x72005) alloc  | 0x00000001 | 0x00000001 | **0** | 0 |
| BMU 0x921c8018 (0x72006) | 0x00000040 | 0x00000040 | **0** | 0 |
| BMU 0x921c801c (0x72007) | 0x00001388 | 0x00001388 | **0** | 0 |
| QMG 0x9234c040 (0xd3010) | 0x00000000 | 0x00000000 | **0** | 0 |
| **QMG 0x9234c044 (0xd3011) sw_fwd** | 0x00000e86 | 0x00000f46 | **+192** | **+192** |
| QMG 0x9234c048 (0xd3012) | 0x00000000 | 0x00000000 | **0** | 0 |
| QMG 0x9234c04c (0xd3013) | 0x00000000 | 0x00000000 | **0** | 0 |
| **MAC2 0x92280718 (0xa01c6) TX-OK** | 0x00000e8c | 0x00000f64 | **+216** | **+216** |

Interpretation (every number tied to its reg):
- **sw_fwd (0x9234c044) +192 and MAC2 TX-OK (0x92280718) +216 climb in lock-step**
  → egress confirmed; sw_fwd is the live software-forward counter (it also advanced
  0xe86→0x1137 between the two runs from intervening traffic — a real monotonic
  counter). The +24 MAC2 surplus = stray non-ping LAN egress in the window.
- **ALL 8 BMU regs are byte-identical IDLE vs DURING, and identical across both
  runs.** 0x800c bp_idx=0x04000800, 0x8010 free=0x40, 0x8014 alloc=0x1 never tick.
  These are **static pool-config/state registers, not per-frame alloc counters** —
  the egress inject does **NOT** allocate/free a BMU buffer through this block per
  frame. (This refutes the `stock_swfwd_egress_path_re.md` guess that the inject
  does `pon_tm_bmu_alloc_bp` per frame via 0x8014/0x800c.)
- **Only QMG 0x9234c044 moves in the whole QMG quad** (0x40/0x48/0x4c flat 0).

## Headline for next RE

1. **RE `pon_tm_net_tx` for the `sw` netdev specifically** — that is the empirically
   confirmed `ndo_start_xmit` of the CPU→LAN egress path. Mainline must reproduce
   what `sw`'s xmit does, NOT pon's UP-ring, NOT idm's ring, NOT the DN-ring kick
   (all three rings already proven flat by the oracles).
2. The inject is **BMU-pool-neutral**: it does not churn the 0x921c8000-0x801c BMU
   alloc/free pointers per frame. So the stock "software-forward" enqueue is NOT a
   per-frame `bmu_alloc_bp` → copy → ring. Look instead for the write inside
   `pon_tm_net_tx`/`pon_tm_data_raw_send` that bumps QMG sw_fwd (0x9234c044)
   directly with every BMU pointer AND every ring counter untouched — i.e. a
   fabric/QMG sw-forward enqueue that references an already-resident buffer or
   pushes the skb payload straight into the sw_fwd queue.

## Device left
On STOCK (NAND boot). Reads only — no registers written, no NAND flashed, no
reboot issued. Temp capture files removed. SSH closed cleanly. Uptime ~19 min,
kernel 4.1.25. (The cold DTR `auto_stock` reset overrode the prior mainline boot.)
