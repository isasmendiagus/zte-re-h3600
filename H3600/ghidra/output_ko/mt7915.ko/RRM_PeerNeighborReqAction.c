// module: mt7915.ko
// function: RRM_PeerNeighborReqAction @ 0x22194c
// size: 744 bytes
//

void RRM_PeerNeighborReqAction(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  byte bVar5;
  int iVar6;
  undefined1 local_52;
  byte local_51;
  undefined4 local_50;
  char acStack_49 [37];
  
  local_50 = 0;
  local_51 = 0;
  if (2 < DebugLevel) {
    printk("%s::\n","RRM_PeerNeighborReqAction");
  }
  iVar2 = MacTableLookup(param_1,param_2 + 10);
  if ((iVar2 != 0) && (*(int *)(iVar2 + 0xfc) == 2)) {
    if ((&DAT_0036daa0)[param_1] == '\0') {
      iVar6 = RRM_PeerNeighborReqSanity
                        (param_1,param_2,*(undefined4 *)(param_2 + 0x908),&local_52,&local_50,
                         &local_51);
      if (iVar6 != 0) {
        if (2 < DebugLevel) {
          printk("DialogToken=%x\n",local_52);
        }
        snprintf(acStack_49,0x21,"%s",local_50);
        uVar4 = (uint)local_51;
        acStack_49[uVar4] = '\0';
        if (-1 < DebugLevel) {
          printk("pSsid=%s\n",acStack_49);
          uVar4 = (uint)local_51;
          if (2 < DebugLevel) {
            printk("SsidLen=%d\n",uVar4);
            uVar4 = (uint)local_51;
          }
        }
        RRM_EnqueueNeighborRep(param_1,iVar2,local_52,local_50,uVar4);
      }
    }
    else {
      bVar1 = 0;
      do {
        bVar5 = bVar1;
        uVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        iVar6 = (uint)bVar5 * 0x5834;
        if (uVar4 <= bVar5) goto LAB_00221a24;
        iVar3 = memcmp((void *)(param_2 + 0x10),
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + param_1 + iVar6 + 0x101,6);
        bVar1 = bVar5 + 1;
      } while (iVar3 != 0);
      iVar6 = *(int *)(
                      "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      + param_1 + iVar6 + 0xe0);
      if (iVar6 == 0) {
LAB_00221a24:
        if (-1 < DebugLevel) {
          printk("no valid NetDev! BSSID=%02x:%02x:%02x:%02x:%02x:%02x\n",
                 *(undefined1 *)(param_2 + 0x10),*(undefined1 *)(param_2 + 0x11),
                 *(undefined1 *)(param_2 + 0x12),*(undefined1 *)(param_2 + 0x13),
                 *(undefined1 *)(param_2 + 0x14),*(undefined1 *)(param_2 + 0x15));
        }
      }
      else {
        iVar3 = MeasureReqInsert(param_1,*(undefined1 *)(param_2 + 0x1a));
        if (iVar3 != 0) {
          _raw_spin_lock_bh(param_1 + 0x795974);
          *(int *)(iVar3 + 0x10) = param_1;
          *(byte *)(iVar3 + 0x4e) = bVar5;
          *(undefined1 *)(iVar3 + 0xd) = 1;
          *(undefined1 *)(iVar3 + 0xe) = 0;
          *(undefined4 *)(iVar3 + 0x48) = *(undefined4 *)(iVar2 + 0xec);
          *(undefined2 *)(iVar3 + 0x4c) = *(undefined2 *)(iVar2 + 0xf0);
          RTMPInitTimer(param_1,iVar3 + 0x14,rtmp_timer_WaitNRRspTimeout,iVar3,0);
          _raw_spin_unlock_bh(param_1 + 0x795974);
          wext_send_nr_req_event
                    (iVar6,param_2 + 10,param_2 + 0x1a,*(int *)(param_2 + 0x908) - 0x1aU & 0xffff);
          RTMPSetTimer(iVar3 + 0x14,120000);
          return;
        }
      }
    }
  }
  return;
}

