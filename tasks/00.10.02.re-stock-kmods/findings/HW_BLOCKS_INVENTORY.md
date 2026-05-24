# HW blocks inventory — ZX279128S ethernet/switch subsystem

Source: function-prefix scan of all decompiled stock .ko (`decomp_all_*.c`),
2026-05-24.

## Already wired in our mainline driver

| Block | Function | Where in our driver |
|---|---|---|
| **TM** (Traffic Manager) | BMU pool, TX/RX desc rings, IRQ at GIC 68 | zx279128-eth.c TM_REG_* macros |
| **PP** (Packet Processor) | L2 switch fabric, VLAN, port-isolate, CPU_FWD | zx_pp_brg_init + zx_port_isolate |
| **NPP** (Network PP) | PHY/MAC mgmt, per-MAC config | zx_smac_* + MAC[i] writes |
| **PON** | base/clock/reset init | zx_pon_clk_reset_init + pon_int_enable |

## **NOT** wired — discovered 2026-05-24, suspected cause of TX failure

| Block | # fns | Function | Relevance to TX bidi |
|---|---|---|---|
| **`sbrg`** (Switch Bridge) | 156 | `add_mactable`, `add_ipv4table`, `add_ipv6table`, `change_portmask`, `add_vltbl` — the **HW FDB** the switch actually consults for egress routing | 🔴 CRÍTICO — sin populate, switch flood→loopback |
| **`spa`** (Stripper/Pkt Action) | 74 | `cpu_untag_pri`, `cpu_untag_svid`, `enty_pktdeal_cfg`, `pon_other_pktdeal_cfg` — defines how CPU port processes pkts + VLAN tag handling | 🔴 ALTO — define qué es "el CPU port" |
| **`cla`** (Classifier) | 82 | `set_local_ipv4_addr`, `set_local_ipv6_addr`, `set_oth_l3_pkt_action_cfg`, `set_cpu_queue_id`, `set_dn_unknown_da_action_cfg`, `set_dn_l2/l3_default_flow_cfg` — L3 classifier + HW ARP/ICMP responder | 🔴 ALTO — stock auto-responde ARP/ICMP sin CPU |
| **`dpa`** (Data Path Accelerator) | 8 | `protocol_pkt_aly_en` (enable HW protocol analysis), `protocol_cpu_pps_en` (gate: ¿permite punt a CPU?) | 🔴 ALTO — el gate puede estar OFF |
| **`adm`** + **`sadm`** (Admin/policer) | 38 + 61 | Per-protocol pass/drop counters: `adm_get_*_pass/drop_protocal_packtcnt(proto)`. proto 0=ARP, proto 5=ICMP. Also brgun (bridge unicast/multicast) PPS gates | 🟡 MEDIO — pueden rate-limit a 0 |
| **`sdet`** (Stream Detector) | 26 | `minframe_length`, `maxframe_length`, `c_tpid`, `soam_drop_en` — validación de frame antes de admitir | 🟡 MEDIO — frames inválidos se dropean aquí |
| **`greg`** (Global Reg) | 41 | `port_closed`, `port_need_authen`, `oam_mode`, `lpi_*` — port state (open/closed/auth-required) | 🟡 MEDIO — CPU port podría estar "closed" |
| **`qmg`** (Queue Manager) | 13 | `ddr_cache_enable`, `up_ram_thd`, `dn_ram_thd`, `statistics` — DDR vs SRAM, thresholds | 🟡 MEDIO — si CPU queue starvada nada anda |
| **`red`** (RED queue mgmt) | 33 | `buffer_queue_cfg`, `cfg_enable`, `fec_enable` — Random Early Detection algorithm | 🟢 BAJO — sólo dropea cerca de buffer-full. Sustained traffic, no ping. |
| **`pm`** (G.988 Performance Mon) | 46 | OMCI G.988 stats | 🟢 N/A — PON only |
| **`uopc`/`sopc`** (Optical Path Ctrl) | 8/8 | PON physical layer | 🟢 N/A — PON only |
| **`smct`** (Switch Multicast) | 7 | `ppmove_pmau`, `pp_pmau`, `uni_pmau` — multicast port masks | 🟢 BAJO — no afecta unicast ping |
| **`usch`** (Upstream Sched) | 10 | per-queue weight/shaping | 🟢 BAJO — no afecta ping de baja tasa |
| **`sch`** (Scheduler) | 70 | per-queue scheduling, shapers (sharp = burst limiter), bucket caps | 🟢 BAJO — defaults probablemente ok |

