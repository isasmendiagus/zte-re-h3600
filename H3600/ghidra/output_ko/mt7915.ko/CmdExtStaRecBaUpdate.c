// module: mt7915.ko
// function: CmdExtStaRecBaUpdate @ 0x1c6af8
// size: 664 bytes
//

undefined4
CmdExtStaRecBaUpdate
          (undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,undefined1 param_5)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  code *pcVar4;
  undefined4 local_58;
  undefined4 local_54;
  undefined2 local_50;
  undefined2 local_4e;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  undefined1 local_49;
  undefined2 local_48;
  undefined2 local_46;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  uint local_38;
  code *local_34;
  undefined1 local_c;
  undefined1 local_8;
  undefined1 local_7;
  undefined1 local_6;
  undefined2 local_4;
  undefined2 local_2;
  
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_58 = 0;
  local_54 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,0x14);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    if (3 < DebugLevel) {
      printk("%s: ucTLVNumber(%d)\n","CmdExtStaRecBaUpdate",1);
    }
    local_34 = CmdExtStaRecUpdateRsp;
    local_40 = CONCAT31(local_40._1_3_,0x27);
    local_44 = CONCAT13(0x25,CONCAT12(0xed,(undefined2)local_44));
    pcVar4 = CmdExtStaRecUpdateRsp;
    local_40 = CONCAT22(0x10,(undefined2)local_40);
    uVar3 = local_38;
    AndesInitCmdMsg(iVar1,local_44,local_40,local_3c,local_38,CmdExtStaRecUpdateRsp);
    local_c = (undefined1)param_2;
    local_58 = CONCAT22(1,(short)(param_2 >> 8));
    local_54 = CONCAT22(CONCAT11(local_54._3_1_,(byte)(((param_2 >> 0x10) << 0x16) >> 0x1e)),
                        CONCAT11(local_c,1));
    AndesAppendCmdMsg(iVar1,&local_58,8);
    if ((3 < DebugLevel) && (printk("%s: StaRecUpdate:\n","CmdExtStaRecBaUpdate"), 3 < DebugLevel))
    {
      uVar3 = local_54 >> 8 & 0xff;
      pcVar4 = (code *)(local_58 >> 0x10);
      printk("%s: ucBssIndex=%d, WlanIdx=%d, ucMuarIdx=%d, u2TotalElementNum=%d\n",
             "CmdExtStaRecBaUpdate",local_58 & 0xff,CONCAT11(local_54._2_1_,local_58._1_1_) & 0x3ff,
             uVar3,pcVar4);
    }
    __memzero(&local_50,0xc);
    local_4 = (undefined2)param_4;
    local_2 = (undefined2)((uint)param_4 >> 0x10);
    local_6 = (undefined1)((uint)param_3 >> 0x10);
    local_8 = (undefined1)param_3;
    local_7 = (undefined1)((uint)param_3 >> 8);
    local_4a = param_5;
    local_48 = local_4;
    local_46 = local_2;
    local_49 = local_6;
    local_4c = local_8;
    local_4b = local_7;
    local_50 = 6;
    local_4e = 0xc;
    if ((3 < DebugLevel) &&
       (printk("%s: BaInfo:\n","CmdExtStaRecBaUpdate",6,0xc,uVar3,pcVar4), 3 < DebugLevel)) {
      printk("%s: u2Tag=%d, u2Length=%d, ucTid=%d, u2BaDirectin=%d, BaEnable=%d, u2BaStartSeq=%d, u2BaWinSize=%d, ucAmsduCap=%d\n"
             ,"CmdExtStaRecBaUpdate",local_50,local_4e,local_4c,local_4b,local_49,local_48,local_46,
             local_4a);
    }
    AndesAppendCmdMsg(iVar1,&local_50,0xc);
    call_fw_cmd_notifieriers(5,param_1,*(undefined4 *)(iVar1 + 0x20));
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdExtStaRecBaUpdate",uVar2);
  }
  return uVar2;
}

