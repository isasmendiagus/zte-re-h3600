# Stock rootfs QoS / Scheduler / Switch / TM config mining (ZTE H3600, ZXIC ZX279128S)

Date: 2026-05-28. Source: READ-ONLY golden stock rootfs at `ext/rootfs/`.
Goal: find the shaper rates, queue->port/tcont mappings, and init/config flow that the proprietary
daemons push to the SCH/DSCH/switch HW, to explain why CPU->LAN TX dies at the DSCH token-bucket shaper
(zero credit).

## TL;DR (most load-bearing findings)

1. **The DSCH shaper rate is NOT a hardcoded constant in the rootfs. It is computed at RUNTIME by
   `cspd` from the link rate** (`CSPDefDOWNIFGetLinkRate` / `CSPDefUPIFGetLinkRate` /
   `rtk_xdsl_dsp_GetLinkSpeed`) and applied via Linux `tc` qdisc commands. So a mainline driver that
   never has `cspd` run (or never reports a link rate) will leave the shaper at its power-on/default
   value -- which is exactly the zero-credit state we observe.
2. **The shaper is applied as a custom `sp` / `spwrr` qdisc carrying `linkspeed`/`limit`/`def`, plus a
   `police rate/burst` ingress filter** -- NOT a hardcoded register blob. See the `tc` template strings
   below. The HW qdisc layer is `zyterhw_qos_*` (Zyter = ZX279128S HW QoS).
3. **The Lua web layer is pure UI / TR-069 plumbing -- it has field NAMES only (ShapingRate,
   CommittedRate, PeakRate, SchedulerAlgorithm, Weight, QueueNum...) and NO numeric default values.**
   The values live in `cspd`'s config DB (the encrypted `db_default_auto_cfg_H3600.xml`).
4. **Best concrete reference for the queue<->port mapping is NOT in the stock rootfs Lua, but in the
   already-decompiled sibling firmware** at `refs/orca-h3600p/ghidra/output_ko/switch.ko/`
   (`chip_tm_init.c`, `pon_driver_adapter_schedue_mode_set.c`, `CSPKernel_skb_SelectQueue.c`,
   `ethdrv_set_wanportid.c`, `sw_mac_add_cpu_macaddress.c`). Recommend cross-reading those for the
   exact tcont/queue indices.

---

## 1. Boot / init / config flow (who applies the TM+switch setup)

`ext/rootfs/etc/rc` -> selects `etc/init.norm` (loadtype 3 = normal).

`ext/rootfs/etc/init.norm`:
- `:30-52` insmod order: `shellproc.ko -> patch.ko -> zx_ponreg.ko -> (sleep 5) ->
  plat-zxylzb_9128S.ko -> tm.ko -> switch.ko`. NOTE `netdriver.ko` is **commented out** (`:49`);
  the eth driver is built into `switch.ko` here.
- `:57-61` `ifconfig pon up; sw up; idm0 up; idm1 up`.
- `:63-79` raw `fpga -w` register pokes (serdes mode). Of note:
  - `:79 fpga -w 20041 400656` -- comment `:78` says "max frame length 1622 = 1600+22(atm)". 0x400656.
  - `:64 fpga -w 10006 2`, `:65 fpga -w 10009 c8`, `:68 fpga -w 10008 300`, `:70 fpga -w 20007 3e8`,
    `:73 fpga -w 20000 10040cb`, `:76 fpga -w 20002 41900000`, `:77 fpga -w 2003c 80000003`.
  - These are PHY/serdes/MAC bring-up, not the per-queue shaper.
- `:99 pc&` -- launches the controller. `bin/pc` is a tiny launcher; the real config engine is
  **`bin/cspd`** (2.8 MB). cspd reads the config DB and pushes QoS/switch/TM via `tc` + `devmem2` +
  the `*Qdisc*` SDK calls.

