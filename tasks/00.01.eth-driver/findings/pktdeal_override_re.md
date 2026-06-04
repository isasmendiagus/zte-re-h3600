# pktdeal override / unicast HW-forward mechanism — RE (2026-06-04)

THE QUESTION: on the ZX279128S, what HW mechanism FORWARDS a unicast flow while
OVERRIDING the per-protocol pktdeal trap? I.e. how does stock's FFE make an
ESTABLISHED TCP flow HW-forward when the SPA per-protocol classifier would
otherwise trap its control frames — exact mechanism, register write sequence,
entry format — to replicate in the mainline driver.

Sources: `decomp_all_tm.c` (cla_set_hash_table 0x15a14, cla_acl_hash_addr_gen
0x16cdc, addFlowOperInfo 0x5b30c, aclGetAvailableHashAddr 0x5bbe4, tm_acl_l2_fast_init
0x57e10, tm_acl_fast_add_v4v6 0x5c2a8, spaRegTable setters), `decomp_halt_baddata_band.c`
(pktdeal real bodies), `DATASHEET.md` (block bases, pipeline order), and the LIVE
empirical record in `hw_forwarding_offload.md` Iters O–AL + `ffe_tcp_trap_re.md` +
`alt_trap_levers_re.md`. Pure RE — no source modified, no device touched.

---

## TL;DR — the honest answer (it is NOT what the task premise assumed)

