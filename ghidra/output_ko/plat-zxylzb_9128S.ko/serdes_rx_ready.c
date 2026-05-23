// module: plat-zxylzb_9128S.ko
// function: serdes_rx_ready @ 0x1bac0
// size: 68 bytes
//

undefined4 serdes_rx_ready(void)

{
  if ((*(uint *)(pon_serdes_base + 0x68) & 0x10) != 0) {
    printk("serdes_rx_ready  ok  \n");
    return 1;
  }
  printk("serdes_rx_ready  failed  \n");
  return 0;
}

