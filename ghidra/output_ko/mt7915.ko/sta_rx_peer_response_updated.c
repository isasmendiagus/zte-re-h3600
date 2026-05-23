// module: mt7915.ko
// function: sta_rx_peer_response_updated @ 0x7896c
// size: 3604 bytes
//

undefined4
sta_rx_peer_response_updated
          (int param_1,int param_2,void *param_3,int param_4,undefined4 param_5,undefined2 param_6)

{
  uint uVar1;
  char cVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  char *pcVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  undefined2 uVar12;
  byte *pbVar13;
  uint uVar14;
  undefined4 uVar15;
  undefined1 uVar16;
  undefined4 *__s1;
  int iVar17;
  int iVar18;
  byte *pbVar19;
  char *pcVar20;
  byte bVar21;
  undefined4 uVar22;
  undefined1 local_a4;
  int local_a0;
  undefined1 local_80;
  undefined1 local_7f;
  undefined1 local_7e;
  undefined1 local_7d;
  undefined1 local_7c;
  undefined4 local_76;
  undefined4 local_72;
  undefined4 local_6e;
  undefined2 local_6a;
  undefined1 auStack_68 [4];
  uint local_64;
  undefined1 auStack_4c [4];
  undefined1 local_48;
  undefined1 local_47;
  undefined1 local_46;
  undefined1 local_45;
  
  iVar4 = GetStaCfgByWdev();
  __s1 = (undefined4 *)((int)param_3 + 6);
  iVar5 = memcmp(__s1,(undefined4 *)(iVar4 + 0x212428),6);
  iVar6 = get_scan_tab_by_wdev(param_1,param_2);
  uVar7 = HcGetBandByWdev(param_2);
  pcVar8 = (char *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar7);
  local_a0 = GetAssociatedAPByWdev(param_1,param_2);
  local_48 = *(undefined1 *)(param_4 + 0x918);
  local_47 = *(undefined1 *)(param_4 + 0x919);
  local_46 = *(undefined1 *)(param_4 + 0x91a);
  local_45 = *(undefined1 *)(param_4 + 0x91b);
  uVar7 = rtmp_avg_rssi(param_1,auStack_4c);
  ApCliCheckPeerExistence
            (param_1,(int)param_3 + 0xc,*(undefined1 *)((int)param_3 + 0x2c),
             *(undefined1 *)((int)param_3 + 0x30));
  uVar3 = *(ushort *)(param_4 + 0x920);
  uVar9 = HcGetMaxStaNum(param_1);
  if (uVar3 < uVar9) {
    uVar9 = (uint)*(ushort *)(param_4 + 0x920);
    iVar17 = uVar9 * 0x14c0;
    local_a0 = param_1 + iVar17 + 0xa1d20;
    if (local_a0 != 0) {
      iVar17 = *(int *)(param_1 + iVar17 + 0xa1d20);
      if (iVar17 == 2 || iVar17 == 0x40001) {
        *(undefined4 *)(iVar4 + 0x213340) = *(undefined4 *)(param_1 + 0x7960e8);
        AdjustBwToSyncAp(param_1,param_3,iVar4);
        ApCliCheckConConnectivity(param_1,iVar4,param_3);
        bVar21 = *(byte *)(iVar4 + 0x41ac);
        iVar17 = PeerBeaconAndProbeRspSanity2
                           (param_1,param_4,*(undefined4 *)(param_4 + 0x908),auStack_68,&local_76);
        if (iVar17 == 1) {
          uVar12 = (undefined2)local_64;
          if (0x37a < ((local_64 & 0xffff) - 10 & 0xffff)) {
            uVar12 = 900;
          }
          *(undefined2 *)(param_1 + 0x7956a2) = uVar12;
        }
        if ((*(uint *)((int)param_3 + 0xa8) & 2) != 0) {
          uVar14 = *(byte *)((int)param_3 + 0xf8) & 3;
          if (((bVar21 & 3) != uVar14) ||
             (((uint)*(byte *)((int)param_3 + 0xf8) << 0x1d) >> 0x1f !=
              ((uint)bVar21 << 0x1d) >> 0x1f)) {
            *(byte *)(iVar4 + 0x41ac) = *(byte *)(iVar4 + 0x41ac) & 0xfc | (byte)uVar14;
            *(byte *)(iVar4 + 0x41ac) =
                 *(byte *)(iVar4 + 0x41ac) & 0xfb |
                 (byte)((((uint)*(byte *)((int)param_3 + 0xf8) << 0x1d) >> 0x1f) << 2);
            uVar1 = 1 << (*(byte *)((int)param_3 + 0xf8) & 3);
            *(uint *)(iVar4 + 0x8dc) = uVar1;
            if ((*(byte *)(iVar4 + 0x41ac) & 4) != 0) {
              *(uint *)(iVar4 + 0x8dc) = uVar1 | 0x80;
            }
            if (0xe < *(byte *)(iVar4 + 0x1a)) {
              *(uint *)(iVar4 + 0x8dc) = *(uint *)(iVar4 + 0x8dc) & 0xffffffdf;
            }
            puVar10 = (undefined4 *)wlan_operate_get_addht(iVar4);
            if (puVar10 != (undefined4 *)0x0) {
              uVar22 = *(undefined4 *)(iVar4 + 0x41ae);
              uVar11 = *(undefined4 *)(iVar4 + 0x41b2);
              uVar15 = *(undefined4 *)(iVar4 + 0x41b6);
              *puVar10 = *(undefined4 *)(iVar4 + 0x41aa);
              puVar10[1] = uVar22;
              puVar10[2] = uVar11;
              puVar10[3] = uVar15;
              puVar10[4] = *(undefined4 *)(iVar4 + 0x41ba);
              *(undefined2 *)(puVar10 + 5) = *(undefined2 *)(iVar4 + 0x41be);
            }
            HW_SET_PROTECT(param_1,iVar4,0,0,0);
            if (1 < DebugLevel) {
              printk("SYNC - AP changed N OperaionMode to %d, my protection to %d\n",uVar14,
                     *(undefined4 *)(iVar4 + 0x8dc));
            }
          }
        }
      }
      if (*(char *)((int)param_3 + 0x31) != '\0') {
        ApCliPeerCsaAction(param_1,*(undefined4 *)(uVar9 * 0x14c0 + param_1 + 0xa1d28),param_3);
      }
    }
  }
  if ((*(uint *)((int)param_3 + 0xa8) & 2) == 0) {
    uVar16 = *(undefined1 *)((int)param_3 + 0x30);
  }
  else {
    uVar16 = *(undefined1 *)((int)param_3 + 0xf6);
    *(undefined1 *)((int)param_3 + 0x30) = uVar16;
  }
  if ((*(uint *)((int)param_3 + 0xa8) & 0x81) != 0) {
    *(uint *)((int)param_3 + 0xa8) = *(uint *)((int)param_3 + 0xa8) | 1;
  }
  iVar17 = BssTableSearchWithSSID
                     (iVar4 + 0x4228,__s1,(int)param_3 + 0xc,*(undefined1 *)((int)param_3 + 0x2c),
                      uVar16);
  local_a4 = (undefined1)uVar7;
  if ((iVar17 == -1) &&
     (iVar17 = BssTableSetEntry(param_1,param_2,iVar4 + 0x4228,param_3,uVar7,param_6,param_5),
     iVar17 != -1)) {
    iVar17 = iVar17 * 0xaf4;
    memmove((void *)(iVar4 + iVar17 + 0x4726),(void *)(param_4 + 0x18),4);
    memmove((void *)(iVar4 + iVar17 + 0x472a),(void *)(param_4 + 0x910),4);
    memmove((void *)(iVar4 + iVar17 + 0x472e),(void *)(param_4 + 0x910),4);
    *(undefined1 *)(iVar4 + iVar17 + 0x42a1) = local_a4;
    memmove((void *)(iVar4 + iVar17 + 0x4230),param_3,6);
  }
  iVar17 = BssTableSearch(iVar6,__s1,*(undefined1 *)((int)param_3 + 0x30));
  if (iVar17 == -1) {
    iVar17 = BssTableSetEntry(param_1,param_2,iVar6,param_3,uVar7,param_6,param_5);
    if (iVar17 == -1) {
      return 0;
    }
    iVar18 = iVar17 * 0xaf4;
    memmove((void *)(iVar6 + iVar18 + 0x4fe),(void *)(param_4 + 0x18),4);
    memmove((void *)(iVar6 + iVar18 + 0x502),(void *)(param_4 + 0x910),4);
    memmove((void *)(iVar6 + iVar18 + 0x506),(void *)(param_4 + 0x910),4);
    uVar9 = (uint)*(byte *)(param_4 + 0x91e) % 10;
    uVar16 = (undefined1)uVar9;
    if (uVar9 == 0) {
      uVar16 = 0xfb;
    }
    *(undefined1 *)(iVar6 + iVar18 + 0x8b) = uVar16;
    memmove((void *)(iVar17 * 0xaf4 + iVar6 + 8),param_3,6);
  }
  uVar7 = jiffies;
  iVar18 = iVar17 * 0xaf4 + iVar6;
  *(undefined1 *)(iVar18 + 0x79) = local_a4;
  *(undefined4 *)(iVar18 + 0xc4) = uVar7;
  if (iVar5 != 0) {
    if ((*(uint *)(param_1 + 0x795124) & 2) == 0) {
      return 1;
    }
    if (*(int *)(param_2 + 0x174) != *(int *)(iVar18 + 0xd0)) {
      return 0;
    }
    if (*(int *)(param_2 + 0x2c) != *(int *)(iVar18 + 0xcc)) {
      return 0;
    }
    pbVar19 = (byte *)(iVar4 + 0x212427);
    pbVar13 = (byte *)((int)param_3 + 5);
    while( true ) {
      pbVar13 = pbVar13 + 1;
      pbVar19 = pbVar19 + 1;
      if (*pbVar19 < *pbVar13) break;
      if (*pbVar13 < *pbVar19) {
        return 1;
      }
      if (pbVar19 == (byte *)(iVar4 + 0x21242d)) {
        return 1;
      }
    }
    if (2 < DebugLevel) {
      printk("SYNC - merge to the IBSS with bigger BSSID=%02x:%02x:%02x:%02x:%02x:%02x\n",
             *(undefined1 *)((int)param_3 + 6),*(undefined1 *)((int)param_3 + 7),
             *(undefined1 *)((int)param_3 + 8),*(undefined1 *)((int)param_3 + 9),
             *(undefined1 *)((int)param_3 + 10),*(undefined1 *)((int)param_3 + 0xb));
    }
    AsicDisableSync(param_1,0);
    *(undefined4 *)(iVar4 + 0x212428) = *__s1;
    *(undefined2 *)(iVar4 + 0x21242c) = *(undefined2 *)((int)param_3 + 10);
    iVar5 = wdev_do_linkdown(param_2);
    if ((iVar5 != 1) && (0 < DebugLevel)) {
      printk("%s(): linkdown fail!!\n","sta_rx_peer_response_updated");
    }
    iVar5 = wdev_do_linkup(param_2,local_a0);
    if ((iVar5 != 1) && (0 < DebugLevel)) {
      printk("%s(): linkup fail!!\n","sta_rx_peer_response_updated");
    }
    iVar5 = wdev_do_conn_act(param_2,local_a0);
    if ((iVar5 != 1) && (0 < DebugLevel)) {
      printk("%s(): connect fail!!\n","sta_rx_peer_response_updated");
    }
  }
  local_80 = 0;
  iVar5 = PeerBeaconAndProbeRspSanity2
                    (param_1,param_4,*(undefined4 *)(param_4 + 0x908),&local_76,&local_80);
  if (iVar5 == 1) {
    UpdateBssScanParm(param_1,local_76,local_72,local_6e,local_6a);
    *(undefined1 *)(iVar4 + 0x213255) = local_80;
  }
  __memzero(&local_7f,9);
  *(undefined2 *)(iVar4 + 0x212456) = *(undefined2 *)((int)param_3 + 0x2e);
  *(undefined1 *)(iVar4 + 0x212455) = *(undefined1 *)((int)param_3 + 0x38);
  uVar16 = *(undefined1 *)((int)param_3 + 0x37);
  *(undefined4 *)(iVar4 + 0x21245c) = uVar7;
  *(undefined1 *)(iVar4 + 0x212454) = uVar16;
  local_7f = *(undefined1 *)(param_4 + 0x918);
  local_7e = *(undefined1 *)(param_4 + 0x919);
  local_7d = *(undefined1 *)(param_4 + 0x91a);
  local_7c = *(undefined1 *)(param_4 + 0x91b);
  if ((*(uint *)(iVar4 + 0x212464) & (uint)(local_a0 != 0)) != 0) {
    Update_Snr_Sample(param_1,local_a0 + 0x108,&local_7f,0,0);
  }
  bVar21 = 0;
  Update_Snr_Sample(param_1,iVar4 + 0x2131c8,&local_7f,0,0);
  Update_Rssi_Sample(param_1,iVar4 + 0x2137a8,iVar4 + 0x2137ac,
                     "SetPartProfileParameters"[param_1 + 0x18] & 0xf,&local_7f);
  if (((*(char *)(param_1 + 0x795074) == '\x01') && (*(char *)((int)param_3 + 0x31) != '\0')) &&
     (*(char *)((int)param_3 + 0x30) != *(char *)((int)param_3 + 0x31))) {
    *(undefined1 *)(param_2 + 0x1a) = 1;
    wlan_operate_set_prim_ch(param_2);
    LinkDown(param_1,0,iVar4,0);
    MlmeQueueInit(param_1,param_1 + 0x7960f8);
    BssTableInit(iVar6);
    RtmpusecDelay(1000000);
    if (pcVar8[0x49c] != 0) {
      cVar2 = *pcVar8;
      pcVar20 = pcVar8;
      while (cVar2 != *(char *)((int)param_3 + 0x31)) {
        bVar21 = bVar21 + 1;
        if (bVar21 == pcVar8[0x49c]) goto LAB_000793e4;
        pcVar20 = pcVar20 + 0x14;
        cVar2 = *pcVar20;
      }
      *(char *)(iVar17 * 0xaf4 + iVar6 + 0x14) = *(char *)((int)param_3 + 0x31);
      *(undefined1 *)(param_2 + 0x1a) = *(undefined1 *)((int)param_3 + 0x31);
      wlan_operate_set_prim_ch(param_2);
      if (2 < DebugLevel) {
        printk("PeerBeacon - STA receive channel switch announcement IE (New Channel =%d)\n",
               *(undefined1 *)((int)param_3 + 0x31));
      }
      if (bVar21 < (byte)pcVar8[0x49c]) goto LAB_00078c80;
    }
LAB_000793e4:
    if (-1 < DebugLevel) {
      printk("PeerBeacon(can not find New Channel=%d in ChannelList[%d]\n",
             *(undefined1 *)(iVar4 + 0x1a));
    }
  }
LAB_00078c80:
  if (*(int *)(param_2 + 0x12f4) == 0) {
    if (*(int *)(param_2 + 0x2c) == 1) {
      uVar9 = (uint)(*(int *)(param_2 + 0x174) != 1) << 4;
    }
    else {
      uVar9 = 0x10;
    }
    if (((uVar9 ^ *(ushort *)((int)param_3 + 0x34)) & 0x10) != 0) {
      if (2 < DebugLevel) {
        if (*(int *)(param_2 + 0x2c) == 1) {
          uVar7 = 0;
          if (*(int *)(param_2 + 0x174) != 1) {
            uVar7 = 1;
          }
        }
        else {
          uVar7 = 1;
        }
        printk("%s:AP privacy:%x is differenct from STA privacy:%x\n","sta_rx_peer_response_updated"
               ,((uint)*(ushort *)((int)param_3 + 0x34) << 0x1b) >> 0x1f,uVar7);
      }
      if ((*(uint *)(iVar4 + 0x212464) & 1) != 0) {
        LinkDown(param_1,0,iVar4,0);
        BssTableInit(iVar6);
      }
      return 0;
    }
  }
  if (*(char *)((int)param_3 + 0x3c) == -1) {
    *(undefined1 *)(param_1 + 0x794cd8) = *(undefined1 *)(param_1 + 0x795041);
    *(undefined1 *)(param_1 + 0x794cd9) = *(undefined1 *)(param_1 + 0x795042);
  }
  else {
    ChangeToCellPowerLimit(param_1);
  }
  if ((*(uint *)(iVar4 + 0x212464) & 1) != 0) {
    uVar9 = ((uint)*(ushort *)((int)param_3 + 0x34) << 0x15) >> 0x1f;
    bVar21 = *(byte *)(iVar4 + 0x41ac);
    if (uVar9 != (*(uint *)(iVar4 + 0x212464) << 0x1c) >> 0x1f) {
      HW_SET_SLOTTIME(param_1,uVar9,*(undefined1 *)(param_2 + 0x1a),param_2);
    }
    uVar9 = 1;
    if (*(int *)(param_1 + 0x79506c) != 1) {
      if (*(int *)(param_1 + 0x79506c) == 0) {
        uVar9 = *(byte *)((int)param_3 + 0x36) & 2;
        if ((*(byte *)((int)param_3 + 0x36) & 2) != 0) {
          uVar9 = 1;
        }
      }
      else {
        uVar9 = 0;
      }
    }
    if ((*(byte *)(param_2 + 0x1a) < 0xf) &&
       (uVar14 = *(uint *)(param_1 + 0x795124), uVar9 != (uVar14 << 0x1d) >> 0x1f)) {
      if (uVar9 == 0) {
        *(uint *)(param_1 + 0x795124) = uVar14 & 0xfffffffb;
        uVar14 = *(uint *)(param_2 + 0x8dc) & 0xffffffdf;
      }
      else {
        *(uint *)(param_1 + 0x795124) = uVar14 | 4;
        uVar14 = *(uint *)(param_2 + 0x8dc) | 0x20;
      }
      *(uint *)(param_2 + 0x8dc) = uVar14;
      HW_SET_PROTECT(param_1,param_2,0,0,0);
      if (1 < DebugLevel) {
        printk("SYNC - AP changed B/G protection to %d\n",uVar9);
      }
    }
    if ((*(uint *)((int)param_3 + 0xa8) & 2) != 0) {
      uVar9 = *(byte *)((int)param_3 + 0xf8) & 3;
      if (((bVar21 & 3) != uVar9) ||
         (((uint)*(byte *)((int)param_3 + 0xf8) << 0x1d) >> 0x1f != ((uint)bVar21 << 0x1d) >> 0x1f))
      {
        bVar21 = *(byte *)(iVar4 + 0x41ac);
        *(byte *)(iVar4 + 0x41ac) = bVar21 & 0xfc | (byte)uVar9;
        iVar5 = (uint)*(byte *)((int)param_3 + 0xf8) << 0x1d;
        *(byte *)(iVar4 + 0x41ac) = bVar21 & 0xf8 | (byte)uVar9 | (char)(iVar5 >> 0x1f) * -4;
        if (iVar5 < 0) {
          uVar14 = *(uint *)(param_2 + 0x8dc) | 0x80;
        }
        else {
          uVar14 = *(uint *)(param_2 + 0x8dc) & 0xffffff7f;
        }
        *(uint *)(param_2 + 0x8dc) = uVar14;
        HW_SET_PROTECT(param_1,param_2,0,0,0);
        if (2 < DebugLevel) {
          printk("SYNC - AP changed N OperaionMode to %d\n",uVar9);
        }
      }
    }
    uVar9 = *(uint *)(param_1 + 0x795124);
    if (((uVar9 & 0x10) != 0) && ((*(byte *)((int)param_3 + 0x36) & 4) != 0)) {
      MlmeSetTxPreamble(param_1,0);
      if (2 < DebugLevel) {
        printk("SYNC - AP forced to use LONG preamble\n");
      }
      uVar9 = *(uint *)(param_1 + 0x795124);
    }
    if ((((uVar9 & 0x100) != 0) && (*(char *)((int)param_3 + 0x50) == '\x01')) &&
       (*(char *)((int)param_3 + 0x56) != *(char *)(iVar4 + 0x41ec))) {
      if (2 < DebugLevel) {
        printk("SYNC - AP change EDCA parameters(from %d to %d)\n");
      }
      HcAcquiredEdca(param_1,param_2,(int)param_3 + 0x50);
      HcSetEdca(param_2);
      *(undefined1 *)(iVar4 + 0x41ec) = *(undefined1 *)((int)param_3 + 0x56);
    }
    memmove((void *)(param_1 + 0x795114),(void *)((int)param_3 + 0x74),8);
    memmove((void *)(param_1 + 0x79507e),(void *)((int)param_3 + 0x7c),5);
    if (((*(uint *)(iVar4 + 0x212464) & 1) != 0) &&
       (iVar5 = AdjustBwToSyncAp(param_1,param_3,param_2), iVar5 != 0)) {
      *(undefined1 *)(param_1 + 0x7956b5) = 0;
      TriEventInit(param_1);
      BuildEffectedChannelList(param_1,param_2);
    }
    if (((local_a0 != 0) != 0) &&
       ((*(char *)(iVar4 + 0x41de) != *(char *)(local_a0 + 0xd20) ||
        (*(char *)(local_a0 + 0xd21) != *(char *)(iVar4 + 0x41df))))) {
      *(char *)(iVar4 + 0x41de) = *(char *)(local_a0 + 0xd20);
      *(undefined1 *)(iVar4 + 0x41df) = *(undefined1 *)(local_a0 + 0xd21);
      __memzero(auStack_68,0x1c);
      local_64 = 1;
      RAParamUpdate(param_1,local_a0,auStack_68);
    }
  }
  return 1;
}

