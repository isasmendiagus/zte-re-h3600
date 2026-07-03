# Forward entry under the submitted regime — cla_tx_fwd stays 0 (2026-07-02)

**Question:** now that the SPA trap_dmac clear makes the CLA submit 1:1
(acl_required climbs, action_rsn=0x49, l3_en=1 — see
`post_trapdmac_submit_regime_2026-07-02.md`), does installing the known-good
forward recipe (fill520 ram2 entry + ram0[9] arm + PM next-hop/flow_info/
sub/cmd tables) make the CLA actually FORWARD?

**Answer: NO. `cla_tx_fwd` stays EXACTLY 0 with the full recipe installed,
readback-verified before AND after the flow. acl_required keeps climbing 1:1,
cla_tx_trp absorbs every packet, and the desIn latch is BYTE-IDENTICAL to the
no-entry run (word2=0xa4800000 → action_rsn=0x49, l3_en=1). The CLA verdict is
completely insensitive to the hash-RAM/PM contents in this regime — install
decay is ruled out.**

## Provenance (same live boot as the submit-regime measurement — NO reboot)
- Kernel banner `#456 Thu Jul 2 19:04:20 UTC 2026`, tree `a13779544`, uptime
  continuous (uart timestamps 12693→17543 s across this session).
- Rig unchanged: host `enxc8a362e95900` 172.31.9.50/24 → device lan2
  172.31.9.1/24 (PP inport 3); lan4 192.168.9.1/24; ip_forward=1; host route
  `192.168.9.0/24 via 172.31.9.1`. Flow = UDP 172.31.9.50:50010 →
  192.168.9.50:53 (host python, bound source port, no sudo needed).
- All writes via driver debugfs (`/sys/kernel/debug/zx_eth/…`), RAM-only.

## Install (all readback-verified)
1. **fill520** (all 520 hash buckets ram2[0..ff] ram3[0..7f] ram4/5[0..3f]
   ram6[0..7]):
   `echo '03005044 fa11c000 00000608 80000000 11000049 32ac1f00 32c0a809 35c35a09' > fill520`
   → `fill520: wrote entry (8 words) to 520/520 hash buckets`.
   clapeek ram2[5], ram2[0xc7], ram2[0xff], ram3[0x7f], ram6[7] all returned
   the entry byte-exact. (Note: task briefing said "clapeek 0x1ff" — ram2 only
   spans 0x100 entries; verified the far banks instead.)
2. **CLA ram0[9]**: pre-state was `93929190 97969594 9b9a9998 9f9e9d9c 00150051`
   (bit8 CLEAR). Wrote word4=**0x00150151** preserving words0-3; readback OK.
3. **CLA ram1[0x90]** generic boot rule: ALREADY PRESENT (driver-installed):
   `22038608 000058a1 00000000 00000000 f00ff000 ffffffff ffffffff 0fffffff`
   + words14/15 `00700000 00092492`. Untouched.
4. **PM tables** (pmwrite, pmpeek-verified):
   - ram1[5] = `c0a80932 bd22b42b 0000cc29` (next-hop 192.168.9.50, MAC
     cc:29:bd:22:b4:2b)
   - ram0[5] = `0de80005 0014035c` (flow_info, next_hop_idx=5)
   - ram6[5] = `00000005` (sub_ram)
   - ram3[5] = `00800000` (cmd_ram last_cmd)

## The numbers (two bursts: 400 pkts @40pps, then 300 pkts @25pps)

| register | BEFORE install | after 400 | after +300 | delta |
|---|---|---|---|---|
| `acl_required` 0x9238c3b8 (hi16) | 0x0d48 (3400) | 0x0ed8 (3800) | 0x1004 (4100) | **+700 = exactly the 700 sent (1:1 held)** |
| `cla_tx_fwd` 0x9238c3c0 | 0 | 0 | 0 | **0 — NEVER moves** |
| `cla_tx_trp` 0x9238c3c4 | 0xdd6 (3542) | 0xf7b (3963) | 0x10bc (4284) | +742 (700 flow + ~42 bg) |
| `hw_trap` 0x9234c060 | 0xdc2 (3522) | 0xf62 (3938) | 0x10a0 (4256) | +734 |

## desIn latch mid-flow (3 independent reads across both bursts)
All three reads identical and identical to the NO-ENTRY runs:
- desIn[0]/[1] live (0xf840806a / 0x6d43ff1f on read 1)
- desIn[2] 0x9238c3e8 = **0xa4800000** → action_rsn=(w2>>23)&0x7f = **0x49
  (OTHERS)** — unchanged by the entry install
- desIn[3] 0x9238c3ec = **0x82610841** → **l3_en=1** — unchanged
- desIn[4] 0x9238c3f0 = 0x00001c18, desIn[5] 0x9238c3f4 = 0x00005444 (stable)

## Persistence proof (post-flow, rules out install decay)
Re-peeked AFTER the 400-pkt burst: ram2[5] = the full entry byte-exact,
ram0[9] word4 still 0x00150151, all four PM entries byte-exact. Nothing
decayed, nothing was overwritten by the driver during the flow.

## VERDICT
- The recipe that this briefing lineage calls "known-good" does NOT flip the
  verdict on the committed #456 build: **submission works, lookup completes
  (rsn 0x49, not 0x54 LOOK_UP_MISS), but the action executed is still trap**,
  with the forward entry provably resident in every hash bucket and the PM
  chain populated.
- Because action_rsn/l3_en/desIn are bit-identical with and without the entry,
  the packet's classify outcome is NOT being sourced from the ram2 hash match
  at all in this regime — either the hash lookup result is ignored/overridden
  downstream (a global fwd-enable / verdict-mux still in trap-all state), or
  the match happens but its action binding (the 0x49 catch-all path) wins.
  Consistent with `zte-flowoffload-framework` memory: the #444→#452 gate is an
  init-OP / driver-change / CLA-indirect field, not a per-flow entry.
- Ruled out THIS boot: install decay, hash-bucket placement (all 520 filled),
  ram0[9] index_valid arm, PM chain absence, ram1[0x90] rule absence,
  submission, LOOK_UP_MISS.
- Note the entry's w4=0x11000049 carries the historical inport byte 0x49
  (WAN-side default per `hw_forward_two_gate_runbook_2026-06-28.md` STEP 2);
  ingress here is lan2 (PP inport 3). An inport-byte mismatch would normally
  express as LOOK_UP_MISS — which we do NOT see — but a follow-up could try
  the lan2 inport byte to close that residual. The stronger lead remains the
  stock-vs-mainline init-OP / indirect-RAM diff for the verdict mux.

## State left behind (device healthy, no reboot)
- Device still on #456, console REPL + UART bridge (:9999/:9998) alive,
  printk=8. RAM-only changes this session: the CLA fill520 entry in all 520
  buckets, ram0[9] word4=0x00150151, the four PM entries above. Rig
  (lan2/lan4 IPs, iptables FORWARD accept, host addrs/route) untouched.
- Host sender script: scratchpad `sendflow.py` (bind 172.31.9.50:50010).
