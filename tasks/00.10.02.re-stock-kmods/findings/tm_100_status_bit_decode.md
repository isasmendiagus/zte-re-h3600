# TM[0x100] — bit-level status register decode

**Target**: `tm_base + 0x100` (phys `0x92340100`), the TM IRQ status
register. Paired with the mask at `tm_base + 0x104`.

Reconstructed entirely from static analysis of stock .ko decomp
(no live HW read required). All references are line numbers in
`decomp_all_plat_zxylzb_9128S.c` unless noted.

---

## 1. Register summary

| Reg | Offset | Purpose | Width | Set by | Cleared by |
|---|---|---|---|---|---|
| `IRQ_STATUS`    | `+0x100` | Pending-event bitmap. Stock IRQ handler inspects only **bits 0+1** (`& 3`) | 32-bit, but only low ~16 bits in use | HW | HW (no SW write ever observed; not W1C, not W0C from runtime experiments — see iter13) |
| `IRQ_MASK`      | `+0x104` | Per-bit mask, **1 = masked / suppress IRQ**, 0 = enable | 32-bit | SW | SW |
| (gap)           | `+0x108..+0x124` | Other TM-block regs (queue counters etc.) — not IRQ |  |  |  |
| `Q_INT_EN(?)`   | `+0x128` | Programmed once with `0x1fff` (13 bits) in `tm_pon_tm_init`. May be queue-interrupt enable mask (one bit per queue, up to 13 queues). Mainline observes value reverts to 0 — suspected Ghidra mis-read; per replay-table only 0x12c is written |  | SW | SW |
| `Q_INT_MASK(?)` | `+0x12c` | Live stock value `0x00001fff` (13 bits). Per-queue interrupt mask (1 = masked) for 13 queues |  | SW | SW |
| `FIFO_INT_EN(?)`| `+0x130` | Programmed with `0x1fffff` (21 bits) in `tm_pon_tm_init`. Suspected FIFO-int enable (overlaps the 8-FIFO + DMA + queue sub-block bits). Reverts to 0 in mainline — Ghidra mis-read suspected |  | SW | SW |
| `FIFO_INT_MASK(?)` | `+0x134` | Live `0x001fffff` on stock. Per-FIFO interrupt mask |  | SW | SW |

The hierarchy implied by the stock code:

```
   ┌────────────────────────────┐   bit 0 (RX_PENDING)
   │ TM[0x100] aggregate status │── bit 1 (TX_DONE)
   └────┬───────────┬───────────┘── bits 2..N: roll-ups
        │           │
   ┌────▼──────┐ ┌──▼─────────┐
   │ Queue int │ │ DMA-des int│  ← claRegTable indirect regs
   │ TM reg 0xb│ │ TM reg 0xc │
   └───────────┘ └────────────┘
                ┌──▼─────────┐
                │ FIFO int   │
                │ TM reg 0xd │
                └────────────┘
```

The aggregated bits in TM[0x100] are roll-ups of sub-block conditions
(per-queue, per-DMA-direction, per-FIFO). The IRQ handler only
filters down to bits 0+1; the rest are informational/error rollups
that **stay set until the underlying condition clears** — they are
not W1C.

---

## 2. Bit-by-bit table

Notation:
- **🟢 Confirmed** = direct evidence in stock decomp
- **🟡 Inferred** = consistent with multiple data points, not literally named
- **🔴 Hypothesis** = best guess given other reg widths / mainline experiments

