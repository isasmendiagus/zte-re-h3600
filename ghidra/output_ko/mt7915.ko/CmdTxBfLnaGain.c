// module: mt7915.ko
// function: CmdTxBfLnaGain @ 0x1b1744
// size: 284 bytes
//

undefined4 CmdTxBfLnaGain(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_44;
  undefined1 local_43;
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
  if (2 < DebugLevel) {
    printk("%s::: LNA gain setting for iBF phase calibration : %d\n","CmdTxBfLnaGain",param_2);
  }
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_40 = CONCAT13(0x1e,CONCAT12(0xed,(undefined2)local_40));
    local_3c = CONCAT31(local_3c._1_3_,8);
    local_3c = CONCAT22(0xffff,(undefined2)local_3c);
    local_43 = (undefined1)param_2;
    local_44 = 0x10;
    local_2c = local_40;
    uStack_28 = local_3c;
    uStack_24 = local_38;
    uStack_20 = local_34;
    local_1c = EventExtCmdResult;
    AndesInitCmdMsg(iVar1,local_40,local_3c,local_38,local_34,EventExtCmdResult);
    AndesAppendCmdMsg(iVar1,&local_44,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdTxBfLnaGain",uVar2);
  }
  return uVar2;
}

