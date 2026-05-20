// module: mt7915.ko
// function: indicate_802_11_pkt @ 0xc9578
// size: 1236 bytes
//

void indicate_802_11_pkt(int param_1,int param_2,uint param_3)

{
  undefined1 uVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  undefined2 uVar8;
  int iVar9;
  ushort uVar10;
  void *pvVar11;
  undefined1 *local_44;
  void *local_40;
  void *local_3c;
  undefined1 auStack_36 [6];
  undefined1 auStack_30 [6];
  undefined1 local_2a;
  undefined1 local_29;
  
  uVar1 = *(undefined1 *)(param_1 + 0x286285);
  iVar9 = *(int *)(param_2 + 0x38);
  if (0x67 < param_3) {
    if (-1 < DebugLevel) {
      printk("%s():invalid wdev_idx(%d)!\n","indicate_802_11_pkt");
    }
    *(int *)(param_1 + 0x9dcd8) = *(int *)(param_1 + 0x9dcd8) + 1;
    RTMPFreeNdisPacket(param_1,iVar9);
    return;
  }
  iVar3 = FUN_000c53fc();
  if (iVar3 == 0) {
    if (1 < DebugLevel) {
      printk("%s:drop packet by PN mismatch!\n","indicate_802_11_pkt");
    }
    *(int *)(param_1 + 0x9dce4) = *(int *)(param_1 + 0x9dce4) + 1;
    RTMPFreeNdisPacket(param_1,iVar9);
    return;
  }
  iVar3 = *(int *)(param_1 + param_3 * 4 + 0xc);
  if (*(char *)(param_2 + 0x73) == '\0') {
    uVar7 = *(uint *)(param_2 + 0x44);
    if ((uVar7 & 0x1800) == 0) {
      if ((uVar7 & 0x100) == 0) {
        if ((uVar7 & 0x200) == 0) {
          if ((uVar7 & 0x400) != 0) {
            local_40 = *(void **)(param_2 + 0x28);
            local_3c = *(void **)(param_2 + 0x2c);
            goto LAB_000c9664;
          }
          if (-1 < DebugLevel) {
            printk("%s():Un-assigned Peer\'s Role!\n","indicate_802_11_pkt");
          }
        }
        local_40 = *(void **)(param_2 + 0x30);
      }
      else {
        local_40 = *(void **)(param_2 + 0x28);
        if ((uVar7 & 0x2000) == 0) {
          local_3c = *(void **)(param_2 + 0x30);
          goto LAB_000c9664;
        }
      }
      local_3c = *(void **)(param_2 + 0x2c);
    }
    else {
      local_40 = *(void **)(param_2 + 0x30);
      local_3c = *(void **)(param_2 + 0x34);
    }
LAB_000c9664:
    pvVar11 = *(void **)(param_2 + 0x3c);
    iVar4 = memcmp(&SNAP_802_1H,pvVar11,6);
    if (iVar4 == 0) {
      iVar4 = memcmp(&IPX,(void *)((int)pvVar11 + 6),2);
      if ((iVar4 == 0) || (iVar4 = memcmp(&APPLE_TALK,(void *)((int)pvVar11 + 6),2), iVar4 == 0))
      goto LAB_000c9750;
    }
    else {
      iVar4 = memcmp(&SNAP_BRIDGE_TUNNEL,pvVar11,6);
      if (iVar4 != 0) goto LAB_000c9750;
    }
    memmove(auStack_36,local_40,6);
    memmove(auStack_30,local_3c,6);
    memmove(&local_2a,(void *)((int)pvVar11 + 6),2);
    *(int *)(param_2 + 0x3c) = (int)pvVar11 + 8;
    uVar10 = *(short *)(param_2 + 0x40) - 8;
    *(ushort *)(param_2 + 0x40) = uVar10;
  }
  else {
    pvVar11 = *(void **)(param_2 + 0x3c);
    local_40 = (void *)((int)pvVar11 + -0xe);
    local_3c = (void *)((int)pvVar11 + -8);
    iVar4 = memcmp(&SNAP_802_1H,pvVar11,6);
    if (iVar4 == 0) {
      iVar4 = memcmp(&IPX,(void *)((int)pvVar11 + 6),2);
      if ((iVar4 != 0) && (iVar4 = memcmp(&APPLE_TALK,(void *)((int)pvVar11 + 6),2), iVar4 != 0)) {
LAB_000c984c:
        memmove(auStack_36,local_40,6);
        memmove(auStack_30,local_3c,6);
        memmove(&local_2a,(void *)((int)pvVar11 + 6),2);
        *(int *)(param_2 + 0x3c) = (int)pvVar11 + 8;
        uVar10 = *(short *)(param_2 + 0x40) - 8;
        *(ushort *)(param_2 + 0x40) = uVar10;
        goto LAB_000c9788;
      }
    }
    else {
      iVar4 = memcmp(&SNAP_BRIDGE_TUNNEL,pvVar11,6);
      if (iVar4 == 0) goto LAB_000c984c;
    }
LAB_000c9750:
    uVar10 = *(ushort *)(param_2 + 0x40);
    memmove(auStack_36,local_40,6);
    memmove(auStack_30,local_3c,6);
    local_29 = (undefined1)uVar10;
    local_2a = (undefined1)(uVar10 >> 8);
  }
LAB_000c9788:
  local_44 = auStack_36;
  if (2000 < uVar10) {
    RTMPFreeNdisPacket(param_1,iVar9);
    if (-1 < DebugLevel) {
      printk("%s():data_len(%d) > max_pkt_len(%d)!\n","indicate_802_11_pkt",uVar10,2000);
    }
    return;
  }
  sVar2 = *(short *)(iVar3 + 0x8fa);
  if (sVar2 == 0) {
    uVar8 = 0;
  }
  else {
    uVar8 = *(undefined2 *)(iVar3 + 0x8fc);
  }
  uVar5 = get_netdev_from_bssid(param_1,param_3);
  wlan_802_11_to_802_3_packet
            (uVar5,*(undefined1 *)(param_2 + 0x4b),sVar2,uVar8,*(undefined4 *)(param_2 + 0x38),
             *(undefined4 *)(param_2 + 0x3c),*(undefined2 *)(param_2 + 0x40),local_44,&TPID);
  if ((((*(char *)(param_1 + 0x286285) == '\x01') && ((**(byte **)(param_2 + 0x10) & 0x40) != 0)) &&
      ((&DAT_0036790d)[param_1] != '\0')) &&
     ((((&DAT_00367910)[param_1] != '\x01' &&
       (iVar4 = *(int *)(iVar9 + 0xcc), *(char *)(iVar4 + 0x17) == '\x11')) &&
      (*(short *)(iVar4 + 0x24) == 0x4400 && *(short *)(iVar4 + 0x22) == 0x4300)))) {
    iVar6 = RTMPLookupRepeaterCliEntry(param_1,0,(void *)(iVar4 + 0x46));
    if (iVar6 != 0) {
      if (*(char *)(iVar6 + 1) != '\x01') {
        printk(&_LC71,0x1001);
        dump_stack();
      }
      memmove((void *)(iVar4 + 0x46),(void *)(iVar6 + 0x7d),6);
    }
    __memzero(iVar4 + 0x28,2);
  }
  announce_or_forward_802_3_pkt(param_1,iVar9,iVar3,uVar1);
  return;
}

