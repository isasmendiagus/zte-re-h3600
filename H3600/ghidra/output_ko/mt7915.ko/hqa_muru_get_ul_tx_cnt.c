// module: mt7915.ko
// function: hqa_muru_get_ul_tx_cnt @ 0x23da08
// size: 328 bytes
//

undefined4 hqa_muru_get_ul_tx_cnt(undefined4 param_1,int param_2)

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
  undefined4 *local_20;
  code *local_1c;
  
  local_40 = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_3c = 0x67;
  if (param_2 != 0) {
    local_40 = os_str_tol(param_2,0,10);
    if (3 < DebugLevel) {
      printk("Index is: %d\n",local_40);
    }
    iVar1 = AndesAllocCmdMsg(param_1,8);
    if (iVar1 != 0) {
      local_20 = &local_38;
      local_1c = muruEventDispatcher;
      local_2c = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_2c));
      local_28 = CONCAT31(local_28._1_3_,5);
      uVar2 = 1;
      local_28 = CONCAT22(0xc,(undefined2)local_28);
      AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,muruEventDispatcher);
      AndesAppendCmdMsg(iVar1,&local_3c,4);
      AndesAppendCmdMsg(iVar1,&local_40,4);
      AndesSendCmdMsg(param_1,iVar1);
      goto LAB_0023db10;
    }
  }
  uVar2 = 0;
LAB_0023db10:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","hqa_muru_get_ul_tx_cnt",uVar2);
  }
  return uVar2;
}

