# Stock FFE aging / per-flow HW activity / pos32 — device-free RE (2026-07-03)

100 % offline static RE of the stock `.ko` modules (Ghidra decomp) to inform the mainline
HW-offload keepalive fix. Sources:
- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_tm.c` (tm.ko, 70 090 lines)
- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_switch.c` (switch.ko, 14 698 lines)
- prior findings `stock_extraction_config_2026-07-02.md`, `pos32_ingress_fix_2026-07-03.md`,
  `wan_ingress_data_hitrate_2026-07-03.md`; memory `zte-cla-ram-layout`, `zte-cla-hw-hash-engine`.

No device was touched. No driver code edited. Nothing committed.

---

## Q1 — Per-flow HW ACTIVITY signal — **ANSWER: a 1-bit hit/age bit per CLA entry. NO per-flow packet/byte counter, NO timestamp.**  **Confidence: HIGH.**

### What exists (and what does NOT)
- **The CLA has a dedicated per-entry "ACL aging table" — one bit per hash/rule entry, updated
  by HW.** It is a separate indirect RAM (`ram_id = 8`) addressed by the SAME slot address as the
  hash entry. This is the only per-flow field HW maintains.
- **There is NO per-flow packet counter, byte counter, or last-used timestamp.** The only
  packet/byte statistics in stock are the ADM counters, and those are **per-`(dir, wlan_id)`
  (per-subscriber), not per-flow** — see `adm_get_pkt_stastc(dir, wlan_id, out)` @ tm.c:17922
  (param 2 = `wlan_id`, validated `< 0x20`, i.e. 0–31 subscribers; `zte_api_fast_l3_session_stat`
  @ tm.c:57396 just wraps two `adm_get_pkt_stastc` calls, dir 0/1). So real per-flow pkts/bytes
  are **not** available from HW.

### The per-entry hit/age bit — RAM, addressing, read protocol
Functions (tm.ko):
- `cla_set_acl_aging_table(ram_addr, age_en)` @ **tm.c:4294** (`@0x171cc`) — writes the age bit.
- `cla_get_acl_aging_table(ram_addr, *out)` @ **tm.c:4367** (`@0x17318`) — reads the age bit.
- `tm_get_acl_flow_status(rule, *out)` @ **tm.c:54056** (`@0x5ec7c`) — the **read-and-clear**
  wrapper: reads the aging bit for the flow, then immediately `cla_set_acl_aging_table(addr, 0)`
  to reset it for the next interval (tm.c:54076–54084).
- Public API `zte_api_fast_l3_session_use` @ **tm.c:57358** (`@0x638d8`) — returns the bit as the
  flow's "in-use" status.

Both `cla_set/get_acl_aging_table` drive the **generic CLA indirect interface** via
`cla_set_indirect_rw_cmd(rw, ram_id=8, addr)` (tm.c:298), `cla_get_indirect_rw_status(&done)`
(tm.c:336), `cla_get_indirect_rw_data(0, &val)` (tm.c:394). The CMD reg value =
`addr + ram_id*0x400000 + rw*0x8000000` (tm.c:324). The CLA indirect ports are at
**CMD = 0x9238c014, DATA0 = 0x9238c01c** (base 0x9238c000 = chip 0x1CC000; confirmed live in
`stock_extraction_config_2026-07-02.md`).

**Aging-table address = the flow's hash slot.** From `tm_get_acl_flow_status` (tm.c:54067–54075):
- normal FFE hash entry (`rule[0xc] & 0x1000000 == 0`): `addr = rule[8] & 0xffff` (+0x400 if
  `rule[8] & 0x10000`) — for a hash-forwarded flow this is the install slot `raw` (0..0x207);
- direct/ACL entry (`rule[0xc] & 0x1000000 != 0`): `addr = (rule[4] & 0x1ff) + 0x400`.

### Polarity — **bit = 1 ⇒ the flow WAS matched/active since the last read; bit = 0 ⇒ idle.**  **Confidence: HIGH.**
`sw_acl_l3_hardfast_flowstatus` @ **switch.c:1890** calls `zte_api_fast_l3_session_use(...&status)`
and returns `status`; `hf_query_l3_status` @ **switch.c:1929** maps `status == 1 → active(1)`,
else `0`. Combined with the read-and-clear in `tm_get_acl_flow_status`, this is a classic
"accessed / reference bit": HW **sets** it to 1 on any packet that matches the entry; SW reads it
(1 = active), then clears it, so a subsequent read of 0 means "no packet hit this entry in the
interval". Corroborated by a live capture: `stock_extraction_config_2026-07-02.md:121-122` saw the
ram2 forward entry's **byte 0x10 bit6 toggle 0x69↔0x29 between reads** on an actively-forwarding
download flow — the same HW-hit/age bit surfaced inside the hash entry itself.

