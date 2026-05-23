// module: mt7915.ko
// function: WscEAPAction @ 0x1f0dd4
// size: 6948 bytes
//

/* WARNING: Type propagation algorithm not settling */

void WscEAPAction(int param_1,uint *param_2)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  byte bVar8;
  uint uVar9;
  void *__s2;
  int iVar10;
  uint *puVar11;
  uint uVar12;
  void *__s1;
  int iVar13;
  char *pcVar14;
  bool bVar15;
  bool bVar16;
  int local_5c;
  int local_58;
  uint local_50;
  ushort local_3a;
  int *local_38;
  undefined4 local_34;
  undefined4 local_2e;
  undefined2 local_2a;
  
  local_38 = (int *)0x0;
  local_2e = 0;
  local_2a = 0;
  if (2 < DebugLevel) {
    printk("-----> WscEAPAction\n");
  }
  local_2a = (undefined2)param_2[1];
  local_2e = *param_2;
  memmove(param_2,(void *)((int)param_2 + 6),param_2[0x242]);
  hex_dump("(WscEAPAction)Elem->MsgLen",param_2,param_2[0x242]);
  uVar3 = WscRxMsgType(param_1,param_2);
  bVar16 = param_2[0x241] == 0x24;
  uVar1 = (uint)bVar16;
  if (2 < DebugLevel) {
    pcVar14 = "FALSE";
    if (uVar1 != 0) {
      pcVar14 = "TRUE";
    }
    printk("WscEAPAction: Addr: %02x:%02x:%02x:%02x:%02x:%02x, MsgType: 0x%02X, bUPnPMsg: %s\n",
           local_2e & 0xff,local_2e._1_1_,local_2e._2_1_,local_2e >> 0x18,(undefined1)local_2a,
           local_2a._1_1_,uVar3,pcVar14);
  }
  uVar12 = param_2[0x24b];
  iVar13 = uVar12 + 0x12e4;
  if (uVar1 == 0) {
    (**(code **)(*(int *)(uVar12 + 0x904) + 0xb8))(param_1,&local_2e,uVar12,&local_38);
    if (*(int *)(uVar12 + 0x14) != 1 && *(int *)(uVar12 + 0x14) != 0x20) goto LAB_001f0f94;
    if (local_38 == (int *)0x0) {
      if (DebugLevel < 3) {
        return;
      }
      printk("WscEAPAction: pEntry is NULL.\n");
      iVar13 = DebugLevel;
      goto joined_r0x001f1910;
    }
    if (*local_38 == 0x20001) {
      local_50 = (uint)*(byte *)(local_38 + 0x39);
      if ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                [param_1 + 0xda] <= local_50) {
        if (DebugLevel < 3) {
          return;
        }
        printk("WscEAPAction: Unknow apidex(=%d).\n");
        iVar13 = DebugLevel;
        goto joined_r0x001f1910;
      }
    }
    else {
      local_50 = (uint)*(byte *)(local_38 + 0x39);
    }
    if (2 < DebugLevel) {
      local_5c = 0;
      printk("WscEAPAction: apidex=%d.\n",local_50);
      local_58 = 0;
      goto LAB_001f0ea8;
    }
    local_5c = 0;
    local_58 = 0;
    *(undefined1 *)(uVar12 + 0x3a72) = 1;
