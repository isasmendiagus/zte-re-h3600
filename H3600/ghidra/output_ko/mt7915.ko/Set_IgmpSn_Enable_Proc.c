// module: mt7915.ko
// function: Set_IgmpSn_Enable_Proc @ 0x241470
// size: 284 bytes
//

undefined4 Set_IgmpSn_Enable_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  int iVar6;
  
  iVar6 = *(int *)(*param_1 + 0x3c);
  uVar2 = simple_strtol(param_2,0,10);
  iVar3 = HcGetBandByWdev((char *)((int)param_1 +
                                  (int)(
                                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                       + iVar6 * 0x5834 + 0xe0)));
  iVar1 = DebugLevel;
  (&DAT_0036b914)[(int)param_1 + iVar3] = uVar2 != 0;
  if (2 < iVar1) {
    pcVar5 = "Enable IGMP Snooping";
    if (uVar2 != 1) {
      pcVar5 = "Disable IGMP Snooping";
    }
    printk("%s:: wdev[%d],OMAC[%d]-%s\n","Set_IgmpSn_Enable_Proc",
           (char)param_1[iVar6 * 0x160d + 0xadc95],(char)param_1[iVar6 * 0x160d + 0xadf3a],pcVar5);
  }
  uVar4 = hc_get_asic_cap(param_1[0x29e5e8]);
  if ((uVar4 & 0x400) != 0) {
    CmdMcastCloneEnable(param_1,uVar2 & 0xff,
                        *(undefined1 *)((int)param_1 + iVar6 * 0x5834 + 0x2b7cef),
                        (char)param_1[iVar6 * 0x160d + 0xadf3a]);
  }
  return 1;
}

