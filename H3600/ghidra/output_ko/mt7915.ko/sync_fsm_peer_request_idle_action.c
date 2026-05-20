// module: mt7915.ko
// function: sync_fsm_peer_request_idle_action @ 0x10a070
// size: 1152 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: ram */

void sync_fsm_peer_request_idle_action(int param_1,int param_2)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 *puVar7;
  char *pcVar8;
  uint uVar9;
  byte bVar10;
  undefined1 auStack_80 [4];
  undefined1 local_7c;
  undefined1 local_7b;
  undefined1 local_7a;
  undefined1 local_79;
  uint local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  iVar3 = PeerProbeReqSanity(param_1,param_2,*(undefined4 *)(param_2 + 0x908),&local_5c);
  if (iVar3 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s():shiang! PeerProbeReqSanity failed!\n","sync_fsm_peer_request_idle_action");
    return;
  }
  cVar2 = *(char *)(param_1 + 0x286285);
  if (cVar2 != '\x01') goto joined_r0x0010a444;
  uVar6 = local_38 >> 0x10 & 0xff;
  if (((uVar6 == 0) || (*(byte *)(param_1 + 0xa7cc25) != uVar6)) ||
     (iVar3 = memcmp((void *)((int)&local_58 + 2),(void *)(param_1 + 0xa7cc04),
                     (uint)*(byte *)(param_1 + 0xa7cc25)), iVar3 != 0)) {
    if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
        [param_1 + 0xda] == '\0') {
      return;
    }
LAB_0010a18c:
    uVar6 = 0;
    do {
      iVar3 = param_1 + uVar6 * 0x5834;
      if ("Wrong format, vow_watf_q=[Level]-[Quantum]\n[Level] should be among 0 to 3 !\n[Quantum] unit is 256us.\n"
          [iVar3] != '\0') {
        pcVar8 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + param_1 + uVar6 * 0x5834 + 0xe0;
        iVar4 = HcGetBandByWdev(pcVar8);
        if ((*(int *)(param_1 + (iVar4 + 0xd9e3a) * 4) != 0) &&
           ((iVar4 = HcGetBandByWdev(pcVar8), *(int *)(param_1 + (iVar4 + 0xd9e3a) * 4) == 0 ||
            (uVar9 = *(uint *)(
                              "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                              + iVar3 + 0x2c), iVar3 = HcGetBandByWdev(pcVar8),
            uVar9 != (byte)(&DAT_003678f2)[param_1 + iVar3])))) {
          iVar3 = HcGetBandByWdev(pcVar8);
          iVar4 = uVar6 * 0x5834 + param_1;
          if ((*(uint *)(param_1 + (iVar3 + 0xd9e3a) * 4) &
              1 << (*(uint *)(
                             "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                             + iVar4 + 0x30) & 0xff)) != 0) {
            if (3 < DebugLevel) {
              printk("%s(): wdev %d is Nontransmitted Bssid, ignore!!\n",
                     "sync_fsm_peer_request_idle_action",
                     "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                     [iVar4 + 0xec]);
            }
            goto LAB_0010a1a8;
          }
        }
        puVar7 = *(undefined4 **)
                  (
                  "Wrong format, vow_watf_add_entry=[Level]-[Addr]:[Addr]:[Addr]:[Addr]:[Addr]:[Addr]\n[Level] should be among 0 to 3 !\n"
                  + uVar6 * 0x5834 + param_1 + 0x10);
        iVar3 = HcGetBandByWdev(pcVar8);
        if (iVar3 == 1) {
          if (0x23 < *(byte *)(param_2 + 0x91f)) goto LAB_0010a310;
        }
        else if ((iVar3 != 0) || (*(byte *)(param_2 + 0x91f) < 0xf)) {
LAB_0010a310:
          g_stWlanFactoryStatistics._8_4_ = g_stWlanFactoryStatistics._8_4_ + 1;
          if ((puVar7 != (undefined4 *)0x0) &&
             (((code *)*puVar7 != (code *)0x0 &&
              (iVar3 = (*(code *)*puVar7)(param_1,pcVar8,&local_5c,param_2), iVar3 == 1)))) {
            (*(code *)puVar7[1])(param_1,pcVar8,&local_5c,param_2);
            g_stWlanFactoryStatistics._12_4_ = g_stWlanFactoryStatistics._12_4_ + 1;
          }
        }
      }
LAB_0010a1a8:
      uVar6 = uVar6 + 1 & 0xff;
    } while (uVar6 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           [param_1 + 0xda]);
  }
  else {
    if (*(char *)(param_2 + 0x918) == '\0') {
      local_7c = 0;
    }
    else {
      local_7c = ConvertToRssi(param_1,param_2 + 0x918);
    }
    if (*(char *)(param_2 + 0x919) == '\0') {
      local_7b = 0;
    }
    else {
      local_7b = ConvertToRssi(param_1,param_2 + 0x918,1);
    }
    if (*(char *)(param_2 + 0x91a) == '\0') {
      local_7a = 0;
    }
    else {
      local_7a = ConvertToRssi(param_1,param_2 + 0x918,2);
    }
    local_79 = 0;
    if (*(char *)(param_2 + 0x91b) != '\0') {
      local_79 = ConvertToRssi(param_1,param_2 + 0x918,3);
    }
    uVar5 = RTMPAvgRssi(param_1,auStack_80);
    bVar10 = *(byte *)(param_2 + 0x91f);
    bVar1 = 0x24 < bVar10;
    if (-1 < DebugLevel) {
      printk("rssi=%d %02x:%02x\n",uVar5,local_5c & 0xff,local_58._1_1_);
      bVar10 = *(byte *)(param_2 + 0x91f);
    }
    ZTE_APUnAssocStaInfoRecordAndReport(param_1,&local_5c,uVar5,bVar1,bVar10);
    if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
        [param_1 + 0xda] != '\0') goto LAB_0010a18c;
  }
  cVar2 = *(char *)(param_1 + 0x286285);
joined_r0x0010a444:
  if (cVar2 == '\0') {
    iVar3 = *(int *)(param_2 + 0x92c);
    puVar7 = *(undefined4 **)(iVar3 + 0xbcc);
    if (((puVar7 != (undefined4 *)0x0) && ((code *)*puVar7 != (code *)0x0)) &&
       (iVar4 = (*(code *)*puVar7)(param_1,iVar3,&local_5c,param_2), iVar4 == 1)) {
      (*(code *)puVar7[1])(param_1,iVar3,&local_5c,param_2);
    }
  }
  return;
}

