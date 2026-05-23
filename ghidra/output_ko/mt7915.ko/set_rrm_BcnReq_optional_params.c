// module: mt7915.ko
// function: set_rrm_BcnReq_optional_params @ 0x221fac
// size: 680 bytes
//

void set_rrm_BcnReq_optional_params(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  byte bVar4;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined4 local_2b;
  undefined2 local_27;
  undefined4 local_25;
  undefined4 local_21;
  undefined4 local_1d;
  undefined1 local_19;
  
  local_31 = 0;
  local_30 = 0;
  local_2b = 0xffffffff;
  local_25 = 0x302d0100;
  local_27 = 0xffff;
  local_21 = 0x463d3632;
  local_1d = 0xc3c0bf7f;
  local_19 = 0xdd;
  local_2f = 0;
  local_2e = 0;
  local_2d = 0;
  local_2c = 0;
  iVar1 = MacTableLookup();
  if (iVar1 == 0) {
    return;
  }
  if (((byte)(*(char *)(param_2 + 9) - 1U) < 0xfe) && (*(char *)(param_2 + 8) == '\0')) {
    iVar2 = (uint)*(byte *)(iVar1 + 0xe4) * 0x5834;
    uVar3 = get_regulatory_class
                      (param_1,*(char *)(param_2 + 9),
                       *(undefined2 *)
                        (
                        "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + param_1 + iVar2 + 0xf8),
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + param_1 + iVar2 + 0xe0);
    iVar2 = DebugLevel;
    *(char *)(param_2 + 8) = (char)uVar3;
    if (2 < iVar2) {
      printk("%s() set optional regclass = %d\n","set_rrm_BcnReq_optional_params",uVar3);
    }
  }
  iVar2 = DebugLevel;
  if (*(short *)(param_2 + 0xc) == 0) {
    *(undefined1 *)(param_2 + 0xd) = 0;
    *(undefined1 *)(param_2 + 0xc) = 0x14;
    if (2 < iVar2) {
      printk("%s() set optional duration = %d\n","set_rrm_BcnReq_optional_params");
    }
  }
  iVar2 = RTMPCompareMemory(param_2 + 0xe,&local_31,6);
  if ((iVar2 == 0) && (RTMPMoveMemory(param_2 + 0xe,&local_2b,6), 2 < DebugLevel)) {
    printk("%s() set optional bssid = %02x:%02x:%02x:%02x:%02x:%02x\n",
           "set_rrm_BcnReq_optional_params",*(undefined1 *)(param_2 + 0xe),
           *(undefined1 *)(param_2 + 0xf),*(undefined1 *)(param_2 + 0x10),
           *(undefined1 *)(param_2 + 0x11),*(undefined1 *)(param_2 + 0x12),
           *(undefined1 *)(param_2 + 0x13));
  }
  iVar2 = DebugLevel;
  if (*(char *)(param_2 + 0x14) == '\0') {
    bVar4 = *(byte *)(iVar1 + 0x11ec) & 0x20;
    if ((*(byte *)(iVar1 + 0x11ec) & 0x20) != 0) {
      *(undefined1 *)(param_2 + 0x14) = 1;
      goto LAB_0022207c;
    }
  }
  else {
    bVar4 = *(char *)(param_2 + 0x14) - 1;
  }
  *(byte *)(param_2 + 0x14) = bVar4;
LAB_0022207c:
  if (2 < iVar2) {
    printk("%s() set optional mode = %d!\n","set_rrm_BcnReq_optional_params",
           *(undefined1 *)(param_2 + 0x14));
  }
  iVar1 = DebugLevel;
  if (*(int *)(param_2 + 0x37) == 0) {
    *(undefined1 *)(param_2 + 0x39) = 0;
    *(undefined1 *)(param_2 + 0x3a) = 0;
    *(undefined1 *)(param_2 + 0x37) = 0x60;
    *(undefined1 *)(param_2 + 0x38) = 0xea;
    if (2 < iVar1) {
      printk("%s() set optional timeout = %d!\n","set_rrm_BcnReq_optional_params",60000);
    }
  }
  iVar1 = DebugLevel;
  if (*(char *)(param_2 + 0x3d) == '\0') {
    *(undefined1 *)(param_2 + 0x3d) = 1;
    if (2 < iVar1) {
      printk("%s() set optional detail = %d\n","set_rrm_BcnReq_optional_params");
    }
    *(undefined1 *)(param_2 + 0x6e) = 0xd;
    RTMPMoveMemory(param_2 + 0x6f,&local_25);
  }
  else {
    *(char *)(param_2 + 0x3d) = *(char *)(param_2 + 0x3d) + -1;
  }
  return;
}

