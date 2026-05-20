// module: mt7915.ko
// function: RTMP_TimerListRelease @ 0x13c1b0
// size: 256 bytes
//

void RTMP_TimerListRelease(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  piVar4 = *(int **)(param_1 + 0xa78490);
  if (piVar4 == (int *)0x0) {
    return;
  }
  piVar2 = piVar4;
  if (piVar4[1] != param_2) {
    do {
      piVar2 = (int *)*piVar2;
      if (piVar2 == (int *)0x0) {
        return;
      }
    } while (piVar2[1] != param_2);
    if (piVar4 != piVar2) {
      for (piVar1 = (int *)*piVar4; piVar1 != (int *)0x0; piVar1 = (int *)*piVar1) {
        if (piVar2 == piVar1) {
          *piVar4 = *piVar2;
          if (piVar2 == *(int **)(param_1 + 0xa78494)) {
            *(int **)(param_1 + 0xa78494) = piVar4;
          }
          goto LAB_0013c26c;
        }
        piVar4 = piVar1;
      }
      goto LAB_0013c234;
    }
  }
  iVar3 = *piVar4;
  *(int *)(param_1 + 0xa78490) = iVar3;
  if (iVar3 == 0) {
    *(undefined4 *)(param_1 + 0xa78494) = 0;
  }
LAB_0013c26c:
  *(char *)(param_1 + 0xa78498) = *(char *)(param_1 + 0xa78498) + -1;
LAB_0013c234:
  if (3 < DebugLevel) {
    printk("%s: release timer obj %lx!\n","RTMP_TimerListRelease",param_2);
  }
  os_free_mem(piVar2);
  return;
}

