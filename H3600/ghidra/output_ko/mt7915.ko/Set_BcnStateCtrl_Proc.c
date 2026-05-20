// module: mt7915.ko
// function: Set_BcnStateCtrl_Proc @ 0x2fdac
// size: 316 bytes
//

undefined4 Set_BcnStateCtrl_Proc(int *param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = *(uint *)(*param_1 + 0x3c);
  bVar1 = os_str_tol(param_2,0,10);
  iVar2 = hc_get_hif_type(param_1[0x29e5e8]);
  if (iVar2 == 2) {
    if ((byte)(bVar1 - 1) < 3) {
      uVar3 = uVar3 & 0xff;
      if ((char *)((int)param_1 +
                  (int)(
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + uVar3 * 0x5834 + 0xe0)) != (char *)0x0) {
        if (param_1[uVar3 * 0x160d + 0xadee5] != 1) {
          param_1[uVar3 * 0x160d + 0xadee5] = (uint)bVar1;
          return 1;
        }
        return 1;
      }
      printk(&_LC379,0x4e7c);
      dump_stack();
      if (-1 < DebugLevel) {
        printk("%s: pMbss == NULL!!\n","Set_BcnStateCtrl_Proc");
        return 0;
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s: bcn_state is incorrect!!\n","Set_BcnStateCtrl_Proc");
      return 0;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: chipcap is not HIF_MT\n","Set_BcnStateCtrl_Proc");
  }
  return 0;
}

