# Multi-flow per-slot HW offload + real DESTROY — IMPLEMENTED & VALIDATED (2026-07-03)

**VERDICT: ✅ BOTH productization bugs FIXED in the driver, rebuilt, booted (#462), and
validated end-to-end on HW.** Two distinct tc-flower flows now HW-forward SIMULTANEOUSLY
(per-slot placement, fill520 clobber gone), and `tc filter del` genuinely invalidates a
flow's HW entry so the deleted flow traps again while the other keeps forwarding.

Device: mainline **#462** (`Linux (none) 6.6.0 #462 Fri Jul 3 00:34:59 UTC 2026`), fresh
DTR boot, RAM-only, NO reboot after boot. Rig: host `enxc8a362e95900` = 172.31.9.50/24
(+192.168.1.50 tftp) on device **lan1**; device lan1=172.31.9.1, lan4=192.168.9.1,
ip_forward=1; route 192.168.9.0/24 via 172.31.9.1; static gw ARP 172.31.9.1→f4:f6:47:0f:42:64.
Counters: cla_tx_fwd 0x9238c3c0, cla_tx_trp 0x9238c3c4, MAC4/lan4 wire-TX 0x92300718.

---

## SELF-CHECK — the per-slot hash key builder is CORRECT (raw=0xf6d5 → slot 0xd5)

The driver builds the flow's 12-word HW hash key from the 5-tuple (extracted-key form:
word0=0x48000000 = ex_rule_id 0x90 / inport 0; then {proto,srcHi,srcLo,dstHi,dstLo,sport,dport}
bit-packed at bit anchor **33+16·n** in a little-endian byte stream), feeds it to the CLA HW
hash engine, and takes the slot from the raw hash.

- **Offline** (python model of the C builder): for UDP 172.31.9.50:50010→192.168.9.50:53 it
  reproduces the live key `48000000 583e0022 81501265 86b41265 0000006b` byte-exact.
- **On-device**, the driver's own recipe log:
  `recipe: proto=17 172.31.9.50:50010->192.168.9.50:53 ... -> raw=0xf6d5 buckets ram2[0xd5]/...`
  → **raw = 0xf6d5, ram2 slot = 0xd5** — EXACTLY the expected value from the on-device
  gparsehashkey/hashcalc measurement. The key builder is proven correct on silicon.

Flow B (dport 1053) hashes to **raw=0x1368 → ram2 slot 0x68** — a DISTINCT bucket, so the two
flows occupy disjoint slots and can coexist.

---

## KEY EMPIRICAL FINDING — the CLA hash lookup is MULTI-WAY (ram2[slot] alone MISSES)

First cut wrote the entry at **ram2[slot] only** (way0 = raw&0xff). Result: **flow A TRAPPED**
(cla_tx_fwd FLAT, cla_tx_trp +401) even though `clapeek ram2 0xd5` read the entry byte-exact
(`03005044 fa11c000 00000608 00000000 11000049 32ac1f00 32c0a809 35c35a09`). So way0 alone is
NOT where the HW resolves this flow.

