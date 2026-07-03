# WAN-port role / mflow-config RE — do the two runtime WAN-bring-up switch calls program HW state mainline is missing?

Date: 2026-07-03
Mode: device-free static RE (read-only). No device, no sub-agents, no code edits, no commits.
Sources: `tasks/00.10.02.re-stock-kmods/findings/decomp_all_switch.c`, `decomp_all_tm.c`;
mainline driver `linux-v6.6/drivers/net/ethernet/zte/{zx-eth-main.c, zx-fpga-reg-tables.h, zx_stock_table.h, zx_stock_bursts.h}`.
Complements the concurrent device A/B test.

## TL;DR (the answer)

The two runtime calls surfaced by the userspace bring-up trace are **NOT the WAN-ingress-lookup gate**. Breakdown:

| Function | Real / stub | HW footprint | Missing on mainline? |
|---|---|---|---|
| `ethdrv_set_wanportid` | SW-only | writes SW global `g_sw_netInfo[0x2c]`; **no HW write** | N/A (no HW) |
| `sw_other_set_wan_lan_switch` | **REAL HW** | `PON_PP_TM_CFG` (fpga idx `0xe8007` = phys **`0x923a001c`**) bits[29:25] = per-port WAN designation; sets bit `25+physport` for the WAN port | **NO — already present**: mainline replays `0x923a001c = 0x21200000` (bit29 set = physport4/MAC4/lan4 = WAN). Live-confirmed matching stock (see zte-tx-egress-blocker) |
| `sw_set_mflow_config` | **STUB** (`return 0;`) | none | N/A (stub) |
| `sw_acl_add_port_flowconfig` | **REAL HW** | per-**flow** CLA ACL rule via `zte_api_sw_qos_add_port_streamselect` (parse+oper+rule install); carries a `direction` field (0=up/1=down) | Not part of default WAN L3 forwarding; only fires when userspace pushes a specific mflow/ACL rule. Not the basic-forwarding gate |

**Conclusion:** the WAN-port *role* HW register (`PON_PP_TM_CFG` bit29) is **already correctly set on mainline** via the stock-replay table, for the exact WAN port used in the download test (lan4 = MAC4 = physport4). So this axis does **not** explain the ~86% WAN-ingress lookup miss. This **closes leads (1) and (2)** left open in `reference_wan_qos_bringup_sequence_2026-07-03.md` and **reinforces VERDICT B** (engine-level WAN-ingress lookup miss below key/slot, from `wan_ingress_perpacket_key` / `stock_wan_ingress_l3en_arm_RE`).

---

## 1. `ethdrv_set_wanportid` — SW-only, no HW

decomp_all_switch.c:290
```c
void ethdrv_set_wanportid(undefined1 param_1)
{
  g_sw_netInfo[0x2c] = param_1;   /* store WAN port id in the SW netInfo blob */
  return;
}
```
Pure software: stashes the WAN port id byte. No register/table write. Nothing for the driver to replicate.

## 2. `sw_other_set_wan_lan_switch` — REAL HW: the WAN-port designation register

decomp_all_switch.c:4366. The relevant HW-touching path (mode < 2 = "WAN or AUTO", and the `eth%d → WAN` case) does:

```c
cVar1 = zte_api_sw_mac_set_port_macfiltermode[wanLogicPort];  /* logical→phys(macfilter) port */
_tm_vlan_check_ena_set = (uint)(byte)cVar1;                   /* = g_sw_cap.sw_wan_port */
uVar5 = fpga_read_reg(0xe8007);
fpga_write_reg(0xe8007, uVar5 & 0xc1ffffff);                  /* CLEAR bits [29:25] (all WAN-port flags) */
tm_set_p2pmode((uint)(byte)cVar1);                            /* then SET the one WAN port's bit */
wan_to_lan = ...; _zte_api_sw_mac_set_port_learnlimit |= 0x1f;
```

`0xc1ffffff` = keep bits {31,30,24..0}, **clear bits [29:25]** — a 5-bit per-port WAN field (ports 0..4).

### The actual write — `tm_set_p2pmode` → `tm_set_pp_wan_cfg`

