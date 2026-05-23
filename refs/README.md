# refs/ — external reference material

**Not authoritative for our device.** Stuff that other people produced
for related-but-not-identical hardware, kept here because it's useful
to cross-reference during RE and the future OpenWrt port.

If something here conflicts with our own `ext/` (which IS authoritative
for our specific H3600 unit), **trust `ext/`**.

## Contents

| Folder | What | Use for |
|---|---|---|
| `orca-h3600p/` | Marcos del Sol Vives' ("orca") prior RE work on his own H3600P unit. **Same model family as ours, but a different physical device.** | Ghidra symbols (unstripped `kernel.elf`), DTS cross-check |
| `stefan-zx297520/` | Stefan's Linux kernel port for the sibling ZXIC SoC ZX297520v3 (D-Link DWR-932M etc). | Reference for `mach-zx` patterns, GPIO/IRQ/QSPI driver shape, dts conventions, what an "almost working" mainline port looks like |

## Why these are NOT in `ext/`

- `ext/` = **OUR** device's golden source (factory NAND of our H3600,
  factory rootfs decrypted with **our** AES key, our extracted vmlinux).
- `refs/` = **someone else's** work — useful but not ground-truth for us.

Symbol offsets, register defaults, DTS values, and AES keys can differ
between physically distinct units even of the same model (vendor key
derivation may include serial number / MAC). Always verify a reference
finding against `ext/` before relying on it for our hardware.
