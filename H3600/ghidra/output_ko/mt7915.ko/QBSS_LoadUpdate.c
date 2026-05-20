// module: mt7915.ko
// function: QBSS_LoadUpdate @ 0x26e6c
// size: 1912 bytes
//

void QBSS_LoadUpdate(int param_1,uint param_2)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  uint uVar10;
  char cVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  char *pcVar15;
  int *piVar16;
  uint local_7c;
  uint local_74;
  byte local_4b;
  undefined2 local_4a;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 uStack_40;
  char local_3f;
  char local_3c;
  
  local_74 = (uint)*(ushort *)(&DAT_00794c50 + param_1);
  pcVar4 = (char *)HcGetQloadCtrl();
  uVar14 = 0;
  if (*(char *)(param_1 + 0x79504d) == '\0') {
    uVar8 = 1;
  }
  else {
    uVar8 = 2;
  }
  uVar12 = 0;
  piVar16 = (int *)(param_1 + 0x8292cc);
  bVar3 = false;
  bVar2 = false;
  local_7c = 0;
  if (*(char *)(param_1 + 0x79504d) != '\0') goto LAB_00027120;
  do {
    if ((*pcVar4 != '\0') && (pcVar4[0xc0] != '\x01')) {
      if ((param_2 != 0) && (uVar10 = *(uint *)(pcVar4 + 4), uVar10 != 0 && uVar10 < param_2)) {
        local_74 = ((param_2 - uVar10) * 1000) / 100;
        if (*(uint *)(pcVar4 + 0xd0) != local_74) {
          FUN_00026bfc(param_1,local_74,(param_2 - uVar10) * 0x118);
        }
        *(uint *)(pcVar4 + 0xd0) = local_74;
      }
      *(uint *)(pcVar4 + 4) = param_2;
      iVar5 = hc_radio_query_by_index(param_1,uVar12,&uStack_40);
      if (iVar5 == 0) {
        if ((((local_3c == '\0') || (local_3f == '\0')) ||
            (iVar5 = scan_in_run_state(param_1), iVar5 != 0)) || (*piVar16 != 0)) {
          cVar11 = pcVar4[0xc0];
        }
        else {
          *(uint *)(pcVar4 + 0x1c) = local_7c;
          uVar12 = __aeabi_uidiv((local_7c >> 10) * 0x14,local_74);
          if (0x12 < uVar12) {
            uVar12 = 0x13;
          }
          *(int *)(pcVar4 + uVar12 * 4 + 0x70) = *(int *)(pcVar4 + uVar12 * 4 + 0x70) + 1;
          cVar1 = pcVar4[0xc0];
          cVar11 = cVar1;
          if (((cVar1 == '\0') && (cVar11 = '\0', pcVar4[0xc1] != '\0')) &&
             (cVar11 = cVar1, *(uint *)(pcVar4 + 0xd4) != 0 && *(uint *)(pcVar4 + 0xd4) <= local_7c)
             ) {
            bVar2 = true;
          }
        }
        iVar5 = param_1 + uVar14 * 4;
        local_7c = *(uint *)(iVar5 + 0xa7c310);
        iVar5 = *(int *)(iVar5 + 0xa7c308);
        *(uint *)(pcVar4 + 0x18) = local_7c;
        uVar12 = __aeabi_uidiv((local_7c >> 10) * 0x14,local_74);
        if (0x12 < uVar12) {
          uVar12 = 0x13;
        }
        *(int *)(pcVar4 + uVar12 * 4 + 0x20) = *(int *)(pcVar4 + uVar12 * 4 + 0x20) + 1;
        if (((cVar11 == '\0') && (pcVar4[0xc1] != '\0')) &&
           (*(uint *)(pcVar4 + 0xd4) != 0 && *(uint *)(pcVar4 + 0xd4) <= local_7c)) {
          bVar2 = true;
        }
        cVar1 = pcVar4[0x14];
        iVar5 = iVar5 + *(int *)(pcVar4 + 0xc);
        iVar13 = *(int *)(pcVar4 + 0x10);
        pcVar4[0x14] = cVar1 + 1U;
        *(int *)(pcVar4 + 0xc) = iVar5;
        *(uint *)(pcVar4 + 0x10) = local_7c + iVar13;
        if ((uint)(byte)pcVar4[0x15] <= (uint)(byte)(cVar1 + 1U)) {
          iVar6 = (uint)(byte)pcVar4[0x15] * 1000000;
          uVar12 = __aeabi_uidiv(iVar5 * 0xff,iVar6);
          pcVar4[8] = (char)uVar12;
          uVar10 = __aeabi_uidiv((local_7c + iVar13) * 0xff,iVar6);
          pcVar4[9] = (char)uVar10;
          if (0xfe < uVar12) {
            pcVar4[8] = -1;
          }
          if (0xfe < uVar10) {
            pcVar4[9] = -1;
          }
          pcVar4[0x14] = '\0';
          pcVar4[0xc] = '\0';
          pcVar4[0xd] = '\0';
          pcVar4[0xe] = '\0';
          pcVar4[0xf] = '\0';
          pcVar4[0x10] = '\0';
          pcVar4[0x11] = '\0';
          pcVar4[0x12] = '\0';
          pcVar4[0x13] = '\0';
        }
        if ((cVar11 == '\0') && (pcVar4[0xc1] != '\0')) {
          cVar11 = pcVar4[0xc4];
          if (bVar2) {
            if (cVar11 != '\0') goto LAB_000271a4;
            cVar11 = pcVar4[0xc3];
            pcVar4[0xc3] = cVar11 + 1U;
            if ((byte)(cVar11 + 1U) < (byte)pcVar4[0xc2]) goto joined_r0x000271c8;
            pcVar4[0xc4] = '\x02';
          }
          else {
            pcVar4[0xc3] = '\0';
            if (cVar11 != '\0') {
LAB_000271a4:
              if ((byte)(cVar11 + 1U) < 100) {
                pcVar4[0xc4] = cVar11 + '\x01';
              }
              else {
                pcVar4[0xc4] = '\0';
                pcVar4[0xc3] = '\0';
              }
            }
joined_r0x000271c8:
            if (!bVar3) goto LAB_000270f0;
          }
          iVar5 = HcGetQloadCtrl(param_1);
          iVar13 = HcGetQloadCtrl(param_1);
          *(undefined1 *)(iVar13 + 0xc0) = 1;
          local_4b = 0;
          *(int *)(iVar5 + 200) = *(int *)(iVar5 + 200) + 1;
          if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              [param_1 + 0xda] != '\0') {
            uVar12 = 0;
            do {
              pcVar15 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + param_1 + uVar12 * 0x5834 + 0xe0;
              iVar13 = wlan_operate_get_ext_cha(pcVar15);
              iVar6 = wlan_operate_get_ht_bw(pcVar15);
              if (iVar6 == 0 || iVar13 == 0) {
                if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    [param_1 + uVar12 * 0x5834 + 0x108] != '\0') {
                  if (2 < DebugLevel) {
                    printk("qbss> Alarm! Switch channel...\n");
                  }
                  RTEnqueueInternalCmd(param_1,3,&local_4b,1);
                }
              }
              else {
                if (2 < DebugLevel) {
                  printk("qbss> Alarm! Change to 20 bw...\n");
                }
                iVar6 = param_1 + 0xa1d20;
                iVar13 = param_1 + 0xa1e0c;
                for (uVar12 = 0; uVar10 = HcGetMaxStaNum(param_1), uVar12 < uVar10;
                    uVar12 = uVar12 + 1) {
                  if (((*(int *)(iVar13 + -0xec) == 0x20001) && (*(int *)(iVar6 + 0xfc) == 2)) &&
                     (*(char *)(iVar6 + 0xd11) != '\0')) {
                    local_48 = 0;
                    local_44 = 0;
                    iVar7 = os_alloc_mem(param_1,&local_48,0x900);
                    if (iVar7 == 0) {
                      iVar7 = param_1 + (uint)*(byte *)(iVar6 + 0xe4) * 0x5834;
                      local_4a = 3;
                      MgtMacHeaderInit(param_1,&uStack_40,0xc,0,iVar13,
                                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                       + iVar7 + 0xfb,
                                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                       + iVar7 + 0x101);
                      MakeOutgoingFrame(local_48,&local_44,0x18,&uStack_40,2,&local_4a,0xffffffff);
                      MiniportMMRequest(param_1,0,local_48,local_44);
                      os_free_mem(local_48);
                      ZTE_Notify_Node_AD(0,iVar6);
                      wlan_dbg_save_staoffline_record(iVar6,local_4a,0xbf,"QBSS_LoadAlarm");
                      __ZTE_STA_Assoc_Process
                                (param_1,0x11,0,0,local_4a,0,iVar6,"QBSS_LoadAlarm",0xc2);
                      if (2 < DebugLevel) {
                        printk("qbss> Alarm! Deauth the station %02x:%02x:%02x:%02x:%02x:%02x\n",
                               *(undefined1 *)(iVar6 + 0xec),*(undefined1 *)(iVar6 + 0xed),
                               *(undefined1 *)(iVar6 + 0xee),*(undefined1 *)(iVar6 + 0xef),
                               *(undefined1 *)(iVar6 + 0xf0),*(undefined1 *)(iVar6 + 0xf1));
                      }
                      mac_entry_delete(param_1,iVar6);
                    }
                    else if (2 < DebugLevel) {
                      printk(" MlmeAllocateMemory fail  ..\n");
                    }
                  }
                  iVar6 = iVar6 + 0x14c0;
                  iVar13 = iVar13 + 0x14c0;
                }
                wlan_operate_set_ht_bw(pcVar15,0,0);
                *(undefined1 *)(iVar5 + 0xcc) = 1;
                iVar13 = HcGetQloadCtrl(param_1);
                *(undefined1 *)(iVar13 + 0xc0) = 0;
              }
              local_4b = local_4b + 1;
              uVar12 = (uint)local_4b;
            } while (uVar12 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                    [param_1 + 0xda]);
          }
          bVar3 = true;
        }
        else {
          pcVar4[0xc3] = '\0';
          pcVar4[0xc4] = '\0';
          pcVar4[0xcc] = '\0';
        }
      }
    }
LAB_000270f0:
    do {
      uVar14 = uVar14 + 1;
      uVar12 = uVar14 & 0xff;
      piVar16 = piVar16 + 0x2bd76;
      if (uVar8 <= uVar12) {
        return;
      }
      if (*(char *)(param_1 + 0x79504d) == '\0') break;
LAB_00027120:
      uVar10 = HcGetRadioPhyModeByBandIdx(param_1,uVar12);
      if ((uVar10 & 0xb1) == 0) {
        uVar9 = 1;
      }
      else {
        uVar9 = 2;
      }
      pcVar4 = (char *)HcGetQloadCtrlByRf(param_1,uVar9);
    } while (pcVar4 == (char *)0x0);
  } while( true );
}

