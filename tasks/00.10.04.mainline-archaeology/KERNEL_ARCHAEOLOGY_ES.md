# Informe: Arqueología del soporte ZTE ZXIC en el kernel Linux mainline

**Objetivo:** recuperar y catalogar todo el código eliminado del kernel para reaprovecharlo en el port de OpenWrt al SoC **ZTE ZXIC ZX279128S** (router/ONU **ZTE H3600P V9**).

**Metodología:** worktree git en el commit anterior a la primera eliminación (`f3a732843acc`, 2021-01-18, equivalente a kernel ~5.11-rc4). Inventario, lectura de drivers y bindings, contraste con el hardware del H3600P documentado.

---

## 1. Resumen ejecutivo

El soporte ZTE ZX vivió en mainline entre **abril 2015** (`acede515b3a5` por Jun Nie / Linaro) y **enero 2021** (sweep liderado por Arnd Bergmann). Cubría dos SoCs:

- **ZX296702** — ARM Cortex-A9 dual, set-top-box, soporte completo (mach-zx, clk, gpio, dma, mmc).
- **ZX296718** — ARM Cortex-A53 quad, set-top-box, añadido en 2016-2017, soporte adicional (pinctrl, pwm, i2c, watchdog, thermal, soc/pm-domains, drm/vou/hdmi/vga).

El **ZX279128S** que necesitas portar es de la **misma familia interna ZXIC** que el **ZX296702** (Cortex-A9 dual @ 1 GHz). Según winnt5 (chinadsl.net 169478), las direcciones de registros y el modelo de clocks son compatibles.

**Lo aprovechable directamente (alta probabilidad):**

| Subsistema | Driver kernel | Reutilizable en ZX279128S |
|---|---|---|
| Clocks (TOP/LSP0/LSP1) | `drivers/clk/zte/clk-zx296702.c` | ✅ Sí, mismo modelo de PLLs y registros |
| GPIO | `drivers/gpio/gpio-zx.c` | ✅ Sí, registros idénticos esperados |
| DMA controller | `drivers/dma/zx_dma.c` | ✅ Sí, compatible "zte,zx296702-dma" |
| SMP (boot CPU1) | `arch/arm/mach-zx/platsmp.c` | ✅ Sí, idéntico patrón Cortex-A9 |
| Power-domains (PCU) | `arch/arm/mach-zx/zx296702-pm-domain.c` | ⚠️ Probable, depende de mismas máscaras |
| MMC (DesignWare) | `drivers/mmc/host/dw_mmc-zx.c` | ⚠️ Solo si el ZX279128S usa DW-MSHC; no consta |

**Lo que NO existe en ningún kernel ZX (vas a tener que escribirlo o adaptar genérico):**

| Subsistema H3600P | Estado |
|---|---|
| Switch interno + 4× GE PHY + RGMII | ❌ Cero código en mainline |
| NAND parallel Denali | ⚠️ Genérico `denali_dt.c` existe; falta wiring DT |
| USB 3.0 (DWC3) | ⚠️ Genérico `dwc3-of-simple.c` existe; falta clock/reset glue |
| PCIe 2.0 (×2) | ❌ Sin trazas ZX; depende del host controller real |
| xPON SerDes | ❌ No interesa (tienes ONT externo) |
| UART PL011 | ✅ Driver mainline `amba-pl011.c` lo cubre directo |

**Conclusión rápida:** vas a salir con kernel arrancando hasta consola (UART + clocks + GPIO + DMA + MMC) reciclando ~80% del trabajo de Jun Nie. Para red, USB y PCIe te toca casi de cero — pero al menos el SoC tendrá clock tree y pinmux funcionales para servirles.

---

## 2. Línea temporal del soporte ZX en mainline

| Fecha | Commit | Quién | Qué |
|---|---|---|---|
| 2015-04-28 | `acede515b3a5` | Jun Nie (Linaro) | **Nacimiento**: ARM: zx: add basic support for ZTE ZX296702 |
| 2015-05-05 | `e3fa9841d309` | Jun Nie | dmaengine: zxdma: ZX296702 |
| 2015-06-04 | `5a4658081226` | Jun Nie | clk: zx: clock support for zx296702 |
| 2015-06-29 | `e7aa6d8c1ba2` | Jun Nie | gpio: zx: ZX296702 GPIO |
| 2015-07-23 | `4599dd2c9269` | Jun Nie | clk: zx: audio div clocks |
| 2016-09-13 | `2e673c7dc37a` | Jun Nie | **arm64**: dts: ZX296718 SoC dts |
| 2016-09-22 | `0a886f59528a` | Shawn Guo (Linaro) | drm: zte: initial vou drm driver |
| 2017-01-06 | `4c2c2e39713b` | Baoyou Xie (Linaro) | soc: zte: pm_domains for zx2967 |
| 2017-04-24 | `cbff0c4d27f4` | Shawn Guo | pinctrl: ZTE ZX |
| 2018-04 onwards | (varios) | Shawn Guo, Arnd | mantenimiento, cleanups, SPDX |
| **2021-01-18** | **`89d4f98ae90d`** | **Arnd Bergmann** | **ARM: remove zte zx platform** ⚠️ |
| 2021-01-20 | 11 commits | Arnd Bergmann | Sweep paralelo: clk, dma, gpio, pinctrl, pwm, i2c, watchdog, thermal, ASoC, RC IR, power/reset |
| 2021-06-27 | `0c4f8fd3ed9c` | Arnd | ASoC dangling Kconfig |
| 2021-08-19 | `47ddb72f7893` | Arnd | DRM drivers/gpu/drm/zte |
| 2021-08-21 | `d014c93515e9` | Shawn Guo | dt-bindings/clock zx header |
| 2021-08-31 | `b1e202503508` | Rob Herring | dt-bindings: display vou.txt |
| 2021-11-02 | `635e4172bd0a` | Arnd | leftover cleanups |

