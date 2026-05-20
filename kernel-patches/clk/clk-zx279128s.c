// SPDX-License-Identifier: GPL-2.0
/*
 * ZTE ZX279128S clock controller driver — minimal skeleton
 *
 * Reverse-engineered from decompiled FUN_c064a254 (topcrm init in
 * stock vmlinux 4.1.25). Implements PLLs, clock tree mux/div/gate
 * to match the stock register layout.
 *
 * Register base: 0x94000000 (TOPCRM)
 *
 * NOTE: this is a SKELETON sufficient for first boot. The decompiled
 * function defines ~60 named clocks; only the bare minimum needed for
 * UART/timer/watchdog are exposed here. Extend as more peripherals
 * are brought up.
 */

#include <linux/clk-provider.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>

/* Register offsets within TOPCRM (extracted from stock kernel) */
#define TOPCRM_PLL_A9_CFG0	0x80
#define TOPCRM_PLL_A9_CFG1	0x84
#define TOPCRM_PLL_LSP_CFG0	0x90
#define TOPCRM_PLL_DDR_CFG0	0xa0
#define TOPCRM_PLL_AUDIO_CFG0	0x100
#define TOPCRM_PLL_PON_CFG0	0x110

#define TOPCRM_CLK_MUX0		0x04
#define TOPCRM_CLK_MUX1		0x0c
#define TOPCRM_CLK_GATE0	0x14
#define TOPCRM_CLK_GATE1	0x18

/* Clock IDs matching what the DTSI references */
#define CLK_OSC			0
#define CLK_PLL_A9		1
#define CLK_PLL_LSP		2
#define CLK_PLL_AUDIO		3
#define CLK_PLL_DDR		4
#define CLK_PLL_PON		5
#define CLK_A9_PERIPHCLK	0x17	/* used by global_timer + twd_wdt */
#define CLK_UART_WCLK		0x0e
#define CLK_NAND_WCLK		0x2b
#define CLK_USB_BUS		0x2c
#define CLK_USB_REF0		0x2e
#define CLK_USB_REF1		0x30
#define CLK_END			0x40

static struct clk_hw_onecell_data *zx_clk_data;

struct zx_pll_fixed {
	const char *name;
	unsigned long rate;
	int id;
};

/*
 * For first boot, define all PLLs as fixed-rate at their default
 * power-on values (BootROM has already locked them).
 * This avoids needing to write PLL registers, which is risky during
 * bring-up.
 */
static const struct zx_pll_fixed zx_plls[] = {
	{ "pll_a9",    1600000000UL, CLK_PLL_A9 },
	{ "pll_lsp",   1000000000UL, CLK_PLL_LSP },
	{ "pll_audio",  983000000UL, CLK_PLL_AUDIO },
	{ "pll_ddr",   1332000000UL, CLK_PLL_DDR },
	{ "pll_pon",    125000000UL, CLK_PLL_PON },
};

/* Derived clocks (fixed factors of PLLs) */
struct zx_fixed_factor {
	const char *name;
	const char *parent;
	unsigned long mult;
	unsigned long div;
	int id;
};

static const struct zx_fixed_factor zx_fixed_factors[] = {
	/* a9_periphclk = pll_a9 / 4 = 400 MHz (typical Cortex-A9 PERIPHCLK) */
	{ "a9_periphclk", "pll_a9", 1, 4, CLK_A9_PERIPHCLK },

	/* uart_wclk: stock uses osc24m direct → register as factor 1:1 */
	{ "uart_wclk", "osc24m", 1, 1, CLK_UART_WCLK },

	/* nand_wclk: 100 MHz from pll_lsp / 10 */
	{ "nand_wclk", "pll_lsp", 1, 10, CLK_NAND_WCLK },

	/* USB clocks: 60/100/125 MHz typical */
	{ "usb_bus_clk",  "pll_lsp", 1, 8,  CLK_USB_BUS },
	{ "usb_ref_clk0", "pll_pon", 1, 1,  CLK_USB_REF0 },
	{ "usb_ref_clk1", "pll_pon", 1, 1,  CLK_USB_REF1 },
};

static int zx279128s_topcrm_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct clk_hw *hw;
	int i;

	zx_clk_data = devm_kzalloc(&pdev->dev,
				   struct_size(zx_clk_data, hws, CLK_END),
				   GFP_KERNEL);
	if (!zx_clk_data)
		return -ENOMEM;

	zx_clk_data->num = CLK_END;
	for (i = 0; i < CLK_END; i++)
		zx_clk_data->hws[i] = ERR_PTR(-ENOENT);

	/* Register PLLs as fixed-rate */
	for (i = 0; i < ARRAY_SIZE(zx_plls); i++) {
		hw = clk_hw_register_fixed_rate(&pdev->dev, zx_plls[i].name,
						NULL, 0, zx_plls[i].rate);
		if (IS_ERR(hw)) {
			dev_err(&pdev->dev, "register %s failed: %ld\n",
				zx_plls[i].name, PTR_ERR(hw));
			return PTR_ERR(hw);
		}
		zx_clk_data->hws[zx_plls[i].id] = hw;
	}

	/* Register fixed-factor derived clocks */
	for (i = 0; i < ARRAY_SIZE(zx_fixed_factors); i++) {
		const struct zx_fixed_factor *f = &zx_fixed_factors[i];

		hw = clk_hw_register_fixed_factor(&pdev->dev, f->name,
						  f->parent, 0,
						  f->mult, f->div);
		if (IS_ERR(hw)) {
			dev_err(&pdev->dev, "register %s failed: %ld\n",
				f->name, PTR_ERR(hw));
			return PTR_ERR(hw);
		}
		zx_clk_data->hws[f->id] = hw;
	}

	return of_clk_add_hw_provider(np, of_clk_hw_onecell_get, zx_clk_data);
}

static const struct of_device_id zx279128s_topcrm_match[] = {
	{ .compatible = "zte,zx279128s-topcrm" },
	{ .compatible = "zte,zx279127-topcrm" },
	{ },
};
MODULE_DEVICE_TABLE(of, zx279128s_topcrm_match);

static struct platform_driver zx279128s_topcrm_driver = {
	.probe = zx279128s_topcrm_probe,
	.driver = {
		.name = "zx279128s-topcrm",
		.of_match_table = zx279128s_topcrm_match,
	},
};
builtin_platform_driver(zx279128s_topcrm_driver);
