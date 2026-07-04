# Churn/WAN-RX 1024 wedge — ROOT CAUSE FOUND + FIXED: RED_CFG bit6 (cpuDn out-buffer charge-accounting) — LIVE on-device (2026-07-04)

## Verdict: FIXED in-driver ([red-arm 2026-07-04], 2 lines of behavior + comments). The wedge was the RED cpuDn out-buffer occupancy leaking 1:1 per DN trap with NO return path; RED_CFG **bit6** (phys 0x92344004) is a live level control for that charge-accounting — cleared (0xDE→0x9E) the charge never accumulates and the wedge is impossible. Validated: qmg_dn_trap driven to >10500 across FIVE 60-flow churn storms on one boot (old hard death wall: 1024), q8-15 occupancy flat at 0 throughout, downloads at line rate, `churn_no_wedge` + new `red_credit_recycle` guards PASS.

Follow-up to `findings/red_trap_credit_return_re_2026-07-04.md` (the device-free RE whose
recipe this session executed) and `findings/fix_churn_adm_policer_2026-07-04.md` (the
monotonic-latch characterization + host-side oracle). Ran on the live H3600, RAM-boot
mainline. Driver changed; regression tests added; full battery run.

---

## A. STEP 1 (read-only pre-check) — the RE's structural hypothesis CONFIRMED exactly

Box found idle-wedged (qmg_dn_trap 1020→1024 while watched). RED out-queue used_space via
the indirect RAM oracle (CMD 0x92344014 = q|0x8400000, DONE 0x92344018 bit0, DATA0
0x9234401c, guart_used=[10:0]):

```
q0-q7  (cpuUp): all 0
q8-q14 (cpuDn): all 0
q15    (cpuDn qid7): guart_used = 1024   <-- exactly == the pinned qmg_dn_trap
```

