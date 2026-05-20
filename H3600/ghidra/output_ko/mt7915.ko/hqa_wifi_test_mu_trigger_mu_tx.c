// module: mt7915.ko
// function: hqa_wifi_test_mu_trigger_mu_tx @ 0x910f4
// size: 620 bytes
//

undefined4 hqa_wifi_test_mu_trigger_mu_tx(undefined4 param_1,byte *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  int local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_60 = 0x1f;
  if (param_2 == (byte *)0x0) {
    if (DebugLevel < 0) {
      return 0xffffffff;
    }
    uVar2 = 0xffffffff;
    printk("%s: Param is NULL!!\n","hqa_wifi_test_mu_trigger_mu_tx");
  }
  else {
    local_40 = *(undefined4 *)(param_2 + 0x14);
    local_3c = *(undefined4 *)(param_2 + 4);
    local_38 = *(undefined4 *)(param_2 + 8);
    local_34 = *(undefined4 *)(param_2 + 0xc);
    local_30 = *(undefined4 *)(param_2 + 0x10);
    local_44 = *(int *)(param_2 + 0x18) + 1;
    local_48 = CONCAT31((uint3)*param_2,1);
    local_2c = 0x4030201;
    if ((-1 < DebugLevel) &&
       (printk("%s: MD_SET_TRIGGER_MU_TX_FRAME\n","hqa_wifi_test_mu_trigger_mu_tx"), 0 < DebugLevel)
       ) {
      uVar2 = local_40;
      iVar1 = local_44;
      printk("RndmPattern:%u Payload_Len[0~3]:%u %u %u %u Round:%u NumSta:%u\n",local_48._1_1_,
             local_3c,local_38,local_34,local_30,local_40,local_44);
      if (0 < DebugLevel) {
        printk("AC:%u WlanIndex[0~3]:%u %u %u %u\n",local_48 & 0xff,local_2c & 0xff,local_2c._1_1_,
               local_2c >> 0x10 & 0xff,local_2c >> 0x18,uVar2,iVar1);
      }
    }
    iVar1 = AndesAllocCmdMsg(param_1,0x24);
    if (iVar1 == 0) {
      if (DebugLevel < 0) {
        return 0xffffffff;
      }
      uVar2 = 0xffffffff;
      printk("%s: msg is NULL\n","hqa_wifi_test_mu_trigger_mu_tx");
    }
    else {
      uVar2 = 0;
      local_5c = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_5c));
      local_58 = CONCAT31(local_58._1_3_,10);
      AndesInitCmdMsg(iVar1,local_5c,local_58,local_54,local_50,local_4c);
      AndesAppendCmdMsg(iVar1,&local_60,4);
      AndesAppendCmdMsg(iVar1,&local_48,0x20);
      AndesSendCmdMsg(param_1,iVar1);
    }
  }
  if (0 < DebugLevel) {
    printk("%s: Ret=%d\n","hqa_wifi_test_mu_trigger_mu_tx",uVar2);
  }
  return uVar2;
}

