# Driver PCIe ZX279128S — Design Document & RE notes

> Investigación para implementar driver mainline del PCIe controller del ZXIC
> ZX279128S (necesario para usar el WiFi MT7915 vía driver `mt76` mainline).
>
> **Status (2026-05-02)**: RE inicial del kernel stock vmlinux (kernel 4.1) hecho.
> Mapa de memoria, init flow y registros L0-state confirmados.

## Por qué necesitamos esto

El H3600 trae un MediaTek **MT7915** (WiFi 6 / 802.11ax dual-band) conectado vía
PCIe interno del SoC. El driver `mt7915` mainline es PCIe-bus only. Sin un
controller PCIe funcionando, el WiFi no levanta desde mainline. Como bonus, una
vez tengamos PCIe podemos enchufar otros devices (NVMe, otra WiFi card, etc).

Confirmado con:
- `/home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/lib/modules/mt7915.ko` (vendor MTK)
- `/home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/etc/wireless/mt7915/MT7915_EEPROM.bin`
- Strings en `mt7915.ko`: `RTMPInitPCIeDevice`, `pci_register_irq`

## Resumen ejecutivo del controller

| Atributo | Valor |
|---|---|
| **IP block** | Synopsys DesignWare PCIe (DWC) |
| **Prueba** | Strings `synopsys pcie probe enter!!!!!!`, `synopsys pcie%d controller setting`, `synopsys pcie%d controller waitting L0 state` |
| **Mainline glue driver** | NO existe — hay que escribirlo (estimado ~600 LoC) |
| **DT compatible (stock)** | `zte,zx279127-pcie` (también `zte,ZX279127-pcie` case-sensitive) |
| **Cantidad de root ports** | 2 (`pcie0`, `pcie1`) |
| **MSI** | Hipótesis: integrado del DWC (no MSI controller externo) |

**Buena noticia**: como es DesignWare PCIe upstream, mainline ya tiene:
- `drivers/pci/controller/dwc/pcie-designware.{c,h}` — core
- `drivers/pci/controller/dwc/pcie-designware-host.c` — modo Root Complex
- `drivers/pci/controller/dwc/pcie-designware-plat.c` — glue genérico (template)

Solo necesitamos el glue SoC-specific.

## Mapa de memoria (extraído por RE)

### Funciones decompiladas en `ghidra/output_pcie/`

| Función Ghidra | Nombre real | Strings que matchean |
|---|---|---|
| `FUN_c0015e04` | `synopsys_pcie_probe` | "synopsys pcie probe enter", "pcie0 irq is", "pcie1 irq is" |
| `FUN_c001605c` | `synopsys_pcie_setup` | "synopsys pcie%d controller setting", "not find pcie port" |
| `FUN_c0016840` | `synopsys_pcie_request_irq` | "request pcie irq failed" |
| `FUN_c00169c8` | `synopsys_pcie_wait_link_up` | "synopsys pcie%d controller waitting L0 state", "link up,gen,cnt" |

### Bases físicas extraídas del `synopsys_pcie_probe` (FUN_c0015e04)

