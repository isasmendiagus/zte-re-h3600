# flash-tool — unified NAND flasher (cspstart-aware + free-form)

**ID**: 00.04
**Parent**: [00 openwrt-port](../00.openwrt-port/)
**Children**: [00.04.01 tftp-port-probe](../00.04.01.tftp-port-probe/), [00.04.02 uart-bridge](../00.04.02.uart-bridge/)
**TaskList items**: #29
**Status**: ✅ DONE — usable for kernel/rootfs/both/header/raw. UART-over-TCP bridge (00.04.02) at PoC stage; integration into `flash.py` via `UART_TCP=1` env-var is task #29.

## Primer: what is cspstart, and why does any of this matter?

If you're reading this without context, the rest of the doc throws around
`cspstart`, `BootPara`, `slot A`, `csp_crc` etc. as if they were standard
terms. They aren't — they're ZTE-specific. Here's the minimum you need
before the next section makes sense:

**1. There are three "headers" on this device. Don't confuse them.**

| Header | Where | Built by | Read by | Purpose |
|---|---|---|---|---|
| **uImage header** | first 64 bytes of any U-Boot image | `mkimage` | U-Boot's `bootm` | "load this image at X, jump to Y" — standard U-Boot |
| **ZTE wrapper** | 32 bytes prepended to the uImage before NAND write (`33 33 33 33 cc cc cc cc 88 88 88 88 dd dd dd dd ff*16`) | the build step (e.g. `build_slotA.py`) | cspstart's NAND scan — uses this magic to *locate* the kernel | "kernel starts here" marker |
| **BootPara header** ← this is the one this tool maintains | 128 KiB separate NAND partition at `0x2080000` (slot A) or `0x4080000` (slot B) | this flash tool | cspstart | catalog card: where the kernel is, how big, what CRC, what rootfs goes with it, header self-CRC |

**2. `cspstart` is a ZTE-custom U-Boot command, not a separate boot stage.**

The boot chain on this device is:

```
SoC mask ROM → U-Boot (ZTE fork) → cspstart command runs inside U-Boot
                                   ↓
                                   scans NAND for the ZTE wrapper magic
                                   reads BootPara header A (and B)
                                   validates each (kernel CRC strict, rootfs CRC lenient)
                                   picks the best valid slot
                                   bootm's the kernel from RAM
                                   ↓
                                   Linux kernel runs
```

cspstart is what enforces ZTE's A/B firmware-update scheme. If slot A's
header says "my kernel CRC is X" and the actual kernel bytes don't CRC
to X, cspstart silently rejects slot A and falls back to slot B. That's
why slot B is the recovery fallback we never touch.

**3. `csp_crc` is just `zlib.crc32`, with one log-output gotcha.**

