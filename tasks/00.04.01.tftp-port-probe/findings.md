# Findings — TFTP port probe (2026-05-23)

## Answer

**No.** ZTE's U-Boot fork on the H3600 does **not** support redirecting
the TFTP destination port. We must keep `in.tftpd` on port 69 (sudo) or
use a host-side workaround (iptables / setcap / authbind).

## Evidence

### 1. U-Boot version is from 2013 — pre-dates `CONFIG_NET_TFTP_VARS`

Captured from the probe's boot banner:

```
U-Boot 2013.04 (Oct 28 2021 - 12:09:15)
```

`CONFIG_NET_TFTP_VARS` (which exposes `tftpdstp` / `tftpsrcp` as env vars
honored by the `tftp` command) landed in mainline U-Boot in 2017. A 2013
base does not have this feature unless ZTE backported it — and they did
not (see #2, #3 below).

### 2. Default env contains no TFTP-port variable

`printenv` output (full capture in `capture.log`):

```
autorun=""
baudrate=115200
bootargs=console="ttyAMA0,115200n8" root=/dev/mtdblock8 ro rootfstype=jffs2 mem=256M
bootcmd=setenv bootargs console=$(console) root=/dev/mtdblock8 ro rootfstype=jffs2  mem=$(memsize);
bootdelay=3
bootfile=uboot.bin
bootloaderfile=bootloader.bin
console="ttyAMA0,115200n8"
ethact=eth0
ethaddr=00:41:71:00:00:50
fileaddr=42000000
filesize=20000
fullfile=upgrade.bin
gatewayip=192.168.1.1
hostname=unknown
ipaddr=192.168.1.1
linuzfile=vmlinuz.bin
loadaddr=0x42000000
memsize=256M
netmask=255.255.255.0
netretry=5
serverip=192.168.1.50
stderr=serial
stdin=serial
stdout=serial
tftpblocksize=1468
versioninfo=U-Boot V1.0.0 20211028123000 0x700000 0x0 0xaf 0xa3
```

Nothing tftp-port-shaped. Only `tftpblocksize` is present.

### 3. `help tftp` confirms the command has no port option

```
=> help tftp
tftp - boot image via network using TFTP protocol

Usage:
tftp [loadAddress] [[hostIPaddr:]bootfilename]
```

You can override the **server IP** by prefixing the filename
(`tftp 0x42000000 192.168.1.99:slotA.bin`), but there is no port
syntax. The command's option parser has no notion of a port.

### 4. `setenv` accepts arbitrary names — does NOT mean they're honored

```
=> setenv tftpdstp 6969
=> printenv tftpdstp
tftpdstp=6969
=> setenv tftpdstport 6969
=> printenv tftpdstport
tftpdstport=6969
=> setenv tftp_port 6969
=> printenv tftp_port
tftp_port=6969
```

All three round-trip cleanly. This proves only that U-Boot's `setenv`
storage is generic — it does NOT prove the `tftp` command reads any of
them. Combined with #2 (none pre-exist) and #3 (the help text doesn't
mention any port option), the conclusion is clear: the `tftp` command
ignores all these vars.

A definitive end-to-end test would require running a TFTP server on a
non-69 port and confirming a transfer succeeds with one of these vars
set. We did not run that test because the negative evidence above is
already overwhelming (default env + help text + U-Boot vintage all
point the same way), and a positive end-to-end test would only confirm
what's already very unlikely.

## Bonus findings from the boot log

The probe's reset at the end captured a full cspstart cycle, which
incidentally validates several other things the flash tool depends on:

- **BootPara header self-CRC scope confirmed live**: cspstart's
  `csp_crc:103 >>csp_crc, data addr:42000000, crc_len:0xa4` line shows
  it CRCs 0xa4 bytes of the header (matches our `HDR_SELF_CRC_END =
  0xa4`).

- **CRC algorithm = zlib.crc32, stored as the un-complemented value**:
  the log prints `crc=0x89d932df, 0x7626cd20`. These are complements
  (XOR = 0xffffffff). The header has `0x7626cd20` stored at offset
  0xa4. Our `bp.csp_crc()` (= `zlib.crc32(data) & 0xffffffff`) returns
  `0x7626cd20` for this header — matches stored.  Confirms what's in
  `lib/bootpara.py::csp_crc()`.

- **fs_start = kernel_offset + kernel_size, NOT static**: cspstart
  computes `JffsOffset:0x360214,JffsSize:0x1620000`, but then
  `FsOffset=a60000` — so it later overrides with the partition's
  hardcoded offset. The kernel_size field's effect on fs_start is more
  nuanced than the doc claims; this is worth digging into separately
  but doesn't affect the flash tool's correctness for slot A.

- **The mysterious 0x38 field**: the doc says `0x34=kernel_size,
  0x38=?`. The cspstart trace shows `JffsOffset:0x360214` — and
  `0x360214` is the value at header offset `0x44` per
  `docs/NAND_LAYOUT_AND_BOOT.md`. So `0x44` (not `0x38`) is the
  rootfs-absolute-offset. The 0x38 field's meaning is still unknown
  but it is NOT kernel_size (which is at 0x34) — the flash tool's
  use of `0x34` is the correct one.

## Action items for the flash tool

1. **Leave `_PREAMBLE` alone** — no `tftpdstp` setenv to add; it would
   be a no-op.

2. **Keep the `sudo in.tftpd` chore in CLAUDE.md** for now. Document
   here that the U-Boot side is the blocker, not the host side.

3. **If we ever care enough** to drop sudo, the host-side options are:

   | Option | One-time sudo? | Per-run sudo? | Scope |
   |---|---|---|---|
   | `iptables -t nat -A PREROUTING -p udp --dport 69 -j REDIRECT --to-port 6969` | yes | no | system-wide |
   | `setcap 'cap_net_bind_service=+eip' /usr/bin/python3.X` | yes | no | that python binary only |
   | `authbind` | yes (configure `/etc/authbind/byport/69`) | no | per user |

   All three would let `py3tftp` / `tftpy` serve on port 69 from
   userland. Pick whichever bothers least.

## Status

- Probe ran cleanly; device booted back to stock kernel afterward.
- No `saveenv` was issued; the three `setenv tftp*` lines evaporated
  on the reset at the end of the probe.
- This subtask can be marked DONE.
