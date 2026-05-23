// module: mt7915.ko
// function: RTMPIoctlWscProfile @ 0x3c260
// size: 1472 bytes
//

void RTMPIoctlWscProfile(int *param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  size_t sVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  char *local_a8;
  char *local_a4;
  char *local_a0;
  undefined *local_9c;
  char *local_98;
  ushort local_91;
  undefined1 auStack_8f [33];
  undefined2 local_6e;
  ushort local_6c;
  byte local_6a;
  char acStack_69 [69];
  
  uVar7 = (uint)*(byte *)(*param_1 + 0x3c);
  __memzero(&local_91,0x69);
  iVar6 = 0;
  iVar8 = uVar7 * 0x5834;
  local_91 = (ushort)*(byte *)(param_1 + uVar7 * 0x160d + 0xae14d);
  __memzero(auStack_8f,0x21);
  uVar9 = (uint)*(byte *)((int)param_1 + iVar8 + 0x2bb2d1);
  memcpy(auStack_8f,
         (char *)((int)param_1 +
                 (int)(
                      "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                      + iVar8 + 0x34)),uVar9);
  iVar2 = param_1[uVar7 * 0x160d + 0xadc9d];
  auStack_8f[uVar9] = 0;
  local_6e = WscGetAuthType(iVar2);
  local_6c = WscGetEncryType(param_1[uVar7 * 0x160d + 0xadcef]);
  __memzero(acStack_69,0x41);
  if (local_6c == 2) {
    local_6a = (char)param_1[uVar7 * 0x160d + 0xadcf0] + 1;
    uVar9 = (uint)local_6a;
    if (*(char *)((int)param_1 +
                 (int)(
                      "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      + uVar9 * 0x51 + iVar8 + 0x160)) == '\0') {
      uVar5 = 0;
    }
    else {
      do {
        iVar2 = iVar6 + uVar9 * 0x51 + iVar8;
        iVar6 = iVar6 + 1;
        local_a8 = (char *)(uint)*(byte *)((int)param_1 +
                                          (int)(
                                               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                               + iVar2 + 0x110));
        snprintf(acStack_69,0x41,"%s%02x",acStack_69);
        uVar9 = (uint)local_6a;
        uVar5 = (uint)*(byte *)((int)param_1 +
                               (int)(
                                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                    + uVar9 * 0x51 + iVar8 + 0x160));
      } while (iVar6 < (int)uVar5);
    }
    acStack_69[uVar5 * 2] = '\0';
  }
  else if (local_6c < 4) {
    local_6a = 1;
  }
  else {
    sVar3 = param_1[uVar7 * 0x160d + 0xaebc3];
    local_6a = 2;
    memcpy(acStack_69,(void *)((int)param_1 + iVar8 + 0x2baec9),sVar3);
    acStack_69[sVar3] = '\0';
  }
  uVar9 = *(uint *)(param_2 + 0x10);
  *(undefined2 *)(param_2 + 0x14) = 0x69;
  uVar5 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
  if (uVar9 < 0xffffff97 && uVar9 + 0x69 <= uVar5) {
    uVar5 = 0;
  }
  if (((uVar5 != 0) || (iVar2 = __copy_to_user(uVar9,&local_91), iVar2 != 0)) && (2 < DebugLevel)) {
    printk("%s: copy_to_user() fail\n","RTMPIoctlWscProfile");
  }
  os_alloc_mem(param_1,&local_98,0x800);
  if (local_98 != (char *)0x0) {
    __memzero(local_98,0x800);
    pcVar1 = local_98;
    local_98[0] = '\n';
    local_98[1] = '\0';
    if (local_6c == 1) {
      sVar3 = strlen(local_98);
      local_a8 = "AuthMode";
      local_a4 = "EncrypType";
      sprintf(pcVar1 + sVar3,"%-12s%-33s%-12s%-12s\n","Configured",&_LC742);
    }
    else if (local_6c == 2) {
      sVar3 = strlen(local_98);
      local_a8 = "AuthMode";
      local_a4 = "EncrypType";
      local_a0 = "DefaultKeyID";
      local_9c = &_LC747;
      sprintf(pcVar1 + sVar3,"%-12s%-33s%-12s%-12s%-13s%-26s\n","Configured",&_LC742);
    }
    else {
      sVar3 = strlen(local_98);
      local_a8 = "AuthMode";
      local_a4 = "EncrypType";
      local_a0 = "Key";
      sprintf(pcVar1 + sVar3,"%-12s%-33s%-12s%-12s%-64s\n","Configured",&_LC742);
    }
    pcVar1 = local_98;
    if (local_91 == 1) {
      sVar3 = strlen(local_98);
      sprintf(pcVar1 + sVar3,"%-12s",&_LC750);
    }
    else {
      sVar3 = strlen(local_98);
      sprintf(pcVar1 + sVar3,"%-12s",&_LC751);
    }
    pcVar1 = local_98;
    sVar3 = strlen(local_98);
    sprintf(pcVar1 + sVar3,"%-33s",auStack_8f);
    pcVar1 = local_98;
    if ((param_1[uVar7 * 0x160d + 0xadc9d] & 0x90U) == 0) {
      sVar3 = strlen(local_98);
      uVar4 = WscGetAuthTypeStr(local_6e);
      sprintf(pcVar1 + sVar3,"%-12s",uVar4);
    }
    else {
      sVar3 = strlen(local_98);
      sprintf(pcVar1 + sVar3,"%-12s","WPAPSKWPA2PSK");
    }
    pcVar1 = local_98;
    if ((param_1[uVar7 * 0x160d + 0xadcef] & 0x30U) == 0) {
      sVar3 = strlen(local_98);
      uVar4 = WscGetEncryTypeStr(local_6c);
      sprintf(pcVar1 + sVar3,"%-12s",uVar4);
    }
    else {
      sVar3 = strlen(local_98);
      sprintf(pcVar1 + sVar3,"%-12s","TKIPAES");
    }
    pcVar1 = local_98;
    if (local_6c == 1) {
      sVar3 = strlen(local_98);
      sprintf(pcVar1 + sVar3,"%s\n",&_LC265);
    }
    else if (local_6c == 2) {
      sVar3 = strlen(local_98);
      sprintf(pcVar1 + sVar3,"%-13d",(uint)local_6a);
      pcVar1 = local_98;
      sVar3 = strlen(local_98);
      sprintf(pcVar1 + sVar3,"%-26s\n",acStack_69);
    }
    else if (3 < local_6c) {
      sVar3 = strlen(local_98);
      sprintf(pcVar1 + sVar3,"%-64s\n",acStack_69);
    }
    if (2 < DebugLevel) {
      printk(&_LC758,local_98);
    }
    os_free_mem(local_98);
  }
  return;
}

