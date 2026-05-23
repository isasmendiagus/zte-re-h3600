// module: mt7915.ko
// function: MtCmdRestartDLReq @ 0x1b7aa4
// size: 432 bytes
//

undefined4 MtCmdRestartDLReq(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_44;
  undefined4 local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  undefined4 local_30;
  undefined4 local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  code *local_1c;
  
  uVar1 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar1 = uVar1 & 0x1000000;
  if (uVar1 == 0) {
    local_40 = uVar1;
    local_3c = uVar1;
    local_38 = uVar1;
    local_34 = uVar1;
    iVar2 = AndesAllocCmdMsg(param_1,0);
    if (iVar2 == 0) {
      uVar3 = 3;
    }
    else {
      local_40._0_3_ = CONCAT12(0xef,(undefined2)local_40);
      local_3c = CONCAT31(local_3c._1_3_,0x17);
      local_38 = CONCAT22(local_38._2_2_,7000);
      local_2c = local_40;
      local_28 = local_3c;
      local_24 = local_38;
      local_20 = local_34;
      local_1c = CmdReStartDLRsp;
      AndesInitCmdMsg(iVar2,local_40,local_3c,local_38,local_34,CmdReStartDLRsp);
      uVar3 = chip_cmd_tx(param_1,iVar2);
    }
    if (3 < DebugLevel) {
      printk("%s:(ret = %d)\n","MtCmdRestartDLReqWithRsp",uVar3);
    }
  }
  else {
    local_2c = 0;
    local_28 = 0;
    local_24 = 0;
    local_20 = 0;
    local_1c = (code *)0x0;
    local_44 = 1;
    iVar2 = AndesAllocCmdMsg(param_1,4);
    if (iVar2 == 0) {
      uVar3 = 3;
    }
    else {
      local_2c._0_3_ = CONCAT12(4,(undefined2)local_2c);
      local_28 = CONCAT31(local_28._1_3_,8);
      local_40 = local_2c;
      local_3c = local_28;
      local_38 = local_24;
      local_34 = local_20;
      local_30 = local_1c;
      AndesInitCmdMsg(iVar2,local_2c,local_28,local_24,local_20,local_1c);
      AndesAppendCmdMsg(iVar2,&local_44,4);
      uVar3 = chip_cmd_tx(param_1,iVar2);
    }
    if (3 < DebugLevel) {
      printk("%s:(ret = %d)\n","MtCmdRestartDLReqNoRsp",uVar3);
    }
  }
  return uVar3;
}

