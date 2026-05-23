# HOST_SETUP — host-side services and commands

What needs to be running on your development laptop for the device-side
work to function. Everything here is **host-side** (your Ubuntu PC), not
device-side.

## Quick reference — the 4 commands you'll actually use

```sh
# 1. Start TFTP server (foreground, Ctrl-C to stop). Required for any flash / boot.
sudo zxic/tools/host/tftpd_start.sh

# 2. Start wire capture to /tmp/capture.pcap. Required for TX/RX driver debug.
sudo zxic/tools/host/tcpdump_capture.sh

# 3. SSH to stock kernel (when slot A has the stock-shell rootfs running)
ssh admin@192.168.1.1                       # password: UkuGPeyRDU

# 4. UART log / REPL (always available, regardless of device kernel)
python3 zxic/lib/uart.py log                # tail UART output
python3 zxic/lib/uart.py auto_bootm_dtb_appended    # full mainline boot
```

That's it for day-to-day. Everything below is one-time setup or
diagnostics.

---

## TFTP server — `tools/host/tftpd_start.sh`

The device pulls files via TFTP during every boot, flash, and mid-iter
cycle. Without this running, nothing works.

```sh
sudo zxic/tools/host/tftpd_start.sh
```

Equivalent raw command (if you want to know what it does):

```sh
sudo pkill -f 'in\.tftpd' 2>/dev/null || true
sudo in.tftpd -L --secure --create \
    -a 192.168.1.50:69 \
    /home/ubuntu/Projects/MYSELF/ZTE/zxic/tftp
```

- `-L` keeps it in the foreground so you see every request live (great
  for debugging "did my TFTP transfer even start?")
- `--secure` chroots to the serve dir
- `--create` lets the device upload back (some debug flows need this)
- `-a 192.168.1.50:69` binds to the host-device link IP only (not 0.0.0.0)

**Common pitfall**: after any directory rename (e.g. the `H3600/` → `zxic/`
migration), a tftpd already running with the old path is still alive and
will silently fail. Always `pkill -f in.tftpd` before starting fresh.

**Check it's running**:

```sh
ps -ef | grep '[i]n.tftpd'
# Expected: -a 192.168.1.50:69 ... /home/ubuntu/Projects/MYSELF/ZTE/zxic/tftp
```

### Refreshing artifacts in the serve dir

After rebuilding the kernel:

```sh
zxic/tools/refresh_tftp.sh
```

Copies `zImage` + DTB + initramfs from `build/` into `tftp/`. Does NOT
restart the daemon — just refreshes content (the daemon serves whatever
is in the dir at request time).

---

## Wire capture — `tools/host/tcpdump_capture.sh`

When debugging the eth-driver, you need ground truth about what's on
the wire. Driver counters lie (TX counter can increment with nothing
reaching the wire). tcpdump doesn't.

```sh
sudo zxic/tools/host/tcpdump_capture.sh
# writes to /tmp/capture.pcap (override: sudo ./tcpdump_capture.sh /tmp/foo.pcap)
```

Equivalent raw command:

```sh
sudo tcpdump -i enxc8a362e95900 -nn -e -v -l -Z $USER \
    -w /tmp/capture.pcap
```

- `enxc8a362e95900` — the USB-Ethernet interface on the host that's
  cabled to the device. Yours may be different — check with
  `ip -br link | grep '^en'`. The wrapper script reads
  `$ZXIC_NET_IFACE` to override.
