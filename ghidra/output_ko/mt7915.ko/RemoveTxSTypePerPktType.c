// module: mt7915.ko
// function: RemoveTxSTypePerPktType @ 0x1dfdec
// size: 260 bytes
//

undefined4 RemoveTxSTypePerPktType(int param_1,uint param_2,uint param_3,uint param_4)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  undefined *puVar5;
  undefined1 auStack_24 [4];
  
  iVar4 = (param_3 & 7) + param_2 * 8;
  puVar5 = &DAT_002963d0 + (iVar4 + 0x60) * 4 + param_1;
  OS_SPIN_LOCK_IRQSAVE(puVar5,auStack_24);
  iVar4 = (iVar4 + 0x18) * 8;
  piVar3 = (int *)**(int **)(&DAT_002963d0 + param_1 + iVar4);
  piVar2 = *(int **)(&DAT_002963d0 + param_1 + iVar4);
  while( true ) {
    piVar1 = piVar3;
    if (piVar2 == (int *)(&DAT_002963d0 + iVar4 + param_1)) {
      OS_SPIN_UNLOCK_IRQRESTORE(puVar5,auStack_24);
      return 0xffffffff;
    }
    if (((*(byte *)((int)piVar2 + 10) == param_2) && (*(byte *)((int)piVar2 + 0xb) == param_3)) &&
       (*(byte *)(piVar2 + 3) == param_4)) break;
    piVar3 = (int *)*piVar1;
    piVar2 = piVar1;
  }
  if (*piVar2 != 0) {
    *(int *)(*piVar2 + 4) = piVar2[1];
  }
  if ((int *)piVar2[1] != (int *)0x0) {
    *(int *)piVar2[1] = *piVar2;
  }
  *piVar2 = 0;
  piVar2[1] = 0;
  os_free_mem(piVar2);
  OS_SPIN_UNLOCK_IRQRESTORE(puVar5,auStack_24);
  return 0;
}

