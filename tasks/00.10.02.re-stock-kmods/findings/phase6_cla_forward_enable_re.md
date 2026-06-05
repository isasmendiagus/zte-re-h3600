# Phase 6 — CLA forward-enable RE (the last switch from trap-all → hash-forward)

## Question
With the FFE extract tables (ram0/ram1) ported + running at boot and the per-flow ram2 entry written,
a routed flow STILL traps 100% and `CLA fwd[0x9238c3c0]=0` — the CLA never makes a forward decision.
What enables the CLA forward/hash-consult path?

## RE (subagent, static decomp) — where the CLA global config is set
- The FFE-init caller `aclRamInit.part.6` (tm.c:54670, calls the inits under `if (g_fast_opti)`) writes
  NO CLA mode/enable register. `cla_set_trap_acl_en_config` is never called. So the enable is NOT in
  the FFE-init path.
- The real CLA global init is `tm_pon_pp_cla_initial` (tm.c:42727), writing 5 config regs; mainline
  replicates only 2. The 3 mainline never wrote: outspace cfg (0x9238c094), l3/up/dn MTU-length
  (0x9238c088 / 0x9238c098). Prime suspect: **outspace 0x9238c094 = 0x8** (ACL_OUT_HASH_NUM/SPACE_SEL,
  the hash-out slot mapping).

## ★ ON-DEVICE TEST (interactive session) — both candidates REFUTED
Peeked the LIVE values (current FFE-init build) — they are NOT zero (the subagent's reset assumption
was wrong), but DO differ from stock:
| reg | phys | mainline (live) | stock | note |
|---|---|---|---|---|
| cla config     | 0x9238c080 | 0x00000600 | ~0xE00 | missing bit11 0x800; trap_acl_en(bit17)=0 (not trapping) |
| l3 mtu         | 0x9238c088 | 0x00007fff | 0x3fff | already large (not 0) |
| poly cfg       | 0x9238c090 | 0x00e400e4 | (matches) | validated earlier |
| outspace cfg   | 0x9238c094 | 0x00000004 | 0x8 | HASH_NUM 1 vs 2 — real diff |
| up/dn mtu      | 0x9238c098 | 0x7fff7fff | 0x3fff3fff | already large |
| oth_l3_action  | 0x9238c0cc | 0x00000000 | 0 | matches |

Tested by LIVE poke (ram2 entry already at all 256 buckets), then 80-SYN routed flow:
- poke outspace 0x9238c094 = 0x8 → **CLA fwd still 0**, flow traps (+93). REFUTED.
- poke config 0x9238c080 = 0xE00 (set bit 0x800) → **CLA fwd still 0**, flow traps (+93). REFUTED.

⇒ Neither the outspace cfg nor the config bit11 is the forward-gate. The CLA fwd counter is stubbornly
0 even with extract tables present, a matching entry at every bucket, and stock-matching config regs.
The trap-all is deeper than the obvious CLA config registers (consistent with the long deadend history,
which now holds EVEN WITH the extract chain present).

## Status of the subagent's code
`zx_cla_fast_forward_enable()` (zx-eth-main.c) writes outspace=0x8 + MTUs=0x3fff (stock parity, RMW,
conservative). KEPT for stock-config parity (and outspace=0x8 makes the slot mapping match stock, useful
for the eventual bucket computation), but it is NOT the forward-gate (HW-refuted above).

## NEXT RE TARGET (the definitive method)
Static decomp of CLA config regs is exhausted. The forward-gate must be found by **live stock kotrace /
register diff at the moment stock forwards a routed flow**: boot stock, provision capWAN (routing), run
a LAN→WAN flow that HW-forwards (CLA fwd climbs on stock), and capture the FULL CLA + SADM + SPA +
parser config region that differs from mainline — OR kotrace the stock ingress decision for a forwarded
packet. Candidates to focus the diff: the parser/ingress→fast-path SELECT (what routes a packet INTO
the CLA hash stage vs the trap path), the SADM forward routing (SADM drop counter 0x1c4208 was huge in
pipeline_stats), and any per-port "fast/acl forward" mode bit. The hash side + extract are done; this is
purely "what makes the CLA consult+forward vs trap."

