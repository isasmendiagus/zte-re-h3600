# NAND Layout & Boot Flow — ZTE H3600 (ZX279128S)

Este doc resume **todo lo aprendido** del NAND, U-Boot ZTE custom (`cspstart`),
estructura de los slots A/B, CRCs, y cómo logramos persistir nuestro kernel
mainline en NAND para que bootee automáticamente sin TFTP.

---

## Hardware NAND

- **Chip**: ESMT F50L1G41LB (SPI NAND, 128 MiB)
- **Page size**: 2 KiB típico
- **Erase block**: 128 KiB típico
- **Acceso desde Linux**: `/dev/mtdN` (raw + IOCTL erase) y `/dev/mtdblockN` (FS-able)

## Layout NAND completo

```
  0x00000000  ┌───────────────────────────────────────────┐
              │  mtd1: BOOTLOADER (1 MiB)                 │
              │  ├─ 0x000000-0x000800: ZTE pre-header     │
              │  ├─ 0x000800-0x0bffff: U-Boot text/data   │ ← NEVER touch (BRICK)
              │  ├─ 0x0c0000-0x0dffff: U-Boot env (128K)  │ ← saveenv (CRC32 auto)
              │  └─ 0x0e0000-0x0fffff: env backup         │
  0x00100000  ├───────────────────────────────────────────┤
              │  mtd2: TAG (1 MiB)                        │
              │  └─ MACs, serial, admin pwd, WiFi creds   │
  0x00200000  ├───────────────────────────────────────────┤
              │  mtd3: WIFI cal (MT7915 EEPROM data)      │
  0x00300000  ├───────────────────────────────────────────┤
              │  mtd4: usercfg (2 MiB)                    │
  0x00500000  ├───────────────────────────────────────────┤
              │  mtd5: defcfg (2 MiB)                     │
  0x00700000  ╞═══════════════════════════════════════════╡
              │ ★ KERNEL SLOT A (was 3.4 MiB stock)       │
              │   AHORA: nuestro mainline 6.6             │
              │   ├─ +0x00: 32-byte ZTE wrapper magic     │
              │   ├─ +0x20: uImage header                 │
              │   └─ +0x40: zImage + DTB appended         │
              │   USABLE: 0x700000 - 0x2000000 (25 MiB)   │
  0x02000000  ├───────────────────────────────────────────┤
              │   GAP (512 KiB) — para no chocar header   │
  0x02080000  ├═══════════════════════════════════════════┤
              │ ★ HEADER A (1 erase block = 128 KiB)      │
              │   Estructura BootPara (ver más abajo)     │
  0x02100000  ├───────────────────────────────────────────┤
              │   gap libre 6 MiB                         │
  0x02700000  ├═══════════════════════════════════════════┤
              │   KERNEL SLOT B (3.4 MiB stock)           │ ← INTACTO = recovery A/B
  0x02a60000  ├───────────────────────────────────────────┤
              │   ROOTFS B (22 MiB stock jffs2)           │ ← INTACTO
  0x04080000  ├───────────────────────────────────────────┤
              │   HEADER B (128 KiB)                      │ ← INTACTO
  0x04100000  ├───────────────────────────────────────────┤
              │   FREE 63 MiB sin usar                    │
  0x08000000  └───────────────────────────────────────────┘  FIN
```

## Estructura del header A (BootPara) — RE'd

Header partition de 128 KiB con primeros 0xa8 bytes con la estructura BootPara.
Cuando se cambia algún campo, hay que recalcular el CRC32 zlib en offset 0xa4.

```
Offset  Size  Campo                       Valor stock        Notas
─────────────────────────────────────────────────────────────────────────
0x00    8     padding/zero                0
0x08    4     ?                           0x00000266         tamaño? versión?
0x0c    4     ?                           0x00000008         flag
0x10    16    Versión ASCII string        "V9.0.0P4_DIGI"    16 bytes con \0
0x20    12    padding                     0
0x2c    4     image counter               1
0x30    4     ?                           0x01980000
0x34    4     KERNEL_SIZE                 0x0035fdcc      ★ MODIFICAR si crece kernel
0x38    4     ?                           0x00000234
0x3c    4     KERNEL csp_crc              0x2fedcd6d      ★ MODIFICAR si cambia kernel
0x40    4     ROOTFS_SIZE                 0x01620000
0x44    4     ?                           0x00360214
0x48    4     ROOTFS csp_crc              0xcad40158      ★ MODIFICAR si cambia rootfs
0x4c    4     KERNEL_OFFSET A             0x00700000
0x50    4     ?                           0x02000000
0x54    8     padding                     0
0x5c    4     KERNEL_OFFSET B             0x02700000
0x60    16    ?                           varios
0x70    24    Board name                  " H1600V9\0..."
0x88    16    padding
0x98    4     flag                        1
0x9c    4     flag                        1
0xa0    4     ?                           0x76 26 cd 20      timestamp/build
0xa4    4     ★ HEADER CRC32 (zlib)       AUTO-RECALCULADO
0xa8+   ...   padding 0x00
0xf4    16    Magic 33333333 66666666 99999999 cccccccc
              (otro magic, no el de búsqueda de search_firmware)
```

