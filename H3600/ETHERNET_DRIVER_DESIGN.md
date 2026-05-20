# Driver Ethernet ZX279128S (H3600) — Design Document

Documento de diseño para implementar driver mainline del ethernet del H3600.
Compilado de RE de `switch.ko` + `plat-zxylzb_9128S.ko` + `idmfdb.ko` + `tm.ko`
(stock kmodules) **CON validación contra estado vivo de stock vía SSH/devmem**.

## 🚨 PIVOT ARQUITECTÓNICO (2026-05-19) — IDM NO ES PARA LAN

Hasta la corrida del 19-may, asumimos que **IDM** (Integrated DMA Manager, `idm0`/`idm1`)
era el path CPU↔ethernet. Resultó FALSO. Inspección del stock vivo reveló:

```
/proc/idm_fdb/idm_map   ← idm0/idm1 son para WiFi (idmfdb mapea a wlanN)
0: idm:0 ssid:0 dev:apcli0
8: idm:1 ssid:0 dev:wlan0
...

/proc/interrupts
 28: 0 GIC 70 idm        ← IDM IRQ NUNCA dispara en operación normal
 29: 1278 GIC 68 pon_tm  ← TM IRQ tiene TODOS los counts
```

**`/proc/net/dev` con tráfico activo**:
- `eth1: 1318 RX, 1262 TX` — toda la traffic CPU↔LAN va por `eth1`
- `idm0/idm1: 0 RX, 0 TX` — IDM netdevs no se usan para ethernet

**El path REAL es**:
```
RJ45 → GePHY → MAC[i] → SW → PP → TM (BMU+DMA) → DDR → CPU
                                  ↑
                          THIS IS WHAT WE NEED
```

**Por lo tanto, nuestro driver actual** (`zx279128-eth.c`) que registra `idm0`/`idm1`
y usa el path IDM **NO va a ver tráfico LAN nunca**. Hay que portear el subsistema
TM (`pon_tm_*` functions) que es un driver de red completo paralelo dentro del mismo
plat-zxylzb_9128S.ko.

### Stock netdevs (de `ip addr` corriendo en el modem):
```
 6: sw       00:d0:d0:81:82:83  ← pon_tm_netdev[0] = CPU↔switch  ⭐ KEY
 7: pon      00:d0:d0:81:82:83  ← pon_tm_netdev[1] = CPU↔fiber (no usamos)
 8: idm1     00:d0:d0:61:62:01  ← WiFi 5GHz
 9: idm0     00:d0:d0:61:62:00  ← WiFi 2.4GHz
10: eth0..4  f4:f6:47:0f:42:64  ← wrappers per-port (pdt_ethdriver_init)
27: br0      f4:f6:47:0f:42:64  ← bridge: eth1+eth2+eth3+eth4+nbif0+wlan0+wlan5g0
```

`br0` (192.168.1.1) contiene `eth1..4` que son virtual wrappers. El frame real
sube/baja por `sw` (= pon_tm_netdev[0]).

## ⚠ Nuestra placa NO tiene fibra (solo Ethernet)

Block diagram oficial del ZX279128S muestra:
```
PON_TOP:
├── ponserdes + GPON/EPON/P2P MAC   ← FIBRA — IGNORAR
├── PP (Packet Processor)            ← USAR (puente CPU↔MACs)
└── SW (Switch hardware):
    ├── MAC0 ─ GMII/MII ─ GePHY ─ RJ45 #1   ← USAR
    ├── MAC1 ─ MII      ─ GePHY ─ RJ45 #2   ← USAR
    ├── MAC2 ─ MII      ─ GePHY ─ RJ45 #3   ← USAR
    ├── MAC3 ─ MII      ─ GePHY ─ RJ45 #4   ← USAR
    └── MAC4 ─ RGMII    ─ external          ← Wifi/extra
```

**Stock IDM aparece como `idm0`/`idm1`** — no es 1 netdev por puerto, es 2 aggregates
(probablemente downstream LAN aggregate + upstream WAN aggregate). El PP/SW maneja
forwarding entre puertos físicos en hardware.

Para el caso NO-PON, podemos:
- Saltear init de PON serdes/GPON MAC
- PERO mantener clocks PON (vía topcrm/lspXcrpm) — algunos clocks compartidos
- PP es necesario para que tráfico vaya CPU↔MACs (registración para CPU port)
- Switch básico funciona en HW sin nuestro driver tocar TM/forwarding rules

## Arquitectura del SoC

El ZX279128S es un **chip de ONU** (Optical Network Unit). NO es un router típico
con un MAC genérico — tiene un **packet processor custom** entre la fibra (PON)
y los puertos Ethernet:

```
   Fibra (PON @ 0x92000000)
              ↓
        NPP (@0x921c0000)        ← Network Packet Processor (IRQ aquí)
        ├── IDM (@0x921c8000)    ← Integrated DMA / MAC ports
        ├── PP  (@0x92380000)    ← Packet Processor (forwarding)
        └── TM  (@0x92340000)    ← Traffic Manager (QoS)
              ↓
   Gigabit PHYs (@0x9b000000) — hasta 4 PHYs
   MDIO bus     (@0x9a101000)
```

## Bases ioremap'd (extraídas del init_module de plat-zxylzb_9128S.ko)

| DT compatible | base addr (phys) | múltiples regiones |
|---|---|---|
| `zte,zx279128s-pon` | `0x92000000` | + top_crm, sys_ctrl, pin_mux, pon_serdes (5 mappings!) |
| `zte,zx279128s-npp` | `0x921c0000` | 1 mapping |
| `zte,zx279128s-tm` | `0x92340000` | 1 mapping |
| `zte,zx279128s-pp` | `0x92380000` | 1 mapping |
| `zte,zx279128s-idm` | `0x921c8000` | 1 mapping |
| `zte,zx279128s-gephy` | `0x9b000000` | 4 IRQs (uno por PHY) |
| `zte,zx279128s-mdio` | `0x9a101000` | MDIO bus |

## Flow de inicialización (orden importante)

