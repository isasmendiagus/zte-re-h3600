# P2 design — move per-port MAC bring-up into zx-dsa phylink ops

**Date:** 2026-05-31 · Branch: eth-dsa · Status: DESIGN (no code yet — see "Why not blind" below)

## Goal
Restore `phy-handle` on the DSA user ports so DSA/phylink owns the four GePHYs
per-port (the upstream-correct shape), driving each port's MAC bring-up from
`zx-dsa`'s `phylink_mac_*` ops — replacing the current TRANSITIONAL `fixed-link`
hack where the conduit (zx-eth) still owns the PHYs and brings up the MACs via
its `adjust_link`.

## Why this is needed
The transitional state (commit a4508c981) works for RX (HW-verified) but:
- DSA never sees real per-port link state (fixed-link = always up).
- We cannot restore `phy-handle`: with it, DSA's per-port phylink `phy_connect`s
  the same GePHYs the conduit already `phy_attach_direct`s → `-EBUSY` → dangling
  PHY state machine → NULL-deref panic (boot #1, 2026-05-31).
- No multi-port story (other jacks) and no link-driven MAC reconfig.

## The coupling problem
All per-port MAC bring-up lives in the CONDUIT driver and keys off `e->base`
(the PON window 0x92000000), which `zx-dsa` does NOT map (it maps only NPP+PP):
- `zx_smac_init_port(e, port)` — zx-eth-main.c:1207 (ctrl=0xbbe003 → 0xbae003,
  mask/enable, +0xe0 serializer bond).
- `config_speed_duplex` — inline in `zx_eth_adjust_link` (~:4197-4219): clears
  bit15 / sets bit13 for 1G, etc. (the proven egress value 0xBA6003).
- per-port `pon_reset` pulse — `zx_eth_adjust_link` :4180-4187 (`e->pon_early`).
- TM link reg — `zx_eth_adjust_link` :4239 (`TM_OFF+0xc000` = 0x03f40050 up).

This is also the **egress-critical** path (the CPU→LAN fix). Refactoring it
carelessly risks the committed egress behavior.

## Options
- **A — zx-dsa maps the PON window + reimplements smac_init/config_speed_duplex.**
  ✗ Duplicates intricate egress-critical code; two drivers writing the same MAC
  regs; the pon_reset pulse + TM link reg are tangled with conduit-private state
  (`e->pon_early`, `phy_was_link[]`). Rejected.
- **B — conduit exports a per-port MAC-link helper; zx-dsa calls it.** ✓ Single
  source of truth; the conduit keeps ownership of its register state. RECOMMENDED.
- **C — keep fixed-link transitional.** Works for RX (and likely TX, pending the
  host-ping proof); simplest; but no per-port link / no multi-port phylink. This
  is the current state and a valid fallback if B proves too invasive.

## Recommended path (B), incremental + HW-gated
1. **Extract** the per-port bring-up out of `zx_eth_adjust_link` into a
   behavior-preserving helper:
   `void zx_eth_port_mac_link(struct zx_eth *e, int port, int speed, int duplex, bool up)`
   containing the pon_reset pulse + `zx_smac_init_port` + config_speed_duplex +
   the TM link reg. `adjust_link` then just calls it per flipped port.
   ⚠ Touches the egress-critical path → **must HW re-verify egress** (CPU→LAN
   ping) after this step. User-attended; NOT a blind change.
2. **Export** a conduit-netdev-keyed wrapper:
   `int zx_eth_conduit_mac_link(struct net_device *conduit, int port, int speed, int duplex, bool up)`
   (EXPORT_SYMBOL_GPL), which resolves `struct zx_eth *e` from the sw netdev priv
   and calls the helper. Guard: only valid for the zx-eth "sw" conduit.
3. **zx-dsa**: implement `phylink_mac_link_up` / `phylink_mac_link_down`
   (and `phylink_mac_config` if needed) that resolve the conduit via
   `dsa_port_to_conduit(dp)` / `dsa_to_port(ds, port)->cpu_dp->conduit` and call
   the exported wrapper with (port, speed, duplex, up). Flesh out
   `phylink_get_caps` (already INTERNAL + MAC_1000FD).
4. **Restore phy-handle** on the DSA user ports (revert the fixed-link block in
   the dtsi). Now DSA/phylink owns the GePHYs per-port → it calls config_init
   (LDO + TX-DAC) on connect and our phylink_mac_link_up brings up the MAC.
5. **PHY-ownership handoff (the hard sub-problem):** the conduit currently
   `phy_init_hw` + `phy_attach_direct` + `phy_start`s all 4 GePHYs in
   `zx_eth_attach_phys`. With DSA owning them, the conduit must STOP doing that —
   otherwise the boot-#1 `-EBUSY` panic returns. But at conduit probe time DSA
   hasn't bound yet (`netdev_uses_dsa(sw)` is false), so the conduit cannot key
   off that. Resolution candidates (USER DECISION):
   (a) a DT property on the eth node (set only when the switch is enabled) that
       tells the conduit "the switch owns the LAN PHYs — don't attach them";
   (b) delete `zte,gephys` from the eth node in the DSA board file
       (`/delete-property/`) so the conduit finds no PHYs to attach;
   (c) detect at runtime that an enabled DSA switch references the conduit and
       skip the attach.
   (b) is simplest and explicit; (a) is most readable. Either way the CPU/conduit
   link uses the existing `port@5` fixed-link.
6. **HW verify:** boot, confirm per-port link via DSA (lanN carrier follows the
   PHY), lan2 RX+TX, then multi-port — **needs cable moves = user-attended.**

## Why not write it blind tonight
- Step 1 refactors the **egress-critical** `adjust_link`; the rule is "never break
  the committed egress fix", and egress can only be re-verified with a host ping
  (the REPL has no ping; the build box isn't cabled).
- Step 5 is a genuine **architecture decision** (PHY-ownership handoff) that the
  user should choose.
- Final validation (per-port link, multi-port) **needs cable moves** — not
  night-testable.

So P2 is teed up here for a HW-attended bench session. The transitional
fixed-link state (option C) remains in place and keeps RX working meanwhile.
