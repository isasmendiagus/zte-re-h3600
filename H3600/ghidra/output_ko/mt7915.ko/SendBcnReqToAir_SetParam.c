// module: mt7915.ko
// function: SendBcnReqToAir_SetParam @ 0x222564
// size: 508 bytes
//

void SendBcnReqToAir_SetParam(int param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  undefined4 *local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  
  pbVar5 = param_2 + 10;
  bVar1 = param_2[1];
  bVar2 = *param_2;
  local_40 = (undefined4 *)0x0;
  local_3c = 0;
  if (2 < DebugLevel) {
    printk("%s()\n","SendBcnReqToAir_SetParam");
  }
  iVar3 = check_rrm_BcnReq_custom_params(param_1,pbVar5);
  if (iVar3 == 0) {
    set_rrm_BcnReq_optional_params(param_1,pbVar5);
    iVar3 = os_alloc_mem(param_1,&local_40,0x900);
    if (iVar3 == 0) {
      ActHeaderInit(param_1,&local_38,param_2 + 2,
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + (uint)bVar2 * 0x5834 + param_1 + 0x101,
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + (uint)bVar2 * 0x5834 + param_1 + 0x101);
      *local_40 = local_38;
      local_40[2] = uStack_30;
      local_40[3] = uStack_2c;
      local_40[1] = uStack_34;
      local_40[4] = local_28;
      local_40[5] = uStack_24;
      compose_rrm_BcnReq_ie(param_1,local_40 + 6,&local_3c,pbVar5,bVar1,(uint)bVar2);
      MiniportMMRequest(param_1,0x81,local_40,local_3c + 0x18);
      iVar3 = MeasureReqLookUp(param_1,bVar1);
      if (iVar3 != 0) {
        *(undefined1 *)(iVar3 + 0xe) = 2;
        iVar4 = *(int *)(param_2 + 0x41);
        if (2 < DebugLevel) {
          printk("%s() Timeout=%lds!\n","SendBcnReqToAir_SetParam",(uint)(iVar4 * 1000) / 1000);
        }
        RTMPInitTimer(param_1,iVar3 + 0x50,rtmp_timer_WaitPeerBCNRepTimeout,iVar3,0);
        RTMPSetTimer(iVar3 + 0x50,iVar4 * 1000);
      }
      os_free_mem(local_40);
      return;
    }
    if (-1 < DebugLevel) {
      printk("%s, MEMORY ALLOC Failed!!\n","SendBcnReqToAir_SetParam");
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s() check customer params failed\n","SendBcnReqToAir_SetParam");
  }
  MeasureReqDelete(param_1,bVar1);
  return;
}