```c
init_module():                          // plat-zxylzb_9128S.ko
  reserve_mem_info()                   // BMU buffer pool memory
  g_pon_work_mode = zte_get_pon_mode() // 0x10 = LAN-only, 1 = HGU/router
  
  // For each DT node (PON, GEPHY, NPP, TM, PP, IDM):
  of_iomap()                           // map their MMIO regions
  irq_of_parse_and_map()               // get their IRQs
  
  // After all bases mapped:
  pon_reset(0xffffffff)                // reset PON block
  msleep(10)
  *(pon_base + 0x40018) = 2            // PON setup
  zx_pon_clk_reset_init(1)             // Clocks via TOPCRM/LSP
  register_pon_int()                   // IRQ handler
  *(pon_base + 0x40044) = 0xffffff7f
  *(pon_base + 0x4001c) = 0xf
  msleep(1)
  
  tm_pon_tm_init()                     // Traffic Manager init
  netdebug_module_init()               // /proc debug iface
  tm_pon_pp_init()                     // Packet Processor
  tm_pon_npp_init()                    // NPP — IRQ thread, IDM init, etc
  
  if (lan_up != 0):
    *(pp_base + 0x2c) |= (1 << (lan_up_port + 0x19))
    zx_pon_clk_reset()
```

## NPP register map (npp_base = 0x921c0000)

Encontrado vía RE de `tm_pon_npp_init`, `idm_net_int`, `idm_net_poll`:

| offset | función | inicialización |
|---|---|---|
| `+0x04` | mask global | `0xffffffff` |
| `+0x08` | IRQ enable mask | `0xffffff` |
| `+0x0c` | IRQ mask | `0xfffff` |
| `+0x40` | NPP control | OR `0x300` |
| `+0x48` | reset/zero | `0` |
| `+0x8020` | IDM IRQ status | (R) |
| `+0x8024` | IDM IRQ mask | `idm_int_mask` (default) |
| `+0x8044` | TX status | |
| `+0x804c` | RX queue length | (R) low 16 bits |
| `+0x10008` | initial value | `0x80` |

## TM init (tm_pon_npp_init llama en orden):
1. `pon_npp_idm_init()`   — IDM (puertos Ethernet) ← **decompilado abajo**
2. `pon_npp_spa_init()`   — ? (TODO)
3. `pon_npp_sipc_init()`  — ? (TODO)
4. `pon_npp_smct_init()`  — ? (TODO)
5. `pon_npp_smac_init()`  — MAC config (TODO)
6. `pon_npp_uopc_init()`  — ? (TODO)

## pon_npp_idm_init (CORAZÓN — 1040 bytes decompilados)

```c
pon_npp_idm_init():
    // Dos puertos Ethernet
    idm_netdev[1] = idm_net_register(1, "idm1")
    idm_netdev[0] = idm_net_register(0, "idm0")
    netif_napi_add(idm_netdev[0], napi_struct, idm_net_poll, 0xff)  // weight 255

    // Configurar NPP/IDM
    npp_base[0x8024] = 0x1f         // IDM IRQ enable (5 bits)
    npp_base[0x8018] = 0x40         // (TODO: meaning)
    npp_base[0x801c] = 5000         // some count/timeout
    npp_base[0x8010] = 0x40
    npp_base[0x8000] |= 0xf0000     // enable
    npp_base[0x8000] = (... & 0xf00fffff) | 0x2000000

    pp_base[0x38] = 0x00000640      // PP setting (BPM?)

    // DMA descriptors — 0xd0 bytes config + 0x6000 ring
    idm_desc_addr = dma_alloc_coherent(0, 0x6020, &dma_handle, GFP_DMA)
    BUG_ON(idm_desc_addr & 0x1f)    // 32-byte aligned

    npp_base[0x80c0] = 0
    npp_base[0x8008] = dma_handle          // ← TX descriptor base
    npp_base[0x8004] = dma_handle + 0x4000 // ← RX/TX split

    rx_desc = idm_desc_addr - 0x80000000   // virt = phys - PAGE_OFFSET
    memset(rx_desc, 0, 0x6000)
    tx_desc = rx_desc + 0x1000              // RX 0x1000 entries x 4B = 4096B
                                            // TX 0x800 entries x 4B = 2048B

    // RX ring fill: cada slot tiene SKB pre-allocated
    for i in 0..RX_RING:
        skb = alloc_skb(0x6c4, GFP_ATOMIC)
        skb_reserve(skb, 0x20)              // 32 byte headroom (DMA align?)
        rx_desc[i*2] = skb_data_phys        // descriptor entry: data ptr
        skb_rq[i] = skb                     // shadow ring of SKB pointers
        skb->offset_bc |= 0x10              // mark as RX
        npp_base[0x8048] = 0x10000          // RX kick (per-slot?)

    idm_rx_index = 0
    idm_tx_index = 0
    idm_tx_done = 0
    npp_base[0x800c] = 0x4000800            // RX enable/config

    // TX SKB pool — 0x200 SKBs preallocated for fast TX
    for i in 0..0x200:
        skb = alloc_skb(0x6c4, GFP_ATOMIC)
        skb_reserve(skb, 0x20)
        idm_skb_stack_push(skb, 0)

    hwnat_set_hook_ptr()
    add_timer(idm_timer, jiffies+100, idm_timer_func)  // periodic check

    request_threaded_irq(g_idm_irq, idm_net_int, ...)
```

### Descriptor format — DECODIFICADO desde idm_net_poll

```c
struct idm_rx_desc {
    u32 dma_addr;      // [0:4] data physical address (virt + 0x80000020)
    u16 len_status;    // [4:6] low 14 bits = packet length (max 16KB)
                       //       upper 2 bits = unknown
    u8  csum_flag;     // [6]   bit 3 set → ip_summed valid; bits[0:2] = hash
    u8  port_flag;     // [7]   bit 7 = port (0=idm0, 1=idm1)
};
```

**RX ring**: 2048 entries × 8B = 16 KB (`idm_desc_addr + 0..0x4000`). Index wraps at `0x7ff` (`if (0x7ff < uVar10) idm_rx_index = 0`).

**TX ring**: 256 entries × 8B = 2KB en `idm_desc_addr + 0x4000` (TBD: re-confirm from idm_net_tx).

**SKB shadow**: `skb_rq[idx]` paralelo al ring, guarda puntero al SKB asociado a cada slot (8 bytes alineado: `skb_rq[(desc_offset)>>3]`).

**SKB pool**: 0x200 SKBs pre-alloc'd vía `_idm_skb_stack_pop(0)`. Si vacío → `__alloc_skbuff(0x6c4, 0x20, 0, 0xffffffff)` (1732B, 32B headroom).

### RX kick / ACK (post-poll)

Después de procesar N paquetes en una vuelta:
```c
*(npp_base + 0x8048) = (N << 16) | N;   // bits[31:16]=count_ack, bits[15:0]=refill
```
Este write libera los slots procesados y le dice al HW cuántos refill SKBs hay disponibles.

