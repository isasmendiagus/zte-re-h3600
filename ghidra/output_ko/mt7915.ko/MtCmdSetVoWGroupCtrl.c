// module: mt7915.ko
// function: MtCmdSetVoWGroupCtrl @ 0x1b6088
// size: 296 bytes
//

uint MtCmdSetVoWGroupCtrl(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  undefined1 auStack_140 [5];
  char local_13b;
  
  if (3 < DebugLevel) {
    printk("%s:struct size %zu\n","MtCmdSetVoWGroupCtrl",0x120);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0x120);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x37ed0000,0x120000f,0,auStack_140,MtCmdSetVoWGroupCtrlRsp);
    AndesAppendCmdMsg(iVar1,param_2,0x120);
    uVar2 = chip_cmd_tx(param_1,iVar1);
    if (uVar2 == 0) {
      uVar2 = (uint)(local_13b != '\x01');
    }
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdSetVoWGroupCtrl",uVar2);
  }
  return uVar2;
}

