# Function index across stock .ko modules

Source: `ALL_KMOD_FUNCTIONS.txt` (generated 2026-05-25 via arm-linux-gnueabi-nm)
Companion: `decomp_all_*.c` for the 5 modules we have Ghidra decomp for.

## Coverage

| Module | Funcs | Decomp | Notes |
|---|---|---|---|
| asix | 60 | ○ symbols only | |
| ax88179_178a | 43 | ○ symbols only | |
| cdc-acm | 44 | ○ symbols only | |
| cdc_ether | 9 | ○ symbols only | |
| cdc_ncm | 44 | ○ symbols only | |
| cdc_subset | 7 | ○ symbols only | |
| dsp_dev | 175 | ○ symbols only | |
| ehci-hcd | 88 | ○ symbols only | |
| ehci-pci | 8 | ○ symbols only | |
| idmfdb | 54 | ✓ FULL | |
| ko_debug | 6 | ○ symbols only | |
| kudp | 24 | ○ symbols only | |
| net1080 | 11 | ○ symbols only | |
| ohci-hcd | 53 | ○ symbols only | |
| ohci-pci | 14 | ○ symbols only | |
| patch | 13 | ○ symbols only | |
| plat-zxylzb_9128S | 249 | ✓ FULL | |
| rndis_host | 12 | ○ symbols only | |
| rtkatm | 26 | ○ symbols only | |
| shellproc | 38 | ○ symbols only | |
| switch | 235 | ✓ FULL | |
| tdm | 55 | ○ symbols only | |
| tm | 1293 | ✓ FULL | |
| usblp | 25 | ○ symbols only | |
| usbnet | 56 | ○ symbols only | |
| usb-storage | 67 | ○ symbols only | |
| usrline | 333 | ○ symbols only | |
| voip_codec | 755 | ○ symbols only | |
| wlan_debug_module | 65 | ○ symbols only | |
| zaurus | 8 | ○ symbols only | |
| zx_ponreg | 11 | ✓ FULL | |

## Index of interesting unique prefixes (search hints)

These prefixes appear in stock .ko symbols. Use them to grep `ALL_KMOD_FUNCTIONS.txt` or `decomp_all_*.c`.


## Quick lookup recipes

- Find function across all modules:
  ```
  grep -B1 "T sbrg_set_pt_da_lookup_en" ALL_KMOD_FUNCTIONS.txt
  ```
- Find module hosting a given function:
  ```
  grep -B500 "T fpga_write_reg" ALL_KMOD_FUNCTIONS.txt | grep "## MODULE:" | tail -1
  ```

## Index of interesting prefixes (search hints)

- `sbrg_*`  156 hits
- `cla_*`  82 hits
- `spa_*`  72 hits
- `dpa_*`  8 hits
- `tm_*`  340 hits
- `pp_*`  41 hits
- `idm_*`  59 hits
- `greg_*`  41 hits
- `sdet_*`  26 hits
- `adm_*`  38 hits
- `chip_*`  1 hits
- `pon_*`  122 hits
- `ethdrv_*`  13 hits
- `fpga_*`  9 hits
- `smac_*`  23 hits
- `proc_*`  7 hits
- `shell_*`  4 hits

## Quick lookup recipes

Find module hosting a function (look at MODULE: tag closest above):
```
awk "/## MODULE:/{mod=\$0} /T fpga_write_reg/{print mod; exit}" ALL_KMOD_FUNCTIONS.txt
```

Find all functions matching a prefix:
```
grep -E " T sbrg_set_" ALL_KMOD_FUNCTIONS.txt
```
