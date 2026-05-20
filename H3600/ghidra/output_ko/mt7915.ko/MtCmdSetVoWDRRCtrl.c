// module: mt7915.ko
// function: MtCmdSetVoWDRRCtrl @ 0x1b5f50
// size: 308 bytes
//

uint MtCmdSetVoWDRRCtrl(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  undefined1 auStack_34 [5];
  char local_2f;
  
  if (3 < DebugLevel) {
    printk("%s:struct size %zu\n","MtCmdSetVoWDRRCtrl",0x14);
  }
  __memzero(auStack_34,0x14);
  iVar1 = AndesAllocCmdMsg(param_1,0x14);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x36ed0000,0x14000f,0,auStack_34,MtCmdSetVoWDRRCtrlRsp);
    AndesAppendCmdMsg(iVar1,param_2,0x14);
    uVar2 = chip_cmd_tx(param_1,iVar1);
    if (uVar2 == 0) {
      uVar2 = (uint)(local_2f != '\x01');
    }
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdSetVoWDRRCtrl",uVar2);
  }
  return uVar2;
}

