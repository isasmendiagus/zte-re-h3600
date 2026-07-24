# WiFi Stage-3 fix "A" (CLA ram7 dual-bank trap-steer) — on-device validation (2026-07-24)

Live H3600 (ZX279128S), mainline 6.6 RAM-boot, kernel **#522** (commit 607dfa783,
built 18:32 UTC, TFTP-booted via manual one-shot U-Boot drive — no retry loop).
Validates fix A.1 (base-bank qid1 replay) + A.2 (q5→q4 re-steer, all banks) from
`findings/wifi_stage3_qmg_queue5_consumer_re_2026-07-07.md` against the Phase-B
baseline (`findings/wifi_stage3_phaseB_ondevice_validation_2026-07-07.md`:
TX-inject works, RX delivery dead in TM DN queue 5).

## TL;DR VERDICT

**Fix (A) DELIVERS port-6/7 ring-ingress traps to the CPU — the Phase-B
black-hole is GONE.** But the delivery arrives on the **TM CPU rings (q4,
ring 0)**, NOT the IDM RX ring: `idm_rx_count` / `idm_wifi_rx_dispatched`
**remain 0**, and empirically CANNOT move from trap delivery — this confirms
the RE's §5 "non-fix" note on hardware (the IDM RX ring is a hw-forward egress
target only; Phase-C feeds it). So:

| Claim | Verdict on HW |
|---|---|
| A.1 replay runs & sticks (base bank ≠ blanket 7) | **YES** — boot log `trap_queue replay: 656 ok, 0 fail (82 entries x 8 banks incl. base/dir-1; 32 q5->q4 WiFi re-steers)`; `cladump` base column live, ARP row `0x11 = 04` in all 8 banks |
| Port-7 (idm1) ring-ingress ARP trap delivered to CPU | **YES** — +21/21, +6..8 per burst, tracked frame-exact by a background-immune oracle (below) |
| Port-6 (idm0) same | **YES** — +8/8 |
| Delivery queue | **TM q4 ring 0** (`rx_head[4]` tracks bursts; q5 status stays 0x0) |
| `idm_rx_count` moves | **NO — 0 throughout** (traps ride TM rings; architectural, not a bug in fix A) |
| Phase-B RX dispatch (`idm_wifi_rx_dispatched`) fires | **NO** — nothing arrives on the IDM ring; ALSO the TM-RX path has no plumbing to the dispatcher (next work item, below) |
| q5 still "dead" on #522 | **NO — q5 DELIVERS when selected** (bank-walk bursts rode q5 healthily, `rx_head[5]` 0→24). The #520 pathology did not reproduce; A.2 is defense-in-depth on this build |

## How it was measured (the delivery oracle)

White-box per Phase-B: `wifi_bind` lan2→(idm1,ssid5) proved TX-inject again
(`tx_injected` 0→14→26…→305, every host frame tagged+injected). But the key
bursts used **device-sourced ARPs** (IP on idm1/idm0, `ping` unresolvable
neighbors → ARP broadcasts into the ring) because of a discovered confound
(§ host-SA below). Delivery counting trick: set idm1's MAC = sw's MAC → every
delivered ring frame hits the driver's loopback-suppression branch, whose
counter `tm_rx_loopback_drops` has **zero background** (it sat at 1 for hours)
— frame-exact attribution immune to the heavy port-4/WAN wire noise:

| Burst (device ARPs via ring) | tm_rx_loopback_drops | rx_head[4] (q4 ring0) | rx_head[5] |
|---|---|---|---|
| 15 ARPs, ARP rows = 4 (fix state) | 1 → 22 (+21 incl. idm1 IPv6 ND) | tracks | 0 |
| 20 ARPs, fix state | sw stats +≈20 excess | 264→283 (+19) | 0 |
| 8 ARPs × 3 probes, row 0x391=5 (walk) | +6 each | ~flat | 0→18 (+6 each) |
| 8 ARPs, rows restored = 4 | 68→74 (+6) | 386→393 | frozen 24 |
| 8 ARPs from **idm0** (port 6), fix state | 81→89 (+8) | 404→413 | frozen |

