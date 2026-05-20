// module: mt7915.ko
// function: Set_HtRdg_Proc @ 0xde2a4
// size: 192 bytes
//

undefined4 Set_HtRdg_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 == 0) {
    return 0;
  }
  iVar2 = os_str_tol(param_2,0,10);
  if ((iVar2 == 0) || (uVar3 = hc_get_asic_cap(param_1[0x29e5e8]), (uVar3 & 0x4000) == 0)) {
    *(undefined1 *)((int)param_1 + 0x79507d) = 0;
  }
  else {
    *(undefined1 *)((int)param_1 + 0x79507d) = 1;
  }
  SetCommonHtVht(param_1,iVar1);
  if (DebugLevel < 3) {
    return 1;
  }
  printk("Set_HtRdg_Proc::(HtRdg=%d)\n",*(undefined1 *)((int)param_1 + 0x79507d));
  return 1;
}

