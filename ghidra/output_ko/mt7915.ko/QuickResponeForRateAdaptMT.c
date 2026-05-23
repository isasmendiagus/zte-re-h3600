// module: mt7915.ko
// function: QuickResponeForRateAdaptMT @ 0x1d9e1c
// size: 204 bytes
//

void QuickResponeForRateAdaptMT(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 local_42;
  undefined1 uStack_41;
  undefined1 auStack_40 [40];
  
  param_2 = param_2 * 0x14c0;
  local_42 = 0;
  if (*(char *)(param_1 + param_2 + 0xa3134) == '\0') {
    return;
  }
  iVar3 = param_1 + param_2 + 0xa1d20;
  iVar2 = param_1 + param_2 + 0xa30e0;
  os_zero_mem(auStack_40,0x28);
  raWrapperEntrySet(param_1,iVar3,iVar2);
  raWrapperConfigSet(param_1,*(undefined4 *)(param_1 + param_2 + 0xa1d28),auStack_40);
  iVar1 = param_1 + param_2 + 0xa3000;
  raSelectTxRateTable(iVar2,auStack_40,iVar1 + 0x124,iVar1 + 0x13c,&local_42,&uStack_41);
  raWrapperEntryRestore(param_1,iVar3,iVar2);
  return;
}