**Mensaje de eliminación de Arnd Bergmann (resumido):**
> The ZTE ZX set-top-box SoC platform was added in 2015 by Jun Nie […] However, the only machines that were ever supported upstream are the reference designs, not actual set-top-box devices. […] there is very little information about zx296702 and zx296718 on the web, I found some references to other chips from the same family, such as **zx296716 and zx296719**, which were never submitted for upstream support. […] there is no support for the GPU on either of them. Shawn confirmed that he has not seen any interest in this platform for the past four years, and that it can be removed.

**Mantenedores:** Jun Nie (jun.nie@linaro.org) y Shawn Guo (shawnguo@kernel.org), ambos de Linaro.

**Ningún chip de tu familia (zx279127/8, zx279131-3) apareció jamás en commits de kernel.** Búsqueda exhaustiva de mensaje de commit y de contenido (`git log -i --grep=` + `git log -i -S` sobre todas las ramas y todos los archivos): cero matches reales para zx279127, zx279128, zx279131, zx279132, zx279133, zxic. Las dos únicas menciones a `zx296716`/`zx296719` son la propia commit message de eliminación de Arnd citando que "nunca fueron upstreamed".

---

## 3. Inventario completo de archivos

(Líneas medidas en `/tmp/linux-zxic` @ `f3a732843acc`. Excluidos falsos positivos: Motorola EZX, HP zx1, Aztech radio, NZXT.)

### 3.1 Arquitectura ARM (mach-zx)

| Path | Líneas | Tipo | Resumen |
|---|---|---|---|
| `arch/arm/mach-zx/Kconfig` | 21 | Kconfig | `ARCH_ZX`, `SOC_ZX296702` (CortexA9MP) |
| `arch/arm/mach-zx/Makefile` | 3 | Makefile | platsmp.o + headsmp.o + zx296702.o |
| `arch/arm/mach-zx/zx296702.c` | 22 | C | `DT_MACHINE_START`, dt_compat = "zte,zx296702" |
| `arch/arm/mach-zx/platsmp.c` | 186 | C | SMP boot: `zx_smp_ops`, `cpu_kill`, abre PCU/sysctrl/bus-matrix |
| `arch/arm/mach-zx/headsmp.S` | 30 | ASM | secondary CPU entry point |
| `arch/arm/mach-zx/zx296702-pm-domain.c` | 202 | C | PCU: 7 dominios (NEON0/1, GPU, DECPPU, VOU, R2D, TOP) |
| `arch/arm/mach-zx/core.h` | 16 | header | Declaraciones internas |
| `arch/arm/configs/zx_defconfig` | 122 | defconfig | Build-config de referencia |

### 3.2 ARM64 / DTS

| Path | Líneas | Tipo | Resumen |
|---|---|---|---|
| `arch/arm/boot/dts/zx296702.dtsi` | 142 | DTSI | SoC ZX296702 (Cortex-A9 dual, GIC, PL310 L2, sysctrl, 3 clock controllers, 2 UART, 2 MMC) |
| `arch/arm/boot/dts/zx296702-ad1.dts` | 48 | DTS | Placa de referencia AD1 (512 MiB RAM) |
| `arch/arm64/boot/dts/zte/zx296718.dtsi` | 627 | DTSI | SoC ZX296718 (Cortex-A53 quad, GIC-v3, 7 GPIO banks, vou/hdmi/vga, dw-mshc, dma, audio) |
| `arch/arm64/boot/dts/zte/zx296718-evb.dts` | 144 | DTS | Placa EVB |
| `arch/arm64/boot/dts/zte/zx296718-pcbox.dts` | 143 | DTS | Variante PCBox |
| `arch/arm64/boot/dts/zte/Makefile` | 3 | Makefile | dtb targets |

### 3.3 Drivers

| Path | Líneas | Subsistema | Resumen |
|---|---|---|---|
| `drivers/clk/zte/clk.c` | 446 | clk | Helpers comunes: PLL ops, audio divider |
| `drivers/clk/zte/clk.h` | 174 | clk | Estructuras `clk_zx_pll`, `zx_clk_gate`, macros `ZX_PLL`, `GATE`, `MUX`, `DIV_T`, `AUDIO_DIV` |
| `drivers/clk/zte/clk-zx296702.c` | 741 | clk | TOPCRM + LSP0CRPM + LSP1CRPM, PLL_A9 (700–1200 MHz, tabla cfg0/cfg1), 3× `CLK_OF_DECLARE` |
| `drivers/clk/zte/clk-zx296718.c` | 1074 | clk | Driver de plataforma con 4 compatibles: topcrm, lsp0crm, lsp1crm, audiocrm |
| `drivers/dma/zx_dma.c` | 941 | dma | DMA engine ZX, hasta 32 canales, scatter-gather + cyclic + memcpy. Compatible: `"zte,zx296702-dma"` |
| `drivers/gpio/gpio-zx.c` | 289 | gpio | Bank de 16 pines, IRQ chained, Compatible: `"zte,zx296702-gpio"` |
| `drivers/gpio/gpio-zx.c` | (incluye 9 registros: DIR/IVE/IV/IEP/IEN/DI/DO1/DO0/DO) | | |
| `drivers/i2c/busses/i2c-zx2967.c` | 602 | i2c | Master con FIFO, FastMode + HighSpeed, IRQ. Compatible: `"zte,zx296718-i2c"` |
| `drivers/mmc/host/dw_mmc-zx.c` | 234 | mmc | Glue para Synopsys DesignWare MSHC, regmap a sysctrl para tuning HS200/DDR50 |
| `drivers/mmc/host/dw_mmc-zx.h` | 32 | mmc | Defines (ZX_LB_OFF, ZX_DLL_LOCK_WO, etc.) |
| `drivers/pinctrl/zte/pinctrl-zx.c` | 445 | pinctrl | Core driver: muxing por offset/bit/width, AON+TOP regions |
| `drivers/pinctrl/zte/pinctrl-zx.h` | 102 | pinctrl | Estructuras `zx_pin_data`, `zx_mux_desc`, `zx_pinctrl_soc_info` |
| `drivers/pinctrl/zte/pinctrl-zx296718.c` | 1024 | pinctrl | 137 pines, mux table completa para EVB. Compatible: `"zte,zx296718-pmm"` y `"zte,zx296718-iocfg"` |
| `drivers/pwm/pwm-zx.c` | 278 | pwm | 4-channel PWM, polarity. Compatible: `"zte,zx296718-pwm"` |
| `drivers/power/reset/zx-reboot.c` | 86 | reset | restart handler vía sysctrl + PCU |
| `drivers/thermal/zx2967_thermal.c` | 256 | thermal | Sensor on-die. Compatible: `"zte,zx296718-thermal"` |
| `drivers/watchdog/zx2967_wdt.c` | 279 | watchdog | WDT con clk + reset. Compatible: `"zte,zx296718-wdt"` |
| `drivers/media/rc/zx-irdec.c` | 181 | rc | NEC-only IR decoder. Compatible: `"zte,zx296718-irdec"` |
| `drivers/media/rc/keymaps/rc-zx-irdec.c` | 76 | rc | keymap |
| `drivers/soc/zte/zx2967_pm_domains.c` | 141 | soc | Core power-domain framework genérico para zx2967 |
| `drivers/soc/zte/zx2967_pm_domains.h` | 44 | soc | Header `zx2967_pm_domain` struct |
| `drivers/soc/zte/zx296718_pm_domains.c` | 181 | soc | Definición de dominios concretos del 296718 |
| `drivers/soc/zte/Kconfig` | 15 | Kconfig | `SOC_ZTE`, `ZX2967_PM_DOMAINS` |
| `drivers/soc/zte/Makefile` | 6 | Makefile | |

