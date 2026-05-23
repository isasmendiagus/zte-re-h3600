// module: mt7915.ko
// function: WscBuildBeaconIE @ 0x1e2d24
// size: 1240 bytes
//

void WscBuildBeaconIE(int param_1,undefined1 param_2,char param_3,uint param_4,ushort param_5,
                     byte param_6,undefined4 param_7,undefined1 param_8,char param_9)

{
  void *pvVar1;
  size_t sVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  uint uVar6;
  char local_3a;
  undefined1 local_39 [3];
  ushort local_36;
  void *local_34;
  void *local_30;
  size_t local_2c [2];
  
  local_34 = (void *)0x0;
  local_2c[0] = 0;
  local_36 = 0;
  local_3a = param_3;
  local_39[0] = param_2;
  os_alloc_mem(0,&local_34,0x100);
  if (local_34 == (void *)0x0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: Allocate memory fail!!!\n","WscBuildBeaconIE");
    return;
  }
  uVar6 = param_6 & 0xf;
  if (param_9 == '\0') {
    uVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (uVar4 <= uVar6) goto LAB_001e2d8c;
    pcVar5 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             + uVar6 * 0x5834 + param_1 + 0xe0;
  }
  else {
    if (param_9 != '\x02') goto LAB_001e2d8c;
    pcVar5 = &DAT_0036db58 + param_1 + uVar6 * 0x2137b0;
  }
  if (pcVar5 == (char *)0x0) {
LAB_001e2d8c:
    if (-1 < DebugLevel) {
      printk("%s: pWpsCtrl or wdev is NULL!!!\n","WscBuildBeaconIE");
    }
    os_free_mem(local_34);
    return;
  }
  if (2 < DebugLevel) {
    printk("-----> WscBuildBeaconIE\n");
  }
  local_30 = local_34;
  local_2c[0] = 0;
  iVar3 = AppendWSCTLV(0x104a,local_34,pcVar5 + 0x1354,0);
  local_30 = (void *)((int)local_30 + iVar3);
  local_2c[0] = local_2c[0] + iVar3;
  iVar3 = AppendWSCTLV(0x1044,local_30,local_39,0);
  local_30 = (void *)((int)local_30 + iVar3);
  local_2c[0] = local_2c[0] + iVar3;
  if (param_9 == '\0') {
    if (pcVar5[0x3ebd] != '\0') {
      iVar3 = AppendWSCTLV(0x1057,local_30,pcVar5 + 0x3ebd,0);
      local_30 = (void *)((int)local_30 + iVar3);
      local_2c[0] = local_2c[0] + iVar3;
    }
    if (local_3a == '\0') {
      iVar3 = AppendWSCTLV(0x1047,local_30,pcVar5 + 0x3d08);
      local_30 = (void *)((int)local_30 + iVar3);
      local_2c[0] = local_2c[0] + iVar3;
    }
    else {
      iVar3 = AppendWSCTLV(0x1041,local_30,&local_3a,0);
      local_30 = (void *)((int)local_30 + iVar3);
      local_2c[0] = local_2c[0] + iVar3;
LAB_001e30dc:
      local_36 = (ushort)((param_4 & 0xff) << 8) | (ushort)(param_4 >> 8) & 0xff;
      iVar3 = AppendWSCTLV(0x1012,local_30,&local_36,0);
      local_36 = param_5 << 8 | param_5 >> 8;
      local_30 = (void *)((int)local_30 + iVar3);
      local_2c[0] = local_2c[0] + iVar3;
      iVar3 = AppendWSCTLV(0x1053,local_30,&local_36,0);
      local_30 = (void *)((int)local_30 + iVar3);
      local_2c[0] = local_2c[0] + iVar3;
      iVar3 = AppendWSCTLV(0x1047,local_30,pcVar5 + 0x3d08,0);
      local_30 = (void *)((int)local_30 + iVar3);
      local_2c[0] = local_2c[0] + iVar3;
      if (param_9 != '\0') goto LAB_001e2fe8;
    }
    if ((*(ushort *)(pcVar5 + 0x18) & 0xb1) != 0) {
      local_36 = 2;
      goto LAB_001e2ec4;
    }
  }
  else {
    if (local_3a != '\0') {
      iVar3 = AppendWSCTLV(0x1041,local_30,&local_3a,0);
      local_30 = (void *)((int)local_30 + iVar3);
      local_2c[0] = local_2c[0] + iVar3;
      goto LAB_001e30dc;
    }
    iVar3 = AppendWSCTLV(0x1047,local_30,pcVar5 + 0x3d08);
    local_30 = (void *)((int)local_30 + iVar3);
    local_2c[0] = local_2c[0] + iVar3;
LAB_001e2fe8:
    if (param_9 != '\x02') goto LAB_001e2ec4;
    if (0xe < *(ushort *)(pcVar5 + 0x18)) {
      local_36 = 2;
      goto LAB_001e2ec4;
    }
  }
  local_36 = 1;
LAB_001e2ec4:
  iVar3 = AppendWSCTLV(0x103c,local_30,&local_36,0);
  local_30 = (void *)((int)local_30 + iVar3);
  local_2c[0] = iVar3 + local_2c[0];
  if (((pcVar5[0x3e15] != '\0') &&
      (WscGenV2Msg(pcVar5 + 0x12e4,local_3a,param_7,param_8,&local_30,local_2c),
      *(int *)(pcVar5 + 0x3e0c) != 0)) && (*(short *)(pcVar5 + 0x3e0a) != 0)) {
    iVar3 = AppendWSCTLV(*(undefined2 *)(pcVar5 + 0x3e08),local_30);
    local_30 = (void *)((int)local_30 + iVar3);
    local_2c[0] = iVar3 + local_2c[0];
  }
  sVar2 = local_2c[0];
  pvVar1 = local_34;
  pcVar5[0xee3] = (char)local_2c[0] + '\x04';
  pcVar5[0xee2] = -0x23;
  pcVar5[0xee5] = 'P';
  pcVar5[0xee4] = '\0';
  pcVar5[0xee7] = '\x04';
  pcVar5[0xee6] = -0xe;
  memcpy(pcVar5 + 0xee8,local_34,local_2c[0]);
  *(short *)(pcVar5 + 0xee0) = (short)sVar2 + 6;
  if (pvVar1 != (void *)0x0) {
    os_free_mem(pvVar1);
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("<----- WscBuildBeaconIE\n");
  return;
}

