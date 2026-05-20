// module: mt7915.ko
// function: MtCmdFwStartReq @ 0x1b8090
// size: 292 bytes
//

undefined4 MtCmdFwStartReq(undefined4 param_1,undefined4 param_2,undefined4 param_3)

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
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  if (0 < DebugLevel) {
    printk("%s: override = 0x%x, address = 0x%x\n","MtCmdFwStartReq",param_2,param_3);
  }
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_48._0_3_ = CONCAT12(2,(undefined2)local_48);
    local_44 = CONCAT31(local_44._1_3_,0x17);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = CmdStartDLRsp;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,CmdStartDLRsp);
    local_4c = param_2;
    AndesAppendCmdMsg(iVar1,&local_4c,4);
    local_4c = param_3;
    AndesAppendCmdMsg(iVar1,&local_4c,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdFwStartReq",uVar2);
  }
  return uVar2;
}

