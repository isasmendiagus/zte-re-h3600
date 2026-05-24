# Phase 4 plan — mainline driver port

What's blocking, what's done, what to do next.

---

## What we have (after Phases 0-3b)

- **Working tracer** (`tasks/00.01.eth-driver/kotrace/`) — can be extended
  with more targets any time without leaving the device unsafe (patches
  are RAM-only, removed on rmmod).
- **Call sequence + args** for `chip_tm_init` (610 entries, including all
  142 `pro_action` calls = the missing `def_ptl_pkt_action` table).
- **Existing mainline driver** at
  `linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c` — 2.5k LOC with
  partial chip_tm_init replay (`zx_chip_tm_init_trap_queues`,
  `zx_tm_pre_init`, `zx_tm_post_bmu`, `zx_tm_dma_init`) and a static
  register-replay infrastructure (`cla.bin`, `pm.bin`, `stock.bin`).
- **Extracted `pro_action` table** as a C header at
  `linux-v6.6/drivers/net/ethernet/zte/zx-pp-pro-actions.h` (ready to
  include from the driver).

## What's NOT yet known

For each of the 15 `zte_api_*` functions called by `chip_tm_init`, we
need to know **which registers it writes** (and the values it writes
to them) so we can replay the same writes from our mainline driver.

`zte_api_pp_set_pro_action` (the most-called, 142 times) is implemented
as a **giant jump table on the protocol id** — each of the 72 protocol
handlers does its own per-protocol register sequence. RE'ing all 72
handlers manually is ~1 day of Ghidra time.

`zte_api_sw_global_init` (called once) is simpler at the top level —
9 inner function calls — but each inner call (`sbrg_set_*`,
`tm_multivlan_mode_set`, `tm_tpid_vlu_select_get`,
`tm_in_port_tpid_select_set`, `zte_api_sw_other_set_onu_mtu`) needs
its own RE.

`zte_api_pp_set_trap_queue` is a thin wrapper: loops 5×, calls
`tm_protocol_pkt_limit_map_set(bank, proto, qid, 0)`. So 164 trace
entries → 820 actual `pkt_limit_map_set` calls. To know the register
layout, RE `tm_protocol_pkt_limit_map_set`.

## Three paths to making the driver work

Ranked by ratio of payoff to effort.

### Path 1 — drill deeper with kotrace (best ratio)

Extend `kotrace.c`'s `tm_targets[]` to include the **next layer** of
functions called by the 15 we already trace:

- `sbrg_set_table_sel` `sbrg_set_hash_mode`
  `sbrg_set_hash_collision_pktdeal` `sbrg_set_macaddr_exchange_md`
  `sbrg_set_multicst_md` (the `sw_global_init` inner callees)
- `tm_multivlan_mode_set` `tm_tpid_vlu_select_get`
  `tm_in_port_tpid_select_set` `tm_protocol_pkt_limit_map_set`
  (per-port + per-trap)
- ... and as many more as we find by `objdump -d --disassemble=<name>`
  on tm.ko one level at a time

At some point the trace bottoms out at functions that directly issue
`writel(reg, val)` — and **those args are exactly what mainline needs**.

Cost: ~2 hours per iteration (add N more targets, rebuild, reflash,
re-trace, parse new dump, add the NEXT layer). After 3-4 iterations we
should reach raw register writes.

### Path 2 — extend the trace to capture writel itself

Add a 21st target `__raw_writel` (the ARM kernel inline that wraps
all writel calls in modules). The thunk captures `(r0=val, r1=addr)`
on every register write anywhere in tm.ko's call chain. Single
iteration gives the complete register-write log — no more drilling.

Cost: ~3 hours. Risk: `__raw_writel` is called EVERYWHERE in the
kernel, not just tm.ko. We'd capture millions of entries per second,
overflow the buffer instantly, and our marker→function mapping is
lost because writel is shared across all functions.

Mitigation: gate the writel hook on caller-PC range. Check LR at thunk
entry, only log if `tm.ko_text_base ≤ lr ≤ tm.ko_text_end`. Adds ~6
extra instructions per thunk; still very feasible.

### Path 3 — static RE of all 15 functions in Ghidra

Open the tm.ko project at `tasks/00.10.02.re-stock-kmods/ghidra/`,
walk through each function's decompiled C output, transcribe to our
driver.

Cost: ~6 hours per function (some are bigger) × 15 = ~90 hours. Most
thorough but slowest.

## Recommended next iteration

**Path 1 — drill once more**:

```c
/* kotrace.c: add to tm_targets[] */
{ "sbrg_set_table_sel",                 'a' },
{ "sbrg_set_hash_mode",                 'h' },
{ "sbrg_set_hash_collision_pktdeal",    'k' },
{ "sbrg_set_macaddr_exchange_md",       'x' },
{ "sbrg_set_multicst_md",               'M' },
{ "tm_multivlan_mode_set",              'n' },
{ "tm_tpid_vlu_select_get",             'T' },
{ "tm_in_port_tpid_select_set",         'I' },
{ "tm_protocol_pkt_limit_map_set",      'L' },
{ "zte_api_sw_other_set_onu_mtu",       'O' },
```

Build, reflash, boot (~6 min round trip). Re-dump `/proc/kotrace_dump`
— now will be much larger (~3000-5000 entries) but with deeper
coverage.

After that captures: if we're seeing concrete register addresses + values
in the args, we're at the level the driver needs.

## Risks / open items

- Ring buffer is 4096 entries. With deeper drilling, easily blow that
  in one chip_tm_init. Bump to 16k or implement a "stop capture at
  ring full" flag.
- `__raw_writel` (Path 2) requires the kernel's actual writel symbol;
  on ARM with cache flushes, it may go through `__sync_icache_dcache`
  or similar wrappers. Verify the symbol exists in kallsyms first.
- 0x14 inconsistency in `pro_action` (PP0 traps, PP1 forwards): may
  matter for actual RX behavior — double-trace to confirm not a
  capture race.

## Once the driver compiles

```bash
# Mainline kernel rebuild (fast — only changed files)
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- O=../build \
     drivers/net/ethernet/zte/ -j$(nproc)
# RAM-only test boot (no NAND touch — preserves stock):
python3 lib/uart.py auto_bootm_dtb_appended
# Check RX from the host:
ping -c 5 192.168.1.1 &       # local ARPs trigger rx
ssh admin@192.168.1.1 'cat /proc/net/dev'   # rx_packets must be > 0
```

If `rx_packets == 0`: drill more. Use kotrace runtime path (no reflash)
to compare stock register state vs mainline post-init via a `devmem`
sweep.
