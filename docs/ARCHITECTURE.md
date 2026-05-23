# ARCHITECTURE — what's actually in the hardware

The single source of truth for **what the silicon looks like**, so we
don't keep rediscovering it. Most of these are "ZXIC's design is
ALMOST standard but with one twist that bites you" — get the twist
right once, write it down once.

## SoC overview

- **ZTE ZXIC ZX279128S** — proprietary GPON+switch+CPU SoC.
- **CPU**: ARM Cortex-A9 dual-core @ 1 GHz, ARMv7.
  - **No VFP enabled** despite the Cortex-A9 family normally having it.
    Any hard-float binary SIGILLs on first VFP instruction.
    → see `LEARNED.md` "kernel panic exitcode=0x4".
- **RAM**: 256 MiB DDR @ phys `0x40000000`.
- **NAND**: 128 MiB SPI NAND (ESMT F50L1G41LB)
  - 2 KiB page, 128 KiB erase block, 64 B OOB.
  - Accessed via SPIFC, mapped via mtd at startup.
- **PHY**: integrated GPHY blocks per LAN port + GPON SerDes for uplink.
- **PCIe**: 2× host controllers (`0x10000000`, `0x20000000`) — one for the
  on-board MT7915 WiFi card.

## PL011 UART — the twist

This is standard ARM PrimeCell PL011 **with shifted register offsets**:

| Reg   | Standard PL011 | ZTE-shifted | Notes |
|-------|----------------|-------------|-------|
| DR    | `+0x00`        | **`+0x04`** | data — writes here transmit |
| FR    | `+0x18`        | **`+0x14`** | flags (BUSY, TXFF, RXFE) |
| IBRD  | `+0x24`        | `+0x24`     | integer baud divisor (matches standard) |
| FBRD  | `+0x28`        | `+0x28`     | fractional baud (matches standard) |
| LCR_H | `+0x2C`        | `+0x2C`     | line control (matches standard) |
| CR    | `+0x30`        | `+0x30`     | control (matches standard) |
| IMSC  | `+0x38`        | `+0x38`     | interrupt mask (matches standard) |

**Implications**:
- Standard pl011 driver writes to DR at `+0x00` → completely silent on this hardware
  (because the real DR is at `+0x04`).
- The stock 4.1.25 kernel ships an unpatched pl011 driver → kernel printk silent
  → that's why we built `kmsg2uart` to bridge `/proc/kmsg` to DR at `+0x04` via `/dev/mem`.
- Mainline 6.6 with `CONFIG_ARCH_ZX=y` handles the shift correctly via
  `arch/arm/include/debug/pl01x.S` and the mach-zx DT setup.

UART base addresses (per `/proc/iomem`):

- `0x94404000` — `serial0` (the console UART — DTR-resettable via FTDI cable)
- `0x94405000` — `serial1` (user-line / second UART)

## NAND layout

See `docs/NAND_LAYOUT_AND_BOOT.md` for the full map. Short version:

| Offset      | Size       | Contents |
|-------------|------------|----------|
| `0x000000`  | `0xc0000`  | **bootloader (U-Boot)** — NEVER touch, brick risk |
| `0x0c0000`  | `0x40000`  | env |
| `0x100000`  | `0x100000` | tag |
| `0x300000`  | `0x400000` | usercfg / defcfg / wlan (encrypted) |
| `0x700000`  | up to ~25 MiB | **slot A kernel** (uImage with 32-byte ZTE wrapper) |
| `0xa60000`  | `0x1620000` | **slot A rootfs** (AES-128-ECB encrypted JFFS2) |
| `0x2080000` | `0x20000`   | **slot A BootPara header** (CRC stored here) |
| `0x2700000` | … | **slot B kernel** (factory stock, fallback) |
| `0x2a60000` | `0x1620000` | **slot B rootfs** |
| `0x4080000` | `0x20000`  | **slot B header** |

## BootPara header

128 KiB at `0x2080000` (slot A) and `0x4080000` (slot B). Key fields:

- `header[0x34..0x38]` — kernel size in CRC region (LE u32)
- `header[0x3c..0x40]` — kernel CRC (LE u32)
- `header[0x48..0x4c]` — rootfs CRC (LE u32)
- `header[0xa4..0xa8]` — self CRC over `header[0..0xa4]`
- `header[?]` — flags (`0xa3` = "boot me", `0x00` = "fallback")

