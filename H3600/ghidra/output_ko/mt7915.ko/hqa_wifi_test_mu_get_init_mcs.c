// module: mt7915.ko
// function: hqa_wifi_test_mu_get_init_mcs @ 0x8f9d0
// size: 404 bytes
//

undefined4 hqa_wifi_test_mu_get_init_mcs(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  code *local_1c;
  
  local_34 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_30 = 0x50;
  if (param_3 == 0) {
    if (DebugLevel < 0) {
      return 0xffffffff;
    }
    uVar2 = 0xffffffff;
    printk("%s: poutput is NULL\n","hqa_wifi_test_mu_get_init_mcs");
  }
  else {
    local_34 = param_2;
    if (0 < DebugLevel) {
      printk("%s: GroupIndex:%u poutput:%p param.groupIndex:%u\n","hqa_wifi_test_mu_get_init_mcs",
             param_2,param_3,param_2);
    }
    iVar1 = AndesAllocCmdMsg(param_1,8);
    if (iVar1 == 0) {
      if (DebugLevel < 0) {
        return 0xffffffff;
      }
      uVar2 = 0xffffffff;
      printk("%s: msg is NULL\n","hqa_wifi_test_mu_get_init_mcs");
    }
    else {
      local_1c = eventDispatcher;
      local_28 = CONCAT31(local_28._1_3_,5);
      local_2c = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_2c));
      local_28 = CONCAT22(0x14,(undefined2)local_28);
      uVar2 = 0;
      local_20 = param_3;
      AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,param_3,eventDispatcher);
      AndesAppendCmdMsg(iVar1,&local_30,4);
      AndesAppendCmdMsg(iVar1,&local_34,4);
      AndesSendCmdMsg(param_1,iVar1);
    }
  }
  if (0 < DebugLevel) {
    printk("%s: Ret=%d\n","hqa_wifi_test_mu_get_init_mcs",uVar2);
  }
  return uVar2;
}

