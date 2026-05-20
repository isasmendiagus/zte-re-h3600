// module: mt7915.ko
// function: RtmpCleanupPsQueue @ 0x1dd604
// size: 124 bytes
//

void RtmpCleanupPsQueue(undefined4 param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  
  if (2 < DebugLevel) {
    printk("RtmpCleanupPsQueue (0x%08lx)...\n");
  }
  piVar2 = (int *)*param_2;
  if (piVar2 != (int *)0x0) {
    do {
      iVar1 = *piVar2;
      *piVar2 = 0;
      *param_2 = iVar1;
      if (iVar1 == 0) {
        param_2[1] = 0;
      }
      param_2[2] = param_2[2] + -1;
      RTMPFreeNdisPacket(param_1,piVar2);
      piVar2 = (int *)*param_2;
    } while (piVar2 != (int *)0x0);
    return;
  }
  return;
}

