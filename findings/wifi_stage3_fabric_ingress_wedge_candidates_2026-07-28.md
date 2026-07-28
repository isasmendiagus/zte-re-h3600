# Fabric-INGRESS endurance wedge (WiFi UP HW-offload) — ranked candidate root causes (DEVICE-FREE RE, 2026-07-28)

Static RE only, no device access. Task: rank candidate mechanisms for the NEW
sustained-load wedge documented in
`findings/wifi_stage3_up_offload_CLOSED_2026-07-28.md` ("⚠ NEW OPEN ISSUE"
section) — after a variable 20k–72k HW-forwarded **fabric-INGRESS** frames
(CPU → fabric injection via the WiFi vif's `zx_idm_xmit` leg, CLA-lookup,
HW-forward straight to WAN MAC), the fabric corrupts (CLA lookups miss,
traps go noparse, `gparsehashkey` reads degenerate raw-IP-byte patterns);
fabric-EGRESS (DN, 110k frames) is clean; recovery is reboot-only (idm1
down/up does NOT recover). Sources: `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`,
`tasks/00.10.02.re-stock-kmods/findings/DATASHEET.md`, the stock decomp,
memory `zte-redwedge-unicast-cpu` / `zte-wifi-up-offload` / `zte-cla-hw-hash-engine`.

---

## Framing: this is provably a NEW code path, not a rerun of the eth wedge

The eth-side wedge family (RED_CFG bit6 cpuDn charge-accounting, fixed
2026-07-04) is about credit charged when a frame is **delivered to the CPU**
(a WAN/LAN MAC-ingress frame traps, QMG charges the RED cpuDn out-buffer,
nothing returns the charge). That mechanism is **not directly reachable
here**: fabric-ingress UP frames are *injected by the CPU* via
`zx_idm_xmit` (zx-eth-main.c:1948) and then **HW-forwarded straight to the
WAN MAC** — they never touch a CPU RX descriptor, so the RED cpuDn/cpuUp
bank and the BMU-free call that fixed the churn wedge
(`zx_bmu_free_bp`, zx-eth-main.c:6015, called only from the CPU-RX-consume
path at zx-eth-main.c:5487/5505/5600) are **not in this frame's lifecycle at
all**. The *family resemblance* (monotonic charge with no return path for a
traffic class the driver never fully accounts for) is the right lens, but
the specific register is provably different — and, per two dedicated 2026-05-28
RE sessions (`tasks/00.10.02.re-stock-kmods/findings/smct_channel_egress_localized_re.md`,
`smct_channel_submit_re.md`), **stock's own CPU→fabric egress/submit
mechanism was never fully reverse-engineered** — the decisive function body
sits behind a missing `halt_baddata()` import thunk. That is a hard limit on
how far device-free RE can go here; it is flagged in every candidate below.

## Candidate ranking

### 1. ★★★★★ An unacknowledged CPU→fabric admission credit/FIFO specific to the injection path (structural top pick)

**Mechanism**: some HW-maintained gauge/credit tied to CPU-originated fabric
admission (the "CPU-port ingress" block group in the architecture diagram —
SIPC 0x921cc000 · SMCT 0x921d0000 · IDM 0x921c8000, DATASHEET.md:214) is
charged per injected+HW-forwarded frame and is either never drained (HW
auto-drain assumption that breaks under this traffic shape) or requires an
explicit driver-side "free"/ack write mainline never issues, mirroring the
RED-bit6 / SMCT dma_tx_free family shape (charge-with-no-return until reboot).
Two concrete named sub-candidates, both flagged but **unresolved** in our own
docs — this session did not add new certainty, only sharper framing:

**1a. SIPC `cpu_up_en` side (phys 0x921cc000).** DATASHEET.md:507-522: SIPC
is explicitly "rx_en / cpu_up_en credit/mailbox bridge" — `sipc_set_rx_en`
(reg_id 0) vs `sipc_set_cpu_up_en` (reg_id 1), stock decomp
`tm_pon_npp_sipc_initial` (decomp_all_tm.c:43211-43217): `sipc_set_rx_en(1);
sipc_set_cpu_up_en(0)` — **stock leaves cpu_up_en OFF at boot**, unlike
mainline's single init write `npp_write(e, NPP_REG_SIPC_INIT, 0x11)`
(zx-eth-main.c:1581) which sets both unconditionally. `0x921cc008(+0x18/1c/20)`
are documented "live FIFO-occupancy/credit GAUGES (wander up/down with flow,
~0x800 on stock; NOT config)" (DATASHEET.md:518) — and this is the register
the wedge doc's own lead flags stepping (0x111011→0x222211) at one wedge
onset. **Caveat (lowers confidence)**: the decomp's own field names for the
*adjacent* counter register (0x921cc004) are `sipc2cpu_aful_cnt_up` /
`_dn` (decomp_all_tm.c:46366-46367, 46599-46600) — "sipc**2cpu**" names the
**fabric→CPU delivery** direction (rx_en side), not CPU→fabric injection
(cpu_up_en side). It is not proven that 0x921cc008's gauge tracks the
injection side at all — it may equally be reflecting delivery-side
backpressure that is a *symptom* of the jam rather than its cause. This is
the single open question the first probe should settle.

