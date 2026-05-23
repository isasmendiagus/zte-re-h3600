// module: mt7915.ko
// function: RTMP_AllocateFragPacketBuffer @ 0x2433b8
// size: 216 bytes
//

int RTMP_AllocateFragPacketBuffer(undefined4 param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = idm_skb_stack_pop(1);
  if (iVar1 == 0) {
    iVar1 = __alloc_skbuff(param_2 + 0x20,0x20,0,0xffffffff);
    if (iVar1 == 0) {
      if (-1 < DebugLevel) {
        printk("can\'t allocate frag rx %ld size packet\n",param_2);
      }
    }
    else {
      *(int *)(iVar1 + 0xcc) = *(int *)(iVar1 + 0xcc) + 0x20;
      g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
      *(int *)(iVar1 + 0xc0) = *(int *)(iVar1 + 0xc0) + 0x20;
      if (0x63f < param_2) {
        *(ushort *)(iVar1 + 0xbc) = *(ushort *)(iVar1 + 0xbc) & 0xff0f | 0x40;
      }
    }
  }
  else {
    *(ushort *)(iVar1 + 0xbc) = *(ushort *)(iVar1 + 0xbc) & 0xff0f | 0x40;
    g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
  }
  return iVar1;
}

