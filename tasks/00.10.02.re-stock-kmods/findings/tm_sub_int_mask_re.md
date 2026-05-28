# tm.ko sub-interrupt mask RE — `tm_pon_tm_reg_initial`

**Goal**: reverse-engineer the three stock tm.ko helpers
(`pon_tm_set_queue_int_mask`, `pon_tm_set_dma_des_int_mask`,
`pon_tm_set_fifo_int_mask`) called from `tm_pon_tm_reg_initial`
(decomp_all_tm.c:42448) and identify their effective physical
writes so mainline `zx-eth-main.c` can replicate them and stop
spurious TM[0x100] sub-block rollups (bits 8-14 in mainline).

All references are to `decomp_all_tm.c` and
`decomp_all_plat_zxylzb_9128S.c` unless noted. Confirmed against the
raw ARM assembly in `ext/rootfs/kmodule/tm.ko` and the live register
dump at `findings/regs/stock_eth_2mib.txt`.

---

## 1. `tm_pon_tm_reg_initial` — full walk (tm.c:42448)

```c
uint tm_pon_tm_reg_initial(void) {
    /* --- queue int mask: 3 bits (one per "queue") --- */
    pon_tm_set_queue_int_mask(/*val=*/0, /*idx=*/0);  /* bit 0 := 0 (unmask) */
    pon_tm_set_queue_int_mask(/*val=*/0, /*idx=*/1);  /* bit 1 := 0 (unmask) */
    pon_tm_set_queue_int_mask(/*val=*/1, /*idx=*/2);  /* bit 2 := 1 (mask)   */

    /* --- DMA descriptor int mask: 2 bits (UP/DN) --- */
    pon_tm_set_dma_des_int_mask(/*val=*/1, /*idx=*/1); /* bit 4 := 1 (mask) UP */
    pon_tm_set_dma_des_int_mask(/*val=*/1, /*idx=*/0); /* bit 3 := 1 (mask) DN */

    /* --- FIFO int mask: 8 bits, all masked --- */
    for (int i = 0; i < 8; i++)
        pon_tm_set_fifo_int_mask(/*idx=*/i, /*val=*/1); /* bits 8..15 := 1 */

    /* --- Inter-packet gap --- */
    pon_tm_set_gap_add(4);   /* writes 4 to reg id 0x1 via the same table */
    return 0;
}
```

The function emits **no direct mmio writes** — every register touch
goes through `tmOnuRegRead/tmOnuRegWrite` (decomp_all_tm.c:35337,
:35356) which uses a per-block descriptor table.

---

## 2. The indirect register protocol

### 2.1 `tmOnuRegRead/Write` mechanics

```c
int tmOnuRegRead(uint id, uint *out, int idx, void *table) {
    /* validates id and dir, then: */
    void *entry = table + id * 0x1c;
    u32 raw = fpga_read_reg(entry->stride * idx + entry->addr);
    *out = (raw >> entry->shift) & entry->mask;
}

int tmOnuRegWrite(uint id, uint value, int idx, void *table) {
    void *entry = table + id * 0x1c;
    int regidx = entry->stride * idx + entry->addr;
    u32 cur = fpga_read_reg(regidx);
    fpga_write_reg(regidx,
        (cur & ~(entry->mask << entry->shift)) |
        ((value & entry->mask) << entry->shift));
}
```

`fpga_read_reg(idx)` (zx_ponreg.ko export, decomp_all_zx_ponreg.c:1):

```c
u32 fpga_read_reg(int idx) { return *(volatile u32 *)(pon + idx * 4); }
```

`pon` is a global virtual address set to `0xf4000000` (zx_ponreg.c:110).
On this SoC the 0xf4000000 VA is a fixmap alias for the 0x92000000
SoC peripheral window, so `fpga_read_reg(idx)` reads phys
`0x92000000 + idx*4`.

### 2.2 Entry struct (28 bytes, from `tmOnuGlbRegValidation` :35310)

