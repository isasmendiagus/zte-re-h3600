// module: mt7915.ko
// function: CmdExtSetTmrCR @ 0x1c72bc
// size: 400 bytes
//

undefined4 CmdExtSetTmrCR(int param_1,int param_2,undefined1 param_3)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined1 extraout_r2;
  undefined1 uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar3 = AndesAllocCmdMsg(param_1,0xc);
  if (iVar3 == 0) {
    uVar6 = 3;
  }
  else {
    local_34 = CONCAT13(0x44,CONCAT12(0xed,(undefined2)local_34));
    local_30 = CONCAT31(local_30._1_3_,8);
    AndesInitCmdMsg(iVar3,local_34,local_30,local_2c,local_28,local_24);
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
      local_40._2_2_ = CONCAT11(uVar4,uVar1);
    }
    else {
      local_40 = CONCAT13(uVar4,0x80000);
    }
    local_40 = (uint)CONCAT21(local_40._2_2_,*(undefined1 *)(iVar2 + 0x14f)) << 8;
    AndesAppendCmdMsg(iVar3,&local_40,4);
    uVar6 = local_3c;
    if (param_2 == 0) {
      local_3c = (uint)local_3c._1_3_ << 8;
      iVar2 = local_3c;
    }
    else {
      local_3c = CONCAT31(local_3c._1_3_,1);
      iVar2 = local_3c;
      local_3c._2_2_ = SUB42(uVar6,2);
      if (param_2 == 1) {
        local_3c = CONCAT22(local_3c._2_2_,1);
        iVar2 = local_3c;
      }
      else if (param_2 == 2) {
        local_3c = CONCAT22(local_3c._2_2_,0x101);
        if (local_40._1_1_ == '\x02') {
          local_3c = 0x20101;
        }
        local_38 = 0x3033403;
        iVar2 = local_3c;
      }
    }
    local_3c = iVar2;
    local_3c = CONCAT13(param_3,(undefined3)local_3c);
    AndesAppendCmdMsg(iVar3,&local_3c,8);
    uVar6 = AndesSendCmdMsg(param_1,iVar3);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdExtSetTmrCR",uVar6);
  }
  return uVar6;
}

