// module: mt7915.ko
// function: SetPartProfileParameters @ 0xef564
// size: 3692 bytes
//

undefined4 SetPartProfileParameters(int param_1,undefined4 param_2)

{
  byte bVar1;
  undefined1 uVar2;
  char cVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  uint uVar11;
  char *pcVar12;
  undefined *puVar13;
  uint uVar14;
  byte *pbVar15;
  char *local_2c [2];
  
  os_alloc_mem(0,local_2c,0x800);
  if (local_2c[0] == (char *)0x0) {
    return 1;
  }
  if (3 < DebugLevel) {
    printk(&_LC22,"SetPartProfileParameters");
  }
  cVar3 = '\0';
  iVar5 = RTMPGetKeyParameter("AutoChannelSkipList",local_2c[0],0x80,param_2,0);
  pcVar12 = local_2c[0];
  pcVar7 = local_2c[0];
  if (iVar5 != 0) {
    while( true ) {
      pcVar7 = strchr(pcVar7,0x3b);
      if (pcVar7 == (char *)0x0) break;
      cVar3 = cVar3 + '\x01';
      pcVar7 = pcVar7 + 1;
    }
    (&DAT_0036b862)[param_1] = cVar3 + '\x01';
    iVar5 = rstrtok(pcVar12,&_LC6);
    if ((iVar5 != 0) && ((&DAT_0036b862)[param_1] != '\0')) {
      puVar13 = &DAT_0036b862 + param_1;
      iVar6 = 0;
      do {
        uVar2 = os_str_tol(iVar5,0,10);
        iVar6 = iVar6 + 1;
        puVar13 = puVar13 + 1;
        *puVar13 = uVar2;
        iVar5 = rstrtok(0,&_LC6);
        if (iVar5 == 0) break;
      } while (iVar6 < (int)(uint)(byte)(&DAT_0036b862)[param_1]);
    }
  }
  iVar5 = RTMPGetKeyParameter("CountryRegion",local_2c[0],0x19,param_2,1);
  if (iVar5 != 0) {
    RT_CfgSetCountryRegion(param_1,local_2c[0],2);
  }
  iVar5 = RTMPGetKeyParameter("CountryRegionABand",local_2c[0],0x19,param_2,1);
  if (iVar5 != 0) {
    RT_CfgSetCountryRegion(param_1,local_2c[0],1);
  }
  if ((*(char *)(param_1 + 0x794c30) == '\0') &&
     (iVar5 = RTMPGetKeyParameter("CountryCode",local_2c[0],0x19,param_2,1), iVar5 != 0)) {
    RTMPSetCountryCode(param_1,local_2c[0]);
  }
  iVar5 = RTMPGetKeyParameter("WirelessMode",local_2c[0],0x80,param_2,1);
  if (iVar5 != 0) {
    FUN_000ee450(param_1,local_2c[0]);
  }
  iVar5 = RTMPGetKeyParameter("Channel",local_2c[0],0x80,param_2,1);
  if (iVar5 != 0) {
    FUN_000ee7ac(param_1,local_2c[0]);
  }
  iVar5 = RTMPGetKeyParameter("BeaconPeriod",local_2c[0],0x80,param_2,1);
  if (iVar5 != 0) {
    uVar4 = os_str_tol(local_2c[0],0,10);
    if (uVar4 - 0x14 < 0x3d5) {
      *(ushort *)(&DAT_00794c50 + param_1) = uVar4;
    }
    else {
      *(ushort *)(&DAT_00794c50 + param_1) = 100;
    }
  }
  iVar5 = RTMPGetKeyParameter("TxPower",local_2c[0],10,param_2,1);
  if (iVar5 != 0) {
    iVar5 = rstrtok(local_2c[0],&_LC6);
    if (iVar5 != 0) {
      iVar6 = 0;
      do {
        if (*(char *)(param_1 + 0x79504d) == '\0') {
          if (iVar6 == 0) {
LAB_000f014c:
            uVar2 = simple_strtol(iVar5,iVar6,10);
            *(undefined1 *)(param_1 + 0x794cd8) = uVar2;
          }
        }
        else {
          if (iVar6 == 0) goto LAB_000f014c;
          if (iVar6 == 1) {
            uVar2 = simple_strtol(iVar5,0,10);
            *(undefined1 *)(param_1 + 0x794cd9) = uVar2;
          }
        }
        iVar6 = iVar6 + 1;
        iVar5 = rstrtok(0,&_LC6);
      } while (iVar5 != 0);
    }
    if (*(char *)(param_1 + 0x286285) == '\0') {
      *(undefined1 *)(param_1 + 0x795041) = *(undefined1 *)(param_1 + 0x794cd8);
      *(undefined1 *)(param_1 + 0x795042) = *(undefined1 *)(param_1 + 0x794cd9);
    }
  }
  iVar5 = RTMPGetKeyParameter("HT_BW",local_2c[0],0x40,param_2,1);
  if (iVar5 != 0) {
    cVar3 = os_str_tol(local_2c[0],0,10);
    wlan_config_set_ht_bw_all(param_1 + 0xa7c558,cVar3);
    if (3 < DebugLevel) {
      pcVar12 = "40 MHz";
      if (cVar3 != '\x01') {
        pcVar12 = "20 MHz";
      }
      printk("HT: Channel Width = %s\n",pcVar12);
    }
    if ((*(char *)(param_1 + 0x286285) == '\x01') &&
       (iVar5 = rstrtok(local_2c[0],&_LC6), iVar5 != 0)) {
      pbVar15 = (byte *)(param_1 + 0x3678c7);
      iVar6 = 0;
      do {
        iVar9 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        if (iVar9 <= iVar6) break;
        pbVar15 = pbVar15 + 1;
        bVar1 = *pbVar15;
        uVar4 = os_str_tol(iVar5,0,10);
        wlan_config_set_ht_bw
                  ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   + param_1 + (uint)bVar1 * 0x5834 + 0xe0,uVar4 & 0xff);
        iVar5 = param_1 + (uint)bVar1 * 0x5834;
        *(ushort *)
         (
         "Wrong format, vow_watf_q=[Level]-[Quantum]\n[Level] should be among 0 to 3 !\n[Quantum] unit is 256us.\n"
         + iVar5 + 100) =
             *(ushort *)
              (
              "Wrong format, vow_watf_q=[Level]-[Quantum]\n[Level] should be among 0 to 3 !\n[Quantum] unit is 256us.\n"
              + iVar5 + 100) & 0xfe7f | (uVar4 & 3) << 7;
        iVar5 = rstrtok(0,&_LC6);
        iVar6 = iVar6 + 1;
      } while (iVar5 != 0);
    }
  }
  iVar5 = RTMPGetKeyParameter("HT_STBC",local_2c[0],0x80,param_2,1);
  if ((iVar5 != 0) && (iVar5 = rstrtok(local_2c[0],&_LC6), iVar5 != 0)) {
    cVar3 = '\0';
    do {
      uVar2 = os_str_tol(iVar5,0,10);
      iVar5 = FUN_000ee05c(param_1,cVar3);
      if (iVar5 != 0) {
        wlan_config_set_ht_stbc(iVar5,uVar2);
      }
      iVar5 = rstrtok(0,&_LC6);
      cVar3 = cVar3 + '\x01';
    } while (iVar5 != 0);
  }
  iVar5 = RTMPGetKeyParameter("HT_BSSCoexistence",local_2c[0],0x19,param_2,1);
  if (iVar5 == 0) {
    uVar11 = 0;
  }
  else {
    uVar11 = os_str_tol(local_2c[0],0,10);
    iVar5 = DebugLevel;
    *(bool *)(param_1 + 0x79564e) = uVar11 == 1;
    if (3 < iVar5) {
      printk("HT: 20/40 BssCoexSupport = %d\n",uVar11);
    }
  }
  cVar3 = '\0';
  iVar5 = RTMPGetKeyParameter("HT_GI",local_2c[0],0x80,param_2,0);
  if (iVar5 != 0) {
    iVar5 = rstrtok(local_2c[0],&_LC6);
    while (iVar5 != 0) {
      uVar2 = os_str_tol(iVar5,0,10);
      if (3 < DebugLevel) {
        printk("HT_GI = %d\n",uVar2);
      }
      iVar5 = FUN_000ee05c(param_1,cVar3);
      cVar3 = cVar3 + '\x01';
      if (iVar5 != 0) {
        wlan_config_set_ht_gi(iVar5,uVar2);
      }
      iVar5 = rstrtok(0,&_LC6);
    }
  }
  iVar5 = RTMPGetKeyParameter("HT_AutoBA",local_2c[0],0x40,param_2,1);
  if (iVar5 != 0) {
    iVar5 = rstrtok(local_2c[0],&_LC6);
    if (iVar5 != 0) {
      cVar3 = '\0';
      do {
        uVar11 = os_str_tol(iVar5,0,10);
        iVar5 = FUN_000ee05c(param_1,cVar3);
        if (iVar5 != 0) {
          wlan_config_set_ba_enable(iVar5,uVar11 & 0xff);
        }
        iVar5 = rstrtok(0,&_LC6);
        cVar3 = cVar3 + '\x01';
      } while (iVar5 != 0);
    }
    if (3 < DebugLevel) {
      pcVar12 = "Disable";
      if (uVar11 != 0) {
        pcVar12 = "Enable";
      }
      printk("HT: Auto BA  = %s\n",pcVar12);
    }
  }
  iVar5 = RTMPGetKeyParameter("VHT_BW",local_2c[0],0x40,param_2,1);
  if ((iVar5 != 0) && (iVar5 = rstrtok(local_2c[0],&_LC6), iVar5 != 0)) {
    uVar11 = 0;
    do {
      uVar14 = 0;
      uVar8 = os_str_tol(iVar5,0,10);
      if (((uVar8 < 4) && (uVar14 = uVar8 & 0xff, *(char *)(param_1 + 0x79504d) != '\0')) &&
         (1 < (int)uVar8)) {
        uVar14 = 1;
      }
      iVar5 = FUN_000ee05c(param_1,uVar11 & 0xff);
      if (iVar5 != 0) {
        wlan_config_set_vht_bw(iVar5,uVar14);
      }
      if (3 < DebugLevel) {
        uVar10 = VhtBw2Str(uVar14);
        printk("wdev[%d] VHT: Channel Width = %s MHz\n",uVar11,uVar10);
      }
      uVar11 = uVar11 + 1;
      iVar5 = rstrtok(0,&_LC6);
    } while (iVar5 != 0);
  }
  iVar5 = RTMPGetKeyParameter("VHT_SGI",local_2c[0],0x80,param_2,1);
  if ((iVar5 != 0) && (iVar5 = rstrtok(local_2c[0],&_LC6), iVar5 != 0)) {
    cVar3 = '\0';
    do {
      uVar2 = os_str_tol(iVar5,0,10);
      iVar5 = FUN_000ee05c(param_1,cVar3);
      if (iVar5 != 0) {
        wlan_config_set_vht_sgi(iVar5,uVar2);
      }
      iVar5 = rstrtok(0,&_LC6);
      cVar3 = cVar3 + '\x01';
    } while (iVar5 != 0);
  }
  iVar5 = RTMPGetKeyParameter("RTSThreshold",local_2c[0],0x80,param_2,0);
  if (iVar5 != 0) {
    if (*(char *)(param_1 + 0x79504d) == '\0') {
      iVar5 = os_str_tol(local_2c[0],0,10);
      if (0xffffe < iVar5 - 1U) {
        iVar5 = 0xfffff;
      }
      if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda] != '\0') {
        uVar11 = 0;
        do {
          wlan_config_set_rts_len_thld
                    ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                     + (uint)(byte)(&DAT_003678c8)[param_1 + uVar11] * 0x5834 + param_1 + 0xe0,iVar5
                    );
          if (3 < DebugLevel) {
            printk("mbss[idx=%d], RTSThreshold[%d]=%d\n",uVar11,uVar11,iVar5);
          }
          uVar11 = uVar11 + 1 & 0xff;
        } while (uVar11 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                [param_1 + 0xda]);
      }
    }
    else {
      iVar5 = rstrtok(local_2c[0],&_LC6);
      cVar3 = '\0';
      while (iVar5 != 0) {
        iVar5 = os_str_tol(iVar5,0,10);
        if (0xffffe < iVar5 - 1U) {
          iVar5 = 0xfffff;
        }
        iVar6 = FUN_000ee05c(param_1,cVar3);
        if (iVar6 != 0) {
          wlan_config_set_rts_len_thld(iVar6,iVar5);
        }
        iVar5 = rstrtok(0,&_LC6);
        cVar3 = cVar3 + '\x01';
      }
    }
  }
  cVar3 = '\0';
  iVar5 = RTMPGetKeyParameter("FragThreshold",local_2c[0],0x80,param_2,0);
  if (iVar5 != 0) {
    iVar5 = rstrtok(local_2c[0],&_LC6);
    while (iVar5 != 0) {
      uVar11 = os_str_tol(iVar5,0,10);
      if (uVar11 - 0x100 < 0x82b) {
        if ((uVar11 & 1) != 0) {
          uVar11 = uVar11 - 1;
        }
      }
      else {
        uVar11 = 0x92a;
      }
      iVar5 = FUN_000ee05c(param_1,cVar3);
      cVar3 = cVar3 + '\x01';
      if (iVar5 != 0) {
        wlan_config_set_frag_thld(iVar5,uVar11);
      }
      iVar5 = rstrtok(0,&_LC6);
    }
  }
  iVar5 = RTMPGetKeyParameter("HT_EXTCHA",local_2c[0],0x40,param_2,1);
  if (iVar5 != 0) {
    iVar5 = os_str_tol(local_2c[0],0,10);
    if (*(char *)(param_1 + 0x286285) == '\0') {
      puVar13 = &DAT_0036db58 + param_1;
      if (iVar5 == 0) {
        uVar10 = 3;
      }
      else {
        uVar10 = 1;
      }
      wlan_config_set_ext_cha(puVar13,uVar10);
      iVar6 = wlan_config_get_ext_cha(puVar13);
      if (iVar6 == 0xf) {
        wlan_config_set_ext_cha(puVar13,uVar10);
      }
      iVar6 = wlan_config_get_ext_cha(&DAT_00581308 + param_1);
      if (iVar6 == 0xf) {
        wlan_config_set_ext_cha(&DAT_00581308 + param_1,uVar10);
      }
      if (3 < DebugLevel) {
        pcVar12 = "BELOW";
        if (iVar5 != 0) {
          pcVar12 = "ABOVE";
        }
        printk("HT: Ext Channel = %s\n",pcVar12);
      }
    }
    iVar5 = rstrtok(local_2c[0],&_LC6);
    if (iVar5 != 0) {
      pbVar15 = &DAT_003678c8 + param_1;
      iVar6 = 0;
      do {
        iVar9 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        if (iVar9 <= iVar6) break;
        iVar5 = os_str_tol(iVar5,0,10);
        if (*(char *)(param_1 + 0x286285) == '\x01') {
          if (iVar5 == 0) {
            wlan_config_set_ext_cha
                      ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + (uint)*pbVar15 * 0x5834 + param_1 + 0xe0,3);
            if (3 < DebugLevel) {
              pcVar12 = "BELOW";
LAB_000efe2c:
              printk("HT: WDEV[%x] Ext Channel = %s\n",iVar6,pcVar12);
            }
          }
          else {
            wlan_config_set_ext_cha
                      ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + (uint)*pbVar15 * 0x5834 + param_1 + 0xe0);
            if (3 < DebugLevel) {
              pcVar12 = "ABOVE";
              goto LAB_000efe2c;
            }
          }
        }
        iVar6 = iVar6 + 1;
        iVar5 = rstrtok(0,&_LC6);
        pbVar15 = pbVar15 + 1;
      } while (iVar5 != 0);
    }
    uVar10 = wlan_config_get_ext_cha
                       ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + param_1 + 0xe0);
    if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
        [param_1 + 0xda] != '\0') {
      iVar5 = 0;
      pbVar15 = (byte *)(param_1 + 0x3678c7);
      do {
        pbVar15 = pbVar15 + 1;
        bVar1 = *pbVar15;
        iVar5 = iVar5 + 1;
        iVar6 = wlan_config_get_ext_cha
                          ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           + (uint)bVar1 * 0x5834 + param_1 + 0xe0);
        if (iVar6 == 0xf) {
          wlan_config_set_ext_cha
                    ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                     + (uint)bVar1 * 0x5834 + param_1 + 0xe0,uVar10);
        }
      } while (iVar5 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                        [param_1 + 0xda]);
    }
  }
  iVar5 = RTMPGetKeyParameter("IEEE80211H",local_2c[0],10,param_2,1);
  if (iVar5 != 0) {
    iVar5 = rstrtok(local_2c[0],&_LC6);
    while (iVar5 != 0) {
      iVar6 = os_str_tol(iVar5,0,10);
      iVar5 = DebugLevel;
      if (iVar6 == 0) {
        *(undefined1 *)(param_1 + 0x795074) = 0;
        *(undefined1 *)(param_1 + 0xa79631) = 0;
        *(undefined1 *)(param_1 + 0x7953ef) = 0;
        *(undefined1 *)(param_1 + 0x7953f6) = 0;
      }
      else {
        *(undefined1 *)(param_1 + 0x795074) = 1;
        iVar5 = DebugLevel;
      }
      if (3 < iVar5) {
        printk("IEEE80211H=%d\n",*(undefined1 *)(param_1 + 0x795074));
      }
      iVar5 = rstrtok(0,&_LC6);
    }
  }
  iVar5 = RTMPGetKeyParameter("DfsEnable",local_2c[0],0x19,param_2,1);
  if (iVar5 != 0) {
    uVar2 = os_str_tol(local_2c[0],0,10);
    *(undefined1 *)(param_1 + 0x7953ef) = uVar2;
  }
  os_free_mem(local_2c[0]);
  return 0;
}