The task premise was: *stock's FFE installs a CLA-hash "hardfast" entry that
forwards an ESTABLISHED TCP flow, overriding the pktdeal trap; decode that entry
and replicate it.* The decompile of that exact chain is complete (entry format,
hash, write sequence — all below, section B/C). **BUT the live evidence
(this same task's Iters O–AL, on real silicon) contradicts the premise on two
points and they must drive the implementation decision:**

1. **The CLA hardfast hash (ram2-6) is NOT the unicast TCP/UDP L2 offload.**
   During a live, confirmed-offloaded 350 Mbit/s same-subnet LAN↔LAN TCP flow,
   the CLA hash banks ram2-6 were scanned and were EMPTY of any 5-tuple entry
   (only static `01:00:5x` multicast L2 entries in ram2; ram3-6 all zero).
   `tm_show_fast_rule_list`, `sbrg_print_ipv4table`, and the CLA hash were ALL
   empty during the offloaded flow. So `cla_set_hash_table`/`zte_api_fast_l3_session_add`
   is the **L3 routed/NAT hardfast path (WAN↔LAN)**, not the same-subnet L2
   accelerator. (Iter O/P, hw_forwarding_offload.md:588-665.)

2. **The pktdeal "override" for same-subnet L2 is not a higher-priority CLA
   entry at all — it is pipeline order + the FDB/forward decision being made in
   a stage DOWNSTREAM of the SPA pktdeal trap, plus the empirical fact that
   forwarding is protocol-discriminated by the SPA pktdeal RAM itself.** There
   is no "valid_en+direct+forward entry that beats pktdeal." See section A.

The override the task is looking for, expressed concretely:
- **For routed/NAT (WAN) flows:** the FFE CLA-hash hardfast (sections B/C) — fully
  decoded, replicable, but irrelevant to a pure-L2 bridge.
- **For same-subnet L2 unicast (the bridge use-case):** there is **no per-flow
  override entry**. Stock simply leaves the relevant protocol slots in the SPA
  pktdeal RAM set to deal=0 (forward) for TCP/UDP *data*, and the switch fabric
  L2-forwards on FDB DA-lookup; control protocols (ICMP/ARP/IGMP) stay deal=1
  (trap). The "TCP-ACK traps" anomaly is a handful of TCP-control ptype slots
  that are deal=1; making them forward is a pktdeal-RAM data change, NOT a CLA
  hardfast install. (Iters AF–AL: `all 0` pktdeal → TCP fully HW, tm_rx=0,
  328 Mbit/s; but it is a MULTI-slot set, not one slot, and forward-all breaks ARP.)

---

## A. PRIORITY / OVERRIDE — where the forward decision sits vs the pktdeal trap

### Ingress pipeline order (from DATASHEET.md + mac_to_spa_admit_re.md, HIGH conf):
```
SMAC → SOPC-bridge → SPA → SDET → CLA → SADM → RED → QMG → (DSCH/SOPC egress)
                      ▲                  ▲                         ▲
            pktdeal trap RAM      ACL/hash hardfast        sw_fwd/hw_fwd/hw_trap
            0x921d4300 reg67       (ram1 TCAM + ram2-6      counters 0x9234c044/48/4c
            [1:0] per (port,        hash, indirect
            ptype slot)             0x9238c014)
```

Key facts that answer "does a CLA hit suppress the pktdeal trap":

- **The per-protocol pktdeal trap lives in SPA (0x921d4300), which is UPSTREAM of
  CLA.** So a CLA-hash hit cannot retroactively suppress a trap decision already
  taken at SPA. If pktdeal=1 (trap) for a packet's ptype slot, SPA marks it for
  CPU *before* CLA runs. This is why setting the TCP-control ptype slots to
  deal=0 (forward) is the thing that actually changes the outcome (Iter AI/AL),
  and why poking CLA-hash entries had no effect on the ACK trap (the trap is
  decided one stage earlier).

- **There is no decompiled evidence of a "CLA-hit overrides pktdeal" precedence
  bit.** The task hypothesized a `valid_en+direct+forward+outport` hash entry the
  pipeline honors *before* pktdeal. The hash-entry fields exist (section B) and
  `direct`/`valid_en`/`act_val` are real, but they govern the CLA stage's own
  forward/result, which is *after* SPA's trap. The CLA hash is the L3 routed
  fast-path result table (per-inport classification result), not a pre-emptive
  override of the upstream SPA trap.

- **Live proof the "override" is really pktdeal-RAM data, not a hardfast entry:**
  with the stock pktdeal table, a never-yet-forwarded TCP flow traps its ACKs
  forever (tm_rx +61451, reproducible, fully reversible — Iter AL). Forwarding
  ALL pktdeal slots (`all 0`) → tm_rx delta 0 (ACKs HW-forward). Restoring stock
  → traps again. **No sticky/persistent per-flow entry** (the earlier "autonomous
  flow-learning survives reboot" claim was RETRACTED in Iter AK as an
  instrument artifact). ⇒ the forward-vs-trap decision is the SPA pktdeal RAM
  value, period; there is no CLA/FFE entry overriding it for L2.

- **The L2 forward itself** (once not trapped) is the switch fabric's FDB
  DA-lookup in SBRAG (0x92388000): `pt_da_lookup_en` 0x923882c0, and the
  default dispositions `unknown_unicst_pktdeal` 0x92388340[23:8],
  `dft_unkuni_vl_trans_pktdeal` 0x9238863c[31:16]. UDP HW-forwards both directions
  with NO static FDB (chip self-resolves the DA), and a static SBRAG FDB entry had
  ZERO effect on the TCP-ACK trap (Iter AG) — confirming the gate is the upstream
  SPA pktdeal trap, NOT a DA-lookup miss.

### Verdict on the override question
- **WAN/routed flows:** the CLA-hash hardfast IS a real per-flow forward result
  (act_val=forward, outport, valid_en, direct) — sections B/C. It is the result of
  the CLA classification stage. It does not "beat" pktdeal; for routed flows the
  L3 traffic isn't trapped by the L2 pktdeal slots in the first place.
- **Same-subnet L2 (bridge):** the override is **data in the SPA pktdeal RAM**
  (deal=0 for the data ptypes), not any CLA entry. To replicate stock you change
  pktdeal RAM, not install a hash entry.

---

## B. The 60-byte (15-word) CLA hash entry format — fully decoded

`cla_set_hash_table(hash_addr, byte entry[60])` (tm.ko 0x15a14). The 60 bytes are
written as 15 u32 words (data_id 14→0, i.e. bytes [0x3c-4]→[0x00]). All offsets
below are byte offsets into the 60-byte entry, decoded BIT-EXACT from the
function's own debug printks (decomp lines 3381-3469):

| byte off | field | extraction (from decomp) |
|---|---|---|
| 0x00 | act_val [1:0] | `entry[0] & 3` — **0=forward, 1=trap, 2=drop, 3=copy** |
| 0x00 | act_rp_en | `(entry[0]<<0x1d)>>0x1f` (bit2) |
| 0x00 | queue_id | `(entry[0]<<0x1a)>>0x1d` (bits[4:2]... see printk) |
| 0x00 | queue_rp_en | `(entry[0]<<0x19)>>0x1f` |
| 0x00-01 | tcont_id | `(entry[1]&0xf)<<1 \| entry[0]>>7` |
| 0x01-02 | gemport_uni_id | `entry[2]<<4 \| entry[1]>>4` |
| 0x03 | tcnt_gpid_rp_en | `entry[3] & 1` |
| 0x03-04 | cmd_flow_id | `entry[4]<<7 \| entry[3]>>1` |
| 0x05 | e8_en | `entry[5] & 1` |
| 0x05 | pkt_len_changed | `(entry[5]<<0x1a)>>0x1b` |
| 0x05 | modify_en | `(entry[5]<<0x19)>>0x1f` |
| 0x05 | vlan_rp_en | `entry[5]>>7` |
| 0x06 | flow_rp_en | `entry[6] & 1` |
| 0x06 | cpu_qid [3:0] | `(entry[6]<<0x1c)>>0x1d` |
| 0x06 | cpu_qid_rp_en | `(entry[6]<<0x1b)>>0x1f` |
| 0x06-08 | mtu_val | `entry[7]<<3 \| entry[6]>>5 \| (entry[8]&7)<<0xb` |
| 0x08 | mtu_rp_en | `(entry[8]<<0x1c)>>0x1f` |
| 0x08-09 | bucket_info | `(entry[9]&3)<<4 \| entry[8]>>4` |
| 0x09 | adm_bucket_rp_en | `(entry[9]<<0x1d)>>0x1f` |
| 0x09-0a | qos_id | `(entry[10]&0xf)<<5 \| entry[9]>>3` |
| 0x0a | qos_rp_en | `(entry[10]<<0x1b)>>0x1f` |
| 0x0a-0b | qid_dscp_ram_idx | `((entry[11]&1)<<3) \| entry[10]>>5` |
| 0x0b | qid_dscp_en | `(entry[11]<<0x1e)>>0x1f` |
| 0x0b | wan_id | `(entry[11]<<0x19)>>0x1b` (bits) |
| 0x0b-0c | flow_pri | `(entry[12]&0x1f)<<1 \| entry[11]>>7` |
| 0x0c-0d | **outport** | `(entry[13]&3)<<3 \| entry[12]>>5` |
| 0x0d-0e | **inport** | `(entry[14]&0x3f)<<6 \| entry[13]>>2` |
| 0x0f | tag_level | `(entry[15]&1)<<2 \| entry[14]>>6` |
| 0x0f | l2_type | `(entry[15]<<0x1d)>>0x1e` |
| 0x0f | pppoe_flag | `(entry[15]<<0x1c)>>0x1f` |
| 0x0f-10 | extr_index | `entry[16]<<4 \| entry[15]>>4` |
| 0x10 | **rule_mode** | `(entry[16]<<0x1b)>>0x1f` |
| 0x10 | **direct** | `(entry[16]<<0x1a)>>0x1f` |
| 0x10 | **valid_en** | `(entry[16]<<0x19)>>0x1f` |
| 0x12 | **da_known** | `(entry[18]<<0x1b)>>0x1f` |
| 0x12 | tcont_high / gemport_valid / flow_sta_info | bits in entry[18] (see printk 3390-3393) |
| 0x13-0x3a | **windata0..19** (20 × u16) | the 5-tuple match key/window; windata0 @0x13, windata19 @0x39 |

### Field values that make it "forward to outport, override-at-CLA, valid":
- `act_val = 0` (forward)
- `valid_en = 1` (entry live)
- `direct = 1` (direct/forced action — bypass further classification, use this result)
- `outport = <egress phys/regport>` (the forward target)
- `inport = <ingress regport>` (logical {0,1,2,3}→regport{1,2,3,4}; CPU=identity per cla_ram_layout)
- `rule_mode`, `da_known`, `flow_pri`, `wan_id` per flow type
- `windata0..19` = the packed 5-tuple match window for the flow

(This matches the partial Iter L map in hw_forwarding_offload.md and cla_ram_layout_re.md;
the table above is now bit-exact from the cla_set_hash_table printks.)

---

## C. The exact write sequence to install one hash entry

`cla_set_hash_table(hash_addr, entry[60])` (decomp 0x15a14, lines 3471-3548):

1. Guard: `hash_addr < 0x208` (max 520 buckets).
2. Poll `cla_get_indirect_rw_status` (DONE reg 0x9238c018 bit0) up to 0x14 times until ready.
3. **Bank-select ram_id from hash_addr and make addr bank-relative** (decomp 3496-3520):
   - `< 0x100`      → ram_id **2**, offset = hash_addr
   - `0x100..0x17f` → ram_id **3**, offset -= 0x100
   - `0x180..0x1bf` → ram_id **4**, offset -= 0x180
   - `0x1c0..0x1ff` → ram_id **5**, offset -= 0x1c0
   - `0x200..0x207` → ram_id **6**, offset -= 0x200
4. `cla_set_indirect_rw_cmd(rw=0, ram_id, offset)` → writes CMD 0x9238c014 =
   `offset | ram_id<<22 | rw<<27` (0x400000=1<<22, 0x8000000=1<<27; rw=0 write).
5. Write **15 words**, data_id 14→0 (entry bytes 0x38→0x00, 4 bytes each):
   `cla_set_indirect_rw_data(data_id, word)` → DATA 0x9238c01c + data_id*4.
   (Loop in decomp writes high words first: `param_2 += 0x3c; uVar2=0xe; do {param_2-=4;
   write(uVar2, *param_2); uVar2--;} while(uVar2 != -1);`.)
6. Return 0 on success (all status reads OK).

### The bucket (hash_addr) — `cla_acl_hash_addr_gen(hash_mode, key45, &out)` (0x16cdc):
- Builds a **45-byte (0x2d) key**, REVERSES it, then runs **byte-wise MSB-first CRC-32**.
- **Poly table selected by hash_mode** (decomp 4207-4250):
  - `1` → crctable_1EDC6F41 (CRC-32C / Castagnoli)
  - `2` → crctable_F4ACFB13
  - `3` → crctable_32583499
  - `0/else` → crctable_04C11DB7 (standard Ethernet CRC-32)
- `bucket = crc & 0xffff`.
- hash_mode per table comes from `cla_set_hash_poly_config` (0x1103c).
- 45-byte key layout (from the printk, decomp 4169-4204):
  - `[0]` outport(5b) + inport low bits, `[1]` inport, `[2]` l2_type/tag_level/pppoe + inport hi,
  - `[2-3]` ex_rule_id, `[3]` ex_rule_mode, `[4]` direct,
  - `[4..0x2c]` extra_data0..19 — the packed 5-tuple/match window (7-bit-offset packing:
    each extra_dataN = `key[2N+5]<<7 | key[2N+4]>>1 | (key[2N+6]&1)<<0xf`).

### Bucket→bank allocation (aclGetAvailableHashAddr, 0x5bbe4, param_1==0 L2/3-tuple case):
- ram2: `bucket & 0xff`; ram3: `(bucket & 0x7f) + 0x100`; ram4: `(bucket & 0x3f) + 0x180`;
  ram5: `(bucket & 0x3f) + 0x1c0`. Collision-tracked via `s_aclHashUsedCnt[bucket]`
  (and `+0x208` for the external/high table). Tries banks in order until a free slot.

### The match window (windata) packing — `tm_acl_setMtchInfo` (~0x60ea0) / the match struct:
Match struct (0xbc) built upstream: SIP@0x64, DIP@0x6c, proto@0x62, sport@0x74, dport@0x76,
rule_cfg@0x1c. rule_cfg value (decomp 55167): `proto==6(TCP) || 0x11(UDP) && !is3Tuple →
0x301600`; else `0x401600` (up) / `0x1600` (down). `addFlowOperInfo` (0x5b30c) packs the
match struct into the 45-byte key + the 60-byte entry, then calls cla_acl_hash_addr_gen +
cla_set_hash_table. (NAT/PPPoE/DSLite/IPv6/6rd branches all OFF for plain LAN IPv4 unicast.)

---

## D. Is there an L2-only (MAC-pair / 2-tuple) variant? — `tm_acl_l2_fast_init` (0x57e10)

**RE'd in full. It is NOT a per-flow MAC-pair forward installer — it is a boot-time
scaffold.** The function:
- Writes only **ram1** (`cla_set_extra_rule_table` = the rule-TCAM, 17-word match+mask)
  and **ram0** (`cla_set_extra_index_table` = the byte-extractor descriptor) — it does
  NOT write the ram2-6 hash result table at all.
- It runs a fixed loop (iVar3 1→8) installing 8 static rule-TCAM templates + their
  extract-index descriptors (constants 0x22038608, 0xe1828406, the 0x2492/0x6db6
  extract masks, etc.) that define HOW the L2 fast path PARSES a frame into a key —
  i.e. it sets up the L2 classification *templates*, once, at init.
- There is **no MAC-pair, no outport, no per-flow forward action** in it. The actual
  per-flow forward result still has to go through the same `cla_set_hash_table`
  (ram2-6) path with a 5-tuple/L2 key.

**Conclusion: there is no simpler "install an L2 MAC-pair forward entry" primitive.**
The only per-flow forward-install primitive is `cla_set_hash_table` (sections B/C),
keyed by the CRC bucket of the packed key. `tm_acl_l2_fast_init` is one-time init,
not a runtime installer. So the hoped-for cheaper L2 path does not exist as a distinct
mechanism — AND, per section A, it would be the wrong lever anyway for same-subnet L2
(which is gated by SPA pktdeal upstream of CLA, and forwarded by SBRAG FDB DA-lookup).

---

## E. Minimal driver recipe — by use case

### Use-case 1 (the bridge / same-subnet L2 unicast — what this project actually needs):
**Do NOT install CLA hash entries.** The mechanism is the SPA pktdeal RAM + SBRAG FDB:
- The forward/trap decision is the 2-bit SPA pktdeal field at **0x921d4300 reg67[1:0]**,
  per (port, ptype-slot), written by `spa_set_enty_pktdeal_cfg(port, ptype, deal)` =
  `tmOnuRegWrite(ptype+0x43, deal, port, spaRegTable)`. 0=forward, 1=trap, 2=drop, 3=copy.
  Port remap: identity except 5↔0.
- To make a protocol HW-forward: set its ptype slot deal=0. To trap (bcast/ARP/ND/control):
  deal=1. **Live-proven** (Iter AI/AL): `all 0` → TCP fully HW (tm_rx=0, 328 Mbit/s);
  but forward-ALL breaks ARP (Iter AF), and the TCP-control ACKs need a MULTI-slot set
  (not one slot — Iter AL bisect: ≥large subset, no single minimal slot).
- The forward itself needs the DA in the SBRAG FDB (`pt_da_lookup_en` 0x923882c0); UDP
  shows the chip self-resolves the DA (no static FDB needed). Static SBRAG FDB had no
  effect on the trap (the trap is the upstream pktdeal, not a DA miss).
- **Net minimal change:** the realistic delivery (Iter AL) is "forward broadly, keep only
  the handful of broadcast/control ptype slots trapping" — a pktdeal-RAM table edit in
  `zx_pp_pro_actions[]` / `zx_chip_tm_init_pro_action`, NOT a CLA hardfast install.
  No conntrack, no FFE, no hash entries.

### Use-case 2 (true routed/NAT WAN↔LAN wire-speed offload — if ever required):
Install a CLA hash hardfast entry per flow:
1. Build the 0xbc match struct (SIP/DIP/proto/sport/dport, rule_cfg per section C).
2. Pack into the 45-byte key (section C packing) + the 60-byte entry (section B fields:
   `act_val=0, valid_en=1, direct=1, outport, inport, windata0..19, rule_mode, da_known`).
3. `bucket = cla_acl_hash_addr_gen(hash_mode, key45) & 0xffff`, hash_mode from the table's
   `cla_set_hash_poly_config` (default 0 = Ethernet CRC-32 0x04C11DB7).
4. Map bucket→bank (ram2: &0xff; ram3: &0x7f +0x100; ram4/5: &0x3f +0x180/+0x1c0).
5. `zx_cla_write_entry(e, ram_id, offset, words)` (ALREADY in zx-eth-main.c:~2009 — writes
   the 15 words + CMD `offset | ram_id<<22`) — this IS the cla_set_hash_table HW sequence.
   The mainline indirect helper (CMD 0x9238c014 / DONE 0x9238c018 / DATA 0x9238c01c) is
   already present and proven.
This is a large surface (per-flow CPU install + conntrack-style learn trigger) and is
**not** needed for an L2 bridge.

---

## Honest confidence

- **HIGH**: entry format (section B), write sequence + hash (section C), tm_acl_l2_fast_init
  is init-scaffold-not-installer (section D) — all bit-exact from the tm.ko decompile.
- **HIGH**: pipeline order SPA(pktdeal) upstream of CLA(hash) — DATASHEET + mac_to_spa_admit_re;
  and the live finding that the same-subnet L2 TCP offload runs with CLA hash EMPTY (Iter O/P).
- **HIGH**: the forward-vs-trap lever for L2 is the SPA pktdeal RAM, fully reversible, no
  sticky per-flow entry (Iter AL; the "autonomous flow-learning override" was RETRACTED, Iter AK).
- **MEDIUM**: that NO "CLA-hit-overrides-pktdeal precedence bit" exists — argued from pipeline
  order + the empirical no-effect of CLA/FDB pokes on the trap, not from a single decompiled
  arbiter function (the SPA classifier core is in the partially-recovered halt_baddata band).
- The task's original framing ("FFE installs a CLA-hash entry that overrides pktdeal for
  ESTABLISHED TCP") is **correct for L3/NAT routed flows** but **does not describe the
  same-subnet L2 bridge case**, which is governed by SPA pktdeal data + SBRAG FDB.
