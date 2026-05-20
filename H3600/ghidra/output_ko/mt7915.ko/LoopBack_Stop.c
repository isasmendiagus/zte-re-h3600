// module: mt7915.ko
// function: LoopBack_Stop @ 0x28cf6c
// size: 344 bytes
//

void LoopBack_Stop(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0xa3bafa) == '\x01') {
    iVar1 = 0;
    do {
      if (2 < DebugLevel) {
        printk("%s, @#@#BreakCount = %d\n","LoopBack_Stop",iVar1);
      }
      bVar2 = iVar1 != 0x65;
      iVar1 = iVar1 + 1;
    } while ((bVar2) && (RtmpusecDelay(300), *(char *)(param_1 + 0xa3bafa) == '\x01'));
  }
  iVar1 = RtmpOSTaskKill(param_1 + 0xa77b60);
  if (iVar1 == 1) {
    if (-1 < DebugLevel) {
      printk("kill LoopBackTxTask task failed!\n");
      goto LAB_0028cfdc;
    }
    if (*(int *)(param_1 + 0xa3bafc) != 0) goto LAB_0028d000;
LAB_0028cfe8:
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0xa3bafc) = 1;
    *(undefined4 *)(param_1 + 0xa3bb00) = 0;
  }
  else {
LAB_0028cfdc:
    iVar1 = DebugLevel;
    if (*(int *)(param_1 + 0xa3bafc) == 0) goto LAB_0028cfe8;
  }
  if (2 < iVar1) {
    printk("***************************************%s @#@#***************************************\n"
           ,"LoopBack_Stop");
  }
LAB_0028d000:
  *(undefined1 *)(param_1 + 0xa3baf9) = 0;
  if ((*(char *)(param_1 + 0xa3baf8) == '\0') && (*(char *)(param_1 + 0xa77ba0) == '\0')) {
    MtCmdHIFLoopBackTest(param_1,0,0);
  }
  if (DebugLevel < 3) {
    return;
  }
  printk(&_LC18,"LoopBack_Stop");
  return;
}

