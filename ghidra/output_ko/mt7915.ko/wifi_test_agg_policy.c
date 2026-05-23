// module: mt7915.ko
// function: wifi_test_agg_policy @ 0x23fc14
// size: 276 bytes
//

undefined4 wifi_test_agg_policy(undefined4 param_1,undefined1 param_2,undefined1 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_2a;
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
  local_28 = 0x68;
  local_2a = param_2;
  local_29 = param_3;
  iVar1 = AndesAllocCmdMsg(param_1,6);
  if (iVar1 == 0) {
    uVar2 = 0;
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: msg is NULL\n","wifi_test_agg_policy");
  }
  else {
    local_24 = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_24));
    local_20 = CONCAT31(local_20._1_3_,10);
    uVar2 = 1;
    AndesInitCmdMsg(iVar1,local_24,local_20,local_1c,local_18,local_14);
    AndesAppendCmdMsg(iVar1,&local_28,4);
    AndesAppendCmdMsg(iVar1,&local_2a,2);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (0 < DebugLevel) {
    printk("%s: Ret=%d\n","wifi_test_agg_policy",uVar2);
  }
  return uVar2;
}

