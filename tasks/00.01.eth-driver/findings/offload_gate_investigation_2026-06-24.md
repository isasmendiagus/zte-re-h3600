# HW offload gate — investigation 2026-06-24 (rig rebuild → slot-sweep → architectural reframe)

Continues the Phase 6 HW L3-offload work. Goal: a routed transit flow LAN→WAN must be
HW-forwarded (offloaded), not trapped to the CPU. This session rebuilt the rig, ran the
slot-sweep live with the corrected key-builder, and — via two rigorous negative experiments —
reframed the blocker from "a missing classify/CLA register" to "a missing L3-routing context".

## Rig (working, reproducible)
- Mainline booted from RAM via TFTP. Boot port = MAC2 = LAN3 = JACK3 (the 3rd LAN RJ45);
  192.168.1.50 on the host NIC there. See `tftp_boot_rig_troubleshooting_2026-06-24.md`
  (AX88179B software-config-flip wedge + `authorized`-toggle recovery; lazy-PHY tftp race fixes).
- LAN side: enxc8a362 (JACK3) → DSA `lan1`, netns SRC 172.31.9.50, static ARP for gateway
  172.31.9.1 → device MAC f4:f6:47:0f:42:64 (bypasses the broken CPU→LAN egress so SRC can send).
- WAN side: enx6c70 (RGMII jack) → DSA `lan4` — host link did NOT come up (device lan4
  carrier=1 but host "Link detected: no"); NOT needed for the gate test (trap happens at ingress).
- Counters (phys): acl_required = 0x9238c3b8 **hi16**; cla_tx_fwd = 0x9238c3c0; cla_tx_trp = 0x9238c3c4.
  hw_trap = 0x9234c060. Read via REPL `memdump <phys> 4`; flow via `hping3 -S` from netns SRC.

## Experiment 1 — slot-sweep (corrected key-builder), live
`scratchpad/sweep_lan2wan.py`. Flow 172.31.9.50:40000→192.168.9.50:5201 TCP, ingress lan1.
Built the 12-word CLA hash key + 15-word ram2 forward entry with the **verified** builder
(`scripts/hw_slot_sweep.py`; its `ip_shorts` packing matches the workflow-verified spec — see
`tasks/00.10.02.re-stock-kmods/findings/phase6_cla_keybuilder_SPEC.md`). Wrote the entry at all 6
candidate buckets (inport 0..5, slot = raw_hash & 0xff). The 6 buckets were EMPTY before (nothing
clobbered). **Result: NO forward** — matched-flow trap delta 48, control 60; both trapped.
Diagnostic: **acl_required = 0**, cla_tx_fwd = 0, cla_tx_trp +81. ⇒ the packet never reaches the
CLA hash, so ram2 content is moot. Gate is UPSTREAM of the hash.

## Experiment 2 — combined SPA classify + ram2 (closes the 2026-06-05 measurement gap)
`scratchpad/combined_test.py`. The 2026-06-05 test loaded SPA classify (matchram+hashram) and saw
cla_fwd=0 but **never measured acl_required**. This session loaded the same classify (matchram
banks 0/1/2 readback-verified exact + 8 hashram slots, via the SPA indirect iface cmd 0x921d4014 /
data 0x921d401c+N*4 / status 0x921d4018) **AND** wrote the ram2 forward entry **AND** measured
acl_required, all on one boot. **Result: acl_required STAYED 0** (cla_tx_fwd=0, cla_tx_trp +80).
⇒ classify + ram2 TOGETHER do not open the ACL path. The "both static conditions" hypothesis is
refuted with acl_required explicitly measured.

## Refuted-candidate list (static-config approach EXHAUSTED)
On mainline, every static candidate produces the same result (traps 100%, acl_required=0,
cla_tx_fwd=0): CLA config 0x9238c080 (==stock 0x600); SPA pktdeal; SPA classify matchram+hashram
(loaded+readback-verified, even with a ram2 entry, acl_required still 0); outspace/MTU; match_mode
(npp 0x1407c, already on); ram2 written at all 520 buckets; DPA analyze-enable (untestable via the
generic `poke` — DPA 0x92398xxx is outside the driver's mapped window 0x92000000-0x921bffff; aly_en
already 0x43). The `ingress-acl-gate-re` workflow's recipe (re-loading SPA classify) was REFUTED by
its own adversarial verifier (high conf) as re-treading the 2026-06-05 result.

