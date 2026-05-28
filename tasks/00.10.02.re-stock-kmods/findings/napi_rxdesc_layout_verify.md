# NAPI RX-descriptor layout — verification of mainline scan-forward vs stock

**Target**: validate that mainline's "scan forward for valid desc" hack
in `zx_tm_napi_poll` matches what stock `pon_tm_net_poll` does.

**Source of truth**: `decomp_all_plat_zxylzb_9128S.c` lines 8558-8866
(stock `pon_tm_net_poll @ 0001c9f0`).

**TL;DR**: the scan-forward approach is **wrong vs stock**, and it
likely works by accident only because mainline reads the wrong ring
geometry. Stock uses **unconditional advance-by-1 (mod 1024)** on a SW
cursor it owns, never consults a HW write pointer, and operates on
**two separate RX rings per queue** (UP and DN) that mainline has
collapsed into one.

---

## 1. Stock per-queue state — what `iVar13` actually points at

Per `pon_tm_queue_init @ 0001a15c` (plat:6914-6944) and the references
in `pon_tm_net_poll`, each queue has a context struct with these fields
relevant to RX:

| Offset (from iVar13) | Field | Meaning |
|---:|---|---|
| `+0x38` | `dn_ring_base` | RX-DN descriptor ring base (kernel VA) |
| `+0x3c` | `dn_cursor` | SW index into DN ring (0..1023 with `&0x3ff` wrap) |
| `+0x78` | `up_ring_base` | RX-UP descriptor ring base (kernel VA) |
| `+0x7c` | `up_cursor` | SW index into UP ring (0..1023 with `&0x3ff` wrap) |

`iVar13` walks **down by 8 bytes per queue** as `local_58` (queue id)
decrements from 7 to 0, so the stride between queues is 8 bytes and
the +0x38/+0x3c/+0x78/+0x7c offsets are absolute into a 256-byte
array shared across all 8 queues.

Initialization at `pon_tm_queue_init` plat:6928-6936:
```c
do {
    iVar1 = iVar2 + 0x20000;     // 128 KiB stride
    puVar3[-1] = iVar2;          // +0x78 of next-iter = up_base
    iVar2 = iVar2 + 0x4000;      // 16 KiB stride to next up_base
    puVar3[0xf] = iVar1;         // +0x3c = dn_base
    *puVar3  = 0;                // up_cursor = 0
    puVar3[0x10] = 0;            // dn_cursor = 0
    puVar3 = puVar3 + 2;
} while (iVar2 != iVar4 + -0x3fac0000);
```

The two rings per queue are at:
- UP base: `iVar4 - 0x3fae0000 + q*0x4000` (16 KiB ring = 1024 × 16 B descs)
- DN base: UP base + 0x20000 (128 KiB later in BPPE region)

Each ring is **1024 entries × 16 B = 16 KiB**.

---

## 2. The HW status reg TM[0x10100 + q*4] — bit-level decode

Line 8612: `uVar6 = *(uint *)(tm_base + (local_58 + 0x4040) * 4)`
= `TM[0x10100 + q*4]`.

| Bits | Meaning | Used as |
|---:|---|---|
| `[15:0]`  | **DN-ring pending count** | cap for DN read loop (line 8735) |
| `[31:16]` | **UP-ring pending count** | cap for UP read loop (line 8620) |

```c
iVar9 = min(budget/2, uVar6 >> 0x10);   /* UP-ring frames to read */
uVar7 = min(budget/2, uVar6 & 0xffff);  /* DN-ring frames to read */
```

**HIGH16 is NOT a HW write pointer.** It is the **pending-frame count
on the UP ring**. The decrement happens through `soft_release_rx_desc`
which writes to `TM[0x4068]` (an indirect "release-N-frames" command
register at plat:7221). Read-clear is not used; HW debits when SW
ack-N writes are processed.

This refutes the earlier hypothesis ("HIGH16 = HW write_ptr"). The
empirical `0xff96000e` observation in iter30 means: 14 frames pending
on DN (LOW16) and 0xff96 frames pending on UP — which is nonsensical
(65430 frames). The 0xff96 either means (a) wrap arithmetic ate
something on the stock semantic, (b) the UP ring is mis-initialized
in mainline so the HW thinks it has 65k pending UP descs, or (c) the
register encoding flipped UP/DN on mainline. Mainline currently only
reads LOW16 — which works because LOW16 = DN-ring count and that is
where switched LAN frames actually arrive.

