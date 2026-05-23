// module: mt7915.ko
// function: RcGetBandIdxByBf @ 0xac88c
// size: 92 bytes
//

int RcGetBandIdxByBf(int param_1)

{
  int iVar1;
  
  if (*(byte *)(param_1 + 0x32d8) == 0) {
    return 0;
  }
  if (*(char *)(param_1 + 0x16a6) == '\0') {
    if (*(byte *)(param_1 + 0x32d8) < 2) {
      return 0;
    }
    if (*(char *)(param_1 + 0x19fa) == '\0') {
      return 0;
    }
    iVar1 = 1;
  }
  else {
    iVar1 = 0;
  }
  return param_1 + iVar1 * 0x1c;
}

