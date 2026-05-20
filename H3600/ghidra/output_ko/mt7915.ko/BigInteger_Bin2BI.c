// module: mt7915.ko
// function: BigInteger_Bin2BI @ 0x1fb4c8
// size: 140 bytes
//

void BigInteger_Bin2BI(byte *param_1,uint param_2,int *param_3)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  byte *pbVar5;
  uint uVar6;
  
  BigInteger_AllocSize(param_3);
  iVar1 = *param_3;
  if (iVar1 == 0) {
    return;
  }
  if (*(int *)(iVar1 + 0xc) != 0) {
    uVar3 = param_2 & 3;
    pbVar2 = param_1 + param_2;
    iVar4 = *(int *)(iVar1 + 0x14) + -1;
    uVar6 = 0;
    if (uVar3 == 0) {
      uVar3 = 4;
    }
    while (pbVar5 = param_1, param_1 != pbVar2) {
      while( true ) {
        param_1 = pbVar5 + 1;
        uVar3 = uVar3 - 1;
        uVar6 = (uint)*pbVar5 | uVar6 << 8;
        if (uVar3 != 0) break;
        *(uint *)(*(int *)(iVar1 + 0xc) + iVar4 * 4) = uVar6;
        iVar4 = iVar4 + -1;
        iVar1 = *param_3;
        uVar3 = 4;
        uVar6 = 0;
        pbVar5 = param_1;
        if (param_1 == pbVar2) goto LAB_001fb54c;
      }
    }
  }
LAB_001fb54c:
  BigInteger_ClearHighBits();
  return;
}

