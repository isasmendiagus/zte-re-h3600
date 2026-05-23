// module: mt7915.ko
// function: MtCmdEdcaParameterSet @ 0x1b49e0
// size: 280 bytes
//

undefined4
MtCmdEdcaParameterSet(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 local_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  local_c._0_1_ = (byte)param_2;
  uVar3 = (short)(ushort)(byte)local_c * 8 + 4;
  local_c = param_2;
  uStack_8 = param_3;
  uStack_4 = param_4;
  iVar1 = AndesAllocCmdMsg(param_1,uVar3);
  if (iVar1 != 0) {
    AndesInitCmdMsg(iVar1,0x27ed0000,0x8000f,0,0,EventExtCmdResult);
    if (uVar3 < 0xc5) {
      AndesAppendCmdMsg(iVar1,&local_c,uVar3);
    }
    uVar2 = chip_cmd_tx(param_1,iVar1);
    return uVar2;
  }
  if (-1 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdEdcaParameterSet",3);
  }
  return 3;
}