---

## 3. Stock NAPI inner loop — pure advance-by-1

UP-ring loop (lines 8636-8723), simplified:
```c
iVar2 = 0; local_4c = 0;
do {
    while (true) {
        desc = up_base + up_cursor * 0x10;
        up_cursor = (up_cursor + 1) & 0x3ff;   /* unconditional advance */
        bp_num = (desc[7] >> 1) | (desc[8] << 7);
        second_buf = desc[6] & 1;
        if (bp_num >= bp_max_number[jumbo_bit]) break;   /* invalid BP -> exit */
        ... process desc ...
        if (++iVar2 == iVar9) goto done_up;
    }
    /* fell out because invalid bp_num */
    rx_errors++;
    printk("rxq %d,invalid bp %u\n", q, bp_num);
    dump_desc(desc);
    iVar2++;
} while (iVar2 != iVar9);
done_up:
if (iVar9 - local_4c) soft_release_rx_desc(1, q, 0, iVar9 - local_4c);
if (local_4c)         soft_release_rx_desc(1, q, 1, local_4c);
```

Key facts:
1. **Cursor advances by exactly 1 every iteration**, valid desc or not.
2. **Invalid BP is logged and counted, but the cursor still advanced** —
   stock does not search for the "next valid" entry.
3. **The cap (`iVar9`) is HIGH16 of TM[0x10100+q*4]** — i.e. stock
   trusts the HW pending counter to tell it exactly how many entries
   to drain from the cursor.
4. **Cache invalidation pre-loads `iVar9 * 16` bytes from the cursor**
   (with wrap), proving the read is **contiguous from cursor onward**.
5. DN-ring loop (lines 8746-8839) is **structurally identical** with
   `dn_cursor` and the LOW16 cap.

The cursor / pending invariant: HW writes RX descriptors **strictly
sequentially** starting at the position SW last left it. There is no
HW write pointer to query because the stock semantic is "HW maintains
the counter, SW maintains the cursor, the two are kept consistent by
the soft_release ack".

---

## 4. Why mainline's scan-forward "works empirically"

Mainline observation: queue 5 has frame at idx 0, then "subsequent at
idx 12+". If stock semantics were preserved, that means **idx 1..11 are
ALSO valid frames** that stock would have processed and that mainline
is skipping because their `len` field reads as 0/invalid.

Two equally plausible explanations:

### Hypothesis A — UP ring sees garbage descs
Mainline does not allocate the UP ring at all (we only have one
`rxdesc_cpu`). Stock writes the UP-ring base to `iVar13 + 0x78` and
DN-ring base to `+0x38`. If HW expects two separate rings 128 KiB
apart and mainline aliases them into one buffer, then half the HW
writes hit one mainline location and half land in DRAM nobody owns.
The "idx 1..11 = zero" pattern is consistent with: HW writing UP
descs into a buffer that doesn't exist (drops on the floor), DN
descs into bytes 0,12,13,... of the merged ring (stride consistent
with how HW packs them).

### Hypothesis B — mainline parses len from wrong byte
Stock at line 8667: `uVar7 = (uint)(*(ushort *)(iVar4 + 0xc) >> 2);`
i.e. `len = (u16)desc[12..13] >> 2`. Mainline matches:
`len = le16_to_cpu(*(__le16 *)(desc + 12)) >> 2;` — so this is fine.

A is the strong hypothesis: stock has **two** rings per queue;
mainline has one. The scan-forward "fix" is finding the next desc
HW actually wrote because the rings overlap in memory and the misses
look like zeros.

---

## 5. Answers to the four questions

### Q1 — Does stock use advance-by-1 or follow HW write_ptr?
**Pure advance-by-1 with `& 0x3ff` wrap on a SW cursor.** No HW write
pointer is consulted. The HW pending-count is used as a budget cap,
not as a position oracle.

