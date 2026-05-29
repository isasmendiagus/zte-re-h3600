# BMU (Buffer Management Unit) — deep RE of stock + mainline gap

**Source binaries**: stock `plat-zxylzb_9128S.ko` (decomp:5694-6123),
`tm.ko` (BMU diag at fpga_read_reg 0xd203x).
**Source captures**:
- Live stock TM register dump @ `findings/regs/stock_eth_2mib.txt`
  (offsets `92348000..923480dc` and `923400e8..923400fc`).
- Stock boot printks @ `tasks/00.01.eth-driver/captures/boot_init_2026-05-22.log`
  lines 6–28 (`pon init` / pool sizes / lan_up).
- Stock replay table @ `linux-v6.6/drivers/net/ethernet/zte/zx_stock_table.h`
  rows /*16347*/–/*16458*/ (multi-instance snapshot).
- Mainline driver @ `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`
  `zx_tm_alloc_pools` (1650), `zx_tm_bmu_init` (1718), `zx_tm_bmu_enable`
  (1758), `zx_bmu_alloc_bp` (2873), `zx_bmu_free_bp` (2913).

---

## 1. Block-level overview

The BMU is a fixed-function HW allocator/freer of **Buffer Pointers**
(BPs) used by both the switch fabric and the CPU TM path. It maintains
**two pools** (normal and jumbo), each with three live entities:

| Entity | What it is | Where |
|--------|------------|-------|
| **BP buffer** | The actual `BP_SIZE`-byte chunk that holds packet data | DDR @ `TM[0xF4]` (normal) / `TM[0xF8]` (jumbo), packed `BP_SIZE * POOL` bytes |
| **BPPE table** | An array of `u16` indices (big-endian on the wire) that names which BP slots are currently free; HW pulls one entry per alloc | DDR @ `TM[0xE8]` (normal) / `TM[0xEC]` (jumbo). Stock allocates a fixed **128 KiB** ring at `0x4e700000`, of which only `POOL * 2` bytes hold valid indices. |
| **Pool config** | Geometry constants (sizes, cursor) that tell HW how to interpret the two DDR regions | `TM[0xFC]` (sizes), `TM[0x8048/0x804c]` (BPPE producer cursor), `TM[0x8058/0x805c]` (bucket-mask) |

HW flow:
1. CPU writes `POOL` `u16` indices `bswap16(0)…bswap16(POOL-1)` into BPPE.
2. CPU writes `TM[0x8048] = POOL << 16` — this is the **producer cursor**
   (high16 = write_ptr, low16 = read_ptr). High16 = POOL means "all N
   indices are valid; HW may consume from `read_ptr` forward."
3. CPU sets `TM[0x8000] = 1` (BMU enable). HW now serves alloc/free.
4. **alloc**: SW pulses `TM[0x8014] |= 1`. HW reads
   `bppe[low16(TM[0x8048])]`, byte-swaps it to get a `bp_idx` in
   `[0, POOL)`, increments low16, and writes
   `0x80000000 | bp_idx` into `TM[0x800c]`. The bp_idx names the slot
   inside `TM[0xF4] + bp_idx * BP_SIZE`.
5. **free**: SW writes `bp_idx | (jumbo_flag << 15)` into `TM[0x8010]`.
   HW pushes the freed idx back into BPPE at a producer-side cursor
   (the high16 of `TM[0x8048]` advances modulo POOL).

The BPPE ring acts as a **producer (HW frees here) / consumer (HW
allocs from here)** queue, with the CPU pre-seeding all indices at init.

### Stock per-unit pool geometry (read from boot log + register snapshot)

