# stock-shell — custom slot-A rootfs for persistent SSH + UART (stock kernel)

**ID**: 00.02
**Parent**: [00 openwrt-port](../00.openwrt-port/)
**Children**: none — atomic task
**TaskList items**: #100, #101 (both done)
**Status**: DONE-ENOUGH — SSH ✓, UART-via-kmsg2uart ✓. Used as RE oracle by 00.01.

**Goal**: build a customized slot-A rootfs (running the stock 4.1.25 kernel)
that boots automatically, gives SSH access, and (eventually) emits kernel
printk on UART — without ever touching slot B or the bootloader.

**Status**: SSH works ✓ — UART/printk pending.

## Where we are (2026-05-22)

- **Slot-A custom rootfs boots**: `./prepare_slot_a.sh --write` builds a
  patched rootfs, flashes it via U-Boot, device reboots into our custom
  slot A, SSH (`admin / UkuGPeyRDU`) is live within ~60 s.
- **Patched cspd is loaded but useless** for kernel printk on UART —
  `logctrl -g N` can't route kernel data (bit `0x08`) to `/dev/console`.
  See discoveries below.
- **UART hardware itself is fine** — direct writes via
  `devmem2 0x94404004 w 0x4f` (ZTE-shifted DR offset) produce bytes on
  UART. Stock kernel's `pl011_console_write` is silent because it likely
  writes to standard DR=+0x00 instead of ZTE's +0x04.

## Files

| File | What it does |
|------|--------------|
| `prepare_slot_a.sh` | Build pipeline: stage → trim → mkfs.jffs2 (with devtable+squash) → AES encrypt → CRC → flash (with `--write`) |
| `flash_slot_a.py` | Drives U-Boot via DTR-reset to tftp+nand-erase+nand-write rootfs+header in one session |
| `flash_slot_a_RECOVERY.py` | Restore factory slot A from `../../h3600_nand_full.bin` |
| `flash_slot_a_ISOLATION.py` | Diagnostic: flash factory bytes + matching CRC (proves flash mechanism is correct) |
| `deploy_cspd_patch.py` | (Legacy) live-patch cspd via SSH — superseded by the NAND-write approach |
| `devtable.txt` | 329 device nodes dumped from a live device — fed to `mkfs.jffs2 --devtable=` (mandatory!) |
| `out/cspd-uart-alive` | Patched cspd binary (3 bytes at 0x1cdeda/0x1cdf21/0x1ce161 → `0x33`) |
| `out/cspd-uart-alive.PATCHED` | Backup of patched cspd |
| `ITERATIONS.md` | Iteration history (iter 0 → iter 7) — what was tried, what failed, why |
| `staging/` | Working rootfs tree (disposable; regenerated each `--write`) |
| `out/` | Built artifacts: `rootfs_a_patched.jffs2`, `..._enc.jffs2`, `header_a_patched.bin` |

External dependencies (in `H3600/`):
- `uart.py` — DTR reset + U-Boot prompt drive
- `tftp/` — TFTP serve dir (this script stages its outputs there)
- `h3600_nand_full.bin` — factory NAND dump (recovery source)

## Quick reference

```sh
# Build + flash patched slot A:
./prepare_slot_a.sh --write

# Restore factory slot A:
python3 flash_slot_a_RECOVERY.py

# Diagnostic flash with factory bytes (useful to bisect flash issues):
python3 flash_slot_a_ISOLATION.py
```

## Pending sub-tasks (in this folder)

1. **Userspace kmsg → UART daemon** — tiny C program that drains
   `/dev/kmsg` and writes each byte to `devmem2 0x94404004` (the
   ZTE-shifted DR). Approach (A) from the playbook. Easiest first win.
2. **Bake daemon into slot A rootfs** — drop binary in `/sbin/`,
   start from `/etc/rc` or via `init.norm`.
3. **(Stretch)** RE the stock kernel `pl011_console_write` and patch
   DR offset from +0x00 to +0x04 — would give true console output
   including early-boot printks the daemon would miss.

## Discoveries

See `../../docs/SLOT_A_CSPD_PATCH_PLAYBOOK.md` for the canonical
discovery log (8 sections, post-mortem of what we learned the hard way).
Short version:
- `csp_crc` is `zlib.crc32` but the U-Boot log prints `(value, ~value)`.
- The lenient JFFS2-magic path is the contract — strict CRC never matches.
- `mkfs.jffs2 --devtable=...` is mandatory; without device nodes, silent boot hang.
- `logctrl -g 3` is `logger | printf`, NOT "all" as the help claims.
- Kernel `printk` silencing is HW-software mismatch: stock kernel writes
  to standard PL011 DR=+0x00 but ZTE PL011 has DR at +0x04.

## Related

- `docs/SLOT_A_CSPD_PATCH_PLAYBOOK.md` — full discovery doc
- `docs/NAND_LAYOUT_AND_BOOT.md` — partition map + cspstart flow
- `docs/NAND_PERSISTENCE_PLAN.md` — mainline-kernel slot-A flash (sister approach)
- Memory: `h3600_slot_a_custom_rootfs_recipe.md`, `h3600_kernel_boot_recipe.md`
