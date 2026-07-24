# WiFi Stage-3 Phase B — first on-device validation of the IDM dispatcher (2026-07-24)

Live H3600 (ZX279128S), mainline 6.6 RAM-boot, kernel **#520** (commit a43cd8cd0 + one
in-session fix, below). First hardware exposure of the Phase-B IDM-ring↔WiFi-vif
dispatcher. Device driven over the UART bridge (:9999); AP brought up on wlan1
(`H3600-AP-Test`, ch36, WPA2, test passphrase) with busybox udhcpd; a real STA
(host `wlo1`) associated + DHCP'd early in the session (later reverted to keep the
host online — the owner's phone was PIN-locked and Samsung blocks
`cmd wifi connect-network` for the adb shell uid, so the OTA-STA phase of the test
is deferred to the end of session / a follow-up).

## TL;DR verdict

**Phase B's CPU-side machinery WORKS on hardware — but WiFi does NOT yet ride the
fabric, because the fabric side (not Phase-B code) swallows everything:**

| Piece | Verdict |
|---|---|
| `wifi_bind` debugfs knob (bind/unbind/dump) | **WORKS** (after an in-session bug fix, below) |
| Dispatch table + rx_handler install/uninstall on a live netdev | **WORKS**, no oops, reversible |
| TX path: rx_handler → skb->cb ssid tag → `zx_idm_xmit` ssid stamp → ring | **WORKS**: `idm_wifi_tx_injected` counts every frame; HW consumes every descriptor |
| Frames enter the switch fabric | **YES** — RED trap-queue accounting tracks the injected count exactly |
| Frames reach anything CPU-visible (TM RX, IDM RX, wire) | **NO** — black-holed after the RED trap stage |
| RX path: fabric → IDM ring → dispatch → vif | **UNTESTED by traffic — nothing on mainline ever egresses to fabric ports 6/7** (empirically confirmed; the spec §6.5 chicken/egg is real) |
| `idm_rx_count` / `idm_wifi_rx_dispatched` after binding | **still 0** (baseline 0 → post-bind 0) |

So the answer to THE KEY QUESTION (does binding make the idm counters move?):
**`idm_wifi_tx_injected` moves (TX direction proven live); `idm_rx_count` does not**,
and the reason is now precisely localized in the fabric configuration, not in the
dispatcher.

## Pre-boot: a real bug found & fixed before first run

`zx_wifi_bind_write` read `f->private_data` as `struct zx_eth *`, but the fops uses
`single_open()` for the read side — after open, `file->private_data` is the
`seq_file`, so the very first `echo` into the knob would have dereferenced a
seq_file as a zx_eth (oops or silent corruption at a multi-KB offset). Every other
write-knob in the driver uses `simple_open` (direct `i_private`); `wifi_bind` is the
only seq_file+writer combo. Fixed:

```c
struct zx_eth *e = ((struct seq_file *)f->private_data)->private;
```

The unfixed build would have failed step 1 of the validation in a misleading way
(likely an oops inside `zx_wifi_register_vif`).

Also rebuilt/re-staged the initramfs (it lives in `/tmp/initramfs_extract`, which had
been wiped: only `lib/` survived; the first boot of the day ran an initramfs with no
`/proc`,`/sys`,`/tmp` mount points and a **stale Jul-3 eth .ko**). Root cause of the
stale-module trap: `build_slotA.py` copies the fresh .ko with `shutil.copy2`
(mtime-preserving) — if the copied .ko's mtime is OLDER than the already-generated
`build/usr/initramfs_data.cpio`, the final `make zImage` skips cpio regeneration and
silently ships the previous initramfs. Force-fix: `touch` the .ko +
`rm build/usr/initramfs_data.cpio*` before rebuilding. (Verified the embedded cpio
carries the fresh 461080-byte module before booting #520.)

## What was exercised on hardware (chronological)

1. **RAM-boot #520** (manual U-Boot drive: tftp + `pci=nomsi pcie_aspm=off` bootargs
   first, no cma). `wifi_bind` node present, table empty, counters 0.
