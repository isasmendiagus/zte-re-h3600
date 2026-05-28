# TX consume engine — why HW won't drain the TX desc ring

**Status**: deep RE complete; one high-confidence fix identified.
**Date**: 2026-05-28.
**Symptom**: mainline driver enqueues TX descs and kicks the ring,
`tm_tx_count` increments, BUT host tcpdump sees ZERO frames. TM[0x10068]
HIGH16 stuck at 7 since boot.

Sources walked:
- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_plat_zxylzb_9128S.c`
  lines 6232–6911 (full TX family).
- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_tm.c` lines
  35962–35988 (`tm_set_p2pmode` / `tm_set_pp_wan_cfg`).
- `tasks/00.10.02.re-stock-kmods/findings/tx_path_stock_decomp.md`
  (prior pass; this doc adds the consume-engine deltas).
- `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c` lines 3077–3251
  (`zx_sw_xmit`).

---

## Q1 — Stock TX function byte-by-byte

### `pon_tm_net_tx` (plat:6721) — the entry point

Three branches based on `*(int*)(param_2 + 0x4c8)`, which is set by
`pon_tm_net_register(param_1, name)` at line 6398:

- `param_1 = 0` → "sw" netdev → `+0x4c8 = 0` → **UP path** (`dir=0`)
- `param_1 = 1` → "pon" netdev → `+0x4c8 = 1` → **DN path** (`dir=1`)

For LAN-only mode (our H3600 config: `g_pon_work_mode=0x10`), all
LAN-egress traffic flows through the "sw" netdev → **`dir=0` → UP
ring (kick = `TM[0x10054] = 1`)**.

Stock desc init (line 6752–6757, UP branch):

```c
*puVar3            = 0x80;        // desc[0..3] = 80 00 00 00 (first dword)
*(u8*)puVar3       = 0xc9;        // desc[0] = c9 (overwrites byte 0)
puVar3[1]          = 0x10000;     // desc[4..7] = 00 00 01 00 (desc[6]=1)
puVar3[2]          = 0x1000000;   // desc[8..11] = 00 00 00 01 (initial VALID bit)
puVar3[3]          = 0;           // desc[12..15] = 0
```

Then if `lan_up == 1` (line 6790):

```c
*(u16*)(puVar3+1)      = 0;                              // desc[4..5]=0 no-op
*(byte*)(puVar3+3)     = *(byte*)(puVar3+3) & 0x1f;     // clear desc[3] bits 5..7
*(u16*)(puVar3+2)      = *(u16*)(puVar3+2) & 0xfc0f
                       | ((lan_up_port + 0x28) & 0x3f) << 4;
                       // desc[2..3] port hint
```

`lan_up_port = 4` per boot printk → encoded value = `(0x2c << 4) = 0x2c0`.

### `pon_tm_data_raw_send` (plat:6600) — final desc + BMU + cache flush

```c
bp     = pon_tm_bmu_alloc_bp();
__dest = BP_BASE + bp * BP_SIZE + 0x10;   // skip 16-byte HW prefix
memcpy(__dest, skb->data, len);            // copy frame at bp_buf+16
desc[11] = (desc[11] & 1) | 0x20;          // → desc[11] = 0x21
desc[7]  = (desc[7] & 1) | (bp & 0x7f) << 1;
desc[8]  = bp >> 7;
desc[12..13] = (desc[12..13] & 3) | (len << 2);
desc[8..11] |= (len << 9);                 // (low bits len-encoded twice)
dma_cache_maint(__dest, len);              // flush BP buffer
soft_insert_tx_1desc(desc, dir);
```

For `len < 0x40` && `(desc[14] & 1) == 0` && `dir == 0`:
- `__memzero(__dest + len)` — zero-pad to 0x40
- `desc[12..13] = (desc[12..13] & 3) | 0x100`
- `desc[8..11] |= (0x40 << 9)`

### `soft_insert_tx_1desc` (plat:6234)

```c
dma_cache_maint(desc, 0x10, 1);            // flush DESC to RAM
if (dir == 0) TM[0x10054] = 1;             // UP kick
else          TM[0x10064] = 1;             // DN kick
```

