# Intermittent host↔device eth forwarding — FOUR stacked root causes (2026-08-02)

**Status: root causes identified + fixed; on-device validation in progress.**
Symptom as reported: with `lan2` = 172.31.9.1/24 and a device httpd, host
`curl http://172.31.9.1:8090/tf` sometimes 200 (~7.5 MB/s), sometimes rc=28
(timeout); device→host ping intermittently 100% loss — even on a fresh boot
with MAC[2] inited.

The "intermittency" decomposed into four INDEPENDENT defects, each proven live:

## 1. Duplicate-route black-hole (the reported L2 flakiness) — CONFIG/USERLAND
- `rc.router` hardcoded `LAN=lan1` and put 172.31.9.1/24 on lan1 at every boot.
  Tests put the same subnet on the boot-linked port (lan2). All lanN are DSA
  fixed-link (carrier ALWAYS up), so BOTH `172.31.9.0/24` routes stay in the
  FIB; first-inserted wins → every reply/device-originated packet routed out
  the dead lan1 (PHY unplugged, MAC never inited).
- PROOF (live, deterministic): `ip -4 neigh` showed
  `172.31.9.50 dev lan1 probes 6 FAILED` while the host sat on lan2.
  With lan1 holding the IP: curl 0/6. `ip addr flush dev lan1`: 10/10.
  Re-added lan1 IP (now inserted AFTER lan2's route): still 10/10 → pure FIB
  insertion-order. The "sometimes works" across sessions = whether some tool
  (devtool `wan` flushes lan1; `eth-download` didn't) had run first.
- FIX: `rc.router` now auto-detects the boot-linked port from dmesg
  (`PHY[[0-3]] link UP` → lanN, 15 s wait loop, fallback lan1) and binds
  LAN IP + DHCP + FORWARD rules to it. `devtool.py eth-download` now flushes
  ALL lanN before configuring the detected port.
- VALIDATED: two consecutive fresh boots logged `rc.router: LAN=lan2
  (boot-linked)`; hammer 30/30 http=200 + device→host ping 5/5 on each.

## 2. Global timer 20.8× too fast — EVERY kernel timer broken — DT BUG
- `zx279128s.dtsi` clocked `arm,cortex-a9-global-timer` from `osc24m` (24 MHz).
  The A9 MPCore global timer counts **PERIPHCLK** = CPUCLK/2 = 500 MHz.
- MEASURED: `echo M > /dev/kmsg` markers 60 real s apart → kernel delta
  1297.5 s (ratio 20.1–21.6; 500/24 = 20.83 exactly, kernel uses clk/2 = 12 MHz
  with GT prescaler 2, HW counts 500/2 = 250 MHz).
- Consequences (all timers 20.8× fast in REAL terms): TCP RTO min 200 ms → 9.6 ms
  real (spurious retransmit storms on WAN RTTs); `ping -W 3` waits 144 ms real
  (→ the flaky "NO internet via WAN" / device-ping 100%-loss readings);
  nf_flow_table flow timeout 30 s → 1.4 s real and GC period 10 s → 0.5 s real
  (→ HW-offloaded flows torn down ~1 s after install); conntrack SYN timeouts
  ~3 s real; all `sleep`s short. Historic device-side ms figures in findings
  are 20.8× overstated; host-side throughput numbers are unaffected.
- FIX: new `periphclk` fixed-clock 500 MHz in the dtsi; global_timer now
  `clocks = <&periphclk>`.

## 3. devtool build shipped STALE driver modules — TOOLING REGRESSION (ours)
- `scratchpad/devtool.py build` staged "fresh" .kos via
  `find $REPO/build -name '*.ko' ...`, but `$REPO/build` became a SYMLINK
  (scratchpad consolidation, commit be2f6b3c1). `find` default `-P` does not
  descend a symlink argument → ZERO modules copied → the image silently shipped
  the tracked initramfs base's stale .kos. PROOF: after a 16:45 build,
  `/tmp/initramfs_extract/lib/modules/zx279128-eth.ko` was dated 12:08 and
  lacked a string present in `build/.../zx279128-eth.ko` (16:45). Both boots
  that day ran a 12:08 eth driver under a 16:45 kernel (CONFIG_ZX279128_ETH=m).
- FIX: devtool build now uses `os.path.realpath(BUILD)` for the find, counts
  the copied .kos and ABORTS if <5 (regression guard).

## 4. HW flow-offload black-holes dual-NAT flows — DRIVER BUG
- Repro: DNAT (phantom IP) + MASQUERADE on the same flow (any "hairpin"-style
  double NAT). nf_flow_table emits, for one direction, BOTH a saddr and a daddr
  IPv4 mangle. `zx_ft_flower_replace` stored both into the single
  `zx_ft_nat.new_ip` (second overwrites first) and set `snat && dnat` together;
  `zx_ft_install_recipe` programs ONE rewrite address (next_hop ram: stock
  `pp_pm_set_next_hop_ram_info` = next_mac + ONE next_dip; flow_info has no
  second address field) with BOTH `sip_en|dip_en` enables.
- PROOF (tcpdump on the client leg): HW-forwarded frames arrived as
  `IP 0.0.0.0.8000 > 10.99.99.99.52967` — dst got the value that belonged in
  src, src got an unprogrammed slot (0.0.0.0) → client drops everything →
  http=000 while the SW slow-path (flowtable removed) instantly does 200 at
  ~0.8 MB/s. Single-NAT flows (plain masquerade, the 2026-07-04 validated
  cases) are unaffected.
- FIX: `zx-eth-main.c` `zx_ft_flower_replace` now declines (-EOPNOTSUPP) any
  direction carrying BOTH saddr+daddr mangles → dual-NAT flows stay on the SW
  flowtable fast-path (correct, just not HW). dev_info logs the decline.
- NOTE: fix was built at 16:45 but did NOT reach the device until defect #3
  was found/fixed — the `nat=SD` recipe seen installing at dmesg[7586] came
  from the stale 12:08 module.

## Measurement rig for line-rate (single-NAT, client==server host)
The obvious LAN-local speed test (host eth1 as client behind the device, host
eth0:8000 as server on the WAN /24) short-circuits via loopback (dst is a local
address). netns is unusable in this container. Working rig with the device flow
kept SINGLE-NAT (HW-offloadable):
- host: `iptables -t nat -A POSTROUTING -o eth1 -d 10.99.99.99 -j SNAT
  --to-source 172.31.9.77` (phantom client), `ip route replace 172.31.9.77/32
  via 10.44.66.223 dev eth0` (reply leg through the device),
  `ip route replace 10.99.99.99/32 via 172.31.9.1 dev eth1`.
- device: `iptables -t nat -A PREROUTING -i lan2 -d 10.99.99.99 -j DNAT
  --to-destination 10.44.66.30`; EXEMPT the phantom from masquerade
  (`-I POSTROUTING -o lan4 -s 172.31.9.77 -j ACCEPT`); static ARP for the
  phantom (`busybox arp -s 172.31.9.77 <host-eth1-mac>` — busybox `ip neigh
  add/replace` is NOT supported on this image, it fails "invalid argument").
- Device flow = DNAT-only: UP rewrites dst only, DN rewrites src only.
Slow-path validated at ~0.79 MB/s end-to-end. Offloaded run pre-clock-fix got
0 bytes — retest pending with the clock + fresh-module fixes (suspect the 1.4 s
real flowtable GC teardown and/or stale module were the killers).

## Post-fix validation (fresh boot, image w/ clock + staging + dual-NAT fixes)
- Clock: `sched_clock: 64 bits at 250MHz`; kmsg markers 22.34 kernel-s over ~22
  real s → 1:1. Device→host LAN RTT 1.19 ms (was "24 ms" = ~1.15 ms real under
  the 20.8× clock — consistent).
- `devtool.py eth-hammer --n 30`: **30/30 http=200** + device→host ping 0 %
  (fresh boot, rc.router auto-detected lan2 — 3rd consecutive boot).
- SW forward path: **10.5–11.7 MB/s** (~90 Mbps) vs 0.8 MB/s before the clock
  fix (13×) — the broken clock was crippling CPU forwarding (TCP timers).
- dual-NAT decline fix VALIDATED: device-DNAT+masquerade flow logs
  "dual-NAT … declining offload (stays SW)" and transfers 11.7 MB/s via the SW
  fast-path (before: black-hole, 0 bytes, mangled src=0.0.0.0 frames on wire).
- HW offload rig (devtool.py eth-offload, host-side phantom DNAT so the DEVICE
  flow is plain masquerade): flow enters HW — **qmg_dn_hw +719k over a 1 GiB
  transfer, http=200**. Gotcha found on the way: a stale device PREROUTING DNAT
  makes the flow dual-NAT → silently declines to SW (eth-offload now flushes
  the nat chains first).

## OPEN: HW-offloaded throughput capped at ~11.6 MB/s (≈93 Mbps) by UP ACK trap
- During the offloaded 1 GiB download: QMG DN hw_fwd +148k (data HW-forwards)
  but **UP hw_fwd = 0** and UP hw_trap climbs 1:1 with DN sw_fwd (+76k = the
  client ACKs) → every ACK traps to the CPU and is SW-forwarded (~4.2k pps).
  TCP is ACK-clocked → data rate slaved to the CPU ACK path ≈ 93 Mbps.
- CLA counters during a run: cla_tx_fwd (0x9238c3c0) delta **0** — the UP
  entry NEVER forward-verdicts; cla_tx_trp climbs. DN poly-0 hits fine.
- Both wire legs proven faster: lan4↔host-eth0 105 Mbps (device-terminated
  wget), lan2→eth1 128 Mbps (device-served curl). Two parallel offloaded flows
  aggregate the SAME 11.7 MB/s → shared cap, not per-flow TCP.
- July-validated known-good: 1d6cd11e3 "UP-direction HW-offload — 10.4 GB
  sustained bidirectional" (qmg_up_trap stayed 0, ~830-920 Mbps). The
  zx_ft_pack_cla / zx_ft_build_key bytes for ETH flows are IDENTICAL between
  1d6cd11e3 and HEAD (key_hdr refactor is a no-op for ETH: 0x48 → same
  cla[4]=0x00100069, same kb[3]) — the regression is NOT in the entry packing.
- Suspect window: 1d6cd11e3..HEAD collateral from wifi work (CLA ram7 dual-bank
  replay + q5→q4 re-steer 8d37fa739, PP_BRG VLAN-check clear 1c0985a0d,
  cpu_chk_en f1603ddff, wedge-#2 BMU restructure 4117a14c3/fa51b3af9, NPP
  clock-gate mask 0xFFFFF→0xFFFFFFFF). Bisect build of 1d6cd11e3 in progress
  (worktree /home/dev/kg1d) to confirm UP offload works there on the same rig.

## Git archaeology (v0.0.1 = DeepSeek handoff, 2026-07-31)
- The global-timer/osc24m clock bug PREDATES v0.0.1 — introduced with the
  original DT (f477756c8, Claude era). The 20.8× clock was there for EVERY
  historic measurement; host-side numbers (curl MB/s) remain valid, device-side
  ms/timer numbers are 20.8× overstated.
- DeepSeek era (v0.0.1..main, 28 commits) did NOT touch the DTS or defconfig.
  Driver changes: wedge-#2 BMU restructure, ftwifi default ON + auto-bind,
  cpu_chk_en, checkpatch churn, BPDUMP strip.
- The devtool module-staging bug (find on the `build` symlink) came from the
  scratchpad consolidation commit be2f6b3c1 (2026-08-02).

## WiFi phase note
- `rig.py wifi up` on the 17:04 image wedged the device console (NUL flood on
  UART, REPL dead) right after the module chain + hostapd start — needed a DTR
  reboot. To watch: may be the documented mt7915/PCIe bring-up wedge; retry.

## WiFi forwarded path (2026-08-02, clock-fixed HEAD image)
- AP + phone assoc reproducible via `rig.py wifi up` / `wifi assoc` (one console
  wedge on the first `wifi up` of the day — NUL flood on UART, DTR reboot
  recovered; did not recur).
- Slow-path FORWARDED WiFi (phone 192.168.50.10 → wlan1 → CPU route+NAT → lan4
  → host eth0): **9.2 MB/s (~74 Mbps)** — vs the historic "SW" figures measured
  under the 20.8× clock. Needs only FORWARD ACCEPT + masquerade (rc.router
  policy DROP otherwise).
- OFFLOADED (nft flowtable {lan2,lan4} + ftwifi=1, auto-bound wlan1): DN wifi
  hardfast installs ("egress wlan1 -> wifi essid 0x11 (idm0 ssid1)") and the
  transfer STALLS after ~14 KB (dn_hw +59 then dead) — the HW-forwarded
  fabric→essid frames never reach the phone. Reproducible on a clean boot
  (devtool.py wifi-offload). Rebinding wlan1 to the Phase-C-validated idm0/ssid0
  (del 0 0; del 0 1; wlan1 0 0) made the NEXT flow fail entirely (0 bytes) —
  stale hardfast state compounds; needs a clean-boot A/B per bind.
- ALSO: stale tracked flows survive `nft flush ruleset` (driver flow tracking
  not fully torn down) and then block NEW installs via "reserve decline:
  higher-way collision (ram6 addr=0x202)" — ram6 has only 8 slots (raw&7), so
  stale entries collide quickly. Driver bug to fix: untrack on flowtable free.
- Suspect for the DN wifi black-hole: productionized AUTO-BIND assigns
  wlan0→idm0/ssid0, wlan1→idm0/ssid1, while Phase-C DN delivery (7.93 MB/s)
  was validated with the AP vif bound to idm0/ssid0 (`wlan1 0 0` in the
  wifi_bind doc). essid 0x11 (ssid1) fabric delivery may be unconfigured.
  UNCONFIRMED — needs clean-boot test with wlan1 forced to 0/0 before traffic.

## 5th defect CAUGHT LIVE: intermittent WAN(lan4) death = RED bit6 revert → 1024 wedge
- Fresh clean boot (HEAD image, ~1-in-3 boots): lan4 completely dead — host
  ARP for 10.44.66.223 unanswered, device→WAN ping 100 % loss — while
  `smac4 RX_pkts` climbs (frames reach MAC4) and dmesg shows a SUCCESSFUL
  PHY[4] bring-up (SOPC bridge ENABLED ready, MAC4 ctrl=0xba6003).
- Signature: `QMG DN hw_trap` frozen at **exactly 1024** = the known WAN-RX
  one-wrap wedge (#1). Live peek: `TM_RED_CFG (0x92344004) = 0xDE` — **bit6
  (cpuDn charge-accounting) SET**, although BOTH probe-time writers clear it
  (zx_tm_red_init and the stock-replay line both write 0x9E). Something
  post-probe intermittently resets/rewrites the RED block back to its 0xDE
  reset value → idle WAN chatter charges the out-buffer to 1024 → latch.
- Clearing bit6 after the latch does NOT recover (verified live: poke 0x9E,
  still 100 % loss, hw_trap stays 1024) — reboot-only, as documented in
  fix_churn_red_dnbank_2026-07-04.md.
- This closes the loop on the ORIGINAL "intermittent even on fresh boot"
  report for the WAN leg (the LAN leg was defect #1, the routes).
- FIX (mitigation + tracer): zx_mac_keepalive_fn now re-asserts bit6=0 every
  100 ms and logs ratelimited "[red-arm] RED_CFG reverted to 0xde" when it
  catches a revert — bounds the charge to a few frames (vs 1024 latch) and
  timestamps the culprit writer for a future proper fix.

## Known-good bisect status (eth UP ACK offload)
- 1d6cd11e3 (July 4, "760 Mbps") booted on the current rig: UNUSABLE as A/B —
  it predates the RED bit6 fix (92bcbd0ce), so its SW path wedges at 1024
  frames (baseline 0.13 MB/s then total death) and no FLOW_CLS fires at all
  in this rig. v0.0.1 (2026-07-31, STATE.md claims eth bidirectional OK)
  built in worktree /home/dev/kg1d (+ the periphclk DT fix) — boot pending.

## WiFi DN offload stall — ssid-bind hypothesis REFUTED, checksum knob REFUTED
- Clean boot, wlan1 force-bound to idm0/ssid0 BEFORE any traffic (`del 0 0`,
  `del 0 1`, `wlan1 0 0`): identical stall — 14480 bytes then dead, dn_hw +57.
  So ssid0-vs-ssid1 (auto-bind ordering) is NOT the cause.
- wifi_bind counters DO show the DN hardfast frames being dispatched to the
  vif (`rx_dispatched` +39) → frames traverse fabric→IDM→driver→mac80211;
  they die between mac80211 and the phone TCP (mangled/checksum suspicion).
- Live A/B of the DeepSeek-era cpu_chk_en (0x92388008 bit16, f1603ddff):
  cleared → STILL stalls (14480B). Restored to 1. Not a one-knob fix; the
  frame-content leg needs a phone-side (or monitor-mode) capture next.
- The 14480 bytes that DO arrive = the slow-path packets before the hardfast
  install; the stall begins exactly when dn_hw starts counting.

## Stale flow tracking survives `nft flush ruleset` — DRIVER BUG (open)
After several offloaded eth flows + nft flush, a NEW (wifi) flow install hit
"[phase6/ft] reserve decline: higher-way collision (ram6 addr=0x202) ...
vs tracked raw=0x8c0a" — a tracked entry from a long-destroyed ruleset still
owned the bucket. ram6 has only 8 slots (raw&7) so stale entries collide fast.
Fix direction: untrack/uninstall on FLOW_BLOCK_UNBIND / flowtable free, not
only on per-flow DESTROY.

## eth UP-ACK offload bisect — state
- HEAD: UP recipes install (nat=S, eg_rp=5, `direct`+`da_known` set — bytes
  PROVEN identical to the July-validated packing), ftup=1, but UP CLA never
  forward-verdicts: cla_tx_fwd stays 0, every ACK traps (up_trap == DN ACK
  count), CPU forwards them at ~4.2k pps → offloaded download is ACK-clocked
  at ≈93 Mbps.
- 1d6cd11e3 (July 4 "known-good") on-device: INVALID A/B — predates the RED
  bit6 fix; its lan4 trap path wedges at 1024 frames (baseline 0.13 MB/s,
  then dead), and no FLOW_CLS fires.
- v0.0.1 (2026-07-31 handoff) first boot: INVALID A/B — that era's
  defconfig/fragment has NO nf_tables (nft: "cache initialization failed");
  the nft config options were added to the DEFCONFIG during the DeepSeek era.
  Rebuild with NF_TABLES/NFT_* forced in is in progress (worktree
  /home/dev/kg1d, build5.log) — boot + `devtool.py eth-offload` there answers
  whether UP ACK HW-forwarding ever worked on the current LAN-local rig.
- If v0.0.1 forwards UP: culprit ∈ the 28 DeepSeek commits (prime suspects:
  4117a14c3 BMU pool priming, f1603ddff cpu_chk_en, 59f8433e8 idm up at boot,
  23032088d ftwifi ON + auto-bind, NPP clock-gate mask 0xFFFFF→0xFFFFFFFF).
  If not: suspects move earlier (8d37fa739 CLA ram7 dual-bank replay + q5→q4
  re-steer, 1c0985a0d PP_BRG VLAN-check clear, wedge-#2 groundwork) OR the
  July UP validation environment (internet RTT, netns client) differed in a
  way that matters.

## Reproducible regression guards (codified per the working principle)
All in `scratchpad/devtool.py`, each self-contained from a fresh `rig.py boot`:
- `devtool.py eth-hammer --n 30` — L2 stability: 30 host→device fetches +
  device→host ping; guards defect #1. PASS = 30/30 + 0% loss.
- `devtool.py eth-offload --mb 1024` — full offload rig (host eth0 server,
  phantom-server DNAT on the HOST, masquerade-only device flow, flowtable
  {lanN,lan4}); reports slow-path vs offloaded MB/s + qmg_dn_hw delta +
  dual-NAT SW-fallback check. Currently expected: ~11.5 MB/s both (UP-ACK cap),
  hw_fwd ≈ +719k, fallback OK. Guards defects #2/#4/#5 and the offload path.
- `devtool.py wifi-offload --mb 1024` — AP up + phone assoc + forwarded
  download slow vs offloaded + QMG deltas. Currently expected: slow ~9-10 MB/s,
  offloaded FAIL (DN stall) until the wifi DN bug is fixed.
- `devtool.py eth-download` — internet-path forwarding sanity (uplink-capped).
- devtool `build` now fails loudly if <5 fresh modules stage (guards defect #3).

## What should be committed (pending review)
- linux-v6.6/arch/arm/boot/dts/zte/zx279128s.dtsi — periphclk 500 MHz +
  global_timer reclock (defect #2; validated 1:1 clock, 13× faster SW forward).
- linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c — (a) dual-NAT decline in
  zx_ft_flower_replace (defect #4, validated); (b) red-arm keepalive re-assert
  + revert logging in zx_mac_keepalive_fn (defect #5 mitigation+tracer).
- tasks/00.01.eth-driver/configs/rc.router — boot-linked LAN auto-detect
  (defect #1, validated on 5+ consecutive boots) + udhcpd conf templating.
- tasks/00.01.eth-driver/configs/udhcpd.conf — DHCP range off the host's
  static .50.
- scratchpad/devtool.py — staging realpath+guard (defect #3), eth-hammer,
  eth-offload, wifi-offload subcommands, eth-download LAN flush.
- NOT to commit: /home/dev/kg1d worktree (bisect scratch; remove with
  `git worktree remove --force /home/dev/kg1d` when done).

## v0.0.1 A/B RESULT (2026-08-02, kg worktree + nft config forced + periphclk fix)
- v0.0.1 kernel/module on the SAME rig, same eth-offload run: recipes DO
  install, but **qmg_dn_hw +0** — even the DN direction HW-forwards NOTHING
  (HEAD DN-forwards ~718k frames on the identical rig). Baseline SW is also
  4-8× slower (1.5 MB/s — v0.0.1 still has the per-packet BPDUMP hexdump,
  stripped later in 39c6e7a05).
- CONCLUSION: the DeepSeek era did NOT regress the eth offload — HEAD is
  strictly better than v0.0.1 on this rig (DN went 0 → 718k hw_fwd). The
  UP-ACK CLA miss exists on BOTH, so it predates v0.0.1. Suspect window moves
  to the late-July (pre-v0.0.1) WiFi Stage-3 CLA work (8d37fa739 ram7
  dual-bank replay + q5→q4 re-steer, 1c0985a0d PP_BRG VLAN-check clear,
   f130d36c8/fa51b3af9 wedge-#2 groundwork) — OR the July 830-920 Mbps UP
  validation environment (internet-RTT flow via netns client) differed in a
  way the LAN-local rig exposes (e.g. pure-ACK ptype classification: TCPTRAP
  instrumentation shows pure-ACKs landing trap-queue q=3 while data rides
  q=7 — if the CLA extract rule for the ACK ptype differs from rule 0x90,
  the stored UP entry can never match; check zx_def_ptl_pkt_map's ptype for
  TCP-control vs the ram7 replay).
- MOST-PROMISING NEXT STEP (eth UP): capture ONE trapped pure-ACK's CLA
  descriptor (desIn latch 0x9238c3e0/e8/ec + action_rsn) during an offloaded
  download to read WHICH ex_rule_id/reason the ACKs classify under; if
  action_rsn = LOOK_UP_MISS with ex_rule != 0x90, the fix is to install the
  UP entry under the ACK ptype's extract rule (or re-steer the ptype).
- MOST-PROMISING NEXT STEP (wifi DN): monitor-mode/phone-side capture of the
  offloaded frames (are they mangled? checksum? headers?) — the frames DO
  reach mac80211 (rx_dispatched climbs); compare one HW-forwarded frame
  against a SW one. Phase-C's stale-IP-checksum bug (4c3c5614d) is the
  precedent; cpu_chk_en bit16 alone was refuted live.