### NAPI poll skeleton (extraído del stock)

```c
int idm_poll(struct napi_struct *napi, int budget) {
    int done = 0;
    int rounds = 5;                              // max 5 mini-batches por call
    do {
        int n = npp_read(0x804c) & 0xffff;       // queue len pending
        if (n == 0) break;
        if (n > budget) n = budget;
        for (i = 0; i < n; i++) {
            struct idm_rx_desc *d = &rx_desc[idm_rx_index];
            struct sk_buff *skb = skb_rq[idm_rx_index];
            idm_rx_index = (idm_rx_index + 1) & 0x7ff;
            
            // Refill: pop pool or alloc new SKB
            struct sk_buff *new_skb = _idm_skb_stack_pop(0);
            if (!new_skb)
                new_skb = __alloc_skbuff(0x6c4, 0x20, 0, -1);
            d->dma_addr = virt_to_phys(new_skb->data);
            skb_rq[idm_rx_index] = new_skb;
            new_skb->offset_bc |= 0x10;          // mark RX
            
            // Process received
            int len = d->len_status & 0x3fff;
            int port = (d->port_flag >> 7) & 1;
            skb_put(skb, len);
            skb->dev = idm_netdev[port];
            skb->ip_summed = (d->csum_flag & 8) ? (d->csum_flag & 7) : 0xff;
            skb->protocol = eth_type_trans(skb, idm_netdev[port]);
            netif_receive_skb(skb);
            done++;
        }
        npp_write(0x8048, (n << 16) | n);        // ack + refill
        budget -= n;
    } while (--rounds > 0 && budget > 0);
    
    if (budget > 0) {                            // no more pending
        napi_complete_done(napi, done);
        npp_write(0x8024, idm_int_mask & ~0x14); // re-enable RX IRQ bits 2,4
    }
    return done;
}
```

### IDM IRQ status bits (param_1 + -0x60 referenced in idm_net_poll)

- `bit 4 (0x10)` → TX done — call `idm_check_tx_done_lock()` (cleanup completed TXs)
- `bit 2 (0x04)` → algún counter/error (TBD)
- `bit 0/1`     → RX done (probable, masked como `0x14` cuando re-arm)

## pon_npp_smac_init (Switch MAC init — los 4 puertos LAN)

```c
pon_npp_smac_init():
    gephy_ldo_init()                          // Power ON GePHY LDOs

    for i in 0..4:
        zx_mdio_write(uni_phy[i], 0x10, 0x8001)   // PHY config bit
        zx_mdio_write(uni_phy[i], 0x11, 0)
        smac_init(i)                              // ← per-port MAC config
        npp_base[(i+1)*0x40000] |= 2              // MAC enable bit

    phy_process(0)
    add_timer(gephy_ldo_timer, +200, gephy_ldo_timer_func)  // periodic LDO check
    register_phy_int()
    zx5201_config()                           // ← External RGMII PHY (WAN!)
    add_timer(extphy_timer, +10, extphy_timer_func)

    // Start autoneg en el "lan_up_port" (puerto principal)
    val = zx_mdio_read(uni_phy[lan_up_port], 0)
    zx_mdio_write(uni_phy[lan_up_port], 0, val | 0x0800)  // BMCR_ANRESTART
```

### MAC[i] register map (per-port, 256KB window)

Bases: `npp_base + (i+1) * 0x40000`
- MAC0 → 0x92200000 → GePHY → RJ45 #1
- MAC1 → 0x92240000 → GePHY → RJ45 #2
- MAC2 → 0x92280000 → GePHY → RJ45 #3
- MAC3 → 0x922c0000 → GePHY → RJ45 #4
- MAC4 → 0x92300000 → RGMII → external (WAN externo)

`smac_init(port)` config por MAC:
| offset (per MAC) | valor | función |
|---|---|---|
| `+0x000` | `0xbae003` | MAC control |
| `+0x004` | `0xffff` | IRQ mask? |
| `+0x008` | `0x80000001` | enable + timer? |
| `+0x0e0` | `func_table_ptr` | PHY callback table |
| `+0xd00` | `clear bit 1` | reset something |
| `+0xd30` | `clear bit 5` | reset something |

## RGMII WAN — zx5201_config (External PHY)

External PHY at MDIO addresses **8 and 9** (probably Realtek RTL5201 family):

```c
zx5201_config():
    DSB
    val = uRamf060000c & 0xffe7f7ff   // ← clear some bits in TOPCRM at 0xf060000c
    DSB
    uRamf060000c = val

    // PHY init sequence (Realtek-specific magic registers)
    zx_mdio_write(8, 0x12, 0x8402)
    zx_mdio_write(9, 0x16, 0xa0f)
    zx_mdio_write(9, 0x1b, 0x800)
    zx_mdio_write(8, 0x1d, 0x355)
    zx_mdio_write(8, 0x10, 0xb62d)
    zx_mdio_write(8, 0x11, 6)
    zx_mdio_write(9, 0x12, 4)
    
    val15 = zx_mdio_read(9, 0x15)
    val14 = zx_mdio_read(9, 0x14)
    zx_mdio_write(9, 0x11, (val15 & 0xc1ff) | 0x2800)
    zx_mdio_write(9, 0x10, val14)
    zx_mdio_write(9, 0x12, 0x204)
    val16 = zx_mdio_read(9, 0x16)
    zx_mdio_write(9, 0x16, (val16 & 0xfff3) | 4)

    if (product_vid == 0x20):  // ← TU device es product_vid=32 (h1600 variant)
        // Additional Realtek "magic" register init
        ...
```

**MMIO 0xf060000c**: alguna región mapeada estáticamente (probablemente TOPCRM
extra). Hay que verificar phys correspondiente desde mach-zx.

## NPP IRQ handler (pon_npp_int) — solo PTP/OAM

```c
pon_npp_int():
    status = npp_base[0]
    mask = npp_base[1]
    if (status & ~mask & 0x20000) ptp_isr()
    if (status & ~mask & 0x40000) oam_isr()  // OAM = fiber, ignorar
```

NPP IRQ NO maneja RX ethernet — eso es vía `g_idm_irq` / `idm_net_int` (NAPI poll).

### Register map NPP COMPLETO (post-RE)

