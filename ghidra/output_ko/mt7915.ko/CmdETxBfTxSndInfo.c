// module: mt7915.ko
// function: CmdETxBfTxSndInfo @ 0x1b33fc
// size: 428 bytes
//

undefined4 CmdETxBfTxSndInfo(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  uVar3 = 0;
  uVar4 = 0;
  uVar5 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,0x10);
  if (iVar1 == 0) {
    uVar3 = 3;
  }
  else {
    *param_2 = 0x20;
    if (2 < DebugLevel) {
      uVar2 = (uint)(byte)param_2[4];
      printk("%s: ucAction=0x%02X, ucReadClr=0x%02X, ucVhtOpt=0x%02X, ucHeOpt=0x%02X,\n",
             "CmdETxBfTxSndInfo",param_2[1],param_2[2],param_2[3],uVar2,uVar3,uVar4,uVar5);
      if (2 < DebugLevel) {
        printk("ucGloOpt=0x%02X, u2WlanIdx=0x%04X, ucSndIntv=0x%02X, ucSndStop:0x%02X\n",param_2[5],
               *(undefined2 *)(param_2 + 6),param_2[8],param_2[9],uVar2,uVar3,uVar4,uVar5);
        if (2 < DebugLevel) {
          printk("ucMaxSndStas=0x%02X, ucTxTime=0x%02X, ucMcs=0x%02X, fgLDPC:0x%02X\n",param_2[10],
                 param_2[0xb],param_2[0xc],param_2[0xd],uVar2,uVar3,uVar4,uVar5);
          if (2 < DebugLevel) {
            printk("ucInf=0x%02X\n",param_2[0xe]);
          }
        }
      }
    }
    AndesInitCmdMsg(iVar1,CONCAT13(0x1e,CONCAT12(0xed,(short)uVar3)),
                    CONCAT22(0xffff,(short)CONCAT31((int3)((uint)uVar4 >> 8),8)),500,0,0);
    AndesAppendCmdMsg(iVar1,param_2,0x10);
    uVar3 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfTxSndInfo",uVar3);
  }
  return uVar3;
}

