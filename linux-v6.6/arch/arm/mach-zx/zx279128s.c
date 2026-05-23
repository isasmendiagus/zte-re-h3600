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

#define ZX_UART0_PHYS		0x94404000
#define ZX_UART0_VIRT		0xf0404000

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

DT_MACHINE_START(ZX279128S_DT, "ZTE ZX279128S (Device Tree)")
	.dt_compat	= zx279128s_dt_compat,
	.map_io		= zx_map_io,
MACHINE_END
