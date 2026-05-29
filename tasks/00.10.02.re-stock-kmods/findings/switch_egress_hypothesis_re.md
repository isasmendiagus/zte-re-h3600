# Switch egress gate hypothesis + `txtest` pipeline-trace design

**Date:** 2026-05-28. **Scope:** DECOMP/STATIC ONLY (live device in use by another
process). **Symptom (input):** CPU-sourced TX (UP ring, GEM 0x2c, dst = host MAC
learned in FDB-A on internal port 3 = PHY[2]/MAC[2]) HAIRPINS back to CPU
(~15 loopbacks/test). `TM[0x10058]` (UP egress/consume count) stays **0** forever:
HW reads the desc (cursor `TM[0x1005c]` advances, BMU recycles the BP) but never
egresses to the wire.

---

## PART 0 — address-map reconciliation (this overturns the U-Boot theory)

`e->base` = phys `0x92000000 + 0x1c0000` = `0x921c0000` (zx-eth-main.c:1122,
`ZX_FPGA_BASE_TO_NPP_OFF 0x1c0000`). So:

| Block | Phys | `e->base` off | What it is |
|---|---|---|---|
| TM/CLA ctrl | 0x92340000 | TM_OFF 0x180000 | TM crossbar, DMA rings (0x10xxx), QMG (0xCxxx @0x9234c000), SCH (0x14xxx @0x92354000) |
| ETH_TM2 / egress-SMUX | 0x923a0000 | 0x1e0000 | per-port egress mux + MAC-addr slots |
| GE SMUX | 0x921d4000 | 0x14000 | GE-MAC per-port |
| SOPC bridge | 0x921d9000 | 0x19000 | SMAC↔SOPC handshake (NPP[0x19068]) |

**Decisive ground truth from `regs/stock_eth_2mib.txt` (working stock KMOD, live):**

```
923a0000 00000000   923a0004 00000001   923a001c 21200000  923a0020 4eb20000
923a0058 00000000   923a0078 00000000   923a007c 00000000  923a00e0 00000000  <-- egress-enable = 0
92340000 00000140   92340004 00000010                       <-- TM/CLA master ctrl
92350000 003f6564   9234c000 01f40fa0   92354000 000003d7   <-- DMA_CTRL / QMG / SCH
```

The **U-Boot** TX path (FUN_40e4fda4→FUN_40e50384/FUN_40e4fd24/FUN_40e5092c)
programs ETH_TM2: `0x923a00e0 = 0x11` (egress enable), MAC slots `0x923a0078/7c`,
queue-ptr `0x923a0058`, then SMUX `0x921d4000` descriptors (FUN_40e50b84) — a
**direct CPU→MAC egress mux**. The **stock KMOD leaves all of those = 0** (live
proof above). So the kmod does NOT use the ETH_TM2 direct path; **kmod CPU-TX
egresses through the PP_BRG switch fabric**, and mainline must match the kmod, not
U-Boot. (U-Boot is still a useful "it can be done on this silicon" reference, but
its egress model differs — do NOT chase 0x923a00e0=0x11 in the kmod-faithful driver.)

This also retires three earlier theories already flagged in the session as
RULED OUT, and adds proof: PP[0xc080] is **0** in stock-live (`921cc080 00000000`),
not 0x600/0x1000 — so `pon_pp_cla_init`'s `pp_base+0xc080=0x1000`
(plat:5505) does NOT latch and is not the gate.

---

## PART 1 — the egress gate hypothesis

### Pipeline (kmod model), with the live anchor at each stage

```
zx_sw_xmit builds UP desc  →  TM[0x10054]=1 (UP kick)
   → TM UP-ring CONSUME engine dequeues desc, allocs/links BP   [TM[0x10058]++ here]
   → TM crossbar hands frame to QMG (0x9234c000) by GEM/queue
   → SCH (0x92354000) schedules the egress queue→port
   → PP_BRG (PP 0x8xxx): GEM-classify + dst-MAC FDB lookup → egress port 3
   → DSCH/SOPC → MAC[2] TX
```

