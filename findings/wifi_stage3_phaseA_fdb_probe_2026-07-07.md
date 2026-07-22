# WiFi Stage-3 Phase A — read-only HW-FDB / CLA probe after real WLAN client assoc (2026-07-07)

Device agent, live H3600 (ZX279128S), mainline Linux 6.6, fresh RAM boot of the
WiFi kernel (`tftp/zImage_dtb.uimg`, Jul-7 build, boot args
`pci=nomsi pcie_aspm=off console=ttyAMA0,115200n8 mem=256M ignore_loglevel`).
**Strictly READ-ONLY**: no CLA/PM/FDB entry was written, no flow installed, no
driver source changed. The only register *writes* issued were indirect-engine
**READ commands** (CMD register with the read-select bit) plus normal AP/DHCP
setup — no forwarding/engine state was mutated.

Goal: settle the 3 open questions (spec §2/§4) about where/how `ssid` is stored,
by reading a HW-learned WLAN client's forwarding entries after a real client
associates to the H3600 AP.

---

## Setup that was brought up (all verified live)

- **WiFi chain loaded:** `pcie-zx279128s → cfg80211 → mac80211 → mt76 →
  mt76-connac-lib → mt7915e` → `wlan0`/`wlan1` (+ `phy0`/`phy1`). MT7915 probed
  (`0000:01:00.0`, WM/WA firmware loaded; the usual `EFUSE_BUFFER_MODE`/
  `TXBF_ACTION` seq 8/9 MCU timeouts are present and non-fatal as always).
- **AP up:** `iw reg set ES` → `country ES: DFS-ETSI`; hostapd on `wlan1`
  (`H3600-AP-Test`, 5 GHz ch36, WPA2-PSK/CCMP, throwaway test pass) →
  `wlan1: AP-ENABLED`, `type AP, channel 36 (5180 MHz)`.
  `ip addr add 192.168.50.1/24 dev wlan1`; `busybox udhcpd`.
- **Real client associated:** Samsung Galaxy A34 5G (adb `RFCW91EWESB`,
  `SM-A346B`) via adb `cmd wifi connect-network "H3600-AP-Test" wpa2 ...`.
  - `iw wlan1 station dump`: **Station `76:b3:fe:0d:9f:39`**, authorized/
    authenticated/associated, signal ~-49 dBm, connected.
  - DHCP lease (udhcpd): **192.168.50.10** (hostname `Galaxy-A34-5G`),
    `ip neigh dev wlan1` → `192.168.50.10 lladdr 76:b3:fe:0d:9f:39 REACHABLE`.
  - AP→STA ICMP 2/4 (phone PSM, as always; L2/L3 path proven up).

**Client MAC under test = `76:b3:fe:0d:9f:39`.**

---

## THE DECISIVE OBSERVATION — the switch fabric never sees the WLAN client

Driver counters (`/sys/kernel/debug/zx_eth/stats`) with the client associated
and AP↔STA traffic actively flowing:

```
rx_per_ingress port0..7 = 0 0 79 0 1205 0 0 0  (invalid=0)   ← port6/7 = 0
idm_rx_count      = 0
idm_rx_per_ssid 0..7 = 0 0 0 0 0 0 0 0  (ssid_invalid=0)
```

- **`idm_rx_count = 0`** — the IDM DMA ring (= fabric WLAN ports 6/7) received
  **zero** descriptors, even with a real client associated and pinging.
- **`rx_per_ingress` port6 = 0, port7 = 0** — no fabric ingress on the WLAN ports
  at all. (port2 = the host/lan2 wire, port4 = WAN; those climb, WLAN does not.)

This is the reproduction, with a *real associated client*, of the Phase-1
observation: **on mainline, WiFi traffic rides MT7915 → PCIe → mac80211 →
`wlan1` and never enters the switch fabric's SPA/ADM/CLA/FDB/IDM pipeline.** The
CPU SW-forwards every WLAN packet (route+NAT — proven in
`wifi_ap_bringup_and_regdb_fix_2026-07-07.md`). Consequently the switch HW has no
opportunity to autonomously learn or classify the WLAN client.

---

## Raw HW reads

