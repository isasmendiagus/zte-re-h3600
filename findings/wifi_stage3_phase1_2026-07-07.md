# WiFi Stage-3 Phase-1: IDM/fabric-port-6/7 polarity + RX-ssid observation — 2026-07-07

Live H3600 (ZX279128S), mainline 6.6, RAM boot. **Read-only-first observational**
pass on the IDM / fabric-port-6/7 path — NOT an offload implementation. Goal:
settle the port-6/7 isolation polarity empirically, then add an additive RX-ssid
decode and observe whether the IDM ring receives anything with the AP up.

Driver stability was preserved throughout: no rmmod, no `sw`-conduit bounce, no
NAND flash, RAM-boot only. The only source change is additive (counters +
debugfs print + one decode); delivery path (`napi_gro_receive`) is unchanged.

## TL;DR

| Step | Result |
|---|---|
| **STEP 1 — polarity** | **ALLOW-mask.** Ports 6/7 = `0xff` = **forward-to-ALL = fully OPEN**, NOT isolated. The feasibility note's "isolates 6/7 with 0xFF" was inverted. |
| **STEP 2 — mask alignment** | **No change made** (justified). `0xff` is what STOCK runs live too; it is maximally permissive (6/7 may reach every port). Aligning to stock's *code* value `0xdf` would only block forwarding to PON port 5 (unused, copper-only SKU) and would diverge from stock-LIVE. Minimal-risk = leave it. |
| **STEP 3 — idm0/1 up + RX-ssid decode + AP observe** | idm0/idm1 brought UP; additive RX-ssid decode built + **verified live on HW** (counters present in debugfs, increment path wired). AP `H3600-AP-Test` reached **AP-ENABLED** (ch36). **`idm_rx_count = 0` throughout** — the IDM ring received NOTHING (AP up, beaconing, broadcast floods). |

## STEP 1 — polarity resolution (READ-ONLY, no engine writes)

`PP_BRG_ISOLATE(p) = PP_base(0x92380000) + 0x83C0 + p*4`. Read TWO independent
ways on the live custom kernel:

1. Driver's own boot readback (`zx_eth_init_vlan_and_isolation` + `zx_chip_tm_init_isolate`):
   `isolate PP[0x83c0..dc] = 0xfe 0xfd 0xfb 0xf7 0xef 0xdf 0xff 0xff`
2. Independent debugfs `poke`/`peek` of each register (this session):

```
peek 0x923883c0 = 0x000000fe   port0
peek 0x923883c4 = 0x000000fd   port1
peek 0x923883c8 = 0x000000fb   port2
peek 0x923883cc = 0x000000f7   port3
peek 0x923883d0 = 0x000000ef   port4
peek 0x923883d4 = 0x000000df   port5 (CPU)
peek 0x923883d8 = 0x000000ff   port6  ← WLAN/IDM
peek 0x923883dc = 0x000000ff   port7  ← WLAN/IDM
```

Both paths agree exactly.

**Verdict: it is an ALLOW-mask (bit set = "this port MAY forward TO that port").**
Decisive evidence, from the bit math against a device that demonstrably forwards:

- LAN ports 0..5 each have **exactly their own bit cleared** (`~(1<<p)`):
  port0=0xfe (bit0 clear), port1=0xfd (bit1), … port5(CPU)=0xdf (bit5).
  Under allow-semantics this reads "forward to all EXCEPT self" — the correct,
  sensible switch behavior (no self-hairpin), and matches the driver comment
  "bit pattern of ports this port may forward to" + "idx5 (CPU)=0xdf blocks self,
  stops the CPU-TX hairpin" (which is the *proven* fix for the CPU-TX loop).
- Under the opposite (isolate/block) reading, every port could forward ONLY to
  itself — nonsensical for a switch that forwards fine. So allow-mask is the
  only self-consistent interpretation.
- Therefore **ports 6/7 = `0xff` = all 8 bits set = may forward to EVERY port =
  fully OPEN**, the MOST permissive value — not isolated.

