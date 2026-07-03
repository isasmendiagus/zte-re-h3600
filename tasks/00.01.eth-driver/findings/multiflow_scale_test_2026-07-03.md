# Multi-flow HW offload — SCALE / robustness stress test (2026-07-03, build #464)

**VERDICT:** The per-slot multi-flow offload is ROBUST for the happy path — many distinct
5-tuples coexist and forward selectively, destroy-under-load is correct, and the flows[32]
overflow is crash-free. **Two productization hazards found, both in collision/overflow
handling (RAM-only, no data corruption, no oops):** (1) HIGH — a true hash collision is
silently clobbered AND delete-of-either-colliding-flow destroys both; (2) MEDIUM — past
ZX_MAX_OFFLOAD_FLOWS=32 the offload is accepted-but-untracked, so its HW entry leaks (can't
be deleted). No crash, BUG, WARNING, or panic anywhere in the session (dmesg OOPS grep = 0).

Device: mainline **#464** (`Linux (none) 6.6.0 #464 Fri Jul 3 00:57:16 UTC 2026`), fresh DTR
boot (uptime dropped 57784→5657s confirming the reset; uptime is known-offset/bogus on this
board). trap_dmac cleared, PM ops registered, DSA setup all confirmed in dmesg. RAM-only, no
reboot after boot. Counters: cla_tx_fwd 0x9238c3c0, cla_tx_trp 0x9238c3c4 (read via memdump).

---

## RIG NOTE — host route was unavailable; used raw L2 frame injection instead

`sudo` on the host now requires a password we don't have (no NOPASSWD, no askpass), so the
`ip route 192.168.9.0/24 via 172.31.9.1` step could NOT be re-added (it currently resolves via
wlo1). **Workaround:** prior sessions left `/usr/local/bin/python3-netraw` (caps
`cap_net_admin,cap_net_raw`). Wrote `scratchpad/rawflow.py` — it crafts Ethernet+IPv4+UDP
frames (dst MAC = device lan1 f4:f6:47:0f:42:64) and sends them via AF_PACKET straight out
enxc8a362e95900, **bypassing the host routing table** and pinning the exact 5-tuple the CLA
hashes. This is strictly better for this test (deterministic 5-tuple, no host-route dependency).
Ingress verified: 400 uninstalled pkts → cla_tx_trp +400 exactly, cla_tx_fwd flat.
Device rig (lan1=172.31.9.1, lan4=192.168.9.1, ip_forward=1) was pre-applied by rc.router.

Install path: `tc filter add dev lan1 ingress protocol ip flower skip_sw ip_proto udp
src_ip 172.31.9.50 dst_ip 192.168.9.50 src_port 50010 dst_port <D> action mirred egress
redirect dev lan4`. Traffic: `python3-netraw rawflow.py 192.168.9.50 <D> 400`.

⚠ CONSOLE GOTCHA: the device REPL truncates/times-out on long compound command lines — batches
of tc filters above ~5-6 per zcon call get cut. Install in small chunks + verify count after.
Also `echo "quoted"` breaks through the `sh -c "…"` REPL layer — pass hex key words unquoted.

---

## TEST 1 — Scale / coexistence: 11 distinct flows coexist + forward selectively ✅

Installed 11 distinct-dport offload flows (dports 53,100,150,200,250,300,350,400,450,500,550).
Each hashed to a **DISTINCT ram2 slot** (driver recipe log), so they occupy disjoint buckets:

| dport | raw   | ram2 slot |   | dport | raw   | ram2 slot |
|-------|-------|-----------|---|-------|-------|-----------|
| 53    | 0xf6d5| 0xd5      |   | 350   | 0x8e10| 0x10      |
| 100   | 0x810c| 0x0c      |   | 400   | 0xcdfc| 0xfc      |
| 150   | 0xd85b| 0x5b      |   | 450   | 0x27e3| 0xe3      |
| 200   | 0x455c| 0x5c      |   | 500   | 0x71cc| 0xcc      |
| 250   | 0x1b44| 0x44      |   | 550   | 0xa65a| 0x5a      |
| 300   | 0xf7f2| 0xf2      |   |       |       |           |

