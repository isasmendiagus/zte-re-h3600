/* zx_stock_bursts.h — auto-generated from zx_stock_table.h by
 *   tasks/00.01.eth-driver/scripts/gen_stock_bursts.py
 *
 * Refactor #38 Phase 8: re-expresses the linear stock_init_table
 * as a stream of OPERATIONS — large contiguous runs as static
 * const u32 arrays (target of __iowrite32_copy), short runs as
 * (off, val) singletons. Same writes, dramatically fewer operations.
 *
 * Source entries : 22363
 * Skipped blocks : ['NPP_AUX', 'PON_LOW', 'PON_TAIL', 'TM'] (14778 entries via XXX runs)
 *                  → handled by explicit zx_<block>_init() in the driver
 * PON_TAIL replaced 2026-08-02: 10 C functions replace 343 bursts (6243 ops)
 * TM replaced 2026-08-02: 9 C functions replace 205 bursts (1656 ops)
 * Bursts (>=4 entries): 278, covering ~300 entries
 * Short runs    : 2444
 * Total ops     : 2722
 */
#ifndef ZX_STOCK_BURSTS_H
#define ZX_STOCK_BURSTS_H

#include <linux/types.h>

/* Burst kind — encoded in the master descriptor table */
#define ZX_BURST_KIND_RUN     0  /* __iowrite32_copy(base + off, data, len) */
#define ZX_BURST_KIND_SINGLE  1  /* writel(val, base + off) */

/* Window selector — which ioremap'd base this op targets */
#define ZX_BURST_WIN_BASE      0
#define ZX_BURST_WIN_PON_EARLY 1

struct zx_stock_op {
	u32 off_or_addr;      /* base offset (for SINGLE) or window-relative byte (for RUN) */
	u32 val_or_len;       /* val (SINGLE) or length in u32 (RUN) */
	const u32 *data;      /* NULL for SINGLE, points into bursts_data[] for RUN */
	u8 kind;
	u8 window;
	u16 _pad;
} __packed;

/* burst #5852: NPP/base off=0x14000 → 0x14018 (7 regs) */
static const u32 zx_burst_5852_data[7] = {
	0xffffffff, 0xffffffff, 0x00003fff, 0xffffffff, 0x3fffffff, 0x01400007, 0x00000001,
};

/* burst #5853: NPP/base off=0x14040 → 0x14054 (6 regs) */
static const u32 zx_burst_5853_data[6] = {
	0xffffffff, 0xffffffff, 0x0007ffff, 0xffffffff, 0xffffffff, 0x03ff05dc,
};

/* burst #5858: NPP/base off=0x14120 → 0x1413c (8 regs) */
static const u32 zx_burst_5858_data[8] = {
	0x470f4264, 0x0000f4f6, 0x470f4265, 0x0000f4f6, 0x470f4266, 0x0000f4f6, 0x470f4267, 0x0000f4f6,
};

/* burst #5859: NPP/base off=0x14240 → 0x14284 (18 regs) */
static const u32 zx_burst_5859_data[18] = {
	0x00650650, 0x00650650, 0x00650650, 0x00650650, 0x00650650, 0x00650650, 0x00650650, 0x00650650,
	0x00650650, 0x00650650, 0x00650650, 0x00650650, 0x00650650, 0x00650650, 0x00650650, 0x00650650,
	0x00650650, 0x00650650,
};

/* burst #5860: NPP/base off=0x14300 → 0x14320 (9 regs) */
static const u32 zx_burst_5860_data[9] = {
	0x50555555, 0x95541555, 0x10554155, 0x55555555, 0x000005aa, 0x50555555, 0x15551555, 0x10554045,
	0x55555555,
};

/* burst #5861: NPP/base off=0x14328 → 0x14334 (4 regs) */
static const u32 zx_burst_5861_data[4] = {
	0x50555555, 0x15551555, 0x10554045, 0x55555555,
};

/* burst #5862: NPP/base off=0x1433c → 0x14348 (4 regs) */
static const u32 zx_burst_5862_data[4] = {
	0x50555555, 0x15551555, 0x10554045, 0x55555555,
};

/* burst #5863: NPP/base off=0x14350 → 0x1435c (4 regs) */
static const u32 zx_burst_5863_data[4] = {
	0x50555555, 0x15551555, 0x10554045, 0x55555555,
};

/* burst #5864: NPP/base off=0x14364 → 0x14370 (4 regs) */
static const u32 zx_burst_5864_data[4] = {
	0x50555555, 0x15541555, 0x10554045, 0x55555555,
};

/* burst #5865: NPP/base off=0x14378 → 0x14384 (4 regs) */
static const u32 zx_burst_5865_data[4] = {
	0x50555555, 0x15551555, 0x10554045, 0x55555555,
};

/* burst #5866: NPP/base off=0x1438c → 0x14398 (4 regs) */
static const u32 zx_burst_5866_data[4] = {
	0x50555555, 0x15551555, 0x10554045, 0x55555555,
};

/* burst #5870: NPP/base off=0x145e4 → 0x14614 (13 regs) */
static const u32 zx_burst_5870_data[13] = {
	0x000004f4, 0x00000040, 0x28d100c6, 0x1003461a, 0x40100000, 0x20060000, 0x70620584, 0x11100000,
	0x00000002, 0x8e1e84c8, 0x0003e9ec, 0x0000818c, 0x00000600,
};