This confirms the gap-analysis prediction: the earlier feasibility text
("probe isolates ports 6/7 with 0xFF") had the polarity **inverted**. Ports 6/7
are already open on mainline.

## STEP 2 — mask alignment decision: leave 0xff (no change)

The playbook allowed *optionally* aligning 6/7 to stock's `0xdf`. Empirically that
is unwarranted here:

- **Stock runs `0xff` LIVE on 6/7 too.** Stock's `pon_pp_port_isolate(6,0xdf)` is an
  OR (`pp[...] |= 0xdf`) onto a HW default whose bit5 is set, so stock's live value
  is `0xff` (DATASHEET §3.14 "Isolation live …={fe,fd,fb,f7,ef,df,ff,ff}"). Mainline
  already matches stock-live.
- `0xdf` differs from `0xff` only in **bit5 = PON port**. This is a copper-only SKU
  (no optical); WiFi offload needs 6/7 ↔ LAN(0–3)/WAN/CPU, never PON. So `0xdf`
  would remove an irrelevant path and, if the live default's bit5 were clear, make
  mainline LESS like stock-live.
- Hard constraint: don't risk the validated datapath. The minimal-risk, most
  stock-faithful choice is **no change** — 6/7 are already open.

Net: STEP 2 required no code edit. (Trivially revertible by construction — nothing
to revert.)

## STEP 3 — idm0/idm1 up + additive RX-ssid decode + AP observation

### Code (committed, additive only)
`linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`:
- `struct zx_eth`: `+u32 idm_rx_count; u32 idm_rx_per_ssid[8]; u32 idm_rx_ssid_invalid;`
  (mirrors the `tm_rx_per_ingress[]` pattern).
- `zx_idm_poll()` (RX loop): decode `ssid=(word1>>16)&0x7`, `ssid_valid=(word1>>19)&1`
  (= RX desc byte6 bits0..2 / bit3 per stock `dump_idm_desc_rx`), bump the counters.
  **`napi_gro_receive` delivery unchanged** — no dispatch, no behavior change.
- `zx_stats_show()`: print `idm_rx_count` + per-ssid histogram + `ssid_invalid`.

Built with `build_slotA.py` (`make all` + `make zImage`, .ko re-embedded). NOTE the
script exits non-zero on the **NAND slotA-packaging** step only (WiFi image ~20 MB >
the 0xc00000 NAND write window) — irrelevant to RAM/TFTP boot; `tftp/zImage_dtb.uimg`
was produced correctly and is what booted.

### On-device bring-up (custom kernel, verified running = has `idm_rx` counters)
- idm0/idm1: `<BROADCAST,MULTICAST,UP,LOWER_UP> … qdisc pfifo_fast` (were noop/DOWN).
- WiFi module chain loaded: pcie-zx279128s → cfg80211 → mac80211 → mt76 →
  mt76-connac-lib → mt7915e → `wlan0/wlan1` + `phy0/phy1`.
- `iw reg set ES` → `country ES: DFS-ETSI` (wens-cert regdb fix in effect).
- hostapd (`/bin/hostapd -B -t /tmp/hostapd.conf`, test SSID `H3600-AP-Test`, test
  pass `h3600aptest`) → `wlan1: AP-ENABLED`, `iw wlan1 info` = type AP, channel 36
  (5180 MHz), txpower 23 dBm. wlan1 tx_packets climbing (beacons/mgmt radiating).
- MT7915 probe health: firmware WM/WA loaded; `eeprom load fail, use default bin` +
  MCU ext-cmd timeouts seq 8/9 (EFUSE_BUFFER_MODE / TXBF_ACTION) — the documented
  non-blocking behavior; AP still enabled. No client associated this session.

### The observation
`idm_rx_count = 0` and `idm_rx_per_ssid 0..7 = 0 0 0 0 0 0 0 0 (ssid_invalid=0)`
**at every read**: AP-idle, after 18× broadcast pings (192.168.1.255 /
255.255.255.255), and while beaconing. Meanwhile the TM ring counters DID move
(`tm_rx_count` 187→195, `rx_per_ingress` port2/port4 climbing) — LAN traffic reaches
the CPU normally via the TM path.

