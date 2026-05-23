// module: mt7915.ko
// function: ReadRadiusParameterFromFile @ 0x113aa4
// size: 4252 bytes
//

void ReadRadiusParameterFromFile(int param_1,char *param_2,undefined4 param_3)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  size_t sVar7;
  char *pcVar8;
  void *pvVar9;
  char extraout_r1;
  char cVar10;
  int iVar11;
  int iVar12;
  byte *pbVar13;
  size_t sVar14;
  byte *local_54;
  byte *local_50;
  undefined2 local_3e;
  undefined4 local_3c;
  char acStack_38 [20];
  
  iVar3 = RTMPGetKeyParameter("own_ip_addr",param_2,0x20,param_3,1);
  if ((((iVar3 != 0) && (*(char *)(param_1 + 0x286285) == '\x01')) &&
      (iVar3 = rstrtok(param_2,&_LC53), iVar3 != 0)) &&
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0')) {
    pbVar13 = (byte *)(param_1 + 0x3678c7);
    iVar12 = 0;
    do {
      pbVar13 = pbVar13 + 1;
      bVar1 = *pbVar13;
      if (2 < DebugLevel) {
        printk("I/F(%s%d) ==> ",&_LC55,iVar12);
      }
      SetWdevOwnIPAddr("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + (uint)bVar1 * 0x5834 + param_1 + 0x10c,iVar3);
      iVar3 = rstrtok(0,&_LC53);
      iVar12 = iVar12 + 1;
    } while ((iVar3 != 0) &&
            (iVar12 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                       [param_1 + 0xda]));
    bVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [param_1 + 0xda];
    if (1 < bVar1) {
      pbVar13 = &DAT_003678c8 + param_1;
      do {
        pbVar13 = pbVar13 + 1;
        *(undefined4 *)("Group --> %u\n" + (uint)*pbVar13 * 0x5834 + param_1) =
             *(undefined4 *)("Group --> %u\n" + param_1);
      } while (pbVar13 != (byte *)(param_1 + bVar1 + 0x3678c7));
    }
  }
  local_54 = (byte *)(param_1 + 0x3678c7);
  iVar3 = RTMPGetKeyParameter("own_radius_port",param_2,0x20,param_3,1);
  if (((iVar3 != 0) && (*(char *)(param_1 + 0x286285) == '\x01')) &&
     ((iVar3 = rstrtok(param_2,&_LC53), iVar3 != 0 &&
      ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
       [param_1 + 0xda] != '\0')))) {
    iVar12 = 0;
    pbVar13 = local_54;
    do {
      pbVar13 = pbVar13 + 1;
      bVar1 = *pbVar13;
      if (2 < DebugLevel) {
        printk("I/F(%s%d) ==> ",&_LC55,iVar12);
      }
      iVar12 = iVar12 + 1;
      uVar6 = simple_strtol(iVar3,0,10);
      *(undefined4 *)("Group --> %u\n" + (uint)bVar1 * 0x5834 + param_1 + 4) = uVar6;
      iVar3 = rstrtok(0,&_LC53);
    } while ((iVar3 != 0) &&
            (iVar12 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                       [param_1 + 0xda]));
    bVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [param_1 + 0xda];
    if (1 < bVar1) {
      pbVar13 = &DAT_003678c8 + param_1;
      do {
        pbVar13 = pbVar13 + 1;
        *(undefined4 *)("Group --> %u\n" + (uint)*pbVar13 * 0x5834 + param_1 + 4) =
             *(undefined4 *)("Group --> %u\n" + param_1 + 4);
      } while (pbVar13 != (byte *)(param_1 + bVar1 + 0x3678c7));
    }
  }
  iVar3 = RTMPGetKeyParameter("session_timeout_interval",param_2,0x20,param_3,1);
  if ((((iVar3 != 0) && (*(char *)(param_1 + 0x286285) == '\x01')) &&
      (iVar3 = rstrtok(param_2,&_LC53), iVar3 != 0)) &&
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0')) {
    iVar12 = 0;
    pbVar13 = local_54;
    do {
      pbVar13 = pbVar13 + 1;
      bVar1 = *pbVar13;
      uVar6 = os_str_tol(iVar3,0,10);
      iVar3 = DebugLevel;
      *(undefined4 *)("Group --> %u\n" + (uint)bVar1 * 0x5834 + param_1 + 0xc) = uVar6;
      if (2 < iVar3) {
        printk("I/F(%s%d) ==> session_timeout_interval=%d\n",&_LC55,iVar12,uVar6);
      }
      iVar12 = iVar12 + 1;
      iVar3 = rstrtok(0,&_LC53);
    } while ((iVar3 != 0) &&
            (iVar12 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                       [param_1 + 0xda]));
    if ((iVar12 == 1) &&
       (1 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  [param_1 + 0xda])) {
      pbVar13 = &DAT_003678c8 + param_1;
      iVar3 = 1;
      do {
        iVar12 = DebugLevel;
        pbVar13 = pbVar13 + 1;
        *(undefined4 *)("Group --> %u\n" + (uint)*pbVar13 * 0x5834 + param_1 + 0xc) =
             *(undefined4 *)("Group --> %u\n" + param_1 + 0xc);
        if (2 < iVar12) {
          printk("I/F(%s%d) ==> session_timeout_interval=%d\n",&_LC55,iVar3);
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                        [param_1 + 0xda]);
    }
  }
  iVar3 = RTMPGetKeyParameter("quiet_interval",param_2,0x20,param_3,1);
  if (((iVar3 != 0) && (*(char *)(param_1 + 0x286285) == '\x01')) &&
     ((iVar3 = rstrtok(param_2,&_LC53), iVar3 != 0 &&
      ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
       [param_1 + 0xda] != '\0')))) {
    iVar12 = 0;
    pbVar13 = local_54;
    do {
      pbVar13 = pbVar13 + 1;
      bVar1 = *pbVar13;
      uVar6 = os_str_tol(iVar3,0,10);
      iVar3 = DebugLevel;
      *(undefined4 *)("Priority --> %s(%u)\n" + (uint)bVar1 * 0x5834 + param_1) = uVar6;
      if (2 < iVar3) {
        printk("I/F(%s%d) ==> quiet_interval=%d\n",&_LC55,iVar12,uVar6);
      }
      iVar12 = iVar12 + 1;
      iVar3 = rstrtok(0,&_LC53);
    } while ((iVar3 != 0) &&
            (iVar12 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                       [param_1 + 0xda]));
    if ((iVar12 == 1) &&
       (1 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  [param_1 + 0xda])) {
      pbVar13 = &DAT_003678c8 + param_1;
      iVar3 = 1;
      do {
        iVar12 = DebugLevel;
        pbVar13 = pbVar13 + 1;
        *(undefined4 *)("Priority --> %s(%u)\n" + (uint)*pbVar13 * 0x5834 + param_1) =
             *(undefined4 *)("Priority --> %s(%u)\n" + param_1);
        if (2 < iVar12) {
          printk("I/F(%s%d) ==> quiet_interval=%d\n",&_LC55,iVar3);
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                        [param_1 + 0xda]);
    }
  }
  iVar3 = RTMPGetKeyParameter("EAPifname",param_2,0x100,param_3,1);
  if ((((iVar3 != 0) && (*(char *)(param_1 + 0x286285) == '\x01')) &&
      (pcVar8 = (char *)rstrtok(param_2,&_LC53), pcVar8 != (char *)0x0)) &&
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0')) {
    iVar3 = 0;
    pbVar13 = local_54;
    do {
      pbVar13 = pbVar13 + 1;
      bVar1 = *pbVar13;
      if ((*pcVar8 != '\0') && (sVar7 = strlen(pcVar8), sVar7 < 0x11)) {
        iVar12 = param_1 + (uint)bVar1 * 0x5834;
        "Priority --> %s(%u)\n"[iVar12 + 0x14] = (char)sVar7;
        sVar7 = strlen(pcVar8);
        memmove("Priority --> %s(%u)\n" + iVar12 + 4,pcVar8,sVar7);
        if (2 < DebugLevel) {
          printk("I/F(%s%d) ==> EAPifname=%s, len=%d\n",&_LC55,iVar3,
                 "Priority --> %s(%u)\n" + iVar12 + 4,"Priority --> %s(%u)\n"[iVar12 + 0x14]);
        }
      }
      iVar3 = iVar3 + 1;
      pcVar8 = (char *)rstrtok(0,&_LC53);
    } while ((pcVar8 != (char *)0x0) &&
            (iVar3 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                      [param_1 + 0xda]));
  }
  iVar3 = RTMPGetKeyParameter("PreAuthifname",param_2,0x100,param_3,1);
  if ((iVar3 != 0) &&
     (((*(char *)(param_1 + 0x286285) == '\x01' &&
       (pcVar8 = (char *)rstrtok(param_2,&_LC53), pcVar8 != (char *)0x0)) &&
      ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
       [param_1 + 0xda] != '\0')))) {
    iVar3 = 0;
    pbVar13 = local_54;
    do {
      pbVar13 = pbVar13 + 1;
      bVar1 = *pbVar13;
      if ((*pcVar8 != '\0') && (sVar7 = strlen(pcVar8), sVar7 < 0x11)) {
        iVar12 = param_1 + (uint)bVar1 * 0x5834;
        "Ac0 --> %uus(%u)\n"[iVar12 + 0xd] = (char)sVar7;
        sVar7 = strlen(pcVar8);
        memmove("Priority --> %s(%u)\n" + iVar12 + 0x15,pcVar8,sVar7);
        if (2 < DebugLevel) {
          printk("I/F(%s%d) ==> PreAuthifname=%s, len=%d\n",&_LC55,iVar3,
                 "Priority --> %s(%u)\n" + iVar12 + 0x15,"Ac0 --> %uus(%u)\n"[iVar12 + 0xd]);
        }
      }
      iVar3 = iVar3 + 1;
      pcVar8 = (char *)rstrtok(0,&_LC53);
    } while ((pcVar8 != (char *)0x0) &&
            (iVar3 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                      [param_1 + 0xda]));
  }
  iVar3 = RTMPGetKeyParameter("PreAuth",param_2,0x100,param_3,1);
  if ((iVar3 != 0) &&
     (((*(char *)(param_1 + 0x286285) == '\x01' && (iVar3 = rstrtok(param_2,&_LC53), iVar3 != 0)) &&
      ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
       [param_1 + 0xda] != '\0')))) {
    iVar12 = 0;
    pbVar13 = local_54;
    do {
      pbVar13 = pbVar13 + 1;
      bVar1 = *pbVar13;
      iVar4 = os_str_tol(iVar3,0,10);
      iVar3 = DebugLevel;
      iVar5 = (uint)bVar1 * 0x5834 + param_1;
      if (iVar4 == 0) {
        "Ac0 --> %uus(%u)\n"[iVar5 + 0xe] = '\0';
        iVar3 = DebugLevel;
      }
      else {
        "Ac0 --> %uus(%u)\n"[iVar5 + 0xe] = '\x01';
      }
      if (2 < iVar3) {
        printk("I/F(%s%d) ==> PreAuth=%d\n",&_LC55,iVar12,
               "Ac0 --> %uus(%u)\n"[(uint)bVar1 * 0x5834 + param_1 + 0xe]);
      }
      iVar12 = iVar12 + 1;
      iVar3 = rstrtok(0,&_LC53);
    } while ((iVar3 != 0) &&
            (iVar12 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                       [param_1 + 0xda]));
  }
  iVar3 = RTMPGetKeyParameter("IEEE8021X",param_2,0x100,param_3,1);
  if (((iVar3 != 0) &&
      ((*(char *)(param_1 + 0x286285) == '\x01' && (iVar3 = rstrtok(param_2,&_LC53), iVar3 != 0))))
     && ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
         [param_1 + 0xda] != '\0')) {
    iVar12 = 0;
    pbVar13 = local_54;
    do {
      pbVar13 = pbVar13 + 1;
      bVar1 = *pbVar13;
      iVar4 = os_str_tol(iVar3,0,10);
      iVar3 = DebugLevel;
      iVar5 = (uint)bVar1 * 0x5834 + param_1;
      if (iVar4 == 0) {
        "Airtime control --> %s(%d)\n"[iVar5 + 0x18] = '\0';
      }
      else {
        "Airtime control --> %s(%d)\n"[iVar5 + 0x18] = '\x01';
      }
      if (2 < iVar3) {
        printk("IF(%s%d) ==> IEEE8021X=%d\n",&_LC55,iVar12,
               "Airtime control --> %s(%d)\n"[(uint)bVar1 * 0x5834 + param_1 + 0x18]);
      }
      iVar12 = iVar12 + 1;
      iVar3 = rstrtok(0,&_LC53);
    } while ((iVar3 != 0) &&
            (iVar12 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                       [param_1 + 0xda]));
  }
  local_3e = 0;
  do {
    iVar3 = RTMPGetKeyParameterWithOffset("RADIUS_Server",param_2,&local_3e,0x100,param_3,1);
    if (iVar3 == 0) {
      local_3e = 0;
      do {
        do {
          iVar3 = RTMPGetKeyParameterWithOffset("RADIUS_Port",param_2,&local_3e,0x100,param_3,1);
          if (iVar3 == 0) {
            local_3e = 0;
            bVar2 = false;
            do {
              do {
                iVar3 = RTMPGetKeyParameterWithOffset
                                  ("RADIUS_Key",param_2,&local_3e,0x100,param_3,1);
                if (iVar3 == 0) {
                  if (!bVar2) {
                    local_50 = local_54;
                    iVar3 = 0;
                    while (iVar12 = iVar3,
                          iVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0)),
                          iVar12 < iVar3) {
                      snprintf(acStack_38,0x10,"RADIUS_Key%d",iVar12 + 1);
                      local_50 = local_50 + 1;
                      bVar1 = *local_50;
                      local_3e = 0;
                      iVar4 = param_1 + (uint)bVar1 * 0x5834;
                      while (iVar5 = RTMPGetKeyParameterWithOffset
                                               (acStack_38,param_2,&local_3e,0x80,param_3,0),
                            iVar3 = iVar12 + 1, iVar5 != 0) {
                        if (*param_2 != '\0') {
                          sVar7 = strlen(param_2);
                          cVar10 = extraout_r1;
                          if (sVar7 < 0x41) {
                            cVar10 = (char)sVar7;
                          }
                          if (0x40 < sVar7) {
                            sVar7 = 0x40;
                            cVar10 = '@';
                          }
                          "%s: ************** Group%d **********\n"[iVar4 + 5] = cVar10;
                          pvVar9 = memmove("Ac2 --> %uus(%u)\n" + param_1 + (uint)bVar1 * 0x5834 + 1
                                           ,param_2,sVar7);
                          if (2 < DebugLevel) {
                            printk("IF(%s%d) ==> radius_key(seq-%d)=%s, len=%d\n",&_LC55,iVar12,0,
                                   pvVar9,"%s: ************** Group%d **********\n"[iVar4 + 5]);
                          }
                        }
                      }
                    }
                  }
                  iVar3 = 0;
                  while( true ) {
                    iVar4 = iVar3;
                    iVar3 = iVar4 + 1;
                    iVar12 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
                    if (iVar12 <= iVar4) break;
                    local_54 = local_54 + 1;
                    bVar1 = *local_54;
                    snprintf(acStack_38,0x10,"NasId%d",iVar3);
                    iVar12 = RTMPGetKeyParameter(acStack_38,param_2,0x21,param_3,0);
                    if ((iVar12 != 0) && (*param_2 != '\0')) {
                      sVar7 = strlen(param_2);
                      iVar12 = param_1 + (uint)bVar1 * 0x5834;
                      cVar10 = (char)sVar7;
                      if (0x10 < sVar7) {
                        sVar7 = 0x10;
                        cVar10 = '\x10';
                      }
                      "Ac1 --> %uus(%u)\n"[iVar12 + 0xb] = cVar10;
                      pvVar9 = memmove("Ac0 --> %uus(%u)\n" + iVar12 + 0xf,param_2,sVar7);
                      if (2 < DebugLevel) {
                        printk("IF(%s%d) ==> NAS-ID=%s, len=%d\n",&_LC55,iVar4,pvVar9,
                               "Ac1 --> %uus(%u)\n"[iVar12 + 0xb]);
                      }
                    }
                  }
                  return;
                }
                sVar7 = strlen(param_2);
                if ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          [param_1 + 0xda] < sVar7) {
                  bVar2 = true;
                }
                pcVar8 = (char *)rstrtok(param_2,&_LC53);
              } while (pcVar8 == (char *)0x0);
              iVar3 = 0;
              pbVar13 = local_54;
              do {
                iVar12 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
                if (iVar12 <= iVar3) break;
                pbVar13 = pbVar13 + 1;
                bVar1 = *pbVar13;
                if (*pcVar8 != '\0') {
                  sVar7 = strlen(pcVar8);
                  iVar12 = param_1 + (uint)bVar1 * 0x5834;
                  sVar14 = sVar7 & 0xff;
                  if (0x40 < sVar7) {
                    sVar14 = 0x40;
                    sVar7 = sVar14;
                  }
                  "%s: ************** Group%d **********\n"[iVar12 + 5] = (char)sVar14;
                  memmove("Ac2 --> %uus(%u)\n" + iVar12 + 1,pcVar8,sVar7);
                  if (2 < DebugLevel) {
                    printk("IF(%s%d) ==> radius_key(seq-%d)=%s, len=%d\n",&_LC55,iVar3,0,pcVar8,
                           "%s: ************** Group%d **********\n"[iVar12 + 5]);
                  }
                }
                iVar3 = iVar3 + 1;
                pcVar8 = (char *)rstrtok(0,&_LC53);
              } while (pcVar8 != (char *)0x0);
            } while( true );
          }
          iVar3 = rstrtok(param_2,&_LC53);
        } while (iVar3 == 0);
        iVar12 = 0;
        pbVar13 = local_54;
        do {
          iVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
          if (iVar4 <= iVar12) break;
          pbVar13 = pbVar13 + 1;
          bVar1 = *pbVar13;
          uVar6 = os_str_tol(iVar3,0,10);
          iVar3 = DebugLevel;
          *(undefined4 *)("Ac1 --> %uus(%u)\n" + (uint)bVar1 * 0x5834 + param_1 + 0x11) = uVar6;
          if (2 < iVar3) {
            printk("IF(%s%d) ==> radius_port(seq-%d)=%d\n",&_LC55,iVar12,0,uVar6);
          }
          iVar12 = iVar12 + 1;
          iVar3 = rstrtok(0,&_LC53);
        } while (iVar3 != 0);
      } while( true );
    }
    iVar3 = rstrtok(param_2,&_LC53);
    if (iVar3 != 0) {
      iVar12 = 0;
      pbVar13 = local_54;
      do {
        iVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        if (iVar4 <= iVar12) break;
        pbVar13 = pbVar13 + 1;
        bVar1 = *pbVar13;
        iVar5 = rtinet_aton(iVar3,&local_3c);
        iVar4 = DebugLevel;
        iVar11 = (uint)bVar1 * 0x5834 + param_1;
        if ((iVar5 != 0) && ((byte)"Ac1 --> %uus(%u)\n"[iVar11 + 0xc] < 2)) {
          *(undefined4 *)("Ac1 --> %uus(%u)\n" + iVar11 + 0xd) = local_3c;
          if (2 < iVar4) {
            printk("IF(%s%d) ==> radius_ip(seq-%d)=%s\n",&_LC55,iVar12,
                   "Ac1 --> %uus(%u)\n"[iVar11 + 0xc],iVar3);
          }
          iVar3 = (uint)bVar1 * 0x5834 + param_1;
          "Ac1 --> %uus(%u)\n"[iVar3 + 0xc] = "Ac1 --> %uus(%u)\n"[iVar3 + 0xc] + '\x01';
        }
        iVar12 = iVar12 + 1;
        iVar3 = rstrtok(0,&_LC53);
      } while (iVar3 != 0);
    }
  } while( true );
}

