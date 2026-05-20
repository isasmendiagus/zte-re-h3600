// module: mt7915.ko
// function: sync_fsm_peer_response_scan_action @ 0x109988
// size: 1764 bytes
//

void sync_fsm_peer_response_scan_action(int param_1,byte *param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  byte *pbVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  undefined4 uVar9;
  byte *pbVar10;
  undefined1 uVar11;
  undefined4 *puVar12;
  uint uVar13;
  undefined4 *puVar14;
  int iVar15;
  int local_74;
  undefined1 local_67;
  short local_66;
  int local_64;
  void *local_60;
  undefined1 auStack_5a [14];
  undefined1 auStack_4c [4];
  byte local_48;
  byte local_47;
  byte local_46;
  byte local_45;
  
  puVar14 = *(undefined4 **)(param_2 + 0x92c);
  local_64 = 0;
  local_60 = (void *)0x0;
  if (puVar14 == (undefined4 *)0x0) {
    if (DebugLevel < 3) {
      return;
    }
    printk("Band:%d, CH:%d, STATE: %s\n",0,param_2[0x91f],
           *(undefined4 *)(SYNC_FSM_STATE_STR + *(int *)(param_1 + 0x829300) * 4));
    return;
  }
  uVar3 = HcGetBandByWdev(puVar14);
  pbVar4 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar3);
  pcVar5 = (char *)get_scan_ctrl_by_wdev(param_1,puVar14);
  iVar6 = get_scan_tab_by_wdev(param_1,puVar14);
  if (puVar14[5] == 2) {
    iVar15 = GetStaCfgByWdev(param_1,puVar14);
    if (iVar15 == 0) {
      return;
    }
  }
  else {
    iVar15 = 0;
  }
  puVar12 = *(undefined4 **)(pcVar5 + 0xaf5d0);
  if ((puVar12 != (undefined4 *)0x0 && puVar14 != puVar12) && (3 < DebugLevel)) {
    printk("[%s] <==============================================> [%s]\n",*puVar12,*puVar14);
  }
  os_alloc_mem(param_1,&local_60,0x180);
  if (local_60 == (void *)0x0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: Alloc memory for ie_list fail!!!\n","sync_fsm_peer_response_scan_action");
    return;
  }
  __memzero(local_60,0x180);
  os_alloc_mem(0,&local_64,0x400);
  iVar2 = local_64;
  if (local_64 == 0) {
    if (DebugLevel < 0) goto LAB_00109ad8;
    printk("%s: Allocate memory fail!!!\n","sync_fsm_peer_response_scan_action");
  }
  else {
    *(undefined1 *)(local_64 + 1) = 0;
    iVar7 = PeerBeaconAndProbeRspSanity
                      (param_1,puVar14,param_2,*(undefined4 *)(param_2 + 0x908),param_2[0x91f],
                       local_60,&local_66,local_64,0,0);
    if (iVar7 == 0) {
      local_74 = 0x81;
    }
    else {
      BssTableSearch(iVar6,(int)local_60 + 6,*(undefined1 *)((int)local_60 + 0x30));
      MacTableLookup(param_1,local_60);
      local_47 = param_2[0x919];
      local_46 = param_2[0x91a];
      local_48 = param_2[0x918];
      local_45 = param_2[0x91b];
      local_74 = rtmp_avg_rssi(param_1,auStack_4c);
      if (*(byte *)((int)local_60 + 0x30) < 0xf) {
        uVar9 = 1;
      }
      else {
        uVar9 = 2;
      }
      uVar9 = HcGetChannelByRf(param_1,uVar9);
      if ((*(char *)((int)local_60 + 0x30) == pcVar5[2]) || (*(char *)(param_1 + 0x795941) != '\0'))
      {
        if ((*(char *)(param_1 + 0x795651) < local_74) &&
           ((*(byte *)((int)local_60 + 0xdd) & 0x40) != 0)) {
          if (*pcVar5 == '\x04') {
            iVar7 = puVar14[5];
            if (((*(byte *)(param_1 + 0x286294) & 3) == 3) && (iVar7 == 2)) {
              if (0 < DebugLevel) {
                printk("%s:Ignore BW 40->20\n","sync_fsm_peer_response_scan_action");
              }
              goto LAB_00109c68;
            }
          }
          else {
            iVar7 = puVar14[5];
          }
          if (iVar7 == 1) {
            Handle_BSS_Width_Trigger_Events(param_1,uVar9);
          }
        }
LAB_00109c68:
        if ((*(uint *)((int)local_60 + 0xa8) & 0x81) != 0) {
          *(uint *)((int)local_60 + 0xa8) = *(uint *)((int)local_60 + 0xa8) | 1;
        }
        if ((iVar15 != 0) &&
           ((iVar7 = RtmpOSNetDevIsUp(*(undefined4 *)
                                       (&DAT_0036db58 +
                                       param_1 + (uint)*(byte *)((int)puVar14 + 0xe) * 0x2137b0)),
            iVar7 == 1 || ((*(uint *)(iVar15 + 0x212464) & 1) != 0)))) {
          build_trigger_event_table(param_1,param_2,local_60);
        }
        iVar15 = BssTableSetEntry(param_1,puVar14,iVar6,local_60,local_74,local_66,iVar2);
        if (((*(char *)(param_1 + 0x79564e) == '\x01') &&
            (*(byte *)((int)local_60 + 0x30) - 1 < 0xe)) && (pbVar4[0x49c] != 0)) {
          uVar13 = 0;
          bVar1 = *pbVar4;
          pbVar10 = pbVar4;
          while ((uint)bVar1 != (uint)*(byte *)((int)local_60 + 0x30)) {
            uVar13 = uVar13 + 1;
            if (pbVar4[0x49c] == uVar13) goto LAB_00109d08;
            pbVar10 = pbVar10 + 0x14;
            bVar1 = *pbVar10;
          }
          if (pbVar4[uVar13 * 0x14 + 1] == 1) {
            PeerBeaconAndProbeRspSanity2
                      (param_1,param_2,*(undefined4 *)(param_2 + 0x908),auStack_5a,&local_67);
            TriEventTableSetEntry
                      (param_1,param_1 + 0x7956b8,(int)local_60 + 6,(int)local_60 + 0xdc,
                       *(uint *)((int)local_60 + 0xa8) & 1,local_67,
                       *(undefined1 *)((int)local_60 + 0x30));
          }
        }
LAB_00109d08:
        if (iVar15 != -1) {
          iVar7 = iVar15 * 0xaf4;
          memmove((void *)(iVar6 + iVar7 + 0x4fe),param_2 + 0x18,4);
          memmove((void *)(iVar6 + iVar7 + 0x502),param_2 + 0x910,4);
          memmove((void *)(iVar6 + iVar7 + 0x506),param_2 + 0x910,4);
          uVar11 = (undefined1)((uint)param_2[0x91e] % 10);
          if ((uint)param_2[0x91e] % 10 == 0) {
            uVar11 = 0xfb;
          }
          *(undefined1 *)(iVar6 + iVar7 + 0x8b) = uVar11;
          memmove((void *)(iVar6 + iVar15 * 0xaf4 + 8),local_60,6);
          if (((*param_2 & 0xf0) == 0x50) && (local_66 != 0)) {
            iVar7 = iVar6 + iVar15 * 0xaf4;
            *(undefined2 *)(iVar7 + 0x4f6) = 0;
            if (*(int *)(iVar7 + 0x4f8) != 0) {
              *(short *)(iVar7 + 0x4f6) = local_66;
              RTMPZeroMemory(*(undefined4 *)(iVar7 + 0x4f8),0x400);
              RTMPMoveMemory(*(undefined4 *)(iVar7 + 0x4f8),iVar2,local_66);
            }
          }
          iVar6 = iVar15 * 0xaf4 + iVar6;
          *(undefined1 *)(iVar6 + 0x6ca) = 0;
          if ((*(char *)((int)local_60 + 0x95) != '\0') && (*(char *)((int)local_60 + 0x96) != '\0')
             ) {
            *(undefined1 *)(iVar6 + 0x6ca) = 1;
          }
        }
      }
    }
    if ((puVar14[5] == 1) && (*(char *)((int)local_60 + 0x30) == (&DAT_0036b860)[param_1])) {
      piVar8 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,uVar3);
      iVar6 = AutoChBssSearchWithSSID
                        (param_1,(int)local_60 + 6,(int)local_60 + 0xc,
                         *(undefined1 *)((int)local_60 + 0x2c),*(undefined1 *)((int)local_60 + 0x30)
                         ,puVar14);
      if (iVar6 == -1) {
        iVar6 = *piVar8 + (uint)(byte)(&DAT_0036b861)[param_1] * 4;
        *(int *)(iVar6 + 0xf0) = *(int *)(iVar6 + 0xf0) + 1;
      }
      AutoChBssInsertEntry
                (param_1,(int)local_60 + 6,(int)local_60 + 0xc,*(undefined1 *)((int)local_60 + 0x2c)
                 ,*(undefined1 *)((int)local_60 + 0x30),*(undefined1 *)((int)local_60 + 0xa3),
                 (int)(char)local_74,puVar14);
    }
  }
  if (local_64 != 0) {
    os_free_mem();
  }
LAB_00109ad8:
  if (local_60 != (void *)0x0) {
    os_free_mem();
  }
  return;
}

