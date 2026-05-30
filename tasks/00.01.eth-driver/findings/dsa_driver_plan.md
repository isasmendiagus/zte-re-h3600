# ZX279128S switch → mainline Linux DSA driver — implementation plan

**Date:** 2026-05-30 · Goal: upstreamable DSA driver for the on-chip 4-port switch.
Foundation RE complete (tag protocol, FDB ops, per-port ops) — see memory
`zte-dsa-foundation` and DATASHEET.md. CPU→LAN egress + RX both proven working
(commit 1c7af7d6c). This doc = the architecture + phased build plan.

## THE key design decision: out-of-band (descriptor) port tag

Standard DSA taggers (tag_trailer/tag_dsa/tag_brcm…) put the source/dest port in
**bytes added to the frame** (header or trailer), and the conduit is a generic
NIC that carries those bytes transparently. **Our hardware does NOT work that
way:** the port is in the **DMA descriptor** the CPU exchanges with the TM/QMG
fabric:
- TX egress port = desc word3 bits[9:4] = `((port+0x28)&0x3f)<<4`
- RX ingress port = desc[6] bits[7:3] = `port+1`
The ethernet frame itself is **untagged**. This is an *out-of-band* tag.

### Implication / chosen approach
The conduit and switch are the **same SoC**, and the existing `zx-eth-main.c`
already owns the CPU-port DMA path (the `sw` netdev: `zx_sw_xmit`→TM ring,
`zx_tm_napi_poll`←TM ring). So:

- **Conduit (DSA master) = the `sw` netdev** (CPU-port DMA). It stays in
  `zx-eth-main.c`.
- The **tag is applied/parsed by the conduit's own TX/RX descriptor code**, not
  by adding frame bytes. The DSA tagger (`tag_zte`) becomes a *thin shim* that
  carries the port index between DSA and the conduit via skb metadata
  (`skb->cb` / a small struct), since tagger and conduit are the same driver.
  - `xmit`: DSA has already set the user port; tagger stashes `dp->index` where
    `zx_sw_xmit` reads it → stamps `desc[2:3]`. No frame bytes added
    (`needed_headroom/tailroom = 0`).
  - `rcv`: conduit reads `desc[6]` ingress port, stores it on the skb; tagger
    sets `skb->dev = dsa_conduit_find_user(dev, 0, ingress_port)`.
- **Switch driver (new, `dsa_switch_ops`)**: registers the switch, programs HW
  (FDB/STP/VLAN/isolation/port-enable) using the RE'd registers, ports = lan0..3,
  CPU port = the internal TM/QMG port.

This keeps the proven DMA path, adds DSA on top. Alternative considered &
rejected for now: tag_8021q (in-band VLAN) — would work but changes wire format
and is uglier than using our native descriptor tag.

RESOLVED (2026-05-30): use a 4-byte INTERNAL tag {mark=0x5a, port, 0, 0} prepended
by the tagger and STRIPPED by the conduit before DMA (never on the wire). This
survives qdisc (unlike skb->cb, which DSA core uses and qdisc may clobber). Shared
defs in include/linux/dsa/zte.h (ZTE_TAG_LEN=4, ZTE_TAG_MARK=0x5a). tag_zte.c
written + COMPILES (CC [M] net/dsa/tag_zte.o ok). The conduit (zx_sw_xmit / napi)
must: TX read tag[1]→desc egress port, copy frame[4:] to BP (drop tag); RX prepend
{mark,port from desc[6]} before netif_receive_skb. (= P1 conduit work.)

## File structure
- `net/dsa/tag_zte.c` — the thin tagger (proto DSA_TAG_PROTO_ZTE). Kconfig
  `NET_DSA_TAG_ZTE`, Makefile entry, enum in `include/net/dsa.h`.
- `drivers/net/dsa/zte/zx-dsa.c` (new) — `dsa_switch_ops` driver. Registers
  dsa_switch, implements the ops (below). Calls the HW-init/register helpers.
- `drivers/net/ethernet/zte/zx-eth-main.c` — refactor: `sw` netdev becomes the
  conduit; split the switch-HW programming into helpers the DSA driver calls
  (or expose via a small in-kernel API / shared module). PHY driver
  `phy-zte-gephy.c` unchanged (upstream it standalone — it's ready).
- DT bindings: `Documentation/devicetree/bindings/net/dsa/zte,zx279128.yaml`;
  DT node with `dsa,member`, ports{ lan0..3 + cpu port `ethernet=<&sw>` }.

## dsa_switch_ops → RE'd register map (from zte-dsa-foundation)
| DSA op | HW mechanism |
|---|---|
| `get_tag_protocol` | return DSA_TAG_PROTO_ZTE |
| `setup` | the existing zx-eth switch init (CLA/PM/PP/TM/SCH/QMG); enable CPU port |
| `port_enable/disable` | gregRegTable port_closed @0x921c004c (1b/port, 1=closed) |
| `phylink_*` / `adjust_link` | per-port smac_init + config_speed_duplex + 0x19068 bridge + TX-DAC; fixes the runtime-link gap (phylink polls all 4 PHYs) |
| `port_stp_state_set` | greg STP @0x921c0044 (3b/port: 0..4), stp_en @0x921c0040 |
| `port_bridge_join/leave` | isolation sbragRegTable[0x39] @0x923883c0+port*4 |
| `port_fdb_add/del` | SBRAG indirect (CMD 0x92388014…); FIX the +0x800 addr bug; port real sbrg_hash |
| `port_vlan_add/del` | SBRAG mem_id=4 @0x92388014, 2b/port attr |
| `port_fast_age` | FDB aging / flush |

## Phased build (each phase compiles + is bench-testable)
- **P0 — skeleton:** tag_zte (shim) + zx-dsa.c registering a dsa_switch with the
  conduit, 4 user ports, CPU port; `get_tag_protocol`, stub `setup`. Goal: probes,
  4 `lanN` netdevs appear.
- **P1 — datapath:** wire the conduit TX/RX to stamp/parse the descriptor port via
  the tagger shim; per-port netdev up/down. Goal: a frame out `lan2` egresses MAC2;
  RX on a port delivers to its `lanN`. (Solves the ingress→CPU per-port gap — DSA
  delivers per ingress port.)
- **P2 — link:** phylink per port across all 4 GePHYs (fixes runtime hot-plug
  link detection — the gap found 2026-05-30). Goal: cable on ANY jack works, hot-plug.
- **P3 — switching:** port_enable, STP, bridge_join (isolation), FDB add/del
  (fix +0x800, real hash), VLAN. Goal: Linux bridge over lan0..3, HW offload.
- **P4 — upstream prep:** DT bindings + docs, split modules cleanly, submit PHY
  driver to netdev first, then the switch.

## Known gaps this resolves (from the multi-port live test 2026-05-30)
1. ingress→CPU only worked on the boot port → DSA delivers per-ingress-port (P1).
2. runtime link-change detection didn't fire on other PHYs → phylink polls all (P2).
3. egress hardcoded to one port → per-frame DSA tag = the dest port (P1).

## Status
P0 starting. Branch `eth-dsa`. Conduit/HW-init reuse from zx-eth-main.c.
