# nand-flash — NAND memory layout + all flash recipes

**ID**: 00.03
**Parent**: [00 openwrt-port](../00.openwrt-port/)
**Children**: none — doc-only task (no scripts of its own; indexes scripts that live in sibling tasks)
**TaskList items**: none directly
**Status**: REFERENCE — read before any NAND write.

**Single source of truth for: NAND offsets, header CRC math, all the
flash scripts. Don't read the scripts without reading this first.**

This task folder doesn't contain scripts directly — they're scattered
where they're used (per task). This README is the **index + the rules
the scripts MUST obey**. Each flash script's header docstring also
embeds the layout for self-containment.

---

## NAND memory layout (128 MiB SPI NAND)

```
phys offset    size       contents                          rule
─────────────────────────────────────────────────────────────────────────────
0x00000000     0xc0000    bootloader (U-Boot)               ★ NEVER TOUCH — brick risk
0x000c0000     0x40000    env                               (saveenv overwrites here)
0x00100000     0x100000   tag (versioninfo etc)             readonly via cspstart
0x00300000     0x100000   usercfg (jffs2)                   per-device config (encrypted)
0x00400000     0x100000   defcfg (jffs2)                    factory defaults
0x00500000     0x200000   wlan (jffs2)                      WiFi calibration
─────────────────────────────────────────────────────────────────────────────
0x00700000     0x1900000  ← SLOT A kernel region (25 MiB)   write up to ~11 MiB; rest 0xff
0x00a60000     0x1620000  ← SLOT A rootfs (22 MiB JFFS2)    AES-128-ECB encrypted
0x02080000     0x20000    ← SLOT A BootPara header (128 K)  CRC stored here
─────────────────────────────────────────────────────────────────────────────
0x02700000     0x1900000  ← SLOT B kernel (factory stock)   ALWAYS LEAVE INTACT — recovery
0x02a60000     0x1620000  ← SLOT B rootfs (factory stock)
0x04080000     0x20000    ← SLOT B BootPara header (factory)
─────────────────────────────────────────────────────────────────────────────
0x05fc0000     ...        end of useful flash
```

cspstart at boot reads BOTH headers, validates each, picks the
"highest-priority valid" slot. If slot A is broken (bad header CRC OR
bad kernel CRC) it falls back to slot B. **Slot B is our safety net** —
DO NOT MODIFY IT.

---

## BootPara header structure

128 KiB at slot offset. Critical fields (little-endian u32):

| Offset    | Field             | What it means |
|-----------|-------------------|----------------|
| `0x34`    | kernel_size       | bytes cspstart will CRC starting at kernel offset |
| `0x3c`    | kernel_csp_crc    | `zlib.crc32(kernel_region_padded_with_0xff)` |
| `0x48`    | rootfs_csp_crc    | `zlib.crc32(rootfs_encrypted_jffs2)` |
| `0xa4`    | self_crc          | `zlib.crc32(header[0..0xa4])` |
| `0xa3`    | flags             | `0xa3` = "boot me first", `0x00` = "fallback" |

**When you change kernel content**: must update `0x34`, `0x3c`, `0xa4`.
**When you change rootfs content**: must update `0x48`, `0xa4`.

---

## csp_crc invariants — the gotcha

ZTE U-Boot log: `csp_crc:103 ... crc=<A>, <B>`. **Both A and B are
zlib.crc32 derivatives:**

- `A` = `zlib.crc32(data) & 0xffffffff` (use this)
- `B` = `A ^ 0xffffffff` (printed for visual confirmation only)

**Store `A` in the header**, not `B`. We wasted a day storing `B`
(complement) until we noticed they're the same number presented differently.

**Kernel CRC = strict check.** If `kernel_csp_crc` in header ≠ what
cspstart computes over NAND, slot is rejected.

**Rootfs CRC = lenient fallback.** If `rootfs_csp_crc` mismatches, cspstart
still passes if the JFFS2 magic (`0x85 0x19 0x01 0xe0`) appears in the
decoded mtdblock view. That's why custom rootfs builds "just work" despite
imperfect CRCs.

---

## The padding bug (we've hit this twice — don't make it three)

