// module: mt7915.ko
// function: ZTE_show_PingFixRate @ 0x15c1f4
// size: 284 bytes
//

undefined4 ZTE_show_PingFixRate(int *param_1)

{
  int iVar1;
  
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  iVar1 = HcGetBandByWdev();
  if (DebugLevel < 0) {
    return 1;
  }
  printk("enable=%d\n",(char)param_1[(int)("MtCmdSetFreqOffset" + iVar1 * 9 + 1)]);
  if (-1 < DebugLevel) {
    printk("transmit_mode=%d\n",param_1[(int)("MtCmdSetFreqOffset" + iVar1 * 9 + 2)]);
    if (DebugLevel < 0) {
      return 1;
    }
    printk("transmit_mcs=%d\n",param_1[(int)("MtCmdSetFreqOffset" + iVar1 * 9 + 3)]);
    if (DebugLevel < 0) {
      return 1;
    }
    printk("retry_limit_by_host=%d\n",param_1[(int)("MtCmdSetFreqOffset" + iVar1 * 9 + 4)]);
    if (DebugLevel < 0) {
      return 1;
    }
    printk("tid=%d\n",param_1[(int)("MtCmdSetFreqOffset" + iVar1 * 9 + 5)]);
  }
  if (-1 < DebugLevel) {
    printk("transmit_stbc=%d\n",param_1[(int)("MtCmdSetFreqOffset" + iVar1 * 9 + 6)]);
  }
  return 1;
}

