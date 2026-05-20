# H3600 — Editar `config.bin` (habilitar SSH/Telnet, etc.)

> Solo aplica al **H3600** (modelo sin la P). El H3600P usa una variante de
> AES con keys derivadas de serial+MAC+passphrase; el H3600 a secas tiene
> **keys hardcoded** porque ZTE rompió su propio algoritmo.

## TL;DR

```bash
# Habilitar SSH (ya está en 1 en stock, no-op normalmente)
./cfg_tool.py ssh-on    config.bin  config_new.bin

# Habilitar Telnet en LAN (puerto 23)
./cfg_tool.py telnet-on config.bin  config_new.bin

# Decode + edit manual
./cfg_tool.py decode config.bin /tmp/c.xml
$EDITOR /tmp/c.xml
./cfg_tool.py plain  /tmp/c.xml config_new.bin   # plain (flag=0)
./cfg_tool.py encode /tmp/c.xml config_new.bin   # AES (flag=4) — opcional
```

Subí `config_new.bin` por el web admin (`Administración → Backup/Restore`).
El router acepta tanto el formato cifrado como el plain.

## Cómo funciona el cifrado (RE)

Source: orca.pet H3600P writeup + verificación en `/bin/cspd`
(`dbcCfgFileEncry`, `EncryByAESCBCandCRC`, `aescbc_encry`/`decry`).

### Layout del archivo

| Offset | Tipo | Campo |
|--------|------|-------|
| 0x00 | u32 BE | Magic `0x01020304` |
| 0x04 | u32 BE | `flag` — `0` = plain zlib, `4` = AES-256-CBC + zlib |
| 0x08 | u32 BE | total uncompressed size |
| 0x0C | u32 BE | reservado / 0 |
| 0x10 | u32 BE | mirror de total size |
| 0x14 | u32 BE | CRC32 zlib del XML descomprimido |
| 0x18 | u32 BE | CRC32 zlib de los primeros 24 bytes del header |
| 0x1C-0x3B | bytes | padding 0x00 (header total = 60 B) |
| 0x3C+  | chunks | uno o varios chunks |

Cada **chunk** tiene su propio header de 12 bytes:
```
u32 BE  plain_len
u32 BE  encoded_len     (= plain_len si no hay encriptación, sino padded)
u32 BE  more_flag       (0 = último chunk, !=0 = sigue otro)
bytes   payload         (encoded_len bytes)
```

Para el modo AES (flag=4):
- Tras descifrar todos los chunks AES y concatenarlos, el resultado **vuelve
  a ser un archivo con el mismo formato pero `flag=0`** (Russian-doll: AES
  envuelve a zlib).
- Luego se procesan los chunks zlib del archivo interior.

### Las keys hardcoded del H3600

```python
key_pass = b"H3600V9Key02660008"
iv_pass  = b"H3600V9Iv02660008"

key = buggy_sha256(key_pass)        # 32 bytes (AES-256 key)
iv  = buggy_sha256(iv_pass)[:16]    # 16 bytes (AES-CBC IV)
```

`buggy_sha256` es una implementación de SHA-256 con un bug en la rutina de
padding final que ZTE incluyó en `libsha256.so`. La implementación correcta
está en [`../tools/ztetool.py`](../tools/ztetool.py) (orca.pet).

Para TU device las keys evaluadas resultan:
- key: `0adbbe9375b8c6b970909c6f6ed1a7754d086d8984f36934b7b4981d44e783d5`
- IV:  `3f206207eef465d4b0b9be6e8a60a396`

(válidas para todo H3600 con FW V9.x, **no** sirven para H3600P.)

## Workflow para subir cambios

1. **Backup actual**: web admin → Backup → guardar `config.bin` original.
2. **Decode + editar**: `./cfg_tool.py decode config.bin /tmp/c.xml; $EDITOR /tmp/c.xml`.
3. **Re-pack plain** (más simple, no necesita reimplementar AES):
   `./cfg_tool.py plain /tmp/c.xml config_new.bin`.
4. **Subir**: web admin → Restore → seleccionar `config_new.bin` → reboot.
5. Si el router rechaza el plain, usar `./cfg_tool.py encode` para reciframos.

## Estado del config en stock V9.0.20P72 (TU device)

Verificado al descifrar `config.bin` real:

- `SSHCfg.SSH_Enable = 1` (puerto 22, user `admin`, pass `UkuGPeyRDU`)
- `TelnetCfg.TS_Enable = 0`, `Lan_Enable = 0` → telnet OFF

⚠️ **PERO** SSH **NO** está accesible desde tu LAN tal cual viene stock.
Lo bloquea el firewall (tabla `FWSC`) — ver sección siguiente.

## El firewall del config (tabla `FWSC`) — esto es lo que hay que tocar

