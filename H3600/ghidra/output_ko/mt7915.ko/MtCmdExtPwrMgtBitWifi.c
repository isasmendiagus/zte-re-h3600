// module: mt7915.ko
// function: MtCmdExtPwrMgtBitWifi @ 0x1af40c
// size: 308 bytes
//

undefined4 MtCmdExtPwrMgtBitWifi(undefined4 param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  code *local_1c;
  
  uVar3 = param_2 & 0xffff;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,4);
  uVar2 = local_44;
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_44._3_1_ = SUB41(uVar2,3);
    local_44._0_3_ =
         CONCAT12((byte)((uVar3 << 0x16) >> 0x1e),CONCAT11((char)(param_2 >> 0x10),(char)uVar3));
    if (2 < DebugLevel) {
      printk("%s:WlanIdx(%d), ucPwrMgtBit(%d)\n","MtCmdExtPwrMgtBitWifi",uVar3,
             (param_2 << 8) >> 0x18);
    }
    local_40 = CONCAT13(0x1b,CONCAT12(0xed,(undefined2)local_40));
    local_3c = CONCAT31(local_3c._1_3_,0xf);
    local_3c = CONCAT22(8,(undefined2)local_3c);
    local_2c = local_40;
    uStack_28 = local_3c;
    uStack_24 = local_38;
    uStack_20 = local_34;
    local_1c = CmdExtPmMgtBitRsp;
    AndesInitCmdMsg(iVar1,local_40,local_3c,local_38,local_34,CmdExtPmMgtBitRsp);
    AndesAppendCmdMsg(iVar1,&local_44,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","MtCmdExtPwrMgtBitWifi",uVar2);
  }
  return uVar2;
}

