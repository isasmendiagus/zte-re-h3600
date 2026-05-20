// module: mt7915.ko
// function: SendBTMReqParam @ 0x229420
// size: 1068 bytes
//

void SendBTMReqParam(int param_1,byte *param_2)

{
  byte bVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  byte *pbVar8;
  char *pcVar9;
  int *piVar10;
  undefined1 uStack_4d;
  void *local_4c;
  int local_48;
  int local_44;
  undefined1 auStack_40 [28];
  
  bVar1 = *param_2;
  uVar2 = *(undefined2 *)(param_2 + 10);
  local_4c = (void *)0x0;
  local_48 = 0;
  local_44 = 0;
  pcVar9 = "RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + param_1 + (uint)bVar1 * 0x5834 + 0x20;
  down_interruptible(pcVar9);
  iVar5 = param_1 + (uint)bVar1 * 0x5834;
  piVar7 = *(int **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar5 + 0x28);
  if (piVar7 != (int *)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar5 + 0x28)) {
    do {
      iVar4 = memcmp((char *)((int)piVar7 + 0xd),param_2 + 1,6);
      if (iVar4 == 0) {
        pbVar8 = param_2 + 0xc;
        up(pcVar9);
        iVar5 = check_btm_custom_params(param_1,pbVar8,uVar2);
        if (iVar5 == 0) {
          iVar5 = os_alloc_mem(param_1,&local_4c,0x900);
          if (iVar5 == 0) {
            ActHeaderInit(param_1,auStack_40,pbVar8,
                          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          + (uint)*param_2 * 0x5834 + param_1 + 0x101,
                          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          + (uint)*param_2 * 0x5834 + param_1 + 0x101);
            memmove(local_4c,auStack_40,0x18);
            local_48 = 0x18;
            InsertActField(param_1,(int)local_4c + 0x18,&local_48,10,7);
            piVar10 = piVar7 + 6;
            InsertDialogToken(param_1,(int)local_4c + local_48,&local_48,param_2[0x12]);
            compose_btm_req_ie(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                       + (uint)*param_2 * 0x5834 + param_1 + 0xe0,
                               (int)local_4c + local_48,&local_44,pbVar8,uVar2);
            piVar7[2] = 5;
            local_48 = local_44 + local_48;
            MiniportMMRequest(param_1,0x81,local_4c,local_48);
            RTMPCancelTimer(piVar7 + 0x13,&uStack_4d);
            RTMPReleaseTimer(piVar7 + 0x13,&uStack_4d);
            RTMPCancelTimer(piVar10,&uStack_4d);
            RTMPReleaseTimer(piVar10,&uStack_4d);
            RTMPInitTimer(param_1,piVar10,rtmp_timer_WaitPeerBTMRspTimeout,piVar7,0);
            iVar5 = piVar7[0x2d];
            if (iVar5 == 0) {
              iVar5 = 15000;
            }
            RTMPSetTimer(piVar10,iVar5);
            iVar4 = MacTableLookup(param_1,param_2 + 1);
            iVar5 = DebugLevel;
            if ((iVar4 != 0) && ((param_2[0x13] & 4) != 0)) {
              uVar3 = (int)((uint)*(ushort *)(&DAT_00794c50 + param_1) *
                           (uint)*(ushort *)(param_2 + 0x14)) / 1000;
              uVar6 = uVar3 & 0xffff;
              *(short *)(iVar4 + 0x13b2) = (short)uVar3;
              if (0 < iVar5) {
                printk("%s() bss discount sec=%d\n","SendBTMReqParam");
                uVar6 = (uint)*(ushort *)(iVar4 + 0x13b2);
              }
              if (uVar6 == 0) {
                *(undefined2 *)(iVar4 + 0x13b2) = 1;
              }
            }
            os_free_mem(local_4c);
            return;
          }
          if (-1 < DebugLevel) {
            printk("%s() allocate memory for btm req frame failed \n","SendBTMReqParam");
            goto LAB_002297d8;
          }
        }
        else if (-1 < DebugLevel) {
          printk("%s() check customer params failed\n","SendBTMReqParam");
LAB_002297d8:
          if ((char)piVar7[0x1a] != '\0') {
            if (DebugLevel < 0) {
              return;
            }
            printk("%s()  BTMReqTimer is valid, wait timeout to delete BTMPeerEntry\n",
                   "SendBTMReqParam");
            return;
          }
          if (-1 < DebugLevel) {
            printk("%s()  BTMReqTimer is not valid, delete BTMPeerEntry now\n","SendBTMReqParam");
          }
          goto LAB_002294fc;
        }
        if ((char)piVar7[0x1a] != '\0') {
          return;
        }
LAB_002294fc:
        RTMPCancelTimer(piVar7 + 6,&uStack_4d);
        RTMPReleaseTimer(piVar7 + 6,&uStack_4d);
        RTMPCancelTimer(piVar7 + 0x13,&uStack_4d);
        RTMPReleaseTimer(piVar7 + 0x13,&uStack_4d);
        down_interruptible(pcVar9);
        if (*piVar7 != 0) {
          *(int *)(*piVar7 + 4) = piVar7[1];
        }
        if ((int *)piVar7[1] != (int *)0x0) {
          *(int *)piVar7[1] = *piVar7;
        }
        *piVar7 = 0;
        piVar7[1] = 0;
        up(pcVar9);
        os_free_mem(piVar7);
        return;
      }
      piVar7 = (int *)*piVar7;
    } while (piVar7 != (int *)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar5 + 0x28));
  }
  up(pcVar9);
  if (-1 < DebugLevel) {
    printk("%s() BTMPeerEntry is already deleted\n","SendBTMReqParam");
  }
  return;
}