### 3.4 GPU/DRM (resumen — probablemente no relevante para tu router)

| Path | Líneas | Notas |
|---|---|---|
| `drivers/gpu/drm/zte/zx_drm_drv.c` | 190 | bind/unbind del componente DRM |
| `drivers/gpu/drm/zte/zx_vou.c` | 921 | Video Output Unit (planos, CRTCs, dpc) |
| `drivers/gpu/drm/zte/zx_hdmi.c` | 760 | HDMI TX |
| `drivers/gpu/drm/zte/zx_vga.c` | 527 | VGA encoder |
| `drivers/gpu/drm/zte/zx_plane.c` | 533 | Planos OSD/GL |
| `drivers/gpu/drm/zte/zx_tvenc.c` | 400 | TV encoder analógico |
| (+ 6 archivos `*_regs.h` con offsets) | | |

**No me detengo en GPU**: el H3600P no tiene salida de vídeo. Si en el futuro lo necesitas, está completo.

### 3.5 Audio (resumen — opcional)

| Path | Líneas | Notas |
|---|---|---|
| `sound/soc/zte/zx-i2s.c` | 452 | I2S CPU DAI |
| `sound/soc/zte/zx-spdif.c` | 363 | SPDIF |
| `sound/soc/zte/zx-tdm.c` | 458 | TDM |
| `sound/soc/codecs/zx_aud96p22.c` | 401 | codec aud96p22 |

### 3.6 Headers globales

| Path | Líneas | Notas |
|---|---|---|
| `include/dt-bindings/clock/zx296702-clock.h` | 180 | IDs de clock (`ZX296702_PLL_A9`, `ZX296702_UART0_WCLK`, …) |
| `include/dt-bindings/clock/zx296718-clock.h` | 164 | IDs (`A53_GATE`, `EMMC_WCLK`, `NAND_WCLK`, `LSP0_UART1_WCLK`, …) |
| `include/dt-bindings/soc/zte,pm_domains.h` | 24 | IDs de power domains |

### 3.7 Documentation (DT bindings — todos legacy `.txt` salvo `zte.yaml`)

22 archivos. Lista en sección 6 más detalle.

**Total de líneas (excluyendo GPU/audio):** ~7 800 LOC. Incluyendo todo: ~13 200 LOC.

---

## 4. Tabla unificada de Device Tree

Direcciones extraídas de los DTSI. Las del **ZX296702** son las que más probablemente coinciden con el ZX279128S (misma familia ARMv7).

### 4.1 ZX296702 (`arch/arm/boot/dts/zx296702.dtsi`)

| Periférico | compatible | Reg base | Tamaño | IRQ (SPI) | Clocks |
|---|---|---|---|---|---|
| GIC interrupt-controller | `arm,cortex-a9-gic` | `0x00801000` | 0x1000 + 0x100 | — | — |
| Global timer | `arm,cortex-a9-global-timer` | `0x00800200` | 0x20 | PPI 11 | `topclk ZX296702_A9_PERIPHCLK` |
| L2 cache PL310 | `arm,pl310-cache` | `0x00c00000` | 0x1000 | — | — |
| Bus matrix | `zte,zx-bus-matrix` | `0x00400000` | 0x1000 | — | — |
| PCU (Power Control Unit) | `zte,zx296702-pcu` | `0xa0008000` | 0x1000 | — | — |
| sysctrl / restart | `zte,sysctrl` (+ syscon) | `0xa0007000` | 0x1000 | — | — |
| TOP CRM clocks | `zte,zx296702-topcrm-clk` | `0x09800000` | 0x1000 | — | — |
| LSP1 CRPM clocks | `zte,zx296702-lsp1crpm-clk` | `0x09400000` | 0x1000 | — | — |
| LSP0 CRPM clocks | `zte,zx296702-lsp0crpm-clk` | `0x0b000000` | 0x1000 | — | — |
| UART0 | `zte,zx296702-uart` | `0x09405000` | 0x1000 | 37 | `lsp1clk UART0_WCLK` |
| UART1 | `zte,zx296702-uart` | `0x09406000` | 0x1000 | 38 | `lsp1clk UART1_WCLK` |
| MMC0 (LSP1) | `snps,dw-mshc` | `0x09408000` | 0x1000 | 40 | `lsp1clk SDMMC0_PCLK/WCLK` |
| MMC1 (LSP0) | `snps,dw-mshc` | `0x0b003000` | 0x1000 | 20 | `lsp0clk SDMMC1_PCLK/WCLK` |

