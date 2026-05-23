// module: mt7915.ko
// function: CmdRxHdrTransUpdate @ 0x1c7450
// size: 284 bytes
//

undefined4
CmdRxHdrTransUpdate(undefined4 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                   undefined1 param_5,char param_6)

{
  int iVar1;
  undefined4 uVar2;
  int local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  code *local_2c;
  
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_2c = CmdRxHdrTransUpdateRsp;
    local_38 = CONCAT22(8,(undefined2)local_38);
    local_3c = CONCAT13(0x47,CONCAT12(0xed,(undefined2)local_3c));
    local_38 = CONCAT31(local_38._1_3_,0xf);
    AndesInitCmdMsg(iVar1,local_3c,local_38,local_34,local_30,CmdRxHdrTransUpdateRsp);
    local_44 = (uint)CONCAT12(param_4,CONCAT11(param_3,param_2)) << 8;
    local_40 = CONCAT31(CONCAT21((ushort)local_40._3_1_ << 8,param_6 == '\0'),param_5);
    AndesAppendCmdMsg(iVar1,&local_44,8);
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdRxHdrTransUpdate",uVar2);
  }
  return uVar2;
}

