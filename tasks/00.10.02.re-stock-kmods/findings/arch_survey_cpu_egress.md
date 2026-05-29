# Arch survey: existing drivers + CPU→egress-port pattern (2026-05-28)

Cross-SoC research to unblock the SOPC egress gate (CPU-injected TX, DA-FDB-resolved
to internal port 3 = LAN, passes QMG+DSCH but SOPC never picks egress port; SMAC TX
stays 0). Companion to `eth_pipeline_architecture_2026-05-28.md` and
`cpu_egress_routing_re.md` / `switch_egress_hypothesis_re.md`.

---

## Q1 — Is there ANY existing mainline/OSS driver for this SoC or relatives?

**VERDICT: No. Fully bespoke. There is no reusable driver code.**

- **OpenWrt**: The only public trace is the forum thread "Support for zx279128s"
  (forum.openwrt.org/t/196946). An OpenWrt maintainer states flatly: *"The SoC isn't
  supported in OpenWrt."* No target, no ethernet/switch driver, no source repo, no RE
  effort. The thread's device is a ZX279128**R** (Cortex-A9 dual-core) + MediaTek WiFi
  (MT7592N/MT7613BE) — WiFi is MTK (separately supported) but the **SoC switch/TM is
  unsupported**.
- **Mainline Linux**: nothing under any of `ZX279128`, `ZX279128S/R`, `ZXIC`. The only
  "zte" net code in-tree is unrelated (`drivers/net/ethernet/zte/zxic`? — no; the
  in-tree `zte` dir does not cover this PON SoC). Our `zx-eth-main.c` is the only driver.
- **OpenWrt ZTE GPON history** is all **other silicon**: F660/F460/F620/F420 v3 +
  HGG420N are **Marvell Avanta (88f6560)** (msdos03/openwrt-avanta, zx19930/openwrt-f660)
  — different chip, GPON port itself not working there either. F680 = ZX279128 family but
  also unsupported. None share the ZXIC switch/TM IP.
- **Is the QoS/switch IP a licensed/known design (Broadcom RDPA/Runner, or a PON SDK)?**
  No confirmation it is Broadcom Runner/RDPA. The RDPA-*flavored* naming in the stock
  rootfs (`rdpa_dm_init.sh`, 8 SP queues/port) is **superficial / cargo-culted**, not the
  real datapath: Broadcom Runner/RDPA is a firmware-driven packet-processor with its own
  thread/messaging model and register map; our traced datapath (BMU/CLA/QMG/DSCH/SOPC +
  GEM/tcont indirect-RAM shaper, `0x921c0000` window) does **not** match RDPA's runner
  architecture or register layout. It reads as **ZTE/ZXIC's own GPON MAC+switch+TM block**
  (an in-house "NPP" network processor), with the QoS layer's *terminology* borrowed from
  the common PON-SDK vocabulary. Conclusion: **no reusable IP-level reference**; the
  RDPA names are a red herring for register-level work. Keep RE-driving from decomp.

**Reusable reference value**: only conceptual. The closest *useful* references are (a)
our own U-Boot decomp (same silicon, proven egress via the direct mux), and (b) the
mainline DSA drivers below for the *general pattern* (Q2) — not for code reuse.

---

## Q2 — How do comparable integrated-switch SoCs route a CPU-INJECTED frame to a
chosen physical egress port?

Surveyed: mt7530, qca8k, b53/bcm_sf2 (+ brcm tag), rtl83xx-style. **All converge on
the SAME two-part mechanism.** A CPU-sourced frame egresses a chosen physical port
only when BOTH are satisfied:

### Mechanism A — source/CPU-port "allowed-egress-port" matrix (fabric config)
A per-source-port bitmask of which ports a frame ingressing there may egress to. The
CPU/IMP port's mask **must include the target LAN port**, else the fabric drops/black-
holes the frame even after the forwarding decision. This is the classic switch port-
isolation / port-VLAN matrix.

| Driver | Register / field | What it does |
|---|---|---|
| **mt7530** | `MT7530_PCR_P(cpu) = PCR_MATRIX(dsa_user_ports)` (mt7530.c:1053) | CPU port's PORT_MATRIX = all user ports; `PCR_MATRIX(x)= (x&0xff)<<16` in PCR @ `0x2004+port*0x100`. User ports get `PCR_MATRIX(BIT(cpu))`. |
| **qca8k** | `QCA8K_PORT_LOOKUP_CTRL(cpu) .MEMBER = dsa_user_ports` (qca8k-8xxx.c:1906) | CPU port's LOOKUP_MEMBER bitmap = all user ports; each user port's MEMBER = `BIT(cpu)`. The egress-allowed member set. |
| **b53/bcm_sf2** | `B53_PVLAN_PORT_MASK(i) |= BIT(cpu)` (b53_common.c:498-511, `b53_imp_vlan_setup`) + `B53_PORT_CTRL(cpu)=RX_{B,M,U}CST_EN` (b53_enable_cpu_port:694) | per-port PVLAN egress mask must include CPU; CPU PORT_CTRL must enable forwarding. |