| Bit | Name (decoded) | Meaning | Set when | Cleared when | Stock site | Conf |
|---:|---|---|---|---|---|---|
|  0 | `RX_PENDING`        | RX ring has descriptor(s) HW-written but not yet drained | HW completes RX desc (UP ring writes from switch fabric) | NAPI poll drains the queue (HW self-clears as queue count returns to 0) | `zx_pon_tm_int` plat:6311 (`& 3` mask) | 🟢 |
|  1 | `TX_DONE`           | TX ring has unconsumed descriptors (SW write-cursor > HW read-cursor) on UP or DN ring | HW DMA fires for any TX desc; bit asserted **while pending > 0** | HW consumes ALL pending TX descs (DN high-16 of `TM[0x10068]` returns to SW cursor) AND `TM[0x10058]/[0x10068]` low-16 are read (`pon_tm_check_tx_done_nolock`/timer) | `zx_pon_tm_int` plat:6311; reclaim in plat:6360 timer | 🟢 |
|  2 | `ERR_GENERIC(?)`    | Stock masks bit 2 in `pon_tm_net_stop` (`\|= 7`) and unmasks in `_open` (`& ~3` keeps bit 2 masked). Not inspected by handler. Likely a TM-internal error rollup | unknown | unknown | mask sites plat:6494,6519,6900,6966,8594 | 🟡 |
|  3 | `BMU_READY` / `BLOCK_OK`        | Steady-state "this TM block is configured & idle". Stock observes `=1` post-init when system is **idle** (no traffic); reads `0x00000008` in stock-kmod-init capture | After full TM bring-up: BPPE pool armed, DMA cfg done, queues initialized | When a runtime condition that breaks the steady state asserts (e.g. RX pending → bit 0 supersedes) | observed in stock dump `regs/stock_eth_2mib.txt:393281` reads `0x00000000` post-traffic-running; mainline-idle vs stock-idle diff | 🟡 |
|  4 | `??? (sometimes set)` | Saw `TM[0x100]=0x10` (bit 4 only) on one stock saved capture. Hypothesis: "BMU pool ≥ threshold" or "MAC link-up rollup". Refuted as IRQ trigger (handler uses `& 3`) | unknown | unknown | tm_irq_gate_investigation_2026-05-27.md L26 | 🟡 |
|  5 | `unknown`           |  |  |  |  | — |
|  6 | `unknown`           |  |  |  |  | — |
|  7 | `unknown`           |  |  |  |  | — |
|  8 | `FIFO_INT_ROLLUP_LO(?)` | One of the 8 FIFO interrupts (`pon_tm_set_fifo_int_mask` reg 0xd, 8 bits). Aggregated into TM[0x100] bit 8 likely | A FIFO crosses its watermark/error threshold without SW ack | SW reads/clears the FIFO sub-status via the claRegTable indirect path (`tmOnuRegRead(0xd,...)`) | tm.c:35212 (sub-block); aggregate inferred | 🔴 |
|  9 | `FIFO_INT_ROLLUP(?)` | second FIFO bit | same as bit 8 |  |  | 🔴 |
| 10 | `FIFO_INT_ROLLUP(?)` | third FIFO bit |  |  |  | 🔴 |
| 11 | `unknown`           |  |  |  |  | — |
| 12 | `DMA_DES_INT_UP(?)` | DMA descriptor interrupt UP direction. Stock `pon_tm_set_dma_des_int_mask(1,1)` (mask=1, dma_des=1=UP) — mainline value 1 = masked off (so unmasked = 0 if mainline doesn't write it) | UP-direction descriptor exception (underflow, fetch error) | Read-clears the sub-status via TM-reg `0xc` | tm.c:35117 sub-block; aggregate inferred | 🔴 |
| 13 | `DMA_DES_INT_DN(?)` | DMA descriptor interrupt DN direction. Stock `pon_tm_set_dma_des_int_mask(1,0)` (mask=1, dma_des=0=DN) | DN-direction descriptor exception | Read-clears via TM-reg `0xc` |  | 🔴 |
| 14 | `QUEUE_INT_ROLLUP(?)` | Aggregation of `pon_tm_set_queue_int_mask` results (3 queue bits, TM-reg 0xb). Set when **any** queue's interrupt is unmasked & condition fires | A queue crosses a threshold / desc-ring overflow / RED dropped frame on a still-armed queue | SW reads sub-status via TM-reg `0xb` | tm.c:35019 sub-block; aggregate inferred | 🔴 |
| 15 | `unknown`           |  |  |  |  | — |
| 16..31 | `unknown / reserved` | Stock writes mask `0xffffffff` initially (`pon_tm_int_init` plat:6338) then transitions to `0xfffffffc`. High 16 bits remain masked permanently. Most likely reserved | — | — | — | — |

**Critical observation: stock NEVER WRITES TM[0x100] anywhere.** A
full grep across all `decomp_all_*.c` finds:
```
plat:6311  uVar1 = *(tm_base + 0x100) & 3 & ~*(tm_base + 0x104);   ← read
```
and **zero** writes. Bench experiments (iter13) confirmed:
- Write `0x02` to TM[0x100] → bit 1 stays set
- Write `0x00` to TM[0x100] → bit 1 stays set

Therefore TM[0x100] is **read-only from SW**; bits self-clear when
the underlying HW condition ends. There is no W1C / read-clear
on the aggregate register itself.

---

## 3. Mainline-vs-stock diff explanation

| State | Mainline IDLE | Stock IDLE | Stock RUNNING (saved) | Stock RUNNING (live reg dump) |
|---|---|---|---|---|
| `TM[0x100]` | `0x00007702` | `0x00000008` | `0x00000010` (bit 4) | `0x00000000` |
| `TM[0x104]` | `0xfffffffe` (bit 0 only unmasked) | (post-init `0xffffffff`, then →`0xfffffffc` on open) | `0xfffffffc` | `0xfffffffc` |
| Bits set on **mainline only** | 1, 8, 9, 10, 12, 13, 14 | — | — | — |

Decoding the mainline-only bits using the inferred mapping:

- **Bit 1 (TX_DONE)** — there's TX-pending descriptors. Confirmed
  separately: `TM[0x10068]` high-16 = 7 (7 DN-direction descriptors
  HW has not consumed). HW TX consume engine is wedged
  (`915120431 findings: HW won't consume TX descriptors`). Bit 1
  is the *symptom* of that wedge.
- **Bits 8, 9, 10 (FIFO_INT_ROLLUP)** — 3 of the 8 FIFO interrupt
  bits are firing. The 8 FIFOs in stock are programmed via
  `pon_tm_set_fifo_int_mask(i, 1)` for `i ∈ [0..7]` — i.e. stock
  **masks all 8 FIFO interrupts**. Mainline doesn't write the
  FIFO mask sub-block (we never call into the equivalent of
  `tm_pon_tm_reg_initial` in tm.ko), so the FIFO interrupts are
  unmasked at the sub-block, and the 3 that report something on
  our bring-up assert via the aggregate rollup.
- **Bits 12, 13 (DMA_DES_INT_UP / DN)** — both DMA-descriptor
  interrupt directions firing. Stock programs
  `pon_tm_set_dma_des_int_mask(1,1)` (UP masked) and
  `pon_tm_set_dma_des_int_mask(1,0)` (DN masked). Mainline doesn't
  → both directions unmasked at sub-block → both rollups assert,
  most plausibly because the DMA descriptor rings aren't where HW
  expects them (re. `iter14`: `TM[0x10050]` UP base wrongly points
  at `txdesc_dma` instead of separate RX/UP BPPE pool address).
- **Bit 14 (QUEUE_INT_ROLLUP)** — one or more of the 3 queue
  interrupts is asserting. Stock programs
  `pon_tm_set_queue_int_mask(0,0)`, `(0,1)`, and `(1,2)` — i.e.
  queues 0+1 are unmasked, queue 2 is masked. Mainline doesn't
  program this → defaults (likely all unmasked) → queue rollup
  asserts on any per-queue threshold cross. The bench shows
  multiple queue counters non-zero in mainline (`q[0]=3 pending,
  q[2]=335 cursor, q[4]=368 cursor`) so a queue threshold IRQ is
  plausibly firing.
- **Bit 3 NOT set on mainline (vs. SET on stock idle)** —
  mainline never reaches the "block_ok" steady state because
  several sub-block init writes are skipped. Bit 3 likely
  asserts only when:
  - BMU enable + dma_cfg_byteorder + queue_init + queue_int_mask
    + dma_des_int_mask + fifo_int_mask + RED-init have all run.
  - In mainline, the `tm_pon_tm_reg_initial` chain from tm.ko
    (`pon_tm_set_*_int_mask` for queue/dma/fifo) is **never called**.

---

## 4. Top 5 candidate causes for the extra error bits

Ranked by likelihood × ease-of-test:

### #1 — `tm_pon_tm_reg_initial` (tm.ko) never runs in mainline (HIGH)

Stock's `tm_pon_tm_init` chains into `tm_pon_tm_reg_initial`
(decomp_all_tm.c:42448), which calls:
- `pon_tm_set_queue_int_mask(0,0)`, `(0,1)`, `(1,2)` — programs
  the 3-bit queue int mask sub-block
- `pon_tm_set_dma_des_int_mask(1,1)`, `(1,0)` — masks both DMA
  directions (2 bits)
- `pon_tm_set_fifo_int_mask(i, 1)` × 8 — masks all 8 FIFO ints
- `pon_tm_set_gap_add(4)` — IPG

Mainline calls only the direct-mmio writes from
`pon_tm_int_init` (`TM[0x104] = 0xffffffff`) and the per-queue
RED config (`pon_tm_red_init`). The sub-block IRQ-mask writes go
through the **claRegTable** indirect path
(`tmOnuRegWrite(0xb/0xc/0xd, ...)`) which depends on
`fpga_write_reg` (an EXPORTed symbol from plat-zxylzb). Mainline
doesn't have this indirection wired up to a backend. **Result:
the sub-block IRQ masks default to "everything unmasked", and
their roll-up bits (8–14 in our hypothesis) light up.**

Test: implement the equivalent of `tm_pon_tm_reg_initial` in
mainline (write the queue/DMA/FIFO sub-block masks). Bits 8..14
of TM[0x100] should clear afterward.

### #2 — DMA UP/DN base regs point at wrong RAM (HIGH for bit 1)

Per iter14 round-2: mainline writes `TM[0x10050] = e->txdesc_dma`
which is the **TX** descriptor ring, but `TM[0x10050]` is the
**UP** (switch→CPU = RX-side) base in stock's layout (the BPPE
pool region `pdt_mem + 0x405e0000`). HW fetches descriptors from
a region that doesn't contain UP descriptors → underflows →
asserts DMA_DES_INT_UP (bit 12). Then because the kicker
`TM[0x10054] = 1` is on the same UP DMA, it also wedges TX
consumption → bit 1 stays set forever.

