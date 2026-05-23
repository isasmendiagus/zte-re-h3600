# Stock-Port Debug Plan — Linux 4.1.25 con KGDB

**Objetivo final**: Tener un kernel ZTE-stock-compatible CON debug tools (KGDB+KPROBES+FTRACE) para hacer step-debug del driver propietario y descubrir qué config exacta hace que LAN→CPU funcione. Después aplicar findings al port mainline (linux-v6.6/).

## Por qué este approach

Despues de 14+ fixes aplicados con todo bit-perfect contra stock_eth.bin, HW data path queda silent. El "missing piece" vive en un sub-bloque (sbrg/spa/sadm) cuya indirect RAM **stock kernel protege via /dev/mem** (crashea SSH cuando intentamos leer TM region).

Stock 4.1.25 kernel está **completamente despojado de debug tools**:
- `# CONFIG_KGDB is not set`
- `# CONFIG_KPROBES is not set`
- `# CONFIG_FUNCTION_TRACER is not set`

Por eso necesitamos rebuilder con esos activos.

## Estructura de carpetas

```
H3600/
├── linux-v6.6/             ← mainline actual (NO TOCAR — port futuro)
├── linux-stockport/        ← NUEVO: vanilla 4.1.25 + ZTE patches + KGDB
└── stockport-build/        ← out-of-tree build dir (objects/uimg)
```

## Fuente del kernel

**Plan A**: Vanilla `linux-4.1.25.tar.xz` de `https://cdn.kernel.org/pub/linux/kernel/v4.x/`

**Plan B** (si encontramos): GPL source release de ZTE que matche. Búsqueda preliminar muestra que ZTE H3600 fuente kernel NO está públicamente disponible. Skip.

## Fases

### FASE 1 — Base setup (1 día estimado)

1. **Descargar y extraer** `linux-4.1.25.tar.xz`
2. **Crear copia working** en `H3600/linux-stockport/`
3. **Cross-build verificación vanilla**: compila kernel pristine con `vexpress_defconfig` o similar — confirmar toolchain OK
4. **Port board file**: 
   - Copiar `arch/arm/boot/dts/zte/zx279128s.dtsi` de linux-v6.6 → adaptar syntax si necesario
   - Crear/portar Kconfig + Makefile entries
5. **Port clock/power drivers básicos** del mainline (TOPCRM enable bits, etc) si el board file los requiere
6. **Crear `zx279128s_defconfig`** con:
   - `CONFIG_KGDB=y`
   - `CONFIG_KGDB_SERIAL_CONSOLE=y`
   - `CONFIG_KPROBES=y`
   - `CONFIG_DYNAMIC_FTRACE=y`
   - `CONFIG_FUNCTION_TRACER=y`
   - `CONFIG_MAGIC_SYSRQ=y`
   - Mismo subset que `stock_config.gz` para máxima compatibilidad
7. **Build**: `make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- zImage modules`

### FASE 2 — Boot test SIN flashear (1 día)

8. **Generar uimg** combo (`mkimage -A arm -T kernel -C none -a 0x42000000 ...`)
9. **TFTP boot via U-Boot** — usar el path ya conocido de nuestro uart.py
10. **Verificar kernel boot básico**: llega a init / shell
11. **Verificar debug tools**:
    - `ls /sys/kernel/debug/kgdb`
    - `ls /sys/kernel/debug/tracing/`
    - `cat /sys/module/kgdboc/parameters/kgdboc`
12. **Solo si todo OK** considerar flashear NAND (Fase 5)

### FASE 3 — Cargar stock .ko's (1-2 días)

13. **Initramfs con stock kmodules**: empaquetar `/H3600/rootfs/kmodule/*.ko` en initramfs custom
14. **insmod en orden conocido**: `plat-zxylzb_9128S.ko` → `switch.ko` → `tm.ko` → `idmfdb.ko`
15. **Verificar ABI**: pueden fallar si stock kernel tiene patches que vanilla no. Si falla:
    - Buscar undefined symbols → analizar qué patches stock tiene → portar
    - Backup plan: re-RE los .ko más críticos como source

### FASE 4 — Debug session productiva (días)

16. **Habilitar KGDB-over-UART**:
    ```
    echo ttyAMA0,115200 > /sys/module/kgdboc/parameters/kgdboc
    echo g > /proc/sysrq-trigger     # rompe a kgdb stub
    ```
17. **Connect from host**: `arm-linux-gnueabi-gdb vmlinux` + `target remote /dev/ttyUSB1`
18. **Dumpear sub-block indirect RAMs sin crash**:
    - `monitor read 0x92348014`, etc — gdb mem access es safe
    - Vmos sbrg / spa / sadm RAMs completas
19. **Set breakpoints**:
    - `b pon_tm_net_int` — ver cada RX IRQ que dispara stock
    - `b sw_set_default_mulrule` — ver setup de trap rules
    - `b zte_api_sw_qos_add_port_streamselect` — entrar al detalle de qué regs escribe
20. **Setear `pon_tm_net_debug = 1`** vía `set *(int*)0xbf036320 = 1` desde gdb → printk por cada packet RX → ver QUÉ packet pasa

