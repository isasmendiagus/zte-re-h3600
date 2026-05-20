// module: mt7915.ko
// function: RemoveTxSTypePerPkt @ 0x1dfa14
// size: 240 bytes
//

undefined4 RemoveTxSTypePerPkt(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  undefined *puVar5;
  undefined1 auStack_24 [8];
  
  puVar5 = &DAT_002963d0 + ((param_2 & 0xf) + 0x20) * 4 + param_1;
  OS_SPIN_LOCK_IRQSAVE(puVar5,auStack_24);
  iVar1 = (param_2 & 0xf) * 8;
  piVar4 = (int *)**(int **)(&DAT_002963d0 + param_1 + iVar1);
  piVar3 = *(int **)(&DAT_002963d0 + param_1 + iVar1);
  while( true ) {
    piVar2 = piVar4;
    if (piVar3 == (int *)(&DAT_002963d0 + iVar1 + param_1)) {
      OS_SPIN_UNLOCK_IRQRESTORE(puVar5,auStack_24);
      return 0xffffffff;
    }
    if ((*(byte *)((int)piVar3 + 9) == param_2) && (*(byte *)(piVar3 + 3) == param_3)) break;
    piVar4 = (int *)*piVar2;
    piVar3 = piVar2;
  }
  if (*piVar3 != 0) {
    *(int *)(*piVar3 + 4) = piVar3[1];
  }
  if ((int *)piVar3[1] != (int *)0x0) {
    *(int *)piVar3[1] = *piVar3;
  }
  *piVar3 = 0;
  piVar3[1] = 0;
  os_free_mem(piVar3);
  OS_SPIN_UNLOCK_IRQRESTORE(puVar5,auStack_24);
  return 0;
}

