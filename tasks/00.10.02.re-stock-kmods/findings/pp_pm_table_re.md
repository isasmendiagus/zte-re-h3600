# PP_PM (PP port-mapper) flow_info / sub_ram table — reverse engineering

Decodes the table the mainline driver replays blindly via `zx_pp_pm_apply_replay`.
Conclusion up front: **PP_PM is the per-FLOW packet-edit/NAT/rewrite descriptor RAM
(flow_info), indexed by flow_id 0..1023, NOT by ingress port. The captured table is
the all-disabled default state and is symmetric across all flows. It cannot
discriminate port1 → PP_PM is EXONERATED as the port1 ingress gate.**

---

## 1. The replay path (mainline)

`linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`

- `zx_pp_pm_apply_replay()` — line 1936. Loops `ZX_PM_INIT_TABLE_LEN` (=1025) entries,
  calling `zx_pp_pm_write_entry(ram_id, ram_addr, data[8])`.
- Table header `#include "zx_pm_table.h"` — line 1934. Struct
  `{ u32 ram_id; u32 ram_addr; u32 data[8]; }` × 1025 (`zx_pm_table.h:17-19`).
  Auto-generated from a stock `pm.bin` capture (`zx_pm_table.h:1-10`).
- Indirect interface (`zx-eth-main.c:1891-1928`):
  - `PP_PM_REG_CMD   = 0x1DC014`  (cmd = `addr | ram_id<<22 | rw<<27`)
  - `PP_PM_REG_DONE  = 0x1DC018`  (poll bit0)
  - `PP_PM_REG_DATA0 = 0x1DC01C`  (data slots 0..3, stride 4)
  - `PP_PM_REG_DATA4 = 0x1DC100`  (data slots 4..7, stride 4)
- `e->base` = npp_base = `0x921c0000` (`zx-eth-main.c:21`). So
  `0x921c0000 + 0x1DC014 = 0x9239C014` — **exactly** the DATASHEET `zx_pppmregtable`
  base (`DATASHEET.md:1026,1030`). The cmd encoding `addr + ram_id*0x400000 +
  rw*0x8000000` matches stock `pp_pm_set_indirect_cmd` (tm.ko @0x2c978,
  `pp_pm_set_indirect_cmd.c:30`). **Mainline writes the correct block at the correct
  address with the correct encoding.**

### Table contents (the whole 1025 entries)

| span | ram_id | ram_addr | data[0] | data[1..7] | meaning |
|---|---|---|---|---|---|
| entry 0       | 3 | 0x000        | `0x00010000` | 0 | flow_info, flow_id 0 |
| entries 1..1023 | 3 | 0x001..0x3ff | `0x00810000` | 0 | flow_info, flow_id 1..1023 |
| entry 1024    | 6 | 0x000        | `0xfc000000` | `data[1]=0x00001fff`, rest 0 | sub_ram, index 0 |

So the table = **1024 flow_info entries (ram_id=3, the full 0..0x3FF flow_id space) +
1 sub_ram entry (ram_id=6, index 0)**. It is purely the RAM's default/reset image;
there is no per-port content.

---

## 2. Entry semantics (decoded from stock tm.ko)

### ram_id=3 → flow_info (`pp_pm_set_flow_info` @0x2cfb8)

The flow_info write takes `(dir, flow_ram_addr, byte[] fields)` and writes 3 data
words (the cmd validates `flow_ram_addr <= 0x3FF` and `dir < 2`,
`pp_pm_set_flow_info.c:36-38`). Fields (from the debug printk,
`pp_pm_set_flow_info.c:22-32` / `pp_pm_set_external_flow_info` printk
`decomp_all_tm.c:18545-18556`):

```
dir, flow_ram_addr (=flow_id), sub_ram_index, next_hop_idx,
dmac_en, smac_en, nat_dport, nat_sport, hl_ttl_en,
tcp_udp_chk_en, ip_chk_en, dport_en, sport_en, dip_en, sip_en,
subnet_id, pri_dscp_tc_en, flow_pri_en, flow_pri, sport, dport
```

This is a **per-flow packet EDIT / NAT / header-rewrite + forwarding descriptor**:
MAC rewrite, L3/L4 NAT (sip/dip/sport/dport rewrite + checksum regen), TTL decrement,
DSCP/priority remap, a `next_hop_idx` and a `sub_ram_index` pointer. It is the action
side of the pipeline — applied to a frame *after* the classifier (CLA) has assigned it
a `flow_id`.

Decoding the two captured data[0] values (all of data[1..7]=0):
- flow 0    = `0x00010000`: every enable bit (dmac/smac/nat/chk/port-match/dscp/pri) = 0.
- flows 1.. = `0x00810000`: identical, plus bit23 (`0x800000`) set — a single
  "valid/default-present" status bit. All action enables still 0.

**Net: every flow_info entry is a no-op passthrough descriptor.** No rewrite, no NAT,
no drop — frames hitting any of these default flows are forwarded unmodified.

### ram_id=6 → sub_ram (`pp_pm_set_sub_ram_info` @0x2e808)

`(sub_index, word[2])`, validates `sub_index < 0x400` (`pp_pm_set_sub_ram_info.c:37`).
Fields: `dscp_tc_val, dscp_tc_en, dei_en, dslite_en, pppoe_en, v6rd_en, cmd_addr,
vlan_addr, modi_dat_addr, swap_en` (`pp_pm_set_sub_ram_info.c:24-34`). A secondary
modify table (DSCP/DEI/PPPoE/DS-Lite/6rd/VLAN-modify pointers) referenced by
flow_info's `sub_ram_index`. The single captured entry (index 0,
`0xfc000000`/`0x00001fff`) has all modify-enables = 0 → also a no-op default.

