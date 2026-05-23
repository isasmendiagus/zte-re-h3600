// module: plat-zxylzb_9128S.ko
// function: serdes_err_cnt_reset @ 0x1b7a0
// size: 52 bytes
//

void serdes_err_cnt_reset(void)

{
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) & 0x7fffffff;
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) | 0x80000000;
  return;
}

