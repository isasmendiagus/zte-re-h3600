# Bitácora de reverse-engineering — vmlinux ZX279128S

Notas en orden cronológico mientras desarrollo los scripts de extracción de
funciones de driver desde el kernel binario.

> ⚠ **AVISO IMPORTANTE — esta bitácora se hizo sobre el firmware de orca.pet**
>
> Cuando arranqué este RE todavía no tenía mi propio dump (estaba esperando UART).
> Trabajé con el `firmware.bin` de orca.pet (V9.0.0P2_DIGI, H3600P) como referencia
> porque es el mismo SoC (ZX279128S). La metodología, scripts y addresses de tablas
> AES/símbolos son **directamente reutilizables** sobre mi vmlinux de TU device,
> pero las funciones específicas (combine_token, output buffer, etc.) tienen
> **offsets distintos** en V9.0.20P72.
>
> - Paths que mencionan `/ZTE/firmware/` → ahora viven en `/ZTE/orca_pet/firmware/`
> - Mi propio vmlinux (V9.0.20P72) está en `/H3600/extracted/vmlinux.bin` y se
>   re-analizó con los mismos scripts. El proyecto Ghidra de TU device está
>   en `/H3600/ghidra/project/`.
> - Las decompilaciones de TU vmlinux están en `/H3600/ghidra/output/` y los
>   hallazgos específicos (clave AES `H36000e71071c440`) en `/H3600/BITACORA.md`.

**Objetivo original:** dado el kernel del firmware H3600P de orca (Linux 4.1.25 SMP,
GCC 4.9.3 Buildroot, 2022-12-13), extraer las funciones de driver decompiladas
para los periféricos del SoC ZX279128S, de forma automatizada vía Ghidra headless.

---

## Setup base

- Ghidra **12.0.4 PUBLIC** en `/opt/ghidra_12.0.4_PUBLIC/`
- JDK 21 (incluido en el path del lanzador)
- Binario fuente: `/home/ubuntu/Projects/MYSELF/ZTE/firmware/vmlinux.bin`
  (6.65 MiB, descomprimido del gzip dentro del zImage del firmware)
- DTS de referencia: `/home/ubuntu/Projects/MYSELF/ZTE/firmware/extracted.dts`
- Base virtual de carga: **`0xC0008000`**
  - Razón: kernel ARM 32-bit Linux 4.1, `PAGE_OFFSET = 0xC0000000` por defecto
    (CONFIG_VMSPLIT_3G), `TEXT_OFFSET = 0x8000`. La dirección física real
    es `0x40008000` (de `bootm`), pero todo el código de la imagen referencia
    direcciones virtuales tras enable de la MMU.

### Comando de import (ejecutado una vez)

```bash
/opt/ghidra_12.0.4_PUBLIC/support/analyzeHeadless \
    /home/ubuntu/Projects/MYSELF/ZTE/ghidra/project zxic \
    -import /home/ubuntu/Projects/MYSELF/ZTE/firmware/vmlinux.bin \
    -loader BinaryLoader \
    -loader-baseAddr 0xC0008000 \
    -processor ARM:LE:32:v7 \
    -overwrite \
    -max-cpu 12
```

- Tiempo de auto-análisis: **~7 min** con 12 cores (vs ~25 min con default 2).
- Resultado: 15,657 funciones identificadas, 57 con nombre auto-derivado
  (todas thunks). El resto son `FUN_xxxxx`.
- **Heap por defecto: 2 GB** (hardcoded en `support/analyzeHeadless`,
  variable `MAXMEM=2G`). El env var `MAXMEM` se ignora — toca editar el
  script o pasar a `launch.sh` directamente. Para 6.65 MiB es suficiente.

### Re-correr scripts sin re-analizar

Una vez analizado, sucesivos scripts usan el proyecto en disco:

```bash
analyzeHeadless ... -process vmlinux.bin -noanalysis -postScript NAME.py ...
```

`-process` carga el programa ya analizado (rápido, ~5 s), `-noanalysis`
evita re-correr analyzers.

---

## Iteración 1 — script Java (`ExtractCompatibles.java`)

**Idea:** iterar `currentProgram.getListing().getDefinedData()`, filtrar
strings que empiecen por `zte,`, `snps,`, etc., obtener xrefs y decompilar
las funciones que las usan.

### Error 1.1 — `ClassNotFoundException` cargando el script Java

