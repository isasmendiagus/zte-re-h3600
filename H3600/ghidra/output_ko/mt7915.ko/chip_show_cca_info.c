// module: mt7915.ko
// function: chip_show_cca_info @ 0x189e60
// size: 416 bytes
//

undefined4 chip_show_cca_info(int param_1)

{
  int iVar1;
  uint local_14;
  
  iVar1 = *(int *)(param_1 + 0x4328);
  mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f52e4,&local_14);
  local_14 = local_14 | 0x80000000;
  mac_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f52e4);
  mac_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f082c,0xf);
  mac_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f0014,0x1f);
  mac_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f0018,0x6060606);
  mac_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f004c,0x1c1c1d1d);
  mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f0024,&local_14);
  if ((0 < DebugLevel) && (printk("CCA for BAND0 info:\n"), 0 < DebugLevel)) {
    printk("-- CCA Prim: %d, SE20: %d, SEC40: %d\n",(local_14 << 0x11) >> 0x1f,
           (local_14 << 0x19) >> 0x1f,(local_14 << 0x1a) >> 0x1f);
  }
  mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f52e4,&local_14);
  local_14 = local_14 & 0x7fffffff;
  mac_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f52e4);
  mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f0024,&local_14);
  if ((0 < DebugLevel) && (printk("CCA for BAND1 info:\n"), 0 < DebugLevel)) {
    printk("-- CCA Prim: %d, SE20: %d, SEC40: %d\n",(local_14 << 0x11) >> 0x1f,
           (local_14 << 0x19) >> 0x1f,(local_14 << 0x1a) >> 0x1f);
  }
  return 0;
}

