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

## SSH on the bake-in rootfs

The bake-in needs SSH so we can `cat /proc/kotrace_dump` and iterate
without reflashing. Two ZTE quirks block plain `ssh admin@dev`:

1. **`/bin/dropbear` is patched by ZTE.** After auth it reads
   `SSHCfg.SSH_ProcType` from `/usercfg/config.bin` via libcfapi:
   - `=0` → `exec /bin/sh` (plain shell)
   - `=1` → `exec /bin/cliagent` (the "Welcome to the world of CLI !"
     restricted prompt that asks for username+password a second time)

   It is hardcoded — NOT pluggable via `/etc/passwd` shell field, NOT
   PAM, NOT a dropbear argv flag. `-p`/`-F`/`-E` are silently ignored.

2. **FWSC firewall blocks SSH from LAN.** cspd applies its access
   rules at startup via `popen('/bin/iptables ...')`, populating the
   `srvcntrl` chain. Rule 8 (`lan_ssh`, FilterTarget=0) drops SSH from
   the LAN interface within seconds of cspd settling.

Both are configured through `/usercfg/config.bin` (AES-128-CBC,
flag=4), uploadable through the web admin (Backup/Restore). On a
stripped rootfs without httpd you can't take that path.

### What the bake-in does instead

**1. `/bin/cliagent` wrapper script** (`tasks/00.02.stock-shell/staging/bin/cliagent`):
```sh
#!/bin/ash
exec /bin/ash
```
plus a backup of the original at `/bin/cliagent.orig`. A *symlink*
won't work here because `/bin/sh` and `/bin/ash` are busybox-applet
symlinks themselves, and busybox dispatches by `argv[0]` — when
dropbear execs `/bin/cliagent`, argv[0] becomes `"cliagent"`, which
busybox has no applet for, and exits silently. The shebang wrapper
forces busybox to be invoked via `argv[0]="ash"` (the shebang
interpreter line), which resolves to the sh applet, and then
exec's an interactive `/bin/ash` over the SSH PTY.

End result: `ssh admin@192.168.1.1` (password `UkuGPeyRDU`) lands
on a `BusyBox v1.17.2 ... built-in shell (ash)` prompt as uid=0.

**2. iptables `srvcntrl` flush loop** in init.norm post-`pc&`:

```sh
(for i in 1..16; do
  sleep 10
  { iptables -L srvcntrl -v -n; iptables -t nat -L srvcntrl -v -n; } > /tmp/fwiter.txt
  cat /tmp/fwiter.txt >> /tmp/fwdump.log
  /sbin/dumpkring /tmp/fwiter.txt        # relay to UART (mmap PL011)
  iptables -F srvcntrl 2>/dev/null
  ip6tables -F srvcntrl 2>/dev/null
done) &
```

160 s of coverage (cspd's `fwScStart` commits around iter 10 on this
unit). Per-iter snapshot of the chain goes to `/tmp/fwdump.log` and
out the UART via `dumpkring` (since `/dev/kmsg` is not writable on
this 4.1 kernel). The actual rule cspd installs is:

```
DROP  tcp  br0   *   0.0.0.0/0  0.0.0.0/0   tcp dpt:22
```

One flush after cspd settles is enough — `cspd` has no firewall
watchdog that re-applies (verified by RE of `fwScStart` /
`setFwAccessRule` symbols).

### Debug aids stamped into the bake-in

- `/tmp/fwdump.log` — running history of every `srvcntrl` snapshot
- `/tmp/cliagent.log` — written by the cliagent wrapper on every
  invocation (argv0, args, tty, env). Use it if SSH stops working.
- The iptables loop also pipes `/tmp/cliagent.log` to the UART each
  iteration when present.

### Note about uploading config_modified.bin

`ext/config_modified.bin` from orca's earlier RE has the right XML
edits (`SSH_ProcType=0`, `lan_ssh FilterTarget=1`) but is encoded
**flag=0 (plain zlib)** — orca's `ztetool.py` doesn't AES-wrap on
encode. This unit's V9.0.20P72 firmware **rejects plain** through
the web admin (silent failure, config keeps its prior values). The
`ext/` reference file is therefore not directly upload-ready; build
a flag=4 wrapper around it (AES-CBC with the H3600 hardcoded keys
from `docs/CONFIG_EDIT.md`) if you want the web-admin path to work.

## netshell — raw TCP shell that sidesteps dropbear entirely

After hours fighting ZTE's patched dropbear (PTY/signal-mask issues
that wedge busybox-ash interactive — see "SSH gotchas" above), the
practical workaround was to **bypass dropbear and run our own daemon**.

`tasks/00.02.stock-shell/netshell.c` is a ~140-line C program that
listens on TCP port 9001, accepts connections, and dups the socket to
stdin/stdout/stderr of a fork+exec'd shell loop. No PTY semantics, no
signal-mask inheritance, no cspd hook. Connect:

```bash
nc 192.168.1.1 9001
# netshell - raw TCP shell, ZTE H3600
# built-ins: cd, pwd, echo, exit. fork+exec everything else.
# 
# wc -c /proc/kotrace_dump
# 0 /proc/kotrace_dump
```

Built-ins: `cd`, `pwd`, `echo`, `exit`. Everything else: `fork+execvp`.
For piped/redirected commands use `sh -c '...'`.

The bake-in (`build_rootfs_with_kotrace.py`) installs it at
`/sbin/netshell` and wraps the daemon in a respawn supervisor in
`init.norm` after `pc&`:

```sh
(while :; do /sbin/netshell 9001 >>/tmp/netshell.log 2>&1; sleep 2; done) &
```

The same supervisor also inserts an idempotent
`iptables -I INPUT 1 -p tcp --dport 9001 -j ACCEPT` rule each iteration
(in case cspd's FWSC ever adds a blocking rule for that port).

### Why we couldn't fix dropbear directly

Three rabbit-hole hypotheses, each falsified:

1. **`/etc/passwd` shell field**: dropbear ignores it; SSH_ProcType=1
   branch in the patched binary hardcodes `exec /bin/cliagent`.
2. **/bin/cliagent symlink/wrapper to /bin/sh**: works structurally
   but `$(...)` substitution in any wrapper hangs forever under
   dropbear's PTY (proved via UART-relay logging of every step).
3. **SIGALRM leak from dropbear's `PtyCmdForShell.isra.5`**: a real
   bug (RE-confirmed: one `sigprocmask(SIG_BLOCK, SIGALRM)` with no
   matching unblock before `execv`). Wrapper that `sigprocmask`s
   UNBLOCK before exec — same hang. Local repro (qemu-arm + same
   busybox + same mask) does NOT reproduce. So the leak is necessary
   but not sufficient; the actual interaction is something specific
   to kernel 4.1.25's PTY line discipline + busybox-ash 1.17.2 that
   we never fully isolated.

netshell sidesteps all of it.

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
