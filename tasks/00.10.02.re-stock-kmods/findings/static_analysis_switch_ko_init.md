# Stock init flow — `switch.ko` static analysis depth-first walk

Walking from `switch.ko init_module` entry point through every function
call, depth-first, documenting each.

For each function: file:line where defined, brief comment of what it
does, HW writes (addr + value), and list of sub-calls.

Source: `tasks/00.10.02.re-stock-kmods/findings/decomp_all_switch.c`
(raw Ghidra decomp of switch.ko).

Cross-reference convention: `[fn-NN]` link tags so we can grep.

---

## Legend

- **HW writes**: register address + value the function pokes
- **Sub-calls**: nested function invocations (descended in same doc)
- **In mainline?**: ✓ replicated / ⚠ partial / ✗ missing / N/A
- **Severity if missing**: 🔴 likely path-breaking · 🟡 unclear · 🟢 informational

### Important note about switch.ko's call structure

switch.ko is the **policy** layer of the ZXIC fabric stack. It owns
almost no direct MMIO. Instead it issues SDK calls into **tm.ko**
(loaded as a prerequisite — `lsmod` confirms `switch` depends on
`tm`). Every callee in `decomp_all_switch.c` with an address ≥
`0x2c000` is a PLT/GOT entry — Ghidra decompiles those as
`halt_baddata()` because the relocation table is non-code. Treat any
such symbol as **"indirect via tm.ko API X"** and do not chase into
this file. The few addresses below 0x2c000 are switch.ko's own
locally defined functions.

### Initialization topology (one-page summary)

```
init_module                                      [fn-00]
├── printk("Init switch module")
├── sw_init_switch                               [fn-01]
│   ├── sw_reg_set_onu_swcap                     [fn-02]
│   ├── sw_init_wlan_ssid                        [fn-03]
│   ├── pdt_ethdriver_init                       [fn-04]
│   ├── [if pon_work_mode & 0x10] sw_set_p2pmode [fn-05]
│   ├── chip_tm_init                             [fn-06]   ★ central fabric bring-up
│   ├── [if work_mode==1] tm_acl_l2_fast_init    (tm.ko)
│   ├── sw_set_default_mulrule                   [fn-07]
│   ├── sw_set_default_protocol_rule             [fn-08]
│   ├── sw_hgu_multi_config_init/sfu_*_init      [fn-09]   (no-ops)
│   ├── sw_alarm_init                            [fn-10]
│   ├── l3_hardfastReg                           [fn-11]
│   ├── sw_qos_init                              [fn-12]
│   └── register_bridge_notifier(...)            (tm.ko or kernel)
├── public_capfun_register                       [fn-13]
└── private_capfun_register                      [fn-14]
```

---

## [fn-00] `init_module` @ decomp_all_switch.c:12400 — entry stub

What it does: trivial four-line entry. Logs "Init switch module",
calls `sw_init_switch`, then registers two callback tables
(public/private capfun). Almost all real work happens inside
`sw_init_switch` and `chip_tm_init`.

HW writes: **none directly**.

Sub-calls in order:
1. `printk("Init switch module\n")`
2. `sw_init_switch()` — [fn-01]
3. `public_capfun_register()` — [fn-13]
4. `private_capfun_register()` — [fn-14]
5. `printk("Init personal switch module Success\n")`

In mainline? **unknown — to verify**.

Severity if missing: 🔴 critical — this is the SDK bring-up entry; without
it the switch fabric registers stay at whatever U-Boot left them in.

---

## [fn-01] `sw_init_switch` @ decomp_all_switch.c:2703 — top-level orchestrator

What it does: brings up the entire switch software stack. Reads ONU
capabilities from cspd, registers per-port net_devices, programs the
fabric via `chip_tm_init`, installs default multicast/protocol ACL
rules, initialises QoS and alarm threads, and wires up the bridge
notifier. Conditional branches on `g_pon_work_mode` (bit 0x10 = LAN
mode, value==1 = HGU mode) select HGU vs SFU multi-config init and
whether to enable L2 fast forwarding.

HW writes (direct): one masked clear at `_tm_vlan_check_ena_set*0x14 +
-0xbe2bce8 &= 0xfffcffff` — clears bits 16-17 of a per-port struct
field; appears to live in a tm.ko-owned static rather than MMIO.

Sub-calls in order:
1. `sw_reg_set_onu_swcap()` — [fn-02]
2. `sw_init_wlan_ssid()` — [fn-03]
3. `pdt_ethdriver_init()` — [fn-04]
4. `if (g_pon_work_mode & 0x10) sw_set_p2pmode()` — [fn-05]
5. `chip_tm_init()` — [fn-06]
6. `if (g_pon_work_mode == 1) tm_acl_l2_fast_init()` (indirect via tm.ko)
7. `sw_set_default_mulrule()` — [fn-07]
8. `sw_set_default_protocol_rule()` — [fn-08]
9. `if (g_pon_work_mode == 1) sw_hgu_multi_config_init()` — [fn-09a]
   `else sw_sfu_multi_config_init()` — [fn-09b]
10. `sw_alarm_init()` — [fn-10]
11. `l3_hardfastReg()` — [fn-11]
12. `sw_qos_init()` — [fn-12]
13. `register_bridge_notifier(DAT_0001417c)` (indirect via tm.ko)

In mainline? **unknown — to verify**.

Severity if missing: 🔴 critical — without `chip_tm_init` and the default
multicast rules the fabric is unconfigured.

---

## [fn-02] `sw_reg_set_onu_swcap` @ decomp_all_switch.c:2541 — pull port topology from cspd

What it does: queries cspd-side userspace structs (`CspGetPortInfo`,
`CspGetSwInfo`) for the unit's port count, WAN logic-port index, PON
port id, WLAN-port mapping, etc., then populates module-global
mirrors (`g_sw_cap`, the logical-to-physical port table
`zte_api_sw_mac_set_port_macfiltermode[]`, port count
`_tm_port_unknwn_multicast_floodport_set`, sw_uni_mask
`_zte_api_sw_mac_set_port_learnlimit`, wan-mask
`_tm_broadcst_vltrans_table_print_get`, wan-port id
`_tm_vlan_check_ena_set`). Computes `lan_up` = OR of all port masks.
Picks a `g_sw_cap` wan-type code 0..7 from `g_pon_work_mode` bitfield
(0x20=GPON, 0x40=EPON, 0x80=GFAST, 0x100=ADSL, 0x200=EFM,
0x400=VDSL2, 0x800=ETHERNET). Bails out cleanly if port count > 8.

HW writes: **none** — only module-global RAM mirrors and printks.
Aborts with error if `eth cnt > 8`.

Sub-calls:
- `__memzero(&g_sw_cap, 0x5c)`
- `CspGetPortInfo(local_24)` (cspd userspace handoff — kernel-shared struct)
- `CspGetSwInfo(&local_28)`
- `zte_api_sw_get_pon_port(&local_2b)` (tm.ko)
- `zte_api_sw_get_wlan_port(&local_2a)` (tm.ko)
- `printk` ×10 (diagnostic dump of every g_sw_cap field)

In mainline? **unknown — to verify** — mainline driver uses DT to
discover port count + roles instead of cspd; the global mirrors that
later code reads (`_tm_vlan_check_ena_set`, `_zte_api_sw_mac_set_port_learnlimit`,
`lan_up`, etc.) must be initialised equivalently or chip_tm_init will
program the wrong port set.

Severity if missing: 🔴 critical — every later function uses the
globals this populates. Without it, port masks are zero and no port
is configured.

---

## [fn-03] `sw_init_wlan_ssid` @ decomp_all_switch.c:5112 — WLAN-to-IDM mapping reset

What it does: zeroes the WLAN→IDM mapping table (`aclWlanToIdmReset`)
then iterates a 16-entry static SSID config blob, calling
`aclWLANToIDMEssidCfg2` for each enabled entry to bind ESSID strings
to internal IDM (Identity Module) tags 6 or 7 depending on type
byte at +0x24.

HW writes: **indirect via aclWLANToIDMEssidCfg2** — registered via
ACL TCAM in tm.ko.

Sub-calls:
- `aclWlanToIdmReset()` (tm.ko, PLT @ 0x2c0fc)
- `aclWLANToIDMEssidCfg2(idx, idmtag, ssid_id, ssid_struct, ...)` (tm.ko, PLT @ 0x2c240) — loop up to 16x

In mainline? **unknown — to verify** — mainline driver currently has no
WLAN-IDM mapping at all (WLAN goes through mt7915 directly).

Severity if missing: 🟢 informational — WLAN ESSID→VLAN mapping only
matters once the user binds the on-board wifi through the GPON fabric;
not a TX/RX path requirement.

---

## [fn-04] `pdt_ethdriver_init` @ decomp_all_switch.c:300 — register per-port netdevs

What it does: clones the underlying carrier (`pon0`/`eth*`) net_device
into N per-LAN-port virtual netdevs (`alloc_etherdev_mqs(100,1,1)`),
copies MAC/MTU/dev_addr, installs `ethdrv_port_dev_destruct` as the
destructor, and calls `register_netdev`. Each clone gets the logical
port id stored at `+0x4c0` and a pointer back to the parent at
`+0x4c4`. Also brings interfaces UP via `dev_change_flags(... | IFF_UP)`.
Installs `pdt_ethdrv_recv` as the global `switch_skb_recv` hook
(this is the RX entry-point from tm.ko into switch.ko) and creates
the `/sys/class/.../ethdrv_test_group` sysfs group.

HW writes: **none** — operates on Linux net_device structures and
the global RX hook pointer.

Sub-calls:
- `set_mii_dev_name_type_part_0(0, &_LC26)` / `(1, &_LC27)` — name templates
- `dev_get_by_name(&init_net, ...)` ×N
- `rtnl_lock` / `dev_change_flags(... | 1)` / `rtnl_unlock` / `msleep(1000)`
- `disableIRQinterrupts` + `coproc_movefrom_Privileged_only_Thread_and_Process_ID` — Ghidra noise for `local_irq_disable() + put_cpu()`
- `alloc_etherdev_mqs(100, 1, 1)` ×N
- `memcpy` ×2 (dev_addr + perm_addr)
- `register_netdev(iVar4)`
- `netif_carrier_off(iVar4)`
- `sysfs_create_group(DAT_00010724, &ethdrv_test_group)`
- Sets `switch_skb_recv = pdt_ethdrv_recv` (global func ptr)

In mainline? **unknown — to verify** — mainline allocates per-port
netdevs directly in the driver probe path; the global `switch_skb_recv`
indirection does not exist in mainline.

Severity if missing: 🔴 critical — without these netdevs the kernel
has no `eth0..ethN` for userspace; sw_init_switch dependents reference
them by name.

---

## [fn-05] `sw_set_p2pmode` @ decomp_all_switch.c:2254 — declare UNI as WAN

What it does: 4-line trampoline. Reads `tm_vlan_check_ena_set` (a tm.ko
global that holds the WAN port id) and calls `tm_set_p2pmode(port)`
(tm.ko) which configures the fabric for UNI-as-WAN mode (the LAN-mode
path that the H3600 actually uses, since `g_pon_work_mode & 0x10` is
the LAN-only mode bit).

HW writes: **indirect via tm.ko `tm_set_p2pmode`**.

Sub-calls:
- `printk("sw_set_uni_as_wan uni=%d", tm_vlan_check_ena_set)`
- `tm_set_p2pmode(cVar1)` (tm.ko PLT @ 0x2c0a0)

In mainline? **unknown — to verify**.

Severity if missing: 🔴 critical — this is the H3600's actual WAN-port
mode bit; without it, traffic forwarding rules treat the WAN port as a
regular LAN port.

---

## [fn-06] `chip_tm_init` @ decomp_all_switch.c:2268 — ★ central fabric bring-up

What it does: this is the heart of switch.ko. Walks every active port
(LAN1..N + PON + WLAN slots) and:

1. Calls `zte_api_sw_global_init(&local_6c[7])` (tm.ko) once with a
   global parameter struct: `0x88a8` ethertype for outer Q-in-Q, four
   TPID values (`0x8100/0x9100/0x9200`), aging time 2000, MAC hash mode
   1, learn enable 1, debug-level-dependent global learn flags.
