// module: mt7915.ko
// function: ap_cls2_err_action @ 0x1e460
// size: 604 bytes
//

void ap_cls2_err_action(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  ushort uVar5;
  uint uVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  byte *pbVar10;
  undefined1 *puVar11;
  undefined2 local_3a;
  undefined4 local_38;
  undefined4 local_34;
  undefined1 auStack_30 [24];
  
  uVar5 = *(ushort *)(param_2 + 0x4e);
  local_38 = 0;
  local_34 = 0;
  local_3a = 6;
  uVar6 = HcGetMaxStaNum();
  if (uVar5 < uVar6) {
    iVar9 = (uint)*(ushort *)(param_2 + 0x4e) * 0x14c0;
    iVar8 = param_1 + iVar9 + 0xa1d20;
    if (iVar8 == 0) goto LAB_0001e5f0;
    iVar9 = param_1 + iVar9;
    if (*(int *)(iVar9 + 0xa1d20) == 0x20001) {
      __ZTE_STA_Assoc_Process(param_1,0x11,0,0,local_3a,0,iVar8,"ap_cls2_err_action",0xbed);
      MacTableDeleteEntry(param_1,*(undefined2 *)(iVar9 + 0xa1e00),*(undefined4 *)(param_2 + 0x2c));
      goto LAB_0001e550;
    }
    uVar6 = get_apidx_by_addr(param_1,*(undefined4 *)(param_2 + 0x28));
    if (uVar6 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      [param_1 + 0xda]) goto LAB_0001e550;
  }
  else {
LAB_0001e5f0:
    uVar6 = get_apidx_by_addr(param_1,*(undefined4 *)(param_2 + 0x28));
    if (uVar6 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      [param_1 + 0xda]) {
      pbVar10 = *(byte **)(param_2 + 0x2c);
      bVar2 = *pbVar10;
      if ((bVar2 & 1) == 0) {
LAB_0001e550:
        iVar8 = os_alloc_mem(param_1,&local_38,0x900);
        if (iVar8 != 0) {
          return;
        }
        if (2 < DebugLevel) {
          puVar11 = *(undefined1 **)(param_2 + 0x2c);
          printk("AUTH - Class 2 error, Send DEAUTH frame to %02x:%02x:%02x:%02x:%02x:%02x\n",
                 *puVar11,puVar11[1],puVar11[2],puVar11[3],puVar11[4],puVar11[5]);
        }
        MgtMacHeaderInit(param_1,auStack_30,0xc,0,*(undefined4 *)(param_2 + 0x2c),
                         *(undefined4 *)(param_2 + 0x28),*(undefined4 *)(param_2 + 0x28));
        MakeOutgoingFrame(local_38,&local_34,0x18,auStack_30,2,&local_3a,0xffffffff);
        MiniportMMRequest(param_1,0,local_38,local_34);
        os_free_mem(local_38);
        return;
      }
      if (DebugLevel < 2) {
        return;
      }
      bVar1 = pbVar10[3];
      bVar3 = pbVar10[1];
      pcVar7 = "AUTH - Class 2 error but sta %02x:%02x:%02x:%02x:%02x:%02x is BM addr\n";
      bVar4 = pbVar10[2];
      goto LAB_0001e648;
    }
  }
  if (DebugLevel < 3) {
    return;
  }
  pbVar10 = *(byte **)(param_2 + 0x28);
  pcVar7 = "AUTH - Class 2 error but not my bssid %02x:%02x:%02x:%02x:%02x:%02x\n";
  bVar1 = pbVar10[3];
  bVar2 = *pbVar10;
  bVar3 = pbVar10[1];
  bVar4 = pbVar10[2];
LAB_0001e648:
  printk(pcVar7,bVar2,bVar3,bVar4,bVar1,pbVar10[4],pbVar10[5]);
  return;
}

