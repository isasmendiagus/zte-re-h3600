// module: mt7915.ko
// function: MtCmdAddressLenReq @ 0x1b7c5c
// size: 352 bytes
//

undefined4 MtCmdAddressLenReq(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  int local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  code *local_24;
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (0 < DebugLevel) {
    printk("Start address = 0x%x, DL length = %d, Data mode = 0x%x\n",param_2,param_3,param_4);
  }
  iVar2 = AndesAllocCmdMsg(param_1,0xc);
  if (iVar2 == 0) {
    uVar4 = 3;
  }
  else {
    local_44 = CONCAT31(local_44._1_3_,0x17);
    if (*(int *)(iVar1 + 0x11c) == param_2) {
      uVar3 = 5;
    }
    else {
      uVar3 = 1;
    }
    local_48._0_3_ = CONCAT12(uVar3,(undefined2)local_48);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = CmdAddrellLenRsp;
    AndesInitCmdMsg(iVar2,local_48,local_44,local_40,local_3c,CmdAddrellLenRsp);
    local_4c = param_2;
    AndesAppendCmdMsg(iVar2,&local_4c,4);
    local_4c = param_3;
    AndesAppendCmdMsg(iVar2,&local_4c,4);
    local_4c = param_4;
    AndesAppendCmdMsg(iVar2,&local_4c,4);
    uVar4 = chip_cmd_tx(param_1,iVar2);
  }
  if (0 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdAddressLenReq",uVar4);
  }
  return uVar4;
}

