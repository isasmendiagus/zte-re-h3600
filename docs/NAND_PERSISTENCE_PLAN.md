# NAND Persistence Playbook — Flashear mainline en slot A

Este documento es el **playbook ejecutable** para flashear nuestro kernel
mainline en NAND y que arranque automáticamente sin TFTP.

> **Pre-requisito**: leer `NAND_LAYOUT_AND_BOOT.md` para entender el layout.

## Status: ✓ FUNCIONANDO

Modem boot automático: cspstart → slot A → mainline 6.6. Recovery vía slot B
(intacto stock) si algo rompe.

## Archivos producidos

```
tftp/slotA.bin                  ← 11 MiB: 32-byte ZTE wrapper + zImage_dtb.uimg
tftp/header_A_modified.bin      ← 128 KiB: BootPara con kernel_size=0x1900000 +
                                  CRCs de kernel + rootfs actualizados
```

Ambos archivos servidos por TFTP local en `/home/ubuntu/Projects/MYSELF/ZTE/H3600/tftp/`.

## Setup network

- **Host (compu)**: `192.168.1.50` en interfaz USB-Ethernet (`enxc8a362e95900` en este host)
- **Modem**: `192.168.1.1` (default U-Boot ZTE)
- **TFTP server**: ya corriendo en host (`in.tftpd -L --create --secure /home/.../tftp`)

## Procedimiento paso a paso

### 1. Cuando tenés que reflashear kernel (rebuild zImage)

```sh
# En host (linux), desde repo del kernel:
cd ~/Projects/MYSELF/ZTE/H3600/linux-v6.6
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- O=../build zImage dtbs -j8

# Generar uImage y wrapper ZTE
cd ~/Projects/MYSELF/ZTE/H3600
cd build/arch/arm/boot
cat zImage dts/zte/zx279128s-h3600.dtb > ../../../../tftp/zImage_dtb.bin
mkimage -A arm -O linux -T kernel -C none \
  -a 0x42000000 -e 0x42000040 \
  -d ../../../../tftp/zImage_dtb.bin \
  ../../../../tftp/zImage_dtb.uimg

# Aplicar wrapper ZTE (32 bytes magic) → slotA.bin
cd ~/Projects/MYSELF/ZTE/H3600
python3 -c "
WRAPPER = b'\\x33\\x33\\x33\\x33\\xcc\\xcc\\xcc\\xcc\\x88\\x88\\x88\\x88\\xdd\\xdd\\xdd\\xdd' + b'\\xff' * 16
uimg = open('tftp/zImage_dtb.uimg','rb').read()
open('tftp/slotA.bin','wb').write(WRAPPER + uimg)
print(f'slotA.bin: {len(WRAPPER) + len(uimg):#x} bytes')
"
```

### 2. Flashear el kernel (slot A)

```sh
# Lanza el script orchestrador, después power-cycle el modem
cd ~/Projects/MYSELF/ZTE/H3600
python3 flash_mainline.py
```

El script hace todo: wait U-Boot → tftp slotA + header → nand erase + write → reset.

### 3. Si solo cambiaste el kernel (no el header)

```sh
# Solo flash el kernel, no toca header (más rápido)
python3 flash_kernel_only.py     # (script no creado todavía, ver flash_mainline.py)
```

### 4. Si crece el kernel (cambia su CRC csp_crc)

**¡SOLVED! csp_crc = `zlib.crc32` ESTÁNDAR** — confirmado 2026-05-03 mediante RE.

**Algoritmo csp_crc (descubierto)**:
- ZTE custom function pero usa **CRC32 IEEE estándar** (mismo que `zlib.crc32` / Ethernet / PNG)
- Tabla precalculada en U-Boot binary file offset `0x51e60` (256 entries)
- Devuelve par `(crc, ~crc)` — el log muestra `crc=<calc>, <complement>` (ambos son derivados, no diferentes algos)
- **Importante**: csp_crc opera sobre el **uImage proper**, NO incluye los 32 bytes del wrapper ZTE

**Cómo pre-calcular CRCs sin iterar boot**:

