// module: mt7915.ko
// function: CmdAccessRegRead @ 0x1c495c
// size: 284 bytes
//

undefined4 CmdAccessRegRead(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 *local_28;
  code *local_24;
  
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_24 = CmdAccessRegReadCb;
    local_34._0_3_ = CONCAT12(0xc2,(undefined2)local_34);
    local_30 = CONCAT22(8,(undefined2)local_30);
    local_30 = CONCAT31(local_30._1_3_,7);
    local_28 = param_3;
    AndesInitCmdMsg(iVar1,local_34,local_30,local_2c,param_3,CmdAccessRegReadCb);
    os_zero_mem(&local_3c,8);
    local_3c = param_2;
    AndesAppendCmdMsg(iVar1,&local_3c,8);
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
    if (DebugLevel < 4) {
      return uVar2;
    }
    printk("%s: address = %x, value = %x\n","CmdAccessRegRead",param_2,*param_3);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdAccessRegRead",uVar2);
  }
  return uVar2;
}

