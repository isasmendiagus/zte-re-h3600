// module: mt7915.ko
// function: CmdInitAccessRegRead @ 0x1c43a8
// size: 288 bytes
//

undefined4 CmdInitAccessRegRead(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  code *local_1c;
  
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  if (3 < DebugLevel) {
    printk("%s: address = %x\n","CmdInitAccessRegRead",param_2);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_1c = CmdInitAccessRegReadCb;
    local_28 = CONCAT31(local_28._1_3_,7);
    local_2c._0_3_ = CONCAT12(3,(undefined2)local_2c);
    local_28 = CONCAT22(8,(undefined2)local_28);
    local_20 = param_3;
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,param_3,CmdInitAccessRegReadCb);
    os_zero_mem(&local_38,0xc);
    local_38 = local_38 & 0xffffff00;
    local_34 = param_2;
    AndesAppendCmdMsg(iVar1,&local_38,0xc);
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdInitAccessRegRead",uVar2);
  }
  return uVar2;
}

