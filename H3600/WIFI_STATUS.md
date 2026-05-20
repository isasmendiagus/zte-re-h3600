# WiFi MT7915 — Estado actual y bitácora del bring-up

> Hardware: MT7915 (vendor 0x14c3 device 0x7915) sobre PCIe interno port 0
> del SoC ZX279128S. Driver mainline `mt7915e` + `mt76` + `mac80211` +
> `cfg80211`.

## TL;DR — Lo que destrabó cada cosa

| # | Síntoma | Causa | Fix |
|---|---|---|---|
| 1 | LTSSM stuck en `Detect.Quiet` (link no entrenaba) | GPIO addr de PERST# mal: `0x944071C0` (bank 7) en vez de `0x944070C0` (bank 3) | Fix de bank en `pcie-zx279128s.c` |
| 2 | mt7915e: `Unknown symbol arc4_setkey` | Faltaba `CONFIG_CRYPTO_LIB_ARC4` en kernel | Habilitado en `.config` (`=y`) |
| 3 | `cfg80211: regulatory.db is malformed` | Par `regulatory.db` + `.p7s` mismatched (descargados separados) | Copiar pareja consistente desde `/lib/firmware/` (Ubuntu wireless-regdb) |
| 4 | mt7915e: `Message 00000010 (seq 1) timeout` → `Failed to get patch semaphore` | **MSI no entregaba interrupts del MT7915 al mt7915e**. Stock usa INTx (GIC 95 Level), DesignWare PCIe MSI no rutea bien al endpoint en este SoC | `pci=nomsi` en kernel cmdline |
| 5 | mt7915e: `Direct firmware load for mediatek/mt7915_eeprom_dbdc.bin failed -2` | Driver busca EEPROM por filename, no estaba | Copiar `MT7915_EEPROM.bin` del rootfs vendor a `/lib/firmware/mediatek/{mt7915_eeprom.bin,mt7915_eeprom_dbdc.bin}` (3584 B) |
| ⚠️ | `pci=noaspm` reportado como "Unknown option" | En kernel 6.6 esa opción no existe en `pci_setup` | Usar `pcie_aspm=off` en su lugar |
| ⚠️ | bootargs el último arg corrupto por `; U-Boot V1.0.0...` | Bug del U-Boot ZTE patched | Poner el arg crítico (nomsi, etc.) **al frente** o agregarlo via `CONFIG_CMDLINE` |

## Insight más importante: MSI vs INTx

Stock usa interrupt **legacy INTx**:
```
37: 14720 GIC 95 Level pcie, 0000:00:00.0
```
Mainline mt76 driver llama `pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES)` que prefiere MSI > INTx. Mainline DesignWare PCIe controller con la config actual de `interrupt-names = "main", "msi"` deja MSI configurado, pero la entrega de MSI al endpoint MT7915 **no funciona en la práctica** (el MCU del chip envía la respuesta pero el handler nunca corre).

Forzar INTx con `pci=nomsi` resolvió **completamente** el bloqueo del patch
semaphore. Posibles causas a investigar a futuro:
- DWC core no enrutaría MSI con la geometría inbound iATU actual
- El IRQ "msi" del DT (`GIC_SPI 0x3b`) puede estar mal cableado al GIC

Por ahora `pci=nomsi` es la solución productiva.

## Cmdline final que funciona

```
pci=nomsi pcie_aspm=off rdinit=/init console=ttyAMA0,115200n8 earlycon=pl011,0x94404000 earlyprintk ignore_loglevel
```

Nota: `pci=nomsi` y `pcie_aspm=off` van **al frente** porque ZTE U-Boot
appendea `; U-Boot V1.0.0 ...` al último arg corrompiéndolo.

## Componentes que necesitamos en /lib/firmware/

```
mediatek/mt7915_rom_patch.bin      (linux-firmware, 144 KB)
mediatek/mt7915_wm.bin             (linux-firmware, 1.26 MB — main FW)
mediatek/mt7915_wa.bin             (linux-firmware, 116 KB — WiFi accelerator)
mediatek/mt7915_eeprom.bin         (de rootfs vendor /etc/wireless/mt7915/, 3584 B)
mediatek/mt7915_eeprom_dbdc.bin    (mismo file, alias)
regulatory.db + regulatory.db.p7s  (pareja de Ubuntu wireless-regdb)
```