This is the single most impactful fix; would clear bit 1 + bit 12
(and probably bit 13 if the DN base is also wrong) in one move.

### #3 — Queue thresholds tripping because RED queue config differs (MED)

Stock `tm_pon_tm_red_initial` (tm.ko:42487) programs per-queue
buffer thresholds across 1168 queues. Mainline runs an
equivalent "TM RED init" (Phase log shows "0 failed of 1168
queue configs"). But the **drop probability table** (`drop_p`
parameter: 0..0xc00 across queue ranges) might not match exactly;
if the queue thresholds are stricter on mainline, more queues
will cross "buffer near full" and the queue rollup (bit 14)
asserts.

Test: dump our RED-init drop_p values per-queue, compare to
stock's pattern (qid 0..0xf: drop_p=0; 0x10..0x14f: 0x7ff;
0x150..0x177: 0x80/0x200; 0x178..0x187: 0xc00; 0x188..0x18f:
0x3ff).

### #4 — `pon_tm_bmu_init` not run / different (MED for bits 8-10)

The FIFO interrupts are likely associated with the BMU pool's
FIFO state machines (BP-alloc, BP-free, etc., 8 FIFOs). If the
BMU is not fully initialized or the BPPE pool memory map differs,
the BMU FIFOs will assert ROLLUPs. Mainline's BMU init is
believed to be wired (`zx_bmu_alloc_bp`/`zx_bmu_free_bp` work),
but the **enable sequence** in stock is `bmu_init → set
TM[0xf0..0xfc] → pon_tm_bmu_enable → TM[0xc008]=0 → ...`. If
mainline skips the `TM[0xc008]=0` post-bmu-enable write (some
"bmu mode" register), the FIFOs may be in a half-initialized
state that asserts.

