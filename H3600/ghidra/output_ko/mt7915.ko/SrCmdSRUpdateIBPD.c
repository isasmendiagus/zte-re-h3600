// module: mt7915.ko
// function: SrCmdSRUpdateIBPD @ 0x1701ac
// size: 220 bytes
//

undefined4 SrCmdSRUpdateIBPD(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 == 0) {
    uVar2 = 2;
  }
  else {
    PrintSrCmdSrIBPD(param_2);
    iVar1 = AndesAllocCmdMsg(param_1,0x14);
    if (iVar1 == 0) {
      uVar2 = 3;
    }
    else {
      AndesInitCmdMsg(iVar1,0xa8ed0000,8,0,0,0);
      AndesAppendCmdMsg(iVar1,param_2,0x14);
      uVar2 = AndesSendCmdMsg(param_1,iVar1);
    }
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","SrCmdSRUpdateIBPD",uVar2);
  }
  return uVar2;
}

