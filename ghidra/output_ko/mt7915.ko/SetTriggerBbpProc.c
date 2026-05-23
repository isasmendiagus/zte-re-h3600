// module: mt7915.ko
// function: SetTriggerBbpProc @ 0x8e44c
// size: 264 bytes
//

undefined4 SetTriggerBbpProc(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  ushort local_2a;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_2a = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_28 = 0x23;
  uVar1 = os_str_tol(param_2,0,10);
  if (uVar1 < 0x801) {
    local_2a = uVar1;
    iVar2 = AndesAllocCmdMsg(param_1,6);
    if (iVar2 != 0) {
      local_24 = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_24));
      local_20 = CONCAT31(local_20._1_3_,10);
      uVar3 = 1;
      AndesInitCmdMsg(iVar2,local_24,local_20,local_1c,local_18,local_14);
      AndesAppendCmdMsg(iVar2,&local_28,4);
      AndesAppendCmdMsg(iVar2,&local_2a,2);
      AndesSendCmdMsg(param_1,iVar2);
      goto LAB_0008e49c;
    }
  }
  uVar3 = 0;
LAB_0008e49c:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","SetTriggerBbpProc",uVar3);
  }
  return uVar3;
}

