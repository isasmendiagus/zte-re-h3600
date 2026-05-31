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

## CORRECTION 2026-05-31: port1 is NOT hardware — it's internal (user was right)
Live proof: during a host ping to port1/jack2, MAC1 RX-ok climbed 0x14->0x1d (+9) — frames DO
physically reach MAC1 (cable/RJ45/PHY1/magnetics all fine; link LED lights, PHY[1] 1Gbps/FD/an_done).
But tm_rx_count stayed 0 → frames reach MAC1 and are NOT forwarded MAC1->fabric->CPU. So the failure
is INTERNAL, not a bench hardware/cable issue. Retract the "likely bench HW" theory.
BUT every readable per-port CONFIG register is IDENTICAL between port1 (fails) and the working ports:
SPA pktdeal port1 == port3 BYTE-FOR-BYTE (55555555 05555545 10544414 55555555 00000000) yet port3
pings and port1 doesn't; isolation/MAC ctrl+en/SOPC(0x19068=0)/STP all match the working pattern.
So the discriminating "bit" is NOT in any per-port config register we can read. It must be in
INDIRECT RAM (CLA classify trap entries, per (ptype,port)) or dynamic/learned state — needs an
in-kernel CLA/FDB dump hook to compare port1 vs port3 trap entries (the wire-level indirect read is
impractical). Status: multi-port DSA FUNCTIONAL on 3/4 ports (0,2,3) + hotplug; port1 isolated.

## cladump 2026-05-31: CLA trap-queue (ram7) is ALSO identical port1 vs working ports
Added debugfs cladump (per-(ptype,port) ram7 qid via indirect CLA read) + clapeek (ad-hoc read).
Result: for every ptype, columns p0=p1=p2=p3=p4=p6 are IDENTICAL (only p7, an internal port,
differs occasionally). So port1's CLA trap-queue config == the working ports'. NOT the discriminator.
CUMULATIVE: port1 is byte-identical to working ports in EVERY readable per-port config — SPA pktdeal,
isolation, MAC ctrl/en, SOPC(0x19068), STP, AND CLA trap-queue ram7. The main CLA classify (ram1) is
a global TCAM (addr=rule index, not per-ingress-port), so it can't discriminate port1 from port3 by
config either. Conclusion: the port1 failure is NOT config — it's a DYNAMIC/internal state (the
SIPC->QMG output FIFO was seen saturated for port1: cc008=0xfff000 vs stock ~0x777 → frames enter
SIPC but don't drain to QMG; a backpressure/flow issue), or a port1 silicon quirk in the MAC->fabric
path. Isolated to port1; not a driver bug (config uniform, 3/4 ports work). Multi-port DSA functional
(3/4 ports + hotplug). Chasing port1 further needs flow-control/credit RE, low value given 3/4 work.

## ★ DEFINITIVE: NOT hardware — stock pings 5/5 over jack2 (2026-05-31)
User's test: cold-booted STOCK with the cable on jack2/port1 → host ping 192.168.1.1 = 5/5 0% loss.
So jack2/port1 hardware (RJ45/magnetics/PHY1/MAC1/PCB) is 100% FINE. The mainline failure is a
DRIVER issue, not hardware. Also re-dumped stock's broadcast-flood + PM rules (the only per-port
surface not yet compared): stock 8300=0 8304=0 8340=0x15555ff 8004=0x40200ff 81c0=0xff, PM in-port
rules {0,1,2,3,4,5}, PM ctrl 0x54=0xc0 out 0x1a0=0x8 — ALL match mainline.
SO: stock and mainline have byte-identical port1 config, AND mainline's port1 config == mainline's
working port3 config, yet stock-port1 works, mainline-port1 fails, mainline-port0/2/3 work. The
divergence is DYNAMIC not config: mainline's SIPC→QMG drain backs up ONLY for port1 (cc008=0xfff000
saturated, QMG hw_trap=0) while stock drains (QMG hw_trap climbs) and mainline's other ports drain.
=> port1 is a per-port DYNAMIC flow/credit issue (QMG/SIPC), not any config register — needs
QMG/flow-control credit RE or stock-vs-mainline dynamic-counter tracing. Multi-port DSA functional
on 3/4 ports + hotplug. This is the honest state: not HW, not config, dynamic, uncracked.

