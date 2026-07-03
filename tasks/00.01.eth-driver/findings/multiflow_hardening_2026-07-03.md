# Multi-flow HW offload — COLLISION + OVERFLOW hardening: FIXED, booted (#466), retested ✅

**VERDICT: Both productization hazards from the scale test are FIXED in the driver, rebuilt,
DTR-booted (#466), and validated end-to-end on HW.** A colliding 2nd flow is now DECLINED (stays
SW, logged) instead of silently clobbering the 1st; past 32 tracked flows the offload is DECLINED
cleanly (no accept-and-leak); and destroy is ownership-checked (by cookie, zeros only that flow's
own buckets). The distinct-flow happy path is unchanged (8 flows coexist + forward selectively;
destroy-middle + re-add correct). BONUS narrow-bank probe answered: the way0-only check is correct.

Device: mainline **#466** (`Linux (none) 6.6.0 #466 Fri Jul 3 04:07:46 UTC 2026`), fresh DTR boot,
RAM-only, NO reboot after boot. trap_dmac[0] @0x921d41a0 = 0 (cleared), PM ops registered, DSA up,
links up, ip_forward=1, lan1=172.31.9.1/24 lan4=192.168.9.1/24 (rc.router). Counters: cla_tx_fwd
0x9238c3c0, cla_tx_trp 0x9238c3c4. 0 real Oops/BUG/Call-trace/panic in dmesg the entire session.
Rig: host enxc8a362e95900 = 192.168.1.50/24 (tftp) + 172.31.9.50/24; raw L2 injection via
`/usr/local/bin/python3-netraw scratchpad/rawflow.py <dst> <dport> 400` (pins the 5-tuple; host
sudo unavailable so no host route — raw L2 bypasses it).

---

## THE FIX (minimal; only the tracking + install-order logic changed — packer/recipe untouched)

Root design that made a collision fatal before: install wrote the CLA entry FIRST and tracked
AFTER, with no collision check → a 2nd flow with the same bucket clobbered the 1st (last-writer
wins), and `zx_flow_untrack` zeroed buckets by hash so deleting either colliding flow killed both.
Overflow: `zx_flow_track` returned false past 32 but `cls_flower_add` still returned 0 (install ran
before track) → accepted-but-untracked HW entry that `tc filter del` could never invalidate (leak).

The fix moves the decision BEFORE any CLA write and reserves the tracking slot up-front:

### `drivers/net/dsa/zte/zx-dsa.c` (the built-in, HW-TESTED tc-flower path)
- **`zx_flow_reserve(p, cookie, raw)` (new, replaces `zx_flow_track`) — zx-dsa.c:949.**
  Scans `flows[32]` BEFORE the CLA is touched and either records `{cookie, raw}` or declines:
  - returns **`-EOPNOTSUPP`** if another tracked flow (different cookie) already owns raw's CLA
    way0 bucket — i.e. `(flows[i].raw & 0xff) == (raw & 0xff)` (ram2, the 256-slot primary the
    HW resolves on). This is the "same bucket set" test the task specified.
  - returns **`-ENOSPC`** if no free slot and this cookie is not already tracked (table full).
  - REPLACE (same cookie) re-uses the slot, still checking collisions vs all others.
  - on success records `{cookie, raw, used}` so a later reserve sees it and destroy can find it.
- **`zx_flow_release(p, cookie)` (new) — zx-dsa.c:980.** Frees a reserved slot if a subsequent
  HW write fails (error-path cleanup only).
- **`zx_flow_untrack(p, cookie)` — zx-dsa.c:994 (already ownership-checked; kept).** Locates the
  entry BY COOKIE, zeros ONLY that flow's own 5 way buckets (its stored `raw`), frees its slot,
  returns `-ENOENT` if the cookie isn't tracked (so a declined flow's stack-cleanup DESTROY is a
  no-op). With collision-reject in place no two tracked flows share way0, so cookie→zero-its-raw
  never clears another live flow's primary bucket. (Correct by construction — see BONUS below.)
