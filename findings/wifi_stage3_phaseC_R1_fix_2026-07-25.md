# WiFi Stage-3 Phase C — R1 ROOT-CAUSED: the fabric DOES deliver to the IDM RX ring; mainline never drains it (2026-07-27, wrap-up)

Session status: **R1 root-caused and the delivery mechanism PROVEN LIVE on HW**;
the driver-side code fix is specified but NOT yet written/built (session was
wrapped up by the coordinator before the fix commit + full e2e A/B). This doc is
the hand-off for whoever lands the fix.

Device: mainline build **#533** (`Linux 6.6.0 #533 Mon Jul 27 14:06 UTC 2026`),
RAM-booted, HEAD `efc45e25e` (phase6-hw-offload). Same rig/topology as the
Phase-C validation (§0.1 of `wifi_stage3_phaseC_offload_spec_2026-07-25.md`):
lan4 WAN 10.44.66.223 (host server wlo1 = 10.44.66.133), wlan1 AP 192.168.50.1
(hostapd + busybox udhcpd), Android client 76:b3:fe:0d:9f:39 = 192.168.50.100,
routed no-NAT, nft flowtable `{ lan4 }` + `flow add` on established TCP.

---

## TL;DR — R1 is neither a CLA lookup miss nor a fabric egress gap

1. **Layer (a) is EXONERATED**: during a reproduced black hole the CLA entry
   HIT and forwarded. `cla_dn_fwd` (phys `0x9238c3cc` lo16) climbed **+25 in
   lockstep with `qmg_dn_hw` (+25)** — same lockstep the proven eth DN path
   shows (`findings/perdir_pmslot_fix_2026-07-03.md`). The validation session's
   "`CLA fwd[0x1cc3c0] = 0`" was a red herring: `0x921cc3c0` is a *different*
   CLA-block counter that evidently does not count WiFi-egress forwards;
   `0x9238c3cc` is the one that tracks DN hardfast verdicts.
2. **Layer (b) is ALSO (mostly) exonerated**: the fabric **delivers the
   hw-forwarded frames into the IDM RX ring, correctly ssid-tagged**. During
   the black hole, `IDM[0x804C] RX_PENDING` (npp+0x804c, read via the driver's
   `stats` node — safe, no raw 0x9200xxxx pokes) showed **0x07a4005c = 92
   frames pending** (hi16 0x07a4 + lo16 0x5c = 0x800 = ring size 2048) while
   `idm_rx_count = 0`.
