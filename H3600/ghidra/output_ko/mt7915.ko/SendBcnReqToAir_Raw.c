// module: mt7915.ko
// function: SendBcnReqToAir_Raw @ 0x21ede0
// size: 648 bytes
//

void SendBcnReqToAir_Raw(int param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  void *local_40;
  int local_3c;
  undefined1 auStack_38 [24];
  
  bVar1 = param_2[1];
  bVar2 = *param_2;
  local_40 = (void *)0x0;
  local_3c = 0;
  if (2 < DebugLevel) {
    printk("%s()\n","SendBcnReqToAir_Raw");
  }
  iVar4 = MacTableLookup(param_1,param_2 + 0xf);
  if ((iVar4 == 0) ||
     (((*(uint *)(
                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + (uint)bVar2 * 0x5834 + param_1 + 0x10c) & 1) == 0 &&
      (*(short *)(iVar4 + 0x514) != 0x10a)))) {
    if (DebugLevel < 0) goto LAB_0021ee70;
    bVar2 = param_2[0xf];
    bVar3 = param_2[0x10];
    pcVar6 = "%s() STA(%02x:%02x:%02x:%02x:%02x:%02x) not associates with AP!\n";
  }
  else {
    if ((*(byte *)(iVar4 + 0x11ec) & 0x30) != 0) {
      iVar4 = os_alloc_mem(param_1,&local_40,0x900);
      if (iVar4 == 0) {
        ActHeaderInit(param_1,auStack_38,param_2 + 0xf,
                      "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      + (uint)bVar2 * 0x5834 + param_1 + 0x101,
                      "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      + (uint)bVar2 * 0x5834 + param_1 + 0x101);
        memmove(local_40,auStack_38,0x18);
        local_3c = 0x18;
        InsertActField(param_1,(int)local_40 + 0x18,&local_3c,5,0);
        InsertDialogToken(param_1,(int)local_40 + local_3c,&local_3c,param_2[0xe]);
        memcpy((void *)((int)local_40 + local_3c),param_2 + 0x19,*(size_t *)(param_2 + 0x15));
        local_3c = *(int *)(param_2 + 0x15) + local_3c;
        MiniportMMRequest(param_1,0x81,local_40);
        iVar5 = MeasureReqLookUp(param_1,bVar1);
        iVar4 = DebugLevel;
        if (iVar5 != 0) {
          *(undefined1 *)(iVar5 + 0xe) = 2;
          if (2 < iVar4) {
            printk("%s() Timeout=%lds!\n","SendBcnReqToAir_Raw",0x3c);
          }
          RTMPInitTimer(param_1,iVar5 + 0x50,rtmp_timer_WaitPeerBCNRepTimeout,iVar5,0);
          RTMPSetTimer(iVar5 + 0x50,60000);
        }
        os_free_mem(local_40);
        return;
      }
      if (2 < DebugLevel) {
        printk("%s() allocate memory failed \n","SendBcnReqToAir_Raw");
      }
      goto LAB_0021ee70;
    }
    if (DebugLevel < 0) goto LAB_0021ee70;
    bVar2 = param_2[0xf];
    bVar3 = param_2[0x10];
    pcVar6 = "%s() STA(%02x:%02x:%02x:%02x:%02x:%02x) does not support beacon report!\n";
  }
  printk(pcVar6,"SendBcnReqToAir_Raw",bVar2,bVar3,param_2[0x11],param_2[0x12],param_2[0x13],
         param_2[0x14]);
LAB_0021ee70:
  MeasureReqDelete(param_1,bVar1);
  return;
}

