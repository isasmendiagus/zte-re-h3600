// module: mt7915.ko
// function: MtAsicSetDPD @ 0x196600
// size: 432 bytes
//

undefined4 MtAsicSetDPD(int param_1,int param_2,uint param_3)

{
  uint local_14;
  
  local_14 = 0;
  if (param_2 == 0) {
    if ((param_3 & 0xfd) == 0) {
      phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x10a08,&local_14);
      local_14 = local_14 | 0xf0000000;
      phy_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x10a08);
    }
    if (param_3 - 1 < 2) {
      phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x11a08,&local_14);
      local_14 = local_14 | 0xf0000000;
      phy_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x11a08);
    }
    if (2 < DebugLevel) {
      printk("%s, Set WFSelect: %d DPD off\n","MtAsicSetDPD",param_3);
    }
  }
  else {
    if ((param_3 & 0xfd) == 0) {
      phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x10a08,&local_14);
      local_14 = local_14 & 0xfffffff;
      phy_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x10a08);
    }
    if (param_3 - 1 < 2) {
      phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x11a08,&local_14);
      local_14 = local_14 & 0xfffffff;
      phy_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x11a08);
    }
    if (2 < DebugLevel) {
      printk("%s, Set WFSelect: %d DPD on\n","MtAsicSetDPD",param_3);
    }
  }
  return 1;
}

