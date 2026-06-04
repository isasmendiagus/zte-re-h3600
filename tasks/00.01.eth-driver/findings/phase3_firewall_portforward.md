# Phase 3 — zone firewall + DNAT port-forward (verified) + secure-by-default boot

**Status: DONE + verified end-to-end on HW (2026-06-04, Iter loop-8).** branch hw-ack-forward.

Builds on the Phase 1.3 NAT router. Adds the stock-style zone firewall (default-deny FORWARD) and
WAN→LAN port-forwarding (DNAT), and ships it as the secure default in the boot auto-config.

## Zone firewall (default-deny FORWARD)
```
iptables -P FORWARD DROP
iptables -A FORWARD -i lan1 -o lan4 -j ACCEPT                                   # LAN -> WAN
iptables -A FORWARD -i lan4 -o lan1 -m state --state ESTABLISHED,RELATED -j ACCEPT  # return only
```
Verified via the netns rig (lan2 stand-in WAN): LAN→WAN ping = 0% loss (allowed); the policy is DROP
so unsolicited WAN→LAN is denied unless an explicit rule opens it. This matches stock's WAN-in-drop.

## DNAT port-forward (WAN:port → LAN host)
```
iptables -t nat -A PREROUTING -i <wan> -p tcp --dport 8099 -j DNAT --to-destination 172.31.9.100:8099
iptables -A FORWARD -i <wan> -o lan1 -p tcp -d 172.31.9.100 --dport 8099 -j ACCEPT
```
Verified: from the fake-ISP (host netns 'wan', 192.168.9.2) `curl http://192.168.9.1:8099/` →
**HTTP 200** served by a listener on the LAN host (172.31.9.100:8099), i.e. the WAN-side request was
DNAT'd through the device to the LAN host. (An earlier test hit 8080 and got 401 from an unrelated
host service already bound there — itself proof the forward path reached the LAN host; re-ran on the
free port 8099 for an unambiguous 200.)

## Secure-by-default boot (persistence — Part A of this iter, commit 07c3cbb14)
The router now auto-configures at boot via **/etc/rc.router** (run by the C-init; init.c gained a
`[ -f /etc/rc.router ] && sh /etc/rc.router` hook). rc.router: quiet console, bring up lan1(LAN)+
lan4(WAN), ip_forward=1, **FORWARD policy DROP** + the LAN→WAN/established rules, MASQUERADE -o lan4,
and (after a link-settle sleep) busybox udhcpd -f on lan1. A port-forward template is included
(commented). Verified on a FRESH boot, zero manual config: ip_forward=1, FORWARD DROP + allows
present, MASQUERADE present, udhcpd started + serving (host DHCPOFFER). The device now boots straight
into a working, firewalled NAT router.

## Notes / next
- The persistent WAN is lan4 (the real WAN jack); the lan2 stand-in is only for cabled live tests.
- DNAT in rc.router is a commented template — uncomment + set host/port per deployment.
- Remaining roadmap: Phase 4 IPv6 (WAN DHCPv6-PD/SLAAC, RA on LAN), Phase 5 QoS (tc), Phase 6 HW
  flow offload (the perf piece). LAN DNS still optional (clients use upstream via DHCP opt 6).
- Live LAN→internet still needs a NIC on the physical WAN jack (lan4); mechanism already proven.
