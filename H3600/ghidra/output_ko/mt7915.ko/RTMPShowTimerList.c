// module: mt7915.ko
// function: RTMPShowTimerList @ 0x13c2b4
// size: 372 bytes
//

void RTMPShowTimerList(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)(param_1 + 0xa78490);
  if ((0 < DebugLevel) &&
     (printk("Timer List Size:%d\n",*(undefined1 *)(param_1 + 0xa78498),DebugLevel,
             param_1 + 0xa78000,param_4), 0 < DebugLevel)) {
    printk("=====================================\n");
  }
  if (piVar1 == (int *)0x0) {
    return;
  }
  do {
    iVar2 = piVar1[1];
    piVar1 = (int *)*piVar1;
    if ((((((0 < DebugLevel) && (printk("Valid:%d\n",*(undefined1 *)(iVar2 + 0x1c)), 0 < DebugLevel)
           ) && (printk("pObj:%lx\n",iVar2), 0 < DebugLevel)) &&
         ((printk("PeriodicType:%d\n",*(undefined1 *)(iVar2 + 0x1e)), 0 < DebugLevel &&
          (printk("Repeat:%d\n",*(undefined1 *)(iVar2 + 0x1f)), 0 < DebugLevel)))) &&
        ((printk("State:%d\n",*(undefined1 *)(iVar2 + 0x1d)), 0 < DebugLevel &&
         ((printk("TimerValue:%ld\n",*(undefined4 *)(iVar2 + 0x20)), 0 < DebugLevel &&
          (printk("timer_lock:%lx\n",*(undefined4 *)(iVar2 + 0x2c)), 0 < DebugLevel)))))) &&
       (printk("pCaller:%pS\n",*(undefined4 *)(iVar2 + 0x30)), 0 < DebugLevel)) {
      printk("=====================================\n");
    }
  } while (piVar1 != (int *)0x0);
  return;
}

