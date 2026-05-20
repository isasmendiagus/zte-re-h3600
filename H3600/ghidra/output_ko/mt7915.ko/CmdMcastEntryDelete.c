// module: mt7915.ko
// function: CmdMcastEntryDelete @ 0x1c78bc
// size: 316 bytes
//

uint CmdMcastEntryDelete(undefined4 param_1,undefined4 *param_2,undefined1 param_3,
                        undefined4 *param_4,undefined4 param_5,undefined2 param_6)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 local_44;
  undefined2 local_40;
  undefined1 local_3e;
  undefined1 local_3d;
  undefined4 local_3c;
  undefined2 local_38;
  undefined2 local_36;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  os_zero_mem(&local_44,0x10);
  iVar1 = AndesAllocCmdMsg(param_1,0x10);
  if (iVar1 == 0) {
    uVar3 = 3;
    uVar2 = 3;
  }
  else {
    local_34 = 0x54ed0002;
    local_30 = CONCAT31(local_30._1_3_,8);
    AndesInitCmdMsg(iVar1,0x54ed0002,local_30,local_2c,local_28,local_24);
    if (param_2 == (undefined4 *)0x0) {
      uVar3 = 1;
      uVar2 = 1;
    }
    else {
      local_44 = *param_2;
      local_40 = *(undefined2 *)(param_2 + 1);
      if (param_4 != (undefined4 *)0x0) {
        local_3c = *param_4;
        local_38 = *(undefined2 *)(param_4 + 1);
        local_36 = param_6;
        local_3d = 1;
      }
      local_3e = param_3;
      AndesAppendCmdMsg(iVar1,&local_44,0x10);
      uVar2 = AndesSendCmdMsg(param_1,iVar1);
      uVar3 = uVar2 & 0xff;
    }
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdMcastEntryDelete",uVar2);
  }
  return uVar3;
}

