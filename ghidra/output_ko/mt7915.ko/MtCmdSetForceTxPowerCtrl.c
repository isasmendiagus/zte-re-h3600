// module: mt7915.ko
// function: MtCmdSetForceTxPowerCtrl @ 0x1b0bcc
// size: 400 bytes
//

undefined4
MtCmdSetForceTxPowerCtrl
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined1 param_5,
          undefined1 param_6)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_64;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_55;
  undefined1 local_54;
  undefined1 local_53;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  code *local_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  code *local_2c;
  
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (0 < DebugLevel) {
    printk("%s: Band(%d), TxMode(%d), MCS(%d), BW(%d), TxPower(%d)\n","MtCmdSetForceTxPowerCtrl",
           param_2,param_4,param_5,param_6,param_3);
  }
  iVar2 = AndesAllocCmdMsg(param_1,8);
  if (iVar2 == 0) {
    uVar3 = 3;
  }
  else {
    local_40 = EventExtCmdResult;
    local_50 = CONCAT13(0x58,CONCAT12(0xed,(undefined2)local_50));
    local_4c = CONCAT31(local_4c._1_3_,0xf);
    local_4c = CONCAT22(8,(undefined2)local_4c);
    local_3c = local_50;
    uStack_38 = local_4c;
    uStack_34 = local_48;
    uStack_30 = local_44;
    local_2c = EventExtCmdResult;
    AndesInitCmdMsg(iVar2,local_50,local_4c,local_48,local_44,EventExtCmdResult);
    __memzero(&local_58,8);
    local_57 = (undefined1)param_4;
    local_55 = param_6;
    local_54 = (undefined1)param_2;
    if (*(char *)(iVar1 + 0x210) == '\0') {
      local_58 = 0xe;
    }
    else {
      local_58 = 0xd;
    }
    local_56 = param_5;
    local_64 = (undefined1)param_3;
    local_53 = local_64;
    AndesAppendCmdMsg(iVar2,&local_58,8);
    uVar3 = chip_cmd_tx(param_1,iVar2);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdSetForceTxPowerCtrl",uVar3);
  }
  return uVar3;
}

