// module: mt7915.ko
// function: HcIsRfSupport @ 0xa9998
// size: 84 bytes
//

bool HcIsRfSupport(int param_1,byte param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xa797a0);
  if (*(byte *)(iVar1 + 0x32d8) == 0) {
    return false;
  }
  if ((param_2 & *(byte *)(iVar1 + 0x1360)) == 0) {
    if (1 < *(byte *)(iVar1 + 0x32d8)) {
      return (param_2 & *(byte *)(iVar1 + 0x16b4)) != 0;
    }
    return false;
  }
  return true;
}

