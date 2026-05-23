// module: mt7915.ko
// function: ZTE_StartAirMonitor @ 0x1595a8
// size: 1388 bytes
//

void ZTE_StartAirMonitor(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  char *pcVar9;
  uint local_130;
  uint local_12c;
  uint local_128;
  uint local_124;
  uint local_120;
  int local_114;
  char acStack_10c [32];
  undefined1 auStack_ec [132];
  char local_68 [32];
  uint local_48;
  char acStack_44 [32];
  
  memset(auStack_ec,0,0xc4);
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (((iVar1 == 0) || (*(int *)(param_2 + 0x10) == 0)) || (*(short *)(param_2 + 0x14) != 0x48)) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s : parameter error length=%d size=%lu\n","ZTE_StartAirMonitor",
           *(undefined2 *)(param_2 + 0x14),0x48);
    return;
  }
  uVar2 = HcGetBandByWdev();
  if (0 < DebugLevel) {
    printk("%s : band_idx value=%d\n","ZTE_StartAirMonitor",uVar2);
  }
  if (1 < uVar2) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s : band_idx error value=%d\n","ZTE_StartAirMonitor",uVar2);
    return;
  }
  pbVar3 = (byte *)vmalloc(0x48);
  if (pbVar3 == (byte *)0x0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s : alloc memory failed size=%lu\n","ZTE_StartAirMonitor",0x48);
    return;
  }
  uVar6 = (uint)*(ushort *)(param_2 + 0x14);
  uVar7 = *(uint *)(((uint)&local_130 & 0xffffe000) + 8);
  if (!CARRY4(*(uint *)(param_2 + 0x10),uVar6) && *(uint *)(param_2 + 0x10) + uVar6 <= uVar7) {
    uVar7 = 0;
  }
  if (uVar7 == 0) {
    iVar4 = __copy_from_user();
    if (iVar4 != 0) goto LAB_00159778;
  }
  else if (uVar6 != 0) {
    __memzero(pbVar3,uVar6);
    goto LAB_00159778;
  }
  if (*(char *)((int)param_1 + 0xa37233) == '\x01') {
    builtin_strncpy(local_68,"Query instance alreadry existed!",0x20);
    local_48 = local_48 & 0xffffff00;
    vfree(pbVar3);
    return;
  }
  if (pbVar3[0x42] != 0) {
    uVar6 = 0;
    pbVar8 = pbVar3 + 4;
    do {
      iVar4 = memcmp(pbVar8,&BROADCAST_ADDR,6);
      uVar6 = uVar6 + 1;
      if (iVar4 == 0) {
LAB_00159730:
        builtin_strncpy(local_68,"STA Mac is Invaild or assocaitio",0x20);
        local_48._0_1_ = 'n';
        local_48._1_1_ = 'e';
        local_48._2_1_ = 'd';
        local_48._3_1_ = ' ';
        builtin_strncpy(acStack_44,"with current AP!",0x10);
        acStack_44[0x10] = 0;
        vfree(pbVar3);
        return;
      }
      iVar4 = memcmp(pbVar8,&ZERO_MAC_ADDR,6);
      if ((iVar4 == 0) || (iVar4 = MacTableLookup(param_1,pbVar8), iVar4 != 0)) goto LAB_00159730;
      pbVar8 = pbVar8 + 6;
    } while (uVar6 < pbVar3[0x42]);
  }
  *(undefined1 *)((int)param_1 + uVar2 + 0xa376ab) = *(undefined1 *)(iVar1 + 0x1a);
  if ((*pbVar3 == 0) && (*(int *)(pbVar3 + 0x44) == 1)) {
    *pbVar3 = *(byte *)(iVar1 + 0x1a);
  }
  param_1[uVar2 + 0x28ddc6] = *(int *)(pbVar3 + 0x44);
  local_114 = (int)param_1 + (short)uVar2 * 2 + 0xa30000;
  *(undefined2 *)((int)param_1 + (short)uVar2 * 2 + 0xa37720) = *(undefined2 *)(pbVar3 + 0x40);
  *(byte *)((int)param_1 + uVar2 + 0xa376a9) = *pbVar3;
  *(undefined1 *)((int)param_1 + uVar2 + 0xa376ad) = *(undefined1 *)(iVar1 + 0xe);
  *(bool *)((int)param_1 + uVar2 + 0xa376a5) = *pbVar3 == 0;
  if (pbVar3[0x42] != 0) {
    uVar6 = 0;
    pbVar8 = pbVar3;
    do {
      local_130 = (uint)pbVar8[5];
      local_12c = (uint)pbVar8[6];
      local_128 = (uint)pbVar8[7];
      local_124 = (uint)pbVar8[8];
      local_120 = (uint)pbVar8[9];
      snprintf(acStack_10c,0x20,"%02x:%02x:%02x:%02x:%02x:%02x",(uint)pbVar8[4]);
      uVar7 = uVar6 & 0xffff;
      uVar6 = uVar6 + 1;
      Set_Enable_MonitorTarget_Proc(param_1,acStack_10c,uVar7);
      pbVar8 = pbVar8 + 6;
    } while (uVar6 < pbVar3[0x42]);
  }
  Set_MonitorClearCounter_Proc(param_1,&_LC138);
  if (*(char *)((int)param_1 + uVar2 + 0xa376ab) != *(char *)((int)param_1 + uVar2 + 0xa376a9)) {
    AsicDisableSync(param_1,0);
    if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
      uVar6 = 0;
      do {
        pcVar9 = (char *)((int)param_1 +
                         (int)(
                              "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                              + uVar6 * 0x5834 + 0xe0));
        if (((pcVar9 != (char *)0x0) && (uVar7 = HcGetBandByWdev(pcVar9), uVar7 == uVar2)) &&
           ((char)param_1[uVar6 * 0x160d + 0xadf59] != '\0')) {
          UpdateBeaconHandler(param_1,pcVar9,6);
        }
        uVar6 = uVar6 + 1 & 0xff;
      } while (uVar6 < *(byte *)((int)param_1 + 0x2b7242));
    }
    if (*(char *)((int)param_1 + uVar2 + 0xa376a5) == '\x01') {
      uVar5 = FirstChannel(param_1,param_1 + (uint)*(byte *)((int)param_1 + uVar2 + 0xa376ad) *
                                             0x160d + 0xadc92);
      *(char *)((int)param_1 + uVar2 + 0xa376a7) = (char)uVar5;
      wlan_operate_scan(param_1 + (uint)*(byte *)((int)param_1 + uVar2 + 0xa376ad) * 0x160d +
                                  0xadc92,uVar5);
    }
    else {
      wlan_operate_scan(param_1 + (uint)*(byte *)((int)param_1 + uVar2 + 0xa376ad) * 0x160d +
                                  0xadc92,*(undefined1 *)((int)param_1 + uVar2 + 0xa376a9));
    }
  }
  Set_Enable_Air_Monitor_Proc(param_1,&_LC138);
  ZTE_MonitorTimerRelease(param_1,uVar2);
  ZTE_MonitorTimerInit(param_1,uVar2);
  if (*(short *)(local_114 + 0x7720) == 0) {
    if (*(char *)((int)param_1 + uVar2 + 0xa376a5) == '\0') {
      uVar5 = 0x960;
    }
    else {
      uVar5 = 200;
    }
    RTMPSetTimer(param_1 + uVar2 * 0xd + 0x28ddac,uVar5);
  }
  else {
    RTMPSetTimer(param_1 + uVar2 * 0xd + 0x28ddac);
  }
LAB_00159778:
  vfree(pbVar3);
  return;
}