`TM[0x10058]` stays 0 ⇒ the frame **dies at the very first stage**: the TM UP-ring
**consume engine never dequeues**. Everything PP_BRG/QMG/SCH-side is downstream of
a step that never fires, so all the prior PP[0x83xx]/[0x80xx] flood/FDB work
(correct, keep it) cannot matter yet. The "~15 loopbacks" are a *separate* RX-side
artifact (the kernel's own broadcast ARP reflecting), not the unicast TX under test.

### #1 GATE HYPOTHESIS — the UP ring is kicked but its base/consume regs are mis-paired

Stock `pon_tm_dma_init` (plat:6279) programs the UP ring as:

```c
tm_base+0x10050 = <UP ring DMA base>      // 0x405e0000-ish
tm_base+0x10060 = <DN ring DMA base>      // 0x405f0000-ish (64 KiB apart)
```

and the dispatcher `soft_insert_tx_1desc(desc, dir=0)` (plat:6234) does ONLY:

```c
dma_cache_maint(desc,0x10,1);
tm_base+0x10054 = 1;                       // UP kick. dir=1 → 0x10064. NEVER both.
```

The TM UP **consume cursor / base pair** is `0x10050` (base) ↔ `0x10054` (kick) ↔
`0x10058` (consumed count) ↔ `0x1005c` (HW cursor). The DN set is
`0x10060/0x10064/0x10068/0x1006c`.

**Mainline mismatch (zx-eth-main.c):**
- `TM_REG_DMA_TX_UP_BASE` is `#define`d to **0x10050** (line 159) and
  `zx_tm_dma_init` writes `e->txdesc_dma` there (line 2519) — OK.
- BUT `zx_sw_xmit` writes the desc into `e->txdesc_cpu` whose DMA addr is
  `e->txdesc_dma` (line 1742) — OK — and then does a **dual kick + post-kick
  VALID-clear** (lines 3237 + ~3247): it kicks `0x10054` AND `0x10064`, then
  clears `desc[11] bit5` on the slot it just handed to HW. Stock does **neither**.
  - The DN kick (`0x10064`) tells the DN consume engine to dequeue from the DN
    base `0x10060` (= `e->dndesc_dma`), where there is **no valid CPU desc** → DN
    engine spins/aborts, and on a no-PON unit the DN classifier hairpins to CPU.
  - The post-kick `desc[11] &= ~0x20` races the **UP** consume engine: HW fetches
    the desc asynchronously *after* the kick returns; clearing VALID first makes
    the UP engine skip the slot → **`TM[0x10058]` never increments** = exactly the
    observed symptom. The cursor `0x1005c` still advances (it tracks fetch, not
    consume), and the BP is recycled — also exactly observed.

**FIX (highest confidence), `zx_sw_xmit`:**
1. Delete the DN kick `tm_write(e, 0x10064, 1);` (keep UP only) — **zx-eth-main.c ~line 3238/3252** (the second kick) and the dual-kick comment block 3229-3235.
2. Delete the post-kick `desc[11] &= ~0x20` invalidation block — **zx-eth-main.c ~lines 3239-3255**. Stock owns the desc from the kick onward; never write it after.

Rationale that this is *the* gate and not a re-litigation: the session "ruled out"
the *desc bytes* and the *UP kick itself*, but the **post-kick VALID clear** and the
**parasitic DN kick** are mutations that happen AFTER the kick — they are the only
two things in the path that can make `TM[0x10058]` stay 0 while the cursor advances
and the BP recycles. They were introduced as anti-storm/anti-dup hacks and are the
direct cause of "consume engine never dequeues."

### #2 (apply together, secondary): UP ring base must differ from the carved
`zx_eth_repoint_tm_descriptors` (line 4284) re-writes `TM_REG_DMA_TX_UP_BASE`
(0x10050) = `e->txdesc_dma` and `0x10060` = `e->dndesc_dma`. Confirm `e->txdesc_dma`
≠ `e->dndesc_dma` (carved offsets `CARVED_TXUP_OFF` vs `CARVED_TXDN_OFF`, lines
1742/1744) — they are 64 KiB apart, matching stock. Keep. If after fix #1 the DN
engine still asserts, mask DN entirely: do not kick 0x10064 anywhere and leave
`0x10068` unread.

### #3 (cleanup, not the gate): ETH_TM2 stays 0
Do NOT add `0x1e00e0=0x11` / MAC slots `0x1e0078`. Stock-live proves the kmod path
leaves them 0; writing them would diverge from the kmod and risk re-enabling the
U-Boot-style direct mux that conflicts with PP_BRG.

**One-line gate:** the UP-ring consume engine never dequeues because mainline
**clears the desc VALID bit and fires a spurious DN kick after the UP kick**;
stock does neither. Remove both — `zx_sw_xmit`, zx-eth-main.c ~lines 3238-3255.

---

## PART 2 — `txtest` debugfs: inject ONE known frame, watch where it dies

### Goal
A single controlled CPU-TX on demand with a FIXED, uniquely-identifiable frame, so
the per-stage counters (sibling task is mapping these HW registers) let us
binary-search the stage at which the one frame dies.

### The fixed frame (64 bytes, uniquely tagged)
```
dst MAC  = c8:a3:62:e9:59:00      (HOST — already learned in FDB-A, internal port 3 → MAC[2])
src MAC  = f4:f6:47:0f:42:64      (device own MAC)
ethertype= 0x88b5                 (IEEE local-experimental; NOT IP/ARP so the kernel
                                   stack never reflects it → no RX-side broadcast noise)
payload  = "ZXTX" 0xA5A5A5A5 <seq:le32> <pad 0x00 .. to 64B>
```
- Unicast dst that is FDB-resolved ⇒ exercises the exact unicast egress decision
  (not flood). ethertype 0x88b5 makes it trivially greppable in tcpdump and in any
  BP hexdump, and guarantees it is NOT the broadcast ARP that causes the residual 15.
- `<seq>` increments per invocation so re-emits/dups are distinguishable.

### Mechanism (reuse the real path; don't fork it)
Add `debugfs file /sys/kernel/debug/zx_eth/txtest`:
- On write of an integer N (default 1): build N copies of the frame into an skb and
  call **`zx_sw_xmit(skb, e->sw_dev)`** — the SAME path under test. This guarantees
  we measure the production path, including the fix from Part 1.
- Snapshot all stage counters immediately before and ~1ms after (one `udelay`/yield),
  print the delta. No live device interaction beyond the existing `regdump`/`poke`.

```c
/* pseudo-handler */
static ssize_t txtest_write(struct file *f, const char __user *u, size_t n, loff_t *o)
{
    struct zx_eth *e = ...;
    u32 reps = parse_uint(u, n) ?: 1;
    struct stage_snap a, b;
    snap(e, &a);
    for (i=0;i<reps;i++) { skb = build_fixed_frame(e, seq++); zx_sw_xmit(skb, e->sw_dev); }
    mdelay(2);
    snap(e, &b);
    print_delta(&a, &b);   /* one line per stage */
    return n;
}
```

### Stage → counter map (expected delta for ONE good frame)

| # | Stage | Counter (read) | Expect/frame | If 0 here, frame died at... |
|---|---|---|---|---|
| 0 | driver enqueue | `e->tm_tx_count` (sw) | +1 | software path / skb build |
| 1 | UP kick accepted | `TM[0x10054]` write-ack / `TM[0x1005c]` HIGH16 (fetch cursor) | cursor +1 | desc not visible to HW (dma_wmb / base mismatch) |
| 2 | **UP consume/egress** | **`TM[0x10058]` & 0xffff** | **+1** | **THE GATE (Part 1). consume engine — fix lands here** |
| 3 | QMG dequeue | `TM[0x9234c000-rel]` QMG per-queue occupancy/deq stat (sibling-mapped) | +1 | queue→port binding (0x401c/0x4020/0x4024/0x4028) |
| 4 | SCH schedule | SCH per-port served stat under `TM[0x14xxx]` (sibling-mapped) | +1 | SCH enable mask `TM[0x14000]=0x3d7` / port-4 bit |
| 5 | PP_BRG forward | PP bridge fwd/learn counter + per-port TX `PP[0x8xxx]` stat | +1 to port 3 | FDB lookup / isolation / VLAN-0 membership |
| 6 | MAC TX | MAC[2] TX-frame counter `MAC2 + 0xc20/0xc50` region (per U-Boot FUN_40e50c40) | +1 | SOPC bridge `NPP[0x19068]` / MAC enable+`+0xE0` |
| 7 | wire | host `tcpdump -e ether proto 0x88b5` | 1 frame | physical/PHY |

**Binary-search rule:** find the lowest # whose delta is 0. Today the prediction is
**stage 2 = 0** (the gate). After the Part-1 fix, expect 2/3/4/5/6/7 to light up in
order; the first that stays 0 is the next gate (most-likely-next: stage 6, needing
the live-proven `MAC[2]+0xE0 = 0x00011200` anti-storm word + SOPC `NPP[0x19068]`
bit, per session notes & U-Boot FUN_40e50c40:64).

### Coordination note for the counter sibling task
Stages 3/4 need the QMG (`0x9234c000`) deq stat and SCH (`0x92354000`) served stat
register offsets — request those. Stage 6 MAC-TX counter offset: U-Boot writes
MAC[N]+0xc20=0x32 / +0xc50=0xa8 (config); the TX *frame* counter is elsewhere in
the MAC stat block — request the MAC stat-counter offset for "tx_frames_ok".

---

## Confidence
- **Address-map / ETH_TM2-is-0-in-kmod:** HIGH (live dump 923a00e0=0, 92340000=0x140
  match static replay; U-Boot vs kmod use different egress models — proven).
- **#1 gate (post-kick VALID clear + DN kick):** HIGH for "explains TM[0x10058]==0
  with cursor-advance + BP-recycle"; these are the only two post-kick desc mutations
  in the path and both are non-stock. The clean test is the Part-2 `txtest` stage-2
  delta before vs after removing them.
- **PP[0xc080] dead candidate:** HIGH (stock-live = 0).

## Cross-references
- `session_2026-05-28_tx_egress_state.md` (symptom + ruled-out list)
- `cpu_egress_routing_re.md` Root-cause B (post-kick clear) — this doc confirms it
  is THE gate via the new TM[0x10058]==0 + live-ETH_TM2 evidence.
- `cpu_lan_egress_gate_re.md` (broadcast-flood = the residual 15, separate axis)
- U-Boot: FUN_40e50854 (TX dispatch), FUN_40e4fda4/FUN_40e50384/FUN_40e4fd24/
  FUN_40e5092c (ETH_TM2 egress mux — the U-Boot-only path), FUN_40e50c40 (MAC+SOPC).
- Stock kmod: plat:6234 `soft_insert_tx_1desc`, plat:6279 `pon_tm_dma_init`,
  plat:6721 `pon_tm_net_tx`, plat:5502 `pon_pp_cla_init`.
- mainline: zx-eth-main.c:2499 `zx_tm_dma_init`, :3117 `zx_sw_xmit`,
  :4271 `zx_eth_repoint_tm_descriptors`.
