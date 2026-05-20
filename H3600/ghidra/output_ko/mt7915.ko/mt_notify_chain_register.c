// module: mt7915.ko
// function: mt_notify_chain_register @ 0x105ab0
// size: 120 bytes
//

undefined4 mt_notify_chain_register(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  OS_SPIN_LOCK();
  iVar3 = *(int *)(param_1 + 4);
  piVar1 = (int *)(param_1 + 4);
  if (iVar3 != 0) {
    if (param_2 == iVar3) goto LAB_00105b18;
    iVar2 = *(int *)(iVar3 + 8);
    while (*(int *)(param_2 + 8) <= iVar2) {
      piVar1 = (int *)(iVar3 + 4);
      iVar3 = *(int *)(iVar3 + 4);
      if (iVar3 == 0) break;
      if (param_2 == iVar3) goto LAB_00105b18;
      iVar2 = *(int *)(iVar3 + 8);
    }
  }
  *(int *)(param_2 + 4) = iVar3;
  *piVar1 = param_2;
LAB_00105b18:
  OS_SPIN_UNLOCK(param_1);
  return 0;
}

