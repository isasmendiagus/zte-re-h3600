# Phase 1.3 — NAT router (ip_forward + MASQUERADE) — FULLY verified end-to-end

**Status: DONE + verified end-to-end on HW (2026-06-04, Iter loop-7).** branch hw-ack-forward.

The mainline device works as a **NAT router**: it routes + SNATs LAN→WAN traffic across two DSA
ports, with conntrack un-NAT'ing the return path. Verified through a *real* datapath (no rule-only
hand-waving) using a fake-ISP in a host network namespace — no physical WAN cable or internet needed.

## Topology used (both host NICs are on LAN jacks; WAN jack lan4 is empty)
Discovered the 2nd USB NIC `enx2c9975313ea9` is cabled to device **lan2** (found by per-port RX
counters while pinging). So lan2 was used as a stand-in WAN uplink:
- Device **lan1 = 172.31.9.1/24** (LAN), **lan2 = 192.168.9.1/24** (WAN uplink).
- Host `enxc8a362e95900` (device lan1) = LAN client, +172.31.9.100/24, route 192.168.9.0/24 via 172.31.9.1.
- Host `enx2c9975313ea9` (device lan2) moved into netns **wan** = fake ISP **192.168.9.2/24**
  (netns is essential — otherwise the host delivers 192.168.9.2 locally and never traverses the device).

## Device config
```
echo 1 > /proc/sys/net/ipv4/ip_forward
iptables -t nat -A POSTROUTING -o lan2 -j MASQUERADE
iptables -A FORWARD -i lan1 -o lan2 -j ACCEPT
iptables -A FORWARD -i lan2 -o lan1 -m state --state ESTABLISHED,RELATED -j ACCEPT
```

## Verification (all PASS)
- LAN client `ping 192.168.9.2` → **4/4 replies, ttl=63** (decremented from 64 ⇒ ROUTED, not bridged).
- WAN-side tcpdump (in netns wan): requests arrive as **`192.168.9.1 > 192.168.9.2`** — the client's
  src `172.31.9.100` was **MASQUERADE/SNAT'd to the device WAN IP 192.168.9.1**; replies
  `192.168.9.2 > 192.168.9.1` get un-NAT'd back to the client (conntrack).
- Rule counters: `MASQUERADE` 1 conn / `FORWARD lan1→lan2` 4 pkts / `FORWARD lan2→lan1 EST,REL` 4 pkts.

⟹ Routing across the DSA fabric + SNAT + conntrack reverse-translation all work. The device is a
functioning NAT router on mainline, using the same tooling stock uses (iptables/conntrack on the CPU).

## What's left for "real internet" (cable-dependent, not a code gap)
Plug a host NIC into the physical WAN jack (lan4) and have it act as the ISP (DHCP/static gw +
masquerade→wlo1). Then `iptables -t nat -A POSTROUTING -o lan4 -j MASQUERADE` (swap lan2→lan4) gives
true LAN→internet NAT. The mechanism is already proven; only the uplink is physical.

## Persistence
Config is currently applied live (not yet in an init script). A future iteration should add an
rc/init that, on boot: quiets printk, brings up lan1/lan4, starts udhcpd, sets ip_forward, installs
the nat/forward rules. (Stock does this from its rcS; mainline initramfs C-init REPL needs an
equivalent.) For now the bring-up sequence lives in STATE.md / this finding.
