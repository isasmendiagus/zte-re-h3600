// module: mt7915.ko
// function: os_module_exit @ 0x245c38
// size: 4 bytes
//

void os_module_exit(void)

{
  int *piVar1;
  int *piVar2;
  bool bVar3;
  
  OS_SPIN_LOCK(&DAT_005f3d24);
  piVar1 = DAT_005f3d1c;
  piVar2 = (int *)*DAT_005f3d1c;
  if ((int **)DAT_005f3d1c != &DAT_005f3d1c) {
    do {
      if (piVar1 != (int *)0x0) {
        if (*piVar1 != 0) {
          *(int *)(*piVar1 + 4) = piVar1[1];
        }
        if ((int *)piVar1[1] != (int *)0x0) {
          *(int *)piVar1[1] = *piVar1;
        }
        *piVar1 = 0;
        piVar1[1] = 0;
        os_free_mem();
      }
      bVar3 = (int **)piVar2 != &DAT_005f3d1c;
      piVar1 = piVar2;
      piVar2 = (int *)*piVar2;
    } while (bVar3);
  }
  OS_SPIN_UNLOCK(&DAT_005f3d24);
  return;
}

