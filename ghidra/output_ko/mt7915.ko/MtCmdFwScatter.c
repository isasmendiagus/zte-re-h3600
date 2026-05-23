// module: mt7915.ko
// function: MtCmdFwScatter @ 0x1b7dc0
// size: 228 bytes
//

undefined4
MtCmdFwScatter(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = AndesAllocCmdMsg(param_1,param_3);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0xee0000,0x10,0,0,0);
    AndesAppendCmdMsg(iVar1,param_2,param_3);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(scatter = %d, ret = %d)\n","MtCmdFwScatter",param_4,uVar2);
  }
  return uVar2;
}

