// module: mt7915.ko
// function: BigInteger_ClearHighBits @ 0x1fb30c
// size: 172 bytes
//

void BigInteger_ClearHighBits(int param_1)

{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  
  if (param_1 == 0) {
    return;
  }
  iVar2 = *(int *)(param_1 + 0xc);
  if (iVar2 == 0) {
    return;
  }
  iVar4 = *(int *)(param_1 + 0x14) + -1;
  if (iVar4 < 0) {
    *(undefined4 *)(param_1 + 0x18) = 1;
    *(undefined4 *)(param_1 + 0x14) = 1;
    *(undefined4 *)(param_1 + 0x1c) = 1;
    return;
  }
  iVar5 = iVar4 * 4;
  uVar1 = *(uint *)(iVar2 + iVar4 * 4);
  if (uVar1 == 0) {
    puVar3 = (uint *)(iVar2 + iVar5);
    do {
      bVar6 = iVar4 == 0;
      iVar4 = iVar4 + -1;
      if (bVar6) {
        *(undefined4 *)(param_1 + 0x18) = 1;
        *(undefined4 *)(param_1 + 0x14) = 1;
        *(undefined4 *)(param_1 + 0x1c) = 1;
        return;
      }
      puVar3 = puVar3 + -1;
      uVar1 = *puVar3;
    } while (uVar1 == 0);
    iVar5 = iVar4 * 4;
  }
  iVar2 = 4;
  do {
    iVar2 = iVar2 + -1;
  } while ((uVar1 >> (iVar2 * 8 & 0xffU) & 0xff) == 0);
  *(int *)(param_1 + 0x14) = iVar4 + 1;
  *(int *)(param_1 + 0x18) = iVar5 + iVar2 + 1;
  return;
}

