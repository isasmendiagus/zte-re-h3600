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

---

# SESSION CONTINUATION (same day): the SECOND bug + a hang postmortem

The owner re-connected the client by hand. With the VLAN fix live, the
shuttle counters tracked real client traffic **1:1** (`tx_injected` ==
`tm_rx_fabric` == `tm_rx_dispatched` deltas, e.g. +16/+16/+16) — the fabric
leg is fully fixed. But ping AND a client browser hit to an on-device httpd
(`http://192.168.50.1`, busybox httpd, left running) still failed:
**Tcp InSegs stayed 0** — dispatched frames died between `netif_rx` and IP.

## Bug #2 (FOUND, source-fixed, HW-validation pending): +2 dispatch offset

`skb:kfree_skb` tracing with the real client's traffic:

```
__netif_receive_skb_core: reason UNHANDLED_PROTO protocol=40746 (0x9f2a) ×30
```

**0x9f2a = the last two bytes of the client's MAC** (0e:3e:df:2c:**9f:2a**)
read as the ethertype ⇒ the frame handed to `eth_type_trans` is shifted by
exactly +2: DN-trap fabric frames sit at **bp_buf+18** (the trap path
prepends a 2-byte stub), while the caller's offset heuristic only knows
+0/+16. UP-ring trap frames (B.2's validated ARPs) sit at +16 — which is why
every earlier validation passed. **This also retro-explains B.2's "DHCP
DISCOVER never reached UDP / Udp SNMP all-zero"** — it was this offset, not
udhcpd's death. Note 0x9f2a ≥ 0x0600, so the kernel accepted it as a
(unknown) ethertype — an 802.3-min check can't catch the shift; the fix
matches *known* ethertypes at +12 vs +14 and shifts only when +14 wins.

Source fix: commit `5e2d25a5e` (in `zx_wifi_tm_rx_dispatch`). **UNTESTED ON
HW** — see postmortem.

## Postmortem: I hung the device (honesty)

Chasing byte-level proof of the +18 offset, I batched ~200 `busybox devmem`
reads of the BP pool over the UART REPL — including one ~1100-char
40-command line. The known console gotcha (ttyAMA input overruns — "send
commands ONE per zc() call") bit hard: input corruption produced a mangled
devmem address, the read hit an unclocked/secure region and the AXI access
never completed → **CPU hard-hang** (console dead mid-stream, zero tty echo,
no SIGINT; mt7915 keeps beaconing autonomously so the SSID is still visible —
misleading). The offset analysis did NOT need that dump — the 0x9f2a
arithmetic was already conclusive.

- Recovery requires a DTR power-cycle (boots STOCK from NAND; mainline was
  RAM-boot) + TFTP re-boot of mainline — out of scope per this session's
  no-reboot directive. STOPPED here and reported.
- ⚠ LESSON (repeat of a documented gotcha, now with a much higher price):
  NEVER send long/many-command lines to the UART REPL; one short command per
  zc() call; and NEVER script devmem loops over the console — if a byte-dump
  is truly needed, add a driver debugfs hexdump knob instead.

## State for the NEXT session (checklist)

1. Device is HUNG; power-cycle via bridge :9998 DTR (≥5-10 s OFF — also
   resets the WAN modem), boots stock, then TFTP RAM-boot mainline.
2. Rebuild first: both fixes are in source (`b5a4e5d8b` PP_BRG[0x008]=0 at
   init + `5e2d25a5e` dispatch offset). No live pokes needed after that.
3. Re-run this session's validation ladder on the new build:
   synthetic UDP out idm1 → `pp_drop` frozen, `tm_rx_fabric/dispatched` tick,
   and now also `Udp/Tcp InSegs` move (offset fixed).
4. With the client: static ARP `192.168.50.100 → 0e:3e:df:2c:9f:2a` on wlan1,
   then ping + `http://192.168.50.1` (busybox httpd, `/tmp/www`). The client
   does NOT answer broadcast who-has (Android doze) and did not answer ICMP
   echo in this session's windows — treat HTTP as the primary proof.
5. Then Phase-B step 4 (client→LAN via route/NAT — bridge conflicts with the
   bound rx_handler) and the port1/jack2 drop_PP retest with the VLAN fix.

## Verdict

**Phase B slow-path: NOT yet closed OTA, but for the first time FULLY
root-caused end-to-end.** Two independent bugs stacked on the client→AP
unicast path: (1) PP outport-VLAN-check vs empty VLAN tables (fixed live,
validated with real client traffic at the fabric level, in source); (2) +2
frame offset on DN-trap dispatch (found via real client traffic, fixed in
source, validation needs the next boot). Everything else — assoc/WPA2 with
bound vif, OTA injection, fabric return, dispatch — verified working with a
REAL client this session.

## Next steps

1. Next boot (new build with both fixes): validation checklist above →
   expect ping + HTTP to the AP to work → Phase B CLOSED.
2. Then client→LAN forwarding (step 4) and Phase C (CLA WiFi flows,
   HW-forward egress → IDM RX ring) per roadmap.
3. Consider CLA catch-all trap rules for inports 6/7 (stock-parity slow
   path) as Phase-C groundwork.

## ✅ CLOSE-OUT 2026-07-25 — Phase B CLOSED end-to-end OTA with a real client

On the rebuilt-and-rebooted build, the user's real phone associated to
`H3600-AP-Test`, and **`http://192.168.50.1` LOADED from the phone** (user-
confirmed live) — the full slow-path shuttle works end-to-end:
`phone ⇄ air ⇄ AP(wlan1) ⇄ IDM ring ⇄ fabric ⇄ trap(fix A) ⇄ TM q4 ⇄ dispatch ⇄ IP stack`.

Two more things had to land on top of bugs #1/#2 above (this is what made the
page load, committed here):

- **The REAL PP_BRG unicast fix was a LAST-WRITER-WINS clobber**, not the
  earlier `zx_pp_init` write. Commit b5a4e5d8b cleared the VLAN-check in
  `zx_pp_init`, but `zx_pp_brg_init` runs LATER in probe and its stock-replay
  line re-wrote `0x92388008 = 0x0000ff00`, silently reverting it (same trap as
  the RED_CFG bit6 churn story — a stock-replay line undoing a fix). Confirmed
  on the #527 boot: the reg read back `0x0000ff00` despite b5a4e5d8b compiled
  in. Fixed by writing `0x00000000` at the `zx_pp_brg_init` site too.
- **The DN-trap dispatch offset is not a fixed +2** — fabric trap frames reach
  the CPU in several layouts (UP-ring eth@+16, DN-trap eth@+18, and DN
  bridge-FORWARD-to-CPU as a BARE IPv4/IPv6 packet at +16 with no eth header).
  Replaced the blind +2 heuristic (5e2d25a5e) with CONTENT-based detection:
  probe 4 offsets for a known ethertype, else accept bare L3 at +16 and deliver
  tun-style; derive length from the L3 header, not the ambiguous desc len. New
  `tm_wifi_rx_noparse` counter for anything still unrecognized.

**Verdict: Phase B (WiFi slow-path, SW forwarding) is CLOSED and validated on
hardware with a real client.** Next stage = Phase C (CLA hardfast WiFi flows,
`gemport_uni_id = 0x10|(ring<<3)|ssid`, HW-forward egress to ports 6/7 → the
IDM RX ring) — the actual offload/fast-path.

(Committed post-hoc by the coordinator after the session agent was
accidentally cancelled mid-write; the driver changes were reviewed against the
running #529 build that served the page.)
