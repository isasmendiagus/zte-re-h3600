// module: mt7915.ko
// function: WscCheckPeerDPID @ 0x1eded8
// size: 516 bytes
//

void WscCheckPeerDPID(int param_1,int param_2,int param_3,int param_4,undefined1 param_5)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  ushort uVar4;
  uint *puVar5;
  char *pcVar6;
  ushort uStack_2b;
  
  param_4 = param_4 + -4;
  puVar5 = (uint *)(param_3 + 4);
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    bVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [param_1 + 0xda];
    pcVar6 = (char *)0x0;
    if (bVar1 == 0) goto joined_r0x001edf14;
    uVar2 = 0;
    pcVar6 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             + param_1 + 0x101;
    do {
      iVar3 = memcmp((void *)(param_2 + 4),pcVar6,6);
      pcVar6 = pcVar6 + 0x5834;
      if (iVar3 == 0) {
        pcVar6 = "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                 + uVar2 * 0x5834 + param_1 + 0x2b;
        goto joined_r0x001edf14;
      }
      uVar2 = uVar2 + 1;
    } while ((uVar2 & 0xff) < (uint)bVar1);
  }
  pcVar6 = (char *)0x0;
joined_r0x001edf14:
  while( true ) {
    if (param_4 < 1) {
      return;
    }
    uVar2 = *puVar5;
    if (((uVar2 & 0xff) << 8 | uVar2 >> 8 & 0xff) == 0x1012) break;
    uStack_2b = (ushort)(uVar2 >> 0x10);
    uVar2 = (uStack_2b & 0xff) << 8 | (uint)(uStack_2b >> 8);
    param_4 = param_4 + (-4 - uVar2);
    puVar5 = (uint *)((int)puVar5 + uVar2 + 4);
  }
  uVar4 = (ushort)puVar5[1] << 8 | (ushort)puVar5[1] >> 8;
  if (uVar4 == 4) {
    WscPBC_DPID_FromSTA(param_1,param_2 + 10,param_5);
    hex_dump("PBC STA:",param_2 + 10,6);
    if (DebugLevel < 3) {
      return;
    }
    printk(&_LC13);
    return;
  }
  if (uVar4 != 0) {
    if (DebugLevel < 3) {
      return;
    }
    printk("%s : DevicePasswordID = 0x%04x\n","WscCheckPeerDPID");
    return;
  }
  if (pcVar6 == (char *)0x0) {
    return;
  }
  if ((pcVar6[0x29e4] != '\0') && (*(int *)(pcVar6 + 4) == 2)) {
    return;
  }
  _raw_spin_lock_bh(pcVar6 + 0x2c00);
  WscInsertPeerEntryByMAC(pcVar6 + 0x2c04,param_2 + 10);
  _raw_spin_unlock_bh(pcVar6 + 0x2c00);
  return;
}

