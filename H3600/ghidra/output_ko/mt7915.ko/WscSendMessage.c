// module: mt7915.ko
// function: WscSendMessage @ 0x1e25c8
// size: 1428 bytes
//

void WscSendMessage(int param_1,int param_2,int param_3,uint param_4,int param_5,char param_6,
                   char param_7)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  undefined4 *local_60;
  ushort local_56;
  int local_54;
  int local_50;
  int local_4c;
  undefined1 local_48;
  undefined1 local_47;
  ushort local_46;
  char local_44;
  char local_43;
  ushort local_42;
  undefined1 local_40;
  undefined1 local_3f;
  undefined1 local_3e;
  undefined1 local_3d;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined1 local_38;
  byte local_37;
  undefined4 local_36;
  undefined2 local_32;
  undefined4 local_30;
  undefined2 local_2c;
  undefined2 local_2a;
  
  local_54 = 0;
  local_50 = 0;
  bVar1 = *(byte *)(param_5 + 0x1c54);
  if ((int)param_4 < 1 && (param_2 != 6 && param_2 != 1)) {
    return;
  }
  if (2 < DebugLevel) {
    printk("-----> WscSendMessage\n");
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    uVar5 = bVar1 & 0xf;
    __memzero(&local_36,0xe);
    if (param_6 == '\0') {
      uVar6 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      if (uVar5 < uVar6) {
        iVar3 = uVar5 * 0x5834 + param_1;
        local_32 = *(undefined2 *)(param_5 + 0x1c59);
        local_30 = *(undefined4 *)
                    (
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + iVar3 + 0x101);
        local_2a = EAPOL;
        local_36 = *(undefined4 *)(param_5 + 0x1c55);
        local_2c = *(undefined2 *)
                    (
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + iVar3 + 0x105);
      }
    }
    else {
      bVar7 = uVar5 == 1;
      if ((bVar1 & 0xf) == 0 || bVar7) {
        bVar7 = param_6 == '\x01';
      }
      if (bVar7) {
        iVar3 = param_1 + uVar5 * 0x2137b0;
        local_2a = EAPOL;
        local_32 = *(undefined2 *)(param_5 + 0x1c59);
        local_30 = *(undefined4 *)(&DAT_0036db73 + iVar3);
        local_36 = *(undefined4 *)(param_5 + 0x1c55);
        local_2c = *(undefined2 *)(&DAT_0036db77 + iVar3);
      }
    }
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
    __memzero(&local_36,0xe);
    if ((*(uint *)(&DAT_0057ffbc + param_1) & 1) == 0) {
      puVar4 = (undefined4 *)(param_5 + 0x1c55);
    }
    else {
      puVar4 = (undefined4 *)(&DAT_0057ff80 + param_1);
    }
    local_36 = *puVar4;
    local_30 = *(undefined4 *)(&DAT_0036db73 + param_1);
    local_2c = *(undefined2 *)(&DAT_0036db77 + param_1);
    local_32 = *(undefined2 *)(puVar4 + 1);
    local_2a = EAPOL;
  }
  else {
    __memzero(&local_36,0xe);
  }
  local_60 = &local_36;
  uVar5 = param_4 & 0xffff;
  uVar6 = uVar5 + 0xe & 0xffff;
  if ((*(char *)(param_5 + 0x2be1) != '\0') && (*(char *)(param_5 + 0x2bf9) != '\0')) {
    uVar6 = uVar5 + 0x10 & 0xffff;
    uVar5 = uVar5 + *(int *)(param_5 + 0x2bf0);
    local_56 = (ushort)((uVar5 & 0xff) << 8) | (ushort)(uVar5 >> 8) & 0xff;
  }
  __memzero(&local_48,4);
  uVar2 = (ushort)((uVar6 & 0xff) << 8) | (ushort)(uVar6 >> 8);
  local_48 = 1;
  local_47 = 0;
  local_46 = uVar2;
  __memzero(&local_44,5);
  local_43 = *(char *)(param_5 + 0x1c50);
  if (param_7 == '\x01') {
    local_43 = local_43 + '\x01';
    local_44 = param_7;
    *(char *)(param_5 + 0x1c50) = local_43;
  }
  else {
    local_44 = '\x02';
  }
  local_40 = 0xfe;
  local_42 = uVar2;
  __memzero(&local_3f,9);
  local_38 = (undefined1)param_2;
  local_3f = 0;
  local_3c = 0;
  local_3b = 0;
  local_3a = 0;
  local_37 = 0;
  local_3e = 0x37;
  local_3d = 0x2a;
  local_39 = 1;
  if ((*(char *)(param_5 + 0x2be1) != '\0') &&
     (local_37 = *(char *)(param_5 + 0x2bf8) == '\0', *(char *)(param_5 + 0x2bf9) != '\0')) {
    local_37 = local_37 | 2;
  }
  os_alloc_mem(0,&local_54,0x800);
  if (local_54 == 0) {
    return;
  }
  local_50 = 0;
  uVar5 = 0;
  if (param_3 != 0) {
    uVar5 = param_4;
  }
  if ((param_3 == 0 || param_4 == 0) || (int)uVar5 < 0) {
    MakeOutgoingFrame(local_54,&local_50,4,&local_48,5,&local_44,9,&local_3f,0xffffffff);
  }
  else if ((*(char *)(param_5 + 0x2be1) == '\0') || (*(char *)(param_5 + 0x2bf9) == '\0')) {
    MakeOutgoingFrame(local_54,&local_50,4,&local_48,5,&local_44,9,&local_3f,param_4,param_3,
                      0xffffffff);
  }
  else {
    *(undefined1 *)(param_5 + 0x2bf9) = 0;
    local_4c = 0;
    MakeOutgoingFrame(local_54,&local_4c,4,&local_48,5,&local_44,9,&local_3f,2,&local_56,0xffffffff)
    ;
    local_50 = local_4c + local_50;
    MakeOutgoingFrame(local_54 + local_50,&local_4c,param_4,param_3,0xffffffff);
    local_50 = local_50 + local_4c;
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar3 = MacTableLookup(param_1,param_5 + 0x1c55);
    if (*(char *)(param_1 + 0x286285) == '\0') goto LAB_001e2920;
LAB_001e2934:
    if (iVar3 != 0) {
      RTMPToWirelessSta(param_1,iVar3,local_60,0xe,local_54,local_50,1);
      goto LAB_001e289c;
    }
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
LAB_001e2920:
    iVar3 = MacTableLookup2(param_1,param_5 + 0x1c55,0);
    goto LAB_001e2934;
  }
  if (1 < DebugLevel) {
    printk("pEntry is NULL\n");
  }
LAB_001e289c:
  if (local_54 != 0) {
    os_free_mem();
  }
  if (2 < DebugLevel) {
    printk("<----- WscSendMessage\n");
  }
  return;
}

