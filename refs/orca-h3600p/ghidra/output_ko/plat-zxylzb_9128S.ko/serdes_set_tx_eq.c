// module: plat-zxylzb_9128S.ko
// function: serdes_set_tx_eq @ 0x1c154
// size: 260 bytes
//

undefined4 serdes_set_tx_eq(int param_1)

{
  if (param_1 != 1) {
    if (param_1 == 2) {
      *pon_serdes_base = *pon_serdes_base & 0xfff1ffff | 0x80000;
      *pon_serdes_base = *pon_serdes_base | 0x80000000;
      pon_serdes_base[1] = pon_serdes_base[1] & 0xfffffff0 | 10;
      pon_serdes_base[1] = pon_serdes_base[1] & 0xffff87ff | 0x3000;
      printk("\nset tx 6db pre and post success \n");
    }
    return 0;
  }
  *pon_serdes_base = *pon_serdes_base & 0xfff1ffff | 0x80000;
  *pon_serdes_base = *pon_serdes_base | 0x80000000;
  pon_serdes_base[1] = pon_serdes_base[1] & 0xfffffff0 | 10;
  pon_serdes_base[1] = pon_serdes_base[1] & 0xffff87ff | 0x1800;
  printk("\nset tx 3db pre and post success \n");
  return 0;
}

