# OF_DECLARE chain extraction

For each compatible string, follow LE32 refs into struct, dump function ptrs.

| Compatible | str addr | refs to str | func ptrs found | decompiled |
|---|---|---|---|---|
| `denali,denali-nand-dt` | 0xc04b97cc | 2 | 3 | FUN_c0239afc, FUN_c0239abc, FUN_c0239adc |
| `rohm,dh2228fv` | 0xc04be9c4 | 2 | 4 | FUN_c0252a50, FUN_c0254120, FUN_c0252b88, FUN_c0254198 |
| `snps,del_p1p2p3_quirk` | 0xc05b760c | 0 | 0 | (none) |
| `snps,del_phy_power_chg_quirk` | 0xc05b7624 | 0 | 0 | (none) |
| `snps,dis_u2_susphy_quirk` | 0xc05b7694 | 0 | 0 | (none) |
| `snps,dis_u3_susphy_quirk` | 0xc05b7678 | 0 | 0 | (none) |
| `snps,disable_scramble_quirk` | 0xc05b75a8 | 0 | 0 | (none) |
| `snps,dwc2` | 0xc04c1944 | 0 | 0 | (none) |
| `snps,dwc3` | 0xc04c0770 | 2 | 3 | FUN_c027d568, FUN_c027d434, FUN_c00aaa9c |
| `snps,has-lpm-erratum` | 0xc05b7524 | 1 | 2 | FUN_c027c740, FUN_c027c604 |
| `snps,hird-threshold` | 0xc05b756c | 0 | 0 | (none) |
| `snps,is-utmi-l1-suspend` | 0xc05b7554 | 0 | 0 | (none) |
| `snps,lfps_filter_quirk` | 0xc05b7644 | 0 | 0 | (none) |
| `snps,lpm-nyet-threshold` | 0xc05b753c | 1 | 2 | FUN_c027c740__dup, FUN_c027c604__dup |
| `snps,req_p1p2p3_quirk` | 0xc05b75f4 | 0 | 0 | (none) |
| `snps,rx_detect_poll_quirk` | 0xc05b765c | 0 | 0 | (none) |
| `snps,tx_de_emphasis` | 0xc05b76cc | 0 | 0 | (none) |
| `snps,tx_de_emphasis_quirk` | 0xc05b76b0 | 0 | 0 | (none) |
| `snps,u2exit_lfps_quirk` | 0xc05b75c4 | 0 | 0 | (none) |
| `snps,u2ss_inp3_quirk` | 0xc05b75dc | 0 | 0 | (none) |
| `snps,usb3_lpm_capable` | 0xc05b7580 | 0 | 0 | (none) |
| `zte,ZX279127-pcie` | 0xc04746cc | 2 | 0 | (none) |
| `zte,ZX279127-spifc` | 0xc04b9954 | 2 | 2 | FUN_c0239afc__dup, FUN_c0239adc__dup |
| `zte,ZX279127-uart` | 0xc04b4d14 | 2 | 2 | FUN_c01dfe8c, FUN_c01e03fc |
| `zte,iram` | 0xc0584ee8 | 0 | 0 | (none) |
| `zte,zx279127-dwc2` | 0xc04c1acc | 0 | 0 | (none) |
| `zte,zx279127-i2c` | 0xc04c9c6c | 2 | 4 | FUN_c02aabe4, FUN_c02a9a90, FUN_c02a9de4, FUN_c02aab7c |
| `zte,zx279127-lsp0crpm` | 0xc0660f10 | 1 | 1 | FUN_c064b740 |
| `zte,zx279127-lsp1crpm` | 0xc0660e4c | 1 | 1 | FUN_c064b084 |
| `zte,zx279127-pcie` | 0xc0584b48 | 1 | 0 | (none) |
| `zte,zx279127-ssp` | 0xc04bebcc | 2 | 2 | FUN_c0254120__dup, FUN_c0254198__dup |
| `zte,zx279127-topcrm` | 0xc0660fd4 | 1 | 1 | FUN_c064a254 |
| `zte,zx279128-dwc3` | 0xc04c1444 | 2 | 2 | FUN_c027ee60, FUN_c027eedc |
| `zte,zx279128-smp` | 0xc0584940 | 2 | 8 | FUN_c06379dc, FUN_c00148ec, FUN_c0014c70, FUN_c0014d54, FUN_c0014b3c, FUN_c0014894, FUN_c0014d24, FUN_c0014d84 |
| `zxic,tempsensor` | 0xc04ce7dc | 4 | 4 | FUN_c02c8740, FUN_c02c85ec, FUN_c00c7ce0, FUN_c02c7f40 |