```
ghidra.app.script.GhidraScriptLoadException: The class could not be found.
It must be the public class of the .java file: ExtractCompatibles
```

**Causa probable:** Ghidra compila los scripts Java al vuelo con su propio
classloader (Felix OSGi). Algo en el código (anotaciones, encoding del
archivo, dependencia interna no resuelta) bloqueó la compilación.

**Solución:** abandonar Java, pasar a Python (Jython 2.7).

### Lección 1

> Para scripts headless en Ghidra, **Python (Jython) es siempre más fiable
> que Java**. Java requiere compilación on-the-fly via Felix; Jython solo
> requiere import. Y `# @runtime Jython` viene activo por defecto.

---

## Iteración 2 — script Jython, vía `getDefinedData()`

Reescritura limpia en Python 2.7 (Jython). Misma lógica de iterar
strings definidas + buscar xrefs.

### Resultados

- 35 strings detectadas con prefijos `zte,`/`snps,`/`denali,`/`zxic,`...
- Solo **3 xrefs** detectadas en total
- 1 función decompilada (snps_dwc3_gadget_init wrapper)

### Error 2.1 — strings no inlinadas no aparecen en `getDefinedData()`

**Causa:** en un binario plano, Ghidra solo crea automáticamente strings en
posiciones a las que ya detectó referencia. Como la mayoría de las
compatible strings se acceden desde literal pools (LDR rN, =addr) que
Ghidra no enlazó, las strings no quedan "definidas" y no aparecen en la
iteración.

### Lección 2

> No confiar en `getDefinedData()` para encontrar strings en binarios planos.
> **Hay que escanear memoria a nivel byte directamente.**

---

## Iteración 3 — escaneo de memoria byte a byte

Reescritura con `mem.getBytes()` para volcar todo el bloque de memoria
inicializada a un buffer Python, luego `find()` para buscar prefijos.

### Error 3.1 — Jython 2.7 no expone `bytearray.tostring()`

```
AttributeError: 'bytearray' object has no attribute 'tostring'
```

**Solución intermedia:** intenté `bytes(barr)` y `str(barr)` — ambas
fallaron (Jython los confunde con repr).

### Error 3.2 — `mem.getBytes(addr, bytearray)` rellena ceros

Aunque `getBytes(addr, byte[])` funciona con un Java array,
**Jython no auto-coerciona `bytearray` Python a `byte[]` Java**. La llamada
no falla, pero rellena el buffer con ceros. Diagnóstico: leer en una
posición conocida (e.g., `0xc0584940` que sabíamos contenía
`"zte,zx279128-smp"`) — devolvía `\x00\x00...`.

**Solución correcta:**

```python
from jarray import zeros
jbarr = zeros(sz, 'b')   # crea byte[] real Java
mem.getBytes(b.getStart(), jbarr)
data_str = "".join(chr(x & 0xff) for x in jbarr)
```

El `& 0xff` es crítico: Java byte es signed (-128..127), hay que máscarar
para obtener el byte unsigned 0..255.

### Resultado

- **35 strings detectadas** (✓ todas las del DTS)
- 3 xrefs LE32 totales (sin cambio respecto a iteración 2 — el problema NO
  era la búsqueda de strings sino las xrefs)

### Lección 3

> En Jython 2.7 + APIs de Ghidra, **siempre** crear arrays Java
> explícitamente con `jarray.zeros(N, 'b')` para `byte[]`. Pasar
> `bytearray` Python falla silenciosamente.

---

## Iteración 4 — escaneo de direcciones físicas de periféricos

**Idea:** abandonar las compat strings y buscar las **direcciones físicas
de periféricos** del DTS (0x94000000, 0x9a101000, etc.) como constantes
LE32 en el binario. Cada literal pool con `LDR rN, =0x94000000` está dentro
de una función de driver.

### Resultados

- Solo `uart0=0x94404000` (2 hits) y `pcie=0x10000000` (7 hits) y unos
  pocos más tienen LE32 hits.
- **La mayoría tienen 0 hits** (uart1, lsp0crpm, lsp1crpm, mdio, i2c, ssp,
  tdm, gephy1-3, tm, pp, npp, idm).
- 1 función extraída: `FUN_c001092c` para uart0 — pero es solo la
  inicialización del **earlyprintk** (función trivial de 2 líneas que
  hardcodea la dirección).