### Q2 — What is HIGH16 of TM[0x10100+q*4]?
**Pending-frame count on the UP (jumbo/upstream) RX ring.** LOW16 is
the same count for the DN (downstream/normal LAN) ring. Not a write
pointer, not a lifetime counter, not byte count. Two stacked
16-bit pending-frame counters, one per direction.

### Q3 — Is mainline's scan-forward safe?
**Functionally yes today** (LAN frames hit DN ring whose count is in
LOW16, and the scan happens to land on the next valid desc). **But
architecturally wrong** — under load it will:
- Skip past stale-zero entries that might legitimately be "later
  arrivals not yet visible to CPU" if cache invalidation hasn't run
  yet on them (race window).
- Process the same desc twice if HW wraps and overwrites a slot the
  scan considered stale-zero.
- Cost up to 1024 iterations per NAPI poll on idle queues — measurable
  perf hit under load.
- Hide the real bug, which is the missing UP ring.

### Q4 — How does stock decide the per-queue starting index?
The SW cursor at `iVar13 + 0x3c` (DN) or `+0x7c` (UP) is **persistent
across NAPI calls**. It is initialized to 0 in `pon_tm_queue_init`
and only ever updated by the inline `cursor = (cursor + 1) & 0x3ff`
in `pon_tm_net_poll` itself. No resync via HW reg. No "where did HW
leave off" query. The contract is: HW always writes at the position
SW left + N (where N = pending count returned in TM[0x10100+q*4]).

---

## 6. Recommended mainline correction

Two-stage fix, smallest first:

1. **Drop the scan-forward.** Reinstate strict advance-by-1 per stock.
   Cap reads at `pending` (LOW16 today, eventually also HIGH16 for
   UP). If a desc has `bp_num >= bp_max_number`, log "invalid bp",
   advance cursor, continue — don't search.
2. **Allocate two RX rings per queue.** Add `rxdesc_dn_cpu` + 8 SW
   cursors for DN, `rxdesc_up_cpu` + 8 cursors for UP. Program the
   UP base into `iVar13+0x78` equivalent (which today is implicit —
   we need to find the corresponding TM register; likely TM[0x10050]
   is one of them given the iter14 finding). DN base goes 128 KiB
   later. Read each ring with its own cursor + cap.

If #1 alone fails (the scan was masking real desc misses), #2 is
mandatory. If #1 succeeds and ping RX delivers all 14 of 14, then
the dual-ring is a perf/correctness latent issue but not blocking.

---

## 7. Confidence

**High** on:
- Stock uses advance-by-1, not write_ptr (lines 8639-8643 are
  unambiguous).
- HIGH16/LOW16 are per-direction pending counts (lines 8620, 8735).
- Stock has two RX rings per queue with 128 KiB separation
  (pon_tm_queue_init body).
- Scan-forward is architecturally wrong vs stock.

**Medium** on:
- The empirical reason mainline's hack works today (Hypothesis A vs
  B above — I lean A but lack direct evidence).
- The exact register that programs the UP ring base in HW (likely
  TM[0x10050]; the DN base might be TM[0x10060] given the
  `pdt_mem + 0x405e0000` / `0x405f0000` separation in
  `pon_tm_dma_init` plat:6294).

**Low** on:
- Whether allocating the second ring is sufficient or if HW needs
  additional config (e.g. enabling UP DMA, programming desc count
  to 1024 explicitly).

---

## 8. Cross-references

- `decomp_all_plat_zxylzb_9128S.c`:
  - `pon_tm_queue_init @ 0001a15c` (lines 6914-6944) — ring allocation
  - `pon_tm_dma_init @ 0001927c` (lines 6277-6301) — TM[0x10050]/[0x10060]
  - `pon_tm_net_poll @ 0001c9f0` (lines 8558-8866) — the NAPI itself
  - `soft_release_rx_desc @ 0001a8e8` (lines 7202-7232) — ACK protocol
- `tm_100_status_bit_decode.md` — TM[0x100] aggregate bit semantics
- `iter30_first_rx_delivered_2026-05-28.md` — empirical state when this
  hack went in
- Mainline `zx-eth-main.c:2610-2777` — current scan-forward NAPI