dmesg corroboration: `LOOPBACK drop #2..#5 src=<sw MAC> dst=33:33:… ethertype=86dd
… ingress=23` — ring-injected frames arriving at the CPU RX path. Note
**ingress=23** (desc[6] raw port = 24): the RX descriptor does NOT carry
fabric inport 6/7 for ring-ingress frames; they land in `rx_per_ingress`
hidden slots ≥8 (the stats line prints only 0..7 — that hid the delivery at
first). Post-delivery the frames die in DSA demux (tag port 23 has no
netdev) — counted in `sw` rx stats + tm_rx_count, zero warnings, no crash.

## Direction + QMG accounting (RE §6 check #3 — resolved)

- SPA→SADM window (0x921d45ec..) during bursts: our frames read
  `inport=7 ssid=5` with **dir=0, act=0, rsn=0x49** (background wire/CPU traps
  read dir=1 act=1 rsn=0x4a/0x4b, validating the decode).
- **QMG UP hw_trap 0x9234c060 counts the injected frames** (+13 for 12, +18 for
  14); `qmg_dn_trap` (0x9234c04c) does NOT (moves only with wire background);
  `qmg_up_sw/hw/trap @0x54/58/5c` all stay 0. → **IDM-ring-ingress traps are
  UP-direction**, exactly the RE §2.4 suspicion. Delivery advances
  `rx_head[]` = the driver's **ring-0 (UP)** cursor, consistent.
- Unexplained delta vs Phase-B: their ring-ARP SADM read `act=1(TRAP)
  rsn=0x11`; ours reads `act=0 rsn=0x49`. Same frame type, different build.
  Not chased further — delivery works and the queue steering demonstrably
  follows ram7 (bank walk below); flagged for the next SADM-decode pass.

## Bank walk (RE §6 check #2) — WHICH ram7 bank do ring frames consult? **ANSWERED: 0x391 (p7 bank, naive mapping)**

Method: set one candidate ARP row to qid5, burst 8 device ARPs, watch which
`rx_head[q]` advances (loopback oracle proves delivery either way):

| State (ARP row 0x11 family) | Frames rode |
|---|---|
| base=5, all per-port=4 | q4 → per-port value wins, base NOT consulted |
| 0x391=5 (others 4) | **q5** — `rx_head[5]` starts advancing |
| 0x311=5 too | q5 (0x391 already 5) |
| all 7 per-port=5, base=4 | q5 |
| all restored 4 | q4 |

→ A fabric-port-7 (idm1) ingress ARP consults **row `ptype|0x380` = 0x391**;
port numbering is NAIVE (no index-space shift). This settles the RE §7 open
question. Port-6 spot-check delivered identically (bank 0x311 by symmetry, not
individually re-walked).

**Why Phase-B's `clawrite 7 0x391` re-steer "failed": it never committed.**
Live-characterized clawrite/CLA-indirect-engine quirk (real, reproduced ~10×):
the **first write of a value does not commit — a second identical write does**
("write arms, next write commits"); interleaved reads can also return
one-op-stale values (a readback once showed a value from two writes earlier,
landing across addresses). Recipe that works: write → clapeek → if wrong,
write again (converges in ≤2 iterations, verified against double-clapeek +
cladump). The boot-time replay (656 back-to-back writes, no interleaved
reads) is unaffected — every boot value verified correct via cladump.

## The host-SA confound (new, matters for Phase-C test design)

Host-sourced frames (SA = host MAC, already FDB-learned on wire port 2)
injected via the ring are **PP-DROPPED** (`pp_drop` +16 ≈ burst of 14+2;
SADM act=0 rsn=0x49): the fabric treats them as a station-move/SA anomaly.
Device-sourced frames (unknown SA) deliver cleanly. So a `wifi_bind`-white-box
with host traffic exercises TX-inject but its RX-delivery outcome is
misleading — use ring-originated (or unknown-SA) frames for delivery tests.

