# WiFi Stage-3 `ssid` encoding spec — exact bit layouts for HW-offload plumbing (2026-07-07)

Device-free RE. Sources: stock decomp `tasks/00.10.02.re-stock-kmods/findings/decomp_all_{tm,switch,plat_zxylzb_9128S,idmfdb}.c`,
existing canonical refs `tasks/00.10.02.re-stock-kmods/findings/DATASHEET.md` + memories
`zte-cla-ram-layout.md`/`zte-datasheet.md`/`zte-port-numbering.md`, mainline
`linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`. No device touched, no source modified.
CLA ram2-6 hash-table mechanics *other than the ssid question* are **not** re-derived here —
see `zte-cla-ram-layout.md` for that (already documented); this doc adds only the ssid dimension
on top of it.

**Headline result:** `ssid` (WiFi vif/SSID index 0-7) is a first-class field of the switch's
**in-flight pipeline descriptor** (confirmed bit-exact at 4 independent monitor points) and of the
**IDM DMA descriptor** (RX/TX, confirmed bit-exact from both the debug dump and the real production
code). It is **NOT a field of any stored table** the driver would program: not the CLA ram2-6
hash entry, not either of the two stored MAC-FDB formats, not PM's `flow_info`/`next_hop`. This
overturns the feasibility scout's working assumption ("hardfast entry with `ssid_out`") — see
§6 for what that means for the Stage-3 plan.

Confidence key: **✅ CONFIRMED** = exact source citation, code inspected directly (not inferred);
**🟡 DERIVED** = follows necessarily from confirmed facts but no single line states it; **❓ OPEN** =
flagged explicitly, not guessed.

---

## 1. IDM descriptor (RX + TX) — ✅ CONFIRMED, bit-exact

8-byte descriptors, ring bases `npp_base+0x8000` (=phys `0x921c8000`, DATASHEET §3.2). Both the
*debug-dump* functions and the *real production code path* were read; they agree exactly.

### RX descriptor

`dump_idm_desc_rx` (decomp_all_plat_zxylzb_9128S.c:4008-4017):
```c
printk("... idm %u,len %u ssid %d ssid vld %d\n", *param_1, param_1[1],
       *(byte*)((int)param_1+7) >> 7,             /* idm ring   = byte7 bit7        */
       *(ushort*)(param_1+1) & 0x3fff,             /* len        = word1 bits[13:0]  */
       *(byte*)((int)param_1+6) & 7,               /* ssid       = byte6 bits[2:0]   */
       ((uint)*(byte*)((int)param_1+6) << 0x1c) >> 0x1f);  /* ssid_valid = byte6 bit3 */
```

| word | bits | field |
|---|---|---|
| word0 (bytes 0-3) | — | RX buffer DMA address |
| word1 (bytes 4-7) | [13:0] | `len` |
| word1 | byte6 bits[2:0] | **`ssid`** (0-7) |
| word1 | byte6 bit3 | **`ssid_valid`** |
| word1 | byte7 bit7 | `idm` ring select (0=idm0/port6, 1=idm1/port7) |