Nota: `csp_crc` es **distinto a zlib's CRC32**. Algoritmo no identificado (es ZTE-custom).
Usamos el truco de leerlo del log cuando falla: `Real crc XXXXXXXX` printa el valor real.

## Boot flow paso a paso

```
   POWER-ON
       ↓
   ┌─────────────────────────────────────────────────────────────┐
   │ 1. SoC boot ROM lee mtd1 offset 0x800 → carga U-Boot a RAM  │
   │    "Boot SPI NAND / start read bootheader / non secure boot"│
   └─────────────────────────────────────────────────────────────┘
       ↓
   ┌─────────────────────────────────────────────────────────────┐
   │ 2. U-Boot init: clocks, DDR, GPIO, ETH, USB clock-gate      │
   │    "addr 0x9400004c after value is 381ff"                   │
   │    Bits 0-8 = DWC2 USB clock; bits 9-14 = DWC3 USB clock    │
   └─────────────────────────────────────────────────────────────┘
       ↓
   ┌─────────────────────────────────────────────────────────────┐
   │ 3. "Press 1 ... bootmode password"  (5s timeout)            │
   │    Si tipeás 1 + Boot4128s! → entrás a U-Boot prompt =>     │
   │    Si NO → countdown "3 2 1 0" → cspstart auto              │
   └─────────────────────────────────────────────────────────────┘
       ↓
   ┌─────────────────────────────────────────────────────────────┐
   │ 4. cspstart (custom ZTE) — flow:                            │
   │    a. zteboot_search_firmware: scan NAND for magic          │
   │       33333333 cccccccc 88888888 dddddddd                   │
   │       → encuentra header A (0x2080000) y B (0x4080000)      │
   │    b. update_bootpara: lee BootPara struct                  │
   │       fs_start = kernel_offset + kernel_size                │
   │    c. verify_kernel: CSP_CRC del kernel completo vs         │
   │       campo CRC del header (offset 0x3c)                    │
   │    d. verify_fs: CSP_CRC del rootfs vs campo CRC (0x48)     │
   │    e. select firmware: serial0/serial1 (ambos 3 → slot 0)   │
   │    f. carga kernel a 0x42020000, "bootm 0x42020020"         │
   │       (los +0x20 saltan el wrapper ZTE de 32 bytes)         │
   └─────────────────────────────────────────────────────────────┘
       ↓
   ┌─────────────────────────────────────────────────────────────┐
   │ 5. bootm (U-Boot std):                                      │
   │    - Lee uImage header en 0x42020020                        │
   │    - Verifying Checksum (CRC32 estándar uImage)             │
   │    - Loading Kernel Image → 0x40008000 (load addr)          │
   │    - Starting kernel → jump 0x40008000                      │
   └─────────────────────────────────────────────────────────────┘
       ↓
   ┌─────────────────────────────────────────────────────────────┐
   │ 6. zImage decompresor → kernel real → init                  │
   │    "Booting Linux on physical CPU 0x0"                      │
   │    "OF: fdt: Machine model: ZTE H3600 (ZX279128S)"          │
   └─────────────────────────────────────────────────────────────┘
```

## RAM layout (256 MiB DDR @ 0x40000000)

```
  0x40000000  ┌─────────────────────────────────────┐
              │  Vectors / very early ZTE asm       │
  0x40007000  ├─────────────────────────────────────┤
              │  cspstart "save bootpara" struct    │ ← passes info to kernel
              │  (0x554 bytes)                      │
  0x40008000  ├─────────────────────────────────────┤
              │  Kernel uncompressed (load addr)    │
              │  Linux runs here                    │
  0x42000000  ├─────────────────────────────────────┤
              │  Scratch / tftp / nand read target  │
              │  CONFIG_SYS_LOAD_ADDR + SZ_16M      │
  0x42020000  ├─────────────────────────────────────┤
              │  Donde cspstart carga kernel image  │
              │  +0x20 = uImage start (post-wrapper)│
  0x4FFFFFFF  └─────────────────────────────────────┘  FIN 256 MiB
```

