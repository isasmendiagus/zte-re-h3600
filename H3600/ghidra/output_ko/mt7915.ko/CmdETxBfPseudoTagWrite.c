// module: mt7915.ko
// function: CmdETxBfPseudoTagWrite @ 0x1b44ac
// size: 236 bytes
//

undefined4
CmdETxBfPseudoTagWrite(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  code *local_1c;
  
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_4c = param_2;
  uStack_48 = param_3;
  uStack_44 = param_4;
  iVar1 = AndesAllocCmdMsg(param_1,9);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_40 = CONCAT13(0x1e,CONCAT12(0xed,(undefined2)local_40));
    local_3c = CONCAT31(local_3c._1_3_,8);
    local_3c = CONCAT22(0xffff,(undefined2)local_3c);
    local_2c = local_40;
    uStack_28 = local_3c;
    uStack_24 = local_38;
    uStack_20 = local_34;
    local_1c = EventExtCmdResult;
    AndesInitCmdMsg(iVar1,local_40,local_3c,local_38,local_34,EventExtCmdResult);
    AndesAppendCmdMsg(iVar1,&local_4c,9);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (0 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfPseudoTagWrite",uVar2);
  }
  return uVar2;
}

