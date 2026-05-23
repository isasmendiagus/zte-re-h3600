// module: mt7915.ko
// function: check_rrm_BcnReq_custom_params @ 0x221dd4
// size: 468 bytes
//

undefined4 check_rrm_BcnReq_custom_params(int param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  char *pcVar4;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  if (2 < DebugLevel) {
    printk("%s()\n","check_rrm_BcnReq_custom_params");
  }
  iVar3 = MacTableLookup(param_1,param_2);
  if ((iVar3 == 0) ||
     (((*(uint *)(
                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + (uint)*(byte *)(iVar3 + 0xe4) * 0x5834 + param_1 + 0x10c) & 1) == 0 &&
      (*(short *)(iVar3 + 0x514) != 0x10a)))) {
    if (DebugLevel < 0) {
      return 1;
    }
    uVar1 = *param_2;
    uVar2 = param_2[1];
    pcVar4 = "%s() STA(%02x:%02x:%02x:%02x:%02x:%02x) not associates with AP!\n";
  }
  else {
    if ((*(byte *)(iVar3 + 0x11ec) & 0x30) != 0) {
      if (param_2[9] == '\0') {
        if (param_2[8] != '\0') {
          return 0;
        }
        if (DebugLevel < 0) {
          return 1;
        }
        printk("%s() regclass cannot set to 0 when channel is set to 0\n",
               "check_rrm_BcnReq_custom_params");
        return 1;
      }
      if (param_2[9] != -1) {
        return 0;
      }
      if (param_2[0x3e] == '\0') {
        if (DebugLevel < 0) {
          return 1;
        }
        printk("%s() op class must be set when channel is set to 255!\n",
               "check_rrm_BcnReq_custom_params");
        return 1;
      }
      iVar3 = RTMPCompareMemory(param_2 + 0x3f,&local_20,0x10);
      if (iVar3 != 0) {
        return 0;
      }
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s() op class list is invalid!\n","check_rrm_BcnReq_custom_params");
      return 1;
    }
    if (DebugLevel < 0) {
      return 1;
    }
    uVar1 = *param_2;
    uVar2 = param_2[1];
    pcVar4 = "%s() STA(%02x:%02x:%02x:%02x:%02x:%02x) not support beacon report!\n";
  }
  printk(pcVar4,"check_rrm_BcnReq_custom_params",uVar1,uVar2,param_2[2],param_2[3],param_2[4],
         param_2[5]);
  return 1;
}

