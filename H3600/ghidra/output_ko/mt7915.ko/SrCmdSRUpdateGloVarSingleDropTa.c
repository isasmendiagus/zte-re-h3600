// module: mt7915.ko
// function: SrCmdSRUpdateGloVarSingleDropTa @ 0x16e8f4
// size: 228 bytes
//

undefined4
SrCmdSRUpdateGloVarSingleDropTa
          (undefined4 param_1,int param_2,undefined1 param_3,undefined1 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 == 0) {
    uVar2 = 2;
  }
  else {
    PrintSrCmdSrGloVarSingleDropTa(param_2,param_3,param_4);
    iVar1 = AndesAllocCmdMsg(param_1,0x294);
    if (iVar1 == 0) {
      uVar2 = 3;
    }
    else {
      AndesInitCmdMsg(iVar1,0xa8ed0000,8,0,0,0);
      AndesAppendCmdMsg(iVar1,param_2,0x294);
      uVar2 = AndesSendCmdMsg(param_1,iVar1);
    }
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","SrCmdSRUpdateGloVarSingleDropTa",uVar2);
  }
  return uVar2;
}

