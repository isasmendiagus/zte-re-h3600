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
