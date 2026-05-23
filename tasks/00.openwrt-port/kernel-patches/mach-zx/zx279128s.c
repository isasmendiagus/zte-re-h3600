// SPDX-License-Identifier: GPL-2.0
/*
 * Machine descriptor for ZTE ZX279128S boards (H3600 family).
 *
 * ARM Cortex-A9 dual-core, register layout reused from ZX296702
 * mach-zx with new compatible strings.
 */

#include <asm/mach/arch.h>

static const char * const zx279128s_dt_compat[] __initconst = {
	"zte,zx279128s",
	"zte,h3600",
	NULL,
};

DT_MACHINE_START(ZX279128S, "ZTE ZX279128S (Device Tree)")
	.dt_compat	= zx279128s_dt_compat,
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
MACHINE_END
