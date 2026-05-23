// module: mt7915.ko
// function: set_dedicated_rx_hist_proc @ 0x22ea54
// size: 364 bytes
//

undefined4 set_dedicated_rx_hist_proc(int *param_1,char *param_2)

{
  int iVar1;
  undefined4 local_34;
  undefined4 local_30;
  undefined1 local_2c [3];
  undefined1 local_29;
  
  local_34 = 0;
  local_30 = 0;
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  os_zero_mem(local_2c);
  RTMPInitTimer(param_1,param_1 + 0x29e47e,rtmp_timer_dedicated_rx_hist_scan_timeout,param_1,0);
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: wdev is Null\n","set_dedicated_rx_hist_proc");
      return 1;
    }
    return 1;
  }
  HcGetBandByWdev(iVar1);
  if (param_2 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: Arg is Null\n","set_dedicated_rx_hist_proc");
      return 0;
    }
  }
  else {
    iVar1 = sscanf(param_2,"%u:%u",&local_34,&local_30);
    if (iVar1 == 2) {
      *(char *)((int)param_1 + 0xa7979d) = (char)local_34;
      param_1[0x29e461] = 1;
      local_29 = 0;
      local_2c[0] = 1;
      mt_cmd_set_rdd_ipi_hist(param_1,local_2c);
      RTMPSetTimer(param_1 + 0x29e47e,local_30);
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("Format Error! Please enter in the following format\nthreshold(0-10):period(ms)\n");
      return 0;
    }
  }
  return 0;
}

