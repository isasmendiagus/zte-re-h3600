// module: mt7915.ko
// function: fp_dump_all_sw_queue @ 0xd39f4
// size: 436 bytes
//

undefined4 fp_dump_all_sw_queue(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  
  if (0 < DebugLevel) {
    printk("tx flow control:%d\n",*(uint *)(param_1 + 0x285b8c) & 1);
  }
  iVar5 = 0;
  iVar3 = param_1 + 0x285b3c;
  puVar4 = (undefined4 *)(param_1 + 0x285af4);
  iVar6 = 0;
  do {
    OS_SPIN_LOCK_BH(iVar3);
    if ((0 < DebugLevel) && (printk("mgmt_que[%d] number:%d\n",iVar6,puVar4[0x18]), 0 < DebugLevel))
    {
      printk("mgmt_post_que[%d] number:%d\n",iVar6,puVar4[0x20]);
    }
    OS_SPIN_UNLOCK_BH(iVar3);
    OS_SPIN_LOCK_BH(iVar3 + -0x10);
    if ((((0 < DebugLevel) && (printk("fp_que[%d] number:%d\n",iVar6,*puVar4), 0 < DebugLevel)) &&
        (printk("fp_post_que[%d] number:%d\n",iVar6,puVar4[8]), 0 < DebugLevel)) &&
       (printk("tx flow block state[%d]:%d\n",iVar6,
               *(uint *)(*(int *)(param_1 + 0x285b90) + iVar5) & 1), 0 < DebugLevel)) {
      iVar1 = 0;
      for (piVar2 = *(int **)(*(int *)(param_1 + 0x285b94) + iVar6 * 8);
          piVar2 != (int *)(*(int *)(param_1 + 0x285b94) + iVar6 * 8); piVar2 = (int *)*piVar2) {
        iVar1 = iVar1 + 1;
      }
      printk("tx flow block dev number[%d]:%d\n",iVar6,iVar1);
    }
    iVar5 = iVar5 + 4;
    OS_SPIN_UNLOCK_BH(iVar3 + -0x10);
    iVar6 = iVar6 + 1;
    iVar3 = iVar3 + 4;
    puVar4 = puVar4 + 4;
  } while (iVar5 != 8);
  return 0;
}