### Other PP_PM RAM ids (ram_id selector, `<0x20`)

The same indirect block addresses many sub-RAMs by `ram_id`: `0xc`=ONU/CPU-MAC
(`zx_pp_pm_set_cpu_mac`, `zx-eth-main.c:1960`), plus modify/vlan-modify/next-hop/
pri/cmd/pppoe-session/aftr-ipv6/b4-ipv6/v6rd/e8-qos RAMs (see
`ghidra/output_ko/tm.ko/pp_pm_set_*_ram_info.c`). The replay only touches ram_id 3
and 6.

---

## 3. Is PP_PM per-INGRESS-PORT? — NO

- flow_info is indexed by **flow_id** (`flow_ram_addr`, 0..1023), never by a port,
  regport, or UNI. There is **no port field anywhere** in the flow_info or sub_ram
  layouts (verified against both `pp_pm_set_flow_info` and the more verbose
  `pp_pm_set_external_flow_info` printk, `decomp_all_tm.c:18545-18556`).
- The only directionality is `dir` (0 = upstream/UNI→GEM, 1/2 = downstream), which is
  global, not per-port.
- The flow_id that selects a flow_info entry is produced *upstream* by the classifier
  (CLA) — that is the block that is keyed on inport/regport. PP_PM merely executes the
  edit action for whatever flow_id arrives.
- All 1024 captured flow_info entries are identical no-ops (bit23 aside). A frame from
  port0, port1, port2 or port3 that resolves to the same default flow gets identical
  (null) treatment. There is no way for this table to drop or mis-route one specific
  ingress port while passing the others.

→ **PP_PM cannot be the port1-discriminating gate.**

---

## 4. PP vs PP_PM vs PM disambiguation

Three distinct blocks (do not conflate):

| name | base | role | indexed by |
|---|---|---|---|
| **PP** | 0x92380000 (`PP ctrl`, DATASHEET.md:219) | top-level packet-processor control (CPU-fwd bit etc.) | global ctrl |
| **PM** (G.988 port-mapper) | 0x921e0000 (DATASHEET.md:628-650) | source→allowed-egress **authorizer**: in-port/out-port rule_valid, g988 mode, inport==outport, cpu-not-drop. THIS is the per-port block. | **per (in_port, out_port)** |
| **PP_PM** (PP port-mapper) | 0x9239c000 (DATASHEET.md:1024) = npp+0x1DC000 | per-flow packet **edit/NAT/rewrite** descriptor RAM (flow_info + sub_ram + modify/next-hop/cpu-mac sub-RAMs) | **per flow_id** |

- "PM" and "PP_PM" share the confusing "port-mapper" label but are unrelated hardware:
  PM is the G.988 ingress/egress port-permission matrix (the genuinely per-port one,
  init'd by `tm_pon_npp_pm_initial` @0x4eee8, which loops ports 0..7 calling
  `pm_set_in_port_rule_valid`/`pm_set_out_port_rule_valid`). PP_PM is the flow-action
  RAM (no port concept).
- **PP_BRG / SBRAG** (0x92388000, DATASHEET.md:220,841) is the L2 bridge
  (FDB/VLAN/flood/isolation) — again a distinct block. Not PP_PM.

So the per-port suspects are **PM** and **PP_BRG/SBRAG**, not PP_PM. (Both already
marked verified-stock-faithful / not-the-gate in the DATASHEET notes.)

---

## 5. Does mainline replay it faithfully & symmetrically? — YES

- Bit-exact: the C array is generated from the stock `pm.bin` capture with no semantic
  change (`zx_pm_table.h:4-6`).
- Correct block/address/encoding (§1).
- **Symmetric across ports/flows**: unlike the CLA concern, this table is *not* biased
  to the capture-time active port. flow_info entries 1..1023 are byte-identical; flow 0
  differs only by lacking bit23. There is no port-specific or capture-port-specific
  entry. Replaying it can neither help nor hurt any single port relative to the others.
- Caveat (not a port-1 issue): mainline replays only the **default** flow_info image.
  The stock driver fills *real* flow_info entries dynamically on service provisioning
  via `operInfoAdd` (`decomp_all_tm.c:1373`) — mainline does not run that ONT service
  stack, but for a plain L2 switch with default passthrough flows this is the intended
  state.

---

## 6. Hypothesis verdict: PP_PM EXONERATED for port1

PP_PM is a per-flow, port-agnostic, action-only RAM, replayed bit-exactly and
symmetrically, with every replayed entry a no-op. There is no field, index, or value in
the captured table that could single out port1's ingress→CPU path. **It is not the
port1 gate; no PP_PM-based test is warranted.**

Redirect the port1 investigation to genuinely per-(in)port surfaces:
- **PM (G.988) in_port_rule_valid / g988 rule RAM** (0x921e0180 / 0x921e0248) — the
  real per-ingress-port authorizer. Confirm port1's in-port rule + g988 entry are
  present and identical to ports 0/2/3 on the live device.
- **CLA per-inport hash RAMs** (already covered — ram2..6 per-inport, regport2=port1
  covered identically, CLA exonerated per MEMORY).
- **SPA per-port enables** (`spa_set_up_reg_pkt_en`/`dn_reg_pkt_en`/`pkt_filter`,
  looped per port in `tm_pon_npp_spa_initial.c:35-63`).
- Given ports 0/2/3 work with identical flat config and port1 is uniquely broken with no
  per-port divergence found in PP_PM/CLA/PP_BRG, the anomaly is most consistent with a
  PHY/MAC-layer or PM-rule asymmetry for port1, not a fabric-action table.
