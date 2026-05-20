// module: mt7915.ko
// function: MtCmdCr4Debug @ 0x1ba50c
// size: 284 bytes
//

undefined4 MtCmdCr4Debug(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_44;
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
  
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  if (0 < DebugLevel) {
    printk(":%s: option(%d)\n","MtCmdCr4Debug",param_2);
  }
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_40 = 0x3c40002;
    local_3c = CONCAT31(local_3c._1_3_,8);
    local_2c = 0x3c40002;
    uStack_28 = local_3c;
    uStack_24 = local_38;
    uStack_20 = local_34;
    local_1c = local_30;
    AndesInitCmdMsg(iVar1,0x3c40002,local_3c,local_38,local_34,local_30);
    os_zero_mem(&local_44,4);
    local_44 = param_2;
    AndesAppendCmdMsg(iVar1,&local_44,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
    if (3 < DebugLevel) {
      printk("%s: (ret = %d)\n","MtCmdCr4Debug",uVar2);
    }
  }
  return uVar2;
}

