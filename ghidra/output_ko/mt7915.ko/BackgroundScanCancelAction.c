// module: mt7915.ko
// function: BackgroundScanCancelAction @ 0x22cdfc
// size: 120 bytes
//

void BackgroundScanCancelAction(int param_1)

{
  undefined1 uStack_9;
  
  if (2 < DebugLevel) {
    printk("%s ===============>\n","BackgroundScanCancelAction");
  }
  *(undefined4 *)(param_1 + 0xa79184) = 0;
  *(undefined1 *)(param_1 + 0xa7905c) = 0;
  *(undefined1 *)(param_1 + 0xa79754) = 0;
  *(undefined1 *)(param_1 + 0xa79791) = 0;
  RTMPCancelTimer(param_1 + 0xa79190,&uStack_9);
  greenap_resume(param_1,1);
  return;
}