cspstart's `csp_crc` function = standard `zlib.crc32` (CRC32 IEEE).
But its log output prints **both** the computed value AND its bitwise
complement: `crc=0x89d932df, 0x7626cd20` (these are `~X` of each other).
The value **stored** in the header is the un-complemented one (matches
what Python's `zlib.crc32` returns). We've burned a day on this gotcha
twice in this project — see `LEARNED.md`.

**4. Why this tool exists.**

To flash slot A successfully, you must:

1. Write your bytes (kernel and/or rootfs) to the right NAND offsets
2. Pad them with `0xff` to NAND-erase-block multiples (a gotcha that
   bit the project twice — without the pad, `nand write` includes RAM
   garbage and CRCs mismatch)
3. Read the BootPara header from the NAND dump, patch only the field(s)
   that describe what you just changed (kernel size, CRC, rootfs CRC),
   recompute the header's self-CRC at offset `0xa4`
4. Write the patched header alongside your content
5. Drive U-Boot via UART (DTR-reset, prompt-wait, send commands in order,
   handle slow TFTP, etc.)

Steps 1–5 happen for *every single flash*. They're tedious, easy to get
wrong, and a single wrong CRC = device boots stock instead of your build
with **no error message**. This tool encapsulates all five steps into
one CLI.

The tool also offers an **escape hatch (Tier 2: `raw`)** for cases where
you don't want cspstart in the loop at all — e.g., OpenWRT installs that
use squashfs+UBIFS at custom NAND offsets. In Tier 2 there's no header
dance because cspstart is no longer the gatekeeper; a custom `bootcmd`
is. The next section explains the two-tier split.

---

## The key idea: two tiers, you pick based on whether you want cspstart in the loop

```
┌─ Tier 1: cspstart-aware ─────────────────┬─ Tier 2: free-form ────────────┐
│                                          │                                 │
│   kernel | rootfs | both | header        │   raw                           │
│                                          │                                 │
│   Maintains cspstart's BootPara contract │   Writes any file to any        │
│   (CRC math, header patching, slot A     │   NAND offset. No header, no    │
│   semantics). A/B recovery preserved.    │   CRC, no slot concept.         │
│                                          │                                 │
│   Use for:                               │   Use for:                      │
│   - Stock firmware restore               │   - OpenWRT-style custom        │
│   - Stock + kernel/rootfs tweaks         │     layouts (squashfs + UBIFS   │
│     (e.g. enable UART, recompute CRCs)   │     at non-cspstart offsets)    │
│   - Our own kernel via cspstart          │   - Anything else that needs    │
│     (mainline, kernel+initramfs, etc.)   │     full-NAND flexibility       │
│                                          │                                 │
└──────────────────────────────────────────┴─────────────────────────────────┘
                          │                              │
                Bootloader region (0x0..0xc0000)         │
                forbidden in BOTH tiers (brick risk).    │
                                                         │
                Slot B sacred in Tier 1                  │
                (recovery fallback);                     │
                                                         │
                                          Slot B optional in Tier 2 (no slot
                                          concept exists — whole NAND is
                                          fair game minus the bootloader).
```

You don't pick subcommands — you pick a **tier**. The tier is determined by
the answer to one question: **"do I want cspstart to validate and boot this
slot at next reboot?"**

- **Yes** → Tier 1. The tool handles BootPara CRC math so cspstart accepts
  your write. Slot A is the default; you never need to type `--slot`.
- **No** → Tier 2. The tool writes bytes wherever you say. cspstart's slot
  selection still runs at boot but won't find what it expects (you've
  presumably also rearranged things), so you're committing to a custom
  bootcmd setup. Slot B's physical region becomes just more NAND space.

```
python3 tasks/00.04.flash-tool/flash.py \
    {kernel|rootfs|both|header|raw} --src FILE \
    [--offset 0xN]   # raw only
    [--slot A|B] [--allow-slot-b]  # Tier 1 only; you almost never need these
    [--dry-run] [--tftp-dir DIR] [--nand-dump FILE]
```

Lives entirely inside this task folder — per CLAUDE.md's "rule of two",
task-local until a second consumer materializes. Promotion candidates when
that happens: `nand_layout.py` → `lib/`, `bootpara.py` → `lib/`, CLI to
`tools/`.

---

## Scope: producer vs. consumer

This tool is the **consumer** end of the pipeline.

- **Consumes**: prepared binary inputs (a kernel binary with its ZTE wrapper +
  uImage header already baked in; a rootfs binary already AES-128-ECB
  encrypted if the slot calls for it).
- **Produces**: bytes on NAND + a patched BootPara header so cspstart accepts
  the slot at next boot.

The **producer** side stays where it lives today — `build_slotA.py` for
mainline kernel wrapping, `prepare_slot_a.sh` for the custom rootfs
encryption pipeline. The flash tool trusts whatever bytes it's handed.

This split mirrors the existing `flash_slot_a_RECOVERY.py` pattern (which
just flashes bytes from `ext/h3600_nand_full.bin`) rather than the
`build_slotA.py` + `flash_mainline.py` pattern (which couples build + flash).

---

## Subcommands

### `kernel --src FILE`

Flashes a kernel binary to slot A's kernel region.

1. Pads `--src` with `0xff` to a NAND erase-block multiple.
2. Computes `kernel_crc = zlib.crc32(padded)`.
3. Reads the slot's BootPara header from `ext/h3600_nand_full.bin`.
4. Patches `kernel_size` (0x34), `kernel_crc` (0x3c), and `self_crc` (0xa4).
   Leaves board name, magics, slot B fields, etc. untouched.
5. Drives U-Boot via UART to: TFTP kernel → erase + write kernel region →
   TFTP header → erase + write header region → reset.

CRC scope: covers `[kernel_offset + 32 : kernel_offset + 32 + kernel_size]`
— i.e. **skip the 32-byte ZTE wrapper, then CRC exactly `kernel_size` bytes**.
The tool therefore sets:

