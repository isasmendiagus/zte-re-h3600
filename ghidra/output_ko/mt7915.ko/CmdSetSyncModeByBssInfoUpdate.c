// module: mt7915.ko
// function: CmdSetSyncModeByBssInfoUpdate @ 0x1c6f88
// size: 276 bytes
//

undefined4 CmdSetSyncModeByBssInfoUpdate(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  code *local_14;
  
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,0x158);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_14 = CmdExtBssInfoUpdateRsp;
    local_20 = CONCAT31(local_20._1_3_,0xf);
    local_24 = CONCAT13(0x26,CONCAT12(0xed,(undefined2)local_24));
    local_20 = CONCAT22(0xffff,(undefined2)local_20);
    AndesInitCmdMsg(iVar1,local_24,local_20,local_1c,local_18,CmdExtBssInfoUpdateRsp);
    local_2c = CONCAT22(1,(undefined2)local_2c);
    local_2c = CONCAT31(local_2c._1_3_,*(undefined1 *)(param_2 + 0xc));
    local_28 = CONCAT31(local_28._1_3_,1);
    AndesAppendCmdMsg(iVar1,&local_2c,8);
    bssUpdateSyncModeCtrl(param_1,param_2,iVar1);
    call_fw_cmd_notifieriers(4,param_1,*(undefined4 *)(iVar1 + 0x20));
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdSetSyncModeByBssInfoUpdate",uVar2);
  }
  return uVar2;
}

