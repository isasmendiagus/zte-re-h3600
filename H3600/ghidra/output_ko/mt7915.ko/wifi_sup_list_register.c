// module: mt7915.ko
// function: wifi_sup_list_register @ 0x155ad0
// size: 448 bytes
//

undefined4 wifi_sup_list_register(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint local_1c;
  
  if (param_2 == 1) {
    local_1c = 0x7fd;
    os_move_mem((void *)(param_1 + 0xa7d098),&local_1c,4);
    return 0;
  }
  if (param_2 == 0) {
    local_1c = 0;
    iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
    uVar4 = (uint)(byte)"rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e];
    uVar5 = *(uint *)(iVar2 + 0x2c);
    if ((uVar5 & 4) != 0) {
      local_1c = local_1c | 1;
    }
    if ((uVar5 & 8) != 0) {
      local_1c = local_1c | 2;
    }
    if ((uVar5 & 0x10) != 0) {
      local_1c = local_1c | 4;
    }
    uVar3 = 0;
    if ((*(uint *)(iVar2 + 0x24) & 0x20) != 0) {
      if ((uVar4 - 0x1e & 0xfb) == 0) {
        uVar3 = 0x10;
      }
      else {
        uVar3 = 8;
      }
    }
    if ((uVar4 - 2 & 0xfd) == 0 ||
        (uVar4 - 0x1f < 2 ||
        (uVar4 - 0x1c < 2 ||
        (uVar4 - 0x18 < 3 ||
        (uVar4 - 0x13 < 2 ||
        (uVar4 - 0xd < 5 || (uVar4 - 9 < 2 || (uVar4 == 0x23 || uVar4 == 0xff)))))))) {
      uVar4 = 0x40;
    }
    else if ((uVar4 - 0x1e & 0xfb) == 0) {
      uVar4 = 0x20;
    }
    else {
      uVar4 = 0;
    }
    uVar4 = uVar3 | local_1c | uVar4;
    if ((*(uint *)(iVar2 + 0x24) & 0x2000000) != 0) {
      uVar4 = uVar4 | 0x80;
    }
    if ((uVar5 & 0x20) != 0) {
      uVar4 = uVar4 | 0x100;
    }
    if ((uVar5 & 0x80) != 0) {
      uVar4 = uVar4 | 0x200;
    }
    local_1c = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           [param_1 + 0xda] << 10 | (uint)*(byte *)(iVar2 + 0x6d) << 0xf |
               (uint)*(byte *)(iVar2 + 0x6d) << 0x13 | uVar4;
    os_move_mem((void *)(param_1 + 0xa7d094),&local_1c,4);
    return 0;
  }
  if (param_2 == 2) {
    uVar1 = 0;
  }
  else {
    uVar1 = 2;
  }
  return uVar1;
}

