// module: mt7915.ko
// function: SendBTMReqIE @ 0x2242ac
// size: 1092 bytes
//

void SendBTMReqIE(int param_1,byte *param_2)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  char *pcVar8;
  byte *__s2;
  int *piVar9;
  undefined1 uStack_49;
  void *local_48;
  int local_44;
  undefined1 auStack_40 [28];
  
  bVar1 = *param_2;
  uVar2 = *(ushort *)(param_2 + 10);
  local_48 = (void *)0x0;
  local_44 = 0;
  pcVar8 = "RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + param_1 + (uint)bVar1 * 0x5834 + 0x20;
  down_interruptible(pcVar8);
  iVar5 = param_1 + (uint)bVar1 * 0x5834;
  piVar7 = *(int **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar5 + 0x28);
  if (piVar7 != (int *)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar5 + 0x28)) {
    __s2 = param_2 + 1;
    do {
      iVar4 = memcmp((char *)((int)piVar7 + 0xd),__s2,6);
      if (iVar4 == 0) {
        up(pcVar8);
        iVar5 = MacTableLookup(param_1,__s2);
        if ((iVar5 == 0) ||
           (((*(uint *)(
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + (uint)*(byte *)(iVar5 + 0xe4) * 0x5834 + param_1 + 0x10c) & 1) == 0 &&
            (*(short *)(iVar5 + 0x514) != 0x10a)))) {
          if (-1 < DebugLevel) {
            printk("%s() STA(%02x:%02x:%02x:%02x:%02x:%02x) not associates with AP!\n",
                   "SendBTMReqIE",param_2[1],param_2[2],param_2[3],param_2[4],param_2[5],param_2[6])
            ;
            goto LAB_00224498;
          }
        }
        else {
          iVar4 = os_alloc_mem(param_1,&local_48,0x900);
          if (iVar4 == 0) {
            ActHeaderInit(param_1,auStack_40,__s2,
                          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          + (uint)*param_2 * 0x5834 + param_1 + 0x101,
                          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          + (uint)*param_2 * 0x5834 + param_1 + 0x101);
            memmove(local_48,auStack_40,0x18);
            piVar9 = piVar7 + 6;
            local_44 = 0x18;
            InsertActField(param_1,(int)local_48 + 0x18,&local_44,10,7);
            InsertDialogToken(param_1,(int)local_48 + local_44,&local_44,param_2[9]);
            memcpy((void *)((int)local_48 + local_44),param_2 + 0xc,(uint)uVar2);
            piVar7[2] = 5;
            local_44 = (uint)uVar2 + local_44;
            MiniportMMRequest(param_1,0x81,local_48,local_44);
            RTMPCancelTimer(piVar7 + 0x13,&uStack_49);
            RTMPReleaseTimer(piVar7 + 0x13,&uStack_49);
            RTMPCancelTimer(piVar9,&uStack_49);
            RTMPReleaseTimer(piVar9,&uStack_49);
            RTMPInitTimer(param_1,piVar9,rtmp_timer_WaitPeerBTMRspTimeout,piVar7,0);
            iVar4 = piVar7[0x2d];
            if (iVar4 == 0) {
              iVar4 = 15000;
            }
            RTMPSetTimer(piVar9,iVar4);
            iVar4 = DebugLevel;
            if ((param_2[0xc] & 4) != 0) {
              uVar3 = (int)((uint)*(ushort *)(&DAT_00794c50 + param_1) *
                           (uint)*(ushort *)(param_2 + 0xd)) / 1000;
              uVar6 = uVar3 & 0xffff;
              *(short *)(iVar5 + 0x13b2) = (short)uVar3;
              if (0 < iVar4) {
                printk("%s() bss discount sec=%d\n","SendBTMReqIE");
                uVar6 = (uint)*(ushort *)(iVar5 + 0x13b2);
              }
              if (uVar6 == 0) {
                *(undefined2 *)(iVar5 + 0x13b2) = 1;
              }
            }
            os_free_mem(local_48);
            return;
          }
          if (-1 < DebugLevel) {
            printk("%s() allocate memory for btm req frame failed \n","SendBTMReqIE");
LAB_00224498:
            if ((char)piVar7[0x1a] != '\0') {
              if (DebugLevel < 0) {
                return;
              }
              printk("%s()  BTMReqTimer is valid, wait timeout to delete BTMPeerEntry\n",
                     "SendBTMReqIE");
              return;
            }
            if (-1 < DebugLevel) {
              printk("%s()  BTMReqTimer is not valid, delete BTMPeerEntry now\n","SendBTMReqIE");
            }
            goto LAB_002243b4;
          }
        }
        if ((char)piVar7[0x1a] != '\0') {
          return;
        }
LAB_002243b4:
        RTMPCancelTimer(piVar7 + 6,&uStack_49);
        RTMPReleaseTimer(piVar7 + 6,&uStack_49);
        RTMPCancelTimer(piVar7 + 0x13,&uStack_49);
        RTMPReleaseTimer(piVar7 + 0x13,&uStack_49);
        down_interruptible(pcVar8);
        if (*piVar7 != 0) {
          *(int *)(*piVar7 + 4) = piVar7[1];
        }
        if ((int *)piVar7[1] != (int *)0x0) {
          *(int *)piVar7[1] = *piVar7;
        }
        *piVar7 = 0;
        piVar7[1] = 0;
        up(pcVar8);
        os_free_mem(piVar7);
        return;
      }
      piVar7 = (int *)*piVar7;
    } while (piVar7 != (int *)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar5 + 0x28));
  }
  up(pcVar8);
  if (-1 < DebugLevel) {
    printk("%s() BTMPeerEntry is already deleted\n","SendBTMReqIE");
  }
  return;
}

