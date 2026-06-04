# Phase 6 / Stage 0d — HW flow-offload backend DESIGN (synthesis)

2026-06-04, branch phase6-hw-offload. Synthesizes Stage 0 RE (ffe_hardfast_install_re,
ffe_hardfast_regwrites_re, ffe_cla_hash_entry_re, phase6_linux_flowtable_survey) into a concrete,
staged implementation plan for our zx-dsa/zx-eth driver.

## The hook (DSA gives us this for free)
DSA 6.6 already wires each user-port (lanN) netdev's `ndo_setup_tc` → block → cls_flower, dispatching
to **`dsa_switch_ops.cls_flower_add / cls_flower_del / cls_flower_stats(ds, port, cls, ingress)`**
(net/dsa/slave.c:1600-1648; hooks declared include/net/dsa.h:1087). So zx-dsa.c implements those three
ops — NO custom ndo plumbing needed. Requires CONFIG_NET_CLS_FLOWER=y (+ NET_CLS_ACT, NET_ACT_*).
(The netfilter-flowtable/conntrack-driven path = TC_SETUP_FT is the eventual FFE analog; check DSA's
TC_SETUP_FT support when we get there — for the first milestones use explicit tc-flower, deterministic.)

## Two CLA mechanisms — pick the EASY one first
- **ram1 = rule TCAM** (cla_set_extra_rule_table @ tm.c:2870; 160 ent × 17 words; winoffset/winmask +
  inport/outport flags). Directly addressed (write rule N), NO hash function needed.
- **ram2-6 = hash** (cla_set_hash_table; stock HFF uses this for scale; needs the hash poly + slot alloc).
⇒ **Stage 2 (first HW forward) = a ram1 TCAM rule** (match 5-tuple → forward-to-port action): simplest
possible, sidesteps the unknown hash poly. **Stage 2b** migrates to the ram2-6 hash (stock-parity,
scales to many flows). Both use the already-implemented zx_cla_write_entry (zx-eth-main.c:1994) +
clapeek read-back.

## Data structures (in zx-dsa or a new zx-offload.c)
- `struct zx_off_flow { struct rhash_head node; unsigned long cookie; u8 ram_id; u16 slot;
   /* 5-tuple + in/out port for debug */ };`
- `rhashtable flow_table` keyed by `cls->cookie` (cls_flower_del/stats look up by cookie).
- a small slot allocator (bitmap) for ram1 rule indices (and later ram2-6 hash slots).

## cls_flower_add → CLA entry (the core)
1. Parse `f->rule` (struct flow_cls_offload): flow_rule_match_basic (ip_proto), _ipv4_addrs (src/dst),
   _ports (src/dst), _meta (ingress ifindex→regport via memory zte-port-numbering). Reject non-5-tuple.
2. Parse `flow_action`: FLOW_ACTION_REDIRECT → egress dev → regport/uni (action target);
   FLOW_ACTION_MANGLE → NAT rewrite (defer to Stage 3 — needs the 0b NAT-bit ground-truth).
3. Build the 17-word CLA entry:
   - ram1 (Stage 2): winoffset/winmask covering the 5-tuple bytes in the packet + action = forward to
     outport (the byte0x39 inport/outport flags from cla_ram_layout_re.md). Match the bit layout used
     by the boot snapshot (zx_cla_table.h) so we don't fight the existing ram1 rules.
   - ram2-6 (Stage 2b): the forward hash entry from ffe_cla_hash_entry_re.md (egress uni/gemport in
     param_4[1..2], valid byte0x10), slot from the hash poly.
4. `zx_cla_write_entry(ram_id, slot, words)`; stash {cookie,ram_id,slot} in the rhashtable.
- **del**: lookup cookie → write an invalidated entry (clear valid_en byte0x10) / free slot.
- **stats**: read the entry's HW counter (tcnt field) via zx_cla_read_entry → flow_stats_update (aging).

## Stage milestones + success metrics
- **S1 plumbing**: implement the 3 ops; cls_flower_add only LOGS the parsed 5-tuple + in/out port +
  actions. Build+boot. `tc qdisc add dev lan1 clsact; tc filter add dev lan1 ingress flower skip_sw
  ip_proto tcp dst_ip <x> action mirred egress redirect dev lan4`. ✔ = dmesg shows the parsed flow.
- **S2 first HW forward (ram1)**: write the TCAM rule; ✔ = `clapeek 1 <slot>` reads it back AND under
  iperf (LAN client→WAN via netns rig) the **pipeline_stats/hw_trap CPU counters stay FLAT** for that
  flow (traffic no longer trapped) while throughput rises. This is the headline proof "HW forwards."
- **S2b**: same via ram2-6 hash (stock-parity).
- **S3 NAT** (needs 0b NAT-bits), **S4 bidir+teardown+aging**, **S5 HW QoS** (hf_entry_police2 →
  ram?/policer), **S6 perf** (max offloaded throughput vs SW).

## Risks / open
- The ram1 rule must route a hit to the chosen egress WITHOUT the trap that currently dominates
  (zte-hw-forwarding-deadend) — i.e. the action must override the per-inport trap. Verify by reading a
  stock forward rule (0b) or by experiment (write rule, watch hw_trap).
- The ingress classifier may require the packet to first match a ram1 rule that POINTS into the ram2-6
  hash — confirm the ram1→ram2-6 chaining when we do S2b.
- Whether DSA delivers a clean 5-tuple to cls_flower_add for a routed (L3) flow on an L2 switch port —
  may need the flow installed on the conduit or via the nf-flowtable path instead. Test in S1.
- NAT-rewrite CLA bits + hash poly still need 0b (clapeek/koprobe on a stock flow) before S2b/S3.

## Config to add (netfilter.fragment, before S1)
CONFIG_NET_CLS_FLOWER=y, CONFIG_NET_CLS_ACT=y, CONFIG_NET_ACT_MIRRED=y, CONFIG_NET_ACT_GACT=y,
CONFIG_NET_SCH_INGRESS=y (clsact); for the later conntrack path: CONFIG_NF_FLOW_TABLE(+_INET)=y,
CONFIG_NET_ACT_CT=y.