### FASE 5 — Apply findings al mainline (1 día final)

21. **Documentar exactamente** qué regs/RAMs stock escribe para el trap setup
22. **Trasladar a `linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c`**
23. **Test ping bidi en mainline** — listo
24. (Opcional) flashear stock-with-KGDB a NAND para debug futuro

## Riesgo y mitigación

| Riesgo | Mitigación |
|---|---|
| Brick por flash malo | NO flashear hasta verificar TFTP-boot. Recovery via UART serial U-Boot. |
| ABI mismatch stock .ko vs nuestro kernel | Mantener mismo subset de CONFIG, mismo gcc version. Backup: RE más .ko |
| Vanilla 4.1.25 le falta drivers (UART, clock, GPIO) que stock patcheó | Portar de linux-v6.6 (donde sí ya tenemos) — esfuerzo medio |
| Vanilla 4.1.25 deprecated, build issues con toolchain moderno | Usar arm-linux-gnueabi-gcc-8 o más viejo si necesario |

## Esfuerzo realista

- **Optimistic**: 3-5 días — si stock .ko cargan sin issues
- **Realistic**: 1-2 semanas — porting+debug iter
- **Pessimistic**: 3-4 semanas — si stock .ko requieren extensive patching

## Decisiones a tomar antes de arrancar

- [ ] **OK con vanilla 4.1.25 (no ZTE GPL)**: confirmado por usuario
- [ ] **Carpeta separada `linux-stockport/`**: confirmado por usuario
- [ ] **Riesgo flash → only after verify**: confirmado por usuario
- [ ] **Empezar con FASE 1 ahora**: pending

## Checkpoint criteria

Saltar a FASE 5 (apply al mainline) si en FASE 4 podemos:
1. Stepear stock `pon_tm_net_int` en gdb
2. Dumpar SBRG indirect RAM contents
3. Identificar UN reg/RAM/bit que stock setea para trap pero nuestro driver no

---

## Build — `linux-stockport/build.sh`

One script handles the full build/deploy cycle:

```bash
cd ~/Projects/MYSELF/ZTE/H3600/linux-stockport
./build.sh                # shim + kernel + deploy to TFTP root
./build.sh shim           # only zte_shim.ko (~5 s)
./build.sh kernel         # only kernel uImage (~1m20s on 8 cores)
./build.sh deploy         # only copy uImage_stockport to tftp dir
./build.sh clean          # mrproper (forces full rebuild)
```

After `./build.sh`, test:
```bash
cd ~/Projects/MYSELF/ZTE/H3600
python3 uart.py auto_bootm_stockport
```

### Toolchain
- **Required**: `~/toolchains/armv7-eabihf--glibc--stable-2018.11-1` (Buildroot GCC 7.3)
- **Why not system arm-linux-gnueabihf**: GCC 13 breaks 4.1.25 inline-asm macros;
  hard-float ABI also rejects `-march=armv7-a` without explicit FPU spec.
- **Download**: https://toolchains.bootlin.com/downloads/releases/toolchains/armv7-eabihf/tarballs/
  - file: `armv7-eabihf--glibc--stable-2018.11-1.tar.bz2`

### Config knobs the script PINS (olddefconfig regresses some silently)

| Knob | Value | Why |
|---|---|---|
| `CONFIG_ARCH_ZX` | **NOT set** | **DO NOT enable** — flips `arch/arm/include/debug/pl01x.S` to ZTE shifted offsets (DR=+0x04, FR=+0x14). Those are for the OTHER UART on this SoC. Our console UART at 0x94404000 uses STANDARD PL011 layout (matches U-Boot console). With `ARCH_ZX=y` the early console goes silent right after "Starting kernel...". |
| `CONFIG_ARCH_MULTI_V7` | `y` | generic ARMv7 multi-platform — sufficient, no mach-zx needed |
| `CONFIG_PHYS_OFFSET` | `0x40000000` | RAM base; ARM_PATCH_PHYS_VIRT is off in our config |
| `CONFIG_UNINLINE_SPIN_UNLOCK` | `y` | exports `_raw_spin_unlock`; stock .ko need it |
| `CONFIG_INITRAMFS_SOURCE` | `/tmp/initramfs_stockport` | bundles init + .ko's into uImage |
| `LOADADDR` (env) | `0x40008000` | stock ZTE convention; mainline 0x42000000 hangs bootm |

### Kernel source patches (already applied)

Four `EXPORT_SYMBOL` additions for stock-.ko compatibility:

| File | Symbol | Why |
|---|---|---|
| `kernel/kallsyms.c:316` | `kallsyms_lookup` | tm.ko / switch.ko `__print_symbol` calls |
| `kernel/pid.c:464` | `find_task_by_vpid` | switch.ko process-tracking debug code |
| `arch/arm/kernel/traps.c:220` | `show_stack` | switch.ko BUG-on paths |
| `.config` `UNINLINE_SPIN_UNLOCK=y` | `_raw_spin_unlock` | almost all stock .ko |

