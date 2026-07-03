# Reference-firmware WAN / routing / QoS bring-up sequence (userspace "what & when")

Date: 2026-07-03
Scope: DEVICE-FREE static analysis of the vendor rootfs `/home/ubuntu/Projects/MYSELF/ZTE/ext/rootfs/`.
Read-only. Complements the concurrent kernel-module ("how") analysis — this maps the userspace
high-level configuration flow and the switch-config calls it makes at WAN/routing/QoS bring-up, and
ranks the runtime init step most likely to be the missing prerequisite for **downlink (WAN-ingress)
L3 acceleration** (`l3_en=0` symptom).

---

## 0. TL;DR — the ranked answer

The reference firmware performs several **runtime** switch-configuration steps when the WAN link/IP
comes up that a minimal "assign IP + route in the Linux kernel" driver has no equivalent for. Ranked
by likelihood of being the missing prerequisite for WAN-ingress L3 acceleration:

1. **WAN-port L3 role designation** — `ethdrv_set_wanportid()` / ioctl `sw_other_set_wan_lan_switch`
   (switch.ko). Tells the switch which physical/logical port is the routed WAN uplink
   (`g_sw_cap.sw_wan_port` / `ptSwInfo->wan_logicport`). This is what makes the ingress parser treat
   that port as `FROM_WAN` and apply the **downstream** L3 parse/capability path
   (`npu_ipv4_l3tcpdown_cap` / `npu_ipv4_l3udpdown_cap` / `npu_ipv4_mc_down_cap`). Without it, the
   parser has no reason to set `l3_en` on WAN-ingress → exactly the observed `l3_en=0`.
2. **Per-WAN-port ingress ACL FlowConfig ("mflow")** — `switchAdapterMflowConfSet` →
   `CmEthMflowConfig` → ioctl `sw_acl_add_port_flowconfig` / `sw_set_mflow_config`. Installs a
   per-port classification rule (`FlowConfig.direction`, `FlowConfig.fwd.fwdmode`, match entries).
   Installed at runtime (not a static register), so it is consistent with "static config identical".
3. **WAN L3-interface IP registration** — ioctl `sw_wancip_set` (WAN Connection IP). Registers the
   dynamically-acquired WAN IP into the switch as an L3 interface, the downlink analogue of the LAN
   IP that already lets uplink work.
4. **WAN QoS / trust-queue provisioning** — `sw_set_wanport_qos`, `sw_qos_set_trustppqueue`
   (`ethSetTrustppQueue`), `QQZyterHWShaperConfig` / `QQZyterHWIFActive`. Lower likelihood as the
   direct `l3_en` cause, but the accelerated path needs a valid egress queue; worth confirming it is
   not a gating prerequisite.
5. **Per-route/nexthop L3 entry** — `hf_set_l3_entry` (`hf_query_l3_status`, nexthop RAM
   `dev_attr_nextHopInfo`). Almost certainly driven kernel-side from FIB/neigh events; listed for
   completeness (the kernel-side agent owns this).

### IMPORTANT reconciliation with prior kernel-side decomp (read before acting)

A prior device-free decomp RE (memory `zte-flowoffload-framework`,
`findings/stock_wan_ingress_l3en_arm_RE_2026-07-03.md`) already established, kernel-side:

- **`sw_wancip_set/get/del` (ioctls 0x410/0x411/0x412) are pure stubs `return 0;`** → hypothesis #3
  (WAN-IP registration) is **already refuted**: the userspace calls it, but the HW ioctl does
  nothing. Do **not** pursue wancip as the fix. Retained below only for completeness.
- `cla_set_local_ipv4_addr`, `cla_set_up/dn_l3_default_flow_cfg` (claReg 0x1e–0x24) have **zero
  callers** in either .ko → no HW WAN-IP/route table is programmed by stock either.
