// module: mt7915.ko
// function: MtCmdEfuseAccessRead @ 0x1aca64
// size: 288 bytes
//

undefined4
MtCmdEfuseAccessRead(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 *local_5c;
  undefined4 local_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 *local_48;
  code *local_44;
  uint local_40 [7];
  
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,0x18);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    os_zero_mem(&local_70,8);
    local_68 = CONCAT13(1,CONCAT12(0xed,(undefined2)local_68));
    local_64 = CONCAT22(0x18,(undefined2)local_64);
    local_64 = CONCAT31(local_64._1_3_,7);
    local_54 = local_68;
    uStack_50 = local_64;
    uStack_4c = local_60;
    local_44 = CmdEfuseAccessReadCb;
    local_70 = param_4;
    local_6c = param_3;
    local_5c = &local_70;
    local_48 = &local_70;
    AndesInitCmdMsg(iVar1,local_68,local_64,local_60,&local_70,CmdEfuseAccessReadCb);
    os_zero_mem(local_40,0x18);
    local_40[0] = param_2 & 0xfffffff0;
    AndesAppendCmdMsg(iVar1,local_40,0x18);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdEfuseAccessRead",uVar2);
  }
  return uVar2;
}