CLA global config (`cla_get_config` @ tm.c:483, `cla_set_config` @ tm.c:435) has two relevant bits:
- **`age_rd_clear` = config bit 19** (`(reg<<0xc)>>0x1f`): if 1, a HW read of the aging table
  auto-clears the bit (so the explicit `cla_set_acl_aging_table(addr,0)` becomes optional).
- **`age_mode` = config bit 3** (`(reg<<0x1c)>>0x1f`): `1 = all rule aging`, `0 = only
  highest-pri rule aging` (tm.c:68242-68246). Debugfs `gclacfg` prints both.

### Implication for the mainline driver
There **is** a real per-flow HW activity signal — a 1-bit "hit since last read" — that the driver
can read to drive FLOW_CLS_STATS **lastused** with genuine per-flow information (not an
always-alive hack). Read protocol per installed flow at its hash slot `raw`:
1. write `0x9238c014 = raw | (8<<22) | (1<<27)`  (i.e. `raw | 0x0A000000`, ram_id=8, rw=1=read);
2. poll the indirect access-done status (`cla_get_indirect_rw_status`) until done;
3. read `0x9238c01c` → **bit0 = "flow hit since last read"**;
4. clear for the next interval: either set `age_rd_clear` (config bit 19) once at init, or write
   `0x9238c014 = raw | (8<<22) | (0<<27)` + `DATA0 = 0` (mirrors `cla_set_acl_aging_table(raw,0)`).

Report `lastused = now` whenever the bit reads 1 for that flow's slot; leave it unchanged when 0.
**There is no HW pkts/bytes counter to report** — for FLOW_CLS_STATS pkts/bytes the driver has
only the per-subscriber ADM counters (coarse) or must keep its own SW estimate; the *activity /
lastused* dimension, which is what the keepalive actually needs, is available exactly.

---

## Q2 — Stock FFE flow aging / eviction — **ANSWER: HW provides the hit-bit; the GC POLICY is a userspace poll-and-delete loop, not a kernel thread.**  **Confidence: HIGH.**

- **No kernel aging thread / timer exists for FFE flows.** grep of both modules found no
  `mod_timer / kthread_run / schedule_delayed_work / timer_setup` driving flow aging in tm.ko or
  switch.ko. The kmods expose only the ioctl-style API surface:
  - install: `sw_acl_l3_hardfast_session_add` @ switch.c:1797 → `zte_api_fast_l3_session_add`
    @ tm.c:59030;
  - delete: `sw_acl_l3_hardfast_session_del` @ switch.c:1847 → `zte_api_fast_l3_session_del`
    @ tm.c:59966 (also `zte_api_fast_l3_session_clr` @ tm.c:57322 flushes all 0x200 buckets);
  - **activity query: `sw_acl_l3_hardfast_flowstatus` @ switch.c:1890 / `hf_query_l3_status`
    @ switch.c:1929 → `zte_api_fast_l3_session_use` → the read-and-clear hit-bit.**
- **What stock READS to decide "still active": the HW hit-bit only** (via `session_use`). It does
  NOT consult a SW conntrack ref or a timestamp inside the kernel. A userspace daemon periodically
  polls `hf_query_l3_status` for each installed session; a session that reads `0` (no hit) across a
  poll interval is deemed stale.
- **How stock DELETES a stale flow:** the daemon calls `session_del` →
  `zte_api_fast_l3_session_del`, which tears down the PM/CLA entry (equivalent of the driver's
  `cls_flower_del`: zero the 15-word entry so `valid_en`/key-compare misses). Not the raw
  `cla_set_hash_table` clear directly — it goes through the session-del path that also releases
  next-hop/flow_info slots.

### Implication for the mainline driver
Stock's GC is **exactly the pattern to mimic** for mainline's flowtable keepalive, and it says the
right activity signal is the **per-flow HW hit-bit**, sampled once per GC interval, read-and-clear:
- On each flowtable GC/stats callback, read the hit-bit for the flow's slot (Q1 protocol). If 1 →
  the flow moved packets in HW this interval → report `lastused = now` (keeps nft from tearing it
  down). If 0 → do NOT bump lastused → let the normal idle timeout expire it.
