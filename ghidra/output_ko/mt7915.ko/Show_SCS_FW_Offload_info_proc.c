// module: mt7915.ko
// function: Show_SCS_FW_Offload_info_proc @ 0xbe774
// size: 292 bytes
//

undefined4 Show_SCS_FW_Offload_info_proc(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined1 *local_90;
  code *local_8c;
  undefined1 auStack_88 [116];
  
  local_9c = 0;
  local_98 = 0;
  local_94 = 0;
  local_a0 = 4;
  memset(auStack_88,0,0x70);
  iVar1 = AndesAllocCmdMsg(param_1,0x74);
  if (iVar1 == 0) {
    uVar2 = 0;
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Msg allocation failed\n","Show_SCS_FW_Offload_info_proc");
  }
  else {
    local_90 = auStack_88;
    local_8c = ScsEventCallback;
    local_98 = CONCAT22(0x70,(undefined2)local_98);
    uVar2 = 1;
    local_9c = CONCAT13(0x82,CONCAT12(0xed,(undefined2)local_9c));
    local_98 = CONCAT31(local_98._1_3_,5);
    AndesInitCmdMsg(iVar1,local_9c,local_98,local_94,local_90,ScsEventCallback);
    AndesAppendCmdMsg(iVar1,&local_a0,4);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","Show_SCS_FW_Offload_info_proc",uVar2);
  }
  return uVar2;
}

