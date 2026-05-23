// module: mt7915.ko
// function: WscPINTimeOutAction @ 0x1e8cb0
// size: 188 bytes
//

void WscPINTimeOutAction(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined1 uStack_11;
  
  if (DebugLevel < 1) {
    if (param_2 == 0) {
      return;
    }
  }
  else {
    printk("-----> WscPINTimeOutAction\n");
    if (param_2 == 0) goto LAB_001e8d14;
  }
  iVar1 = *(int *)(param_2 + 0x29e8);
  if (iVar1 != 0) {
    if (*(char *)(param_2 + 0x28e8) != '\0') {
      *(undefined1 *)(param_2 + 0x28e8) = 0;
      RTMPCancelTimer(param_2 + 0x28ec,&uStack_11);
    }
    WscPINExec(iVar1,0,param_2);
    RtmpOsMlmeUp(iVar1 + 0x286298);
  }
LAB_001e8d14:
  if (0 < DebugLevel) {
    printk("<----- WscPINTimeOutAction\n");
  }
  return;
}

