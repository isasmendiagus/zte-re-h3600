// module: mt7915.ko
// function: rtmp_read_vow_parms_from_file @ 0xf072c
// size: 6196 bytes
//

void rtmp_read_vow_parms_from_file(int param_1,char *param_2,undefined4 param_3)

{
  undefined1 uVar1;
  char cVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  char *__s;
  size_t sVar6;
  undefined2 *puVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  uint uVar10;
  int iVar11;
  char *local_30;
  char *local_2c [2];
  
  iVar4 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (3 < DebugLevel) {
    printk("%s: begin -->\n","rtmp_read_vow_parms_from_file");
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_BW_Ctrl",param_2,0x80,param_3,1);
  if ((iVar5 != 0) && (*param_2 != '\0')) {
    iVar11 = os_str_tol(param_2,0,10);
    iVar5 = DebugLevel;
    *(bool *)(param_1 + 0xa7a2e8) = iVar11 != 0;
    if (3 < iVar5) {
      printk("VOW_BW_Ctrl --> %d\n");
    }
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Airtime_Fairness_En",param_2,0x80,param_3,1);
  if ((iVar5 != 0) && (*param_2 != '\0')) {
    iVar11 = os_str_tol(param_2,0,10);
    iVar5 = DebugLevel;
    *(bool *)(param_1 + 0xa7a2ea) = iVar11 != 0;
    if (3 < iVar5) {
      printk("VOW_Airtime_Fairness_En --> %d\n");
    }
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Airtime_Ctrl_En",param_2,0x80,param_3,1);
  if ((((iVar5 != 0) && (*param_2 != '\0')) && (iVar5 = rstrtok(param_2,&_LC6), iVar5 != 0)) &&
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0')) {
    uVar10 = 0;
    do {
      iVar11 = os_str_tol(iVar5,0,10);
      iVar5 = DebugLevel;
      *(bool *)(param_1 + uVar10 * 0x1c + 0xa79842) = iVar11 != 0;
      if (3 < iVar5) {
        printk("BSS(%d) VOW_Airtime_Ctrl_En --> %d\n",uVar10);
      }
      iVar5 = rstrtok(0,&_LC6);
      uVar10 = uVar10 + 1 & 0xffff;
    } while ((iVar5 != 0) &&
            (uVar10 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda]));
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Rate_Ctrl_En",param_2,0x80,param_3,1);
  if (((iVar5 != 0) && ((*param_2 != '\0' && (iVar5 = rstrtok(param_2,&_LC6), iVar5 != 0)))) &&
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0')) {
    uVar10 = 0;
    do {
      iVar11 = os_str_tol(iVar5,0,10);
      iVar5 = DebugLevel;
      *(bool *)(param_1 + uVar10 * 0x1c + 0xa79841) = iVar11 != 0;
      if (3 < iVar5) {
        printk("BSS(%d) VOW_Rate_Ctrl_En --> %d\n",uVar10);
      }
      iVar5 = rstrtok(0,&_LC6);
      uVar10 = uVar10 + 1 & 0xffff;
    } while ((iVar5 != 0) &&
            (uVar10 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda]));
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_RX_En",param_2,0x80,param_3,1);
  if ((iVar5 != 0) && (*param_2 != '\0')) {
    iVar11 = os_str_tol(param_2,0,10);
    iVar5 = DebugLevel;
    *(bool *)(param_1 + 0xa79826) = iVar11 != 0;
    if (3 < iVar5) {
      printk("VOW_RX_En --> %d\n");
    }
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Group_Min_Rate",param_2,0x80,param_3,1);
  if ((((iVar5 != 0) && (*param_2 != '\0')) && (iVar5 = rstrtok(param_2,&_LC6), iVar5 != 0)) &&
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0')) {
    uVar10 = 0;
    do {
      uVar3 = os_str_tol(iVar5,0,10);
      iVar11 = param_1 + uVar10 * 0x1c;
      puVar7 = (undefined2 *)(iVar11 + 0xa79828);
      *puVar7 = uVar3;
      uVar3 = vow_convert_rate_token(param_1,0,uVar10 & 0xff);
      iVar5 = DebugLevel;
      *(undefined2 *)(iVar11 + 0xa79838) = uVar3;
      if (3 < iVar5) {
        printk("BSS(%d) VOW_Group_Min_Rate --> %d\n",uVar10,*puVar7);
      }
      iVar5 = rstrtok(0,&_LC6);
      uVar10 = uVar10 + 1 & 0xffff;
    } while ((iVar5 != 0) &&
            (uVar10 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda]));
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Group_Max_Rate",param_2,0x80,param_3,1);
  if (((iVar5 != 0) && ((*param_2 != '\0' && (iVar5 = rstrtok(param_2,&_LC6), iVar5 != 0)))) &&
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0')) {
    uVar10 = 0;
    do {
      uVar3 = os_str_tol(iVar5,0,10);
      iVar11 = param_1 + uVar10 * 0x1c;
      *(undefined2 *)(iVar11 + 0xa7982a) = uVar3;
      uVar3 = vow_convert_rate_token(param_1,1,uVar10 & 0xff);
      iVar5 = DebugLevel;
      *(undefined2 *)(iVar11 + 0xa7983a) = uVar3;
      if (3 < iVar5) {
        printk("BSS(%d) VOW_Group_Max_Rate --> %d\n",uVar10,*(undefined2 *)(iVar11 + 0xa7982a));
      }
      iVar5 = rstrtok(0,&_LC6);
      uVar10 = uVar10 + 1 & 0xffff;
    } while ((iVar5 != 0) &&
            (uVar10 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda]));
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Group_Min_Ratio",param_2,0x80,param_3,1);
  if ((iVar5 != 0) &&
     (((*param_2 != '\0' && (iVar5 = rstrtok(param_2,&_LC6), iVar5 != 0)) &&
      ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
       [param_1 + 0xda] != '\0')))) {
    uVar10 = 0;
    do {
      uVar1 = os_str_tol(iVar5,0,10);
      iVar11 = param_1 + uVar10 * 0x1c;
      *(undefined1 *)(iVar11 + 0xa7982c) = uVar1;
      uVar3 = vow_convert_airtime_token(param_1,0,uVar10 & 0xff);
      iVar5 = DebugLevel;
      *(undefined2 *)(iVar11 + 0xa7983c) = uVar3;
      if (3 < iVar5) {
        printk("BSS(%d) VOW_Group_Min_Ratio --> %d\n",uVar10,*(undefined1 *)(iVar11 + 0xa7982c));
      }
      iVar5 = rstrtok(0,&_LC6);
      uVar10 = uVar10 + 1 & 0xffff;
    } while ((iVar5 != 0) &&
            (uVar10 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda]));
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Group_Max_Ratio",param_2,0x80,param_3,1);
  if (((iVar5 != 0) && ((*param_2 != '\0' && (iVar5 = rstrtok(param_2,&_LC6), iVar5 != 0)))) &&
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0')) {
    uVar10 = 0;
    do {
      uVar1 = os_str_tol(iVar5,0,10);
      iVar11 = param_1 + uVar10 * 0x1c;
      *(undefined1 *)(iVar11 + 0xa7982d) = uVar1;
      uVar3 = vow_convert_airtime_token(param_1,1,uVar10 & 0xff);
      iVar5 = DebugLevel;
      *(undefined2 *)(iVar11 + 0xa7983e) = uVar3;
      if (3 < iVar5) {
        printk("BSS(%d) VOW_Group_Max_Ratio --> %d\n",uVar10,*(undefined1 *)(iVar11 + 0xa7982d));
      }
      iVar5 = rstrtok(0,&_LC6);
      uVar10 = uVar10 + 1 & 0xffff;
    } while ((iVar5 != 0) &&
            (uVar10 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda]));
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Refill_Period",param_2,0x80,param_3,1);
  if ((iVar5 != 0) && (*param_2 != '\0')) {
    uVar1 = os_str_tol(param_2,0,10);
    iVar5 = DebugLevel;
    *(undefined1 *)(param_1 + 0xa7a2ee) = uVar1;
    if (3 < iVar5) {
      printk("VOW_Refill_Period --> %d\n",uVar1);
    }
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Group_Min_Rate_Bucket_Size",param_2,0x80,param_3,1);
  if ((((iVar5 != 0) && (*param_2 != '\0')) && (iVar5 = rstrtok(param_2,&_LC6), iVar5 != 0)) &&
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0')) {
    uVar10 = 0;
    do {
      uVar3 = os_str_tol(iVar5,0,10);
      iVar5 = DebugLevel;
      *(undefined2 *)(param_1 + uVar10 * 0x1c + 0xa7982e) = uVar3;
      if (3 < iVar5) {
        printk("BSS(%d) VOW_Group_Min_Rate_Bucket_Size --> %d\n",uVar10,uVar3);
      }
      iVar5 = rstrtok(0,&_LC6);
      uVar10 = uVar10 + 1 & 0xffff;
    } while ((iVar5 != 0) &&
            (uVar10 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda]));
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Group_Max_Rate_Bucket_Size",param_2,0x80,param_3,1);
  if (((iVar5 != 0) && ((*param_2 != '\0' && (iVar5 = rstrtok(param_2,&_LC6), iVar5 != 0)))) &&
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0')) {
    uVar10 = 0;
    do {
      uVar3 = os_str_tol(iVar5,0,10);
      iVar5 = DebugLevel;
      *(undefined2 *)(param_1 + uVar10 * 0x1c + 0xa79830) = uVar3;
      if (3 < iVar5) {
        printk("BSS(%d) VOW_Group_Max_Rate_Bucket_Size --> %d\n",uVar10,uVar3);
      }
      iVar5 = rstrtok(0,&_LC6);
      uVar10 = uVar10 + 1 & 0xffff;
    } while ((iVar5 != 0) &&
            (uVar10 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda]));
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Group_Min_Airtime_Bucket_Size",param_2,0x80,param_3,1);
  if ((iVar5 != 0) &&
     (((*param_2 != '\0' && (iVar5 = rstrtok(param_2,&_LC6), iVar5 != 0)) &&
      ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
       [param_1 + 0xda] != '\0')))) {
    uVar10 = 0;
    do {
      uVar1 = os_str_tol(iVar5,0,10);
      iVar5 = DebugLevel;
      *(undefined1 *)(param_1 + uVar10 * 0x1c + 0xa79834) = uVar1;
      if (3 < iVar5) {
        printk("BSS(%d) VOW_Group_Min_Airtime_Bucket_Size --> %d\n",uVar10,uVar1);
      }
      iVar5 = rstrtok(0,&_LC6);
      uVar10 = uVar10 + 1 & 0xffff;
    } while ((iVar5 != 0) &&
            (uVar10 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda]));
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Group_Max_Airtime_Bucket_Size",param_2,0x80,param_3,1);
  if (((iVar5 != 0) && ((*param_2 != '\0' && (iVar5 = rstrtok(param_2,&_LC6), iVar5 != 0)))) &&
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0')) {
    uVar10 = 0;
    do {
      uVar1 = os_str_tol(iVar5,0,10);
      iVar5 = DebugLevel;
      *(undefined1 *)(param_1 + uVar10 * 0x1c + 0xa79835) = uVar1;
      if (3 < iVar5) {
        printk("BSS(%d) VOW_Group_Max_Airtime_Bucket_Size --> %d\n",uVar10,uVar1);
      }
      iVar5 = rstrtok(0,&_LC6);
      uVar10 = uVar10 + 1 & 0xffff;
    } while ((iVar5 != 0) &&
            (uVar10 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda]));
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Group_Backlog",param_2,0x80,param_3,1);
  if ((iVar5 != 0) &&
     (((*param_2 != '\0' && (iVar5 = rstrtok(param_2,&_LC6), iVar5 != 0)) &&
      ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
       [param_1 + 0xda] != '\0')))) {
    uVar10 = 0;
    do {
      uVar3 = os_str_tol(iVar5,0,10);
      iVar5 = DebugLevel;
      *(undefined2 *)(param_1 + uVar10 * 0x1c + 0xa79832) = uVar3;
      if (3 < iVar5) {
        printk("BSS(%d) VOW_Group_Backlog --> %d\n",uVar10,uVar3);
      }
      iVar5 = rstrtok(0,&_LC6);
      uVar10 = uVar10 + 1 & 0xffff;
    } while ((iVar5 != 0) &&
            (uVar10 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda]));
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Group_Max_Wait_Time",param_2,0x80,param_3,1);
  if (((iVar5 != 0) && ((*param_2 != '\0' && (iVar5 = rstrtok(param_2,&_LC6), iVar5 != 0)))) &&
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0')) {
    uVar10 = 0;
    do {
      uVar1 = os_str_tol(iVar5,0,10);
      iVar5 = DebugLevel;
      *(undefined1 *)(param_1 + uVar10 * 0x1c + 0xa79836) = uVar1;
      if (3 < iVar5) {
        printk("BSS(%d) VOW_Group_Max_Wait_Time --> %d\n",uVar10,uVar1);
      }
      iVar5 = rstrtok(0,&_LC6);
      uVar10 = uVar10 + 1 & 0xffff;
    } while ((iVar5 != 0) &&
            (uVar10 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda]));
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Group_DWRR_Quantum",param_2,0x80,param_3,1);
  if ((iVar5 != 0) &&
     (((*param_2 != '\0' && (iVar5 = rstrtok(param_2,&_LC6), iVar5 != 0)) &&
      ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
       [param_1 + 0xda] != '\0')))) {
    uVar10 = 0;
    do {
      uVar1 = os_str_tol(iVar5,0,10);
      iVar5 = DebugLevel;
      *(undefined1 *)(param_1 + uVar10 * 0x1c + 0xa79837) = uVar1;
      if (3 < iVar5) {
        printk("BSS(%d) VOW_Group_DWRR_Quantum --> %d\n",uVar10,uVar1);
      }
      iVar5 = rstrtok(0,&_LC6);
      uVar10 = uVar10 + 1 & 0xffff;
    } while ((iVar5 != 0) &&
            (uVar10 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda]));
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Sta_VO_DWRR_Quantum",param_2,0x80,param_3,1);
  if ((iVar5 != 0) && (*param_2 != '\0')) {
    if (iVar4 != 0) {
      puVar8 = (undefined1 *)(param_1 + 0xa799eb);
      do {
        uVar1 = os_str_tol(param_2,0,10);
        puVar9 = puVar8 + 8;
        *puVar8 = uVar1;
        puVar8 = puVar9;
      } while (puVar9 != (undefined1 *)(param_1 + (iVar4 - 1U & 0xffff) * 8 + 0xa799f3));
    }
    if (3 < DebugLevel) {
      uVar1 = os_str_tol(param_2,0,10);
      printk("VOW_Sta_VO_DWRR_Quantum --> %d\n",uVar1);
    }
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Sta_VI_DWRR_Quantum",param_2,0x80,param_3,1);
  if ((iVar5 != 0) && (*param_2 != '\0')) {
    if (iVar4 != 0) {
      puVar8 = (undefined1 *)(param_1 + 0xa799ea);
      do {
        uVar1 = os_str_tol(param_2,0,10);
        puVar9 = puVar8 + 8;
        *puVar8 = uVar1;
        puVar8 = puVar9;
      } while (puVar9 != (undefined1 *)(param_1 + (iVar4 - 1U & 0xffff) * 8 + 0xa799f2));
    }
    if (3 < DebugLevel) {
      uVar1 = os_str_tol(param_2,0,10);
      printk("VOW_Sta_VI_DWRR_Quantum --> %d\n",uVar1);
    }
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Sta_BE_DWRR_Quantum",param_2,0x80,param_3,1);
  if ((iVar5 != 0) && (*param_2 != '\0')) {
    if (iVar4 != 0) {
      puVar8 = (undefined1 *)(param_1 + 0xa799e9);
      do {
        uVar1 = os_str_tol(param_2,0,10);
        puVar9 = puVar8 + 8;
        *puVar8 = uVar1;
        puVar8 = puVar9;
      } while (puVar9 != (undefined1 *)(param_1 + (iVar4 - 1U & 0xffff) * 8 + 0xa799f1));
    }
    if (3 < DebugLevel) {
      uVar1 = os_str_tol(param_2,0,10);
      printk("VOW_Sta_BE_DWRR_Quantum --> %d\n",uVar1);
    }
  }
  __memzero(param_2,0x800);
  iVar5 = RTMPGetKeyParameter("VOW_Sta_BK_DWRR_Quantum",param_2,0x80,param_3,1);
  if ((iVar5 != 0) && (*param_2 != '\0')) {
    if (iVar4 != 0) {
      puVar8 = (undefined1 *)(param_1 + 0xa799e8);
      do {
        uVar1 = os_str_tol(param_2,0,10);
        puVar9 = puVar8 + 8;
        *puVar8 = uVar1;
        puVar8 = puVar9;
      } while (puVar9 != (undefined1 *)(param_1 + ((iVar4 - 1U & 0xffff) + 0x14f33e) * 8));
    }
    if (3 < DebugLevel) {
      uVar1 = os_str_tol(param_2,0,10);
      printk("VOW_Sta_BK_DWRR_Quantum --> %d\n",uVar1);
    }
  }
  __memzero(param_2,0x800);
  iVar4 = RTMPGetKeyParameter("VOW_WMM_Search_Rule_Band0",param_2,0x80,param_3,1);
  if ((iVar4 != 0) && (*param_2 != '\0')) {
    iVar5 = os_str_tol(param_2,0,10);
    iVar4 = DebugLevel;
    *(bool *)(param_1 + 0xa7a2ec) = iVar5 != 0;
    if (3 < iVar4) {
      printk("VOW_WMM_Search_Rule_Band0 --> %d\n");
    }
  }
  __memzero(param_2,0x800);
  iVar4 = RTMPGetKeyParameter("VOW_WMM_Search_Rule_Band1",param_2,0x80,param_3,1);
  if ((iVar4 != 0) && (*param_2 != '\0')) {
    iVar5 = os_str_tol(param_2,0,10);
    iVar4 = DebugLevel;
    *(bool *)(param_1 + 0xa7a2ed) = iVar5 != 0;
    if (3 < iVar4) {
      printk("VOW_WMM_Search_Rule_Band1 --> %d\n");
    }
  }
  __memzero(param_2,0x800);
  iVar4 = RTMPGetKeyParameter("VOW_Sta_DWRR_Max_Wait_Time",param_2,0x80,param_3,1);
  if ((iVar4 != 0) && (*param_2 != '\0')) {
    uVar1 = os_str_tol(param_2,0,10);
    iVar4 = DebugLevel;
    *(undefined1 *)(param_1 + 0xa7a2f2) = uVar1;
    if (3 < iVar4) {
      printk("VOW_Sta_DWRR_Max_Wait_Time --> %d\n",uVar1);
    }
  }
  __memzero(param_2,0x800);
  iVar4 = RTMPGetKeyParameter("VOW_Group_DWRR_Max_Wait_Time",param_2,0x80,param_3,1);
  if ((iVar4 != 0) && (*param_2 != '\0')) {
    uVar1 = os_str_tol(param_2,0,10);
    iVar4 = DebugLevel;
    *(undefined1 *)(param_1 + 0xa7a2f3) = uVar1;
    if (3 < iVar4) {
      printk("VOW_Group_DWRR_Max_Wait_Time --> %d\n",uVar1);
    }
  }
  __memzero(param_2,0x800);
  iVar4 = RTMPGetKeyParameter("VOW_WATF_Enable",param_2,0x800,param_3,1);
  if ((iVar4 == 0) || (*param_2 == '\0')) {
LAB_000f0f64:
    cVar2 = *(char *)(param_1 + 0xa7a32c);
  }
  else {
    cVar2 = os_str_tol(param_2,0,10);
    iVar4 = DebugLevel;
    *(char *)(param_1 + 0xa7a32c) = cVar2;
    if (3 < iVar4) {
      printk("VOW_WATF_Enable --> %d\n");
      goto LAB_000f0f64;
    }
  }
  if (cVar2 == '\0') goto LAB_000f0f70;
  __memzero(param_2,0x800);
  iVar4 = RTMPGetKeyParameter("VOW_WATF_Q_LV0",param_2,0x800,param_3,1);
  if ((iVar4 == 0) || (*param_2 == '\0')) {
    *(undefined1 *)(param_1 + 0xa7a32d) = 4;
  }
  else {
    uVar1 = os_str_tol(param_2,0,10);
    iVar4 = DebugLevel;
    *(undefined1 *)(param_1 + 0xa7a32d) = uVar1;
    *(undefined1 *)(param_1 + 0xa7a2f4) = uVar1;
    if (3 < iVar4) {
      printk("VOW_WATF_Q_LV0 --> %d\n");
    }
  }
  __memzero(param_2,0x800);
  iVar4 = RTMPGetKeyParameter("VOW_WATF_Q_LV1",param_2,0x800,param_3,1);
  if ((iVar4 == 0) || (*param_2 == '\0')) {
    *(undefined1 *)(param_1 + 0xa7a32e) = 8;
  }
  else {
    uVar1 = os_str_tol(param_2,0,10);
    iVar4 = DebugLevel;
    *(undefined1 *)(param_1 + 0xa7a32e) = uVar1;
    *(undefined1 *)(param_1 + 0xa7a2f5) = uVar1;
    if (3 < iVar4) {
      printk("VOW_WATF_Q_LV1 --> %d\n");
    }
  }
  __memzero(param_2,0x800);
  iVar4 = RTMPGetKeyParameter("VOW_WATF_Q_LV2",param_2,0x800,param_3,1);
  if ((iVar4 == 0) || (*param_2 == '\0')) {
    *(undefined1 *)(param_1 + 0xa7a32f) = 0xc;
  }
  else {
    uVar1 = os_str_tol(param_2,0,10);
    iVar4 = DebugLevel;
    *(undefined1 *)(param_1 + 0xa7a32f) = uVar1;
    *(undefined1 *)(param_1 + 0xa7a2f6) = uVar1;
    if (3 < iVar4) {
      printk("VOW_WATF_Q_LV2 --> %d\n");
    }
  }
  __memzero(param_2,0x800);
  iVar4 = RTMPGetKeyParameter("VOW_WATF_Q_LV3",param_2,0x800,param_3,1);
  if ((iVar4 == 0) || (*param_2 == '\0')) {
    *(undefined1 *)(param_1 + 0xa7a330) = 0x10;
  }
  else {
    uVar1 = os_str_tol(param_2,0,10);
    iVar4 = DebugLevel;
    *(undefined1 *)(param_1 + 0xa7a330) = uVar1;
    *(undefined1 *)(param_1 + 0xa7a2f7) = uVar1;
    if (3 < iVar4) {
      printk("VOW_WATF_Q_LV3 --> %d\n");
    }
  }
  __memzero(param_2,0x800);
  os_alloc_mem(0,local_2c,0x20);
  os_alloc_mem(0,&local_30,0x20);
  if (local_2c[0] != (char *)0x0) {
    if (local_30 != (char *)0x0) {
      iVar4 = 0;
      do {
        sprintf(local_2c[0],"VOW_WATF_MAC_LV%d",iVar4);
        iVar5 = RTMPGetKeyParameter(local_2c[0],param_2,0x800,param_3,1);
        if ((iVar5 != 0) && (*(char *)(param_1 + 0xa7a32c) != '\0')) {
          __s = (char *)rstrtok(param_2,&_LC120);
          while (__s != (char *)0x0) {
            sVar6 = strlen(__s);
            if (sVar6 == 0x11) {
              sprintf(local_30,"%d-%s",iVar4,__s);
              set_vow_watf_add_entry(param_1,local_30);
              if (3 < DebugLevel) {
                printk("%d-%s",iVar4,__s);
              }
            }
            __s = (char *)rstrtok(0,&_LC120);
          }
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 != 4);
      if (local_2c[0] == (char *)0x0) goto LAB_000f1190;
    }
    os_free_mem();
  }
LAB_000f1190:
  if (local_30 != (char *)0x0) {
    os_free_mem();
  }
LAB_000f0f70:
  __memzero(param_2,0x800);
  iVar4 = RTMPGetKeyParameter("VOW_STA_FRR_QUANTUM",param_2,0x800,param_3,1);
  if ((iVar4 != 0) && (*param_2 != '\0')) {
    uVar1 = simple_strtol(param_2,0,10);
    iVar4 = DebugLevel;
    *(undefined1 *)(param_1 + 0xa7be35) = uVar1;
    if (3 < iVar4) {
      printk("VOW_STA_FRR_QUANTUM --> %d\n",uVar1);
    }
  }
  return;
}

