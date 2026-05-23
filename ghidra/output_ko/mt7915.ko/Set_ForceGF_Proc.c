// module: mt7915.ko
// function: Set_ForceGF_Proc @ 0xdf434
// size: 156 bytes
//

undefined4 Set_ForceGF_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if ((iVar1 != 0) && ((iVar2 = os_str_tol(param_2,0,10), iVar2 == 0 || (iVar2 == 1)))) {
    *(char *)((int)param_1 + 0xa39fcd) = (char)iVar2;
    SetCommonHtVht(param_1,iVar1);
    if (DebugLevel < 3) {
      return 1;
    }
    printk("Set_ForceGF_Proc::(ForceGF=%d)\n",*(undefined1 *)((int)param_1 + 0xa39fcd));
    return 1;
  }
  return 0;
}