| offset | función | valor init |
|---|---|---|
| `+0x04` | mask global | `0xffffffff` |
| `+0x08` | IRQ enable | `0xffffff` |
| `+0x0c` | IRQ mask | `0xfffff` |
| `+0x40` | NPP control | OR `0x300` |
| `+0x48` | reset | `0` |
| `+0x8000` | IDM control | OR `0xf0000`, then `(&0xf00fffff)|0x2000000` |
| `+0x8004` | desc TX base / split | `dma_handle + 0x4000` |
| `+0x8008` | desc RX base | `dma_handle` |
| `+0x800c` | RX enable/config | `0x4000800` |
| `+0x8010` | ? | `0x40` |
| `+0x8018` | ? | `0x40` |
| `+0x801c` | timeout/count | `5000` |
| `+0x8020` | IRQ status (R) | — |
| `+0x8024` | IRQ mask | `0x1f` |
| `+0x8044` | TX status (R) | — |
| `+0x8048` | RX kick | `0x10000` |
| `+0x804c` | RX queue len (R, low 16) | — |
| `+0x80c0` | ? | `0` |
| `+0x10008` | ? | `0x80` |

## IDM netdev (idm_net_register)

```c
idm_netdev = alloc_etherdev_mqs(0xf0, 1, 1);  // 240B priv, 1tx/1rx queue
idm_netdev->netdev_ops = &idm_net_netdev_ops;
idm_netdev->watchdog_timeo = 5000ms;
register_netdev(idm_netdev);
```

`idm_net_netdev_ops` callbacks (decompiled):
- `.ndo_init` → `idm_net_init` (NAPI poll trigger)
- `.ndo_open` → `idm_net_open` (clear bit, netif_carrier_on, unmask IRQ)
- `.ndo_stop` → `idm_net_stop`
- `.ndo_start_xmit` → `idm_net_tx`
- `.ndo_set_mac_address` → `ethdrv_port_dev_set_mac_addr`
- `.ndo_get_stats` → `idm_eth_get_stats`
- `.ndo_tx_timeout` → `idm_net_timeout`
- NAPI poll function → `idm_net_poll`

## TX path resumen (idm_net_tx)

```c
spin_lock_irqsave(&idm_lock_tx, flags);
if (idm_skb_tx >= 0x200 || pending >= 0x400):
    drop;
else:
    write SKB to NPP TX queue (offset TBD)
    idm_skb_tx++
    if (npp_base + 0x8044 < 0x4000000): inc counter A
    else: inc counter B
spin_unlock_irqrestore;
```

## PHY init (gephy_ldo_init)

```c
for each PHY in uni_phy[4]:
    zx_mdio_write(phy_addr, 0x17, 0x2448)
    zx_mdio_write(phy_addr, 0x10, 0xb640)
    
    if (some condition with 0xf0807000-0xf080700c):
        zx_mdio_write(phy_addr, 0x11, 0x1f)
        g_geLdoFlag = 0
    else:
        zx_mdio_write(phy_addr, 0x11, 0x1f)
        g_geLdoFlag = 1
```

Estatus PHY mapeado a virt **0xf0807000-0xf080700c** — necesita estar en mach-zx static iomap?

## Approach mainline driver propuesto

Estructura modular:
```
drivers/net/ethernet/zte/
├── Kconfig
├── Makefile
├── zx279128-pon.c       ← driver PON (clocks + reset, requerido aunque sea LAN)
├── zx279128-tm.c        ← ⭐ NUEVO: TM subsystem (BMU + DMA + RX/TX para "sw" netdev)
├── zx279128-npp.c       ← driver NPP (IRQ controller + RX/TX queues)
├── zx279128-mdio.c      ← MDIO bus driver
├── zx279128-gephy.c     ← PHY driver (LDO init + autoneg)
├── zx279128-idm.c       ← MAC driver (netdev_ops, NAPI poll) — para WiFi
└── zx279128-common.h    ← reg defines + struct shared
```

## ⭐ TM (Traffic Manager) — Subsistema REAL de CPU↔ethernet

### Bases relevantes (todas dentro de nuestro ioremap actual)
- `tm_base = 0x92340000` (= npp_base + 0x180000 en nuestro mapping)

### `pon_tm_dma_init` — DMA setup
```c
tm[0x10000] |= 0x2f0000;
tm[0x10028] = 1;          // ?
tm[0x1002c] = 1;          // ?
tm[0x10030] = 50000;      // some timeout
tm[0x10034] = 0x40;
tm[?+4]    = 0x7f;        // tm_set_onu_mac global offset (unknown abs)
tm[0x10020] = 0x20;
tm[0x10024] = 0x20;
tm[0x10050] = bppe_pool_phys_addr + N;  // BPPE region base for queue X
tm[0x10060] = bppe_pool_phys_addr + N + 0x10000;  // queue Y
tm[0x10388] = 0x131217;
tm[0x1003c] = 0x400040;
```

### `pon_tm_bmu_init` — Buffer Memory Unit
- Allocates **BPPE pool** (Buffer Pool Pointer Element) at `bppe_va_addr`
- Allocates **Jumbo BPPE pool** at `jumbo_bppe_va_addr`
- Each BPPE = u16 index (byteswapped), 2B per entry, populated 0..N
- Pool sizes: `u32_BPPE_POOL_SIZE` (= 0x6c4 from stock?), `u32_JUMBO_BPPE_POOL_SIZE`
- Buffer slot sizes: `u32_BP_SIZE`, `u32_JUMBO_BP_SIZE`
- `dma_cache_maint(bppe_va_addr, 0x20000, 1)` — flush 128KB
- Then writes pool config regs:
  - tm[0x8000] = 0
  - tm[0x8004] = 0x104c040  (BMU control)
  - tm[0x8008] = 0x104c040
  - tm[0x8058] = (BPPE_POOL / 32) - 1
  - tm[0x805c] = (JUMBO_BPPE_POOL / 32) - 1
  - tm[0xe8/0xec/0xf4/0xf8/0xfc] = phys addrs to BP regions
  - tm[0x8048] = BPPE_POOL << 16
  - tm[0x804c] = JUMBO_BPPE_POOL << 16

### `pon_tm_bmu_alloc_bp` — Get a buffer slot
```c
poll tm[0x8014] bit 0 == 0   (busy clear)
write tm[0x8014] |= 1          (request)
poll tm[0x8014] & 3 == 0       (done, no error)
read  tm[0x800c]                (high bit = error, low 16 = BP index)
```

### `pon_tm_int_init` + `pon_tm_net_int` — IRQ
```c
tm[0x104] = 0xffffffff;           // ack/enable mask
request_threaded_irq(g_tm_irq, zx_pon_tm_int, ...);

zx_pon_tm_int → pon_tm_net_int:
    tm[0x104] |= 7;               // re-arm bits 0,1,2
    napi_schedule(napi);
```

