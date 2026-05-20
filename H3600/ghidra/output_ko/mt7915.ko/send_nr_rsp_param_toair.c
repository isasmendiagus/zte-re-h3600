// module: mt7915.ko
// function: send_nr_rsp_param_toair @ 0x221218
// size: 508 bytes
//

void send_nr_rsp_param_toair(int param_1,byte *param_2)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  undefined1 uStack_39;
  void *local_38;
  int local_34;
  undefined1 auStack_30 [24];
  
  uVar1 = *(undefined2 *)(param_2 + 8);
  local_38 = (void *)0x0;
  local_34 = 0;
  iVar2 = MeasureReqLookUp(param_1,param_2[0x10]);
  if ((iVar2 == 0) && (param_2[0x10] != 0)) {
    if (-1 < DebugLevel) {
      printk("%s() invalid token(%d)\n","send_nr_rsp_param_toair");
    }
  }
  else {
    iVar3 = check_rrm_nrrsp_custom_params(param_1,param_2 + 10,uVar1);
    if (iVar3 == 0) {
      iVar3 = os_alloc_mem(param_1,&local_38,0x900);
      if (iVar3 == 0) {
        ActHeaderInit(param_1,auStack_30,param_2 + 10,
                      "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      + (uint)*param_2 * 0x5834 + param_1 + 0x101,
                      "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      + (uint)*param_2 * 0x5834 + param_1 + 0x101);
        memmove(local_38,auStack_30,0x18);
        local_34 = 0x18;
        InsertActField(param_1,(int)local_38 + 0x18,&local_34,5,5);
        InsertDialogToken(param_1,(int)local_38 + local_34,&local_34,param_2[0x10]);
        compose_rrm_nrrsp_ie
                  (param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           + (uint)*param_2 * 0x5834 + param_1 + 0xe0,local_38,&local_34,
                   param_2 + 0x12,param_2[0x11]);
        bVar4 = 0;
        if (param_2[0x10] != 0) {
          RTMPCancelTimer(iVar2 + 0x14,&uStack_39);
          RTMPReleaseTimer(iVar2 + 0x14,&uStack_39);
          bVar4 = param_2[0x10];
        }
        MeasureReqDelete(param_1,bVar4);
        MiniportMMRequest(param_1,0x81,local_38,local_34);
        os_free_mem(local_38);
      }
      else if (-1 < DebugLevel) {
        printk("%s() allocate memory for neighbor report frame failed\n","send_nr_rsp_param_toair");
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s() check customer params failed\n","send_nr_rsp_param_toair");
    }
  }
  return;
}

