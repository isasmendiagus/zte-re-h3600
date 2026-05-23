// module: mt7915.ko
// function: MtAsicUpdateStaRecAadOmByFw @ 0x198194
// size: 4 bytes
//

undefined4 MtAsicUpdateStaRecAadOmByFw(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 uStack_42;
  undefined2 uStack_40;
  undefined1 uStack_3e;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  code *pcStack_24;
  
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_3c = 0;
  uStack_38 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,0xe);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    if (3 < DebugLevel) {
      printk("%s: ucTLVNumber(%d)\n","CmdExtStaRecAADOmUpdate",1);
    }
    pcStack_24 = CmdExtStaRecUpdateRsp;
    uStack_30 = CONCAT31(uStack_30._1_3_,0x27);
    uStack_34 = CONCAT13(0x25,CONCAT12(0xed,(undefined2)uStack_34));
    uStack_30 = CONCAT22(0x10,(undefined2)uStack_30);
    AndesInitCmdMsg(iVar1,uStack_34,uStack_30,uStack_2c,uStack_28,CmdExtStaRecUpdateRsp);
    uStack_38 = (uint)CONCAT11(uStack_38._3_1_,(byte)((uint)(param_2 << 0x16) >> 0x1e)) << 0x10;
    uStack_3c = CONCAT22(1,(ushort)(byte)param_2 << 8);
    uStack_38 = CONCAT31(uStack_38._1_3_,1);
    AndesAppendCmdMsg(iVar1,&uStack_3c,8);
    if ((3 < DebugLevel) &&
       (printk("%s: StaRecUpdate:\n","CmdExtStaRecAADOmUpdate"), 3 < DebugLevel)) {
      printk("%s: ucBssIndex=%d, WlanIdx=%d, ucMuarIdx=%d, u2TotalElementNum=%d\n",
             "CmdExtStaRecAADOmUpdate",uStack_3c & 0xff,
             CONCAT11(uStack_38._2_1_,uStack_3c._1_1_) & 0x3ff,uStack_38 >> 8 & 0xff,
             uStack_3c >> 0x10);
    }
    __memzero(&uStack_42,6);
    uStack_3e = (undefined1)param_3;
    uStack_42 = 0x10;
    uStack_40 = 6;
    if (2 < DebugLevel) {
      printk("%s: u2Tag=%d, u2Length=%d, Wcid=%u, ucAadOm=%u\n","CmdExtStaRecAADOmUpdate",0x10,6,
             param_2,param_3);
    }
    AndesAppendCmdMsg(iVar1,&uStack_42,6);
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdExtStaRecAADOmUpdate",uVar2);
  }
  return uVar2;
}

