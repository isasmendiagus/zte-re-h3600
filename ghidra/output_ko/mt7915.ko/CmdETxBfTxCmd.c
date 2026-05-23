// module: mt7915.ko
// function: CmdETxBfTxCmd @ 0x1b370c
// size: 304 bytes
//

undefined4 CmdETxBfTxCmd(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    *param_2 = 0x23;
    if (0 < DebugLevel) {
      printk("%s: ucAction=0x%02X, fgTxCmdBfManual=0x%02X, ucTxCmdBfBit=0x%02X\n","CmdETxBfTxCmd",
             param_2[1],param_2[2],param_2[3]);
    }
    AndesInitCmdMsg(iVar1,0x1eed0000,0xffff0008,500,0,0);
    AndesAppendCmdMsg(iVar1,param_2,8);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfTxCmd",uVar2);
  }
  return uVar2;
}

