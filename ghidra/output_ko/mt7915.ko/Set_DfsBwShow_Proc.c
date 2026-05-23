// module: mt7915.ko
// function: Set_DfsBwShow_Proc @ 0x23085c
// size: 172 bytes
//

undefined4 Set_DfsBwShow_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("wdev is NULL\n");
    return 0;
  }
  iVar1 = HcGetBandByWdev();
  os_str_tol(param_2,0,10);
  if (DebugLevel < 1) {
    return 1;
  }
  printk("Current DFS Bw is %d\n",*(undefined1 *)((int)param_1 + iVar1 + 0x795134));
  return 1;
}

