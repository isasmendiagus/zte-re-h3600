// module: mt7915.ko
// function: RtmpOSNotifyRawData @ 0x244fec
// size: 424 bytes
//

undefined4
RtmpOSNotifyRawData(undefined4 param_1,void *param_2,size_t param_3,undefined4 param_4,
                   ushort param_5,int param_6)

{
  int iVar1;
  int iVar2;
  void *__dest;
  int iVar3;
  
  iVar1 = idm_skb_stack_pop(1,param_3 + 2);
  if (iVar1 == 0) {
    iVar1 = __alloc_skbuff(param_3 + 0x22,0x20,0,0xffffffff);
    if (iVar1 == 0) {
      if (DebugLevel < 0) {
        return 0xfffffff4;
      }
      printk("%s: failed to allocate sk_buff for notification\n",param_1);
      return 0xfffffff4;
    }
    iVar2 = *(int *)(iVar1 + 0xcc) + 0x20;
    iVar3 = *(int *)(iVar1 + 0xc0) + 0x20;
    g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
    *(int *)(iVar1 + 0xcc) = iVar2;
    *(int *)(iVar1 + 0xc0) = iVar3;
    if (0x63f < (int)(param_3 + 2)) {
      *(ushort *)(iVar1 + 0xbc) = *(ushort *)(iVar1 + 0xbc) & 0xff0f | 0x40;
    }
  }
  else {
    iVar2 = *(int *)(iVar1 + 0xcc);
    iVar3 = *(int *)(iVar1 + 0xc0);
    *(ushort *)(iVar1 + 0xbc) = *(ushort *)(iVar1 + 0xbc) & 0xff0f | 0x40;
    g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
  }
  *(int *)(iVar1 + 0xcc) = iVar2 + 2;
  *(int *)(iVar1 + 0xc0) = iVar3 + 2;
  __dest = (void *)skb_put(iVar1,param_3);
  memcpy(__dest,param_2,param_3);
  *(byte *)(iVar1 + 0x75) = *(byte *)(iVar1 + 0x75) & 0xf9 | 2;
  *(ushort *)(iVar1 + 0xa4) = param_5 << 8 | param_5 >> 8;
  *(size_t *)(iVar1 + 100) = param_3;
  *(undefined4 *)(iVar1 + 0x18) = param_1;
  *(short *)(iVar1 + 0xaa) =
       (short)*(undefined4 *)(iVar1 + 0xcc) - (short)*(undefined4 *)(iVar1 + 200);
  *(byte *)(iVar1 + 0x74) = *(byte *)(iVar1 + 0x74) & 0xf8 | 3;
  __memzero(iVar1 + 0x20,0x30);
  if ((param_6 != 0) && ((*(uint *)(((uint)&stack0xffffffe0 & 0xffffe000) + 4) & 0x100) != 0)) {
    napi_gro_receive(param_6,iVar1);
    return 0;
  }
  netif_rx(iVar1);
  return 0;
}

