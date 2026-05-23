// module: mt7915.ko
// function: MtCmdRFRegAccessRead @ 0x1ad200
// size: 304 bytes
//

undefined4
MtCmdRFRegAccessRead(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  code *local_24;
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  if (3 < DebugLevel) {
    printk("%s: RFIdx = %d, Offset = %x\n","MtCmdRFRegAccessRead",param_2,param_3);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_48 = CONCAT13(2,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT31(local_44._1_3_,7);
    local_44 = CONCAT22(0xc,(undefined2)local_44);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    local_24 = CmdRFRegAccessReadCb;
    local_3c = param_4;
    uStack_28 = param_4;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,param_4,CmdRFRegAccessReadCb);
    os_zero_mem(&local_54,0xc);
    local_54 = param_2;
    local_50 = param_3;
    AndesAppendCmdMsg(iVar1,&local_54,0xc);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdRFRegAccessRead",uVar2);
  }
  return uVar2;
}

