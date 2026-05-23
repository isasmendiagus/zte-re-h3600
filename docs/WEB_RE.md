# H3600 Stock Web Admin — RE log

Bitácora de investigación del web admin (cspd + httpd Lua) en stock V9.0.20P72.
Fin: encontrar un camino para flashear OpenWrt **sin admin pwd ni UART**.

---

## TL;DR del estado actual

| Vector | Status |
|---|---|
| SSH `admin/UkuGPeyRDU` | ✅ funciona en NUESTRO device (per-device pwd, no escalable) |
| TR-069 self-flash | ❌ requiere root SSH para reemplazar `/usercfg/ca-cert.crt` |
| Factory reset → defaults `Haikui_V2` | ❌ pwd persiste en `/usercfg/db_user_cfg.xml` |
| Web admin chpwd Right escalation (user→admin) | ❌ server valida transición |
| Web admin upload (firmware/config/cert) desde user | ❌ Lua dmenu_modifier setea `right=1` (admin-only) |
| **Pre-auth bug sntp_data** | ❌ TESTEADO 2026-05-04: SessionTimeout (ver §6) |
| **dmenu_modifier patch** (si tenemos shell) | ✅ baja ese gate, pero requiere shell primero |
| SPI NAND clip programmer | ✅ universal pero invasivo |

---

## 1. Web auth flow (RE completo)

### 1.1 Capas que el browser aplica (bytecode Lua + JS)
1. **HTTPS solamente** — el cspd serve también `:80` pero rechaza POSTs como CSRF-fail. Cookies son `SID_HTTPS_` / `_TESTCOOKIESUPPORT_HTTPS_` (sufijo `_HTTPS_` literal).
2. **Cert auto-firmado ZTE** — `CN=192.168.1.1, O=ZTE, ZTE-ROOT-CA, valid 2016→2031`. Usar `curl -k`.
3. **Rolling `_sessionTOKEN`** — el primer login con `_sessionTOKEN=""` devuelve `cmret_1452` ("Esta página ha caducado") PERO siembra un token server-side; el segundo intento con el `sess_token` recibido en la respuesta logra `login_need_refresh:true`. Sin esto cualquier login pega "caducado".
4. **`_sessionTmpToken`** se renueva por menuView — embebido como string `"\x31\x38\x33..."` en el HTML retornado por `?_type=menuView&_tag=<page>`. El JS lo extrae con regex y lo usa como `_sessionTOKEN` en POSTs subsiguientes. Cada menuView entrega uno nuevo.
5. **Header custom `Check: sha256(body)`** — todos los POST a `_type=menuData` requieren un header `Check` con sha256 hex del body completo (`form-urlencoded`, incluyendo `&_sessionTOKEN=...`). Sin él → HTTP 400 + SessionTimeout en HTML. **Este header fue el bloqueante principal por mucho rato.**
6. **AES+RSA wrapping** para campos marcados con `<encode>F1,F2,...</encode>` en la respuesta del menuData GET inicial:
   - JS genera `key_str` y `iv_str` random de 16 dígitos cada uno.
   - `encode = base64(RSA_PKCS1v15_encrypt(pubkey, "key_str+iv_str"))` → field `encode` del POST.
   - Cada campo a cifrar = `base64(AES_256_CBC_encrypt(sha256(key_str), sha256(iv_str)[:16], plaintext + zero_pad))`.
   - Padding zero-fill, NO PKCS#7.
7. **Pubkey** está embebida en el login HTML, **idéntica al `enwebdhardcodefile` de la rootfs** → tenemos la priv key (ver memoria `zte_hardcode_vault_keys`).

### 1.2 Errores diferenciables (cmret codes)
| cmret | mensaje | causa |
|---|---|---|
| `cmret_1452` | "Esta página ha caducado…" | CSRF check fail (rolling token mismatch o body checksum off) |
| `lockingTime > 0` | "El inicio de sesión ha fallado N veces" | wrong pwd, lockout counter incrementa |
| `lockingTime = -1` + caducado | – | rolling token mismatch (no cuenta como wrong pwd) |
| `IF_ERRORTYPE=2` "contraseña anterior es un error" | – | chpwd: old pwd wrong O role insuficiente (mismo mensaje) |
| `<IF_ERRORSTR>SessionTimeout</IF_ERRORSTR>` | – | menu_tree no resolvió `backendFile` (rol insuf, página no existe, etc.) |

