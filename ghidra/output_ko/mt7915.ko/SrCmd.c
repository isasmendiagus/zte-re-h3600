// module: mt7915.ko
// function: SrCmd @ 0x16ba14
// size: 244 bytes
//

undefined4 SrCmd(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 == 0) {
    uVar2 = 2;
  }
  else {
    if (0 < DebugLevel) {
      FUN_0016b3c0(param_2);
    }
    iVar1 = AndesAllocCmdMsg(param_1,0xc);
    if (iVar1 == 0) {
      uVar2 = 3;
    }
    else {
      AndesInitCmdMsg(iVar1,0xa8ed0000,8,0,0,0);
      AndesAppendCmdMsg(iVar1,param_2,0xc);
      uVar2 = AndesSendCmdMsg(param_1,iVar1);
    }
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","SrCmd",uVar2);
  }
  return uVar2;
}