## CRCs en el sistema (3 distintos)

| # | CRC | Stored | Algoritmo | Manejo |
|---|---|---|---|---|
| 1 | U-Boot env | mtd1 +0xc0000 | zlib CRC32 | AUTO via `saveenv`/`fw_setenv` |
| 2 | uImage | dentro del uImage header | zlib CRC32 | AUTO via `mkimage` |
| 3 | csp_crc kernel | header A offset 0x3c | **CRC32 IEEE estándar** (= `zlib.crc32`) — RE'd 2026-05-03 | Pre-calcular local con `zlib.crc32(uImage_proper + 0xff_padding)` |
| 3 | csp_crc rootfs | header A offset 0x48 | **CRC32 IEEE estándar** | Pre-calcular local con `zlib.crc32(rootfs_data)` |
| 4 | Header BootPara | header A offset 0xa4 | zlib CRC32 | Recalcular con `python zlib.crc32` |

**Update 2026-05-03**: csp_crc identificado = **CRC32 IEEE estándar** (zlib).
El truco era que csp_crc opera sobre el uImage proper (sin los 32 bytes del
wrapper ZTE) para el kernel, y sobre el rootfs raw para fs. Tabla precalculada
en U-Boot file offset `0x51e60` (256 entries, off-by-1 vs std).

**Pre-cálculo local** (sin iterar):
```python
import zlib
# Kernel: skip 32-byte wrapper, pad with 0xff to kernel_size
crc_kernel = zlib.crc32(uimg_data + b'\xff' * (kernel_size - len(uimg_data)))
# Rootfs: ubica en fs_start..fs_start+rootfs_size (post-erase = 0xff)
crc_rootfs = zlib.crc32(b'\xff' * rootfs_size)
```

## Comandos U-Boot custom ZTE

| Comando | Función |
|---|---|
| `cspboot` | Init del subsistema cspboot (corre auto en boot) |
| `cspnand` | NAND sub-system (interno) |
| `cspstart` | Inicia kernel boot — search + verify + bootm |
| `cspnor` | NOR sub-system (no aplica a este chip) |
| `bootk` | "Boot kernel" (alias) |
| `nand read/write/erase` | Estándar U-Boot |
| `tftp` | TFTP estándar (necesita `setenv ipaddr/serverip`) |
| `printenv/setenv/saveenv` | Estándar U-Boot env |

## Recovery escenarios

| Si rompemos | Qué hacer |
|---|---|
| Slot A (kernel mainline) | cspstart fallback automático → slot B (stock) |
| Slot A + slot B | Entrar U-Boot prompt → tftp `h3600_nand_full.bin` → restaurar particiones via `nand erase + nand write` |
| U-Boot env (mtd1 0xc0000) | `printenv` para ver, `setenv versioninfo "..."` + `saveenv` para restaurar |
| U-Boot binary (mtd1 0..0xc0000) | **BRICK total**, requiere SPI flasher externo (CH341 + clip SOIC8) → **NUNCA TOCAMOS esa zona** |

## Backups disponibles localmente

- `/home/ubuntu/Projects/MYSELF/ZTE/H3600/h3600_nand_full.bin` — dump completo 128 MiB
- `/home/ubuntu/Projects/MYSELF/ZTE/H3600/partitions/0[1-8]_*.bin` — particiones individuales
- SHA256 verified, dumps idénticos en 2 corridas → NAND estable

## Lecciones clave

1. **`versioninfo` env var es solo display** — NO controla qué slot se bootea. cspstart escanea NAND completa por magic headers.
2. **A/B selection** está controlado por `serial0`/`serial1` counters dentro del versioninfo block (offset dentro del kernel slot, no del header). Stock H3600 tiene ambos = 3 → siempre boota slot 0.
3. **U-Boot `bootcmd` no boota nada por sí solo** — solo setea bootargs. El boot real lo hace cspstart.
4. **`autorun` env var falla con "Unknown command"** — no es hook utilizable, fue red herring.
5. **El bootloader busca 2 headers válidos** y construye una BootPara struct para cada uno. Si solo encuentra 1, bootea ese.
6. **`fs_start` no debe overlap con header position** — cspstart valida esto y rechaza el slot si choca.
7. **csp_crc es algoritmo custom**, NO zlib CRC32 — pero el log nos da el "Real crc" calculado, evitando RE.
