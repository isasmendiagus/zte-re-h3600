// module: mt7915.ko
// function: OcDelRepeaterEntry @ 0xacfb8
// size: 260 bytes
//

void OcDelRepeaterEntry(int param_1,uint param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  
  piVar3 = *(int **)(param_1 + 0xc);
  iVar5 = *(int *)(param_1 + 8);
  uVar4 = *(undefined4 *)(iVar5 + 0x18);
  piVar2 = (int *)*piVar3;
  while (piVar1 = piVar2, (int *)(param_1 + 0xc) != piVar3) {
    if (*(byte *)(piVar3 + -1) == param_2) {
      OS_SPIN_LOCK(param_1 + 0x20);
      if (*(char *)(param_1 + 0x1d) == '\0') {
        if (-1 < DebugLevel) {
          printk("%s, bug here? RefCnt zero already.\n","OcDelRepeaterEntry");
        }
      }
      else {
        *(char *)(param_1 + 0x1d) = *(char *)(param_1 + 0x1d) + -1;
      }
      OS_SPIN_UNLOCK(param_1 + 0x20);
      ReleaseOmacIdx(uVar4,0x100,iVar5,*(undefined1 *)((int)piVar3 + -3));
      if (*piVar3 != 0) {
        *(int *)(*piVar3 + 4) = piVar3[1];
      }
      if ((int *)piVar3[1] != (int *)0x0) {
        *(int *)piVar3[1] = *piVar3;
      }
      *piVar3 = 0;
      piVar3[1] = 0;
      os_free_mem(piVar3 + -1);
    }
    piVar2 = (int *)*piVar1;
    piVar3 = piVar1;
  }
  return;
}