```
kernel_size = padded_total - 32           (region cspstart will read)
kernel_crc  = zlib.crc32(padded[32:])     (matches what cspstart will compute)
```

This was verified against the stock NAND dump on 2026-05-23:
`zlib.crc32(ext/h3600_nand_full.bin[0x700020 : 0x700020 + 0x35fdcc])`
= `0x2fedcd6d`, exactly the value stored in header A's `0x3c` field.

Note: this contradicts `tasks/00.01.eth-driver/scripts/build_slotA.py`,
which CRCs the full padded region *including* the wrapper. That script's
inline comment claims to have verified its choice from a U-Boot
`verify_kernel readflash @0x700000` log — but that log only shows where
the NAND read starts, not the CRC scope. The byte-level math on the stock
dump is unambiguous: wrapper is excluded.

This also matches `docs/NAND_LAYOUT_AND_BOOT.md` line 177 (which says CRC
excludes the wrapper). The earlier interpretation in `build_slotA.py` is
the doc bug; the byte-level verification is authoritative.

### `rootfs --src FILE`

Flashes a rootfs binary to slot A's rootfs region.

1. Pads `--src` to `slot.rootfs_size` (`0x1620000`) with `0xff` if smaller.
2. Computes `rootfs_crc = zlib.crc32(padded)`.
3. Reads header from NAND dump, patches `rootfs_crc` (0x48) + `self_crc`.
4. Flashes rootfs + header.

Note: cspstart's rootfs CRC check is **lenient** — even on CRC mismatch,
cspstart accepts the slot if the decrypted view at `mtdblock` shows the
JFFS2 magic (`85 19 01 e0`). For AES-encrypted slots, `--src` MUST be
pre-encrypted; this tool does not encrypt.

### `both --kernel FILE --rootfs FILE`

Single U-Boot session, single header patch covering both `kernel_size`/
`kernel_crc` AND `rootfs_crc`. Use when flashing a fully-coordinated build
(e.g. a stockport image where the kernel and rootfs go together).

### `header --src FILE`

Writes the given file as-is to the slot's header region. No patching, no
CRC math. For surgical use:

- restoring a known-good header from a backup,
- writing a hand-crafted header for experimentation,
- replaying a header staged by a previous `--dry-run`.

The file must be exactly `slot.header_size` bytes (`0x20000`).

### `raw --offset 0xN --src FILE` *(Tier 2)*

Writes any file to any NAND offset. No header involvement, no CRC math,
no slot concept. The escape hatch for custom layouts.

1. Pads `--src` with `0xff` to a NAND erase-block multiple.
2. `nand erase` + `nand write` at `--offset`.
3. That's it — nothing else touched.

Safety:
- Bootloader region (`0x0..0xc0000`) is **unconditionally forbidden**
  (brick risk).
- Slot B's physical region is **allowed without opt-in** — the whole
  point of `raw` is full-NAND flexibility. A warning is printed but the
  write proceeds.
- `--offset` must be NAND-erase-block aligned (`0x20000`).

Typical OpenWRT-style use:
```bash
flash.py raw --offset 0x4100000 --src openwrt-kernel.bin
flash.py raw --offset 0x4d00000 --src openwrt-rootfs.squashfs
flash.py raw --offset 0x6100000 --src openwrt-overlay.ubi
# Paired with a script-as-kernel in slot A to satisfy cspstart:
flash.py kernel --src openwrt-loader-script.bin
```

---

## Safety guards (enforced in `uboot_flash.py`)

| Rule | Behavior | Applies to |
|------|----------|------------|
| Never write the bootloader (`0x0..0xc0000`) | hard reject — raises immediately | both tiers |
| Never write slot B without opt-in | reject unless `--allow-slot-b` is passed | Tier 1 only |
| Slot B write proceeds (with warning) | for `raw` only — no opt-in needed | Tier 2 |
| Write must fit within NAND end (`0x08000000`) | hard reject | both tiers |
| Offset must be NAND-erase-block aligned (`0x20000`) | hard reject | `raw` |
| `--dry-run` | stages files to TFTP dir, prints commands, does NOT open UART | both tiers |

---

## File layout (all in this task folder)

