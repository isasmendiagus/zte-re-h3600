# port1 ingress: dropped at `drop_PP` (forwarding stage) — localization CORRECTED

**Date:** 2026-06-01 (PM). **Supersedes:** `port1_sdet_ingress_gate_re.md`, `port1_spa_admit_gate_re.md`,
and the H1 `0x19068` hypothesis — all of which said port1 dies at MAC→SPA/SDET. **They are WRONG.**

## What was proven (clean delta measurements, both kernels)
New instrument: `pipeline_stats` now prints the full per-uni ingress chain (MAC RX/CRC/ovf, SPA rcv_uni
`0x145cc+uni*4`, SDET transport `0x4160+uni*4`, QMG sw/hw_fwd/hw_trap `0x18c044/48/4c`, drops PP/RED/DSCH
`0x1a040/44/4c`). Delta over 25 host pings (host NIC `enxc8a362e95900`/.50 is physically on jack2=port1;
confirmed via `smac1 RX_pkts`):

| stage | MAINLINE port1 | MAINLINE port2 (works) | STOCK port1 (works) |
|---|---|---|---|
| MAC RX (+0x780) | +27 | +22 | +25 (25/25 ping OK) |
| SPA rcv_uni | +27 | +22 | — |
| SDET transport | +27 (PASSES) | +22 | — |
| **drop_PP (0x921da040)** | **+27 (ALL)** | +0 | **+0** |
| QMG sw_fwd (0x9234c044) | ~+1 | — | **+77 (→CPU)** |
| rx_per_ingress→CPU | **0** | +22 | (ping replies OK) |

⇒ port1 frames **fully traverse MAC→SPA→SDET** (clean: CRC=0, ovf=0 — NOT a serializer/data issue),
then are **100% dropped at `drop_PP`** = the forwarding/bridge decision stage (NOT RED=congestion, NOT
DSCH=egress-sched). On STOCK the same frames pass PP and are forwarded to CPU via QMG sw_fwd. The
old "SDET uni1 transport=2" reading was a stale/low-traffic snapshot, never a real localization.

## Ruled OUT as the gate (2026-06-01, stock-vs-mainline live reads)
- **isolation table** `0x83c0..0x83dc` = `fe fd fb f7 ef df ff ff` — **IDENTICAL** stock & mainline.
- **STP / port_closed** greg `0x40/0x44/0x4c` = `0/0/0` in both — STP unused, no port closed.
- **ALL global forwarding config** (CLA-cfg `0x8c080`=0x600 stock / unwritten mainline; unk-ucast
  `0x8340`=0x015555ff; bcast-flood `0x8300/04`=0; bridge-enable `0x801c`=0x1ffff; LEARN `0x81c4`=0x5555;
  `pt_tls 0x8380`=1). **Logical proof it's not global:** port2/3 forward fine in mainline WITHOUT stock's
  values ⇒ a global diff cannot be the gate. **The gate must be PER-regport2.**