Read mechanism = the driver's `poke` debugfs (single-arg = register PEEK;
two-arg where the value is an indirect-engine **read** CMD). Positive control
first to prove the read path returns real data.

### FDB-A (PP_BRG_RAM, the HW auto-learn target) — indirect regs CMD 0x92388014, D0/D1/D2 0x9238801c/20/24

**Positive control — device self-MAC `f4:f6:47:0f:42:64`** (seeded at probe,
"HW FDB seed self MAC port=1"), IBM-CRC16 bucket 456, slot 0:
```
poke 0x92388014 = 0x080001c8            (bucket 456 | slot0 | READ)
peek 0x9238801c (D0) = 0x0064420f       ← matches expected D0 (mac_high2=0x399f... here 0x6442, mac_low4>>24=0x0f) EXACT
peek 0x92388020 (D1) = 0x000000f0       ← status nibble 0xF (bits[7:4]) = valid/static
peek 0x92388024 (D2) = 0x03f6f401       ← low byte = port bitmap; MAC bytes f6 f4 present
```
Read path CONFIRMED working (returns a real, valid, non-zero entry).

**Client `76:b3:fe:0d:9f:39`** — IBM-CRC16 bucket **263**, all 4 slots:
```
slot0 poke 0x08000107: D0=0x00000000  D1=0x00000000  D2=0x00000000
slot1 poke 0x08400107: D0=0x00000000  D1=0x00000000  D2=0x00000000
slot2 poke 0x08800107: D0=0x00000000  D1=0x00000000  D2=0x00000000
slot3 poke 0x08c00107: D0=0x00000000  D1=0x00000000  D2=0x00000000
```
**Client is ABSENT from FDB-A.** (Expected entry words, had it learned, would be
`D2 top3=0xfeb376.. | port`, `D0=0x00399f0d`.) The reg-0x4e/D2 bits[31:10] the
question targets read **0** here only because there is **no entry at all** — not
because HW learned the MAC and left those bits clear.

### FDB-B (SBRAG secondary) — indirect regs CMD 0x92388814, BUSY 0x92388818, D0/D1/D2 0x9238881c/20/24

Client sbrg-hash (CCITT/XMODEM) bucket **199** (0xc7):
```
poke 0x92388814 = 0x080000c7   (readback 0x000000c7 — read-bit stripped by CMD mask 0x8fc00fff, expected)
peek 0x92388818 (BUSY) = 0x00000000   (idle)
peek 0x9238881c (D0)   = 0x00000000
peek 0x92388820 (D1)   = 0x00000000
peek 0x92388824 (D2)   = 0x00000000
```
**Client is ABSENT from FDB-B** too. (FDB-B is unused by mainline anyway.)

### CLA classifier hash table (ram2) + flow-offload state

- `ft_pm_verify = ok=0 retry=0 fail=0` → **zero PM/flow installs this boot** →
  no offloaded 5-tuple flow exists (none for the client, none at all). `ftup=1`
  (UP offload enabled) but nothing installed — nothing running installs one, and
  the WLAN datapath never triggers a flow build.
- Representative `clapeek ram2` (static boot-time per-inport trap rules):
  ```
  ram2 addr0x00: 0100005d 00154000 80000408 90001417 00000045 000000e0 0...
  ram2 addr0x21: 0100006d 00154000 80000408 90000817 00000042 000000e0 0...   (regport2 = logical port1)
  ram2 addr0x79: 01005055 00154000 80000408 80000c17 80000043 00c20001 0...   (regport3 = logical port2)
  ```
  Decoding `outport` (spec §4: `byte0xd[1:0]<<3 | byte0xc[7:5]`, from word3):
  word3 = `0x900014_17`/`0x900008_17`/`0x80000c_17` → byte0xc=0x17, byte0xd∈{0x14,0x08,0x0c}
  → **outport = 0 (CPU) in every case.** No entry carries an outport in the
  `0x10-0x1f` logical-WLAN-port range; these are inport-keyed CPU-trap rules,
  not 5-tuple flows, and none reference the client.

---

## Verdicts on the 3 questions