`nand write 0x42000000 0x700000 0xb00000` writes **0xb00000 bytes** from
RAM. TFTP only loaded the actual file size into RAM — the trailing bytes
are whatever was in RAM before (garbage).

→ NAND ends up with `file_content + RAM_garbage + 0xff (erased)`.
→ CRC computation that assumed `file_content + 0xff` padding mismatches.

**Fix**: pad the source file with `0xff` to exactly the `nand write` size
BEFORE TFTP. Then RAM has clean bytes, NAND has clean bytes, CRC matches.

See `tasks/00.01.eth-driver/scripts/build_slotA.py` header comment for the
full story.

---

## Mainline-kernel flash (slot A KERNEL region)

**What gets written**: our zImage_dtb + 32-byte ZTE wrapper + 0xff padding.
**Target offset**: `0x700000` (slot A kernel).
**Header**: rebuilt with new kernel CRC + size.

Script bundle:

| File | Role |
|------|------|
| `tasks/00.01.eth-driver/scripts/build_slotA.py` | builds `tftp/slotA.bin` + `tftp/header_A_modified.bin` |
| `tasks/00.01.eth-driver/scripts/flash_mainline.py` | drives U-Boot via UART → TFTP → nand erase + write |

Run:
```sh
cd ~/Projects/MYSELF/ZTE/zxic
python3 tasks/00.01.eth-driver/scripts/build_slotA.py
python3 tasks/00.01.eth-driver/scripts/flash_mainline.py
```

---

## Custom-rootfs flash (slot A ROOTFS region — for stock-shell work)

**What gets written**: our patched JFFS2 (cspd modified, kmsg2uart baked in),
AES-128-ECB encrypted with key `H36000e71071c440`.
**Target offset**: `0xa60000` (slot A rootfs).
**Header**: rebuilt with new rootfs CRC.

Script bundle:

| File | Role |
|------|------|
| `tasks/00.02.stock-shell/prepare_slot_a.sh` | builds + (with `--write`) flashes |
| `tasks/00.02.stock-shell/flash_slot_a.py` | the U-Boot driver (called by the .sh) |
| `tasks/00.02.stock-shell/flash_slot_a_RECOVERY.py` | restores factory rootfs from `ext/h3600_nand_full.bin` |
| `tasks/00.02.stock-shell/flash_slot_a_ISOLATION.py` | diagnostic: flash factory bytes (proves flash mechanism, isolates rootfs bugs) |

Run:
```sh
cd ~/Projects/MYSELF/ZTE/zxic/tasks/00.02.stock-shell
./prepare_slot_a.sh --write
```

---

## Header-only re-flash (rare)

If kernel content is already on NAND but you just need to update the header
(e.g. you computed a different CRC):

| File | Role |
|------|------|
| `tools/flash_header_only.py` | TFTP the new header bin + nand-write at `0x2080000` |
| `tools/flash_kernel_to_nand.py` | full kernel-only flash (legacy, prefer `tasks/00.01.eth-driver/scripts/flash_mainline.py`) |

---

## Recovery

If you ever brick slot A:

| Goal | Run |
|------|-----|
| Restore factory rootfs (stock 4.1.25) | `python3 zxic/tasks/00.02.stock-shell/flash_slot_a_RECOVERY.py` |
| Reflash stock-shell custom rootfs (cspd patched + kmsg2uart) | `cd zxic/tasks/00.02.stock-shell && ./prepare_slot_a.sh --write` |
| Boot mainline from RAM (no NAND change) | `python3 zxic/lib/uart.py auto_bootm_dtb_appended` |
| Worst case: device falls back to slot B | nothing to do — cspstart auto-switches |

**As long as slot B is intact, the device is unbrickable from user-space
NAND writes.** That's why every recipe here writes ONLY slot A.

---

## DTR-pin hardware mod (how the scripts auto-reset the device)

The USB-to-UART (FTDI) cable's **DTR pin is wired to a small relay** that
controls device power. The driver scripts toggle DTR via pyserial to
power-cycle the device automatically:

- `DTR = True`  → relay OPEN  → device **powered off**
- `DTR = False` → relay CLOSED → device **powered on**

