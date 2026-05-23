// module: mt7915.ko
// function: PMF_RobustFrameClassify @ 0x21a64c
// size: 276 bytes
//

undefined4 PMF_RobustFrameClassify(byte *param_1,int param_2,uint param_3,int param_4,char param_5)

{
  byte bVar1;
  undefined4 uVar2;
  uint uVar3;
  
  if (param_3 == 0 || (*param_1 & 0xc) != 0) {
switchD_0021a6fc_caseD_4:
    return 0;
  }
  bVar1 = *param_1 >> 4;
  if (bVar1 != 0xc) {
    if (bVar1 == 0xd) {
      if ((param_5 == '\0') || ((param_1[1] & 0x40) == 0)) {
        switch(param_1[0x18]) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
        case 8:
        case 9:
        case 10:
        case 0xd:
        case 0xe:
        case 0x10:
        case 0x12:
        case 0x13:
        case 0x1f:
        case 0x7e:
          break;
        default:
          goto switchD_0021a6fc_caseD_4;
        }
      }
    }
    else if (bVar1 != 10) {
      return 0;
    }
  }
  if ((param_1[4] & 1) != 0) {
    if ((0x12 < param_3) && (uVar3 = param_3 - 0x12 & 0xff, *(char *)(param_2 + uVar3) == 'L')) {
      if (*(char *)(param_2 + uVar3 + 1) == '\x10') {
        uVar2 = 5;
      }
      else {
        uVar2 = 2;
      }
      return uVar2;
    }
    return 2;
  }
  if (param_4 == 0) {
    return 0;
  }
  if (*(char *)(param_4 + 0x562) == '\0') {
    return 0;
  }
  if (*(char *)(param_4 + 0x562) != '\x01') {
    return 4;
  }
  uVar3 = ((param_1[1] ^ 0x40) << 0x19) >> 0x1f;
  if (param_5 != '\x01') {
    uVar3 = 0;
  }
  if (uVar3 == 0) {
    uVar2 = 4;
  }
  else {
    uVar2 = 3;
  }
  return uVar2;
}

