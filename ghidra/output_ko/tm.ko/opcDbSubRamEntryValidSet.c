// module: tm.ko
// function: opcDbSubRamEntryValidSet @ 0x55c64
// size: 284 bytes
//

undefined4 opcDbSubRamEntryValidSet(uint param_1,int param_2)

{
  short sVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int *piVar5;
  short *psVar6;
  
  piVar5 = s_tmSubRamInfoListHead;
  while (psVar6 = (short *)piVar5[4], (ushort)psVar6[1] != param_1) {
    piVar5 = (int *)piVar5[1];
    if (piVar5 == (int *)0x0) {
      printk("ERROR:the index %d of modify entry isnot exist",param_1);
      return 0;
    }
  }
  if (param_2 != 0) {
    *(undefined1 *)(piVar5 + 2) = 1;
    *(undefined1 *)(psVar6 + 2) = 1;
    *psVar6 = *psVar6 + 1;
    return 0;
  }
  sVar1 = *psVar6;
  *psVar6 = sVar1 + -1;
  if ((short)(sVar1 + -1) == 0) {
    __memzero(psVar6,0x24);
    *(undefined1 *)(psVar6 + 2) = 0;
    *(undefined1 *)(piVar5 + 2) = 0;
    psVar6[1] = (short)param_1;
    psVar6[0xf] = -1;
    psVar6[10] = -1;
    puVar4 = (undefined4 *)piVar5[1];
    if ((puVar4 != (undefined4 *)0x0) && (l_subRamAllAlloc != '\0')) {
      if (*piVar5 == 0) {
        *puVar4 = 0;
        s_tmSubRamInfoListHead = (int *)piVar5[1];
      }
      else {
        *(undefined4 **)(*piVar5 + 4) = puVar4;
        *(int *)piVar5[1] = *piVar5;
      }
      iVar2 = (int)s_tmSubRamInfoListTail;
      piVar5[1] = 0;
      piVar3 = piVar5;
      *piVar5 = (int)s_tmSubRamInfoListTail;
      s_tmSubRamInfoListTail = piVar3;
      *(int **)(iVar2 + 4) = piVar5;
      return 0;
    }
  }
  return 0;
}