## CPU queue: the most-likely "silent killer"

Found in the search:
```c
sw_port_set_cpu_queue_ratelimit     // PPS gate at the CPU queue
zte_api_pp_set_cpu_queue_rate       // same via zte API
cla_set_cpu_queue_id                // which queue ID is "the CPU queue"
dpa_set_protocol_cpu_pps_en(en)     // enable/disable per-protocol PPS gate to CPU
sadm_set_brgunsapt_pps_en           // bridge-unicast-unknown-DA PPS gate
```

If **ANY** of these have an effective value of 0 / disabled at boot in our
mainline (because we never set them), the path "TX-from-CPU → wire" or
"wire → RX-to-CPU" can be **completely silenced** without errors.

## SW layer we also missed: `idmfdb.ko`

Stock has its own `idm_fdb_*` family (82 fns) that **hooks the netdev TX
path** before HW receives the packet:

| Function | Purpose |
|---|---|
| `idm_fdb_init` / `_exit` | module init/exit |
| `idm_fdb_hook_xmit` | **TX hook** — SW-side port routing decision before pushing to HW |
| `idm_fdb_forward` | forward decision |
| `idm_fdb_recv_handle` | RX hook |
| `idm_fdb_idm_isolate_handle` | per-port isolation handling |
| `idm_fdb_multi_send_handle` | multicast TX |
| `idm_multicast_init` | multicast init |
| `idm_proc_*` | procfs exposes live state — `flood_status`, `forbidIdm`, `dbg` |

The `_hook_xmit` is the SW pre-step that probably decides which port to
TX on before our descriptor write hits HW. Stock relies on this layer for
routing decisions; we collapsed it into a single `zx_sw_xmit` that
hardcodes `port=0`.

## RED vs Queue management — corrección

Inicialmente etiqueté RED y qmg como "bajo". Más preciso:

- **RED**: probabilistic drop when buffer near-full. For PING (low rate),
  RED only fires if buffer is wedged. **TRULY low priority** for ping bidi.
- **Queue Manager (`qmg`) en sí**: scheduling, DDR vs SRAM. Defaults
  probably fine.
- **CPU queue rate limit** (`sw_port_set_cpu_queue_ratelimit`): **CAN
  completely silence CPU TX or RX** if defaulted to 0. **Re-classified
  as ALTO** if not properly initialized.

## What this means for the plan

We've been chasing a TX **descriptor format** problem. The real situation
is a **multi-layer HW config** problem:

1. **SW layer** (`idm_fdb_hook_xmit`): port-routing decision
2. **CPU queue** (`cla_set_cpu_queue_id` + `sw_port_set_cpu_queue_ratelimit`): does CPU TX/RX even reach the queue?
3. **HW classifier** (`cla` + `dpa`): does HW understand and route the packet?
4. **HW FDB** (`sbrg_*`): does the switch know where to send dst MAC?
5. **HW validation** (`sdet`): does the frame pass length/VLAN/CRC checks?
6. **Port state** (`greg_port_closed`): are CPU + LAN ports actually OPEN?

All of these need to be set up at probe-time. Currently we set up only #6 (implicitly) and partial #4 (SW FDB only, no HW FDB).

## Physical memory map — what stock maps vs us

Stock has **9 separate ioremap'd MMIO regions** split across multiple DT
nodes. Our mainline collapses to **1 region** (`eth@921c0000` size 2 MiB).

### Stock PON DT node (5 sub-regions)

```c
pon_base       = of_iomap(pon_node, 0);   // 14 refs  — main PON
top_crm_base   = of_iomap(pon_node, 1);   // 18 refs  — Top Clock/Reset Mgr (= our topcrm syscon @ 0x94000000)
sys_ctrl_base  = of_iomap(pon_node, 2);   //  4 refs  — System Control (NEW — we don't have)
pin_mux_base   = of_iomap(pon_node, 3);   //  0 refs  — Pin Mux (NEW — declared but unused in .ko)
pon_serdes_base= of_iomap(pon_node, 4);   // 133 refs — PON SerDes (PON-only, GPON optical PHY)
```

