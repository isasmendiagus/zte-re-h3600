// module: mt7915.ko
// function: mt_cmd_wo_query @ 0x1ba62c
// size: 264 bytes
//

undefined4 mt_cmd_wo_query(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 local_4c [2];
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  if (3 < DebugLevel) {
    printk("%s: option(0x%x)\n","mt_cmd_wo_query",param_2);
  }
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = local_38;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,local_38);
    os_zero_mem(local_4c,4);
    local_4c[0] = param_3;
    AndesAppendCmdMsg(iVar1,local_4c,4);
    call_fw_cmd_notifieriers(param_2,param_1,*(undefined4 *)(iVar1 + 0x20));
    if (DebugLevel < 4) {
      uVar2 = 0;
    }
    else {
      printk("%s: (ret = %d)\n","mt_cmd_wo_query",0);
      uVar2 = 0;
    }
  }
  return uVar2;
}

