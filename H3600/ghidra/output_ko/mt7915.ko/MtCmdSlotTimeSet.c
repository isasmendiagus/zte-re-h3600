// module: mt7915.ko
// function: MtCmdSlotTimeSet @ 0x1b4afc
// size: 284 bytes
//

undefined4
MtCmdSlotTimeSet(undefined4 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                undefined2 param_5,undefined1 param_6)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_5a;
  undefined2 local_58;
  undefined1 local_56;
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
  os_zero_mem(&local_5c);
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  if (iVar1 != 0) {
    local_50 = CONCAT13(0x28,CONCAT12(0xed,(undefined2)local_50));
    local_4c = CONCAT31(local_4c._1_3_,0xf);
    local_4c = CONCAT22(8,(undefined2)local_4c);
    local_3c = local_50;
    uStack_38 = local_4c;
    uStack_34 = local_48;
    uStack_30 = local_44;
    local_2c = EventExtCmdResult;
    AndesInitCmdMsg(iVar1,local_50,local_4c,local_48,local_44,EventExtCmdResult);
    local_58 = param_5;
    local_56 = param_6;
    local_5c = param_2;
    local_5b = param_3;
    local_5a = param_4;
    AndesAppendCmdMsg(iVar1,&local_5c,0xc);
    uVar2 = chip_cmd_tx(param_1,iVar1);
    return uVar2;
  }
  if (-1 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdSlotTimeSet",3);
  }
  return 3;
}

