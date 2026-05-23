# Stock-as-Oracle Strategy

**Status:** active path forward (2026-05-21)
**Replaces:** stockport (compile vanilla 4.1.25 → run stock .ko) — DEAD END
**Final goal:** working bidirectional ping on mainline Linux 6.6 `zx279128-eth.c`

---

## Why stockport failed

`plat-zxylzb_9128S.ko` reports:
```
vermagic: 4.1.25 SMP mod_unload ARMv7
(no __versions section)
```

Vermagic matches vanilla 4.1.25, but ZTE built it **without modversions/CRC
enforcement**. The kernel loader accepts it. Then every hardcoded field offset
(`ldr r0, [r4, #0x12c]` etc.) — baked at compile time against **ZTE's patched
4.1.25 headers** — references the wrong place inside our vanilla structs.

The cascade is the entire kernel struct universe:
`net_device`, `sk_buff`, `napi_struct`, `netdev_queue`, `netdev_rx_queue`,
`device`, `module`, …

Each binary-patch fix unblocks the next crash. Never converges. We tried.

Sources of truth (none reachable):
- ZTE GPL portals → consumer-mobile only, no ONU code (verified 2026-05-21,
  395 packages across 4 categories, all Qualcomm/Mediatek/Hisilicon).
- GitHub / Gitee → symbol search ran cold.
- Operator OEM (Digi) → refused GPL request.

## What we keep instead

**Stock kernel, running on the real device, as a live oracle.** We never load
anything compiled-against-vanilla-headers into stock; we never load
stock-compiled binaries into our kernel. The two stay isolated.

Stock supplies: register sequences, function call ordering, packet flow,
struct layout discovery.

Our mainline v6.6 driver supplies: a place where we control the ABI and can
keep iterating.

## Instrumentation toolbox (rated by friction)

### Tier 0 — already working
- `/proc/tm/shell` — call any kernel/.ko function by name. ZTE's own debug REPL.
- `/dev/logger_main` — captures every `printk`. Drain into a file.
- `/proc/kallsyms` — 82,727 symbols. addr ↔ name resolved at runtime.
- `devmem2`, `fpga -r OFF`, `dumpregs.sh` — read any register, any time.
- Before/after diffs around any function call → "what regs did THIS touch?".

### Tier 1 — kprobes — **DEAD ON STOCK (verified 2026-05-22)**
Stock kernel was built with `# CONFIG_KPROBES is not set` (confirmed from
`/proc/config.gz` on the running device). `HAVE_KPROBES=y` only means the
ARM port supports it; the framework is not actually compiled in.
`/sys/kernel/debug/tracing/` does not exist — even the tracefs interface
is absent.

The original idea was:
```
echo 'p:probe_chip_tm chip_tm_init' > /sys/kernel/debug/tracing/kprobe_events
echo 1 > /sys/kernel/debug/tracing/events/kprobes/probe_chip_tm/enable
cat /sys/kernel/debug/tracing/trace_pipe
```

This path is only available if we rebuild the kernel (see Tier 6 / option E).

### Tier 2 — ftrace — **ALSO DEAD ON STOCK (verified 2026-05-22)**
`CONFIG_FTRACE=y` is in the config but it's just the supporting framework.
`# CONFIG_FUNCTION_TRACER is not set` and no `/sys/kernel/debug/tracing/`
node exists, so there is nothing to write to. Same kernel-rebuild
requirement as Tier 1.

### Tier 3 — ABI-safe tracer .ko (always works)
A trivial module that uses **only opaque kernel APIs** — no struct refs.
```c
extern unsigned long kallsyms_lookup_name(const char *);
// resolve any symbol → call it → printk results
```
Vermagic-only check passes against any 4.1.25 build. We can use it to:
- Live-patch a target function's prologue with `B trampoline`
- Trampoline saves regs, printks, returns to original
- Effectively a hand-rolled kprobe

Only needed if Tier 1 and Tier 2 are both disabled.

### Tier 4 — pre-load .ko patching
If even Tier 3 is impossible: binary-patch `plat.ko` BEFORE insmod to inject
`BL printk` at desired instruction sites. We have toolchain + objdump + offset
patching infrastructure in `auto_patch_plat.py`. Recycle that for tracing,
not ABI fixing.

### Tier 5 — stock-shipped tracers (verify what they do)
The stock firmware ships these in `/lib/modules/4.1.25/`:
- `regtracer.ko` — name suggests register-write tracer
- `memlog.ko` — memory access logger?
- `sbrgdump.ko` — SBRG state dumper
- `netdev_probe.ko` — netdev structure prober

If any of these does what its name says, **enable on real stock device** and
get free instrumentation.

## Pipeline (once oracle is online)

```
                                   ┌─────────────────────────────┐
  ┌──────────────────────────┐    │  Stock device (192.168.1.1) │
  │  Host (Linux dev box)    │    │                              │
  │                          │    │  - Stock kernel 4.1.25       │
  │  scripts/                │ssh │  - Stock plat/tm/switch.ko  │
  │  ├─ dump_stock_regs.py   │◄──►│  - kprobes/ftrace traces     │
  │  ├─ capture_tx_regs.py   │    │  - /proc/tm/shell REPL       │
  │  ├─ dump_stock_function.py│   │                              │
  │  └─ trace_replay_gen.py  │    └─────────────────────────────┘
  │         │                │
  │         ▼                │
  │  H3600/linux-v6.6/       │
  │  drivers/.../zx279128-eth.c
  │  (replay sequence here)  │
  └──────────────────────────┘
```

Capture → diff → replay loop:
1. Snapshot regs before stock TX → ping 1 packet → snapshot after → diff
2. Diff = exact bytes stock wrote during TX
3. Add those writes (in order) to mainline driver `zx_sw_xmit()`
4. Boot mainline, verify ping works
5. Repeat for RX, init, link-up, MTU change, etc.

## Tasks affected

- Drop tasks targeting stockport convergence (was task #95-ish path A)
- Keep / restart these:
  - #87 PORT chip_tm_init (now via trace replay)
  - #89 zte_api_pp_global_init + cpu_queue_rate
  - #90 def_ptl_pkt_map + def_ptl_pkt_action
  - #91 SchRegTable / QmgRegTable decode
- New (2026-05-22):
  - ✅ Verified kprobes / ftrace availability on stock → both OFF; Tier 1+2 dead
  - ✅ kmsg2uart daemon now ships kernel printk live to UART (slot A custom rootfs) → use this as the BOOT-TIME audit source (Tier 0)
  - Audit existing boot UART log first to see what info stock-built-in printks already give (cheapest)
  - If gaps remain: choose between Tier 3 (hook-module via `kallsyms_lookup_name`), Tier 4 (binary-patch .ko + inject `BL printk`), or Tier 6 (rebuild stock kernel with `CONFIG_KPROBES=y`)

## What we do NOT do anymore

- ❌ Recompile vanilla 4.1.25 to ABI-match stock
- ❌ Binary-patch plat.ko's struct offsets to load on our kernel
- ❌ Hunt ZTE GPL for ONU code (exhausted)
- ❌ Map sk_buff / napi_struct / netdev_queue layouts struct-by-struct

## What's locked in

- ✅ Mainline v6.6 driver is the production target
- ✅ Stock running on real device is the trace source
- ✅ No foreign-ABI binaries in either direction
