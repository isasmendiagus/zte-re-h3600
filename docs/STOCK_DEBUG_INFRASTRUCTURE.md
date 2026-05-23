# Stock H3600 — Kernel Debug Infrastructure (discovered 2026-05-21)

Major findings from reverse-engineering the running stock firmware. These let us
capture kernel-internal state and function calls **without compiling our own
kernel** — by using ZTE's existing custom debug hooks.

---

## 1. Why UART goes silent on stock (`cspd` is the culprit)

Stock kernel **does** print to `ttyAMA0` initially. After early userspace boot,
the daemon `cspd` calls:

```
/bin/logctrl -m -p /dev/console -g 0   ← removes all log routing from /dev/console
/bin/logctrl -m -p /dev/console -g 1
/bin/logctrl -m -p /dev/console -g 2
```

found via `strings rootfs/bin/cspd`.

**Result:** `/dev/console` (UART) stops receiving printk. Boot looks "silent
after `Starting kernel...`" but the kernel is fine — output is just routed
elsewhere.

### Re-enabling UART console at runtime

```
ssh admin@192.168.1.1     # pw: UkuGPeyRDU
logctrl -m -p /dev/console -g 3
```

`-g` values: `0=none, 1=logger, 2=printf, 3=logger+printf, 4=logcat`. We
discovered `-g 3` works; higher values reject with "please input right -g option(0..4)".

**Caveat:** even with `-g 3`, only LOGGER+printf is routed to console. To get
**raw kernel printk**, use `/dev/logger_main` (see below).

---

## 2. ZTE custom 3-tier log architecture (`logctrl -l`)

```
1: Serial node          /dev/console               LogSrcType=0x06  (logger+printf)
2: Logger node          /dev/logger_main           LogSrcType=0x08  (kernel printk)
3: RamConsole node      /var/tmp/unix_logf_data    LogSrcType=0x02  (logger only)
```

**Key insight:** kernel printk has its own dedicated node `/dev/logger_main`.
We can `cat` it as a live stream of every printk:

```
cat /dev/logger_main > /tmp/dump.bin &
DPID=$!
# ... trigger some kernel activity ...
kill $DPID
```

258 KB captured during a 1.3 s window (single ping with `g_tm_debug_level=4`).

---

## 3. `/proc/tm/shell` — kernel symbol REPL

The most powerful undocumented interface in stock tm.ko. Operates on any
kernel-resolvable symbol. Write commands, read help via `cat /proc/tm/shell`.

### Capabilities

| Command form | What it does |
|---|---|
| `sym` | Print value of `sym` (any kernel global) |
| `sym=val` | Set `sym = val` |
| `-a sym` | Print address of `sym` |
| `-s 0xADDR` | Reverse-resolve address to symbol name |
| `-f sym arg1,arg2,…` | Call `sym(arg1, arg2, …)` and print return value |
| `-F sym arg1,arg2,…` | Same as `-f`, no safety check |
| `-b -w -l` | Treat data as byte / word / dword |
| `-c N` | Iterate N times |
| `-d` | Inputs in decimal (default hex) |
| `-t vaddr` | Translate virtual to physical addr |
| `-p pid` | Inspect process PID |

### Output sink

Results go to `printk()` → readable via `/dev/logger_main` (NOT
`/dev/console`, NOT the proc file itself which always returns the help text).

### Verified examples

```
echo -f fpga_read_reg 0x10006 > /proc/tm/shell
  → printk: "call func fpga_read_reg,with p 10006"
  → printk: <return value of fpga_read_reg(0x10006)>

echo g_tm_init_flag > /proc/tm/shell
  → printk: "sym g_tm_init_flag is 1(0x00000001)"

echo lan_up > /proc/tm/shell
  → printk: "sym lan_up is 1(0x00000001)"

echo g_tm_debug_level=4 > /proc/tm/shell
  → sets debug verbosity for tm.ko's internal printks
```

### Why this matters

This is effectively a **live kernel-mode debugger** that requires zero kernel
patching. Every function exported by stock plat/tm/switch/idmfdb can be called.
Every global can be inspected or modified. Combined with `/dev/logger_main`
capture, we have full observability.

---

## 4. Stock kernel config — `/etc/autokernelconf`

A copy of the kernel's `.config` is shipped in the rootfs at
`/etc/autokernelconf` (with `@` as comment marker instead of `#`). This is
**ground truth** for what ZTE's actual build used.

### Critical knobs we were missing in our stockport build

| Stock has | We had (broken) | Why this breaks our boot |
|---|---|---|
| `CONFIG_ARCH_ZX279128S=y` | `CONFIG_ARCH_ZX=y` | wrong symbol name → mach-zx code not compiled in |
| `CONFIG_MACH_ZX279128S=y` | `CONFIG_SOC_ZX279128S=y` | same — different mach scaffolding |
| `CONFIG_DEBUG_LL=y` | (not set) | no early UART output before earlycon |
| `CONFIG_DEBUG_LL_UART_PL01X=y` | (not set) | pl01x.S DEBUG_LL macros not included |
| `CONFIG_DEBUG_UART_PHYS=0x94404000` | (not set) | early UART phys addr unknown |
| `CONFIG_DEBUG_UART_VIRT=0xf0704000` | `0xf0404000` in mach-zx | **WRONG** — wrong iomap, MMU sees no UART |
| `CONFIG_SERIAL_LOG_CONSOLE=y` | (not in mainline) | ZTE custom — sources may not exist; not strictly needed for early debug |
| `CONFIG_CMDLINE_FROM_BOOTLOADER=y` | same | OK |
| `CONFIG_CMDLINE=…` (default) | (empty) | optional — bootloader provides ours |

