# Phase 4 — session 2 wall analysis (2026-05-24)

## State after this session

### What now works (vs session 1)
1. **Probe completes cleanly** — bulk replay (whitelisted to TM/PP/NPP/pon-low only)
   no longer hangs the AHB bus. PON/IDM/other unidentified sub-blocks at
   0x80000-0x1c0000, 0x200000-0x340000 etc. are SKIPPED in bulk replay because
   writing to them when their clock/reset isn't enabled by stock's plat module
   locks the bus.
2. **TOPCRM stock-match writes** added: `[0x4c] = 0x0003cfff`, `[0x08] = 0x1ff7ffff`.
   Some bits differed from stock defaults.
3. **C-init REPL on UART confirmed working** — can send commands and read
   /proc/interrupts, /sys/kernel/debug/zx_eth/stats, etc.
4. **Stock + mainline live introspection** — paramiko ssh_shell, memdump
   cross-built, dumped TOPCRM/TM/NPP/PP from STOCK boot to
   `tasks/00.01.eth-driver/captures/fpga/*_stock.txt`.

### What still doesn't work
**TM IRQ count remains 0** (GIC line 68 never fires) despite:
- HW IS receiving packets (rxdesc canaries overwritten in mainline, BP area has
  ethernet frame data with valid MAC headers)
- HW IS processing buffers (ALLOC_BPCNT ~15k, RLS_BPCNT ~15k after some time)
- **TM[0x100] = 0x7710** in mainline (status bits 4, 8-10, 12-14 SET, but bits
  0/1 = RX/TX done are CLEAR)
- Stock's IRQ handler `zx_pon_tm_int` only fires on `status & 3` (bits 0/1)
- Stock has TM[0x100] = 0x010 (bit 4 only) at dump time and IRQ count = 129

### Root cause narrowed
The HW receives packets but **bits 0/1 of TM[0x100] never get set** in
mainline — these are the RX/TX-done bits that actually trigger GIC line 68.
The other status bits (4, 8-14) presumably go to a different IRQ line or are
status-only.

What enables bits 0/1 to fire on RX/TX-done? Stock has some additional
config we don't replicate. Candidates:
1. **pon_tm_red_init** — 4 loops of red_set_queue_cfg (queue management).
   Stock calls this; we don't.
2. **pon_tm_net_init** — registers NAPI poll callback + adds timer +
   `*(u32*)(tm_base+0x104) |= 7`. We have NAPI; missing OR-7 and timer.
3. **pon_tm_int_init** — writes `TM[+0x104] = 0xffffffff` (try changed our
   value from 0xfffffffc to 0xffffffff but it caused silent hang — needs
   investigation).
4. **plat-zxylzb's `pon_int_enable`/`pon_npp_int_enable`/`idm_int_enable`** —
   exported functions we never call. They `bic` bits in registers at
   tm_base+0x40044 and npp_base+0x8024. May be the actual gate for
   FPGA→GIC IRQ output.

## Captures collected this session
- `captures/fpga/topcrm_stock.txt` — 4KB dump of 0x94000000 from stock
- `captures/fpga/tm_block_stock.txt` — 256KB TM block 0x92340000
- `captures/fpga/npp_block_stock.txt` — 256KB NPP block 0x921c0000
- `captures/fpga/pp_block_stock.txt` — 256KB PP block 0x92380000
- `captures/fpga/pon_low_stock.txt` — 64KB pon block 0x92000000
- `captures/fpga/range_9fe_stock.txt` — 4KB at 0x9fe00000

## Tooling improvements
- `scripts/tftp_boot_mainline.py` — bypass cspstart, just TFTP+bootm. No NAND
  flash. Reverts to stock on power-cycle. Much faster iteration.

## Next session priorities
1. Look at `pon_int_enable`/`pon_npp_int_enable`/`idm_int_enable` in detail —
   their writes (tm_base+0x40044, npp_base+0x8024, etc.) are obvious IRQ gates.
   Call equivalents from our driver.
2. Implement `pon_tm_int_init` equivalent: `TM[+0x104] = 0xffffffff` then
   `request_threaded_irq` (vs our `request_irq`). NOTE: testing showed
   0xffffffff write earlier caused silent hang — figure out why (maybe needs
   to be done AFTER bulk replay, not before).
3. Implement `pon_tm_net_init`'s `TM[+0x104] |= 7` — sets bits 0-2.
4. Then validate by counting `cat /proc/interrupts` → pon_tm > 0.

## Lessons learned
1. **Bulk replay of FPGA state CAN hang the AHB bus** when writing to
   sub-blocks that stock pre-enables via topcrm clock bits. Whitelist-only
   replay is necessary.
2. **`request_firmware` works in initramfs** — but only when /lib/firmware/
   contents are reachable. Always reaches CKPT3 (start of replay loop).
3. **`flash_mainline.py` slot A flashing produces CRC mismatch with kernel >
   ~11 MiB** because of bad-block-skip arithmetic interaction with cspstart's
   verify. **`tftp_boot_mainline.py` (no NAND flash) is the safer iteration path.**