2. **WiFi bring-up**: pcie-zx279128s → cfg80211 → mac80211 → mt76 → mt76-connac-lib →
   mt7915e (the known non-blocking MCU seq-8/9 timeouts appeared; also
   `eeprom load fail, use default bin` — cosmetic this session, MACs are MediaTek
   defaults). `iw reg set ES` OK, hostapd `AP-ENABLED` on wlan1 ch36,
   udhcpd on 192.168.50.1/24.
3. **STA sanity** (host wlo1): WPA2 4-way + DHCP lease 192.168.50.10 — AP path
   healthy. (Reverted per owner request to keep the host's internet.)
4. **Baseline counters** (pre-bind): `idm_rx_count=0`, per-ssid all 0,
   `rx_dispatched=0 rx_nobind=0 tx_injected=0`. Matches Phase-A: WiFi never touches
   the fabric on mainline.
5. **Bind**: `echo 'wlan1 1 4' > wifi_bind` → rc=0, node 12 (idm1/ssid4) live,
   table dump correct, netdev_info printed. No -EBUSY (wlan1 unbridged in this rig),
   no crash. Unbind + rebind also exercised later on another node.
6. **Ring-TX probe (no WiFi needed)**: put 10.66.66.1/24 on idm1, ping unresolvable
   in-subnet targets → ARP broadcasts TX on idm1. Netdev TX counters advance; IDM
   **TX_STATUS (npp+0x8044) done-count advances 1:1 with every injected frame** —
   the HW DMA consumes every descriptor (matches the May-28 observation).
7. **Where do they go?** Canonical-counter A/B (ctr.py) around clean bursts:
   `red_trp_in`/`red_trp_out` exceed background by exactly the injected count
   (+27, +8, +21 across three runs), while `qmg_dn_trap`/`cla_dn_trap` count only
   background. **The frames DO enter the fabric and traverse the RED trap-queue
   accounting (in AND out), then vanish**: no TM RX (q0-q15 both rings), no IDM RX
   descriptor writeback (all word1==0 in DDR, checked via devmem), no wire egress
   (mac2_tx flat, host tcpdump silent), qmg_dn_trap untouched.
8. **Unicast variant**: `fdbadd` host-MAC → port 2, static ARP, ping → 8 unicast
   ICMP frames from the ring: same result (trap-class accounting, no delivery, NOT
   FDB-forwarded to the wire). Consistent with mainline's known trap-all posture —
   IDM-ingress frames are trapped like everything else, but their trap DELIVERY
   never reaches the CPU (unlike wire-ingress traps, which arrive on TM q7 fine).
9. **IDM register diff vs stock** (live peeks vs the May stock dump
   `tftp/fpga_npp_stock.txt`): base/enable/control all match
   (`CONTROL=0x020f6766`, `RX_ENABLE=0x4000800` — the ring RX enable IS armed).
   Two real differences found:
   - `IRQ_MASK` npp+0x8024: stock `0x1b`, mainline `0x0b` (bit4 not enabled;
     mainline never writes this reg).
   - **Per-queue credit/qlen block npp+0x8050..0x8064: stock `0x08000000` ×6,
     mainline `0x00010000` ×6** (mainline's 2048 init kicks all credit queue 0 =
     npp+0x804c only). Poked all six to the stock value (write sticks, verified by
     re-peek) → **no behavior change**: injected frames still black-hole, IDM RX
     descs still untouched. So the credit block alone is not the gate (or not the
     whole gate).
10. **IDM IRQ (GIC SPI 38, /proc/interrupts `zx279128-eth-idm`) fired exactly once
    since boot** despite 100+ consumed TX descriptors — the engine never signals
    TX-done/RX events with mainline's IRQ_MASK; possibly related to the mask-bit4
    difference, but irrelevant until something is actually delivered to the ring.
11. **Full TX-path white-box test WITHOUT a STA** (the dispatcher is netdev-
    agnostic): temporarily bound `lan2 1 5` (node 13) and pinged the device from
    the host → every host frame arriving on lan2 was intercepted by
    `zx_wifi_rx_handler`, ssid-stamped, and injected:
    **`idm_wifi_tx_injected` 0 → 6 → 22**, idm1 TX counters advanced in lockstep,
    descriptors consumed, **zero dmesg warnings**. These frames carried VALID ssid
    bits (ssid=5, ring=1 — byte-identical encoding to stock's WiFi UP direction) —
    and the fabric still swallowed them, so the RX-delivery gap is independent of
    ssid tagging. Unbound cleanly afterwards (`del 1 5`).

## Root-cause picture (empirical, as far as this session got)

```
vif RX ──rx_handler──> ssid tag ──zx_idm_xmit──> IDM TX ring ──HW consumes──>
   fabric ingress (port 6/7) ──> trap classification (RED trp_in/trp_out move) ──> ∅
                                                     │
                    wire-ingress traps take this path too, but THEIRS are delivered
                    to TM DN q7 and the CPU sees them; IDM-ingress traps never
                    surface on ANY CPU-visible ring/queue.
```

- The Phase-B spec §4 claim ("no additional register write is needed for the ring
  to receive") is **falsified in the interesting direction**: the ring RX *enable*
  is indeed live, but delivery INTO the ring (and CPU delivery of port-6/7-ingress
  traps generally) needs fabric-side configuration mainline doesn't have.
- The spec §6.5 chicken/egg is **empirically confirmed**: binding alone creates no
  ring-RX traffic. Nothing on mainline ever chooses fabric ports 6/7 as egress —
  the FDB is not consulted for forwarding (trap-all), CLA has no WiFi flows
  (Phase C), and flooding doesn't reach the ring either.
- The remaining unknown is the stock-side config that (a) delivers port-6/7-ingress
  traps to a CPU queue, and/or (b) makes QMG egress-to-port-6/7 pop into the IDM RX
  ring. Candidates from the session: the `IRQ_MASK` bit4 delta; the ram7
  (ptype,port)→qid trap-queue map contents for ports 6/7 (mainline replays qids
  from `zx_pkt_map.h` — mostly qid 4 — while live wire traps demonstrably use q7 via
  the CLA ram2 `cpu_qid` override; inports 6/7 have NO ram2 coverage in the boot
  snapshot, so their traps fall back to the ptype map's queue → possibly a queue
  whose delivery path mainline never arms); and whatever stock's fuller
  `pon_npp_idm_init` / QMG-queue↔IDM-engine binding does (dedicated RE pass
  dispatched, results to be appended below).

## dmesg / stability

Zero warnings/oops across every new code path: bind, unbind, dispatch-table reads,
100+ tag-stamped injections, concurrent hostapd + binds. The guarded/inert-by-default
design held up on hardware.

## Status of the spec's §5 checklist after this session

- Step 1 (scaffolding): ✅ live.
- Step 2 (bind knob + rx_handler): ✅ live (with the seq_file fix).
- Step 3 (TX stamp): ✅ live — `tx_injected` moves, descriptor word1 carries
  clamped ssid bits, ring consumes.
- Step 4 (RX dispatch): code path live and inert (never fires — nothing arrives on
  the ring); **blocked on the fabric-side delivery gap**, which is now the concrete
  next work item (it is a prerequisite piece of Phase C's "make the fabric target
  ports 6/7" anyway).
- Step 4.5/5: n/a until the above.

## LIVE DISCOVERY: the rx_handler eats EAPOL/DHCP — binding an AP vif breaks new clients

Mid-session the owner tried to join `H3600-AP-Test` and could not. Root cause: the
Phase-B binding on wlan1. `zx_wifi_rx_handler` consumes EVERY data frame the vif
receives — **including EAPOL (the WPA2 4-way handshake) and DHCP** — and diverts
them into the IDM ring before hostapd's `ETH_P_PAE` packet socket can see them
(rx_handler runs before ptype_base delivery). A STA associates at the mgmt level,
then the handshake times out. Confirmed by mechanism (the earlier wlo1 STA joined
fine BEFORE the bind existed; the AP chain — hostapd alive, `AP-ENABLED`, IP,
udhcpd — was verified healthy while the failure reproduced). Unbinding restored
joinability.

**Design consequence for Phase B/C:** `zx_wifi_rx_handler` needs a passthrough
(RX_HANDLER_PASS) for at least `ETH_P_PAE` (0x888e), and — until the fabric can
route them back — DHCP/local-destined traffic. Stock's idmfdb faces the same
topology and its `idm_fdb_recv_handle` is gated by `ffe_get_npu_enable()` and
called from inside the vendor driver at a point where control traffic is handled
separately. This is a REAL on-device finding the spec could not have predicted.

## Appendix — dedicated RE pass on the fabric-admission gap (same session)

A device-free RE agent swept the stock decomps for "what stock programs that
mainline omits" for IDM-ring→fabric admission. Results, each then tested LIVE:

| Candidate (stock write mainline omits) | Live mainline value | Poke result |
|---|---|---|
| #1 `pon_pp_set_wifi_mac_len` → 0x923a0028 = 0x640 | **already 0x640** (matches stock) | REFUTED — nothing to fix |
| #2 `greg_set_wifi_queue1_protocol` → 0x921c0090/94 = 0 | 0x90 read **0xa6d30000** (≠ stock 0), 0x94 = 0 | poked 0x90→0 (sticks) — **no change**, still black-holed |
| #3 greg per-port stp/closed 0x921c0040/44/4c = 0 | all already 0 | REFUTED — match stock |
| #4 SPA 0x921d4054 \|= 0x3000000 | already 0x03ff05dc (= stock) | REFUTED — match stock |
| IDM per-queue credit block npp+0x8050..0x8064 = 0x08000000 (found by direct reg diff, not the agent) | 0x00010000 ×6 | poked to stock values (stick) — **no change** |
| IRQ_MASK npp+0x8024 stock 0x1b vs live 0x0b | differs | not poked (pure IRQ signaling; nothing is delivered to signal about) |

The agent also verified: stock's `pon_npp_idm_init` is **byte-faithfully replicated**
by `zx_idm_init` (every register, same values, same order — table in the agent
report); the TX descriptor format is identical; `aclWLANToIDMEssidCfg2` /
`s_aclWlanToIdmEssidMap` is pure software (no HW writes — it is stock's SW
(idm,ssid)→netdev lookup, i.e. stock's equivalent of OUR dispatch table); ports
6/7 isolation is open (0xff allow-mask, re-confirmed); and the previously-refuted
pokes (0x923a001c bit29, pp+0x2c bit29) were not re-tried.

**Best-supported root-cause hypothesis after all refutations:** the gate is not a
static init-register delta in any compared window. Mainline's replayed CLA table
(boot snapshot) contains catch-all classification entries ONLY for inports 0-5
(16×inport-0/CPU + 8 each for wire inports 1-5, zero for 6/7 — zx_cla_table.h,
[[zte-cla-ram-layout]]); on stock, the WLAN-side CLA/QMG state is populated at
WLAN-config time (post-snapshot, by the WLAN config machinery), which is exactly
the state a frame ingressing fabric port 6/7 needs to be classified and delivered
anywhere. A LOOK_UP_MISS from an uncovered inport appears in RED trap-queue
*buffer accounting* (in+out) but produces no delivery — matching every observation.
Confirming this requires either a stock-live capture of the WLAN-time CLA/QMG
writes (SSH oracle, next session) or crafting a ram2 catch-all entry for inport
6/7 on mainline via the existing clawrite/hashcalc machinery — both are Phase-C-
adjacent work items, and the second is the actual Phase-C deliverable anyway.

## Follow-ups

1. **EAPOL/DHCP passthrough in `zx_wifi_rx_handler`** (must-fix before any real
   STA rides a bound vif — see the live discovery above).
2. Stock-live oracle: capture the CLA/QMG writes stock performs at WLAN-config
   time (the runtime state the boot snapshot misses), OR craft an inport-6/7 ram2
   catch-all on mainline and watch the injected frames get classified.
3. Real-STA OTA test of the TX direction (bind AFTER the STA has associated and
   leased, to dodge #1) — expected identical to the lan2 white-box result (same
   code path, already proven).
4. Decide whether IRQ_MASK bit4 + the 0x8050..0x8064 credit block + 0x921c0090=0
   should be added to `zx_idm_init` regardless (stock parity, all harmless live).
5. The `eeprom load fail` message — stage the EEPROM under the exact filename this
   mt76 version asks for (cosmetic).
