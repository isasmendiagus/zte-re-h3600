// module: mt7915.ko
// function: Set_BGProtection_Proc @ 0xd9b94
// size: 208 bytes
//

undefined4 Set_BGProtection_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *param_1;
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar2 + 0x3c),*(undefined4 *)(iVar2 + 0x38));
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = os_str_tol(param_2,0,10);
  if (((iVar1 != 1) && (iVar1 != 2)) && (iVar1 != 0)) {
    return 0;
  }
  param_1[0x1e541b] = iVar1;
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    ApUpdateCapabilityAndErpIe(param_1,param_1 + *(int *)(iVar2 + 0x3c) * 0x160d + 0xadc92);
  }
  if (DebugLevel < 3) {
    return 1;
  }
  printk("Set_BGProtection_Proc::(BGProtection=%ld)\n",param_1[0x1e541b]);
  return 1;
}