```
BPPE_POOL_SIZE         = 0x2000 = 8192       u32_BPPE_POOL_SIZE
NORMAL_BP_BUFFER_SIZE  = 0x1200000 = 18 MiB  ( = 8192 * 0x900 )
u32_BP_SIZE            = 0x900 = 2304
JUMBO_BPPE_POOL_SIZE   = 0x66   = 102        u32_JUMBO_BPPE_POOL_SIZE
JUMBO_BP_SIZE          = 0x2800 = 10240
BP_BUFFER_SIZE         = 0x12ff000 ≈ 19.93 MiB

Carved-DDR pool layout (stock physical addresses):
  0x4e700000  ZX_VA_BPPE_BASE        BPPE (normal), 128 KiB region
  0x4e710000  jumbo BPPE base        +64 KiB into BPPE region
  0x4ec20000  ZX_BP_BUFFER_BASE      BP buffers (normal), 18 MiB
  0x4fe20000  Jumbo BP buffer base   ( = 4ec20000 + 0x1200000 )
  0x4ff1f000  ZX_DESC_BASE           = 4ec20000 + 0x12ff000 (after BP)
```

### Mainline per-unit pool geometry

```
TM_BPPE_POOL_SIZE      = 1024  (8x smaller than stock)
TM_BP_SIZE             = 2304  (same)
TM_JUMBO_BPPE_POOL_SIZE = 0    (no jumbo)
TM_JUMBO_BP_SIZE       = 10240 (config only; pool empty)

Memory:
  bppe_dma  = dma_alloc_coherent(POOL * 2)           // 2 KiB only
  bp_dma    = dma_alloc_coherent(POOL * BP_SIZE)     // 2.25 MiB
  No dedicated jumbo region; same bppe_dma re-used for jumbo base reg.
```

**Live mainline numbers** (from task description):
- `TM[0xE8] = 0x4c047000` (4 KiB aligned, NOT 64 KiB aligned)
- `TM[0xF4] = 0x4c100000`
- `TM[0xFC] = 0x28000900`

---

## 2. Register map TM[0x8000..0x80dc] + TM[0xe8..0xfc]

R = read, W = write, RW = read-write, W1C = write-1-to-clear, RO =
read-only HW status. Names from `dump_bmu_reg` (plat:6103) where stock
printks them.

### Base addresses (TM[0xE8..0xFC])

| Off | Name | Stock live (h3600) | Semantics |
|-----|------|--------------------|-----------|
| 0xE8 | BPPE_BASE | 0x4e700000 | **RW**. PA of normal BPPE table. Stock 64 KiB-aligned (mainline 4 KiB-aligned — see ROOT_CAUSE_2). HW reads via `bppe[low16(TM[0x8048])]`. |
| 0xEC | JUMBO_BPPE_BASE | 0x4e710000 | **RW**. PA of jumbo BPPE table. Stock places at +64 KiB. |
| 0xF0 | ZX_DESC_BASE (TM-RX desc) | 0x4ff1f000 | **RW**. Per-instance RX desc ring base. (Set by `zx_tm_post_bmu`.) |
| 0xF4 | BP_BUFFER_BASE | 0x4ec20000 | **RW**. PA of normal BP backing store (POOL × BP_SIZE bytes). |
| 0xF8 | JUMBO_BP_BUFFER_BASE | 0x4fe20000 | **RW**. PA of jumbo BP backing store. |
| 0xFC | BP_SIZE | 0x28000900 | **RW**. `low16 = BP_SIZE` (=0x900=2304), `high16 = JUMBO_BP_SIZE` (=0x2800=10240). |

### BMU control + status (TM[0x8000..0x80DC])

