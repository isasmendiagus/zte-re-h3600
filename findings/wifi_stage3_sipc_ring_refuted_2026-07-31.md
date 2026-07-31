# Wedge #2, session 2026-07-31f — SIPC→CPU "descriptor ring" REFUTED by full decomp RE; 0x921cc008 demoted to coincident symptom; SMCT pp_pmau init gap found+landed; wedge repro'd at inj=14.8k with the gauge at 0x777

Predecessor: `findings/wifi_stage3_wedge_topcrm_axiqos_2026-07-31.md` (§8 set this
session's task: RE the SIPC→CPU descriptor ring and make mainline drain it).
Memory: `zte-wifi-up-offload`.

## Executive summary

1. **The task's hypothesis is REFUTED.** A full static sweep of every stock decomp
   module found **no SIPC→CPU descriptor ring**: no DDR base/producer/consumer
   register exists anywhere in stock for SIPC, and **stock performs ZERO runtime
   SIPC accesses** (no ISR/NAPI/timer/per-frame code touches the block; the
   counters are read only by debug-shell commands). There is nothing to drain and
   no ack mainline could be missing. Stock's gauge stays low because **the charging
   event never happens on stock**, not because stock consumes anything.
2. **0x921cc008 is demoted from "the halt gate" to a coincident symptom** — three
   live falsifications this session (below), including a real wedge captured with
   the gauge at **0x777**, nowhere near saturation.
3. **One genuine init divergence found and landed**: stock `pon_npp_smct_init`
   writes **npp+0x10004 (SMCT `pp_pmau`, phys 0x921d0004) = 0xB**; mainline never
   wrote it (POR 0xA). Hidden in the decomp behind a Ghidra symbol collision
   (`*(tm_set_onu_mac + npp_base + 4)`, `tm_set_onu_mac` = module offset 0x10000)
   — which is why every previous parity audit missed it. Landed next to the other
   SMCT init writes in `zx_pon_npp_init` (zx-eth-main.c). NOTE: a live *poke* of
   0xB was tried in the 2026-07-31 probe session and did not prevent the wedge,
   but that test predates fix #1 (BP double-free) and was run mid-boot rather than
   at init — treat the init-time write as untested as a wedge fix, and as
   mandatory stock parity regardless.
4. **Wedge #2 remains OPEN.** It reproduced this session at **inj=14,799** on a
   time-warm (~1 h) but frame-cold box (first HW-forwarded frames of the boot).

## The RE result (static, decomp-wide — the full report)

### What SIPC actually is

- TWO identical 0x2000 instances at npp+0xc000 (0x921cc000) and npp+0xe000, each
  with **8 channels at 0x400 stride** (16 channels), ~50 config words per channel
  (+0x000..+0x2bc). Channel offsets +0x280..+0x2bf are an on-chip **packet-buffer
  window** — the boot-capture replay data literally contains a stale SSH frame
  from the stock capture session. SIPC = on-chip multi-channel packet FIFO /
  credit bridge between the CPU port and the fabric. NOT a DMA ring.
- The only SIPC write in all of stock: `pon_npp_sipc_init()` = `npp[0xc000]=0x11`
  (plat :2260-2267) — exactly what mainline does. The whole SW API is 2 bits:
  0x921cc000 bit0 `rx_en`, bit2 `cpu_up_en` (both OSes: 0x11, cpu_up_en=0).
- **No auto-discard / bypass / release knob exists in software.** Ctrl bit4 of
  the 0x11 image is never named or touched by any accessor in any stock module.

### Register decode (now in DATASHEET.md §SIPC/§SMCT)

- `0x921cc004` = eight 4-bit fields: [3:0]/[7:4] cpu_short_drop up/dn,
  [11:8]/[15:12] cpu_pkt_drop dn/up, [19:16] **sipc2cpu_aful_cnt_dn**,
  [23:20] ful_dn, [27:24] aful_up, [31:28] ful_up.
  Mainline idle reads 0x000d0000 = **aful_cnt_dn=13** (SIPC→CPU DN FIFO hit
  almost-full 13× during boot); stock reads 0.
- `0x921cc008`: **no stock reader or symbol exists** — the previous session's
  "three 4-bit gauges" have no name anywhere in stock. Boot image writes 0x844
  once (deaf → blind replay no-op).
- `sipc_desc_full_err`/`empty_err` are **SMCT** bits: 0x921d00d4 bit29/bit28
  (plus [27:16] bud_wrong, bit5 des_err); 0x921d0050 bit0 sipc_err;
  0x921d00d8 [9:0] smct_left_pmau; 0x921d0100 bit0 dma_up_err.
- `0x921cc044` read ≠ write: [3:0] sipc_2spa **sop**, [7:4] **eop**, [11:8]
  **sipc_drop** (live nibble gauges).
- `0x921cc184`/`0x921cc1c4` + n*4: DROP_HPMAU / DROP_AFUL ×11 ports, order:
  up_cpu, UNI0-4, PON0-1, SOAM, wifi0, wifi1.
- Per-frame rituals stock DOES do (all already mirrored by mainline): TM ring
  `soft_release_rx_desc` (0x92344064/68 handshake) and the IDM `npp+0x8048 =
  n|(n<<16)` / TX-reclaim kicks. Verified line-by-line identical in mainline.

## Live falsifications of the 0x921cc008 saturation model (this session)

All on a fresh RAM-boot of the A09 build (default OFF ftwifi, bare rig at first):

1. **Fresh boot, ZERO HW-forwarded frames**: gauge already at 0xeee within
   ~20 min of boot from background LAN/WAN chatter alone; reached **0xfff at
   idle** — and the box kept working (dn_trap moving under host ping, CPU TX
   egressing, REPL fine). **Saturation ≠ halt.**
2. The gauge **drains on mainline too**: fff → 888 → 777 → 555 observed across
   idle periods and rig-up. Not a monotonic leak. Insensitive to pure RX-trap
   traffic (pinned at 777 through +51 trapped frames); moved around TX/flow
   activity in BOTH directions.
3. **A true wedge fired with the gauge at 0x777** (cold-start tracer run, this
   boot): up_fwd froze at 0x39c7 / red_in froze at 0x55ae at inj=14,799, ~40 s
   into a ~1 MB/s phone→WAN HW-forwarded flow (up_fwd was +2.2-2.4k/round for
   7 rounds, then collapsed mid-round r8; the gauge stepped 666→777 AT the
   collapse round, not before). The step is **coincident, not causal**.
4. All 16 per-channel status regs (0xc008 + n·0x400, both instances) read
   **identical** (0x00888011) on the wedged box — the reg is aliased/global;
   the leak is not localizable per-channel.

Post-freeze state (from the tracer + wedgecap): dn_trap and acl_fail still
creep (+1..+15/round — trapped chatter and missing lookups continue), sipc_044
sop/eop nibbles still cycle, BMU ledger balanced (alloc−rls = −11), RED rid0
static config, qmg_up_* = 0, mac2_tx frozen. Same "resource absent, everything
accounts healthy" signature as before. inj also froze (TCP stall upstream —
the phone stops sending when forwards die).

