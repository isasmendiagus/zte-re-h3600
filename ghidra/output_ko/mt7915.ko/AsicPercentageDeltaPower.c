// module: mt7915.ko
// function: AsicPercentageDeltaPower @ 0x144e00
// size: 200 bytes
//

void AsicPercentageDeltaPower(int param_1,int param_2,char *param_3,char *param_4)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_1 + 0x794cd8);
  if (bVar1 < 100) {
    if (0x5a < bVar1) {
      return;
    }
    if (0x3c < bVar1) {
      *param_3 = *param_3 + -1;
      return;
    }
    if (bVar1 < 0x1f) {
      if (0xf < bVar1) {
        *param_4 = *param_4 + -6;
        return;
      }
      if (bVar1 < 10) {
        *param_4 = *param_4 + -0xc;
        return;
      }
      *param_4 = *param_4 + -6;
    }
    *param_3 = *param_3 + -3;
    return;
  }
  if (*(char *)(param_1 + 0x286285) != '\0') {
    return;
  }
  if (-0x23 < param_2) {
    *param_3 = *param_3 + -0xc;
    return;
  }
  if (-0x28 < param_2) {
    *param_3 = *param_3 + -6;
  }
  return;
}

