# TFTP-boot rig troubleshooting — `*T T` timeouts (2026-06-24)

A full mainline RAM-boot via `scripts/tftp_boot_mainline.py` was failing with
`Loading: *T T` (TFTP timeout) and **zero ARP captured** on the host NICs. Root
cause was TWO compounding problems. This doc captures both + the fixes so we
don't burn time on it again.

## Symptom
- U-Boot reached fine; `setenv` commands OK.
- On `tftp`: `mac 2 phy status changed: 1000M full-duplex` then `Loading: *T T` (timeout).
- `ping 192.168.1.50` from U-Boot: `host 192.168.1.50 is not alive`.
- `tcpdump` on both host NICs during the transfer: **0 ARP packets**.

## Problem 1 — wrong jack (U-Boot boots via MAC2)
U-Boot uses `eth0 = MAC2` for TFTP. The ZX279128S MAC→RJ45 mapping is sequential:

| MAC | port |
|---|---|
| MAC0 | LAN RJ45 #1 |
| MAC1 | LAN RJ45 #2 |
| **MAC2** | **LAN RJ45 #3  ← boot/TFTP jack** |
| MAC3 | LAN RJ45 #4 |
| MAC4 | WAN (RGMII / ZX5201) |

So the boot cable must be on the **3rd LAN RJ45 (JACK3)**, and 192.168.1.50 must
be on the host NIC plugged into that jack. The cable had been on WAN, then on
JACK1/MAC0 — both wrong, so U-Boot's request (out MAC2) never reached the host.
(Mapping is a strong inference: block diagram + `mainline_reproduce_goodboot.py`
which documents `HOST_NIC=enxc8a362 ↔ device MAC2 host port`. Confirm with a
successful TFTP.)

## Problem 2 — host NIC (AX88179B) stuck after a software config-flip  ← cost the most time
The host NIC `enxc8a362` is an **AX88179B (USB 0b95:1790)**, multi-config:
- config 2 = `cdc_ncm` (default; carrier is USB-virtual, data path historically flaky but TFTP-boots fine)
- config 1 = `ax88179_178a` (real gigabit carrier)

Flipping to config 1 **by software** (`echo 1 > /sys/bus/usb/devices/3-2/bConfigurationValue`)
reliably wedges the driver into a stuck state:
```
Speed: 1000Mb/s, Duplex: Full, Link partner advertised auto-negotiation: Yes
Link detected: no            ← stuck
```
i.e. the device-side PHY negotiates (U-Boot prints `mac N phy status changed:
1000M`) but the **host driver never raises carrier** → no traffic flows even on
the correct jack. This is why we saw zero ARP and `host not alive`.

### Diagnosis tell
`device sees 1000M link` + `host ethtool: Link detected: no` + `carrier=0`
⇒ host NIC driver is stuck, NOT the jack/device.

### Fix — software USB re-enumeration (no physical unplug, no reboot)
```bash
echo 0 | sudo tee /sys/bus/usb/devices/3-2/authorized   # de-authorize: drops the device
echo 1 | sudo tee /sys/bus/usb/devices/3-2/authorized   # re-authorize: fresh enumeration + re-probe
```
It comes back at the **default config (cdc_ncm)** with carrier restored, no
longer stuck. (`3-2` = the AX88179B's USB path; find via
`for d in /sys/bus/usb/devices/*; do grep -l 0b95 $d/idVendor; done`.)

### Lesson
**Do NOT software-flip the AX88179B to ax88179 mode for booting — it sticks.**
cdc_ncm is the safe default and TFTP-boots fine. If you do flip it and it wedges,
the `authorized` toggle recovers it without touching hardware. Repeated config
switches + USB churn can wedge BOTH modes → then a clean host reboot is needed.

## Driver-side robustness added this session (`lib/uart.py`)
The lazy-PHY race (U-Boot inits MAC/PHY only on the first network command, so the
link negotiates *during* the first `tftp` and the first RRQ is lost) is now
mitigated:
- `_PREAMBLE` issues `ping 192.168.1.50` before `tftp` (warms the PHY + primes ARP;
  harmless no-op if U-Boot lacks `ping`).
- `POST_CMD_SETTLE` (1.5s) after each U-Boot command returns to prompt.
- **In-place `tftp` retry** (`TFTP_INPLACE_RETRIES`): on `*T T`, re-send `tftp`
  without a full DTR restart — by the 2nd send the link has settled. (This was the
  documented-but-unimplemented `retry_on_tftp_fail`; now implemented.)

## Correct rig for the boot
1. AX88179B in cdc_ncm (default; recover via `authorized` toggle if stuck).
2. Boot cable on **JACK3 (3rd LAN RJ45 = MAC2)**; 192.168.1.50/24 on that host NIC.
3. tftpd serving `tftp/` on 192.168.1.50: `dnsmasq --user=root --port=0 --enable-tftp
   --tftp-root=<repo>/tftp --listen-address=192.168.1.50` (must be `--user=root` or it
   can't read the repo dir).
4. `python3 scripts/tftp_boot_mainline.py`.
