// module: mt7915.ko
// function: CmdExtSER @ 0x1c7ec0
// size: 276 bytes
//

undefined4 CmdExtSER(undefined4 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  iVar2 = AndesAllocCmdMsg(param_1,4);
  if (iVar2 == 0) {
    uVar3 = 3;
  }
  else {
    local_34 = CONCAT13(0x81,CONCAT12(0xed,(undefined2)local_34));
    local_30 = CONCAT31(local_30._1_3_,8);
    AndesInitCmdMsg(iVar2,local_34,local_30,local_2c,local_28,local_24);
    uVar1 = local_38;
    local_38._3_1_ = SUB41(uVar1,3);
    local_38._0_3_ = CONCAT12(param_4,CONCAT11(param_3,param_2));
    AndesAppendCmdMsg(iVar2,&local_38,4);
    if (0 < DebugLevel) {
      printk("%s: action=%d ser_set=%d\n","CmdExtSER",local_38 & 0xff,local_38._1_1_);
    }
    uVar3 = AndesSendCmdMsg(param_1,iVar2);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdExtSER",uVar3);
  }
  return uVar3;
}

