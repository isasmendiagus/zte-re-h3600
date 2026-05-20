// module: mt7915.ko
// function: MATProto_PPPoEDis_Exit @ 0x7af84
// size: 232 bytes
//

undefined4 MATProto_PPPoEDis_Exit(int param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  piVar2 = *(int **)(param_1 + 0x14);
  if (piVar2 != (int *)0x0) {
    if ((char)*piVar2 != '\0') {
      piVar3 = piVar2 + 0x40;
      *(char *)piVar2 = '\0';
      do {
        piVar2 = piVar2 + 1;
        iVar1 = *piVar2;
        while (iVar1 != 0) {
          *piVar2 = *(int *)(iVar1 + 0x14);
          MATDBEntryFree(param_1);
          iVar1 = *piVar2;
        }
      } while (piVar2 != piVar3);
      piVar2 = *(int **)(param_1 + 0x14);
    }
    os_free_mem(piVar2);
    *(undefined4 *)(param_1 + 0x14) = 0;
  }
  piVar2 = *(int **)(param_1 + 0x10);
  if (piVar2 != (int *)0x0) {
    if ((char)*piVar2 != '\0') {
      piVar3 = piVar2 + 0x40;
      *(char *)piVar2 = '\0';
      do {
        piVar2 = piVar2 + 1;
        iVar1 = *piVar2;
        while (iVar1 != 0) {
          *piVar2 = *(int *)(iVar1 + 0x14);
          MATDBEntryFree(param_1);
          iVar1 = *piVar2;
        }
      } while (piVar2 != piVar3);
      piVar2 = *(int **)(param_1 + 0x10);
    }
    os_free_mem(piVar2);
    *(undefined4 *)(param_1 + 0x10) = 0;
  }
  return 1;
}

