# Fabric-INGRESS endurance wedge candidates — verification pass (Fable, offline, 2026-07-28)

Adversarial verification of
`findings/wifi_stage3_fabric_ingress_wedge_candidates_2026-07-28.md` (commit
94ab6e701) against the driver source, the stock decomp, the register
DATASHEET, and the eth-wedge precedent docs. Strictly device-free: every
verdict below is file:line-cited; claims that need a live read are marked
UNSETTLED with the exact reason. Net result: **candidate 1a's headline
stock-vs-mainline divergence is REFUTED; 1b's evidence is confirmed but its
"stock does it, mainline doesn't" framing needs correction; candidates 2/3/4
verify cleanly; candidate 5 was partially miscalibrated in BOTH directions
and its zero-cost probe is upgraded to a first-class discriminator.** One
NEW stock-parity gap was found on the SMCT CPU-port block
(`0x921d0004=0xB` never written by mainline).

---

## Candidate 1a — SIPC `cpu_up_en` divergence: **REFUTED as stated** (the gauge observation survives)

**The claim**: "stock leaves cpu_up_en OFF at boot, unlike mainline's
`npp_write(e, NPP_REG_SIPC_INIT, 0x11)` which sets both unconditionally."

**Verdict: the divergence does not exist.** The Sonnet doc cherry-picked
the TM-API-layer init and missed the plat-layer boot write:

- Stock's platform boot init `pon_npp_sipc_init` writes the FULL value
  itself: `*(npp_base + 0xc000) = 0x11`
  (decomp_all_plat_zxylzb_9128S.c:2262-2266, called from the pon_npp init
  sequence at :2247).
- The live stock 2MiB dump reads back exactly that: `921cc000 00000011`
  (tasks/00.10.02.re-stock-kmods/findings/regs/stock_eth_2mib.txt:12289).
- Mainline writes the identical value at the identical register:
  zx-eth-main.c:1581 (`NPP_REG_SIPC_INIT` = offset 0xC000, :99).
- DATASHEET.md:1616,1620 already recorded this: "stock-live `0x11` (both
  on) … ✅ ctrl matches stock."

The decomp cite the Sonnet doc used is real but is a *different layer*:
`tm_pon_npp_sipc_initial` (decomp_all_tm.c:43211-43222) does
`sipc_set_rx_en(1); sipc_set_cpu_up_en(0)` — that is the tm.ko API-layer
initializer, and whatever its call timing, the *observed steady state on
stock is 0x11*, byte-identical to what mainline programs. There is no
config divergence to fix here.

