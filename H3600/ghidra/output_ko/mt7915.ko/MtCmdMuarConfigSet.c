// module: mt7915.ko
// function: MtCmdMuarConfigSet @ 0x1b5cf0
// size: 296 bytes
//

undefined4 MtCmdMuarConfigSet(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  int iVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  uVar3 = 0;
  uVar4 = 0;
  uVar5 = 0;
  uVar6 = 0;
  if (3 < DebugLevel) {
    uVar3 = 0;
    printk("%s:ucMuarModeSel = %d, ucForceClear = %d, ucEntryCnt = %d, ucAccessMode = %d\n",
           "MtCmdMuarConfigSet",*param_2,param_2[1],param_2[10],param_2[0xb],0,0,0,0,0);
  }
  iVar2 = (short)(ushort)(byte)param_2[10] * 8 + 0xd;
  iVar1 = AndesAllocCmdMsg(param_1,iVar2);
  if (iVar1 == 0) {
    uVar4 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,CONCAT13(0x48,CONCAT12(0xed,uVar3)),8,uVar4,uVar5,uVar6);
    AndesAppendCmdMsg(iVar1,param_2,iVar2);
    uVar4 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdMuarConfigSet",uVar4);
  }
  return uVar4;
}

