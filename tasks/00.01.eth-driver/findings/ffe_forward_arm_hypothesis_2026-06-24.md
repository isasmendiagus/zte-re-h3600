# The missing forward-arm: per-flow CLA ram0 index_valid bit (slow-path) — 2026-06-24

## ⛔ CONFOUNDER TEST BLOCKED BY RIG/DRIVER — could NOT build a genuinely-routed bidirectional flow (2026-06-27, modem-on-WAN attempt)
**GOAL:** resolve the standing confounder (every prior mainline test used a ONE-WAY ingress stream with
no resolvable next-hop / no return path) by routing host(lan2)→modem(10.44.66.250 on the WAN/RGMII port,
a real ARP-resolvable responder) THROUGH the device, establishing an ESTABLISHED bidirectional flow, and
re-measuring acl_required (4a no-install / 4b full-install).

**WHAT WORKED (feasibility partially passed):** Device was already on mainline 6.6.0 #444 (uptime ~8.5h,
no reboot). The mainline WAN port **lan4 (= MAC4/regport[4]=5, ZX5201 PHY8) LINKS to the modem**:
BMSR phy8 = 0x796d (link bit set), DSA "Link is Up - 1Gbps/Full". Set lan4=10.44.66.223/24; the device's
**FIRST ping batch to the modem 10.44.66.250 succeeded 4/4, 0% loss, ttl=64**, and ARP resolved the
**real next-hop MAC = cc:29:bd:22:b4:2b** (matches the recorded modem MAC). Device had ip_forward=1 +
MASQUERADE `out lan4` already installed (1524 pkts). So the *link* and the *next-hop resolution* are real.

**WHY THE TEST COULD NOT PROCEED (two hard blockers + one access blocker):**
1. **WAN/lan4 RX→CPU is HARD-WEDGED at exactly 1024 packets** (the documented one-wrap halt / RED-wedge HW
   latch on the ring-1/DN path, see rx_ring_wrap_re.md + [[zte-redwedge-unicast-cpu]]). Driver stats:
   `rx_per_ingress port4 = 1024` FROZEN (port2/lan2 = 2191, climbing). After the first ping batch consumed
   the pre-wedge budget, **every subsequent modem ping/ARP failed** (8/8 loss, lan4 rx stuck at 1024 across
   repeated tries). ⇒ the modem's replies / ARP responses can no longer reach the CPU → **no return path**,
   so a flow can never become conntrack-ESTABLISHED. This is a driver bug independent of the offload test.
2. **CPU→LAN egress to the host on lan2 is DEAD this boot.** Host→device pings on lan2 are RX'd by the CPU
   (port2 RX climbs) but the device emits ZERO reply frames (host tcpdump on the device MAC = 0 captured;
   send2smac2 0x921d9164 / MAC2_TX 0x92280718 both FROZEN at 0x19=25, no delta during a ping). eg_port=2
   (correct for host-on-MAC2) but the egress is non-deterministic/wedged (matches zte-tx-egress-blocker:
   "needs priming, may wedge"). ⇒ the host↔device↔modem return leg is dead in both candidate directions.