- That RE also reinterprets `l3_en=0`: trap reason `0x54 LOOK_UP_MISS` is *inside* the CLA hash
  lookup, so those packets were L3-submitted then missed the hash; the single `l3_en=0` descriptor
  read is judged a noisy/shared latch. Its verdict: the gate is a WAN/RGMII-ingress **engine-level
  hash-lookup miss** (same key/slot/resident-valid entry; 100% from LAN-ingress, ~14% from WAN),
  **not** fixable by any static table write.

**What this userspace analysis adds that is NOT yet closed kernel-side:** the prior RE examined the
WAN-*IP*/route/CLA-default-flow table surface. It did **not** close out two other runtime bring-up
calls this userspace trace surfaced — the **WAN-port role designation** (`ethdrv_set_wanportid` /
`sw_other_set_wan_lan_switch`) and the **per-WAN-port ingress ACL FlowConfig**
(`switchAdapterMflowConfSet` → `sw_set_mflow_config` / `sw_acl_add_port_flowconfig`). These touch the
ingress **port role / classification** stage (which feeds the parse + lookup pipeline), a different
axis from the WAN-IP tables already ruled out. They are the concrete next things for the kernel agent
to check: are they also stubs, and does the WAN-port role feed the WAN-ingress lookup pipeline the
prior RE found non-deterministic? If either is a real HW write that mainline omits, it is a candidate
for the residual ~86% WAN-ingress miss.

---

## 1. Architecture of the reference config plane

### Boot / process launch
- `/etc/rc` → `/etc/init.norm` (normal mode). init.norm inserts the switch stack in order:
  `plat-zxylzb_9128S.ko` → `tm.ko` → `switch.ko`, brings up `pon`/`sw`/`idm0`/`idm1`, does the FPGA
  SerDes register writes (`fpga -w …`), then launches the master config daemon: **`pc &`**.
- The main configuration/service daemon is **`bin/cspd`** (2.8 MB, not stripped) — it owns WAN,
  routing, DHCP/PPP, DNS, firewall, QoS and the switch adapter. `bin/pc`, `bin/cliagent`,
  `bin/controllerd`, `bin/dmsd` are the process-control / CLI / management peers.
- **Dead leftover:** `/etc/rdpa_dm_init.sh` uses Broadcom `bs /bdmf/...` (RDPA/Runner) commands, but
  there is **no `bs` binary** in the image and nothing invokes the script (only self-referenced). It
  is cross-platform cruft; ignore it. The real datapath is `tm.ko`/`switch.ko` (ZX279128S).

### Control interfaces to the switch (what userspace pokes)
| Interface | Owner | Purpose |
|---|---|---|
| `/dev/switch_dev` ioctl (`ethdrv_port_dev_ioctl` → `sw_*` handlers) | switch.ko | main switch config API (VLAN, MAC, port, QoS, ACL/flow, L3 hardfast, wancip, wan/lan role) |
| `/proc/zte/sys/ffe/cmd` (alias `/proc/ffe/cmd`) | FFE engine | **master HW-accel toggle**: `echo ffe 1 > …` enable, `echo ffe 0`/`npu 0 > …` disable (`cat …/ffeinfo` = status) |
| tm.ko sysfs `dev_attr_*` | tm.ko | L3/fast capacity + nexthop/flow debug: `setmaxl3entry [up][dn]`, `setmaxfastentry [enable][upnum][dnnum]`, `nextHopInfo`, `flowInfo`, `flowInfoList` |

### Userspace API stack (call chain)
```
cspd  ─┬─ libcfapi.so   Cf* / ip_route_*  (route + L3-interface add, route_mgr IPC: "cspd.cspd.route_mgr")
       ├─ libcmapi.so   Cm* (config-model: WANCIP, mflow, QoS queue/shaper, IGMP wancip)
       └─ libcommfun.so common_ioctl / bridge_ioctl  ── ioctl ──► /dev/switch_dev ──► switch.ko sw_*
```
FFE `echo ffe 1` and the iptables/ebtables firewall rules are issued by cspd via `system()`-style
shell strings (also referenced by cliagent and ebtables).

---

## 2. WAN interface bring-up sequence (in order)

