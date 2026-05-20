// module: mt7915.ko
// function: MtCmdCr4Set @ 0x1ba2b8
// size: 308 bytes
//

undefined4 MtCmdCr4Set(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  if (3 < DebugLevel) {
    printk(":%s: arg0(%d) arg1(%d) arg2(%d)\n","MtCmdCr4Set",param_2,param_3,param_4);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_48 = 0x1c40002;
    local_44 = CONCAT31(local_44._1_3_,8);
    local_34 = 0x1c40002;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = local_38;
    AndesInitCmdMsg(iVar1,0x1c40002,local_44,local_40,local_3c,local_38);
    os_zero_mem(&local_54,0xc);
    local_54 = param_2;
    local_50 = param_3;
    local_4c = param_4;
    AndesAppendCmdMsg(iVar1,&local_54,0xc);
    uVar2 = chip_cmd_tx(param_1,iVar1);
    if (3 < DebugLevel) {
      printk("%s: (ret = %d)\n","MtCmdCr4Set",uVar2);
    }
  }
  return uVar2;
}