### Error 4.1 — direcciones físicas NO aparecen en código

**Causa:** los drivers Linux usan `ioremap()`/`of_iomap()` que toma la
dirección del DT runtime y devuelve un puntero virtual. El driver luego
accede a registros por offset de ese puntero. **La dirección física solo
aparece UNA vez, en el árbol de dispositivos** (que se parsea en runtime).
Por tanto, en el binario kernel **no hay constantes LE32 con esas
direcciones**.

### Lección 4

> Las direcciones físicas de periféricos **no son útiles** como ancla para
> encontrar drivers en un kernel Linux moderno. El único caso donde sí
> aparecen es earlyprintk (mapping fijo de UART antes de que el DT se
> parsee).

---

## Iteración 5 — cadena vía `of_device_id` struct

**Hallazgo clave:** las strings de compat **están inlinadas dentro de
structs `of_device_id`**. La struct de Linux 4.1 es:

```c
struct of_device_id {
    char    name[32];           // offset 0
    char    type[32];           // offset 32
    char    compatible[128];    // offset 64
    const void *data;           // offset 192
};
```

Por tanto, si la string compat está en `S`, **el struct empieza en S-64**.
Y el campo `data` (puntero a `init_fn` en CLK_OF_DECLARE, o NULL/driver_data
en platform_driver) está en `S+128`.

### Verificación experimental

Para `zte,zx279127-topcrm` @ `0xc0660fd4`:

- struct start = `0xc0660f94` (= S-64)
- 1 LE32 ref a `0xc0660f94` → en `0xc05005a0`
- LE32 a struct+192 = `0xc0661054` → contiene `0xc064a254`
- `0xc064a254` ES un function entry → es `zx_topcrm_init()`

¡Bingo!

### Resultados

- **4 funciones críticas decompiladas:**
  - `zte,zx279127-topcrm` → `FUN_c064a254` (clock tree completo)
  - `zte,zx279127-lsp0crpm` → `FUN_c064b740` (Timer0 clocks etc.)
  - `zte,zx279127-lsp1crpm` → `FUN_c064b084` (MDIO clocks etc.)
  - `zxic,tempsensor` → `FUN_c02c7f40`

### Limitación 5.1 — solo encuentra CLK_OF_DECLARE

Para drivers `platform_driver` (UART, I2C, SPIFC, NAND Denali, USB, PCIe,
etc.) el campo `data` del of_device_id es NULL o driver_data, NO un
function pointer. Por tanto el truco "leer S+128 como puntero a función"
no funciona.

### APIs internas inferidas (mismas usadas por los 3 clock-init)

| Función ofuscada | Equivalente kernel |
|---|---|
| `FUN_c02c04a4(np, 0)` | `of_iomap(np, 0)` |
| `FUN_c02c63a4(...)` | `clk_register_fixed_rate(...)` |
| `FUN_c02c61fc(...)` | `clk_register_divider(...)` |
| `FUN_c02c6968(...)` | `clk_register_mux(...)` |
| `FUN_c02c6574(...)` | `clk_register_gate(...)` |
| `FUN_c02c57d4(...)` | `clk_register_divider_table(...)` |
| `software_udf(0x12, ...)` | `panic()` / BUG handler |

### Lección 5

> Linux usa **dos patrones de driver-init muy distintos**:
> - **CLK_OF_DECLARE / OF_DECLARE_*** — boot-time, struct con
>   `{compat_ptr, init_fn}`, registrado en `__clk_of_table[]`. Init function
>   accesible vía data field del of_device_id.
> - **platform_driver** — runtime, struct `platform_driver` con
>   `.driver.of_match_table` apuntando al array de of_device_id, y `.probe`
>   apuntando a la función. Init function NO accesible directamente desde
>   of_device_id.
>
> Para extracción completa, hay que cubrir AMBOS patrones.

---

## Iteración 6 — pase platform_driver (escaneo ±64 bytes desde struct ref)

**Estrategia:** una vez detectada la dirección del array `of_device_id`
(via `struct_start = compat_str_addr - 64`), buscar LE32 refs a esa
dirección. Cada ref está dentro de un `struct device_driver` (envuelto en
`struct platform_driver`, `struct snd_soc_driver`, etc.). El offset entre
el field `of_match_table` y los punteros a función (`probe`, `remove`,
`shutdown`, ...) varía según el tipo de struct, pero siempre está dentro
de ±64 bytes.

