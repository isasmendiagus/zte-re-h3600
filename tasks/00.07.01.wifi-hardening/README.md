# wifi-hardening — WiFi regression test battery + hardening

**ID**: 00.07.01
**Parent**: [00.07 wifi](../00.07.wifi/)
**Children**: none
**Status**: 🔧 PLANNED — research done, implementation pending

## Scope

Build a comprehensive WiFi regression test battery integrated into the existing
`regress.py` framework (`--wifi` flag). Covers:

### Tier 1 — Traffic-free white-box guards (0 device dependency beyond REPL)
- wifi_bind smoke/unbind/rebind/invalid/overflow
- PM write verify with fabric key_hdr
- Counter sanity (wifi_bind, stats, ftwifi nodes present)
- dmesg clean scan
- ftwifi default=1 check

### Tier 2 — Module lifecycle (needs .ko files staged in initramfs)
- Module chain load/unload/reload (pcie → cfg80211 → mac80211 → mt76 → connac-lib → mt7915e)

### Tier 3 — AP lifecycle (needs hostapd + udhcpd, no client traffic)
- hostapd restart under active bind
- Bind before client association (EAPOL guard)

### Tier 4 — Full integration (needs AP + adb phone + real WiFi traffic)
- DN throughput + HW offload verification
- UP throughput + HW offload verification
- Client disconnect/reconnect
- ftwifi toggle mid-flow
- Concurrent WiFi + Eth flows
- Flow install/destroy churn
- Wedge cold-start guard (2000+ injected frames)
- RED credit leak check on fabric ingress
- SIPC FIFO health

### Infra
- Create `lib/wifi_rig.py` — factor out repeated WiFi bring-up logic from
  wifi_up.py, wifi_ab.py, upab.py, wedge_probe.py, wedge_coldstart.py
- Add `--wifi` flag to `regress.py`
- New counter addresses in `ab_ctrs.py`

## Plan

See `research/hardening_plan.md` for the full 23-test plan, integration
architecture, and counter infrastructure. Based on agent research 2026-08-01.
