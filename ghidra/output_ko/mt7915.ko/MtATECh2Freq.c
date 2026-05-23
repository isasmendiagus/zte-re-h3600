// module: mt7915.ko
// function: MtATECh2Freq @ 0x28b010
// size: 168 bytes
//

int MtATECh2Freq(int param_1,int param_2)

{
  int iVar1;
  
  if (param_2 == 0) {
    if (0xc < param_1 - 1U) {
      iVar1 = 0x9b4;
      if (param_1 != 0xe) {
        iVar1 = 0;
      }
      return iVar1;
    }
    return param_1 * 5 + 0x967;
  }
  if (param_2 != 1) {
    return 0;
  }
  if (param_1 - 7U < 0xaf) {
    return param_1 * 5 + 5000;
  }
  if (0xc < param_1 - 0xb8U) {
    if (param_1 == 6) {
      return 0x13a8;
    }
    if (param_1 != 0xb6) {
      iVar1 = 0x1335;
      if (param_1 != 0xb7) {
        iVar1 = 0;
      }
      return iVar1;
    }
    return 0x1330;
  }
  return param_1 * 5 + 4000;
}

