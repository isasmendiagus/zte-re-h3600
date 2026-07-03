# CLA hash-hit vs default-flow — SOLVED + 🎉 MILESTONE: selective nonzero 5-tuple HW-forward on mainline (2026-07-02)

Device: mainline **#456** (`Linux (none) 6.6.0 #456 Thu Jul 2 19:04:20 UTC 2026`), live, NO reboot.
Rig: host `enxc8a362e95900` = 172.31.9.50/24 (+192.168.1.50/24 tftp) on device **lan1**; device
lan1=172.31.9.1, lan4=192.168.9.1, ip_forward=1; route 192.168.9.0/24 via 172.31.9.1; static gw
ARP 172.31.9.1→f4:f6:47:0f:42:64. Flow: UDP **172.31.9.50:50010 → 192.168.9.50:53**.
Counters: cla_tx_fwd 0x9238c3c0, cla_tx_trp 0x9238c3c4, acl_required 0x9238c3b8 (hi16),
desOut 0x9238c394..3a0 (action_rsn=(w2>>23)&0x7f), gparsehashkey 0x9238c260.

## 🎉🎉🎉 HEADLINE — GENUINE SELECTIVE NONZERO HASH-HIT FORWARD ACHIEVED

For the first time on mainline, a **per-flow nonzero 5-tuple CLA hash entry HW-forwards
selectively**:
- Matching flow (UDP 172.31.9.50:50010→192.168.9.50:**53**): **cla_tx_fwd +400, cla_tx_trp FLAT**,
  desOut action_rsn **0x49 FORWARD**.
- Non-matching flow (same tuple but dport **5555**): **cla_tx_fwd FLAT, cla_tx_trp +401** (trapped).
- Reproduced (matching +400 twice, non-matching +401). This is a real content-selective hash hit,
  not a catch-all.

**THE FIX (one word): the ram2 entry's `word3` must be `0x00000000`, NOT `0x80000000`.**
The long-standing `word3 = 0x80000000 /* valid */` was WRONG — that bit is **not** a valid bit;
it is part of the entry's **extr_index** field. Setting it made extr_index encode ex_rule_id
**0x98**, so a flow classified under the forced rule **0x90** never matched → LOOK_UP_MISS. With
`word3 = 0` the extr_index low byte = **0x90** = the packet's ex_rule_id → HIT.

## TEST 1 — default-flow vs genuine hit: it is a GENUINE ram2 HASH HIT (not L3 default-flow)

Rule 0x98 enabled (ram0[9] word4 = 0x00150151); ram1[0x98] is empty (all-zero) → HW extracts a
**ZERO key** (gparsehashkey w0=0x4c000000 = ex_rule_id 0x98, all extra_data = 0, confirmed live).

| ram2 state | cla_tx_fwd | cla_tx_trp | verdict |
|---|---|---|---|
| **ALL 520 buckets CLEARED** (no valid entry anywhere) | **FLAT** | **+406** | MISS |
| zero-windata forward entry via fill520 (valid) | **+400** | flat | **FORWARD** |

⇒ With NO entry the zero-key MISSES; installing a valid zero-windata entry makes it FORWARD.
**The zero-key "forward" REQUIRES a valid ram2 entry — it is a genuine hash-table hit, NOT the L3
default-flow catch-all.** (A default flow would forward regardless of ram2 content.) TEST 2
(characterize the default flow) is therefore N/A — there is no default-flow forwarding path in play.

L3 default-flow cfg for reference (decomp): `cla_set_up_l3_default_flow_cfg` writes claRegTable
idx 0x1e/0x1f/0x20; `cla_set_dn_...` writes 0x21/0x22/0x23/0x24 (incl da_known @0x24). Not the
mechanism here.

## TEST 3 — why the nonzero hash hit "never matched": the extr_index/ex_rule_id mismatch

### (a) live bucket / occupancy — RULED OUT as the cause
- There is **no readable live-lookup-bucket latch**: the CLA descriptors (desIn 0x9238c3e0.., desOut
  0x9238c394..) carry action + action_rsn but **no hit/match-address field** (grep of the decomp
  desIn/desOut decoders: none). The hash-engine block 0x9238c2c0..0x2fc is the **manual** slot
  calculator (hashcalc), not an ingress latch (reads 0 during a live flow).
- **Slot is not the cause**: `fill520` writes the entry to every internal bucket. The internal hash
  ways map EXACTLY to the fill520 banks — `aclGetAvailableHashAddr` (decomp:52341): way0=ram2
  (hash&0xff), way1=ram3 (&0x7f+0x100), way2=ram4 (&0x3f+0x180), way3=ram5 (&0x3f+0x1c0),
  external=ram6 (0x200..0x207). So any internal bucket the HW probes is covered.

### (b) per-bucket occupancy / build-commit write beyond the 15-word entry — DOES NOT EXIST (HW)
Full RE of the v4-fast install path `tm_acl_fast_add_v4v6` (decomp:52521) →
`tm_acl_get_fastHashRule` (49213) → `cla_set_hash_table` (3366) + `EN_V4FAST_EXTIDXTBL` (49717):
- The ONLY HW writes are **cla_set_hash_table** (the 15-word / 60-byte entry, data_ids 0xe..0) plus
  the **ram0 extract-index arm** (`cla_set_extra_index_table`, i.e. ram0[9] index_valid bits).
- `s_aclHashUsedCnt[0..0x207(+ext)]` is a **software-only** bookkeeping array used by
  `aclGetAvailableHashAddr` to pick a free slot; it is **not a HW register** and the HW lookup does
  not read it. `sa_rulesRecord` is likewise SW. **No per-bucket HW occupancy/valid/way table exists**
  → nothing to "also write". This closes the occupancy hypothesis.

