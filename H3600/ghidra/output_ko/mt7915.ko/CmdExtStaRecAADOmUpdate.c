// module: mt7915.ko
// function: CmdExtStaRecAADOmUpdate @ 0x1c6d94
// size: 496 bytes
//

undefined4 CmdExtStaRecAADOmUpdate(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 local_42;
  undefined2 local_40;
  undefined1 local_3e;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  code *local_24;
  
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_3c = 0;
  local_38 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,0xe);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    if (3 < DebugLevel) {
      printk("%s: ucTLVNumber(%d)\n","CmdExtStaRecAADOmUpdate",1);
    }
    local_24 = CmdExtStaRecUpdateRsp;
    local_30 = CONCAT31(local_30._1_3_,0x27);
    local_34 = CONCAT13(0x25,CONCAT12(0xed,(undefined2)local_34));
    local_30 = CONCAT22(0x10,(undefined2)local_30);
    AndesInitCmdMsg(iVar1,local_34,local_30,local_2c,local_28,CmdExtStaRecUpdateRsp);
    local_38 = (uint)CONCAT11(local_38._3_1_,(byte)((uint)(param_2 << 0x16) >> 0x1e)) << 0x10;
    local_3c = CONCAT22(1,(ushort)(byte)param_2 << 8);
    local_38 = CONCAT31(local_38._1_3_,1);
    AndesAppendCmdMsg(iVar1,&local_3c,8);
    if ((3 < DebugLevel) &&
       (printk("%s: StaRecUpdate:\n","CmdExtStaRecAADOmUpdate"), 3 < DebugLevel)) {
      printk("%s: ucBssIndex=%d, WlanIdx=%d, ucMuarIdx=%d, u2TotalElementNum=%d\n",
             "CmdExtStaRecAADOmUpdate",local_3c & 0xff,
             CONCAT11(local_38._2_1_,local_3c._1_1_) & 0x3ff,local_38 >> 8 & 0xff,local_3c >> 0x10);
    }
    __memzero(&local_42,6);
    local_3e = (undefined1)param_3;
    local_42 = 0x10;
    local_40 = 6;
    if (2 < DebugLevel) {
      printk("%s: u2Tag=%d, u2Length=%d, Wcid=%u, ucAadOm=%u\n","CmdExtStaRecAADOmUpdate",0x10,6,
             param_2,param_3);
    }
    AndesAppendCmdMsg(iVar1,&local_42,6);
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdExtStaRecAADOmUpdate",uVar2);
  }
  return uVar2;
}

