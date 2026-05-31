# Multi-port DSA — root cause: MAC init only happens at boot (not on hotplug)

**Status: RESOLVED (mechanism) — multi-port DSA works when the cable is on the jack AT BOOT.**
Date: 2026-05-31. Branch: eth-dsa.

## Symptom
With the DSA driver, only the port that had a cable at the original boot (port2 / jack3, where
the dup-fix `ping 20/20` was verified) forwarded traffic to the CPU. Moving the cable to any other
jack (jack2/port1, jack1/port0) gave 100% packet loss, `tm_rx_count=0`, `tm_irq_count=0`.

## The red herring (what it was NOT)
A long register-level investigation (stock-vs-mainline diff of SOPC `0x19068`, greg STP, SPA
pktdeal, PP isolation, QMG cfg, SIPC, broadcast flood; FDB seeding; CLA replay) found EVERY
per-port register/table matched stock, and no poke moved `tm_rx_count`. Notably port1 and port2
had **byte-identical** SPA pktdeal yet behaved differently. Conclusion at the time ("only port2
works / non-register classify gate / register approach exhausted") was **WRONG** — it was chasing
a switch-classification bug that does not exist. `zx_eg_port=2` is also NOT the blocker: DSA TX
uses the per-packet tag (`eg = skb->data[1]`); the `=2` default only applies to non-DSA frames.

## Real root cause
A port's MAC is initialized (`zx_smac_init_port`) **only if the port has PHY link AT BOOT**
(during probe / the boot-time adjust_link). When the cable is moved to a different port *after*
boot, the GePHY link-change path does **not** run `smac_init` for the newly-linked MAC.

Proof: after hotplugging the cable to jack1/port0, `MAC0 ctrl=0 / en=0` despite `PHY[0] link=1`.
An uninitialized MAC forwards in **neither** direction → ingress `tm_rx_count=0` AND egress
`MAC TX=0` (txtest with `eg_port=0` injected 20 frames, `MAC0 TXok` stayed 0).

Every earlier "non-port2 fails" measurement was taken on a **hotplugged** cable (MAC never inited)
or after register pokes — never a clean boot with the cable already on that jack.

## Proof it works
Rebooted with the cable physically on **jack1 (port0) at boot** → MAC0 inits during probe →
- host→device ping: 14/15 (~12ms RTT)
- device→host ping: 4/4, 0% loss
- `tm_rx_count`, `tm_irq_count`, `tm_tx_count` all climb; `lan0` carries traffic.
Same behavior as port2/jack3. So **multi-port DSA fundamentally works** — boot with the cable on
the desired jack.

## Connection to the GePHY IRQ panic
The post-boot link-change path is the same one that previously paniced in
`zte_gephy_handle_interrupt -> mdiobus_read` (NULL deref). So the hotplug MAC-reinit and the
GePHY link-change IRQ are the same broken handler — fixing it enables both.

## What's left (the actual remaining work)
1. **Hotplug MAC re-init (the fix):** when a GePHY link comes UP post-boot, run
   `zx_smac_init_port(port)` for that MAC (+ the per-link bring-up adjust_link already does for
   the boot port). Requires the GePHY link-change handler / IRQ to fire reliably (fix the
   `zte_gephy_handle_interrupt` NULL-deref path or fall back to phylib polling). Then moving the
   cable between jacks works without a reboot.
2. **Confirm all 4 ports** boot-with-cable (port0 ✓, port2 ✓; re-test port1/jack2 and port3/jack4
   with a clean boot — expected to work by the same mechanism).
3. **Minor 1/15 host→device loss** on port0 — investigate (could be RTT/load or a real drop).
4. After that, multi-port DSA is functional → resume P2 (phylink/per-port MAC bring-up),
   P3 switch ops (FDB/STP/VLAN/bridge — now testable with the soft-float `ip`/`bridge`).

## ★ PHY_POLL fix VERIFIED + port1 is a real anomaly (2026-05-31)
Implemented `phydev->irq = PHY_POLL` (drop phy_request_interrupt). HW-verified:
- GePHY irqs no longer registered → PHY[3] storm GONE (~30M → none).
- Hotplug WORKS without reboot: moved cable jack2→jack1 live; phylib polling fired
  `PHY[1] link DOWN` then `PHY[0] link UP @1000/FD → MAC[0].ctrl=0xba6003`; adjust_link
  re-ran smac_init(0); **host ping port0 = 6/6 0% loss, tm_rx_count climbs — no reboot.**
So PHY_POLL is the correct fix for link detection + hotplug (matches stock's extphy_timer polling).

BUT this also DISPROVES "MAC-init-at-boot was the whole story": on the same PHY_POLL boot,
**port1/jack2 FAILS** (host ARP for .99 → FAILED, tm_rx_count=0) even though MAC1 IS inited
(adjust_link logged "PHY[1] link UP → MAC[1].ctrl=0xba6003", readback ctrl=0xbb6003 en=0x80000001).
Meanwhile port0/jack1 and port2/jack3 both WORK with MAC inited. Pattern: port0 ✓, port1 ✗,
port2 ✓ — port1 is the odd one out, with a genuine port1-specific ingress→CPU fabric gap that
port0/port2 don't have. (Its SPA pktdeal is identical to port2's, which works — so not that.)
NEXT to characterize port1: test port3/jack4 (does the pattern hold?) and/or swap the cable/RJ45
on jack2 to rule out a bench hardware issue, before assuming a port1 silicon/config quirk.

## ★★ FULL PATTERN 2026-05-31: port0 ✓ port1 ✗ port2 ✓ port3 ✓ — only jack2/port1 fails
Moved the (same) cable jack1→jack4 live (hotplug, no reboot): polling fired
`PHY[3] link UP @1000/FD → MAC[3].ctrl=0xba6003`; **host ping port3 = 6/6 0% loss** (tm_rx=35).
So 3 of 4 ports (port0/jack1, port2/jack3, port3/jack4) ping bidirectional; ONLY port1/jack2 fails.
The SAME cable works in jacks 1/3/4 but not jack2 → strongly points to jack2/port1 being an
ISOLATED issue (bench RJ45/connector/magnetics, or a port1 silicon/MAC quirk), NOT a driver bug
(driver config is uniform; 3/4 ports work identically). Note PHY[1] DID negotiate link fine
(1Gbps/FD/an_done) when cabled — so the link/autoneg path works; the failure is downstream
(MAC1→fabric→CPU). To pin it: try jack2 with a DIFFERENT cable; if it still fails, it's jack2/port1
hardware or a port1-specific silicon quirk — but multi-port DSA is functional (3/4 ports + hotplug).