### `pon_tm_net_init` — netdev registration
```c
pon_tm_netdev[1] = pon_tm_net_register(1, "pon");  // = pon netdev
pon_tm_netdev[0] = pon_tm_net_register(0, "sw");   // = sw netdev ⭐
netif_napi_add(sw_netdev, napi, pon_tm_net_poll, weight=0x200);
pon_tm_queue_init();
tm[0x104] |= 7;
add_timer(pon_tm_timer);
```

### `pon_tm_net_poll` — NAPI poll function (RX path)
- Iterates **8 RX queues** (0..7)
- Per queue, reads desc count at `tm[0x4040*4 + q*4]` low/high 16 bits
- **2 destination netdevs based on desc[6] bit 0**:
  - bit set → `pon_tm_netdev[1]` (pon)
  - bit clear → `pon_tm_netdev[0]` (sw)
- Desc layout (16 bytes per slot):
  - byte 7: low 7 bits of BPPE index
  - byte 8: high bit of BPPE index
  - byte 9 bit 0: is_jumbo flag
  - bytes 12-13: length (u16, in `>>2` units? need check)
- BP physical addr = `pdt_mem_size + 0x405e0000 - ZX_RESERVE*0x100000 + bppe_idx * BP_SIZE`
  (for normal; jumbo uses different base)
- For each frame:
  - `__netdev_alloc_skb(netdev, len+0x12, headroom=0x20)`
  - memcpy from BP into SKB
  - `netif_receive_skb` (or call `switch_skb_recv` hook)
  - Release BP back to pool via `pp_bmu_free_bp`
- After processing batch: `soft_release_rx_desc(jumbo, queue, hash_flag, count)`

### Resumen del data flow correcto:
```
ARP request from host
  → MAC0 → SW → PP forwarding decision (dst MAC=01:00:5e... or br0 MAC)
  → PP allocates BPPE from BMU pool, copies frame into BP
  → PP enqueues RX desc to TM queue N
  → TM IRQ fires (g_tm_irq = GIC 68 = SPI 36)
  → pon_tm_net_int schedules NAPI
  → pon_tm_net_poll processes desc → SKB → netif_receive_skb on `sw` netdev
  → br0 hook intercepts, forwards to userspace ICMP handler
  → ICMP reply via pon_tm TX path
```

### Lo que falta en NUESTRO driver:
1. **Reservar memoria DDR** (~25MB en top de RAM, base = 0x4E700000 per stock)
2. **Implementar pon_tm_bmu_init** (poblar pools, escribir regs)
3. **Implementar pon_tm_dma_init**
4. **Registrar TM IRQ** (`platform_get_irq_byname(pdev, "tm")`, SPI 36 / GIC 68)
5. **Implementar pon_tm_net_poll** (8 queues, BPPE dispatch, BP memcpy to SKB)
6. **Crear "sw" netdev** (no idm0/idm1) con NAPI sobre el handler TM
7. **Implementar TX** vía `pon_tm_data_raw_send` (= write BP, push BPPE to TX queue)

### Resto (IDM para WiFi — posponer):
- IDM stays as-is in driver (registers idm0/idm1 — funciona pero solo se va a usar cuando portemos WiFi forwarding via idmfdb).
- idm_skb_recv callback → wired by future idmfdb port.

## 📊 Datos del stock vivo (2026-05-19 dumps)

Capturados vía SSH (`/home/ubuntu/Projects/MYSELF/ZTE/H3600/stock_dumps/`):

### Memory layout
```
/proc/iomem:
40000000-4fffffff : System RAM       (256MB)
  40008000-40632fef : Kernel code     (~6MB)
  4066a000-4081139f : Kernel data     (~1.7MB)

/proc/meminfo:
MemTotal:  226100 kB   (220MB visible)
→ Kernel uses 220MB, top ~30MB reserved para gear de red

stock /proc/cmdline:
console=ttyAMA0 root=/dev/mtdblock8 ro rootfstype=jffs2 mem=256M
                                                        ^^^^^^^^
              Stock NO usa carveout via mem= ni reserved-memory DT!
              El kernel ve 256MB pero stock reserva via reserve_mem_info()
              (allocator interno que sale del top de RAM)
```

### TM live regs (stock corriendo, tráfico activo):
```
tm[0x104]  = 0xFFFFFFFF   ← TM IRQ enable mask (all bits)
tm[0xE8]   = 0x4E700000   ← BPPE physical base in DDR ⭐
tm[0x8000] = 0            ← BMU init
tm[0x8014] = 0            ← BMU alloc ready
tm[0x8048] = 0x50         ← BPPE pool runtime consumed count (init was POOL<<16)
tm[0x804c] = 0x660050     ← Jumbo BPPE pool
tm[0x8058] = 0x100        ← (POOL_SIZE/32)-1 → POOL_SIZE ≈ 8192
tm[0x805c] = (jumbo size)
```

Derived: **`u32_BPPE_POOL_SIZE = 0x2020`** (8224 entries), with stride 32 buckets.
Carved region in DDR = 25MB starting at **0x4E700000** physical.

### Reserved memory layout (`reserve_mem_info` printk RE):
Stock allocates (from top of RAM, growing down):
```
ZX_RESERVE_MEM_SIZE = configurable (default 25-30MB)
pdt_mem_size = total RAM = 0x10000000 = 256MB
Top of reserved = pdt_mem_size + 0x40000000 = 0x50000000

Layout (offsets from top):
+0x40000000  ZX_PA_BUF_BASE0     (start of reserved region)
+0x40020000  ZX_ACL_BASE
+0x40420000  ZX_FLOW_BASE
+0x40520000  ZX_BP_BUFFER_BASE   ← BP backing store for BPPE
                +BPPE_POOL*BP_SIZE = ZX_DESC_BASE (desc ring)
+0x405e0000  ZX_TX_UP_DESC_BASE  (TX up direction desc)
+0x405f0000  ZX_TX_DN_DESC_BASE  (TX down direction)
+0x40000000  ZX_VA_BPPE_BASE     (BPPE index array, u16 per entry)
+0x40520000  ZX_VA_BP_BUF_BASE   (alias of BP_BUFFER_BASE)
```

### Stock IRQ wiring (`/proc/interrupts`):
```
27 GIC 67 pon_npp     ← NPP IRQ (we currently target this as "npp")
28 GIC 70 idm         ← IDM IRQ (we currently target as "idm" → BUG, for WiFi)
29 GIC 68 pon_tm      ← TM IRQ ⭐ ← THIS IS WHAT WE NEED
30 GIC 69 pon_pp      ← PP IRQ (probably for PPE events)
31-34 gphy0-3         ← GePHY link change
```

