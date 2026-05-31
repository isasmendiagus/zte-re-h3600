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

## Status / progress log (branch `eth-dsa`)
- **2026-05-30 iter1 (commit cec0d44d9):** P0 skeleton — tag_zte tagger +
  DSA_TAG_PROTO_ZTE enum + include/linux/dsa/zte.h + zx-dsa.c (dsa_switch_ops:
  get_tag_protocol→ZTE, stub setup/port_enable/phylink_get_caps) + Kconfig/Makefile.
  Both tag_zte.o and zx-dsa.o COMPILE. NOT wired to probe; HW ops are stubs.
- **NEXT (P0 cont.):** DT node `zte,zx279128-switch` + conduit (`sw` netdev)
  relationship (ports{ lan0..3 + cpu `ethernet=<&sw>` }) so dsa_register_switch
  probes and the 4 `lanN` netdevs appear. Then P1: conduit TX reads the 4-byte
  internal tag → desc[2:3] egress port + copies frame[4:] to BP; conduit RX
  prepends {0x5a, desc[6] ingress port} before netif_receive_skb.
- **2026-05-30 iter2 (commit df7b5b401):** P3 partial — port_enable/disable
  (greg port_closed @npp+0x4c) + port_stp_state_set (greg STP @npp+0x44 + stp_en
  @npp+0x40, BR_STATE_*→chip map) with real register writes; probe ioremaps the
  NPP greg window (non-exclusive, shared w/ conduit for now). Compiles; NOT
  HW-verified. zx_phys_port() = identity stub (CPU/remap TODO).
- **NEXT options:** continue P3 (port_bridge_join/leave via isolation
  sbragRegTable[0x39]@0x923883c0+port*4; port_fdb_add/del — FIX +0x800 addr bug,
  port real sbrg_hash; port_vlan_add mem_id=4) — all compile-checkable + later
  memdump-verifiable; OR the DT node + conduit relationship so it probes (P0 cont).