## RE §6 checks scorecard

1. **Stock-q5 oracle: DEFERRED** (deliberate). Blocked/beside-the-point:
   (a) exercising stock q5 needs a WLAN STA — the owner's phone is PIN-locked
   / on another network, host wlo1 needs owner permission; a wire ARP rides
   the ram2 cpu_qid override (→q7) on stock too, so there's no cheap wire
   trigger; (b) its discriminating value collapsed — q5 DELIVERS on mainline
   #522, so "does stock q5 deliver" no longer gates the fix. Residual value is
   Track-B pairing semantics only.
2. **Re-steer oracle / bank walk: DONE** — consulted row = 0x391 (above).
3. **Direction A/B: DONE** — UP; 0x9234c060 is the counter that ticks.
4. **Descriptor hunt at byte-cursors: MOOT** — descriptors are demonstrably
   written and consumed (frames delivered end-to-end); no byte-pair wedge
   state exists on this build to hunt in (q4 and q5 statuses idle at 0x0).
5. **Credit-seed probe: SKIPPED** — q5 delivers unseeded on #522; poking the
   release doorbell would risk the healthy RED/release state for zero
   fix-validation value. Belongs to Track B if the wedge ever reproduces.

## Open questions (explicit)

- **What un-killed q5?** On #520 (pre-fix) q5 popped-to-nowhere with a byte-pair
  status tick; on #522 q5 delivers healthily (status stays 0, ring-0 cursor
  advances). Candidates: A.1's base-bank sanitization (blanket 7 → real qids);
  or the #520 deadness was accumulated boot/session state that a fresh boot
  never re-entered. Deciding requires re-booting a pre-fix build and
  re-injecting — do only if Track B needs it; the fix state doesn't depend on
  the answer (frames ride q4 anyway).
- Phase-B-vs-now SADM `act/rsn` delta (1/0x11 vs 0/0x49) for the same frame class.
- The ring-flip: Phase-B's dead tick lived in the hi16 (ring-1-paired) half of
  TM[0x10114]; today's delivery advances the ring-0 cursor. Ties into the
  hi16/lo16↔slice↔bit14 pairing (Track B, still unresolved — doc §7).

## What this means for Stage 3 (next steps)

1. **Phase B.2 (new, small): plumb TM-RX-delivered fabric-ingress frames to the
   WiFi dispatcher.** Delivered ring frames reach `zx_tm_napi_poll` with desc
   ingress raw=24 ("ingress 23") and currently die in DSA demux. Recognize the
   fabric/IDM ingress identity there (and decode the desc ssid bits if present
   — idm0-vs-idm1 raw values need one more probe) and hand the skb to
   `zx_wifi_dispatch[]` instead. With that + the EAPOL passthrough gotcha
   fixed, Phase-B RX (`idm_wifi_rx_dispatched`) can finally fire — from the
   slow path, without waiting for Phase C.
2. **Phase C unchanged**: CLA flow entries with `gemport_uni_id = 0x10|(ring<<3)|ssid`
   egress → IDM RX ring → the existing dispatcher RX path (its counters are
   correct as-designed for that path).
3. Track B (RX-poll pairing contract) deprioritized further: no live wedge to
   fix on #522.

## Hardware-run vs inferred (honesty)

- RAN ON HW: boot #522, cladump/clapeek reads, all bursts + counters above,
  bank walk with write-verify, SPA window samples, host tcpdump (no loopback
  egress on lan2 wire), pp_drop attribution, idm0+idm1 both directions probes,
  cleanup (unbind, MAC/link restore, ram7 = boot fix state — verified).
- NOT run: hostapd/AP + real STA this session (white-box equivalence
  established in Phase-B; RX-dispatch cannot fire regardless until Phase B.2
  exists, so an OTA test adds no information today). Stock boot (oracle #1)
  deferred with reasons above.
- INFERRED (not proven): which mechanism un-killed q5 (open question above);
  idm0's consulted bank = 0x311 (symmetry; only delivery was verified).