**1b. SMCT CPU-port egress channel free-level/doorbell pair (phys
0x921d0040 / 0x921d004c).** A separate, better-attested 2026-05-28 RE pass
(decomp-grounded, live-stock-verified) found these two registers **tick live
in lock-step with QMG sw_fwd / MAC TX during real CPU-originated egress**
(`smct_channel_egress_localized_re.md:5-8`) — 0x921d0040 is HW-maintained
(no SW accessor anywhere in the decomp: "NONE — not read/written anywhere",
`smct_channel_submit_re.md:39`) and 0x921d004c is written **only** by
`dma_tx_free` (plat:6214), a **post-egress buffer-FREE doorbell**, guarded by
bit 0x200000 ("request pending") (`smct_channel_submit_re.md:41,61-65`).
This is structurally identical to the BMU/RED "credit returned by an
explicit free-write after the frame is done" pattern. **Mainline never
calls anything resembling `dma_tx_free`** — grep of zx-eth-main.c shows zero
references to 0x921d0040/004c. If WiFi UP's `zx_idm_xmit` path (or the
switch's internal handling of frames injected via the IDM ring) shares this
SMCT channel's buffer-pool accounting with the "normal" CPU eth-TX path,
sustained injection without ever issuing the free-doorbell would deplete a
finite HW pool exactly like the wedge's signature. **Caveat (lowers
confidence)**: IDM (0x921c8000) is a documented-separate ring from SMCT
(0x921d0000) — it is *not proven* that IDM-ring TX frames transit the SMCT
channel at all; they may use an entirely separate HW admission path that
happens to share none of this state. The submit mechanism for *even the
already-working* CPU→fabric eth-TX path was never pinned (see framing
section) — so whether IDM traffic shares it is a real unknown, not
something device-free reading can resolve further.

**Probe (the single highest-value first probe — cheap, read-only, decisive
by the RED-bit6 precedent)**: run a controlled fabric-ingress-ONLY sustained
UP HW-forward session (`scratchpad/upab.py` / `uphold.py`, `ftwifi=1`, no
concurrent DN traffic) while sampling, once per N injected frames (use the
existing driver counter `e->idm_wifi_tx_injected` as the x-axis — it already
exists, zx-eth-main.c:486-2005):
```
0x921cc004               # SIPC drop/aful/ful nibbles (already read at
                          #   zx-eth-main.c:7674 as "SIPC drop=0x%08x")
0x921cc008 / 18 / 1c / 20 # SIPC FIFO gauges (memdump; safe TM/PP range)
0x921d0040 / 0x921d004c   # SMCT egress-channel free-level / free-doorbell
```
Expect ONE of two signatures:
- **Monotonic climb (not wander) in a specific field, saturating at a fixed
  value the moment the wedge fires — and that fixed value is IDENTICAL
  across repeated runs even though the frame-count-at-onset (20k/22k/72k)
  varies** (this is exactly the RED-bit6 tell: `qmg_dn_trap` count varied
  with idle background chatter, but `ram1` occupancy pinned at exactly
  1024 every time). This proves a hard admission-wall credit exhaustion and
  identifies the exact register to fix (mirror the RED-bit6 pattern: either
  clear a charge-enable bit, or add the missing free/doorbell write).
- **All four flat / normal wander, no correlation with onset.** Rules out
  both 1a and 1b in one session; fall to candidate 2/3 below.
Also run the SAME probe on a DN-only (fabric-EGRESS, already known-clean)
session as a control — if SIPC/SMCT gauges behave identically in both
directions, they are not direction-discriminating and cannot explain why
only fabric-ingress wedges.

