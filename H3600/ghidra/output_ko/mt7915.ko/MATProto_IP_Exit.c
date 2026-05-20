// module: mt7915.ko
// function: MATProto_IP_Exit @ 0x7a214
// size: 4 bytes
//

undefined4 MATProto_IP_Exit(int param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  piVar3 = *(int **)(param_1 + 8);
  if (piVar3 != (int *)0x0) {
    if ((char)*piVar3 != '\0') {
      *(char *)piVar3 = '\0';
      piVar2 = piVar3;
      do {
        piVar2 = piVar2 + 1;
        iVar1 = *piVar2;
        while (iVar1 != 0) {
          *piVar2 = *(int *)(iVar1 + 0x10);
          MATDBEntryFree(param_1);
          iVar1 = *piVar2;
        }
      } while (piVar2 != piVar3 + 0x41);
    }
    os_free_mem(piVar3);
    *(undefined4 *)(param_1 + 8) = 0;
  }
  return 1;
}

