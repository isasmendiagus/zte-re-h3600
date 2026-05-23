// module: mt7915.ko
// function: ZTE_reduce_delay_rx @ 0x15df74
// size: 300 bytes
//

undefined4 ZTE_reduce_delay_rx(int *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  
  if ((param_1 == (int *)0x0) || (iVar2 = *param_1, iVar2 == 0)) {
    if (-1 < DebugLevel) {
      printk("%s para error pAdapter =%p\n","ZTE_reduce_delay_rx",param_1);
    }
  }
  else {
    iVar2 = get_wdev_by_ioctl_idx_and_iftype
                      (param_1,*(undefined4 *)(iVar2 + 0x3c),*(undefined4 *)(iVar2 + 0x38));
    if (iVar2 != 0) {
      iVar2 = HcGetBandByWdev();
      if (iVar2 != 0) {
        cVar1 = simple_strtol(param_2,0,10);
        if (2 < DebugLevel) {
          printk("%s[%d]\n","ZTE_reduce_delay_rx",(int)cVar1);
        }
        if (cVar1 == 1) {
          rx_isr_th_backup(param_1);
          rx_isr_th_enhance(param_1);
          return 1;
        }
        if ((char)param_1[0x29f151] != '\0') {
          FUN_00156824(param_1);
        }
      }
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("%s para error wdev =%p\n","ZTE_reduce_delay_rx",0);
      return 0;
    }
  }
  return 0;
}

