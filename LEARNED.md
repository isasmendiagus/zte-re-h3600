# LEARNED — symptom-keyed catalog of recurring problems

**Read this before you debug anything.** Every entry is a problem we've
hit at least twice. Search by symptom (the thing you observe) to find
the cause and the fix.

> Add a new entry the FIRST time you've spent more than 30 minutes on
> something that turns out to be a problem you've already solved. Don't
> bury new findings in `CHRONICLE.md` only — entries here are what
> actually saves time.

---

## Symptom: kernel panic `Attempted to kill init! exitcode=0x4` on mainline 6.6 boot
**Cause**: busybox binary is hard-float (Tag_ABI_VFP_args: VFP registers),
but the Cortex-A9 in this SoC has **no VFP unit enabled**. busybox `sh` as
PID 1 hits a VFP instruction during init → kernel sends SIGILL → exit
code 0x4 = signal 4.
**Symptom variants:**
- `Comm: sh exitcode=0x4`
- `Comm: busybox exitcode=0x4`
- `Comm: init exitcode=0x4` (when shebang failed)
- Same busybox FORKED as child (insmod, ip) works fine — only PID-1 paths SIGILL.
**Fix**: rebuild busybox with `gcc-arm-linux-gnueabi` (soft-float, NOT `-hf`)
+ `CONFIG_STATIC=y`. Verify with `arm-linux-gnueabi-readelf -A busybox`
must show **no** `Tag_FP_arch` or `Tag_ABI_VFP_args`.
**Reference**: `CHRONICLE.md` Cap 10 (2026-05-02), rediscovered 2026-05-22.
**Cost when not known**: 2 hours/iteration.
**Workaround if you can't rebuild now**: use a static C binary as PID 1
that forks busybox per command (see `tasks/00.01.eth-driver/initramfs/init.c`).

---

## Symptom: kernel panic `Attempted to kill init! exitcode=0x0` (clean exit)
**Cause**: `exec /bin/sh` in /init without `< /dev/console > /dev/console 2>&1`
redirect. The new shell has no stdin → reads EOF → exits 0.
**Fix**: explicit redirect:
```sh
exec /bin/sh < /dev/console > /dev/console 2>&1
```
PID 1 cannot exit; if it does, kernel panics. Both `exitcode=0x4` (SIGILL)
and `exitcode=0x0` (clean exit) trigger the same panic.
**Reference**: `CHRONICLE.md` Cap 10.

---

## Symptom: slot A flash CRC mismatch after `nand write` (Real != Want)
**Cause**: `nand write 0xb00000` writes 0xb00000 bytes from RAM. TFTP
only loaded the actual file size into RAM — the trailing bytes are
**RAM garbage** from boot. Our CRC computation assumed `0xff` padding,
so the CRC differs from actual NAND content.
**Fix**: pad slotA.bin to exactly the `nand write` size with `0xff` BEFORE
TFTP. Both NAND and our computation now match.
```python
data = wrapper + uimg
data += b"\xff" * (NAND_WRITE_SIZE - len(data))  # explicit pad
```
**Reference**: `tasks/00.01.eth-driver/scripts/build_slotA.py` header comment.
**Cost**: 3 reflashes ≈ 15 min/iteration.

---

## Symptom: `flash_mainline.py` flashes header but NOT kernel — slot A rejected
**Cause**: `cmd_auto_bootm_dtb_appended` waits 45s after `tftp slotA.bin`.
But TFTP at ~150 KB/s for 11 MiB takes ~75s. After 45s the script sends
`nand erase` mid-TFTP — U-Boot silently drops it. Then `nand write` is
sent, also dropped. Then `tftp header` works (small). So header gets
flashed pointing at OLD kernel content.
**Fix**: bump TFTP wait to 180s (in `tasks/00.01.eth-driver/scripts/flash_mainline.py`
CMDS list, value next to `tftp 0x42000000 slotA.bin`).
**Reference**: `flash_mainline.py` comment block.
**Cost**: 2 wasted boot cycles ≈ 8 min.

---

## Symptom: dynamic-linked C binary says `not found` on stock device
**Cause**: cross-compiler default uses glibc dynamic linker `/lib/ld-linux.so.3`.
Device has uClibc 0.9.33.2 with `/lib/ld-uClibc.so.0`. Linker missing → not found.
**Fix**: always cross-compile static (`-static`) OR build against uClibc-arm.
**Reference**: `docs/CROSS_COMPILE_GUIDE.md`.

