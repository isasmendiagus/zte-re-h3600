# Phase 6 / Stage 0c — Linux flow_offload/flowtable hooks survey + minimal plan for zx-dsa/zx-eth

2026-06-04, branch phase6-hw-offload. How mainline 6.6 delivers established-flow offload to a driver,
using drivers/net/ethernet/mediatek/mtk_ppe_offload.c as the reference, and the minimal hook set for
our driver to install CLA ram2-6 forward entries (ffe_cla_hash_entry_re.md).

## The Linux offload path (two front-ends, one driver callback)
1. **netfilter flowtable (the FFE analog — automatic on conntrack ESTABLISHED):** an `nft` flowtable
   with `flags offload` bound to the LAN+WAN devices. After a flow is ESTABLISHED + a few packets,
   nf_flow_table_offload pushes it to the driver as a TC_SETUP_FT block → FLOW_CLS_REPLACE. This is
   the closest match to stock's FFE (conntrack-driven, no explicit tc rules). net/netfilter/nf_flow_table_offload.c.
2. **tc flower hw-offload (explicit):** `tc qdisc add ... ingress` + `tc filter ... flower skip_sw
   action ...` → TC_SETUP_BLOCK + TC_SETUP_CLSFLOWER. Same driver cb.

## Minimal driver hook set (mirror mtk)
- `.ndo_setup_tc(dev, type, type_data)` on the netdev → handle **TC_SETUP_BLOCK** and **TC_SETUP_FT**
  → `setup_tc_block(dev, f)`: only `FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS`; on FLOW_BLOCK_BIND alloc+
  add a `flow_block_cb` (flow_block_cb_alloc/incref/add), on UNBIND decref/remove. (mtk:553-619)
- block cb `setup_tc_block_cb(type, type_data, cb_priv)`: only `TC_SETUP_CLSFLOWER` →
  `flow_offload_cmd(cls)` dispatch (mtk:553-570, 527-545):
  - **FLOW_CLS_REPLACE** → parse + install a CLA entry; track in an rhashtable keyed by `cls->cookie`.
  - **FLOW_CLS_DESTROY** → look up cookie → remove the CLA entry (zx_cla del / write invalid).
  - **FLOW_CLS_STATS** → read the entry's HW packet/byte counter → `flow_stats_update(...)` (this is
    what keeps the conntrack/flowtable entry alive = AGING; mirrors stock zte_api_fast_l3_session_use).
- init: `rhashtable_init(&flow_table, ...)` for the cookie→entry SW map (mtk:632 mtk_eth_offload_init).
- Which netdev gets `.ndo_setup_tc`? The bridged/routed datapath devices — for DSA, the **user ports
  (lanN)** and/or the conduit; the flowtable binds to the netdevs in the forwarding path (LAN lan1 +
  WAN lan4). Start by wiring it on the DSA user-port netdevs (zx-dsa) and the conduit (zx-eth "sw").

## flow_rule → CLA ram2-6 forward entry mapping (the heart of REPLACE)
Parse via flow_rule_match_* (mtk:240-345):
| Linux match (FLOW_DISSECTOR_KEY_*) | → CLA hash entry field (ffe_cla_hash_entry_re.md) |
|---|---|
| META (ingress ifindex)            | inport (entry byte 0xe/0xf; map ifindex→regport) |
| BASIC (ip_proto, n_proto)         | proto in the 5-tuple key |
| IPV4_ADDRS (src/dst)              | key src/dst IP |
| PORTS (src/dst)                   | key src/dst port |
| (ETH_ADDRS / VLAN — optional)     | L2 rewrite / vlan fields |
Parse the flow_action list (mtk:315-345):
| FLOW_ACTION_REDIRECT (act->dev)   | egress UNI/gemport (entry param_4[1..2]); map odev(lan/wan)→port |
| FLOW_ACTION_MANGLE (NAT rewrite)  | the entry NAT-rewrite fields (❓ exact bits — 0b ground-truth) |
| FLOW_ACTION_CSUM / VLAN_* / PPPOE | csum/vlan/pppoe entry flags (later) |
Then: compute the hash slot (cla_get_hash_poly_config + aclGetAvailableHashAddr — ❓ poly) and write
via **zx_cla_write_entry(ram_id∈2..6, slot, 17-word entry)** (already in zx-eth-main.c:1994). Verify
with `clapeek`.

## Kernel config to ADD (Phase 6 fragment) — currently OFF
build/.config has CONFIG_NETFILTER_INGRESS=y but NOT: **CONFIG_NF_FLOW_TABLE**, **CONFIG_NF_FLOW_TABLE_INET**,
**CONFIG_NET_CLS_FLOWER**, **CONFIG_NET_CLS_ACT**, **CONFIG_NET_ACT_CT**, **CONFIG_NF_FLOW_TABLE_PROCFS**.
Add these to a phase6 config fragment (or netfilter.fragment) before Stage 1. (nftables flowtable also
needs nft userspace with flowtable support — busybox lacks it; use a clean `nft` or the tc-flower route
for the first bring-up.)

## ⇒ Stage 1 (next-next): plumbing only
Add `.ndo_setup_tc` + block cb + rhashtable to zx-dsa/zx-eth; on FLOW_CLS_REPLACE just LOG the parsed
5-tuple + in/out port + actions (NO chip write yet). Bring up the nft flowtable (or tc flower) over
lan1↔lan4, run iperf, confirm the REPLACE callback fires with the right tuple in dmesg. Then Stage 2
writes the CLA entry.

## UNKNOWNS carried
- NAT-rewrite CLA entry bits + the hash poly/slot alloc (0b koprobe/clapeek ground-truth on a stock flow).
- Whether to bind the flowtable on DSA user ports vs conduit (test in Stage 1).
