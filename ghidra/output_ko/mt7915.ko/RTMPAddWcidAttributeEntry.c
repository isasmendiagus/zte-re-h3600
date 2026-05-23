// module: mt7915.ko
// function: RTMPAddWcidAttributeEntry @ 0xdc41c
// size: 840 bytes
//

void RTMPAddWcidAttributeEntry
               (int param_1,char *param_2,undefined4 param_3,int param_4,uint *param_5)

{
  char *pcVar1;
  char cVar2;
  undefined2 uVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  bool bVar8;
  
  uVar5 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  if (uVar5 != 0x7628 && uVar5 != 0x7603) {
    uVar6 = 0x7606;
    bVar8 = 0x7605 < uVar5;
    bVar7 = uVar5 == 0x7606;
    if (!bVar7) {
      bVar8 = uVar5 != 0x7636;
    }
    if (!bVar8 || (bVar7 || uVar5 == 0x7637)) {
      uVar6 = 1;
    }
    if (bVar8 && (!bVar7 && uVar5 != 0x7637)) {
      uVar6 = 0;
    }
    if (uVar5 == 0x7611) {
      uVar6 = uVar6 | 1;
    }
    if (uVar6 == 0) {
      if (*(char *)(param_1 + 0x286285) == '\x01') {
        if (param_2 < (char *)0x30) {
          if ((char *)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                  [param_1 + 0xda] <= param_2) {
            if (DebugLevel < 0) {
              return;
            }
            pcVar1 = 
            "RTMPAddWcidAttributeEntry: The BSS-index(%d) is out of range for MBSSID link.\n";
            goto LAB_000dc53c;
          }
          if (param_5 == (uint *)0x0) {
            if (param_2 < (char *)0x20) {
              pcVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + (int)param_2 * 0x5834 + param_1 + 0xe0;
            }
            else {
              pcVar1 = (char *)0x0;
            }
            uVar3 = *(undefined2 *)(pcVar1 + 0x9a0);
          }
          else {
            uVar3 = (undefined2)param_5[0x38];
          }
LAB_000dc66c:
          pcVar1 = (char *)hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
          if (param_2 < pcVar1) {
            if (param_2 < (char *)0x20) {
              if (param_5 == (uint *)0x0) {
                if (DebugLevel < 0) {
                  return;
                }
                pcVar1 = "RTMPAddWcidAttributeEntry: pEntry is Null\n";
LAB_000dc714:
                printk(pcVar1);
                return;
              }
              cVar2 = *(char *)(param_1 + 0x286285);
              cVar4 = (char)param_5[0x1c4];
              goto LAB_000dc694;
            }
            cVar2 = *(char *)(param_1 + 0x286285);
            if (cVar2 == '\0') goto LAB_000dc564;
            cVar4 = '\0';
          }
          else {
            cVar2 = *(char *)(param_1 + 0x286285);
            cVar4 = '\0';
LAB_000dc694:
            if (cVar2 == '\0') goto LAB_000dc4a8;
          }
          if (cVar2 == '\x01') {
            if (param_5 != (uint *)0x0) goto LAB_000dc5cc;
            goto LAB_000dc600;
          }
          param_2 = (char *)0x0;
        }
        else {
          if (param_5 == (uint *)0x0) {
            if (DebugLevel < 2) {
              return;
            }
            pcVar1 = 
            "RTMPAddWcidAttributeEntry: AP-Client link doesn\'t need to set Group WCID Attribute.\n"
            ;
            goto LAB_000dc714;
          }
          uVar3 = (undefined2)param_5[0x38];
          param_2 = (char *)((uint)(param_2 + -0x30) & 0xff);
          if (param_2 < (char *)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                            [param_1 + 0xda]) goto LAB_000dc66c;
          cVar4 = '\0';
LAB_000dc5cc:
          if (((*param_5 & 0xc) == 0) && (cVar4 != '\x01' && (param_4 != 0 && 1 < param_4 - 3U))) {
LAB_000dc600:
            param_2 = (char *)(param_4 << 1 | (int)param_2 << 4);
          }
          else {
            param_2 = (char *)(param_4 << 1 | 1U | (int)param_2 << 4);
          }
        }
      }
      else if (*(char *)(param_1 + 0x286285) == '\0') {
LAB_000dc4a8:
        if (param_2 != (char *)0x0) {
LAB_000dc564:
          if (DebugLevel < 0) {
            return;
          }
          pcVar1 = "RTMPAddWcidAttributeEntry: The BSS-index(%d) is out of range for Infra link.\n";
          goto LAB_000dc53c;
        }
        if (param_5 == (uint *)0x0) {
          uVar3 = 0;
        }
        else {
          uVar3 = (undefined2)param_5[0x38];
          if ((*param_5 & 8) != 0) {
            param_2 = (char *)(param_4 << 1 | 1);
            goto LAB_000dc4d4;
          }
        }
        param_2 = (char *)(param_4 << 1);
      }
      else {
        param_2 = (char *)0x0;
        uVar3 = 0;
      }
LAB_000dc4d4:
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0,param_2);
      if (DebugLevel < 3) {
        return;
      }
      printk("RTMPAddWcidAttributeEntry: WCID #%d, KeyIndex #%d, Alg=%s\n",uVar3,param_3,
             *(undefined4 *)(CipherName + param_4 * 4));
      if (DebugLevel < 3) {
        return;
      }
      pcVar1 = "\tWCIDAttri = 0x%x\n";
      goto LAB_000dc53c;
    }
  }
  if (DebugLevel < 1) {
    return;
  }
  param_2 = "RTMPAddWcidAttributeEntry";
  pcVar1 = "%s(): MT7603 Not support yet!\n";
LAB_000dc53c:
  printk(pcVar1,param_2);
  return;
}