## csp_crc — the U-Boot CRC

ZTE U-Boot logs `csp_crc:103 ... crc=<A>, <B>` — **both are derivatives**
of the SAME `zlib.crc32` (standard IEEE 802.3 CRC-32):

- `A` = computed CRC (= `zlib.crc32(data) & 0xffffffff`)
- `B` = `A ^ 0xffffffff` (the bitwise complement, printed for visual confirmation)

When patching a header CRC, store `A` (the un-complemented value) at the
appropriate header offset. The kernel-CRC verify is **strict** (must
match exactly). The rootfs-CRC verify falls through to a **lenient JFFS2
magic check** if strict CRC mismatches — that's why custom rootfs builds
"just work" despite imperfect CRCs.

See `LEARNED.md` "csp_crc doesn't match zlib.crc32(data)" + `tools/find_csp_crc.py`.

## AES rootfs encryption

JFFS2 rootfs partition is **AES-128-ECB encrypted**:

- Key: `H36000e71071c440` (16 ASCII bytes — per-unit, derived for this
  particular H3600).
- Direct openssl round-trip works:
  `openssl enc -aes-128-ecb -K $(printf %s "H36000e71071c440" | xxd -p) -nopad`.

The mtd driver's `mtdblock8` exposes the DECRYPTED view; raw `mtd0` shows
ENCRYPTED bytes. csp_crc is computed over the **encrypted** bytes (NAND raw).

See memory `aes_key_discovered` for derivation algorithm.

## ZTE kernel wrapper (uImage prefix)

Slot A kernel image starts with a **32-byte ZTE wrapper**:

```
33 33 33 33 cc cc cc cc 88 88 88 88 dd dd dd dd ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff
```

Then the standard U-Boot uImage header (64 bytes) starts at offset `+0x20`.

When the kernel boots: `bootm 0x42020020` (skip the wrapper).

The wrapper has no semantic function we've found — it's just a magic
signature cspstart looks for. The CRC computation INCLUDES the wrapper.

## TM / Switch / PP / IDM register blocks

The eth-driver work touches multiple register blocks at runtime — see
`tasks/00.01.eth-driver/ETHERNET_DRIVER_DESIGN.md` for the full table. Key
bases (mapped via DT):

| Block | Base | Purpose |
|-------|------|---------|
| MAC0..3 | `0x921c0000 + (i+1)*0x40000` | per-port MAC config |
| IDM    | `+0x008000` (rel base) | descriptor rings, RX/TX kick |
| PP     | `+0x100000` | Packet Processor |
| TM     | `+0x180000` (`0x92340000` abs) | Traffic Manager + BMU + DMA |

## Hardware quirks summary

- **Hard-float SIGILL** on no-VFP Cortex-A9 → use soft-float toolchain.
- **PL011 DR at `+0x04`** not `+0x00` → standard pl011 driver silent.
- **Stock kernel: `# CONFIG_KPROBES is not set`** → can't trace via debugfs.
  Only path: binary-patch `.ko` to inject `printk`.
- **cspd 3-byte patch was a red herring** for UART — the real fix was
  bridging `/proc/kmsg` to PL011 DR via `kmsg2uart` daemon.
- **U-Boot's `csp_crc` is `zlib.crc32`**, log prints `(value, ~value)`.
- **`bootm` takes ONE arg only on ZTE U-Boot** — DTB must be appended
  to zImage (`CONFIG_ARM_APPENDED_DTB=y`), not passed as 3rd `bootm` arg.

## See also

- **`tasks/00.03.nand-flash/README.md`** — the **NAND layout + flash recipes
  bundled together**. If you're about to write to NAND, read THAT first
  (it has the operational checklist + every flash script's role).
- `docs/NAND_LAYOUT_AND_BOOT.md` — full NAND map + cspstart boot flow
- `docs/SLOT_A_CSPD_PATCH_PLAYBOOK.md` — how the cspd / kmsg2uart story unfolded
- `docs/CROSS_COMPILE_GUIDE.md` — toolchain choices for this hardware
- `docs/STOCK_DEBUG_INFRASTRUCTURE.md` — stock /proc/zte/sys/... debug surfaces
- Memory: `[[h3600-kernel-boot-recipe]]`, `[[aes_key_discovered]]`,
  `[[h3600-slot-a-custom-rootfs-recipe]]`
