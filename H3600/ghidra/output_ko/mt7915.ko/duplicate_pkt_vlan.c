// module: mt7915.ko
// function: duplicate_pkt_vlan @ 0x244778
// size: 304 bytes
//

int duplicate_pkt_vlan(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                      int param_5,void *param_6,size_t param_7,undefined4 param_8)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = param_7 + 2 + param_5;
  iVar1 = idm_skb_stack_pop(1,iVar4);
  if (iVar1 == 0) {
    iVar1 = __alloc_skbuff(iVar4 + 0x20,0x20,0,0xffffffff);
    if (iVar1 == 0) {
      return 0;
    }
    iVar2 = *(int *)(iVar1 + 0xcc) + 0x20;
    iVar3 = *(int *)(iVar1 + 0xc0) + 0x20;
    g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
    *(int *)(iVar1 + 0xcc) = iVar2;
    *(int *)(iVar1 + 0xc0) = iVar3;
    if (0x63f < iVar4) {
      *(ushort *)(iVar1 + 0xbc) = *(ushort *)(iVar1 + 0xbc) & 0xff0f | 0x40;
    }
  }
  else {
    iVar2 = *(int *)(iVar1 + 0xcc);
    iVar3 = *(int *)(iVar1 + 0xc0);
    *(ushort *)(iVar1 + 0xbc) = *(ushort *)(iVar1 + 0xbc) & 0xff0f | 0x40;
    g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
  }
  *(int *)(iVar1 + 0xc0) = iVar3 + 2;
  *(int *)(iVar1 + 0xcc) = iVar2 + 2;
  iVar4 = VLAN_8023_Header_Copy(param_2,param_3,param_4,param_5,iVar3 + 2,param_8);
  skb_put(iVar1,iVar4 + param_5);
  memmove(*(void **)(iVar1 + 0xc0),param_6,param_7);
  skb_put(iVar1,param_7);
  *(undefined4 *)(iVar1 + 0x18) = param_1;
  return iVar1;
}

