// module: mt7915.ko
// function: CmdExtGeneralTestOn @ 0x1c7b00
// size: 320 bytes
//

undefined4 CmdExtGeneralTestOn(undefined4 param_1,undefined1 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_34;
  uint local_30;
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
    local_2c = CONCAT13(0x41,CONCAT12(0xed,(undefined2)local_2c));
    local_28 = CONCAT31(local_28._1_3_,0xf);
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,CmdExtGeneralTestRsp);
    local_34 = CONCAT22(local_34._2_2_,0x101);
    local_30 = CONCAT31(local_30._1_3_,param_2);
    AndesAppendCmdMsg(iVar1,&local_34,8);
    if ((2 < DebugLevel) &&
       (printk("%s: CmdExtGeneralTest:\n","CmdExtGeneralTestOn"), 2 < DebugLevel)) {
      printk("%s: ucCategory=%d, ucAction=%d, ucSwitchMode=%d\n","CmdExtGeneralTestOn",
             local_34 & 0xff,local_34._1_1_,local_30 & 0xff);
    }
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdExtGeneralTestOn",uVar2);
  }
  return uVar2;
}