**Production code confirms this is really consumed**, not just a debug decode — `idm_net_poll`
(plat.c:4125-4131), the actual RX handler that runs on every packet:
```c
if ((*(byte *)(iVar13 + 6) & 8) == 0) {      /* byte6 bit3 (ssid_valid) clear */
    bVar9 = 0xff;                            /* → sentinel: "no ssid" */
} else {
    bVar9 = (byte)(((uint)*(byte *)(iVar13 + 6) << 0x1d) >> 0x1d);  /* byte6 & 7 */
}
*(byte *)(iVar12 + 0xb7) = bVar9;             /* stash into skb->cb offset 0xb7 */
```
`skb->cb[0xb7]` is the hand-off point to `idm_skb_recv` (idmfdb.ko's `idm_fdb_forward`, §5). Invalid
ssid → `0xff` (flood/no-ssid marker), not 0 — **do not treat 0xff as ssid 0** in a mainline port.

### TX descriptor

`dump_idm_desc_tx` (plat.c:4194-4203) confirms the *field positions*; `idm_net_tx`
(plat.c:4206-4299) is the real packer, word1 built at **plat.c:4268-4270**:
```c
*(uint *)(iVar4 + 4) =
     param_1[0x19] | *(int *)(param_2 + 0x4c4) << 0x1f |
     (uint)*(byte *)((int)param_1 + 0xb7) << 0x1c;
/*   = len | (idm_ring << 31) | (skb[0xb7] << 28)                                  */
```

| word | bits | field |
|---|---|---|
| word1 | [13:0] | `len` (no explicit mask in the setter — caller must keep it small) |
| word1 | [30:28] | **`ssid`**, copied verbatim from `skb->cb[0xb7]` |
| word1 | [31] | `idm` ring select |

⚠ **No masking of `skb[0xb7]` before the `<<28`.** If the byte holds anything but 0-7 (e.g. the
RX sentinel `0xff` gets echoed back on a reflected/cloned skb) it will corrupt bit31 (`idm` select)
as well as bits 28-30. A mainline implementation **must** clamp/validate ssid to 0-7 before building
the TX descriptor — stock's own contract silently assumes callers never pass an invalid value here.
`idm_net_register` (plat.c:3698) stores the ring index at `netdev_priv+0x4c4`, which is what feeds
the `<<31` term.

### Maps onto the mainline gap

- `zx_idm_poll` (zx-eth-main.c:1621-1707) **already added** the RX decode as an additive/observational
  change (lines 1649-1663: `ssid = (word1>>16)&0x7; ssid_valid = (word1>>19)&1;` — i.e. `word1`
  bits[18:16]/[19], the *word1-relative* form of the *byte6*-relative form above — same bits,
  confirmed consistent) but still delivers unconditionally via `napi_gro_receive` (no dispatch).
- `zx_idm_xmit` (zx-eth-main.c:1733-1780) builds word1 at lines 1772-1773 with **no ssid bits at
  all** — `(len & IDM_DESC_LEN_MASK) | (port->idx ? IDM_DESC_PORT_BIT : 0)`. Needs an
  `IDM_DESC_SSID_SHIFT 28` OR-in of a clamped 3-bit ssid sourced from... `skb->cb` has no
  established convention in mainline; a new per-skb tag (cb field or a `struct zx_eth`-private
  side-channel keyed by the wlan vif) is needed — see §5.

---

## 2. FDB (MAC forwarding table) — ✅ CONFIRMED: **no ssid field, in either of the two stored formats**

Two independent HW tables exist (DATASHEET §3.14); both were checked bit-exhaustively and both are
**scalar-port/bitmap only** — no 3-bit ssid subfield anywhere.

### FDB-A (PP_BRG_RAM, hashed, hardware auto-learn target)

Write function `pon_pp_add_mac(char *mac, uint vlan_status, uint port)` (plat.c:4721-4794),
9-byte entry via `brg_ram_set`/`brg_ram_get` (plat.c:4581/4548, indirect regs `pp_base+0x8014`
CMD / `+0x8018` DONE / `+0x801c..24` DATA):

| byte | field |
|---|---|
| 0 | **port bitmap**, `1 << port` (plat.c:4768: `local_34 = (undefined1)(1 << (param_3 & 0xff))`) — single-port-set bitmap, `param_3` bound-checked `< 8` (plat.c:4744) |
| 1-6 | MAC (6 bytes) |
| 7 | vlan[7:0] |
| 8 | vlan[11:8] (bits[3:0]) \| status (bits[7:4], `0xf0` = valid, decoded via `get_mac_status(status>>4)`) |

No ssid byte, no spare bits (all 9 bytes fully accounted for by the debug-dump/pack code at
plat.c:4757-4778).

### FDB-B (SBRAG indirect secondary table — the one `zx_fdb_add`/`zx_sbrag_add_mac` targets)

Confirmed independently via direct decomp read (this doc) and the delegated agent's read of the
*setter* `sbrg_add_mactable` (tm.c:10706-10840) and *getter* `sbrg_lookup_mactable` (tm.c:10549+):
exactly **3 data words** (`sbrg_set_ind_access_data`/`get` bounds-check `< 3`, tm.c:5906/5935).
Field layout (register IDs 0x4c/0x4d/0x4e via `sbrg_set_indreg_wr`, tm.c:8422; matches the
already-known D0/D1/D2 content from `zte-datasheet.md`, just relabeled — same bits, same meaning):

| word (reg) | bits | field |
|---|---|---|
| reg 0x4c | [7:0] | **port bitmap** (8 bits) |
| reg 0x4c | [31:8] | mac_low4 (3 of the 6 MAC bytes) `<<8` |
| reg 0x4d | [7:0] | mac_low4 byte 4 (`>>24`) |
| reg 0x4d | [23:8] | mac_high2 (2 MAC bytes) |
| reg 0x4d | [31:24] | vlan[7:0] |
| reg 0x4e | [3:0] | vlan[11:8] |
| reg 0x4e | [7:4] | status nibble (0=empty, 0xF=static/valid, per `zx_fdb_add`'s existing driver logic) |
| reg 0x4e | [8] | smac_ctrl |
| reg 0x4e | [9] | dmac_ctrl |
| reg 0x4e | **[31:10]** | **never read, written, or printed by any software path found** (❓ see below) |

Mainline's `zx_fdb_add` (zx-eth-main.c:668-722) already matches this shape (`port` param, single
scalar 0-7, `d2 = port | mac_low4<<8`) and **already lacks ssid** — consistent with stock, not a
mainline bug to fix by adding a field that doesn't exist in the format.

### The WiFi port bitmap is 1 bit per **IDM ring**, not per SSID

`tm_mactable_add_set` (tm.c:40548) remaps a caller-supplied portmask into HW order and passes
**caller bits 6/7 straight through as HW bits 6/7** — i.e. the FDB's WiFi capacity is exactly
"port 6" / "port 7" (one bit each), matching `zte_api_sw_get_wlan_port={6,7}`. **A FDB entry
physically cannot address "client on port 6, ssid 3" vs "client on port 6, ssid 5" — it can only
say "port 6."** This is airtight (every byte of both formats is accounted for by name), not an
inference from missing documentation.

### ❓ OPEN QUESTION — where does the descriptor's `ssid_out` come from on a DA/FDB hit, then?

The internal pipeline descriptor (§3) unambiguously carries a live 3-bit `ssid_out`/`ssid_in` that
gets a real value at runtime. Given neither FDB format nor the CLA stored entry (§4) has a field
for it, three explanations remain open, **none confirmed**:

1. **HW-learned FDB-A entries use the unaccounted reg-0x4e bits [31:10]** (22 spare bits) to stash
   ssid on autonomous SA-learn, and software (which only ever *sets* status/port/vlan/mac) simply
   never had a reason to read/write those bits. Plausible, unverified — would need a live raw read
   of a HW-learned WLAN-client entry (out of scope here: device-free task).
2. **ssid is resolved from VLAN, not MAC** — stock may map each SSID to a distinct internal VLAN;
   the FDB entry already carries a 12-bit VLAN field, and a **separate small config table** (the
   SW-side `s_aclWlanToIdmEssidMap`, §5) could translate (idm_port, vlan) → ssid at the point the
   descriptor's ssid_out is populated. No source line found that literally performs this lookup on
   the DA-hit path — inferred from field availability, not observed.
3. **WiFi-destined unicast that isn't a CLA-flow hit never gets a HW-resolved ssid at all** and
   always traps to CPU, where the *software* (idmfdb.ko, §5, or `ffe_learn_skb`'s SW bridge) picks
   the ssid via its own (idm,ssid)↔MAC state. This is consistent with the project's own established
   finding (`zte-hw-forwarding-deadend.md`: "switch never HW-forwards... trap-all") and would mean
   `ssid_out` in the descriptor is only meaningful for the two directions the driver *builds itself*
   (CLA/PM flow install and IDM TX from the WLAN driver), never for a bare DA lookup.

**Do not guess which of these is true when implementing.** For Stage-3, (3) is the safe assumption
(it matches everything already proven about this switch's trap-all behavior); if a future live
probe shows FDB-A auto-learn entries with nonzero reg-0x4e bits ≥10 after a WLAN client associates,
hypothesis (1) is confirmed and changes the plan.

---

## 3. The shared internal pipeline descriptor — ✅ CONFIRMED, bit-exact, 4 independent monitor points agree

This is **not a stored table** — it's the packet-metadata structure HW carries between blocks
(SPA→ADM→CLA→PM→SBRG/bridge→egress), exposed for debugging at several fixed (non-indirect) FPGA
register windows. It is the thing that *carries* ssid forward once some stage resolves it; useful
context for §5's dispatcher, and for confirming §1/§4's numbers are self-consistent, but nothing
here is written by a mainline driver directly.

Four independent dumps were decoded bit-exactly (all four agree with each other and with §1's IDM
numbers on inport/ssid_in position, which is strong cross-validation):

| dump fn | citation | ssid-related fields found |
|---|---|---|
| `PrintBrgDesc` (SBRG monitor, global bit numbers, mode 0 = ingress) | tm.c:66260-66424, regs `0xe2380`+ | `inport(64:61)`, **`ssid(67:65)`** (tm.c:66358) — 3-bit |
| `PrintBrgDesc` (mode 1 = post-bridge result) | tm.c:66424-66528 | **`outport(239:230)`** (10-bit, likely a port/ring **bitmap**, not a scalar — sits next to `ram_id`), **`ssid_flag(240:240)`** (tm.c:66511, 1 bit only — no multi-bit ssid value in this dump), plus explicit **`qnum_wifi0(442:440)` / `qnum_wifi1(445:443)`** per-idm-ring queue numbers (tm.c:66522-66523) alongside `qnum_uni0..4`/`qnum_pon` |
| `cla_info_show` "desIn"/"desOut" | tm.c:67958-68150, regs `0xe30e5`/`0xe30f8`+ | `ssid_in` = word2 bits[3:1] (tm.c:67993/68088), **`ssid_out` = word3 bits[19:17]** (tm.c:68013/68109), `ssid_flag` = word8 bit13 (tm.c:68048), `Outport` = word6 bits[26:23] (4-bit scalar, tm.c:68039), `Da_known` = word6 bit22 (tm.c:68038, adjacent to Outport) |
| `pm_info_show` "des" | tm.c:63992-64157, regs `0xe702e`+ | `ssid_flag`=local_4c bit2 (tm.c:64104), `outport`=4-bit (local_4c bit0 \| local_50[31:29], tm.c:64102), `ssid_in`=local_3c bits[8:6] (tm.c:64139), `ssid_out`=local_40 byte2&7 (tm.c:64129) |

Key structural fact for implementers: **the CLA desIn/desOut `Outport` field is only 4 bits**
(0-15) while **the PrintBrgDesc post-bridge `outport` field is 10 bits** and looks like a
port/ring *bitmap* rather than a scalar (it sits beside per-egress-class queue numbers for every
physical class including `qnum_wifi0/1` — consistent with flooding support, where multiple bits
can be set at once). These are **two different representations at two different pipeline stages**,
not the same field re-read — don't conflate them.

🟡 DERIVED cross-check: `bit(67:65)` in `PrintBrgDesc`'s global numbering = word2 bits[3:1] under
the CLA descriptor's own word framing (bit 65 = 32×2+1, bit 67 = 32×2+3) — **exactly** matches
`cla_info_show`'s independently-decoded `ssid_in = word2[3:1]`. This is not a coincidence; it's the
same field observed from two different debug commands, and it's the strongest evidence in this
whole document that the bit positions above are real and not decompiler noise.

---

## 4. CLA classifier entry (ram2-6, the hardfast flow-offload table) — ✅ CONFIRMED: **no ssid field**

This extends `zte-cla-ram-layout.md` (already documents ram_id map, inport decode, hash-slot
mechanics — not repeated here) with the one new fact needed for Stage 3.

The stored entry's SW-side debug decoder, `cla_set_hash_table` (tm.c:3366-3550), prints **every
byte** of the 60-byte (15-word) entry with a named field — `inport`, `outport`, `flow_pri`,
`wan_id`, `qid_dscp_en/ram_idx`, `da_known`, `valid_en`, `direct`, `rule_mode`, `extr_index`,
`pppoe_flag`, `l2_type`, `tag_level`, `flow_rp_en`, `vlan_rp_en`, `modify_en`,
`pkt_len_changed`, `e8_en`, `cmd_flow_id`, `tcnt_gpid_rp_en`, `gemport_uni_id`, `qos_rp_en`,
`qos_id`, `adm_bucket_rp_en`, `bucket_info`, `mtu_rp_en`, `mtu_val`, `cpu_qid_rp_en`, `cpu_qid`,
`tcont_id`, `queue_rp_en`, `queue_id`, `act_rp_en`, `act_val` — plus 20 raw `windataN` halfwords
that are the classification-key `extra_data` bytes (already covered by the hash-key doc,
`zte-cla-hw-hash-engine.md`). **`ssid` / `ssid_out` appears in none of these names**, and the
bytes immediately around `outport` (0xc, 0xd) are fully consumed by `outport`(5 bits, split
`byte0xd[1:0]<<3 | byte0xc[7:5]`, tm.c:3401) + `flow_pri`(6 bits) + `inport`(12 bits, per the
existing memory) + `wan_id`(5 bits) — zero spare bits.

**`outport` is 5 bits (0-31)**, wider than the 4-bit scalar seen in the *descriptor's* `Outport`
(§3) — this 5-bit width is the interesting clue for Stage 3 (see 🟡 hypothesis below), since ports
0-7 alone would only need 3 bits.

> **✅ RESOLVED 2026-07-07 by stock-live correlation (see `findings/wifi_stage3_stock_ssid_correlation_2026-07-07.md`, commit 246621e29): the value/range was RIGHT (`0x10 | (idm_ring<<3) | ssid`, e.g. 0x1c = idm1/port7/SSID4) but the FIELD was WRONG — the essid is stored in the CLA flow's `gemport_uni_id` (CLA entry bytes 1-2: `param_2[2]<<4 | param_2[1]>>4`), NOT in `outport` (which stock leaves = 0). So a mainline WiFi flow must pack `gemport_uni_id` with `0x10|(ring<<3)|ssid` and leave `outport=0`. The hypothesis below is preserved for history but is superseded on the field-location point.**

### 🟡 Hypothesis (not confirmed) — `outport` may already be wide enough to fold ssid in via value range

The FDB job (§2, §5) independently confirmed a **real, exact** SW-side "logical WLAN port" numbering
used elsewhere in this codebase: `get_sw_port_from_devname` (decomp_all_switch.c ~4549-4568) computes,
for a WLAN devname, **logical port = `0x10 + ssid` for idm0/port6, or `0x18 + ssid` for idm1/port7**
— i.e. `essid = 0x10 | (idm_ring << 3) | ssid`, range 0x10-0x1f. **A 5-bit CLA `outport` field can
hold exactly this range (0-0x1f).** If the CLA flow installer uses this *same* logical-port
numbering (rather than the raw physical 0-7) when writing a hardfast entry's `outport` for a
WiFi-destined flow, then **no separate ssid_out storage is needed at all — `outport` alone
(values 0x10-0x1f) IS the (ring,ssid) encoding**, and the pipeline's per-descriptor `ssid_out`/
`Outport` fields (§3) would simply be HW's decode of that logical value back into (physical
port, ssid) for downstream stages.

This is an elegant, well-grounded hypothesis (it reuses a numbering scheme *proven to exist* for
exactly this purpose in another part of the same codebase) but **I found no source line that
proves the CLA installer actually writes 0x10-0x1f into `outport` for a WiFi flow** — every call
site of the fast-flow installer inspected in the existing NAT-offload research
(`findings/nat_offload_re_2026-07-03.md`) only exercises LAN/WAN ports 0-5. **Flag as open; do not
program a live CLA entry with `outport=0x10+ssid` without a bench confirmation first** (a wrong
value here would misroute or corrupt a real hardfast flow).

### PM `flow_info`/`next_hop` — ✅ CONFIRMED: no outport, no ssid, at all (existing research, cross-checked here)

`findings/nat_offload_re_2026-07-03.md` already fully bit-decodes PM's 3-word `flow_info` (ram_id 0)
and 3-word `next_hop` (ram_id 1) entries — every bit of both is accounted for (NAT enable bits,
port replacement values, MAC/IP next-hop) and **neither has an outport or ssid field**. This means:
**the egress port/ssid decision for a hardfast flow is entirely a CLA-side concern; PM only rewrites
NAT fields once CLA has already decided where the packet goes.** So there is nothing to add to PM
for Stage 3 — §4's CLA `outport` field (scalar or, per the open hypothesis, logical-port-encoded)
is the only stored-table location that could ever carry the WiFi destination.

---

## 5. The glue path — idmfdb.ko contract (✅ CONFIRMED contract; a few internal offsets ❓ open)

Everything below is independently re-derived and cross-checked (my own read of
`decomp_all_idmfdb.c` + `decomp_all_plat_zxylzb_9128S.c`, and a second, independent pass by a
delegated agent — both agree on every point that overlaps).

### Hook wiring

`idm_fdb_init` (idmfdb.c:1868+) sets **`idm_skb_recv = idm_fdb_forward`**. Plat's IDM RX poll
(`idm_net_poll`, plat.c:4132-4138) calls `(*idm_skb_recv)(idm_ring, skb)` per packet — falling back
to plain `netif_receive_skb` if unset (= mainline's current behavior).

### RX dispatch: `idm_fdb_forward(uint idm, struct sk_buff *skb)` (idmfdb.c:60-162)

- `ssid = skb->cb[0xb7]` (already decoded by plat's IDM RX, §1) (idmfdb.c:76).
- Unicast (DA bit0 clear) + `ssid<8`: **`node_index = ssid + idm*8`** — a flat 16-slot table
  (`fdb_list`, stride 0x128 bytes; 2 idm rings × 8 ssid = 16, idmfdb.c:81-82). Requires
  `node.enabled` and the registered WLAN netdev's `IFF_UP`; sets `skb->dev = wlan_netdev` and
  **direct-dispatches** into the WiFi driver via `dev->netdev_ops->ndo_start_xmit(skb, dev)`
  (a raw function-pointer call, bypassing qdisc/bridge/netfilter entirely — idmfdb.c:110).
- Multicast/broadcast, or `ssid==0xff` (the RX "invalid" sentinel, §1): flooded via
  `idm_fdb_multi_send_handle(idm, ssid, skb, cast)` (idmfdb.c:724+) — per-idm flood-group tables,
  IPv4/IPv6 multicast-to-unicast translation ("MTRANS": DMAC rewrite before each per-target
  `skb_copy`+xmit), broadcast/unknown-ssid floods the whole idm's group.

### Registration: `register_idm_fdb_node(int wlan_index, struct net_device *wlan_dev)` (idmfdb.c:277-319)

- `node_index = ssid + idm*8` computed via an **external** map `WlanIndex2WlanIdmMap(wlan_index)`
  (returns a struct with idm at byte+0x25, ssid at byte+0x26 — the exporting module is not in the
  provided decomp set; ❓ open, not resolvable device-free with what's on disk today).
- Populates `fdb_list[node_index]`: `enabled=1`, `wlan_dev = wlan_dev` (the passed netdev),
  `idm_dev = __dev_get_by_name("idm%d")` (the corresponding IDM ring netdev), plus a type byte from
  the map struct's +0x22. Returns the node pointer, which the caller (the WLAN driver / its glue)
  is expected to hold and pass back into the TX-injection functions below.

### TX injection (WLAN RX → switch fabric): `idm_fdb_recv_handle` / `wlan_recv_idm_handle` (byte-identical twins, idmfdb.c:1-57 / 529-585)

Called by the WLAN driver as `f(struct idm_fdb_node *node, struct sk_buff *skb)` when a frame
arrives over the air and needs to enter the switch:
- **writes `skb->cb[0xb7] = node->ssid`** (idmfdb.c:16/544) — this is the *write* side of the same
  byte §1's TX descriptor reads;
- requires `node.enabled`, `node.idm_dev` set, and a `forbidIdm` flag clear;
- sets `skb->dev = node->wlan_dev`... **counter-intuitively this then calls the netdev_ops of
  `*(param_1+0x10)` = `node->idm_dev`**, i.e. it dispatches into `idm_net_tx` (§1's TX packer),
  which is what actually reads `skb->cb[0xb7]` back out to build the descriptor's `ssid<<28` field.

### `idm_fdb_hook_xmit(struct sk_buff *skb)` (idmfdb.c:165-206) — NOT a transmit/stamping function

Despite the name, this is a **SW MAC-learning tap only**: it returns immediately if the skb came
*from* the IDM ring itself (guarded by `skb->cb[0xbc] & 0x10`, the recycled-pool flag set by plat's
RX refill — prevents re-learning frames the switch just delivered), otherwise calls
**`ffe_learn_skb(skb, 3)`** — the kernel-builtin fast-forwarding-engine's flow learner (not present
in the provided .ko decomps; it's a vmlinux-builtin import, same as `ffe_get_npu_enable`). This
function does **not** touch `skb->cb[0xb7]` or the IDM TX ring directly — that earlier
one-line characterization in `wifi_offload_feasibility_2026-07-04.md` ("stamps skb[0xb7]=ssid...
pushes into the IDM TX ring") is **superseded**: the ssid-stamp-and-push-to-ring behavior belongs
to `idm_fdb_recv_handle`/`wlan_recv_idm_handle` (above), while `idm_fdb_hook_xmit` is purely a
learning hook that feeds the same SW flow-cache tm.ko's NPU backend later promotes to CLA hardfast
entries — the two are separate exported hooks with separate jobs, both presumably called by the
WLAN driver on every upstream RX (one for learning, one for the actual fabric injection).

### The SW-side (idm_port, essid, devname) config table — ✅ CONFIRMED, purely CPU-side

`s_aclWlanToIdmEssidMap`, 16 entries × 0x12 bytes (tm.c, `aclWLANToIDMEssidCfg`/`...Cfg2`/
`...Map`/`...Map2`, tm.c:50058-50227): `[0]`=idm_port (validated ∈{6,7} — the *physical* fabric
port number, not the 0/1 ring index), `[1]`=essid (validated ∈[0x10,0x1f] — see §4's logical-port
numbering), `[2..0x10]`=interface name string. Populated at init by `sw_init_wlan_ssid`
(decomp_all_switch.c:5112, 16 slots of 0x29 bytes read from a radio config block: byte+0x24 picks
idm_port 6/7, byte+0x26 gives ssid). Consumed by the SW fallback RX path
`pdt_ethdrv_recv` (decomp_all_switch.c:651: `aclEssidToWlanIDMMap2(skb->port+1)` → devname →
`dev_get_by_name` → `netif_rx`) — i.e. this table is genuinely CPU-side plumbing for the
software-forwarded case, a sibling/predecessor of idmfdb.ko's own `fdb_list`, not something a
mainline driver needs to replicate bit-for-bit — but its **existence and (idm_port, essid) shape**
is the strongest evidence for §4's `outport = 0x10+ssid` hypothesis, since it's the same
16-slot/(idm,ssid) shape reappearing for the third time in this codebase (here, in `fdb_list`, and
in `get_sw_port_from_devname`'s logical numbering).

### What mainline must build (summary, maps directly onto the gap analysis in `wifi_ap_bringup_and_regdb_fix_2026-07-07.md`)

1. `zx_idm_xmit` (zx-eth-main.c:1733+): OR in a clamped 3-bit ssid at bits[30:28] of word1, sourced
   from a per-skb tag set by whatever dispatches WLAN-RX frames toward the IDM ring — mainline has
   no `skb->cb[0xb7]` convention yet; needs one (or an equivalent side-channel).
2. `zx_idm_poll` (zx-eth-main.c:1621+): already decodes ssid (additive, 2026-07-07); the missing
   piece is a `(idm,ssid) → wlan netdev` dispatch table (mirroring `fdb_list[16]`) and a direct-xmit
   call replacing `napi_gro_receive` when a mapping exists — mirroring `idm_fdb_forward`.
3. A registration API (mirroring `register_idm_fdb_node`) for the WLAN vif driver (mt76/mac80211)
   to bind (idm_ring, ssid) → its netdev — likely a small sysfs/debugfs binding or a netdev
   notifier keyed by a naming convention, per the existing feasibility doc's step 4.
4. `zx_fdb_add` (zx-eth-main.c:668+): no change needed to the entry *format* (§2 proved there's no
   ssid field to add) — but the caller providing `port` for a WiFi client MAC should pass 6 or 7
   (one bit each), understanding that the FDB alone can never disambiguate ssid on that port; ssid
   resolution for such traffic must happen in the dispatcher (item 2), not the FDB.
5. CLA/PM flow builders: **do not add an ssid_out field** (there is none to add, §4) — if/when
   WiFi-destined hardfast flows are attempted, first bench-confirm §4's `outport=0x10+ssid`
   hypothesis on live silicon before trusting it in a real flow install (wrong value risks
   misrouting a real flow, unlike the purely-additive IDM RX/TX changes above).

---

## 6. Net effect on the Stage-3 plan (why this matters)

The 2026-07-04 feasibility scout assumed CLA hardfast entries carry `outport`+`ssid_out` together
("ingress port → CLA hash lookup (hardfast entry with `ssid_out`) or FDB DA lookup"). This RE pass
shows that's **not how the stored data is shaped**: `ssid_out` is real and lives in the *in-flight
descriptor* (§3), but neither of the two structures a mainline driver actually programs (CLA ram2-6,
§4; FDB, §2) has a place to put it directly — only a **logical outport value** (0x10-0x1f, unproven
but well-motivated, §4) could plausibly carry it through the CLA path, and the FDB path
(§2's open question) may rely on hardware doing something with FDB-A's 22 unaccounted bits that
software never needed to touch. Both of Stage 3's two forwarding avenues for a downstream
WiFi-bound HW-offloaded flow are therefore **less certain than the feasibility doc assumed**, and
the safest next concrete step is exactly what §2/§4 flag: a live raw read of a HW-learned WLAN
client's FDB-A entry (after real AP+STA association, no offload changes needed) to settle
hypothesis (1)/(2)/(3) in §2 before writing any HW-programming code — this is a read-only probe,
not a code change, and fits the project's existing debugfs tooling (`clapeek`/`fdbadd`/`pmpeek`).

---

## Source-cite index (file:line, for spot-checking)

- IDM RX desc: `decomp_all_plat_zxylzb_9128S.c:4008-4017` (dump), `:4090,4125-4131` (real code)
- IDM TX desc: `decomp_all_plat_zxylzb_9128S.c:4194-4203` (dump), `:4266-4270` (real code)
- IDM ring init / netdev order: `decomp_all_plat_zxylzb_9128S.c:4340-4418`, ring-index store `:3698`
- FDB-A (`pon_pp_add_mac`/`brg_ram_set`/`get`): `decomp_all_plat_zxylzb_9128S.c:4548-4794`
- FDB-B (`sbrg_add_mactable`/`sbrg_lookup_mactable`): `decomp_all_tm.c:10549-10840`, indirect write
  `sbrg_set_indreg_wr`:8422, CMD `sbrg_set_indreg_cmd`:8339, bounds `sbrg_set/get_ind_access_data`:5906/5935
- FDB portmask remap: `decomp_all_tm.c:40548` (`tm_mactable_add_set`), dump `:8534`
  (`sbrg_print_mactable`), static-add API `:56143-56184` (`zte_api_sw_mac_add_port_macaddress`)
- Pipeline descriptor dumps: `decomp_all_tm.c:63992-64157` (`pm_info_show`),
  `:66260-66528` (`PrintBrgDesc`), `:67825-68150+` (`cla_info_show` desIn/desOut)
- CLA stored entry field dump: `decomp_all_tm.c:3366-3550` (`cla_set_hash_table`)
- PM flow_info/next_hop: `findings/nat_offload_re_2026-07-03.md` §§2-3 (pre-existing, cross-checked)
- SW essid/idm map: `decomp_all_tm.c:50058-50227` (`aclWLANToIDMEssidCfg*`/`aclEssidToWlanIDMMap*`),
  init `decomp_all_switch.c:5112` (`sw_init_wlan_ssid`), consumer `decomp_all_switch.c:651`
  (`pdt_ethdrv_recv`), logical-port formula `decomp_all_switch.c` ~4549-4568
  (`get_sw_port_from_devname`)
- idmfdb.ko: hook install `decomp_all_idmfdb.c:1868+`; RX dispatch `idm_fdb_forward` :60-162;
  registration `register_idm_fdb_node` :277-319; TX injection `idm_fdb_recv_handle`/
  `wlan_recv_idm_handle` :1-57/529-585; learning tap `idm_fdb_hook_xmit` :165-206; flood
  `idm_fdb_multi_send_handle` :724-1105
- Mainline gap points: `zx-eth-main.c` `zx_idm_poll`:1621-1707, `zx_idm_xmit`:1733-1780,
  `zx_fdb_add`:668-722, IDM desc macros :304-306

## Open questions (do not guess past these)

1. Whether HW-autonomous FDB-A learn writes ssid into the unaccounted reg-0x4e bits[31:10] (§2).
2. Whether ssid_out on a plain DA/FDB hit is VLAN-derived, HW-side-only, or simply never populated
   for non-CLA-flow WiFi traffic (§2, three hypotheses listed, none confirmed).
3. Whether CLA's stored `outport` (5 bits) is ever written with the 0x10-0x1f logical-port value
   for a real WiFi hardfast flow, or whether stock never actually builds such a flow at all (§4).
4. `WlanIndex2WlanIdmMap`/`IfName2WlanIdmMap` internals — exporting module not present in the
   decomp set on disk (§5).
5. Exact writer of `fdb_list[node].idm`/`.ssid` byte fields inside `register_idm_fdb_node` — read
   in three places, write site not located in the provided idmfdb.c decomp (§5).
6. `ffe_learn_skb`/`ffe_get_npu_enable` internals — vmlinux-builtin, not in any .ko decomp provided.