| Offset | Width | Name | Notes |
|---|---|---|---|
| 0x00 | u16 | id | must match arg `param_1` |
| 0x02 | u16 | pad | |
| 0x04 | u32 | dir | 1=RO, 2=WO, 3=RW |
| 0x08 | u32 | addr | word index passed to `fpga_read_reg` |
| 0x0c | u32 | mask | bit-field mask (after shift) |
| 0x10 | u16 | shift | bit shift inside the word |
| 0x12 | u16 | max | max value of `idx` (param_3) |
| 0x14 | u32 | stride | added per `idx` step |
| 0x18 | u32 | counter | bookkeeping (++ on every hit) |

### 2.3 The table (`tm.ko` `.data` @ 0x76ec, the `DAT_00045498/740/9ec` pointer)

Decoded from raw bytes (objdump -s -j .data ext/rootfs/kmodule/tm.ko):

| id | dir | addr (word idx) | mask | shift | max | name | resolves to |
|---:|---:|---:|---:|---:|---:|---|---|
| ... | ... | ... | ... | ... | ... | (earlier entries: gap_add etc.) | |
| 8 | 1 (RO) | 0xd0040 | 0x07 | 0 | 0 | queue_int_state | TM[0x100], bits [2:0] |
| 9 | 1 (RO) | 0xd0040 | 0x03 | 3 | 0 | dma_des_int_state | TM[0x100], bits [4:3] |
| 10 | 1 (RO) | 0xd0040 | 0xff | 8 | 0 | fifo_int_state | TM[0x100], bits [15:8] |
| **11** | **3 (RW)** | **0xd0041** | **0x07** | **0** | **0** | **queue_int_mask** | **TM[0x104], bits [2:0]** |
| **12** | **3 (RW)** | **0xd0041** | **0x03** | **3** | **0** | **dma_des_int_mask** | **TM[0x104], bits [4:3]** |
| **13** | **3 (RW)** | **0xd0041** | **0xff** | **8** | **0** | **fifo_int_mask** | **TM[0x104], bits [15:8]** |

`fpga` base 0x92000000 + idx 0xd0040 * 4 = phys `0x92340100` = `TM[0x100]`.
`fpga` base 0x92000000 + idx 0xd0041 * 4 = phys `0x92340104` = `TM[0x104]`.

**The "sub-block int mask" functions are NOT a separate sub-block —
they are RMW bit-field accessors for TM[0x100] (status) and TM[0x104]
(mask) themselves.**

### 2.4 Effective writes from `tm_pon_tm_reg_initial`

Starting state (after `pon_tm_int_init` :6338): `TM[0x104] = 0xffffffff`.

| Call | Effect on TM[0x104] |
|---|---|
| `pon_tm_set_queue_int_mask(0, 0)` | bit 0 := 0 → `0xfffffffe` |
| `pon_tm_set_queue_int_mask(0, 1)` | bit 1 := 0 → `0xfffffffc` |
| `pon_tm_set_queue_int_mask(1, 2)` | bit 2 := 1 → `0xfffffffc` (no-op) |
| `pon_tm_set_dma_des_int_mask(1, 1)` | bit 4 := 1 → `0xfffffffc` (no-op) |
| `pon_tm_set_dma_des_int_mask(1, 0)` | bit 3 := 1 → `0xfffffffc` (no-op) |
| `pon_tm_set_fifo_int_mask(0..7, 1)` | bits 8..15 := 1 → `0xfffffffc` (no-op) |

**Final**: `TM[0x104] = 0xfffffffc` — matches stock live dump exactly
(`9234012c 00001fff` was a separate observation; the IRQ mask itself
is at 0x92340104 = `fffffffc`).

So the whole `tm_pon_tm_reg_initial` sequence boils down to one
single mainline write:

```c
writel(0xfffffffc, tm_base + 0x104);   /* mask bits 2..31, leave 0,1 unmasked */
```

`pon_tm_set_gap_add(4)` is a separate concern (TM gap, not IRQ
related; uses a different table addr — earlier entries in the same
table).

