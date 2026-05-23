// module: mt7915.ko
// function: ExitTxSTypeTable @ 0x1df874
// size: 408 bytes
//

undefined4 ExitTxSTypeTable(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined *puVar7;
  undefined4 *puVar8;
  undefined1 auStack_2c [8];
  
  puVar5 = (undefined4 *)(&DAT_002963d0 + param_1);
  puVar7 = &DAT_002963d4 + param_1;
  puVar8 = (undefined4 *)(&DAT_00296450 + param_1);
  do {
    OS_SPIN_LOCK_IRQSAVE(puVar8,auStack_2c);
    puVar2 = (undefined4 *)**(undefined4 **)(puVar7 + -4);
    puVar6 = *(undefined4 **)(puVar7 + -4);
    while (puVar3 = puVar2, puVar6 != puVar5) {
      if (puVar3 != (undefined4 *)0x0) {
        puVar3[1] = puVar6[1];
      }
      if ((undefined4 *)puVar6[1] != (undefined4 *)0x0) {
        *(undefined4 *)puVar6[1] = *puVar6;
      }
      *puVar6 = 0;
      puVar6[1] = 0;
      os_free_mem(puVar6);
      puVar2 = (undefined4 *)*puVar3;
      puVar6 = puVar3;
    }
    *(undefined4 **)(puVar7 + -4) = puVar5;
    puVar5[1] = puVar5;
    puVar5 = puVar5 + 2;
    OS_SPIN_UNLOCK_IRQRESTORE(puVar8,auStack_2c);
    puVar7 = puVar7 + 8;
    puVar8 = puVar8 + 1;
  } while ((undefined4 *)(&DAT_00296450 + param_1) != puVar5);
  puVar8 = (undefined4 *)(&UNK_002964d0 + param_1);
  puVar7 = &DAT_00296550 + param_1;
  do {
    puVar6 = puVar8 + -0xf;
    puVar5 = puVar8 + -0x10;
    puVar4 = puVar7;
    do {
      puVar3 = puVar5;
      OS_SPIN_LOCK_IRQSAVE(puVar4,auStack_2c);
      puVar2 = *(undefined4 **)puVar6[-1];
      puVar5 = (undefined4 *)puVar6[-1];
      while (puVar1 = puVar2, puVar5 != puVar3) {
        if (puVar1 != (undefined4 *)0x0) {
          puVar1[1] = puVar5[1];
        }
        if ((undefined4 *)puVar5[1] != (undefined4 *)0x0) {
          *(undefined4 *)puVar5[1] = *puVar5;
        }
        *puVar5 = 0;
        puVar5[1] = 0;
        os_free_mem(puVar5);
        puVar2 = (undefined4 *)*puVar1;
        puVar5 = puVar1;
      }
      puVar6[-1] = puVar3;
      puVar3[1] = puVar3;
      OS_SPIN_UNLOCK_IRQRESTORE(puVar4,auStack_2c);
      puVar6 = puVar6 + 2;
      puVar4 = puVar4 + 4;
      puVar5 = puVar3 + 2;
    } while (puVar3 + 2 != puVar8);
    puVar8 = puVar3 + 0x12;
    puVar7 = puVar7 + 0x20;
  } while (puVar8 != (undefined4 *)(&UNK_00296590 + param_1));
  return 0;
}