### (c) content match — VERIFIED byte-exact (so the miss was NOT content)
Forced rule 0x90 (ram0[9]=0x00150001); live gparsehashkey during the flow =
`48000000 583e0022 81501265 86b41265 0000006b`. Decoding extra_data (extra_dataN = key[5+2n]<<7 |
key[4+2n]>>1 | (key[6+2n]&1)<<15): **{0x0011, 0xac1f, 0x0932, 0xc0a8, 0x0932, 0xc35a, 0x0035}** =
exactly the stored windata0..6. Content matches field-for-field. Yet the byte-exact entry (with the
historic `word3=0x80000000`) **MISSED** (cla_tx_fwd flat, desOut **0x54 LOOK_UP_MISS**) — reproduced.

### THE DECISIVE ISOLATION — hit/miss depends on ex_rule_id, via the entry's extr_index field
Holding the key value and entry-placement constant (fill520, zero key), only the ex_rule_id varied:

| ex_rule_id (ram0[9] bit) | ram1 extract | entry word3 | extr_index | cla_tx_fwd |
|---|---|---|---|---|
| **0x98** (bit8) | empty (zero key) | 0x80000000 | 0x498 (low 0x98) | **FORWARD +400** |
| **0x90** (bit0) | zeroed (zero key) | 0x80000000 | 0x498 (low 0x98) | **MISS** |
| **0x90** (bit0) | zeroed (zero key) | **0x00000000** | **0x490 (low 0x90)** | **FORWARD +400** |
| **0x90** (bit0) | real v4 5-tuple | **0x00000000** | 0x490 (low 0x90) | **FORWARD +400 (5-tuple, selective)** |

Same zero key, same entry in all 520 buckets → rule 0x98 hit, rule 0x90 missed. The only HW-visible
per-rule difference is the **ex_rule_id**, and the stored entry carries an **extr_index** field whose
low byte MUST equal the packet's ex_rule_id. `cla_set_hash_table` layout (decomp:3444):
`extr_index = byte0x10<<4 | byte0xf>>4`. With `word3=0x80000000` → byte0xf=0x80 → extr_index=0x498
(low byte **0x98**). With `word3=0` → byte0xf=0x00 → extr_index=0x490 (low byte **0x90**). The
**valid_en bit is byte0x10 bit6** (=0x49, already set in word4), NOT word3 bit31 — the old "word3 =
valid" comment/assumption was the root error.

**Why every prior nonzero test missed:** they all *forced rule 0x90* but kept the stock-captured
`word3=0x80000000` (extr_index→0x98). Rule 0x90 ≠ 0x98 → LOOK_UP_MISS on every packet, regardless of
byte-exact windata, slot, fill520, dport fix, outspace, inport, etc. This also reconciles the
"#444 forwarded / #456 misses" puzzle without an "engine regression": stock's captured entry
(word3=0x80000000) is correct only for a flow the HW classifies to ex_rule_id 0x98; when we force
0x90 the entry's extr_index must be repacked to 0x90.

## VERDICT — the precise reason + the exact fix
- The nonzero hash hit never matched because the stored entry's **extr_index** (byte0xf/byte0x10)
  encoded ex_rule_id **0x98** (via `word3=0x80000000`) while the flow was classified under
  ex_rule_id **0x90** → the bucket key-compare rejected it (LOOK_UP_MISS 0x54). It was **not** an
  engine regression, a slot/bucket problem, a missing occupancy write, or a windata content bug.
- **Exact fix (both driver packers):**
  - `zx-eth-main.c:2304  cla[3] = 0x80000000;` → **`cla[3] = 0;`**
  - `zx-dsa.c:719        cla[3] = 0x80000000;` → **`cla[3] = 0;`**
  - and arm ram0[9] for **rule 0x90** (word4 low16 bit0 → `0x00150001`, the populated v4-5tuple
    extract rule ram1[0x90]), so the entry's extr_index (low byte 0x90) matches the selected
    ex_rule_id. General rule for productization: **entry extr_index low byte == the ex_rule_id the
    HW selects for the flow** (stock's `tm_acl_get_fastHashRule` sets it from the flow's parse; the
    static packers must not hardcode 0x98's 0x80000000).
- Proven recipe on #456 (selective): ram0[9]=0x00150001; ram1[0x90]=real v4 boot rule; entry
  `03005044 fa11c000 00000608 00000000 11000049 32ac1f00 32c0a809 35c35a09 0 0 0 0 0 0 0` via
  fill520; matching flow → cla_tx_fwd +N, non-matching dport → trap.

## NEXT
- Apply the two-line packer fix + arm rule 0x90 in the offload binder (`zx_install_l3_recipe`) and
  re-run the Stage-2 tc/conntrack path end-to-end (should now HW-forward established flows).
- Cross-check the general extr_index==ex_rule_id rule against a captured stock 5-tuple entry to
  confirm stock's extr_index tracks the flow's parsed ex_rule_id (expected).

## State left behind (device healthy, NO reboot)
- Device on **#456**, alive; UART bridge + REPL responsive; console loglevel 8.
- **ram0[9] RESTORED to 0x00150051** (readback-confirmed). ram1[0x90] RESTORED to the real v4 boot
  rule (readback-confirmed). ram2 hash banks CLEARED (fill520 all-zero → inert).
- Datapath healthy (post-restore flow: cla_tx_trp climbs +pkts = normal ingress/trap).
- Host rig intact: enxc8a362e95900 has 192.168.1.50/24 + 172.31.9.50/24; route 192.168.9.0/24 via
  172.31.9.1; static ARP 172.31.9.1→f4:f6:47:0f:42:64. No reboot, no flash.
