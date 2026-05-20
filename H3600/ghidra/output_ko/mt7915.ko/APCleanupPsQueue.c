// module: mt7915.ko
// function: APCleanupPsQueue @ 0x11a50
// size: 180 bytes
//

void APCleanupPsQueue(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  
  if (2 < DebugLevel) {
    printk("%s(): (0x%08lx)...\n","APCleanupPsQueue",param_2,DebugLevel,param_4);
  }
  piVar2 = (int *)*param_2;
  if (piVar2 != (int *)0x0) {
    do {
      if (2 < DebugLevel) {
        printk("%s():%u...\n","APCleanupPsQueue",param_2[2],piVar2,param_4);
        piVar2 = (int *)*param_2;
      }
      if (piVar2 != (int *)0x0) {
        iVar1 = *piVar2;
        *piVar2 = 0;
        *param_2 = iVar1;
        if (iVar1 == 0) {
          param_2[1] = 0;
        }
        param_2[2] = param_2[2] + -1;
      }
      RTMPFreeNdisPacket(param_1,piVar2);
      piVar2 = (int *)*param_2;
    } while (piVar2 != (int *)0x0);
    return;
  }
  return;
}

