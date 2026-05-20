// module: mt7915.ko
// function: MT_RfRegRead @ 0x27e04c
// size: 4 bytes
//

undefined4 MT_RfRegRead(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  code *pcStack_24;
  
  uStack_48 = 0;
  uStack_44 = 0;
  uStack_40 = 0;
  if (3 < DebugLevel) {
    printk("%s: RFIdx = %d, Offset = %x\n","MtCmdRFRegAccessRead",param_2,param_3);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    uStack_48 = CONCAT13(2,CONCAT12(0xed,(undefined2)uStack_48));
    uStack_44 = CONCAT31(uStack_44._1_3_,7);
    uStack_44 = CONCAT22(0xc,(undefined2)uStack_44);
    uStack_34 = uStack_48;
    uStack_30 = uStack_44;
    uStack_2c = uStack_40;
    pcStack_24 = CmdRFRegAccessReadCb;
    uStack_3c = param_4;
    uStack_28 = param_4;
    AndesInitCmdMsg(iVar1,uStack_48,uStack_44,uStack_40,param_4,CmdRFRegAccessReadCb);
    os_zero_mem(&uStack_54,0xc);
    uStack_54 = param_2;
    uStack_50 = param_3;
    AndesAppendCmdMsg(iVar1,&uStack_54,0xc);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdRFRegAccessRead",uVar2);
  }
  return uVar2;
}