> Nota importante: **los UARTs no son PL011**. Compatible propio `zte,zx296702-uart` — pero el driver nunca llegó a mainline. Para el ZX279128S, el datasheet del H3600P dice "UART PL011 estándar ARM", lo cual es **diferente** del ZX296702 y mejor para nosotros (driver `amba-pl011.c` upstream funciona out-of-the-box).

### 4.2 ZX296718 (`arch/arm64/boot/dts/zte/zx296718.dtsi`)

Solo selección de los nodos relevantes (el archivo tiene 627 líneas).

| Periférico | compatible | Reg base | IRQ (SPI) | Clocks |
|---|---|---|---|---|
| GIC v3 | `arm,gic-v3` | `0x02a00000` (+0x02b00000) | PPI 9 | — |
| IR decoder | `zte,zx296718-irdec` | `0x00111000` | 111 | — |
| AON sysctrl | `zte,zx296718-aon-sysctrl` (syscon) | `0x00116000` | — | — |
| pinctrl IOCFG | `zte,zx296718-iocfg` | `0x00119000` | — | — |
| **UART0** | **`arm,pl011`** | `0x0011f000` | 101 | `osc24m` |
| MMC SD0 | `zte,zx296718-dw-mshc` | `0x01110000` | 15 | `topcrm SD0_AHB/WCLK` |
| MMC SD1 | `zte,zx296718-dw-mshc` | `0x01111000` | 16 | `topcrm SD1_AHB/WCLK` |
| **DMA** | `zte,zx296702-dma` | `0x01460000` | 26 | `osc24m` (32 canales/requests) |
| LSP0 CRM | `zte,zx296718-lsp0crm` | `0x01420000` | — | — |
| **GPIO bank 0** | `zte,zx296718-gpio`,`zte,zx296702-gpio` | `0x0142d000` | 49 | — |
| GPIO bank 1 | `…-gpio` | `0x0142d040` | 50 | — |
| GPIO bank 2 | `…-gpio` | `0x0142d080` | 51 | — |
| GPIO bank 3 | `…-gpio` | `0x0142d0c0` | 52 | — |
| GPIO bank 4 | `…-gpio` | `0x0142d100` | 53 | — |
| GPIO bank 5 | `…-gpio` | `0x0142d140` | 54 | — |
| GPIO bank 6 | `…-gpio` | `0x0142d180` | 55 | — |
| LSP1 CRM | `zte,zx296718-lsp1crm` | `0x01430000` | — | — |
| PWM | `zte,zx296718-pwm` | `0x01439000` | — | `lsp1crm PWM_PCLK/WCLK` |
| VOU + DPC + VGA + HDMI + TVENC | (varios) | `0x01440000` rango 0x10000 | 81/82/86 | `topcrm VOU_*` |
| TOP CRM | `zte,zx296718-topcrm` | `0x01461000` | — | — |
| pinctrl PMM | `zte,zx296718-pmm` | `0x01462000` | — | — |
| sysctrl | `zte,zx296718-sysctrl` (syscon) | `0x01463000` | — | — |
| eMMC | `zte,zx296718-dw-mshc` | `0x01470000` | 23 | `topcrm EMMC_NAND_AHB/EMMC_WCLK` |
| AUDIO CRM | `zte,zx296718-audiocrm` | `0x01480000` | — | — |
| I2S0 | `zte,zx296718-i2s`,`zte,zx296702-i2s` | `0x01482000` | 60 | `audiocrm I2S0_*`, dma 22/23 |
| I2C0 | `zte,zx296718-i2c` | `0x01486000` | 35 | `audiocrm I2C0_WCLK` |
| SPDIF0 | `zte,zx296702-spdif` | `0x01488000` | 33 | `audiocrm SPDIF0_WCLK`, dma 30 |

> El gap entre las direcciones del 296702 (0x09xxx, 0x0Bxxx) y las del 296718 (0x011xxx) sugiere un rediseño de bus. **Es muy posible que el ZX279128S retenga el mapping del 296702** (familia armv7) o adopte el del 296718 (familia armv8). Solo el DTB extraído de NAND lo confirmará.

---

## 5. Análisis driver-por-driver

### 5.1 Clock controller (`drivers/clk/zte/`)

**Estructura:**
- `clk.c` + `clk.h` — librería compartida: PLL ops, audio divider, macros DSL para mux/gate/divider.
- `clk-zx296702.c` — controlador legacy con `CLK_OF_DECLARE` (init temprano via `of_clk_init`). Usa **3 device trees nodes** (`topcrm-clk`, `lsp0crpm-clk`, `lsp1crpm-clk`), cada uno mapeado a una dirección distinta (`0x9800000`, `0x0B000000`, `0x9400000`).
- `clk-zx296718.c` — controlador moderno con `platform_driver` y 4 compatibles (`topcrm`, `lsp0crm`, `lsp1crm`, `audiocrm`).

**PLLs ZX296702:**
```c
pll_a9_config[] = {  // CPU PLL
    { 700,  0x800405d1, 0x04555555 },
    { 800,  0x80040691, 0x04aaaaaa },
    { 900,  0x80040791, 0x04000000 },
    { 1000, 0x80040851, 0x04555555 },
    { 1100, 0x80040911, 0x04aaaaaa },
    { 1200, 0x80040a11, 0x04000000 },
};
```
Cada PLL es una pareja de 32-bit `cfg0/cfg1` aplicada a registros `pll_*_REG`.

