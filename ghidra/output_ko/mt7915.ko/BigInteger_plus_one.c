// module: mt7915.ko
// function: BigInteger_plus_one @ 0x1fee38
// size: 120 bytes
//

void BigInteger_plus_one(int param_1)

{
  int iVar1;
  uint uVar2;
  short sVar3;
  int *piVar4;
  
  if (param_1 == 0) {
    return;
  }
  if (*(int *)(param_1 + 0x14) == 0) {
LAB_001feea4:
                    /* WARNING: Subroutine does not return */
    panic("BigInteger_plus_one: todo: length update");
  }
  piVar4 = *(int **)(param_1 + 0xc);
  iVar1 = *piVar4;
  if (iVar1 == -1) {
    sVar3 = 0;
    do {
      sVar3 = sVar3 + 1;
      *piVar4 = 0;
      uVar2 = (uint)sVar3;
      if (*(uint *)(param_1 + 0x14) <= uVar2) goto LAB_001feea4;
      piVar4 = (int *)(*(int *)(param_1 + 0xc) + uVar2 * 4);
      iVar1 = *(int *)(*(int *)(param_1 + 0xc) + uVar2 * 4);
    } while (iVar1 == -1);
  }
  *piVar4 = iVar1 + 1;
  return;
}

