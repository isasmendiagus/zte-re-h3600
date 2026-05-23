// module: mt7915.ko
// function: hqa_wifi_test_mu_get_qd @ 0x90e28
// size: 396 bytes
//

undefined4 hqa_wifi_test_mu_get_qd(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_31;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  code *local_1c;
  
  local_31 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_30 = 0x51;
  if (param_3 == 0) {
    if (DebugLevel < 0) {
      return 0xffffffff;
    }
    uVar2 = 0xffffffff;
    printk("%s: pOutput is NULL\n","hqa_wifi_test_mu_get_qd");
  }
  else {
    local_31 = (undefined1)param_2;
    if (0 < DebugLevel) {
      printk("%s: param.scIdx:%d\n","hqa_wifi_test_mu_get_qd",param_2);
    }
    iVar1 = AndesAllocCmdMsg(param_1,5);
    if (iVar1 == 0) {
      if (DebugLevel < 0) {
        return 0xffffffff;
      }
      uVar2 = 0xffffffff;
      printk("%s: msg is NULL\n","hqa_wifi_test_mu_get_qd");
    }
    else {
      local_1c = eventDispatcher;
      local_28 = CONCAT31(local_28._1_3_,5);
      local_2c = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_2c));
      local_28 = CONCAT22(0x3c,(undefined2)local_28);
      uVar2 = 0;
      local_20 = param_3;
      AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,param_3,eventDispatcher);
      AndesAppendCmdMsg(iVar1,&local_30,4);
      AndesAppendCmdMsg(iVar1,&local_31,1);
      AndesSendCmdMsg(param_1,iVar1);
    }
  }
  if (0 < DebugLevel) {
    printk("%s: Ret=%d\n","hqa_wifi_test_mu_get_qd",uVar2);
  }
  return uVar2;
}

