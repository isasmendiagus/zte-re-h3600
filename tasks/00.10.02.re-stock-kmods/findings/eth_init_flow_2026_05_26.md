# Stock eth init flow — full call graph captured live

**Source**: live execution on stockport (vanilla 4.1.25 + zte_shim + the
6 stock .ko files), captured via SHIM_TRACE (16,340 events) + kotrace
(214 in-place function patches) on 2026-05-26.

**Use this doc to**:
- Understand what stock does at boot, in order, with what args
- Map each step to the mainline driver refactor (task #38)
- Reference table of which ZTE-added kernel symbols matter for what

## Module load order (matches stock /etc/init.norm)

```
1. memlog.ko        — captures printk into /proc/memlog
2. regtracer.ko     — poll-based MMIO reg diff tracer
3. zte_shim.ko      — OUR shim providing ZTE kernel-resident symbols
4. zx_ponreg.ko     — provides fpga_read_reg, fpga_write_reg (BMU/PON regs)
5. plat-zxylzb_9128S.ko  — pon/npp/tm/pp/idm init + gephy MDIO + SMACs
6. tm.ko            — traffic-manager + ACL RAM + SDK init
7. switch.ko        — alloc_etherdev + register_netdev + capfun registers
8. idmfdb.ko        — CPU-port FDB + netdev notifier
```

Each module's `init_module` returns BEFORE the next module loads. So
init order is strict and observable.

## Detailed init per module

### plat-zxylzb_9128S init_module → zx_pon_init (offset 0x1d9a8)

```
zx_pon_init:
  reserve_mem_info()
  zte_get_pon_mode()                       ← returns 0x10 (LAN-only)
  bp_max_number setup (BPPE pool sizes)
  printk "lan_up=1, lan_up_port=4"
  of_find_matching_node_and_match("zte,zx279128s-pon")
    for each matching node:
      pon_base       = of_iomap(node, 0)   ← 0x92000000, 4 MiB
      top_crm_base   = of_iomap(node, 1)   ← 0x94000000
      sys_ctrl_base  = of_iomap(node, 2)
      pin_mux_base   = of_iomap(node, 3)
      pon_serdes_base= of_iomap(node, 4)
      g_pon_irq      = irq_of_parse_and_map(node, 0)
      printk("g_pon_irq=%d,%x,%x,%x,%x,%x")
    "zte,zx279128s-gephy" node →
      for i in 0..3: g_phy_irq[i] = irq_of_parse_and_map(gephy, i)
  pon_reset(-1) + msleep(10)
  register_pon_int()
  *(pon_base + 0x40044) = 0xffffff7f       ← interrupt mask
  *(pon_base + 0x4001c) = 0xf
  msleep(1)
  tm_pon_tm_init()     → "pon tm init"
                          netif_napi_add(pon_dev, weight=512)
                          DMA_DN_DESC_CNT readback
                          "pon_tm net init ok,216/176"
  netdebug_module_init()
  tm_pon_pp_init()     → "pon_pp init"
  tm_pon_npp_init()    → "pon_npp init"
                          pon_npp_smac_init() → smac_init(0..3) [4 SMACs]
                            for each smac: writes npp_base + N*0x40000 + 0..0xd30
                          gephy_ldo_init() at the START (writes via MDIO)
                          phy_process(0)
                          init_timer + add_timer(gephy_ldo_timer)
                          register_phy_int()
  if lan_up: zx_pon_clk_reset()
```

Key data after this:
- IRQs allocated: PON=20, NPP=21, IDM=22, TM=23, PP=24
- BPPE pool init: NORMAL_BP=0x90000, JUMBO_BP=2800, BPPE_POOL=256
- BP_BUFFER_SIZE = 0xe0000

### tm init_module (offset 0x1a000ish)

```
tm_devReg()            → registers tm-related char devs / sysfs nodes
tmUsrInterfaceCreate() → "= TM Module SYS FS Init ended successfully ="
printk "tm_initModule begin..."
aclTestInit() → tm_sdk_init() → 
  aclRamInit():
    memzero(0xf1020000, 4 MiB)             ← ACL RAM bank 1 (ZX_ACL_BASE)
    memzero(0xf1420000, 1 MiB)             ← ACL RAM bank 2 (ZX_FLOW_BASE)
    for each ACL idx 0..N:
      cla_set_extra_index_table(idx, ...)
      cla_get_indirect_rw_status() [waits for HW ready]
tm_initial()
api_lock_init()
printk "tm_initModule end..."
```

ACL RAM is the **runtime-computed iotable entry** at virt 0xf1000000 →
phys 0x4c000000 (= pdt_mem_size + 0x40000000 - ZX_RESERVE_MEM_SIZE << 20
on 256 MiB / 64 MiB-reserve unit).

### switch init_module

```
init_module:
  printk "Init switch module"
  read g_sw_cap fields:
    sw_uni_count, sw_uni_mask, sw_wan_port, sw_wan_mask,
    sw_all_port_count, sw_all_port_mask, gwtype, wantype, onutype
  print "ptSwInfo->wan_logicport=0"
  g_mii_dev_name[0] = "sw"
  g_mii_dev_name[1] = "pon"
  sw_set_uni_as_wan(uni=0)
  printk "PON_PP_TM_CFG=0x21200000" + "after = 0x23200000"
  chip_tm_init() → "-------chip_tm_init end-----"
    tm_pon_protocol_pktdeal_set × N (some return errors, non-fatal)
    dpa_set_protocol_type_i_act × N
  sw_reg_set_onu_swcap() →
    CspGetPortInfo(&out)                   ← reads board_info[+0x68]
    CspGetSwInfo(&out)                     ← reads board_info[+0x80]
    if (sw_info.num_ports <= 8 && port_info.port_count <= 8):
      [loop body that creates netdevs — entered when num_ports > 0]
  sw_init_switch:
    "l2_fast init"
    sw_set_default_ipv4_mulrule (ACL malloc fail observed — sw_acl
        allocator not initialized; non-fatal: rule registration skipped)
    sw_set_default_protocol_rule (same)
    "set cpu queue rate limit to 8000pps"
    Capacity=256000 twice
    "reg hff"
    register npu driver 12
    pdt_ethdriver_init →
      set_mii_dev_name_type_part_0(0, &"sw")
      set_mii_dev_name_type_part_0(1, &"pon")
      if (_tm_port_unknwn_multicast_floodport_set != 0):  ← skipped
        loop: dev_get_by_name + alloc_etherdev_mqs + register
      alloc_etherdev_mqs(priv_size=100, tx=1, rx=1)
      [bunch of writes to dev struct — including netdev_ops @ +0x12c]
      register_netdev(dev) → kernel registers "eth0"
      netif_carrier_off(dev)
  register_bridge_notifier()
  public_capfun_register × 7:
    sw_public_port_cfg_func_reg(p)
    sw_public_port_vlan_func_reg(p)
    sw_public_port_ratelimit_func_reg(p)
    sw_public_onu_other_func_reg(p)
    sw_public_onu_qos_func_reg(p)
    sw_public_onu_mactable_func_reg(p)
    sw_public_onu_statistics_func_reg(p)
  private_capfun_register × 10:
    fuc_table_node_create × 10
  "Init personal switch module Success"
```

### idmfdb init_module

```
init_module:
  register_netdevice_notifier(idm_netdev_event)
  idm_netdev_event fires for each existing netdev:
    iVar1 = IfName2WlanIdmMap(ifname)  ← returns NULL (no wlan map yet)
    if iVar1 != 0: idm_fdb_idm_isolate_handle()
```

## Steady state: running timers post-init

| Timer / source | Period | What it does |
|----------------|--------|--------------|
| `extphy_timer_func` | ~20 ms | MDIO read/write port 10 reg 30, reg 26 (vendor regs) |
| `gephy_ldo_timer_func` | ~50 ms | MDIO ports 10/11/12 regs 0/5/10 + temp_ctrl_read |
| `phy_process` | on PHY IRQ | MDIO + switch_phy_int_check.part.5 |
| ARP/IPv6 dad | sporadic | dev_change_flags → notifier → idm_netdev_event |

## ZTE kernel-resident symbols catalog

These are the ~50 symbols ZTE added INTO their kernel (not as .ko's).
Our `zte_shim.ko` provides stub implementations.

### Csp* family — "Customer Service Platform" board info accessors

| Symbol | Signature (corrected) | Role |
|--------|----------------------|------|
| `CspGetBoardDesInfo` | `int (void **out)` writes &board[+0x20] | Returns board descriptor sub-ptr |
| `CspGetPortInfo` | `int (void **out)` writes &board[+0x68] | Per-port info |
| `CspGetSwInfo` | `int (void **out)` writes &board[+0x80] | Switch info — has num_ports@+8 (u32, ≤8 OK) |
| `CspGetSlicInfo` | `int (void **out)` writes &board[+0xec] | SLIC/codec info |

**Layout discovered**: a single `board_info` struct of ~~0xec+? bytes~~
where each Csp* function returns a sub-pointer at a fixed offset.

Critical fields the stock callers actually read:
- `board[0x88]` (u32) = `sw_info.num_ports` — switch.ko gates netdev
  loop on this. **Must be 1-8** for netdev creation.
- `board[0x6a]` (u16) = `port_info.port_count` — same range check.

### CSPKernel_* family — kernel-side QoS classifier

| Symbol | Note |
|--------|------|
| `CSPKernel_QC_*` | Software classifier matcher (DSCP, VLAN, MAC, IP, etc.) — full set in stock vmlinux text |
| `CSPKernel_QoS_*` | QoS policer/queue management |
| `CSPKernel_skb_*` | SKB classification + remarking |

These are CALLED by .ko's but ZTE put the implementation in vmlinux.
Our shim stubs `return 0` — disables QoS classification at this layer,
network still works for plain L2/L3 traffic.

### FFE — Fast Forwarding Engine

| Symbol | Note |
|--------|------|
| `ffe_learn_skb` | Add flow to FFE cache (HW offload of subsequent packets) |
| `ffe_receive_skb` | FFE-accelerated RX |
| `ffe_get_npu_enable` | Read FFE enable global |

Our stubs return 0 — disables FFE acceleration. Traffic goes through
full Linux netif stack (slower but correct).

### Misc

| Symbol | Note |
|--------|------|
| `g_sw_cap` | 92-byte BSS struct of function ptrs. Stub: 256-byte naked fn of `bx lr`. switch.ko reads fields via offset; values it sees from our stub happen to give a sane default (num_ports=0, num_uni=0, etc.) |
| `g_switch_debug_level` | u32 in stock (T section), value=1. Stub: naked fn (same reason as g_sw_cap — callers do `bl <sym>+<offset>` style indirection) |
| `WlanIndex2WlanIdmMap` | Stock: `void *(int wlan_idx)` returning a struct ptr. Stub: returns NULL (= "not mapped") |
| `IfName2WlanIdmMap` | Same signature, same stub |
| `pdt_mem_size` | unsigned long, value = total RAM (256 MiB on our unit) |
| `ZX_RESERVE_MEM_SIZE` | unsigned int, value = top-of-RAM reserve in MiB (64 on our unit) |
| `product_vid` | unsigned int = 0x32 for H3600 |
| `__alloc_skbuff` | Custom BMU-pool allocator. Stub: NULL → plat takes error path |
| `dma_cache_maint` | Old DMA API. Stub: wmb() |
| `temp_ctrl_read` | SoC die-temp reader. Stub: returns 45 (°C) |
| `zte_get_pon_mode` | Returns operating mode. Stub: 0x10 = LAN-only |
| `zx_mdio_read/write` | PHY MDIO accessors. Stub: read = 0xffff (fake), write = no-op |
| `Kernel_ASEND` | Inter-module message-passing. Stub: 0 |
| `LedActionSet` | LED GPIO control. Stub: 0 |
| `hw_watchdog_reset` | Watchdog pet. Stub: no-op |
| `br_lookup_mfd` | Multicast forward DB lookup. Stub: NULL |
| `register_bridge_notifier` | Bridge events. Stub: 0 |
| `npu_register_driver` | NPU driver registry. Stub: 0 |
| `sw_public_*_func_reg` × 7 | Stock would register callbacks for port/vlan/qos/etc. We ignore `p`. |
| `fuc_table_node_*` | Function table node mgmt. Stub: 0 |

## Critical register-write sequences

### chip_tm_init register sequence

Captured via kotrace (task #19) — the 22363-entry stock dump's first
~hundred relevant writes. Specifies HW TM block init (queues, schedules,
ports). Full table in `tasks/00.01.eth-driver/findings/` from earlier
RE work.

### FDB write — D2 → D1 → D0 (critical for 0 DUPs)

```
writel(D2, FDB_RAM_ADDR + 8);   /* hi half first */
writel(D1, FDB_RAM_ADDR + 4);
writel(D0, FDB_RAM_ADDR + 0);   /* lo half last — triggers HW commit */
```

Reverse order would leave HW in inconsistent state → mid-fetch reads
miss → switch floods → DUPs storm. Discovered task #50 ping-bidi work.

### gephy_ldo_init MDIO sequence (per PHY)

```
for each phy_port in {gephy0..3, internal}:
    zx_mdio_write(phy_port, 0x17, 0x2448)
    read _DAT_f0807000..0xc..0x10    # local gephy ctrl regs
    zx_mdio_write(phy_port, 0x10, 0xb640)
    if (link bits set):
        zx_mdio_write(phy_port, 0x11, 0x1f)
        g_geLdoFlag[phy_port] = 1
    else:
        zx_mdio_write(phy_port, 0x11, 0x1f)
        g_geLdoFlag[phy_port] = 0
```

## Notable findings affecting struct layout

### struct net_device — netdev_ops offset shift

Stock kernel: `netdev_ops` at `dev + 0x12c`.
Our vanilla 4.1.25: `dev + 0x124`.
**Diff: 8 bytes** = some downstream-patched field exists in stock at
the front of struct net_device that isn't in vanilla.

The switch.ko `pdt_ethdriver_init` writes `dev->netdev_ops` at offset
0x12c. We binary-patched the .ko (task #59) to use 0x124 — 1 byte change
at file offset 0x5c8.

If you do another offset RE for other dev fields, expect a similar
+8 shift in the 0x100+ range. Diff likely from one of:
- New field for QoS/FFE state
- New field for tracking
- 64-bit-aligned padding from a downstream feature

`netdev_probe.ko` (`tasks/99.01.linux-stockport/netdev_probe/`) prints
the offsets and is useful for diff-ing.

## Cross-references

- **Consumer**: [00.01 eth-driver](../../00.01.eth-driver/) — uses this
  for the mainline refactor (task #38).
- **Discovered in**: [99.01 linux-stockport](../../99.01.linux-stockport/findings/stockport_revival_2026_05_26.md)
  during the 14-wall journey.
- **Static decompilation**: this dir's `decomp_all_*.c` files have the
  full Ghidra decompilation of every stock .ko function. Cross-check
  any of the above against the C code.
- **Static MMIO map**: `HW_BLOCKS_INVENTORY.md`.
- **Signatures DB**: `ARG_SIGNATURES.json` — 2157 stock functions with
  inferred argument signatures.