## Módulos kernel necesarios

Cargar en este orden:
```
1. pcie-zx279128s.ko          (custom — nuestro driver del SoC PCIe)
2. cfg80211.ko                (mainline)
3. mac80211.ko                (mainline, depende de cfg80211 + arc4)
4. mt76.ko                    (mainline)
5. mt76-connac-lib.ko         (mainline, depende de mt76)
6. mt7915e.ko                 (mainline, depende de los anteriores)
```

`CONFIG_CRYPTO_LIB_ARC4=y` (builtin) es OBLIGATORIO sino mac80211 falla por
símbolo no resuelto.

## Stock vs Mainline — registros con WiFi corriendo (recon SSH)

Capturado vía `stock_recon.py` (paramiko shell):

| Reg | Stock running | Para reproducir en mainline |
|---|---|---|
| topcrm 0x08 | 0x1FF7FFFF | OR `0xFF1E000` (sub-resets) |
| topcrm 0x4C | 0x3CFFF | OR `0x3CE00` sobre `0x381FF` (SerDes mux) |
| pcie_crm 0x70 | 0x1AAB5 | OR `0x1AAB5` |
| pcie_crm 0x74 | 0x1B | OR `0x1B` (PHY release) |
| pcie_crm2 0x0C | **0x25B005** | **`regmap_write` exacto** (no update_bits con mask incompleta) |
| soc_ctrl 0x00 | 0x28 | OR `0x28` (controller enable bits 3+5) |
| soc_ctrl 0xDC | 0x220000 | LTSSM L0 (verify only) |
| GPIO bank3 lvl | 0x20A7 | pins 48/49/50/61 HIGH antes de PERST# pulse |
| /proc/interrupts pcie 00:00 | GIC 95 Level | INTx (forzar con `pci=nomsi`) |

## Workflow de iteración funcional

```
1. Edit driver / config / cmdline
2. cd linux-v6.6 && touch usr/Makefile && make -j8 zImage      (~2-4 min)
3. cd tftp && cat zImage zx279128s-h3600.dtb > zImage_dtb.bin
   mkimage -A arm -O linux -T kernel -C none -a 0x42000000 -e 0x42000040 \
           -d zImage_dtb.bin zImage_dtb.uimg
4. python3 uart.py auto_bootm_dtb_appended  (& en background, espera Power-cycle)
5. Power-cycle el modem físico
6. Script intercepta U-Boot, sends `1` + Boot4128s!, TFTP boot del nuevo kernel
7. Monitor /tmp/uart.log para ver progreso
```

Para iteración SIN reboot del kernel (solo cambios de driver `.ko`), usar:
```
python3 uart_transfer.py build/.../module.ko /tmp/mod/x.ko    (UART base64, ~30s)
python3 uart.py send "rmmod X; insmod /tmp/mod/x.ko; dmesg | tail"
```
Pero requiere que el kernel persistido en NAND tenga las dependencias correctas.

## 🎉🎉🎉 HITO TOTAL: WiFi mainline 100% funcional + INTERNET (2026-05-04)

```
$ /usr/bin/iw wlan0 link
Connected to cc:29:bd:22:b4:2b (on wlan0)
  SSID: Dino-WiFi
  signal: -36 dBm
  RX: 421166 bytes (2140 packets)
  TX: 40403 bytes (1454 packets)

$ udhcpc -i wlan0
udhcpc: lease of 10.44.66.113 obtained from 10.44.66.250

$ ping -c 3 10.44.66.250    →  3/3, 26-87ms
$ ping -c 3 8.8.8.8         →  3/3, 62-164ms  (INTERNET via WiFi mainline)
```

### El bug que lo destrabó todo