## ★★★ UPDATE 2026-06-05 — STOCK CLA CONFIG == MAINLINE (the forward-gate is NOT a config register)
Booted stock and read the CLA config block live via fpga -r (the subagent's stock values were
static-decomp INFERENCES, never read from the device). Live stock (which FORWARDS) vs mainline (traps):
| reg (phys / fpga) | stock | mainline | match? |
|---|---|---|---|
| config 0x9238c080 / e3020 | 0x00000600 | 0x00000600 | SAME |
| l3 mtu 0x9238c088 / e3022 | 0x00007fff | 0x00007fff | SAME |
| poly  0x9238c090 / e3024 | 0x00e400e4 | 0x00e400e4 | SAME |
| outspace 0x9238c094 / e3025 | 0x00000004 | 0x00000004 | SAME |
| up/dn mtu 0x9238c098 / e3026 | 0x7fff7fff | 0x7fff7fff | SAME |
| oth_l3 0x9238c0cc / e3033 | 0x00000000 | 0x00000000 | SAME |
ALL SIX MATCH. The subagent's inferred stock values (config 0xE00, outspace 0x8, MTU 0x3fff) were
WRONG — live stock = mainline exactly. ⇒ the CLA config block is DEFINITIVELY NOT the forward-gate;
stock forwards and mainline traps with byte-identical CLA config. The subagent's zx_cla_fast_forward_
enable() set NON-stock values (outspace 0x8 ≠ stock 0x4, MTU 0x3fff ≠ stock 0x7fff) — REVERTED (removed
the function + call from zx-eth-main.c; FFE extract init kept).
### New direction (config diff exhausted)
Since every static CLA config reg matches, the stock-forwards-vs-mainline-traps difference is NOT a
static register — it is DYNAMIC: stock's FFE software installs the per-flow forwarding STATE (the ram2
hardfast entry + likely SBRAG L3 route + the correct entry ACTION) when a flow is learned; mainline
writes a ram2 entry but it apparently isn't a valid FORWARD entry (or needs a companion SBRAG/da_known
state). PRIME LEAD: decode the ram2 entry ACTION fields — our entry (copied from the stock fwd template
+ substituted 5-tuple) may actually be a TRAP entry, or be missing da_known/direct/act_val=forward.
That alone explains CLA fwd=0 with the entry written everywhere. (Subagent RE in progress on this.)
Secondary: confirm on stock whether CLA fwd[0x9238c3c0] climbs during a routed flow (CLA-hash path) or
stays 0 (then stock forwards routed flows via SBRAG, not the CLA hash — meaning we targeted the wrong
table for L3 routing).

## ★★★★ UPDATE 2026-06-05 — 520-SLOT TEST: gate is UPSTREAM of the hash consult (definitive)
Wrote the (verified-forward) ram2 entry at ALL 520 hash slots across EVERY bank
(ram2[0..0xff]+ram3[0..0x7f]+ram4[0..0x3f]+ram5[0..0x3f]+ram6[0..7]), restored outspace to stock 0x4,
sent the matched routed flow. RESULT: **CLA fwd[0x9238c3c0] delta = 0, hw_trap +80** — still 100% traps.
Combined with: (entry = valid forward, agent-decoded) + (CLA config block byte-identical to stock) +
(extract ram0/ram1 present + run at boot) + (now: entry at every possible bucket in every bank), the
ONLY remaining explanation is that **the CLA never CONSULTS the hash for this flow — an ingress stage
UPSTREAM of the hash lookup traps the packet first.** The entire CLA hash-forward path we built this
session (extract tables, hash engine, write protocol, key builder, per-flow entry) is correct but
NEVER REACHED.
### Where the upstream gate lives (next RE)
The packet path: MAC RX → SPA admit → ingress classify (extract-rule SELECT → ram1 → ram2 hash) → fwd.
CLA fwd=0 means the classify never reaches/acts-on the hash. Upstream candidates, in order:
1. **The ingress extract-rule SELECT** — what makes a packet USE extract-index 9 / a populated ram1
   rule on INGRESS (the HW front-end per-port/per-ptype → extract-index mapping), distinct from the
   ram0/ram1 TABLES (which are present). If mainline never configures the ingress→extract SELECT, the
   hash stage is skipped → trap. RE: how the HW picks the extract path per packet (parser/port config),
   not the API tables.
