// module: mt7915.ko
// function: RTMPMinRssi @ 0x13061c
// size: 152 bytes
//

int RTMPMinRssi(int param_1,int param_2,int param_3,int param_4,char param_5)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  
  iVar2 = (int)param_5;
  bVar3 = "SetPartProfileParameters"[param_1 + 0x18] & 0xf;
  if (("SetPartProfileParameters"[param_1 + 0x18] & 0xfU) == 0) {
    iVar1 = -0x7f;
  }
  else {
    iVar1 = param_2;
    if (param_2 == 0) {
      iVar1 = -0x7f;
    }
    if (bVar3 != 1) {
      if ((param_3 != 0 && param_3 != -0x7f) && (iVar1 = param_2, param_3 <= param_2)) {
        iVar1 = param_3;
      }
      if (((bVar3 != 2) && (param_4 != 0 && param_4 != -0x7f)) && (param_4 <= iVar1)) {
        iVar1 = param_4;
      }
    }
  }
  if (("SetPartProfileParameters"[param_1 + 0x18] & 0xfU) == 4) {
    if (iVar2 != 0 && iVar2 != -0x7f) {
      if (iVar2 <= iVar1) {
        iVar1 = iVar2;
      }
      return iVar1;
    }
    return iVar1;
  }
  return iVar1;
}

