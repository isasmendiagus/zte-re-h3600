// module: mt7915.ko
// function: BN_security_bits @ 0x20df68
// size: 132 bytes
//

int BN_security_bits(int param_1,int param_2)

{
  int iVar1;
  
  if (param_1 < 0x3c00) {
    if (0x1dff < param_1) {
      iVar1 = 0xc0;
      if (param_2 == -1) {
        return 0xc0;
      }
      goto LAB_0020df94;
    }
    if (0xbff < param_1) {
      iVar1 = 0x80;
      if (param_2 == -1) {
        return 0x80;
      }
      goto LAB_0020df94;
    }
    if (param_1 < 0x800) {
      if (param_1 < 0x400) {
        return 0;
      }
      iVar1 = 0x50;
    }
    else {
      iVar1 = 0x70;
    }
  }
  else {
    iVar1 = 0x100;
  }
  if (param_2 == -1) {
    return iVar1;
  }
LAB_0020df94:
  param_2 = param_2 / 2;
  if (param_2 < 0x50) {
    return 0;
  }
  if (param_2 <= iVar1) {
    iVar1 = param_2;
  }
  return iVar1;
}