```
CONFIG_CRYPTO_AES=m        # → =y
CONFIG_CRYPTO_CCM=m        # → =y
CONFIG_CRYPTO_GCM=m        # → =y
CONFIG_CRYPTO_HMAC=m       # → =y
CONFIG_CRYPTO_SHA256=m     # → =y
CONFIG_CRYPTO_CTR=m        # → =y
CONFIG_CRYPTO_CMAC=m       # → =y
CONFIG_CRYPTO_GHASH=m      # → =y
```

Las primitivas crypto estaban compiladas como **módulos** pero no se cargaban
porque no se copiaron al initramfs. Cuando mac80211 hacía
`crypto_alloc_aead("ccm(aes)")` para instalar las keys CCMP del 4-way
handshake, fallaba silenciosamente → wpa_supplicant veía timeout del EAPOL M3
→ disociación → loop infinito de auth/assoc/deauth.

Cambiar todo el conjunto crypto a **builtin (`=y`)** los hace presentes en el
kernel image — no dependen de carga de modules. Después del rebuild + flash:

- 4-way handshake **completa**
- CCMP keys **instaladas en hardware** del MT7915
- L2 enlace cifrado **funciona**
- DHCP, routing, ping, internet → **todo**

### Stack completo end-to-end funcional

| Capa | Estado |
|---|---|
| ZX279128S boot custom (mainline 6.6) | ✅ desde NAND |
| PCIe DesignWare RC driver (`pcie-zx279128s.c`) | ✅ Gen1 x1 link up |
| MT7915 [14c3:7915] enumerado por PCIe | ✅ |
| Firmware MT7915 (rom_patch + WM + WA) | ✅ desde linux-firmware |
| mt76 + mt7915e mainline (Linux 6.6) | ✅ probe completo |
| EFUSE_BUFFER_MODE timeout (cosmético, post-FW) | ⚠️ no bloquea |
| wlan0 + wlan1 (2.4 + 5 GHz) interfaces | ✅ |
| `iw scan` ve APs reales | ✅ |
| wpa_supplicant cross-compiled WPA2-PSK | ✅ |
| **4-way handshake CCMP** | **✅** (crypto builtin fue la fix) |
| DHCP IPv4 (10.44.66.113) | ✅ |
| IPv6 SLAAC (2a0c:5a86:4d08:cc00::/64) | ✅ |
| Ping LAN gateway | ✅ |
| **Ping internet (8.8.8.8)** | **✅** |

## ✅✅✅ HITO previo: WiFi escanea redes reales (2026-05-03)

```
$ iw dev
phy#0
  Interface wlan1
    addr 00:0c:43:26:59:97   (5GHz)
    type managed
    txpower 20.00 dBm
phy#0
  Interface wlan0
    addr 00:0c:43:26:46:44   (2.4GHz)
    type managed
    txpower 20.00 dBm

$ iw wlan0 scan
BSS a8:9a:93:5c:85:a0(on wlan0)
  SSID: MiFibra-85A0
  freq: 2412
  signal: -63.00 dBm
  RSN: WPA2 / CCMP / PSK
```

**MT7915 mainline driver completamente operativo en el ZTE H3600**.

## ✅ HITO previo: WiFi UP a nivel driver (2026-05-03)

```
$ ls /sys/class/net/
lo  sit0  wlan0  wlan1

$ ifconfig wlan0
wlan0     Link encap:Ethernet  HWaddr 00:0C:43:26:46:44
          UP BROADCAST MULTICAST  MTU:1500  Metric:1

$ ifconfig wlan1
wlan1     Link encap:Ethernet  HWaddr 00:0C:43:26:59:97
          UP BROADCAST MULTICAST  MTU:1500  Metric:1
```

OUI `00:0C:43` = MediaTek → EEPROM cargado correctamente.

Warnings no-bloqueantes residuales:
- `cfg80211: regulatory.db is malformed` (cosmético, regdb fallback funciona)
- `eeprom load fail, use default bin` (driver intenta vendor file, usa eFuse)
- `Message 000021ed (seq 8) timeout` = `MCU_EXT_CMD_EFUSE_BUFFER_MODE`
- `Message 00001eed (seq 9) timeout` = `MCU_EXT_CMD_TXBF_ACTION`