LAB_001f0ebc:
    if ((*local_38 != 0x20001) || (1 < (uVar3 - 0x22 & 0xff))) goto LAB_001f0ed0;
    if (((*(byte *)((int)local_38 + 0xd25) & 2) != 0) && (0xc < *(int *)(uVar12 + 0x12f4))) {
      if (DebugLevel < 3) {
        return;
      }
      printk("WscEAPAction: Already receive EAP_RSP(Identitry) from this STA, ignore it.\n");
      iVar13 = DebugLevel;
      goto joined_r0x001f1910;
    }
    *(byte *)((int)local_38 + 0xd25) = *(byte *)((int)local_38 + 0xd25) | 2;
    *(undefined1 *)(uVar12 + 0x3aad) = 1;
  }
  else {
    if (*(int *)(uVar12 + 0x14) == 1 || *(int *)(uVar12 + 0x14) == 0x20) {
      local_5c = 0;
      local_58 = 0;
      local_50 = 0;
    }
    else {
LAB_001f0f94:
      local_5c = GetStaCfgByWdev(param_1,uVar12);
      if (local_5c == 0) {
        printk(&_LC163,0x3ef);
        dump_stack();
      }
      local_58 = 2;
      local_50 = 0;
    }
LAB_001f0ea8:
    *(undefined1 *)(uVar12 + 0x3a72) = 1;
    if (local_38 != (int *)0x0) goto LAB_001f0ebc;
LAB_001f0ed0:
    *(undefined1 *)(uVar12 + 0x3aad) = 1;
    if (uVar3 == 0x28) {
      WscSendEapFragData(param_1,iVar13,local_38);
      return;
    }
  }
  if (uVar3 == 0x22) {
    if (((*(uint *)(uVar12 + 0x12e4) & 1) != 0) || ((uVar1 & *(uint *)(uVar12 + 0x12e4) >> 1) != 0))
    {
      *(undefined4 *)(uVar12 + 0x3d04) = 1;
      *(bool *)(uVar12 + 0x2f35) = bVar16;
      WscEapEnrolleeAction(param_1,param_2,0x21,local_38,iVar13);
    }
    goto LAB_001f10e0;
  }
  if (uVar3 == 0x23) {
    if (2 < DebugLevel) {
      printk("WscEAPAction: Rx Identity\n");
    }
    *(undefined4 *)(uVar12 + 0x3d04) = 4;
    if (uVar1 == 0) {
      if (*(int *)(uVar12 + 0x12e8) == 2) {
        __s2 = (void *)(uVar12 + 0x2f39);
        iVar5 = HcGetBandByChannel(param_1,*(undefined1 *)((int)param_2 + 0x91f));
        WscPBC_DPID_FromSTA(param_1,__s2,iVar5);
        WscPBCSessionOverlapCheck(param_1,iVar5);
        if (*(char *)(param_1 + iVar5 + 0x795ab4) == '\x01') {
          local_50 = iVar5 * 2;
          __s1 = (void *)(param_1 + iVar5 * 0x18 + 0x795ab7);
          iVar10 = memcmp(__s1,&ZERO_MAC_ADDR,6);
          if ((iVar10 != 0) && (iVar10 = memcmp(__s1,__s2,6), iVar10 != 0)) {
            uVar3 = 0;
            if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                [param_1 + 0xda] != '\0') {
              do {
                iVar10 = HcGetBandByWdev("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                         + param_1 + uVar3 * 0x5834 + 0xe0);
                if (((iVar10 == iVar5) &&
                    (iVar10 = param_1 + uVar3 * 0x5834,
                    *(int *)(
                            "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                            + iVar10 + 0x2b) != 0)) &&
                   ("PIN authentication or communication error occurs!!\nRegistrar does NOT accept the same PIN again!(PIN:%08u)\n"
                    [iVar10 + 0x5c] == '\x01')) {
                  if (2 < DebugLevel) {
                    printk("%s(): found pAd->ApCfg.MBSSID[%d] WPS on\n","WscEAPAction",uVar3);
                  }
                  if (uVar3 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                    [param_1 + 0xda]) {
                    if (0 < DebugLevel) {
                      printk("%s(): pAd->ApCfg.MBSSID[%d] WPS on, PBC Overlap detected\n",
                             "WscEAPAction",uVar3);
                    }
                    *(undefined1 *)(param_1 + 0x795a81) = 1;
                    goto LAB_001f1b44;
                  }
                  break;
                }
                uVar3 = uVar3 + 1 & 0xff;
              } while (uVar3 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                     [param_1 + 0xda]);
            }
            if (0 < DebugLevel) {
              printk("%s(): pAd->ApCfg.MBSSID[%d] WPS off, PBC Overlap is invalid\n","WscEAPAction",
                     uVar3);
            }
            *(undefined1 *)(param_1 + 0x795a81) = 0;
            goto LAB_001f114c;
          }
        }
        if (*(char *)(param_1 + 0x795a81) != '\0') {
          local_50 = iVar5 << 1;
LAB_001f1b44:
          hex_dump("EntryAddr",__s2,6);
          iVar5 = (local_50 + iVar5) * 8;
          hex_dump("StaMacAddr0",param_1 + iVar5 + 0x795ab7,6);
          hex_dump("StaMacAddr1",param_1 + iVar5 + 0x795abd,6);
          hex_dump("StaMacAddr2",param_1 + iVar5 + 0x795ac3,6);
          hex_dump("StaMacAddr3",param_1 + iVar5 + 0x795ac9,6);
          if ((*(int *)(uVar12 + 0x12e8) == 2) && (*(char *)(param_1 + 0x795a81) == '\x01')) {
            *(undefined4 *)(uVar12 + 0x12f0) = 0x109;
            uVar4 = HcGetBandByChannel(param_1,*(undefined1 *)((int)param_2 + 0x91f));
            RTMPSetLED(param_1,10,uVar4);
            if (2 < DebugLevel) {
              printk("WscEAPAction: PBC Session Overlap!\n");
            }
            __memzero(&local_34,4);
            local_34 = 0x100;
            Kernel_ASEND("cspd.wlan_manage.wlan_mgr",0xa277,&local_34,4,0,0);
            cVar2 = *(char *)(uVar12 + 0x2f36);
            goto LAB_001f10f4;
          }
        }
      }
LAB_001f114c:
      if ((*(uint *)(uVar12 + 0x12e4) & 6) == 0) {
LAB_001f10ec:
        cVar2 = *(char *)(uVar12 + 0x2f36);
        goto LAB_001f10f4;
      }
      if (local_38 == (int *)0x0) {
        if (local_58 == 0) {
LAB_001f11c8:
          if (*(char *)(uVar12 + 0x3f28) == '\x01') {
            RTMPCancelTimer(uVar12 + 0x3ef4,&local_3a);
            *(undefined1 *)(uVar12 + 0x3f28) = 0;
          }
          *(undefined4 *)(uVar12 + 0x3a74) = 0;
          *(undefined4 *)(uVar12 + 0x3f2c) = 0;
          goto LAB_001f11e4;
        }
        *(undefined1 *)(uVar12 + 0x2f36) = 1;
        *(undefined4 *)(uVar12 + 0x12f4) = 0xc;
      }
      else {
        if (DebugLevel < 3) {
          if (local_58 == 0) {
LAB_001f1180:
            WscSendUPnPConfReqMsg
                      (param_1,*(byte *)(uVar12 + 0x2f38) & 0xf,
                       "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                       + (uint)*(byte *)(local_38 + 0x39) * 0x5834 + param_1 + 0x34,local_38 + 0x3b,
                       2,0,0);
            goto LAB_001f11c8;
          }
          *(undefined1 *)(uVar12 + 0x2f36) = 1;
          *(undefined4 *)(uVar12 + 0x12f4) = 0xc;
        }
        else {
          printk("%s: pEntry->Addr=%02x:%02x:%02x:%02x:%02x:%02x\n","WscEAPAction",
                 (char)local_38[0x3b],*(undefined1 *)((int)local_38 + 0xed),
                 *(undefined1 *)((int)local_38 + 0xee),*(undefined1 *)((int)local_38 + 0xef),
                 (char)local_38[0x3c],*(undefined1 *)((int)local_38 + 0xf1));
          if (local_58 == 0) {
            if (local_38 == (int *)0x0) goto LAB_001f11c8;
            goto LAB_001f1180;
          }
LAB_001f11e4:
          *(undefined1 *)(uVar12 + 0x2f36) = 1;
          *(undefined4 *)(uVar12 + 0x12f4) = 0xc;
          if (local_38 == (int *)0x0) goto LAB_001f1588;
        }
        if (*local_38 == 0x20001) {
          *(undefined1 *)(uVar12 + 0x3edc) = 1;
          if (local_58 == 0) {
            WscSendMessage(param_1,1,0,0,iVar13,0,1);
            cVar2 = *(char *)(uVar12 + 0x2f36);
          }
          else if (((*(uint *)(param_1 + 0x795124) & 2) == 0) || (*(int *)(uVar12 + 0x12e4) != 4)) {
            WscSendMessage(param_1,1,0,0,iVar13,2,2);
            cVar2 = *(char *)(uVar12 + 0x2f36);
          }
          else {
            WscSendMessage(param_1,1,0,0,iVar13,2,1);
            cVar2 = *(char *)(uVar12 + 0x2f36);
          }
          goto LAB_001f10f4;
        }
      }
LAB_001f1588:
      if ((*(uint *)(param_1 + 0xa39f84) & 0x140) == 0) {
        RTMPModTimer(uVar12 + 0x3ab0,5000);
        *(undefined1 *)(uVar12 + 0x3aac) = 1;
      }
      goto LAB_001f1100;
    }
LAB_001f149c:
    if (*(char *)(uVar12 + 0x3a71) != '\0') {
      RTMPModTimer(uVar12 + 0x3a78,15000);
    }
    if (*(char *)(uVar12 + 0x3aac) != '\0') {
      if (local_58 == 0 && *(int *)(uVar12 + 0x3d04) == 2) {
        RTMPModTimer(uVar12 + 0x3ab0,5000);
      }
      else {
        RTMPCancelTimer(uVar12 + 0x3ab0,&local_3a);
        *(undefined1 *)(uVar12 + 0x3aac) = 0;
      }
    }
LAB_001f14e8:
    iVar13 = DebugLevel;
    *(undefined1 *)(uVar12 + 0x3a72) = 0;
  }
  else if (uVar3 == 0x25) {
    if (2 < DebugLevel) {
      printk("Receive EAP_Req/Identity from WPS AP or WCN\n");
    }
    if (uVar1 != 0) {
      if (*(int *)(uVar12 + 0x12e4) == 1) {
        *(undefined4 *)(uVar12 + 0x3d04) = 1;
        *(undefined1 *)(uVar12 + 0x2f35) = 1;
        WscEapEnrolleeAction(param_1,param_2,0x26,local_38,iVar13);
      }
      else if (local_38 != (int *)0x0) {
        WscSendEapRspId(param_1,local_38,iVar13);
      }
      goto LAB_001f149c;
    }
    if (local_38 != (int *)0x0) {
      WscSendEapRspId(param_1,local_38,iVar13);
    }
    if (*(int *)(uVar12 + 0x12f4) - 0xcU < 0xe) goto LAB_001f10ec;
    if (*(int *)(uVar12 + 0x12e4) == 4) {
      uVar4 = 0xc;
    }
    else {
      uVar4 = 0xb;
    }
    *(undefined4 *)(uVar12 + 0x12f4) = uVar4;
    cVar2 = *(char *)(uVar12 + 0x2f36);
LAB_001f10f4:
    if (cVar2 == '\x01') goto LAB_001f1588;
LAB_001f1100:
    iVar13 = DebugLevel;
    if (uVar1 != 0) goto LAB_001f14e8;
  }
  else {
    if (uVar3 == 0x26) {
      if (DebugLevel < 3) {
        if (*(int *)(uVar12 + 0x12e4) == 1) {
LAB_001f15d8:
          *(undefined4 *)(uVar12 + 0x3d04) = 1;
          *(bool *)(uVar12 + 0x2f35) = bVar16;
          WscEapEnrolleeAction(param_1,param_2,0x26,local_38,iVar13);
          if (*(char *)(uVar12 + 0x3aac) == '\0') {
            *(undefined1 *)(uVar12 + 0x3aac) = 1;
            RTMPSetTimer(uVar12 + 0x3ab0,5000);
          }
        }
      }
      else {
        printk("Receive EAP_Req(Wsc_Start) from WPS AP\n");
        if (*(int *)(uVar12 + 0x12e4) == 1) goto LAB_001f15d8;
        if (2 < DebugLevel) {
          printk("Ignore EAP_Req(Wsc_Start) from WPS AP\n");
        }
      }
      goto LAB_001f10e0;
    }
    if (uVar3 == 0x27) {
      if (2 < DebugLevel) {
        printk("Receive EAP_Fail from WPS AP\n");
      }
      iVar13 = *(int *)(uVar12 + 0x12f4);
      if (iVar13 < 0x1a) {
        if ((iVar13 != 0x10) && (9 < iVar13 || iVar13 == 3)) {
          *(undefined4 *)(uVar12 + 0x12e4) = 0;
          *(undefined4 *)(uVar12 + 0x12f4) = 0;
          *(undefined4 *)(uVar12 + 0x12f0) = 2;
          if (local_58 == 2) {
            FUN_001e0304(param_1,uVar12);
          }
        }
      }
      else {
        *(undefined4 *)(uVar12 + 0x12f4) = 0;
        if (((local_58 == 2) && ((*(byte *)(param_1 + 0x286294) & 3) == 3)) &&
           (*(int *)(uVar12 + 0x14) == 2)) {
          bVar8 = *(byte *)(uVar12 + 0x2f38);
          *(undefined4 *)(uVar12 + 0x12e4) = 0;
          if (*(int *)(uVar12 + 0x3bc8) != 0) {
            if (*(int *)(&DAT_0036da4c + param_1) == 0) {
              if (0 < DebugLevel) {
                printk("<----- WscConWpsStop\n");
              }
              *(undefined4 *)(uVar12 + 0x3bc8) = 0;
            }
            else {
              (&DAT_0036da50)[param_1] = 1;
              if (*(int *)(&DAT_0036da4c + param_1) == 1) {
                *(undefined1 *)(param_1 + 0x79463d) = 0;
              }
              else {
                (&DAT_00580e8d)[param_1] = 0;
              }
              ApCliIfDown(param_1);
              RTMPSetTimer(param_1 + 0x36da54,10000);
              (&DAT_0036da88)[param_1] = 1;
            }
          }
          if (((local_38 != (int *)0x0) && (*local_38 == 2)) &&
             ((iVar13 = (bVar8 & 0xf) * 0x2137b0 + param_1, (&DAT_00580e8d)[iVar13] == '\x01' &&
              (*(int *)(&DAT_0036da4c + param_1) == 0)))) {
            (&DAT_00580e8d)[iVar13] = 0;
            ApCliIfDown(param_1);
            (&DAT_00580e8d)[iVar13] = 1;
          }
        }
      }
      goto LAB_001f10e0;
    }
    if (uVar3 != 4) {
      uVar9 = uVar3 & 0xfd;
      if ((uVar3 & 0xf7) == 7 || uVar9 == 9) {
        iVar5 = FUN_001e0460(param_1,param_2,1,iVar13);
        zte_wps_overlap_detected(param_1,*(byte *)(uVar12 + 0x2f38) & 0xf);
        if (((*(uint *)(uVar12 + 0x12e4) & 4) == 0) ||
           (iVar5 == 0 || *(char *)(uVar12 + 0x3cc8) == '\0')) {
          if (((*(uint *)(uVar12 + 0x12e4) & 2) == 0) || (local_58 != 0 || uVar1 != 0))
          goto LAB_001f10e0;
          *(undefined4 *)(uVar12 + 0x3d04) = 2;
          WscEapApProxyAction(param_1,param_2,uVar3,local_38,iVar13);
          goto LAB_001f10ec;
        }
        if (uVar1 == 0) {
          if (*(char *)(uVar12 + 0x3a70) != '\0') {
LAB_001f1850:
            iVar13 = DebugLevel;
            if (2 < DebugLevel) {
              printk("UPnP Registrar is working now, ignore EAP Messages.\n");
              iVar13 = DebugLevel;
            }
            goto LAB_001f1108;
          }
          *(undefined4 *)(uVar12 + 0x3d04) = 4;
          if (local_38 == (int *)0x0) goto LAB_001f10ec;
        }
        else {
          *(undefined4 *)(uVar12 + 0x3d04) = 4;
          if (local_38 == (int *)0x0) goto LAB_001f149c;
        }
        WscEapRegistrarAction(param_1,param_2,uVar3,local_38,iVar13);
LAB_001f10e0:
        if (uVar1 == 0) goto LAB_001f10ec;
        goto LAB_001f149c;
      }
      uVar6 = uVar3 - 5 & 0xff;
      bVar15 = 7 < uVar9;
      if (uVar9 != 8) {
        bVar15 = uVar6 != 0;
      }
      if ((!bVar15 || (uVar9 == 8 || uVar6 == 1)) || (uVar3 == 0xc)) {
        iVar5 = FUN_001e0460(param_1,param_2,0,iVar13);
        zte_wps_overlap_detected(param_1,*(byte *)(uVar12 + 0x2f38) & 0xf);
        if (local_58 == 0) {
          if ((*(char *)(uVar12 + 0x3e14) != '\0') || (*(char *)(uVar12 + 0x3e15) == '\0'))
          goto LAB_001f1800;
          uVar9 = *(uint *)(uVar12 + 0x12e4);
        }
        else {
          if ((local_58 != 2) || (*(char *)(uVar12 + 0x3cc8) == '\0')) goto LAB_001f10e0;
LAB_001f1800:
          uVar9 = *(uint *)(uVar12 + 0x12e4);
          if (((uVar9 & 1) != 0) && (iVar5 != 0)) {
            *(undefined4 *)(uVar12 + 0x3d04) = 1;
            *(bool *)(uVar12 + 0x2f35) = bVar16;
            if (uVar3 == 5) {
              if (local_58 == 0) {
                if (*(char *)(uVar12 + 0x3cc8) == '\0') {
                  *(undefined4 *)(uVar12 + 0x12e8) = 1;
                  WscGetConfWithoutTrigger(param_1,iVar13,0);
                }
                else if ((*(byte *)(uVar12 + 0x2f38) & 0x30) == 0) {
                  WscBuildBeaconIE(param_1,*(undefined1 *)(uVar12 + 0x12ec),1,
                                   *(uint *)(uVar12 + 0x12e8) & 0xffff,
                                   *(undefined2 *)(uVar12 + 0x12ee),*(byte *)(uVar12 + 0x2f38) & 0xf
                                   ,0,0,0);
                  WscBuildProbeRespIE(param_1,3,*(undefined1 *)(uVar12 + 0x12ec),1,
                                      *(uint *)(uVar12 + 0x12e8) & 0xffff,
                                      *(undefined2 *)(uVar12 + 0x12ee),
                                      *(undefined1 *)(uVar12 + 0x2f38),0,0,0);
                  UpdateBeaconHandler(param_1,*(undefined4 *)(uVar12 + 0x3cd0),2);
                }
              }
              *(undefined1 *)(uVar12 + 0x12fc) = *(undefined1 *)(uVar12 + 0x1304);
              WscGetRegDataPIN(param_1,*(undefined4 *)(uVar12 + 0x1300),iVar13);
              if (2 < DebugLevel) {
                printk("(%d) WscEnrolleePinCode: %08u\n",1,*(undefined4 *)(uVar12 + 0x1300));
              }
            }
            if ((uVar1 != 0) || (*(char *)(uVar12 + 0x3a70) == '\0')) {
              WscEapEnrolleeAction(param_1,param_2,uVar3,local_38,iVar13);
              goto LAB_001f10e0;
            }
            goto LAB_001f1850;
          }
        }
        if ((uVar9 & 2) != 0) {
          uVar9 = uVar1;
          if (local_58 != 0) {
            uVar9 = 0;
          }
          if (uVar9 != 0) {
            *(undefined4 *)(uVar12 + 0x3d04) = 2;
            WscEapApProxyAction(param_1,param_2,uVar3,local_38,iVar13);
            goto LAB_001f149c;
          }
        }
        goto LAB_001f10e0;
      }
      if (uVar3 == 0xd) {
        if (2 < DebugLevel) {
          printk("WscState: %d\n",*(undefined4 *)(uVar12 + 0x12f4));
        }
        uVar3 = *(uint *)(uVar12 + 0x12e4);
        if (((uVar3 & 4) == 0) || (0xe < *(int *)(uVar12 + 0x12f4))) {
          if ((uVar3 & 1) != 0) {
            iVar5 = FUN_001e0460(param_1,param_2,0,iVar13);
            if (iVar5 != 0) {
              *(undefined4 *)(uVar12 + 0x3d04) = 1;
              *(bool *)(uVar12 + 0x2f35) = bVar16;
              WscEapEnrolleeAction(param_1,param_2,0xd,local_38,iVar13);
              goto LAB_001f10e0;
            }
            uVar3 = *(uint *)(uVar12 + 0x12e4);
          }
          if (((uint)(local_58 == 0) & uVar3 >> 1) != 0) {
            *(undefined4 *)(uVar12 + 0x3d04) = 2;
            WscEapApProxyAction(param_1,param_2,0xd,local_38,iVar13);
          }
        }
        else {
          iVar13 = FUN_001e0460(param_1,param_2,1,iVar13);
          if (iVar13 != 0) {
            if (0 < *(int *)(uVar12 + 0x3f2c)) {
              *(int *)(uVar12 + 0x3f2c) = *(int *)(uVar12 + 0x3f2c) + -1;
            }
            *(undefined4 *)(uVar12 + 0x12f4) = 1;
            *(undefined1 *)(uVar12 + 0x2f36) = 0;
          }
        }
        goto LAB_001f10e0;
      }
      if (uVar3 == 0xe) {
        if (uVar1 != 0) {
          if ((*(int *)(uVar12 + 0x12f4) == 0x17) && (*(char *)(uVar12 + 0x12ec) == '\x02')) {
            *(undefined1 *)(uVar12 + 0x3cc8) = 0;
            *(undefined4 *)(uVar12 + 0x12f0) = 0x22;
          }
          os_alloc_mem(0,&local_34,0x400);
          if (local_34 != 0) {
            __memzero(local_34,0x400);
            uVar4 = BuildMessageNACK(param_1,iVar13,local_34);
            cVar2 = WscSendUPnPMessage(param_1,*(byte *)(uVar12 + 0x2f38) & 0xf,0x11,0,local_34,
                                       uVar4,param_2[0x244],param_2[0x245],param_1 + 0x794b5b,
                                       local_58);
            os_free_mem(local_34);
            if (cVar2 == '\0') {
              WscUPnPErrHandle(param_1,iVar13,param_2[0x244]);
            }
          }
          if (*(char *)(uVar12 + 0x3a71) == '\x01') {
            RTMPCancelTimer(uVar12 + 0x3a78,&local_3a);
            *(undefined1 *)(uVar12 + 0x3a71) = 0;
          }
          *(undefined1 *)(uVar12 + 0x3a70) = 0;
          goto LAB_001f149c;
        }
        iVar5 = FUN_001e0460(param_1,param_2,0,iVar13);
        if ((iVar5 == 0) && (iVar5 = FUN_001e0460(param_1,param_2,1,iVar13), iVar5 == 0))
        goto LAB_001f10ec;
        if (2 < DebugLevel) {
          printk("Receive NACK from WPS client.\n");
        }
        uVar9 = param_2[0x242];
        local_3a = 0;
        uVar3 = local_34;
        do {
          uVar6 = uVar9 & 0xffff;
          local_34 = uVar3;
          if (uVar6 < 5) {
LAB_001f2078:
            if (2 < DebugLevel) {
              printk("WSC_ID_CONFIG_ERROR is missing\n");
            }
            if (*(int *)(uVar12 + 0x12f4) < 0x14) goto LAB_001f233c;
            goto LAB_001f2094;
          }
          uVar3 = *param_2;
          puVar11 = param_2 + 1;
          local_34._2_2_ = (ushort)(uVar3 >> 0x10);
          uVar7 = (local_34._2_2_ & 0xff) << 8 | (uint)(local_34._2_2_ >> 8);
          uVar9 = uVar6 + (0xfffc - uVar7);
          param_2 = (uint *)((int)puVar11 + uVar7);
          local_34 = uVar3;
          if (uVar6 < uVar7 + 4) {
            if (2 < DebugLevel) {
              printk("unexpected WSC IE Length(%u)\n");
            }
            goto LAB_001f2078;
          }
        } while (((uVar3 & 0xff) << 8 | uVar3 >> 8 & 0xff) != 0x1009);
        local_3a = (ushort)*puVar11;
        if (DebugLevel < 3) {
          uVar3 = (local_3a & 0xff) << 8 | (uint)(local_3a >> 8);
        }
        else {
          uVar3 = (local_3a & 0xff) << 8 | (uint)(local_3a >> 8);
          printk("WSC_ID_CONFIG_ERROR: %d\n",uVar3);
        }
        iVar10 = *(int *)(uVar12 + 0x12f4);
        bVar16 = SBORROW4(uVar3,0xf);
        iVar5 = uVar3 - 0xf;
        if (uVar3 != 0xf) {
          bVar16 = SBORROW4(iVar10,0x13);
          iVar5 = iVar10 + -0x13;
        }
        if ((uVar3 != 0xf && iVar10 != 0x13) && iVar5 < 0 == bVar16) {
LAB_001f2094:
          *(undefined1 *)(uVar12 + 0x3cd8) = 1;
          WscDelListEntryByMAC(uVar12 + 0x3ee8,local_38 + 0x3b);
          if (0x16 < *(int *)(uVar12 + 0x12f4)) goto LAB_001f233c;
          bVar8 = 1;
          *(undefined4 *)(uVar12 + 0x12f0) = 2;
        }
        else {
LAB_001f233c:
          bVar8 = 0;
        }
        iVar5 = *(int *)(uVar12 + 0x12f4);
        if (iVar5 == 0) {
          if ((local_58 == 0) && (*(short *)(uVar12 + 0x145c) != 0)) {
            bVar8 = 1;
          }
        }
        else if (iVar5 == 0x17) {
          if (*(char *)(uVar12 + 0x12ec) == '\x02') {
            *(undefined1 *)(uVar12 + 0x3cc8) = 0;
            bVar8 = 1;
            *(undefined4 *)(uVar12 + 0x12f0) = 0x22;
            *(undefined1 *)(uVar12 + 0x3cd8) = 0;
          }
        }
        else if (((local_58 == 0 && iVar5 == 0x18) && (*(char *)(uVar12 + 0x12ec) == '\x02')) &&
                ((*(uint *)(
                           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           + local_50 * 0x5834 + param_1 + 0x254) & 0xe) != 0)) {
          bVar8 = 1;
          *(undefined4 *)(uVar12 + 0x12f0) = 2;
        }
        if ((bool)(bVar8 & local_58 == 0)) {
          if (*(int *)(uVar12 + 0x12f8) == 0) {
            uVar3 = *(byte *)(uVar12 + 0x2f38) & 0xf;
            WscBuildBeaconIE(param_1,*(undefined1 *)(uVar12 + 0x12ec),0,0,0,uVar3,0,0,0);
            WscBuildProbeRespIE(param_1,3,*(undefined1 *)(uVar12 + 0x12ec),0,0,0,
                                *(undefined1 *)(uVar12 + 0x2f38),0,0,0);
            UpdateBeaconHandler(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                        + uVar3 * 0x5834 + param_1 + 0xe0,2);
            if (*(char *)(uVar12 + 0x2f3f) != '\0') {
              RTMPCancelTimer(uVar12 + 0x2f40,&local_3a);
              *(undefined1 *)(uVar12 + 0x2f3f) = 0;
            }
            if (*(char *)(uVar12 + 0x3cc8) != '\0') {
              *(undefined1 *)(uVar12 + 0x3cc8) = 0;
            }
          }
LAB_001f2130:
          WscSendEapFail(param_1,iVar13,1);
          *(undefined4 *)(uVar12 + 0x12f4) = 3;
        }
        else {
          if ((local_58 == 0) ||
             (((*(uint *)(param_1 + 0x795124) & 2) != 0 && (*(int *)(uVar12 + 0x12e4) == 4))))
          goto LAB_001f2130;
          if ((local_58 != 0 && local_5c != 0) && ((*(uint *)(local_5c + 0x212464) & 1) != 0)) {
            local_34 = 0;
            os_alloc_mem(0,&local_34,0x100);
            if (local_34 != 0) {
              uVar4 = BuildMessageNACK(param_1,iVar13);
              if (*(char *)(param_1 + 0x286285) == '\x01') {
                if ((*(byte *)(uVar12 + 0x2f38) & 0x30) == 0) {
                  WscSendMessage(param_1,3,local_34,uVar4,iVar13,*(byte *)(uVar12 + 0x2f38) & 0x30,1
                                );
                }
                else {
                  WscSendMessage(param_1,3,local_34,uVar4,iVar13,1,2);
                }
              }
              if (*(char *)(param_1 + 0x286285) == '\0') {
                if (((*(uint *)(param_1 + 0x795124) & 2) == 0) ||
                   ((*(uint *)(uVar12 + 0x12e4) & 4) == 0)) {
                  WscSendMessage(param_1,3,local_34,uVar4,iVar13,2,2);
                }
                else {
                  WscSendMessage(param_1,3,local_34,uVar4,iVar13,2,1);
                }
              }
              if (local_34 != 0) {
                os_free_mem();
              }
            }
            *(undefined4 *)(uVar12 + 0x12f4) = 0x1b;
          }
        }
        if (*(int *)(uVar12 + 0x12f8) != 0) goto LAB_001f10ec;
        RTMPCancelTimer(uVar12 + 0x3ab0,&local_3a);
        *(undefined1 *)(uVar12 + 0x3aac) = 0;
        *(undefined1 *)(uVar12 + 0x16fc) = 1;
        cVar2 = *(char *)(uVar12 + 0x2f36);
        goto LAB_001f10f4;
      }
      if (2 < DebugLevel) {
        printk("Unsupported Msg Type (%02X)\n",uVar3);
      }
      *(undefined4 *)(uVar12 + 0x12f0) = 2;
      *(undefined2 *)(uVar12 + 0x145c) = 0;
      FUN_001e2b5c(param_1,local_38,iVar13);
      goto LAB_001f1100;
    }
    uVar3 = *(uint *)(uVar12 + 0x12e4);
    bVar8 = 0;
    if ((uVar3 & 4) == 0) {
LAB_001f1944:
      if ((uVar3 & 2) == 0) {
        if ((*(char *)(uVar12 + 0x3cc8) != '\0') || (*(char *)(param_1 + 0x286285) != '\x01'))
        goto LAB_001f19c8;
        if (2 < DebugLevel) {
          printk("WscTrigger is FALSE, ignore EAP M1.\n");
          goto LAB_001f1100;
        }
      }
      else {
        if (local_58 == 0 && uVar1 == 0) {
          if ((*(char *)(uVar12 + 0x3cc8) == '\0') || (*(int *)(uVar12 + 0x12f4) < 0x12)) {
            *(undefined4 *)(uVar12 + 0x3d04) = 2;
            WscEapApProxyAction(param_1,param_2,4,local_38,iVar13);
            goto LAB_001f10ec;
          }
          goto LAB_001f10e0;
        }
LAB_001f19c8:
        bVar15 = (bool)(bVar8 ^ 1);
        if (local_58 == 0) {
          bVar15 = false;
        }
        if (!bVar15) goto LAB_001f10e0;
        if (2 < DebugLevel) {
          printk("(Line:%d)Ignore EAP M1.\n",0x5d0);
          goto LAB_001f1100;
        }
      }
      if (uVar1 == 0) {
        *(bool *)(uVar12 + 0x3aad) = bVar16;
        return;
      }
      goto LAB_001f14e8;
    }
    *(undefined4 *)(uVar12 + 0x3d04) = 4;
    if ((uVar1 != 0) || (*(char *)(uVar12 + 0x3a70) == '\0')) {
      if (local_38 == (int *)0x0) {
        bVar8 = 1;
      }
      else {
        WscEapRegistrarAction(param_1,param_2,4,local_38,iVar13);
        bVar8 = 1;
        uVar3 = *(uint *)(uVar12 + 0x12e4);
      }
      goto LAB_001f1944;
    }
    iVar13 = DebugLevel;
    if (2 < DebugLevel) {
      printk("UPnP Registrar is working now, ignore EAP M1.\n");
      iVar13 = DebugLevel;
    }
  }
LAB_001f1108:
  *(undefined1 *)(uVar12 + 0x3aad) = 0;
joined_r0x001f1910:
  if (2 < iVar13) {
    printk("<----- WscEAPAction\n");
  }
  return;
}

