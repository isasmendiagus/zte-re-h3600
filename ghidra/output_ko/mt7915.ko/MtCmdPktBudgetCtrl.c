// module: mt7915.ko
// function: MtCmdPktBudgetCtrl @ 0x1bcfa0
// size: 484 bytes
//

undefined4 MtCmdPktBudgetCtrl(int param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  int iVar6;
  undefined2 local_44;
  undefined2 local_42 [15];
  
  if (2 < DebugLevel) {
    printk(":%s: bssid(%d),wcid(%d),type(%d)\n","MtCmdPktBudgetCtrl",param_2,param_3,param_4);
  }
  if (param_4 < 2) {
    iVar3 = AndesAllocCmdMsg(param_1,0x1c);
    if (iVar3 == 0) {
      uVar2 = 3;
    }
    else {
      AndesInitCmdMsg(iVar3,0x6ced0002,0x8000d,0,0,EventExtCmdResult);
      os_zero_mem(&local_44,0x1c);
      local_42[0] = (undefined2)param_3;
      local_44._0_1_ = (undefined1)param_2;
      local_44._1_1_ = 5;
      if (param_4 == 1) {
        iVar5 = 0;
        puVar4 = (undefined2 *)(param_1 + 0xa7c544);
        do {
          iVar6 = iVar5 + 2;
          puVar4 = puVar4 + 1;
          uVar1 = *puVar4;
          iVar5 = iVar5 + 1;
          (&local_44)[iVar6 * 2] = 0xffff;
          local_42[iVar6 * 2] = uVar1;
        } while (iVar5 != 5);
      }
      else {
        iVar5 = 0;
        do {
          iVar6 = iVar5 + 2;
          iVar5 = iVar5 + 1;
          (&local_44)[iVar6 * 2] = 0xffff;
          local_42[iVar6 * 2] = 0xffff;
        } while (iVar5 != 5);
      }
      AndesAppendCmdMsg(iVar3,&local_44,0x1c);
      uVar2 = chip_cmd_tx(param_1,iVar3);
      if (3 < DebugLevel) {
        printk("%s: (ret = %d)\n","MtCmdPktBudgetCtrl",uVar2);
      }
    }
  }
  else if (DebugLevel < 0) {
    uVar2 = 0;
  }
  else {
    printk(":%s: set wrong type (%d) for PBC!\n","MtCmdPktBudgetCtrl",param_4);
    uVar2 = 0;
  }
  return uVar2;
}

