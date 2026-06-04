# Phase 6 / Stage 1 — flow-offload plumbing wired + VERIFIED (log-only)

2026-06-04, branch phase6-hw-offload. The Linux→driver HW-offload path works end-to-end.

## What was done
- zx-dsa.c: implemented dsa_switch_ops.cls_flower_add/del/stats (#ifdef CONFIG_NET_CLS_FLOWER,
  additive). cls_flower_add parses flow_rule (match basic/ipv4_addrs/ports/meta + action
  REDIRECT/MANGLE) and dev_info-logs; returns -EOPNOTSUPP (flows stay in the working SW path).
- netfilter.fragment: added NET_SCHED + NET_CLS + NET_CLS_FLOWER + NET_CLS_ACT + NET_ACT_MIRRED/GACT
  + NET_SCH_INGRESS (NET_SCHED was the parent gate that was off).
- tc: cross-built a modern static iproute2-6.1.0 tc (flower built-in; the stock tc is 2012/no-flower,
  busybox has none). configs/bin/tc + README-tc.md; staged by stage_userland.sh.

## VERIFIED on HW
`tc qdisc add dev lan1 clsact; tc filter add dev lan1 ingress protocol ip flower ip_proto tcp
dst_ip 192.168.9.2 action mirred egress redirect dev lan2` → FRC=0, and dmesg:
```
[phase6] cls_flower_add port1 ing=1 cookie=c5245800 proto=6 0.0.0.0:0 -> 192.168.9.2:0 in_ifidx=0
[phase6]   act[0]=REDIRECT dev=lan2
```
⇒ DSA routes user-port tc-flower → our cls_flower_add with the correct port (1=lan1), proto (6=TCP),
dst_ip, and the REDIRECT egress dev (lan2). Parsing is correct. The plumbing is solid.

## Gotchas
- flower syntax needs `protocol ip` BEFORE `flower`, else `ip_proto`/`dst_ip` = "Illegal".
- NET_SCHED is the parent Kconfig gate for all NET_CLS_*/NET_SCH_* — must be =y or they silently drop.
- skip_sw makes the add fail (our cb returns -EOPNOTSUPP); without skip_sw it adds in SW + still calls
  our HW cb (which is what we want for Stage 1 logging). For Stage 2 we'll return 0 on success.

## Next (Stage 2): make it actually forward in HW
In cls_flower_add, instead of logging+EOPNOTSUPP, build a CLA ram1 rule-TCAM entry (match the 5-tuple
→ forward to the REDIRECT egress port) and write it with zx_cla_write_entry (zx-eth-main.c:2035 —
corrected). Verify: read it back (double-read/stock fpga, NOT single clapeek — word0 off-by-one) AND
under iperf the pipeline_stats/hw_trap CPU counters go FLAT for the flow while throughput rises.
PER THE REVIEW: treat "does a CLA forward rule actually override the per-inport CPU trap?" as the
explicit experiment — be ready to ALSO set the SPA pktdeal slot (0x921d4300) for the flow (that's how
the merged #36 TCP-ACK HW-forward worked). rhashtable(cookie→{ram_id,slot}) for del.
