// module: mt7915.ko
// function: send_nr_resp_toair @ 0x21eb70
// size: 624 bytes
//

void send_nr_resp_toair(int param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  byte bVar7;
  undefined1 uStack_2d;
  int local_2c;
  undefined1 auStack_28 [12];
  
  uVar3 = *(ushort *)(param_2 + 8);
  local_2c = 0;
  iVar4 = MeasureReqLookUp(param_1,param_2[1]);
  if ((iVar4 == 0) && (param_2[1] != 0)) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s invalid token(%d)\n","send_nr_resp_toair");
    return;
  }
  iVar5 = MacTableLookup(param_1,param_2 + 2);
  if ((iVar5 == 0) ||
     (((*(uint *)(
                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + (uint)*param_2 * 0x5834 + param_1 + 0x10c) & 1) == 0 &&
      (*(short *)(iVar5 + 0x514) != 0x10a)))) {
    if (DebugLevel < 0) {
      return;
    }
    bVar7 = param_2[2];
    bVar1 = param_2[3];
    bVar2 = param_2[4];
    pcVar6 = "%s() STA(%02x:%02x:%02x:%02x:%02x:%02x) not associates with AP!\n";
  }
  else {
    __memzero(auStack_28,8);
    iVar5 = memcmp(auStack_28,(void *)(iVar5 + 0x11ec),8);
    if (iVar5 != 0) {
      os_alloc_mem(0,&local_2c,uVar3 + 0x1b);
      if (local_2c != 0) {
        __memzero(local_2c,uVar3 + 0x1b);
        iVar5 = local_2c;
        ActHeaderInit(param_1,local_2c,param_2 + 2,
                      "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      + (uint)*param_2 * 0x5834 + param_1 + 0x101,
                      "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      + (uint)*param_2 * 0x5834 + param_1 + 0x101);
        *(undefined1 *)(iVar5 + 0x18) = 5;
        *(undefined1 *)(iVar5 + 0x19) = 5;
        *(byte *)(iVar5 + 0x1a) = param_2[1];
        memmove((void *)(iVar5 + 0x1b),param_2 + 10,(uint)*(ushort *)(param_2 + 8));
        uVar3 = *(ushort *)(param_2 + 8);
        bVar7 = 0;
        if (param_2[1] != 0) {
          RTMPCancelTimer(iVar4 + 0x14,&uStack_2d);
          RTMPReleaseTimer(iVar4 + 0x14,&uStack_2d);
          bVar7 = param_2[1];
        }
        MeasureReqDelete(param_1,bVar7);
        MiniportMMRequest(param_1,0x81,local_2c,uVar3 + 0x1b);
        os_free_mem(local_2c);
        return;
      }
      if (DebugLevel < 0) {
        return;
      }
      printk("%s Not available memory for neighbor report frame\n","send_nr_resp_toair");
      return;
    }
    if (DebugLevel < 0) {
      return;
    }
    bVar7 = param_2[2];
    bVar1 = param_2[3];
    bVar2 = param_2[4];
    pcVar6 = "%s() STA(%02x:%02x:%02x:%02x:%02x:%02x) not support rrm\n";
  }
  printk(pcVar6,"send_nr_resp_toair",bVar7,bVar1,bVar2,param_2[5],param_2[6],param_2[7]);
  return;
}

