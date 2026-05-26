# Capturing module-init traces with kotrace — handoff

Where we are (2026-05-26) and what comes next, structured so an agent
picking up the job can resume without re-deriving everything.

## Why we care

This is a **GPL-licensed device** (ZTE H3600, ZX279128S SoC). ZTE,
Digi and CHN have all refused to release the kernel SDK. We are
reverse-engineering the driver init paths because there is no other
way to forward-port them to mainline Linux — the only legitimate
information we ever got was via reading binaries.

`/proc/kotrace_dump` is our window into what stock's eth/switch/tm
init actually *does*. We capture each call to a target function and
its r0..r3 args. That data feeds the mainline driver port in
`linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c`.

## What's running today

| Piece | Lives | Role |
|---|---|---|
| `tasks/00.01.eth-driver/kotrace/kotrace.c` | host source | RAM patcher + ring buffer |
| `kotrace.ko` (patches+thunks) | `/kmodule/` in rootfs | patches first insn of each target with `b thunk` |
| `kotrace_targets.h` | included by .c | auto-generated 2157-fn target table across plat / tm / switch / mt7915 / idmfdb |
| `/sbin/netshell` (port 9001) | bake-in rootfs | raw-TCP shell, bypasses dropbear; line tokenizer with quote support |
| `/sbin/dumpkring` (path) | bake-in rootfs | reads file, writes byte-for-byte to PL011 UART via /dev/mem mmap |
| `tasks/00.01.eth-driver/kotrace/build_rootfs_with_kotrace.py` | host | builds the bake-in rootfs; injects kinsmod + netshell + iptables-flush + watchdog-pet |
| `/proc/kotrace_dump` | runtime | textified ring buffer; write to it (echo, dd, or our `reset` builtin) resets it |

`kotrace.ko` accepts three runtime params (all settable on insmod, no
recompile):
```
patch_limit=N            # cap on total successful patches (0 = no limit)
patch_modules=a,b,c      # CSV whitelist of module names (empty = all in kt_modules[])
patch_skip=fn1,fn2       # CSV blacklist of function names
```

## What works, what doesn't

**Works**:

- Post-boot insmod of kotrace.ko with **all 2157 patches** (no
  patch_limit, no module whitelist). Box stays up, ring fills with
  real runtime data (TX/RX/timers). Confirmed 2026-05-26.
- Bake-in boot path with **patch_limit=1** (single patch applied
  during boot). Box boots all the way through cspd cascade.

**Doesn't work**:

- Bake-in with full patching (MINIMAL_BOOT=0, no patch_limit). Box
  reboots silently between `[ko:L switch]` and the next U-Boot
  banner. No softlockup printout in the failing iters, no panic.
  Looks like the HW watchdog (/dev/FeedDog, major 123) firing
  before `pc&` brings cspd up to feed it — cumulative thunk
  overhead pushes the time-to-cspd past the watchdog window.
- The /etc/init.norm injection of a watchdog-pet loop
  (`while :; do echo > /dev/FeedDog; sleep 2; done &`) didn't help;
  device may need an actual ioctl(WDIOC_KEEPALIVE), not a write,
  OR the watchdog driver isn't loaded yet when the loop starts.

## The plan ("Option B" — post-boot init replay)

We don't need bake-in init capture if we can re-trigger init paths
post-boot. The trick: `rmmod target_module ; insmod /kmodule/target_module.ko`
re-runs that module's `module_init`. With kotrace patches already in
place, the second init runs through the thunks.

The catch: rmmod'ing a net-stack module kills our network → we
lose netshell → can't issue commands → reboot. Solution: drive the
whole sequence from a single shell script that runs locally on the
device and dumps the result out the UART (which never dies).

### Recipe per target module

1. Boot the bake-in rootfs (MINIMAL_BOOT=1 — no boot-time patches,
   stable). Wait for netshell on `192.168.1.1:9001`.
2. Push kotrace.ko via tftp:
   ```sh
   cd /tmp ; busybox tftp -g -r kotrace.ko 192.168.1.50
   ```
