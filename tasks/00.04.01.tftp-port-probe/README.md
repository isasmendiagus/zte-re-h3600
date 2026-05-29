# tftp-port-probe — does ZTE U-Boot support a custom TFTP port?

**ID**: 00.04.01
**Parent**: [00.04 flash-tool](../00.04.flash-tool/)
**Children**: none
**TaskList items**: none directly
**Status**: DONE — 2026-05-23 — answer is NO, see [findings.md](findings.md)

## Why

The flash tool currently relies on `sudo in.tftpd -a 192.168.1.50:69 ...` to
serve files to the device, because port 69 is privileged. If U-Boot lets us
override the destination port (e.g. via `tftpdstp` env var), we can:

- Run a pure-Python TFTP server (`py3tftp` / `tftpy`) on a non-privileged
  port (≥ 1024)
- Drop the `sudo` chore from the host setup entirely
- Make every flash recipe usable without elevated privileges

Standard mainline U-Boot exposes `tftpdstp` (and sometimes `tftpdstport`)
when compiled with `CONFIG_NET_TFTP_VARS`. ZTE's U-Boot fork is old and
custom — we don't know without checking.

## Method

Drive U-Boot via UART using the same `uart._do_reset_then` machinery the
flash tool uses, but **only run safe read-mostly commands**:

1. `printenv` — dump the full env (would `tftpdstp` already appear?)
2. `help tftp` — see if the tftp command's own help mentions a port option
3. `setenv tftpdstp 6969` → `printenv tftpdstp` (does the name exist?)
4. Same for `tftpdstport`, `tftp_port` (alternate spellings used by some forks)

**Safety**: no `saveenv` is ever called. All `setenv` changes evaporate on
the next power-cycle. No NAND writes, no flash, no boot of any image.

## Files

- `probe_uboot_tftp.py` — the probe script
- `capture.log` — full UART output (committed for diff/review)
- `findings.md` — written after the probe runs

## Run

```
python3 tasks/00.04.01.tftp-port-probe/probe_uboot_tftp.py
```

Device must be reachable on `/dev/ttyUSB*` with the FTDI cable's DTR-relay
mod for auto-power-cycle. Takes ~90 seconds (DTR reset → U-Boot prompt →
a handful of `printenv`/`setenv` commands → reset).

## What "yes" vs "no" looks like

- **Yes** (env var supported): `printenv` shows `tftpdstp` already in the
  list, OR the var name parses cleanly (no "Unknown command") and
  `printenv tftpdstp` after the setenv prints the value back. (Note: even
  if `setenv` accepts an arbitrary name, that alone doesn't prove the
  `tftp` command honors it — a follow-up live-network test is needed to
  fully confirm. This probe answers "is the var name plausible".)
- **No**: `printenv` doesn't mention any tftp-port-related var, `help
  tftp` doesn't either, and none of the candidate names are pre-existing.
  → would have to fall back to iptables redirect or `setcap`.

## Follow-up (if probe is positive)

Run a separate session with `py3tftp` listening on `192.168.1.50:6969`
and an empty `slotA.bin` placeholder. From U-Boot: `setenv tftpdstp 6969
; tftp 0x42000000 slotA.bin`. If TFTP succeeds (or reports a clean
file-not-found from the server, not a network timeout), the var is
honored end-to-end. Then the flash tool's `_PREAMBLE` can be extended
with a `tftpdstp` setenv and the sudo dependency dropped.
