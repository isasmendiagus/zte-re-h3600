// module: mt7915.ko
// function: MtfAsicSetTxStream @ 0x195e6c
// size: 108 bytes
//

undefined4 MtfAsicSetTxStream(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  uint local_14;
  
  uVar1 = 0x820f4000;
  if (param_3 != 0) {
    uVar1 = 0x820f4008;
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar1,&local_14);
  local_14 = local_14 & 0xfffcffff | (param_2 - 1U & 3) << 0x10;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar1);
  return 1;
}

