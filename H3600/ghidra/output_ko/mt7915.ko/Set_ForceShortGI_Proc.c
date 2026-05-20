// module: mt7915.ko
// function: Set_ForceShortGI_Proc @ 0xdf398
// size: 156 bytes
//

undefined4 Set_ForceShortGI_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if ((iVar1 != 0) && ((iVar2 = os_str_tol(param_2,0,10), iVar2 == 0 || (iVar2 == 1)))) {
    *(char *)(param_1 + 0x28e7f3) = (char)iVar2;
    SetCommonHtVht(param_1,iVar1);
    if (DebugLevel < 3) {
      return 1;
    }
    printk("Set_ForceShortGI_Proc::(ForceShortGI=%d)\n",(char)param_1[0x28e7f3]);
    return 1;
  }
  return 0;
}

