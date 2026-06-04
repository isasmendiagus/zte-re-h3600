# FFE TCP-trap vs UDP-forward RE — the conntrack flow-learn gate (2026-06-04)

Goal: explain (with addresses + decomp) why **TCP traps to the CPU and wedges**
while **UDP HW-forwards** on the mainline DSA driver, confirm whether stock's
**FFE (Fast-Forward-Engine)** is the mechanism, and give the **minimal fix**.

Empirical baseline (from Iter AC, real HW): UDP lan3↔lan1 ~300 Mbit/s/dir, hw_trap
stays ~143, NO wedge. TCP collapses to ~6 Mbit/s within ~3s: the **reverse-dir TCP
ACKs (small len-66 IPv4) TRAP to the CPU**, hw_trap climbs to ~1057, the CPU-RX
trap path latches at ~1024 frames → TCP dies. The per-protocol SPA pktdeal layer
(0x921d4300, reg67[1:0]) is set to FORWARD (deal=0) for all slots by mainline, so
SPA is **not** trapping TCP — the trap originates upstream in the FFE path.

---

## TL;DR

- **CONFIRMED: it IS the FFE flow-learn path.** FFE is a netfilter-**conntrack-based**
  L3/L4 software flow cache that, on the *first* packets of a flow, **traps them to
  the CPU** (`ffe_receive_skb` → slow-path returns 1/2 = "punt to CPU stack"), learns
  the 5-tuple, and only then installs a HW "hardfast" forwarding entry so subsequent
  packets HW-forward. Mainline implements **none of FFE**, so every trapped packet
  stays trapped — for TCP this is continuous.
- **The precise TCP-vs-UDP asymmetry is conntrack state, not a CLA/SPA rule.** In
  `ffe_ip_conntrack_check` (vmlinux `c0452a7c`) the protocol byte is read and:
  - **UDP (0x11)** is accepted immediately → flow gets learned/bound → HW-forwards.
  - **TCP (0x06)** is accepted **only when the conntrack L4 state == 3 (ESTABLISHED)**
    (`if ((cVar2 == '\x06') && ((char)piVar8[0x3a] != '\x03')) goto LAB_c0452b90;` =
    free-skb + return-trap). Until the TCP handshake reaches ESTABLISHED *and stock's
    CPU installs the hardfast entry*, every TCP frame is punted to the CPU.
  On mainline there is no conntrack/FFE at all, so **TCP frames are punted to the CPU
  forever** → the CPU-RX trap path latches at ~1024 and TCP wedges. UDP "works" on
  mainline only because UDP HW-L2-forwards by default once the FDB has the dest MAC;
  TCP's reverse-dir ACKs are what the chip hands to the trap classifier and mainline
  has nothing to consume/install them.