- `-nn` no DNS lookup (don't block on reverse-DNS)
- `-e` show link-layer (MAC) headers
- `-v` verbose
- `-l` line-buffered (live)
- `-Z $USER` drop root after opening socket
- `-w` raw pcap output

**Read it back**:

```sh
tcpdump -r /tmp/capture.pcap | head            # quick look
tcpdump -r /tmp/capture.pcap 'ether host f4:f6:47:0f:42:64'  # filter by device MAC
wireshark /tmp/capture.pcap                    # GUI inspect
```

**Filter while capturing** (lighter than post-filter):

```sh
sudo zxic/tools/host/tcpdump_capture.sh 'arp or icmp'  # only ARP + ping
```

(The wrapper passes any extra args through to tcpdump's filter expression.)

---

## Network setup (the host's USB-Ethernet link)

The host PC and the H3600 are connected via a USB-to-Ethernet adapter,
not via your home LAN. The link uses a private subnet.

| Side | IP | MAC | Notes |
|------|-----|-----|-------|
| Host PC | `192.168.1.50/24` | (host's adapter MAC) | Static IP via netplan/NetworkManager |
| H3600 stock | `192.168.1.1/24` | factory MAC | Default per stock firmware |
| H3600 mainline `sw` | `192.168.1.99/24` | `f4:f6:47:0f:42:64` | Assigned by our `/init` script |

**Check the link**:

```sh
ip -br addr show enxc8a362e95900
# UP            192.168.1.50/24
ping -c 1 192.168.1.1      # stock kernel responds
ping -c 1 192.168.1.99     # mainline kernel responds (when driver works)
```

If the interface name differs:

```sh
ip -br link | grep '^en'
# enxc8a362e95900   UP   c8:a3:62:e9:59:00 ...   ← that's it
```

Set `ZXIC_NET_IFACE` to override the default in the wrapper scripts.

---

## One-time setup

### apt packages

```sh
sudo apt install \
    tftpd-hpa \
    tcpdump \
    gcc-arm-linux-gnueabi binutils-arm-linux-gnueabi \
    u-boot-tools \
    bison flex libelf-dev libssl-dev \
    openssh-client paramiko \
    python3-pyserial python3-paramiko \
    wireshark-qt
```

### Disable the system tftpd-hpa service

Ubuntu's `tftpd-hpa` package starts a systemd service we don't want
(it serves from `/srv/tftp` by default). Disable it so our wrapper
doesn't race with it:

```sh
sudo systemctl disable --now tftpd-hpa
```

### USB-Ethernet static IP

Add to NetworkManager or netplan so the host-side IP is always
`192.168.1.50` on the device link:

```yaml
# /etc/netplan/01-zxic-link.yaml
network:
  version: 2
  ethernets:
    enxc8a362e95900:
      addresses: [192.168.1.50/24]
      dhcp4: false
      optional: true
```

```sh
sudo netplan apply
```

### DTR hardware mod

Required for `uart.py auto_*` commands to power-cycle the device
without your finger on the power button. See
`tools/dtr-mod/README.md` for the one-time FT232R EEPROM flip.

After that, install the holding service:

```sh
sudo cp zxic/tools/dtr-mod/dtr-hold.service /etc/systemd/system/
sudo systemctl daemon-reload
sudo systemctl enable --now dtr-hold
```

This keeps DTR in the "device ON" state whenever the host is up.

### Cross-compiler verification

```sh
arm-linux-gnueabi-gcc --version          # should be installed
arm-linux-gnueabi-gcc -dumpmachine        # MUST print arm-linux-gnueabi (NOT -hf)
```

Full reasoning in `docs/CROSS_COMPILE_GUIDE.md`. TL;DR: this hardware
has no VFP unit, so hard-float binaries SIGILL on first VFP instruction.

---

## Permissions / sudo notes

| Action | Needs sudo? |
|---|---|
| `in.tftpd` (bind port 69, chroot) | yes |
| `tcpdump` (open raw socket) | yes (drops to user after open via `-Z`) |
| `python3 lib/uart.py *` | no (your user is in `dialout` group, hopefully) |
| `ssh admin@...` | no |
| `arm-linux-gnueabi-gcc ...` | no |
| Restarting `dtr-hold.service` | yes |

Make sure your user is in `dialout` (and `wireshark` for live capture
in the GUI):

```sh
sudo usermod -aG dialout,wireshark $USER
# log out / log in for it to take effect
```

---

## Troubleshooting

| Symptom | First thing to check |
|---|---|
| "TFTP timeout" from U-Boot | Is `tftpd_start.sh` running? `ps -ef \| grep '[i]n.tftpd'` |
| TFTP serves wrong file / stale file | `ls -la zxic/tftp/` — did you forget to run `refresh_tftp.sh`? |
| TFTP serves correct file but boot still fails | tftpd serving the *old* H3600 path; restart with the wrapper |
| Capture shows 0 packets but device is ping-able | Wrong `$IFACE`. Run `ip -br link \| grep '^en'`, set `ZXIC_NET_IFACE` |
| `uart.py auto_*` hangs at reset | DTR-hold not running, OR cable EEPROM not modded. See `tools/dtr-mod/README.md` |
| `ssh admin@192.168.1.1` "connection refused" | Slot A booted into mainline, not stock-shell. Either switch slot or `auto_bootm` the stock kernel from RAM |

---

## See also

- `tools/host/` — the wrapper scripts referenced here
- `tools/dtr-mod/README.md` — the DTR hardware mod (one-time per cable)
- `docs/ITERATE.md` — the dev loops that use these host services
- `docs/CROSS_COMPILE_GUIDE.md` — toolchain choices
- `tasks/00.03.nand-flash/README.md` — flash recipes that consume the TFTP server
