// module: mt7915.ko
// function: CmdHIFLoopbackReq @ 0x1c44cc
// size: 256 bytes
//

undefined4 CmdHIFLoopbackReq(undefined4 param_1,uint param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  code *local_1c;
  
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_1c = CmdHIFLoopbackRsp;
    local_2c._0_3_ = CONCAT12(0x20,(undefined2)local_2c);
    local_28 = CONCAT31(local_28._1_3_,0x17);
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,CmdHIFLoopbackRsp);
    local_30 = param_2 & 0xffff | param_3 << 0x10;
    if (0 < DebugLevel) {
      printk("loopback value=0x%x\n");
    }
    AndesAppendCmdMsg(iVar1,&local_30,4);
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (0 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdHIFLoopbackReq",uVar2);
  }
  return uVar2;
}

