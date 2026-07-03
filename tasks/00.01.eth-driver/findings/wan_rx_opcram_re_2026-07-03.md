# WAN-RX one-wrap wedge — OPC-RAM / trap-occupancy RE (device-free, 2026-07-03)

Pure offline RE (no device touched). Goal was to crack the "QMG DN hw_trap latches at
exactly 1024" wedge by extracting the OPC-RAM occupancy protocol and finding the stock
per-consumed-frame occupancy-return op that mainline omits.

## TL;DR — the two starting leads are REFUTED; the real gate is the RED block

1. **Lead 1 (OPC-RAM indirect occupancy) — REFUTED.** `greg_set_opc_ram_init` is NOT an
   indirect CMD/DATA occupancy RAM. It is a **2-bit soft-reset trigger** in a global
   control register: `opc_ram_init = 0x921C0008[9:8]`. There is no per-CPU-queue
   occupancy field behind it. (It survives as a *soft-reset lever* — see Fix C.)

2. **Lead 2 (stock per-frame occupancy-return the poll omits) — REFUTED.** Stock
   `pon_tm_net_poll` (plat @0x1c9f0) does exactly `pp_bmu_free_bp` + `soft_release_rx_desc`
   per consumed frame — **byte-for-byte the same set of ops mainline already does**. There
   is NO extra QMG/OPC/SADM "credit-return" register write in the stock RX path. Nothing is
   missing from `zx_tm_napi_poll`.

3. **The real mechanism (new, higher confidence): the RED block, one stage UPSTREAM of the
   QMG.** `0x9234c04c` (QMG DN hw_trap) is a **read-only statistics counter** (confirmed
   on-device + confirmed here: `QmgRegTable[8]`), i.e. a passive observer — not a gate.
   The pipeline order (decomp `pp_broadcast_drop_re`) is:
   `… → RED(fwd/trap/drop) → QMG(sw_fwd/hw_fwd/hw_trap) → …`. Stock `pon_tm_red_init`
   programs the RED **out-buffer queue depth for queues 0–15 = 0x400 = 1024**. The CPU
   trap queues are exactly qids 0–7 (see `zx_def_ptl_pkt_map`, all qid0/qid1 ∈ 0..7). When
   the DN CPU-trap queue's RED occupancy reaches its 1024 out-buffer limit, RED stops
   admitting to that queue and (with open_out/trap_color set) **demotes further traps to
   sw_fwd** — which is *exactly* the observed signature (QMG hw_trap frozen at 1024,
   sw_fwd climbing, RED drop climbing as background).

So "1024" is the **RED per-queue out-buffer depth**, and the wedge is the RED CPU-trap
queue occupancy pinned at that depth and never draining.

---

## 1. OPC-RAM indirect protocol (the requested deliverable)

`greg_set_opc_ram_init(control)` (tm @0x32498) → `tmOnuRegWrite(0x19, control, 0, &gregRegTable)`.

`tmOnuRegWrite`/`tmOnuRegRead` (tm @0x45c14/@0x45bac) resolve the target via a table entry
of stride **0x1c**:
```
entry+0x00 = id (self)          entry+0x10 = shift  (ushort)
entry+0x04 = type               entry+0x14 = per-index stride
entry+0x08 = base reg-id        entry+0x18 = access count
entry+0x0c = mask
phys = 0x92000000 + (base_id + stride*index)*4        // fpga_read_reg(id)=*(pon+id*4)
write = RMW: (old & ~(mask<<shift)) | ((val & mask) << shift)
```

Extracted `gregRegTable[0x19]` (tm.ko .data @0x4ab0 + 0x19*0x1c, verified no reloc):
```
base_id = 0x70002  →  phys 0x921C0008     mask = 0x3   shift = 8   stride = 0
```
i.e. **opc_ram_init = a 2-bit field `0x921C0008[9:8]`**, NOT an indirect RAM. The whole
greg RAM-init register `0x921C0008` (matches DATASHEET PART 2):

| field | phys / bits | init fn (tm) | greg id |
|---|---|---|---|
| spa_ram_init  | `0x921C0008[5:0]`  | `greg_set_spa_ram_init` @0x325c0  | 0x1b |
| smct_ram_init | `0x921C0008[7:6]`  | `greg_set_smct_ram_init` @0x3252c | 0x1a |
| **opc_ram_init** | **`0x921C0008[9:8]`** | `greg_set_opc_ram_init` @0x32498 | **0x19** |
| soam_ram_init | `0x921C0008[12:10]` | `greg_set_soam_ram_init` @0x32404 | 0x18 |
| nppu_pm_ram_init | `0x921C000C[4:0]` | `greg_set_nppu_pm_ram_init` @0x32654 | 0x1c |

