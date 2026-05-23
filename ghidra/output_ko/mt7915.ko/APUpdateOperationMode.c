// module: mt7915.ko
// function: APUpdateOperationMode @ 0x152a8
// size: 580 bytes
//

void APUpdateOperationMode(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  if (param_2 == 0) {
    return;
  }
  iVar2 = wlan_operate_get_addht(param_2);
  iVar3 = HcGetBandByWdev(param_2);
  if (*(uint *)(param_1 + 0x7960e8) == 0 ||
      *(int *)(&DAT_0036b8a8 + param_1) + 500U <= *(uint *)(param_1 + 0x7960e8)) {
    iVar5 = 0;
    if ((*(char *)(param_1 + 0x285945) == '\0') ||
       (iVar4 = wlan_config_get_ht_bw(param_2), iVar4 != 1)) {
      iVar5 = 0;
      uVar7 = 0;
      uVar6 = 0;
    }
    else {
      uVar7 = 2;
      uVar6 = 4;
    }
  }
  else {
    iVar5 = 1;
    uVar7 = 1;
    uVar6 = 2;
  }
  if (*(char *)(param_1 + 0x285942) != '\0') {
    uVar7 = 3;
    uVar6 = 8;
  }
  if (3 < DebugLevel) {
    printk(" --%s:\n OperationMode: %d, bNonGFExist: %d\n","APUpdateOperationMode",
           *(byte *)(iVar2 + 2) & 3,iVar5);
  }
  iVar3 = param_1 + iVar3;
  if (((*(byte *)(iVar2 + 2) & 3) != uVar7) ||
     ((uint)*(byte *)(iVar3 + 0x285943) != ((uint)*(byte *)(iVar2 + 2) << 0x1d) >> 0x1f)) {
    bVar1 = *(byte *)(iVar2 + 2);
    *(byte *)(iVar2 + 2) = bVar1 & 0xfc | (byte)uVar7;
    *(byte *)(iVar2 + 2) = bVar1 & 0xf8 | (byte)uVar7 | (*(byte *)(iVar3 + 0x285943) & 1) << 2;
    UpdateBeaconHandler(param_1,param_2,2);
  }
  if ((iVar5 != 0) || (*(char *)(iVar3 + 0x285943) != '\0')) {
    uVar6 = uVar6 | 0x80;
  }
  iVar2 = nonerp_protection("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            + (uint)*(byte *)(param_2 + 0xe) * 0x5834 + param_1 + 0xe0);
  if (iVar2 != 0) {
    uVar6 = uVar6 | 0x20;
  }
  if ((((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7615) &&
      ((byte)"Get_RBIST_IQ_Data_Proc"[param_1 + 0x10] < 0x10)) &&
     (*(char *)(param_1 + 0x79504d) != '\0' && uVar7 == 0)) {
    uVar6 = uVar6 | 4;
  }
  iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if ((iVar2 == 2) && ((*(uint *)(param_2 + 0x8dc) & uVar6) != uVar6)) {
    *(uint *)(param_2 + 0x8dc) = uVar6;
    HW_SET_PROTECT(param_1,param_2,0,0,0);
    return;
  }
  return;
}

