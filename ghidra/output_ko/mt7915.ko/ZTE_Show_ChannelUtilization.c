// module: mt7915.ko
// function: ZTE_Show_ChannelUtilization @ 0x156b54
// size: 168 bytes
//

undefined4 ZTE_Show_ChannelUtilization(int *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar1 = HcGetBandByWdev();
  if (0 < DebugLevel) {
    printk("%s : band_idx value=%d\n","ZTE_Show_ChannelUtilization",uVar1);
  }
  if (1 < uVar1) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s : band_idx error value=%d\n","ZTE_Show_ChannelUtilization",uVar1);
    return 0;
  }
  uVar2 = ZTE_Get_ChannelUtilization(param_1,uVar1);
  printk("ChannelUtilization:%d\n",uVar2);
  return 1;
}

