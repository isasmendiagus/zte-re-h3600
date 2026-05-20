// module: mt7915.ko
// function: hqa_wifi_test_su_cal_lq @ 0x8fdec
// size: 512 bytes
//

undefined4 hqa_wifi_test_su_cal_lq(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_3c;
  undefined1 local_36;
  undefined1 uStack_35;
  undefined1 local_34;
  undefined1 uStack_33;
  undefined2 local_32;
  undefined2 local_30;
  undefined2 local_2e;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_36 = 0;
  uStack_35 = 0;
  local_3c = 0x53;
  local_34 = 0;
  uStack_33 = 0;
  local_32 = 0;
  local_30 = 0;
  local_2e = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (param_2 == (undefined1 *)0x0) {
    if (DebugLevel < 0) {
      return 0xffffffff;
    }
    uVar2 = 0xffffffff;
    printk("%s: Params is NULL!!\n","hqa_wifi_test_su_cal_lq");
  }
  else {
    local_36 = *param_2;
    uStack_35 = param_2[1];
    local_34 = param_2[2];
    uStack_33 = param_2[3];
    local_2e = *(undefined2 *)(param_2 + 8);
    local_32 = *(undefined2 *)(param_2 + 4);
    if ((0 < DebugLevel) &&
       (printk("%s: CMD_HQA_SET_SU_CALC_LQ\n","hqa_wifi_test_su_cal_lq"), 0 < DebugLevel)) {
      printk("%s: Nu_User:%u, BW:%u, Nss0:%u PFMUID:%u NTxer:%u GroupIndex:%u\n",
             "hqa_wifi_test_su_cal_lq",local_36,uStack_35,local_34,uStack_33,(undefined1)local_32,
             local_2e);
    }
    iVar1 = AndesAllocCmdMsg(param_1,0xe);
    if (iVar1 == 0) {
      if (DebugLevel < 0) {
        return 0xffffffff;
      }
      uVar2 = 0xffffffff;
      printk("%s: msg is NULL\n","hqa_wifi_test_su_cal_lq");
    }
    else {
      local_2c = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_2c));
      local_28 = CONCAT31(local_28._1_3_,10);
      uVar2 = 0;
      AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,local_1c);
      AndesAppendCmdMsg(iVar1,&local_3c,4);
      AndesAppendCmdMsg(iVar1,&local_36,10);
      AndesSendCmdMsg(param_1,iVar1);
    }
  }
  if (0 < DebugLevel) {
    printk("%s: Ret=%d\n","hqa_wifi_test_su_cal_lq",uVar2);
  }
  return uVar2;
}