| Off | Name (dump_bmu_reg) | Stock live | Stock_table replay | Semantics |
|-----|---------------------|------------|--------------------|-----------|
| 0x8000 | bmu cfg | 0x00000001 | (not in replay) | **RW**. `bit0 = ENABLE`. Stock first writes 0 (in pon_tm_bmu_init), then 1 (in pon_tm_bmu_enable). Other bits unused. |
| 0x8004 | bpp cfg | 0x0104C040 | 0x0104C040 (@188404) | **RW**. `bppCtrl1`. Constant per H3600 firmware. Not bit-decoded (likely DMA-burst / threshold config). |
| 0x8008 | bpp cfg 2 | 0x0104C040 | 0x0104C040 | **RW**. `bppCtrl2`. Same as 0x8004. |
| 0x800C | sw_alloc_bp | 0x00000000 | n/a | **RO**. Alloc result. `bit31=valid`, `bits[15:0]=bp_idx`. Cleared by alloc completion or by HW state. |
| 0x8010 | sw_free_bp | 0x00000013 | 0x00000025 | **W**. Free request. `bits[14:0]=bp_idx`, `bit15=jumbo_flag`. Reading shows last-written value. |
| 0x8014 | sw_alloc_cfg | 0x00000000 | n/a | **RW**. `bit0=alloc_kick`, `bit1=jumbo_select` (per `pon_tm_bmu_alloc_jumbo_bp` which writes 3 = both bits). Poll until `bits[1:0]==0`. |
| 0x8028 | bpp_b ctrl?  | n/a | 0x00010004 | **RW**. Stock-replay constant; not touched by `pon_tm_bmu_init`. Likely BPPE-prefetch threshold. |
| 0x802C | ditto jumbo | n/a | 0x00010004 | **RW**. Jumbo counterpart. |
| 0x8030 | port_map(?) | n/a | 0x01010101 | **RW**. 4 bytes packed; probably per-MAC BPP routing. |
| 0x8034 | port_map(?) | n/a | 0x00000101 | **RW**. |
| 0x8040 | bppi ptr | 0x00510002 | 0x00720023 | **RO** (mostly). `low16 = bppi_read_ptr`, `high16 = bppi_write_ptr`. **BPPI** = "buffers pending into pool" ring — HW frees here when descriptors complete. NOT BPPE. |
| 0x8044 | bppi cfg | 0x00500001 | 0x00500001 | **RW**. |
| **0x8048** | **bppe ptr** | **0x00000050** | n/a | **RW**. `low16 = read_ptr`, `high16 = write_ptr`. Init: write `POOL<<16` to advertise N valid entries. HW increments low16 on alloc, high16 on free (refill). Stock live shows low16=0x50 (HW consumed 80 entries since init), high16=0 meaning the producer wrapped (80 entries since last full cycle). Crucial register: **mainline writes 0x04000000 but reads back 0 → see ROOT_CAUSE_1**. |
| 0x804C | jumbo bppe ptr | 0x00660050 | n/a | **RW**. Jumbo counterpart. |
| 0x8058 | pool size | 0x00000100 | n/a | **RW**. Bucket count. Stock formula `(POOL>>5)-1` yields 0xFF for POOL=8192, but **live shows 0x100**. Either decomp formula is `>>5` (no -1) or HW post-increments. Mainline writes 0x1F (formula) and reads back 0x20 — supports the "HW adds +1" hypothesis OR the decomp's `- 1` is wrong (more likely: decomp imm). For POOL=8192 stock wrote 256 directly, NOT 255. **See ROOT_CAUSE_3.** |
| 0x805C | jumbo pool size | 0x00000003 | n/a | **RW**. Jumbo counterpart. |
| 0x8080 | bppe bpcnt | 0x00001fb0 | 0x00001fb0 | **RO**. Number of free BPs currently in normal BPPE ring (= 0x1fb0 = 8112 of 8192 stock live; ~80 in-flight). |
| 0x8084 | jumbo bpcnt | 0x00000016 | 0x00000016 | **RO**. |
| 0x8088 | bppi bpcnt | 0x0000004f | 0x0000004f | **RO**. Buffers waiting in BPPI ring. |
| 0x808C | jumbo bppi bpcnt | 0x0000004f | 0x0000004f | **RO**. |
| 0x8090 | alloc bpcnt | 0x00000b02 | 0x00000a23 | **RO** (HW counter). Lifetime BP-alloc count. |
| 0x8094 | jumbo alloc cnt | 0x00000001 | 0x00000001 | **RO**. |
| 0x8098 | rls bpcnt | 0x00000b01 | 0x00000a22 | **RO**. Lifetime BP-free count. (Diff alloc - rls = currently allocated.) |
| 0x809C | jumbo rls cnt | 0x00000000 | (n/a) | **RO**. |
| 0x80A0 | bp initsat | 0x00000000 | (n/a) | **R?**. `dump_bmu_reg` prints it as "bp initsat" (init-saturate?). HW status; not written by stock. **Mainline never reads this**; if HW uses it as a "init valid" gate, this could matter. |
| 0x80A4 | (unknown) | 0x00000000 | (n/a) | |
| 0x80A8 | (unknown) | 0x0000054d | 0x000004f4 | **RW** (replay). Likely watermark. |
| 0x80B0 | (unknown) | 0x000005b5 | 0x0000052f | **RW**. |
| 0x80B4 | (unknown) | 0x00000001 | 0x00000001 | **RW**. |
| 0x80B8 | (unknown) | 0x000005b4 | 0x0000052e | **RW**. |
| 0x80C8 | (unknown) | 0x00000200 | 0x00000200 | **RW**. Constant 0x200. |
| 0x80CC | (unknown) | 0x04022000 | 0x04022000 | **RW**. Constant. |
| 0x80D0 | (unknown) | 0x07f00000 | 0x07f00000 | **RW**. Constant — 8-bit field at bits[28:20] = 0x7f. Looks like an enable mask. |
| 0x80D8 | (unknown) | 0x00004000 | 0x00004000 | **RW**. Constant. |
| 0x80DC | bp stat | 0x40000111 | 0x40000111 | **RW**. Multi-field status. `bits[5:0]=` free-credit (read+masked by free path: `(tm[0x80dc] << 23) >> 26` extracts bits[8:3]). `bit30` set in live = some "ready" indicator. **Mainline never writes this**; stock-table-replay does. |