1. **WAN mode selection** (config DB): `dwWanMode` = `0:DHCP 1:BRIDGE 2:ROUTER 3:PPP`
   (`dbCreateWanModeTbl`, `dbAdjustWanMode`, `MultiapSetWanMode`). ROUTER/DHCP/PPP ⇒ L3-routed WAN;
   BRIDGE ⇒ pure L2. Only the L3 modes should arm the L3 datapath. WAN objects are created via
   `AddWANC` / `OperationWANC` (see `bin/wantest`, `CmWANDAddWancd`, `CmWANCAddIP`, `CmWANCAddPPP`).

2. **Physical link up** → event into cspd: `EthLinkHandleWANNotify` → `ProcWanUpMsg` /
   `handle_wanif_up` → `CallWANNotify` (fan-out to DNS/firewall/QoS/route subsystems).
   State machine: `wanPortCreating` → `wanPortUping` → `wanPortSet` (source hint: `bridge_wanport.c`).

3. **IP acquisition**
   - DHCP: `DhcpcInitWancIPDataBase`, `Dhcp4cDealOfferAction`, `Dhcp4cGetNextHop` → WANCIP populated.
   - PPP: `CmWANCAddPPP` / `CmWANCSetPPP` (`bin/pppd`, `rp-pppoe.so`).
   The acquired address becomes the **WANCIP** ("WAN Connection IP") data-model object
   (`dbCreateWANCIPTbl`, `dbCreateWANCIPPrvDataTbl`).

4. **L3 interface + route binding** (libcfapi): `binding_l3if_V4V6_Conf` / `AdjustL3WANBind` →
   `ip_route_ifaddr_up` / `ip_route_if_add` (+ `ip6_route_if_add`) → route manager thread
   `cspd.cspd.route_mgr`; default route/DNS via `dnsClientHandleDefRouteUpMsg`,
   `SetV4RouteProtocolParam`. `GenericRtEntryBeEffect` marks a route entry "effective".

5. **Switch programming (the runtime hardware push at WAN-up)** — the steps a minimal driver misses:
   - `switchAdapterMflowConfSet` → `CmEthMflowConfig` → ioctl **`sw_acl_add_port_flowconfig` /
     `sw_set_mflow_config`** — installs the per-WAN-port ingress ACL FlowConfig. FlowConfig fields
     (from switch.ko strings): `direction`, `ruleType`, `rule_pri`, `match.entry[].field/mask/value`,
     `fwd.{fwdmode,desportmsk,des_q,gemport}`.
   - **`ethdrv_set_wanportid`** / ioctl **`sw_other_set_wan_lan_switch`** — designates the port as WAN
     ("set wan lan switch, eth%d to WAN", "set wan lan switch mode=%d", "WAN or AUTO"). Populates
     `g_sw_cap.sw_wan_port` / `ptSwInfo->wan_logicport` used for `FROM_WAN` direction detection.
   - ioctl **`sw_wancip_set`** — registers the WAN IP as a switch L3 interface (also `sw_wancip_get`/
     `sw_wancip_del`; IGMP variant `CmSetIgmpWancIP`/`sw_wancip_set` for multicast).
   - `hf_set_l3_entry` — per-route/nexthop hardware L3 entry (kernel-driven).

6. **QoS on WAN-up** (see §3): `QQZyterHWIFActive` / `QQZyterHWShaperConfig`, ioctl
   `sw_set_wanport_qos`, `sw_qos_set_trustppqueue` (`ethSetTrustppQueue`).

7. **FFE / flow-session lifecycle**: FFE master-enabled at boot (`echo ffe 1 > /proc/zte/sys/ffe/cmd`).
   Per-flow L3 hardfast sessions added/aged by cspd via ioctls `sw_acl_l3_hardfast_session_add` /
   `sw_acl_l3_hardfast_session_del` (`tFlowConfig` add/del/get/stat), polling the per-entry aging bit
   (`hf_query_l3_status`) — consistent with the userspace poll-and-delete GC already documented in
   memory `zte-flowoffload-framework`.