**No barrier, no second register write, no post-kick desc clear.**
Stock NEVER touches the desc again after this; HW owns it.

---

## Q2 — Egress port hint (desc[2..3])

Stock encodes `((lan_up_port + 0x28) & 0x3f) << 4` into bits 4..9 of LE
u16 at desc[2..3]. With `lan_up_port = 4`: encoded = `0x2c0`.

The `+0x28 = 40` constant offset means this field is NOT the raw PHY
index (0..3 for LAN1..4) — it's a **switch-fabric egress descriptor
ID** in some packing the switch crossbar understands. Live stock dump
+ RE both confirm 0x28 is the LAN-only offset (the DN branch uses
`(*(byte*)(param_1 + 0xb4) + 0x28)` — same +0x28 offset but
per-skb-context port, not the global `lan_up_port`).

**For LAN-only mode the value is ALWAYS 0x2c (lan_up_port=4)** — it
doesn't encode "go to LAN3 specifically". The switch fabric uses
**FDB lookup on dst MAC** to choose actual egress port. So our ARP reply
to host on LAN3 gets routed by switch dst-MAC learning, not by desc
encoding. Mainline's `port=4` is correct.

Important: stock also calls `tm_set_pp_wan_cfg(lan_up_port)` =
`fpga[0xe8007] |= (1 << (4+0x19)) = (1 << 29)` via `tm_set_p2pmode`.
**That fpga reg = PP[0x1a01c]. Mainline never writes it.**

---

## Q3 — Is there a TX engine enable register? YES.

The **TM[0x4040] port mask** + **NPP[0x19068] SOPC bridge** + **PP[+0x1a01c]
PON_PP_TM_CFG** form the egress enable triple:

1. `TM[0x4040] = 0x000003ff` — written by mainline (zx_tm_dma_init:2539). 10
   bits set = all 10 switch egress ports enabled. ✓ present.
2. `NPP[0x19068] |= (1 << port)` — set on per-PHY link-UP via
   `smac_sopc_mode_switch`. Mainline added this at iter 25 (commit
   e92d08cc0). ✓ present.
3. `fpga[0xe8007] |= (1 << (lan_up_port + 0x19))` = **PP[0x1a01c] |= BIT(29)**
   for `lan_up_port=4`. Mainline does **NOT** write this.
   ❌ **MISSING.**

Live stock dump shows PP[0x1a01c] = 0 anyway (the "HW write-lock pattern"
documented in `hw_write_lock_pattern_re.md` may apply — but stock's
printk shows the write happens). The conservative reading: stock writes
it once during `tm_set_p2pmode` after BMU enable. Even if the bit
doesn't stick visibly, the side-effect of the write (likely a sticky
"PON_PP_TM_CFG written" flag inside the PP block) may gate the TX
consume engine.

There is **no separate `0x10000` "TX engine enable" register** in TM
space — TX consume is gated entirely by per-port egress masks (above)
and by the desc-ring HW being able to fetch from
`TM[0x10050]/TM[0x10060]`.

---

## Q4 — Cache coherency

Stock uses `dma_cache_maint(desc, 0x10, 1)` (`flush`) on the 16-byte
desc just before the kick, and `dma_cache_maint(__dest, len)` on the
BP buffer after memcpy.

Mainline uses `memremap_wc` for the entire 64 MiB carved region (line
1715). WC memory is uncached; writes go via the write-combine buffer
into DDR. **`dma_wmb()` is correct** for WC mappings (it drains the
write buffer). The two `dma_wmb()` calls in `zx_sw_xmit` (lines 3182,
3216) are functionally equivalent to stock's `dma_cache_maint(flush)`
for the WC case.

**Cache coherency is NOT the bug.** RX works through the same path with
the same mapping.

---

## Q5 — TX desc format byte-by-byte

Mainline `zx_sw_xmit` writes (verified vs stock `pon_tm_data_raw_send`):