```c
/* PORT 0 (struct base @ DAT_c069ea18, 56 bytes / 0x38) */
port[0].cfg_base       = 0x10000000;          /* DBI/CFG space PCIe0 */
port[0].phy_regs       = ioremap(0x0F000000, 0x4000);  /* PHY/secondary 16K */
port[0].crm_a          = 0xF0500000 (virt);    /* PCIe-CRM (VA static map) */
port[0].crm_b          = 0xF0400000 (virt);    /* TOPCRM (VA static map; phys 0x94000000) */
port[0].port_logic     = ioremap(0x09500000, 0x4000);  /* DWC port logic 16K */
port[0].mem_window     = ioremap(0x1C000000, 0x10000); /* MEM space (initial 64K) */
port[0].irq_main       = platform_get_irq(pdev, 0);    /* GIC SPI 63 → MSI/main? */
port[0].irq_aux        = platform_get_irq(pdev, 2);    /* GIC SPI 59 */

/* PORT 1 (struct base @ DAT_c069ea50, 56 bytes / 0x38) */
port[1].cfg_base       = 0x20000000;          /* DBI/CFG space PCIe1 */
port[1].phy_regs       = ioremap(0x0F100000, 0x4000);
port[1].crm_a          = 0xF0500000 (virt);    /* shared */
port[1].crm_b          = 0xF0400000 (virt);    /* shared */
port[1].port_logic     = ioremap(0x09600000, 0x4000);
port[1].mem_window     = ioremap(0x2C000000, 0x10000);
port[1].irq_main       = platform_get_irq(pdev, 1);    /* GIC SPI 78 */
port[1].irq_aux        = platform_get_irq(pdev, 3);    /* GIC SPI 74 */
```

### Tabla consolidada (memory map físico)

### Tabla consolidada — REINTERPRETADA tras descubrir ATU programmer

Después de encontrar `dw_pcie_program_outbound_atu` (FUN_c0015980 con offsets
0x900-0x91C estándar del DWC) y su caller (FUN_c00168a4):

```c
/* FUN_c00168a4(port=0): outbound ATU programming */
dw_pcie_program_outbound_atu(
    dbi_base = port[0].phy_regs(=0x0F000000),  /* DBI base!! */
    cpu_addr = 0x10000000,    /* CPU address window */
    limit    = 0x18000000,    /* + 128 MiB */
    pci_addr = 0x10000000,    /* identity mapping for PCIe addr */
    upper    = 0,
    region   = 0
);
/* port=1: cpu=0x20000000 limit=0x28000000 pci=0x20000000 */
```

**El driver llama "phy_regs" lo que en realidad es la DBI region** (donde están
los iATU registers en offsets `0x900+`). Mapping correcto:

| Region | Phys addr | Size | Función |
|---|---|---|---|
| **PCIe0 DBI** | `0x0F000000` | 16K | DWC core regs (iATU @ +0x900, port_logic offsets standard DWC) |
| **PCIe1 DBI** | `0x0F100000` | 16K | idem port 1 |
| **PCIe0 MEM window** | `0x10000000` - `0x18000000` | 128 MiB | Outbound ATU window — endpoint BARs aparecen aquí |
| **PCIe1 MEM window** | `0x20000000` - `0x28000000` | 128 MiB | idem port 1 |
| **PCIe0 SoC ctrl regs** | `0x09500000` | 16K | SoC-extra ctrl. **LTSSM mirror @ +0xDC** (no en DBI) |
| **PCIe1 SoC ctrl regs** | `0x09600000` | 16K | idem port 1 |
| **PCIe0 link_train regs** | `0x1C000000` | 64K | (a confirmar — quizás no necesario) |
| **PCIe1 link_train regs** | `0x2C000000` | 64K | idem |
| **TOPCRM (clocks/reset)** | `0x94000000` | 1M | virt 0xF0400000 — controla PCIe clocks |
| **PCIe-CRM (sub-reset)** | `0x94100000` | 1M | virt 0xF0500000 — controla PCIe sub-resets/PHY |
| **TOPCRM extra block** | `0x94200000` | 1M | virt 0xF0600000 — escritura en `+0x0C` durante setup |

### iATU programming (descubierto en FUN_c0015980)

Confirma 100% que es DesignWare PCIe — offsets ATU exactos a `pcie-designware.h`:

```c
#define PCIE_ATU_VIEWPORT       0x900   /* param_6 */
#define PCIE_ATU_CR1            0x904   /* param_5: type (MEM/IO/CFG0/CFG1) */
#define PCIE_ATU_CR2            0x908   /* hardcoded 0x80000000 = REGION_ENABLE */
#define PCIE_ATU_LOWER_BASE     0x90C   /* param_2 */
#define PCIE_ATU_UPPER_BASE     0x910   /* hardcoded 0 (32-bit only) */
#define PCIE_ATU_LIMIT          0x914   /* param_3 */
#define PCIE_ATU_LOWER_TARGET   0x918   /* param_4 */
#define PCIE_ATU_UPPER_TARGET   0x91C   /* hardcoded 0 */
```

