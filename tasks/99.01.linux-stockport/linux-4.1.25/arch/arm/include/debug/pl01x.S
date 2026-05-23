/* arch/arm/include/debug/pl01x.S
 *
 * Debugging macro include header for PL011 (vendor PrimeCell).
 *
 * ZTE ZX279128S note: the integrated PL011 has its register layout SHIFTED
 * by +4 for DR/FR/LCR_H/CR (but NOT for IBRD/FBRD). See BITACORA.md Hallazgo 1.
 * When CONFIG_ARCH_ZX279128S is set, use shifted offsets so DEBUG_LL/earlycon hit
 * the right registers.
 */
#include <linux/amba/serial.h>

#ifdef CONFIG_DEBUG_UART_PHYS
		.macro	addruart, rp, rv, tmp
		ldr	\rp, =CONFIG_DEBUG_UART_PHYS
		ldr	\rv, =CONFIG_DEBUG_UART_VIRT
		.endm
#endif

		.macro	senduart,rd,rx
#ifdef CONFIG_ARCH_ZX279128S
		strb	\rd, [\rx, #0x04]	@ ZTE DR @ +0x04
#else
		strb	\rd, [\rx, #UART01x_DR]
#endif
		.endm

		.macro	waituart,rd,rx
#ifdef CONFIG_ARCH_ZX279128S
1001:		ldr	\rd, [\rx, #0x14]	@ ZTE FR @ +0x14 (per BITACORA Hallazgo 1)
		tst	\rd, #UART01x_FR_TXFF
		bne	1001b
#else
1001:		ldr	\rd, [\rx, #UART01x_FR]
 ARM_BE8(	rev	\rd, \rd )
		tst	\rd, #UART01x_FR_TXFF
		bne	1001b
#endif
		.endm

		.macro	busyuart,rd,rx
#ifdef CONFIG_ARCH_ZX279128S
1001:		ldr	\rd, [\rx, #0x14]	@ ZTE FR @ +0x14 (per BITACORA Hallazgo 1)
		tst	\rd, #UART01x_FR_BUSY
		bne	1001b
#else
1001:		ldr	\rd, [\rx, #UART01x_FR]
 ARM_BE8(	rev	\rd, \rd )
		tst	\rd, #UART01x_FR_BUSY
		bne	1001b
#endif
		.endm