```python
import zlib, struct

# 1. Kernel CRC: csp_crc reads from data_addr=slot+0x20 (skip ZTE wrapper)
#    for crc_len = kernel_size from header (offset 0x34)
slotA = open('tftp/slotA.bin','rb').read()
real_uimg = slotA[32:]                          # skip 32-byte wrapper
kernel_size_in_header = 0x1900000               # value we put at hdr offset 0x34
# After NAND erase + write, area beyond our data is 0xff
crc_region = real_uimg + b'\xff' * (kernel_size_in_header - len(real_uimg))
new_kernel_crc = zlib.crc32(crc_region) & 0xFFFFFFFF

# 2. Rootfs CRC: csp_crc reads from fs_start (= kernel_offset + kernel_size_header)
#    for rootfs_size bytes (header offset 0x40, default 0x1620000)
fs_data = b'\xff' * 0x1620000  # all erased after our nand erase
new_rootfs_crc = zlib.crc32(fs_data) & 0xFFFFFFFF

# 3. Build header
NAND = open('h3600_nand_full.bin','rb').read()
hdr = bytearray(NAND[0x2080000:0x2080000+0x20000])
hdr[0x34:0x38] = struct.pack('<I', kernel_size_in_header)
hdr[0x3c:0x40] = struct.pack('<I', new_kernel_crc)
hdr[0x48:0x4c] = struct.pack('<I', new_rootfs_crc)
hdr[0xa4:0xa8] = struct.pack('<I', zlib.crc32(bytes(hdr[:0xa4])) & 0xFFFFFFFF)
open('tftp/header_A_modified.bin','wb').write(bytes(hdr))
```

Con esto, **flashear es 1 sola pasada** sin necesidad de iterar.

### 4b. Workflow alternativo iterativo (si por algún motivo el cálculo local diverge)

```sh
# Paso 1: flashear el kernel nuevo (header viejo seguirá apuntando al CRC viejo)
python3 flash_mainline.py
# → boot va a fallar con "Kernel CRC check failed. Real crc XXXXXXXX, Want YYYYYYYY"

# Paso 2: leer el "Real crc XXXXXXXX" del log y actualizar header:
python3 -c "
import struct, zlib
NEW_KERNEL_CRC = 0xXXXXXXXX  # ← copiar del log
NEW_ROOTFS_CRC = 0xYYYYYYYY  # ← copiar del log si también falla rootfs

d = open('h3600_nand_full.bin','rb').read()
hdr = bytearray(d[0x2080000:0x2080000+0x20000])
hdr[0x34:0x38] = struct.pack('<I', 0x1900000)         # kernel_size (gap pre-header)
hdr[0x3c:0x40] = struct.pack('<I', NEW_KERNEL_CRC)    # csp_crc kernel
hdr[0x48:0x4c] = struct.pack('<I', NEW_ROOTFS_CRC)    # csp_crc rootfs
hdr[0xa4:0xa8] = struct.pack('<I', zlib.crc32(bytes(hdr[:0xa4])) & 0xffffffff)
open('tftp/header_A_modified.bin','wb').write(bytes(hdr))
"

# Paso 3: re-flash solo el header
python3 flash_header_only.py
```

## Comandos U-Boot manuales (alternativa a los scripts)

Si querés hacerlo paso a paso desde el prompt `=>`:

```
=> setenv ipaddr 192.168.1.1
=> setenv serverip 192.168.1.50

# Kernel mainline
=> tftp 0x42000000 slotA.bin
=> nand erase 0x700000 0x1980000        # erase 25 MiB del slot A area
=> nand write 0x42000000 0x700000 0xb00000   # write 11 MiB

# Header A modificado
=> tftp 0x42000000 header_A_modified.bin
=> nand erase 0x2080000 0x20000          # erase 1 erase block (128K)
=> nand write 0x42000000 0x2080000 0x20000

# Limpiar env (opcional, solo si tocaste autorun u otra var de test)
=> setenv autorun ""
=> saveenv

# Reset
=> reset
```

## Validación post-boot

Después del reset, deberías ver en UART:

```
cspboot:1300 Booting image ...... 
zteboot_search_firmware:48 searching the whole image...
zteboot_verify_header:334 found version
zteboot_search_firmware:85 correct header has been found @2080000
zteboot_search_firmware:85 correct header has been found @4080000
...
pdt_getreal_kernelfs:529 verify_kernel readflash @0x700000 size:0x1900000
csp_crc:103  >>csp_crc, ...
zteboot_verify_kernel:175 verify kernel success!!         ← ✓
zteboot_verify_fs:242 verify fs success!!                 ← ✓
zteboot_do_settings:378 >>s=256M, select=0                 ← slot A elegido
## Booting kernel from Legacy Image at 42020020 ...
   Verifying Checksum ... OK
   Loading Kernel Image ... OK
   Starting kernel ...

[    0.000000] Booting Linux on physical CPU 0x0
[    0.000000] OF: fdt: Machine model: ZTE H3600 (ZX279128S) — first boot
```

