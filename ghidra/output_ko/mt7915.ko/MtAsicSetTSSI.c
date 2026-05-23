// module: mt7915.ko
// function: MtAsicSetTSSI @ 0x1964e4
// size: 280 bytes
//

undefined4 MtAsicSetTSSI(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  
  uVar1 = 0xe3f3f800;
  if (param_2 != 0) {
    uVar1 = 0xe1010800;
  }
  if ((param_3 & 0xfd) == 0) {
    if (2 < DebugLevel) {
      printk("%s, Set WF#%d TSSI off\n","MtAsicSetTSSI");
    }
    phy_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x10d04,uVar1);
    if (param_2 == 0) {
      phy_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x10d18,0);
    }
  }
  if (param_3 - 1 < 2) {
    if (2 < DebugLevel) {
      printk("%s, Set WF#%d TSSI on\n","MtAsicSetTSSI",param_3);
    }
    phy_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x11d04,uVar1);
    if (param_2 == 0) {
      phy_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x11d18,0);
      return 1;
    }
  }
  return 1;
}

