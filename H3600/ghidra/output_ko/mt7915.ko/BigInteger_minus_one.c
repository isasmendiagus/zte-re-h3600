// module: mt7915.ko
// function: BigInteger_minus_one @ 0x1fedb8
// size: 128 bytes
//

void BigInteger_minus_one(int param_1)

{
  int iVar1;
  uint uVar2;
  short sVar3;
  int *piVar4;
  
  if (param_1 == 0) {
    return;
  }
  if (*(int *)(param_1 + 0x14) != 0) {
    piVar4 = *(int **)(param_1 + 0xc);
    if (*piVar4 != 0) {
      *piVar4 = *piVar4 + -1;
      return;
    }
    sVar3 = 0;
    do {
      sVar3 = sVar3 + 1;
      *piVar4 = -1;
      uVar2 = (uint)sVar3;
      if (*(uint *)(param_1 + 0x14) <= uVar2) {
        return;
      }
      piVar4 = (int *)(*(int *)(param_1 + 0xc) + uVar2 * 4);
      iVar1 = *(int *)(*(int *)(param_1 + 0xc) + uVar2 * 4);
    } while (iVar1 == 0);
    *piVar4 = iVar1 + -1;
    return;
  }
  return;
}