- **`zx_dsa_cls_flower_add` — zx-dsa.c:1131-1152.** Now computes `raw = zx_cla_flow_hash(...)`
  up-front, calls `zx_flow_reserve` BEFORE `zx_ffe_arm`/`zx_install_l3_recipe`; on `-EOPNOTSUPP`
  logs `"offload declined: CLA bucket collision …"` and returns it; on full logs
  `"offload declined: flow table full …"` and returns `-EOPNOTSUPP` (stay SW); only on a clean
  reservation does it install the recipe. A HW-write failure calls `zx_flow_release` + returns the
  error. A declined offload leaves `flows[]` AND the CLA banks untouched.

### `drivers/net/ethernet/zte/zx-eth-main.c` (conduit FT path — mirrored, compiled, not HW-exercised)
Identical logic mirrored: `zx_ft_flow_reserve` (2431), `zx_ft_flow_release` (2461),
`zx_ft_flow_untrack` (2475, already ownership-checked), and `zx_ft_flower_replace` (2620-2639)
reserve-before-install with the same decline logs. (The FT path still doesn't bind from userspace
tc — Part-2 GAP — so it is source-identical to the validated DSA path but untested this session.)

Both units compile clean (only pre-existing unused-function warnings, none for the new code).
**Build #466:** zImage (vmlinux w/ built-in zx-dsa) + module `zx279128-eth.ko` (stripped, staged to
BOTH `tasks/00.01.eth-driver/initramfs/lib/modules/` and `/tmp/initramfs_extract/lib/modules/`,
md5 `27332a48…`), zImage re-embedded, wrapped to `tftp/zImage_dtb.uimg`. Build-order: zImage first
(records the export in Module.symvers) → relink .ko → strip → stage both → zImage again → mkimage.

---

## RETEST RESULTS (all on #466, raw L2 400-pkt bursts, cla_tx_fwd/cla_tx_trp read via memdump)

### (a) COLLISION-REJECT ✅
Install dport200 → `raw=0x455c buckets ram2[0x5c]…` rc=0 (accepted, no warning). It HW-forwards:
cla_tx_fwd 0x000→0x190 (+400 exact), trp flat.
Install dport3002 (raw 0x335c, `raw&0xff=0x5c` — same way0):
```
[phase6] offload declined: CLA bucket collision cookie=c497d800 raw 0x335c (way0 0x5c already owned) -> stays in SW
```
tc returns `RTNETLINK answers: Operation not supported` (EOPNOTSUPP; skip_sw so no SW install
either) — the point is the existing entry is NOT clobbered. dport200 STILL forwards after the
declined install: cla_tx_fwd 0x190→0x320 (+400 exact), trp flat. **No silent clobber; the live
flow is untouched; the stack's follow-up DESTROY of the declined cookie is a `-ENOENT` no-op (does
NOT zero dport200's shared low-byte).** (Old behavior killed both.)

