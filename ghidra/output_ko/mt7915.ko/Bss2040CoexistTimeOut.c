// module: mt7915.ko
// function: Bss2040CoexistTimeOut @ 0x1709c
// size: 204 bytes
//

void Bss2040CoexistTimeOut(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if (2 < DebugLevel) {
    printk("Bss2040CoexistTimeOut(): Recovery to original setting!\n");
  }
  *(byte *)(param_2 + 0x795652) = *(byte *)(param_2 + 0x795652) & 0xfe;
  __memzero(param_2 + 0x7956b4,1);
  *(byte *)(param_2 + 0x795652) = *(byte *)(param_2 + 0x795652) | 2;
  if (*(char *)(param_2 + 0x79564e) != '\0') {
    if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
        [param_2 + 0xda] != '\0') {
      uVar1 = 0;
      do {
        SendBSS2040CoexistMgmtAction(param_2,0,uVar1 & 0xff,0);
        uVar1 = uVar1 + 1;
      } while ((int)uVar1 <
               (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                [param_2 + 0xda]);
      return;
    }
    return;
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("Bss2040CoexistTimeOut(): bBssCoexEnable is FALSE, return directly!\n");
  return;
}

