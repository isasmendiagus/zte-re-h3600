// module: mt7915.ko
// function: fw_log_to_ethernet @ 0x1d5058
// size: 712 bytes
//

void fw_log_to_ethernet(int param_1,void *param_2,uint param_3)

{
  ushort uVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  undefined2 *puVar6;
  undefined1 *puVar7;
  uint uVar8;
  uint uVar9;
  undefined4 uVar10;
  int iVar11;
  bool bVar12;
  uint local_34;
  undefined4 local_2e;
  
  uVar9 = *(uint *)(param_1 + 0xa7cc28);
  if (uVar9 == 0xffffffff) {
    local_34 = 0;
  }
  else {
    local_34 = uVar9 & 0xffffff | 0xfe000000;
  }
  bVar12 = (param_3 & 1) != 0;
  uVar8 = param_3;
  if (bVar12) {
    uVar8 = param_3 + 1;
  }
  uVar8 = uVar8 & 0xffff;
  iVar3 = idm_skb_stack_pop(1,param_3 + 0x2c);
  if (iVar3 == 0) {
    iVar3 = __alloc_skbuff(param_3 + 0x4c,0x20,0,0xffffffff);
    if (iVar3 == 0) {
      return;
    }
    iVar4 = *(int *)(iVar3 + 0xcc) + 0x20;
    iVar11 = *(int *)(iVar3 + 0xc0) + 0x20;
    g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
    *(int *)(iVar3 + 0xcc) = iVar4;
    *(int *)(iVar3 + 0xc0) = iVar11;
    if (0x63f < param_3 + 0x2c) {
      *(ushort *)(iVar3 + 0xbc) = *(ushort *)(iVar3 + 0xbc) & 0xff0f | 0x40;
    }
  }
  else {
    iVar4 = *(int *)(iVar3 + 0xcc);
    iVar11 = *(int *)(iVar3 + 0xc0);
    *(ushort *)(iVar3 + 0xbc) = *(ushort *)(iVar3 + 0xbc) & 0xff0f | 0x40;
    g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
  }
  uVar10 = *(undefined4 *)
            (
            "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            + param_1 + 0xe0);
  *(int *)(iVar3 + 0xcc) = iVar4 + 0x2a;
  *(int *)(iVar3 + 0xc0) = iVar11 + 0x2a;
  *(undefined4 *)(iVar3 + 0x18) = uVar10;
  pvVar5 = (void *)skb_put(iVar3,uVar8);
  pvVar5 = memcpy(pvVar5,param_2,param_3);
  if (bVar12) {
    *(undefined1 *)((int)pvVar5 + param_3) = 0;
    puVar6 = (undefined2 *)skb_push(iVar3,8);
    puVar6[1] = 0x88d9;
    *puVar6 = 0x31d4;
  }
  else {
    puVar6 = (undefined2 *)skb_push(iVar3,8);
    puVar6[1] = 0x88d9;
    *puVar6 = 0x31d4;
  }
  uVar1 = (ushort)((uVar8 + 8 & 0xff) << 8) | (ushort)(uVar8 + 8 >> 8) & 0xff;
  *(uint *)(puVar6 + -4) = uVar9;
  puVar6[2] = uVar1;
  *(uint *)(puVar6 + -6) = local_34;
  puVar6[-2] = uVar1;
  puVar6[3] = 0;
  puVar6[-1] = 0x1100;
  uVar2 = Checksum16(puVar6 + -6,uVar8 + 0x14);
  puVar6[3] = uVar2;
  puVar7 = (undefined1 *)skb_push(iVar3,0x14);
  puVar7[1] = 0;
  *(undefined2 *)(puVar7 + 4) = 0;
  *(ushort *)(puVar7 + 2) =
       (ushort)((uVar8 + 0x1c & 0xff) << 8) | (ushort)(uVar8 + 0x1c >> 8) & 0xff;
  *(undefined2 *)(puVar7 + 10) = 0;
  *(uint *)(puVar7 + 0xc) = local_34;
  puVar7[8] = 7;
  *(uint *)(puVar7 + 0x10) = uVar9;
  *puVar7 = 0x45;
  *(undefined2 *)(puVar7 + 6) = 0x40;
  puVar7[9] = 0x11;
  uVar2 = Checksum16(puVar7,0x14);
  *(undefined2 *)(puVar7 + 10) = uVar2;
  pvVar5 = (void *)skb_push(iVar3,0xe);
  uVar10 = *(undefined4 *)
            (
            "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            + param_1 + 0xfb);
  uVar2 = *(undefined2 *)
           (
           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + param_1 + 0xff);
  local_2e._1_1_ = (char)((uint)uVar10 >> 8);
  local_2e._0_1_ = (byte)uVar10;
  local_2e._2_2_ = (undefined2)((uint)uVar10 >> 0x10);
  if (local_2e._1_1_ == -1) {
    local_2e._0_2_ = (ushort)(byte)local_2e;
  }
  else {
    local_2e._0_2_ = CONCAT11(local_2e._1_1_ + '\x01',(byte)local_2e);
  }
  pvVar5 = memmove(pvVar5,(void *)(param_1 + 0xa7cc2c),6);
  *(undefined2 *)((int)pvVar5 + 10) = uVar2;
  *(undefined4 *)((int)pvVar5 + 6) = local_2e;
  *(undefined2 *)((int)pvVar5 + 0xc) = 8;
  RtmpOsPktRcvHandle(iVar3,*(undefined4 *)(param_1 + 0xa1904));
  return;
}

