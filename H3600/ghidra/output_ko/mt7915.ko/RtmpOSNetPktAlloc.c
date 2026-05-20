// module: mt7915.ko
// function: RtmpOSNetPktAlloc @ 0x243310
// size: 168 bytes
//

int RtmpOSNetPktAlloc(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = idm_skb_stack_pop(1,param_2 + 2,param_3,param_4,param_4);
  if (iVar1 == 0) {
    iVar1 = __alloc_skbuff(param_2 + 0x22,0x20,0,0xffffffff);
    if (iVar1 != 0) {
      *(int *)(iVar1 + 0xcc) = *(int *)(iVar1 + 0xcc) + 0x20;
      g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
      *(int *)(iVar1 + 0xc0) = *(int *)(iVar1 + 0xc0) + 0x20;
      if (0x63f < param_2 + 2) {
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

