// module: tm.ko
// function: opcDbQosEntryValidSet @ 0x5591c
// size: 280 bytes
//

undefined4 opcDbQosEntryValidSet(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  char cVar5;
  int *piVar6;
  
  piVar6 = s_tmQosInfoListHead;
  if (param_1 == -1) {
    return 0xfffffff4;
  }
  while (piVar2 = piVar6 + 3, param_1 != *piVar2) {
    piVar1 = piVar6 + 1;
    piVar6 = (int *)*piVar1;
    if ((int *)*piVar1 == (int *)0x0) {
      printk("ERROR:the index %d of qos entry isnot exist",param_1,param_3,*piVar2,param_4);
      return 0;
    }
  }
  iVar3 = piVar6[4];
  if (param_2 == 0) {
    cVar5 = *(char *)(iVar3 + 4) + -1;
    *(char *)(iVar3 + 4) = cVar5;
    if (cVar5 == '\0') {
      __memzero(piVar6[4],5);
      puVar4 = (undefined4 *)piVar6[1];
      *(undefined1 *)(piVar6 + 2) = 0;
      piVar6[3] = param_1;
      if ((puVar4 != (undefined4 *)0x0) && (l_qosAllAlloc != '\0')) {
        if (*piVar6 == 0) {
          *puVar4 = 0;
          s_tmQosInfoListHead = (int *)piVar6[1];
        }
        else {
          *(undefined4 **)(*piVar6 + 4) = puVar4;
          *(int *)piVar6[1] = *piVar6;
        }
        iVar3 = (int)s_tmQosInfoListTail;
        piVar6[1] = 0;
        piVar2 = piVar6;
        *piVar6 = (int)s_tmQosInfoListTail;
        s_tmQosInfoListTail = piVar2;
        *(int **)(iVar3 + 4) = piVar6;
        return 0;
      }
    }
    return 0;
  }
  *(undefined1 *)(piVar6 + 2) = 1;
  *(char *)(iVar3 + 4) = *(char *)(iVar3 + 4) + '\x01';
  return 0;
}

