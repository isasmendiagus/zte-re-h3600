// module: mt7915.ko
// function: MtCmdSetVoWFeatureCtrl @ 0x1b61b4
// size: 276 bytes
//

undefined4 MtCmdSetVoWFeatureCtrl(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_48 [40];
  
  if (3 < DebugLevel) {
    printk("%s:struct size %zu\n","MtCmdSetVoWFeatureCtrl",0x28);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0x28);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x38ed0000,0x28000f,0,auStack_48,MtCmdSetVoWFeatureCtrlRsp);
    AndesAppendCmdMsg(iVar1,param_2,0x28);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdSetVoWFeatureCtrl",uVar2);
  }
  return uVar2;
}

