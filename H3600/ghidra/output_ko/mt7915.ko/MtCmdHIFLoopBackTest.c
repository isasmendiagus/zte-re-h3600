// module: mt7915.ko
// function: MtCmdHIFLoopBackTest @ 0x1b79ac
// size: 244 bytes
//

undefined4 MtCmdHIFLoopBackTest(undefined4 param_1,undefined2 param_2,undefined2 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 local_44;
  undefined2 local_42;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 local_1c;
  
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  os_zero_mem(&local_44,4);
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_40._0_3_ = CONCAT12(0x20,(undefined2)local_40);
    local_3c = CONCAT31(local_3c._1_3_,0x17);
    local_2c = local_40;
    uStack_28 = local_3c;
    uStack_24 = local_38;
    uStack_20 = local_34;
    local_1c = local_30;
    AndesInitCmdMsg(iVar1,local_40,local_3c,local_38,local_34,local_30);
    local_44 = param_2;
    local_42 = param_3;
    AndesAppendCmdMsg(iVar1,&local_44,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdHIFLoopBackTest",uVar2);
  }
  return uVar2;
}

