// module: mt7915.ko
// function: DfsNonOccupancyCountDown @ 0x232850
// size: 648 bytes
//

void DfsNonOccupancyCountDown(int param_1)

{
  short *psVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  char *pcVar9;
  int iVar10;
  char cVar11;
  bool bVar12;
  uint local_2c [2];
  
  pcVar9 = (char *)(param_1 + 0x795134);
  iVar10 = 0;
  bVar2 = false;
  local_2c[0] = 0;
  bVar3 = false;
  do {
    iVar4 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),iVar10);
    if (*(char *)(iVar4 + 0x49c) == '\0') {
      if (pcVar9[0x2b7] == '\x01') {
        cVar11 = *pcVar9;
        goto LAB_0023299c;
      }
    }
    else {
      iVar6 = iVar4 + ((byte)(*(char *)(iVar4 + 0x49c) - 1) + 1) * 0x14;
      iVar7 = iVar4;
      do {
        if (*(short *)(iVar7 + 0xc) != 0) {
          *(short *)(iVar7 + 0xc) = *(short *)(iVar7 + 0xc) + -1;
        }
        if (*(short *)(iVar7 + 10) == 0) {
          if (*(char *)(iVar7 + 7) != '\0') {
            *(undefined1 *)(iVar7 + 7) = 0;
          }
        }
        else {
          *(short *)(iVar7 + 10) = *(short *)(iVar7 + 10) + -1;
        }
        iVar7 = iVar7 + 0x14;
      } while (iVar7 != iVar6);
      if (pcVar9[0x2b7] == '\x01') {
        cVar11 = *pcVar9;
        iVar7 = iVar4 + 0xc;
LAB_00232954:
        do {
          if (cVar11 == '\x06') {
            if (*(char *)(param_1 + 0x795130) == *(char *)(iVar7 + -0xc)) {
              if (*(short *)(iVar4 + 0xc) != 0) goto LAB_00232944;
              bVar2 = true;
            }
            if (*(char *)(param_1 + 0x795131) == *(char *)(iVar7 + -0xc)) {
              psVar1 = (short *)(iVar4 + 0xc);
              iVar4 = iVar4 + 0x14;
              iVar7 = iVar7 + 0x14;
              if (*psVar1 == 0) {
                bVar3 = true;
              }
              if (iVar4 == iVar6) break;
              goto LAB_00232954;
            }
          }
          else if ((*(char *)(iVar7 + -0xc) == *(char *)(param_1 + 0x795132)) &&
                  (*(short *)(iVar4 + 0xc) == 0)) {
            bVar2 = true;
          }
LAB_00232944:
          iVar4 = iVar4 + 0x14;
          iVar7 = iVar7 + 0x14;
        } while (iVar4 != iVar6);
LAB_0023299c:
        if (cVar11 == '\x06') {
          bVar12 = false;
          if (bVar3) {
            bVar12 = bVar2;
          }
          if (bVar12) goto LAB_002329e4;
        }
        else if (bVar2) {
LAB_002329e4:
          uVar8 = 0;
          *(undefined1 *)(param_1 + iVar10 + 0x7953eb) = 0;
          if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              [param_1 + 0xda] != '\0') {
            do {
              local_2c[0] = 0;
              uVar5 = HcGetBandByWdev("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                      + param_1 + uVar8 * 0x5834 + 0xe0);
              if ((*(byte *)(param_1 + 0x7953f0) == uVar5) &&
                 (iVar4 = param_1 + uVar8 * 0x5834,
                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 [iVar4 + 0x108] != '\0')) {
                local_2c[0] = (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                    [iVar4 + 0xfa] | local_2c[0] | uVar8 << 8 |
                              (uint)*(byte *)(param_1 + 0x7953f0) << 0x10;
                RTEnqueueInternalCmd(param_1,0x1a,local_2c,4);
              }
              uVar8 = uVar8 + 1 & 0xff;
            } while (uVar8 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                   [param_1 + 0xda]);
          }
        }
      }
    }
    pcVar9 = pcVar9 + 1;
    if (iVar10 == 1) {
      return;
    }
    iVar10 = 1;
  } while( true );
}