### 1.3 Snippet curl de login funcionando
```bash
# 1) bootstrap (sets SID_HTTPS_)
curl -sk -c jar.txt https://192.168.1.1/ -o /dev/null
# 2) get salt
SALT=$(curl -sk -b jar.txt -c jar.txt 'https://192.168.1.1/?_type=loginData&_tag=login_token' \
  -H 'X-Requested-With: XMLHttpRequest' \
  | sed -nE 's/.*>([0-9A-Za-z]+)<.*/\1/p')
# 3) primer login (siempre falla "caducado" pero siembra token)
PWHASH=$(printf '%s' "user${SALT}" | sha256sum | cut -d' ' -f1)
RESP=$(curl -sk -b jar.txt -c jar.txt 'https://192.168.1.1/?_type=loginData&_tag=login_entry' \
  -H 'X-Requested-With: XMLHttpRequest' -H 'Origin: https://192.168.1.1' \
  -H 'Content-Type: application/x-www-form-urlencoded; charset=UTF-8' \
  --data-urlencode "Password=${PWHASH}" --data-urlencode "Username=user" \
  --data-urlencode "_sessionTOKEN=" --data-urlencode "action=login")
TOK=$(echo "$RESP" | sed -nE 's/.*"sess_token":"([^"]+)".*/\1/p')
# 4) segundo login con TOK del primer intento → SUCC
SALT=$(curl -sk -b jar.txt -c jar.txt 'https://192.168.1.1/?_type=loginData&_tag=login_token' \
  -H 'X-Requested-With: XMLHttpRequest' | sed -nE 's/.*>([0-9A-Za-z]+)<.*/\1/p')
PWHASH=$(printf '%s' "user${SALT}" | sha256sum | cut -d' ' -f1)
curl -sk -b jar.txt -c jar.txt 'https://192.168.1.1/?_type=loginData&_tag=login_entry' \
  -H 'X-Requested-With: XMLHttpRequest' -H 'Origin: https://192.168.1.1' \
  -H 'Content-Type: application/x-www-form-urlencoded; charset=UTF-8' \
  --data-urlencode "Password=${PWHASH}" --data-urlencode "Username=user" \
  --data-urlencode "_sessionTOKEN=${TOK}" --data-urlencode "action=login"
# → {"sess_token":"...","login_need_refresh":true}
```

Helper Python completo en `/tmp/attack2.py` (no commitable, usa `sess_state.json`).

---

## 2. Endpoints probados con sesión `user/45788798`

| Endpoint | Método | Resultado |
|---|---|---|
| `?_type=menuData&_tag=devauth_accountmgr_lua.lua` | GET | ✅ devuelve solo nuestra fila `IGD.AU2` |
| ↑ mismo con `_InstID=IGD.AU1` | GET | ✅ devuelve **fila admin** (Right, ChgPwd flag) → **IDOR de lectura confirmada** pero solo metadata, NO pwd |
| ↑ POST con `Right=2` (no-op) | POST | ✅ `IF_IRET=0` SUCC |
| ↑ POST con `Right=0` (escalación) | POST | ❌ "contraseña anterior es un error" (genérico para wrong-pwd Y wrong-role) |
| ↑ POST con `_InstID=IGD.AU1, Username=admin, Right=0` | POST | ❌ idem |
| `?_type=menuView&_tag=Upgrade` | GET | ❌ 404 (página no en menu del rol user) |
| `?_type=menuData&_tag=do_firmware_upgrade.lua` | POST multipart | ❌ SessionTimeout (rol insuficiente) |
| `?_type=menuData&_tag=do_restore_usrcfg.lua` | POST multipart | ❌ SessionTimeout |
| `?_type=menuData&_tag=updownload_prevent_ctl.lua` | GET | ❌ SessionTimeout |
| `?_type=menuData&_tag=firewall_homepage_lua.lua` | GET | ✅ funciona (menu propio de user) |

