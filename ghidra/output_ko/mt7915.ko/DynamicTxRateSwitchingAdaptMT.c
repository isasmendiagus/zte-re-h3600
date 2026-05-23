// module: mt7915.ko
// function: DynamicTxRateSwitchingAdaptMT @ 0x1d9ee8
// size: 180 bytes
//

void DynamicTxRateSwitchingAdaptMT(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined1 local_4a;
  undefined1 uStack_49;
  undefined1 auStack_48 [44];
  
  param_2 = param_2 * 0x14c0;
  iVar2 = param_1 + param_2 + 0xa30e0;
  iVar1 = param_1 + param_2 + 0xa1d20;
  local_4a = 0;
  os_zero_mem(auStack_48,0x28);
  raWrapperEntrySet(param_1,iVar1,iVar2);
  raWrapperConfigSet(param_1,*(undefined4 *)(param_1 + param_2 + 0xa1d28),auStack_48);
  raSelectTxRateTable(iVar2,auStack_48,param_1 + param_2 + 0xa3000 + 0x124,
                      param_1 + param_2 + 0xa3000 + 0x13c,&local_4a,&uStack_49);
  raWrapperEntryRestore(param_1,iVar1,iVar2);
  return;
}

