// module: mt7915.ko
// function: RRM_PeerNeighborReqSanity @ 0x223748
// size: 556 bytes
//

undefined4
RRM_PeerNeighborReqSanity
          (int param_1,int param_2,int param_3,undefined1 *param_4,undefined4 *param_5,char *param_6
          )

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  
  if (param_4 == (undefined1 *)0x0 || param_2 == 0) {
    return 0;
  }
  iVar2 = MacTableLookup(param_1,param_2 + 10);
  if ((iVar2 != 0) &&
     ((uint)*(byte *)(iVar2 + 0xe4) <=
      (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  [param_1 + 0xda])) {
    iVar4 = (uint)*(byte *)(iVar2 + 0xe4) * 0x5834;
    pcVar3 = (char *)(param_2 + 0x1b);
    *param_5 = "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n" +
               param_1 + iVar4 + 0x34;
    *param_6 = "pStaCfg->WpaPassPhrase"[(uint)*(byte *)(iVar2 + 0xe4) * 0x5834 + param_1 + 5];
    *param_4 = *(undefined1 *)(param_2 + 0x1a);
    if (pcVar3 + *(byte *)(param_2 + 0x1c) + 1 < (char *)(param_2 + param_3)) {
      param_1 = param_1 + iVar4;
      do {
        cVar1 = *pcVar3;
        if (cVar1 == '&') {
          if (DebugLevel < 3) {
            "The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n"[param_1 + 0x24]
                 = pcVar3[2];
            if (pcVar3[4] == '\b') {
              "The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n"
              [param_1 + 0x25] = '\x01';
            }
            else if (pcVar3[4] == '\v') {
              "The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n"
              [param_1 + 0x26] = '\x01';
            }
          }
          else {
            printk("%s - Got STA Measurement Request\n","RRM_PeerNeighborReqSanity");
            iVar2 = DebugLevel;
            "The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n"[param_1 + 0x24]
                 = pcVar3[2];
            if (pcVar3[4] == '\b') {
              "The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n"
              [param_1 + 0x25] = '\x01';
              if (2 < iVar2) {
                printk("%s - STA Request LCI Measurement Report\n","RRM_PeerNeighborReqSanity");
              }
            }
            else if (pcVar3[4] == '\v') {
              "The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n"
              [param_1 + 0x26] = '\x01';
              if (2 < iVar2) {
                printk("%s - STA Request CIVIC Measurement Report\n","RRM_PeerNeighborReqSanity");
              }
            }
            else if (2 < iVar2) {
              printk("unknown PeerMeasurementType: %d\n");
            }
          }
        }
        else if (cVar1 != -0x23) {
          if (cVar1 == '\0') {
            *param_5 = pcVar3 + 2;
            *param_6 = pcVar3[1];
          }
          else if (-1 < DebugLevel) {
            printk("unknown Eid: %d\n");
          }
        }
        pcVar3 = pcVar3 + (byte)pcVar3[1] + 2;
      } while (pcVar3 + (byte)pcVar3[1] + 1 < (char *)(param_2 + param_3));
    }
    return 1;
  }
  return 0;
}

