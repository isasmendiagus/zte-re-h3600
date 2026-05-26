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

/* Full stock iotable_init() table recovered from vmlinux.bin by anchoring
 * on the known UART entry (virt=0xf0700000 phys=0x94400000) and reading
 * surrounding 16-byte map_desc structs. 13 entries, all MT_DEVICE.
 *
 * Stock plat.ko hardcodes virtual addresses in this range:
 *   gephy_ldo_init  → 0xf0807000  (covered by 0xf0800000 chunk)
 *   phy_process     → 0xf0101100  (GIC ICDICPR — covered by 0xf0100000 chunk)
 *   ...others likely in 0xf0400000..0xf0c00000 too
 * Without these entries plat.ko page-faults on its first MMIO access in
 * each function — exactly what zx_pon_init was hitting in iter 1 (gephy)
 * and iter 2 (phy_process). */
#define MAP_1M(V, P) { .virtual = (V), .pfn = __phys_to_pfn(P), .length = SZ_1M, .type = MT_DEVICE }

static struct map_desc zx_io_desc[] __initdata = {
	MAP_1M(0xf0000000, 0x00400000),	/* cortex-A9 PERIPHBASE/SCU area */
	MAP_1M(0xf0100000, 0x00800000),	/* cortex-A9 GIC dist/CPU iface */
	MAP_1M(0xf0200000, 0x00a20000),	/* ? */
	MAP_1M(0xf0400000, 0x94000000),	/* top_crm */
	MAP_1M(0xf0500000, 0x94100000),	/* pcie crm */
	MAP_1M(0xf0600000, 0x94200000),	/* pcie crm2 */
	MAP_1M(0xf0700000, 0x94400000),	/* UART/serial block (DEBUG_LL) */
	MAP_1M(0xf0800000, 0x9a100000),	/* gephy block */
	MAP_1M(0xf0900000, 0x00d00000),	/* ? */
	MAP_1M(0xf0a00000, 0x00200000),	/* ? */
	MAP_1M(0xf0b00000, 0x09100000),	/* USB dwc3 */
	MAP_1M(0xf0c00000, 0x09400000),	/* ? */
	{ .virtual = 0xf0f00000, .pfn = __phys_to_pfn(0x9fe00000),
	  .length = 0x20000, .type = MT_DEVICE },
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
