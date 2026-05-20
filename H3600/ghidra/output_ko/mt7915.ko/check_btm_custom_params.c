// module: mt7915.ko
// function: check_btm_custom_params @ 0x2276d0
// size: 480 bytes
//

undefined4 check_btm_custom_params(int param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  undefined1 *__s1;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  
  local_16 = 0;
  local_15 = 0;
  local_14 = 0;
  local_13 = 0;
  local_12 = 0;
  local_11 = 0;
  iVar3 = MacTableLookup();
  if ((iVar3 == 0) ||
     (((*(uint *)(
                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + (uint)*(byte *)(iVar3 + 0xe4) * 0x5834 + param_1 + 0x10c) & 1) == 0 &&
      (*(short *)(iVar3 + 0x514) != 0x10a)))) {
    if (-1 < DebugLevel) {
      uVar1 = *param_2;
      uVar2 = param_2[1];
      pcVar5 = "%s() STA(%02x:%02x:%02x:%02x:%02x:%02x) not associates with AP!\n";
LAB_00227790:
      printk(pcVar5,"check_btm_custom_params",uVar1,uVar2,param_2[2],param_2[3],param_2[4],
             param_2[5]);
      return 1;
    }
  }
  else if (*(char *)(iVar3 + 0xd22) == '\0') {
    if (-1 < DebugLevel) {
      uVar1 = *param_2;
      uVar2 = param_2[1];
      pcVar5 = "%s() STA(%02x:%02x:%02x:%02x:%02x:%02x) not support btm!\n";
      goto LAB_00227790;
    }
  }
  else {
    if ((byte)param_2[0x42] == 0) {
      if (DebugLevel < 2) {
        return 0;
      }
      printk("%s() candidate count equals to 0; btm request is meaningless\n",
             "check_btm_custom_params");
      return 0;
    }
    __s1 = param_2 + 0x48;
    iVar3 = (uint)(byte)param_2[0x42] * 0x12;
    while( true ) {
      iVar3 = iVar3 + -0x12;
      iVar4 = memcmp(__s1,&local_16,6);
      if (iVar4 == 0) {
        if (DebugLevel < 0) {
          return 1;
        }
        printk("%s() bssid check failed \n","check_btm_custom_params");
        return 1;
      }
      pcVar5 = __s1 + -5;
      __s1 = __s1 + 0x12;
      if (*pcVar5 == '\0') break;
      if (iVar3 < 1) {
        return 0;
      }
    }
    if (-1 < DebugLevel) {
      printk("%s() channel check failed \n","check_btm_custom_params");
      return 1;
    }
  }
  return 1;
}