2. Per port (loop bounded by `tm_set_p2pmode` = total port count + 1):
   - `zte_api_sw_port_init(&local_cc)` — initialise port id, link state,
     unicast flag (`port != WAN ? 1 : 0`), 2 reserved bytes.
   - `zte_api_sw_vlan_set_port_pvid(port, 0, 0)` — clear PVID.
   - `zte_api_sw_vlan_set_port_vlancfg(port, 0, 0, 3)` — base vlan cfg.
   - If `g_switch_debug_level == 1 or 3` (HGU modes):
     `zte_api_sw_vlan_set_port_vlancfg(port, 0, 0xfff, 3)` — pass-all.
   - If `port == WAN`: same pass-all + apply to PON port if wanLogicPort != -1.
   - `zte_api_sw_port_set_port_isolatemask(port, ~mask)` — per-port
     isolation (WAN+WLAN see all; LAN ports see `~(lan_up & ~(1<<self))`).
   - `zte_api_sw_set_port_brdcast(local_c0)` — broadcast settings struct.
   - `zte_api_sw_set_port_unicast(local_88)` — unicast struct (sets
     unknown-unicast trap-to-CPU for port==PON in HGU mode).
   - `zte_api_sw_set_port_muticast(local_b0)` — multicast struct
     (sets `+0x18=2` for WLAN ports in HGU mode, else 0).
3. `zte_api_pp_global_init(&local_a0)` — packet-processor global init
   (debug-level-dependent flags + age=2 in HGU).
4. `zte_api_pp_set_cpu_queue_rate(queue, 8000)` for queues 0..7 —
   CPU queue rate limit 8000pps each.
5. Loops through `DAT_00013cf4[]` table calling
   `zte_api_pp_set_trap_queue(direction=0/1, ethertype, queue)` and
   `tm_protocol_pkt_limit_pps_set(direction, queue, 1, 8000)` for each
   entry — installs protocol→CPU-queue mappings.
6. Loops through `DAT_00013cf8[]` table calling
   `zte_api_pp_set_pro_action(direction=0/1, ethertype, action)` —
   installs protocol→action (forward/trap/drop) rules.
7. `tm_cla_outspace_cfg_get` then `tm_cla_outspace_cfg_set(1, val)` —
   adjusts classifier output space.

HW writes: **all indirect via tm.ko APIs** (`zte_api_sw_*`,
`zte_api_pp_*`, `tm_cla_*`, `tm_protocol_pkt_limit_pps_set`).
**This is the function whose effect mainline replays via
`zx_stock_table.h`** — the captured TM register writes during stock
boot are the cumulative side-effect of all the tm.ko APIs that
chip_tm_init invokes here.

Sub-calls (tm.ko PLT names, deduplicated):
- `zte_api_sw_global_init(struct *)` — 1×
- `zte_api_sw_port_init(struct *)` — N×
- `zte_api_sw_vlan_set_port_pvid(port, 0, 0)` — N×
- `zte_api_sw_vlan_set_port_vlancfg(port, idx, vid, mode)` — up to 3N×
- `zte_api_sw_port_set_port_isolatemask(port, ~mask)` — N×
- `zte_api_sw_set_port_brdcast(struct *)` — N×
- `zte_api_sw_set_port_unicast(struct *)` — N×
- `zte_api_sw_set_port_muticast(struct *)` — N×
- `zte_api_pp_global_init(struct *)` — 1×
- `zte_api_pp_set_cpu_queue_rate(q, 8000)` — 8×
- `zte_api_pp_set_trap_queue(dir, eth, q)` — table-driven loop
- `tm_protocol_pkt_limit_pps_set(dir, q, 1, 8000)` — table-driven loop
- `zte_api_pp_set_pro_action(dir, eth, act)` — table-driven loop
- `tm_cla_outspace_cfg_get / tm_cla_outspace_cfg_set` — 1×