### IRQs (orden en `platform_get_irq`)

DT `interrupts = <0x00 0x3f 0x04   0x00 0x4e 0x04   0x00 0x3b 0x04   0x00 0x4a 0x04>`
- index 0 → SPI 63 (0x3f) → port[0].irq_main
- index 1 → SPI 78 (0x4e) → port[1].irq_main
- index 2 → SPI 59 (0x3b) → port[0].irq_aux (MSI?)
- index 3 → SPI 74 (0x4a) → port[1].irq_aux (MSI?)

## Init flow del stock driver (probe)

```c
synopsys_pcie_probe(pdev) {
    /* === Pre-init: GPIO/PMU pin toggles (probable PERST# / clock req) === */
    pmu_set(0x35, 0); udelay(N);   /* deassert pin 53 */
    pmu_set(0x35, 1); mdelay(M);
    pmu_set(0x37, 0); udelay(N);   /* deassert pin 55 */
    pmu_set(0x37, 1); mdelay(M);

    pr_info("synopsys pcie probe enter!!!!!!");

    /* === Get IRQs from DT (4 total) === */
    irq[0] = platform_get_irq(pdev, 0);
    irq[2] = platform_get_irq(pdev, 2);
    pr_info("pcie0 irq is %d", irq[0]);
    irq[1] = platform_get_irq(pdev, 1);
    irq[3] = platform_get_irq(pdev, 3);
    pr_info("pcie1 irq is %d", irq[1]);

    /* === Build per-port struct (HARDCODED phys, no DT reg) === */
    port[0].cfg_base    = 0x10000000;
    port[0].phy_regs    = ioremap(0x0F000000, 0x4000);
    port[0].crm_a       = 0xF0500000;     /* static virt */
    port[0].crm_b       = 0xF0400000;     /* static virt of TOPCRM */
    port[0].port_logic  = ioremap(0x09500000, 0x4000);
    port[0].mem_window  = ioremap(0x1C000000, 0x10000);
    port[0].irq_main    = irq[0];
    port[0].irq_aux     = irq[2];

    port[1].cfg_base    = 0x20000000;
    port[1].phy_regs    = ioremap(0x0F100000, 0x4000);
    port[1].crm_a       = 0xF0500000;
    port[1].crm_b       = 0xF0400000;
    port[1].port_logic  = ioremap(0x09600000, 0x4000);
    port[1].mem_window  = ioremap(0x2C000000, 0x10000);
    port[1].irq_main    = irq[1];
    port[1].irq_aux     = irq[3];

    /* Initialize per-port (probably called from a worker or directly) */
    /* synopsys_pcie_setup(0); synopsys_pcie_setup(1); */
    /* synopsys_pcie_wait_link_up(0); ... */
    /* synopsys_pcie_request_irq(0); ... */
    /* dw_pcie_host_init equivalent */
}
```

## Reset / Clock sequence (`synopsys_pcie_setup` — FUN_c001605c)

Confirmado por disasm. Para **port 0**, secuencia exacta de bit-bangs:

