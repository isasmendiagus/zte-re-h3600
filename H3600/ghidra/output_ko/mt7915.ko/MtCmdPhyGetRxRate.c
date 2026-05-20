// module: mt7915.ko
// function: MtCmdPhyGetRxRate @ 0x152cdc
// size: 252 bytes
//

undefined4
MtCmdPhyGetRxRate(undefined4 param_1,undefined1 param_2,undefined1 param_3,undefined2 param_4,
                 undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_30;
  undefined1 local_2f;
  undefined2 local_2e;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  code *local_1c;
  
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    os_zero_mem(&local_30,4);
    local_1c = phyStateEventDispatcher;
    local_20 = param_5;
    local_28 = CONCAT31(local_28._1_3_,5);
    local_2c = CONCAT13(0xad,CONCAT12(0xed,(undefined2)local_2c));
    local_28 = CONCAT22(8,(undefined2)local_28);
    local_30 = param_2;
    local_2f = param_3;
    local_2e = param_4;
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,param_5,phyStateEventDispatcher);
    AndesAppendCmdMsg(iVar1,&local_30,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdPhyGetRxRate",uVar2);
  }
  return uVar2;
}

