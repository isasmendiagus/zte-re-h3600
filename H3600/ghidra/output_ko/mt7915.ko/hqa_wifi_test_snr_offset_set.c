// module: mt7915.ko
// function: hqa_wifi_test_snr_offset_set @ 0x902d0
// size: 312 bytes
//

undefined4 hqa_wifi_test_snr_offset_set(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_31;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_31 = (undefined1)param_2;
  local_30 = 0x47;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (0 < DebugLevel) {
    printk("%s: offset: 0x%x\n","hqa_wifi_test_snr_offset_set",param_2);
  }
  iVar1 = AndesAllocCmdMsg(param_1,5);
  if (iVar1 == 0) {
    if (DebugLevel < 0) {
      return 0xffffffff;
    }
    uVar2 = 0xffffffff;
    printk("%s: msg is NULL\n","hqa_wifi_test_snr_offset_set");
  }
  else {
    local_2c = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_2c));
    local_28 = CONCAT31(local_28._1_3_,10);
    uVar2 = 0;
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,local_1c);
    AndesAppendCmdMsg(iVar1,&local_30,4);
    AndesAppendCmdMsg(iVar1,&local_31,1);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (0 < DebugLevel) {
    printk("%s: Ret=%d\n","hqa_wifi_test_snr_offset_set",uVar2);
  }
  return uVar2;
}

