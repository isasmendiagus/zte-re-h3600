// module: mt7915.ko
// function: WscUPnPMsgTimeOutAction @ 0x1e2448
// size: 380 bytes
//

void WscUPnPMsgTimeOutAction(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_1c;
  
  if (2 < DebugLevel) {
    printk("-----> WscUPnPMsgTimeOutAction\n");
  }
  if (param_2 != 0) {
    iVar2 = *(int *)(param_2 + 0x29e8);
    if (iVar2 == 0) {
      if (-1 < DebugLevel) {
        printk("%s: pAd is NULL!!\n","WscUPnPMsgTimeOutAction");
      }
    }
    else {
      if (2 < DebugLevel) {
        printk("UPnP StateMachine TimeOut(State=%d!)\n",*(undefined4 *)(param_2 + 0x10));
      }
      if (*(char *)(param_2 + 0x278e) == '\0') {
        os_alloc_mem(0,&local_1c,0x400);
        if (local_1c != 0) {
          __memzero(local_1c,0x400);
          uVar1 = BuildMessageNACK(iVar2,param_2,local_1c);
          WscSendUPnPMessage(iVar2,*(byte *)(param_2 + 0x1c54) & 0xf,0x11,0,local_1c,uVar1,0,0,
                             iVar2 + 0x794b5b,0);
          os_free_mem(local_1c);
        }
        *(undefined1 *)(param_2 + 0x278c) = 0;
        *(undefined1 *)(param_2 + 0x278e) = 0;
        *(undefined1 *)(param_2 + 0x278d) = 0;
        *(undefined4 *)(param_2 + 0x10) = 0;
        *(undefined4 *)(param_2 + 0xc) = 2;
      }
      else {
        RTMPModTimer(param_2 + 0x2794,2000);
        if (DebugLevel < 3) {
          return;
        }
        printk("UPnPMsgTimer Pending......\n");
      }
      if (2 < DebugLevel) {
        printk("<----- WscUPnPMsgTimeOutAction\n");
      }
    }
  }
  return;
}

