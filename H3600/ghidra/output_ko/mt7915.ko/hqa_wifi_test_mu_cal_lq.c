// module: mt7915.ko
// function: hqa_wifi_test_mu_cal_lq @ 0x8fb68
// size: 640 bytes
//

undefined4 hqa_wifi_test_mu_cal_lq(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_50;
  undefined1 local_4a;
  undefined1 uStack_49;
  undefined1 local_48;
  undefined1 uStack_47;
  undefined1 local_46;
  undefined1 uStack_45;
  undefined1 local_44;
  undefined1 uStack_43;
  undefined1 local_42;
  undefined1 uStack_41;
  undefined2 local_40;
  undefined2 local_3e;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_4a = 0;
  uStack_49 = 0;
  local_50 = 0x4d;
  local_48 = 0;
  uStack_47 = 0;
  local_46 = 0;
  uStack_45 = 0;
  local_44 = 0;
  uStack_43 = 0;
  local_42 = 0;
  uStack_41 = 0;
  local_40 = 0;
  local_3e = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  if (param_2 == (undefined1 *)0x0) {
    if (DebugLevel < 0) {
      return 0xffffffff;
    }
    uVar2 = 0xffffffff;
    printk("%s: Params is NULL!!\n","hqa_wifi_test_mu_cal_lq");
  }
  else {
    uStack_41 = param_2[9];
    local_4a = *param_2;
    uStack_49 = param_2[1];
    local_48 = param_2[2];
    uStack_47 = param_2[3];
    local_46 = param_2[4];
    uStack_45 = param_2[5];
    local_44 = param_2[6];
    uStack_43 = param_2[7];
    local_42 = param_2[8];
    local_40 = *(undefined2 *)(param_2 + 10);
    local_3e = *(undefined2 *)(param_2 + 0xc);
    if (((0 < DebugLevel) &&
        (printk("%s: CMD_HQA_SET_MU_CALC_LQ\n","hqa_wifi_test_mu_cal_lq"), 0 < DebugLevel)) &&
       (printk("%s: Num_User:%u, BW:%u, Nss[0~3]:%u %u %u %u\n","hqa_wifi_test_mu_cal_lq",local_4a,
               uStack_49,local_48,uStack_47,local_46,uStack_45), 0 < DebugLevel)) {
      printk("%s: PFID[0~3]:%u %u %u %u Num_Txer:%u GroupIndex:%u\n","hqa_wifi_test_mu_cal_lq",
             local_44,uStack_43,local_42,uStack_41,(undefined1)local_40,local_3e);
    }
    iVar1 = AndesAllocCmdMsg(param_1,0x12);
    if (iVar1 == 0) {
      if (DebugLevel < 0) {
        return 0xffffffff;
      }
      uVar2 = 0xffffffff;
      printk("%s: msg is NULL\n","hqa_wifi_test_mu_cal_lq");
    }
    else {
      local_3c = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_3c));
      local_38 = CONCAT31(local_38._1_3_,10);
      uVar2 = 0;
      AndesInitCmdMsg(iVar1,local_3c,local_38,local_34,local_30,local_2c);
      AndesAppendCmdMsg(iVar1,&local_50,4);
      AndesAppendCmdMsg(iVar1,&local_4a,0xe);
      AndesSendCmdMsg(param_1,iVar1);
    }
  }
  if (0 < DebugLevel) {
    printk("%s: Ret=%d\n","hqa_wifi_test_mu_cal_lq",uVar2);
  }
  return uVar2;
}

