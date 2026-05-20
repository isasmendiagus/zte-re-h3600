// module: mt7915.ko
// function: Set_AP_SSID_Proc @ 0x35f1c
// size: 660 bytes
//

undefined4 Set_AP_SSID_Proc(int *param_1,char *param_2)

{
  int iVar1;
  size_t sVar2;
  size_t sVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  char *pcVar7;
  char *__s;
  
  iVar6 = *param_1;
  iVar4 = *(int *)(iVar6 + 0x3c);
  iVar1 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
  if (((iVar4 < iVar1) && (iVar1 = *(int *)(iVar6 + 0x3c), iVar1 < 0x20)) &&
     (sVar2 = strlen(param_2), sVar2 < 0x21)) {
    iVar4 = iVar1 * 0x5834;
    __s = (char *)((int)param_1 +
                  (int)(
                       "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                       + iVar4 + 0x34));
    pcVar7 = (char *)((int)param_1 +
                     (int)(
                          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          + iVar4 + 0xe0));
    __memzero(__s,0x20);
    sVar2 = strlen(param_2);
    memmove(__s,param_2,sVar2 + 1);
    sVar2 = strlen(param_2);
    *(char *)((int)param_1 + iVar4 + 0x2bb2d1) = (char)sVar2;
    if ((pcVar7 != (char *)0x0) && (param_1[iVar1 * 0x160d + 0xaec8b] != 0)) {
      sVar2 = strlen(param_2);
      sVar3 = strlen(__s);
      if ((sVar2 != sVar3) || (iVar4 = memcmp(param_2,__s,sVar2), iVar4 != 0)) {
        pbVar5 = (byte *)(param_1 + 0xda1ff);
        iVar4 = 0;
        do {
          if (((pbVar5[0x5c] == 1) && ((uint)*pbVar5 == param_1[iVar1 * 0x160d + 0xaecaa])) &&
             (pbVar5[0x5c] = 0, 0 < DebugLevel)) {
            printk("%s():Modify SSID and clear PMKID (idx %d)from (mbssidx %d)\n","Set_AP_SSID_Proc"
                   ,iVar4);
          }
          iVar4 = iVar4 + 1;
          pbVar5 = pbVar5 + 0x60;
        } while (iVar4 != 0x80);
      }
      ap_send_broadcast_deauth(param_1,pcVar7);
      if ((param_1[iVar1 * 0x160d + 0xadc9d] == 1) && (param_1[iVar1 * 0x160d + 0xadcef] == 1)) {
        *(ushort *)(param_1 + iVar1 * 0x160d + 0xaecb5) =
             *(ushort *)(param_1 + iVar1 * 0x160d + 0xaecb5) & 0xffef;
      }
      else {
        *(ushort *)(param_1 + iVar1 * 0x160d + 0xaecb5) =
             *(ushort *)(param_1 + iVar1 * 0x160d + 0xaecb5) | 0x10;
      }
      APSecInit(param_1,pcVar7);
      restart_ap(pcVar7);
      if (2 < DebugLevel) {
        printk("I/F(ra%d) Set_SSID_Proc::(Len=%d,Ssid=%s)\n",*(undefined4 *)(iVar6 + 0x3c),
               *(undefined1 *)((int)param_1 + iVar1 * 0x5834 + 0x2bb2d1),__s);
        return 1;
      }
      return 1;
    }
  }
  return 0;
}

