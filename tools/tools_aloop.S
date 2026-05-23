/* Tiny ARM payload: write magic to RAM, then try UART forever */
.section .text
.globl _start
_start:
	@ Write magic value 0xDEADBEEF to scratch RAM at 0x47000000
	ldr	r11, =0x47000000
	ldr	r10, =0xDEADBEEF
	str	r10, [r11]

	@ Write 0xCAFEBABE to second scratch slot to mark "step 2"
	ldr	r11, =0x47000004
	ldr	r10, =0xCAFEBABE
	str	r10, [r11]

	@ Now try the UART loop (re-init + write A's)
	@ Enable LSP0 master clocks
	ldr	r11, =0x94000014
	ldr	r10, [r11]
	movw	r9, #0x3A00
	orr	r10, r10, r9
	str	r10, [r11]

	@ Mark "step 3" in RAM
	ldr	r11, =0x47000008
	mov	r10, #3
	str	r10, [r11]

	@ UART0 clock
	ldr	r11, =0x94400010
	ldr	r10, [r11]
	orr	r10, r10, #3
	str	r10, [r11]

	@ Mark step 4
	ldr	r11, =0x4700000c
	mov	r10, #4
	str	r10, [r11]

	@ Re-init UART
	ldr	r11, =0x94404000
	mov	r10, #0
	str	r10, [r11, #0x34]
	mov	r10, #13
	str	r10, [r11, #0x24]
	mov	r10, #36
	str	r10, [r11, #0x28]
	mov	r10, #0x70
	str	r10, [r11, #0x30]
	movw	r10, #0x301
	str	r10, [r11, #0x34]

	@ Mark step 5 (UART configured)
	ldr	r11, =0x47000010
	mov	r10, #5
	str	r10, [r11]

	@ Loop: write 'A'
	mov	r10, #'A'
	ldr	r11, =0x94404004
1:
	str	r10, [r11]
	mov	r0, #0x100
2:
	subs	r0, r0, #1
	bne	2b
	b	1b