3. **THE ROOT CAUSE is a driver lifecycle gap**: the IDM RX ring's consumer
   (`zx_idm_poll` NAPI + the IDM IRQ) is only ever started in **`zx_eth_open`**
   (zx-eth-main.c:2086-2107, gated on `e->started`) — i.e. only when one of the
   **idm0/idm1 netdevs is administratively UP**. Nothing in the rig (or in any
   production bring-up so far) ever ups them, so since Phase 1: NAPI disabled,
   `IDM[0x8024] IRQ_MASK = 0x1F` (all masked, the probe-time init value,
   :1539), `IRQ_STATUS = 0x6` pending forever, frames accumulate in the ring
   and `idm_rx_count` stays 0. **Stock does NOT have this gap: `idm_net_init`
   writes mask = 0 at init** (decomp-RE'd note at zx-eth-main.c:278-284).
4. **LIVE PROOF (the fix works)**: `busybox ip link set idm0 up; ... idm1 up`
   → the ring drained instantly: `idm_rx_count 0 → 93`,
   **`idm_rx_per_ssid[4] = 93`** (every black-holed frame was ssid=4 tagged =
   idm1/ssid4, exactly the installed essid 0x1c), `ssid_invalid = 0`,
   `RX_PENDING → 0x08000000` (0 pending, 2048 free), `IRQ_MASK → 0x0b`.
   First-ever nonzero `idm_rx_count` on mainline — **the spec's "R1 retired"
   marker** (§4 V1).

## The reproduced black hole (evidence trail)

Repro protocol (`scratchpad r1_repro.py` in the session scratchpad): snapshot
`ctr.py` per-stage counters + driver stats, `ftwifi 1`, 30 s phone HTTP GET via
`adb shell toybox nc`, mid/final snapshots, `ftwifi 0`.

- Run "BH try 1" got the install through the production nft path:
  `[phaseC/ft] cookie=c56067d4 egress wlan1 -> wifi essid 0x1c ... installing`
  `[phase6/ft] recipe: proto=6 10.44.66.133:8080->192.168.50.100:47478
  eg_rp=28 wan_ing=1 nh=76:b3:fe:0d:9f:39 pm_slot=12 ... raw=0xb6c4
  buckets ram2[0xc4]/3[0x144]/4[0x184]/5[0x1c4]/6[0x204] rc=0`
  → **DL bytes = 0** (black hole reproduced).
- Deltas across that run: `cla_dn_fwd +25`, `qmg_dn_hw +25` (lockstep),
  PM fwd-class bytes +25 (`pm_fwdtrp` hi-byte, `dpa_fdct` byte3), DSCH
  inq/outq ticking, **zero drops everywhere**: `pp_drop +0`, `dsch_drop +0`,
  `cla_dn_drop +0`, `sadm_drop +0` (`red_drop +1` background), no wire egress
  (`mac2_tx` flat). The 25 = the server's initial window + retransmits, all
  eaten by the (then-undrained) ring.
- The synthetic white-box repro also works without a client:
  `fttest install deadb0b0 0a2c4285 c0a83264 1f90 d00d 28` (rc = raw 0xff09 —
  NOTE `zx_ft_install_recipe` returns **raw on success**, `rc=65289` in the
  fttest log line is success, not an error). Destroyed after use (rc=0).

## The one remaining validation gap (be honest)

The final e2e A/B (ftwifi=1 download at HW speed with flat trap counters vs
ftwifi=0 SW baseline) was **NOT completed**:

- Attempt 1 after the live fix: the DN install was **declined by our own
  collision guards** ("higher-way collision ram6", "way0 owned") — the
  long-lived boot has accumulated **stale tracked `ft_flows[]` entries**
  (installs whose DESTROY never arrived across many sessions; there is no
  debugfs dump of the tracked table, and dmesg had rotated). 2-of-3 retries
  collided; the try that installed is the black-hole evidence above (that was
  *before* idm links were up).
- Attempt 2 (after idm-up, fresh connection): the phone connection never
  established (0 bytes with **no** counter movement and **no** new
  [phaseC/ft] offer in dmesg — dozing Android, not a datapath signal). Session
  was wrapped before a retry.

Nothing observed contradicts the root cause; the 93-frame drain + ssid
correctness is strong proof of the delivery leg. But the throughput A/B still
needs one clean run.

## Fix shape for the resuming agent (driver change, not yet written)

**Start the IDM engine at probe (stock parity), not at ndo_open:**

- In `zx_eth_probe` after `netif_napi_add_weight(...zx_idm_poll...)` +
  `devm_request_irq`: `napi_enable(&e->napi);`
  `npp_and(e, IDM_REG_IRQ_MASK, ~IDM_IRQ_NAPI_MASK);` `e->started = true;`
  (equivalently write mask 0x0b like the live state).
- Remove (or no-op) the `e->started` NAPI/mask toggling from
  `zx_eth_open`/`zx_eth_stop` (:2086-2107, :2109-2131) so a user downing
  idm0/idm1 cannot kill WiFi-offload delivery. Keep `netif_carrier_*` /
  queue mgmt as-is. Note `napi_enable` on an already-enabled NAPI is a bug —
  ownership must live in exactly one place (probe/remove).
- Alternative (more conservative, if probe-time enable worries anyone):
  have `zx_wifi_bind` ensure-started; but the open/stop lifecycle interaction
  (last-port-down disables NAPI while a vif is still bound) makes this
  strictly worse. Probe-time is also what stock does.
- Keep `ftwifi` default OFF (unchanged).
- Regress guard idea (test-per-fix policy): after boot, WITHOUT touching idm
  links, `fttest install` a WiFi-egress tuple + hping the tuple from the WAN
  side (as this session did) and assert `idm_rx_count` climbs; plus assert
  `IDM[0x8024] & 0x04 == 0` at baseline.

Also worth landing (small QoL, found this session):
- A debugfs dump of tracked `ft_flows[]` (cookie/raw/pm_slot/age) — stale-flow
  collisions are now the dominant install-flakiness on long-lived boots and
  are invisible today.
- pipeline_stats' "CLA fwd" label should point at `0x9238c3cc` (or print both)
  — `0x921cc3c0` misled the Phase-C validation into calling this a lookup miss.

## Session gotchas (repeat offenders)

- `ctr.py read()`'s 30-poke burst at 0.05 s spacing caused a ttyAMA input
  overrun **while the CPU was busy SW-forwarding** (mid-download snapshot) —
  mangled two greps; idle-time snapshots were clean. Under traffic use the
  slower `ab_ctrs.py` pacing (0.25 s/line).
- `busybox grep -A9 "IDM regs"` must target `/sys/kernel/debug/zx_eth/stats`
  (the IDM section is in `stats`, not `regdump`).
- Console printk noise (periodic phone-ARP `TM-RX fabric NOPARSE` dumps — a
  pre-existing Phase-B-dispatch cosmetic, len=64 ARPs with the +2 stub offset
  quirk) floods zc() captures: `echo 1 > /proc/sys/kernel/printk` first.

## Device state at session end (left SAFE)

- Build #533 RAM-booted, uptime preserved (no reboot this session).
- `ftwifi = 0` (default, verified). No synthetic flows installed
  (`fttest destroy deadb0b0` rc=0). Stale tracked ft_flows[] from earlier
  sessions remain (unknown set — see gap above).
- **idm0 + idm1 left UP** = the live R1 workaround is ACTIVE on this boot
  (harmless with ftwifi off; makes the ring drain). A reboot reverts to the
  broken default until the probe-time fix lands.
- hostapd (`H3600-AP-Test`) + udhcpd still running; wlan1 bound (idm1,ssid4);
  client 192.168.50.100 associated; WAN modem healthy (0 % loss).
- Host: http.server on 10.44.66.133:8080 stopped; UART bridge :9999/:9998 up.
- No driver source changes were made this session (working tree's pre-existing
  modifications are from earlier sessions, untouched).
