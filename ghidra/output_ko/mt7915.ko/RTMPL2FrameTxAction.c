// module: mt7915.ko
// function: RTMPL2FrameTxAction @ 0x243800
// size: 356 bytes
//

undefined4
RTMPL2FrameTxAction(undefined4 param_1,undefined4 param_2,code *param_3,undefined4 param_4,
                   void *param_5,size_t param_6,undefined1 param_7)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = idm_skb_stack_pop(1,param_6 + 2);
  if (iVar1 == 0) {
    iVar1 = __alloc_skbuff(param_6 + 0x22,0x20,0,0xffffffff);
    if (iVar1 == 0) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s : Error! Can\'t allocate a skb.\n","RTMPL2FrameTxAction");
      return 0;
    }
    iVar2 = *(int *)(iVar1 + 0xcc) + 0x20;
    iVar3 = *(int *)(iVar1 + 0xc0) + 0x20;
    g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
    *(int *)(iVar1 + 0xcc) = iVar2;
    *(int *)(iVar1 + 0xc0) = iVar3;
    if (0x63f < param_6 + 2) {
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
  *(void **)(iVar1 + 0xcc) = (void *)(iVar2 + 2);
  *(undefined4 *)(iVar1 + 0x18) = param_2;
  memmove((void *)(iVar2 + 2),param_5,param_6);
  skb_put(iVar1,param_6);
  if (2 < DebugLevel) {
    printk("%s doen\n","RTMPL2FrameTxAction");
  }
  (*param_3)(param_1,iVar1,param_7);
  return 1;
}

