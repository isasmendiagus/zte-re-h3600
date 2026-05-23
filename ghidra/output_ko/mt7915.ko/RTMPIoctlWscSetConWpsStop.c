// module: mt7915.ko
// function: RTMPIoctlWscSetConWpsStop @ 0x361b4
// size: 640 bytes
//

uint RTMPIoctlWscSetConWpsStop(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  uint uVar6;
  undefined4 local_40;
  uint uStack_3c;
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  int local_24 [2];
  
  uVar6 = *(uint *)(*param_1 + 0x3c);
  os_alloc_mem(0,local_24,0x16);
  if (local_24[0] == 0) {
    return 0;
  }
  uVar2 = *(uint *)(param_2 + 0x10);
  uVar4 = (uint)*(ushort *)(param_2 + 0x14);
  uVar3 = *(uint *)(((uint)&local_40 & 0xffffe000) + 8);
  if (!CARRY4(uVar2,uVar4) && uVar2 + uVar4 <= uVar3) {
    uVar3 = 0;
  }
  if (uVar3 == 0) {
    uVar4 = __copy_from_user(local_24[0],uVar2,uVar4);
  }
  else if (uVar4 != 0) {
    __memzero(local_24[0],uVar4);
  }
  if (2 < DebugLevel) {
    printk("CON_WPS BAND_STOP_CMD From[%s], isApCli[%d], is2gBand[%d]\n",local_24[0],
           (int)*(char *)(local_24[0] + 0x11),(int)*(char *)(local_24[0] + 0x10));
  }
  if (*(char *)(local_24[0] + 0x11) == '\0') {
    uVar6 = uVar6 & 0xff;
    iVar1 = param_1[uVar6 * 0x160d + 0xae14d];
    if ((param_1[uVar6 * 0x160d + 0xae14b] != 0) &&
       ((char)param_1[uVar6 * 0x160d + 0xaebc4] == '\x01')) {
      if (2 < DebugLevel) {
        printk("FROM IOCTL CON_WPS[%d]: Stop the AP Wsc Machine\n",uVar6);
      }
      local_40 = 0;
      local_38 = 0;
      local_34 = 0;
      local_30 = 0;
      uStack_3c = uVar6;
      WscBuildBeaconIE(param_1,(char)iVar1,0,0);
      uStack_3c = 0;
      local_40 = 0;
      local_34 = 0;
      local_30 = 0;
      local_2c = 0;
      local_38 = uVar6;
      WscBuildProbeRespIE(param_1,3,(char)iVar1,0);
      UpdateBeaconHandler(param_1,(char *)((int)param_1 +
                                          (int)(
                                               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                               + uVar6 * 0x5834 + 0xe0)),2);
      _WscStop(param_1,0,param_1 + uVar6 * 0x160d + 0xae14b,0);
    }
  }
  else {
    piVar5 = param_1 + 0xdbb8f;
    do {
      if (2 < DebugLevel) {
        printk("CON_WPS FROM IOCTL: Stop the %s WPS, state [%d]\n",piVar5[-0x4b9],piVar5[4]);
      }
      if (piVar5[4] != 0) {
        _WscStop(param_1,1,piVar5,0);
        *piVar5 = 0;
      }
      piVar5 = piVar5 + 0x84dec;
    } while (piVar5 != param_1 + 0x1e5767);
  }
  os_free_mem(local_24[0]);
  return uVar4;
}

