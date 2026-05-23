// module: mt7915.ko
// function: pci_io_remap_write32 @ 0x17a784
// size: 272 bytes
//

void pci_io_remap_write32(undefined4 param_1,uint param_2,undefined4 param_3)

{
  undefined4 local_14;
  
  if ((0xbfffff < param_2 + 0xe8000000) &&
     ((0x7fffffe < param_2 + 0x90000000 && param_2 != 0x77ffffff) && param_2 < 0xf0000000)) {
    if (0x3fffff < param_2 + 0x84000000) {
      hif_io_read32(param_1,0xf11b0,&local_14);
      hif_io_write32(param_1,0xf11b0,local_14 & 0xfff00000 | param_2 >> 0xc);
      hif_io_read32(param_1,0xf11b0,&local_14);
      hif_io_write32(param_1,param_2 & 0xfff,param_3);
      return;
    }
    param_2 = param_2 + 0x9c000000;
  }
  hif_io_read32(param_1,0xf11ac,&local_14);
  hif_io_write32(param_1,0xf11ac,param_2 >> 0x10 | (uint)local_14._2_2_ << 0x10);
  hif_io_read32(param_1,0xf11ac,&local_14);
  hif_io_write32(param_1,(param_2 & 0xffff) + 0xe0000,param_3);
  return;
}

