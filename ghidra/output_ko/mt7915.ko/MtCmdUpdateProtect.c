// module: mt7915.ko
// function: MtCmdUpdateProtect @ 0x1b75a4
// size: 232 bytes
//

undefined4 MtCmdUpdateProtect(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x3eed0000,0x8000f,0,0,EventExtCmdResult);
    AndesAppendCmdMsg(iVar1,param_2,0xc);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdUpdateProtect",uVar2);
  }
  return uVar2;
}

