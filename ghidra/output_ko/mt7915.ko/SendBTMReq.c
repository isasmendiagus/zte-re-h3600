// module: mt7915.ko
// function: SendBTMReq @ 0x227264
// size: 552 bytes
//

void SendBTMReq(int param_1,byte *param_2)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  undefined1 uStack_25;
  int local_24;
  
  bVar1 = *param_2;
  uVar2 = *(ushort *)(param_2 + 10);
  down_interruptible("RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" +
                     param_1 + (uint)bVar1 * 0x5834 + 0x20);
  iVar5 = param_1 + (uint)bVar1 * 0x5834;
  pcVar6 = *(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar5 + 0x28);
  if (pcVar6 != "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar5 + 0x28) {
    do {
      iVar4 = memcmp(pcVar6 + 0xd,param_2 + 1,6);
      if (iVar4 == 0) break;
      pcVar6 = *(char **)pcVar6;
    } while (pcVar6 != "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar5 + 0x28);
  }
  up("RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + param_1 + (uint)bVar1 * 0x5834 + 0x20);
  os_alloc_mem(0,&local_24,uVar2 + 0x1c);
  if (local_24 == 0) {
    if (-1 < DebugLevel) {
      printk("%s Not available memory\n","SendBTMReq");
    }
  }
  else {
    __memzero(local_24,uVar2 + 0x1c);
    iVar5 = local_24;
    ActHeaderInit(param_1,local_24,param_2 + 1,
                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + (uint)*param_2 * 0x5834 + param_1 + 0x101,
                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + (uint)*param_2 * 0x5834 + param_1 + 0x101);
    *(undefined1 *)(iVar5 + 0x18) = 10;
    *(undefined1 *)(iVar5 + 0x19) = 7;
    *(byte *)(iVar5 + 0x1a) = param_2[9];
    memmove((void *)(iVar5 + 0x1b),param_2 + 0xc,(uint)*(ushort *)(param_2 + 10));
    uVar2 = *(ushort *)(param_2 + 10);
    BTMSetPeerCurrentState(param_1,param_2,5);
    MiniportMMRequest(param_1,0x81,local_24,uVar2 + 0x1b);
    RTMPCancelTimer(pcVar6 + 0x4c,&uStack_25);
    RTMPReleaseTimer(pcVar6 + 0x4c,&uStack_25);
    RTMPSetTimer(pcVar6 + 0x18,15000);
    iVar5 = MacTableLookup(param_1,param_2 + 1);
    if ((iVar5 != 0) && ((param_2[0xc] & 0x1c) != 0)) {
      uVar3 = (int)((uint)*(ushort *)(&DAT_00794c50 + param_1) * (uint)*(ushort *)(param_2 + 0xd)) /
              1000;
      *(short *)(iVar5 + 0x13b2) = (short)uVar3;
      printk("bss discount sec=%d\n",uVar3 & 0xffff);
      if (*(short *)(iVar5 + 0x13b2) == 0) {
        *(undefined2 *)(iVar5 + 0x13b2) = 1;
      }
    }
    os_free_mem(local_24);
  }
  return;
}

