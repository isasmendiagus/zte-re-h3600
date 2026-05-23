// module: mt7915.ko
// function: Set_WscAutoTriggerDisable_Proc @ 0x2aefc
// size: 136 bytes
//

undefined4
Set_WscAutoTriggerDisable_Proc
          (int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  
  iVar2 = *param_1;
  cVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  iVar2 = *(int *)(iVar2 + 0x3c);
  *(bool *)(param_1 + iVar2 * 0x160d + 0xaec5e) = cVar1 != '\0';
  if (2 < DebugLevel) {
    printk("Set_WscAutoTriggerDisable_Proc::(bWscAutoTriggerDisable=%d)\n",
           (char)param_1[iVar2 * 0x160d + 0xaec5e]);
  }
  return 1;
}

