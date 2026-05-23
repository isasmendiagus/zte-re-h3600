// module: mt7915.ko
// function: mt_cmd_ext_pcie_aspm_dym_ctrl @ 0x1bca50
// size: 268 bytes
//

undefined4 mt_cmd_ext_pcie_aspm_dym_ctrl(undefined4 param_1,undefined3 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  code *local_24;
  
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    os_zero_mem(&local_4c,4);
    local_48 = CONCAT13(0x84,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT31(local_44._1_3_,8);
    local_44 = CONCAT22(8,(undefined2)local_44);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = EventExtCmdResult;
    local_4c = CONCAT13(local_4c._3_1_,param_2);
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,EventExtCmdResult);
    AndesAppendCmdMsg(iVar1,&local_4c,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","mt_cmd_ext_pcie_aspm_dym_ctrl",uVar2);
  }
  return uVar2;
}