```c
synopsys_pcie_setup(port=0) {
    pr_info("synopsys pcie%d controller setting", 0);

    /* 1. Gate clocks via TOPCRM */
    *(crm_b + 0x70) |= 0xb5;                /* enable PCIe gateable clocks */
    udelay(50);

    /* 2. Sub-reset deasserts (3 sequential bits) */
    *(crm_b + 0x08) |= 0x8000;  udelay(50);
    *(crm_b + 0x08) |= 0x2000;  udelay(50);
    *(crm_b + 0x08) |= 0x4000;  udelay(50);

    /* 3. Hold then release reset bit */
    *(crm_b + 0x74) &= ~0x1;    udelay(50);
    *(0xF060000C) &= ~0x4000;   udelay(500);  /* HARDCODED virt addr */
    *(crm_b + 0x24) &= ~(1<<26); udelay(50);
    *(crm_b + 0x74) |= 0x1;
    *(crm_b + 0x70) &= ~(1<<8);  /* clear gate (let it run) */

    /* 4. PHY regs init */
    *(crm_a + 0x00) |= 0x20;    /* PHY config bit */

    /* 5. Port logic init */
    *(port_logic + 0xA0) = (*(port_logic + 0xA0) & 0xFFFFFFF0) | 1;  /* link width=1 / lane config */
    *(port_logic + 0x80) |= 0x20;  /* enable ? */
}
```

Para **port 1** (parametrizado), bits diferentes pero misma estructura:
- `crm_b[0x70] |= 0x1AA00`
- `crm_b[0x08] |= 0x8000000` → `|= 0x2000000` → `|= 0x4000000`
- `(port_logic + 0x1B4) = 0x202D5A` y `(port_logic + 0x1B0) = 0x46C24A` — **registros configurables hardcoded** (lane training params?)
- `crm_b[0x74] &= ~0x8` → eventualmente `|= 0x8`
- `crm_b[0x70] &= ~(1<<17)`
- Bit clear/set pattern similar
- `(port_logic + 0xA0) = (val & 0xFFFFFFF0) | 1`
- Final: `(crm_b + 0x74) = 0x3F` (full enable)

## Wait link up (`synopsys_pcie_wait_link_up` — FUN_c00169c8)

```c
synopsys_pcie_wait_link_up(port) {
    pr_info("synopsys pcie%d controller waitting L0 state", port);

    int i = 2000;
    do {
        udelay(50);  /* approx — based on (*DAT_c068531c)(0x66665b0) call */
        u32 dbg = *(port_logic + 0xDC);

        /* LTSSM state in bits [22:17] (6 bits)
         * 0x11 (decimal 17) = L0 state in DesignWare PCIe */
        if (((dbg << 9) >> 26) == 0x11) {
            u32 link_width = *(phy_regs + 0x80) << 12 >> 28;  /* bits [19:16] */
            int delta = 2001 - i;
            pr_info("pcie%d link up,gen%d,cnt %d!", port, link_width, delta);
            return 0;
        }
        i--;
    } while (i);
    return -ETIMEDOUT;
}
```

**Insight clave**: el offset `0xDC` en port_logic es el **LTSSM debug register**.
En DesignWare canon esto es `PORT_LOGIC_LINK_DEBUG_REG_2` o `PORT_DBG2`. La
state machine mapping (0x11 = L0) coincide con DWC standard.

## Que necesita un glue driver mainline

Mirando `drivers/pci/controller/dwc/pcie-designware-plat.c` y `pcie-spear13xx.c`:

```c
/* drivers/pci/controller/dwc/pcie-zx279128s.c — propuesta */

struct zx279128s_pcie {
    struct dw_pcie *pci;        /* upstream DWC core */
    void __iomem *port_logic;   /* phys 0x09500000 / 0x09600000 */
    void __iomem *phy_regs;     /* phys 0x0F000000 / 0x0F100000 */
    struct regmap *topcrm;      /* phys 0x94000000 — vía syscon */
    struct regmap *pcie_crm;    /* phys TBD — vía syscon */
    int port_id;                /* 0 o 1 */
    /* clocks, resets via clk/reset framework — to be defined */
};

static int zx279128s_pcie_host_init(struct dw_pcie_rp *pp) {
    struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
    struct zx279128s_pcie *zp = to_zx_pcie(pci);

    /* Reset/clock sequence (translation of synopsys_pcie_setup) */
    zx279128s_pcie_setup(zp);
    
    /* Wait for link up */
    if (zx279128s_pcie_wait_link(zp))
        return -ETIMEDOUT;

    /* DWC core takes over: ATU config, MSI init, bus scan */
    return 0;
}

static const struct dw_pcie_host_ops zx279128s_pcie_host_ops = {
    .host_init = zx279128s_pcie_host_init,
};

static int zx279128s_pcie_probe(struct platform_device *pdev) {
    struct zx279128s_pcie *zp = devm_kzalloc(...);
    zp->pci = devm_kzalloc(...);
    zp->pci->dev = &pdev->dev;
    zp->pci->ops = &dw_pcie_ops;
    zp->pci->pp.ops = &zx279128s_pcie_host_ops;

    /* Map regions */
    zp->port_logic = devm_platform_ioremap_resource_byname(pdev, "port_logic");
    zp->phy_regs   = devm_platform_ioremap_resource_byname(pdev, "phy");
    /* DBI is mapped automatically by DWC core via "dbi" resource */

    zp->topcrm    = syscon_regmap_lookup_by_phandle(np, "zte,topcrm");
    zp->pcie_crm  = syscon_regmap_lookup_by_phandle(np, "zte,pcie-crm");

    return dw_pcie_host_init(&zp->pci->pp);
}

static const struct of_device_id zx279128s_pcie_of_match[] = {
    { .compatible = "zte,zx279128s-pcie", },
    {},
};
```

### DT propuesto

```dts
pcie0: pcie@10000000 {
    compatible = "zte,zx279128s-pcie";
    reg = <0x10000000 0x4000>,    /* dbi */
          <0x09500000 0x4000>,    /* port_logic */
          <0x0f000000 0x4000>;    /* phy regs */
    reg-names = "dbi", "port_logic", "phy";

    ranges = <0x82000000 0 0x1c000000 0x1c000000 0 0x4000000>;  /* MEM */
    bus-range = <0x00 0xff>;

    interrupts = <GIC_SPI 63 IRQ_TYPE_LEVEL_HIGH>,  /* main */
                 <GIC_SPI 59 IRQ_TYPE_LEVEL_HIGH>;  /* msi */
    interrupt-names = "main", "msi";

    clocks = <&topcrm PCIE0_AXI>, <&topcrm PCIE0_REF>;
    clock-names = "axi", "ref";
    resets = <&topcrm PCIE0_RST>, <&pcie_crm PCIE0_PHY_RST>;
    reset-names = "core", "phy";

    zte,topcrm = <&topcrm>;
    zte,pcie-crm = <&pcie_crm>;
    
    status = "okay";
    #address-cells = <3>;
    #size-cells = <2>;
    device_type = "pci";
};

pcie1: pcie@20000000 { /* ... análogo, port 1 */ };
```

## Roadmap

1. [x] Confirmar IP block (DesignWare DWC) — strings ✓
2. [x] Confirmar 2 ports — strings ✓
3. [x] Encontrar DT compatible string — `zte,zx279127-pcie` ✓
4. [x] Disassembly `synopsys_pcie_probe` — bases físicas ✓
5. [x] Disassembly `synopsys_pcie_setup` — clock/reset sequence ✓
6. [x] Disassembly `synopsys_pcie_wait_link_up` — LTSSM offset (0xDC) ✓
7. [x] **Identificar phys real de virt 0xF0500000 y 0xF060000C** ✓:
       Extraído del `static_io_desc[]` (19 entradas) en `DAT_c065e6b0`:
       - 0xF0400000 → 0x94000000 (TOPCRM, confirmado)
       - 0xF0500000 → 0x94100000 (PCIe-CRM, sub-resets)
       - 0xF0600000 → 0x94200000 (extra crm block; offset +0x0C usado)
       - 0xF3000000 → 0x10000000 4M (PCIe0 DBI mapping permanente)
       - 0xF3400000 → 0x20000000 4M (PCIe1 DBI mapping permanente)
       Tabla completa: `/tmp/static_io_table.txt`