2. **SPA pktdeal** (0x921d4300, per-(port,ptype) trap/forward) — the #36 merged fix forced the
   forward-slot set to deal=0 for TCP ACKs (CPU-forward); for user→user HW-forward the routed flow's
   ptype may still be deal=trap, trapping BEFORE the CLA. Needs the indirect write
   (zx_spa_set_enty_pktdeal_cfg), not a direct poke.
3. The per-port routing / fast-forward mode set at capWAN/routing provisioning on stock.
DEFINITIVE METHOD (deferred earlier, now clearly needed): kotrace stock ingress for a HW-forwarded
routed flow to see which stage/register makes stock consult the hash + forward, vs mainline trapping —
the static config diff is exhausted (everything matches) so only the live forward path reveals the gate.

## UPDATE 2026-06-05 — stock forwarding confirmed live; CLA hash IS the mechanism (gate-upstream conclusion reinforced)
Booted stock, rebuilt the routing rig (LAN host 192.168.1.50 ↔ br0; WAN host 10.9.9.1 in netns ↔
nbif1=10.9.9.2 capWAN; default via 10.9.9.1, ip_forward=0). iperf3 LAN→WAN = **570 MB @ 318 Mbit/s**
with **ip_forward=0** → stock HW-forwards routed L3 (Linux SW routing is OFF; the HW does it). Combined
with this session's live kotrace (stock hardfast install goes through cla_set_hash_table → ram2), the
**CLA ram2 hash IS stock's L3-routing forward mechanism** — our approach targets the right table.
Could NOT read stock's CLA fwd counter during/after the flow: under FFE activity /dev/logger_main is
flooded (345 KB in 2 s) and the printk rate-limiter drops the fpga-read lines (reads only work at idle).
Not needed for the conclusion: mainline traps 100% (hw_trap reliable) with the full hash path present,
so the gate is upstream of the hash consult regardless.
NET: hash mechanism confirmed correct; gate is the ingress consult/select upstream of the CLA hash.
The remaining RE is a broad INGRESS-region diff stock-vs-mainline (SPA 0x921d4xxx, the ingress
classify/admit, transfer_en/da_lookup 0x92388xxx, the parser→extract SELECT) at idle (when stock reads
are reliable) — NOT the CLA config block (already proven identical). This is the focused next effort.