---

## 3. Por qué falla la escalación de role en chpwd

`Page:__checkRightPassed` y `Area:__checkRightPassed` en `menu_tree_mgr.lua` calculan:
```lua
isRightsMeeted(userRight, resourceRight) = bit_(userRight - 1) of resourceRight
```
Bitmask:
- `right=0` → cualquiera
- `right=1` (`0001` binario) → solo bit 0 = userRight=1 = admin
- `right=2` (`0010`) → bit 1 = userRight=2 = user (limited)
- `right=3` (`0011`) → admin O user

**`/home/httpd/webmodules/config/dmenu.lua` define los rights por menú**.
**`/home/httpd/webmodules/config/dmenu_modifier.lua` los OVERRIDE** — específicamente `usrCfgMgr` baja de 3→1 (cierra acceso al user).

| Menú | dmenu | dmenu_modifier (override) | Acceso user (right=2) |
|---|---|---|---|
| `firmwareUpgr` | 1 | – | ❌ |
| `usrCfgMgr` | 3 | **1** | ❌ (perderíamos por el modifier) |
| `remoteMgr` | 1 | – | ❌ |
| `logMgr` | 1 | – | ❌ |

**Patch teórico** (si tuviéramos shell): editar offset `0x442-0x44A` de `dmenu_modifier.lua` (bytecode Lua 5.1) — cambiar el `1.0` que setea para `usrCfgMgr` a `3.0` (`03 00 00 00 00 00 00 f0 3f` → `03 00 00 00 00 00 00 08 40`). Restaura acceso a `do_restore_usrcfg.lua` para user.

---

## 4. cspd C-side (no tiene role check útil)

- **`callUploadDownloadProc`** (en `httpd!0x4fbb8`): solo valida tipos Lua + `changeLocked` flag. Cero check de user/right.
- **`my_upload_file`** (en `httpd!0x4c9a4`): parsea multipart, llama `GetUploadFileEntryItem(name)`, stream a path del entry. Sin role gate.
- **El role check vive 100% en el dispatcher Lua** antes de llegar a `cmapi.callUploadDownloadProc`. La C-side trustea lo que pasa el Lua.
- **Falsa pista**: `writeUserRight2ConfFile`/`userRight=%s` strings en cspd están dentro de `writeVsftpdCfgFile` (FTP user provisioning), nada que ver con uploads.

**Conclusión §4**: NO hay bypass C-side. Todo el camino del exploit depende de la Lua VM o de patchear `dmenu_modifier.lua`.

---

## 5. Decryption keys + crypto material (referenciar memoria)