So GIC line 68 = SPI 36 (after subtracting 32) = **0x24**. We need to add this
to DT and register handler. Currently our driver registers only IDM IRQ (SPI 38).

### Stock netdev TX/RX stats during active session:
```
br0:   1318 RX, 1262 TX   (bridge, has 192.168.1.1)
sw:    1296 RX, 1241 TX   ⭐ ← THIS is pon_tm_netdev[0], real CPU↔switch traffic
eth1:  1318 RX, 1262 TX   (wrapper around sw, port 1)
idm0:  0, 0               (WiFi forwarding, unused without active wifi)
idm1:  0, 0
```

Confirms TM path is the active CPU↔switch path.

## Implementation plan — TM driver port

Iterative approach using Airoha `airoha_eth.c` as architectural reference:

### Phase 1: minimal TM scaffolding (no traffic yet)
- DT: add `reserved-memory` node for 25MB at `0x4E700000-0x50000000` + reference
  it from eth node via `memory-region` property
- Driver: parse reserved-mem, register TM IRQ, dummy NAPI handler (just count)
- Validate via live_load_mod that TM IRQ FIRES (count goes up)

### Phase 2: BMU + DMA init
- `pon_tm_bmu_init`: populate BPPE index array, write tm[0x8048/0x804c/0x8058/0x805c/0xe8/0xec/...]
- `pon_tm_dma_init`: write tm[0x10000/0x10028..0x10388]
- Validate: read back regs, check they stuck

### Phase 3: "sw" netdev + RX
- Replace idm0/idm1 with single "sw" netdev (eth->ports[0])
- NAPI poll based on airoha_qdma_rx_napi_poll + stock pon_tm_net_poll RE
- 8 queues, demux per desc[9] is_jumbo + desc[6] bit 0 sw_or_pon
- Validate: ping from host → counter goes up + dmesg shows RX

### Phase 4: TX
- `pon_tm_data_raw_send`: alloc BP via BMU, memcpy SKB into BP, write TX desc
- Validate: ping replies from modem to host

### Phase 5: cleanup + per-port netdevs (eth0..eth4)
- Eventually wrap with per-port netdevs as stock does (pdt_ethdriver_init pattern)
- For now: just use `sw` netdev with bridge in userspace if needed

## Stock RE done — all functions decompiled

| Function | Status |
|----------|--------|
| `pon_tm_net_init` | ✅ RE'd |
| `pon_tm_net_int` (IRQ handler) | ✅ RE'd |
| `pon_tm_net_poll` (NAPI) | ✅ RE'd (313 lines) |
| `pon_tm_net_register` | ✅ RE'd |
| `pon_tm_net_open/stop` | ✅ RE'd |
| `pon_tm_dma_init` | ✅ RE'd |
| `pon_tm_bmu_init` | ✅ RE'd |
| `pon_tm_bmu_alloc_bp` | ✅ RE'd |
| `pon_tm_bmu_alloc_jumbo_bp` | ✅ RE'd |
| `pon_tm_bmu_enable` | (trivial) |
| `pon_tm_red_init` | ✅ RE'd (queue config) |
| `pon_tm_queue_init` | ✅ RE'd |
| `pon_tm_data_raw_send` (TX) | ✅ RE'd |
| `pon_tm_get_next_txdesc` | ✅ RE'd |
| `pon_tm_check_tx_done_nolock` | ✅ RE'd |
| `pon_tm_timer_func` | ✅ RE'd |
| `reserve_mem_info` | ✅ RE'd (memory layout) |
| `pon_tm_int_init` | ✅ RE'd |
| `red_set_queue_cfg` | partial |
| `soft_release_rx_desc` | needed |
| `soft_insert_tx_1desc` | needed |
| `pp_bmu_free_bp` | needed |

Para BOOT minimal sin forwarding, solo necesitamos:
- pon clocks ON
- npp básico (TX/RX queues + IRQ)
- mdio + gephy
- idm netdev

Sin TM/PP (forwarding) — el kernel mainline puede hacer software bridging. Mucho menos trabajo.

## TX descriptor format (8 bytes per entry, decompilado)

```
struct idm_tx_desc {
    u32 dma_addr;            // physical address of data
    u32 len_flags;           // bit 0-20: length
                             // bit 28-30: type/flags
                             // bit 31: port flag (0=idm0, 1=idm1)
};

idm_net_tx flow:
    tx_desc[idx].dma_addr = virt_to_phys(skb->data)
    tx_desc[idx].len_flags = skb_len | (port<<31) | (type<<28)
    npp_base[0x8040] = count << 16         // TX kick

TX ring: 1024 entries (`idm_tx_index & 0x3ff`)
SKB TX pool: 0x200 (pre-allocated)
Per-port pending limit: 0x400
```

## Sub-inits — TODOS RE-DEADAS (oneliners triviales)

```c
void pon_npp_spa_init(void)  { npp[0x141c0] = 0; }
void pon_npp_sipc_init(void) { npp[0xc000]  = 0x11; }
void pon_npp_uopc_init(void) { npp[0x18000] |= 8; }
void pon_npp_smct_init(void) {
    npp[0x10000] = 0xb;
    npp[tm_set_onu_mac_off + 4] = 0xb;   // TBD: tm_set_onu_mac es relativo a npp
    npp[0x10010] = 0x3810;
}
```

Estos son sub-bloques NPP (SPA / SIPC = service-packet-adapter / inter-packet-comm;
UOPC = upstream operation; SMCT = ?). En modo LAN-only sin fibra probablemente
SPA + SIPC son no-op pero baratos de hacer. UOPC y SMCT pueden ser necesarios
para que el switch reciba paquetes desde CPU.

## smac_init(port) — RE COMPLETO (168 B)

```c
void smac_init(int port) {
    void __iomem *base = npp_base + (port + 1) * 0x40000;   // MAC[i] window
    writel(0xbae003,   base + 0x000);   // MAC control
    writel(0xffff,     base + 0x004);   // IRQ mask
    writel(0x80000001, base + 0x008);   // enable + timer
    writel((u32)PTR_phy_callback_table, base + 0x0e0);
    val = readl(base + 0xd00);  writel(val & ~0x2,  base + 0xd00);   // clear bit 1
    val = readl(base + 0xd30);  writel(val & ~0x20, base + 0xd30);   // clear bit 5
}
```

