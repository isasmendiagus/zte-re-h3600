# WiFi Throughput Tuning — Plan (2026-08-01)

## Current state
- hostapd config: only `ieee80211n=1` — no 11ac/11ax
- Client Samsung A5 links at 11n (~40-80 Mbps TCP)
- BPDUMP debug hook floods UART (every packet < 20th dumps 48 hex bytes)

## Phase 1 — Enable 11ac (VHT)
Add to wifi_up.py HOSTAPD_CONF:
```
ieee80211ac=1
vht_oper_chwidth=1
vht_capab=[MAX-MPDU-7991][SHORT-GI-80][TX-STBC-2BY1][RX-STBC-1][MAX-A-MPDU-LEN-EXP7][SU-BEAMFORMER][SU-BEAMFORMEE]
```
Expected: A5 (2016/2017) goes from 11n to VHT 80MHz MCS9 1SS → 433 Mbps PHY, ~180-320 Mbps TCP (3-5x improvement).

## Phase 2 — Enable 11ax (HE)
Add to hostapd conf: `ieee80211ax=1`, `he_oper_chwidth=1`, `he_su_beamformer=1`, `he_su_beamformee=1`, `he_mu_beamformer=1`, `he_bss_color=1`.
Requires 11ax-capable client (modern phone/laptop with AX200+). Expected 8-12x over 11n.

## Phase 3 — Strip debug hooks
- Comment out BPDUMP block (zx-eth-main.c:5556-5566) — per-packet hexdump in NAPI
- Comment out phaseC/idm-rx hex dump (lines 1880-1888)
- Downgrade NOPARSE fabric to dev_dbg (line 5425)
- Gate TM RX deliver with counter

## Phase 4 — Tuning knobs
- `echo 1 > /sys/kernel/debug/ieee80211/phy1/mt76/implicit_txbf` for stationary clients
- `insmod mt7915e.ko sr_scene_detect=1`
- Monitor muru_stats, tx_stats for PPDU distribution
- Rate control is HW-managed (mt7915 firmware) — only intervene if stuck

## Client constraints
- Samsung A5 (2015): 11n only (150 Mbps max)
- Samsung A5 (2016/2017): 11ac (433 Mbps VHT 80MHz 1SS)  
- Neither supports 11ax