## On STOCK (for contrast)
A routed LAN→WAN flow forwards at line rate: acl_required CLIMBS then cla_tx_fwd CLIMBS (per the
2026-06-06 live stock comparison). So the CLA path IS the stock forward mechanism (not SBRAG), and
acl_required-climbing is the signature of entering it. Stock forwarding REQUIRES the web-UI
"Enrutamiento" provisioning (creates nbif2 + default route); a manual ifconfig does NOT forward.

## Architectural reframe (the current lead)
`acl_required` = packets SUBMITTED to the ACL for an **L3 fast-forward decision**. A packet is only
submitted if the HW recognizes it as **L3-routed transit** (off-subnet, TTL-decrement) — which
requires an **L3 ROUTING INTERFACE CONTEXT** in the HW. Stock creates this during routing-mode
provisioning (per-interface/per-VLAN L3-route-enable, a HW routing/RIF/next-hop binding). Mainline's
raw DSA **L2** ports + Linux ip_forward create NO HW L3 context, so transit unicast defaults to
L2-trap → acl_required never climbs. This explains why every static L2/CLA-classify candidate was
refuted: **the missing gate is the absence of L3-routing-context setup, not a classify bit.** It also
reconciles the CLA-vs-SBRAG question: CLA+PM IS the forward table, but it's only CONSULTED for packets
the L3-route context flags as routable.

## Next steps (deliberate phase — UI-driven runtime capture)
1. Workflow `l3-route-context-arch` (running, task wd6kpdayi) — map the stock L3 forward path from the
   decomp, pinpoint the L3-route-context arm + which registers/tables hold it.
2. Reboot to stock; use Chrome MCP on the web UI (192.168.1.1) → set WAN to **Enrutamiento** — this
   ARMS the L3-routing context deterministically.
3. Capture the HW state the workflow flagged (stock-routing-provisioned) and **diff vs mainline** →
   the exact L3-route-context writes to replicate in the driver. The UI makes the trigger repeatable
   (vs guessing the writes from the decomp).
4. (Deferred) Bake the SPA classify load into the driver (`zx_pm_spa_init` / a `zx_spa_classify_init`)
   — a legitimate init gap (stock loads it, mainline doesn't), though alone it does NOT open the gate.

## ★ BREAKTHROUGH model — the `l3_en` descriptor fork (workflow `l3-route-context-arch`)
The gate is a per-packet descriptor bit **`l3_en`**, PROVEN as a real field born in SPA classify
and propagated downstream (dumped by name: SPA spa_info_show bit120 tm.c:65725; ADM bit102 :65908;
bridge PrintBrgDesc bit119/114 :66379/66474; CLA des bit7 word0 :64080).
- `l3_en=0` → L2-switch → unknown unicast traps (= the mainline default, the observed 100% trap).
- `l3_en=1` → L3-routing candidate → submitted to CLA ACL → `acl_required` climbs → then ram2 hash
  → `cla_tx_fwd`. **This explains why EVERY refuted candidate failed: they're all downstream of
  `l3_en`.** Writing ram2 by hand can't move acl_required because an `l3_en=0` packet is never
  submitted to the ACL. TWO mainline gaps: (1) `l3_en` never armed → acl_required=0; (2) no FFE
  per-flow learn-install engine → cla_tx_fwd=0 even past gate 1.
- Layer 2 (the cla_tx_fwd half) = stock's FFE conntrack engine in switch.ko: `ffe_receive_skb`/
  `ffe_learn_skb` → `hf_set_l3_entry` → `zte_api_fast_l3_session_add` → `tm_add_acl_flow_rule`
  installs CLA ram2 + PM next-hop + flow_info at flow-learn (runtime, NOT a provisioning ioctl).

### What arms `l3_en` — live tests this session (NARROWED, not yet cracked)
The workflow's lead (SPA ONU-MAC DA-matcher → l3_en) was tested live and is INFERRED-only (verifier
flagged: the only PROVEN DA-lookup machinery is in the **SBRG** block, not SPA classify):
- SPA ONU-MAC table (0x921d4120+N*8 lo / 0x921d4124+N*8 hi): **slots 0-3 ALREADY populated** with the
  4 device MACs (slot0 = f4:f6:47:0f:42:64 = the exact gateway MAC the transit frame is L2-addressed
  to). So the ONU-MAC table is NOT the missing piece — the MAC match is already satisfiable, yet
  acl_required=0. ⇒ ONU-MAC DA-match alone does NOT arm l3_en.
