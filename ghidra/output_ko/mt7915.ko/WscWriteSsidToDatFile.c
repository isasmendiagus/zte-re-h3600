// module: mt7915.ko
// function: WscWriteSsidToDatFile @ 0x1e67e4
// size: 596 bytes
//

void WscWriteSsidToDatFile(int param_1,char *param_2,int param_3,int param_4)

{
  int iVar1;
  size_t sVar2;
  size_t sVar3;
  uint uVar4;
  char local_2a [10];
  
  if (param_3 == 0) {
    __memzero(param_2,0x200);
    if (param_4 == 0) {
      if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda] != '\0') {
        uVar4 = 0;
        do {
          if (uVar4 == 0) {
            builtin_strncpy(param_2,"SSID=",5);
            sVar2 = strlen(param_2);
          }
          else {
            sVar3 = strlen(param_2);
            sVar2 = sVar3 + 1;
            param_2[sVar3] = ';';
          }
          if (0x1ff < (int)((byte)"pStaCfg->WpaPassPhrase"[param_1 + uVar4 * 0x5834 + 5] + sVar2)) {
            return;
          }
          memmove(param_2 + sVar2,
                  "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                  + param_1 + uVar4 * 0x5834 + 0x34,
                  (uint)(byte)"pStaCfg->WpaPassPhrase"[param_1 + uVar4 * 0x5834 + 5]);
          uVar4 = uVar4 + 1 & 0xff;
        } while (uVar4 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                               [param_1 + 0xda]);
      }
    }
    else if (param_4 == 2) {
      iVar1 = *(int *)(&DAT_00370ad0 + param_1);
      builtin_strncpy(param_2,"SSID=",5);
      sVar2 = strlen(param_2);
      if (sVar2 + *(size_t *)(&DAT_00370ad4 + param_1 + iVar1 * 0x74) < 0x200) {
        memmove(param_2 + sVar2,(void *)(param_1 + iVar1 * 0x74 + 0x370ad8),
                *(size_t *)(&DAT_00370ad4 + param_1 + iVar1 * 0x74));
        return;
      }
    }
  }
  else {
    uVar4 = 0;
    local_2a[0] = '\0';
    local_2a[1] = '\0';
    local_2a[2] = '\0';
    local_2a[3] = '\0';
    local_2a[4] = '\0';
    local_2a[5] = '\0';
    local_2a[6] = '\0';
    local_2a[7] = '\0';
    local_2a[8] = '\0';
    local_2a[9] = '\0';
    if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
        [param_1 + 0xda] != '\0') {
      do {
        snprintf(local_2a,10,"SSID%d",uVar4 + 1);
        iVar1 = rtstrstr(param_2,local_2a);
        if (iVar1 != 0) {
          __memzero(param_2,0x200);
          sVar2 = strlen(local_2a);
          memcpy(param_2,local_2a,sVar2);
          sVar2 = strlen(param_2);
          param_2[sVar2] = '=';
          if ((int)((uint)(byte)"pStaCfg->WpaPassPhrase"[param_1 + uVar4 * 0x5834 + 5] + sVar2 + 1)
              < 0x200) {
            memmove(param_2 + sVar2 + 1,
                    "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                    + param_1 + uVar4 * 0x5834 + 0x34,
                    (uint)(byte)"pStaCfg->WpaPassPhrase"[param_1 + uVar4 * 0x5834 + 5]);
          }
        }
        __memzero(local_2a,10);
        uVar4 = uVar4 + 1 & 0xff;
      } while (uVar4 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                             [param_1 + 0xda]);
    }
  }
  return;
}

