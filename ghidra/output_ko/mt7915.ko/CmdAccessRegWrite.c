// module: mt7915.ko
// function: CmdAccessRegWrite @ 0x1c484c
// size: 268 bytes
//

undefined4 CmdAccessRegWrite(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  if (3 < DebugLevel) {
    printk("%s: address = %x, data = %x\n","CmdAccessRegWrite",param_2,param_3);
  }
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_30 = CONCAT31(local_30._1_3_,8);
    local_34._0_3_ = CONCAT12(0xc2,(undefined2)local_34);
    AndesInitCmdMsg(iVar1,local_34,local_30,local_2c,local_28,local_24);
    os_zero_mem(&local_3c,8);
    local_3c = param_2;
    local_38 = param_3;
    AndesAppendCmdMsg(iVar1,&local_3c,8);
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdAccessRegWrite",uVar2);
  }
  return uVar2;
}

