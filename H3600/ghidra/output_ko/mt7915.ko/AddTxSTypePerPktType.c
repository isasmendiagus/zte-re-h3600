// module: mt7915.ko
// function: AddTxSTypePerPktType @ 0x1dfc54
// size: 404 bytes
//

undefined4 AddTxSTypePerPktType(int param_1,uint param_2,uint param_3,uint param_4,int param_5)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined1 auStack_30 [4];
  int *local_2c [2];
  
  local_2c[0] = (int *)0x0;
  os_alloc_mem(0,local_2c,0x1c);
  if (local_2c[0] == (int *)0x0) {
    if (DebugLevel < 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("can not allocate TxS Type\n");
      uVar1 = 0xffffffff;
    }
  }
  else {
    iVar3 = (param_3 & 7) + param_2 * 8;
    puVar4 = &DAT_002963d0 + (iVar3 + 0x60) * 4 + param_1;
    iVar5 = param_1 + iVar3 * 8;
    OS_SPIN_LOCK_IRQSAVE(puVar4,auStack_30);
    for (puVar6 = *(undefined4 **)(&DAT_00296490 + iVar5);
        puVar6 != (undefined4 *)(&DAT_002963d0 + (iVar3 + 0x18) * 8 + param_1);
        puVar6 = (undefined4 *)*puVar6) {
      if (((*(byte *)((int)puVar6 + 10) == param_2) && (*(byte *)((int)puVar6 + 0xb) == param_3)) &&
         (*(byte *)(puVar6 + 3) == param_4)) {
        if (-1 < DebugLevel) {
          printk("%s: already registered TxSType (PktType = %d, PktSubType = %d, Format = %d\n",
                 "AddTxSTypePerPktType",param_2,param_3,param_4);
        }
        OS_SPIN_UNLOCK_IRQRESTORE(puVar4,auStack_30);
        os_free_mem(local_2c[0]);
        return 0xffffffff;
      }
    }
    *(char *)((int)local_2c[0] + 10) = (char)param_2;
    *(char *)((int)local_2c[0] + 0xb) = (char)param_3;
    *(char *)(local_2c[0] + 3) = (char)param_4;
    local_2c[0][4] = param_5;
    *(undefined1 *)(local_2c[0] + 2) = 1;
    piVar2 = *(int **)(&DAT_00296494 + iVar5);
    iVar3 = *piVar2;
    local_2c[0][1] = (int)piVar2;
    *local_2c[0] = iVar3;
    *(int **)(*piVar2 + 4) = local_2c[0];
    *piVar2 = (int)local_2c[0];
    OS_SPIN_UNLOCK_IRQRESTORE(puVar4,auStack_30);
    uVar1 = 0;
  }
  return uVar1;
}