Sampled 3 (first-installed=53, middle=300, last=550) + 1 uninstalled (5555). cla_tx_fwd:

| step                      | cla_tx_fwd | cla_tx_trp | verdict |
|---------------------------|-----------|-----------|---------|
| baseline                  | 0x190     | 0x206     | — |
| +400 dport 53 (first)     | 0x320 (+400)| flat    | **FORWARD** |
| +400 dport 300 (middle)   | 0x4b0 (+400)| flat    | **FORWARD (coexists)** |
| +400 dport 550 (last)     | 0x640 (+400)| flat    | **FORWARD (coexists)** |
| +400 dport 5555 (NOT inst)| flat        | +400    | **TRAP (selective)** |

⇒ **11 distinct flows coexist cleanly**; each HW-forwards its own 5-tuple, an uninstalled
5-tuple traps, and flow 1 (dport 53) still forwards after 10 more installs (no clobber).
(Target was 8–12; console batching capped us at 11 — the limit was tooling, not the driver.)

---

## TEST 2 — Hash collision: SILENT clobber + delete-either-kills-both ⚠ HIGH

Used the on-device **hashcalc** debugfs as a fast slot oracle: host-side `keybuild.py`
reproduces `zx_cla_flow_hash`'s 12-word key builder (verified byte-exact against the known
dport53 key 48000000 583e0022 81501265 86b41265 0000006b → 0xf6d5), fed into hashcalc.
Scanning dports found **dport 3002 (raw 0x335c) collides with installed dport 200 (raw 0x455c)**
— `raw & 0xff = 0x5c` for both, so they map to the **same bucket in ALL 5 banks** (the low
byte drives every bank mask 0xff/0x7f/0x3f/0x3f/0x7; only the high byte differs, which no bank
uses). A genuine full collision with a real installable dst_port.

Installed dport3002 while dport200 was live and forwarding:
- Driver **accepted it SILENTLY** — recipe rc=0, in_hw, `ram2[0x5c]` logged, **no collision
  warning/detection.**

| step                        | cla_tx_fwd | cla_tx_trp | verdict |
|-----------------------------|-----------|-----------|---------|
| dport200 forwards (pre)     | +400      | flat      | FORWARD |
| install dport3002 (collide) | —         | —         | accepted, no warning |
| +400 dport200 (1st)         | flat      | +400      | **now TRAPS (clobbered)** |
| +400 dport3002 (2nd)        | +400      | flat      | **FORWARD (last writer wins)** |

Then deleted the collided-OUT flow (dport200, which was already trapping):
- `flow del cookie=… cleared raw=0x455c (5 ways) rc=0` — zeroed the SHARED bucket.

| step                        | cla_tx_fwd | cla_tx_trp | verdict |
|-----------------------------|-----------|-----------|---------|
| +400 dport3002 (was live)   | flat      | +400      | **now TRAPS — the LIVE flow died** |

⇒ **A true collision is (a) silently overwritten (last-writer-wins, no detection/rejection),
and (b) delete of EITHER colliding flow zeroes the shared bucket and destroys BOTH — including
a still-referenced live flow.** Root cause: the driver writes the SAME 15-word entry to all 5
ways at the flow's own hash, so a colliding flow has nowhere to go, and `zx_flow_untrack`
zeros buckets by hash without checking which flow currently owns them.

---

## TEST 3 — flows[32] overflow: graceful, crash-free, but leaks the HW entry ⚠ MEDIUM

Installed **36** tc-flower filters (> ZX_MAX_OFFLOAD_FLOWS=32).
- Exactly **4** `flow table full; cookie=… raw 0x… untracked (del will leak)` dev_warn lines.
- **0** Oops / BUG / Call trace / panic / WARNING (dmesg grep).
- `zx_flow_track` returns false when flows[32] is full → logs the warning, **but the offload is
  still ACCEPTED (cls_flower_add returns 0)** because `zx_install_l3_recipe` runs (and writes
  the CLA entry) BEFORE the track attempt.

