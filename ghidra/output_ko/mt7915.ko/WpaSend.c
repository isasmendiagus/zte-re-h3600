// module: mt7915.ko
// function: WpaSend @ 0x1938c
// size: 1164 bytes
//

void WpaSend(int param_1,uint *param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  size_t __n;
  char cVar5;
  undefined4 local_34;
  undefined2 local_30;
  uint local_2e;
  uint local_2a;
  uint local_26;
  undefined2 local_22;
  
  local_34 = *param_2;
  local_30 = (undefined2)param_2[1];
  local_2a = param_2[1];
  local_26 = param_2[2];
  local_22 = (undefined2)param_2[3];
  local_2e = local_34;
  iVar2 = MacTableLookup(param_1,&local_34);
  if (iVar2 == 0) {
    if (DebugLevel < 4) {
      return;
    }
    printk("WpaSend - No such MAC - %02x:%02x:%02x:%02x:%02x:%02x\n",local_34 & 0xff,local_34._1_1_,
           local_34._2_1_,local_34 >> 0x18,(undefined1)local_30,local_30._1_1_);
    return;
  }
  uVar1 = *(ushort *)(iVar2 + 0xe0);
  if (*(char *)(iVar2 + 0x1466) == '\0') {
    if (-1 < DebugLevel) {
      printk("##[%s] calling OS_WAIT\n","WpaSend");
    }
    uVar3 = RTMPMsecsToJiffies(500);
    iVar4 = wait_for_completion_timeout(iVar2 + 0x1468,uVar3);
    if (iVar4 == 0) {
      if (DebugLevel < 0) goto LAB_0001943c;
      printk("#[%s]ERR:Wtbl entry not created 500msec\n","WpaSend");
    }
    if (2 < DebugLevel) {
      printk("###[%s] wait is over\n","WpaSend");
    }
  }
LAB_0001943c:
  if ((((*(uint *)(iVar2 + 0x17c) & 0x12cf8) != 0) && (*(char *)((int)param_2 + 0xf) != '\x03')) ||
     ("Airtime control --> %s(%d)\n"[(uint)*(byte *)(iVar2 + 0xe4) * 0x5834 + param_1 + 0x18] ==
      '\x01')) {
    RTMPToWirelessSta(param_1,iVar2,&local_2e,0xe,(int)param_2 + 0xe,param_3 + -0xe,
                      *(char *)(param_1 + (uint)uVar1 * 0x620 + 0x2f762) != '\x01');
  }
  if (DebugLevel < 3) {
    iVar4 = memcmp(param_2 + 3,&EAPOL,2);
    if (iVar4 != 0) {
LAB_00019568:
      __MlmeDeAuthAction(param_1,iVar2,2,0,"WpaSend",0x2ec);
      return;
    }
    cVar5 = *(char *)((int)param_2 + 0x12);
    if (cVar5 == '\x03') {
LAB_00019604:
      if (((*(uint *)(iVar2 + 0x17c) & 0x12cf8) != 0) && (*(char *)((int)param_2 + 0xf) != '\x03'))
      {
        if (2 < DebugLevel) {
          printk("Send EAP_CODE_SUCCESS\n\n");
        }
        if (*(int *)(iVar2 + 0xfc) != 2) {
          return;
        }
        *(undefined1 *)(iVar2 + 0x554) = 0;
        *(undefined1 *)(iVar2 + 0x514) = 6;
        os_move_mem((void *)(iVar2 + 0x4a0),
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + (uint)*(byte *)(iVar2 + 0xe4) * 0x5834 + param_1 + 0x101,6);
        os_move_mem((void *)(iVar2 + 0x4a6),(void *)(iVar2 + 0xec),6);
        if (*(char *)(iVar2 + 0x400) == '\x02') {
          __n = 0x30;
        }
        else {
          __n = 0x20;
        }
        os_move_mem((void *)(iVar2 + 0x30a),
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + (uint)*(byte *)(iVar2 + 0xe4) * 0x5834 + param_1 + 0x29a,__n);
        WPABuildPairMsg1(param_1,iVar2 + 0x17c,iVar2);
        return;
      }
      *(undefined4 *)(iVar2 + 0xadc) = 0;
      *(undefined1 *)(iVar2 + 0x514) = 10;
      if ((*(uint *)(iVar2 + 0x2c4) & 1) != 0) {
        "%s: group %d, band %u.\n"[(uint)*(byte *)(iVar2 + 0xe4) * 0x5834 + param_1 + 0x10] = '\x01'
        ;
        *(undefined1 *)(param_1 + (uint)uVar1 * 0x620 + 0x2f762) = 1;
      }
      if (*(int *)(
                  "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                  + (uint)*(byte *)(iVar2 + 0xe4) * 0x5834 + param_1 + 0x2b) != 0) {
        WscInformFromWPA(iVar2);
      }
      if (DebugLevel < 3) {
        return;
      }
      printk("IEEE8021X-WEP : Send EAP_CODE_SUCCESS\n\n");
      return;
    }
    if (cVar5 == '\x04') {
LAB_000197c0:
      __MlmeDeAuthAction(param_1,iVar2,0x17,0,"WpaSend",0x2e4);
      return;
    }
  }
  else {
    printk("%s(%d), pEapHdr->code=%d, pEntry->SecConfig.Handshake.WpaState=%d\n","WpaSend",0x2b0,
           *(undefined1 *)((int)param_2 + 0x12),*(undefined1 *)(iVar2 + 0x514));
    iVar4 = memcmp(param_2 + 3,&EAPOL,2);
    if (iVar4 != 0) {
      if (2 < DebugLevel) {
        printk("Send Deauth, Reason : REASON_NO_LONGER_VALID\n");
      }
      goto LAB_00019568;
    }
    cVar5 = *(char *)((int)param_2 + 0x12);
    if (cVar5 == '\x03') goto LAB_00019604;
    if (cVar5 == '\x04') {
      if (2 < DebugLevel) {
        printk("Send Deauth, Reason : REASON_8021X_AUTH_FAIL\n");
      }
      goto LAB_000197c0;
    }
  }
  iVar4 = DebugLevel;
  if (((cVar5 == '\x01') && (9 < *(byte *)(iVar2 + 0x514))) &&
     ((*(char *)((int)param_2 + 0xf) == '\0' && (*(undefined1 *)(iVar2 + 0x514) = 4, 2 < iVar4)))) {
    printk("Start to re-authentication by 802.1x daemon\n");
  }
  return;
}

