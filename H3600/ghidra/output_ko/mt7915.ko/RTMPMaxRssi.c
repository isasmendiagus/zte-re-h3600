// module: mt7915.ko
// function: RTMPMaxRssi @ 0x12fa18
// size: 120 bytes
//

int RTMPMaxRssi(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  
  uVar3 = (byte)"SetPartProfileParameters"[param_1 + 0x18] & 0xf;
  iVar2 = param_2;
  if (uVar3 != 1 || param_2 == 0) {
    iVar2 = -0x7f;
  }
  bVar4 = param_3 != 0;
  iVar1 = 0;
  if (bVar4) {
    iVar1 = uVar3 - 1;
  }
  if (((bVar4 && uVar3 != 1) && iVar1 < 0 == (bVar4 && SBORROW4(uVar3,1))) &&
     (iVar2 = param_2, param_2 < param_3)) {
    iVar2 = param_3;
  }
  if (uVar3 == 3 && param_4 != 0) {
    if (iVar2 < param_4) {
      iVar2 = param_4;
    }
    iVar2 = (int)(char)iVar2;
  }
  if (iVar2 == -0x7f) {
    iVar2 = 0;
  }
  return iVar2;
}