---

## 3. QoS / queue configuration

- **Boot init:** ioctl `sw_qos_init` (queues + scheduler). Priority→queue map `sw_qos_set_opritoqueue`,
  scheduler `sw_qos_set_port_schedule` / `sw_qos_set_mode_schedule`, overall bandwidth
  `sw_qos_set_overall_bandwidth`. cspd initcall `CspdQoSModuleInit`.
- **Per-WAN (on WAN-up):**
  - `sw_set_wanport_qos` — WAN-port QoS binding.
  - Trust priority queue: `sw_qos_set_trustppqueue` via `ethSetTrustppQueue` (CLI toggle
    `switchtst -strustppque [enable]`).
  - HW shaper: `QQZyterHWShaperConfig` ("shaping rate = %u"), activated per interface by
    `QQZyterHWIFActive` / `QQZyterVDHWIFActive`; egress-TM shaper (`QQShaperSet`, `DBVIEW_QOS_SHAPER`).
  - DHCP path also calls `_dhcpcInitQos` / `_dhcpcSetQosFd`; DNS QoS `DnsQosInit`.
- **tm.ko capacity (kernel-init, static — direction-split):** `setmaxl3entry [up][dn]` and
  `setmaxfastentry [enable][upnum][dnnum]`. These allocate L3/fast-entry capacity **separately per
  direction**. No userspace writer exists (set at module init), so if "static config is identical"
  they are not the runtime differentiator — but worth confirming the mainline driver's DN allocation
  is non-zero, since a zero `dn` allocation would independently cap downstream acceleration.
- **DB tables backing QoS:** `dbCreateQOSBasicTbl`, `dbCreateQOSClassificationTbl`,
  `dbCreateQOSPolicerTbl`, `dbCreateQOSQueueTbl`, `dbCreateQOSShaperTbl`.

**Prerequisite assessment:** QoS is unlikely to be the direct cause of `l3_en=0` (that flag is set in
the parse stage, before queueing). But the accelerated forward needs a resolved egress queue
(`FlowConfig.fwd.des_q`, `sw_qos_select_queue`); verify the DN accelerated path has a valid queue
mapping so it is not a secondary gate.

---

## 4. Feature inventory → userspace entry point → switch-config call

| Feature | Userspace entry point (cspd / lib) | Switch-config call (ioctl / proc) |
|---|---|---|
| WAN mode (DHCP/PPP/Router/Bridge) | `MultiapSetWanMode`, `OperationWANC`, `wantest` | `sw_other_set_wan_lan_switch` (`ethdrv_set_wanportid`) |
| WAN IP / L3 interface | DHCP `DhcpcInitWancIPDataBase` / PPP `CmWANCAddPPP`; `binding_l3if_V4V6_Conf` | `sw_wancip_set`; `ip_route_ifaddr_up`/`ip_route_if_add` (route_mgr) |
| Routing (v4/v6) | `SetV4RouteProtocolParam`, `GenericRtEntryBeEffect`, `PRouteChainRegister` | `hf_set_l3_entry` (kernel FIB/neigh-driven) |
| Per-WAN-port flow classification | `switchAdapterMflowConfSet` → `CmEthMflowConfig` | `sw_acl_add_port_flowconfig` / `sw_set_mflow_config` |
| HW L3 fast sessions (FFE flows) | cspd poll/GC (`tFlowConfig` add/del) | `sw_acl_l3_hardfast_session_add`/`_del`, `hf_query_l3_status` |
| HW acceleration master toggle | cspd/cliagent shell | `echo ffe 1 > /proc/zte/sys/ffe/cmd` (`ffe 0`/`npu 0` = off) |
| NAT | iptables (`nat` table) + FFE flow offload | (FFE learns NATed 5-tuple; `zte_api_fast_l3_session_use`) |
| Firewall | `fwinput`/`fwinput_pre`/`acl_forward` iptables chains (in cspd/libcfapi) | (Linux netfilter; ACL rules also via `sw_acl_*`) |
| ACL / ratelimit / mirror | `switchAdapterACLConfSet`, `SW_ACL_ACT_*` | `sw_acl_setMtchInfo`, `sw_port_set_port_ratelimit` |
| QoS queues/shaper/trust | `CspdQoSModuleInit`, `QQZyterHWShaperConfig`, `ethSetTrustppQueue` | `sw_qos_init`, `sw_set_wanport_qos`, `sw_qos_set_trustppqueue`, `sw_qos_set_*` |
| Multicast (IGMP/MLD) | `CmSetIgmpWancIP` / `SetIgmpWancIP` | `sw_wancip_set` (IGMP), `sw_add_igmp_addr_e8v4` |
| VLAN translation | `switchAdapterVlanConfSet` | `sw_vlan_*_port_*vlantranslationentry`, `sw_multi_vlan_trans_deal` |

