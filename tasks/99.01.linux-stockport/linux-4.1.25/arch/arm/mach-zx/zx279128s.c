// SPDX-License-Identifier: GPL-2.0
/*
 * Device Tree support for ZTE ZXIC ZX279128S SoC
 *
 * Provides a static iomap for the PL011 UART so that DEBUG_LL works
 * after MMU enable (mainline multiplatform doesn't auto-map peripherals).
 */
#include <linux/init.h>
#include <linux/sizes.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>

/* Per stock /etc/autokernelconf: CONFIG_DEBUG_UART_VIRT=0xf0704000
 * (NOT 0xf0404000 — we had this wrong, the wrong iomap meant kernel hit
 * unmapped memory when writing to "uart") */
#define ZX_UART0_PHYS		0x94404000
#define ZX_UART0_VIRT		0xf0704000

static struct map_desc zx_io_desc[] __initdata = {
	{
		.virtual	= ZX_UART0_VIRT,
		.pfn		= __phys_to_pfn(ZX_UART0_PHYS),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},
};

static void __init zx_map_io(void)
{
	iotable_init(zx_io_desc, ARRAY_SIZE(zx_io_desc));
}

static const char * const zx279128s_dt_compat[] = {
	"zte,zx279128s",
	NULL,
};

/* DT-based registration kept for future DTB-boot path. */
DT_MACHINE_START(ZX279128S_DT, "ZTE ZX279128S (Device Tree)")
	.dt_compat	= zx279128s_dt_compat,
	.map_io		= zx_map_io,
MACHINE_END

/* Stock bootloader (cspstart) passes ATAGs with mach_type=0x44258 (279128
 * decimal = the SoC number). DT_MACHINE_START's .nr=~0 doesn't match, so
 * boot fails with "unrecognized machine ID". Register a 2nd descriptor
 * with the explicit numeric ID so ATAG-based boot succeeds.
 * Discovered 2026-05-21: kernel actually prints
 *   "Error: unrecognized/unsupported machine ID (r1 = 0x00044258)"
 * confirming the value. */
static const struct machine_desc __mach_desc_ZX279128S_ATAG __used
__attribute__((__section__(".arch.info.init"))) = {
	.nr		= 0x44258,
	.name		= "ZTE ZX279128S (ATAG)",
	.map_io		= zx_map_io,
};
