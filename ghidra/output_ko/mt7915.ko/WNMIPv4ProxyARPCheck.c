// module: mt7915.ko
// function: WNMIPv4ProxyARPCheck @ 0x226d14
// size: 348 bytes
//

void WNMIPv4ProxyARPCheck(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar2 = (uint)*(byte *)(param_2 + 0x2d);
  if (uVar2 < 0x68) {
    iVar3 = *(int *)(param_1 + uVar2 * 4 + 0xc);
    if (*(int *)(iVar3 + 0x14) == 1) {
      uVar4 = (uint)*(byte *)(iVar3 + 0xe);
      if ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                [param_1 + 0xda] <= uVar4) {
        printk(&_LC51,0x538);
        dump_stack();
        uVar4 = (uint)*(byte *)(iVar3 + 0xe);
      }
      if (param_3 == 0x43 && param_4 == 0x44) {
        iVar3 = MacTableLookup(param_1,param_5 + 0x24);
        iVar1 = param_1 + uVar4 * 0x5834;
        if (((iVar3 != 0 && "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n"[iVar1 + 0xc] != '\0') &&
            (printk("entry func_tb_idx=%d,%d,%d\n",*(undefined1 *)(iVar3 + 0xe4),uVar2),
            *(byte *)(iVar3 + 0xe4) == uVar2)) &&
           ("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n"[iVar1 + 0xc] != '\0')) {
          AddIPv4ProxyARPEntry
                    (param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                             + param_1 + uVar4 * 0x5834 + 0xe0,param_5 + 0x24,param_5 + 0x18);
          return;
        }
      }
    }
  }
  else {
    printk(&_LC49,0x52c);
    dump_stack();
    if (-1 < DebugLevel) {
      printk("%s(): Invalid wdev_idx(%d)\n","WNMIPv4ProxyARPCheck",uVar2);
      return;
    }
  }
  return;
}