### Shim (`linux-stockport/zte_shim/zte_shim.c`)

**~40 symbols** that ZTE compiled built-in to their kernel but stock .ko need at insmod time:

- **Globals** (11): `pdt_mem_size`, `product_vid`, `u32_BP_SIZE`, `u32_BPPE_POOL_SIZE`,
  `u32_JUMBO_BP_SIZE`, `u32_JUMBO_BPPE_POOL_SIZE`, `ZX_RESERVE_MEM_SIZE`, `g_sw_cap`,
  `g_switch_debug_level`, `WlanIndex2WlanIdmMap`, `IfName2WlanIdmMap`
- **Functions** (~29 stubs): `__alloc_skbuff`, `skb_recycle`, `dma_cache_maint`,
  `ffe_*` (3), `temp_ctrl_read`, `zte_get_pon_mode`, `zx_mdio_read/write`, `Csp*` (3),
  `Kernel_ASEND`, `LedActionSet`, `npu_register_driver`, `register_bridge_notifier`,
  `wlan_to_idm_map`, `sw_public_*_func_reg` (7), `fuc_table_node_*` (2),
  `hw_watchdog_reset`, `br_lookup_mfd`

**DO NOT** add globals like `g_tm_init_flag`, `lan_up`, `g_pon_work_mode`, `DN_MAX_FAST_ENTRY` —
those are EXPORTED by stock `plat-zxylzb_9128S.ko` / `tm.ko`. A shim stub of wrong size
shadows the real one and crashes at offset-access (we saw `g_tm_init_flag+0x1c/0xfffff3cc`).

### Load order in initramfs `/tmp/initramfs_stockport/init`

```
memlog → regtracer → zte_shim → zx_ponreg → plat → tm → switch → idmfdb
```

### TFTP serving

In-house `tftpd-hpa` runs as `sudo in.tftpd … /home/ubuntu/Projects/MYSELF/ZTE/H3600/tftp`.
**NOT** `/srv/tftp/` (despite Debian default). `build.sh deploy` puts the file in the
right place.

---

## Session 2026-05-21 — Stockport kernel finally booting!

After ~14 prior boot attempts ending in silent hangs, the kernel now reaches userspace-handoff territory. Key fixes from this session:

### Root cause of all silent boots: 4 configuration mistakes

We had to extract `/etc/autokernelconf` from the running stock device (rootfs ships its own kernel `.config`!) to learn the correct values. Diff vs what we had:

| Knob | Stock truth (autokernelconf) | What we had (broken) |
|---|---|---|
| `CONFIG_ARCH_ZX279128S=y` | y | renamed to `CONFIG_ARCH_ZX` ❌ |
| `CONFIG_MACH_ZX279128S=y` | y | renamed to `CONFIG_SOC_ZX279128S` ❌ |
| `CONFIG_DEBUG_LL=y` | y | not set ❌ |
| `CONFIG_DEBUG_LL_UART_PL01X=y` | y | not set ❌ |
| `CONFIG_DEBUG_UART_PHYS=0x94404000` | 0x94404000 | not set ❌ |
| `CONFIG_DEBUG_UART_VIRT=0xf0704000` | **0xf0704000** | mach-zx hard-coded `0xf0404000` ❌ |
| `CONFIG_ARM_APPENDED_DTB` | not set (uses ATAGs!) | we'd been trying DTBs ❌ |
| Machine ID from bootloader | **0x44258** (= 279128 dec) | we only had `~0` (DT-only) ❌ |

After fixing all 8: kernel decompressor prints, `Booting Linux on physical CPU 0x0`, version line, bootconsole, memory init — all visible on UART.

### Critical insight: stock uses ATAGs, NOT DTB

`CONFIG_ARM_APPENDED_DTB` is NOT set in stock. The bootloader (cspstart) passes ATAGs with `r1 = 0x00044258`. Our `DT_MACHINE_START` macro registers a descriptor with `.nr = ~0`, which only matches when a DTB is present. To boot with ATAGs we had to register a second descriptor:

```c
static const struct machine_desc __mach_desc_ZX279128S_ATAG __used
__attribute__((__section__(".arch.info.init"))) = {
    .nr     = 0x44258,                 /* exact value cspstart passes in r1 */
    .name   = "ZTE ZX279128S (ATAG)",
    .map_io = zx_map_io,
};
```

`0x44258` is the H3600's `product_vid` baked into firmware (also visible in U-Boot log: `product_vid = 32-h1600`, where 0x32 is the variant code — different from the mach number).

### Current blocker: no timer/clocksource registered

```
sched_clock: 32 bits at 100 Hz, resolution 10000000ns
Console: colour dummy device 80x30
Calibrating delay loop...  ← HANG
```

`100 Hz, 10 ms resolution` is the jiffies fallback when no real clocksource registered. Our minimal mach-zx only provides `.map_io`. Stock's `MACH_ZX279128S` has `.init_time` that hardcodes Cortex-A9 global timer / TWD via PERIPHBASE registers.

