# Stock CPU→LAN egress: empirical debug-trace attempt (2026-05-28)

**HEADLINE (EMPIRICAL): debug level 4 produces NO datapath trace.** With
`g_tm_debug_level=4` AND `g_switch_debug_level=4` enabled on factory stock, a
host `ping` that the device echoed back out MAC2/LAN (confirmed CPU→LAN egress)
produced **ZERO kernel-log lines** — no `call func`, no `fpga_write_reg`, no
per-frame printk anywhere. The egress hot path is silent at every debug level.
The task's method (capture `call func` / `fpga_write_reg` lines emitted during
egress) is not achievable, because that printk is NOT a datapath hook.

## What the trace actually showed (empirical)

Live factory stock (`Linux H3600 V9 4.1.25`, root SSH admin/UkuGPeyRDU,
paramiko `invoke_shell`). Device already booted stock; ping 192.168.1.1 = 11ms,
3/3 and 5/5 replies each run = egress confirmed.

1. **`/dev/logger_main` carries USERSPACE daemon logs, not the kernel trace.**
   A 2s capture with NO debug = 264 KB, 0 `call func`, 0 `fpga_write_reg`; the
   only `call func`-ish hit was `Call function failed! startSlaacInst` (a
   userspace daemon). logger_main is the wrong sink for kernel debug — the
   prior `capture_tx_regs.py` assumption was incorrect.
2. **Kernel debug goes to the kernel ring (`/proc/kmsg`).** Writing
   `echo g_tm_debug_level=4 > /proc/tm/shell` DID land in kmsg as
   `<4>sym g_tm_debug_level set to 4(...)` — so the WRITE path works and the
   knob is the right name. (Matches the prior oracles, which read fpga via
   `/proc/kmsg`, not logger_main.)
3. **With debug=4, a 5-packet egress ping produced 0 kmsg lines.** `cat
   /proc/kmsg` across the ping window = `0 /tmp/k2.txt` (empty). Repeated with
   3-packet ping: also empty. The egress path emits no printk even at level 4.

## Why (cross-checked in decomp — NOT empirical)

The `call func %s,with p %x` format string the task expected is the
**`/proc/tm/shell` `-f <symbol> <args>` RPC echo**, not a datapath trace. It is
the shell's own "I am now invoking this function pointer" log:
`decomp_all_shellproc.c:1531-1607` (case 3: `kallsyms_lookup(sym)` →
`printk("call func %s,with p %x",...)` → `(*pcVar5)(args)`). Duplicated in
`decomp_all_plat_zxylzb_9128S.c:675-728`. It ONLY fires when YOU invoke a
function via the shell (as `capture_tx_regs.py` did:
`echo -f fpga_read_reg 0x... > /proc/tm/shell`). The egress path never routes
through this RPC, so no `call func`/`fpga_write_reg` lines appear during a real
ping. `g_tm_debug_level` gates control-plane verbosity only; the fast egress
path has no debug printk at all (consistent with 0 kmsg lines observed).

## Doorbell hypothesis (from decomp + the three ring oracles — NOT from a trace)

No passive trace was obtainable, so the doorbell can only be inferred. The three
live oracles (UP / IDM / DN ring counters all flat 0 while QMG sw_fwd
0x9234c044 + MAC2 TX-OK 0x92280718 climb in lock-step) rule out any DMA-ring
kick. `0xd3011` (QMG sw_fwd) appears in decomp ONLY in a stats-dump
(`decomp_all_tm.c:46575`), confirming it is a HW counter incremented by the
fabric, not a SW-written doorbell. So the enqueue is a **fabric/BMU operation,
not a ring kick**: BMU buffer alloc (`0x921c8014` request / `0x921c800c` BP
index, `pon_tm_bmu_alloc_bp`) + frame copy into the BP buffer + a descriptor
carrying the GEM/egress-port nibble (`src_port+0x28`, lan_up=4 → GEM 0x2c) that
the PP_BRG DA-lookup resolves to MAC2. The remaining gate is MAC2
egress-enable, CONTROL[0] bits 0,1 (`0x92280000`), per `sopc_spa_cpu_egress_re.md`.

## Recommendation for next RE

A passive printk trace is impossible. To find the exact sw_fwd enqueue write
empirically, the only viable method is a **before/after register diff across
the BMU + fabric-inject window** (the oracle pattern, extended): poke-read
`0x921c8014`/`0x921c800c` (BMU alloc) and candidate fabric-inject regs during a
ping, looking for the write whose effect makes 0x9234c044 climb with all ring
counters at 0. Decomp `pon_tm_data_raw_send`/`pon_tm_bmu_alloc_bp` is the map.

## Device left
On STOCK. Debug knobs set back to 0 (verified write path). All /tmp capture
files removed. Only `/proc/tm/shell` debug knobs were written — no hardware
registers, no NAND, no reboot. SSH closed cleanly.

## Artifact
Adapted capture script: `tasks/00.01.eth-driver/scripts/capture_egress_trace.py`
(note: it targets logger_main per the original method — superseded by the kmsg
finding above; the egress path emits nothing in either sink).