In mainline? **⚠ partial** — mainline replays the cumulative MMIO via
`zx_stock_table.h` (the captured RAM-side writes that tm.ko performs
under chip_tm_init's direction). Correctness verification: replay
table must contain the same register pokes that this orchestration
produces for our specific `g_pon_work_mode=0x10`, port-count=4 (LAN
mode, LAN1..LAN4 + WAN + PON-internal).

Severity if missing: 🔴 critical — switch fabric is unconfigured
without it.

---

## [fn-07] `sw_set_default_mulrule` @ decomp_all_switch.c:2039 — install default IPv4+IPv6 multicast rules

What it does: allocates 0x49c-byte ACL rule structures from
`_DAT_0002c340` (a `kmem_cache` set up at module load), zeroes them,
fills two stream-select rule blobs (one for IPv4 multicast destination
MAC `01:00:5e:xx:xx:xx`, one for IPv6 multicast destination MAC
`33:33:xx:xx:xx:xx`), and registers each via
`zte_api_sw_qos_add_port_streamselect(struct, out_handle)` (tm.ko).
Rule priority field (`+0x256`) is 5; action (`+0x250`) is 1 (drop or
trap, depending on tm.ko's interpretation).

HW writes: **indirect via tm.ko ACL TCAM** (`zte_api_sw_qos_add_port_streamselect`).

Sub-calls:
- `kmem_cache_alloc(_DAT_0002c340, GFP_ATOMIC=0x20)`
- `__memzero` ×2
- `zte_api_sw_qos_add_port_streamselect(buf, out_handle)` ×2
- `kfree(buf)`

In mainline? **unknown — to verify** — mainline has no equivalent
default multicast TCAM rule install path; IGMP snooping currently goes
through Linux bridge code.

Severity if missing: 🟡 unclear — default multicast handling is
expected by the fabric to either forward to all LAN ports or trap to
CPU; without the rules behaviour falls through to whatever the TCAM
default-action is.

---

## [fn-08] `sw_set_default_protocol_rule` @ decomp_all_switch.c:2126 — install default link-layer protocol rules

What it does: same allocator/structure shape as [fn-07] but installs
multiple protocol-specific stream-select rules:
- STP/BPDU rule (dest MAC `01:80:c2:00:00:00`, mask `ff:ff:ff`)
- IGMP/MLD rule (proto IGMP=0xd at `+0xc`, dest MAC mask
  `01:00:5e:ff:ff:ff` for IPv4 multicast bucket)
- Per-physical-port replicated variant of both rules over all
  `_tm_port_unknwn_multicast_floodport_set` LAN ports (extra rule
  body offset 0x30..0x53 holds the port mask 1<<portid).

All registered via `zte_api_sw_qos_add_port_streamselect` (tm.ko).
Aborts on first failure.

HW writes: **indirect via tm.ko ACL TCAM**.

Sub-calls:
- `kmem_cache_alloc` / `__memzero` / `kfree`
- `zte_api_sw_qos_add_port_streamselect(buf, out_handle)` — 2 + 2*N
  invocations where N = LAN port count

In mainline? **unknown — to verify**.

Severity if missing: 🟡 unclear — STP BPDUs and IGMP packets won't be
trapped to CPU; multicast learning + spanning tree won't work in stock
behavior, but mainline currently doesn't rely on either of these.

---

## [fn-09a] `sw_hgu_multi_config_init` @ decomp_all_switch.c:10890 — empty stub

What it does: **literal `return;`** — placeholder, no work. Stock H3600
likely has the multi-config bake-in elsewhere (cspd userspace or
device-tree). Decomp body is one return statement.

HW writes: **none**.

Sub-calls: none.

In mainline? N/A.

Severity if missing: 🟢 informational.

---

## [fn-09b] `sw_sfu_multi_config_init` @ decomp_all_switch.c:10181 — empty stub

What it does: identical empty stub to [fn-09a]. Both branches of the
work-mode if/else in [fn-01] are no-ops in switch.ko itself.

HW writes: **none**.

Sub-calls: none.

In mainline? N/A.

Severity if missing: 🟢 informational.

---

## [fn-10] `sw_alarm_init` @ decomp_all_switch.c:4867 — alarm/watchdog kthread + CPU rate limits

What it does: zeroes a 64-byte alarm state buffer at `DAT_000170cc`,
spawns the `sw_port_alarm_kthread` polling thread (which periodically
calls `sw_alarm_scanforalarm` and re-applies pps limits — body at
decomp_all_switch.c:4837), installs per-queue CPU pps rate limits of
8000pps for queues 1..7 (both ingress dir=0 and egress dir=1), sets
port-6 and port-7 (WLAN ports) ratelimit to 1/1 via
`zte_api_sw_port_set_port_ratelimit`. Finally pokes
`fpga_write_reg(0xd3000, 0x1f40fa0)` — this is the **only direct MMIO
poke originating from switch.ko**, routed through an exported helper
that goes to tm.ko or `plat-zxylzb` (PLT @ 0x2c1f0). Address 0xd3000
is in the PP (packet processor) base; value `0x1f40fa0` decomposes
as `(8000<<8)|0xa0` — likely a global CPU rx pps burst+limit pair.

HW writes:
- `fpga_write_reg(0xd3000, 0x1f40fa0)` — indirect via tm.ko/plat
  helper, single CSR poke.
- Multiple `tm_protocol_pkt_limit_pps_set(dir, q, 1, 8000)` (tm.ko)
  for q=1..7 and dir=0/1.
- `zte_api_sw_port_set_port_ratelimit(6, 1, 1)` /
  `(7, 1, 1)` — tm.ko.

Sub-calls:
- `__memzero(DAT_000170cc, 0x40)`
- `kthread_create_on_node(sw_port_alarm_kthread, 0, -1, "sw_port_alarm_kthread")`
- `wake_up_process()`
- `tm_protocol_pkt_limit_pps_set` ×13
- `zte_api_sw_port_set_port_ratelimit` ×2
- `fpga_write_reg(0xd3000, 0x1f40fa0)`

In mainline? **unknown — to verify** — mainline has no equivalent
alarm kthread and almost certainly skips the per-queue CPU pps caps
+ the `0xd3000` poke. The `0xd3000` write was observed in our stock
register replay table, so verify it's present in `zx_stock_table.h`.

Severity if missing: 🟡 unclear — CPU queue rate-limits prevent
control-plane DoS; alarm kthread polls link state. Neither is on the
TX/RX data path, but the `0xd3000` poke might gate PP enable.

---

## [fn-11] `l3_hardfastReg` @ decomp_all_switch.c:1384 — register L3 hardfast callbacks

What it does: builds a 5-pointer callback table containing
`hf_set_l3_entry`, `hf_del_l3_entry`, `hf_query_l3_status`,
`hf_entry_police2`, plus 4 little-endian shorts of value `0x14` each
(entry sizes), and hands it to `npu_hff_register` (which lives at
decomp_all_switch.c:10920 — also in switch.ko, despite the name).
`npu_hff_register` copies these into the `npu_hff_func_tbl` global,
calls `npu_register_driver(&npu_drv)` (PLT @ 0x2c02c — into tm.ko or
NPU module), and zeroes the 0x420-byte `DAT_00020350` table — the
session table for L3 hardware fast-forwarding.

HW writes: **none directly** — installs callbacks that *later* are
invoked from the RX/TX hot paths to program L3 hardfast flow entries
via tm.ko TCAM. `__memzero(DAT_00020350, 0x420)` clears the session
table.

Sub-calls:
- `npu_hff_register(local_28, local_18)` @ decomp_all_switch.c:10920
  - `__memzero(&npu_hff_func_tbl, 0x10)`
  - `npu_register_driver(&npu_drv)` (PLT @ 0x2c02c — tm.ko)
  - `__memzero(DAT_00020350, 0x420)`
  - sets `g_multivlan_lock = 0`

In mainline? **unknown — to verify** — mainline driver has no L3
hardfast at all; flow offload would have to be added via TC/flower.

Severity if missing: 🟢 informational — hardware fast-forwarding is a
performance optimisation, not a correctness requirement. Mainline can
function with software forwarding.

---

## [fn-12] `sw_qos_init` @ decomp_all_switch.c:6027 — QoS tcont scheduler hookup

What it does: sets the global `dev_qos_select_queue` function pointer
to `sw_qos_select_queue` (so Linux multi-queue qdisc lookups route
through switch.ko's queue selector). **Returns early if work_mode bit
0x10 is set** (LAN-only mode — which is the H3600's actual mode), so
on our unit this function effectively only sets the `dev_qos_select_queue`
pointer. In other (GPON/EPON) modes it clears the QoS global state via
`qos_global_para_clr` and for tcont indexes [g_tcont_start ..
g_tcont_size) calls `tm_tcont_secsch_hang_que_set(tcont, queue, 0)`
for queues 0..7 (initialises tcont→queue scheduler hangups).

HW writes:
- LAN mode (our case): only `dev_qos_select_queue` global ptr write.
- GPON/EPON mode: **indirect via tm.ko `tm_tcont_secsch_hang_que_set`**.

Sub-calls:
- LAN mode: none beyond global ptr assignment.
- GPON/EPON mode:
  - `qos_global_para_clr()` @ decomp_all_switch.c:6006 — `__memzero(&g_qos_queue, 0x60)`, sets `g_tcont_size/start` based on debug_level.
  - `tm_tcont_secsch_hang_que_set(tcont, q, 0)` 8× per tcont, looped.

In mainline? **unknown — to verify** — mainline uses standard Linux qdisc;
no `dev_qos_select_queue` indirection.

Severity if missing: 🟡 unclear — without the `dev_qos_select_queue`
hook, Linux uses default queue selection which may not align with the
fabric's hardware queue numbering on multi-queue netdevs.

---

## [fn-13] `public_capfun_register` @ decomp_all_switch.c:992 — ioctl callback table install

What it does: calls 7 separate "register a group of callbacks" functions
exported by tm.ko (`sw_public_*_func_reg`). Each takes a fixed set of
function pointers — port_vlan, port_cfg, port_ratelimit, onu_mactable,
onu_qos, onu_statistics, onu_other groups — and installs them into
tm.ko's central capfun jump table. The capfun table is what cspd's
userspace IOCTLs ultimately dispatch through.

HW writes: **none** — pure callback registration.

Sub-calls (all into tm.ko, PLT addresses ≥ 0x2c000):
- `sw_public_port_vlan_func_reg(7 fn ptrs)` (PLT @ 0x2c1fc)
- `sw_public_port_cfg_func_reg(19 fn ptrs)` (PLT @ 0x2c038)
- `sw_public_port_ratelimit_func_reg(6 fn ptrs)` (PLT @ 0x2c294)
- `sw_public_onu_mactable_func_reg(15 fn ptrs)` (PLT @ 0x2c22c)
- `sw_public_onu_qos_func_reg(5 fn ptrs)` (PLT @ 0x2c11c)
- `sw_public_onu_statistics_func_reg(7 fn ptrs)` (PLT @ 0x2c310)
- `sw_public_onu_other_func_reg(10 fn ptrs)` (PLT @ 0x2c270)

In mainline? **unknown — to verify** — cspd uses these IOCTL paths;
mainline driver has no equivalent IOCTL surface.

Severity if missing: 🟢 informational — required for stock userspace
configuration (cspd) but not for the kernel data path.

---

## [fn-14] `private_capfun_register` @ decomp_all_switch.c:931 — internal ioctl ID→handler table

What it does: 48 sequential `fuc_table_node_create(id, handler)` calls,
each registering a single IOCTL command-id (0x3eb..0x41d + 0x47) and
its corresponding switch.ko-local handler function. This is the
private/extended IOCTL surface; `fuc_table_node_create` lives in
tm.ko (PLT @ 0x2c280) and stores into a shared linked list that
userspace queries via cspd.

HW writes: **none** — pure callback registration.

Sub-calls: 48× `fuc_table_node_create(0x3eb..0x41d, handler)`.

In mainline? **unknown — to verify** — cspd-only.

Severity if missing: 🟢 informational — required for advanced stock
userspace features (port stats, VLAN add/del, MAC filter table)
but not for the kernel data path.

---

## Cross-module dependencies summary

switch.ko's init touches **no MMIO directly**. Every register write
the fabric sees is mediated by tm.ko via the following API families:

| Family | Purpose | Called from |
|---|---|---|
| `zte_api_sw_global_init` | TPIDs, aging time, hash mode | chip_tm_init |
| `zte_api_sw_port_init` | per-port enable + link state | chip_tm_init |
| `zte_api_sw_vlan_set_*` | PVID + per-port VLAN config | chip_tm_init |
| `zte_api_sw_port_set_port_isolatemask` | port isolation matrix | chip_tm_init |
| `zte_api_sw_set_port_{brdcast,unicast,muticast}` | broadcast/unicast/multicast | chip_tm_init |
| `zte_api_pp_global_init` | PP global cfg | chip_tm_init |
| `zte_api_pp_set_cpu_queue_rate` | per-queue CPU pps | chip_tm_init |
| `zte_api_pp_set_trap_queue` | protocol → CPU queue | chip_tm_init |
| `zte_api_pp_set_pro_action` | protocol → fwd/trap/drop | chip_tm_init |
| `zte_api_sw_qos_add_port_streamselect` | ACL TCAM rule | sw_set_default_*_rule |
| `zte_api_sw_port_set_port_ratelimit` | per-port pps cap | sw_alarm_init |
| `tm_protocol_pkt_limit_pps_set` | per-direction pps cap | chip_tm_init + sw_alarm_init |
| `tm_set_p2pmode` | UNI-as-WAN mode bit | sw_set_p2pmode |
| `tm_cla_outspace_cfg_*` | classifier outspace size | chip_tm_init |
| `tm_acl_l2_fast_init` | L2 fast forward TCAM | sw_init_switch |
| `fpga_write_reg(0xd3000, 0x1f40fa0)` | single PP CSR poke | sw_alarm_init |
| `tm_tcont_secsch_hang_que_set` | tcont→queue (GPON/EPON only) | sw_qos_init |

The cumulative effect of all these calls during the stock boot is
what `zx_stock_table.h` captures as a replay table for the mainline
driver. Verification target: confirm that `zx_stock_table.h` includes
the writes that result from this orchestration order for
`g_pon_work_mode=0x10` (LAN-only).

---

## Decomp quality notes

- Functions at addresses ≥ `0x2c000` are PLT/GOT stubs and decompile
  as `halt_baddata()` — every "tm.ko API" listed above appears in the
  decomp this way. Not a bug; the relocation table is non-code.
- Ghidra renames `disableIRQinterrupts` /
  `coproc_movefrom_Privileged_only_Thread_and_Process_ID` for what's
  actually `local_irq_disable() + put_cpu()`/`smp_processor_id()` ARM
  idioms in the dev_get_by_name preempt-safety wrapper. Same gotcha as
  noted in the plat-zxylzb walk.
- The two `*_multi_config_init` stubs being empty is real — not a
  decomp artifact — those entry points exist purely as ABI hooks for
  cspd to call into; the work happens elsewhere.
- `register_bridge_notifier` (decomp_all_switch.c:14075) is a PLT
  stub; the actual notifier body is `sw_bridge_event` @
  decomp_all_switch.c:1992 in switch.ko, but it's registered through
  tm.ko.

---

## Walk status

- Top-level `init_module` mapped: **✓**
- Level-1 (sw_init_switch + register fns): **✓** (14 functions
  documented end-to-end)
- Level-2 (within chip_tm_init / sw_alarm_init / sw_set_default_*):
  **✓** — sub-call lists itemised; tm.ko/PP API surfaces enumerated
  but not chased (cross-module boundary).
- Level-3+: cross-module; chase via `decomp_all_tm.c` if needed.

---

# APPENDIX: Complete function inventory

The 16 functions in the init walk above ([fn-00..14], including [fn-09a/09b])
exhaust the `init_module → sw_init_switch` tree. switch.ko's decomp
contains **423 FUNCTION blocks total** — the rest are either:

1. **Local helpers** (235 entries, addresses `< 0x2c000`) that implement
   the ioctl/IGMP/QoS/VLAN/ACL surfaces but are NOT reached from
   `init_module`. They're only called from userspace via cspd-driven
   IOCTL dispatch (the tables built by [fn-13]/[fn-14]), from the RX/TX
   hot-path hooks installed in [fn-04], or from the alarm kthread spawned
   by [fn-10].

2. **Imported PLT stubs** (188 entries, addresses `≥ 0x2c000`) that
   Ghidra decompiles as `halt_baddata()` because the relocation table
   is non-code. Each represents one symbol from a `Requires:` module
   (`tm`, `plat-zxylzb`) or the kernel itself.

Entries below use sequential ids starting at **fn-100** to avoid
clashing with the existing fn-00..14. Address (Ghidra-displayed text
address) appears for traceability; `:line` is into
`decomp_all_switch.c`.

## Imported kernel symbols (PLT stubs)

Linux kernel exports linked by the loader. All decompile as
`halt_baddata()` — Ghidra cannot resolve PLT branches.

- [fn-100] `alloc_etherdev_mqs` @ 0x2c008 / switch.c:12459 — kernel: alloc multi-queue net_device
- [fn-101] `strcpy` @ 0x2c014 / switch.c:12483 — libc
- [fn-102] `rtnl_unlock` @ 0x2c020 / switch.c:12520 — kernel: rtnl mutex unlock
- [fn-103] `unregister_netdev` @ 0x2c050 / switch.c:12652 — kernel
- [fn-104] `__printk_ratelimit` @ 0x2c0c4 / switch.c:12736 — kernel
- [fn-105] `memcpy` @ 0x2c0e8 / switch.c:12796 — libc
- [fn-106] `kfree` @ 0x2c0ec / switch.c:12809 — kernel slab
- [fn-107] `eth_type_trans` @ 0x2c130 / switch.c:13061 — kernel: extract ethertype, advance skb->data
- [fn-108] `kfree_skb` @ 0x2c160 / switch.c:13133 — kernel sk_buff free
- [fn-109] `___ratelimit` @ 0x2c164 / switch.c:13145 — kernel ratelimit core
- [fn-110] `msecs_to_jiffies` @ 0x2c174 / switch.c:13181 — kernel
- [fn-111] `_raw_spin_unlock_bh` @ 0x2c178 / switch.c:13193 — kernel
- [fn-112] `__alloc_skb` @ 0x2c184 / switch.c:13241 — kernel
- [fn-113] `dev_queue_xmit_sk` @ 0x2c194 / switch.c:13289 — kernel: enqueue skb on net_device qdisc
- [fn-114] `kmem_cache_alloc` @ 0x2c198 / switch.c:13301 — kernel slab; ACL rule alloc uses this
- [fn-115] `capable` @ 0x2c1a4 / switch.c:13337 — kernel capability check
- [fn-116] `netif_receive_skb_sk` @ 0x2c1a8 / switch.c:13349 — kernel: hand skb to netif RX
- [fn-117] `strncmp` @ 0x2c204 / switch.c:13541 — libc
- [fn-118] `register_netdev` @ 0x2c208 / switch.c:13554 — kernel
- [fn-119] `strncpy` @ 0x2c214 / switch.c:13578 — libc
- [fn-120] `free_netdev` @ 0x2c220 / switch.c:13615 — kernel
- [fn-121] `memcmp` @ 0x2c264 / switch.c:13663 — libc
- [fn-122] `sysfs_create_group` @ 0x2c268 / switch.c:13676 — kernel sysfs
- [fn-123] `sscanf` @ 0x2c26c / switch.c:13688 — libc
- [fn-124] `printk` @ 0x2c274 / switch.c:13701 — kernel
- [fn-125] `__memzero` @ 0x2c2b4 / switch.c:13821 — libc memzero
- [fn-126] `netif_rx` @ 0x2c2c4 / switch.c:13869 — kernel
- [fn-127] `strcmp` @ 0x2c2c8 / switch.c:13881 — libc
- [fn-128] `kthread_create_on_node` @ 0x2c2d0 / switch.c:13906 — kernel
- [fn-129] `sprintf` @ 0x2c2d4 / switch.c:13918 — libc
- [fn-130] `__dev_kfree_skb_any` @ 0x2c33c / switch.c:14051 — kernel
- [fn-131] `register_bridge_notifier` @ 0x2c344 / switch.c:14075 — kernel bridge: hook for FDB events
- [fn-132] `netif_carrier_off` @ 0x2c34c / switch.c:14099 — kernel
- [fn-133] `dev_get_by_name` @ 0x2c3a8 / switch.c:14195 — kernel
- [fn-134] `_raw_spin_lock_bh` @ 0x2c3b4 / switch.c:14231 — kernel
- [fn-135] `netif_carrier_on` @ 0x2c3bc / switch.c:14255 — kernel
- [fn-136] `rtnl_lock` @ 0x2c3d4 / switch.c:14327 — kernel
- [fn-137] `dev_change_flags` @ 0x2c41c / switch.c:14531 — kernel (used to bring eth* up at init)
- [fn-138] `__aeabi_idivmod` @ 0x2c478 / switch.c:14615 — libgcc ARM EABI divmod
- [fn-139] `msleep` @ 0x2c47c / switch.c:14627 — kernel
- [fn-140] `wake_up_process` @ 0x2c0b0 / switch.c:12989 — kernel
- [fn-141] `msleep_interruptible` @ 0x2c0a8 / switch.c:12965 — kernel

## Imported tm.ko / plat-zxylzb symbols (PLT stubs)

Functions in sibling kernel modules switch.ko links against. switch.ko
is the policy layer; these are the SDK calls into tm.ko (fabric MMIO
driver) and plat-zxylzb (FPGA register helper).

### `zte_api_sw_*` family (tm.ko SDK — port/MAC/VLAN/QoS)

- [fn-150] `zte_api_sw_port_get_port_loopback` @ 0x2c000 / switch.c:12435 — tm.ko
- [fn-151] `zte_api_sw_mac_clear_macaddress` @ 0x2c00c / switch.c:12471 — tm.ko
- [fn-152] `zte_api_sw_port_set_port_flowcontrol` @ 0x2c01c / switch.c:12508 — tm.ko
- [fn-153] `zte_api_sw_port_get_port_ratelimit` @ 0x2c028 / switch.c:12544 — tm.ko
- [fn-154] `zte_api_sw_global_init` @ 0x2c03c / switch.c:12604 — tm.ko (called once from chip_tm_init)
- [fn-155] `zte_api_sw_mac_set_onu_stpaction` @ 0x2c040 / switch.c:12616 — tm.ko
- [fn-156] `zte_api_sw_vlan_set_port_inframemode` @ 0x2c044 / switch.c:12628 — tm.ko
- [fn-157] `zte_api_sw_port_get_port_statistics1` @ 0x2c04c / switch.c:12640 — tm.ko
- [fn-158] `zte_api_sw_port_get_port_mirror` @ 0x2c058 / switch.c:12676 — tm.ko
- [fn-159] `zte_api_sw_mac_set_onu_agingtime` @ 0x2c060 / switch.c:12700 — tm.ko
- [fn-160] `zte_api_sw_vlan_set_port_vlancfg` @ 0x2c06c / switch.c:12724 — tm.ko
- [fn-161] `zte_api_fast_l3_session_del` @ 0x2c07c / switch.c:12760 — tm.ko (L3 fast-fwd TCAM del)
- [fn-162] `zte_api_sw_qos_get_availbktid` @ 0x2c084 / switch.c:12784 — tm.ko
- [fn-163] `zte_api_sw_port_get_port_linkstate` @ 0x2c094 / switch.c:12821 — tm.ko (poll PHY link)
- [fn-164] `zte_api_sw_mac_set_port_macfiltermode` @ 0x2c0a4 / switch.c:12881 — tm.ko (and it's also a data array: indexed as `[port]` to get internal port id)
- [fn-165] `zte_api_sw_vlan_get_port_inframemode` @ 0x2c0a8 / switch.c:12893 — tm.ko
- [fn-166] `zte_api_sw_port_set_port_isolatemask` @ 0x2c0ac / switch.c:12905 — tm.ko (and also indexed as data: `[port]` gives internal port id mapping)
- [fn-167] `zte_api_sw_qos_add_port_streamselect` @ 0x2c0b4 / switch.c:12929 — tm.ko: ACL TCAM rule add
- [fn-168] `zte_api_sw_mac_set_port_learnlimit` @ 0x2c0c8 / switch.c:13013 — tm.ko (and the underlying global holds the LAN-port mask)
- [fn-169] `zte_api_pp_global_init` @ 0x2c0ac / switch.c:12977 — tm.ko PP init
- [fn-170] `zte_api_pp_set_cpu_queue_rate` @ 0x2c0d4 / switch.c:13049 — tm.ko: per-queue CPU pps
- [fn-171] `zte_api_sw_port_get_port_enable` @ 0x2c134 / switch.c:13073 — tm.ko
- [fn-172] `zte_api_sw_port_clear_port_count` @ 0x2c138 / switch.c:13085 — tm.ko
- [fn-173] `zte_api_sw_port_get_port_statistics4` @ 0x2c144 / switch.c:13109 — tm.ko
- [fn-174] `zte_api_sw_port_get_port_statistics3` @ 0x2c148 / switch.c:13121 — tm.ko
- [fn-175] `zte_api_sw_mac_get_port_learnlimit` @ 0x2c174 / switch.c:13205 — tm.ko
- [fn-176] `zte_api_sw_mac_clear_port_mactable` @ 0x2c188 / switch.c:13253 — tm.ko
- [fn-177] `zte_api_sw_port_init` @ 0x2c190 / switch.c:13277 — tm.ko (called N× from chip_tm_init)
- [fn-178] `zte_api_sw_qos_get_port_streamselect` @ 0x2c19c / switch.c:13313 — tm.ko: ACL TCAM rule lookup
- [fn-179] `zte_api_sw_port_get_port_linkmode` @ 0x2c1ac / switch.c:13361 — tm.ko
- [fn-180] `zte_api_sw_qos_get_port_schedule` @ 0x2c1bc / switch.c:13397 — tm.ko
- [fn-181] `zte_api_sw_port_set_port_enable` @ 0x2c1c0 / switch.c:13409 — tm.ko
- [fn-182] `zte_api_sw_mac_del_port_macfilterentry` @ 0x2c1c4 / switch.c:13421 — tm.ko
- [fn-183] `zte_api_sw_mac_set_onu_proaction` @ 0x2c1d0 / switch.c:13469 — tm.ko
- [fn-184] `zte_api_sw_vlan_get_port_vlancfg` @ 0x2c1d4 / switch.c:13481 — tm.ko
- [fn-185] `zte_api_sw_mac_add_port_macfilterentry` @ 0x2c1d8 / switch.c:13493 — tm.ko
- [fn-186] `zte_api_sw_qos_del_port_streamselect` @ 0x2c1e0 / switch.c:13517 — tm.ko: ACL TCAM rule del
- [fn-187] `zte_api_sw_port_set_port_floodcontrolmask` @ 0x2c1e4 / switch.c:13529 — tm.ko
- [fn-188] `zte_api_sw_set_port_brdcast` @ 0x2c218 / switch.c:13591 — tm.ko (struct-arg, called N× from chip_tm_init)
- [fn-189] `zte_api_sw_get_pon_port` @ 0x2c21c / switch.c:13603 — tm.ko: returns PON port id
- [fn-190] `zte_api_sw_set_port_unicast` @ 0x2c224 / switch.c:13627 — tm.ko (struct-arg)
- [fn-191] `zte_api_sw_qos_set_port_schedule` @ 0x2c278 / switch.c:13713 — tm.ko
- [fn-192] `zte_api_sw_mac_del_port_macaddress` @ 0x2c280 / switch.c:13737 — tm.ko (called from sw_bridge_event on STP FLUSH)
- [fn-193] `zte_api_sw_fast_entry_policy` @ 0x2c284 / switch.c:13749 — tm.ko: query fast-entry remaining capacity (used by hf_entry_police2)
- [fn-194] `zte_api_sw_phy_read` @ 0x2c288 / switch.c:13761 — tm.ko: MDIO read
- [fn-195] `zte_api_sw_set_port_muticast` @ 0x2c29c / switch.c:13809 — tm.ko (struct-arg) [sic — "muticast"]
- [fn-196] `zte_api_sw_port_get_port_statistics2` @ 0x2c2a4 / switch.c:13833 — tm.ko
- [fn-197] `zte_api_sw_port_get_port_flowcontrol` @ 0x2c2d8 / switch.c:13931 — tm.ko
- [fn-198] `zte_api_sw_port_get_port_multicastrate` @ 0x2c30c / switch.c:13967 — tm.ko
- [fn-199] `zte_api_sw_mac_add_port_macaddress` @ 0x2c314 / switch.c:13991 — tm.ko
- [fn-200] `zte_api_sw_get_wlan_port` @ 0x2c348 / switch.c:14087 — tm.ko: returns WLAN port id
- [fn-201] `zte_api_sw_phy_write` @ 0x2c350 / switch.c:14111 — tm.ko: MDIO write
- [fn-202] `zte_api_sw_port_set_port_broadcastrate` @ 0x2c368 / switch.c:14159 — tm.ko
- [fn-203] `zte_api_sw_vlan_get_port_pvid` @ 0x2c3b0 / switch.c:14219 — tm.ko
- [fn-204] `zte_api_fast_l3_session_use` @ 0x2c3c4 / switch.c:14291 — tm.ko: bump session refcount
- [fn-205] `zte_api_sw_other_set_onu_mtu` @ 0x2c3cc / switch.c:14315 — tm.ko: set per-port MTU
- [fn-206] `zte_api_pp_set_trap_queue` @ 0x2c3dc / switch.c:14351 — tm.ko PP: protocol→queue
- [fn-207] `zte_api_sw_port_get_port_broadcastrate` @ 0x2c3f0 / switch.c:14423 — tm.ko
- [fn-208] `zte_api_sw_port_set_port_linkmode` @ 0x2c3f4 / switch.c:14435 — tm.ko
- [fn-209] `zte_api_sw_port_set_port_loopback` @ 0x2c3f8 / switch.c:14447 — tm.ko
- [fn-210] `zte_api_sw_port_set_port_mirror` @ 0x2c3fc / switch.c:14459 — tm.ko
- [fn-211] `zte_api_sw_port_set_port_ratelimit` @ 0x2c400 / switch.c:14471 — tm.ko
- [fn-212] `zte_api_sw_port_set_port_multicastrate` @ 0x2c40c / switch.c:14507 — tm.ko
- [fn-213] `zte_api_sw_vlan_set_port_pvid` @ 0x2c410 / switch.c:14519 — tm.ko
- [fn-214] `zte_api_sw_port_clear_count_by_portid` @ 0x2c42c / switch.c:14579 — tm.ko
- [fn-215] `zte_api_sw_mac_get_onu_agingtime` @ 0x2c474 / switch.c:14603 — tm.ko
- [fn-216] `zte_api_fast_l3_session_add` @ 0x2c484 / switch.c:14651 — tm.ko: L3 fast-fwd TCAM add
- [fn-217] `zte_api_pp_set_pro_action` @ 0x2c3c0 / switch.c:14279 — tm.ko PP: protocol→action

### `tm_*` family (tm.ko low-level + table mgmt)

- [fn-220] `tm_ipv6table_delete_set` @ 0x2c004 / switch.c:12447 — tm.ko: delete IPv6 TCAM entry
- [fn-221] `tm_ipv6table_add_set` @ 0x2c030 / switch.c:12568 — tm.ko: add IPv6 TCAM entry
- [fn-222] `tm_port_unknwn_multicast_flood_set` @ 0x2c034 / switch.c:12580 — tm.ko: global unknown-mcast flood toggle
- [fn-223] `tm_port_statistics` @ 0x2c054 / switch.c:12664 — tm.ko
- [fn-224] `tm_port_802x_authen_get` @ 0x2c064 / switch.c:12712 — tm.ko
- [fn-225] `tm_onu_mac_addr_set` @ 0x2c080 / switch.c:12772 — tm.ko
- [fn-226] `tm_mac_learning_number_get` @ 0x2c098 / switch.c:12833 — tm.ko
- [fn-227] `tm_port_vlan_filter_get` @ 0x2c09c / switch.c:12845 — tm.ko
- [fn-228] `tm_port_unknwn_multicast_floodport_set` @ 0x2c0a0 / switch.c:12857 — tm.ko (also serves as data: port count)
- [fn-229] `tm_set_p2pmode` @ 0x2c0a4 (also see [fn-05]) / switch.c:12869 — tm.ko: UNI-as-WAN mode
- [fn-230] `tm_ipv4table_add_set` @ 0x2c0b8 / switch.c:12941 — tm.ko: add IPv4 TCAM entry
- [fn-231] `tm_tcont_que_sch_weight_get` @ 0x2c0c0 / switch.c:13001 — tm.ko (GPON-only, unused on H3600)
- [fn-232] `tm_vlan_check_ena_set` @ 0x2c0cc / switch.c:13025 — tm.ko (also serves as data: WAN port id)
- [fn-233] `tm_broadcst_vltrans_table_print_get` @ 0x2c0d0 / switch.c:13037 — tm.ko (also serves as data: wan mask)
- [fn-234] `tm_mactable_add_set` @ 0x2c15c / switch.c:13157 — tm.ko: add static FDB entry
- [fn-235] `tm_port_tls_get` @ 0x2c160 / switch.c:13169 — tm.ko: get transparent-LAN-service (Q-in-Q) flag
- [fn-236] `tm_vlan_statistics` @ 0x2c180 / switch.c:13229 — tm.ko
- [fn-237] `tm_port_status_set` @ 0x2c18c / switch.c:13265 — tm.ko: link up/down
- [fn-238] `tm_port_dft_multicst_vltrans_get` @ 0x2c1b8 / switch.c:13385 — tm.ko: default multicast VLAN translation
- [fn-239] `tm_port_unknwn_multicast_fwd_set` @ 0x2c1c8 / switch.c:13433 — tm.ko: per-port unknown-mcast fwd flag
- [fn-240] `tm_hash_mode_set` @ 0x2c1cc / switch.c:13445 — tm.ko: MAC hash function selector
- [fn-241] `tm_mac_ramaddr_sel_get` @ 0x2c1dc / switch.c:13505 — tm.ko: hash bucket address read
- [fn-242] `tm_port_protocol_pktdeal_get` @ 0x2c20c / switch.c:13566 — tm.ko: get per-port protocol action
- [fn-243] `tm_mactable_print_get` @ 0x2c25c / switch.c:13639 — tm.ko: dump FDB
- [fn-244] `tm_protocol_pkt_limit_pps_set` @ 0x2c260 (see [fn-10]) / switch.c:13651 — tm.ko
- [fn-245] `tm_broadcst_vltrans_table_delete_set` @ 0x2c27c / switch.c:13725 — tm.ko
- [fn-246] `tm_port_dft_unkunicst_vltrans_set` @ 0x2c294 / switch.c:13773 — tm.ko: default unknown-unicast VLAN trans
- [fn-247] `tm_acl_l2_fast_init` @ 0x2c2b8 (see [fn-01]) / switch.c:13845 — tm.ko: init L2 fast-fwd ACL
- [fn-248] `tm_hash_mode_get` @ 0x2c2cc / switch.c:13894 — tm.ko
- [fn-249] `tm_tcont_que_sch_sp_dwwr_mod_get` @ 0x2c2e0 / switch.c:13943 — tm.ko (GPON-only)
- [fn-250] `tm_tcont_sharp_set` @ 0x2c2ec / switch.c:13979 — tm.ko (GPON-only)
- [fn-251] `tm_multicst_vltrans_table_delete_set` @ 0x2c2f8 / switch.c:14003 — tm.ko
- [fn-252] `tm_port_dft_broadcst_vltrans_set` @ 0x2c328 / switch.c:14027 — tm.ko
- [fn-253] `tm_flow_rate_limit_set` @ 0x2c330 / switch.c:14039 — tm.ko
- [fn-254] `tm_port_vlan_filter_set` @ 0x2c358 / switch.c:14123 — tm.ko: enable per-port VLAN filtering
- [fn-255] `tm_port_dft_multicst_vltrans_set` @ 0x2c35c / switch.c:14135 — tm.ko
- [fn-256] `tm_ipv4table_lookup_get` @ 0x2c360 / switch.c:14147 — tm.ko: lookup IPv4 TCAM
- [fn-257] `tm_ipv6table_lookup_get` @ 0x2c36c / switch.c:14171 — tm.ko: lookup IPv6 TCAM
- [fn-258] `tm_tcont_secsch_hang_que_set` @ 0x2c3b8 / switch.c:14243 — tm.ko (GPON-only)
- [fn-259] `tm_ipv4table_delete_set` @ 0x2c3c0 / switch.c:14267 — tm.ko
- [fn-260] `tm_cla_outspace_cfg_set` @ 0x2c3c8 (see [fn-06]) / switch.c:14303 — tm.ko: classifier outspace
- [fn-261] `tm_tcont_que_sch_sp_dwwr_mod_set` @ 0x2c3d8 / switch.c:14339 — tm.ko (GPON-only)
- [fn-262] `tm_port_dft_unkunicst_vltrans_get` @ 0x2c3e0 / switch.c:14387 — tm.ko
- [fn-263] `tm_port_tls_set` @ 0x2c3e4 / switch.c:14399 — tm.ko: enable Q-in-Q on port
- [fn-264] `tm_mactable_delete_set` @ 0x2c3e8 / switch.c:14411 — tm.ko: delete FDB entry
- [fn-265] `tm_broadcst_vltrans_table_add_set` @ 0x2c408 / switch.c:14495 — tm.ko
- [fn-266] `tm_vlan_stat_config` @ 0x2c418 / switch.c:14543 — tm.ko: VLAN statistics enable
- [fn-267] `tm_port_protocol_pktdeal_set` @ 0x2c41c / switch.c:14555 — tm.ko: per-port protocol action
- [fn-268] `tm_multicst_vltrans_table_add_set` @ 0x2c420 / switch.c:14567 — tm.ko
- [fn-269] `tm_cla_outspace_cfg_get` @ 0x2c430 (see [fn-06]) / switch.c:14591 — tm.ko
- [fn-270] `tm_tcont_que_sch_weight_set` @ 0x2c480 / switch.c:14639 — tm.ko (GPON-only)
- [fn-271] `tm_port_dft_broadcst_vltrans_get` @ 0x2c488 / switch.c:14663 — tm.ko
- [fn-272] `tm_port_802x_authen_set` @ 0x2c48c / switch.c:14675 — tm.ko: 802.1x authen enable

### Other tm.ko / plat-zxylzb / cspd imports

- [fn-280] `Kernel_ASEND` @ 0x2c018 / switch.c:12496 — kernel: cspd async send
- [fn-281] `aclEssidToWlanIDMMap2` @ 0x2c024 / switch.c:12532 — tm.ko: ESSID→IDM map
- [fn-282] `npu_register_driver` @ 0x2c02c (see [fn-11]) / switch.c:12556 — NPU module: register hardfast callbacks
- [fn-283] `sw_public_port_cfg_func_reg` @ 0x2c038 (see [fn-13]) / switch.c:12592 — tm.ko capfun reg
- [fn-284] `fuc_table_node_clear` @ 0x2c05c / switch.c:12688 — tm.ko: clear private capfun table (sic — "fuc")
- [fn-285] `sw_public_onu_other_func_reg` @ 0x2c078 (see [fn-13]) / switch.c:12748 — tm.ko
- [fn-286] `sw_public_onu_statistics_func_reg` @ 0x2c0b0 / switch.c:12917 — tm.ko
- [fn-287] `sw_public_port_vlan_func_reg` @ 0x2c0b8 / switch.c:12953 — tm.ko
- [fn-288] `aclWlanToIdmReset` @ 0x2c0fc (see [fn-03]) / switch.c:13097 — tm.ko
- [fn-289] `spa_set_hashram` @ 0x2c178 / switch.c:13217 — tm.ko or plat: hashram poke
- [fn-290] `ffe_receive_skb` @ 0x2c1a0 / switch.c:13325 — tm.ko: fast-fwd RX hook
- [fn-291] `CspGetSwInfo` @ 0x2c1b4 (see [fn-02]) / switch.c:13373 — cspd kernel-shared struct accessor
- [fn-292] `sw_public_onu_qos_func_reg` @ 0x2c11c / switch.c:13457 — tm.ko
- [fn-293] `sw_public_onu_mactable_func_reg` @ 0x2c22c / switch.c:13955 — tm.ko
- [fn-294] `aclWLANToIDMEssidCfg2` @ 0x2c240 (see [fn-03]) / switch.c:14015 — tm.ko
- [fn-295] `ffe_learn_skb` @ 0x2c340 / switch.c:14063 — tm.ko: fast-fwd learning hook
- [fn-296] `sw_public_port_ratelimit_func_reg` @ 0x2c294 / switch.c:14183 — tm.ko
- [fn-297] `fuc_table_node_create` @ 0x2c280 (see [fn-14]) / switch.c:14207 — tm.ko: private capfun node create
- [fn-298] `LedActionSet` @ 0x2c2b0 / switch.c:13785 — plat-zxylzb: LED control
- [fn-299] `fpga_write_reg` @ 0x2c1f0 / switch.c:13797 — plat-zxylzb: FPGA CSR write
- [fn-300] `fpga_read_reg` @ 0x2c2b8 / switch.c:14375 — plat-zxylzb: FPGA CSR read
- [fn-301] `CSPKernel_skb_SelectQueue` @ 0x2c2c0 / switch.c:13857 — cspd: queue-select callback
- [fn-302] `spa_set_matchram` @ 0x2c4f4 (?) / switch.c:14363 — tm.ko: matchram (TCAM matchram) poke
- [fn-303] `IfName2WlanIdmMap` @ 0x2c404 / switch.c:14483 — tm.ko: ifname→IDM map
- [fn-304] `CspGetPortInfo` @ 0x2c4cc (see [fn-02]) / switch.c:14687 — cspd kernel-shared struct accessor

## switch.ko-local: netdev ops (per-port netdev callbacks installed by [fn-04])

- [fn-310] `ethdrv_port_dev_open` @ switch.c:1 — net_device->open: no-op return 0.
- [fn-311] `ethdrv_port_dev_init` @ switch.c:10 — net_device->init: no-op return 0.
- [fn-312] `ethdrv_port_dev_destruct` @ switch.c:19 — net_device->destructor: no-op (used as destructor pointer; actual free goes via free_netdev).
- [fn-313] `ethdrv_port_dev_stop` @ switch.c:28 — net_device->stop: no-op return 0.
- [fn-314] `ethdrv_port_dev_ioctl` @ switch.c:37 — net_device->ioctl: no-op return 0.
- [fn-315] `ethdrv_port_dev_change_mtu` @ switch.c:46 — net_device->change_mtu: clamps to parent's max (`*(parent+0x14c)`), stores into `dev->mtu` at +0x14c. Returns -EOPNOTSUPP-ish (-34 = 0xffffffde) if too large.
- [fn-316] `ethdrv_port_dev_get_stats` @ switch.c:61 — returns `dev + 0x4c8` (pointer to embedded struct net_device_stats counters).
- [fn-317] `ethdrv_port_dev_set_mac_addr` @ switch.c:230 — copies sa->data into dev_addr; checks address family before write.
- [fn-318] `swport_dev_xmit_fin` @ switch.c:447 — TX continuation: bumps tx_packets/tx_bytes, calls `dev_queue_xmit_sk` on parent netdev. In LAN-mode (`g_pon_work_mode & 0x10`) and `wan_to_lan != 0` paths it re-targets the WAN port via `dev_get_by_name("pon"/"eth%d")`. Drops skb on missing parent.
- [fn-319] `ethdrv_recv_fin` @ switch.c:502 — RX continuation: bumps rx_packets/rx_bytes on stats, eth_type_trans + netif_receive_skb_sk on the chosen netdev. Drops skb if target dev is null.
- [fn-320] `pdt_ethdrv_rate_limit_1s` @ switch.c:409 — periodic counter clamp: clears `g_rev_packet_100ms` and updates `g_timestamp_1`. Called from a 1s timer in tm.ko presumably.

## switch.ko-local: RX/TX hot path

- [fn-321] `pdt_ethdrv_recv` @ switch.c:531 — **the RX trampoline installed as `switch_skb_recv`** (see [fn-04]). Big function: ratelimits debug printks against `g_eth_debug_mac/g_eth_vlan/g_eth_debug_vlan`, sniff debug dump if `g_debug_mode==7`, then dispatches the skb to either the correct LAN netdev or — for `pon`/`eth0` ingress — to ffe_receive_skb (tm.ko fast-fwd) or netif_receive_skb_sk. Re-targets WAN via `dev_get_by_name("eth0")` for ethertype 0x884c/0x8899 (LACP/Slow). Uses `disableIRQinterrupts + put_cpu` Ghidra noise = `local_irq_save+smp_processor_id` for refcnt dec on the looked-up dev.
- [fn-322] `pdt_ethdrv_send` @ switch.c:789 — **the TX trampoline** (mirror of pdt_ethdrv_recv). Selects the egress logical port based on dev name and WAN/LAN topology; ratelimits with the same window; final dispatch via dev_queue_xmit_sk on the parent.

## switch.ko-local: ACL / flow / hardfast helpers

- [fn-330] `sw_acl_setMtchInfo` @ switch.c:1035 — packs an ACL match-info struct (ruleType, pri, fields, masks) before calling add/del.
- [fn-331] `hf_entry_police2` @ switch.c:1149 — checks remaining hardfast slots: calls `zte_api_sw_fast_entry_policy()` for 4 counters, compares (DN or UP)+(other) against `UP_MAX_FAST_ENTRY`/`DN_MAX_FAST_ENTRY` and returns 1=ok, 0=full.
- [fn-332] `sw_acl_add_port_flowconfig` @ switch.c:1193 — kmem_cache_alloc 0xd0 → memzero 0x49c → memcpy from user buf → `zte_api_sw_qos_add_port_streamselect`. Trampoline wrapper for ACL TCAM rule add.
- [fn-333] `sw_acl_del_port_flowconfig` @ switch.c:1239 — mirror of add: `zte_api_sw_qos_del_port_streamselect`.
- [fn-334] `sw_acl_get_port_flowconfig` @ switch.c:1285 — calls `zte_api_sw_qos_get_port_streamselect`, writes results back into caller buf.
- [fn-335] `sw_cla_show_aclrule` @ switch.c:1375 — `return 0` stub. Likely was a debug dump that got compiled out.
- [fn-336] `l3_hardfastUnReg` @ switch.c:1412 — paired with [fn-11] `l3_hardfastReg`: unregisters NPU hardfast callbacks (called from cleanup_module).
- [fn-337] `FROM_WAN` @ switch.c:1421 — predicate: true iff dev name does NOT start with "pon" (RX side: from-WAN = not from PON).
- [fn-338] `TO_WAN` @ switch.c:1436 — predicate: true if dev name == "pon" or "ptm" or matches `eth%u` whose internal port id == `_tm_vlan_check_ena_set` (the WAN port).
- [fn-339] `TO_LAN` @ switch.c:1785 — predicate: dev name starts with "sw" (logical switch port).
- [fn-340] `sw_acl_l3_hardfast_session_add.part.1` @ switch.c:1476 — Ghidra-split body: builds an IPv4/v6 5-tuple session struct from skb (src/dst ip, ports, proto), classifies WAN vs LAN direction, then routes to `tm_ipv4table_add_set`/`tm_ipv6table_add_set` (tm.ko) + `zte_api_fast_l3_session_add` (tm.ko).
- [fn-341] `sw_acl_l3_hardfast_session_del.part.3` @ switch.c:1748 — Ghidra-split body: mirror of add, calls `tm_ipv4table_delete_set`/`tm_ipv6table_delete_set` + `zte_api_fast_l3_session_del`.
- [fn-342] `sw_acl_l3_hardfast_session_add` @ switch.c:1797 — wrapper: null-check + dispatch to `.part.1`.
- [fn-343] `hf_set_l3_entry` @ switch.c:1823 — NPU callback entry-point: dispatches to `sw_acl_l3_hardfast_session_add`, returns 1=ok / 0=fail (rate-limited error printk).
- [fn-344] `sw_acl_l3_hardfast_session_del` @ switch.c:1847 — wrapper: null-check + dispatch to `.part.3`.
- [fn-345] `hf_del_l3_entry` @ switch.c:1866 — NPU callback entry-point: dispatches to `sw_acl_l3_hardfast_session_del`.
- [fn-346] `sw_acl_l3_hardfast_flowstatus` @ switch.c:1890 — query hit-counter + age for an L3 hardfast session via `zte_api_fast_l3_session_use`.
- [fn-347] `hf_query_l3_status` @ switch.c:1929 — NPU callback entry-point: dispatches to `sw_acl_l3_hardfast_flowstatus`.
- [fn-348] `sw_acl_l3_hardfast_entry_show` @ switch.c:1951 — empty stub returning 0.

## switch.ko-local: VLAN / bridge / forwarding policy

- [fn-350] `sw_set_idm_isolate` @ switch.c:1960 — **direct FPGA poke**: `fpga_read_reg(0xe20f6) → mask bits 0x40/0x80 based on (param1=0|1, param2=0|1) → fpga_write_reg(0xe20f6, ...)`. Per-IDM (Identity-Module 0 or 1) isolate enable. Bit 0x40 = IDM0, 0x80 = IDM1.
- [fn-351] `sw_bridge_event` @ switch.c:1992 — bridge_notifier callback. On event==2 (STP TCN flush), parses dev name into port id then calls `zte_api_sw_mac_del_port_macaddress(port, mac, 0, 0)` to flush that port's FDB.
- [fn-352] `sw_set_wanport_qos` @ switch.c:2024 — masks bits 16-17 of a per-port struct field at `[_tm_vlan_check_ena_set * 0x14 + (- 0xbe2bce8)]` (a tm.ko-owned static, not MMIO). Same write seen referenced from [fn-01].
- [fn-353] `sw_set_mflow_config` @ switch.c:8046 — empty stub returning 0.
- [fn-354] `sw_multi_vlan_trans_deal` @ switch.c:10190 — VLAN translation orchestrator for IGMP/MLD multi-VLAN groups: iterates a config table and calls `tm_multicst_vltrans_table_*` add/delete.

## switch.ko-local: VLAN management (cspd IOCTL surface)

- [fn-360] `sw_vlan_set_port_inframemode` @ switch.c:7110 — trampoline → tm.ko `zte_api_sw_vlan_set_port_inframemode`.
- [fn-361] `sw_vlan_get_port_inframemode` @ switch.c:7134 — trampoline → tm.ko `zte_api_sw_vlan_get_port_inframemode`.
- [fn-362] `sw_vlan_set_port_pvid` @ switch.c:7193 — trampoline → tm.ko `zte_api_sw_vlan_set_port_pvid`.
- [fn-363] `sw_vlan_get_port_pvid` @ switch.c:7227 — trampoline → tm.ko `zte_api_sw_vlan_get_port_pvid`.
- [fn-364] `sw_vlan_set_port_vlancfg` @ switch.c:7263 — trampoline → tm.ko `zte_api_sw_vlan_set_port_vlancfg`.
- [fn-365] `sw_vlan_get_port_vlancfg` @ switch.c:7302 — trampoline → tm.ko `zte_api_sw_vlan_get_port_vlancfg`.
- [fn-366] `sw_vlan_add_port_vlantranslationentry` @ switch.c:7333 — `return 0` stub.
- [fn-367] `sw_vlan_del_port_vlantranslationentry` @ switch.c:7342 — `return 0` stub.
- [fn-368] `sw_vlan_add_port_dsvlantranslationentry` @ switch.c:7351 — trampoline → tm.ko `tm_broadcst_vltrans_table_add_set` (or similar; downstream VLAN translation).
- [fn-369] `sw_vlan_del_port_dsvlantranslationentry` @ switch.c:7423 — trampoline → tm.ko `tm_broadcst_vltrans_table_delete_set`.
- [fn-370] `sw_vlan_show_port_dsvlantranslationentry` @ switch.c:7493 — trampoline → tm.ko `tm_broadcst_vltrans_table_print_get`.
- [fn-371] `sw_vlan_set_port_defaultunivlantrans` @ switch.c:7508 — trampoline → tm.ko `tm_port_dft_unkunicst_vltrans_set`.
- [fn-372] `sw_vlan_get_port_defaultunivlantrans` @ switch.c:7537 — trampoline → tm.ko `tm_port_dft_unkunicst_vltrans_get`.
- [fn-373] `sw_vlan_set_port_defaultbrdvlantrans` @ switch.c:7571 — trampoline → tm.ko `tm_port_dft_broadcst_vltrans_set`.
- [fn-374] `sw_vlan_get_port_defaultbrdvlantrans` @ switch.c:7600 — trampoline → tm.ko `tm_port_dft_broadcst_vltrans_get`.
- [fn-375] `sw_vlan_add_port_dsmulvlantranslationentry` @ switch.c:7633 — trampoline → tm.ko `tm_multicst_vltrans_table_add_set`.
- [fn-376] `sw_vlan_del_port_dsmulvlantranslationentry` @ switch.c:7740 — trampoline → tm.ko `tm_multicst_vltrans_table_delete_set`.
- [fn-377] `sw_vlan_set_port_defaultmulvlantrans` @ switch.c:7847 — trampoline → tm.ko `tm_port_dft_multicst_vltrans_set`.
- [fn-378] `sw_vlan_get_port_defaultmulvlantrans` @ switch.c:7869 — trampoline → tm.ko `tm_port_dft_multicst_vltrans_get`.
- [fn-379] `sw_vlan_set_port_transparent` @ switch.c:7891 — trampoline → tm.ko `tm_port_tls_set` (transparent LAN service / Q-in-Q).
- [fn-380] `sw_vlan_get_port_transparent` @ switch.c:7933 — trampoline → tm.ko `tm_port_tls_get`.
- [fn-381] `sw_vlan_set_port_vlanfilter` @ switch.c:7975 — trampoline → tm.ko `tm_port_vlan_filter_set`.
- [fn-382] `sw_vlan_get_port_vlanfilter` @ switch.c:8007 — trampoline → tm.ko `tm_port_vlan_filter_get`.

## switch.ko-local: Bridge / FDB / MAC table (cspd IOCTL surface)

- [fn-390] `sw_mac_set_port_macfiltermode` @ switch.c:2744 — trampoline → tm.ko `zte_api_sw_mac_set_port_macfiltermode`.
- [fn-391] `sw_mac_get_port_macfiltermode` @ switch.c:2768 — trampoline.
- [fn-392] `sw_mac_add_port_macfilterentry` @ switch.c:2780 — trampoline → tm.ko `zte_api_sw_mac_add_port_macfilterentry`.
- [fn-393] `sw_mac_del_port_macfilterentry` @ switch.c:2815 — trampoline → tm.ko `zte_api_sw_mac_del_port_macfilterentry`.
- [fn-394] `sw_mac_get_port_macfilterentry` @ switch.c:2850 — trampoline.
- [fn-395] `sw_mac_set_onu_stpaction` @ switch.c:2862 — trampoline → tm.ko `zte_api_sw_mac_set_onu_stpaction`.
- [fn-396] `sw_mac_get_onu_stpaction` @ switch.c:2899 — trampoline.
- [fn-397] `sw_mac_set_onu_proaction` @ switch.c:2911 — trampoline → tm.ko `zte_api_sw_mac_set_onu_proaction`.
- [fn-398] `sw_mac_get_onu_proaction` @ switch.c:2936 — trampoline.
- [fn-399] `sw_mac_set_onu_agingtime` @ switch.c:2948 — trampoline → tm.ko `zte_api_sw_mac_set_onu_agingtime`.
- [fn-400] `sw_mac_get_onu_agingtime` @ switch.c:2969 — trampoline → tm.ko `zte_api_sw_mac_get_onu_agingtime`.
- [fn-401] `sw_mac_set_port_learnlimit` @ switch.c:2995 — trampoline → tm.ko `zte_api_sw_mac_set_port_learnlimit`.
- [fn-402] `sw_mac_get_port_learnlimit` @ switch.c:3022 — trampoline → tm.ko `zte_api_sw_mac_get_port_learnlimit`.
- [fn-403] `sw_mac_add_port_macaddress` @ switch.c:3059 — trampoline → tm.ko `zte_api_sw_mac_add_port_macaddress`.
- [fn-404] `sw_mac_del_port_macaddress` @ switch.c:3094 — trampoline → tm.ko `zte_api_sw_mac_del_port_macaddress`.
- [fn-405] `sw_mac_show_macaddress` @ switch.c:3129 — trampoline → tm.ko `tm_mactable_print_get`.
- [fn-406] `sw_mac_clear_macaddress` @ switch.c:3145 — trampoline → tm.ko `zte_api_sw_mac_clear_macaddress`.
- [fn-407] `sw_mac_show_port_mactable` @ switch.c:3161 — trampoline → tm.ko `tm_mactable_print_get` (per-port).
- [fn-408] `sw_mac_clear_port_mactable` @ switch.c:3173 — trampoline → tm.ko `zte_api_sw_mac_clear_port_mactable`.
- [fn-409] `sw_mac_get_port_learnnum` @ switch.c:3196 — trampoline → tm.ko `tm_mac_learning_number_get`.
- [fn-410] `sw_mac_get_onu_macentrynum` @ switch.c:3230 — trampoline → tm.ko `tm_mac_learning_number_get` summed across ports.
- [fn-411] `sw_mac_add_cpu_macaddress` @ switch.c:3269 — wraps tm.ko `tm_mactable_add_set` with port=CPU/local.
- [fn-412] `sw_mac_del_cpu_macaddress` @ switch.c:3358 — wraps tm.ko `tm_mactable_delete_set`.
- [fn-413] `sw_mac_show_cpu_macaddress` @ switch.c:3436 — wraps `tm_mactable_print_get`.
- [fn-414] `sw_mac_add_port_macadd_feature` @ switch.c:3474 — extended FDB add with feature flags via `tm_mactable_add_set`.
- [fn-415] `sw_mac_del_port_macadd_feature` @ switch.c:3534 — extended FDB del.
- [fn-416] `sw_mac_set_mac_hashmode` @ switch.c:3594 — trampoline → tm.ko `tm_hash_mode_set` (selects MAC-hash function).
- [fn-417] `sw_mac_get_mac_hashmode` @ switch.c:3613 — trampoline → tm.ko `tm_hash_mode_get`.

## switch.ko-local: Multicast / IGMP / MLD

- [fn-430] `sw_multicast_en` @ switch.c:4924 — top-level multicast enable/disable. Iterates over the LAN-port mask (`zte_api_sw_mac_set_port_learnlimit | DAT_0002c0e2 | DAT_0002c0e6`) and toggles `tm_port_unknwn_multicast_flood_set(5,en)`, `_floodport_set`, `_fwd_set`, `tm_port_dft_multicst_vltrans_set` for each. Direct call surface from cspd.
- [fn-431] `sw_wlan_idmessid_map` @ switch.c:4990 — empty stub returning 0.
- [fn-432] `sw_essid_wlanidm_map` @ switch.c:4999 — empty stub returning 0.
- [fn-433] `drv_get_igmp_portlistBCD` @ switch.c:8055 — extract IGMP join port list from a Linux bridge mcast forwarding DB into BCD-encoded mask format.
- [fn-434] `drv_get_mld_portlistBCD` @ switch.c:8173 — IPv6 MLD equivalent of fn-433.
- [fn-435] `drv_add_igmp_addr_epon_sfu` @ switch.c:8321 — legacy/unused (EPON SFU): add IGMP group MAC to multicast TCAM. Not exercised on H3600 (LAN-only).
- [fn-436] `drv_del_igmp_addr_epon_sfu` @ switch.c:8395 — legacy/unused.
- [fn-437] `drv_add_mld_addr_epon_sfu` @ switch.c:8463 — legacy/unused.
- [fn-438] `drv_del_mld_addr_epon_sfu` @ switch.c:8536 — legacy/unused.
- [fn-439] `drv_add_igmp_addr_gpon_sfu` @ switch.c:8609 — legacy/unused (GPON SFU).
- [fn-440] `drv_del_igmp_addr_gpon_sfu` @ switch.c:8917 — legacy/unused.
- [fn-441] `drv_add_mld_addr_gpon_sfu` @ switch.c:9332 — legacy/unused.
- [fn-442] `drv_del_mld_addr_gpon_sfu` @ switch.c:9711 — legacy/unused.
- [fn-443] `sw_igmp_mulrule_deal` @ switch.c:10352 — IGMP rule dispatcher: picks epon vs gpon path based on `g_pon_work_mode`. On LAN-only mode this routes nowhere useful.
- [fn-444] `sw_add_igmp_addr_e8v4` @ switch.c:10440 — add IGMP group entry (E8 stands for the second-gen H3600 PON variant — legacy on our LAN-only unit).
- [fn-445] `sw_del_igmp_addr_e8v4` @ switch.c:10521 — legacy.
- [fn-446] `sw_mld_mulrule_deal` @ switch.c:10613 — MLD rule dispatcher (IPv6 variant of fn-443).
- [fn-447] `sw_add_mld_addr_e8v4` @ switch.c:10716 — legacy.
- [fn-448] `sw_del_mld_addr_e8v4` @ switch.c:10794 — legacy.

## switch.ko-local: QoS / scheduler

- [fn-460] `sw_qos_select_queue` @ switch.c:5984 — `dev_qos_select_queue` callback installed by [fn-12]. Picks a TX queue from skb priority via a static map.
- [fn-461] `qos_global_para_clr` @ switch.c:6006 — zeros `g_qos_queue` (0x60 bytes) and sets `g_tcont_size/start` based on `g_switch_debug_level`.
- [fn-462] `sw_qos_vdsl_up` @ switch.c:6063 — VDSL-specific QoS uplink path (legacy/unused on H3600).
- [fn-463] `sw_qos_set_port_schedule` @ switch.c:6084 — trampoline → tm.ko `zte_api_sw_qos_set_port_schedule`.
- [fn-464] `sw_qos_get_port_schedule` @ switch.c:6109 — trampoline → tm.ko.
- [fn-465] `sw_qos_set_tcontschedule` @ switch.c:6147 — programs T-CONT scheduler via tm.ko `tm_tcont_*` (GPON-only; unused on H3600).
- [fn-466] `sw_qos_get_tcontschedule` @ switch.c:6205 — mirror getter (GPON-only).
- [fn-467] `sw_qos_get_availbktid` @ switch.c:6272 — trampoline → tm.ko `zte_api_sw_qos_get_availbktid`.
- [fn-468] `sw_qos_set_trustppqueue` @ switch.c:6313 — `return 0` stub.
- [fn-469] `sw_qos_get_trustppqueue` @ switch.c:6322 — `return 0` stub.
- [fn-470] `sw_qos_set_opritoqueue` @ switch.c:6331 — `return 0` stub.
- [fn-471] `sw_qos_get_opritoqueue` @ switch.c:6340 — `return 0` stub.
- [fn-472] `qos_info_show` @ switch.c:6349 — debug dump of `g_qos_queue` state via printk.
- [fn-473] `pon_driver_adapter_schedue_mode_set` @ switch.c:6378 — PON-driver schedule mode setter (GPON-only).
- [fn-474] `wan_driver_adapter_schedue_mode_set` @ switch.c:6430 — WAN-driver schedule mode setter (xDSL legacy).
- [fn-475] `sw_qos_set_mode_schedule` @ switch.c:6467 — fans out to fn-473 / fn-474 based on work_mode.
- [fn-476] `sw_qos_set_queue` @ switch.c:6495 — trampoline to tm.ko T-CONT helpers (GPON-only).
- [fn-477] `sw_qos_set_rcqueue` @ switch.c:6592 — RC (rate-control?) queue setter.
- [fn-478] `sw_qos_set_overall_bandwidth` @ switch.c:6629 — sets overall BW limit via tm.ko.
- [fn-479] `sw_qos_get_queue_id` @ switch.c:6683 — `return 0` stub.

## switch.ko-local: Per-port operations (sw_port_*)

- [fn-490] `sw_port_set_port_enable` @ switch.c:5147 — trampoline → tm.ko `zte_api_sw_port_set_port_enable`.
- [fn-491] `sw_port_get_port_enable` @ switch.c:5178 — trampoline → tm.ko.
- [fn-492] `sw_port_set_port_flowcontrol` @ switch.c:5211 — trampoline → tm.ko.
- [fn-493] `sw_port_get_port_flowcontrol` @ switch.c:5234 — trampoline → tm.ko.
- [fn-494] `sw_port_set_port_isolate` @ switch.c:5269 — simple wrapper that builds isolatemask for one port and calls fn-495.
- [fn-495] `sw_port_get_port_isolate` @ switch.c:5283 — `return 0` stub.
- [fn-496] `sw_port_set_port_isolatemask` @ switch.c:5295 — trampoline → tm.ko `zte_api_sw_port_set_port_isolatemask` (translates logical port via the macfiltermode table).
- [fn-497] `sw_port_get_port_isolatemask` @ switch.c:5334 — `return 0` stub.
- [fn-498] `sw_port_set_port_floodcontrol` @ switch.c:5346 — `return 0` stub.
- [fn-499] `sw_port_get_port_floodcontrol` @ switch.c:5358 — `return 0` stub.
- [fn-500] `sw_port_set_port_floodcontrolmask` @ switch.c:5370 — trampoline → tm.ko `zte_api_sw_port_set_port_floodcontrolmask`.
- [fn-501] `sw_port_get_port_floodcontrolmask` @ switch.c:5411 — `return 0` stub.
- [fn-502] `sw_port_set_port_linkmode` @ switch.c:5423 — trampoline → tm.ko `zte_api_sw_port_set_port_linkmode`.
- [fn-503] `sw_port_get_port_linkmode` @ switch.c:5457 — trampoline → tm.ko.
- [fn-504] `sw_port_get_port_linkstate` @ switch.c:5496 — trampoline → tm.ko `zte_api_sw_port_get_port_linkstate`. Also called from sw_alarm_scanforalarm.
- [fn-505] `sw_port_set_port_mirror` @ switch.c:5537 — trampoline → tm.ko.
- [fn-506] `sw_port_get_port_mirror` @ switch.c:5599 — trampoline → tm.ko.
- [fn-507] `sw_port_set_port_loopback` @ switch.c:5645 — trampoline → tm.ko.
- [fn-508] `sw_port_get_port_loopback` @ switch.c:5670 — trampoline → tm.ko.
- [fn-509] `sw_port_set_port_factoryloopback` @ switch.c:5703 — factory-loopback variant (uses MDIO + phy_read/write).
- [fn-510] `sw_port_get_port_factoryloopback` @ switch.c:5728 — getter.
- [fn-511] `sw_port_set_port_proaction` @ switch.c:5769 — trampoline → tm.ko `tm_port_protocol_pktdeal_set`.
- [fn-512] `sw_port_get_port_proaction` @ switch.c:5813 — trampoline → tm.ko `tm_port_protocol_pktdeal_get`.
- [fn-513] `sw_port_set_port_802dot1xen` @ switch.c:5864 — trampoline → tm.ko `tm_port_802x_authen_set`.
- [fn-514] `sw_port_get_port_802dot1xen` @ switch.c:5915 — trampoline → tm.ko `tm_port_802x_authen_get`.
- [fn-515] `sw_port_set_ethdev_carrier` @ switch.c:5963 — sets `g_ethdev_carrierFlag` (gates the alarm kthread's link-poll loop).
- [fn-516] `sw_port_clear_port_count` @ switch.c:3639 — trampoline → tm.ko `zte_api_sw_port_clear_port_count`.
- [fn-517] `sw_port_clear_port_count_byportid` @ switch.c:3655 — trampoline → tm.ko `zte_api_sw_port_clear_count_by_portid`.
- [fn-518] `sw_port_get_port_statistics1` @ switch.c:3671 — trampoline → tm.ko `zte_api_sw_port_get_port_statistics1`.
- [fn-519] `sw_port_get_port_statistics2` @ switch.c:3830 — trampoline → tm.ko statistics2.
- [fn-520] `sw_port_get_port_statistics3` @ switch.c:3933 — trampoline → tm.ko statistics3.
- [fn-521] `sw_port_get_port_statistics4` @ switch.c:4072 — trampoline → tm.ko statistics4.
- [fn-522] `sw_port_get_port_rmonstats` @ switch.c:4191 — `return 0` stub (RMON not implemented).
- [fn-523] `sw_port_get_port_statistics` @ switch.c:4200 — aggregates statistics1..4 calls into one buffer.
- [fn-524] `sw_port_get_port_vlanstatistics` @ switch.c:4276 — trampoline → tm.ko `tm_vlan_statistics`.
- [fn-525] `sw_port_set_port_ratelimit` @ switch.c:6692 — trampoline → tm.ko `zte_api_sw_port_set_port_ratelimit`.
- [fn-526] `sw_port_get_port_ratelimit` @ switch.c:6716 — trampoline → tm.ko.
- [fn-527] `sw_port_set_port_broadcastrate` @ switch.c:6757 — trampoline → tm.ko.
- [fn-528] `sw_port_get_port_broadcastrate` @ switch.c:6790 — trampoline → tm.ko.
- [fn-529] `sw_port_set_cpu_broadcastrate` @ switch.c:6831 — `return 0` stub.
- [fn-530] `sw_port_set_cpu_queue_ratelimit` @ switch.c:6851 — `return 0` stub.
- [fn-531] `sw_port_set_port_multiprorate` @ switch.c:6860 — `return 0` stub.
- [fn-532] `sw_port_get_port_multiprorate` @ switch.c:6872 — `return 0` stub.
- [fn-533] `sw_port_set_port_multicastrate` @ switch.c:6884 — trampoline → tm.ko `zte_api_sw_port_set_port_multicastrate`.
- [fn-534] `sw_port_get_port_multicastrate` @ switch.c:6917 — trampoline → tm.ko.

## switch.ko-local: Register / PHY raw access (debugfs-style)

- [fn-540] `sw_reg_set_readreg` @ switch.c:6958 — raw register read: calls `fpga_read_reg(*param_1)` directly. Byte-swaps result before returning. Exposed as IOCTL/sysfs for debug.
- [fn-541] `sw_reg_set_writereg` @ switch.c:7006 — raw register write: byte-swaps value then `fpga_write_reg`. **Userspace can poke arbitrary fabric registers via this entry.**
- [fn-542] `sw_phy_reg_set_readreg` @ switch.c:7044 — trampoline → tm.ko `zte_api_sw_phy_read` (MDIO).
- [fn-543] `sw_phy_reg_set_writereg` @ switch.c:7081 — trampoline → tm.ko `zte_api_sw_phy_write` (MDIO).

## switch.ko-local: Alarm / LED / link-monitor

- [fn-550] `Alarm_Msg` @ switch.c:4583 — formats a port-state-change message and `Kernel_ASEND`s it to userspace ("cspd.cspd.switch_mgr" target, msg id 0xa401 link-up / 0xa402 link-down). Includes ethN name, link/speed/duplex fields.
- [fn-551] `turn_on_led_green` @ switch.c:4619 — `LedActionSet(0xb100, port-1)` (plat-zxylzb); sets `g_LAN_ON_Flag=1`.
- [fn-552] `turn_off_led` @ switch.c:4631 — `LedActionSet(0xb200, port-1)`; clears flag.
- [fn-553] `turn_flash_led` @ switch.c:4642 — fetches statistics1; if rx packets advanced, calls `LedActionSet(0x2200, port-1)` to blink.
- [fn-554] `turn_flash_led.part.1` @ switch.c:12425 — Ghidra-split tail of fn-553.
- [fn-555] `sw_alarm_scanforalarm` @ switch.c:4674 — **the alarm kthread body**. Per-port loop: reads link state, compares against last state, on change → `Alarm_Msg` + `netif_carrier_on/off` + LED action. **Direct FPGA pokes**: `fpga_write_reg(0xd3000, 0x1f40fa0)` on link DOWN, `fpga_write_reg(0xd3000, 0x3f40050)` on link UP. The 0xd3000 register appears to be a global PP CPU rate-limit knob (8000pps idle, 1Gbps active).
- [fn-556] `sw_port_alarm_kthread` @ switch.c:4837 — infinite kthread: every 500ms (`sw_timerbase * 500`), calls fn-555 if `g_ethdev_carrierFlag != 0`. After 90 ticks (~45s), calls `tm_protocol_pkt_limit_pps_set(*, *, 0, 0)` for queues 1..7 and disables WLAN port rate limits. This is the **periodic re-arm** referenced from sw_alarm_init.

## switch.ko-local: WAN IP / WAN-LAN switch

- [fn-560] `sw_wancip_set` @ switch.c:4897 — `return 0` stub.
- [fn-561] `sw_wancip_get` @ switch.c:4906 — `return 0` stub.
- [fn-562] `sw_wancip_del` @ switch.c:4915 — `return 0` stub.
- [fn-563] `sw_other_set_wan_lan_switch` @ switch.c:4366 — **direct FPGA poke** `fpga_read_reg(0xe8007) → mask 0xc1ffffff → fpga_write_reg(0xe8007, masked)`. Reconfigures which port is the WAN port via `_tm_vlan_check_ena_set` global + `tm_set_p2pmode`. Modes: 0=WAN to default, 1=AUTO, 2..5=eth1..eth4 as WAN, 6=all-LAN.
- [fn-564] `sw_other_set_onu_mtu` @ switch.c:4469 — clamps MTU to 2000, calls `zte_api_sw_other_set_onu_mtu` per port (5 entries).
- [fn-565] `sw_other_get_onu_mtu` @ switch.c:4500 — `printk("not support now!")` + return 0.
- [fn-566] `sw_other_set_area_code` @ switch.c:5008 — `return 0` stub.
- [fn-567] `sw_other_get_port_from_devname` @ switch.c:5017 — wraps `get_sw_port_from_devname` for external callers.

## switch.ko-local: Speed/duplex translation helpers

- [fn-570] `sw_ztespeed_to_cspplatspeed` @ switch.c:5038 — maps internal speed enum (0/1/2/3) to cspd's encoding (0=1G,1=100M,2=10M,3=Down).
- [fn-571] `sw_zteduplex_to_cspplatduplex` @ switch.c:5058 — maps internal duplex code to cspd's (0=Half,1=Full).
- [fn-572] `cspplatspeed_to_sw_ztespeed` @ switch.c:5075 — inverse of fn-570.
- [fn-573] `cspplatduplex_to_sw_zteduplex` @ switch.c:5095 — inverse of fn-571.
- [fn-574] `get_sw_port_from_devname` @ switch.c:4511 — parses `eth%d`/`pon`/`ptm` into the internal port id via `zte_api_sw_mac_set_port_macfiltermode[]` lookup.

## switch.ko-local: NPU L3 hardfast helpers

NPU = the hardware "Network Processing Unit" that L3 fast-forwarding sits
on (programmed via tm.ko TCAM). switch.ko owns the session table.

- [fn-580] `npu_drv_indev_learn` @ switch.c:10899 — `return 0` stub (no inbound learning).
- [fn-581] `npu_drv_outdev_learn` @ switch.c:10910 — `return 0` stub.
- [fn-582] `npu_hff_register` @ switch.c:10920 — copies fn ptrs into `npu_hff_func_tbl`, calls `npu_register_driver`, zeros 0x420-byte session table. Called from l3_hardfastReg ([fn-11]).
- [fn-583] `npu_drv_free_flow` @ switch.c:10941 — frees an L3 flow entry slot.
- [fn-584] `npu_drv_refresh_flow` @ switch.c:10955 — refresh/touch a flow's age via `zte_api_fast_l3_session_use`.
- [fn-585] `npu_drv_lookup_multientry` @ switch.c:11274 — search multi-VLAN entry table.
- [fn-586] `npu_drv_delete_multivlan` @ switch.c:11299 — delete multi-VLAN entry from tm.ko TCAM.
- [fn-587] `npu_drv_create_multivlan` @ switch.c:11350 — create multi-VLAN entry; acquires `g_multivlan_lock` spin.
- [fn-588] `npu_drv_dup_flow` @ switch.c:11420 — duplicate flow entry (for bidirectional or multi-target offload).
- [fn-589] `npu_drv_delete_flow.part.1` @ switch.c:11464 — Ghidra-split body: tear down NPU L3 flow + tm.ko TCAM del.
- [fn-590] `npu_drv_delete_flow` @ switch.c:11774 — wrapper around `.part.1`.
- [fn-591] `npu_drv_create_flow.part.2` @ switch.c:11846 — Ghidra-split body: ~400 lines that build the flow's 5-tuple, allocate a session slot, program tm.ko TCAM (ipv4/ipv6 add_set), bump refcounts.
- [fn-592] `npu_drv_create_flow` @ switch.c:12240 — wrapper around `.part.2`.
- [fn-593] `sw_update_match_rule_ip` @ switch.c:12312 — patches an existing ACL rule's IP field (used by NPU multi-VLAN re-program).
- [fn-594] `sw_set_trap_cpu_ip` @ switch.c:12383 — installs a "trap to CPU" ACL TCAM rule for a given IP (control-plane intercept).

## switch.ko-local: Cleanup / exit

- [fn-600] `cleanup_module` @ switch.c:12414 — module exit: 2-liner. Calls `l3_hardfastUnReg()` (fn-336) and `fuc_table_node_clear()` (PLT into tm.ko). Notably it does **NOT** unregister the per-port netdevs (allocated in [fn-04]), unregister `switch_skb_recv`, kill the alarm kthread, or undo any of the chip_tm_init register programming. Implies switch.ko is never expected to be rmmod'd in production.

## switch.ko-local: Miscellaneous / data accessors

- [fn-610] `set_mii_dev_name_type.part.0` @ switch.c:243 — Ghidra-split helper to format `eth%u` device name templates used by pdt_ethdriver_init.
- [fn-611] `set_mii_dev_name_type` @ switch.c:276 — wrapper around fn-610.
- [fn-612] `ethdrv_del_br_device` @ switch.c:257 — deletes a netdev from a Linux bridge (helper for cspd bridge-mgr; calls `dev_get_by_name` + `unregister_netdev`).
- [fn-613] `ethdrv_set_wanportid` @ switch.c:290 — sets the global `_tm_vlan_check_ena_set` (the WAN port id) from cspd.
- [fn-614] `ethdrv_test_show` @ switch.c:70 — sysfs `cat` handler: dumps debug-mode, debug-mac, vlan settings, capability help text.
- [fn-615] `ethdrv_test_store` @ switch.c:127 — sysfs `echo` handler: parses `dbg recv|mac|send|close|all`, `mac xx:xx:..`, `vlan N`, etc., updates globals `g_debug_mode`, `g_eth_debug_mac`, `g_eth_debug_vlan`.
- [fn-616] `swport_dev_get_stats` @ switch.c:438 — returns `dev + 0x4c8` (stats pointer); used as net_device->get_stats for sw* netdevs (vs eth*).

---

## Direct MMIO writes from switch.ko-local code

Despite [fn-01]'s claim that switch.ko owns "almost no direct MMIO",
the local code actually pokes the FPGA register space at three
addresses (all via plat-zxylzb's `fpga_write_reg` PLT):

| Reg | Writer | Value(s) | Meaning |
|---|---|---|---|
| `0xd3000` | sw_alarm_init ([fn-10]) | `0x1f40fa0` | initial CPU rate-limit (8000pps) |
| `0xd3000` | sw_alarm_scanforalarm ([fn-555]) | `0x1f40fa0` on link-down, `0x3f40050` on link-up | link-state-dependent rate-limit |
| `0xe20f6` | sw_set_idm_isolate ([fn-350]) | mask bits 0x40 (IDM0) / 0x80 (IDM1) | per-IDM isolation enable |
| `0xe8007` | sw_other_set_wan_lan_switch ([fn-563]) | `read & 0xc1ffffff` | WAN/LAN role-switch CSR |
| arbitrary | sw_reg_set_writereg ([fn-541]) | user-supplied | debug back-door |

`zx_stock_table.h` (the mainline replay) must include the
`0xd3000=0x1f40fa0` initial poke. Replay status of the link-up
`0x3f40050` write is uncertain — it only fires once a LAN port goes
up, so a static replay table will not include it; mainline likely
has to reproduce it from its own carrier-up handler. The `0xe20f6`
IDM-isolate and `0xe8007` WAN/LAN-switch writes are only triggered
by cspd IOCTLs at runtime, not at init — irrelevant to the boot replay.

---

## Function count summary

| Category | Count |
|---|---|
| Init walk (existing [fn-00..14] + 09a/09b) | 16 |
| Imported kernel symbols (PLT) | 42 |
| Imported tm.ko `zte_api_sw_*` (PLT) | 68 |
| Imported tm.ko `tm_*` (PLT) | 53 |
| Imported misc tm.ko/plat/cspd (PLT) | 25 |
| switch.ko-local netdev ops | 11 |
| switch.ko-local RX/TX hot path | 2 |
| switch.ko-local ACL / hardfast | 19 |
| switch.ko-local VLAN / bridge | 5 |
| switch.ko-local VLAN management | 23 |
| switch.ko-local FDB / MAC table | 28 |
| switch.ko-local multicast / IGMP / MLD | 19 |
| switch.ko-local QoS / scheduler | 20 |
| switch.ko-local per-port operations | 45 |
| switch.ko-local register / PHY raw | 4 |
| switch.ko-local alarm / LED | 7 |
| switch.ko-local WAN-LAN / MTU | 8 |
| switch.ko-local speed/duplex helpers | 5 |
| switch.ko-local NPU hardfast | 15 |
| switch.ko-local cleanup_module | 1 |
| switch.ko-local misc / data accessors | 7 |
| **TOTAL** | **423** |