8. [x] Disassembly de funciones colaterales del PCIe driver ✓:
       - `FUN_c0015980` = `dw_pcie_program_outbound_atu` (iATU offsets confirmados!)
       - `FUN_c00168a4` = `synopsys_pcie_setup_atu` (configura outbound window MEM)
       Todos en `ghidra/output_pcie_extra/`
9. [x] Disassembly del IRQ handler (`LAB_c0015a74`) ✓:
       Es un STUB — solo `return 1` (IRQ_HANDLED). Confirma que stock NO usa
       MSI custom — usaremos el MSI integrado del DWC core (`dw_pcie_msi_init`).
10. [x] Esqueleto del glue driver compilado ✓:
       - `drivers/pci/controller/dwc/pcie-zx279128s.c` (320 líneas)
       - Kconfig + Makefile entries agregados
       - DTSI updated con nodos `pcie0`, `pcie1`, `topcrm`, `pcie_crm`, `pcie_crm2`
       - Compila clean (DTBs incluidos)
9. [ ] Mapear bits `0xb5`, `0x1AA00`, `0x8000`, `0x2000`, `0x4000` en
       TOPCRM contra alguna doc — son bits de clock-gate / reset-deassert
10. [ ] Decidir DT bindings finales — lograr consensus con upstream conventions
11. [ ] Escribir glue driver `drivers/pci/controller/dwc/pcie-zx279128s.c`
12. [ ] DT bindings doc en `Documentation/devicetree/bindings/pci/`
13. [ ] Update DTSI con nodos PCIe completos
14. [ ] Test inicial: link training (verificar `Link is Up`)
15. [ ] Test final: enumerar MT7915 → cargar driver mt76 → asociar a AP

## Referencias

- DesignWare PCIe IP: https://www.synopsys.com/dw/ipdir.php?ds=dwc_pcie_3
- mt76 driver mainline: `drivers/net/wireless/mediatek/mt76/`
- Ejemplos similares para template:
  - `drivers/pci/controller/dwc/pcie-designware-plat.c` (más simple)
  - `drivers/pci/controller/dwc/pci-imx6.c` (más completo, similar features)
  - `drivers/pci/controller/dwc/pcie-spear13xx.c` (single port, similar SoC)
  - `drivers/pci/controller/dwc/pcie-fu740.c` (RISC-V SiFive, glue puro)

## Fuentes RE

- Stock vmlinux: `/home/ubuntu/Projects/MYSELF/ZTE/H3600/extracted/vmlinux.bin`
- Stock DT: `/home/ubuntu/Projects/MYSELF/ZTE/H3600/extracted/h3600_real.dts`
- Decompiled fns: `/home/ubuntu/Projects/MYSELF/ZTE/H3600/ghidra/output_pcie/`
- Ghidra script: `/home/ubuntu/Projects/MYSELF/ZTE/H3600/ghidra/dump_pcie_funcs.py`

## Esfuerzo estimado

| Item | Tiempo (horas) |
|---|---|
| Identificar phys mappings restantes (TOPCRM/PCIe-CRM/PHY) | 2-4 h |
| Disasm del IRQ handler para MSI | 2 h |
| Escribir glue driver basado en `pcie-spear13xx.c` template | 8-12 h |
| Escribir DT bindings doc | 1 h |
| Update DTSI + .config | 1 h |
| Debug del primer link-up (esperar ~50% chance funcione al primer try) | 4-16 h |
| Total optimista | **18-30 h** |
| Total realista | **30-50 h** |

Mucho menos de lo que pensé inicialmente — porque el DWC core ya hace todo el
heavy lifting y solo escribimos el glue.

---

**Última update**: 2026-05-02. Próximo paso: identificar phys de las regiones
virt 0xF0500000 y 0xF060000C, y disassemblar el IRQ handler.