Los dos timeouts son comandos post-init que el chip no acepta — no impiden
crear las interfaces. A futuro investigar si afectan throughput o features.

## ⚠️ Checkpoint 2026-05-03 EOD: 4-way handshake falla

### Lo que sí funciona
- Driver mainline mt7915e carga + crea wlan0 (2.4GHz) y wlan1 (5GHz)
- `iw dev` lista interfaces, `iw scan` ve redes reales (Dino-WiFi, MiFibra-85A0)
- `wpa_supplicant -D nl80211` se conecta a Dino-WiFi exitosamente:
  - `wlan0: authenticate with cc:29:bd:22:b4:2b` ✓
  - `wlan0: send auth (try 1/3)` ✓
  - `wlan0: authenticated` ✓
  - `wlan0: associate (try 1/3)` ✓
  - `wlan0: RX AssocResp (capab=0x1c31 status=0 aid=23)` ✓
  - `wlan0: associated` ✓
- **Router de la casa lo ve como Cliente-7** con MAC `00:0c:43:26:46:44`
  (verificado en su admin web)

### Lo que NO funciona
- ~250ms después de `associated` el driver hace:
  `wlan0: deauthenticating from cc:29:bd:22:b4:2b by local choice (Reason: 1=UNSPECIFIED)`
- IP queda en `0.0.0.0` (router lo lista así también)
- `iw wlan0 link` reporta `Not connected`
- DHCP (udhcpc) no recibe respuesta porque no hay link L2 real
- ping al gateway (10.44.66.250) 100% packet loss
- Loop infinito de auth → assoc → deauth → reattempt

### Causa probable

El timeout `MCU_EXT_CMD_EFUSE_BUFFER_MODE` (cmd `0x21ed` seq 8) durante init
del driver:
```
[t+95s] mt7915e 0000:01:00.0: Message 000021ed (seq 8) timeout
[t+115s] mt7915e 0000:01:00.0: Message 00001eed (seq 9) timeout
```

`EFUSE_BUFFER_MODE` es el comando que sube la EEPROM (con TX power tables,
**parámetros de derivación de keys**, regulatorio) al MCU del chip. Sin esto:
- Chip usa eFuse defaults (se ve "use default bin" en el log)
- Las keys derivadas del PSK pueden no programarse correctamente al chip
- → 4-way handshake EAPOL no llega o no se procesa
- → AP detecta timeout y/o supplicant deauths

`MCU_EXT_CMD_TXBF_ACTION` (cmd `0x1eed` seq 9) es de beamforming —
secundario, pero también indica que el chip MCU no acepta comandos extendidos.

### Test 2026-05-03 EOD: `flash_mode=false` NO destrabó

Aplicado `dev->flash_mode = false` en `mt7915_eeprom_load_default` para que el
driver mande `EFUSE_BUFFER_MODE` sin payload (sólo header, modo `EE_MODE_EFUSE`).

Resultado: el comando **igual da timeout**. Y aparecen MÁS timeouts:
```
Message 000021ed (seq 4) timeout   ← EFUSE_BUFFER_MODE (corto, no payload)
Message 00001eed (seq 5) timeout   ← TXBF_ACTION
Message 00003aed (seq 6) timeout   ← MCU_EXT cmd 0x3a (no identificado)
```

**Conclusión revisada**: el chip MCU rechaza **todos los ext commands** después
de cargar patch + WM + WA. Esto NO es problema del payload — es la pipe de ext
commands en general que no funciona.

Causa más probable: **firmware mainline incompatible con silicon revision** del
chip. Las strings de los firmware reportan versión sospechosa:
- `WM Firmware Version: ____000000` (placeholder, no string real)
- `WA Firmware Version: DEV_000000` (DEV build, no GA)