- This neither churns (a flow with real HW traffic is never seen as idle) nor leaks (a genuinely
  idle flow's bit stays 0 → it ages out normally). It is strictly better than the current
  "always report lastused" keepalive, which can leak flows that quietly went idle.
- Note: `age_mode` (config bit 3) chooses whether all rules or only the highest-priority rule age;
  for the FFE hash entries mainline installs, set/verify it so per-entry aging is meaningful.

---

## Q3 — pos32 / inport bit — **ANSWER: pos32 is a single ingress-class bit at HW-key bit 32, empirically WAN/RGMII=1 vs LAN/GePHY=0; NOT a low-bit-of-inport that the SW builder writes.**  **Confidence: MEDIUM.**

### What is established (from prior on-device captures)
- The HW-extracted key (`gparsehashkey`, 0x9238c260) has **word0 = 0x48000000 INVARIANT across
  both directions** (UP LAN-ingress and DN WAN-ingress); the ONLY ingress-dependent bit is
  **pos32 = bit0 of word1**, sitting immediately below the 5-tuple field block (which starts at
  bit33 = proto). UP key word1 low byte `0x0c` (proto 6 <<1, pos32=0); DN `0x0d` (pos32=1).
- Empirically universal: **24/24 DN (WAN/RGMII, regport5) captures = pos32 1; all UP/LAN captures
  = pos32 0** (`wan_ingress_data_hitrate_2026-07-03.md`). The mainline fix (build #474) sets
  `kb[4] |= 1` for the WAN-side entry and PROVED byte-exact key + slot match in both directions
  (`pos32_ingress_fix_2026-07-03.md`).

### What the decomp adds
- The SW structured 45-byte hash key (`cla_acl_hash_addr_gen` @ tm.c:4154) DOES carry a full
  multi-bit inport (byte0 bits[7:5] + byte1<<3 + byte2 bit0 = 11-bit inport) plus outport,
  tag_level, l2_type, pppoe, ex_rule_id, direct. But **that is a DIFFERENT serialization from the
  HW `gparsehashkey`** the driver replicates — and critically, in the HW key word0 is invariant,
  i.e. the HW key does **not** expose the full 11-bit inport. So pos32 is not "bit N of the inport
  field" in the HW key; it is the single ingress-discriminator bit the HW folds into the key.
- The stock fast-rule builder `tm_acl_get_fastHashRule` @ **tm.c:49213** packs inport from
  `param_2[1]` into entry bytes 0xe/0xf (tm.c:49325-49335, gated by `param_2[0x1c] & 4` = an
  inport-match-enable), and header bits from `param_2[0xb0]/[0xb1]` into bytes 0/6 — i.e. stock's
  installed-entry hash naturally incorporates the ingress port through the SW CRC path, which is
  why stock never needs an explicit "pos32" step: its install-slot and its HW-extraction-slot are
  computed from consistent ingress-aware inputs. The mainline driver, which builds the compact HW
  key form directly, must instead reproduce the one bit (pos32) the HW derives from ingress.
- Because word0 is invariant and only one bit changes, pos32 is best modelled as a **1-bit ingress
  CLASS bit (WAN/RGMII vs LAN/GePHY)**, not the LSB of a wider inport field. A pure "low bit of
  regport" rule is *inconsistent* with the class model (regport1 and regport3 are odd LAN ports →
  would give pos32=1), but the on-device data only exercised one LAN port (lan2) and the WAN port
  (regport5), so a low-bit-of-inport rule cannot be *fully* excluded from captures alone. The
  structural evidence (invariant word0 ⇒ no full inport in the HW key) favors the class bit.

### Implication for the mainline driver
- The current fix — `is_wan = (in/eg regport == WAN regport 5) → kb[4] |= 1`, else 0 — is
  **correct for every port tested and is the right generalization** if pos32 is a WAN/LAN class
  bit. Keep deriving it from ingress-port CLASS (WAN/RGMII ⇒ 1, GePHY/LAN ⇒ 0) rather than from a
  raw inport LSB.
- **To fully pin it** (only if a third distinct ingress port ever becomes testable): install a
  flow ingressing on a *second, odd-numbered LAN regport* and read `gparsehashkey` bit32. class=0
  there confirms "WAN/LAN class"; =1 would mean "low bit of inport". Until then treat the rule as
  ingress-class with MEDIUM confidence.
- Consistency (matches the pos32 finding): pos32 affects hash/slot ONLY; the stored windata
  byte-compare starts at proto (bit33), so there is no windata byte to also set for pos32.

---

## Bottom line for the keepalive fix
1. A **real per-flow HW activity bit exists** (CLA aging table, ram_id 8, indexed by hash slot,
   read via 0x9238c014/0x9238c01c, bit0 = hit-since-last-read, read-and-clear). Use it to drive
   FLOW_CLS_STATS **lastused** with genuine per-flow signal.
2. **No per-flow pkts/bytes counter or timestamp** exists — only per-subscriber ADM counters. So
   pkts/bytes for FLOW_CLS_STATS must remain a SW estimate; only *lastused/activity* is HW-exact.
3. Stock's GC = **poll the hit-bit per interval, delete on no-hit** (userspace policy, kernel just
   exposes add/del/use). Mirror it: bump lastused only when the bit reads 1 → no churn, no leak.
4. pos32 = single **ingress-class bit** (WAN/RGMII=1, LAN/GePHY=0); the current `regport==5` fix is
   the correct generalization pending a second-LAN-port capture.
