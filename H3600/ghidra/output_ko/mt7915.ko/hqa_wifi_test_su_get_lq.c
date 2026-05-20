// module: mt7915.ko
// function: hqa_wifi_test_su_get_lq @ 0x8fff0
// size: 364 bytes
//

undefined4 hqa_wifi_test_su_get_lq(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  code *local_1c;
  
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_30 = 0x52;
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 0xffffffff;
    }
    uVar2 = 0xffffffff;
    printk("%s: pOutput is NULL\n","hqa_wifi_test_su_get_lq");
  }
  else {
    if (0 < DebugLevel) {
      printk("%s:pOutput = %p\n","hqa_wifi_test_su_get_lq",param_2);
    }
    iVar1 = AndesAllocCmdMsg(param_1,4);
    if (iVar1 == 0) {
      if (DebugLevel < 0) {
        return 0xffffffff;
      }
      uVar2 = 0xffffffff;
      printk("%s: msg is NULL\n","hqa_wifi_test_su_get_lq");
    }
    else {
      local_1c = eventDispatcher;
      local_28 = CONCAT31(local_28._1_3_,5);
      local_2c = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_2c));
      local_28 = CONCAT22(0x18,(undefined2)local_28);
      uVar2 = 0;
      local_20 = param_2;
      AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,param_2,eventDispatcher);
      AndesAppendCmdMsg(iVar1,&local_30,4);
      AndesSendCmdMsg(param_1,iVar1);
    }
  }
  if (0 < DebugLevel) {
    printk("%s: Ret=%d\n","hqa_wifi_test_su_get_lq",uVar2);
  }
  return uVar2;
}