- **2026-05-30 iter3 (commit 0d1a14bac):** P3 partial — SBRAG FDB add/del +
  indirect plumbing (PP window 0x92388000, CORRECT offsets 0x14/18/1c/20/24 —
  fixed the +0x800 bug). Entry layout per stock; status=0xF. Compiles; HASH is a
  PLACEHOLDER (real sbrg_hash being RE'd by a parallel agent) → entries mis-slot
  until ported. Launched agent afcf41fea (sbrg_hash RE).
- **NEXT:** drop in the real sbrg_hash when the agent returns; then port_vlan_add
  (SBRAG mem_id=4, 2b/port) + port_bridge_join/leave (isolation @pp+0x3c0+port*4).
  Then the bigger integration: DT node + conduit relationship so it PROBES
  (P0 cont/P1) — needed before any HW (memdump) verification.
- **2026-05-30 iter4 (commit c2d85d9b1):** P3 partial — VLAN add/del (SBRAG
  mem_id=4 RMW of 2-bit/port membership in D0) + zx_sbrag_read_entry (rw=1
  prefetch); generalized write_entry to take mem_id. Compiles; VLAN attr encoding
  is best-effort placeholder (TODO). sbrg_hash agent (afcf41fea) still pending.
- **NEXT:** port_bridge_join/leave via isolation (sbragRegTable[0x39]
  @pp+0x3c0+port*4, allow-bitmap, stored complemented; needs per-bridge member
  tracking in priv) + port_fast_age. Integrate the real sbrg_hash when the agent
  returns. Then the big one: DT node + conduit relationship so it PROBES (P0
  cont/P1) — the gate to any HW (memdump) verification.
- **2026-05-30 iter5/6 (commits b314b5477, 987b11d25):** real sbrg_hash
  (CRC-16/CCITT via crc_itu_t, reads mode+width live) + DT binding doc. **FULL
  IMAGE BUILD exit 0; tag_zte.ko (5.5K) + zx-dsa.ko (10K) both build** — all
  P0+P3 pieces integrate end-to-end (modpost OK), not just isolated .o.
- **State of P3 (all COMPILE, NONE HW-verified — driver doesn't probe yet):**
  port_enable/disable, STP, FDB add/del (real hash), VLAN add/del. Remaining P3:
  bridge_join/leave (isolation — fiddly port remap + complement, risky blind),
  port_fast_age (needs FDB-flush RE).
- **THE GATE for any HW verification = the DT/conduit integration (P0 cont/P1):
  make `sw` a DSA conduit + the zx-dsa platform device probe.** This is invasive
  (touches the working zx-eth driver) and best done with the user / HW in the
  loop, not blind overnight. The autonomous loop has built+validated all the
  compile-checkable, spec-backed pieces; the next steps need HW verification or a
  design decision on the conduit refactor.
- **2026-05-30 iter7/8 (commits 3306c0562, 36d2e5ab3):** bridge_join/leave
  (isolation, RE'd remap+permute) + port_fast_age (SW FDB flush). **P3 COMPLETE
  — all per-port dsa_switch_ops implemented + compile + build into zx-dsa.ko.**
- **AUTONOMOUS-SAFE COMPILE WORK IS NOW EXHAUSTED.** Everything spec-backed +
  compile-verifiable is done (P0 skeleton, tagger, all P3 ops, real hash, DT
  binding, full-build validated). NONE is HW-verified because the driver doesn't
  probe yet.
- **THE remaining step = conduit refactor (P1): make zx-eth `sw` a DSA conduit +
  zx-dsa platform device probe. INVASIVE (touches the working egress driver),
  needs HW verification + a user design decision — NOT to be done blind
  overnight.** Loop should now do only safe upstream-prep (checkpatch, MAINTAINERS,
  commit hygiene) and flag the user for the conduit refactor.
- **checkpatch (2026-05-30):** tag_zte.c = 1 warn (filename-in-header). zx-dsa.c
  = 8 errors (switch-case one-liners `case X: stmt; break;` → split lines) + 18
  warns (block comments need trailing */ on own line). NEXT safe iteration =
  checkpatch cleanup across both files (upstream-prep, non-invasive). Then
  MAINTAINERS entry. After that, only the conduit refactor remains (needs user).
- **2026-05-30 LOOP WIND-DOWN (14 commits on eth-dsa):** all safe compile-verifiable
  autonomous work DONE — P0+P3 (review-fixed FDB byte-order bug), real hash,
  isolation, DT binding, MAINTAINERS, checkpatch 0/0 (3 files), full-build validated,
  conduit-refactor guide (dsa_conduit_refactor_guide.md). The ONLY remaining step is
  the P1 conduit refactor (invasive + needs HW + user decision) — see the guide.
  Loop slowed to a heartbeat; remaining safe prep ticks: a HW-verify test script for
  the per-port ops (memdump-readback), upstream patch-series prep.
- **2026-05-31 P1 (safe portion DONE, 20 commits):** conduit datapath TX strip
  (0b664459b) + RX prepend & tagger mac_header fix (aa3917378) + conduit of_node
  + DT switch node draft (f2981f269, DTB compiles, status="disabled"). All gated/
  draft → main's egress unaffected, everything compiles + checkpatch-clean.
- **TO TEST ON HW (bench session — needs you + the device; not blind overnight):**
  1. `&switch_dsa { status = "okay"; };` in zx279128s-h3600.dts.
  2. Make the DSA driver + tagger LOAD at boot: set CONFIG_NET_DSA=y,
     NET_DSA_ZTE_ZX279128=y, NET_DSA_TAG_ZTE=y (built-in) — else add the .ko's to
     the initramfs (build_slotA only bundles zx279128-eth.ko today).
  3. build_slotA.py → boot → `dmesg`: expect zx-dsa probe + dsa_register_switch +
     lan0..3 netdevs. Watch for EPROBE_DEFER (conduit ordering) or DSA rejecting
     the conduit (it expects a fairly normal NIC; `sw` is switch-ish — possible
     friction; debug here).
  4. `ip addr add 192.168.1.99/24 dev lan2; ip link set lan2 up; ping` from host →
     expect 0% loss (same directed path, now via the tag). Then dsa_verify.py.
  RISK: a DSA-enabled boot could disrupt the `sw` conduit; recover by rebuilding a
  non-DSA image. This is why it's a HW-attended step.
- Reuse switch HW-init + register helpers from zx-eth-main.c.
