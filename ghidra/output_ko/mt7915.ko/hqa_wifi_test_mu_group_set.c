// module: mt7915.ko
// function: hqa_wifi_test_mu_group_set @ 0x90b10
// size: 788 bytes
//

undefined4 hqa_wifi_test_mu_group_set(undefined4 param_1,undefined2 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined2 local_3e;
  undefined1 local_3c;
  undefined1 uStack_3b;
  undefined1 local_3a;
  byte bStack_39;
  undefined1 local_38;
  undefined1 uStack_37;
  undefined1 local_36;
  undefined1 uStack_35;
  undefined1 local_34;
  undefined1 uStack_33;
  undefined1 local_32;
  undefined1 uStack_31;
  undefined1 local_30;
  undefined1 uStack_2f;
  undefined1 local_2e;
  undefined1 uStack_2d;
  undefined1 local_2c;
  undefined1 uStack_2b;
  undefined1 local_2a;
  undefined1 uStack_29;
  
  local_3e = 0;
  local_58 = 0x4a;
  local_3c = 0;
  uStack_3b = 0;
  local_3a = 0;
  bStack_39 = 0;
  local_38 = 0;
  uStack_37 = 0;
  local_36 = 0;
  uStack_35 = 0;
  local_34 = 0;
  uStack_33 = 0;
  local_32 = 0;
  uStack_31 = 0;
  local_30 = 0;
  uStack_2f = 0;
  local_2e = 0;
  uStack_2d = 0;
  local_2c = 0;
  uStack_2b = 0;
  local_2a = 0;
  uStack_29 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  if (param_2 == (undefined2 *)0x0) {
    if (DebugLevel < 0) {
      return 0xffffffff;
    }
    uVar2 = 0xffffffff;
    printk("%s: mu_group params is NULL!!\n","hqa_wifi_test_mu_group_set");
  }
  else {
    local_3e = *param_2;
    local_2c = *(undefined1 *)(param_2 + 1);
    local_3c = *(undefined1 *)((int)param_2 + 3);
    local_3a = *(undefined1 *)((int)param_2 + 5);
    uStack_37 = *(undefined1 *)(param_2 + 5);
    local_36 = *(undefined1 *)((int)param_2 + 0xb);
    uStack_3b = *(undefined1 *)(param_2 + 2);
    bStack_39 = *(byte *)(param_2 + 3);
    uStack_29 = *(undefined1 *)(param_2 + 4);
    local_2a = *(undefined1 *)((int)param_2 + 7);
    local_38 = *(undefined1 *)((int)param_2 + 9);
    uStack_35 = *(undefined1 *)(param_2 + 6);
    uStack_2b = *(undefined1 *)((int)param_2 + 0xd);
    local_34 = *(undefined1 *)(param_2 + 0xb);
    uStack_33 = *(undefined1 *)((int)param_2 + 0x17);
    uStack_31 = *(undefined1 *)((int)param_2 + 0x19);
    local_32 = *(undefined1 *)(param_2 + 0xc);
    local_30 = *(undefined1 *)(param_2 + 9);
    uStack_2f = *(undefined1 *)((int)param_2 + 0x13);
    local_2e = *(undefined1 *)(param_2 + 10);
    uStack_2d = *(undefined1 *)((int)param_2 + 0x15);
    if ((0 < DebugLevel) &&
       (printk("%s: MU_STRUCT_MU_GROUP Content\n","hqa_wifi_test_mu_group_set"), 0 < DebugLevel)) {
      uVar3 = (uint)bStack_39;
      printk("Gindex:%u Num_User:%u BW:%u LDPC[0~3]:%u %u %u %u\n",local_3e,local_2c,uStack_29,
             local_3c,uStack_3b,local_3a,uVar3);
      if ((0 < DebugLevel) &&
         (printk("Nss[0~3]:%u %u %u %u GID:%u SGI:%u\n",local_38,uStack_37,local_36,uStack_35,
                 uStack_2b,local_2a,uVar3), 0 < DebugLevel)) {
        printk("InitMCS[0~3]:%u %u %u %u PFID[0~3]:%u %u %u %u\n",local_34,uStack_33,local_32,
               uStack_31,local_30,uStack_2f,local_2e,uStack_2d);
      }
    }
    iVar1 = AndesAllocCmdMsg(param_1,0x1a);
    if (iVar1 == 0) {
      if (DebugLevel < 0) {
        return 0xffffffff;
      }
      uVar2 = 0xffffffff;
      printk("%s: msg is NULL\n","hqa_wifi_test_mu_group_set");
    }
    else {
      uVar2 = 0;
      local_54 = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_54));
      local_50 = CONCAT31(local_50._1_3_,10);
      AndesInitCmdMsg(iVar1,local_54,local_50,local_4c,local_48,local_44);
      AndesAppendCmdMsg(iVar1,&local_58,4);
      AndesAppendCmdMsg(iVar1,&local_3e,0x16);
      AndesSendCmdMsg(param_1,iVar1);
    }
  }
  if (0 < DebugLevel) {
    printk("%s: Ret=%d\n","hqa_wifi_test_mu_group_set",uVar2);
  }
  return uVar2;
}