### 2. ★★★ BMU internal buffer-pool charge/free asymmetry for HW-forwarded-without-CPU-delivery frames

**Mechanism**: the switch fabric may allocate an internal packet buffer
(BMU `bp`) for every admitted frame regardless of ingress identity
(physical MAC or CPU-injected via IDM), the same pool `zx_bmu_alloc_bp`/
`zx_bmu_free_bp` (zx-eth-main.c:5975/6015) manage for the CPU-RX-consume
path. Normal WAN-ingress→LAN-egress HW-forward (no CPU involvement either
end) has moved gigabytes cleanly for a long time, and DN fabric-EGRESS
(WAN→fabric→CPU-delivered-to-vif, which DOES call `zx_bmu_free_bp` per
zx-eth-main.c:5506-5516) has moved 110k frames clean — so the *general*
HW-forward-without-CPU-touch pattern and the *general* CPU-delivery-then-free
pattern are BOTH independently proven not to leak. What's untested by any
prior work is the ONE combination this new path exercises: **CPU-injected
(not physical-MAC-ingress) admission that HW-forwards away (never delivered
to CPU)** — i.e. the injection side's buffer accounting might not be
symmetric with either proven-safe case, especially since `zx_idm_xmit`
(zx-eth-main.c:1948-2021) never calls `zx_bmu_alloc_bp` at all — the IDM
ring is a pure skb-DMA descriptor push, so if the fabric's ingress
admission for CPU-injected frames DOES need a BMU (or BMU-like) buffer,
either HW allocates it invisibly (fine, by the two proven-safe precedents)
or something in the injection path needs to but doesn't (leak).

