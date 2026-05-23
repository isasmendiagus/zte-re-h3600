# Slot A + patched cspd reproducibility playbook

Build a slot-A rootfs with our 3-byte `cspd` patch, flash it, boot it, SSH in.
This documents the **working** pipeline as of 2026-05-22.

> Pre-req reading: `NAND_LAYOUT_AND_BOOT.md`, `NAND_PERSISTENCE_PLAN.md`
> Recovery: `stock_traced/flash_slot_a_RECOVERY.py` restores factory slot A.

## TL;DR

```sh
cd ~/Projects/MYSELF/ZTE/H3600/stock_traced
./prepare_slot_a.sh --write
# ~5 min: build jffs2 → encrypt → flash → reset
# After: SSH admin@192.168.1.1 password UkuGPeyRDU
```

Slot B is never touched — automatic fallback if anything breaks.

## What slot A contains

- Stock H3600 V9.0.20P72 rootfs, minus trims (see below)
- `/bin/cspd` with 3 bytes patched: `0x1cdeda, 0x1cdf21, 0x1ce161 → 0x33` (was `30/31/32`)
- 329 device nodes recreated via `mkfs.jffs2 --devtable=devtable.txt`
- `/etc/dsl/{boot.bin,fw.bin}` (switch chip firmware — `nfbi bootdownload` needs it)

## End-to-end pipeline

1. **Stage** — `rootfs/` is the extracted stock JFFS2 tree (owned by `ubuntu:ubuntu`).
2. **Drop patched cspd** — `out/cspd-uart-alive` copied to `rootfs/bin/cspd`.
3. **Trim** to fit 22 MiB jffs2:
   - `/home/httpd/public/img`
   - `/etc/usb_modeswitch.d`
   - `/bin/voip`, `/bin/mqtt`
   - `/lib/modules/4.1.25/modules.*.bin`
   - `/etc/autokernelconf`
   - **DO NOT trim** `/etc/dsl`, `/bin/smbd`, `/bin/cspd` itself
4. **Build jffs2**:
   ```
   mkfs.jffs2 \
     --pagesize=2048 --eraseblock=131072 --no-cleanmarkers \
     --pad=0x1620000 --little-endian -m size \
     --squash --devtable=devtable.txt \
     --root rootfs --output rootfs.jffs2
   ```
   `--squash` forces uid/gid 0 (avoids ubuntu uid leak). `--devtable` creates
   `/dev/console`, `/dev/null`, `/dev/ttyAMA0`, etc.
5. **AES-128-ECB encrypt** with key `H36000e71071c440` (16 ASCII chars).
6. **Build BootPara header**:
   - `header[0x48:0x4c]` ← LE32 `zlib.crc32(encrypted_rootfs)`
   - `header[0xa4:0xa8]` ← LE32 `zlib.crc32(header[0:0xa4])`
   - (See CRC note below — these strict CRCs *won't* match cspstart's expectation
     but the lenient JFFS2-magic-detection path accepts.)
7. **Flash via U-Boot** in one session — `flash_slot_a.py`:
   - DTR reset → press `1` → bootmode password
   - `tftp 0x42000000 rootfs_a_patched_enc.jffs2`
   - `nand erase 0xa60000 0x1620000`
   - `nand write 0x42000000 0xa60000 0x1620000`
   - `tftp 0x42000000 header_a_patched.bin`
   - `nand erase 0x2080000 0x20000`
   - `nand write 0x42000000 0x2080000 0x20000`
   - `reset`

## What success looks like in the UART log

```
zteboot_verify_fs:237 use defualt jffs2 fs!!     ← lenient path accepts slot A
zteboot_verify_fs:242 verify fs success!!
zteboot_do_settings:378 >>s=256M, select=0       ← slot A selected
Starting kernel ...
[~60s of silent boot]
$ ssh admin@192.168.1.1                          ← SSH listens within ~1 min
```

## Discoveries from this work

### 1. `csp_crc` IS `zlib.crc32` — but the printed pair is `(value, ~value)`

ZTE U-Boot logs `csp_crc:103 ... crc=<calc>, <complement>`. Both numbers are
derivatives of the same standard IEEE CRC32. Verify:
`0xf9467fa4 ^ 0xffffffff = 0x06b9805b`.

