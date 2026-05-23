// module: mt7915.ko
// function: DfsCacRestrictBand @ 0x231f3c
// size: 228 bytes
//

bool DfsCacRestrictBand(int param_1,uint param_2,int param_3,int param_4)

{
  int iVar1;
  
  if (param_2 == 6) {
    if (param_3 - 0x74U < 0xd) {
      return true;
    }
    return param_4 - 0x74U < 0xd;
  }
  if (param_2 == 3) {
    if (param_3 - 100U < 0x1d) {
      return true;
    }
  }
  else {
    iVar1 = strncmp((char *)(param_1 + 0x794c31),"KR",2);
    if (iVar1 == 0) {
      if (param_2 < 2) {
        if (param_2 == 0) {
          return param_3 == 0x80;
        }
        return param_3 - 0x7cU < 5;
      }
    }
    else if (param_2 == 0) {
      return param_3 - 0x78U < 9;
    }
  }
  return param_3 - 0x74U < 0xd;
}

