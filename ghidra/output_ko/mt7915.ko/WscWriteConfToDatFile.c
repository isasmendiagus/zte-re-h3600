// module: mt7915.ko
// function: WscWriteConfToDatFile @ 0x1eba98
// size: 4256 bytes
//

void WscWriteConfToDatFile(int param_1,int param_2)

{
  undefined2 uVar1;
  uint uVar2;
  char *pcVar3;
  size_t sVar4;
  undefined4 uVar5;
  char *pcVar6;
  char *pcVar7;
  undefined4 uVar8;
  char *pcVar9;
  char cVar10;
  byte bVar11;
  int iVar12;
  undefined4 uVar13;
  uint uVar14;
  uint uVar15;
  byte *pbVar16;
  int iVar17;
  uint uVar18;
  char *pcVar19;
  uint uVar20;
  char *pcVar21;
  char *local_cc;
  char *local_c8;
  int local_a4;
  char *local_a0;
  undefined1 auStack_9c [12];
  char local_90 [40];
  undefined4 local_68;
  
  bVar11 = *(byte *)(param_1 + 0x794b18);
  local_a4 = 0;
  local_a0 = (char *)0x0;
  local_90[0] = '\0';
  local_90[1] = '\0';
  local_90[2] = '\0';
  local_90[3] = '\0';
  local_90[4] = '\0';
  local_90[5] = '\0';
  local_90[6] = '\0';
  local_90[7] = '\0';
  local_90[8] = '\0';
  local_90[9] = '\0';
  local_90[10] = '\0';
  local_90[0xb] = '\0';
  local_90[0xc] = '\0';
  local_90[0xd] = '\0';
  local_90[0xe] = '\0';
  local_90[0xf] = '\0';
  local_90[0x10] = '\0';
  local_90[0x11] = '\0';
  local_90[0x12] = '\0';
  local_90[0x13] = '\0';
  local_90[0x14] = '\0';
  local_90[0x15] = '\0';
  local_90[0x16] = '\0';
  local_90[0x17] = '\0';
  local_90[0x18] = '\0';
  local_90[0x19] = '\0';
  local_90[0x1a] = '\0';
  local_90[0x1b] = '\0';
  local_90[0x1c] = '\0';
  local_90[0x1d] = '\0';
  local_90[0x1e] = '\0';
  local_90[0x1f] = '\0';
  local_90[0x20] = '\0';
  local_90[0x21] = '\0';
  local_90[0x22] = '\0';
  local_90[0x23] = '\0';
  local_90[0x24] = '\0';
  local_90[0x25] = '\0';
  local_90[0x26] = '\0';
  local_90[0x27] = '\0';
  if (2 < DebugLevel) {
    printk("-----> WscWriteConfToDatFile(CurOpMode = %d)\n");
  }
  if (param_2 == 0) {
    uVar14 = bVar11 & 0xf;
    if ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              [param_1 + 0xda] < uVar14) {
      if (DebugLevel < 3) {
        return;
      }
      printk("<----- WscWriteConfToDatFile (wrong apidx = %d)\n",uVar14);
      return;
    }
    pcVar3 = (char *)get_dev_l2profile(param_1);
    iVar12 = uVar14 * 0x5834 + param_1;
    snprintf(local_90,0x14,"Key%dStr%d=",
             (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   [iVar12 + 600] + 1,uVar14 + 1);
    snprintf(local_90 + 0x14,0x14,"Key%dType=",
             (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   [iVar12 + 600] + 1);
  }
  else {
    if (param_2 != 2) {
      return;
    }
    pcVar3 = "/etc/Wireless/RT2860STA/RT2860STA.dat";
    if (*(char *)(param_1 + 0x286285) != '\0') {
      pcVar3 = (char *)0x0;
    }
    snprintf(local_90,0x14,"Key%dStr=",(byte)(&DAT_0036dcd0)[param_1] + 1);
    snprintf(local_90 + 0x14,0x14,"Key%dType=",(byte)(&DAT_0036dcd0)[param_1] + 1);
  }
  local_c8 = local_90 + 0x14;
  local_cc = local_90;
  if (pcVar3 != (char *)0x0) {
    RtmpOSFSInfoChange(auStack_9c,1);
    uVar14 = RtmpOSFileOpen(pcVar3,0,0);
    if ((uVar14 == 0) || (0xfffff000 < uVar14)) {
      if (2 < DebugLevel) {
        printk("-->1) %s: Error opening file %s\n","WscWriteConfToDatFile",pcVar3);
      }
      RtmpOSFSInfoChange(auStack_9c,0);
      return;
    }
    uVar15 = 0;
    memset(&local_68,0,0x40);
    while (iVar12 = RtmpOSFileRead(uVar14,&local_68,0x40), 0 < iVar12) {
      uVar15 = uVar15 + iVar12;
    }
    os_alloc_mem(0,&local_a4,uVar15);
    if (local_a4 == 0) {
      RtmpOSFileClose(uVar14);
      if (2 < DebugLevel) {
        printk("CfgData mem alloc fail. (fileLen = %ld)\n",uVar15);
      }
    }
    else {
      if (uVar15 != 0) {
        __memzero(local_a4,uVar15);
      }
      RtmpOSFileSeek(uVar14,0);
      uVar2 = RtmpOSFileRead(uVar14,local_a4,uVar15);
      RtmpOSFileClose(uVar14);
      if (uVar2 == uVar15) {
        uVar14 = RtmpOSFileOpen(pcVar3,0x201,0);
        if ((uVar14 != 0) && (uVar14 < 0xfffff001)) {
          iVar12 = rtstrstr(local_a4,"Default\n");
          pcVar3 = (char *)(iVar12 + 8);
          RtmpOSFileWrite(uVar14,local_a4,(int)pcVar3 - local_a4);
          os_alloc_mem(0,&local_a0,0x200);
          if (local_a0 == (char *)0x0) {
            if (2 < DebugLevel) {
              printk("pTempStr mem alloc fail. (512)\n");
            }
          }
          else {
            while (__memzero(local_a0,0x200), pcVar19 = local_a0,
                  (uint)((int)pcVar3 - local_a4) < uVar15) {
              cVar10 = *pcVar3;
              if (cVar10 == '\n' || cVar10 == '\0') {
                iVar12 = 0;
              }
              else {
                iVar12 = 0;
                pcVar6 = pcVar3;
                do {
                  iVar12 = iVar12 + 1;
                  local_a0[(int)pcVar6 - (int)pcVar3] = cVar10;
                  pcVar6 = pcVar6 + 1;
                  cVar10 = *pcVar6;
                } while (cVar10 != '\n' && cVar10 != '\0');
              }
              local_a0[iVar12] = '\0';
              sVar4 = strlen(local_a0);
              pcVar3 = pcVar3 + sVar4 + 1;
              iVar12 = strncmp(pcVar19,"SSID=",5);
              if ((((iVar12 == 0) || (iVar12 = strncmp(pcVar19,"SSID1=",6), iVar12 == 0)) ||
                  (iVar12 = strncmp(pcVar19,"SSID2=",6), iVar12 == 0)) ||
                 ((iVar12 = strncmp(pcVar19,"SSID3=",6), iVar12 == 0 ||
                  (iVar12 = strncmp(pcVar19,"SSID4=",6), iVar12 == 0)))) {
                iVar12 = rtstrstr(pcVar19,&_LC132);
                WscWriteSsidToDatFile(param_1,local_a0,iVar12 == 0,param_2);
                pcVar6 = local_a0;
              }
              else {
                iVar12 = strncmp(pcVar19,"NetworkType=",0xc);
                if (iVar12 == 0) {
                  __memzero(pcVar19,0x200);
                  if (s__RB_FULL__Free_Queue_List___00371ba4[param_1 + 0x14] == '\0') {
                    pcVar19 = "NetworkType=Adhoc";
                  }
                  else {
                    pcVar19 = "NetworkType=Infra";
                  }
                  uVar5 = *(undefined4 *)(pcVar19 + 4);
                  uVar8 = *(undefined4 *)(pcVar19 + 8);
                  uVar13 = *(undefined4 *)(pcVar19 + 0xc);
                  uVar1 = *(undefined2 *)(pcVar19 + 0x10);
                  *(undefined4 *)local_a0 = *(undefined4 *)pcVar19;
                  *(undefined4 *)(local_a0 + 4) = uVar5;
                  *(undefined2 *)(local_a0 + 0x10) = uVar1;
                  *(undefined4 *)(local_a0 + 8) = uVar8;
                  *(undefined4 *)(local_a0 + 0xc) = uVar13;
                  pcVar6 = local_a0;
                }
                else {
                  iVar12 = strncmp(pcVar19,"AuthMode=",9);
                  if (iVar12 == 0) {
                    __memzero(pcVar19,0x200);
                    pcVar19 = local_a0;
                    builtin_strncpy(local_a0,"AuthMode=",10);
                    pcVar6 = local_a0;
                    if (param_2 == 0) {
                      if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          [param_1 + 0xda] != '\0') {
                        iVar12 = 0;
                        iVar17 = 0;
                        do {
                          if ("pStaCfg->WpaPassPhrase"[param_1 + iVar17 + 5] != '\0') {
                            if (iVar12 == 0) {
                              uVar5 = GetAuthModeStr(*(undefined4 *)
                                                      (
                                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                  + param_1 + 0x10c));
                              pcVar6 = "%s%s";
                            }
                            else {
                              uVar5 = GetAuthModeStr(*(undefined4 *)
                                                      (
                                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                  + param_1 + iVar17 + 0x10c));
                              pcVar6 = "%s;%s";
                            }
                            snprintf(pcVar19,0x200,pcVar6,pcVar19,uVar5);
                          }
                          iVar12 = iVar12 + 1;
                          iVar17 = iVar17 + 0x5834;
                          pcVar6 = local_a0;
                        } while (iVar12 < (int)(uint)(byte)
                                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                  [param_1 + 0xda]);
                      }
                    }
                    else if (param_2 == 2) {
                      WscGetAuthType(*(undefined4 *)(&DAT_0036db84 + param_1));
                      uVar5 = WscGetAuthTypeStr();
                      snprintf(pcVar19,0x200,"%s%s",pcVar19,uVar5);
                      pcVar6 = local_a0;
                    }
                  }
                  else {
                    iVar12 = strncmp(pcVar19,"EncrypType=",0xb);
                    if (iVar12 == 0) {
                      __memzero(pcVar19,0x200);
                      pcVar19 = local_a0;
                      builtin_strncpy(local_a0,"EncrypType=",0xc);
                      pcVar6 = local_a0;
                      if (param_2 == 0) {
                        if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda] != '\0') {
                          iVar12 = 0;
                          pcVar7 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                   + param_1 + 0x254;
                          do {
                            if (iVar12 == 0) {
                              uVar5 = GetEncryModeStr(*(undefined4 *)
                                                       (
                                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                  + param_1 + 0x254));
                              pcVar6 = "%s%s";
                            }
                            else {
                              uVar5 = GetEncryModeStr(*(undefined4 *)pcVar7);
                              pcVar6 = "%s;%s";
                            }
                            snprintf(pcVar19,0x200,pcVar6,pcVar19,uVar5);
                            iVar12 = iVar12 + 1;
                            pcVar7 = pcVar7 + 0x5834;
                            pcVar6 = local_a0;
                          } while (iVar12 < (int)(uint)(byte)
                                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                  [param_1 + 0xda]);
                        }
                      }
                      else if (param_2 == 2) {
                        iVar12 = WscGetEncryType(*(undefined4 *)(&DAT_0036dccc + param_1));
                        uVar2 = iVar12 - 1U & 0xffff;
                        if (uVar2 < 8) {
                          pcVar6 = *(char **)(&DAT_002a10d8 + uVar2 * 4);
                        }
                        else {
                          pcVar6 = "TKIPAES";
                        }
                        snprintf(pcVar19,0x200,"%s%s",pcVar19,pcVar6);
                        pcVar6 = local_a0;
                      }
                    }
                    else {
                      iVar12 = strncmp(pcVar19,"WPAPSK=",7);
                      if (((iVar12 == 0) || (iVar12 = strncmp(pcVar19,"WPAPSK1=",8), iVar12 == 0))
                         || ((iVar12 = strncmp(pcVar19,"WPAPSK2=",8), iVar12 == 0 ||
                             ((iVar12 = strncmp(pcVar19,"WPAPSK3=",8), iVar12 == 0 ||
                              (iVar12 = strncmp(pcVar19,"WPAPSK4=",8), iVar12 == 0)))))) {
                        pcVar6 = strstr(pcVar19,"WPAPSK=");
                        WscWriteWpaPskToDatFile(param_1,pcVar19,pcVar6 == (char *)0x0);
                        pcVar6 = local_a0;
                      }
                      else {
                        iVar12 = strncmp(pcVar19,"WscConfMode=",0xc);
                        pcVar7 = local_a0;
                        if (iVar12 == 0) {
                          builtin_strncpy(pcVar19,"WscConfMode=",0xd);
                          pcVar6 = local_a0;
                          if (param_2 == 0) {
                            if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                [param_1 + 0xda] != '\0') {
                              iVar12 = 0;
                              pcVar19 = "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                                        + param_1 + 0x2b;
                              do {
                                pcVar6 = "en_bw_refill: %d\n" + param_1 + 4;
                                if (iVar12 != 0) {
                                  pcVar6 = *(char **)pcVar19;
                                }
                                pcVar9 = "%s;%d";
                                if (iVar12 == 0) {
                                  pcVar6 = *(char **)(pcVar6 + 0x52c);
                                  pcVar9 = "%s%d";
                                }
                                iVar12 = iVar12 + 1;
                                snprintf(pcVar7,0x200,pcVar9,pcVar7,pcVar6);
                                pcVar19 = pcVar19 + 0x5834;
                                pcVar6 = local_a0;
                              } while (iVar12 < (int)(uint)(byte)
                                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                  [param_1 + 0xda]);
                            }
                          }
                          else if (param_2 == 2) {
                            snprintf(local_a0,0x200,"%s%d",local_a0,
                                     *(undefined4 *)(&DAT_0036ee3c + param_1));
                            pcVar6 = local_a0;
                          }
                        }
                        else {
                          iVar12 = strncmp(pcVar19,"WscConfStatus=",0xe);
                          pcVar7 = local_a0;
                          if (iVar12 == 0) {
                            builtin_strncpy(pcVar19,"WscConfStatus=",0xf);
                            pcVar6 = local_a0;
                            if (param_2 == 0) {
                              if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                  [param_1 + 0xda] != '\0') {
                                iVar12 = 0;
                                do {
                                  pcVar19 = "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                                            + iVar12 * 0x5834 + 0x33;
                                  if (iVar12 == 0) {
                                    pcVar19 = (char *)(uint)(byte)
                                                  "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                                                  [param_1 + 0x33];
                                  }
                                  pcVar6 = "%s;%d";
                                  if (iVar12 == 0) {
                                    pcVar6 = "%s%d";
                                  }
                                  else {
                                    pcVar19 = (char *)(uint)(byte)pcVar19[param_1];
                                  }
                                  iVar12 = iVar12 + 1;
                                  snprintf(pcVar7,0x200,pcVar6,pcVar7,pcVar19);
                                  pcVar6 = local_a0;
                                } while (iVar12 < (int)(uint)(byte)
                                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                  [param_1 + 0xda]);
                              }
                            }
                            else if (param_2 == 2) {
                              snprintf(local_a0,0x200,"%s%d",local_a0,
                                       (uint)(byte)(&DAT_0036ee44)[param_1]);
                              pcVar6 = local_a0;
                            }
                          }
                          else {
                            iVar12 = strncmp(pcVar19,"DefaultKeyID=",0xd);
                            if (iVar12 == 0) {
                              __memzero(pcVar19,0x200);
                              pcVar19 = local_a0;
                              builtin_strncpy(local_a0,"DefaultKeyID=",0xe);
                              pcVar6 = local_a0;
                              if (param_2 == 0) {
                                if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                    [param_1 + 0xda] != '\0') {
                                  pbVar16 = (byte *)(
                                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                  + param_1 + 600);
                                  iVar12 = 0;
                                  do {
                                    pcVar6 = pcVar19;
                                    if (iVar12 == 0) {
                                      pcVar6 = (char *)(uint)(byte)
                                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                  [param_1 + 600];
                                    }
                                    pcVar7 = "%s;%d";
                                    if (iVar12 == 0) {
                                      pcVar7 = "%s%d";
                                      pcVar9 = pcVar19;
                                      pcVar21 = pcVar6;
                                    }
                                    else {
                                      pcVar21 = (char *)(uint)*pbVar16;
                                      pcVar9 = pcVar6;
                                    }
                                    iVar12 = iVar12 + 1;
                                    snprintf(pcVar19,0x200,pcVar7,pcVar9,pcVar21 + 1);
                                    pbVar16 = pbVar16 + 0x5834;
                                    pcVar6 = local_a0;
                                  } while (iVar12 < (int)(uint)(byte)
                                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                  [param_1 + 0xda]);
                                }
                              }
                              else if (param_2 == 2) {
                                snprintf(local_a0,0x200,"%s%d",local_a0,
                                         (byte)(&DAT_0036dcd0)[param_1] + 1);
                                pcVar6 = local_a0;
                              }
                            }
                            else {
                              pcVar6 = pcVar19;
                              if (param_2 == 0) {
                                uVar2 = *(byte *)(param_1 + 0x794b18) & 0xf;
                                sVar4 = strlen(local_c8);
                                iVar12 = strncmp(pcVar19,local_c8,sVar4);
                                if (iVar12 == 0) {
                                  if ((*(uint *)(
                                                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                + uVar2 * 0x5834 + param_1 + 0x254) & 0xe) != 0) {
                                    local_68 = param_2;
                                    iVar12 = rtstrstr(pcVar19,&_LC255);
                                    if (iVar12 == 0) goto LAB_001ec158;
                                    iVar17 = 0;
                                    local_68 = CONCAT31(local_68._1_3_,*(char *)(iVar12 + 1) + -0x30
                                                       );
                                    do {
                                      iVar12 = rtstrstr(iVar12 + 1,&_LC256);
                                      if (iVar12 == 0) break;
                                      bVar11 = *(char *)(iVar12 + 1) - 0x30;
                                      if (bVar11 < 2) {
                                        *(byte *)((int)&local_68 + iVar17 + 1) = bVar11;
                                      }
                                      iVar17 = iVar17 + 1;
                                    } while (iVar17 != 3);
                                    __memzero(pcVar19,0x200);
                                    sVar4 = strlen(local_c8);
                                    uVar18 = 0;
                                    memmove(pcVar19,local_c8,sVar4);
                                    while (uVar20 = uVar18 & 0xff, pcVar6 = local_a0,
                                          uVar20 < (byte)
                                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                  [param_1 + 0xda]) {
                                      if (uVar2 == uVar20) {
                                        snprintf(pcVar19,0x200,"%s0",pcVar19);
                                      }
                                      else {
                                        snprintf(pcVar19,0x200,"%s%d",pcVar19,
                                                 (uint)*(byte *)((int)&local_68 + uVar20));
                                      }
                                      uVar18 = uVar18 + 1;
                                      if ((int)uVar2 <
                                          (int)((byte)
                                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                  [param_1 + 0xda] - 1)) {
                                        snprintf(pcVar19,0x200,"%s;",pcVar19);
                                      }
                                    }
                                  }
                                }
                                else {
                                  sVar4 = strlen(local_cc);
                                  iVar12 = strncmp(pcVar19,local_cc,sVar4);
                                  if ((iVar12 == 0) &&
                                     ((*(uint *)(
                                                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                + uVar2 * 0x5834 + param_1 + 0x254) & 0xe) != 0)) {
                                    __memzero(pcVar19,0x200);
                                    sVar4 = strlen(local_cc);
                                    memmove(pcVar19,local_cc,sVar4);
                                    sVar4 = strlen(pcVar19);
                                    iVar12 = uVar2 * 0x5834;
                                    uVar2 = (uint)*(ushort *)
                                                   (
                                                  "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                                                  + param_1 + iVar12 + 0x70);
                                    pcVar6 = local_a0;
                                    if (uVar2 != 0) {
                                      if ((uVar2 & 0xfffffff7) == 5) {
                                        iVar17 = 0;
                                        while( true ) {
                                          pcVar6 = local_a0;
                                          if ((int)(uint)*(ushort *)
                                                          (
                                                  "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                                                  + param_1 + iVar12 + 0x70) <= iVar17) break;
                                          snprintf(pcVar19,0x200,"%s%02x",pcVar19,
                                                   (uint)(byte)
                                                  "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                                                  [param_1 + iVar17 + iVar12 + 0x30]);
                                          iVar17 = iVar17 + 1;
                                        }
                                      }
                                      else if ((uVar2 & 0xffffffef) == 10) {
                                        memmove(pcVar19 + sVar4,
                                                "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                                                + param_1 + iVar12 + 0x30,uVar2);
                                        pcVar6 = local_a0;
                                      }
                                    }
                                  }
                                }
                              }
                              else if (param_2 == 2) {
                                iVar12 = rtstrstr(pcVar19,local_c8);
                                if (iVar12 == 0) {
                                  iVar12 = rtstrstr(pcVar19,local_cc);
                                  pcVar6 = local_a0;
                                  if ((iVar12 != 0) &&
                                     (bVar11 = (&DAT_00370ad0)[param_1],
                                     (*(uint *)(&DAT_0036dccc + param_1) & 0xe) != 0)) {
                                    __memzero(pcVar19,0x200);
                                    sVar4 = strlen(local_cc);
                                    iVar12 = (uint)bVar11 * 0x74;
                                    memmove(pcVar19,local_cc,sVar4);
                                    sVar4 = strlen(pcVar19);
                                    uVar2 = (uint)*(ushort *)(&DAT_00370b3c + param_1 + iVar12);
                                    pcVar6 = local_a0;
                                    if (uVar2 != 0) {
                                      if ((uVar2 & 0xfffffff7) == 5) {
                                        iVar17 = 0;
                                        while( true ) {
                                          pcVar6 = local_a0;
                                          if ((int)(uint)*(ushort *)
                                                          (&DAT_00370b3c + param_1 + iVar12) <=
                                              iVar17) break;
                                          snprintf(pcVar19,0x200,"%s%02x",pcVar19,
                                                   (uint)*(byte *)(param_1 +
                                                                  iVar17 + iVar12 + 0x370afc));
                                          iVar17 = iVar17 + 1;
                                        }
                                      }
                                      else if ((uVar2 & 0xffffffef) == 10) {
                                        memmove(pcVar19 + sVar4,
                                                (void *)(param_1 + iVar12 + 0x370afc),uVar2);
                                        pcVar6 = local_a0;
                                      }
                                    }
                                  }
                                }
                                else {
                                  pcVar6 = local_a0;
                                  if ((*(uint *)(&DAT_0036dccc + param_1) & 0xe) != 0) {
                                    __memzero(pcVar19,0x200);
                                    snprintf(pcVar19,0x200,"%s0",local_c8);
                                    pcVar6 = local_a0;
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
              sVar4 = strlen(pcVar6);
              RtmpOSFileWrite(uVar14,pcVar6,sVar4);
              RtmpOSFileWrite(uVar14,&_LC13,1);
            }
          }
          RtmpOSFileClose(uVar14);
LAB_001ec158:
          if (local_a0 != (char *)0x0) {
            os_free_mem();
          }
        }
      }
      else if (2 < DebugLevel) {
        printk("CfgData mem alloc fail, fileLen = %ld\n",uVar15);
      }
      if (local_a4 != 0) {
        os_free_mem();
      }
    }
    RtmpOSFSInfoChange(auStack_9c,0);
    if (2 < DebugLevel) {
      printk("<----- WscWriteConfToDatFile\n");
    }
  }
  return;
}

