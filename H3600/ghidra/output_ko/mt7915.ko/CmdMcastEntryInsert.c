// module: mt7915.ko
// function: CmdMcastEntryInsert @ 0x1c7774
// size: 324 bytes
//

uint CmdMcastEntryInsert(undefined4 param_1,undefined4 *param_2,undefined1 param_3,
                        undefined1 param_4,undefined4 *param_5,undefined4 param_6,undefined2 param_7
                        )

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 local_3c;
  undefined2 local_38;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined4 local_30;
  undefined2 local_2c;
  undefined2 local_2a;
  
  os_zero_mem(&local_3c,0x14);
  iVar1 = AndesAllocCmdMsg(param_1,0x14);
  if (iVar1 == 0) {
    uVar3 = 3;
    uVar2 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x53ed0002,8,0,0,0);
    if (param_2 == (undefined4 *)0x0) {
      uVar3 = 1;
      uVar2 = 1;
    }
    else {
      local_3c = *param_2;
      local_38 = *(undefined2 *)(param_2 + 1);
      if (param_5 != (undefined4 *)0x0) {
        local_30 = *param_5;
        local_2c = *(undefined2 *)(param_5 + 1);
        local_2a = param_7;
        local_34 = 1;
      }
      local_36 = param_3;
      local_35 = param_4;
      AndesAppendCmdMsg(iVar1,&local_3c,0x14);
      uVar2 = AndesSendCmdMsg(param_1,iVar1);
      uVar3 = uVar2 & 0xff;
    }
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdMcastEntryInsert",uVar2);
  }
  return uVar3;
}