decomp_all_tm.c:35979 / 35962:
```c
undefined4 tm_set_p2pmode(uint param_1) {
  lan_up_port = param_1;                 /* global: the WAN phys(macfilter) port */
  tm_set_pp_wan_cfg(lan_up_port & 0xff);
  return 0;
}
void tm_set_pp_wan_cfg(int param_1) {    /* param_1 = WAN port */
  uVar1 = fpga_read_reg(0xe8007);        /* "PON_PP_TM_CFG=0x%x" */
  fpga_write_reg(0xe8007, uVar1 | 1 << (param_1 + 0x19U & 0xff));  /* set bit (port + 25) */
}
```

**Register:** `PON_PP_TM_CFG`. `fpga_read/write_reg(idx)` addresses phys `0x92000000 + idx*4`; idx `0xe8007` → **phys `0x923a001c`** (matches the zte-tx-egress-blocker live label "0x923a001c PON_PP_TM_CFG").

**Value for the WAN port:** bit `25 + physport`. For lan4/MAC4/physport4 → **bit29 (0x20000000)**. This is a PON-packet-processor/TM-config field UPSTREAM of the CLA that marks which ingress port is the WAN/uplink.

`lan_up_port` is also consumed at runtime when building CLA ACL rules — `tm_acl_v2.c` (decomp_all_tm.c:53364): for the uplink direction the rule's port field is set to `lan_up_port + 1`. That is a *per-rule* consumer, not additional boot HW state.

### Is mainline missing it? NO — it's already replayed

- `zx-fpga-reg-tables.h:71-76` shows the structured reg-ids for base_off `0xe8007` cover only bits via shift 4/6/8/9/10/24 — the WAN bits[29:25] fall inside reg_id13 (shift24, mask 0xff = bits[31:24]); they are **only** set via the raw replay value, not a named API.
- Mainline replays that raw value: `zx_stock_table.h:22172 { 0x1e001c, 0x21200000 }` (plus 7 strided mirrors 0x1e081c..0x1e381c) and `zx_stock_bursts.h:4195 ... 0x21200000` — walked by the stock-init replay walker (zx-eth-main.c:1014, "Stock-init replay walker"; table included at :74/:78).
- `0x21200000 & 0x3e000000 = 0x20000000` → **only bit29 set → physport4 = WAN**. Exactly right for lan4=MAC4=physport4 (zx-eth-main.c:223 "port 4 = MAC4 (RGMII WAN)").
- Empirically confirmed already: zte-tx-egress-blocker records live mainline `0x923a001c = 0x21200000` "matches stock".

⇒ The WAN role register is **byte-identical to stock on mainline** for the WAN port under test. `sw_other_set_wan_lan_switch`'s HW effect is present.

### Driver-comment reconciliation (fixes a latent mis-ID)

