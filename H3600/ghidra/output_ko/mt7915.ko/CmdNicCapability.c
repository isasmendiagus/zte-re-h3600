// module: mt7915.ko
// function: CmdNicCapability @ 0x1c4b40
// size: 196 bytes
//

undefined4 CmdNicCapability(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = AndesAllocCmdMsg(param_1,0);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x9ed0000,0x1c0007,0,0,EventExtNicCapability);
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdNicCapability",uVar2);
  }
  return uVar2;
}

