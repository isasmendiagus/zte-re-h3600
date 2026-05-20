// module: mt7915.ko
// function: MtCmdTpcUlUtVarCfg @ 0x1bb084
// size: 312 bytes
//

undefined4
MtCmdTpcUlUtVarCfg(undefined4 param_1,undefined1 param_2,undefined1 param_3,undefined2 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  if (-1 < DebugLevel) {
    printk("u1EntryIdx: %d, VarType:%d, Value: %d\n");
  }
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    os_zero_mem(&local_58);
    local_50 = CONCAT13(0xa1,CONCAT12(0xed,(undefined2)local_50));
    local_4c = CONCAT31(local_4c._1_3_,8);
    local_4c = CONCAT22(0xffff,(undefined2)local_4c);
    local_54 = CONCAT22(local_54._2_2_,param_4);
    local_3c = local_50;
    uStack_38 = local_4c;
    uStack_34 = local_48;
    uStack_30 = local_44;
    local_2c = local_40;
    local_58 = CONCAT31(CONCAT12(local_58._3_1_,CONCAT11(param_3,param_2)),9);
    AndesInitCmdMsg(iVar1,local_50,local_4c,local_48,local_44,local_40);
    AndesAppendCmdMsg(iVar1,&local_58,8);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdTpcUlUtVarCfg",uVar2);
  }
  return uVar2;
}

