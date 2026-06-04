# Phase 6 research — ADVERSARIAL review (before writing driver code)

2026-06-04. Skeptical re-verification of the 7 Phase-6 RE docs against the actual sources
(decomp_all_switch.c, decomp_all_tm.c, linux-v6.6 driver/DSA). Read-only except this file.
Methodology: grep to each cited symbol/line, read ~40–120 line windows, cross-check offsets/bitmasks.

---

## VERDICT: **YES, WITH FIXES**

The HFF→CLA call chain is REAL and the structural claims hold up: every named function exists, the
edges are real, the struct offsets in `zte_api_fast_l3_session_add` are accurate, the CLA indirect
cmd encoding (`addr | ram_id<<22 | rw<<27`) is independently confirmed in BOTH stock and our driver,
and the DSA cls_flower hooks exist. **Stage 1 (plumbing: add the 3 dsa ops + log the parsed flow) is
safe to start now.** But there are **two material misreads that will produce wrong code if copied
verbatim into Stage 2**, several wrong file:line citations, and one over-optimistic verification
assumption. Fix the items in the BUGS list (esp. #1, #2, #3) before writing the CLA-entry builder.

The single biggest *unproven* assumption — whether a CLA forward action actually overrides the
SPA/per-inport trap so the flow forwards in HW — is correctly flagged as a risk by the design docs
and is NOT resolved by the static RE. Stage 2's success metric must treat this as the experiment.

---

## PER-CLAIM

### Claim 1 — the call chain. **CONFIRMED (with one mischaracterization).**
- `l3_hardfastReg` @ switch.c:1386 (hdr `@00012404`) → `npu_hff_register(&local_28,&local_18)`
  @ switch.c:1407; def @ switch.c:10920. ✅ Registers 4 handlers incl `hf_set_l3_entry` @ :1398.
- `hf_set_l3_entry` def @ switch.c:1825 → `sw_acl_l3_hardfast_session_add` @ :1797/1800 →
  `_part_1` @ :1476/1478 → call `zte_api_fast_l3_session_add(local_b8,&local_cc)` @ switch.c:1734. ✅
- Called from switch init @ switch.c:2734. ✅
- **MISCHARACTERIZATION:** the docs (install_re.md:36, DATASHEET:1865) call switch.c:14651 a
  "thin" wrapper that forwards to tm.c:59030. It is NOT a thin wrapper — switch.c:14651–14660 is a
  Ghidra **decompilation failure**: `void zte_api_fast_l3_session_add(void){ halt_baddata(); }`
  ("WARNING: Bad instruction - Truncating control flow"). It is the cross-module import/PLT stub for
  the tm.ko export. The runtime call resolves to **tm.c:59030**, which is the right target — so the
  conclusion is correct, but "thin wrapper" is wrong and should read "unresolved cross-module stub".
- The REAL impl `zte_api_fast_l3_session_add(byte*,uint*)` @ tm.c:59030/59032. ✅ We followed the
  right one. Struct offsets all verified in-body: direction `*param_1` @59121; `+0x9d==0xff` sentinel
  @59122–59132; `+0x9f/+0x9c/+0x9a/+0x98` @59123,59134–59136; `+0x68`/`+0x6a` @59141–59143;
  `__memzero(local_e4,0xbc)`/`local_148,100`/`local_15c,0x14` @59118–59120; `fast_api_busy_lock`
  @59140. ✅ All accurate.

### Claim 2 — the chip-write path. **CONFIRMED chain; TWO misreads in the slot/MMIO detail.**
- `zte_api_fast_l3_session_add` → `tm_add_acl_flow_rule(local_e4,&local_148,&local_15c)` @ tm.c:59875
  (def @54261/54263). ✅ Args = (entry, &flags, &out_idx) ✅.
- In `tm_add_acl_flow_rule`: `g_qosEn = (entry[+0xc]==2)` @54277 ✅; `addFlowOperInfo` @54278 ✅;
  fast gate `if ((g_fast_opti==0) || (5 < entry[+0xc]-3U))` @54280 → else `tm_acl_fast_add` @54284. ✅
  So fast-path requires `entry[+0xc] ∈ [3..8]` (DATASHEET "[3..8]" ✅; regwrites_re.md "[0..5]" of
  `-3` = same set ✅).
- `tm_acl_fast_add` @54225/54227 → `tm_acl_fast_add_v4v6(...)` @54238/54247 etc (def @52521). ✅
- Inside v4v6: `cla_get_hash_poly_config(auStack_b4)` @52612 ✅; `aclGetExtIdxRuleRamAddrByPort
  (entry[+8],…)` @52619 ✅; `tm_acl_get_fastHashRule(...,auStack_64)` @52627 ✅; then
  `aclGetAvailableHashAddr_constprop_13(mode,…)` with **mode 0 @52704 → cla_set_hash_table(&0x7fff)
  @52734**, **mode 1 @52770 → cla_set_external_hash_table(&0xffff) @52800**, **mode 2 @52806 →
  cla_set_hash_table(&0x7fff) @52838**. ✅ `param_5[2]=slot&0xffff|0x10000` (ext) @52797 ✅;
  `param_5[3]=uVar3|0x10000000` @52851 ✅. The internal/external/fallback mapping is correct.
- `cla_set_hash_table` is ram_id **2..6** by addr banks (param_1<0x100→2, <0x180→3, <0x1c0→4,
  <0x200→5, else→6) @52496–52520 of the fn (decomp_all_tm.c:3496–3520). ✅ Matches cla_ram_layout_re.

  **MISREAD 2a (capacity):** "internal hash = 0x7fff (32768) slots; external = 0xffff (65536)"
  (regwrites_re.md:37, DATASHEET:1883–1884) is a **bitmask-as-capacity error**. The `& 0x7fff` /
  `& 0xffff` only strip the found-flag from `local_bc` (success is signalled by the **sign bit**:
  `if ((int)local_bc < 0)` @52706/52772/52808). The REAL internal capacity is hard-bounded:
  `cla_set_hash_table` rejects any `param_1 >= 0x208` → **520 entries** (decomp_all_tm.c:3472,
  `if (param_1 < 0x208)`), exactly the 520 of cla_ram_layout_re.md. Writing `slot & 0x7fff` for a
  slot ≥ 0x208 would FAIL with "input invalid parameter". Do NOT size any slot allocator at 32768.

  **MISREAD 2b (MMIO signature):** "`cla_set_hash_table(idx,entry) → cla_set_indirect_rw_cmd(0, idx,
  entry)`" (regwrites_re.md:42; DATASHEET:1885 "cla_set_indirect_rw_cmd(0, slot, entry)") is wrong.
  Real signature: `cla_set_indirect_rw_cmd(ind_rw_en, ram_id, ram_addr)` (decomp_all_tm.c:300) — the
  3rd arg is the **address**, not the entry. Stock calls it as `cla_set_indirect_rw_cmd(0, uVar3=
  ram_id, param_1=bank-relative-addr)` @3521. The 15 entry words are written SEPARATELY via a loop of
  `cla_set_indirect_rw_data(word_idx, value)` @3525–3530 (0xe..0, 15 words from `param_2+0x3c`
  downward), and the busy-poll is `cla_get_indirect_rw_status()` in a `do{}while` (≤0x13 tries)
  @3476–3484 — **inside cla_set_hash_table, not inside cla_set_indirect_rw_cmd** as the doc implies.
  The cmd ENCODING is nonetheless verified correct: cmd = `ram_addr + ram_id*0x400000 +
  ind_rw_en*0x8000000` = `addr | ram_id<<22 | rw<<27` (decomp_all_tm.c:324). ✅
- Entry size nit: stock writes a **15-word** entry (ram2-6), not 17. cla_ram_layout_re.md:15 says 15
  ✓; but regwrites_re.md/DATASHEET loosely say "17-word entry" — harmless (our 17-word writer zero-
  pads), but the ram2-6 builder must populate 15 words (bytes 0..0x3b), not 17.

### Claim 3 — forward-entry layout (`tm_acl_get_fastHashRule` @ tm.c:49213). **MOSTLY CONFIRMED; one bit-nibble error + a citation hazard.**
- Def @49213/49215, sig `(int param_1, byte *param_2 /*flow*/, uint param_3, byte *param_4 /*entry*/)`. ✅
- **CITATION HAZARD:** ffe_cla_hash_entry_re.md cites "tm.c:142–150 / 197–207 / 111 / 103 / 121–122 /
  151,201". Those are **function-local line numbers**, NOT decomp_all_tm.c global lines (the fn starts
  at global 49215). A future reader greps the wrong place. Re-cite as global lines (below).
- egress target = `flow+0xb2`: switch on `*(ushort*)(param_2+0xb2)` gated by `*(int*)(param_2+0x10)==1`
  @49364–49408, with the "Invalid target uni port!" validation @49383. ✅ The `==0` (direct) branch
  @49414–49420 also reads `param_2[0xb2]`. ✅
- **BIT ERROR (load-bearing):** ffe_cla_hash_entry_re.md:33 + DATASHEET:1904 say the target goes to
  "`param_4[1]` (**low nibble**) + param_4[2]". The code @49410–49411 writes
  `param_4[2]=(uVar10>>4)` and `param_4[1] = param_4[1]&0xf | (uVar10&0xf)<<4` — i.e. the target's low
  nibble lands in the **HIGH nibble of param_4[1]**. The LOW nibble of param_4[1] is preserved (it
  holds flow+0xb0's nibble from @49360). So: **target = param_4[1][7:4] + param_4[2]**, not the low
  nibble. The Linux→CLA mapping table must encode it in the high nibble or the egress port is wrong.
- valid/direction byte 0x10: `param_4[0x10] |= 0x40` (valid_en bit6) @49319; `param_4[0x10] |=
  (flow+0x10 & 1)<<5` (direct bit5) @49324; printk decode confirms byte0x10 = {valid_en@bit6,
  direct@bit5, rule_mode@bit4} (decomp_all_tm.c:3440–3442). ✅ matches "valid byte 0x10".
- `param_4[0x12]` bit2 = `(flow+0x10==0)<<2` @49316 ✅.
- inport-like `param_4[0xe]=(v<<6)`, `param_4[0xf]|=(v>>2)` @49334–49335 ✅ FOR THE FIELD — **but the
  source is NOT flow+0x10**. ffe_cla_hash_entry_re.md:39 says these come from "flow+0x10". In the code
  `v=uVar8` @49334 was reassigned @49326–49332 to `(flow[1] & 7)` gated by `(flow+0x1c & 4)`, i.e.
  derived from `param_2[1]`, not `param_2+0x10`. Correct the provenance note.

### Claim 4 — "our driver ALREADY implements the CLA write." **CONFIRMED FUNCTIONALLY; WRONG LINE NUMBERS + a read-back caveat that undercuts the verification plan.**
- `zx_cla_write_entry` is at **zx-eth-main.c:2035** and `zx_cla_read_entry` at **:2053** — NOT
  1994/2007 as cited in cla_ram_layout_re.md:8, ffe_cla_hash_entry_re.md:13, design:21/41,
  survey:45, DATASHEET:1897. Lines 1994/2007 land in the *pp_pm* code (zx_pp_pm_write_entry @1956).
  Fix the citation in all 5 places.
- Semantics verified: CMD `0x1CC014`, DONE `0x1CC018`, DATA0 `0x1CC01C` (stride 4) @2018–2020 ✅;
  write = `writel(data[0..16]); writel(ram_addr | ram_id<<22, CMD)` @2042–2044 (rw=0 implicit) ✅;
  read sets `CLA_RAM_READ = 1u<<27` @2059 ✅. So `cmd = addr|ram_id<<22|rw<<27` ✅, usable signature.
- debugfs `clapeek` (write "<ram_id> <addr>") @4201/4581 and `cladump` (ram7) @4160/4580 EXIST. ✅
- **CAVEAT that weakens the de-risk:** `zx_cla_read_entry` has a documented **word0 off-by-one** bug
  (zx-eth-main.c:2062–2068): a single back-to-back indirect read returns `data[1..16]` correctly but
  `data[0]` is the *next* entry's word0. The forward ACTION bits live in bytes 0..5 = **word0/word1**
  (tcont/queue/act in word0 per the printk @3466–3469; gemport_uni_id/e8_en in word1). So
  "VERIFY the forward entry with clapeek" (ffe_cla_hash_entry_re.md:48, design S2 metric) is
  **unreliable for exactly the action word we most need to confirm**. Mitigations: read the
  *previous* slot's word0, or read twice, or use stock `fpga -r` (no shift). Don't gate S2 success on
  clapeek word0 alone.

### Claim 5 — DSA hooks + the routed-flow/TCAM-override risk. **HOOKS CONFIRMED; the core de-risk is UNVERIFIED and partly contradicted.**
- `dsa_switch_ops.cls_flower_add/del/stats` @ include/net/dsa.h:1087/1089/1091 ✅. Dispatch in
  net/dsa/slave.c:1566–1597 (`ds->ops->cls_flower_add(ds,port,cls,ingress)` @1569), `TC_SETUP_CLSFLOWER`
  case @1627. (Doc cited "1600–1648" — approximately right, off by ~30; update to 1566/1627.)
- `TC_SETUP_FT` @1708 → **`dsa_slave_setup_ft_block` forwards to the CONDUIT master's ndo_setup_tc**
  @1696 — it does NOT call a dsa_switch_op. So the netfilter-flowtable (FFE-analog, conntrack-driven)
  path must be implemented on the **zx-eth conduit**, not zx-dsa. survey.md:28 ("wire it on the DSA
  user-port netdevs and the conduit") is misleading for the FT path; design.md:12 hedges correctly.
  For the explicit tc-flower path (cls_flower_*), zx-dsa is right. Recommendation stands: do explicit
  tc-flower first. zx-dsa.c exists today with NO cls_flower/ndo_setup_tc ops (grep empty) — consistent
  with "we must add them".
- **HIGHEST-RISK, UNVERIFIED:** "a ram1 TCAM rule is the first easy HW forward, action overrides the
  per-inport trap." The static RE does NOT prove this. From memory [[zte-hw-forwarding-deadend]] the
  trap-vs-forward decision is a **2-bit pktdeal field per (port, proto-slot) at SPA 0x921d4300**
  (`tm_port_protocol_pktdeal_set`); the merged TCP-ACK fix worked by flipping THAT (via the SPA
  indirect write), NOT by a CLA forward action. So a CLA ram1/ram2-6 forward entry may be ANDed/ORed
  with, or gated upstream by, the SPA pktdeal trap — there is real evidence the SPA classifier sits
  *upstream* and independently traps. The design docs DO flag this (design.md:57–63, survey/risks),
  which is good — but it must be treated as **the** Stage-2 experiment, not a detail. Also: stock only
  ever installs CLA forward entries for the **L3 fast path (IPv4/IPv6 5-tuple, type∈[3..8])**; there
  is NO evidence stock uses a ram1 TCAM rule for L3 5-tuple forwarding. "ram1 TCAM = first easy HW
  forward" is the team's own simplification, not something observed in stock. Lower confidence than
  the doc's framing implies.
- L3 5-tuple delivery on a DSA *user port* for a *routed* flow: for a CPU-routed packet the L2 switch
  port sees only the first (pre-route) hop; tc-flower ingress on lanN gets the L2-presented packet.
  Whether the kernel offers a clean post-route 5-tuple+REDIRECT here is genuinely uncertain (design
  flags it, survey leans nf-flowtable). Treat as Stage-1 finding, exactly as planned.

### Claim 6 — internal contradictions / overstated ✅.
- DATASHEET:1858 marks the whole HFF block "🟡 inferred (exact chip regs pending 0a-deep)" yet the
  later 0a-deeper block (DATASHEET:1897) and ffe_cla_hash_entry_re.md present the CLA reg interface as
  "✅ already known + in driver". Both are true of different things (chain=🟡-static, CLA-iface=✅-from
  -prior-live-clapeek) but the ✅ on the *forward-entry layout* is overstated: the egress-target
  encoding has the nibble error above, and the NAT bits are honestly ❓. Net: the *interface* is ✅,
  the *entry bit layout* is 🟡 and should not be marked validated until 0b koprobe/clapeek ground-truth.
- ffe_cla_hash_entry_re.md:33 "param_4[1] low nibble" vs the actual high-nibble write = a self-
  contained error (see Claim 3).
- No contradiction found in the type-field set ([3..8]) or the cmd encoding — those are consistent
  across all docs and both sources.

---

## RANKED BUGS / RISKS (fix before/during coding)

1. **[BLOCKER for S2 correctness] Egress-target nibble is wrong.** Target uni goes to
   `param_4[1][7:4]` + `param_4[2]`, NOT param_4[1] low nibble (tm.c:49410–49411). Fix the mapping in
   ffe_cla_hash_entry_re.md:33 + DATASHEET:1904 and in the entry builder.
2. **[BLOCKER for slot allocator] Internal hash is 520 entries, not 32768.** The `&0x7fff` is a mask,
   not a capacity; `cla_set_hash_table` hard-rejects addr ≥ 0x208 (tm.c:3472). Size allocators per
   the 520-entry / ram2-6 bank map, not 0x7fff/0xffff. Fix regwrites_re.md:37 + DATASHEET:1883–1884.
3. **[HIGH — the whole thesis] CLA-forward-overrides-SPA-trap is UNPROVEN and contradicted by the
   merged TCP-ACK fix** (which used the SPA pktdeal field at 0x921d4300, not a CLA action). Make S2's
   first milestone an explicit experiment: write one forward entry, watch hw_trap/tm_rx; be ready to
   ALSO flip the SPA pktdeal slot. Don't assume the CLA action alone forwards.
4. **[MEDIUM] Wrong file:line for zx_cla_write/read_entry** (real = 2035/2053, cited = 1994/2007) in
   5 docs + DATASHEET. Correct before anyone greps 1994 and edits pp_pm by mistake.
5. **[MEDIUM] clapeek word0 off-by-one** makes "read the slot back" unreliable for the action word
   (bytes 0..5). Verify via previous-slot/double-read or stock fpga; don't gate S2 on clapeek word0.
6. **[MEDIUM] TC_SETUP_FT goes to the conduit, not zx-dsa.** The conntrack/flowtable (FFE-analog) path
   must be on zx-eth; only explicit tc-flower hits zx-dsa cls_flower_*. survey.md:28 needs the caveat.
7. **[LOW] "thin wrapper" mislabel** for switch.c:14651 (it's a Ghidra halt_baddata stub / xmodule
   import). Conclusion unaffected; fix the wording in install_re.md:36 + DATASHEET:1865.
8. **[LOW] Citation hazard:** tm_acl_get_fastHashRule offsets cited as function-local lines (103, 111,
   142–207). Re-cite as global decomp lines (49312–49464). Also note inport-field provenance is
   flow[1], not flow+0x10 (tm.c:49326–49335).
9. **[LOW] Entry width:** ram2-6 entry is 15 words (0x3c bytes), not 17 — builder must fill words 0..14.

---

## CONCRETE CORRECTIONS

- **ffe_cla_hash_entry_re.md:33 / DATASHEET:1904** — change "param_4[1] (low nibble) + param_4[2]" to
  "param_4[1] HIGH nibble [7:4] + param_4[2] (tm.c:49410–49411)". Demote the forward-entry layout from
  ✅ to 🟡 until 0b ground-truth.
- **ffe_hardfast_regwrites_re.md:37 / DATASHEET:1883–1884** — replace "internal 0x7fff (32768) /
  external 0xffff (65536) slots" with "the &0x7fff/&0xffff are masks stripping the sign found-flag;
  internal capacity = 520 entries (cla_set_hash_table rejects addr≥0x208, tm.c:3472), ram2-6 banks per
  cla_ram_layout_re.md; external (cla_set_external_hash_table) is the overflow table."
- **ffe_hardfast_regwrites_re.md:42 / DATASHEET:1885** — fix the call to
  `cla_set_indirect_rw_cmd(rw=0, ram_id, ram_addr)` (3rd arg is addr); note the 15 entry words are
  written via `cla_set_indirect_rw_data(idx,val)` (tm.c:3525–3530) and the busy-poll is
  `cla_get_indirect_rw_status` in cla_set_hash_table (tm.c:3476–3484). Keep the verified encoding
  `addr|ram_id<<22|rw<<27` (tm.c:324).
- **All CLA-write citations** — change "zx-eth-main.c:1994/2007" → "zx-eth-main.c:2035/2053".
- **ffe_hardfast_install_re.md:36 / DATASHEET:1865** — "thin @ switch.c:14651" → "unresolved cross-
  module import stub (Ghidra halt_baddata) @ switch.c:14651; real export tm.c:59030".
- **phase6_linux_flowtable_survey.md:28** — add: the TC_SETUP_FT (nf-flowtable) path forwards to the
  CONDUIT master's ndo_setup_tc (slave.c:1696), so implement it on zx-eth; only explicit tc-flower
  (cls_flower_*) reaches zx-dsa.
- **phase6_offload_design.md / DATASHEET 0a-deeper** — add an explicit caveat that no stock evidence
  shows a ram1 TCAM rule used for L3 5-tuple forwarding, and that forward-vs-trap may be gated by the
  SPA pktdeal field (0x921d4300) upstream of CLA — Stage 2 must test both levers.
