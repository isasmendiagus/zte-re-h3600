# WAN-RX one-wrap wedge — RED unwedge LIVE-TESTED on-device (2026-07-03)

Device: live H3600, fresh DTR-boot mainline #464 (RAM boot). Controlled mode, single agent.
Goal: test the ranked RED soft-unwedge from `wan_rx_opcram_re_2026-07-03.md` on the wedged WAN
DN CPU-trap path. Follows the offline RED root-cause RE.

## TL;DR — the RED soft-poke unwedge does NOT work. Durable fix remains HW offload.

The wedge reproduces exactly (QMG DN hw_trap latches at 1024). But **none** of the RED-block
manipulations resume WAN RX→CPU: RAM0 out-buffer rewrite, cfg_enable[1:0] toggle, direct ram1
occupancy-zero write, and even a FULL RED disable all leave hw_trap frozen at 1024 with 100%
WAN loss. All four writes are SAFE (LAN/UP path kept flowing throughout). This is a clean
NEGATIVE result and matches the earlier port1-redwedge conclusion that RED cfg_enable→0 is not a
recoverable lever. The DN CPU-trap-queue pin at 1024 is **not clearable via the RED indirect
RAM (ram0/ram1) or the RED cfg register.**

## STEP 0 — boot + rig

- DTR-booted fresh #464 (`UART_TCP=1 python3 lib/uart.py auto_bootm_dtb_appended`). Confirmed
  fresh probe in dmesg: `TM RED init: 0 failed`, `RED block init (0x92344000): globals + 400
  out-buffer + 0x180 in-buffer queues`, PHY[4](WAN)+PHY[2] link UP, `debugfs ready`. (Board
  uptime counter runs fast — /proc/uptime showed ~6197s while dmesg boot-clock was ~92s; the
  reboot is real, confirmed by the uptime drop 68775→6197 + fresh dmesg.)
- Rig applied at BOOT (initramfs): `lan1=172.31.9.1/24` (carrier up), `lan4=192.168.9.1/24`
  (carrier up), `sw=192.168.1.99`, `ip_forward=1`. Host `enxc8a362e95900` = 192.168.1.50/24 +
  172.31.9.50/24 (kept). Added host PERMANENT ARP `172.31.9.1 → f4:f6:47:0f:42:64`.
- **lan4 ↔ modem HEALTHY**: `fe80::1%lan4 = cc:29:bd:22:b4:2b`, `ping -6 fe80::1%lan4` = 2/2.
- **lan1 host↔device bidi ping did NOT pass this boot** (separate, documented, non-deterministic
  CPU→LAN TX-egress issue — see [[zte-tx-egress-blocker]]). Device RX on lan1 works (smac2
  RX_pkts climbs 166→217 from host background traffic) and device TX reaches QMG DN sw_fwd + DSCH
  (drop=0), but frames don't reach the wire (0 pkts captured on host during device→host ping).
  eg_port=2 + TX-DAC-force are applied (dmesg confirms), SOPC bridge PHY[2] enabled. This is NOT
  on the RED/WAN critical path — the experiment uses lan4 (healthy). LAN health for STEP 3 was
  tracked via the **UP trap path** (LAN→CPU): smac2 RX + UP hw_trap climbing = LAN/UP healthy.

## STEP 1 — clean baseline (pre-wedge)

```
smac4 RX_pkts=198 good_uc=5
QMG DN sw_fwd=42 hw_fwd=0 hw_trap=198   (== smac4 RX, 1:1 trap — healthy)
        UP  sw_fwd=0  hw_fwd=0 hw_trap=127
drops: PP=0 RED[0x1a044]=40 DSCH=0
rx_per_ingress port4(WAN)=198  port2(LAN)=127
```
Every WAN frame traps 1:1 to CPU (hw_trap == smac4 RX == rx_per_ingress port4). Confirms the
documented healthy pre-wedge behaviour.

**RED-occupancy oracle NOT read on-device this session** (root-cause validation gap):
- No `od`/`hexdump`/`dd` applets in the on-device busybox; `busybox od`/`hexdump` also absent.
- The only working reader (`head -c` on the debugfs `mem` file) reads sequentially FROM offset 0,
  so reaching the RED block (offset 0x184xxx) would traverse the **MAC4 hazard region
  (offset 0x140xxx = phys 0x92300000)** via memcpy_fromio — the exact bus-hang hazard. Refused.
- `poke` readback can't read a reg without writing it (verified: `poke 0x9234401c deadbeef` →
  readback 0xdeadbeef, i.e. DATA0 is a normal RW reg, the write lands).
- ⇒ Reading RED ram1 occupancy safely needs a driver-side single-`readl` `peek` debugfs (a small
  rebuild). Not done because the unwedge failed (see STEP 3), so a reader/watchdog has no lever to
  drive. The QMG-level signature (below) validates the mechanism downstream of RED instead.