**Probe**: during the same fabric-ingress-only run, sample
`tm_bmu_free_ok` / `tm_bmu_free_fail` (existing driver counters,
zx-eth-main.c:456-457) and the RED cpuUp-bank `ram1` occupancy for q0-7
(the exact oracle from `findings/red_trap_credit_return_re_2026-07-04.md`:
poll `0x92344018` bit0, `0x92344014 = q|0x8400000` for q=0..7, read
`0x9234401c`). Expect flat 0 (as in the churn fix's validated state) if this
candidate is irrelevant; any climb correlated with injected-frame count is
the tell.

### 3. ★★★ CLA hash-engine / parser pipeline hazard under sustained back-to-back CPU admission (best fit for the CORRUPTION symptom specifically)

**Mechanism**: `gparsehashkey` (phys 0x9238c260, 12-word HW-extracted-key
latch, `scratchpad/gksample.py`/`probe.py`) reading "degenerate repeating
patterns (`45000000 00000001...` — raw IP bytes where the key header should
be)" post-wedge is a parser/extraction-stage symptom, not a queue-occupancy
symptom — `0x45` is literally the IPv4 version/IHL byte, i.e. the CLA's key
extractor is reading raw payload at an offset where it should be reading a
built key header (`ZX_FT_KEY_HDR_*`, `0x30`/`0x38`/`0x48` per
`zx_ft_build_key`). This is the signature of a **stale or misaligned buffer
pointer feeding the hash/parse engine** (`cla_acl_hash_addr_gen`,
tm.c:4154, per `tasks/00.10.02.re-stock-kmods/findings/phase6_cla_hw_hash_CRACKED.md`) —
consistent with a slowly-shrinking pool of valid in-flight buffers (from
candidate 1 or 2) eventually causing a buffer to be reused/read while a
prior in-flight frame's DMA write is still in progress, which would also
explain the **variable** 20k–72k onset (a timing-dependent race gets more
likely as headroom shrinks, unlike a hard fixed-depth wall which would fire
at a constant count). This candidate is therefore best read as the
**downstream consequence** of 1 or 2 rather than an independent root cause
— ranked here because it is the most direct explanation of the reported
*corruption* (as opposed to the reported *stall*), and worth checking on
its own terms if 1/2 both refute.

**Probe**: capture `gparsehashkey` continuously (not just post-wedge) during
the sustained run — if the degenerate pattern first appears gradually
(occasional bad reads intermixed with good ones, increasing in frequency)
rather than as a hard step, that supports the race-hazard framing over a
clean admission-wall latch, and further narrows where the buffer-reuse
window is (correlate against `idm_wifi_tx_injected` and any BMU/SIPC/SMCT
gauge sampled in parallel).

### 4. ★★ SADM/DPA per-port policer state on the fabric-ingress "port 6/7" identity, never initialized by mainline

**Mechanism**: mainline "zero SADM writes… zero DPA writes" entirely
(`findings/queue_subsystem_re_2026-07-04.md` §C, "❌ the gap") — these
blocks sit between SPA and CLA in the ingress pipeline
(`ingress MAC → SPA → SADM → CLA…`) and include per-port/per-subscriber
token-bucket policers. If fabric ports 6/7 (the CPU-inject identity used by
`zx_idm_xmit`/IDM) are, unlike physical MAC ports, subject to a SADM
per-port bucket that is left at an undefined/marginal power-on-reset state
(never explicitly initialized to a known-good value the way CLA/RED/QMG
are), a bucket that drains to empty under sustained high-rate injection
could plausibly produce mis-admission (not a clean drop, since SADM's own
current counters were checked to be 0/inert in the *unrelated* wan_rx_onewrap
case — but that check was never repeated for the fabric ports 6/7 identity
specifically). Ranked lower because it is the least-attested candidate (no
existing finding has touched SADM/DPA behavior for ports 6/7 at all) and
requires the most new RE to even characterize.

**Probe**: read SADM pass/drop counters (`0x92384000`-based per earlier
DATASHEET decode, and `0x1c4200`/`0x1c4208` already surfaced in
`pipeline_stats`, zx-eth-main.c:7679-7684) filtered to whatever ingress-port
identity the fabric-ingress path presents (>=15 per the `ingress_port>=15`
convention at zx-eth-main.c:5506) before/during/after the run. Flat-zero
throughout → refutes; any climb (even without an explicit wedge) is a lead.

### 5. ★ Local SW-side IDM ring reclaim bug (cheap to rule out, weak fit for the system-wide corruption)

**Mechanism**: `zx_idm_xmit`/`zx_idm_poll`'s local `tx_pending` atomic +
`IDM_REG_TX_STATUS` reclaim (zx-eth-main.c:1717-1736, `IDM_TX_POOL_LIMIT`
0x200 vs `IDM_TX_RING_SIZE` 1024) could in principle drift under sustained
load (e.g. `done_cnt` 16-bit read racing a wrapped kick count), eventually
permanently stalling *this netdev's* queue. Ranked lowest because a pure
local ring-accounting bug would stall `idm1`'s TX queue specifically, not
corrupt CLA lookups fabric-wide or kill the unrelated SW path — the
reported symptom is bigger than this mechanism's blast radius. Worth a
free/no-cost check only.

**Probe**: read `e->tx_pending` / cumulative `IDM_REG_TX_STATUS` done-count
at the moment of wedge; if `tx_pending` is pinned at `IDM_TX_POOL_LIMIT`
while everything downstream (SIPC/SMCT/BMU/RED) reads clean, this jumps in
rank; otherwise treat as ruled out alongside 1-4's clean reads.

---

## What device-free RE cannot settle (flagged honestly)

- **The true CPU→fabric frame-submit mechanism is unknown even for the
  long-working eth path** (`smct_channel_submit_re.md` §HONEST STATUS) —
  the decisive stock function body is a missing import thunk. Any claim
  that IDM-ring traffic does or doesn't share SMCT/SIPC/BMU accounting with
  that path is an inference, not a proof, until read live.
- Whether `0x921cc008`'s gauge fields are direction-attributable (UP vs DN,
  i.e. cpu_up_en vs rx_en) is undetermined from the decomp alone — the
  adjacent counter register's field *names* (`sipc2cpu_*`) argue for
  delivery-direction, but the gauge register itself has no such naming.
- Whether fabric ports 6/7 (IDM/CPU-inject identity) receive the *same*
  SPA/SADM/CLA per-port treatment as physical ports 0-4, or a distinct HW
  code path, is not derivable from the DATASHEET's current per-port RE
  (which was done against physical ports).

## Recommended order for the next device session

1. Run candidate 1's probe first (SIPC + SMCT gauges vs `idm_wifi_tx_injected`,
   UP-only run, with a DN-only control) — decisive by the RED-bit6
   precedent and touches only existing safe-range MMIO reads.
2. In the same run, sample candidate 2's BMU/RED-cpuUp counters and
   candidate 3's `gparsehashkey` latch for free (all read-only, all in the
   already-used safe TM/PP/CLA range) — one sustained run can score
   candidates 1-3 simultaneously.
3. Only open candidate 4 (SADM/DPA) if 1-3 all come back flat.
4. Candidate 5 is a zero-cost sanity check, do any time.
