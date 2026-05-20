// module: mt7915.ko
// function: MtAsicSetApcliWdevIfAddr @ 0x19adcc
// size: 428 bytes
//

/* WARNING: Removing unreachable block (ram,0x0019aefc) */

void MtAsicSetApcliWdevIfAddr(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  undefined4 *__s2;
  uint uVar4;
  undefined2 local_26;
  undefined2 local_24;
  undefined2 local_22;
  
  uVar4 = (uint)*(byte *)(param_2 + 0xe);
  local_26 = 0;
  local_24 = 0;
  local_22 = 0;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar2 == 2) {
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fb020);
    param_1 = param_1 + uVar4 * 6;
    __s2 = (undefined4 *)(param_1 + 0x794c1c);
    iVar2 = memcmp(&local_26,__s2,6);
    if (iVar2 == 0) {
      *(byte *)(param_2 + 0x1b) = (*(byte *)(param_2 + 0x1b) | 2) ^ (byte)(1 << (uVar4 + 2 & 0xff));
    }
    else {
      *(undefined4 *)(param_2 + 0x1b) = *__s2;
      *(undefined2 *)(param_2 + 0x1f) = *(undefined2 *)(param_1 + 0x794c20);
    }
  }
  else if (*(char *)(iVar1 + 0xfa) == '\0') {
    *(char *)(param_2 + 0x20) =
         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
         [param_1 + 0xda] + *(char *)(param_2 + 0x20);
  }
  else if (*(char *)(iVar1 + 0xfa) == '\x01' &&
           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           [param_1 + 0xda] != '\0') {
    bVar3 = *(byte *)(param_2 + 0x1b) | 2;
    *(byte *)(param_2 + 0x1b) = bVar3;
    *(byte *)(param_2 + 0x1b) =
         bVar3 + ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  [param_1 + 0xda] + -1) * '\x04';
  }
  if (2 < DebugLevel) {
    printk("%s-%s apcli_idx = %d, if_addr = %02x:%02x:%02x:%02x:%02x:%02x (MBSSIDMode:%d)\n",
           "/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/hw_ctrl/cmm_chip_mt.c"
           ,"MtAsicSetApcliWdevIfAddr",uVar4,*(undefined1 *)(param_2 + 0x1b),
           *(undefined1 *)(param_2 + 0x1c),*(undefined1 *)(param_2 + 0x1d),
           *(undefined1 *)(param_2 + 0x1e),*(undefined1 *)(param_2 + 0x1f),
           *(undefined1 *)(param_2 + 0x20),*(undefined1 *)(iVar1 + 0xfa));
  }
  return;
}

