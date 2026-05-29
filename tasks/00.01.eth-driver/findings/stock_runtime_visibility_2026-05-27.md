# Stock runtime register visibility — /dev/fpga + sysfs paths

Empirical finding captured 2026-05-27 — describes how to read stock H3600
HW state at runtime from userspace, what works vs what doesn't, and the
mapping that lets us correlate `fpga_*_reg` calls to physical addresses.

## TL;DR

Stock exposes **two userspace paths to peripheral state**:

1. **`/dev/fpga` char device** (major 222, from `zx_ponreg.ko`) — used via
   `fpga -r REG NUM` and `fpga -w REG DATA` binaries. Works for **most**
   blocks (PP/NPP/MAC/SERDES/switch fabric). **Does NOT work for TM** —
   reads as 0 from outside tm.ko's runtime context (HW-gating effect).

2. **`/sys/devices/platform/tm/tmTest/{tmup,tmdn,...}` sysfs entries** —
   `cat` them to dump the full per-stage pipeline statistics. Output goes
   to `printk` (capture via `/proc/kmsg`). Reads via tm.ko's
   `tmOnuRegRead` which DOES unblock TM gating.

Mainline equivalent needed: a debugfs `pipeline_stats` entry that reads
the same regs via our driver's TM accessor pattern.

## The fpga interface — addressing model

### Mechanics

`zx_ponreg.ko` hardcodes `pon = 0xf4000000` (kernel VA) and exposes
`fpga_read_reg(idx)` / `fpga_write_reg(idx, val)` which do:

```c
return *(u32 *)(pon + idx*4);
*(u32 *)(pon + idx*4) = val;
```

So each `sub_block_id` is a **32-bit dword index** into a unified
kernel-virtual register window starting at `pon`. The window is a
static iomap (made at kernel boot via `iotable_init`) of a physical
range starting at `phys = 0x92000000`. Empirically verified:

```
phys = 0x92000000 + sub_block_id * 4
       i.e.
sub_block_id = (phys - 0x92000000) / 4
```

### Verified mapping table

Captured live on stock 2026-05-27:

| Block | Phys address | sub_block_id | Verified value | Identity |
|---|---|---|---|---|
| pon top | `0x92000000` | `0x00000` | `0x00000000` | base |
| reg `0x10000` | `0x92010000` | `0x10000` | `0x27912810` | unknown — version/ID? |
| reg `0x20000` | `0x92020000` | `0x20000` | `0x010040cb` | unknown |
| TM top | `0x92180000` | `0x60000` | **`0x00000000`** ← HW-gated | TM[0x000] |
| TM IRQ status | `0x92180100` | `0x60040` | **`0x00000000`** ← HW-gated | TM[0x100] |
| MAC[0] ctrl | `0x92200000` | `0x80000` | `0x00ba6003` ✓ | LAN1 |
| MAC[0] en | `0x92200008` | `0x80002` | `0x80000001` ✓ | LAN1 enable |
| MAC[2] ctrl | `0x92280000` | `0xa0000` | `0x00ba6003` ✓ | LAN3 |
| MAC[2] en | `0x92280008` | `0xa0002` | `0x80000001` ✓ | LAN3 enable |
| MAC[4] ctrl | `0x92300000` | `0xc0000` | `0x00ba6003` ✓ | WAN |
| MAC[4] en | `0x92300008` | `0xc0002` | `0x80000001` ✓ | WAN enable |
| PP top | `0x92380000` | `0xe0000` | `0x00000001` ✓ | PP[0] |
| switch alarm reg | `0x9234c000` | `0xd3000` | `0x03f40050` ✓ | link-UP value |
| NPP SPA reg | `0x921d4054` | `0x75015` | `0x03ff05dc` ✓ | NPP SPA |

⚠️ TM block (`sub_block_id` 0x60000..0x6FFFF) reads as **0** even though
the block is alive (pon_tm IRQ fires 100/ping on stock). PP/MAC in
adjacent address ranges read correctly. **Not a /dev/mem filter** —
fpga -r is going through the kernel-mapped VA and still gets 0. This is
HW-level gating tied to tm.ko's runtime access pattern.

### How to use it

The `fpga` binary is on stock at `/bin/fpga`. Usage:

```
fpga -r <reg hex> <count dec>     # read NUM 32-bit regs starting at hex addr
fpga -w <reg hex> <data hex>      # write data to reg
```

**Quirk**: output goes to `printk` (not stdout), so you need to capture
kernel log. Klogd is NOT running on stock, so `/proc/kmsg` is undrained
— we can read it briefly. Script pattern:

```sh
#!/bin/sh
OUT=/tmp/kmsg.out
> "$OUT"
cat /proc/kmsg > "$OUT" 2>&1 &
KPID=$!
sleep 0.3
for spec in "$@"; do
    addr=$(echo "$spec" | cut -d, -f1)
    count=$(echo "$spec" | cut -d, -f2)
    fpga -r "$addr" "$count"
done
sleep 0.3
kill $KPID
cat "$OUT"
```

Saved as `tasks/00.01.eth-driver/scripts/stock_fpga_dump.sh`. Usage:

```
./stock_fpga_dump.sh 0xd3000,1 0x80000,4 0xa0000,1
```

## The sysfs path — runtime pipeline statistics

### What works