**Side flag (DATASHEET internal inconsistency, cannot settle offline):**
DATASHEET.md:511-512 maps reg_id0→bit[0] (rx_en), reg_id1→bit[2]
(cpu_up_en), but 0x11 = bits {0,4}, so either the bit map or the "both on"
gloss at :1616 is wrong (if cpu_up_en really is bit2, it is OFF in both
stock AND mainline — still no divergence; bit4's meaning is then unknown).

**What survives of 1a**: only the empirical lead — the `0x921cc008` gauge
stepped 0x111011→0x222211 at one wedge onset
(wifi_stage3_up_offload_CLOSED_2026-07-28.md:109-110, correctly quoted),
and the gauges are genuinely documented as live FIFO-occupancy gauges
(DATASHEET.md:518). Direction-attribution is undetermined (the adjacent
counter names `sipc2cpu_aful_cnt_up/_dn`, decomp_all_tm.c ~46366/46599,
are delivery-direction — verified present). Sampling them stays in the
probe, but as a symptom/cause discriminator, NOT as a config-divergence
hunt.

## Candidate 1b — SMCT free-doorbell `0x921d0040/004c`: **CONFIRMED evidence, CORRECTED framing**

Every citation checks out:
- `0x921d0040`: "NONE — not read/written anywhere in decomp", HW-maintained
  free-level (smct_channel_submit_re.md:39, confidence HIGH at :56-59).
- `0x921d004c`: written ONLY by `dma_tx_free`, guard bit 0x200000
  (smct_channel_submit_re.md:41,61-65; body verified at
  decomp_all_plat_zxylzb_9128S.c:6212-6228:
  `tm_base+0x1004c = bp | 0x200000 | q<<12 | port<<20`).
- Both tick live in lock-step with QMG sw_fwd / MAC TX during stock CPU
  egress (smct_channel_egress_localized_re.md:5-8).
- Mainline: zero references to either register (grep of zx-eth-main.c —
  the only 0x921d0xxx writes are the init trio, see below).

**Correction 1 — "stock ticks the doorbell, mainline doesn't" overstates
what the RE established.** `dma_tx_free` has ZERO callers in the entire
8-file decomp corpus (smct_channel_submit_re.md:67-69) — even *stock's*
visible C never issues the doorbell; the caller is behind the missing
`halt_baddata()` import thunk. The 2026-05-28 docs explicitly hedge that
0x4c's live movement could itself be HW-maintained
(smct_channel_egress_localized_re.md:18-21). So the "explicit driver-side
free-write stock performs and mainline lacks" is medium-confidence
inference, not established stock behavior.

**Correction 2 — mainline already has a doorbell-free CPU→fabric path that
provably doesn't wedge.** Mainline has TWO CPU→fabric TX paths:
`zx_sw_xmit` (zx-eth-main.c:6255, TM-ring, BMU-alloc'd at :6153) used by
the eth conduit — which has moved gigabytes (12GB sustained validated, per
zte-flowoffload memory) without ever issuing 0x4c — and `zx_idm_xmit`
(:2249). If per-CPU-egress-frame doorbell accounting were required
generically, the eth path would have wedged long ago. For 1b to be the
mechanism, the depletion must be specific to the IDM/fabric-ingress
combination (injected AND CLA-forwarded), which no offline evidence can
currently show — the doc's own caveat ("IDM is a documented-separate ring
… not proven that IDM-ring TX frames transit the SMCT channel") is the
correct confidence level and should be read as governing.

**NEW finding (this pass) — a real, small SMCT stock-parity gap.** Stock's
`pon_npp_smct_init` writes THREE regs: `+0x00=0xB`, `+0x04=0xB`,
`+0x10=0x3810` (decomp_all_plat:3335-3341), plus `+0x08=0x80` from the
init tail (:2254); the stock dump reads all four back
(stock_eth_2mib.txt:16385-16387). Mainline writes `+0x00` (:1582),
`+0x10` (:1583), and `+0x08=0x80` (as the generically-named
`NPP_REG_INIT_VAL`, :102/:1595) — **but never `0x921d0004=0xB`**
(pp_pmau per DATASHEET.md:531). Whether mainline's POR value happens to be
0xB is a 1-read on-device check. Weak prior (eth egress works fine), but
it is the only concrete config divergence found anywhere in the SIPC/SMCT
group, on exactly the CPU-port channel block — added to the probe.

## Candidate 2 — BMU charge/free asymmetry: **CONFIRMED (probe rows corrected)**

All citations verified: `zx_bmu_alloc_bp` :5975 / `zx_bmu_free_bp` :6015;
free called only from the TM-RX consume path (:5487 DSA-invalid drop,
:5505 loopback drop, :5600 common per-descriptor release — comment block
:5592-5599 documents the validated pool-exhaustion history);
`zx_idm_xmit` (:1948-2021) never touches BMU; the DN fabric-egress
dispatch (`ingress_port >= 15` at :5506-5516) is freed by the common
release (comment :5515). `tm_bmu_free_ok/fail` counters at :456-457. The
"only-untested combination" logic (CPU-injected admission that HW-forwards
away) is sound.

**Probe correction**: the doc's probe samples "RED cpuUp-bank ram1
occupancy for q0-7". Those are the wrong rows for this traffic class:
ram1 rows 0-7 (cpuUp) and 8-15 (cpuDn) are the **trap-to-CPU out-buffer**
banks (red_trap_credit_return_re_2026-07-04.md:20-27) — an injected frame
that HW-forwards to the WAN MAC is never delivered to the CPU, so if RED
charges it anywhere it is on an **egress-port out-queue row**: tcont rows
at `tcont*8+0x10`, port rows at `(40+port)*8` (same doc :22-23). Sweep the
whole ram1 row space (rows 0-15, 0x10-0x4f, and (40+p)*8 for p=0..4) via
the same indirect port — identical cost, complete coverage. The oracle
itself is live-proven: in the churn fix the pinned row read guart_used =
exactly 1024 == the pinned counter (fix_churn_red_dnbank_2026-07-04.md:14-21).

## Candidate 3 — CLA parser/hash pipeline hazard: **CONFIRMED as the downstream-corruption reading; strengthened by the precedent's disanalogy**

Citations verified: gparsehashkey latch `0x9238c260`
(DATASHEET.md:29,970 — "byte-exact vs the SW key-builder");
`cla_acl_hash_addr_gen` @ tm.c:4154
(phase6_cla_hw_hash_CRACKED.md:11,14); the degenerate `45000000 …`
raw-IP-byte pattern quote matches the source doc
(wifi_stage3_up_offload_CLOSED_2026-07-28.md:101-104).

One addition this pass: the RED-bit6 precedent actually *supports* the
composite (1/2 upstream + 3 downstream) reading more than the doc said.
When the eth cpuDn credit walled at 1024, the failure mode was **graceful**
— RED demoted further traps to sw_fwd, traffic kept flowing
(red_trap_credit_return_re_2026-07-04.md:60-61). A pure credit wall does
NOT corrupt parsers. The new wedge corrupts trap descriptors, CLA lookups,
and the parse-key latch — so either this credit is of a different kind
(one whose exhaustion starves a buffer feed rather than gating admission),
or candidate 3's buffer-reuse hazard is the actual damage mechanism seated
on top of 1/2's depletion. The doc's "downstream consequence" framing is
right; the graceful-vs-destructive contrast is the sharpest reason to
believe it.

## Candidate 4 — SADM/DPA per-port policer, ports 6/7: **CONFIRMED accurate (kept at ★★)**

- "Mainline: zero DPA writes" / "Mainline: zero SADM writes" — verified at
  queue_subsystem_re_2026-07-04.md:115,119 (SADM base 0x92384000, DPA
  0x92398000; pipeline position MAC→SPA→SADM→CLA at :54).
- The previously-uncited "SADM counters were checked 0/inert" claim IS
  attested: wan_rx_onewrap_wedge_2026-07-03.md:173 ("SADM pass[0x1c4200]=0
  drop[0x1c4208]=0 … RULED OUT") — for the WAN trap path only, never for
  ports 6/7 traffic, exactly as the doc said.
- The pipeline_stats reads exist at zx-eth-main.c:7679-7684
  (e->base+0x1c4200/0x1c4208 = phys 0x92384200/08).
- Note vs candidate 1a: unlike SIPC, SADM is a REAL stock-vs-mainline init
  divergence (stock writes adm_en/trap_en/one_second,
  queue_subsystem_re:117-119). It stays ranked low only because policer
  exhaustion produces drops, not parser corruption, and the counters are
  already sampled for free in the probe.

## Candidate 5 — SW IDM ring reclaim: **CORRECTED in both directions; probe upgraded**

The doc's blast-radius dismissal ("would stall this netdev's queue, not
… kill the unrelated SW path") is **wrong on the SW-path point**: the
ftwifi=0 SW path injects TCP via the SAME `zx_idm_xmit`
(wifi_stage3_up_offload_CLOSED_2026-07-28.md:105-107 — ICMP survives
precisely because it rides the stack, not the fabric). Additionally,
`tx_pending` is reset ONLY in the probe-time ring init
(zx-eth-main.c:1697-1700), not on ndo_open — so "idm1 down/up does NOT
recover" is *consistent* with a pinned `tx_pending`, not evidence against
it. Three of the four wedge symptoms fit a driver-local stall.

What still argues against candidate 5 as root cause: the fabric-side
corruption evidence (post-wedge lookups MISS 1:1 and traps arrive
noparse — frames demonstrably still transit the fabric, which a
driver-side TX stall would prevent), and reclaim's arithmetic is
straightforward (read `IDM_REG_TX_STATUS & 0xFFFF`, cap 0x100/call, ACK
consumed count via TX_KICK low16 — :1717-1736; `IDM_TX_POOL_LIMIT` 0x200
:305 vs ring 1024 :296, so the pool gate trips long before ring wrap).

**Upgrade**: reading `e->tx_pending` at wedge is not a mere rule-out — it
is the cheapest *fork discriminator* in the whole plan:
- `tx_pending` pinned at 0x200 ⇒ the fabric-side ring CONSUMER stopped
  acking (TX_STATUS frozen) ⇒ an admission-side wall (candidates 1/2),
  with precedent (the Phase-B "QMG DN queue-5 consumer unbound" fabric
  black-hole, memory zte-wifi-phaseB-dispatcher);
- `tx_pending` free-flowing while throughput is zero ⇒ frames are admitted
  but mis-parsed/mis-forwarded ⇒ candidate 3's corruption is primary.

---

## Re-ranked list (post-verification)

1. **★★★★☆ Composite: fabric-side admission-resource depletion on the
   CPU-inject identity (candidate 1's shape + candidate 2's framing),
   surfacing as candidate 3's parser corruption.** Same structural top
   pick, but stripped of 1a's refuted config-divergence story and with
   1b's stock-side mechanism downgraded to medium-confidence inference.
   The only *proven* facts are: SMCT 0x40/0x4c move with stock CPU egress;
   mainline never touches them; the 0x921cc008 gauge stepped once at
   onset; nothing yet attributes any of these to the IDM path.
2. **★★★★ Candidate 3 (CLA parser/buffer-reuse hazard)** — promoted to
   co-equal observable: the graceful-vs-destructive contrast with the RED
   precedent means the corruption mechanism must be identified even if a
   credit wall is found upstream.
3. **★★★ Candidate 2 probe set (BMU/RED occupancy)** — unchanged rank,
   corrected rows (full ram1 sweep, not cpuUp q0-7).
4. **★★ Candidate 5 (IDM reclaim / consumer stall)** — promoted from ★:
   still unlikely as root cause, but its one-line probe now carries the
   primary fork.
5. **★★ Candidate 4 (SADM/DPA)** — unchanged; free counters ride along.

## The single sharpest first probe (offline-justified, all read-only)

One sustained UP-only fabric-ingress run (`ftwifi=1`, no DN traffic),
sampling every ~2k injected frames against `e->idm_wifi_tx_injected`
(:487, printed at :7575), plus one identical DN-only control run:

| read | what | why |
|---|---|---|
| `e->tx_pending` (debugfs or devmem the atomic) + `IDM_REG_TX_STATUS` | driver-side pool vs HW ack | THE fork: pinned-at-0x200 ⇒ admission wall upstream; free-flowing ⇒ corruption primary |
| `0x921cc004` | SIPC drop/aful nibbles (already in pipeline_stats :7674) | any nonzero = SIPC actually saturating |
| `0x921cc008/18/1c/20` | SIPC gauges | the observed onset step; monotonic-climb-to-fixed-value vs wander |
| `0x921d0040`, `0x921d004c` | SMCT free-level / doorbell | 1b: does the free-level drain monotonically toward a floor? |
| `0x921d0004` (once, at boot) | pp_pmau | NEW parity gap: stock=0xB; if mainline POR ≠ 0xB, cheap fix candidate |
| ram1 sweep rows 0-15, 0x10-0x4f, (40+p)*8 p=0..4 (`0x92344014=row\|0x8400000`, poll `0x92344018` bit0, read `0x9234401c` [10:0]/[25:11]) | RED out-queue occupancy, ALL banks | live-proven oracle (fix_churn_red_dnbank:14-21); any row climbing 1:1 with injected count and never falling = the RED-bit6 tell |
| `tm_bmu_free_ok/fail` (:6388-6389) + `gparsehashkey 0x9238c260` continuously | BMU health + corruption onset shape | gradual bad-read intermixing ⇒ race/reuse (cand 3); hard step ⇒ latch/wall |

Decision rule: a gauge that climbs monotonically and freezes at the SAME
value across runs while onset frame-count varies (the validated RED-bit6
signature) identifies the exhausted resource; all-flat plus pinned
`tx_pending` points at the ring consumer (Phase-B q5 precedent); all-flat
plus flowing `tx_pending` promotes candidate 3 to primary. Recovery
experiments (greg ram-init pulses etc.) should be sequenced AFTER the
gauge run — note the OPC pulse did NOT unstick ram1 in the RED case
(fix_churn_red_dnbank_2026-07-04.md:43).

## Sonnet claims that were wrong or unsupported (summary)

1. **WRONG**: "stock leaves cpu_up_en OFF at boot, unlike mainline" —
   stock's `pon_npp_sipc_init` writes 0x11 at boot
   (decomp_all_plat:2265); live stock reads 0x11
   (stock_eth_2mib.txt:12289); mainline is byte-identical (:1581).
2. **OVERSTATED**: "stock ticks the SMCT doorbell during CPU egress" —
   the ticking is live-observed but `dma_tx_free` has zero decomp callers
   and the source docs themselves hedge that the movement may be
   HW-maintained (smct_channel_submit_re.md:67-69).
3. **WRONG (partially)**: candidate 5's blast-radius dismissal — the dead
   SW path and the no-recovery-on-down/up are both consistent with a
   pinned `tx_pending` (shared `zx_idm_xmit`; reset only at ring init
   :1700).
4. **IMPRECISE**: candidate 2's probe rows (ram1 cpuUp q0-7) don't cover
   the rows an injected+HW-forwarded frame could charge.
5. Everything else checked out, including the honest-caveats section,
   which was accurate throughout.

## What remains unsettleable offline (unchanged from the source doc, re-confirmed)

- Whether IDM-ring frames share SMCT/SIPC/BMU accounting with stock's
  (still-unRE'd) CPU→fabric submit — the decisive stock function is a
  missing import thunk (smct_channel_submit_re.md §HONEST STATUS).
- Direction-attribution of the 0x921cc008 gauge fields.
- Mainline's POR value of `0x921d0004`.
- The SIPC ctrl bit map inconsistency (bit2 vs bit4 for cpu_up_en).
