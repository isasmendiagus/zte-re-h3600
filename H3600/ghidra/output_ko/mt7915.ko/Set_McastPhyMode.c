// module: mt7915.ko
// function: Set_McastPhyMode @ 0x32da0
// size: 984 bytes
//

undefined4 Set_McastPhyMode(int *param_1,undefined4 param_2)

{
  char cVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  ushort uVar5;
  int iVar6;
  undefined1 *puVar7;
  uint uVar8;
  int *piVar9;
  char *pcVar10;
  bool bVar11;
  bool bVar12;
  undefined1 auStack_13c [4];
  undefined4 local_138;
  undefined1 local_12f;
  undefined4 local_100;
  undefined2 local_e8;
  undefined2 local_e6;
  
  iVar6 = *param_1;
  uVar8 = *(uint *)(iVar6 + 0x3c);
  cVar1 = os_str_tol(param_2,0,10);
  if ((*(int *)(iVar6 + 0x38) - 0x100U & 0xfffffeff) != 0) {
    if (2 < DebugLevel) {
      printk("Do nothing! This device interface is NOT AP mode!\n");
    }
    return 0;
  }
  uVar8 = uVar8 & 0xff;
  if (*(byte *)((int)param_1 + 0x2b7242) <= uVar8) {
    if (DebugLevel < 3) {
      return 0;
    }
    printk("Invalid device interface!\n");
    return 0;
  }
  if (*(byte *)((int)param_1 + uVar8 * 0x5834 + 0x2b7262) < 0xf) {
    if (cVar1 == '\x04') {
      if (DebugLevel < 3) {
        return 0;
      }
      printk("We could not set VHT mode for multicast frames in 2.4G band!\n");
      return 0;
    }
  }
  else if (cVar1 == '\x01') {
    if (DebugLevel < 3) {
      return 0;
    }
    printk("We could not set CCK mode for multicast frames in 5G band!\n");
    return 0;
  }
  pcVar10 = (char *)((int)param_1 +
                    (int)(
                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + uVar8 * 0x5834 + 0xe0));
  uVar2 = wlan_config_get_ht_bw(pcVar10);
  *(ushort *)(param_1 + uVar8 * 0x160d + 0xadf55) =
       *(ushort *)(param_1 + uVar8 * 0x160d + 0xadf55) & 0xfe7f | (uVar2 & 3) << 7;
  switch(cVar1) {
  case '\0':
    memmove(param_1 + uVar8 * 0x160d + 0xadf55,(void *)((int)param_1 + uVar8 * 0x5834 + 0x2b7d52),2)
    ;
    *(ushort *)(param_1 + uVar8 * 0x160d + 0xadf55) =
         *(ushort *)(param_1 + uVar8 * 0x160d + 0xadf55) & 0xfe7f;
    break;
  case '\x01':
    *(byte *)((int)param_1 + uVar8 * 0x5834 + 0x2b7d55) =
         *(byte *)((int)param_1 + uVar8 * 0x5834 + 0x2b7d55) & 0x1f;
    uVar2 = *(ushort *)(param_1 + uVar8 * 0x160d + 0xadf55);
    uVar5 = uVar2 & 0xfe7f;
    *(ushort *)(param_1 + uVar8 * 0x160d + 0xadf55) = uVar5;
    uVar2 = uVar2 & 0x3f;
    uVar3 = uVar2 + 0x3c & 0x3f;
    uVar2 = uVar2 + 0x34 & 0x3f;
    bVar12 = 0x32 < uVar2;
    bVar11 = uVar2 == 0x33;
    if (0x33 < uVar2) {
      bVar12 = 2 < uVar3;
      bVar11 = uVar3 == 3;
    }
    if (!bVar12 || bVar11) {
      *(byte *)(param_1 + uVar8 * 0x160d + 0xadf55) = (byte)uVar5 & 0xc0 | 3;
    }
    break;
  case '\x02':
    *(byte *)((int)param_1 + uVar8 * 0x5834 + 0x2b7d55) =
         *(byte *)((int)param_1 + uVar8 * 0x5834 + 0x2b7d55) & 0x1f | 0x20;
    uVar2 = *(ushort *)(param_1 + uVar8 * 0x160d + 0xadf55);
    uVar3 = uVar2 & 0xfe7f;
    *(ushort *)(param_1 + uVar8 * 0x160d + 0xadf55) = uVar3;
    if (7 < (uVar2 & 0x3f)) {
      *(byte *)(param_1 + uVar8 * 0x160d + 0xadf55) = (byte)uVar3 & 0xc0 | 7;
    }
    break;
  case '\x03':
    piVar9 = param_1 + uVar8 * 0x160d;
    *(byte *)((int)piVar9 + 0x2b7d55) = *(byte *)((int)piVar9 + 0x2b7d55) & 0x1f | 0x40;
    iVar6 = wlan_operate_get_bw(pcVar10);
    uVar2 = *(ushort *)(piVar9 + 0xadf55);
    uVar3 = 0;
    if (iVar6 != 0) {
      *(ushort *)(piVar9 + 0xadf55) = uVar2 & 0xfe7f | 0x80;
      break;
    }
    goto LAB_00032f28;
  case '\x04':
    piVar9 = param_1 + uVar8 * 0x160d;
    *(byte *)((int)piVar9 + 0x2b7d55) = *(byte *)((int)piVar9 + 0x2b7d55) & 0x1f | 0x80;
    uVar3 = wlan_operate_get_bw(pcVar10);
    uVar2 = *(ushort *)(piVar9 + 0xadf55);
LAB_00032f28:
    *(ushort *)(piVar9 + 0xadf55) = uVar2 & 0xfe7f | (uVar3 & 3) << 7;
    break;
  default:
    if (DebugLevel < 3) {
      return 0;
    }
    printk("unknown Muticast PhyMode %d.\n",cVar1);
    if (DebugLevel < 3) {
      return 0;
    }
    printk("0:Disable, 1:CCK, 2:OFDM, 3:HTMIX, 4:VHT.\n");
    return 0;
  }
  if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
    puVar7 = (undefined1 *)((int)param_1 + 0x2b7be1);
    iVar6 = 0;
    do {
      __memzero(auStack_13c,0x114);
      local_12f = *puVar7;
      local_e8 = (undefined2)param_1[uVar8 * 0x160d + 0xadf55];
      puVar7 = puVar7 + 0x5834;
      local_138 = 2;
      local_100 = 0x100;
      local_e6 = local_e8;
      iVar4 = AsicBssInfoUpdate(param_1,auStack_13c);
      if ((iVar4 != 0) && (2 < DebugLevel)) {
        printk("Fail to apply the bssinfo, BSSID=%d!\n",iVar6);
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
  }
  return 1;
}