**For strict verify to pass**, the value stored in the header must equal the
computed `csp_crc` output — NOT its complement. Our header currently stores
`zlib.crc32(...)` which happens to be the complement of what csp_crc returns
(i.e. csp_crc is the JAMCRC variant: zlib without the final XOR-0xffffffff).

**This does not matter in practice** because the **lenient JFFS2 path**
(`zteboot_verify_fs:237 use defualt jffs2 fs!!`) accepts the rootfs when the
decoded JFFS2 magic is present, regardless of CRC. If you ever want strict CRC
match, store `(zlib.crc32(data) ^ 0xffffffff) & 0xffffffff` instead.

### 2. Lenient JFFS2 path is the contract — not strict CRC

cspstart's logic when both BootPara headers are present:
1. Compute csp_crc of rootfs region
2. Compare to header's stored CRC
3. If match → STRICT pass
4. If mismatch → check for JFFS2 magic via the decrypted mtdblock view
5. If JFFS2 magic present → LENIENT pass (`use defualt jffs2 fs!!`)
6. If neither → reject slot, try the other

For any custom rootfs you build with `mkfs.jffs2`, expect path 4-5 to fire.
The JFFS2 magic check is sufficient; do not stress over strict CRC.

### 3. `mkfs.jffs2 --devtable=...` is mandatory

The JFFS2 extractor that produced our `rootfs/` couldn't create char/block
special files without root, so `/dev/` was empty. Without device nodes
JFFS2 in the image, `init` can't open `/dev/console` → silent boot hang
(no UART output past "Starting kernel ...").

Solution: dump live `/dev/` listing from a booted device, generate
`devtable.txt` with 329 entries (console, null, zero, mtdblock*, ttyAMA0,
ttyUSB*, bcm*, mmcblk*, sda-sdh, etc.), pass to `mkfs.jffs2 --devtable=`.

### 4. Slot selection (`select=0` vs `select=1`) when both pass

Observed: `BootPara->flags = 0xa3` in slot A makes it win over slot B
(`flags = 0x00`). The original stock factory header has `0xa3`. Our
patched header copies from the factory header and keeps `flags = 0xa3`,
so slot A wins.

If slot A is **empty/erased** (no valid BootPara magic), cspstart skips
straight to slot B — that's the recovery behavior.

### 5. UART silencing is multi-layered — and the cspd patch was useless for kernel printk

(REVISED 2026-05-22 — replaces the earlier "two layers" theory.)

Layers in play:

1. **cspd `/dev/console` logctrl mask** — bits 0x02|0x04|0x10 (logger, printf, logcat).
   Crucially, **bit 0x08 (kernel data) is never accessible via `logctrl -g N`**
   for the Serial node — only `/dev/logger_main` carries kernel data.
   So our `-g 0/1/2 → -g 3` 3-byte cspd patch only affected userspace logger
   forwarding, not kernel printk. **The patch was a no-op for the actual goal.**

2. **`/proc/sys/kernel/printk = 0`** — kernel console_loglevel=0 → only
   `KERN_EMERG` reaches consoles. Set somewhere we haven't located yet
   (not in `/etc/rc`, `/etc/init.norm`, `/etc/init.debug`; not via any
   `/proc/sys/kernel/printk` string in any binary). Probably a syscall
   (`klogctl(8,...)` / `sys_syslog(SYSLOG_ACTION_CONSOLE_OFF)`) from cspd
   or a kernel module. Setting it to 7 via SSH does NOT restore UART output.

3. **Kernel printk → console driver path is silent** — even with
   `printk=7`, `ignore_loglevel=Y`, and forced prints via
   `echo h > /proc/sysrq-trigger`, **nothing reaches UART**. But the
   hardware UART TX *is* alive: writing data bytes directly to
   `devmem2 0x94404004` (the **shifted DR** at `base+0x04`) produces
   exactly that output on UART (verified by writing `OHAI\n` → 5 bytes
   captured on UART). The silence is between kernel printk and the PL011
   driver. Likely cause: the stock kernel's `pl011_console_write` targets
   the standard PL011 DR offset (`base+0x00`) instead of the ZTE-shifted
   DR (`base+0x04`), so writes hit a no-op address.

**Implications:**
- The cspd binary patch (3 bytes → '3') does not need to be undone but
  should not be relied on for UART output.
