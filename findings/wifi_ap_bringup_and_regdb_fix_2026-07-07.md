# WiFi STA re-verify + permanent 5 GHz regdb fix + first AP bring-up — 2026-07-07

Live H3600 (ZX279128S), mainline 6.6, RAM boot. Session goals: re-verify the
MT7915 STA path on the fresh WiFi kernel, then (per owner request) bring the
H3600 up as an **AP** with a real STA client, toward eventually observing WiFi
HW offloading.

## TL;DR

| Milestone | Result |
|---|---|
| Fresh WiFi kernel boots (RAM) | **PASS** (#516) after a boot-args fix (below) |
| MT7915 PCIe probe + wlan0/wlan1 | **PASS** (Gen1 x1, `[14c3:7915]`, MediaTek OUI) |
| 5 GHz regdom (the long blocker) | **FIXED PERMANENTLY** — `country ES: DFS-ETSI`, 5 GHz enabled |
| STA scan sees `Dino-WiFi-5GHz` | **PASS** (freq 5200, ch 40, on wlan1) |
| STA scan sees `Dino-WiFi` (2.4) | **PASS** (on wlan0, confirms radio RX) |
| **AP bring-up (hostapd)** | **PASS** — `AP-ENABLED`, beaconing ch 36 |
| **Real client associates** | **PASS** — Android STA: WPA2 4-way handshake + DHCP lease .10 + stable 377 s |
| AP -> client datapath | **PASS** — ICMP 3/3 0% loss (AP -> STA) |
| WiFi HW offload | **NOT IMPLEMENTED** (Stage 3 — see below) |

STA full 4-way/DHCP/ping was NOT separately re-run on 5 GHz this session (the
owner redirected to AP mode once the radio + scan + regdom were confirmed); the
AP path exercises the same crypto/handshake stack and passed with a real client.

## Boot-args fix (was silently corrupting userspace)

The documented WiFi boot line carried `cma=16M@0x4e800000`. That address now
lands **inside the eth-carved reserved-memory region** (`0x4c000000-0x4fffffff`,
DTS `eth_carved`) that exists since the ethernet driver landed. Result: every
userspace exec SIGSEGV'd, the C-init REPL returned `[exit=11]` on everything.
Fix (in `scratchpad/reboot_mainline_wifi.py`): drop `cma=`, boot with
`pci=nomsi pcie_aspm=off console=ttyAMA0,115200n8 mem=256M ignore_loglevel`
(the two PCI args stay at the FRONT — U-Boot corrupts the last arg; `pci=nomsi`
is mandatory, MSI never delivers MT7915 IRQs on this SoC).

## Permanent 5 GHz regdb fix (committed)

Root cause (confirmed): this host's wireless-regdb (2025.10) `regulatory.db.p7s`
is signed by `CN=wens`, but the kernel only shipped `net/wireless/certs/
sforshee.hex` built-in. With `CONFIG_CFG80211_REQUIRE_SIGNED_REGDB=y` the
wens-signed db was rejected — dmesg `regulatory.db is malformed or signature is
missing/invalid` -> country 00 -> every 5 GHz channel `No-IR` -> `iw reg set`
never took, wlan1 could not scan/associate on 5 GHz.

Fix: added `net/wireless/certs/wens.hex` (the wens regdb signing cert; it had
been staged into the tree on 2026-07-05 but the kernel was never rebuilt with
it). The certs Makefile globs `certs/*.hex` into `shipped_regdb_certs[]`, so
after rebuilding **cfg80211.ko** (it's `=m` — `make zImage` alone does NOT
rebuild it; must `make modules`) the kernel trusts BOTH sforshee- and
wens-signed regdbs. `shipped-certs.c` grew 4119 -> 8415 B (both certs).

Verified on-device after reboot into #516:
- `iw reg set ES` -> `iw reg get`: `country ES: DFS-ETSI` with
  `(5250-5350 @ 80)`, `(5470-5725 @ 160)` enabled (previously world/00, 2.4 only).
- `iw wlan1 scan` -> `SSID: Dino-WiFi-5GHz  freq: 5200`. Previously nothing on 5 GHz.

Committed as `4f4439ef1` (branch `phase6-hw-offload`): wens.hex + the wifi
staging script + recovered soft-float wpa_supplicant/iw + the boot script.

## AP bring-up (H3600 as access point)

hostapd = the static soft-float 2.11 (libnl 3.5.0) staged in the initramfs
(`/bin/hostapd`). Config: `tasks/00.07.wifi/configs/hostapd-ap-test.conf` —
wlan1, 5 GHz ch 36, WPA2-PSK/CCMP, SSID **`H3600-AP-Test`** (renamed off the
owner's home SSID), throwaway test passphrase `h3600aptest`.

- **First attempt failed** with `nl80211: 'nl80211' generic netlink not found`.
  This was a **pre-crash artifact**, not a real hostapd/libnl bug: the MT7915
  phy had gone away and the device rebooted right after (lost /tmp + modules +
  wiphy). Root of that instability is unconfirmed but correlates with the
  known MT7915 MCU ext-cmd timeouts (`EFUSE_BUFFER_MODE`/`TXBF_ACTION`, seq
  8/9) that fire at every probe. STA recovered cleanly on a fresh boot + chain
  reload (2 interfaces back), so nothing was permanently broken.
- **On a clean boot hostapd works**: `nl80211` resolves, phy1 selected, iftype
  AP set, mgmt frames subscribed, `wlan1: AP-ENABLED`. `iw wlan1 info` -> `type
  AP, channel 36 (5180 MHz), ssid H3600-AP-Test, txpower 23 dBm`. The beacon
  radiates well (Android scan sees it at RSSI -40).

### Client association (real Android STA)

The owner's connection failure ("no se puede conectar") was simply **no DHCP** —
Android drops a WPA network that gives no IP. Fixed by assigning
`192.168.50.1/24` to wlan1 and running `busybox udhcpd -S /tmp/udhcpd.conf`
(the bare `udhcpd`/`which` aren't symlinked; call the busybox applet directly).
Then via adb `cmd wifi connect-network "H3600-AP-Test" wpa2 "h3600aptest"`:

- Android: `SSID "H3600-AP-Test", IP 192.168.50.10, Supplicant state COMPLETED`
  (WPA2 4-way handshake completed, DHCP lease from our udhcpd).
- H3600 `iw wlan1 station dump`: `Station 76:b3:fe:0d:9f:39, signal -43 dBm,
  connected time 377 s` (stable).
- **AP -> STA ICMP: 3/3, 0% loss** (round-trip works over the air).
- STA -> AP ICMP: 0/3 — an Android-side routing/power-save quirk (avg RTT on the
  working direction was 441 ms, classic phone PSM; Android deprioritizes the
  route on a no-internet Wi-Fi). Not a device WiFi fault: the reverse direction
  proves the L2/L3 path is bidirectional.

## End-to-end: WiFi client reaches the internet THROUGH the H3600 (SW path)

After the AP worked, wired the client to the internet via the host as uplink and
**verified a real Android STA reaching 8.8.8.8 through the H3600** (cellular
data OFF, so the only path is WiFi):

```
Android STA 192.168.50.10
  -> WiFi 5 GHz WPA2  -> H3600 AP wlan1 (hostapd)
  -> H3600 route+NAT (MASQUERADE -o lan2)  -> lan2 (MAC2) 192.168.9.1
  -> host enxc8a362 192.168.9.2  -> host NAT (MASQUERADE -o wlo1)  -> internet
```

**Proof (device conntrack, cellular off):**
`src=192.168.50.10 dst=8.8.8.8 type=8 ... src=8.8.8.8 dst=192.168.9.1` — the
H3600 is NAT-translating the client's ICMP; 7 conntrack entries for the client.
Android ping 8.8.8.8 = 4/4 0% loss with mobile data disabled.

### The "host<->device DSA path is broken" was a MISDIAGNOSIS (two config bugs)

Earlier this session I concluded the DSA host<->device L3 path was broken. It was
not — two host/config mistakes:
1. **Host routing:** `ip addr add` on enxc8a362 was silently failing (expired
   sudo cache), so there was no connected route for the device subnet — the
   host sent the test pings out `wlo1` (default route via the home modem), never
   to the device. `ip route get 192.168.9.1` -> `via 10.44.66.250 dev wlo1` was
   the tell.
2. **Wrong port:** the host cable is on **lan2 (MAC2 / RJ45 #3, the U-Boot TFTP
   jack)**, NOT lan4/WAN as assumed. Found by flooding ARP from the host and
   reading per-port rx deltas on the device: lan2 +16 / sw +20, lan4 only +4.
   (Consistent with the memory: U-Boot TFTPs via MAC2, and this box TFTP-booted
   fine over this same cable.)

With the IP on **lan2** and the host route correct, host<->device is 3/3 both
ways, RTT ~2 ms. Device-side setup that made the client's internet work:
`ip route add default via 192.168.9.2`, `iptables -t nat -A POSTROUTING -o lan2
-j MASQUERADE`, `iptables -P FORWARD ACCEPT`, and udhcpd with `option dns` +
`option router 192.168.50.1`. Host-side: `ip_forward=1`, `iptables -t nat -A
POSTROUTING -s 192.168.9.0/24 -o wlo1 -j MASQUERADE`.

This is the **SW-forwarding baseline** (CPU routes+NATs every packet — visible
in conntrack/netfilter). It is exactly the base on which the HW offload (below)
is built.

## WiFi HW offloading — status: NOT IMPLEMENTED (Stage 3)

Per the earlier device-free RE (`findings/wifi_offload_feasibility_2026-07-04.md`):
mainline drives the MT7915 as a plain PCIe mac80211 netdev. To route client
traffic it must be **SW-bridged** into the LAN (CPU forwards every packet).
There is NO WED-style CPU-less path. Stock's "HW forwarding" = the switch fabric
has two extra WLAN ports (6/7) backed by the **IDM DMA ring** (which mainline
already drives as idm0/idm1) carrying a 4-bit port + 3-bit `ssid` in the
descriptor; the CPU still shuttles each packet MT7915<->IDM but HW does
classification/NAT/FDB/QoS.

So today an AP+client test shows **software bridging** only — there is no WiFi
HW offload to observe yet; building it is the Stage-3 effort. Concrete next
steps (ranked, from the feasibility finding):
1. SW-bridge wlan1 into the LAN bridge and confirm end-to-end client->LAN/WAN
   forwarding (baseline; CPU path). `CONFIG_BRIDGE=y` is ready.
2. Device probe of the IDM ssid path: de-isolate fabric port 6, inject an
   idm0 TX frame with the ssid bits set (`skb[0xb7]`, TX desc word1
   `len|idm<<31|ssid<<28`), check the HW FDB learns the client MAC on port6+ssid;
   confirm idm0 RX decodes ssid (RX desc byte6 bits0-2 + bit3 valid).
3. Glue dispatcher: map (idm,ssid)<->wlan netdev, direct-xmit both ways
   (bypassing bridge/netfilter), like stock idmfdb.ko.
4. Extend the CLA/PM flow-offload (the working DN ethernet path) to emit
   outport 6/7 + ssid so WAN->WiFi DN NAT rides HW.

Risks noted: exact stored-entry ssid encodings, the trap-all L2 behaviour (only
CLA flows get the full HW ride), MT7915 AP-mode MCU stability (the reboot above).

### Stage-3 gap analysis (mainline IDM code, 2026-07-07)

Device state today: `idm0`/`idm1` netdevs exist but are **DOWN** (qdisc noop,
0 rx) — fabric ports 6/7 unused. All debugfs offload tools are present
(`clapeek`/`clawrite`/`fdbadd`/`pmwrite`/`pmpeek`/`txtest`/`ftup`/`hashcalc`).

Mainline `drivers/net/ethernet/zte/zx-eth-main.c` gaps (vs the stock ssid path):
- **RX (`zx_idm_poll` :1633-1660):** decodes only `len` (word1 bits0-13) and the
  idm-port bit (word1 bit31); delivers via plain `napi_gro_receive`. The ssid
  (byte6 bits0-2) + ssid_valid (byte6 bit3) = word1 bits16-19 are **never read**.
  No `(idm,ssid)->vif` dispatch hook (the stock `idm_skb_recv` equivalent).
- **TX (`zx_idm_xmit` :1744-1746):** builds word1 = `len | (port?BIT31:0)` only;
  ssid bits 30:28 are **never set**, `skb[0xb7]` is never read.
- **No ssid macros** anywhere (`IDM_DESC_LEN_MASK`/`_PORT_BIT` only, :304-306;
  `IDM_DESC_CSUM_SHIFT 28` defined but unused). Ring is a raw `u32*`.
- **FDB (`zx_fdb_add` :656):** can address port 6/7 (`port<8`), encodes port in
  `d2` (:677), but the entry format has **no ssid field**; port 6 is currently
  repurposed as a plain CPU port for idm0/idm1 (comment :261).
- **CLA/PM builders:** all keyed on LAN/WAN ports + `ZX_CPU_PORT 5`; the
  `zx_ft_regport[8]`/`port_remap[8]` tables carry logical→phys for ports 0-7 but
  **no ssid / outport / ssid_flag** dimension anywhere.

**Port 6/7 isolation — POLARITY MUST BE VERIFIED FIRST.** `zx_port_isolate`
(:888) writes `PP_BRG_ISOLATE(p)=0x83C0+p*4` (PP block, `PP_OFF 0x1C0000`). At
:7619-7620 ports 6/7 get `0xFF` (also duplicated raw at :1340-1341). But the
code comment (:885) documents the register as an **allow-mask** (ports this port
may forward TO); the LAN loop `~(1<<i)` (allow all-but-self) only makes sense
under allow-semantics, under which `0xFF` = forward to ALL (MORE permissive, not
isolated). Stock uses `0xdf` (all except PON port 5). So the feasibility note's
"isolates 6/7 with 0xFF" is likely **inverted** — mainline already opens 6/7,
just not identically to stock. Read `PP[0x83D8]/[0x83DC]` live before changing.

**Ranked first reversible steps (do #1+#2 as one observational commit):**
1. After verifying polarity, align ports 6/7 forwarding mask with stock
   (`0xFF`->`0xdf`) at :7619-7620 (+ the duplicate :1340-1341). 2 lines, trivially
   revertible.
2. RX ssid decode (additive/observational) in `zx_idm_poll` after :1634:
   `u8 ssid=(word1>>16)&0x7; bool ssid_valid=(word1>>19)&1;` — log/count per-ssid
   (mirror `tm_rx_per_ingress` :394), keep `napi_gro_receive`. Gives the
   empirical RX-ssid ground truth once 6/7 are open.
3. TX ssid stamp in `zx_idm_xmit` :1744-1746: OR `((ssid&0x7)<<28)` + add
   `#define IDM_DESC_SSID_SHIFT 28`; defaults to 0 (= today) when no ssid marker.
   Only useful once AP-mode WiFi vifs feed frames with an ssid source.

Blocking unknown for #2/#3 to become *useful*: the exact ssid bit positions in
the **stored** FDB/CLA/PM entries still need RE from stock `tm.ko` — mainline
has none of that plumbing yet.

## Reusable gotchas this session

- **tftpd dies on USB-NIC re-enumeration.** The host TFTP NIC (AX88179,
  cdc_ncm, flaky after power-cycles) drops off the bus; in.tftpd is bound to
  192.168.1.50:69 and dies with it, so U-Boot's RRQ goes unanswered (`T T`).
  Fix used: a watchdog (`/tmp/tftpd_watchdog.sh`) that restarts tftpd + re-adds
  the IP/route whenever tftpd disappears. A genuine clean re-enum needs the iface
  to actually vanish (`echo 0 > .../authorized; sleep; echo 1`) — a too-fast
  toggle leaves it in the same stuck state.
- **REPL echoes commands to the UART log**, so never send the owner's WPA PSK
  through it. For the AP a self-chosen TEST passphrase sidesteps the issue
  entirely. The device DSA user ports do not give a working host<->device L3
  path without the full rig bridging, so `wget`-ing a secret config over the LAN
  wasn't available either.
- busybox has `udhcpd`/`udhcpc` applets but no symlinks — call `busybox udhcpd`.
- `iw reg set <cc>` silently no-ops while the regdb is rejected (country stays
  00); fixing the cert is the only way to get a real regdom.
