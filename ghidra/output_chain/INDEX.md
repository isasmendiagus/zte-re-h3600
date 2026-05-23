# OF_DECLARE chain extraction

For each compatible string, follow LE32 refs into struct, dump function ptrs.

| Compatible | str addr | refs to str | func ptrs found | decompiled |
|---|---|---|---|---|
| `rohm,dh2228fv` | 0xc04bf0e8 | 2 | 4 | FUN_c0253540, FUN_c0251df8, FUN_c0251f30, FUN_c02534c8 |
| `snps,del_p1p2p3_quirk` | 0xc05b8938 | 0 | 0 | (none) |
| `snps,del_phy_power_chg_quirk` | 0xc05b8950 | 0 | 0 | (none) |
| `snps,dis_u2_susphy_quirk` | 0xc05b89c0 | 0 | 0 | (none) |
| `snps,dis_u3_susphy_quirk` | 0xc05b89a4 | 0 | 0 | (none) |
| `snps,disable_scramble_quirk` | 0xc05b88d4 | 0 | 0 | (none) |
| `snps,dwc2` | 0xc04c2068 | 0 | 0 | (none) |
| `snps,dwc3` | 0xc04c0e94 | 2 | 3 | FUN_c027c90c, FUN_c00aa818, FUN_c027c7d8 |
| `snps,has-lpm-erratum` | 0xc05b8850 | 1 | 2 | FUN_c027bae4, FUN_c027b9a8 |
| `snps,hird-threshold` | 0xc05b8898 | 0 | 0 | (none) |
| `snps,is-utmi-l1-suspend` | 0xc05b8880 | 0 | 0 | (none) |
| `snps,lfps_filter_quirk` | 0xc05b8970 | 0 | 0 | (none) |
| `snps,lpm-nyet-threshold` | 0xc05b8868 | 1 | 2 | FUN_c027bae4__dup, FUN_c027b9a8__dup |
| `snps,req_p1p2p3_quirk` | 0xc05b8920 | 0 | 0 | (none) |
| `snps,rx_detect_poll_quirk` | 0xc05b8988 | 0 | 0 | (none) |
| `snps,tx_de_emphasis` | 0xc05b89f8 | 0 | 0 | (none) |
| `snps,tx_de_emphasis_quirk` | 0xc05b89dc | 0 | 0 | (none) |
| `snps,u2exit_lfps_quirk` | 0xc05b88f0 | 0 | 0 | (none) |
| `snps,u2ss_inp3_quirk` | 0xc05b8908 | 0 | 0 | (none) |
| `snps,usb3_lpm_capable` | 0xc05b88ac | 0 | 0 | (none) |
| `zte,ZX279127-pcie` | 0xc04755ac | 2 | 1 | FUN_c0015e04 |
| `zte,ZX279127-spifc` | 0xc04ba5ec | 2 | 1 | FUN_c023b770 |
| `zte,ZX279127-uart` | 0xc04b5af4 | 2 | 2 | FUN_c01dfe48, FUN_c01df8d8 |
| `zte,iram` | 0xc0585f78 | 1 | 0 | (none) |
| `zte,zx279127-dwc2` | 0xc04c21f0 | 0 | 0 | (none) |
| `zte,zx279127-i2c` | 0xc04ca390 | 2 | 4 | FUN_c02a9158, FUN_c02a9ef0, FUN_c02a9f58, FUN_c02a8e10 |
| `zte,zx279127-lsp0crpm` | 0xc06625b0 | 1 | 1 | FUN_c064c950 |
| `zte,zx279127-lsp1crpm` | 0xc06624ec | 1 | 1 | FUN_c064c294 |
| `zte,zx279127-pcie` | 0xc0585d18 | 1 | 1 | FUN_c0015e04__dup |
| `zte,zx279127-ssp` | 0xc04bf2f0 | 2 | 2 | FUN_c0253540__dup, FUN_c02534c8__dup |
| `zte,zx279127-topcrm` | 0xc0662674 | 1 | 1 | FUN_c064b464 |
| `zte,zx279128-dwc3` | 0xc04c1b68 | 2 | 2 | FUN_c027e280, FUN_c027e204 |
| `zte,zx279128-smp` | 0xc0585b10 | 2 | 8 | FUN_c0014d64, FUN_c0014d34, FUN_c06389dc, FUN_c0014874, FUN_c0014c50, FUN_c0014d04, FUN_c0014b1c, FUN_c00148cc |
| `zxic,tempsensor` | 0xc04cef00 | 4 | 4 | FUN_c02c72b4, FUN_c02c7960, FUN_c00c7a5c, FUN_c02c7ab4 |
