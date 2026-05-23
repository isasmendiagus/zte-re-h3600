// module: mt7915.ko
// function: rtmp_ap_init @ 0x16944
// size: 416 bytes
//

undefined4 rtmp_ap_init(int param_1)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  
  if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0') {
    uVar3 = 0;
    do {
      iVar2 = param_1 + uVar3 * 0x5834;
      pcVar1 = "!!! Driver is in Monitor Mode now !!!\n" + iVar2 + 0x20;
      pcVar1[0] = '\0';
      pcVar1[1] = '\0';
      pcVar1[2] = '\0';
      pcVar1[3] = '\0';
      pcVar1 = "!!! Driver is in Monitor Mode now !!!\n" + iVar2 + 0x1c;
      pcVar1[0] = '\0';
      pcVar1[1] = '\0';
      pcVar1[2] = '\0';
      pcVar1[3] = '\0';
      os_alloc_mem(param_1,"!!! Driver is in Monitor Mode now !!!\n" + iVar2 + 0x1c,0x900);
      if (*(int *)("!!! Driver is in Monitor Mode now !!!\n" + iVar2 + 0x1c) != 0) {
        __memzero(*(int *)("!!! Driver is in Monitor Mode now !!!\n" + iVar2 + 0x1c),0x900);
      }
      iVar2 = param_1 + uVar3 * 0x5834;
      pcVar1 = "!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" + iVar2;
      pcVar1[0] = '\0';
      pcVar1[1] = '\0';
      pcVar1[2] = '\0';
      pcVar1[3] = '\0';
      pcVar1 = "!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" + iVar2 + 4;
      pcVar1[0] = '\0';
      pcVar1[1] = '\0';
      pcVar1[2] = '\0';
      pcVar1[3] = '\0';
      os_alloc_mem(param_1,"!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" + iVar2 + 4,
                   0x900);
      if (*(int *)("!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" + iVar2 + 4) != 0) {
        __memzero(*(int *)("!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" + iVar2 + 4)
                  ,0x900);
      }
      uVar3 = uVar3 + 1 & 0xff;
    } while (uVar3 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           [param_1 + 0xda]);
  }
  APOneShotSettingInitialize(param_1);
  if (2 < DebugLevel) {
    printk("apstart up %02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(param_1 + 0x794b5b),
           *(undefined1 *)(param_1 + 0x794b5c),*(undefined1 *)(param_1 + 0x794b5d),
           *(undefined1 *)(param_1 + 0x794b5e),*(undefined1 *)(param_1 + 0x794b5f),
           *(undefined1 *)(param_1 + 0x794b60));
  }
  APInitForMain(param_1);
  RtmpOSNetDevAddrSet(*(undefined1 *)(param_1 + 0x286285),*(undefined4 *)(param_1 + 4),
                      param_1 + 0x794b5b,0);
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7615) {
    SetMuraPlatformTypeProc(param_1);
    SetMuraEnableHwSwPatch(param_1);
    return 0;
  }
  return 0;
}