- Real fix paths for persistent kernel UART:
  - (A) Userspace daemon that drains `/dev/kmsg` and writes each char via
    `devmem2 0x94404004` — works today; brittle, slow.
  - (B) Patch the stock kernel binary's `pl011_console_write` to use
    DR=+0x04 instead of +0x00 — invasive, needs kernel image RE.
  - (C) Replace stock kernel with mainline (which has `CONFIG_ARCH_ZX=y`
    + DT-driven shifted PL011) — much bigger lift, but the long-term path.

### 6. PL011 hardware register layout (ZTE-shifted)

Confirmed from running stock device 2026-05-22 via `devmem2`:

| Reg   | Offset (from `base=0x94404000`) | Notes |
|-------|---------------------------------|-------|
| DR    | `+0x04` | Standard PL011 DR is `+0x00`. Writing here transmits a byte. |
| FR    | `+0x14` | Standard is `+0x18`. Flags (BUSY, TXFE, RXFE). Stock value `0x90`. |
| IBRD  | `+0x24` | Stock value `0xD` (integer divisor for 115200 baud @ 24 MHz UART clock) |
| FBRD  | `+0x28` | Stock value `0x24` |
| LCR_H | `+0x2C` | Stock value `0x00` |
| CR    | `+0x30` | Stock value `0x70` (not a standard PL011 CR bitmap — pending) |
| IMSC  | `+0x38` | Stock value `0x12` |

`+0x00` reads `0x1060000` — NOT data. Writes there silently no-op (verified).

A second PL011 instance exists at `0x94405000` (same register signature).

### 7. `logctrl -g N` → LogSrcType bitmap (from runtime probing on stock)

Mapping (CORRECTED — replaces the misleading help text):

| `-g N`  | LogSrcType set on `/dev/console` |
|---------|----------------------------------|
| 0       | `0x00` (nothing) |
| 1       | `0x02` (logger) |
| 2       | `0x04` (printf) |
| 3       | `0x06` (logger + printf) |
| 4..8    | `0x10` (logcat — clamped default) |
| f       | `0x00` |

Other mask bits observed on other nodes:
- `0x08` = kernel data — only ever set on `/dev/logger_main`. NOT user-controllable.
- `0x10` = logcat diagnostic.

`-g 3` is NOT the "ALL" the help text claims — it's `logger | printf` only.
The help text is wrong.

### 8. CRC drift across reboots (cosmetic)

We saw cspstart compute different CRCs over the "same" flashed image on
sequential boots (e.g. `d4c2b8c5` first boot, `f9467fa4` next boot). Likely
JFFS2 writes cleanmarkers / mount counters during first mount, mutating the
underlying NAND bytes → next-boot computed CRC differs.

Doesn't matter because lenient path accepts regardless. But it explains
why the ISOLATION test's strict-CRC match was effectively a one-shot — the
exact match only held until first JFFS2 mount.

## File index (paths relative to `H3600/`)

| File | Purpose |
|------|---------|
| `tasks/stock_traced/README.md` | Task overview, status, files, next sub-tasks |
| `tasks/stock_traced/prepare_slot_a.sh` | Build + (with `--write`) flash slot A |
| `tasks/stock_traced/flash_slot_a.py` | U-Boot driver: DTR reset → tftp + nand erase/write |
| `tasks/stock_traced/flash_slot_a_ISOLATION.py` | Diagnostic: flash factory bytes + matching CRC |
| `tasks/stock_traced/flash_slot_a_RECOVERY.py` | Restore factory slot A from `h3600_nand_full.bin` |
| `tasks/stock_traced/devtable.txt` | 329 device nodes dumped from live device via SSH |
| `tasks/stock_traced/out/cspd-uart-alive` | Patched cspd (3 bytes at 0x1cdeda/0x1cdf21/0x1ce161 → `0x33`) |
| `tasks/stock_traced/out/cspd-uart-alive.PATCHED` | Backup of patched cspd |
| `tasks/stock_traced/ITERATIONS.md` | Iteration history (iter 0 → iter 7) |
| `h3600_nand_full.bin` | Factory NAND backup (recovery source) |

## Recovery

If slot A boots into something broken, just rebuild and reflash — slot B is
intact stock and will always boot via lenient path if cspstart can't find a
valid slot A header.

To explicitly restore factory slot A:
```sh
cd ~/Projects/MYSELF/ZTE/H3600/stock_traced
python3 flash_slot_a_RECOVERY.py
```
