// module: mt7915.ko
// function: MtAsicSetMbssWdevIfAddrGen1 @ 0x19a79c
// size: 452 bytes
//

void MtAsicSetMbssWdevIfAddrGen1(int param_1,int param_2,int param_3)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  byte bVar4;
  uint local_24 [2];
  
  cVar1 = *(char *)(param_2 + 0xe);
  local_24[0] = 0;
  if (0 < DebugLevel) {
    printk("%s-%s\n",
           "/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/hw_ctrl/cmm_chip_mt.c"
           ,"MtAsicSetMbssWdevIfAddrGen1");
  }
  if (param_3 == 1) {
    bVar4 = (byte)param_1;
    *(undefined4 *)(param_2 + 0x1b) = *(undefined4 *)(param_1 + 0x794b5b);
    *(undefined2 *)(param_2 + 0x1f) = *(undefined2 *)(param_1 + 0x794b5f);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fb020,local_24);
    local_24[0] = local_24[0] | 0x40000000;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820fb020);
    uVar3 = local_24[0];
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5018,local_24);
    bVar2 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [param_1 + 0xda];
    if (bVar2 < 3) {
      bVar4 = 0xef;
    }
    local_24[0] = local_24[0] & 0xfcffffff;
    if (2 < bVar2) {
      if (bVar2 < 5) {
        bVar4 = 0xcf;
        local_24[0] = local_24[0] | 0x1000000;
      }
      else if (bVar2 < 9) {
        local_24[0] = local_24[0] | 0x2000000;
        bVar4 = 0x8f;
      }
      else {
        local_24[0] = local_24[0] | 0x3000000;
        bVar4 = 0xf;
      }
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5018);
    if (cVar1 != '\0') {
      *(byte *)(param_2 + 0x1b) = *(byte *)(param_2 + 0x1b) | 2;
      switch(uVar3 >> 0x1d) {
      case 1:
        *(byte *)(param_2 + 0x1d) = bVar4 & *(byte *)(param_2 + 0x1d) | cVar1 << 4;
        break;
      case 2:
        *(byte *)(param_2 + 0x1e) = bVar4 & *(byte *)(param_2 + 0x1e) | cVar1 << 4;
        break;
      case 3:
        *(byte *)(param_2 + 0x1f) = bVar4 & *(byte *)(param_2 + 0x1f) | cVar1 << 4;
        break;
      case 4:
        *(byte *)(param_2 + 0x20) = bVar4 & *(byte *)(param_2 + 0x20) | cVar1 << 4;
        break;
      default:
        *(byte *)(param_2 + 0x1c) = bVar4 & *(byte *)(param_2 + 0x1c) | cVar1 << 4;
      }
    }
  }
  return;
}