```
tasks/00.04.flash-tool/
├── README.md          (this file — design notes + recipe)
├── flash.py           CLI: argparse, subcommands, stages files into tftp/
├── nand_layout.py     constants: slot layouts, header field offsets, NAND geometry
├── bootpara.py        pure-function header patching (no I/O): read/patch/CRC
├── build_rootfs.py    generic mkfs.jffs2 + AES-128-ECB wrapper with LOUD size-overflow
│                      check (mkfs.jffs2 will silently truncate when --pad is exceeded —
│                      this script refuses to build past 100 % and warns under 5 %)
└── uboot_flash.py     U-Boot driving over UART; safety guards; WriteStep dataclass
```

`build_rootfs.py` is the canonical builder. Run standalone:

```
python3 tasks/00.04.flash-tool/build_rootfs.py \
    --staging tasks/00.02.stock-shell/staging \
    --devtable tasks/00.02.stock-shell/devtable.txt \
    --out my_rootfs_enc.jffs2
```

The per-task wrapper `tasks/00.01.eth-driver/kotrace/build_rootfs_with_kotrace.py`
prepares the staging (drops kotrace.ko + netshell + patches init.norm) and
then runs the same mkfs+AES sequence inline. Either path produces an
identical bit-for-bit image (verified 2026-05-26).

`bootpara.py` has no UART dependency and is unit-testable on a NAND dump
alone. `uboot_flash.py` imports `uart` from the shared `lib/` directory
(the one stable lib this tool depends on).

`flash.py` adjusts `sys.path` at startup so:
- siblings (`nand_layout`, `bootpara`, `uboot_flash`) are importable
- shared `lib/uart.py` is importable

---

## What this tool deliberately does NOT do

- Build kernel/rootfs from source (stays in `build_slotA.py` /
  `prepare_slot_a.sh`)