- CLA `local_ipv4` (0x9238c09c) was **0** (never written by mainline init). Writable via poke
  (confirmed). Set it to 172.31.9.1 then 192.168.9.1 — **acl_required STILL 0** (both), cla_tx_trp+80.
  So local_ipv4 alone (even + classify + ram2 + ONU-MAC) does not arm l3_en either.
- CLA config 0x9238c080=0x600, bit11(mac_req)=0, bit17(trap_acl)=0 (unchanged).
- POKE RANGE NOTE: CLA region (0x9238cxxx) AND SPA region (0x921d4xxx) ARE pokeable via the generic
  `poke` helper; DPA (0x92398xxx) is NOT (outside the 0x92000000-0x921bffff main map).

### Next suspect + why stock-capture, not more poking
Per the verifier's mandated fallback: `l3_en` is likely armed by the **SBRG per-port L3 config** —
the bridge block has MANY per-port enables (sbrg_set_pt_transfer_en :4651, smac_look_en :5582,
smac_lookfail_pktdeal :5677, learn_mode :5770, and a da_lookup_en the verifier cited ~tm.c:6226).
Guessing these one-by-one via poke is more haystack. **The decisive move is the STOCK CAPTURE the user
endorsed:** reboot to stock, drive the web UI (Chrome MCP) → WAN = Enrutamiento (arms the routing
context deterministically), then dump the SBRG/SPA/CLA per-port L3 config (incl. the SBRG pt_* enables,
ONU-MAC, local_ipv4, the descriptor `l3_en` path) and **diff vs mainline** → the exact missing writes.

## Stock UI recon + active-forwarding-capture attempt (2026-06-24)
Rebooted to stock, drove the web UI via Chrome MCP (admin/a3.141592A). Findings:
- **capWAN is ALREADY provisioned in routing mode** (a prior session persisted it in NAND): Tipo=
  **Enrutamiento** (options: Enrutamiento / Conexión puente), service INTERNET, link-type IP, IPv4
  Static, **IP 10.9.9.2 / mask 255.255.255.0 / gateway 10.9.9.1**, DNS 10.9.9.1, **VLAN Desactivado**.
  So the HW L3 routing context is armed on this stock boot. Conceptual model = "routing WAN
  connection + static IP + service binding, no VLAN". (WanConnection = the real DIGI PPPoE — DO NOT
  delete.) Submenus seen: Estado, WAN, QoS, Seguridad, Control parental, DDNS, SNTP, Enlace de puerto
  (port binding), Multicast.
- Stock Ethernet "Estado": WAN interface **Activo 1000M** (MAC f4:f6:47:0f:42:64).
- **acl_required (fpga 0xe30ee hi16) = 437 (0x1b5) on stock, cla_tx_fwd (0xe30f0) = 0.** Sending a
  routed transit flow 192.168.1.50→10.9.9.1 did NOT increment acl_required (stayed 437) — because the
  WAN egress fails (see below), so the packets are NOT actually forwarded. ⇒ acl_required climbs only
  for SUCCESSFULLY forwarded flows; the 437 is cumulative/stale. cla_tx_fwd=0 confirms no live forward.
