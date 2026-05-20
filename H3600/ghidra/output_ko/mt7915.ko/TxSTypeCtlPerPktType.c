// module: mt7915.ko
// function: TxSTypeCtlPerPktType @ 0x1dfef0
// size: 528 bytes
//

undefined4
TxSTypeCtlPerPktType
          (int param_1,uint param_2,uint param_3,uint param_4,char param_5,char param_6,char param_7
          ,undefined1 param_8,undefined4 param_9)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  uint uVar6;
  undefined1 auStack_2c [8];
  
  iVar3 = (param_3 & 7) + param_2 * 8;
  puVar5 = &DAT_002963d0 + (iVar3 + 0x60) * 4 + param_1;
  iVar3 = (iVar3 + 0x18) * 8;
  OS_SPIN_LOCK_IRQSAVE(puVar5,auStack_2c);
  puVar2 = *(undefined4 **)(&DAT_002963d0 + param_1 + iVar3);
  while( true ) {
    if (puVar2 == (undefined4 *)(&DAT_002963d0 + iVar3 + param_1)) {
      OS_SPIN_UNLOCK_IRQRESTORE(puVar5,auStack_2c);
      if (0 < DebugLevel) {
        printk("%s: can not find TxSType(PktType = %d, PktSubType = %d, Format = %d)\n",
               "TxSTypeCtlPerPktType",param_2,param_3,param_5);
      }
      return 0xffffffff;
    }
    if (((*(byte *)((int)puVar2 + 10) == param_2) && (*(byte *)((int)puVar2 + 0xb) == param_3)) &&
       (*(char *)(puVar2 + 3) == param_5)) break;
    puVar2 = (undefined4 *)*puVar2;
  }
  iVar4 = (int)(short)param_2;
  uVar1 = 1 << (param_3 & 0xff);
  iVar3 = param_1 + iVar4 * 4;
  if (param_6 == '\0') {
    uVar6 = *(uint *)(&DAT_002965b8 + iVar3) & ~uVar1;
  }
  else {
    uVar6 = uVar1 | *(uint *)(&DAT_002965b8 + iVar3);
  }
  *(uint *)(&DAT_002965b8 + iVar3) = uVar6;
  iVar3 = param_1 + iVar4 * 4;
  iVar4 = param_1 + iVar4 * 4;
  if (param_7 == '\0') {
    uVar6 = *(uint *)(&DAT_002965c4 + iVar3) & ~uVar1;
  }
  else {
    uVar6 = uVar1 | *(uint *)(&DAT_002965c4 + iVar3);
  }
  *(uint *)(&DAT_002965c4 + iVar3) = uVar6;
  if (param_5 == '\x01') {
    *(uint *)(&DAT_002965d4 + iVar4) = uVar1 | *(uint *)(&DAT_002965d4 + iVar4);
  }
  else {
    *(uint *)(&DAT_002965d4 + iVar4) = *(uint *)(&DAT_002965d4 + iVar4) & ~uVar1;
  }
  if (param_4 < 0x40) {
    uVar1 = 1 << (param_4 & 0xff);
    *(uint *)(&DAT_002965e0 + param_1) = *(uint *)(&DAT_002965e0 + param_1) | uVar1;
    *(uint *)(&DAT_002965e4 + param_1) = *(uint *)(&DAT_002965e4 + param_1) | (int)uVar1 >> 0x1f;
  }
  else if (param_4 - 0x40 < 0x40) {
    uVar1 = 1 << (param_4 & 0xff);
    *(uint *)(&DAT_002965e8 + param_1) = *(uint *)(&DAT_002965e8 + param_1) | uVar1;
    *(uint *)(&DAT_002965ec + param_1) = *(uint *)(&DAT_002965ec + param_1) | (int)uVar1 >> 0x1f;
  }
  else {
    *(undefined4 *)(&DAT_002965e0 + param_1) = 0xffffffff;
    *(undefined4 *)(&DAT_002965e4 + param_1) = 0xffffffff;
    *(undefined4 *)(&DAT_002965e8 + param_1) = 0xffffffff;
    *(undefined4 *)(&DAT_002965ec + param_1) = 0xffffffff;
  }
  *(undefined1 *)(puVar2 + 5) = param_8;
  puVar2[6] = param_9;
  OS_SPIN_UNLOCK_IRQRESTORE(puVar5,auStack_2c);
  return 0;
}