- CLA fwd/drop/copy `0x9238c3c0/c8/d8` + SADM pass/drop `0x92384200/08` read 0 on mainline during the
  drop (wrong offsets or clear-on-read — not useful; don't rely on them).

## CLA ram1 lead — REFUTED by HW (2026-06-01)
Found that mainline's LIVE CLA rule-TCAM (ram1) word[0] reads differently from stock AND from its own
source `zx_cla_init_table` at odd addresses (0x3/0x11/0x13/0x15 read the *neighbouring* key). Looked
like a flaky CMD-commit in the 780-entry replay (a sentinel `0xdeadbeef` write+read round-tripped, but
a correct-value rewrite didn't stick). Added a read-back-verify-retry to `zx_cla_write_entry` and
rebuilt. **Result: ram1 reads UNCHANGED and port1 STILL drops (drop_PP +26, rx_per_ingress port1=0).**
⇒ the ram1 word[0] discrepancy is most likely a READ-addressing artifact (odd-addr aliasing in the
indirect read — my fix's read-back aliased too, so it never "converged"). **CORRECTION (don't trust my
earlier "CLA exonerated"):** the verify-retry test was INVALID (broken/aliased verify), so port1 still
dropping does NOT exonerate the CLA. The per-inport **ram2-6** classification (the trap decision, distinct
from the ram1 rule-TCAM) is the LIVE lead — stock's golden regport2/regport3 entries are now captured in
`tasks/00.10.02.re-stock-kmods/findings/captures/cla_stock/`. **The verify-retry change was HARMFUL and
was REVERTED:** dmesg showed `CLA init: 1641 ok, 163 fail` (the read-back verify never
converges — the indirect READ is itself unreliable/aliasing, so it rejects valid writes) and the
re-read entries came back with ZEROED bodies. So `zx_cla_write_entry` is back to the original simple
write. OPEN QUESTION (low priority, not the gate): is the live ram1 word[0] discrepancy a real write
bug or purely a read artifact? The indirect CLA READ via clapeek is demonstrably unreliable (aliasing
odd addrs + zeroed bodies under some conditions), so NO per-addr CLA read can be trusted without a
sentinel round-trip. Don't build on clapeek CLA reads.

## Still open — the per-regport2 forwarding/trap decision
Both LAN ports reach CPU only by **CLA trap** (broadcast flood = 0 in stock too, so flood isn't the
path). port1's frames (incl. broadcast ARP) get NO valid destination → drop_PP. So **regport2's
trap-to-CPU decision is what differs.** Candidates:
1. CLA per-inport classification: rule TCAM (ram1) + per-inport hash (ram2-6). `cladump` shows ram7
   (trap-queue) identical p0..p6, but ram2-6/ram1 (the trap *decision*) NOT yet verified reliably for
   regport2 vs regport3. Mainline replays a 780-entry `zx_cla_init_table` (zx_cla_table.h) captured
   from stock — verify it actually programs regport2's trap, and diff vs stock's live CLA.
2. The to-CPU MECHANISM itself differs: stock uses QMG sw_fwd (+77); mainline's working ports reach
   CPU with sw_fwd barely moving — mainline may trap via a different path that misses regport2.

## Tools / method (this session)
- **Stock reg read = `/dev/logger_main`** (NOT /proc/kmsg — old doc was wrong). Recipe in
  [[zte-device-access]]; widx=(phys-0x92000000)/4; value line `fpga read: reg=0x.., value=0x..`.
- **Mainline:** debugfs `pipeline_stats`/`stats`/`cladump`/`clapeek`/`poke`/`mem` over the UART REPL
  (:9999), no network needed (host is on the broken port1). `poke` lets you test fixes live (no rebuild).
- Bench: host has 3 USB-NICs, one per jack — `enxc8a362e95900`/.50→jack2=**port1**, `enx2c99…`→jack3=
  port2, `enx6c70…`→jack4=port3. Generate port1 ingress: `ping 192.168.1.99` (only .50 has an IP).
- Branch `port1-d00d30-probe` carries the `pipeline_stats` ingress-chain enhancement (worth keeping).
- REFUTED this session: the smac_init d00/d30 0x32/0xA8 lead (all 4 ports' HW defaults byte-identical;
  the writes don't even stick — read back 0). Stock MAC bring-up fully decoded & faithfully ported.

## RETRACTION (2026-06-01, end of session) — CLA word0 "corruption" UNCONFIRMED
I briefly concluded mainline corrupts regport2's CLA word0 (clapeek read 0x0100006d vs golden 0x01005055)
and built a write-race fix. The fix did NOT change the read and did NOT fix port1. A controlled
sequence-read then proved mainline's **clapeek word0 (data[0]) read is unreliable** (address-dependent,
mismatches the source table even where it should match; words 1..16 read fine). So the "corruption" was
likely a READ artifact in `zx_cla_read_entry`'s data[0] fetch, not real CLA state. Fix reverted.
Net: port1 still drops at drop_PP (reliable); the per-regport2 cause remains UNIDENTIFIED; and any
mainline CLA word0 value must be treated as untrustworthy until zx_cla_read_entry's data[0] read is fixed.

## RE-LOCALIZED (2026-06-01, agent fresh-eyes review) + two more leads poke-refuted
Outside-view agent caught two real errors of mine:
1. `pipeline_stats` read the WRONG-DIRECTION QMG counters: 0xc044/48/4c are **DN (egress)**; LAN→CPU is
   **UP: 0xc054(sw_fwd)/0xc05c(hw_fwd)/0xc060(hw_trap)**. Fixed in pipeline_stats.
2. `drop_PP` (0x921da040) is the **OPC "PP DROP cnts"** aggregate (read by both up & dn stock dumpers),
   NOT a "bridge forwarding-policy" stage. So my "drop_PP = forwarding decision" framing was wrong.
RE-LOCALIZATION via the correct counters (H1): port1 frames pass SPA+SDET, **are NOT hw-trapped to CPU**
(UP hw_trap does not count them; UP sw_fwd is always 0 even for working ports), and end at OPC drop_PP.
Working ports DO get UP hw_trap → CPU. So it's a **trap-to-CPU verdict miss for regport2**. Confirmed
genuinely per-port (NOT traffic-type): the boot log shows an ARP (0806) from a working port trapped to
CPU, while port1's ARP is dropped — same frame type, different ingress port.

Leads tested via live `poke` (free, reversible) and REFUTED (port1 still drops, rx_per_ingress port1=0):
- **PP[0x8008] inport/outport vl_chk**: mainline 0x0000ff00 vs stock 0x0000dfdf. Poked to 0x0000dfdf
  (readback confirmed) → port1 still drops. (Consistent: it's a global byte; ports 2/3 work without it.)
- **SPA pt_802x_trap_en 0x921d4064**: stock 0x7f, mainline never writes it. Poked to 0x7f (readback
  confirmed 0x7f) → port1 still drops.

PATTERN: every config-register diff looks promising but the live poke does NOT fix port1. Increasingly
this looks like NOT a single config-register bug. Remaining candidates (none yet confirmed): the
uni→regport INPORT-tag conversion the CLA hash keys on (if port1's frames present the wrong inport, they
match the wrong/no CLA entry → no trap); a per-inport rule (ram1) trap match; or dynamic/silicon state.

## SA-security / source-MAC REFUTED (2026-06-02, live raw-frame tests via cap_net_raw)
With cap_net_raw/cap_net_admin on a system-python copy (the pyenv copy hung — setcap secure-mode ignores
PYTHONHOME), confirmed via tcpdump that raw ARP/frame injection works and frames reach the device MAC
(sent 40 from enx2c99→jack3, smac2 RX += exactly 40). Findings:
- Injected broadcast ARP and crafted ICMPv6 RS do NOT trap to CPU on ANY port (incl. working port2) —
  broadcast-flood is off and crafted frames don't match a CLA trap rule. So injected frames are not a
  usable CPU-trap probe; only the host OS's organic ND/MLD/mDNS traps (that's what drives rx_per_ingress).
- Decisive SA test: bounced port1's host NIC (link down/up) with the SAME MAC (control) and with a NEW
  MAC (02:de:ad:be:ef:01); after each, waited for OS IPv6 ND. **rx_per_ingress[port1] stayed 0 in both.**
  ⇒ NOT source-MAC/station-move/secure-learning; and a link-bounce re-init doesn't fix it either.
- Cumulative proof of the bug (MAC-independent): smac1 RX=821 (frames reach MAC1) vs rx_per_ingress
  port1=0 (none to CPU), while port2/3 = 1535/1537 to CPU for the same OS traffic type.

## NET (exhaustive) — port1 cause is NOT software-addressable config/classification
Ruled out on HW: all per-port config regs (identical + poke-refuted incl PP[0x8008], SPA 0x4064),
isolation/STP, MAC bring-up/d00d30, 0x19068, the entire CLA (inport-tag correct, ram1 rules + ram2
result + cpu_qid all match stock golden), and source-MAC/SA-security. port1 frames reach MAC1, pass
SPA+SDET, are NOT hw-trapped to CPU, and die at the OPC drop_PP — genuinely per-regport2, with every
readable input correct yet the trap verdict differs from working ports. Remaining (heavy, uncertain):
kotrace stock's RUNTIME trap classification for port1 vs mainline (the only way left to see what stock
does differently at runtime). Otherwise port1 is a deep isolated anomaly; driver is functional 3/4+hotplug.

## LOOP (2026-06-02) — systematic per-port ENABLE/gate sweep (user hypothesis)
Added a `peek` (read-only, 1-arg) path to the `poke` debugfs → can read ANY mainline reg via REPL.
Swept all per-port-indexed registers (from zx-fpga-reg-tables.h stride>0) for port1 vs port2 on mainline:
- SOPC 0x19004(crc_pad)/0x19038/0x19068 = all 0; UOPC tcont 0x18000/04 single; SMCT 0x10000=0xb/04=0xa;
  SIPC 0xc000=0x11; SPA enty_pktdeal 0x4300/14/28 = 0x55555555 (p0==p1==p2); SDET 0x71002/3/0x71080 = 0.
  → all identical port1-vs-port2 or global.
- ONLY genuine per-port asymmetry found: **SPA port_vlan_filter (0x921d42ac + port*4, [5:0])**:
  port0=0x36 port1=**0x26** port2=0x36 port3=0x27 port4=0x36. port1's 0x26 is unique among active ports.
- **REFUTED by live poke:** set port1's filter to 0x36 (port2's working val) AND 0x27 (port3's working
  val) — readback-confirmed, frames reach MAC1 (smac1 RX +13) — port1 STILL rx_per_ingress=0. So
  port_vlan_filter is NOT the gate (likely a HW reset default; mainline doesn't init SPA fully).
⇒ The user's per-port-enable hypothesis is REFUTED: no per-port-asymmetric static register gates port1
(the only asymmetric one, port_vlan_filter, doesn't change the verdict). Combined with all prior:
port1's trap-to-CPU miss is NOT explained by any static per-port register.
Bench note: a NIC down/up bounce drops enxc8a362's 192.168.1.0/24 subnet route (noprefixroute) → TFTP
boot fails (reply routes via WiFi); fix = re-add route (did via raw netlink RTM_NEWROUTE, cap_net_admin).

## ★★★ SOLVED (2026-06-02) — port1 gate = SPA port_vlan_filter
The loop's systematic per-port sweep + stock-golden comparison FOUND IT:
- **SPA `port_vlan_filter` (0x921d42ac + port*4, [5:0], x10 table).** STOCK clears all to 0; MAINLINE
  left it at a non-zero reset default (p0=0x36 p1=0x26 p2=0x36 p3=0x27 p4=0x36 — never inited the SPA
  fully). That non-zero per-port VLAN filter GATES port1's ingress→CPU trap.
- LIVE-CONFIRMED: poke all pvf entries to 0 (stock value) → port1 rx_per_ingress climbs 0→18 with port1
  traffic; revert to non-zero → port1 drops again. (Poking ONLY port1's entry didn't suffice — needs the
  whole table = 0, a cross-port effect of the filter.) NOT SMCT (isolated: port1 works w/ SMCT=mainline 0xa).
- FIX: `zx_pm_spa_init` now clears port_vlan_filter x10 to 0 (`npp_write(e, 0x142ac + i*4, 0)`), matching
  stock. After rebuild+boot, port1 frames (src c8:a3:62, jack2) reach CPU with NO poke — BPDUMP/TM RX
  confirm. **The long-standing port1 ingress→CPU bug is fixed.**

## FOLLOW-ON crash (fixed) — zx_tm_napi_poll bad bppe_idx deref
Opening port1's ingress exposed a latent RX-path bug: NAPI processed stale/garbage descriptors with
out-of-range bppe_idx (seen: bppe=2927..4975 vs pool size 1024) → bp_buf = bp_cpu + bppe_idx*2304 points
~11MB past the 2.3MB bp pool → deref crash (kernel panic at zx_tm_napi_poll+0x158). The len-only validity
check passed garbage (len=5..9). FIX: added `bppe_idx < TM_BPPE_POOL_SIZE` to the bp_buf-deref guard so
out-of-range descs are invalidated+acked+skipped (no deref). 

## ✅ FINAL VERIFICATION (2026-06-02) — port1 STABLE, no crash
Clean boot, both fixes in driver, NO pokes. Sustained port1 traffic (3× 30 pings via jack2):
rx_per_ingress[port1] climbed 11→37→55→94, REPL alive all rounds (no panic). port1 ingress→CPU WORKS
and is STABLE under load. The multi-session port1 saga is CLOSED. Remaining = tuning (full bidirectional
ping / egress to port1, bench route hygiene, remove debug instrumentation, OpenWrt integration).

---

## ✅✅ FINAL HW VERIFICATION on a CLEAN BOOT (2026-06-03) + new load-wedge finding

RAM-booted mainline with BOTH fixes (port_vlan_filter clear + bppe bound-check).
Boot was clean — REPL ready, **no panic**, DSA tree setup, live `ingress=1 ... delivered`.

DSA note: the C-init puts `192.168.1.99/24` on the **conduit `sw`**, and `lan0..lan3`
come up **DOWN**. For a port to ping you must `ip link set lanN up` and move the IP to
the user port (frames trapped to a down user-port netdev are dropped). After
`ip link set lan1 up` + IP on `lan1`:

- **Bidirectional ping on port1/jack2: 8/8, 0% loss** (ARP + ICMP round-trip on the wire,
  confirmed by host tcpdump). The port1 gate fix is **fully verified end-to-end**.
- Sustained 90 pings earlier: 90/90 0% loss; a 100MB ingress blast climbed rx_per_ingress
  port1 by +424 with `tm_bmu_free_fail=0` and **no crash** — the fix is stable under load
  for the *ingress-count* path.

### ⚠️ NEW SEPARATE BUG (not the gate fix) — unicast→CPU RED-wedge under load / relink

Two independent triggers put port1 into a state where **light + bulk unicast→CPU stops
working while broadcast still works**:
1. A **cable disconnect/reconnect** (PHY link DOWN→UP pulses the MAC port-reset, dmesg:
   `PHY[1] link DOWN ... MAC[1].ctrl=0xba6000 (port-reset bit 7 pulsed)`).
2. A **heavy bulk TCP blast** (50MB nc) — after ~1000 packets the path wedges.

Per-stage localization (5 ICMP unicast sent, post-wedge), repeatable:
- `smac1 good_uc` +5 (frames arrive CLEAN at MAC1, crc=0) ✅
- `QMG UP hw_trap` **+1** (almost none trapped to CPU)
- **`RED[0x1a044]` +5** ← the 5 unicast frames die at RED
- `tm_tx_count` +1 (kernel never sees them → no reply) → host ping 100% loss

So the unicast-to-CPU frames are routed into a CPU queue that **RED drops persistently**
(broadcast/flood-to-CPU uses a different queue and keeps working — that's why ARP resolves
but ICMP doesn't). The `port_vlan_filter` gate is NOT involved (verified still =0 across
the whole table via peek after the wedge). RX is not hard-wedged (tm_rx still climbs,
bmu_free_credit fluctuates 5..33) — it's specifically the unicast-trap CPU queue that RED
is dropping.

**Consequence**: bulk TCP throughput is currently unobtainable — the bulk transfer itself
triggers the wedge (~1000 pkts in, then RED drops the rest → TCP collapses to ~kbit/s).
A clean boot restores it; the next disturbance re-wedges it.

**Root-cause hypothesis (for the next iteration)**: the QMG CPU-trap queue used by the
unicast-DA-hit path has a RED threshold / average-occupancy that saturates under burst and
does not decay/drain (per-queue NAPI servicing or RED EWMA stuck). The boot-time QMG/RED
init sets it correctly; neither the link-up handler nor steady-state recovers it. NEXT:
map the QMG per-queue + RED threshold regs, peek the unicast-trap queue's occupancy/RED
config pre- vs post-wedge, and either (a) re-apply RED/queue init on link-up, or (b) fix
the per-queue drain so the trap queue doesn't saturate. This is a robustness/QoS bug,
distinct from the (solved + merged) port1 ingress gate.
