// module: mt7915.ko
// function: MacTableReset @ 0x14a2e0
// size: 1396 bytes
//

void MacTableReset(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  void *__src;
  int iVar4;
  uint uVar5;
  void *pvVar6;
  void *__src_00;
  undefined1 uStack_57;
  undefined2 local_56;
  undefined4 local_54;
  undefined4 local_50;
  void *local_4c;
  void *local_48;
  void *local_44;
  undefined1 auStack_40 [28];
  
  local_54 = 0;
  local_50 = 0;
  if (2 < DebugLevel) {
    printk("MacTableReset\n");
  }
  __src = (void *)(param_1 + 0xa1d20);
  iVar4 = param_1 + 0xa1e0c;
  pvVar6 = __src;
  for (uVar5 = 0; iVar1 = HcGetMaxStaNum(param_1), (int)uVar5 < iVar1; uVar5 = uVar5 + 1) {
    if (((*(int *)(iVar4 + -0xec) == 0x20001) &&
        (*(undefined1 *)(iVar4 + 0x8f) = 0, *(char *)(param_1 + 0x286285) == '\x01')) &&
       (*(int *)(iVar4 + 0x10) == 2)) {
      iVar1 = os_alloc_mem(param_1,&local_54,0x900);
      if (iVar1 != 0) {
        if (DebugLevel < 3) {
          return;
        }
        printk(" MlmeAllocateMemory fail  ..\n",0x11,iVar1);
        return;
      }
      local_56 = 2;
      __ZTE_STA_Assoc_Process(param_1,0x11,0,0,2,0,pvVar6,"MacTableReset",0x84e);
      if (1 < DebugLevel) {
        printk("Send DeAuth (Reason=%d) to %02x:%02x:%02x:%02x:%02x:%02x\n",local_56,
               *(undefined1 *)((int)pvVar6 + 0xec),*(undefined1 *)(iVar4 + 1),
               *(undefined1 *)(iVar4 + 2),*(undefined1 *)(iVar4 + 3),*(undefined1 *)(iVar4 + 4),
               *(undefined1 *)(iVar4 + 5));
      }
      iVar1 = param_1 + (uint)*(byte *)(iVar4 + -8) * 0x5834;
      MgtMacHeaderInit(param_1,auStack_40,0xc,0,iVar4,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar1 + 0xfb,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar1 + 0x101);
      MakeOutgoingFrame(local_54,&local_50,0x18,auStack_40,2,&local_56,0xffffffff);
      MiniportMMRequest(param_1,0,local_54,local_50);
      os_free_mem(local_54);
      RtmpusecDelay(5000);
    }
    pvVar6 = (void *)((int)pvVar6 + 0x14c0);
    MacTableDeleteEntry(param_1,uVar5 & 0xffff,iVar4);
    iVar4 = iVar4 + 0x14c0;
  }
  if (*(char *)(param_1 + 0x286285) != '\x01') {
    return;
  }
  local_4c = (void *)0x0;
  local_48 = (void *)0x0;
  local_44 = (void *)0x0;
  os_alloc_mem(0,&local_4c,0x400);
  iVar4 = HcGetMaxStaNum(param_1);
  os_alloc_mem(0,&local_48,iVar4 * 0x14c0);
  os_alloc_mem(0,&local_44,0x6e400);
  if (((local_4c == (void *)0x0) || (local_48 == (void *)0x0)) || (local_44 == (void *)0x0)) {
    uVar3 = 0x871;
LAB_0014a7bc:
    printk(&_LC44,uVar3);
    dump_stack();
    if (local_4c != (void *)0x0) {
      os_free_mem();
    }
    if (local_48 != (void *)0x0) {
      os_free_mem();
    }
    if (local_44 != (void *)0x0) {
      os_free_mem();
    }
    return;
  }
  uVar5 = HcGetMaxStaNum(param_1);
  uVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar2 <= uVar5) {
    uVar3 = 0x882;
    goto LAB_0014a7bc;
  }
  __memzero(local_4c,0x400);
  pvVar6 = local_48;
  iVar4 = HcGetMaxStaNum(param_1);
  if (iVar4 * 0x14c0 != 0) {
    __memzero(pvVar6);
  }
  __memzero(local_44,0x6e400);
  if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0') {
    uVar5 = 0;
    do {
      iVar4 = param_1 + uVar5 * 0x5834;
      uVar5 = uVar5 + 1 & 0xff;
      RTMPCancelTimer("IF(ra0) Set_WscConfMode_Proc::(WscConfMode(0,1,2)=%d)\n" + iVar4 + 0x10,
                      &uStack_57);
      "IF(ra0) Set_WscConfMode_Proc::(WscConfMode(0,1,2)=%d)\n"[iVar4 + 0xc] = '\0';
      __memzero("%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n" +
                iVar4 + 0x31,6);
      "%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n"[iVar4 + 0x2e]
           = '\0';
      "pStaCfg->WpaPassPhrase"[iVar4 + 0xb] = '\0';
    } while (uVar5 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           [param_1 + 0xda]);
  }
  os_zero_mem(param_1 + 0xa7bea8,0x20);
  _raw_spin_lock_bh(param_1 + 0x285c50);
  if (DebugLevel < 3) {
    if (*(int *)(param_1 + 0x28592c) == 0) goto LAB_0014a64c;
LAB_0014a764:
    APCleanupPsQueue(param_1,param_1 + 0x285924);
  }
  else {
    printk("McastPsQueue.Number %d...\n",*(undefined4 *)(param_1 + 0x28592c));
    if (*(int *)(param_1 + 0x28592c) != 0) goto LAB_0014a764;
  }
  if (2 < DebugLevel) {
    printk("2McastPsQueue.Number %d...\n",*(undefined4 *)(param_1 + 0x28592c));
  }
LAB_0014a64c:
  __src_00 = (void *)(param_1 + 0xa1920);
  memcpy(local_4c,__src_00,0x400);
  pvVar6 = local_48;
  iVar4 = HcGetMaxStaNum(param_1);
  memcpy(pvVar6,__src,iVar4 * 0x14c0);
  memcpy(local_44,(void *)(param_1 + 0x2f6a0),0x6e400);
  __memzero(__src_00,0x1e4038);
  memcpy(__src_00,local_4c,0x400);
  pvVar6 = local_48;
  iVar4 = HcGetMaxStaNum(param_1);
  memcpy(__src,pvVar6,iVar4 * 0x14c0);
  memcpy((void *)(param_1 + 0x2f6a0),local_44,0x6e400);
  os_free_mem(local_4c);
  os_free_mem(local_48);
  os_free_mem(local_44);
  *(undefined4 *)(param_1 + 0x285928) = 0;
  *(undefined4 *)(param_1 + 0x285924) = 0;
  *(undefined4 *)(param_1 + 0x28592c) = 0;
  _raw_spin_unlock_bh(param_1 + 0x285c50);
  return;
}