## UPDATE 2026-06-05 — SPA classify engine: ON but RULE RAMs EMPTY on mainline (current best lead)
Agent RE flagged the SPA classify/match engine (spa_set_match_mode + matchram + hashram, the hashram
`action` field = per-packet forward-vs-trap) as configured by stock's tm_pon_pp_initial but absent from
the mainline driver's flat replay (indirect-RAM loads a register dump can't capture). ON-DEVICE VERIFY
(mainline, poke — reliable; stock SPA range 0x75xxx is NOT readable via fpga -r, different access domain):
- match_mode 0x921d407c = **0x1** (engine ON — agent's "off" guess REFUTED; bootloader/other init sets it)
- reg_pkt_up 0x921d4000 = 0xffffffff, reg_pkt_dn 0x921d4040 = 0xffffffff (ptype enables ON)
- 0x921d4054 = 0x03ff05dc ; indirect status 0x921d4018 = 1 (idle)
- **SPA matchram slot0 (indirect ram_id=0) = all zero; hashram slot0 (ram_id=5) = all zero** → the SPA
  CLASSIFY RULE RAMs are EMPTY on mainline (read via cmd 0x921d4014 = addr|ram_id<<22|rw<<27, data
  0x921d401c). Stock loads them (spa_set_matchram from _LANCHOR1 0x160B + spa_set_hashram from
  DAT_0004eee4) — mainline never does.
HYPOTHESIS (best current lead): the SPA classify engine is enabled but rule-less on mainline, so it
emits no classify/forward action for L3-routed unicast → those flows trap, never reaching the CLA hash
(L2 still forwards via the separate SBRG DA-lookup path, which is why L2 works but L3-routed doesn't).
CAVEAT: like the prior agent candidates (CLA config, match_mode — all refuted on HW), this needs
port-and-test to confirm, not just decomp. NEXT: port the SPA matchram + hashram rule loading
(templates _LANCHOR1 + DAT_0004eee4 from stock spa init, via the SPA indirect iface 0x921d4014/401c),
then re-test the routed flow. If still traps, the gate is elsewhere (DPA protocol-analyze, or kotrace
the live stock forward decision — the SPA range being fpga-unreadable means a live stock diff needs the
indirect-read recipe or kotrace).
### Reads gotcha (for next session)
Stock fpga -r reads the CLA/NPP range (0xe3xxx) but NOT the SPA range (0x75xxx) — and /dev/logger_main
floods under any FFE activity (rate-limiter drops read lines). Mainline poke reads ANY reg reliably.

## ★★★ UPDATE 2026-06-05 — METHODOLOGY RE-FRAME (user lead "review old findings"): the test rig was FLAWED
Reviewing the OLD findings (hw_forwarding_offload.md Iter AB/AC): **HW L2 same-subnet forwarding ALREADY
WORKS on mainline** — UDP lan1<->lan3 ~300 Mbit/s both dirs, hw_fwd=450761 / hw_trap=143 / no wedge,
via the SBRG DA-lookup path; it REQUIRES the dest MAC be known (static ARP so DA-lookup HITS).
⇒ THE FORWARD PATH IS ENABLED on mainline today (refutes "CLA traps all").
CRITICAL FLAW in THIS session's tests: the L3-routed test flow was 192.168.9.50 -> 172.31.9.50, but
**NO host existed at 172.31.9.50 (lan1)**. With no dest host, the device routes lan4->lan1, ARPs for
172.31.9.50, gets NO reply, cannot resolve the dest MAC, and TRAPS every packet to the CPU (which also
can't ARP it) — REGARDLESS of any CLA-hash/forward gate. So hw_trap climbing was the unreachable-dest
ARP-trap, not proof the gate is missing. The stock test that DID forward (192.168.1.50->10.9.9.1) had a
REAL host at the dest.
⇒ THIS SESSION'S "6 refuted candidates" are INCONCLUSIVE for L3 — the flow could not forward under any
config because the destination was unreachable. The CLA hash work (engine/write/extract/entry) is still
valid + built; it was just tested against a broken rig.
### CORRECTED NEXT TEST (high-value, likely the real path)
Set up a proper 2-host L3-routed rig with a REACHABLE dest: real host on lan1 (e.g. 172.31.9.50) AND on
lan4 (192.168.9.50), static ARP/neigh on BOTH the host side AND seed the device FDB if needed, so the
device can resolve the egress dest MAC. Then run the routed flow:
 (a) BASELINE: does it HW-forward at all (hw_trap flat) once the dest is reachable + FDB populated? L2
     same-subnet already works; the L3-routed case may "just work" via the route + DA-lookup once the
     dest MAC is known — OR it traps until the FFE/CLA-hash entry is installed.
 (b) If it traps: install the CLA-hash fwd entry at the engine-computed slot (now that the dest is
     reachable) and re-check hw_trap — THIS is the real test of the CLA hash offload, which the broken
     rig prevented all session.
Also: seed the device's SBRG FDB with the dest MAC (debugfs fdbadd) so DA-lookup hits, mirroring the
working L2 rig (Iter AB used assisted-learning / static FDB).

## UPDATE 2026-06-05 — reachable-dest L3 rig test: routed transit NEITHER forwards NOR traps (drops)
Built the corrected rig: enx6c70 in netns L = 172.31.9.50/24 (lan1, ingress confirmed working — ICMP
to 172.31.9.1 climbed hw_trap +20), enx2c99 in netns W = 192.168.9.50/24 (lan4), device firewall
FLUSHED (iptables ACCEPT) + ip_forward=1 + static ARP both sides + device neigh seeded for both hosts
(172.31.9.50->lan1, 192.168.9.50->lan4). Ran UDP L->W (172.31.9.50 -> 192.168.9.50, routed lan1->lan4).
RESULT: hw_trap FLAT (not trapped), W rx delta = 0 (not forwarded), lan1 netdev rx flat. netns L tx
climbs (host IS sending). ⇒ the routed transit flow is DROPPED in the HW pipeline — it neither
HW-forwards, nor traps to the CPU, nor reaches W. (Contrast: ICMP TO the device IP on lan1 DOES trap
+ reach CPU; routed TRANSIT does not.)
NEW understanding (re-frames again): the L3-routed TRANSIT case (user-port -> user-port, different
subnets) is not "trap-all" and not "unreachable-dest-trap" — it's a silent DROP. Candidates: SPA
pktdeal=drop(2) for the transit ptype on lan1; a routing-miss HW drop; or the to-device-MAC transit
packet not being delivered to the CPU routing path on a user port. Also unverified: whether SW routing
(CPU-forward lan1->lan4) works AT ALL on mainline (the merged router may only have been exercised via
the conduit, not inter-user-port). NEXT (fresh session): (1) confirm whether the CPU even receives the
routed transit packet (tcpdump the conduit / check FORWARD counters) — if not, it's an HW drop pre-CPU;
(2) check the SPA pktdeal deal value for the transit ptype on lan1 (the #36 lever); (3) verify
inter-user-port SW routing works before chasing HW offload.

## ★★★★ UPDATE 2026-06-05 — VALID RIG at last: routed transit TRAPS + SW path also broken (DSA demux)
The earlier netns tests were INVALID (I had broken the USB NICs by juggling netns — the user caught it;
`ip netns del` returned the trapped NIC enx2c99 to the default ns, restoring it). Found that the
cdc_ncm NIC enxc8a362 is dead, but the two r8152 NICs work: enx2c99->lan1(LAN), enx6c70->lan4(WAN).
enx2c99 TOLERATES netns (carrier=1, tx works); enx6c70 does NOT (carrier drops in netns). So the VALID
rig = enx2c99 in netns SRC (172.31.9.50, lan1, tx confirmed) + enx6c70 in main ns (192.168.9.50, lan4).
CLEAN RESULT (300 UDP lan1->lan4, firewall flushed, ip_forward=1, neigh seeded both ways):
- hw_trap +300 (ALL trapped), dest enx6c70 rx +0.
- conduit sw rx +301 (packets REACH the CPU), but lan4 tx +0 (CPU does NOT forward out lan4).
- lan1 netdev rx flat (packets hit the conduit but are NOT demuxed to the lan1 user-port netdev).
- device route get 192.168.9.50 -> dev lan4 (correct), ip_forward=1.
TWO confirmed findings:
1. **No HW forward of the L3-routed flow** (traps 100%) — the genuine Phase 6 gap, now confirmed with a
   VALID rig (not a rig artifact). My earlier "6 refuted candidates" were on the invalid rig (no tx) and
   need re-testing.
2. **The CPU/SW inter-user-port routing is ALSO broken**: trapped packets reach the conduit (sw rx
   climbs) but Linux does not forward them out lan4 (lan4 tx=0). Likely a DSA RX-demux/tag issue —
   ingress-lan1 packets aren't presented on the lan1 netdev, so Linux routing (lan1->lan4) never fires.
   (The merged SW router may only route conduit<->user-port, not user-port<->user-port.)
### NEXT (valid rig available now)
(a) Re-test the CLA hash offload PROPERLY: with FFE extract loaded (this boot) + the ram2 fwd entry for
    THIS flow (172.31.9.50:sport->192.168.9.50:5201) at the engine-computed slot (or all 520 buckets),
    re-run + measure hw_trap. The earlier all-520 test was on the invalid (no-tx) rig.
(b) Separately debug the DSA RX demux (why ingress-lan1 traffic isn't on the lan1 netdev) — needed for
    the SW baseline + assisted offload. RIG GOTCHA: use enx2c99 (r8152) for netns; enx6c70 drops carrier
    in netns; enxc8a362 (cdc_ncm) is dead; never leave NICs in a netns (del returns them but down).
