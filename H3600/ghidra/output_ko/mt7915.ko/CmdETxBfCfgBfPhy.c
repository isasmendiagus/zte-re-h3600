// module: mt7915.ko
// function: CmdETxBfCfgBfPhy @ 0x1b3840
// size: 304 bytes
//

undefined4 CmdETxBfCfgBfPhy(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = AndesAllocCmdMsg(param_1,0x10);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    *param_2 = 0x24;
    if (2 < DebugLevel) {
      printk("%s: ucAction=0x%02X, ucBandIdx=0x%02X, ucSmthIntlBypass=0x%02X\n","CmdETxBfCfgBfPhy",
             param_2[1],param_2[2],param_2[3]);
    }
    AndesInitCmdMsg(iVar1,0x1eed0000,0xffff0008,500,0,0);
    AndesAppendCmdMsg(iVar1,param_2,0x10);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfCfgBfPhy",uVar2);
  }
  return uVar2;
}

