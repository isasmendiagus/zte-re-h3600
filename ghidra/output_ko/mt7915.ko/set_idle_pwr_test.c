// module: mt7915.ko
// function: set_idle_pwr_test @ 0x26aac
// size: 332 bytes
//

undefined4 set_idle_pwr_test(int *param_1,char *param_2)

{
  int iVar1;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  if (iVar1 != 0) {
    HcGetBandByWdev();
    if (param_2 == (char *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s: Arg is Null\n","set_idle_pwr_test");
      }
    }
    else {
      iVar1 = sscanf(param_2,"%d:%u:%u:%u",&local_34,&local_30,&local_2c,&local_28);
      if (iVar1 == 4) {
        if (2 < DebugLevel) {
          printk("%s: pwr_thres %d, time %d, cnt = %d, cmd_type = %d\n","set_idle_pwr_test",local_34
                 ,local_30,local_2c,local_28);
        }
        os_zero_mem(local_24,0x14);
        local_20 = local_34;
        local_1c = local_2c;
        local_18 = local_30;
        local_14 = local_28;
        local_24[0] = 2;
        mt_cmd_set_rdd_ipi_hist(param_1,local_24);
        return 0;
      }
      if (-1 < DebugLevel) {
        printk(
              "Format Error! Please enter in the following format\npwr_thres:time(ms):cnt:offset_level\n"
              );
      }
    }
  }
  return 1;
}

