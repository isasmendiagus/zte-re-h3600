/* kmsg2uart_nolibc.S — pure ARM EABI syscalls, no libc.
 *
 * Behavior identical to kmsg2uart.c:
 *   - mmap /dev/mem at PL011 base 0x94404000 (one page)
 *   - open /proc/kmsg (or with --test, skip kmsg, just write banner)
 *   - loop: read /proc/kmsg, write each byte to DR at base+0x04
 *           polling FR at base+0x14 for !TXFF before each write
 *
 * Build:
 *   arm-linux-gnueabi-gcc -nostdlib -static -O2 -s -o out/kmsg2uart kmsg2uart_nolibc.S
 *
 * Why: gives a ~1 KB static ARM binary that doesn't need uClibc or glibc.
 * Static-linked glibc was 455 KB; this is ~30x smaller and fits in our
 * jffs2 budget.
 */

/* ARM EABI syscall numbers (per arch/arm/include/uapi/asm/unistd.h) */
.equ SYS_exit,    1
.equ SYS_read,    3
.equ SYS_write,   4
.equ SYS_open,    5
.equ SYS_close,   6
.equ SYS_mmap2, 192

/* mmap2 prot/flags */
.equ PROT_READ,    1
.equ PROT_WRITE,   2
.equ MAP_SHARED,   1

.equ O_RDONLY,  0
.equ O_RDWR,    2

.equ PL011_BASE_PAGE, (0x94404000 >> 12)   /* mmap2 takes page offset */
.equ PAGE_SIZE,        0x1000

.equ DR_OFF,  0x04
.equ FR_OFF,  0x14
.equ FR_TXFF, (1 << 5)

.section .rodata
mem_path:    .asciz "/dev/mem"
kmsg_path:   .asciz "/proc/kmsg"
banner:      .ascii "\r\n[kmsg2uart] alive — DR=0x94404004 (ZTE-shifted PL011)\r\n"
banner_end:
.equ banner_len, banner_end - banner
test_banner: .ascii "[kmsg2uart] --test: wrote banner, exiting.\r\n"
test_end:
.equ test_len, test_end - test_banner
test_arg:    .asciz "--test"
err_mem:     .ascii "kmsg2uart: open /dev/mem failed\n"
err_mem_end:
.equ err_mem_len, err_mem_end - err_mem
err_mmap:    .ascii "kmsg2uart: mmap PL011 failed\n"
err_mmap_end:
.equ err_mmap_len, err_mmap_end - err_mmap
err_kmsg:    .ascii "kmsg2uart: open /proc/kmsg failed\n"
err_kmsg_end:
.equ err_kmsg_len, err_kmsg_end - err_kmsg

.section .bss
.align 12          /* page-align so we can poke uart_base mapping */
buf:        .skip 4096

