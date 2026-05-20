// module: mt7915.ko
// function: hqa_muru_reset_ul_tx_cnt @ 0x23d88c
// size: 376 bytes
//

undefined4 hqa_muru_reset_ul_tx_cnt(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_29;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_29 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_28 = 0x66;
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Argument is NULL\n","hqa_muru_reset_ul_tx_cnt");
  }
  else {
    local_29 = os_str_toul(param_2,0,10);
    iVar1 = AndesAllocCmdMsg(param_1,5);
    if (iVar1 != 0) {
      local_24 = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_24));
      local_20 = CONCAT31(local_20._1_3_,10);
      AndesInitCmdMsg(iVar1,local_24,local_20,local_1c,local_18,local_14);
      AndesAppendCmdMsg(iVar1,&local_28,4);
      AndesAppendCmdMsg(iVar1,&local_29,1);
      AndesSendCmdMsg(param_1,iVar1);
      if (DebugLevel < 1) {
        return 1;
      }
      uVar2 = 1;
      goto LAB_0023d9d8;
    }
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: msg is NULL\n","hqa_muru_reset_ul_tx_cnt");
  }
  if (DebugLevel < 1) {
    return 0;
  }
  uVar2 = 0;
LAB_0023d9d8:
  printk("%s: CMD %s\n","hqa_muru_reset_ul_tx_cnt");
  return uVar2;
}

