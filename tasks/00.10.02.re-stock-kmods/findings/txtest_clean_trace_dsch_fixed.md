# DSCH drop FIXED; TX-only trace localizes next gate to DSCH→SOPC (2026-05-28)

## Two new tools landed this session (driver debugfs, DEBUG ONLY)
- `poke` (write `<phys> <val>`) — live register write. + `regdump`/`mem`/`memdump` reads.
- `txtest` (write N) — inject N KNOWN frames straight through `zx_sw_xmit`: dst=host
  MAC (FDB→internal port 3/MAC2), src=device, ethertype 0x88b5, payload "ZXTX"+seq.
  Isolates the TX/egress path with NO ARP/RX/ping/storm noise. THE key diagnostic.

## DSCH drop = FIXED (confirmed)
Root cause (RE'd): the SCH downstream-scheduler per-queue token-bucket shaper had
zero credit (bucket-cap=0) because the driver wrote garbage to the SCH indirect
port instead of filling the shaper RAM. FIX (in source, `zx_sch_init` @ zx-eth-main.c):
proper indirect-RAM init (poll→cmd→data, RAMID2/3 per-queue + RAMID5/6 per-tcont,
fill=1600000, cap=tm_getFillcap(1600000)=200000), 0x20 units × 8 queues, replacing
the 3 garbage writes. dmesg: "SCH shaper RAM init: 32 units x 8 queues, rate=1600000
cap=200000". Live confirmation via txtest: **drop_DSCH d=0** (was +6/test).
Corroborated by the rootfs RE (stock_rootfs_qos_sched_config.md): stock leaves the
shaper at 0 at init and `cspd` fills it at runtime via `tc ... root sp ... linkspeed`;
our fix replays stock `tm_pon_tm_sch_initial`'s init default.

## TX-only trace (4 frames via txtest) — clean deltas
```
QMG fwd (0x9234c044)      d=+5   frame reaches QMG, forwarded
drop_DSCH (0x921da04c)    d=0    NOT dropped (SCH fix holds)
SOPC send2smac0..4        d=0    reaches NO SOPC port (crossbar→MAC stage)
SMAC2 TX (0x92280718)     d=0    MAC never sees it
tm_rx_loopback_drops      0→0    NOT looped to CPU (no storm, unlike ping)
host tcpdump (0x88b5)     -      nothing on the wire
```
NB: under ping (ARP/broadcast) instead of txtest, the same post-DSCH frame STORMS
(loopback +51) — the broadcast/ARP path hairpins; the clean unicast txtest frame
just vanishes. Either way it never reaches SOPC/MAC.

## Next gate (precise): DSCH → SOPC handoff / egress-port assignment
The frame now passes QMG + DSCH but reaches NO `send2smacN` and is not dropped or
looped — it's lost at the DSCH-dequeue → SOPC egress-port-pick. Note QMG increments
**sw_fwd** not **hw_fwd** — the QMG may be software-forwarding (trap) rather than
hardware-forwarding to the egress MAC. Candidates: DSCH out-queue→SOPC/port binding,
the QMG hw-fwd vs sw-fwd decision for CPU-sourced frames, the internal-port→SOPC-port
map, or SOPC/egress enable for the LAN-up path. The SOPC `send2smacN` reg is the
egress-port-pick (no separate crossbar reg) — so "reaches no smacN" = egress port
never assigned.

## Source state
All landed fixes are in zx-eth-main.c: flood=CPU-only, isolation port-remap, FDB
aging, broadcast gates, SCH shaper init, + debug tooling (poke/regdump/txtest).
RX works. TX: passes QMG+DSCH, dies at DSCH→SOPC. Device left at the SCH-fix build.
