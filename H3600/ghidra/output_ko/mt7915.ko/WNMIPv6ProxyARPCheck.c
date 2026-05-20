// module: mt7915.ko
// function: WNMIPv6ProxyARPCheck @ 0x226e74
// size: 664 bytes
//

void WNMIPv6ProxyARPCheck(int param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  byte local_3d;
  int local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  uVar4 = (uint)*(byte *)(param_2 + 0x2d);
  local_3d = 0;
  if (uVar4 < 0x68) {
    iVar5 = *(int *)(param_1 + uVar4 * 4 + 0xc);
    if (*(int *)(iVar5 + 0x14) == 1) {
      uVar4 = (uint)*(byte *)(iVar5 + 0xe);
      if ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                [param_1 + 0xda] <= uVar4) {
        printk(&_LC51,0x562);
        dump_stack();
        uVar4 = (uint)*(byte *)(iVar5 + 0xe);
      }
      if (("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n"[uVar4 * 0x5834 + param_1 + 0xc] != '\0') &&
         (iVar5 = IsIPv6RouterAdvertisement(param_1,param_3 + -2,&local_3d), iVar5 != 0)) {
        if (0 < DebugLevel) {
          printk("This packet is router advertisement\n");
        }
        uVar2 = *(ushort *)(param_3 + 4);
        local_3c = CONCAT22(local_3c._2_2_,uVar2);
        printk("WNMIPv6ProxyARPCheck: offset=%d\n",local_3d);
        iVar5 = uVar4 * 0x5834;
        pcVar6 = (char *)(param_3 + 4 + local_3d + 0x34);
        local_3c = ((uVar2 & 0xff) << 8 | (uint)(uVar2 >> 8)) + (-0x10 - (uint)local_3d);
        while (iVar3 = local_3c, 0 < local_3c) {
          bVar1 = pcVar6[1];
          if (*pcVar6 == '\x03') {
            local_38 = *(undefined4 *)(pcVar6 + 0x10);
            uStack_34 = *(undefined4 *)(pcVar6 + 0x14);
            if (param_4 == 0) {
              _raw_spin_lock_bh("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" +
                                param_1 + iVar5 + 0x14);
            }
            for (pcVar7 = *(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" +
                                    param_1 + iVar5 + 0x20);
                pcVar7 != "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + iVar5 + 0x20;
                pcVar7 = *(char **)pcVar7) {
              if (pcVar7[0xe] == '\0') {
                local_30 = *(undefined4 *)(pcVar7 + 0x17);
                uStack_2c = *(undefined4 *)(pcVar7 + 0x1b);
                AddIPv6ProxyARPEntry
                          (param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                   + param_1 + iVar5 + 0xe0,pcVar7 + 8,&local_38,param_4);
              }
            }
            if (param_4 == 0) {
              _raw_spin_unlock_bh("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" +
                                  param_1 + iVar5 + 0x14);
            }
          }
          pcVar6 = pcVar6 + (bVar1 & 0x1f) * 8;
          local_3c = iVar3 + (bVar1 & 0x1f) * -8;
        }
      }
    }
  }
  else {
    printk(&_LC49,0x556);
    dump_stack();
    if (-1 < DebugLevel) {
      printk("%s(): Invalid wdev_idx(%d)\n","WNMIPv6ProxyARPCheck",uVar4);
    }
  }
  return;
}

