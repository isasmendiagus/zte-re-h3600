// module: mt7915.ko
// function: WscWriteWpaPskToDatFile @ 0x1e6a38
// size: 612 bytes
//

void WscWriteWpaPskToDatFile(int param_1,char *param_2,int param_3)

{
  int iVar1;
  size_t sVar2;
  size_t sVar3;
  char cVar4;
  uint uVar5;
  char local_32 [14];
  
  if (param_3 == 0) {
    __memzero(param_2,0x200);
    cVar4 = *(char *)(param_1 + 0x286285);
    if (cVar4 == '\x01') {
      if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda] == '\0') {
        return;
      }
      uVar5 = 0;
      do {
        if (uVar5 == 0) {
          builtin_strncpy(param_2,"WPAPSK=",7);
          sVar2 = strlen(param_2);
        }
        else {
          sVar3 = strlen(param_2);
          sVar2 = sVar3 + 1;
          param_2[sVar3] = ';';
        }
        iVar1 = param_1 + uVar5 * 0x5834;
        if (0x1ff < (int)(*(size_t *)
                           (
                           "PIN authentication or communication error occurs!!\nRegistrar does NOT accept the same PIN again!(PIN:%08u)\n"
                           + iVar1 + 0x58) + sVar2)) break;
        memmove(param_2 + sVar2,
                "PIN authentication or communication error occurs!!\nRegistrar does NOT accept the same PIN again!(PIN:%08u)\n"
                + iVar1 + 0x15,
                *(size_t *)
                 (
                 "PIN authentication or communication error occurs!!\nRegistrar does NOT accept the same PIN again!(PIN:%08u)\n"
                 + iVar1 + 0x58));
        uVar5 = uVar5 + 1 & 0xff;
      } while (uVar5 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                             [param_1 + 0xda]);
      cVar4 = *(char *)(param_1 + 0x286285);
    }
    if (cVar4 == '\0') {
      builtin_strncpy(param_2,"WPAPSK=",7);
      sVar2 = *(size_t *)(&DAT_0037181c + param_1);
      if ((sVar2 != 0) && (sVar3 = strlen(param_2), (int)(sVar2 + sVar3) < 0x200)) {
        memmove(param_2 + sVar3,s_TASK_STACK_INFO__size_in_byte__003717c0 + param_1 + 0x19,sVar2);
        return;
      }
    }
  }
  else {
    uVar5 = 0;
    local_32[0] = '\0';
    local_32[1] = '\0';
    local_32[2] = '\0';
    local_32[3] = '\0';
    local_32[4] = '\0';
    local_32[5] = '\0';
    local_32[6] = '\0';
    local_32[7] = '\0';
    local_32[8] = '\0';
    local_32[9] = '\0';
    if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
        [param_1 + 0xda] != '\0') {
      do {
        snprintf(local_32,10,"WPAPSK%d",uVar5 + 1);
        iVar1 = rtstrstr(param_2,local_32);
        if (iVar1 != 0) {
          __memzero(param_2,0x200);
          sVar2 = strlen(local_32);
          memcpy(param_2,local_32,sVar2);
          sVar2 = strlen(param_2);
          param_2[sVar2] = '=';
          if ((int)(*(size_t *)
                     (
                     "PIN authentication or communication error occurs!!\nRegistrar does NOT accept the same PIN again!(PIN:%08u)\n"
                     + param_1 + uVar5 * 0x5834 + 0x58) + sVar2 + 1) < 0x200) {
            memmove(param_2 + sVar2 + 1,
                    "PIN authentication or communication error occurs!!\nRegistrar does NOT accept the same PIN again!(PIN:%08u)\n"
                    + param_1 + uVar5 * 0x5834 + 0x15,
                    *(size_t *)
                     (
                     "PIN authentication or communication error occurs!!\nRegistrar does NOT accept the same PIN again!(PIN:%08u)\n"
                     + param_1 + uVar5 * 0x5834 + 0x58));
          }
        }
        __memzero(local_32,10);
        uVar5 = uVar5 + 1 & 0xff;
      } while (uVar5 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                             [param_1 + 0xda]);
    }
  }
  return;
}

