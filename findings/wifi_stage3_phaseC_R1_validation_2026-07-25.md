# WiFi Stage-3 Phase C — R1 fix VALIDATED + DN offload CLOSED (2026-07-28)

**Verdict: Phase-C DN WiFi HW-offload CLOSED — HW-forwarded at link speed with
flat CPU trap counters.** Validated on HW, builds #534/#535/#536/#537
RAM-booted (final = #537, the committed tree). Two additional bugs were found
and fixed on the way (both HW-root-caused): the PM's TTL-edit leaves a stale
IPv4 header checksum, and a probe methodology confound (fake next-hop DA).

Rig: same as `wifi_stage3_phaseC_offload_spec_2026-07-25.md` §0.1 — lan4 WAN
10.44.66.223 (host server wlo1 10.44.66.133:8080 serving a 300 MB file), wlan1
AP `H3600-AP-Test` 192.168.50.1/24 (hostapd + udhcpd via the new
`scratchpad/wifi_up.py`), Android client via adb (randomized MAC
ba:02:b1:26:83:24, DHCP 192.168.50.10), routed no-NAT, host route
192.168.50.0/24 via 10.44.66.223, nft flowtable `{ lan4 }` + `flow add` on
established TCP.

## 1. R1 fix (87b6f4fb2, consumer starts at probe) — BOTH halves PROVEN

- **Static half:** at fresh boot, with idm0/idm1 NEVER upped,
  `IDM[0x8024] IRQ_MASK = 0x0000000b` (NAPI bits clear; pre-fix boots read
  0x1F all-masked). Reproduced on every boot #534-#537.
- **Dynamic half (the auto-drain):** `fttest install deadb0b0 0a2c4285
  c0a83264 1f90 d00d 28` on the fresh #534 boot (installed clean, pm_slot=8 —
  the stale-flow collision that blocked the 07-27 attempt is gone on a fresh
  boot, as predicted), then 50 hping data packets from the WAN side →
  `idm_rx_count 0→50`, `idm_rx_per_ssid[4] = 50` (exactly the installed essid
  0x1c = idm1/ssid4), `ssid_invalid = 0`, `RX_PENDING = 0x08000000` (0
  pending). The ring drains at probe with no manual `ip link set idm* up`.
  **The R1 black hole is retired.**
- Regress guard added per test-per-fix policy: `regress.py wifi_r1_drain`
  (needs no WiFi hardware) — ran live: **PASS**
  (idm_rx_count_delta=30/30, ssid4_delta=30, irq_mask=0xb).

### Gotcha discovered by the guard work: the hardfast traps TCP SYN by design
A pure-SYN hping burst NEVER rides the HW path — 50 SYNs → `qmg_dn_trap +50`,
`cla_dn_fwd +0`. The same tuple with `-PA -d 200` (PSH+ACK+payload) rides HW
50/50. TCP control packets (SYN/FIN/RST) are deliberately CPU-trapped so
conntrack sees them (standard fastpath design; stock FFE does the same). Any
future synthetic-traffic HW-hit test must send *data* packets.

## 2. NEW BUG FOUND + FIXED: PM TTL-edit leaves a stale IP header checksum

With R1 fixed, the first e2e A/B still delivered ~0 bytes: frames were
HW-forwarded, ring-drained AND dispatched (`cla_dn_fwd` = `idm_rx_count` =
`rx_dispatched` = +25..30, traps flat) but nothing reached the client.

