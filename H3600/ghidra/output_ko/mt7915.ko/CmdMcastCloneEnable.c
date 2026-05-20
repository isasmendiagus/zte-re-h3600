// module: mt7915.ko
// function: CmdMcastCloneEnable @ 0x1c7658
// size: 280 bytes
//

undefined4
CmdMcastCloneEnable(undefined4 param_1,undefined4 param_2,undefined1 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_38 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_34 = 0x52ed0002;
    local_30 = CONCAT31(local_30._1_3_,8);
    AndesInitCmdMsg(iVar1,0x52ed0002,local_30,local_2c,local_28,local_24);
    local_38._0_3_ = CONCAT12(param_3,CONCAT11((char)param_4,(char)param_2));
    if (2 < DebugLevel) {
      printk("%s: omac_idx=%d, en=%d\n","CmdMcastCloneEnable",param_4,param_2);
    }
    AndesAppendCmdMsg(iVar1,&local_38,4);
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdMcastCloneEnable",uVar2);
  }
  return uVar2;
}

