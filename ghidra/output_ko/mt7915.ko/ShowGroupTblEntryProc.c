// module: mt7915.ko
// function: ShowGroupTblEntryProc @ 0x8cd98
// size: 336 bytes
//

undefined4 ShowGroupTblEntryProc(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 *local_20;
  code *local_1c;
  
  local_48 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_44 = 5;
  if (param_2 != 0) {
    local_48 = os_str_tol(param_2,0,10);
    if (3 < DebugLevel) {
      printk("Index is: %d\n",local_48);
    }
    iVar1 = AndesAllocCmdMsg(param_1,8);
    if (iVar1 != 0) {
      local_20 = &local_40;
      local_1c = eventDispatcher;
      local_2c = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_2c));
      local_28 = CONCAT31(local_28._1_3_,5);
      uVar2 = 1;
      local_28 = CONCAT22(0x14,(undefined2)local_28);
      AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,eventDispatcher);
      AndesAppendCmdMsg(iVar1,&local_44,4);
      AndesAppendCmdMsg(iVar1,&local_48,4);
      AndesSendCmdMsg(param_1,iVar1);
      goto LAB_0008cea8;
    }
  }
  uVar2 = 0;
LAB_0008cea8:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","ShowGroupTblEntryProc",uVar2);
  }
  return uVar2;
}