---

## Symptom: kernel printk works but userspace `echo > /dev/console` is silent (stock kernel only)
**Cause**: stock 4.1.25 kernel's pl011 TTY TX writes to standard DR offset
(`+0x00`). ZTE-shifted PL011 has DR at `+0x04`. Writes to `+0x00` no-op.
Mainline 6.6 with `CONFIG_ARCH_ZX=y` handles this correctly.
**Fix on stock kernel**: `kmsg2uart` daemon (`tasks/00.02.stock-shell/kmsg2uart.c`)
that reads `/proc/kmsg` + writes to DR at `+0x04` via `/dev/mem` mmap.
**Reference**: `docs/SLOT_A_CSPD_PATCH_PLAYBOOK.md` §5.

---

## Symptom: csp_crc doesn't match `zlib.crc32(data)`
**Cause**: ZTE U-Boot's `csp_crc:103` log prints `(value, ~value)` — both
derive from the SAME standard `zlib.crc32`. The "value" printed first is
the computed CRC; the second is its bitwise complement (`^ 0xffffffff`).
**Fix**: when interpreting boot logs, ignore the second number — it's
just `~CRC` for visual confirmation. Store `zlib.crc32(data) & 0xffffffff`
in header offset `0x3c` (kernel) or `0x48` (rootfs).
**However**: even with correct CRC, slot-A rootfs uses **lenient JFFS2
magic detection** (`use defualt jffs2 fs!!` path) — strict CRC match is
optional for rootfs. Kernel CRC IS strict.
**Reference**: `docs/SLOT_A_CSPD_PATCH_PLAYBOOK.md` §1, `tools/find_csp_crc.py`.

---

## Symptom: shell + driver work, but `live_load_mod` can't find `~ #` prompt
**Cause**: our C-init's REPL uses `#` as prompt (NOT `~ #` like busybox sh).
The `cmd_live_load_mod` in `lib/uart.py` waits for `~ #` pattern.
**Fix (when busybox sh as PID 1 works)**: that's when `~ #` appears. With
the C-init REPL workaround, edit `cmd_live_load_mod` to expect `# ` instead.
**TODO**: track in tasks/00.01.eth-driver after soft-float busybox lands.

---

## Symptom: `arping` not found on host
**Cause**: Ubuntu 24.04 split `iputils-arping` into separate package.
**Fix**: `sudo apt install iputils-arping`. Or use `ping -c 1 -b 192.168.1.255`
for raw broadcast.

---

## Symptom: TX counter `tm_tx_count` increments but packets don't reach the host
**Cause**: open RE problem — TM→PP→port forwarding gate is intermittent.
Some packets egress on physical LAN port, most get swallowed in TM/PP.
**Status**: tasks #87, #91, #92, #93 in TaskList. Driver-side problem.
**Not a bug we caused** — fundamental TM gate decoding incomplete.
**Where to dig**: `tasks/00.01.eth-driver/ETHERNET_DRIVER_DESIGN.md` §"TM forwarding".

---

## Symptom: RX counter `rx_packets=0` regardless of host activity
**Cause**: driver's RX descriptor rings (`TM[0x10100..1011c]`) all = 0 —
no RX descriptors populated. `tm_irq_count = 0` — hardware never fires
RX IRQ. Driver isn't supplying buffers for RX.
**Status**: task #55 marked completed but apparently not delivering to
sw netdev. Needs re-verification.
**Where to dig**: `lib/uart.py`'s diff between stock-driver init and ours
(via `tasks/00.01.eth-driver/captures/`).

---

## Story: cspd 3-byte patch was a RED HERRING for UART silence
**Initial assumption (wrong)**: cspd calls `logctrl -m -p /dev/console -g 0/1/2`
at startup to silence UART. So we patched 3 bytes (offsets 0x1cdeda,
0x1cdf21, 0x1ce161 — all `0x30/0x31/0x32` → `0x33`) to make those calls
use `-g 3` ("receive ALL"). Theory: cspd would now keep UART open.
**What actually happened**: cspd's `logctrl` was governing USERSPACE log
forwarding, NOT kernel `printk`. Kernel `printk` was silent because the
kernel's pl011 console driver writes to the **standard PL011 DR offset
(`+0x00`)** but this hardware has the DR at `+0x04` (ZTE-shifted).
**Verification**: we observed that the cspd patch made no visible change
on UART after stock kernel boot. RX (input) worked (we could type), TX
(output) stayed silent.
**Actual fix — `kmsg2uart` daemon**: a 1-page C program that
- opens `/proc/kmsg` for reading
- mmaps `/dev/mem` at the PL011 base (`0x94404000`)
- in a loop: read a printk line, write each byte to **`base + 0x04`** (the
  ZTE-shifted DR), polling FR at `+0x14` for TX-not-full