**PLLs ZX296718:**
```c
pll_cpu_table[] = {  // 1.31 - 1.6 GHz
    PLL_RATE(1312000000, 0x00103621, 0x04aaaaaa),
    PLL_RATE(1407000000, 0x00103a21, 0x04aaaaaa),
    PLL_RATE(1503000000, 0x00103e21, 0x04aaaaaa),
    PLL_RATE(1600000000, 0x00104221, 0x04aaaaaa),
};
pll_vga_table[] = {  // tablas para VGA pixel clock con resoluciones 800x600..1920x1080
    ... (12 entradas)
};
```
PLLs DDR/audio/etc se declaran como `fixed-clock` en el DTSI (no se reconfiguran en runtime).

**Registros TOP CRM ZX296702:**
```
+0x04 CLK_MUX        - selección padre para muchos clocks
+0x08 CLK_DIV
+0x0c CLK_EN0        - gates
+0x10 CLK_EN1        - gates
+0x68 VOU_LOCAL_CLKEN
+0x70 VOU_LOCAL_CLKSEL
+0x74 VOU_LOCAL_DIV2_SET
+0x8c CLK_MUX1
```

**Registros TOP CRM ZX296718:**
```
0x04..0x28  TOP_CLK_MUX0..MUX9
0x34..0x4c  TOP_CLK_GATE0..GATE6
0x58        TOP_CLK_DIV0
0x80        PLL_CPU_REG
0xa0        PLL_DDR_REG
0xb0        PLL_VGA_REG
```

**LSP0 CRPM (ZX296702):** offsets típicos +0x0c (SDMMC1), +0x10 (SPDIF0), +0x14 (SPDIF0_DIV), +0x18 (I2S0), +0x1c (I2S0_DIV), +0x2c (GPIO).

**LSP1 CRPM (ZX296702):** +0x20 (UART0), +0x24 (UART1), +0x2c (SDMMC0), +0x30 (SPDIF1).

**Cantidad de clocks expuestos al DT:**
- ZX296702: ~180 IDs distribuidos en 3 namespaces (`ZX296702_TOPCLK_END`=87, `ZX296702_LSP0CLK_END`=80, `ZX296702_LSP1CLK_END`=14).
- ZX296718: ~164 IDs en 4 namespaces.

**Sí, hay driver específico de ZX296702.** Es el camino más directo para reciclar en el ZX279128S.

### 5.2 Pinctrl (`drivers/pinctrl/zte/`)

**Estado:** solo existe driver para **ZX296718** (`pinctrl-zx296718.c`), no para ZX296702. El ZX296702 nunca tuvo pinctrl en mainline (presumiblemente bootloader configuraba pinmux).

- **Pines:** 137 pines descritos en `pinctrl-zx296718.c`.
- **Modelo:** dos regiones — **AON** (Always-On, registros bien organizados, 2 bits/pin) + **TOP** (offset/bit/width arbitrario por pin).
- **Compatibles DT:** `"zte,zx296718-pmm"` (TOP pin-controller) + `"zte,zx296718-iocfg"` (auxiliary AON).
- **Función mux ejemplo:** `function = "BGPIO"` para usar un pin como GPIO bank.
- **Reg:** TOP en `0x1462000`, AON IOCFG en `0x119000`.

**Reaprovechabilidad para ZX279128S:** depende crítico de cuántos pines y qué mux soporta. El hardware manual ZX279128S debería listar la pin-list. Si la convención (registro AON con 2 bits/pin + tabla TOP separada) se mantiene, el core (`pinctrl-zx.c` 445 líneas) sirve y solo hay que escribir un nuevo `pinctrl-zx279128s.c` análogo al `pinctrl-zx296718.c` con la tabla específica.

### 5.3 GPIO (`drivers/gpio/gpio-zx.c`)

- **Compatible:** solo `"zte,zx296702-gpio"` (también lo usa el 296718 en la lista de fallback).
- **Banks:** 16 GPIO por bank, IRQ chained.
- **Registros (offset desde reg base del bank):**
```
0x00 ZX_GPIO_DIR    - dirección (1 = output)
0x04 ZX_GPIO_IVE    - interrupt valid edge
0x08 ZX_GPIO_IV     - interrupt vector
0x0C ZX_GPIO_IEP    - interrupt edge polarity
0x10 ZX_GPIO_IEN    - interrupt enable
0x14 ZX_GPIO_DI     - data in
0x18 ZX_GPIO_DO1    - data out (set bit)
0x1C ZX_GPIO_DO0    - data out (clear bit)
0x20 ZX_GPIO_DO     - data out (read-modify-write)
```
- **Reaprovechabilidad ZX279128S:** muy alta. Mismo modelo de Cortex-A9 + bank ZX. Las 7 banks del 296718 confirman que el patrón se repite.

### 5.4 DMA (`drivers/dma/zx_dma.c`)

- **Compatible:** `"zte,zx296702-dma"`. Reusado en el 296718 (mismo IP block).
- **Capacidades:**
  - 32 canales (mapeados a peripherals via `dma-requests`).
  - Modos: scatter-gather, cyclic (audio), memcpy.
  - Burst widths: 8/16/32/64-bit, configurables vía `ZX_DST_BURST_WIDTH/SRC_BURST_WIDTH`.
  - LLI (Linked List Items) en RAM, tamaño 4×PAGE_SIZE.
  - Forced close (`ZX_FORCE_CLOSE`).
- **Registros principales:** ver sección 8 (anexo).
- **Reaprovechabilidad ZX279128S:** alta, asumiendo que el SoC reutiliza el DMA IP (lo más probable dado el linaje).

### 5.5 SMP boot (`arch/arm/mach-zx/platsmp.c`)

