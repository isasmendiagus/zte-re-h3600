// module: mt7915.ko
// function: chip_show_asic_rx_stat @ 0x189640
// size: 240 bytes
//

undefined4 chip_show_asic_rx_stat(int param_1,int param_2)

{
  undefined4 local_14;
  
  local_14 = 0;
  if (DebugLevel < 3) {
    if (param_2 != 10) {
      return 0;
    }
  }
  else {
    printk("mt7915: %s, Type(%d)\n","chip_show_asic_rx_stat",param_2);
    if (param_2 != 10) goto LAB_001896f8;
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820ed014,&local_14);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820ed030,&local_14);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fd014,&local_14);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fd030,&local_14);
LAB_001896f8:
  if (2 < DebugLevel) {
    printk("%s, Type(%d):%x\n","chip_show_asic_rx_stat",param_2,local_14);
  }
  return local_14;
}

