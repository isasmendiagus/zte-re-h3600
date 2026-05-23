// module: mt7915.ko
// function: mt_cmd_ext_twt_agrt_update @ 0x1bcb60
// size: 320 bytes
//

undefined4
mt_cmd_ext_twt_agrt_update
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_c = param_2;
  uStack_8 = param_3;
  uStack_4 = param_4;
  iVar1 = AndesAllocCmdMsg(param_1,0x2c);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    os_zero_mem(&local_54,0x2c);
    os_move_mem(&local_54,&local_c,0x2c);
    AndesInitCmdMsg(iVar1,0x94ed0000,0x8000d,0,0,EventExtCmdResult);
    AndesAppendCmdMsg(iVar1,&local_54,0x2c);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","mt_cmd_ext_twt_agrt_update",uVar2);
  }
  return uVar2;
}

