# Stock WAN-ingress CLA-lookup-ENABLE — DEVICE-FREE decomp RE (2026-07-03)

Task: find, in the stock switch/tm .ko, the per-ingress (per-source-port / per-direction)
classifier-lookup-ENABLE that stock sets and mainline omits — the init/register that makes
WAN/RGMII-ingress packets perform the CLA 5-tuple hash lookup (and thus HIT a resident entry).

Sources (read-only): `decomp_all_{tm,switch}.c`, the real `ext/rootfs/kmodule/tm.ko` ELF,
`linux-v6.6/.../zte/{zx-eth-main.c,zx_reg_tables.h,zx-pp-pro-actions.h}`, and the on-device
findings + memory. No device, no code edits, no commits.

---

## ★ HEADLINE / VERDICT (two parts)

**(A) Answer to the literal question: NO per-ingress CLA lookup-ENABLE register exists — in stock
OR mainline.** The entire CLA lookup configuration is **GLOBAL** (`cla_set_config`,
`cla_set_outspace_cfg`, `cla_set_hash_poly_config` all take **no port** argument), and it is
byte-identical stock↔mainline (proven live: `stock_wan_ingress_lookup_compare`). There is no
per-source-port, per-inport, or per-direction register anywhere in the CLA block that arms/gates
whether the hash lookup runs for a given ingress. So there is nothing of that shape for mainline
to be "missing". Every genuinely per-ingress STATIC surface in the whole stock init path is
enumerated below and is either already replicated on mainline or proven inert.

**(B) This CORROBORATES the current authoritative on-device state (VERDICT B), and REFUTES the
premise this task was written against.** The task's WHY ("~75%/89% of WAN pkts arrive with
`l3_en=0`, never reaching the CLA lookup — a pre-CLA per-ingress parse-arm") came from
`wan_ingress_l3en_split`. That split has since been **discarded** as a wrong-bank artifact
(`counter_audit_2026-07-03` bug #1: it computed `l3_en=0 = QMG_DN_hw_trap − cla_tx_trp(UP bank)`,
subtracting an UP-direction CLA counter from a DN QMG counter). The direction-correct measurement
(`acl_required_fork_settler`) shows **`acl_required` (0x9238c3b8 hi16, direction-agnostic) climbs
1:1 with load** ⇒ **every WAN-ingress DN packet DOES reach the CLA lookup**, and ~72% then **FAIL
the lookup INSIDE the CLA** (acl_failed ≈ cla_dn_trap ≈ QMG DN hw_trap; SPA/DPA parse traps carry
≈none). So packets are already performing the lookup — there is nothing to "enable"; they perform
it and MISS. This is exactly why (A) finds no enable register: the mechanism is a lookup **result**
difference (VERDICT B), not a lookup **gating** difference.

**⇒ The task's B2 axis ("a per-ingress lookup-enable stock does, mainline doesn't") is CLOSED
NEGATIVE.** The surviving fix is NOT a stock init register; it is either **B1** (encode the
WAN-ingress/pos32 compare-domain bit into the STORED CLA windata for WAN entries — a per-entry
*content* change in `zx_ft_pack_cla`, not an init) or a **HW/pipeline property** of the WAN/RGMII
(DN ring-1) ingress that changes the hash-compare outcome. See "surviving leads" below.

---

## Full RULED-OUT set — per-ingress static surfaces (present on mainline or inert)
| surface | stock fn | mainline | status |
|---|---|---|---|
| CLA lookup config (cla_config 0x600 / poly 0x00e400e4 / outspace 0x4) — **GLOBAL, no port arg** | `tm_pon_pp_cla_initial` | byte-identical live | present/identical |
| WAN-port ROLE (`PON_PP_TM_CFG` 0x923a001c bits[29:25]) | `sw_other_set_wan_lan_switch`→`tm_set_pp_wan_cfg` | replayed `0x21200000` (bit29=physport4) | present (`wan_portrole_mflow_RE`) |
| per-port,per-proto action `enty_pktdeal_cfg` (0x921d4300+port*0x14) | `pp_set_pro_action` | replayed 0..7 | present (PP0 profile — see note) |
| ONU/to-me MAC (arms L3-route on to-me DMAC) | `spa_set_onu_mac_addr`/`pp_pm_set_onu_mac_ram_info` | `zx_eth_register_cpu_mac_slots` (base MAC = lan4 DMAC) | present |
| up/dn `reg_pkt_en` (0x14000/04/08 + 0x14040/44/48) + `match_mode`(0x1407c) + 0x14054\|=0x3000000 | `spa_set_up/dn_reg_pkt_en`,`tm_pon_npp_spa_initial` | written all-on / set | present |
| pkt_en/pps_en per-entry | " | HW-reset all-on | present/inert |
| `cla_set_oth_l3_pkt_action_cfg(0)` | `tm_pon_pp_cla_initial` | replayed (:1199) | present |
| per-port DA-lookup-en (0x923882c0) | `sbrg_set_pt_da_lookup_en` | brg-init | present (L2, not the L3 gate) |
| `cla_set_local_ipv4` / up-dn `l3_default_flow_cfg` / `mac_req_ctrl` | tm.c | **0 on stock too** (no callers) | inert on both |
| `sw_wancip_set` (WAN-IP→HW L3 iface) / `sw_set_mflow_config` | ioctl | — | **stubs `return 0;`** on stock |
| trap_dmac slot4 | `spa_set_trap_dmac` | clears 0..3 | stock API is 4 slots; slot4 live=0 (`acl_required_fork_settler` TEST2) |
| SPA match-RAM/hash-RAM (ram_id0/5) | `tm_pon_npp_spa_initial` | **NOT populated** | omitted, but NOT this gate — see note |

