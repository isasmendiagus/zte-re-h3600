// module: mt7915.ko
// function: MtSetTmrCRByFw @ 0x198004
// size: 4 bytes
//

undefined4 MtSetTmrCRByFw(int param_1,int param_2,undefined1 param_3)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined1 extraout_r2;
  undefined1 uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  uStack_40 = 0;
  uStack_3c = 0;
  uStack_38 = 0;
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar3 = AndesAllocCmdMsg(param_1,0xc);
  if (iVar3 == 0) {
    uVar6 = 3;
  }
  else {
    uStack_34 = CONCAT13(0x44,CONCAT12(0xed,(undefined2)uStack_34));
    uStack_30 = CONCAT31(uStack_30._1_3_,8);
    AndesInitCmdMsg(iVar3,uStack_34,uStack_30,uStack_2c,uStack_28,uStack_24);
    iVar5 = *(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10);
    if (iVar5 != 0) {
      uVar1 = *(undefined1 *)(iVar5 + 8);
      uVar4 = *(undefined1 *)(iVar5 + 9);
    }
    else {
      uVar4 = 10;
      uVar1 = extraout_r2;
    }
    if (iVar5 != 0) {
      uStack_40._2_2_ = CONCAT11(uVar4,uVar1);
    }
    else {
      uStack_40 = CONCAT13(uVar4,0x80000);
    }
    uStack_40 = (uint)CONCAT21(uStack_40._2_2_,*(undefined1 *)(iVar2 + 0x14f)) << 8;
    AndesAppendCmdMsg(iVar3,&uStack_40,4);
    uVar6 = uStack_3c;
    if (param_2 == 0) {
      uStack_3c = (uint)uStack_3c._1_3_ << 8;
      iVar2 = uStack_3c;
    }
    else {
      uStack_3c = CONCAT31(uStack_3c._1_3_,1);
      iVar2 = uStack_3c;
      uStack_3c._2_2_ = SUB42(uVar6,2);
      if (param_2 == 1) {
        uStack_3c = CONCAT22(uStack_3c._2_2_,1);
        iVar2 = uStack_3c;
      }
      else if (param_2 == 2) {
        uStack_3c = CONCAT22(uStack_3c._2_2_,0x101);
        if (uStack_40._1_1_ == '\x02') {
          uStack_3c = 0x20101;
        }
        uStack_38 = 0x3033403;
        iVar2 = uStack_3c;
      }
    }
    uStack_3c = iVar2;
    uStack_3c = CONCAT13(param_3,(undefined3)uStack_3c);
    AndesAppendCmdMsg(iVar3,&uStack_3c,8);
    uVar6 = AndesSendCmdMsg(param_1,iVar3);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdExtSetTmrCR",uVar6);
  }
  return uVar6;
}

