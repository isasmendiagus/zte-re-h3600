// module: mt7915.ko
// function: rebuild_802_11_eapol_frm @ 0xc588c
// size: 360 bytes
//

void rebuild_802_11_eapol_frm(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  undefined4 uVar2;
  void *pvVar3;
  undefined1 *puVar4;
  undefined1 *__dest;
  undefined4 *puVar5;
  int iVar6;
  bool bVar7;
  undefined4 local_2e;
  undefined2 local_2a;
  undefined2 local_28;
  undefined4 local_24;
  undefined2 local_20;
  undefined4 local_1e;
  undefined2 local_1a;
  undefined4 local_18;
  undefined2 local_14;
  
  __memzero(&local_28,0x18);
  uVar1 = **(undefined2 **)(param_2 + 0x1c);
  puVar5 = *(undefined4 **)(param_2 + 0x30);
  local_24 = **(undefined4 **)(param_2 + 0x28);
  local_28._1_1_ = (byte)((ushort)uVar1 >> 8);
  local_20 = *(undefined2 *)(*(undefined4 **)(param_2 + 0x28) + 1);
  bVar7 = (local_28._1_1_ & 3) == 3;
  local_1e = **(undefined4 **)(param_2 + 0x2c);
  local_1a = *(undefined2 *)(*(undefined4 **)(param_2 + 0x2c) + 1);
  local_18 = *puVar5;
  local_14 = *(undefined2 *)(puVar5 + 1);
  if (bVar7) {
    puVar5 = *(undefined4 **)(param_2 + 0x34);
  }
  if (bVar7) {
    iVar6 = 0x1e;
    local_2e = *puVar5;
    local_2a = *(undefined2 *)(puVar5 + 1);
  }
  else {
    iVar6 = 0x18;
  }
  local_28._0_1_ = (char)uVar1;
  if ((char)local_28 < '\0') {
    iVar6 = iVar6 + 8;
  }
  else {
    iVar6 = iVar6 + 6;
  }
  local_28 = uVar1;
  skb_push(*(undefined4 *)(param_2 + 0x38),iVar6 + -0xc);
  RtmpOsSkbResetNetworkHeader(*(undefined4 *)(param_2 + 0x38));
  RtmpOsSkbResetTransportHeader(*(undefined4 *)(param_2 + 0x38));
  RtmpOsSkbResetMacLen(*(undefined4 *)(param_2 + 0x38));
  uVar2 = *(undefined4 *)(*(int *)(param_2 + 0x38) + 0xcc);
  *(short *)(param_2 + 0x40) = *(short *)(param_2 + 0x40) + -0xc + (short)iVar6;
  *(undefined4 *)(param_2 + 0x3c) = uVar2;
  *(undefined4 *)(param_2 + 0x1c) = uVar2;
  __memzero(*(undefined4 *)(*(int *)(param_2 + 0x38) + 0xcc),iVar6);
  pvVar3 = memmove(*(void **)(param_2 + 0x3c),&local_28,0x18);
  puVar4 = (undefined1 *)((int)pvVar3 + 0x18);
  if ((local_28._1_1_ & 3) == 3) {
    *(undefined4 *)((int)pvVar3 + 0x18) = local_2e;
    *(undefined2 *)((int)pvVar3 + 0x1c) = local_2a;
    puVar4 = (undefined1 *)((int)pvVar3 + 0x1e);
  }
  __dest = puVar4;
  if ((char)local_28 < '\0') {
    __dest = puVar4 + 2;
    *puVar4 = *(undefined1 *)(param_2 + 0x4a);
  }
  memmove(__dest,&SNAP_802_1H,6);
  *(uint *)(param_2 + 0x44) = *(uint *)(param_2 + 0x44) & 0xfffbffff;
  update_rxblk_addr(param_2);
  return;
}

