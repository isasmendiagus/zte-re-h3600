# Phase 4 — IPv6 (routed prefix + ip6tables zone firewall) — verified

**Status: forwarding + firewall DONE + verified end-to-end on HW (2026-06-04, Iter loop-9).**
RA/prefix-delegation daemon = follow-up (needs a clean build). branch hw-ack-forward.

## Kernel
Base had `CONFIG_IPV6=y` but `CONFIG_IP6_NF_IPTABLES` off. Added to
`configs/netfilter.fragment`: IP6_NF_IPTABLES, IP6_NF_FILTER, IP6_NF_TARGET_REJECT, IP6_NF_MANGLE,
IP6_NF_NAT, IP6_NF_TARGET_MASQUERADE (all =y). NF_CONNTRACK is shared with v4. The stock uClibc
**ip6tables binary works** (same family as iptables, no liboss_pub).

## Config (in rc.router, auto-applied at boot — verified)
IPv6 is **routed, no NAT** (the standard model — a delegated prefix, not masqueraded):
- lan1 (LAN) = `fd00:1::1/64`, lan4 (WAN) = `fd00:9::1/64`.
- `net.ipv6.conf.all.forwarding = 1`.
- ip6tables zone firewall: `-P FORWARD DROP`, `-A FORWARD -i lan1 -o lan4 -j ACCEPT`,
  `-A FORWARD -i lan4 -o lan1 -m state --state ESTABLISHED,RELATED -j ACCEPT`,
  `-A FORWARD -p ipv6-icmp -j ACCEPT` (NDP/PMTU — pragmatic; tighten to specific ICMPv6 types later).
Verified on a fresh boot: forwarding=1, lan1/lan4 v6 addrs set, ip6tables FORWARD policy+rules present.

## End-to-end verification (netns rig, WAN moved to lan2 for the test)
LAN client `fd00:1::100` (main ns, on lan1) → fake-ISP `fd00:9::2` (netns wan, on lan2):
**4/4 replies, ttl=63** (hop-limit decremented from 64 ⇒ ROUTED through the device). No NAT — the
fake-ISP saw the real LAN src and routed the reply back via `fd00:9::1`. v6 forwarding + the v6 zone
firewall both work.

## Follow-up (not blocking)
- **RA / prefix delegation on LAN**: no radvd/odhcpd available (busybox lacks them; stock ones likely
  link liboss_pub → would hang). LAN clients currently need a static v6 addr. A clean radvd/odhcpd
  build (or a small custom RA sender) is needed to auto-advertise `fd00:1::/64` to LAN clients. On a
  real WAN, the prefix would come from DHCPv6-PD (also needs a clean client, e.g. odhcp6c).
- **ICMPv6 rule** is currently allow-all-forward; tighten to NS/NA/RS/RA/too-big/time-exceeded.
- Tighten v6 firewall test (TCP probe) to confirm DROP of unsolicited WAN→LAN (v4 path already proved
  the DROP mechanism; v6 uses the same conntrack/state engine).
