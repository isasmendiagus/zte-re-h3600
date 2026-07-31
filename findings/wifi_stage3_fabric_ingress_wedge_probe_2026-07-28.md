# Fabric-INGRESS wedge — ON-DEVICE probe session (2026-07-31): fork verdict CORRUPTION-primary; ALL named candidates refuted; wedge is volume-triggered, SW-free, and halts the MAC→SPA ingress front-end chip-wide

Executes the verified probe plan of
`findings/wifi_stage3_fabric_ingress_wedge_candidates_VERIFY_2026-07-28.md`
(and its source doc) on the live H3600. Four wedge reproductions across four
RAM-boots of build #542, each with full signature capture. Net result: the
probe was decisive — **`tx_pending` FLOWING (the fork verdict) + every
admission gauge clean ⇒ corruption-side primary** — but every *named*
candidate mechanism (1a, 1b, 2, 3-as-SW-collision, 4, 5) is now refuted by
direct measurement, including the one fix candidate we could try
(`0x921d0004=0xB` stock parity — applied live, wedge still fires). The wedge
is reproducibly triggered by nothing but sustained fabric-ingress HW
forwarding itself, and its end state is a **chip-wide ingress front-end halt
(MAC→SPA admit dead on ALL ports, frames vanish before every readable
counter)**. Root cause remains OPEN; `ftwifi` stays default OFF (verified:
`ft_wifi_en` is kzalloc-zero, no explicit set).

## Reproduction statistics (onset in injected fabric-ingress frames)

| boot | traffic shape | onset (tx_injected) | notes |
|---|---|---|---|
| A (probe run1/run2) | 3MB bursts, fresh TCP flow per burst | ~5.1k | wedge hit at flow ~#3's start (dinj=17 into the burst) |
| B (endurance, parity poke 0x921d0004=0xB applied pre-traffic) | 8MB bursts | ~2.4k | **parity fix REFUTED** — burst 1 clean (2346 fwd 1:1), died at burst 2 start |
| C (discrim phase0) | 1 throttled continuous flow | ~0.9k | WAN leg degraded (retransmit-heavy) — earliest onset seen |
| D (discrim reordered, hands-off) | 1 continuous flow ~1.25 MB/s, ZERO SW ops after the single flow-start install | **~32k** | in the historical 19.6k–71.8k single-flow window |

Historical (2026-07-28): 19.6k / 22k / 71.8k — all single continuous flows.
Pattern: single-flow onsets 19.6k–71.8k (now +32k); flow transitions /
retransmit-heavy shapes correlate with much earlier onset (0.9k–5.1k) but are
NOT required. Volume/duration of fabric-ingress forwarding alone suffices
(boot D is the proof: no hashcalc, no fttest, no gkey reads, no
install/destroy beyond the initial hardfast install, counters-only sampling —
still wedged).

## The fork verdict (the VERIFY doc's primary discriminator) — measured twice

At wedge, every time:
- `e->tx_pending` = 13–43, **far below IDM_TX_POOL_LIMIT 0x200, still
  moving** — and `IDM_REG_TX_STATUS` (0x921c8044) done-count tracks it 1:1
  (0x19→0x1c→0x2b while pend 25→28→43). The fabric-side ring consumer acks
  every injected frame. **⇒ NOT an admission wall; candidates 1/2 (and 5)
  refuted as mechanism; corruption primary (candidate-3 branch).**
- Post-wedge, injected frames still transit the CLA and MISS 1:1
  (`cla_acl_fail` +15 for +15 injected, `cla_up_fwd` frozen).

## Candidate-by-candidate refutation (all live-measured)