Vendor distingue `WIFI_RAM_CODE_MT7915.bin` (E1) vs `WIFI_RAM_CODE_MT7915_E2.bin`
(E2). Mainline ships solo el E2-equivalent (`mt7915_rom_patch.bin` 144544 B = E2 size).
Si nuestro chip es E1 → mainline le carga FW de E2 → MCU acepta solo lo
básico (registros, patch_sem, FW_SCATTER) pero rechaza ext cmds.

**Próximo paso REAL** (siguiente sesión):
- Leer `MT_HW_REV` (0x70010204 chip-internal addr) via printk en mt7915 driver
  → confirmar E1 o E2
- Extraer `WIFI_RAM_CODE_MT7915_E1.bin` / `_E2.bin` + `mt7915_patch_e1_hdr.bin` /
  `_e2.bin` del binario `mt7915.ko` vendor (están en `.data` section)
- Reemplazar mt7915_rom_patch.bin / mt7915_wm.bin con los del vendor
- Reintentar

### Datos del chip leídos via SSH stock (2026-05-03 EOD)

Vendor driver iwpriv permite leer chip-internal regs:
```
$ iwpriv wlan0 mac 70010200    → 0x7915          # MT_HW_CHIPID
$ iwpriv wlan0 mac 70010204    → 0x8a10          # MT_HW_REV (chip rev marker)
$ iwpriv wlan0 mac 70010210    → 0x0001          # silicon variant (1 = E2)
$ iwpriv wlan0 e2p 0           → 0x7915          # EEPROM[0..1] = chip id
$ iwpriv wlan0 e2p 4           → 0x0C00          # EEPROM[4..5] = format/ver
```

Driver vendor: **version 7.1.0.1**

**Conclusión actualizada**: chip ES E2 (`0x70010210 = 1`). Vendor's `chip[0x14] == 1`
distinguishing E1/E2 maps to this register read. **Mainline mt7915_rom_patch.bin
(144544 B ≈ vendor E2 144032 B) IS the right generation.** Por lo tanto el 4WH
issue NO es por mismatch silicon E1/E2.

Sigue abierto: **¿por qué los ext commands del MCU timeout post-init?** Posibles
causas más sutiles:
- DMA event ring del MCU no recibe responses (mientras patch via FW_SCATTER sí)
- Falta init seq específico que vendor hace pre-ext-cmd
- Bug en mainline mt76 v6.6 vs versión más reciente que arregla MT7915 E2
- Los WM/WA firmware mainline reportan `____000000` y `DEV_000000` —
  probablemente son los GA pero formato/sub-versión incompatible

Vendor extracted firmware blobs disponibles en `/tmp/vendor_fw/`:
- mt7915_rom_patch_e1.bin (128208 B, build 2019-08-20)
- mt7915_rom_patch_e2.bin (144032 B, build 2020-05-19)
- mt7915_wm_e1.bin (1051968 B)
- mt7915_wm_e2.bin (1260968 B)
- mt7915_wa.bin (103904 B)

Para próxima sesión: comparar formato vendor_e2 vs mainline (header wrappers,
section trailers) y eventualmente probar reemplazo.

### Cosas probadas que NO ayudaron
- `pci=nomsi pcie_aspm=off` (esto SÍ destrabó el patch_sem inicial — fue clave)
- Pre-computar PSK en hex via `wpa_passphrase` (era para descartar problema de
  `#` en password)
- Agregar `proto=RSN`, `pairwise=CCMP`, `group=CCMP`, `ieee80211w=1` al config
- `iw reg set ES` (no toma efecto, queda country=00)
- IP estática + ping (sin link L2 no rutea)
- mt7915 + mt7916 firmware variants — usamos los de linux-firmware estándar

### RE de EFUSE_BUFFER_MODE (mt76 mt7915/mcu.c:2751-2805)

Flujo:
1. `mt7915_eeprom_load`: lee EEPROM de DT/nvmem o eFuse del chip
2. Si chip eFuse vacío (>= 29 free blocks): retorna `-EINVAL`
3. `mt7915_eeprom_init`: cae a `mt7915_eeprom_load_default`:
   - Carga `/lib/firmware/mediatek/mt7915_eeprom.bin` (3584B exact)
   - **Setea `dev->flash_mode = true`**
