// module: mt7915.ko
// function: PeerWNMAction @ 0x22a218
// size: 1648 bytes
//

void PeerWNMAction(int param_1,int param_2)

{
  byte bVar1;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  char cVar6;
  uint uVar7;
  undefined4 uVar8;
  int *piVar9;
  undefined *puVar10;
  uint uVar11;
  char *pcVar12;
  int *local_2c [2];
  
  switch(*(undefined1 *)(param_2 + 0x19)) {
  case 1:
    if (((*(char *)(param_2 + 0x1b) == 'O') && (*(char *)(param_2 + 0x1d) == '\0')) &&
       (*(char *)(param_2 + 0x1f) == '\0')) {
      cVar6 = *(char *)(param_2 + 0x1e);
      if (cVar6 == '\x04') {
        bss_color_parse_collision_report(*(undefined4 *)(param_2 + 0x92c),param_2 + 0x28);
        cVar6 = *(char *)(param_2 + 0x1e);
      }
      if (cVar6 == '\x05') {
        bss_color_parse_inuse_report(*(undefined4 *)(param_2 + 0x92c),param_2 + 0x28);
      }
    }
    break;
  default:
    if (2 < DebugLevel) {
      printk("Invalid action field = %d\n");
    }
    break;
  case 6:
    if (2 < DebugLevel) {
      printk("%s()\n","ReceiveBTMQuery");
    }
    uVar11 = 0;
    do {
      uVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      uVar7 = uVar11 & 0xff;
      iVar4 = uVar7 * 0x5834;
      uVar11 = uVar11 + 1;
      if (uVar3 <= uVar7) goto LAB_0022a36c;
      iVar5 = memcmp((void *)(param_2 + 0x10),
                     "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                     + param_1 + iVar4 + 0x101,6);
    } while (iVar5 != 0);
    if (param_1 + iVar4 == -0x2bbeb4) {
LAB_0022a36c:
      if (-1 < DebugLevel) {
        printk("%s Can not find Peer Control\n","ReceiveBTMQuery");
      }
    }
    else {
      iVar5 = param_1 + iVar4;
      if ("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n"[iVar5 + 0xe] == '\0') {
        if (-1 < DebugLevel) {
          printk("%s BTM Not Supported Drop!!\n","ReceiveBTMQuery");
        }
      }
      else {
        pcVar12 = "RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + param_1 + iVar4 + 0x20;
        uVar8 = *(undefined4 *)
                 (
                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + iVar5 + 0xe0);
        down_interruptible(pcVar12);
        piVar9 = *(int **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar5 + 0x28);
        local_2c[0] = piVar9;
        if (piVar9 != (int *)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + iVar4 + 0x28
                             )) {
          do {
            local_2c[0] = piVar9;
            iVar5 = memcmp((char *)((int)piVar9 + 0xd),(void *)(param_2 + 10),6);
            if (iVar5 == 0) {
              up(pcVar12);
              if (DebugLevel < 0) {
                return;
              }
              printk("%s Find peer address in BTMPeerList already\n","ReceiveBTMQuery");
              return;
            }
            piVar9 = (int *)*piVar9;
            local_2c[0] = piVar9;
          } while ((int *)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + iVar4 + 0x28)
                   != piVar9);
        }
        up(pcVar12);
        os_alloc_mem(0,local_2c,0xb8);
        if (local_2c[0] == (int *)0x0) {
          if (-1 < DebugLevel) {
            printk("%s Not available memory\n","ReceiveBTMQuery");
          }
        }
        else {
          __memzero(local_2c[0],0xb8);
          piVar9 = local_2c[0];
          local_2c[0][2] = 2;
          memmove((char *)((int)local_2c[0] + 0xd),(void *)(param_2 + 10),6);
          cVar6 = *(char *)(param_2 + 0x1a);
          piVar9[5] = param_1;
          *(char *)((int)piVar9 + 0x13) = cVar6;
          down_interruptible(pcVar12);
          piVar9 = *(int **)("RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + iVar4);
          *local_2c[0] = *piVar9;
          local_2c[0][1] = (int)piVar9;
          *(int **)(*piVar9 + 4) = local_2c[0];
          *piVar9 = (int)local_2c[0];
          up(pcVar12);
          wext_send_btm_query_event_newapi
                    (uVar8,(void *)(param_2 + 10),(char *)(param_2 + 0x1a),
                     *(int *)(param_2 + 0x908) - 0x1aU & 0xffff);
          RTMPInitTimer(param_1,local_2c[0] + 0x13,rtmp_timer_WaitPeerBTMReqTimeout,local_2c[0],0);
          RTMPSetTimer(local_2c[0] + 0x13,30000);
        }
      }
    }
    break;
  case 7:
    if (2 < DebugLevel) {
      printk(&_LC4,"ReceiveBTMReq");
    }
    bVar1 = *(byte *)(param_1 + 0x794ab8);
    if (bVar1 != 0) {
      uVar11 = 0;
      puVar10 = &DAT_0036db73 + param_1;
      do {
        iVar4 = memcmp((void *)(param_2 + 4),puVar10,6);
        puVar10 = puVar10 + 0x2137b0;
        if (iVar4 == 0) {
          iVar4 = uVar11 * 0x2137b0;
          if (param_1 + iVar4 != -0x580ddc) {
            if (&DAT_0036db58 + param_1 + iVar4 == (undefined *)0x0) {
              if (DebugLevel < 0) {
                return;
              }
              printk(" %s wdev not initialized\n","ReceiveBTMReq");
              return;
            }
            if ((&DAT_00580e0e)[param_1 + iVar4] == '\0') {
              if (DebugLevel < 0) {
                return;
              }
              printk(" %s BTM Not Supported Drop!! WNMBTMEnable %d\n","ReceiveBTMReq");
              return;
            }
            puVar10 = &DAT_00580dec + param_1 + iVar4;
            down_interruptible(puVar10);
            local_2c[0] = *(int **)(&DAT_00580e28 + param_1 + iVar4);
            if ((local_2c[0] != (int *)(&DAT_00580e28 + param_1 + iVar4)) &&
               (iVar5 = memcmp((undefined *)((int)local_2c[0] + 0xd),(void *)(param_2 + 10),6),
               iVar5 == 0)) {
              up(puVar10);
              if (DebugLevel < 0) {
                return;
              }
              printk(" Found peer entry in list already\n");
              return;
            }
            up(puVar10);
            iVar5 = *(int *)(&DAT_0036db58 + param_1 + uVar11 * 0x2137b0);
            if (iVar5 == 0) {
              if (DebugLevel < 0) {
                return;
              }
              printk("%s NetDev not initialized\n","ReceiveBTMReq");
              return;
            }
            os_alloc_mem(0,local_2c,0xb8);
            if (local_2c[0] != (int *)0x0) {
              __memzero(local_2c[0],0xb8);
              piVar9 = local_2c[0];
              local_2c[0][2] = 3;
              memmove((undefined *)((int)local_2c[0] + 0xd),(void *)(param_2 + 10),6);
              uVar2 = *(undefined1 *)(param_2 + 0x1a);
              piVar9[5] = param_1;
              *(undefined1 *)((int)piVar9 + 0x13) = uVar2;
              down_interruptible(puVar10);
              piVar9 = *(int **)(&DAT_00580e2c + param_1 + iVar4);
              *local_2c[0] = *piVar9;
              local_2c[0][1] = (int)piVar9;
              *(int **)(*piVar9 + 4) = local_2c[0];
              *piVar9 = (int)local_2c[0];
              up(puVar10);
              wext_send_btm_req_event
                        (iVar5,(void *)(param_2 + 10),param_2 + 0x1b,
                         *(int *)(param_2 + 0x908) - 0x1aU & 0xffff);
              RTMPInitTimer(param_1,local_2c[0] + 0x20,rtmp_timer_WaitPeerBTMRspTimeout,local_2c[0],
                            0);
              RTMPSetTimer(local_2c[0] + 0x20,15000);
              return;
            }
            if (DebugLevel < 0) {
              return;
            }
            printk("%s Not available memory\n","ReceiveBTMReq");
            return;
          }
          break;
        }
        uVar11 = uVar11 + 1;
      } while ((uVar11 & 0xff) < (uint)bVar1);
    }
    if (-1 < DebugLevel) {
      printk(" %s Can not find Peer Control\n","ReceiveBTMReq");
    }
    break;
  case 8:
    FUN_0022498c(param_1,param_2);
    return;
  case 0x1a:
    ReceiveWNMNotifyReq(param_1,param_2);
    return;
  case 0x1b:
    ReceiveWNMNotifyRsp(param_1,param_2);
  }
  return;
}