| candidate | measurement | verdict |
|---|---|---|
| 1b SMCT `0x921d0004` parity gap (POR 0xA vs stock 0xB — REAL, confirmed on 2 boots) | poked 0xB (readback-verified) pre-traffic on boot B → wedge at ~2.4k frames anyway | **refuted as the fix** (parity gap remains a cosmetic divergence) |
| 1 SIPC saturation | `0x921cc004` stepped 0x80000→0xE080000 in one wedge; stayed flat 0x70000 through another | not consistent → not the trigger |
| 1b SMCT free-level/doorbell 0x921d0040/4c | wander healthily through wedge (0x8181→0xb5b5→0xcbcb), mirror lo8==hi8; also move with plain eth CPU egress on mainline | exonerated |
| 2 BMU/RED occupancy | `tm_bmu_free_ok` advances, `fail`=0; **FULL ram1 sweep (rows 0-15, 0x10-0x4f, (40+p)*8 — the VERIFY-corrected row set) reads all-zero at wedge, twice** | exonerated |
| 3 as SW/HW collision (install/hash-engine/debugfs racing lookups) | boot D wedged hands-off with zero SW ops; separately phases A (20× hashcalc under traffic) and B (8× fttest install/destroy under traffic) never got to run before C wedged — but C alone refutes the *necessity* of any SW op | **SW interference NOT required** |
| 4 SADM/ADM/DPA never initialized | live diff vs stock 2MiB dump: **all 17 candidate regs byte-identical to stock** (0x92384000=0x21, one_second=200e6 both blocks, ADM q0/q5=0x201f40, DPA 0x10c0/0x1f) — the driver's stock-replay covers them (the queue_subsystem doc's "mainline writes nothing" was about explicit code only) | **refuted — no config gap exists** |
| 5 IDM reclaim stall | see fork verdict | refuted |

## Post-wedge forensics — where frames actually die

- **MAC-ingress (all ports): dead at the very front.** 20 host pings into
  lan4 (uni4/RGMII): `SPA_rcv` frozen, `red_trp_in`/`pp_drop`/`sadm_*`/
  `qmg_dn_trap` all frozen — the frames increment NOTHING readable. ARP
  neigh entries go FAILED on the device; WAN-ingress trapping is dead
  (this is also the practical wedge discriminator vs modem flake:
  Δ`qmg_dn_trap`=0 under host ping = wedge).
- **CPU-inject ingress: still admitted, still looked up — but the parse is
  garbage.** `gparsehashkey` latch shows degenerate keys: `45000000 …` (raw
  IPv4 bytes where the key header should be) alternating with
  `38000000 0 0 …` (correct UP key_hdr byte, EMPTY tuple). The staging
  window at 0x9238c200 read back a raw HTTP header fragment
  ("…USER-AGENT: Chromium/140…") — payload bytes at a parse-window offset.
  The CLA engine itself still cycles (lookups complete, they just miss).
- **The asymmetry (MAC admit blocked / CPU-inject parsed-wrong) is the
  sharpest remaining mechanism clue**: whatever hangs is between MAC admit
  and the key extractor — a descriptor/buffer stage shared by all ingress,
  in which CPU-injected frames take a partially-different path.
- Everything else frozen: all QMG groups, RED in/out counters, TM q4/q5
  status. Note for future probes: wifi-UP forwarded frames count in the
  **DN** QMG/RED groups (`qmg_dn_hw`≈`red_fwd_in`≈ total forwards;
  `qmg_up_*` stay 0 for this path).

## Observables RETRACTED by healthy-box controls (do NOT chase these)

1. `hashcalc` reference key (11..cc) returning **0x5ed3** — identical on a
   fresh healthy boot. The driver comment's 0x4a15 dates from an older
   poly/outspace config; 0x5ed3 is the correct current answer. NOT
   corruption.
2. Hash trigger `0x9238c2c0` parking at **1** after compute (DATASHEET's
   "reads 0x3 idle" is stale for this config) — same on healthy boot.
3. `0x9238c2f0` (12th key word) reading 0 after hashcalc / odd write
   behavior — same on healthy boot (weird semantics, not a lock).