### Stock separate DT nodes (1 region each)

```c
npp_base = of_iomap(npp_node, 0);  // 92 refs — Network PP
pp_base  = of_iomap(pp_node, 0);   // 91 refs — Packet Processor (switch)
tm_base  = of_iomap(tm_node, 0);   // 124 refs — Traffic Manager
idm_base = of_iomap(idm_node, 0);  // ? refs   — IDM (used by idmfdb.ko)
```

### Mainline coverage

Our mainline maps **eth@921c0000** size 0x200000 (2 MiB) covering physical
0x921c0000..0x923c0000. Stock's reg accesses (via `fpga_*_reg` indirect):

| Range (stock dword index) | Translates to (byte offset from stock base 0xf4000000) | Status |
|---|---|---|
| `0x10006..0x36000` (6 calls) | `0x40018..0xd8000` | **BEFORE our window** — SerDes/PRBS test, PON physical (PON-only, irrelevant for LAN) |
| `0x70000..0xe813b` (191 calls) | `0x1c0000..0x3a04ec` | **IN our window** — npp/tm/pp/idm registers ✓ |

So our 2 MiB window IS sufficient size for ethernet — we just don't have
direct access to `sys_ctrl_base` and `pin_mux_base` regions.

### `data_base` (false positive)
Initially looked like an MMIO base but is just a strtoul radix variable in a
parsing helper. Not hardware.

## IRQs — stock registers 5 distinct lines

```c
g_pon_irq → zx_pon_int        (PON top-level)
g_npp_irq → pon_npp_int       (NPP)
g_pp_irq  → zx_pon_pp_int     (PP switch)
g_tm_irq  → zx_pon_tm_int     (TM — this is THE one we have, GIC 68)
g_idm_irq → idm_net_int       (IDM — separate from TM!)
zx_phy_int → request_threaded_irq(...)  per-PHY interrupts (4×)
```

**Our mainline registers only 1 IRQ: the TM at GIC 68.** We do NOT handle:
- PON IRQ (PON state changes)
- NPP IRQ (PHY/MAC events)
- PP IRQ (switch events: FDB miss, port state change, etc — could matter for FDB learning!)
- IDM IRQ (separate path for IDM packets)
- PHY IRQs (link state change — we poll instead)

The **PP IRQ** is the most suspicious miss for our ping bidi. The switch
may signal "FDB miss / new MAC seen" via IRQ that we never service, so
the switch never learns and keeps flooding.

DTSI exposes GIC SPIs: 0x0b, 0x26, 0x2c, 0x32, 0x3f, 0x4e (= 11, 38, 44, 50, 63, 78).
But only ONE is wired to eth (need to check which).

## What we still haven't decompiled

Other stock .ko in `ext/kmodules_dump/` not yet decompiled:
- `dsp_dev.ko` (160KB) — DSP, voice
- `tdm.ko` (35KB) — PCM/TDM
- `voip_codec.ko` (215KB) — VoIP
- `usrline.ko` (184KB) — POTS/userline
- `shellproc.ko` (32KB) — stock shell processor (procfs/debug — may
  expose useful HW state queries we could use)
- `rtkatm.ko` (16KB) — Realtek ATM (?)
- `kudp.ko` (16KB) — kernel UDP
- `patch.ko` (5KB) — generic patcher

The voice-related ones (dsp/tdm/voip/usrline) are POTS-only, not relevant
to ethernet. `shellproc.ko` might be worth a quick scan — if it exposes
"dump all HW state" via procfs, we could call it on live stock to capture
register snapshots.

## Where the rest of the puzzle lives: cspd userland

None of `cla_set_local_ipv4_addr` or `sbrg_add_mactable` etc. are called
from within the .ko files. They're EXPORTED functions called by userland
— specifically by `cspd` (the ZTE management daemon).

Next step (Phase 5a): scan `cspd` binary for `cla_set_*`, `sbrg_*`,
`dpa_set_*`, `spa_set_*`, `sw_port_set_cpu_queue_ratelimit` to find the
ioctl/syscall sequence + args stock uses at boot.