One-shot hexdump of dispatched frames (new debugfs `idm_rx_dump`) gave the
ground truth — frames are clean 802.3, DA = client MAC (PM nh rewrite OK),
no offset quirk (unlike the TM ring's +2), TTL decremented 0x40→0x3f, BUT:

- frame 1 IP csum stored `0xbab1`, correct-for-TTL-0x3f is `0xbbb1`
- frame 2 stored `0xb9e0`, correct is `0xbae0`

i.e. **exactly the checksum of TTL+1** — the PM edit decrements TTL without
updating the IPv4 header checksum, and the client's IP stack silently drops
every frame (`ip_rcv_core` csum check). On the eth DN path the egress
pipeline repairs it in HW; the fabric→IDM shuttle pops the frame out to the
CPU after the PM edit with nothing downstream to repair it.

**Stock comparison (asked by the user, answered from the decomp):** stock
repairs this in HW. `pp_pm_get_flow_info` (decomp_all_tm.c:63626-63633) shows
the PM flow_info entry carries per-flow edit-enable bits — `ip_checksum_en` =
bit4, `tcp_udp_checksum_en` = bit3, `hl_ttl_en` = bit2 — and the PM cmd RAM
has matching `ip_checksum_up`/`tcp_checksum_up` flags (tm.c:19014, 63526-27).
Our installer's flow_info word (`fi=...:00200204`) has bit2 (TTL edit) SET and
bit4 (IP-csum update) CLEAR — we enable the TTL edit but not the checksum
repair. **Fix landed:** repair the IPv4 header checksum in the dispatch path
(`ip_fast_csum`, zx_idm_poll) — the CPU touches every shuttled frame anyway;
TCP/UDP csums are unaffected (TTL not in the pseudo-header), IPv6 has no
header csum. *Stock-parity alternative for later:* set flow_info bit4 at
install and drop the CPU repair — deferred because that word is shared with
the (working) eth path and deserves its own regression pass. Open question
noted: how the eth egress leg gets its checksum repaired with bit4 clear
(per-egress-port enable is the leading theory).

## 3. Dispatch xmit mode: direct ndo_start_xmit WINS (stock parity)

A new debugfs knob `wifi_dispatch_qx` allowed a live A/B of the dispatch API
with the csum fix in place:

| mode | rate (same rig/phone) |
|---|---|
| `dev_queue_xmit` (qx=1) | 1.97-1.98 MB/s (reproduced twice) |
| **direct `ndo_start_xmit` (qx=0, stock parity — DEFAULT)** | **7.65-7.93 MB/s** |

Both deliver correctly; the direct call is ~4x faster. An earlier reading
that mac80211 "silently eats" ndo-direct frames was a probe confound: the
synthetic fttest flow uses a fixed fake next-hop `02:00:00:00:00:01`, which
AP-mode mac80211 legitimately drops at STA lookup (unicast to a
non-associated station). Committed default: qx=0.

## 4. The headline A/B (build #537, committed defaults, 40 s runs)

| run | ftwifi | bytes | rate | HW counters | slow-path |
|---|---|---|---|---|---|
| A-537 | 1 | 314,573,008 | **7.93 MB/s** | qmg_dn_hw = idm_rx_count = rx_dispatched = **+217,277** | qmg_dn_trap **+81** |
| A1/A2 (#536) | 1 | 79.5 / 78.8 MB | 1.98 MB/s (qx=1 then) | +57,515 / +56,974 lockstep | +40 / +44 |
| B-537 | 0 | 12,801,976 | 0.32 MB/s | all IDM/CLA flat 0 | qmg_dn_trap **+11,433** |
| B1/B2 (#536) | 0 | 12.5 / 12.6 MB | 0.31 MB/s | flat | +11,028 / +11,279 |

- **24.6x over the SW baseline**; 7.93 MB/s ≈ the practical TCP ceiling of
  this client's 130 Mbps 11n/20 MHz link — the bottleneck is now the air, not
  the datapath.
- 100% of DN data frames rode HW (qmg_dn_hw == idm_rx_count == rx_dispatched,
  rx_nobind 0); the trap counter carried only handshakes/control.
- `qmg_dn_sw` moving during A-runs is the CPU-injected UP side (client ACKs
  relayed CPU→fabric→WAN), not DN data.
- Installs came through the production nft path (`[phaseC/ft] ... installing
  DN hardfast`, nh = the client's real MAC via zx_ft_resolve_nh). One run on
  #535 hit the known H2 ram6 decline (its own UP entry owned bucket 0x200) —
  correctly stayed in SW; fresh connection reinstalled fine. Counter note:
  `cla_dn_fwd` (0x9238c3cc lo16) wraps at 0xffff mid-run — use `qmg_dn_hw`
  for volume assertions.

## 5. Landed alongside (this commit)

- `scratchpad/wifi_up.py` — one-command idempotent AP bring-up
  (sanity/wan/wifi/conf/daemons/assoc/bind/offload/verify, `--adb`,
  `--offload`), gotchas baked in (udhcpd `-f` logged, associate-before-bind
  EAPOL order, lo-up, printk quiet). Used for the #535/#536/#537 bring-ups.
- `scratchpad/wifi_ab.py` — the throughput/counter A/B harness used here
  (slow-paced reads, console-overrun-safe).
- `regress.py wifi_r1_drain` — the R1 guard (PASS live).
- Driver: probe-time consumer start (87b6f4fb2, prior commit) + this
  commit's csum repair, dispatch-mode knob, one-shot `idm_rx_dump` hexdump.

## 6. Device end state (left SAFE) + next step

- Build #537 RAM-booted; `ftwifi=0` (default); wifi_dispatch_qx=0 (default);
  no synthetic flows tracked (all fttest cookies destroyed rc=0); nft
  flowtable rig installed but inert with ftwifi=0; AP + udhcpd running,
  client associated; idm0/idm1 DOWN (no longer needed — that's the point of
  R1); WAN modem healthy; host: UART bridge :9999/:9998 up, http.server
  stopped.
- **Next step: the UP direction** (WiFi→WAN: client uploads still ride the
  CPU slow path — qmg_up_* stayed 0 all session; wire the UP install for
  wlan-ingress flows), then Phase D (stock-parity HW csum via flow_info bit4,
  descriptor-DMA shuttle improvements if UP/DN CPU load ever matters).
