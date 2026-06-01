# SPA indirect match/hash RAM + ingress classification flow — full RE

**Status: static RE (decomp + mainline source + reg-table + stock-dump + prior live diffs). Date: 2026-06-01.**
Decode of the SPA (stream/source-port classifier, block phys `0x921d4000` = NPP+0x14000)
indirect match/hash RAM and the full per-frame ingress classification/admit path. Extends and
reconciles `spa_indirect_ram_protocol_re.md`, `pm_spa_init_recipe_re.md`,
`port1_spa_admit_gate_re.md`, and memory `zte-spa-matchram-not-gate`.

Address model (all confirmed elsewhere, restated): `tmOnuRegWrite(reg_id,val,sub_idx,table)`
RMW at `phys = 0x92000000 + (base_off + stride*sub_idx)*4` masked/shifted per `zx_sparegtable`
entry. SPA word base 0x75000 → phys 0x921d4000. `npp_write(e,off,val)` = `writel(val, 0x921c0000+off)`.

---

## 1. SPA indirect interface (CMD / STATUS / DATA) — CONFIDENCE: HIGH

| port | reg_id (spaRegTable) | base_off (word) | phys | role |
|---|---|---|---|---|
| CMD     | 4 | 0x75005 | **0x921d4014** | indirect_rw_cmd (write = trigger) |
| STATUS  | 5 | 0x75006 mask 0x1 | **0x921d4018** | indirect_rw_status, poll **bit0==0 = done** |
| DATA    | 6 | 0x75007 stride1, **sub 0..6** | **0x921d401c..0x921d4034** | indirect_rw_data, **7 slots** |

**CMD bit-layout** (`spa_set_indirect_rw_cmd` decomp_all_tm.c:25957):
`val = ram_addr + ram_id*0x400000 + ind_rw_en*0x8000000`
- **addr   = bits[21:0]** (validated `<= 0x3FFFFF`, :25945)
- **ram_id = bits[26:22]** (×0x400000; validated `<= 5`, :25943) → **6 banks: ram_id 0..5**
- **rw/go  = bit[27]** (`ind_rw_en`; validated `<= 1`, :25947). **1 = READ-prefetch, 0 = WRITE-commit**.
Writing CMD is itself the trigger; completion polled on STATUS bit0 (≤0x13 spins, :26174/26058).

**DATA slot count:** the reg-table entry (reg_id 6) has `max_sub_idx=6` ⇒ sub-index 0..6 =
**7 data words** (0x921d401c..0x921d4034). `spa_get/set_indirect_rw_data` validate `param < 6`
in the decomp (so only idx 0..5 ever used by tm.ko = 6 words/line for matchram), but the HW
window physically exposes 7 slots (matches the task's "7 slots" and DATASHEET reg6 "x7").

**Comparison to CLA indirect (`cla_ram_layout_re.md`):** same 3-port shape (CMD/STATUS/DATA)
but **different CMD encoding and bank count.** CLA packs `{ram_id, addr, rd/wr}` differently and
has 8 RAM banks (ram0 portless / ram1 rule-TCAM / ram2-6 per-inport hash+trap / ram7 trap-queue).
SPA has only **6 banks**, and of those tm.ko only ever uses **ram_id 0 (match-RAM)** and
**ram_id 5 (hash-RAM)**; ram_id 1..4 are never touched by the initializer (left at HW reset).

**Leftover stock CMD readback** `0x921d4014 = 0x01400007`: bit27=0 (WRITE-commit),
ram_id=(>>22)&0x1f=**5** (hash-RAM), addr=7 → the last write was hash-RAM entry idx 7, exactly the
final iteration of `spa_set_hashram` (loop 0..7). CONFIRMED.

---

## 2. Per-ram_id entry format — CONFIDENCE: HIGH (structure) / MEDIUM (exact bit packing)

### ram_id 0 = MATCH-RAM (`spa_set_matchram` :26131)
- **11 entries** (init copies `_LANCHOR1` = 0x160 bytes / 8 words-of-input per entry = 11;
  loop :43344-43358 steps +8 words, stops at `&uStack_20`).
- **4 rules share one 6-word RAM line** (`addr = rule_num >> 2`, slot = `rule_num & 3`); the
  builder does READ-prefetch → OR new rule into its slot → WRITE-commit (read-modify-write).
- **Per-rule logical fields** (input struct printk :26164-26168; 10 bytes packed by the init at
  :43346-43355 from each 8-word `_LANCHOR1` entry):

  | field | width | source byte (input struct) |
  |---|---|---|
  | `rule_num`      | 8b  | byte0 |
  | `valid`         | 1b  | byte1 |
  | `v4_v6_flag`    | 1b  | byte2 |
  | `offset_mode`   | 2b  | byte3 |
  | `offset`        | 6b  | byte4 |
  | `compare_mode`  | 2b  | byte5 |
  | `mask`          | 16b | byte6-7 |
  | `data`          | 16b | byte8-9 |

  i.e. a generic **offset/mask/data byte-matcher**: "at packet byte `offset` (mode-selected
  L2/L3 base, v4/v6 variant), compare 16 bits under `mask` against `data` using `compare_mode`."
  **There is NO source-port / source-MAC / out-port / uni / allow column in a match-RAM rule.**
  The match-RAM is portless — confirmed (memory `zte-spa-matchram-not-gate`).

