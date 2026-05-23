// module: mt7915.ko
// function: MtCmdPatchFinishReq @ 0x1b7f88
// size: 260 bytes
//

undefined4 MtCmdPatchFinishReq(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_44;
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
  local_44 = 0;
  if (0 < DebugLevel) {
    printk(&_LC0,"MtCmdPatchFinishReq");
  }
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_40._0_3_ = CONCAT12(7,(undefined2)local_40);
    local_3c = CONCAT31(local_3c._1_3_,0x17);
    local_2c = local_40;
    uStack_28 = local_3c;
    uStack_24 = local_38;
    uStack_20 = local_34;
    local_1c = CmdPatchFinishRsp;
    AndesInitCmdMsg(iVar1,local_40,local_3c,local_38,local_34,CmdPatchFinishRsp);
    local_44 = local_44 & 0xffffff00;
    AndesAppendCmdMsg(iVar1,&local_44,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdPatchFinishReq",uVar2);
  }
  return uVar2;
}

