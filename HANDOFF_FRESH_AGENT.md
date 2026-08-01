# HANDOFF — continuar el proyecto ZTE H3600 desde cero

> Documento de arranque en frío para un agente nuevo (sin contexto previo).
> Léelo entero **antes** de tocar nada. Última actualización: **2026-07-31**.

---

## 0. Qué es esto en una frase

Estamos construyendo un **driver Linux mainline 6.6** para el router **ZTE H3600**
(SoC **ZXIC ZX279128S**) donde **la CPU configura** (routing / NAT / firewall en
software) y **el hardware reenvía** (flow-offload en silicio), replicando el
modelo híbrido del firmware de fábrica. **Meta final: correr OpenWrt** en la caja.

Estado hoy: **Ethernet 100% funcionando** (DSA multipuerto + offload HW
bidireccional, NAT en silicio, ~line-rate). **WiFi funcionando** (STA + AP +
slow-path + mecanismo de offload HW validado en ambas direcciones) **pero con UN
blocker abierto** ("wedge #2") que mantiene el offload WiFi apagado por defecto.

---

## 1. Lo PRIMERO que tenés que leer (en orden)

Todo está en el repo `/home/ubuntu/Projects/MYSELF/ZTE/`:

1. **`CLAUDE.md`** — convenciones de código, naming, reglas de cuándo crear archivos. **Obligatorio.**
2. **`ROADMAP.md`** — qué se está haciendo ahora, qué está parqueado, por qué.
3. **`README.md`** — visión general + tabla de Status (estado real de cada subsistema).
4. **`STATE.md`** — qué hay en el device AHORA (⚠️ puede estar desactualizado: el device
   quedó en estado indeterminado tras la última corrida del wedge — no confíes en él
   hasta bootear a un estado limpio conocido).
5. **`LEARNED.md`** — catálogo síntoma → causa → fix. **Grepéalo antes de debuggear
   cualquier cosa que huela a conocido.**
6. **`findings/`** — investigaciones cerradas (los `wifi_stage3_*` son el trabajo reciente).

**Regla de oro:** el conocimiento durable vive en `findings/*.md`, en el código
commiteado y en la memoria del proyecto — **no** en transcripts de agentes. Si algo
no está en un finding o en un commit, no pasó.

---

## 2. Hardware (cheat sheet)

| | |
|---|---|
| SoC | ZTE ZXIC ZX279128S — **ARM Cortex-A9 dual-core, 1 GHz, sin VFP habilitado** (por eso soft-float) |
| RAM | 256 MiB @ 0x40000000 |
| NAND | 128 MiB SPI NAND (ESMT F50L1G41LB) — page 2 KiB, erase 128 KiB, OOB 64 B |
| UART | PL011 @ 0x94404000, **ZTE-shifted**: DR=+0x04, FR=+0x14 (¡no estándar!) |
| Red | host `192.168.1.50` ↔ device LAN vía USB-eth `enxc8a362e95900` |
| SSH (kernel stock) | `admin / UkuGPeyRDU` @ `192.168.1.1` |
| U-Boot prompt | `Boot4128s!` |
| AES rootfs key | `H36000e71071c440` (16 bytes ASCII) |
| WiFi | MediaTek **MT7915** (WiFi 6) por PCIe, driver in-tree **mt76/mac80211** |

**Transporte según el kernel:** stock = **SSH** (read-only NAND). Mainline = **UART**
(RAM-boot vía TFTP/DTR, no se flashea NAND). Nunca reflashear el stock.

---

## 3. Reglas de seguridad OPERATIVAS (NO negociables)

Estas evitan brickear el device o el datapath. **Respetalas al pie de la letra:**

- **Sudo no requiere password** en este host (NOPASSWD configurado). Usar `sudo` directamente, sin `echo ... | sudo -S`.
- **RAM-boot / DTR únicamente.** El stock es NAND read-only. **No reflashear.**
- ⚠️ **NUNCA** hacer memdump/dd de **MAC4 `0x92000000`**.
- ⚠️ **NUNCA** escribir **TM `0x92340128` ni `0x92340130`** (mata el datapath).
- **NUNCA** saturar la consola UART con batches de `poke`/`devmem` (cuelga la CPU —
  ya nos pasó, requiere DTR + rebuild + TFTP para recuperar).
