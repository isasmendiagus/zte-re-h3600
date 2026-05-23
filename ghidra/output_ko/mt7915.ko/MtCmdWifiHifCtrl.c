// module: mt7915.ko
// function: MtCmdWifiHifCtrl @ 0x1b924c
// size: 332 bytes
//

undefined4 MtCmdWifiHifCtrl(int param_1,undefined1 param_2,undefined1 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  code *local_24;
  
  uVar3 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  if (uVar3 - 0x7636 < 2 || (uVar3 == 0x7615 || uVar3 == 0x7622)) {
    local_50 = 0;
    local_4c = 0;
    iVar1 = AndesAllocCmdMsg(param_1,8);
    if (iVar1 == 0) {
      uVar2 = 3;
    }
    else {
      local_48 = CONCAT13(0x43,CONCAT12(0xed,(undefined2)local_48));
      local_44 = CONCAT31(local_44._1_3_,0xf);
      local_44 = CONCAT22(8,(undefined2)local_44);
      local_34 = local_48;
      uStack_30 = local_44;
      uStack_2c = local_40;
      local_24 = CmdWifiHifCtrlRsp;
      local_3c = param_4;
      uStack_28 = param_4;
      AndesInitCmdMsg(iVar1,local_48,local_44,local_40,param_4,CmdWifiHifCtrlRsp);
      local_50._0_2_ = CONCAT11(param_2,param_3);
      AndesAppendCmdMsg(iVar1,&local_50,8);
      uVar2 = chip_cmd_tx(param_1,iVar1);
    }
    if (2 < DebugLevel) {
      printk("%s:(ret = %d)\n","MtCmdWifiHifCtrl",uVar2);
    }
    return uVar2;
  }
  return 0;
}

