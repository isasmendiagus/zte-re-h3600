// module: mt7915.ko
// function: RTMPMinSnr @ 0x1306b4
// size: 44 bytes
//

int RTMPMinSnr(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  
  uVar2 = (byte)"SetPartProfileParameters"[param_1 + 0x18] & 0xf;
  bVar3 = param_3 != 0;
  iVar1 = 0;
  if (bVar3) {
    iVar1 = uVar2 - 1;
  }
  if (((bVar3 && uVar2 != 1) && iVar1 < 0 == (bVar3 && SBORROW4(uVar2,1))) && (param_3 <= param_2))
  {
    param_2 = param_3;
  }
  return param_2;
}

