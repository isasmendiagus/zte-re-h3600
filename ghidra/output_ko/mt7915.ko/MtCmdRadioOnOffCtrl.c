// module: mt7915.ko
// function: MtCmdRadioOnOffCtrl @ 0x1af18c
// size: 344 bytes
//

undefined4 MtCmdRadioOnOffCtrl(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_44 [4];
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  code *local_1c;
  
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  if (3 < DebugLevel) {
    printk("%s: On = %d\n","MtCmdRadioOnOffCtrl",param_2);
  }
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_40 = CONCAT13(5,CONCAT12(0xed,(undefined2)local_40));
    local_3c = CONCAT31(local_3c._1_3_,0xf);
    local_3c = CONCAT22(8,(undefined2)local_3c);
    local_2c = local_40;
    uStack_28 = local_3c;
    uStack_24 = local_38;
    uStack_20 = local_34;
    local_1c = EventExtCmdResult;
    AndesInitCmdMsg(iVar1,local_40,local_3c,local_38,local_34,EventExtCmdResult);
    os_zero_mem(local_44,4);
    if ((param_2 == 1) || (param_2 == 2)) {
      local_44[0] = (undefined1)param_2;
    }
    else if (-1 < DebugLevel) {
      printk("%s: unknown state, On=%d\n","MtCmdRadioOnOffCtrl",param_2);
    }
    AndesAppendCmdMsg(iVar1,local_44,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdRadioOnOffCtrl",uVar2);
  }
  return uVar2;
}

