// module: mt7915.ko
// function: Set_WscSetupLockTime_Proc @ 0x2ae94
// size: 104 bytes
//

undefined4 Set_WscSetupLockTime_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *param_1;
  iVar1 = os_str_tol(param_2,0,10);
  if (2 < DebugLevel) {
    printk("Set_WscSetupLockTime_Proc::(SetupLockTime=%d)\n",iVar1);
  }
  param_1[*(int *)(iVar2 + 0x3c) * 0x160d + 0xaec42] = iVar1;
  return 1;
}

