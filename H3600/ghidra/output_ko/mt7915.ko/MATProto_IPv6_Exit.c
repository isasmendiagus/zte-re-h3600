// module: mt7915.ko
// function: MATProto_IPv6_Exit @ 0x7bfc8
// size: 120 bytes
//

undefined4 MATProto_IPv6_Exit(int param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  piVar3 = *(int **)(param_1 + 0xc);
  if (piVar3 != (int *)0x0) {
    if ((char)*piVar3 != '\0') {
      *(char *)piVar3 = '\0';
      piVar2 = piVar3;
      do {
        piVar2 = piVar2 + 1;
        iVar1 = *piVar2;
        while (iVar1 != 0) {
          *piVar2 = *(int *)(iVar1 + 0x1c);
          MATDBEntryFree(param_1);
          iVar1 = *piVar2;
        }
      } while (piVar2 != piVar3 + 0x41);
    }
    os_free_mem(piVar3);
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  return 1;
}

