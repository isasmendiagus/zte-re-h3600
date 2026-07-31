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

---

# ADDENDUM 2026-07-31 (same session): the DECISIVE discriminator — HW-forwarding is REQUIRED; injection alone is harmless

## The control run (modem-independent, WiFi → LAN2 egress)

Rig: phone → AP(wlan1) → idm1 → fabric → **lan2** (device) → host 192.168.1.50,
`ftwifi=1`, nft flowtable on lan2, no WAN/modem in the path at all.
(Cabling note: the DSA port names are 0-indexed — the host's physical LAN3
cable is device **lan2**, LAN1 is **lan0**; `lan4` is the WAN/RGMII port.
Getting this wrong costs a whole debug cycle: `lan3` links UP and pings
nothing.)

Observed: the FT entries installed and were destroyed normally, but the flow
**never HW-forwarded** — `cla_up_fwd` AND `cla_dn_fwd` both flat, `acl_fail`
climbing ~2× injections. Cause is a known-shaped gap, not a new bug: for
fabric ingress the `up_idx_fix` cmd_flow_id repack (idx=pm_slot) is applied
only when `eg_regport == ZX_WAN_REGPORT` (zx-eth-main.c ~:3330), so a
fabric-ingress→LAN-egress entry is packed the old DN way and can never match.
**WiFi→LAN HW-offload is therefore an unimplemented path**, separate from
this wedge.

That accident produced the cleanest possible control: **the same fabric
INJECTION volume through the identical `zx_idm_xmit` path, with NO CLA
HW-forward match** (frames trap to the CPU and are SW-forwarded out lan2).

| run | HW-forwarding? | frames injected | wedge? |
|---|---|---|---|
| boots A–D (WAN egress) | YES (`cla_up_fwd` 1:1) | 0.9k / 2.4k / 5.1k / 32k | **WEDGED every time** |
| this control (LAN egress) | **NO** (dfwd=0 all run) | **141,095** | **NO WEDGE** |

Sustained ~0.75 MB/s for ~25 min, plus 20× `hashcalc` and 8× `fttest`
install/destroy under live traffic — all clean. `tm_irq` steady 0x10,
`0x9238c29x` gauges wandering in the healthy band the whole time
(e5/5e/12/3a → f0/5e/2c/3f, no monotonic drift), BMU alloc-result 0.

**Conclusions:**
1. **CPU→fabric injection is NOT the trigger** — 141k injected frames are
   harmless when they are trapped/SW-forwarded instead of HW-forwarded.
   This retires the whole "IDM ring / SIPC / SMCT injection-side credit"
   family (candidate 1 in all its forms) on positive evidence, not absence.
2. **The trigger is HW-FORWARDING of fabric-ingress frames** — i.e. the
   frame lifecycle that never reaches a CPU RX descriptor and therefore
   never runs `zx_bmu_free_bp` (zx-eth-main.c:6015; the SW-forward control
   above DOES run it for every frame, which is exactly why it survives).
