// module: plat-zxylzb_9128S.ko
// function: serdes_get_err_cnt @ 0x1b764
// size: 36 bytes
//

uint serdes_get_err_cnt(void)

{
  return *(uint *)(pon_serdes_base + 0x60) >> 0x10 | *(int *)(pon_serdes_base + 100) << 0x10;
}

