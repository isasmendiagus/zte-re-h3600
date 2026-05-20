// module: plat-zxylzb_9128S.ko
// function: serdes_set_rx_eq @ 0x1c258
// size: 160 bytes
//

undefined4 serdes_set_rx_eq(int param_1)

{
  if (param_1 != 1) {
    if (param_1 == 2) {
      *(uint *)(pon_serdes_base + 8) = *(uint *)(pon_serdes_base + 8) & 0xffffff8f;
      *(uint *)(pon_serdes_base + 8) = *(uint *)(pon_serdes_base + 8) & 0xffff8fff | 0x2000;
      printk("\nset rx 6db pre and post success \n");
    }
    return 0;
  }
  *(uint *)(pon_serdes_base + 8) = *(uint *)(pon_serdes_base + 8) & 0xffffff8f;
  *(uint *)(pon_serdes_base + 8) = *(uint *)(pon_serdes_base + 8) & 0xffff8fff;
  printk("\nset rx 3db pre and post success \n");
  return 0;
}