### What's intentionally NOT in stock and we don't need

```
@ CONFIG_ARM_PATCH_PHYS_VIRT is not set     → we must set CONFIG_PHYS_OFFSET=0x40000000
@ CONFIG_CMDLINE_FORCE is not set           → bootloader cmdline wins (correct)
@ CONFIG_ARM_APPENDED_DTB is not set        → stock uses ATAGs, not DTB!
```

**Note: stock uses ATAGs, not DTB.** Our prior attempts to pass a DTB via
`bootm <kernel> - <dtb>` are not how stock works. cspstart/U-Boot passes ATAGs
which the kernel parses to find machine + cmdline. With the right mach support
(`MACH_ZX279128S=y`), the kernel auto-selects the machine from ATAG mach_type.

---

## 5. SSH access details

```
host:   192.168.1.1
user:   admin
pass:   UkuGPeyRDU
```

Stock SSH server **rejects non-interactive `ssh user@host cmd`** and `exec`
requests. Use `paramiko.invoke_shell()` to get an interactive session — see
`ssh_shell.py` in this directory.

### `ssh_shell.py` sentinel-bug fix (2026-05-21)

The previous sentinel `"@@DONE_$$_MARKER@@"` matched the terminal echo of the
send line itself, causing the script to return BEFORE the command ran (output
was empty). New sentinel uses the **expanded** shell PID, which only appears
after the shell actually executes the `echo`. See current `ssh_shell.py`.

---

## 6. Why our `regtracer.ko` won't load on stock

```
insmod /tmp/regtracer.ko
  → can't insert: invalid module format
```

Vermagic matches exactly (`4.1.25 SMP mod_unload ARMv7`). The rejection is
subtler — probably a kernel-internal struct layout / `__mod_*` section drift
between our compiled kernel and ZTE's patched build. Stock kernel has
patches we don't have in our vanilla source.

**Workaround:** we don't need regtracer at all anymore — `/proc/tm/shell` +
`/dev/logger_main` gives us the same capabilities with zero compilation.

---

## 7. Capture recipe for init function call timeline

The stock init has already run by the time we SSH in. To **re-observe init**,
unload the chain and reload with debug on:

```sh
# 1. Open kernel printk capture in the background
ssh admin@192.168.1.1
cat /dev/logger_main > /tmp/init_trace.bin &
DPID=$!

# 2. Set debug level high on all stock modules
echo g_tm_debug_level=4    > /proc/tm/shell
echo g_switch_debug_level=4 > /proc/tm/shell
echo g_phy_dbg_lvl=4       > /proc/tm/shell

# 3. Unload in reverse load order (NOTE: shellproc is [permanent] → can't unload)
rmmod idmfdb
rmmod switch
rmmod tm
rmmod plat-zxylzb_9128S
rmmod zx_ponreg
rmmod patch

# 4. Reload in the order from /etc/init.norm
insmod /kmodule/patch.ko
insmod /kmodule/zx_ponreg.ko
sleep 5
insmod /kmodule/plat-zxylzb_9128S.ko
insmod /kmodule/tm.ko
insmod /kmodule/switch.ko

# 5. Replay the fpga init from /etc/init.norm
fpga -w 10006 2
fpga -w 10009 c8
fpga -w 1001a 61a88158
fpga -w 1001b bd8
fpga -w 10008 300
fpga -w 20013 1
fpga -w 20007 3e8
fpga -w 2000a 26202020
fpga -w 20040 01010101
fpga -w 20000 10040cb
fpga -w 2000c 6
fpga -w 20001 3c0001
fpga -w 20002 41900000
fpga -w 2003c 80000003
fpga -w 20041 400656

# 6. Bring up interfaces
ifconfig pon up
ifconfig sw up
ifconfig idm0 up; ifconfig idm1 up

# 7. Stop capture
sleep 2
kill $DPID
wc -c /tmp/init_trace.bin
```

Then pull `/tmp/init_trace.bin` via SSH and parse with the binary's headers
(each printk entry is wrapped in a logger header — see `/dev/logger_main`
format in ZTE log driver source, if found).

---

## 8. Capture recipe for TX-time register sequence (RX→TX)

(Proven 2026-05-21 — 258 KB captured during single ping.)

```sh
echo g_tm_debug_level=4 > /proc/tm/shell
cat /dev/logger_main > /tmp/txcap.bin &
DPID=$!
sleep 0.3
ping -c 1 192.168.1.50 > /dev/null
sleep 1
kill $DPID
```

---

## 9. Pending follow-ups

- Parse `/dev/logger_main` binary format. Each entry has a header (timestamp,
  module ID, source file, function, line, severity, message). The text we
  printed in section 3 examples was post-parsing.
- Diff the captured stock TX register sequence against our mainline 6.6
  driver's writes to find the missing TX-emit step.
- For stockport custom kernel: apply the config diff in section 4 and rebuild.

See [[STOCKPORT_PLAN]] for the stockport build flow.
