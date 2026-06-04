# Phase 6 / Stage 0a-deep — the HFF install reaches the CLA HASH TABLE (static RE)

2026-06-04, branch phase6-hw-offload. Continues ffe_hardfast_install_re.md. Traced
`zte_api_fast_l3_session_add` (tm.c:59030) down to the actual chip programming: **a stock hardfast
session = a CLA HASH-TABLE entry** (5-tuple key → forward action), written via the CLA indirect
cmd/addr/data interface. This is the same CLA hash described in memory zte-cla-ram-layout (ram2-6
per-inport hash) — and confirms why mainline (which installs NO hash entries) has the CLA trap-all
behaviour of zte-hw-forwarding-deadend.

## The full install stack (all in decomp_all_tm.c, module tm_acl_v2.c)
```
zte_api_fast_l3_session_add(ptFastL3Session, &result)            tm.c:59030
  builds entry local_e4[~0xbc] + flags local_148 (bits 0x4 / 0x20 / 0x800000) + out local_15c
  → tm_add_acl_flow_rule(entry, &flags, &out_idx)                tm.c:54261
      g_qosEn = (entry[+0xc]==2)
      → addFlowOperInfo(flags, entry, &handle)                   tm.c:51948  (alloc flow-oper handle)
      → if (g_fast_opti && entry[+0xc]-3 in [0..5]):
            tm_acl_fast_add(entry, handle, out_idx)              tm.c:54225
              → tm_acl_fast_add_v4v6(...)                        tm.c:52521  ← the CLA hash install
        else: addAclRule()                                      tm.c:53798  (slow/TCAM rule path)
  After add: SW shadow hash — cla_list_hash_addr_gen(key,0x28)&0x1ff (9-bit, 512 buckets, 40-byte
  tuple) → tm_findFastIdxByTuple → kmem_cache node (0x20B), stores flow idx at node+0x30.
```

## The CLA hash write (tm_acl_fast_add_v4v6, tm.c:52521)
```
cla_get_hash_poly_config(poly)                       — hash polynomial config
aclGetExtIdxRuleRamAddrByPort(entry[+8], &ramaddr)   — rule RAM addr by (in)port
tm_acl_get_fastHashRule(handle, entry, ..., rule64)  — BUILDS the hash rule entry (auStack_64)
aclGetAvailableHashAddr_constprop_13(mode, &x, poly, &slot)   — find a free slot
   mode 0 = INTERNAL hash → cla_set_hash_table(slot & 0x7fff, rule64)        (15-bit addr)
   mode 1 = EXTERNAL hash → cla_set_external_hash_table(slot & 0xffff, n, rule64) (16-bit addr)
   mode 2 = (fallback) → cla_set_hash_table(slot & 0x7fff, rule64)
   result word param_5[2] = slot|0x10000 (ext) ; param_5[3] = uVar3|0x10000000
   s_aclHashUsedCnt[] usage counters (+0x208 offset region for external)
```
So: **internal CLA hash = 0x7fff (32768) slots; external CLA hash = 0xffff (65536) slots.** Each
offloaded flow consumes one hash slot keyed by its 5-tuple.

## The MMIO (cla_set_hash_table, tm.c:3366-3553)
`cla_set_hash_table(idx, entry)` → **`cla_set_indirect_rw_cmd(0, idx, entry)`** (tm.c:~3521) = the CLA
INDIRECT register write (cmd/addr/data with a busy-wait `do{}while(busy)` poll, tm.c:~3484). Mode arg
0 = write. The rule entry has GPON-aware action fields (printk at tm.c:~3415): `e8_en`,
`cmd_flow_id`, `tcnt_gpid_rp_en`, `gemport_uni_id` (= entry[5] bitfields) — i.e. the action carries
egress gemport/uni id + counters/policer enables, not just a LAN port.

## What we must program per offloaded flow (for the Linux backend)
1. Build a CLA hash rule = {5-tuple key (+ inport/direction), action: egress port/gemport+uni, MAC/
   NAT rewrite, queue/policer}. (Exact bit layout = tm_acl_get_fastHashRule — UNKNOWN, next.)
2. Compute the hash slot via the CLA poly (cla_get_hash_poly_config) + find a free slot.
3. Write it via the CLA indirect cmd interface (cla_set_indirect_rw_cmd) — internal (0x7fff) or
   external (0xffff) hash RAM.
4. Maintain a SW shadow (5-tuple→slot) for del/aging; del via tm_del_acl_flow_rule (tm.c:54092) →
   the inverse CLA indirect write; aging via zte_api_fast_l3_session_use.

## UNKNOWNS → next sub-iterations
- **0a-deeper (static):** (a) `cla_set_indirect_rw_cmd` (tm.c ~near 3366) — the EXACT CLA register
  offsets (cmd/addr/data, busy bit) — cross-ref memory zte-cla-ram-layout + the clapeek recipe +
  DATASHEET CLA §; identify WHICH ram_id the L3 fast-hash uses. (b) `tm_acl_get_fastHashRule` — the
  hash-rule ENTRY bit layout (key + action fields). (c) `cla_get_hash_poly_config` /
  `aclGetAvailableHashAddr` — the hash function (so we can compute the same slot).
- **0b (koprobe):** kotrace {tm_acl_fast_add_v4v6, cla_set_hash_table, cla_set_indirect_rw_cmd,
  tm_acl_get_fastHashRule} on stock under an iperf flow; pair with fpga -r of the CLA regs to capture
  the live entry bytes + the indirect cmd sequence + the chosen slot. Grounds all of the above.
- **0c/0d:** Linux flowtable hooks + design (map: Linux flow_offload 5-tuple+action → this CLA hash
  rule; our driver computes the slot + does the indirect write).
