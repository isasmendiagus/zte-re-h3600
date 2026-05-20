// module: mt7915.ko
// function: WscEapApProxyAction @ 0x1e42c8
// size: 1688 bytes
//

void WscEapApProxyAction(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  undefined1 uStack_2d;
  int local_2c [2];
  
  bVar4 = false;
  local_2c[0] = 0;
  if (DebugLevel < 3) {
    iVar2 = *(int *)(param_2 + 0x904);
    if (iVar2 == 0x24) {
LAB_001e4388:
      iVar6 = *(int *)(param_2 + 0x910);
      iVar2 = 0x24;
      bVar4 = false;
      if (0 < iVar6) {
        bVar4 = true;
      }
      goto LAB_001e439c;
    }
    iVar6 = 0;
LAB_001e4310:
    if (*(int *)(param_5 + 0x2a20) != 2) goto LAB_001e4320;
LAB_001e43f4:
    if (iVar2 == 0x22 && param_4 == 0) {
      iVar2 = 2;
      goto LAB_001e43d0;
    }
    iVar2 = *(ushort *)(param_5 + 0x2b26) + 0x400;
    os_alloc_mem(0,local_2c,iVar2);
    if (local_2c[0] == 0) {
      if (DebugLevel < 3) {
        if (!bVar4) {
          return;
        }
        goto LAB_001e4348;
      }
      bVar5 = true;
      printk("WscData Allocate failed!\n");
    }
    else {
      __memzero(local_2c[0],iVar2);
      zte_wps_overlap_detected(param_1,*(byte *)(param_5 + 0x1c54) & 0xf);
      if (*(int *)(param_2 + 0x904) == 0x24) {
        switch(param_3) {
        case 5:
        case 8:
        case 10:
        case 0xc:
          if (2 < DebugLevel) {
            printk("WscEapApProxyAction: Rx WscMsg(%d) from UPnP, eventID=0x%x!\n",param_3,iVar6);
          }
          WscSendMessage(param_1,4,param_2,*(undefined4 *)(param_2 + 0x908),param_5,0,1);
          iVar2 = DebugLevel;
          if (param_3 == 5) {
            *(undefined4 *)(param_5 + 0x2790) = *(undefined4 *)(param_2 + 0x914);
            if (2 < iVar2) {
              printk("%s():registrarID=0x%x!\n","WscEapApProxyAction");
            }
            if (*(char *)(param_5 + 0x2c44) == '\x01') {
              RTMPCancelTimer(param_5 + 0x2c10,&uStack_2d);
              *(undefined1 *)(param_5 + 0x2c44) = 0;
            }
            bVar5 = true;
            *(undefined4 *)(param_5 + 0x2c48) = 0;
            *(undefined4 *)(param_5 + 0x2790) = 0;
          }
          else {
            if (param_3 != 0xc) goto LAB_001e4320;
            uVar3 = *(byte *)(param_5 + 0x1c54) & 0xf;
            WscBuildBeaconIE(param_1,2,0,0,0,uVar3,0,0,0);
            bVar5 = true;
            WscBuildProbeRespIE(param_1,3,2,0,0,0,*(undefined1 *)(param_5 + 0x1c54),0,0,0);
            UpdateBeaconHandler(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                        + uVar3 * 0x5834 + param_1 + 0xe0,2);
          }
          break;
        case 6:
          if (2 < DebugLevel) {
            printk("WscEapApProxyAction: Rx WscMsg M2D(%d) from UPnP, eventID=0x%x!\n",6,iVar6);
          }
          bVar5 = true;
          WscSendMessage(param_1,4,param_2,*(undefined4 *)(param_2 + 0x908),param_5,0,1);
          *(int *)(param_5 + 0x2c48) = *(int *)(param_5 + 0x2c48) + 1;
          if ((*(int *)(param_5 + 0x2790) != 0) || (*(char *)(param_5 + 0x2c44) != '\0'))
          goto LAB_001e4320;
          RTMPSetTimer(param_5 + 0x2c10,15000);
          *(undefined1 *)(param_5 + 0x2c44) = 1;
          break;
        default:
          if (DebugLevel < 3) goto LAB_001e4320;
          printk("Recv WscMsg(%d) from UPnP, request EventID=%d! drop it!\n",param_3,iVar6);
          bVar5 = true;
        }
      }
      else {
        switch(param_3) {
        case 4:
        case 7:
        case 9:
        case 0xb:
          if (2 < DebugLevel) {
            printk("WscEapApProxyAction: Rx WscMsg(%d) from EAP\n",param_3);
          }
          if (param_3 == 4) {
            cVar1 = WscSendUPnPMessage(param_1,*(byte *)(param_5 + 0x1c54) & 0xf,0x11,1,param_2,
                                       *(undefined4 *)(param_2 + 0x908),0,0,param_5 + 0x1c55,0);
            *(undefined4 *)(param_5 + 0x10) = 0xd;
            bVar5 = cVar1 == '\0';
          }
          else {
            cVar1 = WscSendUPnPMessage(param_1,*(byte *)(param_5 + 0x1c54) & 0xf,0x11,1,param_2,
                                       *(undefined4 *)(param_2 + 0x908),0,
                                       *(undefined4 *)(param_5 + 0x2790),param_5 + 0x1c55,0);
            bVar5 = cVar1 == '\0';
          }
          break;
        default:
          if (DebugLevel < 3) goto LAB_001e4320;
          bVar5 = true;
          printk("Recv WSC Msg(%d) from EAP , it\'s impossible, drop it!\n",param_3);
          break;
        case 0xd:
          if (2 < DebugLevel) {
            printk("WscEapApProxyAction: Rx WSC_ACK from EAP\n");
          }
          if (*(int *)(param_5 + 0x2c48) < 1) goto LAB_001e4320;
          bVar5 = true;
          *(int *)(param_5 + 0x2c48) = *(int *)(param_5 + 0x2c48) + -1;
          break;
        case 0xf:
          if ((2 < DebugLevel) &&
             (printk("WscEapApProxyAction: Rx WSC_DONE from EAP\n"), 2 < DebugLevel)) {
            printk("WscEapApProxyAction: send WSC_DONE to UPnP Registrar!\n");
          }
          cVar1 = WscSendUPnPMessage(param_1,*(byte *)(param_5 + 0x1c54) & 0xf,0x11,2,param_2,
                                     *(undefined4 *)(param_2 + 0x908),0,
                                     *(undefined4 *)(param_5 + 0x2790),param_5 + 0x1c55,0);
          WscSendEapFail(param_1,param_5,0);
          RTMPCancelTimer(param_5 + 0x27cc,&uStack_2d);
          *(undefined1 *)(param_5 + 0x27c8) = 0;
          *(undefined1 *)(param_4 + 0xd24) = 0;
          *(undefined1 *)(param_5 + 0x1c52) = 0;
          __memzero(param_5 + 0x1c55,6);
          if (*(char *)(param_5 + 0x1c5b) == '\0') {
            bVar5 = cVar1 == '\0';
          }
          else {
            bVar5 = cVar1 == '\0';
            *(undefined1 *)(param_5 + 0x1c5b) = 0;
            RTMPCancelTimer(param_5 + 0x1c5c,&uStack_2d);
          }
        }
      }
    }
  }
  else {
    printk("WscEapApProxyAction Enter!\n");
    iVar2 = *(int *)(param_2 + 0x904);
    if (iVar2 == 0x24) goto LAB_001e4388;
    iVar6 = 0;
LAB_001e439c:
    if (DebugLevel < 3) goto LAB_001e4310;
    printk("WscEapApProxyAction():pEntry=%p, ElemMsgType=%ld, MsgType=%d!\n",param_4,iVar2,param_3);
    iVar2 = *(int *)(param_5 + 0x2a20);
    if (iVar2 == 2) {
      iVar2 = *(int *)(param_2 + 0x904);
      goto LAB_001e43f4;
    }
LAB_001e43d0:
    if (2 < DebugLevel) {
      printk("EarlyCheckFailed: gWscActionMode=%d, pEntry=%p!\n",iVar2,param_4);
    }
LAB_001e4320:
    bVar5 = true;
  }
  if (local_2c[0] != 0) {
    os_free_mem();
  }
  if (!(bool)(bVar5 & bVar4)) {
    return;
  }
  if (2 < DebugLevel) {
    printk("Need to send UPnP but bUPnPStatus is false!MsgType=%d, regID=0x%x!\n",param_3,iVar6);
  }
LAB_001e4348:
  WscUPnPErrHandle(param_1,param_5,iVar6);
  return;
}