`FWSC` = **F**ire**W**all **S**ervice **C**ontrol. Cada fila es una regla
del estilo *"si IP origen está en este rango Y el servicio destino está en
esta lista, entonces ALLOW/DROP"*.

Estado real en TU stock (9 reglas activas):

| # | Name | Interface (INCViewName) | Src IP | ServiceList | FilterTarget |
|---|---|---|---|---|---|
| 1 | access1 | WAN | 188.26.208.1-254 | HTTP,SSH,HTTPS | **1=ALLOW** |
| 2 | access2 | WAN | 188.26.216.1-254 | HTTP,SSH,HTTPS | **1=ALLOW** |
| 3 | access3 | WAN | 172.16.20.105 | HTTP,SSH,HTTPS | **1=ALLOW** |
| 4 | access4 | WAN | 91.232.81.222 | HTTP,SSH,HTTPS | **1=ALLOW** |
| 5 | access5 | WAN | 188.26.217.1-254 | HTTP,SSH,HTTPS | **1=ALLOW** |
| 6 | access6 | WAN | * | PING | 1=ALLOW |
| 7 | access7 | WAN (v6) | * | PING | 1=ALLOW |
| 8 | **lan_ssh** | **LAN** (DEV.IP.IF1) | * | **SSH** | **0=DROP** |
| 9 | **lan_sshv6** | **LAN** (v6) | * | **SSH** | **0=DROP** |

Las reglas 1-5 dejan al ISP entrar por SSH/HTTP/HTTPS desde sus rangos de
management (`188.26.x.x`, etc. — todo de Digi/ZTE). Las reglas **8 y 9**
matan explícitamente SSH desde tu LAN. Por eso no podés hacer
`ssh admin@192.168.1.1` desde una PC en la LAN aunque `SSH_Enable=1`.

### Cómo habilitar SSH desde LAN

Editar el XML descifrado y para los Row No=7 y Row No=8 de la tabla `FWSC`:

```xml
<!-- ANTES -->
<DM name="FilterTarget" val="0"/>   <!-- DROP -->

<!-- DESPUÉS -->
<DM name="FilterTarget" val="1"/>   <!-- ALLOW -->
```

O alternativamente desactivar la regla:
```xml
<DM name="Enable" val="0"/>         <!-- regla deshabilitada -->
```

Cualquiera de las dos sirve — la más limpia es flipear `FilterTarget` a 1.

### `SSHCfg.SSH_ProcType` y `SSH_Level` (los flags que vimos antes)

No regulan el firewall (eso es FWSC). Lo que sí hacen, según `dbCreateSSHCfgTbl`
y `FwGetCurrentLevel` en `cspd`:

- `SSH_Level` = nivel mínimo de "security level" del firewall global en el
  que el daemon SSH se levanta. El firewall global tiene niveles
  Low/Medium/High; si `SSH_Level=3` el SSH solo arranca en Low (más permisivo).
- `SSH_ProcType` = tipo de proceso del demonio SSH (restricted shell vs full
  shell — el `cli_agent` interactivo de ZTE vs `dropbear` directo).

El `config_modified.bin` usa `ProcType=0` y `Level=1` (más permisivo, demonio
arranca siempre, shell más completa). El stock usa `1`/`3` (más restringido).
**Ninguno** de estos dos flags abre el SSH desde LAN — para eso hay que
tocar FWSC sí o sí.

## TL;DR del flujo "SSH desde LAN"

```bash
./cfg_tool.py decode config.bin /tmp/c.xml
# editar /tmp/c.xml: FWSC Row No=7 y Row No=8 → FilterTarget de "0" a "1"
./cfg_tool.py plain  /tmp/c.xml config_lansh.bin
# subir config_lansh.bin desde web admin → reboot
```

`telnet-on` (helper del cfg_tool) es independiente del FWSC porque la regla
del firewall de telnet no existe por defecto, solo basta con flipear
`TelnetCfg.TS_Enable` y `Lan_Enable`.

## Credenciales stock (per-device)

- Admin web/SSH: `UkuGPeyRDU`
- U-Boot: `Boot4128s!`
- Device key (32B, en `mtd2 @ 0x190`): `MfDGk9YRwLDEZTMO4HNztPIVYa&T2Ql2`
- Serial: `ZTE0H89N5Q05834`, MAC base: `f4:f6:47:0f:42:64`

(El device key + serial + MAC solo se necesitan si querés descifrar configs
del H3600**P** — para el H3600 las keys son las hardcoded de arriba.)

## Archivos

- [`cfg_tool.py`](cfg_tool.py) — wrapper de alto nivel (decode/encode/ssh-on/telnet-on)
- [`../tools/ztetool.py`](../tools/ztetool.py) — implementación cruda del cifrado
  (orca.pet, GPL) — `--router h3600`