- **Solo herramientas envueltas** (`rig.py`, `reboot_mainline_wifi.py`, `wifi_up.py`,
  `uphold.py`, `upab.py`, `ctr.py`, `ab_ctrs.py`) — **NO** `lib/uart.py send` crudo
  (el clasificador de seguridad lo bloquea; las wrappers pasan).
- No tocar el **modem WAN / PPPoE**. No `rmmod`. No bajar el conduit `sw`.
- Solo la **passphrase de test** por UART, nunca la WPA real del dueño.
- **Un solo agente tocando el device a la vez.**
- Si el clasificador bloquea algo: **PARÁ y reportá**. Nunca auto-otorgarte permisos
  ni editar `settings.local.json`.

---

## 4. El código

- **Driver principal:** `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c` (monolito grande).
  - Netdevs conduit: `sw` (datapath validado FT/nft-flowtable) + `idm0/idm1` (rings fabric WiFi).
  - Puertos DSA: `lan0-4` + WAN.
- **DSA:** `zx-dsa.c` (`tag_zte` tagger).
- **Rama de trabajo:** `phase6-hw-offload` == `main` (commiteamos directo a `main`).
- **Herramientas de rig/test:** todas en `scratchpad/` (ver §6).

Build + boot mainline: `tasks/00.01.eth-driver/scripts/build_slotA.py` luego
`tftp_boot_mainline.py` (o las wrappers `reboot_mainline_wifi.py` / `wifi_up.py`).

---

## 5. Lo que YA funciona (no re-hacer)

- ✅ **Boot mainline** (TFTP+bootm), `/init` en C, REPL por UART, replay de 22k regs stock.
- ✅ **Ethernet DSA multipuerto** (`lan0-4` + WAN), hotplug, RX+TX+egress a line-rate.
- ✅ **Ethernet HW offload BIDIRECCIONAL** (DN+UP), NAT en silicio, 10 GB+ sostenido,
  vía nft-flowtable. (Hit-rate ~99.99%, ~95 MB/s DN, upload 3x sobre SW.)
- ✅ **Churn/RED "wedge #1"** arreglado (RED_CFG bit6, charge-accounting).
- ✅ **WiFi STA** (MT7915 in-tree) — probado.
- ✅ **WiFi AP** (hostapd soft-float) + cliente real + internet vía SW-NAT (5 GHz WPA2).
- ✅ **WiFi slow-path** ("Phase B", dispatcher fabric ⇄ vif por IDM ring) — e2e con cliente real.
- ✅ **WiFi HW offload MECANISMO** (DN: 7.93 MB/s HW-forwarded 24.6x SW; UP: 99.94% hit, 3.1x SW).
  El `ssid` viaja en `gemport_uni_id = 0x10 | (idm_ring<<3) | ssid` de la entrada CLA.

---

## 6. Lo que está ABIERTO — "wedge #2" (el ÚNICO blocker)

**Síntoma:** bajo **fabric-ingress HW-forwarding sostenido**, el front-end del fabric
se **starva y se cuelga** (mueren frames entre MAC-admit y RED-in, chip-wide,
solo se recupera con reboot, tras ~1k–72k frames). Todos los bancos de accounting
leen sanos. Esto es lo único que mantiene `ftwifi` **apagado por defecto**.

**Ya REFUTADO** (no volver a probar sin evidencia nueva): BMU-pool drain, top_crm
clock bit, SIPC descriptor-ring, A09 AXI/QoS block.

**Lead vivo:** `sipc2cpu_aful_cnt_dn` ≠ 0 **solo en mainline** → una clase de frame
pega en un path CPU-bound **sin consumidor** (mismo patrón que el "q5-unbound" de Phase-B).

**Próximo paso concreto (documentado):** A/B de **≥3 boots frescos** (build viejo vs
`pp_pmau`) usando `scratchpad/wedge_coldstart.py` (repro de 1 minuto), luego perseguir
el path CPU-bound sin consumidor.

