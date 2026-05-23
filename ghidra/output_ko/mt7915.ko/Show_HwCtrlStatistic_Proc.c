// module: mt7915.ko
// function: Show_HwCtrlStatistic_Proc @ 0xb27b0
// size: 340 bytes
//

undefined4 Show_HwCtrlStatistic_Proc(int param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  undefined4 *puVar4;
  int *piVar5;
  uint uVar6;
  
  if ((0 < DebugLevel) &&
     (printk("\tHwCtrlTask Totaol Ref. Cnt: %d\n",*(undefined4 *)(param_1 + 0x285cdc)),
     0 < DebugLevel)) {
    printk("\tHwCtrlTask CMD Statistic:\n");
  }
  if (HwCmdTable._0_4_ != 0) {
    uVar6 = 0;
    piVar5 = (int *)HwCmdTable._0_4_;
    do {
      iVar1 = *piVar5;
      if (iVar1 != 0x41) {
        uVar3 = 0;
        piVar2 = piVar5;
        do {
          if (0 < DebugLevel) {
            printk("\tCMDID: %d, Handler: %p, RfCnt: %d\n",iVar1,piVar2[1],piVar2[2]);
          }
          uVar3 = uVar3 + 1 & 0xff;
          iVar1 = piVar5[uVar3 * 3];
          piVar2 = piVar5 + uVar3 * 3;
        } while (iVar1 != 0x41);
      }
      uVar6 = uVar6 + 1 & 0xff;
      piVar5 = *(int **)(HwCmdTable + uVar6 * 4);
    } while (piVar5 != (int *)0x0);
  }
  _raw_spin_lock_bh(param_1 + 0x285ca8);
  if (0 < DebugLevel) {
    printk("\tQueSize: %d\n",*(undefined4 *)(param_1 + 0x285c98));
  }
  for (puVar4 = *(undefined4 **)(param_1 + 0x285c9c); puVar4 != (undefined4 *)0x0;
      puVar4 = (undefined4 *)puVar4[0xf]) {
    if (0 < DebugLevel) {
      printk("\tTYPE:%d, CID:%d\n",*puVar4,puVar4[1]);
    }
  }
  _raw_spin_unlock_bh(param_1 + 0x285ca8);
  return 1;
}