Test: verify `TM[0xc008]=0` is written. Verify `TM[0xfc] =
u32_BP_SIZE | u32_JUMBO_BP_SIZE << 0x10` matches stock.

### #5 — Missing `tm_pon_tm_init` direct writes `TM[0x128]`, `TM[0x130]` (LOW)

Decomp shows `tm_pon_tm_init` plat:7068-7069 writes:
```c
*(tm_base + 0x128) = 0x1fff;       // 13-bit mask
*(tm_base + 0x130) = 0x1fffff;     // 21-bit mask
```

Mainline does write these but observes them read back as 0
(see `tm_irq_gate_investigation_2026-05-27.md`). Either:
- Ghidra misread the offset (replay table only has 0x12c/0x134),
  in which case this is a no-op, OR
- Some later write clobbers them.

Low priority — even if these are genuine "sub-int enable" regs,
they sit *between* the IRQ_MASK at +0x104 and the per-queue
masks at +0x12c/+0x134, so they may be redundant. Worth
verifying with a runtime experiment (write + immediate read-back)
to determine if the addresses are even writeable.

---

## Cross-references

- `decomp_all_plat_zxylzb_9128S.c` lines 6280-6347 (pon_tm_dma_init,
  zx_pon_tm_int, pon_tm_int_init), 6478-6522 (open/stop), 6891-6911
  (pon_tm_net_int), 6947-6977 (pon_tm_net_init), 7058-7087
  (tm_pon_tm_init), 8562-8596 (pon_tm_net_poll)