Direction axis also yields no static enable: DN has separate init in 3 places
(`spa_set_dn_reg_pkt_en` all-on; `cla dn_unicast_ctrl`=0 both; `cla_set_dn_l3_default_flow_cfg`
zero callers, 0 on stock too), and the two SPA content-classify RAMs carry **no direction bit**
(fields = valid/match_array/action_rsn/action only; bytes extracted below).

### Note — SPA match-RAM/hash-RAM: a real omission, but NOT the WAN gate
Stock's `tm_pon_npp_spa_initial` (tm.ko 0x3ed1c) loads 11 match-RAM rules (`spa_set_matchram`,
ram_id0) + 8 hash-RAM entries (`spa_set_hashram`, ram_id5) via the SPA indirect regs
(**CMD 0x921d4014 = `ram_addr|ram_id<<22|rw_en<<27`, DONE 0x921d4018 bit0, DATA[0..5]
0x921d401c..30**). Mainline's `zx_pm_spa_init` (zx-eth-main.c:6162) sets match_mode + the direct
regs but does **zero indirect writes** — its own comment (:6158) confirms the match-RAM "is NOT
populated here yet". **However this is NOT the WAN-ingress-lookup gate**, for two independent
reasons: (1) it is **portless + direction-agnostic** (extracted bytes below = generic L2/L3/
EtherType offset matchers with no port/direction/action/l3_en column — `spa_matchram_tcp_re`),
so it cannot produce a WAN-vs-LAN asymmetry; (2) an empty SPA classifier would trap frames
**pre-CLA**, but `acl_required` shows WAN-ingress frames **reach the CLA** (SPA/DPA traps carry
≈none of the loss). So populating it is not expected to fix the miss. Extracted source (for
completeness / any future SPA work):
- match-RAM `.data:.LANCHOR1` (28-byte records from `.data+0x74`): generic matchers at packet
  bytes 0x0b (IP-proto), 0x0e (EtherType), 0x11; masks 0x0fffffff/0x3fff/0xffffffff.
- hash-RAM `.rodata+0x1af0` (12 words = 8 entries × 6B): `a9160000 0002a51a 00000002 8d320000
  00027562 02000002 75a20100 00027562 01000002 75a20200 0002a120 0c000002`.

### Note — enty_pktdeal_cfg PP0 vs PP1
Mainline uses the PP0 action for every port; PP0/PP1 differ in **one ptype (proto 0x14:
PP0=trap/PP1=forward)** (`zx-pp-pro-actions.h`). One ptype cannot explain a bulk-TCP-data miss,
and `acl_required` shows frames reach the CLA anyway. Not the gate; a trivial side-experiment at
most.

---

## Surviving fix leads (neither is a stock init register mainline misses)
1. **B1 — stored compare-domain bit (per-entry content, HIGHEST remaining):** the WAN-ingress
   extracted key carries `pos32=1` (word1 low, the WAN/RGMII ingress-domain bit); the driver sets
   it in the HASH (slot-match proven both dirs, #474) but `zx_ft_pack_cla`/`zx_cla_pack_entry`
   build the STORED windata **ingress-agnostic**, so if the post-hash COMPARE includes the
   ingress-domain bit, a WAN packet (pos32=1) fails vs stored (pos32=0). LAN packet (pos32=0)
   matches → fits "same entry hits from LAN, misses from WAN". Caveat: the stock↔mainline
   windata diff (`stock_wan_dn_entry_diff`) showed the compare region byte-identical except
   extr_index/da_known/direct — all since tested and insufficient (`exact_stock_entry_test`,
   `wan_verdict_bits_bisect`), and `in_cla_wan_ingress_miss` notes word1-low is `cmd_flow_id`
   (an ACTION field, not compare). So B1 needs the *exact* stored-windata bit position for pos32,
   which the static diff has NOT located — this is the open kotrace target.
2. **HW/pipeline (the residual after B1):** a WAN/RGMII (DN ring-1) ingress property that changes
   the hash-compare result for the same key/slot/resident-valid entry. Not SW-writable via any
   stock init register (this RE + the whole ruled-out table). Needs a stock live-WAN-ingress CLA
   lookup kotrace to see what stock's WAN-ingress descriptor/compare state carries that mainline's
   doesn't.

## Confidence
- **HIGH**: no per-ingress CLA lookup-ENABLE register exists (CLA config is global + byte-identical;
  full per-ingress static surface enumerated present/inert). The literal task answer is the NO
  branch — redirect to entry-content (B1) or HW/pipeline.
- **HIGH**: this corroborates VERDICT B (`acl_required_fork_settler`) — packets reach the CLA and
  fail the lookup; the l3_en=0/pre-CLA premise is a discarded cross-bank artifact (`counter_audit`).
- **HIGH**: SPA match/hash RAM is the only omitted upstream classify table, but is portless +
  frames reach the CLA anyway ⇒ not this gate.