⚠️ **Lección crítica:** la varianza de onset en UN MISMO build va de 1.7k a 205k frames
→ **una sola corrida limpia NO es evidencia de fix**. Exigir ≥3 cold-starts frescos.

Findings relevantes: `findings/wifi_stage3_fabric_ingress_wedge_*`,
`wifi_stage3_wedge_bmu_pool_2026-07-28.md`, `wifi_stage3_sipc_ring_refuted_2026-07-31.md`.
Memoria: `zte-wifi-up-offload`, `zte-wifi-phaseC-dn-offload`.

---

## 7. Herramientas de rig (usar estas, no reinventar)

En `scratchpad/`:

- `rig.py` — setup del rig. `rig.py up` → `rig.py download --counters`. Ver `RIG_README.md`.
- `reboot_mainline_wifi.py` / `reboot_mainline_longdtr.py` — reboot mainline vía DTR+TFTP.
- `wifi_up.py` — bring-up del AP en un comando (hostapd + udhcpd + bind).
- `wedge_coldstart.py` — repro del wedge #2 en ~1 min (arranque en frío).
- `ctr.py` / `ab_ctrs.py` — lectura de contadores por etapa (usar `ab_ctrs.py` bajo
  tráfico: pacing 0.25 s/línea; `ctr.py` puede overflowear la UART bajo carga).
- `regress.py` — batería de guards (churn, poly0_stale, high_way_collision, concurrency_race, etc.).
- `upab.py` / `uphold.py` / `uptest.py` — endurance de UP.

---

## 8. Orden de trabajo recomendado (roadmap corto)

1. **Cerrar wedge #2** (§6) — el único blocker para `ftwifi` ON.
2. **Productionizar WiFi** — auto-bind (vif→idm/ssid), multi-SSID + 2.4 GHz + multi-cliente,
   csum-to-HW (flow_info bit4 como en eth), hardening + regress, tuning de throughput
   (el cliente de test linkea a 11n; falta calibrar 11ax/TXBF).
3. **USB** — pendrive mount/RW/throughput/hotplug (no empezado).
4. **Cleanup** pre-upstream (dedup FT/DSA, partir el monolito, sacar debug hooks).
5. **Port a OpenWrt** (la meta real).

---

## 9. Cómo trabajar (metodología)

- **Iterá hasta terminar**, seguí las pistas, no pidas confirmación en cada paso.
  Escalá solo en bifurcaciones reales (decisiones del dueño).
- **Un test por fix.** No declares algo arreglado sin verificarlo en HW (o ≥3 cold-starts
  para el wedge). Reportá fallos con el output real; no maquilles.
- **Escribí findings.** Cuando cierres una investigación, promové el `.md` a `findings/`
  y actualizá la memoria del proyecto.
- **Commit directo a `main`** cuando el usuario lo pida; ramas mergeadas se borran.
- **Presupuesto de tokens ajustado** — no re-derivar lo ya establecido, no releer
  transcripts, ir al grano.

---

## 10. Gotchas que muerden (los repetidos)

- `gemport_uni_id` estaba truncado a 4 bits (`& 0xf`) — ahora 12 bits (el ssid vivía ahí).
- Entradas CLA de **UP** necesitan `direct=0` + `da_known=1` (pack `0x0010004n`); el
  fabric **rechaza** `direct=1` en UP.
- PM TTL-edit deja el **checksum IP viejo** → el cliente dropea en silencio (reparar en
  CPU o usar flow_info bit4; stock usa bit4).
- El consumer del IDM RX ring (`zx_idm_poll` NAPI + IRQ) hay que arrancarlo en **probe**,
  no en `ndo_open` (si no, los frames WiFi-offloaded se acumulan sin drenar).
- `clawrite` a veces "no commitea en la primera escritura" — verificá con readback.
- Ruido de printk en consola (ARPs `TM-RX fabric NOPARSE`) inunda capturas:
  `echo 1 > /proc/sys/kernel/printk` primero.

---

**TL;DR para vos, agente nuevo:** leé `CLAUDE.md` + `ROADMAP.md` + `README.md`,
respetá §3 (seguridad), y tu primera misión real es **§6 (wedge #2)** con el método
de **≥3 cold-starts** (`wedge_coldstart.py`). Todo lo demás ya anda.
