// module: mt7915.ko
// function: ZTE_Set_WorkMode_Proc @ 0x29524
// size: 200 bytes
//

undefined4 ZTE_Set_WorkMode_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar2 = HcGetBandByWdev();
  if (uVar2 < 2) {
    iVar3 = simple_strtol(param_2,0,10);
    iVar1 = DebugLevel;
    param_1[(int)("MtCmdSetFreqOffset" + uVar2 * 9 + 7)] = iVar3;
    if (iVar1 < 1) {
      return 1;
    }
    printk("%s::(band_idx=%d, WorkMode=%d)\n","ZTE_Set_WorkMode_Proc",uVar2);
    return 1;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s : band_idx error value=%d\n","ZTE_Set_WorkMode_Proc",uVar2);
  return 0;
}