Para cada ref R encontrada en pase 2, escaneo:
- Offsets negativos: R−4, R−8, ..., R−76 (típicamente platform_driver
  tiene `.probe` en offset 0 y `.driver.of_match_table` en offset 44 →
  probe en R−44)
- Offsets positivos: R+4, R+8, ..., R+60 (otros struct types)

Para cada valor LE32 encontrado en kernel-virtual range que apunta a un
function entry → decompilar.

### Resultados — ¡salto enorme!

**De 4 → 35 funciones decompiladas, cubriendo 14 drivers distintos:**

| Compat | Refs | Funcs | Más probable identidad |
|---|---|---|---|
| `denali,denali-nand-dt` | 2 | 3 | NAND probe + 2 helpers |
| `rohm,dh2228fv` | 2 | 4 | SPI codec probe/read/write/init |
| `snps,dwc3` | 2 | 3 | DWC3 quirk-parse + 2 más |
| `snps,has-lpm-erratum` | 1 | 2 | dwc3 quirks (mismo func que arriba) |
| `zte,ZX279127-spifc` | 2 | 2 | SPI flash controller (compartido con NAND) |
| `zte,ZX279127-uart` | 2 | 2 | UART probe + remove |
| `zte,zx279127-i2c` | 2 | 4 | I2C probe + read + write + init |
| `zte,zx279127-lsp0crpm` | 1 | 1 | clock init (CLK_OF_DECLARE pase 2) |
| `zte,zx279127-lsp1crpm` | 1 | 1 | clock init |
| `zte,zx279127-ssp` | 2 | 2 | SSP/SPI driver (mismo módulo que rohm) |
| `zte,zx279127-topcrm` | 1 | 1 | **clock tree completo (118 líneas)** |
| `zte,zx279128-dwc3` | 2 | 2 | DWC3 wrapper probe + remove |
| `zte,zx279128-smp` | 2 | 8 | SMP boot + power-down callbacks |
| `zxic,tempsensor` | 4 | 4 | thermal sensor read/init/show/store |

### Problemas restantes / drivers NO recuperados

- `zte,ZX279127-pcie` y `zte,zx279127-pcie` — 0 funcs. Probable causa:
  no usan platform_driver estándar (PCIe host controllers a menudo usan
  `struct dw_pcie` u otra envoltura). Ambos compat strings existen, lo
  cual sugiere registro doble (uno para legacy, otro para el chip).
- `zte,zx279127-dwc2` — 0 funcs. La struct ref existe pero no apunta a
  función válida.
- `snps,dwc2` — 0 funcs. El driver DWC2 mainline parece no estar en este
  build (solo DWC3).
- `zte,iram` — 0 funcs. Es un memory binding (no driver), probablemente
  consumido por SMP boot.
- Los `snps,*_quirk`, `snps,hird-threshold`, etc. — son **propiedades del
  device tree**, no compatibles. El driver real (DWC3) las parsea con
  `of_property_read_*`. Esperado tener 0 refs como struct ref.

### Verificación spot — UART driver

Inspeccionando `FUN_c01dfe8c` (extraído como UART probe):

```c
undefined4 FUN_c01dfe8c(int param_1) {
  int iVar3 = *(int *)(param_1 + 0x68);
  FUN_c01de9c8(DAT_c01dfec8, iVar3);
  ...iterates [DAT_c01dfecc + 0..14], clears matching entries
}
```

Esto **NO es la probe del UART**. Es una función de remove/teardown que
itera un array. El verdadero `_probe()` debe ser `FUN_c01e03fc` (más
larga, llama a `request_mem_region`/`request_irq` patterns) — pero esa
función referencia "usb_serial" string, lo cual sugiere que es del driver
PL011 standard, NO un driver custom ZTE.

Conclusión: en este kernel, **el "compatible" `zte,ZX279127-uart` está
registrado dentro del array of_device_id del driver `amba-pl011` standard
de mainline** (que acepta múltiples compats vendor-specific además del
estándar `arm,pl011`). Por tanto **no hay que escribir driver UART nuevo**:
basta con añadir `zte,ZX279127-uart` al `of_match_table` del pl011 driver
mainline (vía DT bindings update) o usar simplemente `arm,pl011` directamente
en el DTS del port OpenWrt.

