// module: mt7915.ko
// function: WscCreateProfileFromCfg @ 0x1e8e94
// size: 1812 bytes
//

void WscCreateProfileFromCfg(int param_1,uint param_2,int param_3,undefined4 *param_4)

{
  char cVar1;
  uint uVar2;
  bool bVar3;
  undefined *puVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;
  char *__s;
  byte *pbVar8;
  int iVar9;
  uint local_34;
  undefined2 local_30;
  
  uVar5 = *(byte *)(param_3 + 0x1c54) & 0xf;
  if (*(byte *)(param_3 + 0x1c54) == 0 && *(char *)(param_1 + 0x286285) == '\0') {
    bVar3 = true;
    local_30 = WscGetAuthType(*(undefined4 *)(&DAT_0036db84 + param_1));
    local_34 = WscGetEncryType(*(undefined4 *)(&DAT_0036dccc + param_1));
    uVar7 = (uint)(byte)(&DAT_0036ddb0)[param_1];
  }
  else {
    if ((param_2 & 0xf) == 0) {
      if ((*(char *)(param_3 + 8) == '\x01') ||
         (uVar7 = *(uint *)(
                           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           + uVar5 * 0x5834 + param_1 + 0x10c), (uVar7 & 0x90) == 0x90)) {
        if ((param_2 & 0x40) == 0) {
          uVar7 = *(uint *)(
                           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           + uVar5 * 0x5834 + param_1 + 0x10c);
          goto LAB_001e9028;
        }
        if (*(uint *)("!!! Link UP, Port Not Secured! ignore this set::OID_802_11_BSSID_LIST_SCAN\n"
                     + uVar5 * 0x5834 + param_1 + 0x44) < 4) {
          iVar9 = *(uint *)(
                           "!!! Link UP, Port Not Secured! ignore this set::OID_802_11_BSSID_LIST_SCAN\n"
                           + uVar5 * 0x5834 + param_1 + 0x44) * 2;
          local_30 = *(undefined2 *)(&DAT_002a115c + iVar9);
          local_34 = (uint)*(ushort *)(&DAT_002a1164 + iVar9);
        }
        else {
          local_34 = 0xc;
          local_30 = 0x22;
        }
        if (*(char *)(param_3 + 8) == '\x02') {
          if ((*(uint *)(
                        "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + uVar5 * 0x5834 + param_1 + 0x254) & 0x10) != 0) {
            local_34 = 4;
          }
          if ((*(uint *)(
                        "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + uVar5 * 0x5834 + param_1 + 0x254) & 0x20) != 0) {
            local_34 = local_34 | 8;
          }
        }
      }
      else {
LAB_001e9028:
        local_30 = WscGetAuthType(uVar7);
        local_34 = WscGetEncryType(*(undefined4 *)
                                    (
                                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                    + uVar5 * 0x5834 + param_1 + 0x254));
      }
      uVar7 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          [uVar5 * 0x5834 + param_1 + 0x338];
    }
    else {
      uVar7 = uVar5;
      if (uVar5 < 2) {
        uVar7 = param_2;
      }
      if (uVar7 == 1) {
        iVar9 = param_1 + uVar5 * 0x2137b0;
        local_30 = WscGetAuthType(*(undefined4 *)(&DAT_0036db84 + iVar9));
        local_34 = WscGetEncryType(*(undefined4 *)(&DAT_0036dccc + iVar9));
        uVar7 = (uint)(byte)(&DAT_0036ddb0)[iVar9];
      }
      else {
        uVar7 = 0;
        local_34 = 0;
        local_30 = 0;
      }
    }
    bVar3 = false;
  }
  if (2 < DebugLevel) {
    printk("-----> WscGetDefaultProfileForM8\n");
  }
  __memzero(param_4 + 2,0x74);
  *param_4 = 1;
  if (2 < DebugLevel) {
    printk("%s:: pWscControl->WscConfStatus  = %d, OpMode = %d\n","WscCreateProfileFromCfg",
           *(undefined1 *)(param_3 + 8),param_2);
  }
  if (*(char *)(param_3 + 8) == '\x01') {
    if ((param_2 & 0xf) != 0) {
      if ((((param_2 & 0xf) != 2) ||
          (s__RB_FULL__Free_Queue_List___00371ba4[param_1 + 0x14] != '\0')) ||
         ((param_2 & 0x40) == 0)) goto LAB_001e8f3c;
      *(undefined1 *)(param_4 + 0x1e) = 1;
      WscGenRandomKey(param_1,param_3,param_4 + 0xc,param_4 + 0x1c);
      *(undefined2 *)(param_4 + 0xb) = 0x20;
      *(undefined2 *)((int)param_4 + 0x2e) = 8;
      if (bVar3) goto LAB_001e9250;
      goto LAB_001e90b8;
    }
    if ((param_2 & 0x40) == 0) goto LAB_001e8f3c;
    *(undefined1 *)(param_4 + 0x1e) = 1;
    WscGenRandomKey(param_1,param_3,param_4 + 0xc,param_4 + 0x1c);
    *(undefined2 *)(param_4 + 0xb) = local_30;
    *(undefined2 *)((int)param_4 + 0x2e) = (undefined2)local_34;
    if (bVar3) goto LAB_001e9250;
  }
  else {
LAB_001e8f3c:
    __s = (char *)(param_4 + 0xc);
    *(undefined1 *)(param_4 + 0x1e) = 1;
    *(undefined2 *)(param_4 + 0x1c) = 0;
    __memzero(__s,0x40);
    switch(local_34) {
    case 2:
      cVar1 = (char)uVar7;
      if (!bVar3) {
        uVar2 = uVar5;
        if (uVar5 < 2) {
          uVar2 = param_2;
        }
        if (uVar2 == 1) {
          pcVar6 = &DAT_0036db84 + param_1 + uVar5 * 0x2137b0;
        }
        else {
          pcVar6 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   + uVar5 * 0x5834 + param_1 + 0x10c;
        }
LAB_001e9124:
        *(char *)(param_4 + 0x1e) = cVar1 + '\x01';
        if (pcVar6 != (char *)0x0) goto LAB_001e9134;
        goto switchD_001e8f68_caseD_3;
      }
      uVar2 = uVar5;
      if (uVar5 < 2) {
        uVar2 = param_2;
      }
      if (uVar2 == 1) {
        pcVar6 = &DAT_0036db84 + param_1 + uVar5 * 0x2137b0;
        if (!bVar3) goto LAB_001e9124;
      }
      else if (!bVar3) {
        *(char *)(param_4 + 0x1e) = cVar1 + '\x01';
        break;
      }
      pcVar6 = &DAT_0036db84 + param_1;
      *(char *)(param_4 + 0x1e) = cVar1 + '\x01';
      if (pcVar6 != (char *)0x0) {
LAB_001e9134:
        if (pcVar6[uVar7 * 0x51 + 0x54] != '\0') {
          iVar9 = 0;
          pbVar8 = (byte *)(pcVar6 + uVar7 * 0x51 + 3);
          do {
            pbVar8 = pbVar8 + 1;
            iVar9 = iVar9 + 1;
            snprintf(__s,0x40,"%s%02x",__s,(uint)*pbVar8);
          } while (iVar9 < (int)(uint)(byte)pcVar6[uVar7 * 0x51 + 0x54]);
          *(ushort *)(param_4 + 0x1c) = (ushort)(byte)pcVar6[uVar7 * 0x51 + 0x54] << 1;
          break;
        }
        goto switchD_001e8f68_caseD_3;
      }
      *(undefined2 *)(param_4 + 0xb) = local_30;
      *(undefined2 *)((int)param_4 + 0x2e) = 2;
      goto LAB_001e925c;
    default:
switchD_001e8f68_caseD_3:
      break;
    case 4:
    case 8:
    case 0xc:
      *(short *)(param_4 + 0x1c) = (short)*(undefined4 *)(param_3 + 0x29e0);
      memcpy(__s,(void *)(param_3 + 0x299d),*(size_t *)(param_3 + 0x29e0));
    }
    *(undefined2 *)(param_4 + 0xb) = local_30;
    *(undefined2 *)((int)param_4 + 0x2e) = (undefined2)local_34;
    if (bVar3) {
LAB_001e9250:
      if (bVar3) {
LAB_001e925c:
        if (s__RB_FULL__Free_Queue_List___00371ba4[param_1 + 0x14] == '\x01') {
          puVar4 = &DAT_0057ff80;
        }
        else {
          puVar4 = &DAT_0036db73;
        }
        memmove((void *)((int)param_4 + 0x72),puVar4 + param_1,6);
        memmove(param_4 + 3,(void *)(param_1 + 0x57ff5e),(uint)(byte)(&DAT_0057ff7e)[param_1]);
        param_4[2] = (uint)(byte)(&DAT_0057ff7e)[param_1];
      }
      goto LAB_001e90c8;
    }
    if ((param_2 & 0xf) != 0) {
LAB_001e90b8:
      uVar7 = uVar5;
      if (uVar5 < 2) {
        uVar7 = param_2;
      }
      if (uVar7 == 1) {
        iVar9 = param_1 + uVar5 * 0x2137b0;
        memmove((void *)((int)param_4 + 0x72),
                (void *)((uint)*(ushort *)(&DAT_00580e38 + iVar9) * 0x14c0 + param_1 + 0xa1e0c),6);
        memmove(param_4 + 3,(void *)(param_1 + uVar5 * 0x2137b0 + 0x57ff5e),
                (uint)(byte)(&DAT_0057ff7e)[iVar9]);
        param_4[2] = (uint)(byte)(&DAT_0057ff7e)[iVar9];
      }
      goto LAB_001e90c8;
    }
  }
  memmove((void *)((int)param_4 + 0x72),
          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          + uVar5 * 0x5834 + param_1 + 0x101,6);
  if ((*(char *)(param_3 + 8) == '\x01') && (*(size_t *)(param_3 + 0x29f5) - 1 < 0x20)) {
    memmove(param_4 + 3,(void *)(param_3 + 0x29f9),*(size_t *)(param_3 + 0x29f5));
    param_4[2] = *(undefined4 *)(param_3 + 0x29f5);
  }
  else {
    iVar9 = param_1 + uVar5 * 0x5834;
    memmove(param_4 + 3,
            "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n" +
            param_1 + uVar5 * 0x5834 + 0x34,(uint)(byte)"pStaCfg->WpaPassPhrase"[iVar9 + 5]);
    param_4[2] = (uint)(byte)"pStaCfg->WpaPassPhrase"[iVar9 + 5];
  }
LAB_001e90c8:
  if ((*(char *)(param_3 + 0x2b31) != '\0') && ((param_2 & 0x40) != 0)) {
    memmove((void *)((int)param_4 + 0x72),(void *)(param_3 + 0x1c55),6);
  }
  if (2 < DebugLevel) {
    printk("<----- WscCreateProfileFromCfg\n");
    return;
  }
  return;
}

