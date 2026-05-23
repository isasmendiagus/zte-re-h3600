// module: mt7915.ko
// function: ReadSecurityParameterFromFile @ 0x116048
// size: 3216 bytes
//

void ReadSecurityParameterFromFile(int param_1,int param_2,undefined4 param_3)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  int iVar12;
  undefined1 *puVar13;
  uint uVar14;
  undefined *puVar15;
  undefined *puVar16;
  byte *pbVar17;
  bool bVar18;
  char acStack_38 [20];
  
  iVar4 = RTMPGetKeyParameter("AuthMode",param_2,600,param_3,1);
  if (iVar4 != 0) {
    cVar3 = *(char *)(param_1 + 0x286285);
    if (cVar3 == '\x01') {
      iVar4 = rstrtok(param_2,&_LC53);
      if ((iVar4 != 0) &&
         ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda] != '\0')) {
        pbVar17 = (byte *)(param_1 + 0x3678c7);
        iVar5 = 0;
        do {
          pbVar17 = pbVar17 + 1;
          bVar2 = *pbVar17;
          if (2 < DebugLevel) {
            printk("I/F(%s%d) ==> ",&_LC55,iVar5);
          }
          SetWdevAuthMode("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          + (uint)bVar2 * 0x5834 + param_1 + 0x10c,iVar4);
          iVar5 = iVar5 + 1;
          "%s: group %d, band %u.\n"[(uint)bVar2 * 0x5834 + param_1 + 0x10] = '\x02';
          iVar4 = rstrtok(0,&_LC53);
        } while ((iVar4 != 0) &&
                (iVar5 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                          [param_1 + 0xda]));
      }
      cVar3 = *(char *)(param_1 + 0x286285);
    }
    if ((cVar3 == '\0') && (iVar4 = rstrtok(param_2,&_LC53), iVar4 != 0)) {
      puVar16 = &DAT_0036db84 + param_1;
      iVar5 = 0;
      do {
        if (2 < DebugLevel) {
          printk("I/F(%s%d) ==> ",&_LC55,iVar5);
        }
        SetWdevAuthMode(puVar16,iVar4);
        puVar16[0x85c] = 2;
        iVar4 = rstrtok(0,&_LC53);
        puVar16 = puVar16 + 0x2137b0;
        bVar18 = iVar5 == 0;
        bVar1 = iVar5 == -1;
        iVar5 = 1;
      } while ((bVar18 || bVar1) && iVar4 != 0);
    }
  }
  iVar4 = RTMPGetKeyParameter("EncrypType",param_2,600,param_3,1);
  if (iVar4 != 0) {
    cVar3 = *(char *)(param_1 + 0x286285);
    if (cVar3 == '\x01') {
      iVar4 = rstrtok(param_2,&_LC53);
      if (iVar4 != 0) {
        pbVar17 = (byte *)(param_1 + 0x3678c7);
        iVar5 = 0;
        do {
          pbVar17 = pbVar17 + 1;
          bVar2 = *pbVar17;
          if (2 < DebugLevel) {
            printk("I/F(%s%d) ==> ",&_LC55,iVar5);
          }
          SetWdevEncrypMode("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            + (uint)bVar2 * 0x5834 + param_1 + 0x10c,iVar4);
          iVar4 = rstrtok(0,&_LC53);
          iVar5 = iVar5 + 1;
        } while (iVar4 != 0);
      }
      cVar3 = *(char *)(param_1 + 0x286285);
    }
    if ((cVar3 == '\0') && (iVar4 = rstrtok(param_2,&_LC53), iVar4 != 0)) {
      puVar16 = &DAT_0036db84 + param_1;
      iVar5 = 0;
      do {
        if (2 < DebugLevel) {
          printk("I/F(%s%d) ==> ",&_LC55,iVar5);
        }
        SetWdevEncrypMode(puVar16,iVar4);
        iVar4 = rstrtok(0,&_LC53);
        puVar16 = puVar16 + 0x2137b0;
        bVar18 = iVar5 == 0;
        bVar1 = iVar5 == -1;
        iVar5 = 1;
      } while ((bVar18 || bVar1) && iVar4 != 0);
    }
  }
  iVar4 = RTMPGetKeyParameter("DefaultKeyID",param_2,600,param_3,1);
  if (iVar4 != 0) {
    cVar3 = *(char *)(param_1 + 0x286285);
    if (cVar3 == '\x01') {
      iVar4 = rstrtok(param_2,&_LC53);
      if (iVar4 != 0) {
        pbVar17 = (byte *)(param_1 + 0x3678c7);
        iVar5 = 0;
        do {
          pbVar17 = pbVar17 + 1;
          bVar2 = *pbVar17;
          iVar12 = os_str_tol(iVar4,0,10);
          iVar4 = DebugLevel;
          iVar10 = (uint)bVar2 * 0x5834 + param_1;
          if (iVar12 - 1U < 4) {
            "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [iVar10 + 600] = (char)(iVar12 - 1U);
          }
          else {
            "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [iVar10 + 600] = '\0';
            iVar4 = DebugLevel;
          }
          if (2 < iVar4) {
            printk("I/F(%s%d)) ==> DefaultKeyId=%d\n",&_LC55,iVar5,
                   "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   [(uint)bVar2 * 0x5834 + param_1 + 600]);
          }
          iVar5 = iVar5 + 1;
          iVar4 = rstrtok(0,&_LC53);
        } while (iVar4 != 0);
      }
      cVar3 = *(char *)(param_1 + 0x286285);
    }
    if ((cVar3 == '\0') && (iVar4 = rstrtok(param_2,&_LC53), iVar4 != 0)) {
      puVar13 = &DAT_0036dcd0 + param_1;
      iVar4 = 0;
      do {
        iVar5 = os_str_tol(param_2,0,10);
        if (iVar5 - 1U < 4) {
          *puVar13 = (char)(iVar5 - 1U);
        }
        else {
          *puVar13 = 0;
        }
        if (2 < DebugLevel) {
          printk("I/F(%s%d)) ==> DefaultKeyId=%d\n",&_LC55,iVar4,*puVar13);
        }
        iVar5 = rstrtok(0,&_LC53);
        puVar13 = puVar13 + 0x2137b0;
        bVar18 = iVar4 == 0;
        bVar1 = iVar4 == -1;
        iVar4 = 1;
      } while ((bVar18 || bVar1) && iVar5 != 0);
    }
  }
  puVar16 = &DAT_0036db84 + param_1;
  iVar4 = 0;
  do {
    iVar12 = iVar4 + 1;
    snprintf(acStack_38,0x10,"Key%dType",iVar12);
    iVar5 = RTMPGetKeyParameter(acStack_38,param_2,600,param_3,1);
    if (iVar5 != 0) {
      iVar5 = rstrtok(param_2,&_LC53);
      if (iVar5 == 0) {
        iVar10 = 0;
      }
      else {
        iVar9 = 0;
        do {
          iVar6 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
          iVar10 = iVar9 + 1;
          if (iVar9 < iVar6) {
            os_str_tol(iVar5,0,10);
          }
          iVar5 = rstrtok(0,&_LC53);
          iVar9 = iVar10;
        } while (iVar5 != 0);
      }
      cVar3 = *(char *)(param_1 + 0x286285);
      if (cVar3 == '\x01') {
        iVar10 = 0;
        bVar1 = false;
        pbVar17 = &DAT_003678c8 + param_1;
        while (iVar10 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                         [param_1 + 0xda]) {
          iVar10 = iVar10 + 1;
          snprintf(acStack_38,0x10,"Key%dStr%d",iVar12,iVar10);
          iVar5 = RTMPGetKeyParameter(acStack_38,param_2,600,param_3,0);
          if (iVar5 != 0) {
            bVar1 = true;
            ParseWebKey("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + (uint)*pbVar17 * 0x5834 + param_1 + 0x10c,param_2,iVar4,0);
          }
          pbVar17 = pbVar17 + 1;
        }
        if (!bVar1) {
          snprintf(acStack_38,0x10,"Key%dStr",iVar12);
          iVar5 = RTMPGetKeyParameter(acStack_38,param_2,600,param_3,0);
          if (iVar5 != 0) {
            if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                [param_1 + 0xda] == '\x01') {
              ParseWebKey("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          + param_1 + 0x10c,param_2,iVar4,0);
              cVar3 = *(char *)(param_1 + 0x286285);
              goto LAB_00116378;
            }
            iVar5 = rstrtok(param_2,&_LC53);
            iVar10 = 0;
            if (iVar5 != 0) {
              iVar10 = 0;
              pbVar17 = (byte *)(param_1 + 0x3678c7);
              do {
                pbVar17 = pbVar17 + 1;
                iVar10 = iVar10 + 1;
                ParseWebKey("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            + (uint)*pbVar17 * 0x5834 + param_1 + 0x10c,iVar5,iVar4,0);
                iVar5 = rstrtok(0,&_LC53);
              } while (iVar5 != 0);
            }
          }
        }
        cVar3 = *(char *)(param_1 + 0x286285);
      }
LAB_00116378:
      if (cVar3 == '\0') {
        bVar1 = false;
        puVar15 = puVar16;
        do {
          snprintf(acStack_38,0x10,"Key%dStr%d",iVar12,iVar10 + 1);
          iVar5 = RTMPGetKeyParameter(acStack_38,param_2,600,param_3,0);
          if (iVar5 != 0) {
            ParseWebKey(puVar15,param_2,iVar4,0);
            bVar1 = true;
          }
          puVar15 = puVar15 + 0x2137b0;
        } while (puVar15 != (undefined *)(param_1 + 0x794ae4));
        if (!bVar1) {
          snprintf(acStack_38,0x10,"Key%dStr",iVar12);
          iVar5 = RTMPGetKeyParameter(acStack_38,param_2,600,param_3,0);
          if (iVar5 != 0) {
            if (*(char *)(param_1 + 0x794ab8) == '\x01') {
              ParseWebKey(puVar16,param_2,iVar4,0);
            }
            else {
              iVar10 = rstrtok(param_2,&_LC53);
              puVar15 = puVar16;
              iVar5 = 0;
              if (iVar10 != 0) {
                do {
                  ParseWebKey(puVar15,iVar10,iVar4,0);
                  iVar10 = rstrtok(0,&_LC53);
                  puVar15 = puVar15 + 0x2137b0;
                  bVar18 = iVar5 == 0;
                  bVar1 = iVar5 == -1;
                  iVar5 = 1;
                } while ((bVar18 || bVar1) && iVar10 != 0);
              }
            }
          }
        }
      }
    }
    iVar4 = iVar12;
  } while (iVar12 != 4);
  ReadWPAParameterFromFile(param_1,param_2,param_3);
  iVar4 = RTMPGetKeyParameter("PWDIDR",param_2,600,param_3,1);
  cVar3 = *(char *)(param_1 + 0x286285);
  if (iVar4 != 0) {
    if (cVar3 == '\x01') {
      iVar4 = rstrtok(param_2,&_LC53);
      if ((iVar4 != 0) &&
         ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda] != '\0')) {
        pbVar17 = (byte *)(param_1 + 0x3678c7);
        iVar5 = 0;
        do {
          pbVar17 = pbVar17 + 1;
          bVar2 = *pbVar17;
          if (2 < DebugLevel) {
            printk("I/F(%s%d) ==> ",&_LC55,iVar5);
          }
          iVar5 = iVar5 + 1;
          cVar3 = os_str_tol(iVar4,0,10);
          "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
          [(uint)bVar2 * 0x5834 + param_1 + 0x10c] = cVar3 != '\0';
          iVar4 = rstrtok(0,&_LC53);
        } while ((iVar4 != 0) &&
                (iVar5 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                          [param_1 + 0xda]));
      }
      cVar3 = *(char *)(param_1 + 0x286285);
      if (cVar3 != '\0') goto LAB_001162b8;
    }
    else if (cVar3 != '\0') goto LAB_001162c0;
    iVar4 = rstrtok(param_2,&_LC53);
    if (iVar4 != 0) {
      puVar16 = &DAT_0036e368 + param_1;
      uVar14 = 0;
      do {
        if (2 < DebugLevel) {
          printk("I/F(%s%d) ==> ",&_LC55,uVar14);
        }
        cVar3 = os_str_tol(iVar4,0,10);
        *puVar16 = cVar3 != '\0';
        iVar4 = rstrtok(0,&_LC53);
        uVar8 = uVar14 ^ 1;
        uVar14 = 1;
        puVar16 = puVar16 + 0x2137b0;
        if (iVar4 == 0) {
          uVar8 = 0;
        }
      } while (uVar8 != 0);
    }
    cVar3 = *(char *)(param_1 + 0x286285);
  }
LAB_001162b8:
  if (cVar3 == '\x01') {
    pbVar17 = &DAT_003678c8 + param_1;
    iVar4 = 0;
    while (iVar4 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                    [param_1 + 0xda]) {
      iVar4 = iVar4 + 1;
      snprintf(acStack_38,0x10,"PWDID%d",iVar4);
      iVar5 = RTMPGetKeyParameter(acStack_38,param_2,600,param_3,0);
      if (iVar5 != 0) {
        iVar12 = param_1 + (uint)*pbVar17 * 0x5834;
        pcVar11 = "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                  + iVar12 + 0x110;
        *(char **)(
                  "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                  + iVar12 + 0x110) = pcVar11;
        *(char **)(
                  "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                  + iVar12 + 0x114) = pcVar11;
        iVar5 = param_2;
        do {
          uVar7 = rstrtok(iVar5,&_LC53);
          iVar5 = rstrtok(0,&DAT_00297a58);
          insert_pwd_id("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + iVar12 + 0x10c,pcVar11,uVar7);
        } while (iVar5 != 0);
      }
      pbVar17 = pbVar17 + 1;
    }
  }
LAB_001162c0:
  ReadRadiusParameterFromFile(param_1,param_2,param_3);
  ReadApcliSecParameterFromFile(param_1,param_2,param_3);
  rtmp_read_pmf_parameters_from_file(param_1,param_2,param_3);
  return;
}