| Byte | Stock | Mainline | Match? |
|------|-------|----------|--------|
| 0 | 0xc9 | 0xc9 | ✓ |
| 1 | 0x00 | 0x00 | ✓ |
| 2..3 | LE16 ((4+0x28)&0x3f)<<4 = 0x02c0 | LE16 0x02c0 | ✓ |
| 4..7 | 0x00010000 + desc[7]=(bp&0x7f)<<1 | 0x00010000 + same | ✓ |
| 8 | `bp >> 7` (in low byte of u32@+8) | same | ✓ |
| 9..10 | (part of len<<9 in u32@+8) | same | ✓ |
| 11 | 0x21 (`& 1 | 0x20`) | 0x21 | ✓ |
| 12..13 | `(len<<2)` or `0x100` if len<0x40 | matches | ✓ |
| 14..15 | 0 | 0 | ✓ |

**Desc format is byte-for-byte correct.** Not the bug.

---

## Q6 — TM[0x10068] HIGH16 = 7 stuck (and TM[0x10058] for UP)

Per `pon_tm_check_tx_done_nolock` (plat:6362):

```c
if (dir != 1) net_txq[16] -= (TM[0x10058] & 0xffff);    // UP done
else          net_txq[44] -= (TM[0x10068] & 0xffff);    // DN done
```

Stock reads ONLY the **low16** and uses it as "consumed since last
read". Empirical confirmation (commit 546ae0b3a):

- Stock low16 values vary up-and-down between reads (0x7 → 0x2 → 0x2 →
  0x0 → 0x1) — **functionally clear-on-read**.
- High16 was NEVER documented as meaningful in stock decomp; stock
  never reads it.

**Hypothesis for HIGH16 semantics**: it is the HW-side "pending count"
or "SW-cursor latched at last consume". Since stock never reads it and
its meaning isn't documented, the "stuck at 7" observation is
**circumstantial, not load-bearing**. We've been chasing a phantom.

The relevant counter is LOW16, and mainline does drain it via the
1-jiffy reclaim work (commit 80f610eda). That part is correct.

---

## ROOT CAUSE (high confidence)

The mainline TX path was **changed in iter 32 to write to DN ring and
kick DN** (lines 3146, 3197 in `zx_sw_xmit`):

```c
desc = (u8 *)e->dndesc_cpu + e->tx_head * TM_TX_DESC_SIZE;  /* DN ring */
...
tm_write(e, 0x10064, 1);                                     /* DN kick */
```

But for the **"sw" netdev in LAN-only mode** stock unambiguously uses
**UP ring + UP kick** (`pon_tm_data_raw_send(..., dir=0)` →
`soft_insert_tx_1desc(desc, 0)` → `TM[0x10054] = 1`).

The iter-32 switch was justified by "315 loopback drops" being
interpreted as "switch loopback'd UP-ring traffic back to CPU". But
that's the wrong interpretation: the switch loopback comes from a
different mechanism (CPU hairpin via FDB miss / unknown-MAC flooding),
NOT from desc-ring direction. UP/DN ring direction selects which DMA
engine consumes — for sw netdev it MUST be UP.

Additionally, mainline does a **post-kick `desc[11] &= ~0x20`** (line
3215) that stock NEVER does. Stock kicks then leaves desc[11] = 0x21
on the slot, advances SW cursor, and HW consumes/advances internally.
The post-kick clear is **actively defeating HW** — if HW reads the
desc asynchronously (after the kick returns) it sees VALID=0 and skips
the slot. This explains the "frames queue but HW never drains" symptom
across both UP and DN ring experiments.

A secondary contributing factor is the **missing PP[0x1a01c] |=
BIT(29)** write — stock's `tm_set_p2pmode(4)` enables the PON_PP_TM
egress route for `lan_up_port=4`. Without it the TX desc may be
consumed by HW DMA but dropped at the PP egress decision (no
qmg-up-sw-fwd / no MAC TX counter increment).

---

## Single most actionable fix

**Two-line change in `zx_sw_xmit`** (`linux-v6.6/drivers/net/ethernet/zte/
zx-eth-main.c` lines ~3146, 3197, 3211–3217):

1. Restore UP ring write/kick:
   - `desc = (u8 *)e->txdesc_cpu + e->tx_head * TM_TX_DESC_SIZE;` (was
     `dndesc_cpu`)
   - `tm_write(e, 0x10054, 1);` (was `tm_write(e, 0x10064, 1)`)