## pon_npp_smac_init — RE COMPLETO (352 B)

```c
int pon_npp_smac_init(void) {
    gephy_ldo_init();                                    // power on LDOs

    for (int i = 0; i < 4; i++) {
        zx_mdio_write(uni_phy[i], 0x10, 0x8001);         // PHY init bit
        zx_mdio_write(uni_phy[i], 0x11, 0);
        smac_init(i);
        npp[(i+1)*0x40000] |= 2;                         // MAC[i] enable
        has_phy_int[i] = 1;
        uni_phy_stat[i] = 0xffffffff;                    // mark unknown
    }
    phy_process(0);                                      // initial state machine kick
    setup_timer(&gephy_ldo_timer, gephy_ldo_timer_func, jiffies+200);
    register_phy_int();                                  // GePHY IRQ → IRQ handler
    zx5201_config();                                     // external Realtek WAN PHY
    setup_timer(&extphy_timer, extphy_timer_func, jiffies+10);
    uni_phy_stat[4] = 0xffffffff;

    // Start autoneg on the "primary" LAN port
    val = zx_mdio_read(uni_phy[lan_up_port], 0);
    zx_mdio_write(uni_phy[lan_up_port], 0, val | 0x0800);  // BMCR_ANRESTART
    return 0;
}
```

## idm_net_poll — ya RE-deada (ver sección "RX kick / ACK" arriba)

## gephy region 0xf0807000 — TODO

Aparece en `gephy_ldo_init` para chequeo per-PHY antes de escribir reg 0x11.
Probable: mapeo estático en mach-zx que apunta a algún region de PHY control.
Lo dejamos para cuando el driver compile y veamos qué pasa al runtime.

## Estimación

| Phase | Tiempo |
|---|---|
| RE de las 5 funciones faltantes | 1-2 días |
| Escribir skeleton driver con probe | 1 día |
| Hacer que el carrier UP/DOWN funcione | 1 día |
| TX funcional (poder mandar paquetes) | 2-3 días |
| RX funcional (recibir) | 2-3 días |
| Debug/iteración | 3-5 días |
| **TOTAL** | **~2 semanas full-time** |

## Recursos para iteración rápida

Cuando empecemos a debuggear:
- `CONFIG_MODULES=y` para iterar driver via `insmod` sin reboot
- `CONFIG_DYNAMIC_DEBUG` para `dmesg` verboso del driver
- USB→Ethernet para network mientras tanto

## Referencias

- Stefan's `dwmac-zx29.c` — chip distinto pero PATTERN reusable (HRTIMER poll por IRQs rotos)
- Stock kmodules: `/H3600/rootfs/kmodule/{plat-zxylzb_9128S,switch,tm,idmfdb,zx_ponreg}.ko`
- Decomp Ghidra: `/H3600/ghidra/output_ko/<modulo>.ko/<funcion>.c`
- Stock DTS: `/H3600/extracted/h3600_real.dts`

---

## 2026-05-20 — Snapshot+replay strategy progress

### Estado actual
- **22363 stock regs** replayed en probe (PON early + NPP+ region)
- **CLA hash table**: 1804 entries replayed (ram=1+2+7) desde dump `stock_cla.bin`
- **pp_pm RAM**: 1025 entries replayed (ram=3 default flow_info + ram=6 global setting) desde dump `stock_pm.bin`
- TM IRQ se arma OK, BMU pools allocados, sw netdev registra
- **Symptom**: sw netdev RX = 0 packets a pesar del replay. Kernel se cuelga ocasionalmente — necesita full reboot 3min.

### Dumps tomados via /dev/mem indirect access en stock corriendo
- `stock_eth.bin` (2MB raw block 0x921c0000)
- `stock_pon_early.bin` (1.5MB pon-early region)
- `stock_pp.bin`, `stock_topcrm.bin`
- `stock_cla.bin` — 2820 CLA entries dumpeados via cla_set_indirect_rw_*
- `stock_pm.bin` — 2305 pp_pm entries (ram=3: 1024, ram=6: 1, ram=12: 256 ya las programamos como CPU MAC, ram=13: 1024 = packet trace buffer DESCARTAR)

### Lo que sigue NO funcionando
Replay completo de:
- 22363 NPP regs
- 1804 CLA entries  
- 1025 pp_pm entries
- Per-port MAC config
- VLAN setup (16 entries)
- Port isolate
- Trap-to-CPU bits

…y aún así sw netdev RX = 0. Lo que sospecho falta:
- **brg_ram tables** (FDB hash, VLAN modify) — dump devolvió empty cuando intenté
- **sub_ram, modify_ram** dentro de pp_pm — quizá ram_ids extra no dumpeados
- Algún kick/sync register que finaliza la config (un "commit/apply" final)

### Strategy nueva — bisect via snapshot diff
En vez de seguir agregando tablas a ciegas:
1. Boot stock corriendo → dump TODOS los registros de TM/sbrg/brg/pp/spa/cla bloque por bloque (`/dev/mem` byte-a-byte, ya tengo dumpmem.c)
2. Boot nuestro driver → dump los MISMOS registros
3. Diff binario → lista de offsets que difieren
4. Cada diff es un candidato concreto a debuggear

Esto reemplaza el "guess which table next" por una lista de gaps verificables.

### Riesgos del approach actual
- Kernel hangs cada N iteraciones → 3min reboot c/u
- Módulo creció 147KB → 297KB (transfer ~4 min)
- Bisecting incremental con runtime toggles sería más rápido pero requiere infra (debugfs hooks)


---

## 2026-05-20 — Iter speed FIX (B exitoso) + ping bidi sigue 0%

### Cambio: externalizar replay tables del .ko
- Removí `zx_stock_replay[]`, `zx_cla_replay[]`, `zx_pm_replay[]` como `static const` arrays
- Driver ahora hace `request_firmware("zx-replay/{stock,cla,pm}.bin", dev)` en probe
- Bins en formato binario simple: `[u32 magic 'ZXGR'][u32 count][records]`
- Bins viven en initramfs at `/lib/firmware/zx-replay/`
- Rebuild kernel UNA vez para meterlos al cpio

**Resultado:**
| Métrica | Antes | Ahora |
|---|---|---|
| .ko size | 297 KB | **26.5 KB** |
| Live iter (rmmod+xfer+insmod) | ~5 min (con drops) | **~30 s** |
| Full reboot iter | ~10 min (transfer falla) | ~3 min (boot+30s) |