### ram_id 5 = HASH-RAM (`spa_set_hashram` :26029)
- **8 entries** (init loop idx 0..7, :43360-43366; source = the 12-word `DAT_0004eee4` blob).
- **2 data words/entry** (writes only `spa_set_indirect_rw_data(1,*)` then `(0,*)`, :26076-26077).
- **Fields** (printk :26045-26049):

  | field | width | meaning (inferred) |
  |---|---|---|
  | `valid`         | 1b  | entry valid |
  | `match_array`   | ~24b| bitmap of which match-RAM rules must hit for this entry |
  | `action_rsn`    | ~7b | trap/action reason code |
  | `action`        | 2b  | result action (0..3) |

  **The hash-RAM is the RESOLVER:** a match-RAM rule produces a per-rule hit bit; the hash-RAM
  entry's `match_array` is the boolean combination of those rule-hits that selects this entry,
  and the entry yields an `action` (2b) + `action_rsn`. So the classification is:
  **match-RAM rules (byte-matchers) → hit vector → hash-RAM `match_array` → entry → action.**

### Is ANY ram dimension per-ingress-port / per-uni?
**No — neither match-RAM nor hash-RAM carries a port/uni key.** Both are content-keyed
(byte-match + rule-combination), identical regardless of which physical port the frame arrived on.
The ONLY per-ingress-port classification dimension in the entire SPA is **NOT in the indirect
RAM** — it is the direct `enty_pktdeal_cfg` table (see §3b).

---

## 3. How a frame gets admitted — the pkt_en/pps_en + enty_pktdeal relationship

### 3a. pkt_en / pps_en are per-ENTRY, NOT per-port (CONFIRMED, and shown DEAD as the gate)
- `spa_set_up_reg_pkt_en(entry,1)` (:26271) → reg_id 0, 3 sub-words: entry 0x00-0x1f→0x14000,
  0x20-0x3f→0x14004, 0x40-0x4d→0x14008 (**78 entry bits**). dn mirror reg_id 1 @0x14040/44/48
  (`spa_set_dn_reg_pkt_en`, 0..0x52).
- `spa_set_up_reg_pps_en(entry,1)` (:26373) → reg_id 2 @0x1400c/0x14010 (**62 entry bits**, 0..0x3d).
  dn mirror reg_id 3 @0x1404c/0x14050 (`spa_set_dn_reg_pps_en`).
- The "entry" indexing these bitmaps is the **classification entry** resolved by §2
  (match→hash), NOT a physical port. pkt_en = "this entry's packets are receive-admitted";
  pps_en = "this entry's packet/policer counting enabled".
- **LIVE RESULT (port1_spa_admit_gate_re.md §LIVE TEST 2026-05-31):** mainline reads
  `0x1400c=ffffffff, 0x14010=3fffffff, 0x1404c=ffffffff, 0x14050=ffffffff` — i.e. HW reset
  default is ALL-ON. So mainline not writing pps_en is **harmless**; the pkt_en/pps_en gate is
  **NOT the port1 drop** (every entry admitted on both stages). Hypothesis DEAD.

