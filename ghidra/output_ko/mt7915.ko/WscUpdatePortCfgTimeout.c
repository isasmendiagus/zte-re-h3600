// module: mt7915.ko
// function: WscUpdatePortCfgTimeout @ 0x1ed10c
// size: 520 bytes
//

void WscUpdatePortCfgTimeout(undefined4 param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  int iVar8;
  byte local_19 [5];
  
  if (param_2 == 0) {
    return;
  }
  iVar8 = *(int *)(param_2 + 0x29e8);
  if (iVar8 == 0) {
    return;
  }
  uVar5 = (uint)*(ushort *)(param_2 + 0x1cbc);
  uVar1 = *(byte *)(param_2 + 0x1c54) & 0xf;
  if (uVar5 == 8) goto LAB_001ed178;
  if (uVar5 < 9) {
    if (uVar5 == 2) {
      uVar5 = 0x10;
      goto LAB_001ed178;
    }
    if (uVar5 == 4) {
      uVar5 = 2;
      goto LAB_001ed178;
    }
    if (uVar5 == 1) goto LAB_001ed178;
  }
  else {
    if (uVar5 == 0x20) {
      uVar5 = 0x80;
      goto LAB_001ed178;
    }
    if (uVar5 < 0x21) {
      if (uVar5 == 0x10) {
        uVar5 = 0x40;
        goto LAB_001ed178;
      }
    }
    else {
      if (uVar5 == 0x22) {
        uVar5 = 0x90;
        goto LAB_001ed178;
      }
      if (uVar5 == 0x80) {
        uVar5 = 0x20;
        goto LAB_001ed178;
      }
    }
  }
  uVar5 = 0;
LAB_001ed178:
  iVar4 = uVar1 * 0x5834 + iVar8;
  if (*(uint *)(
               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
               + iVar4 + 0x10c) == uVar5) {
    pcVar6 = (char *)(*(ushort *)(param_2 + 0x1cbe) - 1 & 0xffff);
    if (pcVar6 < (char *)0xc) {
      pcVar7 = "WscLinkDown" + (int)pcVar6 * 4;
    }
    else {
      iVar4 = 0;
      pcVar7 = pcVar6;
    }
    iVar3 = uVar1 * 0x5834;
    if (pcVar6 < (char *)0xc) {
      iVar4 = *(int *)(pcVar7 + 0x280);
    }
    if (((*(int *)(
                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + iVar8 + iVar3 + 0x254) == iVar4) &&
        (iVar4 = memcmp("Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                        + iVar8 + iVar3 + 0x34,(void *)(param_2 + 0x1c9c),
                        *(size_t *)(param_2 + 0x1c98)), iVar4 == 0)) &&
       (iVar4 = memcmp((void *)(param_2 + 0x299d),(void *)(param_2 + 0x1cc0),
                       (uint)*(ushort *)(param_2 + 0x1d00)), iVar4 == 0)) {
      return;
    }
  }
  WscWriteConfToPortCfg
            (iVar8,param_2,param_2 + 0x1c98,((*(uint *)(param_2 + 0x1c94) ^ 0x8000) << 0x10) >> 0x1f
            );
  *(uint *)(param_2 + 0x1c94) = *(uint *)(param_2 + 0x1c94) & 0x7fff;
  local_19[0] = *(byte *)(param_2 + 0x1c54) & 0xf;
  *(byte *)(iVar8 + 0x794b18) = local_19[0];
  uVar2 = RTEnqueueInternalCmd(iVar8,5,local_19,1);
  if (2 < DebugLevel) {
    printk("%s: en-queu CMDTHREAD_AP_RESTART - enq_rv = 0x%x\n","WscUpdatePortCfgTimeout",uVar2);
  }
  RtmpOsTaskWakeUp(iVar8 + 0x794ae8);
  return;
}