3. Re the egress/ring back-pressure hypothesis (a colleague's): the control
   was SW-forwarding to a LAN port at similar packet rates without trouble,
   and `tx_pending` is low/flowing at every wedge — back-pressure on the
   IDM ring is not the mechanism. The correlate is HW-forward, not egress
   port or ring depth. (Caveat, stated honestly: this control did not run
   HW-forwarding to a LAN port — that path does not exist yet — so
   "HW-forward to WAN specifically" vs "HW-forward generally" is not yet
   separated.)

## Prime suspect after this: the BMU buffer-pointer POOL DEPTH (HW level)

Structural fit is now exact. Every admitted frame consumes a BMU BP.
- CPU-delivered frames (SW path, the control): driver frees the BP per
  descriptor → no leak → 141k frames clean.
- HW-forwarded fabric-ingress frames: never touch a CPU RX descriptor, so
  nothing in the driver frees their BP; if the fabric doesn't auto-return it
  for this ingress identity, the pool drains monotonically → when it hits
  bottom, **MAC ingress can no longer admit (chip-wide MAC→SPA halt — the
  exact wedge signature) while CPU-injected frames, already DMA'd in, still
  enter the parser and produce garbage keys** (the corruption signature).
  This asymmetry explains BOTH halves of the wedge for the first time.
- Note what is NOT being re-proposed: the driver's *software*
  `tm_bmu_free_ok/fail` counters (they only cover the CPU-RX-consume path)
  and RED ram1 — both already refuted. **The HW pool depth has never been
  read.**

Decisive probe (read-only, safe TM range): `0x92348048` low-16 (runtime
level) for all 5 BMU instances (stride 0x400: 0x92348048 / 8448 / 8848 /
8c48 / 9048), sampled against `idm_wifi_tx_injected` through a WAN-egress
HW-forwarding run. Monotonic climb pinning at pool size (8192) at onset,
same pinned value across the 20k/32k/70k-varied runs = the RED-1024
signature = proof. Flat = clean refutation.

# ADDENDUM 2026-07-31b: TM DMA-descriptor engine + ingress-buffer RE (static)

Static RE sweep of the remaining undecoded blocks (stock decomp + mainline).
Bases: `tm_base=0x92340000`, `npp_base=0x921c0000`, `pp_base=0x92380000`;
`fpga widx = (phys-0x92000000)/4`.

**The two `dma_des` interrupt instances = the two CPU↔fabric TM DMA rings.**
`pon_tm_get_dma_des_int_state` (decomp_all_tm.c:34941) reads reg_id 9,
`pon_tm_set_dma_des_int_mask` (tm.c:35119) RMWs reg_id 0xc; stock masks BOTH
in `tm_pon_tm_reg_initial` (tm.c:42467-42468). Physical: status
`0x92340100` **bit3 = instance 0 (UP ring)**, **bit4 = instance 1 (DN ring)**;
mask `0x92340104` bits[4:3]. The rings themselves (`pon_tm_dma_init`,
decomp_all_plat:6280-6300): UP base/kick/consume
`0x92350050`/`54`/`58`, DN `0x92350060`/`64`/`68`. Raise condition = a
descriptor-engine exception on that ring (fetch/write timeout per
`DMA_TIMEOUT 0x92350030`=50000, or ring under/overflow); there is **no other
per-ring error or level register** — only the consume counters.
(Consistent with our live finding that `0x92340100` bit4 is set from boot on
mainline and is not W1C-clearable: a poor canary. The per-instance bit3
transition at onset is still an uncaptured read.)

**Full stock footprint of the TM 0x10000 block (0x92350000):** `+0x00 |=
0x2f0000` (DMA ctrl), `+0x20/+0x24 = 0x20` (burst/watermark UP/DN),
`+0x28/+0x2c = 1` (ring enable), `+0x30 = 50000` (DMA_TIMEOUT), `+0x34 =
0x40` (prefetch), `+0x3c = 0x400040` (ring geometry), the two ring triples
above, `+0x388 = 0x131217` (arbitration). Descriptor refill/recycle is done
in **software** (`pon_tm_get_next_txdesc` plat:6687, `pon_tm_queue_init`
plat:6916); HW auto-consumes. Per-queue desc counts `0x92350100+q*4` are
**never written** by stock. **Nothing in this block is written
periodically** — `pon_tm_timer_func` (plat:6438) only *reads* the consume
counters. ⇒ **There is no "mainline forgot a periodic poke" bug here.**

**`0x9238c280`–`0x9238c28c` are NOT a separate register group** — the
gparsehashkey latch is 12 words, `0x9238c260..0x9238c28c` (scratchpad/
upkey.py:9,48). So the raw HTTP-header bytes this session found at
`0x9238c200`+ are the *tail of the same corrupted key latch*, not an
independent finding. `0x9238c290/294/298/29c` (fpga widx 0xe30a4-a7) are 4
genuinely undocumented byte-range gauges right after the latch — inferred
(by adjacency + live wander) to be parse-pipeline cursors/levels feeding the
hash engine. Useful only as a leak canary; this session's control run traced
them healthy under 141k frames.

**Stock's IDM TX path touches NO register mainline is missing.**
`idm_net_tx` (plat:4206): 2 desc words, DSB, **KICK `0x921c8040 =
nframes<<16`** (plat:4290), reads **STATUS `0x921c8044`** for backpressure
(plat:4239). Reclaim `idm_check_tx_done_nolock` (plat:3844): STATUS & 0xffff,
cap 0x100, **KICK = done_count low-16 ACK** (plat:3891). Mainline
`zx_idm_tx_reclaim` (zx-eth-main.c:1710-1745) replicates this exactly; init
`pon_npp_idm_init` (plat:4342) writes only 0x8024/8018/801c/8010/8000, all
matched (:1566-1574). ⇒ candidate 1b's "missing driver-side doorbell" is
**dead for the IDM path** on positive evidence.
**Base-gotcha correction (DATASHEET §3.2 lines 1577-1578 are STALE):** the
"IDM 0x800c BMU bp-idx / 0x8014 BMU alloc-poll" rows are wrong — those are
**BMU at tm_base+0x8000 = 0x92348000** (alloc-result `0x9234800c`, free
`0x92348010`, alloc-poll `0x92348014`, per `pon_tm_bmu_alloc_bp` plat:5772 /
`pp_bmu_free_bp` plat:5823). In the IDM block `0x921c800c` is RX_ENABLE and
`0x921c8014` is unused. **Stock's IDM TX issues no BMU alloc/free — the
fabric allocates/frees the BP internally**, which is precisely the
lifecycle the BMU-pool hypothesis says breaks for HW-forwarded
fabric-ingress frames.

**SPA admit:** the only per-port MAC→SPA gate is the SOPC↔SMAC bridge
`0x921d9068` (`smac_sopc_mode_switch` plat:2290; bit(port+5)=RO
phy_mac_ready, bit(port)=SW admit) — per-port and SW/link-driven, so it
cannot itself explain a chip-wide load-triggered halt. There is **no per-uni
receive-enable inside SPA**: the only global backpressure surface is
**buffer availability from the BMU pool feeding the crossbar** — again
pointing at the BP pool.

Honest limit (unchanged): the CPU→fabric HW-forward BP lifecycle is not in
any readable stock function body (the decisive submit path is behind the
missing `halt_baddata` import thunk), so the BMU-pool mechanism remains an
inference from register semantics until `0x92348048` is read live through a
wedge.
