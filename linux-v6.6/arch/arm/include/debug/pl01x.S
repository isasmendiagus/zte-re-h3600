/* SPDX-License-Identifier: GPL-2.0-only */
/* ZTE ZXIC SoCs (ZX279128S / ZX297520v3): PL011 with custom register layout.
 * Per Stefan Dösinger's port:
 *   DR=0x04, FR=0x14, IBRD=0x24, FBRD=0x28, LCRH=0x30, CR=0x34
 */
#include <linux/amba/serial.h>

#ifdef CONFIG_DEBUG_UART_PHYS
		.macro	addruart, rp, rv, tmp
		ldr	\rp, =CONFIG_DEBUG_UART_PHYS
		ldr	\rv, =CONFIG_DEBUG_UART_VIRT
		.endm
#endif

		.macro	senduart,rd,rx
		strb	\rd, [\rx, #0x04]	@ ZTE DR
		.endm

		.macro	waituartcts,rd,rx
		.endm

		.macro	waituarttxrdy,rd,rx
1001:		ldr	\rd, [\rx, #0x14]	@ ZTE FR
 ARM_BE8(	rev	\rd, \rd )
		tst	\rd, #UART01x_FR_TXFF
		bne	1001b
		.endm

		.macro	busyuart,rd,rx
1001:		ldr	\rd, [\rx, #0x14]	@ ZTE FR
 ARM_BE8(	rev	\rd, \rd )
		tst	\rd, #UART01x_FR_BUSY
		bne	1001b
		.endm
