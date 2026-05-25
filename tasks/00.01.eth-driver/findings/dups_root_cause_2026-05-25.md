# DUPs root cause analysis — 2026-05-25 (post-tcpdump)

Two findings change the playing field. Both came out of finally running
`tcpdump -e` on the host (the experiment Agent C said we should have run
hours ago).

## Finding 1 — The DUPs we'd been chasing for hours were caused by my own fix

For most of the day we'd been measuring "158 DUPs by RUN3 of 50 pings"
and theorizing about switch flood, MAC FDB lookup, etc. After reverting
the `zx_sbrg_set_unknown_unicast_flood_policy(e, 0x20)` call I'd added
to probe in commit `ff0327bdd`, the DUPs dropped to **zero** in the
short-ping verification (30 pings, 9 s) — 30 requests, 2 replies, ratio
1:1.

What happened: there's already an init at L1831 in `zx279128-eth.c`
that writes `PP[0x8340] = 0xff5555ff`. Per Agent 1+4 RE that is the
stock-matching state:

| Bits | Field | Value | Meaning |
|---|---|---|---|
| 0..7   | (reserved low byte) | 0xff | (vendor magic, do not touch) |
| 8..23  | PKTDEAL (sbrag 0x35) | 0x5555 = 0b01 per port × 8 | "normal lookup" each port (NOT "flood" — 1 means lookup, 3 means flood) |
| 24..31 | FWD     (sbrag 0x36) | 0xff = bit per port × 8 | per-port forward enable |

My `flood_policy(e, 0x20)` overlaid `0x20000000` on bits 24..31, leaving
PKTDEAL alone. That set "only CPU port has forwarding enabled"
which, combined with PKTDEAL=lookup, means LAN-port lookups had no
fwd-enabled destination → fell through to the unknown-DA fallback
action. The fallback action is configured to FLOOD by default. So my
"fix" inadvertently sent every unicast through the flood path.

**Commit `1abc0c6f7`** removes the bad call.

## Finding 2 — There's a SECOND, larger amplification source

After the revert + a 100-ping burst test, the picture became more
complex:

| Test | Sent | Replies in pcap | Amplification |
|---|---|---|---|
| 30 pings, 0.3 s interval (warm, short) | 30 | 2  | **1:1** |
| 100 pings, 0.1 s interval | 100 | 848 | **8.48x** |
| 20 pings, 1.0 s interval | 20 | 385 | **19.25x** |

The amplification is HIGHER at slower ping rates, not lower. That
contradicts the "TX desc replay" hypothesis (which would scale with
desc-ring saturation, i.e. with rate).

Driver STATS during burst:
```
drv:rx=999 rxlb=49 tx=877 napi=142 irq=142 (10 s window, 100 pings sent)
```

We're delivering **999 RX frames** to the IP stack — ~10x more than the
input rate. Loopback drops caught only 49. The other 950 are being
re-injected into the IP stack, which generates a reply for each →
877 TX → 848 wire egress. The math closes: **the amplification is
upstream of TX, in the RX path.**

Most likely mechanism: the switch hairpin (CPU egress -> CPU ingress
via the CPU port loop) re-delivers our own ICMP replies. The
LOOPBACK-drop heuristic compares `src_mac == sw_dev->dev_addr` but the
SW block REWRITES src_mac on egress (it stamps the egress port's MAC,
not the original CPU-port MAC), so the heuristic misses most loops.
Linux's IP stack interprets the looped frame as either:
- a duplicate-IP-with-our-own-address (silently ignored), or
- a new echo *request* from us to host (generates yet another reply), or
- ARP confusion

…depending on the frame content. The replies pile up over time → 19x
amplification when ICMP traffic is slow enough for the loop to settle
into a steady state.

## What the desc-invalidate fix DID accomplish

Even though it didn't kill the amplification, the post-kick clear of
desc[11] bit 5 in commit `1abc0c6f7` is correct hygiene per stock
behavior:
- Stock `pon_tm_data_raw_send` (decomp_all_plat_zxylzb_9128S.c:6596)
  sets bit 5 via `desc[11] = (desc[11] & 1) | 0x20`.
- Stock `pon_tm_get_next_txdesc` (:6687) checks outstanding-TX count and
  refuses TX if the ring is full.
- Stock `pon_tm_check_tx_done_nolock` (:6360) reads `tm[0x10058]` to
  drain the outstanding counter.

We do none of those. Without the invalidate, the burst test was 10x;
with it, 8.48x. The drop is small but consistent.

## What stays unexplained

- The slow-rate amplification (19x for 1-s ping) — the more time
  between ours pings, the *worse* the amplification, suggesting a
  steady-state feedback loop that runs for as long as we give it.
- `tx_done` HW counter (`tm[0x10058]`) stays at 0 in STATS — HW never
  reports any TX completion, even though wire emissions ARE happening
  (we see them in pcap). This means either:
  - Wrong register (0x10058 is not the LAN done-counter)
  - HW counter requires explicit ack we're not doing
  - HW emits but doesn't classify them as "done" (maybe each emission
    is a "still pending" cycle, not a "consumed" event)
- Why does the 30-ping fresh test show 1:1 ratio when subsequent tests
  show 8-19x? Possibly because the switch FDB hasn't auto-learned the
  host MAC's egress port yet → no hairpin → no loop. Once it learns,
  the loop kicks in and stays in steady state.

## Recommended next steps (post this commit)

1. **Tighten the LOOPBACK heuristic**: drop ALL replies whose dst_mac
   == sw_dev->dev_addr (i.e., anything that ends up addressed back to
   us). This is independent of how the switch rewrites src_mac.
2. **Verify with `tcpdump -e` on a DIFFERENT host** (or `wlan0` of a
   second machine) that the wire-side amplification really is 8-19x
   and not an artifact of host-side NIC behavior.
3. **Find the right TX-done register**. Read 0x10068 (DN counter) in
   STATS, or scan TM register space for a counter that increments per
   wire emit. Without this, we have no way to track TX completions and
   the desc-invalidate fix is partial at best.
4. **Test with the LOOPBACK heuristic disabled entirely** — paradoxically
   that may IMPROVE numbers because right now we drop only 49/999
   loops; the other 950 still cause RX→TX feedback. Without the
   heuristic, the IP stack would do its own dup-check and silently
   drop based on the IPID/checksum. Worth a one-cycle experiment.

## Files / commits

- Code: `1abc0c6f7` — eth: revert broken flood_policy + add desc invalidate
- Previous code state (where the broken flood_policy was added):
  `ff0327bdd`
- Today's full session summary: `tasks/00.01.eth-driver/findings/session_2026-05-25_FULL.md`
- pcap files referenced (not in git): `/tmp/dups.pcap`, `/tmp/run_a.pcap`,
  `/tmp/run_b.pcap`, `/tmp/burst.pcap`, `/tmp/slow.pcap`