### What the stock_table.h replay programs (rows 16347..16370 — instance 0)

This is the **runtime snapshot** captured from a booted device; it
contains both "config" regs (constant) and "live counter" regs (which
change at runtime). Replay setting them as boot-time constants is OK
for the constant ones and risk-free for the counters (HW resets them
or rolls forward anyway):

- `0x188010 = 0x25` — TM[0x8010] last free (data; harmless)
- `0x188028 = 0x10004` — config: BPPE prefetch (?)
- `0x18802c = 0x10004` — jumbo counterpart
- `0x188030 = 0x01010101` — config: per-port BPP map (?)
- `0x188034 = 0x00000101` — config
- `0x188040 = 0x00720023` — BPPI cursor snapshot (TM[0x8040])
- `0x188044 = 0x00500001` — BPPI cfg
- `0x188080 = 0x00001fb0` — bppe bpcnt snapshot (RO normally — write-through?)
- `0x188084 = 0x00000016` — jumbo cnt
- `0x188088 = 0x0000004f` / `0x18808c = 0x0000004f` — bppi cnt
- `0x188090 = 0x00000a23` — alloc lifetime cnt (snapshot)
- `0x188094 = 0x1` — jumbo alloc
- `0x188098 = 0x00000a22` — rls cnt
- `0x1880a8 / 0x1880b0 / 0x1880b4 / 0x1880b8` — watermarks
- `0x1880c8 = 0x200` (constant)
- `0x1880cc = 0x04022000` (constant)
- `0x1880d0 = 0x07f00000` (constant)
- `0x1880d8 = 0x00004000` (constant)
- `0x1880dc = 0x40000111` (bp stat — constant on H3600)

**Crucially absent from the replay**: `0x188000, 0x188004, 0x188008,
0x188014, 0x188048, 0x18804C, 0x188058, 0x18805C`. The mainline
`zx_tm_bmu_init` is the only path that programs these. Stock has these
covered in `pon_tm_bmu_init` (decomp:5694).

The replay repeats for instances 0..4 at strides 0x400 — there are
**five BMU instances** at TM[0x8000], +0x400, +0x800, +0xC00, +0x1000.
Mainline only programs **instance 0** in `zx_tm_bmu_init` (no loop).
`zx_tm_pre_init` loops over instances 0..3 for `TM[0x000/004/104/124/12C/134]`,
and `zx_tm_post_bmu` loops over `TM[+0xF0/+0xFC]` instances 0..3.
**See ROOT_CAUSE_2** — the BMU itself is not programmed across instances.

