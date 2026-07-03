# Post-trap_dmac CLA submit regime — decisive measurement (2026-07-02)

**Question answered:** on the committed #452-era driver (branch `phase6-hw-offload`,
HEAD `a13779544`, WITH `zx_eth_clear_spa_trap_dmac`), does the CLA submit counter
`acl_required` climb under a routed test flow, and what is the precise CLA
descriptor trap-reason?

**Answer: acl_required CLIMBS 1:1 with the flow, and the reason is 0x49 (OTHERS,
through-CLA) — NOT 0x54 LOOK_UP_MISS.** The trap_dmac fix fully unlocked CLA
submission, and the lookup does not even miss: packets complete classification
with the catch-all "forward-grade" reason yet are still trapped to CPU.

## Build / boot provenance
- Rebuilt from the working tree at `a13779544` (contains the SPA trap_dmac clear).
  Kernel banner of the booted image: `Linux version 6.6.0 ... #456 Thu Jul 2
  19:04:20 UTC 2026` — fresh build, fresh DTR boot (host /tmp had been wiped;
  rig fully re-staged: `/tmp/initramfs_extract` from
  `tasks/00.01.eth-driver/initramfs/` + `scripts/stage_userland.sh`, uart_bridge
  restarted, in.tftpd restarted serving `ZTE/tftp` — note
  `tools/host/tftpd_start.sh` still points at the stale `zxic/tftp` path).