`cat /sys/devices/platform/tm/tmTest/tmup` and `tmdn` dump comprehensive
per-stage stats for the upstream (UNI→CPU) and downstream (CPU→UNI)
paths. These are **READ-ONLY** entries (cat, not echo) and the read
internally calls tm.ko's `tm_smac_statistics1` + friends, which traverse
the TM regs via `tmOnuRegRead` — the access pattern that DOES unblock
TM gating.

Also writable entries that accept a port index:
- `gportstatistics1..4` (write port idx → printk per-port counters)
- `nppGreg/gportstatus` (write port → printk port link state)

### Stock pipeline snapshot under ping load (captured 2026-05-27)

Stock pinging 30/30 0% loss 0.6ms via LAN3:

```
UPSTREAM (UNI → CPU):
  smac0 (LAN1) recv:  72
  smac2 (LAN3) recv:  72
  smac4 (WAN)  recv:  376
  sdet uni0 egress_transport: 72  drop: 0
  sdet uni2 egress_transport: 72  drop: 0
  sdet uni4 egress_transport: 120 drop: 0
  sipc2cpu_aful_cnt_up: 6   ← "almost full" warnings (benign)
  spa_fwd: 76, spa_trp: 44  ← 44 trapped to CPU
  cla trap pkts: 144
  pm recv: 1526, pm trap: 1526
  qmg hw trap pkts: 144
  usch in/out que: 0

DOWNSTREAM (CPU → UNI):
  QMG sw fwd: 1527
  DSCH out que: 247
  sopc_send2smac0 (LAN1): 474
  sopc_send2smac2 (LAN3): 462   ← matches my tcpdump frame count exactly
  sopc_send2smac4 (WAN):  591
  smac0 send total frame: 474
  smac2 send total frame: 462
  smac4 send total frame: 591

ERROR counters (all blocks): ALL ZERO
  smct, bmu, qmg, red, pp_ctrl, uopc, dma → no drops, no malformed
```

The full list of counters available is in
`tasks/00.01.eth-driver/findings/stock_sysfs_debug_tree_2026-05-27.md`.

### Implications for mainline debugging

When booting mainline + running same probe script, we get per-stage
breakdown of where in the pipeline frames die:

| If mainline counter ... | Implication |
|---|---|
| `smacN recv` < stock | MAC RX not receiving frames — PHY or MAC issue |
| `spa_fwd` + `spa_trp` < stock | Classification/parser dropping early |
| `cla trap pkts` < stock | CPU-bound frames not being classified to trap |
| `qmg hw trap` < stock | Queue manager not forwarding to trap path |
| `sopc_send2smacN` < stock | Software path not producing TX frames |
| Any `*_drop_cnt` > 0 | Direct pointer to where drops happen |

## The TM-gating mystery

Reading TM regs from outside tm.ko's runtime context returns 0. Two
hypotheses:

**H1**: tm.ko's `tmOnuRegRead` does pre-read + post-read writes to a
"register access window enable" reg, then accesses the target reg
between. Without those wraps, the AXI slave returns 0.

**H2**: TM block has clock-gating that's tied to active tm.ko ioctls or
sysfs accesses. When idle/no-access, slave gates off; reads return 0.

For mainline implications:
- If H1: we need to **replicate the wrap pattern** in our driver. Without
  it, all our `tm_read()`/`tm_write()` calls would silently return 0.
- If H2: we need to keep TM "alive" — but that contradicts the fact that
  our existing mainline reads (e.g. `tm_read(e, 0x100)`) DO get non-zero
  values (`0x0a`, `0x02` — see prior findings).

Most likely interpretation: **H1, but only for certain ranges**. We've
seen mainline `tm_read(e, 0x100)` succeed, which means our `tm_read`
already does the right thing (via the address `e->base + 0x180000 + 0x100`).
But userspace /dev/fpga + /dev/mem at the SAME phys address read 0.

Theory: kernel-side accesses via the original ioremap (with shareable
attribute) work; userspace mappings via /dev/mem (non-shareable) get a
NULL response from the bus matrix for TM specifically. The other blocks
(PP/MAC) are mapped via the same kernel ioremap, but their AXI slaves
accept both shareable and non-shareable transactions.

This is a guess; without proper datasheet access we can't confirm.

## Action items for mainline driver

1. **Add debugfs `/sys/kernel/debug/zx_eth/pipeline_stats`** that prints
   the same per-stage counter values as stock's `tmTest/tmup` + `tmdn`.
   These counters live in TM/PP/NPP regs accessible via our existing
   `tm_read()` (which works from kernel-context). The output format
   should mirror stock so we can `diff` side-by-side.
   
2. **Verify our `tm_read()` works for ALL relevant TM offsets** —
   recall that `TM[0x100]` reads `0x0a` for us live, so the kernel-side
   path works. But we should systematically dump TM[0x000..0x140] and
   TM[0x10000..0x10080] in mainline and compare with what stock's
   `tmup`/`tmdn` printk shows.

3. **Document the fpga-id → phys-addr mapping** in our driver source
   header — so future contributors can use `fpga -r N` on stock and
   translate to mainline reg offsets.

## Cross-refs

- `tasks/00.01.eth-driver/scripts/stock_fpga_dump.sh` — fpga -r capture script
- `tasks/00.01.eth-driver/findings/stock_sysfs_debug_tree_2026-05-27.md` — full sysfs entry inventory
- `tasks/00.10.02.re-stock-kmods/findings/static_analysis_*.md` — per-kmod function inventories
- `tasks/00.01.eth-driver/findings/stock_init_deep_re_2026-05-27.md` — init flow gap analysis
