// module: mt7915.ko
// function: ExtEventICapUnSolicitStatusHandler @ 0x1a71c0
// size: 256 bytes
//

void ExtEventICapUnSolicitStatusHandler(int param_1,void *param_2)

{
  memmove((void *)(param_1 + 0xa3ae15),param_2,0x20);
  if (DebugLevel < 1) goto LAB_001a71f4;
  printk("%s: prICapGetEvent->u4StartAddr1 = 0x%x\n","ExtEventICapUnSolicitStatusHandler",
         *(undefined4 *)((int)param_2 + 8));
  if (0 < DebugLevel) {
    printk("%s: prICapGetEvent->u4StartAddr2 = 0x%x\n","ExtEventICapUnSolicitStatusHandler",
           *(undefined4 *)((int)param_2 + 0xc));
    if (DebugLevel < 1) goto LAB_001a71f4;
    printk("%s: prICapGetEvent->u4StartAddr3 = 0x%x\n","ExtEventICapUnSolicitStatusHandler",
           *(undefined4 *)((int)param_2 + 0x10));
    if (DebugLevel < 1) goto LAB_001a71f4;
    printk("%s: prICapGetEvent->u4EndAddr = 0x%x\n","ExtEventICapUnSolicitStatusHandler",
           *(undefined4 *)((int)param_2 + 0x14));
    if (DebugLevel < 1) goto LAB_001a71f4;
    printk("%s: prICapGetEvent->u4StopAddr = 0x%x\n","ExtEventICapUnSolicitStatusHandler",
           *(undefined4 *)((int)param_2 + 0x18));
  }
  if (0 < DebugLevel) {
    printk("%s: prICapGetEvent->u4Wrap = 0x%x\n","ExtEventICapUnSolicitStatusHandler",
           *(undefined4 *)((int)param_2 + 0x1c));
  }
LAB_001a71f4:
  complete(param_1 + 0xa3ba38);
  return;
}

