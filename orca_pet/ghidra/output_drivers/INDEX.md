# Driver-function index by peripheral

Each peripheral physical address from extracted.dts is searched as a 32-bit
LE constant in code. Functions containing such loads are decompiled.

| Periph | Phys addr | LE32 hits | Functions extracted |
|---|---|---|---|
| gic | 0x00801000 | 0 | (no func found) |
| timer_a9 | 0x00800200 | 0 | (no func found) |
| twd_wdt | 0x00800620 | 0 | (no func found) |
| mg_crm | 0x00804000 | 0 | (no func found) |
| l2_pl310 | 0x00c00000 | 2 | (no func found) |
| iram | 0x00200800 | 2 | (no func found) |
| nand_data | 0x00d80000 | 2 | (no func found) |
| nand_reg | 0x00d00000 | 2 | (no func found) |
| mmc_sd | 0x08980000 | 0 | (no func found) |
| usb2_dwc2 | 0x09000000 | 3 | (no func found) |
| usb3_dwc3 | 0x09100000 | 0 | (no func found) |
| pcie | 0x10000000 | 7 | (no func found) |
| topcrm | 0x94000000 | 2 | (no func found) |
| temp_sens | 0x94100034 | 0 | (no func found) |
| lsp0crpm | 0x94400000 | 0 | (no func found) |
| uart0 | 0x94404000 | 2 | FUN_c001092c |
| uart1 | 0x94405000 | 0 | (no func found) |
| spifc | 0x94406000 | 0 | (no func found) |
| lsp1crpm | 0x9a100000 | 0 | (no func found) |
| mdio | 0x9a101000 | 0 | (no func found) |
| i2c0 | 0x9a102000 | 0 | (no func found) |
| i2c1 | 0x9a103000 | 0 | (no func found) |
| ssp | 0x9a105000 | 0 | (no func found) |
| tdm | 0x9a106000 | 0 | (no func found) |
| gephy0 | 0x9b000000 | 2 | (no func found) |
| gephy1 | 0x9b100000 | 0 | (no func found) |
| gephy2 | 0x9b200000 | 0 | (no func found) |
| gephy3 | 0x9b300000 | 0 | (no func found) |
| pon | 0x92000000 | 2 | (no func found) |
| tm | 0x92340000 | 0 | (no func found) |
| pp | 0x92380000 | 0 | (no func found) |
| npp | 0x921c0000 | 0 | (no func found) |
| idm | 0x921c8000 | 0 | (no func found) |
