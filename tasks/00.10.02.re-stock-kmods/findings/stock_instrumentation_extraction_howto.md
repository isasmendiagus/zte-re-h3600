# Stock instrumentation & data-extraction — the 3 mechanisms (how-to)

How we "register" instrumentation on the running device and "extract" the
data back to the host. Three independent mechanisms, each with its own
register/trigger/extract loop. Written 2026-05-28 alongside
`stock_egress_fn_trace_re.md` (which used #1).

Quick chooser:
- **What function ran / call order / its r0–r3 args** → #1 kotrace.
- **Free-form kernel printk / boot-time text / live markers** → #2 kmsg2uart.
- **Read/write a SoC register live, no reboot** (mainline driver only) → #3 port 9999.

---

## 1. kotrace.ko — function-entry tracer ("koprobe")

A loadable module that RAM-patches a target function's first instruction with
`b thunk`; the thunk records `(marker, func_addr, r0,r1,r2,r3)` to a ring and
restores the original instruction on rmmod. Works on the STOCK kernel (which
has NO kprobes/ftrace compiled in). Source:
`tasks/99.01.linux-stockport/kotrace/kotrace.c`.

### Register (choose targets + build)
- Full mode: targets come from `kotrace_targets.h` (auto-generated, 2157 fns,
  by `tasks/00.10.02.re-stock-kmods/scripts/generate_kotrace_targets.py` from
  `ARG_SIGNATURES.json`). Big ring, noisy.
- Focused mode (preferred for a specific question): hand-write a small targets
  header (see `kotrace_targets_egress.h` — 8 fns, unique markers), copy it over
  `kotrace_targets.h`, build, then restore the full header. Tiny ring, minimal
  disturbance to the live module.
- Build (Debian gcc gotcha — see below):
  ```sh
  cd tasks/99.01.linux-stockport/kotrace
  cp kotrace_targets_egress.h kotrace_targets.h          # focused
  make clean
  make CROSS=arm-linux-gnueabihf- KCFLAGS="-march=armv7-a -fno-pic -fno-PIE"
  cp kotrace_targets.h.full.bak kotrace_targets.h         # restore full
  ```
  - vermagic must read `4.1.25 SMP mod_unload ARMv7` (matches stock).
  - kotrace targets by SYMBOL NAME via the loaded module's per-module kallsyms;
    it patches modules already-loaded at insmod time AND any that load later
    (MODULE_STATE_COMING notifier). Verify your fn names exist:
    `arm-linux-gnueabi-nm ext/kmodules_dump/<mod>.ko | grep <fn>`.
  - Useful insmod params: `patch_modules=plat_zxylzb_9128S,switch` (whitelist),
    `patch_skip=fnA,fnB`, `patch_pct=50`, `patch_limit=N` (bisect aids).

### Get the .ko onto the device (factory dropbear has NO sftp)
TFTP pull from the host tftpd (already serving `~/Projects/MYSELF/ZTE/tftp`
at 192.168.1.50):
```sh
cp kotrace.ko ~/Projects/MYSELF/ZTE/tftp/kotrace_egress.ko        # host
# device (via paramiko invoke_shell, user admin / pass UkuGPeyRDU):
cd /tmp && tftp -g -r kotrace_egress.ko -l /tmp/kotrace.ko 192.168.1.50
insmod /tmp/kotrace.ko
```
`/tmp` is tmpfs (rw, 20 MB); rootfs is jffs2 ro → RAM-only, nothing persists.

### Trigger + extract (the data)
```sh
echo > /proc/kotrace_dump            # reset ring (clean window)
# ... cause the path to run, e.g. from HOST:  ping -c 5 192.168.1.1
cat /proc/kotrace_dump               # TEXT dump, one line per call
```
Dump line format: `<seq> <marker> <func_addr> <r0> <r1> <r2> <r3>` (all hex).
Resolve func_addr → name: `runtime_addr − module_base = nm offset`
(module base from `lsmod`; nm offset from `arm-linux-gnueabi-nm <mod>.ko`).
The `/proc` text dump over SSH is the reliable extraction path. The thunk ALSO
emits markers to PL011 directly (ioremap, independent of kmsg2uart) which is a
handy live confirmation but not the data of record.

### Cleanup (rmmod is SAFE)
```sh
rmmod kotrace        # restores all patched prologues; device keeps forwarding
rm -f /tmp/kotrace.ko
```
Confirm with `lsmod | grep kotrace` (gone) and a ping. Power-cycle also clears
everything (RAM-only).

### BUILD GOTCHA (cost ~30 min — document so we never repeat)
Debian `arm-linux-gnueabihf-gcc` is `--enable-default-pie`. A plain build emits
a `_GLOBAL_OFFSET_TABLE_` (PIC) reference; the 4.1.25 module loader then fails
with the misleading `insmod: ... unknown symbol in module, or unknown
parameter`. FIX: `KCFLAGS="-march=armv7-a -fno-pic -fno-PIE"`.
- `-march=armv7-a` is required so inline `dsb`/`dmb` assemble (else the
  cc-option fallback sets the compiler to armv5t → "selected processor does
  not support `dsb`").
- Do NOT add `-mfpu=neon` / hard-float — the kernel Makefile appends
  `-msoft-float -mfpu=vfp` (module ABI). Adding neon/hard-float gives a
  different "unknown symbol" rejection.
- Confirm the fix: `arm-linux-gnueabi-readelf --wide -s kotrace.ko | awk
  '$7=="UND"{print $NF}'` should NOT list `_GLOBAL_OFFSET_TABLE_`.

---

## 2. kmsg2uart — kernel printk → UART bridge

Stock 4.1.25 ships the standard pl011 driver hard-wired to DR `+0x00`, but the
ZTE PL011 has its data register at `+0x04` → stock console is silent.
`kmsg2uart` is a tiny static-ARM daemon that reads `/proc/kmsg` and writes each
byte to PL011 DR at PHYS `0x94404000 + 0x04` via `/dev/mem`. Source +
README: `tasks/00.02.stock-shell/{kmsg2uart.c,kmsg2uart_nolibc.S,README.md}`.

### Register / start
- It's BAKED into the slot-A custom rootfs (cspd-patched + kmsg2uart), started
  from `/etc/rc` (or `/etc/init.norm`). On the plain FACTORY stock rootfs it is
  NOT running (and not needed for kotrace, which writes PL011 itself).
- Recovery/build of that rootfs: `tasks/00.02.stock-shell/prepare_slot_a.sh
  --write`; artifacts in `out/` (see STATE.md "Last-known-good" table).

### Extract (host side)
Read the serial line with the project UART helper:
```sh
python3 lib/uart.py log        # stream UART to stdout / log file
```
(`lib/uart.py` also does `reset` via DTR, bootm sequences, marker-waits.)
Anything the kernel `printk`s — including kotrace's `[ko: …]` patch log and the
per-call markers — appears here. This is the BOOT-TIME / free-text audit
channel; for structured per-call data prefer kotrace's `/proc` dump (#1).

---

## 3. Port 9999 — live register poke/peek (MAINLINE driver only)

A TCP REPL (`localhost:9999`, the UART bridge socket) that execs one busybox
applet per line on the device, exposing our mainline driver's debugfs. Lets us
read AND write SoC registers with NO rebuild/reboot. **This is a feature of OUR
`zx279128-eth.ko` (debugfs in `zx-eth-main.c`), so it only exists when the
device is booted on our MAINLINE build — NOT on stock.** Full detail:
`tasks/00.01.eth-driver/findings/live_poke_peek_tool.md`.

### Register / available nodes (mount once per boot)
```sh
mount -t debugfs none /sys/kernel/debug
```
| node | dir | what |
|---|---|---|
| `/sys/kernel/debug/zx_eth/stats` | r | driver counters + TM/PP/MAC/PHY regs |
| `/sys/kernel/debug/zx_eth/regdump` | r | hex-TEXT `<phys> <val>` (UART-robust) |
| `/sys/kernel/debug/zx_eth/poke` | w | `"<phys> <val>"` hex → `writel` (phys ∈ [0x921c0000,0x923c0000), 4-aligned) |
| `memdump <hexphys> <hexlen>` | bin | physical-addr hex dump (no /dev/mem) |

Address map: `phys = 0x921c0000 + e->base_off`. MAC2/host = 0x92280000;
TM[0x10054] = 0x921d0054; PP[0x8340] = 0x92388340; SMCT gauges 0x921d0040/4c.

### Drive it (host side)
```python
import socket, time
s = socket.create_connection(("localhost", 9999), timeout=10); s.settimeout(2.0)
def run(cmd, w=1.2):
    s.sendall(cmd.encode()+b"\r"); time.sleep(w)
    o=b""
    try:
        while True:
            d=s.recv(8192)
            if not d: break
            o+=d
    except socket.timeout: pass
    return o.decode("utf-8","replace")
run("mount -t debugfs none /sys/kernel/debug")
print(run("memdump 92280000 c"))                                   # peek
run('''sh -c "echo '92280008 80000001' > /sys/kernel/debug/zx_eth/poke"''')  # poke
print(run("cat /sys/kernel/debug/zx_eth/stats"))
```
Note: one applet per line — no `;`/`|`/redirect directly, but `sh -c "..."`
gives you redirects (that's how poke is written).

### Gotchas
- QMG block (e->base+0xc000) is HW-rewritten — pokes don't stick.
- Enabling MAC[2] (`+0x08`) with incomplete bring-up → packet STORM; always
  poke `<macbase>+0x08=0` after a test.
- Binary `mem` reads drift over UART; prefer hex-TEXT `regdump`/`memdump`.

---

## Cross-reference
- Result produced with #1: `findings/stock_egress_fn_trace_re.md` +
  `findings/eg_kotrace_dump.txt`.
- printk-splice alternative to #1 (entry-only, on-disk ELF patch, MEMWRITE
  thunk because printk crashes from the hand-crafted context):
  `tasks/00.01.eth-driver/scripts/ko_printk_splice.py` +
  `research/printk_injection_methodology.md`. kotrace is preferred (RAM
  patch after loader resolves symbols → no ELF/reloc surgery, rmmod-safe).
- Stock's own debug knobs (no instrumentation at all):
  `tasks/00.01.eth-driver/scripts/capture_egress_trace.py` writes
  `g_tm_debug_level/g_switch_debug_level=4` via `/proc/tm/shell` and captures
  `/dev/logger_main` — datapath untouched, but only as verbose as ZTE's own
  log statements.