### 3b. enty_pktdeal_cfg IS the per-(ingress-port × protocol) action table (NEW — the per-port dim)
`spa_set_enty_pktdeal_cfg(port_id, protocol_type, action)` (:28135):
`tmOnuRegWrite(reg_id = 0x43 + protocol_type, val = action(2b), sub_idx = port_id, spaRegTable)`.
- `protocol_type` 0..0x3c selects **reg_id 67..125** (each is a 2-bit field, base 0x750c0+,
  packed 16 protos/word, see `zx_sparegtable` reg_id 67-127 all `mask=0x3, stride=5`).
- **`sub_idx = port_id` (0..7)** with `stride=5` ⇒ each physical ingress port gets its own
  5-word block at `0x921d4300 + port*0x14`. **This is the SPA's one genuinely per-ingress-port
  classification surface:** "for ingress port P, protocol T → action (0=fwd,1=trap,2=drop,3=…)".
- Mainline **DOES replay this**: `zx_chip_tm_init_pro_action` (zx-eth-main.c:2180) loops
  port 0..7 × proto, calling `zx_spa_set_enty_pktdeal_cfg` (:2164) → same reg_id `67+proto`,
  sub_idx=port. Uses `zx_pp_pro_actions[]` (kotrace-extracted), **PP0 action for every port**.

### 3c. Per-uni receive counters (the live discriminator origin)
`spa_get_*` dump (:28365-28384) reads per-SOURCE-port SOP/EOP counters:
`rcv_pon, rcv_uni0..4, rcv_wifi0/1, rcv_cpu, before_tagflt_fwd/drp`. These are exactly the
SPA-side per-physical-source-port counters; "uni1" = port1's SPA receive counter (the live
discriminator: uni1=2 vs uni2/3=229/230 in DATASHEET line 423). They are read-only stats, not a
gate, but prove **the SPA does see frames per physical uni** and tags each frame with its
source-uni identity internally — even though the match/hash RAM key is portless.

---

## 4. Full SPA ingress classification flow (map)

```
frame from SMAC(port P)
  │
  ├─[A] SPA tags frame with source-uni id (P) → rcv_uniP_sop/eop counter++   (0x921d45cc+…, stats only)
  │
  ├─[B] enty_pktdeal_cfg[port P][protocol T]  → 2-bit action (fwd/trap/drop)  ← ONLY per-INGRESS-PORT decision
  │        (reg_id 67+T, sub_idx P; mainline replays via zx_chip_tm_init_pro_action)
  │
  ├─[C] match_mode (0x1407c, =1) gates the classifier; if 0 the match/hash RAM is not consulted
  │
  ├─[D] match-RAM (ram_id0, 11 rules): each rule = offset/mask/data byte-match → per-rule hit bit  (PORTLESS)
  │
  ├─[E] hash-RAM (ram_id5, 8 entries): match_array combines rule-hits → selects ENTRY → action+rsn (PORTLESS)
  │
  ├─[F] per-ENTRY admit: pkt_en[entry] (0x14000/04/08) AND pps_en[entry] (0x1400c/10) must be 1
  │        (mainline: pkt_en written, pps_en left at all-on HW default → both effectively all-on)
  │
  ├─[G] tag-filter / trap (802x_trap, bpdu_trap, dft_pri, port_pkt_filter, color_mode) → before_tagflt_fwd/drp
  │
  └─→ forward to SDET (per-uni transport counter 0x921c4160+uni*4) → fabric (QMG/IDM/PM)
```

Net: a frame is admitted iff (B) its (port,protocol) action ≠ drop, AND (D/E) it classifies to a
hash-RAM entry whose (F) pkt_en & pps_en bits are set, AND (G) it isn't tag-filtered/trapped.

---

## 5. Does mainline populate the match/hash RAM? — NO (CONFIRMED)

`zx_pm_spa_init` (zx-eth-main.c:4706-4732) writes ONLY direct registers:
pkt_en 0x14000/04/08 + dn 0x14040/44/48, `0x14054 |= 0x03000000`, **`0x1407c = 1` (match_mode)**,
PM rules. **It performs ZERO indirect (CMD/DATA) writes** — the comment at :4702 explicitly says
"The SPA match-RAM (indirect, ram_id 0) is NOT populated here yet." So:
- **match-RAM (ram_id0) and hash-RAM (ram_id5) are LEFT EMPTY (HW reset) under mainline.**
- match_mode=1 IS set, so the classifier is enabled but consults an all-zero/invalid table.

