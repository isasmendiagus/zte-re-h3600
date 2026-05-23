// module: mt7915.ko
// function: MtCmdFwDecompressStart @ 0x1b81b8
// size: 432 bytes
//

undefined4 MtCmdFwDecompressStart(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  code *local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  code *local_24;
  
  uVar2 = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  iVar1 = AndesAllocCmdMsg(param_1,0x38);
  if (iVar1 == 0) {
    uVar3 = 3;
  }
  else {
    local_38 = CmdStartDLRsp;
    local_48._0_3_ = CONCAT12(0x30,(undefined2)local_48);
    local_44 = CONCAT31(local_44._1_3_,0x17);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = CmdStartDLRsp;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,CmdStartDLRsp);
    local_4c = *param_2;
    AndesAppendCmdMsg(iVar1,&local_4c,4);
    local_4c = param_2[1];
    AndesAppendCmdMsg(iVar1,&local_4c,4);
    local_4c = param_2[2];
    AndesAppendCmdMsg(iVar1,&local_4c,4);
    local_4c = param_2[3];
    AndesAppendCmdMsg(iVar1,&local_4c,4);
    local_4c = param_2[4];
    AndesAppendCmdMsg(iVar1,&local_4c,4);
    puVar4 = param_2;
    if (param_2[4] != 0) {
      do {
        local_4c = puVar4[5];
        uVar2 = uVar2 + 1;
        AndesAppendCmdMsg(iVar1,&local_4c,4);
        local_4c = puVar4[6];
        AndesAppendCmdMsg(iVar1,&local_4c,4);
        local_4c = puVar4[7];
        AndesAppendCmdMsg(iVar1,&local_4c,4);
        puVar4 = puVar4 + 3;
      } while (uVar2 < (uint)param_2[4]);
    }
    uVar3 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdFwDecompressStart",uVar3);
  }
  return uVar3;
}

