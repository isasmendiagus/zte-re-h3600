// module: mt7915.ko
// function: mt_cmd_set_rdd_ipi_hist @ 0x1be5f0
// size: 232 bytes
//

undefined4 mt_cmd_set_rdd_ipi_hist(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0xa3ed0000,0xffff0008,0,0,0);
    AndesAppendCmdMsg(iVar1,param_2,0x14);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","mt_cmd_set_rdd_ipi_hist",uVar2);
  }
  return uVar2;
}