3. Activate full patching:
   ```sh
   rmmod kotrace ; insmod /tmp/kotrace.ko    # default patch_limit=0
   ```
4. Reset the ring and re-init the target. Do this AS ONE SHELL
   COMMAND so a network drop mid-way doesn't strand us:
   ```sh
   sh -c '
     /sbin/dumpkring /proc/kotrace_dump > /tmp/cap_pre.txt
     echo > /proc/kotrace_dump
     rmmod tm
     insmod /kmodule/tm.ko
     sleep 2
     cat /proc/kotrace_dump > /tmp/cap_tm_init.txt
     /sbin/dumpkring /tmp/cap_tm_init.txt   # spit to UART
     # belt-and-suspenders: if network is dead, reboot to restore from slot A
     if ! ping -c 1 -W 1 192.168.1.50 >/dev/null 2>&1 ; then
         reboot -f
     fi
   '
   ```
5. The UART dump is captured host-side in `/tmp/uart_bridge.log` by
   the existing bridge daemon. Pull it from there for analysis.
6. Resolve `bf*` addresses in the trace to symbols:
   ```sh
   # device-side, via ssh/netshell while alive:
   sh -c 'grep -E "^bf[0-9a-f]+ t" /proc/kallsyms' > /tmp/syms.txt
   ```
   Then on the host, sort the trace by `fn_addr` and look up each in
   `syms.txt`.

### Per-module load order (from /proc/modules dependency tree)

```
mt7915 (no deps)
  └─ idmfdb (depends mt7915)
       └─ switch (depends idmfdb)
            └─ tm (depends switch)
                 └─ plat_zxylzb_9128S (depends all)
```

rmmod has to go in *reverse* order (highest dependency first).
insmod can rely on kernel auto-resolving via /lib/modules/modules.dep
if it exists, otherwise insmod in load order.

### Things to watch for

- `set_memory_rw failed` on `zx_mdio_*` (kernel-text symbols).
  These addresses are in `c00xxxxx` (kernel base), not module text.
  The patcher correctly bails out before writing the branch, but
  the v2 target table shouldn't include them — regenerate
  `kotrace_targets.h` with the kallsyms input filtered to module
  addresses only.
- Watchdog still bites if any captured function is *very* hot. If
  the post-boot insmod-of-kotrace itself hangs, lower the scope
  with `patch_modules` and re-try.

## Open work

- `touch_softlockup_watchdog()` periodic call from the thunk (or
  from a kotrace timer/kthread). The kernel exports it. Would let
  us run the bake-in safely with all patches.
- A small ARM-asm extension to the thunk that calls a C helper for
  smart-deref of pointer args (see prior commit 606cec092 for the
  table; runtime use is pending).
- Regenerate `kotrace_targets.h` excluding kernel-text symbols.
- Optionally: cross-compile a static `socat` for ARM so we can
  replace netshell with a real PTY-fronted shell.

## Files / commits

- `tasks/00.01.eth-driver/kotrace/build_rootfs_with_kotrace.py`
  — bake-in recipe; check `INJECT_BLOCK` for the latest params.
- `tasks/00.02.stock-shell/netshell.c` — TCP shell daemon.
- `tasks/00.02.stock-shell/dumpkring.c` — file→UART relay.
- Recent commits: `db24fa025` (filters + tokenizer), `a77fcad5b`
  (patch_limit module param), `4bd63544c` (netshell milestone).

## Hard-coded device truth (no SDK = these are tribal knowledge)

- SoC: ZTE ZXIC ZX279128S, ARM Cortex-A9 dual-core, ARMv7 soft-float
- PL011 UART base: 0x94404000, **ZTE-shifted** (DR @+0x04, FR @+0x14)
- Module base addresses (post-boot, from `/proc/modules`):
  - plat_zxylzb_9128S 0xbf01d000
  - tm                0xbf04f000
  - switch            0xbf19a000
  - idmfdb            0xbf1cd000
  - mt7915            0xbf1db000
- Device IP `192.168.1.1`, host `192.168.1.50`. SSH `admin/UkuGPeyRDU`.
  Bake-in netshell on TCP/9001 (no auth, raw TCP, drop-in shell).