### Verificación spot — DWC3 wrapper

`FUN_c027ee60` (struct ref offset = 4, indicando es la 2ª función del
struct → probable `.remove`):

```c
iVar1 = *(int *)(param_1 + 0x68);     // pdev->dev.driver_data → priv
uVar2 = *(undefined4 *)(iVar1 + 4);   // priv->clk[0]
FUN_c02c3d60(uVar2);  // clk_disable_unprepare(clk)
FUN_c02c3d34(uVar2);  // clk_put(clk)
// repeat for priv->clk[1] and priv->clk[2]
FUN_c01ed868(param_1 + 0x10, iVar1);  // devm_kfree o similar
```

Es la **función remove del wrapper DWC3** que libera 3 clocks (que
coinciden con los del DTS: `usb_bus_clk`, `usb_ref_clk0`, `usb_ref_clk1`).
La probe está en `FUN_c027eedc`.

### Verificación spot — Denali NAND

`FUN_c0239afc`:

```c
if (_DAT_c06ae9b0 != 3) {
    panic_print("spi_bootsel != %d", _DAT_c06ae9b0, ...);
    return -EINVAL;
}
puVar2 = devm_kzalloc(dev, 0x638, GFP_KERNEL);  // priv struct of 1592 bytes
*puVar2 = 3;
puVar2[0x17d] = iVar5;  // priv->dev = dev (offset 0x5f4)
iVar1 = platform_get_irq(pdev, 0);
...
```

Es la **probe del wrapper Denali NAND ZTE**. El kernel tiene una
verificación de boot mode (3 = parallel NAND, vs SPI NAND mode). Allocates
1592 bytes para priv data. Le sigue mapping de regs y setup de IRQ.

### Lección 6

> Para platform_driver, **el escaneo ±64 bytes desde el ref a
> of_match_table es muy efectivo**, pero genera falsos positivos: muchos
> de los punteros a función capturados son `.remove`/`.suspend`/`.resume`,
> no `.probe`. La identificación correcta requiere inspección humana.
>
> En estructuras platform_driver, el `.probe` siempre está en offset 0,
> así que `R - of_match_offset` da el probe. Pero `of_match_offset` varía
> (~44 para Linux 4.1) y depende de campos previos en `device_driver`.

---

## Estado final: extracted

- `/home/ubuntu/Projects/MYSELF/ZTE/ghidra/output_chain/`:
  - `INDEX.md` — tabla de todos los compats con funcs decompiladas
  - 35 archivos `.c` con código decompilado por driver
- `/home/ubuntu/Projects/MYSELF/ZTE/ghidra/project/zxic/` — Ghidra
  project persistente, reusable para nuevos scripts sin re-analizar
- `/home/ubuntu/Projects/MYSELF/ZTE/ghidra/scripts/` — los 3 scripts
  funcionales: `extract_compatibles.py`, `extract_drivers.py`,
  `extract_chain.py`

### Archivos más valiosos en el output

1. **`zte_zx279127-topcrm__FUN_c064a254.c`** — clock controller principal,
   PLLs + clocks + dividers + muxes. Base directa para
   `clk-zx279128s.c` mainline.
2. **`zte_zx279127-lsp0crpm__FUN_c064b740.c`** — LSP0 clocks (Timer0).
3. **`zte_zx279127-lsp1crpm__FUN_c064b084.c`** — LSP1 clocks (incluye
   MDIO y PWM clocks).
4. **`denali_denali-nand-dt__FUN_c0239afc.c`** — NAND probe.
5. **`zte_zx279128-dwc3__FUN_c027ee60.c`** + `__FUN_c027eedc.c` —
   DWC3 wrapper (clocks glue layer).
6. **`zte_zx279127-i2c__*.c`** (4 funcs) — I2C controller completo.
7. **`zte_zx279128-smp__*.c`** (8 funcs) — SMP boot, secondary CPU enable.

### APIs internas inferidas (tabla extendida)

