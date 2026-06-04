# SPA matchram & TCP-control: does it classify TCP to a FORWARD or TRAP ptype? — RE (2026-06-04)

THE QUESTION: Does stock's SPA "matchram" (header-pattern → protocol-type-slot
classifier) put TCP control frames (pure-ACK/SYN/FIN) into a FORWARD ptype slot or a
TRAP ptype slot? I.e. is the matchram the lever to make TCP ACKs HW-forward on
mainline, or does stock forward them by a different mechanism (the FFE conntrack bind)?

Pure RE from decompiled stock binaries + the real `tm.ko` ELF. No source modified, no
device touched.

---

## TL;DR — VERDICT: the matchram is NOT the lever.

1. **The SPA matchram has NO forward/trap action field at all.** It is a portless
   header byte-matcher: each entry is `{rule_num, valid, v4_v6_flag, offset_mode,
   offset, compare_mode, mask, data}` (decoded bit-exact from `spa_set_matchram` and
   the boot table `.LANCHOR1`). There is no `act`/`deal`/`forward`/`trap`/`ptype`
   column in a matchram entry. The matchram only decides *which protocol-type slot a
   frame falls into*; it cannot itself forward or trap. (Re-confirms the prior
   `zte-spa-matchram-not-gate` finding, which disassembled the same ELF.)

2. **The forward-vs-trap decision is a SEPARATE table: the SPA per-ptype pktdeal RAM
   at HW `0x921d4300` reg67[1:0]** (`spa_set_enty_pktdeal_cfg`), 0=forward 1=trap
   2=drop 3=copy, indexed by ptype slot 0..0x3c. THIS is where "forward or trap" is
   decided, not in the matchram.

3. **A plain TCP frame's ptype slot is set to TRAP (deal=1) by stock's boot pktdeal
   table.** Stock's `def_ptl_pkt_action` (captured live in `zx-pp-pro-actions.h`) sets
   action=1 (trap) for the vast majority of the 71 ptype slots, including the generic
   L4/IP slots a bridged TCP frame lands in. Only a small set of slots are forward(0):
   `0x12, 0x1e, 0x1f, 0x20, 0x23, 0x24, 0x26, 0x28, 0x43, 0x44`. So at the SPA stage,
   **stock would classify-and-TRAP a fresh TCP frame**, exactly as the FFE design
   requires (FFE wants to see the first packets of every TCP flow).