- **BLOCKER: WAN-side host link.** enx6c70 (r8152) on the WAN/RGMII jack shows `Link detected: no`
  (carrier down) on BOTH stock and mainline, even after re-up. Stock ROUTED our test packet (replied
  "From 10.9.9.2 Destination Host Unreachable" = routing engine processed it, then failed ARP to the
  WAN gateway 10.9.9.1 because enx6c70 isn't linked). So the routing PATH is active on stock; the only
  failure is the WAN host NIC link. The r8152 does NOT negotiate on the RGMII/ZX5201 jack; historically
  (memory) the WAN host that worked was **enxc8a362 (AX88179B), at 341 Mbit/s**.

## ⇒ The decisive remaining experiment is BLOCKED on the WAN NIC
To capture stock ACTIVELY FORWARDING (acl_required climbing + the FFE-installed CLA ram2/PM for a live
5-tuple — the dynamic arm to replicate), we need ONE successfully-forwarded flow on stock, which needs
a working WAN-side link. The r8152 won't link on RGMII. **UNBLOCK = swap the AX88179B (USB-C, the
reliable RGMII NIC) onto the WAN jack, and put the r8152 on a GePHY LAN jack (JACK3) for the LAN
client + UI access.** (Physical recable; AX in cdc_ncm linked on WAN historically — verify mode.)
Until then the active-forwarding capture cannot proceed; the static-config approach is exhausted.

## ★★★ STOCK HW-FORWARDING CONFIRMED LIVE (2026-06-24, modem-as-WAN rig)
Connected the user's real modem (10.44.66.250, /24) to the ZTE WAN/RGMII jack — a RELIABLE
link partner (vs the dead host NICs). Reconfigured capWAN via the web UI: static IP 10.44.66.222 /
gw 10.44.66.250 / DNS 8.8.8.8 (kept Enrutamiento, INTERNET, no VLAN). Result:
- ZTE WAN (nbif1) ARP-resolves the modem (cc:29:bd:22:b4:2b); gateway reachable at L2.
- **A LAN client (enxc8a362=192.168.1.50, route 8.8.8.8 via 192.168.1.1) reaches the internet
  THROUGH the ZTE: ping 8.8.8.8 = 3/3, 0% loss.** The forwarding rig WORKS.
- A SHORT flow (≤300 pkts) is SOFTWARE-routed (acl_required delta 0) — the FFE doesn't engage.
- A SUSTAINED flood (UDP/ICMP, ~14s) → **acl_required climbs hard (hi16 0x2e6e→0xbb70) AND
  cla_tx_fwd (e30f0) = 0xa3ee (41966) — NON-ZERO. The FFE installed a HW session and is
  HW-FORWARDING.** This is the first time we've directly observed stock HW-forward a live flow.
- Confirms the model end-to-end: the gate (acl_required) + HW-forward (cla_tx_fwd) are armed
  DYNAMICALLY by the FFE per-flow install once a flow MATURES (sustained / conntrack-established).
  Short flows are CPU/software-routed; matured flows get the FFE HW fast-path.
- NIC-contention gotcha: the flood saturates enxc8a362, which ALSO carries the SSH to the ZTE —
  SSH reads starve during a --flood. Use a LOW-RATE sustained flow to read counters/RAM concurrently,
  or read right after (conntrack/FFE entries persist ~30s).

## NEXT: capture the FFE-installed state (the dynamic arm to replicate)
With a live HW-forwarding flow, read the FFE-installed CLA ram2 hash entry + PM ram1 next-hop +
PM ram0 flow_info for the live 5-tuple (192.168.1.50→8.8.8.8 NAT'd via 10.44.66.222), and whatever
arms acl_required/l3_en. This (a) validates our cracked key-builder against a real stock-installed
entry, and (b) reveals the full per-flow install to replicate in the mainline driver's offload hook
(the missing piece — manual ram2 write alone didn't move acl_required). Use a low-rate sustained
flow to keep the FFE entry alive while reading via SSH/fpga.

## Artifacts
- scripts: `scripts/hw_slot_sweep.py` (builder, verified), `scratchpad/sweep_lan2wan.py`,
  `scratchpad/combined_test.py`, `scratchpad/find_boot_jack.py`.
- spec: `tasks/00.10.02.re-stock-kmods/findings/phase6_cla_keybuilder_SPEC.md` (corrected key-builder).
- rig: `tftp_boot_rig_troubleshooting_2026-06-24.md`.
