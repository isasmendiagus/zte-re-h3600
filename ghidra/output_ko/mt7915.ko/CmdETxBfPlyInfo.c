// module: mt7915.ko
// function: CmdETxBfPlyInfo @ 0x1b35ac
// size: 348 bytes
//

undefined4 CmdETxBfPlyInfo(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  uVar4 = 0;
  uVar5 = 0;
  uVar6 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,0x10);
  if (iVar1 == 0) {
    uVar4 = 3;
  }
  else {
    *param_2 = 0x21;
    if (2 < DebugLevel) {
      uVar3 = (uint)(byte)param_2[5];
      uVar2 = (uint)(byte)param_2[6];
      printk("%s: ucAction=0x%02X, ucGloOpt=0x%02X, ucGrpIBfOpt=0x%02X, ucGrpEBfOpt=0x%02X,\n",
             "CmdETxBfPlyInfo",param_2[1],param_2[4],uVar3,uVar2,uVar4,uVar5,uVar6);
      if (2 < DebugLevel) {
        printk("u2WlanIdx=0x%04X, ucNss=0x%02X, ucSSPly=0x%02X\n",*(undefined2 *)(param_2 + 2),
               param_2[7],param_2[8],uVar3,uVar2,uVar4,uVar5,uVar6);
      }
    }
    AndesInitCmdMsg(iVar1,CONCAT13(0x1e,CONCAT12(0xed,(short)uVar4)),
                    CONCAT22(0xffff,(short)CONCAT31((int3)((uint)uVar5 >> 8),8)),500,0,0);
    AndesAppendCmdMsg(iVar1,param_2,0x10);
    uVar4 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfPlyInfo",uVar4);
  }
  return uVar4;
}

