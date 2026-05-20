// module: mt7915.ko
// function: InitTxSTypeTable @ 0x1df728
// size: 316 bytes
//

undefined4 InitTxSTypeTable(int param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  char *pcVar3;
  char *pcVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined1 auStack_24 [4];
  
  if (0 < DebugLevel) {
    printk("%s %d\n","InitTxSTypeTable",0x54);
  }
  puVar5 = (undefined4 *)(&UNK_0029644c + param_1);
  puVar1 = &DAT_002963d0 + param_1;
  do {
    puVar5 = puVar5 + 1;
    *puVar5 = 0;
    OS_SPIN_LOCK_IRQSAVE(puVar5,auStack_24);
    *(undefined **)puVar1 = puVar1;
    *(undefined **)(puVar1 + 4) = puVar1;
    puVar1 = puVar1 + 8;
    OS_SPIN_UNLOCK_IRQRESTORE(puVar5,auStack_24);
  } while (puVar5 != (undefined4 *)(&UNK_0029648c + param_1));
  puVar5 = (undefined4 *)(&UNK_0029654c + param_1);
  puVar1 = &DAT_00296490 + param_1;
  do {
    puVar6 = puVar5 + 8;
    puVar2 = puVar1;
    do {
      puVar5 = puVar5 + 1;
      *puVar5 = 0;
      OS_SPIN_LOCK_IRQSAVE(puVar5,auStack_24);
      *(undefined **)puVar2 = puVar2;
      *(undefined **)(puVar2 + 4) = puVar2;
      puVar2 = puVar2 + 8;
      OS_SPIN_UNLOCK_IRQRESTORE(puVar5,auStack_24);
    } while (puVar5 != puVar6);
    puVar1 = puVar1 + 0x40;
  } while ((undefined4 *)(&UNK_002965ac + param_1) != puVar5);
  pcVar3 = &DAT_002965f8 + param_1;
  do {
    pcVar4 = pcVar3 + 0xc;
    __memzero(pcVar3);
    pcVar3 = pcVar4;
  } while (pcVar4 != "Set_RBIST_Capture_Start" + param_1);
  return 0;
}

