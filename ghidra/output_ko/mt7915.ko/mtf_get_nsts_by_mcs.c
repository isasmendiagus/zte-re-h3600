// module: mt7915.ko
// function: mtf_get_nsts_by_mcs @ 0x19d8d0
// size: 112 bytes
//

int mtf_get_nsts_by_mcs(undefined4 param_1,uint param_2,int param_3,int param_4)

{
  int iVar1;
  
  switch(param_1) {
  case 2:
  case 3:
    if (param_2 != 0x20) {
      iVar1 = (param_2 >> 3) + 1;
      if (param_3 != 0 && iVar1 == 1) {
        iVar1 = (param_2 >> 3) + 2;
      }
      return iVar1;
    }
    break;
  case 4:
  case 8:
  case 9:
  case 10:
  case 0xb:
    if (param_4 == 1 && param_3 != 0) {
      param_4 = 2;
    }
    return param_4;
  }
  return 1;
}

