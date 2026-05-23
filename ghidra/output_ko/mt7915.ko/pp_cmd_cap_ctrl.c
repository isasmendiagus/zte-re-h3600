// module: mt7915.ko
// function: pp_cmd_cap_ctrl @ 0x171940
// size: 292 bytes
//

undefined4 pp_cmd_cap_ctrl(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 == (undefined1 *)0x0) {
    uVar2 = 2;
  }
  else {
    iVar1 = AndesAllocCmdMsg(param_1,4);
    if (iVar1 == 0) {
      uVar2 = 3;
    }
    else {
      if (2 < DebugLevel) {
        printk("%s: cmd_sub_id = %d, dbdc_idx %d, pp_ctrl %d, pp_auto_mode %d\n","pp_cmd_cap_ctrl",
               *param_2,param_2[1],param_2[2],param_2[3]);
      }
      AndesInitCmdMsg(iVar1,0xb6ed0000,8,0,0,0);
      AndesAppendCmdMsg(iVar1,param_2,4);
      uVar2 = AndesSendCmdMsg(param_1,iVar1);
    }
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","pp_cmd_cap_ctrl",uVar2);
  }
  return uVar2;
}

