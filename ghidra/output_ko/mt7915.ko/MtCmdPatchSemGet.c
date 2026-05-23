// module: mt7915.ko
// function: MtCmdPatchSemGet @ 0x1b7ea8
// size: 220 bytes
//

undefined4 MtCmdPatchSemGet(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_44;
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
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_40._0_3_ = CONCAT12(0x10,(undefined2)local_40);
    local_3c = CONCAT31(local_3c._1_3_,0x17);
    local_2c = local_40;
    uStack_28 = local_3c;
    uStack_24 = local_38;
    uStack_20 = local_34;
    local_1c = CmdPatchSemRsp;
    AndesInitCmdMsg(iVar1,local_40,local_3c,local_38,local_34,CmdPatchSemRsp);
    local_44 = param_2;
    AndesAppendCmdMsg(iVar1,&local_44,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdPatchSemGet",uVar2);
  }
  return uVar2;
}