4. Más adelante, `mt7915_mcu_set_eeprom`:
   - Si `flash_mode=true` → `mt7915_mcu_set_eeprom_flash` (4 páginas de 1024B)
   - **La primera página timeout** (cmd `EFUSE_BUFFER_MODE` = `0x21ed` con payload)
5. Si `flash_mode=false` → cmd `EFUSE_BUFFER_MODE` corto sin payload (chip usa
   su propio eFuse). Esto **no se ha probado**.

`patch` + `WM` + `WA` firmware se cargan via `FW_SCATTER` cmd (otro path), por
eso esos sí funcionan. `EFUSE_BUFFER_MODE` es path distinto que el chip no
acepta.

### Ideas para sesiones futuras

1. **RE de `MCU_EXT_CMD_EFUSE_BUFFER_MODE` en mt76**: ver qué payload espera y
   por qué el chip no responde. Quizás formato del EEPROM mainline ≠ vendor.
2. **Probar firmware MT7915 mas viejo o vendor**: stock vendor mt7915.ko tenía
   `WIFI_RAM_CODE_MT7915_E2.bin` con build date 2021-01-22. Ours es 2022-09-29.
   Posible regression en mainline FW para esta silicon revision.
3. **Revisar si chip es realmente single-band MT7915** o variante con DBDC.
   Stock crea 10 vAPs (5 por banda) → es DBDC. Mainline mt7915_eeprom_dbdc.bin
   es la elegida. Quizás formato wrong.
4. **Forzar single-band**: parchear driver para asumir single radio y ver si
   EFUSE upload anda con menos data.
5. **Agregar prints en mt76_connac_mcu_send_msg**: ver dónde exactamente se
   bloquea. Podría ser DMA TX OK pero RX nunca llega — apuntaría a IRQ del
   MCU response que no entra (similar al MSI issue inicial pero en otro contexto).
6. **Ver si el ROM patch + WM/WA firmware son los correctos para este SKU**:
   probar otras versiones del linux-firmware repo.

### Estado actual de archivos

- `pcie-zx279128s.c` — driver del SoC PCIe controller (funciona)
- `wpa_supplicant.conf` con SSID `Dino-WiFi` + PSK hex
- `/usr/sbin/wpa_supplicant` (1.4MB static, soft-float)
- `/usr/sbin/dropbearmulti` (1MB static, sin password auth, solo pubkey — pendiente)
- `/usr/bin/iw` (800KB static, soft-float, funciona)
- `/etc/wpa_supplicant.conf`
- `/lib/firmware/mediatek/{mt7915_*,regulatory.db,regulatory.db.p7s}`

Cmdline kernel: `pci=nomsi pcie_aspm=off rdinit=/init console=ttyAMA0,115200n8 earlycon=pl011,0x94404000 earlyprintk ignore_loglevel`

## Pendientes (post wlan0 UP)

- [ ] Agregar `iw` a initramfs para testing (scan, set mode, AP)
- [ ] Probar wlan0 en modo STA → asociar a AP de prueba
- [ ] Probar wlan0 en modo AP → asociar cliente
- [ ] Investigar timeout EFUSE_BUFFER_MODE (puede afectar TX power calibration)
- [ ] Investigar timeout TXBF_ACTION (puede afectar beamforming)
- [ ] Cargar firmware MT7916 si querés enable port 1 (chip dual con dos radios más)
- [ ] **Investigar por qué MSI no funciona** — fix permanente del DWC PCIe driver
- [ ] Limpiar el driver `pcie-zx279128s.c` (eliminar regs redundantes)

## Archivos relevantes

- Driver SoC PCIe: `linux-v6.6/drivers/pci/controller/dwc/pcie-zx279128s.c`
- DT: `linux-v6.6/arch/arm/boot/dts/zte/zx279128s.dtsi`
- Init script (initramfs): `/tmp/initramfs_extract/init`
- Recon stock: `stock_recon.py`
- UART iter: `uart.py`, `uart_transfer.py`
- Doc previo PCIe: `PCIE_STATUS_2026-05-03.md`