zx-eth-main.c:135-138, 1156-1159, 1369-1372 discuss "stock does `pp[0x2c] |= 1 << (lan_up_port + 0x19)`" and deliberately **skip** setting `BIT(25)` on the 8 per-port PP blocks (`pp + 0x0100 + inst*0x400 + 0x2c`, left at `0x106`). The `+0x19` shift and `lan_up_port` prove that comment is describing **this same stock write** — but it targets `tm_set_pp_wan_cfg`'s **single global `PON_PP_TM_CFG` (0x923a001c)**, *not* the per-port PP-block `+0x2c` registers the driver leaves alone. The driver's decision to skip the per-port `+0x2c` bit25 is harmless here **because the correct WAN bit (bit29) is set anyway via the `0x21200000` replay**. (Documenting so a future reader doesn't "fix" the wrong register.)

## 3. `sw_set_mflow_config` — STUB

decomp_all_switch.c:8046:
```c
undefined4 sw_set_mflow_config(void) { return 0; }
```
Registered as the port-vlan mflow handler (`sw_public_port_vlan_func_reg(..., sw_set_mflow_config)`, decomp_all_switch.c:1000). Does nothing in HW. Same class as `sw_wancip_set` (decomp_all_switch.c:4897, also `return 0;`). Nothing to replicate.

## 4. `sw_acl_add_port_flowconfig` — REAL, but per-flow ACL, not the WAN-ingress gate

decomp_all_switch.c:1193. Builds a 0x49c `FlowConfig` (fields: ruleType, rule_pri, index, **direction**@+4, match.entry[], fwd.fwdmode/desportmsk/gemport/des_q, action) and calls `zte_api_sw_qos_add_port_streamselect` (decomp_all_tm.c:63181). That routine:
- `tm_cla_get_parse_info` (decomp_all_tm.c:60764) — turns the FlowConfig into CLA parse info. **`direction` field (param+4)**: `0` = up (printk "TM_ACL_direction(0:up 1:down)"), `1` = down → sets `cla_parse_info[0x10]` and default srcport (`param_2[8]=5` for down). Invalid direction → returns error.
- `tm_cla_get_oper_info` + `tm_add_acl_flow_rule` (decomp_all_tm.c:54261) — installs the ACL flow rule (per-rule CLA slot via hash-poly + first-free `aclGetAvailableHashAddr`).

This is the **per-flow ACL/streamselect** path. It is invoked only when userspace pushes a specific mflow/ACL rule (`CmEthMflowConfig` → ioctl), NOT as part of default WAN L3 forwarding. Basic routed/NAT HW forwarding in the reference uses the L3 hardfast path (`hf_set_l3_entry`, npu hff) — a different engine. So this call does not program the default WAN-ingress L3 lookup either.

## Cross-reference: the up/down "direction" concept

There are three distinct "direction/WAN" notions; none is the missing per-port ingress-lookup selector:

1. **`FROM_WAN`/`TO_WAN`** (decomp_all_switch.c:1421/1436) — SW string helpers (`strncmp(name,"pon"/"ptm"/"eth")`) used in the host L3-hardfast session path. Not HW.
2. **`PON_PP_TM_CFG` bits[29:25]** — the real per-ingress-port WAN designation (§2). Already set on mainline.
3. **ACL `direction` 0:up/1:down** — a *per-rule* field in the ACL/streamselect install (§4), feeding `cla_parse_info[0x10]`. Per-rule, not per-port; and the ACL path isn't the default-forwarding lookup.

The mainline driver already makes the WAN key ingress-aware independently: `ZX_WAN_REGPORT 5` + `kb[4] |= 1` pos32 bit (zx-eth-main.c:2314/2358-2379) — the "is_wan" key bit (VERDICT B lineage). So both the WAN role register *and* the ingress-aware key are present on mainline.

---

## What the driver should add for lan4 — ranked by likelihood of fixing the ~86% miss

All four functions are accounted for and **none programs WAN-ingress-lookup state that mainline lacks.** The ranked recommendations:

1. **(HIGHEST, but a *verification* not a fix) Confirm `PON_PP_TM_CFG` on the current build.** On the device A/B, read phys **`0x923a001c`** live during the WAN download and confirm **bit29 (0x20000000) is set** (expected `0x21200000`). If — and only if — it reads 0 there (e.g. the replay entry got dropped for the current WAN port, or lan4 is remapped to a physport ≠ 4), then write the WAN bit: `w32 0x923a001c = (read | (1 << (25 + physport_of_lan4)))`. Static evidence says it is already `0x21200000` (bit29), so this is expected to be a **no-op confirmation** — its value is to *exclude* the role register as the cause, not to fix.

2. **(LOW) Try a per-WAN-port catch-all ACL FlowConfig** matching `sw_acl_add_port_flowconfig` with `direction=1` (down) for the WAN port, only as an experiment to see whether the reference's ACL/streamselect arms something the default hash path doesn't. Low likelihood — the reference forwards at ~99% without relying on this for basic transit, and the offload path is `hf_set_l3_entry`, not the ACL engine. Do not invest unless (1) and the A/B leave it open.

3. **(NOT a lever) `ethdrv_set_wanportid` / `sw_set_mflow_config`** — SW-only and stub respectively; nothing to add.

**Net:** this axis is exhausted. The ~86% WAN-ingress miss is not caused by a missing WAN role/classification register — it is the previously-proven VERDICT B engine-level lookup non-determinism (same key/slot/resident-valid entry, ~100% from LAN-ingress, ~14% from WAN/RGMII). The device A/B should treat `0x923a001c` as a quick exclusion check and keep the primary effort on the VERDICT B leads (clean same-5-tuple LAN-vs-WAN A/B; WAN DN ring-1 pipeline timing).