---

## 3. Bit decode correction for TM[0x100] / TM[0x104]

The previous `tm_100_status_bit_decode.md` table is **partially wrong**
about bits 12–14. Corrected mapping (per the .data table just decoded):

| Bit(s) | What | Stock-init final value in TM[0x104] |
|---:|---|:---:|
| 0 | RX_PENDING / queue 0 | 0 (unmasked) |
| 1 | TX_DONE / queue 1 | 0 (unmasked) |
| 2 | queue 2 | 1 (masked) |
| 3 | DMA_DES DN | 1 (masked) |
| 4 | DMA_DES UP | 1 (masked) |
| 5..7 | reserved | 1 |
| 8..15 | FIFO 0..7 rollup | 1 (all masked) |
| 16..31 | reserved | 1 |

So mainline's `TM[0x100] = 0x7702` decodes as:

```
bit 1   = TX_DONE                    (real RX/TX engine issue)
bit 8   = FIFO 0 rollup              (sub-block)
bit 9   = FIFO 1 rollup              (sub-block)
bit 10  = FIFO 2 rollup              (sub-block)
bit 12  = FIFO 4 rollup              (sub-block, NOT DMA_DES)
bit 13  = FIFO 5 rollup              (sub-block, NOT DMA_DES)
bit 14  = FIFO 6 rollup              (sub-block, NOT DMA_DES)
```

`pon_tm_set_fifo_int_mask(i, 1)` for i ∈ [0..7] sets bits 8..15 of
TM[0x104] to 1, which **prevents these from routing to the IRQ
line**, but the STATUS register TM[0x100] still latches the
underlying condition. So if mainline writes `TM[0x104] = 0xfffffffc`
post-init, mainline's IRQ handler will see the same `& 3` view as
stock (lines :6311) — but TM[0x100] reads will still show the
sub-block conditions firing.

---

## 4. Other lifecycle TM[0x104] writes (plat-zxylzb)

| Site | Operation | Final value |
|---|---|---|
| `pon_tm_int_init` :6338 | `TM[0x104] = 0xffffffff` | mask all |
| `tm_pon_tm_reg_initial` (tm.ko) | RMW per table → effective `0xfffffffc` |
| `pon_tm_net_init` :6966 | `TM[0x104] \|= 7` | `0xffffffff` (re-mask 0..2) |
| `pon_tm_net_open` :6519 | `TM[0x104] &= 0xfffffffc` | `0xfffffffc` (open) |
| `pon_tm_net_int` :6900 | `TM[0x104] \|= 7` | mask before NAPI schedule |
| `pon_tm_net_poll` :8594 | `TM[0x104] &= 0xfffffffc` | NAPI complete re-enable |
| `pon_tm_net_stop` :6494 | `TM[0x104] \|= 7` | mask on stop |

Steady-state running: `TM[0x104] = 0xfffffffc` (live dump confirms).

---

## 5. What clears bit 1 (TX_DONE) of TM[0x100] in stock?

`TM[0x100]` is **read-only from SW** (no writes anywhere in any
stock kmod; bench tests in iter13 confirmed writes are ignored).
Bit 1 represents "TX ring has unconsumed descriptors". It self-
clears when HW finishes consuming TX descriptors.

The trigger for HW to do that work is the **TX descriptor count
read-clear** at `TM[0x10058]` (UP) and `TM[0x10068]` (DN). Stock
`pon_tm_check_tx_done_nolock` (:6360) issues these reads from the
periodic `pon_tm_timer_func` (:6436, runs every jiffy):

```c
net_txq[1] -= TM[0x10058] & 0xffff;   /* UP: clear-on-read low-16 */
net_txq[3] -= TM[0x10068] & 0xffff;   /* DN: clear-on-read low-16 */
```

The read also signals the HW DMA controller "I've acknowledged
these completions, advance the descriptor ring". Once HW's pending
descriptor count drops to zero, TM[0x100] bit 1 self-clears.