/* burst #7019: PP_FUC/base off=0x1c0004 → 0x1c0010 (4 regs) */
static const u32 zx_burst_7019_data[4] = {
	0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7022: PP_FUC/base off=0x1c003c → 0x1c0048 (4 regs) */
static const u32 zx_burst_7022_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7026: PP_FUC/base off=0x1c00ac → 0x1c00b8 (4 regs) */
static const u32 zx_burst_7026_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7027: PP_FUC/base off=0x1c00c0 → 0x1c00e0 (9 regs) */
static const u32 zx_burst_7027_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7028: PP_FUC/base off=0x1c0100 → 0x1c0118 (7 regs) */
static const u32 zx_burst_7028_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7029: PP_FUC/base off=0x1c0400 → 0x1c0410 (5 regs) */
static const u32 zx_burst_7029_data[5] = {
	0x00000001, 0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7030: PP_FUC/base off=0x1c0420 → 0x1c0434 (6 regs) */
static const u32 zx_burst_7030_data[6] = {
	0x00000fff, 0x00000106, 0x01070104, 0x00000106, 0x00000101, 0x00010001,
};

/* burst #7031: PP_FUC/base off=0x1c043c → 0x1c0448 (4 regs) */
static const u32 zx_burst_7031_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7035: PP_FUC/base off=0x1c04ac → 0x1c04b8 (4 regs) */
static const u32 zx_burst_7035_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7036: PP_FUC/base off=0x1c04c0 → 0x1c04e0 (9 regs) */
static const u32 zx_burst_7036_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7037: PP_FUC/base off=0x1c0500 → 0x1c0518 (7 regs) */
static const u32 zx_burst_7037_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7038: PP_FUC/base off=0x1c0800 → 0x1c0810 (5 regs) */
static const u32 zx_burst_7038_data[5] = {
	0x00000001, 0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7039: PP_FUC/base off=0x1c0820 → 0x1c0834 (6 regs) */
static const u32 zx_burst_7039_data[6] = {
	0x00000fff, 0x00000106, 0x01070104, 0x00000106, 0x00000101, 0x00010001,
};

/* burst #7040: PP_FUC/base off=0x1c083c → 0x1c0848 (4 regs) */
static const u32 zx_burst_7040_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7044: PP_FUC/base off=0x1c08ac → 0x1c08b8 (4 regs) */
static const u32 zx_burst_7044_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7045: PP_FUC/base off=0x1c08c0 → 0x1c08e0 (9 regs) */
static const u32 zx_burst_7045_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7046: PP_FUC/base off=0x1c0900 → 0x1c0918 (7 regs) */
static const u32 zx_burst_7046_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7047: PP_FUC/base off=0x1c0c00 → 0x1c0c10 (5 regs) */
static const u32 zx_burst_7047_data[5] = {
	0x00000001, 0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7048: PP_FUC/base off=0x1c0c20 → 0x1c0c34 (6 regs) */
static const u32 zx_burst_7048_data[6] = {
	0x00000fff, 0x00000106, 0x01070104, 0x00000106, 0x00000101, 0x00010001,
};

/* burst #7049: PP_FUC/base off=0x1c0c3c → 0x1c0c48 (4 regs) */
static const u32 zx_burst_7049_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7053: PP_FUC/base off=0x1c0cac → 0x1c0cb8 (4 regs) */
static const u32 zx_burst_7053_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7054: PP_FUC/base off=0x1c0cc0 → 0x1c0ce0 (9 regs) */
static const u32 zx_burst_7054_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7055: PP_FUC/base off=0x1c0d00 → 0x1c0d18 (7 regs) */
static const u32 zx_burst_7055_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7056: PP_FUC/base off=0x1c1000 → 0x1c1010 (5 regs) */
static const u32 zx_burst_7056_data[5] = {
	0x00000001, 0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7057: PP_FUC/base off=0x1c1020 → 0x1c1034 (6 regs) */
static const u32 zx_burst_7057_data[6] = {
	0x00000fff, 0x00000106, 0x01070104, 0x00000106, 0x00000101, 0x00010001,
};

/* burst #7058: PP_FUC/base off=0x1c103c → 0x1c1048 (4 regs) */
static const u32 zx_burst_7058_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7062: PP_FUC/base off=0x1c10ac → 0x1c10b8 (4 regs) */
static const u32 zx_burst_7062_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7063: PP_FUC/base off=0x1c10c0 → 0x1c10e0 (9 regs) */
static const u32 zx_burst_7063_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7064: PP_FUC/base off=0x1c1100 → 0x1c1118 (7 regs) */
static const u32 zx_burst_7064_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7065: PP_FUC/base off=0x1c1400 → 0x1c1410 (5 regs) */
static const u32 zx_burst_7065_data[5] = {
	0x00000001, 0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7066: PP_FUC/base off=0x1c1420 → 0x1c1434 (6 regs) */
static const u32 zx_burst_7066_data[6] = {
	0x00000fff, 0x00000106, 0x01070104, 0x00000106, 0x00000101, 0x00010001,
};

/* burst #7067: PP_FUC/base off=0x1c143c → 0x1c1448 (4 regs) */
static const u32 zx_burst_7067_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7071: PP_FUC/base off=0x1c14ac → 0x1c14b8 (4 regs) */
static const u32 zx_burst_7071_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7072: PP_FUC/base off=0x1c14c0 → 0x1c14e0 (9 regs) */
static const u32 zx_burst_7072_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7073: PP_FUC/base off=0x1c1500 → 0x1c1518 (7 regs) */
static const u32 zx_burst_7073_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7074: PP_FUC/base off=0x1c1800 → 0x1c1810 (5 regs) */
static const u32 zx_burst_7074_data[5] = {
	0x00000001, 0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7075: PP_FUC/base off=0x1c1820 → 0x1c1834 (6 regs) */
static const u32 zx_burst_7075_data[6] = {
	0x00000fff, 0x00000106, 0x01070104, 0x00000106, 0x00000101, 0x00010001,
};

/* burst #7076: PP_FUC/base off=0x1c183c → 0x1c1848 (4 regs) */
static const u32 zx_burst_7076_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7080: PP_FUC/base off=0x1c18ac → 0x1c18b8 (4 regs) */
static const u32 zx_burst_7080_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7081: PP_FUC/base off=0x1c18c0 → 0x1c18e0 (9 regs) */
static const u32 zx_burst_7081_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7082: PP_FUC/base off=0x1c1900 → 0x1c1918 (7 regs) */
static const u32 zx_burst_7082_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7083: PP_FUC/base off=0x1c1c00 → 0x1c1c10 (5 regs) */
static const u32 zx_burst_7083_data[5] = {
	0x00000001, 0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7084: PP_FUC/base off=0x1c1c20 → 0x1c1c34 (6 regs) */
static const u32 zx_burst_7084_data[6] = {
	0x00000fff, 0x00000106, 0x01070104, 0x00000106, 0x00000101, 0x00010001,
};

/* burst #7085: PP_FUC/base off=0x1c1c3c → 0x1c1c48 (4 regs) */
static const u32 zx_burst_7085_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7089: PP_FUC/base off=0x1c1cac → 0x1c1cb8 (4 regs) */
static const u32 zx_burst_7089_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7090: PP_FUC/base off=0x1c1cc0 → 0x1c1ce0 (9 regs) */
static const u32 zx_burst_7090_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7091: PP_FUC/base off=0x1c1d00 → 0x1c1d18 (7 regs) */
static const u32 zx_burst_7091_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7092: PP_FUC/base off=0x1c2000 → 0x1c2010 (5 regs) */
static const u32 zx_burst_7092_data[5] = {
	0x00000001, 0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7093: PP_FUC/base off=0x1c2020 → 0x1c2034 (6 regs) */
static const u32 zx_burst_7093_data[6] = {
	0x00000fff, 0x00000106, 0x01070104, 0x00000106, 0x00000101, 0x00010001,
};

/* burst #7094: PP_FUC/base off=0x1c203c → 0x1c2048 (4 regs) */
static const u32 zx_burst_7094_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7098: PP_FUC/base off=0x1c20ac → 0x1c20b8 (4 regs) */
static const u32 zx_burst_7098_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7099: PP_FUC/base off=0x1c20c0 → 0x1c20e0 (9 regs) */
static const u32 zx_burst_7099_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7100: PP_FUC/base off=0x1c2100 → 0x1c2118 (7 regs) */
static const u32 zx_burst_7100_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7101: PP_FUC/base off=0x1c2400 → 0x1c2410 (5 regs) */
static const u32 zx_burst_7101_data[5] = {
	0x00000001, 0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7102: PP_FUC/base off=0x1c2420 → 0x1c2434 (6 regs) */
static const u32 zx_burst_7102_data[6] = {
	0x00000fff, 0x00000106, 0x01070104, 0x00000106, 0x00000101, 0x00010001,
};

/* burst #7103: PP_FUC/base off=0x1c243c → 0x1c2448 (4 regs) */
static const u32 zx_burst_7103_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7107: PP_FUC/base off=0x1c24ac → 0x1c24b8 (4 regs) */
static const u32 zx_burst_7107_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7108: PP_FUC/base off=0x1c24c0 → 0x1c24e0 (9 regs) */
static const u32 zx_burst_7108_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7109: PP_FUC/base off=0x1c2500 → 0x1c2518 (7 regs) */
static const u32 zx_burst_7109_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7110: PP_FUC/base off=0x1c2800 → 0x1c2810 (5 regs) */
static const u32 zx_burst_7110_data[5] = {
	0x00000001, 0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7111: PP_FUC/base off=0x1c2820 → 0x1c2834 (6 regs) */
static const u32 zx_burst_7111_data[6] = {
	0x00000fff, 0x00000106, 0x01070104, 0x00000106, 0x00000101, 0x00010001,
};

/* burst #7112: PP_FUC/base off=0x1c283c → 0x1c2848 (4 regs) */
static const u32 zx_burst_7112_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7116: PP_FUC/base off=0x1c28ac → 0x1c28b8 (4 regs) */
static const u32 zx_burst_7116_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7117: PP_FUC/base off=0x1c28c0 → 0x1c28e0 (9 regs) */
static const u32 zx_burst_7117_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7118: PP_FUC/base off=0x1c2900 → 0x1c2918 (7 regs) */
static const u32 zx_burst_7118_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7119: PP_FUC/base off=0x1c2c00 → 0x1c2c10 (5 regs) */
static const u32 zx_burst_7119_data[5] = {
	0x00000001, 0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7120: PP_FUC/base off=0x1c2c20 → 0x1c2c34 (6 regs) */
static const u32 zx_burst_7120_data[6] = {
	0x00000fff, 0x00000106, 0x01070104, 0x00000106, 0x00000101, 0x00010001,
};

/* burst #7121: PP_FUC/base off=0x1c2c3c → 0x1c2c48 (4 regs) */
static const u32 zx_burst_7121_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7125: PP_FUC/base off=0x1c2cac → 0x1c2cb8 (4 regs) */
static const u32 zx_burst_7125_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7126: PP_FUC/base off=0x1c2cc0 → 0x1c2ce0 (9 regs) */
static const u32 zx_burst_7126_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7127: PP_FUC/base off=0x1c2d00 → 0x1c2d18 (7 regs) */
static const u32 zx_burst_7127_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7128: PP_FUC/base off=0x1c3000 → 0x1c3010 (5 regs) */
static const u32 zx_burst_7128_data[5] = {
	0x00000001, 0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7129: PP_FUC/base off=0x1c3020 → 0x1c3034 (6 regs) */
static const u32 zx_burst_7129_data[6] = {
	0x00000fff, 0x00000106, 0x01070104, 0x00000106, 0x00000101, 0x00010001,
};

/* burst #7130: PP_FUC/base off=0x1c303c → 0x1c3048 (4 regs) */
static const u32 zx_burst_7130_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7134: PP_FUC/base off=0x1c30ac → 0x1c30b8 (4 regs) */
static const u32 zx_burst_7134_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7135: PP_FUC/base off=0x1c30c0 → 0x1c30e0 (9 regs) */
static const u32 zx_burst_7135_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7136: PP_FUC/base off=0x1c3100 → 0x1c3118 (7 regs) */
static const u32 zx_burst_7136_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7137: PP_FUC/base off=0x1c3400 → 0x1c3410 (5 regs) */
static const u32 zx_burst_7137_data[5] = {
	0x00000001, 0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7138: PP_FUC/base off=0x1c3420 → 0x1c3434 (6 regs) */
static const u32 zx_burst_7138_data[6] = {
	0x00000fff, 0x00000106, 0x01070104, 0x00000106, 0x00000101, 0x00010001,
};

/* burst #7139: PP_FUC/base off=0x1c343c → 0x1c3448 (4 regs) */
static const u32 zx_burst_7139_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7143: PP_FUC/base off=0x1c34ac → 0x1c34b8 (4 regs) */
static const u32 zx_burst_7143_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7144: PP_FUC/base off=0x1c34c0 → 0x1c34e0 (9 regs) */
static const u32 zx_burst_7144_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7145: PP_FUC/base off=0x1c3500 → 0x1c3518 (7 regs) */
static const u32 zx_burst_7145_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7146: PP_FUC/base off=0x1c3800 → 0x1c3810 (5 regs) */
static const u32 zx_burst_7146_data[5] = {
	0x00000001, 0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7147: PP_FUC/base off=0x1c3820 → 0x1c3834 (6 regs) */
static const u32 zx_burst_7147_data[6] = {
	0x00000fff, 0x00000106, 0x01070104, 0x00000106, 0x00000101, 0x00010001,
};

/* burst #7148: PP_FUC/base off=0x1c383c → 0x1c3848 (4 regs) */
static const u32 zx_burst_7148_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7152: PP_FUC/base off=0x1c38ac → 0x1c38b8 (4 regs) */
static const u32 zx_burst_7152_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7153: PP_FUC/base off=0x1c38c0 → 0x1c38e0 (9 regs) */
static const u32 zx_burst_7153_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7154: PP_FUC/base off=0x1c3900 → 0x1c3918 (7 regs) */
static const u32 zx_burst_7154_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7155: PP_FUC/base off=0x1c3c00 → 0x1c3c10 (5 regs) */
static const u32 zx_burst_7155_data[5] = {
	0x00000001, 0x02abfc8d, 0x00000001, 0x00640064, 0x00000001,
};

/* burst #7156: PP_FUC/base off=0x1c3c20 → 0x1c3c34 (6 regs) */
static const u32 zx_burst_7156_data[6] = {
	0x00000fff, 0x00000106, 0x01070104, 0x00000106, 0x00000101, 0x00010001,
};

/* burst #7157: PP_FUC/base off=0x1c3c3c → 0x1c3c48 (4 regs) */
static const u32 zx_burst_7157_data[4] = {
	0x00000106, 0x01030101, 0x00000106, 0x00111111,
};

/* burst #7161: PP_FUC/base off=0x1c3cac → 0x1c3cb8 (4 regs) */
static const u32 zx_burst_7161_data[4] = {
	0x0000f42e, 0x00220022, 0x002e002e, 0x00f400f4,
};

/* burst #7162: PP_FUC/base off=0x1c3cc0 → 0x1c3ce0 (9 regs) */
static const u32 zx_burst_7162_data[9] = {
	0x04f4052e, 0x04f40000, 0x04f4052e, 0x04f4052e, 0x04f40000, 0x0000052e, 0x0000052e, 0x04f4052e,
	0x0a220a22,
};

/* burst #7163: PP_FUC/base off=0x1c3d00 → 0x1c3d18 (7 regs) */
static const u32 zx_burst_7163_data[7] = {
	0x0000000f, 0x000242f0, 0x00000064, 0x00000411, 0x22008e3f, 0xc7000007, 0xf000107c,
};

/* burst #7164: PP_FUC/base off=0x1c4000 → 0x1c4018 (7 regs) */
static const u32 zx_burst_7164_data[7] = {
	0x00000021, 0x00002008, 0x000003e8, 0x0bebc200, 0x00000834, 0x00000004, 0x00000001,
};

/* burst #7171: PP_FUC/base off=0x1c5000 → 0x1c5018 (7 regs) */
static const u32 zx_burst_7171_data[7] = {
	0x00000021, 0x00002008, 0x000003e8, 0x0bebc200, 0x00000834, 0x00000004, 0x00000001,
};

/* burst #7178: PP_FUC/base off=0x1c6000 → 0x1c6018 (7 regs) */
static const u32 zx_burst_7178_data[7] = {
	0x00000021, 0x00002008, 0x000003e8, 0x0bebc200, 0x00000834, 0x00000004, 0x00000001,
};

/* burst #7185: PP_FUC/base off=0x1c7000 → 0x1c7018 (7 regs) */
static const u32 zx_burst_7185_data[7] = {
	0x00000021, 0x00002008, 0x000003e8, 0x0bebc200, 0x00000834, 0x00000004, 0x00000001,
};

/* burst #7198: PP_FUC/base off=0x1c83c0 → 0x1c83dc (8 regs) */
static const u32 zx_burst_7198_data[8] = {
	0x000000fe, 0x000000fd, 0x000000fb, 0x000000f7, 0x000000ef, 0x000000df, 0x000000ff, 0x000000ff,
};

/* burst #7201: PP_FUC/base off=0x1c8c00 → 0x1c8c24 (10 regs) */
static const u32 zx_burst_7201_data[10] = {
	0x00002222, 0xe6000000, 0xda480000, 0xda480000, 0xda480000, 0xda480000, 0xda480000, 0xda480000,
	0x00101000, 0x00f40000,
};

/* burst #7207: PP_FUC/base off=0x1c8e00 → 0x1c8e14 (6 regs) */
static const u32 zx_burst_7207_data[6] = {
	0x40d1c042, 0x2843ff1a, 0x16000000, 0x10830001, 0x383102c2, 0x00880000,
};

/* burst #7209: PP_FUC/base off=0x1cc014 → 0x1cc030 (8 regs) */
static const u32 zx_burst_7209_data[8] = {
	0x00000004, 0x00000001, 0x43424140, 0x47464544, 0x4b4a4948, 0x4f4e4d4c, 0x00150355, 0x00000ff0,
};

/* burst #7216: PP_FUC/base off=0x1cc1e0 → 0x1cc220 (17 regs) */
static const u32 zx_burst_7216_data[17] = {
	0xf4f6470f, 0x4264c8a3, 0x62e95900, 0x08004500, 0x003463d7, 0x40004006, 0x5369c0a8, 0x0132c0a8,
	0x01019f18, 0x0016b935, 0x3e5bc507, 0xb9bd8010, 0x004ba242, 0x00000101, 0x080a8773, 0xa8560000,
	0x0b5d0000,
};

/* burst #7217: PP_FUC/base off=0x1cc260 → 0x1cc284 (10 regs) */
static const u32 zx_burst_7217_data[10] = {
	0x4b000000, 0xc5d39000, 0x1000b200, 0x00688a00, 0x8000c7ae, 0xa6d2800c, 0x02658150, 0x02038150,
	0x002d3e30, 0x0001726a,
};

/* burst #7218: PP_FUC/base off=0x1cc290 → 0x1cc29c (4 regs) */
static const u32 zx_burst_7218_data[4] = {
	0x00000097, 0x0000006c, 0x00000001, 0x00000038,
};

/* burst #7220: PP_FUC/base off=0x1cc394 → 0x1cc3b0 (8 regs) */
static const u32 zx_burst_7220_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00840000,
};

/* burst #7223: PP_FUC/base off=0x1cc3e0 → 0x1cc3f8 (7 regs) */
static const u32 zx_burst_7223_data[7] = {
	0x40d1c042, 0x2843ff1a, 0x96000000, 0x81610841, 0x00001c18, 0x00000044, 0x00000055,
};

/* burst #7224: PP_FUC/base off=0x1cc814 → 0x1cc830 (8 regs) */
static const u32 zx_burst_7224_data[8] = {
	0x00000004, 0x00000001, 0x43424140, 0x47464544, 0x4b4a4948, 0x4f4e4d4c, 0x00150355, 0x00000ff0,
};

/* burst #7232: PP_FUC/base off=0x1cc9e0 → 0x1cca20 (17 regs) */
static const u32 zx_burst_7232_data[17] = {
	0xf4f6470f, 0x4264c8a3, 0x62e95900, 0x08004500, 0x003463d7, 0x40004006, 0x5369c0a8, 0x0132c0a8,
	0x01019f18, 0x0016b935, 0x3e5bc507, 0xb9bd8010, 0x004ba242, 0x00000101, 0x080a8773, 0xa8560000,
	0x0b5d0000,
};

/* burst #7233: PP_FUC/base off=0x1cca60 → 0x1cca84 (10 regs) */
static const u32 zx_burst_7233_data[10] = {
	0x4b000000, 0xc5d39000, 0x1000b200, 0x00688a00, 0x8000c7ae, 0xa6d2800c, 0x02658150, 0x02038150,
	0x002d3e30, 0x0001726a,
};

/* burst #7234: PP_FUC/base off=0x1cca90 → 0x1cca9c (4 regs) */
static const u32 zx_burst_7234_data[4] = {
	0x00000097, 0x0000006c, 0x00000001, 0x00000038,
};

/* burst #7236: PP_FUC/base off=0x1ccb94 → 0x1ccbb0 (8 regs) */
static const u32 zx_burst_7236_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00840000,
};

/* burst #7239: PP_FUC/base off=0x1ccbe0 → 0x1ccbf8 (7 regs) */
static const u32 zx_burst_7239_data[7] = {
	0x40d1c042, 0x2843ff1a, 0x96000000, 0x81610841, 0x00001c18, 0x00000044, 0x00000055,
};

/* burst #7240: PP_FUC/base off=0x1cd014 → 0x1cd030 (8 regs) */
static const u32 zx_burst_7240_data[8] = {
	0x00000004, 0x00000001, 0x43424140, 0x47464544, 0x4b4a4948, 0x4f4e4d4c, 0x00150355, 0x00000ff0,
};

/* burst #7248: PP_FUC/base off=0x1cd1e0 → 0x1cd220 (17 regs) */
static const u32 zx_burst_7248_data[17] = {
	0xf4f6470f, 0x4264c8a3, 0x62e95900, 0x08004500, 0x003463d7, 0x40004006, 0x5369c0a8, 0x0132c0a8,
	0x01019f18, 0x0016b935, 0x3e5bc507, 0xb9bd8010, 0x004ba242, 0x00000101, 0x080a8773, 0xa8560000,
	0x0b5d0000,
};

/* burst #7249: PP_FUC/base off=0x1cd260 → 0x1cd284 (10 regs) */
static const u32 zx_burst_7249_data[10] = {
	0x4b000000, 0xc5d39000, 0x1000b200, 0x00688a00, 0x8000c7ae, 0xa6d2800c, 0x02658150, 0x02038150,
	0x002d3e30, 0x0001726a,
};

/* burst #7250: PP_FUC/base off=0x1cd290 → 0x1cd29c (4 regs) */
static const u32 zx_burst_7250_data[4] = {
	0x00000097, 0x0000006c, 0x00000001, 0x00000038,
};

/* burst #7252: PP_FUC/base off=0x1cd394 → 0x1cd3b0 (8 regs) */
static const u32 zx_burst_7252_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00840000,
};

/* burst #7255: PP_FUC/base off=0x1cd3e0 → 0x1cd3f8 (7 regs) */
static const u32 zx_burst_7255_data[7] = {
	0x40d1c042, 0x2843ff1a, 0x96000000, 0x81610841, 0x00001c18, 0x00000044, 0x00000055,
};

/* burst #7256: PP_FUC/base off=0x1cd814 → 0x1cd830 (8 regs) */
static const u32 zx_burst_7256_data[8] = {
	0x00000004, 0x00000001, 0x43424140, 0x47464544, 0x4b4a4948, 0x4f4e4d4c, 0x00150355, 0x00000ff0,
};

/* burst #7264: PP_FUC/base off=0x1cd9e0 → 0x1cda20 (17 regs) */
static const u32 zx_burst_7264_data[17] = {
	0xf4f6470f, 0x4264c8a3, 0x62e95900, 0x08004500, 0x003463d7, 0x40004006, 0x5369c0a8, 0x0132c0a8,
	0x01019f18, 0x0016b935, 0x3e5bc507, 0xb9bd8010, 0x004ba242, 0x00000101, 0x080a8773, 0xa8560000,
	0x0b5d0000,
};

/* burst #7265: PP_FUC/base off=0x1cda60 → 0x1cda84 (10 regs) */
static const u32 zx_burst_7265_data[10] = {
	0x4b000000, 0xc5d39000, 0x1000b200, 0x00688a00, 0x8000c7ae, 0xa6d2800c, 0x02658150, 0x02038150,
	0x002d3e30, 0x0001726a,
};

/* burst #7266: PP_FUC/base off=0x1cda90 → 0x1cda9c (4 regs) */
static const u32 zx_burst_7266_data[4] = {
	0x00000097, 0x0000006c, 0x00000001, 0x00000038,
};

/* burst #7268: PP_FUC/base off=0x1cdb94 → 0x1cdbb0 (8 regs) */
static const u32 zx_burst_7268_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00840000,
};

/* burst #7271: PP_FUC/base off=0x1cdbe0 → 0x1cdbf8 (7 regs) */
static const u32 zx_burst_7271_data[7] = {
	0x40d1c042, 0x2843ff1a, 0x96000000, 0x81610841, 0x00001c18, 0x00000044, 0x00000055,
};

/* burst #7272: PP_FUC/base off=0x1ce014 → 0x1ce030 (8 regs) */
static const u32 zx_burst_7272_data[8] = {
	0x00000004, 0x00000001, 0x43424140, 0x47464544, 0x4b4a4948, 0x4f4e4d4c, 0x00150355, 0x00000ff0,
};

/* burst #7280: PP_FUC/base off=0x1ce1e0 → 0x1ce220 (17 regs) */
static const u32 zx_burst_7280_data[17] = {
	0xf4f6470f, 0x4264c8a3, 0x62e95900, 0x08004500, 0x003463d7, 0x40004006, 0x5369c0a8, 0x0132c0a8,
	0x01019f18, 0x0016b935, 0x3e5bc507, 0xb9bd8010, 0x004ba242, 0x00000101, 0x080a8773, 0xa8560000,
	0x0b5d0000,
};

/* burst #7281: PP_FUC/base off=0x1ce260 → 0x1ce284 (10 regs) */
static const u32 zx_burst_7281_data[10] = {
	0x4b000000, 0xc5d39000, 0x1000b200, 0x00688a00, 0x8000c7ae, 0xa6d2800c, 0x02658150, 0x02038150,
	0x002d3e30, 0x0001726a,
};

/* burst #7282: PP_FUC/base off=0x1ce290 → 0x1ce29c (4 regs) */
static const u32 zx_burst_7282_data[4] = {
	0x00000097, 0x0000006c, 0x00000001, 0x00000038,
};

/* burst #7284: PP_FUC/base off=0x1ce394 → 0x1ce3b0 (8 regs) */
static const u32 zx_burst_7284_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00840000,
};

/* burst #7287: PP_FUC/base off=0x1ce3e0 → 0x1ce3f8 (7 regs) */
static const u32 zx_burst_7287_data[7] = {
	0x40d1c042, 0x2843ff1a, 0x96000000, 0x81610841, 0x00001c18, 0x00000044, 0x00000055,
};

/* burst #7288: PP_FUC/base off=0x1ce814 → 0x1ce830 (8 regs) */
static const u32 zx_burst_7288_data[8] = {
	0x00000004, 0x00000001, 0x43424140, 0x47464544, 0x4b4a4948, 0x4f4e4d4c, 0x00150355, 0x00000ff0,
};

/* burst #7296: PP_FUC/base off=0x1ce9e0 → 0x1cea20 (17 regs) */
static const u32 zx_burst_7296_data[17] = {
	0xf4f6470f, 0x4264c8a3, 0x62e95900, 0x08004500, 0x003463d7, 0x40004006, 0x5369c0a8, 0x0132c0a8,
	0x01019f18, 0x0016b935, 0x3e5bc507, 0xb9bd8010, 0x004ba242, 0x00000101, 0x080a8773, 0xa8560000,
	0x0b5d0000,
};

/* burst #7297: PP_FUC/base off=0x1cea60 → 0x1cea84 (10 regs) */
static const u32 zx_burst_7297_data[10] = {
	0x4b000000, 0xc5d39000, 0x1000b200, 0x00688a00, 0x8000c7ae, 0xa6d2800c, 0x02658150, 0x02038150,
	0x002d3e30, 0x0001726a,
};

/* burst #7298: PP_FUC/base off=0x1cea90 → 0x1cea9c (4 regs) */
static const u32 zx_burst_7298_data[4] = {
	0x00000097, 0x0000006c, 0x00000001, 0x00000038,
};

/* burst #7300: PP_FUC/base off=0x1ceb94 → 0x1cebb0 (8 regs) */
static const u32 zx_burst_7300_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00840000,
};

/* burst #7303: PP_FUC/base off=0x1cebe0 → 0x1cebf8 (7 regs) */
static const u32 zx_burst_7303_data[7] = {
	0x40d1c042, 0x2843ff1a, 0x96000000, 0x81610841, 0x00001c18, 0x00000044, 0x00000055,
};

/* burst #7304: PP_FUC/base off=0x1cf014 → 0x1cf030 (8 regs) */
static const u32 zx_burst_7304_data[8] = {
	0x00000004, 0x00000001, 0x43424140, 0x47464544, 0x4b4a4948, 0x4f4e4d4c, 0x00150355, 0x00000ff0,
};

/* burst #7312: PP_FUC/base off=0x1cf1e0 → 0x1cf220 (17 regs) */
static const u32 zx_burst_7312_data[17] = {
	0xf4f6470f, 0x4264c8a3, 0x62e95900, 0x08004500, 0x003463d7, 0x40004006, 0x5369c0a8, 0x0132c0a8,
	0x01019f18, 0x0016b935, 0x3e5bc507, 0xb9bd8010, 0x004ba242, 0x00000101, 0x080a8773, 0xa8560000,
	0x0b5d0000,
};

/* burst #7313: PP_FUC/base off=0x1cf260 → 0x1cf284 (10 regs) */
static const u32 zx_burst_7313_data[10] = {
	0x4b000000, 0xc5d39000, 0x1000b200, 0x00688a00, 0x8000c7ae, 0xa6d2800c, 0x02658150, 0x02038150,
	0x002d3e30, 0x0001726a,
};

/* burst #7314: PP_FUC/base off=0x1cf290 → 0x1cf29c (4 regs) */
static const u32 zx_burst_7314_data[4] = {
	0x00000097, 0x0000006c, 0x00000001, 0x00000038,
};

/* burst #7316: PP_FUC/base off=0x1cf394 → 0x1cf3b0 (8 regs) */
static const u32 zx_burst_7316_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00840000,
};

/* burst #7319: PP_FUC/base off=0x1cf3e0 → 0x1cf3f8 (7 regs) */
static const u32 zx_burst_7319_data[7] = {
	0x40d1c042, 0x2843ff1a, 0x96000000, 0x81610841, 0x00001c18, 0x00000044, 0x00000055,
};

/* burst #7320: PP_FUC/base off=0x1cf814 → 0x1cf830 (8 regs) */
static const u32 zx_burst_7320_data[8] = {
	0x00000004, 0x00000001, 0x43424140, 0x47464544, 0x4b4a4948, 0x4f4e4d4c, 0x00150355, 0x00000ff0,
};

/* burst #7328: PP_FUC/base off=0x1cf9e0 → 0x1cfa20 (17 regs) */
static const u32 zx_burst_7328_data[17] = {
	0xf4f6470f, 0x4264c8a3, 0x62e95900, 0x08004500, 0x003463d7, 0x40004006, 0x5369c0a8, 0x0132c0a8,
	0x01019f18, 0x0016b935, 0x3e5bc507, 0xb9bd8010, 0x004ba242, 0x00000101, 0x080a8773, 0xa8560000,
	0x0b5d0000,
};

/* burst #7329: PP_FUC/base off=0x1cfa60 → 0x1cfa84 (10 regs) */
static const u32 zx_burst_7329_data[10] = {
	0x4b000000, 0xc5d39000, 0x1000b200, 0x00688a00, 0x8000c7ae, 0xa6d2800c, 0x02658150, 0x02038150,
	0x002d3e30, 0x0001726a,
};

/* burst #7330: PP_FUC/base off=0x1cfa90 → 0x1cfa9c (4 regs) */
static const u32 zx_burst_7330_data[4] = {
	0x00000097, 0x0000006c, 0x00000001, 0x00000038,
};

/* burst #7332: PP_FUC/base off=0x1cfb94 → 0x1cfbb0 (8 regs) */
static const u32 zx_burst_7332_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00840000,
};

/* burst #7335: PP_FUC/base off=0x1cfbe0 → 0x1cfbf8 (7 regs) */
static const u32 zx_burst_7335_data[7] = {
	0x40d1c042, 0x2843ff1a, 0x96000000, 0x81610841, 0x00001c18, 0x00000044, 0x00000055,
};

/* burst #7343: PP_FUC/base off=0x1d4148 → 0x1d4154 (4 regs) */
static const u32 zx_burst_7343_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7346: PP_FUC/base off=0x1d4240 → 0x1d425c (8 regs) */
static const u32 zx_burst_7346_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7354: PP_FUC/base off=0x1d4548 → 0x1d4554 (4 regs) */
static const u32 zx_burst_7354_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7357: PP_FUC/base off=0x1d4640 → 0x1d465c (8 regs) */
static const u32 zx_burst_7357_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7365: PP_FUC/base off=0x1d4948 → 0x1d4954 (4 regs) */
static const u32 zx_burst_7365_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7368: PP_FUC/base off=0x1d4a40 → 0x1d4a5c (8 regs) */
static const u32 zx_burst_7368_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7376: PP_FUC/base off=0x1d4d48 → 0x1d4d54 (4 regs) */
static const u32 zx_burst_7376_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7379: PP_FUC/base off=0x1d4e40 → 0x1d4e5c (8 regs) */
static const u32 zx_burst_7379_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7387: PP_FUC/base off=0x1d5148 → 0x1d5154 (4 regs) */
static const u32 zx_burst_7387_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7390: PP_FUC/base off=0x1d5240 → 0x1d525c (8 regs) */
static const u32 zx_burst_7390_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7398: PP_FUC/base off=0x1d5548 → 0x1d5554 (4 regs) */
static const u32 zx_burst_7398_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7401: PP_FUC/base off=0x1d5640 → 0x1d565c (8 regs) */
static const u32 zx_burst_7401_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7409: PP_FUC/base off=0x1d5948 → 0x1d5954 (4 regs) */
static const u32 zx_burst_7409_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7412: PP_FUC/base off=0x1d5a40 → 0x1d5a5c (8 regs) */
static const u32 zx_burst_7412_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7420: PP_FUC/base off=0x1d5d48 → 0x1d5d54 (4 regs) */
static const u32 zx_burst_7420_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7423: PP_FUC/base off=0x1d5e40 → 0x1d5e5c (8 regs) */
static const u32 zx_burst_7423_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7431: PP_FUC/base off=0x1d6148 → 0x1d6154 (4 regs) */
static const u32 zx_burst_7431_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7434: PP_FUC/base off=0x1d6240 → 0x1d625c (8 regs) */
static const u32 zx_burst_7434_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7442: PP_FUC/base off=0x1d6548 → 0x1d6554 (4 regs) */
static const u32 zx_burst_7442_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7445: PP_FUC/base off=0x1d6640 → 0x1d665c (8 regs) */
static const u32 zx_burst_7445_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7453: PP_FUC/base off=0x1d6948 → 0x1d6954 (4 regs) */
static const u32 zx_burst_7453_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7456: PP_FUC/base off=0x1d6a40 → 0x1d6a5c (8 regs) */
static const u32 zx_burst_7456_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7464: PP_FUC/base off=0x1d6d48 → 0x1d6d54 (4 regs) */
static const u32 zx_burst_7464_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7467: PP_FUC/base off=0x1d6e40 → 0x1d6e5c (8 regs) */
static const u32 zx_burst_7467_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7475: PP_FUC/base off=0x1d7148 → 0x1d7154 (4 regs) */
static const u32 zx_burst_7475_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7478: PP_FUC/base off=0x1d7240 → 0x1d725c (8 regs) */
static const u32 zx_burst_7478_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7486: PP_FUC/base off=0x1d7548 → 0x1d7554 (4 regs) */
static const u32 zx_burst_7486_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7489: PP_FUC/base off=0x1d7640 → 0x1d765c (8 regs) */
static const u32 zx_burst_7489_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7497: PP_FUC/base off=0x1d7948 → 0x1d7954 (4 regs) */
static const u32 zx_burst_7497_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7500: PP_FUC/base off=0x1d7a40 → 0x1d7a5c (8 regs) */
static const u32 zx_burst_7500_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7508: PP_FUC/base off=0x1d7d48 → 0x1d7d54 (4 regs) */
static const u32 zx_burst_7508_data[4] = {
	0x00000022, 0x000004d5, 0x0000001c, 0x00000012,
};

/* burst #7511: PP_FUC/base off=0x1d7e40 → 0x1d7e5c (8 regs) */
static const u32 zx_burst_7511_data[8] = {
	0x40d1c042, 0x2843ff1a, 0xaa200000, 0x81610841, 0x00000e0c, 0x80000022, 0x000000ea, 0x00021000,
};

/* burst #7516: PP_FUC/base off=0x1d8080 → 0x1d80c4 (18 regs) */
static const u32 zx_burst_7516_data[18] = {
	0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688,
	0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688,
	0x00688688, 0x00688688,
};

/* burst #7519: PP_FUC/base off=0x1d8124 → 0x1d8134 (5 regs) */
static const u32 zx_burst_7519_data[5] = {
	0x28d100c6, 0x1003461a, 0x40100000, 0x00060000, 0x000102c2,
};

/* burst #7520: PP_FUC/base off=0x1d8140 → 0x1d814c (4 regs) */
static const u32 zx_burst_7520_data[4] = {
	0x2387a132, 0xac807a7b, 0xe451b174, 0x60540080,
};

/* burst #7527: PP_FUC/base off=0x1d9080 → 0x1d90c4 (18 regs) */
static const u32 zx_burst_7527_data[18] = {
	0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688,
	0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688,
	0x00688688, 0x00688688,
};

/* burst #7530: PP_FUC/base off=0x1d9124 → 0x1d9134 (5 regs) */
static const u32 zx_burst_7530_data[5] = {
	0x28d100c6, 0x1003461a, 0x40100000, 0x00060000, 0x000102c2,
};

/* burst #7531: PP_FUC/base off=0x1d9140 → 0x1d914c (4 regs) */
static const u32 zx_burst_7531_data[4] = {
	0x2387a132, 0xac807a7b, 0xe451b174, 0x60540080,
};

/* burst #7538: PP_FUC/base off=0x1da080 → 0x1da0c4 (18 regs) */
static const u32 zx_burst_7538_data[18] = {
	0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688,
	0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688,
	0x00688688, 0x00688688,
};

/* burst #7541: PP_FUC/base off=0x1da124 → 0x1da134 (5 regs) */
static const u32 zx_burst_7541_data[5] = {
	0x28d100c6, 0x1003461a, 0x40100000, 0x00060000, 0x000102c2,
};

/* burst #7542: PP_FUC/base off=0x1da140 → 0x1da14c (4 regs) */
static const u32 zx_burst_7542_data[4] = {
	0x2387a132, 0xac807a7b, 0xe451b174, 0x60540080,
};

/* burst #7549: PP_FUC/base off=0x1db080 → 0x1db0c4 (18 regs) */
static const u32 zx_burst_7549_data[18] = {
	0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688,
	0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688, 0x00688688,
	0x00688688, 0x00688688,
};

/* burst #7552: PP_FUC/base off=0x1db124 → 0x1db134 (5 regs) */
static const u32 zx_burst_7552_data[5] = {
	0x28d100c6, 0x1003461a, 0x40100000, 0x00060000, 0x000102c2,
};

/* burst #7553: PP_FUC/base off=0x1db140 → 0x1db14c (4 regs) */
static const u32 zx_burst_7553_data[4] = {
	0x2387a132, 0xac807a7b, 0xe451b174, 0x60540080,
};

/* burst #7556: PP_FUC/base off=0x1dc014 → 0x1dc020 (4 regs) */
static const u32 zx_burst_7556_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7558: PP_FUC/base off=0x1dc080 → 0x1dc098 (7 regs) */
static const u32 zx_burst_7558_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7560: PP_FUC/base off=0x1dc0b8 → 0x1dc0d4 (8 regs) */
static const u32 zx_burst_7560_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7563: PP_FUC/base off=0x1dc414 → 0x1dc420 (4 regs) */
static const u32 zx_burst_7563_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7565: PP_FUC/base off=0x1dc480 → 0x1dc498 (7 regs) */
static const u32 zx_burst_7565_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7567: PP_FUC/base off=0x1dc4b8 → 0x1dc4d4 (8 regs) */
static const u32 zx_burst_7567_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7570: PP_FUC/base off=0x1dc814 → 0x1dc820 (4 regs) */
static const u32 zx_burst_7570_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7572: PP_FUC/base off=0x1dc880 → 0x1dc898 (7 regs) */
static const u32 zx_burst_7572_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7574: PP_FUC/base off=0x1dc8b8 → 0x1dc8d4 (8 regs) */
static const u32 zx_burst_7574_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7577: PP_FUC/base off=0x1dcc14 → 0x1dcc20 (4 regs) */
static const u32 zx_burst_7577_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7579: PP_FUC/base off=0x1dcc80 → 0x1dcc98 (7 regs) */
static const u32 zx_burst_7579_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7581: PP_FUC/base off=0x1dccb8 → 0x1dccd4 (8 regs) */
static const u32 zx_burst_7581_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7584: PP_FUC/base off=0x1dd014 → 0x1dd020 (4 regs) */
static const u32 zx_burst_7584_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7586: PP_FUC/base off=0x1dd080 → 0x1dd098 (7 regs) */
static const u32 zx_burst_7586_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7588: PP_FUC/base off=0x1dd0b8 → 0x1dd0d4 (8 regs) */
static const u32 zx_burst_7588_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7591: PP_FUC/base off=0x1dd414 → 0x1dd420 (4 regs) */
static const u32 zx_burst_7591_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7593: PP_FUC/base off=0x1dd480 → 0x1dd498 (7 regs) */
static const u32 zx_burst_7593_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7595: PP_FUC/base off=0x1dd4b8 → 0x1dd4d4 (8 regs) */
static const u32 zx_burst_7595_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7598: PP_FUC/base off=0x1dd814 → 0x1dd820 (4 regs) */
static const u32 zx_burst_7598_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7600: PP_FUC/base off=0x1dd880 → 0x1dd898 (7 regs) */
static const u32 zx_burst_7600_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7602: PP_FUC/base off=0x1dd8b8 → 0x1dd8d4 (8 regs) */
static const u32 zx_burst_7602_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7605: PP_FUC/base off=0x1ddc14 → 0x1ddc20 (4 regs) */
static const u32 zx_burst_7605_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7607: PP_FUC/base off=0x1ddc80 → 0x1ddc98 (7 regs) */
static const u32 zx_burst_7607_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7609: PP_FUC/base off=0x1ddcb8 → 0x1ddcd4 (8 regs) */
static const u32 zx_burst_7609_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7612: PP_FUC/base off=0x1de014 → 0x1de020 (4 regs) */
static const u32 zx_burst_7612_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7614: PP_FUC/base off=0x1de080 → 0x1de098 (7 regs) */
static const u32 zx_burst_7614_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7616: PP_FUC/base off=0x1de0b8 → 0x1de0d4 (8 regs) */
static const u32 zx_burst_7616_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7619: PP_FUC/base off=0x1de414 → 0x1de420 (4 regs) */
static const u32 zx_burst_7619_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7621: PP_FUC/base off=0x1de480 → 0x1de498 (7 regs) */
static const u32 zx_burst_7621_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7623: PP_FUC/base off=0x1de4b8 → 0x1de4d4 (8 regs) */
static const u32 zx_burst_7623_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7626: PP_FUC/base off=0x1de814 → 0x1de820 (4 regs) */
static const u32 zx_burst_7626_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7628: PP_FUC/base off=0x1de880 → 0x1de898 (7 regs) */
static const u32 zx_burst_7628_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7630: PP_FUC/base off=0x1de8b8 → 0x1de8d4 (8 regs) */
static const u32 zx_burst_7630_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7633: PP_FUC/base off=0x1dec14 → 0x1dec20 (4 regs) */
static const u32 zx_burst_7633_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7635: PP_FUC/base off=0x1dec80 → 0x1dec98 (7 regs) */
static const u32 zx_burst_7635_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7637: PP_FUC/base off=0x1decb8 → 0x1decd4 (8 regs) */
static const u32 zx_burst_7637_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7640: PP_FUC/base off=0x1df014 → 0x1df020 (4 regs) */
static const u32 zx_burst_7640_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7642: PP_FUC/base off=0x1df080 → 0x1df098 (7 regs) */
static const u32 zx_burst_7642_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7644: PP_FUC/base off=0x1df0b8 → 0x1df0d4 (8 regs) */
static const u32 zx_burst_7644_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7647: PP_FUC/base off=0x1df414 → 0x1df420 (4 regs) */
static const u32 zx_burst_7647_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7649: PP_FUC/base off=0x1df480 → 0x1df498 (7 regs) */
static const u32 zx_burst_7649_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7651: PP_FUC/base off=0x1df4b8 → 0x1df4d4 (8 regs) */
static const u32 zx_burst_7651_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7654: PP_FUC/base off=0x1df814 → 0x1df820 (4 regs) */
static const u32 zx_burst_7654_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7656: PP_FUC/base off=0x1df880 → 0x1df898 (7 regs) */
static const u32 zx_burst_7656_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7658: PP_FUC/base off=0x1df8b8 → 0x1df8d4 (8 regs) */
static const u32 zx_burst_7658_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7661: PP_FUC/base off=0x1dfc14 → 0x1dfc20 (4 regs) */
static const u32 zx_burst_7661_data[4] = {
	0x03000003, 0x00000001, 0x470f4267, 0x0000f4f6,
};

/* burst #7663: PP_FUC/base off=0x1dfc80 → 0x1dfc98 (7 regs) */
static const u32 zx_burst_7663_data[7] = {
	0x04f404f4, 0x619a619a, 0x04f404f4, 0x000000c6, 0x000001b0, 0x000004f4, 0x04f404f4,
};

/* burst #7665: PP_FUC/base off=0x1dfcb8 → 0x1dfcd4 (8 regs) */
static const u32 zx_burst_7665_data[8] = {
	0x00000047, 0x30000400, 0x1a40c604, 0x001c1803, 0x08844400, 0x60009a20, 0x468d0000, 0x001a20d1,
};

/* burst #7669: PP_FUC/base off=0x1e001c → 0x1e002c (5 regs) */
static const u32 zx_burst_7669_data[5] = {
	0x21200000, 0x4eb20000, 0x4e720000, 0x00000640, 0x00000708,
};

/* burst #7670: PP_FUC/base off=0x1e0118 → 0x1e0134 (8 regs) */
static const u32 zx_burst_7670_data[8] = {
	0x00008100, 0x00009100, 0x000088a8, 0x00009200, 0x00008100, 0x00008100, 0x00008100, 0x00008100,
};

/* burst #7673: PP_FUC/base off=0x1e03e0 → 0x1e03fc (8 regs) */
static const u32 zx_burst_7673_data[8] = {
	0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040,
};

/* burst #7675: PP_FUC/base off=0x1e081c → 0x1e082c (5 regs) */
static const u32 zx_burst_7675_data[5] = {
	0x21200000, 0x4eb20000, 0x4e720000, 0x00000640, 0x00000708,
};

/* burst #7676: PP_FUC/base off=0x1e0918 → 0x1e0934 (8 regs) */
static const u32 zx_burst_7676_data[8] = {
	0x00008100, 0x00009100, 0x000088a8, 0x00009200, 0x00008100, 0x00008100, 0x00008100, 0x00008100,
};

/* burst #7679: PP_FUC/base off=0x1e0be0 → 0x1e0bfc (8 regs) */
static const u32 zx_burst_7679_data[8] = {
	0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040,
};

/* burst #7681: PP_FUC/base off=0x1e101c → 0x1e102c (5 regs) */
static const u32 zx_burst_7681_data[5] = {
	0x21200000, 0x4eb20000, 0x4e720000, 0x00000640, 0x00000708,
};

/* burst #7682: PP_FUC/base off=0x1e1118 → 0x1e1134 (8 regs) */
static const u32 zx_burst_7682_data[8] = {
	0x00008100, 0x00009100, 0x000088a8, 0x00009200, 0x00008100, 0x00008100, 0x00008100, 0x00008100,
};

/* burst #7685: PP_FUC/base off=0x1e13e0 → 0x1e13fc (8 regs) */
static const u32 zx_burst_7685_data[8] = {
	0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040,
};

/* burst #7687: PP_FUC/base off=0x1e181c → 0x1e182c (5 regs) */
static const u32 zx_burst_7687_data[5] = {
	0x21200000, 0x4eb20000, 0x4e720000, 0x00000640, 0x00000708,
};

/* burst #7688: PP_FUC/base off=0x1e1918 → 0x1e1934 (8 regs) */
static const u32 zx_burst_7688_data[8] = {
	0x00008100, 0x00009100, 0x000088a8, 0x00009200, 0x00008100, 0x00008100, 0x00008100, 0x00008100,
};

/* burst #7691: PP_FUC/base off=0x1e1be0 → 0x1e1bfc (8 regs) */
static const u32 zx_burst_7691_data[8] = {
	0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040,
};

/* burst #7693: PP_FUC/base off=0x1e201c → 0x1e202c (5 regs) */
static const u32 zx_burst_7693_data[5] = {
	0x21200000, 0x4eb20000, 0x4e720000, 0x00000640, 0x00000708,
};

/* burst #7694: PP_FUC/base off=0x1e2118 → 0x1e2134 (8 regs) */
static const u32 zx_burst_7694_data[8] = {
	0x00008100, 0x00009100, 0x000088a8, 0x00009200, 0x00008100, 0x00008100, 0x00008100, 0x00008100,
};

/* burst #7697: PP_FUC/base off=0x1e23e0 → 0x1e23fc (8 regs) */
static const u32 zx_burst_7697_data[8] = {
	0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040,
};

/* burst #7699: PP_FUC/base off=0x1e281c → 0x1e282c (5 regs) */
static const u32 zx_burst_7699_data[5] = {
	0x21200000, 0x4eb20000, 0x4e720000, 0x00000640, 0x00000708,
};

/* burst #7700: PP_FUC/base off=0x1e2918 → 0x1e2934 (8 regs) */
static const u32 zx_burst_7700_data[8] = {
	0x00008100, 0x00009100, 0x000088a8, 0x00009200, 0x00008100, 0x00008100, 0x00008100, 0x00008100,
};

/* burst #7703: PP_FUC/base off=0x1e2be0 → 0x1e2bfc (8 regs) */
static const u32 zx_burst_7703_data[8] = {
	0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040,
};

/* burst #7705: PP_FUC/base off=0x1e301c → 0x1e302c (5 regs) */
static const u32 zx_burst_7705_data[5] = {
	0x21200000, 0x4eb20000, 0x4e720000, 0x00000640, 0x00000708,
};

/* burst #7706: PP_FUC/base off=0x1e3118 → 0x1e3134 (8 regs) */
static const u32 zx_burst_7706_data[8] = {
	0x00008100, 0x00009100, 0x000088a8, 0x00009200, 0x00008100, 0x00008100, 0x00008100, 0x00008100,
};

/* burst #7709: PP_FUC/base off=0x1e33e0 → 0x1e33fc (8 regs) */
static const u32 zx_burst_7709_data[8] = {
	0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040,
};

/* burst #7711: PP_FUC/base off=0x1e381c → 0x1e382c (5 regs) */
static const u32 zx_burst_7711_data[5] = {
	0x21200000, 0x4eb20000, 0x4e720000, 0x00000640, 0x00000708,
};

/* burst #7712: PP_FUC/base off=0x1e3918 → 0x1e3934 (8 regs) */
static const u32 zx_burst_7712_data[8] = {
	0x00008100, 0x00009100, 0x000088a8, 0x00009200, 0x00008100, 0x00008100, 0x00008100, 0x00008100,
};

/* burst #7715: PP_FUC/base off=0x1e3be0 → 0x1e3bfc (8 regs) */
static const u32 zx_burst_7715_data[8] = {
	0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040, 0x00000040,
};

static const struct zx_stock_op zx_stock_ops[2722] = {
	{ 0x40000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4006c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4046c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4086c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x40c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4106c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4146c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4186c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x41c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4206c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4246c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4286c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x42c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4306c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4346c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4386c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x43c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4406c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4446c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4486c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x44c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4506c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4546c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4586c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x45c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4606c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4646c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4686c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x46c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4706c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4746c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4786c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x47c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4806c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4846c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4886c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x48c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4906c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4946c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4986c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x49c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4a86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4ac00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4ac18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4ac20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4ac24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4ac44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4ac68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4ac6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4b86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4bc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4bc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4bc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4bc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4bc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4bc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4bc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4c86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4cc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4cc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4cc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4cc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4cc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4cc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4cc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4d86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4dc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4dc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4dc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4dc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4dc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4dc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4dc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4e86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4ec00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4ec18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4ec20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4ec24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4ec44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4ec68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4ec6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4f86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4fc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4fc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4fc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4fc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4fc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4fc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x4fc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5006c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5046c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5086c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x50c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5106c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5146c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5186c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x51c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5206c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5246c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5286c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x52c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5306c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5346c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5386c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x53c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5406c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5446c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5486c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x54c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5506c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5546c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5586c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x55c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5606c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5646c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5686c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x56c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5706c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5746c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5786c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x57c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5806c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5846c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5886c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x58c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5906c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5946c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5986c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x59c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5a86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5ac00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5ac18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5ac20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5ac24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5ac44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5ac68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5ac6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5b86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5bc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5bc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5bc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5bc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5bc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5bc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5bc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5c86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5cc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5cc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5cc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5cc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5cc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5cc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5cc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5d86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5dc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5dc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5dc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5dc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5dc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5dc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5dc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5e86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5ec00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5ec18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5ec20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5ec24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5ec44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5ec68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5ec6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5f86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5fc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5fc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5fc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5fc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5fc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5fc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x5fc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6006c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6046c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6086c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x60c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6106c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6146c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6186c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x61c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6206c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6246c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6286c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x62c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6306c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6346c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6386c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x63c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6406c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6446c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6486c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x64c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6506c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6546c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6586c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x65c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6606c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6646c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6686c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x66c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6706c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6746c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6786c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x67c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6806c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6846c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6886c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x68c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6906c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6946c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6986c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x69c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6a86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6ac00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6ac18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6ac20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6ac24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6ac44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6ac68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6ac6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6b86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6bc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6bc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6bc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6bc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6bc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6bc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6bc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6c86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6cc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6cc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6cc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6cc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6cc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6cc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6cc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6d86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6dc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6dc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6dc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6dc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6dc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6dc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6dc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6e86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6ec00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6ec18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6ec20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6ec24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6ec44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6ec68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6ec6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6f86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6fc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6fc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6fc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6fc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6fc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6fc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x6fc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7006c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7046c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7086c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x70c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7106c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7146c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7186c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x71c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7206c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7246c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7286c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x72c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7306c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7346c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7386c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x73c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7406c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7446c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7486c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x74c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7506c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7546c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7586c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x75c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7606c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7646c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7686c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x76c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7706c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7746c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7786c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x77c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7806c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7846c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7886c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x78c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7906c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7946c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7986c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79c00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79c18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79c20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79c24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79c44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79c68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x79c6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7a86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7ac00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7ac18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7ac20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7ac24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7ac44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7ac68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7ac6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7b86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7bc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7bc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7bc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7bc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7bc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7bc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7bc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7c86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7cc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7cc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7cc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7cc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7cc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7cc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7cc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7d86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7dc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7dc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7dc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7dc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7dc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7dc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7dc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7e86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7ec00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7ec18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7ec20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7ec24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7ec44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7ec68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7ec6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f000, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f018, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f020, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f024, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f044, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f068, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f06c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f400, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f418, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f420, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f424, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f444, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f468, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f46c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f800, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f818, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f820, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f824, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f844, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f868, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7f86c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7fc00, 0x27912810, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7fc18, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7fc20, 0x00000300, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7fc24, 0x000000c8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7fc44, 0xffffff7f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7fc68, 0x61a88158, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x7fc6c, 0x00000bd8, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_PON_EARLY },
	{ 0x14000, 7, zx_burst_5852_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x14040, 6, zx_burst_5853_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1405c, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x14064, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1407c, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1408c, 0x00000007, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x14090, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x14094, 0x00000204, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x14120, 8, zx_burst_5858_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x14240, 18, zx_burst_5859_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x14300, 9, zx_burst_5860_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x14328, 4, zx_burst_5861_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1433c, 4, zx_burst_5862_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x14350, 4, zx_burst_5863_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x14364, 4, zx_burst_5864_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x14378, 4, zx_burst_5865_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1438c, 4, zx_burst_5866_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x14500, 0x00002121, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x14504, 0x21210042, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x145cc, 0x00210000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x145d0, 0x2d2d0000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x145dc, 0x0000f4f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x145e4, 13, zx_burst_5870_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0004, 4, zx_burst_7019_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0020, 0x00000fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c0024, 0x00000106, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c0030, 0x00000101, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c0034, 0x00010001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c003c, 4, zx_burst_7022_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0054, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c0090, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c0094, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c009c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c00a0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c00a4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c00ac, 4, zx_burst_7026_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c00c0, 9, zx_burst_7027_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0100, 7, zx_burst_7028_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0400, 5, zx_burst_7029_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0420, 6, zx_burst_7030_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c043c, 4, zx_burst_7031_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0454, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c0490, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c0494, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c049c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c04a0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c04a4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c04ac, 4, zx_burst_7035_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c04c0, 9, zx_burst_7036_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0500, 7, zx_burst_7037_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0800, 5, zx_burst_7038_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0820, 6, zx_burst_7039_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c083c, 4, zx_burst_7040_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0854, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c0890, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c0894, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c089c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c08a0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c08a4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c08ac, 4, zx_burst_7044_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c08c0, 9, zx_burst_7045_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0900, 7, zx_burst_7046_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0c00, 5, zx_burst_7047_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0c20, 6, zx_burst_7048_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0c3c, 4, zx_burst_7049_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0c54, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c0c90, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c0c94, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c0c9c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c0ca0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c0ca4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c0cac, 4, zx_burst_7053_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0cc0, 9, zx_burst_7054_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c0d00, 7, zx_burst_7055_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1000, 5, zx_burst_7056_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1020, 6, zx_burst_7057_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c103c, 4, zx_burst_7058_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1054, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c1090, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c1094, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c109c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c10a0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c10a4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c10ac, 4, zx_burst_7062_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c10c0, 9, zx_burst_7063_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1100, 7, zx_burst_7064_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1400, 5, zx_burst_7065_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1420, 6, zx_burst_7066_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c143c, 4, zx_burst_7067_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1454, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c1490, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c1494, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c149c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c14a0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c14a4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c14ac, 4, zx_burst_7071_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c14c0, 9, zx_burst_7072_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1500, 7, zx_burst_7073_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1800, 5, zx_burst_7074_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1820, 6, zx_burst_7075_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c183c, 4, zx_burst_7076_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1854, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c1890, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c1894, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c189c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c18a0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c18a4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c18ac, 4, zx_burst_7080_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c18c0, 9, zx_burst_7081_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1900, 7, zx_burst_7082_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1c00, 5, zx_burst_7083_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1c20, 6, zx_burst_7084_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1c3c, 4, zx_burst_7085_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1c54, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c1c90, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c1c94, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c1c9c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c1ca0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c1ca4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c1cac, 4, zx_burst_7089_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1cc0, 9, zx_burst_7090_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c1d00, 7, zx_burst_7091_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2000, 5, zx_burst_7092_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2020, 6, zx_burst_7093_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c203c, 4, zx_burst_7094_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2054, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c2090, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c2094, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c209c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c20a0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c20a4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c20ac, 4, zx_burst_7098_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c20c0, 9, zx_burst_7099_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2100, 7, zx_burst_7100_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2400, 5, zx_burst_7101_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2420, 6, zx_burst_7102_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c243c, 4, zx_burst_7103_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2454, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c2490, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c2494, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c249c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c24a0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c24a4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c24ac, 4, zx_burst_7107_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c24c0, 9, zx_burst_7108_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2500, 7, zx_burst_7109_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2800, 5, zx_burst_7110_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2820, 6, zx_burst_7111_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c283c, 4, zx_burst_7112_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2854, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c2890, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c2894, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c289c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c28a0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c28a4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c28ac, 4, zx_burst_7116_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c28c0, 9, zx_burst_7117_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2900, 7, zx_burst_7118_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2c00, 5, zx_burst_7119_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2c20, 6, zx_burst_7120_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2c3c, 4, zx_burst_7121_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2c54, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c2c90, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c2c94, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c2c9c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c2ca0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c2ca4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c2cac, 4, zx_burst_7125_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2cc0, 9, zx_burst_7126_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c2d00, 7, zx_burst_7127_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3000, 5, zx_burst_7128_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3020, 6, zx_burst_7129_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c303c, 4, zx_burst_7130_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3054, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c3090, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c3094, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c309c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c30a0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c30a4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c30ac, 4, zx_burst_7134_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c30c0, 9, zx_burst_7135_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3100, 7, zx_burst_7136_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3400, 5, zx_burst_7137_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3420, 6, zx_burst_7138_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c343c, 4, zx_burst_7139_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3454, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c3490, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c3494, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c349c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c34a0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c34a4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c34ac, 4, zx_burst_7143_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c34c0, 9, zx_burst_7144_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3500, 7, zx_burst_7145_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3800, 5, zx_burst_7146_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3820, 6, zx_burst_7147_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c383c, 4, zx_burst_7148_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3854, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c3890, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c3894, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c389c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c38a0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c38a4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c38ac, 4, zx_burst_7152_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c38c0, 9, zx_burst_7153_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3900, 7, zx_burst_7154_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3c00, 5, zx_burst_7155_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3c20, 6, zx_burst_7156_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3c3c, 4, zx_burst_7157_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3c54, 0x00000490, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c3c90, 0x000003aa, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c3c94, 0x0000007f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c3c9c, 0x00002e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c3ca0, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c3ca4, 0x00f42e00, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c3cac, 4, zx_burst_7161_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3cc0, 9, zx_burst_7162_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c3d00, 7, zx_burst_7163_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c4000, 7, zx_burst_7164_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c4020, 0x0007d000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c4028, 0x00001388, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c4030, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c4034, 0x00001869, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c4200, 0x0101012d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c4204, 0x3810e62e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c4268, 0xb8000000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c426c, 0x22222222, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c4284, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c5000, 7, zx_burst_7171_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c5020, 0x0007d000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c5028, 0x00001388, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c5030, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c5034, 0x00001869, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c5200, 0x0101012d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c5204, 0x3810e62e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c5268, 0xb8000000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c526c, 0x22222222, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c5284, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c6000, 7, zx_burst_7178_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c6020, 0x0007d000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c6028, 0x00001388, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c6030, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c6034, 0x00001869, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c6200, 0x0101012d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c6204, 0x3810e62e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c6268, 0xb8000000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c626c, 0x22222222, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c6284, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c7000, 7, zx_burst_7185_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c7020, 0x0007d000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c7028, 0x00001388, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c7030, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c7034, 0x00001869, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c7200, 0x0101012d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c7204, 0x3810e62e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c7268, 0xb8000000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c726c, 0x22222222, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c7284, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8014, 0x01000fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8018, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c801c, 0x0001ffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8054, 0x00000002, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c80a8, 0x62e95900, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c80ac, 0x0000c8a3, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c80b0, 0x00000102, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8180, 0x00000004, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8184, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8204, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c82d4, 0x00005555, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c83c0, 8, zx_burst_7198_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c8630, 0x00000080, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8638, 0x000000c0, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8c00, 10, zx_burst_7201_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c8c40, 0x2e2d172e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8c48, 0xd10306f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8c4c, 0xe6f40022, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8c54, 0x00f40000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8c5c, 0x00f40000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8c64, 0x00f40000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8e00, 6, zx_burst_7207_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1c8e1c, 0x62e95900, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8e20, 0x0000c8a3, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1c8e24, 0x42015400, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc014, 8, zx_burst_7209_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cc054, 0x00202000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc058, 0x00000012, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc088, 0x00007fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc090, 0x00e400e4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc094, 0x00000004, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc098, 0x7fff7fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc0c8, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc0d0, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc0d4, 0x00000007, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc1cc, 0x000004e6, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc1d0, 0x00000048, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc1e0, 17, zx_burst_7216_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cc260, 10, zx_burst_7217_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cc290, 4, zx_burst_7218_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cc300, 0x24904111, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc304, 0x01004851, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc394, 8, zx_burst_7220_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cc3b8, 0x04d504d5, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc3c4, 0x0000052e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc3e0, 7, zx_burst_7223_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cc814, 8, zx_burst_7224_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cc854, 0x00202000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc858, 0x00000012, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc880, 0x00000600, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc888, 0x00007fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc890, 0x00e400e4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc894, 0x00000004, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc898, 0x7fff7fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc8c8, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc8d0, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc8d4, 0x00000007, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc9cc, 0x000004e6, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc9d0, 0x00000048, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cc9e0, 17, zx_burst_7232_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cca60, 10, zx_burst_7233_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cca90, 4, zx_burst_7234_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1ccb00, 0x24904111, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ccb04, 0x01004851, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ccb94, 8, zx_burst_7236_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1ccbb8, 0x04d504d5, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ccbc4, 0x0000052e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ccbe0, 7, zx_burst_7239_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cd014, 8, zx_burst_7240_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cd054, 0x00202000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd058, 0x00000012, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd080, 0x00000600, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd088, 0x00007fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd090, 0x00e400e4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd094, 0x00000004, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd098, 0x7fff7fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd0c8, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd0d0, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd0d4, 0x00000007, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd1cc, 0x000004e6, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd1d0, 0x00000048, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd1e0, 17, zx_burst_7248_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cd260, 10, zx_burst_7249_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cd290, 4, zx_burst_7250_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cd300, 0x24904111, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd304, 0x01004851, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd394, 8, zx_burst_7252_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cd3b8, 0x04d504d5, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd3c4, 0x0000052e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd3e0, 7, zx_burst_7255_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cd814, 8, zx_burst_7256_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cd854, 0x00202000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd858, 0x00000012, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd880, 0x00000600, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd888, 0x00007fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd890, 0x00e400e4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd894, 0x00000004, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd898, 0x7fff7fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd8c8, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd8d0, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd8d4, 0x00000007, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd9cc, 0x000004e6, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd9d0, 0x00000048, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cd9e0, 17, zx_burst_7264_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cda60, 10, zx_burst_7265_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cda90, 4, zx_burst_7266_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cdb00, 0x24904111, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cdb04, 0x01004851, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cdb94, 8, zx_burst_7268_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cdbb8, 0x04d504d5, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cdbc4, 0x0000052e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cdbe0, 7, zx_burst_7271_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1ce014, 8, zx_burst_7272_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1ce054, 0x00202000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce058, 0x00000012, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce080, 0x00000600, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce088, 0x00007fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce090, 0x00e400e4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce094, 0x00000004, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce098, 0x7fff7fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce0c8, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce0d0, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce0d4, 0x00000007, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce1cc, 0x000004e6, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce1d0, 0x00000048, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce1e0, 17, zx_burst_7280_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1ce260, 10, zx_burst_7281_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1ce290, 4, zx_burst_7282_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1ce300, 0x24904111, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce304, 0x01004851, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce394, 8, zx_burst_7284_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1ce3b8, 0x04d504d5, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce3c4, 0x0000052e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce3e0, 7, zx_burst_7287_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1ce814, 8, zx_burst_7288_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1ce854, 0x00202000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce858, 0x00000012, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce880, 0x00000600, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce888, 0x00007fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce890, 0x00e400e4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce894, 0x00000004, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce898, 0x7fff7fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce8c8, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce8d0, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce8d4, 0x00000007, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce9cc, 0x000004e6, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce9d0, 0x00000048, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ce9e0, 17, zx_burst_7296_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cea60, 10, zx_burst_7297_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cea90, 4, zx_burst_7298_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1ceb00, 0x24904111, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ceb04, 0x01004851, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ceb94, 8, zx_burst_7300_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cebb8, 0x04d504d5, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cebc4, 0x0000052e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cebe0, 7, zx_burst_7303_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cf014, 8, zx_burst_7304_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cf054, 0x00202000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf058, 0x00000012, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf080, 0x00000600, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf088, 0x00007fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf090, 0x00e400e4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf094, 0x00000004, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf098, 0x7fff7fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf0c8, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf0d0, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf0d4, 0x00000007, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf1cc, 0x000004e6, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf1d0, 0x00000048, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf1e0, 17, zx_burst_7312_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cf260, 10, zx_burst_7313_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cf290, 4, zx_burst_7314_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cf300, 0x24904111, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf304, 0x01004851, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf394, 8, zx_burst_7316_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cf3b8, 0x04d504d5, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf3c4, 0x0000052e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf3e0, 7, zx_burst_7319_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cf814, 8, zx_burst_7320_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cf854, 0x00202000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf858, 0x00000012, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf880, 0x00000600, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf888, 0x00007fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf890, 0x00e400e4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf894, 0x00000004, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf898, 0x7fff7fff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf8c8, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf8d0, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf8d4, 0x00000007, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf9cc, 0x000004e6, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf9d0, 0x00000048, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cf9e0, 17, zx_burst_7328_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cfa60, 10, zx_burst_7329_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cfa90, 4, zx_burst_7330_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cfb00, 0x24904111, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cfb04, 0x01004851, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cfb94, 8, zx_burst_7332_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1cfbb8, 0x04d504d5, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cfbc4, 0x0000052e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1cfbe0, 7, zx_burst_7335_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d4000, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4004, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4008, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4018, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d402c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4048, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4080, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d40c0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4140, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4148, 4, zx_burst_7343_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d4218, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4224, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4228, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4240, 8, zx_burst_7346_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d4400, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4404, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4408, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4418, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d442c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4448, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4480, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d44c0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4540, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4548, 4, zx_burst_7354_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d4618, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4624, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4628, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4640, 8, zx_burst_7357_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d4800, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4804, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4808, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4818, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d482c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4848, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4880, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d48c0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4940, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4948, 4, zx_burst_7365_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d4a18, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4a24, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4a28, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4a40, 8, zx_burst_7368_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d4c00, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4c04, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4c08, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4c18, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4c2c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4c48, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4c80, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4cc0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4d40, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4d48, 4, zx_burst_7376_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d4e18, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4e24, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4e28, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d4e40, 8, zx_burst_7379_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d5000, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5004, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5008, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5018, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d502c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5048, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5080, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d50c0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5140, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5148, 4, zx_burst_7387_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d5218, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5224, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5228, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5240, 8, zx_burst_7390_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d5400, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5404, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5408, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5418, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d542c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5448, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5480, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d54c0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5540, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5548, 4, zx_burst_7398_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d5618, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5624, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5628, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5640, 8, zx_burst_7401_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d5800, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5804, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5808, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5818, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d582c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5848, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5880, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d58c0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5940, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5948, 4, zx_burst_7409_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d5a18, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5a24, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5a28, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5a40, 8, zx_burst_7412_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d5c00, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5c04, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5c08, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5c18, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5c2c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5c48, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5c80, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5cc0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5d40, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5d48, 4, zx_burst_7420_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d5e18, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5e24, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5e28, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d5e40, 8, zx_burst_7423_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d6000, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6004, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6008, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6018, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d602c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6048, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6080, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d60c0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6140, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6148, 4, zx_burst_7431_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d6218, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6224, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6228, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6240, 8, zx_burst_7434_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d6400, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6404, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6408, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6418, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d642c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6448, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6480, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d64c0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6540, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6548, 4, zx_burst_7442_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d6618, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6624, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6628, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6640, 8, zx_burst_7445_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d6800, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6804, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6808, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6818, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d682c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6848, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6880, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d68c0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6940, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6948, 4, zx_burst_7453_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d6a18, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6a24, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6a28, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6a40, 8, zx_burst_7456_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d6c00, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6c04, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6c08, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6c18, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6c2c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6c48, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6c80, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6cc0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6d40, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6d48, 4, zx_burst_7464_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d6e18, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6e24, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6e28, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d6e40, 8, zx_burst_7467_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d7000, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7004, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7008, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7018, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d702c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7048, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7080, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d70c0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7140, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7148, 4, zx_burst_7475_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d7218, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7224, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7228, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7240, 8, zx_burst_7478_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d7400, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7404, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7408, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7418, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d742c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7448, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7480, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d74c0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7540, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7548, 4, zx_burst_7486_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d7618, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7624, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7628, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7640, 8, zx_burst_7489_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d7800, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7804, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7808, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7818, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d782c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7848, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7880, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d78c0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7940, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7948, 4, zx_burst_7497_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d7a18, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7a24, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7a28, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7a40, 8, zx_burst_7500_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d7c00, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7c04, 0x000003e7, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7c08, 0x00000834, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7c18, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7c2c, 0x00000018, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7c48, 0x0bebc200, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7c80, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7cc0, 0x00201f40, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7d40, 0x00000009, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7d48, 4, zx_burst_7508_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d7e18, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7e24, 0x0000002e, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7e28, 0x00000003, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d7e40, 8, zx_burst_7511_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d8000, 0x000010c0, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d8014, 0x0000001f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d8024, 0x000005dc, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d8050, 0x00c04077, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d8080, 18, zx_burst_7516_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d8100, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d8110, 0xf4f410a0, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d8114, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d8124, 5, zx_burst_7519_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d8140, 4, zx_burst_7520_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d815c, 0x60540099, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d8168, 0x80000000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d816c, 0xc00040c6, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d8170, 0x019a0000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d9000, 0x000010c0, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d9014, 0x0000001f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d9024, 0x000005dc, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d9050, 0x00c04077, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d9080, 18, zx_burst_7527_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d9100, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d9110, 0xf4f410a0, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d9114, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d9124, 5, zx_burst_7530_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d9140, 4, zx_burst_7531_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1d915c, 0x60540099, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d9168, 0x80000000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d916c, 0xc00040c6, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1d9170, 0x019a0000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1da000, 0x000010c0, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1da014, 0x0000001f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1da024, 0x000005dc, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1da050, 0x00c04077, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1da080, 18, zx_burst_7538_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1da100, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1da110, 0xf4f410a0, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1da114, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1da124, 5, zx_burst_7541_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1da140, 4, zx_burst_7542_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1da15c, 0x60540099, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1da168, 0x80000000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1da16c, 0xc00040c6, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1da170, 0x019a0000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1db000, 0x000010c0, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1db014, 0x0000001f, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1db024, 0x000005dc, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1db050, 0x00c04077, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1db080, 18, zx_burst_7549_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1db100, 0x000000f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1db110, 0xf4f410a0, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1db114, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1db124, 5, zx_burst_7552_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1db140, 4, zx_burst_7553_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1db15c, 0x60540099, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1db168, 0x80000000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1db16c, 0xc00040c6, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1db170, 0x019a0000, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc014, 4, zx_burst_7556_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dc034, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc038, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc03c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc080, 7, zx_burst_7558_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dc0a0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc0b8, 8, zx_burst_7560_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dc108, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc140, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc414, 4, zx_burst_7563_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dc434, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc438, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc43c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc480, 7, zx_burst_7565_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dc4a0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc4b8, 8, zx_burst_7567_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dc508, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc540, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc814, 4, zx_burst_7570_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dc834, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc838, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc83c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc880, 7, zx_burst_7572_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dc8a0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc8b8, 8, zx_burst_7574_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dc908, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dc940, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dcc14, 4, zx_burst_7577_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dcc34, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dcc38, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dcc3c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dcc80, 7, zx_burst_7579_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dcca0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dccb8, 8, zx_burst_7581_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dcd08, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dcd40, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd014, 4, zx_burst_7584_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dd034, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd038, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd03c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd080, 7, zx_burst_7586_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dd0a0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd0b8, 8, zx_burst_7588_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dd108, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd140, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd414, 4, zx_burst_7591_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dd434, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd438, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd43c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd480, 7, zx_burst_7593_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dd4a0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd4b8, 8, zx_burst_7595_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dd508, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd540, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd814, 4, zx_burst_7598_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dd834, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd838, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd83c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd880, 7, zx_burst_7600_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dd8a0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd8b8, 8, zx_burst_7602_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dd908, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dd940, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ddc14, 4, zx_burst_7605_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1ddc34, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ddc38, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ddc3c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ddc80, 7, zx_burst_7607_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1ddca0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ddcb8, 8, zx_burst_7609_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1ddd08, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ddd40, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de014, 4, zx_burst_7612_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1de034, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de038, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de03c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de080, 7, zx_burst_7614_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1de0a0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de0b8, 8, zx_burst_7616_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1de108, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de140, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de414, 4, zx_burst_7619_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1de434, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de438, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de43c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de480, 7, zx_burst_7621_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1de4a0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de4b8, 8, zx_burst_7623_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1de508, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de540, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de814, 4, zx_burst_7626_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1de834, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de838, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de83c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de880, 7, zx_burst_7628_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1de8a0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de8b8, 8, zx_burst_7630_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1de908, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1de940, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dec14, 4, zx_burst_7633_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dec34, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dec38, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dec3c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dec80, 7, zx_burst_7635_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1deca0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1decb8, 8, zx_burst_7637_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1ded08, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1ded40, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df014, 4, zx_burst_7640_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1df034, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df038, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df03c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df080, 7, zx_burst_7642_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1df0a0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df0b8, 8, zx_burst_7644_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1df108, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df140, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df414, 4, zx_burst_7647_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1df434, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df438, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df43c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df480, 7, zx_burst_7649_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1df4a0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df4b8, 8, zx_burst_7651_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1df508, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df540, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df814, 4, zx_burst_7654_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1df834, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df838, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df83c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df880, 7, zx_burst_7656_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1df8a0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df8b8, 8, zx_burst_7658_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1df908, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1df940, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dfc14, 4, zx_burst_7661_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dfc34, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dfc38, 0x000086dd, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dfc3c, 0x00000800, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dfc80, 7, zx_burst_7663_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dfca0, 0x000004f4, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dfcb8, 8, zx_burst_7665_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1dfd08, 0x0000003d, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1dfd40, 0x00030001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e0004, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e001c, 5, zx_burst_7669_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e0118, 8, zx_burst_7670_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e0194, 0x00ffffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e019c, 0x007fffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e03e0, 8, zx_burst_7673_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e0804, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e081c, 5, zx_burst_7675_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e0918, 8, zx_burst_7676_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e0994, 0x00ffffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e099c, 0x007fffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e0be0, 8, zx_burst_7679_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e1004, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e101c, 5, zx_burst_7681_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e1118, 8, zx_burst_7682_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e1194, 0x00ffffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e119c, 0x007fffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e13e0, 8, zx_burst_7685_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e1804, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e181c, 5, zx_burst_7687_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e1918, 8, zx_burst_7688_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e1994, 0x00ffffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e199c, 0x007fffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e1be0, 8, zx_burst_7691_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e2004, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e201c, 5, zx_burst_7693_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e2118, 8, zx_burst_7694_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e2194, 0x00ffffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e219c, 0x007fffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e23e0, 8, zx_burst_7697_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e2804, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e281c, 5, zx_burst_7699_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e2918, 8, zx_burst_7700_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e2994, 0x00ffffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e299c, 0x007fffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e2be0, 8, zx_burst_7703_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e3004, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e301c, 5, zx_burst_7705_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e3118, 8, zx_burst_7706_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e3194, 0x00ffffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e319c, 0x007fffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e33e0, 8, zx_burst_7709_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e3804, 0x00000001, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e381c, 5, zx_burst_7711_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e3918, 8, zx_burst_7712_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
	{ 0x1e3994, 0x00ffffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e399c, 0x007fffff, NULL, ZX_BURST_KIND_SINGLE, ZX_BURST_WIN_BASE },
	{ 0x1e3be0, 8, zx_burst_7715_data, ZX_BURST_KIND_RUN, ZX_BURST_WIN_BASE },
};

;

#define ZX_STOCK_OPS_LEN 10621

/* Per-block slice indices into zx_stock_ops[]. Drivers walk one
 * block at a time so explicit zx_<block>_init() calls (Phase 9+)
 * can be interleaved at the right point in the init sequence. */
/* PON_LOW: handled by explicit zx_<block>_init() — no ops emitted */

#define ZX_STOCK_OPS_PON_B_START 0
#define ZX_STOCK_OPS_PON_B_END   1792
#define ZX_STOCK_OPS_PON_B_LEN   1792
#define ZX_STOCK_OPS_PON_TAIL_START 1792
#define ZX_STOCK_OPS_PON_TAIL_END   1792  /* handled by explicit C */
#define ZX_STOCK_OPS_PON_TAIL_LEN   0
#define ZX_STOCK_OPS_NPP_START 1792
#define ZX_STOCK_OPS_NPP_END   1815
#define ZX_STOCK_OPS_NPP_LEN   23
#define ZX_STOCK_OPS_TM_START 1815
#define ZX_STOCK_OPS_TM_END   1815  /* handled by explicit C */
#define ZX_STOCK_OPS_TM_LEN   0
#define ZX_STOCK_OPS_PP_FUC_START 1815
#define ZX_STOCK_OPS_PP_FUC_END   2722
#define ZX_STOCK_OPS_PP_FUC_LEN   907

/* Sanity: total individual register writes when replayed must equal
 * the original 22363 entries minus the 14778 entries in
 * blocks handled by explicit zx_<block>_init() functions. */
#define ZX_STOCK_OPS_WRITES_EXPECTED 2722

#endif /* ZX_STOCK_BURSTS_H */