| Función ofuscada | Linux equivalent | Notas |
|---|---|---|
| `FUN_c02c04a4` | `of_iomap()` | Map regs from DT |
| `FUN_c02c63a4` | `clk_register_fixed_rate()` | |
| `FUN_c02c61fc` | `clk_register_divider()` | |
| `FUN_c02c6968` | `clk_register_mux()` | |
| `FUN_c02c6574` | `clk_register_gate()` | |
| `FUN_c02c57d4` | `clk_register_divider_table()` | con tabla |
| `FUN_c02c3d60` | `clk_disable_unprepare()` | |
| `FUN_c02c3d34` | `clk_put()` | |
| `FUN_c01ed3bc` | `devm_kzalloc()` | dev, size, gfp |
| `FUN_c01ec070` | `platform_get_irq()` | pdev, idx |
| `FUN_c01ed868` | `devm_kfree()` o release | |
| `FUN_c01e7918` | `dev_err()` o printk | |
| `FUN_c046918c` | `printk()`/`pr_err()` | |
| `software_udf(0x12, ...)` | BUG/panic handler | ARM software undef instruction |

---

## Iteración 7 — DESBLOQUEO TOTAL: orca.pet revela la clave AES

El usuario aportó el writeup de Marcos del Sol Vives (orca.pet/zteh3600p)
que cierra el círculo en 5 minutos:

### La encriptación del rootfs

- **Algoritmo: AES-128-ECB**
- **Clave (hex):** `48333630305039636534666637363466`
- **Clave (ASCII):** `H3600P9ce4ff764f`
- **Localización en firmware.bin:** offset `0x360000` (= bs=2048 × skip=1728),
  longitud `0x1200000` = 18 MiB (= count=9216 × bs=2048)
- **Comando exacto:**

```bash
dd if=firmware.bin bs=2048 skip=1728 count=9216 | \
    openssl enc -d -aes-128-ecb -K 48333630305039636534666637363466 -nopad > rootfs.bin
```

### Verificación

```
file rootfs.bin  →  Linux jffs2 filesystem data little endian
```

✓ Hipótesis previa confirmada: **el rootfs SÍ vive en firmware.bin**, no
en una partición separada de NAND. El bloque de 21 MiB de alta entropía
era exactamente esto, AES-128-ECB cifrado.

### Extracción

```bash
pip install --user jefferson
~/.local/bin/jefferson -d rootfs/ rootfs.bin
```

Estructura típica Linux: `/bin /etc /lib /sbin /usr /home /var ...` +
`/kmodule` (custom ZTE) + `/lib/modules/4.1.25/` (estándar).

### Lección 7 — el atajo definitivo

> **Antes de meterse en RE pesado, busca prior art.** Marcos del Sol Vives
> hizo esto en 2024. Su clave AES (descubierta vía RE de la función
> `combine_token` en el kernel) ahorra semanas de trabajo. El thread de
> XYUU también ayudaba pero su firmware era un build distinto (H3-2S sin
> AES en rootfs). orca.pet es específico para H3600P P5_DIGI con AES.
>
> Habría sido mejor leer estos 3 sources ANTES de empezar el RE de
> bootloader.

### Otras revelaciones de orca.pet aplicables aquí

1. **El kernel ELF con símbolos** está disponible en orca.pet/zteh3600p
   (descarga directa). Si lo importamos a Ghidra, los `FUN_xxxx` se
   convierten en nombres reales. **TO-DO: descargar y re-importar.**
2. **WiFi: MediaTek MT7916 vía PCIe** (PCI IDs `14c3:7906`, `14c3:790a`).
   Driver mainline `mt76` lo cubre **completamente**. Cero RE necesario.
3. **Mapeo iomap estático del kernel** (visible en bootlog tras
   `earlyprintk` activado):
   ```
   0x94000000 → 0xf0400000  (TOPCRM)
   0x94100000 → 0xf0500000  (temp sensor)
   0x94400000 → 0xf0700000  (LSP0CRPM)
   0x9a100000 → 0xf0800000  (LSP1CRPM/MDIO/I2C)
   0x00d00000 → 0xf0900000  (NAND reg)
   0x92000000 → 0xf4000000  (PON)
   0x09100000 → 0xf0b00000  (USB3 dwc3)
   ```
   → Mi escaneo previo de direcciones físicas en vmlinux falló porque
   la kernel usa estas direcciones VIRTUALES (0xfXXXXXXX), no las
   físicas. Para futuros pases, usar las virtuales.
4. **Particiones reales (post-extracción):**
   - mtdblock0: bootloader
   - mtdblock1: tag (datos por dispositivo, MAC, serial, passwords WiFi)
   - mtdblock2: wifi calib
   - mtdblock3: usercfg (rw)
   - mtdblock4: defcfg (ro)
   - mtdblock5: kernel1
   - mtdblock6: kernel2 (backup)
   - mtdblock7: rootfs (jffs2 ro)
   - mtdblock8: rootfs (per `root=/dev/mtdblock8 ro rootfstype=jffs2`)

