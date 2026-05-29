# MACRO / red-team review — CPU→LAN TX egress wall

**Date**: 2026-05-28
**Reviewer brief**: fresh-eyes, challenge core ASSUMPTIONS, not registers.
**Scope**: analysis & strategy only. Did not touch device/build/git.

---

## Reading-of-record

I could not find the specific files the task brief cited
(`old_working_tx_commit_re.md`, `egress_contradiction_universal_2026-05-28.md`,
`stock_egress_netdev_id_re.md`, journey entries #9–#16, etc.). They are not on
disk. The newest committed state is `STATE.md` dated **2026-05-22** (stops at
iter 8: "RX dead, TX partial") and the `00.01.eth-driver/findings` set dated
**2026-05-24**. So this review is grounded in what exists, plus the brief's
summary of the later iterations.

**Macro flag #0 (process):** the team is iterating faster than it is
check-pointing. A red-team can't audit findings that aren't written down, and
*you* can't either, three weeks from now. If 15 iterations happened, ~7 of them
left no durable artifact. That alone is a reason you feel like you're going in
circles — you may be re-deriving the same dead ends.

---

## The single most important thing I found

`tasks/00.01.eth-driver/findings/ping_bidi_works_2026-05-24.txt` — the file
that "proves" bidi — **disproves it on inspection.** The tcpdump shows:

- Every ICMP reply (id 487 seq 1–10, id 488 seq 1–3) arrives in **one ~1ms
  burst at t=50.620xxx**. Real round-trips over a 16ms-RTT link cannot land 13
  replies inside 1ms. This is a **buffer being flushed**, not a link working.
- id 489 seq 3 appears **twice** (DUP). After the burst, the host gets
  **nothing** — it keeps re-ARPing and re-sending seq 4/5 with no answer.

That is the signature of a switch that **flooded a backlog of stale frames
once** and then went quiet. Combined with "40% loss + 70 DUPs", "0–60% of
attempts", "ARP cycles REACHABLE→FAILED" — **TX egress has never actually
worked in a sustained, directed way.** You have been tuning the statistics of a
flood, calling the lucky leaks "success", and then trying to remove the loss/DUPs
that are *intrinsic to flooding*. You are optimizing noise.

**Implication:** stop trying to "reduce the 40% loss." That framing assumes a
mostly-working path. Reframe to: *"directed unicast egress from CPU to one known
port has 0 confirmed successes."* That is the true baseline, and it is honest.

---

## Ranked wrong-assumptions + one cheap experiment each

**1. "TX basically works, we're polishing it." — FALSE; it has never worked.**
Cheap test: send **1000** ICMP requests at 1/sec; count replies whose timestamps
are >5ms apart (i.e. real RTTs, not a burst). If the count of *temporally
isolated* replies is ~0, the link is flooding, full stop.

**2. The host may be cabled to a different physical jack than `lan_up_port=0`/MAC0.**
4× RJ45 → PHY/MAC 0–3; you hardcode port 0. The brief's own netdev oracle says
the carrier-up copper port is eth3/MAC2. **You may be egressing to a dead jack
and reading the wrong counter.**
Cheap test: read `BMSR.LinkStatus` (`zx_mdio_read(uni_phy[i],1)`) for **all 4**
PHYs. The one(s) with link = where the cable is. If that isn't port 0, every TX
experiment so far targeted an unconnected port.

**3. RX↔TX symmetry is assumed but the paths are asymmetric — and RX is the trustworthy oracle.**
RX *demonstrably* delivers the host's frames (you see src=c8:a3:62:e9:59:00).
That proves: clocks, the connected PHY/MAC, BMU, and the CPU-punt path all work
**for the port the host is on.** TX failing while RX works on the *same wire*
means the problem is **egress-direction-specific**, not link/clock/DMA.
Cheap test: from the RX descriptor of an inbound host frame, **read which port
HW tagged as ingress.** Egress to *that exact port number* — not 0, not a guess.
RX already told you the answer; you've been ignoring its testimony.

**4. The egress measurement is via registers that have lied twice; trust the wire instead.**
Two TM address-map errors + a /proc/kmsg drop bug mean "frame reached sw_fwd but
not SOPC send2smac2" is built on reads you've already caught being wrong.
Cheap test: **tcpdump on the host is the only oracle that matters.** Put the
host NIC in promisc, inject ONE uniquely-tagged frame (unusual ethertype + magic
payload), grep the capture. Wire-present or wire-absent. Delete register-counter
reasoning from the egress question entirely until a frame is confirmed/denied on
copper.

**5. The FDB you seed is the wrong table, and bulk replay clobbers it anyway.**
Round-2 review already found `zx_fdb_add`→VLAN/port-membership table, not the
MAC FDB the fabric consults; and `fpga.bin` replays *over* those buckets with
another unit's zeros. So directed unicast egress was **never possible** — the
fabric has no route for the dst MAC and falls back to flood (hence the burst).
Cheap test: **disable bulk `fpga.bin` replay** and re-run #1. If loss/DUP
behavior changes at all, replay is half your variance. (Highest-leverage single
change; removes ~11k unknown side-effects.)

**6. `txtest` validity: dst=host-MAC may be the wrong trigger.**
If the fabric has no FDB entry for host-MAC, a *unicast* dst guarantees the
flood-or-drop path. The honest first target is **broadcast** (dst=ff:ff:ff:ff:ff:ff),
which has a defined egress (all member ports) independent of FDB state.
Cheap test: inject a broadcast frame, tcpdump host. If broadcast egresses but
unicast doesn't → it's purely an FDB problem, not a TX-engine problem. This
cleanly splits "TX engine broken" from "routing/FDB broken."

**7. A port-level egress gate (greg_port_closed / cpu_queue_ratelimit) may be off.**
Never written. Default could be "closed" / rate=0 → counters increment, wire
silent. Plausible but **lower priority** than 2/3/6 because it's another
register hunt; only pursue if #6 shows the TX engine itself is dead.

---

## The one assumption to kill first, and why

**"There is a working TX baseline to improve."** There isn't. Reframe the goal to
*"egress one confirmed unicast/broadcast frame to the port the host is actually
on, with tcpdump as the only judge."* The cheapest decisive experiment is the
**combination of #2 + #3 + #6**: read all 4 PHYs for link, read the ingress-port
tag off a real RX frame, then inject **one broadcast** frame and watch the host.
That triangulates "which port" and "engine vs FDB" in a single sitting, using
the wire (not registers) and RX (not guesses) as oracles.

If broadcast egresses on the linked port but unicast doesn't → it's 100% the FDB
(do #5 properly: real `sbrg_add_mactable` via the indirect protocol, with replay
disabled). If even broadcast doesn't egress on the linked port → the TX engine
or a port gate is the wall (#7), and *that* is when register archaeology earns
its keep — but not before.

**Pivot discipline:** round-2 already set a 3-experiment budget before pivoting
to the 4.1 stockport. By the brief's count you're ~12 experiments past that line.
Honor it. If #2/#3/#6 don't put a frame on the wire, the disciplined call is to
stop hand-porting and bring up the vendor 4.1 kernel as the reference that
*does* egress — then diff against it — rather than a 16th register poke.
