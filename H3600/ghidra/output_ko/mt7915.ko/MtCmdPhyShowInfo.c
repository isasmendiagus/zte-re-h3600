// module: mt7915.ko
// function: MtCmdPhyShowInfo @ 0x152f18
// size: 276 bytes
//

undefined4 MtCmdPhyShowInfo(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_30;
  undefined1 local_2f;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (0 < DebugLevel) {
    printk("%s: ucPhyStateInfoCatg: %d, BandIdx: %d \n","MtCmdPhyShowInfo",param_2,param_3);
  }
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    os_zero_mem(&local_30,4);
    local_28 = CONCAT31(local_28._1_3_,8);
    local_2c = CONCAT13(0xad,CONCAT12(0xed,(undefined2)local_2c));
    local_28 = CONCAT22(0xffff,(undefined2)local_28);
    local_30 = (undefined1)param_2;
    local_2f = (undefined1)param_3;
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,local_1c);
    AndesAppendCmdMsg(iVar1,&local_30,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdPhyShowInfo",uVar2);
  }
  return uVar2;
}

