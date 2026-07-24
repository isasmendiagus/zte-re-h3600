# WiFi Stage-3 Phase B.2 — TM trap-RX → vif dispatch, implemented + ON-DEVICE VALIDATED (2026-07-24)

Same-day follow-up to `findings/wifi_stage3_fixA_ondevice_validation_2026-07-07.md`
(fix A delivers port-6/7 ring-ingress traps to the CPU on TM q4 ring0, but the
frames died in DSA demux with fabric ingress identity raw=24, and the IDM RX
ring — where the Phase-B dispatcher listened — never sees traps). Phase B.2
closes exactly that gap. Kernel **#524**, RAM-boot, validated live.

## What was added (zx-eth-main.c)

1. **`zx_wifi_tm_rx_dispatch()`** — in the TM NAPI RX delivery chain, frames
   whose descriptor ingress identity is fabric/IDM (`desc[6]` raw port ≥ 0x10)
   are decoded as `raw = 0x10 | idm<<3 | ssid`, looked up in the existing
   Phase-B dispatch table (`node = ssid + idm*8`), and — when a bound, UP vif
   exists — copied into a fresh skb and delivered to the local stack **as vif
   RX** (`eth_type_trans(vif)` + `netif_rx`), mirroring stock's
   wlan→idm→fabric→trap→CPU slow path. Unbound/alloc-fail falls through to
   the pre-B.2 baseline (sw delivery → DSA demux drop). New counters:
   `tm_rx_fabric` / `tm_wifi_rx_dispatched` / `tm_wifi_rx_nobind` (in `stats`
   and `wifi_bind`); first-8 diag print dumps raw/idm/ssid/len/MACs/ethertype.
2. **Loop guard**: dispatched skbs carry a `SHUTTLED` cb marker (0xa5 at
   cb[40]); `zx_wifi_rx_handler` passes marked frames to the stack instead of
   re-injecting (would otherwise loop vif→ring→trap→vif forever).
3. **EAPOL passthrough** in `zx_wifi_rx_handler` (`ETH_P_PAE` →
   RX_HANDLER_PASS) — the Phase-B live-discovered handshake-eater fixed.
   Code-inspected only (no STA this session).

## Live results (#524)

| Step | Result |
|---|---|
| Unbound burst (6 ARPs via idm1) | `tm_rx_fabric=15, nobind=15, dispatched=0` — recognized, baseline preserved (inert by default) |
| Diag decode | `raw=0x18 (idm1 ssid0)` for idm1 frames — **encoding hypothesis `0x10\|idm<<3\|ssid` CONFIRMED** for idm1; src/dst/ethertype all correct |
| Bind `lan2 1 0`, burst 8 ARPs | **`tm_wifi_rx_dispatched` 0 → 6** — trap-path frames handed to the bound vif's stack |
| Loop check (25 s at rest) | `tm_rx_fabric` FROZEN (23→23); `tx_injected` moves only with host background; **no loop** |
| idm0 (bind `lan1 0 0`, 6 ARPs) | dispatched +8 / fabric +15 — idm0 decodes to node (0,0) → **idm0 raw = 0x10** (inferred via successful dispatch; nobind +7 = idm0's link-up ND arriving before the bind) |
| dmesg | **zero WARN/BUG/Oops** across all new paths |

## What this unlocks / next

- The Phase-B RX story is now complete for the slow path: vif → ring → fabric
  → trap (fix A) → TM q4 → **dispatch back to the vif's stack (B.2)**. With a
  real AP + STA, upstream client traffic can now traverse the fabric and still
  be routed by the CPU — giving the HW FDB visibility of client MACs on ports
  6/7+ssid (stock's premise for DN offload steering).
- OTA test with hostapd + a real STA (incl. EAPOL passthrough under fire) is
  the natural next validation; then Phase C (CLA flows with
  `gemport_uni_id = 0x10|(ring<<3)|ssid` → hw-forward egress → IDM RX ring →
  the existing `idm_wifi_rx_dispatched` ndo_start_xmit path).
- ssid≠0 raw encoding (bits 0..2) still only hypothesis-confirmed at ssid=0;
  first ssid-tagged unknown-SA traffic will confirm via the diag print.

## Honesty

- RAN ON HW: everything in the table above.
- NOT run: EAPOL passthrough under a real handshake (no STA); ssid≠0 decode;
  mac80211 vif as dispatch target (lan1/lan2 used as stand-in vifs — the
  dispatch path is netdev-agnostic by design, same as Phase-B TX was).
- Pre-existing observation (out of scope, not touched): the TM RX
  invalid-ingress and loopback-suppression branches appear to free the BP
  twice (branch-local `zx_bmu_free_bp` + the common one at the end of the
  len>0 block). Stable in practice; worth a dedicated look.
