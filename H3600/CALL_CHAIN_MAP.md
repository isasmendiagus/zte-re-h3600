# Call Chain Map — Stock SDK ACL/CPU-Trap Path

Generado por `/tmp/build_chain_v2.py` desde decompiles Ghidra de tm.ko + switch.ko.

## Resumen ejecutivo

- **Total funciones decompiladas**: 9290 (across 5 modules)
- **Cadena para "agregar 1 rule ACL CPU-trap"**: ~50 funciones distintas
- **Tamaño ASM total cadena**: ~200KB
- **Estimación C portado**: 5000-10000 líneas

## Sub-sistemas (1821 funciones totales)

| Prefix | Count | Purpose |
|--------|-------|---------|
| **tm**   | 337 | Traffic Manager — SDK master |
| **sw**   | 167 | Switch — high-level API |
| **sbrg** | 156 | Sub-Bridge — switch HW driver |
| **pon**  | 121 | PON — fiber (skip for LAN-only) |
| **zte**  | 100 | API wrappers (mostly stubs) |
| **cla**  |  82 | **Classifier — ACL HW** ⭐ |
| **spa**  |  72 | Source Port Adapter |
| **sch**  |  70 | Scheduler — QoS |
| **sadm** |  61 | Subscriber ADMission |
| **idm**  |  55 | IDM DMA |
| **pp**   |  40 | Packet Processor (incl pp_pm_*) |
| **adm**  |  38 | Admission |
| **red**  |  33 | RED queue |
| **smac** |  23 | Switch MAC |
| **npu**  |  13 | NPU/FFE driver |
| **ethdrv** | 13 | Per-port netdev wrappers |

## Call chain TOP-DOWN: sw_set_default_mulrule → CLA HW write

```
sw_set_default_mulrule (switch.ko, 2299B)              ← user-callable
└── zte_api_sw_qos_add_port_streamselect (tm.ko, 5317B)  ← API entry
    ├── tm_acl_find_filter (2374B)
    │   └── tm_acl_check_matchfiled (1790B)
    ├── tm_add_acl_flow_rule (924B)                      ← dispatcher
    │   ├── addFlowOperInfo (10771B)                     ← SKIP: NAT/QoS marshal
    │   │   └── operInfoAdd (47117B) ⚠️                  ← SKIP: massive helper tree
    │   │       ├── opcDbCmdEntryValidSet (1448B)
    │   │       ├── opcDbFlowEntryValidSet (2717B)
    │   │       ├── opcDbNatEntryValidSet (1552B)
    │   │       ├── opcDbQosEntryValidSet (1567B)
    │   │       ├── opcDbVlanEntryValidSet (1559B)
    │   │       ├── operListInit (4377B)
    │   │       ├── pp_pm_set_flow_info (2745B)
    │   │       ├── pp_pm_set_next_hop_ram_info (2728B)
    │   │       ├── pp_pm_set_sub_ram_info (2537B)
    │   │       ├── pp_pm_set_external_flow_info (1675B)
    │   │       └── ... ~20 more sub-funcs
    │   └── addAclRule (6881B)                           ← FULL rule path
    │       ├── aclBuildExtRuleAndHashEntriesByParseCondition (29654B) ⚠️
    │       ├── aclBuildHashAndAclRule (28114B) ⚠️       ← SKIP: huge marshal
    │       │   ├── cla_set_hash_table (6872B)           ★ writes HW
    │       │   ├── cla_set_extra_rule_table (9863B)
    │       │   ├── cla_set_extra_index_table (2889B)
    │       │   ├── cla_set_external_hash_table (1087B)
    │       │   └── cla_get_hash_poly_config (1310B)
    │       └── cla_get_extra_rule_table (10336B)
    └── tm_acl_add_rule_node (2440B)                     ← linked list mgmt
```

## ⭐ Camino FAST (mucho menor): tm_acl_fast_add_v4v6

`tm_add_acl_flow_rule` puede tomar el FAST PATH si la rule es simple:

```
tm_acl_fast_add (38L)                                   ← dispatcher
└── tm_acl_fast_add_v4v6 (398L, 11302B)                 ← real worker
    ├── tm_acl_get_fastHashRule (7924B)                 ← data marshal
    ├── cla_get_hash_poly_config (1310B)                ← read CRC poly
    ├── aclGetExtIdxRuleRamAddrByPort (846B)            ← compute addr
    ├── cla_set_hash_table (6872B)                      ★ HW write
    │   ├── cla_set_indirect_rw_cmd (950B)              ← cmd reg
    │   ├── cla_set_indirect_rw_data (716B)             ← data reg
    │   └── cla_get_indirect_rw_status (651B)           ← poll ready
    ├── cla_set_external_hash_table (1087B)             ← optional
    ├── EN_V4FAST_EXTIDXTBL/EN_V6FAST_EXTIDXTBL (~665B each)
    └── cla_get/set_extra_index_table (~3500B each)

LEAF: tmOnuRegWrite/Read (728/516B) + fpga_write_reg/read_reg (~275B)
```

