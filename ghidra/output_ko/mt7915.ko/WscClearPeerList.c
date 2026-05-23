// module: mt7915.ko
// function: WscClearPeerList @ 0x1ed318
// size: 72 bytes
//

void WscClearPeerList(int *param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)*param_1;
  if (piVar1 == (int *)0x0) {
    return;
  }
  do {
    iVar2 = *piVar1;
    *param_1 = iVar2;
    if (iVar2 == 0) {
      param_1[1] = 0;
    }
    *(char *)(param_1 + 2) = (char)param_1[2] + -1;
    os_free_mem(piVar1);
    piVar1 = (int *)*param_1;
  } while (piVar1 != (int *)0x0);
  return;
}

