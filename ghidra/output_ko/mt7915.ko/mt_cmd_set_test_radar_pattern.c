// module: mt7915.ko
// function: mt_cmd_set_test_radar_pattern @ 0x1b9980
// size: 260 bytes
//

undefined4 mt_cmd_set_test_radar_pattern(undefined4 param_1,void *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_19c [392];
  
  iVar1 = AndesAllocCmdMsg(param_1,0x184);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    os_zero_mem(auStack_19c,0x184);
    memcpy(auStack_19c,param_2,0x184);
    AndesInitCmdMsg(iVar1,0xb2ed0000,0xffff0008,0,0,0);
    AndesAppendCmdMsg(iVar1,auStack_19c,0x184);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","mt_cmd_set_test_radar_pattern",uVar2);
  }
  return uVar2;
}

