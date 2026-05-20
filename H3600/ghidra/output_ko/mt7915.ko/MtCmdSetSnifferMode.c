// module: mt7915.ko
// function: MtCmdSetSnifferMode @ 0x1b7778
// size: 228 bytes
//

undefined4 MtCmdSetSnifferMode(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x42ed0000,0xf,0,0,EventExtCmdResult);
    AndesAppendCmdMsg(iVar1,param_2,8);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (0 < DebugLevel) {
    printk("%s:(ret = %d) sniffer_mode:%d\n","MtCmdSetSnifferMode",uVar2,*param_2);
  }
  return uVar2;
}