## STEP 2 — wedge reproduced + validated

`ping -6 -c 1300 -i 0.01 fe80::1%lan4 -q` → 1300 tx, 824 rx, then loss (198 baseline + ~826 = 1024).
Post-wedge:
```
smac4 RX_pkts=1517 good_uc=1309         (WAN MAC RX STILL CLIMBING)
QMG DN sw_fwd=1343 hw_fwd=0 hw_trap=1024 (0x400)  ← FROZEN, the choke
        UP  hw_trap=140                  (LAN/UP still healthy)
drops: RED[0x1a044]=535 (climbing)
rx_per_ingress port4=1024 (frozen)
further WAN ping: 20 tx / 0 rx = 100% loss (permanent)
```
Signature matches the finding EXACTLY: hw_trap frozen at 1024 while MAC RX climbs and sw_fwd
climbs. On-device validation of the mechanism at the QMG-observer level.

## STEP 3 — unwedge tests (all SAFE TM-range pokes; all FAILED to resume WAN RX)

RED indirect (driver defs): CMD 0x92344014 = q|(ram<<22)|(rw<<27); DATA0 0x9234401c;
RED_CFG 0x92344004 = [1:0]cfg_en [2]share_mode [3]trap_color [4]open_out (driver value 0x1E).

| # | poke | result | LAN/UP |
|---|---|---|---|
| (a) | RAM0 out-buffer rewrite q0..7 (CMD=q, DATA0=0x3ff) | hw_trap **still 1024**, 100% loss | healthy (UP hw_trap 140→154) |
| (b) | cfg_enable[1:0] toggle 0x1E→0x1C→0x1E | hw_trap **still 1024**, 100% loss | healthy (UP hw_trap →155) |
| (c) | direct ram1 occupancy=0 write q0..7 (CMD=q\|0x400000 rw0, DATA0=0) | hw_trap **still 1024**, 100% loss | healthy (UP hw_trap →170) |
| (d) | FULL RED disable 0x92344004=0, ping WHILE disabled | hw_trap **still 1024**, sw_fwd still climbs, 100% loss | healthy (UP hw_trap →172) |

Then restored RED_CFG=0x1E; LAN/UP still healthy (smac2 RX 166→217, UP hw_trap →174).

**Interpretation.** The DN CPU-trap-queue occupancy pin is NOT reachable through the RED indirect
RAM interface or the RED enable register. Notably, even a FULL RED disable (d) did not let frames
trap through (they still sw_fwd), so the trap-vs-sw_fwd choke at 1024 is not gated by anything the
RED cfg_enable clears. The pin is an internal HW accounting state cleared only by a block/chip
reset (reboot) — consistent with (i) the port1-redwedge finding that RED cfg_enable→0 was already
ruled out as a recoverable lever, and (ii) every prior session finding the wedge reboot-only.

## STEP 4 — watchdog: NOT implemented

Conditional on STEP 3 working. It didn't — there is no working live poke to drive from a watchdog,
so no watchdog was added. No rebuild performed.

## Strategic conclusion (task-requested)

**HW offload is the durable fix.** The wedge is a symptom of trap-everything: mainline traps ~all
WAN traffic to the CPU, so the DN CPU-trap queue fills its 1024 out-buffer and the trap decision
latches. Offloaded WAN flows don't trap → the RED/QMG DN trap queue never fills → no wedge. The
Phase-6 HW offload framework is built and working (see MILESTONE_hw_offload_working / the
autooffload findings). Bootstrapping one flow costs <1024 trapped frames (fine), then offload stops
the trapping. A software RED-drain watchdog is NOT viable — no RED write drains the pin.

## What a future session needs for the direct RED-occupancy confirmation

Add a minimal `peek` debugfs (single `readl(phys)` → `pr_info` hex, no write side-effect) next to
`zx_poke_write`, rebuild + DTR-boot, then run the ram1 oracle (CMD 0x92344014 = q|0x8400000, read
DATA0 0x9234401c). This is the only SAFE way to read the RED block (avoids the MAC4-traversal
hazard of a sequential `mem` read and the write-corruption of `poke`). Expected: DN qid pinned
~1024. But this only CONFIRMS the mechanism; it does not yield a fix (the unwedge is dead).

## Device left

REPL alive; kernel 6.6.0 #464; RED_CFG restored to 0x1E; LAN/UP→CPU healthy; ip_forward=1.
WAN wedge PERSISTS (hw_trap frozen 1024, reboot-only clear — a fresh DTR boot clears it). WAN/PPPoE
untouched. Host rig kept: 192.168.1.50 + 172.31.9.50 + permanent ARP 172.31.9.1→f4:f6:47:0f:42:64.
No git commit.
