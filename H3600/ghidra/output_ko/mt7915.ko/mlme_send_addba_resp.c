// module: mt7915.ko
// function: mlme_send_addba_resp @ 0xa2bb4
// size: 752 bytes
//

void mlme_send_addba_resp(int param_1,ushort *param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  bool bVar6;
  int iVar7;
  int iVar8;
  ushort *puVar9;
  undefined4 local_54;
  undefined4 local_50;
  undefined1 auStack_49 [24];
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  ushort local_2e;
  byte local_2c;
  byte local_2b;
  ushort local_2a;
  
  iVar8 = *(int *)(param_2 + 0x496);
  local_54 = 0;
  iVar2 = GetStaCfgByWdev(param_1,iVar8);
  iVar3 = mlme_addba_resp_sanity(param_1,param_2,*(undefined4 *)(param_2 + 0x484));
  if (iVar3 == 1) {
    iVar3 = os_alloc_mem(param_1,&local_54,0x900);
    if (iVar3 == 0) {
      __memzero(auStack_49,0x21);
      puVar9 = param_2 + 1;
      uVar1 = *param_2;
      iVar3 = HcGetBandByWdev(iVar8);
      cVar5 = *(char *)(param_1 + 0x286285);
      if (cVar5 == '\x01') {
        iVar7 = (uint)uVar1 * 0x14c0 + param_1;
        iVar4 = *(int *)(iVar7 + 0xa1d20);
        if (iVar4 == 2 || iVar4 == 0x40001) {
          ActHeaderInit(param_1,auStack_49,puVar9,iVar8 + 0x1b,puVar9);
          cVar5 = *(char *)(param_1 + 0x286285);
        }
        else {
          iVar8 = param_1 + (uint)*(byte *)(iVar7 + 0xa1e04) * 0x5834;
          ActHeaderInit(param_1,auStack_49,puVar9,
                        "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + iVar8 + 0xfb,
                        "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + iVar8 + 0x101);
          cVar5 = *(char *)(param_1 + 0x286285);
        }
      }
      if (iVar2 != 0 && cVar5 == '\0') {
        if ((*(uint *)(param_1 + 0x795124) & 2) == 0) {
          ActHeaderInit(param_1,auStack_49,iVar2 + 0x212428,iVar2 + 0x1b,puVar9);
        }
        else {
          ActHeaderInit(param_1,auStack_49,puVar9,iVar2 + 0x1b,iVar2 + 0x212428);
        }
      }
      local_2f = *(undefined1 *)((int)param_2 + 9);
      local_2e = (ushort)(byte)param_2[4];
      local_31 = 3;
      local_30 = 1;
      bVar6 = false;
      if ((char)param_2[5] != '\0') {
        bVar6 = *(short *)((uint)uVar1 * 0x14c0 + param_1 + 0xa29e8) == 0;
      }
      local_2a = param_2[7];
      if ((*(uint *)(param_1 + iVar3 * 0x24 + 0xa7d18c) & 0x800) != 0) {
        bVar6 = false;
      }
      local_2c = bVar6 | 2U | (*(byte *)((int)param_2 + 0xb) & 0xf) << 2 | (char)param_2[6] << 6;
      local_2b = (byte)(((uint)param_2[6] << 0x16) >> 0x18);
      MakeOutgoingFrame(local_54,&local_50,0x21,auStack_49,0xffffffff);
      MiniportMMRequest(param_1,1,local_54,local_50);
      os_free_mem(local_54);
      if (2 < DebugLevel) {
        printk("%s(%d): TID(%d), BufSize(%d) <==\n","mlme_send_addba_resp",param_2[0x490],
               ((uint)local_2c << 0x1a) >> 0x1c,(uint)local_2b << 2 | (uint)(local_2c >> 6));
      }
    }
    else if (2 < DebugLevel) {
      printk("ACTION - PeerBAAction() allocate memory failed\n");
    }
  }
  return;
}

