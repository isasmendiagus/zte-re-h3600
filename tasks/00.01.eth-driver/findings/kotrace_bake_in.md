# Kotrace bake-in: capturing module init traces at boot

Use this when you need to observe code that runs **before** SSH/cspd
comes up — module init functions (`chip_tm_init`, `sw_init_switch`,
plat-zxylzb internals, etc). The post-boot SSH workflow in
`kotrace_workflow.md` is faster but only sees post-init runtime.

## How it works

`build_rootfs_with_kotrace.py` copies the 00.02.stock-shell staging,
drops `kotrace.ko` into `/kmodule/`, and patches `/etc/init.norm` to
load it AFTER zx_ponreg but BEFORE plat-zxylzb. The kotrace notifier
is then live when plat/tm/switch reach `MODULE_STATE_COMING`, so it
can patch their .text with thunks **before** their init runs.

```
+--------------------+
| /etc/rc            |
|  mount /proc       |  ← fix: /proc/.keep + /sys/.keep
|  LOADTYPE=3 force  |  ← fix: /proc/zte/verinfo/loadtype is empty here
|  exec init.norm    |
+--------------------+
         │
+--------------------+
| /etc/init.norm     |
|  insmod shellproc  |
|  insmod patch      |
|  insmod zx_ponreg  |
|  kinsmod kotrace   |  ← bake-in entry point
|  dumpkring (early) |  ← validates pipeline; ring=0 bytes expected
|  insmod plat       |  ← notifier fires; thunks patched
|  dumpkring (late)  |  ← captures plat init traces
|  insmod tm         |
|  insmod switch     |
|  ...               |
|  pc&  (cspd)       |
+--------------------+
```

## Toggle: KOTRACE_MINIMAL_BOOT

`kotrace.c` has a compile-time flag:

- `KOTRACE_MINIMAL_BOOT 1` — notifier observes module load/unload
  events but **does not patch** any function. Box boots all the way
  through (cspd, httpd, WiFi, bridge). Ring stays empty.
- `KOTRACE_MINIMAL_BOOT 0` — full patching. Plat init still crashes
  (under bisect). Captures function call args before the crash.

Default in source: `MINIMAL_BOOT 1` while we bisect the crash.

## Three small static-ARM helpers in /sbin

All built static against arm-linux-gnueabi and ~543KB each. All three
mmap /dev/mem at PL011 base 0x94404000 and bypass /dev/console (which
breaks on this firmware when cspstart fails to expand `$(console)` in
bootargs).

| Tool | Purpose |
|---|---|
| `printok <tag>` | echo "[printok] <tag>" straight to UART. Bisect probe. |
| `kinsmod <ko> [params]` | `init_module(2)` syscall + write errno to UART. Replaces busybox-insmod whose stderr goes to /dev/null in init.norm. |
| `dumpkring <path>` | open + read file, write byte-for-byte to UART. Used as `/sbin/dumpkring /proc/kotrace_dump`. |

## Critical infra fixes (silent before)

These were not bugs in kotrace — they were bugs in our generated
rootfs that **silently** truncated the bake-in flow before the
kotrace work could even run.

1. **`/proc` and `/sys` did not exist** as directories in the
   staging. `mount -t proc proc /proc` failed silently, so EVERY
   `/proc/*` open returned ENOENT (including `/proc/kotrace_dump`).
   Fixed with `staging/proc/.keep` + `staging/sys/.keep` so mkfs.jffs2
   includes the dirs.

2. **`/proc/zte/verinfo/loadtype` returns empty** at /etc/rc time
   (kernel populates it later). With empty `$LOADTYPE`, the original
   rc fell through every branch and exited cleanly — init.norm never
   ran. Fixed by forcing `LOADTYPE=3` if empty in `etc/rc`.

3. **busybox insmod's stderr is invisible** when init.norm has no
   controlling tty. Use `kinsmod` instead — it pushes the syscall
   errno through PL011 directly so failures are observable.

## Run it

```bash
# 1. set MINIMAL=1 (boot survives) or 0 (bisect crash)
sed -i 's/#define KOTRACE_MINIMAL_BOOT 0/#define KOTRACE_MINIMAL_BOOT 1/' \
    tasks/00.01.eth-driver/kotrace/kotrace.c

# 2. build kotrace.ko
make -C tasks/00.01.eth-driver/kotrace

# 3. build the bake-in rootfs (drops kotrace.ko in /kmodule + injects)
python3 tasks/00.01.eth-driver/kotrace/build_rootfs_with_kotrace.py

# 4. flash slot A
python3 tasks/00.04.flash-tool/flash.py rootfs \
    --src tasks/00.01.eth-driver/out/rootfs_kotrace_enc.jffs2
```

Then watch `/tmp/uart_bridge.log`. Expected markers in order:

```
[printok] RC_TOP ... RC_BEFORE_INIT_NORM
[printok] BEGIN
[printok] BEFORE_SHELLPROC / BEFORE_PATCH / BEFORE_ZXPONREG
[kinsmod] try /kmodule/kotrace.ko (NNNNNN bytes)
[koINIT:A..F init markers]
[ko: kotrace loaded]
[kinsmod] init_module() returned 0 OK
[printok] AFTER_KOTRACE
[printok] BEFORE_DUMPKRING_EARLY
=== dumpkring: /proc/cmdline OK (/proc mounted) ===
=== /proc/modules: kotrace ... Live ...
=== dumpkring: done (0 bytes) ===     ← early dump, ring empty
[printok] AFTER_DUMPKRING_EARLY
[printok] BEFORE_PLAT
[ko:C plat_zxylzb_9128S]               ← thunks patched here (MINIMAL=0)
[ko:L plat_zxylzb_9128S]
[printok] BEFORE_DUMPKRING
=== dumpkring: done (N bytes) ===     ← late dump, ring=plat captures
[printok] AFTER_DUMPKRING
...
```

## Status

- **2026-05-25**: MINIMAL=1 path validated end-to-end. EARLY dump =
  `done (0 bytes)`, LATE dump = `done (0 bytes)` (notifier-only, by
  design). Box boots fully through cspd cascade. Pipeline confirmed.
- **MINIMAL=0 still crashes** during/after plat_zxylzb LIVE. The
  thunk corrupts state that manifests on the next userspace
  transition (printok / dumpkring fork+exec after plat-LIVE → reset
  within microseconds of the second uart_puts). Hardware watchdog
  may also contribute since cspd never runs to pet it.

## Next: bisect MINIMAL=0 crash

Approaches under consideration:

- Add a per-module patch-count limit (`KOTRACE_PATCH_LIMIT=N`,
  patch only the first N functions in v2 lookup). Start at N=1 and
  scale up until plat-init crashes.
- Move ring-buffer dump INTO the notifier (`MODULE_STATE_LIVE`
  callback dumps via printk), so kmsg2uart streams the trace
  before any further module load can crash the box.
- Pet the hardware watchdog from a userspace watchdog-fed helper
  spawned before plat insmod, to rule out HW-WDT contribution.
