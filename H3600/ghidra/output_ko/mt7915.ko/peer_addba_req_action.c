// module: mt7915.ko
// function: peer_addba_req_action @ 0xa6e40
// size: 980 bytes
//

void peer_addba_req_action(int param_1,int param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  ushort *puVar5;
  byte bVar6;
  uint uVar7;
  undefined1 uVar8;
  undefined2 uVar9;
  int iVar10;
  uint uVar11;
  int *piVar12;
  undefined4 uVar13;
  void *local_3c;
  ushort local_38;
  undefined4 local_36;
  undefined2 local_32;
  undefined1 local_30;
  undefined1 local_2f;
  byte local_2e;
  byte local_2d;
  undefined2 local_2c;
  undefined2 local_2a;
  
  if (2 < DebugLevel) {
    printk("%s ==> (Wcid = %d)\n","peer_addba_req_action",*(undefined2 *)(param_2 + 0x920));
  }
  if (param_1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s():Unexpected pAd NULL!\n","peer_addba_req_action");
    }
  }
  else {
    puVar5 = (ushort *)(param_2 + 0x920);
    uVar1 = *puVar5;
    uVar2 = HcGetMaxStaNum(param_1);
    if (uVar1 < uVar2) {
      uVar2 = (uint)*puVar5;
      iVar4 = uVar2 * 0x14c0 + param_1;
      if (*(int *)(iVar4 + 0xa1d20) == 0x20001) {
        if (*(int *)(iVar4 + 0xa1e1c) != 2) {
          if (DebugLevel < 0) {
            return;
          }
          printk("peer entry is not in association state\n");
          return;
        }
        if (*(char *)(iVar4 + 0xa2282) == '\x01') {
          if (*(char *)(param_1 + uVar2 * 0x620 + 0x2f762) != '\x01') {
            if (DebugLevel < 0) {
              return;
            }
            printk("%s: PMF Connection IGNORE THIS PKT DUE TO NOT IN PORTSECURED\n",
                   "peer_addba_req_action");
            return;
          }
          if ((*(byte *)(param_2 + 1) & 0x40) == 0) {
            if (DebugLevel < 0) {
              return;
            }
            printk("%s: PMF CONNECTION BUT RECV WEP=0 ACTION, DROP FRAME\n","peer_addba_req_action")
            ;
            return;
          }
        }
      }
      iVar4 = PeerAddBAReqActionSanity(param_1,param_2,*(undefined4 *)(param_2 + 0x908));
      if (iVar4 == 0) {
        uVar8 = 1;
        bVar6 = 0;
        uVar9 = 0;
      }
      else {
        iVar10 = uVar2 * 0x14c0 + param_1;
        piVar12 = (int *)(iVar10 + 0xa1d28);
        iVar4 = wlan_config_get_ba_decline(*(undefined4 *)(iVar10 + 0xa1d28));
        if (iVar4 == 0) {
          if (*(byte *)(iVar10 + 0xa1ddf) < 0x40) {
            uVar8 = 0x25;
            bVar6 = 0;
            uVar9 = 0;
          }
          else {
            uVar3 = wlan_config_get_ba_rx_wsize(*piVar12);
            uVar7 = (uint)*(byte *)(param_2 + 0x1c) << 2 | (uint)(*(byte *)(param_2 + 0x1b) >> 6);
            iVar4 = wlan_config_get_ppdu_caps(*piVar12);
            iVar10 = *piVar12;
            if ((*(ushort *)(iVar10 + 0x18) & 0x1c0) == 0) {
              uVar1 = *(ushort *)(iVar4 + 8);
            }
            else {
              uVar1 = *(ushort *)(iVar4 + 4);
            }
            uVar11 = (uint)uVar1;
            if (uVar3 <= uVar1) {
              uVar11 = uVar3;
            }
            if (uVar7 == 0) {
              uVar7 = 0x40;
            }
            else if (((*(uint *)(uVar2 * 0x14c0 + param_1 + 0xa1d84) & 0x18) == 0) && (0x3f < uVar7)
                    ) {
              uVar7 = 0x40;
            }
            uVar3 = uVar11 & 0xffff;
            if (uVar7 <= (uVar11 & 0xffff)) {
              uVar3 = uVar7;
            }
            if (uVar3 == 0) {
              uVar3 = 1;
            }
            uVar9 = (undefined2)uVar3;
            if (2 < DebugLevel) {
              printk("[Peer is Originator]recv. add ba req, (peer:ori)tx_ba_wsize=%d, (our:rec)rx_ba_wsize=%d \n"
                     ,uVar7,uVar3);
              iVar10 = *(int *)(uVar2 * 0x14c0 + param_1 + 0xa1d28);
            }
            iVar4 = wlan_config_get_ppdu_caps(iVar10);
            bVar6 = 0;
            if (*(char *)(iVar4 + 0x11) != '\0') {
              bVar6 = *(byte *)(param_2 + 0x1b) & 1;
            }
            iVar4 = ba_resrc_rec_add(param_1,*(undefined2 *)(uVar2 * 0x14c0 + param_1 + 0xa1e00),
                                     ((uint)*(byte *)(param_2 + 0x1b) << 0x1a) >> 0x1c,
                                     *(undefined2 *)(param_2 + 0x1d),uVar3);
            if (iVar4 == 0) {
              uVar8 = 0x26;
            }
            else {
              uVar8 = 0;
            }
          }
        }
        else {
          bVar6 = 0;
          uVar8 = 0x25;
          uVar9 = 0;
        }
      }
      os_alloc_mem(0,&local_3c,0x930);
      if (local_3c != (void *)0x0) {
        __memzero(&local_38,0x10);
        local_36 = *(undefined4 *)(param_2 + 10);
        local_38 = *puVar5;
        local_2f = *(undefined1 *)(param_2 + 0x1a);
        local_32 = *(undefined2 *)(param_2 + 0xe);
        local_2d = (byte)(((uint)*(byte *)(param_2 + 0x1b) << 0x1a) >> 0x1c);
        local_2a = 0;
        local_30 = uVar8;
        local_2e = bVar6;
        local_2c = uVar9;
        __memzero(local_3c,0x930);
        *(ushort *)((int)local_3c + 0x920) = *puVar5;
        uVar13 = *(undefined4 *)(param_2 + 0x92c);
        *(undefined4 *)((int)local_3c + 0x908) = 0x10;
        *(undefined4 *)((int)local_3c + 0x92c) = uVar13;
        memmove(local_3c,&local_38,0x10);
        mlme_send_addba_resp(param_1,local_3c);
        os_free_mem(local_3c);
        return;
      }
      if (-1 < DebugLevel) {
        printk("%s():alloc memory failed!\n","peer_addba_req_action");
      }
    }
  }
  return;
}

