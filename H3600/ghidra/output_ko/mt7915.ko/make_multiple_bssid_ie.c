// module: mt7915.ko
// function: make_multiple_bssid_ie @ 0xb45b4
// size: 1484 bytes
//

void make_multiple_bssid_ie
               (int param_1,int param_2,int *param_3,int param_4,uint param_5,char param_6)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  char *pcVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined1 local_30;
  char local_2f;
  undefined2 local_2e;
  int local_2c [2];
  
  iVar2 = HcGetBandByWdev(param_2);
  iVar5 = param_1 + (short)iVar2 * 4;
  if (*(uint *)(&DAT_003678e8 + iVar5) == 0) {
    return;
  }
  iVar7 = param_1 + iVar2;
  if (*(uint *)(*(int *)(param_2 + 4) + 0x4060) != (uint)(byte)(&DAT_003678f2)[iVar7]) {
    return;
  }
  if ((*(uint *)(&DAT_003678e8 + iVar5) & ~(1 << (*(uint *)(*(int *)(param_2 + 4) + 0x4064) & 0xff))
      ) == 0) {
    return;
  }
  if (DebugLevel < 4) {
    if ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              [param_1 + 0xda] < 2) {
      return;
    }
  }
  else {
    printk("%s, MBSSID Bitmap = 0x%08x, FrameLen = %ld\n","make_multiple_bssid_ie",param_5,*param_3)
    ;
    if ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              [param_1 + 0xda] < 2) goto LAB_000b4758;
  }
  pcVar6 = "%s,wdev(null)(caller:%pS)\n" + param_1 + 0x14;
  iVar9 = 1;
  do {
    pcVar8 = pcVar6 + -0x4068;
    iVar3 = BeaconTransmitRequired(param_1,pcVar8,0);
    if (iVar3 == 0) {
      if (3 < DebugLevel) {
        printk("IdBss %d not ready for beaconing!\n",iVar9);
      }
    }
    else {
      iVar3 = HcGetBandByWdev(pcVar8);
      if (iVar3 == iVar2) {
        uVar1 = 1 << (*(uint *)(pcVar6 + -4) & 0xff);
        if (((((uVar1 & param_5) != 0) && (*(uint *)(&DAT_003678e8 + iVar5) != 0)) &&
            (*(uint *)(pcVar6 + -8) != (uint)(byte)(&DAT_003678f2)[iVar7])) &&
           ((uVar1 & *(uint *)(&DAT_003678e8 + iVar5)) != 0)) {
          if (3 < DebugLevel) {
            printk("Add IdBss %d IE: (mbss_grp_idx=%d)\n",iVar9);
          }
          iVar3 = *param_3;
          *(undefined1 *)(param_4 + iVar3) = 0x47;
          iVar11 = iVar3 + 3;
          *(undefined *)(param_4 + iVar3 + 2) = (&DAT_003678f0)[iVar7];
          *param_3 = iVar11;
          if (3 < DebugLevel) {
            printk("%s, IdBss = %d, FrameLen = %ld\n","make_nontransmitted_bssid_sub_ie",
                   *(undefined4 *)(pcVar6 + -8),iVar11);
          }
          *(undefined1 *)(param_4 + iVar11) = 0;
          iVar10 = iVar3 + 5;
          *param_3 = iVar10;
          local_2f = '\0';
          local_30 = 0x53;
          if (3 < DebugLevel) {
            printk("\t1 2 %s, IdBss = %d, pFrameLen = %ld\n","make_nontransmitted_bssid_cap_ie",
                   *(undefined4 *)(pcVar6 + -8),iVar10);
          }
          local_2e = *(undefined2 *)(pcVar6 + 0x24);
          local_2f = '\x02';
          MakeOutgoingFrame(param_4 + iVar10,local_2c,1,&local_30,1,&local_2f,2,&local_2e,0xffffffff
                           );
          if (pcVar6[0x22] == '\0') {
            local_2f = pcVar6[0x21];
          }
          else {
            local_2f = '\0';
          }
          iVar10 = iVar10 + local_2c[0];
          MakeOutgoingFrame(param_4 + iVar10,local_2c,1,&SsidIe,1,&local_2f,local_2f,pcVar6,
                            0xffffffff);
          iVar10 = iVar10 + local_2c[0];
          *param_3 = iVar10;
          if (DebugLevel < 4) {
            local_2f = 'U';
          }
          else {
            printk("\t1 2 CapIE/SSID End pFrameLen = %ld\n");
            iVar10 = *param_3;
            local_2f = 'U';
            if (3 < DebugLevel) {
              printk("\t3 %s, mbss_grp_idx = %d, FrameLen = %ld\n",
                     "make_nontransmitted_bssid_idx_ie",*(undefined4 *)(pcVar6 + -4),iVar10);
            }
          }
          if (param_6 == '\0') {
            local_2e = CONCAT11(local_2e._1_1_,3);
            MakeOutgoingFrame(param_4 + iVar10,local_2c,1,&local_2f,1,&local_2e,1,pcVar6 + -4,1,
                              &DAT_0036b8a0 + param_1,1,&DAT_0036b89f + param_1,0xffffffff);
            *(short *)(pcVar6 + -0x36e8) = (short)iVar10;
          }
          else {
            local_2e = CONCAT11(local_2e._1_1_,1);
            MakeOutgoingFrame(param_4 + iVar10,local_2c,1,&local_2f,1,&local_2e,1,pcVar6 + -4,
                              0xffffffff);
          }
          *param_3 = iVar10 + local_2c[0];
          if (3 < DebugLevel) {
            printk("\t3 BssidIdxIE End FrameLen = %ld\n");
          }
          ComposeRSNIE(param_1,pcVar8,param_3,param_4);
          ComposeWPSIE(param_1,pcVar8,param_3,param_4);
          *(char *)(param_4 + iVar11 + 1) = ((char)*param_3 + -2) - (char)iVar11;
          if (3 < DebugLevel) {
            printk("NonTransSubIE End FrameLen = %ld, IE Len = %d\n",*param_3);
          }
          *(char *)(param_4 + iVar3 + 1) = ((char)*param_3 + -2) - (char)iVar3;
          if (3 < DebugLevel) {
            printk("MbssIe IE Len = %d\n");
          }
        }
      }
      else if (3 < DebugLevel) {
        uVar4 = HcGetBandByWdev(pcVar8);
        printk("IdBss %d at diff band(%d)!\n",iVar9,uVar4);
      }
    }
    iVar9 = iVar9 + 1;
    pcVar6 = pcVar6 + 0x5834;
  } while (iVar9 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                    [param_1 + 0xda]);
LAB_000b4758:
  if (3 < DebugLevel) {
    printk("\tMultipleBssidIE End FrameLen = %ld\n",*param_3);
  }
  return;
}

