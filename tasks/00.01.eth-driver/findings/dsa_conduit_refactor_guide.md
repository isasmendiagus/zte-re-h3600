# DSA conduit refactor (P1) — step-by-step implementation guide

**Status:** the ONLY remaining step to make the DSA driver probe + be HW-verifiable.
**Why it's not done autonomously:** invasive (touches the working egress driver
`zx-eth-main.c`, commit 1c7af7d6c on main), needs HW verification, and a design
decision. Do this with the device on the bench. Branch: `eth-dsa`.

Prereqs already DONE (all compile, checkpatch-clean, branch eth-dsa, 13 commits):
tag_zte tagger, zx-dsa dsa_switch_ops (all per-port ops), real sbrg_hash, DT
binding, MAINTAINERS. See dsa_driver_plan.md + memory zte-dsa-foundation.

## Architecture recap
- DSA conduit (master) = the existing `sw` netdev in zx-eth-main.c (the CPU<->fabric
  DMA path). It stays a normal netdev; DSA attaches to it.
- zx-dsa = a platform device that registers the dsa_switch (4 user ports lan0..3 +
  CPU port 5) and programs the fabric. It must be instantiated and reference the
  conduit.
- Tag = 4-byte INTERNAL tag {0x5a, port, 0, 0} the tagger adds/parses and the
  conduit strips before DMA / prepends on RX. Never on the wire.

## Step 1 — make zx-dsa probe (instantiate + bind to conduit)
DSA needs the switch's CPU port to reference the conduit via DT:
`port@5 { reg = <5>; ethernet = <&sw>; phy-mode="internal"; fixed-link{speed=<1000> full-duplex;}; }`
Options to get zx-dsa instantiated:
  (a) Add a `switch { compatible="zte,zx279128-switch"; reg=<0x921c0000 0x1000>; ports{...} }`
      node to the H3600 DTS (the dtb appended by build_slotA.py — find the board dts
      under arch/arm/boot/dts/ or the one the build concatenates). zx-dsa's
      of_match binds. This is the clean path.
  (b) Or have zx-eth-main.c probe register a platform_device for zx-dsa (software
      device) once `sw` exists — uglier, avoids DTS edits.
Recommend (a). The conduit `sw` netdev must have a DT node (or be findable by DSA);
since `sw` is created by the platform driver, give the eth node a label `sw:` and
reference it from port@5's `ethernet`.
GOTCHA: DSA probe ordering — the conduit netdev must exist before dsa_register_switch
resolves `ethernet=<&sw>`. DSA defers (EPROBE_DEFER) until the conduit appears, so
order usually resolves itself; verify with `dmesg`.

## Step 2 — conduit TX: consume + strip the internal tag (zx_sw_xmit)
In zx_sw_xmit (zx-eth-main.c ~L3295), when DSA is active the skb arrives with the
4-byte tag prepended by tag_zte (skb->data[0]=0x5a, [1]=egress port). Change:
```c
#include <linux/dsa/zte.h>
u8 eg = zx_eg_port;                         /* fallback (non-DSA) */
const u8 *frame = skb->data; u32 flen = len;
if (len >= ZTE_TAG_LEN && skb->data[0] == ZTE_TAG_MARK) {
    eg = skb->data[1];                      /* DSA egress port */
    frame = skb->data + ZTE_TAG_LEN;        /* skip the internal tag */
    flen = len - ZTE_TAG_LEN;
}
/* desc[2:3] = ((eg + 0x28) & 0x3f) << 4;  copy `frame`/`flen` into BP+16; len=flen */
```
i.e. derive the egress port from the tag (not the global zx_eg_port), and memcpy
`frame` (tag-stripped) of length `flen` into the BP buffer. Update the desc length
field to flen. Keep the non-DSA path (no marker) working for the standalone netdev.
GOTCHA: padding — the <0x40 min-length pad must use flen, after stripping.

## Step 3 — conduit RX: prepend the ingress tag (zx_tm_napi_poll)
In the RX delivery path (zx_tm_napi_poll ~L2790, where it currently does
netif_receive_skb on e->sw_dev with the computed `ingress_port`
= ((desc[6]>>3)&0x1f)-1): when DSA is active, prepend the 4-byte tag so tag_zte's
rcv can demux to the right lanN:
```c
u8 *t = skb_push(skb, ZTE_TAG_LEN);
t[0] = ZTE_TAG_MARK; t[1] = ingress_port & 0xff; t[2] = 0; t[3] = 0;
/* then netif_receive_skb(skb) — DSA's rx_handler on the conduit intercepts */
```
Ensure skb headroom >= ZTE_TAG_LEN (netdev_alloc_skb already reserves 32; OK).
The existing loopback-drop + per-ingress counters can stay for debug.

## Step 4 — "DSA active" gating
Decide how the conduit knows DSA is attached (to choose tag vs plain path). Cleanest:
check `netdev_uses_dsa(e->sw_dev)` (returns true once a DSA switch is bound to the
conduit). Use it to gate steps 2/3. When false, keep the current standalone behavior
(so the driver still works pre-DSA / if DSA is disabled).

## Step 5 — register-access sharing
zx-dsa currently devm_ioremaps its own NPP (0x921c0000) + PP (0x92388000) windows
(non-exclusive). That works but double-maps. Optional cleanup: have zx-dsa get the
base from the conduit (a small exported accessor) or from DT reg. Not blocking.

## Step 6 — test plan (bench, cable on jack 3 = MAC2 = port 2)
1. Build + boot. `dmesg`: zx-dsa probe, dsa_register_switch OK, 4 `lanN` netdevs appear.
2. `ip link` shows lan0..3 + the conduit. `ip addr add 192.168.1.99/24 dev lan2; ip link set lan2 up`.
3. ping host<->device on lan2 (the cabled MAC2). Expect 0% loss (mirrors the proven
   directed-egress path, now via the DSA tag). Verify with the egress counters +
   host tcpdump.
4. Verify RX demux: a frame arriving on MAC2 should be delivered on lan2 (check the
   tag prepend + tag_zte rcv path; ingress_port=2 → lan2).
5. memdump-verify the P3 ops: bridge two ports (needs 2nd cable — defer), add a
   static FDB entry (`bridge fdb add`) → read back the SBRAG slot via memdump;
   STP state change → read greg 0x921c0044; VLAN add → read SBRAG mem_id=4 row.
6. Move cable to other jacks (multi-port) — needs physical access.

## Risks / watch-items
- The tag stripping/prepend changes the proven egress path → re-verify ping 0% loss
  FIRST before trusting the rest.
- Probe ordering / EPROBE_DEFER between conduit and switch.
- The CPU-port index in DSA (port 5) vs the chip — getPort remap (zx_phys_port is
  identity for user ports; CPU-port ops are guarded off). Confirm the CPU port
  forwards (the egress already proved CPU->MAC2 works).
- Keep `main`'s standalone driver working (gate via netdev_uses_dsa).
- If anything wedges the device: reboot via tftp_boot_mainline.py (RAM boot).

## After P1 works
P2 (phylink for all 4 PHYs / hot-plug — fixes the runtime link-detection gap),
then P4 (upstream: PHY driver first to netdev@, then the switch). The per-port ops
(P3) are written + need memdump/HW verification once probing.
