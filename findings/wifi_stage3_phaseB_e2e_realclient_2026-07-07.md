# WiFi Stage-3 Phase B — real-client end-to-end session: THE unicast gap found + fixed live (2026-07-25)

Device agent session on the LIVE running kernel **#524** (no reboot/rebuild, per
brief). Real STA `0e:3e:df:2c:9f:2a` (owner's second device, static IP
`192.168.50.100`) associated to `H3600-AP-Test` (wlan1 bound to (idm1, ssid4) =
node 12) at session start and stayed for most of the session (it deauthed and
re-joined once mid-session, and left for good near the end — dozing Android).

## Headline

**Phase B's slow path was NOT closed by B.2 — B.2 only ever validated
trap-class frames (ARP/DHCP-broadcast/icmpv6). ALL plain unicast IP traffic
from a WLAN client (ICMP echo replies, TCP, UDP) reinjected into the fabric
was PP-DROPPED 1:1.** Root cause found and fixed LIVE via poke:

> **`PP_BRG 0x92388008` — power-on default `0x0000ff00` = `outport_vl_chk_en
> [15:8] = 0xff` (outport VLAN check enabled on every egress port) with
> mainline's VLAN tables EMPTY → every bridge-FORWARD verdict fails the
> egress VLAN check → `drop_PP` (0x921da040) +1 per frame.**
> Stock writes `0x0000dfdf` at config time (checks on, tables populated);
> mainline never touches the register, so the reset default stood.
> **Live fix: `poke 0x92388008 = 0x00000000`** (all VLAN checks off — the
> semantically correct value for mainline's VLAN-less trap-all bridge).
> Source fix (1 line, next build): write 0 in `zx_pp_brg_init`.

After the poke, the identical synthetic frames that pp_dropped **deliver
end-to-end: fabric → TM trap → `zx_wifi_tm_rx_dispatch` → bound-vif stack**
(`tm_rx_fabric`/`tm_rx_dispatched` +N, `pp_drop` frozen — re-verified twice,
including at the canonical (1,4) bind).

## What was proven live with the REAL client (before it left)

| Leg | Result |
|---|---|
| WPA2 assoc to the BOUND vif | OK (station AUTHORIZED, connected ~1-2 h across the session) |
| Client OTA frames → wlan1 rx_handler → ring injection | **WORKS** — `tx_injected` tracked real client traffic all session (idle drips + a ~100-frame screen-on burst + 33/34-frame elicited bursts) |
| Trap-class client frames (bcast/mcast/ARP/DHCP) → dispatch | WORKS (the B.2 result, re-observed: dispatched moved with client traffic at node 12 = raw 0x1c) |
| **Unicast client frames (echo replies, TCP, DNS)** | **ALL pp_dropped 1:1 pre-fix** (+33 pp_drop / +33 injected, twice; SPA desIn latch = `(inport7, act=0 FORWARD, rsn 0x49)`) |
| AP→client unicast TX (mac80211, not fabric) | OK at radio level — station `tx packets` +8 for 8 pings, `tx failed` 0 (client radio ACKed) |
| Client answers pings | YES (its echo replies were the elicited injected frames) — the ping FAILED only because the replies died at PP |

The client deauthed before the fix could be OTA-confirmed (and my two post-fix
ping attempts were INVALID — see honesty section). **The final OTA
confirmation (ping 192.168.50.100 succeeding) still needs the client to
re-join.** Everything else about the path is now verified.

## The bisect (all live, no rebuild)

Eliminated one variable at a time; each step = counter-delta experiment with
synthetic frames from the device via idm1 (inport 7), DA = wlan1's MAC:

1. **ssid**: NOT the trigger — rebound wlan1 to (1, ssid0); client frames still
   pp_dropped 1:1 (+33/+34).
2. **SA**: NOT the trigger — set idm1's MAC = client MAC; probe still delivered.
3. **FDB state**: NOT the trigger — client MAC and wlan1 MAC absent from BOTH
   FDB tables (FDB-A PP_BRG_RAM + FDB-B sbrag, both hash variants, all slots
   zero). Installing wlan1's MAC → CPU (regport0) in both tables (fdbadd +
   manual indirect writes, readback-verified) did NOT stop the drop → the PP
   decision here isn't DA-known gated.
4. **IP content**: NOT the trigger — exact replica (SA=client MAC,
   src=192.168.50.100, dst=192.168.50.1, DA=wlan1 MAC, ICMPv4) delivered.
5. **L4 class WAS the discriminator**: every delivering probe was
   protocol-trapped (ICMP echo request / ARP / icmpv6 → act=1); plain **UDP
   pp_dropped +5/5** with desIn `(7,0,0,0x49)` — *same signature as the
   client*. So: **ring-ingress FORWARD-class (act=0, rsn 0x49) = dead;
   trap-class = fine.** (Wire-port FORWARD-class survives via the CLA
   per-inport catch-all trap rules — `zx_cla_table.h` has 8 rules per wire
   inport 1..5 and NONE for ring inports 6/7, so ring FORWARD frames fall
   through to the plain bridge path.)