---

## 5. Management UI / CLI knobs

- **CLI (`bin/cliagent`)**: exposes the FFE master toggle directly —
  `echo ffe 1 > /proc/zte/sys/ffe/cmd` (enable) / `echo ffe 0 > …` (disable). WAN node
  create/modify commands ("wan node set/save").
- **`bin/switchtst`** (direct switch test CLI over `/dev/switch_dev`) has explicit sections:
  `l3 operation`, `HardQOS operation`, `acl operation`, `qos operation`, `port/vlan/mac/ratelimit`.
  Notable flags: `-feature_open` (feature enable), `-strustppque [enable]` (trust-priority-queue),
  `-sqosmode/-sqosqueue/-sqosrcqueue/-sqosoverall`, `-sacl/-addacl`, `getLogicPort`/`getSwPort`
  (ifname→switch-port map). This is the closest thing to a hand-drivable API for reproducing the
  steps above during driver bring-up.
- **`bin/wantest`**: creates/deletes WAN connections (`AddWANC`, `clear`, per-type Eth/DSL/PTM
  IP/PPP/Bridge). Useful to script a WAN-up and observe the resulting switch state.
- Web UI (`httpd`, 37 WANCIP refs) config lives on a separate jffs partition not present in this
  rootfs snapshot; the backend commands are the same `Cm*`/`Cf*` API calls above.

---

## 6. Concrete recommendation for the driver

Add, at **WAN interface bring-up** (link + IP up), the runtime switch-config steps the reference
firmware performs and a minimal "kernel IP+route only" driver omits, in priority order:

1. **Register the WAN port's L3 role** — the equivalent of `ethdrv_set_wanportid(wan_logicport)` /
   ioctl `sw_other_set_wan_lan_switch(port → WAN)`. This is the most direct path to flipping
   WAN-ingress packets to `l3_en=1` (arms `FROM_WAN` → downstream L3 caps). Verify the mainline
   driver actually programs `g_sw_cap.sw_wan_port` / `wan_logicport` for the WAN uplink port and that
   the ingress parse stage keys `l3_en` off it.
2. **Install the per-WAN-port ingress FlowConfig** the way `CmEthMflowConfig` →
   `sw_acl_add_port_flowconfig` does (direction=downstream, `fwd.fwdmode` = forward/route). Because it
   is installed at runtime into ACL/flow RAM (not a static register), it would not appear in a
   static-register diff — matching the "config identical" observation.
3. **Register the WAN IP as a switch L3 interface** (`sw_wancip_set`) when the address is
   acquired/changes.
4. Confirm the DN accelerated path has QoS queue provisioning (`sw_set_wanport_qos` /
   `sw_qos_set_trustppqueue`) and that tm.ko `setmaxl3entry`'s `dn` allocation is non-zero.

Cross-reference with the kernel-side agent: they should confirm which of {`ethdrv_set_wanportid`,
`sw_set_mflow_config`, `sw_wancip_set`} the ingress parser reads when deciding `l3_en` for a
WAN-ingress packet. That register/field is the definitive fix target.
