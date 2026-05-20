// module: mt7915.ko
// function: CmdITxBfPhaseCal @ 0x1b15e0
// size: 352 bytes
//

undefined4
CmdITxBfPhaseCal(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                byte param_5,byte param_6)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_55;
  undefined1 local_54;
  undefined1 local_53;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  code *local_2c;
  
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  uVar2 = (uint)param_5;
  uVar3 = (uint)param_6;
  if (2 < DebugLevel) {
    printk("%s::: Enable iBF phase calibration : ucGroup = %d, ucGroup_L_M_H = %d, fgSX2 = %d\n",
           "CmdITxBfPhaseCal",param_2,param_3,param_4);
  }
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar4 = 3;
  }
  else {
    os_zero_mem(&local_58);
    local_50 = CONCAT13(0x1e,CONCAT12(0xed,(undefined2)local_50));
    local_4c = CONCAT31(local_4c._1_3_,8);
    local_4c = CONCAT22(0xffff,(undefined2)local_4c);
    local_56 = (undefined1)param_2;
    local_57 = (undefined1)param_3;
    local_55 = (undefined1)param_4;
    local_3c = local_50;
    uStack_38 = local_4c;
    uStack_34 = local_48;
    uStack_30 = local_44;
    local_2c = EventExtCmdResult;
    local_54 = (undefined1)uVar2;
    local_58 = 0xe;
    local_53 = (undefined1)uVar3;
    AndesInitCmdMsg(iVar1,local_50,local_4c,local_48,local_44,EventExtCmdResult,uVar2,uVar3);
    AndesAppendCmdMsg(iVar1,&local_58,8);
    uVar4 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdITxBfPhaseCal",uVar4);
  }
  return uVar4;
}