3. **No host root → cannot reboot or reconfigure.** A fresh TFTP boot would clear both wedges (and give
   ~1024 packets of working WAN RX — enough, since stock's FFE installs on the 2nd packet of a 5-tuple),
   BUT the boot preamble hardcodes `serverip 192.168.1.50` and the host NIC currently holds 172.31.9.50;
   `ip addr add 192.168.1.50` fails (no sudo, no cap on /bin/ip, no netns with that IP). Host routes also
   can't be added, so host→modem traffic can't be forced through the device (host reaches the modem
   directly over its own wifi, same /24).

**ONLY ACHIEVABLE MEASUREMENT (the one-way control, = the confounder case, NOT its resolution):** routed
host 172.31.9.50:40000 → 192.168.9.50:5201 (host route via 172.31.9.1=lan2; device routes it out lan4;
no responder at .50 → next-hop unresolvable). 400 UDP datagrams (single pinned 5-tuple, no root → Python
UDP socket, hping3 needs root). Result: **acl_required(hi16) FLAT 26→26, cla_tx_fwd FLAT 0, cla_tx_trp
+405 (≈ all trapped); only 26/400 even egressed lan4** (the rest dropped at unresolved-ARP). This merely
re-confirms the prior FLAT one-way result on this boot; it does NOT control the confounder (this flow has
no resolvable next-hop / no return path — exactly the artifact case).

**VERDICT: INCONCLUSIVE — confounder UNRESOLVED.** The genuinely-routed bidirectional ESTABLISHED flow
(the whole point of the test) could not be constructed: the WAN-port→modem direction links and the
next-hop resolves, but the RETURN path is doubly broken (WAN RX one-wrap-latch + dead lan2 CPU egress),
and no root → no reboot to clear the latches / no host-route to force the path. NEXT (needs the operator):
either (a) grant host root so a TFTP reboot can run (`serverip 192.168.1.50` on the connected NIC) →
re-attempt within the fresh ~1024-packet WAN-RX window with a low-rate sustained TCP/UDP flow to the modem;
or (b) fix the WAN RX one-wrap-halt + CPU→LAN egress wedge in the driver first (they block any real routed
flow regardless of offload). All device writes were RAM-only / interface-config (lan4 IP+route+static ARP,
all REMOVED afterward); device left healthy on mainline, lan4 restored to 192.168.9.1/24, existing
bridge/routes intact, NO reboot.


## ❌❌❌❌ REFUTED ON HARDWARE (2026-06-27, the byte-0x05=0xc0 ARM test) — the last static content diff is NOT the gate; outcome (b) CONFIRMED, the submit gate needs the live CPU-routed pipeline, not static content
Device freshly TFTP-booted to mainline 6.6.0 (RAM-only, conduit sw=192.168.1.99). Rig: host
`enxc8a362e95900`=172.31.9.50/24 cabled to device **lan2 = PP ingress port2** (confirmed: device lan2 ARP
learns host MAC c8:a3:62:e9:59:00, smac2 RX climbs with the flow); device lan2=172.31.9.1, **lan4=192.168.9.1**
(carrier up), ip_forward=1, FORWARD ACCEPT. Host route `192.168.9.0/24 via 172.31.9.1` (gw resolved to
f4:f6:47:0f:42:64 REACHABLE). Test flow `172.31.9.50 → 192.168.9.50:5201` sport40000 (UDP + TCP-SYN, ≥300 pkts
each per variant). NOTE: busybox `ip neigh` has no add/replace + no `arp` → the egress next-hop is NOT
kernel-resolvable (one-way ingress stream, same caveat as all prior mainline runs); the HW rewrite MAC is
supplied by PM ram1, and the test exercises the **ingress→submit** decision (smac2/SDET confirmed reached).

**THE HYPOTHESIS:** the byte-diff (agent a0251b47) found stock's LIVE HW-forwarding ram2 entry differs from
our inert mainline poke in exactly ONE content byte: **byte 0x05 = stock 0xc0 (e8_en/modify_en bit6 +
vlan_rp_en bit7 ARMED) vs mainline 0x00 (UNARMED)**. The make-or-break + complete-PM-chain installs both used
`fa110005` (byte5=0x00). This test restores byte5=0xc0 (→ word1 = `fa11c0NN`, the spec's documented value) and
remeasures.

**INSTALL (readback-CONFIRMED every write, all 3 variants):** CLA ram2 fwd entry via **fill520** (entry written
to ALL 520 buckets — slot-prediction dimension removed; confirmed present at ram2[5], ram2[0xc7]=stock's slot,
ram3[0x10]) with **byte0x05=0xc0**; CLA **ram0[9] word4 0x00150051→0x00150151 (bit8 SET, readback OK)**; boot
rule **ram1[0x98]** = exact generic boot rule (copied from the driver-installed ram1[0x90]); full PM chain
**ram0 flow_info + ram1 next-hop (192.168.9.50 + MAC 6c:70:cb:b6:81:69) + ram6 sub_ram + ram3 cmd_ram**, all
readback-confirmed, pointer chain resolved.

**VARIANTS + COUNTERS (acl_required=hi16 of 0x9238c3b8; cla_tx_fwd 0x9238c3c0; cla_tx_trp 0x9238c3c4; hw_trap
0x9234c060):**

| variant | ram2 word1 | counters BEFORE → AFTER (~600 pkts UDP+TCP) | result |
|---|---|---|---|
| **V1** byte5=0xc0, cmd_flow_id=5, flow_info@5 (= prior complete install + ONLY byte5 armed) | `fa11c005` | acl_req **13→13**, cla_tx_fwd **0→0**, cla_tx_trp 58→661 (+603), hw_trap 58→661 (+603) | **FLAT** |
| **V2** byte5=0xc0, **cmd_flow_id=0, flow_info@0** (max fidelity to stock — word1 byte-identical to stock) | `fa11c000` | acl_req **13→13**, cla_tx_fwd **0→0**, cla_tx_trp 666→1269 (+603), hw_trap 666→1269 (+603) | **FLAT** |
| **V3** fill520 byte5=0xc0 + ram0[9] bit8 readback-confirmed, sustained 400-pkt UDP, mid-flow read | `fa11c000` | acl_req **13→13** (mid-flow 0x000d000d), cla_tx_fwd **0→0** (mid-flow 0), cla_tx_trp 1273→1674 (+401), hw_trap 1273→1674 (+401) | **FLAT** |

Every variant: **acl_required(hi16) and cla_tx_fwd stayed DEAD-FLAT** while **every single packet CPU-trapped**
(cla_tx_trp/hw_trap climbed +Npkts, smac2 RX +Npkts = ingress reached). desIn 0x9238c3e0 mid-flow = 0x509a403c
(shows the flow's port 0x9a40=40000 — packet reaches the CLA-ingress descriptor stage, but this is the shared
per-packet snapshot, not a pinned forward decision; the counters are the reliable signal and they are flat).

**VERDICT — OUTCOME (b) CONFIRMED. byte0x05=0xc0 was NOT the missing piece.** The byte-diff's sole static
content difference (the e8_en/modify_en/vlan_rp_en ARM byte) does NOT lift `acl_required` or engage
`cla_tx_fwd`, even with the now-byte-identical word1 (`fa11c000`, cmd_flow_id=0), the full PM pointer chain, the
boot rule at the armed slot, and ram0[9] bit8 set, and even with the entry written to ALL 520 hash buckets so
no slot can be missed. This **closes the byte-diff branch** and confirms the standing reframe: byte0x05 is read
**AFTER** a packet is submitted to the CLA forward classify, but on mainline **the packet is never submitted**
(`acl_required` flat 0/13-background → the upstream SPA-classify/SDET per-inport submit-vs-trap takes the
TRAP disposition before the CLA forward tables are ever consulted). **The forward-submit gate is genuinely the
DYNAMIC live-pipeline path** (stock's CPU actively routing + the FFE conntrack install through the real
datapath — `ffe_learn_skb → hf_set_l3_entry → zte_api_fast_l3_session_add`), NOT any static table content.
⇒ STATIC REPLICATION IS NOW FULLY EXHAUSTED (refuted: ram2-inport, ram1 per-flow rule, ram0 bit, full PM chain,
ONU-MAC, local_ipv4, routing-context regs, SPA pktdeal, DPA parse-enable, SPA classify RAMs, **and now the
byte0x05=0xc0 arm — the last content diff**). The path forward = **user decision (B): wire the real dynamic
path** (hook conntrack IPS_CONFIRMED → drive the CPU-routed first-packet through switch.ko's datapath so the HW
itself sets the submit/l3_en for the flow). All writes RAM-only; device verified healthy (ip_forward=1, lan2
ARP bidirectional/REACHABLE, pipeline kept trapping normally = no wedge); device LEFT ON MAINLINE.

---

## ❌❌❌ REFUTED ON HARDWARE (2026-06-27, the COMPLETE PM-chain install) — completing ram6+ram3 + real next-hop + routable flow does NOT lift acl_required; the gate is genuinely UPSTREAM (dynamic submit path)
Device on mainline 6.6.0 #444 (uptime ~29h, no reboot). The prior "make-or-break" install left a **dangling
sub_ram_index**: this test completed the full PM pointer chain and measured — DECISIVELY FLAT.

**STEP 0 — flow_info/sub_ram/cmd_ram linkage layout (decoded from decomp_all_tm.c, verified on device):**
- **PM indirect iface** (driver `zx_pp_pm_*`, ppPmRegTable @ block 0x1DC000 → phys **0x921dc000**, inside the
  poke window): CMD 0x921dc014 = `addr | ram_id<<22 | rw<<27`; DONE 0x921dc018 bit0; DATA0-3 @0x921dc01c,
  DATA4-7 @0x921dc100. **ram_id selects the table**: 0=flow_info(3 words), 1=next_hop(3 words),
  3=cmd_ram(1 word), 4=e8_qos, 6=sub_ram(2 words). The debugfs `pmwrite <ram_id> <addr> <w0..w7>` already
  uses the generic `ram_id<<22` encoding → ram3/ram6 writable with NO driver change.
- **flow_info** (`pp_pm_set_flow_info`@18340, byte array p[0..11]): `dmac_en=p0&1, smac_en=p0bit1,
  hl_ttl_en=p4bit2, ip_chk=p4bit4, tcp_udp_chk=p4bit3, sport_en=p4bit6, sip_en=p5bit0,
  next_hop_idx=(p7&7)<<6|(p6>>2) [9-bit →ram1], sub_ram_index=(p8&0x1f)<<5|(p7>>3) [10-bit →ram6]`.
  ★ **The prior install `fi=0de80005 0014035c 0` decodes to next_hop_idx=5 BUT sub_ram_index=0** — a
  dangling pointer into the UNWRITTEN ram6[0]. (dmac_en/hl_ttl_en/chk bits were all set → it DID request a
  rewrite, but the microcode pointer chain was broken.)
- **sub_ram** (`pp_pm_set_sub_ram_info`@19411, ram_id 6, 2 words, p[0..7]): `cmd_addr=(p2<<3)|(p1>>5)|
  (p3&3)<<11 [13-bit →ram3], vlan_addr=(p4&0xf)<<6|(p3>>2), modi_dat_addr=(p5&0x1f)<<4|(p4>>4),
  swap_en=p5bit5, *_en flags in p1[4:0]`. next_hop_idx is NOT here (it's in flow_info directly).
- **cmd_ram** (`pp_pm_set_cmd_ram_info`@19044, ram_id 3, 1 word): `data0 = modify_data[15:0] |
  modify_cmd<<16 | ip_chk<<21 | tcp_chk<<22 | last_cmd<<23 | dat_type<<24`. Production builder
  `writeCmdInfoToRam`@50253 streams 12-byte cmd records (the DMAC/SMAC/TTL-- microcode lives in switch.ko
  `hf_set_l3_entry`, not in tm). A minimal **last_cmd=1 no-op (`00800000`)** makes the entry well-formed.
- **Full chain**: CLA ram2[5].cmd_flow_id=5 → flow_info[5] → {next_hop[5], sub_ram[5]} → cmd_ram[5].

**STEP 1 — genuinely-routable flow:** host enxc8a362e95900=172.31.9.50/24 cabled to device **lan2 (PP
ingress port2)**; device lan2=172.31.9.1, lan1=192.168.9.1, ip_forward=1; kernel route `192.168.9.50 dev
lan1 src 192.168.9.1` resolves (lan1 directly connected). Host route `192.168.9.0/24 via 172.31.9.1 dev
enxc8a362`. Next-hop MAC fed to PM ram1 = `6c:70:cb:b6:81:69` (real). (busybox `ip neigh` here only
supports show/flush — but the HW rewrite MAC comes from PM ram1, not the kernel neigh; route is routable.)

**STEP 2 — COMPLETE install (readback-CONFIRMED every write, rc=0):**
- CLA ram1[0x98] boot rule; CLA ram0[9] `00150051→00150151` (slot-8 index_valid bit8 SET, readback OK);
  CLA ram2 fwd entry via fill520 520/520 (readback ram2[5]=`03005044 fa110005 00000608 80000000 06000049
  32ac1f00 32c0a809 519c4009 00000014` = exact 5-tuple TCP/172.31.9.50→192.168.9.50:40000→5201, w3 valid).
- PM ram1[5]=`c0a80932 cbb68169 00006c70` (dip + next-hop MAC). 
- ★ PM ram0[5] flow_info=`0de80005 2814035c` — **patched p7 0x00→0x28 to set sub_ram_index=5** (next_hop_idx
  still 5; readback confirmed). rev @0x405 same.
- ★ PM ram6[5] sub_ram=`0000a000` (cmd_addr=5; readback OK).
- ★ PM ram3[5] cmd_ram=`00800000` (last_cmd=1 minimal valid; readback OK).
The dangling pointer is GONE: ram2→flow_info→{next_hop,sub_ram}→cmd_ram all resolve.

**STEP 3 — MEASURE (BEFORE → AFTER ~600 pkts [300 TCP-SYN + 300 UDP, sport40000 dport5201], + a 2nd 400-pkt
burst):**
| counter | addr | BEFORE | AFTER | Δ |
|---|---|---|---|---|
| **acl_required (hi16)** | 0x9238c3b8 | 5 | **5** | **FLAT** |
| **cla_tx_fwd** | 0x9238c3c0 | 0 | **0** | **FLAT** |
| cla_tx_trp | 0x9238c3c4 | 4303 | 5313 | +~1010 (≈ all pkts) |
| hw_trap | 0x9234c060 | 3325 | 3930+ | +~600 (≈ all pkts) |
pipeline_stats during the flow: smac2 RX climbing, **uni2 SDET_transport=203** (pkts reach SDET on port2),
**CLA fwd[0x1cc3c0]=0 drop=0 copy=0** (forward engine consulted NOTHING), **QMG UP hw_fwd=0 hw_trap=4336**.

**VERDICT: completing the install did NOT arm the submit.** Both acl_required and cla_tx_fwd stayed
dead-flat while every packet CPU-trapped — the EXACT signature of the incomplete install. ⇒ The install
incompleteness (dangling ram6/ram3) was **NOT** the issue. **acl_required is genuinely UPSTREAM-gated**: the
packet takes the per-inport TRAP disposition at SPA-classify/SDET and is never submitted to the CLA
forward/ACL classify, so the now-complete ram2→flow_info→sub_ram→cmd_ram chain is never consulted. This
CONFIRMS the standing reframe (★★★★ below): the gate is the submit-to-ACL / l3_en=1 decision made UPSTREAM
of the CLA — the dynamic CPU-routing/priming path that stock's runtime Enrutamiento provisioning sets, NOT
any static table completeness. The PM-table-completeness branch is now CLOSED. All writes RAM-only; device
verified healthy (lan2 ping 0% loss, routes/bridge intact); no reboot.


## ❌❌ REFUTED ON HARDWARE (2026-06-27, decisive parse-enable + classify-RAM test) — the DPA protocol-analysis-enable and the SPA classify RAMs are NOT the ingress forward-arm
Device on mainline 6.6.0; transit flow `172.31.9.50 → 192.168.9.50:5201` ingressing **lan2 = PP ingress port2**
(host enxc8a362e95900=172.31.9.50/24; device lan2=172.31.9.1, lan1=192.168.9.1 [this boot the dst subnet
is on lan1, not lan4], ip_forward=1; host route 192.168.9.0/24 via 172.31.9.1 → packets route into the box,
one-way stream exercises ingress classify). Counters via debugfs `poke` (hi16 for acl_required).

**STEP 0 — addresses nailed from tm.ko (`ext/rootfs/kmodule/tm.ko`):**
- `dpa_set_protocol_pkt_aly_en(type_id 0..6, 1)` → `tmOnuRegWrite(reg_id=type_id, …, &dpaRegTable)`.
  dpaRegTable (.data+0x2fa8) reg_id 0..6 all have **fpga widx 0xe6000 = phys 0x92398000, mask 1, shift 6..12**
  → enabling types 0..6 = setting bits **[12:6] = 0x1FC0** of 0x92398000. `protocol_cpu_pps_en` = 0x92398014 bit0.
- Matchram source = **`.rodata + 0x1990`** (R_ARM_MOVW/MOVT `.LANCHOR1`, val 0x1990; 0x160 bytes = 11 entries
  × 8 input-u32). Decoded 11 entries {rule,valid,v4v6,offmode,offset,cmpmode,mask,data}: e0 off4/m00ff/d0011
  (proto=UDP), e1 off0xb/d0208, e2 d076c, e3(cmp1) d013e, e4(cmp2) d0141, e5 off0xa d0043, e6 off0xa d0044,
  e7 off0xb d0043, e8 d0044, e9 off4/m00ff/d0006 (proto=TCP), e10 d00b3. = **L3/proto byte-matchers for
  control-plane punt (DHCP 67/68=0x43/0x44, specific ports, IP-proto), NOT a generic-routed-flow arm.**
- poke window is `[0x921c0000, 0x923c0000)` (e->base=npp 0x921c0000 size 0x200000) → reaches BOTH 0x92398000
  (DPA, off 0x1d8000) and the SPA indirect 0x921d4000.

**STEP 1 — BASELINE (mainline, no flow):**
- DPA `0x92398000 = 0x000010C0` → bits 6,7,12 set ⇒ aly-en types **{0,1,6} ON, {2,3,4,5} OFF** (NOT stock's
  full 0x1FC0). `0x92398014 = 0x1F` → cpu_pps_en bit0 already ON. **The mainline driver NEVER writes 0x92398000
  (grep-confirmed) ⇒ 0x10C0 is the HW reset/strap default.**
- SPA matchram ram_id0 lines 0,1,2 (rules 0-10) = **ALL ZERO (empty)**; hashram ram_id5 line0 = **ALL ZERO**.
  (Read via SPA indirect: CMD 0x921d4014 = addr|ram_id<<22|rwEn0; DONE 0x921d4018 bit0; DATA 0x921d401c..30.
  Leftover CMD readback was 0x01400007 = ram_id5 addr7, the last stock-init hashram write — confirms format.)
  ⇒ confirms the hypothesis premise: **classify RAMs ARE empty on mainline.**
- Counters: acl_required(hi16)=**1**, cla_tx_fwd=**0**, cla_tx_trp=2038, hw_trap=2038.

**TEST A — parse-enable cannot be flipped (HW-CLAMPED):** writing `0x92398000 = 0x1FC0` (and even 0xFFFFFFFF)
**reads back 0x10C0 every time** (double-write, re-read all confirm). Bits 8-11 (types 2,3,4,5) are
**not settable via this MMIO write** — reserved/strapped/precondition-gated. So the "most direct l3_en gate"
(full protocol-analysis enable) is **physically unreachable by register write**, and mainline already sits at
the HW-allowed value. ⇒ **Test A is a no-op: parse-enable is not a lever, and is not the discriminator
(mainline = HW default = whatever stock also lands on for these bits).**

**TEST B — classify-RAM load: NOT PERFORMED (write), refuted by prior RE + control result.** Per
`tasks/00.10.02.re-stock-kmods/findings/spa_match_hash_ram_re.md` (HIGH-confidence static RE): the matchram is
**portless** and the hashram is a **trap/action RESOLVER** (rule-hit vector → action+reason); their **default-
empty behavior is ADMIT-FORWARD**, not trap, and their content encodes **L3/EtherType control-plane TRAP
matchers (IPv4/IPv6/ARP/DHCP→CPU)** — explicitly "**not** a per-port admit gate; populating them is not
expected to fix forwarding." Loading them can only ADD control-plane traps; it does NOT carry the forward-
submit / l3_en arm. (The dense per-rule RMW bit-packing would also risk corrupting the live classifier that
the working L2 bridge/egress depends on, for a test the RE already predicts null.)

**CONTROL / MEASUREMENT (3 independent 300–600-pkt runs, current state = partial-DPA-0x10C0 + empty RAMs):**
every run: **acl_required(hi16) FLAT** (1→1, then 3→3 after background drift), **cla_tx_fwd FLAT at 0**,
cla_tx_trp +~Npkts, hw_trap +~Npkts. Every transit packet CPU-trapped; the CLA forward-submit/acl path
never engages — IDENTICAL signature to all prior runs. desIn (CLA-ingress, fpga 0xe30fb=phys 0x9238c3ec,
l3_en=bit6) read during the flow showed a non-deterministic snapshot value (0x80010841, bit6=1) but this is
a shared per-packet snapshot register, not pinned to the trapped transit packet — the **counters are the
reliable signal and they are flat.**

**VERDICT (this branch closed):** Neither the DPA protocol-analysis-enable NOR the SPA classify RAMs are the
ingress forward-arm. (a) Parse-enable is HW-clamped/unwritable and mainline already = HW default (non-
discriminator); (b) the classify RAMs are portless control-plane trap matchers whose empty default is admit-
forward, not the L3 forward-submit gate. This **reinforces the standing conclusion** that `l3_en` is HW-
internal/not SW-armed by any of these inits, the per-ingress disposition `enty_pktdeal` was already flipped
deal=0→1 and REFUTED, and the routing-context regs (claRegTable 0x1e-0x24 / mac_req_ctrl bit11) read 0 on
BOTH stock-while-routing and mainline. ⇒ **The arming that submits a routed transit packet to CLA forward is
NOT in the SPA/DPA flat or indirect init — it is a dynamic path** (set by stock's runtime Enrutamiento/flow
provisioning, not by `tm_pon_pp_initial`/`tm_pon_npp_spa_initial` static init). All writes were rejected/RAM-
only; device verified healthy (lan2 ping 0% loss, bridge intact); no reboot.

---

## ★★★★★★★ NEW LEAD (2026-06-27, agent aba4f493 + driver-source check) — mainline SKIPS the ingress L3-arming init (l3_en=0 explained)
Completeness-critic decomp diff + driver grep converge on a concrete GAP (not a dead-end):
- **acl_required=0 ⇒ packets never reach CLA-TX classify as "needs ACL"** (cast-class config already
  selects Acl on BOTH; extract tables present) → diverted/trapped UPSTREAM of CLA-TX. Root symptom
  l3_en=0 (descriptor probe). l3_en/ip_flag is armed by the PARSER, enabled by
  `dpa_set_protocol_pkt_aly_en(0..6,1)` @decomp:14927 ← `tm_pon_pp_dpa_initial`@43094 ← `tm_pon_pp_initial`@43666.
- **DRIVER GAP (zx-eth-main.c, grep-confirmed):** the driver has NO matchram/hashram/spa_set_match/
  spa_set_hash load and NO dpa/protocol-analysis-enable. `zx_pp_init`@1076 is partly a FLAT replay of a
  `stock_eth.bin` DIRECT-register dump (line 1081) — which CANNOT capture INDIRECT RAMs. So the **SPA
  classify RAMs (matchram ram_id0 = the 11-entry .LANCHOR1 L3/EtherType byte-matcher; hashram ram_id5)
  are EMPTY on mainline**, and the protocol-analysis-enable may be unset → no packet is flagged L3 →
  acl_required=0 → trap. (The prior "SPA match-RAM not the gate" finding was about EGRESS authorization,
  a different datapath — not contradicted.)
- **SPA indirect protocol:** base 0x921d4000, CMD 0x921d4014=addr|ramid<<22|rwEn<<27, DONE 0x921d4018
  bit0, DATA 0x921d401c..0x921d4030 (6 words/line, 4 rules share a line → RMW). ram_id0=matchram,
  ram_id5=hashram. matchram entry = {rule,valid,v4_v6,offset_mode,offset,cmp_mode,mask(u16),data(u16)}
  matching at offsets 4/10/11.
- **ALSO still-missing table writes (necessary-not-sufficient, for AFTER submit works):** PM ram6 sub_ram
  (`pp_pm_set_sub_ram_info`@19468, UNCONDITIONAL — our flow_info's sub_ram_index points into it = dangling
  ptr); PM ram3 cmd_ram (`pp_pm_set_cmd_ram_info`@19104 = the DMAC/SMAC/TTL-- rewrite microcode).
- **NO HW route/LPM/FIB table exists** (deliverable-3, exhaustive grep) — L3 fwd is purely per-flow CLA hash. subnet_id = a 4-bit ONU-MAC selector, not a route. SADM = policer, not route stage.
- **DECISIVE TEST (device on mainline NOW):** (1) read mainline DPA protocol-analysis-enable reg (addr from
  dpa_set_protocol_pkt_aly_en@14927) + SPA matchram(r0)/hashram(r5) — confirm disabled/empty; (2) enable
  protocol-analysis + load the .LANCHOR1 classify RAMs via the SPA indirect; (3) transit flow → does
  l3_en (CLA desIn 0xe30f8) flip to 1 + acl_required (0x9238c3b8 hi16) climb? Incremental: test the parse-
  enable ALONE first (most direct l3_en gate), then the matchram/hashram. If acl_required climbs → THE GATE
  → then add ram2+ram6+ram3+PM for full cla_tx_fwd. If nothing → the arming is elsewhere (dynamic).

---

## ❌ REFUTED ON HARDWARE (2026-06-27) — SPA pktdeal=1 is NOT the gate (decisive deal-flip test)
Device on mainline 6.6.0 #444; transit flow `172.31.9.50 → 192.168.9.50:5201` ingressing **port2/lan2**
(live cabling: host `enxc8a362e95900` cables to device **lan2**, confirmed by smac2/lan2 RX climbing).
Counters via debugfs `poke`: acl_required 0x9238c3b8, cla_tx_fwd 0x9238c3c0, cla_tx_trp 0x9238c3c4,
hw_trap 0x9234c060.

**STEP 1 — baseline port2 pktdeal (0x921d4328, 5 dwords):** `50555555 05551545 00544004 55555544 00000000`.
Decoded (reg_id=67+proto, port2 stride 5 dwords, 2-bit field, dword=proto>>4, shift=(proto&15)*2):
the 17 ACK-fwd slots {0x0c,0x0d,0x17,0x1f,0x22,0x24,0x25,0x26,0x2c,0x2d,0x2f,0x40-0x45} ALL read **deal=0**
(confirms `zx_chip_tm_init_pro_action` applied the ACK-fwd override on port2); the rest are deal=1 (trap)
except the stock action_pp0=0 protos. So hypothesis-A's premise (routed slot may be deal=0) is plausible.

**CONTROL (no flip):** 400 transit pkts (200 TCP SYN + 200 UDP) → acl_required 0→0 (FLAT),
cla_tx_fwd 0→0 (FLAT), cla_tx_trp +404, hw_trap +404. Every packet CPU-trapped, CLA forward never engaged.

**STEP 3/4 — THE FLIP (`echo "all 1" > pktdeal`, indirect spaRegTable write, NOT raw poke):**
readback confirmed port2 RAM updated to 0x55555555 (deal=1) for protos 0x00..0x3f.
Re-ran identical 400-pkt flow → **acl_required 0→0 (STILL FLAT), cla_tx_fwd 0→0 (STILL FLAT),
cla_tx_trp +404, hw_trap +404 — IDENTICAL to control.** pipeline_stats during the flow: smac2 RX climbing,
uni2 SDET active, **QMG UP hw_fwd=0 hw_trap=1884, CLA fwd[0x1cc3c0]=0 drop=0 copy=0** (forward engine
consulted NOTHING even with deal=1).

**VERDICT: SPA pktdeal=1 is NOT the gate.** Flipping the per-inport disposition from deal=0→deal=1 does
not submit the routed packet to the CLA forward classify; acl_required never lifts off 0. This REFUTES
the "deal=0 L2-bypass is the gate" hypothesis and REINFORCES the prior FACT A: the packet is never
submitted to ACL/forward regardless of pktdeal. The gate is elsewhere (upstream l3_en / SDET submit
decision, or a routing-context register raw DSA never provisions — see hypothesis #1, claRegTable
0x1e-0x24 + mac_req_ctrl bit11). NOTE: live route for 192.168.9.0/24 was on **lan1**, not lan4 this boot,
and 192.168.9.50 had no ARP responder (enx6c70 down) — one-way ingress stream, which is sufficient to
exercise port2 classify (smac2 RX confirmed). Writes were RAM-only; `pktdeal stock` issued to restore
(reboot fully restores the ACK-fwd override).

## ★★★★★★ GATE PINNED + DRIVER FIX (2026-06-27, agent a2062a8c) — SPA enty_pktdeal_cfg: routed slot must be deal=1, mainline forces deal=0
**THE GATE = SPA `enty_pktdeal_cfg`** (the per-ingress-port classify disposition):
- `spa_set_enty_pktdeal_cfg(port, ptype, deal)` @decomp_all_tm.c:28133 → `tmOnuRegWrite(ptype+0x43, deal,
  sub=port, &spaRegTable)`. HW: **phys 0x921d4300 + port*0x14**, 2-bit field [1:0], 61 proto-slots
  (ptype 0..0x3c) × ingress port 0..7. Encoding (decomp_halt_baddata_band.c:82-90):
  **deal=0 FORWARD (→ L2/SBRG bridge, BYPASSES CLA forward); deal=1 TRAP (→ routes INTO CLA classify,
  where ram2 forward can win); deal=2 DROP; deal=3 copy+fwd.** ⇒ L3-routing offload needs **deal=1** for
  the routed flow's proto-slot. acl_required=0 + "CLA consulted NOTHING" (make-or-break) = the deal=0
  L2-bypass signature. RAW POKE of 0x921d4300 does NOT update the live classifier (decomp:2354) — must
  use the indirect spaRegTable CMD/DATA sequence (the driver's zx_pp_init path).
- **DRIVER DEFECTS (zx-eth-main.c):** (A) `zx_chip_tm_init_pro_action` @2362 (runs LAST) forces
  `zx_pktdeal_ack_fwd_slots[]={0x0c,0x0d,0x17,0x1f,0x22,0x24,0x25,0x26,0x2c,0x2d,0x2f,0x40,0x41,0x42,
  0x43,0x44,0x45}` to **deal=0** (a TCP-ACK-HW-forward L2 optimization) — knocking the routed L3 slot
  to L2-bypass. (B) slot-map bug (already flagged @2346): `zx_pp_pro_actions[]` writes the kotrace proto
  ENUM as the ptype-slot index, skipping stock's proto→ptype 71-case remap (`zte_api_pp_set_pro_action`,
  decomp_halt_baddata_band.c:101-120) → trap/fwd bits land on wrong slots.
- **FIX (at .port_enable/setup for routed LAN ports):** `spa_set_enty_pktdeal_cfg(port, ptype, 1)` for
  the TCP/UDP ptype-slot the routed L3 transit classifies into, via the indirect write; and don't let
  the ACK-fwd override knock it back to 0. Pin proto→ptype via the decomp switch (partial @113-116).
- **trap reason tables (from tm.ko .data relocs):** trapPktType @0x88a0 — **73(0x49)=ZX_TM_TRAP_OTHERS**
  (catch-all; and it was the STALE 0xe702e forward-desc value, not the trapped pkt). Neighbors:
  84=LOOK_UP_MISS, 81=L3_LOCAL, 85=CFG_BY_SOFTWARE, 90/91=TCP_CTRL_SYN/FIN. drop_reason @0x8aa0.
- **Correct trapped-pkt descriptors (read these, NOT stale 0xe702e):** SPA→SADM "desOut" fpga 0x7517b
  (l3_en bit120, action_rsn 87-93); ADM "desOut" 0xe5090; **CLA-ingress "desIn" 0xe30f8** (l3_en@68101,
  action_rsn@68097) + **CLA-egress "desOut" 0xe30e5** (l3_en@68001, Da_known/Outport) = the precise
  submit-vs-trap read.
- **DECISIVE TEST (device on mainline NOW, no reboot):** read live SPA pktdeal port2 (0x921d4328, 5 words,
  2-bit/slot) → is the test flow's TCP/UDP slot deal=0? If yes → flip to deal=1 via the indirect seq →
  run transit flow → watch acl_required(0x9238c3b8 hi16) + cla_tx_fwd(0x9238c3c0) + hw_trap. CLIMB = GATE
  FOUND. Also read CLA desIn 0xe30f8 of a trapped pkt for the real action/l3_en/reason.

---

## ★★★★★ GATE LOCALIZED (2026-06-27, agent a8117571) — the per-inport SUBMIT-vs-TRAP disposition (SPA-classify/SDET), confirmed by l3_en=0 on mainline
On-device stock-vs-mainline + descriptor probe:
- **L3 routing-context regs REFUTED:** claRegTable 0x1e/0x21=0x9238c120/124, 0x1f-0x24=0x9238c428/42c,
  config idx5=0x9238c080. ALL = 0x0 / mac_req_ctrl(bit11)=0 on BOTH stock and mainline — even on stock
  while it actively routes the live WAN (nbif1=10.44.66.222). So NOT the discriminator.
- **DESCRIPTOR PROBE (the key datum):** mainline trapped transit packet (172.31.9.50:40000→
  192.168.9.50:5201, smac2 RX +10303, hw_trap=10303, hw_fwd=0, CLA fwd=0 drop=0 = forward engine
  consulted NOTHING) → **l3_en=0**. Stock while forwarding → des 0x87 → **l3_en=1**. ⇒ mainline never
  reaches the forward-classify stage that evaluates l3_en/CLA-forward; port2 ingress takes the TRAP
  disposition. CONFIRMS the reframe: gate = the upstream SPA-classify/SDET per-inport submit-vs-trap.
- ⚠ CAVEAT: 0xe702e (phys 0x9239c0b8) is the FORWARD-path descriptor and stays STATIC during mainline
  transit (never written, since no submit). So its action_reason=73/drop=0 may be STALE (last-forwarded
  pkt), NOT the trapped packet's reason. The real trap reason is in the CPU-bound RX descriptor the
  driver receives (zx-eth-main.c RX path). NEXT: read the correct trapped-pkt descriptor + map the
  action_reason → trapPktType[] string; and find what sets the per-inport submit-vs-trap disposition
  (the SPA-classify/SDET reg) — that's the gate to flip. (Ties to [[zte-hw-forwarding-deadend]]: the
  driver is a trap-all DSA conduit; stock sets routed ports to submit-to-forward.)

---

## ★★★★ REFRAME (2026-06-27) — the gate is the ACL-SUBMIT / l3_en decision, UPSTREAM of the CLA; ram2-inport is DOWNSTREAM (dead lead)
Ground-truth attempt (agent a6f0d543) to capture stock's real ram2 entry for the live regport2 flow
came back: the entry's slot is in 0x40..0xff (slot=hash&0xff), not reachable in the bounded sweep —
BUT this no longer matters, because reconciling the two hard facts below shows the ram2-inport was a
DOWNSTREAM red herring:
- FACT A (make-or-break + 2 clean boots): mainline with the FULL install (ram2 5-tuple-exact + ram0[9]
  bit8 + boot rule slot8 + PM) → **acl_required FLAT at 0**, cla_tx_fwd=0, all trapped. pipeline_stats:
  packets reach SDET but the **CLA forward engine is consulted NOTHING** (fwd=drop=0); they take the
  per-inport TRAP disposition and are NEVER submitted to the ACL/forward classify.
- FACT B (stock cross-check): the SAME boot rule slot8 + ram0[9] bit8 → stock acl_required CLIMBS and
  the flow HW-forwards.
⇒ The ram2 entry (inport or 5-tuple or otherwise) is only consulted AFTER a packet is submitted to the
ACL/forward classify (acl_required++). On mainline acl_required never lifts off 0 → the packet is never
submitted → ram2 is never read → its inport is irrelevant. **The gate is the submit-to-ACL / `l3_en=1`
decision**, made UPSTREAM in SPA-classify/SDET (the per-inport disposition: TRAP vs submit-to-forward).
This IS the "L3" angle: l3_en=0 (L2-switch, unknown-unicast traps) vs l3_en=1 (L3-routable → submitted
to CLA ACL/forward). Stock arms l3_en=1 for the transit flow; mainline leaves it 0.

### DECOMP RE RESULT (agent a02457c4, 2026-06-27) — l3_en is HW-internal; gate is dynamic + the L3 routing-context regs
- **l3_en is NOT SW-writable.** Every appearance in the decomp is a descriptor READ/decode for display
  (spa_info_show @65725, adm_info_show @65908, PrintBrgDesc @66379/66474, pm_info_show @64080). No
  register pokes it. It is HW-computed in fixed-function parse/route from: (1) the "to-me" compare
  (DST-MAC vs ONU-MAC/SPA tables + DST-IP vs local_ipv4, gated by CLA config bit11 `mac_req_ctrl`),
  (2) parse flags (ip/tcp/udp, desc bits 135-139), (3) the **L3 default-flow routing context**
  (`cla_set_up_l3_default_flow_cfg @1608` = claRegTable idx 0x1e/0x1f/0x20 upstream; `_dn_ @1701` =
  0x21-0x24 incl `da_known`). ⇒ "find the l3_en write" REFUTED.
- **Static to-me inputs PROVEN identical stock↔mainline** (local_ipv4=0 both, ONU-MAC slots0-3 both,
  da_lookup_en=0xff both, mac_req=0 on stock) → ONU-MAC hypothesis (#1 below) REFUTED before testing.
- **NOT-YET-COMPARED (the new concrete leads):** the L3 default-flow cfg regs **claRegTable 0x1e-0x24**
  (`cla_set_up/dn_l3_default_flow_cfg`) + **CLA config bit11 `mac_req_ctrl`** (`cla_set_config @456` /
  `cla_set_mac_req_ctrl_config @564`, claRegTable idx 5). The agent flags these as the "upstream routing
  context set once by stock's Enrutamiento provisioning that raw L2 DSA lacks." TEST: read these on
  stock vs mainline; if mainline has them zero/unset → likely the gate (mainline never provisions a
  HW L3 routing interface).
- **Boot-rule contradiction RESOLVED:** the boot rule (ram1[0x98]) is the generic v4 *shape* (extract
  offsets 8..22) reused for ALL v4 flows; per-flow MATCH VALUES go to ram2. So stock arming slot 8 +
  ram2(flow) is correct/complete — confirming the CLA ram1/ram0/ram2 tables are NOT the difference.
- **THE DECISIVE READ (Q3, on-device, read-only):** the trapped packet at the CPU carries the OPC/PM→CPU
  descriptor, decoded by `pm_info_show "des" @64048` (fpga widx **0xe702e**, 7 words): **l3_en = word0
  bit7** (`:64080`); **action_reason (7-bit) = (w?&0x3f)<<1 | (w?>>31)** (`:64138`) → indexes
  `trapPktType[]` (the WHY-trapped string, read live); **drop_reason (3-bit)** at `:64132`. On a trapped
  mainline transit packet: l3_en==0 confirms upstream L3-recognition gate; action_rsn names the reason
  (distinguishes "unknown-unicast/no-route" [→ routing context] from a parse/framing issue).
- PM ram12 (ONU-MAC) layout for completeness: `pp_pm_set_onu_mac_ram_info @20316`, ram_id 0xc, 16
  entries per-SUBNET (not per-port); but it's NOT the gate (device MAC already present).

LEADING HYPOTHESES (re-ranked after the decomp RE):
1. **L3 default-flow routing context (claRegTable 0x1e-0x24) + mac_req_ctrl bit11 (idx5) unset on
   mainline** — the "Enrutamiento" HW routing-interface context raw DSA never provisions. TOP suspect.
2. **Packet framing at the parse stage** (DSA tag / header offset) altering the HW parse / to-me compare.
3. ~~ONU-MAC / destined-to-me (PM ram12)~~ — REFUTED (device MAC present, static inputs identical).
DECISIVE empirical probe: dump a TRAPPED transit packet's descriptor on mainline (fpga 0xe702e: l3_en
word0 bit7 + action_rsn) → names the trap reason → discriminates hypothesis 1 vs 2.

---


## ★★★ CRITICAL CAPTURE (2026-06-27) — per-flow ram1 rule REFUTED; boot rule suffices on stock
Captured live on stock while a UDP flow (192.168.1.50:50000→8.8.8.8:53) was HW-FORWARDING
(cla_tx_fwd 0→0x393): ram0[9] = 0x00150151 (bit 8 = slot 8 armed), and **ram1[0x98] (slot 8, the
armed slot) = the GENERIC BOOT RULE byte-for-byte** (`22038608 000058a1 0 0 f00ff000 ffffffff
ffffffff 0fffffff 0 0 0 0 0 0 00700000 00092492 0`). So stock forwards this flow with the GENERIC
boot rule — it does NOT write a per-flow ram1 window rule. **The "per-flow ram1 rule" hypothesis is
REFUTED.**
⇒ THE SHARP CONTRADICTION: stock forwards with {ram0[9] bit8 + boot rule slot8 + ram2 + PM}; mainline
TRAPS with the SAME config (the make-or-break/UDP tests). Identical ram0/ram1/PM, opposite result
(stock acl_required+cla_tx_fwd climb; mainline acl_required=0, all trapped). The difference is NOT
ram0/ram1/PM.
PRIME SUSPECT (concrete, testable): the **ram2 ENTRY's INPORT field / key does not match the mainline
ingress packet.** fill520 used byte0x10=0x49 (WAN-side default; keybuilder spec flagged the per-regport
inport packing as UNSOLVED). The mainline flow ingresses **regport2 (lan2 = jack3)**. If the rule
match/submit depends on the inport (extracted by the boot rule window, compared vs the ram2 value),
a wrong inport → no match → no submit → acl_required=0 → trap. NEXT: capture stock's REAL ram2 entry
(esp. byte0x10 inport) for a flow ingressing regport2, then on mainline write THAT entry (correct
inport) + boot rule + ram0 bit, and test. (Also possible: a packet byte-offset/framing diff so the
boot rule's full-frame offsets {8,12,14,16,18,20,22} don't align on mainline ingress — but the inport
is the leading suspect.) Stock logger ring is a replay buffer — read ONE indirect entry per cat-session
and take the LAST occurrence (worked here for ram1[0x98]).

---


## ★ ram1 rule-builder RE + KEY RECONCILIATION (2026-06-27) — re-test with UDP, not SYNs
Workflow `ram1-rule-builder-crack` decoded the CLA ram1 extra_rule_table architecture (PROVEN):
**ram1 holds only the extract SHAPE (winoffset[N]@bit7*N, winmask[N]@bit140+16*N, offtype[N]@bit
0x3c*8+3*N); the per-flow MATCH VALUES go to the ram2 windata buffer (param_3), slot fixed by
descriptor ARRAY INDEX N (N0→0x13,N1→0x15,...), NOT win_offset.** Boot rule (ram1[0x98]) decodes to
winoffsets {8,12,14,16,18,20,22}, winmask0=0xff/1..6=0xffff, ALL offset_type=2, hash_len=7. The
verifier REFUTED the synthesis's "just clone the boot rule" (the make-or-break already had boot rule +
ram2 + ram0 bit → trapped) AND flagged builder bugs (descriptor order misaligns windata; stock arms
TWO L4 windows/port at 0xc,0xe & 0x10,0x12 type=2, IP/proto type=0). So a from-scratch precise
replication of aclBuildExtRuleAndHashEntriesByParseCondition (tm.c:48424) is needed IF the per-flow
rule is genuinely required.

**BUT — KEY RECONCILIATION:** the make-or-break "FAIL" used hping3 -S (TCP SYNs), which NEVER reach
conntrack-ESTABLISHED → trapped BY DESIGN (`ffe_ip_conntrack_check`; stock traps SYNs too). And the
stock cross-check showed a **UDP single-tuple flow HW-forwarded with just the boot rule at slot 8 +
the ram0[9] bit** (no per-flow rule). So the make-or-break FAIL may be a SYN-methodology artifact, NOT
proof the install is incomplete. **DECISIVE pending test (agent a9ad18cf): mainline + full install
(ram2 UDP entry + ram0[9] bit + boot rule + PM) + a UDP flow (no establishment needed).** If it
HW-forwards → the install is ALREADY COMPLETE for UDP (the ram1 per-flow builder is moot; just wire
the driver + trigger). If it traps → the per-flow ram1 rule is genuinely required and the precise
builder RE is the job. (Note prior contradiction to resolve: UDP used slot 8 = the BOOT rule and
forwarded on stock, which argues the boot SHAPE suffices for at least UDP.)

---


## ★★★ MAINLINE-SIDE CONFIRMATION (2026-06-27, live RAM-boot, clean) — the ram1 window-RULE is the gate
Ran the FULL fast-path mirror install on a clean mainline boot and measured per-stage counters under a
sustained 400-pkt TCP flow (172.31.9.50→192.168.9.50:5201 sport40000, ingress lan1=MAC2/regport, routed
to lan4). Install was readback-VERIFIED coherent:
- CLA ram2[5] = forward entry, word3=0x80000000 VALID, 5-tuple key byte-matches the flow EXACTLY
  (decoded: proto@0x13=06, src@0x15=172.31.9.50, dst@0x19=192.168.9.50, sport@0x1d=40000, dport@0x1f=5201).
- CLA ram0[9] = `...00150151` → index_valid bit 8 IS SET (slot 8 = ram1 addr 0x98 = (9<<4)|8).
- CLA ram1[0x98] = the generic BOOT rule (window f00ff000/ffffffff/ffffffff/0fffffff); PM next-hop+fill OK.
RESULT (reproducible across 2 clean boots): cla_tx_fwd FLAT 0; acl_required hi16 FLAT; cla_tx_trp +400
(ALL trapped). pipeline_stats: smac2 good_uc=400 (arrive) → SDET_transport=192 (reach SDET) → **CLA
fwd[0x1cc3c0]=0 drop=0** (CLA forward engine consulted NOTHING) → QMG UP hw_trap=387 (trapped to CPU).
⇒ Packets take the per-inport TRAP disposition; they are NEVER submitted to the ACL/forward classify
(acl_required does not increment per-packet). The index_valid bit being set is NOT sufficient.

DISCRIMINATOR FOUND (the `pktdeal all 0` experiment): forcing SPA pktdeal to forward-all (deal=0) makes
the packets BYPASS the CLA entirely — they pass SMAC→SPA→SDET then VANISH before CLA/SADM (CLA fwd=drop=0,
SADM pass=drop=0, lan4 tx≈0); acl_required ticked once on the write, not per-packet. ⇒ The CLA hash-forward
engine is on the TRAP datapath only; pktdeal=trap routes packets INTO the CLA, pktdeal=forward routes them
down the L2/SBRG-bridge path that never reaches the CLA. So the CLA forward entry can only win if the packet
is (a) routed into the CLA (pktdeal=trap, the default) AND (b) the per-flow ram1 window-RULE actually
MATCHES so classify SUBMITS it to the forward stage (acl_required++) and the ram2 forward action overrides
the trap.

REMAINING UNSOLVED (the whole job now): the per-flow ram1 extra_rule_table WINDOW-MATCHER format. The boot
rule at slot 8 does NOT match an arbitrary transit 5-tuple, so the flow is never submitted to ACL. Stock's
slow path builds a fresh ram1 rule (aclBuildExtRuleAndHashEntriesByParseCondition tm.c:48424) whose window
matches the specific flow, at a freshly-allocated slot, then sets THAT slot's index_valid bit. Pinning the
17-word match/mask layout (winoffset/winmask0..19) for a given 5-tuple REQUIRES the stock differential
capture (bulk-TCP vs control event; see the capture experiment design). This is the last gate; ram2+ram0+PM
are all confirmed correct/sufficient-but-inert without the matching ram1 rule.

## ★★★ CONFIRMED EMPIRICALLY on stock (2026-06-24 cross-check)
Read CLA ram0[0x00..0x0f] before/after a fresh single-tuple UDP flow install (192.168.1.50:51000→
8.8.8.8:53). The install happened (cla_tx_fwd 0→0x4f, acl_required hi16 0x79→0x128). **ONLY index_id=9
changed**: 5 words BEFORE `93929190 97969594 9b9a9998 9f9e9d9c 00150051` → AFTER `...00150151`. The u16
index_valid at byte +0x10 (= word4 low16): **0x0051 → 0x0151, diff 0x0100 = (1<<8) → slot 8**. No other
ram0 entry changed; the fixed per-port arms (idx1-5=0x0355, idx6-7=0x0055, idx8=0x0755, idx0xa=0x0004)
were untouched. ⇒ **the per-flow forward-arm = RMW CLA ram0[9] index_valid |= (1<<slot)**, the exact
write mainline's offload install is missing (mainline ram0[9]=0x00150051, bit-8 clear).
EXACT replication: ram0 index_id=9, set word4 = 0x00150051 | (1<<(16+? )) ... i.e. low16 0x0051→0x0151
for slot 8 (preserve the high bits 0x0015). Order: ram2 + ram1 per-flow rule FIRST, then the ram0 bit.
CAVEATS (don't block the verdict): ram2 exact addresses + the ram1 per-flow rule words were NOT pinned
(the /dev/logger_main ring buffer re-streams history, defeating per-address mapping) — the ram1 rule
slot/content still needs a non-ring read method or a copy of the v4 boot rule (0x90/0x98). Device left
RED-wedged on the mgmt path (bulk flow tripped the LAN-unicast→CPU latch) — needs a clean boot.
Captured ram2 entry contents during the flow (6-word reads, valid marker word2=0x80000408): e.g.
`01005055 00154000 80000408 90001417 00000045 000000e0` (addresses not pinned).

---


From workflow `ffe-forward-arm-re`. Explains why the full ram2+PM install left mainline trapping
(acl_required=0): we replicate the FAST path (ram2 + PM), but stock at RUNTIME uses the SLOW path,
which ALSO arms a per-flow bit in CLA ram0 + a per-flow rule in CLA ram1 that ram2 needs to be live.

## Core hypothesis (verifier: plausibly-upstream=true, already-refuted=false; confidence high)
- **Stock runtime uses the SLOW path, not the fast path we mirror.** PROVEN: `tm_sdk_init` forces
  `g_fast_opti=0` whenever `lan_up==1` (tm.c:54813-54814) and g_fast_opti is never set to 1, so
  `tm_add_acl_flow_rule` (tm.c:54280) dispatches to `addAclRule` (slow) → `aclBuildHashAndAclRule`,
  NOT `tm_acl_fast_add`.
- The slow path, after `cla_set_hash_table` (CLA ram2), does TWO writes we DON'T:
  1. **CLA ram0 (extra_index_table, per-port) RMW: `*(u16*)(entry+0x10) |= (1<<rule_slot)`** — the
     **index_valid bit** for the allocated rule slot (slot 0..15). `cla_set_extra_index_table(index_id,
     entry)` (set fn tm.c:2652; RMW at tm.c:53663/53695/53774).
  2. **CLA ram1 (extra_rule_table): a per-flow window-matcher RULE** at a freshly-allocated slot
     `rule_addr = (port_rule_base<<4)|slot` — NOT the fixed boot rule 0x90/0x98.
     `cla_set_extra_rule_table` (set fn tm.c:2872; callsites 53655/53690/53769); built by
     `aclBuildExtRuleAndHashEntriesByParseCondition` (tm.c:48424).
- The classify stage only SUBMITS a flow to the ACL/forward stage (acl_required++) for rule slots
  whose index_valid bit is set → **ram2 alone is inert without the 1<<slot arm** → exactly why
  brute-filling ram2 at all 520 buckets lifted nothing.
- index_id (which ram0 entry) = `DAT_0007acfd[port*2]` (per-port, `aclGetExtIdxRuleRamAddrByPort`
  tm.c:50139/50166), OR fixed 9 (v4-fast)/10 (v6-fast). index_id < 0x10. Note EN_V4FAST_EXTIDXTBL
  (tm.c:49719) ALSO RMWs the same ram0 +0x10 ushort but with FIXED class bits once-per-port (fast
  path) — distinct from the slow path's dynamic 1<<slot per rule.

## VERIFIER SOFT SPOT (the one thing to confirm)
The WRITE side (slow path sets 1<<slot) is proven; the GATING role (classify submits to forward ONLY
for slots with index_valid set) is structural INFERENCE, not a decompiled classify-submit line. The
decisive confirmation is the stock before/after read below.

## DECISIVE confirmation (stock, read-only) — DO THIS FIRST
On stock (modem-WAN rig, LAN client): read CLA ram0[index_id] (the per-port extra_index_table entry),
note the u16 index_valid at byte +0x10. Start a FRESH 5-tuple TCP flow (send ≥2 packets so the FFE
installs; confirm via cla_tx_fwd climbing). Re-read CLA ram0[index_id]. **EXPECT a new index_valid bit
(1<<slot) set post-install that was 0 before.** Stock CLA ram0 read via fpga: `fpga -w 0xe3005
<0x8000000|index_id>` (rw=1, ram0, addr=index_id); `fpga -r 0xe3007 5`. Try index_id ∈ {per-port from
the table, 9, 10}. Also capture the allocated ram1 rule + the ram2 slot for the flow. This proves the
arm AND gives the exact index_id/slot/bit + ram1 rule to replicate on mainline.

## Mainline replication (after confirmation)
Install full ram2 + PM (as before) + (a) write the per-flow ram1 window-matcher rule at a free slot S
(clawrite ram_id=1), (b) RMW CLA ram0[index_id] index_valid |= (1<<S) (clapeek ram0 to read, clawrite
ram_id=0 to write back). Order: ram2 + ram1 rule BEFORE the ram0 index_valid bit. Then run the matching
flow, watch acl_required (0x9238c3b8 hi16) + cla_tx_fwd (0x9238c3c0). SUCCESS = they climb, cla_tx_trp
stops. Driver impl: add the ram0 index_valid RMW + ram1 per-flow rule to the offload install (the
driver's zx_ffe_arm only writes the FIXED boot rule 0x90/0x98 + the once-per-port index, NOT the
per-flow slot arm).