2. Delete the post-kick desc invalidation block (lines 3211–3217).
   Stock NEVER clears desc[11] bit 5 after the kick. The "DUPs"
   symptom that motivated it was a different bug (CPU hairpin via FDB
   flooding); the right fix is loopback drop in the RX path (already
   present at line 2720) plus correct switch FDB programming.

3. ALSO write `PP[0x1a01c] |= BIT(29)` once at init (mirrors stock
   `tm_set_p2pmode(4)`). Add to `zx_tm_dma_init` after the existing PP
   global writes:

   ```c
   /* Stock tm_set_p2pmode(lan_up_port=4) — PON_PP_TM_CFG egress enable. */
   {
       void __iomem *pp = e->base + PP_OFF;
       writel(readl(pp + 0x1a01c) | BIT(29), pp + 0x1a01c);
   }
   ```

---

## Confidence

- **High** on root cause #1 (wrong ring/kick): stock decomp is
  unambiguous (`pon_tm_data_raw_send(..., 0)` →
  `soft_insert_tx_1desc(desc, 0)` → `TM[0x10054]`). The iter-32 switch
  to DN was a reasoning error about loopback symptoms.
- **High** on root cause #2 (post-kick desc clear): stock has no
  equivalent operation; the clear is defeating HW asynchronous desc
  fetch.
- **Medium** on root cause #3 (missing PP[0x1a01c] write): the live
  register reads 0 in the stock 2 MiB dump, suggesting the write may
  not stick. But stock's `printk` of `after PON_PP_TM_CFG=0x%x` would
  show what the write produces; without that capture we don't know if
  it's a no-op or essential. Cost to add is zero; worth applying
  alongside #1/#2.

---

## Required reg / desc-byte changes (summary)

| Where | Change | Direction |
|-------|--------|-----------|
| `zx_sw_xmit` desc target | `dndesc_cpu` → `txdesc_cpu` | restore UP ring |
| `zx_sw_xmit` kick | `TM[0x10064]=1` → `TM[0x10054]=1` | restore UP kick |
| `zx_sw_xmit` post-kick | delete `desc[11] &= ~0x20` block | stock never clears |
| `zx_tm_dma_init` | add `PP[0x1a01c] |= BIT(29)` | mirror `tm_set_p2pmode(4)` |

No desc-byte changes. The desc format is correct.

---

## Cross-references

- `tx_path_stock_decomp.md` — prior pass (now superseded by this doc;
  this doc keeps the desc-format verification and adds the
  UP-vs-DN-ring root cause).
- `mac_to_cpu_path_re.md` — RX path RE; section Q4(d) hinted at the
  egress-port encoding question.
- `lan_up_port_lifecycle.md` — `lan_up_port=4` setter / consumer
  chain; explains why `+0x28` is the LAN-only egress offset.
- `bmu_protocol_deep_re.md` — BMU alloc/free protocol; confirms TX BP
  alloc is correct (mainline `tm_tx_dropped = 0`).
- `iter13_tm_bit1_storm_2026-05-27.md` — TM[0x100] bit 1 storm
  attributed to TX consume wedge — should self-resolve once HW
  consumes UP ring.
- `stock_tx_path_kotrace_2026-05-25.md` — kotrace v2 capture of stock
  TX (note: kotrace r2=1 reading appears to be a tooling artifact;
  trust the decomp which is unambiguous on dir=0 for sw netdev).

---

## Open questions (lower priority)

- What does TM[0x10068]/TM[0x10058] HIGH16 actually mean? Stock never
  reads it; mainline observation that it's "stuck" may be irrelevant.
  After the fix above, this can be re-tested — if HW consumes the UP
  ring properly, high16 may show meaningful producer-cursor advance.

- Does `PP[0x1a01c]` ever observably latch BIT(29)? Run a stock
  bench-test where we capture the dump immediately after `tm_set_p2pmode`
  prints its "after" printk — if the read-back shows the bit, it's a
  TX gate; if 0, it's a write-only side-effect register.

- Does the switch FDB get populated with the device CPU MAC
  (f4:f6:47:0f:42:64) on UP ring TX? After fix #1+#2, if pings still
  drop, check `pp_get_fdb` for the device's own MAC presence — without
  it, the switch may broadcast every CPU TX which would corrupt the
  bench bridge.
