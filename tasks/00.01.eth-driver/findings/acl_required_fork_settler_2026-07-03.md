# acl_required + DN-bank + stage-ladder fork-settler — pre-CLA parse vs in-CLA lookup (2026-07-03, #476)

## VERDICT (TEST 1, the KEY output): **IN-CLA lookup miss = VERDICT B. Pre-CLA parse gate REFUTED.**
Measured direction-correctly (DN CLA bank + SPA/DPA/CLA stage-verdict ladder, after a mid-task
correction from the counter-mapping agent). During a real WAN download:
- **`acl_required` (submit-to-CLA, direction-agnostic) climbs 1:1 with load (+116), not flat/~14 %** →
  every WAN-ingress DN packet reaches the CLA lookup.
- **`acl_failed` +83 ≈ `cla_dn_trap` (DN CLA trap 0x9238c3d0) +84 ≈ QMG DN hw_trap +84** → the loss is
  packets trapping **inside the CLA lookup** (LOOK_UP_MISS).
- **`spa_trp` +4 and `dpa_trp` +0** → the pre-CLA parse stages (SPA classify, DPA parse) do **NOT**
  carry the loss. The l3_en=0 / parse-arm hypothesis is refuted on the correct counters.

⇒ The recent pivot (`wan_ingress_l3en_split` / `disposition_compare` / `stock_wan_ingress_l3en_arm_RE`)
toward "fix the DN parse-arm" rested on `l3_en=0 = QMG_hw_trap − cla_tx_trp`, computed from the **UP**
CLA bank against **DN** QMG. Read on the **DN** CLA bank + the stage ladder, the loss is unambiguously
at the CLA lookup, not the parse stage. Consistent with `wan_ingress_perpacket_key` (same key/slot,
resident+valid entry, still misses only on WAN-ingress) and the stock compare (byte-identical config,
stock forwards ~99 %).

---

## ★ Counter-bank correction applied (undecoded_pipeline_counters_2026-07-03.md)
CLA fwd/trap/drop are **direction-split**; the driver + all prior "authoritative" reads used the UP bank
while measuring a download:
| dir | CLA fwd | CLA trap | CLA drop |
|---|---|---|---|
| UP (LAN→WAN, uploads) | 0x9238c3c0 | 0x9238c3c4 | 0x9238c3c8 |
| **DN (WAN→LAN, downloads)** | **0x9238c3cc** | **0x9238c3d0** | **0x9238c3d4** |

`acl_required`/`acl_failed` = the single packed reg **0x9238c3b8** (hi16 = "acl required" = submitted to
CLA; lo16 = "acl failed" = lookup failed), **direction-agnostic** (from stock `tm statics`,
decomp_all_tm.c:68134). Stage-verdict counters (byte-packed fwd/drp/cpy/trp): **SPA** before/after-vlan
0x921d45c4 / 0x921d45c8, **DPA** (DN parse) 0x9239810c ([31:24]fwd/[23:16]drp/[15:8]cpy/[7:0]trp).

Read via debugfs `mem` (base phys 0x921c0000, `mem_woff=(phys-0x921c0000)/4`), all printk-independent:
CLA acl_req+UP+DN banks `skip=471278 count=8` (0x3b8..0x3d4); SPA `skip=20849 count=2`; DPA `skip=483395
count=1`; QMG DN sw/hw_fwd/hw_trap `skip=405521 count=3` (0x9234c044/48/4c). All verified in-window.

## Rig (PATH 1, real internet via the modem)
Device #476 fresh boot. Host `enxc8a362e95900` → device **lan2** (172.31.9.1/24), modem → **lan4**
(10.44.66.223/24, `default via 10.44.66.250`, 8.8.8.8 0 % loss). `MASQUERADE -o lan4`, FORWARD lan2↔lan4,
ip_forward=1. Host in netns `client` 172.31.9.50/24 (no wifi leak). nft offload flowtable `{lan2,lan4}`
loaded first and **confirmed installed** (dmesg `[phase6/ft] recipe: … wan_ing=1 raw=0x9609`) before the
download. `curl http://80.249.99.148/1GB.zip` + Host hdr, pinned `--local-port`. Cabling re-confirmed each
boot (host ping burst → lan2 rx +20, lan1 rx=0).

