// module: mt7915.ko
// function: ap_probe_response_allowed @ 0x4beb8
// size: 1228 bytes
//

bool ap_probe_response_allowed(int param_1,int *param_2,int param_3,int param_4)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  undefined4 local_5d;
  undefined2 local_59;
  undefined1 auStack_57 [5];
  char local_52;
  char local_51;
  undefined4 local_4c;
  undefined1 local_48;
  undefined1 local_47;
  undefined1 local_46;
  undefined1 local_45;
  
  local_5d = *(undefined4 *)(param_4 + 0x10);
  iVar8 = param_2[1];
  local_59 = *(undefined2 *)(param_4 + 0x14);
  if (*param_2 == 0) {
    return false;
  }
  if ((*(uint *)(*param_2 + 0x138) & 1) == 0) {
    return false;
  }
  hc_radio_query_by_channel(param_1,*(undefined1 *)((int)param_2 + 0x1a),auStack_57);
  if ((local_52 != *(char *)(param_4 + 0x91f)) && (local_51 != *(char *)(param_4 + 0x91f))) {
    return false;
  }
  if (*(byte *)(param_3 + 0x26) != 0) {
    if (((uint)*(byte *)(iVar8 + 0x4089) == (uint)*(byte *)(param_3 + 0x26)) &&
       (iVar2 = memcmp((void *)(param_3 + 6),(void *)(iVar8 + 0x4068),
                       (uint)*(byte *)(iVar8 + 0x4089)), iVar2 == 0)) goto LAB_0004bfac;
    iVar2 = HcGetBandByWdev(param_2);
    if ((*(int *)(param_1 + (iVar2 + 0xd9e3a) * 4) != 0) &&
       (((uVar9 = *(uint *)(iVar8 + 0x4060), iVar2 = HcGetBandByWdev(param_2),
         uVar9 == (byte)(&DAT_003678f2)[param_1 + iVar2] &&
         (iVar2 = HcGetBandByWdev(param_2),
         (*(uint *)(param_1 + (iVar2 + 0xd9e3a) * 4) & ~(1 << (*(uint *)(iVar8 + 0x4064) & 0xff)))
         != 0)) &&
        ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
         [param_1 + 0xda] != '\0')))) {
      uVar9 = 0;
      do {
        iVar7 = uVar9 * 0x5834;
        iVar10 = param_1 + iVar7;
        iVar2 = HcGetBandByWdev("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                + param_1 + iVar7 + 0xe0);
        uVar6 = *(uint *)(param_1 + (iVar2 + 0xd9e3a) * 4);
        if ((((uVar6 != 0) &&
             (*(uint *)(
                       "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                       + iVar10 + 0x2c) != (uint)(byte)(&DAT_003678f2)[param_1 + iVar2])) &&
            (((uVar6 & 1 << (*(uint *)(
                                      "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                                      + iVar10 + 0x30) & 0xff)) != 0 &&
             ((iVar5 = HcGetBandByWdev(param_2), iVar5 == iVar2 &&
              ((uint)(byte)"pStaCfg->WpaPassPhrase"[iVar10 + 5] == (uint)*(byte *)(param_3 + 0x26)))
             )))) && (iVar2 = memcmp((void *)(param_3 + 6),
                                     "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                                     + param_1 + iVar7 + 0x34,
                                     (uint)(byte)"pStaCfg->WpaPassPhrase"[iVar10 + 5]), iVar2 == 0))
        {
          if (3 < DebugLevel) {
            printk("%s(): NonTx SSID found, apidx=%d\n","ap_probe_response_allowed",uVar9);
          }
          goto LAB_0004bfac;
        }
        uVar9 = uVar9 + 1 & 0xff;
      } while (uVar9 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                             [param_1 + 0xda]);
    }
    if (*(char *)(param_3 + 0x26) != '\0') {
      if (*(char *)(param_3 + 0x26) != ' ') {
        return false;
      }
      iVar2 = memcmp(&local_5d,(void *)((int)param_2 + 0x21),6);
      if (iVar2 != 0) {
        return false;
      }
    }
  }
  if (*(char *)(iVar8 + 0x408a) != '\0') {
    return false;
  }
LAB_0004bfac:
  iVar8 = ApCheckMapBlackList(param_1,param_3,*(undefined1 *)((int)param_2 + 0xe));
  if (iVar8 == 0) {
    if (DebugLevel < 3) {
      return false;
    }
    printk("%s():probed by black sheep, return!\n","ap_probe_response_allowed");
    return false;
  }
  local_48 = 0;
  if (*(char *)(param_4 + 0x918) != '\0') {
    local_48 = ConvertToRssi(param_1,param_4 + 0x918,0);
  }
  if (*(char *)(param_4 + 0x919) == '\0') {
    local_47 = 0;
  }
  else {
    local_47 = ConvertToRssi(param_1,param_4 + 0x918,1);
  }
  if (*(char *)(param_4 + 0x91a) == '\0') {
    local_46 = 0;
  }
  else {
    local_46 = ConvertToRssi(param_1,param_4 + 0x918,2);
  }
  local_45 = 0;
  if (*(char *)(param_4 + 0x91b) != '\0') {
    local_45 = ConvertToRssi(param_1,param_4 + 0x918,3);
  }
  uVar3 = RTMPAvgRssi(param_1,&local_4c);
  uVar4 = HcGetBandByWdev(param_2);
  ZTE_APUnAssocStaInfoRecordAndReport(param_1,param_3,uVar3,uVar4,*(undefined1 *)(param_4 + 0x91f));
  if ((&DAT_0036b920)[param_1] == '\0') {
    return true;
  }
  uVar3 = Get_BndStrgTable(param_1,*(undefined1 *)((int)param_2 + 0xe));
  local_4c = 0;
  uVar1 = 0;
  if (*(char *)(param_4 + 0x918) != '\0') {
    uVar1 = ConvertToRssi(param_1,param_4 + 0x918);
  }
  local_4c = CONCAT31(local_4c._1_3_,uVar1);
  if (*(char *)(param_4 + 0x919) == '\0') {
    uVar1 = 0;
  }
  else {
    uVar1 = ConvertToRssi(param_1,param_4 + 0x918,1);
  }
  local_4c._0_2_ = CONCAT11(uVar1,(undefined1)local_4c);
  if (*(char *)(param_4 + 0x91a) == '\0') {
    uVar1 = 0;
  }
  else {
    uVar1 = ConvertToRssi(param_1,param_4 + 0x918,2);
  }
  local_4c._0_3_ = CONCAT12(uVar1,(undefined2)local_4c);
  if (*(char *)(param_4 + 0x91b) == '\0') {
    uVar1 = 0;
  }
  else {
    uVar1 = ConvertToRssi(param_1,param_4 + 0x918,3);
  }
  local_4c = CONCAT13(uVar1,(undefined3)local_4c);
  iVar8 = BndStrg_CheckConnectionReq
                    (param_1,uVar3,param_3,*(undefined1 *)(param_4 + 0x904),&local_4c);
  return iVar8 != 0;
}

