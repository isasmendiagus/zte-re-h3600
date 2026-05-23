// module: mt7915.ko
// function: MtCmdSetVoWModuleCtrl @ 0x1b6528
// size: 276 bytes
//

undefined4 MtCmdSetVoWModuleCtrl(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_84 [100];
  
  if (3 < DebugLevel) {
    printk("%s:struct size %zu\n","MtCmdSetVoWModuleCtrl",100);
  }
  iVar1 = AndesAllocCmdMsg(param_1,100);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x4bed0000,0x64000f,0,auStack_84,MtCmdSetVoWModuleCtrlRsp);
    AndesAppendCmdMsg(iVar1,param_2,100);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdSetVoWModuleCtrl",uVar2);
  }
  return uVar2;
}

