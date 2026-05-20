// module: mt7915.ko
// function: check_rrm_nrrsp_custom_params @ 0x220cd4
// size: 500 bytes
//

undefined4 check_rrm_nrrsp_custom_params(int param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  undefined1 *__s1;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  undefined1 auStack_18 [8];
  
  local_1e = 0;
  local_1d = 0;
  local_1c = 0;
  local_1b = 0;
  local_1a = 0;
  local_19 = 0;
  iVar3 = MacTableLookup();
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
    pcVar5 = "%s() STA(%02x:%02x:%02x:%02x:%02x:%02x) not associates with AP!\n";
  }
  else {
    __memzero(auStack_18,8);
    iVar3 = memcmp(auStack_18,(void *)(iVar3 + 0x11ec),8);
    if (iVar3 != 0) {
      if ((byte)param_2[7] == 0) {
        if (DebugLevel < 2) {
          return 0;
        }
        printk("%s() nr count equals to 0; neighbor report response is meaningless\n",
               "check_rrm_nrrsp_custom_params");
        return 0;
      }
      __s1 = param_2 + 0xd;
      iVar3 = (uint)(byte)param_2[7] * 0x12;
      while( true ) {
        iVar4 = memcmp(__s1,&local_1e,6);
        if (iVar4 == 0) {
          if (DebugLevel < 0) {
            return 1;
          }
          printk("%s() bssid check failed \n","check_rrm_nrrsp_custom_params");
          return 1;
        }
        pcVar5 = __s1 + -5;
        __s1 = __s1 + 0x12;
        if (*pcVar5 == '\0') break;
        iVar3 = iVar3 + -0x12;
        if (iVar3 == 0) {
          return 0;
        }
      }
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s() channel check failed \n","check_rrm_nrrsp_custom_params");
      return 1;
    }
    if (DebugLevel < 0) {
      return 1;
    }
    uVar1 = *param_2;
    uVar2 = param_2[1];
    pcVar5 = "%s() STA(%02x:%02x:%02x:%02x:%02x:%02x) not support rrm\n";
  }
  printk(pcVar5,"check_rrm_nrrsp_custom_params",uVar1,uVar2,param_2[2],param_2[3],param_2[4],
         param_2[5]);
  return 1;
}

