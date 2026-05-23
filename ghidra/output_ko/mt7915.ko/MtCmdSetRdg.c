// module: mt7915.ko
// function: MtCmdSetRdg @ 0x1b7690
// size: 228 bytes
//

int MtCmdSetRdg(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  if (iVar1 == 0) {
    iVar1 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x3fed0000,8,0,0,0);
    AndesAppendCmdMsg(iVar1,param_2,0xc);
    iVar1 = chip_cmd_tx(param_1,iVar1);
    if (iVar1 == 0) {
      return 0;
    }
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdSetRdg",iVar1);
  }
  return iVar1;
}

