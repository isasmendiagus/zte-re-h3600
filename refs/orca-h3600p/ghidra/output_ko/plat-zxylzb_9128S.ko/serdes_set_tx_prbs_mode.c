// module: plat-zxylzb_9128S.ko
// function: serdes_set_tx_prbs_mode @ 0x1bf7c
// size: 208 bytes
//

undefined4 serdes_set_tx_prbs_mode(int param_1)

{
  serdes_set_gen_en_open();
  *pon_serdes_base = *pon_serdes_base & 0xfffffff8;
  pon_serdes_base[0x11] = pon_serdes_base[0x11] & 0xfe3fffff | 0x1000000;
  if (param_1 == 1) {
    pon_serdes_base[0x11] = pon_serdes_base[0x11] & 0xfffffcff | 0x200;
    printk("\nserdes_set_tx_prbs_prbs_mode to 23\n");
    return 0;
  }
  if (param_1 != 0) {
    if (param_1 == 2) {
      pon_serdes_base[0x11] = pon_serdes_base[0x11] | 0x300;
      printk("\nserdes_set_tx_prbs_prbs_mode to 31\n");
    }
    return 0;
  }
  pon_serdes_base[0x11] = pon_serdes_base[0x11] & 0xfffffcff;
  printk("\nserdes_set_tx_prbs_prbs_mode to 7\n");
  return 0;
}

