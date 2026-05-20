// module: mt7915.ko
// function: rx_isr_th_enhance @ 0x15dd4c
// size: 240 bytes
//

void rx_isr_th_enhance(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (*(char *)(param_1 + 0xa7c544) == '\x01') {
    return;
  }
  if (2 < DebugLevel) {
    printk("%s:: ---Enter---\n","rx_isr_th_enhance",param_3,DebugLevel,param_4);
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x8309605c,0x44400000);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x830960a8,0xa0d);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x830a740c,0x22222220);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x830a744c,0x201000d);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x83020280,7);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x83030280,7);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x8309f05c,0xf121d3);
  *(undefined1 *)(param_1 + 0xa7c544) = 1;
  return;
}

