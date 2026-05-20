# PCIe ZX279128S Driver — Estado actual (2026-05-03 PM)

## 🎉 LINK UP — MT7915 enumerado

Tras encontrar el bug del GPIO base, el LTSSM entrena hasta L0 y el endpoint
MT7915 aparece en el bus PCIe.

```
[T] PERST# pulsed on pins 53+55 (bank 3 @ 0x944070C0)
[T] PCIe link up after 0ms
[T] PCIe Gen.1 x1 link up
[T] pci 0000:00:00.0: [1cf2:6830] type 01 class 0x060400   ← DWC bridge
[T] pci 0000:01:00.0: [14c3:7915] type 00 class 0x000280   ← MT7915 endpoint
[T]   BAR 0: assigned [mem 0x10000000-0x100fffff]
[T]   BAR 2: assigned [mem 0x10300000-0x10303fff 64bit pref]
[T]   BAR 4: assigned [mem 0x10304000-0x10304fff 64bit pref]
[T] LTSSM = 0x00228000   (bits[22:17] = 0x11 = L0)
```

## El bug que destrabó todo

Mi driver pulsaba PERST# en GPIO bank 3 vía `ioremap(0x944071C0, 0x40)`. RE de
la `pin_set()` de stock (`FUN_c01b1418`) reveló:
- GPIO base = `0x94407000` (verificado vía `zx_map_io` iotable de stock)
- bank stride = `0x40`
- bank 3 base = `0x94407000 + 3*0x40` = **`0x944070C0`** (NO `0x944071C0`)
- `0x944071C0` = bank 7 → no existe / no hace nada útil

→ Mi PERST# nunca tocaba los pines 53/55 reales. El endpoint MT7915
permanecía en reset y nunca respondía al training del controller, dejando el
LTSSM eternamente en `Detect.Quiet`.

## Resumen de fixes acumulados

| # | Fix | Impacto |
|---|-----|---------|
| 1 | Mover setup de `start_link` a `host_init` | DWC core podía leer DBI sin colgar |
| 2 | Retornar `-ENODEV` si LTSSM no llega a L0 | Evita hang en `iatu_detect` |
| 3 | Disable port 1 en DT (`status="disabled"`) | Evita hang del `setup_port1` |
| 4 | Fix register mapping: `0xb5` va a `pcie_crm[0x70]`, no `topcrm[0x70]` | Clocks PCIe se habilitan |
| 5 | OR `0x3CE00` a `topcrm[0x4C]` (SerDes lane mux) | PHY lanes asignadas a PCIe |
| 6 | OR `0x0FF1E000` a `topcrm[0x08]` (subresets) | Sub-bloques deasertados |
| 7 | OR `0x1AAB5` a `pcie_crm[0x70]` (no solo `0xb5`) | Clocks completos |
| 8 | Set `0x1B` en `pcie_crm[0x74]` (no solo bit 0) | PHY release completo |
| 9 | Set `0x28` en `soc_ctrl[0x00]` (bits 3 + 5) | Controller enable |
| 10 | Force `pcie_crm2[0x0C] = 0x250D05` (bits específicos) | Lane / iso config |
| 11 | Set bit 5 de DBI `[0x710]` (LTSSM_ENABLE manual) | Por si DWC core no lo hace |
| 12 | **Fix GPIO bank 3 addr → `0x944070C0`** | **PERST# real → endpoint despierta** |

Probable que algunos de los #5-#11 sean redundantes (U-Boot ya los dejaba
seteados) — el verdadero gatillo del link fue #12. Vale la pena simplificar
después una vez confirmado todo.

## Pendientes inmediatos

1. **Arreglar warning DT**: `pcieport 0000:00:00.0: of_irq_parse_pci: failed with rc=-22`
   → falta `interrupt-map` / `interrupt-map-mask` en el nodo `pcie0` del DTSI.
   Sin esto las INTx del endpoint no rutean — pero **MSI sí funciona** (ya se
   ve `PME: Signaling with IRQ 19`).

2. **Cargar mainline `mt76` + `mt7915e`** y firmware MT7915. El driver vendor
   ZTE no nos sirve (es kernel 4.1 con APIs viejas). Necesito:
   - `CONFIG_MT76_CORE=m`
   - `CONFIG_MT7915E=m`  
   - `mt7915_wm.bin` + `mt7915_wa.bin` + `mt7915_rom_patch.bin` en `/lib/firmware/mediatek/`
   - Build modules + transfer + insmod

3. **Considerar habilitar port 1**: el segundo PCIe lo dejamos disabled por el
   hang del setup_port1. Con todo lo aprendido, su setup probablemente sea
   simétrico al port 0 con offsets distintos. Hay un MT7916 al otro lado
   según orca.pet.

4. **Limpiar driver**: muchos writes son no-op porque U-Boot ya dejó esos
   bits. Vale la pena dejar solo lo estrictamente necesario:
   - PERST# pulse (bank 3 @ 0x944070C0, pines 53/55)
   - LTSSM_ENABLE en DBI[0x710]
   - Eventualmente: clocks/resets si U-Boot decide no setearlos en algún
     escenario.

## Sanity check — registros stock vs mainline

Tras todos los fixes, el estado de regs en mainline al final del setup
matchea stock (que está corriendo con link up):

| Reg | Stock running | Mainline post-driver |
|---|---|---|
| topcrm 0x08 | 0x1FF7FFFF | 0x1FF7FFFF ✓ |
| topcrm 0x24 | 0x10000000 | 0x10000000 ✓ |
| topcrm 0x4C | 0x3CFFF | 0x3CFFF ✓ |
| pcie_crm 0x70 | 0x1AAB5 | 0x1AAB5 ✓ |
| pcie_crm 0x74 | 0x1B | 0x1B ✓ |
| pcie_crm2 0x0C | 0x25B005 | 0x250D05 (bits 12,13,15 vs 8,10,11 — no bloquea link) |
| soc_ctrl 0x00 | 0x28 | 0x28 ✓ |
| soc_ctrl 0xDC | 0x220000 (L0) | 0x228000 (L0 + entered) ✓ |

## Workflow de iteración funcional

```
1. Edit pcie-zx279128s.c
2. cd linux-v6.6 && make M=drivers/pci/controller/dwc -j4   (~5s)
3. python3 uart_transfer.py build/.../pcie-zx279128s.ko /tmp/mod/pcie.ko  (~15s)
4. python3 uart.py send "rmmod pcie_zx279128s; insmod /tmp/mod/pcie.ko; dmesg | tail -30"
5. Iterar
```

Total: ~30s/ciclo, sin reboot.
