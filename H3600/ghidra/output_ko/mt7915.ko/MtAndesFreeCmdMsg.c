// module: mt7915.ko
// function: MtAndesFreeCmdMsg @ 0x1aca18
// size: 4 bytes
//

void MtAndesFreeCmdMsg(int param_1)

{
  int iVar1;
  undefined4 uStack_14;
  
  uStack_14 = 0;
  if (param_1 != 0) {
    iVar1 = *(int *)(param_1 + 0x1c);
    if (iVar1 == 0) {
      if (-1 < DebugLevel) {
        printk("%s: pAd is null\n","AndesFreeCmdMsg");
      }
    }
    else {
      if ((*(byte *)(param_1 + 4) & 4) != 0) {
        complete(param_1 + 0x50);
      }
      if (*(int *)(param_1 + 0x24) != 0) {
        RTMPFreeNdisPacket(iVar1);
      }
      OS_SPIN_LOCK_IRQSAVE(iVar1 + 0xa78500,&uStack_14);
      *(int *)(iVar1 + 0xa78514) = *(int *)(iVar1 + 0xa78514) + 1;
      OS_SPIN_UNLOCK_IRQRESTORE(iVar1 + 0xa78500,&uStack_14);
    }
    os_free_mem(param_1);
  }
  return;
}