`uart.py` implements `reset()` as DTR-True for 2s then DTR-False. All the
`auto_*` commands begin with `_do_reset_then(...)` which uses this. That's
why no manual power-cycle is needed between iterations.

**If you don't have this hardware mod**: the `auto_*` scripts will hang
waiting for "first byte detected" after reset. Workaround: comment out the
DTR cycle in `lib/uart.py::reset()` and power-cycle manually each iter.

The relay/DTR wiring is documented in the cable build (not in this repo).
Pin assignments in `lib/uart.py::open_port()`.

---

## The two programming modes (RAM-temporary vs NAND-persistent)

There are **two distinct ways** we get our code running on the device.
Pick the right one for the situation:

### Mode 1: RAM-only (ephemeral) — `bootm` from RAM

- TFTP a kernel image into RAM at `0x42000000`.
- `bootm 0x42000000` jumps to it.
- **NAND is NOT modified.** A reboot reverts to whatever's in NAND slots.
- Iter cycle: ~3 min (TFTP transfer dominates).
- Use for: **driver development** — change driver code, rebuild kernel,
  test instantly without risking NAND state.

Script: `python3 zxic/lib/uart.py auto_bootm_dtb_appended` (calls a sequence
that does DTR reset → drive U-Boot prompt → TFTP `zImage_dtb.uimg` → bootm).

### Mode 2: NAND-persistent — write to slot A, reboot

- TFTP the image into RAM, then `nand erase` + `nand write` to slot A.
- Update the BootPara header with new CRC.
- Reset → cspstart loads from NAND → boots automatically on every power-on.
- Iter cycle: ~5–7 min (TFTP + NAND erase + NAND write × 2).
- Use for: **shipping a build**, **letting the device run unattended**,
  or for **stock-shell** where we want the cspd-patched rootfs persistent.

Scripts (currently separate per-target):
- Kernel persistence: `tasks/00.01.eth-driver/scripts/build_slotA.py` + `flash_mainline.py`
- Rootfs persistence (stock-shell): `tasks/00.02.stock-shell/prepare_slot_a.sh --write`

### Slot A vs Slot B

Currently **every script writes ONLY slot A** by design. Slot B is left as
factory-stock so cspstart can always fall back to a known-good kernel +
rootfs. If you ever want to write slot B (e.g. promote the current slot-A
build to "stable" and use slot A for experiments) we'd need to add a slot
parameter to the scripts. Not done yet — flag a TODO when you need it.

### TODO — unify into one parameterized script

The five flash scripts above have duplicated U-Boot-drive logic. A clean
end-state would be one tool:

```sh
zxic flash --mode=ram|nand --what=kernel|rootfs|both \
           --slot=A|B --src=tftp/slotA.bin [--header=tftp/header.bin]
```

Until that lands, the per-task scripts work. Don't refactor preemptively —
do it next time you'd add a 6th flash script.

---

## Operational checklist before any flash

```sh
# 1. TFTP server is running with the right serve dir
ps -ef | grep tftpd | grep -v grep
# Expected: -a 192.168.1.50:69 .../zxic/tftp

# 2. Required files exist in tftp/
ls -la zxic/tftp/{slotA.bin,header_A_modified.bin}
# For rootfs flash: zxic/tftp/rootfs_a_patched_enc.jffs2, header_a_patched.bin

# 3. No stale process holds /dev/ttyUSB0
pgrep -fa uart\\.py
# Expected: empty

# 4. Device is in U-Boot prompt OR can be DTR-reset (cable wired with DTR)
```

---

## See also

- `docs/ARCHITECTURE.md` — full hardware reference (PL011 shift, NAND
  + BootPara + csp_crc + AES key all in one place)
- `docs/NAND_LAYOUT_AND_BOOT.md` — historical detailed NAND map + cspstart flow
- `docs/NAND_PERSISTENCE_PLAN.md` — older walkthrough of slot-A persistence
- `LEARNED.md` — recurring bugs (padding, CRC complement confusion, etc.)
- `tasks/00.02.stock-shell/ITERATIONS.md` — chronological notes on 8 flash iterations
