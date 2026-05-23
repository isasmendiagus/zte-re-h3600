// module: mt7915.ko
// function: RTMPAllocateNdisPacket @ 0x243490
// size: 300 bytes
//

undefined4
RTMPAllocateNdisPacket
          (undefined4 param_1,int *param_2,void *param_3,size_t param_4,void *param_5,size_t param_6
          )

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_4 + param_6;
  iVar1 = idm_skb_stack_pop(1,iVar2 + 0x1bU);
  if (iVar1 == 0) {
    iVar1 = __alloc_skbuff(iVar2 + 0x3b,0x20,0,0xffffffff);
    if (iVar1 == 0) {
      *param_2 = 0;
      return 1;
    }
    *(int *)(iVar1 + 0xcc) = *(int *)(iVar1 + 0xcc) + 0x20;
    g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
    *(int *)(iVar1 + 0xc0) = *(int *)(iVar1 + 0xc0) + 0x20;
    if (0x63f < iVar2 + 0x1bU) {
      *(ushort *)(iVar1 + 0xbc) = *(ushort *)(iVar1 + 0xbc) & 0xff0f | 0x40;
    }
  }
  else {
    *(ushort *)(iVar1 + 0xbc) = *(ushort *)(iVar1 + 0xbc) & 0xff0f | 0x40;
    g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
  }
  if (param_4 == 0 || param_3 == (void *)0x0) {
    if (param_6 == 0 || param_5 == (void *)0x0) goto LAB_00243500;
  }
  else {
    memmove(*(void **)(iVar1 + 0xcc),param_3,param_4);
    if (param_6 == 0 || param_5 == (void *)0x0) goto LAB_00243500;
  }
  memmove((void *)(*(int *)(iVar1 + 0xcc) + param_4),param_5,param_6);
LAB_00243500:
  skb_put(iVar1,iVar2);
  *param_2 = iVar1;
  return 0;
}