**Default behavior with empty match/hash RAM + match_mode=1:** every hash-RAM entry has
`valid=0` and match-RAM rules are invalid → no content classification resolves. The observed
live behavior (ports 0/2/3 ping fine, port1 mostly dies) shows the **default is admit-forward**
for un-classified frames (the fabric/PM forwards by FDB/flood regardless of SPA classification),
NOT drop-all — consistent with mainline working on 3/4 ports without ever populating the RAM.
The stock `_LANCHOR1`/`DAT_0004eee4` contents are baked tm.ko .rodata (recoverable by reading
the ELF at those symbols) but, per memory `zte-spa-matchram-not-gate`, they encode L3/EtherType
trap byte-matchers (e.g. IPv4/IPv6/ARP-to-CPU), **not** a per-port admit gate — so populating
them is not expected to fix port1.

---

## 6. Hypothesis for the port1 silent drop, testable by kotrace/poke

The SPA match/hash RAM is **portless** and pkt_en/pps_en are **all-on** (both live-confirmed
non-gates). The ONE per-ingress-port surface inside the SPA is **enty_pktdeal_cfg**
(reg_id 67+proto, sub_idx = port, block `0x921d4300 + port*0x14`). Mainline writes it for all
8 ports using the **PP0 action for every entry** (zx-eth-main.c:2189), but stock's
`pp_set_pro_action` distinguishes **PP0 vs PP1** (comment :2186 notes proto 0x14 differs
PP0=1/PP1=0) and the per-port `action` may not be uniform across ports. If port1's logical→
physical port-remap (`port_remap[1]` = regport2) lands its `enty_pktdeal_cfg` block on a port
sub-index whose action for the ping/ARP protocol is **drop(2)** instead of **fwd(0)** — while
ports 0/2/3 map to fwd — that would be a per-ingress-port, counter-silent (SDET never sees it),
config-invisible-to-flat-symmetry drop at exactly the MAC→SPA stage, matching the signature.

### Concrete read-only test (definitive, no poke needed first)
Dump the per-port enty_pktdeal blocks and compare port1's vs ports 0/2/3's action for each proto:
```
# block base 0x921d4300 + port*0x14, 5 words each (reg_id 67..127, 2b/proto, 16 proto/word)
for P in 0 1 2 3; do for w in 0 4 8 c 10; do devmem $((0x921d4300 + P*0x14 + 0x$w)); done; done
```
Decode each 2-bit field (proto = word*16 + bit/2). **If port1's block has a `drop(2)` where the
working ports have `fwd(0)` for the ARP/IPv4 proto → that IS the gate.** Cross-check the live
SPA per-uni counters (`rcv_uni1` region near 0x921d45cc) and `before_tagflt_drp` — if
`before_tagflt_drp` climbs when pinging port1, the drop is the tag-filter/pktdeal action, not the
RAM. The match/hash RAM read (§1 protocol, ram_id0/5) can confirm both tables are empty (all
zero) on mainline, ruling them out definitively.

### Caveat
enty_pktdeal action `2` semantics (drop vs trap-to-CPU vs policer) is inferred (2-bit, range
checked `<4`); confirm by the live dump above. If port1's pktdeal block is byte-identical to the
working ports (as every other per-port reg has proven to be — port1_spa_admit_gate_re.md §LIVE),
then the SPA holds NO register-level discriminator and the drop is an init-sequence/silicon-channel
issue (the standing conclusion), requiring a stock port1-ingress kotrace.

---

## Confidence summary
- **HIGH:** indirect protocol (CMD `addr|ram_id<<22|rw<<27`, 6 banks, STATUS bit0, 6+1 DATA),
  match-RAM 11 rules byte-matcher (no port column), hash-RAM 8 entries resolver, mainline does
  NOT populate the RAM, pkt_en/pps_en are per-entry & all-on (DEAD as gate).
- **HIGH (NEW):** `enty_pktdeal_cfg` is the SPA's only per-(ingress-port × protocol) action
  table (reg_id 67+proto, sub_idx=port); mainline replays it with PP0 action for all ports.
- **MEDIUM:** exact match/hash-RAM bit packing (transcribed, dense — re-derive or replay raw on
  implement); enty_pktdeal action-code semantics (0=fwd/1=trap/2=drop inferred).
- **OPEN:** whether port1's enty_pktdeal block actually differs (needs the §6 live dump);
  `_LANCHOR1`/`DAT_0004eee4` literal bytes (in tm.ko .rodata, not this dump).
