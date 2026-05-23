// module: mt7915.ko
// function: wifi_test_muru_set_arb_op_mode @ 0x23f560
// size: 224 bytes
//

bool wifi_test_muru_set_arb_op_mode(undefined4 param_1,undefined1 param_2)

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
  local_28 = 0xe;
  local_29 = param_2;
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
    printk("%s:(Ret = %d_\n","wifi_test_muru_set_arb_op_mode",bVar2);
  }
  return bVar2;
}

