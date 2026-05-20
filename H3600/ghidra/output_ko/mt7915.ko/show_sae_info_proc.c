// module: mt7915.ko
// function: show_sae_info_proc @ 0x20872c
// size: 560 bytes
//

undefined4 show_sae_info_proc(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  
  iVar1 = hc_get_chip_wtbl_max_num
                    (*(undefined4 *)
                      (*(int *)(
                               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                               + param_1 + 0xcc) + 0xa797a0));
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = os_str_toul(param_2,0,10);
  }
  if ((0 < DebugLevel) &&
     (printk("k iteration varieble: %d, anti clogging th: %d\n",
             "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             [param_1 + 0xc4],
             *(undefined4 *)
              (
              "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              + param_1 + 0xc0)), 0 < DebugLevel)) {
    printk("total ins: %d\n",
           *(undefined4 *)
            (
            "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            + param_1 + 0xb0));
  }
  if (iVar1 != 0) {
    pcVar4 = "pci_sw_int_handler" + param_1;
    iVar5 = 0;
    do {
      cVar3 = pcVar4[0x128];
      if (cVar3 != '\0' || iVar2 == 1) {
        if (0 < DebugLevel) {
          uVar6 = (uint)(byte)pcVar4[0x164];
          uVar7 = (uint)(byte)pcVar4[0x165];
          uVar8 = (uint)(byte)pcVar4[0x166];
          uVar9 = (uint)(byte)pcVar4[0x167];
          uVar10 = (uint)(byte)pcVar4[0x168];
          uVar11 = (uint)(byte)pcVar4[0x169];
          uVar12 = (uint)(byte)pcVar4[0x16a];
          uVar13 = (uint)(byte)pcVar4[0x16b];
          printk("idx:%d, v/r:%d/%d, OM=0x%02x:%02x:%02x:%02x:%02x:%02x, PM=0x%02x:%02x:%02x:%02x:%02x:%02x\n"
                 ,iVar5,cVar3,pcVar4[0x129],pcVar4[0x160],pcVar4[0x161],pcVar4[0x162],pcVar4[0x163],
                 uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13);
          if (0 < DebugLevel) {
            printk("\tstate:%d, group:%d, sync:%d, sc:0x%x, last_peer_sc:0x%x, same_mac_ins=%d, timer_state=%d\n"
                   ,*(undefined4 *)pcVar4,*(undefined2 *)(pcVar4 + 0x2c),(int)pcVar4[0x2e],
                   *(undefined2 *)(pcVar4 + 4),*(undefined2 *)(pcVar4 + 6),
                   *(int *)(pcVar4 + 0x17c) != 0,pcVar4[0x149],uVar6,uVar7,uVar8,uVar9,uVar10,uVar11
                   ,uVar12,uVar13);
          }
          cVar3 = pcVar4[0x128];
        }
        if (((cVar3 != '\0') &&
            (((*(int *)(pcVar4 + 0x180) != 0 ||
              ((0 < DebugLevel &&
               (printk("\t[error]pSaeIns->pParentSaeCfg is NULL\n"), pcVar4[0x128] != '\0')))) &&
             (*(int *)(pcVar4 + 0x174) == 0)))) && (0 < DebugLevel)) {
          printk("\t[error]pSaeIns->psk is NULL\n");
        }
      }
      iVar5 = iVar5 + 1;
      pcVar4 = pcVar4 + 0x188;
    } while (iVar5 != iVar1);
  }
  return 1;
}

