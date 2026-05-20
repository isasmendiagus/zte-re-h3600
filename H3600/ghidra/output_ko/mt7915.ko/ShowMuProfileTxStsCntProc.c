// module: mt7915.ko
// function: ShowMuProfileTxStsCntProc @ 0x8f54c
// size: 312 bytes
//

undefined4 ShowMuProfileTxStsCntProc(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 local_4e;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 *local_3c;
  code *local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_4e = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_4c = 0x1e;
  if (param_2 != 0) {
    local_4e = os_str_tol(param_2,0,10);
    iVar1 = AndesAllocCmdMsg(param_1,6);
    if (iVar1 != 0) {
      local_3c = &local_34;
      local_38 = eventDispatcher;
      local_48 = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_48));
      local_44 = CONCAT31(local_44._1_3_,5);
      uVar2 = 1;
      local_44 = CONCAT22(0x24,(undefined2)local_44);
      AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,eventDispatcher);
      AndesAppendCmdMsg(iVar1,&local_4c,4);
      AndesAppendCmdMsg(iVar1,&local_4e,2);
      AndesSendCmdMsg(param_1,iVar1);
      goto LAB_0008f64c;
    }
  }
  uVar2 = 0;
LAB_0008f64c:
  if (-1 < DebugLevel) {
    printk("%s:(Ret = %d\n","ShowMuProfileTxStsCntProc",uVar2);
  }
  return uVar2;
}

