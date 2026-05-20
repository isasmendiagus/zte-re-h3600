// module: mt7915.ko
// function: TxSTypeCtlPerPkt @ 0x1dfb04
// size: 332 bytes
//

undefined4
TxSTypeCtlPerPkt(int param_1,uint param_2,uint param_3,int param_4,char param_5,undefined1 param_6,
                undefined4 param_7)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  undefined1 auStack_2c [8];
  
  puVar4 = &DAT_002963d0 + ((param_2 & 0xf) + 0x20) * 4 + param_1;
  OS_SPIN_LOCK_IRQSAVE(puVar4,auStack_2c);
  iVar1 = (param_2 & 0xf) * 8;
  puVar5 = *(undefined4 **)(&DAT_002963d0 + param_1 + iVar1);
  while( true ) {
    if (puVar5 == (undefined4 *)(&DAT_002963d0 + iVar1 + param_1)) {
      OS_SPIN_UNLOCK_IRQRESTORE(puVar4,auStack_2c);
      if (0 < DebugLevel) {
        printk("%s: can not find TxSType(PktPID = %d, Format = %d)\n","TxSTypeCtlPerPkt",param_2,
               param_3);
      }
      return 0xffffffff;
    }
    if ((*(byte *)((int)puVar5 + 9) == param_2) && (*(byte *)(puVar5 + 3) == param_3)) break;
    puVar5 = (undefined4 *)*puVar5;
  }
  uVar3 = 1 << (param_2 & 0xff);
  if (param_4 == 0) {
    uVar2 = *(uint *)(&DAT_002965b0 + param_1) & ~uVar3;
  }
  else {
    uVar2 = uVar3 | *(uint *)(&DAT_002965b0 + param_1);
  }
  *(uint *)(&DAT_002965b0 + param_1) = uVar2;
  if (param_5 == '\0') {
    uVar2 = *(uint *)(&DAT_002965b4 + param_1) & ~uVar3;
  }
  else {
    uVar2 = uVar3 | *(uint *)(&DAT_002965b4 + param_1);
  }
  *(uint *)(&DAT_002965b4 + param_1) = uVar2;
  if (param_3 == 1) {
    uVar3 = uVar3 | *(uint *)(&DAT_002965d0 + param_1);
  }
  else {
    uVar3 = *(uint *)(&DAT_002965d0 + param_1) & ~uVar3;
  }
  *(uint *)(&DAT_002965d0 + param_1) = uVar3;
  *(undefined1 *)(puVar5 + 5) = param_6;
  puVar5[6] = param_7;
  OS_SPIN_UNLOCK_IRQRESTORE(puVar4,auStack_2c);
  return 0;
}

