# WiFi Stage-3: the QMG DN queue-5 "consumer binding" — device-free stock-decomp RE (2026-07-24)

Follow-up to `findings/wifi_stage3_phaseB_ondevice_validation_2026-07-07.md` (Appendix 2:
injected WiFi-vif frames classify perfectly — `inport=7, TRAP, reason=ARP` — land TM DN
queue 5, whose status byte-pair ticks per frame, yet no descriptor is ever written to DDR).
Task: find, in the stock decompilation, how stock binds queue 5's dequeue consumer
(hypothesis at hand-off: "stock binds it to the IDM RX ring at WLAN-config time").

**Device NOT touched** — pure decomp/source reading. Sources cited as `file:line`
(decomp files under `tasks/00.10.02.re-stock-kmods/findings/`, mainline =
`linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`).

---

## TL;DR

1. **The hand-off hypothesis is REFUTED by the decomp.** Stock has **no per-queue
   consumer-binding mechanism at all** — nothing binds any QMG/TM DN queue to the IDM
   RX ring, at WLAN-config time or ever. All 8 CPU trap queues (× 2 ring slices each)
   are drained by the **single CPU RX DMA engine** and one NAPI poll
   (`pon_tm_net_poll`), queue 5 included. On stock, q5 is simply the ordinary
   ARP/protocol trap queue (`def_ptl_pkt_map` ptype 0x11 → qid **5 in both columns**,
   `zx_pkt_map.h:38`) and delivers through the same rings as every other queue.
2. **The IDM RX ring never receives traps on stock.** It receives only fabric
   **hw-forward egress to ports 6/7** (FFE-offloaded flows). Stock's WLAN→router
   slow path never enters the fabric: wlan0 is SW-bridged; `idmfdb.ko` is a pure
   software shuttle (netdev→netdev `ndo_start_xmit`, no MMIO) gated by
   `ffe_get_npu_enable()` (`decomp_all_idmfdb.c:1,:529`). So Phase-B's expectation
   "trapped ring-ingress frames should surface on the IDM RX ring" tests a path
   **stock itself never uses**.
3. **What actually selects the trap queue** is CLA ram7, and it is **dual-banked in a
   way mainline only half-replays**: stock writes qid0 into 7 per-inport banks
   (offsets 0x080/0x100/0x180/0x200/0x280/0x300/0x380) **and qid1 into the base bank
   0x000-0x7f** (the "dir1"/port-5 slot). Mainline replays only the per-port banks
   and leaves the base bank at its blanket value 7 — and the base bank is
   **live-proven** trap-queue steering (churn-fix session). This bank split — not a
   queue-consumer register — is where a re-steer fix lives.
4. **Why q4/q7 deliver on mainline and q5 doesn't**: nothing per-queue is "armed" for
   4/7 — the stock contract needs no arming (HW keeps pending counts, SW keeps
   cursors, `soft_release_rx_desc` keeps them consistent; **no init-time credit
   seeding exists anywhere** — the release doorbell `tm[0x4064/0x4068]` has exactly
   one writer in the entire stock plat module). q4/q7 simply have healthy,
   exercised release cycles from boot (wire traps ride ram2 `cpu_qid` overrides into
   them). q5 was never exercised by wire traffic on mainline and its observed
   pop-to-nowhere is a **mainline-local state/pairing pathology**, not a missing
   stock write — see §5 for the candidate mechanisms and the targeted live checks.

---

## 1. The stock CPU trap-queue delivery machinery (the "consumer" that exists)

### 1.1 One DMA, 8 queues × 2 ring slices, one poll

- `pon_tm_queue_init` (`decomp_all_plat_zxylzb_9128S.c:6914-6944`): per queue q=0..7,
  two DDR descriptor slices — slice A at `carve_base + q*0x4000`, slice B at
  `A + 0x20000`; 0x400 descriptors × 16 B each; SW cursors zeroed. Pure SW-side
  bookkeeping — **no HW register is written per queue**.
- `pon_tm_net_poll` (`:8558-8866`): queue loop is a plain bitmap walk `q = 7..0`
  over **all 8 queues** (`local_44 = 0xff`, `:8601-8612`). Per queue it reads the
  packed pending register `TM[0x10100 + q*4]` (`:8612`, via
  `tm_base + (q + 0x4040)*4`), drains **hi16-count** frames from one slice
  (`iVar13+0x78/+0x7c` base/cursor, `:8618-8731`) and **lo16-count** frames from the
  other (`iVar13+0x38/+0x3c`, `:8732-8850`), advancing cursors strictly by 1 with
  `& 0x3ff` wrap. Queue 5 receives **zero special treatment**.
