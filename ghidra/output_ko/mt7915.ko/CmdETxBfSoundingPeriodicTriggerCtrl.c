// module: mt7915.ko
// function: CmdETxBfSoundingPeriodicTriggerCtrl @ 0x1b1ce0
// size: 412 bytes
//

undefined4
CmdETxBfSoundingPeriodicTriggerCtrl
          (undefined4 param_1,int param_2,undefined4 param_3,uint param_4,undefined1 param_5,
          undefined1 *param_6)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  undefined1 local_50;
  undefined1 local_4f;
  undefined1 local_4e;
  undefined1 local_4d;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  code *local_24;
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  if (DebugLevel < 3) {
    if (8 < param_4) {
      return 2;
    }
  }
  else {
    printk("%s: Sounding trigger enable = %d\n","CmdETxBfSoundingPeriodicTriggerCtrl",param_2);
    if (8 < param_4) {
      uVar2 = 2;
      goto LAB_001b1e58;
    }
  }
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  os_zero_mem(&local_54,0xc);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    if (param_2 == 0) {
      local_54 = 0;
    }
    else {
      local_53 = (undefined1)param_4;
      local_54 = 1;
      if (param_6 != (undefined1 *)0x0) {
        local_50 = *param_6;
        local_4f = param_6[1];
        local_4d = param_6[3];
        local_4e = param_6[2];
      }
      local_52 = param_5;
      local_4c = param_3;
    }
    local_48 = CONCAT13(0x1e,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT31(local_44._1_3_,8);
    local_44 = CONCAT22(0xffff,(undefined2)local_44);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = EventExtCmdResult;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,EventExtCmdResult);
    AndesAppendCmdMsg(iVar1,&local_54,0xc);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
LAB_001b1e58:
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfSoundingPeriodicTriggerCtrl",uVar2);
  }
  return uVar2;
}

