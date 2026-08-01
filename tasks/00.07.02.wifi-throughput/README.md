# wifi-throughput — WiFi throughput tuning (11ac/11ax, debug strip)

**ID**: 00.07.02
**Parent**: [00.07 wifi](../00.07.wifi/)
**Children**: none
**Status**: 🔧 PLANNED — research done, implementation pending

## Scope

### Phase 1 — Enable 11ac (VHT) in hostapd
- Add `ieee80211ac=1`, `vht_oper_chwidth=1`, `vht_capab` to `wifi_up.py` HOSTAPD_CONF
- Expected: 3-5x throughput improvement on Samsung A5 (2016/2017) — from ~40-80 Mbps to ~180-320 Mbps TCP

### Phase 2 — Enable 11ax (HE) in hostapd
- Add `ieee80211ax=1`, `he_*` options to HOSTAPD_CONF
- Requires 11ax-capable client (Samsung A5 max is 11ac)
- Expected: 8-12x over 11n with modern client

### Phase 3 — Strip debug hooks
- Comment out BPDUMP (zx-eth-main.c:5556-5566) — per-packet hexdump in NAPI hot path
- Comment out phaseC/idm-rx hex dump (lines 1880-1888)
- Downgrade NOPARSE fabric to `dev_dbg` (line 5425)
- Add `zx_debug_verbose` knob for init milestone noise
- Gate TM RX deliver `dev_info` with counter

### Phase 4 — Tuning knobs
- `implicit_txbf` debugfs for stationary clients
- `sr_scene_detect=1` module parameter
- Monitor `muru_stats`, `tx_stats` for PPDU distribution
- Rate control is HW-managed (mt7915 firmware) — only intervene if stuck

### Client constraints
- Samsung Galaxy A5 (2015): 11n only (150 Mbps max PHY)
- Samsung Galaxy A5 (2016/2017): 11ac (433 Mbps VHT 80MHz 1SS)
- Neither supports 11ax — need modern phone/laptop for HE testing

## Plan

See `research/throughput_plan.md` for full analysis. Based on agent research 2026-08-01.
