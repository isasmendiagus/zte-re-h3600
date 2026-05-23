// module: mt7915.ko
// function: WscWriteConfToPortCfg @ 0x1e5fcc
// size: 2064 bytes
//

void WscWriteConfToPortCfg(int param_1,int param_2,size_t *param_3,int param_4)

{
  bool bVar1;
  char cVar2;
  size_t sVar3;
  undefined4 uVar4;
  uint uVar5;
  char *pcVar6;
  byte bVar7;
  ushort uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  char *pcVar12;
  int *piVar13;
  undefined1 *puVar14;
  undefined1 *puVar15;
  bool bVar16;
  uint local_7c;
  undefined1 auStack_69 [69];
  
  if (2 < DebugLevel) {
    printk("-----> WscWriteConfToPortCfg\n");
  }
  if (*(char *)(param_1 + 0x286285) == '\0') {
    local_7c = (uint)*(byte *)(param_2 + 0x1c54);
    if (local_7c != 0) goto LAB_001e6020;
    if (param_4 != 0) {
      (&DAT_00371cb8)[param_1] = (char)*param_3;
      __memzero((void *)(param_1 + 0x371c98),0x20);
      memmove((void *)(param_1 + 0x371c98),param_3 + 1,(uint)(byte)(&DAT_00371cb8)[param_1]);
      (&DAT_00371c91)[param_1] = (char)*param_3;
      __memzero(s_patch_common_sys_patch_common_mc_00371c50 + param_1 + 0x21,0x20);
      memmove(s_patch_common_sys_patch_common_mc_00371c50 + param_1 + 0x21,param_3 + 1,
              (uint)(byte)(&DAT_00371c91)[param_1]);
      iVar10 = memcmp((void *)((int)param_3 + 0x6a),&DAT_0036db73 + param_1,6);
      if (iVar10 == 0) {
        cVar2 = '\x02';
        bVar1 = false;
        local_7c = 0;
      }
      else {
        cVar2 = '\x02';
        __memzero(&DAT_00371c92 + param_1,6);
        memmove(&DAT_00371c92 + param_1,(void *)((int)param_3 + 0x6a),6);
        bVar1 = false;
        local_7c = 0;
      }
      goto LAB_001e6084;
    }
    local_7c = 0;
  }
  else {
    local_7c = (uint)*(byte *)(param_2 + 0x1c54);
LAB_001e6020:
    local_7c = local_7c & 0xf;
    cVar2 = '\0';
    bVar1 = true;
    __memzero("Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n" +
              param_1 + local_7c * 0x5834 + 0x34,0x20);
    memmove("Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n" +
            param_1 + local_7c * 0x5834 + 0x34,param_3 + 1,*param_3);
    "pStaCfg->WpaPassPhrase"[param_1 + local_7c * 0x5834 + 5] = (char)*param_3;
LAB_001e6084:
    if (2 < DebugLevel) {
      printk("ra%d - AuthType: %u, EncrType: %u\n",local_7c,(short)param_3[9],
             *(undefined2 *)((int)param_3 + 0x26));
    }
    if ((param_3[9] & 0xa2) == 0) {
      uVar4 = WscGetAuthTypeStr();
      if (bVar1) {
LAB_001e620c:
        piVar13 = (int *)(param_1 + 0xa1d20);
        uVar9 = 0;
        SetWdevAuthMode("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + local_7c * 0x5834 + param_1 + 0x10c,uVar4);
        puVar14 = (undefined1 *)(param_1 + 0x2f762);
        while( true ) {
          puVar15 = puVar14;
          uVar5 = HcGetMaxStaNum(param_1);
          iVar10 = DebugLevel;
          bVar16 = uVar5 <= uVar9;
          uVar9 = uVar9 + 1;
          if (bVar16) break;
          iVar10 = *piVar13;
          puVar14 = puVar15 + 0x620;
          piVar13 = piVar13 + 0x530;
          if (iVar10 == 0x20001) {
            *puVar15 = 2;
          }
        }
        iVar11 = local_7c * 0x5834 + param_1;
        "%s: group %d, band %u.\n"[iVar11 + 0x10] = '\x02';
        if (2 < iVar10) {
          printk("IF(ra%d) %s::(AuthMode=0x%x)\n",local_7c,"WscSetAuthMode",
                 *(undefined4 *)
                  (
                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + iVar11 + 0x10c));
        }
      }
      else if (cVar2 == '\x02') goto LAB_001e63a4;
LAB_001e60bc:
      uVar8 = *(ushort *)((int)param_3 + 0x26);
      uVar9 = (uint)(ushort)(uVar8 - 1);
      if (uVar9 < 8) {
LAB_001e60d8:
        pcVar6 = *(char **)(&DAT_002a10d8 + uVar9 * 4);
      }
      else {
        pcVar6 = "TKIPAES";
      }
      if (bVar1) {
        SetWdevEncrypMode("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          + param_1 + local_7c * 0x5834 + 0x10c,pcVar6);
        if (2 < DebugLevel) {
          printk("IF(ra%d) %s::(EncrypType=0x%x)\n",local_7c,"WscSetEncrypType",
                 *(undefined4 *)
                  (
                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + param_1 + local_7c * 0x5834 + 0x254));
        }
        uVar8 = *(ushort *)((int)param_3 + 0x26);
        if (uVar8 != 1) {
          if ((uVar8 & 0xc) != 0) goto LAB_001e6498;
          goto LAB_001e6440;
        }
        goto LAB_001e6448;
      }
      if (cVar2 == '\x02') goto LAB_001e63fc;
      if (uVar8 == 1) goto LAB_001e6164;
      if ((uVar8 & 0xc) == 0) goto LAB_001e6440;
      pcVar12 = (char *)0x0;
LAB_001e6118:
      iVar10 = DebugLevel;
      sVar3 = param_3[0x1a];
      if ((ushort)sVar3 - 8 < 0x39) {
        param_3 = param_3 + 10;
        memset(auStack_69,0,0x41);
        *(uint *)(param_2 + 0x29e0) = (uint)(ushort)sVar3;
        RTMPZeroMemory(param_2 + 0x299d,0x40);
        RTMPMoveMemory(param_2 + 0x299d,param_3,*(undefined4 *)(param_2 + 0x29e0));
        RTMPMoveMemory(auStack_69,param_3,*(undefined4 *)(param_2 + 0x29e0));
        RTMPZeroMemory(pcVar12 + 0x179,0x41);
        RTMPMoveMemory(pcVar12 + 0x179,param_3,*(undefined4 *)(param_2 + 0x29e0));
        if (2 < DebugLevel) {
          printk("WpaPskLen = %d\n",*(undefined4 *)(param_2 + 0x29e0));
        }
      }
      else {
        *(undefined4 *)(param_2 + 0x29e0) = 0;
        if (iVar10 < 3) {
LAB_001e6144:
          if (cVar2 != '\x02') {
            return;
          }
          goto LAB_001e6150;
        }
        printk("WPAPSK: Invalid Key Length (%d)\n",(short)param_3[0x1a]);
      }
    }
    else {
      if ((*(ushort *)((int)param_3 + 0x26) & 0xc) == 0) {
        if (2 < DebugLevel) {
          printk(
                "AuthType is WPAPSK or WPA2PAK.\nGet illegal EncrType(%d) from External Registrar, set EncrType to TKIP\n"
                );
        }
        *(undefined2 *)((int)param_3 + 0x26) = 4;
      }
      if (cVar2 == '\x02') {
        (&DAT_00580311)[param_1] = 1;
      }
      else if (bVar1) {
        if (*(char *)(param_2 + 0x2b31) != '\0') {
          if ((short)param_3[9] == 2) {
            *(undefined2 *)(param_3 + 9) = 0x22;
          }
          if (*(short *)((int)param_3 + 0x26) == 4) {
            *(undefined2 *)((int)param_3 + 0x26) = 0xc;
          }
        }
        uVar4 = WscGetAuthTypeStr();
        goto LAB_001e620c;
      }
      uVar4 = WscGetAuthTypeStr((short)param_3[9]);
      if (cVar2 != '\x02') goto LAB_001e60bc;
LAB_001e63a4:
      SetWdevAuthMode(&DAT_0036db84 + param_1,uVar4);
      iVar10 = DebugLevel;
      (&DAT_0036e3e0)[param_1] = cVar2;
      if (2 < iVar10) {
        printk("WscSetAuthMode::(AuthMode=0x%x)\n",*(undefined4 *)(&DAT_0036db84 + param_1));
      }
      uVar8 = *(ushort *)((int)param_3 + 0x26);
      uVar9 = (uint)(ushort)(uVar8 - 1);
      if (uVar9 < 8) goto LAB_001e60d8;
      pcVar6 = "TKIPAES";
LAB_001e63fc:
      pcVar12 = &DAT_0036db58 + param_1;
      SetWdevEncrypMode(&DAT_0036db84 + param_1,pcVar6);
      if (2 < DebugLevel) {
        printk("WscSetEncrypType::(EncrypType=0x%x)\n",*(undefined4 *)(&DAT_0036dccc + param_1));
      }
      uVar8 = *(ushort *)((int)param_3 + 0x26);
      if (uVar8 == 1) goto LAB_001e6150;
      if ((uVar8 & 0xc) != 0) {
        if (bVar1) {
LAB_001e6498:
          pcVar12 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + param_1 + local_7c * 0x5834 + 0xe0;
          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + local_7c * 0x5834 + 600] = '\x01';
        }
        else {
          (&DAT_0036dcd0)[param_1] = 0;
        }
        goto LAB_001e6118;
      }
LAB_001e6440:
      if (uVar8 != 2) goto LAB_001e6448;
      sVar3 = param_3[0x1a];
      bVar7 = (char)param_3[0x1c] - 1;
      if (3 < bVar7) {
        if (2 < DebugLevel) {
          printk("Unsupport default key index (%d)\n",0);
        }
        if (bVar1) {
          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [local_7c * 0x5834 + param_1 + 600] = '\0';
          goto LAB_001e6164;
        }
        if (cVar2 != '\x02') goto LAB_001e6164;
        (&DAT_0036dcd0)[param_1] = 0;
        goto LAB_001e6150;
      }
      if (bVar1) {
        pcVar6 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + local_7c * 0x5834 + param_1 + 0x10c;
      }
      else if (cVar2 == '\x02') {
        pcVar6 = &DAT_0036db84 + param_1;
      }
      else {
        pcVar6 = (char *)0x0;
      }
      pcVar6[0x14c] = bVar7;
      if (((sVar3 & 0xfff7) == 5) || ((sVar3 & 0xffef) == 10)) {
        FUN_001e0784(pcVar6,param_3);
      }
      else {
        if (DebugLevel < 3) goto LAB_001e6144;
        printk("WEP: Invalid Key Length (%d)\n",(short)param_3[0x1a]);
      }
    }
LAB_001e6448:
    if (cVar2 != '\x02') goto LAB_001e6164;
  }
LAB_001e6150:
  if (((s__RB_FULL__Free_Queue_List___00371ba4[param_1 + 0x14] == '\x01') &&
      (*(char *)(param_2 + 0x2920) == '\x02')) && (*(int *)(param_2 + 0x1c90) != 0)) {
    *(undefined1 *)(param_2 + 0x2874) = 1;
    RTMPSetTimer(param_2 + 0x2878,10000);
  }
LAB_001e6164:
  if (2 < DebugLevel) {
    printk("<----- ra%d - WscWriteConfToPortCfg\n",local_7c);
  }
  return;
}