- Delivery targets are the two TM netdevs (`pon_tm_net_register(1,..)/(0,..)`,
  `:6947-6977`) and the `switch_skb_recv` hook — i.e. the normal CPU slow path.

### 1.2 The only per-(queue,ring) mechanism: the release-credit doorbell

- `soft_release_rx_desc(ring, q, sop, count)` (`:7202-7232`):
  `tm[0x4068] = ring<<14 | count<<4 | sop<<3 | q; tm[0x4064] = 1`
  (phys 0x92344064/68; mainline `TM_RED_RELEASE_GO`/`TM_RED_RELEASE`,
  zx-eth-main.c:198-199). Valid q = 0..7, ring = 0..1.
- The poll releases **every slot it advanced past** — invalid-BP descs included
  (`:8719-8730`, `:8832-8839`): two calls per (q,ring), sop=0 for non-SOP and sop=1
  for SOP counts.
- **grep-proven: this is the ONLY writer of 0x4064/0x4068 in the stock plat module**
  (and no writer exists in tm.ko/switch.ko/idmfdb.ko decomps). There is **no
  init-time credit seeding** — after reset a queue must deliver with no arming at
  all, or the whole stock RX path could never start. This kills every "stock arms
  q5's credits at WLAN time" variant.
- Contract (already RE'd in `napi_rxdesc_layout_verify.md:57-210`): HW maintains
  the two 16-bit pending counts in `TM[0x10100+q*4]`, SW maintains the cursors,
  the release ack keeps them consistent. No HW write-pointer, no queue enable, no
  per-queue DMA attach.

### 1.3 Generic TM/QMG init (all replayed by mainline already)

`pon_tm_dma_init` (`:6277-6301`) = mainline `zx_tm_dma_init` (zx-eth-main.c:4642-4670,
stock-dump parity incl. `DMA_CTRL 0x3f6564`, `0x10004=0x7f`, distinct UP/DN TX rings);
`pon_tm_red_init` (`:7235-7288`) = `zx_tm_red_init` (1168 queue cfgs, ram0 q0-15
guart 0x400); IRQ unmask `tm_base+0x104 |= 7` (`:6966`) = mainline TM IRQ arm. Nothing
per-queue-5 anywhere in the init chain.

---

## 2. What actually chooses the queue: CLA ram7 and its two write paths

### 2.1 The addressing decode (new)

`tm_protocol_pkt_limit_map_set(port, ptype, qid)` (`decomp_all_tm.c:40362-40400`)
computes the ram7 row and calls `cla_set_cpu_queue_id(row, qid)`
(`decomp_all_tm.c:3957-4023`; ram_id 7 indirect write, row ≤ 0x3ff, **qid ≤ 7
accepted** — qids ≥ 8 rejected; note the Phase-B session's "qid 7 clamps to 4" was a
property of the mainline debugfs helper, not of stock):

| port arg | row = ptype masked \| bank |
|---|---|
| 0 | `& 0xff \| 0x080` |
| 1 | `& 0x7f \| 0x100` |
| 2 | `& 0xff \| 0x180` |
| 3 | `& 0x7f \| 0x200` |
| 4 | `& 0xff \| 0x280` |
| **5** | **`& 0x7f` (base bank 0x000-0x7f)** |
| 6 | `& 0x7f \| 0x300` |
| 7 | `& 0xff \| 0x380` |

### 2.2 The two directions

`zte_api_pp_set_trap_queue(dir, ptype, qid)` (`decomp_all_tm.c:57882-57916`):

- **dir 0**: loops port = 0..7 **skipping 5** → writes qid into the 7 per-inport
  banks (including 0x300/0x380 = fabric/WLAN inports 6/7).
- **dir 1**: writes port **5 only** → the **base bank** 0x000-0x7f.

Caller: `chip_tm_init` (`decomp_all_switch.c:2505-2518`) walks the
`{ptype, qid_dir0, qid_dir1}` table (`DAT_00013cf4`, = mainline's
`zx_def_ptl_pkt_map`) calling **both** dirs per ptype, plus
`tm_protocol_pkt_limit_pps_set(0/1, 5, 1, 8000)` (an 8 kpps limit tied to queue-5
class traffic — note stock rate-limits this queue's protocol class explicitly).

ARP: `zx_pkt_map.h:38` = `{0x11, 5, 5}` — **queue 5 in both columns**. So on stock,
an ARP trap from ANY inport (wire, CPU, or fabric 6/7) is steered to CPU DN queue 5
and delivered through the ordinary machinery of §1. Queue 5 needs no WLAN-time
binding on stock because there is nothing to bind.

### 2.3 The mainline half-replay (a real, citable gap)

`zx_chip_tm_init_trap_queues` (zx-eth-main.c:4086-4109) replays **qid0 into the 7
per-port banks and skips port 5** — i.e. the **base bank is never written with its
qid1 column**. Before that, `zx_cla_apply_replay` blankets all 1024 ram7 rows with
qid=7 (`findings/fix_churn_red_dnbank_2026-07-04.md:53-60`). Net mainline state:
base bank = 7 everywhere, per-port banks = stock qid0.

The same churn-fix session **live-proved the base bank is consulted** for DN-trap
steering (blanket-rewriting it 7→6 instantly moved new DN-trap charges). So mainline
currently runs a ram7 whose base bank disagrees with stock (7 vs the qid1 column) —
harmless so far only because wire traps ride the boot-replayed **ram2 catch-all
`cpu_qid` overrides** (inports 1-5 → q7; see the Phase-B validation doc + memory
`zte-cla-ram-layout`), which take precedence and land in queues whose release cycles
are healthy.

### 2.4 Why the session's `clawrite 7 0x391 <qid>` re-steer didn't move the tick

Two decomp-grounded candidates (not resolvable device-free):

- **Bank-index space mismatch** ([[zte-port-numbering]]: every block has its own
  port index space). The SPA→SADM descriptor says `inport=7`, but ram7's bank index
  for that frame may not be "7" — the effective row could be `0x311` (bank 6), or the
  **base bank row 0x011** if ring-ingress frames are classified in the dir-1/base
  space. Only `0x391` was poked.
- **The frames may be UP-direction, not DN.** Evidence from the validation session
  itself: `qmg_dn_trap` (0x9234c04c) did NOT count the injected frames, and the tick
  appeared in `TM[0x10114]` **hi16** — which the stock-poll RE maps to the *first*
  drain block (`napi_rxdesc_layout_verify.md:175-186` calls hi16 the UP-ring count).
  If the ring-injected frames are UP-classified (CPU-side ingress, like LAN), the
  QMG **UP** hw_trap counter (0x9234c060) — never watched during the session — should
  have ticked instead, and the per-port (dir-0) banks are the ones consulted.

---

## 3. Stock's WLAN datapath: where the IDM RX ring really gets fed

- `sw_init_wlan_ssid` (`decomp_all_switch.c:5112-5144`) → `aclWLANToIDMEssidCfg2`
  (`decomp_all_tm.c:50175-50192`): **pure software** — fills
  `s_aclWlanToIdmEssidMap` (wlan_index → {idm port 6/7, essid}). No MMIO. (Confirms
  the Phase-B appendix-1 finding; this is stock's equivalent of our dispatch table.)
- `idm_fdb_recv_handle` / `wlan_recv_idm_handle` (`decomp_all_idmfdb.c:1-58,
  :529-586`): symmetric SW shuttles — look up the node, stamp `skb->dev`, call the
  target netdev's `ndo_start_xmit` (`*(dev+300)+0x10`). Gated by
  `ffe_get_npu_enable()`. No register writes.
- `idm_net_poll` (`decomp_all_plat_zxylzb_9128S.c:4020-4191`): drains the IDM RX
  ring — pending = `npp[0x804c] & 0xffff`, refund `npp[0x8048] = N | N<<16` after
  consuming N. `pon_npp_idm_init` (`:4340-4455`) seeds 2048 × `npp[0x8048]=0x10000`
  then `npp[0x800c]=0x4000800`. Mainline `zx_idm_init`
  (zx-eth-main.c:1580-1632) is register-faithful to all of this (re-confirmed).
- **Nothing anywhere routes a TRAP verdict into this ring.** The IDM RX ring is fed
  by the fabric's forwarding path when the egress decision is port 6/7 — which on
  stock happens once FFE installs WLAN flows (ssid plumbed through CLA/PM/FDB, per
  `findings/wifi_offload_feasibility_2026-07-04.md`). Slow-path/control WLAN
  traffic on stock goes wlan0 → SW bridge, never entering the fabric.
- The one WLAN-named greg knob, `greg_set_wifi_queue1_protocol`
  (`decomp_all_tm.c:22671-22692`), just zeroes greg regs 0x46/0x47
  (0x921c0090/94) — already poked to stock parity live and refuted.
- The IDM per-queue block `npp+0x8050..0x8064` (stock 0x08000000 ×6): **no writer in
  any of the four decomped modules** (the `pp_base+0x8050` / `tm_base+0x8058` hits
  are different blocks: PP-BRG interrupt regs and the BMU pool-size reg). Its
  stock value is either HW-reset default or written by a module we have not
  decomped (ffe.ko/hwnat). It was already poked live with no behavior change.

---

## 4. The queue-4/7-vs-5 delta, restated with the decomp in hand

| | q4 | q7 | q5 |
|---|---|---|---|
| stock consumer | CPU RX DMA (§1) | CPU RX DMA | CPU RX DMA — **identical** |
| stock steering source | ram7 qid0/1 = 4 rows (most ptypes) | ram2 catch-all `cpu_qid` overrides (live-verified) | ram7 `{0x11,5,5}` etc |
| per-queue arming register | none exists | none exists | none exists |
| mainline delivery | works (exercised since boot) | works (exercised since boot) | **never exercised by wire traffic**; dead when first exercised by Phase-B injection |

So the "consumer binding" the Phase-B hand-off asked for **does not exist as a
register**; what distinguishes 4/7 from 5 on mainline is only their runtime history
and (possibly) which status half/slice pairing they exercise. The dead-q5 mechanism
is therefore a mainline pathology among these candidates:

1. **Release/pairing skew.** Mainline pairs lo16↔slice-A(base)/`ring=0` and
   hi16↔slice-B(+0x20000)/`ring=1` (zx-eth-main.c:4838-4845, release at :5067-5071).
   The stock-poll RE (`napi_rxdesc_layout_verify.md:120,175`) pairs **hi16 with the
   FIRST drain block and release ring-bit=1**, whose desc pointer is the *other*
   struct field. If stock's true pairing is (hi16 ↔ slice A ↔ bit14=1), mainline
   scans the wrong slice for hi16 frames and acks the wrong bank — q4/q7 survive
   because their traffic pattern keeps the miscredited banks topped up, q5 (first
   touched by injection, on the hi16 side) starves immediately. The Iter-AD wedge
   fix (zx-eth-main.c:4790-4799) validated one pairing empirically but only for the
   lo16/ring0 path under wire traffic.
2. **Un-ACKed poison descriptors.** q5 slice-A slots 0-15 hold 16 boot-era descs with
   len=0; mainline's scan-forward skips them and — when a scan finds *no* valid
   desc — releases nothing (`scan >= TM_RX_DESC_PER_Q → break` with `slots=0`,
   zx-eth-main.c:4879-4882, :5067). Stock would have advanced past and released
   them (§1.2). If HW's free-slot accounting for (q5, that ring) already counted
   those 16 as outstanding, they are never returned. (16 ≪ 0x400 though — this
   alone shouldn't kill the queue unless the counter semantics are
   cursor-based rather than credit-based.)
3. **The byte-pair anomaly is the truth-teller.** The injected burst moved
   `TM[0x10114]` hi16 by `+N*0x101` (both bytes lockstep, e.g. 0xc0c0→0xcdcd for 13
   frames). Two 8-bit lockstep counters fit "(enqueued, discarded-at-dequeue)" — a
   consumer popping and dropping for want of a usable descriptor slot — and do NOT
   fit a healthy 16-bit pending count. Whatever state makes q5's hi16 read as a
   byte-pair while q7's reads as a count IS the delta; it is not writable from any
   register stock's init chain touches (we looked), so it is accumulated state.

**Ruled out by this pass:** ADM per-queue PPS policing (sits BEFORE RED/QMG — the
frames demonstrably reach and leave the q5 accounting, and mainline doesn't enable
ADM anyway); SADM; the IDM credit block (poked live, no change); IRQ_MASK bit4
(signaling only); `wifi_queue1_protocol` (poked live); any per-queue QMG register
(`qmg_*` decomp sweep: only global thresholds/trap-cfg/ram-depth exist,
`decomp_all_tm.c:32704-33036`).

---

## 5. Mainline fix shape

**Don't hunt for a queue-5 "enable" — none exists. Two-track fix:**

- **Track A (Phase-B unblock, small): steer WLAN-ingress traps to a queue that
  demonstrably delivers.** In order of preference:
  1. Add the missing **dir-1 replay**: extend `zx_chip_tm_init_trap_queues` to also
     write `qid1` into the base bank (`addr = ptype & 0x7f`), matching stock
     `chip_tm_init` exactly. (Stock parity; by itself only helps if the base bank
     is what ring-ingress frames consult.)
  2. **Re-steer the trap ptypes** the dispatcher cares about (ARP 0x11, and the
     0x1d/0x1f/0x20 qid-5 rows) to **qid 4** across ALL banks including base —
     8 `zx_cla_set_cpu_queue_id` calls per ptype. This sidesteps the dead queue
     entirely with zero new mechanism.
  3. The Phase-C-proper alternative: install **ram2 catch-all entries for inports
     6/7 with trap + `cpu_qid` override** (mirroring the boot-replayed inport-1..5
     entries that make wire traps deliver via q7 today; the clawrite/hashcalc
     machinery already exists). This is simultaneously the first concrete Phase-C
     deliverable.
- **Track B (correctness, medium): fix the CPU RX poll to the stock contract** —
  strict advance-by-1 with the pending count as budget (no scan-forward), release
  every advanced slot even when the desc looks stale (already half-done via Iter U,
  but the "no valid desc found" path still releases nothing), and settle the
  hi16/lo16 ↔ slice ↔ release-bit14 pairing against stock (see confirm list). This
  is what un-poisons q5 (and any future queue) rather than avoiding it.
- **Non-fix:** binding q5 to the IDM RX ring. Stock's IDM RX ring is a hw-forward
  egress target, not a trap sink; the Phase-B RX dispatcher will be fed by Phase-C
  (CLA/FFE entries whose egress = ports 6/7), not by trap delivery.

---

## 6. CONFIRM on the next stock-live / device session (targeted)

1. **Stock oracle for q5 (5 min):** on stock, put a STA on WiFi and have it ARP
   (or ping the router) while watching `TM[0x10114]` and both q5 slices — confirm
   q5 ticks AND delivers via the normal CPU rings with **no** WLAN-time register
   writes (the central negative claim of this doc). Also record which of hi16/lo16
   moves and which slice fills — this settles the pairing question of §4.1 with a
   healthy queue.
2. **Mainline re-steer oracle:** `clawrite 7 0x011 4` (base bank, ARP row) → inject →
   does the tick move to q4 and deliver? If not, walk the remaining banks
   (`0x091, 0x111, 0x191, 0x211, 0x291, 0x311`) one at a time — whichever row moves
   the tick identifies the bank index space for ring-ingress frames (and 0x311
   specifically tests the port-numbering-mismatch hypothesis for why 0x391 failed).
3. **Direction check:** during an injection burst, A/B `qmg` UP hw_trap
   (0x9234c060) and DN hw_trap (0x9234c04c), plus QMG sw_fwd (0x9234c044) — pins
   UP-vs-DN classification of IDM-ingress traps (§2.4) and closes the
   "qmg_dn_trap didn't move" loose end.
4. **Descriptor hunt at the byte-cursors:** after a burst, dump q5 slice A AND B at
   slots `hi16>>8` and `hi16&0xff` (the byte-pair values), not only around
   mainline's `rx_head` — rules the "desc written where mainline never looks"
   variant in or out.
5. **Credit-seed probe:** with traffic stopped, issue release doorbells for q5
   (`tm[0x4068] = ring<<14 | N<<4 | sop<<3 | 5`, all four ring/sop combinations,
   small N) then re-inject — if delivery starts, §4's credit-starvation variant is
   confirmed and Track B is mandatory.
6. **Stock WLAN-config write capture** (existing follow-up, still worthwhile for
   Phase C): kotrace/oracle the WLAN bring-up for CLA ram2 writes — expected result
   per this RE: none at config time; entries appear at FFE flow-install time.

## 7. Open questions (explicitly unresolved, do not guess)

- The exact semantics of `TM[0x10100+q*4]` per half (pending-count vs cursor pair)
  and the definitive hi16/lo16 ↔ slice-A/B ↔ release-bit14 pairing. The two prior
  RE notes disagree (`napi_rxdesc_layout_verify.md` §2 vs mainline's empirically
  validated Iter-AD pairing); only live check #1/#4 settles it.
- Which ram7 bank (index space) a fabric-port-6/7-ingress frame consults (§2.4);
  live check #2 settles it.
- Who writes the IDM per-queue block `npp+0x8050..0x8064` on stock (no writer in
  the four decomped modules; candidates: HW reset default, ffe.ko/hwnat). Low
  priority — poked live already with no effect.
- The origin/format of the 16 len=0 boot-era descriptors in q5 slice A.
- Whether `tm_protocol_pkt_limit_pps_set(dir, 5, 1, 8000)` (`decomp_all_switch.c:
  2512-2513`) — stock's 8 kpps limiter on the queue-5 protocol class — has any
  mainline analogue worth replaying once q5 delivers.