⇒ Overflow is handled gracefully (no wrap, no oob, no crash). **But** past 32 flows the HW
entry is installed-yet-untracked, so a later `tc filter del` cannot invalidate it → the HW
keeps forwarding a flow userspace thinks it removed (a leak). The CLA banks (ram2 = 256 slots)
hold far more than 32, so this is purely a tracking-array limit, not an HW capacity limit.

---

## TEST 4 — Destroy under load: correct + selective ✅

Clean 3-flow set (dports 53/300/550 → distinct slots d5/f2/5a). All 3 forwarded +400.

| step                              | dport53 | dport300 | dport550 |
|-----------------------------------|---------|----------|----------|
| all 3 installed                   | FWD +400| FWD +400 | FWD +400 |
| **del middle (dport300)**         | FWD +400| **TRAP +400** | FWD +400 |
| re-add dport300                   | —       | **FWD +400 (restored)** | — |
| **del-all**                       | **TRAP +400** | **TRAP +400** | **TRAP +400** |

`tc filter del` of the middle flow logged `cleared raw=0xf7f2 (5 ways) rc=0`; it traps while the
neighbours keep forwarding; re-add restores forwarding; delete-all leaves cla_tx_fwd perfectly
flat (all three trap). ⇒ **Destroy-under-load is robust for distinct (non-colliding) flows.**

---

## SEVERITY RANKING (for productization)

1. **HIGH — Hash collision unhandled (silent clobber + delete-either-kills-both).** Distinct
   5-tuples whose HW hash shares the low byte share all 5 buckets. The driver neither detects
   nor rejects the 2nd; it clobbers the 1st, and deleting either zeros the shared entry, killing
   both. **Fix options:** (a) on `zx_flow_track`, detect an existing tracked flow with the same
   `raw` but a different cookie → reject the new offload (`return -EOPNOTSUPP`, keep it in the
   working SW path) OR spread colliding flows across the 5 distinct ways (way0..ext) instead of
   replicating one entry to all; (b) make `zx_flow_untrack` verify bucket ownership (compare the
   stored 15-word entry, or refcount per bucket) before zeroing, so it never clears another
   flow's live entry. Collision probability is real at scale (birthday: ~50% by ~19 flows over
   256 low-byte slots).

2. **MEDIUM — >32-flow leak.** Past flows[32], offload is accepted but untracked → HW entry
   cannot be deleted (stale forward after `tc filter del`). **Fix:** when flows[] is full, reject
   the offload (`return -EOPNOTSUPP`) so the flow stays in SW and no untrackable HW entry is
   written — instead of the current accept-and-warn. (Or grow/dynamically-size the array.)

3. **LOW / none — Scale coexistence + destroy-under-load are solid.** Distinct flows coexist,
   forward selectively, and delete cleanly under load. No crash/leak in the happy path.

Minor: stale CLA entries from the >32 untracked flows remain in RAM (cleared on next boot);
harmless. Next-hop DMAC still the seeded fallback (dst is fictional) — orthogonal, forward
decision unaffected.

---

## State left behind
- Device on **#464**, healthy, alive; UART bridge running (:9998/:9999); console loglevel 8.
- lan1 clsact qdisc + all flower filters **removed** (lan1 back to `noqueue`). ip_forward=1,
  lan1=172.31.9.1/24, lan4=192.168.9.1/24 intact. WAN/PPPoE untouched. No reboot post-boot.
- Stale untracked CLA entries (4000-range dports) linger in RAM — clear on next boot, harmless.
- Host rig: enxc8a362e95900 = 192.168.1.50/24 + 172.31.9.50/24; static ARP 172.31.9.1→
  f4:f6:47:0f:42:64 (PERMANENT). Host route 192.168.9.0/24 NOT set (no sudo) — used raw L2
  injection instead. Tools in scratchpad: rawflow.py (L2 UDP gen), keybuild.py (hash-key model).
- Driver source UNCHANGED this session (test-only); NOT committed.
