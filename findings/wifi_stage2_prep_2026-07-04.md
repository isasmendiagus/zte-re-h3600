# STAGE 2 (WiFi) prep — config audit, build proof, staged configs (2026-07-04)

Device-free prep for the MT7915 STA re-verify + first hostapd AP bring-up.
No device contact was made. Companion memory: `zte-wifi-state`,
`zte-wifi-credentials`.

## 1. Kernel config audit (live `build/.config`, branch `phase6-hw-offload`)

Verdict: **the running config was ALREADY fully STA-ready AND AP-ready
kernel-side.** Nothing had to be enabled. mac80211 has no separate "AP mode"
Kconfig gate — AP iftype ships with `CONFIG_MAC80211` + hostapd over nl80211.

| Symbol | State | STA needs | AP (hostapd) needs |
|---|---|---|---|
| `CONFIG_CFG80211` (nl80211) | m | yes | yes |
| `CONFIG_MAC80211` | m | yes | yes (AP iftype unconditional) |
| `CONFIG_MAC80211_RC_MINSTREL` | y | yes | yes (default RC) |
| `CONFIG_MT76_CORE` / `MT76_CONNAC_LIB` / `MT7915E` | m / m / m | yes | yes |
| `CONFIG_PCIE_ZX279128S` (our RC glue, `drivers/pci/controller/dwc/`) | m | yes | yes |
| `CONFIG_PCI` / `CONFIG_PCI_MSI` | y / y | yes (boot with `pci=nomsi`!) | same |
| `CONFIG_FW_LOADER` | y | yes (mt7915 fw + EEPROM) | yes |
| Crypto **builtin** (the May EAPOL-M3 gotcha): `CRYPTO_AES`, `CCM`, `GCM`, `CTR`, `CMAC`, `GHASH`, `HMAC`, `SHA256` | all **y** | yes | yes (CCMP; CMAC = PMF/11w) |
| `CONFIG_CRYPTO_LIB_ARC4` | y | yes (mac80211 won't load without) | yes |
| `CONFIG_BRIDGE` | y | — | yes (bridge wlan into LAN) |
| `CONFIG_DEBUG_FS` | y | nice (mt76 debugfs) | nice |
| `CONFIG_CFG80211_REQUIRE_SIGNED_REGDB` / `USE_KERNEL_REGDB_KEYS` | y / y | needs `regulatory.db{,.p7s}` on rootfs | **hard requirement**: without regdb + non-world regdom, all 5 GHz channels are NO-IR and hostapd refuses to start |
| `CONFIG_MAC80211_MESH`, `MAC80211_DEBUGFS`, `CFG80211_DEBUGFS` | n | no | no (optional debug aids, left off — minimal-change rule) |

The **real gap for AP is userspace, not kernel**: no soft-float `hostapd`
binary exists for this board (wpa_supplicant + iw exist from May). Cross-
compiling hostapd (needs libnl) is device-free and should happen before the
on-device phase.

## 2. What was changed

- **`linux-v6.6/arch/arm/configs/zx279128s_defconfig` — synced to the live
  config.** The tracked defconfig had drifted badly: the whole phase6 block
  (netfilter/NAT/NFT_FLOW_OFFLOAD, `NET_DSA=y`+`NET_DSA_ZTE_ZX279128=y`,
  `BRIDGE=y`, tc/act, `ZTE_GEPHY`/`MDIO_ZTE` builtin) existed only in
  `build/.config`. Running the documented flow (`make … zx279128s_defconfig`)
  would have silently destroyed the offload config. Sync method:
  `savedefconfig` → copied over the tracked defconfig → regenerated `.config`
  → **byte-identical round-trip verified**. No symbol was added or removed;
  the defconfig now reproduces the exact WiFi-ready + offload build.
- No other kernel config edits (audit found nothing missing).

## 3. Build result

`make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- O=../build zImage dtbs modules`
(the documented flow) — **exit 0, zero warnings** (log `/tmp/wifi_stage2_build.log`).

| Artifact | Size |
|---|---|
| `build/arch/arm/boot/zImage` | 15,681,376 B |
| `build/net/wireless/cfg80211.ko` | 855,676 B |
| `build/net/mac80211/mac80211.ko` | 900,976 B |
| `build/drivers/net/wireless/mediatek/mt76/mt76.ko` | 98,404 B |
| `build/drivers/net/wireless/mediatek/mt76/mt76-connac-lib.ko` | 71,668 B |
| `build/drivers/net/wireless/mediatek/mt76/mt7915/mt7915e.ko` | 156,824 B |
| `build/drivers/pci/controller/dwc/pcie-zx279128s.ko` | 12,332 B |

(Module .kos unchanged from the Jul-3 build — expected, the round-tripped
config is byte-identical, so the incremental build had nothing to redo.)

## 4. Staged configs (NOT deployed) + secret handling

- Templates (tracked, secret-free — placeholder `@WIFI_PSK@`):
  - `tasks/00.07.wifi/configs/wpa_supplicant-sta.conf.template` — SSID
    `Dino-WiFi-5GHz`, WPA2-PSK/CCMP/RSN, `ieee80211w=1`, `scan_ssid=1`.
  - `tasks/00.07.wifi/configs/hostapd-ap.conf.template` — wlan1, `hw_mode=a`,
    ch36 (non-DFS) / 80 MHz (seg0 42), 11n+ac+ax, WPA2-PSK/CCMP, PMF optional,
    `country_code` left commented (must be set on device — see below).
- Secret: `scratchpad/.wifi_psk` (mode 600), **git-ignored** — same pattern as
  `scratchpad/.sudo_pw`. `.gitignore` also covers `tasks/00.07.wifi/out/`.
- Renderer: `tasks/00.07.wifi/scripts/gen_wifi_configs.sh` — substitutes the
  PSK from `$WIFI_PSK` or the secret file into `tasks/00.07.wifi/out/*.conf`
  (chmod 600), then **fails if the PSK literal appears in any git-tracked
  file**. Ran clean: `OK: PSK not present in any git-tracked file.`
- 5 GHz radio is **wlan1** on this board (wlan0 = 2.4 GHz).
- ⚠ The AP template's SSID `Dino-WiFi-5GHz` (as specified for staging) equals
  the owner's HOME AP SSID — rename (e.g. `H3600-AP-Test`) before radiating,
  or clients will be confused.

## 5. Remaining ON-DEVICE steps (next phase — none attempted here)

1. **Bootargs**: put `pci=nomsi pcie_aspm=off` at the FRONT of the cmdline
   (MSI never delivers MT7915 IRQs on this SoC; ZTE U-Boot corrupts the LAST
   bootarg). Belongs in the `bootm`/cspstart cmdline used for TFTP boots.
2. Confirm rootfs payload: `mt7915_{rom_patch,wm,wa}.bin` + `MT7915_EEPROM.bin`
   (in `ext/firmware/mediatek/`), matched `regulatory.db{,.p7s}`, soft-float
   `wpa_supplicant` + `iw`, and the module chain
   `pcie-zx279128s → cfg80211 → mac80211 → mt76 → mt76-connac-lib → mt7915e`.
3. **STA re-verify** (last proven 2026-05-04, ~2 months stale): render configs
   (`gen_wifi_configs.sh`), `iw dev wlan1 scan | grep -i dino` to confirm the
   exact SSID, associate to `Dino-WiFi-5GHz` with
   `wpa_supplicant -D nl80211 -i wlan1`, DHCP, ping 8.8.8.8.
4. **hostapd AP bring-up** (never done): needs the **cross-compiled soft-float
   hostapd** (device-free prerequisite, still unbuilt — libnl dependency);
   set `country_code` (+ verify regdom via `iw reg get` is not world/00, else
   5 GHz is NO-IR and AP start fails); start hostapd on wlan1, associate a
   client, then bridge wlan1 into the LAN bridge (`CONFIG_BRIDGE=y` ready).
5. Known non-blocking residue from May: EFUSE_BUFFER_MODE / TXBF_ACTION MCU
   timeouts (TX-power/beamforming) — ignore unless they block AP.
6. Longer-term: WiFi HW-forwarding via the IDM ring = Stage 3
   (`findings/wifi_offload_feasibility_2026-07-04.md`), not this phase.
