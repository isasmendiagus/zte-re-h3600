// module: mt7915.ko
// function: sta_rx_pkt_allow @ 0xcb37c
// size: 2784 bytes
//

undefined4 sta_rx_pkt_allow(int param_1,int param_2,int param_3)

{
  byte bVar1;
  char cVar2;
  ushort uVar3;
  bool bVar4;
  int iVar5;
  int *piVar6;
  byte bVar7;
  undefined4 uVar8;
  void *__s1;
  byte *pbVar9;
  int iVar10;
  byte *pbVar11;
  undefined1 *puVar12;
  char *__s1_00;
  byte *pbVar13;
  int iVar14;
  uint uVar15;
  
  pbVar13 = *(byte **)(param_3 + 0x10);
  pbVar9 = *(byte **)(param_3 + 0x1c);
  if (3 < DebugLevel) {
    printk("-->%s():pRxBlk->wcid=%d\n","sta_rx_pkt_allow",*(undefined2 *)(param_3 + 0x4e));
  }
  if (param_1 == 0) {
    if (DebugLevel < 1) {
      return 0;
    }
    printk("%s(): pAd is null","sta_rx_pkt_allow");
    return 0;
  }
  uVar15 = (uint)*(ushort *)(param_3 + 0x4e);
  iVar5 = GetStaCfgByWdev(param_1,param_2);
  if (iVar5 == 0) {
    return 0;
  }
  if ((pbVar9[1] & 3) == 3) {
    if (*(char *)(param_1 + uVar15 * 0x14c0 + 0xa1e08) != '\0') {
      *(undefined4 *)(iVar5 + 0x213340) = jiffies;
      uVar3 = *(ushort *)(param_3 + 0x48);
      *(int *)(iVar5 + 0x21317c) = *(int *)(iVar5 + 0x21317c) + 1;
      *(uint *)(iVar5 + 0x213180) = (uint)uVar3 + *(int *)(iVar5 + 0x213180);
      __s1 = *(void **)(param_3 + 0x34);
      iVar14 = memcmp(__s1,(void *)(iVar5 + 0x1b),6);
      if (iVar14 == 0) {
        if (DebugLevel < 1) {
          return 0;
        }
        printk("ApCli receive a looping packet!\n");
        return 0;
      }
      iVar14 = *(int *)(param_3 + 0x38);
      pbVar11 = *(byte **)(iVar14 + 0xcc);
      if (((*pbVar11 & 1) == 0) || (iVar10 = memcmp(pbVar11 + 0xe,&DAT_0032f494,3), iVar10 != 0)) {
        bVar4 = false;
      }
      else if ((*(uint *)(iVar14 + 100) < 0x1a) ||
              (cVar2 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       [param_1 + 0xda], cVar2 == '\0')) {
        bVar4 = true;
      }
      else {
        __s1_00 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + param_1 + 0x101;
        do {
          iVar14 = memcmp(__s1_00,pbVar11 + 0x14,6);
          __s1_00 = __s1_00 + 0x5834;
          if (iVar14 == 0) {
            if (DebugLevel < 2) {
              return 0;
            }
            printk("recv pkt from own, drop!!!\n");
            return 0;
          }
        } while (__s1_00 !=
                 "printing range e2p value\n" + (uint)(byte)(cVar2 - 1) * 0x5834 + param_1 + 0xd);
        bVar4 = true;
      }
      if ((((&DAT_003678f8)[param_1] == '\x01') &&
          (iVar14 = memcmp((void *)(uVar15 * 0x14c0 + param_1 + 0xa1e0c),__s1,6), iVar14 != 0)) &&
         (piVar6 = (int *)MacTableLookup(param_1,__s1), piVar6 != (int *)0x0)) {
        if (*piVar6 != 0x20001) {
          bVar4 = false;
        }
        if (bVar4) {
          if ((*(ushort *)(piVar6 + 0x38) < 0x120) && (piVar6[0x3f] == 2)) {
            ZTE_Notify_Node_AD(0,piVar6);
          }
          __ZTE_STA_Assoc_Process(param_1,0x11,0,0,0,0,piVar6,"sta_rx_pkt_allow",0x16f5);
          mac_entry_delete(param_1,piVar6);
        }
      }
    }
    uVar8 = 0x1e;
    *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 0x800;
  }
  else {
    uVar8 = 0x18;
  }
  bVar7 = *pbVar13;
  if ((bVar7 & 0x80) == 0) {
    iVar14 = uVar15 * 0x14c0 + param_1;
    if (*(char *)(iVar14 + 0xa1e08) == '\0') {
      iVar10 = *(int *)(iVar14 + 0xa1d20);
      if (iVar10 != 2 && iVar10 != 0x40001) {
        if (DebugLevel < 1) {
          return 0;
        }
        printk("%s():  Not my bss! pRxInfo->MyBss=%d\n","sta_rx_pkt_allow",bVar7 >> 7);
        return 0;
      }
      bVar7 = pbVar9[1];
      if ((((bVar7 & 3) == 2) && (bVar1 = *pbVar9, (bVar1 & 0xc) == 8)) &&
         (iVar14 = memcmp((void *)(*(int *)(iVar14 + 0xa1d28) + 0x21),*(void **)(param_3 + 0x30),6),
         iVar14 == 0)) {
        if ((char)bVar1 < '\0') {
          pbVar11 = pbVar9 + 0x1a;
        }
        else {
          pbVar11 = pbVar9 + 0x18;
        }
        if ((bVar7 & 0x80) != 0) {
          if ((*(byte *)(param_3 + 99) < 0x40) &&
             ((*(uint *)(uVar15 * 0x14c0 + param_1 + 0xa1dd4) & 2) != 0)) {
            *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 4;
          }
          else {
            pbVar11 = pbVar11 + 4;
          }
        }
        if ((pbVar13[1] & 0x40) != 0) {
          pbVar11 = pbVar11 + 2;
        }
        iVar14 = memcmp(&SNAP_802_1H,pbVar11,6);
        if ((iVar14 == 0) || (iVar14 = memcmp(&SNAP_BRIDGE_TUNNEL,pbVar11,6), iVar14 == 0)) {
          pbVar11 = pbVar11 + 6;
        }
        iVar14 = memcmp(&EAPOL,pbVar11,2);
        if (iVar14 != 0) {
          if (DebugLevel < 1) {
            return 0;
          }
          printk("%s():  Not my bss! pRxInfo->MyBss=%d\n","sta_rx_pkt_allow",*pbVar13 >> 7);
          return 0;
        }
        *pbVar13 = *pbVar13 | 0x80;
        if (DebugLevel < 4) goto LAB_000cb410;
        printk("%s(): Hit EAP!\n","sta_rx_pkt_allow");
        iVar10 = *(int *)(uVar15 * 0x14c0 + param_1 + 0xa1d20);
      }
    }
    else {
      *pbVar13 = bVar7 | 0x80;
      iVar10 = *(int *)(iVar14 + 0xa1d20);
    }
  }
  else {
LAB_000cb410:
    iVar10 = *(int *)(uVar15 * 0x14c0 + param_1 + 0xa1d20);
  }
  if (((iVar10 == 2) && (*(int *)(param_2 + 0x14) == 2)) && ((*pbVar13 & 0x90) == 0x90)) {
    RTMPWakeUpWdev(param_1,param_2);
  }
  *(int *)(param_1 + 0xa39e64) = *(int *)(param_1 + 0xa39e64) + 1;
  if (*(char *)(param_2 + 0x8d8) == '\0') {
LAB_000cb59c:
    bVar7 = *pbVar9 >> 4;
  }
  else {
    bVar7 = *pbVar9 >> 4;
    if ((*(char *)(param_1 + 0x795089) != '\0') && ((bVar7 & 8) != 0)) {
      if (DebugLevel < 4) {
        if ((*(byte *)(*(int *)(param_3 + 0x1c) + 0x18) & 0x10) != 0) {
LAB_000cb490:
          *(undefined1 *)(param_1 + 0x794ca4) = 0;
          if (*(char *)(iVar5 + 0x2124c0) != '\0') goto LAB_000cb59c;
          RTMP_SLEEP_FORCE_AUTO_WAKEUP(param_1,iVar5);
        }
      }
      else {
        printk("bAPSDCapable\n");
        if ((*(byte *)(*(int *)(param_3 + 0x1c) + 0x18) & 0x10) != 0) {
          if (3 < DebugLevel) {
            printk("RxDone- Rcv EOSP frame, driver may fall into sleep\n");
          }
          goto LAB_000cb490;
        }
      }
      if ((((pbVar9[1] & 0x20) == 0) || (*(char *)(param_1 + 0x794ca4) == '\0')) || (DebugLevel < 3)
         ) goto LAB_000cb59c;
      printk("MoreData bit=1, Sending trigger frm again\n");
      bVar7 = *pbVar9 >> 4;
    }
  }
  if ((bVar7 & 4) == 0) {
    iVar14 = uVar15 * 0x14c0 + param_1;
    if (*(int *)(iVar14 + 0xa1d20) == 2 || *(int *)(iVar14 + 0xa1d20) == 0x40001) {
      if ((pbVar9[1] & 3) != 2) {
LAB_000cb560:
        *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 0x100;
        return uVar8;
      }
      iVar10 = RtmpOSNetDevIsUp(*(undefined4 *)
                                 (&DAT_0036db58 + param_1 + (uint)*(byte *)(iVar5 + 0xe) * 0x2137b0)
                               );
      if ((iVar10 == 1) &&
         (*(undefined4 *)(iVar5 + 0x213340) = jiffies, *(char *)(iVar14 + 0xa1e08) != '\x01')) {
        *(uint *)(iVar5 + 0x213180) = (uint)*(ushort *)(param_3 + 0x48) + *(int *)(iVar5 + 0x213180)
        ;
        *(int *)(iVar5 + 0x21317c) = *(int *)(iVar5 + 0x21317c) + 1;
        if (((*pbVar13 & 0x60) == 0) ||
           (iVar5 = ApCliHandleRxBroadcastFrame(param_1,param_3,param_1 + uVar15 * 0x14c0 + 0xa1d20)
           , iVar5 != 0)) {
          iVar14 = *(int *)(uVar15 * 0x14c0 + param_1 + 0xa1d28);
          iVar5 = memcmp((void *)(iVar14 + 0x1b),*(void **)(param_3 + 0x30),6);
          if (iVar5 != 0) goto LAB_000cb560;
          if (2 < DebugLevel) {
            printk("%s[%d]Drop: SA is from my CLI=%d\n\r","sta_rx_pkt_allow",0x180f,
                   *(undefined1 *)(iVar14 + 0xe));
            return 0;
          }
        }
      }
    }
    else if (*(char *)(iVar5 + 0x4060) == '\x01') {
      puVar12 = *(undefined1 **)(param_3 + 0x2c);
      iVar10 = memcmp(puVar12,(void *)(iVar5 + 0x413a),6);
      if (iVar10 == 0) {
        if (*(char *)(param_1 + 0x286285) != '\0') {
          return uVar8;
        }
        *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 0x100;
        if (*(short *)(param_3 + 0x4e) != *(short *)(iVar14 + 0xa1e00)) {
          printk(&_LC125,0x1842);
          dump_stack();
          return uVar8;
        }
        return uVar8;
      }
      if (0 < DebugLevel) {
        printk("%s():  Infra-No my BSSID(Peer=>%02x:%02x:%02x:%02x:%02x:%02x, My=>%02x:%02x:%02x:%02x:%02x:%02x)!\n"
               ,"sta_rx_pkt_allow",*puVar12,puVar12[1],puVar12[2],puVar12[3],puVar12[4],puVar12[5],
               *(undefined1 *)(iVar5 + 0x413a),*(undefined1 *)(iVar5 + 0x413b),
               *(undefined1 *)(iVar5 + 0x413c),*(undefined1 *)(iVar5 + 0x413d),
               *(undefined1 *)(iVar5 + 0x413e),*(undefined1 *)(iVar5 + 0x413f));
        return 0;
      }
    }
    else {
      puVar12 = *(undefined1 **)(param_3 + 0x30);
      iVar14 = memcmp(puVar12,&DAT_0057ff80 + param_1,6);
      if (iVar14 == 0) {
        if (*(char *)(param_1 + 0x286285) != '\0') {
          return uVar8;
        }
        if ((pbVar9[1] & 3) == 0) {
          *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 0x400;
          return uVar8;
        }
        return uVar8;
      }
      if (0 < DebugLevel) {
        printk("%s():  AdHoc-No my BSSID(Peer=>%02x:%02x:%02x:%02x:%02x:%02x, My=>%02x:%02x:%02x:%02x:%02x:%02x)!\n"
               ,"sta_rx_pkt_allow",*puVar12,puVar12[1],puVar12[2],puVar12[3],puVar12[4],puVar12[5],
               *(undefined1 *)(iVar5 + 0x212428),*(undefined1 *)(iVar5 + 0x212429),
               *(undefined1 *)(iVar5 + 0x21242a),*(undefined1 *)(iVar5 + 0x21242b),
               *(undefined1 *)(iVar5 + 0x21242c),*(undefined1 *)(iVar5 + 0x21242d));
        return 0;
      }
    }
  }
  else {
    if (3 < DebugLevel) {
      printk("%s():  No DATA!\n","sta_rx_pkt_allow");
    }
    wlan_dbg_radio_statistics_inc(0,0xd);
  }
  return 0;
}

