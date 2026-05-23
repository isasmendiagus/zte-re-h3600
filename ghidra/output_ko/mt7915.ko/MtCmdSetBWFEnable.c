// module: mt7915.ko
// function: MtCmdSetBWFEnable @ 0x1bd188
// size: 448 bytes
//

undefined4 MtCmdSetBWFEnable(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_60 [4];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  os_zero_mem(local_60,4);
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 != 0) {
    local_5c = CONCAT13(0x6e,CONCAT12(0xed,(undefined2)local_5c));
    local_58 = CONCAT31(local_58._1_3_,8);
    local_48 = local_5c;
    uStack_44 = local_58;
    uStack_40 = local_54;
    local_3c = local_50;
    local_38 = local_4c;
    AndesInitCmdMsg(iVar1,local_5c,local_58,local_54,local_50,local_4c);
    local_60[0] = (char)param_2;
    AndesAppendCmdMsg(iVar1,local_60,4);
    if (-1 < DebugLevel) {
      printk("%s: send cmd to N9 CmdBWFEnable.ucBwfLwcEnable [%d] Enable[%d]\n","MtCmdSetBWFEnable",
             local_60[0],param_2);
    }
    chip_cmd_tx(param_1,iVar1);
    iVar1 = AndesAllocCmdMsg(param_1,4);
    if (iVar1 != 0) {
      local_5c = CONCAT22(local_5c._2_2_,2);
      local_34 = local_5c;
      uStack_30 = local_58;
      uStack_2c = local_54;
      uStack_28 = local_50;
      local_24 = local_4c;
      AndesInitCmdMsg(iVar1,local_5c,local_58,local_54,local_50,local_4c);
      local_60[0] = (char)param_2;
      AndesAppendCmdMsg(iVar1,local_60,4);
      if (-1 < DebugLevel) {
        printk("%s: send cmd to CR4 CmdBWFEnable.ucBwfLwcEnable [%d] Enable[%d]\n",
               "MtCmdSetBWFEnable",local_60[0],param_2);
      }
      uVar2 = chip_cmd_tx(param_1,iVar1);
      goto LAB_001bd2e0;
    }
  }
  uVar2 = 3;
LAB_001bd2e0:
  if (0 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdSetBWFEnable",uVar2);
  }
  return uVar2;
}