### Q1 — does HW-autonomous FDB-A learn write `ssid` into reg-0x4e (D2) bits[31:10]?
**STILL-AMBIGUOUS — unobservable on mainline; needs stock-live correlation.**
The premise ("after a real client associates, read the HW-learned entry") cannot
be met on mainline: the switch fabric received **zero** frames from the WLAN
client (`idm_rx_count=0`, port6/7 ingress=0), so **no HW-autonomous FDB-A learn
event ever fired** for the client. Its FDB-A bucket is empty. The reg-0x4e[31:10]
bits are therefore untestable here (0 = no-entry, not a learned-with-ssid=0
entry). Hypothesis (1) of spec §2 can be neither confirmed nor refuted on
mainline. **Recommend: boot stock, associate a WLAN client, dump FDB-A for its
MAC, inspect D2 bits[31:10].** (NOT performed here — hard constraint: stock boot
is a separate coordinator decision.)

### Q2 — is `ssid_out` on a plain DA/FDB hit VLAN-derived / HW-side-only / never populated?
**STILL-AMBIGUOUS — mainline evidence is consistent with hypothesis (3) but does
not distinguish it; needs stock correlation.** No WLAN frame reaches the fabric
on mainline, so no in-HW DA/FDB hit for the client occurs and no descriptor
`ssid_out` is ever populated for WLAN traffic. This matches spec §2 hypothesis
(3) ("WiFi-destined unicast that isn't a CLA-flow hit never gets a HW-resolved
ssid; the CPU picks it in SW") — which is exactly mainline's behavior (CPU
SW-routes/NATs all WLAN traffic). But that only describes *mainline*; whether
*stock*'s HW resolves ssid via VLAN vs a HW-only mechanism is not observable from
the mainline datapath. Needs stock correlation.

### Q3 — is CLA's 5-bit `outport` ever written `0x10-0x1f` for WiFi, or does stock never build such a flow?
**CONFIRMED for mainline (no such flow / no such outport); stock-half still needs
correlation.** Mainline installed zero flows (`ft_pm_verify=ok=0`); every live
CLA ram2 entry is a static CPU-trap rule with `outport=0`; mainline's flow
builders are keyed on LAN/WAN ports 0-5 only (gap analysis). **Mainline never
writes an `outport` of 0x10-0x1f for WiFi and builds no WiFi hardfast flow at
all.** Whether *stock* builds a hardfast flow with `outport=0x10+ssid` (spec §4's
well-grounded hypothesis) remains unconfirmed and is answerable only on stock.

---

## Bottom line for the Stage-3 plan

Phase A **cannot be completed on mainline alone.** The root cause is structural,
not a probe gap: mainline's WiFi datapath (MT7915 PCIe → mac80211 → `wlan1`, CPU
SW-forwarding) never routes WLAN client traffic through the switch fabric, so the
switch HW never learns/classifies a WLAN client and the three ssid-storage
questions have no live mainline signal to read. `idm_rx_count` stayed **0**
throughout with a real associated, actively-pinging client — the definitive
evidence.

**Recommended next step (coordinator decision — NOT taken here):** a **stock-live
correlation** session. Stock's `idmfdb.ko` + IDM plumbing *does* route WiFi
through the fabric (fabric ports 6/7 / IDM ring), so on stock the same structures
(FDB-A D2 bits[31:10], any CLA WLAN-outport flow, descriptor `ssid_out`) will
carry real values after a client associates. Boot stock, associate a WLAN client,
dump FDB-A/FDB-B/CLA for its MAC, and compare against spec §2 hypotheses (1)/(2)
and §4's `outport=0x10+ssid` hypothesis. Per the hard constraints this device
agent did not boot stock.

## Reproduce
- Boot: `/tmp/.../scratchpad/boot_once.py` (one-shot manual U-Boot tftp+bootm, no
  re-reset of a good boot).
- WiFi chain + AP + client: steps above (hostapd `H3600-AP-Test`, udhcpd,
  adb `cmd wifi connect-network`).
- Reads: `scratchpad/dcmd.py` driving `poke`/`clapeek` over the UART bridge :9999;
  peeks land in `dmesg` (console). Bucket math in this session's Python snippet
  (IBM-CRC16 for FDB-A, CCITT/XMODEM for FDB-B).