- **Compatible:** `"zte,zx296702-smp"` (en `cpus { enable-method = ... }`).
- **Mecanismo:** despierta CPU1 escribiendo en PCU + bus-matrix + sysctrl. Define `cpu_kill` para hotplug.
- **Reaprovechabilidad ZX279128S:** alta — es el patrón estándar Cortex-A9MP-with-PCU. El header-smp + platsmp.c se aplican casi literal.

### 5.6 Power domains (`arch/arm/mach-zx/zx296702-pm-domain.c` y `drivers/soc/zte/`)

- **mach-zx legacy:** 7 dominios duros (NEON0/1, GPU, DECPPU, VOU, R2D, TOP) con offsets fijos (PCU+0x18..0x28).
- **drivers/soc/zte/zx2967_pm_domains.{c,h}:** versión refactorizada genérica para zx2967 con polaridad PWREN/PWRDN configurable. `zx296718_pm_domains.c` instancia los dominios concretos.
- **Reaprovechabilidad ZX279128S:** media. Tendrás que descubrir qué dominios existen (probablemente CPU0/1, GPU si existe, periféricos). Puedes empezar SIN driver de power-domain (todo encendido tras bootloader) y añadirlo después.

### 5.7 Red — **NO existe driver ZX**.

```bash
$ find /tmp/linux-zxic/drivers/net -iname "*zx*" -o -iname "*zte*"
(vacío)
```
**Confirmado: cero código de red.** El switch/PHY/MAC del H3600P es trabajo inédito. Posibles caminos:
1. Datasheet del ZX279128S muestra qué controlador MAC usa (¿stmmac/dwmac? ¿propio?).
2. Buscar en el SDK de OpenWrt-China o RealTek (los switches a menudo se identifican por strings en el bootlog).
3. Sniffar el bootlog del firmware stock: a veces revela "RTL8367/Ralink/Atheros".

### 5.8 NAND — **NO existe driver ZX**.

```bash
$ find /tmp/linux-zxic/drivers/mtd -iname "*zx*" -o -iname "*zte*"
(vacío)
```
**Pero existe `drivers/mtd/nand/raw/denali.c` + `denali_dt.c` genérico** que cubre el controlador Denali NAND IP (el mismo que tu H3600P según la doc). Solo necesitas:
1. Identificar el compatible string esperado (`denali,denali-nand-dt` o similar).
2. Wiring DT con `reg`, `interrupts`, `clocks`.

### 5.9 USB — **NO existe driver ZX**.

```bash
$ find /tmp/linux-zxic/drivers/usb -iname "*zx*" -o -iname "*zte*"
(vacío)
```
Si el USB 3.0 del H3600P es DWC3 (Synopsys), `drivers/usb/dwc3/dwc3-of-simple.c` o `dwc3-pci.c` son la base. Hace falta glue para clocks/resets/PHY.

### 5.10 Otros driver ZX que existen pero probablemente no necesitas

| Driver | Para qué |
|---|---|
| `i2c-zx2967.c` | I2C master del 296718 — útil si necesitas hablar con un PMIC o sensor I2C |
| `pwm-zx.c` | PWM — útil si controlas LEDs/fans con PWM |
| `zx2967_thermal.c` | Sensor térmico on-die |
| `zx2967_wdt.c` | Watchdog — recomendable activar para producción |
| `zx-irdec.c` | Decoder IR NEC — irrelevante para router |
| `zx-reboot.c` | Restart handler — mínimo y reusable |

---

## 6. Cobertura de periféricos del H3600P V9

| Periférico H3600P | Existe driver ZX | Reaprovecha | Notas |
|---|---|---|---|
| **CPU Cortex-A9 dual @ 1 GHz** | ✅ `mach-zx` + `platsmp.c` | Alta | El ZX296702 es A9 single, pero el 0x800200 timer + GIC + L2 son idénticos. |
| **DDR3 512 MB** | (DRAM no requiere driver) | — | Inicializada por bootloader |
| **NAND Denali 256 MB** | ❌ ZX no | ✅ vía `denali_dt.c` mainline | Necesitas binding DT correcto |
| **4× GE PHY interno + RGMII externo + switch** | ❌ | ❌ | Trabajo inédito; pista: bootlog stock |
| **2× UART PL011** | ✅ driver `amba-pl011.c` mainline | Directa | El compat ZX296702 no era PL011, pero el H3600P **sí lo es** (mejor para nosotros) |
| **2× PCIe 2.0** | ❌ | ❌ | Necesita driver de host controller (DesignWare/Synopsys/propio) |
| **USB 3.0 (DWC3)** | ❌ | ✅ vía `dwc3-of-simple.c` mainline | Glue clocks/PHY |
| **I2C** | ✅ `i2c-zx2967.c` (296718) | Media | Compat probable diferente, registros similares |
| **SPI** | ❌ | (genérico spi-pl022 o dw-spi) | Probable Synopsys DW-SPI |
| **GPIO** | ✅ `gpio-zx.c` | Alta | Mismo modelo de bank de 16 |
| **JTAG** | (no requiere driver Linux) | — | |
| **xPON SerDes** | ❌ | (no necesario) | Tienes ONT externo |
| **DMA** | ✅ `zx_dma.c` | Alta | Mismo IP esperado |
| **Clocks (PLLs CPU/DDR/PERI/AUDIO)** | ✅ `clk-zx296702.c` | Alta | Modelo de PLLs reutilizable; tabla cfg0/cfg1 puede necesitar recálculo |
| **Pinctrl** | ⚠️ solo 296718 | Media | Tendrás que escribir `pinctrl-zx279128s.c` con tabla nueva |
| **Power domains** | ✅ mach-zx + soc/zte | Media | Opcional al principio |
| **Watchdog** | ✅ `zx2967_wdt.c` | Media | Compat 296718, registros pueden ser distintos |
| **Thermal** | ✅ `zx2967_thermal.c` | Baja-media | Solo si el sensor on-die es el mismo IP |
| **Reset (restart handler)** | ✅ `zx-reboot.c` | Alta | Solo necesita la dir del sysctrl correcta |
| **SMP** | ✅ `platsmp.c` | Alta | Siempre y cuando el PCU+bus-matrix sigan igual |

