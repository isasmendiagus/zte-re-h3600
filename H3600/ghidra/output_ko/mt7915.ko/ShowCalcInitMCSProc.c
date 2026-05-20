// module: mt7915.ko
// function: ShowCalcInitMCSProc @ 0x8dd74
// size: 296 bytes
//

undefined4 ShowCalcInitMCSProc(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 *local_18;
  code *local_14;
  
  local_40 = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_3c = 0x11;
  if (param_2 != 0) {
    local_40 = os_str_tol(param_2,0,10);
    iVar1 = AndesAllocCmdMsg(param_1,8);
    if (iVar1 != 0) {
      local_18 = &local_38;
      local_14 = eventDispatcher;
      local_24 = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_24));
      local_20 = CONCAT31(local_20._1_3_,5);
      uVar2 = 1;
      local_20 = CONCAT22(0x14,(undefined2)local_20);
      AndesInitCmdMsg(iVar1,local_24,local_20,local_1c,local_18,eventDispatcher);
      AndesAppendCmdMsg(iVar1,&local_3c,4);
      AndesAppendCmdMsg(iVar1,&local_40,4);
      AndesSendCmdMsg(param_1,iVar1);
      goto LAB_0008de64;
    }
  }
  uVar2 = 0;
LAB_0008de64:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","ShowCalcInitMCSProc",uVar2);
  }
  return uVar2;
}

