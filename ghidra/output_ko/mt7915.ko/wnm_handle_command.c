// module: mt7915.ko
// function: wnm_handle_command @ 0x22818c
// size: 376 bytes
//

undefined4 wnm_handle_command(int *param_1,undefined1 *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = (uint)*(byte *)(*param_1 + 0x3c);
  switch(*param_2) {
  case 1:
    if (param_2[5] == '\0') {
      *(undefined1 *)((int)param_1 + uVar1 * 0x5834 + 0x2bbee6) = 0;
      UpdateBeaconHandler(param_1,(char *)((int)param_1 +
                                          (int)(
                                               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                               + uVar1 * 0x5834 + 0xe0)),2);
      return 0;
    }
    break;
  case 2:
    if ((param_2[5] & 1) == 0) {
      *(byte *)((int)param_1 + uVar1 * 0x5834 + 0x2bbee6) = param_2[5] & 1;
    }
    else {
      *(undefined1 *)((int)param_1 + uVar1 * 0x5834 + 0x2bbee6) = 1;
    }
    UpdateBeaconHandler(param_1,param_1 + uVar1 * 0x160d + 0xadc92,2);
    return 0;
  case 3:
    iVar3 = MacTableLookup(param_1,param_2 + 9);
    if (iVar3 != 0) {
      Send_BTM_Req(param_1,param_2 + 9,param_2 + 0x13,*(undefined4 *)(param_2 + 0xf));
      return 0;
    }
    break;
  default:
    if (DebugLevel < 0) {
      return 2;
    }
    printk("%s Invalid Command %d\n","wnm_handle_command");
    return 2;
  case 5:
    uVar2 = send_btm_req_ie(param_1,param_2 + 5,*(undefined4 *)(param_2 + 1));
    return uVar2;
  case 6:
    uVar2 = send_btm_req_param(param_1,param_2 + 5,*(undefined4 *)(param_2 + 1));
    return uVar2;
  }
  return 0;
}

