// module: mt7915.ko
// function: MtCmdSmeshConfigSet @ 0x1ace2c
// size: 352 bytes
//

undefined4 MtCmdSmeshConfigSet(undefined4 param_1,undefined1 *param_2,code *param_3)

{
  int iVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  code *unaff_r9;
  bool bVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  
  uVar6 = 0;
  uVar7 = 0;
  if (3 < DebugLevel) {
    unaff_r9 = (code *)(uint)(byte)param_2[3];
    uVar7 = 0;
    uVar6 = 0;
    printk("%s:ucBand = %d, ucAccessMode = %d, ucSmeshEn = %d, fgSmeshRxA2 = %d, fgSmeshRxA1 = %d, fgSmeshRxData = %d, fgSmeshRxMgnt = %d, fgSmeshRxCtrl = %d\n"
           ,"MtCmdSmeshConfigSet",*param_2,param_2[1],param_2[2],unaff_r9,param_2[4],param_2[5],
           param_2[6],param_2[7],0,0);
  }
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar4 = 3;
  }
  else {
    bVar5 = param_2[1] != '\0';
    if (bVar5) {
      param_3 = (code *)0x0;
      uVar2 = 8;
      uVar3 = 0;
    }
    else {
      uVar3 = 8;
      uVar2 = 7;
    }
    if (bVar5) {
      unaff_r9 = param_3;
    }
    if (!bVar5) {
      unaff_r9 = MtCmdGetTxSmeshRsp;
    }
    AndesInitCmdMsg(iVar1,CONCAT13(0xae,CONCAT12(0xed,uVar6)),
                    CONCAT31((int3)(CONCAT22(uVar3,uVar7) >> 8),uVar2),0,param_3,unaff_r9);
    AndesAppendCmdMsg(iVar1,param_2,8);
    uVar4 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdSmeshConfigSet",uVar4);
  }
  return uVar4;
}