---

## TEST 1 — the fork-settler, DN-bank + stage ladder (3 parallel dl, ports 40000-40002)
**Window while flow offloaded (before → t+3 s):**
| stage / counter | phys | Δ | reading |
|---|---|---|---|
| `acl_required` (hi16) | 0x9238c3b8 | **+116** | packets submitted to CLA — tracks load |
| `acl_failed` (lo16) | 0x9238c3b8 | **+83** | 72 % of submitted → **lookup failed** |
| SPA classify trap | 0x921d45c4 byte0 | **+4** | pre-CLA SPA trap negligible (fwd +80) |
| DPA parse trap | 0x9239810c | **+0** | DN parse stage traps **nothing** (reg 0 throughout) |
| **CLA DN trap** | **0x9238c3d0** | **+84** | **the loss — trapped IN the CLA lookup** |
| CLA DN fwd | 0x9238c3cc | +0 | (see anomaly below) |
| CLA DN drop | 0x9238c3d4 | +0 | not a downstream drop |
| CLA UP fwd | 0x9238c3c0 | +33 | forwards land here (== QMG DN hw_fwd) |
| QMG DN hw_fwd | 0x9234c048 | +33 | |
| QMG DN hw_trap | 0x9234c04c | **+84** | **== CLA DN trap +84** |
| lan4 DN ingress | rx | +66 | |
| lan2 UP ingress | rx | +35 | |

**The trap ladder resolves the stage cleanly: SPA trap +4, DPA trap +0, CLA DN trap +84.**
`cla_dn_trap (+84) ≈ acl_failed (+83) ≈ QMG DN hw_trap (+84)` — the download DN packets reach the CLA and
trap in the lookup. This is the direction-correct confirmation the counter-mapping agent asked for, and it
is more direct than `acl_required` alone.

