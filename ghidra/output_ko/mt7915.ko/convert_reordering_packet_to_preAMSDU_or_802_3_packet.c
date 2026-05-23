// module: mt7915.ko
// function: convert_reordering_packet_to_preAMSDU_or_802_3_packet @ 0xa7800
// size: 704 bytes
//

void convert_reordering_packet_to_preAMSDU_or_802_3_packet(int param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined2 uVar5;
  void *__s2;
  short sVar6;
  int iVar7;
  void *__src;
  void *local_3c;
  undefined1 auStack_36 [6];
  undefined1 auStack_30 [6];
  undefined1 local_2a;
  undefined1 local_29;
  
  if (0x67 < param_3) {
    printk(&_LC68,0x7a3);
    dump_stack();
    if (DebugLevel < 0) {
      return;
    }
    printk("%s(): invalid wdev_idx(%d)\n","convert_reordering_packet_to_preAMSDU_or_802_3_packet",
           param_3);
    return;
  }
  uVar3 = *(uint *)(param_2 + 0x44);
  iVar7 = *(int *)(param_1 + param_3 * 4 + 0xc);
  if ((uVar3 & 0x1800) == 0) {
    if ((uVar3 & 0x100) == 0) {
      if ((uVar3 & 0x200) == 0) {
        if ((uVar3 & 0x400) != 0) {
          local_3c = *(void **)(param_2 + 0x2c);
          __src = *(void **)(param_2 + 0x28);
          goto LAB_000a783c;
        }
        if (-1 < DebugLevel) {
          printk("%s():Un-assigned Peer\'s Role!\n",
                 "convert_reordering_packet_to_preAMSDU_or_802_3_packet");
        }
      }
      __src = *(void **)(param_2 + 0x30);
    }
    else {
      __src = *(void **)(param_2 + 0x28);
      if ((uVar3 & 0x2000) == 0) {
        local_3c = *(void **)(param_2 + 0x30);
        goto LAB_000a783c;
      }
    }
    local_3c = *(void **)(param_2 + 0x2c);
  }
  else {
    local_3c = *(void **)(param_2 + 0x34);
    __src = *(void **)(param_2 + 0x30);
  }
LAB_000a783c:
  __s2 = *(void **)(param_2 + 0x3c);
  iVar1 = memcmp(&SNAP_802_1H,__s2,6);
  if (iVar1 == 0) {
    iVar1 = memcmp(&IPX,(void *)((int)__s2 + 6),2);
    if ((iVar1 != 0) && (iVar1 = memcmp(&APPLE_TALK,(void *)((int)__s2 + 6),2), iVar1 != 0))
    goto LAB_000a787c;
  }
  else {
    iVar1 = memcmp(&SNAP_BRIDGE_TUNNEL,__s2,6);
    if (iVar1 == 0) {
LAB_000a787c:
      memmove(auStack_36,__src,6);
      memmove(auStack_30,local_3c,6);
      memmove(&local_2a,(void *)((int)__s2 + 6),2);
      *(int *)(param_2 + 0x3c) = (int)__s2 + 8;
      *(short *)(param_2 + 0x40) = *(short *)(param_2 + 0x40) + -8;
      goto LAB_000a78c4;
    }
  }
  uVar5 = *(undefined2 *)(param_2 + 0x40);
  memmove(auStack_36,__src,6);
  memmove(auStack_30,local_3c,6);
  local_29 = (undefined1)uVar5;
  local_2a = (undefined1)((ushort)uVar5 >> 8);
LAB_000a78c4:
  iVar1 = *(int *)(param_2 + 0x38);
  if (iVar1 == 0) {
    printk(&_LC71,0x7b2);
    dump_stack();
    iVar1 = *(int *)(param_2 + 0x38);
    if (iVar1 == 0) {
      return;
    }
  }
  uVar2 = get_netdev_from_bssid(param_1,param_3);
  *(undefined4 *)(iVar1 + 0x18) = uVar2;
  iVar4 = *(int *)(param_2 + 0x3c);
  *(int *)(iVar1 + 0xcc) = iVar4;
  *(uint *)(iVar1 + 100) = (uint)*(ushort *)(param_2 + 0x40);
  *(uint *)(iVar1 + 0xc0) = iVar4 + (uint)*(ushort *)(param_2 + 0x40);
  if ((*(uint *)(param_2 + 0x44) & 2) == 0) {
    if ((*(uint *)(param_2 + 0x44) & 0xa00) == 0) {
      uVar2 = 0xe;
      uVar5 = 0;
      sVar6 = 0;
    }
    else {
      sVar6 = *(short *)(iVar7 + 0x8fa);
      if (sVar6 == 0) {
        uVar2 = 0xe;
        uVar5 = 0;
      }
      else {
        uVar2 = 0x12;
        uVar5 = *(undefined2 *)(iVar7 + 0x8fc);
      }
    }
    uVar2 = skb_push(iVar1,uVar2);
    VLAN_8023_Header_Copy(sVar6,uVar5,auStack_36,0xe,uVar2,&TPID);
  }
  return;
}