### Mechanism B — per-frame destination-port TAG that OVERRIDES FDB (the inject path)
For CPU-injected frames, the driver does **not** rely on dst-MAC FDB lookup. It prepends
a switch tag carrying an explicit **egress-port bitmask + "from CPU" flag**; the fabric
forwards directly to those ports, bypassing FDB/learning. This is how the CPU picks the
port deterministically.

| Tag driver | Field that selects egress port |
|---|---|
| **tag_mtk** | `mtk_tag[1] = (1 << dp->index) & GENMASK(5,0)` (tag_mtk.c:57) — egress dest-port bitmask. |
| **tag_qca** | `hdr |= QCA_HDR_XMIT_FROM_CPU(BIT7); hdr |= QCA_HDR_XMIT_DP_BIT(BIT(dp->index))` (tag_qca.c:28-29) — FROM_CPU flag + dest-port map. |
| **tag_brcm** | `brcm_tag[3] = (1<<dp->index) & BRCM_IG_DSTMAP1_MASK` (+DSTMAP2 for port 8) (tag_brcm.c:118-120) — ingress dest-map. |

Note mt7530 also sets the CPU port to **fallback/security PORT_VLAN mode**
(mt7530.h:219-230, `MT7530_PORT_FALLBACK_MODE`) so the matrix/tag — not pure VLAN — gov-
erns CPU egress.

---

## Mapping to our SOPC — 1-3 hypotheses (ranked)

Our stock TX desc has **no dest-port field** (per `cpu_egress_routing_re.md`: desc
encodes GEM 0x2c = source LAN-up virtual port, NOT a destination). So we are relying
**purely on Mechanism A + FDB** (no Mechanism-B tag). That makes Mechanism A the prime
suspect: **the SOPC/fabric has no "CPU/LAN-up source-port → LAN-port-3 egress-allowed"
membership, so SOPC computes an empty egress bitmask and never asserts send2smacN.**

- **H1 (highest) — SOPC egress-port allowed-mask for the CPU/LAN-up source is empty
  or excludes port 3.** Direct analog of `PCR_MATRIX(cpu)` / `PORT_LOOKUP_MEMBER(cpu)` /
  `PVLAN_PORT_MASK|=BIT(cpu)`. Our GEM-0x2c (LAN-up source) needs its egress-member set
  to include physical port 3 (MAC2). Find the per-source-port (or per-GEM) egress bitmap
  in the SOPC/PP_BRG window and verify port-3 bit is set for the LAN-up source — this is
  almost certainly the missing config. Candidates already in our notes: PP isolate table
  `PP[0x83c0+src*4]`, SMAC_LOOK_EN `PP[0x81c0]`, DA_LOOKUP_EN `PP[0x82c0]`, and the SOPC
  send2smac select at `NPP 0x19068`/`0x1991xx`. Check whether the SOPC crossbar has a
  per-egress-port enable mask gated by the source GEM/port.

- **H2 (high) — SOPC needs a CPU-port egress-ENABLE / "from-CPU" allow bit**, analogous
  to b53 `b53_enable_cpu_port` (PORT_CTRL forwarding-enable) and mt7530's CPU-port flood
  enable `MT7530_MFC BC/UNM/UNU_FFP(BIT(cpu))` (mt7530.c:1036). If the SOPC treats CPU-
  sourced frames as a distinct class, there may be a per-egress-port "accept from internal
  source" enable that is unset. (Note `MFC` flood-enable is also what lets an *unknown*
  unicast / cold-ARP-reply reach the LAN before the host MAC is learned — worth setting.)

- **H3 (medium, alternative architecture) — adopt Mechanism B**: give the desc an explicit
  dest-port like mtk/qca/brcm tags do. This is the U-Boot direct-mux path (ETH_TM2
  `0x923a00e0=0x11` + MAC slots) which *bypasses* the FDB/fabric decision — exactly a
  hardware "dest-port tag." Stock kmod does NOT use it, but it is the proven-working
  egress on this silicon and is the cleanest fallback if the SOPC member-mask (H1) can't
  be located. (= "Way forward B" in the architecture doc.)

**Action**: locate the SOPC/PP_BRG per-source egress-port bitmap (H1) and confirm the
port-3 bit for the LAN-up GEM source; cross-check against a stock-live dump of that
register. That is the single most likely missing-config, matching the universal DSA
pattern of "CPU source-port → allowed-egress-port matrix."

---
## Sources
- OpenWrt forum, "Support for zx279128s" — SoC unsupported.
- WikiDevi ZTE; openwrt-avanta / openwrt-f660 (Marvell, different silicon).
- linux-v6.6 `drivers/net/dsa/{mt7530.c,mt7530.h, qca/qca8k-8xxx.c, b53/b53_common.c}`,
  `net/dsa/{tag_mtk.c,tag_qca.c,tag_brcm.c}`, `include/linux/dsa/tag_qca.h`.
