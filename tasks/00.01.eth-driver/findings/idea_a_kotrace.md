# Idea A — loader-notifier + RAM-patching tracer (`kotrace.ko`)

The working trace approach for stock kernel modules on this device. Replaces
the on-disk LIEF/ELF splice approach which is structurally infeasible (see
[[ko_splice_bugs]]).

---

## What it is

A separate kernel module (`kotrace.ko`) that:

1. Resolves a handful of un-exported kernel helpers via
   `kallsyms_lookup_name()`.
2. Registers a `module_notifier`. On every load, gets a callback at
   `MODULE_STATE_COMING` (after relocations applied, kallsyms populated, but
   **before** `init_module` runs).
3. For the module of interest (`switch.ko` here):
   - walks `mod->kallsyms->symtab` for each target function name
   - allocates an executable thunk buffer with `module_alloc()`
   - builds a 32-byte thunk per target — instructions are emitted
     directly with the now-known runtime addresses, **no relocations
     required**
   - flips switch's `.text` to RW via `set_memory_rw()`, overwrites the
     function's first instruction with `b thunk` (4 bytes), flushes
     I-cache, restores RO
4. When `init_module(switch)` runs immediately after, each patched
   function entry emits a 1-byte marker to UART (direct write to the
   PL011 data register), then runs its displaced original first
   instruction, then branches back to function+4 and continues.

All bytes the thunks need are computed at patch time from
already-resolved addresses, so the failure modes that bricked the
on-disk approach (stale relocations, malformed symbol-table) cannot
happen.

## Why it works where on-disk patching didn't

| Failure mode in on-disk splice | How RAM-patch sidesteps it |
|---|---|
| `.rel.text` reloc on displaced first insn gets misapplied to inserted branch | We don't have a separate static rel table — we write resolved bytes |
| LIEF appends LOCAL symbols past `sh_info` → malformed ELF | No symbols added |
| Loader silently mishandles new `.text.splice` / `.data.splice` sections | Thunk lives in `module_alloc()`'d memory, not a new ELF section |
| `R_ARM_JUMP24` / `R_ARM_MOVW_ABS_NC` need careful encoding | Single direct `b` instruction encoded from known absolute runtime addrs |
| Bricks the device on every wrong guess, no panic message | If something goes wrong, the host kotrace.ko is just removed; switch.ko on disk untouched |

## Components on disk

```
tasks/00.01.eth-driver/kotrace/
├── kotrace.c                       # the module — notifier + RAM patcher
├── hello.c                         # Phase A1 sanity .ko (validates build env)
├── Makefile                        # out-of-tree build against the 4.1.25 tree
└── build_rootfs_with_kotrace.py    # bake kotrace.ko into a flashable rootfs
                                    # + patch /etc/init.norm to insmod it
                                    # BEFORE cspd loads switch
```

## Two ways to use it

### A — boot-time (catches init_module's first run)

```bash
# build the .ko + rootfs
make -C tasks/00.01.eth-driver/kotrace
python3 tasks/00.01.eth-driver/kotrace/build_rootfs_with_kotrace.py
# flash + watch
python3 tasks/00.04.flash-tool/flash.py rootfs \
    --src tasks/00.01.eth-driver/out/rootfs_kotrace_enc.jffs2
# UART will stream markers; redirect flash python's stdout to a file
# if you want a persistent capture
```

This is the **only** path that captures `init_module`'s first execution —
once switch is LIVE its init functions don't usually run again.

### B — runtime (iterate without reflashing)

If switch is already loaded, kotrace's init walks the loaded-modules list
via `find_module("switch")` and patches it in place. Useful for iterating
on the patching logic itself without a 5-minute flash cycle:

```bash
make -C tasks/00.01.eth-driver/kotrace
cp tasks/00.01.eth-driver/kotrace/kotrace.ko tftp/
# from SSH on the device:
cd /tmp && busybox tftp -g -r kotrace.ko 192.168.1.50
rmmod kotrace 2>/dev/null
insmod /tmp/kotrace.ko
```

Markers from this path won't show `init_module`'s execution (it already
ran), but they will fire if anything in userspace later triggers one of
the patched functions (e.g. ifconfig sw down/up, sysfs writes).

## Critical implementation details discovered the hard way

### 1. Kernel helpers we need are NOT exported

Three primitives needed for patching are in the kernel image but NOT
`EXPORT_SYMBOL`'d, so they can't be linked at insmod:

- `module_alloc(size)` — allocate executable memory in the module area
- `set_memory_rw(addr, n)` — flip pages to RW
- `set_memory_ro(addr, n)` — flip pages back to RO
- `find_module(name)` — also used for the "already loaded" path

**Fix**: `kallsyms_lookup_name()` IS exported. Declare function pointers,
resolve them in `module_init`, abort if any are NULL. The symbols ARE in
`/proc/kallsyms` on this device (verified):

```
c000dd00 T module_alloc
c00130f8 T set_memory_ro
c0013104 T set_memory_rw
c006cdfc T kallsyms_lookup_name
```

### 2. PL011 register layout is ZTE-shifted, and FR is at +0x14

The PL011 UART data register sits at `+0x04` (stock PL011 is `+0x00`).
The flag register, where we poll TXFF to avoid FIFO overflow, is at
`+0x14` (stock PL011 is `+0x18`). Without that throttle, writing more
than ~16 bytes in a burst silently drops everything past the FIFO depth
— our marker stream gets truncated and we think the trace isn't firing
when it actually is.

