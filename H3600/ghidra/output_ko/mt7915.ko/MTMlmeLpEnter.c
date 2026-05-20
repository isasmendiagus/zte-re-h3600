// module: mt7915.ko
// function: MTMlmeLpEnter @ 0x19a51c
// size: 636 bytes
//

void MTMlmeLpEnter(int param_1,undefined4 param_2)

{
  byte bVar1;
  char cVar2;
  int *piVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  
  bVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda];
  iVar4 = GetStaCfgByWdev();
  iVar6 = *(int *)(*(int *)(param_1 + 4) + 0x240);
  if (iVar6 == 0) {
    warn_slowpath_null("include/linux/netdevice.h",0xa06);
    printk(&_LC7);
  }
  else {
    _set_bit(0,iVar6 + 0x50);
  }
  cVar2 = *(char *)(param_1 + 0x286285);
  if (cVar2 == '\0') {
    *(undefined4 *)(iVar4 + 0x2127a8) = 0;
    RTMPZeroMemory(iVar4 + 0x212649,0x15c);
    if (((*(uint *)(param_1 + 0xa39f84) & 0x100) == 0) &&
       (((*(uint *)(iVar4 + 0x212464) & 1) != 0 || ((*(uint *)(param_1 + 0x795124) & 2) != 0)))) {
      __cntl_disconnect_request(param_2,1,iVar4 + 0x212428,8,"MTMlmeLpEnter",0xe5);
      RtmpusecDelay(1000);
    }
    cVar2 = *(char *)(param_1 + 0x286285);
    if (cVar2 == '\0') {
      uVar5 = get_scan_tab_by_wdev(param_1,param_2);
      if (((*(uint *)(iVar4 + 0x212464) & 1) != 0) || ((*(uint *)(param_1 + 0x795124) & 2) != 0)) {
        LinkDown(param_1,0,param_2,0);
      }
      RtmpusecDelay(10000);
      BssTableInit(uVar5);
      cVar2 = *(char *)(param_1 + 0x286285);
    }
  }
  if (cVar2 == '\x01') {
    iVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar4 < (int)(uint)bVar1) {
      hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    }
    piVar3 = (int *)("%s: Allocate memory fail!!!\n" + param_1 + 0xc);
    piVar8 = (int *)0x0;
    for (iVar4 = 1; piVar7 = piVar3,
        iVar6 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0)), iVar4 < iVar6;
        iVar4 = iVar4 + 1) {
      if (*piVar7 != 0) {
        iVar6 = *(int *)(*piVar7 + 0x240);
        if (iVar6 == 0) {
          warn_slowpath_null("include/linux/netdevice.h",0xa06);
          printk(&_LC7);
        }
        else {
          _set_bit(0,iVar6 + 0x50);
        }
      }
      piVar3 = piVar7 + 0x160d;
      piVar8 = piVar7;
    }
    APStop(param_1,piVar8,1);
  }
  HcSetAllSupportedBandsRadioOff(param_1);
  msleep(1000);
  RTMP_RADIO_ON_OFF_CTRL(param_1,2,2);
  uVar5 = HcGetBandByWdev(param_2);
  MTHifPolling(param_1,uVar5);
  chip_set_hif_dma(param_1,2,0);
  FwOwn(param_1);
  return;
}