.section .text
.global _start
.align 2
_start:
    /* argc on top of stack; argv[0..] follows */
    ldr  r0, [sp]            /* argc */
    cmp  r0, #2
    blt  not_test
    /* argv[1] = sp + 8 */
    ldr  r1, [sp, #8]
    /* strcmp(argv[1], "--test") */
    ldr  r2, =test_arg
strcmp_loop:
    ldrb r3, [r1], #1
    ldrb r4, [r2], #1
    cmp  r3, r4
    bne  not_test
    cmp  r3, #0
    bne  strcmp_loop
    mov  r5, #1              /* test_mode = 1 */
    b    after_args
not_test:
    mov  r5, #0
after_args:

    /* fd = open("/dev/mem", O_RDWR) */
    ldr  r0, =mem_path
    mov  r1, #O_RDWR
    mov  r2, #0
    mov  r7, #SYS_open
    swi  #0
    cmp  r0, #0
    blt  fail_mem
    mov  r6, r0              /* r6 = mem_fd */

    /* mmap2(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, mem_fd, PL011_PAGE_OFFSET) */
    mov  r0, #0
    mov  r1, #PAGE_SIZE
    mov  r2, #(PROT_READ | PROT_WRITE)
    mov  r3, #MAP_SHARED
    /* args 5+ via stack on ARM EABI for mmap2? No — mmap2 has 6 register args */
    /* Actually mmap2 sig: (void*, size_t, int, int, int, off_t) all in r0-r5 */
    mov  r4, r6              /* fd */
    ldr  r5, =PL011_BASE_PAGE
    mov  r7, #SYS_mmap2
    swi  #0
    cmn  r0, #4096           /* if MAP_FAILED (-errno close to 0xffff_f...) */
    bhi  fail_mmap
    mov  r8, r0              /* r8 = uart_base */

    /* write(1, banner, banner_len) — also to stdout for SSH visibility */
    mov  r0, #1
    ldr  r1, =banner
    mov  r2, #banner_len
    mov  r7, #SYS_write
    swi  #0

    /* Write banner to UART byte by byte */
    ldr  r9, =banner
    ldr  r10, =banner_len
write_banner_loop:
    cmp  r10, #0
    beq  banner_done
    ldrb r0, [r9], #1
    sub  r10, r10, #1
    bl   uart_putc
    b    write_banner_loop
banner_done:

    /* if test_mode, write test banner then exit */
    cmp  r5, #1
    bne  open_kmsg
    ldr  r9, =test_banner
    ldr  r10, =test_len
write_test_loop:
    cmp  r10, #0
    beq  exit_ok
    ldrb r0, [r9], #1
    sub  r10, r10, #1
    bl   uart_putc
    b    write_test_loop

open_kmsg:
    /* kmsg_fd = open("/proc/kmsg", O_RDONLY) */
    ldr  r0, =kmsg_path
    mov  r1, #O_RDONLY
    mov  r2, #0
    mov  r7, #SYS_open
    swi  #0
    cmp  r0, #0
    blt  fail_kmsg
    mov  r6, r0              /* r6 = kmsg_fd */

main_loop:
    /* n = read(kmsg_fd, buf, 4096) */
    mov  r0, r6
    ldr  r1, =buf
    mov  r2, #4096
    mov  r7, #SYS_read
    swi  #0
    cmp  r0, #0
    ble  main_loop           /* EOF or err → keep trying */
    mov  r10, r0             /* n */
    ldr  r9, =buf
write_loop:
    cmp  r10, #0
    beq  main_loop
    ldrb r0, [r9], #1
    sub  r10, r10, #1
    bl   uart_putc
    b    write_loop

/* void uart_putc(int c in r0) — preserves r1-r12 */
uart_putc:
    push {r1, r2, lr}
    mov  r2, r0              /* save char */
wait_tx:
    ldr  r1, [r8, #FR_OFF]   /* fr = *(uart_base + FR_OFF) */
    tst  r1, #FR_TXFF        /* if (fr & TXFF) keep waiting */
    bne  wait_tx
    str  r2, [r8, #DR_OFF]   /* *(uart_base + DR_OFF) = c */
    pop  {r1, r2, lr}
    bx   lr

exit_ok:
    mov  r0, #0
    mov  r7, #SYS_exit
    swi  #0

fail_mem:
    mov  r0, #2
    ldr  r1, =err_mem
    mov  r2, #err_mem_len
    mov  r7, #SYS_write
    swi  #0
    mov  r0, #1
    mov  r7, #SYS_exit
    swi  #0

fail_mmap:
    mov  r0, #2
    ldr  r1, =err_mmap
    mov  r2, #err_mmap_len
    mov  r7, #SYS_write
    swi  #0
    mov  r0, #1
    mov  r7, #SYS_exit
    swi  #0

fail_kmsg:
    mov  r0, #2
    ldr  r1, =err_kmsg
    mov  r2, #err_kmsg_len
    mov  r7, #SYS_write
    swi  #0
    mov  r0, #1
    mov  r7, #SYS_exit
    swi  #0