- Boot log contains: `SPA trap_dmac filter cleared (match stock; enables HW L3
  forward)` at t=66.09s ✓ (the previously-running #453/a41efb318 lacked this).
- Live confirmation of the clear: `0x921d41a0/a4/a8/ac` all read **0x00000000** ✓.
- `build_slotA.py` NAND-padding step now FAILS (`slotA body 0xe3fbef exceeds
  0xc00000`) — image grew past the NAND write budget. Irrelevant for RAM/TFTP
  boot (`tftp/zImage_dtb.uimg` is built before that step) but NAND flashing
  needs a diet or a bigger NAND_WRITE_SIZE before it works again.

## Rig
- Host `enxc8a362e95900` (192.168.1.50 TFTP + 172.31.9.50/24 test) → device
  **lan2** (PP ingress port2 / inport 3). Host route `192.168.9.0/24 via 172.31.9.1`.
- Device (RAM-only, via REPL): moved 172.31.9.1/24 from lan1 (rc.router default)
  to lan2, lan2 up (1Gbps/FD), `iptables -A FORWARD -i lan2 -o lan4 -j ACCEPT`,
  ip_forward=1, lan4=192.168.9.1/24 (rc.router). Ping host↔lan2 OK.
- Flow: UDP **172.31.9.50:50010 → 192.168.9.50:53**, 400 datagrams (run 1) +
  3000 datagrams (run 2), one-way ingress.

## The numbers

| register | BEFORE | after 400 pkts | after +3000 pkts | delta total |
|---|---|---|---|---|
| `acl_required` 0x9238c3b8 (hi16) | 0x0000 (0) | 0x0190 (400) | 0x0d48 (3400) | **+3400 = exactly the 3400 datagrams sent** |
| `cla_tx_fwd` 0x9238c3c0 | 0x0 | 0x0 | 0x0 | **0 — never forwards** |
| `cla_tx_trp` 0x9238c3c4 | 0x1f (31) | 0x1bf (447) | 0xdaf (3503) | +3472 (= 3400 flow + ~72 background) |
| `hw_trap` 0x9234c060 | 0x1d (29) | 0x1ba (442) | 0xda5 (3493) | +3464 |

(raw `acl_required` reads 0x01900190 / 0x0d480d48 — low16 mirrors hi16 here.)

## desIn latch (0x9238c3e0 base; word2 = 0x9238c3e8, action_rsn = bits[29:23])

Mid-flow, 5 independent reads across both runs (flow = ~100 pps, dominating all
other ingress ~100:1); the latch is demonstrably LIVE (desIn[0]/[1] change on
every read) yet word2/word3 are rock-stable during the flow:

| read | desIn[0] 0x3e0 | desIn[1] 0x3e4 | desIn[2] 0x3e8 | rsn=(w2>>23)&0x7f | desIn[3] 0x3ec | l3_en (bit6) |
|---|---|---|---|---|---|---|
| flow r1 | — | — | 0xa4800000 | **0x49** | 0x82610841 | **1** |
| flow r2 | 0x2010c06a | 0x6d43ff03 | 0xa4800000 | **0x49** | 0x82610841 | **1** |
| flow r3 | 0xe837006a | 0x6d43ff06 | 0xa4800000 | **0x49** | 0x82610841 | **1** |
| flow r4 | 0x8013c06a | 0x6d43ff02 | 0xa4800000 | **0x49** | 0x82610841 | **1** |
| idle 1  | 0xa8250056 | 0xaac3ff04 | 0xa5300000 | 0x4a | 0x82610803 | 0 |
| idle 2  | — | — | 0x94a00000 | 0x29 | 0x82610805 | 0 |

- Flow packets: **action_rsn = 0x49 (OTHERS — the "through-CLA / catch-all →
  forward" code, the one stock shows while forwarding)**, and **l3_en = 1**.
- Idle/background (ARP/broadcast) packets latch different signatures (0x4a,
  0x29, l3_en=0) — proving the flow rows are really the UDP flow, not a stale
  or shared-alias reading.
- gparsehashkey latch 0x9238c260..27c mid-flow (for the record): 0x4b000000
  0xc5d39000 0x1000b200 0x00b88a00 0x8001eee0 0x87e88022 0x1265583f 0x12658150.

## VERDICT — a THIRD regime, sharper than either briefing option

- (A-half confirmed) **`acl_required` CLIMBS, exactly 1:1** → the SPA trap_dmac
  clear DID unlock CLA submission. The pre-fix "never submitted / l3_en=0"
  dead-end is definitively over on the committed build.
- (A-half refuted) **The reason is NOT 0x54 LOOK_UP_MISS. It is 0x49 OTHERS with
  l3_en=1.** The earlier LOOK_UP_MISS latch readings do not describe the current
  committed build's flow regime.
- Interpretation: the flow is submitted, classified, and completes the CLA with
  the same reason code stock shows on forwarded traffic — but the VERDICT is
  still trap (`cla_tx_fwd`=0, `cla_tx_trp`/`hw_trap` climb 1:1). The gate is
  therefore **the action/verdict bound to what the lookup resolves to** (the
  boot-replayed CLA RAM entries / default action are trap-to-CPU — consistent
  with the known trap-all conduit behavior), NOT a hash-bucket placement miss
  and NOT a submission gate.

## Next driver step this decides
Skip any further "why doesn't it submit / why does the hash miss" work. The
lookup machinery is fine end-to-end. The remaining work item is per-flow
verdict programming: install/flip a CLA entry whose ACTION is forward (correct
egress + next-hop rewrite) for the 5-tuple — i.e. the Stage-2b offload binder
path (HW hash engine 0x9238c2c0/c2c4/c2fc computes the slot; write the ram2
forward-action entry with the correct inport byte) — then re-run this exact
measurement and watch `cla_tx_fwd` move off 0.

## State left behind
- Device: mainline #456 running from RAM, REPL alive, UART bridge up
  (:9999/:9998), in.tftpd serving `ZTE/tftp` on 192.168.1.50. All device
  changes RAM-only. WAN/PPPoE untouched.
- Host keeps 172.31.9.50/24 + the 192.168.9.0/24 route on enxc8a362e95900.
- `/tmp/zcon.py` recreated; `/tmp/initramfs_extract` re-staged; stripped #456
  `zx279128-eth.ko` copied to BOTH staging trees.
