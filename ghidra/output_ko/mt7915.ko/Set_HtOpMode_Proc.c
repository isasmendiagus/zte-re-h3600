// module: mt7915.ko
// function: Set_HtOpMode_Proc @ 0xddf40
// size: 192 bytes
//

undefined4 Set_HtOpMode_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 == 0) {
    return 0;
  }
  iVar2 = os_str_tol(param_2,0,10);
  if (iVar2 == 1) {
    *(byte *)((int)param_1 + 0x794cce) = *(byte *)((int)param_1 + 0x794cce) | 1;
  }
  else {
    if (iVar2 != 0) {
      return 0;
    }
    *(byte *)((int)param_1 + 0x794cce) = *(byte *)((int)param_1 + 0x794cce) & 0xfe;
  }
  SetCommonHtVht(param_1,iVar1);
  if (2 < DebugLevel) {
    printk("Set_HtOpMode_Proc::(HtOpMode=%d)\n",*(byte *)((int)param_1 + 0x794cce) & 1);
    return 1;
  }
  return 1;
}

