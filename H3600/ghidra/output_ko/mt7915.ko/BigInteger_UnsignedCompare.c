// module: mt7915.ko
// function: BigInteger_UnsignedCompare @ 0x1fbab0
// size: 180 bytes
//

undefined4 BigInteger_UnsignedCompare(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint *puVar4;
  uint *puVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  bool bVar9;
  
  BigInteger_ClearHighBits();
  BigInteger_ClearHighBits(param_2);
  if (param_2 == 0 || param_1 == 0) {
    return 0;
  }
  uVar8 = *(uint *)(param_1 + 0x18);
  uVar1 = *(uint *)(param_2 + 0x18);
  if (uVar8 == uVar1) {
    iVar6 = *(int *)(param_1 + 0x14) + -1;
    if (-1 < iVar6) {
      uVar3 = *(uint *)(*(int *)(param_1 + 0xc) + iVar6 * 4);
      uVar7 = *(uint *)(*(int *)(param_2 + 0xc) + iVar6 * 4);
      if (uVar7 < uVar3) {
        return 1;
      }
      if (uVar7 <= uVar3) {
        puVar4 = (uint *)(*(int *)(param_1 + 0xc) + iVar6 * 4);
        puVar5 = (uint *)(*(int *)(param_2 + 0xc) + iVar6 * 4);
        do {
          bVar9 = iVar6 == 0;
          iVar6 = iVar6 + -1;
          if (bVar9) goto LAB_001fbae8;
          puVar4 = puVar4 + -1;
          puVar5 = puVar5 + -1;
          if (*puVar5 < *puVar4) {
            return 1;
          }
        } while (*puVar5 <= *puVar4);
      }
      return 0xffffffff;
    }
  }
  else if (uVar1 <= uVar8) {
    return 1;
  }
LAB_001fbae8:
  if (uVar8 < uVar1) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