The kernel's printk path doesn't need to change; we just bridge kmsg → UART
from userspace.
**Why we kept the cspd patch anyway**: it's harmless. With `-g 3` cspd
forwards more log sources to `/dev/console`, which we read via `kmsg2uart`
indirectly. Removing the cspd patch would have no measurable effect on UART.
**Lesson**: when "patching the obvious suspect" doesn't fix the symptom,
**verify the cause-effect chain** before iterating. Don't iterate on a
wrong hypothesis. We could have saved ~1 day if we'd checked register
addresses earlier.
**Reference**: `docs/SLOT_A_CSPD_PATCH_PLAYBOOK.md`, `tasks/00.02.stock-shell/kmsg2uart.c`.

---

## Topic: How to observe what stock kernel modules do at runtime
**Constraint**: stock 4.1.25 has `# CONFIG_KPROBES is not set` and
`# CONFIG_FUNCTION_TRACER is not set`. `/sys/kernel/debug/tracing/`
does not exist. dynamic tracing is DEAD on stock.
**Available**:
- `kmsg2uart` daemon (in stock-traced custom rootfs) drains `/proc/kmsg`
  → writes to ZTE-shifted PL011 DR at `+0x04` via `/dev/mem` → visible
  on UART. So any kernel `printk` is visible to us.
- Stock device can SSH (`admin / UkuGPeyRDU` @ `192.168.1.1`).
- We can `rmmod` + `insmod` arbitrary .ko files.
**Methodology**: **binary-patch stock `.ko` to add `printk` calls.**
- Pick target function in Ghidra, find safe insertion offset.
- Splice in `push {r0-r3, lr}; ldr r0,=fmt; mov r1, <arg>; bl printk; pop {r0-r3, lr}`.
- Add a relocation entry for the `printk` symbol (kernel resolves at insmod).
- Add the fmt string to `.rodata`.
- Re-flash the patched .ko into slot-A rootfs (or push via SCP, rmmod, insmod).
- Watch UART for the new printk lines.
**Reference**: `tasks/99.01.linux-stockport/auto_patch_plat.py` has a working
pattern (originally for symbol fixups; recycle the ELF splicing).
**Why this is the path**: hook-module-via-kallsyms_lookup_name (Tier 3)
needs ABI-matched build environment; binary patching (Tier 4) needs only
`pyelftools` + Ghidra offsets. Tier 4 is what's actually viable today.
**Reference doc**: `docs/STRATEGY_STOCK_AS_ORACLE.md` Tier 4.

---

## Symptom: Mixed Spanish/English in `CHRONICLE.md` makes grep awkward
**Cause**: legacy from project start.
**Fix**: when you copy a finding from CHRONICLE into LEARNED, write it
in English.

---

## Anti-patterns to avoid

1. **Don't rewrite working scripts inline in shell when one already exists in `lib/`.**
   We did this for `flash_mainline.py` (rewrote the slotA.bin build inline,
   re-introduced the padding bug).
2. **Don't trust file paths in shell-cmd output across `Shell cwd was reset` boundaries.**
   Bash tool resets cwd between calls. Use absolute paths.
3. **Don't `exec` in /init unless you've understood the redirect requirement.**
   Plain `exec /bin/sh` → EOF → panic.
4. **Don't assume CONFIG_DEVTMPFS_MOUNT auto-mounts `/dev` for initramfs.**
   It mounts for ramfs root; with initramfs you must mount devtmpfs in /init.
5. **Don't put `.ko` builds inside `git`** (they're large, opaque, regeneratable).
6. **Don't rediscover.** If a problem matches a LEARNED entry's symptom, the
   solution is the LEARNED entry's fix. If a new finding emerges, add a new entry.

---

## How to add a new entry

1. Symptom (the OBSERVABLE thing).
2. Cause (what's actually happening underneath).
3. Fix (the SPECIFIC change).
4. Reference (file:line where the solution lives in code, OR the doc that documents it).
5. Cost (rough wall-clock time to debug from scratch — motivates future-you to read this list).
