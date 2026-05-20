// module: mt7915.ko
// function: ORIBATimerTimeout @ 0xa2614
// size: 212 bytes
//

void ORIBATimerTimeout(int param_1)

{
  ushort uVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) {
    return;
  }
  if ((*(int *)(param_1 + 0xa77bb4) == 1) &&
     ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)) {
    return;
  }
  iVar4 = (uint)*(ushort *)(param_1 + 0x285920) << 3;
  if (*(ushort *)(param_1 + 0x285920) != 0) {
    iVar5 = 1;
    piVar3 = (int *)(param_1 + 0x1b214);
    do {
      iVar4 = iVar4 + -1;
      iVar5 = iVar5 + 1;
      if ((*piVar3 == 3) &&
         (uVar1 = *(ushort *)(piVar3 + -3), uVar2 = HcGetMaxStaNum(param_1), uVar2 <= uVar1)) {
        printk(&_LC22,0x61b);
        dump_stack();
      }
      piVar3 = piVar3 + 0x12;
    } while (iVar5 < 0x480 && 0 < iVar4);
    return;
  }
  return;
}

