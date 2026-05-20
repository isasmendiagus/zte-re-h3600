// module: mt7915.ko
// function: Show_APSecurityInfo_Proc @ 0x189f4
// size: 2112 bytes
//

undefined4 Show_APSecurityInfo_Proc(int param_1,int param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  ushort uVar8;
  ushort uVar9;
  int iVar10;
  uint uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  int iVar15;
  char *pcVar16;
  undefined4 *puVar17;
  ushort *puVar18;
  int iVar19;
  char *pcVar20;
  char cVar21;
  uint uVar22;
  char cVar23;
  undefined4 uVar24;
  bool bVar25;
  
  if (param_1 == 0) {
    return 0;
  }
  iVar10 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 != 0) {
    uVar11 = os_str_toul(param_2,0,10);
    uVar11 = uVar11 & 0xff;
    if ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              [param_1 + 0xda] <= uVar11) {
      if (DebugLevel < 1) {
        return 1;
      }
      printk("Invalid apidx\n");
      return 1;
    }
    iVar15 = uVar11 * 0x5834;
    iVar10 = param_1 + iVar15;
    uVar4 = *(ushort *)("======== WATF LV%d\'s MAC Address List ========\n" + iVar10 + 0x1c);
    if (DebugLevel < 1) {
      if ((*(uint *)(
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + iVar10 + 0x254) & 0xe) != 0) {
LAB_00018e00:
        iVar10 = param_1 + (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                       [param_1 + uVar11 * 0x5834 + 600] * 0x51 + uVar11 * 0x5834;
        hex_dump_with_lvl("hex key",
                          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          + iVar10 + 0x110,
                          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          [iVar10 + 0x160],1);
        goto LAB_00018e5c;
      }
      if ((*(uint *)(
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + iVar10 + 0x254) & 0x1f0) == 0) {
        iVar10 = param_1 + iVar15 + 0x10c;
        pcVar20 = "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                  + iVar10 + 4;
        if (pcVar20 ==
            *(char **)(
                      "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                      + iVar10 + 4)) {
          return 1;
        }
        goto LAB_00018e80;
      }
LAB_00018ad0:
      iVar10 = param_1 + uVar11 * 0x5834 + 0x10c;
      pcVar20 = "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                + iVar10 + 4;
      if (pcVar20 ==
          *(char **)(
                    "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                    + iVar10 + 4)) {
        return 1;
      }
      pcVar16 = *(char **)(
                          "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                          + param_1 + uVar11 * 0x5834 + 0x110);
      if (pcVar20 == pcVar16) {
        return 1;
      }
    }
    else {
      uVar12 = GetAuthModeStr(*(undefined4 *)
                               (
                               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                               + iVar10 + 0x10c));
      uVar13 = GetEncryModeStr(*(undefined4 *)
                                (
                                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                + iVar10 + 0x254));
      uVar14 = GetEncryModeStr(*(undefined4 *)
                                (
                                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                + iVar10 + 0x334));
      uVar22 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           [iVar10 + 0x338];
      uVar24 = *(undefined4 *)
                (&DAT_0028f7c0 + (uint)*(byte *)(param_1 + (uint)uVar4 * 0x620 + 0x2f762) * 4);
      printk("BSS(%d), WCID(%d), AuthMode(%s), PairwiseCipher(%s)\nGroupCipher(%s), GroupKeyId(%d), PortSecured(%s)\n"
             ,uVar11,(uint)uVar4,uVar12,uVar13,uVar14,uVar22,uVar24);
      if ((*(uint *)(
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + iVar10 + 0x254) & 0xe) != 0) {
        if (0 < DebugLevel) {
          iVar15 = param_1 + (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                         [iVar10 + 600] * 0x51 + iVar15;
          printk("keyid(%d), Key = %s keylen = %d\n",
                 (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                             [iVar10 + 600],
                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + iVar15 + 0x110,
                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 [iVar15 + 0x160],uVar13,uVar14,uVar22,uVar24);
        }
        goto LAB_00018e00;
      }
      if ((*(uint *)(
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + iVar10 + 0x254) & 0x1f0) != 0) {
        if (DebugLevel < 1) goto LAB_00018ad0;
        printk("Key = %s\n",
               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
               + param_1 + iVar15 + 0x259,
               *(uint *)(
                        "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + iVar10 + 0x254),DebugLevel,uVar13,uVar14,uVar22,uVar24);
      }
LAB_00018e5c:
      iVar10 = uVar11 * 0x5834 + param_1;
      pcVar20 = "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                + iVar10 + 0x110;
      if (pcVar20 ==
          *(char **)(
                    "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                    + iVar10 + 0x110)) goto LAB_00018b68;
LAB_00018e80:
      pcVar16 = *(char **)(
                          "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                          + uVar11 * 0x5834 + param_1 + 0x110);
      if (pcVar16 == pcVar20) goto LAB_00018b68;
    }
    cVar21 = '\0';
    do {
      cVar23 = cVar21;
      if (0 < DebugLevel) {
        cVar23 = cVar21 + '\x01';
        printk("%d pwdid = %s, pwd = %s\n",cVar21,pcVar16 + 0x49,pcVar16 + 8);
      }
      hex_dump_with_lvl("pwdid",pcVar16 + 0x49,0x28,1);
      hex_dump_with_lvl(&_LC12,pcVar16 + 8,0x40,1);
      pcVar16 = *(char **)pcVar16;
      cVar21 = cVar23;
    } while (pcVar20 != pcVar16);
LAB_00018b68:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("PWDID Required = %d\n",
           "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
           [uVar11 * 0x5834 + param_1 + 0x10c]);
    return 1;
  }
  if ((((DebugLevel < 1) || (printk("Security Infomation: AP\n"), DebugLevel < 1)) ||
      (printk("BSS\tWCID\tAuthMode\tPairwiseCipher\tGroupCipher\tGroupKeyId\tPortSecured"),
      DebugLevel < 1)) || (printk(&_LC16), DebugLevel < 1)) {
    iVar15 = DebugLevel;
    if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
        [param_1 + 0xda] == '\0') goto LAB_00018c28;
LAB_00018bc0:
    uVar11 = 0;
    iVar15 = DebugLevel;
    do {
      iVar19 = uVar11 * 0x5834 + param_1;
      uVar4 = *(ushort *)("======== WATF LV%d\'s MAC Address List ========\n" + iVar19 + 0x1c);
      if (0 < iVar15) {
        uVar12 = GetAuthModeStr(*(undefined4 *)
                                 (
                                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                 + iVar19 + 0x10c));
        uVar13 = GetEncryModeStr(*(undefined4 *)
                                  (
                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                  + iVar19 + 0x254));
        uVar14 = GetEncryModeStr(*(undefined4 *)
                                  (
                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                  + iVar19 + 0x334));
        printk(" %d\t%d\t%s\t\t%s\t\t%s\t\t%d\t\t%s",uVar11,(uint)uVar4,uVar12,uVar13,uVar14,
               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
               [iVar19 + 0x338],
               *(undefined4 *)
                (&DAT_0028f7c0 + (uint)*(byte *)(param_1 + (uint)uVar4 * 0x620 + 0x2f762) * 4));
        iVar15 = DebugLevel;
        if ((0 < DebugLevel) &&
           (printk(&_LC19,"Group%d airtime token: max %d(0x%08X), min %d(0x%08X)\n"[iVar19 + 10]),
           iVar15 = DebugLevel, 0 < DebugLevel)) {
          printk(&_LC17);
          iVar15 = DebugLevel;
        }
      }
      uVar11 = uVar11 + 1 & 0xffff;
    } while (uVar11 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda]);
  }
  else {
    printk(&_LC17);
    iVar15 = DebugLevel;
    if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
        [param_1 + 0xda] != '\0') goto LAB_00018bc0;
  }
  if (((0 < iVar15) && (printk(&_LC17), iVar15 = DebugLevel, 0 < DebugLevel)) &&
     (printk("Security Infomation: AP Client\n"), iVar15 = DebugLevel, 0 < DebugLevel)) {
    printk("BSS\tWCID\tAuthMode\tPairwiseCipher\tPortSecured\n");
    iVar15 = DebugLevel;
  }
LAB_00018c28:
  puVar17 = (undefined4 *)(&DAT_0036dccc + param_1);
  iVar19 = 0;
  do {
    uVar4 = *(ushort *)(puVar17 + 0x20b);
    if ((*(char *)((int)puVar17 + 0x2131c1) == '\x01') && (0 < iVar15)) {
      uVar12 = GetAuthModeStr(puVar17[-0x52]);
      uVar13 = GetEncryModeStr(*puVar17);
      printk(" %d\t%d\t%s\t\t%s\t\t%s\n",iVar19,(uint)uVar4,uVar12,uVar13,
             *(undefined4 *)
              (&DAT_0028f7c0 + (uint)*(byte *)(param_1 + (uint)uVar4 * 0x620 + 0x2f762) * 4));
      iVar15 = DebugLevel;
    }
    bVar25 = iVar19 != 1;
    iVar19 = 1;
    puVar17 = puVar17 + 0x84dec;
  } while (bVar25);
  if (((0 < iVar15) && (printk(&_LC17), 0 < DebugLevel)) &&
     (printk("Security Infomation: STA\n"), 0 < DebugLevel)) {
    printk("BSS\t\t\tAID\tWCID\tAuthMode\tPairwiseCipher\tPortSecured\n");
  }
  if (iVar10 != 0) {
    puVar18 = (ushort *)(param_1 + 0xa1e02);
    do {
      uVar4 = *puVar18;
      if (((*(int *)(puVar18 + -0x71) == 0x20001) && (*(int *)(puVar18 + 0xd) == 2)) &&
         (0 < DebugLevel)) {
        uVar7 = puVar18[5];
        uVar1 = *(undefined1 *)((int)puVar18 + 0xb);
        uVar8 = puVar18[6];
        uVar2 = *(undefined1 *)((int)puVar18 + 0xd);
        uVar5 = puVar18[-1];
        uVar6 = puVar18[0xb];
        uVar3 = *(undefined1 *)((int)puVar18 + 0xf);
        uVar9 = puVar18[7];
        uVar12 = GetAuthModeStr(*(undefined4 *)(puVar18 + 0x4d));
        uVar13 = GetEncryModeStr(*(undefined4 *)(puVar18 + 0xf1));
        printk("%02x:%02x:%02x:%02x:%02x:%02x\t%d\t%d\t%s\t\t%s\t\t%s\n",(char)uVar7,uVar1,
               (char)uVar8,uVar2,(char)uVar9,uVar3,uVar6,uVar5,uVar12,uVar13,
               *(undefined4 *)
                (&DAT_0028f7c0 + (uint)*(byte *)(param_1 + (uint)uVar4 * 0x620 + 0x2f762) * 4));
      }
      puVar18 = puVar18 + 0xa60;
    } while (puVar18 != (ushort *)((iVar10 - 1U & 0xffff) * 0x14c0 + param_1 + 0xa32c2));
  }
  return 1;
}