**Total ASM en fast path**: ~40KB → estimo **800-1200 líneas C portado** (vs 5000+ del full path).

## Sub-bloques HW que la SDK programa

Cada uno tiene su propia register table (decoded from `.data` of tm.ko):

| Sub-block | RegTable | Entries | Purpose |
|-----------|----------|---------|---------|
| **cla** | claRegTable | 83 | Classifier — **ACL hash tables** ⭐ |
| **spa** | spaRegTable | 134 | Source Port Adapter (CPU MAC, trap_en) |
| **sbrg** | sbragRegTable | 88 | Sub-Bridge (flood masks, isolate) |
| **pp_pm** | ppPmRegTable | 6 | PP Packet Manager (indirect access) |
| **sadm** | sadmRegTable | 21 | Subscriber ADMission |
| **smac** | smacRegTable | 64 | Switch MAC config |
| **sdetg** | sdetgRegTable | 18 | Subscriber Detection |
| **red** | RedRegTable | 13 | RED queue (drop) |
| **sopc** | sopcRegTable | 9 | One-shot pkt classifier (?) |
| **uopc** | UopcRegTable | 8 | Upstream operation |
| **sch** | SchRegTable | 19 | Scheduler |
| **dpa** | dpaRegTable | 25 | DPA (?) |
| **adm** | AdmRegTable | 22 | Admission |
| **qmg** | QmgRegTable | 12 | Queue Manager |
| **pm** | pmRegTable | 17 | Performance Monitor |
| **greg** | gregRegTable | 72 | Global Registers |
| **PonTm** | PonTmRegTable | 14 | PON TM specific |
| **PonPp** | PonPpRegTable | 21 | PON PP specific |

**~600 reg entries total**, cada uno con (offset, mask, shift, stride) decodificable.

## Lo que YA tengo decodificado y portado

| Funciones | Decompiled | En driver |
|-----------|------------|-----------|
| tmOnuRegWrite/Read | ✓ | tm_write/read (via base ioremap) |
| fpga_write/read_reg | ✓ | direct MMIO |
| ppPmRegTable | ✓ | constants in driver |
| spa CPU MAC programming | ✓ | zx_register_cpu_mac() |
| pp_pm indirect access | ✓ | zx_pp_pm_*() |
| brg_ram_get/set | ✓ | zx_brg_ram_*() |
| Most reg tables decoded | ✓ | header file with claRegTable + others |

## Lo que FALTA portear (orden de prioridad)

### Critical para CPU trap (~1000 líneas):
1. **`tm_acl_fast_add_v4v6`** (~398L decompile)
2. **`tm_acl_get_fastHashRule`** (~250L) — construye struct
3. **`cla_set_hash_table`** (~200L) — escribe HW
4. **`cla_set_indirect_rw_cmd/data/status`** (~50L cada uno)
5. **`cla_get_hash_poly_config`** (~50L) — lee CRC poly
6. **`aclGetExtIdxRuleRamAddrByPort`** (~50L)
7. **Macros EN_V4FAST_EXTIDXTBL** (~30L)
8. **High-level caller**: copy logic de `sw_set_default_mulrule` (89L) — solo lo que setea match=dst_mac+action=cpu_port

### Nice-to-have después:
- `sw_set_default_protocol_rule` (130L) para 802.1x/STP/BPDU rules
- `pp_pm_set_flow_info` para fast forwarding entries

## Estimación realista de esfuerzo

- **Fast-path port (suficiente para ping bidi)**: 800-1500 líneas C portado, **3-7 días** focused work
- **Full SDK port**: 5000+ líneas, **2-4 semanas**

## Strategy alternativa: SRAM snapshot+replay

En vez de portear las APIs, podemos:
1. Boot stock → ejecutar todas las init (`sw_init_switch` etc)
2. Dump CLA hash table SRAM via stock side (read all 1024 buckets × N slots usando `cla_get_indirect_rw_*`)
3. Save bytes
4. En nuestro driver: replay esas writes literalmente vía `cla_set_indirect_rw_*`

Ventaja: bypasea 95% del SDK porque copiamos el ESTADO FINAL en vez de re-ejecutar la lógica.

Funciona si las entries SRAM son self-contained (no dependen de runtime state). FDB hash entries probablemente sí.
