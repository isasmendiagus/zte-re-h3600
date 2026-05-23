// module: mt7915.ko
// function: SendWNMNotifyReq @ 0x2298e8
// size: 796 bytes
//

void SendWNMNotifyReq(int param_1,byte *param_2)

{
  byte bVar1;
  ushort uVar2;
  short sVar3;
  undefined2 uVar4;
  int iVar5;
  char cVar6;
  int iVar7;
  char *pcVar8;
  int local_24;
  
  iVar7 = (uint)*param_2 * 0x5834;
  uVar2 = *(ushort *)(param_2 + 10);
  down_interruptible(&_LC170 + param_1 + iVar7);
  pcVar8 = *(char **)("RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + iVar7 + 4);
  if (pcVar8 != "RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + iVar7 + 4) {
    do {
      iVar5 = memcmp(pcVar8 + 0xd,param_2 + 1,6);
      if (iVar5 == 0) break;
      pcVar8 = *(char **)pcVar8;
    } while (pcVar8 != "RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + iVar7 + 4);
  }
  up(&_LC170 + param_1 + iVar7);
  os_alloc_mem(0,&local_24,uVar2 + 0x23);
  if (local_24 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s Not available memory\n","SendWNMNotifyReq");
    return;
  }
  __memzero(local_24,uVar2 + 0x1c);
  iVar7 = local_24;
  ActHeaderInit(param_1,local_24,param_2 + 1,
                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                + (uint)*param_2 * 0x5834 + param_1 + 0x101,
                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                + (uint)*param_2 * 0x5834 + param_1 + 0x101);
  *(undefined1 *)(iVar7 + 0x18) = 10;
  *(undefined1 *)(iVar7 + 0x19) = 0x1a;
  bVar1 = param_2[9];
  *(undefined1 *)(iVar7 + 0x1b) = 1;
  *(byte *)(iVar7 + 0x1a) = bVar1;
  sVar3 = *(short *)(param_2 + 7);
  if (sVar3 == 0) {
    printk("remediation\n");
    *(undefined1 *)(iVar7 + 0x1c) = 0xdd;
    uVar4 = *(undefined2 *)(param_2 + 10);
    *(undefined1 *)(iVar7 + 0x1e) = 0x50;
    *(undefined1 *)(iVar7 + 0x1f) = 0x6f;
    *(undefined1 *)(iVar7 + 0x21) = 0;
    *(char *)(iVar7 + 0x1d) = (char)uVar4 + '\x05';
    *(undefined1 *)(iVar7 + 0x20) = 0x9a;
    cVar6 = (char)*(undefined2 *)(param_2 + 10);
  }
  else {
    if (sVar3 != 2) {
      if (sVar3 != 1) {
        printk("no match event type:%d\n",sVar3);
        os_free_mem(local_24);
        return;
      }
      printk("deauth imminent: %d\n",*(undefined2 *)(param_2 + 10));
      *(undefined1 *)(iVar7 + 0x1c) = 0xdd;
      uVar4 = *(undefined2 *)(param_2 + 10);
      *(undefined1 *)(iVar7 + 0x21) = 1;
      *(undefined1 *)(iVar7 + 0x1e) = 0x50;
      *(char *)(iVar7 + 0x1d) = (char)uVar4 + '\x05';
      *(undefined1 *)(iVar7 + 0x1f) = 0x6f;
      *(undefined1 *)(iVar7 + 0x20) = 0x9a;
      memmove((void *)(iVar7 + 0x22),param_2 + 0xc,3);
      sVar3 = *(short *)(param_2 + 10);
      *(char *)(iVar7 + 0x25) = (char)(sVar3 - 3U);
      if ((sVar3 - 3U & 0xff) == 0) {
        iVar7 = 0x26;
      }
      else {
        memmove((void *)(iVar7 + 0x26),param_2 + 0xf,*(ushort *)(param_2 + 10) - 3);
        iVar7 = *(ushort *)(param_2 + 10) + 0x23;
      }
      iVar5 = MacTableLookup(param_1,param_2 + 1);
      if (iVar5 != 0) {
        *(undefined2 *)(iVar5 + 0x13b2) = 0x28;
      }
      goto LAB_00229abc;
    }
    printk("remediation with method\n");
    *(undefined1 *)(iVar7 + 0x1c) = 0xdd;
    uVar4 = *(undefined2 *)(param_2 + 10);
    *(undefined1 *)(iVar7 + 0x1e) = 0x50;
    *(undefined1 *)(iVar7 + 0x1f) = 0x6f;
    *(char *)(iVar7 + 0x1d) = (char)uVar4 + '\x05';
    *(undefined1 *)(iVar7 + 0x20) = 0x9a;
    *(undefined1 *)(iVar7 + 0x21) = 0;
    cVar6 = (char)*(undefined2 *)(param_2 + 10) + -1;
  }
  *(char *)(iVar7 + 0x22) = cVar6;
  memmove((void *)(iVar7 + 0x23),param_2 + 0xc,(uint)*(ushort *)(param_2 + 10));
  iVar7 = *(ushort *)(param_2 + 10) + 0x23;
LAB_00229abc:
  if (local_24 == 0) {
    return;
  }
  WNMSetPeerCurrentState(param_1,param_2,1);
  MiniportMMRequest(param_1,0,local_24,iVar7);
  RTMPSetTimer(pcVar8 + 0x18,0x400);
  os_free_mem(local_24);
  return;
}

