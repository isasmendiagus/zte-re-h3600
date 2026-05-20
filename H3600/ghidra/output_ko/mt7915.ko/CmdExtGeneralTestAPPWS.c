// module: mt7915.ko
// function: CmdExtGeneralTestAPPWS @ 0x1c7d9c
// size: 288 bytes
//

undefined4 CmdExtGeneralTestAPPWS(undefined4 param_1,undefined1 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  code *local_1c;
  
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_1c = CmdExtGeneralTestRsp;
    local_28 = CONCAT22(8,(undefined2)local_28);
    local_2c = CONCAT13(0x41,CONCAT12(0xed,(undefined2)local_2c));
    local_28 = CONCAT31(local_28._1_3_,0xf);
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,CmdExtGeneralTestRsp);
    local_34._0_2_ = CONCAT11(param_2,2);
    AndesAppendCmdMsg(iVar1,&local_34,8);
    if (0 < DebugLevel) {
      printk("%s: ucCategory=%d, ucAction=%d\n","CmdExtGeneralTestAPPWS",local_34 & 0xff,
             local_34._1_1_);
    }
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdExtGeneralTestAPPWS",uVar2);
  }
  return uVar2;
}

