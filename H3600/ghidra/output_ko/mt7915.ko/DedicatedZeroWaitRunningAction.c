// module: mt7915.ko
// function: DedicatedZeroWaitRunningAction @ 0x22ec94
// size: 296 bytes
//

void DedicatedZeroWaitRunningAction
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if ((2 < DebugLevel) &&
     (printk("%s(): ch_stat %d\n","DedicatedZeroWaitRunningAction",
             *(undefined4 *)(param_1 + 0x79540c)), 2 < DebugLevel)) {
    printk("%s(): Get new outband DFS channel\n","DedicatedZeroWaitRunningAction");
  }
  DfsDedicatedOutBandRDDRunning(param_1);
  iVar2 = DfsGetBgndParameter(param_1,4);
  if (iVar2 == 0) {
    if (2 < DebugLevel) {
      printk(&_LC38,"DedicatedZeroWaitRunningAction");
    }
    DedicatedZeroWaitStop(param_1,0);
    return;
  }
  *(undefined4 *)(param_1 + 0xa79184) = 2;
  if (*(code **)(iVar1 + 0x280) != (code *)0x0) {
    (**(code **)(iVar1 + 0x280))(param_1,7,1);
  }
  DfsDedicatedOutBandRDDStart(param_1);
  if (*(int *)(param_1 + 0x79540c) - 2U < 3) {
    *(undefined4 *)(param_1 + 0x79540c) = 3;
  }
  if (2 < DebugLevel) {
    printk("%s(): ch_stat %d\n","DedicatedZeroWaitRunningAction",*(undefined4 *)(param_1 + 0x79540c)
           ,param_4);
    return;
  }
  return;
}