(This was confirmed empirically — see git commits 546ae0b3a /
80f610eda.)

Mainline's TX_DONE persists because the underlying TX engine is
wedged: the UP DMA base register `TM[0x10050]` is pointed at the
wrong RAM region (see `tm_100_status_bit_decode.md` §4 #2), so HW
never gets to "all consumed" and the reclaim timer reads zero.
Adding the int_mask sequence will **not** clear bit 1.

---

## 6. Mainline patch suggestion (what to add, not the code)

### 6.1 Where

In `zx-eth-main.c`, the probe path that currently calls
`pon_tm_int_init` equivalent (writes `TM[0x104] = ~TM_IRQ_ARM_BITS =
0xFFFFFFFE`). Replace that single write with the masked-FIFO-and-DMA
variant.

### 6.2 What

A single writel — there is no claRegTable protocol to wire up
because the indirect path collapses to one register:

```
writel(0xfffffffc, tm_base + 0x104);   /* mask bits 2..31, unmask RX_PENDING + TX_DONE */
```

That is functionally identical to executing the entire
`tm_pon_tm_reg_initial` int-mask sequence.

### 6.3 Whether it will help bits 8-14 in TM[0x100]

**No.** TM[0x104] mask gates IRQ routing, not status latching. Bits
8-14 in TM[0x100] reflect actual sub-block conditions (FIFO
rollups). Masking them off only stops the IRQ from being routed to
the CPU on those bits. Since stock's IRQ handler already only
inspects `TM[0x100] & 3 & ~TM[0x104]`, mainline's handler doing
the same with `0xfffffffc` mask is sufficient to ignore the FIFO
noise. The displayed `TM[0x100] = 0x7702` would persist until the
true underlying issues are fixed (UP-base mis-pointing, BMU init,
etc., per the bit-decode doc §4).

### 6.4 Optional `pon_tm_set_gap_add(4)` equivalent

Not IRQ-related. `pon_tm_set_gap_add` writes value 4 to the gap_add
sub-block via reg id 0x1 of the same table. Decoding that entry is
left for a follow-up; only relevant if mainline traffic shows
inter-frame-gap issues.

---

## 7. Source cross-reference

- `decomp_all_tm.c:35019` `pon_tm_set_queue_int_mask`
- `decomp_all_tm.c:35117` `pon_tm_set_dma_des_int_mask`
- `decomp_all_tm.c:35212` `pon_tm_set_fifo_int_mask`
- `decomp_all_tm.c:35310` `tmOnuGlbRegValidation` (struct layout decoder)
- `decomp_all_tm.c:35337` `tmOnuRegRead`
- `decomp_all_tm.c:35356` `tmOnuRegWrite`
- `decomp_all_tm.c:42448` `tm_pon_tm_reg_initial`
- `decomp_all_tm.c:47097` `tm_pon_tm_initial`
- `decomp_all_tm.c:47123` `tm_initial`
- `decomp_all_tm.c:69411` `tm_initModule`
- `decomp_all_zx_ponreg.c:1`,:10 `fpga_read_reg`/`fpga_write_reg`
- `decomp_all_plat_zxylzb_9128S.c:6311` `zx_pon_tm_int` (handler)
- `decomp_all_plat_zxylzb_9128S.c:6338` `pon_tm_int_init` (TM[0x104] = 0xffffffff)
- `decomp_all_plat_zxylzb_9128S.c:6360` `pon_tm_check_tx_done_nolock` (TX_DONE clearing path)
- `decomp_all_plat_zxylzb_9128S.c:6478..` `pon_tm_net_stop/open/int/poll` (mask lifecycle)
- `decomp_all_plat_zxylzb_9128S.c:7058` `tm_pon_tm_init` (sets TM[0x128]/TM[0x130])
- `regs/stock_eth_2mib.txt` (live phys dump @ 0x9234012c, 0x92340104, etc.)
- Raw bytes: `objdump -s -j .data ext/rootfs/kmodule/tm.ko` → table @ offset 0x76ec
