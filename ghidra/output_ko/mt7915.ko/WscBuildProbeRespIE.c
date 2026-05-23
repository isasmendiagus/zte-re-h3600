// module: mt7915.ko
// function: WscBuildProbeRespIE @ 0x1e3200
// size: 1788 bytes
//

void WscBuildProbeRespIE(int param_1,undefined1 param_2,undefined1 param_3,char param_4,
                        ushort param_5,ushort param_6,byte param_7,undefined4 param_8,
                        undefined4 param_9,char param_10)

{
  short sVar1;
  void *pvVar2;
  int iVar3;
  size_t sVar4;
  uint uVar5;
  char *pcVar6;
  uint extraout_r12;
  bool bVar7;
  ushort *local_48;
  char local_3b;
  undefined1 local_3a;
  undefined1 local_39 [3];
  ushort local_36;
  void *local_34;
  void *local_30;
  size_t local_2c [2];
  
  local_34 = (void *)0x0;
  local_2c[0] = 0;
  local_36 = 0;
  local_3b = param_4;
  local_3a = param_3;
  local_39[0] = param_2;
  os_alloc_mem(0,&local_34,0x200);
  if (local_34 == (void *)0x0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: Allocate memory fail!!!\n","WscBuildProbeRespIE");
    return;
  }
  uVar5 = param_7 & 0xf;
  if (param_10 == '\0') {
    pcVar6 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             + uVar5 * 0x5834 + param_1 + 0xe0;
  }
  else {
    if (param_10 != '\x02') goto LAB_001e37e4;
    pcVar6 = &DAT_0036db58 + param_1 + uVar5 * 0x2137b0;
  }
  if (pcVar6 == (char *)0x0) {
LAB_001e37e4:
    if (-1 < DebugLevel) {
      printk("%s: Wdev is NULL!!!\n","WscBuildProbeRespIE");
    }
    os_free_mem(local_34);
    return;
  }
  if (2 < DebugLevel) {
    printk("-----> %s:: apidx = %x\n","WscBuildProbeRespIE",(uint)param_7);
  }
  local_30 = local_34;
  local_2c[0] = 0;
  iVar3 = AppendWSCTLV(0x104a,local_34,pcVar6 + 0x1354,0);
  local_30 = (void *)((int)local_30 + iVar3);
  local_2c[0] = local_2c[0] + iVar3;
  iVar3 = AppendWSCTLV(0x1044,local_30,&local_3a,0);
  local_30 = (void *)((int)local_30 + iVar3);
  local_2c[0] = local_2c[0] + iVar3;
  if (param_10 == '\0') {
    if (pcVar6[0x3ebd] != '\0') {
      iVar3 = AppendWSCTLV(0x1057,local_30,pcVar6 + 0x3ebd,0);
      local_30 = (void *)((int)local_30 + iVar3);
      local_2c[0] = local_2c[0] + iVar3;
    }
    if (local_3b != '\0') {
      iVar3 = AppendWSCTLV(0x1041,local_30,&local_3b,0);
      local_30 = (void *)((int)local_30 + iVar3);
      local_2c[0] = local_2c[0] + iVar3;
LAB_001e372c:
      local_36 = param_5 << 8 | param_5 >> 8;
      iVar3 = AppendWSCTLV(0x1012,local_30,&local_36,0);
      local_30 = (void *)((int)local_30 + iVar3);
      local_2c[0] = local_2c[0] + iVar3;
      local_36 = param_6 << 8 | param_6 >> 8;
      iVar3 = AppendWSCTLV(0x1053,local_30,&local_36,0);
      local_30 = (void *)((int)local_30 + iVar3);
      local_2c[0] = local_2c[0] + iVar3;
    }
  }
  else if (local_3b != '\0') {
    iVar3 = AppendWSCTLV(0x1041,local_30,&local_3b,0);
    local_30 = (void *)((int)local_30 + iVar3);
    local_2c[0] = local_2c[0] + iVar3;
    goto LAB_001e372c;
  }
  local_48 = &local_36;
  iVar3 = AppendWSCTLV(0x103b,local_30,local_39,0);
  local_30 = (void *)((int)local_30 + iVar3);
  local_2c[0] = local_2c[0] + iVar3;
  iVar3 = AppendWSCTLV(0x1047,local_30,pcVar6 + 0x3d08,0);
  local_30 = (void *)((int)local_30 + iVar3);
  local_2c[0] = local_2c[0] + iVar3;
  __memzero(local_30,0x44);
  sVar4 = strlen(pcVar6 + 0x13af);
  iVar3 = AppendWSCTLV(0x1021,local_30,pcVar6 + 0x13af,sVar4 & 0xffff);
  local_30 = (void *)((int)local_30 + iVar3);
  local_2c[0] = local_2c[0] + iVar3;
  __memzero(local_30,0x24);
  sVar4 = strlen(pcVar6 + 0x13ef);
  iVar3 = AppendWSCTLV(0x1023,local_30,pcVar6 + 0x13ef,sVar4 & 0xffff);
  local_30 = (void *)((int)local_30 + iVar3);
  local_2c[0] = local_2c[0] + iVar3;
  __memzero(local_30,0x24);
  sVar4 = strlen(pcVar6 + 0x140f);
  iVar3 = AppendWSCTLV(0x1024,local_30,pcVar6 + 0x140f,sVar4 & 0xffff);
  local_30 = (void *)((int)local_30 + iVar3);
  local_2c[0] = local_2c[0] + iVar3;
  __memzero(local_30,0x24);
  sVar4 = strlen(pcVar6 + 0x142f);
  iVar3 = AppendWSCTLV(0x1042,local_30,pcVar6 + 0x142f,sVar4 & 0xffff);
  local_30 = (void *)((int)local_30 + iVar3);
  local_2c[0] = local_2c[0] + iVar3;
  iVar3 = AppendWSCTLV(0x1054,local_30,pcVar6 + 0x138c,0);
  local_30 = (void *)((int)local_30 + iVar3);
  local_2c[0] = local_2c[0] + iVar3;
  __memzero(local_30,0x24);
  sVar4 = strlen(pcVar6 + 0x136c);
  iVar3 = AppendWSCTLV(0x1011,local_30,pcVar6 + 0x136c,sVar4 & 0xffff);
  bVar7 = pcVar6[0x3e15] == '\0';
  uVar5 = extraout_r12;
  if (bVar7) {
    uVar5 = (uint)(byte)pcVar6[0x12ee];
  }
  local_30 = (void *)((int)local_30 + iVar3);
  local_2c[0] = local_2c[0] + iVar3;
  if (!bVar7) {
    uVar5 = (uint)*(ushort *)(pcVar6 + 0x12ee);
  }
  if (!bVar7) {
    uVar5 = uVar5 & 0xf97f;
  }
  if (pcVar6[0x1354] == '\x10') {
    if (*(int *)(pcVar6 + 0x12e8) == 1) {
      uVar5 = uVar5 | 4;
    }
    else if (*(int *)(pcVar6 + 0x12e8) == 2) {
      uVar5 = uVar5 | 0x8c;
    }
  }
  local_36 = (ushort)((uVar5 & 0xff) << 8) | (ushort)(uVar5 >> 8) & 0xff;
  iVar3 = AppendWSCTLV(0x1008,local_30,local_48,0);
  local_30 = (void *)((int)local_30 + iVar3);
  local_2c[0] = local_2c[0] + iVar3;
  if (param_10 == '\0') {
    if ((*(ushort *)(pcVar6 + 0x18) & 0xb1) != 0) {
      local_36 = 2;
      goto LAB_001e35a4;
    }
  }
  else {
    if (param_10 != '\x02') goto LAB_001e35a4;
    if (0xe < (byte)pcVar6[0x1a]) {
      local_36 = 2;
      goto LAB_001e35a4;
    }
  }
  local_36 = 1;
LAB_001e35a4:
  iVar3 = AppendWSCTLV(0x103c,local_30,local_48,0);
  local_30 = (void *)((int)local_30 + iVar3);
  local_2c[0] = iVar3 + local_2c[0];
  if (((pcVar6[0x3e15] != '\0') &&
      (WscGenV2Msg(pcVar6 + 0x12e4,local_3b,param_8,param_9,&local_30,local_2c),
      *(int *)(pcVar6 + 0x3e0c) != 0)) && (*(short *)(pcVar6 + 0x3e0a) != 0)) {
    iVar3 = AppendWSCTLV(*(undefined2 *)(pcVar6 + 0x3e08),local_30);
    local_30 = (void *)((int)local_30 + iVar3);
    local_2c[0] = iVar3 + local_2c[0];
  }
  if ((0xfb < (int)local_2c[0]) && (2 < DebugLevel)) {
    printk("Len is overflow!\n");
  }
  pvVar2 = local_34;
  pcVar6[0x10e5] = (char)local_2c[0] + '\x04';
  pcVar6[0x10e4] = -0x23;
  pcVar6[0x10e7] = 'P';
  pcVar6[0x10e6] = '\0';
  pcVar6[0x10e8] = -0xe;
  pcVar6[0x10e9] = '\x04';
  sVar1 = (short)local_2c[0];
  memcpy(pcVar6 + 0x10ea,local_34,local_2c[0]);
  *(short *)(pcVar6 + 0x10e2) = sVar1 + 6;
  if (pvVar2 != (void *)0x0) {
    os_free_mem(pvVar2);
  }
  if (2 < DebugLevel) {
    printk("<----- %s\n","WscBuildProbeRespIE");
  }
  return;
}