## Where this leaves the wedge hunt (hypothesis, updated)

The sipc2cpu_aful_cnt_dn=13-at-idle datum + the Phase-B "QMG DN queue-5
consumer unbound" precedent suggest the shape: **some frame class on mainline is
steered into a CPU-bound SIPC/QMG path that has no configured consumer**, its
FIFO backs up (aful events), and under sustained load a shared fabric resource
exhausts → chip-wide MAC→RED admission halt. Stock never charges that path
(0xc004=0 on stock). The divergence generating the enqueues is OUTSIDE SIPC
(config is byte-identical) — prime suspects per the RE: trap-queue/transport
steering for fabric-ingress trap classes (ram7 rows / dead-queue pattern) and
UP CLA/PM action bits. Also still unexplained: ram7 base rows reading qid=4
on this build vs the documented blanket qid=7 (flagged last session).

## Landed this session

- `NPP_REG_SMCT_PP_PMAU` (npp+0x10004) = 0xB written at init in
  `zx_pon_npp_init` (zx-eth-main.c, next to SMCT_INIT_0/1) — build OK
  (zImage_dtb.uimg 16.4 MiB; slotA padding step fails >12 MiB as known,
  harmless for RAM-boot).
- DATASHEET.md §SIPC rewritten (block structure, full 0xc004/0xc044 decode,
  0xc008 demotion note, DROP_HPMAU/AFUL tables) + new §SMCT error/status table
  + pp_pmau stock-value annotation.

## Session gotchas (rig)

- A bare `reboot_mainline_wifi.py` boot has **all DSA lan ports DOWN**; the IP
  on the conduit `sw` cannot ping/be pinged (RX demuxes to a down lan port and
  is dropped silently — netdev RX counts climb, IP InReceives stays 0). This
  looked exactly like a wedge/corruption for ~30 min. Bring the rig up first;
  the host-ping wedge discriminator is only valid with lan ports up (dn_trap
  delta remains valid regardless).
- The kernel clock runs ~4.5× wall time on these RAM-boots (dmesg timestamps
  vastly ahead) — separate anomaly, undiagnosed, noted for timer-related work.