**Post-collapse window (t+3 → t+6 s, flows torn down):** `acl_required`/`acl_failed` **froze** (+0) while
`cla_dn_trap`/`spa_trp`/QMG hw_trap/lan4 rx each climbed +10 — i.e. once the offload entry is gone the DN
packets default-trap **without** being counted as "ACL required" (they don't need a lookup). This is why a
raw `QMG hw_trap` over-counts the miss and why `acl_required` is the correct gate for "reached the CLA".

**Anomaly (flagged, does not change the verdict):** `cla_dn_fwd` (0x3cc) read **+0** while `QMG DN hw_fwd`
(0x048) and `cla_UP_fwd` (0x3c0) read +33 (and lan2 UP ingress +35). So the ~33 forwards register in the
UP fwd bank / QMG-DN-hw_fwd, not in the DN CLA fwd bank — suggesting the forwarded packets are largely the
UP-ACK path (LAN→WAN) and that the **DN download DATA HW-forwards ≈ 0 %** on this build (worse than the
"~14 %" prior sessions read off the wrong/UP bank). The fwd-side bank labeling needs one more disambiguation
(drive a pure DN-only flow), but the **trap side is unambiguous** and carries the verdict.

## TEST 2 — 5th trap_dmac slot
`mem` dump phys 0x921d41a0 + i·8, i=0..4 (all 5 to-me DST-MAC trap slots) = **all 0x00000000**, incl.
**slot 4 (0x921d41c0/0x921d41c4) = 0**. No stuck 5th slot; nothing to clear, no re-run needed. Empirically
closes the lead the static RE (`stock_wan_ingress_l3en_arm_RE`) predicted dead. (Read method validated
against cla_config 0x9238c080=0x600, hash_poly 0x090=0x00e400e4, outspace 0x094=0x4.)

## TEST 3 — same-boot LAN-vs-WAN A/B on one byte-identical DN 5-tuple
DSA tc-flower skip_sw on **lan2 (LAN/GePHY ingress)** for the *same* DN 5-tuple `80.249.99.148:80 →
10.44.66.223:40000`:
`tc qdisc add dev lan2 clsact; tc filter add dev lan2 ingress protocol ip flower skip_sw ip_proto tcp
src_ip 80.249.99.148 dst_ip 10.44.66.223 src_port 80 dst_port 40000 action mirred egress redirect dev lan4`
→ dmesg recipe `in_rp=3 raw=0xd37f` (pos32=0, LAN-keyed). Injected **200 TCP PSH,ACK data frames** of that
5-tuple **into lan2** (host `rawflow.py` in the netns).

| ingress | entry | acl_required | acl_failed | HW-fwd verdict |
|---|---|---|---|---|
| **LAN / GePHY (lan2)** | raw 0xd37f | **+200** | **+0** | **+200 = 100 % hit** (cla_fwd/QMG hw_fwd +200, hw_trap +0) |
| **WAN / RGMII (lan4)** | raw 0x9609 | +116 | +83 | ~72 % `acl_failed` / `cla_dn_trap` |

Identity `200 = 0 + 200`. **clapeek** (resident+valid, same boot):
- LAN `ram2[0x7f]` = `03005044 fa11c000 00000608 00000000 06000049 9450f900 df0a2c63 40005042 0000009c`
- WAN `ram2[0x09]` (during traffic, from `perpacket_key`) = `… fa11c009 …` — **BYTE-IDENTICAL except word1
  low byte (`00` LAN vs `09` WAN) = the ingress-keying field.**

Identical install mechanism (both submit to the CLA), byte-identical entry, opposite hit rate.
**⇒ the ingress datapath (WAN/RGMII vs LAN/GePHY) is the SOLE variable.** LAN-ingress packets hitting the
same-shape entry never fail the lookup; WAN-ingress packets reach the CLA and ~72 % fail it.
(NB: TEST-3 LAN drive is a LAN→WAN/upstream flow with a LAN-keyed entry; a true DN-direction LAN-ingress
drive of the *WAN-keyed* entry is not feasible because pos32 differs by ingress — the closest clean A/B,
stated per the task.)

---

## CONCLUSION — branch + sharpest next fix
**VERDICT B (in-CLA WAN-ingress lookup miss), confirmed on the direction-correct DN bank + stage ladder.**
The parse-gate branch is dead: SPA trap ≈ 0, DPA trap = 0, `cla_dn_trap` carries the entire loss and equals
`acl_failed`. The gate is a **WAN/RGMII-ingress-specific CLA lookup failure** for an entry that is at the
correct slot (pos32 proven), byte-identical to a LAN entry that hits 100 %, and resident+valid.

**Sharpest next fix = the WAN-ingress CLA lookup engine / per-ingress way-probe:**
1. Determine which of the 5 installed ways (ram2[0x09]…ram6[0x201]) the **WAN-ingress** lookup actually
   probes vs LAN — read `cla_get_outspace_cfg` / `ACL_OUT_SPACE_SEL` / `outer_hash_num` and test empirically:
   install the WAN DN entry in **all 5 ways** vs **way0 only** and re-measure `acl_failed`/`cla_dn_trap`.
2. Compare the WAN entry's stored windata compare-field vs the WAN-ingress-extracted compare bytes — the
   `fa11c009` vs `fa11c000` word1 low byte is the ingress field; check the lookup isn't comparing+rejecting it.
3. Settle the fwd-bank anomaly: drive a pure DN-only flow and confirm whether `cla_dn_fwd` (0x3cc) ever
   moves — if DN data HW-forwards ≈ 0 %, the "~14 %" was always UP-ACK bleed and the real WAN-DN forward
   rate is near zero (raises the stakes on the CLA lookup fix).
A *partial* ~72 % miss on a deterministic hash at the correct slot points to a way/bank-probe subset or a
WAN-ingress pipeline race — the VERDICT-B engine lead.

## Left clean
- Device **DTR-rebooted to pristine #476** (reboot_mainline.py, BOOT_OK ×2): rc.router defaults
  (sw=192.168.1.99, lan1=172.31.9.1, lan4=192.168.9.1), no default route, **nft empty**, DN hw_trap=5
  (**no wedge**), printk=1 4 1 7. tc/nft/iptables residue gone.
- Host: `enxc8a362e95900` in root ns @192.168.1.50, `192.168.1.0/24` route restored (TFTP-ready), single
  `in.tftpd`, netns `client` torn down.
- Driver source UNCHANGED, nothing committed. Scripts: `scratchpad/{repl.py, netns_up.sh, netns_down.sh,
  reboot_mainline.py, rawflow.py; device /tmp/s2.sh ladder-sampler}`.
