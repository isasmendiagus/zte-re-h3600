// module: mt7915.ko
// function: CmdInitAccessRegWrite @ 0x1c428c
// size: 280 bytes
//

undefined4 CmdInitAccessRegWrite(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (3 < DebugLevel) {
    printk("%s: address = %x, data = %x\n","CmdInitAccessRegWrite",param_2,param_3);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_2c._0_3_ = CONCAT12(3,(undefined2)local_2c);
    local_28 = CONCAT31(local_28._1_3_,8);
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,local_1c);
    os_zero_mem(&local_38,0xc);
    local_38 = CONCAT31(local_38._1_3_,1);
    local_34 = param_2;
    local_30 = param_3;
    AndesAppendCmdMsg(iVar1,&local_38,0xc);
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdInitAccessRegWrite",uVar2);
  }
  return uVar2;
}

