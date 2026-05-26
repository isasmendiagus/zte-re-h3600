# STATE — what's on the device RIGHT NOW

## Journey-to-date (so future-you remembers why)

1. Tried mainline 6.6 with PCIe / WiFi / wpa_supplicant — none worked.
2. Pivoted to building **our own ethernet driver** (`zx279128-eth.c`)
   using brute-force stock register replay (22,363 entries + 1025 pp_pm +
   780 CLA dumped via stock sysfs hooks). TX path partial; RX path dead.
3. **Got UART output on stock kernel**: cspd 3-byte patch + `kmsg2uart`
   daemon (mmap PL011 DR at ZTE-shifted `+0x04`, drain `/proc/kmsg`).
   Stock kernel has standard pl011 driver hard-coded to DR+0x00 (silent).
4. **Verified kprobes/ftrace are NOT compiled** in stock kernel
   (`# CONFIG_KPROBES is not set`, no `/sys/kernel/debug/tracing/`).
5. **Built kotrace** (loader-notifier + RAM patcher,
   `tasks/00.01.eth-driver/kotrace/`) — replaces target fn prologues with
   `b thunk` after the kernel loader resolves all symbols. Post-boot
   loading works for 2157 functions across plat/tm/switch/mt7915/idmfdb
   and routinely captures 32 k+ entries during a ping. Bake-in init
   capture (insmod via `/etc/init.norm`) is **parked** with a silent SoC
   reset — see `tasks/00.01.eth-driver/findings/kotrace_init_capture.md`.
6. **PING BIDI on mainline** (2026-05-24, task #50) — `pon_tm_net_tx` +
   `bp_idx 10-bit decode` + frame-at-`bp_buf+16` fixes landed; RX/TX
   both alive. Refactor + iperf still pending (tasks #37, #38, #47).
7. **WiFi works** (2026-05-04, `tasks/00.07.wifi/`) — MT7915 over the
   internal PCIe link → wlan0 + internet.
8. **Now**: post-boot kotrace captures + Ghidra are the live RE loop.
   Shell access on the bake-in slot-A rootfs is via netshell
   (`nc 192.168.1.1 9001`) since the ZTE-patched dropbear wedges on
   exec — see CLAUDE.md "SSH gotchas".

**Last updated**: 2026-05-26 (manually maintained; update when you
change slot A or boot a different kernel).

## Slot A NAND (kernel + rootfs)
- **Kernel at 0x700000**: stock (factory) — last touched 2026-05-22 ~13:00
  during mainline-flash attempts (those wrote then we recovered to stock).
- **Rootfs at 0xa60000**: stock-traced custom JFFS2 (cspd patched + kmsg2uart
  baked) from iter 8c. Slot A still has this rootfs even after mainline
  TFTP attempts (we never reflashed slot-A rootfs in those attempts).
- **Header at 0x2080000**: factory.

## Slot B NAND (kernel + rootfs)
- **Untouched factory stock** — always intact. cspstart falls back here
  if slot A header CRC mismatches OR JFFS2 magic missing.

## Currently running
- **Boot path**: most recent boot was via `uart.py auto_bootm_dtb_appended`
  → TFTP loaded `tftp/zImage_dtb.uimg` into RAM 0x42000000 → `bootm`.
- **Kernel**: mainline Linux 6.6 (`6.6.0-dirty`) compiled today.
- **rootfs**: in-RAM initramfs cpio embedded in the uImage. Contains:
  - `/init` — static ARM C binary, our REPL loop (forks busybox per command)
  - `/lib/modules/zx279128-eth.ko` — our driver
  - `/lib/firmware/zx-replay/{stock,cla,pm}.bin` — replay tables
  - `/bin/busybox` — **HARD-FLOAT** (will be replaced; see ROADMAP step 1)
- **Driver loaded**: yes (per `cat /proc/modules` = `zx279128_eth Live`)
- **sw netdev**: up, IP `192.168.1.99/24`, MAC `f4:f6:47:0f:42:64`
- **TX / RX**: bidi ping works since 2026-05-24 (task #50). Throughput
  not measured yet (#37 iperf pending).

## Last-known-good for fallback recovery

If anything breaks:

| Want | Run |
|---|---|
| Re-flash factory slot A (recovery to stock-traced kmsg2uart rootfs) | `python3 zxic/tasks/00.02.stock-shell/flash_slot_a_RECOVERY.py` |
| Re-flash the slot-A stock-traced custom rootfs (cspd patched + kmsg2uart) | `cd zxic/tasks/00.02.stock-shell && ./prepare_slot_a.sh --write` |
| Boot mainline from TFTP (in-RAM, no NAND change) | `python3 zxic/lib/uart.py auto_bootm_dtb_appended` |
| Get UART shell on running mainline | `python3 -c "from lib.uart import open_port; ser=open_port(); ser.write(b'\r')"`  → type commands |
| Reset device via DTR | `python3 zxic/lib/uart.py reset` |

## Open inflight things
- `/tmp/initramfs_extract/` — current staging dir kernel embeds. May
  contain stale .ko if you forget to copy after rebuild.
- TFTP daemon — was running with cwd at OLD `H3600/tftp` path; needs
  restart pointing at `zxic/tftp` (or it serves stale files).
- Background processes from earlier uart.py log sessions might still
  hold the serial port. `pkill -f uart.py` if stuck.

## Sanity check before any iter

```sh
cd ~/Projects/MYSELF/ZTE/zxic

# 1. TFTP serving from correct path?
ps -ef | grep '[i]n.tftpd'
# expected: -a 192.168.1.50:69 .../zxic/tftp
# if wrong path or not running: sudo tools/host/tftpd_start.sh
# (full docs: docs/HOST_SETUP.md)

# 2. No stale serial holders?
pgrep -fa "uart\.py"
# expected: empty

# 3. Device reachable?
ping -c 2 -W 1 192.168.1.1   # stock
# OR ping -c 2 192.168.1.99   # our mainline assigned IP
```
