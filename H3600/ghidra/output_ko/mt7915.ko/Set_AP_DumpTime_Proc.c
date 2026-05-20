// module: mt7915.ko
// function: Set_AP_DumpTime_Proc @ 0x338ec
// size: 460 bytes
//

undefined4 Set_AP_DumpTime_Proc(int param_1)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  undefined4 uVar6;
  
  if ((2 < DebugLevel) && (printk("\n\t%-10s\t%-10s\n","PreTBTTTime","TBTTTime"), 2 < DebugLevel)) {
    printk("%-10lu\t%-10lu\n",*(undefined4 *)(param_1 + 0xa78a14),
           *(undefined4 *)(param_1 + 0xa78a10));
  }
  if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0') {
    pcVar3 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             + param_1 + 0xe0;
    pcVar4 = "RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + 0xc;
    iVar5 = 0;
    do {
      iVar1 = BeaconTransmitRequired(param_1,pcVar3,1);
      if (iVar1 != 0) {
        if (2 < DebugLevel) {
          uVar6 = *(undefined4 *)(pcVar4 + 0x2c);
          printk("\n%s:%d\tBcn_State:%d\t%-10s: %d\n","Apidx",iVar5,*(undefined4 *)(pcVar3 + 0x94c),
                 "recover",uVar6);
          if (2 < DebugLevel) {
            printk("\t%-10s\t%-10s\t%-10s\t%-10s\n","WriteBcnRing","BcnDmaDone","TXS_TSF","TXS_SN",
                   uVar6);
          }
        }
        iVar1 = 0;
        pcVar2 = pcVar4;
        do {
          if (2 < DebugLevel) {
            printk("Idx[%d]:\t%-10lu\t%-10lu\t%-10lu\t%-10lu\n",iVar1,*(undefined4 *)pcVar2,
                   *(undefined4 *)(pcVar2 + 0x14),*(undefined4 *)(pcVar2 + 0x30),
                   *(undefined4 *)(pcVar2 + 0x44));
          }
          iVar1 = iVar1 + 1;
          pcVar2 = pcVar2 + 4;
        } while (iVar1 != 5);
      }
      iVar5 = iVar5 + 1;
      pcVar3 = pcVar3 + 0x5834;
      pcVar4 = pcVar4 + 0x5834;
    } while (iVar5 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                      [param_1 + 0xda]);
  }
  return 1;
}