**Conclusion (empirical RX-ssid ground truth for Phase 1):** with ports 6/7 OPEN and
idm0/idm1 UP, **the IDM ring receives nothing** — because *nothing steers fabric
traffic to ports 6/7*:
- The switch never targets 6/7 without the missing plumbing: no FDB entry →
  port 6/7, no CLA flow → outport 6/7, and evidently the broadcast-flood copies to
  6/7 don't reach the IDM RX ring either (likely needs the one-time
  `greg_set_wifi_queue1_protocol` / `pon_pp_set_wifi_mac_len` IDM-RX enable that the
  feasibility note flagged as a risk — untested, out of scope here).
- WiFi RX in mainline never touches the IDM ring anyway: MT7915 frames go
  mt76→mac80211 (SW path). Stock's `idmfdb.ko` is what injects WiFi RX into the IDM
  **TX** ring (upstream) so the fabric SA-learns port6/7+ssid — none of that glue
  exists in mainline. So `idm_rx = 0` is expected regardless of whether a client
  associates.

The counter mechanism is proven functional (present + wired); the *ssid value*
ground truth cannot be obtained until the FDB/CLA/greg plumbing that makes the
fabric DMA to 6/7 exists. That is the next phase (explicitly deferred here).

## Honest hardware-vs-inferred ledger
- **Ran on hardware:** the two isolate reads (driver + debugfs poke), the custom
  kernel boot (idm_rx counters prove it's the new build), idm0/1 up, full WiFi
  module chain + AP-ENABLED + regdom, the broadcast-flood test, and every
  `idm_rx`/`tm_rx` read above.
- **Inferred (not exercised):** *why* the flood copies don't reach IDM RX (greg
  IDM-RX enable hypothesis — not probed); the ssid bit *values* stock would stamp
  (needs the stored-entry RE the parallel device-free agent is producing); any
  client-traffic idm behavior (no client associated — but the path analysis makes
  it client-independent).

## Boot-flakiness gotcha (cost real time this session)
`reboot_mainline_wifi.py` / `reboot_wifi_longdtr.py` repeatedly reported BOOT_FAIL
even when the device HAD reached a usable REPL: the C-init prints
`=== C-init REPL ready on UART ===` (the script greps substring "REPL ready"), but
the marker detection kept missing it and the script would then **DTR-reset a
perfectly good boot and retry** — on one retry it reset the very boot I was working
on (idm up, wlan checks) and dropped the device to U-Boot mid-sequence, colliding
with my concurrent UART reads. Also: a **bare DTR power-cycle without interrupting
cspstart autoboots the flashed STOCK kernel from NAND** (per zte-device-access) —
so "the device booted" can mean stock, not the custom RAM image. Reliable recipe
that worked: kill all boot scripts, drive U-Boot MANUALLY over the bridge
(`tftp 0x42000000 zImage_dtb.uimg` → `setenv bootargs 'pci=nomsi pcie_aspm=off
console=ttyAMA0,115200n8 mem=256M ignore_loglevel'` → `bootm 0x42000000`), then do
NOT let any script reset it again. Confirm you're on the custom image by
`grep idm_rx /sys/kernel/debug/zx_eth/stats` (only the custom build has it) — NOT
uname (both are "#516"). The marker-detection bug in the reboot scripts is worth
fixing (or bump the marker string / trust a REPL round-trip instead of the log grep).

## Next phase (deferred — needs the stock ssid-encoding RE)
1. RE the ssid bit positions in the STORED FDB/CLA/PM entries (parallel device-free
   agent) — the blocking unknown to make the RX decode *useful*.
2. Probe whether an IDM-RX enable (greg_set_wifi_queue1_protocol /
   pon_pp_set_wifi_mac_len) is needed before the fabric will DMA port6/7 egress into
   the ring; then re-run this exact observation.
3. Only then: TX ssid stamp + the (idm,ssid)→vif glue dispatcher + CLA/PM outport-6/7
   extension (the full offload — NOT this phase).
