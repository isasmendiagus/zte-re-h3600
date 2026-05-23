// module: mt7915.ko
// function: MtCmdThermalMode @ 0x1b9120
// size: 296 bytes
//

undefined4 MtCmdThermalMode(undefined4 param_1,undefined1 param_2,undefined1 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  code *local_14;
  
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  if (2 < DebugLevel) {
    printk("%s----------------->\n","MtCmdThermalMode");
  }
  local_3c = param_2;
  local_3b = param_3;
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 != 0) {
    local_30 = CONCAT22(local_30._2_2_,60000);
    local_38 = CONCAT13(0x79,CONCAT12(0xed,(undefined2)local_38));
    local_34 = CONCAT31(local_34._1_3_,0xf);
    local_34 = CONCAT22(0xffff,(undefined2)local_34);
    local_24 = local_38;
    uStack_20 = local_34;
    uStack_1c = local_30;
    uStack_18 = local_2c;
    local_14 = EventExtCmdResult;
    AndesInitCmdMsg(iVar1,local_38,local_34,local_30,local_2c,EventExtCmdResult);
    AndesAppendCmdMsg(iVar1,&local_3c,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
    return uVar2;
  }
  if (-1 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdThermalMode",3);
  }
  return 3;
}