---

## 3. Complete alloc protocol (stock `pon_tm_bmu_alloc_bp`)

Per `plat:5772`, the full procedure is:

```
spin_lock_bh(&alloc_lock);
if (bmu_alloc_timeout != 0) {
    // last call timed out; check whether HW finally finished
    if ((tm[0x8014] & 1) != 0) goto fail;
    result = tm[0x800c];
    bmu_alloc_timeout = 0;
    if ((int)result < 0) {
        // bit31 set => success even from prior alloc
        spin_unlock_bh(&alloc_lock);
        bmu_status.timeout_recovered++;
        return result & 0xffff;
    }
    // fall through to retry
}
tm[0x8014] |= 1;             // kick
for (i = 200; i > 0; i--) {
    status = tm[0x8014] & 3;  // bits[1:0]: 1=busy, 0=done
    if (status == 0) {
        result = tm[0x800c];
        if ((int)result < 0) {
            spin_unlock_bh(&alloc_lock);
            bmu_status.sw_alloc_cnt++;
            return result & 0xffff;
        }
        break;  // done but bit31 clear == pool empty
    }
}
bmu_alloc_timeout = 1;
spin_unlock_bh(&alloc_lock);
bmu_status.alloc_bp_fail++;
return 0xffffffff;
```

Mainline `zx_bmu_alloc_bp` (line 2873) is a strict subset — no
timeout-recovery sticky flag, no spin lock (relies on caller's
tx_lock). For diagnostic purposes the simplification is fine.

**Implicit prerequisites** (not in the function itself):
- `TM[0x8000].bit0 == 1` (BMU enabled).
- BPPE physical addr in `TM[0xE8]` points at writable, cache-coherent
  DDR; HW reads `bppe[low16(TM[0x8048])]` to learn the bp_idx.
