# WiFi HW-offload (Stage 3) — consolidated PLAN + open questions (to resume later)

Status as of 2026-07-07. This is the pick-up-later roadmap for making WAN⇄WiFi
traffic ride the switch's HW-forwarding path (CLA/PM offload to fabric ports 6/7),
instead of the current CPU SW-forwarding baseline. Nothing here is urgent — the
SW path already works end-to-end (see below). This file exists so the effort can
be resumed cold without re-deriving context.

---

## 0. TL;DR — is this the same as the ethernet offload?

**Yes — it's the SAME shared core, not a parallel engine.** The switch fabric has
ONE classification/forwarding pipeline — **CLA (classifier) + PM (HW-NAT) + FDB +
QMG/RED (queues)** — that serves *all* ports: LAN (0-4), WAN/PON (5), **and WiFi
(6/7)**. Proof: the pipeline's internal descriptor already carries `4-bit port +
3-bit ssid + ssid_flag`. A WAN→WiFi flow is a CLA/PM flow just like WAN→LAN, only
egressing to outport 6/7 + ssid. **We are NOT building a second offload engine —
we reuse the CLA/PM machinery already cracked for ethernet.**

What is genuinely new (the "edges", not the core):
1. **Transport:** eth uses MAC ports + the DSA conduit (`sw`); WiFi uses fabric
   ports 6/7 + the **IDM DMA ring** (`idm0`/`idm1` netdevs, already driven by
   mainline). Different DMA path, same CLA/PM downstream.
2. **The `ssid` dimension** — eth ports have no ssid; WiFi does, and it is NOT
   stored in FDB or CLA entries (see §2). This is the real unknown.
3. **The `(idm,ssid)↔vif` dispatcher** (stock's `idmfdb.ko`) — no eth analog;
   the CPU shuttles each packet MT7915⇄IDM (no WED / zero-CPU path exists).

```
        [ MT7915 radio (PCIe, separate device) ]
                   │  (CPU shuttle, no WED)
   eth MACs ─ DSA conduit ─┐        ┌─ IDM ring ─ fabric ports 6/7 (WiFi)
                           ▼        ▼
              ┌─────────────────────────────────┐
              │  CLA + PM + FDB + QMG/RED   ← THE SAME SHARED CORE
              └─────────────────────────────────┘