- Wrap a uImage with the 32-byte ZTE magic (it's part of the input bytes)
- Run `mkimage` (input is already uImage-shaped)
- AES-encrypt rootfs (input is already encrypted if needed)
- RAM-only `bootm` (lives in `lib/uart.py auto_bootm_dtb_appended`)
- Touch the bootloader (brick risk — refused in both tiers)
- Tier 1 only: touch env, tag, wifi-cal, usercfg, defcfg, or slot B without
  opt-in. Tier 2 (`raw`) allows all of these — by design, since the whole
  point is full-NAND flexibility for custom layouts.

---

## RAM-only `bootm` vs NAND-persistent flash (the two programming modes)

This tool only does NAND-persistent writes. The other mode — RAM-only
`bootm` of a kernel without touching NAND — is a separate mechanism that
lives in `lib/uart.py`. Pick the right mode for the situation:

| Mode | What it does | Iter cycle | Use for |
|---|---|---|---|
| **RAM-only `bootm`** (`lib/uart.py auto_bootm_dtb_appended`) | DTR-reset → drive U-Boot → TFTP kernel into RAM at `0x42000000` → `bootm`. NAND is **not** modified; reboot reverts to whatever's in slot A. | ~3 min (TFTP dominates) | **Driver development** — change driver code, rebuild kernel, test instantly without risking NAND state. |
| **NAND-persistent** (this tool) | TFTP into RAM, then `nand erase` + `nand write` to the chosen NAND region. Optionally also writes a coherent BootPara header (Tier 1) so cspstart picks it up on every reboot. | ~3-5 min (TFTP + erase + write × N) | **Shipping a build**, **letting the device run unattended**, or any case where the change must survive a power-cycle. |

Don't reach for NAND-persistent flash when iterating on driver code —
that's wasted erase cycles and slower per iteration.

---

## DTR-pin hardware mod (how every script auto-resets the device)

The FTDI USB-to-UART cable used with this device has its **DTR pin wired
to a small relay that controls device power**. Scripts toggle DTR via
pyserial to power-cycle the modem automatically:

- `DTR = True`  → relay OPEN  → device **powered off**
- `DTR = False` → relay CLOSED → device **powered on**

`lib/uart.py::dtr_reset()` implements the cycle (DTR-True for 2s, then
DTR-False). All `auto_*` entry points and `_do_reset_then` begin with
this, which is why no manual power-cycle is needed between iterations.

**If you don't have this hardware mod**, the prompt-wait will hang
forever after issuing a reset. Workarounds:
- Comment out the DTR cycle in `lib/uart.py::dtr_reset()` and
  power-cycle manually each iteration
- Build the cable mod per `tools/dtr-mod/README.md`

---

## Sharing UART with concurrent tools — `00.04.02 uart-bridge` (PoC)

Right now `flash.py` opens `/dev/ttyUSB0` exclusively for the entire
flash cycle (TFTP + nand write + ~60 s post-reset boot capture). During
that time any other tool trying to read UART (e.g. a kotrace boot-trace
monitor, an interactive `tio` session) gets `EBUSY`.

The bridge in [`tasks/00.04.02.uart-bridge/`](../00.04.02.uart-bridge/)
solves this. A daemon owns the serial port and re-publishes it over
TCP:
- **`tcp/9999`** — raw UART, bidirectional, multi-client
- **`tcp/9998`** — control plane: `DTR_PULSE`, `DTR_HIGH`, `DTR_LOW`, `STATUS`
- **`/tmp/uart_bridge.log`** — append-only tee for `tail -f` replay

Usage (PoC, not yet wired into flash.py — that's task #29):

```bash
# terminal 1 — start the bridge once per session
python3 tasks/00.04.02.uart-bridge/uart_bridge.py

# terminal 2 — live UART viewer that survives any flash cycle
nc localhost 9999

# terminal 3 — flash WITHOUT competing for /dev/ttyUSB0:
UART_TCP=1 python3 tasks/00.04.flash-tool/flash.py rootfs --src ...
#       ^^^^^^^^ once lib/uart.py is patched per task #29
```

Until task #29 lands, the bridge is useful standalone for live UART
monitoring during ad-hoc debugging.

---

## Recovery scenarios

What to do when something goes wrong. Slot B is intact by default (Tier 1
respects it), so the device is **unbrickable from user-space NAND writes**
as long as you stay in Tier 1.

| Symptom | Recover with |
|---|---|
| Slot A is broken (bad kernel, hung boot) but `=>` prompt reachable | `flash.py kernel --src <slice of stock kernel from ext/h3600_nand_full.bin>` |
| Slot A rootfs corrupted | `flash.py rootfs --src <slice of stock rootfs from ext/h3600_nand_full.bin>` |
| Slot A entirely garbage | `flash.py both --kernel <slice> --rootfs <slice>` |
| Boot ROM hangs before U-Boot prompt | External SPI flasher needed (you've trashed bootloader region — shouldn't happen if you used this tool) |
| In a custom (Tier 2) layout, your custom bootcmd is broken | Drop into U-Boot prompt, `env default -a; saveenv; reset` — cspstart will resume validating slot B and boot stock |

In normal operation, you'd never hit any of these — cspstart auto-falls-back
to slot B if slot A fails validation.

---

## Operational pre-flight checklist

Before any real (non-`--dry-run`) flash:

```sh
# 1. TFTP daemon is running and serving the project's tftp/ dir
ps -ef | grep tftpd | grep -v grep
# Expected:  in.tftpd ... -a 192.168.1.50:69 /home/ubuntu/Projects/MYSELF/ZTE/tftp

# 2. No stale process holds /dev/ttyUSB0
lsof /dev/ttyUSB0 2>/dev/null
# Expected: empty

# 3. The source file you're flashing actually exists and is the right shape
ls -la <your --src path>

# 4. Device is reachable: either at U-Boot prompt already, or DTR cable wired
#    for auto-reset (the FTDI hardware mod above)
```

If the TFTP daemon path is stale (e.g., points at the pre-rename
`H3600/tftp` path), restart it:

```sh
sudo pkill -f 'in.tftpd' && \
  sudo in.tftpd -L --secure --create -a 192.168.1.50:69 \
       /home/ubuntu/Projects/MYSELF/ZTE/tftp
```

---

## See also

- `docs/NAND_LAYOUT_AND_BOOT.md` — full RE'd header layout + boot flow (Spanish; the authoritative narrative reference)
- `docs/ARCHITECTURE.md` — hardware reference (PL011, NAND, AES, CRC algorithms)
- `LEARNED.md` — past bugs (0xff padding, CRC complement, TFTP timeout)
- `lib/uart.py` — the UART driver + `_do_reset_then` we build on
- `tools/dtr-mod/README.md` — how the DTR cable mod is built