Writing the SAME entry to the other four banks at the flow's own hash (via clawrite, which for
ram 1-6 uses the correct CMD-first/descending `zx_cla_write_hash`) → **flow A FORWARDED
(+400 cla_tx_fwd, +400 MAC4 wire-TX)**. So the fix is **per-slot placement across ALL 5 banks**
(one bucket per bank, at the flow's own hash — NOT all 520):

```
way0 = ram2[ raw & 0xff        ]
way1 = ram3[ 0x100 + (raw&0x7f) ]
way2 = ram4[ 0x180 + (raw&0x3f) ]
way3 = ram5[ 0x1c0 + (raw&0x3f) ]
ext  = ram6[ 0x200 + (raw&0x7 ) ]
```

These 5 buckets are distinct per distinct raw hash, so different flows still occupy disjoint
buckets → coexistence preserved. (This is why the old fill520 "worked": it covered every way;
the HW just needs the entry in whichever way it probes for that key.)

---

## THE CODE CHANGES

### `drivers/net/dsa/zte/zx-dsa.c` (built-in — the TESTED tc-flower path)
- **`zx_cla_hash_raw(p, key[12])`** (new): drives the CLA HW hash engine via the already-mapped
  `cla_regs` (KEY0 0x2c4.., TRIG 0x2c0, OUT 0x2fc) — load key, trigger, read raw16.
- **`zx_cla_flow_hash(p, proto,saddr,daddr,sport,dport)`** (new): builds the 12-word extracted-key
  form (word0=0x48000000 + 7 fields at bit anchor 33+16·n, LE byte stream) and returns the raw hash.
- **`zx_cla_way_slots(raw, ram[5], addr[5])`** (new): the per-bank bucket map above.
- **`zx_install_l3_recipe`**: replaced the fill520 520-bucket loop with **5 writes** at the flow's
  own buckets (`zx_cla_way_slots` + `zx_cla_wr` per way). Returns the raw hash.
- **`struct zx_flow_ent flows[32]`** in `zx_dsa_priv` (new): tracks `{cookie, raw}` per installed flow.
- **`zx_flow_track` / `zx_flow_untrack`** (new): record raw by tc cookie on add; on del, zero the
  15-word entry in all 5 way banks (valid_en byte0x10 bit6 → 0 → key-compare misses → traps).
- **`zx_dsa_cls_flower_add`**: tracks the installed flow's raw against `cls->cookie`.
- **`zx_dsa_cls_flower_del`**: was `return -EOPNOTSUPP` (no-op) → now calls `zx_flow_untrack`
  (invalidates the flow's 5 buckets); returns 0.

### `drivers/net/ethernet/zte/zx-eth-main.c` (conduit module — the FT/conntrack path, untested*)
Mirrored identically for consistency: `zx_ft_flow_hash`, `zx_ft_way_slots`, per-slot 5-way write
in `zx_ft_install_recipe`, `ft_flows[32]` in `struct zx_eth`, `zx_ft_flow_track/untrack`, and
`FLOW_CLS_DESTROY` now calls `zx_ft_flow_untrack`.
*The FT path still does not bind from userspace tc (Part-2 GAP 1: conduit `sw` has no
`.ndo_setup_tc`), so it was compiled but not exercised this session. Logic is source-identical
to the validated DSA path.

Both units compile clean (only pre-existing unused-function warnings). Build #462: zImage
(vmlinux w/ built-in zx-dsa) + module `zx279128-eth.ko` (stripped, md5 `4e46fc7b…`, staged to
BOTH initramfs dirs), zImage re-embedded, wrapped to `tftp/zImage_dtb.uimg`.

---

## VALIDATION (all via the driver's own tc-flower install path on lan1)

Two flows installed (driver log confirms distinct 5-way buckets):
```
A dport 53   -> raw=0xf6d5 buckets ram2[0xd5]/3[0x155]/4[0x195]/5[0x1d5]/6[0x205] rc=0
B dport 1053 -> raw=0x1368 buckets ram2[0x68]/3[0x168]/4[0x1a8]/5[0x1e8]/6[0x200] rc=0
```

### Multi-flow coexistence (BUG #1 fixed)
| step | cla_tx_fwd | cla_tx_trp | MAC4-TX | verdict |
|---|---|---|---|---|
| baseline | 0x000 | 0x00a | 0x008 | — |
| +400 A (dport 53) | **0x190 (+400)** | +1 | **0x198 (+400)** | **HW FORWARD** |
| +400 B (dport 1053) | **0x320 (+400)** | flat | **0x328 (+400)** | **HW FORWARD (coexists)** |
| +400 dport 5555 (not installed) | 0x320 (flat) | **0x1a0 (+405)** | flat | **TRAP (selective)** |

**⇒ A AND B both HW-forward simultaneously (each +400 fwd + +400 wire-TX). The fill520
single-entry clobber is gone; distinct 5-tuples coexist in distinct buckets.**

### `tc filter del` genuinely invalidates (BUG #2 fixed)
`tc filter del dev lan1 ingress pref 49152` (flow A) → driver log:
`cls_flower_del port1 cookie=c4985000` + `flow del cookie=c4985000 -> cleared raw=0xf6d5 (5 ways) rc=0`

| step | cla_tx_fwd | cla_tx_trp | MAC4-TX | verdict |
|---|---|---|---|---|
| baseline (post-del) | 0x320 | 0x1ab | 0x328 | — |
| +400 A (dport 53, DELETED) | 0x320 (flat) | **0x33b (+400)** | flat | **TRAPS** (entry invalidated) |
| +400 B (dport 1053, still in tc) | **0x4b0 (+400)** | flat | **0x4b8 (+400)** | **still FORWARDS** |

**⇒ The deleted flow now TRAPS (no stale HW-forward leak); the surviving flow keeps forwarding.**

---

## WAY/BUCKET SUBTLETY (the one non-obvious result)

The task anticipated it: **ram2[slot] alone is insufficient — the HW multi-way lookup requires
the entry in every bank at the flow's hash.** A single-way write MISSES despite a byte-exact,
correctly-placed way0 entry. The minimal winning set was not bisected per-way (would cost extra
boots); writing all 5 ways is robust, still per-slot (5 disjoint buckets per flow), and preserves
coexistence. If a future session wants the true minimal way, clear ram2[slot] and add ways one at
a time — but all-5-ways is correct and cheap (5 indirect writes/flow).

Next-hop MAC was the seeded fallback `6c:70:cb:b6:81:69` (dst 192.168.9.50 is fictional → neigh
unresolved); this only affects the egress DMAC rewrite, not the forward decision — both forward
and wire-egress are proven above.

---

## State left behind (device healthy, NO reboot)
- Device on **#462**, alive; UART bridge running (:9998/:9999); console loglevel 8.
- lan1 clsact qdisc + both flower filters **removed** (each del exercised the new invalidate
  path, rc=0); lan1 back to `noqueue`. CLA hash banks cleared for both flows. Datapath healthy.
- Host rig intact: `enxc8a362e95900` = 192.168.1.50/24 + 172.31.9.50/24; route 192.168.9.0/24
  via 172.31.9.1; static ARP 172.31.9.1→f4:f6:47:0f:42:64.
- Driver source edited in linux-v6.6 (zx-dsa.c + zx-eth-main.c); **NOT committed**.