Reference: `tasks/00.02.stock-shell/kmsg2uart.c` already had this
constant; we re-discovered it the hard way. Now codified at the top of
`kotrace.c` with both offsets and `PL011_FR_TXFF` bit.

### 3. mod->kallsyms is populated BEFORE MODULE_STATE_COMING fires

In Linux 4.1, by the time the notifier callback runs for
`MODULE_STATE_COMING`, the kernel has already:
- resolved external symbols
- applied relocations
- populated `mod->kallsyms->symtab` + `strtab` (incl. STATIC symbols)

So `find_sym_in_mod(mod, "chip_tm_init")` works — even though
`chip_tm_init` is a *static* function inside `switch.ko` and therefore
NOT visible in `/proc/kallsyms` from userspace.

### 4. Init functions that survive vs. don't

Functions marked `__init` get freed after init_module returns. If we
ever try to call a patched `__init` after init, we'd jump into freed
memory. None of our current 5 targets are `__init`-marked in stock
switch.ko (verified — they live in `.text`, not `.init.text`), so we're
safe. If we ever target a `__init` function, we MUST also unpatch it
before MODULE_STATE_LIVE — otherwise the thunk's back-jump to func+4
points at memory that's about to be released.

## The actual trace captured (2026-05-23)

Marker mapping in current `kotrace.c`:

| Marker | Function |
|---|---|
| `S` | `sw_init_switch` |
| `W` | `sw_init_wlan_ssid` |
| `E` | `ethdrv_port_dev_init` |
| `C` | `chip_tm_init` |
| `A` | `sw_alarm_init` |

UART stream excerpt during boot, between `[ko: ... patched OK]` (end of
patching, just before `init_module(switch)` runs) and `[ko:L switch]`
(switch LIVE):

```
SW<4>Init switch module        ← S = sw_init_switch enters
                                  W = sw_init_wlan_ssid called early
<4>g_sw_cap.sw_uni_count=5
<4>g_sw_cap.sw_uni_mask=0xf
<4>g_sw_cap.sw_wan_port=4
... [snipped 20 lines of stock init prints] ...
<4>port id 4, name pon
<4>Error! NFBI maybe not connect!
<4>Error! NFBI maybe not connect!
E<4>Error! NFBI maybe not connect!      ← E ×1 (ethdrv called for UNI 0)
<4>Error! NFBI maybe not connect!
EEEECA<4>sw_set_uni_as_wan uni=4        ← E ×4 (UNIs 1-4), then C, then A
<4>lan_up_port=0x4
<4>PON_PP_TM_CFG=0x21200000
<4>after PON_PP_TM_CFG=0x21200000
<4>tm_pon_protocol_pktdeal_set fail, error protocal 33
... [TM init body — stock printks from inside chip_tm_init] ...
<4>-------chip_tm_init end-----
<4>[SW][sw_init_switch] l2_fast init    ← back in sw_init_switch
```

### What this trace tells us

**Init order**:

```
sw_init_switch
  ├─ sw_init_wlan_ssid                 (immediately)
  ├─ ... port enumeration / config ...
  ├─ ethdrv_port_dev_init × 5          (one per UNI port: 0, 1, 2, 3, 4)
  ├─ chip_tm_init                      (the TM block we suspected was missing)
  └─ sw_alarm_init                     (after chip_tm_init returns)
```

**Implication for mainline port**: our `linux-v6.6/zx279128-eth` driver
needs to do, in order:

1. Per UNI port: a `ethdrv_port_dev_init`-equivalent
2. After all ports are up: `chip_tm_init`-equivalent (the TM block work
   that `rx_path_dead.md` flagged as the suspected blocker for RX)
3. Then `sw_alarm_init` (probably less critical for RX — alarm/event
   path)

Next phase (#19) drills into `chip_tm_init` specifically — adds more
function targets that `chip_tm_init` calls internally, to capture the
register-write sequence for the TM block.

## Limitations + things to clean up

- **1-char markers collide with kernel printks visually** — `EEEECA` is
  unambiguous in context, but for less obvious cases the output is
  noisy. Improvement: emit `[C]`, `[S]` etc. (3 bytes per marker, still
  small enough to not stress FIFO, much easier to grep).
- **No revert path** — `kotrace_exit` doesn't undo patches. If you
  rmmod kotrace and the patched functions get called later, the
  thunks live on but the marker-emission code points at PL011 which is
  fine, so no crash; but the bytes we wrote in `switch.ko`'s `.text`
  stay there. Cosmetic for now; would matter if we did online debugging
  on a production system.
- **`module_alloc()` is never freed** — if kotrace is rmmod'd and
  re-insmod'd, we leak `0xa0` bytes per cycle of `module_alloc` memory.
  Cosmetic; the device reboots well before we'd run out.
- **No file-based capture** — UART is captured manually with one-shot
  python `read()`. A persistent UART logger writing to a file would be
  cleaner (see [[uart_capture_pipeline]] when written — TODO).

## Build env reminder

The `Makefile` builds against `tasks/99.01.linux-stockport/linux-4.1.25/`.
That kernel tree has CONFIG_MODULES, CONFIG_MODULE_UNLOAD, CONFIG_ARM,
CONFIG_AEABI matching the running kernel's vermagic
(`4.1.25 SMP mod_unload ARMv7`). `CONFIG_MODVERSIONS` is OFF on both,
so we don't have to match symbol CRCs.

gcc 13.3.0 (host) builds a .ko that loads fine on the device's gcc-4.9
kernel — the on-the-wire ABI is the same as long as vermagic matches.
