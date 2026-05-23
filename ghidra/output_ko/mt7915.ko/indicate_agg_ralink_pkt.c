// module: mt7915.ko
// function: indicate_agg_ralink_pkt @ 0xc9a68
// size: 980 bytes
//

void indicate_agg_ralink_pkt(int param_1,undefined4 param_2,int param_3,uint param_4)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  ushort uVar5;
  ushort uVar6;
  byte *pbVar7;
  short sVar8;
  undefined4 *puVar9;
  void *local_44;
  void *local_40;
  undefined1 *local_3c;
  undefined1 auStack_36 [6];
  undefined1 auStack_30 [6];
  undefined1 local_2a;
  undefined1 local_29;
  
  uVar1 = *(undefined1 *)(param_1 + 0x286285);
  if (0x67 < param_4) {
    if (-1 < DebugLevel) {
      printk("%s():Invalid wdev_idx(%d)\n","indicate_agg_ralink_pkt",param_4);
    }
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0x38));
    wlan_dbg_set_last_error(0,1,0x1054,"indicate_agg_ralink_pkt");
    return;
  }
  pbVar7 = *(byte **)(param_3 + 0x3c);
  puVar9 = *(undefined4 **)(param_1 + param_4 * 4 + 0xc);
  uVar5 = (ushort)*pbVar7 + (ushort)pbVar7[1] * 0x100;
  if ((0x600 < uVar5) || (*(ushort *)(param_3 + 0x40) <= uVar5)) {
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0x38));
    wlan_dbg_set_last_error(0,1,0x1061,"indicate_agg_ralink_pkt");
    return;
  }
  uVar4 = *(uint *)(param_3 + 0x44);
  sVar8 = *(ushort *)(param_3 + 0x40) - 2;
  pbVar7 = pbVar7 + 2;
  *(byte **)(param_3 + 0x3c) = pbVar7;
  *(short *)(param_3 + 0x40) = sVar8;
  if ((uVar4 & 0x1800) == 0) {
    if ((uVar4 & 0x100) == 0) {
      if ((uVar4 & 0x200) == 0) {
        if ((uVar4 & 0x400) != 0) {
          local_44 = *(void **)(param_3 + 0x28);
          local_40 = *(void **)(param_3 + 0x2c);
          goto LAB_000c9b30;
        }
        if (-1 < DebugLevel) {
          printk("%s():Un-assigned Peer\'s Role!\n","indicate_agg_ralink_pkt");
          pbVar7 = *(byte **)(param_3 + 0x3c);
          sVar8 = *(short *)(param_3 + 0x40);
        }
      }
      local_44 = *(void **)(param_3 + 0x30);
    }
    else {
      local_44 = *(void **)(param_3 + 0x28);
      if ((uVar4 & 0x2000) == 0) {
        local_40 = *(void **)(param_3 + 0x30);
        goto LAB_000c9b30;
      }
    }
    local_40 = *(void **)(param_3 + 0x2c);
  }
  else {
    local_44 = *(void **)(param_3 + 0x30);
    local_40 = *(void **)(param_3 + 0x34);
  }
LAB_000c9b30:
  iVar2 = memcmp(&SNAP_802_1H,pbVar7,6);
  if (iVar2 == 0) {
    iVar2 = memcmp(&IPX,pbVar7 + 6,2);
    if ((iVar2 != 0) && (iVar2 = memcmp(&APPLE_TALK,pbVar7 + 6,2), iVar2 != 0)) goto LAB_000c9b64;
  }
  else {
    iVar2 = memcmp(&SNAP_BRIDGE_TUNNEL,pbVar7,6);
    if (iVar2 == 0) {
LAB_000c9b64:
      memmove(auStack_36,local_44,6);
      memmove(auStack_30,local_40,6);
      memmove(&local_2a,pbVar7 + 6,2);
      *(short *)(param_3 + 0x40) = sVar8 + -8;
      *(byte **)(param_3 + 0x3c) = pbVar7 + 8;
      goto LAB_000c9bac;
    }
  }
  memmove(auStack_36,local_44,6);
  memmove(auStack_30,local_40,6);
  local_29 = (undefined1)sVar8;
  local_2a = (undefined1)((ushort)sVar8 >> 8);
LAB_000c9bac:
  local_3c = auStack_36;
  if (*(int *)(param_3 + 0x38) == 0) {
    printk(&_LC76,0x1067);
    dump_stack();
    if (*(int *)(param_3 + 0x38) == 0) {
      RTMPFreeNdisPacket(param_1,0);
      wlan_dbg_set_last_error(0,1,0x106b,"indicate_agg_ralink_pkt");
      return;
    }
  }
  *(int *)(param_1 + 0xa39e48) = *(int *)(param_1 + 0xa39e48) + 1;
  uVar6 = *(short *)(param_3 + 0x40) - uVar5;
  iVar2 = *(int *)(param_3 + 0x3c) + uVar6 + 0xe;
  iVar2 = duplicate_pkt_vlan(*puVar9,*(undefined2 *)((int)puVar9 + 0x8fa),
                             *(undefined2 *)(puVar9 + 0x23f),iVar2 + -0xe,0xe,iVar2,uVar5 - 0xe,
                             &TPID);
  if (iVar2 == 0) {
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0x38));
    wlan_dbg_set_last_error(0,1,0x107a,"indicate_agg_ralink_pkt");
    return;
  }
  *(ushort *)(param_3 + 0x40) = uVar6;
  uVar3 = get_netdev_from_bssid(param_1,param_4);
  wlan_802_11_to_802_3_packet
            (uVar3,*(undefined1 *)(param_3 + 0x4b),0,0,*(undefined4 *)(param_3 + 0x38),
             *(undefined4 *)(param_3 + 0x3c),*(undefined2 *)(param_3 + 0x40),local_3c,&TPID);
  announce_or_forward_802_3_pkt(param_1,*(undefined4 *)(param_3 + 0x38),puVar9,uVar1);
  announce_or_forward_802_3_pkt(param_1,iVar2,puVar9,uVar1);
  return;
}

