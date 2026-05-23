// module: mt7915.ko
// function: set_mgmt_txpwr_offset @ 0xc0478
// size: 404 bytes
//

undefined4 set_mgmt_txpwr_offset(int *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  
  iVar3 = *(int *)(*param_1 + 0x38);
  uVar4 = *(uint *)(*param_1 + 0x3c);
  if ((iVar3 - 0x100U & 0xfffffeff) == 0) {
    if (param_2 == 0) {
      if (-1 < DebugLevel) {
        printk("%s: Invalid parameters!!\n","set_mgmt_txpwr_offset",iVar3,DebugLevel,param_4);
      }
    }
    else {
      cVar1 = os_str_tol(param_2,0,10);
      bVar5 = (param_1[0xa5b19] & 0xffffU) == 0x7915;
      if (bVar5) {
        cVar2 = -0x20;
      }
      else {
        cVar2 = -0x10;
      }
      if (bVar5) {
        iVar3 = 0x1f;
      }
      else {
        iVar3 = 0xf;
      }
      if (cVar1 <= iVar3 && (int)cVar2 <= (int)cVar1) {
        if (0 < DebugLevel) {
          printk("%s: [TxdPwrOffset]: %u\n","set_mgmt_txpwr_offset",cVar1,DebugLevel,param_4);
        }
        uVar4 = uVar4 & 0xff;
        *(char *)(param_1 + uVar4 * 0x160d + 0xadee1) = cVar1;
        UpdateBeaconHandler(param_1,(char *)((int)param_1 +
                                            (int)(
                                                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                 + uVar4 * 0x5834 + 0xe0)),6);
        UpdateBeaconHandler(param_1,(char *)((int)param_1 +
                                            (int)(
                                                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                 + uVar4 * 0x5834 + 0xe0)),5);
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: [TxdPwrOffset] range [%d,%d]\n","set_mgmt_txpwr_offset",(int)cVar2,iVar3,param_4
              );
      }
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: pObj->ioctl_if_type = %d!!\n","set_mgmt_txpwr_offset",iVar3,DebugLevel,param_4);
  }
  return 0;
}