## RE agent SIPC-gauge hypothesis TESTED → DISPROVEN (2026-05-31)
RE agent hypothesized the zx_npp_twin_data.h snapshot replay (zx_npp_apply_pair @ zx-eth-main.c:864)
clobbers SIPC FIFO/credit gauges at 0x921cc008/18/1c/20/04 with frozen capture values, saturating
port1's drain. TESTED on HW:
- cc008 (0x921cc008) read 0x00000000 BEFORE any poke this boot (NOT 0xfff000) — yet port1 still fails.
  So the gauge value does not correlate with the failure.
- Poked 0x921cc008/18/1c/20/04=0 + re-asserted 0x921cc000=0x11 → port1 still 100% loss, tm_rx_count=0.
- Toggled SIPC rx_en (0x921cc000 0→0x11) to resync pointers → still 100% loss.
=> SIPC gauge/ctrl is NOT the port1 gate. Also note SIPC at 0xc000 is a SINGLE shared block (not
per-port-addressed), so it cannot by itself discriminate port1 from the working ports anyway.
STATUS: port1 still uncracked. Confirmed NOT: hardware (stock pings), static config (all identical
to port3+stock), CLA trap-queue, SIPC gauge/ctrl. It is a per-port DYNAMIC difference whose source
is still unidentified. Static decomp analysis isn't pinning it; the next viable approach is a LIVE
side-by-side: plug TWO cables (a working jack + jack2) so port0 and port1 are both up on one boot,
then compare their live pipeline counters (MAC RX, SIPC, QMG sw_fwd/hw_trap, RED) during ping to
see exactly where port1 diverges from port0 in real time. Or a stock kotrace of port1 ingress.

## ★★★ DEFINITIVE same-boot proof + live tool (2026-05-31)
Added rx_per_ingress histogram to the `stats` debugfs (slot[i]=ingress_port+1). With port1, port2,
port3 ALL cabled and up on ONE boot, after traffic:
  rx_per_ingress port0..7 = 0 0 9 12 0 0 0 0
  => port2=9, port3=12 reach the CPU; PORT1=0; port0=0 (no cable). All frames that arrive decode to
  port2/port3, NONE to port1 or "invalid". So port1's ingress→CPU delivers ZERO while port2/3 work,
  same boot, identical config. port1 is genuinely, reproducibly broken — not a test artifact/topology.
This gives a LIVE per-port discriminator tool: poke something for port1 and watch rx_per_ingress[port1]
(the "port1" column) — if it climbs, the fix worked. Next experiments can use this for fast feedback.

## Live hunt 2026-05-31: SILENT drop at MAC1→fabric (clean RX, no drop counter)
Using the rx_per_ingress live tool + SIPC/MAC counters (3 cables up, port1/2/3):
- SIPC drop counters 0x921cc004 = 0, cc008 = 0 → NO drop registered at the SIPC→CPU stage.
- MAC1 vs MAC2 RX counter block (0x780..0x79c): MAC1 RXok=88, MAC2 RXok=55, both with byte/frame
  counters consistent and ALL error counters (+0x794/+0x798/+0x79c) = 0 on BOTH → MAC1 receives
  CLEAN frames (no CRC/align errors), same as MAC2.
=> port1's drop is SILENT and BEFORE the SIPC: MAC1 receives 88 clean frames and forwards 0 to the
   fabric/CPU, while MAC2 receives 55 clean and forwards 9. No counter anywhere registers the drop.
Live experiments tried this session, all negative: SIPC gauge poke/toggle (cc008), SIPC drop
counter (0), MAC RX-error check (clean). The drop is a silent, config-invisible, per-port MAC1→fabric
forwarding failure — identical config to the working ports, not HW (stock works), no error counter.
This is beyond register inspection/poking. Remaining deep paths: decode the CLA ram1 TCAM for a
per-ingress-port rule missing for port1 (needs the TCAM key field spec), or kotrace stock's port1
ingress. Multi-port DSA functional on 3/4 ports + hotplug; port1 deeply characterized but uncracked.
