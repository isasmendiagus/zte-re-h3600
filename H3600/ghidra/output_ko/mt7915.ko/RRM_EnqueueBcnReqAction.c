// module: mt7915.ko
// function: RRM_EnqueueBcnReqAction @ 0x21d7c8
// size: 636 bytes
//

undefined4 RRM_EnqueueBcnReqAction(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  void *local_44;
  int local_40;
  int local_3c;
  undefined1 auStack_38 [28];
  
  bVar2 = *(byte *)(param_3 + 0x1c);
  local_44 = (void *)0x0;
  if (bVar2 < 3) {
    pcVar5 = (char *)(param_3 + 4);
    do {
      pcVar5 = pcVar5 + 1;
      if (*pcVar5 != -1) {
        iVar3 = MacTableLookup(param_1,param_3 + 5);
        if ((iVar3 == 0) || (*(int *)(iVar3 + 0xfc) != 2)) {
          if (DebugLevel < 1) {
            return 1;
          }
          printk("Peer Not connected\n");
          return 1;
        }
        if (((*(byte *)(iVar3 + 0xe4) != param_2) ||
            (*(char *)(*(int *)(iVar3 + 8) + 0xb21) != '\x01')) ||
           (uVar1 = 1 << (uint)bVar2,
           ((*(uint *)(iVar3 + 0x11ec) >> 4 | *(uint *)(iVar3 + 0x11f0) << 0x1c) & uVar1) == 0 &&
           (*(uint *)(iVar3 + 0x11f0) >> 4 & (int)uVar1 >> 0x1f) == 0)) {
          if (DebugLevel < 1) {
            return 1;
          }
          printk("Peer does not support this request\n");
          return 1;
        }
        break;
      }
    } while (pcVar5 != (char *)(param_3 + 10));
    iVar3 = os_alloc_mem(param_1,&local_44,0x900);
    if ((iVar3 == 0) && (local_44 != (void *)0x0)) {
      iVar3 = param_1 + param_2 * 0x5834;
      MgtMacHeaderInit(param_1,auStack_38,0xd,0,param_3 + 5,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar3 + 0xfb,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar3 + 0x101);
      memmove(local_44,auStack_38,0x18);
      local_40 = 0x18;
      InsertActField(param_1,(int)local_44 + 0x18,&local_40,5,0);
      InsertDialogToken(param_1,(int)local_44 + local_40,&local_40,*(undefined1 *)(param_3 + 4));
      MakeOutgoingFrame((int)local_44 + local_40,&local_3c,*(undefined4 *)(param_3 + 0xb),
                        param_3 + 0xf,0xffffffff);
      local_40 = local_3c + local_40;
      uVar4 = MiniportMMRequest(param_1,0x81,local_44);
      if (local_44 != (void *)0x0) {
        os_free_mem(local_44);
        return uVar4;
      }
      return uVar4;
    }
    if (2 < DebugLevel) {
      printk("%s() allocate memory failed\n","RRM_EnqueueBcnReqAction");
    }
  }
  else if (0 < DebugLevel) {
    printk("Incorrect mode\n");
    return 1;
  }
  return 1;
}

