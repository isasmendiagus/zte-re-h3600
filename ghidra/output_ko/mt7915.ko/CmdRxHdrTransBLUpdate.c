// module: mt7915.ko
// function: CmdRxHdrTransBLUpdate @ 0x1c79fc
// size: 256 bytes
//

undefined4
CmdRxHdrTransBLUpdate(undefined4 param_1,undefined1 param_2,undefined1 param_3,undefined2 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  code *local_24;
  
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_24 = CmdRxHdrTransBLUpdateRsp;
    local_34 = CONCAT13(0x47,CONCAT12(0xed,(undefined2)local_34));
    local_30 = CONCAT31(local_30._1_3_,0xf);
    local_30 = CONCAT22(8,(undefined2)local_30);
    AndesInitCmdMsg(iVar1,local_34,local_30,local_2c,local_28,CmdRxHdrTransBLUpdateRsp);
    local_3c = CONCAT22(local_3c._2_2_,0x101);
    local_38 = CONCAT22(param_4,CONCAT11(param_3,param_2));
    AndesAppendCmdMsg(iVar1,&local_3c,8);
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdRxHdrTransBLUpdate",uVar2);
  }
  return uVar2;
}