4. TM IRQ STATUS `0x92340100` bit4 (dma_des_int[1], per the field map
   [2:0]=queue/[4:3]=dma-des/[15:8]=fifo recovered from
   `tm_pon_tm_reg_initial`'s setters) — **set on healthy mainline from boot,
   never W1C-clearable in either state**. Stock-live reads 0 (benign
   divergence note). Useless as canary.
5. The parse-window pointer group `0x9238c290..c29c` — live-wandering
   gauges (change between consecutive reads), not restorable config.

Recovery attempts on a wedged box (all failed, reboot-only confirmed):
trigger clear/force-idle, key-reg rewrite, stock `pon_pp_cla_init` replay
(0x9238c080=0x1000→0x600, 0x9238c084=2 pulse and variants), c290-group
rewrite, TM irq W1C. (RED release-poke family was already refuted in the
churn-wedge work; ram1 is all-zero here anyway.)

## Why this should still be fixable (the stock existence proof)

Stock HW-forwards WiFi via the SAME fabric ports 6/7 / IDM ring at high
volume indefinitely (the whole Stage-3 offload design is based on that
finding). So a real config/behavior delta MUST exist. This session
eliminated every delta our RE has named so far — what remains unexplored:

1. **TM DMA-descriptor engine RE** — the [4:3] dma-des int pair, the TM
   0x10000-block error/status regs beyond what `mem`/`stats` print, and
   what descriptor refill/recycle stock's (still-unRE'd, import-thunk-hidden)
   CPU→fabric submit does that `zx_idm_xmit` doesn't. The front-end-halt
   signature (admit blocked chip-wide) smells like descriptor/buffer-pool
   starvation in a stage none of our counters name.
2. **The `0x9238c280-0x29c` gauge trace**: capture healthy-mainline values
   during a flow every ~2k frames (they are live parse-pipeline
   pointers/levels; stock-under-traffic read fc/5b/18/3d, wedged-mainline
   f8/02/12/0c) — a monotonic drain toward wedge would finally name the
   leaking resource.
3. Rate-dependence: same volume at 1/10th rate — does onset scale with
   frames or with time?
4. IDM descriptor recycling details: mainline reuses ring slots with
   `IDM_TX_POOL_LIMIT` 0x200 gating; whether the FABRIC side of the IDM
   ring needs a per-frame buffer return that stock issues from the hidden
   submit path is exactly the still-open smct/1b-shaped question — but now
   scoped to the IDM (0x921c8000) block, whose registers beyond
   CTRL/STATUS/KICK are undecoded.

## Tooling added/fixed (this session)

- `scratchpad/wedge_probe.py` — the whole probe kit: `run` (chunked-burst
  reproduction with wedge auto-capture), `endur` (fix endurance),
  `discrim` (phased SW-collision discriminator, C-first), `sample`/`ram1`/
  `wedgecap` (paced gauge rounds, full RED ram1 indirect sweep, fork-verdict
  capture). All device I/O via ab_ctrs pacing (console-safe under traffic).
- `scratchpad/reboot_mainline_wifi.py` — REPL-detection bug FIXED:
  `run_uboot_seq()` stops its log pump on return, so the "REPL ready"
  marker wait was polling a file nobody wrote to (BOOT_FAIL on good boots,
  ~4 min wasted per retry). The script now keeps its own `uart.log_loop`
  pump alive during the marker wait. Validated on a live boot (BOOT_OK).
- Boot-time flakes root-caused during the session: host in.tftpd not
  running (restart command is in CLAUDE.md), and the known stuck-USB-NIC /
  duplicate-.50 storm (`findings/wifi_sta_reverify_2026-07-05.md`).
- Wedge-vs-modem-flake discriminator reconfirmed: Δ`qmg_dn_trap` under
  host ping (frozen ⇒ wedge; the modem-AP leg's post-reboot recovery
  transient otherwise looks similar from the host side).

## Device end state

Fresh RAM-boot of build #542, fabric healthy, NO rig configured (no wifi
modules loaded, ftwifi=0, idm1 down, lan4 unconfigured), UART bridge REPL
live. Host: in.tftpd running on 192.168.1.50:69; return-route
192.168.50.0/24 and :9099 sink rules cleaned (no iptables DROP added this
session); adb phone still associated to nothing (AP gone with the reboot).
