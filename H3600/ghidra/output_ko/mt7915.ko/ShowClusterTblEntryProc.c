// module: mt7915.ko
// function: ShowClusterTblEntryProc @ 0x8d1b8
// size: 348 bytes
//

undefined4 ShowClusterTblEntryProc(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 *local_40;
  code *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_54 = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_50 = 7;
  if (param_2 != 0) {
    local_54 = os_str_tol(param_2,0,10);
    if (3 < DebugLevel) {
      printk("Index is: %d\n",local_54);
    }
    iVar1 = AndesAllocCmdMsg(param_1,8);
    if (iVar1 != 0) {
      local_40 = &local_38;
      local_3c = eventDispatcher;
      local_4c = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_4c));
      local_48 = CONCAT31(local_48._1_3_,5);
      uVar2 = 1;
      local_48 = CONCAT22(0x20,(undefined2)local_48);
      AndesInitCmdMsg(iVar1,local_4c,local_48,local_44,local_40,eventDispatcher);
      AndesAppendCmdMsg(iVar1,&local_50,4);
      AndesAppendCmdMsg(iVar1,&local_54,4);
      AndesSendCmdMsg(param_1,iVar1);
      goto LAB_0008d2d4;
    }
  }
  uVar2 = 0;
LAB_0008d2d4:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","ShowClusterTblEntryProc",uVar2);
  }
  return uVar2;
}