- **Minimal fix (recommended): do NOT reimplement FFE.** Make TCP behave like UDP =
  plain L2 forward, by ensuring the chip never punts unicast TCP to the CPU on a
  configured/forwarding port. Concretely: confirm every protocol slot in
  `spa_set_enty_pktdeal_cfg` (HW 0x921d4300, reg67[1:0]) is deal=0 (already true), and
  **fix the real wedge: the CPU-RX trap-ring latch at ~1024** so the few trapped TCP
  control frames drain. The forwarding itself already works (UDP proves it). The
  alternative (port stock's `ffe_*` + `cla_set_hash_table` hardfast install) is far
  larger and unnecessary for L2 bridging. See "Minimal fix" below.

---

## 1. RX trap-decision logic (stock) — with addresses

### Call site (switch.ko `pdt_ethdrv_recv` @ 0x109c8, decomp_all_switch.c:531)
For a normal unicast LAN frame the RX handler calls the engine gate:
```
switch.c:629  iVar3 = ffe_receive_skb(param_1,3);
switch.c:630  if (iVar3 == 0) { return 0; }   // 0 ⇒ consumed/forwarded by engine, do NOT pass up
switch.c:645  netif_receive_skb_sk(...);       // nonzero ⇒ punt UP to the CPU IP stack
```
So **ffe_receive_skb()==0 ⇒ HW/engine forwards (CPU does nothing); !=0 ⇒ trap to CPU.**
In switch.ko `ffe_receive_skb`/`ffe_learn_skb` are **PLT import thunks** (switch.c:13325
/14063 decode as `halt_baddata()` — the whole 0x2c1xx–0x2c2xx band is imports). The
**real bodies live in vmlinux** (exported `__ksymtab_ffe_receive_skb` / `_ffe_learn_skb`).

### ffe_receive_skb @ vmlinux `c0473110`
```
if FFE-disabled flag (*(_DAT_c07f7630 + 0x134) != 0)  -> return 1   // trap
if (skb->flags & ~1 != 0) or (skb field +0x68 != 0)   -> return 1   // trap
else build a flow-key (proto-indexed via &DAT_c07f7638[proto]) and call
    ffe_receive_pkt_slow_path(&key, &skb->flags)        // = ffe_receive_skb body
```
`_DAT_c07f7630 + 0x134` is the **global FFE-disable flag**: `ffe_enable` (c044f940)
writes 0 there, `ffe_disable` (c044f878) writes 1 and tears down every flow. When
disabled, ffe_receive_skb unconditionally returns 1 (everything traps).

### ffe_receive_pkt_slow_path @ vmlinux `c044e0f0` (the body)
Walks the registered packet-layer parsers (`(**code*)(iVar3+4)` = per-proto parse),
then the registered proto handler (`+0x28` = search/apply-flow):
```
iVar3 = (handler->search_apply)(handler,key,parsebuf);
if (iVar3 == 0) return 0;        //  flow FOUND & applied -> HW-forward, consume
... _DAT_c07f7630[0xd]++ (miss counter)
if (iVar3 != 2) return iVar3;    //  e.g. 1 = trap/punt
// iVar3 == 2  -> "learnable miss": create flow & PUNT this packet to CPU:
iVar3 = (handler->learn_alloc)(handler,key,parsebuf);  // +0x2c
... links the new (unbound) flow onto the learn list, returns 2
```
Return **0 = forwarded by an installed flow**, **1/2 = punt to CPU** (2 also kicks
off learning). This is the gate that differs for TCP vs UDP — see §3.

### ffe_ip_conntrack_check @ vmlinux `c0452a7c` (the TCP/UDP discriminator)
This is where the IP-proto byte gates binding the skb to a conntrack/flow:
```
puVar4 = nf_ct_tuple(...);        // FUN_c032121c(...)
cVar2  = *(char*)(puVar4 + 1);    // the L4 protocol byte from the conntrack tuple
if (cVar2 == 0x11 || cVar2 == 0x06) {        // UDP (17) or TCP (6)
    if (cVar2 == 0x06 && (char)piVar8[0x3a] != 0x03)   // TCP not ESTABLISHED(=3)
        goto LAB_c0452b90;        // -> ffe_free_skb_flow(skb); return 1  == TRAP, no bind
}
else if (puVar4 != &DAT_c066e9d0)              // not the allowed "other" proto
    goto LAB_c0452b90;            //                                 == TRAP, no bind
... else: bind skb->_nfct to the flow's conntrack (uVar9+0x6c/+0x70), return 1
```
`piVar8[0x3a]` is the per-direction conntrack L4 state; **== 3 means TCP ESTABLISHED**
(consistent with `ffe_check_ct_status` @ c04533d4 which gates on the conntrack
`status & 0x200` / `+0x88` assured/seen-reply bits). **UDP binds with no state gate;
TCP binds only once ESTABLISHED.** Until then TCP keeps returning 1 = trap.

---

## 2. What TRIGGERS flow-learn (stock) — per new flow, on the TX/egress side

### ffe_learn_skb @ vmlinux `c04511f4`, called from TX
switch.ko `pdt_ethdrv_send` @ 0x11130 calls `ffe_learn_skb(skb,3)` on **every TX**
(switch.c:877). Body:
```
must be in softirq;  if (skb->flags & ~1 != 0):
    build flow-key (proto-indexed &DAT_c07f7638[proto]);
    iVar2 = nf_something(_DAT_c07f7630+200, 2, &key);   // FUN_c00316fc(...,2,..) (notifier/ct lookup)
    if (iVar2 == 0x8001 || ffe_learn_pkt(&key, skb->flags) != 0)
        (*skb->dev_release)(...);   // bind/refcount, learning done
```
So learn is **per-flow, both protocols**, triggered as packets *egress* — it pairs
the ingress-seen flow (from ffe_receive) with the egress dev to build a full path.

### ffe_learn_pkt @ vmlinux `c044e484` → installs into the SW flow cache
Parses, finds the matching proto handler, and calls the handler's **build/apply**
callback `(**code*)(handler+0x40)` which leads to `ffe_general_insert_flow`
(c044e8a0) — an RCU hash-list insert of the flow with its **match-action**
function pointer (`param_1[0xe]`). That action callback is the HW programmer
registered via `ffe_register_flow_match_action` (c044de30); for L3/NAT flows it is
the chain the task already mapped in switch.ko/tm.ko:
`sw_acl_l3_hardfast_session_add` (switch:1797) → `zte_api_fast_l3_session_add`
(tm:0x6558c) → `tm_add_acl_flow_rule` → `addFlowOperInfo` → **`cla_set_hash_table`**
(tm:0x15a14) i.e. the HW CLA hash entry. For pure-L2 bridged flows the action is the
lighter FDB/forward bind, not the L3 hardfast.

**Does it require a CPU callback to install?** Yes — the install is entirely
CPU-driven software: ffe_receive punts the packet (return 2) → ffe_thread / the
learn path runs on the CPU → ffe_learn_pkt → match-action callback → (for routed
flows) cla_set_hash_table. There is **no autonomous HW learn**; the CPU must run
the FFE code to install the entry. Mainline runs none of it.

---

## 3. WHY UDP forwards but TCP traps (decisive)

It is **(a) + (c) combined**, NOT (b):

- **NOT (b) a CLA/SPA ACL rule trapping TCP.** The SPA per-protocol pktdeal layer
  (`tm_port_protocol_pktdeal_set` @ tm.ko 0x37340 → `spa_set_enty_pktdeal_cfg` @
  0x2b1f4 → HW **0x921d4300 reg67[1:0]**, decomp_halt_baddata_band.c:164-232) is the
  only per-protocol trap knob, and mainline programs **deal=0 (forward)** for all 61
  slots. DATASHEET.md confirms 0x921d4300 reg67[1:0]=enty_pktdeal_cfg. So no protocol
  ACL is trapping TCP. (Refutes the "CLA rule" hypothesis.)

- **(a) TCP is stateful/conntrack-gated; UDP is not.** `ffe_ip_conntrack_check`
  (c0452a7c): UDP (0x11) binds and forwards immediately; TCP (0x06) is rejected
  (free + return-trap) until conntrack state == 3 (ESTABLISHED). So on *stock*, every
  TCP frame before the handshake completes traps to the CPU by design — that is the
  FFE "learn the new flow first" behavior. UDP skips the state gate.

- **(c) on MAINLINE the session never installs, so TCP traps forever.** Mainline has
  zero FFE/conntrack code; ffe_receive_skb-equivalent does not exist, nothing ever
  consumes/binds/installs the trapped TCP frames. The chip therefore keeps handing
  the reverse-dir TCP ACKs to the CPU-trap ring (Iter AC: 14× lan1→lan3 len-66 IPv4),
  which latches at ~1024 and wedges. UDP "works" because once the bridge FDB knows the
  destination MAC the chip HW-L2-forwards UDP without involving the FFE/trap path at
  all; TCP's small ACKs are precisely what the chip routes to the trap classifier.

**Bottom line:** stock relies on a CPU-resident conntrack flow engine to turn the
first (trapped) packets of a TCP flow into an installed HW session; mainline never
ported that engine, so TCP's CPU-trapped frames accumulate and the (separately
buggy) CPU-RX trap ring latches at ~1024 → wedge.