**Score:** ~10/19 periféricos cubiertos por código existente, ~5/19 cubiertos por drivers genéricos del kernel (denali, dwc3, pl011, dw-spi), ~4/19 sin cobertura (red, PCIe).

---

## 7. Plan de acción concreto

### 7.1 Fase 0 — recolección previa (lo que falta hacer offline)

1. **Volcar la NAND del H3600P y extraer el DTB del firmware ZTE original.** Sin esto, todo lo demás es especulación. El DTB te dará: direcciones reales, listado completo de periféricos, GPIO pin numbers, switch config.
2. **Capturar el bootlog de U-Boot y kernel original** (UART0/1 a 115200). Buscar strings "zx279128", "denali", "dwc3", "stmmac", "rtl83", "switch" — confirman qué drivers usa el firmware stock.
3. **Datasheet ZX279128S** (la PDF que ya tienes en `ZTE/`) — confirmar listado de PLLs y pin-list.

### 7.2 Fase 1 — fork del kernel con código ZX revivido

Comandos exactos:

```bash
cd /home/ubuntu/Projects/MYSELF/ZTE
./setup_fork.sh v6.6        # crea linux-zxic-fork/ con rama zxic-resurrect-v6.6
```

El script (ver `setup_fork.sh`) hace `git revert` sobre los 18 commits de eliminación, en orden cronológico inverso. Conflictos esperables:

- **`MAINTAINERS`**: bloque ZX se reañade ya borrado de la sección. Manualmente reaplicar.
- **`arch/arm/Kconfig`**: línea `source "arch/arm/mach-zx/Kconfig"` puede chocar si la ordenación cambió.
- **`arch/arm/Kconfig.debug`**: entradas `DEBUG_ZTE_ZX*` para earlyprintk.
- **`arch/arm/Makefile`**: `machine-$(CONFIG_ARCH_ZX) := zx` puede chocar.
- **`arch/arm/boot/dts/Makefile`**: en kernels 6.x se reorganizó por vendor (Makefile separado por vendor). Mover los `zx296702*.dtb` al sitio correcto.
- **`Documentation/devicetree/bindings/serial/pl011.yaml`**: la línea `enum: zte,zx296702-uart` cambió de schema. Adaptar a nuevo formato YAML.
- **`drivers/reset/Kconfig`**: comentario sobre ZX2967 — borrar el revert si choca.

Estimación: 2-4 horas de resolución manual.

### 7.3 Fase 2 — adaptación al ZX279128S

```bash
cd linux-zxic-fork
git checkout -b zx279128s-port

# 1. Crear DTSI del nuevo SoC
cp arch/arm/boot/dts/zx296702.dtsi arch/arm/boot/dts/zx279128s.dtsi
# Editar: añadir CPU#2 (es dual @ 1 GHz vs single @ ?), revisar reg bases con DTB extraído.

# 2. Crear DTS de la placa
cat > arch/arm/boot/dts/zx279128s-h3600p.dts <<EOF
/dts-v1/;
#include "zx279128s.dtsi"
/ {
    model = "ZTE H3600P V9";
    compatible = "zte,h3600p", "zte,zx279128s";
    memory@50000000 { device_type="memory"; reg=<0x50000000 0x20000000>; };
};
EOF

# 3. Añadir compat en el match table del clock driver
# Editar drivers/clk/zte/clk-zx296702.c y añadir:
#   "zte,zx279128s-topcrm-clk", etc.
# Mismo patrón en gpio-zx.c, zx_dma.c.

# 4. Defconfig
cp arch/arm/configs/zx_defconfig arch/arm/configs/zx279128s_defconfig
# Añadir CONFIG_MTD_NAND_DENALI=y, CONFIG_USB_DWC3=y, etc.

# 5. Build
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- O=build zx279128s_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- O=build -j$(nproc)
```

### 7.4 Fase 3 — bring-up incremental

Orden recomendado, por dificultad creciente:

1. **UART** (PL011 + osc) → ver "earlycon" en consola.
2. **GIC + timer** → kernel arranca a init=/bin/sh.
3. **Clocks completos** → todos los bloques tienen relojes.
4. **GPIO + pinctrl** → controlas LEDs.
5. **DMA** → habilitas drivers que dependan.
6. **MMC/eMMC o NAND** → rootfs persistente.
7. **USB DWC3** → puerto USB funcional.
8. **PCIe** → trabajo grande.
9. **Switch + GE PHY** → trabajo grande.

### 7.5 Patches que vas a tener que escribir tú

