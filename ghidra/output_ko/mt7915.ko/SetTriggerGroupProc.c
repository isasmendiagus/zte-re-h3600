// module: mt7915.ko
// function: SetTriggerGroupProc @ 0x8e558
// size: 268 bytes
//

undefined4 SetTriggerGroupProc(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  char local_29;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_29 = '\0';
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_28 = 0x20;
  bVar1 = os_str_tol(param_2,0,10);
  if (1 < bVar1) {
    local_29 = bVar1 - 1;
    iVar2 = AndesAllocCmdMsg(param_1,5);
    if (iVar2 != 0) {
      local_24 = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_24));
      local_20 = CONCAT31(local_20._1_3_,10);
      uVar3 = 1;
      AndesInitCmdMsg(iVar2,local_24,local_20,local_1c,local_18,local_14);
      AndesAppendCmdMsg(iVar2,&local_28,4);
      AndesAppendCmdMsg(iVar2,&local_29,1);
      AndesSendCmdMsg(param_1,iVar2);
      goto LAB_0008e62c;
    }
  }
  uVar3 = 0;
LAB_0008e62c:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","SetTriggerGroupProc",uVar3);
  }
  return uVar3;
}