Ver memoria persistida:
- [`zte_hardcode_vault_keys.md`](../../.claude/projects/.../memory/zte_hardcode_vault_keys.md) — AES-256-ECB key (`0x02660x0008` + `H3600V90_DIGI` + zero-pad), descifra `/etc/enwebdhardcodefile` (RSA priv) y `/etc/enhardcodefile` (cred vault: hgw, admin@ZTE2020, !@#$%12345 WiFi PSK, etc.)
- [`digi_h3600_universal_creds.md`](../../.claude/projects/.../memory/digi_h3600_universal_creds.md) — `H3600V9key`/`H3600V9IV` derivan keys del default-cfg (decifra `/etc/db_default_auto_cfg_H3600.xml`); contiene ACS URL `tr069-1.s.digimobil.es:9191/web/tr069`, ConnReq creds `itms/fn3f8vz9`, factory creds `admin/Haikui_V2` + `admin/Haikui_V2_cli` (no usables tras provisioning).
- [`aes_key_discovered.md`](../../.claude/projects/.../memory/aes_key_discovered.md) — rootfs AES key `H36000e71071c440`.

---

## 6. Pre-auth handlers — RESULTADOS DEL TEST (2026-05-04)

Auditoría inicial de `hidden_table_conf.lua` + `login_table_conf.lua` sugería que estos handlers no tenían `needLogin=true`. **Test live demostró que TODOS están gated por la routing layer**:

| URL | Resultado live test (sin login) |
|---|---|
| `GET ?_type=hiddenData&_tag=sntp_data` | ❌ SessionTimeout |
| `POST ?_type=hiddenData&_tag=sntp_data` (NtpServer1=evil) | ❌ SessionTimeout |
| `GET ?_type=hiddenData&_tag=accessdev_data` | ❌ SessionTimeout |
| `?_type=hiddenData&_tag=login_captcha_lua` etc. | – Archivo no existe (dead code) |

**Conclusión §6**: El análisis estático del agente no captó que `checkBackEndFile`/`Page:__checkRightPassed` corren ANTES del dispatch del handler para CUALQUIER `_type` excepto `loginData` específicos. La constante pool sin `needLogin=true` no implica unauth.

**`filterIllegalPath`** bloquea path traversal (`%.%.%/`) y rechaza `.lua` extension en `_tag`. Sin require arbitrario.

**Endpoints REALMENTE pre-auth** (verificados en ambas direcciones):
- `loginData/login_token` — devuelve salt
- `loginData/login_entry` — login POST
- `loginData/logout_entry` — logout
- `loginData/modeswitch_entry` — ¿quizá útil? requiere `csrf_check`, no testeado aún

**Negativo confirmado**: NO hay pre-auth config-write ni pre-auth info-disclosure útil en el web admin. Cualquier ataque debe partir de una sesión autenticada (mínimo `user`).

---

## 9. Capabilities confirmadas del rol `user` (live tested)

| Capability | Endpoint | Confirmado |
|---|---|---|
| **Reboot device** | `POST /?_type=menuData&_tag=devmgr_restartmgr_lua.lua` body `IF_ACTION=Restart&_sessionTOKEN=<tmptoken_from_rebootAndReset>` + Check header | ✅ 2026-05-04 — HTTP 200 SUCC, ping cae T+5s, vuelve T+53s. SIN role check en el handler. |
| IDOR read en accountmgr | `GET _type=menuData&_tag=devauth_accountmgr_lua.lua?_InstID=IGD.AU1` | ✅ devuelve `Right` y `ChgPwd` flag de admin |
| Edit propio pwd (Right=2 no-op) | POST devauth_accountmgr_lua | ✅ |
| ~~Edit URL filter, IP filter, DMZ, SNTP, samba, DHCP~~ | varios endpoints | ❌ FALSE POSITIVE — los `_m.lua` son solo READ models, los WRITE handlers `_lua.lua` están admin-only. Confirmado 2026-05-04 con sntp_lua.lua (SessionTimeout para user). |

### Superficie LAN del device — port scan 2026-05-04

Solo **3 puertos abiertos** desde LAN (`192.168.1.1`):
- TCP 53 (DNS resolver)
- TCP 80 (HTTP redirect a HTTPS)
- TCP 443 (HTTPS web admin)

**Cerrados/firewalleados**: SSH 22 (FWSC lan_ssh DROP), FTP 21, Telnet 23, Samba 139/445, TR-069 ConnReq 7547, mDNS, SSDP, UPnP, SLP. Sin servicios de discovery escuchando.

**Implicación**: aunque el config tenga otras cuentas (FTP `admin/admin`, Samba `admin/Haikui_V2_samba`, CLI/SSH `admin/Haikui_V2_cli`), **los servicios no escuchan en LAN**. Setup de fake servers (NTP, ACS, etc.) tampoco funciona porque el device no broadcastea ni resuelve hostnames de management vía DNS LAN. La única superficie real es el web admin.

### Patrón crítico — `_m.lua` vs `_lua.lua` (descubierto 2026-05-04)

ZTE separa cada tabla en **dos archivos**:
- `<entity>_m.lua` = **READ model** (definición de fields para el view) → puede aparecer en menú user
- `<entity>_lua.lua` = **WRITE handler** (CRUD via `IF_ACTION=Apply`) → typically admin-only

Confirmado live con SNTP:
- `sntp_m.lua` aparece en `sntpMenu` → user puede LEER (returns CurrentLocalTime, NtpServers)
- `sntp_lua.lua` (write handler) → SessionTimeout desde sesión user

**Implicación**: el audit del menú user que listaba "user puede editar firewall/dhcp/dmz/etc" fue **false positive**. Esos handlers son READ-only models. Los writes correspondientes (`_lua.lua` suffix) están todos admin-gated. La sandbox está cerrada.
| Right escalation (chpwd con Right=0/1) | POST devauth_accountmgr_lua | ❌ rechazado |
| Subir firmware/config/cert | do_*.lua endpoints | ❌ SessionTimeout |

---

## 7. Audit binario de memory corruption (cerrado, 2026-05-04)

Scripts en `tools_re/`:
- `find_unsafe.py` / `find_unsafe2.py` — escanea cspd ARM disasm por strcpy/sprintf/sscanf en buffer stack pequeño. Cubrió 5584 funciones, encontró 30+ candidatos.
- `find_global_writes.py` — escanea writes a globals .data/.bss. 65 sitios totales (14 en httpd, 51 en cspd).
- `build_callgraph.py` — call-graph reverso para tracer reachability.
- `dump_context.py` — dump disasm con bound-check check para verificar exploitability.

**Resultados**:
- Confirmados sweet spots del usuario: `ddnsMain @ 0x27790` (4 sprintf en 156B buffer) y `writeVsftpdCfgFile @ 0x925f8` (6 sprintf en 256B buffers). Toman data de config files (admin-controlled), NO de input web directo.
- Top stack candidatos descubiertos: `IPIFSetOverridedDNS @ 0xa844c` (strcpy en 124B), `SntpDefGwHandle @ 0x111240` (strcpy en 88B), varios `Route*HandleMsg` con strcpy en 16B desde 472B src. Todos triggereados por eventos kernel netlink, NO por POST web.
- Global writes (.data/.bss): TODOS bounded — `csProcSocketReadMsg` (cmp r2,#4096; bhi exit), `g_sLineBuffer` en my_upload_file (cmp r6,#1023; beq exit), todos los `_*Init` memcpy son length-hardcoded desde .rodata.

**Veredicto memory corruption**: descartado como vector remoto. El stock está bien reforzado en handlers expuestos a red. ZTE aplicó length checks consistentes.

## 8. Próximos pasos concretos

1. **SPI NAND clip programmer** (Plan A) — universal, ~$10 hardware, abre carcasa, dump+flash. Independiente de pwd, indep de cualquier bug. Camino recomendado para distribución de OpenWrt a usuarios finales.
2. **Esperar respuesta de Digi a pedido GPL** (ya cursado por mail). Si dan fuentes → puerto trivial.
3. **Si Digi pushea V9.1.x via TR-069** → re-auditar. Regression bugs comunes en updates.
4. **Path UART** sigue válido para nuestro device de desarrollo (`Boot4128s!` U-Boot pwd ya documentado).

---

## 8. Scripts útiles que YA existen

| Path | Qué hace |
|---|---|
| `/tmp/attack2.py` | Login + warmup + chpwd attack helper (sesión user) |
| `/tmp/test_fwupload.py` | Probe POST a do_firmware_upgrade / do_restore_usrcfg desde user |
| `/tmp/enwebdhardcodefile.dec` | Priv key RSA descifrada del web vault |
| `/tmp/enhardcodefile.dec` | Vault completo descifrado (cred plaintext) |
| `/tmp/default_h3600_dec.xml` | XML default cfg descifrado (admin/Haikui_V2, ACS URL, ConnReq) |
| `~/Projects/MYSELF/ZTE/H3600/cfg_tool.py` | Decode/encode/edit `config.bin` (FWSC, SSH, Telnet) — listo para subir si conseguimos endpoint |
| `~/Projects/MYSELF/ZTE/H3600/login.stock.firmware.har` | HAR del browser (login + chpwd) — referencia de bytes exactos |
