// module: mt7915.ko
// function: RTMPSetVHT @ 0x201c1c
// size: 68 bytes
//

void RTMPSetVHT(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(char *)(iVar1 + 0x96) == '\0') {
    return;
  }
  mt_WrapSetVHTETxBFCap(param_1,param_2,param_1 + 0x795960,param_4);
  return;
}

