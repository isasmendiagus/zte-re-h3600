# Phase 4 — session summary (2026-05-24)

This session combined the trace data from Phases 2-3c with hands-on driver work
to attempt to bring up RX on the mainline `zx279128-eth` driver. We made
significant infrastructure progress but **did not achieve bidirectional ping**.
This doc captures what's now in place, where the wall is, and the most
sensible next moves.

---

## Final state

### Driver code (`linux-v6.6/drivers/net/ethernet/zte/`)

| Change | What it does |
|---|---|
| `eth->fpga_base = devm_ioremap(dev, 0x92000000, 0x400000)` | Unified 4 MiB FPGA window (pon+npp+idm+tm+pp blocks), matching stock `zx_ponreg.ko`'s virt-mapping. |
| `#include "zx-fpga-reg-tables.h"` | All 20 stock register descriptor tables (~700 entries) decoded statically from `tm.ko`. |
| `#include "zx-pp-pro-actions.h"` | The 71-entry `def_ptl_pkt_action` table (trap-vs-forward per protocol) extracted from kotrace runtime args. |
| `zx_fpga_table_write()` helper (in header) | Read-modify-write via the descriptor-table semantics (handles bit mask + shift). |
| `zx_tm_port_isolate_set(port, mask)` | Equivalent of stock `tm_port_isolate_set`. Per-port isolation register. |
| `zx_chip_tm_init_isolate()` | Loops 8 ports — runs at probe. |
| `zx_spa_set_enty_pktdeal_cfg(port, proto, action)` | Equivalent of stock `spa_set_enty_pktdeal_cfg`. Writes packet-deal config. |
| `zx_chip_tm_init_pro_action()` | Loops 8 ports × 71 protos using the extracted `def_ptl_pkt_action` table. |
| Bulk FPGA-state replay block | Loads `/lib/firmware/zx-replay/fpga.bin` (sparse blob from stock dump). Applies 25019 non-trivial register writes; skips 496 DDR-pointing regs (stock's 0x4Exxxxxx addresses don't apply to mainline's CMA). |
| `writel(0xa, fpga+0)` | Attempted IRQ enable per stock's `sbrg_set_irq_en_mask(0xa)` call — turned out to be a no-op (sbragRegTable[0] has mask=0). Left in code, harmless. |
| `TM_BPPE_POOL_SIZE 8192 → 1024` | Fixed pre-existing `dma_alloc_coherent` failure (18MB single alloc exceeded default CMA). |

### Tooling

- **`tasks/00.04.02.uart-bridge/`** — daemon + pyserial-compat client, exposes /dev/ttyUSB0
  on TCP for concurrent host-side monitor + flash. Auto-restart wrapper.
- **`flash.py --uart-tcp` default-on** — opt-out via `--direct-uart`.
- **`lib/uart.py`** — `UART_TCP=1` env var routes through bridge.
- **`tasks/00.01.eth-driver/kotrace/`** — Idea A working tracer
  ([findings/idea_a_kotrace.md](idea_a_kotrace.md)). Now also includes
  `pdt_ethdrv_recv`, `ethdrv_recv_fin`, `sbrg_set_irq_en_mask` targets for
  RX-path debugging.

### Captures collected this session

| File | Size | Content |
|---|---|---|
| `captures/kotrace_p3c_full_args.txt` | 213 KB | 4738 trace entries × 49 functions × r0–r3 args |
| `captures/kotrace_p3c_analysis.txt` | 24 KB | Distinct arg patterns per function |
| `captures/rx_path_trace.txt` | small | RX-path markers during stock ping (117 `*` = pdt_ethdrv_recv calls) |
| `captures/irq_trace.txt` | small | Shows stock calls `sbrg_set_irq_en_mask(0xa)` once during boot |
| `captures/fpga/fpga_stock_working.bin` | 4 MiB | Full FPGA window from stock when ping works (25515 non-trivial dwords) |

### Mainline boot behaviour (2026-05-24)

- Probe completes cleanly. driver loads. `[INIT] ip link set sw up` works.
- `sw netdev` registered at `192.168.1.99/24`, MAC populated.
- TX: ~15 packets/1146 bytes leave the netdev (ARP attempts from kernel).
- RX: **0 packets** — host `tcpdump -i enxc8a362e95900` sees nothing either way.
- `cat /proc/interrupts` → `20: 0 GIC-0 68 Level zx279128-eth-tm` → **TM IRQ count = 0**.
- BMU stats DO move (`ALLOC_BPCNT` ~16k, `RLS_BPCNT` ~16k) — hardware IS pulling buffers,
  but the IRQ never reaches the kernel so our NAPI poll never runs.

### The wall

The TM block is silently allocating/releasing BMU buffers (so the front-end of
RX HW is alive) but **the level-triggered IRQ to GIC line 68 never fires**.
Multiple hypotheses tested and ruled out:

1. ❌ `sw_open`-side `TM[0x104] = 0xfffffffc` (block-level IRQ unmask) — already done, didn't help.
2. ❌ `writel(0xa, fpga+0)` (replicating stock `sbrg_set_irq_en_mask(0xa)`) — no effect; sbragRegTable[0] has mask=0 so stock's call IS a no-op.
3. ❌ Bulk replay of 25019 stock FPGA register values — no effect on IRQ.

What's still untried (= where we'd go in the next session):

