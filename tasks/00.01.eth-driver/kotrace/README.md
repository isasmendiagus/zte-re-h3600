# kotrace — loader-notifier + RAM-patching tracer

Working trace mechanism for stock kernel modules on this device. Background
and design rationale live in
[`../findings/idea_a_kotrace.md`](../findings/idea_a_kotrace.md) — that's the
authoritative writeup. This README is the operator's manual.

## Files

| File | What |
|---|---|
| `kotrace.c` | The module — notifier + RAM patcher |
| `hello.c` | Tiny sanity .ko used to validate the build env |
| `Makefile` | Out-of-tree build against the 4.1.25 source tree |
| `build_rootfs_with_kotrace.py` | Bake kotrace.ko into a flashable rootfs and inject an `insmod` line into `/etc/init.norm` so kotrace runs BEFORE cspd starts loading drivers |

## Quick start — capture switch.ko's init sequence at boot

```bash
# 1. build
make -C tasks/00.01.eth-driver/kotrace

# 2. bake into rootfs (copies 00.02 staging read-only, drops in kotrace.ko,
#    patches init.norm)
python3 tasks/00.01.eth-driver/kotrace/build_rootfs_with_kotrace.py

# 3. flash and watch UART
#
# flash.py uses the uart-bridge daemon (port 9999 data, 9998 ctl) BY
# DEFAULT — multiple processes can tail UART concurrently. To opt out
# pass --direct-uart.
#
# Prereq: the bridge must be reachable. Confirm with:
#     ss -tln | grep -E ':9998|:9999'   # both ports should be LISTEN
# If not running, flash.py will auto-spawn it; or start manually:
#     tasks/00.04.02.uart-bridge/uart_bridge.py &
#
python3 tasks/00.04.flash-tool/flash.py rootfs \
    --src tasks/00.01.eth-driver/out/rootfs_kotrace_enc.jffs2 \
    | tee /tmp/a3_boot.log

# 4. once boot completes, grep markers from the captured stream
#    (the bridge also tees everything to /tmp/uart_bridge.log so a parallel
#     `tail -f /tmp/uart_bridge.log` works during flash too)
grep -aE "\[ko|patched OK" /tmp/a3_boot.log
```

What "good" looks like:

```
[ko: kotrace loaded]
[ko: 'switch' not yet loaded — will wait for COMING]
[ko:L kotrace]
[ko:C shellproc] [ko:L shellproc]
[ko:C patch] [ko:L patch]
[ko:C zx_ponreg] [ko:L zx_ponreg]
[ko:C plat_zxylzb_9128S] [ko:L plat_zxylzb_9128S]
[ko:C tm] [ko:L tm]
[ko:C switch]
[ko: switch found, allocating thunks: 0x000000a0]
[ko: target chip_tm_init @ 0xbf19d6ac]
  patched OK
[ko: target sw_init_switch @ 0xbf19e0bc]
  patched OK
... etc for 5 targets ...
[ko:L switch]
```

Then **inside** the body of the kernel boot messages between the patch
lines and `[ko:L switch]`, the 1-char markers for each patched function
appear as the init runs (`S`, `W`, `E`, `C`, `A`).

## Quick start — iterate the patching logic without reflashing

If switch is already loaded (typical post-boot state), `kotrace.ko`'s init
finds it via `find_module("switch")` and patches it in place:

```bash
make -C tasks/00.01.eth-driver/kotrace
cp tasks/00.01.eth-driver/kotrace/kotrace.ko tftp/

# on device via SSH:
cd /tmp && busybox tftp -g -r kotrace.ko 192.168.1.50
rmmod kotrace 2>/dev/null
insmod /tmp/kotrace.ko
```

Marker chars from already-init'd functions won't fire (init only runs
once at module load), but the `[ko: target X @ Y] patched OK` sequence
DOES fire, which is enough to validate that:
- runtime symbol lookup works (addresses look right)
- `module_alloc` + thunk codegen worked
- `set_memory_rw` + cache flush succeeded

Lets you iterate on the .ko in ~10s per cycle vs ~5 min for a reflash.

## Target functions

Currently hard-coded in `kotrace.c` `targets[]`:

| Marker | Function in switch.ko |
|---|---|
| `S` | `sw_init_switch` |
| `W` | `sw_init_wlan_ssid` |
| `E` | `ethdrv_port_dev_init` |
| `C` | `chip_tm_init` |
| `A` | `sw_alarm_init` |

Add new targets by appending to the `targets[]` array. Each needs:
- a function name as known inside the module's symtab (use
  `arm-linux-gnueabi-readelf -s ext/kmodules_dump/switch.ko` to list)
- a unique 1-byte marker char that doesn't appear too often in
  surrounding stock output

Functions whose FIRST instruction is PC-relative (e.g. `bx lr` for a
trivial wrapper, or any `ldr/ldm` against PC) cannot be patched safely
without rewriting them — kotrace doesn't check this; if you target one,
the displaced instruction will compute against a wrong PC.

## Reading the markers in context

`<4>` is the kernel printk level prefix that surrounds normal output.
Our markers are single chars written directly to PL011 without a level
prefix, so they appear as bare letters mid-stream. Use the **context**
around each marker to interpret:

- `SW<4>Init switch module` — S=sw_init_switch entered, W=sw_init_wlan_ssid
  was the very next thing called (back-to-back). The kernel's printk
  comes after.
- `EEEECA<4>sw_set_uni_as_wan` — five E's = ethdrv_port_dev_init called
  five times (once per UNI port 0..4), then C, then A.

For complicated traces consider switching to multi-char markers
(`[C]`, `[S]`, etc.) — see "Limitations" in
[`../findings/idea_a_kotrace.md`](../findings/idea_a_kotrace.md).

## Adding a new traced module (not just switch)

Currently the patcher is hard-wired to `strcmp(mod->name, "switch")`.
To trace e.g. `tm.ko`:

1. Add a second copy of `patch_switch_module()` named for the new module
   (or genericize — keep one function, take a name-list arg).
2. Add to the notifier callback's match:
   `if (strcmp(mod->name, "tm") == 0) patch_tm_module(mod);`
3. Pick a different marker-char alphabet so the streams don't collide
   if you ever load both at once.

## Caveats / future work

See "Limitations + things to clean up" in
[`../findings/idea_a_kotrace.md`](../findings/idea_a_kotrace.md).
