// module: tm.ko
// function: opcDbNatEntryValidSet @ 0x55a34
// size: 280 bytes
//

undefined4 opcDbNatEntryValidSet(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  short sVar2;
  int iVar3;
  int *piVar4;
  short *psVar5;
  undefined4 *puVar6;
  int *piVar7;
  
  piVar7 = s_tmNatInfoListHead;
  if (param_1 == -1) {
    return 0xfffffff4;
  }
  while (piVar4 = piVar7 + 3, param_1 != *piVar4) {
    piVar1 = piVar7 + 1;
    piVar7 = (int *)*piVar1;
    if ((int *)*piVar1 == (int *)0x0) {
      printk("ERROR:the index %d of nat entry isnot exist",param_1,param_3,*piVar4,param_4);
      return 0;
    }
  }
  psVar5 = (short *)piVar7[4];
  if (param_2 == 0) {
    sVar2 = *psVar5;
    *psVar5 = sVar2 + -1;
    if ((short)(sVar2 + -1) == 0) {
      __memzero(piVar7[4],0x12);
      puVar6 = (undefined4 *)piVar7[1];
      *(undefined1 *)(piVar7 + 2) = 0;
      piVar7[3] = param_1;
      if ((puVar6 != (undefined4 *)0x0) && (l_natAllAlloc != '\0')) {
        if (*piVar7 == 0) {
          *puVar6 = 0;
          s_tmNatInfoListHead = (int *)piVar7[1];
        }
        else {
          *(undefined4 **)(*piVar7 + 4) = puVar6;
          *(int *)piVar7[1] = *piVar7;
        }
        iVar3 = (int)s_tmNatInfoListTail;
        piVar7[1] = 0;
        piVar4 = piVar7;
        *piVar7 = (int)s_tmNatInfoListTail;
        s_tmNatInfoListTail = piVar4;
        *(int **)(iVar3 + 4) = piVar7;
        return 0;
      }
    }
    return 0;
  }
  *(undefined1 *)(piVar7 + 2) = 1;
  *psVar5 = *psVar5 + 1;
  return 0;
}