6. **Full ladder** (SPA verdicts / SADM / DPA / ACL / CLA UP+DN banks / PM /
   ADM / QMG): for the dying frames ONLY `pp_drop` ticks — no ACL/CLA
   involvement → death inside PP's bridge decision.
7. **Isolation table** 0x923883c0..dc: live == stock ({fe fd fb f7 ef df ff
   ff}) → exonerated.
8. **regdump-vs-stock diff** (PP_BRG block, live vs
   `tasks/00.10.02.re-stock-kmods/findings/regs/stock_eth_2mib.txt`):
   shortlist of ONE plausible config diff → `0x92388008` stock `0xdfdf` vs
   live `0xff00` → poked 0 → **fixed** (UDP probe: pp_drop +0,
   fabric/dispatched +N, twice).

## Post-fix validated state (synthetic, canonical bind (1,4))

- 5 UDP FORWARD-class frames via idm1: `tm_rx_fabric +10 (5 + bg),
  tm_rx_nobind +10` (expected — device frames are ssid0 = node 8 = unbound),
  `pp_drop +0` (frozen at 0x428 through the final windows).
- Earlier same-poke validation at bind (1,0): `tm_rx_dispatched +6` — the
  frames enter the BOUND vif's stack (the complete B.2 shuttle, now for
  FORWARD-class too).
- dmesg: zero WARN/BUG through all of it. Wire datapath: untouched counters
  keep ticking; the poke only REMOVES a filter (cannot drop more).

## Live-state notes (this boot)

- The `0x92388008 = 0` poke is LIVE-ONLY — **a reboot reverts it**. Driver
  patch needed in `zx_pp_brg_init` (zx-eth-main.c; the driver never writes
  this register today — grep `0x8008` finds only unrelated IDM/TM offsets).
- Benign residue left in place (documented, harmless): wlan1's MAC → CPU-port
  FDB entries (FDB-A bucket 0x9f slot0 D2 readback quirk: top nibble stored
  as status; sbrag buckets 0x9f/0x74/0x2ec); PERMANENT ARP
  `192.168.50.100 → 0e:3e:df:2c:9f:2a` on wlan1 (deliberate — instant ping
  when the client re-joins; the dozing client ignores broadcast who-has).
- Housekeeping done: prior agent's leftover `nc localhost 9999` monitor
  killed; duplicate daemonized udhcpd killed (foreground `udhcpd -f` kept,
  pid 211); idm1 restored (own MAC `02:72:5f:c1:c1:01`, only 10.66.66.1/24);
  wifi_bind restored to node 12 = (idm1, ssid4) → wlan1.

## Honesty / invalid-test confession

- My two post-fix "ping the client" tests were **invalid**: a leftover
  `192.168.50.100/32` address on idm1 (from the replica experiment) made the
  target a LOCAL address. By the time I found and removed it, the client had
  deauthed (station dump empty — authoritative). So the fix is proven for the
  exact frame class that killed the client's pings, but the literal OTA ping
  success was not yet observed.
- The client's presence was intermittent (Android doze): it answered pings
  and UDP-to-closed-port probes when awake (33-frame bursts), and slept
  otherwise. All "client didn't respond" windows were cross-checked against
  `tx_injected` before drawing conclusions.
- Step 4 of the brief (bridge wlan1↔LAN for client→LAN forwarding) was NOT
  attempted: gated on the unicast fix (found late in the window) and on a
  present client. With FORWARD-class delivery fixed, this is the immediate
  next test.

## Relation to the OPEN port1/jack2 anomaly

Same drop counter (`drop_PP`), same "everything upstream passes" shape. The
port1 case drops trap-class too, so it is NOT automatically explained by the
VLAN-check default — but the June port1 comparison predates this register's
identification (0x92388008 was never in the port1 diff shortlists, and stock
vs mainline DIFFERS on it). **Re-test port1 ingress with `0x92388008 = 0`**
next time jack2 is cabled — cheap and plausibly the same class of omission.

## Next steps

1. **OTA close**: client re-joins → `ping 192.168.50.100` (static ARP already
   staged) → expect success; then client→LAN via SW bridge/route+NAT
   (Phase-B step 4) → Phase B fully CLOSED.
2. **Driver patch** (next build): `zx_pp_brg_init` writes
   `PP_BRG[0x8008] = 0` + comment; consider CLA catch-all trap rules for
   inports 6/7 (stock-parity slow path) as Phase-C groundwork.
3. Phase C (CLA WiFi flows, HW-forward egress → IDM RX ring) per roadmap.