Stable across 30 s; never falls; all other queues zero. **The pinned resource is exactly
the hypothesized RED cpuDn out-buffer** (q15 = DN bank qid7 = the control/SYN trap class
from the churn characterization). ram5 reads all-zero (different structure; ram1 is the
gauge, matching stock's `red_get_out_que_ram_used_space`).

## B. STEP 2 (the release poke) — REFUTED, along with every other SW return op

All tested live with the ram1 occupancy oracle watching, on BOTH a stale-pinned queue
(q15=1024) and an actively-charging one (q14, after retargeting):

| Candidate return op | Result |
|---|---|
| Release port 0x92344068/64, **bank=1 (bit14)**, qid=7, count=16, sop=1 and sop=0 | ring1 pending (TM[0x1011c] HIGH16) decremented -16 each — the engine ACTS — but ram1 q15 UNCHANGED |
| Release port bank=0, same qid/counts/sops | ring0 pending decremented; ram1 UNCHANGED |
| Same matrix on the ACTIVELY charging queue (qid=6/q14) | no dip; leak continued 1:1 through the releases |
| ram1 direct occupancy=0 write (data-then-CMD, the SBRAG order) | doesn't stick (RO) |
| ram1 write CMD-first/descending (the CLA-ram lesson) | doesn't stick |
| ram0 out-buffer cfg rewrite (same value 0x400) | occupancy unchanged |
| RED cfg_enable full toggle 0x92344004: 0 → restore | stuck charge unchanged (oracle-verified this time; prior sessions' blind rule-out was right) |
| OPC ram-init pulse 0x921C0008[9:8] set→clear | ram1 q15/q14 unchanged; leak continued right through it (isolated on a virgin boot) |

**Conclusion: the release-port word is a RING-delivery credit ack only. The RED cpuDn
occupancy has NO software return op.** (The count-field overflow discovery in the RE was
still load-bearing: it proved the old rule-out invalid and justified re-testing — the
re-test just refuted the poke for a deeper reason.)

Side-effect note: releases with no pending frames drive TM[0x10100+q*4] pending negative
(0xffe0 = -32) — harmless on a wedged box, cleared by reboot; don't do it on a healthy one.

## C. The pivotal discovery — ram7 BASE bank steering + the bit6 level control

1. **The RE's "unwritten base bank" premise was wrong**: mainline's `zx_cla_apply_replay`
   blankets ALL CLA ram7 entries 0..1023 with qid=7 (`ram7_data[17]={7,0}`), then
   `zx_chip_tm_init_trap_queues` overwrites the per-port banks with qid0. Live clapeek:
   base bank (0x00-0x7f) = 7 everywhere, port4 bank (0x280+) = stock qid0 values.
2. **The DN direction consults the BASE bank; UP consults the per-port banks** — proven
   live: blanket-rewriting the base bank 7→6 instantly moved new DN-trap charges from
   RED out-queue 15 to 14 (and 6→5 moved them to 13). This *functionally unwedged the
   wedged box without reboot* (new traps admit against the empty queue; qmg_dn_trap blew
   past 1024, delivery to CPU resumed).
3. **While probing, the leak STOPPED permanently mid-session.** Bisected on a fresh boot:
   my toggle had written RED_CFG=0x1e, clobbering the undocumented bits [7:6] of the
   0xDE reset value. Runtime bit-bisect on a leaking box:
   - 0x5E (bit7 cleared): still leaks
   - **0x9E (bit6 cleared): leak stops INSTANTLY** (single write, no zero-edge needed)
   - restore 0xDE: leak RESUMES 1:1
   - re-clear: freezes again
   **RED_CFG bit6 = the cpuDn out-buffer charge-accounting enable, a live level control.**
   With bit6=0, DN traps stop charging used_space entirely → the 1024 admission wall can
   never be reached → no wedge, ever. (Mechanically it is charge-DISABLE, not a
   credit-return: pre-existing stuck charges stay until reboot, but stop mattering once
   no new charge accumulates — and on a fixed-from-boot box they never exist.)

## D. Why stock never hits this (and why this is a deliberate stock divergence)

Stock ALSO runs RED_CFG=0xDE (bit6 set; confirmed in stock_eth_2mib.txt:92344004) — but
stock never exercises DN hw_trap at scale (live stock: qmg_dn_trap == 0 under real
traffic; its to-CPU rides the sw_fwd verdict). The charge-only accounting can't hurt a
driver that never charges it. Mainline's trap-all DSA-conduit architecture charges it on
EVERY WAN-ingress frame → bit6 must be off until/unless delivery is ever rearchitected
onto sw_fwd. CPU overload protection still exists on either side of it: ADM per-CPU-queue
PPS policing (pre-RED), the RX-ring pending counters + NAPI budget, the BMU pool.

## E. The fix ([red-arm 2026-07-04], zx-eth-main.c) — and the gotcha that almost hid it

1. `zx_tm_red_init` (end): RMW-clear bit6 of RED_CFG (tm off 0x4004), with the full story
   in a comment. Boot log: `RED_CFG 0xde -> 0x9e (bit6 cpuDn charge-accounting OFF)`.
2. **`zx_tm_dma_init` line ~4424 — the reverter**: a stock-dump replay block later in
   probe wrote the literal stock constant `tm_write(e, 0x4004, 0x000000de)`, silently
   restoring bit6 after fix (1) — the first fixed build still leaked, caught only because
   validation re-read the occupancy natively. Changed to 0x9E with a warning comment.
   (Found by reading RED_CFG post-boot = 0xde despite the armed log line, then grepping
   the driver for 0x4004.)
3. Corrected the `zx_red_block_init` header: its dead-space base bug (offsets 0x184xxx
   through tm_write → 0x924Cxxxx) is real but NOT the wedge root cause (stock also runs
   0xDE); left functionally untouched pending a dedicated arbitration pass.

## F. Validation (live, fixed build, no pokes)

- RED_CFG stays 0x9E through full rig-up (probe → rc.router → wan → client → offload).
- Idle + traffic: qmg_dn_trap climbs freely, **ram1 q8-15 flat at 0** from boot.
- **`red_credit_recycle` (new targeted guard): PASS** — 406 host→lan4 DN-trap pings,
  max q8-15 growth 0. (On the unfixed driver the charged queue grows ~1:1 = FAIL; the
  leak side was demonstrated live on the virgin unfixed boot earlier the same session.)
- **`churn_no_wedge`: PASS** — the exact historical killer storm (n=30×2): qmg_dn_trap
  8956→10565, lan4 datapath alive, 31/60 flows served. One boot survived FIVE such
  storms (cumulative dn_trap >10500 = 10× the old death wall).
- Full battery: see the summary in the session report (baseline_download,
  sustained_download, concurrency_race, counters_sanity, dmesg_clean).

## G. Test-harness lessons baked into regress.py (same commit)

- New `red_credit_recycle` test (ORDER + QUICK): the fast, surgical leak guard.
- `churn_no_wedge` joined the default ORDER (near the end) and learned the real-world
  oracle physics: (a) the modem AP's **wire→WiFi leg** saturates for ~1-4 min post-storm
  (its ICMP responder stays clean → host→modem 0% does NOT clear the lan4 leg — the
  "modem-independent" oracle is not AP-bridge-independent!); baseline + post-storm oracle
  now retry across that window; (b) when lan4 stays dead, a **device-side trap-delta
  probe** discriminates: ping lan4 50× and read Δqmg_dn_trap — the true reboot-only wedge
  has the counter FROZEN (RED demotes), the AP outage shows it climbing 1:1 (measured
  live: +132 for ~132 arriving pings while the host saw 80-100% reply loss). Frozen →
  FAIL; climbing → SKIP/inconclusive.
- `qmg_dn_trap`-value gates retired everywhere (counters_sanity, recovery_alive,
  sustained_download, churn, rig.py status/download): it is a CUMULATIVE admit counter
  that now legitimately exceeds 1024 on a healthy box. Wedge detection = the oracles.

## H. Ruled out / de-scoped this session

- No software refund of an already-charged cpuDn queue exists (full matrix in §B) — a
  box wedged on a pre-fix build stays charge-stuck until reboot (the base-bank steering
  in §C.2 is the only reboot-free workaround, 8×1023 budget).
- The ram7 base-bank *stock-parity* rewrite (qid1 column) is NOT needed for the wedge and
  was not landed (the blanket-7 steers all DN traps to one queue, which is fine with
  accounting off; per-class spreading is a QoS nicety for later).
- `ip link set sw down` with active offload HUNG the device (REPL dead → DTR recovery) —
  same fragility class as the known rmmod hang; avoid bouncing the conduit.

## I. Honest caveats

- bit6's official semantics are undocumented (no public datasheet); "cpuDn out-buffer
  charge-accounting enable" is the behavioral characterization from the live bisect
  (leak↔level, both directions, twice). It could plausibly gate out-buffer accounting
  more broadly (e.g. also the DN LAN-port egress queues) — no adverse effect appeared in
  line-rate sustained downloads or storms, and the ram1 oracle shows all queues flat.
- The post-storm lan4 outage attribution (modem AP wire→WiFi) rests on: host→modem clean
  + device counters clean + frames arriving (smac4/trap +1:1) + replies 80-100% lost +
  spontaneous ~1-4 min recovery + device→host also failing during the window. A wired
  host↔lan4 path would prove it conclusively; this rig doesn't have one spare.
- `qmg_up_trap` stayed 0 all session (UP offload from build #492 holds).
