// module: plat-zxylzb_9128S.ko
// function: serdes_set_rx_prbs_mode @ 0x1b9fc
// size: 196 bytes
//

undefined4 serdes_set_rx_prbs_mode(int param_1)

{
  *(uint *)(pon_serdes_base + 0x14) = *(uint *)(pon_serdes_base + 0x14) & 0xffff8fff;
  *(uint *)(pon_serdes_base + 0x14) = *(uint *)(pon_serdes_base + 0x14) | 0x10000000;
  if (param_1 == 1) {
    *(uint *)(pon_serdes_base + 0x44) = *(uint *)(pon_serdes_base + 0x44) & 0xfffff3ff | 0x800;
    printk("\nserdes_set_tx_prbs_prbs_mode to 23\n");
    return 0;
  }
  if (param_1 != 0) {
    if (param_1 == 2) {
      *(uint *)(pon_serdes_base + 0x44) = *(uint *)(pon_serdes_base + 0x44) | 0xc00;
      printk("\nserdes_set_tx_prbs_prbs_mode to 31\n");
    }
    return 0;
  }
  *(uint *)(pon_serdes_base + 0x44) = *(uint *)(pon_serdes_base + 0x44) & 0xfffff3ff;
  printk("\nserdes_set_tx_prbs_prbs_mode to 7\n");
  return 0;
}