---

## 4. Minimal fix to make TCP HW-forward like UDP

Two options; **recommend (i)** — do not port FFE.

### (i) RECOMMENDED — keep plain L2 forwarding; stop punting unicast TCP, fix the latch
The driver's job is an L2 DSA bridge; UDP already proves HW L2 forwarding works both
directions with hw_trap flat. We do **not** need stock's L3 hardfast sessions. Steps:

1. **Confirm no protocol is set to trap.** All SPA pktdeal slots forward:
   live-dump HW **0x921d4300** (reg67, 2-bit fields) per port (regport remap 5↔0) —
   every slot should read deal=0. If any TCP-associated slot reads deal=1, write 0 via
   the mainline equivalent of `spa_set_enty_pktdeal_cfg(port, ptype, 0)` =
   `tmOnuRegWrite(ptype+0x43, 0, port, spaRegTable)`. (Per task context this is already
   0 in mainline — verify, don't assume.)

2. **Fix the real blocker — the CPU-RX trap-ring ~1024 latch** (the wedge), so the
   handful of TCP control/ACK frames that *do* trap (broadcast/ARP/initial SYN, ND,
   and any L2-miss) drain instead of freezing tm_rx_count + tm_irq. This is the
   `zx_tm_net_poll` / NAPI trap-ring release path in
   `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c` — already the subject of Iters
   T/U/V/Z (slot-release + NAPI-rearm tried; latch persists). The FFE finding says the
   *forwarding* is not the problem — **the trap-drain is**. Re-target the latch
   directly: the ~1024 == TM_RX_DESC_PER_Q boundary ⇒ the poll stops re-arming after
   exactly one ring wrap. Audit the head/tail wrap + the IRQ re-enable ordering after
   the first 1024-descriptor cycle (compare to stock `pon_tm_net_poll` in
   decomp_all_plat_zxylzb_9128S.c).  *This is the single most promising fix:* once the
   trap ring drains, the small fraction of TCP frames that trap no longer accumulate
   and TCP stops collapsing — matching UDP's behavior.

   Concretely the value/region to chase is the TM RX ring control around
   `tm_base+0x10064` (DN) / `+0x10054` (UP) kick/consume and the per-queue RX desc
   count; the latch is in the driver's wrap handling, not in a chip protocol rule.

### (ii) ALTERNATIVE — port the hardfast-session install (larger; not recommended)
If you instead want TCP to be HW-offloaded like stock: implement, on the CPU, the
flow-learn install for ESTABLISHED TCP flows:
`(on trapped TCP, once ESTABLISHED)` → build the 5-tuple → call the tm.ko HW
programmer chain `zte_api_fast_l3_session_add` (tm 0x6558c) → `tm_add_acl_flow_rule`
→ `addFlowOperInfo` → **`cla_set_hash_table(idx & 0x7fff, entry)`** (tm 0x15a14;
indirect CLA hash RAM, entry format partly mapped in Iter L / cla_ram_layout_re.md).
This requires standing up conntrack tracking + the CLA hash-entry encoder in the
mainline driver — large surface, and unnecessary for an L2 bridge. Use only if true
wire-speed routed/NAT offload (not just L2 forwarding) becomes a requirement.

---

## Addresses / registers index (for the next session)

| symbol | addr | what |
|---|---|---|
| ffe_receive_skb | vmlinux c0473110 | RX gate; 0=forward, !=0=trap; checks disable flag +0x134 |
| ffe_receive_skb_locked | vmlinux c04731e8 | softirq-wrapped variant |
| ffe_receive_pkt_slow_path | vmlinux c044e0f0 | body: search flow → 0 fwd / 1 trap / 2 learn+punt |
| ffe_ip_conntrack_check | vmlinux c0452a7c | **TCP(6) needs ct state==3; UDP(17) binds free** |
| ffe_learn_skb | vmlinux c04511f4 | TX-side learn trigger (every tx) |
| ffe_learn_pkt | vmlinux c044e484 | inserts SW flow + calls match-action HW programmer |
| ffe_general_insert_flow | vmlinux c044e8a0 | RCU hash-list flow insert (pure SW cache) |
| ffe_enable / ffe_disable | vmlinux c044f940 / c044f878 | clears/sets disable flag @ _DAT_c07f7630+0x134 |
| ffe_check_ct_status | vmlinux c04533d4 | conntrack assured/seen-reply gate (status&0x200, +0x88) |
| pdt_ethdrv_recv (call site) | switch.ko 0x109c8 (switch.c:629) | `ffe_receive_skb(skb,3)`; ==0 ⇒ consume |
| pdt_ethdrv_send (learn) | switch.ko 0x11130 (switch.c:877) | `ffe_learn_skb(skb,3)` |
| tm_port_protocol_pktdeal_set | tm.ko 0x37340 | per-proto pktdeal setter (band:164) |
| spa_set_enty_pktdeal_cfg | tm.ko 0x2b1f4 | writes 0x921d4300 reg67[1:0] (band:216) |
| HW enty_pktdeal_cfg | 0x921d4300 reg67[1:0] | 0=forward 1=trap per (port,proto-slot) — mainline=0 |
| cla_set_hash_table | tm.ko 0x15a14 | HW CLA hash install (option-ii target) |
| zte_api_fast_l3_session_add | tm.ko 0x6558c | hardfast L3 session add (option-ii target) |

## Honest confidence
- HIGH: FFE = conntrack-based SW flow cache; the proto discriminator is in
  ffe_ip_conntrack_check (c0452a7c) with the literal TCP==6 / state==3 / UDP==17
  checks (decompiled this session from vmlinux, not inferred).
- HIGH: SPA pktdeal is not trapping TCP (mainline deal=0; refutes the CLA-rule
  hypothesis).
- HIGH: mainline implements no FFE → trapped TCP never installs/forwards.
- MEDIUM: the *exact* register write that drains the ~1024 trap-ring latch is in the
  mainline poll wrap logic, not a chip protocol rule — direction is firm (UDP proves
  forwarding works; the wedge is a trap-drain bug), but the precise off-by-one in the
  ring wrap still needs the targeted audit in §4(i).2.

---

## CORRECTION + synthesis — 2026-06-04 (Iter AF, verified on HW)

Two updates to the claims above, from live testing this session:

1. **WRONG above: "mainline programs deal=0 (forward) for all 61 pktdeal slots."** It does
   NOT. `zx_chip_tm_init_pro_action` (zx-eth-main.c) replays the **stock def_ptl_pkt_action
   trap table** (deal=1 for most slots) and runs LAST in init, overwriting the earlier
   entity-loop deal=0 writes. VERIFIED by experiment: forcing deal=0 for ALL slots
   (`zx_proto_fwd_all=1`) BREAKS broadcast/ARP — frames reach the MACs (smac RX climbs) but
   never trap to the CPU (tm_rx=0), the bridge never learns/replies → 100% loss. Control
   with the stock trap table: ping 5/5, tm_rx=16. So broadcast/control MUST keep trapping;
   the §4(i).1 "ensure all deal=0" step is wrong and would break the bridge. The reason TCP
   still works today is NOT pktdeal=forward — it's the merged bit14 wedge fix letting the
   CPU software-bridge drain the trapped frames. (The §3 conclusion "pktdeal is not the
   TCP-vs-UDP discriminator" still stands — but because forwarding goes via the CPU SW
   bridge, not because pktdeal=0.)

2. **Resolves the Iter O/P "CLA hash ram2-6 EMPTY during the offloaded flow" contradiction.**
   ffe_learn_pkt (§2) installs one of TWO actions depending on flow type: L3/NAT flows →
   the heavy CLA-hash hardfast (`cla_set_hash_table`); **pure-L2 bridged flows → the lighter
   SBRAG FDB/forward bind, NOT the CLA hash.** The Iter O/P LAN↔LAN same-subnet test was a
   pure-L2 flow → stock used the FDB bind, so ram2-6 was legitimately empty while TCP still
   HW-forwarded. ⇒ For OUR L2 goal, the FFE-equivalent we need is just **populating the SBRAG
   FDB** (+ the switch honoring it), which in mainline DSA = `assisted_learning_on_cpu_port`
   → `.port_fdb_add` → `zx_sbrag_write_entry` (already stubbed; tested inert in Iter AB
   because the bridge FDB stays EMPTY — see below). We do NOT need conntrack/FFE for L2.

**The concrete open blocker (the real "part 2"):** on the live mainline device the **bridge
FDB is EMPTY** (`bridge fdb show` shows no lan1/lan3 peer MACs) even after sustained trapped
traffic (tm_rx=105, hw_fwd=0). Software ping works via FLOODING, which is why FDB can stay
empty. With an empty bridge FDB, assisted-learning has nothing to push to the SBRAG, so no HW
offload. Two sub-questions to settle (need 2 stable NICs — HW-blocked by host USB hub
instability this session, only jack2/ASIX survived; jack4/enx6c70 dropped off the bus):
  (A) Why doesn't the bridge FDB populate from the trapped frames' source MACs? (learning
      disabled on the DSA user ports? frames delivered without correct skb->dev?)
  (B) The dead-end claim (zte-hw-forwarding-deadend: static fdbadd didn't make hw_fwd climb —
      "CLA preempts DA-lookup") vs Iter AC (UDP DID HW-forward 450761 frames). DECISIVE test
      when NICs return: with a static SBRAG FDB entry for the peer MAC, run a unicast UDP/TCP
      flow lan3→lan1 and watch QMG hw_fwd — climbs ⇒ FDB-offload path viable (do that);
      stays 0 ⇒ CLA-trap-all confirmed and the FFE-hardfast port (option ii) is the only path.
