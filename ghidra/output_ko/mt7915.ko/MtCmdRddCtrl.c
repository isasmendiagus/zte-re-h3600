// module: mt7915.ko
// function: MtCmdRddCtrl @ 0x1b949c
// size: 388 bytes
//

undefined4
MtCmdRddCtrl(undefined4 param_1,int param_2,undefined1 param_3,undefined1 param_4,undefined1 param_5
            )

{
  int iVar1;
  undefined4 uVar2;
  undefined2 uVar3;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_55;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  code *local_2c;
  
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  if (3 < DebugLevel) {
    printk("[MtCmdRddCtrl] dispath CMD start\n");
  }
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    uVar3 = 10000;
    if (param_2 != 0x33) {
      uVar3 = 0;
    }
    local_48 = CONCAT22(local_48._2_2_,uVar3);
    local_50 = CONCAT13(0x3a,CONCAT12(0xed,(undefined2)local_50));
    local_4c = CONCAT31(local_4c._1_3_,9);
    local_3c = local_50;
    uStack_38 = local_4c;
    uStack_34 = local_48;
    uStack_30 = local_44;
    local_2c = EventExtCmdResult;
    AndesInitCmdMsg(iVar1,local_50,local_4c,local_48,local_44,EventExtCmdResult);
    os_zero_mem(&local_58,8);
    local_58 = (undefined1)param_2;
    local_55 = param_5;
    local_57 = param_3;
    local_56 = param_4;
    AndesAppendCmdMsg(iVar1,&local_58,8);
    uVar2 = chip_cmd_tx(param_1,iVar1);
    if (DebugLevel < 4) {
      return uVar2;
    }
    printk("[MtCmdRddCtrl] dispath CMD complete\n");
    if (DebugLevel < 4) {
      return uVar2;
    }
    printk("[MtCmdRddCtrl] ret = %d\n",uVar2);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdRddCtrl",uVar2);
  }
  return uVar2;
}