- `TM[0xFC].low16 = BP_SIZE` (so HW knows stride).
- BPPE table must be **populated AND visible to HW** (= cache-flushed if
  the region isn't dma_alloc_coherent).
- `TM[0x8048].high16` must be a positive number indicating "N entries
  pre-loaded by SW; HW may now consume them."

---

## 4. Complete free protocol (stock `pp_bmu_free_bp`)

Per `plat:5823`:

```
spin_lock_bh(&free_lock);
for (i = 200; i > 0; i--) {
    if (allow_free_cnt > 0) {
        allow_free_cnt--;
        tm[0x8010] = bp_idx | (jumbo_flag << 15);
        spin_unlock_bh(&free_lock);
        return 0;
    }
    // refill credit from HW
    allow_free_cnt = (int)(tm[0x80dc] << 23) >> 26;  // bits [8:3]
}
spin_unlock_bh(&free_lock);
return -1;
```

The HW exposes a 6-bit "available free slots" credit in TM[0x80DC]
bits[8:3]. SW caches it as `allow_free_cnt`, decrementing per free,
refilling from the HW reg when empty.

Mainline `zx_bmu_free_bp` (line 2913) replicates this with the
correct bit-extraction (`(tm[0x80dc] >> 3) & 0x3f`).

---

## 5. The diff: what stock does that mainline doesn't

| # | Topic | Stock | Mainline | Severity |
|---|-------|-------|----------|----------|
| 1 | **POOL_SIZE** | 0x2000 (8192) | 0x400 (1024) | 🟡 functional ratio (8x smaller pool) but no HW correctness issue — see Q2 below |
| 2 | **BPPE region size** | 0x20000 (128 KiB) for both pools | `POOL_SIZE * 2` = 2 KiB | 🔴 Possibly significant — stock allocates 64 KiB per pool; HW may need a region this large for prefetch / wrap behavior |
| 3 | **BPPE alignment** | 64 KiB (0x4e700000) | 4 KiB (e.g. 0x4c047000) | 🟡 HW may require ≥64 KiB alignment; testable |
| 4 | **dma_cache_maint(bppe, 0x20000)** | flushes 128 KiB after BPPE write | uses dma_alloc_coherent (no-op flush) | 🟢 mainline path is correct |
| 5 | **BPPE init pattern** | `for i in 0..POOL-1: bppe[i] = bswap16(i)` | identical (`cpu_to_be16(i)`) | 🟢 verified equivalent |
| 6 | **TM[0xEC]** (jumbo BPPE base) | `bppe_phys + 0x10000` (distinct buffer) | reuses normal `bppe_dma` | 🟡 we set jumbo_pool=0, so HW shouldn't fetch from it — but if HW probes the region during init, sharing the address could corrupt normal BPPE |
| 7 | **TM[0xF8]** (jumbo BP buf) | `bp_phys + 0x1200000` (distinct) | reuses normal `bp_dma` | 🟡 same risk as #6 |
| 8 | **TM[0x8058]** (BUCKETS_M1) | live = 0x100, stock_table doesn't replay it; pon_tm_bmu_init writes `(POOL>>5)-1` = 0xFF for 8192 | writes 0x1F for POOL=1024 | 🔴 stock LIVE value doesn't match formula by +1 — see Q3 |
| 9 | **TM[0x804C]** (JUMBO_POOL_SIZE writeback) | `JUMBO_POOL<<16` = 0x660000 then live = 0x660050 (HW consumed) | writes 0 | 🟢 acceptable if jumbo unused |
| 10 | **TM[0x80a8/b0/b4/b8/c8/cc/d0/d8/dc]** (constants from stock_table replay) | replay covers these | mainline does NOT write the BMU-side constants 0x80C8/0xCC/0xD0/0xD8/0xDC (replay table only includes them per-instance but mainline runs replay AFTER bmu_enable) | 🟡 need to verify replay touches them in our current code path |
| 11 | **5 BMU instances (TM[0x8000/0x8400/0x8800/0x8C00/0x9000])** | stock_table replay covers each instance with config + counters | mainline `zx_tm_bmu_init` only writes **instance 0** | 🔴 **likely the smoking gun** — TM ASIC may load BPPE from instance N's regs based on egress port |
| 12 | **TM[0xc008] = 0** | written once after BMU enable | written (✓) | 🟢 |
| 13 | **bmu_alloc_timeout sticky flag** | yes; re-reads after timeout | no | 🟢 cosmetic / robustness |
| 14 | **Order of writes in pon_tm_bmu_init** | (cache flush) → 0x8000=0 → ctrls → 0x8058 → bases → 0xFC → 0x8048 | bases → 0xFC → 0x8000=0 → ctrls → 0x8048 → 0x8058 | 🟡 different but probably tolerable (BMU is disabled while configuring) |

### Specific check for Q4 (stock_table BMU regs)

Stock_table writes at `0x188xxx` (TM[0x8xxx]) for instance 0:
- 0x188010 / 0x188028 / 0x18802c / 0x188030 / 0x188034 / 0x188040 /
  0x188044 / 0x188080..98 / 0x1880a8/b0/b4/b8 / 0x1880c8..dc.

`zx_stock_apply_block(eth, "TM", ...)` runs at probe `start_kernel`
sequence before `zx_eth_init_chip_tm`. **It writes these constants
BEFORE mainline's `zx_tm_bmu_init` overwrites 0x8000/4/8/48/58 — so
the watermarks/constants ARE present.** BUT the replay runs while
BMU is in HW power-on default state (mostly zero); writes go through
unchecked. After mainline's `zx_tm_bmu_init` writes `0x8000=1` to
enable, the live regs at 0x80C8/CC/D0/D8/DC should still contain the
replay values. Verify by reading them post-init.

### Specific check for Q5 (warm-up / preload sequence)

Stock between `pon_tm_bmu_enable` and the first `pon_tm_bmu_alloc_bp`:
- `TM[0xc008] = 0` (immediately after enable)
- `pon_tm_net_init()` — creates "sw"/"pon" netdevs, NAPI register, queue
  init, **starts pon_tm_timer (1-jiffy reclaim)**
- `pon_tm_int_init()` — `TM[0x104] = 0xffffffff`, then request_threaded_irq

**No BPPE preload kick or warm-up write was identified between
enable and first alloc.** The HW is expected to read BPPE on-demand
when SW issues alloc_kick (`TM[0x8014] |= 1`).

However, **the periodic `pon_tm_timer`** does run shortly after enable
and calls into the TX reclaim path, which on its first invocation
issues frees back to TM[0x8010]. These frees are what populates the
"allow_free_cnt" credit pipeline in HW. *Not* a BPPE preload, but
indirectly the timer keeps the free path warm. Mainline now has a
timer per commit `80f610eda` — good.

---

## 6. Top 3 candidate root causes (ranked by likelihood)

### Candidate 1 (🔴 highest likelihood): **Mainline programs only BMU instance 0; HW expects all 5 instances configured**

Evidence:
- Stock register dump shows ALL FIVE instances at `0x92348000`,
  `0x92348400`, `0x92348800`, `0x92348C00`, `0x92349000` filled with
  identical config (including `0x8000=1`, `0x8004=0x104c040`, etc.).
- Stock replay table mirrors per-instance writes at strides of `0x400`
  for `0x188010`..`0x1880dc` × 5 instances (rows 16347–16458).
- Mainline `zx_tm_pre_init` AND `zx_tm_post_bmu` loop over the 4
  instances explicitly. But `zx_tm_bmu_init` (the function that writes
  TM[0x8000/4/8/48/4c/58/5c]) **does NOT loop**. So instances 1..4
  remain with `TM[0x8000]=0` (BMU disabled), `TM[0x8048]=0` (no producer
  cursor), `TM[0xE8]=0` (no BPPE base).
- If the TM egress fabric routes frames to a per-instance BMU based on
  some classifier output, the "wrong" instance may be servicing alloc
  requests and finding its pool genuinely empty.

**Why TM[0x800c] reads back 0 in mainline alloc**: instance 0 is
configured but the HW alloc engine is querying a different instance
whose BPPE is empty. The alloc completes (bits[1:0]→0) but bit31
stays clear because no entries are pre-loaded in instance N.

**Test**: mirror the BMU init across instances 0..3 (or 0..4) inside
`zx_tm_bmu_init` — write `TM[base + 0x8000/0x8004/0x8008/0x8048/
0x804c/0x8058/0x805c/0x00E8/0x00EC/0x00F4/0x00F8/0x00FC]` for
`base in {0, 0x400, 0x800, 0xC00, 0x1000}`. Each instance gets the
SAME `bppe_dma` / `bp_dma` (all 5 share the one CMA region). Re-test
the alloc path.

### Candidate 2 (🟡 medium likelihood): **TM[0x8048] writes don't latch because instance 0 isn't enabled yet**

Evidence:
- Task notes that mainline writes `TM[0x8048] = 0x04000000` but reads
  back `0`. This is the explicit "smoking gun" described in the prompt.
- HW register write may be gated on `BMU_ENABLE`. Stock writes 0x8048
  in `pon_tm_bmu_init` while `TM[0x8000]=0`. Mainline does the same.
  But mainline's `TM[0xE8] = bppe_dma` (4 KiB-aligned) could be
  rejected by HW alignment-check (HW expects ≥ 64 KiB alignment).
  When base is rejected, all subsequent BPPE-related writes may also
  be silently dropped.
- Alternatively, HW may post-process `0x8048` write: the high16
  becomes the *new* write_ptr only if HW is in a particular state
  (e.g., the per-instance BPPE region must be readable). If `TM[0xE8]`
  points at unmapped memory (which it does for instances 1..4 in
  mainline today), HW may discard 0x8048 writes.

**Test**: After writing `TM[0xE8]=bppe_dma`, re-read it. If non-zero,
the base latched. Then write `TM[0x8048]=0x04000000` and re-read — if
this latches it's a sequencing issue, not alignment. If it doesn't,
try `bppe_dma & ~0xFFFF` (force 64 KiB align by over-allocating).

### Candidate 3 (🟡 lower likelihood): **BPPE region size mismatch — HW prefetches 128 KiB worth**

Evidence:
- Stock's `dma_cache_maint(bppe_va_addr, 0x20000, 1)` flushes 128 KiB,
  but the actual BPPE table is only POOL*2 = 16 KiB even for stock's
  POOL=8192. The extra 112 KiB of zeros must be tolerable to HW
  because stock works — BUT it implies HW does read into the high-
  address region (else why bother flushing it?).
- HW may **prefetch ahead** of the current write_ptr to keep the
  alloc engine's pipeline full. If the prefetch wraps around the
  high16 producer cursor, HW may see "this address has zeros, no
  valid bp_idx, pool empty."
- Mainline's BPPE is only 2 KiB (POOL=1024 × 2 bytes), backed by a
  single dma_alloc_coherent. HW prefetching past the 2 KiB hits
  whatever follows in CMA — likely zeros or another driver's buffer.
  Either way, when HW eventually consumes "past" entry 1023, it sees
  garbage indices ≥ POOL → drops them → pool empty.

**Test**: Increase mainline POOL_SIZE to 8192 (matching stock); allocate
0x20000 bytes for BPPE explicitly (not POOL*2). The 128 KiB region
allocation may fail under default CMA — fall back to dedicated
reserved-mem in DT.

### Lower-ranked candidates (worth mentioning, not in top 3)

- **TM[0x80A0] "bp initsat" gate** — if HW uses this as a "ready"
  status that must be polled before alloc, mainline misses it. But
  stock never polls it either, so HW likely auto-asserts.
- **TM[0x8058] off-by-one (0x100 vs 0xFF)** — could be ROUND_UP vs
  ROUND_DOWN bucket-count. Current mainline writes 0x1F for POOL=1024;
  stock-equivalent would be 0x20 (POOL=1024 → 1024/32 = 32). Already
  caught (see `(POOL>>5) - 1` formula comment in mainline line 1738).
  Try writing 0x20 (= POOL/32 without -1) for parity with stock 0x100
  = 8192/32.

---

## 7. Action items / what to test next

| Step | What | Expected signal |
|------|------|------------------|
| 1 | Replicate `zx_tm_bmu_init` across all 5 instances (loop strides 0x400 over TM[0x8000/4/8/48/4c/58/5c/E8/EC/F4/F8/FC]) | TM[0x800c] returns bit31=1 |
| 2 | Read back `TM[0x8048]` after the write — verify it latches per instance | Should = 0x04000000 in each enabled instance |
| 3 | Force 64 KiB-aligned `bppe_dma` (over-allocate, take aligned slice) | If step 1 didn't fix it, this may |
| 4 | Bump POOL_SIZE to 8192 + bppe region to 128 KiB | If steps 1–3 didn't fix it |
| 5 | Try `TM[0x8058] = POOL>>5` (drop the -1) | Match stock live value 0x100/0x20 |

---

## Cross-references

- Stock decomp: `decomp_all_plat_zxylzb_9128S.c` lines 5694–6123 (BMU
  family), 7062–7087 (`tm_pon_tm_init` orchestrator), 7770–7818
  (`reserve_mem_info`).
- TM/BMU diagnostic via FPGA-indirect: `decomp_all_tm.c` 46708–46725
  (`fpga_read_reg(0xd203x)`).
- Live register snapshot: `findings/regs/stock_eth_2mib.txt` lines
  401409–401478 (TM[0x8000..0x80dc] instance 0).
- Mainline driver:
  - alloc path: `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c:2873`
  - bmu init: ditto:1718
  - per-instance writes (counterexamples): ditto:2141, 2347
- Boot pool sizes: `tasks/00.01.eth-driver/captures/boot_init_2026-05-22.log`
  lines 22–26.
- Stock_table replay (multi-instance BMU): `linux-v6.6/drivers/net/ethernet/zte/zx_stock_table.h`
  rows 16347–16458.