| Path | Effort | Likely payoff |
|---|---|---|
| Compare full FPGA state dump of stock-running-with-ping vs mainline-running-no-ping → find delta in IRQ-control regs | 1-2 iter cycles, ~30 min | High — direct evidence of which register stock has that we don't |
| Trace deeper sub-functions of `pdt_ethdrv_recv`'s caller (the actual IRQ handler) — find what register stock READs on each interrupt | More kotrace targets + ping trace | Medium — but pdt_ethdrv_recv has no direct callers (function pointer dispatch), needs more digging |
| Verify GIC-side IRQ routing in our DTS — could be that 68 isn't the right HW IRQ number for TM block | Read DT + DT-binding doc | Low risk but easy to rule out |

---

## Why this session is a real milestone even without ping

Before this session, the eth-driver task had three open questions:

- **What does `chip_tm_init` actually call, and in what order?** → SOLVED (Phase 3c trace, 4738 entries)
- **What are the register addresses behind the API?** → SOLVED (Phase 4 — all 20 RegTables decoded; helper extracts `(base, stride, mask, shift)` per `(table, reg_id)`)
- **What's the def_ptl_pkt_action table?** → SOLVED (Phase 3c capture, extracted to zx-pp-pro-actions.h)

The remaining gap is **finding the exact write that enables TM IRQ generation
to the GIC**. That's a few-hour problem with the tooling we now have, not the
multi-day open question it was at session start.

---

## Files to commit

```
# New files
linux-v6.6/drivers/net/ethernet/zte/zx-fpga-reg-tables.h
linux-v6.6/drivers/net/ethernet/zte/zx-pp-pro-actions.h
tasks/00.01.eth-driver/findings/idea_a_kotrace.md
tasks/00.01.eth-driver/findings/chip_tm_init_sequence.md
tasks/00.01.eth-driver/findings/chip_tm_init_args.md
tasks/00.01.eth-driver/findings/ko_splice_bugs.md
tasks/00.01.eth-driver/findings/phase4_driver_port_plan.md
tasks/00.01.eth-driver/findings/phase4_wall.md
tasks/00.01.eth-driver/findings/driver_codegen_demo.md
tasks/00.01.eth-driver/findings/phase4_session_summary.md   (this file)
tasks/00.01.eth-driver/findings/captures/kotrace_*.txt
tasks/00.01.eth-driver/findings/captures/irq_trace.txt
tasks/00.01.eth-driver/findings/captures/rx_path_trace.txt
tasks/00.01.eth-driver/PLAN_init_debug.md
tasks/00.01.eth-driver/kotrace/{*.c,*.h,Makefile,README.md,build_rootfs_with_kotrace.py,.gitignore}
tasks/00.01.eth-driver/scripts/ko_loader_sim.py
tasks/00.04.02.uart-bridge/{README.md,uart_bridge.py,lib_uart_tcp.py,research/design.md}
tasks/00.01.01.fix-lief-rel-sections/README.md

# Modified files
linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c   (Phase 4 additions: fpga_base, helpers, isolate, pro_action, bulk replay, IRQ attempt)
lib/uart.py                                          (UART_TCP env var routing)
tasks/00.04.flash-tool/{flash.py,uboot_flash.py,README.md}   (--direct-uart flag, default to bridge, reset timeout 240→60)
tasks/00.01.eth-driver/README.md                     (children/findings refs)
tasks/00.01.eth-driver/research/printk_injection_methodology.md
TASKS_TREE.md
LEARNED.md
CLAUDE.md

# DO NOT commit (binaries, caches, build outputs)
ext/kmodules_dump/                  (stock .ko blobs, large)
tasks/00.01.01.fix-lief-rel-sections/LIEF/   (huge upstream tree)
tasks/00.01.eth-driver/captures/fpga/*.bin   (4 MiB binary dumps)
tasks/00.01.eth-driver/initramfs/lib/firmware/zx-replay/fpga.bin   (200 KB regenerable blob)
tftp/                              (regeneratable build artifacts)
build/                             (gitignored already)
**/__pycache__/
.claude/
```
