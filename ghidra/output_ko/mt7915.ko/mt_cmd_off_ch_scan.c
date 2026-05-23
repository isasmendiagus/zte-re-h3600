// module: mt7915.ko
// function: mt_cmd_off_ch_scan @ 0x1b9ba0
// size: 304 bytes
//

undefined4 mt_cmd_off_ch_scan(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (2 < DebugLevel) {
    printk("[%s] dispath CMD start\n","mt_cmd_off_ch_scan");
  }
  iVar1 = AndesAllocCmdMsg(param_1,0x10);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x9aed0000,9,0,0,EventExtCmdResult);
    AndesAppendCmdMsg(iVar1,param_2,0x10);
    uVar2 = chip_cmd_tx(param_1,iVar1);
    if (DebugLevel < 3) {
      return uVar2;
    }
    printk("%s dispath CMD complete\n","mt_cmd_off_ch_scan");
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","mt_cmd_off_ch_scan",uVar2);
  }
  return uVar2;
}

