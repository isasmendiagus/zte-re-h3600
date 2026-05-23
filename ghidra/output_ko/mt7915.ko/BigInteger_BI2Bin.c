// module: mt7915.ko
// function: BigInteger_BI2Bin @ 0x1fb3c4
// size: 168 bytes
//

void BigInteger_BI2Bin(int param_1,int param_2,uint *param_3)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  
  if (param_1 == 0) {
    printk("BigInteger_BI2Bin: pBI is NUll\n");
    *param_3 = 0;
    return;
  }
  if (*(int *)(param_1 + 0xc) == 0) {
    *param_3 = 0;
    return;
  }
  BigInteger_ClearHighBits();
  uVar7 = *(uint *)(param_1 + 0x18);
  puVar1 = (undefined1 *)(param_2 + -1);
  uVar6 = 0;
  iVar2 = *(int *)(param_1 + 0xc);
  uVar3 = uVar7 & 3;
  iVar4 = *(int *)(param_1 + 0x14) + -1;
  if (uVar3 == 0) {
    uVar3 = 4;
  }
  uVar5 = *(uint *)(iVar2 + iVar4 * 4);
  while( true ) {
    uVar3 = uVar3 - 1;
    bVar8 = uVar7 <= uVar6;
    uVar6 = uVar6 + 1;
    if (bVar8) break;
    puVar1 = puVar1 + 1;
    *puVar1 = (char)(uVar5 >> (uVar3 * 8 & 0xff));
    if (uVar3 == 0) {
      iVar4 = iVar4 + -1;
      if (-1 < iVar4) {
        iVar2 = *(int *)(param_1 + 0xc);
      }
      uVar3 = 4;
      if (-1 < iVar4) {
        uVar5 = *(uint *)(iVar2 + iVar4 * 4);
      }
    }
    uVar7 = *(uint *)(param_1 + 0x18);
  }
  *param_3 = uVar7;
  return;
}

