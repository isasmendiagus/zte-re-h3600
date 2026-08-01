# WiFi Hardening + Regression Test Battery — Plan (2026-08-01)

## Architecture

### Infra: `lib/wifi_rig.py`
Factor out repeated WiFi bring-up from wifi_up.py, wifi_ab.py, upab.py, wedge_probe.py, wedge_coldstart.py:
- `ensure_up()` — idempotent WiFi AP bring-up
- `ensure_down()` — teardown
- `assoc_check()` — is adb phone associated?
- `flow_dn/up()` — start traffic flows from phone
- `read_counters/stats/wifi_bind()` — one-shot counter reads

### Integration: `regress.py --wifi`
Add --wifi flag that runs wifi_up.py before the battery, then adds WiFi tests to ORDER.

## Test Battery (23 tests, 4 tiers)

### Tier 1 — Traffic-free (9 tests)
- wifi_bind_smoke: bind wlan1→idm1/ssid4 succeeds
- wifi_unbind: clean unbind
- wifi_rebind: rebind after unbind
- wifi_bind_invalid: nonexistent iface → -ENODEV
- wifi_bind_overflow: >16 nodes → graceful fail
- wifi_tx_injected_sanity: tx_injected >= 0
- wifi_default_ftwifi_1: ftwifi reads 1 by default
- wifi_counters_sanity: all WiFi debugfs nodes present
- wifi_pm_write_verify: PM verify with key_hdr=0x38

### Tier 2 — Module lifecycle (3 tests)
- wifi_modprobe_chain: load pcie→cfg80211→mac80211→mt76→connac→mt7915e
- wifi_modprobe_rmmod: unload reverse order
- wifi_modprobe_reload: full cycle load→unload→load

### Tier 3 — AP lifecycle (2 tests)
- wifi_hostapd_restart: kill+restart under active bind, no wedge
- wifi_bind_before_assoc: bind before EAPOL, client still connects

### Tier 4 — Traffic integration (9 tests)
- wifi_dn_throughput_hw: DN offload verification (qmg_dn_hw climbs)
- wifi_up_throughput_hw: UP offload verification (qmg_up_hw climbs)
- wifi_client_disconnect: disconnect/reconnect, idm_rx_count keeps climbing
- wifi_ftwifi_toggle: ftwifi 1→0→1 mid-flow
- wifi_flow_install_destroy: fttest fabric install→clapeek→destroy→clapeek
- wifi_flow_churn: N short flows, clean install/destroy
- wifi_eth_concurrent: simultaneous WiFi UP + Eth DN
- wifi_coldstart_guard: 2000+ injected frames without freeze
- wifi_dmesg_clean_after: no oops/WARN in dmesg

## Counter addresses to add to ab_ctrs.py
- cla_up_fwd (0x9238c3c0), cla_acl_fail (0x9238c3c4)
- IDM TX_STATUS (0x921c8044)
- SIPC gauges: 0x921cc004, 0x921cc008, 0x921cc018, 0x921cc01c, 0x921cc020