### Test ping bidi post-replay
```
sw: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 ... f4:f6:47:0f:42:64
inet 192.168.1.1/24 scope global sw
PING 192.168.1.50 (192.168.1.50): 56 data bytes
3 packets transmitted, 0 packets received, 100% packet loss
```

sw netdev se abre, IP asignada, link UP, pero no llega NADA al CPU. TM IRQ count debe seguir en 0 (a verificar).

### Next steps (con iter rápida)
1. **Dump live regs**: bootstrap dumpmem en target, capturar 0x921c0000+0x200000 mapeado completo
2. **Diff vs `stock_eth.bin`**: lista de offsets que difieren (`diff_regs.py` ya escrito)
3. **Trickle de fixes**: cada candidato se prueba en ~30s ahora, no 6min

### Estado al final de este iter (07:58)
- ✓ Approach B (externalize replay) funciona end-to-end
- ✓ Iter rápida confirmada (~30s)
- ✓ Driver completo carga sin errores, replays todos OK
- ✗ Ping bidi: 100% packet loss (TM RX = 0 confirmado, mismo síntoma que antes)
- → Siguiente paso técnico: dump live regs (debugfs hook en driver, o fix del tiny dumper static) → diff vs `stock_eth.bin` → identificar gap concreto

### Notas técnicas para próximo iter
- `request_firmware()` busca en /lib/firmware/UTS_RELEASE/, /lib/firmware/updates/UTS_RELEASE/, /lib/firmware/updates/, /lib/firmware/
- Initramfs path config: `CONFIG_INITRAMFS_SOURCE="/tmp/initramfs_extract"` — para regenerar el cpio, repoblar /tmp/initramfs_extract + rebuild kernel + regen uimg
- `/dev/mem` con dd da 0 bytes (STRICT_DEVMEM=y probable). mmap funciona pero necesita binario libc-linked. Mejor: debugfs hook en el driver mismo

---

## 2026-05-20 08:13 — debugfs + BUG ENCONTRADO: TM IRQ_MASK invertido

### Stats post-replay (con ping en curso)
```
=== Driver counters ===
tm_irq_count      = 0     ← cero IRQs (problema)
tm_napi_count     = 0
tm_rx_count       = 0

=== TM regs ===
TM[0x0104] IRQ_MASK         = 0xffffffff  ← TODOS MASKED
TM[0x10068] DMA_DESC_CNT_DN = 0x2880 → 0  ← HW consumió 10368 descs sin avisar
```

### Análisis
Stock escribe `0xFFFFFFFC` a TM_IRQ_MASK (bits 0,1 cleared = enabled).
RE de `idm_net_open` confirma convención **1 = MASKED**:
```c
idm_int_mask = *(uint *)(npp_base + 0x8024) & 0xfffffffb;  // CLEAR bit 2
```

Nuestro driver hacía `tm_or(IRQ_MASK, 0x07)` (SET bits) tres veces:
1. zx_tm_init  
2. zx_sw_open  
3. zx_tm_poll (re-arm)

Y `tm_write(IRQ_MASK, 0)` en stop/remove (UNMASKABA TODO, opuesto a lo deseado).

### Fix
- Agregué `tm_and()` helper
- `tm_or(mask, 0x07)` → `tm_and(mask, ~0x07)` en init / open / poll-complete
- `tm_write(mask, 0)` → `tm_write(mask, 0xFFFFFFFF)` en stop / remove
- `TM_IRQ_ARM_BITS`: 0x07 → 0x03 (matches stock 0xFFFFFFFC bits 0,1)

Quote del bug:
```c
/* BEFORE - wrong (SETs bits = MASKs them) */
tm_or(e, TM_REG_IRQ_MASK, TM_IRQ_ARM_BITS);

/* AFTER - correct (CLEARs bits = ENABLEs them) */
tm_and(e, TM_REG_IRQ_MASK, ~(u32)TM_IRQ_ARM_BITS);
```

Esperado: post-fix `tm_irq_count` debe incrementarse al pingar, y el delta de DESC_CNT_DN se procesa, y eventualmente ping bidi anda.

## 2026-05-20 08:35 — IRQ_MASK fix verificado, pero IRQs siguen 0

Post-fix observations:
```
[ sw open: TM IRQ_MASK now 0xfffffffc (was 0xFFFFFFFF) ]  ← FIX OK
TM[0x0104] IRQ_MASK = 0xfffffffc   ← matches stock value exactly

$ cat /proc/interrupts | grep zx
 19:          0  zx279128-eth-idm
 21:          0  zx279128-eth-tm
```

A pesar de IRQ_MASK correcto, NEITHER TM ni IDM IRQ firan al tener tráfico. Tampoco con idm0 UP.

### Posibles causas (a investigar próximo iter)
1. **GIC trigger type**: Stock DTS pone los 3 IRQs en NODOS SEPARADOS (npp/tm/pp), nuestro DTS los junta bajo el mismo node. ¿Importa para Level trigger?
2. **Otro reg de enable** además de IRQ_MASK que falta — buscar en stock_regs writes a 0x18012X/0x18013X (que SÍ se replayan: 0x180124, 12C, 134)
3. **Switch realmente dropea antes de TM**: paquetes nunca llegan a la queue CPU → IRQ no tiene razón de firar
4. **TX path stub**: nuestro sw_xmit dropea todo → ARP nunca sale → host no nos pingea (ARP fails)

### Estado consolidado del approach
| Componente | Status |
|---|---|
| Replay stock regs | ✓ 22363 escritos |
| Replay CLA + pp_pm | ✓ 2829 escritos |
| TM IRQ_MASK | ✓ 0xFFFFFFFC = stock |
| Module size | ✓ 26-31KB |
| Iter speed | ✓ ~30s |
| /sys/.../zx_eth/stats | ✓ debugfs hook works |
| TM IRQ fires | ✗ count = 0 |
| IDM IRQ fires | ✗ count = 0 |
| sw netdev RX | ✗ tm_rx_count = 0 |
| sw netdev TX | ✗ unimplemented (drops) |
| Ping bidi | ✗ blocked |

### Próximas hipótesis a probar
1. Stock writes 0x180124 = 0x03FFFFFF (replayed por nosotros). Quizá esa es la real "queue enable mask". Verificar valor live.
2. Implementar TX stub básico que al menos arme un skb y kick un DMA, ver si el "TX_DONE" IRQ fires (test independiente del RX).
3. Mirar `set_pon_tm_int_info` stock function — quizá hay info de cómo armar el IRQ correctamente.
4. Probar `IRQ_TYPE_EDGE_RISING` en DTS para TM (long shot).

