# Fabric-ingress endurance wedge — the BMU BP-pool session (2026-07-31): TWO real bugs found+fixed (BP double-free; pm_ext wiping the BPPE table), pool-drain REFUTED as the gate, wedge #2 characterized to a hard wall

Session goal (task): read the BMU BP-pool depth (`0x92348048` lo16, 5
instances @0x400) live through a HW-forward wedge repro; if it drains →
fix the BP-return path; if flat → refute and push the next thread — carried
through to "fix the wedge for good" by coordinator extension.

## Executive summary

1. **The decisive read as specified is impossible**: `0x92348048` lo16 reads
   0 on mainline always (write-deaf, HW-owned cursor). The REAL pool gauges
   (from stock's own `dump_bmu_reg` labels) are `0x92348080` = **bppe bpcnt**
   (DDR free-list level) and `0x92348088` = **bppi bpcnt** (on-chip prefetch
   FIFO level).
2. **Pool-drain is REFUTED as the wedge gate** — twice over:
   - The BMU alloc/release HW ledger (`0x8090`/`0x8098`, counts HW events —
     verified: tracks MAC-ingress frame counts) is **balanced at wedge onset**
     (constant boot offset −16, zero drift through the run).
   - The pool level is **zero from boot on mainline** (vs stock 8112+79) — a
     pool that is always empty cannot "drain to empty at onset". eth
     HW-offload runs 12 GB in this state; the fabric survives on a ~15-entry
     BPPI recycle margin for eth paths.
3. **Wedge bug #1 FOUND + FIXED (commit bcee9471f)**: the TM RX consume path
   **double-freed the BMU BP** in two drop branches (DSA-invalid-ingress and
   loopback-suppression each called `zx_bmu_free_bp`, then the common
   per-descriptor release freed the same `bppe_idx` again). **Live proof:
   ledger drift == `tm_rx_loopback_drops` EXACTLY (149 == 149) at the
   captured wedge.** Duplicate BP indices in the free ring → one buffer
   handed to two in-flight frames → the garbage-gkey / raw-HTTP-in-parser
   corruption signature, probabilistic long-fuse onsets (0.9k–72k), and the
   full chip-death flavor. Post-fix: corruption signature GONE (gkey latch
   holds a clean frozen key at wedge), and the wedge-collapse no longer
   kills the whole chip the same way.
4. **Wedge bug #1b FOUND + FIXED (commit e82c6c385)**: the July DN-offload
   change `zx_ft_pm_ext_init` memset the full 0x520000 carve at 0x4E700000 —
   **the first 0x20000 of that carve is the BMU BPPE free-list table**
   (+ jumbo table at +0x10000) that `zx_tm_alloc_pools` fills earlier in
   probe. Every boot since July silently wiped the pool table. Fixed: zero
   from +0x20000 only (no FT offset ever touches the head: ACL +0x20000,
   flow_info +0x41C000/+0x49C000).
5. **Wedge #2 remains OPEN** — a distinct, faster, apparently deterministic
   failure (onsets 967 and ~965-into-flow on consecutive repros) that still
   gates `ftwifi` default-ON. Characterized to a hard wall (below).

## The 0x92348048 answer (the task's THE QUESTION)

Does the free-BP count drain monotonically toward 0 at onset? **NO — it
never moves at all.** `0x8048` lo16 = 0 at baseline, mid-run, and onset (all
5 instances; hi16 also 0). The real gauges: `bppe_cnt` 0 → 0 → 0;
`bppi_cnt` ~15 steady; HW alloc/release ledger balanced (drift −16 constant
through 30+ bursts, both pre- and post-fix builds). Verdict per the task's
own fork: **refuted → next thread**.

## Bug #1: the BP double-free (the corruption amplifier)

- `zx-eth-main.c` TM RX consume: branches at (pre-fix) :5487 (DSA invalid
  ingress) and :5505 (loopback suppression) called `zx_bmu_free_bp(e,
  bppe_idx, 0)` AND fell through to the common release at :5600 → two
  `tm[0x8010]` free-writes for one BP.
- Captured live on the wedging run (pre-fix build #542): ledger drift grew
  −16 → −165 across 31 bursts; `tm_rx_loopback_drops` = 149 = the drift
  delta. One duplicate free-ring entry per hairpinned CPU-egress frame.
- Explains the historical wedge statistics: single-flow runs (1-2 hairpins)
  lasted 19.6k–71.8k; fresh-connection-per-burst shapes (≈5 hairpins/burst)
  died at 0.9k–5.1k; the eth 12 GB endurance (rig.py warms ARP → ~0
  hairpins) never wedged; the 141k SW control (single flow) was clean.
- Also new that session: a pre-fix wedge fired with ZERO fabric injections
  (idm1 down → the UP rx_handler gate `IFF_UP` failed — wifi_up.py binds but
  never ups idm1) on ~11.7k DN HW-forwards + 174k SW UP frames + 149
  hairpin double-frees.

## Bug #1b: the pm_ext BPPE wipe + BMU priming parity (landed, pool still unprimed)

Also landed in e82c6c385 + the follow-up build:
- Bulk stock-replay walker now SKIPs base-window 0x188000..0x1891ff (86 ops)
  — the captured table replayed the BMU block's RUNTIME state (HW-owned
  cursors, status regs, INIT=1 enables) before `zx_tm_bmu_init` ran, so the
  virgin engine was first enabled with an empty producer.
- `zx_tm_bmu_init` now primes `0x8048`/`0x804c` ONCE (instance 0 only —
  stock parity: the 5 instances mirror one engine; stock's replay never
  writes 0x8048 per-instance) and advertises a real jumbo pool (0x66
  entries, table at bppe+0x10000, `0x805c`=(0x66>>5)−1) instead of an empty
  one.
- **Open anomaly**: even with a virgin-block 0→1 enable + full written-value
  parity (verified reg-by-reg vs the stock 2MiB live dump: ctrl, buckets,
  bases, sizes all byte-identical), mainline's `bppe_cnt` stays 0. Every
  live re-prime variant refuted: 0x8048/0x8044 writes are deaf, 0x80dc
  bit30 is RO status, bucket-count 0x100-vs-0xff irrelevant, dc-write +
  INIT toggle no-op. Production's trigger is environmental (untraced) —
  next lead: boot STOCK live and re-prime there to learn the preconditions.
- Stock-vs-mainline full BMU block diff (0x92348000-0x923480fc) captured in
  this doc's session log; mainline-only nonzero "distress" regs at idle:
  0x8050=8, 0x8054=0xa, 0x80d4=0x200, 0x80e0=0xfb1, 0x80e4=0x3b0 (all 0 on
  stock) — undecoded, likely starvation-event counters.

## Wedge #2 — the remaining bug (OPEN, the hard wall)

Repro: throttled continuous phone→WAN upload via AP + ftwifi=1 + idm1 up
(UP fabric-injection HW-forward active, DN ACK HW-forward active). Two
consecutive true wedges at **967** and **~965-into-flow (inj 2069→3034)**
injected frames, both during retransmit-heavy windows (the WAN modem-WiFi
leg flaps under load; endur2.py now auto-discriminates modem flake vs true
wedge via Δqmg_dn_trap under host ping — the flake self-heals in 1-4 min
and previously false-alarmed the burst harness).

Signature at onset (all captured live, post-fix build):
- MAC2 RX-ok **counts** arriving frames (+10 for 10 pings) but
  `red_trp_in`/`qmg_dn_trap`/SPA all **frozen** → frames die between MAC
  admit and RED-in. Chip-wide (all ports).
- CPU TM-TX transmits (tx_count climbs, no drops, BP allocs succeed) but
  frames never reach MAC egress (`mac2_tx` frozen) → fabric core dead in
  BOTH directions.
- IDM TX ring alive (fabric consumes, STATUS moves); injected frames
  vanish pre-CLA (up_fwd frozen, acl_fail climbs only slowly, gkey latch
  frozen with a VALID well-formed key — the corruption flavor is gone).
- **Every readable accounting bank healthy at onset**: BMU ledger balanced;
  RED indirect ALL ram-ids swept — rid1 (used_space) all ZERO, rid0 =
  static config 0x400(=1024 cap)/0x800400, rid2 = static 0x200020, rid3
  zero; QMG dn in/out balanced; qmg_up_* zero; SIPC/parse gauges wandering
  healthily; tm_irq bit3 (UP-ring dma_des exception) NOT set.
- Recovery: reboot-only. The July eth-wedge ram7 trap-queue re-steer
  (blanket base bank → qid6, incl. row 0x391, double-write) does NOT
  unwedge this one. (Note: ram7 base rows read qid=4 on this build, not
  the documented blanket 7 — undiagnosed side observation.)

Interpretation: a fabric-core arbiter/stage halts on a resource **no known
register exposes**. It is specific to forwarding that crosses fabric ports
6/7 (WiFi/IDM): eth-only HW-forwarding at 8.6M+ frames never wedges; every
wedging run had port-6/7 traffic. The RED charge-accounting family (the
proven eth-churn mechanism) is exonerated for this one (charge accounting
is disabled by the [red-arm] fix and all levels read zero).

## Next concrete steps (for the follow-up session)

1. **Stock reference experiment**: boot stock (NAND slot B), drive WiFi
   AP traffic (stock forwards ports 6/7 indefinitely), capture the same
   BMU/QMG/RED/SIPC gauge set under load; then live re-prime stock's BMU
   (INIT=0 → prime → INIT=1 via devmem) to learn what production requires.
   Diff against mainline's dead-production state.
2. **Per-stage vanish localization**: `0x921cc044` (SIPC→SPA handoff
   counter) + the undecoded mainline-only BMU distress counters
   (0x8050/0x8054/0x80d4/0x80e0/0x80e4) sampled through a repro — find the
   FIRST counter that stops/steps at onset.
3. Rate-dependence: the phone's background chatter (2068 sparse injections)
   never wedged; the ~1MB/s flow dies at ~1k. Same volume at 1/10 rate.
4. The `0x8044` cursor (stock 0x00500001, mainline 0, no stock writer —
   HW-maintained) — decode via the stock re-prime experiment.

## Tooling delivered

- `scratchpad/wedge_probe.py`: `bmu` one-shot (pool cursors + ledger, all 5
  instances), BMU regs in `lite_sample`, `red_ramid_sweep` (all-bank RED
  indirect), extended `wedgecap` (BMU + full QMG/RED + rid sweep).
- `scratchpad/endur2.py`: throttled continuous-flow endurance with the
  modem-flake vs true-wedge auto-discriminator (Δqmg_dn_trap under ping),
  flow auto-restart, BMU/RED per-round telemetry.
- Build-pipeline note: `/tmp/initramfs_extract` (CONFIG_INITRAMFS_SOURCE)
  can vanish on host /tmp cleanup — restore with
  `sudo cpio -idm < build/usr/initramfs_data.cpio` into it (the packed
  archive of the last good build survives in build/usr/), then
  `build_slotA.py` (its final slotA padding step fails >12MiB — harmless
  for RAM-boot; tftp/zImage_dtb.uimg is produced before it).
- Rig gotchas fixed/annotated: wifi_up.py never ups idm1 (UP injection
  silently off — `ip link set idm1 up` after bind for UP-offload tests); a
  stale host route `192.168.50.10 via 192.168.1.1` hijacked the phone's
  return path (delete it).

## Device end state

Rebooted clean on the fix build (#542+fixes), no rig, ftwifi=0 (default
OFF, kzalloc-zero verified), UART bridge REPL live.

---

# ADDENDUM 2026-07-31d — STOCK-LIVE experiment done: the BMU **engine** is dead on mainline (not a missing register value); wedge #2 mechanism now coherent

## What the stock-live experiment settled (READ-ONLY stock boot, SSH+devmem2)

Live stock BMU block (under normal stock operation), vs live mainline:

| reg | stock LIVE | mainline LIVE | note |
|---|---|---|---|
| 0x8048 bppe ptr | **0x50** | 0 | engine cursor (lo16=read) |
| 0x8044 | **0x500001** | 0 | HW-maintained, no stock writer |
| 0x8040 bppi ptr | 0x880039 (moves) | 0xfb00ec (moves) | both alive |
| 0x8080 **bppe bpcnt** | **0x1FB0 (8112)** | **0** | the DDR free-list level |
| 0x8084 | 0x16 | 0 | |
| 0x8088 bppi bpcnt | **0x4F (79)** | 0xa–0xf | on-chip FIFO level |
| 0x808c | 0x4F | 0 | |
| 0x8050 / 0x8054 | 0 / 0 | 8 / 0xa | mainline-only |
| 0x80d4 | **0x200** | 0x200 | **NOT a divergence** (the 2MiB text dump misled) |
| 0x80dc bp stat | 0x40000111 | 0x00000111 | bit30 = RO engine-ready-ish |
| 0x80e0 / 0x80e4 | **0 / 0** | 0xfb1 / 0x3b0 | mainline-only, climb with traffic |

**Decisive result — SW cannot prime the pool, not even on stock**: the exact
sequence `INIT=0 → 0x8048=POOL<<16 → INIT=1` executed on a live healthy stock
box left `bppe_cnt` at 8112 and `0x8048` at 0x50 — **unchanged**. The cursor
and level are **engine-maintained, SW-write-immune**. So mainline's zeros are
NOT a missing/incorrect register write (full written-value parity vs live
stock is verified reg-by-reg), and the whole "find the missing priming poke"
thread is CLOSED as refuted.

## Where the pool actually dies on mainline (new, localized)

- The BPPE free-list **is correct in DDR**: `memdump 0x4e700000` on mainline
  shows the be16 ramp 0,1,2,3,… intact (also confirms fix #1b holds — before
  that fix this region was zeroed every boot). Cache-flush theory (stock's
  `dma_cache_maint(bppe, 0x20000, 1)` vs mainline's bare `dma_wmb()`)
  therefore also **refuted**.
- **The DDR→chip prefetch engine never runs**: driving the alloc-kick
  (`0x8014=1` ×4) on mainline **drained the on-chip FIFO 10 → 6 and never
  refilled** from the valid DDR list. `0x80a0` (bp initsat) writes + enable
  re-toggle: no effect.
- Config regs latch fine (ctrl/bases/sizes/buckets all read back stock-exact)
  while every *engine* register (cursor 0x8048/0x8044, levels 0x8080/0x8088
  refill, prefetch) is inert ⇒ **the BMU's engine is unclocked / held in
  reset on mainline, or was never released by the correct first-enable
  window** — a top_crm/sys_ctrl clock-reset question, NOT a TM-register
  question. That is the next thread (new RE surface: top_crm map).

## Wedge #2 — coherent mechanism (fits every observation)

With no DDR pool, the chip runs on the tiny on-chip BPPI recycle margin
(~10–15 BPs) which is replenished almost entirely by the **SW free path**
(`tm[0x8010]`, `zx_bmu_free_bp`, once per CPU-consumed RX descriptor).
- **HW-forwarded frames never take the SW free path** → each one leaks a BP
  from a ~15-deep margin → starvation halt after ~1k frames. **Matches the
  measured post-fix onsets exactly (967 and ~965).**
- At starvation: MAC RX-ok still counts (the MAC is outside the BMU) but
  nothing can be *admitted* into the fabric → `red_trp_in`/SPA/qmg frozen,
  frames die precisely **between MAC-admit and RED-in** (the observed
  signature); CPU TX also dies (needs a BP to allocate) → **core dead in
  both directions**; every accounting bank reads healthy because nothing is
  over-charged — the resource is simply absent. Reboot-only because the
  engine never produces.
- Explains the survivors: eth-only HW-offload runs 12 GB fine because the
  trap-all DSA-conduit architecture sends eth ingress to the CPU, which
  SW-frees every BP; the 141k-frame SW control was clean for the same
  reason; and WiFi UP/DN fabric forwards (ports 6/7) are the ONLY traffic
  that consumes BPs without ever returning them.
- Consistent with bug #1 too: on a ~15-BP margin, a *double*-free (adding a
  phantom BP) was catastrophic in a different way — corruption rather than
  starvation.

## The wall (precise) + next step

**Wall**: making the BMU engine produce its DDR pool is not reachable through
any TM/BMU register — proven on both stock (SW writes immune) and mainline
(every parity write + kick + initsat + enable-toggle inert). The gate is
outside the block we have mapped/RE'd.

**Next step (ordered)**:
1. RE the **top_crm / sys_ctrl clock+reset map** for the TM/BMU sub-block
   (`pon_base`/`top_crm_base`/`sys_ctrl_base` are already iomapped by the
   PON node; stock's `zx_pon_clk_reset()` + `pon_reset` are the entry
   points) and release/strobe the BMU engine before `zx_tm_bmu_enable`.
   Success signal = `bppe_cnt` goes ~8112 in the boot log line already added.
2. Independent of (1), a **software mitigation is now well-defined and
   testable**: make the HW-forward path return BPs. Either find the fabric's
   BP auto-return enable, or (pragmatic) keep a CPU-visible accounting of
   fabric-forwarded frames and issue matching `tm[0x8010]` frees — but note
   the BP index of a HW-forwarded frame is not known to SW, so this likely
   needs the fabric-side enable, not a SW loop.
3. Stock gotcha found the hard way: **writing TM 0x92340128/0x130 on a LIVE
   stock box kills the datapath instantly** (box went unreachable mid-test;
   recovered by power-cycle — read-only NAND, nothing lost but the tmpfs
   capture). Do not strobe TM IRQ-enable regs on a running box.
