// module: mt7915.ko
// function: WaitPeerWNMNotifyRspTimeout @ 0x229cac
// size: 180 bytes
//

void WaitPeerWNMNotifyRspTimeout(undefined4 param_1,int *param_2)

{
  byte bVar1;
  int iVar2;
  undefined1 uStack_11;
  
  printk(&_LC4,"WaitPeerWNMNotifyRspTimeout");
  if (param_2 != (int *)0x0) {
    iVar2 = param_2[5];
    RTMPReleaseTimer(param_2 + 6,&uStack_11);
    if ((*(uint *)(iVar2 + 0xa39f84) & 0x140) == 0) {
      bVar1 = *(byte *)(param_2 + 3);
      down_interruptible(&_LC170 + (uint)bVar1 * 0x5834 + iVar2);
      if (*param_2 != 0) {
        *(int *)(*param_2 + 4) = param_2[1];
      }
      if ((int *)param_2[1] != (int *)0x0) {
        *(int *)param_2[1] = *param_2;
      }
      *param_2 = 0;
      param_2[1] = 0;
      up(&_LC170 + (uint)bVar1 * 0x5834 + iVar2);
      os_free_mem(param_2);
      return;
    }
  }
  return;
}

