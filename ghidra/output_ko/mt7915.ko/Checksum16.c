// module: mt7915.ko
// function: Checksum16 @ 0x1d4bb0
// size: 152 bytes
//

uint Checksum16(ushort *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  ushort *puVar4;
  
  if (param_2 < 2) {
    if (param_2 == 0) {
      return 0xffff;
    }
    uVar3 = 0;
  }
  else {
    uVar3 = 0;
    iVar2 = param_2;
    puVar4 = param_1;
    do {
      iVar2 = iVar2 + -2;
      uVar3 = uVar3 + *puVar4;
      if ((int)uVar3 < 0) {
        uVar3 = ((int)uVar3 >> 0x10) + (uVar3 & 0xffff);
      }
      puVar4 = puVar4 + 1;
    } while (1 < iVar2);
    uVar1 = param_2 - 2U >> 1;
    param_1 = param_1 + uVar1 + 1;
    if (param_2 - 2U == uVar1 * 2) goto LAB_001d4bfc;
  }
  uVar3 = uVar3 + (byte)*param_1;
LAB_001d4bfc:
  iVar2 = (int)uVar3 >> 0x10;
  if (iVar2 == 0) {
    return ~uVar3 & 0xffff;
  }
  do {
    uVar3 = iVar2 + (uVar3 & 0xffff);
    iVar2 = (int)uVar3 >> 0x10;
  } while (iVar2 != 0);
  return ~uVar3 & 0xffff;
}

