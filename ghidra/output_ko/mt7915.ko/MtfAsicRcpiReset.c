// module: mt7915.ko
// function: MtfAsicRcpiReset @ 0x1951fc
// size: 56 bytes
//

void MtfAsicRcpiReset(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = FUN_00195078();
  if (iVar1 != 1) {
    return;
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f9830,param_2 | 0x8000,param_4);
  return;
}

