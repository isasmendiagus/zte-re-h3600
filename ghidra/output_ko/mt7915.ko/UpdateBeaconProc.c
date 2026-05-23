// module: mt7915.ko
// function: UpdateBeaconProc @ 0xb5a44
// size: 800 bytes
//

undefined4
UpdateBeaconProc(int param_1,char *param_2,undefined4 param_3,undefined4 param_4,char param_5)

{
  char *pcVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  
  iVar3 = HcGetBandByWdev(param_2);
  if (param_2 == (char *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s(): no wdev\n","UpdateBeaconProc");
    return 0;
  }
  uVar4 = *(uint *)(param_1 + (iVar3 + 0xd9e3a) * 4);
  if (uVar4 == 0) {
LAB_000b5b98:
    uVar4 = *(uint *)(param_2 + 0x990);
    if (uVar4 < 3) goto LAB_000b5b4c;
  }
  else {
    iVar5 = (uint)(byte)param_2[0xe] * 0x5834 + param_1;
    uVar6 = (uint)(byte)(&DAT_003678f2)[param_1 + iVar3];
    if ((*(uint *)("Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                  + iVar5 + 0x2c) == uVar6) ||
       ((uVar4 & 1 << (*(uint *)(
                                "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                                + iVar5 + 0x30) & 0xff)) == 0)) goto LAB_000b5b98;
    pcVar1 = param_2 + 0xc;
    param_2 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              + param_1 + uVar6 * 0x5834 + 0xe0;
    iVar3 = param_1 + uVar6 * 0x5834;
    if (2 < DebugLevel) {
      param_5 = '\x01';
      printk("%s(): wdev(%d) is Nontransmitted Bssid, update to BssIdx %d wdev(%d)\n",
             "UpdateBeaconProc",*pcVar1,uVar6,
             "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             [iVar3 + 0xec]);
      goto LAB_000b5b98;
    }
    uVar4 = *(uint *)("======== WATF LV%d\'s MAC Address List ========\n" + iVar3 + 0xc);
    if (uVar4 < 3) {
      return 0;
    }
    param_5 = '\x01';
  }
  iVar3 = *(int *)(param_2 + 0x14);
  if ((iVar3 - 0x10U & 0xffffffef) == 0 || (iVar3 == 4 || iVar3 == 1)) {
    iVar5 = BeaconTransmitRequired(param_1,param_2,param_3);
    iVar3 = DebugLevel;
    if (iVar5 != 0) {
      if ((param_2[0x944] != '\0') &&
         (*(uint *)(*(int *)(param_2 + 0x3fe4) + 0x1c) =
               *(uint *)(*(int *)(param_2 + 0x3fe4) + 0x1c) | 1 << param_2[0xe], 2 < iVar3)) {
        printk("%s, wdev(%d) csa_ap_bitmap = 0x%x\n","UpdateBeaconProc",param_2[0xc]);
      }
      if (param_2[0x988] != '\x02') {
        AsicDisableBeacon(param_1,param_2);
        if (param_5 == '\0') {
          AsicUpdateBeacon(param_1,param_2);
        }
        else {
          uVar2 = MakeBeacon(param_1,param_2,param_3);
          *(undefined2 *)(param_2 + 0x958) = uVar2;
          AsicUpdateBeacon(param_1,param_2);
        }
        AsicEnableBeacon(param_1,param_2);
        return 1;
      }
      if (param_5 != '\0') {
        uVar2 = MakeBeacon(param_1,param_2,param_3);
        *(undefined2 *)(param_2 + 0x958) = uVar2;
        AsicUpdateBeacon(param_1,param_2);
        return 1;
      }
      AsicUpdateBeacon(param_1,param_2);
      return 1;
    }
    if (2 < DebugLevel) {
      printk("%s(): wdev(%d) NO BeaconTransmitRequired\n","UpdateBeaconProc",param_2[0xc]);
    }
    if (param_2[0x988] != '\x02') {
      return 0;
    }
    param_2[0x950] = '\0';
    AsicUpdateBeacon(param_1,param_2);
    return 0;
  }
LAB_000b5b4c:
  if (DebugLevel < 3) {
    return 0;
  }
  printk("%s, wdev(%d) bss not ready (%d) or not required (%d) !!\n","UpdateBeaconProc",param_2[0xc]
         ,uVar4,*(undefined4 *)(param_2 + 0x14));
  return 0;
}

