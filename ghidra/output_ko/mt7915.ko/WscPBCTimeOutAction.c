// module: mt7915.ko
// function: WscPBCTimeOutAction @ 0x1e85b4
// size: 188 bytes
//

void WscPBCTimeOutAction(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined1 uStack_11;
  
  if (DebugLevel < 1) {
    if (param_2 == 0) {
      return;
    }
  }
  else {
    printk("-----> WscPBCTimeOutAction\n");
    if (param_2 == 0) goto LAB_001e8618;
  }
  iVar1 = *(int *)(param_2 + 0x29e8);
  if (iVar1 != 0) {
    if (*(char *)(param_2 + 0x2804) != '\0') {
      *(undefined1 *)(param_2 + 0x2804) = 0;
      RTMPCancelTimer(param_2 + 0x2808,&uStack_11);
    }
    WscPBCExec(iVar1,0,param_2);
    RtmpOsMlmeUp(iVar1 + 0x286298);
  }
LAB_001e8618:
  if (0 < DebugLevel) {
    printk("<----- WscPBCTimeOutAction\n");
  }
  return;
}