Si ves `Machine model: ZTE H3600` ✓ → mainline funcionando.

Si ves `select=1` (slot B) → el slot A fue rechazado, ver troubleshooting.

## Troubleshooting

### `Kernel CRC check failed. Real crc XXXX, Want YYYY`
Cambió el contenido del kernel pero el header tiene CRC viejo. Solución:
update header offset 0x3c con `XXXX` y reflashear header.

### `Romfs CRC check failed. Real crc XXXX, Want YYYY`
Mismo problema con el rootfs (que en realidad son bytes 0xff "erased"). Solución:
update header offset 0x48 con `XXXX` y reflashear header.

### `select=1` (boot slot B en lugar de A) sin error CRC visible
El slot A fue rechazado por algún check posterior. Posibles causas:
- `fs_start` overlap con header_A (offset 0x2080000) → bajar `kernel_size` para dejar gap
- Magic header del kernel (32 bytes inicio del kernel partition) corrupto

### Modem no bootea ningún slot (cspstart find 0 headers)
- Slot A magic corrupto → `nand erase 0x700000 ...` y reflashear
- Slot B también corrupto → recovery via TFTP de `h3600_nand_full.bin` desde U-Boot prompt:
  ```
  => tftp 0x42000000 partitions/06_kernel1.bin
  => nand erase 0x700000 0x360000
  => nand write 0x42000000 0x700000 0x360000
  => tftp 0x42000000 partitions/02_tag.bin
  => nand erase 0x2080000 0x20000
  ... (restaurar otras particiones según necesidad)
  ```

### U-Boot no arranca (no hay output, modem dead)
**BRICK** — necesitás SPI flasher externo (CH341 + clip SOIC8) para reflashear
mtd1 desde el chip directamente. **POR ESO NUNCA TOCAMOS U-Boot binary**.

## Recovery completo

Si querés volver al firmware stock 100%:

```sh
# Desde U-Boot prompt:
=> setenv ipaddr 192.168.1.1
=> setenv serverip 192.168.1.50
=> tftp 0x42000000 partitions/02_tag.bin
=> nand erase 0x100000 0x100000
=> nand write 0x42000000 0x100000 0x100000

=> tftp 0x42000000 partitions/06_kernel1.bin
=> nand erase 0x700000 0x360000
=> nand write 0x42000000 0x700000 0x360000

=> tftp 0x42000000 partitions/07_rootfs.bin
=> nand erase 0xa60000 0x1620000
=> nand write 0x42000000 0xa60000 0x1620000

# Restaurar header A original
=> python (en host) → restore header_A_original.bin desde h3600_nand_full.bin offset 0x2080000
=> tftp 0x42000000 header_A_original.bin
=> nand erase 0x2080000 0x20000
=> nand write 0x42000000 0x2080000 0x20000

=> reset
```

## Ventajas del setup actual

✅ **Boot 100% automático**: cspstart elige slot A → mainline sin tocar nada.
✅ **Recovery integrado**: slot B intacto, fallback automático si slot A se corrompe.
✅ **U-Boot intacto**: nunca riesgo de brick.
✅ **No depende de network/TFTP en cada boot**: kernel vive en NAND.
✅ **Iteración rápida**: solo `flash_mainline.py` después de cada rebuild.

## Limitaciones conocidas

- ❌ Cada vez que el kernel cambia de tamaño/contenido cambian los CRCs csp_crc:
  hay que iterar 1 boot fallido (para leer "Real crc XXXX" del log) + 1 reflash header.
  **Posible mejora**: RE'r el algoritmo csp_crc para calcular local sin iterar.
- ❌ Slot B tiene firmware stock viejo: si necesitamos slot B también para
  segunda imagen mainline, hay que repetir el proceso para el slot B.
- ❌ Bootargs vienen del DTB (chosen.bootargs), no del U-Boot env: cambiar bootargs
  requiere rebuild del DTB.
