// module: mt7915.ko
// function: WscPINAction @ 0x1e7288
// size: 360 bytes
//

void WscPINAction(undefined4 param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined1 uStack_21;
  
  if (2 < DebugLevel) {
    printk("-----> WscPINAction\n");
  }
  if (*(char *)(param_2 + 0x1c5b) == '\0') {
    cVar1 = *(char *)(param_2 + 0x283c);
  }
  else {
    *(undefined1 *)(param_2 + 0x1c5b) = 0;
    RTMPCancelTimer(param_2 + 0x1c5c,&uStack_21);
    cVar1 = *(char *)(param_2 + 0x283c);
  }
  if (cVar1 != '\0') {
    *(undefined1 *)(param_2 + 0x283c) = 0;
    RTMPCancelTimer(param_2 + 0x2840,&uStack_21);
  }
  if (*(char *)(param_2 + 0x28e8) != '\0') {
    *(undefined1 *)(param_2 + 0x28e8) = 0;
    RTMPCancelTimer(param_2 + 0x28ec,&uStack_21);
  }
  *(undefined4 *)(param_2 + 0xc) = 0x23;
  *(undefined4 *)(param_2 + 0x10) = 2;
  WscInitRegistrarPair(param_1,param_2,0);
  if (2 < DebugLevel) {
    printk("Enrollee_pin_code-----> %u\n",*(undefined4 *)(param_2 + 0x1c));
  }
  RTMPSetTimer(param_2 + 0x1c5c,120000);
  *(undefined1 *)(param_2 + 0x1c5b) = 1;
  *(undefined1 *)(param_2 + 0x29e4) = 1;
  WscScanExec(param_1,param_2);
  RTMPSetTimer(param_2 + 0x28ec,10000);
  iVar2 = DebugLevel;
  *(undefined1 *)(param_2 + 0x28e8) = 1;
  if (2 < iVar2) {
    printk("<----- WscPINAction\n");
  }
  return;
}