These are RAM soft-init/zeroing pulse controls (a small state-machine clears the block's
internal RAM). **They are NOT per-frame occupancy counters.** Stock's boot `tm_initial`
(@0x542d4 → tm_pon_tm_initial/pp/npp) does **not** call any of them, and neither does
`switch.ko` or the plat kmod — so "mainline omits opc_ram_init" is a **non-difference**
(stock's Linux path omits it too; the RAM is init'd by HW reset / bootloader).

## 2. Stock RX-consume path — nothing missing

`pon_tm_net_poll` (plat @0x1c9f0), per descriptor, does ONLY:
- `pp_bmu_free_bp(bppe_idx, 0, jumbo)`  (free the buffer-pool entry)
- `soft_release_rx_desc(ring, qid, sop, count)` → `tm[0x4068]=ring<<14|count<<4|qid|sop<<3; tm[0x4064]=1`

`soft_release_rx_desc` (plat @0x1a8e8) is byte-identical to mainline's
`zx_tm_release_rx_desc_raw`. It processes both rings and splits sop=0/sop=1 sub-counts —
mainline already replicates this (dual-ring, `slots-ack` sop=0 + `ack` sop=1). **There is
no additional QMG/OPC/SADM register write per consumed frame.** This positively rules out
"add a missing occupancy-return write to the poll." The on-device iteration-2 result
(release sop=0 count=0x400 on all 8 qids → no unwedge) is consistent: the RX-ring release
is not the lever.

## 3. The RED mechanism + the new device-safe ORACLE

RED block base `0x92344000` (= tm_base+0x4000). Indirect RAM protocol (stock
`red_set_queue_cfg`@plat 0x1a618, `red_get_queue_status`@0x1a7e0,
`red_get_buffer_queue_used_space`@tm 0x440e0):
```
CMD   0x92344014 = qidx | (ram_id << 22) | (rw << 27)
DONE  0x92344018  bit0 == 1  → idle/ready (poll before AND after)
DATA0 0x9234401C  (DATA1/2/3 = +0x20/+0x24/+0x28)
```
RED RAM ids: 0 = out-buffer depth cfg (4 words), 1 = **queue status/occupancy** (read),
2 = in-buffer depth cfg, 4 = WRED drop-curve (Yellow/Green thresholds, 4 words),
5 = **buffer_queue_used_space** (read, [15:0]).

Stock `pon_tm_red_init` and mainline `zx_tm_red_init` are IDENTICAL: q0–15 out-buffer=0x400
(1024), q16–399=0x800400, RAM2 in-buffer, RAM4 curve `{0xff803fff,0x100ff80,0x100200,0x20}`.
So the RED config is NOT a stock/mainline difference — the 1024 depth is intentional in both.

**NEW ORACLE (device-safe — RED is in the safe TM/PP range, NOT the MAC hazard block):**
read the RED per-queue occupancy DIRECTLY instead of inferring it from the QMG stat:
```
# occupancy of CPU-trap queue q (q = 0..7), via RED RAM 1 "queue status":
poke 0x92344018 -> (wait bit0==1)
poke 0x92344014 = q | 0x8400000     # ram1(<<22)=0x400000 | rw1(<<27)=0x8000000
(wait 0x92344018 bit0==1)
peek 0x9234401C  -> occupancy in [11:0]   # expect ~0x400 (1024) on the wedged DN queue
# cross-check via RAM 5 used_space:  CMD = q | 0x9400000 ; DATA0[15:0]
```
Prediction to confirm the mechanism on the next device iteration: in the wedged state, the
DN CPU-trap queue's RED occupancy is pinned at ~1024 while a healthy UP qid oscillates.

## 4. Why it latches (and why stock doesn't)

RED occupancy is incremented on enqueue-to-CPU-queue and decremented on dequeue. Frames DO
reach the CPU (ring drains, 1024 delivered) so the dequeue path runs for the first ring's
worth, yet the occupancy sticks at 1024 permanently → the dequeue-side decrement stops.
Because RED config + per-frame accounting are byte-identical to stock, the latch is NOT a
missing config or a missing poll write. It is a HW-internal accounting effect exposed only
under **sustained trap-all load**: mainline traps ~all traffic to the CPU (the switch never
HW-forwards — see [[zte-hw-forwarding-deadend]]), so the DN CPU-trap queue fills its 1024
out-buffer; stock HW-forwards, so its CPU-trap queue rarely fills and never hits the wall.

## 5. Ranked fixes / next-iteration plan

