// module: mt7915.ko
// function: CmdITxBfPhaseComp @ 0x1b1864
// size: 412 bytes
//

undefined4
CmdITxBfPhaseComp(int param_1,undefined4 param_2,undefined1 param_3,undefined4 param_4,
                 undefined1 param_5,undefined1 param_6,undefined1 param_7)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_58 [2];
  undefined1 local_56;
  undefined1 local_55;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  undefined1 auStack_50 [44];
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("%s::: Enable iBF phase compensation : fgRdFromE2p = %d, ucBW = %d, ucDbdcBandIdx = %d\n"
           ,"CmdITxBfPhaseComp",param_6,param_2,param_4);
  }
  iVar2 = AndesAllocCmdMsg(param_1,0x30);
  if (iVar2 == 0) {
    uVar3 = 3;
  }
  else {
    os_zero_mem(local_58,0x30);
    local_56 = (undefined1)param_2;
    local_54 = (undefined1)param_4;
    local_53 = param_6;
    local_52 = param_7;
    local_58[0] = 0xf;
    local_55 = param_3;
    if (*(code **)(iVar1 + 0x14c) != (code *)0x0) {
      (**(code **)(iVar1 + 0x14c))(param_1,param_5,auStack_50);
    }
    AndesInitCmdMsg(iVar2,0x1eed0000,0xffff0008,1000,0,EventExtCmdResult);
    AndesAppendCmdMsg(iVar2,local_58,0x30);
    uVar3 = chip_cmd_tx(param_1,iVar2);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdITxBfPhaseComp",uVar3);
  }
  return uVar3;
}