```

---

## 1. What is already DONE and committed (branch phase6-hw-offload, not pushed)

- `61c98d860` — Stage-3 gap analysis of the mainline IDM code (what mainline lacks
  vs stock's ssid path). See `findings/wifi_ap_bringup_and_regdb_fix_2026-07-07.md`
  §"Stage-3 gap analysis".
- `0b9e37cb0` — **ssid encoding spec** (`findings/wifi_stage3_ssid_encoding_spec_2026-07-07.md`):
  bit-exact IDM descriptor layout + the internal pipeline descriptor ssid bits;
  the proven finding that **neither FDB nor CLA stores an ssid field**; the full
  `idmfdb.ko` glue contract; 6 open questions (reproduced in §3 below).
- `1478beecf` — **Phase 1 (device):** port-6/7 isolation polarity SETTLED
  (`PP_BRG_ISOLATE` is an ALLOW-mask; live `PP[0x83c0..dc]=fe fd fb f7 ef df ff ff`
  → ports 6/7 = 0xff = already fully OPEN, feasibility note was polarity-inverted →
  **no mask change needed**); additive IDM RX-ssid decode landed + verified live
  (`idm_rx_count`/`idm_rx_per_ssid[8]` in debugfs, `ssid=word1[18:16]`,
  `valid=word1[19]`). Observation: with AP up + 6/7 open, `idm_rx_count = 0` — the
  IDM ring receives nothing because no FDB/CLA/greg plumbing steers fabric traffic
  to 6/7, and mainline WiFi RX never touches the IDM ring.

**Also already working (the baseline this builds on):** H3600 as a real WiFi AP
(hostapd on wlan1, WPA2, real Android client assoc + DHCP) reaching the internet
through the H3600 via **SW** route+NAT — proven by conntrack. See
`findings/wifi_ap_bringup_and_regdb_fix_2026-07-07.md`. HW offload only improves
CPU/throughput under load; it is NOT a correctness gap.

---

## 2. Key architectural findings that shape the plan (from the ssid spec)

- **IDM descriptor (confirmed bit-exact):** RX `byte6[2:0]=ssid`, `byte6 bit3=ssid_valid`,
  `byte7 bit7=idm-ring`; invalid→sentinel `0xff` at `skb->cb[0xb7]`. TX
  `word1 = len | idm_ring<<31 | ssid<<28`, ssid read from `skb->cb[0xb7]`.
- **FDB has NO ssid field** — port is a plain bitmap (WiFi = 1 bit each for port
  6/7). The FDB alone can never disambiguate which SSID a client is on → ssid
  resolution must live in the dispatcher, not the FDB.
- **CLA hardfast entry has NO `ssid_out` field** either. Well-grounded but
  UNCONFIRMED hypothesis: stock folds ssid into the CLA 5-bit `outport` value via a
  logical-port scheme (`get_sw_port_from_devname`: port6 = `0x10+ssid`,
  port7 = `0x18+ssid`). Must be bench-confirmed before trusting in a real flow
  install (wrong outport misroutes a real flow).
- **PM flow_info/next_hop carries no outport/ssid** — egress port/ssid is purely a
  CLA-side concern.
- **`idmfdb.ko` glue mapped:** `idm_fdb_forward` (RX dispatch, node index =
  `ssid+idm*8`), `register_idm_fdb_node` (vif registration), TX injection writes
  `skb[0xb7]`; `idm_fdb_hook_xmit` is a pure SW MAC-learning tap (not ring injection).

---

## 3. PHASE A — the open questions (do NOT guess past these)

These are the highest-risk, highest-leverage unknowns. Almost all Stage-3 risk is
concentrated here. Resolve them (RE + a couple of read-only on-device probes)
BEFORE writing any HW-programming code — a wrong bit position misprograms silicon.

1. Whether HW-autonomous FDB-A learn writes ssid into the unaccounted
   reg-`0x4e` bits[31:10].
2. Whether `ssid_out` on a plain DA/FDB hit is VLAN-derived, HW-side-only, or simply
   never populated for non-CLA-flow WiFi traffic (three hypotheses, none confirmed).
3. Whether CLA's stored `outport` (5 bits) is ever written with the 0x10-0x1f
   logical-port value for a real WiFi hardfast flow, or whether stock never builds
   such a flow at all.
4. `WlanIndex2WlanIdmMap` / `IfName2WlanIdmMap` internals — exporting module not in
   the decomp set on disk.
5. Exact writer of `fdb_list[node].idm` / `.ssid` byte fields inside
   `register_idm_fdb_node` — read in 3 places, write site not located in the
   provided idmfdb.c decomp.
6. `ffe_learn_skb` / `ffe_get_npu_enable` internals — vmlinux-builtin, not in any
   .ko decomp provided.

**The single safest, cheapest first concrete step (read-only, no code change):**
after a real AP+STA association, do a raw read of a HW-learned WLAN client's FDB-A
entry (via existing debugfs `clapeek`/`fdbadd`/`pmpeek`) and inspect the
unaccounted FDB-A reg-`0x4e` bits[31:10] — this settles open questions (1)/(2)/(3)
empirically. May also need stock-live correlation (boot stock, learn a WiFi client,
dump the same structures) if the mainline read is ambiguous.

---

## 4. Phased plan + effort (honest, RE-work resists precise estimation)

- **Phase A — resolve the ssid encoding (§3).** HIGHEST RISK. Device-free decomp RE
  + a short on-device confirmation tail (read-only probes; NOT fully device-free).
  Good case: ~1-2 focused sessions. Bad case (mechanism obscure / needs stock
  live-trace): can balloon. **Do this first and alone — it tells us if we're in the
  good or bad case before committing to the rest.**
- **Phase B — IDM plumbing:** RX ssid decode→dispatch, TX ssid stamp, greg IDM-RX
  enable if needed, and the `(idm,ssid)↔vif` dispatcher (idmfdb equivalent).
  Moderate, bounded once A is known. Driver code + live iteration.
- **Phase C — extend CLA/PM flow-offload to emit outport 6/7 + ssid.** Heavily
  reuses the eth DN offload path; relatively fast, but gated on A.
- **Phase D — integration + validation + hardening:** WAN→WiFi DN NAT rides HW,
  verify with a real client, measure hit-rate/CPU, regress tests, handle MT7915
  MCU stability.

**Overall estimate (dominated by Phase A):** good case ~1-2 weeks of focused
sessions; realistic a few weeks; bad case up to a couple of months. Calibration
anchor: the ethernet offload — the *same full flow* — was the longest, hardest arc
of the whole project (weeks, many dead-ends). WiFi should be SHORTER because the
core (CLA/PM/hash/FDB) + tooling already exist, but it adds the new ssid RE front.

---

## 5. Model / cost policy for this work (user directive 2026-07-07)

- Default model for spawned agents is now **Sonnet 5** (not Fable 5). See
  memory `model-policy-fable-default` REFINEMENT 4.
- **Do NOT put the Phase-A RE reasoning on Haiku** — it's the deepest, highest-stakes
  RE of the project (wrong bit positions misprogram silicon; need honest
  hypothesis-vs-fact discipline, which the Sonnet-5 spec pass did well). Haiku is
  fine for MECHANICAL retrieval sub-tasks only.
- **Cost-saving hybrid option:** Haiku for grunt retrieval (grep/extract/list all
  refs to ssid/idm/0x10/0xb7 with line numbers, dump structs) feeding a **Sonnet 5**
  synthesizer that does the correlation/hypothesis. Keeps the judgment on the strong
  model while the cheap one does the acarreo.

---

## 6. Rig gotchas relevant to resuming (learned the hard way this session)

- Boot scripts report `BOOT_FAIL` even when the device DOES reach the REPL (marker-
  detection bug) and, worse, will restart a good boot. Reliable recipe = drive
  U-Boot manually (tftp + `setenv bootargs` + `bootm`); don't let a script re-reset.
- A bare DTR pulse WITHOUT interrupting `cspstart` boots **STOCK from NAND**.
- WiFi boot args: `pci=nomsi pcie_aspm=off` at the FRONT (U-Boot corrupts the last
  arg; MSI never delivers MT7915 IRQs). Do NOT use `cma=16M@0x4e800000` — it now
  lands inside the eth-carved reserved region and SIGSEGVs all userspace.
- cfg80211/mt76 are `=m`; a config change needs `make modules`, not just `make zImage`.
- Ports 6/7 are already OPEN (no isolation change needed) — §1 `1478beecf`.
- Host cable is on **lan2 (MAC2, the TFTP jack)**, not lan4.
- UART REPL echoes everything — never send the owner's real WPA PSK through it (use
  a throwaway test passphrase for the AP; SSID must NOT be `Dino-WiFi-5GHz`).

---

## 7. Cross-references

- `findings/wifi_stage3_ssid_encoding_spec_2026-07-07.md` — the bit-exact spec + source-cite index.
- `findings/wifi_stage3_phase1_2026-07-07.md` — Phase 1 device results.
- `findings/wifi_ap_bringup_and_regdb_fix_2026-07-07.md` — AP bring-up + regdb fix + gap analysis.
- `findings/wifi_offload_feasibility_2026-07-04.md` — original IDM feasibility scout (note: its
  "isolates 6/7 with 0xFF" and "CLA hardfast carries ssid_out" claims are both CORRECTED above).
- Memory: `zte-wifi-state`, `zte-roadmap`, `model-policy-fable-default`.