| Patch | Estimación |
|---|---|
| `dt-bindings: arm: zte: add zx279128s` | 30 min |
| `arm: dts: add zx279128s.dtsi + h3600p.dts` | 1-2 días (con DTB origen como guía) |
| `clk: zte: add zx279128s compat` | 2-4 h |
| `gpio: zte: add zx279128s compat` | 30 min |
| `pinctrl: zte: add zx279128s driver` | 2-5 días (depende de # pines) |
| Switch driver | 5-15 días |
| PCIe host controller (si propio) | 5-15 días |
| `arm: mach-zx: add SOC_ZX279128S Kconfig` | 1 h |

---

## 8. Anexo

### 8.1 Comandos git útiles

```bash
# El commit donde el código todavía vive
git checkout f3a732843acc

# Ver el último estado completo del subsistema
git ls-tree -r f3a732843acc -- arch/arm/mach-zx drivers/clk/zte drivers/pinctrl/zte

# Ver commit de eliminación + autores originales
git log --grep="zte zx\|zx296" --pretty='%h %ai %an %s' -- arch/arm

# Listar todos los archivos jamás tocados con "zx" en el nombre
git log --all --diff-filter=A --name-only --pretty=format: -- "*zx*" | sort -u

# Ver author + co-author de un fichero específico
git log --pretty='%h %an' -- drivers/clk/zte/clk-zx296702.c | sort | uniq -c | sort -rn
```

### 8.2 Paths absolutos de los ficheros más importantes

Worktree con código vivo: **`/tmp/linux-zxic/`**
Copias en este proyecto: **`/home/ubuntu/Projects/MYSELF/ZTE/extracted_files/`**

Top-priority para estudiar primero:

| Fichero | ¿Por qué? |
|---|---|
| `extracted_files/dts/zx296702.dtsi` | Plantilla casi-lista para tu DTSI del ZX279128S |
| `extracted_files/clk/clk-zx296702.c` | PLLs, divisores, clock tree; tu mayor reuse |
| `extracted_files/clk/clk.c` | PLL ops base — necesitas leer esto para entender los flag bits |
| `extracted_files/gpio/gpio-zx.c` | GPIO completo, 290 líneas, plug-and-play |
| `extracted_files/dma/zx_dma.c` | DMA completo, 940 líneas |
| `extracted_files/mach-zx/platsmp.c` | SMP boot — accede a PCU y sysctrl |
| `extracted_files/headers/zx296702-clock.h` | IDs de clock para bindings DT |
| `extracted_files/bindings/zx296702-clk.txt` | Documentación del binding clock |

### 8.3 Snippets clave

**8.3.1 Compatibles que el ZX279128S probablemente reutilizará tal cual:**

```dts
compatible = "zte,zx296702-gpio";       // gpio-zx.c
compatible = "zte,zx296702-dma";        // zx_dma.c  (incluso el 296718 lo usa)
compatible = "zte,zx296702-smp";        // platsmp.c (en cpus { enable-method })
compatible = "zte,zx296702-pcu";        // power-control
compatible = "zte,sysctrl", "syscon";   // restart + clocks tuning
```

**8.3.2 Compatibles que podrían cambiar (recomendado declarar nuevos):**

```dts
compatible = "zte,zx279128s-topcrm-clk", "zte,zx296702-topcrm-clk";  // fallback
compatible = "zte,zx279128s-pinctrl";  // tabla pinmux nueva
compatible = "zte,zx279128s-uart", "arm,pl011";  // mejor solo "arm,pl011" si es PL011 puro
```

**8.3.3 Macros DSL del clock driver — patrón a entender:**

```c
GATE(ZX296702_UART0_WCLK, "uart0_wclk", "lsp_26", CLK_UART0, 0, 0, 0)
//    ID                    name          parent   reg        bit flag gflag
```

**8.3.4 Patrón del DTS para GPIO interrupt:**

```dts
gpio0: gpio@142d000 {
    compatible = "zte,zx296702-gpio";
    reg = <0x142d000 0x40>;        // 9 registros × 4 bytes = 0x24, redondeado
    gpio-controller; #gpio-cells = <2>;
    gpio-ranges = <&pinctrl 0 0 16>;
    interrupts = <GIC_SPI 49 IRQ_TYPE_LEVEL_HIGH>;
    interrupt-controller; #interrupt-cells = <2>;
};
```

### 8.4 Direcciones físicas — comparación rápida ZX296702 vs ZX296718

| Bloque | ZX296702 | ZX296718 |
|---|---|---|
| GIC dist | 0x00801000 | 0x02a00000 |
| Timer/L2 | 0x00800200 / 0x00c00000 | (GIC-v3, no L2 PL310) |
| sysctrl | 0xa0007000 | 0x01463000 |
| TOP CRM | 0x09800000 | 0x01461000 |
| LSP0 CRM | 0x0b000000 | 0x01420000 |
| LSP1 CRM | 0x09400000 | 0x01430000 |
| Audio CRM | (no separate) | 0x01480000 |
| GPIO bank0 | (no en DTSI; 0x9404000? ver bin) | 0x0142d000 |
| UART0 | 0x09405000 | 0x0011f000 |
| MMC0 | 0x09408000 | 0x01110000 |
| DMA | (no en DTSI 296702) | 0x01460000 |

**Hipótesis a verificar con el DTB del H3600P:** el ZX279128S puede heredar el mapping del 296702 (mismo armv7) o haber adoptado el del 296718. La pista de winnt5 indica que **comparte registros con el 296702**, lo cual sugiere que el mapping `0x09400000` / `0x0b000000` / `0x09800000` es el correcto.

### 8.5 Cosas que NO encontré (declaradas explícitamente)

- **ZX279127, ZX279128, ZX279131-3** → cero referencias en cualquier commit del kernel.
- **ZXIC** como string genérico → cero matches en mensaje de commit (todas las referencias son a "ZX" sin "IC").
- **ZX296716, ZX296719** → mencionados solo en la commit message de eliminación de Arnd, sin código.
- **xPON / GPON / EPON drivers** → cero, ni siquiera para el 296718.
- **Switch / GE PHY drivers ZTE** → cero.
- **Forks externos del kernel con ZX vivo posterior a 2021** → no comprobé exhaustivamente repos de Linaro o BSPs de ZTE; tu repo local solo contiene `master`. Recomiendo buscar manualmente:
  - `git.linaro.org` (rama `landing-team-zte` si existió)
  - GitHub: searches por `zx296718` filename recientes
  - openwrt-project / OpenWrt staging
  - SDK público de ZTE (no creo que exista para el ZX279128S, pero conviene confirmar).

---

**Fin del informe.** Total ~13 000 LOC catalogados en `extracted_files/` listos para reutilizar. Próximo paso real: extraer el DTB del firmware stock del H3600P para confirmar las direcciones.