4. **Therefore the matchram is NOT the lever.** Replicating stock's matchram on
   mainline would NOT make TCP ACKs HW-forward — the matchram has no forward bit, and
   the slot a TCP frame matches is set to TRAP in the pktdeal table anyway. Stock makes
   ESTABLISHED-TCP forward via the **FFE/conntrack per-flow bind**, NOT via the
   matchram. For a same-subnet L2 bridge that bind is the **SBRAG FDB forward**
   (NOT a CLA-hash hardfast — that's only L3/NAT/WAN).

---

## 1. What the matchram is (decoded) — and what it is NOT

### Boot programmer
`tm_pon_npp_spa_initial` (tm.ko `0x3ed1c`; decomp `0x4ed1c`) is the boot path that
programs the matchram. Sequence:
- `spa_set_match_mode(1)` (HW `0x921d407c`[1:0]).
- `memcpy(stack, &.LANCHOR1, 0x160)` — copies the 352-byte static match-rule table
  (`.LANCHOR1` in `.data`, reloc `R_ARM_MOVW/MOVT_ABS .LANCHOR1` at the memcpy).
- Loop: for each entry, build a 10-byte struct and call **`spa_set_matchram(&ent)`**
  (tm.ko `0x28120`).
- Then 8× `spa_set_hashram(i, ...)` (tm.ko `0x27ee4`) from a `.rodata` table.

### Entry struct (from `spa_set_matchram` printk, decomp 26161-26168)
`byte[0]=rule_num, [1]=valid, [2]=v4_v6_flag, [3]=offset_mode, [4]=offset,
[5]=compare_mode, [6:8]=mask(u16), [8:10]=data(u16)`.
→ A frame is matched by: take `offset` bytes into the frame (in `offset_mode`/`v4_v6`
window), `AND mask`, `compare_mode` against `data`. **No action/ptype/port field.**

### The boot table `.LANCHOR1` (extracted from the real `tm.ko` .data, 28-byte records)
```
rule0: rule=0  marker=0xe3005  m0=0x0fffffff
rule1: rule=1  marker=0xe3006  m0=0x1
rule2: rule=2  marker=0xe3007  m0=0xffffffff m1=0x110000 m2=0x1
rule3: rule=3  marker=0xe3020  m0=0xfffff
rule4: rule=4  marker=0xe3020  off=0x11
rule5: rule=5  marker=0xe3020  off=0x0b
rule6: rule=6  marker=0xe3022  m0=0x3fff
rule7: rule=7  marker=0xe3022  off=0x0e
rule8: rule=8  marker=0xe3023  ...
```
(The `0xe30XX` word is the per-rule SPA indirect-RAM line address the entry programs,
not a packet field.) These are generic L2/L3/EtherType offset+mask matchers (matching
at packet offsets like 0x0b = IP-protocol byte position, 0x11, 0x0e = EtherType). They
classify frames into protocol-type slots; **none of them carries a forward/trap bit, an
outport, or a "TCP-control vs TCP-data" distinction.** There is no rule that matches TCP
flags (SYN/ACK/FIN) — the matchram operates on fixed header *offsets*, and stock does
NOT program any TCP-flags rule.

→ **Answer to RE-task #2: NO. The matchram does not distinguish TCP-control from
TCP-data. It cannot — it matches fixed header offsets/EtherType/IP-proto, not TCP
flags or packet length, and assigns the same ptype to control and data of the same
protocol.**

### HW-reset default (what mainline runs with) — RE-task #3
Mainline (`linux-v6.6/.../zte/`) programs **no** matchram (grep: no `spa_set_matchram`
equivalent; `zx_pm_spa_init` writes pkt_en + direct SPA regs but never the match RAM).
The matchram is an INDIRECT RAM (`ram_id 0`, behind CMD `0x921d4014`/DONE `0x921d4018`/
DATA `0x921d401c..30`) so a flat register dump can NOT see it — confirmed: the live
stock dump (`regs/stock_eth_2mib.txt`) captures only the SPA flat regs (match_mode,
pkt_en, indirect-port shadow), NOT the 11 indirect match-RAM lines. So there is no
captured stock matchram content; it had to be recovered from the `.LANCHOR1` blob
(done above). Mainline runs at the HW power-on default of ram_id0 (whatever ptype the
default classifier assigns). **But this is moot for the TCP-ACK question — see §3.**

---

## 2. Where forward/trap actually lives (the pktdeal RAM, downstream of matchram)

The matchram → ptype slot. The ptype slot → action is a DIFFERENT table:
- `spa_set_enty_pktdeal_cfg(port, ptype, deal)` → `tmOnuRegWrite(ptype+0x43, deal,
  port, spaRegTable)` → HW **`0x921d4300` reg67[1:0]** (per (port, ptype) 2-bit field,
  +0x14/ptype, +0x4/port). **0=forward, 1=trap, 2=drop, 3=copy.**
- Set per-port by `zte_api_pp_set_pro_action(group0)` → 8× `tm_port_protocol_pktdeal_set`.

Stock's boot values for this table = `def_ptl_pkt_action`, captured live by kotrace
into `linux-v6.6/.../zte/zx-pp-pro-actions.h` (142 calls = 71 ptype slots × 2 PP). The
forward(0) slots are ONLY: `0x12, 0x1e, 0x1f, 0x20, 0x23, 0x24, 0x26, 0x28, 0x43,
0x44` (plus `0x14` forwards on PP1 only). **Every other slot, including the generic
L3/L4/IP slots, is TRAP(1).**

→ **Answer to RE-task #1 + #4: a plain bridged TCP frame is classified by the matchram
into a generic L3/L4 ptype slot whose pktdeal is deal=1 (TRAP) under stock's boot
table. So at the SPA stage, BEFORE any FFE/CPU involvement, stock TRAPS a fresh TCP
frame.** This is consistent and intentional: stock's FFE *needs* the first packets of
each TCP flow trapped to the CPU so conntrack can learn the flow (see §4).

(The few forward(0) slots like 0x1e/0x1f/0x20 are specific accelerated data ptypes; the
prior live work — Iter AI/AL in `pktdeal_override_re.md` — found that making TCP ACKs
HW-forward by the pktdeal route requires forcing a LARGE multi-slot subset to deal=0,
and forcing ALL slots to forward breaks broadcast/ARP. So the pktdeal table is not a
clean single-slot lever for "TCP-control forwards" either.)

---

## 3. Resolving the original tension

> "If stock's matchram classified TCP→a forward ptype, stock would never trap TCP and
> wouldn't need the FFE. Since stock's FFE DOES trap TCP initially, stock's matchram
> probably classifies TCP-control to a TRAP ptype."

**Confirmed — but with the precise mechanism corrected:** it is not the matchram that
"classifies TCP to a trap ptype"; the matchram only *picks the slot*. The TRAP decision
is the **pktdeal RAM** value for that slot, and stock sets it to TRAP(1). The matchram
has no action field, so it can never be the forward-vs-trap lever. The two are separate
tables:
- matchram (ram_id0, `0x921d4014` indirect) = byte-matcher → ptype slot. No action.
- pktdeal (`0x921d4300` reg67[1:0]) = per-(port,ptype) forward/trap/drop/copy.

Independently confirmed: `0x921d41c0` `trap_protocol_type0..3` (the only true IP-proto
trap in the SPA block; 4×8-bit IP-proto values) reads **0 in stock** — stock is NOT
IP-proto-trapping TCP via that register either (would trap ALL TCP incl. data, which it
doesn't). So no SPA-level rule selectively traps TCP-control; the initial TCP trap is
purely the generic-slot pktdeal=TRAP, and the steady-state forward comes from the FFE
bind installed after conntrack reaches ESTABLISHED.

→ **RE-task #5 answer:** `spa_set_matchram` is unrelated to `trap_protocol_type0..3`
(`0x921d41c0`). The matchram is ram_id0 indirect; `trap_protocol_type` is a direct SPA
reg (spaRegTable rows 0x1a..0x1d, set via `spa_set_trap_protocol_type0..3` /
`tm_soft_protocol_iptype_set`). Stock leaves it 0. They are independent mechanisms.

---

## 4. Since it's the FFE bind (NOT the matchram): what table does the bind write?

Stock makes an ESTABLISHED TCP flow HW-forward via the FFE/conntrack per-flow bind, NOT
the matchram. The bind table depends on flow type:

- **L3 routed / NAT / WAN↔LAN flow:** the CLA-hash "hardfast" entry —
  `zte_api_fast_l3_session_add` (tm 0x6558c) → `tm_add_acl_flow_rule` → `addFlowOperInfo`
  → **`cla_set_hash_table`** (tm 0x15a14), writing the 60-byte CLA hash entry (ram2-6,
  indirect CMD `0x9238c014`). Format fully decoded in `pktdeal_override_re.md` §B/C
  (`act_val=0` forward, `valid_en=1`, `direct=1`, `outport`, `inport`, `windata0..19`
  = packed 5-tuple). This is NOT used for an L2 bridge.

- **Same-subnet L2 unicast (the bridge case — what this project needs):** the bind is
  the lighter **SBRAG FDB / DA-lookup forward**, NOT a CLA-hash entry. Decisive live
  evidence (`ffe_tcp_trap_re.md` §CORRECTION, Iter O/P): during a confirmed-offloaded
  350 Mbit/s same-subnet LAN↔LAN TCP flow, the CLA hash banks ram2-6 were scanned and
  found EMPTY — so stock used the FDB forward, not the hash. The relevant HW:
  SBRAG FDB at `0x92388000`, `pt_da_lookup_en` `0x923882c0`, unknown-unicast
  dispositions `0x92388340[23:8]` / `0x9238863c[31:16]`. In mainline DSA terms this maps
  to `assisted_learning_on_cpu_port` → `.port_fdb_add` → `zx_sbrag_write_entry`
  (already stubbed in the driver).

**Net: for our L2 goal there is no matchram or CLA-hash entry to replicate — the
forwarding path is (a) the chip not trapping the data frames + (b) the SBRAG FDB
resolving the destination MAC.** The remaining real blocker (per `ffe_tcp_trap_re.md`
§"part 2") is that the mainline bridge FDB stays empty so assisted-learning has nothing
to push, plus the CPU-RX trap-ring drain — neither of which is the matchram.

---

## Concrete answers to the deliverable

**(a) What ptype stock's matchram assigns to TCP, and does it forward or trap?**
The matchram assigns TCP (control and data alike — it cannot tell them apart) to a
generic L3/L4 ptype slot. That ptype's pktdeal action under stock's boot table
(`def_ptl_pkt_action`) is **TRAP (deal=1)**. So at the SPA stage stock **TRAPS** a fresh
TCP frame. (The matchram itself has no action field; the trap comes from the separate
pktdeal RAM `0x921d4300`.)

**(b) Verdict — matchram or FFE bind?**
**The matchram is NOT the lever.** It has no forward/trap/ptype-action column, and the
slot TCP lands in is set to TRAP in stock's pktdeal table. Replicating stock's matchram
on mainline would not make ACKs HW-forward. Stock forwards ESTABLISHED-TCP via the
**FFE/conntrack per-flow bind**: for same-subnet L2 that bind is the **SBRAG FDB
forward** (CLA hash ram2-6 empty during a live L2 flow); for L3/NAT it's the CLA-hash
hardfast.

**(c) If FFE: what table the bind writes for an L2 flow.**
The **SBRAG FDB** (`0x92388000`; `pt_da_lookup_en` `0x923882c0`), via
`zte_api_fast_l3_session_add`'s L2 branch / the FDB forward bind — NOT `cla_set_hash_table`
(that's the L3/NAT path, ram2-6, which was verified empty during a live same-subnet L2
TCP flow). Mainline equivalent: `.port_fdb_add` → `zx_sbrag_write_entry` +
`assisted_learning_on_cpu_port`.

---

## Honest confidence
- **HIGH**: matchram entry format + no-action-column (decoded bit-exact from
  `spa_set_matchram` printk + `.LANCHOR1` extracted from the real tm.ko `.data`;
  re-confirms `zte-spa-matchram-not-gate`).
- **HIGH**: forward/trap lives in the separate pktdeal RAM `0x921d4300`, and stock's
  boot table traps the generic TCP slot (live-captured `def_ptl_pkt_action`).
- **HIGH**: matchram does not distinguish TCP-control from TCP-data (offset/EtherType/
  IP-proto matcher only; no flags/length match; stock programs no TCP-flags rule).
- **HIGH**: stock's initial TCP trap is the FFE/conntrack design, and the L2 bind is the
  SBRAG FDB not the CLA hash (live Iter O/P: ram2-6 empty during offloaded L2 flow).
- **MEDIUM**: the exact HW-reset default of the matchram ram_id0 (mainline's value) was
  not captured in the flat dump and is not load-bearing for this verdict (the trap is in
  pktdeal, not the matchram).