**Confidence: HIGH — do this first (diagnostic, read-only, safe):**
- Reproduce wedge, then sweep RED occupancy (RAM 1 recipe above) for q=0..7. Identify the
  pinned queue (expected ≈1024). This converts the passive QMG-stat oracle into the actual
  gated resource and tells us the exact DN trap qid. Also read a healthy UP qid for contrast.

**Fix A — RED occupancy re-arm watchdog (confidence MEDIUM, the most promising unwedge):**
- Once the pinned qid is known, test clearing it live (RED block, safe range):
  1. Re-write RAM0 out-buffer cfg for that qid (`0x92344014=q|0(ram0)`, DATA0=0x400) — may
     reset the queue's occupancy accounting.
  2. If that fails, toggle the RED block enable: `0x92344004[1:0]` → 0 then back to stock
     (`red_set_cfg_enable`; the mainline stock value has share_mode|trap_color|open_out set)
     — a RED soft-disable/re-enable is the closest thing to a block reset for this stage.
- If either clears the pin (occupancy drops, QMG hw_trap resumes climbing), wire it into a
  **driver watchdog** (delayed_work): oracle = RED occupancy(q) pinned high AND `smac4 RX`
  climbing (via pipeline_stats) → re-arm. This is the concrete, keyed-on-a-real-oracle
  version of the old "find a soft-reset" lead.

**Fix B — RAM soft-reset pulse (confidence LOW-MEDIUM, fallback lever):**
- If RED re-enable doesn't clear it, pulse the greg RAM-inits (now fully mapped):
  `opc_ram_init 0x921C0008[9:8]`, `smct_ram_init [7:6]`, `spa_ram_init [5:0]` (write a
  nonzero control then 0). Do this OFFLINE-computed only, RAM-only, never near MAC 0x92300000.
  Risk: re-init mid-flight may drop in-flight frames; acceptable for a wedged path.

**Fix C — reduce trapping = the durable root-cause fix (confidence HIGH on causation):**
- The 1024 out-buffer is a genuine CPU-trap-queue resource, not a bulk datapath. The lasting
  fix is HW forwarding (Phase 6 offload) so the CPU-trap queue isn't a sustained bulk path.
  Raising the q0–15 out-buffer depth above 1024 only delays the wall (and diverges from stock).

**Fix D — RX-qid ↔ RED-queue mapping check (confidence UNKNOWN, cheap to check):**
- If the diagnostic shows the pinned RED queue is one the driver's `soft_release_rx_desc`
  never targets for the DN path (qid mismatch between the DMA-ring qid 0–7 and the RED queue
  the DN ptype uses), then the driver is releasing the wrong queue and the dequeue-decrement
  never reaches the DN RED queue. Fix = release the correct qid. The iteration-2 "released
  all 8 qids, no effect" argues against a pure ring-credit miss but does NOT rule out the RED
  queue being decremented by a different signal than the ring release.

## 6. Driver code change (when a fix is confirmed)

- Diagnostic: add a debugfs reader that runs the RED RAM-1/RAM-5 occupancy recipe for q0..7
  (extend `pipeline_stats`). No datapath change.
- Fix A watchdog: a `delayed_work` (reuse the `zx_bmu_dump_work` pattern) that, on the pinned
  oracle, does the RED re-arm write. Put the RED re-arm helper next to `zx_red_block_init`
  (it already has RED_IND_CMD/DONE/DATA0 defs and the cfg_enable RMW at `RED_CFG=0x184004`).
  Trigger from the same place the TX-reclaim timer runs.

---

### Register quick-reference (all verified from decomp this session)
```
opc_ram_init   0x921C0008[9:8]   (greg id 0x19; soft-reset trigger, not occupancy)
smct_ram_init  0x921C0008[7:6]   spa_ram_init 0x921C0008[5:0]   soam 0x921C0008[12:10]
QMG (all RO stats): dn sw_fwd 0x9234C044 · dn hw_fwd 0x9234C048 · dn hw_trap 0x9234C04C
                    up sw_fwd 0x9234C054 · up hw_fwd 0x9234C05C · up hw_trap 0x9234C060
QMG cfg (RW): up_thd 0xC000[12:0] · dn_thd 0xC000[25:13] · trap_cfg 0xC008[1:0] · up_depth 0xC00C[10:0]
RED indirect: CMD 0x92344014 = q|(ram<<22)|(rw<<27) · DONE 0x92344018 b0 · DATA0..3 0x9234401C/20/24/28
RED occupancy read: ram1 (q|0x8400000) or ram5 used_space (q|0x9400000) → DATA0
CPU-trap qids (zx_def_ptl_pkt_map): all ∈ 0..7  → all in RED's q0..15 out-buffer=1024 range
```