### (b) OVERFLOW-REJECT ✅
Installed 45 distinct-dport flows (dports 1000-1050, hashing to distinct low bytes). Exactly **32**
occupied `flows[32]`; the remaining **19** were DECLINED with:
```
[phase6] offload declined: flow table full (max 32) cookie=… raw 0x… -> stays in SW
```
(19× "flow table full", tc EOPNOTSUPP each). Because `zx_flow_reserve` runs BEFORE the CLA write,
the 19 declined flows wrote NOTHING to the CLA → **no leak** (vs the old accept-and-leak). **0**
real Oops/BUG/Call-trace/panic. `tc qdisc del clsact` then cleanly untracked all 32 (32× "flow del
… cleared raw=… (5 ways) rc=0").

### (c) DISTINCT-FLOW REGRESSION (coexist + ownership-destroy + re-add) ✅
8 distinct non-colliding flows (dports 53/100/150/250/300/350/400/450 → ram2 slots
d5/0c/5b/44/f2/10/fc/e3), all accepted, none declined. Selective forwarding (400-pkt each):

| step                         | cla_tx_fwd      | cla_tx_trp   | verdict |
|------------------------------|-----------------|--------------|---------|
| +d53 (first)                 | 0x320→0x4b0 +400| flat         | FORWARD |
| +d300 (middle)               | 0x4b0→0x640 +400| flat         | FORWARD (coexists) |
| +d450 (last)                 | 0x640→0x7d0 +400| flat         | FORWARD (coexists) |
| +d9999 (NOT installed)       | flat 0x7d0      | +401         | TRAP (selective) |

Ownership-checked destroy — `tc filter del pref 300` → `flow del cookie=c49fa000 -> cleared
raw=0xf7f2 (5 ways) rc=0`:

| step                         | cla_tx_fwd      | cla_tx_trp   | verdict |
|------------------------------|-----------------|--------------|---------|
| +d300 (DELETED)              | flat 0x7d0      | +401         | TRAPS (entry invalidated) |
| +d53 (neighbor, still in tc) | 0x7d0→0x960 +400| flat         | still FORWARDS |

Re-add dport300 → `raw=0xf7f2 buckets ram2[0xf2]` rc=0; injecting → cla_tx_fwd 0x960→0xaf0 (+400),
trp flat → **FORWARDS again**. Destroy is ownership-correct (only the deleted flow's buckets
cleared); re-add restores. (NOTE: the first re-add attempt was silently dropped by the console REPL
when batched with the counter-reads in one line — retrying it standalone installed fine; a tooling
quirk, not a driver bug.)

### (d) BONUS — NARROW-BANK alias does NOT break forwarding; way0-only check is CORRECT ✅
dport100 (0x810c), dport250 (0x1b44), dport400 (0xcdfc) have DIFFERENT `raw&0xff` (0c/44/fc) but
the SAME `raw&7 = 4` → they ALL write the same ext bucket **ram6[0x204]** (last-writer d400 owns
it). The way0-only collision check ACCEPTS all three (correctly — their way0 buckets differ). Each
still HW-forwards +400 exactly (fwd 0xaf0→0xc80→0xe10→0xfa0, trp flat throughout).

**⇒ The HW resolves the flow off the distinct way0 (ram2, 256-slot primary); a shared narrow-bank
(ram6, 8-slot) entry need NOT be uniquely owned.** So (1) covering ONLY `raw&0xff` is the CORRECT
collision criterion, and (2) extending the check to the narrow banks (ram3 0x7f / ram4,5 0x3f /
ram6 0x7) would be WRONG — it would reject validly-coexisting flows like these three. This also
confirms `zx_flow_untrack`'s zero-my-5-ways is safe: zeroing a shared higher/narrow-bank bucket
that another flow last-wrote does not kill that other flow (it forwards off its own distinct way0),
matching the earlier scale-test "destroy-middle keeps neighbours forwarding" result.

---

## State left behind (device healthy, NO reboot)
- Device on **#466**, alive; UART bridge running (:9998/:9999); console loglevel 8.
- lan1 clsact qdisc + all flower filters REMOVED (each del exercised the ownership-checked
  invalidate path); lan1 back to `noqueue`. CLA hash banks cleared. trap_dmac[0]=0. Datapath healthy.
- Host rig intact: enxc8a362e95900 = 192.168.1.50/24 (tftp) + 172.31.9.50/24; static ARP
  172.31.9.1→f4:f6:47:0f:42:64. WAN/PPPoE untouched.
- Driver source edited in linux-v6.6 (zx-dsa.c + zx-eth-main.c); **NOT committed**.
- Stale CLA entries from the 32 overflow-test flows were cleared on the final qdisc-del (untracked);
  any left are harmless (clear on next boot).
