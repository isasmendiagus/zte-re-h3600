// module: mt7915.ko
// function: ZTE_ReportSTARssiInfo @ 0x159b18
// size: 836 bytes
//

void ZTE_ReportSTARssiInfo(int param_1,uint param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  ushort uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  uint uVar8;
  int *piVar9;
  undefined4 *puVar10;
  char cVar11;
  int local_378 [32];
  int local_2f8;
  char local_2f4 [64];
  int local_2b4;
  undefined4 local_2b0;
  undefined2 local_2ac;
  char local_2aa;
  undefined4 local_2a8 [161];
  
  memset(local_378,0,0xc4);
  if (0 < DebugLevel) {
    printk("%s : band_idx value=%d scantype=%d\n","ZTE_ReportSTARssiInfo",param_2,
           *(undefined4 *)(param_1 + (param_2 + 0x28ddc6) * 4));
  }
  if (*(int *)(param_1 + (param_2 + 0x28ddc6) * 4) == 0) {
    local_378[0] = param_2 * 5;
    piVar9 = local_378;
    iVar6 = param_1 + 0xa3724e;
    uVar8 = 0;
    do {
      if (0 < DebugLevel) {
        printk("switch 0 %s : pMntEntry %u bValid=%d band=%u Count=%lu rssi: %d %d %d %d\n",
               "ZTE_ReportSTARssiInfo",uVar8,*(undefined1 *)(iVar6 + -0x1a),
               *(undefined1 *)(iVar6 + -0x19),*(undefined4 *)(iVar6 + -0x16),
               (int)*(char *)(iVar6 + 4),(int)*(char *)(iVar6 + 5),(int)*(char *)(iVar6 + 6),
               (int)*(char *)(iVar6 + 7));
      }
      if ((*(char *)(iVar6 + -0x1a) != '\0') && (*(byte *)(iVar6 + -0x19) == param_2)) {
        local_2f8 = local_2f8 + 1;
        if (9 < uVar8) {
          return;
        }
        iVar4 = *(int *)(iVar6 + -0x16);
        uVar2 = *(undefined2 *)(iVar6 + -2);
        piVar9[2] = *(int *)(iVar6 + -6);
        *(undefined2 *)(piVar9 + 3) = uVar2;
        if (iVar4 == 0) {
          cVar11 = -100;
          builtin_strncpy(local_2f4,"Query STA not found!",0x14);
          local_2f4[0x14] = 0;
          piVar9[4] = -100;
        }
        else {
          iVar4 = RTMPAvgRssi(param_1,iVar6);
          piVar9[4] = iVar4;
          cVar11 = (char)iVar4;
        }
        iVar4 = DebugLevel;
        *(char *)(param_2 * 10 + 0x5f4530 + uVar8) = cVar11;
        if (2 < iVar4) {
          printk("7613 g_aucSTARssiInfo[%d]=%d\n",uVar8,(int)cVar11);
        }
      }
      uVar8 = uVar8 + 1;
      piVar9 = piVar9 + 3;
      iVar6 = iVar6 + 0x44;
    } while (uVar8 != 0x10);
  }
  else {
    __memzero(&local_2b4,0x28c);
    local_2b0 = *(undefined4 *)
                 (
                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + param_1 + 0x101);
    local_2ac = *(undefined2 *)
                 (
                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + param_1 + 0x105);
    local_2b4 = param_2 * 5;
    puVar7 = (undefined4 *)(param_1 + 0xa37248);
    iVar6 = 0;
    puVar10 = local_2a8;
    do {
      if (0 < DebugLevel) {
        printk("switch 1 %s : pMntEntry %u bValid=%d band=%u Count=%lu rssi: %d %d %d %d\n",
               "ZTE_ReportSTARssiInfo",iVar6,*(undefined1 *)(puVar7 + -5),
               *(undefined1 *)((int)puVar7 + -0x13),puVar7[-4],(int)*(char *)((int)puVar7 + 10),
               (int)*(char *)((int)puVar7 + 0xb),(int)*(char *)(puVar7 + 3),
               (int)*(char *)((int)puVar7 + 0xd));
      }
      iVar6 = iVar6 + 1;
      if (((*(char *)(puVar7 + -5) != '\0') && (*(byte *)((int)puVar7 + -0x13) == param_2)) &&
         (puVar7[-4] != 0)) {
        uVar5 = *puVar7;
        uVar1 = *(undefined1 *)(param_1 + param_2 + 0xa376a9);
        local_2aa = local_2aa + '\x01';
        uVar3 = *(ushort *)(param_1 + (param_2 + 0x51bb90) * 2);
        *(undefined2 *)(puVar10 + 1) = *(undefined2 *)(puVar7 + 1);
        *(undefined1 *)(puVar10 + 4) = uVar1;
        *puVar10 = uVar5;
        puVar10[2] = (uint)uVar3;
        uVar5 = RTMPAvgRssi(param_1,(int)puVar7 + 6);
        puVar10[3] = uVar5;
        if (2 < DebugLevel) {
          printk("%s rssi=%d\n","ZTE_ReportSTARssiInfo",uVar5);
        }
      }
      puVar10 = puVar10 + 5;
      puVar7 = puVar7 + 0x11;
    } while (iVar6 != 0x10);
    Kernel_ASEND("multiapd.map.slave",0xa2bb,&local_2b4,0x28c,0,0);
  }
  return;
}

