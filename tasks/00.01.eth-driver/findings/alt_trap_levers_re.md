# Alternative TCP-control trap levers — RE of DPA / CLA / ADM / SPA protocol mechanisms (2026-06-04)

Goal: find a register/mechanism that traps TCP control frames (pure-ACK len-66, SYN,
FIN) to the CPU **separately** from the broadcast/ARP flood path — i.e. a lever I can
disable for TCP without making the Linux bridge stop seeing broadcast/ARP (which would
break flooding). Pure RE from the stock decomp; no device run, no source modified.

## TL;DR — verdict for each candidate

| Candidate | HW reg | Per-protocol? | Traps TCP-control specifically? | Separate from bcast/ARP flood? | Verdict |
|---|---|---|---|---|---|
| **DPA `protocol_pkt_aly_en`** | `0x92398000` bits[6:12] | yes, 7 type slots | **NO** — downstream(PON) analysis path; LAN-LAN counter=0 | n/a | NOT the lever |
| **DPA `protocol_cpu_pps_en`** | `0x92398014` bit0 | global gate for DPA | **NO** — same DPA path; rate-limit gate, not a trap | n/a | NOT the lever |
| **CLA `trap_acl_en`** | `0x9238c080` bit17 | no (global) | unlikely (no TCP ACL programmed; trap_acl band empty) | NO (global) | NOT the lever |
| **CLA `oth_l3_pkt_action`** | `0x9238c0cc` [1:0] | no (catch-all L3) | NO — stock sets it to 0=FORWARD at init | NO | NOT the lever |
| **ADM `protocol_pkt_map`** | `0x92394040/44` [23:0] | yes, 8 cpu-queue slots | **NO** — maps protocol→{cpu_queid,pps_bucket}; a policer/queue map, not a trap | n/a | NOT the lever |
| **SPA `trap_protocol_type0..3`** | `0x921d41c0` (4×8-bit) | yes, 4 IP-proto numbers | **could** (it's literally "trap these IP protos") but stock value = **0x00000000** (unused) | **YES (this one IS separate)** | not active in stock; see note |
| (ref) SPA `enty_pktdeal` | `0x921d4300` reg67[1:0] | yes, per (port,slot) | the known lever — but conflicts with bcast | NO | already ruled out |

**Bottom line: none of the DPA/CLA/ADM candidates is the TCP-control trap.** The only
mechanism in this set that is *both* TCP-specific *and* cleanly separate from the
broadcast/flood path is **SPA `trap_protocol_type0..3` (0x921d41c0)** — but stock leaves
it at 0 (disabled), so it is **not what is trapping TCP today**. This independently
**re-confirms the prior conclusion** (`ffe_tcp_trap_re.md`): the small-TCP-control trap is
**not a chip protocol-classifier rule at all** — it is the stock **FFE conntrack flow
engine** trapping the first/unestablished packets of every TCP flow to the CPU, which
mainline never ported. There is no single "stop trapping TCP-control" register because on
mainline TCP isn't being trapped by a *rule* — it's being delivered to the CPU because the
chip's only forwarding bind for those flows is the FDB/flood path and nothing installs a
unicast forward for the reverse-direction ACKs.

---

## How these registers are written (indirection)

All setters go through `tmOnuRegWrite(reg_index, value, sub_index, &xxxRegTable)`
(decomp_all_tm.c:35358). Each RegTable entry is 0x1c bytes: +8=HW base addr, +0xc=mask,
+0x10=shift, +0x14=stride. So `reg_index` selects a table row that already encodes the
exact HW address+bitfield. Addresses below are resolved against the decoded tables in
`DATASHEET.md` and the live `regs/stock_eth_2mib.txt` 2 MiB dump.

---

## 1. DPA `dpa_set_protocol_pkt_aly_en` / `dpa_set_protocol_cpu_pps_en`  — STRONGEST candidate, REFUTED

### Decompiled behavior
- `dpa_set_protocol_pkt_aly_en(type_id, act_val)` (tm.ko 0x273e8, decomp:14927):
  validates `type_id<7` and `act_val<2`, then `tmOnuRegWrite(type_id, act_val, 0, dpaRegTable)`.
  `type_id` is used directly as the table reg-index → each of the 7 protocol slots is a
  separate 1-bit field in the **same word**.
- `dpa_set_protocol_cpu_pps_en(pps_en)` (tm.ko 0x275e8, decomp:15002): `tmOnuRegWrite(7, pps_en, 0, dpaRegTable)` — table row 7.

### HW addresses (resolved, confirmed against live dump)
- `protocol_pkt_aly_en`: **`0x92398000`**, the 7 type slots are bits **[6],[7],[8],[9],[10],[11],[12]** (type_id 0..6), each mask 0x1. (DATASHEET.md:1035-1041.)
- `protocol_cpu_pps_en`: **`0x92398014`** bit[0]. (DATASHEET.md:1042.)
- DPA fwd/drp/cpy/trp action **counter**: **`0x9239810c`**. (DATASHEET.md:1614.)

### Init (chip_tm_init): YES stock enables it
`tm_pon_pp_dpa_initial` (decomp:43094) loops `dpa_set_protocol_pkt_aly_en(0..6, 1)` then
`dpa_set_protocol_cpu_pps_en(1)`. Live stock values confirm:
- `0x92398000 = 0x000010c0`  → bits 6,7,12 set = pkt_aly for type_id 0,1,6 ON.
- `0x92398014 = 0x0000001f`  → cpu_pps_en bit0 = 1 (ON).

### Why it is NOT the TCP-control trap
- **DPA = "Downstream Packet Analysis."** Its sibling regs are `pon_detault_pri`
  (0x92398038) and the tpid-select table — i.e. this block analyzes **downstream/PON
  (WAN→LAN)** protocol traffic, not LAN↔LAN unicast switching. (DATASHEET.md:1029,1611;
  HW_BLOCKS_INVENTORY.md:22.)
- **Decisive empirical proof:** the DPA action counter `0x9239810c` reads **0x00000000**
  in the live stock dump — DPA's fwd/drop/copy/**trap** engine has acted on **zero**
  packets. If DPA were trapping LAN TCP-control frames this counter would be nonzero.
- `pkt_aly_en` is "enable protocol *analysis/parse*" (feeds counters + the PPS
  rate-limiter), and `cpu_pps_en` is the **packets-per-second rate-limit gate** for
  punting matched protocol packets — a policer, not a per-frame trap classifier. Neither
  is keyed on TCP vs TCP-control-vs-data, and neither is the per-frame forward/trap
  decision for bridged unicast.

⇒ Disabling DPA would have **no effect** on the LAN TCP-ACK trap (counter already 0).

---

## 2. CLA `cla_set_trap_acl_en_config`  — REFUTED

- `cla_set_trap_acl_en_config(trap_acl_en)` (tm.ko 0x10af0, decomp:536): `tmOnuRegWrite(4, en, 0, claRegTable)`.
- HW: **`0x9238c080` bit[17]** = `trap_acl_en_config`. (DATASHEET.md:819.)
- It is a **single global enable** for the CLA ACL-trap subsystem — not per-protocol, not
  TCP-specific, and **not separate from broadcast** (it gates the whole ACL trap path). No
  TCP/L4 ACL rule is programmed in the stock CLA hash/ACL RAM for the L2-bridge case (the
  CLA hash ram2-6 is empty for pure-L2 flows — see ffe_tcp_trap_re.md §CORRECTION). Prior
  work already poked this with no effect (hw_forwarding_offload.md:223). Not the lever.

## 3. CLA `cla_set_oth_l3_pkt_action_cfg`  — REFUTED

- `cla_set_oth_l3_pkt_action_cfg(act_val)` (tm.ko 0x11ce4, decomp:1275): validates `act_val<4`, `tmOnuRegWrite(0x15, act_val, 0, claRegTable)`.
- HW: **`0x9238c0cc` bits[1:0]** = `oth_l3_pkt_action_cfg` (0=fwd,1=trap,2=drop,3=copy). (DATASHEET.md:835.)
- It is the **catch-all action for non-matched L3 packets** — global, not per-protocol.
  Stock sets it to **0 (forward)** at init (`tm_pon_pp_cla_initial` decomp:42757,
  `cla_set_oth_l3_pkt_action_cfg(0)`), so it is **already forwarding**, not trapping. Not
  the lever. (If anything it confirms stock's default-L3 disposition is *forward*.)

## 4. ADM `adm_set_protocol_pkt_map` / `adm_get_protocol_pkt_map`  — REFUTED

- `adm_set_protocol_pkt_map(direction, cpu_queid, pps_bucketnum)` (tm.ko 0x2b0a4, decomp:17070):
  reads/writes a 3-bit field at `cpu_queid*3` in row 10 (dir=0, up) or row 9 (dir=1, dn).
- HW: **`0x92394040`** (up) / **`0x92394044`** (dn), bits[23:0], 8×3-bit fields keyed by
  `cpu_queid` (0..7). (DATASHEET.md:1015-1016.)
- This maps a **CPU queue id → a PPS bucket number** (which policer bucket rate-limits that
  CPU queue). It is an admission/policing/queue-assignment map, **not a forward/trap
  decision and not keyed on IP protocol or TCP flags**. The ADM block is the
  per-protocol pass/drop **counter + policer** stage (DATASHEET.md:1002,1602). Not the lever.

---

## 5. SPA `trap_protocol_type0..3` — the ONLY TCP-capable & flood-separate lever, but UNUSED in stock

This setter is **not in the task's candidate list but is the most on-point mechanism found**:

- `spa_set_trap_protocol_type0(ip_type)` (tm.ko 0x398e0, decomp:27050): validates
  `ip_type < 0x100` (an 8-bit **IP protocol number**), `tmOnuRegWrite(0x1a, ip_type, 0, spaRegTable)`.
  type1/2/3 are at rows 0x1b/0x1c/0x1d. Exposed via `tm_soft_protocol_iptype_set(slot, ip_type)` (decomp:46044).
- HW: all four packed in **`0x921d41c0`**: type0=bits[31:24], type1=[23:16], type2=[15:8],
  type3=[7:0]. (DATASHEET.md:547-550.)
- Semantics: "trap (to CPU) any IP packet whose **IP-protocol byte** equals one of these 4
  configured values." This is in the **SPA ingress classifier** = the same upstream stage
  that handles LAN ingress, and it keys on **IP protocol number** — so setting one slot to
  `6` would trap **all TCP** (not just control frames), while leaving ARP (L2, no IP
  proto) and broadcast flooding untouched. **This is the only candidate that is both
  protocol-specific AND structurally separate from the broadcast/flood path.**
- **BUT: stock leaves it disabled.** Live `0x921d41c0 = 0x00000000` (regs/stock_eth_2mib.txt:20593)
  → all four IP-proto trap slots = 0 (proto 0 = effectively off). It is **not in the
  driver init replay** either. So it is **NOT what traps TCP today** — and it traps *all*
  TCP, not just control frames, so it can't explain "TCP-data forwards but TCP-ACK traps."

⇒ It is the cleanest *separate* lever, but it is (a) not the active cause and (b) too
coarse (all-TCP) to be the control-frame-only trap. Useful only as a *negative* control:
confirming `0x921d41c0 == 0` proves SPA is not IP-proto-trapping TCP.

---

## Synthesis — the real mechanism and the recommended lever

The exhaustive RE of all DPA/CLA/ADM/SPA per-protocol trap knobs **finds no chip register
that traps TCP-control frames specifically**:
- The per-frame forward/trap classifier knobs that exist are **either global**
  (trap_acl, oth_l3) **or already forward** (oth_l3=0) **or in the wrong (downstream/PON)
  path** (DPA, counter=0) **or a policer/queue map** (ADM) **or unused** (SPA
  trap_protocol_type, =0).
- The one per-(port,protocol) per-frame trap that *is* active is the already-known SPA
  `enty_pktdeal` (0x921d4300 reg67[1:0]) — and it is the broadcast/ARP gate, so it
  *cannot* be repurposed (forwarding it breaks flood; this is the established conflict).

This matches and **re-confirms `ffe_tcp_trap_re.md`**: the small-TCP-control trap is not a
classifier rule — it is the **stock FFE conntrack flow engine** (`ffe_receive_skb` →
`ffe_ip_conntrack_check`, vmlinux c0452a7c) trapping every TCP frame until the conntrack
state is ESTABLISHED (and stock's CPU installs an FFE/hardfast forward bind). UDP binds
immediately so UDP HW-forwards; TCP control frames keep being handed to the CPU because
mainline ported none of FFE and nothing ever installs a unicast forward for them. There is
no register to flip because mainline isn't being *commanded* to trap TCP by a rule — the
chip simply has no installed forward for those reverse-dir unicast flows and falls back to
the CPU/flood path.

### Recommended lever (unchanged, now exhaustively justified)
Do **not** chase a per-protocol trap register — none exists for TCP-control. Two viable
directions, in priority order:

1. **Fix the CPU-RX trap-ring drain** (ffe_tcp_trap_re.md §4(i).2): the handful of TCP
   control frames that trap are fine to trap *if they drain*; the wedge is the ~1024
   trap-ring latch in the mainline NAPI poll wrap, not a forwarding rule. This keeps
   broadcast/ARP trapping (flood works) while letting the few trapped TCP-control frames
   pass through the CPU SW bridge. Lowest risk, no chip-config change.

2. **Populate the SBRAG FDB so the chip HW-L2-forwards unicast** (ffe_tcp_trap_re.md
   §CORRECTION (2)): for a pure-L2 bridge the FFE-equivalent is just an FDB bind, not the
   CLA hardfast. The open blocker is the empty mainline bridge FDB (assisted-learning has
   nothing to push). If a static SBRAG FDB entry makes QMG `hw_fwd` climb for unicast TCP,
   this is the offload path. This forwards *unicast* (TCP + UDP) while broadcast/multicast
   still hit the flood bitmap and still trap to the CPU → **clean separation achieved at
   the FDB/forwarding layer, not via a protocol-trap register.**

The separation the task is asking for ("forward unicast TCP while broadcast still traps")
is therefore obtained at the **FDB/forwarding-bind layer (SBRAG)**, NOT via any
DPA/CLA/ADM/SPA protocol-trap register — all of which are now ruled out with addresses.

---

## Register quick-reference (verified addresses)

| symbol | HW addr / bits | stock-live value | role |
|---|---|---|---|
| DPA protocol_pkt_aly_en | `0x92398000` [6:12] (7×1-bit) | `0x000010c0` | downstream protocol analysis enable (PON path) |
| DPA protocol_cpu_pps_en | `0x92398014` [0] | `0x0000001f` (bit0=1) | DPA→CPU PPS rate-limit gate |
| DPA action counter | `0x9239810c` | `0x00000000` | fwd/drp/cpy/trp count = **0 ⇒ DPA inert for LAN** |
| CLA trap_acl_en | `0x9238c080` [17] | (global) | CLA ACL-trap master enable |
| CLA oth_l3_pkt_action | `0x9238c0cc` [1:0] | 0 (init=forward) | catch-all non-matched-L3 action |
| ADM protocol_pkt_map up/dn | `0x92394040`/`0x92394044` [23:0] | — | cpu_queid→pps_bucket map (policer) |
| SPA trap_protocol_type0..3 | `0x921d41c0` (4×8-bit IP-proto) | `0x00000000` | trap-by-IP-proto-number (UNUSED in stock) |
| (ref) SPA enty_pktdeal | `0x921d4300` reg67[1:0] | stock trap table | the known per-(port,proto) trap = bcast gate |
