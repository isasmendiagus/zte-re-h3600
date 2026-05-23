// module: mt7915.ko
// function: set_disable_contention_tx @ 0x23e860
// size: 248 bytes
//

bool set_disable_contention_tx(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  bool bVar2;
  undefined1 local_29;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_29 = 0;
  local_28 = 0xcb;
  local_29 = os_str_tol(param_2,0,10);
  iVar1 = AndesAllocCmdMsg(param_1,5);
  bVar2 = iVar1 != 0;
  if (bVar2) {
    local_24 = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_24));
    local_20 = CONCAT31(local_20._1_3_,10);
    AndesInitCmdMsg(iVar1,local_24,local_20,local_1c,local_18,local_14);
    AndesAppendCmdMsg(iVar1,&local_28,4);
    AndesAppendCmdMsg(iVar1,&local_29,1);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","set_disable_contention_tx",bVar2);
  }
  return bVar2;
}