`ext/rootfs/etc/rdpa_dm_init.sh` -- **looks like a Broadcom-RDPA leftover, probably NOT used on this
ZXIC build** (it uses `bs /bdmf/new egress_tm ... port/index=lan0..lan3`, Broadcom bdmf syntax). Still
informative because it documents the intended DS egress_tm model:
- `:5-8` creates DS `egress_tm` index 0..3 = `lan0..lan3`, `level=queue, mode=sp` (strict priority).
- `:11-45` each LAN port gets **8 priority queues** `queue_id 7..0`, `weight=0` (=> strict priority,
  not WRR), `drop_alg=dt` (drop-tail), `drop_threshold=128` (1500 for lan1), `stat_enable=yes`.
- Takeaway: **8 SP queues per LAN port, queue_id 0=lowest .. 7=highest prio, drop-tail @128 desc.**
  If this maps to the real HW, the host's "best effort" egress would land on a low queue_id.

Build-time feature flags (`ext/rootfs/etc/autouserconf`, `autokernelconf`):
- `CONFIG_CSPCORE_ZX279128S_QOS_COMPONENT=1`, `CONFIG_CSPCORE_ZYTER_HWQOS=1`,
  `CONFIG_CSPCORE_QOS_V2=1`.
- `CONFIG_CSPCORE_QOS_QQ_SP=1`, `CONFIG_CSPCORE_QOS_QQ_WRR=1` (queue scheduler = SP or WRR).
- `CONFIG_CSPCORE_TC_SCHED_SP=1`, `CONFIG_CSPCORE_TC_SCHED_SPDWRR=1`.
- kernel: `CONFIG_CSPKERNEL_NET_SCH_SPWRR=y` (the custom `sp`/`spwrr` qdisc lives in the STOCK kernel's
  net/sched -- it is NOT in mainline; the mainline port has no `sp` qdisc, so `cspd`'s `tc qdisc add
  ... root sp ...` would silently no-op). `CONFIG_CSPKERNEL_QOS_POLICER_METER_SRTC/TRTC=y` (srTCM/trTCM
  token buckets -> CIR/CBS/PIR/PBS).

## 2. How the shaper is actually programmed (cspd strings, `bin/cspd`)

These are printf/templates pulled from `bin/cspd` via `strings`:

- `tc qdisc add dev %s root sp limit %d def %d linktype %d linkspeed %u`
  -> the egress scheduler/shaper. **`linkspeed` is the shaper rate and is a runtime arg** (the `%u`),
  sourced from the WAN/DSL link rate, not a constant.
- `tc qdisc add dev %s root %s limit %d def %d linktype %d` (the `%s` qdisc name = `sp` or `spwrr`).
- `tc qdisc change dev %s parent root %s id %d prio %d enable %d setlen %d`
  -> per-queue enable/priority/length change. `enable %d` = the queue-enable bit; `id %d` = queue id;
  `prio %d` = priority. This is the closest thing to the "queue enables / queue->prio" we need.
- `tc filter add dev %s parent ffff: protocol all prio 1 handle 1 u32 match u32 0 0
   police rate %u burst %u mtu %d drop flowid :1` -> ingress policer (token bucket: `rate`,`burst`).
- `tc qdisc add dev %s handle ffff: ingress` / `tc qdisc del dev %s root|ingress`.

Shaper-rate compute path (function names in cspd):
- `QQDefDevShaperCale ... End, ShapingRate %d Link %d burst %d` -- computes ShapingRate from the link.
- `QQZyterHWShaperConfig in: shaping rate = %u`, `QQZyterHWCalcBandwith`, `QQZyterHWGetWANDRate`,
  `QQZyterHWConfig`, `QQZyterHWIFActive`, `QQZyterHWSchGetInfo`.
- `CSPDefDOWNIFGetLinkRate`, `CSPDefUPIFGetLinkRate`, `rtk_xdsl_dsp_GetLinkSpeed` -- the rate sources.
- HW qdisc registration: `RegisterZyterHWIFQdisc` / `__initcall_RegisterZyterHWIFQdisc`; per-IF qdisc
  classes named `zyterhw_qos_eth`, `zyterhw_qos_lan`, `zyterhw_qos_vd`.
- Scheduler check funcs: `CSPDefSPWRR`, `CSPQQSPWRRPrioCheck` (`iSPMinPrio`/`iWRRMaxPrio`),
  `CSPZyterHWQdiscSet/Check/ConfigAll/Destroy`, **`CSPZYLANQdiscSet/Check/ConfigAll/Destroy`**
  (`CSPZYLAN*` = the LAN-side HW qdisc -- this is the path the host->LAN egress goes through;
  `CSPZYLANQdiscCheck Fail! The hard queue can not be disabled` confirms fixed HW queues exist).
- Per-queue debug line (best mapping evidence in cspd):
  `dwIndex = %d, giHWQueueID = %d, gdwQueueWeight = %d, giWRRQueueFlag = %d`
  -> there is a software index -> `HWQueueID` -> weight + (WRR vs SP) flag mapping table inside cspd.
  Also globals `giHWQueueID`, `gdwQueueWeight`, `gdwDefaultQueueID`, `QQMAssignedQueueID`.
- Direct HW register poke near QoS: `devmem2 0x94100090 w 0x10` (single 32-bit write; meaning TBD),
  and `fpga -w 72006 60`, `fpga -w 72007 1000`.
- Queue count constant referenced: `QUEUE_TRAFFICCLASS_MAX` (with overflow guard
  `iQueuePrio + QUEUE_TRAFFICCLASS_MAX val overflow`) -- consistent with the 8 queues in
  `rdpa_dm_init.sh`.

## 3. Switch / port / CPU / uplink mapping

- cspd has a `MultiUplink` subsystem: `g_uplink_type`, `CurrUpLinkType`, `dbCreateMultiUplinkTbl`,
  `CallCurrUplinkNotify`, `__initcall_MultiUplinkModuleInit`, `InternalPort`/`InternalPortEndRange`.
  Port name transfer funcs: `CSPDefUPIFNameTransfer`, `CSPDefDownIFNameTransfer`,
  `CSPZyterHWUPIFNameTransfer`, `CSPZyterVDHWIFNameTransfer`, `cfGetBrPortIDbyLowID`,
  `CfGetBrPortIndexByPortID`, `__AddViewbyPortID`.
- LAN interface names referenced in cspd: `eth1 eth2 eth3 eth4` (note: these are the cspd/web LAN
  port names, 1-indexed; map to internal PHY/MAC 0-indexed -- so web "eth3"/lan3 likely = internal
  port 2 = PHY[2]/MAC[2], which the task says is the host path).
- **No explicit "internal port 3 -> tcont/queue index N" string exists in the rootfs Lua or cspd
  strings.** That mapping is compiled into `switch.ko`/`tm.ko`/cspd logic. The decompiled sibling is the
  way to get it (see section below).

## 4. Lua web layer (UI only -- no values)

All compiled Lua 5.1 bytecode (`\x1bLuaQ\x00`, header `01 04 04 04 08` = LE, 32-bit int/size_t/instr,
64-bit double). Relevant modules at `ext/rootfs/home/httpd/webmodules/modules/`:
- `qos_shaper_lua.lua` -> `OBJ_QOSSHAPER_CONF_ID`: fields `Enable, Interface, ShapingRate`.
- `qos_queue_lua.lua` -> `OBJ_QOSQQ_ID`: `Enable, TrafficClasses, QueueInterface, DefaultQueue,
  NeedStats, SchedulerAlgorithm, Weight, QueueNum, ShapingRate`, `InterfaceFilter=WAN`.
- `qos_speed_lua.lua` -> `OBJ_QOSQP_ID` (policer): `CommittedRate, CommittedBurstSize, ExcessBurstSize,
  PeakRate, PeakBurstSize, MeterType, ConformingAction...` (= srTCM/trTCM token-bucket params).
- `qos_type_m.lua` / `qos_basic_m.lua` -> `OBJ_QOSQC_ID` classifier (DSCP/VlanPrio -> QueueNum), only
  i18n label keys (`QosType_0xx`), no numbers.
Conclusion for the Lua: **pure UI. No shaper/scheduler default values. Do not spend time decompiling
the QoS Lua for numbers -- there are none.** (Decompiling is still trivially possible -- see the user
note at end -- but it will only yield the field/object names already listed here.)

## 5. The config-DB blob (where the numbers would be, if persisted)

`ext/rootfs/etc/db_default_auto_cfg_H3600.xml` -- 6840 bytes, `file` says `data` (encrypted/compressed,
NOT plain XML; high-entropy binary). This is cspd's factory-default config DB for THIS model. If any
default ShapingRate/Weight/QueueNum is persisted, it is here, but it is encrypted. cspd decrypts it at
boot (`dbCreateQOSShaperTbl`, `dbCreateQOSPolicerTbl`, `DBVIEW_QOS_SHAPER`, `dbDefPortControl` etc.).
To extract values, run cspd or RE its DB-decrypt routine -- out of scope for read-only string mining.

## Implications for the DSCH zero-credit bug

- The DSCH per-queue token-bucket shaper having `fill-rate = bucket-cap = 0` is the **default/unprogrammed
  HW state**. Stock fills it only when `cspd` calls `QQZyterHWShaperConfig`/`tc ... root sp ... linkspeed
  %u` with a real link rate. For a LAN-only / CPU->LAN path with no WAN link rate, stock either (a) uses a
  full-rate/line-rate default for the LAN qdisc (`CSPZYLAN*`), or (b) leaves it unshaped. The mainline
  port currently does neither, so credit stays 0.
- **Actionable for the driver agent:** the DSCH queue used by host egress must be given a non-zero
  fill-rate + bucket-cap (i.e. the equivalent of `tc qdisc add dev <lan> root sp ... linkspeed <line
  rate>` and `enable=1`). The exact HW queue index for internal port 3 (host) is still unconfirmed from
  the rootfs alone -- pull it from `refs/orca-h3600p/ghidra/output_ko/switch.ko/chip_tm_init.c`,
  `pon_driver_adapter_schedue_mode_set.c`, and `CSPKernel_skb_SelectQueue.c`.

## File:line cite index
- `ext/rootfs/etc/rc:19-26` (loadtype branch -> init.norm)
- `ext/rootfs/etc/init.norm:30-52` (insmod order, netdriver disabled), `:57-79` (ifup + fpga pokes),
  `:79` (max frame 1622), `:99` (`pc&` launches controller)
- `ext/rootfs/etc/rdpa_dm_init.sh:5-8` (DS egress_tm lan0-3, mode=sp), `:11-45` (8 SP queues/port,
  qid 7..0, weight=0, drop-tail @128/1500) -- likely Broadcom leftover, verify before trusting
- `ext/rootfs/etc/autouserconf` (ZX279128S_QOS_COMPONENT, ZYTER_HWQOS, QQ_SP/QQ_WRR, QOS_V2)
- `ext/rootfs/etc/autokernelconf` (CSPKERNEL_NET_SCH_SPWRR=y, POLICER_METER_SRTC/TRTC=y)
- `ext/rootfs/bin/cspd` (strings): `tc qdisc add dev %s root sp ... linkspeed %u`;
  `tc qdisc change ... id %d prio %d enable %d setlen %d`; `police rate %u burst %u`;
  `QQZyterHWShaperConfig in: shaping rate = %u`; `dwIndex=%d giHWQueueID=%d gdwQueueWeight=%d
  giWRRQueueFlag=%d`; `CSPZYLANQdisc*`; `devmem2 0x94100090 w 0x10`
- `ext/rootfs/home/httpd/webmodules/modules/qos_{shaper,queue,speed,type_m,basic_m}_lua.lua`
  (UI field names only, no values)
- `ext/rootfs/etc/db_default_auto_cfg_H3600.xml` (encrypted factory default config DB)
- Reference (sibling fw, already decompiled): `refs/orca-h3600p/ghidra/output_ko/switch.ko/`
  -> `chip_tm_init.c`, `pon_driver_adapter_schedue_mode_set.c`, `CSPKernel_skb_SelectQueue.c`,
  `ethdrv_set_wanportid.c`, `sw_mac_add_cpu_macaddress.c`, `CspGetPortInfo.c`