---

## Iteración 8 — análisis de los .ko reales

Tras la extracción, los `.ko` de los drivers críticos están en
`/home/ubuntu/Projects/MYSELF/ZTE/firmware/rootfs/kmodule/`. **Ninguno
está strippeado** — TODOS los símbolos de funciones están preservados.

### Inventario de .ko críticos

| Archivo | Tamaño | Symbols | Descripción inferida |
|---|---|---|---|
| `switch.ko` | 200 KiB | 467 | Switch driver (MAC + VLAN + ACL + IGMP snoop) |
| `tm.ko` | 1.2 MiB | 3048 | Traffic Manager (QoS scheduler) — el más grande |
| `plat-zxylzb_9128S.ko` | 140 KiB | 599 | Platform: MDIO/GEPHY/PP/NPP/PCIe glue |
| `bspdriver.ko` | 13 KiB | 93 | BSP: GPIO/pinctrl/early init |
| `idmfdb.ko` | 35 KiB | 106 | IDM forwarding database |
| `tdm.ko` | 35 KiB | 86 | TDM audio |
| `dsp_dev.ko` | 160 KiB | 358 | DSP (voice) |
| `voip_codec.ko` | 215 KiB | 530 | VoIP codec |
| `kudp.ko` | 16 KiB | 78 | Kernel UDP helper |
| `usrline.ko` | 175 KiB | 364 | POTS user line |
| `zx_ponreg.ko` | 5 KiB | 24 | PON registers helper |

### Confirmación de no-stripping

```bash
$ readelf -s switch.ko | head -40
... 467 entries with FUNC type and full names ...

Examples:
  sw_acl_setMtchInfo
  sw_bridge_event
  sw_port_alarm_kthread
  sw_set_trap_cpu_ip
  sw_reg_set_writereg
  sw_vlan_get_port_*
  sw_mac_set_port_*
  sw_igmp_mulrule_deal
  ...
```

✓ Trabajo de RE multiplicado por 100 — pasamos de `FUN_c02ab123` a
`sw_vlan_set_port_pvid` directamente. Ghidra nos da código semántico
casi-source.

### Plan ajustado

1. **Importar los .ko críticos** en Ghidra (formato ELF, NO binary):
   - switch.ko, plat-zxylzb_9128S.ko, bspdriver.ko, tm.ko (largo)
   - Cada uno como proyecto separado o sección distinta
   - Como son ELF relocatable Ghidra detecta secciones, símbolos y
     reubicaciones automáticamente. **No hace falta especificar base
     address** ni adivinar.
2. **Decompilar funciones por nombre semántico** (no por scan brute):
   - `*_init`, `*_probe` → drivers init
   - `mdio_*`, `phy_*` → PHY interface
   - `sw_*_init`, `sw_*_register` → switch register sequence
3. **Mapear cada compatible del DTS a su driver real:**
   - `zte,zx279128s-mdio` → buscar en `plat-zxylzb_9128S.ko`
   - `zte,zx279128s-pp/npp/tm/idm` → en `switch.ko`/`tm.ko`/`plat-...ko`
   - `zte,zx279128s-gephy` → en `plat-zxylzb_9128S.ko` o `switch.ko`
   - `zte,zx279128s-pon` → en `zx_ponreg.ko`/`plat-...ko`

---

## Próximos pasos

1. **Importar los .ko clave** en Ghidra headless con `-loader ElfLoader`
   (auto-detecta arch + base + secciones, no hay que adivinar nada).
2. **Re-correr `extract_chain.py` adaptado** para iterar funciones
   nombradas en vez de strings compat.
3. **Empezar a escribir drivers mainline** con los nombres reales:
   - `clk-zx279128s.c` ya casi listo (de iteración 5)
   - `mdio-zx279128s.c` desde `plat-zxylzb_9128S.ko::mdio_*`
   - `gephy-zx279128s.c` (PHY driver) desde `plat-...ko::*phy_*`
   - DSA-style switch driver desde `switch.ko`
4. **Descargar y comparar** con el ELF kernel con símbolos de orca.pet
   para validar nuestros findings.