- `decomp_all_tm.c` lines 35019-35330 (queue/DMA/FIFO int mask
  set/get), 42448-42525 (`tm_pon_tm_reg_initial`,
  `tm_pon_tm_red_initial`)
- `static_analysis_plat_zxylzb_init.md` fn-15, fn-18, fn-19,
  fn-29, fn-45, fn-46, fn-47
- `static_analysis_tm_ko_init.md` fn-05a, fn-05a-1 .. fn-05a-4,
  fn-05b
- Bench validations: `tasks/00.01.eth-driver/findings/iter13_*`,
  `iter14_*`, `tm_irq_gate_investigation_*`, `ping_bidi_irq_storm_*`
- Live stock register snapshot: `regs/stock_eth_2mib.txt`
  L393281-393293

---

## Caveats

- The bit assignments for bits 8–14 are **inferred** from a
  combination of:
  - The 8/2/3 widths of the sub-block masks (FIFO=8, DMA=2, queue=3)
  - Their physical proximity in the +0x100..+0x134 IRQ block
  - The exact set of bits showing up on mainline
  - Stock's "configure & mask everything" pattern in tm.ko
  No stock symbol literally says "bit 8 = FIFO 0 rollup". The
  hypothesis is consistent but unverified.
- Bit 3's role as "block ok" is the weakest claim — it's only
  derived from "stock idle reads 0x08 once everything is up".
  Could equally be a TX-empty flag or an "init complete" latch.
- The reads at +0x128 and +0x130 returning 0 in mainline despite
  our writes is unexplained. Could be Ghidra misread of the
  offset (the replay table only has +0x12c/+0x134), or the
  registers are RO/RW-restricted.
