// module: mt7915.ko
// function: MtAsicSetMbssWdevIfAddrGen2 @ 0x19a974
// size: 412 bytes
//

void MtAsicSetMbssWdevIfAddrGen2(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  byte unaff_r8;
  byte bVar4;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  
  bVar4 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda];
  uVar3 = (uint)*(byte *)(param_2 + 0xe);
  local_2e = 0;
  local_2c = 0;
  if (bVar4 < 3) {
    unaff_r8 = 0xef;
  }
  local_2a = 0;
  if (2 < bVar4) {
    if (bVar4 < 5) {
      unaff_r8 = 0xcf;
    }
    else if (bVar4 < 9) {
      unaff_r8 = 0x8f;
    }
    else {
      unaff_r8 = 0xf;
    }
  }
  if (uVar3 == 0) {
    *(undefined4 *)(param_2 + 0x1b) = *(undefined4 *)(param_1 + 0x794b5b);
    *(undefined2 *)(param_2 + 0x1f) = *(undefined2 *)(param_1 + 0x794b5f);
  }
  else {
    iVar2 = param_1 + (uVar3 - 1) * 6;
    iVar1 = memcmp(&local_2e,(undefined4 *)(iVar2 + 0x794b61),6);
    if (iVar1 == 0) {
      *(undefined4 *)(param_2 + 0x1b) = *(undefined4 *)(param_1 + 0x794b5b);
      *(undefined2 *)(param_2 + 0x1f) = *(undefined2 *)(param_1 + 0x794b5f);
      if ((uVar3 < bVar4 >> 1) ||
         (*(char *)(param_2 + 0x20) = *(char *)(param_2 + 0x20) + '\x01', uVar3 != bVar4 >> 1)) {
        *(byte *)(param_2 + 0x1b) = *(byte *)(param_2 + 0x1b) | 2;
      }
      bVar4 = *(byte *)(param_2 + 0x1e) & unaff_r8 | (byte)((uVar3 & 0xf) << 4);
      if (0xf < uVar3) {
        bVar4 = bVar4 ^ 1;
      }
      *(byte *)(param_2 + 0x1e) = bVar4;
      *(undefined4 *)(iVar2 + 0x794b61) = *(undefined4 *)(param_2 + 0x1b);
      *(undefined2 *)(iVar2 + 0x794b65) = *(undefined2 *)(param_2 + 0x1f);
    }
    else {
      *(undefined4 *)(param_2 + 0x1b) = *(undefined4 *)(iVar2 + 0x794b61);
      *(undefined2 *)(param_2 + 0x1f) = *(undefined2 *)(iVar2 + 0x794b65);
    }
  }
  if (2 < DebugLevel) {
    printk("\n%s mbss_idx = %d, if_addr = %02x:%02x:%02x:%02x:%02x:%02x\n",
           "MtAsicSetMbssWdevIfAddrGen2",uVar3,*(undefined1 *)(param_2 + 0x1b),
           *(undefined1 *)(param_2 + 0x1c),*(undefined1 *)(param_2 + 0x1d),
           *(undefined1 *)(param_2 + 0x1e),*(undefined1 *)(param_2 + 0x1f),
           *(undefined1 *)(param_2 + 0x20));
  }
  return;
}

