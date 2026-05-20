// module: mt7915.ko
// function: AutoChannelSelCheck @ 0x268c4
// size: 800 bytes
//

void AutoChannelSelCheck(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint *puVar9;
  char *pcVar10;
  bool bVar11;
  
  uVar3 = HcGetAmountOfBand();
  if (uVar3 == 0) {
    return;
  }
  uVar8 = 0;
  pcVar10 = (char *)0x0;
  uVar7 = 0;
  puVar9 = (uint *)(&DAT_0036b844 + param_1);
  do {
    uVar5 = puVar9[1];
    if ((uVar5 != 0) && (uVar6 = puVar9[3], puVar9[3] = uVar6 + 1, uVar5 < uVar6 + 1)) {
      if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda] != '\0') {
        uVar5 = 0;
        do {
          pcVar10 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + uVar5 * 0x5834 + param_1 + 0xe0;
          uVar5 = uVar5 + 1 & 0xffff;
          uVar6 = HcGetBandByWdev(pcVar10);
          if (uVar7 == uVar6) break;
        } while (uVar5 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                               [param_1 + 0xda]);
      }
      iVar4 = scan_in_run_state(param_1,pcVar10);
      if (iVar4 == 0) {
        iVar4 = param_1 + uVar8 * 4;
        *(undefined4 *)(&DAT_0036b850 + iVar4) = 0;
        if (*(short *)(param_1 + 0x285920) != 0) {
          if (DebugLevel < 1) {
            return;
          }
          printk("%s(): Ignore ACS checking because has associated clients.\n","AutoChannelSelCheck"
                );
          return;
        }
        if (2 < DebugLevel) {
          printk("%s(): Scanning channels for channel selection.\n","AutoChannelSelCheck");
        }
        if (1 < *(int *)(&DAT_0036b828 + iVar4) - 3U) {
          ApSiteSurvey_by_wdev(param_1,0,0x80,1,pcVar10);
          return;
        }
        if (param_1 == 0 || pcVar10 == (char *)0x0) {
          return;
        }
        iVar4 = HcGetBandByWdev(pcVar10);
        iVar1 = HcGetAutoChCtrlbyBandIdx(param_1,iVar4);
        iVar2 = scan_in_run_state(param_1,pcVar10);
        if (iVar2 == 0) {
          *(undefined4 *)(iVar1 + 0x10) = 0;
          os_zero_mem(iVar1 + 0x74,0x1e0);
          if (2 < DebugLevel) {
            printk("%s----------------->\n","AutoChSelScanStart");
          }
          *(undefined1 *)(param_1 + 0xa7c349) = 0;
          *(undefined1 *)(param_1 + iVar4 + 0xa7c304) = 0;
          *(undefined1 *)(iVar1 + 0xc) = 0;
          *(char **)(iVar1 + 8) = pcVar10;
          bVar11 = (*(ushort *)(pcVar10 + 0x18) & 0xb1) == 0;
          if (bVar11) {
            *(byte *)(iVar1 + 0x14) = (byte)*(ushort *)(pcVar10 + 0x18) & 0xb1;
          }
          else {
            *(undefined1 *)(iVar1 + 0x14) = 1;
          }
          AutoChSelBuildChannelList(param_1,!bVar11,pcVar10);
          if (0 < DebugLevel) {
            printk("%s: IsABand = %d, ChannelListNum = %d\n","AutoChSelScanStart",
                   *(undefined1 *)(iVar1 + 0x14),*(undefined1 *)(iVar1 + 0xe));
          }
          MlmeEnqueueWithWdev(param_1,0x2e,0,0,0,pcVar10[0xe],pcVar10);
          RtmpOsMlmeUp(param_1 + 0x286298);
          if (2 < DebugLevel) {
            pcVar10 = "%s<-----------------\n";
            goto LAB_000242c0;
          }
        }
        else if (-1 < DebugLevel) {
          pcVar10 = "%s::Failed!!!Scan is running, please try again after scan done!\n";
LAB_000242c0:
          printk(pcVar10,"AutoChSelScanStart");
          return;
        }
        return;
      }
    }
    uVar8 = uVar8 + 1;
    uVar7 = uVar8 & 0xff;
    puVar9 = puVar9 + 1;
    if (uVar3 <= uVar7) {
      return;
    }
  } while( true );
}