Next step: read `/proc/iomem` + `/proc/interrupts` from running stock to extract PERIPHBASE, then add equivalent `.init_time` to our machine descriptor.

### What changed in this commit

1. `arch/arm/mach-zx/Kconfig` — renamed `ARCH_ZX → ARCH_ZX279128S`, `SOC_ → MACH_`
2. `arch/arm/mach-zx/zx279128s.c` — fixed `ZX_UART0_VIRT` (0xf04...→0xf07...), added ATAG machine descriptor with `.nr=0x44258`
3. `arch/arm/include/debug/pl01x.S` — symbol name updates
4. `arch/arm/Makefile`, `arch/arm/boot/dts/Makefile`, `arch/arm/boot/compressed/head.S` — symbol name updates
5. `linux-stockport/build.sh` — pin all DEBUG_LL knobs + ATAG mach naming, removed DTB-append (stock doesn't use it)
6. `uart.py` — `auto_bootm_stockport` reverted to single-arg `bootm`, simpler bootargs
7. `kernel/locking/spinlock.c` — `_raw_spin_unlock` exported unconditionally (for stock .ko)
8. `kernel/kallsyms.c`, `kernel/pid.c`, `arch/arm/kernel/traps.c` — `EXPORT_SYMBOL` for 4 symbols stock .ko need
9. `linux-stockport/zte_shim/zte_shim.c` — trimmed to 40 truly-missing symbols (was duplicating stock-owned globals)
10. `STOCK_DEBUG_INFRASTRUCTURE.md` — discovered `/proc/tm/shell` + `/dev/logger_main` debug REPL on stock

### Boot progression (timeline of what works now)

```
[bootloader]
  cspstart → U-Boot 2013.04 → autoboot interrupted by uart.py DTR reset
  tftp 0x42000000 uImage_stockport          ← 8.0 MiB
  setenv bootargs 'rdinit=/init ... loglevel=15 ignore_loglevel keep_bootcon ...'
  bootm 0x42000000

[stockport kernel, all UART output visible thanks to DEBUG_LL]
  Uncompressing Linux... done, booting the kernel.
  Booting Linux on physical CPU 0x0
  Linux version 4.1.25 (ubuntu@pc-work) (gcc 7.3.0 Buildroot 2018.08.1) #9 SMP
  bootconsole [earlycon0] enabled
  Memory: 248268K/262144K available (4829K kernel code, ...)
  ...
  sched_clock: 32 bits at 100 Hz             ← jiffies fallback (no real clock)
  Console: colour dummy device 80x30
  Calibrating delay loop...                  ← ☠ HANG (no timer interrupts)
```

---

## CORRECTION (Session 2026-05-21 cont.) — Stock DOES use APPENDED_DTB

Earlier section in this doc said "stock uses ATAGs, NOT DTB" — that was wrong.
Re-reading `/etc/autokernelconf` more carefully:

```
CONFIG_ARM_APPENDED_DTB=y                                ← APPENDED IS y!
CONFIG_ARM_ATAG_DTB_COMPAT=y                             ← convert ATAGs to DT properties
CONFIG_ARM_ATAG_DTB_COMPAT_CMDLINE_FROM_BOOTLOADER=y     ← cmdline from bootloader wins
```

**The real picture:**
- Stock zImage has a DTB appended to it (the kernel decompressor finds it).
- Stock kernel ALSO accepts ATAGs from bootloader; `ARM_ATAG_DTB_COMPAT` merges
  the ATAG cmdline and ATAG_MEM into the DT's `chosen/bootargs` and `memory`
  nodes, overriding what the DTB declared.
- DT-based machine resolution then picks `DT_MACHINE_START` whose `dt_compat`
  list matches the DTB root `compatible` string.

So `/proc/cpuinfo` shows `Hardware: ZTE ZX279128S (Device Tree)` — confirmed.

**For our stockport build:** turn ON `CONFIG_ARM_APPENDED_DTB=y` AND
`CONFIG_ARM_ATAG_DTB_COMPAT=y`, append the DTB to zImage, wrap as uImage.
The DT-based machine (`DT_MACHINE_START(ZX279128S_DT, ...)` with
`compatible="zte,zx279128s"`) will now be selected, and gets `.init_time` /
`.init_machine` from the DT clock/timer nodes for free — no need to hand-code
PERIPHBASE init in mach-zx.

### Result: kernel boots cleanly all the way to userspace

```
Uncompressing Linux... done, booting the kernel.
Booting Linux on physical CPU 0x0
Linux version 4.1.25 (gcc 7.3.0) #10 SMP Thu May 21 09:29:29 UTC 2026
Machine model: ZTE H3600 (ZX279128S) — first boot      ← from DTB
bootconsole [earlycon0] enabled
Memory: 248248K/262144K available
sched_clock: 64 bits at 24MHz, resolution 41ns          ← REAL timer (was 100Hz jiffies)
Calibrating delay loop... 94.61 BogoMIPS
CPU0: thread -1, cpu 0, socket 0, mpidr 80000000        ← SMP init
... rest of boot ...
[zte_shim] loaded — 40 truly-missing symbols (stripped from 50+, no duplicates)
[zte_shim] globals: u32_BP_SIZE=2304 pdt_mem_size=268435456 ZX_RESERVE_MEM_SIZE=64
```

Init script ran. memlog, regtracer, zte_shim, zx_ponreg all loaded clean.

### Next blocker: `plat-zxylzb_9128S.ko` NULL deref at init

```
Unable to handle kernel NULL pointer dereference at virtual address 00000008
Internal error: Oops: 17 [#1] SMP ARM
Modules linked in: plat_zxylzb_9128S(O+) zx_ponreg(O) zte_shim(O) regtracer(O) memlog(O)
```

`+8` offset on NULL = `someptr->field_at_offset_8`. Cause: plat ioremaps its
register bases via `of_iomap()` (confirmed by undef-syms `__arm_ioremap`,
`of_iomap`, `of_find_matching_node_and_match`, `irq_of_parse_and_map`). It
walks the DT looking for these compatibles:

```
zte,zx279128s-pon        ← PON IP block
zte,zx279128s-npp        ← Network Packet Processor
zte,zx279128s-pp         ← Packet Processor  
zte,zx279128s-tm         ← Traffic Manager
zte,zx279128s-idm        ← Internal Data Mover
zte,zx279128s-gephy      ← GbE PHY
```

Our current `tftp/h3600_stockport.dtb` ONLY has:

```
zte,zx279128s-eth        (mainline driver style)
zte,zx279128s-pcie
zte,zx279128s-dwc3
zte,zx279128s-topcrm
zte,zx279128s-pcie-crm
```

— so plat's `of_find_matching_node_and_match("zte,zx279128s-pon", …)` returns
NULL, plat dereferences it → BUG.

### Next step

Add the 6 missing nodes (`zte,zx279128s-{pon,npp,pp,tm,idm,gephy}`) to our
DTS, with `reg` properties pointing at the actual register windows we know
from `/proc/iomem` on stock:

```
PON SoC region:  0x92000000  (per fpga_write_reg formula = pon_base + offset*4)
TM region:       0x9234c000  (32 KiB)
SBRG / SPA region: 0x9234e000 (region adjacent)
...
```

Pull stock's `/proc/iomem` (already captured above) for the rest.

---

## Updated config diff for stockport (final)

| Knob | Required value | Comment |
|---|---|---|
| `CONFIG_ARCH_ZX279128S=y` | y | mach-zx with DT_MACHINE_START |
| `CONFIG_MACH_ZX279128S=y` | y | DT-based machine descriptor |
| `CONFIG_ARM_APPENDED_DTB=y` | y | DTB appended to zImage |
| `CONFIG_ARM_ATAG_DTB_COMPAT=y` | y | bootloader cmdline overrides DT bootargs |
| `CONFIG_ARM_ATAG_DTB_COMPAT_CMDLINE_FROM_BOOTLOADER=y` | y | yes, from-bootloader form |
| `CONFIG_DEBUG_LL=y` | y | early UART before earlycon |
| `CONFIG_DEBUG_LL_UART_PL01X=y` | y | use pl01x.S (ZTE-shifted) |
| `CONFIG_DEBUG_UART_PHYS=0x94404000` | 0x94404000 | console UART phys |
| `CONFIG_DEBUG_UART_VIRT=0xf0704000` | **0xf0704000** | NOT 0xf0404000 (we had this wrong) |
| `CONFIG_DEBUG_LL_INCLUDE="debug/pl01x.S"` | debug/pl01x.S | source of asm UART macros |
| `CONFIG_EARLY_PRINTK=y` | y | hooks DEBUG_LL into early console |
| `CONFIG_UNINLINE_SPIN_UNLOCK=y` (or patched spinlock.c) | y | so stock .ko can resolve `_raw_spin_unlock` |

Plus the 4 EXPORT_SYMBOL kernel patches for `kallsyms_lookup`,
`find_task_by_vpid`, `show_stack`, `_raw_spin_unlock`.

---

## Boot recipe (verified working as of 2026-05-21)

```bash
# 1. Build kernel + shim + deploy
cd ~/Projects/MYSELF/ZTE/H3600/linux-stockport
./build.sh                                            # zImage+DTB+uImage_stockport

# 2. Run on device
cd ~/Projects/MYSELF/ZTE/H3600
python3 uart.py auto_bootm_stockport                  # DTR reset → U-Boot → tftp → bootm
```

`uart.py auto_bootm_stockport` does:
```
DTR reset
↓ U-Boot interrupted at autoboot countdown
setenv serverip 192.168.1.50
setenv ipaddr 192.168.1.1
setenv tftpblocksize 1468
tftp 0x42000000 uImage_stockport                      ← 8.27 MiB (zImage + DTB)
setenv bootargs 'rdinit=/init console=ttyAMA0,115200n8 earlyprintk
                 ignore_loglevel keep_bootcon loglevel=15 mem=256M
                 cma=16M@0x4e800000'
bootm 0x42000000                                       ← single arg, DTB is inside
```

ARM_ATAG_DTB_COMPAT then merges the bootargs (from `setenv` above) into the
DT's `chosen/bootargs` node, so the cmdline takes effect even though the DTB
might have its own default.

---

## VMSPLIT_3G — Memory layout mismatch (fixed 2026-05-21)

### What VMSPLIT is

ARM 32-bit kernels split the 4 GiB virtual address space between user mode and kernel mode. Where that split lives is `PAGE_OFFSET`:

| Config | PAGE_OFFSET | User space | Kernel space | Notes |
|---|---|---|---|---|
| `VMSPLIT_1G` | 0x40000000 | 0..1G | 1..4G | Rare |
| `VMSPLIT_2G` | 0x80000000 | 0..2G | 2..4G | Linux default |
| `VMSPLIT_3G` | 0xC0000000 | 0..3G | 3..4G | **Stock H3600 uses this** |

`PAGE_OFFSET` is also the start of the **kernel direct-map** for physical RAM: `virt = PAGE_OFFSET + (phys - PHYS_OFFSET)`. So with stock's `PAGE_OFFSET=0xC0000000` and `PHYS_OFFSET=0x40000000`, physical address `0x40000000` (start of RAM) appears in the kernel at virtual `0xC0000000`, and the 256 MB RAM extends through `0xCFFFFFFF`.

### Why it matters for plat-zxylzb_9128S.ko

`pon_tm_bmu_init` computes the BMU pool base **arithmetically**, not via ioremap. Disassembly:

```
0x83ec  push {r3..r9, lr}
0x83f0  movw r5, =ZX_RESERVE_MEM_SIZE    ; shim: 64
0x83f4  movw r4, =u32_BPPE_POOL_SIZE     ; shim: 256
0x83fc  movw r6, =pdt_mem_size           ; shim: 256MiB = 0x10000000
...
0x8404  ldr r2, [r5]     ; r2 = ZX_RESERVE_MEM_SIZE
0x840c  ldr r0, [r4]     ; r0 = BPPE_POOL_SIZE
0x8414  ldr r3, [r6]     ; r3 = pdt_mem_size
0x8420  lsl r0, r2, #20  ; r0 = ZX_RESERVE_MEM_SIZE << 20  (MiB → bytes)
0x8424  add r3, r3, #-0x40000000  ; r3 += 0xC0000000  (add PAGE_OFFSET in 2's complement)
0x8428  rsb r2, r0, r3   ; r2 = r3 - r0
0x842c  str r2, [LANCHOR0]   ; LANCHOR0 = pdt_mem_size + 0xC0000000 - reserve_bytes
...
0x8450  strh r0, [r2, lr]    ; *(u16*)(r2 + lr) = 0   ← CRASH on bad r2
```

Formula:

```
bmu_pool_base = pdt_mem_size + 0xC0000000 - (ZX_RESERVE_MEM_SIZE_MiB << 20)
              = 0x10000000  + 0xC0000000 - 0x4000000
              = 0xCC000000
```

This is the END of usable RAM minus the reserve region (carved out at the top of physical RAM for HW use). It only works if `PAGE_OFFSET == 0xC0000000`:

- With `VMSPLIT_3G`: `virt 0xCC000000 = phys 0x4C000000` — valid kernel-mapped RAM ✓
- With `VMSPLIT_2G` (what we had): `virt 0xCC000000` is in vmalloc/module area — unmapped → BUG ✗

### Root cause analysis lesson

**Stock kernel ships its own `.config` at `/etc/autokernelconf`.** I should have systematically diffed our config against that file from the very first build. Every "kernel goes silent" / "kernel oopses" issue this session traces back to a config flag we either had wrong or didn't pin. The next session below adds a diff tool to catch these going forward.

### Stock kernel config knobs that affect memory/init

From `/etc/autokernelconf`:

```
CONFIG_VMSPLIT_3G=y                        # PAGE_OFFSET = 0xC0000000 (NOT default 2G!)
CONFIG_PAGE_OFFSET=0xC0000000
CONFIG_PHYS_OFFSET=0x40000000              # RAM base
# CONFIG_ARM_PATCH_PHYS_VIRT is not set    # PHYS_OFFSET hard-coded above
CONFIG_NR_CPUS=2                           # SMP, dual A9
CONFIG_HZ_FIXED=100                        # 100 Hz timer
CONFIG_HZ_100=y
```


---

## Session 2026-05-21 cont. — Option C: probe `struct net_device` offsets

### Why

Plat-zxylzb_9128S.ko was compiled against stock kernel headers. The disasm
of `pon_tm_net_register+0x84` does:

```
ldr r1, [r4, #0x1DC]    ; r1 = netdev->FIELD_X  (FIELD_X at offset 476 in stock)
...
str r0, [r1]            ; *FIELD_X = some_pointer
```

The constant `0x1DC` is a **hardcoded byte offset** baked into the .ko by gcc
when it compiled. It corresponds to some field of `struct net_device` — most
likely `ml_priv` or one of the protocol-specific pointer fields like
`ax25_ptr` / `ip_ptr` / `dn_ptr` / `ieee80211_ptr`.

`struct net_device` size and field offsets depend on ~30 different
`CONFIG_*` flags. Even after adopting stock's `/etc/autokernelconf` as our
base, `make olddefconfig` strips some flags due to dependency cycles, and
ZTE may have header patches we don't have. So our `struct net_device`
layout differs from stock's, and the field plat thought was at +0x1DC is
somewhere else in our kernel → NULL deref → crash.

### What this probe does

Compile a tiny module against **our** kernel that prints:
1. `sizeof(struct net_device)`
2. `offsetof(...)` for every pointer field of `net_device`
3. Which field, if any, is at offset `0x1DC` in our kernel

With that information we can decide whether to:
- (A) Binary-patch plat.ko to use OUR offset (find/replace `0xDC 0x11`
  → new bytes)
- (B) Realign our `struct net_device` by enabling/disabling specific
  CONFIGs until `offsetof(ml_priv) == 0x1DC`
- (D) Provide our own `alloc_etherdev_mqs()` that returns a fake struct
  laid out the way stock expects

### How we know plat's offset

From `objdump -d plat-zxylzb_9128S.ko`:

```
0000952c <pon_tm_net_register>:
    9540:  mov   r0, #0xf8            ; sizeof_priv = 248
    9544:  bl    alloc_etherdev_mqs   ; returns netdev in r0
    9548:  subs  r4, r0, #0           ; r4 = netdev (NULL check)
    ...
    959c:  ldr   r1, [r4, #0x1DC]     ; r1 = netdev[476]    ← THIS
    95a4:  ldr   r0, [r2]             ; r0 = *LANCHOR2 (some plat global)
    95b0:  str   r0, [r1]             ; *r1 = r0    ← CRASH if r1=NULL
```

So stock expected `netdev[476]` to be a valid pointer.


### Probe results — OUR `struct net_device` layout

```
sizeof(struct net_device) = 1152 (0x480)

Field offsets (4.1.25 vanilla, our config):
   0x000 (0)   name
   0x1B0 (432) atalk_ptr
   0x1B4 (436) ip_ptr
   0x1BC (444) ip6_ptr
   0x1C4 (452) ieee80211_ptr
   0x1D0 (464) dev_addr           ← unsigned char *
   0x1D4 (468) _rx                ← struct netdev_rx_queue *
   0x1D8 (472) num_rx_queues      ← u32
   0x1DC (476) real_num_rx_queues ← u32 ★ THIS IS WHERE PLAT READS A "POINTER"
   0x1F0 (496) broadcast
   0x240 (576) _tx
   0x29C (668) ml_priv            ← void *
```

Plat reads offset 0x1DC expecting a pointer. In OUR kernel that's a `u32`
counter (value=1 by default). Then `str r0, [r1=0x00000001]` → translation
fault.

In stock layout, offset 0x1DC must be a real pointer field, almost certainly
`ml_priv`. The gap between stock's `ml_priv@476` and ours `ml_priv@668` is
**192 bytes** = 48 four-byte pointers. That accounts for most of the
delta in CONFIGs that add fields between `dev_addr` and `ml_priv`:
`CONFIG_RPS` (`_rx` queues), `CONFIG_NET_RX_BUSY_POLL`, `CONFIG_NET_CLS_ACT`,
`CONFIG_FCOE`, `CONFIG_TIPC`, `CONFIG_NET_DSA`, `CONFIG_RFS_ACCEL`, etc.

### Next step

Dump stock's actual netdev memory via `/proc/tm/shell` to confirm `ml_priv`
is at 0x1DC there:

```
# get address of stock's eth0 netdev (or any registered one)
echo -f __dev_get_by_name init_net,eth0 > /proc/tm/shell
# capture printk output via /dev/logger_main, get the address X
# then read 800 bytes at X
echo -F memcpy 0x80abcdef,$X,800 > /proc/tm/shell  # or use devmem2
```

If stock's ml_priv = 0x1DC confirmed, the fix is one of:
- **Option A (binary patch):** rewrite every `[r4, #0x1DC]` in plat.ko to
  `[r4, #0x29C]` (a few `sed` / hex-edit operations on the .ko file).
- **Option B (struct realign):** modify our `include/linux/netdevice.h`
  to add 192 bytes padding before `ml_priv` so it lands at 0x1DC. Breaks
  every other driver — only viable in a dedicated stockport kernel build.
- **Option E (live patch):** loader module that rewrites plat's `.text`
  before init runs.

Recommended: **Option A** — most surgical, lowest blast radius.


### Stock memory dump confirms the gap

Via `/proc/tm/shell` on running stock (using exported global `pon_tm_netdev = 0xce124800`):

```
addr        value          field (inferred)
0xce124800  0x006e6f70    "pon\0" — name
0xce12494C  0x000005dc    1500 — mtu
0xce1249C0  0xce170700    pointer (likely qdisc or header_ops)
0xce1249C8  0xcda1ba00    pointer
0xce1249DC  0xcd8b2788    pointer ★ field plat reads
0xce1249E0  0xcd8b2bc0    pointer
0xce1249E4  0x00000001    u32 queue count
0xce1249E8  0x00000001    u32 queue count
```

Stock layout has `_tx` + `_rx` (or similar) clustered into 0x1DC..0x1E8 (16
bytes of two ptrs + two counts). Our 4.1.25 vanilla layout splits them
(_rx@0x1D4, _tx@0x240) — total separation 96 bytes. ZTE compacted them
via custom kernel patches we don't have.

### Honest conclusion

Stockport's plat.ko requires ZTE's exact struct net_device layout, which
is **not derivable from the .config alone** — they have header patches.
Without stock kernel source, perfect ABI match is infeasible. The remaining
options to make plat.ko run unmodified are:

- **Binary surgery on plat.ko** to remap every offset it uses for ZTE's
  custom net_device → our standard one. Many instructions, fragile.
- **Custom kernel hack:** edit our `include/linux/netdevice.h` to compact
  the layout matching stock. Breaks every other driver.
- **Live patch loader module:** rewrites plat .text at insmod time.

All three are weeks of work with no guaranteed success.

### The pivot value

We already proved on stock kernel:
- `/proc/tm/shell` can call ANY kernel function (`-f sym arg1,arg2`)
- It can SET any global (`sym=val`)
- It can READ any memory address (`-l 0xADDR`)
- Output captured via `cat /dev/logger_main`
- Stock plat exports `pon_tm_netdev`, `idm_netdev`, all `fpga_*` funcs,
  all `tm_*` / `spa_*` functions

This is **a complete kernel-mode debugger on stock, without any
recompilation**. The original goal (capture init+TX register sequence
for mainline 6.6 port) is achievable here, today.

### Wins to keep regardless of pivot

1. **Stockport kernel boots to userspace.** Build via `linux-stockport/build.sh`.
2. **40 config knobs documented** in `STOCK_DEBUG_INFRASTRUCTURE.md`.
3. **`check_config_vs_stock.sh`** — diff our config vs stock systematically.
4. **`/proc/tm/shell` + `/dev/logger_main`** discovered as debug REPL.
5. **BMU formula** decoded: `pdt_mem_size + PAGE_OFFSET - reserve_bytes`.
6. **Init call graph** for plat: `zx_pon_init → tm_pon_tm_init →
   pon_tm_{bmu,dma,red}_init → pon_tm_net_init → pon_tm_net_register`.
7. **`netdev_probe.ko`** in `linux-stockport/netdev_probe/` — useful for
   any future struct-layout debugging.


---

## Session 2026-05-21 final — stock kernel disasm via /proc/tm/shell

### Breakthrough: read stock kernel function bytes via /proc/tm/shell

`/proc/tm/shell -l 0xADDR` reads any kernel address. Combined with kallsyms
(82K symbols visible on stock), we can extract assembly bytes of any kernel
function without recompiling.

Tool: `H3600/dump_stock_function.py SYMBOL N_BYTES` — dumps stock kernel
function disassembly to compare with our compiled equivalent.

Tool: `linux-stockport/struct_offset_diff.py` — analyzes dumps + finds
struct field offset differences.

### Key finding: struct layout shifts are NON-UNIFORM

After comparing `register_netdevice`, `alloc_etherdev_mqs`, `free_netdev`,
`netif_set_real_num_tx_queues`:

```
Stock offset → Ours offset (delta)
0x12C → 0x124  (Δ -8)   netdev_ops
0x138 → 0x130  (Δ -8)
0x180 → 0x174  (Δ -12)
0x294 → 0x294  (Δ  0)
0x420 → 0x418  (Δ -8)
```

ZTE did NOT just add fields at the top of the struct; they RE-ARRANGED
fields. No simple "shift by N bytes" fix exists. Every field plat
references needs individual stock→ours mapping.

### Implications

To make stock plat.ko load unmodified, we'd need either:
1. A complete field-by-field translation table + auto-patch ~60+ plat
   instructions
2. Modify our `include/linux/netdevice.h` to mirror ZTE's exact layout
   (would require knowing/guessing every shifted field)
3. Wrapper alloc_etherdev returning stock-shape struct + translation
   layer for every kernel call plat makes

All three are ~1-2 weeks of work with unclear success guarantee.

### Stop decision

For our goal (capture init+TX register sequences for mainline 6.6 port),
the stock kernel itself (already on NAND, all .ko's load natively) is
infinitely easier. We have `/proc/tm/shell` + `/dev/logger_main` as a
complete kernel REPL. See task #95.

### Tools archived for future stockport revisit

- `linux-stockport/build.sh` — full build pipeline
- `linux-stockport/check_config_vs_stock.sh` — config diff vs stock
- `linux-stockport/auto_patch_plat.py` — auto crash→patch→rebuild loop
- `linux-stockport/struct_offset_diff.py` — compare struct offsets
  function-by-function
- `linux-stockport/netdev_probe/` — kernel module probing our struct sizes
- `H3600/dump_stock_function.py` — dump stock kernel function bytes via SSH
- `/tmp/stock_dumps/` — captured stock kernel function disassemblies

