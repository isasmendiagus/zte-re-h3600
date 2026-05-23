/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * arch/arm/include/debug/zx-pl011.S
 *
 * DEBUG_LL macros for ZTE ZX279128S "shifted PL011" UART.
 *
 * The ZTE UART is functionally PL011 but with all registers shifted +4 bytes:
 *   Standard PL011 → ZTE shifted
 *   DR     0x000  →  0x004
 *   FR     0x018  →  0x01c
 *   IBRD   0x024  →  0x028
 *   FBRD   0x028  →  0x02c
 *   LCR_H  0x02C  →  0x030
 *   CR     0x030  →  0x034
 *
 * This header replaces debug/pl01x.S when CONFIG_DEBUG_UART_ZX_PL011 is set.
 */

#define ZX_UART01x_DR		0x004
#define ZX_UART01x_FR		0x01c
#define ZX_UART01x_FR_TXFF	0x020	/* same TXFF bit position (bit 5) */
#define ZX_UART01x_FR_BUSY	0x008	/* same BUSY bit position (bit 3) */

#ifdef CONFIG_DEBUG_UART_PHYS
		.macro	addruart, rp, rv, tmp
		ldr	\rp, =CONFIG_DEBUG_UART_PHYS
		ldr	\rv, =CONFIG_DEBUG_UART_VIRT
		.endm
#endif

		.macro	senduart,rd,rx
		strb	\rd, [\rx, #ZX_UART01x_DR]
		.endm

		.macro	waituartcts,rd,rx
		.endm

		.macro	waituarttxrdy,rd,rx
1001:		ldr	\rd, [\rx, #ZX_UART01x_FR]
 ARM_BE8(	rev	\rd, \rd )
		tst	\rd, #ZX_UART01x_FR_TXFF
		bne	1001b
		.endm

		.macro	busyuart,rd,rx
1001:		ldr	\rd, [\rx, #ZX_UART01x_FR]
 ARM_BE8(	rev	\rd, \rd )
		tst	\rd, #ZX_UART01x_FR_BUSY
		bne	1001b
		.endm
