// module: mt7915.ko
// function: mt_cmd_set_rdd_log_config @ 0x1b9a88
// size: 276 bytes
//

undefined4
mt_cmd_set_rdd_log_config
          (undefined4 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_4d;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  undefined1 local_49;
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
  iVar1 = AndesAllocCmdMsg(param_1,5);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    os_zero_mem(&local_4d,5);
    local_48 = CONCAT13(0x9d,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT31(local_44._1_3_,8);
    local_44 = CONCAT22(0xffff,(undefined2)local_44);
    local_4c = 0;
    local_4d = 4;
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = local_38;
    local_4b = param_2;
    local_4a = param_3;
    local_49 = param_4;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,local_38);
    AndesAppendCmdMsg(iVar1,&local_4d,5);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","mt_cmd_set_rdd_log_config",uVar2);
  }
  return uVar2;
}

